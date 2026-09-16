/*
                        Low-Level System Library

            Copyright 2019 Green Hills Software, Inc.

    This program is the property of Green Hills Software, Inc,
    its contents are proprietary information and no part of it
    is to be disclosed to anyone except employees of Green Hills
    Software, Inc., or as agreed in writing signed by the President
    of Green Hills Software, Inc.
*/

#include <limits.h>
#include <stdio.h>

/* This file is used to override the value of FOPEN_MAX used by the libraries.
 * To do that, build this file with -D__GHS_OVERRIDE_FOPEN_MAX=<N> (where <N>
 * is the desired value of FOPEN_MAX) and link it into your application.
 *   - On standalone, this can be done by simply rebuilding libsys with that
 *     option passed.
 *   - On INTEGRITY, you must add this file to your application manually.
 */

#if !defined(__GHS_OVERRIDE_FOPEN_MAX)
#  error "Must define __GHS_OVERRIDE_FOPEN_MAX to use this file."
#endif

/* The first 3 FILEs are defined in stdio.h itself. Can't reduce FOPEN_MAX
 * below that. */
#if __GHS_OVERRIDE_FOPEN_MAX < 3
#  error "__GHS_OVERRIDE_FOPEN_MAX too small."
#endif

#if __GHS_OVERRIDE_FOPEN_MAX > USHRT_MAX - 1
#  error "__GHS_OVERRIDE_FOPEN_MAX too large."
#endif

#if defined(__UVELOSITY)
#  error "Not supported on u-velOSity."
#endif

/* Not defined in library builds, but is defined when this file is added to an
 * INTEGRITY project. */
#if defined(__INTEGRITY)
#  include <INTEGRITY_version.h>
#  if defined(INTEGRITY_IoT)
#    if   INTEGRITY_IoT_MAJOR_VERSION <  2019 || \
         (INTEGRITY_IoT_MAJOR_VERSION == 2019 && \
          INTEGRITY_IoT_MINOR_VERSION < 22)
#      error "Not supported on INTEGRITY IoT prior to version 2019.22.x"
#    else
       /* Ensure we're including the INTEGRITY ind_io.h, not the one in libsys.
        */
#      include "../INTEGRITY-include-full/ind_io.h"
#      define __GHS_NEED_FILE_LOCKS_ARRAY
#    endif
#  endif
#endif

/* Ensure these arrays aren't put in SDA or ZDA. */
#pragma ghs startdata

/* Communicate to the libraries how many files to allow. */
unsigned short __gh_FOPEN_MAX = __GHS_OVERRIDE_FOPEN_MAX;

/* Provide strong definitions of all arrays whose sizes depend on FOPEN_MAX.
 * These override the weak definitions provided elsewhere in the libraries. */

struct _iobuf _iob     [__GHS_OVERRIDE_FOPEN_MAX];
void *        _iob_lock[__GHS_OVERRIDE_FOPEN_MAX + 1];

size_t __gh_buffersizes[__GHS_OVERRIDE_FOPEN_MAX];

/* Used by the wide character I/O functions. */
signed char __gh_wide_orientation[__GHS_OVERRIDE_FOPEN_MAX];

/* Used by tmpfile() to delete files on close. */
char           __gh_del_names[__GHS_OVERRIDE_FOPEN_MAX][L_tmpnam];
unsigned short __gh_del_index[__GHS_OVERRIDE_FOPEN_MAX];

/* Used to track which FILEs are currently associated with an underlying file.
 * Must reserve the 3 standard streams statically. */
unsigned char __gh_file_reservations[__GHS_OVERRIDE_FOPEN_MAX] = {1, 1, 1};

/* Additional pushback space needed for ungetwc. */
unsigned char __gh_file_pushback[__GHS_OVERRIDE_FOPEN_MAX][2*MB_LEN_MAX];

/* Contains the actual file lock structs on INTEGRITY IoT. */
#if defined(__GHS_NEED_FILE_LOCKS_ARRAY)
LibraryLock __ghs_file_locks[__GHS_OVERRIDE_FOPEN_MAX];
#endif

/* This symbol is used to verify that, if FOPEN_MAX is overridden, the stdio
 * arrays have also been replaced. If you see an error like "unresolved symbol:
 * __ghs_alternate_file_arrays_v2", it means you passed
 * -D__GHS_OVERRIDE_FOPEN_MAX but didn't include this file in your project (or
 * included an older version of it). */
char __ghs_alternate_file_arrays_v2 = 1;

#pragma ghs enddata
