# The source code also contains definitions for
# architectures riscv64 s390x powerpc64le.
# Building code for them workd.
# Work on real hardware has been 
# tested for architectures: armv7 aaarch64 under Linux

ONLY_FOR_ARCHS =	amd64 i386

GH_ACCOUNT =		tx00100xt
GH_PROJECT =		SeriousSamClassic-VK
GH_TAGNAME =		1.10.6c

COMMENT =		Open source version Serious Sam Classic with vulkan support
N=			serioussam-vk
V=			1.10.6c
PKGNAME =		${N}-${V}
DISTNAME =		SeriousSamClassic-VK-${V}
CATEGORIES =		games
REVISION =		1

HOMEPAGE =		https://github.com/tx00100xt/SeriousSamClassic-VK

MAINTAINER =		YOUR NAME <YOUR MAIL>

# GPLv2
PERMIT_PACKAGE =	Yes

WANTLIB += ${COMPILER_LIBCXX} SDL2 c m z ogg \
			pthread vorbis vorbisfile
#			pthread vorbis vorbisfile vulkan

MODULES =		devel/cmake

COMPILER =		base-clang ports-gcc

CONFIGURE_ARGS +=	-DUSE_SYSTEM_INSTALL=ON

BUILD_DEPENDS =		devel/sdl2 \
			devel/bison \
			audio/libvorbis \
			audio/libogg \
			graphics/vulkan-headers \
			graphics/ImageMagick

# Libraries loaded with dlopen(3)
LIB_DEPENDS =		devel/sdl2 \
			audio/libvorbis \
			audio/libogg \
			graphics/vulkan-loader

NO_TEST =		Yes

# Unocmment this for aarch64 and armv7 architectures
#.if ${MACHINE_ARCH} == aarch64 || ${MACHINE_ARCH} == armv7
#CONFIGURE_ARGS +=	-DRPI4=ON
#.endif

.if ${MACHINE_ARCH}== i386 || ${MACHINE_ARCH}== amd64
CONFIGURE_ARGS +=	-DUSE_ASM=OFF
CXXFLAGS += -Wno-nullability-completeness
.endif

post-install:
	${INSTALL_MAN} ${WRKSRC}/man/bsd/serioussam-vk.1 ${PREFIX}/man/man1/serioussam-vk.1
	${INSTALL_MAN} ${WRKSRC}/man/bsd/serioussamclassic-vk.1 ${PREFIX}/man/man1/serioussamclassic-vk.1

.include	<bsd.port.mk>
