/*============================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                         */
/* Module       = App_MEM_U2B6_Sample.c                                       */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2025 Renesas Electronics Corporation. All rights reserved.             */
/*============================================================================*/
/* Purpose:                                                                   */
/* This file contains sample application for MEM Driver Component             */
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
/*              Devices:        U2B12-E                                       */
/*============================================================================*/

/*******************************************************************************
**                      Revision Control History                              **
*******************************************************************************/
/*
 * 1.0.2:  31/03/2025  : Initial Version.
*                        As part of G4KH U2Bx-E support, the following are made:
 *                        + Add function Guard_Enable_PE
 */
/******************************************************************************/

/*******************************************************************************
**                     Include Section                                        **
*******************************************************************************/
#include "App_Mem_Device_Sample.h"

/*******************************************************************************
**                      ISR Defines                                           **
*******************************************************************************/
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
  (uint32) 0xffc83040UL, //PBGERRSLV62_base
  (uint32) 0xFFF4A000UL, //PBGERRSLV70_base
  (uint32) 0xFFF2A000UL, //PBGERRSLV8H0_base
  (uint32) 0xFFF6D480UL, //PBGERRSLV8M0_base
  (uint32) 0xFF97A200UL, //PBGERRSLV8L0_base
  (uint32) 0xFFF6E080UL, //PBGERRSLV8UL0_base
  (uint32) 0xFF0A1400UL, //PBGERRSLV90_base
  (uint32) 0xFF0A1600UL, //PBGERRSLV91_base-
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
  (uint32) 0xFF860000UL, //PBG_CANFD0_base
  (uint32) 0xFF860800UL, //PBG_CANFD1_base
  (uint32) 0xFF861000UL, //PBG_CANFD2_base
  (uint32) 0xFFF60000UL  //PBG_GTM_base
  };

  //Enable write
  for (int i =0; i<18;i++)
  {
  volatile uint32 *ptr;
  ptr = (volatile uint32 *)(RSLVXX_base[i] + (uint32)0x18UL);
  *ptr = (uint32)0xA5A5A501UL;
  }

  //Write PBG0
  for (int i =0; i<39;i++)
  {
    for (int ii =0; ii<18;ii++)
    {
      volatile uint32 *ptr;
      ptr = (volatile uint32 *)(PBGXX_base[i] + ((uint32)ii * 0x8UL));
      *ptr |= 0x00000143UL;
    }
  }

  //Write PBG1
  for (int i =0; i<39;i++)
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
/*******************************************************************************
**                      Watchdog Initialization                               **
*******************************************************************************/
void Wdg_Init(void)
{
  /* No action required */
}

/*******************************************************************************
**                      MCU Initialization                                  **
*******************************************************************************/
void Mcu_Init(void)
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
  CLKKCPROT1  = MEM_59_RENESAS_KCPROT_SET;
  HSOSCSTPM   = 0x00000000UL;
  CLKKCPROT1  = MEM_59_RENESAS_KCPROT_CLR;

  /* HSIntOSC stops operation in stand-by mode(HSOSCSTPM.MOSCSTPMSK = 0). */
  CLKKCPROT1  = MEM_59_RENESAS_KCPROT_SET;
  HSOSCSTPM   = 0x00000000UL;
  CLKKCPROT1  = MEM_59_RENESAS_KCPROT_CLR;

  /* 1.Confirm that the HSIntOSC is stable (HSOSCS.HSOSCSTAB = 1). */
  /* (Checked) **/

#if 0
  /* 2.Confirm that the MainOSC is unstable (MOSCS.MOSCSTAB = 0). */
  while ( (MOSCS & 0x00000002UL) != 0x00000000UL )
  {
  }
#endif

  /* 3.Start the MainOSC (MOSCE.MOSCENTRG = 1). */
  CLKKCPROT1  = MEM_59_RENESAS_KCPROT_SET;
  MOSCE       = 0x00000001UL;
  CLKKCPROT1  = MEM_59_RENESAS_KCPROT_CLR;

  /* 4.Confirm that the MainOSC has been started (MOSCS.MOSCSTAB = 1). */
  while ( (MOSCS & 0x00000002UL) != 0x00000002UL )
  {
  }

  /* MainOSC stops operation in stand-by mode(MOSCSTPM.MOSCSTPMSK = 0). */
  CLKKCPROT1  = MEM_59_RENESAS_KCPROT_SET;
  MOSCSTPM    = 0x00000000UL;
  CLKKCPROT1  = MEM_59_RENESAS_KCPROT_CLR;

  /************************************************/
  /* PLL                                          */
  /* - OPBT11.CKDIVMD = 11b is needed.            */
  /************************************************/

  /* 1.Confirm that the MainOSC is stable (MOSCS.MOSCSTAB = 1). */
  /* (Checked) **/

#if 0
  /* 2.Confirm that the PLL is unstable (PLLS.PLLCLKSTAB = 0). */
  while ( (PLLS & 0x00000002UL) != 0x00000000UL )
  {
  }
#endif

  /* 3.Start the PLL (PLLE.PLLENTRG = 1). */
  CLKKCPROT1  = MEM_59_RENESAS_KCPROT_SET;
  PLLE        = 0x00000001UL;
  CLKKCPROT1  = MEM_59_RENESAS_KCPROT_CLR;

  /* 4.Confirm that the PLL has been started      */
  /* (PLLS.PLLCLKSTAB = 1 and PLLS.PLLCLKEN = 1). */
  while ( (PLLS & 0x00000003UL) != 0x00000003UL )
  {
  }

  /* PLL stops operation in stand-by mode(PLLSTPM.PLLSTPMSK = 0) */
  CLKKCPROT1  = MEM_59_RENESAS_KCPROT_SET;
  PLLSTPM     = 0x00000000UL;
  CLKKCPROT1  = MEM_59_RENESAS_KCPROT_CLR;

  /* Select a source clock(CKSC_CPUC.CPUCLKSCSID = 0). */
  CLKKCPROT1  = MEM_59_RENESAS_KCPROT_SET;

  /* Selected Clock source ID=0:CLK_PLLO */
  /* (This setting dependencies Option Bytes. CKDIVMD = 11B) */
  CKSC_CPUC   = 0x00000000UL;
  CLKKCPROT1  = MEM_59_RENESAS_KCPROT_CLR;

  /* Confirm completion of selection(CKSC_CPUS.CPUCLKSACT = 1). */
  while ( (CKSC_CPUS & 0x00000001UL) != 0x00000000UL )
  {
  }
}


/*******************************************************************************
**                      Port Initialization                                   **
*******************************************************************************/
void Port_Init(void)
{
  /* No action required */
}

/******************************************************************************
**                          End of File                                      **
*******************************************************************************/
