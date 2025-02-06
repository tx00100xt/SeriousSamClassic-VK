# Serious Sam Classic: Vulkan
[![Build status](https://github.com/tx00100xt/SeriousSamClassic-VK/actions/workflows/cibuild.yml/badge.svg)](https://github.com/tx00100xt//SeriousSamClassic-VK/actions/)
[![License: GPL v2](https://img.shields.io/badge/License-GPL_v2-blue.svg)](https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html)
[![GitHub release (latest by date)](https://img.shields.io/github/v/release/tx00100xt/SeriousSamClassic-VK)](https://github.com/tx00100xt/SeriousSamClassic-VK/releases/tag/1.10.7)
[![Github downloads](https://img.shields.io/github/downloads/tx00100xt/SeriousSamClassic-VK/total.svg?logo=github&logoColor=white&style=flat-square&color=E75776)](https://github.com/tx00100xt/SeriousSamClassic-VK/releases/)

Vulkan Serious Engine port based on [open source version](https://github.com/sultim-t/Serious-Engine-Vk).

![Screenshot 00](https://raw.githubusercontent.com/tx00100xt/SeriousSamClassic-VK/main/Images/samvulkan_1.png)
![Screenshot 01](https://raw.githubusercontent.com/tx00100xt/SeriousSamClassic-VK/main/Images/samvulkan_2.png)
![Screenshot 02](https://raw.githubusercontent.com/tx00100xt/SeriousSamClassic-VK/main/Images/samvulkan_3.png)
![Screenshot 00](https://raw.githubusercontent.com/tx00100xt/SeriousSamClassic-VK/main/Images/samvulkan_4.png)
![Screenshot 01](https://raw.githubusercontent.com/tx00100xt/SeriousSamClassic-VK/main/Images/samvulkan_5.png)
![Screenshot 02](https://raw.githubusercontent.com/tx00100xt/SeriousSamClassic-VK/main/Images/samvulkan_6.png)

Prerequisites:
* [Vulkan Header files and API registry](https://github.com/KhronosGroup/Vulkan-Headers)
* [Vulkan Validation Layers](https://github.com/KhronosGroup/Vulkan-ValidationLayers)
* [Vulkan Installable Client Driver (ICD) Loader](https://github.com/KhronosGroup/Vulkan-Loader) 

## Serious Engine:

This is the source code for Serious Engine v.1.10, including the following projects:

* `DedicatedServer`
* `Ecc` The *Entity Class Compiler*, a custom build tool used to compile *.es files
* `Engine` Serious Engine 1.10
* `EngineGUI` Common GUI things for game tools
* `EntitiesMP` All the entity logic
* `GameGUIMP` Common GUI things for game tools
* `GameMP` All the game logic
* `Modeler` Serious Modeler
* `RCon` Used to connect to servers using an admin password
* `SeriousSam` The main game executable
* `SeriousSkaStudio` Serious Ska Studio
* `WorldEditor` Serious Editor
* `DecodeReport` Used to decode crash *.rpt files
* `Depend` Used to build a list of dependency files based on a list of root files
* `LWSkaExporter` Exporter for use in LightWave
* `MakeFONT` Used for generating *.fnt files
* `TexConv` Used for converting *.tex files to *.tga images
* `Shaders` Compiled shaders
* `GameAgent` The serverlist masterserver written in Python
* `libogg`, `libvorbis` Third party libraries used for playing OGG-encoded ingame music (see http://www.vorbis.com/ for more information)

Prepare building for Debian/Ubuntu based OS
-------------------------------------------

Type this in your terminal:

```
sudo apt-get install build-essential libsdl2-dev cmake libvorbis-dev flex bison git libxxhash-dev
sudo apt-get install libvulkan1 libvulkan-dev vulkan-validationlayers vulkan-validationlayers-dev

```
Note: libsdl2-dev version >= 2.0.6, vulkan packages version >= 1.2.xxx
* For Debian 10, you can install vulkan packages from backports.

Building
--------
More detailed information about building the game for different operating systems and different platforms can be found on the [SeriousSamClassic-VK wiki.](https://github.com/tx00100xt/SeriousSamClassic-VK/wiki)


There are still many asserts in the engine. Most of them are irrelevant and should be removed, but while it's not done, the asserts will effectively kill the engine when triggered in the Debug build. Use Release or RelWithDebInfo build if you intend to play (automatically set as RelWithDebInfo in the build scripts).

### Linux

#### Setting up the repository

Type this in your terminal:

```
git clone https://github.com/tx00100xt/SeriousSamClassic-VK.git
```

#### Copy official game data (optional)

If you have access to a copy of the game (either by CD or through Steam),
you can copy the *.gro files from the game directory to the repository.
(SeriousSamClassic-VK/SamTFE is the directory of the game Serious Sam Classic The First Encounter, SeriousSamClassic-VK/SamTSE is the directory of the game Serious Sam Classic The Second Encounter)

#### Building (for SS:TFE and SS:TSE)

Type this in your terminal:

```
cd SeriousSamClassic-VK
mkdir build
cd build
cmake ..
make -j4
make install
```
If you prefer **ninja**, then add key **-GNinja** to the cmake. And replace the **make** command with **ninja**.

### Ubuntu 
Instead of building you can install packages from ppa by adding ppa:tx00100xt/serioussam to your system's Software Sources.
```bash
sudo add-apt-repository ppa:tx00100xt/serioussamclassic
sudo apt update
```
This PPA can be added to your system manually by copying the lines below and adding them to your system's software sources.
```
deb https://ppa.launchpadcontent.net/tx00100xt/serioussamclassic/ubuntu YOUR_UBUNTU_VERSION_HERE main 
deb-src https://ppa.launchpadcontent.net/tx00100xt/serioussamclassic/ubuntu YOUR_UBUNTU_VERSION_HERE main  
```
After adding ppa, run the commands:
```bash
sudo apt install serioussamclassic-vk serioussamclassic-xplus
```

### Gentoo
To build the game, use the ebuild included in the official Gentoo repository.  
https://packages.gentoo.org/packages/games-fps/serioussam  
You will also need CD images of the games Serious Sam Classic The First Encounter and  
Serious Sam Classic The First Encounter.

Type this in your terminal:

```
emerge -av serioussam --autounmask=y
```

For game add-ons, use a [serioussam-overlay](https://github.com/tx00100xt/serioussam-overlay) containing ready-made ebuilds for building the add-ons.  

Type this in your terminal:

```
emerge eselect-repository
eselect repository enable serioussam
emaint sync --repo serioussam
```
The list of add-ons can be found in [README](https://github.com/tx00100xt/serioussam-overlay/tree/main?tab=readme-ov-file#ebuilds)

### Arch Linux

To build a game under Arch Linux you can use the package from AUR: https://aur.archlinux.org/packages/serioussam-vk

### Raspberry Pi

The build for raspberry pi is similar to the build for Linux, you just need to add an additional build key.

```
cd SeriousSamClassic-VK
mkdir build
cd build
cmake -DRPI4=TRUE ..
make -j4
make install
```

### FreeBSD

#### Setting up the repository

Type this in your terminal:

```
git clone https://github.com/tx00100xt/SeriousSamClassic-VK.git
```

#### Copy official game data (optional)

If you have access to a copy of the game (either by CD or through Steam),
you can copy the *.gro files from the game directory to the repository.
(SeriousSamClassic-VK/SamTFE is the directory of the game Serious Sam Classic The First Encounter, SeriousSamClassic-VK/SamTSE is the directory of the game Serious Sam Classic The Second Encounter)

#### Building (for SS:TFE and SS:TSE)

Type this in your terminal:

```
cd SeriousSamClassic-VK
mkdir build
cd build
cmake ..
make -j4
make install
```
If you prefer **ninja**, then add key **-GNinja** to the cmake. And replace the **make** command with **ninja**.
For **i386** architecture, add key **-DUSE_ASM=OFF** to **cmake**.
To build a binary package for installation on the system, you can use the template:
https://github.com/tx00100xt/SeriousSamClassic-VK/tree/main/templates

### OpenBSD

#### Install the required packages
```
sudo pkg_add bison cmake git sdl2 libogg libvorbis nasm vulkan-loader
```
#### Setting up the repository

```
git clone https://github.com/tx00100xt/SeriousSamClassic-VK.git
```

#### Copy official game data (optional)

If you have access to a copy of the game (either by CD or through Steam),
you can copy the *.gro files from the game directory to the repository.
(SeriousSamClassic-VK/SamTFE is the directory of the game Serious Sam Classic The First Encounter, SeriousSamClassic-VK/SamTSE is the directory of the game Serious Sam Classic The Second Encounter)

#### Building for amd64 (for SS:TFE and SS:TSE)

Type this in your terminal:

```
cd SeriousSamClassic-VK
mkdir build
cd build
cmake .. -DUSE_ASM=OFF
make -j4
make install
```
If you prefer **ninja**, then add key **-GNinja** to the cmake. And replace the **make** command with **ninja**.
To build a binary package for installation on the system, you can use the template:
https://github.com/tx00100xt/SeriousSamClassic-VK/tree/main/templates

### NetBSD

Install required dependencies:
```
sudo pkgin install cmake nasm bison SDL2 libogg libvorbis
```
NetBSD does not have Vulkan support, so you need to disable its dependencies when building. To do this, 
use the argument **-DUSE_SYSTEM_VULKAN=FALSE** for the **cmake**.
The rest is the same as described for the OpenBSD.

### macOS

#### Install dependes

```
brew install bison flex sdl2 libogg libvorbis zlib-ng cmake git vulkan-loader vulkan-headers
```

#### Setting up the repository

Type this in your terminal:

```
git clone https://github.com/tx00100xt/SeriousSamClassic-VK.git
```

#### Copy official game data (optional)

If you have access to a copy of the game (either by CD or through Steam),
you can copy the *.gro files from the game directory to the repository.
(SeriousSamClassic-VK/SamTFE is the directory of the game Serious Sam Classic The First Encounter, SeriousSamClassic-VK/SamTSE is the directory of the game Serious Sam Classic The Second Encounter)

#### Building (for SS:TFE and SS:TSE)

Type this in your terminal:

```
cd SeriousSamClassic-VK
mkdir build
cd build
cmake ..
make -j4
make install
```

Flatpak
-------
[![Serious Sam Classic Vulkan on flathub](https://flathub.org/api/badge?locale=en)](https://flathub.org/apps/io.itch.tx00100xt.SeriousSamClassic-VK)   
You can also install the game using flatpak from the flathub repository. When you first start the game,  
you will be asked to place your game data along the following paths:
```
~/.var/app/io.itch.tx00100xt.SeriousSamClassic-VK/data/Serious-Engine/serioussam
```
```
~/.var/app/io.itch.tx00100xt.SeriousSamClassic-VK/data/Serious-Engine/serioussamse
```
You can place game data in these paths before starting the game. Then the game will start immediately.  
To start the game, use the application menu. More detailed information about flatpak on the [SeriousSamClassic-VK Flatpak wiki.](https://github.com/tx00100xt/SeriousSamClassic-VK/wiki/Flatpak.md)

Snap
----
[![Get it from the Snap Store](https://snapcraft.io/static/images/badges/en/snap-store-black.svg)](https://snapcraft.io/serioussam-vk)   
You can also install the game using snap from the snapcraft. When you first start the game,  
you will be asked to place your game data along the following paths:
```
~/snap/serioussam-vk/current/.local/share/Serious-Engine/serioussam
```
```
~/snap/serioussam-vk/current/.local/share/Serious-Engine/serioussamse
```
You can place game data in these paths before starting the game. Then the game will start immediately.  
To start the game, use the application menu. More detailed information about snap on the [SeriousSamClassic-VK Snap wiki.](https://github.com/tx00100xt/SeriousSamClassic-VK/wiki/Snap.md)

AppImage
--------
[![Get Appimage](https://raw.githubusercontent.com/srevinsaju/get-appimage/master/static/badges/get-appimage-branding-blue.png)](https://github.com/tx00100xt/SeriousSamClassic-VK/releases/tag/1.10.6d)
   
You can also run the game using AppImage. When you first start the game,  
you will be asked to place your game data along the following paths:
```
~/.local/share/Serious-Engine/serioussam
```
```
~/.local/share/Serious-Engine/serioussamse
```
You can place game data in these paths before starting the game. Then the game will start immediately.  
You can also place your game data anywhere in your home directory. The first time you start the game, it will find it itself.
AppImage also contains libraries for the modification of XPLUS. Download:
```
wget https://archive.org/download/sam-tfe-xplus/SamTFE-XPLUS.tar.xz
wget https://archive.org/download/sam-tse-xplus/SamTSE-XPLUS.tar.xz
```
And unpack it to the root directory of game resources. After unpacking the archives for the XPLUS mod, simply select this mod in the game menu.
You can build your AppImage using the build script. Type this in your terminal:
```
./build-appimage.sh
```

Build only the OpenGL version
-----------------------------
### Note:  
By default, the game uses the Vulkan renderer.If the Vulkan is not  
detected when the game starts, the game switches to OpenGL rendering.  
The default rendering value is set by the **sam_iGfxAPI** variable ( **0 - OpenGL / 1 - Vulkan** ).  
This variable can be set to zero in the configuration file, then OpenGL rendering to be used by default.  
The configuration file is located on the path:
```
~/.local/share/Serious-Engine/serioussam(se)/Scripts/PersistentSymbols.ini
```
This file is created after first launch.To change the default rendering to OpenGL,   
you need to change the **sam_iGfxAPI** value to **zero**  
or write the line: **persistent extern INDEX sam_iGfxAPI=(INDEX)0;** in this file.   

If your video card does not support Vulkan and you do not have the Vulkan libraries  
and header files installed, then you can build a version only with an OpenGL render.  
You just need to add one key(**-DUSE_SYSTEM_VULKAN=FALSE**) for the cmake command. Example:

```
cd SeriousSamClassic-VK
mkdir build
cd build
cmake -DUSE_SYSTEM_VULKAN=FALSE ..
make -j4
make install
```

Running
-------

You can buy the original games on Steam, as a part of a bundle with Serious Sam Revolution ( http://store.steampowered.com/app/227780 )

## Serious Sam Classic The First Encounter

### Running the game

1. Locate the game directory for "Serious Sam Classic The First Encounter" ([steam](https://store.steampowered.com/app/41050/Serious_Sam_Classic_The_First_Encounter/))
2. Build game from source code or [Download latest release](https://github.com/tx00100xt/SeriousSamClassic-VK/releases) and copy the latest files from the game directory to SamTFE/Bin
3. Copy all *.gro files, Help folder and Levels folder from the game directory to SamTFE directory.
   At the current time the files are:
   * Help (folder)
   * Levels (folder)
   * 1_00_ExtraTools.gro
   * 1_00_music.gro
   * 1_00c.gro
   * 1_00c_Logo.gro
   * 1_00c_scripts.gro
   * 1_04_patch.gro
4. Start the game
   * ./run_game.sh or ./run_game_hud.sh (for start game with MangoHUD)

## Serious Sam Classic The Second Encounter

### Running the game

1. Locate the game directory for "Serious Sam Classic The Second Encounter" ([steam](https://store.steampowered.com/app/41060/Serious_Sam_Classic_The_Second_Encounter/))
2. Build game from source code or [Download latest release](https://github.com/tx00100xt/SeriousSamClassic-VK/releases) and copy the latest files from the game directory to SamTSE/Bin
3. Copy all *.gro files and Help folder from the game directory to SamTSE directory.
   At the current time the files are:
   * Help (folder)
   * SE1_00.gro
   * SE1_00_Extra.gro
   * SE1_00_ExtraTools.gro
   * SE1_00_Levels.gro
   * SE1_00_Logo.gro
   * SE1_00_Music.gro
   * 1_04_patch.gro
   * 1_07_tools.gro
4. Start the game
   * ./run_game.sh or ./run_game_hud.sh (for start game with MangoHUD)

## Install the game in system (/usr/bin;/usr/lib/;/usr/share)

1. Just add string for cmake command:
```
cmake -DCMAKE_INSTALL_PREFIX:PATH=/usr 
```
2. Build game from source code.
3. Install the game: 
```
cd build
sudo make install
```
4.   Put game data in (Recommended):
```
/usr/share/serioussam/ - for TFE
/usr/share/serioussamse/ - for TSE
```
or
```
~/.local/share/Serious-Engine/serioussam/ - for TFE
~/.local/share/Serious-Engine/serioussamse/ - for TSE
```
6. Type in console:
```
serioussam       	# for run Serious Sam Classic The First Encounter
```
  or
```
serioussamse       	# for run Serious Sam Classic The Second Encounter
```
**Note:** If the game does not find the data on the recommended paths, then it will independently perform a search.
Please note that when installing the game on a system, all content of the original game is required (including directories: Controls, Data, Demos, Help, and so on) in directories **/usr/share/serioussam(se)** or **~/.local/share/Serious-Engine/serioussam(se)**, depending on the directory you select.
You can see a more detailed description in the [Wiki](https://github.com/tx00100xt/SeriousSamClassic-VK/wiki/How-to-building-a-package-for-Debian-or-Ubuntu.md#game-resources).

## Serious Sam Classic XPLUS

What is XPLUS?
XPLUS is a global modification that changes effects, models, weapons, textures to high definition. XPLUS was created by fans of the game Serious Sam and is distributed for free.
Remark: -JD- and VITEK is author this mod for windows.

![XPLUS Oasis](https://raw.githubusercontent.com/tx00100xt/SeriousSamClassic-VK/main/Images/samxplus_1.png)

![XPLUS Dunes](https://raw.githubusercontent.com/tx00100xt/SeriousSamClassic-VK/main/Images/samxplus_2.png)

![XPLUS Sacred Yards](https://raw.githubusercontent.com/tx00100xt/SeriousSamClassic-VK/main/Images/samxplus_3.png)

### Linux, FreeBSD, macOS, Raspberry PI OS

#### Building XPLUS (for SS:TFE and SS:TSE)

Type this in your terminal:

```
cd SeriousSamClassic-VK
mkdir build-xplus
cd build-xplus
cmake -DXPLUS=TRUE ..
make -j4
make install
```
Note: for Raspberry Pi4 just add **-DRPI4=TRUE** for cmake command.

Download:
[Xplus TFE from Google Drive] or [Xplus TFE from pCloud], and unpack to  SeriousSamClassic-VK/SamTFE/Mods directory.
[Xplus TSE from Google Drive] or [Xplus TSE from pCloud],, and unpack to  SeriousSamClassic-VK/SamTSE/Mods directory.
You can also download the archive using curl or wget:
```
cd SeriousSamClassic-VK
wget https://archive.org/download/sam-tfe-xplus/SamTFE-XPLUS.tar.xz
wget https://archive.org/download/sam-tse-xplus/SamTSE-XPLUS.tar.xz
tar -xJvpf SamTFE-XPLUS.tar.xz -C SamTFE
tar -xJvpf SamTSE-XPLUS.tar.xz -C SamTSE
```
or
```
cd SeriousSamClassic-VK
for var in a b c; do wget https://github.com/tx00100xt/serioussam-mods/raw/main/SamTFE-XPLUS/SamTFE-XPLUS.tar.xz.parta$var; done; cat SamTFE-XPLUS.tar.xz.part* > SamTFE-XPLUS.tar.xz
for var in a b c; do wget https://github.com/tx00100xt/serioussam-mods/raw/main/SamTSE-XPLUS/SamTSE-XPLUS.tar.xz.parta$var; done; cat SamTSE-XPLUS.tar.xz.part* > SamTSE-XPLUS.tar.xz
tar -xJvpf SamTFE-XPLUS.tar.xz -C SamTFE
tar -xJvpf SamTSE-XPLUS.tar.xz -C SamTSE
```
To start the modification, use the game menu - item Modification.

Building demo version of the game
---------------------------------
To build the demo version of the game, official demo files for Windows and official patches for the game from Croteam are used. 
These files are automatically downloaded and unpacked in demo build scripts.

Type this in your terminal:

```
git clone https://github.com/tx00100xt/SeriousSamClassic-VK.git SeriousSamClassic-VK
cd SeriousSamClassic-VK
./build-linux64demo.sh        	    # use build-linux32demo.sh for 32-bits
```

Windows
-------
* This project can be compiled starting from Windows 7 and higher.

1. Download and Install [Vulkan SDK 1.3.204.1] or higher.
2. Download and Install [Visual Studio 2015 Community Edition] or higher.
3. Download and Install [Windows 10 SDK 10.0.14393.795] or other.
4. Open the solution in the Sources folder, select Release x64 or Release Win32 and compile it.

Supported Architectures
----------------------
* `x86`
* `aarch64`
* `e2k` (elbrus)

Supported OS
-----------
* `Linux`
* `FreeBSD`
* `OpenBSD`
* `Windows`
* `Raspberry PI OS`
* `macOS`

### Build status
|CI|Platform|Compiler|Configurations|Platforms|Status|
|---|---|---|---|---|---|
|GitHub Actions|Windows, Ubuntu, FreeBSD, Alpine, Raspberry PI OS Lite, macOS|MSVC, GCC, Clang|Release|x86, x64, armv7l, aarch64, riscv64, ppc64le, s390x, mipsel, loongarch64|![GitHub Actions Build Status](https://github.com/tx00100xt/SeriousSamClassic-VK/actions/workflows/cibuild.yml/badge.svg)

You can download a the automatically build based on the latest commit.  
To do this, go to the [Actions tab], select the top workflows, and then Artifacts.

License
-------

* Serious Engine is licensed under the GNU GPL v2 (see LICENSE file).
* amp11lib is licensed under the GNU GPL v2 (see amp11lib/COPYING file).

### Note:
The following applies only to the for Windows build. Because none of the following is used when building under (Linux, *BSD, macOS) systems.
<pre>

Some of the code included with the engine sources is not licensed under the GNU GPL v2:
</pre>

* zlib (located in `Sources/Engine/zlib`) by Jean-loup Gailly and Mark Adler
* LightWave SDK (located in `Sources/LWSkaExporter/SDK`) by NewTek Inc.
* libogg/libvorbis (located in `Sources/libogg` and `Sources/libvorbis`) by Xiph.Org Foundation

[io.itch.tx00100xt.SeriousSamClassic-VK]: https://flathub.org/en-GB/apps/io.itch.tx00100xt.SeriousSamClassic-VK "Serious Sam Classic with Vulkan support on flathub"
[Xplus TFE from Google Drive]: https://drive.google.com/file/d/1MPmibfMCGTWFBSGeFWG3uae0zZzJpiKy/view?usp=sharing "Serious Sam Classic XPLUS Mod"
[Xplus TSE from Google Drive]: https://drive.google.com/file/d/1W_UIeVl7y3ZBroM39FmKdngNZuXC7DKv/view?usp=sharing "Serious Sam Classic XPLUS Mod"
[Xplus TFE from pCloud]: https://e1.pcloud.link/publink/show?code=XZ02gRZ4nhrRGPSfV4aEL4IF8GYySafWVJX "Serious Sam Classic XPLUS Mod"
[Xplus TSE from pCloud]: https://e1.pcloud.link/publink/show?code=XZy2gRZ3D7n8fu83SkhIdB1xRaK7y9pKiry "Serious Sam Classic XPLUS Mod"
[Vulkan SDK 1.3.204.1]: https://sdk.lunarg.com/sdk/download/1.3.204.1/windows/VulkanSDK-1.3.204.1-Installer.exe "Vulkan SDK 1.3.204.1"
[Visual Studio 2015 Community Edition]: https://go.microsoft.com/fwlink/?LinkId=615448&clcid=0x409 "Visual Studio 2015 Community Edition"
[Windows 10 SDK 10.0.14393.795]: https://go.microsoft.com/fwlink/p/?LinkId=838916 "Windows 10 SDK 10.0.14393.795"
[Actions tab]: https://github.com/tx00100xt//SeriousSamClassic-VK/actions "Download Artifacts"
