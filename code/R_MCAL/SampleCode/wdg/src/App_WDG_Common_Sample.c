/*============================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                         */
/* Module       = App_WDG_Common_Sample.c                                     */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.        */
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
/*              Devices:        X2x                                           */
/*============================================================================*/

/*******************************************************************************
**                      Revision Control History                              **
*******************************************************************************/
/*
 * 2.4.1:  30/06/2025    : Remove SW-VERSION in file header 
 * 2.4.0: 30/06/2025     : Update SW-VERSION for                               
 *                         RH850/Ver22.01.00 (D) U2Ax release                   
 * 2.3.2:  29/04/2025    : Update SW-VERSION for RH850/Ver22.00.03 U2Bx-E  
 * 2.3.1:  31/03/2025    : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E   
 *                         As part of support U2Bx-E SampleApp on G4KH
 *                         Add Guard_Enable_PE()
 * 2.3.0:  28/02/2025    : Update SW-VERSION for RH850/U2Cx MCAL                
 *                         Ver22.01.00/Ver22.01.00.D Release   
 * 2.2.0:  31/12/2024    : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D
 *                         Final release
 * 2.1.2:  30/10/2024    : Update SW-VERSION to 2.1.2
 * 2.1.1:  31/08/2024    : Add macro RUN_OTHER_PE,RUN_PEx(x from 1 to 6)
 *                         for run multiple PE
 *                       : Update macro EIBD705 to EIBD
 *                       : Update macro EIBD306 to EIBD705
 *                       : Update SW-VERSION to 2.1.1
 * 2.0.0:  08/08/2023    : Update Sample app for supporting multicore
 * 1.4.3:  10/05/2022    : Release
 * 1.3.1:  30/06/2021    : Remove define WDG_INSTANCE_INDEX.
 *                         Change from #include "Wdg_59.h" to #include "Wdg_.h"
 *                         Update macros name: 
 *                         WDG_59_FEINT_DISABLE_ALLOWED -> WDG_FEINT_DISABLE_ALLOWED
 *                         WDG_59_WDTBA                 -> WDG_WDTBA
 *                         WDG_59_WDTB_UNIT_NUMBER      -> WDG_WDTB_UNIT_NUMBER
 *                         WDG_59_VENDOR_ID             -> WDG_VENDOR_ID
 *                         WDG_59_MODULE_ID             -> WDG_MODULE_ID
 *                         WDG_59_SW_MAJOR_VERSION      -> WDG_SW_MAJOR_VERSION
 *                         WDG_59_SW_MINOR_VERSION      -> WDG_SW_MINOR_VERSION
 *                         WDG_59_SW_PATCH_VERSION      -> WDG_SW_PATCH_VERSION
 *                         Update APIs name:  
 *                         Wdg_59_GetVersionInfo        -> Wdg_GetVersionInfo
 *                         Wdg_59_SetMode               -> Wdg_SetMode
 *                         Wdg_59_SetTriggerCondition   -> Wdg_SetTriggerCondition
 *                         Wdg_59_Init(Wdg_59_Config)   -> Wdg_Init(Wdg_Config)
 * 1.2.1:  06/05/2021    : Improve source code to fix Style_Format_015
 * 1.2.0:  26/08/2020    : Release
 * 1.1.0:  19/06/2020    : Release
 * 1.0.0:  20/03/2020    : Initial Version
 */
/******************************************************************************/

/*******************************************************************************
**                     Include Section                                        **
*******************************************************************************/
#include "Wdg.h"
#include "App_Wdg_Common_Sample.h"

/*******************************************************************************
**                      Defines                                               **
*******************************************************************************/
/* This macro is used checking reset flag */
#define GET_BIT(REG, BIT) (((REG) >> BIT) & 0x1)


/*******************************************************************************
**                         Global Data                                        **
*******************************************************************************/
/* Variable to store the test result */
volatile uint8 GucTestResult;


/*******************************************************************************
**                        User function prototypes                            **
*******************************************************************************/
void Mcu_Init(void);
void Port_Init(void);
void Interrupt_Init(void);

#if defined(RUN_OTHER_PE)
extern void Guard_Enable_PE(void);
#endif
//Define register value for DIO out
#define TEST_PORT_BASE  0xffd90000ul
#define Test_PWE        (*((volatile uint32 *)(TEST_PORT_BASE + 0x2F44ul)))
#define PM(n)           (*((volatile uint16 *)(TEST_PORT_BASE + 0x10 + (n * 0x40ul))))
#define PMC(n)          (*((volatile uint16 *)(TEST_PORT_BASE + 0x14 + (n * 0x40ul))))
#define P(n)            (*((volatile uint16 *)(TEST_PORT_BASE +(n * 0x40ul))))

//Set pin level
#define SET_PIN_LEVEL(port, pin, level)   \
            (port) = (((port)) & (~(1 << (pin)))) | ((level) << (pin))
/*******************************************************************************
**                                 Note                                       **
*******************************************************************************/
/* This Sample application related to following parameter in SampleApp.bat    */
/*                                                                            */
/* SampleApp.bat                                                              */
/*  CPU0_OPTION        : This parameter decide the parameter WDG_DRIVERA_FLAG */
/*                       is defined.                                          */
/*   Range             : CPU0_USED     : WDG Driver 0 is valid                */
/*                     : CPU0_NOT_USED : WDG Driver 0 isn't valid             */
/*  CPU1_OPTION        : This parameter decide CPU1 (PE1) is used and the     */
/*                       parameter WDG_DRIVERA_FLAG is defined.               */
/*   Range             : CPU0_USED     : WDG Driver 1 is valid.               */
/*                     : CPU0_NOT_USED : WDG Driver 1 isn't valid.            */

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
/* The main function is implement for Wdg */
int main(void)
#if defined (RUN_OTHER_PE)
{
  Guard_Enable_PE();
  Interrupt_Init();
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
  Std_VersionInfoType Lddversioninfo;
  /* Initialize test state */
  GucTestResult = WDG_FAIL;
  /*Enable guard for all PE */
  #if defined(RUN_OTHER_PE)
  Guard_Enable_PE();
  #endif
  /* Initialize MCU */
  Mcu_Init();

  /* Initialize PORT */
  Port_Init();

  /* Enable WDG interupt */
  Interrupt_Init();
#if (WDG_FEINT_DISABLE_ALLOWED == STD_ON)
  #if ((WDG_WDTBA_CONFIGURED == STD_ON) && (WDG_WDTBA_CORE_CONFIGURED == 0x00))
   /* Binding EI level interrupt to CPU core 0 */
   EIBD &= EIBD_PEID_BOUND_PE0_VALUE;
  #endif
#endif /* (DEVICE == U2x) */
  
  /* Check reset flag */
#if ((WDG_WDTBA_CONFIGURED == STD_ON) && (WDG_WDTBA_CORE_CONFIGURED == 0x00))
  if (GET_BIT(APP_WDG_RESF, APP_WDG_RESF_BIT_POS_WDTBA) ==
                                           APP_WDG_RST_FLAG_VALUE)
#else 
  if (GET_BIT(APP_WDG_RESF, APP_WDG_RESF_BIT_POS) ==
                                           APP_WDG_RST_FLAG_VALUE)
 #endif
  {
    GucTestResult = WDG_PASS;
    while (1);
  }

  /* To get the version of the Watchdog Driver */
  Wdg_GetVersionInfo(&Lddversioninfo);
  /* Checking version */
  if ((WDG_VENDOR_ID == Lddversioninfo.vendorID) &&
     (WDG_MODULE_ID == Lddversioninfo.moduleID) &&
     (WDG_SW_MAJOR_VERSION == Lddversioninfo.sw_major_version) &&
     (WDG_SW_MINOR_VERSION == Lddversioninfo.sw_minor_version) &&
     (WDG_SW_PATCH_VERSION == Lddversioninfo.sw_patch_version))

  {
    /* Initialization of Watchdog Driver */
    Wdg_Init(Wdg_Config);

    /* Invoke SetMode function */
    Wdg_SetMode(WDGIF_SLOW_MODE);

    /* Sets the timeout value for the trigger counter */
    /* Set trigger condition to 4000 ms, then report to DEM */ 
    Wdg_SetTriggerCondition(0x0FA0);
    /* Implement wdg trigger function and reset will occur after 4000 ms */
    while (1);
  }
  else
  {
    GucTestResult = WDG_FAIL;
  }
  return 0;
} /* End of main() function */


/******************************************************************************/
/*              End of file                                                   */
/******************************************************************************/
