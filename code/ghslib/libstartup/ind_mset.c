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
#define memset __ghs_variant1__memfuncs__safe__memset
#pragma ghs alias __ghs_safe_memset __ghs_variant1__memfuncs__safe__memset
#endif

#if defined(__i386__) && defined(__x86_64__) && !defined(__GHS_SAFE_ALTERNATE_COMPILE)
/* For 64-bit x86, use this hand-optimized assembly implementation. This
 * implementation isn't written to work on 32-bit x86, so can't just be listed
 * in ind_mset.gpj. */
#if !defined(__linux)
#pragma ghs static_call 0
#pragma ghs max_stack   0
#endif
void *(memset)(void *s, int c, size_t n);
#pragma asm
#include "ind_mset.86"
#pragma endasm
#else

/* The C version of memset doesn't have SIMD code, so it isn't built when
 * __GHS_SIMD_ALTERNATE_COMPILE is defined. */
#if !defined(__GHS_SIMD_ALTERNATE_COMPILE)

/* Unrolled memset loop, using up to 16-byte alignment */
/* This routine is used by gprof and crt0.o */
/* Only POWER values of 4 and 5 are supported. */
#define POWER	4
#define LOOP	(1<<POWER)

void *(memset)(void *s, int c, size_t n) {
    register unsigned char *pt=s;
    unsigned char ch=c; 

    if (n > 2*LOOP) {
	/* we have at least one aligned 16-byte block */
	register size_t i;
	register int ch4;
	struct quad { int b1,b2,b3,b4; };

	/* Compute repeated char value */
	ch4 = ch;
	ch4 <<= 8;
	ch4 |= ch;
	ch4 = (ch4 << 16 | ch4);

	if ((i = ((size_t)pt & (LOOP-1))) != 0) {
	    i = LOOP - i;		/* i is bytes before the blocks */
	    n -= i;			/* n is bytes in blocks and after blocks */
	    do {
		*pt = ch;
		pt++;
	    } while (--i);
	}

	/* we are now at a block boundary. */
	i = n >> POWER;		/* i is number of blocks */
	n &= LOOP-1;		/* n is bytes after the block */

	{
#ifdef USE_STRUCT16
	    register struct quad ch16;
	    ch16.b1=ch4; ch16.b2=ch4; ch16.b3=ch4; ch16.b4=ch4;
#endif
	    do {
#ifdef USE_STRUCT16
		((struct quad*)pt)[0] = ch16;
		((struct quad*)pt)[1] = ch16;
		pt += 2 * sizeof(struct quad);
#else
		((struct quad*)pt)[0].b1 = ch4;
		((struct quad*)pt)[0].b2 = ch4;
		((struct quad*)pt)[0].b3 = ch4;
		((struct quad*)pt)[0].b4 = ch4;
# if POWER == 4
		pt += sizeof(struct quad);
# elif POWER == 5
		((struct quad*)pt)[1].b1 = ch4;
		((struct quad*)pt)[1].b2 = ch4;
		((struct quad*)pt)[1].b3 = ch4;
		((struct quad*)pt)[1].b4 = ch4;
		pt += 2 * sizeof(struct quad);
# endif
#endif
	    } while (--i);
	}
    }
    if (n) {	/* n is bytes after the blocks */
	do {
	    *pt = ch;
	    pt++;
	} while ( --n );
    }
    return(s);
}

#endif /* !defined(__GHS_SIMD_ALTERNATE_COMPILE) */
#endif /* defined(__i386__) && defined(__x86_64__) */
