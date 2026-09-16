/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2X MCAL Components                                                                 */
/* Module       = Ocu.c                                                                                               */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2023-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains API function implementations of OCU Driver                                                      */
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
 *  1.4.0  30/05/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.01
 *  1.3.1  31/03/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 and RH850/U2Bx-E MCAL Ver22.00.02 Release
 *  1.3.0  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 *  1.2.0  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 *  1.1.1  30/08/2024  : As part of Multi Variant support, following changes are made:
 *                       1. Using global Ocu_GblCountingDirection instead of macro Ocu_GblCountingDirection,
 *                          Ocu_GulPollingTimes instead of OCU_ASYNCHONOUS_POLLING_TIMES, and Ocu_GucKernelCoreId
 *                          instead of OCU_KERNEL_COREID in APIs                
 *  1.0.1  08/11/2023  : Update function Ocu_GetCounter and Ocu_SetAbsoluteThreshold to set initial value for local 
 *                       variable outside DET check
 *         25/10/2023  : Change versioninfo from InOut to Out parameters
 *                       Add comment in Functions invoked: Ocu_HW_Taud_ChannelInit and Ocu_HW_Tauj_ChannelInit in 
 *                       Ocu_Init
 *                       Remove Functions invoked Ocu_GaaHwFunc in Ocu_DeInit, Ocu_StopChannel
 *                       Add comment Functions invoked Det_ReportRuntimeError in Ocu_StartChannel, Ocu_StopChannel,
 *                       Ocu_SetPinState, Ocu_SetPinAction, Ocu_SetAbsoluteThreshold
 *                       Change name of Functions invoked in Ocu_SetAbsoluteThreshold, Ocu_SetRelativeThreshold: 
 *                       from Ocu_HW_Tauj_SetAbsoluteThreshold, Ocu_HW_Taud_SetAbsoluteThreshold and 
 *                       Ocu_HW_Tauj_SetRelativeThreshold, Ocu_HW_Taud_SetRelativeThreshold to 
 *                       Ocu_HW_Tauj_SetThreshold, Ocu_HW_Taud_SetThreshold
 *                       Add new comment in Functions invoked: Ocu_HW_Taud_GetCounter and Ocu_HW_Tauj_GetCounter in
 *                       Ocu_SetAbsoluteThreshold
 *                       Change comment in Preconditions: from NA to None in Ocu_CheckDetErrors
 *         17/10/2023  : QAC message: add new 0404 and delete 2814, 2824, 2844, 2934
 *         04/10/2023  : Change order of calling det error OCU_E_UNINIT first and then OCU_E_INVALID_CORE
 *         25/09/2023  : Update return value for Ocu_SetRelativeThreshold and Ocu_SetAbsoluteThreshold
 *                       cause: Ocu_SetAbsoluteThreshold()/Ocu_SetRelativeThreshold() may return 
 *                       "OCU_CM_IN_REF_INTERVAL" unintentionally at certain timing
 *                       eg:
 *                       Call Ocu_SetAbsoluteThreshold(ChannelNumber, 30, 35) (OcuCountdirection: OCU_UPCOUNTING)
 *                       and current counter = 29)
 *                       before the update: return OCU_CM_IN_REF_INTERVAL
 *                       after the update: return OCU_CM_OUT_REF_INTERVAL
 *  1.0.0  04/04/2023  : Initial Version
 */
/**********************************************************************************************************************/
/***********************************************************************************************************************
**                                             Margin for Control History                                             **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:0316)    : Cast from a pointer to void to a pointer to object type.                                     */
/* Rule                : MISRA C:2012 Rule-11.5, CWE Rule CWE-188, CWE-398, CWE-569                                   */
/* JV-01 Justification : A cast should not be performed between a pointer to object type and a different pointer to   */
/*                       object type.                                                                                 */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (7:0404)    : More than one read access to volatile objects between sequence points.                       */
/* Rule                : MISRA C:2012 Rule-1.3, Rule-13.2, CERTCCM EXP30, EXP10, CWE Rule CWE-682, CWE-758, CWE-737   */
/* JV-01 Justification : This is to get an element in the array of struct, volatile of the counter variable of 'for'  */
/*                       loop is used to ensure no optimization. It is accepted                                       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1503)    : The function '%1s' is defined but is not used within this project.                           */
/* Rule                : MISRA C:2012 Rule-2.1, CERTCCM MSC07, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : This is accepted, due to the module's API is exported for user's usage.                      */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:2004)    : No concluding 'else' exists in this 'if'-'else'-'if' statement.                              */
/* Rule                : MISRA C:2012 Rule-15.7, CERTCCM MSC01, CWE Rule CWE-398, CWE-569                             */
/* JV-01 Justification : The "else" statement with empty content is removed to improve readability.                   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:2982)    : This assignment is redundant. The value of this object is never used before being modified.  */
/* Rule                : MISRA C:2012 Rule-2.2, CERTCCM MSC07, MSC13, CWE Rule CWE-14, CWE-398, CWE-561, CWE-563,     */
/*                       CWE-569, CWE-633                                                                             */
/* JV-01 Justification : The variable needs to be initialized before using it.                                        */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:3383)    : Cannot identify wraparound guard for unsigned arithmetic expression.                         */
/* Rule                : CERTCCM INT30                                                                                */
/* JV-01 Justification : It can still result in values that are out of range for the intended use, as intuitive       */
/*                       "invariants" may not hold                                                                    */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:3384)    : Cannot identify wraparound guard for dependent unsigned arithmetic expression.               */
/* Rule                : CERTCCM INT30                                                                                */
/* JV-01 Justification : In order to effectively guard against overflow and wraparound at all stages, the expression  */
/*                       should be split up into individual dynamic operations, with their own guards where applicable*/
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3387)    : A full expression containing an increment (++) or decrement (--) operator should have no     */
/*                       potential side effects other than that caused by the increment or decrement operator.        */
/* Rule                : MISRA C:2012 Rule-13.3                                                                       */
/* JV-01 Justification : An increment/decrement is created as a side effect. In this case, it's accessing a volatile  */
/*                       object. This can be accepted.                                                                */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3415)    : Right hand operand of '&&' or '||' is an expression with persistent side effects.            */
/* Rule                : MISRA C:2012 Rule-13.5, CERTCCM EXP02, CWE Rule CWE-398, CWE-768, CWE-569                    */
/* JV-01 Justification : Although it is a volatile object, it does not have direct access to the HW register, and     */
/*                       there is no side effect.                                                                     */
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
/* Message (2:3678)    : The object referenced by '%1s' is not modified through it, so '%1s' could be declared with   */
/*                       type '%2s'.                                                                                  */
/* Rule                : MISRA C:2012 Rule-8.13                                                                       */
/* JV-01 Justification : This is accepted. It is just advice for improve safety by reducing the possibility that the  */
/*                       referenced data is unintentionally modified through an unexpected alias and improves         */
/*                       clarity by indicating that the referenced data is not intended to be modified through this   */
/*                       alias or those depending on it                                                               */
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
/* Included for macro definitions (e.g. Service IDs)*/
#include "Ocu.h"
/* Included for Global Data Types */
#include "Ocu_Ram.h"
/* Included for the declaration of Det_ReportError(), Det_ReportRuntimeError()*/
#include "Det.h"
#if (OCU_MULTI_CORE_SUPPORT == STD_ON)
#include "Ocu_Kernel.h"
#include "Os.h"
#endif
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR Release version information */
#define OCU_C_AR_RELEASE_MAJOR_VERSION    OCU_AR_RELEASE_MAJOR_VERSION_VALUE
#define OCU_C_AR_RELEASE_MINOR_VERSION    OCU_AR_RELEASE_MINOR_VERSION_VALUE
#define OCU_C_AR_RELEASE_REVISION_VERSION OCU_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define OCU_C_SW_MAJOR_VERSION            OCU_SW_MAJOR_VERSION_VALUE
#define OCU_C_SW_MINOR_VERSION            OCU_SW_MINOR_VERSION_VALUE
/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (OCU_AR_RELEASE_MAJOR_VERSION != OCU_C_AR_RELEASE_MAJOR_VERSION)
  #error "Ocu.c : Mismatch in Release Major Version"
#endif
#if (OCU_AR_RELEASE_MINOR_VERSION != OCU_C_AR_RELEASE_MINOR_VERSION)
  #error "Ocu.c : Mismatch in Release Minor Version"
#endif
#if (OCU_AR_RELEASE_REVISION_VERSION != OCU_C_AR_RELEASE_REVISION_VERSION)
  #error "Ocu.c : Mismatch in Release Revision Version"
#endif
#if (OCU_SW_MAJOR_VERSION != OCU_C_SW_MAJOR_VERSION)
  #error "Ocu.c : Mismatch in Software Major Version"
#endif
#if (OCU_SW_MINOR_VERSION != OCU_C_SW_MINOR_VERSION)
  #error "Ocu.c : Mismatch in Software Minor Version"
#endif

/**********************************************************************************************************************/

/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/
#define OCU_START_SEC_PRIVATE_CODE
#include "Ocu_MemMap.h"
#if (OCU_DEV_ERROR_DETECT == STD_ON)
STATIC FUNC(Std_ReturnType, OCU_PRIVATE_CODE) Ocu_CheckDetErrors(Ocu_ChannelType LddChannel, uint8 LucApi_SID);
#endif
STATIC FUNC(void, OCU_PRIVATE_CODE) Ocu_SetStatus(boolean LblStatusType);
#define OCU_STOP_SEC_PRIVATE_CODE
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Ocu_GetVersionInfo
**
** Service ID            : 0x09
**
** Description           : This service returns the version information of this module.
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
** Reference ID          : OCU_DUD_ACT_001, OCU_DUD_ACT_001_GBL001, OCU_DUD_ACT_001_ERR001
***********************************************************************************************************************/
#if (OCU_VERSION_INFO_API == STD_ON)
#define OCU_START_SEC_PUBLIC_CODE_GLOBAL
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, OCU_PUBLIC_CODE) Ocu_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, OCU_APPL_DATA) versioninfo)        /* PRQA S 1503, 3432 # JV-01, JV-01 */
{
  #if (OCU_DEV_ERROR_DETECT == STD_ON)
  /* Check if the parameter passed is equal to the Null pointer */
  if (NULL_PTR == versioninfo)
  {
    /* Report to DET */
    (void)Det_ReportError(OCU_MODULE_ID, OCU_INSTANCE_ID, OCU_GET_VERSION_INFO_SID, OCU_E_PARAM_POINTER);
  }
  else
  #endif
  {
    /* Load module version into versioninfo */
    versioninfo->vendorID = (uint16)OCU_VENDOR_ID;
    versioninfo->moduleID = (uint16)OCU_MODULE_ID;
    versioninfo->sw_major_version = (uint8)OCU_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version = (uint8)OCU_SW_MINOR_VERSION;
    versioninfo->sw_patch_version = (uint8)OCU_SW_PATCH_VERSION;
  }
} /* End of API Ocu_GetVersionInfo */
#define OCU_STOP_SEC_PUBLIC_CODE_GLOBAL
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* (OCU_VERSION_INFO_API == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Ocu_Init
**
** Service ID            : 0x00
**
** Description           : Service for OCU initialization.
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non Reentrant
**
** Input Parameters      : ConfigPtr
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variables      : Ocu_GblDriverStatus, Ocu_GpChannelConfig, Ocu_GpChannelRamData, Ocu_GaaHwFunc
**                       : Ocu_GaaStartChannelBuffer, Ocu_GaaSetPinStateBuffer, Ocu_GaaSetPinActionBuffer
**                       : Ocu_GaaSetAbsoluteThresholdBuffer, Ocu_GaaSetRelativeThresholdBuffer
**                       : Ocu_GblCountingDirection, Ocu_GucKernelCoreId, Ocu_GulPollingTimes
**
** Functions invoked     : Ocu_HW_Taud_UnitInit, Ocu_HW_Tauj_UnitInit, Det_ReportError,Ocu_ HW_Tauj_ChannelInit, 
**                         Ocu_HW_Taud_ChannelInit
**
** Registers Used        : None
**
** Reference ID          : OCU_DUD_ACT_002, OCU_DUD_ACT_002_GBL004, OCU_DUD_ACT_002_ERR004
** Reference ID          : OCU_DUD_ACT_002_GBL001, OCU_DUD_ACT_002_GBL002, OCU_DUD_ACT_002_GBL003
** Reference ID          : OCU_DUD_ACT_002_ERR001, OCU_DUD_ACT_002_ERR002, OCU_DUD_ACT_002_ERR003
** Reference ID          : OCU_DUD_ACT_002_GBL005, OCU_DUD_ACT_002_GBL006, OCU_DUD_ACT_002_GBL007
***********************************************************************************************************************/

#define OCU_START_SEC_PUBLIC_CODE_LOCAL
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, OCU_PUBLIC_CODE) Ocu_Init(P2CONST(Ocu_ConfigType, AUTOMATIC, OCU_APPL_CONST) ConfigPtr)                      /* PRQA S 1503 # JV-01 */
{
  /* Index of loop count */
  VAR(volatile uint8, AUTOMATIC) LucCount;
  /* Index of HW IP Type */
  VAR(volatile uint8, AUTOMATIC) LucHWIPType;
  #if (OCU_DEV_ERROR_DETECT == STD_ON)
  /* Declare the variable to store the DET return value */
  VAR(Std_ReturnType, AUTOMATIC) LddDetCheckResult;
  #if (OCU_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = (uint8)GetCoreID();
  #endif
  /* Initialize return value */
  LddDetCheckResult = E_OK;
  /* Check if configure pointer is NULL pointer */
  if (NULL_PTR == ConfigPtr)
  {
    /* Report to DET */
    (void)Det_ReportError(OCU_MODULE_ID, OCU_INSTANCE_ID, OCU_INIT_SID, OCU_E_INIT_FAILED);
    /* Set Return value */
    LddDetCheckResult = E_NOT_OK;
  }
  #if (OCU_ALREADY_INIT_DET_CHECK == STD_ON)
  /* Check if the OCU Driver is already Initialized */
  else if (OCU_INITIALIZED == Ocu_GblDriverStatus)                                                                      /* PRQA S 2004, 3416 # JV-01, JV-01 */
  {
    /* Report to DET */
    (void)Det_ReportError(OCU_MODULE_ID, OCU_INSTANCE_ID, OCU_INIT_SID, OCU_E_ALREADY_INITIALIZED);
    /* Set Return value */
    LddDetCheckResult = E_NOT_OK;
  } /* else No action required */
  #endif
  /* Check if any DET error was reported */
  if (E_OK == LddDetCheckResult)
  #endif /* End of OCU_DEV_ERROR_DETECT == STD_ON */
  {
    /* Check whether the existing database is correct */
    if (OCU_DBTOC_VALUE == ConfigPtr->ulStartOfDbToc)
    {
      #if (OCU_MULTI_CORE_SUPPORT == STD_ON)
      /* Holds the kernel core ID in multicore */
      Ocu_GucKernelCoreId = ConfigPtr->ucKernelCoreId;
      /* Hold the polling times for Ocu_StartChannel and Ocu_SetAbsolute/RelativeThreshold */
      Ocu_GulPollingTimes = ConfigPtr->ulAsynchonousPollingTimes;
      #if (OCU_DEV_ERROR_DETECT == STD_ON)
      /* Check if invoke on kernel core */
      if (Ocu_GucKernelCoreId != LucCoreID)                                                                             /* PRQA S 3416 # JV-01 */
      {
        /* Report Error to DET */
        (void)Det_ReportError(OCU_MODULE_ID, OCU_INSTANCE_ID, OCU_INIT_SID, OCU_E_INVALID_CORE);
      }
      else
      #endif
      #endif
      {
        /* Store the configured counting direction*/
        Ocu_GblCountingDirection = ConfigPtr->blCountingDirection;
        /* Store the global pointer to the first Channel Configuration */
        Ocu_GpChannelConfig = (P2CONST(Ocu_ChannelConfigType, OCU_VAR_INIT, OCU_CONFIG_CONST))                          /* PRQA S 0316 # JV-01 */
                                                                                        ConfigPtr->pChannelConfig;
        /* Store the global pointer to First Channel's Ram data */
        Ocu_GpChannelRamData =
          (P2VAR(Ocu_ChannelRamDataType, OCU_VAR_NO_INIT, OCU_CONFIG_CONST))ConfigPtr->pChannelRamData;                 /* PRQA S 0316, 3432 # JV-01, JV-01 */
        /* Loop for all configured timer IPs then do the unit init */
        for (LucCount = (uint8)OCU_ZERO; LucCount < (uint8)OCU_TOTAL_HW_IP_CONFIG; LucCount++)                          /* PRQA S 3387, 3416 # JV-01, JV-01 */
        {
          /* Read the Timer Type for the given unit */
          LucHWIPType = Ocu_GaaHWIP[LucCount].ucIndex;
          /* Check against null pointer */
          if (NULL_PTR != Ocu_GaaHwFunc[LucHWIPType]->pHWUnitInit)                                                      /* PRQA S 3416 # JV-01 */
          {
            /* Invoke low-level driver for initializing the hardware */
            Ocu_GaaHwFunc[LucHWIPType]->pHWUnitInit(ConfigPtr);
          } /* else No action required */
        }
        /* Loop for all configured timer channels then do the channel init */
        for (LucCount = (uint8)OCU_ZERO; LucCount < (uint8)OCU_TOTAL_CHANNELS_CONFIG; LucCount++)                       /* PRQA S 3387, 3416 # JV-01, JV-01 */
        {
          /* Read the Timer Type for the given channel */
          LucHWIPType = Ocu_GpChannelConfig[LucCount].ucTimerUnitType;                                                  /* PRQA S 0404 # JV-01 */
          /* Check against null pointer */
          if (NULL_PTR != Ocu_GaaHwFunc[LucHWIPType]->pHWChannelInit)                                                   /* PRQA S 3416 # JV-01 */
          {
            /* Invoke low-level driver for initializing the hardware */
            Ocu_GaaHwFunc[LucHWIPType]->pHWChannelInit((Ocu_ChannelType)LucCount);                                      /* PRQA S 0404 # JV-01 */
          } /* else No action required */
          /* Clear all buffer requests */
          #if (OCU_MULTI_CORE_SUPPORT == STD_ON)
          /* Clear buffer request for Ocu_StartChannel and Ocu_StopChannel */
          Ocu_GaaStartChannelBuffer[LucCount].blSetRequest = OCU_FALSE;
          Ocu_GaaStartChannelBuffer[LucCount].blBufferLock = OCU_FALSE;
          Ocu_GaaStopChannelBuffer[LucCount].blSetRequest = OCU_FALSE;
          Ocu_GaaStopChannelBuffer[LucCount].blBufferLock = OCU_FALSE;

          /* Clear buffer request for Ocu_SetPinState */
          #if (OCU_SET_PIN_STATE_API == STD_ON)
          Ocu_GaaSetPinStateBuffer[LucCount].lddPinState = OCU_LOW;
          Ocu_GaaSetPinStateBuffer[LucCount].blSetRequest = OCU_FALSE;
          Ocu_GaaSetPinStateBuffer[LucCount].blBufferLock = OCU_FALSE;
          #endif

          /* Clear buffer request for Ocu_SetPinAction */
          #if (OCU_SET_PIN_ACTION_API == STD_ON)
          Ocu_GaaSetPinActionBuffer[LucCount].lddPinAction = OCU_DISABLE;
          Ocu_GaaSetPinActionBuffer[LucCount].blSetRequest = OCU_FALSE;
          Ocu_GaaSetPinActionBuffer[LucCount].blBufferLock = OCU_FALSE;
          #endif

          /* Clear buffer request for Ocu_SetAbsoluteThreshold */
          #if (OCU_SET_ABSOLUTE_THRESHOLD_API == STD_ON)
          Ocu_GaaSetAbsoluteThresholdBuffer[LucCount].lddSwAbsoluteValue = (uint32)OCU_ZERO;
          Ocu_GaaSetAbsoluteThresholdBuffer[LucCount].blSetRequest = OCU_FALSE;
          Ocu_GaaSetAbsoluteThresholdBuffer[LucCount].blBufferLock = OCU_FALSE;
          Ocu_GaaSetAbsoluteThresholdBuffer[LucCount].lddSwCounterValue = (uint32)OCU_ZERO;
          #endif

          /* Clear buffer request for Ocu_SetRelativeThreshold */
          #if (OCU_SET_RELATIVE_THRESHOLD_API == STD_ON)
          Ocu_GaaSetRelativeThresholdBuffer[LucCount].lddSwRelativeValue = (uint32)OCU_ZERO;
          Ocu_GaaSetRelativeThresholdBuffer[LucCount].blSetRequest = OCU_FALSE;
          Ocu_GaaSetRelativeThresholdBuffer[LucCount].blBufferLock = OCU_FALSE;
          Ocu_GaaSetRelativeThresholdBuffer[LucCount].lddSwCounterValue = (uint32)OCU_ZERO;
          Ocu_GaaSetRelativeThresholdBuffer[LucCount].lddSwReferenceValue = (uint32)OCU_ZERO;
          Ocu_GaaSetRelativeThresholdBuffer[LucCount].lddSwThresholdValue = (uint32)OCU_ZERO;
          #endif
          #endif /* End of OCU_MULTI_CORE_SUPPORT == STD_ON */
        }
      /* Set Driver state to Initialized */
      Ocu_SetStatus(OCU_INITIALIZED);
      } 
    } /* End of ConfigPtr->ulStartOfDbToc) == OCU_DBTOC_VALUE */
    else
    {
      #if (OCU_DEV_ERROR_DETECT == STD_ON)
      /* Report to DET */
      (void)Det_ReportError(OCU_MODULE_ID, OCU_INSTANCE_ID, OCU_INIT_SID, OCU_E_INVALID_DATABASE);
      #endif
    }
  } /* End of LddDetCheckResult == E_OK , no action required for else condition */
} /* End of API Ocu_Init */

#define OCU_STOP_SEC_PUBLIC_CODE_LOCAL
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Ocu_DeInit
**
** Service ID            : 0x01
**
** Description           : This function de-initializes the OCU module.
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : Ocu_Init must be called before this function.
**
** Global Variables      : Ocu_GblDriverStatus, Ocu_GpChannelConfig, Ocu_GaaHwFunc, Ocu_GaaStartChannelBuffer,
**                       : Ocu_GaaSetPinStateBuffer, Ocu_GaaSetPinActionBuffer, Ocu_GaaSetAbsoluteThresholdBuffer,
**                       : Ocu_GaaSetRelativeThresholdBuffer, Ocu_GblDriverStatus, Ocu_GucKernelCoreId,
**                       : Ocu_GblCountingDirection, Ocu_GulPollingTimes
**
** Functions invoked     : Ocu_HW_Taud_ChannelDeInit, Ocu_HW_Tauj_ChannelDeInit, Det_ReportError
**
** Registers Used        : None
**
** Reference ID          : OCU_DUD_ACT_003
** Reference ID          : OCU_DUD_ACT_003_ERR001, OCU_DUD_ACT_003_ERR002, OCU_DUD_ACT_003_ERR003
** Reference ID          : OCU_DUD_ACT_003_GBL001, OCU_DUD_ACT_003_GBL002, OCU_DUD_ACT_003_GBL003
** Reference ID          : OCU_DUD_ACT_003_GBL004, OCU_DUD_ACT_003_GBL005, OCU_DUD_ACT_003_GBL006
***********************************************************************************************************************/
#if (OCU_DE_INIT_API == STD_ON)
#define OCU_START_SEC_PUBLIC_CODE_LOCAL
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, OCU_PUBLIC_CODE) Ocu_DeInit(void)                                                                            /* PRQA S 1503 # JV-01 */
{
  /* Index of loop count */
  VAR(volatile uint8, AUTOMATIC) LucCount;
  /* Index of HW IP Type */
  VAR(volatile uint8, AUTOMATIC) LucHWIPType;
  #if (OCU_DEV_ERROR_DETECT == STD_ON)
  /* Defining a local pointer to point to the Channel Ram Data */
  P2VAR(Ocu_ChannelRamDataType, AUTOMATIC, OCU_VAR_NO_INIT) LpRamData;                                                  /* PRQA S 3432, 3678 # JV-01, JV-01 */
  /* Initialize local variable to first Channel */
  VAR(uint8, AUTOMATIC) LucChannelID;
  /* Declare the variable to store the DET return value */
  VAR(Std_ReturnType, AUTOMATIC) LddDetCheckResult;
  #if (OCU_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = (uint8)GetCoreID();
  #endif
  if (OCU_INITIALIZED != Ocu_GblDriverStatus)                                                                           /* PRQA S 3416 # JV-01 */
  {
    /* Report to DET */
    (void)Det_ReportError(OCU_MODULE_ID, OCU_INSTANCE_ID, OCU_DEINIT_SID, OCU_E_UNINIT);
    /* Set return value */
    LddDetCheckResult = E_NOT_OK;
  }
  else
  {
    /* Initialize return value */
    LddDetCheckResult = E_OK;
    /* Initialize Channel ID */
    LucChannelID = (uint8)OCU_ZERO;
    /* Load the global pointer to the local pointer */
    LpRamData = Ocu_GpChannelRamData;
    /* Check if control API wasn't executed on Master Core */
    #if (OCU_MULTI_CORE_SUPPORT == STD_ON)
    if (Ocu_GucKernelCoreId != LucCoreID)                                                                               /* PRQA S 3416 # JV-01 */
    {
      /* Report Error to DET */
      (void)Det_ReportError(OCU_MODULE_ID, OCU_INSTANCE_ID, OCU_DEINIT_SID, OCU_E_INVALID_CORE);
      LddDetCheckResult = E_NOT_OK;
    } /* else No action required */
    else
    #endif
    {
      do
      {
        /* Check if the Channel is in Running State */
        if (OCU_CH_RUNNING == LpRamData[LucChannelID].blChannelStatus)
        {
          /* Set return value */
          LddDetCheckResult = E_NOT_OK;
        } /* else No action required */
        /* Increment the Channel ID count */
        LucChannelID++;                                                                                                 /* PRQA S 3383 # JV-01 */
      } while (((uint8)OCU_TOTAL_CHANNELS_CONFIG != LucChannelID) && (E_OK == LddDetCheckResult));

      /* Check if the Channel is in Running State */
      if (E_NOT_OK == LddDetCheckResult)
      {
        /* Report to Development Errors */
        (void)Det_ReportError(OCU_MODULE_ID, OCU_INSTANCE_ID, OCU_DEINIT_SID, OCU_E_PARAM_INVALID_STATE);
      } /* else No action required */
    } /* end of (Ocu_GucKernelCoreId != LucCoreID) */
  } /* End of OCU_INITIALIZED != Ocu_GblDriverStatus */
  /* Check if any DET error was reported */
  if (E_OK == LddDetCheckResult)
  #endif /* (OCU_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Reset the configured counting direction */
    Ocu_GblCountingDirection = OCU_UPCOUNTING;
    /* Loop for all configured timer channels then do the channel deinit */
    for (LucCount = (uint8)OCU_ZERO; LucCount < (uint8)OCU_TOTAL_CHANNELS_CONFIG; LucCount++)                           /* PRQA S 3387, 3416 # JV-01, JV-01 */
    {
      /* Read the Timer Type for the given channel */
      LucHWIPType = Ocu_GpChannelConfig[LucCount].ucTimerUnitType;                                                      /* PRQA S 0404 # JV-01 */
      /* Check against null pointer */
      if (NULL_PTR != Ocu_GaaHwFunc[LucHWIPType]->pHWChannelDeInit)                                                     /* PRQA S 3416 # JV-01 */
      {
        /* Invoke low-level driver for De-initializing the hardware */
        Ocu_GaaHwFunc[LucHWIPType]->pHWChannelDeInit((Ocu_ChannelType)LucCount);                                        /* PRQA S 0404 # JV-01 */
      } /* else No action required */

      /* Clear all buffer requests */
      #if (OCU_MULTI_CORE_SUPPORT == STD_ON)
      /* Reset the kernel core ID in multicore */
      Ocu_GucKernelCoreId = OCU_ZERO;
      /* Reset the polling times for Ocu_StartChannel and Ocu_SetAbsolute/RelativeThreshold */
      Ocu_GulPollingTimes = (uint32)OCU_ZERO;
      /* Clear buffer request for Ocu_StartChannel and Ocu_StopChannel */
      Ocu_GaaStartChannelBuffer[LucCount].blSetRequest = OCU_FALSE;
      Ocu_GaaStartChannelBuffer[LucCount].blBufferLock = OCU_FALSE;
      Ocu_GaaStopChannelBuffer[LucCount].blSetRequest = OCU_FALSE;
      Ocu_GaaStopChannelBuffer[LucCount].blBufferLock = OCU_FALSE;

      /* Clear buffer request for Ocu_SetPinState */
      #if (OCU_SET_PIN_STATE_API == STD_ON)
      Ocu_GaaSetPinStateBuffer[LucCount].lddPinState = OCU_LOW;
      Ocu_GaaSetPinStateBuffer[LucCount].blSetRequest = OCU_FALSE;
      Ocu_GaaSetPinStateBuffer[LucCount].blBufferLock = OCU_FALSE;
      #endif

      /* Clear buffer request for Ocu_SetPinAction */
      #if (OCU_SET_PIN_ACTION_API == STD_ON)
      Ocu_GaaSetPinActionBuffer[LucCount].lddPinAction = OCU_DISABLE;
      Ocu_GaaSetPinActionBuffer[LucCount].blSetRequest = OCU_FALSE;
      Ocu_GaaSetPinActionBuffer[LucCount].blBufferLock = OCU_FALSE;
      #endif

      /* Clear buffer request for Ocu_SetAbsoluteThreshold */
      #if (OCU_SET_ABSOLUTE_THRESHOLD_API == STD_ON)
      Ocu_GaaSetAbsoluteThresholdBuffer[LucCount].lddSwAbsoluteValue = (uint32)OCU_ZERO;
      Ocu_GaaSetAbsoluteThresholdBuffer[LucCount].blSetRequest = OCU_FALSE;
      Ocu_GaaSetAbsoluteThresholdBuffer[LucCount].blBufferLock = OCU_FALSE;
      Ocu_GaaSetAbsoluteThresholdBuffer[LucCount].lddSwCounterValue = (uint32)OCU_ZERO;
      #endif

      /* Clear buffer request for Ocu_SetRelativeThreshold */
      #if (OCU_SET_RELATIVE_THRESHOLD_API == STD_ON)
      Ocu_GaaSetRelativeThresholdBuffer[LucCount].lddSwRelativeValue = (uint32)OCU_ZERO;
      Ocu_GaaSetRelativeThresholdBuffer[LucCount].blSetRequest = OCU_FALSE;
      Ocu_GaaSetRelativeThresholdBuffer[LucCount].blBufferLock = OCU_FALSE;
      Ocu_GaaSetRelativeThresholdBuffer[LucCount].lddSwCounterValue = (uint32)OCU_ZERO;
      Ocu_GaaSetRelativeThresholdBuffer[LucCount].lddSwReferenceValue = (uint32)OCU_ZERO;
      Ocu_GaaSetRelativeThresholdBuffer[LucCount].lddSwThresholdValue = (uint32)OCU_ZERO;
      #endif
      #endif /* End of OCU_MULTI_CORE_SUPPORT == STD_ON */
    } /* End of for loop LucCount < (uint8)OCU_TOTAL_CHANNELS_CONFIG */
    /* Set Driver state to uninitialized */
    Ocu_SetStatus(OCU_UNINITIALIZED);
  } /* End of LddDetCheckResult == E_NOT_OK, else No action required */
} /* End of API Ocu_DeInit */

#define OCU_STOP_SEC_PUBLIC_CODE_LOCAL
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of OCU_DE_INIT_API == STD_ON */

/***********************************************************************************************************************
** Function Name         : Ocu_StartChannel
**
** Service ID            : 0x02
**
** Description           : Service to start an OCU channel.
**
** Sync/Async            : Synchronous (Single core) / Asynchronous (Multi-core)
**
** Re-entrancy           : Reentrant for different channel numbers
**
** Input Parameters      : ChannelNumber
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : Std_ReturnType
**
** Preconditions         : Ocu_Init must be called before this function.
**
** Global Variables      : Ocu_GpChannelRamData, Ocu_GaaStartChannelBuffer, Ocu_GpChannelConfig, Ocu_GaaHwFunc,
**                       : Ocu_GulPollingTimes
**
** Functions invoked     : Ocu_HW_Taud_StartChannel, Ocu_HW_Tauj_StartChannel, Ocu_CheckDetErrors, 
**                         Det_ReportRuntimeError
**
** Registers Used        : None
**
** Reference ID          : OCU_DUD_ACT_004
** Reference ID          : OCU_DUD_ACT_004_ERR001, OCU_DUD_ACT_004_ERR002, OCU_DUD_ACT_004_ERR003
** Reference ID          : OCU_DUD_ACT_004_CRT001, OCU_DUD_ACT_004_CRT002, OCU_DUD_ACT_004_GBL001
** Reference ID          : OCU_DUD_ACT_004_CRT003, OCU_DUD_ACT_004_CRT004,OCU_DUD_ACT_004_CRT005
***********************************************************************************************************************/
#define OCU_START_SEC_PUBLIC_CODE_GLOBAL
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, OCU_PUBLIC_CODE) Ocu_StartChannel(Ocu_ChannelType ChannelNumber)                                   /* PRQA S 1503 # JV-01 */
{
  /* Defining a pointer to point to the Channel Ram Data */
  P2VAR(Ocu_ChannelRamDataType, AUTOMATIC, OCU_CONFIG_DATA) LpRamData;                                                  /* PRQA S 3432, 3678 # JV-01, JV-01 */
  #if (OCU_MULTI_CORE_SUPPORT == STD_OFF)
  /* Declare a Local variable to Timer Type */
  VAR(volatile uint8, AUTOMATIC) LucCheckTimerType;
  #else
  /* Polling times until the request has been executed */
  VAR(volatile uint32, AUTOMATIC) LulPollingTimes;
  /* Defining a local pointer to point to the Buffer Ram Data */
  P2VAR(volatile Ocu_Channel_RequestType, AUTOMATIC, OCU_VAR_NO_INIT) LpBufferData;
  #endif
  /* Declare the variable to store the DET return value */
  VAR(Std_ReturnType, AUTOMATIC) LddReturnResult;
  #if (OCU_DEV_ERROR_DETECT == STD_ON)
  /* Check the Det error */
  LddReturnResult = Ocu_CheckDetErrors(ChannelNumber, OCU_START_CHANNEL_SID);
  /* Check if any DET error was reported */
  if (E_OK == LddReturnResult)
  #endif /* (OCU_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Initial value */
    LddReturnResult = E_OK;                                                                                             /* PRQA S 2982 # JV-01 */
    /* Load the channel RAM data to the local */
    LpRamData = &Ocu_GpChannelRamData[ChannelNumber];
    /* Check if the timer is already running */
    if (OCU_CH_RUNNING == LpRamData->blChannelStatus)
    {
      /* Report to Development Errors */
      (void)Det_ReportRuntimeError(OCU_MODULE_ID, OCU_INSTANCE_ID, OCU_START_CHANNEL_SID, OCU_E_BUSY);
      LddReturnResult = E_NOT_OK;
    } /* else No action required */
    else
    {
      #if (OCU_MULTI_CORE_SUPPORT == STD_ON)
      /* Load buffer pointer */
      LpBufferData = &Ocu_GaaStartChannelBuffer[ChannelNumber];
      /* Enter global critical section */
      OCU_ENTER_CRITICAL_SECTION(OCU_RAM_DATA_PROTECTION_GLOBAL);
      /* Set request to master core if the shared buffer is ready - not locked by Satellite */
      if(OCU_UNLOCKEDSTATUS(LpBufferData->blBufferLock))                                                                /* PRQA S 3432 # JV-01 */
      {
        /* Lock the shared buffer */
        OCU_LOCKPROCESS(LpBufferData->blBufferLock);                                                                    /* PRQA S 3432 # JV-01 */
        /* Exit global critical section */
        OCU_EXIT_CRITICAL_SECTION(OCU_RAM_DATA_PROTECTION_GLOBAL);
        /* Request is issued */
        LpBufferData->blSetRequest = OCU_TRUE;
        /* Release Lock */
        OCU_UNLOCKPROCESS(LpBufferData->blBufferLock);                                                                  /* PRQA S 3432 # JV-01 */
        /* Waiting until the request is being executed */
        LulPollingTimes = Ocu_GulPollingTimes;
        do
        {
          LulPollingTimes--;                                                                                            /* PRQA S 3384, 3387 # JV-01, JV-01 */
        } while ((OCU_TRUE == LpBufferData->blSetRequest) && ((uint32)OCU_ZERO != LulPollingTimes));                    /* PRQA S 3415, 3416 # JV-01, JV-01 */
        /* Check if the request has been executed */
        if ((OCU_TRUE == LpBufferData->blSetRequest) && ((uint32)OCU_ZERO == LulPollingTimes))                          /* PRQA S 3415, 3416 # JV-01, JV-01 */
        {
          /* Report to Development Errors */
          (void)Det_ReportRuntimeError(OCU_MODULE_ID, OCU_INSTANCE_ID, OCU_START_CHANNEL_SID, OCU_E_REQUEST_ONGOING);
          /* Channel is not started */
          LddReturnResult = E_NOT_OK;
        }
        else
        {
          /* Channel is started */
          LddReturnResult = E_OK;
        }
      }
      else
      {
        /* Exit global critical section */
        OCU_EXIT_CRITICAL_SECTION(OCU_RAM_DATA_PROTECTION_GLOBAL);
        /* Report to Development Errors */
        (void)Det_ReportRuntimeError(OCU_MODULE_ID, OCU_INSTANCE_ID, OCU_START_CHANNEL_SID, OCU_E_REQUEST_FALSE);
        /* Channel is not started */
        LddReturnResult = E_NOT_OK;
      }
      #else
      /* Read the Timer Type for the given channel */
      LucCheckTimerType = Ocu_GpChannelConfig[ChannelNumber].ucTimerUnitType;
      /* Enter local critical section */
      OCU_ENTER_CRITICAL_SECTION(OCU_INTERRUPT_CONTROL_PROTECTION);
      /* Check against null pointer */
      if (NULL_PTR != Ocu_GaaHwFunc[LucCheckTimerType]->pStartRestartChannel)                                           /* PRQA S 3416 # JV-01 */
      {
        /* Restart the slave timer with the new threshold */
        Ocu_GaaHwFunc[LucCheckTimerType]->pStartRestartChannel(ChannelNumber, LpRamData->ddHwLastThreshold);
      } /* else No action required */
      /* Assign the timer status to the Channel */
      LpRamData->blChannelStatus = OCU_CH_RUNNING;
      /* Exit local critical section */
      OCU_EXIT_CRITICAL_SECTION(OCU_INTERRUPT_CONTROL_PROTECTION);
      #endif /* OCU_MULTI_CORE_SUPPORT == STD_ON */
    } /* else No action required */
  } /* else No action required */
  return LddReturnResult;
} /* End of API Ocu_StartChannel */

#define OCU_STOP_SEC_PUBLIC_CODE_GLOBAL
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Ocu_StopChannel
**
** Service ID            : 0x03
**
** Description           : This API stops the particular timer Channel
**
** Sync/Async            : Synchronous (Single core) / Asynchronous (Multi-core)
**
** Re-entrancy           : Reentrant for different channel numbers
**
** Input Parameters      : ChannelNumber
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : Ocu_Init must be called before this function.
**
** Global Variables      : Ocu_GpChannelRamData, Ocu_GaaStopChannelBuffer, Ocu_GpChannelConfig, Ocu_GaaHwFunc
**
** Functions invoked     : Ocu_HW_Taud_StopChannel, Ocu_HW_Tauj_StopChannel, Ocu_CheckDetErrors, Det_ReportRuntimeError
**
** Registers Used        : None
**
** Reference ID          : OCU_DUD_ACT_005, OCU_DUD_ACT_005_CRT001, OCU_DUD_ACT_005_ERR001
** Reference ID          : OCU_DUD_ACT_005_CRT002, OCU_DUD_ACT_005_CRT003, OCU_DUD_ACT_005_GBL001
***********************************************************************************************************************/
#define OCU_START_SEC_PUBLIC_CODE_GLOBAL
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, OCU_PUBLIC_CODE) Ocu_StopChannel(Ocu_ChannelType ChannelNumber)                                              /* PRQA S 1503 # JV-01 */
{
  #if (OCU_MULTI_CORE_SUPPORT == STD_OFF)
  /* Declare a Local variable to Timer Type */
  VAR(volatile uint8, AUTOMATIC) LucCheckTimerType;
  #else
  /* Defining a local pointer to point to the Buffer Ram Data */
  P2VAR(volatile Ocu_Channel_RequestType, AUTOMATIC, OCU_VAR_NO_INIT) LpBufferData;
  #endif
  #if (OCU_DEV_ERROR_DETECT == STD_ON)
  /* Declare the variable to store the DET return value */
  VAR(Std_ReturnType, AUTOMATIC) LddDetCheckResult;
  /* Check the DET error */
  LddDetCheckResult = Ocu_CheckDetErrors(ChannelNumber, OCU_STOP_CHANNEL_SID);
  /* Check if any DET error was reported */
  if (E_OK == LddDetCheckResult)
  #endif /* End of OCU_DEV_ERROR_DETECT == STD_ON */
  {
    /* Check if the timer is started */
    if (OCU_CH_RUNNING == Ocu_GpChannelRamData[ChannelNumber].blChannelStatus)                                          /* PRQA S 3416 # JV-01 */
    {
      #if (OCU_MULTI_CORE_SUPPORT == STD_ON)
      /* Load buffer pointer */
      LpBufferData = &Ocu_GaaStopChannelBuffer[ChannelNumber];
      /* Enter global critical section */
      OCU_ENTER_CRITICAL_SECTION(OCU_RAM_DATA_PROTECTION_GLOBAL);
      /* Set request to master core if the shared buffer is ready - not locked by Satellite */
      if(OCU_UNLOCKEDSTATUS(LpBufferData->blBufferLock))                                                                /* PRQA S 3432 # JV-01 */
      {
        /* Lock the shared buffer */
        OCU_LOCKPROCESS(LpBufferData->blBufferLock);                                                                    /* PRQA S 3432 # JV-01 */
        /* Exit global critical section */
        OCU_EXIT_CRITICAL_SECTION(OCU_RAM_DATA_PROTECTION_GLOBAL);
        /* Request is issued */
        LpBufferData->blSetRequest = OCU_TRUE;
        /* Release Lock */
        OCU_UNLOCKPROCESS(LpBufferData->blBufferLock);                                                                  /* PRQA S 3432 # JV-01 */
      }
      else
      {
        /* Exit global critical section */
        OCU_EXIT_CRITICAL_SECTION(OCU_RAM_DATA_PROTECTION_GLOBAL);
        /* Report to Development Errors */
        (void)Det_ReportRuntimeError(OCU_MODULE_ID, OCU_INSTANCE_ID, OCU_STOP_CHANNEL_SID, OCU_E_REQUEST_FALSE);
      }
      #else
      /* Read the Timer Type for the given channel */
      LucCheckTimerType = Ocu_GpChannelConfig[ChannelNumber].ucTimerUnitType;
      /* Check against null pointer */
      if (NULL_PTR != Ocu_GaaHwFunc[LucCheckTimerType]->pStopChannel)                                                   /* PRQA S 3416 # JV-01 */
      {
        /* Invoke low-level driver to Stop the particular Channel */
        Ocu_GaaHwFunc[LucCheckTimerType]->pStopChannel(ChannelNumber);
      } /* else No action required */
      #endif /* OCU_MULTI_CORE_SUPPORT == STD_ON */
    } /* else No action required */
  } /* End of LddDetCheckResult == E_NOT_OK, else No action required */
} /* End of API Ocu_StopTimer */

#define OCU_STOP_SEC_PUBLIC_CODE_GLOBAL
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Ocu_EnableNotification
**
** Service ID            : 0x0b
**
** Description           : This service is used to enable notifications from an OCU channel.
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Reentrant for different channel numbers
**
** Input Parameters      : ChannelNumber
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : Ocu_Init must be called before this function and OCU_NOTIFICATION_SUPPORTED must be STD_ON
**
** Global Variables      : Ocu_GpChannelRamData, Ocu_GpChannelConfig, Ocu_GaaHwFunc
**
** Functions invoked     : Ocu_HW_Taud_EnableInterrupt, Ocu_HW_Tauj_EnableInterrupt
**                         Ocu_CheckDetErrors, Det_ReportError
**
** Registers Used        : None
**
** Reference ID          : OCU_DUD_ACT_006, OCU_DUD_ACT_006_ERR001, OCU_DUD_ACT_006_GBL001
** Reference ID          : OCU_DUD_ACT_006_CRT001, OCU_DUD_ACT_006_CRT002
***********************************************************************************************************************/
#if (OCU_NOTIFICATION_SUPPORTED == STD_ON)
#define OCU_START_SEC_PUBLIC_CODE_GLOBAL
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, OCU_PUBLIC_CODE) Ocu_EnableNotification(Ocu_ChannelType ChannelNumber)                                       /* PRQA S 1503 # JV-01 */
{
  /* Declare a Local variable to Timer Type */
  VAR(volatile uint8, AUTOMATIC) LucCheckTimerType;

  #if (OCU_DEV_ERROR_DETECT == STD_ON)
  /* Declare the variable to store the DET return value */
  VAR(Std_ReturnType, AUTOMATIC) LddDetCheckResult;
  /* Check the DET Error */
  LddDetCheckResult = Ocu_CheckDetErrors(ChannelNumber, OCU_ENABLE_NOTIFICATION_SID);
  /* Check if any DET error was reported */
  if (E_OK == LddDetCheckResult)
  {
    /* Check if the Notification Function isn't configured */
    if (NULL_PTR == Ocu_GpChannelConfig[ChannelNumber].pOcuNotificationPointer)                                         /* PRQA S 3416 # JV-01 */
    {
      /* Report Error to Det */
      (void)Det_ReportError(OCU_MODULE_ID, OCU_INSTANCE_ID, OCU_ENABLE_NOTIFICATION_SID, OCU_E_NO_VALID_NOTIF);
      LddDetCheckResult = E_NOT_OK;
    } /* else No action required */
  } /* else No action required */
  /* Check if any DET error was reported */
  if (E_OK == LddDetCheckResult)
  #endif /*  #if (OCU_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Read the Timer Type for the given channel */
    LucCheckTimerType = Ocu_GpChannelConfig[ChannelNumber].ucTimerUnitType;
    /* Enter global critical section */
    OCU_ENTER_CRITICAL_SECTION(OCU_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
    /* Check against null pointer */
    if (NULL_PTR != Ocu_GaaHwFunc[LucCheckTimerType]->pEnableInterrupt)                                                 /* PRQA S 3416 # JV-01 */
    {
      /* Invoke low-level driver to enable interrupt for the particular Channel */
      Ocu_GaaHwFunc[LucCheckTimerType]->pEnableInterrupt(ChannelNumber);
    } /* else No action required */
    /* Set the Notification Status Flag to OCU_TRUE */
    Ocu_GpChannelRamData[ChannelNumber].blNotifyStatus = OCU_TRUE;
    /* Exit global critical section */
    OCU_EXIT_CRITICAL_SECTION(OCU_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
  } /* else No action required */
} /* End of API Ocu_EnableNotification */

#define OCU_STOP_SEC_PUBLIC_CODE_GLOBAL
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of OCU_NOTIFICATION_SUPPORTED == STD_ON */
/***********************************************************************************************************************
** Function Name         : Ocu_DisableNotification
**
** Service ID            : 0x0a
**
** Description           : This service is used to disable notifications from an OCU channel.
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Reentrant for different channel numbers
**
** Input Parameters      : ChannelNumber
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : Ocu_Init must be called before this function and
**                         OCU_NOTIFICATION_SUPPORTED must be STD_ON
**
** Global Variables      : Ocu_GpChannelRamData, Ocu_GpChannelConfig, Ocu_GaaHwFunc
**
** Functions invoked     : Ocu_HW_Taud_DisableInterrupt, Ocu_HW_Tauj_DisableInterrupt
**                         Ocu_CheckDetErrors, Det_ReportError
**
** Registers Used        : None
**
** Reference ID          : OCU_DUD_ACT_007, OCU_DUD_ACT_007_ERR001, OCU_DUD_ACT_007_GBL001
** Reference ID          : OCU_DUD_ACT_007_CRT001, OCU_DUD_ACT_007_CRT002
***********************************************************************************************************************/

#if (OCU_NOTIFICATION_SUPPORTED == STD_ON)
#define OCU_START_SEC_PUBLIC_CODE_GLOBAL
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, OCU_PUBLIC_CODE) Ocu_DisableNotification(Ocu_ChannelType ChannelNumber)                                      /* PRQA S 1503 # JV-01 */
{
  /* Defining a pointer to point to the Channel Ram Data */
  P2VAR(Ocu_ChannelRamDataType, AUTOMATIC, OCU_CONFIG_DATA) LpRamData;                                                  /* PRQA S 3432 # JV-01 */
  /* Declare a Local variable to Timer Type */
  VAR(volatile uint8, AUTOMATIC)
  LucCheckTimerType;
  boolean LblDisableInterrupt;

  #if (OCU_DEV_ERROR_DETECT == STD_ON)
  /* Declare the variable to store the DET value */
  VAR(Std_ReturnType, AUTOMATIC)
  LddDetCheckResult;
  /* Check DET error */
  LddDetCheckResult = Ocu_CheckDetErrors(ChannelNumber, OCU_DISABLE_NOTIFICATION_SID);
  /* Check if any DET error was reported */
  if (E_OK == LddDetCheckResult)
  {
    /* Check if the Notification Function isn't configured */
    if (NULL_PTR == Ocu_GpChannelConfig[ChannelNumber].pOcuNotificationPointer)                                         /* PRQA S 3416 # JV-01 */
    {
      /* Report Error to DET */
      (void)Det_ReportError(OCU_MODULE_ID, OCU_INSTANCE_ID, OCU_DISABLE_NOTIFICATION_SID, OCU_E_NO_VALID_NOTIF);
      LddDetCheckResult = E_NOT_OK;
    } /* else No action required */
  } /* else No action required */
  if (E_OK == LddDetCheckResult)
  #endif /* End of OCU_DEV_ERROR_DETECT == STD_ON */
  {
    /* Default value */
    LblDisableInterrupt = OCU_FALSE;
    /* Updating the channel ram data to the current channel */
    LpRamData = &Ocu_GpChannelRamData[ChannelNumber];
    /* Read the Timer Type for the given channel */
    LucCheckTimerType = Ocu_GpChannelConfig[ChannelNumber].ucTimerUnitType;
    /* Enter global critical section */
    OCU_ENTER_CRITICAL_SECTION(OCU_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
    /* To check the channel is GTM or TAU */
    if (OCU_HWIP_GTM != LucCheckTimerType)                                                                              /* PRQA S 3416 # JV-01 */
    {
      /* Disable the interrupt if the channel pin action is not OCU_SET_HIGH or OCU_SET_LOW and
      no need to rewrite the slave channel data register at the next cycle */
    if ((OCU_FALSE == LpRamData->blRequireRewriteCountValue)
    #if (OCU_SET_PIN_ACTION_API == STD_ON)
          && (OCU_SET_HIGH != LpRamData->ddPinActionState) && (OCU_SET_LOW != LpRamData->ddPinActionState)
    #endif
      )
      {
        /* Interrupt disable is required */
        LblDisableInterrupt = OCU_TRUE;
      }
    }
    else
    {
      /* Check if output disable for GTM channels */
      if (OCU_FALSE == Ocu_GpChannelConfig[ChannelNumber].blOutputPinUsed)                                              /* PRQA S 3416 # JV-01 */
      {
        /* Interrupt disable is required */
        LblDisableInterrupt = OCU_TRUE;
      }
    }
    /* Check if interrupt disable is required */
    if (OCU_TRUE == LblDisableInterrupt)
    {
      /* Check against null pointer */
      if (NULL_PTR != Ocu_GaaHwFunc[LucCheckTimerType]->pDisableInterrupt)                                              /* PRQA S 3416 # JV-01 */
      {
        /* Invoke low-level driver to disable interrupt for the particular Channel */
        Ocu_GaaHwFunc[LucCheckTimerType]->pDisableInterrupt(ChannelNumber);
      } /* else No action required */
    }
    /* Set the Notification Status Flag to OCU_FALSE */
    LpRamData->blNotifyStatus = OCU_FALSE;
    /* Exit global critical section */
    OCU_EXIT_CRITICAL_SECTION(OCU_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
  } /* else No action required */
} /* End of API Ocu_DisableNotification */

#define OCU_STOP_SEC_PUBLIC_CODE_GLOBAL
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of OCU_NOTIFICATION_SUPPORTED == STD_ON */
/***********************************************************************************************************************
** Function Name         : Ocu_SetPinState
**
** Service ID            : 0x04
**
** Description           : Service to set immediately the level of the pin associated with an OCU channel.
**
** Sync/Async            : Synchronous (Single core) / Asynchronous (Multi-core)
**
** Re-entrancy           : Reentrant for different channel numbers
**
** Input Parameters      : ChannelNumber, PinState
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : Ocu_Init must be called before this function and
**                         OCU_SET_PIN_STATE_API must be STD_ON
**
** Global Variables      : Ocu_GpChannelRamData, Ocu_GpChannelConfig, Ocu_GaaHwFunc, Ocu_GaaSetPinStateBuffer
**
** Functions invoked     : Ocu_CheckDetErrors, Det_ReportError, Det_ReportRuntimeError
**                         Ocu_HW_Taud_SetPinState, Ocu_HW_Tauj_SetPinState,
**
** Registers Used        : None
**
** Reference ID          : OCU_DUD_ACT_008
** Reference ID          : OCU_DUD_ACT_008_GBL001, OCU_DUD_ACT_008_ERR001, OCU_DUD_ACT_008_ERR002
** Reference ID          : OCU_DUD_ACT_008_ERR003, OCU_DUD_ACT_008_CRT001, OCU_DUD_ACT_008_CRT002
** Reference ID          : OCU_DUD_ACT_008_CRT003, OCU_DUD_ACT_008_CRT004, OCU_DUD_ACT_008_CRT005
***********************************************************************************************************************/
#if (OCU_SET_PIN_STATE_API == STD_ON)
#define OCU_START_SEC_PUBLIC_CODE_GLOBAL
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, OCU_PUBLIC_CODE) Ocu_SetPinState(Ocu_ChannelType ChannelNumber, Ocu_PinStateType PinState)                   /* PRQA S 1503 # JV-01 */
{
  #if (OCU_MULTI_CORE_SUPPORT == STD_OFF)
  /* Declare a Local variable to Timer Type */
  VAR(volatile uint8, AUTOMATIC) LucCheckTimerType;
  #else
  /* Defining a local pointer to point to the Buffer Ram Data */
  P2VAR(volatile Ocu_SetPinState_RequestType, AUTOMATIC, OCU_VAR_NO_INIT) LpBufferData;
  #endif
  #if (OCU_DEV_ERROR_DETECT == STD_ON)
  /* Declare the variable to store the DET return value */
  VAR(Std_ReturnType, AUTOMATIC) LddDetCheckResult;
  /* Check the DET error */
  LddDetCheckResult = Ocu_CheckDetErrors(ChannelNumber, OCU_SET_PIN_STATE_SID);
  if (E_OK == LddDetCheckResult)
  {
    /* Check that the channel enables pin output */
    if (OCU_FALSE == Ocu_GpChannelConfig[ChannelNumber].blOutputPinUsed)                                                /* PRQA S 3416 # JV-01 */
    {
      /* Report Error to Det */
      (void)Det_ReportError(OCU_MODULE_ID, OCU_INSTANCE_ID, OCU_SET_PIN_STATE_SID, OCU_E_PARAM_NO_PIN);
      LddDetCheckResult = E_NOT_OK;
    }
    else if ((OCU_CH_RUNNING == Ocu_GpChannelRamData[ChannelNumber].blChannelStatus) ||                                 /* PRQA S 2004, 3416 # JV-01, JV-01 */
                                                                     ((OCU_HIGH != PinState) && (OCU_LOW != PinState)))
    {
      /* Report Error to Det */
      (void)Det_ReportError(OCU_MODULE_ID, OCU_INSTANCE_ID, OCU_SET_PIN_STATE_SID, OCU_E_PARAM_INVALID_STATE);
      LddDetCheckResult = E_NOT_OK;
    } /* else No action required */
  } /* else No action required */
  /* Check if any DET error was reported */
  if (E_OK == LddDetCheckResult)
  #endif /* End of OCU_DEV_ERROR_DETECT == STD_ON */
  {
    #if (OCU_MULTI_CORE_SUPPORT == STD_ON)
        /* Load buffer pointer */
    LpBufferData = &Ocu_GaaSetPinStateBuffer[ChannelNumber];
    /* Enter global critical section */
    OCU_ENTER_CRITICAL_SECTION(OCU_RAM_DATA_PROTECTION_GLOBAL);
    /* Set request to master core if the shared buffer is ready - not locked by Satellite */
    if(OCU_UNLOCKEDSTATUS(LpBufferData->blBufferLock))                                                                  /* PRQA S 3432 # JV-01 */
    {
      /* Lock the shared buffer */
      OCU_LOCKPROCESS(LpBufferData->blBufferLock);                                                                      /* PRQA S 3432 # JV-01 */
      /* Exit global critical section */
      OCU_EXIT_CRITICAL_SECTION(OCU_RAM_DATA_PROTECTION_GLOBAL);
      /* Update the request */
      LpBufferData->lddPinState = PinState;
      /* Request is issued */
      LpBufferData->blSetRequest = OCU_TRUE;
      /* Release Lock */
      OCU_UNLOCKPROCESS(LpBufferData->blBufferLock);                                                                    /* PRQA S 3432 # JV-01 */
    }
    else
    {
      /* Exit global critical section */
      OCU_EXIT_CRITICAL_SECTION(OCU_RAM_DATA_PROTECTION_GLOBAL);
      /* Report to Development Errors */
      (void)Det_ReportRuntimeError(OCU_MODULE_ID, OCU_INSTANCE_ID, OCU_SET_PIN_STATE_SID, OCU_E_REQUEST_FALSE);
    }
    #else
    /* Read the Timer Type for the given channel */
    LucCheckTimerType = Ocu_GpChannelConfig[ChannelNumber].ucTimerUnitType;
    /* Check against null pointer */
    if (NULL_PTR != Ocu_GaaHwFunc[LucCheckTimerType]->pSetPinState)                                                     /* PRQA S 3416 # JV-01 */
    {
      /* Enter local critical section */
      OCU_ENTER_CRITICAL_SECTION(OCU_INTERRUPT_CONTROL_PROTECTION);
      /* Invoke low-level driver to set the pin state for the particular Channel */
      Ocu_GaaHwFunc[LucCheckTimerType]->pSetPinState(ChannelNumber, PinState);
      /* Exit local critical section */
      OCU_EXIT_CRITICAL_SECTION(OCU_INTERRUPT_CONTROL_PROTECTION);
    } /* else No action required */
    #endif /* OCU_MULTI_CORE_SUPPORT == STD_ON */
  } /* End of E_OK == LddDetCheckResult */
} /* End of API Ocu_SetPinState */
#define OCU_STOP_SEC_PUBLIC_CODE_GLOBAL
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of OCU_SET_PIN_STATE_API == STD_ON */
/***********************************************************************************************************************
** Function Name         : Ocu_SetPinAction
**
** Service ID            : 0x05
**
** Description           : Service to indicate the driver what shall be done automatically by hardware (if supported)
**                         upon comparing matches.
**
** Sync/Async            : Synchronous (Single core) / Asynchronous (Multi-core)
**
** Re-entrancy           : Reentrant for different channel numbers
**
** Input Parameters      : ChannelNumber, PinAction
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : Ocu_Init must be called before this function and
**                         OCU_SET_PIN_ACTION_API must be STD_ON
**
** Global Variables      : Ocu_GpChannelConfig, Ocu_GaaHwFunc, Ocu_GaaSetPinActionBuffer
**
** Functions invoked     : Ocu_CheckDetErrors, Det_ReportError, Ocu_HW_Taud_SetPinAction, Ocu_HW_Tauj_SetPinAction
**                         Det_ReportRuntimeError
** Registers Used        : None
**
** Reference ID          : OCU_DUD_ACT_009, OCU_DUD_ACT_009_GBL001
** Reference ID          : OCU_DUD_ACT_009_CRT001, OCU_DUD_ACT_009_CRT002, OCU_DUD_ACT_009_GBL002
** Reference ID          : OCU_DUD_ACT_009_CRT003, OCU_DUD_ACT_009_CRT004, OCU_DUD_ACT_009_CRT005
** Reference ID          : OCU_DUD_ACT_009_ERR001, OCU_DUD_ACT_009_ERR002, OCU_DUD_ACT_009_ERR003
***********************************************************************************************************************/
#if (OCU_SET_PIN_ACTION_API == STD_ON)
#define OCU_START_SEC_PUBLIC_CODE_GLOBAL
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, OCU_PUBLIC_CODE) Ocu_SetPinAction(Ocu_ChannelType ChannelNumber, Ocu_PinActionType PinAction)                /* PRQA S 1503 # JV-01 */
{
  #if (OCU_MULTI_CORE_SUPPORT == STD_OFF)
  /* Declare a Local variable to Timer Type */
  VAR(volatile uint8, AUTOMATIC) LucCheckTimerType;
  #else
  /* Defining a local pointer to point to the Buffer Ram Data */
  P2VAR(volatile Ocu_SetPinAction_RequestType, AUTOMATIC, OCU_VAR_NO_INIT) LpBufferData;
  #endif
  #if (OCU_DEV_ERROR_DETECT == STD_ON)
  /* Declare the variable to store the DET return value */
  VAR(Std_ReturnType, AUTOMATIC) LddDetCheckResult;
  /* Check the DET error */
  LddDetCheckResult = Ocu_CheckDetErrors(ChannelNumber, OCU_SET_PIN_ACTION_SID);
  if (E_OK == LddDetCheckResult)
  {
    /* Check that the channel enables pin output */
    if (OCU_FALSE == Ocu_GpChannelConfig[ChannelNumber].blOutputPinUsed)                                                /* PRQA S 3416 # JV-01 */
    {
      /* Report Error to Det */
      (void)Det_ReportError(OCU_MODULE_ID, OCU_INSTANCE_ID, OCU_SET_PIN_ACTION_SID, OCU_E_PARAM_NO_PIN);
      LddDetCheckResult = E_NOT_OK;
    }
    else if ((OCU_SET_HIGH  != PinAction) && (OCU_SET_LOW  != PinAction) && (OCU_TOGGLE  != PinAction) &&               /* PRQA S 2004 # JV-01 */
                                                                                          (OCU_DISABLE != PinAction))
    {
      /* Report Error to Det */
      (void)Det_ReportError(OCU_MODULE_ID, OCU_INSTANCE_ID, OCU_SET_PIN_ACTION_SID, OCU_E_PARAM_INVALID_ACTION);
      LddDetCheckResult = E_NOT_OK;
    } /* else No action required */
  } /* else No action required */
  /* Check if any DET error was reported */
  if (E_OK == LddDetCheckResult)
  #endif /* End of OCU_DEV_ERROR_DETECT == STD_ON */
  {
    #if (OCU_MULTI_CORE_SUPPORT == STD_ON)
    /* Load buffer pointer */
    LpBufferData = &Ocu_GaaSetPinActionBuffer[ChannelNumber];
    /* Enter global critical section */
    OCU_ENTER_CRITICAL_SECTION(OCU_RAM_DATA_PROTECTION_GLOBAL);
    /* Set request to master core if the shared buffer is ready - not locked by Satellite */
    if(OCU_UNLOCKEDSTATUS(LpBufferData->blBufferLock))                                                                  /* PRQA S 3432 # JV-01 */
    {
      /* Lock the shared buffer */
      OCU_LOCKPROCESS(LpBufferData->blBufferLock);                                                                      /* PRQA S 3432 # JV-01 */
      /* Exit global critical section */
      OCU_EXIT_CRITICAL_SECTION(OCU_RAM_DATA_PROTECTION_GLOBAL);
      /* Update the request */
      LpBufferData->lddPinAction = PinAction;
      /* Request is issued */
      LpBufferData->blSetRequest = OCU_TRUE;
      /* Release Lock */
      OCU_UNLOCKPROCESS(LpBufferData->blBufferLock);                                                                    /* PRQA S 3432 # JV-01 */
    }
    else
    {
      /* Exit global critical section */
      OCU_EXIT_CRITICAL_SECTION(OCU_RAM_DATA_PROTECTION_GLOBAL);
      /* Report to Development Errors */
      (void)Det_ReportRuntimeError(OCU_MODULE_ID, OCU_INSTANCE_ID, OCU_SET_PIN_ACTION_SID, OCU_E_REQUEST_FALSE);
    }
    #else
    /* Read the Timer Type for the given channel */
    LucCheckTimerType = Ocu_GpChannelConfig[ChannelNumber].ucTimerUnitType;
    /* Enter local critical section */
    OCU_ENTER_CRITICAL_SECTION(OCU_INTERRUPT_CONTROL_PROTECTION);
    /* Check against null pointer */
    if (NULL_PTR != Ocu_GaaHwFunc[LucCheckTimerType]->pSetPinAction)                                                    /* PRQA S 3416 # JV-01 */
    {
      /* Invoke low-level driver to set the pin action for the particular Channel */
      Ocu_GaaHwFunc[LucCheckTimerType]->pSetPinAction(ChannelNumber, PinAction);
    } /* else No action required */
    /* Set the pin action */
    Ocu_GpChannelRamData[ChannelNumber].ddPinActionState = PinAction;
    /* Exit local critical section */
    OCU_EXIT_CRITICAL_SECTION(OCU_INTERRUPT_CONTROL_PROTECTION);
    #endif /* OCU_MULTI_CORE_SUPPORT == STD_ON */
  } /* End of LddDetCheckResult == E_NOT_OK, else No action required */
} /* End of API Ocu_SetPinAction */
#define OCU_STOP_SEC_PUBLIC_CODE_GLOBAL
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of OCU_SET_PIN_ACTION_API == STD_ON */
/***********************************************************************************************************************
** Function Name         : Ocu_GetCounter
**
** Service ID            : 0x06
**
** Description           : Service to read the current value of the counter.
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Reentrant
**
** Input Parameters      : ChannelNumber
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : Ocu_ValueType
**
** Preconditions         : Ocu_Init must be called before this function and
**                         OCU_GET_COUNTER_API must be STD_ON
**
** Global Variables      : Ocu_GpChannelConfig, Ocu_GaaHwFunc
**
** Functions invoked     : Ocu_CheckDetErrors, Ocu_HW_Taud_GetCounter, Ocu_HW_Tauj_GetCounter
**
** Registers Used        : None
**
** Reference ID          : OCU_DUD_ACT_010, OCU_DUD_ACT_010_GBL001
***********************************************************************************************************************/
#if (OCU_GET_COUNTER_API == STD_ON)
#define OCU_START_SEC_PUBLIC_CODE_GLOBAL
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(Ocu_ValueType, OCU_PUBLIC_CODE) Ocu_GetCounter(Ocu_ChannelType ChannelNumber)                                      /* PRQA S 1503 # JV-01 */
{
  /* Declare the variable to store the DET return value */
  VAR(Ocu_ValueType, AUTOMATIC) LddCounterValue;
  /* Declare a Local variable to Timer Type */
  VAR(volatile uint8, AUTOMATIC) LucCheckTimerType;
  #if (OCU_DEV_ERROR_DETECT == STD_ON)
  /* Declare the variable to store the DET return value */
  VAR(Std_ReturnType, AUTOMATIC) LddDetCheckResult;
  /* Check the DET error */
  LddDetCheckResult = Ocu_CheckDetErrors(ChannelNumber, OCU_SET_GET_COUNTER_SID);
  #endif
  /* Initial value */
  LddCounterValue = (uint32)OCU_ZERO;
  /* Check if any DET error was reported */
  #if (OCU_DEV_ERROR_DETECT == STD_ON)
  if (E_OK == LddDetCheckResult)
  #endif
  {
    /* Read the Timer Type for the given channel */
    LucCheckTimerType = Ocu_GpChannelConfig[ChannelNumber].ucTimerUnitType;
    /* Check against null pointer */
    if (NULL_PTR != Ocu_GaaHwFunc[LucCheckTimerType]->pGetCounter)                                                      /* PRQA S 3416 # JV-01 */
    {
      /* Invoke low-level driver to get the current counter value of the particular Channel */
      LddCounterValue = Ocu_GaaHwFunc[LucCheckTimerType]->pGetCounter(ChannelNumber);
    } /* else No action required */
  } /* else No action required */
  return LddCounterValue;
} /* End of API Ocu_SetPinAction */
#define OCU_STOP_SEC_PUBLIC_CODE_GLOBAL
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of OCU_GET_COUNTER_API == STD_ON */
/***********************************************************************************************************************
** Function Name         : Ocu_SetAbsoluteThreshold
**
** Service ID            : 0x07
**
** Description           : Service to set the value of the channel threshold using absolute input data.
**
** Sync/Async            : Synchronous (Single core) / Asynchronous (Multi-core)
**
** Re-entrancy           : Reentrant for different channel numbers
**
** Input Parameters      : ChannelNumber, ReferenceValue, AbsoluteValue
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : Ocu_ReturnType
**
** Preconditions         : Ocu_Init must be called before this function and
**                         OCU_SET_ABSOLUTE_THRESHOLD_API must be STD_ON
**
** Global Variables      : Ocu_GpChannelConfig, Ocu_GaaHwFunc, Ocu_GaaSetAbsoluteThresholdBuffer, Ocu_GulPollingTimes,
**                       : Ocu_GblCountingDirection
**
** Functions invoked     : Ocu_CheckDetErrors, Det_ReportError, Det_ReportRuntimeError
**                         Ocu_HW_Tauj_SetThreshold, Ocu_HW_Taud_SetThreshold, Ocu_HW_Tauj_GetCounter, 
**                         Ocu_HW_Taud_GetCounter
**
** Registers Used        : None
**
** Reference ID          :  OCU_DUD_ACT_011, OCU_DUD_ACT_011_ERR001
** Reference ID          :  OCU_DUD_ACT_011_GBL001, OCU_DUD_ACT_011_ERR002, OCU_DUD_ACT_011_ERR003
** Reference ID          :  OCU_DUD_ACT_011_CRT001, OCU_DUD_ACT_011_CRT002, OCU_DUD_ACT_011_CRT003
** Reference ID          :  OCU_DUD_ACT_011_CRT004, OCU_DUD_ACT_011_CRT005
***********************************************************************************************************************/
#if (OCU_SET_ABSOLUTE_THRESHOLD_API == STD_ON)
#define OCU_START_SEC_PUBLIC_CODE_GLOBAL
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(Ocu_ReturnType, OCU_PUBLIC_CODE) Ocu_SetAbsoluteThreshold(Ocu_ChannelType ChannelNumber,                           /* PRQA S 1503 # JV-01 */
                                                            Ocu_ValueType ReferenceValue, Ocu_ValueType AbsoluteValue)
{
  /* Declare a Local variable to return the result */
  VAR(volatile Ocu_ReturnType, AUTOMATIC) LenReturnResult;
  /* Variable to hold the current SW time */
  VAR(volatile Ocu_ValueType, AUTOMATIC) LddSwCounterValue;
  /* Declare a Local variable to Timer Type */
  #if (OCU_MULTI_CORE_SUPPORT == STD_OFF)
  VAR(volatile uint8, AUTOMATIC) LucCheckTimerType;
  #else
  /* Polling times until the request has been executed */
  VAR(volatile uint32, AUTOMATIC) LulPollingTimes;
  /* Defining a local pointer to point to the Buffer Ram Data */
  P2VAR(volatile Ocu_SetAbsoluteThreshold_RequestType, AUTOMATIC, OCU_VAR_NO_INIT) LpBufferData;
  #endif
  #if (OCU_DEV_ERROR_DETECT == STD_ON)
  /* Pointer to the channel configuration */
  P2CONST(Ocu_ChannelConfigType, AUTOMATIC, OCU_CONFIG_DATA) LpChannel;
  /* Declare the variable to store the DET return value */
  VAR(Std_ReturnType, AUTOMATIC) LddDetCheckResult;
  /* Check the DET error */
  LddDetCheckResult = Ocu_CheckDetErrors(ChannelNumber, OCU_SET_ABSOLUTE_THRESHOLD_SID);
  /* Check if any DET error was reported */
  if (E_OK == LddDetCheckResult)
  {
    /* Updating the channel config parameter to the current channel */
    LpChannel = &Ocu_GpChannelConfig[ChannelNumber];
    /* Check if the input threshold is greater than the max value that the channel can count */
    if ((LpChannel->ulMaxCounterValue < ReferenceValue) || (LpChannel->ulMaxCounterValue < AbsoluteValue))
    {
      /* Report Error to Det */
      (void)Det_ReportError(OCU_MODULE_ID, OCU_INSTANCE_ID, OCU_SET_ABSOLUTE_THRESHOLD_SID,
                                                                                      OCU_E_PARAM_INVALID_THRESHOLD);
      LddDetCheckResult = E_NOT_OK;
    } /* else No action required */
  } /* else No action required */
  #endif /* End of OCU_DEV_ERROR_DETECT == STD_ON */
  /* Initial value */
  LenReturnResult = OCU_CM_OUT_REF_INTERVAL;
  LddSwCounterValue = AbsoluteValue;
  #if (OCU_DEV_ERROR_DETECT == STD_ON)
  /* Check if any DET error was reported */
  if (E_OK == LddDetCheckResult)
  #endif
  {
    #if (OCU_MULTI_CORE_SUPPORT == STD_OFF)
    /* Read the Timer Type for the given channel */
    LucCheckTimerType = Ocu_GpChannelConfig[ChannelNumber].ucTimerUnitType;
    /* Enter global critical section */
    OCU_ENTER_CRITICAL_SECTION(OCU_INTERRUPT_CONTROL_PROTECTION);
    /* Check that the low-layer function is valid */
    if (NULL_PTR != Ocu_GaaHwFunc[LucCheckTimerType]->pSetThreshold)                                                    /* PRQA S 3416 # JV-01 */
    {
      /* Invoke low-level driver to set the new threshold using absolute value */
      Ocu_GaaHwFunc[LucCheckTimerType]->pSetThreshold(ChannelNumber, AbsoluteValue);
    } /* else No action required */

    /* Check that the low-layer function is valid */
    if (NULL_PTR != Ocu_GaaHwFunc[LucCheckTimerType]->pGetCounter)                                                      /* PRQA S 3416 # JV-01 */
    {
      /* Invoke low-level driver to get the current counter value again after setting the new threshold */
      LddSwCounterValue = Ocu_GaaHwFunc[LucCheckTimerType]->pGetCounter(ChannelNumber);
    } /* else No action required */
    /* Exit global critical section */
    OCU_EXIT_CRITICAL_SECTION(OCU_INTERRUPT_CONTROL_PROTECTION);
    #else /* OCU_MULTI_CORE_SUPPORT == STD_ON */
    /* Load buffer pointer */
    LpBufferData = &Ocu_GaaSetAbsoluteThresholdBuffer[ChannelNumber];
    /* Enter global critical section */
    OCU_ENTER_CRITICAL_SECTION(OCU_RAM_DATA_PROTECTION_GLOBAL);
    /* Set request to master core if the shared buffer is ready - not locked by Satellite */
    if(OCU_UNLOCKEDSTATUS(LpBufferData->blBufferLock))                                                                  /* PRQA S 3432 # JV-01 */
    {
      /* Lock the shared buffer */
      OCU_LOCKPROCESS(LpBufferData->blBufferLock);                                                                      /* PRQA S 3432 # JV-01 */
      /* Exit global critical section */
      OCU_EXIT_CRITICAL_SECTION(OCU_RAM_DATA_PROTECTION_GLOBAL);
      /* Update the request */
      LpBufferData->lddSwAbsoluteValue = AbsoluteValue;
      /* Request is issued */
      LpBufferData->blSetRequest = OCU_TRUE;
      /* Initial the buffer */
      LpBufferData->lddSwCounterValue = (Ocu_ValueType)OCU_ZERO;
      /* Release Lock */
      OCU_UNLOCKPROCESS(LpBufferData->blBufferLock);                                                                    /* PRQA S 3432 # JV-01 */
      /* Waiting until the request is being executed */
      LulPollingTimes = Ocu_GulPollingTimes;
      do
      {
        LulPollingTimes--;                                                                                              /* PRQA S 3384, 3387 # JV-01, JV-01 */
      } while ((OCU_TRUE == LpBufferData->blSetRequest) && ((uint32)OCU_ZERO != LulPollingTimes));                      /* PRQA S 3415, 3416 # JV-01, JV-01 */
      /* Check if the request hasn't been executed */
      if ((OCU_TRUE == LpBufferData->blSetRequest) && ((uint32)OCU_ZERO == LulPollingTimes))                            /* PRQA S 3415, 3416 # JV-01, JV-01 */
      {
        /* Report to Development Errors */
        (void)Det_ReportRuntimeError(OCU_MODULE_ID, OCU_INSTANCE_ID,
                                                                OCU_SET_ABSOLUTE_THRESHOLD_SID, OCU_E_REQUEST_ONGOING);
      }
      else
      {
        /* Load the current counter value from buffer */
        LddSwCounterValue = LpBufferData->lddSwCounterValue;
      }
    }
    else
    {
      /* Exit global critical section */
      OCU_EXIT_CRITICAL_SECTION(OCU_RAM_DATA_PROTECTION_GLOBAL);
      /* Report to Development Errors */
      (void)Det_ReportRuntimeError(OCU_MODULE_ID, OCU_INSTANCE_ID,
                                                                  OCU_SET_ABSOLUTE_THRESHOLD_SID, OCU_E_REQUEST_FALSE);
    }
    #endif /* End of OCU_MULTI_CORE_SUPPORT == STD_OFF */

    /* Check the counting direction */
    if (OCU_UPCOUNTING == Ocu_GblCountingDirection)                                                                     /* PRQA S 3416 # JV-01 */
    {
      /* In case of Reference Interval is inside this cycle */
      if (ReferenceValue <= AbsoluteValue)
      {
        /* If the current counter is in the Reference Interval */
        if ((ReferenceValue <= LddSwCounterValue ) && (LddSwCounterValue < AbsoluteValue))                              /* PRQA S 3415, 3416 # JV-01, JV-01 */
        {
          /* Return OCU_CM_IN_REF_INTERVAL */
          LenReturnResult = OCU_CM_IN_REF_INTERVAL;
        } /* else No action required */
      }
      else /* In case of Reference Interval is in the rollover of the counter */
      {
        /* If the current counter is in the Reference Interval */
        if ((ReferenceValue <= LddSwCounterValue ) || (LddSwCounterValue < AbsoluteValue))                              /* PRQA S 3415, 3416 # JV-01, JV-01 */
        {
          /* Return OCU_CM_IN_REF_INTERVAL */
          LenReturnResult = OCU_CM_IN_REF_INTERVAL;
        } /* else No action required */
      } /* End of check Reference Interval is inside this cycle */
    }
    else /* Else OCU_DOWNCOUNTING */
    {
      /* In case of Reference Interval is inside this cycle */
      if (ReferenceValue >= AbsoluteValue)
      {
        /* If the current counter is in the Reference Interval */
        if ((ReferenceValue >= LddSwCounterValue ) && (LddSwCounterValue > AbsoluteValue))                              /* PRQA S 3415, 3416 # JV-01, JV-01 */
        {
          /* Return OCU_CM_IN_REF_INTERVAL */
          LenReturnResult = OCU_CM_IN_REF_INTERVAL;
        } /* else No action required */
      }
      else /* In case of Reference Interval is in the rollover of the counter */
      {
        /* If the current counter is in the Reference Interval */
        if ((ReferenceValue >= LddSwCounterValue ) || (LddSwCounterValue > AbsoluteValue))                              /* PRQA S 3415, 3416 # JV-01, JV-01 */
        {
          /* Return OCU_CM_IN_REF_INTERVAL */
          LenReturnResult = OCU_CM_IN_REF_INTERVAL;
        } /* else No action required */
      } /* End of check Reference Interval is inside this cycle */
    } /* OCU_UPCOUNTING == Ocu_GblCountingDirection */
  } /* E_OK == LddDetCheckResult */
  return LenReturnResult;
} /* End of API Ocu_SetAbsoluteThreshold */
#define OCU_STOP_SEC_PUBLIC_CODE_GLOBAL
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of OCU_SET_ABSOLUTE_THRESHOLD_API == STD_ON */
/***********************************************************************************************************************
** Function Name         : Ocu_SetRelativeThreshold
**
** Service ID            : 0x08
**
** Description           : Service to set the value of the channel threshold relative to the current value of
**                         the counter.
**
** Sync/Async            : Synchronous (Single core) / Asynchronous (Multi-core)
**
** Re-entrancy           : Reentrant for different channel numbers
**
** Input Parameters      : ChannelNumber, RelativeValue
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : Ocu_ReturnType
**
** Preconditions         : Ocu_Init must be called before this function and
**                         OCU_SET_RELATIVE_THRESHOLD_API must be STD_ON
**
** Global Variables      : Ocu_GpChannelConfig, Ocu_GaaHwFunc, Ocu_GaaSetRelativeThresholdBuffer, 
**                       : Ocu_GblCountingDirection, Ocu_GulPollingTimes
**
** Functions invoked     : Ocu_CheckDetErrors, Det_ReportError, Det_ReportRuntimeError
**                         Ocu_HW_Tauj_SetThreshold, Ocu_HW_Taud_SetThreshold
**
** Registers Used        : None
**
** Reference ID          : OCU_DUD_ACT_012, OCU_DUD_ACT_012_ERR001, OCU_DUD_ACT_012_ERR002, OCU_DUD_ACT_012_GBL001
** Reference ID          : OCU_DUD_ACT_012_ERR003, OCU_DUD_ACT_012_CRT001, OCU_DUD_ACT_012_CRT002
** Reference ID          : OCU_DUD_ACT_012_CRT003, OCU_DUD_ACT_012_CRT004, OCU_DUD_ACT_012_CRT005
***********************************************************************************************************************/
#if (OCU_SET_RELATIVE_THRESHOLD_API == STD_ON)
#define OCU_START_SEC_PUBLIC_CODE_GLOBAL
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(Ocu_ReturnType, OCU_PUBLIC_CODE) Ocu_SetRelativeThreshold(Ocu_ChannelType ChannelNumber,                           /* PRQA S 1503 # JV-01 */
                                                                                          Ocu_ValueType RelativeValue)
{
  /* Declare a Local variable to return the result */
  VAR(volatile Ocu_ReturnType, AUTOMATIC) LenReturnResult;
  /* Variable to hold the current SW time */
  VAR(volatile Ocu_ValueType, AUTOMATIC) LddSwCounterValue;
  /* Local variable holds the new absolute threshold - SW tick */
  VAR(Ocu_ValueType, AUTOMATIC) LddSwThresholdValue;
  /* Local variable holds the new reference SW tick */
  VAR(Ocu_ValueType, AUTOMATIC) LddSwReferenceValue;
  #if (OCU_MULTI_CORE_SUPPORT == STD_OFF)
  /* Local variable holds the SW tick until the counter overflows */
  VAR(Ocu_ValueType, AUTOMATIC) LddSwOverFlowValue;
  /* Declare a Local variable to Timer Type */
  VAR(volatile uint8, AUTOMATIC) LucCheckTimerType;
  #else
  /* Polling times until the request has been executed */
  VAR(volatile uint32, AUTOMATIC) LulPollingTimes;
  /* Defining a local pointer to point to the Buffer Ram Data */
  P2VAR(volatile Ocu_SetRelativeThreshold_RequestType, AUTOMATIC, OCU_VAR_NO_INIT) LpBufferData;
  #endif
  #if (OCU_DEV_ERROR_DETECT == STD_ON)
  /* Declare the variable to store the DET return value */
  VAR(Std_ReturnType, AUTOMATIC) LddDetCheckResult;
  /* Check the DET error */
  LddDetCheckResult = Ocu_CheckDetErrors(ChannelNumber, OCU_SET_RELATIVE_THRESHOLD_SID);
  if (E_OK == LddDetCheckResult)
  {
    /* Check if the input RelativeValue is greater than the max counter of the timer channel */
    if (Ocu_GpChannelConfig[ChannelNumber].ulMaxCounterValue < RelativeValue)                                           /* PRQA S 3416 # JV-01 */
    {
      /* Report Error to Det */
      (void)Det_ReportError(OCU_MODULE_ID, OCU_INSTANCE_ID, OCU_SET_RELATIVE_THRESHOLD_SID,
                                                                                      OCU_E_PARAM_INVALID_THRESHOLD);
      LddDetCheckResult = E_NOT_OK;
    } /* else No action required */
  } /* else No action required */
  #endif /* End of OCU_DEV_ERROR_DETECT == STD_ON */
  /* Initial value */
  LenReturnResult = OCU_CM_OUT_REF_INTERVAL;
  LddSwCounterValue = (uint32)OCU_ZERO;
  LddSwReferenceValue = (uint32)OCU_ZERO;
  LddSwThresholdValue = (uint32)OCU_ZERO;                                                                               /* PRQA S 2982 # JV-01 */
  #if (OCU_DEV_ERROR_DETECT == STD_ON)
  /* Check if any DET error was reported */
  if (E_OK == LddDetCheckResult)
  #endif /* End of OCU_DEV_ERROR_DETECT == STD_ON */
  {
    #if (OCU_MULTI_CORE_SUPPORT == STD_OFF)
    /* Read the Timer Type for the given channel */
    LucCheckTimerType = Ocu_GpChannelConfig[ChannelNumber].ucTimerUnitType;
    /* Enter global critical section */
    OCU_ENTER_CRITICAL_SECTION(OCU_INTERRUPT_CONTROL_PROTECTION);
    /* Check that the low-layer function is valid */
    if (NULL_PTR != Ocu_GaaHwFunc[LucCheckTimerType]->pGetCounter)                                                      /* PRQA S 3416 # JV-01 */
    {
      /* Invoke low-level driver to get the current counter value */
      LddSwCounterValue = Ocu_GaaHwFunc[LucCheckTimerType]->pGetCounter(ChannelNumber);
      LddSwReferenceValue = LddSwCounterValue;
    } /* else No action required */

    /* Check the counting direction */
    if (OCU_UPCOUNTING == Ocu_GblCountingDirection)                                                                     /* PRQA S 3416 # JV-01 */
    {
      /* Read the remaining tick until overflow occurs on the master channel */
      LddSwOverFlowValue = Ocu_GpChannelConfig[ChannelNumber].ulMaxCounterValue - LddSwCounterValue;                    /* PRQA S 0404, 3384 # JV-01, JV-01 */
      /* Check that is there any capable of overflowing the master counter */
      if (LddSwOverFlowValue >= RelativeValue)
      {
        /* Set new absolute threshold value equal to last counter + relative time */
        LddSwThresholdValue = LddSwCounterValue + RelativeValue;                                                        /* PRQA S 3383 # JV-01 */
      }
      else /* The master channel will overflow */
      {
        /* Set new absolute threshold value */
        LddSwThresholdValue = (RelativeValue - LddSwOverFlowValue) - (uint32)OCU_ONE;                                   /* PRQA S 3383, 3384 # JV-01, JV-01 */
      }
    }
    else /* Else OCU_DOWNCOUNTING */
    {
      /* Check that is there any capable of overflowing the master counter */
      if (LddSwCounterValue >= RelativeValue)                                                                           /* PRQA S 3416 # JV-01 */
      {
        /* Set new absolute threshold value equal to last counter - relative time */
        LddSwThresholdValue = LddSwCounterValue - RelativeValue;                                                        /* PRQA S 3384 # JV-01 */
      }
      else /* The master channel will overflow */
      {
        /* Read the max Sw counter value */
        LddSwOverFlowValue = Ocu_GpChannelConfig[ChannelNumber].ulMaxCounterValue;
        /* Set new absolute threshold value */
        LddSwThresholdValue = LddSwOverFlowValue - (RelativeValue - LddSwCounterValue - (uint32)OCU_ONE);               /* PRQA S 3383, 3384 # JV-01, JV-01 */
      }
    } /* OCU_UPCOUNTING == Ocu_GblCountingDirection */

    /* Check against null pointer */
    if (NULL_PTR != Ocu_GaaHwFunc[LucCheckTimerType]->pSetThreshold)                                                    /* PRQA S 3416 # JV-01 */
    {
      /* Invoke low-level driver to set the new threshold using relative value */
      Ocu_GaaHwFunc[LucCheckTimerType]->pSetThreshold(ChannelNumber, LddSwThresholdValue);
    } /* else No action required */

    /* Check that the low-layer function is valid */
    if (NULL_PTR != Ocu_GaaHwFunc[LucCheckTimerType]->pGetCounter)                                                      /* PRQA S 3416 # JV-01 */
    {
      /* Invoke low-level driver to get the current counter value again after setting the new threshold */
      LddSwCounterValue = Ocu_GaaHwFunc[LucCheckTimerType]->pGetCounter(ChannelNumber);
    } /* else No action required */
    /* Exit global critical section */
    OCU_EXIT_CRITICAL_SECTION(OCU_INTERRUPT_CONTROL_PROTECTION);
    #else /* OCU_MULTI_CORE_SUPPORT == STD_ON */
    LpBufferData = &Ocu_GaaSetRelativeThresholdBuffer[ChannelNumber];
    /* Enter global critical section */
    OCU_ENTER_CRITICAL_SECTION(OCU_RAM_DATA_PROTECTION_GLOBAL);
    /* Set request to master core if the shared buffer is ready - not locked by Satellite */
    if(OCU_UNLOCKEDSTATUS(LpBufferData->blBufferLock))                                                                  /* PRQA S 3432 # JV-01 */
    {
     /* Lock the shared buffer */
      OCU_LOCKPROCESS(LpBufferData->blBufferLock);                                                                      /* PRQA S 3432 # JV-01 */
      /* Exit global critical section */
      OCU_EXIT_CRITICAL_SECTION(OCU_RAM_DATA_PROTECTION_GLOBAL);
      /* Update the request */
      LpBufferData->lddSwRelativeValue = RelativeValue;
      /* Request is issued */
      LpBufferData->blSetRequest = OCU_TRUE;
      /* Initial the buffer */
      LpBufferData->lddSwCounterValue = (Ocu_ValueType)OCU_ZERO;
      LpBufferData->lddSwReferenceValue = (Ocu_ValueType)OCU_ZERO;
      LpBufferData->lddSwThresholdValue = (Ocu_ValueType)OCU_ZERO;
      /* Release Lock */
      OCU_UNLOCKPROCESS(LpBufferData->blBufferLock);                                                                    /* PRQA S 3432 # JV-01 */

      /* Waiting until the request is being executed */
      LulPollingTimes = Ocu_GulPollingTimes;
      do
      {
        LulPollingTimes--;                                                                                              /* PRQA S 3384, 3387 # JV-01, JV-01 */
      } while ((OCU_TRUE == LpBufferData->blSetRequest) && ((uint32)OCU_ZERO != LulPollingTimes));                      /* PRQA S 3415, 3416 # JV-01, JV-01 */
      /* Check if the request has been executed */
      if ((OCU_TRUE == LpBufferData->blSetRequest) && ((uint32)OCU_ZERO == LulPollingTimes))                            /* PRQA S 3415, 3416 # JV-01, JV-01 */
      {
        /* Report to Development Errors */
        (void)Det_ReportRuntimeError(OCU_MODULE_ID, OCU_INSTANCE_ID,
                                                                OCU_SET_RELATIVE_THRESHOLD_SID, OCU_E_REQUEST_ONGOING);
      }
      else
      {
        /* Load the counter value from buffer */
        LddSwCounterValue = LpBufferData->lddSwCounterValue;
        LddSwReferenceValue = LpBufferData->lddSwReferenceValue;
        LddSwThresholdValue = LpBufferData->lddSwThresholdValue;
      }
    }
    else
    {
      /* Exit global critical section */
      OCU_EXIT_CRITICAL_SECTION(OCU_RAM_DATA_PROTECTION_GLOBAL);
      /* Report to Development Errors */
      (void)Det_ReportRuntimeError(OCU_MODULE_ID, OCU_INSTANCE_ID,
                                                                  OCU_SET_RELATIVE_THRESHOLD_SID, OCU_E_REQUEST_FALSE);
    }
    #endif /* OCU_MULTI_CORE_SUPPORT == STD_ON */

    /* Check the counting direction */
    if (OCU_UPCOUNTING == Ocu_GblCountingDirection)                                                                     /* PRQA S 3416 # JV-01 */
    {
      /* In case of Reference Interval is inside this cycle */
      if (LddSwReferenceValue <= LddSwThresholdValue)
      {
        /* If the current counter is in the Reference Interval */
        if ((LddSwReferenceValue <= LddSwCounterValue ) && (LddSwCounterValue < LddSwThresholdValue))                   /* PRQA S 3415, 3416 # JV-01, JV-01 */
        {
          /* Return OCU_CM_IN_REF_INTERVAL */
          LenReturnResult = OCU_CM_IN_REF_INTERVAL;
        } /* else No action required */
      }
      else /* In case of Reference Interval is in the rollover of the counter */
      {
        /* If the current counter is in the Reference Interval */
        if ((LddSwReferenceValue <= LddSwCounterValue ) || (LddSwCounterValue < LddSwThresholdValue))                   /* PRQA S 3415, 3416 # JV-01, JV-01 */
        {
          /* Return OCU_CM_IN_REF_INTERVAL */
          LenReturnResult = OCU_CM_IN_REF_INTERVAL;
        } /* else No action required */
      } /* End of check Reference Interval is inside this cycle */
    }
    else /* Else OCU_DOWNCOUNTING */
    {
      /* In case of Reference Interval is inside this cycle */
      if (LddSwReferenceValue >= LddSwThresholdValue)
      {
        /* If the current counter is in the Reference Interval */
        if ((LddSwReferenceValue >= LddSwCounterValue ) && (LddSwCounterValue > LddSwThresholdValue))                   /* PRQA S 3415, 3416 # JV-01, JV-01 */
        {
          /* Return OCU_CM_IN_REF_INTERVAL */
          LenReturnResult = OCU_CM_IN_REF_INTERVAL;
        } /* else No action required */
      }
      else /* In case of Reference Interval is in the rollover of the counter */
      {
        /* If the current counter is in the Reference Interval */
        if ((LddSwReferenceValue >= LddSwCounterValue ) || (LddSwCounterValue > LddSwThresholdValue))                   /* PRQA S 3415, 3416 # JV-01, JV-01 */
        {
          /* Return OCU_CM_IN_REF_INTERVAL */
          LenReturnResult = OCU_CM_IN_REF_INTERVAL;
        } /* else No action required */
      } /* End of check Reference Interval is inside this cycle */
    } /* OCU_UPCOUNTING == Ocu_GblCountingDirection */
  } /* End of check if any DET error was reported */
  return LenReturnResult;
} /* End of API Ocu_SetPinAction */
#define OCU_STOP_SEC_PUBLIC_CODE_GLOBAL
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of OCU_SET_ABSOLUTE_THRESHOLD_API == STD_ON */
/***********************************************************************************************************************
** Function Name        : Ocu_CheckDetErrors
**
** Service ID           : None
**
** Description          : This API is used to report DET for invalid initialization and invalid channels in this file.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant
**
** Input Parameters     : LddChannel, LucApi_SID
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return parameter     : Std_ReturnType
**
** Preconditions        : None
**
** Global Variables     : Ocu_GblDriverStatus, Ocu_GpChannelConfig
**
** Functions invoked    : Det_ReportError
**
** Registers Used       : None
**
** Reference ID         : OCU_DUD_ACT_013
** Reference ID         : OCU_DUD_ACT_013_ERR001, OCU_DUD_ACT_013_ERR002, OCU_DUD_ACT_013_ERR003
***********************************************************************************************************************/
#if (OCU_DEV_ERROR_DETECT == STD_ON)
#define OCU_START_SEC_PRIVATE_CODE
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

STATIC FUNC(Std_ReturnType, OCU_PRIVATE_CODE) Ocu_CheckDetErrors(Ocu_ChannelType LddChannel, uint8 LucApi_SID)
{
  /* Declare the variable to store the DET return value */
  VAR(Std_ReturnType, AUTOMATIC) LddDetCheckResult;
  #if (OCU_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = OCU_ONE << (uint8)GetCoreID();
  #endif
  /* Initialized return value to E_OK */
  LddDetCheckResult = E_OK;
  /* Check if the OCU Driver is initialized properly */
  if (OCU_INITIALIZED != Ocu_GblDriverStatus)                                                                           /* PRQA S 3416 # JV-01 */
  {
    /* Report to DET module */
    (void)Det_ReportError(OCU_MODULE_ID, OCU_INSTANCE_ID, LucApi_SID, OCU_E_UNINIT);
    /* Set Return value */
    LddDetCheckResult = E_NOT_OK;
  }
  /* Check channel is in the valid range */
  else if ((Ocu_ChannelType)OCU_MAX_CHANNEL_ID_CONFIGURED < LddChannel)
  {
    /* Report to DET module */
    (void)Det_ReportError(OCU_MODULE_ID, OCU_INSTANCE_ID, LucApi_SID, OCU_E_PARAM_INVALID_CHANNEL);
    /* Set Return value */
    LddDetCheckResult = E_NOT_OK;
  }
  else
  {
    #if (OCU_MULTI_CORE_SUPPORT == STD_ON)
    /* Check that the target core isn't mapping into this channel */
    if (OCU_ZERO == (Ocu_GpChannelConfig[LddChannel].ucCoreIndex & LucCoreID))                                          /* PRQA S 0404, 3416 # JV-01, JV-01 */
    {
      /* Report Error to DET */
      (void)Det_ReportError(OCU_MODULE_ID, OCU_INSTANCE_ID, LucApi_SID, OCU_E_INVALID_CORE);
      LddDetCheckResult = E_NOT_OK;
    } /* Else no action required */
    #endif /* End of OCU_MULTI_CORE_SUPPORT == STD_ON */
  } /* End of Check if the OCU Driver is initialized */
  return (LddDetCheckResult);
} /* End of API Ocu_CheckDetErrors */

#define OCU_STOP_SEC_PRIVATE_CODE
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of (OCU_DEV_ERROR_DETECT == STD_ON) */
/***********************************************************************************************************************
** Function Name         : Ocu_SetStatus
**
** Service ID            : None
**
** Description           : This service changed the status of OCU.
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : LblStatusType
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : None
**
** Preconditions         : None
**
** Global Variables Used : Ocu_GblDriverStatus
**
** Functions Invoked     : None
**
** Registers Used        : None
**
** Reference ID          : OCU_DUD_ACT_014, OCU_DUD_ACT_014_GBL001
***********************************************************************************************************************/
#define OCU_START_SEC_PRIVATE_CODE
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
STATIC FUNC(void, OCU_PRIVATE_CODE) Ocu_SetStatus(boolean LblStatusType)
{
  /* Set the state of Ocu module */
  Ocu_GblDriverStatus = LblStatusType;
}
#define OCU_STOP_SEC_PRIVATE_CODE
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
