/*
 *                         Copyright 2015-2019                      
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

#ifndef _THREAD11_H_
#define _THREAD11_H_

#include "ind_thrd.h"

#ifdef __cplusplus
extern "C" {
#endif

/* IMPORTANT: Define this symbol in the file that implements the primitives
   below to indicate support of C++11 threading */
extern char __ghs_provides_cpp11_os_threading_support;


/* Return codes for C++11 multi-threading interface. */
enum {
    _Thrd_success,
    _Thrd_nomem,
    _Thrd_timedout,
    _Thrd_busy,
    _Thrd_error
};

/* Declare basic types used by the C++11 multi-threading interface. */
typedef void *_Thrd_t;				/* Thread */
typedef unsigned long _Thrd_id_t;		/* Thread ID number */
typedef long (*_Thrd_callback_t)(void *);	/* Thread function pointer */
typedef void *_Mtx_t;				/* Mutex */
typedef void *_Cnd_t;				/* Condition variable */
typedef void *_Sem_t;				/* Semaphore */
typedef void *_Tss_t;				/* Thread specific storage */
typedef void(*_Tss_dtor_t)(void*);              /* TSS destructor function */

/* Represent time with nanosecond resolution. */
typedef struct xtime {
    long long sec;
    long      nsec;
} xtime;


/* Return the current system time in microseconds. */
long long _Xtime_get_ticks(void);

/* Return the offset from the start of the main thread's local storage area to
 * the start of the current thread's local storage area. It is assumed that
 * the main thread's local storage area is the .tlsdata/.tlsbss sections. */
size_t __c_tls_offset(void);

/* Called within a new thread for thread_local dynamic initialization. */
void __c_thread_created(void);

/* Called when exiting a thread for thread_local destructors. */
void __c_thread_terminated(void);


/* Create a thread 'thr' that executes function pointer 'fp' and passes it the
 * argument 'arg'. Set '*thr' to a pointer to the new thread. */
int _Thrd_start_config(_Thrd_t * thr, long priority, size_t stacksize,
	_Thrd_callback_t fp, void *arg);

/* Interface for '_Thrd_start_config' using the default configuration. */
int _Thrd_start(_Thrd_t * thr, _Thrd_callback_t fp, void *arg);

/* Block until thread 'thr' has terminated.  If 'res' is non-NULL, set '*res'
 * with the return value from executing thread 'thr'.  The value in the res
 * field is not currently used by std::thread, so it is valid not to set it. */
int _Thrd_join(_Thrd_t thr, long *res);

/* Detach thread 'thr'. The thread will not be joined or otherwise referenced
 * after this point. You can (and probably should) release its resources after
 * it terminates. */
int _Thrd_detach(_Thrd_t thr);

/* Halt execution of this thread until the given time '*t'. */
void _Thrd_sleep(const xtime* t);

/* Halt execution of this thread for the interval of given time '*t'. */
void _Thrd_rel_sleep(const xtime* t);

/* Cause the current thread to yield, potentially allowing other threads to
 * run. */
void _Thrd_yield(void);

/* Return the pointer to the current thread. */
_Thrd_t _Thrd_current(void);

/* Exits the current thread. */
_Thrd_t _Thrd_exit(int status);


/* Create a mutex. Specify properties as bits in the 'typ' field:
 * plain = 0x01		// Does not need to support "try" or "timed".
 * try = 0x02   	// Supports _Mtx_trylock hook.
 * timed = 0x04		// Supports _Mtx_timedlock hook.
 * recursive = 0x100	// Can be locked multiple times by the same thread.
 *
 * Note that, in general, any mutex that supports extra features (like try,
 * timed, or recursive) is safe to use when implementing a mutex that does not
 * need these features.  However, the reverse is not true--a mutex without
 * needed features will fail to function properly. */
int _Mtx_init(_Mtx_t *mtx, int typ);

/* Release any resources used by mutex. */
void _Mtx_destroy(_Mtx_t mtx);

/* Block until mutex can be locked by this thread. */
int _Mtx_lock(_Mtx_t mtx);

/* Attempt to lock mutex 'mtx', but do not block indefinitely.
 * Return timedout status if unsuccessful due to absolute time limit. */ 
int _Mtx_timedlock(_Mtx_t mtx, const xtime *t);

/* Attempt to lock mutex 'mtx', but do not block indefinitely.
 * Return timedout status if unsuccessful due to relative time limit. */ 
int _Mtx_rel_timedlock(_Mtx_t mtx, const xtime *t);

/* Unlock mutex previously locked by this thread. */
int _Mtx_unlock(_Mtx_t mtx);

/* Does the current thread have a lock on this mutex?  This hook is optional.
 * If the operation cannot be easily supported, conservatively return true. */
int _Mtx_current_owns(_Mtx_t mtx);


/* Create a counting semaphore with the initial value of sval and set
 * *sem equal to the new semaphore.
 * Return success or error. */
int _Sem_init(_Sem_t *sem, int sval);

/* Release any resources associated with semaphore.
 * Return success or error. */
int _Sem_destroy(_Sem_t sem);

/* Decrement (lock) the semaphore sem. If the semaphore's value is greater
 * than zero, the decrement proceeds and the function returns immediately. If
 * the semarphore currently has the value zero or less, then the call blocks
 * until a _Sem_post() call unblocks it.
 * Return success or error. */
int _Sem_wait(_Sem_t sem);

/* Decrement (lock) the semaphore 'sem'. If the semaphore's value is greater
 * than zero, the decrement will occur and the function will return
 * immediately. If the semaphore's value is zero or less, the call will block
 * until a '_Sem_post()' call unblocks it, or it will time out if the absolute
 * time reaches 't'.
 *
 * Return success (if the call did not time out), timedout
 * (if it did time out), or error. */
int _Sem_timedwait(_Sem_t sem, const xtime *t);

/* Decrement (lock) the semaphore 'sem'. If the semaphore's value is greater
 * than zero, the decrement will occur and the function will return
 * immediately. If the semaphore's value is zero or less, the call will block
 * until a '_Sem_post()' call unblocks it, or it will time out after the
 * relative time interval 't'.
 *
 * Return success (if the call did not time out), timedout
 * (if it did time out), or error. */
int _Sem_rel_timedwait(_Sem_t sem, const xtime *t);

/* Increment the value of semaphore by one. If there are any threads blocked
 * on the semaphore, one of them is unblocked.
 * 
 * Return success or error. */
int _Sem_post(_Sem_t sem);

/* Get the value of the semaphore object, and set *sval
 * This function is only needed for consistency checking (testing the library
 * code).
 * Return success or error. */
int _Sem_getvalue(_Sem_t sem, int *sval);

/* Sets the value of the thread-specific storage identified by key for the
 * current thread to value.
 * Return success or error. */
int _Tss_set(_Tss_t key, const void *value);

/* Returns the value of the thread-specific storage identified by key for the
 * current thread to value.
 */
void *_Tss_get(_Tss_t key);

/* Creates new thread-specific storage key and stores it in the object pointed
 * to by key. 
 * Return success or error. */
int _Tss_create(_Tss_t *key, _Tss_dtor_t destructor);

/* Destroys the thread-specific storage identified by key
 * Return success or error. */
int _Tss_delete(_Tss_t key);

#ifdef __cplusplus
}
#endif

#endif /* _THREAD11_H_ */
