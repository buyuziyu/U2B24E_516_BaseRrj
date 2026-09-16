/*============================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                         */
/* Module       = App_WDG_Common_Sample_1.c                                   */
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
** 2.4.0: 30/06/2025     : Update SW-VERSION for                               
**                         RH850/Ver22.01.00 (D) U2Ax release                   
** 2.3.2:  29/04/2025    : Update SW-VERSION for RH850/Ver22.00.03 U2Bx-E       
 * 2.3.1:  31/03/2025    : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E   
 * 2.3.0:  28/02/2025    : Update SW-VERSION for RH850/U2Cx MCAL                
 *                         Ver22.01.00/Ver22.01.00.D Release   
 * 2.2.0:  31/12/2024    : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D
 *                         Final release
 * 2.1.2:  30/10/2024    : Update SW-VERSION to 2.1.2
 * 2.1.1:  31/08/2024    : Update SW-VERSION to 2.1.1
 *                       : Update macro EIBD705 to EIBD
 *                       : Update macro EIBD306 to EIBD705
 * 2.0.3:  13/06/2024    : Initial Version
 */
/******************************************************************************/

/*******************************************************************************
**                      Instance Index                                        **
*******************************************************************************/
//#define WDG_INSTANCE_INDEX    1
/*******************************************************************************
**                     Include Section                                        **
*******************************************************************************/
#include "Wdg.h"
#include "App_WDG_Multi_PostBuildVariant_Sample.h"
#include "App_WDG_Common_Sample_1.h"

/*******************************************************************************
**                         Global Data                                        **
*******************************************************************************/
/* Set trigger condition to 3000 ms */
#define TIMEOUT_PE1_3000MS          0xBB8
Std_ReturnType GddResult_1;

/*******************************************************************************
**                        User function prototypes                            **
*******************************************************************************/

/*******************************************************************************
*                      Function Definitions                                   **
*******************************************************************************/
/*******************************************************************************
** Function Name         : main_PE1
**
** Description           : Sample application of WDG instance 1.
**
** Note                  : Following API need exclusive control between multi
**                         core for avoid resource access conflicting.
**                         - Wdg_59_Init()
**                         When the application call above APIs, please
**                         take care resource access conflicting between
**                         multi core.
*******************************************************************************/

/*******************************************************************************
** Function Name         : CAXI
**
** Description           : This function generate caxi operation for 
**                         exclusive control of multi core.
**                         The return value show previous value of LpRegAdd. 
*******************************************************************************/
/* This macro is used checking reset flag */
#define GET_BIT(REG, BIT) (((REG) >> BIT) & 0x1)

#if ((!defined(IAR)) && (!defined(CCRH)))
static asm uint32 CAXI(uint32 *LpRegAdd)
{
%con     LpRegAdd
  mov    LpRegAdd, r6
  mov           1, r10
  caxi   [r6], r0, r10
}
#endif

/*******************************************************************************
** Function Name         : main_PE1
**
** Description           : Sample application of WDG instance 1.
**
*******************************************************************************/
 /* The main function is implement for Wdg */
int main_PE1(void)
{
  Std_VersionInfoType Lddversioninfo;
  volatile  uint32 count;
  /* Enable Interrupt */
  ENABLE_INTERRUPT();
  while (count < 80000) {
     count++;
  };
  /* Bind EIC to CPU0*/
  #if ((WDG_WDTBA_CONFIGURED == STD_ON) && (WDG_WDTBA_CORE_CONFIGURED == 0x01))
   /* Binding EI level interrupt to CPU core 0 */
  EIBD = ((EIBD & EIBD_PEID_BOUND_PE0_VALUE)|0x01);
  #endif

    /* Check reset flag */
  #if ((WDG_WDTBA_CONFIGURED == STD_ON) && (WDG_WDTBA_CORE_CONFIGURED == 0x01))
   if (GET_BIT(APP_WDG_RESF, APP_WDG_RESF_BIT_POS_WDTBA) == APP_WDG_RST_FLAG_VALUE)
  #else 
   if (GET_BIT(APP_WDG_RESF, APP_WDG_RESF_BIT_POS) == APP_WDG_RST_FLAG_VALUE)
  #endif
 /* Check Reset flag for Variant2 */
  if (VARIANT_RESET == 2)
  {
    GddResult_1 = WDG_PASS;
    VARIANT_RESET = 0;
    while (1)
   {
    /* Infinite loop for debugging */
   }
  }
  /* Check PE1 Running Request */
  BR0CHK1 = WDG_SYNC_ENABLE;
  while (BR0SYNC1 != WDG_SYNC_COMPLETE)
  {
      /* No action required */
  };

  /* To get the version of the Watchdog Driver */
  Wdg_GetVersionInfo(&Lddversioninfo);

  /* Checking version */
  if ((WDG_VENDOR_ID == Lddversioninfo.vendorID) &&
     (WDG_MODULE_ID == Lddversioninfo.moduleID) &&
     (WDG_SW_MAJOR_VERSION == Lddversioninfo.sw_major_version) &&
     (WDG_SW_MINOR_VERSION == Lddversioninfo.sw_minor_version) &&
     (WDG_SW_PATCH_VERSION == Lddversioninfo.sw_patch_version))
  { 
    while(Wdg_GucInitSuccessFlag == E_NOT_OK);
    /* Initialize core 1 */
      /* Support ECM reset for post build variant */
#if ((WDG_WDTBA_CONFIGURED == STD_ON) && (WDG_WDTBA_CORE_CONFIGURED == 0x00))
  if (GET_BIT(APP_WDG_RESF, APP_WDG_RESF_BIT_POS_WDTBA) ==
                                           APP_WDG_RST_FLAG_VALUE)
#else 
  if (GET_BIT(APP_WDG_RESF, APP_WDG_RESF_BIT_POS) ==
                                           APP_WDG_RST_FLAG_VALUE)
 #endif
  {
    WDG_WAIT_MS(10 * 10); 
    Wdg_Init(Wdg_Config_Variant_2);
    VARIANT_RESET=2;
  }
  else
  {
    Wdg_Init(Wdg_Config_Variant_1);
    VARIANT_RESET=1;
  }
    /* Invoke SetMode function */
    Wdg_SetMode(WDGIF_SLOW_MODE);

    /* Sets the timeout value for the trigger counter */
    /* Set trigger condition to 3000 ms */
    Wdg_SetTriggerCondition(TIMEOUT_PE1_3000MS);
    /* Implement wdg trigger function and overflow after 3000 ms */
    while (1)
    {
      /* Waiting trigger function */
    }
  }
  else
  {
    /* Set return value to E_NOT_OK */
    GddResult_1 = E_NOT_OK;
  }
  return GddResult_1;
}/* End of main() function */

/******************************************************************************/
/*              End of file                                                   */
/******************************************************************************/
