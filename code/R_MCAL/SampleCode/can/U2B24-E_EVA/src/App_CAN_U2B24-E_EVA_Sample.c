/*============================================================================*/
/* Project      = RH850/X2x MCAL PF Development                               */
/* Module       = App_CAN_U2B24-E_EVA_Sample.c                                */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2024, 2025 Renesas Electronics Corporation. All rights reserved.       */
/*============================================================================*/
/* Purpose:                                                                   */
/* This application file contains execution sequences to demonstrate the usage*/
/* of CAN Driver APIs.                                                        */
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
/*              Devices:        U2B24-E_EVA                                   */
/*============================================================================*/

/*******************************************************************************
**                      Revision Control History                              **
*******************************************************************************/
/*
 * 2.4.1: 30/06/2025  : Remove the SW-VERSION from header of file
 * 2.3.1: 31/03/2025  : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 * 2.1.2: 31/10/2024  : Increase SW-VERSION to 2.1.2
 * 2.1.1: 21/06/2024  : Remove Mcu_Reset
 *        11/05/2024  : Initial Version
 */
/******************************************************************************/
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "App_CAN_Device_Sample.h"

/*******************************************************************************
**                         Local Definitions                                  **
*******************************************************************************/
#define DISABLE_WRITE_KEY_CODE  (0xA5A5A500UL)
#define ENABLE_WRITE_KEY_CODE   (0xA5A5A501UL)

#define CAN0_PORT_ID 21U
#define CAN0_PIN_RX 5U  /* CAN0RX: P21_5 */
#define CAN0_PIN_TX 4U  /* CAN0TX: P21_4 */

#define CAN1_PORT_ID 4U
#define CAN1_PIN_RX 13U  /* CAN1RX: P4_13 */
#define CAN1_PIN_TX 12U  /* CAN1TX: P4_12 */

#define CAN8_PORT_ID 3U
#define CAN8_PIN_RX 11U /* CAN8RX: P3_11 */
#define CAN8_PIN_TX 10U /* CAN8TX: P3_10 */

#define CAN16_PORT_ID 30U
#define CAN16_PIN_RX 9U /* CAN8RX: P30_9 */
#define CAN16_PIN_TX 5U /* CAN8TX: P30_5 */

#define PIN_P(n)          *((volatile uint16*)(0xFFD90000UL \
                                           + 0x0000UL + ((uint32)(n) * 0x40UL)))

#define PFC_MASK(n)                           ((n - 1U) & 0x001U)
#define PFCE_MASK(n)                          ((n - 1U) & 0x002U) >> 1U
#define PFCAE_MASK(n)                         ((n - 1U) & 0x004U) >> 2U
#define PORT0_BASE_ADDRESS                    0xFFD90000UL
#define PORT1_BASE_ADDRESS                    0xFFD94000UL
#define CAN_CPUCLK_MHZ 400UL
#define CAN_WAIT_NS(t)  { volatile uint32 cnt; \
  for ( cnt = 0;cnt < ((((uint32)CAN_CPUCLK_MHZ * ((uint32)t)) / (uint32)1000) + (uint32)1);cnt++ ); }

#define APP_ALT1_IN                           (uint8)1U
#define APP_ALT2_IN                           (uint8)2U
#define APP_ALT3_IN                           (uint8)3U
#define APP_ALT4_IN                           (uint8)4U
#define APP_ALT5_IN                           (uint8)5U
#define APP_ALT6_IN                           (uint8)6U
#define APP_ALT7_IN                           (uint8)7U
#define APP_ALT8_IN                           (uint8)8U
#define APP_ALT9_IN                           (uint8)9U
#define APP_ALT10_IN                           (uint8)10U
#define APP_ALT11_IN                           (uint8)11U
#define APP_ALT12_IN                           (uint8)12U
#define APP_ALT13_IN                           (uint8)13U
#define APP_ALT14_IN                           (uint8)14U
#define APP_ALT15_IN                           (uint8)15U
#define APP_ALT16_IN                           (uint8)16U
#define APP_ALT1_OUT                           (uint8)1U
#define APP_ALT2_OUT                           (uint8)2U
#define APP_ALT3_OUT                           (uint8)3U
#define APP_ALT4_OUT                           (uint8)4U
#define APP_ALT5_OUT                           (uint8)5U
#define APP_ALT6_OUT                           (uint8)6U
#define APP_ALT7_OUT                           (uint8)7U
#define APP_ALT8_OUT                           (uint8)8U
#define APP_ALT9_OUT                           (uint8)9U
#define APP_ALT10_OUT                           (uint8)10U
#define APP_ALT11_OUT                           (uint8)11U
#define APP_ALT12_OUT                           (uint8)12U
#define APP_ALT13_OUT                           (uint8)13U
#define APP_ALT14_OUT                           (uint8)14U
#define APP_ALT15_OUT                           (uint8)15U
#define APP_ALT16_OUT                           (uint8)16U

/*******************************************************************************
*                       Global Variables                                      **
*******************************************************************************/
/* Array for Intr Reg information */
CONST(uint32, CAN_APPL_CONST) Can_GaaIntCntlRegsInfo[] =
{
  /* HW Unit: RSCAN0 */
  653UL, /* EIC297 (INTRCANGRECC0) */
  /* HW Unit: RSCAN1 */
  655UL, /* (INTRCANGRECC1) */
  /* HW Unit: RSCAN2 */
  657UL, /* (INTRCANGRECC2) */
  /* HW Unit: CAN0 */
  658UL, /* EIC658 (INTRCAN0ERR)   */
  659UL, /* EIC659 (INTRCAN0REC)   */
  660UL, /* EIC660 (INTRCAN0TRX)   */
  /* HW Unit: CAN1 */
  664UL, /* EIC664 (INTRCAN1ERR)   */
  665UL, /* EIC665 (INTRCAN1REC)   */
  666UL, /* EIC666 (INTRCAN1TRX)   */
  /* HW Unit: CAN2 */
  670UL, /* EIC670(INTRCAN2ERR)   */
  671UL, /* EIC670 (INTRCAN2REC)   */
  672UL, /* EIC672 (INTRCAN2TRX)   */
  /* HW Unit: CAN8 */
  1005UL, /* EIC1005 (INTRCAN8ERR)   */
  1006UL, /* EIC1006 (INTRCAN8REC)   */
  1007UL, /* EIC1007 (INTRCAN8TRX)   */
  
  /* HW Unit: CAN16 */
  612UL, /* EIC612 (INTRCAN16ERR)   */
  613UL, /* EIC613 (INTRCAN16REC)   */
  614UL  /* EIC614 (INTRCAN16TRX)   */

};

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
void Can_IvtInit(void);
void Port_Sub_Init(uint8 controller,
                   uint8 port_group_out, 
                   uint8 pin_out, uint8 alt_mode_out,
                   uint8 port_group_in,
                   uint8 pin_in, uint8 alt_mode_in);
/******************************************************************************
*                       Function Definitions                                  **
******************************************************************************/

/******************************************************************************
                              System Initialization
******************************************************************************/
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

#if 0
  /* 2.Confirm that the MainOSC is unstable (MOSCS.MOSCSTAB = 0). */
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

#if 0
  /* 2.Confirm that the PLL is unstable (PLLS.PLLCLKSTAB = 0). */
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
  CAN_WAIT_NS(100 * 1000); /* 100us */

  /* Start of repetitions: 5 repetitions (800MHz) */
  /* Division ratio of clock source PLL is changed from 3/8 to 4/8 */
  CKD_PLLC = 0x8U;
  (void)CKD_PLLC;
  EXECUTE_SYNCP();
  while ( (CKD_PLLS & (uint32)0x2) != (uint32)0x2U );
  CAN_WAIT_NS(100 * 1000); /* 100us */
  /* Division ratio of clock source PLL is changed from 4/8 to 5/8 */
  CKD_PLLC = 0xAU;
  (void)CKD_PLLC;
  EXECUTE_SYNCP();
  while ( (CKD_PLLS & (uint32)0x2) != (uint32)0x2U );
  CAN_WAIT_NS(100 * 1000); /* 100us */
  /* Division ratio of clock source PLL is changed from 5/8 to 6/8 */
  CKD_PLLC = 0xCU;
  (void)CKD_PLLC;
  EXECUTE_SYNCP();
  while ( (CKD_PLLS & (uint32)0x2) != (uint32)0x2U );
  CAN_WAIT_NS(100 * 1000); /* 100us */
  /* Division ratio of clock source PLL is changed from 6/8 to 7/8 */
  CKD_PLLC = 0xEU;
  (void)CKD_PLLC;
  EXECUTE_SYNCP();
  while ( (CKD_PLLS & (uint32)0x2) != (uint32)0x2U );
  CAN_WAIT_NS(100 * 1000); /* 100us */
  /* Division ratio of clock source PLL is changed from 7/8 to 1 */
  CKD_PLLC = 0x0U;
  (void)CKD_PLLC;
  EXECUTE_SYNCP();
  while ( (CKD_PLLS & (uint32)0x2) != (uint32)0x2U );
  CAN_WAIT_NS(100 * 1000); /* 100us */
  /* End of repetitions for PLL */
  
  /* -- Divider clock synchronized for SSCG -- */
  while ( (CKD_SSCGS & (uint32)0x2) != (uint32)0x2U ); /* Read CKD_SSCGS and verify that the value of SSCGCLKDSYNC is 1B */

  /* The clock source for the System clock is changed from CLK_IOSC to CLK_PLLO */
  CKS_SSCGC = (uint32)0x0U;
  (void)CKS_SSCGC;
  EXECUTE_SYNCP();

  /* Read CKS_SSCGS and verify that the value of SYSCLKSACT is 0B */
  while ( (CKS_SSCGS & (uint32)0x1U) != (uint32)0x0U );
  CAN_WAIT_NS(100 * 1000); /* 100us */

  /* Start of repetitions: 5 repetitions (800MHz) */
  /* Division ratio of clock source SSCG is changed from 3/8 to 4/8 */
  CKD_SSCGC = 0x8U;
  (void)CKD_SSCGC;
  EXECUTE_SYNCP();
  while ( (CKD_SSCGS & (uint32)0x2) != (uint32)0x2U );
  CAN_WAIT_NS(100 * 1000); /* 100us */
  /* Division ratio of clock source SSCG is changed from 4/8 to 5/8 */
  CKD_SSCGC = 0xAU;
  (void)CKD_SSCGC;
  EXECUTE_SYNCP();
  while ( (CKD_SSCGS & (uint32)0x2) != (uint32)0x2U );
  CAN_WAIT_NS(100 * 1000); /* 100us */
  /* Division ratio of clock source SSCG is changed from 5/8 to 6/8 */
  CKD_SSCGC = 0xCU;
  (void)CKD_SSCGC;
  EXECUTE_SYNCP();
  while ( (CKD_SSCGS & (uint32)0x2) != (uint32)0x2U );
  CAN_WAIT_NS(100 * 1000); /* 100us */
  /* Division ratio of clock source SSCG is changed from 6/8 to 7/8 */
  CKD_SSCGC = 0xEU;
  (void)CKD_SSCGC;
  EXECUTE_SYNCP();
  while ( (CKD_SSCGS & (uint32)0x2) != (uint32)0x2U );
  CAN_WAIT_NS(100 * 1000); /* 100us */
  /* Division ratio of clock source SSCG is changed from 7/8 to 1 */
  CKD_SSCGC = 0x0U;
  (void)CKD_SSCGC;
  EXECUTE_SYNCP();
  while ( (CKD_SSCGS & (uint32)0x2) != (uint32)0x2U );
  CAN_WAIT_NS(100 * 1000); /* 100us */
  /* End of repetitions for SSCG */

  /* Set the write protection of Clock controller */
  CLKKCPROT1 = DISABLE_WRITE_KEY_CODE;

  /**************/
  /* CAN Clock  */
  /**************/
  
  /* CLK_CANFD_C/CLK_CANFD_XIN Selector Control Register (CKS_RCANC.RCANXINSCSID = 1). */
  CLKKCPROT1  = ENABLE_WRITE_KEY_CODE;
  CKS_RCANC   = 0x00010001UL;
  CLKKCPROT1  = DISABLE_WRITE_KEY_CODE;
  
  /* CLKC_CANXL_CHn Selector Control Register (CLKC_CANXL_CHn.CANXLSCSID = 0100B). */
  CLKKCPROT1  = ENABLE_WRITE_KEY_CODE;
  CKS_CANXL0C   = 0x00000004UL;
  CLKKCPROT1  = DISABLE_WRITE_KEY_CODE;
  
  CLKKCPROT1  = ENABLE_WRITE_KEY_CODE;
  CKS_CANXL1C   = 0x00000004UL;
  CLKKCPROT1  = DISABLE_WRITE_KEY_CODE;
}

/* Perform the System initialization */
void Mcu_Init(void)
{
  /* Setup module standby controllers ========================================*/
  /* Disable protection for module standby registers */
  CAN_MSRKCPROT = CAN_KCPROT_SET;
  /* Enable RS-CAN module */
  CAN_MSR_RCAN = CAN_MSR_ACTIVE;
  while (CAN_MSR_RCAN != CAN_MSR_ACTIVE);
  /* Enable TAUD module */
  CAN_MSR_TAUD = CAN_MSR_ACTIVE;
  while (CAN_MSR_TAUD != CAN_MSR_ACTIVE);
  /* Enable protection for module standby registers */
  CAN_MSRKCPROT = CAN_KCPROT_CLR;

  /* Initialize EIC registers */
  Can_IvtInit();

#if 0
  /* Enable interrupts */
  __asm("ei");
#endif
}

/*******************************************************************************
**                      Watchdog Initialization                               **
*******************************************************************************/
void Wdg_Init(void)
{
  /* call the function */
}

/******************************************************************************
*                       Port Initialization                                  **
******************************************************************************/
void Switch_To_ControllerId(uint8 controller)
{
  uint32 LulCount;
  volatile P2VAR(Can_Port0RegSetType, AUTOMATIC, REGSPACE) LpReg;
  LpReg = (volatile Can_Port0RegSetType *)(PORT0_BASE_ADDRESS + (64 * (uint32)18));
  if(controller == 0)
  {
    LpReg->ulPSR    = 0xFFFFFFFE;
  }
  else 
  {
    LpReg->ulPSR    = 0xFFFFFFFF;
  }
  LulCount = 5000000;
  while (LulCount--);
}

/* Perform the CAN Port Pin Configuration */
void Port_Init(void)
{
  volatile P2VAR(Can_Port0RegSetType, AUTOMATIC, REGSPACE) LpReg;
  CAN_PKCPROT = CAN_KCPROT_SET;
  CAN_PWE     = 0x001FFFFEUL;
  LpReg = (volatile Can_Port0RegSetType *)(PORT0_BASE_ADDRESS + (64 * (uint32)21));
  LpReg->ulPSR    = 0xFFFF00FF;
  LpReg->ulPMSR    = 0xFFFFFFFF;
  LpReg->ulPMSR    = 0xFFFFFF00;
  Port_Sub_Init(0, 21, 4, APP_ALT4_OUT, 21, 5, APP_ALT4_IN);
  Port_Sub_Init(1, 4, 12, APP_ALT3_OUT, 4, 13, APP_ALT4_IN);
  Port_Sub_Init(8, 3, 10, APP_ALT2_OUT, 3, 11, APP_ALT2_IN);
  Port_Sub_Init(0, 20, 4, APP_ALT8_OUT, 20, 3, APP_ALT6_IN);
  Port_Sub_Init(1, 24, 7, APP_ALT5_OUT, 24, 8, APP_ALT5_IN);
  Port_Sub_Init(16, 30, 5, APP_ALT7_OUT, 30, 9, APP_ALT7_IN);
  CAN_PWE     = 0x00000000UL;
  CAN_PKCPROT = CAN_KCPROT_CLR;
}

void Port_Sub_Init(uint8 controller,
                   uint8 port_group_out, 
                   uint8 pin_out, uint8 alt_mode_out,
                   uint8 port_group_in,
                   uint8 pin_in, uint8 alt_mode_in)
{
  volatile P2VAR(Can_Port0RegSetType, AUTOMATIC, REGSPACE) LpReg;
  volatile P2VAR(Can_Port1RegSetType, AUTOMATIC, REGSPACE) LpReg1;
  uint32 LulCount;

  // out
  LpReg = (volatile Can_Port0RegSetType *)(PORT0_BASE_ADDRESS + (64 * (uint32)port_group_out));
  
  LpReg->usP     = (uint16)((LpReg->usP   & ~(1 << pin_out)) | (1U << pin_out));
  LpReg->usPMC   = (uint16)((LpReg->usPMC & ~(1 << pin_out)) | (1U << pin_out));
  LpReg->usPM    = (uint16) (LpReg->usPM  & ~(1 << pin_out));
  LpReg->ulPMCSR = ((1UL << pin_out) << 16U) | 0xFFFFUL;
  LpReg->ulPMSR  = ((1UL << pin_out) << 16U) | 0x0000UL;
  
  LpReg->usPFC   = (uint16)((LpReg->usPFC & ~(1 << pin_out))
                                            | (PFC_MASK(alt_mode_out) << pin_out));
  LpReg->usPFCE  = (uint16)((LpReg->usPFCE & ~(1 << pin_out))
                                            | (PFCE_MASK(alt_mode_out) << pin_out));
  LpReg->usPFCAE = (uint16)((LpReg->usPFCAE & ~(1 << pin_out))
                                            | (PFCAE_MASK(alt_mode_out) << pin_out));

  LpReg1 = (volatile Can_Port1RegSetType *)(PORT1_BASE_ADDRESS + (64 * (uint32)port_group_out));
  LpReg1->usPIPC  &= (uint16)(~(1U << pin_out));
  LpReg1->usPIBC  &= (uint16)(~(1U << pin_out));

  // in
  LpReg = (volatile Can_Port0RegSetType *)(PORT0_BASE_ADDRESS + (64 * (uint32)port_group_in));
  LpReg->usP     = (uint16)((LpReg->usP   & ~(1 << pin_in)) | (1U << pin_in));
  LpReg->usPMC   = (uint16)((LpReg->usPMC & ~(1 << pin_in)) | (1U << pin_in));
  LpReg->usPM    = (uint16)((LpReg->usPM  & ~(1 << pin_in)) | (1U << pin_in));
  LpReg->ulPMCSR = ((1UL << pin_in) << 16U) | 0xFFFFUL;
  LpReg->ulPMSR  = ((1UL << pin_in) << 16U) | 0xFFFFUL;

  LpReg->usPFC   = (uint16)((LpReg->usPFC & ~(1 << pin_in))
                                            | (PFC_MASK(alt_mode_in) << pin_in));
  LpReg->usPFCE  = (uint16)((LpReg->usPFCE & ~(1 << pin_in))
                                            | (PFCE_MASK(alt_mode_in) << pin_in));
  LpReg->usPFCAE = (uint16)((LpReg->usPFCAE & ~(1 << pin_in))
                                            | (PFCAE_MASK(alt_mode_in) << pin_in));

  LpReg1 = (volatile Can_Port1RegSetType *)(PORT1_BASE_ADDRESS + (64 * (uint32)port_group_out));
  LpReg1->usPIPC &= (uint16)(~(1U << pin_in));
  LpReg1->usPIBC &= (uint16)(~(1U << pin_in));

  LulCount = 1723*5000;/*temp*/
  while (LulCount--);/*temp*/
}


/*****************************************************************************
                          Timer Initialization
*****************************************************************************/
void Gpt_Init(void)
{
  /*
   * Timer count has to be loaded based on the system requirement. The value
   * provided here is just for reference and may not be suitable for
   * production purposes.
   */
#if 0
  /* Channel 0 Config: interval timer 1ms */
  /* Mode selection for Interval timer */
  /*  interval counter = 1ms/(1/40MHz) */
  CAN_OSTM0CMP  = 0x00009C40UL;
  /*  Enable interrupt, Interval timer mode */
  CAN_OSTM0CTL = 0x80UL;

  /* enable interrupt for OSTM channel 0, enable reference table jump */
  CAN_ICOSTM018 = 0x0040U;
  CAN_OSTM0TS = 0x01U;
#endif

  /* Only TAUD0 channel 0 is used.                            */
  /* Timer mode is interval timer mode and interval is 1[ms]. */
  /* PCLK = 80[MHz] is assumed.                               */
  CAN_TAUD0TT         = 0xFFFFU;          /* Stop all channels of TAUD0.      */
  CAN_TAUD0TPS        = 0x0001U;          /* Setting CK0 (PCLK/(2^1)->40MHz). */
  CAN_TAUD0CDR0       = (40000U - 1U);    /* 40000/40MHz -> 1ms.              */
  CAN_TAUD0CMOR0      = 0x0000U;          /* CK0, SW trigger and interval.    */

  CAN_EIC_INTTAUD0I0  = 0x004FU;          /* Enable INT(Table reference).     */

  CAN_TAUD0TS         = 0x0001U;          /* Start.                           */
}

void Gpt_Init_1(void)
{
  /*
   * Timer count has to be loaded based on the system requirement. The value
   * provided here is just for reference and may not be suitable for
   * production purposes.
   */
#if 0
  /* Channel 0 Config: interval timer 1ms */
  /* Mode selection for Interval timer */
  /*  interval counter = 1ms/(1/40MHz) */
  CAN_OSTM0CMP  = 0x00009C40UL;
  /*  Enable interrupt, Interval timer mode */
  CAN_OSTM0CTL = 0x80UL;

  /* enable interrupt for OSTM channel 0, enable reference table jump */
  CAN_ICOSTM018 = 0x0040U;
  CAN_OSTM0TS = 0x01U;
#endif

  /* Only TAUD2 channel 0 is used.                            */
  /* Timer mode is interval timer mode and interval is 1[ms]. */
  /* PCLK = 80[MHz] is assumed.                               */
  CAN_TAUD2TT         = 0xFFFFU;          /* Stop all channels of TAUD2.      */
  CAN_TAUD2TPS        = 0x0001U;          /* Setting CK0 (PCLK/(2^1)->40MHz). */
  CAN_TAUD2CDR0       = (40000U - 1U);    /* 40000/40MHz -> 1ms.              */
  CAN_TAUD2CMOR0      = 0x0000U;          /* CK0, SW trigger and interval.    */

  CAN_EIC_INTTAUD2I0  = 0x004FU;          /* Enable INT(Table reference).     */

  CAN_TAUD2TS         = 0x0001U;          /* Start.                           */
}

void Can_IvtInit(void)
{
  uint32 LulIndex;

  for (LulIndex = 0U;
    LulIndex < (uint32)(sizeof(Can_GaaIntCntlRegsInfo) / sizeof(uint32)); LulIndex++)
  {
    CAN_EIC[Can_GaaIntCntlRegsInfo[LulIndex]] =
      (CAN_EIMK | CAN_EITB | CAN_EIC_PRI);
  }
}

/*******************************************************************************
                          End of the file
*******************************************************************************/
