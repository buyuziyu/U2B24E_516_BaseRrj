/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2X MCAL Components                                                                 */
/* Module       = App_OCU_U2B12-E_Sample.c                                                                            */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2024,2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains sample application for OCU Driver Component                                                     */
/*                                                                                                                    */
/*====================================================================================================================*/
/*                                                                                                                    */
/* Unless otherwise agreed upon in writing between your company and Renesas Electronics Corporation the following     */
/* shall apply!                                                                                                       */
/*                                                                                                                    */
/* Warranty Disclaimer                                                                                                */
/*                                                                                                                    */
/* There is no warranty of any kind whatsoever granted by Renesas. Any warranty is expressly disclaimed and excluded  */
/* by Renesas, either expressed or implied, including but not limited to those for non-infringement of intellectual   */
/* property, merchantability and/or fitness for the particular purpose.                                               */
/*                                                                                                                    */
/* Renesas shall not have any obligation to maintain, service or provide bug fixes for the supplied Product(s) and/or */
/* the Application.                                                                                                   */
/*                                                                                                                    */
/* Each User is solely responsible for determining the appropriateness of using the Product(s) and assumes all risks  */
/* associated with its exercise of rights under this Agreement, including, but not limited to the risks and costs of  */
/* program errors, compliance with applicable laws, damage to or loss of data, programs or equipment, and             */
/* unavailability or interruption of operations.                                                                      */
/*                                                                                                                    */
/* Limitation of Liability                                                                                            */
/*                                                                                                                    */
/* In no event shall Renesas be liable to the User for any incidental, consequential, indirect, or punitive damage    */
/* (including but not limited to lost profits) regardless of whether such liability is based on breach of contract,   */
/* tort, strict liability, breach of warranties, failure of essential purpose or otherwise and even if advised of the */
/* possibility of such damages. Renesas shall not be liable for any services or products provided by third party      */
/* vendors, developers or consultants identified or referred to the User by Renesas in connection with the Product(s) */
/* and/or the Application.                                                                                            */
/*                                                                                                                    */
/*====================================================================================================================*/
/* Environment:                                                                                                       */
/*              Devices:        X2x                                                                                   */
/*====================================================================================================================*/

/***********************************************************************************************************************
**                                              Revision Control History                                              **
***********************************************************************************************************************/
/*
 * 1.4.1:  30/06/2025    : Update Guard_Enable_PE function for support GTM and sample app on core 6
 * 1.4.0   30/05/2025    : Add interrupt definition, enable clock source, port pin to testing GTM channel
 * 1.3.1:  31/03/2025    : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 and RH850/U2Bx-E MCAL Ver22.00.02 Release
 *                         As part of support U2Bx-E SampleApp on G4KH, following changes are made:
 *                         1. Add function Guard_Enable_PE
 * 1.3.0:  31/03/2025    : As part of support U2Bx-E in sample app, following changes are made:
 *                         1. Update Port_Init for TAUJ2O1, TAUJ2O3
 * 1.2.0:  31/12/2024    : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 * 1.0.3:  22/04/2024    : Initial Version.
 *         18/05/2024    : Add GaaListChannel
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
#include "Std_Types.h"
#include "App_OCU_Device_Sample.h"
#include "Ocu_Cfg.h"

/***********************************************************************************************************************
**                                                      Macros                                                        **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                   Global variables                                                 **
***********************************************************************************************************************/
uint32 RenICRADRR[] = {

  /* TAUJ2 (x2) */
  OCU_EIC_ADDR(961UL),
  OCU_EIC_ADDR(963UL),

  /* ATOM0/TOM0*/
  OCU_EIC_ADDR(86UL),
  OCU_EIC_ADDR(87UL)
};

/* Array of testing channels*/
uint8 GaaListChannel[5] = {0, 1, 3, 4, 5};
/***********************************************************************************************************************
**                                               User function prototypes                                             **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Function Definitions                                              **
***********************************************************************************************************************/

/* Function for Mcu clock settings */
void Mcu_Init(void)
{
  /* Release the write protection of Standby controller register.*/
  MSRKCPROT = ENABLE_WRITE_KEY_CODE;

  /* Enable clock source for TAUJ unit TAUJ2 */
  MSR_TAUJ &= 0xFFFFFFFCUL;

  /* Enable clock source for OSTM0 */
  MSR_OSTM &= 0xFFFFFFFEUL;

  #if (OCU_TIMER_IP_GTM == STD_ON)
  /* Enable clock source GTM */
  MSR_GTM  = 0;
  /* Wait for stable GTM clock */
  while (MSR_GTM != 0);
  /* CMU_GCLK_NUM value */
  CMU_GCLK_NUM = 1;
  /* CMU_GCLK_DEN value */
  CMU_GCLK_DEN = 1;
  /* Enable CMU */
  GTM0CMUCLKEN = 0x00AAAAAAUL;
  #endif

  /* Set the write protection of Standby controller registers. */
  MSRKCPROT = DISABLE_WRITE_KEY_CODE;
}

void Clock_Init(void)
{
  /* Wait to HSIntOSC clock is stable(HSOSCS.HSOSCSTAB = 1). */
  while ( (HSOSCS & 0x00000002ul) != 0x00000002ul )
  {
  }

  /* HSIntOSC stops operation in stand-by mode(HSOSCSTPM.MOSCSTPMSK = 0). */
  CLKKCPROT1  = ENABLE_WRITE_KEY_CODE;
  HSOSCSTPM   = 0x00000000UL;
  CLKKCPROT1  = DISABLE_WRITE_KEY_CODE;

  /***********/
  /* MainOSC */
  /***********/

  /* Start the MainOSC (MOSCE.MOSCENTRG = 1). */
  CLKKCPROT1  = ENABLE_WRITE_KEY_CODE;
  MOSCE       = 0x00000001ul;
  CLKKCPROT1  = DISABLE_WRITE_KEY_CODE;

  /* Confirm that the MainOSC has been started (MOSCS.MOSCSTAB = 1). */
  while ( (MOSCS & 0x00000002ul) != 0x00000002ul )
  {
  }

  /* MainOSC stops operation in stand-by mode(MOSCSTPM.MOSCSTPMSK = 0). */
  CLKKCPROT1  = ENABLE_WRITE_KEY_CODE;
  MOSCSTPM    = 0x00000000UL;
  CLKKCPROT1  = DISABLE_WRITE_KEY_CODE;

  /* Start the PLL (PLLE.PLLENTRG = 1). */
  CLKKCPROT1  = ENABLE_WRITE_KEY_CODE;
  PLLE        = 0x00000001ul;
  CLKKCPROT1  = DISABLE_WRITE_KEY_CODE;

  /* 4.Confirm that the PLL has been started (PLLS.PLLCLKSTAB = 1). */
  while ( (PLLS & 0x00000002ul) != 0x00000002ul )
  {
  }

  /* PLL stops operation in stand-by mode(PLLSTPM.PLLSTPMSK = 0) */
  CLKKCPROT1  = ENABLE_WRITE_KEY_CODE;
  PLLSTPM     = 0x00000000ul;
  CLKKCPROT1  = DISABLE_WRITE_KEY_CODE;

  /* Select a source clock(CKSC_CPUC.CPUCLKSCSID = 0). */
  CLKKCPROT1  = ENABLE_WRITE_KEY_CODE;
  /* Selected Clock source ID=0:CLK_PLLO */
  /* (This setting dependencies Option Bytes. CKDIVMD = 11B) */
  CKSC_CPUC   = 0x00000000ul;
  CLKKCPROT1  = DISABLE_WRITE_KEY_CODE;

  /* Confirm completion of selection(CKSC_CPUS.CPUCLKSACT = 0). */
  while ( (CKSC_CPUS & 0x00000001ul) != 0x00000000ul )
  {
  }

  /* Select CLKC_HSB as clock source for TAUJ2 */
  CLKKCPROT1  = ENABLE_WRITE_KEY_CODE;
  CKS_ATAUJC |= 0x4UL;
  CLKKCPROT1  = DISABLE_WRITE_KEY_CODE;
}
/* Function for the initialization of the Port pins */
void Port_Init(void)
{
  /*                             | PFCEAE PFCAE PFCE PFC | PM | PMC |  */
  /* P15_09_ALT_OUT16 (TAUJ2O1)  |    1     1    1    1  | 0  |  1  |  */
  /* P22_09_ALT_OUT15 (TAUJ2O3)  |    1     1    1    0  | 0  |  1  |  */
  /* P02_08_ALT_OUT8  (ATOM00)   |    0     1    1    1  | 0  |  1  |  */
  /* P02_01_ALT_OUT8  (ATOM01)   |    0     1    1    1  | 0  |  1  |  */
  /* P10_07_ALT_OUT8  (TOM00)    |    0     1    1    1  | 0  |  1  |  */
  /* P14_06_ALT_OUT7  (TOM01)    |    0     1    1    0  | 0  |  1  |  */

  /* Port set alt out mode for pin P15_09 mode ATL_OUT16 channel TAUJ2O1 ouput symbol 'TAUJ2O1' */
  OCU_PFCEAE(15) |= (uint16)(1u<<9);
  OCU_PFCAE(15)  |= (uint16)(1u<<9);
  OCU_PFCE(15)   |= (uint16)(1u<<9);
  OCU_PFC(15)    |= (uint16)(1u<<9);
  OCU_PM(15)     &= (uint16)(~(1u<<9));
  OCU_PMC(15)    |= (uint16)(1u<<9);

  /* Port set alt out mode for pin P22_09 mode ATL_OUT16 channel TAUJ2O3 ouput symbol 'TAUJ2O3' */
  OCU_PFCEAE(22) |= (uint16)(1u<<9);
  OCU_PFCAE(22)  |= (uint16)(1u<<9);
  OCU_PFCE(22)   |= (uint16)(1u<<9);
  OCU_PFC(22)    &= (uint16)(~(1u<<9));
  OCU_PM(22)     &= (uint16)(~(1u<<9));
  OCU_PMC(22)    |= (uint16)(1u<<9);
  
    /* Port set alt out mode for pin P02_08 mode ATL_OUT8 channel ATOM00 ouput symbol 'ATOM00' */
  OCU_PFCEAE(2) &= (uint16)~(1u<<8);
  OCU_PFCAE(2)  |= (uint16)(1u<<8);
  OCU_PFCE(2)   |= (uint16)(1u<<8);
  OCU_PFC(2)    |= (uint16)(1u<<8);
  OCU_PM(2)     &= (uint16)~(1u<<8);
  OCU_PMC(2)    |= (uint16)(1u<<8);

  /* Port set alt out mode for pin P02_01 mode ATL_OUT8 channel ATOM01 ouput symbol 'ATOM01' */
  OCU_PFCEAE(2) &= (uint16)~(1u<<1);
  OCU_PFCAE(2)  |= (uint16)(1u<<1);
  OCU_PFCE(2)   |= (uint16)(1u<<1);
  OCU_PFC(2)    |= (uint16)(1u<<1);
  OCU_PM(2)     &= (uint16)~(1u<<1);
  OCU_PMC(2)    |= (uint16)(1u<<1);

  /* Port set alt out mode for pin P10_07 mode ATL_OUT8 channel TOM000 ouput symbol 'TOM000' */
  OCU_PFCEAE(10) &= (uint16)~(1u<<7);
  OCU_PFCAE(10)  |= (uint16)(1u<<7);
  OCU_PFCE(10)   |= (uint16)(1u<<7);
  OCU_PFC(10)    |= (uint16)(1u<<7);
  OCU_PM(10)     &= (uint16)~(1u<<7);
  OCU_PMC(10)    |= (uint16)(1u<<7);

  /* Port set alt out mode for pin P14_06 mode ATL_OUT7 channel TOM001 ouput symbol 'TOM001' */
  OCU_PFCEAE(14) &= (uint16)~(1u<<6);
  OCU_PFCAE(14)  |= (uint16)(1u<<6);
  OCU_PFCE(14)   |= (uint16)(1u<<6);
  OCU_PFC(14)    &= (uint16)~(1u<<6);
  OCU_PM(14)     &= (uint16)~(1u<<6);
  OCU_PMC(14)    |= (uint16)(1u<<6);
}

/* Function for Watchdog settings */
void Wdg_Init(void)
{
  /* No Wdg initialization required */
}

void Reg_Init(void)
{
    volatile uint16 *ptr;
    uint32 count;
    for (count = 0; count < sizeof(RenICRADRR)/sizeof(RenICRADRR[0]); count++)
    {
        ptr = (volatile uint16 *)RenICRADRR[count];
        *ptr = (*ptr | 0x004F);
    }
}

void App_Ocu_Start_Timer0(uint32 ulPeriod)
{
  /* Only OSTM0 is used */
  /* Mode selection for Interval timer, Interval counter = 1[ms]/(1/80[MHz]) */
  OCU_OSTM0CMP = 80*ulPeriod;
  /* Enable interrupt, Interval timer mode */
  OCU_OSTM0CTL = 0x80U;
  /* Interrupt for OSTM0, Enable interrupt*/
  *(volatile uint16 *)OCU_EIC_ADDR(360) &= 0x7FU;
  /* Interrupt for OSTM0, Enable reference table jump */
  *(volatile uint16 *)OCU_EIC_ADDR(360) |= 0x4FU;
  /* Start OSTM0 */
  OCU_OSTM0TS = 0x01U;
}

void Guard_Enable_PE(void)
{

  /* Bound interrupt to core 6 */
  #if defined (RUN_OTHER_PE)
  /* TAUD1O1 */
  INTC2_EIBD(961) = 6;
  /* TAUJ2O1 */
  INTC2_EIBD(963) = 6;
  /* ATOM0x */
  INTC2_EIBD(86) = 6;
  /* TOM0x */
  INTC2_EIBD(87) = 6;
  #endif

  const uint32 RSLVXX_base[]=
  {
  (uint32) 0xFFC6B000UL, //PBGERRSLV00_base
  (uint32) 0xFFC63100UL, //PBGERRSLV10_base
  (uint32) 0xFFDE1000UL, //PBGERRSLV20_base
  (uint32) 0xFFC73200UL, //PBGERRSLV30_base
  (uint32) 0xFFC75400UL, //PBGERRSLV40_base
  (uint32) 0xFFC7B000UL, //PBGERRSLV50_base
  (uint32) 0xFFC83000UL, //PBGERRSLV60_base
  (uint32) 0xffc83040UL, //PBGERRSLV62_base
  (uint32) 0xFFF4A000UL, //PBGERRSLV70_base
  (uint32) 0xFFF2A000UL, //PBGERRSLV8H0_base
  (uint32) 0xFFF6D480UL, //PBGERRSLV8M0_base
  (uint32) 0xFF97A200UL, //PBGERRSLV8L0_base
  (uint32) 0xFFF6E080UL, //PBGERRSLV8UL0_base
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
  (uint32) 0xFFF6D400UL, //PBG8M0_base
  (uint32) 0xFF97A000UL, //PBG8L0_base
  (uint32) 0xFF97A100UL, //PBG8L1_base
  (uint32) 0xFFF6E000UL, //PBG8UL0_base
  (uint32) 0xFF0A1300UL, //PBG90_base
  (uint32) 0xFF0A1500UL, //PBG91_base
  (uint32) 0xFF0A1700UL, //PBG92_base
  (uint32) 0xFF879400UL, //PBG100_base
  (uint32) 0xFF879500UL, //PBG101_base
  (uint32) 0xFF8B1400UL, //PBG11H0_base
  (uint32) 0xFF8B1600UL, //PBG11H1_base
  (uint32) 0xFF8B1800UL, //PBG11H2_base
  (uint32) 0xFF8F8000UL, //PBG11L0_base
  };

  //Enable write
  for (int i =0; i<18;i++)
  {
  volatile uint32 *ptr;
  ptr = (volatile uint32 *)(RSLVXX_base[i] + (uint32)0x18UL);
  *ptr = (uint32)0xA5A5A501UL;
  }

  //Write PBG0
  for (int i =0; i<35;i++)
  {
    for (int ii =0; ii<18;ii++)
    {
      volatile uint32 *ptr;
      ptr = (volatile uint32 *)(PBGXX_base[i] + ((uint32)ii * 0x8UL));
      *ptr |= 0x00000143UL;
    }
  }

  //Write PBG1
  for (int i =0; i<35;i++)
  {
    for (int ii =0; ii<18;ii++)
    {
      volatile uint32 *ptr;
      ptr = (volatile uint32 *)(PBGXX_base[i] + 0x4UL + ((uint32)ii * 0x8UL));
      *ptr |= 0xFFFFUL;
    }
  }

  //Disable write
  for (int i =0; i<18;i++)
  {
  volatile uint32 *ptr;
  ptr = (volatile uint32 *)(RSLVXX_base[i]+0x18UL);
  *ptr = 0xA5A5A500UL;
  }
  
}

void App_Ocu_Stop_Timer0(void)
{
  /* Stop OSTM0 */
  OCU_OSTM0TT = 0x01U;
}

void Mcal_Ocu_Init(void)
{
  /* Initialize Clock */
  Clock_Init();

  /* Initialize MCU */
  Mcu_Init();

  /* Initialize the Port pins */
  Port_Init();

  /* Initialization of the table reference bit in ICR register */
  Reg_Init();

  /* Initialize the Watchdog timer */
  Wdg_Init();

  /* Enable interrupt using EI instruction */
  ENABLE_INTERRUPT();
}
/***********************************************************************************************************************
**                                                 Notification function                                              **
***********************************************************************************************************************/


/***********************************************************************************************************************
**                                                       End of File                                                  **
***********************************************************************************************************************/
