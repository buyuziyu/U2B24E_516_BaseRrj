/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Mcu.c                                                                                               */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains API function implementations of MCU Driver                                                      */
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
 * 2.5.1:  30/06/2025   : Update SW-VERSION for U2Bx Ver22.02.00.001 Release
 * 2.5.0:  30/06/2025   : Update SW-VERSION for U2Ax Ver22.01.00(D) Release
 * 2.4.0:  31/05/2025   : Update SW-VERSION for U2Cx Ver21.01.01 Release
 * 2.3.2:  29/04/2025   : Update SW-VERSION for U2Ax Ver22.00.03 Release
 * 2.3.1:  31/03/2025   : Update SW-VERSION for U2BxE Ver22.00.02 Release
 * 2.3.0:  28/02/2025   : Update SW-VERSION for Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024   : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Release
 * 2.1.2:  31/10/2024   : Update SW-VERSION to 2.1.2
 * 2.1.1:  30/08/2024   : Update SW-VERSION to 2.1.1
 *                        As part of ARDAACL-47932 (ARDAACL-47792), following changes are made:
 *                        - Update funtion Mcu_Init call Mcu_ECCSetRramEccInt to init Retention RAM ECC
 * 2.0.1:  10/10/2023   : Move checking of MCU_E_UNINIT to be performed first in Mcu_GetWakeUpFactor
 * 2.0.0:  10/07/2023   : Remove redundant QAC message 0857, 3469
 * 1.4.5:  06/01/2023   : As new Mcu structure:
 *                       - Update API:  Mcu_Init, Mcu_InitRamSection, Mcu_InitClock, Mcu_DistributePllClock,
 *                       Mcu_PerformReset, Mcu_SetMode Mcu_ReleaseIoBufferHold, Mcu_GetWakeUpFactor,
 *                       Mcu_ClearAndSetWakeUpFactor, Mcu_GetPllStatus, Mcu_GetRamState,
 *                       Mcu_GetResetRawValue, Mcu_GetResetReason
 *                       - Update QAC messages
 * 1.4.4:  15/07/2022   : Update QAC message 9.5.0
 * 1.4.3:  23/06/2022   : Add QAC message (2:2814) and updated QAC message
 *         24/05/2022   : Removed redundant QAC message
 *         11/05/2022   : Removed "else" statement don't use when no action required, updated QAC message
 *         22/04/2022   : Update SW-VERSION to 1.4.3, update QAC mesage
 * 1.3.1:  02/07/2021   : Add QAC message 9.5.0
 *                        Format source code to 120 characters
 *                        Improve Violation tag (remove START/END)
 * 1.2.0:  17/07/2020   : Release
 * 1.1.0:  19/06/2020   : Release
 * 1.0.5:  20/05/2020   : As per ticket #264311
 *                        Update header comment for API Mcu_InitRamSection
 * 1.0.4:  18/05/2020   : As per ticket #268957
 *                       Update Critical section 's name in MCU driver to unify with other MCAL modules
 * 1.0.3:  14/05/2020   : Update comment header section
 * 1.0.2:  26/04/2020   : As per #263738
 *                        + Fix QAC message for Mcu_Init.
 *                        As per #259321
 *                        + Fix range for check argument of Mcu_InitClock
 * 1.0.1:  17/01/2020   : As per #264311, update to remove check DEM error MCU_E_ECM_INIT_FAILURE from
 *                        Mcu_InitRamSection
 * 1.0.0:  10/01/2020   : Initial Version
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:0316)    : Cast from a pointer to void to a pointer to object type.                                     */
/* Rule                : MISRA C:2012 Rule-11.5, CWE Rule CWE-188, CWE-398, CWE-569                                   */
/* JV-01 Justification : A cast should not be performed between a pointer to object type and a different pointer to   */
/*                       object type.                                                                                 */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0488)    : Performing pointer arithmetic.                                                               */
/* Rule                : MISRA C:2012 Rule-18.4, CERTCCM EXP08, CWE Rule CWE-188, CWE-398, CWE-569                    */
/* JV-01 Justification : This is to get the ID in the data structure in the code.                                     */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1503)    : The function '%1s' is defined but is not used within this project.                           */
/* Rule                : MISRA C:2012 Rule-2.1, CERTCCM MSC07, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : This is accepted, due to the module's API is exported for user's usage.                      */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:2982)    : This assignment is redundant. The value of this object is never used before being modified.  */
/* Rule                : MISRA C:2012 Rule-2.2, CERTCCM MSC07, MSC13, CWE Rule CWE-14, CWE-398, CWE-561, CWE-563,     */
/*                       CWE-569, CWE-633                                                                             */
/* JV-01 Justification : The variable needs to be initialized before using it.                                        */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3416)    : Logical operation performed on expression with persistent side effects.                      */
/* Rule                : CERTCCM EXP45, CWE Rule CWE-398, CWE-569, CWE-737                                            */
/* JV-01 Justification : Logical operation accesses volatile object which is a register access. All register          */
/*                       addresses are generated with volatile qualifiers. There is no impact on the functionality    */
/*                       due to this conditional check for mode change.                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE Rule CWE-398, CWE-569                                            */
/* JV-01 Justification : Compiler keyword (macro) is defined and used following AUTOSAR standard rule. It is accepted.*/
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
/* Included for module version information */
#include "Mcu.h"
/* Included for post build types, macros */
#include "Mcu_PBTypes.h"
/* Included for RAM variable declarations */
#include "Mcu_Ram.h"
#if (MCU_DEV_ERROR_DETECT == STD_ON)
/* Included for the declaration of Det_ReportError() */
#include "Det.h"
#endif
/* Included for declaration of the function Dem_ReportErrorStatus() and Dem_SetEventStatus() */
#include "Dem.h"

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/

/* AUTOSAR release version information */
#define MCU_C_AR_RELEASE_MAJOR_VERSION    MCU_AR_RELEASE_MAJOR_VERSION_VALUE
#define MCU_C_AR_RELEASE_MINOR_VERSION    MCU_AR_RELEASE_MINOR_VERSION_VALUE
#define MCU_C_AR_RELEASE_REVISION_VERSION MCU_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define MCU_C_SW_MAJOR_VERSION            MCU_SW_MAJOR_VERSION_VALUE
#define MCU_C_SW_MINOR_VERSION            MCU_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/

#if (MCU_AR_RELEASE_MAJOR_VERSION != MCU_C_AR_RELEASE_MAJOR_VERSION)
#error "Mcu.c : Mismatch in Release Major Version"
#endif

#if (MCU_AR_RELEASE_MINOR_VERSION != MCU_C_AR_RELEASE_MINOR_VERSION)
#error "Mcu.c : Mismatch in Release Minor Version"
#endif

#if (MCU_AR_RELEASE_REVISION_VERSION != MCU_C_AR_RELEASE_REVISION_VERSION)
#error "Mcu.c : Mismatch in Release Revision Version"
#endif

#if (MCU_SW_MAJOR_VERSION != MCU_C_SW_MAJOR_VERSION)
#error "Mcu.c : Mismatch in Software Major Version"
#endif

#if (MCU_SW_MINOR_VERSION != MCU_C_SW_MINOR_VERSION)
#error "Mcu.c : Mismatch in Software Minor Version"
#endif
/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/

/**********************************************************************************************************************/
/**                                       Internal Function Prototypes                                               **/
/**********************************************************************************************************************/

#define MCU_START_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"

STATIC FUNC(void, MCU_PRIVATE_CODE) Mcu_SetStatus(const boolean LblStatus);

#define MCU_STOP_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/

/***********************************************************************************************************************
** Function Name      : Mcu_Init
**
** Service ID         : 0x00
**
** Description        : This service performs initialization of the MCU Driver component.
**
** Sync/Async         : Synchronous
**
** Reentrancy         : Non-Reentrant
**
** Input Parameters   : ConfigPtr - Pointer to MCU Driver Configuration set
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : None
**
** Preconditions      : None
**
** Global Variables   : Mcu_GpConfigPtr, Mcu_GpClockHwInfo, Mcu_GpResetHwInfo, Mcu_GpClmHwInfo, Mcu_GpStbHwInfo,
**                      Mcu_GpVmonHwInfo, Mcu_GpDmonHwInfo, Mcu_GpWUFMONHwInfo, Mcu_GpWakeUpHwInfo,
**                      Mcu_GpIOBufferHoldHwInfo, Mcu_GpEcmHwInfo, Mcu_GpEccHwInfo, Mcu_GucCramEccEcmInit,
**                      Mcu_GucLramEccEcmInit, Mcu_GucRramEccEcmInit
**
** Function Invoked   : Det_ReportError, Mcu_ECCSetLramEccInt, Mcu_ECCSetCramEccInt, Mcu_ECCSetRramEccInt,
**                      Mcu_ECMSetEcmRegister, Mcu_RSTSetEcmReset, Mcu_VMNSetDelayMonitorDiag,
**                      Mcu_VMNSetVoltageMonitorDiag, Mcu_SetStatus
**
** Registers Used     : None
**
** Reference ID       : MCU_DUD_ACT_001, MCU_DUD_ACT_001_ERR001, MCU_DUD_ACT_001_ERR002, MCU_DUD_ACT_001_ERR003,
** Reference ID       : MCU_DUD_ACT_001_ERR004, MCU_DUD_ACT_001_ERR005, MCU_DUD_ACT_001_ERR006, MCU_DUD_ACT_001_ERR007,
** Reference ID       : MCU_DUD_ACT_001_GBL001, MCU_DUD_ACT_001_GBL002, MCU_DUD_ACT_001_GBL003, MCU_DUD_ACT_001_GBL004,
** Reference ID       : MCU_DUD_ACT_001_GBL005, MCU_DUD_ACT_001_GBL006, MCU_DUD_ACT_001_GBL007, MCU_DUD_ACT_001_GBL008
** Reference ID       : MCU_DUD_ACT_001_GBL009, MCU_DUD_ACT_001_GBL010, MCU_DUD_ACT_001_GBL011, MCU_DUD_ACT_001_GBL012,
** Reference ID       : MCU_DUD_ACT_001_GBL013, MCU_DUD_ACT_001_GBL014
***********************************************************************************************************************/
#define MCU_START_SEC_PUBLIC_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(void, MCU_PUBLIC_CODE) Mcu_Init(P2CONST(Mcu_ConfigType, AUTOMATIC, MCU_APPL_CONST) ConfigPtr)                      /* PRQA S 1503 # JV-01 */
{
  Std_ReturnType LucMcuInitStatus;
  LucMcuInitStatus = E_OK;                                                                                              /* PRQA S 2982 # JV-01 */

  #if (MCU_DEV_ERROR_DETECT == STD_ON)
  /* Report to DET, if configuration pointer is NULL pointer */
  if (NULL_PTR == ConfigPtr)
  {
    /* Report to DET, NULL_PTR */
    (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_INIT_SID, MCU_E_INIT_FAILED);
  }
    /* Report to DET if the DBTOC value is wrong */
  else if (MCU_DBTOC_VALUE != (ConfigPtr->ulStartOfDbToc))
  {
    /* No database flashed. Hence, report to DET */
    (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_INIT_SID, MCU_E_INVALID_DATABASE);
  }
  else
  #endif /* MCU_DEV_ERROR_DETECT == STD_ON */
  {
    /* Assign the global pointer with the module configuration pointer */
    Mcu_GpConfigPtr = (P2CONST(Mcu_ConfigType, AUTOMATIC, MCU_CONFIG_DATA))ConfigPtr;

    /* Get the pointer to clock hardware registers information structure */
    Mcu_GpClockHwInfo = (P2CONST(Mcu_ClockHwInfoType, AUTOMATIC, MCU_CONFIG_DATA))Mcu_GpConfigPtr->pClockHwInfo;        /* PRQA S 0316 # JV-01 */

    /* Get the pointer to reset hardware registers information structure */
    Mcu_GpResetHwInfo = (P2CONST(Mcu_ResetHwInfoType, AUTOMATIC, MCU_CONFIG_DATA))Mcu_GpConfigPtr->pRstHwInfo;          /* PRQA S 0316 # JV-01 */

    #if (MCU_CLMA_OPERATION == STD_ON)
    /* Get the pointer to clock monitor hardware registers information structure */
    Mcu_GpClmHwInfo = (P2CONST(Mcu_ClmHwInfoType, AUTOMATIC, MCU_CONFIG_DATA))Mcu_GpConfigPtr->pClmHwInfo;              /* PRQA S 0316 # JV-01 */
    #endif /* MCU_CLMA_OPERATION == STD_ON */

    #if (MCU_MODE_TRANSITION_SUPPORT == STD_ON)
    /* Get the pointer to standby hardware registers information structure */
    Mcu_GpStbHwInfo = (P2CONST(Mcu_StbHwInfoType, AUTOMATIC, MCU_CONFIG_DATA))Mcu_GpConfigPtr->pStbHwInfo;              /* PRQA S 0316 # JV-01 */
    #endif /* MCU_MODE_TRANSITION_SUPPORT == STD_ON */

    #if (MCU_VMON_DIAG_OPERATION == STD_ON)
    /* Get the pointer to voltage monitor hardware registers information structure */
    Mcu_GpVmonHwInfo = (P2CONST(Mcu_VmonHwInfoType, AUTOMATIC, MCU_CONFIG_DATA))Mcu_GpConfigPtr->pVmonHwInfo;           /* PRQA S 0316 # JV-01 */
    #endif /* MCU_VMON_DIAG_OPERATION == STD_ON */

    #if (MCU_DMON_DIAG_OPERATION == STD_ON)
    /* Get the pointer to delay monitor hardware registers information structure */
    Mcu_GpDmonHwInfo = (P2CONST(Mcu_DmonHwInfoType, AUTOMATIC, MCU_CONFIG_DATA))Mcu_GpConfigPtr->pDmonHwInfo;           /* PRQA S 0316 # JV-01 */
    #endif /* MCU_DMON_DIAG_OPERATION == STD_ON */

    #if (MCU_GETWAKEUPFACTOR_API == STD_ON)
    /* Get the pointer to wake-up factor monitor hardware registers information structure */
    Mcu_GpWUFMONHwInfo = (P2CONST(Mcu_WUFMONHwInfoType, AUTOMATIC, MCU_CONFIG_DATA))Mcu_GpConfigPtr->pWUFMONHwInfo;     /* PRQA S 0316 # JV-01 */
    #endif /* MCU_GETWAKEUPFACTOR_API == STD_ON */

    #if ((MCU_GETWAKEUPFACTOR_API == STD_ON) || (MCU_CLEARANDSETWAKEUPFACTOR_API == STD_ON))
    /* Get the pointer to wake-up hardware registers information structure */
    Mcu_GpWakeUpHwInfo = (P2CONST(Mcu_WakeUpHwInfoType, AUTOMATIC, MCU_CONFIG_DATA))Mcu_GpConfigPtr->pWUFHwInfo;        /* PRQA S 0316 # JV-01 */
    #endif /* ((MCU_GETWAKEUPFACTOR_API == STD_ON) || (MCU_CLEARANDSETWAKEUPFACTOR_API == STD_ON)) */

    #if (MCU_RELEASEIOBUFFERHOLD_API == STD_ON)
    /* Get the pointer to IO buffer hold hardware registers information structure */
    Mcu_GpIOBufferHoldHwInfo =
      (P2CONST(Mcu_IOBufferHoldHwInfoType, AUTOMATIC, MCU_CONFIG_DATA))Mcu_GpConfigPtr->pIOBufferHoldHwInfo;            /* PRQA S 0316 # JV-01 */
    #endif /* MCU_RELEASEIOBUFFERHOLD_API == STD_ON */

    #if (MCU_ECM_OPERATION == STD_ON)
    /* Get the pointer to ECM hardware registers information structure */
    Mcu_GpEcmHwInfo = (P2CONST(Mcu_EcmHwInfoType, AUTOMATIC, MCU_CONFIG_DATA))Mcu_GpConfigPtr->pEcmHwInfo;              /* PRQA S 0316 # JV-01 */
    #endif /* MCU_ECM_OPERATION == STD_ON */

    /* Get the pointer to ECC hardware registers information structure */
    Mcu_GpEccHwInfo = (P2CONST(Mcu_EccHwInfoType, AUTOMATIC, MCU_CONFIG_DATA))Mcu_GpConfigPtr->pEccHwInfo;              /* PRQA S 0316 # JV-01 */

    /* Settings for the behavior of the device during reset */
    Mcu_RSTSetEcmReset();

    #if (MCU_VMON_DIAG_OPERATION == STD_ON)
    LucMcuInitStatus = Mcu_VMNSetVoltageMonitorDiag();
    #ifdef MCU_E_VMON_DIAG_FAILURE
    if (E_NOT_OK == LucMcuInitStatus)
    {
      /* Report to DEM. VMON DIAG Failed. */
      MCU_DEM_REPORT_ERROR(MCU_E_VMON_DIAG_FAILURE, DEM_EVENT_STATUS_FAILED);
    }
    else
    {
      /* Report to DEM. VMON DIAG Passed. */
      MCU_DEM_REPORT_ERROR(MCU_E_VMON_DIAG_FAILURE, DEM_EVENT_STATUS_PASSED);
    }
    #endif /* MCU_E_VMON_DIAG_FAILURE */
    #endif /* MCU_VMON_DIAG_OPERATION == STD_ON */

    #if (MCU_DMON_DIAG_OPERATION == STD_ON)
    if (E_OK == LucMcuInitStatus)
    {
      LucMcuInitStatus = Mcu_VMNSetDelayMonitorDiag();

      #if defined(MCU_E_DMON_DIAG_FAILURE)
      if (E_NOT_OK == LucMcuInitStatus)
      {
        /* Report to DEM. DMON DIAG Failed. */
        MCU_DEM_REPORT_ERROR(MCU_E_DMON_DIAG_FAILURE, DEM_EVENT_STATUS_FAILED);
      }
      else
      {
        /* Report to DEM. DMON DIAG Passed. */
        MCU_DEM_REPORT_ERROR(MCU_E_DMON_DIAG_FAILURE, DEM_EVENT_STATUS_PASSED);
      }
      #endif /* MCU_E_DMON_DIAG_FAILURE */
    } /* else No action required */
    #endif /* MCU_DMON_DIAG_OPERATION == STD_ON */

    if (E_OK == LucMcuInitStatus)
    {
      #if (MCU_RAM_ECCECM_SETTING_INITRAMSECTION == STD_OFF)
      Mcu_ECCSetLramEccInt();
      Mcu_ECCSetCramEccInt();
      #if (MCU_RETENTION_RAM_SETTING == STD_ON)
      Mcu_ECCSetRramEccInt();
      #endif /* MCU_RETENTION_RAM_SETTING == STD_ON */
      #else
      Mcu_GucLramEccEcmInit = MCU_RAM_ECCECM_INIT_NOT_DONE;
      Mcu_GucCramEccEcmInit = MCU_RAM_ECCECM_INIT_NOT_DONE;
      #if (MCU_RETENTION_RAM_SETTING == STD_ON)
      Mcu_GucRramEccEcmInit = MCU_RAM_ECCECM_INIT_NOT_DONE;
      #endif /* MCU_RETENTION_RAM_SETTING == STD_ON */
      #endif /* MCU_RAM_ECCECM_SETTING_INITRAMSECTION == STD_OFF */

      #if (MCU_ECM_OPERATION == STD_ON)
      LucMcuInitStatus = Mcu_ECMSetEcmRegister(MCU_ECM_SETTING_INIT);
      #if (MCU_RAM_ECCECM_SETTING_INITRAMSECTION == STD_OFF)
      if (E_OK == LucMcuInitStatus)
      {
        LucMcuInitStatus = Mcu_ECMSetEcmRegister(MCU_ECM_SETTING_AFTER_RAMINIT_LRAM);

        if (E_OK == LucMcuInitStatus)
        {
          LucMcuInitStatus = Mcu_ECMSetEcmRegister(MCU_ECM_SETTING_AFTER_RAMINIT_CRAM);
        } /* else No action required */
      } /* else No action required */
      #if (MCU_RETENTION_RAM_SETTING == STD_ON)
      if (E_OK == LucMcuInitStatus)
      {
        LucMcuInitStatus = Mcu_ECMSetEcmRegister(MCU_ECM_SETTING_AFTER_RAMINIT_RRAM);
      } /* else No action required */
      #endif /* MCU_RETENTION_RAM_SETTING == STD_ON */
      #endif /* MCU_RAM_ECCECM_SETTING_INITRAMSECTION == STD_OFF */

      #if defined(MCU_E_ECM_INIT_FAILURE)
      if (E_NOT_OK == LucMcuInitStatus)
      {
        /* Report to DEM */
        /* ECM Register setting Failed. */
        MCU_DEM_REPORT_ERROR(MCU_E_ECM_INIT_FAILURE, DEM_EVENT_STATUS_FAILED);
      } /* else No action required */
      #endif /* MCU_E_ECM_INIT_FAILURE */
      #endif /* MCU_ECM_OPERATION == STD_ON */
    } /* else No action required */

    /* Check if any error */
    if (E_OK == LucMcuInitStatus)
    {
      /* Set the global variable status */
      Mcu_SetStatus(MCU_INITIALIZED);
    } /* else No action required */
  }
}
#define MCU_STOP_SEC_PUBLIC_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name      : Mcu_InitRamSection
**
** Service ID         : 0x01
**
** Description        : This function initializes the RAM section as provided from the configuration structure.
**
** Sync/Async         : Synchronous
**
** Reentrancy         : Non-Reentrant
**
** Input Parameters   : RamSection - Id for RAM section
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : Std_ReturnType (E_OK, E_NOT_OK)
**
** Preconditions      : MCU Driver component must be initialized
**
** Global Variables   : Mcu_GblDriverStatus
**
** Function Invoked   : Det_ReportError, Mcu_RAMInitRamSection
**
** Registers Used     : None
**
** Reference ID       : MCU_DUD_ACT_002, MCU_DUD_ACT_002_ERR001, MCU_DUD_ACT_002_ERR002
***********************************************************************************************************************/
#define MCU_START_SEC_PUBLIC_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, MCU_PUBLIC_CODE) Mcu_InitRamSection(Mcu_RamSectionType RamSection)                                 /* PRQA S 1503 # JV-01 */
{
  Std_ReturnType LucReturnValue;

  /* Initialize return value with E_OK */
  LucReturnValue = E_OK;

  #if (MCU_DEV_ERROR_DETECT == STD_ON)
  /* Report to DET, if the component is not initialized */
  if (MCU_UNINITIALIZED == Mcu_GblDriverStatus)                                                                         /* PRQA S 3416 # JV-01 */
  {
    /* Report to DET */
    (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_INITRAMSECTION_SID, MCU_E_UNINIT);
    LucReturnValue = E_NOT_OK;
  } /* else No action required */

  /* Report to DET, if RamSetting Id is out of range */
  if (E_OK == LucReturnValue)
  {
    if ((MCU_MAX_RAMSETTING == MCU_ZERO) || (MCU_MAX_RAMSETTING <= RamSection))
    {
      /* Report to DET */
      (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_INITRAMSECTION_SID, MCU_E_PARAM_RAMSECTION);
      LucReturnValue = E_NOT_OK;
    } /* else No action required */
  } /* else No action required */

  /* Check if any development error occurred */
  if (E_OK == LucReturnValue)
  #endif /* MCU_DEV_ERROR_DETECT == STD_ON */
  {
    /* Initilize for selected RAM section */
    Mcu_RAMInitRamSection(RamSection);
  } /* else No action required */
  /* Return the value of RAM initialization result */
  return (LucReturnValue);
}
#define MCU_STOP_SEC_PUBLIC_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name      : Mcu_InitClock
**
** Service ID         : 0x02
**
** Description        : This service initializes the PLL and other MCU specific clock options.
**
** Sync/Async         : Synchronous
**
** Reentrancy         : Non-Reentrant
**
** Input Parameters   : ClockSetting - Id for Clock setting
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : Std_ReturnType (E_OK, E_NOT_OK)
**
** Preconditions      : MCU Driver component must be initialized
**
** Global Variables   : Mcu_GblDriverStatus
**
** Function Invoked   : Det_ReportError, Mcu_CLKInitClock, MCU_DEM_REPORT_ERROR
**
** Registers Used     : None
**
** Reference ID       : MCU_DUD_ACT_003, MCU_DUD_ACT_003_ERR001, MCU_DUD_ACT_003_ERR002, MCU_DUD_ACT_003_ERR003
** Reference ID       : MCU_DUD_ACT_003_ERR004, MCU_DUD_ACT_003_GBL001
***********************************************************************************************************************/
#if (MCU_INIT_CLOCK == STD_ON)
#define MCU_START_SEC_PUBLIC_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, MCU_PUBLIC_CODE) Mcu_InitClock(Mcu_ClockType ClockSetting)                                         /* PRQA S 1503 # JV-01 */
{
  Std_ReturnType LucReturnValue;

  #if (MCU_DEV_ERROR_DETECT == STD_ON)
  /* Report to DET, if the component is not initialized */
  if (MCU_UNINITIALIZED == Mcu_GblDriverStatus)                                                                         /* PRQA S 3416 # JV-01 */
  {
    /* Report to DET */
    (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_INITCLOCK_SID, MCU_E_UNINIT);
    LucReturnValue = E_NOT_OK;
  }
  else if (ClockSetting >= Mcu_GpConfigPtr->ucNofClockSettings)                                                         /* PRQA S 3416 # JV-01 */
  {
    /* Report to DET */
    (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_INITCLOCK_SID, MCU_E_PARAM_CLOCK);
    LucReturnValue = E_NOT_OK;
  }
  else
  #endif /* MCU_DEV_ERROR_DETECT == STD_ON */
  {
    Mcu_GpClockSetting =
      (P2CONST(Mcu_ClockSettingType, AUTOMATIC, MCU_CONFIG_DATA))Mcu_GpConfigPtr->pClockSetting + ClockSetting;         /* PRQA S 0316, 0488 # JV-01, JV-01 */
    /* Initialize clock source generator */
    LucReturnValue = Mcu_CLKInitClock();

    #ifdef MCU_E_CLOCK_FAILURE
    if (E_NOT_OK == LucReturnValue)
    {
      /* Report to Dem if clock source initalization is failed. */
      MCU_DEM_REPORT_ERROR(MCU_E_CLOCK_FAILURE, DEM_EVENT_STATUS_FAILED);
    }
    else
    {
      MCU_DEM_REPORT_ERROR(MCU_E_CLOCK_FAILURE, DEM_EVENT_STATUS_PASSED);
    }
    #endif /* MCU_E_CLOCK_FAILURE */
  }

  /* Return the value of clock initialization result */
  return (LucReturnValue);
}
#define MCU_STOP_SEC_PUBLIC_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* MCU_INIT_CLOCK == STD_ON */

/***********************************************************************************************************************
** Function Name      : Mcu_DistributePllClock
**
** Service ID         : 0x03
**
** Description        : This function activates the PLL clock to the MCU clock distribution
**
** Sync/Async         : Synchronous
**
** Reentrancy         : Non-Reentrant
**
** Input Parameters   : None
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : Std_ReturnType
**
** Preconditions      : MCU Driver component must be initialized
**
** Global Variables   : Mcu_GblDriverStatus
**
** Function Invoked   : Det_ReportError, Mcu_CLKDistributeClocks, Mcu_CLKGetPllStatus
**
** Registers Used     : None
**
** Reference ID       : MCU_DUD_ACT_045, MCU_DUD_ACT_045_ERR001, MCU_DUD_ACT_045_ERR002
***********************************************************************************************************************/
#if (MCU_NO_PLL == STD_OFF)
#define MCU_START_SEC_PUBLIC_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, MCU_PUBLIC_CODE) Mcu_DistributePllClock(void)                                                      /* PRQA S 1503 # JV-01 */
{
  Std_ReturnType LucReturnValue;

  Mcu_PllStatusType LddPllLockStatus;
  LucReturnValue = E_OK;                                                                                                /* PRQA S 2982 # JV-01 */
  LddPllLockStatus = MCU_PLL_LOCKED;                                                                                    /* PRQA S 2982 # JV-01 */
  #if (MCU_DEV_ERROR_DETECT == STD_ON)
  /* Report to DET, if module is not initialized */
  if (MCU_UNINITIALIZED == Mcu_GblDriverStatus)                                                                         /* PRQA S 3416 # JV-01 */
  {
    /* Report to DET */
    (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_DISTRIBUTEPLLCLOCK_SID, MCU_E_UNINIT);
    LucReturnValue = E_NOT_OK;
  }
  else
  #endif /* MCU_DEV_ERROR_DETECT == STD_ON */
  {
    /* Get PLL status */
    LddPllLockStatus = Mcu_CLKGetPllStatus();
    /* Report to DET, if PLL has been detected as non-locked */
    if (MCU_PLL_UNLOCKED == LddPllLockStatus)
    {
      #if (MCU_DEV_ERROR_DETECT == STD_ON)
      /* Report to DET */
      (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_DISTRIBUTEPLLCLOCK_SID, MCU_E_PLL_NOT_LOCKED);
      #endif /* MCU_DEV_ERROR_DETECT == STD_ON */
      LucReturnValue = E_NOT_OK;
    }
    else
    {
      LucReturnValue = Mcu_CLKDistributeClocks();
    }
  }
  /* Return the value of activates PLL clock result */
  return (LucReturnValue);
}
#define MCU_STOP_SEC_PUBLIC_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* MCU_NO_PLL == STD_OFF */

/***********************************************************************************************************************
** Function Name      : Mcu_GetPllStatus
**
** Service ID         : 0x04
**
** Description        : This service provides the lock status of the PLL.
**
** Sync/Async         : Synchronous
**
** Reentrancy         : Reentrant
**
** Input Parameters   : None
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : Mcu_PllStatusType
**
** Preconditions      : MCU Driver component must be initialized
**
** Global Variables   : Mcu_GblDriverStatus
**
** Function Invoked   : Det_ReportError, Mcu_CLKGetPllStatus
**
** Registers Used     : None
**
** Reference ID       : MCU_DUD_ACT_004, MCU_DUD_ACT_004_ERR001
***********************************************************************************************************************/
#define MCU_START_SEC_PUBLIC_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(Mcu_PllStatusType, MCU_PUBLIC_CODE) Mcu_GetPllStatus(void)                                                         /* PRQA S 1503 # JV-01 */
{
  Mcu_PllStatusType LddPllLockStatus;

  #if (MCU_INIT_CLOCK == STD_ON)
  LddPllLockStatus = MCU_PLL_LOCKED;                                                                                    /* PRQA S 2982 # JV-01 */
  #endif /* MCU_INIT_CLOCK == STD_ON */

  #if (MCU_DEV_ERROR_DETECT == STD_ON)
  /* Report to DET, if module is not initialized */
  if (MCU_UNINITIALIZED == Mcu_GblDriverStatus)                                                                         /* PRQA S 3416 # JV-01 */
  {
    /* Report to DET */
    (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_GETPLLSTATUS_SID, MCU_E_UNINIT);
    /* Set PLL status to undefined */
    LddPllLockStatus = MCU_PLL_STATUS_UNDEFINED;
  }
  else
  #endif /* MCU_DEV_ERROR_DETECT == STD_ON */
  {
    LddPllLockStatus = Mcu_CLKGetPllStatus();
  }

  return (LddPllLockStatus);
}
#define MCU_STOP_SEC_PUBLIC_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name      : Mcu_GetResetReason
**
** Service ID         : 0x05
**
** Description        : The function reads the reset type from the hardware.
**
** Sync/Async         : Synchronous
**
** Reentrancy         : Reentrant
**
** Input Parameters   : None
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : Mcu_ResetType
**
** Preconditions      : MCU Driver component must be initialized
**
** Global Variables   : Mcu_GblDriverStatus
**
** Function Invoked   : Det_ReportError, Mcu_RSTGetResetReason
**
** Registers Used     : None
**
** Reference ID       : MCU_DUD_ACT_005, MCU_DUD_ACT_005_ERR001
***********************************************************************************************************************/
#define MCU_START_SEC_PUBLIC_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(Mcu_ResetType, MCU_PUBLIC_CODE) Mcu_GetResetReason(void)                                                           /* PRQA S 1503 # JV-01 */
{
  Mcu_ResetType LddResetSource;

  LddResetSource = MCU_NON_RST;                                                                                         /* PRQA S 2982 # JV-01 */

  #if (MCU_DEV_ERROR_DETECT == STD_ON)
  /* Report to DET, if module is not initialized */
  if (MCU_UNINITIALIZED == Mcu_GblDriverStatus)                                                                         /* PRQA S 3416 # JV-01 */
  {
    /* Report to DET */
    (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_GETRESETREASON_SID, MCU_E_UNINIT);
    /* Set Reset status to undefined */
    LddResetSource = MCU_RESET_UNDEFINED;
  }
  else
  #endif /* MCU_DEV_ERROR_DETECT == STD_ON */
  {
    LddResetSource = Mcu_RSTGetResetReason();
  }
  return (LddResetSource);
}
#define MCU_STOP_SEC_PUBLIC_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name      : Mcu_GetResetRawValue
**
** Service ID         : 0x06
**
** Description        : The service return reset type value from the hardware register
**
** Sync/Async         : Synchronous
**
** Reentrancy         : Reentrant
**
** Input Parameters   : None
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : Mcu_RawResetType
**
** Preconditions      : MCU Driver component must be initialized
**
** Global Variables   : Mcu_GblDriverStatus
**
** Function Invoked   : Det_ReportError, Mcu_RSTGetResetRawValue
**
** Registers Used     : None
**
** Reference ID       : MCU_DUD_ACT_006, MCU_DUD_ACT_006_ERR001
***********************************************************************************************************************/
#define MCU_START_SEC_PUBLIC_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(Mcu_RawResetType, MCU_PUBLIC_CODE) Mcu_GetResetRawValue(void)                                                      /* PRQA S 1503 # JV-01 */
{
  Mcu_RawResetType LddResetValue;

  /* Initialize the local variable */
  LddResetValue = MCU_LONG_WORD_ZERO;                                                                                   /* PRQA S 2982 # JV-01 */

  #if (MCU_DEV_ERROR_DETECT == STD_ON)
  /* Report to DET, if module is not initialized */
  if (MCU_UNINITIALIZED == Mcu_GblDriverStatus)                                                                         /* PRQA S 3416 # JV-01 */
  {
    /* Report to DET */
    (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_GETRESETRAWVAULE_SID, MCU_E_UNINIT);
    /* Set RESET status to uninitialized */
    LddResetValue = MCU_RESET_UNINIT;
  }
  else
  #endif /* MCU_DEV_ERROR_DETECT == STD_ON */
  {
    LddResetValue = Mcu_RSTGetResetRawValue();
  }
  return (LddResetValue);
}
#define MCU_STOP_SEC_PUBLIC_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name      : Mcu_PerformReset
**
** Service ID         : 0x07
**
** Description        : This service provides microcontroller reset by accessing the Software reset register.
**
** Sync/Async         : Synchronous
**
** Reentrancy         : Non-Reentrant
**
** Input Parameters   : None
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : None
**
** Preconditions      : MCU Driver component must be initialized
**
** Global Variables   : Mcu_GblDriverStatus
**
** Function Invoked   : Det_ReportError, MCU_RESET_CALLOUT, Mcu_RSTPerformReset
**
** Registers Used     : None
**
** Reference ID       : MCU_DUD_ACT_007, MCU_DUD_ACT_007_ERR001
***********************************************************************************************************************/
#if (MCU_PERFORM_RESET_API == STD_ON)
#define MCU_START_SEC_PUBLIC_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(void, MCU_PUBLIC_CODE) Mcu_PerformReset(void)                                                                      /* PRQA S 1503 # JV-01 */
{
  #if (MCU_DEV_ERROR_DETECT == STD_ON)
  /* Report to DET, if module is not initialized */
  if (MCU_UNINITIALIZED == Mcu_GblDriverStatus)                                                                         /* PRQA S 3416 # JV-01 */
  {
    /* Report to DET */
    (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_PERFORMRESET_SID, MCU_E_UNINIT);
  }
  else
  #endif /* MCU_DEV_ERROR_DETECT == STD_ON */
  {
    #if (MCU_SW_RESET_CALL_API == STD_ON)
    MCU_RESET_CALLOUT();
    #else
    Mcu_RSTPerformReset();
    #endif /* MCU_SW_RESET_CALL_API == STD_ON */
  }
}
#define MCU_STOP_SEC_PUBLIC_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* MCU_PERFORMRESET_API == STD_ON */

/***********************************************************************************************************************
** Function Name      : Mcu_GetVersionInfo
**
** Service ID         : 0x09
**
** Description        : This service returns the version information of this module.
**
** Sync/Async         : Synchronous
**
** Reentrancy         : Reentrant
**
** Input Parameters   : None
**
** InOut Parameters   : None
**
** Output Parameters  : versioninfo
**
** Return parameter   : None
**
** Preconditions      : None
**
** Global Variables   : None
**
** Functions Invoked  : Det_ReportError
**
** Registers Used     : None
**
** Reference ID       : MCU_DUD_ACT_034, MCU_DUD_ACT_034_ERR001
***********************************************************************************************************************/
#if (MCU_VERSION_INFO_API == STD_ON)
#define MCU_START_SEC_PUBLIC_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(void, MCU_PUBLIC_CODE) Mcu_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, MCU_APPL_DATA) versioninfo)        /* PRQA S 1503, 3432 # JV-01, JV-01 */
{
  #if (MCU_DEV_ERROR_DETECT == STD_ON)
  /* Check if parameter passed is equal to Null pointer */
  if (NULL_PTR == versioninfo)
  {
    (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_GETVERSIONINFO_SID, MCU_E_PARAM_POINTER);
  }
  else
  #endif /* MCU_DEV_ERROR_DETECT == STD_ON */
  {
    versioninfo->vendorID = MCU_VENDOR_ID;
    versioninfo->moduleID = MCU_MODULE_ID;
    versioninfo->sw_major_version = MCU_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version = MCU_SW_MINOR_VERSION;
    versioninfo->sw_patch_version = MCU_SW_PATCH_VERSION;
  }
  return;
}
#define MCU_STOP_SEC_PUBLIC_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* MCU_VERSION_INFO_API == STD_ON */

/***********************************************************************************************************************
** Function Name      : Mcu_GetRamState
**
** Service ID         : 0x0A
**
** Description        : This service provides the actual status of the microcontroller RAM area.
**
** Sync/Async         : Synchronous
**
** Reentrancy         : Reentrant
**
** Input Parameters   : None
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : Mcu_RamStateType (MCU_RAMSTATE_INVALID, MCU_RAMSTATE_VALID)
**
** Preconditions      : MCU Driver component must be initialized
**
** Global Variables   : Mcu_GblDriverStatus, Mcu_GblRAMInitStatus
**
** Functions Invoked  : Det_ReportError, Mcu_ECCGetRamState
**
** Registers Used     : None
**
** Reference ID       : MCU_DUD_ACT_008, MCU_DUD_ACT_008_CRT001, MCU_DUD_ACT_008_CRT002, MCU_DUD_ACT_008_ERR001
** Reference ID       : MCU_DUD_ACT_008_GBL001
***********************************************************************************************************************/
#if (MCU_GET_RAM_STATE_API == STD_ON)
#define MCU_START_SEC_PUBLIC_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(Mcu_RamStateType, MCU_PUBLIC_CODE) Mcu_GetRamState(void)                                                           /* PRQA S 1503 # JV-01 */
{
  Mcu_RamStateType LddRamStatus;

  #if (MCU_DEV_ERROR_DETECT == STD_ON)
  LddRamStatus = MCU_RAMSTATE_INVALID;
  /* Report to DET, if the component is not initialized */
  if (MCU_UNINITIALIZED == Mcu_GblDriverStatus)                                                                         /* PRQA S 3416 # JV-01 */
  {
    /* Report to DET */
    (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_GETRAMSTATE_SID, MCU_E_UNINIT);
  }
  /* If no development error occurred */
  else
  #endif /* MCU_DEV_ERROR_DETECT == STD_ON */
  {
    #if (MCU_PROVIDE_RAM_STATE_ISR == STD_ON)
    MCU_ENTER_CRITICAL_SECTION(MCU_RAM_DATA_PROTECTION);
    LddRamStatus = Mcu_GblRAMInitStatus;
    Mcu_GblRAMInitStatus = MCU_RAMSTATE_VALID;
    MCU_EXIT_CRITICAL_SECTION(MCU_RAM_DATA_PROTECTION);
    #else
    LddRamStatus = Mcu_ECCGetRamState();
    #endif /* MCU_PROVIDE_RAM_STATE_ISR == STD_ON */
  }

  /* Return the value of RAM status result */
  return (LddRamStatus);
}
#define MCU_STOP_SEC_PUBLIC_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* MCU_GET_RAM_STATE_API == STD_ON */

/***********************************************************************************************************************
** Function Name      : Mcu_SetMode
**
** Service ID         : 0x08
**
** Description        : This service activates the MCU power modes.
**
** Sync/Async         : Synchronous
**
** Reentrancy         : Reentrant
**
** Input Parameters   : LddMcuMode - Id for power mode setting
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : None
**
** Preconditions      : MCU Driver component must be initialized
**
** Global Variables   : Mcu_GblDriverStatus
**
** Function Invoked   : Det_ReportError, Mcu_STBSetMode
**
** Registers Used     : None
**
** Reference ID       : MCU_DUD_ACT_043, MCU_DUD_ACT_043_ERR001, MCU_DUD_ACT_043_ERR002
***********************************************************************************************************************/
#define MCU_START_SEC_PUBLIC_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(void, MCU_PUBLIC_CODE) Mcu_SetMode(Mcu_ModeType LddMcuMode)                                                        /* PRQA S 1503 # JV-01 */
{
  #if (MCU_DEV_ERROR_DETECT == STD_ON)
  Std_ReturnType LucReturnValue;
  LucReturnValue = E_OK;
  /* Report to DET, if the component is not initialized */
  if (MCU_UNINITIALIZED == Mcu_GblDriverStatus)                                                                         /* PRQA S 3416 # JV-01 */
  {
    /* Report to DET */
    (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_SETMODE_SID, MCU_E_UNINIT);
    LucReturnValue = E_NOT_OK;
  } /* else No action required */

  if (E_OK == LucReturnValue)
  {
    /* Report to DET, if Mode Setting Id is out of range */
    if ((MCU_CONFIGURED_MODE_SETTING_NUM - MCU_ONE) < LddMcuMode)
    {
      /* Report to DET */
      (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_SETMODE_SID, MCU_E_PARAM_MODE);
      LucReturnValue = E_NOT_OK;
    } /* else No action required */
  } /* else No action required */
  /* Check if any development error occurred */
  if (E_OK == LucReturnValue)
  #endif /* MCU_DEV_ERROR_DETECT == STD_ON */
  {
    Mcu_STBSetMode(LddMcuMode);
  } /* else No action required */
  return;
}
#define MCU_STOP_SEC_PUBLIC_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name      : Mcu_ClearAndSetWakeUpFactor
**
** Service ID         : 0x0B
**
** Description        : This service clear and set WakeUp factor for trasition to Power-Down mode
**
** Sync/Async         : Synchronous
**
** Reentrancy         : Non-Reentrant
**
** Input Parameters   : LddMcuMode
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : Std_ReturnType
**
** Preconditions      : MCU Driver component must be initialized
**
** Global Variables   : Mcu_GblDriverStatus
**
** Function Invoked   : Det_ReportError, Mcu_STBClearWakeUpFactor, Mcu_STBSetWakeUpFactor
**
** Registers Used     : None
**
** Reference ID       : MCU_DUD_ACT_046, MCU_DUD_ACT_046_ERR001, MCU_DUD_ACT_046_ERR002
***********************************************************************************************************************/
#if (MCU_CLEARANDSETWAKEUPFACTOR_API == STD_ON)
#define MCU_START_SEC_PUBLIC_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, MCU_PUBLIC_CODE) Mcu_ClearAndSetWakeUpFactor(Mcu_ModeType LddMcuMode)                              /* PRQA S 1503 # JV-01 */
{
  Std_ReturnType LucReturnValue;

  #if (MCU_DEV_ERROR_DETECT == STD_ON)
  LucReturnValue = E_OK;

  /* Report to DET, if module is not initialized */
  if (MCU_UNINITIALIZED == Mcu_GblDriverStatus)                                                                         /* PRQA S 3416 # JV-01 */
  {
    /* Report to DET */
    (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_CLEARANDSETWAKEUPFACTOR_SID, MCU_E_UNINIT);
    LucReturnValue = E_NOT_OK;
  } /* else No action required */

  if (E_OK == LucReturnValue)
  {
    /* Report to DET, if Mode Setting Id is out of range */
    if ((MCU_CONFIGURED_MODE_SETTING_NUM - MCU_ONE) < LddMcuMode)
    {
      /* Report to DET */
      (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_CLEARANDSETWAKEUPFACTOR_SID, MCU_E_PARAM_MODE);
      LucReturnValue = E_NOT_OK;
    } /* else No action required */
  } /* else No action required */

  /* Check if any development error occurred */
  if (E_OK == LucReturnValue)
  #endif /* MCU_DEV_ERROR_DETECT == STD_ON */
  {
    /* Clear Wakeup factor flag */
    Mcu_STBClearWakeUpFactor();
    /* Set Wakeup factor before trasition to specific mode */
    LucReturnValue = Mcu_STBSetWakeUpFactor(LddMcuMode);
  } /* else No action required */
  return (LucReturnValue);
}
#define MCU_STOP_SEC_PUBLIC_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* MCU_CLEARANDSETWAKEUPFACTOR_API == STD_ON */

/***********************************************************************************************************************
** Function Name      : Mcu_GetWakeUpFactor
**
** Service ID         : 0x0C
**
** Description        : This service support to get Wake-Up factors via Wake-Up Factor Registers
**
** Sync/Async         : Synchronous
**
** Reentrancy         : Non-Reentrant
**
** Input Parameters   : LpMcuWakeupfactorinfoPtr
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : Std_ReturnType
**
** Preconditions      : MCU Driver component must be initialized
**
** Global Variables   : Mcu_GblDriverStatus
**
** Function Invoked   : Det_ReportError, Mcu_STBGetWakeUpFactor
**
** Registers Used     : None
**
** Reference ID       : MCU_DUD_ACT_047, MCU_DUD_ACT_047_ERR001, MCU_DUD_ACT_047_ERR002
***********************************************************************************************************************/
#if (MCU_GETWAKEUPFACTOR_API == STD_ON)
#define MCU_START_SEC_PUBLIC_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, MCU_PUBLIC_CODE)
Mcu_GetWakeUpFactor(P2VAR(Mcu_WakeUpFactorInfoType, AUTOMATIC, MCU_APPL_DATA) LpMcuWakeupfactorinfoPtr)                 /* PRQA S 1503, 3432 # JV-01, JV-01 */
{
  Std_ReturnType LucReturnValue;
  LucReturnValue = E_OK;

  #if (MCU_DEV_ERROR_DETECT == STD_ON)
  /* Report to DET, if module is not initialized */
  if (MCU_UNINITIALIZED == Mcu_GblDriverStatus)                                                                         /* PRQA S 3416 # JV-01 */
  {
    /* Report to DET */
    (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_GETWAKEUPFACTOR_SID, MCU_E_UNINIT);
    LucReturnValue = E_NOT_OK;
  } /* else No action required */

  if (E_OK == LucReturnValue)
  {
    /* Report to DET, if configuration pointer is NULL pointer */
    if (NULL_PTR == LpMcuWakeupfactorinfoPtr)
    {
      /* Report to DET */
      (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_GETWAKEUPFACTOR_SID, MCU_E_PARAM_POINTER);
      LucReturnValue = E_NOT_OK;
    } /* else No action required */
  } /* else No action required */
  if (E_OK == LucReturnValue)
  #endif /* MCU_DEV_ERROR_DETECT == STD_ON */
  {
    Mcu_STBGetWakeUpFactor(LpMcuWakeupfactorinfoPtr);
  } /* else No action required */
  return (LucReturnValue);
}
#define MCU_STOP_SEC_PUBLIC_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* MCU_GETWAKEUPFACTOR_API == STD_ON */

/***********************************************************************************************************************
** Function Name      : Mcu_ReleaseIoBufferHold
**
** Service ID         : 0x0D
**
** Description        : This service support to release the I/O hold state after the wake-up
**
** Sync/Async         : Synchronous
**
** Reentrancy         : Non-Reentrant
**
** Input Parameters   : None
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : Std_ReturnType
**
** Preconditions      : MCU Driver component must be initialized
**
** Global Variables   : Mcu_GblDriverStatus
**
** Function Invoked   : Det_ReportError, Mcu_STBReleaseIoBufferHold
**
** Registers Used     : None
**
** Reference ID       : MCU_DUD_ACT_048, MCU_DUD_ACT_048_ERR001
***********************************************************************************************************************/
#if (MCU_RELEASEIOBUFFERHOLD_API == STD_ON)
#define MCU_START_SEC_PUBLIC_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, MCU_PUBLIC_CODE) Mcu_ReleaseIoBufferHold(void)                                                     /* PRQA S 1503 # JV-01 */
{
  Std_ReturnType LucReturnValue;

  LucReturnValue = E_OK;

  #if (MCU_DEV_ERROR_DETECT == STD_ON)
  /* Report to DET, if module is not initialized */
  if (MCU_UNINITIALIZED == Mcu_GblDriverStatus)                                                                         /* PRQA S 3416 # JV-01 */
  {
    /* Report to DET */
    (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_RELEASEIOBUFFERHOLD_SID, MCU_E_UNINIT);
    LucReturnValue = E_NOT_OK;
  }
  else
  #endif /* MCU_DEV_ERROR_DETECT == STD_ON */
  {
    Mcu_STBReleaseIoBufferHold();
  }
  /* Return the value of release the I/O hold state result */
  return (LucReturnValue);
}
#define MCU_STOP_SEC_PUBLIC_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* MCU_RELEASEIOBUFFERHOLD_API == STD_ON */

/***********************************************************************************************************************
** Function Name      : Mcu_SetStatus
**
** Service ID         : None
**
** Description        : This function is change Mcu_GblDriverStatus
**
** Sync/Async         : Synchronous
**
** Reentrancy         : Non-Reentrant
**
** Input Parameters   : LblStatus
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : None
**
** Preconditions      : None
**
** Global Variables   : Mcu_GblDriverStatus
**
** Functions Invoked  : None
**
** Registers Used     : None
**
** Reference ID       : MCU_DUD_ACT_044, MCU_DUD_ACT_044_GBL001
***********************************************************************************************************************/
#define MCU_START_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
STATIC FUNC(void, MCU_PRIVATE_CODE) Mcu_SetStatus(const boolean LblStatus)
{
  Mcu_GblDriverStatus = LblStatus;
  return;
}
#define MCU_STOP_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
