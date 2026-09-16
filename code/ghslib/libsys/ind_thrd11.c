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

/* This file includes stubs to assist in interfacing with the multi-threading
 * features of C++11 on third-party operating systems. (As enabled by <thread>
 * and <mutex>). By implementing this compatibility layer, you can port C++11
 * multi-threading to an operating system that is not officially supported by
 * Green Hills Software. */
#include <stdlib.h>
#include <stddef.h>
#include "ind_thrd11.h"

/* ==========================================================================
   IMPORTANT: Define the symbol

        __ghs_provides_cpp11_os_threading_support

   in the file that implements the primitives below. It indicates that the
   target "provides C++11 OS threading support."
   (prefix '__ghs_' is reserved for all special GHS symbols)

   If the symbol is defined, the target must supply implementations for all
   of the functions:
       _Thrd_*
       _Mtx_*
       _Sem_*
       _Call_once
   
   A target is allowed to have threading support without implementing
   thread-local storage.
*/
/*
char __ghs_provides_cpp11_os_threading_support;
*/

/* ==========================================================================
   -- Thread-safe initialization of function-local static variables --

   IMPORTANT: For the initializations of function-local static variables to be
   thread-safe you must define the _Mtx_* functions and ensure that they are
   linked into your application.  Since the initialization code references
   the _Mtx_* functions weakly, those references alone will not cause an object
   file to be extracted from a library.  The easiest way to ensure that the
   _Mtx_* functions are always resolved is to use this pragma directive within
   the file that defines all of the _Mtx_* functions:

        #pragma ghs alias __ghs_extract_weak__Mtx_init _Mtx_init

   This will allow a weak reference to _Mtx_init to extract the object from the
   archive, thereby ensuring that the _Mtx_* functions are always linked into
   your application.
*/
/*
#pragma ghs alias __ghs_extract_weak__Mtx_init _Mtx_init
*/

/* ==========================================================================
   -- Handling Thread-Local Storage --

      Note: If implementing thread-local storage is impractical for a
      particular OS, other <thread> and <mutex> features may still be enabled.
      Simply leave '__c_tls_offset' (described below) unimplemented and
      returning 0. A constant offset of 0 will make every thread use the main
      task version of variables in the primary TLS area. As such, programs
      should execute as if the thread_local keyword does not exist. You may use
      the --no_thread_local_storage option to disable support for the
      thread_local keyword entirely.

   When the compiler encounters a thread_local variable, it allocates that
   variable to the .tlsdata or .tlsbss sections (depending on whether it is
   initialized to a non-zero value). These two sections are placed contiguously
   in the program image, with the .tlsdata section preceding the .tlsbss
   section. The "primary TLS area" refers to these two sections, which are used
   exclusively by the main thread. Secondary TLS areas are created outside
   these sections for other threads.
   
   The primary TLS area provides the following functionality:

   1) At link time, the linker uses the combined size of the .tlsdata/.tlsbss
      sections to determine the size of all secondary TLS areas in the program.
      The linker then sets certain symbols (listed below) to allow the run-time
      environment to make the same determination. This information is used when
      a secondary TLS area must be allocated for a newly created thread.
      
   2) The linker creates an initialization image from the .tlsdata section.
      The initialization image is output separately into the .ROM.tlsdata
      section. After a secondary TLS area is allocated for a new thread, the
      environment uses the initialization image to set the correct values for
      thread_local variables with constant initial values. These variables are
      placed in the newly created .tlsdata. Any thread_local variables not
      explicitly initialized to a constant are placed in the newly created
      .tlsbss, which must be cleared to zero.
      
   3) The main thread's thread_local variables reside in the primary TLS area.
      In other words, these .tlsdata and .tlsbss sections serve as a statically
      allocated TLS area. As a consequence, a normal relocation to a
      thread_local variable will resolve to the main thread's copy of the
      variable.

   In order to access a thread_local variable 'var', the compiler outputs code
   with effects similar to the following:

     *(&var + __c_tls_offset())

   The '__c_tls_offset()' function returns the offset between the primary TLS
   area and the current thread's TLS area. Thus, by definition,
   '__c_tls_offset' returns zero for the main thread.

   (A conceptual view of memory)
   _________________________________________________________________
   | TLS area #1 |...................| TLS area #2 |................      
   =================================================================
   ^                                 ^
   ^---------------------------------^
      ( TLS offset for thread #2 )   


   The following linker-provided variables supply the information
   needed to initialize secondary TLS areas. In each case, this information is
   provided by the variable's address, not its value.

   __ghs_tls_align    - Provides the maximum alignment requirement for .tlsdata
                        or .tlsbss variables. TLS areas must be at least this
			aligned.
			
   __ghs_tls_rw_start - Start of .tlsdata/.tlsbss for the main thread.
   
   __ghs_tls_rw_end   - End of .tlsdata/.tlsbss for the main thread.
   
   __ghs_tls_ro_start - Start of .ROM.tlsdata. As noted above, this section
                        contains constant data to initialize each new copy of
			.tlsdata.
			
   __ghs_tls_ro_end   - End of .ROM.tlsdata.

   The size of the secondary TLS area for each new thread is determined by
   ('__ghs_tls_rw_end - __ghs_tls_rw_start'), plus sufficient padding to meet
   the alignment requirement of '__ghs_tls_align'. The size of the constant
   initialized subset of this TLS area is given by
   ('__ghs_tls_ro_end - __ghs_tls_ro_start'), which must be no greater than the
   size of the total TLS area. If it is smaller, the remainder of the TLS area
   will be zero initialized data. The constant data is copied from
   '__ghs_tls_ro_end' to the start of each new TLS area. Finally, the
   '__c_tls_offset' function mentioned previously must return the offset to the
   TLS area from '__ghs_tls_rw_start'.
   

   In summary, an environment that supports thread_local must do the
   following:

   1) Implement '__c_tls_offset()' as described above.

   2) Allocate secondary TLS areas for new threads using the linker-determined
      size of the TLS area. Examples of allocating a TLS area include using
      malloc or carving the area out of the new thread's stack. The TLS area
      must meet the alignment requirements of all TLS variables
      (see '__ghs_tls_align' above).

         Note: We recommend allocating new TLS areas during thread creation
	 rather than during a thread's first execution. Using this approach, a
	 failure to allocate a TLS area will result in a failure to create a
	 thread rather than a defunct thread.

   3) Call something comparable to the example '__c_tls_init' function
      (provided below) to copy the initialization image into the new TLS area.
      
   4) Before they execute their entry function, call '__c_thread_created()'
      from within new threads to initialize thread_local objects that require
      dynamic initialization (such as the calling of constructors).

         Note: This requires that '__c_tls_offset()' return valid offsets for
	 the current thread prior to 'calling __c_thread_created()'. If
         '__c_tls_offset()' needs any special setup of its own, it should be
	 done prior.

   5) Call '__c_thread_terminated()' from within the thread when it exits.
      
  ========================================================================== */

#if 0
/* Return the offset from the start of the main thread's local storage area to
 * the start of the current thread's local storage area. It is assumed that
 * the main thread's local storage area is the .tlsdata/.tlsbss sections. */
size_t __c_tls_offset(void);
#else
/* A backup function for non-threaded environments only for GHS standalone
   target setup */
size_t __c_tls_offset_ghs_standalone_internal_only(void)
{
    return 0;
}    
#endif

/* Remove #if 0 appropriately for the functionality that is implemented */
#if 0
/* Example implementation of requirement 3) noted above.
 *  
 * Implement symbols representing the start and end of the RAM and ROM regions
 * used by thread-local storage. The RAM section is the primary TLS area, where
 * the variables are allocated by the linker. The ROM section contains the
 * constant data used for the initial values in .tlsdata. This allows a new
 * thread to begin with the right starting values even if the main thread has
 * already modified it. */
#pragma weak __ghs_tls_rw_start
#pragma weak __ghs_tls_rw_end
#pragma weak __ghs_tls_ro_start
#pragma weak __ghs_tls_ro_end
extern char __ghs_tls_rw_start[];
extern char __ghs_tls_rw_end[];
extern char __ghs_tls_ro_start[];
extern char __ghs_tls_ro_end[];


/* Alignment requirement for TLS areas. */
#pragma weak __ghs_tls_align
extern char __ghs_tls_align[];


/* Calculate the TLS offset used by '__c_tls_offset', and perform any
 * initialization on the indicated memory block. 'stack' and 'stacksize' are
 * pointers to the initial stack pointer and initial stack size, respectively.
 * In this example, the operating system will carve space for the TLS area from
 * the top of the new task's stack, reducing the remaining stack size.
 *
 * The return value is the offset which should be saved and returned by
 * '__c_tls_offset' when called from within this task. */
void *__c_tls_init(void **stack, void **stacksize)
{

    
    /* The size of the stack region. The TLS region will be reserved at the
     * top of the thread's stack. */
    size_t stacksz = (size_t)*stacksize;

    
    /* The start and size of the primary TLS area. */
    char *rwbegin = __ghs_tls_rw_start;
    size_t rwsz = __ghs_tls_rw_end - rwbegin;

    
    /* The start and size of the TLS constant initialization value region. */
    char *robegin = __ghs_tls_ro_start;
    size_t rosz = __ghs_tls_ro_end - robegin;
    size_t stackpad = 0;

    
    /* The address of this thread's TLS area. */
    char *newtls;

    
    /* If there are no TLS variables, return an offset of '0' and use the
     * main thread version of the variables. */
    if (rwsz <= 0)
	return ((void*)0);

    
    /* If the stack is not large enough to allocate a new TLS area, give up and
     * use the main version of variables. This should not happen for C++11
     * created threads, which reserve extra memory in '_Thrd_start'. For
     * statically allocated threads, detect this problem with gstack. */
    if (stacksz <= rwsz)
	return ((void*)0);

    
    /* Push enough space on the top of the thread's stack the TLS areas. */
    stacksz -= rwsz;
    newtls = ((char*)*stack) + stacksz;
    stackpad = ((size_t)newtls) & (((size_t)__ghs_tls_align) - 1);    
    if (stacksz <= stackpad)
	return ((void*)0);
    stacksz -= stackpad;
    newtls -= stackpad;
    *stacksize = (void*)stacksz;

    
    /* Copy the 'init' values for .tlsdata and zero out .tlsbss. */
    if (rosz > rwsz)
	rosz = rwsz;
    if (rosz > 0)
	memcpy(newtls, robegin, rosz);
    if (rwsz > rosz)
	memset((newtls + rosz), 0, (rwsz - rosz));

    
    /* Return the offset of the new TLS area from the original version. */
    return ((void*)(newtls - rwbegin));
}
#endif

/* Remove #if 0 appropriately for the functionality that is implemented */
#if 0
/* Return the current system time in microseconds. */
long long _Xtime_get_ticks(void)
{
    return 0;
}

/* Create a thread 'thr' that executes function pointer 'fp' and passes it the
 * argument 'arg'. Set '*thr' to a pointer to the new thread.
 *
 * Return success if there are no problems, otherwise return nomem or error
 * status. */
int _Thrd_start_config(_Thrd_t * thr, long priority, size_t stacksize,
	_Thrd_callback_t fp, void *arg)
{
    return _Thrd_error;
}


/* Interface for '_Thrd_start_config' using the default configuration. */
int _Thrd_start(_Thrd_t * thr, _Thrd_callback_t fp, void *arg)
{
    return _Thrd_error;
}


/* Block until thread 'thr' has terminated. If 'res' is non-NULL, set '*res'
 * with the return value from executing thread 'thr'.  The value in the res
 * field is not currently used by std::thread, so it is valid not to set it.
 *
 * Return success or error. */
int _Thrd_join(_Thrd_t thr, long *res)
{
    return _Thrd_error;
}


/* Detach thread 'thr'. The thread will not be joined or otherwise referenced
 * after this point. You can (and probably should) release its resources after
 * it terminates.
 *
 * Return success or error. */
int _Thrd_detach(_Thrd_t thr)
{
    return _Thrd_success;
}


/* Halt execution of this thread until the given time '*t'. */
void _Thrd_sleep(const xtime* t)
{
    
}

/* Halt execution of this thread for the interval of given time '*t'. */
void _Thrd_rel_sleep(const xtime* t)
{
    
}


/* Cause the current thread to yield, potentially allowing other threads to
 * run. */
void _Thrd_yield(void)
{
    
}


/* Return the pointer to the current thread. */
_Thrd_t _Thrd_current(void)
{
    return NULL;
}

/* Exits the current thread */
void _Thrd_exit(int status)
{

}


/* Create a mutex. Specify properties as bits in the 'typ' field:
 * plain = 0x01		// Does not need to support "try" or "timed".
 * try = 0x02   	// Supports _Mtx_trylock hook.
 * timed = 0x04		// Supports _Mtx_timedlock hook.
 * recursive = 0x100	// Can be locked multiple times by the same thread.
 * 
 * Return success or error.
 *
 * Note that, in general, any mutex that supports extra features (like try,
 * timed, or recursive) is safe to use when implementing a mutex that does not
 * need these features. However, the reverse is not true--a mutex without
 * needed features will fail to function properly. */
int _Mtx_init(_Mtx_t *mtx, int typ)
{
    return _Thrd_error;
}

/* Release any resources used by mutex 'mtx'. */
void _Mtx_destroy(_Mtx_t mtx)
{
    
}


/* Block until the mutex 'mtx' can be locked by this thread.
 *  
 * Return success or error. */
int _Mtx_lock(_Mtx_t mtx)
{
    return _Thrd_error;
}


/* Attempt to lock mutex 'mtx'. If it is already locked, return without
 * blocking.
 *
 * Return success, busy, or error. */
int _Mtx_trylock(_Mtx_t mtx)
{
    return _Thrd_error;
}


/* Attempt to lock mutex 'mtx', but do not block indefinitely.
 *
 * Return timedout status if unsuccessful due to absolute time limit. */ 
int _Mtx_timedlock(_Mtx_t mtx, const xtime *t)
{
    return _Thrd_error;
}

/* Attempt to lock mutex 'mtx', but do not block indefinitely.
 *
 * Return timedout status if unsuccessful due to relative time limit. */ 
int _Mtx_rel_timedlock(_Mtx_t mtx, const xtime *t)
{
    return _Thrd_error;
}


/* Unlock mutex previously locked by this thread.
 * Return success or error. */
int _Mtx_unlock(_Mtx_t mtx)
{
    return _Thrd_error;
}

/* Check to see whether the current thread has a lock on the mutex 'mtx'.
 * If this operation is not supported, conservatively return true. This
 * unintuitive, conservative behavior exists to satisfy sanity checks in the
 * library. Although this function is not necessary for correctness, returning
 * a spurious false value will cause assertion failures.
 * Note that this hook is optional. */
int _Mtx_current_owns(_Mtx_t mtx)
{
    return 1;
}


/* Create a counting semaphore with the initial value of 'sval' and set '*sem'
 * equal to the new semaphore.
 *
 * Return success or error. */
int _Sem_init(_Sem_t *sem, int sval)
{
    return _Thrd_error;
}


/* Release any resources associated with the semaphore 'sem'.
 *  
 * Return success or error. */
int _Sem_destroy(_Sem_t sem)
{
    return _Thrd_error;
}


/* Decrement (lock) the semaphore 'sem'. If the semaphore's value is greater
 * than zero, the decrement will occur and the function will return
 * immediately. If the semaphore's value is zero or less, the call will block
 * until a '_Sem_post()' call unblocks it. */
int _Sem_wait(_Sem_t sem)
{
    return _Thrd_error;
}


/* Decrement (lock) the semaphore 'sem'. If the semaphore's value is greater
 * than zero, the decrement will occur and the function will return
 * immediately. If the semaphore's value is zero or less, the call will block
 * until a '_Sem_post()' call unblocks it, or it will time out if the absolute
 * time reaches 't'.
 *
 * Return success (if the call did not time out), timedout
 * (if it did time out), or error. */
int _Sem_timedwait(_Sem_t sem, const xtime *t)
{
    return _Thrd_error;
}


/* Decrement (lock) the semaphore 'sem'. If the semaphore's value is greater
 * than zero, the decrement will occur and the function will return
 * immediately. If the semaphore's value is zero or less, the call will block
 * until a '_Sem_post()' call unblocks it, or it will time out after the
 * relative time interval 't'.
 *
 * Return success (if the call did not time out), timedout
 * (if it did time out), or error. */
int _Sem_rel_timedwait(_Sem_t sem, const xtime *t)
{
    return _Thrd_error;
}


/* Increment the value of semaphore 'sem' by one. If there are any threads
 * blocked on this semaphore, one of them is unblocked.
 * 
 * Return success or error. */
int _Sem_post(_Sem_t sem)
{
    return _Thrd_error;
}


/* Get the value of the semaphore 'sem', and set '*sval'.
 * This function is only needed for consistency checking (testing the library
 * code).
 *
 * Return success or error. */
int _Sem_getvalue(_Sem_t sem, int *sval)
{
    return _Thrd_error;
}

/* Sets the value of the thread-specific storage identified by key for the
 * current thread to value.  Different threads may set different values to the
 * same key.
 * 
 * Return success or error. */
int _Tss_set(_Tss_t key, const void *value)
{
    return _Thrd_error;
}

/* Returns the value of the thread-specific storage identified by key for the
 * current thread to value.  Different threads may get different values to the
 * same key. */
void *_Tss_get(_Tss_t key)
{
    return NULL;
}

/* Creates new thread-specific storage key and stores it in the object pointed
 * to by _Tss_t. Although the same key value may be used by different threads,
 * the values bound to the key by _Tss_set are maintained on a per-thread basis
 * and persist for the life of the calling thread.
 * 
 * The value NULL is associated with the newly created key in all existing
 * threads, and upon thread creation, the values associated with all TSS keys
 * is initialized to NULL.
 *
 * If destructor is not a null pointer, then also associates the destructor
 * which is called when the storage is released by thrd_exit (but not by
 * _Tss_delete and not at program termination by exit).
 * 
 * Return success or error. */
int _Tss_create(_Tss_t *key, _Tss_dtor_t destructor)
{
    return _Thrd_error;
}

/*
 * Destroys the thread-specific storage identified by key
 *
 * The destructor, if one was registered by _Tss_create, is not called
 * 
 * Return success or error. */
int _Tss_delete(_Tss_t key)
{
    return _Thrd_error;
}

#endif
