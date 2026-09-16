/*
                        Low-Level System Library

            Copyright 2014-2015 Green Hills Software, Inc.

    This program is the property of Green Hills Software, Inc,
    its contents are proprietary information and no part of it
    is to be disclosed to anyone except employees of Green Hills
    Software, Inc., or as agreed in writing signed by the President
    of Green Hills Software, Inc.
*/
/* ind_core.c: Machine Independent core-specific initialization for multi-core
   support. */

#include "ind_thrd.h"
#include "ind_multicore.h"

static ThreadLocalStorage local_storage = {0};

extern int __ghs_syscall(int, ...);
extern void __ghs_multicore_init_done(void);
extern char **environ;

#pragma weak __ghs_board_devices_init=__ghs_multicore_init
void __ghs_multicore_init(void)
{

    __ghs_add_local_storage(&local_storage);
    __ghs_register_syscall_func(__ghs_syscall, environ);
    __ghs_multicore_init_done();
}

