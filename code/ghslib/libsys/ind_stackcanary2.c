/*
                        Low-Level System Library

            Copyright 2010-2014 Green Hills Software, Inc.

    This program is the property of Green Hills Software, Inc,
    its contents are proprietary information and no part of it
    is to be disclosed to anyone except employees of Green Hills
    Software, Inc., or as agreed in writing signed by the President
    of Green Hills Software, Inc.
*/

/* __stack_chk_guard should be randomly set.  This value is loaded into the
 * canary guard variable on stack frames.
 */
#include <stdint.h>
#include "indos.h"
uintptr_t __stack_chk_guard = (uintptr_t)0x37ab51bdb31a25cLL;

uintptr_t *__ghs_get_stack_chk_guard_address(void)
{
    return &__stack_chk_guard;
}

/* The user or OS should choose a random initial canary value at the time the
 * system starts up. On stand-alone targets the canary value can be set by
 * defining the function __ghs_set_stack_chk_guard:
 *
 *     #include "indos.h"
 *     void __ghs_set_stack_chk_guard(void)
 *     {
 *         *__ghs_get_stack_chk_guard_address() = <RANDOM_VALUE>;
 *     }
 *
 * On INTEGRITY, the canary value must be initialized at the start of main:
 *
 *     #pragma ghs startnoinline
 *     // Do not allow main2() to be inlined or main() may require a canary.
 *     static int main2(void) {
 *         // Code that would normally be in main() should be placed here.
 *     }
 *     #pragma ghs endnoinline
 *
 *     extern uintptr_t *__ghs_get_stack_chk_guard_address(void);
 *     int main(void) {
 *         // Initialize the stack canary before any code
 *         // that may require a stack canary
 *         *__ghs_get_stack_chk_guard_address() = <RANDOM_VALUE>;
 *         // The real program starts in main2
 *         return main2();
 *     }
 *
 * This method can also be used on stand-alone targets.
 */
