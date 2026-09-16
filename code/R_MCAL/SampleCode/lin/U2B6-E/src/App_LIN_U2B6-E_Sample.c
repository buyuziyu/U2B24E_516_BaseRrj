/*============================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                         */
/* Module       = App_LIN_U2B6-E_Sample.c                                     */
/*============================================================================*/
/* (c) 2024-2025 Renesas Electronics Corporation. All rights reserved.        */
/*============================================================================*/
/* Purpose:                                                                   */
/* This file contains sample application for LIN Driver Component             */
/*                                                                            */
/*============================================================================*/
/*                                                                            */
/* Unless otherwise agreed upon in writing between your company and           */
/* Renesas Electronics Corporation the following shall apply!                 */
/*                                                                            */
/* Warranty Disclaimer                                                        */
/*                                                                            */
/* There is no warranty of any kind whatsoever granted by Renesas. Any        */
/* warranty is expressly disclaimed and excluded by Renesas, either expressed */
/* or implied, including but not limited to those for non-infringement of     */
/* intellectual property, merchantability and/or fitness for the particular   */
/* purpose.                                                                   */
/*                                                                            */
/* Renesas shall not have any obligation to maintain, service or provide bug  */
/* fixes for the supplied Product(s) and/or the Application.                  */
/*                                                                            */
/* Each User is solely responsible for determining the appropriateness of     */
/* using the Product(s) and assumes all risks associated with its exercise    */
/* of rights under this Agreement, including, but not limited to the risks    */
/* and costs of program errors, compliance with applicable laws, damage to    */
/* or loss of data, programs or equipment, and unavailability or              */
/* interruption of operations.                                                */
/*                                                                            */
/* Limitation of Liability                                                    */
/*                                                                            */
/* In no event shall Renesas be liable to the User for any incidental,        */
/* consequential, indirect, or punitive damage (including but not limited     */
/* to lost profits) regardless of whether such liability is based on breach   */
/* of contract, tort, strict liability, breach of warranties, failure of      */
/* essential purpose or otherwise and even if advised of the possibility of   */
/* such damages. Renesas shall not be liable for any services or products     */
/* provided by third party vendors, developers or consultants identified or   */
/* referred to the User by Renesas in connection with the Product(s) and/or   */
/* the Application.                                                           */
/*                                                                            */
/*============================================================================*/
/* Environment:                                                               */
/*              Devices:        X2x                                           */
/*============================================================================*/

/*******************************************************************************
**                      Revision Control History                              **
*******************************************************************************/
/*
 * 2.4.1:  30/06/2025  : Update Tx PortPin of Channel 0
 * 2.3.2:  25/04/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03
 *                       Release
 * 2.3.1:  31/03/2025  : Support core G4KH for U2Bx-E device
 *                       Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02
 *                       Release
 * 2.3.0:  31/01/2025  : Update SW-VERSION for Ver22.00.06 U2C2 Beta release and
 *                       Ver22.01.00(D) U2C4 Final Release
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00(D) U2Bx Final Release
 * 2.1.2:  31/10/2024  : Update SW-VERSION
 * 2.1.1:  25/06/2024  : Initial Version
 */
/******************************************************************************/

/*******************************************************************************
**                     Include Section                                        **
*******************************************************************************/
#include "App_LIN_Device_Sample.h"

/*******************************************************************************
**                         Local Definitions                                  **
*******************************************************************************/
#define PIN_PM(n)         *((volatile uint16*)(PORT_BASE + 0x0010UL + ((uint32)(n) * 0x40UL)))
#define PIN_PMC(n)        *((volatile uint16*)(PORT_BASE + 0x0014UL + ((uint32)(n) * 0x40UL)))
#define PIN_PFC(n)        *((volatile uint16*)(PORT_BASE + 0x0018UL + ((uint32)(n) * 0x40UL)))
#define PIN_PFCE(n)       *((volatile uint16*)(PORT_BASE + 0x001CUL + ((uint32)(n) * 0x40UL)))
#define PIN_PFCAE(n)      *((volatile uint16*)(PORT_BASE + 0x0028UL + ((uint32)(n) * 0x40UL)))
#define PIN_PBDC(n)       *((volatile uint16*)(PORT_BASE + 0x4004UL + ((uint32)(n) * 0x40UL)))
#define PIN_PIPC(n)       *((volatile uint16*)(PORT_BASE + 0x4008UL + ((uint32)(n) * 0x40UL)))
#define PIN_PFCEAE(n)     *((volatile uint16*)(PORT_BASE + 0x002CUL + ((uint32)(n) * 0x40UL)))
#define LIN_CPUCLK_MHZ 400UL
#define LIN_WAIT_NS(t)  { volatile uint32 cnt; \
  for ( cnt = 0;cnt < ((((uint32)LIN_CPUCLK_MHZ * ((uint32)t)) / (uint32)1000) + (uint32)1);cnt++ ); }

/*******************************************************************************
**                      Local types                                           **
*******************************************************************************/


/*******************************************************************************
**                      Local variables                                       **
*******************************************************************************/


/*******************************************************************************
**                      ISR Defines                                           **
*******************************************************************************/


/*******************************************************************************
**                      Clock Initialization                                  **
*******************************************************************************/
void Clock_Init(void)
{
  /**********************/
  /* LSIntOSC(240[KHz]) */
  /**********************/
  /* (After power supply the LSIntOSC starts operation. It cannot be stopped.) */

  /**********************/
  /* HSIntOSC(200[MHz]) */
  /**********************/
  /* (After Power On Reset or System Reset1 release the HSIntOSC starts operation.) */

  /* Wait to HSIntOSC clock is stable(HSOSCS.HSOSCSTAB = 1). */
  while ( (HSOSCS & 0x00000002UL) != 0x00000002UL )
  {
  }

  /* HSIntOSC stops operation in stand-by mode(HSOSCSTPM.MOSCSTPMSK = 0). */
  CLKKCPROT1  = ENABLE_WRITE_KEY_CODE;
  HSOSCSTPM   = 0x00000000UL;
  CLKKCPROT1  = DISABLE_WRITE_KEY_CODE;

  /***********/
  /* MainOSC */
  /***********/

  /* 1.Confirm that the HSIntOSC is stable (HSOSCS.HSOSCSTAB = 1). */
  /* (Checked) **/

  /* 2.Confirm that the MainOSC is unstable (MOSCS.MOSCSTAB = 0). */
#if 0
  while ( (MOSCS & 0x00000002UL) != 0x00000000UL )
  {
  }
#else
  {
    volatile int w;
    for(w=0; w>1000000000; w++){};
  }
#endif

  /* 3.Start the MainOSC (MOSCE.MOSCENTRG = 1). */
  CLKKCPROT1  = ENABLE_WRITE_KEY_CODE;
  MOSCE       = 0x00000001UL;
  CLKKCPROT1  = DISABLE_WRITE_KEY_CODE;

  /* 4.Confirm that the MainOSC has been started (MOSCS.MOSCSTAB = 1). */
  while ( (MOSCS & 0x00000002UL) != 0x00000002UL )
  {
  }

  /* MainOSC stops operation in stand-by mode(MOSCSTPM.MOSCSTPMSK = 0). */
  CLKKCPROT1  = ENABLE_WRITE_KEY_CODE;
  MOSCSTPM    = 0x00000000UL;
  CLKKCPROT1  = DISABLE_WRITE_KEY_CODE;

  /*******/
  /* PLL */
  /*******/

  /* 1.Confirm that the MainOSC is stable (MOSCS.MOSCSTAB = 1). */
  /* (Checked) **/

  /* 2.Confirm that the PLL is unstable (PLLS.PLLCLKSTAB = 0). */
#if 0
  while ( (PLLS & 0x00000002UL) != 0x00000000UL )
  {
  }
#else
  {
    volatile int w;
    for(w=0; w>1000000000; w++){};
  }
#endif

  /* 3.Start the PLL (PLLE.PLLENTRG = 1). */
  CLKKCPROT1  = ENABLE_WRITE_KEY_CODE;
  PLLE        = 0x00000001UL;
  CLKKCPROT1  = DISABLE_WRITE_KEY_CODE;

  /* 4.Confirm that the PLL has been started (PLLS.PLLCLKSTAB = 1). */
  while ( (PLLS & 0x00000002UL) != 0x00000002UL )
  {
  }

  /* PLL stops operation in stand-by mode(PLLSTPM.PLLSTPMSK = 0) */
  CLKKCPROT1  = ENABLE_WRITE_KEY_CODE;
  PLLSTPM     = 0x00000000UL;
  CLKKCPROT1  = DISABLE_WRITE_KEY_CODE;

  /* Release the write protection of Clock controller register */
  CLKKCPROT1 = ENABLE_WRITE_KEY_CODE;

  /* Division ratio of clock source PLL is changed from 1 to 3/8 */
  CKD_PLLC = 0x6U;   /* Write 0110B in CKD_PLLC.PLLCLKDCSID */
  (void)CKD_PLLC;
  CKD_SSCGC = 0x6U;  /* Write 0110B in CKD_SSCGC.SSCGCLKDCSID */
  (void)CKD_SSCGC;
  EXECUTE_SYNCP();

  /* -- Divider clock synchronized for PLL -- */
  while ( (CKD_PLLS & (uint32)0x2) != (uint32)0x2U ); /* Read CKD_PLLS and verify that the value of PLLCLKDSYNC is 1B */

  /* The clock source for the System clock is changed from CLK_IOSC to CLK_PLLO */
  CKS_CLEANC = (uint32)0x0U;
  (void)CKS_CLEANC;
  EXECUTE_SYNCP();

  /* Read CKS_CLEANS and verify that the value of SYSCLKSACT is 0B */
  while ( (CKS_CLEANS & (uint32)0x1U) != (uint32)0x0U );
  LIN_WAIT_NS(100 * 1000); /* 100us */

  /* Start of repetitions: 5 repetitions (800MHz) */
  /* Division ratio of clock source PLL is changed from 3/8 to 4/8 */
  CKD_PLLC = 0x8U;
  (void)CKD_PLLC;
  EXECUTE_SYNCP();
  while ( (CKD_PLLS & (uint32)0x2) != (uint32)0x2U );
  LIN_WAIT_NS(100 * 1000); /* 100us */
  /* Division ratio of clock source PLL is changed from 4/8 to 5/8 */
  CKD_PLLC = 0xAU;
  (void)CKD_PLLC;
  EXECUTE_SYNCP();
  while ( (CKD_PLLS & (uint32)0x2) != (uint32)0x2U );
  LIN_WAIT_NS(100 * 1000); /* 100us */
  /* Division ratio of clock source PLL is changed from 5/8 to 6/8 */
  CKD_PLLC = 0xCU;
  (void)CKD_PLLC;
  EXECUTE_SYNCP();
  while ( (CKD_PLLS & (uint32)0x2) != (uint32)0x2U );
  LIN_WAIT_NS(100 * 1000); /* 100us */
  /* Division ratio of clock source PLL is changed from 6/8 to 7/8 */
  CKD_PLLC = 0xEU;
  (void)CKD_PLLC;
  EXECUTE_SYNCP();
  while ( (CKD_PLLS & (uint32)0x2) != (uint32)0x2U );
  LIN_WAIT_NS(100 * 1000); /* 100us */
  /* Division ratio of clock source PLL is changed from 7/8 to 1 */
  CKD_PLLC = 0x0U;
  (void)CKD_PLLC;
  EXECUTE_SYNCP();
  while ( (CKD_PLLS & (uint32)0x2) != (uint32)0x2U );
  LIN_WAIT_NS(100 * 1000); /* 100us */
  /* End of repetitions for PLL */
  
  /* -- Divider clock synchronized for SSCG -- */
  while ( (CKD_SSCGS & (uint32)0x2) != (uint32)0x2U ); 
  /* Read CKD_SSCGS and verify that the value of SSCGCLKDSYNC is 1B */

  /* The clock source for the System clock is changed from CLK_IOSC to CLK_PLLO */
  CKS_SSCGC = (uint32)0x0U;
  (void)CKS_SSCGC;
  EXECUTE_SYNCP();

  /* Read CKS_SSCGS and verify that the value of SYSCLKSACT is 0B */
  while ( (CKS_SSCGS & (uint32)0x1U) != (uint32)0x0U );
  LIN_WAIT_NS(100 * 1000); /* 100us */

  /* Start of repetitions: 5 repetitions (800MHz) */
  /* Division ratio of clock source SSCG is changed from 3/8 to 4/8 */
  CKD_SSCGC = 0x8U;
  (void)CKD_SSCGC;
  EXECUTE_SYNCP();
  while ( (CKD_SSCGS & (uint32)0x2) != (uint32)0x2U );
  LIN_WAIT_NS(100 * 1000); /* 100us */
  /* Division ratio of clock source SSCG is changed from 4/8 to 5/8 */
  CKD_SSCGC = 0xAU;
  (void)CKD_SSCGC;
  EXECUTE_SYNCP();
  while ( (CKD_SSCGS & (uint32)0x2) != (uint32)0x2U );
  LIN_WAIT_NS(100 * 1000); /* 100us */
  /* Division ratio of clock source SSCG is changed from 5/8 to 6/8 */
  CKD_SSCGC = 0xCU;
  (void)CKD_SSCGC;
  EXECUTE_SYNCP();
  while ( (CKD_SSCGS & (uint32)0x2) != (uint32)0x2U );
  LIN_WAIT_NS(100 * 1000); /* 100us */
  /* Division ratio of clock source SSCG is changed from 6/8 to 7/8 */
  CKD_SSCGC = 0xEU;
  (void)CKD_SSCGC;
  EXECUTE_SYNCP();
  while ( (CKD_SSCGS & (uint32)0x2) != (uint32)0x2U );
  LIN_WAIT_NS(100 * 1000); /* 100us */
  /* Division ratio of clock source SSCG is changed from 7/8 to 1 */
  CKD_SSCGC = 0x0U;
  (void)CKD_SSCGC;
  EXECUTE_SYNCP();
  while ( (CKD_SSCGS & (uint32)0x2) != (uint32)0x2U );
  LIN_WAIT_NS(100 * 1000); /* 100us */
  /* End of repetitions for SSCG */

  /* Set the write protection of Clock controller */
  CLKKCPROT1 = DISABLE_WRITE_KEY_CODE;

  /**************/
  /* CAN Clock  */
  /**************/
  
  /* CLK_RLIN3/CLK_RLIN3_CH23 Selector Control Register (CKS_RLINC.RLINSCSID = 1) & (CKS_RLINC.RLIN23SCSID = 1) */
  CLKKCPROT1  = ENABLE_WRITE_KEY_CODE;
  CKS_RLINC   = 0x00010001UL;
  CLKKCPROT1  = DISABLE_WRITE_KEY_CODE;
}

/*******************************************************************************
**                    Support post build variant: MCU Reset                   **
*******************************************************************************/
void Mcu_Reset(void)
{
  /* Reset Controller KeyCode Protection */
  #define MCU_RST_DISABLE_REG_PROTECT_VALUE     (uint32)0xA5A5A501UL
  #define MCU_RST_ENABLE_REG_PROTECT_VALUE      (uint32)0xA5A5A500UL
  #define MCU_SW_RESET_ENABLE_VALUE             (uint32)0x00000001UL

  #define RESKCPROT0                            (*((volatile uint32*)(0xFF980F00UL)))
  #define SWARESA                               (*((volatile uint32*)(0xFF988410UL)))

  RESKCPROT0 = MCU_RST_DISABLE_REG_PROTECT_VALUE;

  SWARESA = MCU_SW_RESET_ENABLE_VALUE;

  RESKCPROT0 = MCU_RST_ENABLE_REG_PROTECT_VALUE;
}

/*******************************************************************************
**                      Watchdog Initialization                               **
*******************************************************************************/
void Wdg_Init(void)
{
  /* No action is need */
}


/*******************************************************************************
**                      Mcu Initialization                                    **
*******************************************************************************/
void Mcu_Init(void)
{
  /* Set Reference Table Method for RLIN30 */
  EIC621 |= (uint16)(1 << 6);
  /* Set Reference Table Method for RLIN311 */
  EIC622 |= (uint16)(1 << 6);
  /* Set Reference Table Method for RLIN311 */
  EIC623 |= (uint16)(1 << 6);

  /* Set Reference Table Method for RLIN312 */
  EIC626 |= (uint16)(1 << 6);
  /* Set Reference Table Method for RLIN312 */
  EIC627 |= (uint16)(1 << 6);
  /* Set Reference Table Method for RLIN312 */
  EIC628 |= (uint16)(1 << 6);
 
  /* Set Reference Table Method for RLIN313 */
  EIC631 |= (uint16)(1 << 6);
  /* Set Reference Table Method for RLIN313 */
  EIC632 |= (uint16)(1 << 6);
  /* Set Reference Table Method for RLIN313 */
  EIC633 |= (uint16)(1 << 6);

  /* Set Reference Table Method for RLIN314 */
  EIC636 |= (uint16)(1 << 6);
  /* Set Reference Table Method for RLIN314 */
  EIC637 |= (uint16)(1 << 6);
  /* Set Reference Table Method for RLIN314 */
  EIC638 |= (uint16)(1 << 6);

  /* Set Reference Table Method for RLIN315 */
  EIC641 |= (uint16)(1 << 6);
  /* Set Reference Table Method for RLIN315 */
  EIC642 |= (uint16)(1 << 6);
  /* Set Reference Table Method for RLIN315 */
  EIC643 |= (uint16)(1 << 6);

  /* Set Reference Table Method for RLIN316 */
  EIC645 |= (uint16)(1 << 6);
  /* Set Reference Table Method for RLIN316 */
  EIC646 |= (uint16)(1 << 6);
  /* Set Reference Table Method for RLIN316 */
  EIC647 |= (uint16)(1 << 6);

  /* Set Reference Table Method for RLIN317 */
  EIC993 |= (uint16)(1 << 6);
  /* Set Reference Table Method for RLIN317 */
  EIC994 |= (uint16)(1 << 6);
  /* Set Reference Table Method for RLIN317 */
  EIC995 |= (uint16)(1 << 6);

  /* Set Reference Table Method for RLIN318 */
  EIC997 |= (uint16)(1 << 6);
  /* Set Reference Table Method for RLIN318 */
  EIC998 |= (uint16)(1 << 6);
  /* Set Reference Table Method for RLIN318 */
  EIC999 |= (uint16)(1 << 6);
 
  /* Set Reference Table Method for RLIN323 */
  EIC649 |= (uint16)(1 << 6);
  /* Set Reference Table Method for RLIN323 */
  EIC650 |= (uint16)(1 << 6);
  /* Set Reference Table Method for RLIN323 */
  EIC651 |= (uint16)(1 << 6);

  /* Set Reference Table Method for Timer */
#ifdef USE_LIN_OSTM
  EIC360 |= (uint16)(1 << 6);
#else
  EIC10  |= (uint16)(1 << 6);
#endif

  /* Release the write protection of Stndby controller register.*/
  MSRKCPROT = ENABLE_WRITE_KEY_CODE;

  /* Set to active */
  MSR_RLIN3 = RLIN3_MSR_ACTIVE;
  MSR_OSTM = OSTM0_MSR_ACTIVE;
  MSR_TAUD = TAUD0_MSR_ACTIVE;

  /*Set the write protection of Stndby controller registers.*/
  MSRKCPROT = DISABLE_WRITE_KEY_CODE;
  while ((MSR_RLIN3 != RLIN3_MSR_ACTIVE) ||
         (MSR_OSTM != OSTM0_MSR_ACTIVE)||
         (MSR_TAUD != TAUD0_MSR_ACTIVE));
}


/*******************************************************************************
**                      Timer Initialization                                  **
*******************************************************************************/
void App_Lin_Start_Timer0(void)
{
#ifdef USE_LIN_OSTM
  /* Only OSTM0 is used */
  /* Mode selection for Interval timer, Interval counter = 1[ms]/(1/80[MHz]) */
  LIN_OSTM0CMP = 0x00013880UL;
  /* Enable interrupt, Interval timer mode */
  LIN_OSTM0CTL = 0x80U;
  /* Interrupt for OSTM0, Enable reference table jump */
  LIN_ICOSTM0 = 0x4FU;
  /* Start OSTM0 */
  LIN_OSTM0TS = 0x01U;
#else
  /* Only TAUD0 channel 0 is used.                            */
  /* Timer mode is interval timer mode and interval is 1[ms]. */
  /* PCLK = 80[MHz] is assumed.                               */
  LIN_TAUD0TT         = 0xFFFFU;          /* Stop all channels of TAUD0.          */
  LIN_TAUD0TPS        = 0x0005U;          /* Setting CK0 (PCLK/(2^5)->2500[kHz]). */
  LIN_TAUD0CDR0       = (2500U - 1U);     /* 2500/2500[kHz] -> 1[ms].             */
  LIN_TAUD0CMOR0      = 0x0000U;          /* CK0, SW trigger and interval.        */
  LIN_ICTAUD0         = 0x004FU;          /* Enable INT(Table reference).         */
  LIN_TAUD0TS         = 0x0001U;          /* Start TAUD0 channel 0.               */
#endif
}

void App_Lin_Stop_Timer0(void)
{
#ifdef USE_LIN_OSTM
  LIN_OSTM0TT = 0x01U;                    /* Stop OSTM0.                      */
#else
  LIN_TAUD0TT = 0x0001U;                  /* Stop TAUD0 channel 0.            */
#endif
}


/*******************************************************************************
**                      Port Initialization                                   **
*******************************************************************************/
void Port_Init(void)
{
  /* Set Port Keycode Register to Enable */
  PKCPROT = ENABLE_WRITE_KEY_CODE;
 
#if 1
  /* Set Port Write Enable Register to Enable */
  PWE = 0x007F7FFF;
  while (PWE != 0x007F7FFFUL)
  {
    ASM_NOP();
  };
#endif

  /* --- Port Setting Start --- */
  /*********************
  ** RLIN3 Channel #0                                          | PMC PM PBDC PIPC | PFCEAE PFCAE PFCE PFCn | **
  ** P15_15 : RLIN30TX - Alternative Function 2(Output)        | 1   0  0    0    | 0      0     0    1    | **
  ** P15_2  : RLIN30RX - Alternative Function 4(Input)         | 1   1  0    0    | 0      0     1    1    | **
  *********************/
  /* Seting Value */
  #define LIN_PORT_VALUE_TX0 (1U << 15U) /* P15_15 */
  #define LIN_PORT_VALUE_RX0 (1U << 2U) /* P15_2 */

  /* Set Port Function Control Expansion Register to AF 2 */
  PIN_PFCEAE(15) &= (uint16)~(LIN_PORT_VALUE_TX0);
  PIN_PFCEAE(15) &= (uint16)~(LIN_PORT_VALUE_RX0);

  /* Set Port Function Control Additional Expansion Register to AF 1-4 */
  PIN_PFCAE(15) &= (uint16)~(LIN_PORT_VALUE_TX0);
  PIN_PFCAE(15) &= (uint16)~(LIN_PORT_VALUE_RX0);

  /* Set Port Function Control Expansion Register to AF 1-2 */
  PIN_PFCE(15) &= (uint16)~(LIN_PORT_VALUE_TX0);
  PIN_PFCE(15) |= (uint16)(LIN_PORT_VALUE_RX0);

  /* Set Port Function Control Register to AF 2*/
  PIN_PFC(15) |= (uint16)(LIN_PORT_VALUE_TX0);
  PIN_PFC(15) |= (uint16)(LIN_PORT_VALUE_RX0);

  /* Set Port IP Control Register to Software I/O Control */
  PIN_PIPC(15) &= (uint16)(~(LIN_PORT_VALUE_TX0 | LIN_PORT_VALUE_RX0));

  /* Set Port Mode Control Register to AF Mode */
  PIN_PMC(15) |= (uint16)(LIN_PORT_VALUE_TX0 | LIN_PORT_VALUE_RX0);

  /* Set Port Mode Register to Output for TX */
  PIN_PM(15) &= (uint16)~LIN_PORT_VALUE_TX0;

  /* Set Port Mode Register to Input for RX */
  PIN_PM(15) |= (uint16)LIN_PORT_VALUE_RX0;

  /* Set Port Bi-Direction Control Register to Output for TX */
  PIN_PBDC(15) &= (uint16)~LIN_PORT_VALUE_TX0;

  /*********************
  ** RLIN3 Channel #1                                          | PMC PM PBDC PIPC | PFCEAE PFCAE PFCE PFCn | **
  ** P02_2  : RLIN31TX - Alternative Function 2(Output)        | 1   0  0    0    | 0      0     0    1    | **
  ** P02_3  : RLIN31RX - Alternative Function 6(Input)         | 1   1  0    0    | 0      1     0    1    | **
  *********************/
  /* Seting Value */
  #define LIN_PORT_VALUE_TX1 (1UL << 2U) /* P02_2 */
  #define LIN_PORT_VALUE_RX1 (1UL << 3U) /* P02_3 */

  /* Set Port Function Control Expansion Register to AF 2 */
  PIN_PFCEAE(02) &= (uint16)~(LIN_PORT_VALUE_TX1);
  PIN_PFCEAE(02) &= (uint16)~(LIN_PORT_VALUE_RX1);

  /* Set Port Function Control Additional Expansion Register to AF 1-4 */
  PIN_PFCAE(02) &= (uint16)~(LIN_PORT_VALUE_TX1);
  PIN_PFCAE(02) |= (uint16)(LIN_PORT_VALUE_RX1);

  /* Set Port Function Control Expansion Register to AF 1-2 */
  PIN_PFCE(02) &= (uint16)~(LIN_PORT_VALUE_TX1);
  PIN_PFCE(02) &= (uint16)~(LIN_PORT_VALUE_RX1);

  /* Set Port Function Control Expansion Register to AF 2 */
  PIN_PFC(02) |= (uint16)(LIN_PORT_VALUE_TX1);
  PIN_PFC(02) |= (uint16)(LIN_PORT_VALUE_RX1);

  /* Set Port Function Control Additional Expansion Register to AF 1-4 */
  PIN_PIPC(02) &= (uint16)(~(LIN_PORT_VALUE_TX1 | LIN_PORT_VALUE_RX1));

  /* Set Port Function Control Expansion Register to AF 1-2 */
  PIN_PMC(02) |= (uint16)(LIN_PORT_VALUE_TX1 | LIN_PORT_VALUE_RX1);

  /* Set Port Function Control Register to AF 2*/
  PIN_PM(02) &= (uint16)~LIN_PORT_VALUE_TX1;

  /* Set Port IP Control Register to Software I/O Control */
  PIN_PM(02) |= (uint16)LIN_PORT_VALUE_RX1;

  /* Set Port Mode Control Register to AF Mode */
  PIN_PBDC(02) &= (uint16)~LIN_PORT_VALUE_TX1;

  /* Set Port Write Enable Register to Disable */
  PWE = 0x00000000UL;

  /* Set Port Keycode Register to Disable */
  PKCPROT = DISABLE_WRITE_KEY_CODE;
}

#if defined(RUN_OTHER_PE)
void BoundIntToPEMax(void)
{
  int peid;
  peid = STSR(0, 2);
  if (peid == PEID_MAX_VALUE)
  {
    EIBD_BASE_ADDR[360] = PEID_MAX_VALUE;
    EIBD_BASE_ADDR[621] = PEID_MAX_VALUE;
    EIBD_BASE_ADDR[622] = PEID_MAX_VALUE;
    EIBD_BASE_ADDR[623] = PEID_MAX_VALUE;
    EIBD_BASE_ADDR[626] = PEID_MAX_VALUE;
    EIBD_BASE_ADDR[627] = PEID_MAX_VALUE;
    EIBD_BASE_ADDR[628] = PEID_MAX_VALUE;
  }
  else
  {
    // Do nothing since PE0 is default
  }
}
#endif

void Guard_Enable_PE(void)
{
  const uint32 RSLVXX_base[]=
  {
  (uint32) 0xFFC6B000UL, //PBGERRSLV00_base
  (uint32) 0xFFC63100UL, //PBGERRSLV10_base
  (uint32) 0xFFDE1000UL, //PBGERRSLV20_base
  (uint32) 0xFFC73200UL, //PBGERRSLV30_base
  (uint32) 0xFFC75400UL, //PBGERRSLV40_base
  (uint32) 0xFFC7B000UL, //PBGERRSLV50_base
  (uint32) 0xFFC83000UL, //PBGERRSLV60_base
  (uint32) 0xFFC83040UL, //PBGERRSLV62_base
  (uint32) 0xFFF4A000UL, //PBGERRSLV70_base
  (uint32) 0xFFF2A000UL, //PBGERRSLV8H0_base
  (uint32) 0xFF97A200UL, //PBGERRSLV8L0_base
  (uint32) 0xFF0A1400UL, //PBGERRSLV90_base
  (uint32) 0xFF0A1600UL, //PBGERRSLV91_base
  (uint32) 0xFF87A000UL, //PBGERRSLV100_base
  (uint32) 0xFF8B2000UL, //PBGERRSLV11H0_base
  (uint32) 0xFF8F8100UL,  //PBGERRSLV11L0_base
  };

  const uint32 PBGXX_base[]=
  {
  (uint32) 0xFFC6B080UL, //PBG00_base
  (uint32) 0xFFC6B100UL, //PBG01_base
  (uint32) 0xFFC63000UL, //PBG10_base
  (uint32) 0xFFDE0B00UL, //PBG20_base
  (uint32) 0xFFDE0C00UL, //PBG21_base
  (uint32) 0xFFDE0D00UL, //PBG22_base
  (uint32) 0xFFDE0E00UL, //PBG23_base
  (uint32) 0xFFDE1200UL, //PBG24_base
  (uint32) 0xFFC72B00UL, //PBG30_base
  (uint32) 0xFFC72C00UL, //PBG31_base
  (uint32) 0xFFC72D00UL, //PBG32_base
  (uint32) 0xFFC75300UL, //PBG40_base
  (uint32) 0xFFC75380UL, //PBG41_base
  (uint32) 0xFFC7A300UL, //PBG50_base
  (uint32) 0xFFC7A400UL, //PBG51_base
  (uint32) 0xFFC7A500UL, //PBG52_base
  (uint32) 0xFFC81000UL, //PBG60_base
  (uint32) 0xFFC81200UL, //PBG61_base
  (uint32) 0xFFC82000UL, //PBG62_base
  (uint32) 0xFFF49400UL, //PBG70_base
  (uint32) 0xFFF49600UL, //PBG71_base
  (uint32) 0xFFF29300UL, //PBG8H0_base
  (uint32) 0xFF97A000UL, //PBG8L0_base
  (uint32) 0xFF0A1300UL, //PBG90_base
  (uint32) 0xFF0A1500UL, //PBG91_base
  (uint32) 0xFF0A1700UL, //PBG92_base
  (uint32) 0xFF879400UL, //PBG100_base
  (uint32) 0xFF879500UL, //PBG101_base
  (uint32) 0xFF8B1400UL, //PBG11H0_base
  (uint32) 0xFF8B1600UL, //PBG11H1_base
  (uint32) 0xFF8B1800UL, //PBG11H2_base
  (uint32) 0xFF8F8000UL, //PBG11L0_base    
  (uint32) 0xFF860000UL, //PBG_CANFD0_base
  (uint32) 0xFF860800UL, //PBG_CANFD1_base
  (uint32) 0xFF88FA00UL, //PBG_ATU_base
  (uint32) 0xFFF60000UL  //PBG_GTM_base
  };

  //Enable write
  for (int i =0; i<16;i++)
  {
  volatile uint32 *ptr;
  ptr = (volatile uint32 *)(RSLVXX_base[i] + (uint32)0x18UL);
  *ptr = (uint32)0xA5A5A501UL;
  }

  //Write PBG0
  for (int i =0; i<36;i++)
  {
    for (int ii =0; ii<16;ii++)
    {
      volatile uint32 *ptr;
      ptr = (volatile uint32 *)(PBGXX_base[i] + ((uint32)ii * 0x8UL));
      *ptr |= 0x00000143UL;
    }
  }

  //Write PBG1
  for (int i =0; i<36;i++)
  {
    for (int ii =0; ii<16;ii++)
    {
      volatile uint32 *ptr;
      ptr = (volatile uint32 *)(PBGXX_base[i] + 0x4UL + ((uint32)ii * 0x8UL));
      *ptr |= 0xFFFFUL;
    }
  }

  //Disable write
  for (int i =0; i<16;i++)
  {
  volatile uint32 *ptr;
  ptr = (volatile uint32 *)(RSLVXX_base[i]+0x18UL);
  *ptr = 0xA5A5A500UL;
  }
}
/******************************************************************************
**                          End of File                                      **
******************************************************************************/
