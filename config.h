/* config.h.  Generated from config.h.in by configure.  */
/* config.h.in.  Generated from configure.ac by autoheader.  */

/* Build the Wayland clients */
#define BUILD_CLIENTS 1

/* Build the DRM compositor */
#define BUILD_DRM_COMPOSITOR 1

/* Build the fbdev compositor */
#define BUILD_FBDEV_COMPOSITOR 1

/* Build the headless compositor */
#define BUILD_HEADLESS_COMPOSITOR 1

/* Build the RDP compositor */
#define BUILD_RDP_COMPOSITOR 1

/* Build the compositor for Raspberry Pi */
#define BUILD_RPI_COMPOSITOR 1

/* Build the vaapi recorder */
#define BUILD_VAAPI_RECORDER 1

/* Build the Wayland (nested) compositor */
#define BUILD_WAYLAND_COMPOSITOR 1

/* Build the wcap tools */
#define BUILD_WCAP_TOOLS 1

/* Build the X11 compositor */
#define BUILD_X11_COMPOSITOR 1

/* Build the X server launcher */
#define BUILD_XWAYLAND 1

/* Build Weston with EGL support */
#define ENABLE_EGL 1

/* Build Weston with libxkbcommon support */
#define ENABLE_XKBCOMMON 1

/* have Raspberry Pi BCM headers */
/* #undef HAVE_BCM_HOST */

/* Have cairo-egl */
/* #undef HAVE_CAIRO_EGL */

/* Build with dbus support */
#define HAVE_DBUS 1

/* Define to 1 if you have the <dlfcn.h> header file. */
#define HAVE_DLFCN_H 1

/* Define to 1 if you have the <execinfo.h> header file. */
#define HAVE_EXECINFO_H 1

/* Define to 1 if you have the <freerdp/version.h> header file. */
/* #undef HAVE_FREERDP_VERSION_H */

/* Define to 1 if you have the `initgroups' function. */
#define HAVE_INITGROUPS 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Have lcms support */
/* #undef HAVE_LCMS */

/* Define if libdrm is available */
#define HAVE_LIBDRM 1

/* Have libunwind support */
/* #undef HAVE_LIBUNWIND */

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have the `mkostemp' function. */
#define HAVE_MKOSTEMP 1

/* Define to 1 if you have the `posix_fallocate' function. */
#define HAVE_POSIX_FALLOCATE 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the `strchrnul' function. */
#define HAVE_STRCHRNUL 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Have systemd-login */
/* #undef HAVE_SYSTEMD_LOGIN */

/* Have systemd-login >= 209 */
/* #undef HAVE_SYSTEMD_LOGIN_209 */

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Have webp */
/* #undef HAVE_WEBP */

/* Define to 1 if you have the `xcb_poll_for_queued_event' function. */
#define HAVE_XCB_POLL_FOR_QUEUED_EVENT 1

/* libxcb supports XKB protocol */
/* #undef HAVE_XCB_XKB */

/* Define to the sub-directory in which libtool stores uninstalled libraries.
   */
#define LT_OBJDIR ".libs/"

/* Name of package */
#define PACKAGE "weston"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "https://bugs.freedesktop.org/enter_bug.cgi?product=Wayland&component=weston&version=1.8.0"

/* Define to the full name of this package. */
#define PACKAGE_NAME "weston"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "weston 1.8.0"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "weston"

/* Define to the home page for this package. */
#define PACKAGE_URL "http://wayland.freedesktop.org"

/* Define to the version of this package. */
#define PACKAGE_VERSION "1.8.0"

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Use the GLESv2 GL cairo backend */
/* #undef USE_CAIRO_GLESV2 */

/* Use resize memory pool as a performance optimization */
#define USE_RESIZE_POOL 1

/* Enable extensions on AIX 3, Interix.  */
#ifndef _ALL_SOURCE
# define _ALL_SOURCE 1
#endif
/* Enable GNU extensions on systems that have them.  */
#ifndef _GNU_SOURCE
# define _GNU_SOURCE 1
#endif
/* Enable threading extensions on Solaris.  */
#ifndef _POSIX_PTHREAD_SEMANTICS
# define _POSIX_PTHREAD_SEMANTICS 1
#endif
/* Enable extensions on HP NonStop.  */
#ifndef _TANDEM_SOURCE
# define _TANDEM_SOURCE 1
#endif
/* Enable general extensions on Solaris.  */
#ifndef __EXTENSIONS__
# define __EXTENSIONS__ 1
#endif


/* Version number of package */
#define VERSION "1.8.0"

/* The default backend to load, if not wayland nor x11. */
#define WESTON_NATIVE_BACKEND "drm-backend.so"

/* The default desktop shell client to load. */
#define WESTON_SHELL_CLIENT "weston-desktop-shell"

/* Enable large inode numbers on Mac OS X 10.5.  */
#ifndef _DARWIN_USE_64_BIT_INODE
# define _DARWIN_USE_64_BIT_INODE 1
#endif

/* Number of bits in a file offset, on hosts where this is settable. */
/* #undef _FILE_OFFSET_BITS */

/* Define for large files, on AIX-style hosts. */
/* #undef _LARGE_FILES */

/* Define to 1 if on MINIX. */
/* #undef _MINIX */

/* Define to 2 if the system does not provide POSIX.1 features except with
   this defined. */
/* #undef _POSIX_1_SOURCE */

/* Define to 1 if you need to in order for `stat' and other things to work. */
/* #undef _POSIX_SOURCE */
