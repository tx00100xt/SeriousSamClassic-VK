/* Copyright (c) 2002-2012 Croteam Ltd. 
   Copyright (c) 2020 Sultim Tsyrendashiev
This program is free software; you can redistribute it and/or modify
it under the terms of version 2 of the GNU General Public License as published by
the Free Software Foundation


This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA. */

#include "Engine/StdH.h"

#include <Engine/Graphics/ViewPort.h>

#include <Engine/Graphics/GfxProfile.h>
#include <Engine/Graphics/GfxLibrary.h>
#include <Engine/Base/Statistics_Internal.h>

#ifdef SE1_VULKAN
#include <Engine/Graphics/Vulkan/SvkMain.h>
#include <Engine/Base/Translation.h>
#include <Engine/Base/Console.h>
// may instead choose to use std::clamp() in C++17
#define CLAMP(x, lo, hi)    ((x) < (lo) ? (lo) : (x) > (hi) ? (hi) : (x))
#endif

#include <Engine/Base/Translation.h>
#include <Engine/Base/Console.h>

extern INDEX ogl_bExclusive;
extern INDEX gfx_bRenderOnParentWindow;

// helper for D3D surface
#ifdef SE1_D3D
static HRESULT CreateSwapChain_D3D( CViewPort *pvp, PIX pixSizeI, PIX pixSizeJ)
{
  HRESULT hr;
  
  // release old if still allocated
  if( pvp->vp_pSwapChain!=NULL) {
    ASSERT( pvp->vp_pSurfDepth!=NULL);
    D3DRELEASE( pvp->vp_pSwapChain, TRUE);
    D3DRELEASE( pvp->vp_pSurfDepth, TRUE);
  } else ASSERT(pvp->vp_pSurfDepth==NULL);

  D3DPRESENT_PARAMETERS d3dPresentParams;
  memset( &d3dPresentParams, 0, sizeof(d3dPresentParams));
  d3dPresentParams.Windowed = TRUE;
  d3dPresentParams.BackBufferWidth  = pixSizeI;
  d3dPresentParams.BackBufferHeight = pixSizeJ;
  d3dPresentParams.BackBufferFormat = _pGfx->gl_d3dColorFormat;
  d3dPresentParams.BackBufferCount  = 1;
  d3dPresentParams.MultiSampleType  = D3DMULTISAMPLE_NONE; // !!!! TODO
  d3dPresentParams.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
  d3dPresentParams.SwapEffect = D3DSWAPEFFECT_DISCARD; 
  d3dPresentParams.hDeviceWindow = pvp->vp_hWnd;
  ASSERT( pvp->vp_pSwapChain==NULL && pvp->vp_pSurfDepth==NULL);
  hr = _pGfx->gl_pd3dDevice->CreateAdditionalSwapChain( &d3dPresentParams, &pvp->vp_pSwapChain);
  D3D_CHECKERROR(hr);
  hr = _pGfx->gl_pd3dDevice->CreateDepthStencilSurface( pixSizeI, pixSizeJ, _pGfx->gl_d3dDepthFormat,
                                                        D3DMULTISAMPLE_NONE, &pvp->vp_pSurfDepth);
  D3D_CHECKERROR(hr);
  ASSERT( pvp->vp_pSwapChain!=NULL);
  ASSERT( pvp->vp_pSurfDepth!=NULL);
}

static void SetAsRenderTarget_D3D( CViewPort *pvp)
{
  HRESULT hr;
  LPDIRECT3DSURFACE8 pColorSurface;
  if (pvp->vp_pSwapChain != NULL)
  {
    hr = pvp->vp_pSwapChain->GetBackBuffer( 0, D3DBACKBUFFER_TYPE_MONO, &pColorSurface); 
    D3D_CHECKERROR(hr);
    hr = _pGfx->gl_pd3dDevice->SetRenderTarget( pColorSurface, pvp->vp_pSurfDepth);
    D3D_CHECKERROR(hr);
    D3DRELEASE( pColorSurface, TRUE);
  }
}
#endif // SE1_D3D
#ifdef PLATFORM_WIN32
// helper for OGL

CTempDC::CTempDC(HWND hWnd)
{
  ASSERT(hWnd!=NULL);
  hwnd = hWnd;
  hdc = GetDC(hwnd);
  ASSERT(hdc!=NULL);
}

CTempDC::~CTempDC(void)
{
  ReleaseDC(hwnd, hdc);
}
#endif

/*
 *   ViewPort functions
 */

CViewPort::CViewPort( PIX pixWidth, PIX pixHeight, HWND hWnd) :
                      vp_Raster( pixWidth, pixHeight, 0)
{
  vp_hWnd = NULL;
  vp_hWndParent = hWnd;
#ifdef SE1_D3D
  vp_pSwapChain = NULL;
  vp_pSurfDepth = NULL;
#endif // SE1_D3D
#ifdef SE1_VULKAN
  // nothing 
#endif // SE1_VULKAN

  vp_ctDisplayChanges = 0;
  OpenCanvas();
  vp_Raster.ra_pvpViewPort = this;
}


CViewPort::~CViewPort(void)
{
  CloseCanvas(TRUE);
  // reset current viewport if needed
  if( _pGfx->gl_pvpActive==this) _pGfx->gl_pvpActive = NULL;
}


#ifdef PLATFORM_WIN32
#define CViewPortCLASS "ViewPort Window"
static BOOL _bClassRegistered = FALSE;

LRESULT CALLBACK CViewPortCLASS_WindowProc(
  HWND hWnd,      // handle to window
  UINT Msg,       // message identifier
  WPARAM wParam,  // first message parameter
  LPARAM lParam   // second message parameter
)
{
  // forget erase bacground messages
  if (Msg==WM_ERASEBKGND) return TRUE;

  // if any mouse message
  if ((Msg>=WM_MOUSEFIRST&&Msg<=WM_MOUSELAST)) {
    // send it to parent
    HWND hWndParent = GetParent(hWnd);
    ASSERT(hWndParent!=NULL);
    return CallWindowProc( (WNDPROC)GetWindowLongPtr(hWndParent, GWLP_WNDPROC),
                           hWndParent, Msg, wParam, lParam);
  }

  LRESULT r = DefWindowProc( hWnd, Msg, wParam, lParam );

  // UGLY fix! For some reason DefWindowProc returns 0
  return TRUE;
}
#endif

// open overlaid window for rendering context
void CViewPort::OpenCanvas(void)
{
#ifdef PLATFORM_WIN32
  // rendering on parent window
#if defined(SE1_D3D) && defined(SE1_VULKAN) 
  if(gfx_bRenderOnParentWindow && (_pGfx->gl_eCurrentAPI == GAT_D3D || _pGfx->gl_eCurrentAPI == GAT_VK))
#elif !defined(SE1_D3D) && defined(SE1_VULKAN) 
  if(gfx_bRenderOnParentWindow && _pGfx->gl_eCurrentAPI == GAT_VK)
#elif !defined(SE1_D3D) && !defined(SE1_VULKAN) 
  if(FALSE)
#endif
  {
    vp_hWnd = vp_hWndParent;
    // determine window and desktopsize
    RECT rectWindow;
    GetClientRect( vp_hWndParent, &rectWindow);
    const PIX pixWinSizeI = rectWindow.right  - rectWindow.left;
    const PIX pixWinSizeJ = rectWindow.bottom - rectWindow.top;
    CDisplayMode dm;
    _pGfx->GetCurrentDisplayMode(dm);
    ASSERT( (dm.dm_pixSizeI==0 && dm.dm_pixSizeJ==0) || (dm.dm_pixSizeI!=0 && dm.dm_pixSizeJ!=0));
    const BOOL bFullScreen = (dm.dm_pixSizeI==pixWinSizeI && dm.dm_pixSizeJ==pixWinSizeJ);

#ifdef SE1_D3D
    // prepare new swap chain for D3D
    if( _pGfx->gl_eCurrentAPI==GAT_D3D && !bFullScreen)
    {
      HRESULT hr;
      if( (hr=CreateSwapChain_D3D( this, pixWinSizeI, pixWinSizeJ)))
      {
        CPrintF("CreateSwapChain_D3D Failed!! - OpenCanvas Parent %x",hr);
      }
    }
#endif

#ifdef SE1_VULKAN
    // prepare new swap chain for Vulkan
    if( _pGfx->gl_eCurrentAPI==GAT_VK)
    {
      CPrintF("Vulkan: Try Create Swapchain...\n");
      _pGfx->gl_SvkMain->CreateSwapchain(pixWinSizeI, pixWinSizeJ);
      //_pGfx->gl_SvkMain->Initialize();
      CPrintF("Vulkan: Create Swapchain Done.\nVulkan: === Ready to Render ===\n");
    }
#endif

    // resize raster
    Resize();
    ShowWindow( vp_hWnd, SW_SHOW);

#ifdef SE1_D3D
    // set as rendering target
    if( _pGfx->gl_eCurrentAPI==GAT_D3D && vp_pSwapChain!=NULL) 
      SetAsRenderTarget_D3D(this);
#endif
   } 
   else { // rendering on child window

    // do nothing if not feasable
    if( vp_hWnd!=NULL || vp_hWndParent==NULL) return;

    // register class
    if( !_bClassRegistered) {
      WNDCLASSA wc;
      wc.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
      wc.lpfnWndProc = CViewPortCLASS_WindowProc;
      wc.cbClsExtra = 0;
      wc.cbWndExtra = 0;
      wc.hInstance = NULL;
      wc.hIcon = NULL;
      wc.hCursor = LoadCursor( NULL, IDC_ARROW);
      wc.hbrBackground = NULL;
      wc.lpszMenuName = NULL;
      wc.lpszClassName = CViewPortCLASS;
      RegisterClassA(&wc);
      _bClassRegistered = TRUE;
    }
  
    // determine window and desktopsize
    RECT rectWindow;
    GetClientRect( vp_hWndParent, &rectWindow);
    const PIX pixWinSizeI = rectWindow.right  - rectWindow.left;
    const PIX pixWinSizeJ = rectWindow.bottom - rectWindow.top;
    CDisplayMode dm;
    _pGfx->GetCurrentDisplayMode(dm);
    ASSERT( (dm.dm_pixSizeI==0 && dm.dm_pixSizeJ==0) || (dm.dm_pixSizeI!=0 && dm.dm_pixSizeJ!=0));
    const BOOL bFullScreen = (dm.dm_pixSizeI==pixWinSizeI && dm.dm_pixSizeJ==pixWinSizeJ);

    // set fullscreen attribs if window size is equal to screen size
    DWORD dwExStyle = NONE;
    DWORD dwStyle   = WS_CHILD|WS_CLIPCHILDREN|WS_CLIPSIBLINGS;
    if( bFullScreen && ogl_bExclusive) {
      dwExStyle = WS_EX_TOPMOST;
      dwStyle   = WS_POPUP;     
    } 

    // set child window
    vp_hWnd = ::CreateWindowExA(
      dwExStyle,
      CViewPortCLASS,
      "",   // title
      dwStyle,
      0,0,
      0,0,  // window size
      vp_hWndParent,
      NULL,
      (HINSTANCE)GetWindowLongPtr(vp_hWndParent, GWLP_HINSTANCE),
      NULL);
    ASSERT( vp_hWnd!=NULL);
#ifdef SE1_D3D
    // prepare new swap chain for D3D
    if( _pGfx->gl_eCurrentAPI==GAT_D3D && !bFullScreen) CreateSwapChain_D3D( this, pixWinSizeI, pixWinSizeJ);
#endif // SE1_D3D

#ifdef SE1_VULKAN
    if (_pGfx->gl_eCurrentAPI == GAT_VK)
    {
      CPrintF("Vulkan: Try Create Swapchain...\n");
      _pGfx->gl_SvkMain->CreateSwapchain(pixWinSizeI, pixWinSizeJ);
      CPrintF("Vulkan: Create Swapchain Done.\nVulkan: === Ready to Render ===\n");
    }
#endif // SE1_VULKAN

    // resize raster
    Resize();
    ShowWindow( vp_hWnd, SW_SHOW);
#ifdef SE1_D3D
    // set as rendering target
    if( _pGfx->gl_eCurrentAPI==GAT_D3D && vp_pSwapChain!=NULL) SetAsRenderTarget_D3D(this);
#endif // SE1_D3D
  }

#else  // !PLATFORM_WIN32
  vp_hWnd = vp_hWndParent;
#ifdef SE1_VULKAN
  if (_pGfx->gl_eCurrentAPI == GAT_VK)
  {
    CPrintF("Vulkan: Try Create Swapchain...\n");
    _pGfx->gl_SvkMain->CreateSwapchain(0, 0); //  SDL_Vulkan_GetDrawableSize in SvkSwapchain.cpp 
    CPrintF("Vulkan: Create Swapchain Done.\nVulkan: === Ready to Render ===\n");
    extern  __attribute__ ((visibility("default"))) SDL_Window * _hwndMain;
  }
  // is it required?
  // if (_pGfx->gl_eCurrentAPI == GAT_VK && vp_VkSwapchain != VK_NULL_HANDLE) SetAsRenderTarget_Vulkan(this);
#endif // SE1_VULKAN
#endif
}


// close overlaid window
void CViewPort::CloseCanvas( BOOL bRelease/*=FALSE*/)
{
  // release D3D swap chain if allocated
#ifdef SE1_D3D
  if( _pGfx->gl_eCurrentAPI==GAT_D3D && bRelease) {
    if( vp_pSwapChain!=NULL) D3DRELEASE( vp_pSwapChain, TRUE);
    if( vp_pSurfDepth!=NULL) D3DRELEASE( vp_pSurfDepth, TRUE);
  }
#endif // SE1_D3D
#ifdef SE1_VULKAN
  if (_pGfx->gl_eCurrentAPI == GAT_VK && bRelease) 
  {
    _pGfx->gl_SvkMain->DestroySwapchain();
  }
#endif // SE1_VULKAN


  // destroy window
#ifdef PLATFORM_WIN32
  if (gfx_bRenderOnParentWindow == FALSE || _pGfx->gl_eCurrentAPI == GAT_OGL) // only for child window
  {
    if( vp_hWnd!=NULL && IsWindow(vp_hWnd)) 
    { 
      BOOL bRes = DestroyWindow(vp_hWnd);
      ASSERT(bRes);
    }
  }
#endif

  // mark
  vp_hWnd = NULL;
#ifdef SE1_D3D
  vp_pSwapChain = NULL;
  vp_pSurfDepth = NULL;
#endif // SE1_D3D

#ifdef SE1_VULKAN
  // nothing 
#endif // SE1_VULKAN
}


// Change size of this viewport, it's raster and all it's drawports
void CViewPort::Resize(void)
{
#ifdef PLATFORM_WIN32
	PIX pixNewWidth, pixNewHeight;
	RECT rectWindow;

	// get the size of the window
	GetClientRect( vp_hWndParent, &rectWindow);
	pixNewWidth  = rectWindow.right  - rectWindow.left;
	pixNewHeight = rectWindow.bottom - rectWindow.top;

  // resize child window
  if(gfx_bRenderOnParentWindow == FALSE || _pGfx->gl_eCurrentAPI == GAT_OGL)
  {
    ASSERT( vp_hWnd!=NULL);
    SetWindowPos( vp_hWnd, NULL, 0,0, pixNewWidth, pixNewHeight, SWP_NOZORDER|SWP_NOMOVE);
  }

  // resize the raster
  vp_Raster.Resize( pixNewWidth, pixNewHeight);

  // "resize" D3D surface (if any)
#ifdef SE1_D3D
  if( _pGfx->gl_eCurrentAPI==GAT_D3D && vp_pSwapChain!=NULL) {
    // release old surface
    ASSERT( vp_pSurfDepth!=NULL);
    D3DRELEASE( vp_pSwapChain, TRUE);
    D3DRELEASE( vp_pSurfDepth, TRUE);
    // create a new one and set it as current
    HRESULT hr;
    if( (hr=CreateSwapChain_D3D( this, pixNewWidth, pixNewHeight)) )
    {
      CPrintF("CViewPort::Resize CreateSwapChain_D3D Failed!! - Resize %x",hr);
    }
    SetAsRenderTarget_D3D(this);
  }
#endif // SE1_D3D
#endif // PLATFORM_WIN32
#ifdef SE1_VULKAN
  if (_pGfx->gl_eCurrentAPI == GAT_VK)
  {
    CPrintF("Vulkan: Try ReCreate Swapchain...\n");
 #ifdef PLATFORM_UNIX
    extern  __attribute__ ((visibility("default"))) SDL_Window * _hwndMain;
    
    _pGfx->gl_SvkMain->RecreateSwapchain(0, 0); //  SDL_Vulkan_GetDrawableSize in SvkSwapchain.cpp
 #else
    _pGfx->gl_SvkMain->RecreateSwapchain(pixNewWidth, pixNewHeight);
 #endif
    CPrintF("Vulkan: ReCreate Swapchain Done.\nVulkan: === Ready to Render ===\n");
  }
#endif // SE1_VULKAN
}


void CViewPort::SwapBuffers(void)
{
  // skip if child window not present
  if( vp_hWnd==NULL) return;

  // ask the current driver to swap buffers
  _sfStats.StartTimer(CStatForm::STI_SWAPBUFFERS);
  _pfGfxProfile.StartTimer( CGfxProfile::PTI_SWAPBUFFERS);
  _pfGfxProfile.IncrementAveragingCounter(1);
  _pGfx->SwapBuffers(this);
  _pfGfxProfile.StopTimer( CGfxProfile::PTI_SWAPBUFFERS);
  _sfStats.StopTimer(CStatForm::STI_SWAPBUFFERS);
}

