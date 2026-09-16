/*
 *                          Copyright 2015                      
 *                         Green Hills Software                      
 *
 *    This program is the property of Green Hills Software.  Its
 *    contents constitute the proprietary information of Green Hills
 *    Software.  Your use of this program shall be in accordance with
 *    the shrink-wrap or click-through license agreement accompanying
 *    it or the executed license agreement by and between you or your
 *    company and Green Hills Software, which supersedes the former.
 *    If you have not agreed to the terms of a license agreement with
 *    Green Hills Software, do not use this program and promptly
 *    contact Green Hills Software.
 *
 */

/* This file includes stubs for implementing an interface for the C++ 11
 * multi-threading features in the <condition_variable> header.  These features
 * are inherently operating system specific behavior, but by implementing this
 * layer, support can be ported to a third party operating system. */

#include <stdlib.h>
#include <stddef.h>
#include "ind_thrd11.h"

/* Remove #if 0 appropriately for the functionality that is implemented */
#if 0
/* Create a condition variable and set *cnd equal to a pointer to it.
 * Return success or error. */
int _Cnd_init(_Cnd_t * cnd)
{
    return _Thrd_error;
}

/* Release resources associated with a condition variable. */
void _Cnd_destroy(_Cnd_t cnd)
{
    
}

/* Atomically unlocks the mutex and blocks the current thread until condition
 * 'cnd' is signalled by _Cnd_signal or _Cnd_broadcast or a spurious wakeup
 * occurs.  The mutex is atomically reacquired (locked) when the current thread
 * wakes up.
 *
 * Precondition:  The mutex 'mtx' is locked by the current thread.
 * Postcondition: The mutex 'mtx' is locked by the current thread.
 *
 * Returns success or error. */
int _Cnd_wait(_Cnd_t cnd, _Mtx_t mtx)
{
    return _Thrd_error;
}

/* Like _Cnd_wait, but with a maximum time limit before giving up.
 * Returns success, timedout, or error. */
int _Cnd_timedwait(_Cnd_t cnd, _Mtx_t mtx, const xtime *t)
{
    return _Thrd_error;
}

/* Unblocks one thread waiting for condition variable.
 * Returns success or error. */
int _Cnd_signal(_Cnd_t cnd)
{
    return _Thrd_error;
}

/* Unblocks all threads waiting for condition variable.
 * Returns success or error. */
int _Cnd_broadcast(_Cnd_t cnd)
{
    return _Thrd_error;
}
#endif
