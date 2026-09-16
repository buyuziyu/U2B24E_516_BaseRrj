/*============================================================================*/
/* Project      = RH850/X2x AR4 MCAL Development                              */
/* Module       = App_PWM_U2B24-E_Sample.c                                    */
/*                                                                            */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2024-2025 Renesas Electronics Corporation. All rights reserved.        */
/*============================================================================*/
/* Purpose:                                                                   */
/* This file contains sample application for PWM Driver Component             */
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
/*                                                                            **
 * 2.5.1:  30/06/2025 : Remove SW-VERSION in header comment                   **
 * 2.3.2:  29/04/2025 : Update SW-VERSION for U2Ax Ver22.00.04 Beta Release   **
 * 2.3.1:  31/03/2025 : Update SW-VERSION for U2BxE Ver22.00.02 Beta Release  **
 *                      As part of U2BxE support, following changes are made: **
 *                      1. Add function Guard_Enable_PE, GblSyncCoreFlag      **
 * 2.3.0:  31/12/2024 : For GTM support, add the following changes            **
 *                      1. Add TOM/ATOM EIC                                   **
 *                      1. Update Mcu_Init, Port_Init                         **
 * 2.2.0:  31/12/2024 : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final **
 *                      Release                                               **
 *                      As part of U2BxE support, following changes are made  **
 *                      1. Update setting, comment for Port_Init              **
 * 2.1.2:  31/10/2024 : Update SW-VERSION for Ver22.01.02 U2Bx Beta2 Release  **
 * 2.1.1:  13/08/2024 : As part of U2BxE support, following changes are made  **
 *                      1. Update setting for Port_Init                       **
 *                      2. Update comment for Port_Init                       **
 *         23/05/2024 : Initial Version.                                      **
 *                                                                            */
/******************************************************************************/


/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "App_Pwm_Device_Sample.h"
#include "Pwm_Cfg.h"

/*******************************************************************************
**                            Macros                                          **
*******************************************************************************/


/*******************************************************************************
**                        Global variables                                    **
*******************************************************************************/
uint32 RenICRADRR[] = {

              /* TAUD0 */
              PWM_EIC0_ADDR(10UL), /* INTTAUD0I0 */
              PWM_EIC_ADDR(320UL), /* INTTAUD0I1 */
              PWM_EIC0_ADDR(11UL), /* INTTAUD0I2 - CORE0 */
              PWM_EIC_ADDR(321UL), /* INTTAUD0I3 */
              PWM_EIC_ADDR(322UL),
              PWM_EIC_ADDR(323UL),
              PWM_EIC_ADDR(324UL),
              PWM_EIC_ADDR(325UL),
              PWM_EIC_ADDR(326UL),
              PWM_EIC_ADDR(327UL),

              /* TAUD1 */
              PWM_EIC_ADDR(328UL), /* INTTAUD1I0 */
              PWM_EIC_ADDR(329UL), /* INTTAUD1I1 */
              PWM_EIC_ADDR(330UL), /* INTTAUD1I2 */
              PWM_EIC_ADDR(331UL), /* INTTAUD1I3 */

              /* TAUD2 */
              PWM_EIC_ADDR(344UL), /* INTTAUD2I0 */
              PWM_EIC_ADDR(345UL), /* INTTAUD2I1 */
              PWM_EIC_ADDR(346UL), /* INTTAUD2I2 */
              PWM_EIC_ADDR(347UL), /* INTTAUD2I3 */

              /* TAUD3 */
              /* TAUD3 - Interrupt selection bit 010 */
              PWM_EIC_ADDR(505UL),
              PWM_EIC_ADDR(506UL),
              PWM_EIC_ADDR(507UL),
              PWM_EIC_ADDR(508UL),

              /* TAUD3 - Interrupt selection bit 001 */
              PWM_EIC_ADDR(379UL),  /* INTTAUD3I0 */
              PWM_EIC_ADDR(380UL),  /* INTTAUD3I1 */
              PWM_EIC_ADDR(381UL),  /* INTTAUD3I1 */
              PWM_EIC_ADDR(382UL),
              
              /* TAUD3 - Interrupt selection bit 100 */
              PWM_EIC_ADDR(793UL),  /* INTTAUD3I0 */
              PWM_EIC_ADDR(794UL),  /* INTTAUD3I1 */
              PWM_EIC_ADDR(795UL),  /* INTTAUD3I2 */
              PWM_EIC_ADDR(796UL),  /* INTTAUD3I3 */

              /* TAUJ2 */
              PWM_EIC_ADDR(960UL), /* INTTAUJ2I0 */
              PWM_EIC_ADDR(961UL), /* INTTAUJ2I1 */
              PWM_EIC_ADDR(962UL), /* INTTAUJ2I2 */
              PWM_EIC_ADDR(963UL), /* INTTAUJ2I3 */

              /* TOM0 */
              PWM_EIC_ADDR(86UL), /* INTGTM0IOS000 */
              PWM_EIC_ADDR(87UL), /* INTGTM0IOS001 */
              /* ATOM0 */
              PWM_EIC_ADDR(88UL), /* INTGTM0IOS002 */
              PWM_EIC_ADDR(89UL), /* INTGTM0IOS003 */
};

/*******************************************************************************
**                        User function prototypes                            **
*******************************************************************************/
void Clock_Init(void);
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/* Function for Mcu clock settings */
void Mcu_Init(void)
{
  #if defined (RUN_OTHER_PE)
  /* Waiting enable PBG */
  while(1 != GblSyncCoreFlag);
  #endif
  /* Release the write protection of Standby controller register.*/
  MSRKCPROT = ENABLE_WRITE_KEY_CODE;

  /* Enable clock source for TAUD unit TAUD0,1,2,3 */
  MSR_TAUD &= 0xFFFFFFF0UL;
  /* Enable clock source for TAUJ unit TAUD2,3 */
  MSR_TAUJ &= 0xFFFFFFF0UL;
  /* Enable clock source for OSTM0 */
  MSR_OSTM &= 0xFFFFFFFEUL;
  /* Enable clock source GTM */
  MSR_GTM  = PWM_MSR_GTM_OPERATING_VALUE;
  while (MSR_GTM != PWM_MSR_GTM_OPERATING_VALUE);
  /* Set the write protection of Standby controller registers. */
  MSRKCPROT = DISABLE_WRITE_KEY_CODE;

  #if (PWM_GTM_UNIT_USED == STD_ON)
  /* Enable CMU */
  GTM0CMUCLKEN = 0x00AAAAAAUL;
  #endif
}

void Clock_Init(void)
{
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

  /* Start the MainOSC (MOSCE.MOSCENTRG = 1). */
  CLKKCPROT1  = ENABLE_WRITE_KEY_CODE;
  MOSCE       = 0x00000001UL;
  CLKKCPROT1  = DISABLE_WRITE_KEY_CODE;

  /* Confirm that the MainOSC has been started (MOSCS.MOSCSTAB = 1). */
  while ( (MOSCS & 0x00000002UL) != 0x00000002UL )
  {
  }

  /* MainOSC stops operation in stand-by mode(MOSCSTPM.MOSCSTPMSK = 0). */
  CLKKCPROT1  = ENABLE_WRITE_KEY_CODE;
  MOSCSTPM    = 0x00000000UL;
  CLKKCPROT1  = DISABLE_WRITE_KEY_CODE;

  /* Start the PLL (PLLE.PLLENTRG = 1). */
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

  /* Select a source clock(CKSC_CPUC.CPUCLKSCSID = 0). */
  CLKKCPROT1  = ENABLE_WRITE_KEY_CODE;
  /* Selected Clock source ID=0:CLK_PLLO */
  /* (This setting dependencies Option Bytes. CKDIVMD = 11B) */
  CKSC_CPUC   = 0x00000000UL;
  CLKKCPROT1  = DISABLE_WRITE_KEY_CODE;

  /* Confirm completion of selection(CKSC_CPUS.CPUCLKSACT = 0). */
  while ( (CKSC_CPUS & 0x00000001UL) != 0x00000000UL )
  {
  }
}

/* Function for initialization of PORT Pins Alternate functionality */
void Port_Init(void)
{
  /*                                     | PFCEAE PFCAE PFCE PFC | PM | PMC |  */
  /* P15-CN18 P00_9_ALT_OUT8 (TOM000)    |    0     1    1    1  | 0  |  1  |  */
  /* P13-CN18 P00_10_ALT_OUT5 (TOM001)   |    0     1    0    0  | 0  |  1  |  */
  /* P6-CN18 P00_3_ALT_OUT10 (ATOM02)    |    1     0    0    1  | 0  |  1  |  */
  /* P12-CN18 P00_4_ALT_OUT9 (ATOM03)    |    1     0    0    0  | 0  |  1  |  */
  /* P39-CN17 P32_3_ALT_OUT16 (TAUD1O3)  |    1     1    1    1  | 0  |  1  |  */
  /* P60-CN17 P22_11_ALT_OUT15 (TAUJ2O1) |    1     1    1    0  | 0  |  1  |  */


  /* Port set alt out mode for pin P00 for TOM and ATOM channels */
  PWM_PFCEAE(0) |= (uint16)((1u<<3)|(1u<<4));
  PWM_PFCEAE(0) &= (uint16)(~((1u<<9)|(1u<<10)));
  PWM_PFCAE(0)  |= (uint16)((1u<<9)|(1u<<10));
  PWM_PFCAE(0)  &= (uint16)(~((1u<<3)|(1u<<4)));
  PWM_PFCE(0)   |= (uint16)(1u<<9);
  PWM_PFCE(0)   &= (uint16)(~((1u<<3)|(1u<<4)|(1u<<10)));
  PWM_PFC(0)    |= (uint16)((1u<<3)|(1u<<9));
  PWM_PFC(0)    &= (uint16)(~((1u<<4)|(1u<<10)));
  PWM_PM(0)     &= (uint16)(~((1u<<3)|(1u<<4)|(1u<<9)|(1u<<10)));
  PWM_PMC(0)    |= (uint16)(((1u<<3)|(1u<<4)|(1u<<9)|(1u<<10)));
  
  /* Port set alt out mode for pin P32 for TAUD1O3 channel */
  PWM_PFCEAE(32) |= (uint16)(1u<<3);
  PWM_PFCAE(32)  |= (uint16)(1u<<3);
  PWM_PFCE(32)   |= (uint16)(1u<<3);
  PWM_PFC(32)    |= (uint16)(1u<<3);
  PWM_PM(32)     &= (uint16)(~(1u<<3));
  PWM_PMC(32)    |= (uint16)(1u<<3);

  /* Port set alt out mode for pin P22 for TAUJ2O1 channel */
  PWM_PFCEAE(22) |= (uint16)(1u<<11);
  PWM_PFCAE(22)  |= (uint16)(1u<<11);
  PWM_PFCE(22)   |= (uint16)(1u<<11);
  PWM_PFC(22)    &= (uint16)(~(1u<<11));
  PWM_PM(22)     &= (uint16)(~(1u<<11));
  PWM_PMC(22)    |= (uint16)(1u<<11);
}

/* Function for WDG Initialization */
void Wdg_Init(void)
{
  /* Watchdog functionality has been disabled through Flash Option bytes */
}

/* Function for Registers Initialization */
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

void App_Pwm_Start_Timer0(void)
{
  /* Only OSTM0 is used */
  /* Mode selection for Interval timer, Interval counter = 1[ms]/(1/80[MHz]) */
  PWM_OSTM0CMP = 0x00013880UL;
  /* Enable interrupt, Interval timer mode */
  PWM_OSTM0CTL = 0x80U;
  /* Interrupt for OSTM0, Enable interrupt*/
  *(volatile uint16 *)PWM_EIC_ADDR(360) &= 0x7FU;
  /* Interrupt for OSTM0, Enable reference table jump */
  *(volatile uint16 *)PWM_EIC_ADDR(360) |= 0x4FU;
  /* Start OSTM0 */
  PWM_OSTM0TS = 0x01U;
}

void App_Pwm_Stop_Timer0(void)
{
  /* Stop OSTM0 */
  PWM_OSTM0TT = 0x01U;
}

void Mcal_Pwm_Init(void)
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

#ifdef USE_FREERUN_TIMER
/* Function for Starting Free-run Timer */
void App_Start_FreeRun_Timer(void)
{
  /* Value for comparison */
  PWM_OSTM0CMP = 0x00000000UL;
  /* Disable interrupt, Free-run compare mode */
  PWM_OSTM0CTL = 0x02U;
  /* Start OSTM0 */
  PWM_OSTM0TS = 0x01U;
}
#endif

/* Setup peripheral guard to enable Read/write */
void Guard_Enable_PE(void)
{
  #if defined(RUN_OTHER_PE)
    INTC2_EIBD86 = 6;
    INTC2_EIBD87 = 6;
    INTC2_EIBD88 = 6;
    INTC2_EIBD89 = 6;
    INTC2_EIBD330 = 6;
    INTC2_EIBD331 = 6;
    INTC2_EIBD960 = 6;
    INTC2_EIBD961 = 6;
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
    (uint32) 0xFF8F8100UL, //PBGERRSLV11L0_base
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
  for (int i =0; i<15;i++)
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
