/*
                        Low-Level System Library

            Copyright 1983-2014 Green Hills Software, Inc.

    This program is the property of Green Hills Software, Inc,
    its contents are proprietary information and no part of it
    is to be disclosed to anyone except employees of Green Hills
    Software, Inc., or as agreed in writing signed by the President
    of Green Hills Software, Inc.
*/

/*
    The Green Hills Software Libraries have been ported to many versions of
    Unix and other target environments, each with their major and minor 
    differences and conflicts.

    Every attempt has been made to isolate these differences into indOS.c
    and a few other files.

    At present, the following target environments and flavors of Unix are
    understood:

    Only one of the following should ever be set:
	    BSD                            \
	    SOLARIS20                       \  imply ANYUNIX
	    SUNOS                           /
	    __linux			   /
	    ------------
	    EMBEDDED
	    MSDOS
	    __windows
	    __VXWORKS
    Variables in the first group are intended to represent various genuine
    Unix systems.  All of these imply the variable 'ANYUNIX', which is used
    to select the most generic features of Unix, such as directories with /
    and system calls like fork(), exec(), link() and unlink().
*/
#if defined(__INTEGRITY_SHARED_LIBS)
#   define	UN_BUFFERED_STD		1
#   define	VARIABLE_FILE_BUFFERS	1
#endif
/* 
 * VARIABLE_FILE_BUFFERS means that the size of buffer can be controlled
 * via setvbuf() and __gh_bufinit. It is orthogonal to LESS_BUFFERED_IO
 */

/*
    ANYBSD is any non-System V Unix system which provides these Bsd 4.3 calls:
	rename
	truncate
	gettimeofday
	vfork
	signal/kill
    and this library routine
	on_exit
*/

#ifdef __VXWORKS	/* vxWorks.h defines BSD */
#undef	BSD
#endif
#if defined(BSD) || defined(SUNOS)
#define		ANYBSD
#endif

/*	ANYSYSV4 is any Unix system that is based on Unix System V.4
	1.	the timezone interface is System V and not Bsd.
	2.	the stat struct is enlarged versus either V.3 or Bsd.
	3.	weak symbols are available
	4.	the C library is a full (and correct) Ansi C implementation
	5.	truncate exists
	6.	signals are System V style, not BSD style
*/
#if defined(SOLARIS20)
#define		ANYSYSV4
#endif

/*	ANYSYSV is any Unix system which is based on Unix System V.3 or V.4
	1.	the timezone interface is System V and not Bsd.
	2.	ANYSYSV is used with __m88k to distinguish OCS specific features
*/
#if defined(ANYSYSV4)
#define		ANYSYSV
#endif

/*	LIBCISANSI means a Unix system which has an Ansi compliant libc.a
	On such systems the driver will use libc.a instead of libind.a libansi.a
*/
#if (defined(ANYSYSV4) || defined(__VXWORKS) || \
     defined(__linux) || defined(__LYNX))
#define		LIBCISANSI
#endif

#define _______UnixCount	\
	defined(BSD) 		+ \
	defined(SOLARIS20)	+ \
	defined(SUNOS)		+ \
	defined(__linux)
#define _____OtherCount		\
	defined(EMBEDDED)	+ \
	defined(MSDOS)		+ \
	defined(__windows)	+ \
	defined(__VXWORKS)	

/* No targets appear to define SYSV, SYSV40, SUNOS, BSD, __LYNX, MSDOS */
#if defined(SYSV) || defined(SYSV40) || defined(SUNOS) || defined(BSD) \
 || defined(__LYNX) || defined(MSDOS)
#error unexpected define
#endif
/* Make EMBEDDED the default */
#if _______UnixCount + _____OtherCount == 0
#define EMBEDDED
#endif

/*  MINIMUM_SPACE uses more compact code which is more appropriate for embedded
    uses.  Often this means dropping code which is only there for Unix 
    compatibility, or which is only relevant when we might use our libansi with
    another vendor's libc.a
    LESS_BUFFERED_IO is a specific space-saving change that makes sense in 
    embedded uses, but actually works on Unix as well.  It is almost always used
    together with MINIMUM_SPACE.  stdin and stdout are unbuffered by default.
    To recover the benefits of buffering, functions like printf and fwrite
    create their own buffers and flush them before exiting.  Thus, a call to
    printf or fwrite will probably only call write() one more time than if
    full buffering was in use.  putc(), however, always calls write().
    Internally LESS_BUFFERED_IO means:
    _io_buffering is ignored, except for 2 uses of _IOPBF (fputs and printf)
    _io_stdio_buffer is never set because malloc is never called.
*/
#if defined(EMBEDDED) && !defined(__INTEGRITY_SHARED_LIBS)
#   define	MINIMUM_SPACE		1
#   define	NO_LOCALE_DECIMAL_POINT	1
#   if !defined(NO_LESS_BUFFERED_IO)
#     define	LESS_BUFFERED_IO	1
#   endif
#   define	NO_LINE_BUFFERING	1
#   define	VARIABLE_FILE_BUFFERS	1
#   define	NO_INITIALIZED_DATA	1
/* #   define	APPEND_MEANS_SEEK_BEFORE_WRITE 1 */
#endif

#if defined(EMBEDDED) && defined(__MLIBCALL)
#undef _______UnixCount
#undef _____OtherCount
#define _______UnixCount 0
#define _____OtherCount  1
#endif

#if _______UnixCount == 1
#define		ANYUNIX
#elif _______UnixCount > 1
#error		Too many Unix target environments defined
#endif

#if _____OtherCount > 1
#error		Too many non-Unix target environments defined
#elif (_____OtherCount == 1) && defined(ANYUNIX)
#error		Both Unix and non-Unix target environments defined
#endif

#if (_______UnixCount + _____OtherCount) == 0
#error		No target environment defined
#endif

#if defined(EMBEDDED)
# if !((defined(__MC68000) || defined(__ppc)) && defined(__COFF)) && !defined(NO_DYNAMIC_LIBS)
#  define DYNAMIC_FLOAT_PRINTF 1
#  define DYNAMIC_FLOAT_SCANF 1
# endif
# if !defined(NO_DYNAMIC_LIBS)
#  define DYNAMIC_EINT1_PRINTF 1
# endif
#endif
