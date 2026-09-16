/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Lin.c                                                                                               */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2019-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* API function implementations of LIN Driver Component.                                                              */
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
 *
 * 2.4.0:  30/06/2025  : Remove the SW-VERSION from header of file
 * 2.3.2:  25/04/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 Release
 * 2.3.1:  31/03/2025  : Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02 Release
 *                       Add new QAC message 3006, remove redundant message 1532, 2844, 2814, 2824
 * 2.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00(D) U2Bx Final Release
 * 2.1.2:  31/10/2024  : Update SW-VERSION to 2.1.2
 *         24/07/2024  : As part of QAC 9.5.0 support, following changes are made:
                         1. Add message 2844, 2814, 2824
 * 2.0.1:  10/01/2024  : Update to correct for header description
 *         21/10/2023  : Update to improve for critical section, Lin_ErrorReport in Lin_WakeupInternal
 *         20/10/2023  : Remove meassage 2844, 2814, 2824
 *         11/10/2023  : Update AR version "LIN_AR_R21_11_VERSION" to "LIN_AR_R22_11_VERSION"
 *                       Update "LIN_INTERRUPT_CONTROL_PROTECTION_GLOBAL" to "LIN_INTERRUPT_CONTROL_PROTECTION"
 *                       Modify pointer casting type to fix QA-C messages
 *         14/09/2023  : In Lin_SendFrame, update to fix for LucChannelRamIndex not initialized for AR422
 *                       In Lin_GoToSleep, Lin_GetStatus, update to move LOC of initialization of LucChannelRamIndex
 * 2.0.0:  23/08/2023  : Update critical section in API Lin_WakeupInternal
 *         26/07/2023  : Add information about CWE violation ID
 *         24/07/2023  : RemoveQAC messages (3:3416) and add update justification for QAC (2:2824)
 *                       Update to support for Multicore:
 *                       Add new include "Os.h" to support for multicore.
 *                       Update API Lin_Init, Lin_CheckWakeup, Lin_SendFrame, Lin_GoToSleep, Lin_GoToSleepInternal,
 *                       Lin_WakeUp, Lin_WakeupInternal, Lin_GetStatus to support for Multicore.
 *                       Update API "Lin_WakeupInternal" to correct for critical section call
 *         03/07/2023  : Update Reference ID for Lin_CheckWakeup and Lin_WakeupInternal
 *         30/06/2023  : Remove preparation of slave reception and disabling interrupt for master in Lin_CheckWakeup
 *                       Add disabling interrupt for master node in Lin_WakeupInternal
 *         20/06/2023  : Add Lin_HwScheduleInterrupt in Function invoked of Lin_SendFrame
 *         25/05/2023  : Change name of AR version LIN_AR_2111_VERSION to LIN_AR_R21_11_VERSION
 *         22/05/2023  : Remove redundant QAC message and QAC messages (3:3206), (2:3673)
 *         10/05/2023  : Remove QAC message (2:3205)
 *         28/04/2023  : Remove LpRamVars->blWakeupCalled = LIN_TRUE (LIN_DUD_ACT_008_GBL003) 
 *                       in function Lin_WakeupInternal
 *         20/04/2023  : Add Lin_HwSlaveStartHeaderReception to Functions invoked in header of 
 *                       Lin_CheckWakeup, Lin_WakeupInternal
 *                       Add Lin_GpChannelConfig to Global Variables in header of 
 *                       Lin_GoToSleep, Lin_SendFrame, Lin_WakeupInternal, Lin_GetStatus
 *                       Update Pre-compile for parameter LpLinChannelPtr in function Lin_CheckWakeup
 * 1.5.0:  10/04/2023  : Add QAC message 9.5.0 and QAC message (2:3205).
 *         07/04/2023  : Update function Lin_CheckWakeup, Lin_SendFrame, Lin_GoToSleep, Lin_WakeUp, 
 *                       Lin_WakeupInternal and Lin_GetStatus and add EcuM.h, Linif.h for support AR21-11
 * 1.4.4:  13/06/2022  : Add QAC message 9.5.0.
 *                       Function Lin_WakeUp: Clear wake-up flag after a wake-up command to the LIN bus failed.
 * 1.4.3:  09/06/2022  : Remove "else" statement don't use when no action required.
 *         23/05/2022  : Add QAC Message (3:2004) and PRQA comment PRQA S 2004 # JV-01
 *         14/04/2022  : Update SW-VERSION to 1.4.3
 * 1.4.1:  04/03/2022  : Update SW-VERSION to 1.4.2
 * 1.4.0:  18/11/2021  : Update Critical section nesting for Lin_WakeupInternal and Lin_CheckWakeup
 * 1.3.1:  02/07/2021  : Add QAC message 9.5.0.
 *                       Format source code to 120 characters.
 *                       Improve Violation tag (remove START/END).
 *         27/04/2021  : Fix coding rule for function Lin_WakeUp, update record
 *                       history and copy right.
 * 1.2.0:  26/08/2020  : Release.
 * 1.1.0:  19/06/2020  : Release.
 * 1.0.2:  22/05/2020  : Update software version definition.
 * 1.0.1:  25/03/2020  : Update Format dd/mm/yyyy and revision format.
 *         20/03/2019  : Fix QAC
 *                         1. Update "MISRA C Rule Violations" and "QAC warning"
 *                            message from MISRA-C:2004 to MISRA-C:2012.
 *         19/03/2019  : Fix QAC
 *                         1. Update "MISRA C Rule Violations" and "QAC warning"
 *                            message from MISRA-C:2004 to MISRA-C:2012.
 *                         2. Move static function prototypes from header file to
 *                            source file.
 * 1.0.0:  12/03/2019  : Initial Version.
 *
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Lin APIs header file */
#include "Lin.h"
/* Global RAM variables header file */
#include "Lin_Ram.h"
#if (LIN_DEV_ERROR_DETECT == STD_ON)
/* Development Error header */
#include "Det.h"
#endif
/* Included for declaration of the function Dem_SetEventStatus() (for AR4.3.1) */
/* and Dem_ReportErrorStatus() (for AR4.2.2) */
#include "Dem.h"
/* Schedule Manager header */
#if (LIN_CRITICAL_SECTION_PROTECTION == STD_ON)
#include "SchM_Lin.h"
#endif
#if (LIN_WAKEUP_SUPPORT == STD_ON)
#if (LIN_AR_VERSION == LIN_AR_R22_11_VERSION)
/* Included for the declaration of EcuM_SetWakeupEvent() */
#include "EcuM.h"
#include "LinIf.h"
#else
/* Included for the declaration of EcuM_SetWakeupEvent() */
#include "EcuM_Cbk.h"
#include "LinIf_Cbk.h"
#endif
#endif

/**
 * include os
*/
#if (LIN_MULTI_CORE_SUPPORT == STD_ON)
#include "Os.h"
#endif /* #if (LIN_MULTI_CORE_SUPPORT == STD_ON) */
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define LIN_C_AR_RELEASE_MAJOR_VERSION    LIN_AR_RELEASE_MAJOR_VERSION_VALUE
#define LIN_C_AR_RELEASE_MINOR_VERSION    LIN_AR_RELEASE_MINOR_VERSION_VALUE
#define LIN_C_AR_RELEASE_REVISION_VERSION LIN_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define LIN_C_SW_MAJOR_VERSION            LIN_SW_MAJOR_VERSION_VALUE
#define LIN_C_SW_MINOR_VERSION            LIN_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (LIN_AR_RELEASE_MAJOR_VERSION != LIN_C_AR_RELEASE_MAJOR_VERSION)
#error "Lin.c : Mismatch in Release Major Version"
#endif

#if (LIN_AR_RELEASE_MINOR_VERSION != LIN_C_AR_RELEASE_MINOR_VERSION)
#error "Lin.c : Mismatch in Release Minor Version"
#endif

#if (LIN_AR_RELEASE_REVISION_VERSION != LIN_C_AR_RELEASE_REVISION_VERSION)
#error "Lin.c : Mismatch in Release Revision Version"
#endif

#if (LIN_SW_MAJOR_VERSION != LIN_C_SW_MAJOR_VERSION)
#error "Lin.c : Mismatch in Software Major Version"
#endif

#if (LIN_SW_MINOR_VERSION != LIN_C_SW_MINOR_VERSION)
#error "Lin.c : Mismatch in Software Minor Version"
#endif

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:3218)    : File scope static, '%s', is only accessed in one function.                                   */
/* Rule                : CERTCCM DCL19, MISRA C:2012 Rule-8.9, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : By moving the array into the function, the stack size used will be more, hence this is       */
/*                       defined outside.                                                                             */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:5087)    : Use of #include directive after code fragment.                                               */
/* Rule                : MISRA C:2012 Rule-20.1                                                                       */
/* JV-01 Justification : This is done as per Memory Requirement, (MEMMAP003 - Specification of Memory Mapping).       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1503)    : The function '%1s' is defined but is not used within this project.                           */
/* Rule                : CERTCCM MSC07, MISRA C:2012 Rule-2.1, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : This is accepted, due to the module's API is exported for user's usage.                      */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE Rule CWE-398, CWE-569                                            */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is accepted. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0316)    : Cast from a pointer to void to a pointer to object type.                                     */
/* Rule                : MISRA C:2012 Rule-11.5, CWE Rule CWE-188, CWE-398, CWE-569                                   */
/* JV-01 Justification : A cast should not be performed between a pointer to object type and a different pointer to   */
/*                       object type.                                                                                 */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:2814)    : Possible: Dereference of NULL pointer.                                                       */
/* Rule                : CERTCCM EXP34, CWE Rule CWE-476, CWE-465, CWE-737, CWE-690                                   */
/* JV-01 Justification : This is accepted, due to the implementation is following hardware specification.             */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/* JV-02 Justification : This is accepted, The pointer has been NULL checked by DET.                                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/* JV-03 Justification : This is accepted, the pointer can not be NULL and ensured by gentool.                        */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:2982)    : This assignment is redundant. The value of this object is never used before being modified.  */
/* Rule                : CERTCCM MSC07, MSC13, MISRA C:2012 Rule-2.2, CWE Rule CWE-14, CWE-398, CWE-561, CWE-563      */
/*                       CWE-569, CWE-633                                                                             */
/* JV-01 Justification : The variable needs to be initialized before using it.                                        */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (7:0404)    : More than one read access to volatile objects between sequence points.                       */
/* Rule                : CERTCCM EXP10, EXP30, MISRA C:2012 Rule-1.3, Rule-13.2, CWE Rule CWE-682, CWE-758, CWE-737   */
/* JV-01 Justification : This is to get element in array of struct, volatile of counter variable of 'for' loop is     */
/*                       used to ensure no optimization. It is accepted.                                              */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:3383)    : Cannot identify wraparound guard for unsigned arithmetic expression.                         */
/* Rule                : CERTCCM INT30                                                                                */
/* JV-01 Justification : It can still result in values that are out of range for the intended use, as intuitive       */
/*                       "invariants" may not hold.                                                                   */
/*       Verification  : However, LIN_NO_OF_CHANNELS is the upper constrained of LucNoOfLinChannels, prevent          */
/*                       LucNoOfLinChannels to be out of range.                                                       */
/* JV-02 Justification : It can still result in values that are out of range for the intended use, as intuitive       */
/*                       "invariants" may not hold.                                                                   */
/*       Verification  : However, LIN_ZERO is the lower constrained of LucCount, prevent LucCount to be out of range. */
/**********************************************************************************************************************/
/* Message (6:2995)    : The result of this logical operation is always 'true'.                                       */
/* Rule                : MISRA C:2012 Rule-2.2, CWE Rule CWE-561, CWE-633                                             */
/* JV-01 Justification : Depending on device configuration, there is case where the 'if' will return 'false'.         */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (6:2991)    : The value of this 'if' controlling expression is always 'true'.                              */
/* Rule                : MISRA C:2012 Rule-14.3                                                                       */
/* JV-01 Justification : Depending on device configuration, there is case where the 'if' will return 'false'.         */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3678)    : The object referenced by '%1s' is not modified through it, so '%1s' could be declared with   */
/*                       type '%2s'.                                                                                  */
/* Rule                : MISRA C:2012 Rule-8.13                                                                       */
/* JV-01 Justification : This is accepted. It just an advise for improve safety by reducing the possibility that      */
/*                       the referenced data is unintentionally modified through an unexpected alias and improves     */
/*                       clarity by indicating that the referenced data is not intended to be modified through this   */
/*                       alias or those depending on it.                                                              */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3387)    : A full expression containing an increment (++) or decrement (--) operator should have no     */
/*                       potential side effects other than that caused by the increment or decrement operator.        */
/* Rule                : MISRA C:2012 Rule-13.3                                                                       */
/* JV-01 Justification : An increment/decrement is created a side affect. In this case it's accessing a volatile      */
/*                       object. This can be accepted.                                                                */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:0312)    : Dangerous pointer cast results in loss of volatile qualification.                            */
/* Rule                : CERTCCM EXP32, MISRA C:2012 Rule-11.8, CWE Rule CWE-737                                      */
/* JV-01 Justification : According to the coding guide, all global variables must have volatile attribute, but        */
/*                       volatile must be removed when return these variables from APIs according to the AUTOSAR      */
/*                       specification.                                                                               */
/*       Verification  : Since these are normal memory objects, any problem doesn't occurs.                           */
/**********************************************************************************************************************/
/* Message (3:2004)    : No concluding 'else' exists in this 'if'-'else'-'if' statement.                              */
/* Rule                : MISRA C:2012 Rule-15.7, CERTCCM MSC01, CWE Rule CWE-398, CWE-569                             */
/* JV-01 Justification : The "else"statement with empty content is removed to improve readability.                    */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (6:2993)    : The value of this 'do - while' loop controlling expression is always 'false'. The loop will  */
/*                       only be executed once.                                                                       */
/* Rule                : MISRA C:2012 Rule-14.3                                                                       */
/* JV-01 Justification : This loop will only be executed atleast once, depends on user configuration.                 */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (6:2996)    : The result of this logical operation is always 'false'.                                      */
/* Rule                : MISRA C:2012 Rule-2.2, CWE Rule CWE-561, CWE-633                                             */
/* JV-01 Justification : Depending on device status, there is case where the 'if' will return 'true'.                 */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/
#if (LIN_MASTER_MODE_SUPPORT == STD_ON)
#define LIN_START_SEC_CONST_UNSPECIFIED
#include "Lin_MemMap.h"
/* This structure contains Sleep frame PDU parameters */
static CONST(Lin_PduType, LIN_CONFIG_DATA) Lin_GstSleepPdu =                                                            /* PRQA S 3218 # JV-01 */
{
  /* PID */
  LIN_SLEEP_COMMAND,
  /* Cs Model equal to classic */
  LIN_CLASSIC_CS,
  #if (LIN_AR_VERSION == LIN_AR_R22_11_VERSION)
  /* Frame direction equal to LIN_FRAMERESPONSE_TX */
  LIN_FRAMERESPONSE_TX,
  #else
  /* Frame direction equal to LIN_MASTER_RESPONSE */
  LIN_MASTER_RESPONSE,
  #endif /* #if (LIN_AR_VERSION == LIN_AR_R22_11_VERSION) */
  /*Frame data length equal to eight */
  LIN_EIGHT,
  /* Data pointer points to NULL */
  NULL_PTR
};
#define LIN_STOP_SEC_CONST_UNSPECIFIED
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* #if (LIN_MASTER_MODE_SUPPORT == STD_ON) */

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/

/***********************************************************************************************************************
** Function Name      : Lin_Init
**
** Service ID         : 0x00
**
** Description        : Initializes the LIN module.
**
** Sync/Async         : Synchronous
**
** Re-entrancy        : Non-Reentrant
**
** Input Parameters   : Config
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return Parameter   : None
**
** Preconditions      : Lin Driver state shall be in LIN_UNINIT
**
** Global Variables   : Lin_GaaGlobalAccPoint
**                      Lin_GaaGetCoreId2Index (LIN_MULTI_CORE_SUPPORT == STD_ON),
**                      Lin_GaaChannelId2CoreIndex (LIN_MULTI_CORE_SUPPORT == STD_ON)
**
** Functions invoked  : Det_ReportError, Lin_HwInit, Lin_SetStatus, GetCoreID (LIN_MULTI_CORE_SUPPORT == STD_ON)
**
** Registers Used     : None
**
** Reference ID       : LIN_DUD_ACT_001, LIN_DUD_ACT_001_ERR001,
** Reference ID       : LIN_DUD_ACT_001_ERR002, LIN_DUD_ACT_001_ERR003
** Reference ID       : LIN_DUD_ACT_001_GBL001, LIN_DUD_ACT_001_GBL003
** Reference ID       : LIN_DUD_ACT_001_GBL004, LIN_DUD_ACT_001_GBL005
** Reference ID       : LIN_DUD_ACT_001_GBL006, LIN_DUD_ACT_001_GBL007
** Reference ID       : LIN_DUD_ACT_001_GBL008, LIN_DUD_ACT_001_GBL009
** Reference ID       : LIN_DUD_ACT_001_GBL010, LIN_DUD_ACT_001_ERR004
** Reference ID       : LIN_DUD_ACT_001_GBL011, LIN_DUD_ACT_001_GBL012
** Reference ID       : LIN_DUD_ACT_001_GBL013
***********************************************************************************************************************/
#define LIN_START_SEC_PUBLIC_CODE
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(void, LIN_PUBLIC_CODE) Lin_Init(P2CONST(Lin_ConfigType, AUTOMATIC, LIN_APPL_CONST) Config)                         /* PRQA S 1503 # JV-01 */
{
  volatile P2VAR(Lin_RamData, AUTOMATIC, LIN_APPL_DATA) LpRamVars;                                                      /* PRQA S 3432 # JV-01 */

  Std_ReturnType LucReturnValue;

  uint8 LucNoOfLinChannels;
  uint8 LucCoreIndex;
  uint8 LucChannelRamIndex;

  #if (LIN_DEV_ERROR_DETECT == STD_ON)
  boolean LblDetErrFlag;
  #endif

  #if (LIN_MULTI_CORE_SUPPORT == STD_ON)
  uint8 LucCoreId;
  /* Get Core id for code branching */
  LucCoreId = (uint8)GetCoreID();
  /* Covert Core Id to Core Index */
  LucCoreIndex = Lin_GaaGetCoreId2Index[LucCoreId];
  #else
  /* if Multicore is not configude, defauld coreid is 0x00
     To optimize implementation */
  LucCoreIndex = LIN_ZERO;
  #endif /* #if (LIN_MULTI_CORE_SUPPORT == STD_ON) */

  #if (LIN_DEV_ERROR_DETECT == STD_ON)
  /* Initialize error status flag to LIN_FALSE */
  LblDetErrFlag = LIN_FALSE;

  #if (LIN_MULTI_CORE_SUPPORT == STD_ON)
  /* Check invalid core for init API */
  if(LIN_INVALID_CORE == LucCoreIndex)
  {
    /* Report to DET */
    (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_INIT_SID, LIN_E_INVALID_CORE);

    /* Set the error status flag to LIN_TRUE */
    LblDetErrFlag = LIN_TRUE;
  }
  else
  #endif
  {
    #if (LIN_ALREADY_INIT_DET_CHECK == STD_ON)
    /* Check if Lin is not in UNINIT state */
    if (LIN_UNINIT != *(Lin_GaaGlobalAccPoint[LucCoreIndex].pDriverState))
    {
      /* Report to DET */
      (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_INIT_SID, LIN_E_STATE_TRANSITION);

      /* Set the error status flag to LIN_TRUE */
      LblDetErrFlag = LIN_TRUE;
    } /* else No action required */
    #endif /* #if (LIN_ALREADY_INIT_DET_CHECK == STD_ON) */
  }

  /* Check if Lin configuration pointer is a NULL Pointer */
  if (NULL_PTR == Config)
  {
    /* Report to DET */
    (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_INIT_SID, LIN_E_INVALID_POINTER);

    /* Set the error status flag to LIN_TRUE */
    LblDetErrFlag = LIN_TRUE;
  }
  else if ((uint32)LIN_DBTOC_VALUE != (Config->ulStartOfDbToc))                                                         /* PRQA S 2004 # JV-01 */
  {
    /* Report to DET */
    (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_INIT_SID, LIN_E_INVALID_DATABASE);

    /* Set the error status flag to LIN_TRUE */
    LblDetErrFlag = LIN_TRUE;
  } /* else No action required */

  /* Check if no DET error is occurred */
  if (LIN_FALSE == LblDetErrFlag)
  #endif /* #if (LIN_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Initializes the global pointer of LIN first channel config structure */
    *(Lin_GaaGlobalAccPoint[LucCoreIndex].pChannelConfig) = 
        (volatile P2CONST(Lin_ChannelInfo, LIN_VAR_NO_INIT, LIN_APPL_CONST))                                            /* PRQA S 0316 # JV-01 */
        (Config->pFirstChannel);

    /* Initializes the global pointer to RLIN3 first channel structure */
    *(Lin_GaaGlobalAccPoint[LucCoreIndex].pRLIN3Properties) =
        (volatile P2CONST(Lin3_ChannelConfigType, LIN_VAR_NO_INIT, LIN_APPL_CONST))                                     /* PRQA S 0316 # JV-01 */
        (Config->pRLIN3Properties);

    /* Initializes RLIN3 HW for configured channels */
    LucNoOfLinChannels = LIN_ZERO;

    /* Initialize the return value */
    LucReturnValue = E_OK;                                                                                              /* PRQA S 2982 # JV-01 */

    do
    {
      /* Check if channel is belong to this core in multicore */
      #if (LIN_MULTI_CORE_SUPPORT == STD_ON )
      if (LucCoreIndex == Lin_GaaChannelId2CoreIndex[LucNoOfLinChannels])
      {
        /* Get Channel Ram Index for each core */
        LucChannelRamIndex = 
        (*(Lin_GaaGlobalAccPoint[LucCoreIndex].pChannelConfig))[LucNoOfLinChannels].ucChannelRamIndex;
      #else
        /* single core - Channel Ram index = channel id */
        LucChannelRamIndex = LucNoOfLinChannels;
      #endif /* #if (LIN_MULTI_CORE_SUPPORT == STD_ON) */

        /* Initializes the LIN HW channel - input channel index : Channel config */
        LucReturnValue = Lin_HwInit(LucNoOfLinChannels, LucCoreIndex);

        /* Get the pointer to channel RAM data */
        LpRamVars = &(Lin_GaaGlobalAccPoint[LucCoreIndex].pChannelRamData[LucChannelRamIndex]);

        /* Initialize the sleep requested bit */
        LpRamVars->ucSlpRqst_RespRdy = LIN_CLR_SLEEP_REQUEST;

        #if (LIN_AR_VERSION == LIN_AR_422_VERSION)
        /* Initialize channel status */
        LpRamVars->enChannelStatus = LIN_OPERATIONAL;
        #elif ((LIN_AR_VERSION == LIN_AR_431_VERSION) || (LIN_AR_VERSION == LIN_AR_R22_11_VERSION))
        /* Initialize channel status */
        LpRamVars->enChannelStatus = LIN_CH_SLEEP;
        #endif /* #if (LIN_AR_VERSION == LIN_AR_422_VERSION) */

        /* Initialize the LinIf wake-up flag */
        LpRamVars->blWakeupCalled = LIN_FALSE;

        /* Initialize the frame identifier */
        LpRamVars->ucFrameId = LIN_ZERO;

        /* Initialize the frame length */
        LpRamVars->ucFrameLength = LIN_ONE;

        /* Initialize the sleep pending status */
        LpRamVars->blSleepPending = LIN_FALSE;

        #if (LIN_SLAVE_MODE_SUPPORT == STD_ON)
        /* Initialize Header completion flag */
        LpRamVars->blHeaderComplete = LIN_FALSE;
        #endif

        /* Initialize the the checksum model */
        LpRamVars->enCheckSumModel = LIN_ENHANCED_CS;

        /* Initialize the frame type */
        LpRamVars->enFrameType = LIN_FRAMERESPONSE_TX;

      /* Check if channel is belong to this core in multicore support */
      #if (LIN_MULTI_CORE_SUPPORT == STD_ON)
      }
      #endif /* #if (LIN_MULTI_CORE_SUPPORT == STD_ON) */
      /* increasign channel index */
      LucNoOfLinChannels++;                                                                                             /* PRQA S 3383 # JV-01 */

    }while ((LIN_NO_OF_CHANNELS > LucNoOfLinChannels) && (E_OK == LucReturnValue));                                     /* PRQA S 2996, 2993 # JV-01, JV-01 */

    if (E_OK == LucReturnValue)
    {
      /* Set the status of LIN driver to LIN_INIT */
      Lin_SetStatus(LIN_INIT, LucCoreIndex);
    } /* else No action required */

  } /* if (LblDetErrFlag == LIN_FALSE) */
    /* else No action required */
}
#define LIN_STOP_SEC_PUBLIC_CODE
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name      : Lin_CheckWakeup
**
** Service ID         : 0x0A
**
** Description        : After a wake-up caused by LIN bus transceiver, the API
**                      Lin_CheckWakeup() will be called by the LIN Interface
**                      to identify the corresponding LIN channel. After
**                      detecting of a wake-up event on an individual channel,
**                      the LIN Driver has to notify the ECU state Manager
**                      immediately via the EcuM_SetWakeupEvent() call-back
**                      function.
**
** Sync/Async         : Synchronous
**
** Re-entrancy        : Non-Reentrant
**
** Input Parameters   : Channel
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : Std_ReturnType
**
** Preconditions      : None
**
** Global Variables   : Lin_GaaGlobalAccPoint,
**                      Lin_GaaGetCoreId2Index (LIN_MULTI_CORE_SUPPORT == STD_ON),
**
** Functions invoked  : Det_ReportError,
**                      EcuM_SetWakeupEvent, LinIf_WakeupConfirmation,
**                      LIN_ENTER_CRITICAL_SECTION, LIN_EXIT_CRITICAL_SECTION,
**                      GetCoreID (LIN_MULTI_CORE_SUPPORT == STD_ON)
**
** Registers Used     : None
**
** Reference ID       : LIN_DUD_ACT_002, LIN_DUD_ACT_002_ERR001,
** Reference ID       : LIN_DUD_ACT_002_ERR002, LIN_DUD_ACT_002_ERR003,
** Reference ID       : LIN_DUD_ACT_002_ERR004, LIN_DUD_ACT_002_GBL001,
** Reference ID       : LIN_DUD_ACT_002_CRT003, LIN_DUD_ACT_002_CRT004,
** Reference ID       : LIN_DUD_ACT_002_CRT005, LIN_DUD_ACT_002_ERR005
** Reference ID       : LIN_DUD_ACT_002_ERR006
***********************************************************************************************************************/
#define LIN_START_SEC_PUBLIC_CODE
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, LIN_PUBLIC_CODE) Lin_CheckWakeup(uint8 Channel)                                                    /* PRQA S 1503 # JV-01 */
{

  #if (LIN_WAKEUP_SUPPORT == STD_ON)
  volatile P2CONST(Lin_ChannelInfo, AUTOMATIC, LIN_PRIVATE_CONST) LpLinChannelPtr;
  volatile P2VAR(Lin_RamData, AUTOMATIC, LIN_APPL_DATA) LpRamVars;                                                      /* PRQA S 3432 # JV-01 */
  #endif /* #if (LIN_WAKEUP_SUPPORT == STD_ON) */

  #if (LIN_DEV_ERROR_DETECT == STD_ON)
  boolean LblDetErrFlag;
  #endif

  Std_ReturnType LucReturnValue;
  #if (LIN_WAKEUP_SUPPORT == STD_ON)
  uint8 LucChannelRamIndex;
  #endif /* #if ((LIN_DEV_ERROR_DETECT == STD_ON) && (LIN_WAKEUP_SUPPORT == STD_ON)) */
  uint8 LucCoreIndex;

  #if (LIN_MULTI_CORE_SUPPORT == STD_ON)
  uint8 LucCoreId;
  /* Get Core id for code branching */
  LucCoreId = (uint8)GetCoreID();
  /* Covert Core Id to Core Index */
  LucCoreIndex = Lin_GaaGetCoreId2Index[LucCoreId];
  #else
  /* if Multicore is not configude, defauld coreid is 0x00
     To optimize implementation */
  LucCoreIndex = LIN_ZERO;
  #endif /* #if (LIN_MULTI_CORE_SUPPORT == STD_ON) */

  /* Initialize the return value to E_OK */
  LucReturnValue = E_OK;

  #if (LIN_DEV_ERROR_DETECT == STD_ON)
  /* Initialize error status flag to LIN_FALSE */
  LblDetErrFlag = LIN_FALSE;
  #endif /* (LIN_DEV_ERROR_DETECT == STD_ON) */

  #if (LIN_AR_VERSION == LIN_AR_422_VERSION)
  #if (LIN_DEV_ERROR_DETECT == STD_ON)
  /* Report to DET, if module is not Initialized */
  if (LIN_UNINIT == *(Lin_GaaGlobalAccPoint[LucCoreIndex].pDriverState))
  {
    /* Report to DET */
    (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_CHECK_WAKEUP_SID, LIN_E_UNINIT);

    /* Set the error status flag to LIN_TRUE and return E_NOT_OK */
    LblDetErrFlag = LIN_TRUE;
    LucReturnValue = E_NOT_OK;
  }
  else
  {
    /* Report to DET, if Channel is out of range */
    if (LIN_MAX_CHANNEL_ID < Channel)
    {
      /* Report to DET */
      (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_CHECK_WAKEUP_SID, LIN_E_INVALID_CHANNEL);

      /* Set the error status flag to LIN_TRUE and return E_NOT_OK*/
      LblDetErrFlag = LIN_TRUE;
      LucReturnValue = E_NOT_OK;
    } /* else No action required */
  }
  #endif /* #if (LIN_DEV_ERROR_DETECT == STD_ON) */
  #elif ((LIN_AR_VERSION == LIN_AR_431_VERSION) || (LIN_AR_VERSION == LIN_AR_R22_11_VERSION))
  #if (LIN_MULTI_CORE_SUPPORT == STD_ON)
  /* Check invalid core for init API */
  if(LIN_INVALID_CORE == LucCoreIndex)
  {
    #if (LIN_DEV_ERROR_DETECT == STD_ON)
    /* Report to DET */
    (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_CHECK_WAKEUP_SID, LIN_E_INVALID_CORE);
    /* Set the error status flag to LIN_TRUE */
    LblDetErrFlag = LIN_TRUE;
    #endif /* #if (LIN_DEV_ERROR_DETECT == STD_ON) */
    /* Return E_NOT_OK if error occurs */
    LucReturnValue = E_NOT_OK;
  }
  else
  #endif /* #if (LIN_MULTI_CORE_SUPPORT == STD_ON) */
  {
    if (LIN_UNINIT == *(Lin_GaaGlobalAccPoint[LucCoreIndex].pDriverState))
    {
      #if (LIN_DEV_ERROR_DETECT == STD_ON)
      /* Report to DET */
      (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_CHECK_WAKEUP_SID, LIN_E_UNINIT);

      /* Set the error status flag to LIN_TRUE */
      LblDetErrFlag = LIN_TRUE;
      #endif /* #if (LIN_DEV_ERROR_DETECT == STD_ON) */
      /* Return E_NOT_OK if error occurs */
      LucReturnValue = E_NOT_OK;
    }
    else
    {
      /* Report to DET, if Channel is out of range */
      if (LIN_MAX_CHANNEL_ID < Channel)
      {
        #if (LIN_DEV_ERROR_DETECT == STD_ON)
        /* Report to DET */
        (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_CHECK_WAKEUP_SID, LIN_E_INVALID_CHANNEL);

        /* Set the error status flag to LIN_TRUE */
        LblDetErrFlag = LIN_TRUE;
        #endif /* #if (LIN_DEV_ERROR_DETECT == STD_ON) */
        /* Return E_NOT_OK if error occurs */
        LucReturnValue = E_NOT_OK;
      }
      else
      {
        /* DET error if invalid call for current  core */
        #if (LIN_MULTI_CORE_SUPPORT == STD_ON)
        if (LucCoreIndex != Lin_GaaChannelId2CoreIndex[Channel])
        {
          #if (LIN_DEV_ERROR_DETECT == STD_ON)
          (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_CHECK_WAKEUP_SID, LIN_E_INVALID_CORE);
          /* Set the error status flag to LIN_TRUE */
          LblDetErrFlag = LIN_TRUE;
          #endif
          /* Return E_NOT_OK if error occurs */
          LucReturnValue = E_NOT_OK;
        } /* else no action */
        #endif /* #if (LIN_MULTI_CORE_SUPPORT == STD_ON) */
      }
    }
  }
  #endif /* if (LIN_AR_VERSION == LIN_AR_422_VERSION) */

  #if (LIN_DEV_ERROR_DETECT == STD_ON)
  /* Check if DET error occured */
  if (LIN_FALSE == LblDetErrFlag)
  #endif /* #if (LIN_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Check if no error occured */
    if (E_OK == LucReturnValue)                                                                                         /* PRQA S 2995, 2991 # JV-01, JV-01 */
    {
      #if (LIN_WAKEUP_SUPPORT == STD_ON)
      #if (LIN_MULTI_CORE_SUPPORT == STD_ON)
      /* Get Channel Ram Index for each core */
      LucChannelRamIndex = (*(Lin_GaaGlobalAccPoint[LucCoreIndex].pChannelConfig))[Channel].ucChannelRamIndex;
      #else
      /* single core - Channel Ram index = channel id */
      LucChannelRamIndex = Channel;
      #endif /* #if (LIN_MULTI_CORE_SUPPORT == STD_ON) */
      /* Get the address of Channel info structure */
      LpLinChannelPtr = &((*(Lin_GaaGlobalAccPoint[LucCoreIndex].pChannelConfig))[Channel]);

      /* Get the pointer to channel RAM data */
      LpRamVars = &(Lin_GaaGlobalAccPoint[LucCoreIndex].pChannelRamData[LucChannelRamIndex]);

      /* Enter the protection area */
      LIN_ENTER_CRITICAL_SECTION(LIN_RAM_DATA_PROTECTION);
      /* Check if wake-up occurred */
      if (LIN_WAKEUP == LpRamVars->ucSlpRqst_RespRdy)
      {
        /* Clear the sleep requested bit */
        LpRamVars->ucSlpRqst_RespRdy = LIN_CLR_SLEEP_REQUEST;

        /* Exit the protection area */
        LIN_EXIT_CRITICAL_SECTION(LIN_RAM_DATA_PROTECTION);

        /* Invoke the upper layer wakeup notification */
        EcuM_SetWakeupEvent((EcuM_WakeupSourceType)LIN_ONE << (LpLinChannelPtr->ucWakeupSourceId));

        /* Invoke the LinIf wakeup notification */
        LinIf_WakeupConfirmation((EcuM_WakeupSourceType)LIN_ONE << (LpLinChannelPtr->ucWakeupSourceId));
      }
      else
      {
        /* Exit the protection area */
        LIN_EXIT_CRITICAL_SECTION(LIN_RAM_DATA_PROTECTION);
      }
      #endif /* #if (LIN_WAKEUP_SUPPORT == STD_ON) */
    } /* else No action required */
  } /* else No action required */
  return (LucReturnValue);
}
#define LIN_STOP_SEC_PUBLIC_CODE
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Lin_GetVersionInfo
**
** Service ID            : 0x01
**
** Description           : This API returns the version information of LIN
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
** Reference ID          : LIN_DUD_ACT_003, LIN_DUD_ACT_003_ERR001
***********************************************************************************************************************/
#if (LIN_VERSION_INFO_API == STD_ON)
#define LIN_START_SEC_PUBLIC_CODE
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(void, LIN_PUBLIC_CODE) Lin_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, LIN_APPL_DATA) versioninfo)        /* PRQA S 1503, 3432 # JV-01, JV-01 */
{
#if (LIN_DEV_ERROR_DETECT == STD_ON)
  /* Check if parameter passed is equal to Null pointer */
  if (NULL_PTR == versioninfo)
  {
    /* Report to DET */
    (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_GET_VERSIONINFO_SID, LIN_E_PARAM_POINTER);
  }
  else
#endif /* (LIN_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Copy the vendor Id */
    versioninfo->vendorID = (uint16)LIN_VENDOR_ID;
    /* Copy the module Id */
    versioninfo->moduleID = (uint16)LIN_MODULE_ID;
    /* Copy Software Major Version */
    versioninfo->sw_major_version = LIN_SW_MAJOR_VERSION;
    /* Copy Software Minor Version */
    versioninfo->sw_minor_version = LIN_SW_MINOR_VERSION;
    /* Copy Software Patch Version */
    versioninfo->sw_patch_version = LIN_SW_PATCH_VERSION;
  }
}
#define LIN_STOP_SEC_PUBLIC_CODE
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* #if (LIN_VERSION_INFO_API == STD_ON) */

/***********************************************************************************************************************
** Function Name      : Lin_SendFrame
**
** Service ID         : 0x04
**
** Description        : This service sends a LIN header and LIN response on
**                      addressed LIN channel.
**                      Only used for LIN master nodes.
**
** Sync/Async         : Asynchronous
**
** Re-entrancy        : Non-Reentrant
**
** Input Parameters   : Channel, PduInfoPtr
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : Std_ReturnType
**
** Preconditions      : The LIN Driver must be initialized. The LIN Channel must be in LIN_CH_OPERATIONAL state,
**                      LIN_MASTER_MODE_SUPPORT must be STD_ON
**
** Global Variables   : Lin_GaaGlobalAccPoint
**                      Lin_GaaGetCoreId2Index (LIN_MULTI_CORE_SUPPORT == STD_ON),
**                      Lin_GaaChannelId2CoreIndex (LIN_MULTI_CORE_SUPPORT == STD_ON)
**
** Functions invoked  : Det_ReportError, Lin_HwSendHeaderInternal, Lin_HwScheduleInterrupt
**                      LIN_ENTER_CRITICAL_SECTION, LIN_EXIT_CRITICAL_SECTION
**                      GetCoreID (LIN_MULTI_CORE_SUPPORT == STD_ON)
**
** Registers Used     : None
**
** Reference ID       : LIN_DUD_ACT_004, LIN_DUD_ACT_004_ERR001,
** Reference ID       : LIN_DUD_ACT_004_ERR002, LIN_DUD_ACT_004_ERR003,
** Reference ID       : LIN_DUD_ACT_004_ERR004, LIN_DUD_ACT_004_ERR005,
** Reference ID       : LIN_DUD_ACT_004_ERR006, LIN_DUD_ACT_004_ERR007,
** Reference ID       : LIN_DUD_ACT_004_ERR008, LIN_DUD_ACT_004_ERR009,
** Reference ID       : LIN_DUD_ACT_004_ERR010, LIN_DUD_ACT_004_GBL001,
** Reference ID       : LIN_DUD_ACT_004_CRT001, LIN_DUD_ACT_004_CRT002,
** Reference ID       : LIN_DUD_ACT_004_ERR011, LIN_DUD_ACT_004_ERR012,
** Reference ID       : LIN_DUD_ACT_004_ERR013
***********************************************************************************************************************/
/* SWS_Lin_00287 */
#if (LIN_MASTER_MODE_SUPPORT == STD_ON)
#define LIN_START_SEC_PUBLIC_CODE
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#if (LIN_AR_VERSION == LIN_AR_422_VERSION)
FUNC(Std_ReturnType, LIN_PUBLIC_CODE)
Lin_SendFrame(uint8 Channel, P2VAR(Lin_PduType, AUTOMATIC, LIN_APPL_DATA) PduInfoPtr)
#elif ((LIN_AR_VERSION == LIN_AR_431_VERSION) || (LIN_AR_VERSION == LIN_AR_R22_11_VERSION))
FUNC(Std_ReturnType, LIN_PUBLIC_CODE)
Lin_SendFrame(uint8 Channel, P2CONST(Lin_PduType, AUTOMATIC, LIN_APPL_DATA) PduInfoPtr)                                 /* PRQA S 1503 # JV-01 */
#endif /* #if (LIN_AR_VERSION == LIN_AR_422_VERSION) */
{
  volatile P2VAR(Lin_RamData, AUTOMATIC, LIN_APPL_DATA) LpRamVars;                                                      /* PRQA S 3432 # JV-01 */
  volatile P2VAR(uint8, AUTOMATIC, LIN_APPL_DATA) volatile LpDataBufferPtr;                                             /* PRQA S 3432 # JV-01 */
  P2VAR(uint8, AUTOMATIC, LIN_APPL_DATA) LpSduPtr;                                                                      /* PRQA S 3432, 3678 # JV-01, JV-01 */
  Std_ReturnType LucReturnValue;

  #if (LIN_DEV_ERROR_DETECT == STD_ON)
  boolean LblDetErrFlag;
  boolean LblSleepPending;
  Lin_StatusType LenChannelStatus;
  #elif ((LIN_DEV_ERROR_DETECT == STD_OFF) && \
                                  ((LIN_AR_VERSION == LIN_AR_431_VERSION) || (LIN_AR_VERSION == LIN_AR_R22_11_VERSION)))
  boolean LblSleepPending;
  Lin_StatusType LenChannelStatus;
  #endif

  uint8 LucChannelRamIndex;
  uint8 LucCoreIndex;
  uint8 LucCount;

  #if (LIN_MULTI_CORE_SUPPORT == STD_ON)
  uint8 LucCoreId;
  /* Get Core id for code branching */
  LucCoreId = (uint8)GetCoreID();
  /* Covert Core Id to Core Index */
  LucCoreIndex = Lin_GaaGetCoreId2Index[LucCoreId];
  #else
  /* if Multicore is not configude, defauld coreid is 0x00
     To optimize implementation */
  LucCoreIndex = LIN_ZERO;
  #endif /* #if (LIN_MULTI_CORE_SUPPORT == STD_ON) */

  /* Set the error flag */
  LucReturnValue = E_OK;

  #if (LIN_DEV_ERROR_DETECT == STD_ON)
  /* Initialize error status flag to LIN_FALSE */
  LblDetErrFlag = LIN_FALSE;
  #endif /* #if  (LIN_DEV_ERROR_DETECT == STD_ON) */

  #if (LIN_AR_VERSION == LIN_AR_422_VERSION)
  #if (LIN_DEV_ERROR_DETECT == STD_ON)
  /* Report to DET, if module is not initialized */
  if (LIN_UNINIT == *(Lin_GaaGlobalAccPoint[LucCoreIndex].pDriverState))
  {
    /* Report to DET */
    (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_SEND_FRAME_SID, LIN_E_UNINIT);

    /* Set the error status flag to LIN_TRUE */
    LblDetErrFlag = LIN_TRUE;
    LucReturnValue = E_NOT_OK;
  }
  else
  {
    /* Report to DET, if Channel is out of range */
    if (LIN_MAX_CHANNEL_ID < Channel)
    {
      /* Report to DET */
      (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_SEND_FRAME_SID, LIN_E_INVALID_CHANNEL);

      /* Set the error status flag to LIN_TRUE */
      LblDetErrFlag = LIN_TRUE;
      LucReturnValue = E_NOT_OK;
    }
    else
    {
      #if (LIN_MULTI_CORE_SUPPORT == STD_ON)
      /* Get Channel Ram Index for each core */
      LucChannelRamIndex = (*(Lin_GaaGlobalAccPoint[LucCoreIndex].pChannelConfig))[Channel].ucChannelRamIndex;
      #else
      /* single core - Channel Ram index = channel id */
      LucChannelRamIndex = Channel;
      #endif /* #if (LIN_MULTI_CORE_SUPPORT == STD_ON) */

      /* Get the address of LIN Channel structure */
      LenChannelStatus = 
      (Lin_GaaGlobalAccPoint[LucCoreIndex].pChannelRamData)[LucChannelRamIndex].enChannelStatus;

      /* Get the address of LIN Channel structure */
      LblSleepPending = (Lin_GaaGlobalAccPoint[LucCoreIndex].pChannelRamData)[LucChannelRamIndex].blSleepPending;

      /* Check if the channel is in sleep state */
      if ((LIN_CH_SLEEP == LenChannelStatus) || (LIN_TRUE == LblSleepPending))
      {
        /* Report to DET */
        (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_SEND_FRAME_SID, LIN_E_STATE_TRANSITION);

        /* Set the error status flag to LIN_TRUE */
        LblDetErrFlag = LIN_TRUE;
        LucReturnValue = E_NOT_OK;
      } /* else No action required */
    }

    /* Report to DET if Pdu Info pointer is a NULL pointer */
    if (NULL_PTR == PduInfoPtr)
    {
      /* Report to DET */
      (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_SEND_FRAME_SID, LIN_E_PARAM_POINTER);

      /* Set the error status flag to LIN_TRUE */
      LblDetErrFlag = LIN_TRUE;
      LucReturnValue = E_NOT_OK;
    }
    else
    {
      /* Get the pointer to data pointer */
      LpSduPtr = PduInfoPtr->SduPtr;

      /* Report to DET, if Sdu Pointer is a NULL pointer */
      if ((LIN_MASTER_RESPONSE == PduInfoPtr->Drc) && (NULL_PTR == LpSduPtr))
      {
        /* Report to DET */
        (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_SEND_FRAME_SID, LIN_E_PARAM_POINTER);

        /* Set the error status flag to LIN_TRUE */
        LblDetErrFlag = LIN_TRUE;
        LucReturnValue = E_NOT_OK;
      } /* else No action required */
    }
  }
  #endif /* #if (LIN_DEV_ERROR_DETECT == STD_ON) */
  #elif ((LIN_AR_VERSION == LIN_AR_431_VERSION) || (LIN_AR_VERSION == LIN_AR_R22_11_VERSION))
  /* Check invalid core for API */
  #if (LIN_MULTI_CORE_SUPPORT == STD_ON)
  if(LIN_INVALID_CORE == LucCoreIndex)
  {
    #if (LIN_DEV_ERROR_DETECT == STD_ON)
    /* Report to DET */
    (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_SEND_FRAME_SID, LIN_E_INVALID_CORE);
    /* Set the error status flag to LIN_TRUE */
    LblDetErrFlag = LIN_TRUE;
    #endif /* #if (LIN_DEV_ERROR_DETECT == STD_ON) */
    /* Set the error status flag to LIN_TRUE */
    LucReturnValue = E_NOT_OK;
  }
  else
  #endif /* #if (LIN_MULTI_CORE_SUPPORT == STD_ON) */
  {
    /* Report to DET, if module is not initialized */
    if (LIN_UNINIT == *(Lin_GaaGlobalAccPoint[LucCoreIndex].pDriverState))
    {
      #if (LIN_DEV_ERROR_DETECT == STD_ON)
      /* Report to DET */
      (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_SEND_FRAME_SID, LIN_E_UNINIT);

      /* Set the error status flag to LIN_TRUE */
      LblDetErrFlag = LIN_TRUE;
      #endif /* #if (LIN_DEV_ERROR_DETECT == STD_ON) */
      LucReturnValue = E_NOT_OK;
    }
    else
    {
      /* Report to DET, if Channel is out of range */
      if (LIN_MAX_CHANNEL_ID < Channel)
      {
        #if (LIN_DEV_ERROR_DETECT == STD_ON)
        /* Report to DET */
        (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_SEND_FRAME_SID, LIN_E_INVALID_CHANNEL);

        /* Set the error status flag to LIN_TRUE */
        LblDetErrFlag = LIN_TRUE;
        #endif /* #if (LIN_DEV_ERROR_DETECT == STD_ON) */
        LucReturnValue = E_NOT_OK;
      }
      else
      {
        /* DET error if invalid call for current  core */
        #if (LIN_MULTI_CORE_SUPPORT == STD_ON)
        if (LucCoreIndex!= Lin_GaaChannelId2CoreIndex[Channel])
        {
          #if (LIN_DEV_ERROR_DETECT == STD_ON)
          (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_SEND_FRAME_SID, LIN_E_INVALID_CORE);
          /* Set the error status flag to LIN_TRUE */
          LblDetErrFlag = LIN_TRUE;
          #endif
          /* Return E_NOT_OK if error occurs */
          LucReturnValue = E_NOT_OK;
        }
        else
        #endif /* #if (LIN_MULTI_CORE_SUPPORT == STD_ON) */
        {
          #if (LIN_MULTI_CORE_SUPPORT == STD_ON)
          /* Get Channel Ram Index for each core */
          LucChannelRamIndex = (*(Lin_GaaGlobalAccPoint[LucCoreIndex].pChannelConfig))[Channel].ucChannelRamIndex;
          #else
          /* single core - Channel Ram index = channel id */
          LucChannelRamIndex = Channel;
          #endif /* #if (LIN_MULTI_CORE_SUPPORT == STD_ON) */

          #if (LIN_SLAVE_MODE_SUPPORT == STD_ON)
          /* [AR21-11] Support Slave mode: SWS_Lin_00287 Lin_SendFrame is only applicable for LIN master nodes */
          if (LIN_SLAVE_NODE == (*(Lin_GaaGlobalAccPoint[LucCoreIndex].pChannelConfig))[Channel].enNodeType)
          {
            #if (LIN_DEV_ERROR_DETECT == STD_ON)
            /* Report to DET */
            (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_SEND_FRAME_SID, LIN_E_INVALID_NODE_TYPE);
            /* Set the error status flag to LIN_TRUE */
            LblDetErrFlag = LIN_TRUE;
            #endif /* #if (LIN_DEV_ERROR_DETECT == STD_ON) */
            LucReturnValue = E_NOT_OK;
          }
          else
          #endif /* (LIN_SLAVE_MODE_SUPPORT == STD_ON) */
          {
            /* Get the address of LIN Channel structure */
            LenChannelStatus = 
            (Lin_GaaGlobalAccPoint[LucCoreIndex].pChannelRamData)[LucChannelRamIndex].enChannelStatus;
            /* Get the address of LIN Channel structure */
            LblSleepPending = (Lin_GaaGlobalAccPoint[LucCoreIndex].pChannelRamData)[LucChannelRamIndex].blSleepPending;

            /* Check if the channel is in sleep state */
            if ((LIN_CH_SLEEP == LenChannelStatus) || (LIN_TRUE == LblSleepPending))
            {
              #if (LIN_DEV_ERROR_DETECT == STD_ON)
              /* Report to DET */
              (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_SEND_FRAME_SID, LIN_E_STATE_TRANSITION);

              /* Set the error status flag to LIN_TRUE */
              LblDetErrFlag = LIN_TRUE;
              #endif /* #if (LIN_DEV_ERROR_DETECT == STD_ON) */
              LucReturnValue = E_NOT_OK;
            } /* else No action required */
          }
        }
      }

      /* Report to DET if Pdu Info pointer is a NULL pointer */
      if (NULL_PTR == PduInfoPtr)
      {
        #if (LIN_DEV_ERROR_DETECT == STD_ON)
        /* Report to DET */
        (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_SEND_FRAME_SID, LIN_E_PARAM_POINTER);

        /* Set the error status flag to LIN_TRUE */
        LblDetErrFlag = LIN_TRUE;
        #endif /* #if (LIN_DEV_ERROR_DETECT == STD_ON) */
        LucReturnValue = E_NOT_OK;
      }
      else
      {
        /* Get the pointer to data pointer */
        LpSduPtr = PduInfoPtr->SduPtr;

        #if (LIN_AR_VERSION == LIN_AR_R22_11_VERSION)
        /* Report to DET, if Sdu Pointer is a NULL pointer */
        /* AR21-11 use LIN_FRAMERESPONSE_TX instead of LIN_MASTER_RESPONSE */
        if ((LIN_FRAMERESPONSE_TX == PduInfoPtr->Drc) && (NULL_PTR == LpSduPtr))
        #else
        /* Report to DET, if Sdu Pointer is a NULL pointer */
        if ((LIN_MASTER_RESPONSE == PduInfoPtr->Drc) && (NULL_PTR == LpSduPtr))
        #endif /* #if (LIN_AR_VERSION == LIN_AR_431_VERSION) */
        {
          #if (LIN_DEV_ERROR_DETECT == STD_ON)
          /* Report to DET */
          (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_SEND_FRAME_SID, LIN_E_PARAM_POINTER);

          /* Set the error status flag to LIN_TRUE */
          LblDetErrFlag = LIN_TRUE;
          #endif /* #if (LIN_DEV_ERROR_DETECT == STD_ON) */
          LucReturnValue = E_NOT_OK;
        } /* else No action required */
      }
    }
  }
  #endif /* #if (LIN_AR_VERSION == LIN_AR_422_VERSION) */

  #if (LIN_DEV_ERROR_DETECT == STD_ON)
  /* Check whether any development error occurred */
  if (LIN_FALSE == LblDetErrFlag)
  #endif /* LIN_DEV_ERROR_DETECT */
  {
    if (E_OK == LucReturnValue)                                                                                         /* PRQA S 2991, 2995 # JV-01, JV-01 */
    {
      /* Get the address of LIN Channel structure */
      LpRamVars = &((Lin_GaaGlobalAccPoint[LucCoreIndex].pChannelRamData)[LucChannelRamIndex]);

      /* Get pointer to data array of upper layer */
      LpSduPtr = PduInfoPtr->SduPtr;

      /* Copy the data length to local variable */
      LucCount = PduInfoPtr->Dl;

      /* Pointing to array aaFrameData of global Ram variable */
      LpDataBufferPtr = &LpRamVars->aaFrameData[(uint32)LIN_ZERO];

      /* Enter the protection area */
      LIN_ENTER_CRITICAL_SECTION(LIN_INTERRUPT_CONTROL_PROTECTION);

      /* Disable RLIN3 Interrupt */
      /* There is a possibility that the EIRF bit will be cleared if an
         interrupt is occured at this mask timing, but it is no problem.
         [SWS_Lin_00021] */
      Lin_HwScheduleInterrupt(Channel, LIN_INTERRUPT_DIS);

      /* Exit the protection area */
      LIN_EXIT_CRITICAL_SECTION(LIN_INTERRUPT_CONTROL_PROTECTION);

      #if (LIN_AR_VERSION == LIN_AR_R22_11_VERSION)
      /* AR21-11 use LIN_FRAMERESPONSE_TX instead of LIN_MASTER_RESPONSE */
      if (LIN_FRAMERESPONSE_TX == PduInfoPtr->Drc)
      #else
      if (LIN_MASTER_RESPONSE == PduInfoPtr->Drc)
      #endif /* #if (LIN_AR_VERSION == LIN_AR_431_VERSION) */
      {
        /* Copy the data bytes to a LIN Driver software buffer */
        do
        {
          /* Copy the data bytes to a LIN Driver software buffer */
          *LpDataBufferPtr = *LpSduPtr;
          LpDataBufferPtr++;                                                                                            /* PRQA S 3387 # JV-01 */
          LpSduPtr++;
          LucCount--;                                                                                                   /* PRQA S 3383 # JV-02 */
        } while (LIN_ZERO != LucCount);
      } /* else No action required */

      /* Call the internal function to start the frame transmission */
      LucReturnValue = Lin_HwSendHeaderInternal(Channel, PduInfoPtr, LIN_SEND_FRAME_SID);
    } /* else No action required */
  } /* else No action required */
  return (LucReturnValue);
}
#define LIN_STOP_SEC_PUBLIC_CODE
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* #if (LIN_MASTER_MODE_SUPPORT == STD_ON) */

/***********************************************************************************************************************
** Function Name        : Lin_GoToSleep
**
** Service ID           : 0x06
**
** Description          : This service instructs the driver to transmit a
**                        go-to-sleep-command on the addressed LIN channel.
**                        Only used for LIN master nodes.
**
** Sync/Async           : Asynchronous
**
** Re-entrancy          : Non-Reentrant
**
** Input Parameters     : Channel
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return parameter     : Std_ReturnType
**
** Preconditions        : The LIN Driver must be initialized. LIN_MASTER_MODE_SUPPORT must be STD_ON
**
** Global Variables     : Lin_GaaGlobalAccPoint,
**                        Lin_GaaGetCoreId2Index (LIN_MULTI_CORE_SUPPORT == STD_ON),
**                        Lin_GaaChannelId2CoreIndex (LIN_MULTI_CORE_SUPPORT == STD_ON)
**
** Functions invoked    : Det_ReportError, Lin_HwSendHeaderInternal
**                        LIN_ENTER_CRITICAL_SECTION, LIN_EXIT_CRITICAL_SECTION,
**                        Lin_HwScheduleInterrupt, GetCoreID (LIN_MULTI_CORE_SUPPORT == STD_ON)
**
** Registers Used       : None
**
** Reference ID         : LIN_DUD_ACT_005, LIN_DUD_ACT_005_ERR001,
** Reference ID         : LIN_DUD_ACT_005_ERR002, LIN_DUD_ACT_005_CRT001,
** Reference ID         : LIN_DUD_ACT_005_CRT002, LIN_DUD_ACT_005_CRT003,
** Reference ID         : LIN_DUD_ACT_005_GBL002, LIN_DUD_ACT_005_GBL003,
** Reference ID         : LIN_DUD_ACT_005_GBL004, LIN_DUD_ACT_005_CRT004,
** Reference ID         : LIN_DUD_ACT_005_GBL001, LIN_DUD_ACT_005_ERR003,
** Reference ID         : LIN_DUD_ACT_005_ERR004, LIN_DUD_ACT_005_ERR005
***********************************************************************************************************************/
/* SWS_Lin_00288 */
#if (LIN_MASTER_MODE_SUPPORT == STD_ON)
#define LIN_START_SEC_PUBLIC_CODE
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, LIN_PUBLIC_CODE) Lin_GoToSleep(uint8 Channel)                                                      /* PRQA S 1503 # JV-01 */
{
  volatile P2VAR(Lin_RamData, AUTOMATIC, LIN_APPL_DATA) LpRamVars;                                                      /* PRQA S 3432 # JV-01 */
  volatile P2VAR(uint8, AUTOMATIC, LIN_APPL_DATA) volatile LpDataBuffer;                                                /* PRQA S 3432 # JV-01 */
  Std_ReturnType LucReturnValue;

  uint8 LucDataCount;
  uint8 LucDataLength;

  #if (LIN_DEV_ERROR_DETECT == STD_ON)
  boolean LblDetErrFlag;
  #endif
  uint8 LucChannelRamIndex;
  uint8 LucCoreIndex;

  #if (LIN_MULTI_CORE_SUPPORT == STD_ON)
  uint8 LucCoreId;
  /* Get Core id for code branching */
  LucCoreId = (uint8)GetCoreID();
  /* Covert Core Id to Core Index */
  LucCoreIndex = Lin_GaaGetCoreId2Index[LucCoreId];
  #else
  /* if Multicore is not configude, defauld coreid is 0x00
     To optimize implementation */
  LucCoreIndex = LIN_ZERO;
  #endif /* #if (LIN_MULTI_CORE_SUPPORT == STD_ON) */

  /* Initialize the return value */
  LucReturnValue = E_NOT_OK;                                                                                            /* PRQA S 2982 # JV-01 */

  #if (LIN_DEV_ERROR_DETECT == STD_ON)
  /* Initialize error status flag to LIN_FALSE */
  LblDetErrFlag = LIN_FALSE;
  /* Check invalid core for API */
  #if (LIN_MULTI_CORE_SUPPORT == STD_ON)
  if(LIN_INVALID_CORE == LucCoreIndex)
  {
    /* Report to DET */
    (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_GO_TO_SLEEP_SID, LIN_E_INVALID_CORE);
    /* Set the error status flag to LIN_TRUE */
    LblDetErrFlag = LIN_TRUE;
  }
  else
  #endif /* #if (LIN_MULTI_CORE_SUPPORT == STD_ON) */
  {
    /* Report to DET, if module is not initialized */
    if (LIN_UNINIT == *(Lin_GaaGlobalAccPoint[LucCoreIndex].pDriverState))
    {
      /* Report to DET */
      (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_GO_TO_SLEEP_SID, LIN_E_UNINIT);

      /* Set the error status flag to LIN_TRUE */
      LblDetErrFlag = LIN_TRUE;
    }
    else
    {
      /* Report to DET, if Channel is out of range */
      if (LIN_MAX_CHANNEL_ID < Channel)
      {
        /* Report to DET */
        (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_GO_TO_SLEEP_SID, LIN_E_INVALID_CHANNEL);

        /* Set the error status flag to LIN_TRUE */
        LblDetErrFlag = LIN_TRUE;
      } /* else No action required */
      else
      {
        /* DET error if invalid call */
        #if (LIN_MULTI_CORE_SUPPORT == STD_ON)
        if (LucCoreIndex!= Lin_GaaChannelId2CoreIndex[Channel])
        {
          (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_GO_TO_SLEEP_SID, LIN_E_INVALID_CORE);
          /* Set the error status flag to LIN_TRUE */
          LblDetErrFlag = LIN_TRUE;
        }
        else
        #endif /* #if (LIN_MULTI_CORE_SUPPORT == STD_ON) */
        {
          #if (LIN_SLAVE_MODE_SUPPORT == STD_ON)
          /* [AR21-11] Support Slave mode: SWS_Lin_00263 Lin_GoToSleep is only applicable for LIN master nodes */
          if (LIN_SLAVE_NODE == (*(Lin_GaaGlobalAccPoint[LucCoreIndex].pChannelConfig))[Channel].enNodeType)
          {
            (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_GO_TO_SLEEP_SID, LIN_E_INVALID_NODE_TYPE);
            /* Set the error status flag to LIN_TRUE */
            LblDetErrFlag = LIN_TRUE;
          } /* else No action required */
          #endif /* (LIN_SLAVE_MODE_SUPPORT == STD_ON) */
        }
      }
    }
  }
  /* Check whether any development error occurred */
  if (LIN_FALSE == LblDetErrFlag)
  #endif /* LIN_DEV_ERROR_DETECT */
  {
    #if (LIN_MULTI_CORE_SUPPORT == STD_ON)
    /* Get Channel Ram Index for each core */
    LucChannelRamIndex = (*(Lin_GaaGlobalAccPoint[LucCoreIndex].pChannelConfig))[Channel].ucChannelRamIndex;
    #else
    /* single core - Channel Ram index = channel id */
    LucChannelRamIndex = Channel;
    #endif /* #if (LIN_MULTI_CORE_SUPPORT == STD_ON) */

    /* Get the address of LIN Channel structure */
    LpRamVars = &((Lin_GaaGlobalAccPoint[LucCoreIndex].pChannelRamData)[LucChannelRamIndex]);

    /* Check if current status is already in LIN_CH_SLEEP_PENDING */
    if (LIN_TRUE == LpRamVars->blSleepPending)
    {
      /* Update the return value */
      LucReturnValue = E_OK;
    }
    else
    {
      /* Enter the protection area */
      LIN_ENTER_CRITICAL_SECTION(LIN_INTERRUPT_CONTROL_PROTECTION);

      /* Disable RLIN3 Interrupt */
      /* There is a possibility that the EIRF bit will be cleared if an
         interrupt is occured at this mask timing, but it is no problem.
         [SWS_Lin_00074] */
      Lin_HwScheduleInterrupt(Channel, LIN_INTERRUPT_DIS);

      /* Exit the protection area */
      LIN_EXIT_CRITICAL_SECTION(LIN_INTERRUPT_CONTROL_PROTECTION);

      LpDataBuffer = &LpRamVars->aaFrameData[(uint32)LIN_ZERO];
      /* Enter the protection area */
      LIN_ENTER_CRITICAL_SECTION(LIN_RAM_DATA_PROTECTION);
      /* Copy the data length to local variable */
      LucDataLength = Lin_GstSleepPdu.Dl;

      *LpDataBuffer = LIN_ZERO;

      /* Copy sleep frame data */
      for (LucDataCount = LIN_ONE; LucDataLength > LucDataCount; LucDataCount++)
      {
        /* Increment the data buffer pointer */
        LpDataBuffer++;                                                                                                 /* PRQA S 3387 # JV-01 */

        /* Copy the sleep frame data */
        *LpDataBuffer = LIN_COPY_SLEEP_FRAME;
      }

      /* Set the Sleep requested bit */
      LpRamVars->ucSlpRqst_RespRdy = LIN_SET_SLEEP_REQUEST;

      /* Change Channel status to Sleep Pending */
      LpRamVars->blSleepPending = LIN_TRUE;

      /* Exit the protection area */
      LIN_EXIT_CRITICAL_SECTION(LIN_RAM_DATA_PROTECTION);

      /* Call the internal function to start the frame transmission */
      LucReturnValue = Lin_HwSendHeaderInternal(Channel, &Lin_GstSleepPdu, LIN_GO_TO_SLEEP_SID);
    }
  } /* if (LblDetErrFlag == LIN_FALSE) */ /* else No action required */

  return (LucReturnValue);
}
#define LIN_STOP_SEC_PUBLIC_CODE
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* #if (LIN_MASTER_MODE_SUPPORT == STD_ON) */

/***********************************************************************************************************************
** Function Name      : Lin_GoToSleepInternal
**
** Service ID         : 0x09
**
** Description        : This is the same function as Lin_GoToSleep () but
**                      without sending a go-to-sleep command on the bus. LIN
**                      channel will enter into the LIN_CH_SLEEP state, enabling
**                      the wake-up detection and optionally sets the LIN
**                      hardware unit to reduced power operation mode(if
**                      supported by hardware).
**
** Sync/Async         : Synchronous
**
** Re-entrancy        : Non Re-entrant
**
** Input Parameters   : Channel
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : Std_ReturnType
**
** Preconditions      : The LIN Driver must be initialized.
**
** Global Variables   : Lin_GaaGlobalAccPoint,
**                      Lin_GaaGetCoreId2Index (LIN_MULTI_CORE_SUPPORT == STD_ON),
**                      Lin_GaaChannelId2CoreIndex (LIN_MULTI_CORE_SUPPORT == STD_ON),
**
** Functions invoked  : Det_ReportError, Lin_HwHandleWakeupRequest,
**                      Lin_HwScheduleInterrupt
**                      LIN_ENTER_CRITICAL_SECTION, LIN_EXIT_CRITICAL_SECTION,
**                      GetCoreID (LIN_MULTI_CORE_SUPPORT == STD_ON)
**
** Registers Used     : None
**
** Reference ID       : LIN_DUD_ACT_006, LIN_DUD_ACT_006_ERR001,
** Reference ID       : LIN_DUD_ACT_006_ERR002, LIN_DUD_ACT_006_CRT001,
** Reference ID       : LIN_DUD_ACT_006_CRT002, LIN_DUD_ACT_006_GBL001,
** Reference ID       : LIN_DUD_ACT_006_GBL002, LIN_DUD_ACT_006_GBL003,
** Reference ID       : LIN_DUD_ACT_006_CRT003, LIN_DUD_ACT_006_CRT004,
** Reference ID       : LIN_DUD_ACT_006_CRT005, LIN_DUD_ACT_006_CRT006,
** Reference ID       : LIN_DUD_ACT_006_GBL004, LIN_DUD_ACT_006_ERR003,
** Reference ID       : LIN_DUD_ACT_006_ERR004
***********************************************************************************************************************/
#define LIN_START_SEC_PUBLIC_CODE
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, LIN_PUBLIC_CODE) Lin_GoToSleepInternal(uint8 Channel)                                              /* PRQA S 1503 # JV-01 */
{
  #if (LIN_WAKEUP_SUPPORT == STD_ON)
  volatile P2CONST(Lin_ChannelInfo, AUTOMATIC, LIN_PRIVATE_CONST) LpLinChannelPtr;
  #endif

  volatile P2VAR(Lin_RamData, AUTOMATIC, LIN_APPL_DATA) LpRamVars;                                                      /* PRQA S 3432 # JV-01 */
  Std_ReturnType LucReturnValue;

  #if (LIN_DEV_ERROR_DETECT == STD_ON)
  boolean LblDetErrFlag;
  #endif /* #if  (LIN_DEV_ERROR_DETECT == STD_ON) */
  uint8 LucChannelRamIndex;
  uint8 LucCoreIndex;

  #if (LIN_MULTI_CORE_SUPPORT == STD_ON)
  uint8 LucCoreId;
  /* Get Core id for code branching */
  LucCoreId = (uint8)GetCoreID();
  /* Covert Core Id to Core Index */
  LucCoreIndex = Lin_GaaGetCoreId2Index[LucCoreId];
  #else
  /* if Multicore is not configude, defauld coreid is 0x00
     To optimize implementation */
  LucCoreIndex = LIN_ZERO;
  #endif /* #if (LIN_MULTI_CORE_SUPPORT == STD_ON) */

  /* Initialize the return value */
  LucReturnValue = E_NOT_OK;                                                                                            /* PRQA S 2982 # JV-01 */

  #if (LIN_DEV_ERROR_DETECT == STD_ON)
  /* Initialize error status flag to LIN_FALSE */
  LblDetErrFlag = LIN_FALSE;

  /* Check invalid core for API */
  #if (LIN_MULTI_CORE_SUPPORT == STD_ON)
  if(LIN_INVALID_CORE == LucCoreIndex)
  {
    /* Report to DET */
    (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_GO_TO_SLEEP_INTERNAL_SID, LIN_E_INVALID_CORE);
    /* Set the error status flag to LIN_TRUE */
    LblDetErrFlag = LIN_TRUE;
  }
  else
  #endif /* #if (LIN_MULTI_CORE_SUPPORT == STD_ON) */
  {
    /* Report to DET, if module is not initialized */
    if (LIN_UNINIT == *(Lin_GaaGlobalAccPoint[LucCoreIndex].pDriverState))
    {
      /* Report to DET */
      (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_GO_TO_SLEEP_INTERNAL_SID, LIN_E_UNINIT);

      /* Set the error status flag to LIN_TRUE */
      LblDetErrFlag = LIN_TRUE;
    }
    else
    {
      /* Report to DET, if Channel is out of range */
      if (LIN_MAX_CHANNEL_ID < Channel)
      {
        /* Report to DET */
        (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_GO_TO_SLEEP_INTERNAL_SID, LIN_E_INVALID_CHANNEL);

        /* Set the error status flag to LIN_TRUE */
        LblDetErrFlag = LIN_TRUE;
      } /* else No action required */
      else
      {
        /* DET error if invalid call for current  core */
        #if (LIN_MULTI_CORE_SUPPORT == STD_ON)
        if (LucCoreIndex!= Lin_GaaChannelId2CoreIndex[Channel])
        {
          (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_GO_TO_SLEEP_INTERNAL_SID, LIN_E_INVALID_CORE);
          /* Set the error status flag to LIN_TRUE */
          LblDetErrFlag = LIN_TRUE;
        } /* else do nothing */
        #endif /* #if (LIN_MULTI_CORE_SUPPORT == STD_ON) */
      }
    }
  }

  /* Check whether any development error occurred */
  if (LIN_FALSE == LblDetErrFlag)
  #endif /* LIN_DEV_ERROR_DETECT */
  {
    #if (LIN_MULTI_CORE_SUPPORT == STD_ON)
    /* Get Channel Ram Index for each core */
    LucChannelRamIndex = (*(Lin_GaaGlobalAccPoint[LucCoreIndex].pChannelConfig))[Channel].ucChannelRamIndex;
    #else
    /* single core - Channel Ram index = channel id */
    LucChannelRamIndex = Channel;
    #endif /* #if (LIN_MULTI_CORE_SUPPORT == STD_ON) */

    /* Get the address of LIN Channel structure */
    LpRamVars = &((Lin_GaaGlobalAccPoint[LucCoreIndex].pChannelRamData)[LucChannelRamIndex]);

    /* Check if current status is already in LIN_CH_SLEEP */
    if ((LIN_CH_SLEEP == LpRamVars->enChannelStatus) && (LIN_FALSE == LpRamVars->blSleepPending))
    {
      /* Update the return value */
      LucReturnValue = E_OK;
    }
    else
    {
      /* Enter the protection area */
      LIN_ENTER_CRITICAL_SECTION(LIN_RAM_DATA_PROTECTION);

      /* Change Channel status to Sleep */
      LpRamVars->enChannelStatus = LIN_CH_SLEEP;

      /* Clear sleep pending status */
      LpRamVars->blSleepPending = LIN_FALSE;

      /* Clear the sleep requested bit */
      LpRamVars->ucSlpRqst_RespRdy = LIN_CLR_SLEEP_REQUEST;

      /* Reset the LinIf wake-up flag */
      LpRamVars->blWakeupCalled = LIN_FALSE;

      /* Exit the protection area */
      LIN_EXIT_CRITICAL_SECTION(LIN_RAM_DATA_PROTECTION);

      /* Check if global wake-up support is enabled */
      #if (LIN_WAKEUP_SUPPORT == STD_ON)
      /* Get the address of LIN Channel structure */
      LpLinChannelPtr = &((*(Lin_GaaGlobalAccPoint[LucCoreIndex].pChannelConfig))[Channel]);

      /* Check if channel specific wake-up support is enabled */
      if (LIN_TRUE == LpLinChannelPtr->blWakeupSupport)
      {
        /* Set RLIN3 to Slave Wake-up */
        LucReturnValue = Lin_HwHandleWakeupRequest(Channel, LIN_SLAVE_ISSUE, LIN_GO_TO_SLEEP_INTERNAL_SID);
      }
      else
      {

        LIN_ENTER_CRITICAL_SECTION(LIN_INTERRUPT_CONTROL_PROTECTION);

        /* Disable RLIN3 Interrupt */
        Lin_HwScheduleInterrupt(Channel, LIN_INTERRUPT_DIS);

        /* Exit the protection area */
        LIN_EXIT_CRITICAL_SECTION(LIN_INTERRUPT_CONTROL_PROTECTION);

        /* Update the return value */
        LucReturnValue = E_OK;
      }
      #else

      /* Enter the protection area */
      LIN_ENTER_CRITICAL_SECTION(LIN_INTERRUPT_CONTROL_PROTECTION);
      /* Disable RLIN3 Interrupt */
      Lin_HwScheduleInterrupt(Channel, LIN_INTERRUPT_DIS);
      /* Exit the protection area */
      LIN_EXIT_CRITICAL_SECTION(LIN_INTERRUPT_CONTROL_PROTECTION);
      /* Update the return value */
      LucReturnValue = E_OK;
      #endif /* #if (LIN_WAKEUP_SUPPORT == STD_ON) */
    }
  } /* No development errors occurred */ /* else No action required */

  return (LucReturnValue);
}
#define LIN_STOP_SEC_PUBLIC_CODE
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name      : Lin_WakeUp
**
** Service ID         : 0x07
**
** Description        : This service instructs the driver to transmit a
**                      wake-up command on the addressed LIN channel.
**
** Sync/Async         : Asynchronous
**
** Re-entrancy        : Non-Reentrant
**
** Input Parameters   : Channel
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : Std_ReturnType
**
** Preconditions      : LIN Driver must be initialized. LIN channel state must be in LIN_CH_SLEEP state.
**
** Global Variables   : Lin_GaaGlobalAccPoint
**                      Lin_GaaGetCoreId2Index(LIN_MULTI_CORE_SUPPORT == STD_ON),
**                      Lin_GaaChannelId2CoreIndex (LIN_MULTI_CORE_SUPPORT == STD_ON),
**
** Functions invoked  : Det_ReportError,
**                      Lin_HwHandleWakeupRequest
**                      LIN_ENTER_CRITICAL_SECTION, LIN_EXIT_CRITICAL_SECTION,
**                      Lin_HwScheduleInterrupt
**                      GetCoreID (LIN_MULTI_CORE_SUPPORT == STD_ON)
**
** Registers Used     : None
**
** Reference ID       : LIN_DUD_ACT_007, LIN_DUD_ACT_007_ERR001,
** Reference ID       : LIN_DUD_ACT_007_ERR002, LIN_DUD_ACT_007_ERR003,
** Reference ID       : LIN_DUD_ACT_007_ERR004, LIN_DUD_ACT_007_CRT001,
** Reference ID       : LIN_DUD_ACT_007_CRT002, LIN_DUD_ACT_007_CRT003,
** Reference ID       : LIN_DUD_ACT_007_GBL001, LIN_DUD_ACT_007_GBL002,
** Reference ID       : LIN_DUD_ACT_007_CRT004, LIN_DUD_ACT_007_ERR005,
** Reference ID       : LIN_DUD_ACT_007_ERR006
***********************************************************************************************************************/
#define LIN_START_SEC_PUBLIC_CODE
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, LIN_PUBLIC_CODE) Lin_Wakeup(uint8 Channel)                                                         /* PRQA S 1503 # JV-01 */
{
  volatile P2VAR(Lin_RamData, AUTOMATIC, LIN_APPL_DATA) LpRamVars;                                                      /* PRQA S 3432 # JV-01 */
  Std_ReturnType LucReturnValue;

  #if (LIN_DEV_ERROR_DETECT == STD_ON)
  Lin_StatusType LenChannelStatus;
  boolean LblDetErrFlag;
  #endif
  uint8 LucChannelRamIndex;
  uint8 LucCoreIndex;

  #if (LIN_MULTI_CORE_SUPPORT == STD_ON)
  uint8 LucCoreId;
  /* Get Core id for code branching */
  LucCoreId = (uint8)GetCoreID();
  /* Covert Core Id to Core Index */
  LucCoreIndex = Lin_GaaGetCoreId2Index[LucCoreId];
  #else
  /* if Multicore is not configude, defauld coreid is 0x00
     To optimize implementation */
  LucCoreIndex = LIN_ZERO;
  #endif /* #if (LIN_MULTI_CORE_SUPPORT == STD_ON) */

  /* Initialize the return value */
  LucReturnValue = E_NOT_OK;                                                                                            /* PRQA S 2982 # JV-01 */

  #if (LIN_DEV_ERROR_DETECT == STD_ON)
  /* Initialize error status flag to LIN_FALSE */
  LblDetErrFlag = LIN_FALSE;

  /* Check invalid core for API */
  #if (LIN_MULTI_CORE_SUPPORT == STD_ON)
  if(LIN_INVALID_CORE == LucCoreIndex)
  {
    /* Report to DET */
    (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_WAKEUP_SID, LIN_E_INVALID_CORE);
    /* Set the error status flag to LIN_TRUE */
    LblDetErrFlag = LIN_TRUE;
  }
  else
  #endif /* #if (LIN_MULTI_CORE_SUPPORT == STD_ON) */
  {
    /* Report to DET, if module is not Initialized */
    if (LIN_UNINIT == *(Lin_GaaGlobalAccPoint[LucCoreIndex].pDriverState))
    {
      /* Report to DET */
      (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_WAKEUP_SID, LIN_E_UNINIT);

      /* Set the error status flag to LIN_TRUE */
      LblDetErrFlag = LIN_TRUE;
    }
    else
    {
      /* Report to DET, if Channel is out of range */
      if (LIN_MAX_CHANNEL_ID < Channel)
      {
        /* Report to DET */
        (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_WAKEUP_SID, LIN_E_INVALID_CHANNEL);

        /* Set the error status flag to LIN_TRUE */
        LblDetErrFlag = LIN_TRUE;
      }
      else
      {
        /* DET error if invalid call for current  core */
        #if (LIN_MULTI_CORE_SUPPORT == STD_ON)
        if (LucCoreIndex!= Lin_GaaChannelId2CoreIndex[Channel])
        {
          (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_WAKEUP_SID, LIN_E_INVALID_CORE);
          /* Set the error status flag to LIN_TRUE */
          LblDetErrFlag = LIN_TRUE;
        }
        else
        #endif /* #if (LIN_MULTI_CORE_SUPPORT == STD_ON) */
        {
          #if (LIN_MULTI_CORE_SUPPORT == STD_ON)
          /* Get Channel Ram Index for each core */
          LucChannelRamIndex = (*(Lin_GaaGlobalAccPoint[LucCoreIndex].pChannelConfig))[Channel].ucChannelRamIndex;
          #else
          /* single core - Channel Ram index = channel id */
          LucChannelRamIndex = Channel;
          #endif /* #if (LIN_MULTI_CORE_SUPPORT == STD_ON) */

          /* Get the address of LIN Channel structure */
          LenChannelStatus = (Lin_GaaGlobalAccPoint[LucCoreIndex].pChannelRamData)[LucChannelRamIndex].enChannelStatus;

          if (LIN_CH_SLEEP != LenChannelStatus)
          {
            /* Report to DET */
            (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_WAKEUP_SID, LIN_E_STATE_TRANSITION);

            /* Set the error status flag to LIN_TRUE */
            LblDetErrFlag = LIN_TRUE;
          }
          else
          {
            /* Get the address of LIN Channel structure */
            if(LIN_TRUE == (Lin_GaaGlobalAccPoint[LucCoreIndex].pChannelRamData)[LucChannelRamIndex].blWakeupCalled)
            {
              /* Report to DET */
              (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_WAKEUP_SID, LIN_E_STATE_TRANSITION);

              /* Set the error status flag to LIN_TRUE */
              LblDetErrFlag = LIN_TRUE;
            } /* else No action required */
          }
        }
      }
    }
  }

  /* Check whether any development error occurred */
  if (LIN_FALSE == LblDetErrFlag)
  #endif /* LIN_DEV_ERROR_DETECT */
  {
    #if (LIN_DEV_ERROR_DETECT == STD_OFF)
    #if (LIN_MULTI_CORE_SUPPORT == STD_ON)
    /* Get Channel Ram Index for each core */
    LucChannelRamIndex = (*(Lin_GaaGlobalAccPoint[LucCoreIndex].pChannelConfig))[Channel].ucChannelRamIndex;
    #else
    /* single core - Channel Ram index = channel id */
    LucChannelRamIndex = Channel;
    #endif /* #if (LIN_MULTI_CORE_SUPPORT == STD_ON) */
    #endif /* #if (LIN_DEV_ERROR_DETECT == STD_OFF) */

    /* Enter the protection area */
    LIN_ENTER_CRITICAL_SECTION(LIN_INTERRUPT_CONTROL_PROTECTION);

    /* Disable RLIN3 Interrupt */
    Lin_HwScheduleInterrupt(Channel, LIN_INTERRUPT_DIS);

    /* Exit the protection area */
    LIN_EXIT_CRITICAL_SECTION(LIN_INTERRUPT_CONTROL_PROTECTION);

    /* Enter the protection area */
    LIN_ENTER_CRITICAL_SECTION(LIN_RAM_DATA_PROTECTION);

    /* Get the address of LIN Channel structure */
    LpRamVars = &((Lin_GaaGlobalAccPoint[LucCoreIndex].pChannelRamData)[LucChannelRamIndex]);

    /* Clear the sleep requested bit */
    LpRamVars->ucSlpRqst_RespRdy = LIN_CLR_SLEEP_REQUEST;

    /* Set the LinIf wake-up flag */
    LpRamVars->blWakeupCalled = LIN_TRUE;

    /* Exit the protection area */
    LIN_EXIT_CRITICAL_SECTION(LIN_RAM_DATA_PROTECTION);

    /* Set RLIN3 to Slave Wake-up */
    LucReturnValue = Lin_HwHandleWakeupRequest(Channel, LIN_MASTER_ISSUE, LIN_WAKEUP_SID);

    if (E_NOT_OK == LucReturnValue)
    {
      /* Clear wake-up flag after a wake-up command to the LIN bus failed */
      LpRamVars->blWakeupCalled = LIN_FALSE;
    }  /* else No action required */

  } /* if (LblDetErrFlag == LIN_FALSE) */ /* else No action required */
  return (LucReturnValue);
}
#define LIN_STOP_SEC_PUBLIC_CODE
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name      : Lin_WakeupInternal
**
** Service ID         : 0x0b
**
** Description        : This is the same function as Lin_Wakeup () but
**                      without sending a wake-up command on the bus. LIN
**                      channel will enter into the LIN_OPERATIONAL state.
**
** Sync/Async         : Asynchronous
**
** Re-entrancy        : Non-Reentrant
**
** Input Parameters   : Channel
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : Std_ReturnType
**
** Preconditions      : LIN Driver must be initialized. LIN channel state must be in LIN_CH_SLEEP state.
**
** Global Variables   : Lin_GaaGlobalAccPoint
**                      Lin_GaaGetCoreId2Index (LIN_MULTI_CORE_SUPPORT == STD_ON),
**                      Lin_GaaChannelId2CoreIndex (LIN_MULTI_CORE_SUPPORT == STD_ON),
**
** Functions invoked  : Det_ReportError, Lin_HwSetMasterMode, Lin_HwScheduleInterrupt
**                      LIN_ENTER_CRITICAL_SECTION, LIN_EXIT_CRITICAL_SECTION
**                      Lin_HwSlaveStartHeaderReception, GetCoreID (LIN_MULTI_CORE_SUPPORT == STD_ON),
**                      Lin_ErrorReport
**
** Registers Used     : None
**
** Reference ID       : LIN_DUD_ACT_008, LIN_DUD_ACT_008_ERR001, LIN_DUD_ACT_008_CRT003, LIN_DUD_ACT_008_CRT004,
** Reference ID       : LIN_DUD_ACT_008_ERR002, LIN_DUD_ACT_008_ERR003,
** Reference ID       : LIN_DUD_ACT_008_ERR004, LIN_DUD_ACT_008_CRT001,
** Reference ID       : LIN_DUD_ACT_008_GBL001, LIN_DUD_ACT_008_GBL002,
** Reference ID       : LIN_DUD_ACT_008_CRT002, LIN_DUD_ACT_008_CRT005
** Reference ID       : LIN_DUD_ACT_008_CRT006, LIN_DUD_ACT_008_ERR005,
** Reference ID       : LIN_DUD_ACT_008_ERR006
***********************************************************************************************************************/
#define LIN_START_SEC_PUBLIC_CODE
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, LIN_PUBLIC_CODE) Lin_WakeupInternal(uint8 Channel)                                                 /* PRQA S 1503 # JV-01 */
{
  volatile P2VAR(Lin_RamData, AUTOMATIC, LIN_APPL_DATA) LpRamVars;                                                      /* PRQA S 3432 # JV-01 */
  Std_ReturnType LucReturnValue;

  #if (LIN_DEV_ERROR_DETECT == STD_ON)
  Lin_StatusType LenChannelStatus;
  boolean LblDetErrFlag;
  #endif
  uint8 LucChannelRamIndex;
  uint8 LucCoreIndex;

  #if (LIN_MULTI_CORE_SUPPORT == STD_ON)
  uint8 LucCoreId;
  /* Get Core id for code branching */
  LucCoreId = (uint8)GetCoreID();
  /* Covert Core Id to Core Index */
  LucCoreIndex = Lin_GaaGetCoreId2Index[LucCoreId];
  #else
  /* if Multicore is not configude, defauld coreid is 0x00
     To optimize implementation */
  LucCoreIndex = LIN_ZERO;
  #endif /* #if (LIN_MULTI_CORE_SUPPORT == STD_ON) */

  /* Initialize the return value */
  LucReturnValue = E_NOT_OK;                                                                                            /* PRQA S 2982 # JV-01 */

  #if (LIN_DEV_ERROR_DETECT == STD_ON)
  /* Initialize error status flag to LIN_FALSE */
  LblDetErrFlag = LIN_FALSE;
  /* Check invalid core for API */
  #if (LIN_MULTI_CORE_SUPPORT == STD_ON)
  if(LIN_INVALID_CORE == LucCoreIndex)
  {
    /* Report to DET */
    (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_WAKEUP_INTERNAL_SID, LIN_E_INVALID_CORE);
    /* Set the error status flag to LIN_TRUE */
    LblDetErrFlag = LIN_TRUE;
  }
  else
  #endif /* #if (LIN_MULTI_CORE_SUPPORT == STD_ON) */
  {
    /* Report to DET, if module is not Initialized */
    if (LIN_UNINIT == *(Lin_GaaGlobalAccPoint[LucCoreIndex].pDriverState))
    {
      /* Report to DET */
      (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_WAKEUP_INTERNAL_SID, LIN_E_UNINIT);

      /* Set the error status flag to LIN_TRUE */
      LblDetErrFlag = LIN_TRUE;
    }
    else
    {
      /* Report to DET, if Channel is out of range */
      if (LIN_MAX_CHANNEL_ID < Channel)
      {
        /* Report to DET */
        (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_WAKEUP_INTERNAL_SID, LIN_E_INVALID_CHANNEL);

        /* Set the error status flag to LIN_TRUE */
        LblDetErrFlag = LIN_TRUE;
      }
      else
      {
        /* DET error if invalid call */
        #if (LIN_MULTI_CORE_SUPPORT == STD_ON)
        if (LucCoreIndex!= Lin_GaaChannelId2CoreIndex[Channel])
        {
          (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_WAKEUP_INTERNAL_SID, LIN_E_INVALID_CORE);
          /* Set the error status flag to LIN_TRUE */
          LblDetErrFlag = LIN_TRUE;
        }
        else
        #endif /* #if (LIN_MULTI_CORE_SUPPORT == STD_ON) */
        {
          #if (LIN_MULTI_CORE_SUPPORT == STD_ON)
          /* Get Channel Ram Index for each core */
          LucChannelRamIndex = (*(Lin_GaaGlobalAccPoint[LucCoreIndex].pChannelConfig))[Channel].ucChannelRamIndex;
          #else
          /* single core - Channel Ram index = channel id */
          LucChannelRamIndex = Channel;
          #endif /* #if (LIN_MULTI_CORE_SUPPORT == STD_ON) */

          /* Get the address of LIN Channel structure */
          LenChannelStatus = (Lin_GaaGlobalAccPoint[LucCoreIndex].pChannelRamData)[LucChannelRamIndex].enChannelStatus;

          if (LIN_CH_SLEEP != LenChannelStatus)
          {
            /* Report to DET */
            (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_WAKEUP_INTERNAL_SID, LIN_E_STATE_TRANSITION);
            /* Set the error status flag to LIN_TRUE */
            LblDetErrFlag = LIN_TRUE;
          }
          else
          {
            /* Get the address of LIN Channel structure */
            if (LIN_TRUE == (Lin_GaaGlobalAccPoint[LucCoreIndex].pChannelRamData)[LucChannelRamIndex].blWakeupCalled)
            {
              /* Report to DET */
              (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_WAKEUP_INTERNAL_SID, LIN_E_STATE_TRANSITION);
              /* Set the error status flag to LIN_TRUE */
              LblDetErrFlag = LIN_TRUE;
            } /* else No action required */
          }
        }
      }
    }
  }

  /* Check whether any development error occurred */
  if (LIN_FALSE == LblDetErrFlag)
  #endif /* LIN_DEV_ERROR_DETECT */
  {
    #if (LIN_DEV_ERROR_DETECT == STD_OFF)
    #if (LIN_MULTI_CORE_SUPPORT == STD_ON)
    /* Get Channel Ram Index for each core */
    LucChannelRamIndex = (*(Lin_GaaGlobalAccPoint[LucCoreIndex].pChannelConfig))[Channel].ucChannelRamIndex;
    #else
    /* single core - Channel Ram index = channel id */
    LucChannelRamIndex = Channel;
    #endif /* #if (LIN_MULTI_CORE_SUPPORT == STD_ON) */
    #endif /* #if (LIN_DEV_ERROR_DETECT == STD_ON) */

    /* Enter the protection area */
    LIN_ENTER_CRITICAL_SECTION(LIN_INTERRUPT_CONTROL_PROTECTION);

    /* Set RLIN3 to Reset Mode */
    LucReturnValue = Lin_HwSetMasterMode(Channel, RLIN3_RESET_MODE);

    if (E_OK == LucReturnValue)
    {
      /* Set RLIN3 to Operation Mode */
      LucReturnValue = Lin_HwSetMasterMode(Channel, RLIN3_OPERATION_MODE);
    }

      /* Exit the protection area */
      LIN_EXIT_CRITICAL_SECTION(LIN_INTERRUPT_CONTROL_PROTECTION);

    if (E_OK == LucReturnValue)
    {
      /* Enter the protection area */
      LIN_ENTER_CRITICAL_SECTION(LIN_RAM_DATA_PROTECTION);

      /* Get the pointer to channel RAM data */
      LpRamVars = &((Lin_GaaGlobalAccPoint[LucCoreIndex].pChannelRamData)[LucChannelRamIndex]);

      /* Set the channel status */
      LpRamVars->enChannelStatus = LIN_OPERATIONAL;

      /* Clear the sleep requested bit */
      LpRamVars->ucSlpRqst_RespRdy = LIN_CLR_SLEEP_REQUEST;

      /* Exit the protection area */
      LIN_EXIT_CRITICAL_SECTION(LIN_RAM_DATA_PROTECTION);

      #if (LIN_SLAVE_MODE_SUPPORT == STD_ON)
      if (LIN_SLAVE_NODE == (*(Lin_GaaGlobalAccPoint[LucCoreIndex].pChannelConfig))[Channel].enNodeType)
      {
        /* SWS_Lin_00272
        The LIN driver shall be able to receive a LIN header at any time in LIN_CH_OPERATIONAL state */
        Lin_HwSlaveStartHeaderReception(Channel);
      }
      else
      #endif /* (LIN_SLAVE_MODE_SUPPORT == STD_ON) */
      {
        #if (LIN_MASTER_MODE_SUPPORT == STD_ON)
        /* Enter the protection area */
        LIN_ENTER_CRITICAL_SECTION(LIN_INTERRUPT_CONTROL_PROTECTION);

        /* Disable RLIN3 Interrupt */
        Lin_HwScheduleInterrupt(Channel, LIN_INTERRUPT_DIS);

        /* Exit the protection area */
        LIN_EXIT_CRITICAL_SECTION(LIN_INTERRUPT_CONTROL_PROTECTION);
        #endif /* if (LIN_MASTER_MODE_SUPPORT == STD_ON) */
      }
    } /* else No action required */
    else
    {
      #if defined(LIN_E_TIMEOUT) || (LIN_DEV_ERROR_DETECT == STD_ON)
      /* Report Error to DEM or DET */
      LucReturnValue = Lin_ErrorReport(LIN_WAKEUP_INTERNAL_SID);
      #endif /* #if defined(LIN_E_TIMEOUT) || (LIN_DEV_ERROR_DETECT == STD_ON) */
    }

  } /* if (LblDetErrFlag == LIN_FALSE) */ /* else No action required */
  return (LucReturnValue);
}
#define LIN_STOP_SEC_PUBLIC_CODE
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name      : Lin_GetStatus
**
** Service ID         : 0x08
**
** Description        : Indicates the current transmission, reception or
**                      operation status of the LIN driver.
**                      Only used for LIN master nodes.
**
** Sync/Async         : Synchronous
**
** Re-entrancy        : Non-Reentrant
**
** Input Parameters   : Channel
**
** InOut Parameters   : None
**
** Output Parameters  : Lin_SduPtr
**
** Return parameter   : Lin_StatusType
**
** Preconditions      : The LIN Driver must be initialized. LIN_MASTER_MODE_SUPPORT must be STD_ON
**
** Global Variables   : Lin_GaaGlobalAccPoint,
**                      Lin_GaaGetCoreId2Index (LIN_MULTI_CORE_SUPPORT == STD_ON),
**                      Lin_GaaChannelId2CoreIndex (LIN_MULTI_CORE_SUPPORT == STD_ON)
**
** Functions invoked  : Det_ReportError
**                      LIN_ENTER_CRITICAL_SECTION, LIN_EXIT_CRITICAL_SECTION
**                      GetCoreID (LIN_MULTI_CORE_SUPPORT == STD_ON)
**
** Registers Used     : None
**
** Reference ID       : LIN_DUD_ACT_009, LIN_DUD_ACT_009_ERR001,
** Reference ID       : LIN_DUD_ACT_009_ERR002, LIN_DUD_ACT_009_ERR003,
** Reference ID       : LIN_DUD_ACT_009_ERR004, LIN_DUD_ACT_009_ERR005,
** Reference ID       : LIN_DUD_ACT_009_CRT001, LIN_DUD_ACT_009_GBL001,
** Reference ID       : LIN_DUD_ACT_009_CRT002, LIN_DUD_ACT_009_GBL002,
** Reference ID       : LIN_DUD_ACT_009_GBL003, LIN_DUD_ACT_009_ERR006,
** Reference ID       : LIN_DUD_ACT_009_ERR007, LIN_DUD_ACT_009_ERR008,
** Reference ID       : LIN_DUD_ACT_009_ERR009
***********************************************************************************************************************/
/* SWS_Lin_00289 */
#if (LIN_MASTER_MODE_SUPPORT == STD_ON)
#define LIN_START_SEC_PUBLIC_CODE
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#if (LIN_AR_VERSION == LIN_AR_R22_11_VERSION)
FUNC(Lin_StatusType, LIN_PUBLIC_CODE)
Lin_GetStatus(uint8 Channel, P2CONST(P2VAR(uint8, AUTOMATIC, LIN_APPL_CONST), AUTOMATIC, LIN_APPL_CONST) Lin_SduPtr)    /* PRQA S 1503, 3432 # JV-01, JV-01 */
#else
FUNC(Lin_StatusType, LIN_PUBLIC_CODE)
Lin_GetStatus(uint8 Channel, P2VAR(P2VAR(uint8, AUTOMATIC, LIN_APPL_DATA), AUTOMATIC, LIN_APPL_DATA) Lin_SduPtr)
#endif /* (LIN_AR_VERSION == LIN_AR_R22_11_VERSION) */
{
  volatile P2VAR(Lin_RamData, AUTOMATIC, LIN_APPL_DATA) LpRamVars;                                                      /* PRQA S 3432 # JV-01 */

  #if (LIN_DEV_ERROR_DETECT == STD_ON)
  boolean LblDetErrFlag;
  #endif

  boolean LblSleepPending;
  Lin_StatusType LenReturnValue;
  uint8 LucChannelRamIndex;
  uint8 LucCoreIndex;

  #if (LIN_DEV_ERROR_DETECT == STD_ON)
  #if (LIN_AR_VERSION == LIN_AR_R22_11_VERSION)
  P2CONST(P2VAR(uint8, AUTOMATIC, LIN_APPL_DATA), AUTOMATIC, LIN_APPL_CONST) LpLinSduPtr;                               /* PRQA S 3432, 3678 # JV-01, JV-01 */
  #else
  P2VAR(P2VAR(uint8, AUTOMATIC, LIN_APPL_DATA), AUTOMATIC, LIN_APPL_DATA) LpLinSduPtr;
  #endif
  #elif (LIN_DEV_ERROR_DETECT == STD_OFF) && ((LIN_AR_VERSION == LIN_AR_431_VERSION))
  P2VAR(P2VAR(uint8, AUTOMATIC, LIN_APPL_DATA), AUTOMATIC, LIN_APPL_DATA) LpLinSduPtr;
  #elif (LIN_DEV_ERROR_DETECT == STD_OFF) && ((LIN_AR_VERSION == LIN_AR_R22_11_VERSION))
  P2CONST(P2VAR(uint8, AUTOMATIC, LIN_APPL_DATA), AUTOMATIC, LIN_APPL_CONST) LpLinSduPtr;                               /* PRQA S 3432, 3678 # JV-01, JV-01 */
  #endif

  #if (LIN_MULTI_CORE_SUPPORT == STD_ON)
  uint8 LucCoreId;
  /* Get Core id for code branching */
  LucCoreId = (uint8)GetCoreID();
  /* Covert Core Id to Core Index */
  LucCoreIndex = Lin_GaaGetCoreId2Index[LucCoreId];
  #else
  /* if Multicore is not configude, defauld coreid is 0x00
     To optimize implementation */
  LucCoreIndex = LIN_ZERO;
  #endif /* #if (LIN_MULTI_CORE_SUPPORT == STD_ON) */

  #if (LIN_DEV_ERROR_DETECT == STD_ON)
  /* Initialize error status flag to LIN_FALSE */
  LblDetErrFlag = LIN_FALSE;
  #endif /* #if (LIN_DEV_ERROR_DETECT == STD_ON) */

  #if (LIN_AR_VERSION == LIN_AR_422_VERSION)
  /* Initialize the return value */
  LenReturnValue = LIN_NOT_OK;
  #elif ((LIN_AR_VERSION == LIN_AR_431_VERSION) || (LIN_AR_VERSION == LIN_AR_R22_11_VERSION))
  /* Initialize the return value */
  LenReturnValue = LIN_CH_SLEEP;                                                                                        /* PRQA S 2982 # JV-01 */
  #endif /* #if (LIN_AR_VERSION == LIN_AR_422_VERSION) */

  #if (LIN_AR_VERSION == LIN_AR_422_VERSION)
  #if (LIN_DEV_ERROR_DETECT == STD_ON)
  /* Report to DET, if module is not initialized */
  if (LIN_UNINIT == *(Lin_GaaGlobalAccPoint[LucCoreIndex].pDriverState))
  {
    /* Report to DET */
    (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_GET_STATUS_SID, LIN_E_UNINIT);

    /* Set the error status flag to LIN_TRUE */
    LblDetErrFlag = LIN_TRUE;
  }
  else
  {
    /* Report to DET, if Channel is out of range */
    if (LIN_MAX_CHANNEL_ID < Channel)
    {
      /* Report to DET */
      (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_GET_STATUS_SID, LIN_E_INVALID_CHANNEL);

      /* Set the error status flag to LIN_TRUE */
      LblDetErrFlag = LIN_TRUE;
    } /* else No action required */

    /* Get the pointer to data buffer */
    LpLinSduPtr = Lin_SduPtr;

    /* Report to DET if Lin_SduPtr pointer is a NULL pointer */
    if (NULL_PTR == LpLinSduPtr)
    {
      /* Report to DET */
      (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_GET_STATUS_SID, LIN_E_PARAM_POINTER);

      /* Set the error status flag to LIN_TRUE */
      LblDetErrFlag = LIN_TRUE;
    } /* else No action required */
  }
  #endif /* if (LIN_DEV_ERROR_DETECT == STD_ON) */
  #elif ((LIN_AR_VERSION == LIN_AR_431_VERSION) || (LIN_AR_VERSION == LIN_AR_R22_11_VERSION))
  /* Check invalid core for API */
  #if (LIN_MULTI_CORE_SUPPORT == STD_ON)
  if(LIN_INVALID_CORE == LucCoreIndex)
  {
    #if (LIN_DEV_ERROR_DETECT == STD_ON)
    /* Report to DET */
    (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_GET_STATUS_SID, LIN_E_INVALID_CORE);
    /* Set the error status flag to LIN_TRUE */
    LblDetErrFlag = LIN_TRUE;
    #endif /* #if (LIN_DEV_ERROR_DETECT == STD_ON) */
    /* Set the error status flag to LIN_TRUE */
    LenReturnValue = LIN_NOT_OK;
  }
  else
  #endif /* #if (LIN_MULTI_CORE_SUPPORT == STD_ON) */
  {
    if (LIN_UNINIT == *(Lin_GaaGlobalAccPoint[LucCoreIndex].pDriverState))
    {
      #if (LIN_DEV_ERROR_DETECT == STD_ON)
      /* Report to DET, if module is not initialized */
      /* Report to DET */
      (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_GET_STATUS_SID, LIN_E_UNINIT);

      /* Set the error status flag to LIN_TRUE */
      LblDetErrFlag = LIN_TRUE;
      #endif /* #if (LIN_DEV_ERROR_DETECT == STD_ON) */
      LenReturnValue = LIN_NOT_OK;
    }
    else
    {
      /* Report to DET, if Channel is out of range */
      if (LIN_MAX_CHANNEL_ID < Channel)
      {
        #if (LIN_DEV_ERROR_DETECT == STD_ON)
        /* Report to DET */
        (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_GET_STATUS_SID, LIN_E_INVALID_CHANNEL);

        /* Set the error status flag to LIN_TRUE */
        LblDetErrFlag = LIN_TRUE;
        #endif /* #if (LIN_DEV_ERROR_DETECT == STD_ON) */
        LenReturnValue = LIN_NOT_OK;
      }
      else
      {
        /* DET error if invalid call */
        #if (LIN_MULTI_CORE_SUPPORT == STD_ON)
        if (LucCoreIndex!= Lin_GaaChannelId2CoreIndex[Channel])
        {
          #if (LIN_DEV_ERROR_DETECT == STD_ON)
          (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_GET_STATUS_SID, LIN_E_INVALID_CORE);
          /* Set the error status flag to LIN_TRUE */
          LblDetErrFlag = LIN_TRUE;
          #endif
          /* Return E_NOT_OK if error occurs */
          LenReturnValue = LIN_NOT_OK;
        }
        else
        #endif /* #if (LIN_MULTI_CORE_SUPPORT == STD_ON) */
        {
          #if (LIN_SLAVE_MODE_SUPPORT == STD_ON)
          /* [AR21-11] Support Slave mode: SWS_Lin_00264 Lin_GetStatus is only applicable for LIN master nodes */
          if (LIN_SLAVE_NODE == (*(Lin_GaaGlobalAccPoint[LucCoreIndex].pChannelConfig))[Channel].enNodeType)
          {
            #if (LIN_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_GET_STATUS_SID, LIN_E_INVALID_NODE_TYPE);
            /* Set the error status flag to LIN_TRUE */
            LblDetErrFlag = LIN_TRUE;
            #endif /* #if (LIN_DEV_ERROR_DETECT == STD_ON) */
            LenReturnValue = LIN_NOT_OK;
          } /* else No action required */
          #endif /* (LIN_SLAVE_MODE_SUPPORT == STD_ON) */
        }
      }

      /* Get the pointer to data buffer */
      LpLinSduPtr = Lin_SduPtr;

      /* Report to DET if Lin_SduPtr pointer is a NULL pointer */
      if (NULL_PTR == LpLinSduPtr)
      {
        #if (LIN_DEV_ERROR_DETECT == STD_ON)
        /* Report to DET */
        (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_GET_STATUS_SID, LIN_E_PARAM_POINTER);

        /* Set the error status flag to LIN_TRUE */
        LblDetErrFlag = LIN_TRUE;
        #endif /* #if (LIN_DEV_ERROR_DETECT == STD_ON) */
        LenReturnValue = LIN_NOT_OK;
      } /* else No action required */
    }
  }
  #endif /* #if (LIN_AR_VERSION == LIN_AR_422_VERSION) */

  #if (LIN_DEV_ERROR_DETECT == STD_ON)
  /* Check whether any development error occurred */
  if (LIN_FALSE == LblDetErrFlag)
  #elif (LIN_DEV_ERROR_DETECT == STD_OFF)
  #if ((LIN_AR_VERSION == LIN_AR_431_VERSION) || (LIN_AR_VERSION == LIN_AR_R22_11_VERSION))
  if (LIN_NOT_OK != LenReturnValue)
  #endif /* #if ((LIN_AR_VERSION == LIN_AR_431_VERSION) || (LIN_AR_VERSION == LIN_AR_R22_11_VERSION)) */
  #endif /* #if (LIN_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (LIN_MULTI_CORE_SUPPORT == STD_ON)
    /* Get Channel Ram Index for each core */
    LucChannelRamIndex = (*(Lin_GaaGlobalAccPoint[LucCoreIndex].pChannelConfig))[Channel].ucChannelRamIndex;
    #else
    /* single core - Channel Ram index = channel id */
    LucChannelRamIndex = Channel;
    #endif /* #if (LIN_MULTI_CORE_SUPPORT == STD_ON) */

    /* Get the pointer to channel RAM data */
    LpRamVars = &((Lin_GaaGlobalAccPoint[LucCoreIndex].pChannelRamData)[LucChannelRamIndex]);

    /* Enter the protection area */
    LIN_ENTER_CRITICAL_SECTION(LIN_RAM_DATA_PROTECTION);

    /* Update the return value of the requested channel */
    LenReturnValue = LpRamVars->enChannelStatus;

    /* Get current sleep pending status */
    LblSleepPending = LpRamVars->blSleepPending;

    /* When Lin_GetStatus is called, the LIN driver shall directly enter the LIN_CH_SLEEP state */
    if (LIN_TRUE == LblSleepPending)
    {

      /* Change Channel status to Sleep */
      LpRamVars->enChannelStatus = LIN_CH_SLEEP;

      /* Clear sleep pending status */
      LpRamVars->blSleepPending = LIN_FALSE;

      LenReturnValue = LIN_CH_SLEEP;
    } /* else No action required */

    /* Check if the reception is successful */
    if (LIN_RX_OK == LenReturnValue)
    {
      *Lin_SduPtr = (uint8 *)&(LpRamVars->aaFrameData[(uint32)LIN_ZERO]);                                               /* PRQA S 0312 # JV-01 */
    } /* else No action required */

    /* Exit the protection area */
    LIN_EXIT_CRITICAL_SECTION(LIN_RAM_DATA_PROTECTION);
  } /* No DET errors occurred */
  return (LenReturnValue);
}

#define LIN_STOP_SEC_PUBLIC_CODE
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* #if (LIN_MASTER_MODE_SUPPORT == STD_ON) */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
