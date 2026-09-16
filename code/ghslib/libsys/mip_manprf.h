/*
 *   Copyright 2004-2016 by Green Hills Software,Inc.
 *
 *  This program is the property of Green Hills Software, Inc,
 *  its contents are proprietary information and no part of it
 *  is to be disclosed to anyone except employees of Green Hills
 *  Software, Inc., or as agreed in writing signed by the President
 *  of Green Hills Software, Inc.
 */

/****
 *  Originally tested on Malta 4kc and IDT 79eb355
 *   but this implementation should work on most MIPS targets.
 *  Non-standard items:
 *     1. timer fed back on int7 (though this is traditional)
 *     2. TICKS_PER_SEC()
 */

#if defined(__mips16)

#define NO_BUILD_MANPRF 1

#else

#define OFF_ALIGN_FILL_INST	0x00000026	/* XOR R0, R0, R0 */

/* setup the interrupt vector 
 *  - r27 dedicated to interrupts 
 *  - this will not work under PIC: could fixup address
 *     at runtime, or place handler in ABS section */
#pragma asm
#if __PTR_BIT == 64
.section "orgffffffff80000180","ax" >0xffffffff80000180
dla $27, __ghs_manprf_timer_handler
#else
.section "org80000180","ax" >0x80000180
#if defined(__mips_micromips)
lui $27, %hi(__ghs_manprf_timer_handler)
addiu $27, $27, %lo(__ghs_manprf_timer_handler)
#else
la $27, __ghs_manprf_timer_handler
#endif
#endif
jr $27
nop
nop
nop
#pragma endasm

/* TICKS_PER_SEC: on some targets you may be able to read or
 * compute this value. If so, define a function called
 * __ghs_manprf_timer_ticks_per_sec that returns the timer
 * frequency. Otherwise, you'll want to set this value here.
 */
#pragma weak __ghs_manprf_timer_ticks_per_sec
unsigned int __ghs_manprf_timer_ticks_per_sec(void);
unsigned int TICKS_PER_SEC(void) {
    if(__ghs_manprf_timer_ticks_per_sec) {
        return __ghs_manprf_timer_ticks_per_sec();
    } else {
	return 200000;
    }
}

/* Initialize the count and compare registers. */
asm void TIMER_INIT(unsigned int compare)
{
%reg compare
    /* clear the count */
#ifdef __JAXA2_HAZARDS
	.align	4 mod 8, OFF_ALIGN_FILL_INST
#endif	
    mtc0 $0, $9
    /* set the compare */
#ifdef __JAXA2_HAZARDS
	.align	4 mod 8, OFF_ALIGN_FILL_INST
#endif	
    mtc0 compare, $11

%error
}

/* Enable the timer interrupt */
asm void ENABLE_TIMER_INTERRUPT(void)
{
    /* read the status register */
/* ERT_TX49H3_012 */
#ifdef __R4000__
    nop
#endif
#ifdef __JAXA2_HAZARDS
	.align	4 mod 8, OFF_ALIGN_FILL_INST
#endif	
    mfc0 $3, $12
    nop
    nop
    /* set the timer interrupt mask and enable interrupt bit */
    /* assumes timer on HW INT 7 */
    ori $3, $3, 0x8001
    /* move to the status register */
#ifdef __JAXA2_HAZARDS
	.align	4 mod 8, OFF_ALIGN_FILL_INST
#endif	
    mtc0 $3, $12
}

#if __PTR_BIT == 64
typedef uint64_t address_type;
#else
typedef uint32_t address_type;
#endif

/* Read the exception PC. */
asm address_type GET_EPC(void)
{
    /* move from EPC */
/* ERT_TX49H3_012 */
#ifdef __R4000__
    nop
#endif
#ifdef __JAXA2_HAZARDS
	.align	4 mod 8, OFF_ALIGN_FILL_INST
#endif	
#if __PTR_BIT == 64
    dmfc0 $2, $14
#else
    mfc0  $2, $14
#endif
    nop
    nop
}

/* Clear the timer interrupt. */
asm void CLEAR_TIMER_INTERRUPT(void)
{
    /* on MIPS, done by TIMER_INIT.
     *  EXL cleared on return from interrupt */
}

#endif
