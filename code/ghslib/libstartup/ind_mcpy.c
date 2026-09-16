/*
                      Low-Level Startup Library

            Copyright 1983-2017 Green Hills Software, Inc.

    This program is the property of Green Hills Software, Inc,
    its contents are proprietary information and no part of it
    is to be disclosed to anyone except employees of Green Hills
    Software, Inc., or as agreed in writing signed by the President
    of Green Hills Software, Inc.
*/

#include "ind_startup.h"
#include "indlibvariant.h"

#if defined(__GHS_SAFE_ALTERNATE_COMPILE)
#define memcpy __ghs_variant1__memfuncs__safe__memcpy
#pragma ghs alias __ghs_safe_memcpy __ghs_variant1__memfuncs__safe__memcpy
char __ghs_variant1__memfuncs__safe____ghs_forward_memcpy = 0;
#endif

#if defined(__i386__) && defined(__x86_64__) && !defined(__GHS_SAFE_ALTERNATE_COMPILE)
/* For 64-bit x86, use this hand-optimized assembly implementation. This
 * implementation isn't written to work on 32-bit x86, so can't just be listed
 * in ind_mcpy.gpj. */
#if !defined(__linux)
#pragma ghs static_call 0
#pragma ghs max_stack   0
#endif
void *(memcpy)(void *s1, const void *s2, size_t n);
#pragma asm
#include "ind_mcpy.86"
#pragma endasm
#else

/* The C version of memcpy doesn't have SIMD code, so it isn't built when
 * __GHS_SIMD_ALTERNATE_COMPILE is defined. */
#if !defined(__GHS_SIMD_ALTERNATE_COMPILE)

#include <stdint.h>

typedef unsigned long ulong;
typedef unsigned char uchar;

// The following implementation of memcpy is organized as follows:
//    1.  Align the destination pointer by copying a byte at a time
//    2a. If both pointers are aligned, do a copy word-by-word
//    2b. If the pointers are not relatively aligned, align the source
//        pointer and copy word-by-word, stitching together source loads
//        to store into the dest pointer
//    3.  Copy the remaining bytes, a byte at a time (this will be at most
//        sizeof(ulong)-1 bytes (2a) or (2 * sizeof(ulong))-1 bytes (2b)
//
// Some additional features of this version:
//    1. At most 3*(sizeof(long)-1) byte copies will be performed.  This is
//       important, since a naive solution might default to byte-by-byte copies
//       for difficultly aligned cases, meaning the difference between an
//       aligned copy and a misaligned copy can be 8 times the number of
//       load/stores on 64-bit architectures.
//    2. No memory past the end of the source or dest buffer is read/written.
//       This is useful for memory mapped I/O which may have unexpected
//       sideeffects if adjacent memory is read/written.
//    3. No memory is read or written twice.
//    4. No misaligned accesses are used.
//    5. Copies are performed in an ascending manner.
//    6. No SIMD or floating point types are used.
void *(memcpy)(void *s1, const void *s2, size_t n)
{
    void *result = s1;

    // Align the destination pointer
    uchar       *cp1 = (uchar *)s1;
    const uchar *cp2 = (const uchar *)s2;
    while (n > 0 && (((uintptr_t)cp1) & (sizeof(ulong)-1))) {
	*cp1 = *cp2;
	++cp1;
	++cp2;
	--n;
    }
    
    // Copy the middle portion
    if (n >= sizeof(ulong)) {
	ulong *lp1 = (ulong *)cp1;

	// Check if cp2 is aligned
	if (((uintptr_t)cp2) & (sizeof(ulong)-1)) {
	    // cp2 is not aligned - perform two aligned loads and shift the
	    // bits together

	    // Since there are at least sizeof(long) bytes left, we can always
	    // copy from cp2 until we get to an aligned address
	    int          shift  = 0;
	    int          shift1 = 0;
	    ulong        temp1  = 0;
	    const ulong *lp2    = 0;
	    const uchar *cp2t   = cp2;
	    while (((uintptr_t)cp2t) & (sizeof(ulong)-1)) {
#ifdef __BIG_ENDIAN__
		temp1 = (temp1<<8) | *cp2t;
#else
		temp1 = temp1 | ((ulong)(*cp2t) << shift);
#endif
		++cp2t;
		shift += 8;
	    }

	    // Copy in the aligned portion
	    shift1 = (8*sizeof(ulong))-shift;
	    lp2 = (const ulong *)cp2t;
	    while (n >= (2*sizeof(ulong))) {
		ulong temp2 = *lp2;
#ifdef __BIG_ENDIAN__
		*lp1 = (temp1 << shift1) | (temp2 >> shift);
		temp1 = temp2;
#else
		*lp1 = temp1 | (temp2 << shift);
		temp1 = temp2 >> shift1;
#endif
		n -= sizeof(ulong);
		++lp1;
		++lp2;
	    }

	    // Copy the remaining bytes read into temp2
	    cp1 = (uchar *)lp1;
	    while (shift) {
#ifdef __BIG_ENDIAN__
		*cp1 = (uchar)(temp1 >> (shift-8));
		++cp1;
#else
		*cp1 = (uchar)temp1;
		++cp1;
		temp1 = temp1 >> 8;
#endif
		shift -= 8;
		--n;
	    }
	    cp2 = (uchar *)lp2;
	} else {
	    // If cp2 is aligned, do a long-by-long copy
	    const ulong *lp2 = (const ulong *)cp2;
	    while (n >= sizeof(ulong)) {
		*lp1 = *lp2;
		++lp1;
		++lp2;
		n -= sizeof(ulong);
	    }
	    cp1 = (uchar *)lp1;
	    cp2 = (const uchar *)lp2;
	}
    }

    // Copy the remaining portion
    while (n > 0) {
	*cp1 = *cp2;
	++cp1;
	++cp2;
	--n;
    }

    return result;
}

#endif /* !defined(__GHS_SIMD_ALTERNATE_COMPILE) */
#endif /* defined(__i386__) && defined(__x86_64__) */
