/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas U2B12E MCAL Components                                                              */
/* Module       = App_Adc_U2B12-E_Sample.c                                                                            */
/*====================================================================================================================*/
/*                                  COPYRIGHT                                                                         */
/*====================================================================================================================*/
/* (c) 2024,2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains sample application for ADC Driver Component                                                     */
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
/*              Devices:        U2B12E                                                                                */
/*====================================================================================================================*/

/***********************************************************************************************************************
**                      Revision Control History                                                                      **
***********************************************************************************************************************/
/*
 * 2.5.1:  30/06/2025 : Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.03 release
 *                      Remove SW-VERSION in file header
 * 2.3.1:  31/03/2025 : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 *                      As part of support U2Bx-E SampleApp on G4KH, following changes are made:
 *                      1. Add Guard_Enable_PE() and update Adc_Set_EI_Bind_PE6()
 * 2.3.0:  19/12/2024 : Initial Version
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                      Include Section                                                                               **
***********************************************************************************************************************/
#include "App_ADC_Device_Sample.h"
#include "Platform_Types.h"
#include "App_ADC_Multi_Sample.h"

/***********************************************************************************************************************
**                      Macros                                                                                        **
***********************************************************************************************************************/
#define ADC_CPUCLK_MHZ 400UL
#define ADC_WAIT_NS(t)  { volatile uint32 cnt; \
 for ( cnt = 0;cnt < ((((uint32)ADC_CPUCLK_MHZ * ((uint32)t)) / (uint32)1000) + (uint32)1);cnt++ ); }

/***********************************************************************************************************************
**                      ISR Defines                                                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                      Clock Initialization                                                                          **
***********************************************************************************************************************/
void Clock_Init(void)
{
  /* Wait to HSIntOSC clock is stable */
  while ((HSOSCS & 0x00000002UL) != 0x00000002UL)
  {
  }
  /* Release the write protection of Clock controller register */
  CLKKCPROT1  = ADC_KCPROT_SET;

  /* Confirm if Main OSC is stable */
  if ((MOSCS & 0x00000002UL) == 0x00000000UL)
  {
    /* Start the MainOSC (MOSCE.MOSCENTRG = 1). */
    MOSCE       = 0x00000001UL;
    /* Confirm that the MainOSC has been started (MOSCS.MOSCSTAB = 1). */
    while ( (MOSCS & 0x00000002UL) != 0x00000002UL )
    {
    }
  }

  /* Confirm if PLL/SSCG/SSCG1 are stable */
  if ((PLLS & 0x00000002UL) == 0x00000000UL)
  {
    /**/
    PLLE        = 0x00000001UL;
    /* Confirm that the PLL/SSCG/SSCG1 has been started. */
    while ( (PLLS & 0x00000002UL) != 0x00000002UL )
    {
    }
  }

  /* Start Clock Gear Up sequence */
  /* 1. Division ratio of clock source PLL/SSCG/SSCG1 is changed from 1/1 to 3/8 */
  CKD_PLLC = 0x6U;
  CKD_SSCGC = 0x6U;

  /* Confirm that the value of CLKDSYNC is 1B. */
  while ((CKD_PLLS & 0x00000002UL) != 0x00000002UL)
  {
  }
  while ((CKD_SSCGS & 0x00000002UL) != 0x00000002UL)
  {
  }

  /* 2. The clock source for the System clock is changed from CLK_IOSC to CLK_PLLO/CLK_SSCGO/CLK_SSCG1O */
  CKS_CLEANC = 0x0U;
  CKS_SSCGC = 0x0U;

  /* Confirm that the value of CLKSACT is 0B. (Wait 100us after verifying) */
  while ((CKS_CLEANS & 0x00000001UL) != 0x00000000UL)
  {
  }
  /* 100us */
  ADC_WAIT_NS(100 * 1000);

  while ((CKS_SSCGS & 0x00000001UL) != 0x00000000UL)
  {
  }
  /* 100us */
  ADC_WAIT_NS(100 * 1000);

  /* start of repetitions(5 repetitions) */
  /* 3. Division ratio of clock source PLL/SSCG/SSCG1 is changed from 3/8 to 1 */
  /* PLL */

  /* Division ratio of clock source PLL is changed from 3/8 to 4/8 */
  CKD_PLLC = 0x8U;
  while ((CKD_PLLS & 0x00000002UL) != 0x00000002UL)
  {
  }
  ADC_WAIT_NS(100 * 1000);

  /* Division ratio of clock source PLL is changed from 4/8 to 5/8 */
  CKD_PLLC = 0xAU;
  while ((CKD_PLLS & 0x00000002UL) != 0x00000002UL)
  {
  }
  ADC_WAIT_NS(100 * 1000);

  /* Division ratio of clock source PLL is changed from 5/8 to 6/8 */
  CKD_PLLC = 0xCU;
  while ((CKD_PLLS & 0x00000002UL) != 0x00000002UL)
  {
  }
  ADC_WAIT_NS(100 * 1000);

  /* Division ratio of clock source PLL is changed from 6/8 to 7/8 */
  CKD_PLLC = 0xEU;
  while ((CKD_PLLS & 0x00000002UL) != 0x00000002UL)
  {
  }
  ADC_WAIT_NS(100 * 1000);

  /* Division ratio of clock source PLL is changed from 7/8 to 1 */
  CKD_PLLC = 0x0U;
  while ((CKD_PLLS & 0x00000002UL) != 0x00000002UL)
  {
  }
  ADC_WAIT_NS(100 * 1000);
  /* End of repetitions for PLL */

  /* SSCG */

  /* Division ratio of clock source SSCG is changed from 3/8 to 4/8 */
  CKD_SSCGC = 0x8U;
  while ((CKD_SSCGS & 0x00000002UL) != 0x00000002UL)
  {
  }
  ADC_WAIT_NS(100 * 1000);

  /* Division ratio of clock source SSCG is changed from 4/8 to 5/8 */
  CKD_SSCGC = 0xAU;
  while ((CKD_SSCGS & 0x00000002UL) != 0x00000002UL)
  {
  }
  ADC_WAIT_NS(100 * 1000);

  /* Division ratio of clock source SSCG is changed from 5/8 to 6/8 */
  CKD_SSCGC = 0xCU;
  while ((CKD_SSCGS & 0x00000002UL) != 0x00000002UL)
  {
  }
  ADC_WAIT_NS(100 * 1000);

  /* Division ratio of clock source SSCG is changed from 6/8 to 7/8 */
  CKD_SSCGC = 0xEU;
  while ((CKD_SSCGS & 0x00000002UL) != 0x00000002UL)
  {
  }
  ADC_WAIT_NS(100 * 1000);

  /* Division ratio of clock source SSCG is changed from 7/8 to 1 */
  CKD_SSCGC = 0x0U;
  while ((CKD_SSCGS & 0x00000002UL) != 0x00000002UL)
  {
  }
  ADC_WAIT_NS(100 * 1000);
  /* End of repetitions for SSCG */

  /* Set the write protection of Clock controller register */
  CLKKCPROT1  = ADC_KCPROT_CLR;
  /* End Clock Gear Up sequence */
}

/***********************************************************************************************************************
**                      Watchdog Initialization                                                                       **
***********************************************************************************************************************/
void Wdg_Init(void)
{
  /* call the function */
}
/***********************************************************************************************************************
*    ADC Interrupt Bind Register Initialization
*    ADC EI level interrupt source to define a binding between interrupt sources 32 to 1063 and CPU cores.
***********************************************************************************************************************/
void Adc_Set_EI_Bind(void)
{
  /* Binded to PE0  */
  EIBD442 = (EIBD442 & ADC_EIBD_PEID_MASK) | ADC_EIBD_PEID_PE0; /* ADI01 */
  EIBD72  = (EIBD72  & ADC_EIBD_PEID_MASK) | ADC_EIBD_PEID_PE0; /* DMA0_02 */

  /* Binded to PE1  */
  EIBD453 = (EIBD453 & ADC_EIBD_PEID_MASK) | ADC_EIBD_PEID_PE1; /* ADI12 */
  EIBD85  = (EIBD85  & ADC_EIBD_PEID_MASK) | ADC_EIBD_PEID_PE1; /* DMA0_06 */
}

void Adc_Set_EI_Bind_PE6(void)
{
  /* Binded to PE6  */
  INTC2_EIBD360 = 6;
  INTC2_EIBD8 = 6;
  INTC2_EIBD70 = 6;
  INTC2_EIBD71 = 6;
  INTC2_EIBD72 = 6;
  INTC2_EIBD73 = 6;
  INTC2_EIBD74 = 6;
  INTC2_EIBD75 = 6;
  INTC2_EIBD76 = 6;
  INTC2_EIBD77 = 6;
  INTC2_EIBD78 = 6;
  INTC2_EIBD79 = 6;
  INTC2_EIBD80 = 6;
  INTC2_EIBD81 = 6;
  INTC2_EIBD82 = 6;
  INTC2_EIBD83 = 6;
  INTC2_EIBD84 = 6;
  INTC2_EIBD85 = 6;
  INTC2_EIBD825 = 6;
  INTC2_EIBD826 = 6;
  INTC2_EIBD827 = 6;
  INTC2_EIBD828 = 6;
  INTC2_EIBD829 = 6;
  INTC2_EIBD830 = 6;
  INTC2_EIBD831 = 6;
  INTC2_EIBD832 = 6;
  INTC2_EIBD833 = 6;
  INTC2_EIBD834 = 6;
  INTC2_EIBD835 = 6;
  INTC2_EIBD836 = 6;
  INTC2_EIBD837 = 6;
  INTC2_EIBD838 = 6;
  INTC2_EIBD839 = 6;
  INTC2_EIBD840 = 6;
  INTC2_EIBD441 = 6;
  INTC2_EIBD442 = 6;
  INTC2_EIBD443 = 6;
  INTC2_EIBD444 = 6;
  INTC2_EIBD445 = 6;
  INTC2_EIBD451 = 6;
  INTC2_EIBD452 = 6;
  INTC2_EIBD453 = 6;
  INTC2_EIBD454 = 6;
  INTC2_EIBD455 = 6;
  INTC2_EIBD446 = 6;
  INTC2_EIBD447 = 6;
  INTC2_EIBD448 = 6;
  INTC2_EIBD449 = 6;
  INTC2_EIBD450 = 6;
  INTC2_EIBD456 = 6;
  INTC2_EIBD457 = 6;
  INTC2_EIBD458 = 6;
  INTC2_EIBD459 = 6;
  INTC2_EIBD460 = 6;
  INTC2_EIBD461 = 6;
  INTC2_EIBD463 = 6;
  INTC2_EIBD462 = 6;
  INTC2_EIBD464 = 6;
}

/***********************************************************************************************************************
*    Setup peripheral guard to enable Read/write
***********************************************************************************************************************/
void Guard_Init(void)
{
  PEGKCPROT0 = ADC_KCPROT_SET;
  PEGKCPROT1 = ADC_KCPROT_SET;
  PBGKCPROT60 = ADC_KCPROT_SET;
  PBGKCPROT70 = ADC_KCPROT_SET;

  /* Enable read/write Local RAM */
  PEGPROT0(0) |= 0x00000143UL;
  PEGPROT0(1) |= 0x00000143UL;
  PEGPROT0(2) |= 0x00000143UL;
  PEGPROT0(3) |= 0x00000143UL;
  PEGPROT0(4) |= 0x00000143UL;
  PEGPROT0(5) |= 0x00000143UL;
  PEGPROT0(6) |= 0x00000143UL;
  PEGPROT0(7) |= 0x00000143UL;

  PEGPROT1(0) |= 0x00000143UL;
  PEGPROT1(1) |= 0x00000143UL;
  PEGPROT1(2) |= 0x00000143UL;
  PEGPROT1(3) |= 0x00000143UL;
  PEGPROT1(4) |= 0x00000143UL;
  PEGPROT1(5) |= 0x00000143UL;
  PEGPROT1(6) |= 0x00000143UL;
  PEGPROT1(7) |= 0x00000143UL;

  /* Enable read/write ADCK */
  PBG60PROT0(1) |= 0x00000143UL;
  PBG60PROT0(14) |= 0x00000143UL;
  PBG60PROT0(15) |= 0x00000143UL;

  PBG70PROT0(1) |= 0x00000143UL;
  PBG70PROT0(6) |= 0x00000143UL;
  PBG70PROT0(7) |= 0x00000143UL;

  PEGKCPROT0 = ADC_KCPROT_CLR;
  PEGKCPROT1 = ADC_KCPROT_CLR;
  PBGKCPROT60 = ADC_KCPROT_CLR;
  PBGKCPROT70 = ADC_KCPROT_CLR;
}

void Guard_Enable_PE(void)
{
  #if defined(RUN_PE6)
  Adc_Set_EI_Bind_PE6();
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
/***********************************************************************************************************************
**                      Mcu Initialization                                                                            **
***********************************************************************************************************************/
void Mcu_Init(void)
{

  /* Clock Initialization */
  Clock_Init();

  /* Interrupt settings */
  /* Set Reference Table Method for ECM */
  EIC08 |= ADC_EIC_EITB;

  /* Setup module standby controllers */
  /* Disable protection for module standby registers */
  ADC_MSRKCPROT = ADC_KCPROT_SET;
  /* Enable SAD module */
  ADC_MSR_ADC_ISO = ADC_MSR_ACTIVE;
  /* Enable clock for OSTM0 */
  ADC_MSR_OSTM &= 0xFFFFFFFEUL;
  /* Enable protection for module standby registers */
  ADC_MSRKCPROT = ADC_KCPROT_CLR;
}

/***********************************************************************************************************************
**                      ADC Module Interrupt registers Initialization                                                 **
***********************************************************************************************************************/
void Adc_Set_TableReference(void)
{
  volatile uint16* LpEicReg;
  uint32 LulCount;

  /* adc conversion interrupt registers initialization */
  /* ADCK0 */
  LpEicReg = ADC_INTCREG_BASEADD_ADCK0;
  for (LulCount = 0UL; LulCount < ADC_ADCK_NUM_OF_INTERRUPTS; LulCount++)
  {
    LpEicReg[LulCount] = (uint16)((LpEicReg[LulCount] & ~ADC_EIC_EIP_MASK) | ADC_EIC_EIP_LOWEST | ADC_EIC_EITB);
  }

  /* ADCK1 */
  LpEicReg = ADC_INTCREG_BASEADD_ADCK1;
  for (LulCount = 0UL; LulCount < ADC_ADCK_NUM_OF_INTERRUPTS; LulCount++)
  {
    LpEicReg[LulCount] = (uint16)((LpEicReg[LulCount] & ~ADC_EIC_EIP_MASK) | ADC_EIC_EIP_LOWEST | ADC_EIC_EITB);
  }

  /* ADCK2 */
  LpEicReg = ADC_INTCREG_BASEADD_ADCK2;
  for (LulCount = 0UL; LulCount < ADC_ADCK_NUM_OF_INTERRUPTS; LulCount++)
  {
    LpEicReg[LulCount] = (uint16)((LpEicReg[LulCount] & ~ADC_EIC_EIP_MASK) | ADC_EIC_EIP_LOWEST | ADC_EIC_EITB);
  }

  /* ADCK3 */
  LpEicReg = ADC_INTCREG_BASEADD_ADCK3;
  for (LulCount = 0UL; LulCount < ADC_ADCK_NUM_OF_INTERRUPTS; LulCount++)
  {
    LpEicReg[LulCount] = (uint16)((LpEicReg[LulCount] & ~ADC_EIC_EIP_MASK) | ADC_EIC_EIP_LOWEST | ADC_EIC_EITB);
  }
  
  /* ADE */
  LpEicReg = ADC_INTCREG_BASEADD_ADE;
  for (LulCount = 0UL; LulCount < ADC_ADE_NUM_OF_INTERRUPTS; LulCount++)
  {
    LpEicReg[LulCount] = (uint16)((LpEicReg[LulCount] & ~ADC_EIC_EIP_MASK) | ADC_EIC_EIP_MIDDLE | ADC_EIC_EITB);
  }

  /* sDAMC0 */
  LpEicReg = ADC_INTCREG_BASEADD_SDMAC0;
  for (LulCount = 0UL; LulCount < ADC_SDMAC_NUM_OF_INTERRUPTS; LulCount++)
  {
    LpEicReg[LulCount] = (uint16)((LpEicReg[LulCount] & ~ADC_EIC_EIP_MASK) | ADC_EIC_EIP_LOWEST | ADC_EIC_EITB);
  }
}

/***********************************************************************************************************************
**                      Port Initialization                                                                           **
***********************************************************************************************************************/
void Port_Init(void)
{
  /* P33_6 */
  uint16 LusSetmask = 0x0040;
  uint16 LusClearmask = ~LusSetmask;

  /* Set Port Write Access P33 to Enable */
  PKCPROT = ADC_KCPROT_SET;
  PWE = PWE | 0x00100000UL;

  /* Set Port Mode P33_6 to Alternative Mode */
  PMC33 = PMC33 | LusSetmask;

  /* Set Alternative Function */
  PFC33 = PFC33 & LusClearmask;
  PFCE33 = PFCE33 | LusSetmask;
  PFCAE33 = PFCAE33 & LusClearmask;
  PFCEAE33 = PFCEAE33 & LusClearmask;

  PM33 = PM33 | LusSetmask;

  /* Set Port Write Access P33 to Disable */
  PWE = PWE & ~(0x00100000UL);
  PKCPROT = ADC_KCPROT_CLR;
}

/***********************************************************************************************************************
**                      Timer Hardwrare Trigger                                                                       **
***********************************************************************************************************************/
void Start_Timer0()
{
  /* Disable protection for module standby registers */
  ADC_MSRKCPROT = ADC_KCPROT_SET;
  /* Put GTM in operating mode */
  MSR_GTM &= ADC_MSR_ACTIVE;
  /* Disable protection for module standby registers */
  ADC_MSRKCPROT = ADC_KCPROT_CLR;
  while ((MSR_GTM & 0x00000001) != 0x00000000);
  
  /* Setup global clock divider: Clock Management Unit Registers */
  CMU_GCLK_NUM = 0xFFFFFF;
  CMU_GCLK_DEN = 0xFFFFFF;
  /* Setup the CMU_CLKx prescalers, divide SYS_CLK by 10 */
  CMU_CLK_0_CTRL = 0x9; 
  
  /* Enable clock prescalers (FXCLK only) */
  CMU_CLK_EN = 0x800000;
  CMU_FXCLK_CTRL = 0;
  
  /* Set up start Trigger for GTM TOM0_OUT0 */
  /* Set PWM period */
  GTM0_TOM0_CH0_CM0 = 8000;
  /* Set PWM duty cycle */
  GTM0_TOM0_CH0_CM1 = 4000;
  /* Load PWM period */
  GTM0_TOM0_CH0_SR0 = 8000;
  /* Load PWM duty cycle */
  GTM0_TOM0_CH0_SR1 = 4000;
  /* Setup TOM channel 0 in SOMP */
  GTM0_TOM0_CH0_CTRL = 0x82A;
  /* Force update */
  GTM0_TOM0_TGC0_FUPD_CTRL = 0x20002;
  /* Initiate the trigger request and enable update mode for channel 0 */
  GTM0_TOM0_TGC0_GLB_CTRL = 0x20001;
  /* Enable channel operation on an update trigger */ 
  GTM0_TOM0_TGC0_ENDIS_STAT = 0x00000002;
  /* Set up timebase CMP to 200 */
  GTM0_TOM0_TGC0_ACT_TB = 0x010000C8;
  /* Enable output on channel 0 */
  GTM0_TOM0_TGC0_OUTEN_STAT = 0x00000002;
  
}
/***********************************************************************************************************************
*    DMA Master Enable Initialization
*    DME: bit0
*    Enables or disables DMA transfers on all channels.
*    0: Disable DMA transfers on all channels
*    1: Enable DMA transfers on all channels
*
***********************************************************************************************************************/
void Adc_DMA_DME_Enable(void)
{
  ADC_DMA0OR |= ADC_DME_ENABLE; /* DMA0OR DME */
  ADC_DMA1OR |= ADC_DME_ENABLE; /* DMA1OR DME */
}

void Adc_Start_OSTM(void)
{
	/* Only OSTM0 is used */
	/* Mode selection for Interval timer, Interval counter = 1ms/(1/80 MHz) */
	ADC_OSTM0CMP = 0x00013880UL;
	/* Enable interrupt, Interval timer mode */
	ADC_OSTM0CTL = 0x80U;
	/* Interrupt for Ostm0, Enable Interrupt */
	*(volatile uint16 *)ADC_EIC_ADDR(360) &= 0x7FU;
	/* Interrupt for Ostm0, Enable reference table jump */
	*(volatile uint16 *)ADC_EIC_ADDR(360) |= 0x4FU;
	/* Start OSTM0 */
	ADC_OSTM0TS = 0x01U;
}
void Adc_Stop_OSTM(void)
{
	ADC_OSTM0TT = 0x01U;
}
/**********************************************************************************************************************
**                          End of File                                                                              **
***********************************************************************************************************************/
