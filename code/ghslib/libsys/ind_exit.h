/*
                        Low-Level System Library

            Copyright 1983-2014 Green Hills Software, Inc.

    This program is the property of Green Hills Software, Inc,
    its contents are proprietary information and no part of it
    is to be disclosed to anyone except employees of Green Hills
    Software, Inc., or as agreed in writing signed by the President
    of Green Hills Software, Inc.
*/
/* ind_exit.h: declarations for callers of ind_exit.c */

/*   FUNCTIONS ALWAYS NEEDED TO RUN PROGRAMS COMPILED WITH THE DEFAULT CRT0   */

#ifdef __cplusplus
extern "C" {
#endif

typedef __attribute__((strong_fptr)) void (*__ghs_at_exit_fptr)(void);

struct __GHS_AT_EXIT {
    __ghs_at_exit_fptr func;
    struct __GHS_AT_EXIT *next;
};

#if defined(__cplusplus) && (__cplusplus >= 201103L) && \
    defined(__EXCEPTION_HANDLING) && \
    !(defined(__GHS_ACT_LIKE) && __GHS_ACT_LIKE < 201550)
#define __CXX11_NOEXCEPT noexcept
#else
#define __CXX11_NOEXCEPT
#endif

void _Exit(int __VAL) __CXX11_NOEXCEPT __attribute__((__noreturn__));
void __ghs_at_exit (struct __GHS_AT_EXIT *gae);

#ifdef __cplusplus
}
#endif
