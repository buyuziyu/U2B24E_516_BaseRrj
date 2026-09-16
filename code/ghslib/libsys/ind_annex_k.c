/*
                        Low-Level System Library

            Copyright 2020 Green Hills Software, Inc.

    This program is the property of Green Hills Software, Inc,
    its contents are proprietary information and no part of it
    is to be disclosed to anyone except employees of Green Hills
    Software, Inc., or as agreed in writing signed by the President
    of Green Hills Software, Inc.
*/

#if !defined(__STDC_LIB_EXT1__)
#error "This file requires Annex K support"
#endif

#define __STDC_WANT_LIB_EXT1__ 1
#include <stdlib.h>

/* This is the default runtime-constraint handler for Annex K functions.
 *
 * You can set a custom handler at runtime by calling set_constraint_handler_s.
 *
 * You can also customize the behavior of the default handler by modifying this
 * function. One reason to do that, instead of setting a handler at runtime, is
 * that almost every Annex K function links in the default handler. Customizing
 * the default handler allows you to call those funtions without linking in
 * abort_handler_s (and with it fputs and abort).
 */
void __ghs_default_constraint_handler_s(const char *msg, void *ptr,
	errno_t error)
{
    abort_handler_s(msg, ptr, error);
}
