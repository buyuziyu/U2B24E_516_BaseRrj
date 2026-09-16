/*
                        Low-Level System Library

            Copyright 2007-2014 Green Hills Software, Inc.

    This program is the property of Green Hills Software, Inc,
    its contents are proprietary information and no part of it
    is to be disclosed to anyone except employees of Green Hills
    Software, Inc., or as agreed in writing signed by the President
    of Green Hills Software, Inc.
*/

#include "ind_thrd.h"
#include <stddef.h>
#include <setjmp.h>

/* IMPORTANT: If you customize or replace __ghsLock and __ghsUnlock, then
 * delete the following symbol definition. The symbol __ghs_single_threaded
 * signals to other parts of the libraries that it is safe to omit
 * locking/synchronization code. */
#pragma weak __ghs_single_threaded
char __ghs_single_threaded = 1;

/* Acquire global lock.  Blocks until the lock becomes available. */
void __ghsLock(void)
{
}

/* Release global lock */
void __ghsUnlock(void)
{
}

/* A callback to initialize the lock data structure before it is used. */
void __gh_lock_init(void)
{
}

