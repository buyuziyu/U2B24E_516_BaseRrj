/*============================================================================*/
/* Project      = AUTOSAR Renesas U2B10 MCAL Components                       */
/* Module       = App_MCU_U2B24-E_PostBuildVariant_Sample.c                   */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2024-2025 Renesas Electronics Corporation. All rights reserved.        */
/*============================================================================*/
/* Purpose:                                                                   */
/* This file contains sample application for MCU Driver Component             */
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
/*              Devices:        U2B24-E                                       */
/*============================================================================*/

/*******************************************************************************
**                      Revision Control History                              **
*******************************************************************************/
/*
 * 2.5.0:  30/06/2025  : Update SW-VERSION to 2.5.0
 * 2.4.0:  31/05/2025  : Update SW-VERSION to 2.4.0
 * 2.3.2:  29/04/2025  : Update SW-VERSION to 2.3.2
 * 2.3.1:  31/03/2025  : Update SW-VERSION to 2.3.1
 *                       Add function call when using RUN_OTHER_PE
 * 2.3.0:  28/02/2025  : Update SW-VERSION to 2.3.0
 *                       Add macro MCU_MSR_KCPROT, MCU_SWMRESS_GTM, MCU_MSR_GTM
 * 2.2.0:  31/12/2024  : Update SW-VERSION to 2.2.0
 * 2.1.2:  31/10/2024  : Update SW-VERSION to 2.1.2
 * 2.1.1:  30/08/2024  : Update SW-VERSION to 2.1.1
 *         19/05/2024  : Initial Version
 */
/******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "App_MCU_PostBuildVariant_Sample.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

/*******************************************************************************
**                      Macro                                                 **
*******************************************************************************/

/*******************************************************************************
**                         Global Data                                        **
*******************************************************************************/
Std_VersionInfoType                  VersionInfo;
volatile uint8                       GucIntCount;
volatile Std_ReturnType              GenIsTestSuccess;
volatile Mcu_PllStatusType           GenPllStatus[3];
volatile Std_ReturnType              GenInitClockResult;
volatile Std_ReturnType              GenDistributePllResult;
volatile Std_ReturnType              GenInitRamSectionResult[9];

#if (MCU_GET_RAM_STATE_API == STD_ON)
volatile Mcu_RamStateType            GenRamState;
#endif

volatile Mcu_ResetType               GenResetReason[2];
volatile Mcu_RawResetType            GenRawResetReason[2];

#if (MCU_GETWAKEUPFACTOR_API == STD_ON)
Mcu_WakeUpFactorInfoType             Wakeupfactorinfo;
#endif
#if (MCU_RELEASEIOBUFFERHOLD_API == STD_ON)
volatile Std_ReturnType              GenRealeaseResult;
#endif
#if (MCU_CLEARANDSETWAKEUPFACTOR_API == STD_ON)
volatile Std_ReturnType              GucWakeupResult;
#endif

/*******************************************************************************
**                      Private function declaration                          **
*******************************************************************************/
void symbol_before_halt(void);

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#if defined(RUN_OTHER_PE)
/* Enable register write to all HWIP for other than PE0 */
void Guard_Enable_PE()
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
  };

  //Enable write
  for (int i =0; i<sizeof(RSLVXX_base)/sizeof(RSLVXX_base[0]);i++)
  {
    volatile uint32 *ptr;
    ptr = (volatile uint32 *)(RSLVXX_base[i] + (uint32)0x18UL);
    *ptr = (uint32)0xA5A5A501UL;
  }

  //Write PBG0
  for (int i =0; i<sizeof(PBGXX_base)/sizeof(PBGXX_base[0]);i++)
  {
    for (int ii =0; ii<16;ii++)
    {
      volatile uint32 *ptr;
      ptr = (volatile uint32 *)(PBGXX_base[i] + ((uint32)ii * 0x8UL));
      *ptr |= 0x00000143UL;
    }
  }

  //Write PBG1
  for (int i =0; i<sizeof(PBGXX_base)/sizeof(PBGXX_base[0]);i++)
  {
    for (int ii =0; ii<16;ii++)
    {
      volatile uint32 *ptr;
      ptr = (volatile uint32 *)(PBGXX_base[i] + 0x4UL + ((uint32)ii * 0x8UL));
      *ptr |= 0xFFFFUL;
    }
  }

  //Disable write
  for (int i =0; i<sizeof(RSLVXX_base)/sizeof(RSLVXX_base[0]);i++)
  {
    volatile uint32 *ptr;
    ptr = (volatile uint32 *)(RSLVXX_base[i]+0x18UL);
    *ptr = 0xA5A5A500UL;
  }
}
#endif

int main(void)
#if defined(RUN_OTHER_PE)
{
  /* Open register access permission for all CPU */
  Guard_Enable_PE();
	while(1);
}
#if defined(RUN_PE1)
int main_PE1(void)
#elif defined(RUN_PE2)
int main_PE2(void)
#elif defined(RUN_PE3)
int main_PE3(void)
#elif defined(RUN_PE4)
int main_PE4(void)
#elif defined(RUN_PE5)
int main_PE5(void)
#elif defined(RUN_PE6)
int main_PE6(void)
#endif
#endif
{
  volatile uint32 LucIntCount;
  GenIsTestSuccess  = E_OK;
  GucIntCount       = 0;
  uint32 LulDelay = 0x0008;

  /* To Get Version Information of the MCU Driver component */
  #if (MCU_VERSION_INFO_API == STD_ON)
  Mcu_GetVersionInfo(&VersionInfo);

  if( (VersionInfo.vendorID         != MCU_VENDOR_ID) ||
      (VersionInfo.moduleID         != MCU_MODULE_ID) ||
      (VersionInfo.sw_major_version != MCU_SW_MAJOR_VERSION) ||
      (VersionInfo.sw_minor_version != MCU_SW_MINOR_VERSION) ||
      (VersionInfo.sw_patch_version != MCU_SW_PATCH_VERSION) )
  {
    GenIsTestSuccess = E_NOT_OK;
  }
  #endif /* (MCU_VERSION_INFO_API == STD_ON) */

  /* Initialization of the table reference bit in ICR register */
  Reg_Init();

  /* Check if the reset factor is power on reset*/
  if((MCU_POWER_ON_RESET_VALUE | MCU_EXTERNAL_RESET_VALUE) != MCU_RESF)
  {
    /* Initialise MCU Driver of variant 2*/
    Mcu_Init(Mcu_Config_Variant_2);
  }
  else
  {
    /* Initialise MCU Driver of variant 1*/
    Mcu_Init(Mcu_Config_Variant_1);
  }

  /* Initialize WDG */
  Wdg_Init();

  /* Initialize PORT */
  Port_Init();

  /* Enable Interrupt  */
  ENABLE_INTERRUPT();

  /* Initialize clock */
  #if (MCU_INIT_CLOCK == STD_ON)
  /* Canceling Module standby mode of GTM follow HWUM caution */  
  if (MCU_SWMRESS_GTM == 0)
  {
      MCU_MSR_KCPROT = 0xA5A5A501;
      MCU_MSR_GTM   = 0x00;
      MCU_MSR_KCPROT = 0xA5A5A500;
  }
  GenInitClockResult = Mcu_InitClock(MCU_MCUCLOCKSETTINGCONFIG);
  #endif /* (MCU_INIT_CLOCK == STD_ON) */

  GenPllStatus[0] = Mcu_GetPllStatus();
  LucIntCount = 10000;
  while((LucIntCount > 0) && (MCU_PLL_LOCKED != Mcu_GetPllStatus()))
  {
    LucIntCount--;
  }

  #if (MCU_NO_PLL == STD_OFF)
  GenDistributePllResult = Mcu_DistributePllClock();
  #endif /* (MCU_NO_PLL == STD_OFF) */

  GenPllStatus[1] = Mcu_GetPllStatus();

  /* Initialize LRAM section */
  #if defined MCU_LRAM_SETTING_0
  GenInitRamSectionResult[0] = Mcu_InitRamSection(MCU_LRAM_SETTING_0);
  #endif

  GenPllStatus[2] = Mcu_GetPllStatus();

  #if defined MCU_LRAM_SETTING_1
  GenInitRamSectionResult[1] = Mcu_InitRamSection(MCU_LRAM_SETTING_1);
  #endif

  #if defined MCU_LRAM_SETTING_2
  GenInitRamSectionResult[2] = Mcu_InitRamSection(MCU_LRAM_SETTING_2);
  #endif

  #if defined MCU_LRAM_SETTING_3
  GenInitRamSectionResult[3] = Mcu_InitRamSection(MCU_LRAM_SETTING_3);
  #endif

  #if defined MCU_LRAM_SETTING_4
  GenInitRamSectionResult[4] = Mcu_InitRamSection(MCU_LRAM_SETTING_4);
  #endif

  #if defined MCU_LRAM_SETTING_5
  GenInitRamSectionResult[5] = Mcu_InitRamSection(MCU_LRAM_SETTING_5);
  #endif

  #if defined MCU_LRAM_SETTING_6
  GenInitRamSectionResult[6] = Mcu_InitRamSection(MCU_LRAM_SETTING_6);
  #endif

  /* Initialize Local RAM self */
  #if defined MCU_LRAM_SELF_SETTING
  GenInitRamSectionResult[7] = Mcu_InitRamSection(MCU_LRAM_SELF_SETTING);
  #endif

  /* Initialize Cluster RAM */
  #if defined MCU_CRAM_SETTING
  GenInitRamSectionResult[8] = Mcu_InitRamSection(MCU_CRAM_SETTING);
  #endif

  /* Get Ram status */
  #if (MCU_GET_RAM_STATE_API == STD_ON)
  GenRamState = Mcu_GetRamState();
  #endif

  /* Get reset reason */
  GenResetReason[0] = Mcu_GetResetReason();

  /* Read the reset type value */
  GenRawResetReason[0] = Mcu_GetResetRawValue();

  /* Read Reset Reason again */
  GenResetReason[1] = Mcu_GetResetReason();

  /* Read the reset type value */
  GenRawResetReason[1] = Mcu_GetResetRawValue();

  #if (MCU_ECM_OPERATION == STD_ON)
  {
    uint32  LulPseudoCount;
    uint32  LulPseudoReg;
    uint32  LulPseudoVal;
    volatile uint32 *LpRegAddr;
    const uint32 LaaEcmPeTable[14] =
    {
      0x00000000UL,  /* ECMPE00 */
      0x00000000UL,  /* ECMPE01 */
      0x00010080UL,  /* ECMPE02 */
      0x00000000UL,  /* ECMPE03 */
      0x00000000UL,  /* ECMPE04 */
      0x00000000UL,  /* ECMPE05 */
      0x00000000UL,  /* ECMPE06 */
      0x00000001UL,  /* ECMPE07 */
      0x00000000UL,  /* ECMPE08 */
      0x00000000UL,  /* ECMPE09 */
      0x00000000UL,  /* ECMPE10 */
      0x00000000UL,  /* ECMPE11 */
      0x00000000UL,  /* ECMPE12 */
      0x00000000UL,  /* ECMPE13 */
    };

    /* Pseudo Error generation */
    MCU_ECMPEM = 0x00000000UL;
    LpRegAddr  = (volatile uint32*)MCU_ECMPE0_ADDRESS;
    for (LulPseudoReg = 0; LulPseudoReg < 14; LulPseudoReg++)
    {
      for (LulPseudoCount = 0; LulPseudoCount < 32; LulPseudoCount++)
      {
        LulPseudoVal = ((uint32)0x1 << LulPseudoCount);
        if(0 != (LaaEcmPeTable[LulPseudoReg] & LulPseudoVal))
        {
          /* ECM Key Code Protection Disable */
          MCU_ECMKCPROT = MCU_ECM_ENABLE_WRITE_ACCESS_VALUE;
          *LpRegAddr = LulPseudoVal;
          /* ECM Key Code Protection Enable */
          MCU_ECMKCPROT = MCU_ECM_DISABLE_WRITE_ACCESS_VALUE;
        }
      }
      LpRegAddr++;
    }
  }
  /* Check ECM error are raised */
  if(GucIntCount != 0x03)
  {
    GenIsTestSuccess = E_NOT_OK;
  }
  else
  {
    GenIsTestSuccess = E_OK;
  }
  #endif /* (MCU_ECM_OPERATION == STD_ON) */

  /* Invoke Mcu_SetMode with RUN MODE */
  Mcu_SetMode(MCU_MODE_SETTING_0);

  #if (MCU_RELEASEIOBUFFERHOLD_API == STD_ON)
  /* Release the I/O hold state after the wake-up */
  GenRealeaseResult = Mcu_ReleaseIoBufferHold();
  if( ((uint32)0x00000000UL != MCU_IOHOLD0) ||
      ((uint32)0x00000000UL != MCU_IOHOLD1) )
  {
    GenIsTestSuccess = E_NOT_OK;
  }
  else
  {
    GenIsTestSuccess = E_OK;
  }
  #endif

  #if (MCU_CLEARANDSETWAKEUPFACTOR_API == STD_ON)
  /* Clear and set WakeUp factor */
  GucWakeupResult = Mcu_ClearAndSetWakeUpFactor(MCU_MODE_SETTING_1);
  /* Check Wakeup factors are clear */
  if( ((uint32)0x00000000UL != MCU_WUFMON)  ||
      ((uint32)0x00000000UL != MCU_WUF0_A0) ||
      ((uint32)0x00000000UL != MCU_WUF0_A1) ||
      ((uint32)0x00000000UL != MCU_WUF0_A2) )
  {
    GenIsTestSuccess = E_NOT_OK;
  }
  else
  {
    GenIsTestSuccess = E_OK;
  }
  #endif

  /* Set TAUJ's clock is not stop when Chip trans to Stand by Mode */
  WRITE_REG(MCU_MSRKCPROT, 32, 0xA5A5A501UL);
  WRITE_REG(MCU_MSR_TAUJ_AWO, 32, 0x80000000);
  WRITE_REG(MCU_MSRKCPROT, 32, 0xA5A5A500UL);
  /* Enable interrupt of INTTAUJ2I0 Channel 0 interrupt 368  */
  WRITE_REG(INTC2_ADDR_EIC(372) ,16 ,0x41);
  /* Set MCU_TAUJ2CDR0 value */
  WRITE_REG(MCU_TAUJ2CDR0, 32, 0x0000FFFF);
  /* TAUJn Prescaler Clock Select Register */
  WRITE_REG(MCU_TAUJ2TPS, 16, 0x0000);
  /* MCU_TAUJ2TOE - 1: Enables independent timer output function */
  WRITE_REG(MCU_TAUJ2TOE, 8, 0x01);
  /* TAUJnCMORm - TAUJnMD[4:0] = 0000b , TAUJnMAS = Master */
  WRITE_REG(MCU_TAUJ2CMOR0, 16, 0x0801);
  /* TAUJnTS to start TAUJ timer */
  WRITE_REG(MCU_TAUJ2TS, 8, 0x01);
  while(0 < LulDelay)
  {
      LulDelay--;
  }
  /* Disable Interrupt  */
  DISABLE_INTERRUPT();

  /* Invoke Mcu_SetMode with STOP MODE */
  Mcu_SetMode(MCU_MODE_SETTING_1);

  #if (MCU_GETWAKEUPFACTOR_API == STD_ON)
  /* Check Wake-Up factors via Wake-Up Factor Registers */
  Mcu_GetWakeUpFactor(&Wakeupfactorinfo);
  if( (Wakeupfactorinfo.ulWufMonValue  != MCU_WUFMON)  ||
      (Wakeupfactorinfo.aaWufDetail[0] != MCU_WUF0_A0) ||
      (Wakeupfactorinfo.aaWufDetail[1] != MCU_WUF0_A1) ||
      (Wakeupfactorinfo.aaWufDetail[2] != MCU_WUF0_A2) )
  {
    GenIsTestSuccess = E_NOT_OK;
  }
  else
  {
    GenIsTestSuccess = E_OK;
  }
  #endif

  /* Application specific functionality */
  #if (MCU_PERFORM_RESET_API == STD_ON)
  if (GenResetReason[1] != MCU_SW_SYS_RST)
  {
    /* Perform the software reset */
    Mcu_PerformReset();
  }
  #endif

  while(1)
  { 
    /* Sample App End */  
  }
}

/*******************************************************************************
**                      Watchdog Initialization                               **
*******************************************************************************/
void Wdg_Init(void)
{
}

/*******************************************************************************
**                      Port Initialization                                   **
*******************************************************************************/
void Port_Init(void)
{
}

/*******************************************************************************
**                      Register Initialization                               **
*******************************************************************************/
void Reg_Init(void)
{
  volatile uint16 *pIcrReg;
  uint32 LulCount;
  
  pIcrReg = (volatile uint16 *)(MCU_ICR_REG_ADDR);
  
  for (LulCount = 0; LulCount < MCU_ICR_REG_NUM; LulCount++)
  {
     *pIcrReg = (uint16)MCU_EIC_REG_VALUE;
     pIcrReg++;
  }

  /* ECM ERROR Clear */
  {
    /* Register Protection Disable */
    MCU_ECMKCPROT = MCU_ECM_ENABLE_WRITE_ACCESS_VALUE;
    
    for (LulCount = MCU_ZERO; LulCount < MCU_FOURTEEN; LulCount++)
    {
      *(volatile uint32 *)(MCU_ECM_ECMESSTCn_ADDRESS + (0x4 * LulCount)) = 
                                                                     0xFFFFFFFF;
    }
    
    /* Register Protection Enable */
    MCU_ECMKCPROT = MCU_ECM_DISABLE_WRITE_ACCESS_VALUE;
  }
}

/*******************************************************************************
**                      Callback Function                                     **
*******************************************************************************/
void MCU_RESET_CALLOUT(void)
{
  GucIntCount++;
}

void Mcu_EcmNotification(uint16 EcmErrorNum)
{
  /* Action for configured ECM source */
  if ((uint16)80 == EcmErrorNum || (uint16)224 == EcmErrorNum 
                                || (uint16)71 == EcmErrorNum)
  {
    GucIntCount++;
  }
  else
  {
    /* Do nothing */
  }
}

/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
