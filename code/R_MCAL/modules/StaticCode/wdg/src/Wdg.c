/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Wdg.c                                                                                               */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Driver code of the Watchdog Component                                                                              */
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
 * 2.4.1:  30/06/2025    : Remove SW-VERSION in file header 
 * 2.4.0:  30/06/2025    : Update SW-VERSION for RH850/Ver22.01.00 (D) U2Ax release
 * 2.3.2:  29/04/2025    : Update SW-VERSION for RH850/Ver22.00.03 U2Bx-E  
 * 2.3.1:  31/03/2025    : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 * 2.3.0:  28/02/2025    : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024    : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final release
 * 2.1.2:  30/10/2024    : Update SW-VERSION to 2.1.2
 * 2.1.1:  31/08/2024    : Update SW-VERSION to 2.1.1
 *                       : As part of ARDAACL-39240
 *                         1. Add condition for Wdg_ECM_Init function
 * 2.0.1:  21/10/2023    : Add Message (3:3416), remove messages (2:2844), (2:2814), (2:2834).
 * 2.0.0:  18/07/2023    : Delete Message (3:3416), Message (3:3415), add Message (2:2844),
 *                         Change #include "Wdg_Mapping.h" with #include "Wdg_MemMap.h",
 *                         Support Multicore: Add Code sequence to access configured core, then use struct pointer to 
 *                         access registers, variables according to each used core 
 *                         Add Error check when calling invalid API.
 * 2.0.0:  10/05/2023    : Add Global Variable Used "Wdg_GpConfigPtr" in description of function Wdg_SetTriggerCondition
 *                         Change description of function Wdg_GetVersionInfo:
 *                         InOutput Parameters from "None" to "versioninfo", Output from "versioninfo" to "None"
 *                         Add function invoke WDG_DEM_REPORT_ERROR in description  function Wdg_SetMode 
 * 1.4.3:  10/05/2022    : Update SW-VERSION, Remove "else" statement don't use when no action required.
 *                         Change marco name WDG_TIME_UNIT_MSEC_TO_MICRO_SEC from TIME_UNIT_MSEC_TO_MICRO_SEC
 *                         Add QAC message 9.5.0 2004
 * 1.4.2:  10/03/2022    : Add QAC message 9.5.0 2814
 * 1.3.1:  07/07/2021    : Add QAC message 9.5.0
 *                         Format source code to 120 characters
 *                         Improve Violation tag (remove START/END)
 *         30/06/2021    : 1) Change file name from Wdg_59.c to Wdg.c.
 *                         2) Correct included file.
 *                         3) Remove _VendorID ("_59") in all macros, APIs, funtions,
 *                         variable, memory keywords, memclass and pointerclass
 *                         which has exit VendorID and format WDG_59_* or Wdg_59_*.
 *                         4) Change from #include "Wdg_59_MemMap.h" to #include "Wdg_Mapping.h".
 * 1.3.0:  20/01/2021    : Updated QAC message (2:3227)
 *                         Updated type of function parameter (remove const).
 *         25/11/2020    : Updated QAC message
 *                         Updated Wdg_59_SetTriggerCondition Api:
 *                         Removed check condition for
 *                         DET error WDG_59_E_INVALID_TIMEOUT
 * 1.2.0:  26/08/2020    : Release
 * 1.1.0:  19/06/2020    : Release
 * 1.0.3:  21/05/2020    : Revert critical section in
 *                         Wdg_59_SetTriggerCondition API and change
 *                         WDG_RAM_DATA_PROTECTION to
 *                         WDG_INTERRUPT_CONTROL_PROTECTION
 * 1.0.2:  19/05/2020    : Delete critical section in
 *                         Wdg_59_SetTriggerCondition API
 * 1.0.1:  17/04/2020    : Add case Report a DET if Wdg_59_SetTriggerCondition
 *                         is called with a timeout value smaller than
 *                         ulSettingTimeValue/ulSlowTimeValue/ulFastTimeValue/
 *                         ulDefaultTimeValue.
 * 1.0.0:  26/03/2020    : Initial Version
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (1:1503)    : The function '%1s' is defined but is not used within this project.                           */
/* Rule                : CERTCCM MSC07, MISRA C:2012 Rule-2.1, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : This is accepted, due to the module's API is exported for user's usage.                      */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:2004)    : No concluding 'else' exists in this 'if'-'else'-'if' statement.                              */
/* Rule                : CERTCCM MSC01, MISRA C:2012 Rule-15.7, CWE Rule CWE-398, CWE-569                             */
/* JV-01 Justification : The "else" statement with empty content is removed to improve readability.                   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (6:2880)    : This code is unreachable.                                                                    */
/* Rule                : CERTCCM MSC07, MISRA C:2012 Rule-2.1, CWE Rule CWE-670                                       */
/* JV-01 Justification : Part of the code is manually check and confirmed to be executable depending on the           */
/*                       configuration                                                                                */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (6:2992)    : The value of this 'if' controlling expression is always 'false'.                             */
/* Rule                : MISRA C:2012 Rule-14.3                                                                       */
/* JV-01 Justification : This is to support different configuration, macro value can be generated so that such        */
/*                       conditional statement can be either true or false                                            */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (6:2996)    : The result of this logical operation is always 'false'.                                      */
/* Rule                : MISRA C:2012 Rule-2.2, CWE Rule CWE-561, CWE-633                                             */
/* JV-01 Justification : Depending on device status, there is case where the 'if' will return 'true'.                 */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:3383)    : Cannot identify wraparound guard for unsigned arithmetic expression.                         */
/* Rule                : CERTCCM INT30                                                                                */
/* JV-01 Justification : It can still result in values that are out of range for the intended use, as intuitive       */
/*                       "invariants" may not hold                                                                    */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE Rule CWE-398, CWE-569                                            */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is accepted. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3416)    : Logical operation performed on expression with persistent side effects.                      */
/* Rule                : CERTCCM EXP45, CWE Rule CWE-398, CWE-569, CWE-737                                            */
/* JV-01 Justification : Logical operation accesses volatile object which is a register access. All register          */
/*                       addresses are generated with volatile qualifiers. There is no impact on the functionality    */
/*                       due to this conditional check for mode change.                                               */
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
/* Included for macro definitions */
#include "Wdg.h"
/* Included for RAM variable declarations */
#include "Wdg_Ram.h"
/* Included for declaration of the function Dem_ReportErrorStatus() */
#include "Dem.h"
#if (WDG_DEV_ERROR_DETECT == STD_ON)
/* Included for the declaration of Det_ReportError() */
#include "Det.h"
#endif
/**
 * include os
*/
#if (WDG_MULTI_CORE_SUPPORT == STD_ON)
#include "Os.h"
#endif

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define WDG_C_AR_RELEASE_MAJOR_VERSION    WDG_AR_RELEASE_MAJOR_VERSION_VALUE
#define WDG_C_AR_RELEASE_MINOR_VERSION    WDG_AR_RELEASE_MINOR_VERSION_VALUE
#define WDG_C_AR_RELEASE_REVISION_VERSION WDG_AR_RELEASE_REVISION_VERSION_VALUE
/* File version information */
#define WDG_C_SW_MAJOR_VERSION            WDG_SW_MAJOR_VERSION_VALUE
#define WDG_C_SW_MINOR_VERSION            WDG_SW_MINOR_VERSION_VALUE
/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (WDG_AR_RELEASE_MAJOR_VERSION != WDG_C_AR_RELEASE_MAJOR_VERSION)
  #error "Wdg.c : Mismatch in Release Major Version"
#endif
#if (WDG_AR_RELEASE_MINOR_VERSION != WDG_C_AR_RELEASE_MINOR_VERSION)
  #error "Wdg.c : Mismatch in Release Minor Version"
#endif
#if (WDG_AR_RELEASE_REVISION_VERSION != WDG_C_AR_RELEASE_REVISION_VERSION)
  #error "Wdg.c : Mismatch in Release Revision Version"
#endif
#if (WDG_SW_MAJOR_VERSION != WDG_C_SW_MAJOR_VERSION)
  #error "Wdg.c : Mismatch in Software Major Version"
#endif
#if (WDG_SW_MINOR_VERSION != WDG_C_SW_MINOR_VERSION)
  #error "Wdg.c : Mismatch in Software Minor Version"
#endif
/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/

/***********************************************************************************************************************
** Function Name         : Wdg_Init
**
** Service ID            : 0x00
**
** Description           : This service initialize the Watchdog driver and
**                         hardware.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : ConfigPtr Pointer to the configuration
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : None
**
** Preconditions         : None
**
** Global Variables Used : Wdg_GpConfigPtr.
**
** Functions Invoked     : Det_ReportError,
**                         Wdg_ECM_Init,
**                         Wdg_WDTBn_Init,
**                         Wdg_SetStatus.
**
** Registers Used        : None
**
** Reference ID          : WDG_DUD_ACT_001, WDG_DUD_ACT_001_ERR001, WDG_DUD_ACT_001_ERR003,
** Reference ID          : WDG_DUD_ACT_001_ERR002, WDG_DUD_ACT_001_GBL001
***********************************************************************************************************************/
#define WDG_START_SEC_PUBLIC_CODE
#include "Wdg_MemMap.h"

FUNC(void, WDG_PUBLIC_CODE) Wdg_Init(P2CONST(Wdg_ConfigType, AUTOMATIC, WDG_APPL_CONST) ConfigPtr)                      /* PRQA S 1503 # JV-01 */
{
 uint8 LucCoreIndex;
 #if (WDG_MULTI_CORE_SUPPORT == STD_ON)
 uint8 ucCoreId;
 /* Get Core id for code branching */
 ucCoreId = (uint8)GetCoreID();
 /* Covert Core Id to Core Index */
 LucCoreIndex = Wdg_GaaGetCoreId2Index[ucCoreId];                                                                      
 #else
 /* if Multicore is not configure, default coreid is 0x00 
    To optimize implementation */
 LucCoreIndex = WDG_ZERO;
 #endif
 #if (WDG_DEV_ERROR_DETECT == STD_ON)
  #if (WDG_MULTI_CORE_SUPPORT == STD_ON)
  /* Check invalid core for calling API */
  if(WDG_INVALID_INDEX == LucCoreIndex)
  {
   /* Report to DET */
   (void)Det_ReportError(WDG_MODULE_ID, WDG_INSTANCE_ID, WDG_INIT_SID, WDG_E_INVALID_CORE);
  }
  else
  #endif
 /* Report Error to DET, if the config pointer value is NULL */
 if (NULL_PTR == ConfigPtr)
 {
   /* Report Error to DET */
   (void)Det_ReportError(WDG_MODULE_ID, WDG_INSTANCE_ID, WDG_INIT_SID, WDG_E_PARAM_POINTER);
 } /* End of ConfigPtr == NULL_PTR */
 else
 #endif /* End of (WDG_DEV_ERROR_DETECT == STD_ON) */
 {
   /* Check whether the existing database is correct */
   if (WDG_DBTOC_VALUE != (ConfigPtr->ulStartOfDbToc))
    {
     #if (WDG_DEV_ERROR_DETECT == STD_ON)
     /* Report Error to DET */
     (void)Det_ReportError(WDG_MODULE_ID, WDG_INSTANCE_ID, WDG_INIT_SID, WDG_E_INVALID_DATABASE);
     #endif /* End of Check to check database */
    }
   else
   {
     /* Assign the config pointer value to global pointer */
     Wdg_GpConfigPtr = ConfigPtr;
     if (WDG_WDTBA != (Wdg_GpConfigPtr->aaUnitProperty[LucCoreIndex])->ddWdtbUnitNumber)                                /* PRQA S 3416 # JV-01 */
     { /* Initialize ECM Registers */
      #if (WDG_WDTBN_CONFIGURED == STD_ON)
       Wdg_ECM_Init();
      #endif
     }
     /* Initialize WDTBn Registers */
     Wdg_WDTBn_Init();
     #if (WDG_DEV_ERROR_DETECT == STD_ON)
     /* Set the state of Watchdog as idle */
     Wdg_SetStatus(WDG_IDLE);
     #endif
   } /* end if (WDG_DBTOC_VALUE !=(ConfigPtr->ulStartOfDbToc)) */
 }
}

#define WDG_STOP_SEC_PUBLIC_CODE
#include "Wdg_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Wdg_SetMode
**
** Service ID            : 0x01
**
** Description           : This service change the mode of the Watchdog timer
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : WdgIf_ModeType  Mode
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : Wdg_Init must be called before this
**                         function.
**
** Global Variables Used : Wdg_GddDriverState,
**                         Wdg_GddCurrentMode.
**
** Functions Invoked     : Det_ReportError,
**                         WDG_DEM_REPORT_ERROR
**                         Wdg_WDTBn_SetMode
**
** Registers Used        : None
**
** Reference ID          : WDG_DUD_ACT_002, WDG_DUD_ACT_002_ERR001,
** Reference ID          : WDG_DUD_ACT_002_ERR002, WDG_DUD_ACT_002_ERR003, WDG_DUD_ACT_002_ERR007,
** Reference ID          : WDG_DUD_ACT_002_ERR004, WDG_DUD_ACT_002_ERR005,
** Reference ID          : WDG_DUD_ACT_002_ERR006
***********************************************************************************************************************/
#define WDG_START_SEC_PUBLIC_CODE
#include "Wdg_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(Std_ReturnType, WDG_PUBLIC_CODE) Wdg_SetMode(WdgIf_ModeType Mode)                                                  /* PRQA S 1503 # JV-01 */
{ 
 uint8 LucCoreIndex;
 /* Variable to store the return value */
 Std_ReturnType LucReturnValue;
 #if (WDG_MULTI_CORE_SUPPORT == STD_ON)
 uint8 ucCoreId;
 /* Get Core id for code branching */
 ucCoreId = (uint8)GetCoreID();
 /* Covert Core Id to Core Index */
 LucCoreIndex = Wdg_GaaGetCoreId2Index[ucCoreId];                                                                      
 #else
 /* if Multicore is not configure, default coreid is 0x00 
    To optimize implementation */
 LucCoreIndex = WDG_ZERO;
 #endif
 /* Initialize the return value */
 LucReturnValue = E_OK;
 /* Report Error to DET, if state of Watchdog is not idle */
 #if (WDG_DEV_ERROR_DETECT == STD_ON)
 #if (WDG_MULTI_CORE_SUPPORT == STD_ON)
 /* Check invalid core for calling API */
 if(WDG_INVALID_INDEX == LucCoreIndex)
 {
   /* Report to DET */
   (void)Det_ReportError(WDG_MODULE_ID, WDG_INSTANCE_ID, WDG_SETMODE_SID, WDG_E_INVALID_CORE);
   /* Set Return Value as E_NOT_OK */
   LucReturnValue = E_NOT_OK;
 }
 else
 #endif
 {
  if (WDG_IDLE != *(Wdg_GaaGlobalAccPoint[LucCoreIndex].Wdg_GddDriverState))                                            
  {
   /* Report Error to DET */
   (void)Det_ReportError(WDG_MODULE_ID, WDG_INSTANCE_ID, WDG_SETMODE_SID, WDG_E_DRIVER_STATE);
   /* Set Return Value as E_NOT_OK */
   LucReturnValue = E_NOT_OK;
  } /* else No action required */
 /* Check whether input parameter 'Mode' is in the range */
 }
 if ((WDGIF_FAST_MODE != Mode) && (WDGIF_SLOW_MODE != Mode) && (WDGIF_OFF_MODE != Mode))
 {
   /* Report Error to DET, if the parameter mode is not within the range */
   (void)Det_ReportError(WDG_MODULE_ID, WDG_INSTANCE_ID, WDG_SETMODE_SID, WDG_E_PARAM_MODE);
   /* Set Return Value as E_NOT_OK */
   LucReturnValue = E_NOT_OK;
 } /* else No action required */
 /* Check if any DET error was reported */
 if (E_OK == LucReturnValue)
 #endif /* End of (WDG_DEV_ERROR_DETECT == STD_ON) */
 {
   /* Check for request mode is OFF */
   if ((WDGIF_OFF_MODE == Mode) && (WDGIF_OFF_MODE != *(Wdg_GaaGlobalAccPoint[LucCoreIndex].Wdg_GddCurrentMode)))
   {
     #if (WDG_E_DISABLE_REJECTED_CONFIGURED == STD_ON)
     /* Report Error to DEM as Event status is Failed */
     WDG_DEM_REPORT_ERROR(WDG_E_DISABLE_REJECTED, DEM_EVENT_STATUS_FAILED);
     #endif
     /* Set Return Value as E_NOT_OK */
     LucReturnValue = E_NOT_OK;
   } /* Requested mode and current mode are different */
   else if ((Mode != *(Wdg_GaaGlobalAccPoint[LucCoreIndex].Wdg_GddCurrentMode)) 
     && (WDGIF_OFF_MODE != *(Wdg_GaaGlobalAccPoint[LucCoreIndex].Wdg_GddCurrentMode)))
   {
     #if (WDG_E_MODE_FAILED_CONFIGURED == STD_ON)
     /* Report Error to DEM as Event status is Failed */
     WDG_DEM_REPORT_ERROR(WDG_E_MODE_FAILED, DEM_EVENT_STATUS_FAILED);
     #endif
     /* Set Return Value as E_NOT_OK */
     LucReturnValue = E_NOT_OK;
   }
   else
   {
     #if (WDG_E_DISABLE_REJECTED_CONFIGURED == STD_ON)
     /* Report Error to DEM as Event status is Passed */
     WDG_DEM_REPORT_ERROR(WDG_E_DISABLE_REJECTED, DEM_EVENT_STATUS_PASSED);
     #endif 
     #if (WDG_E_MODE_FAILED_CONFIGURED == STD_ON)
     /* Report Error to DEM as Event status is Passed */
     WDG_DEM_REPORT_ERROR(WDG_E_MODE_FAILED, DEM_EVENT_STATUS_PASSED);
     #endif
   }
   /* Check if any DEM error was not reported */
   if (E_OK == LucReturnValue)
   {
     /* Set WDTBn Registers for set mode */
     Wdg_WDTBn_SetMode(Mode);
   } /* else No action required */
 } /* if (E_OK == LucReturnValue) */
 return (LucReturnValue);
}

#define WDG_STOP_SEC_PUBLIC_CODE
#include "Wdg_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Wdg_SetTriggerCondition
**
** Service ID            : 0x03
**
** Description           : This service is used to initialize the trigger
**                         counter.
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : timeout
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : None
**
** Preconditions         : Wdg_Init must be called before this
**                         function.
**
** Global Variables Used : Wdg_GddDriverState,
**                         Wdg_GddCurrentMode,
**                         Wdg_GulTriggerCounter,
**                         Wdg_GpConfigPtr.
**
** Functions Invoked     : Det_ReportError.
**                         WDG_ENTER_CRITICAL_SECTION,
**                         WDG_EXIT_CRITICAL_SECTION.
**
** Registers Used        : None
**
** Reference ID          : WDG_DUD_ACT_003, WDG_DUD_ACT_003_CRT001,
** Reference ID          : WDG_DUD_ACT_003_CRT002, WDG_DUD_ACT_003_ERR001,
** Reference ID          : WDG_DUD_ACT_003_ERR002, WDG_DUD_ACT_003_ERR003,
** Reference ID          : WDG_DUD_ACT_003_GBL001, WDG_DUD_ACT_003_GBL002,
** Reference ID          : WDG_DUD_ACT_003_GBL003, WDG_DUD_ACT_003_GBL004,
** Reference ID          : WDG_DUD_ACT_003_GBL005
***********************************************************************************************************************/
#define WDG_START_SEC_PUBLIC_CODE
#include "Wdg_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, WDG_PUBLIC_CODE) Wdg_SetTriggerCondition(uint16 timeout)                                                     /* PRQA S 1503 # JV-01 */
{
  uint8 LucCoreIndex;
  #if (WDG_DEV_ERROR_DETECT == STD_ON)
  /* Variable to store the status value */
  VAR(uint8, AUTOMATIC) LucStatusValue;
  #endif
  #if (WDG_MULTI_CORE_SUPPORT == STD_ON)
  uint8 ucCoreId;
  /* Get Core id for code branching */
  ucCoreId = (uint8)GetCoreID();
  /* Covert Core Id to Core Index */
  LucCoreIndex = Wdg_GaaGetCoreId2Index[ucCoreId];                                                                      
  #else
  LucCoreIndex = WDG_ZERO;
  #endif
/* Check if DET is enabled */
  #if (WDG_DEV_ERROR_DETECT == STD_ON)
  /* Initialize the status value */
  LucStatusValue = E_OK;
  #if (WDG_MULTI_CORE_SUPPORT == STD_ON)
  /* Check invalid core for calling API */
  if(WDG_INVALID_INDEX == LucCoreIndex)
  {
    /* Report to DET */
    (void)Det_ReportError(WDG_MODULE_ID, WDG_INSTANCE_ID, WDG_SETTRIGGERCONDITION_SID, WDG_E_INVALID_CORE);
    /* Set Return Value as E_NOT_OK */
    LucStatusValue = E_NOT_OK;
  }
  else
  #endif
  {
   /* Check whether Watchdog Driver is initialized */
   if ((WDG_UNINIT == *(Wdg_GaaGlobalAccPoint[LucCoreIndex].Wdg_GddDriverState)) ||                                     
    (WDGIF_OFF_MODE == *(Wdg_GaaGlobalAccPoint[LucCoreIndex].Wdg_GddCurrentMode)))
   {
    /* Report to DET, if Watchdog is not in idle state */
    (void)Det_ReportError(WDG_MODULE_ID, WDG_INSTANCE_ID, WDG_SETTRIGGERCONDITION_SID, WDG_E_DRIVER_STATE);
    /* Set status Value as E_NOT_OK */
    LucStatusValue = E_NOT_OK;
   } /* else No action required */
  }
  /* Check whether timeout value requested is invalid value */
  if (WDG_MAXIMUM_TIMEOUT < timeout)                                                                                    /* PRQA S 2992, 2996 # JV-01, JV-01 */
  {
    /* Report to DET, if Watchdog is not in idle state */
    (void)Det_ReportError(WDG_MODULE_ID, WDG_INSTANCE_ID, WDG_SETTRIGGERCONDITION_SID, WDG_E_PARAM_TIMEOUT);            /* PRQA S 2880 # JV-01 */
    /* Set status Value as E_NOT_OK */
    LucStatusValue = E_NOT_OK;
  } /* else No action required */

  /* Check if any DET error was reported */
  if (E_OK == LucStatusValue)
  #endif /* End of (WDG_DEV_ERROR_DETECT == STD_ON) */
  {
   /* Check if critical section protection is required */
   #if (WDG_CRITICAL_SECTION_PROTECTION == STD_ON)
   WDG_ENTER_CRITICAL_SECTION(WDG_INTERRUPT_CONTROL_PROTECTION);
   #endif
   /* Check whether Watchdog disable is allowed */
   #if (WDG_DISABLE_ALLOWED == STD_ON)
   /* Check if the current mode is slow */
   if (WDGIF_SLOW_MODE == *(Wdg_GaaGlobalAccPoint[LucCoreIndex].Wdg_GddCurrentMode))
   {
     /* Check Arcitrary timing interrupt mode is STD_ON */
     if (WDG_TRUE == Wdg_GpConfigPtr->aaUnitProperty[LucCoreIndex]->blArbitraryTimingInterruptMode)                     /* PRQA S 3416 # JV-01 */
     {
       /* Set the trigger counter value considering the slow mode */
     *(Wdg_GaaGlobalAccPoint[LucCoreIndex].Wdg_GulTriggerCounter) = (timeout * WDG_TIME_UNIT_MSEC_TO_MICRO_SEC)         /* PRQA S 3383 # JV-01 */
                                                 / (Wdg_GpConfigPtr->aaUnitProperty[LucCoreIndex]->ulSettingTimeValue); 
     }
     else
     {
       /* Set the trigger counter value considering the slow mode */
       *(Wdg_GaaGlobalAccPoint[LucCoreIndex].Wdg_GulTriggerCounter) =
        (timeout * WDG_TIME_UNIT_MSEC_TO_MICRO_SEC) / (Wdg_GpConfigPtr->aaUnitProperty[LucCoreIndex]->ulSlowTimeValue); /* PRQA S 3383 # JV-01 */
     }
   }
   /* Check if the current mode is fast */
   else if (WDGIF_FAST_MODE == *(Wdg_GaaGlobalAccPoint[LucCoreIndex].Wdg_GddCurrentMode))                               /* PRQA S 2004 # JV-01 */
   {
     if (WDG_TRUE == Wdg_GpConfigPtr->aaUnitProperty[LucCoreIndex]->blArbitraryTimingInterruptMode)                     /* PRQA S 3416 # JV-01 */
     {
       /* Set the trigger counter value considering the fast mode */
       *(Wdg_GaaGlobalAccPoint[LucCoreIndex].Wdg_GulTriggerCounter) = (timeout * WDG_TIME_UNIT_MSEC_TO_MICRO_SEC) /     /* PRQA S 3383 # JV-01 */
         (Wdg_GpConfigPtr->aaUnitProperty[LucCoreIndex]->ulSettingTimeValue);
     }
     else
     {/* Set the trigger counter value considering the fast mode */
     *(Wdg_GaaGlobalAccPoint[LucCoreIndex].Wdg_GulTriggerCounter) =
       (timeout * WDG_TIME_UNIT_MSEC_TO_MICRO_SEC) / (Wdg_GpConfigPtr->aaUnitProperty[LucCoreIndex]->ulFastTimeValue);  /* PRQA S 3383 # JV-01 */
     }
   } /* else The trigger counter need not be set for off mode */
   #else
   /* Whether Watchdog disable is not allowed */
   /* Set the trigger counter value considering the default mode */
   *(Wdg_GaaGlobalAccPoint[LucCoreIndex].Wdg_GulTriggerCounter) =
     (timeout * WDG_TIME_UNIT_MSEC_TO_MICRO_SEC) / (Wdg_GpConfigPtr->aaUnitProperty[LucCoreIndex]->ulDefaultTimeValue); /* PRQA S 3383 # JV-01 */
   #endif /* End of (WDG_DISABLE_ALLOWED == STD_ON) */
   /* Check if critical section protection is required */
   #if (WDG_CRITICAL_SECTION_PROTECTION == STD_ON)
   WDG_EXIT_CRITICAL_SECTION(WDG_INTERRUPT_CONTROL_PROTECTION);
   #endif
  }
}
#define WDG_STOP_SEC_PUBLIC_CODE
#include "Wdg_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Wdg_GetVersionInfo
**
** Service ID            : 0x04
**
** Description           : This API returns the version information of WDG
**                         driver component.
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : versioninfo
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variables      : None
**
** Functions invoked     : Det_ReportError
**
** Registers Used        : None
**
** Reference ID          : WDG_DUD_ACT_004, WDG_DUD_ACT_004_ERR001
***********************************************************************************************************************/
#if (WDG_VERSION_INFO_API == STD_ON)
#define WDG_START_SEC_PUBLIC_CODE
#include "Wdg_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, WDG_PUBLIC_CODE) Wdg_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, WDG_APPL_DATA) versioninfo)        /* PRQA S 1503, 3432 # JV-01, JV-01 */
{
/* Check if DET is enabled */
  #if (WDG_DEV_ERROR_DETECT == STD_ON)
  /* Check if parameter passed is equal to Null pointer */
  if (NULL_PTR == versioninfo)
  {
   /* Report Error to DET */
   (void)Det_ReportError(WDG_MODULE_ID, WDG_INSTANCE_ID, WDG_GETVERSIONINFO_SID, WDG_E_PARAM_POINTER); 
  }
  else
  #endif /* (WDG_DEV_ERROR_DETECT == STD_ON) */
  {
   (versioninfo)->vendorID = (uint16)WDG_VENDOR_ID;
   (versioninfo)->moduleID = (uint16)WDG_MODULE_ID;
   (versioninfo)->sw_major_version = (uint8)WDG_SW_MAJOR_VERSION;
   (versioninfo)->sw_minor_version = (uint8)WDG_SW_MINOR_VERSION;
   (versioninfo)->sw_patch_version = (uint8)WDG_SW_PATCH_VERSION;
  }
}
#define WDG_STOP_SEC_PUBLIC_CODE
#include "Wdg_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /*(WDG_VERSION_INFO_API == STD_ON)*/

/***********************************************************************************************************************
**                                                    End Of File                                                     **
***********************************************************************************************************************/
