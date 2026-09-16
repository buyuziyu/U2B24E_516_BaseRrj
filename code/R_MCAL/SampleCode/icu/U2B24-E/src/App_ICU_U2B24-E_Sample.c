/*============================================================================*/
/* Project      = RH850/X2x MCAL PF Development                               */
/* Module       = App_ICU_U2B24_Sample.c                                      */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2024-2025 Renesas Electronics Corporation. All rights reserved.        */
/*============================================================================*/
/* Purpose:                                                                   */
/* This file contains sample application for ICU Driver Component             */
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
/*              Devices: RH850/U2B24-E                                        */
/*============================================================================*/

/*******************************************************************************
**                      Revision Control History                              **
*******************************************************************************/
/*
 * 2.4.1:  30/06/2025 : Update Guard_Enable_PE function for support sample app on core 6
 * 2.3.1:  31/03/2025 : As part of GTM support the following are made:
 *                       + Add GTM specific stub setting
 *                      As part of G4KH U2Bx-E support, the following are made:
 *                       + Update function Guard_Enable_PE
 * 2.2.0:  31/12/2024 : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D
 *                      Final Release
 * 2.1.2:  31/10/2024 : Update SW-VERSION for Ver22.01.02 Beta2 Release
 * 2.0.2:  24/06/2024 : Initial Version
 */
/******************************************************************************/

/*******************************************************************************
**                     Include Section                                        **
*******************************************************************************/
#include "Std_Types.h"
#include "App_Icu_Device_Sample.h"
#include "Icu_Cfg.h"
/*******************************************************************************
**                         Global Data                                        **
*******************************************************************************/
const uint32 RenICR_ADRR[] = 
{
  /* TAUJ2_INTC2 */
  ICU_EIC_INTC2(960), ICU_EIC_INTC2(961), ICU_EIC_INTC2(962), ICU_EIC_INTC2(963),
  /* TAUD0_EVEN_INTC1_CORE0 */
  ICU_EIC_INTC1_PE0(10), ICU_EIC_INTC1_PE0(11), ICU_EIC_INTC1_PE0(12), ICU_EIC_INTC1_PE0(13),
  ICU_EIC_INTC1_PE0(23), ICU_EIC_INTC1_PE0(24), ICU_EIC_INTC1_PE0(25), ICU_EIC_INTC1_PE0(26),
  /* TAUD0_EVEN_INTC1_CORE1 */
  ICU_EIC_INTC1_PE1(10), ICU_EIC_INTC1_PE1(11), ICU_EIC_INTC1_PE1(12), ICU_EIC_INTC1_PE1(13),
  ICU_EIC_INTC1_PE1(23), ICU_EIC_INTC1_PE1(24), ICU_EIC_INTC1_PE1(25), ICU_EIC_INTC1_PE1(26),
  /* TAUD1_INTC2 */
  ICU_EIC_INTC2(328), ICU_EIC_INTC2(329), ICU_EIC_INTC2(330), ICU_EIC_INTC2(331),
  ICU_EIC_INTC2(332), ICU_EIC_INTC2(333), ICU_EIC_INTC2(334), ICU_EIC_INTC2(335),
  ICU_EIC_INTC2(336), ICU_EIC_INTC2(337), ICU_EIC_INTC2(338), ICU_EIC_INTC2(339),
  ICU_EIC_INTC2(340), ICU_EIC_INTC2(341), ICU_EIC_INTC2(342), ICU_EIC_INTC2(343),
  /* TAUD2_INTC2 */
  ICU_EIC_INTC2(344), ICU_EIC_INTC2(345), ICU_EIC_INTC2(346), ICU_EIC_INTC2(347),
  ICU_EIC_INTC2(348), ICU_EIC_INTC2(349), ICU_EIC_INTC2(350), ICU_EIC_INTC2(351),
  ICU_EIC_INTC2(352), ICU_EIC_INTC2(353), ICU_EIC_INTC2(354), ICU_EIC_INTC2(355),
  ICU_EIC_INTC2(356), ICU_EIC_INTC2(357), ICU_EIC_INTC2(358), ICU_EIC_INTC2(359),
  /* TAUD3_INTC2 SOURCE 0 */
  ICU_EIC_INTC2(379), ICU_EIC_INTC2(380), ICU_EIC_INTC2(381), ICU_EIC_INTC2(382),
  ICU_EIC_INTC2(383), ICU_EIC_INTC2(384), ICU_EIC_INTC2(385), ICU_EIC_INTC2(386),
  ICU_EIC_INTC2(387), ICU_EIC_INTC2(388), ICU_EIC_INTC2(389), ICU_EIC_INTC2(390),
  ICU_EIC_INTC2(391), ICU_EIC_INTC2(392), ICU_EIC_INTC2(393), ICU_EIC_INTC2(394),
  /* TAUD3_INTC2 SOURCE 1 */
  ICU_EIC_INTC2(505), ICU_EIC_INTC2(506), ICU_EIC_INTC2(507), ICU_EIC_INTC2(508),
  ICU_EIC_INTC2(509), ICU_EIC_INTC2(510), ICU_EIC_INTC2(511), ICU_EIC_INTC2(512),
  ICU_EIC_INTC2(513), ICU_EIC_INTC2(514), ICU_EIC_INTC2(515), ICU_EIC_INTC2(516),
  ICU_EIC_INTC2(517), ICU_EIC_INTC2(518), ICU_EIC_INTC2(519), ICU_EIC_INTC2(520),
  /* TAUD3_INTC2 SOURCE 2 */
  ICU_EIC_INTC2(793), ICU_EIC_INTC2(794), ICU_EIC_INTC2(795), ICU_EIC_INTC2(796),
  ICU_EIC_INTC2(797), ICU_EIC_INTC2(798), ICU_EIC_INTC2(799), ICU_EIC_INTC2(800),
  ICU_EIC_INTC2(801), ICU_EIC_INTC2(802), ICU_EIC_INTC2(803), ICU_EIC_INTC2(804),
  ICU_EIC_INTC2(817), ICU_EIC_INTC2(818), ICU_EIC_INTC2(819), ICU_EIC_INTC2(820),
  /* GTM_IRQ_SEL0j TIM00 to TIM07 */
  ICU_EIC_INTC2(86),ICU_EIC_INTC2(87),ICU_EIC_INTC2(88),ICU_EIC_INTC2(89),
  ICU_EIC_INTC2(90),ICU_EIC_INTC2(91),ICU_EIC_INTC2(92),ICU_EIC_INTC2(93),
  /* IRQ0..3_INTC2 */
  ICU_EIC_INTC2(765), ICU_EIC_INTC2(766), ICU_EIC_INTC2(767), ICU_EIC_INTC2(768),
  /* End */
  0xFFFFFFFFUL
};

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
void Clock_Init(void);

/* Function for Mcu clock settings */
void Mcu_Init(void)
{
  Clock_Init();
  /* Disable protection for module standby registers */
  ICU_MSRKCPROT = ICU_KCPROT_SET;
  /* Enable TAUJ modules */
  ICU_MSR_TAUJ_AWO = ICU_MSR_ACTIVE;
  while (ICU_MSR_TAUJ_AWO != ICU_MSR_ACTIVE);
  /* Enable TAUD module */
  ICU_MSR_TAUD = ICU_MSR_ACTIVE;
  while (ICU_MSR_TAUD != ICU_MSR_ACTIVE);
  /* Enable clock source for OSTM0 */
  MSR_OSTM &= 0xFFFFFFFEUL;
  /* Enable protection for module standby registers */
  /* Enable clock source for GTM */
  ICU_MSR_GTM = ICU_MSR_ACTIVE;
  while (ICU_MSR_GTM != ICU_MSR_ACTIVE);
  /* GTM CMU enable, by default all GTM TIM channels clock source is 80MHz */
  #if (ICU_GTM_TIMER_UNIT_USED == STD_ON)
  /* Enable CMU */
  GTM0CMUCLKEN = 0x0000AAAAUL;
  #endif
  ICU_MSRKCPROT = ICU_KCPROT_CLR;
}

/* Function for Wdg settings */
void Wdg_Init(void)
{
  /* Wdg initialization for the corresponding variant should be done here */
}

void Port_Init(void)
{
  /* Piggy board: Y-RH850-U2BE-516PIN-PB-T1-V1                                         */
  /* PORT  |  PG_PIN     | ALT_mode | IcuChannel | PFCEAE PFCAE PFCE PFC | PM | PMC |  */
  /* P15_4 | (CN14_B_53) | AF01_IN  | (TAUJ2I0)  |    0     0    0    0  |  1 |  1  |  */
  /* P15_5 | (CN14_B_47) | AF05_IN  | (TAUJ2I1)  |    0     1    0    0  |  1 |  1  |  */
  /* P15_6 | (CN14_B_51) | AF02_IN  | (TAUJ2I2)  |    0     0    0    1  |  1 |  1  |  */
  /* P02_5 | (CN14_B_01) | AF15_IN  | (TAUJ2I3)  |    1     1    1    0  |  1 |  1  |  */
  /* P23_2 | (CN17_K_41) | AF16_IN  | (TAUD1I0)  |    1     1    1    1  |  1 |  1  |  */
  /*                                  (TAUD1I1)   Use input from TAUD1I0               */
  /* P23_3 | (CN17_J_46) | AF16_IN  | (TAUD1I2)  |    1     1    1    1  |  1 |  1  |  */
  /* P02_0 | (CN14_A_08) | AF02_IN  | (TIM00)    |    0     0    0    1  |  1 |  1  |  */
  /* P02_1 | (CN14_B_05) | AF02_IN  | (TIM01)    |    0     0    0    1  |  1 |  1  |  */
  /* P02_2 | (CN14_A_06) | AF02_IN  | (TIM02)    |    0     0    0    1  |  1 |  1  |  */
  /* P02_3 | (CN14_B_03) | AF02_IN  | (TIM03)    |    0     0    0    1  |  1 |  1  |  */
  /* P02_4 | (CN14_A_04) | AF07_IN  | (TIM04)    |    0     1    1    0  |  1 |  1  |  */
  /* P00_0 | (CN18_x_04) | AF02_IN  | (IRQ0)     |    0     0    0    1  |  1 |  1  |  */

  /* Register Protection Enable */
  ICU_PKCPROT = ICU_PORT_ENABLE_WRITE_ACCESS_VALUE;
  /* Set Port Write Enable Register */
  ICU_PWE |= ICU_PWE_ENABLE_WRITE_ACCESS_VALUE;

  /* Configure for port */
  ICU_PFCEAE(15)  &= (uint16)~((1u<<4));
   ICU_PFCAE(15)  &= (uint16)~((1u<<4));
    ICU_PFCE(15)  &= (uint16)~((1u<<4));
     ICU_PFC(15)  &= (uint16)~((1u<<4));
     ICU_PMC(15)  |= (uint16) ((1u<<4));
      ICU_PM(15)  |= (uint16) ((1u<<4));

  ICU_PFCEAE(15)  &= (uint16)~((1u<<5));
   ICU_PFCAE(15)  |= (uint16) ((1u<<5));
    ICU_PFCE(15)  &= (uint16)~((1u<<5));
     ICU_PFC(15)  &= (uint16)~((1u<<5));
     ICU_PMC(15)  |= (uint16) ((1u<<5));
      ICU_PM(15)  |= (uint16) ((1u<<5));

  ICU_PFCEAE(15)  &= (uint16)~((1u<<6));
   ICU_PFCAE(15)  &= (uint16)~((1u<<6));
    ICU_PFCE(15)  &= (uint16)~((1u<<6));
     ICU_PFC(15)  |= (uint16) ((1u<<6));
     ICU_PMC(15)  |= (uint16) ((1u<<6));
      ICU_PM(15)  |= (uint16) ((1u<<6));

  ICU_PFCEAE(02)  |= (uint16) ((1u<<5));
   ICU_PFCAE(02)  |= (uint16) ((1u<<5));
    ICU_PFCE(02)  |= (uint16) ((1u<<5));
     ICU_PFC(02)  &= (uint16) ((1u<<5));
     ICU_PMC(02)  |= (uint16) ((1u<<5));
      ICU_PM(02)  |= (uint16) ((1u<<5));

  ICU_PFCEAE(23)  |= (uint16) ((1u<<2)|(1u<<3));
   ICU_PFCAE(23)  |= (uint16) ((1u<<2)|(1u<<3));
    ICU_PFCE(23)  |= (uint16) ((1u<<2)|(1u<<3));
     ICU_PFC(23)  |= (uint16) ((1u<<2)|(1u<<3));
     ICU_PMC(23)  |= (uint16) ((1u<<2)|(1u<<3));
      ICU_PM(23)  |= (uint16) ((1u<<2)|(1u<<3));

  ICU_PFCEAE(02)  &= (uint16)~((1u<<0)|(1u<<1)|(1u<<2)|(1u<<3));
   ICU_PFCAE(02)  &= (uint16)~((1u<<0)|(1u<<1)|(1u<<2)|(1u<<3));
    ICU_PFCE(02)  &= (uint16)~((1u<<0)|(1u<<1)|(1u<<2)|(1u<<3));
     ICU_PFC(02)  |= (uint16) ((1u<<0)|(1u<<1)|(1u<<2)|(1u<<3));
     ICU_PMC(02)  |= (uint16) ((1u<<0)|(1u<<1)|(1u<<2)|(1u<<3));
      ICU_PM(02)  |= (uint16) ((1u<<0)|(1u<<1)|(1u<<2)|(1u<<3));

  ICU_PFCEAE(02)  &= (uint16)~((1u<<4));
   ICU_PFCAE(02)  |= (uint16) ((1u<<4));
    ICU_PFCE(02)  |= (uint16) ((1u<<4));
     ICU_PFC(02)  &= (uint16)~((1u<<4));
     ICU_PMC(02)  |= (uint16) ((1u<<4));
      ICU_PM(02)  |= (uint16) ((1u<<4));

  ICU_PFCEAE(00)  &= (uint16)~((1u<<0));
   ICU_PFCAE(00)  &= (uint16)~((1u<<0));
    ICU_PFCE(00)  &= (uint16)~((1u<<0));
     ICU_PFC(00)  |= (uint16) ((1u<<0));
     ICU_PMC(00)  |= (uint16) ((1u<<0));
      ICU_PM(00)  |= (uint16) ((1u<<0));

  /* Enable Digital Noise Elimination for TAUD and TAUJ */
  /* TAUD1 */
  ICU_DNFAEN_TAUD1 |= 0xFFFFU;
  /* TAUDJ2 */
  ICU_DNFAEN_TAUJ2 |= 0xFFU;
}

void Reg_Init(void)
{
  volatile uint16 *ptr;
  uint8 count;
  for (count = 0; RenICR_ADRR[count] != 0xFFFFFFFFUL;  count++)
  {
    ptr = (volatile uint16 *)RenICR_ADRR[count];
    *ptr = (*ptr | 0x40u);
  }
}

void Clock_Init(void)
{
  /* Wait to HSIntOSC clock is stable(HSOSCS.HSOSCSTAB = 1). */
  while ((HSOSCS & 0x00000002ul) != 0x00000002ul){}
  /* HSIntOSC stops operation in stand-by mode(HSOSCSTPM.MOSCSTPMSK = 0). */
  CLKKCPROT1  = ENABLE_WRITE_KEY_CODE;
  HSOSCSTPM   = 0x00000000UL;
  CLKKCPROT1  = DISABLE_WRITE_KEY_CODE;
  /* Start the MainOSC (MOSCE.MOSCENTRG = 1). */
  CLKKCPROT1  = ENABLE_WRITE_KEY_CODE;
  MOSCE       = 0x00000001ul;
  CLKKCPROT1  = DISABLE_WRITE_KEY_CODE;
  /* 4.Confirm that the MainOSC has been started (MOSCS.MOSCSTAB = 1). */
  while ((MOSCS & 0x00000002ul) != 0x00000002ul){}
  /* MainOSC stops operation in stand-by mode(MOSCSTPM.MOSCSTPMSK = 0). */
  CLKKCPROT1  = ENABLE_WRITE_KEY_CODE;
  MOSCSTPM    = 0x00000000UL;
  CLKKCPROT1  = DISABLE_WRITE_KEY_CODE;
  /* Start the PLL (PLLE.PLLENTRG = 1). */
  CLKKCPROT1  = ENABLE_WRITE_KEY_CODE;
  PLLE        = 0x00000001ul;
  CLKKCPROT1  = DISABLE_WRITE_KEY_CODE;
  /* Confirm that the PLL has been started (PLLS.PLLCLKSTAB = 1). */
  while ((PLLS & 0x00000002ul) != 0x00000002ul){}
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
  while ((CKSC_CPUS & 0x00000001ul) != 0x00000000ul){}
}

void App_Icu_Start_Timer0(void)
{
  /* Only OSTM0 is used */
  /* Mode selection for Interval timer, Interval counter = 1[ms]/(1/80[MHz]) */
  ICU_OSTM0CMP = 0x00013880UL;
  /* Enable interrupt, Interval timer mode */
  ICU_OSTM0CTL = 0x80U;
  /* Interrupt for OSTM0, Enable interrupt*/
  EIC360 &= 0x7FU;
  /* Interrupt for OSTM0, Enable reference table jump */
  EIC360 |= 0x4FU;
  /* Start OSTM0 */
  ICU_OSTM0TS = 0x01U;
}

/* Enable register write to all HWIP for other than core 0 */
void Guard_Enable_PE(void)
{
  #if defined (RUN_OTHER_PE)
  /* Bound interrupt to core 6 */
  INTC2_EIBD960 = 6;
  INTC2_EIBD961 = 6;
  INTC2_EIBD962 = 6;
  INTC2_EIBD963 = 6;
  INTC2_EIBD328 = 6;
  INTC2_EIBD329 = 6;
  INTC2_EIBD330 = 6;
  INTC2_EIBD86 = 6;
  INTC2_EIBD87 = 6;
  INTC2_EIBD88 = 6;
  INTC2_EIBD89 = 6;
  INTC2_EIBD90 = 6;
  INTC2_EIBD765 = 6;
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
**                         Notification function                              **
*******************************************************************************/

/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
