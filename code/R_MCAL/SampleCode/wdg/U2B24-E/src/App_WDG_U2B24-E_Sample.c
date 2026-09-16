/*============================================================================*/
/* Project      = RH850/X2x MCAL PF Development                               */
/* Module       = App_WDG_U2B24_Sample.c                                      */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2024-2025 Renesas Electronics Corporation. All rights reserved.        */
/*============================================================================*/
/* Purpose:                                                                   */
/* This file contains the sample application of WDG Component Driver.         */
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
/*              Devices:        U2B24                                         */
/*============================================================================*/

/*******************************************************************************
**                      Revision Control History                              **
*******************************************************************************/
/*
 * 2.4.1:  30/06/2025    : Remove SW-VERSION in file header 
 * 2.3.2:  29/04/2025    : Update SW-VERSION for RH850/Ver22.00.03 U2Bx-E
 * 2.3.1:  31/03/2025    : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 *                         Added guard for handling PE
 * 2.3.0:  31/01/2025    : Update SW-VERSION for Ver22.00.06 U2Cx Beta Release
 * 2.2.0:  31/12/2024    : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D
 *                         Final release
 * 2.1.2:  30/10/2024    : Update SW-VERSION to 2.1.2
 * 2.1.1:  31/08/2024    : Update SW-VERSION to 2.1.1
 *                       : Initial Version
 */
/******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "App_Wdg_Device_Sample.h"

/*******************************************************************************
**                         Global Data                                        **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
/*******************************************************************************
**                      PBG Initialization                                    **
*******************************************************************************/

void PBG_Init(void)
{
   PBGKCPROT11 = WDG_KCPROT_SET;
   PBGKCPROT50 = WDG_KCPROT_SET;
   PBGKCPROT20 = WDG_KCPROT_SET;

   PBG11PROT0(10) |= 0x00000143UL;
   PBG51PROT0(2) |= 0x00000143UL;
   PBG51PROT0(3) |= 0x00000143UL;
   PBG50PROT0(8) |= 0x00000143UL;
   PBG20PROT0(11) |= 0x00000143UL;
   PBG20PROT0(8) |= 0x00000143UL;
   
   PBGKCPROT11 = WDG_KCPROT_CLR;
   PBGKCPROT50 = WDG_KCPROT_CLR;
   PBGKCPROT20 = WDG_KCPROT_CLR;
}


/*******************************************************************************
**                      Mcu Initialization                                    **
*******************************************************************************/

void Mcu_Init(void)
{	
    PBG_Init();
    /* Enable write protection */
    CLKKCPROT1 = WDG_KCPROT_SET;

    /* Initialize MCU clock for WDTBn: 10 Mhz */
    CKSC_WDTC = (CKSC_WDTC & 0x00);

    /* Initialize MCU clock for WDTBA: 240 kHz */
    CKSC_AWDTC = (CKSC_AWDTC & 0x00);

    /* Disable write protection */
    CLKKCPROT1 = WDG_KCPROT_CLR;
}

/*******************************************************************************
**                      Port Initialization                                   **
*******************************************************************************/
void Port_Init(void)
{

}

/*******************************************************************************
**                    Interrupt Initialization                                **
*******************************************************************************/
void Interrupt_Init(void)
{
  /* Set Reference Table Method for WDTBn (INTWDTBnTIT) */
  /* WDTB0..6 */
  EIC22_PE0 |= (1 << 6);
  EIC22_PE1 |= (1 << 6);
  EIC22_PE2 |= (1 << 6);
  EIC22_PE3 |= (1 << 6);
  EIC22_PE4 |= (1 << 6);
  EIC22_PE5 |= (1 << 6);
  EIC22_PE6 |= (1 << 6);
  /* WDTBA */
  EIC981 |= (1 << 6);
  /* Enable interrupt for all */
  ENABLE_INTERRUPT();
}
/*******************************************************************************
**                    Guard for enabling PE                                   **
*******************************************************************************/
void Guard_Enable_PE(void)
{
  /* Binded to PE0 & PE1  */
  #if defined(RUN_OTHER_PE)
  INTC1_EIBD22  = 6;
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
  (uint32) 0xFFC83040UL, //PBGERRSLV62_base
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
  (uint32) 0xFF860000UL, //PBG_CANFD0_base
  (uint32) 0xFF860800UL, //PBG_CANFD1_base
  (uint32) 0xFF88FA00UL, //PBG_ATU_base
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
    for (int ii =0; ii<16;ii++)
    {
      volatile uint32 *ptr;
      ptr = (volatile uint32 *)(PBGXX_base[i] + ((uint32)ii * 0x8UL));
      *ptr |= 0x00000143UL;
    }
  }

  //Write PBG1
  for (int i =0; i<39;i++)
  {
    for (int ii =0; ii<16;ii++)
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
**                         End of file                                        **
*******************************************************************************/
