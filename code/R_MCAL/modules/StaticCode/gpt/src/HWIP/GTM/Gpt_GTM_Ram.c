/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Gpt_GTM_Ram.c                                                                                       */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2024, 2025 Renesas Electronics Corporation. All rights reserved.                                               */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Global variable declarations                                                                                       */
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
 *  2.4.0  30/06/2025  : As part of QAC 11.6.0 support, following changes are made:
 *                       + Add message 1502, 3684
 *                       As part of GTM HWIP support, following changes is made:
 *                       + Add defined for Gpt_GaaGTMUnitConfig
 *  2.3.2  25/04/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03
 *  2.3.1  31/03/2025  : Update SW-VERSION for RH850/U2BxE MCAL Ver22.00.02/Ver22.00.02.D Release
 *  2.3.0  28/02/2025  : Update condition to define for functions in Gpt_GtmFunc structure
 *                     : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 *  2.2.0  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 *  2.1.2  31/10/2024  : Initial Version
 */
/**********************************************************************************************************************/
/***********************************************************************************************************************
**                                             Margin for Control History                                             **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (1:1502)    : The object '%1s' is defined but is not used within this project.                             */
/* Rule                : MISRA C:2012 Dir-1.1-C90                                                                     */
/* JV-01 Justification : This is accepted since there is no problem with the software behavior. This variable is      */
/*                       intended for user use, so it will not be used within the module scope                        */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3684)    : Array declared with unknown size.                                                            */
/* Rule                : MISRA C:2012 Rule-8.11, CERTCCM ARR02                                                        */
/* JV-01 Justification : Arrays used are verified in the file which are only declarations and size is configuration   */
/*                       dependent.                                                                                   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:5087)    : Use of #include directive after code fragment.                                               */
/* Rule                : MISRA C:2012 Rule-20.1                                                                       */
/* JV-01 Justification : This is done as per Memory Requirement, (MEMMAP003 - Specification of Memory Mapping).       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for RAM variable declarations */
#include "Gpt_GTM_Ram.h"
/* Included for function table of low level functions */
#include "Gpt_GTM_LLDriver.h"

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR Release version information */
#define GPT_GTM_RAM_C_AR_RELEASE_MAJOR_VERSION GPT_AR_RELEASE_MAJOR_VERSION_VALUE
#define GPT_GTM_RAM_C_AR_RELEASE_MINOR_VERSION GPT_AR_RELEASE_MINOR_VERSION_VALUE
#define GPT_GTM_RAM_C_AR_RELEASE_PATCH_VERSION GPT_AR_RELEASE_REVISION_VERSION_VALUE
/* File version information */
#define GPT_GTM_RAM_C_SW_MAJOR_VERSION    GPT_SW_MAJOR_VERSION_VALUE
#define GPT_GTM_RAM_C_SW_MINOR_VERSION    GPT_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (GPT_GTM_RAM_AR_RELEASE_MAJOR_VERSION != GPT_GTM_RAM_C_AR_RELEASE_MAJOR_VERSION)
  #error "Gpt_GTM_Ram.c : Mismatch in Release Major Version"
#endif
#if (GPT_GTM_RAM_AR_RELEASE_MINOR_VERSION !=  GPT_GTM_RAM_C_AR_RELEASE_MINOR_VERSION)
  #error "Gpt_GTM_Ram.c : Mismatch in Release Minor Version"
#endif
#if (GPT_GTM_RAM_AR_RELEASE_REVISION_VERSION != GPT_GTM_RAM_C_AR_RELEASE_PATCH_VERSION)
  #error "Gpt_GTM_Ram.c : Mismatch in Release Patch Version"
#endif

#if (GPT_GTM_RAM_SW_MAJOR_VERSION != GPT_GTM_RAM_C_SW_MAJOR_VERSION)
  #error "Gpt_GTM_Ram.c : Mismatch in Software Major Version"
#endif
#if (GPT_GTM_RAM_SW_MINOR_VERSION != GPT_GTM_RAM_C_SW_MINOR_VERSION)
  #error "Gpt_GTM_Ram.c : Mismatch in Software Minor Version"
#endif

/***********************************************************************************************************************
**                                                   Global Data                                                      **
***********************************************************************************************************************/
#if (GPT_TIMER_IP_GTM == STD_ON)
#define GPT_START_SEC_VAR_INIT_UNSPECIFIED
#include "Gpt_MemMap.h"
VAR(Gpt_HwFuncTableType, GPT_VAR_INIT) Gpt_GtmFunc =
{
  #if ((GPT_ATOM_UNIT_USED == STD_ON) || (GPT_TOM_UNIT_USED == STD_ON))
  &Gpt_HW_Gtm_UnitInit,
  &Gpt_HW_Gtm_ChannelInit,
  #if (GPT_DE_INIT_API == STD_ON)
  &Gpt_HW_Gtm_UnitDeInit,
  &Gpt_HW_Gtm_ChannelDeInit,
  #endif
  #if (GPT_TIME_ELAPSED_API == STD_ON)
  &Gpt_HW_Gtm_GetTimeElapsed,
  #endif
  #if (GPT_TIME_REMAINING_API == STD_ON)
  &Gpt_HW_Gtm_GetTimeRemaining,
  #endif
  &Gpt_HW_Gtm_StartTimer,
  &Gpt_HW_Gtm_StopTimer,
  &Gpt_HW_Gtm_EnableInterrupt,
  &Gpt_HW_Gtm_DisableInterrupt,
  #else // NO USE ANY GTM CHANNEL
  NULL_PTR,
  NULL_PTR,
  #if (GPT_DE_INIT_API == STD_ON)
  NULL_PTR,
  NULL_PTR,
  #endif
  #if (GPT_TIME_ELAPSED_API == STD_ON)
  NULL_PTR,
  #endif
  #if (GPT_TIME_REMAINING_API == STD_ON)
  NULL_PTR,
  #endif
  NULL_PTR,
  NULL_PTR,
  NULL_PTR,
  NULL_PTR,
  #endif
  /* End of ((GPT_ATOM_UNIT_USED == STD_ON) || (GPT_TOM_UNIT_USED == STD_ON)) */
  #if ((GPT_REPORT_WAKEUP_SOURCE == STD_ON) && (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON))
  NULL_PTR, /* pEnableWakeup */
  NULL_PTR, /* pDisableWakeup */
  #endif
  #if (GPT_GET_PREDEF_TIMER_VALUE_API == STD_ON)
  &Gpt_HW_Gtm_StartPredefTimer,
  &Gpt_HW_Gtm_StopPredefTimer,
  &Gpt_HW_Gtm_GetPredefTimerValue
  #endif
};
#define GPT_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define GPT_START_SEC_VAR_NO_INIT_PTR
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/* Global pointer variable for GTM Unit configuration */
const Gpt_GTMUnitConfigType* volatile Gpt_GpGTMUnitConfig;                                                              /* PRQA S 1502 # JV-01 */
#define GPT_STOP_SEC_VAR_NO_INIT_PTR
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#if ((GPT_TOM_UNIT_USED == STD_OFF) && (GPT_ATOM_UNIT_USED == STD_OFF))
#define GPT_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
const Gpt_GTMUnitConfigType Gpt_GaaGTMUnitConfig[];                                                                     /* PRQA S 3684 # JV-01 */
#define GPT_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* ((GPT_TOM_UNIT_USED == STD_OFF) && (GPT_ATOM_UNIT_USED == STD_OFF)) */

#endif /* GPT_TIMER_IP_GTM == STD_ON */

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
