PORTNAME=	serioussam-vk
DISTNAME=	SeriousSamClassic-VK
DISTVERSION=	1.10.6c
PORTREVISION=	1
CATEGORIES=	games

MAINTAINER= 	YOUR@MAIL
COMMENT=	Serious Sam Classic is open source game engine with vulkan support
WWW=		https://github.com/tx00100xt/SeriousSamClassic-VK

LICENSE= 	GPLv2
LICENSE_FILE= 	${WRKSRC}/LICENSE

# The source code also contains definitions for
# architectures riscv64 s390x powerpc64le.
# Building code for them workd.
# Work on real hardware has been 
# tested for architectures: armv7 aaarch64 under Linux
ONLY_FOR_ARCHS= amd64 i386

BUILD_DEPENDS=	flex:textproc/flex \
		vulkan-headers>0:graphics/vulkan-headers \
		convert:graphics/ImageMagick7

# Libraries loaded with dlopen(3)
LIB_DEPENDS=	libogg.so:audio/libogg \
		libvorbis.so:audio/libvorbis \
		libvorbisfile.so:audio/libvorbis \
		libvulkan.so:graphics/vulkan-loader

USES=		bison:build cmake compiler:c++11-lang sdl desktop-file-utils
USE_CXXSTD=	c++14
USE_SDL=	sdl2

CONFLICTS=	serioussam

GH_ACCOUNT=	tx00100xt
GH_PROJECT=	SeriousSamClassic-VK
USE_GITHUB=	yes

CMAKE_ARGS=	-DRPI4:BOOL=FALSE -DUSE_ASM:BOOL=FALSE \
	-DUSE_SYSTEM_INSTALL:BOOL=TRUE -DUSE_I386_NASM_ASM:BOOL=FALSE

post-install:
	${INSTALL_MAN} ${WRKSRC}/man/bsd/serioussam-vk.1 ${STAGEDIR}${PREFIX}/man/man1/serioussam-vk.1
	${INSTALL_MAN} ${WRKSRC}/man/bsd/serioussamclassic-vk.1 ${STAGEDIR}${PREFIX}/man/man1/serioussamclassic-vk.1

.include <bsd.port.options.mk>

.if ${ARCH} == amd64
CMAKE_ON=	USE_ASM
.endif

# Unocmment this for aarch64 and armv7 architectures
#.if ${ARCH} == aarch64 || ${ARCH} == armv7
#CMAKE_ON=	RPI4
#.endif

.include	<bsd.port.mk>
