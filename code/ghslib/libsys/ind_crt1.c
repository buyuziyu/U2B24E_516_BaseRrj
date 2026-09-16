/*
                        Low-Level System Library

            Copyright 1983-2014 Green Hills Software, Inc.

    This program is the property of Green Hills Software, Inc,
    its contents are proprietary information and no part of it
    is to be disclosed to anyone except employees of Green Hills
    Software, Inc., or as agreed in writing signed by the President
    of Green Hills Software, Inc.
*/

#include "inddef.h"
#include "ind_crt1.h"
#include "ind_exit.h"
#include "ind_thrd.h"
#include "indos.h"
#include "ind_weak.h"
void exit(int);
int atexit(void (*function)(void));
#if defined (__CRT_TRACE_INIT)
extern void __ghs_trace_init(void);
#endif
#pragma weak __ghs_board_devices_init
extern void __ghs_board_devices_init(void);
#pragma weak __gh_iob_init
extern void __gh_iob_init(void);
#pragma weak __gh_lock_init
extern void __gh_lock_init(void);
#pragma weak __ghs_malloc_init
extern void __ghs_malloc_init(void);
#pragma weak __cpp_exception_init
extern void __cpp_exception_init(void **);
#pragma weak __ghs_cpp_exception_init
extern void __ghs_cpp_exception_init(void);
#pragma weak __ghs_manprf_init
extern void __ghs_manprf_init(void);
#pragma weak __ghs_coverage_init
extern void __ghs_coverage_init(void);
#if defined(__mips) && !defined(__TRW_RH32__)
int __ghs_start_pmon_profiling(void);
#endif
#if defined(__StarCore__)
extern void __destroy_global_chain(void);
extern void __exec_staticinit(void);
#endif
    /* Declare 'main' as a far function on MIPS when in LocalPIC mode,
       so that it can be reached however large the user program is.
       Without being 'far', 'main' can be out of the range of 16-bits
       that a local pic call allows when the user program is too large. */
#if defined(__mips) && !defined(__TRW_RH32) && \
	defined(__ghs_pic) && defined(__localpic)
#pragma ghs callmode=far
extern 	int main(int argc, char ** argv, char **envp);
#pragma ghs callmode=default
#else
extern	int main (int argc, char **argv, char **envp);
#endif
#if defined(__ghs_ropi)
#pragma ghs nowarning ghs_ropi_addr_in_static_init
#endif


/*----------------------------------------------------------------------*/
/* ind_crt1.c: Machine Independent library initialization startup code. */
/*									*/
/* CALLED FROM:  __ghs_ind_crt0 in ind_crt0.c				*/
/* ENTRY POINT:  __ghs_ind_crt1 					*/
/*----------------------------------------------------------------------*/
/* This is the first C function called by the standard libraries after	*/
/* memory and static and global data have been initialized.  It         */
/* initializes the ANSI C and other run time libraries before jumping   */
/* to the application entry point (main).				*/
/* Arguments to the initialization routine:  argc, argv, and envp.	*/
/* These are valid if the program is run from the debugger or 0 if not.	*/
/* If argc==0, we construct the arguments to main() on our stack frame. */
/* You may change these arguments to provide any other default values	*/
/*----------------------------------------------------------------------*/

char **environ;

#ifdef __mips
#pragma ghs far
#endif
void __ghs_ind_crt1 (int argc, char *argv[], char *envp[])
{
    /* Hold the default arguments to main() when they are not passed
     * to the target by the debugger.
     */
    char noname[2];
    char *arg[2];
    char *env[2];

#if defined (__CRT_TRACE_INIT)
/*------------------*/
/* initialize trace */
/*------------------*/
    {
	__ghs_trace_init();
    }
#endif

/*--------------------------*/
/* initialize board devices */
/*--------------------------*/
    {
	if (__ghs_weak_func_exists(__ghs_board_devices_init))
	    __ghs_board_devices_init();
    }

/*-----------------*/
/* initialize lock */
/*-----------------*/
    {
	if (__ghs_weak_func_exists(__gh_lock_init))
	    __gh_lock_init();
    }
	
/*---------------------------*/
/* initialize malloc library */
/*---------------------------*/
    {
        if (__ghs_weak_func_exists(__ghs_malloc_init))
	    __ghs_malloc_init();
    }

/*----------------*/
/* initialize iob */
/*----------------*/
    {
	if (__ghs_weak_func_exists(__gh_iob_init))
	    __gh_iob_init();
    }

#if !defined(__disable_thread_safe_extensions) && !defined(__OSE)
/*--------------------*/
/* C++ Thread-safe    */
/* Exception handling */
/*--------------------*/
    {
	if (__ghs_weak_func_exists(__ghs_cpp_exception_init))
	    __ghs_cpp_exception_init();
    }
#endif /* !defined(__disable_thread_safe_extensions) && !defined(__OSE) */

/*-----------------------------*/
/* initialize manual profiling */
/*-----------------------------*/
    {
	if (__ghs_weak_func_exists(__ghs_manprf_init))
	    __ghs_manprf_init();
    }

/*----------------------------------*/
/* initialize -coverage=* profiling */
/*----------------------------------*/
    {
	if (__ghs_weak_func_exists(__ghs_coverage_init))
	    __ghs_coverage_init();
    }

#if !defined(__OSE)
/*----------------------------------*/
/* initialize -stack_protector      */
/*----------------------------------*/    
    {
	if (__ghs_weak_func_exists(__ghs_set_stack_chk_guard))
	    __ghs_set_stack_chk_guard();
    }
#endif /* __OSE */


#if defined(__arm__)
/*---------------------------------*/
/* validate .ghtws section info    */
/*---------------------------------*/
    {
	extern void __ghs_validate_ghtws(void);
        #pragma weak __ghs_validate_ghtws
	if (__ghs_weak_func_exists(__ghs_validate_ghtws))
	    __ghs_validate_ghtws();	
    }
#endif /* __arm__ */
    
/*--------------------------------------------*/
/* set default arguments to main()            */
/*--------------------------------------------*/

    /* Check if the debugger did not supply arguments
     * (for example, when executing out of flash)
     */
    if (!argc) {
	noname[0] = 0;
	noname[1] = 0;

	arg[0] = noname;
	arg[1] = 0;

	env[0] = noname+1;
	env[1] = 0;

	envp = env;
	argv = arg;

	argc = 1;
    }
    environ = envp;

    /* This is a suitable location to place any additional initialization
       routines that must execute prior to main()
     */

/*------------------------------*/
/* call main(argc, argv, envp)	*/
/*------------------------------*/
    exit(main(argc, argv, envp));
    /* exit() will shut down the C library and call _Exit() */
    _Exit(-1);
    /* _Exit() should never return. If it does, let our caller handle it.   */
    return;
}
