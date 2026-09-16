/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Icu.c                                                                                               */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains API implementations of Icu Driver Component.                                                    */
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
 * 2.4.1:  30/06/2025  : Remove SW-VERSION in file header
 * 2.4.0:  30/05/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.01 Release
 * 2.3.1:  31/03/2025  : As part of support QAC 11.6.0, following changes are made:
                         1. Add 3415 and remove 2814, 2824, 2844, 2934, 4304
 * 2.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release 
 * 2.1.2:  31/10/2024  : As part of support GTM HWIP into common code, following changes are made:
 *                       1. Update Icu_GetDutyCycleValues, Icu_GetTimeElapsed, Icu_GetInputState
 *                       2. Remove pEnableEdgeDetection and pDisableEdgeDetection, update code comment
 *                       3. Add init value for Icu_GpSignalMeasurementData
 *                       As part of postbuild variant support, following changes are made:
 *                       1. Change macro ICU_KERNEL_COREID to global variable Icu_GucKernalCoreId
 *                       2. Update Icu_Init to get the kernel core Id from input Icu_Config
 *                       3. Update software version. Remove redundant QAC message
 * 2.0.1:  19/10/2023  : Add QAC messages 3415, 4304. Remove QAC messages 2814, 2824, 2844, 2934, 0857.
 *         14/10/2023  : Change macro name from ICU_AR_R21_11_VERSION to ICU_AR_R22_11_VERSION
 *                       Change error order in API Icu_CheckWakeup()
 * 2.0.0:  03/08/2023  : Support Autosar multi-core distribution type 4
 *                       1. Memory section separate for Global and Local API
 *                       2. Update Global Critical Section 
 *                       3. Icu_Init, Icu_DeInit control API, Add det check for kernel core, clear buffer request
 *                       4. Icu_SetMode add det check for kernel core
 *                       5. Icu_DisableWakeup, Icu_EnableWakeup, Icu_DisableNotification, Icu_EnableNotification,
 *                          Icu_GetInputState, Icu_GetTimestampIndex, Icu_GetEdgeNumbers, Icu_GetTimeElapsed,
 *                          Icu_GetDutyCycleValues, Icu_GetInputLevel, Icu_GetTAUInCountValue add core det check will
 *                          support multi-core same as single core
 *                       6. Icu_SetActivationCondition, Icu_StartTimestamp, Icu_StopTimestamp, Icu_ResetEdgeCount,
 *                          Icu_EnableEdgeCount, Icu_DisableEdgeCount, Icu_EnableEdgeDetection, 
 *                          Icu_DisableEdgeDetection, Icu_StartSignalMeasurement, Icu_StopSignalMeasurement 
 *                          add core det check, separate code for multi-core and single-core, master core using master 
 *                          satellite concept, single core same as previous implementation
 * 1.4.5:  02/12/2022  : Add pre-processor ICU_AR_VERSION == ICU_AR_2111_VERSION for support AR21-11
 * 1.4.4:  17/11/2022  : Update "Input Parameters", "Global Variables", 
 *                       "Functions invoked" for all functions.
 *         16/06/2022  : Update QAC message and QAC header
 *         09/06/2022  : Add DET check when invoke Icu_StartSignalMeasurement, Icu_StopSignalMeasurement,
 *                       Icu_GetTimeElapsed, Icu_GetInputState with extra duty channel
 * 1.4.3:  23/05/2022  : Fix QAC header and message.
 *         09/05/2022  : Remove "else" statement when no action required; add QAC message 2004.
 *         17/04/2022  : Merge QAC message from U2Ax, E2x and U2Bx
 * 1.4.2:  02/03/2022  : Fix QAC header and message
 * 1.4.1:  18/10/2021  : Add QAC message 9.5.0
 *         15/09/2021  : Rename TimerChannelConfig to ChannelUserRegConfig
 *                       Update condition (ICU_ATU_TIMERA_UNIT_USED == STD_ON) || (ICU_ATU_TIMERC_UNIT_USED == STD_ON) 
 *                       to (ICU_ATU_TIMER_UNIT_USED == STD_ON)
 *                       Icu_SetMode: update condition "Check whether Channel is in progress"
 * 1.3.2:  30/08/2021  : Change from #include "Icu_MemMap.h" to #include "Icu_Mapping.h".
 *         23/08/2021  : Update pre-compile condition to raise runtime error ICU_E_NOT_STARTED in Icu_StopTimestamp
 *         20/08/2021  : Remove code segment of setting blTimestampingStarted in Icu_StopTimestamp
 * 1.3.1:  02/07/2021  : Add QAC message 9.5.0
 *                       Format source code to 120 characters
 *                       Improve Violation tag (remove START/END)
 * 1.3.0:  20/01/2021  : Changed CONSTP2CONST to P2CONST for argument ConfigPtr
 *                       in Icu_Init().
 *         12/11/2020  : Update IF condition of Icu_GetDutyCycleValues
 * 1.2.0:  17/07/2020  : Release
 * 1.1.0:  19/06/2020  : Release
 * 1.0.0:  25/03/2020  : Initial Version
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
/* Message (3:4304)    : An expression of 'essentially Boolean' type (%1s) is being cast to unsigned type '%2s'.      */
/* Rule                : MISRA C:2012 Rule-10.5                                                                       */
/* JV-01 Justification : This is accepted. This casting from boolean to unsigned type for values 0 and 1 does not     */
/*                       make data conflict.                                                                          */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:4342)    : An expression of 'essentially unsigned' type (%1s) is being cast to enum type '%2s'.         */
/* Rule                : MISRA C:2012 Rule-10.5, CWE Rule CWE-704                                                     */
/* JV-01 Justification : It is assigned to a variable with no conflict in the data.                                   */
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
#include "Icu.h"
/* Included for RAM variable declarations */
#include "Icu_Ram.h"
#if (ICU_MULTI_CORE_SUPPORT == STD_ON)
#include "Icu_Kernel.h"
#include "Os.h"
#endif
#if (ICU_AR_VERSION == ICU_AR_431_VERSION) || (ICU_AR_VERSION == ICU_AR_R22_11_VERSION)
/* Included for the declaration of Det_ReportRuntimeError() */
#include "Det.h"
#elif (ICU_AR_VERSION == ICU_AR_422_VERSION)
#if (ICU_DEV_ERROR_DETECT == STD_ON)
/* Included for the declaration of Det_ReportError() */
#include "Det.h"
#endif
#endif /*(ICU_AR_VERSION == ICU_AR_431_VERSION) || (ICU_AR_VERSION == ICU_AR_R22_11_VERSION) */

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define ICU_C_AR_RELEASE_MAJOR_VERSION    ICU_AR_RELEASE_MAJOR_VERSION_VALUE
#define ICU_C_AR_RELEASE_MINOR_VERSION    ICU_AR_RELEASE_MINOR_VERSION_VALUE
#define ICU_C_AR_RELEASE_REVISION_VERSION ICU_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define ICU_C_SW_MAJOR_VERSION            ICU_SW_MAJOR_VERSION_VALUE
#define ICU_C_SW_MINOR_VERSION            ICU_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (ICU_AR_RELEASE_MAJOR_VERSION != ICU_C_AR_RELEASE_MAJOR_VERSION)
  #error "Icu.c : Mismatch in Release Major Version"
#endif

#if (ICU_AR_RELEASE_MINOR_VERSION != ICU_C_AR_RELEASE_MINOR_VERSION)
  #error "Icu.c : Mismatch in Release Minor Version"
#endif

#if (ICU_AR_RELEASE_REVISION_VERSION != ICU_C_AR_RELEASE_REVISION_VERSION)
  #error "Icu.c : Mismatch in Release Revision Version"
#endif

#if (ICU_SW_MAJOR_VERSION != ICU_C_SW_MAJOR_VERSION)
  #error "Icu.c : Mismatch in Software Major Version"
#endif

#if (ICU_SW_MINOR_VERSION != ICU_C_SW_MINOR_VERSION)
  #error "Icu.c : Mismatch in Software Minor Version"
#endif

/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/
/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/
#define ICU_START_SEC_PRIVATE_CODE

#include "Icu_MemMap.h"

/* The prototype of function which is used in this file only */
STATIC FUNC(void, ICU_PRIVATE_CODE) Icu_SetDriverStatus(const boolean LblStatus);

#define ICU_STOP_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Icu_Init
**
** Service ID            : 0x00
**
** Description           : This API performs the initialization of the Icu Driver Component.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
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
** Global Variables      : Icu_GpChannelConfig, Icu_GpChannelUserRegConfig, Icu_GaaHWIPConfig, 
**                         Icu_GpChannelRamData, Icu_GenModuleMode, Icu_GulWakeupSource, Icu_GaaHwDepFunc, 
**                         Icu_GpTimeStampData, Icu_GpEdgeCountData, Icu_GpSignalMeasurementData
**                         Icu_GblDriverStatus.
**
** Functions invoked     : Det_ReportError, Icu_HW_Taud_UnitInit, Icu_HW_Tauj_UnitInit, Icu_HW_Taud_ChannelInit,
**                         Icu_HW_Tauj_ChannelInit, Icu_HW_Pin_ChannelInit, Icu_HW_Atu_UnitInit, Icu_HW_Atu_ChannelInit,
**                         Icu_SetDriverStatus
**
** Registers Used        : None
**
** Reference ID          : ICU_DUD_ACT_001, ICU_DUD_ACT_001_ERR001, ICU_DUD_ACT_001_ERR002, 
** Reference ID          : ICU_DUD_ACT_001_ERR003, ICU_DUD_ACT_001_ERR004, ICU_DUD_ACT_001_GBL010
** Reference ID          : ICU_DUD_ACT_001_GBL001, ICU_DUD_ACT_001_GBL002, ICU_DUD_ACT_001_GBL003
** Reference ID          : ICU_DUD_ACT_001_GBL005, ICU_DUD_ACT_001_GBL006, ICU_DUD_ACT_001_GBL007
** Reference ID          : ICU_DUD_ACT_001_GBL009, ICU_DUD_ACT_001_GBL004, ICU_DUD_ACT_001_GBL008
***********************************************************************************************************************/
#define ICU_START_SEC_PUBLIC_CODE_LOCAL
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_PUBLIC_CODE) Icu_Init(P2CONST(Icu_ConfigType, AUTOMATIC, ICU_APPL_CONST) ConfigPtr)                      /* PRQA S 1503 # JV-01 */
{
  /* Defining a pointer to the channel config parameters */
  P2CONST(Icu_ChannelConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannel;
  /* Defining a pointer to the channel timer config parameters */
  P2CONST(Icu_ChannelUserRegConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpTimerChannel;
  /* Local variable to store Measurement Mode */
  Icu_MeasurementModeType LddMeasurementMode;
  /* Local variable to store RAM index */
  uint8 LucIndex;
  /* Local variable to hold the channel number */
  volatile uint8 LucChannelNo;
  /* Local variable to hold the channel number */
  volatile uint8 LucUnitNo;
  /* Index of HW IP Type */
  volatile VAR(uint8, AUTOMATIC) LucHWIPType;
  #if (ICU_MULTI_CORE_SUPPORT == STD_ON)
  /* Local variable to hold the channel ram index */
  volatile uint8 LucChannelRamIndex;
  #endif
  #if (ICU_DEV_ERROR_DETECT == STD_ON)
  #if (ICU_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = (uint8)GetCoreID();
  #endif
  /* Check if the Configuration pointer is NULL */
  if (NULL_PTR == ConfigPtr)
  {
    /* Report Error to DET */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_INIT_SID, ICU_E_INIT_FAILED);
  }
  #if (ICU_ALREADY_INIT_DET_CHECK == STD_ON)
  /* Check if the ICU Driver is already initialized */
  else if (ICU_INITIALIZED == Icu_GblDriverStatus)                                                                      /* PRQA S 3416 # JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_INIT_SID, ICU_E_ALREADY_INITIALIZED);
  }
  #endif
  else
  #endif /* End of (ICU_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Check if the database is flashed on the target device */
    if (ICU_DBTOC_VALUE == (ConfigPtr->ulStartOfDbToc))
    {
      #if (ICU_MULTI_CORE_SUPPORT == STD_ON)
      /* Holds the kernal core ID in multicore */
      Icu_GucKernalCoreId = ConfigPtr->ucKernelCoreId;
      #if (ICU_DEV_ERROR_DETECT == STD_ON)
      /* Check if invoke on kernel core */
      if (Icu_GucKernalCoreId != LucCoreID)                                                                             /* PRQA S 3416 # JV-01 */
      {
        /* Report Error to DET */
        (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_INIT_SID, ICU_E_INVALID_CORE);
      }
      else
      #endif
      #endif
      {
        /* Update the global pointer with the first channel's configuration database address */
        Icu_GpChannelConfig =
                           (P2CONST(Icu_ChannelConfigType, ICU_VAR_NO_INIT, ICU_APPL_CONST)) ConfigPtr->pChannelConfig; /* PRQA S 0316 # JV-01 */
        /*  Update the global pointer with the first Timer channel's configuration database address */
        Icu_GpChannelUserRegConfig =
              (P2CONST(Icu_ChannelUserRegConfigType, ICU_VAR_NO_INIT, ICU_APPL_CONST))ConfigPtr->pChannelUserRegConfig; /* PRQA S 0316 # JV-01 */

        /* Update the global pointer with the first channel's ram address */
        Icu_GpChannelRamData = 
                     (P2VAR(volatile Icu_ChannelRamDataType, ICU_VAR_NO_INIT, ICU_CONFIG_DATA)) ConfigPtr->pRamAddress; /* PRQA S 0316 # JV-01 */
        #if (ICU_EDGE_COUNT_API == STD_ON)
        Icu_GpEdgeCountData = (P2VAR(volatile Icu_EdgeCountModeRamDatatype, ICU_VAR_NO_INIT, ICU_CONFIG_DATA))          /* PRQA S 0316 # JV-01 */
                                                                                       ConfigPtr->pEdgeCountRamAddress;
        #endif
        /* Update the global pointer with the first channel's address of Timestamp mode type channel's RAM data */
        #if (ICU_TIMESTAMP_API == STD_ON)
        Icu_GpTimeStampData = (P2VAR(volatile Icu_TimeStampChannelRamDataType, ICU_VAR_NO_INIT, ICU_APPL_CONST))        /* PRQA S 0316 # JV-01 */
                                                                                          ConfigPtr->pTimeStampAddress;
        #endif /* End of (ICU_TIMESTAMP_API == STD_ON) */
        /* Update the global pointer with the first channel's address of Signal Measurement mode */
        #if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)
        Icu_GpSignalMeasurementData = (P2VAR(volatile Icu_SignalMeasurementModeRamDataType, ICU_VAR_NO_INIT,            /* PRQA S 0316 # JV-01 */
                                                                    ICU_APPL_CONST))ConfigPtr->pSignalMeasureAddress;
        #endif
        for (LucChannelNo = ICU_ZERO; LucChannelNo < ICU_MAX_CHANNEL; LucChannelNo++)                                   /* PRQA S 3387, 3416 # JV-01, JV-01 */
        {
          /* Load the channel pointer */
          LpChannel = &Icu_GpChannelConfig[LucChannelNo];                                                               /* PRQA S 0404 # JV-01 */
          if ((ICU_HW_EXT_INTP != LpChannel->ucIcuChannelType) && (ICU_HW_EXT_IRQ != LpChannel->ucIcuChannelType))
          {
            /* Load the timer channel pointer */
            LpTimerChannel = &Icu_GpChannelUserRegConfig[LucChannelNo];                                                 /* PRQA S 0404 # JV-01 */
            /* Read the Measurement mode of the channel */
            LddMeasurementMode = (Icu_MeasurementModeType)LpChannel->ucIcuMeasurementMode;                              /* PRQA S 4342 # JV-01 */
            /* Check whether measurement mode is timestamp */
            if (ICU_MODE_TIMESTAMP == LddMeasurementMode)
            {
              /* Read the current activation edge from RAM */
              LucIndex = LpTimerChannel->ucRamDataIndex;
              /* Reset the flag to indicate that the timestamping is not started */
              Icu_GpTimeStampData[LucIndex].blTimestampingStarted = ICU_FALSE;
            } /* else No action required */
          } /* else No action required */
        } /* End of loop all channels */

        /* Invoke low level driver for Initializing the hardware */
        for (LucUnitNo = ICU_ZERO; LucUnitNo < ICU_TOTAL_HW_IP_CONFIG; LucUnitNo++)                                     /* PRQA S 3387, 3416 # JV-01, JV-01 */
        {
          /* Read the HWIP Type for given channel  */
          LucHWIPType = Icu_GaaHWIPConfig[LucUnitNo].ucIndex;
          if (NULL_PTR != Icu_GaaHwDepFunc[LucHWIPType]->pUnitInit)                                                     /* PRQA S 3416 # JV-01 */
          {
            /* Invoke low level driver for Deinitializing the hardware */
            Icu_GaaHwDepFunc[LucHWIPType]->pUnitInit(ConfigPtr);
          } /* else No action required */
        }

        for (LucChannelNo = (uint8)ICU_ZERO; LucChannelNo < (uint8)ICU_MAX_CHANNEL; LucChannelNo++)                     /* PRQA S 3387, 3416 # JV-01, JV-01 */
        {
          /* Read the HWIP Type for given channel */
          LucHWIPType = Icu_GpChannelConfig[LucChannelNo].ucIcuChannelType;                                             /* PRQA S 0404 # JV-01 */
          if (NULL_PTR != Icu_GaaHwDepFunc[LucHWIPType]->pChannelInit)                                                  /* PRQA S 3416 # JV-01 */
          {
            Icu_GaaHwDepFunc[LucHWIPType]->pChannelInit(LucChannelNo);                                                  /* PRQA S 0404 # JV-01 */
          } /* else No action required */
        } /* End loop */

        #if (ICU_MULTI_CORE_SUPPORT == STD_ON)
        /* Loop from max channel ID to zero */
        LucChannelNo = (uint8)ICU_MAX_CHANNEL;
        do
        {
          /* Loop till channel zero */
          LucChannelNo--;                                                                                               /* PRQA S 3384, 3387 # JV-01, JV-01 */
          /* Read the Icu mode for given channel */
          LddMeasurementMode = (Icu_MeasurementModeType)Icu_GpChannelConfig[LucChannelNo].ucIcuMeasurementMode;         /* PRQA S 0404, 4342 # JV-01, JV-01 */
          /* Read the ram data index for given channel */
          LucChannelRamIndex = Icu_GpChannelUserRegConfig[LucChannelNo].ucRamDataIndex;                                 /* PRQA S 0404 # JV-01 */

          /* Clear buffer request for Icu_SetActivationCondition */
          Icu_GaaSetActivationConditionBuffer[LucChannelNo].lddActivation = ICU_RISING_EDGE;
          Icu_GaaSetActivationConditionBuffer[LucChannelNo].blSetRequest = ICU_FALSE;
          Icu_GaaSetActivationConditionBuffer[LucChannelNo].blBufferLock = ICU_FALSE;

          /* Clear buffer request for each channel setting mode */
          switch (LddMeasurementMode)
          {
            #if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)
            case ICU_MODE_SIGNAL_MEASUREMENT:
            {
              /* Clear buffer request for Icu_StartSignalMeasurement, Icu_StopSignalMeasurement */
              Icu_GaaStartSignalMeasurementBuffer[LucChannelRamIndex].lddChannel = LucChannelNo;                        /* PRQA S 0404 # JV-01 */
              Icu_GaaStartSignalMeasurementBuffer[LucChannelRamIndex].blSetRequest = ICU_FALSE;
              Icu_GaaStartSignalMeasurementBuffer[LucChannelRamIndex].blBufferLock = ICU_FALSE;
              Icu_GaaStopSignalMeasurementBuffer[LucChannelRamIndex].lddChannel = LucChannelNo;                         /* PRQA S 0404 # JV-01 */
              Icu_GaaStopSignalMeasurementBuffer[LucChannelRamIndex].blSetRequest = ICU_FALSE;
              Icu_GaaStopSignalMeasurementBuffer[LucChannelRamIndex].blBufferLock = ICU_FALSE;
              break;
            }
            #endif

            #if (ICU_EDGE_DETECT_API == STD_ON)
            case ICU_MODE_SIGNAL_EDGE_DETECT:
            {
              /* Clear buffer request for Icu_EnableEdgeDetection, Icu_DisableEdgeDetection */
              Icu_GaaEnableEdgeDetectionBuffer[LucChannelRamIndex].lddChannel = LucChannelNo;                           /* PRQA S 0404 # JV-01 */
              Icu_GaaEnableEdgeDetectionBuffer[LucChannelRamIndex].blSetRequest = ICU_FALSE;
              Icu_GaaEnableEdgeDetectionBuffer[LucChannelRamIndex].blBufferLock = ICU_FALSE;
              Icu_GaaDisableEdgeDetectionBuffer[LucChannelRamIndex].lddChannel = LucChannelNo;                          /* PRQA S 0404 # JV-01 */
              Icu_GaaDisableEdgeDetectionBuffer[LucChannelRamIndex].blSetRequest = ICU_FALSE;
              Icu_GaaDisableEdgeDetectionBuffer[LucChannelRamIndex].blBufferLock = ICU_FALSE;
              break;
            }
            #endif

            #if (ICU_EDGE_COUNT_API == STD_ON)
            case ICU_MODE_EDGE_COUNTER:
            {
              /* Clear buffer request for Icu_ResetEdgeCount, Icu_EnableEdgeCount,Icu_DisableEdgeCount */
              Icu_GaaResetEdgeCountBuffer[LucChannelRamIndex].lddChannel = LucChannelNo;                                /* PRQA S 0404 # JV-01 */
              Icu_GaaResetEdgeCountBuffer[LucChannelRamIndex].blSetRequest = ICU_FALSE;
              Icu_GaaResetEdgeCountBuffer[LucChannelRamIndex].blBufferLock = ICU_FALSE;
              Icu_GaaEnableEdgeCountBuffer[LucChannelRamIndex].lddChannel = LucChannelNo;                               /* PRQA S 0404 # JV-01 */
              Icu_GaaEnableEdgeCountBuffer[LucChannelRamIndex].blSetRequest = ICU_FALSE;
              Icu_GaaEnableEdgeCountBuffer[LucChannelRamIndex].blBufferLock = ICU_FALSE;
              Icu_GaaDisableEdgeCountBuffer[LucChannelRamIndex].lddChannel = LucChannelNo;                              /* PRQA S 0404 # JV-01 */
              Icu_GaaDisableEdgeCountBuffer[LucChannelRamIndex].blSetRequest = ICU_FALSE;
              Icu_GaaDisableEdgeCountBuffer[LucChannelRamIndex].blBufferLock = ICU_FALSE;
              break;
            }
            #endif

            #if (ICU_TIMESTAMP_API == STD_ON)
            case ICU_MODE_TIMESTAMP:
            {
              /* Clear buffer request for Icu_StartTimestamp, Icu_StopTimestamp */
              Icu_GaaStartTimestampBuffer[LucChannelRamIndex].lddChannel = LucChannelNo;                                /* PRQA S 0404 # JV-01 */
              Icu_GaaStartTimestampBuffer[LucChannelRamIndex].lpBufferPtr = NULL_PTR;
              Icu_GaaStartTimestampBuffer[LucChannelRamIndex].lusBufferSize = (uint16)ICU_ZERO;
              Icu_GaaStartTimestampBuffer[LucChannelRamIndex].lusNotifyInterval = (uint16)ICU_ZERO;
              Icu_GaaStartTimestampBuffer[LucChannelRamIndex].blSetRequest = ICU_FALSE;
              Icu_GaaStartTimestampBuffer[LucChannelRamIndex].blBufferLock = ICU_FALSE;
              Icu_GaaStopTimestampBuffer[LucChannelRamIndex].lddChannel = LucChannelNo;                                 /* PRQA S 0404 # JV-01 */
              Icu_GaaStopTimestampBuffer[LucChannelRamIndex].blSetRequest = ICU_FALSE;
              Icu_GaaStopTimestampBuffer[LucChannelRamIndex].blBufferLock = ICU_FALSE;
              break;
            }
            #endif

            default: {
              /* Default do nothing */
              break;
            }
          } /* End of switch */
        } while ((uint8)ICU_ZERO != LucChannelNo);                                                                      /* PRQA S 3416 # JV-01 */
        #endif /* End of multi-core support */

        /* Set Icu Driver Mode as normal */
        Icu_GenModuleMode = ICU_MODE_NORMAL;

        #if (ICU_REPORT_WAKEUP_SOURCE == STD_ON)
        /* Set the wakeup source information as Zero*/
        Icu_GulWakeupSource = ICU_WAKEUP_INFO_INIT_VAL;
        #endif
        /* Set Icu Driver status as initialized */
        Icu_SetDriverStatus(ICU_INITIALIZED);
      }
    }
    else /* If there is no valid database is present */
    {
      #if (ICU_DEV_ERROR_DETECT == STD_ON)
      /* Report to DET */
      (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_INIT_SID, ICU_E_INVALID_DATABASE);
      #endif
    } /* End of (ConfigPtr->ulStartOfDbToc) == ICU_DBTOC_VALUE */
  } /* End of NULL_PTR == ConfigPtr */
} /* End of API Icu_Init */

#define ICU_STOP_SEC_PUBLIC_CODE_LOCAL
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Icu_DeInit
**
** Service ID            : 0x01
**
** Description           : This API performs the De-Initialization of the Icu
**                         Driver Component by making all the registers to the power on reset state.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Global Variables      : Icu_GblDriverStatus, Icu_GaaHwDepFunc, Icu_GaaHWIPConfig, Icu_GpChannelConfig.
**
** Functions invoked     : Det_ReportError, Icu_SetDriverStatus, Icu_HW_Atu_UnitDeInit, Icu_HW_Taud_UnitDeInit,
**                         Icu_HW_Tauj_UnitDeInit, Icu_HW_Taud_ChannelDeInit, Icu_HW_Tauj_ChannelDeInit, 
**                         Icu_HW_Atu_ChannelDeInit, Icu_HW_Pin_ChannelDeInit
**
** Registers Used        : None
**
** Reference ID          : ICU_DUD_ACT_002, ICU_DUD_ACT_002_ERR001, ICU_DUD_ACT_002_ERR002, ICU_DUD_ACT_002_GBL001
***********************************************************************************************************************/
#if (ICU_DE_INIT_API == STD_ON)
#define ICU_START_SEC_PUBLIC_CODE_LOCAL
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_PUBLIC_CODE) Icu_DeInit(void)                                                                            /* PRQA S 1503 # JV-01 */
{
  /* Declare a Local variable to Timer Type */
  volatile uint8 LucUnitNo;
  /* Local variable to hold the channel number */
  volatile uint8 LucChannelNo;
  /* Index of HW IP Type */
  volatile VAR(uint8, AUTOMATIC) LucHWIPType;
  #if (ICU_MULTI_CORE_SUPPORT == STD_ON)
  /* Local variable to hold the channel ram index */
  volatile uint8 LucChannelRamIndex;
  /* Local variable to hold the channel mode */
  volatile Icu_MeasurementModeType LddChannelMeasurementMode;
  #endif
  #if (ICU_DEV_ERROR_DETECT == STD_ON)
  #if (ICU_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = (uint8)GetCoreID();
  #endif
  /* Check if the Icu Module is not initialized */
  if (ICU_INITIALIZED != Icu_GblDriverStatus)                                                                           /* PRQA S 3416 # JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_DEINIT_SID, ICU_E_UNINIT);
  }
  #if (ICU_MULTI_CORE_SUPPORT == STD_ON)
  /* Check if control API wasn't executed on Master Core */
  else if (Icu_GucKernalCoreId != LucCoreID)                                                                            /* PRQA S 3416 # JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_DEINIT_SID, ICU_E_INVALID_CORE);
  }
  #endif
  else
  #endif /* End of (ICU_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Set Icu Driver status as un-initialized */
    Icu_SetDriverStatus(ICU_UNINITIALIZED);
    #if (ICU_MULTI_CORE_SUPPORT == STD_ON)
    /* Clear the kernal core ID in multicore */
    Icu_GucKernalCoreId = ICU_ZERO;
    #endif
    /* Invoke low-level driver for De-Initializing the hardware */
    for (LucUnitNo = ICU_ZERO; LucUnitNo < ICU_TOTAL_HW_IP_CONFIG; LucUnitNo++)                                         /* PRQA S 3387, 3416 # JV-01, JV-01 */
    {
      /* Read the HWIP Type for the given channel */
      LucHWIPType = Icu_GaaHWIPConfig[LucUnitNo].ucIndex;
      if (NULL_PTR != Icu_GaaHwDepFunc[LucHWIPType]->pUnitDeInit)                                                       /* PRQA S 3416 # JV-01 */
      {
        /* Invoke low-level driver for Deinitializing the hardware */
        Icu_GaaHwDepFunc[LucHWIPType]->pUnitDeInit();
      } /* else No action required */
    } /* End of the loop */

    for (LucChannelNo = ICU_ZERO; LucChannelNo < ICU_MAX_CHANNEL; LucChannelNo++)                                       /* PRQA S 3387, 3416 # JV-01, JV-01 */
    {
      /* Read the HWIP Type for given channel */
      LucHWIPType = Icu_GpChannelConfig[LucChannelNo].ucIcuChannelType;                                                 /* PRQA S 0404 # JV-01 */
      if (NULL_PTR != Icu_GaaHwDepFunc[LucHWIPType]->pChannelDeInit)                                                    /* PRQA S 3416 # JV-01 */
      {
        /* Invoke low-level driver for Deinitializing the hardware */
        Icu_GaaHwDepFunc[LucHWIPType]->pChannelDeInit(LucChannelNo);                                                    /* PRQA S 0404 # JV-01 */
      } /* else No action required */

      #if (ICU_MULTI_CORE_SUPPORT == STD_ON)
      /* Read the Icu mode for given channel */
      LddChannelMeasurementMode = (Icu_MeasurementModeType)Icu_GpChannelConfig[LucChannelNo].ucIcuMeasurementMode;      /* PRQA S 0404, 4342 # JV-01, JV-01 */
      /* Read the ram data index for given channel */
      LucChannelRamIndex = Icu_GpChannelUserRegConfig[LucChannelNo].ucRamDataIndex;                                     /* PRQA S 0404 # JV-01 */

      /* Clear buffer request for Icu_SetActivationCondition */
      Icu_GaaSetActivationConditionBuffer[LucChannelNo].lddActivation = ICU_RISING_EDGE;
      Icu_GaaSetActivationConditionBuffer[LucChannelNo].blSetRequest = ICU_FALSE;
      Icu_GaaSetActivationConditionBuffer[LucChannelNo].blBufferLock = ICU_FALSE;

      /* Clear buffer request for each channel setting mode */
      switch (LddChannelMeasurementMode)
      {
        #if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)
        case ICU_MODE_SIGNAL_MEASUREMENT:
        {
          /* Clear buffer request for Icu_StartSignalMeasurement, Icu_StopSignalMeasurement */
          Icu_GaaStartSignalMeasurementBuffer[LucChannelRamIndex].lddChannel = (uint8)ICU_ZERO;
          Icu_GaaStartSignalMeasurementBuffer[LucChannelRamIndex].blSetRequest = ICU_FALSE;
          Icu_GaaStartSignalMeasurementBuffer[LucChannelRamIndex].blBufferLock = ICU_FALSE;
          Icu_GaaStopSignalMeasurementBuffer[LucChannelRamIndex].lddChannel = (uint8)ICU_ZERO;
          Icu_GaaStopSignalMeasurementBuffer[LucChannelRamIndex].blSetRequest = ICU_FALSE;
          Icu_GaaStopSignalMeasurementBuffer[LucChannelRamIndex].blBufferLock = ICU_FALSE;
          break;
        }
        #endif

        #if (ICU_EDGE_DETECT_API == STD_ON)
        case ICU_MODE_SIGNAL_EDGE_DETECT:
        {
          /* Clear buffer request for Icu_EnableEdgeDetection, Icu_DisableEdgeDetection */
          Icu_GaaEnableEdgeDetectionBuffer[LucChannelRamIndex].lddChannel = (uint8)ICU_ZERO;
          Icu_GaaEnableEdgeDetectionBuffer[LucChannelRamIndex].blSetRequest = ICU_FALSE;
          Icu_GaaEnableEdgeDetectionBuffer[LucChannelRamIndex].blBufferLock = ICU_FALSE;
          Icu_GaaDisableEdgeDetectionBuffer[LucChannelRamIndex].lddChannel = (uint8)ICU_ZERO;
          Icu_GaaDisableEdgeDetectionBuffer[LucChannelRamIndex].blSetRequest = ICU_FALSE;
          Icu_GaaDisableEdgeDetectionBuffer[LucChannelRamIndex].blBufferLock = ICU_FALSE;
          break;
        }
        #endif

        #if (ICU_EDGE_COUNT_API == STD_ON)
        case ICU_MODE_EDGE_COUNTER:
        {
          /* Clear buffer request for Icu_ResetEdgeCount, Icu_EnableEdgeCount,Icu_DisableEdgeCount */
          Icu_GaaResetEdgeCountBuffer[LucChannelRamIndex].lddChannel = (uint8)ICU_ZERO;
          Icu_GaaResetEdgeCountBuffer[LucChannelRamIndex].blSetRequest = ICU_FALSE;
          Icu_GaaResetEdgeCountBuffer[LucChannelRamIndex].blBufferLock = ICU_FALSE;
          Icu_GaaEnableEdgeCountBuffer[LucChannelRamIndex].lddChannel = (uint8)ICU_ZERO;
          Icu_GaaEnableEdgeCountBuffer[LucChannelRamIndex].blSetRequest = ICU_FALSE;
          Icu_GaaEnableEdgeCountBuffer[LucChannelRamIndex].blBufferLock = ICU_FALSE;
          Icu_GaaDisableEdgeCountBuffer[LucChannelRamIndex].lddChannel = (uint8)ICU_ZERO;
          Icu_GaaDisableEdgeCountBuffer[LucChannelRamIndex].blSetRequest = ICU_FALSE;
          Icu_GaaDisableEdgeCountBuffer[LucChannelRamIndex].blBufferLock = ICU_FALSE;
          break;
        }
        #endif

        #if (ICU_TIMESTAMP_API == STD_ON)
        case ICU_MODE_TIMESTAMP:
        {
          /* Clear buffer request for Icu_StartTimestamp, Icu_StopTimestamp */
          Icu_GaaStartTimestampBuffer[LucChannelRamIndex].lddChannel = (uint8)ICU_ZERO;
          Icu_GaaStartTimestampBuffer[LucChannelRamIndex].lpBufferPtr = NULL_PTR;
          Icu_GaaStartTimestampBuffer[LucChannelRamIndex].lusBufferSize = (uint16)ICU_ZERO;
          Icu_GaaStartTimestampBuffer[LucChannelRamIndex].lusNotifyInterval = (uint16)ICU_ZERO;
          Icu_GaaStartTimestampBuffer[LucChannelRamIndex].blSetRequest = ICU_FALSE;
          Icu_GaaStartTimestampBuffer[LucChannelRamIndex].blBufferLock = ICU_FALSE;
          Icu_GaaStopTimestampBuffer[LucChannelRamIndex].lddChannel = (uint8)ICU_ZERO;
          Icu_GaaStopTimestampBuffer[LucChannelRamIndex].blSetRequest = ICU_FALSE;
          Icu_GaaStopTimestampBuffer[LucChannelRamIndex].blBufferLock = ICU_FALSE;
          break;
        }
        #endif

        default: {
          /* Default do nothing */
          break;
        }
      }
      #endif /* End of multi-core support */
    } /* End of the loop */
  } /* End of ICU_INITIALIZED != Icu_GblDriverStatus */
} /* End of API Icu_DeInit */

#define ICU_STOP_SEC_PUBLIC_CODE_LOCAL
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of (ICU_DE_INIT_API == STD_ON) */
/***********************************************************************************************************************
** Function Name         : Icu_SetMode
**
** Service ID            : 0x02
**
** Description           : This API service will set the operation mode of the Icu Driver.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : Mode
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : The Icu Driver must be initialized, ICU_SET_MODE_API must be STD_ON
**
** Global Variables      : Icu_GblDriverStatus, Icu_GpChannelRamData, Icu_GenModuleMode, Icu_GpChannelConfig, 
**                         Icu_GaaHwDepFunc.
**
** Functions invoked     : Det_ReportError, Icu_HW_SetMode
**
** Registers Used        : None
**
** Reference ID          : ICU_DUD_ACT_003, ICU_DUD_ACT_003_ERR001, ICU_DUD_ACT_003_ERR002
** Reference ID          : ICU_DUD_ACT_003_ERR003, ICU_DUD_ACT_003_ERR004, ICU_DUD_ACT_003_GBL001
***********************************************************************************************************************/
#if (ICU_SET_MODE_API == STD_ON)
#define ICU_START_SEC_PUBLIC_CODE_LOCAL
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_PUBLIC_CODE) Icu_SetMode(Icu_ModeType Mode)                                                              /* PRQA S 1503 # JV-01 */
{
  /* Local variable to loop through the channels */
  Icu_ChannelType LucChannelNo;
  /* Defining a pointer to the channel config parameters */
  P2CONST(Icu_ChannelConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannel;
  /* Declare a Local variable to Timer Type */
  volatile uint8 LucTimerType;

  #if (ICU_DEV_ERROR_DETECT == STD_ON)
  /* Local variable to hold the DET value */
  Std_ReturnType LddDetCheckResult;
  #if (ICU_BUSY_OPERATION_DET_CHECK == STD_ON)
  /* Local variable to store running operation */
  boolean LblRunningOperation;
  #endif
  #if (ICU_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = (uint8)GetCoreID();
  #endif
  /* Initial value for Det check */
  LddDetCheckResult = E_OK;
  /* Check if the Icu Module is not initialized */
  if (ICU_INITIALIZED != Icu_GblDriverStatus)                                                                           /* PRQA S 3416 # JV-01 */
  {
    /* Report Error to Det */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_SET_MODE_SID, ICU_E_UNINIT);
    LddDetCheckResult = E_NOT_OK;
  }
  else if ((ICU_MODE_NORMAL != Mode) && (ICU_MODE_SLEEP != Mode))
  {
    /* Report Error to Det */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_SET_MODE_SID, ICU_E_PARAM_MODE);
    LddDetCheckResult = E_NOT_OK;
  }
  #if (ICU_MULTI_CORE_SUPPORT == STD_ON)
  /* Check if control API wasn't executed on Master Core */
  else if (Icu_GucKernalCoreId != LucCoreID)                                                                            /* PRQA S 3416 # JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_SET_MODE_SID, ICU_E_INVALID_CORE);
    LddDetCheckResult = E_NOT_OK;
  }
  #endif
  #if (ICU_BUSY_OPERATION_DET_CHECK == STD_ON)
  /* Check if any DET was reported */
  else
  {
    LblRunningOperation = ICU_FALSE;
    LucChannelNo = ICU_ZERO;
    do
    {
      /* Check whether Channel is in progress */
      if (((uint8)ICU_TRUE == (uint8)Icu_GpChannelRamData[LucChannelNo].ucChannelRunning)                               /* PRQA S 0404, 3416, 4304 # JV-01, JV-01, JV-01 */
      #if ((ICU_ENABLE_WAKEUP_API == STD_ON) || (ICU_NOTIFY_WAKEUP_INTERRUPT == STD_ON))
          && ((uint8)ICU_FALSE == (uint8)Icu_GpChannelRamData[LucChannelNo].ucWakeupEnable)                             /* PRQA S 3415, 3416, 4304 # JV-01, JV-01, JV-01 */
      #endif
      )
      {
        /* Update running operation as TRUE */
        LblRunningOperation = ICU_TRUE;
      } /* else No action required */
      /* Increment the pointer to point to the next channel */
      LucChannelNo++;                                                                                                   /* PRQA S 3383 # JV-01 */
    } while ((LucChannelNo < (uint8)ICU_MAX_CHANNEL) && (ICU_TRUE != LblRunningOperation));

    if ((ICU_MODE_SLEEP == Mode) && (ICU_TRUE == LblRunningOperation))
    {
      /* Report Error to Det */
      (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_SET_MODE_SID, ICU_E_BUSY_OPERATION);
      LddDetCheckResult = E_NOT_OK;
    } /* else No action required */
  } /* End of Check if the Icu Module is not initialized */
  #endif /* End of (ICU_BUSY_OPERATION_DET_CHECK == STD_ON) */
  /* Check if any DET was reported */
  if (E_OK == LddDetCheckResult)
  #endif /* End of (ICU_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Set operation mode to SLEEP provided there is no running operation */
    for (LucChannelNo = (uint8)ICU_ZERO; LucChannelNo < (uint8)ICU_MAX_CHANNEL; LucChannelNo++)
    {
      /* Updating the channel config parameter to the current channel */
      LpChannel = &Icu_GpChannelConfig[LucChannelNo];
      /* Read the Timer Type for the given channel  */
      LucTimerType = LpChannel->ucIcuChannelType;
      if (NULL_PTR != Icu_GaaHwDepFunc[LucTimerType]->pSetMode)                                                         /* PRQA S 3416 # JV-01 */
      {
        Icu_GaaHwDepFunc[LucTimerType]->pSetMode(LucChannelNo, Mode);
      } /* else No action required */
    }
    /* Update the ICU Driver Mode */
    Icu_GenModuleMode = Mode;
  } /* else No action required */
} /* End of API Icu_SetMode */

#define ICU_STOP_SEC_PUBLIC_CODE_LOCAL
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of (ICU_SET_MODE_API == STD_ON) */

/***********************************************************************************************************************
** Function Name        : Icu_DisableWakeup
**
** Service ID           : 0x03
**
** Description          : This API service will disable the wakeup interrupt of
**                        the requested Icu channel. The requested channel must be wake-up capable.
**
** Sync/Async           : Synchronous
**
** Reentrancy           : Reentrant
**
** Input Parameters     : Channel
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return parameter     : None
**
** Preconditions        : The Icu Driver must be initialized, ICU_DISABLE_WAKEUP_API must be STD_ON
**
** Global Variables     : Icu_GblDriverStatus, Icu_GpChannelConfig, Icu_GpChannelRamData, Icu_GulWakeupSource.
**
** Functions invoked    : Det_ReportError
**
** Registers Used       : None
**
** Reference ID          : ICU_DUD_ACT_004_CRT001, ICU_DUD_ACT_004_CRT002, ICU_DUD_ACT_004_ERR001 ICU_DUD_ACT_004_ERR002
** Reference ID          : ICU_DUD_ACT_004, ICU_DUD_ACT_004_ERR003, ICU_DUD_ACT_004_ERR004
** Reference ID          : ICU_DUD_ACT_004_GBL001, ICU_DUD_ACT_004_GBL002
***********************************************************************************************************************/

#if (ICU_DISABLE_WAKEUP_API == STD_ON)
#define ICU_START_SEC_PUBLIC_CODE_GLOBAL
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(void, ICU_PUBLIC_CODE) Icu_DisableWakeup(Icu_ChannelType Channel)                                                  /* PRQA S 1503 # JV-01 */
{
  #if (ICU_DEV_ERROR_DETECT == STD_ON)
  #if (ICU_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = ICU_ONE << (uint8)GetCoreID();
  #endif
  /* Check if the Icu Module is not initialized */
  if (ICU_INITIALIZED != Icu_GblDriverStatus)                                                                           /* PRQA S 3416 # JV-01 */
  {
    /* Report Error to Det */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_DISABLE_WAKEUP_SID, ICU_E_UNINIT);
  }
  else if (ICU_MAX_CHANNEL_ID_CONFIGURED < Channel)
  {
    /* Report Error to Det */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_DISABLE_WAKEUP_SID, ICU_E_PARAM_CHANNEL);
  }
  else if ((uint8)ICU_FALSE == Icu_GpChannelConfig[Channel].ucIcuWakeupCapability)                                      /* PRQA S 3416, 4304 # JV-01, JV-01 */
  {
    /* Report Error to Det */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_DISABLE_WAKEUP_SID, ICU_E_PARAM_CHANNEL);
  }
  #if (ICU_MULTI_CORE_SUPPORT == STD_ON)
  /* Check that the target core is mapping into this channel */
  else if (ICU_ZERO == (Icu_GpChannelConfig[Channel].ucCoreIndex & LucCoreID))                                          /* PRQA S 0404, 3416 # JV-01, JV-01 */
  {
    /* Report to Development Errors */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_DISABLE_WAKEUP_SID, ICU_E_INVALID_CORE);
  }
  #endif
  else
  #endif /* End of (ICU_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Get the spinlock */
    ICU_ENTER_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
    /* Store the disabled wakeup status into RAM */
    Icu_GpChannelRamData[Channel].ucWakeupEnable = (uint8)ICU_FALSE;                                                    /* PRQA S 4304 # JV-01 */
    #if (ICU_REPORT_WAKEUP_SOURCE == STD_ON)
    /* Set the wakeup source information */
    Icu_GulWakeupSource = (Icu_GulWakeupSource &
                  (~(EcuM_WakeupSourceType)(ICU_DOUBLE_ONE << Icu_GpChannelConfig[Channel].ucEcuMChannelWakeupInfo)));
    #endif
    /* Release the spinlock */
    ICU_EXIT_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
  } /* End of ICU_INITIALIZED != Icu_GblDriverStatus */
} /* End of API Icu_DisableWakeup */

#define ICU_STOP_SEC_PUBLIC_CODE_GLOBAL
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of (ICU_DISABLE_WAKEUP_API == STD_ON) */

/***********************************************************************************************************************
** Function Name        : Icu_EnableWakeup
**
** Service ID           : 0x04
**
** Description          : This API service will enable the wakeup interrupt of
**                        the requested Icu channel. The requested channel must be wake-up capable.
**
** Sync/Async           : Synchronous
**
** Reentrancy           : Reentrant
**
** Input Parameters     : Channel
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return parameter     : None
**
** Preconditions        : The Icu Driver must be initialized, ICU_ENABLE_WAKEUP_API must be STD_ON
**
** Global Variables     : Icu_GblDriverStatus, Icu_GpChannelRamData,
**                        Icu_GpChannelConfig, Icu_GulWakeupSource, Icu_GenModuleMode.
**
** Functions invoked    : Det_ReportError.
**
** Registers Used       : None
**
** Reference ID         : ICU_DUD_ACT_005, ICU_DUD_ACT_005_CRT001, ICU_DUD_ACT_005_CRT002, ICU_DUD_ACT_005_ERR001
** Reference ID         : ICU_DUD_ACT_005_ERR002, ICU_DUD_ACT_005_ERR003, ICU_DUD_ACT_005_GBL001, ICU_DUD_ACT_005_GBL002
** Reference ID         : ICU_DUD_ACT_005_ERR004
***********************************************************************************************************************/
#if (ICU_ENABLE_WAKEUP_API == STD_ON)
#define ICU_START_SEC_PUBLIC_CODE_GLOBAL
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_PUBLIC_CODE) Icu_EnableWakeup(Icu_ChannelType Channel)                                                   /* PRQA S 1503 # JV-01 */
{
  #if (ICU_DEV_ERROR_DETECT == STD_ON)
  #if (ICU_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = ICU_ONE << (uint8)GetCoreID();
  #endif
  /* Check if the Icu Module is not initialized */
  if (ICU_INITIALIZED != Icu_GblDriverStatus)                                                                           /* PRQA S 3416 # JV-01 */
  {
    /* Report Error to Det */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_ENABLE_WAKEUP_SID, ICU_E_UNINIT);
  } /* End of ICU_INITIALIZED != Icu_GblDriverStatus */
  else if (ICU_MAX_CHANNEL_ID_CONFIGURED < Channel)
  {
    /* Report Error to Det */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_ENABLE_WAKEUP_SID, ICU_E_PARAM_CHANNEL);
  }
  else if ((uint8)ICU_FALSE == Icu_GpChannelConfig[Channel].ucIcuWakeupCapability)                                      /* PRQA S 3416, 4304 # JV-01, JV-01 */
  {
    /* Report Error to Det */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_ENABLE_WAKEUP_SID, ICU_E_PARAM_CHANNEL);
  }
  #if (ICU_MULTI_CORE_SUPPORT == STD_ON)
  /* Check that the target core is mapping into this channel */
  else if (ICU_ZERO == (Icu_GpChannelConfig[Channel].ucCoreIndex & LucCoreID))                                          /* PRQA S 0404, 3416 # JV-01, JV-01 */
  {
    /* Report to Development Errors */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_ENABLE_WAKEUP_SID, ICU_E_INVALID_CORE);
  }
  #endif
  else
  #endif /* End of (ICU_DEV_ERROR_DETECT == STD_ON) */
  {
    if (ICU_MODE_NORMAL == Icu_GenModuleMode)
    {
      /* Get the spinlock */
      ICU_ENTER_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
      /* Store the enabled wakeup status into RAM */
      Icu_GpChannelRamData[Channel].ucWakeupEnable = (uint8)ICU_TRUE;                                                   /* PRQA S 4304 # JV-01 */
      #if (ICU_REPORT_WAKEUP_SOURCE == STD_ON)
      /* Set the wakeup source information */
      Icu_GulWakeupSource = (Icu_GulWakeupSource | ((EcuM_WakeupSourceType)ICU_DOUBLE_ONE
                                                              << Icu_GpChannelConfig[Channel].ucEcuMChannelWakeupInfo));
      #endif
      /* Release the spinlock */
      ICU_EXIT_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
    } /* else No action required */
  } /* End of ICU_INITIALIZED != Icu_GblDriverStatus */
} /* End of API Icu_EnableWakeup */

#define ICU_STOP_SEC_PUBLIC_CODE_GLOBAL
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of (ICU_ENABLE_WAKEUP_API == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Icu_CheckWakeup
**
** Service ID            : 0x15
**
** Description           : This API checks the wakeup notification for a particular channel
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : WakeupSource
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : Icu_Init must be called before this function, ICU_REPORT_WAKEUP_SOURCE must be STD_ON
**
** Global Variables      : Icu_GblDriverStatus, Icu_GpChannelRamData, Icu_GpChannelConfig.
**
** Functions invoked     : Det_ReportError, EcuM_SetWakeupEvent.
**
** Registers Used        : None
**
** Reference ID         : ICU_DUD_ACT_022, ICU_DUD_ACT_022_ERR001, ICU_DUD_ACT_022_ERR002, ICU_DUD_ACT_022_GBL001
***********************************************************************************************************************/
#if ((ICU_WAKEUP_FUNCTIONALITY_API == STD_ON) && (ICU_REPORT_WAKEUP_SOURCE == STD_ON))
#define ICU_START_SEC_PUBLIC_CODE_LOCAL
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_PUBLIC_CODE) Icu_CheckWakeup(EcuM_WakeupSourceType WakeupSource)                                         /* PRQA S 1503 # JV-01 */
{
  /* Defining a pointer to the channel config parameters */
  P2CONST(Icu_ChannelConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannel;
  /* Local variable to hold the wakeup occurrence */
  boolean LblWakeupOccurrence;
  /* Local variable to hold the channel number */
  uint32 LulChannelNo;

  #if (ICU_DEV_ERROR_DETECT == STD_ON)
  #if (ICU_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = (uint8)GetCoreID();
  #endif
  /* Check if the ICU Driver is initialized properly */
  if (ICU_INITIALIZED != Icu_GblDriverStatus)                                                                           /* PRQA S 3416 # JV-01 */
  {
    /* Report to DET */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_CHECK_WAKEUP_SID, ICU_E_UNINIT);
  }
  #if (ICU_MULTI_CORE_SUPPORT == STD_ON)
  /* Check if control API wasn't executed on Master Core */
  else if (Icu_GucKernalCoreId != LucCoreID)                                                                            /* PRQA S 3416 # JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_CHECK_WAKEUP_SID, ICU_E_INVALID_CORE);
  }
  #endif /* End of ICU_MULTI_CORE_SUPPORT == STD_ON */
  else
  #endif /* End of ICU_DEV_ERROR_DETECT == STD_ON */
  {
    /* Set initial value */
    LulChannelNo = (uint32)ICU_ZERO;
    /* Load the channel pointer */
    LpChannel = &Icu_GpChannelConfig[LulChannelNo];

    do
    {
      /* Save the Wakeup status into the local variable */
      LblWakeupOccurrence = Icu_GpChannelRamData[LulChannelNo].blWakeupOccurrence;                                      /* PRQA S 0404 # JV-01 */

      /* Check if the wakeup is occurred */
      if ((((EcuM_WakeupSourceType)(ICU_DOUBLE_ONE << LpChannel->ucEcuMChannelWakeupInfo)) == WakeupSource) &&
                          (ICU_TRUE == LblWakeupOccurrence) && (ICU_NOWAKEUP != LpChannel->ucEcuMChannelWakeupInfo))
      {
        /* Reset wakeup flag for Channel */
        Icu_GpChannelRamData[LulChannelNo].blWakeupOccurrence = ICU_FALSE;
        /* Invoke the EcuM Set Wakeup API */
        EcuM_SetWakeupEvent(WakeupSource);
        /* Update the Channel No with the maximum number of Channel configured to break */
        LulChannelNo = (uint32)ICU_MAX_CHANNEL;
      } /* End of (Icu_GulWakeupSource & WakeupSource) == WakeupSource */
      else
      {
        /* Increment pointer to point to next Channel */
        LpChannel++;
        /* Increment Channel ID count */
        LulChannelNo++;                                                                                                 /* PRQA S 3383 # JV-01 */
      }
    } while ((uint32)ICU_MAX_CHANNEL > LulChannelNo);
  } /* End of ICU_INITIALIZED == Icu_GblDriverStatus */
} /* End of API Icu_CheckWakeup */

#define ICU_STOP_SEC_PUBLIC_CODE_LOCAL
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* #if ((ICU_WAKEUP_FUNCTIONALITY_API == STD_ON) && (ICU_REPORT_WAKEUP_SOURCE == STD_ON)) */

/***********************************************************************************************************************
** Function Name         : Icu_SetActivationCondition
**
** Service ID            : 0x05
**
** Description           : This API service will set the activation edge
**                         according to the Activation parameter for the given channel.
**
** Sync/Async            : Synchronous (Single-core) / Asynchronous (Multi-core)
**
** Reentrancy            : Reentrant
**
** Input Parameters      : Channel, Activation
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : The Icu Driver must be initialized.
**
** Global Variables      : Icu_GpChannelConfig, Icu_GblDriverStatus, Icu_GaaHwDepFunc.
**
** Functions invoked     : Det_ReportError, Icu_HW_Taud_SetActivation, Icu_HW_Tauj_SetActivation,
**                         Icu_HW_Atu_SetActivation, Icu_HW_Pin_SetActivation
**
** Registers Used        : None
**
** Reference ID          : ICU_DUD_ACT_006, ICU_DUD_ACT_006_ERR001, ICU_DUD_ACT_006_ERR004, ICU_DUD_ACT_006_CRT001
** Reference ID          : ICU_DUD_ACT_006_ERR002, ICU_DUD_ACT_006_ERR003, ICU_DUD_ACT_006_ERR005
** Reference ID          : ICU_DUD_ACT_006_ERR006, ICU_DUD_ACT_006_CRT002
***********************************************************************************************************************/
#define ICU_START_SEC_PUBLIC_CODE_GLOBAL
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_PUBLIC_CODE) Icu_SetActivationCondition(Icu_ChannelType Channel, Icu_ActivationType Activation)          /* PRQA S 1503 # JV-01 */
{
  #if (ICU_MULTI_CORE_SUPPORT == STD_OFF)
  /* Declare a Local variable to Timer Type */
  volatile uint8 LucHWIPType;
  /* Defining a pointer to the channel config parameters */
  P2CONST(Icu_ChannelConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannel;
  #endif
  #if (ICU_DEV_ERROR_DETECT == STD_ON)
  #if (ICU_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = ICU_ONE << (uint8)GetCoreID();
  #endif
  /* Check if the Icu Module is not initialized */
  if (ICU_INITIALIZED != Icu_GblDriverStatus)                                                                           /* PRQA S 3416 # JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_SET_ACTIVATION_CONDITION_SID, ICU_E_UNINIT);
  }
  else if (ICU_MAX_CHANNEL_ID_CONFIGURED < Channel)
  {
    /* Report Error to DET */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_SET_ACTIVATION_CONDITION_SID, ICU_E_PARAM_CHANNEL);
  }
  else if ((uint8)ICU_MODE_SIGNAL_MEASUREMENT == Icu_GpChannelConfig[Channel].ucIcuMeasurementMode)                     /* PRQA S 3416 # JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_SET_ACTIVATION_CONDITION_SID, ICU_E_PARAM_CHANNEL);
  }
  /* Check if the activation edge other than Rising Falling or Both edges */
  else if ((ICU_FALLING_EDGE != Activation) && (ICU_RISING_EDGE != Activation) && (ICU_BOTH_EDGES != Activation))
  {
    /* Report Error to DET */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_SET_ACTIVATION_CONDITION_SID, ICU_E_PARAM_ACTIVATION);
  }
  #if (ICU_MULTI_CORE_SUPPORT == STD_ON)
  /* Check that the target core is mapping into this channel */
  else if (ICU_ZERO == (Icu_GpChannelConfig[Channel].ucCoreIndex & LucCoreID))                                          /* PRQA S 0404, 3416 # JV-01, JV-01 */
  {
    /* Report to Development Errors */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_SET_ACTIVATION_CONDITION_SID, ICU_E_INVALID_CORE);
  }
  #endif
  else
  #endif /* End of (ICU_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (ICU_MULTI_CORE_SUPPORT == STD_ON)
    /* Get the spinlock */
    ICU_ENTER_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
    /* Set request to master core if the shared buffer is ready - not locked by Satellite */
    if(ICU_UNLOCKEDSTATUS(Icu_GaaSetActivationConditionBuffer[Channel].blBufferLock))                                   /* PRQA S 3432 # JV-01 */
    {
      /* Lock the shared buffer */
      ICU_LOCKPROCESS(Icu_GaaSetActivationConditionBuffer[Channel].blBufferLock);                                       /* PRQA S 3432 # JV-01 */
      /* Release the spinlock */
      ICU_EXIT_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
      /* Update the request */
      Icu_GaaSetActivationConditionBuffer[Channel].lddActivation = Activation;
      /* Request is issued */
      Icu_GaaSetActivationConditionBuffer[Channel].blSetRequest = ICU_TRUE;
      /* Release Lock */
      ICU_UNLOCKPROCESS(Icu_GaaSetActivationConditionBuffer[Channel].blBufferLock);                                     /* PRQA S 3432 # JV-01 */
    }
    else
    {
      /* Release the spinlock */
      ICU_EXIT_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
      /* Report to Development Errors */
      (void)Det_ReportRuntimeError(ICU_MODULE_ID, ICU_INSTANCE_ID, 
                                                                ICU_SET_ACTIVATION_CONDITION_SID, ICU_E_REQUEST_FALSE);
    }
    #else
    LpChannel = &Icu_GpChannelConfig[Channel];
    /* Read the Unit Type for the given unit */
    LucHWIPType = LpChannel->ucIcuChannelType;
    /* Set the activation edge value */
    if (NULL_PTR != Icu_GaaHwDepFunc[LucHWIPType]->pSetActivation)                                                      /* PRQA S 3416 # JV-01 */
    {
      /* Enter Critical Section */
      ICU_ENTER_CRITICAL_SECTION(ICU_INTERRUPT_CONTROL_PROTECTION);
      /* Invoke lower layer fucntion */
      Icu_GaaHwDepFunc[LucHWIPType]->pSetActivation(Channel, Activation);
      /* Exit Critical Section */
      ICU_EXIT_CRITICAL_SECTION(ICU_INTERRUPT_CONTROL_PROTECTION);
    } /* else No action required */
    #endif /* End of ICU_MULTI_CORE_SUPPORT == STD_ON */
  } /* End of ICU_INITIALIZED != Icu_GblDriverStatus */
} /* End of API Icu_SetActivationCondition */

#define ICU_STOP_SEC_PUBLIC_CODE_GLOBAL
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Icu_DisableNotification
**
** Service ID            : 0x06
**
** Description           : This API service will disable the Icu signal notification of the requested channel.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : Channel
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : The Icu Driver must be initialized.
**
** Global Variables      : Icu_GblDriverStatus, Icu_GpChannelConfig, Icu_GpChannelRamData.
**
** Functions invoked     : Det_ReportError
**
** Registers Used        : None
**
** Reference ID          : ICU_DUD_ACT_007, ICU_DUD_ACT_007_CRT001,
** Reference ID          : ICU_DUD_ACT_007_CRT002, ICU_DUD_ACT_007_ERR001, ICU_DUD_ACT_007_ERR002
** Reference ID          : ICU_DUD_ACT_007_ERR003, ICU_DUD_ACT_007_ERR004, ICU_DUD_ACT_007_GBL001
** Reference ID          : ICU_DUD_ACT_007_ERR005
***********************************************************************************************************************/
#define ICU_START_SEC_PUBLIC_CODE_GLOBAL
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_PUBLIC_CODE) Icu_DisableNotification(Icu_ChannelType Channel)                                            /* PRQA S 1503 # JV-01 */
{
  #if (ICU_DEV_ERROR_DETECT == STD_ON)
  #if (ICU_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = ICU_ONE << (uint8)GetCoreID();
  #endif
  /* Check if the Icu Module is not initialized */
  if (ICU_INITIALIZED != Icu_GblDriverStatus)                                                                           /* PRQA S 3416 # JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_DISABLE_NOTIFICATION_SID, ICU_E_UNINIT);
  }
  else if (ICU_MAX_CHANNEL_ID_CONFIGURED < Channel)
  {
    /* Report Error to DET */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_DISABLE_NOTIFICATION_SID, ICU_E_PARAM_CHANNEL);
  }
  else if (((uint8)ICU_MODE_SIGNAL_MEASUREMENT == Icu_GpChannelConfig[Channel].ucIcuMeasurementMode) ||                 /* PRQA S 3416 # JV-01 */
                                ((uint8)ICU_MODE_EDGE_COUNTER == Icu_GpChannelConfig[Channel].ucIcuMeasurementMode))    /* PRQA S 3415, 3416 # JV-01, JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_DISABLE_NOTIFICATION_SID, ICU_E_PARAM_CHANNEL);
  }
  #if (ICU_ALREADY_ENABLEDISABLE_DET_CHECK == STD_ON)
  /* Check if the notification for the channel is already Disabled */
  else if ((uint8)ICU_FALSE == Icu_GpChannelRamData[Channel].ucNotificationEnable)                                      /* PRQA S 0404, 3416, 4304 # JV-01, JV-01, JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_DISABLE_NOTIFICATION_SID, ICU_E_ALREADY_DISABLED);
  }
  #endif /* End of (ICU_ALREADY_ENABLEDISABLE_DET_CHECK == STD_ON) */
  #if (ICU_MULTI_CORE_SUPPORT == STD_ON)
  /* Check that the target core is mapping into this channel */
  else if (ICU_ZERO == (Icu_GpChannelConfig[Channel].ucCoreIndex & LucCoreID))                                          /* PRQA S 0404, 3416 # JV-01, JV-01 */
  {
  /* Report to Development Errors */
  (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_DISABLE_NOTIFICATION_SID, ICU_E_INVALID_CORE);
  }
  #endif
  else
  #endif /* End of (ICU_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Get the spinlock */
    ICU_ENTER_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
    /* Store the disabled notification into RAM */
    Icu_GpChannelRamData[Channel].ucNotificationEnable = (uint8)ICU_FALSE;                                              /* PRQA S 4304 # JV-01 */
    /* Release the spinlock */
    ICU_EXIT_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
  } /* End of ICU_INITIALIZED != Icu_GblDriverStatus */
} /* End of API Icu_DisableNotification */

#define ICU_STOP_SEC_PUBLIC_CODE_GLOBAL
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Icu_EnableNotification
**
** Service ID            : 0x07
**
** Description           : This API service will enable the Icu signal notification of the requested channel.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : Channel
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : The Icu Driver must be initialized.
**
** Global Variables      : Icu_GblDriverStatus, Icu_GpChannelConfig, Icu_GpChannelRamData, Icu_GulWakeupSource.
**
** Functions invoked     : Det_ReportError
**
** Registers Used        : None
**
** Reference ID          : ICU_DUD_ACT_008, ICU_DUD_ACT_008_CRT001, ICU_DUD_ACT_008_CRT002, ICU_DUD_ACT_008_ERR001
** Reference ID          : ICU_DUD_ACT_008_ERR002, ICU_DUD_ACT_008_ERR003, ICU_DUD_ACT_008_ERR004
** Reference ID          : ICU_DUD_ACT_008_ERR005
** Reference ID          : ICU_DUD_ACT_008_GBL002, ICU_DUD_ACT_008_GBL003, ICU_DUD_ACT_008_GBL001
***********************************************************************************************************************/
#define ICU_START_SEC_PUBLIC_CODE_GLOBAL
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_PUBLIC_CODE) Icu_EnableNotification(Icu_ChannelType Channel)                                             /* PRQA S 1503 # JV-01 */
{
  #if (ICU_DEV_ERROR_DETECT == STD_ON)
  #if (ICU_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = ICU_ONE << (uint8)GetCoreID();
  #endif
  /* Check if the Icu Module is not initialized */
  if (ICU_INITIALIZED != Icu_GblDriverStatus)                                                                           /* PRQA S 3416 # JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_ENABLE_NOTIFICATION_SID, ICU_E_UNINIT);
  }
  /* Check if the channel is valid */
  else if (ICU_MAX_CHANNEL_ID_CONFIGURED < Channel)
  {
    /* Report Error to DET */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_ENABLE_NOTIFICATION_SID, ICU_E_PARAM_CHANNEL);
  }
  /* Check if the measurement mode is other than Time Stamp measurement */
  else if (((uint8)ICU_MODE_SIGNAL_MEASUREMENT == Icu_GpChannelConfig[Channel].ucIcuMeasurementMode) ||                 /* PRQA S 3416 # JV-01 */
                                ((uint8)ICU_MODE_EDGE_COUNTER == Icu_GpChannelConfig[Channel].ucIcuMeasurementMode))    /* PRQA S 3415, 3416 # JV-01, JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_ENABLE_NOTIFICATION_SID, ICU_E_PARAM_CHANNEL);
  }
  #if (ICU_ALREADY_ENABLEDISABLE_DET_CHECK == STD_ON)
  /* Check if the notification for the channel is already Enabled */
  else if ((uint8)ICU_TRUE == Icu_GpChannelRamData[Channel].ucNotificationEnable)                                       /* PRQA S 0404, 3416, 4304 # JV-01, JV-01, JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_ENABLE_NOTIFICATION_SID, ICU_E_ALREADY_ENABLED);
  }
  #endif /* End of (ICU_ALREADY_ENABLEDISABLE_DET_CHECK == STD_ON) */
  #if (ICU_MULTI_CORE_SUPPORT == STD_ON)
  /* Check that the target core is mapping into this channel */
  else if (ICU_ZERO == (Icu_GpChannelConfig[Channel].ucCoreIndex & LucCoreID))                                          /* PRQA S 0404, 3416 # JV-01, JV-01 */
  {
    /* Report to Development Errors */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_ENABLE_NOTIFICATION_SID, ICU_E_INVALID_CORE);
  }
  #endif
  else
  #endif /* End of (ICU_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Get the spinlock */
    ICU_ENTER_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
    /* Store notification status into RAM */
    Icu_GpChannelRamData[Channel].ucNotificationEnable = (uint8)ICU_TRUE;                                               /* PRQA S 4304 # JV-01 */
    #if (ICU_NOTIFY_WAKEUP_INTERRUPT == STD_ON)
    /* Check if the channel is wakeup capable */
    if ((uint8)ICU_TRUE == Icu_GpChannelConfig[Channel].ucIcuWakeupCapability)                                          /* PRQA S 3416, 4304 # JV-01, JV-01 */
    {
      /* Store the enabled wakeup status into RAM */
      Icu_GpChannelRamData[Channel].ucWakeupEnable = (uint8)ICU_TRUE;                                                   /* PRQA S 4304 # JV-01 */
      #if (ICU_REPORT_WAKEUP_SOURCE == STD_ON)
      /* Set the wakeup source information */
      Icu_GulWakeupSource = (Icu_GulWakeupSource |
                    ((EcuM_WakeupSourceType)(ICU_DOUBLE_ONE << Icu_GpChannelConfig[Channel].ucEcuMChannelWakeupInfo)));
      #endif /* End of (ICU_REPORT_WAKEUP_SOURCE == STD_ON) */
    } /* else No action required */
    #endif /* End of (ICU_NOTIFY_WAKEUP_INTERRUPT == STD_ON) */
    /* Release the spinlock */
    ICU_EXIT_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
  } /* End of ICU_INITIALIZED != Icu_GblDriverStatus */
} /* End of API Icu_EnableNotification */

#define ICU_STOP_SEC_PUBLIC_CODE_GLOBAL
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Icu_GetInputState
**
** Service ID            : 0x08
**
** Description           : This API service will return the status of the Icu input.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : Channel
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : Icu_InputStateType
**
** Preconditions         : The Icu Driver must be initialized, ICU_GET_INPUT_STATE_API must be STD_ON
**
** Global Variables      : Icu_GblDriverStatus, Icu_GpChannelConfig, Icu_GpChannelRamData,Icu_GpChannelUserRegConfig.
**
** Functions invoked     : Det_ReportError
**
** Registers Used        : None
**
** Reference ID          : ICU_DUD_ACT_009, ICU_DUD_ACT_009_CRT001,
** Reference ID          : ICU_DUD_ACT_009_ERR001, ICU_DUD_ACT_009_ERR002, ICU_DUD_ACT_009_ERR003
** Reference ID          : ICU_DUD_ACT_009_ERR004, ICU_DUD_ACT_009_ERR005
** Reference ID          : ICU_DUD_ACT_009_CRT002, ICU_DUD_ACT_009_GBL001
***********************************************************************************************************************/
#if (ICU_GET_INPUT_STATE_API == STD_ON)
#define ICU_START_SEC_PUBLIC_CODE_GLOBAL
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(Icu_InputStateType, ICU_PUBLIC_CODE) Icu_GetInputState(Icu_ChannelType Channel)                                    /* PRQA S 1503 # JV-01 */
{
  /* Local variable to store the channel status */
  Icu_InputStateType LddChannelState;

  #if (ICU_DEV_ERROR_DETECT == STD_ON)
  #if (ICU_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = ICU_ONE << (uint8)GetCoreID();
  #endif
  /* Set the initial state to Idle */
  LddChannelState = ICU_IDLE;
  /* Check if the Icu Module is not initialized */
  if (ICU_INITIALIZED != Icu_GblDriverStatus)                                                                           /* PRQA S 3416 # JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_GET_INPUT_STATE_SID, ICU_E_UNINIT);
  }
  /* Check if the channel is valid */
  else if (ICU_MAX_CHANNEL_ID_CONFIGURED < Channel)
  {
    /* Report Error to DET */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_GET_INPUT_STATE_SID, ICU_E_PARAM_CHANNEL);
  }
  else if (((uint8)ICU_MODE_SIGNAL_EDGE_DETECT != Icu_GpChannelConfig[Channel].ucIcuMeasurementMode) &&                 /* PRQA S 3416 # JV-01 */
                          ((uint8)ICU_MODE_SIGNAL_MEASUREMENT != Icu_GpChannelConfig[Channel].ucIcuMeasurementMode))    /* PRQA S 3415, 3416 # JV-01, JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_GET_INPUT_STATE_SID, ICU_E_PARAM_CHANNEL);
  }
  /* Check if the channel is configured for extra duty channel */
  else if (ICU_FIVE == (uint8)Icu_GpChannelUserRegConfig[Channel].ucChannelProperties)                                  /* PRQA S 3416 # JV-01 */
  {
    /* Report Error to Det */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_GET_INPUT_STATE_SID, ICU_E_PARAM_CHANNEL);
  }
  #if (ICU_MULTI_CORE_SUPPORT == STD_ON)
  /* Check that the target core is mapping into this channel */
  else if (ICU_ZERO == (Icu_GpChannelConfig[Channel].ucCoreIndex & LucCoreID))                                          /* PRQA S 0404, 3416 # JV-01, JV-01 */
  {
    /* Report to Development Errors */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_GET_INPUT_STATE_SID, ICU_E_INVALID_CORE);
  }
  #endif
  else
  #endif /* End of #if (ICU_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (ICU_GTM_TIMER_UNIT_USED == STD_ON)
    /* Get the input state by invoking lowlayer function - GTM only */
    if (NULL_PTR != Icu_GaaHwDepFunc[Icu_GpChannelConfig[Channel].ucIcuChannelType]->pGetPulseData)                     /* PRQA S 3416 # JV-01 */
    {
      Icu_GaaHwDepFunc[Icu_GpChannelConfig[Channel].ucIcuChannelType]->pGetPulseData(Channel);
    } /* else No action required */
    #endif
    /* Get the spinlock */
    ICU_ENTER_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
    /* Read the channel input status */
    LddChannelState = (Icu_InputStateType)Icu_GpChannelRamData[Channel].ucChannelStatus;                                /* PRQA S 0404, 4342 # JV-01, JV-01 */
    /* Store channel status as idle */
    Icu_GpChannelRamData[Channel].ucChannelStatus = (uint8)ICU_IDLE;
    /* Release the spinlock */
    ICU_EXIT_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
  } /* End of ICU_INITIALIZED != Icu_GblDriverStatus */
  return (LddChannelState);
} /* End of API Icu_GetInputState */

#define ICU_STOP_SEC_PUBLIC_CODE_GLOBAL
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of (ICU_GET_INPUT_STATE_API == STD_ON) */
/***********************************************************************************************************************
** Function Name         : Icu_StartTimestamp
**
** Service ID            : 0x09
**
** Description           : This API service starts the capturing of timer values
**                         on the edges activated (rising/falling/both) to an
**                         externalbuffer at the beginning of the buffer.
**
** Sync/Async            : Synchronous (Single-core) / Asynchronous (Multi-core)
**
** Reentrancy            : Reentrant
**
** Input Parameters      : Channel, BufferPtr, BufferSize, NotifyInterval
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : The Icu Driver must be initialized,
**                         ICU_TIMESTAMP_API must be STD_ON
**
** Global Variables      : Icu_GpChannelConfig, Icu_GpChannelUserRegConfig,
**                         Icu_GblDriverStatus, Icu_GpTimeStampData,
**                         Icu_GpChannelRamData, Icu_GaaHwDepFunc. 
**
** Functions invoked     : Det_ReportError, Icu_HW_Atu_StartCountMeasurement,
**                         Icu_HW_Taud_StartCountMeasurement, Icu_HW_Tauj_StartCountMeasurement
**
** Registers Used        : None
**
** Reference ID          : ICU_DUD_ACT_010, ICU_DUD_ACT_010_CRT001, ICU_DUD_ACT_010_CRT002
** Reference ID          : ICU_DUD_ACT_010_ERR002, ICU_DUD_ACT_010_ERR003, ICU_DUD_ACT_010_ERR004
** Reference ID          : ICU_DUD_ACT_010_ERR005, ICU_DUD_ACT_010_ERR006, ICU_DUD_ACT_010_GBL001
** Reference ID          : ICU_DUD_ACT_010_GBL002, ICU_DUD_ACT_010_GBL003, ICU_DUD_ACT_010_ERR001
** Reference ID          : ICU_DUD_ACT_010_ERR007, ICU_DUD_ACT_010_ERR008
***********************************************************************************************************************/
#if (ICU_TIMESTAMP_API == STD_ON)
#define ICU_START_SEC_PUBLIC_CODE_GLOBAL
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_PUBLIC_CODE) Icu_StartTimestamp(Icu_ChannelType Channel,                                                 /* PRQA S 1503 # JV-01 */
                    P2VAR(Icu_ValueType, AUTOMATIC, ICU_APPL_DATA) BufferPtr, uint16 BufferSize, uint16 NotifyInterval) /* PRQA S 3432 # JV-01 */
{
  #if (ICU_MULTI_CORE_SUPPORT == STD_OFF)
  /* Local pointer variable for Timestamp channel data */
  P2VAR(volatile Icu_TimeStampChannelRamDataType, AUTOMATIC, ICU_CONFIG_DATA) LpTimeStampData;
  /* Defining a pointer to the channel config parameters */
  P2CONST(volatile Icu_ChannelConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannel;
  /* Declare a Local variable to Timer Type */
  volatile uint8 LucTimerType;
  #endif
  /* Local variable to store the channel ram index */
  uint8 LucIndex;
  #if (ICU_DEV_ERROR_DETECT == STD_ON)
  #if (ICU_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = ICU_ONE << (uint8)GetCoreID();
  #endif
  /* Check if the Icu Module is not initialized */
  if (ICU_INITIALIZED != Icu_GblDriverStatus)                                                                           /* PRQA S 3416 # JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_START_TIMESTAMP_SID, ICU_E_UNINIT);
  }
  /* Check if the channel is valid */
  else if (ICU_MAX_CHANNEL_ID_CONFIGURED < Channel)
  {
    /* Report Error to DET */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_START_TIMESTAMP_SID, ICU_E_PARAM_CHANNEL);
  }
  else if ((uint8)ICU_MODE_TIMESTAMP != Icu_GpChannelConfig[Channel].ucIcuMeasurementMode)                              /* PRQA S 3416 # JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_START_TIMESTAMP_SID, ICU_E_PARAM_CHANNEL);
  }
  /* Check if the pointer passed is Null */
  else if ((P2VAR(Icu_ValueType, AUTOMATIC, ICU_APPL_DATA))NULL_PTR == BufferPtr)                                       /* PRQA S 3432 # JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_START_TIMESTAMP_SID, ICU_E_PARAM_POINTER);
  }
  /* Check if the channel buffer size is zero */
  else if ((uint16)ICU_ZERO == BufferSize)
  {
    /* Report Error to DET */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_START_TIMESTAMP_SID, ICU_E_PARAM_BUFFER_SIZE);
  }
  /* Check if the channel notifying interval is less than one */
  else if ((uint16)ICU_NOTIFY_INTERVAL_MIN_VAL > NotifyInterval)
  {
    /* Report Error to DET */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_START_TIMESTAMP_SID, ICU_E_PARAM_NOTIFY_INTERVAL);
  }
  #if (ICU_MULTI_CORE_SUPPORT == STD_ON)
  /* Check that the target core is mapping into this channel */
  else if (ICU_ZERO == (Icu_GpChannelConfig[Channel].ucCoreIndex & LucCoreID))                                          /* PRQA S 0404, 3416 # JV-01, JV-01 */
  {
    /* Report to Development Errors */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_START_TIMESTAMP_SID, ICU_E_INVALID_CORE);
  }
  #endif
  else
  #endif /* End of #if (ICU_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (ICU_MULTI_CORE_SUPPORT == STD_ON)
    /* Read the channel time stamp ram index */
    LucIndex = Icu_GpChannelUserRegConfig[Channel].ucRamDataIndex;
    /* Get the spinlock */
    ICU_ENTER_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
    /* Set request to master core if the shared buffer is ready - not locked by Satellite */
    if(ICU_UNLOCKEDSTATUS(Icu_GaaStartTimestampBuffer[LucIndex].blBufferLock))                                          /* PRQA S 3432 # JV-01 */
    {
      /* Lock the shared buffer */
      ICU_LOCKPROCESS(Icu_GaaStartTimestampBuffer[LucIndex].blBufferLock);                                              /* PRQA S 3432 # JV-01 */
      /* Release the spinlock */
      ICU_EXIT_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
      /* Update the request */
      Icu_GaaStartTimestampBuffer[LucIndex].lpBufferPtr = BufferPtr;
      Icu_GaaStartTimestampBuffer[LucIndex].lusBufferSize = BufferSize;
      Icu_GaaStartTimestampBuffer[LucIndex].lusNotifyInterval = NotifyInterval;
      /* Request is issued */
      Icu_GaaStartTimestampBuffer[LucIndex].blSetRequest = ICU_TRUE;
      /* Release Lock */
      ICU_UNLOCKPROCESS(Icu_GaaStartTimestampBuffer[LucIndex].blBufferLock);                                            /* PRQA S 3432 # JV-01 */
    }
    else
    {
      /* Release the spinlock */
      ICU_EXIT_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
      /* Report to Development Errors */
      (void)Det_ReportRuntimeError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_START_TIMESTAMP_SID, ICU_E_REQUEST_FALSE);
    }
    #else
    /* Read the channel time stamp ram index */
    LucIndex = Icu_GpChannelUserRegConfig[Channel].ucRamDataIndex;
    /* Initialize Timestamp RAM data */
    LpTimeStampData = &Icu_GpTimeStampData[LucIndex];
    LpTimeStampData->pBufferPointer = BufferPtr;
    LpTimeStampData->usBufferSize = BufferSize;
    LpTimeStampData->usTimestampIndex = (uint16)ICU_BUFFER_IDX_INIT_VAL;
    LpTimeStampData->usTimestampsCounter = (uint16)ICU_ZERO;
    LpTimeStampData->usNotifyInterval = NotifyInterval;
    /* Activate Timestamp capturing */
    /* Updating the channel config parameter to the current channel */
    LpChannel = &Icu_GpChannelConfig[Channel];
    /* Read the Timer Type for the given channel  */
    LucTimerType = LpChannel->ucIcuChannelType;
    /* Activate Timestamp capturing */
    if (NULL_PTR != Icu_GaaHwDepFunc[LucTimerType]->pStartCountMeasurement)                                             /* PRQA S 3416 # JV-01 */
    {
      Icu_GaaHwDepFunc[LucTimerType]->pStartCountMeasurement(Channel);
    } /* else No action required */
    /* Initialize channel status as active */
    Icu_GpChannelRamData[Channel].ucChannelStatus = (uint8)ICU_ACTIVE;
    /* Set the flag to indicate that the timestamping is started */
    LpTimeStampData->blTimestampingStarted = ICU_TRUE;
    #endif /* End of ICU_MULTI_CORE_SUPPORT == STD_ON */
  } /* End of ICU_INITIALIZED != Icu_GblDriverStatus */
} /* End of API Icu_StartTimestamp */

#define ICU_STOP_SEC_PUBLIC_CODE_GLOBAL
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* End of (ICU_TIMESTAMP_API == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Icu_StopTimestamp
**
** Service ID            : 0x0A
**
** Description           : This API service stops the timestamp measurement of the requested channel.
**
** Sync/Async            : Synchronous (Single-core) / Asynchronous (Multi-core)
**
** Reentrancy            : Reentrant
**
** Input Parameters      : Channel
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : The Icu Driver must be initialized, ICU_TIMESTAMP_API must be STD_ON
**
** Global Variables      : Icu_GpChannelConfig, Icu_GpChannelRamData, Icu_GblDriverStatus, Icu_GaaHwDepFunc.
**
** Functions invoked     : Det_ReportError, Det_ReportRuntimeError, Icu_HW_Atu_StopCountMeasurement,
**                         Icu_HW_Taud_StopCountMeasurement, Icu_HW_Tauj_StopCountMeasurement
**
** Registers Used        : None
**
** Reference ID          : ICU_DUD_ACT_011, ICU_DUD_ACT_011_CRT001,  ICU_DUD_ACT_011_CRT002, ICU_DUD_ACT_011_ERR001
** Reference ID          : ICU_DUD_ACT_011_ERR002, ICU_DUD_ACT_011_ERR003, ICU_DUD_ACT_011_ERR004
** Reference ID          : ICU_DUD_ACT_011_ERR005, ICU_DUD_ACT_011_ERR006,ICU_DUD_ACT_011_ERR007, ICU_DUD_ACT_011_GBL001
***********************************************************************************************************************/
#if (ICU_TIMESTAMP_API == STD_ON)
#define ICU_START_SEC_PUBLIC_CODE_GLOBAL
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_PUBLIC_CODE) Icu_StopTimestamp(Icu_ChannelType Channel)                                                  /* PRQA S 1503 # JV-01 */
{
  #if (ICU_MULTI_CORE_SUPPORT == STD_OFF)
  /* Defining a pointer to the channel config parameters */
  P2CONST(Icu_ChannelConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannel;
  /* Declare a Local variable to Timer Type */
  volatile uint8 LucTimerType;
  #else
  /* Local variable to store the channel ram index */
  uint8 LucIndex;
  #endif
  #if (ICU_DEV_ERROR_DETECT == STD_ON)
  #if (ICU_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = ICU_ONE << (uint8)GetCoreID();
  #endif
  /* Check if the Icu Module is not initialized */
  if (ICU_INITIALIZED != Icu_GblDriverStatus)                                                                           /* PRQA S 3416 # JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_STOP_TIMESTAMP_SID, ICU_E_UNINIT);
  }
  /* Check if the channel is valid */
  else if (ICU_MAX_CHANNEL_ID_CONFIGURED < Channel)
  {
    /* Report Error to DET */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_STOP_TIMESTAMP_SID, ICU_E_PARAM_CHANNEL);
  }
  /* Check if the channel is other than Time Stamp measurement */
  else if ((uint8)ICU_MODE_TIMESTAMP != Icu_GpChannelConfig[Channel].ucIcuMeasurementMode)                              /* PRQA S 3416 # JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_STOP_TIMESTAMP_SID, ICU_E_PARAM_CHANNEL);
  }
  #if (ICU_AR_VERSION == ICU_AR_422_VERSION)
  /* Check if the channel status is Idle */
  else if ((uint8)ICU_IDLE == Icu_GpChannelRamData[Channel].ucChannelStatus)
  {
    /* Report Error to DET */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_STOP_TIMESTAMP_SID, ICU_E_NOT_STARTED);
  }
  #endif /* End of (ICU_AR_VERSION == ICU_AR_422_VERSION) */
  #if (ICU_MULTI_CORE_SUPPORT == STD_ON)
  /* Check that the target core is mapping into this channel */
  else if (ICU_ZERO == (Icu_GpChannelConfig[Channel].ucCoreIndex & LucCoreID))                                          /* PRQA S 0404, 3416 # JV-01, JV-01 */
  {
    /* Report to Development Errors */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_STOP_TIMESTAMP_SID, ICU_E_INVALID_CORE);
  }
  #endif
  else
  #endif /* End of (ICU_DEV_ERROR_DETECT == STD_ON) */
  /* Check if the channel status is Idle */
  #if (ICU_AR_VERSION == ICU_AR_431_VERSION) || (ICU_AR_VERSION == ICU_AR_R22_11_VERSION)
  if ((uint8)ICU_IDLE == Icu_GpChannelRamData[Channel].ucChannelStatus)                                                 /* PRQA S 0404, 3416 # JV-01, JV-01 */
  {
    (void)Det_ReportRuntimeError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_STOP_TIMESTAMP_SID, ICU_E_NOT_STARTED);
  }
  else
  #endif /* End of (ICU_AR_VERSION == ICU_AR_431_VERSION) || (ICU_AR_VERSION == ICU_AR_R22_11_VERSION) */
  {
    #if (ICU_MULTI_CORE_SUPPORT == STD_ON)
    /* Read the channel time stamp ram index */
    LucIndex = Icu_GpChannelUserRegConfig[Channel].ucRamDataIndex;
    /* Get the spinlock */
    ICU_ENTER_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
    /* Set request to master core if the shared buffer is ready - not locked by Satellite */
    if(ICU_UNLOCKEDSTATUS(Icu_GaaStopTimestampBuffer[LucIndex].blBufferLock))                                           /* PRQA S 3432 # JV-01 */
    {
      /* Lock the shared buffer */
      ICU_LOCKPROCESS(Icu_GaaStopTimestampBuffer[LucIndex].blBufferLock);                                               /* PRQA S 3432 # JV-01 */
      /* Release the spinlock */
      ICU_EXIT_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
      /* Request is issued */
      Icu_GaaStopTimestampBuffer[LucIndex].blSetRequest = ICU_TRUE;
      /* Release Lock */
      ICU_UNLOCKPROCESS(Icu_GaaStopTimestampBuffer[LucIndex].blBufferLock);                                             /* PRQA S 3432 # JV-01 */
    }
    else
    {
      /* Release the spinlock */
      ICU_EXIT_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
      /* Report to Development Errors */
      (void)Det_ReportRuntimeError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_STOP_TIMESTAMP_SID, ICU_E_REQUEST_FALSE);
    }
    #else
    /* Updating the channel config parameter to the current channel */
    LpChannel = &Icu_GpChannelConfig[Channel];
    /* Read the Timer Type for the given channel  */
    LucTimerType = LpChannel->ucIcuChannelType;
    /* Stop Timestamp capturing */
    if (NULL_PTR != Icu_GaaHwDepFunc[LucTimerType]->pStopCountMeasurement)                                              /* PRQA S 3416 # JV-01 */
    {
      Icu_GaaHwDepFunc[LucTimerType]->pStopCountMeasurement(Channel);
    } /* else No action required */
    /* Initialize channel status as idle */
    Icu_GpChannelRamData[Channel].ucChannelStatus = (uint8)ICU_IDLE;
    #endif /* End of ICU_MULTI_CORE_SUPPORT == STD_ON */
  } /* End of ICU_INITIALIZED != Icu_GblDriverStatus */
} /* End of API Icu_StopTimestamp */
#define ICU_STOP_SEC_PUBLIC_CODE_GLOBAL
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of (ICU_TIMESTAMP_API == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Icu_GetTimestampIndex
**
** Service ID            : 0x0B
**
** Description           : This API service reads the timestamp index the next to be written for the requested channel.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : Channel
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : Icu_IndexType
**
** Preconditions         : The Icu Driver must be initialized, ICU_TIMESTAMP_API must be STD_ON
**
** Global Variables      : Icu_GblDriverStatus, Icu_GpChannelUserRegConfig, Icu_GpChannelConfig, Icu_GpTimeStampData
**
** Functions invoked     : Det_ReportError.
**
** Registers Used        : None
**
** Reference ID          : ICU_DUD_ACT_012,ICU_DUD_ACT_012_ERR001, ICU_DUD_ACT_012_ERR002,ICU_DUD_ACT_012_ERR003
** Reference ID          : ICU_DUD_ACT_012_ERR004
***********************************************************************************************************************/
#if (ICU_TIMESTAMP_API == STD_ON)
#define ICU_START_SEC_PUBLIC_CODE_GLOBAL
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(Icu_IndexType, ICU_PUBLIC_CODE) Icu_GetTimestampIndex(Icu_ChannelType Channel)                                     /* PRQA S 1503 # JV-01 */
{
  /* Return value */
  Icu_IndexType LusTimestampIndex;
  uint8 LucIndex;
  #if (ICU_DEV_ERROR_DETECT == STD_ON)
  #if (ICU_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = ICU_ONE << (uint8)GetCoreID();
  #endif
  /* Initial value */
  LusTimestampIndex = (uint16)ICU_BUFFER_IDX_INIT_VAL;
  /* Check if the Icu Module is not initialized */
  if (ICU_INITIALIZED != Icu_GblDriverStatus)                                                                           /* PRQA S 3416 # JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_GET_TIMESTAMP_INDEX_SID, ICU_E_UNINIT);
  }
  /* Check if the channel is valid */
  else if (ICU_MAX_CHANNEL_ID_CONFIGURED < Channel)
  {
    /* Report Error to DET */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_GET_TIMESTAMP_INDEX_SID, ICU_E_PARAM_CHANNEL);
  }
  /* Check if the measurement mode is other than Time Stamp measurement */
  else if ((uint8)ICU_MODE_TIMESTAMP != Icu_GpChannelConfig[Channel].ucIcuMeasurementMode)                              /* PRQA S 3416 # JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_GET_TIMESTAMP_INDEX_SID, ICU_E_PARAM_CHANNEL);
  }
  #if (ICU_MULTI_CORE_SUPPORT == STD_ON)
  /* Check that the target core is mapping into this channel */
  else if (ICU_ZERO == (Icu_GpChannelConfig[Channel].ucCoreIndex & LucCoreID))                                          /* PRQA S 0404, 3416 # JV-01, JV-01 */
  {
    /* Report to Development Errors */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_GET_TIMESTAMP_INDEX_SID, ICU_E_INVALID_CORE);
  }
  #endif
  else
  #endif /* End of (ICU_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Initial value */
    LusTimestampIndex = (uint16)ICU_BUFFER_IDX_INIT_VAL;
    LucIndex = Icu_GpChannelUserRegConfig[Channel].ucRamDataIndex;
    /* If timestamping is started, then only return timestamp index value */
    if (ICU_TRUE == Icu_GpTimeStampData[LucIndex].blTimestampingStarted)                                                /* PRQA S 0404, 3416 # JV-01, JV-01 */
    {
      LusTimestampIndex = Icu_GpTimeStampData[LucIndex].usTimestampIndex;                                               /* PRQA S 0404 # JV-01 */
    } /* else No action required */
  } /* End of ICU_INITIALIZED != Icu_GblDriverStatus */
  return (LusTimestampIndex);
} /* End of API Icu_GetTimestampIndex */

#define ICU_STOP_SEC_PUBLIC_CODE_GLOBAL
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* End of (ICU_TIMESTAMP_API == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Icu_ResetEdgeCount
**
** Service ID            : 0x0C
**
** Description           : This API resets the value of the counted edges.
**
** Sync/Async            : Synchronous (Single-core) / Asynchronous (Multi-core)
**
** Reentrancy            : Reentrant
**
** Input Parameters      : Channel
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : The Icu Driver must be initialized, ICU_EDGE_COUNT_API must be STD_ON
**
** Global Variables      : Icu_GblDriverStatus, Icu_GpChannelConfig, Icu_GaaHwDepFunc.
**
** Functions invoked     : Det_ReportError, Icu_HW_Atu_ResetEdgeCount, Icu_HW_Taud_ResetEdgeCount,
**                         Icu_HW_Tauj_ResetEdgeCount
**
** Registers Used        : None
**
** Reference ID          : ICU_DUD_ACT_013,ICU_DUD_ACT_013_ERR001, ICU_DUD_ACT_013_ERR002,ICU_DUD_ACT_013_ERR003
** Reference ID          : ICU_DUD_ACT_013_ERR004, ICU_DUD_ACT_013_ERR005
** Reference ID          : ICU_DUD_ACT_013_CRT001, ICU_DUD_ACT_013_CRT002
***********************************************************************************************************************/
#if (ICU_EDGE_COUNT_API == STD_ON)
#define ICU_START_SEC_PUBLIC_CODE_GLOBAL
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_PUBLIC_CODE) Icu_ResetEdgeCount(Icu_ChannelType Channel)                                                 /* PRQA S 1503 # JV-01 */
{
  #if (ICU_MULTI_CORE_SUPPORT == STD_OFF)
  /* Defining a pointer to the channel config parameters */
  P2CONST(Icu_ChannelConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannel;
  /* Declare a Local variable to Timer Type */
  volatile uint8 LucTimerType;
  #else
  /* Local variable to store the channel ram index */
  uint8 LucIndex;
  #endif
  #if (ICU_DEV_ERROR_DETECT == STD_ON)
  #if (ICU_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = ICU_ONE << (uint8)GetCoreID();
  #endif
  /* Check if the Icu Module is not initialized */
  if (ICU_INITIALIZED != Icu_GblDriverStatus)                                                                           /* PRQA S 3416 # JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_RESET_EDGE_COUNT_SID, ICU_E_UNINIT);
  }
  /* Check if the channel is valid */
  else if (ICU_MAX_CHANNEL_ID_CONFIGURED < Channel)
  {
    /* Report Error to DET */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_RESET_EDGE_COUNT_SID, ICU_E_PARAM_CHANNEL);
  }
  /* Check if the measurement mode is other than Edge counting */
  else if ((uint8)(ICU_MODE_EDGE_COUNTER) != Icu_GpChannelConfig[Channel].ucIcuMeasurementMode)                         /* PRQA S 3416 # JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_RESET_EDGE_COUNT_SID, ICU_E_PARAM_CHANNEL);
  }
  #if (ICU_MULTI_CORE_SUPPORT == STD_ON)
  /* Check that the target core is mapping into this channel */
  else if (ICU_ZERO == (Icu_GpChannelConfig[Channel].ucCoreIndex & LucCoreID))                                          /* PRQA S 0404, 3416 # JV-01, JV-01 */
  {
    /* Report to Development Errors */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_RESET_EDGE_COUNT_SID, ICU_E_INVALID_CORE);
  }
  #endif
  else
  #endif /* End of #if (ICU_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (ICU_MULTI_CORE_SUPPORT == STD_ON)
    /* Read the channel time stamp ram index */
    LucIndex = Icu_GpChannelUserRegConfig[Channel].ucRamDataIndex;
    /* Get the spinlock */
    ICU_ENTER_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
    /* Set request to master core if the shared buffer is ready - not locked by Satellite */
    if(ICU_UNLOCKEDSTATUS(Icu_GaaResetEdgeCountBuffer[LucIndex].blBufferLock))                                          /* PRQA S 3432 # JV-01 */
    {
      /* Lock the shared buffer */
      ICU_LOCKPROCESS(Icu_GaaResetEdgeCountBuffer[LucIndex].blBufferLock);                                              /* PRQA S 3432 # JV-01 */
      /* Release the spinlock */
      ICU_EXIT_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
      /* Request is issued */
      Icu_GaaResetEdgeCountBuffer[LucIndex].blSetRequest = ICU_TRUE;
      /* Release Lock */
      ICU_UNLOCKPROCESS(Icu_GaaResetEdgeCountBuffer[LucIndex].blBufferLock);                                            /* PRQA S 3432 # JV-01 */
    }
    else
    {
      /* Release the spinlock */
      ICU_EXIT_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
      /* Report to Development Errors */
      (void)Det_ReportRuntimeError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_RESET_EDGE_COUNT_SID, ICU_E_REQUEST_FALSE);
    }
    #else
    /* Updating the channel config parameter to the current channel */
    LpChannel = &Icu_GpChannelConfig[Channel];
    /* Read the Timer Type for the given channel */
    LucTimerType = LpChannel->ucIcuChannelType;
    if (NULL_PTR != Icu_GaaHwDepFunc[LucTimerType]->pResetEdgeCount)                                                    /* PRQA S 3416 # JV-01 */
    {
      /* Invoke low-level driver for initializing the hardware */
      Icu_GaaHwDepFunc[LucTimerType]->pResetEdgeCount(Channel);
    } /* else No action required */
    #endif /* End of #if (ICU_MULTI_CORE_SUPPORT == STD_ON) */
  } /* End of ICU_INITIALIZED != Icu_GblDriverStatus */
} /* End of API Icu_ResetEdgeCount */

#define ICU_STOP_SEC_PUBLIC_CODE_GLOBAL
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* End of (ICU_EDGE_COUNT_API == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Icu_EnableEdgeCount
**
** Service ID            : 0x0D
**
** Description           : This API service enables the counting of edges of the requested channel.
**
** Sync/Async            : Synchronous (Single-core) / Asynchronous (Multi-core)
**
** Reentrancy            : Reentrant
**
** Input Parameters      : Channel
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : The Icu Driver must be initialized, ICU_EDGE_COUNT_API must be STD_ON
**
** Global Variables      : Icu_GpChannelRamData, Icu_GpChannelConfig,
**                         Icu_GblDriverStatus, Icu_GaaHwDepFunc.
**
** Functions invoked     : Det_ReportError, Icu_HW_Atu_StartCountMeasurement,
**                         Icu_HW_Taud_StartCountMeasurement, Icu_HW_Tauj_StartCountMeasurement
**
** Registers Used        : None
**
** Reference ID          : ICU_DUD_ACT_014, ICU_DUD_ACT_014_CRT001,ICU_DUD_ACT_014_CRT002, ICU_DUD_ACT_014_ERR001
** Reference ID          : ICU_DUD_ACT_014_ERR002, ICU_DUD_ACT_014_ERR003, ICU_DUD_ACT_014_ERR004
** Reference ID          : ICU_DUD_ACT_014_ERR005,ICU_DUD_ACT_014_GBL001
***********************************************************************************************************************/
#if (ICU_EDGE_COUNT_API == STD_ON)
#define ICU_START_SEC_PUBLIC_CODE_GLOBAL
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_PUBLIC_CODE) Icu_EnableEdgeCount(Icu_ChannelType Channel)                                                /* PRQA S 1503 # JV-01 */
{
  #if (ICU_MULTI_CORE_SUPPORT == STD_OFF)
  /* Defining a pointer to the channel config parameters */
  P2CONST(Icu_ChannelConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannel;
  /* Declare a Local variable to Timer Type */
  volatile uint8 LucTimerType;
  #else
  /* Local variable to store the channel ram index */
  uint8 LucIndex;
  #endif
  #if (ICU_DEV_ERROR_DETECT == STD_ON)
  #if (ICU_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = ICU_ONE << (uint8)GetCoreID();
  #endif
  /* Check if the Icu Module is not initialized */
  if (ICU_INITIALIZED != Icu_GblDriverStatus)                                                                           /* PRQA S 3416 # JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_ENABLE_EDGE_COUNT_SID, ICU_E_UNINIT);
  }
  /* Check if the channel is valid */
  else if (ICU_MAX_CHANNEL_ID_CONFIGURED < Channel)
  {
    /* Report Error to DET */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_ENABLE_EDGE_COUNT_SID, ICU_E_PARAM_CHANNEL);
  }
  /* Check if the measurement mode is other than Edge counting */
  else if ((uint8)(ICU_MODE_EDGE_COUNTER) != Icu_GpChannelConfig[Channel].ucIcuMeasurementMode)                         /* PRQA S 3416 # JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_ENABLE_EDGE_COUNT_SID, ICU_E_PARAM_CHANNEL);
  }
  #if (ICU_MULTI_CORE_SUPPORT == STD_ON)
  /* Check that the target core is mapping into this channel */
  else if (ICU_ZERO == (Icu_GpChannelConfig[Channel].ucCoreIndex & LucCoreID))                                          /* PRQA S 0404, 3416 # JV-01, JV-01 */
  {
    /* Report to Development Errors */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_ENABLE_EDGE_COUNT_SID, ICU_E_INVALID_CORE);
  }
  #endif
  else
  #endif /* End of (ICU_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (ICU_MULTI_CORE_SUPPORT == STD_ON)
    /* Read the channel time stamp ram index */
    LucIndex = Icu_GpChannelUserRegConfig[Channel].ucRamDataIndex;
    /* Get the spinlock */
    ICU_ENTER_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
    /* Set request to master core if the shared buffer is ready - not locked by Satellite */
    if(ICU_UNLOCKEDSTATUS(Icu_GaaEnableEdgeCountBuffer[LucIndex].blBufferLock))                                         /* PRQA S 3432 # JV-01 */
    {
      /* Lock the shared buffer */
      ICU_LOCKPROCESS(Icu_GaaEnableEdgeCountBuffer[LucIndex].blBufferLock);                                             /* PRQA S 3432 # JV-01 */
      /* Release the spinlock */
      ICU_EXIT_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
      /* Request is issued */
      Icu_GaaEnableEdgeCountBuffer[LucIndex].blSetRequest = ICU_TRUE;
      /* Release Lock */
      ICU_UNLOCKPROCESS(Icu_GaaEnableEdgeCountBuffer[LucIndex].blBufferLock);                                           /* PRQA S 3432 # JV-01 */
    }
    else
    {
      /* Release the spinlock */
      ICU_EXIT_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
      /* Report to Development Errors */
      (void)Det_ReportRuntimeError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_ENABLE_EDGE_COUNT_SID, ICU_E_REQUEST_FALSE);
    }
    #else
    /* Updating the channel config parameter to the current channel */
    LpChannel = &Icu_GpChannelConfig[Channel];
    /* Read the Timer Type for the given channel */
    LucTimerType = LpChannel->ucIcuChannelType;
    if (NULL_PTR != Icu_GaaHwDepFunc[LucTimerType]->pStartCountMeasurement)                                             /* PRQA S 3416 # JV-01 */
    {
      Icu_GaaHwDepFunc[LucTimerType]->pStartCountMeasurement(Channel);
    } /* else No action required */
    /* Initialize the channel status as active */
    Icu_GpChannelRamData[Channel].ucChannelStatus = (uint8)ICU_ACTIVE;
    #endif /* End of #if (ICU_MULTI_CORE_SUPPORT == STD_ON) */
  } /* End of ICU_INITIALIZED != Icu_GblDriverStatus */
} /* End of API Icu_EnableEdgeCount */

#define ICU_STOP_SEC_PUBLIC_CODE_GLOBAL
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of (ICU_EDGE_COUNT_API == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Icu_DisableEdgeCount
**
** Service ID            : 0x0E
**
** Description           : This API service disables the counting of edges of the requested channel.
**
** Sync/Async            : Synchronous (Single-core) / Asynchronous (Multi-core)
**
** Reentrancy            : Reentrant
**
** Input Parameters      : Channel
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : The Icu Driver must be initialized, ICU_EDGE_COUNT_API must be STD_ON
**
** Global Variables      : Icu_GblDriverStatus, Icu_GpChannelRamData,
**                         Icu_GpChannelConfig, Icu_GaaHwDepFunc.
**
** Functions invoked     : Det_ReportError, Icu_HW_Taud_StopCountMeasurement,
**                         Icu_HW_Tauj_StopCountMeasurement, Icu_HW_Atu_StopCountMeasurement
**
** Registers Used        : None
**
** Reference ID          : ICU_DUD_ACT_015, ICU_DUD_ACT_015_CRT001, ICU_DUD_ACT_015_CRT002, ICU_DUD_ACT_015_ERR001
** Reference ID          : ICU_DUD_ACT_015_ERR002, ICU_DUD_ACT_015_ERR003, ICU_DUD_ACT_015_ERR004
** Reference ID          : ICU_DUD_ACT_015_ERR005, ICU_DUD_ACT_015_GBL001
***********************************************************************************************************************/
#if (ICU_EDGE_COUNT_API == STD_ON)
#define ICU_START_SEC_PUBLIC_CODE_GLOBAL
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_PUBLIC_CODE) Icu_DisableEdgeCount(Icu_ChannelType Channel)                                               /* PRQA S 1503 # JV-01 */

{
  #if (ICU_MULTI_CORE_SUPPORT == STD_OFF)
  /* Defining a pointer to the channel config parameters */
  P2CONST(Icu_ChannelConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannel;
  /* Declare a Local variable to Timer Type */
  volatile uint8 LucTimerType;
  #else
  /* Local variable to store the channel ram index */
  uint8 LucIndex;
  #endif
  #if (ICU_DEV_ERROR_DETECT == STD_ON)
  #if (ICU_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = ICU_ONE << (uint8)GetCoreID();
  #endif
  /* Check if the Icu Module is not initialized */
  if (ICU_INITIALIZED != Icu_GblDriverStatus)                                                                           /* PRQA S 3416 # JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_DISABLE_EDGE_COUNT_SID, ICU_E_UNINIT);
  }
  else if (ICU_MAX_CHANNEL_ID_CONFIGURED < Channel)
  {
    /* Report Error to DET */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_DISABLE_EDGE_COUNT_SID, ICU_E_PARAM_CHANNEL);
  }
  /* Check if the measurement mode is other than Edge counting */
  else if ((uint8)(ICU_MODE_EDGE_COUNTER) != Icu_GpChannelConfig[Channel].ucIcuMeasurementMode)                         /* PRQA S 3416 # JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_DISABLE_EDGE_COUNT_SID, ICU_E_PARAM_CHANNEL);
  }
  #if (ICU_MULTI_CORE_SUPPORT == STD_ON)
  /* Check that the target core is mapping into this channel */
  else if (ICU_ZERO == (Icu_GpChannelConfig[Channel].ucCoreIndex & LucCoreID))                                          /* PRQA S 0404, 3416 # JV-01, JV-01 */
  {
    /* Report to Development Errors */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_DISABLE_EDGE_COUNT_SID, ICU_E_INVALID_CORE);
  }
  #endif
  else
  #endif /* End of (ICU_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (ICU_MULTI_CORE_SUPPORT == STD_ON)
    /* Read the channel time stamp ram index */
    LucIndex = Icu_GpChannelUserRegConfig[Channel].ucRamDataIndex;
    /* Get the spinlock */
    ICU_ENTER_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
    /* Set request to master core if the shared buffer is ready - not locked by Satellite */
    if(ICU_UNLOCKEDSTATUS(Icu_GaaDisableEdgeCountBuffer[LucIndex].blBufferLock))                                        /* PRQA S 3432 # JV-01 */
    {
      /* Lock the shared buffer */
      ICU_LOCKPROCESS(Icu_GaaDisableEdgeCountBuffer[LucIndex].blBufferLock);                                            /* PRQA S 3432 # JV-01 */
      /* Release the spinlock */
      ICU_EXIT_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
      /* Request is issued */
      Icu_GaaDisableEdgeCountBuffer[LucIndex].blSetRequest = ICU_TRUE;
      /* Release Lock */
      ICU_UNLOCKPROCESS(Icu_GaaDisableEdgeCountBuffer[LucIndex].blBufferLock);                                          /* PRQA S 3432 # JV-01 */
    }
    else
    {
      /* Release the spinlock */
      ICU_EXIT_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
      /* Report to Development Errors */
      (void)Det_ReportRuntimeError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_DISABLE_EDGE_COUNT_SID, ICU_E_REQUEST_FALSE);
    }
    #else
    /* Updating the channel config parameter to the current channel */
    LpChannel = &Icu_GpChannelConfig[Channel];
    /* Read the Timer Type for the given channel  */
    LucTimerType = LpChannel->ucIcuChannelType;
    /* Invoke the Low-Level Driver for disabling the edge count */
    if (NULL_PTR != Icu_GaaHwDepFunc[LucTimerType]->pStopCountMeasurement)                                              /* PRQA S 3416 # JV-01 */
    {
      Icu_GaaHwDepFunc[LucTimerType]->pStopCountMeasurement(Channel);
    } /* else No action required */
    /* Initialize the channel status as idle */
    Icu_GpChannelRamData[Channel].ucChannelStatus = (uint8)ICU_IDLE;
    #endif /* End of ICU_MULTI_CORE_SUPPORT == STD_ON */
  } /* End of ICU_INITIALIZED != Icu_GblDriverStatus */
} /* End of API Icu_DisableEdgeCount */

#define ICU_STOP_SEC_PUBLIC_CODE_GLOBAL
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of (ICU_EDGE_COUNT_API == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Icu_EnableEdgeDetection
**
** Service ID            : 0x16
**
** Description           : This API service enables the counting of edges of the requested channel.
**
** Sync/Async            : Synchronous (Single-core) / Asynchronous (Multi-core)
**
** Reentrancy            : Reentrant
**
** Input Parameters      : Channel
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : The Icu Driver must be initialized, ICU_EDGE_DETECT_API must be STD_ON
**
** Global Variables      : Icu_GblDriverStatus, Icu_GpChannelConfig, Icu_GaaHwDepFunc.
**
** Functions invoked     : Det_ReportError, Icu_HW_Atu_StartCountMeasurement,
**                         Icu_HW_Taud_StartCountMeasurement, Icu_HW_Tauj_StartCountMeasurement,
**                         Icu_HW_Pin_EnableEdgeDetection
**
** Registers Used        : None
**
** Reference ID          : ICU_DUD_ACT_023, ICU_DUD_ACT_023_ERR001, ICU_DUD_ACT_023_ERR002, ICU_DUD_ACT_023_ERR003
** Reference ID          : ICU_DUD_ACT_023_ERR004, ICU_DUD_ACT_023_ERR005
***********************************************************************************************************************/
#if (ICU_EDGE_DETECT_API == STD_ON)
#define ICU_START_SEC_PUBLIC_CODE_GLOBAL
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_PUBLIC_CODE) Icu_EnableEdgeDetection(Icu_ChannelType Channel)                                            /* PRQA S 1503 # JV-01 */
{
  #if (ICU_MULTI_CORE_SUPPORT == STD_OFF)
  /* Declare a Local variable to Timer Type */
  volatile uint8 LucHWIPType;
  #else
  /* Local variable to store the channel ram index */
  uint8 LucIndex;
  #endif
  #if (ICU_DEV_ERROR_DETECT == STD_ON)
  #if (ICU_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = ICU_ONE << (uint8)GetCoreID();
  #endif
  /* Check if the Icu Module is not initialized */
  if (ICU_INITIALIZED != Icu_GblDriverStatus)                                                                           /* PRQA S 3416 # JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_ENABLE_EDGE_DETECTION_SID, ICU_E_UNINIT);
  }
  /* Check if the channel is valid */
  else if (ICU_MAX_CHANNEL_ID_CONFIGURED < Channel)
  {
    /* Report Error to DET */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_ENABLE_EDGE_DETECTION_SID, ICU_E_PARAM_CHANNEL);
  }
  /* Check if the measurement mode is other than Edge Detection */
  else if ((uint8)ICU_MODE_SIGNAL_EDGE_DETECT != Icu_GpChannelConfig[Channel].ucIcuMeasurementMode)                     /* PRQA S 3416 # JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_ENABLE_EDGE_DETECTION_SID, ICU_E_PARAM_CHANNEL);
  }
  #if (ICU_MULTI_CORE_SUPPORT == STD_ON)
  /* Check that the target core is mapping into this channel */
  else if (ICU_ZERO == (Icu_GpChannelConfig[Channel].ucCoreIndex & LucCoreID))                                          /* PRQA S 0404, 3416 # JV-01, JV-01 */
  {
    /* Report to Development Errors */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_ENABLE_EDGE_DETECTION_SID, ICU_E_INVALID_CORE);
  }
  #endif
  else
  #endif /* End of (ICU_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (ICU_MULTI_CORE_SUPPORT == STD_ON)
    /* Read the channel time stamp ram index */
    LucIndex = Icu_GpChannelUserRegConfig[Channel].ucRamDataIndex;
    /* Get the spinlock */
    ICU_ENTER_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
    /* Set request to master core if the shared buffer is ready - not locked by Satellite */
    if(ICU_UNLOCKEDSTATUS(Icu_GaaEnableEdgeDetectionBuffer[LucIndex].blBufferLock))                                     /* PRQA S 3432 # JV-01 */
    {
      /* Lock the shared buffer */
      ICU_LOCKPROCESS(Icu_GaaEnableEdgeDetectionBuffer[LucIndex].blBufferLock);                                         /* PRQA S 3432 # JV-01 */
      /* Release the spinlock */
      ICU_EXIT_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
      /* Request is issued */
      Icu_GaaEnableEdgeDetectionBuffer[LucIndex].blSetRequest = ICU_TRUE;
      /* Release Lock */
      ICU_UNLOCKPROCESS(Icu_GaaEnableEdgeDetectionBuffer[LucIndex].blBufferLock);                                       /* PRQA S 3432 # JV-01 */
    }
    else
    {
      /* Release the spinlock */
      ICU_EXIT_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
      /* Report to Development Errors */
      (void)Det_ReportRuntimeError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_ENABLE_EDGE_DETECTION_SID, ICU_E_REQUEST_FALSE);
    }
    #else
    /* Read the Timer Type for the given channel */
    LucHWIPType = Icu_GpChannelConfig[Channel].ucIcuChannelType;

    /* Enable the edge Detect for the channel */
    if (NULL_PTR != Icu_GaaHwDepFunc[LucHWIPType]->pStartCountMeasurement)                                              /* PRQA S 3416 # JV-01 */
    {
      Icu_GaaHwDepFunc[LucHWIPType]->pStartCountMeasurement(Channel);
    } /* else No action required */
    #endif /* End of (ICU_CRITICAL_SECTION_PROTECTION == STD_ON) */
  } /* End of ICU_INITIALIZED != Icu_GblDriverStatus */
} /* End of API Icu_EnableEdgeDetection */

#define ICU_STOP_SEC_PUBLIC_CODE_GLOBAL
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* #if (ICU_EDGE_DETECT_API == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Icu_DisableEdgeDetection
**
** Service ID            : 0x17
**
** Description           : This API service disables the counting of edges of the requested channel.
**
** Sync/Async            : Synchronous (Single-core) / Asynchronous (Multi-core)
**
** Reentrancy            : Reentrant
**
** Input Parameters      : Channel
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : The Icu Driver must be initialized, ICU_EDGE_DETECT_API must be STD_ON
**
** Global Variables      : Icu_GblDriverStatus, Icu_GpChannelConfig, Icu_GaaHwDepFunc.
**
** Functions invoked     : Det_ReportError, Icu_HW_Atu_StopCountMeasurement,
**                         Icu_HW_Taud_StopCountMeasurement, Icu_HW_Tauj_StopCountMeasurement,
**                         Icu_HW_Pin_DisableEdgeDetection
**
** Registers Used        : None
**
** Reference ID          : ICU_DUD_ACT_024, ICU_DUD_ACT_024_ERR001, ICU_DUD_ACT_024_ERR002, ICU_DUD_ACT_024_ERR003
** Reference ID          : ICU_DUD_ACT_024_ERR004, ICU_DUD_ACT_024_ERR005
** Reference ID          : ICU_DUD_ACT_024_CRT001, ICU_DUD_ACT_024_CRT002
***********************************************************************************************************************/
#if (ICU_EDGE_DETECT_API == STD_ON)
#define ICU_START_SEC_PUBLIC_CODE_GLOBAL
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_PUBLIC_CODE) Icu_DisableEdgeDetection(Icu_ChannelType Channel)                                           /* PRQA S 1503 # JV-01 */
{
  #if (ICU_MULTI_CORE_SUPPORT == STD_OFF)
  /* Defining a pointer to the channel config parameters */
  P2CONST(Icu_ChannelConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannel;
  /* Declare a Local variable to Timer Type */
  volatile uint8 LucHWIPType;
  #else
  /* Local variable to store the channel ram index */
  uint8 LucIndex;
  #endif
  #if (ICU_DEV_ERROR_DETECT == STD_ON)
  #if (ICU_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = ICU_ONE << (uint8)GetCoreID();
  #endif
  /* Check if the Icu Module is not initialized */
  if (ICU_INITIALIZED != Icu_GblDriverStatus)                                                                           /* PRQA S 3416 # JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_DISABLE_EDGE_DETECTION_SID, ICU_E_UNINIT);
  }
  /* Check if the channel is valid */
  else if (ICU_MAX_CHANNEL_ID_CONFIGURED < Channel)
  {
    /* Report Error to DET */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_DISABLE_EDGE_DETECTION_SID, ICU_E_PARAM_CHANNEL);
  }
  /* Check if the measurement mode is other than Edge Detection */
  else if ((uint8)ICU_MODE_SIGNAL_EDGE_DETECT != Icu_GpChannelConfig[Channel].ucIcuMeasurementMode)                     /* PRQA S 3416 # JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_DISABLE_EDGE_DETECTION_SID, ICU_E_PARAM_CHANNEL);
  }
  #if (ICU_MULTI_CORE_SUPPORT == STD_ON)
  /* Check that the target core is mapping into this channel */
  else if (ICU_ZERO == (Icu_GpChannelConfig[Channel].ucCoreIndex & LucCoreID))                                          /* PRQA S 0404, 3416 # JV-01, JV-01 */
  {
    /* Report to Development Errors */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_DISABLE_EDGE_DETECTION_SID, ICU_E_INVALID_CORE);
  }
  #endif
  else
  #endif /* End of (ICU_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (ICU_MULTI_CORE_SUPPORT == STD_ON)
    /* Read the channel time stamp ram index */
    LucIndex = Icu_GpChannelUserRegConfig[Channel].ucRamDataIndex;
    /* Get the spinlock */
    ICU_ENTER_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
    /* Set request to master core if the shared buffer is ready - not locked by Satellite */
    if(ICU_UNLOCKEDSTATUS(Icu_GaaDisableEdgeDetectionBuffer[LucIndex].blBufferLock))                                    /* PRQA S 3432 # JV-01 */
    {
      /* Lock the shared buffer */
      ICU_LOCKPROCESS(Icu_GaaDisableEdgeDetectionBuffer[LucIndex].blBufferLock);                                        /* PRQA S 3432 # JV-01 */
      /* Release the spinlock */
      ICU_EXIT_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
      /* Request is issued */
      Icu_GaaDisableEdgeDetectionBuffer[LucIndex].blSetRequest = ICU_TRUE;
      /* Release Lock */
      ICU_UNLOCKPROCESS(Icu_GaaDisableEdgeDetectionBuffer[LucIndex].blBufferLock);                                      /* PRQA S 3432 # JV-01 */
    }
    else
    {
      /* Release the spinlock */
      ICU_EXIT_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
      /* Report to Development Errors */
      (void)Det_ReportRuntimeError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_DISABLE_EDGE_DETECTION_SID, ICU_E_REQUEST_FALSE);
    }
    #else
    /* Updating the channel config parameter to the current channel */
    LpChannel = &Icu_GpChannelConfig[Channel];

    /* Read the Timer Type for the given channel */
    LucHWIPType = LpChannel->ucIcuChannelType;

    /* Enable the edge Detect for the channel */
    if (NULL_PTR != Icu_GaaHwDepFunc[LucHWIPType]->pStopCountMeasurement)                                               /* PRQA S 3416 # JV-01 */
    {
      Icu_GaaHwDepFunc[LucHWIPType]->pStopCountMeasurement(Channel);
    } /* else No action required */
    #endif /* End of ICU_MULTI_CORE_SUPPORT == STD_ON */
  } /* End of ICU_INITIALIZED != Icu_GblDriverStatus */
} /* End of API Icu_DisableEdgeDetection */

#define ICU_STOP_SEC_PUBLIC_CODE_GLOBAL
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* #if (ICU_EDGE_DETECT_API == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Icu_GetEdgeNumbers
**
** Service ID            : 0x0F
**
** Description           : This API service reads the number of counted edges after the last reset of edges happened.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : Channel
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : Icu_EdgeNumberType
**
** Preconditions         : The Icu Driver must be initialized, ICU_EDGE_COUNT_API must be STD_ON

** Global Variables      : Icu_GblDriverStatus, Icu_GpChannelConfig
**                         Icu_GpChannelUserRegConfig, Icu_GpEdgeCountData,
**                         Icu_GaaHwDepFunc.
**
** Functions invoked     : Det_ReportError, Icu_HW_Taud_GetEdgeNumbers.
**
** Registers Used        : None
**
** Reference ID          : ICU_DUD_ACT_016, ICU_DUD_ACT_016_ERR001, ICU_DUD_ACT_016_ERR002, ICU_DUD_ACT_016_ERR003
** Reference ID          : ICU_DUD_ACT_016_ERR004
***********************************************************************************************************************/
#if (ICU_EDGE_COUNT_API == STD_ON)
#define ICU_START_SEC_PUBLIC_CODE_GLOBAL
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(Icu_EdgeNumberType, ICU_PUBLIC_CODE) Icu_GetEdgeNumbers(Icu_ChannelType Channel)                                   /* PRQA S 1503 # JV-01 */
{
  /* Return value */
  Icu_EdgeNumberType LddEdgeCount;
  /* Ram index */
  uint8 LucRamIndex;
  /* Defining a pointer to the channel config parameters */
  P2CONST(Icu_ChannelConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannel;
  /* Declare a Local variable to Timer Type */
  volatile uint8 LucTimerType;
  #if (ICU_DEV_ERROR_DETECT == STD_ON)
  #if (ICU_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = ICU_ONE << (uint8)GetCoreID();
  #endif
  /* Initial value */
  LddEdgeCount = (uint32)ICU_ZERO;
  /* Check if the Icu Module is not initialized */
  if (ICU_INITIALIZED != Icu_GblDriverStatus)                                                                           /* PRQA S 3416 # JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_GET_EDGE_NUMBERS_SID, ICU_E_UNINIT);
  }
  /* Check if the channel is valid */
  else if (ICU_MAX_CHANNEL_ID_CONFIGURED < Channel)
  {
    /* Report Error to DET */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_GET_EDGE_NUMBERS_SID, ICU_E_PARAM_CHANNEL);
  }
  /* Check if the measurement mode is other than Edge counting */
  else if ((uint8)(ICU_MODE_EDGE_COUNTER) != Icu_GpChannelConfig[Channel].ucIcuMeasurementMode)                         /* PRQA S 3416 # JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_GET_EDGE_NUMBERS_SID, ICU_E_PARAM_CHANNEL);
  }
  #if (ICU_MULTI_CORE_SUPPORT == STD_ON)
  /* Check that the target core is mapping into this channel */
  else if (ICU_ZERO == (Icu_GpChannelConfig[Channel].ucCoreIndex & LucCoreID))                                          /* PRQA S 0404, 3416 # JV-01, JV-01 */
  {
    /* Report to Development Errors */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_GET_EDGE_NUMBERS_SID, ICU_E_INVALID_CORE);
  }
  #endif
  else
  #endif /* End of (ICU_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Read the channel ram index */
    LucRamIndex = Icu_GpChannelUserRegConfig[Channel].ucRamDataIndex;
    /* Updating the channel config parameter to the current channel */
    LpChannel = &Icu_GpChannelConfig[Channel];
    /* Read the Timer Type for the given channel  */
    LucTimerType = LpChannel->ucIcuChannelType;
    if (NULL_PTR != Icu_GaaHwDepFunc[LucTimerType]->pGetEdgeNumbers)                                                    /* PRQA S 3416 # JV-01 */
    {
      Icu_GaaHwDepFunc[LucTimerType]->pGetEdgeNumbers(Channel);
    } /* else No action required */
    LddEdgeCount = (Icu_EdgeNumberType)Icu_GpEdgeCountData[LucRamIndex].ulIcuEdgeCount;                                 /* PRQA S 0404 # JV-01 */
  } /* End of ICU_INITIALIZED != Icu_GblDriverStatus */
  return (LddEdgeCount);
} /* End of API Icu_GetEdgeNumbers */

#define ICU_STOP_SEC_PUBLIC_CODE_GLOBAL
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of (ICU_EDGE_COUNT_API == STD_ON) */
/***********************************************************************************************************************
** Function Name         : Icu_StartSignalMeasurement
**
** Service ID            : 0x13
**
** Description           : This API starts the measurement of signals beginning
**                         with the configured default start edge which occurs first after the call of this service.
**
** Sync/Async            : Synchronous (Single-core) / Asynchronous (Multi-core)
**
** Reentrancy            : Reentrant
**
** Input Parameters      : Channel
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : The Icu Driver must be initialized, ICU_SIGNAL_MEASUREMENT_API must be STD_ON
**
** Global Variables      : Icu_GpChannelConfig, Icu_GblDriverStatus, Icu_GpChannelRamData, 
**                         Icu_GaaHwDepFunc, Icu_GpChannelUserRegConfig.
**
** Functions invoked     : Det_ReportError, Icu_HW_Atu_StartCountMeasurement,
**                         Icu_HW_Taud_StartCountMeasurement, Icu_HW_Tauj_StartCountMeasurement
**
** Registers Used        : None
**
** Reference ID          : ICU_DUD_ACT_020_ERR002, ICU_DUD_ACT_020_ERR003, ICU_DUD_ACT_020_ERR001
** Reference ID          : ICU_DUD_ACT_020_GBL001, ICU_DUD_ACT_020_GBL002, ICU_DUD_ACT_020_GBL003
** Reference ID          : ICU_DUD_ACT_020_ERR004, ICU_DUD_ACT_020_CRT001, ICU_DUD_ACT_020_CRT002, ICU_DUD_ACT_020
** Reference ID          : ICU_DUD_ACT_020_ERR005, ICU_DUD_ACT_020_ERR006
***********************************************************************************************************************/
#if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)
#define ICU_START_SEC_PUBLIC_CODE_GLOBAL
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_PUBLIC_CODE) Icu_StartSignalMeasurement(Icu_ChannelType Channel)                                         /* PRQA S 1503 # JV-01 */
{
  #if (ICU_MULTI_CORE_SUPPORT == STD_OFF)
  /* Defining a pointer to the channel config parameters */
  P2CONST(Icu_ChannelConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannel;
  /* Defining a pointer to the timer channel configuration parameters */
  P2CONST(Icu_ChannelUserRegConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannelUserRegConfig;
  /* Declare a Local variable to Timer Type */
  volatile uint8 LucTimerType;
  #else
  /* Local variable to store the channel ram index */
  uint8 LucIndex;
  #endif
  #if (ICU_DEV_ERROR_DETECT == STD_ON)
  #if (ICU_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = ICU_ONE << (uint8)GetCoreID();
  #endif
  /* Check if the Icu Module is not initialized */
  if (ICU_INITIALIZED != Icu_GblDriverStatus)                                                                           /* PRQA S 3416 # JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_START_SIGNAL_MEASUREMENT_SID, ICU_E_UNINIT);
  }
  /* Check if the channel is valid */
  else if (ICU_MAX_CHANNEL_ID_CONFIGURED < Channel)
  {
    /* Report Error to DET */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_START_SIGNAL_MEASUREMENT_SID, ICU_E_PARAM_CHANNEL);
  }
  /* Check if the measurement mode is other than Signal measurement */
  else if ((uint8)ICU_MODE_SIGNAL_MEASUREMENT != Icu_GpChannelConfig[Channel].ucIcuMeasurementMode)                     /* PRQA S 3416 # JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_START_SIGNAL_MEASUREMENT_SID, ICU_E_PARAM_CHANNEL);
  }
  /* Check if the channel is configured for extra duty channel */
  else if (ICU_FIVE == (uint8)(Icu_GpChannelUserRegConfig[Channel].ucChannelProperties))                                /* PRQA S 3416 # JV-01 */
  {
    /* Report Error to Det */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_START_SIGNAL_MEASUREMENT_SID, ICU_E_PARAM_CHANNEL);
  }
  #if (ICU_MULTI_CORE_SUPPORT == STD_ON)
  /* Check that the target core is mapping into this channel */
  else if (ICU_ZERO == (Icu_GpChannelConfig[Channel].ucCoreIndex & LucCoreID))                                          /* PRQA S 0404, 3416 # JV-01, JV-01 */
  {
    /* Report to Development Errors */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_START_SIGNAL_MEASUREMENT_SID, ICU_E_INVALID_CORE);
  }
  #endif
  else
  #endif /* End of (ICU_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (ICU_MULTI_CORE_SUPPORT == STD_ON)
    /* Read the channel time stamp ram index */
    LucIndex = Icu_GpChannelUserRegConfig[Channel].ucRamDataIndex;
    /* Get the spinlock */
    ICU_ENTER_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
    /* Set request to master core if the shared buffer is ready - not locked by Satellite */
    if(ICU_UNLOCKEDSTATUS(Icu_GaaStartSignalMeasurementBuffer[LucIndex].blBufferLock))                                  /* PRQA S 3432 # JV-01 */
    {
      /* Lock the shared buffer */
      ICU_LOCKPROCESS(Icu_GaaStartSignalMeasurementBuffer[LucIndex].blBufferLock);                                      /* PRQA S 3432 # JV-01 */
      /* Release the spinlock */
      ICU_EXIT_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
      /* Request is issued */
      Icu_GaaStartSignalMeasurementBuffer[LucIndex].blSetRequest = ICU_TRUE;
      /* Release Lock */
      ICU_UNLOCKPROCESS(Icu_GaaStartSignalMeasurementBuffer[LucIndex].blBufferLock);                                    /* PRQA S 3432 # JV-01 */
    }
    else
    {
      /* Release the spinlock */
      ICU_EXIT_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
      /* Report to Development Errors */
      (void)Det_ReportRuntimeError(ICU_MODULE_ID, ICU_INSTANCE_ID,
                                                               ICU_START_SIGNAL_MEASUREMENT_SID, ICU_E_REQUEST_FALSE);
    }
    #else
    /* Updating the channel config parameter to the current channel */
    LpChannel = &Icu_GpChannelConfig[Channel];

    /* Read timer channel configuration pointer */
    LpChannelUserRegConfig = &Icu_GpChannelUserRegConfig[Channel];

    /* Read the Timer Type for the given channel */
    LucTimerType = LpChannel->ucIcuChannelType;
    /* Start count measurement for the channel */
    if (NULL_PTR != Icu_GaaHwDepFunc[LucTimerType]->pStartCountMeasurement)                                             /* PRQA S 3416 # JV-01 */
    {
      Icu_GaaHwDepFunc[LucTimerType]->pStartCountMeasurement(Channel);
    } /* else No action required */
    /* Initialize channel status as idle */
    Icu_GpChannelRamData[Channel].ucChannelStatus = (uint8)ICU_IDLE;

    /* Set result status is FALSE for channel */
    Icu_GpChannelRamData[Channel].blResultComplete = ICU_FALSE;

    /* If the channel is duty cycle channel, set result status is FALSE for extra channel */
    if (((uint8)(LpChannelUserRegConfig->ucChannelProperties &
                                                         ICU_DUTY_PERIOD_ENABLED_MASK)) == ICU_DUTY_PERIOD_ENABLED_MASK)
    {
      /* Set result status is FALSE for extra channel */
      Icu_GpChannelRamData[Channel + ICU_ONE].blResultComplete = ICU_FALSE;
    } /* else No action required */
    #endif /* End of ICU_MULTI_CORE_SUPPORT == STD_ON */
  } /* End of ICU_INITIALIZED != Icu_GblDriverStatus */
} /* End of API Icu_StartSignalMeasurement */

#define ICU_STOP_SEC_PUBLIC_CODE_GLOBAL
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* End of (ICU_SIGNAL_MEASUREMENT_API == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Icu_StopSignalMeasurement
**
** Service ID            : 0x14
**
** Description           : This API stops the measurement of signals of the given channel.
**
** Sync/Async            : Synchronous (Single-core) / Asynchronous (Multi-core)
**
** Reentrancy            : Reentrant
**
** Input Parameters      : Channel
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : The Icu Driver must be initialized, ICU_SIGNAL_MEASUREMENT_API must be STD_ON
**
** Global Variables      : Icu_GpChannelConfig, Icu_GblDriverStatus,
**                         Icu_GaaHwDepFunc, Icu_GpChannelUserRegConfig.
**
** Functions invoked     : Det_ReportError, Icu_HW_Atu_StopCountMeasurement,
**                         Icu_HW_Taud_StopCountMeasurement, Icu_HW_Tauj_StopCountMeasurement
**
** Registers Used        : None
**
** Reference ID          : ICU_DUD_ACT_021, ICU_DUD_ACT_021_ERR001, ICU_DUD_ACT_021_ERR002, ICU_DUD_ACT_021_ERR003
** Reference ID          : ICU_DUD_ACT_021_ERR004, ICU_DUD_ACT_021_ERR005, ICU_DUD_ACT_021_ERR006
** Reference ID          : ICU_DUD_ACT_021_CRT001, ICU_DUD_ACT_021_CRT002
***********************************************************************************************************************/
#if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)
#define ICU_START_SEC_PUBLIC_CODE_GLOBAL
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_PUBLIC_CODE) Icu_StopSignalMeasurement(Icu_ChannelType Channel)                                          /* PRQA S 1503 # JV-01 */
{
  #if (ICU_MULTI_CORE_SUPPORT == STD_OFF)
  /* Defining a pointer to the channel config parameters */
  P2CONST(Icu_ChannelConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannel;
  /* Declare a Local variable to Timer Type */
  volatile uint8 LucTimerType;
  #else
  /* Local variable to store the channel ram index */
  uint8 LucIndex;
  #endif
  #if (ICU_DEV_ERROR_DETECT == STD_ON)
  #if (ICU_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = ICU_ONE << (uint8)GetCoreID();
  #endif
  /* Check if the Icu Module is not initialized */
  if (ICU_INITIALIZED != Icu_GblDriverStatus)                                                                           /* PRQA S 3416 # JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_STOP_SIGNAL_MEASUREMENT_SID, ICU_E_UNINIT);
  }
  /* Check if the channel is valid */
  else if (ICU_MAX_CHANNEL_ID_CONFIGURED < Channel)
  {
    /* Report Error to DET */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_STOP_SIGNAL_MEASUREMENT_SID, ICU_E_PARAM_CHANNEL);
  }
  /* Check if the measurement mode is other than Signal measurement */
  else if ((uint8)ICU_MODE_SIGNAL_MEASUREMENT != Icu_GpChannelConfig[Channel].ucIcuMeasurementMode)                     /* PRQA S 3416 # JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_STOP_SIGNAL_MEASUREMENT_SID, ICU_E_PARAM_CHANNEL);
  }
  /* Check if the channel is configured for extra duty channel */
  else if (ICU_FIVE == (uint8)(Icu_GpChannelUserRegConfig[Channel].ucChannelProperties))                                /* PRQA S 3416 # JV-01 */
  {
    /* Report Error to Det */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_STOP_SIGNAL_MEASUREMENT_SID, ICU_E_PARAM_CHANNEL);
  }
  #if (ICU_MULTI_CORE_SUPPORT == STD_ON)
  /* Check that the target core is mapping into this channel */
  else if (ICU_ZERO == (Icu_GpChannelConfig[Channel].ucCoreIndex & LucCoreID))                                          /* PRQA S 0404, 3416 # JV-01, JV-01 */
  {
    /* Report to Development Errors */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_STOP_SIGNAL_MEASUREMENT_SID, ICU_E_INVALID_CORE);
  }
  #endif
  else
  #endif /* End of (ICU_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (ICU_MULTI_CORE_SUPPORT == STD_ON)
    /* Read the channel time stamp ram index */
    LucIndex = Icu_GpChannelUserRegConfig[Channel].ucRamDataIndex;
    /* Get the spinlock */
    ICU_ENTER_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
    /* Set request to master core if the shared buffer is ready - not locked by Satellite */
    if(ICU_UNLOCKEDSTATUS(Icu_GaaStopSignalMeasurementBuffer[LucIndex].blBufferLock))                                   /* PRQA S 3432 # JV-01 */
    {
      /* Lock the shared buffer */
      ICU_LOCKPROCESS(Icu_GaaStopSignalMeasurementBuffer[LucIndex].blBufferLock);                                       /* PRQA S 3432 # JV-01 */
      /* Release the spinlock */
      ICU_EXIT_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
      /* Request is issued */
      Icu_GaaStopSignalMeasurementBuffer[LucIndex].blSetRequest = ICU_TRUE;
      /* Release Lock */
      ICU_UNLOCKPROCESS(Icu_GaaStopSignalMeasurementBuffer[LucIndex].blBufferLock);                                     /* PRQA S 3432 # JV-01 */
    }
    else
    {
      /* Release the spinlock */
      ICU_EXIT_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
      /* Report to Development Errors */
      (void)Det_ReportRuntimeError(ICU_MODULE_ID, ICU_INSTANCE_ID,
                                                                ICU_STOP_SIGNAL_MEASUREMENT_SID, ICU_E_REQUEST_FALSE);
    }
    #else
    /* Updating the channel config parameter to the current channel */
    LpChannel = &Icu_GpChannelConfig[Channel];
    /* Read the Timer Type for the given channel */
    LucTimerType = LpChannel->ucIcuChannelType;
    /* Stop count measurement for the channel */
    if (NULL_PTR != Icu_GaaHwDepFunc[LucTimerType]->pStopCountMeasurement)                                              /* PRQA S 3416 # JV-01 */
    {
      Icu_GaaHwDepFunc[LucTimerType]->pStopCountMeasurement(Channel);
    } /* else No action required */
    #endif /* End of ICU_MULTI_CORE_SUPPORT == STD_ON */
  } /* End of ICU_INITIALIZED != Icu_GblDriverStatus */
} /* End of API Icu_StopSignalMeasurement */

#define ICU_STOP_SEC_PUBLIC_CODE_GLOBAL
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of (ICU_SIGNAL_MEASUREMENT_API == STD_ON) */
/***********************************************************************************************************************
** Function Name         : Icu_GetTimeElapsed
**
** Service ID            : 0x10
**
** Description           : This API service reads the elapsed signal time (Low
**                         Time, High Time or Period Time) of the requested channel as configured.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : Channel
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : Icu_ValueType
**
** Preconditions         : The Icu Driver must be initialized, ICU_GET_TIME_ELAPSED_API must be STD_ON
**
** Global Variables      : Icu_GpChannelConfig, Icu_GblDriverStatus, Icu_GpChannelRamData, 
**                         Icu_GpChannelUserRegConfig, Icu_GpSignalMeasurementData.
**
** Functions invoked     : Det_ReportError.
**
** Registers Used        : None
**
** Reference ID          : ICU_DUD_ACT_017, ICU_DUD_ACT_017_CRT001
** Reference ID          : ICU_DUD_ACT_017_ERR002, ICU_DUD_ACT_017_ERR003, ICU_DUD_ACT_017_GBL003
** Reference ID          : ICU_DUD_ACT_017_GBL001, ICU_DUD_ACT_017_GBL002, ICU_DUD_ACT_017_GBL004
** Reference ID          : ICU_DUD_ACT_017_ERR004, ICU_DUD_ACT_017_ERR001, ICU_DUD_ACT_017_CRT002
** Reference ID          : ICU_DUD_ACT_017_ERR005
***********************************************************************************************************************/
#if (ICU_GET_TIME_ELAPSED_API == STD_ON)
#define ICU_START_SEC_PUBLIC_CODE_GLOBAL
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(Icu_ValueType, ICU_PUBLIC_CODE) Icu_GetTimeElapsed(Icu_ChannelType Channel)                                        /* PRQA S 1503 # JV-01 */
{
  /* Local variable */
  uint8 LucMeasureProperty;
  uint8 LucIndex;
  Icu_ValueType LddSignalTime;

  #if (ICU_DEV_ERROR_DETECT == STD_ON)
  #if (ICU_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = ICU_ONE << (uint8)GetCoreID();
  #endif
  /* Set the initial value for return value */
  LddSignalTime = (uint32)ICU_SIGNAL_TIME_INIT_VAL;
  /* Check if the Icu Module is not initialized */
  if (ICU_INITIALIZED != Icu_GblDriverStatus)                                                                           /* PRQA S 3416 # JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_GET_TIME_ELAPSED_SID, ICU_E_UNINIT);
  }
  /* Check if the channel is valid */
  else if (ICU_MAX_CHANNEL_ID_CONFIGURED < Channel)
  {
    /* Report Error to DET */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_GET_TIME_ELAPSED_SID, ICU_E_PARAM_CHANNEL);
  }
  /* Check if the measurement mode is other than Signal measurement */
  else if ((uint8)ICU_MODE_SIGNAL_MEASUREMENT != Icu_GpChannelConfig[Channel].ucIcuMeasurementMode)                     /* PRQA S 3416 # JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_GET_TIME_ELAPSED_SID, ICU_E_PARAM_CHANNEL);
  }
  else if (ICU_FIVE == (uint8)(Icu_GpChannelUserRegConfig[Channel].ucChannelProperties))                                /* PRQA S 3416 # JV-01 */
  {
    /* Report Error to Det */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_GET_TIME_ELAPSED_SID, ICU_E_PARAM_CHANNEL);
  }
  #if (ICU_MULTI_CORE_SUPPORT == STD_ON)
  /* Check that the target core is mapping into this channel */
  else if (ICU_ZERO == (Icu_GpChannelConfig[Channel].ucCoreIndex & LucCoreID))                                          /* PRQA S 0404, 3416 # JV-01, JV-01 */
  {
    /* Report to Development Errors */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_GET_TIME_ELAPSED_SID, ICU_E_INVALID_CORE);
  }
  #endif
  else
  #endif /* End of (ICU_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Set the initial value for return value */
    LddSignalTime = (uint32)ICU_SIGNAL_TIME_INIT_VAL;
    /* Load the channel measure property */
    LucMeasureProperty = Icu_GpChannelUserRegConfig[Channel].ucChannelProperties;
    /* Get the index of the RAM data */
    LucIndex = Icu_GpChannelUserRegConfig[Channel].ucRamDataIndex;
    #if (ICU_GTM_TIMER_UNIT_USED == STD_ON)
    /* Get the pulse data by invoking lowlayer function - GTM only */
    if (NULL_PTR != Icu_GaaHwDepFunc[Icu_GpChannelConfig[Channel].ucIcuChannelType]->pGetPulseData)                     /* PRQA S 3416 # JV-01 */
    {
      Icu_GaaHwDepFunc[Icu_GpChannelConfig[Channel].ucIcuChannelType]->pGetPulseData(Channel);
    } /* else No action required */
    #endif
    /* Get the spinlock since ulSignalPeriodTime, ulSignalActiveTime, blResultComplete be updated by satellite core */
    ICU_ENTER_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
    /* Check for the status of result channel */
    if (ICU_TRUE == Icu_GpChannelRamData[Channel].blResultComplete)                                                     /* PRQA S 0404, 3416 # JV-01, JV-01 */
    {
      /* Check if measurement mode is either low or high */
      if ((ICU_HIGH_TIME_MASK == (uint8)(LucMeasureProperty)) || (ICU_LOW_TIME_MASK == (uint8)(LucMeasureProperty)))
      {
        /* Read the captured Signal Active Time */
        LddSignalTime = Icu_GpSignalMeasurementData[LucIndex].ulSignalActiveTime;                                       /* PRQA S 0404 # JV-01 */
        Icu_GpSignalMeasurementData[LucIndex].ulSignalActiveTime = (uint32)ICU_ACTIVE_TIME_RESET_VAL;
        /* Disable for the status of result Channel */
        Icu_GpChannelRamData[Channel].blResultComplete = ICU_FALSE;
      } /* End of ((LucMeasureProperty & ICU_HIGH_TIME_MASK) < ICU_TWO) */
      /* Check if measurement mode is for period time */
      else if ((uint8)ICU_PERIOD_TIME_MASK == (uint8)(LucMeasureProperty & ICU_HIGH_LOW_TIME_MASK))                     /* PRQA S 2004 # JV-01 */
      {
        /* Read the captured Signal Period Time */
        LddSignalTime = Icu_GpSignalMeasurementData[LucIndex].ulSignalPeriodTime;                                       /* PRQA S 0404 # JV-01 */

        Icu_GpSignalMeasurementData[LucIndex].ulSignalPeriodTime = (uint32)ICU_PERIOD_TIME_RESET_VAL;
        /* Disable for the status of result Channel */
        Icu_GpChannelRamData[Channel].blResultComplete = ICU_FALSE;
      } /* else No action required */
    } /* else No action required */
    ICU_EXIT_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
  } /* End of ICU_INITIALIZED != Icu_GblDriverStatus */
  return (LddSignalTime);
} /* End of API Icu_GetTimeElapsed */

#define ICU_STOP_SEC_PUBLIC_CODE_GLOBAL
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of (ICU_GET_TIME_ELAPSED_API == STD_ON) */
/***********************************************************************************************************************
** Function Name         : Icu_GetDutyCycleValues
**
** Service ID            : 0x11
**
** Description           : This API service reads the coherent high time and period time for the requested Icu channel.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : Channel
**
** InOut Parameters      : None
**
** Output Parameters     : DutyCycleValues
**
** Return parameter      : None
**
** Preconditions         : The Icu Driver must be initialized, ICU_GET_DUTY_CYCLE_VALUES_API must be STD_ON
**
** Global Variables      : Icu_GpChannelConfig, Icu_GpChannelUserRegConfig,
**                         Icu_GblDriverStatus, Icu_GpSignalMeasurementData
**                         Icu_GpChannelRamData.
**
** Functions invoked     : Det_ReportError.
**
** Registers Used        : None
**
** Reference ID          : ICU_DUD_ACT_018, ICU_DUD_ACT_018_CRT001, ICU_DUD_ACT_018_CRT002
** Reference ID          : ICU_DUD_ACT_018_ERR004, ICU_DUD_ACT_018_ERR003, ICU_DUD_ACT_018_ERR006
** Reference ID          : ICU_DUD_ACT_018_ERR002, ICU_DUD_ACT_018_GBL001, ICU_DUD_ACT_018_ERR005
** Reference ID          : ICU_DUD_ACT_018_GBL002, ICU_DUD_ACT_018_ERR001, ICU_DUD_ACT_018_ERR007
***********************************************************************************************************************/
#if (ICU_GET_DUTY_CYCLE_VALUES_API == STD_ON)
#define ICU_START_SEC_PUBLIC_CODE_GLOBAL
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_PUBLIC_CODE)
Icu_GetDutyCycleValues(Icu_ChannelType Channel, P2VAR(Icu_DutyCycleType, AUTOMATIC, ICU_APPL_DATA) DutyCycleValues)     /* PRQA S 1503, 3432 # JV-01, JV-01 */
{
  /* Local variable to store the channel ram index */
  uint8 LucIndex;

  #if (ICU_DEV_ERROR_DETECT == STD_ON)
  #if (ICU_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = ICU_ONE << (uint8)GetCoreID();
  #endif
  /* Check if the Icu Module is not initialized */
  if (ICU_INITIALIZED != Icu_GblDriverStatus)                                                                           /* PRQA S 3416 # JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_GET_DUTY_CYCLE_VALUES_SID, ICU_E_UNINIT);
  }
  /* Check if the channel is valid */
  else if (ICU_MAX_CHANNEL_ID_CONFIGURED < Channel)
  {
    /* Report Error to DET */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_GET_DUTY_CYCLE_VALUES_SID, ICU_E_PARAM_CHANNEL);
  }
  /* Check if the measurement mode is other than Signal measurement */
  else if ((uint8)ICU_MODE_SIGNAL_MEASUREMENT != Icu_GpChannelConfig[Channel].ucIcuMeasurementMode)                     /* PRQA S 3416 # JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_GET_DUTY_CYCLE_VALUES_SID, ICU_E_PARAM_CHANNEL);
  }
  /* Check if the channel is configured for duty cycle measurement */
  else if ((uint8)ICU_DUTY_PERIOD_ENABLED_MASK != 
                      (uint8)(Icu_GpChannelUserRegConfig[Channel].ucChannelProperties & ICU_DUTY_PERIOD_ENABLED_MASK))  /* PRQA S 3416 # JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_GET_DUTY_CYCLE_VALUES_SID, ICU_E_PARAM_CHANNEL);
  }
  /* Check if the channel is configured for the extra channel */
  else if (ICU_EXTRA_CHANNEL_DISABLED_MASK ==
                            (uint8)(Icu_GpChannelUserRegConfig[Channel].ucChannelProperties & ICU_HIGH_LOW_TIME_MASK))  /* PRQA S 3416 # JV-01 */
  {
    /* Report Error to Det */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_GET_DUTY_CYCLE_VALUES_SID, ICU_E_PARAM_CHANNEL);
  }
  /* Check if the pointer passed is Null */
  else if (NULL_PTR == DutyCycleValues)
  {
    /* Report Error to DET */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_GET_DUTY_CYCLE_VALUES_SID, ICU_E_PARAM_POINTER);
  }
  #if (ICU_MULTI_CORE_SUPPORT == STD_ON)
  /* Check that the target core is mapping into this channel */
  else if (ICU_ZERO == (Icu_GpChannelConfig[Channel].ucCoreIndex & LucCoreID))                                          /* PRQA S 0404, 3416 # JV-01, JV-01 */
  {
    /* Report to Development Errors */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_GET_DUTY_CYCLE_VALUES_SID, ICU_E_INVALID_CORE);
  }
  #endif
  else
  #endif /* End of (ICU_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Initial value */
    DutyCycleValues->ActiveTime = (uint32)ICU_ACTIVE_TIME_INIT_VAL;
    DutyCycleValues->PeriodTime = (uint32)ICU_PERIOD_TIME_INIT_VAL;
    /* Read channel's RAM Index */
    LucIndex = Icu_GpChannelUserRegConfig[Channel].ucRamDataIndex;
    #if (ICU_GTM_TIMER_UNIT_USED == STD_ON)
    /* Get the input state by invoking lowlayer function - GTM only */
    if (NULL_PTR != Icu_GaaHwDepFunc[Icu_GpChannelConfig[Channel].ucIcuChannelType]->pGetPulseData)                     /* PRQA S 3416 # JV-01 */
    {
      Icu_GaaHwDepFunc[Icu_GpChannelConfig[Channel].ucIcuChannelType]->pGetPulseData(Channel);
    } /* else No action required */
    #endif
    /* Get the spinlock since ulSignalPeriodTime, blResultComplete be updated by satellite core */
    ICU_ENTER_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
    /* Check if the HW is GTM or TAU/ATU */
    if (ICU_HW_GTM_TIM != Icu_GpChannelConfig[Channel].ucIcuChannelType)                                                /* PRQA S 3416 # JV-01 */
    {
      if ((ICU_TRUE == Icu_GpChannelRamData[Channel].blResultComplete) &&                                               /* PRQA S 0404, 3416 # JV-01, JV-01 */
          (ICU_TRUE == Icu_GpChannelRamData[Channel + ICU_ONE].blResultComplete))                                       /* PRQA S 3415, 3416 # JV-01, JV-01 */
      {
        /* Check if a valid period is finished */
        if ((uint32)ICU_PERIOD_TIME_RESET_VAL < Icu_GpSignalMeasurementData[LucIndex].ulSignalPeriodTime)               /* PRQA S 0404, 3416 # JV-01, JV-01 */
        {
          DutyCycleValues->ActiveTime = Icu_GpSignalMeasurementData[LucIndex].ulPrevSignalActiveTime;                   /* PRQA S 0404 # JV-01 */

          /* Read the captured Signal Period Time */
          DutyCycleValues->PeriodTime = Icu_GpSignalMeasurementData[LucIndex].ulSignalPeriodTime;                       /* PRQA S 0404 # JV-01 */

          Icu_GpSignalMeasurementData[LucIndex].ulSignalPeriodTime = (uint32)ICU_PERIOD_TIME_RESET_VAL;

          /* Disable the status of result Channel */
          Icu_GpChannelRamData[Channel].blResultComplete = ICU_FALSE;
          Icu_GpChannelRamData[Channel + ICU_ONE].blResultComplete = ICU_FALSE;
        } /* else No action required */
      } /* else No action required */
    }
    else /* Incase of GTM */
    {
      /* Check if result available */
      if (ICU_TRUE == Icu_GpChannelRamData[Channel].blResultComplete)                                                   /* PRQA S 0404, 3416 # JV-01, JV-01 */
      {
        /* Check if a valid period is finished */
        if ((uint32)ICU_PERIOD_TIME_RESET_VAL < Icu_GpSignalMeasurementData[LucIndex].ulSignalPeriodTime)               /* PRQA S 0404, 3416 # JV-01, JV-01 */
        {
          /* Load the active time */
          DutyCycleValues->ActiveTime = Icu_GpSignalMeasurementData[LucIndex].ulSignalActiveTime;                       /* PRQA S 0404 # JV-01 */
          /* Load the period time */
          DutyCycleValues->PeriodTime = Icu_GpSignalMeasurementData[LucIndex].ulSignalPeriodTime;                       /* PRQA S 0404 # JV-01 */
          /* Clear the active time */
          Icu_GpSignalMeasurementData[LucIndex].ulSignalActiveTime = ICU_DOUBLE_ZERO;
          /* Clear the period time */
          Icu_GpSignalMeasurementData[LucIndex].ulSignalPeriodTime = ICU_DOUBLE_ZERO;
          /* Disable the status of result Channel */
          Icu_GpChannelRamData[Channel].blResultComplete = ICU_FALSE;
        } /* else No action required */
      } /* else No action required */
    } /* End of checking GTM channel */
    /* Release the spinlock */
    ICU_EXIT_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
  } /* End of ICU_INITIALIZED != Icu_GblDriverStatus */
} /* End of API Icu_GetDutyCycleValues */

#define ICU_STOP_SEC_PUBLIC_CODE_GLOBAL
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of (ICU_GET_DUTY_CYCLE_VALUES_API == STD_ON) */
/***********************************************************************************************************************
** Function Name         : Icu_GetInputLevel
**
** Service ID            : 0xA0
**
** Description           : This API service returns the state of the input pin related to the ICU channel
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LddChannel
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : Icu_LevelType
**
** Preconditions         : The Icu Driver must be initialized, ICU_GET_INPUT_LEVEL_API must be STD_ON
**
** Global Variables      : Icu_GblDriverStatus, Icu_GpChannelConfig, Icu_GaaHwDepFunc.
**
** Functions invoked     : Det_ReportError, Icu_HW_GetInputLevel.
**
** Registers Used        : None
**
** Reference ID          : ICU_DUD_ACT_025, ICU_DUD_ACT_025_ERR001, ICU_DUD_ACT_025_ERR002, ICU_DUD_ACT_025_ERR003
***********************************************************************************************************************/
#if (ICU_GET_INPUT_LEVEL_API == STD_ON)
#define ICU_START_SEC_PUBLIC_CODE_GLOBAL
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(Icu_LevelType, ICU_PUBLIC_CODE) Icu_GetInputLevel(Icu_ChannelType LddChannel)                                      /* PRQA S 1503 # JV-01 */
{
  /* Defining a pointer to the channel config parameters */
  P2CONST(Icu_ChannelConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannel;
  /* Declare a Local variable to Timer Type */
  volatile uint8 LucHWIPType;
  /* Local variable to store the return level value  */
  Icu_LevelType LddInputLevel;
  #if (ICU_DEV_ERROR_DETECT == STD_ON)
  #if (ICU_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = ICU_ONE << (uint8)GetCoreID();
  #endif
  /* Initial value */
  LddInputLevel = ICU_LOW;
  /* Check if the Icu Module is not initialized */
  if (ICU_INITIALIZED != Icu_GblDriverStatus)                                                                           /* PRQA S 3416 # JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_GET_INPUT_LEVEL_SID, ICU_E_UNINIT);
  }
  /* Check if the channel is valid */
  else if (ICU_MAX_CHANNEL_ID_CONFIGURED < LddChannel)
  {
    /* Report Error to DET */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_GET_INPUT_LEVEL_SID, ICU_E_PARAM_CHANNEL);
  }
  #if (ICU_MULTI_CORE_SUPPORT == STD_ON)
  /* Check that the target core is mapping into this channel */
  else if ((Icu_GpChannelConfig[LddChannel].ucCoreIndex & LucCoreID) != LucCoreID)                                      /* PRQA S 0404, 3416 # JV-01, JV-01 */
  {
    /* Report to Development Errors */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_GET_INPUT_LEVEL_SID, ICU_E_INVALID_CORE);
  }
  #endif
  else
  #endif /* End of (ICU_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Initial value */
    LddInputLevel = ICU_LOW;
    /* Updating the channel config parameter to the current channel */
    LpChannel = &Icu_GpChannelConfig[LddChannel];
    /* Read the Timer Type for the given channel */
    LucHWIPType = LpChannel->ucIcuChannelType;
    /* Updating the channel config parameter to the current channel */
    if (NULL_PTR != Icu_GaaHwDepFunc[LucHWIPType]->pGetInputLevel)                                                      /* PRQA S 3416 # JV-01 */
    {
      LddInputLevel = Icu_GaaHwDepFunc[LucHWIPType]->pGetInputLevel(LddChannel);
    } /* else No action required */
  } /* End of ICU_INITIALIZED != Icu_GblDriverStatus */
  return (LddInputLevel);
} /* End of API Icu_GetInputlevel */

#define ICU_STOP_SEC_PUBLIC_CODE_GLOBAL
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of (ICU_GET_INPUT_LEVEL_API == STD_ON) */
/***********************************************************************************************************************
** Function Name         : Icu_GetVersionInfo
**
** Service ID            : 0x12
**
** Description           : This API returns the version information of ICU driver component.
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
** Reference ID          : ICU_DUD_ACT_019, ICU_DUD_ACT_019_ERR001
***********************************************************************************************************************/
#if (ICU_GET_VERSION_INFO_API == STD_ON)
#define ICU_START_SEC_PUBLIC_CODE_GLOBAL
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(void, ICU_PUBLIC_CODE) Icu_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, ICU_APPL_DATA) versioninfo)        /* PRQA S 1503, 3432 # JV-01, JV-01 */
{
  #if (ICU_DEV_ERROR_DETECT == STD_ON)
  /* Check if parameter passed is equal to Null poinFEter */
  if (NULL_PTR == versioninfo)
  {
    /* Report Error to DET */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_GET_VERSION_INFO_SID, ICU_E_PARAM_VINFO);
  }
  else
  #endif /* (ICU_DEV_ERROR_DETECT == STD_ON) */
  {
    versioninfo->vendorID = ICU_VENDOR_ID;
    versioninfo->moduleID = ICU_MODULE_ID;
    versioninfo->sw_major_version = ICU_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version = ICU_SW_MINOR_VERSION;
    versioninfo->sw_patch_version = ICU_SW_PATCH_VERSION;
  }
}

#define ICU_STOP_SEC_PUBLIC_CODE_GLOBAL
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* (ICU_GET_VERSION_INFO_API == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Icu_GetTAUInCountValue
**
** Service ID            : 0x19
**
** Description           : This service reads the TAU Counter value of the particular channel.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LddChannel
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : Icu_CounterValueType
**
** Preconditions         : The Icu Driver must be initialized, ICU_GET_TAU_COUNT_VALUE_API must be STD_ON
**
** Global Variables      : Icu_GpChannelConfig, Icu_GblDriverStatus, Icu_GaaHwDepFunc.
**
** Functions invoked     : Det_ReportError, Icu_HW_Taud_GetTAUInCountValue, Icu_HW_Tauj_GetTAUInCountValue
**
** Registers Used        : None
**
** Reference ID          : ICU_DUD_ACT_026, ICU_DUD_ACT_026_ERR001, ICU_DUD_ACT_026_ERR002, ICU_DUD_ACT_026_ERR003
** Reference ID          : ICU_DUD_ACT_026_ERR004
***********************************************************************************************************************/
#if (ICU_GET_TAU_COUNT_VALUE_API == STD_ON)
#define ICU_START_SEC_PUBLIC_CODE_GLOBAL
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(Icu_CounterValueType, ICU_PUBLIC_CODE) Icu_GetTAUInCountValue(Icu_ChannelType LddChannel)                          /* PRQA S 1503 # JV-01 */
{
  /* Defining return value */
  Icu_CounterValueType LddTAUInCounterValue;
  /* Defining a pointer to the channel config parameters */
  P2CONST(Icu_ChannelConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannel;
  /* Declare a Local variable to Timer Type */
  volatile uint8 LucTimerType;

  #if (ICU_DEV_ERROR_DETECT == STD_ON)
  #if (ICU_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = ICU_ONE << (uint8)GetCoreID();
  #endif
  /* Initialize the return value */
  LddTAUInCounterValue = ICU_TAU_CNT_INIT_VAL;
  /* Check if the Icu Module is not initialized */
  if (ICU_INITIALIZED != Icu_GblDriverStatus)                                                                           /* PRQA S 3416 # JV-01 */
  {
    /* Report Error to Det */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_GET_COUNT_VALUE_SID, ICU_E_UNINIT);
  }
  /* Check if the channel is valid */
  else if (ICU_MAX_CHANNEL_ID_CONFIGURED < LddChannel)
  {
    /* Report Error to Det */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_GET_COUNT_VALUE_SID, ICU_E_PARAM_CHANNEL);
  }
  else if ((ICU_HW_TAUD != Icu_GpChannelConfig[LddChannel].ucIcuChannelType) &&                                         /* PRQA S 3416 # JV-01 */
                                                (ICU_HW_TAUJ != Icu_GpChannelConfig[LddChannel].ucIcuChannelType))      /* PRQA S 3415, 3416 # JV-01, JV-01 */
  {
    /* Report Error to Det */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_GET_COUNT_VALUE_SID, ICU_E_PARAM_CHANNEL);
  }
  #if (ICU_MULTI_CORE_SUPPORT == STD_ON)
  /* Check that the target core is mapping into this channel */
  else if ((Icu_GpChannelConfig[LddChannel].ucCoreIndex & LucCoreID) != LucCoreID)                                      /* PRQA S 0404, 3416 # JV-01, JV-01 */
  {
    /* Report to Development Errors */
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_GET_COUNT_VALUE_SID, ICU_E_INVALID_CORE);
  }
  #endif
  else
  #endif
  {
    /* Initialize the return value */
    LddTAUInCounterValue = ICU_TAU_CNT_INIT_VAL;
    /* Updating the channel config parameter to the current channel */
    LpChannel = &Icu_GpChannelConfig[LddChannel];
    /* Read the Timer Type for the given channel */
    LucTimerType = LpChannel->ucIcuChannelType;

    if (NULL_PTR != Icu_GaaHwDepFunc[LucTimerType]->pGetTAUInCountValue)                                                /* PRQA S 3416 # JV-01 */
    {
      LddTAUInCounterValue = Icu_GaaHwDepFunc[LucTimerType]->pGetTAUInCountValue(LddChannel);
    } /* else No action required */
  } /* End of ICU_INITIALIZED != Icu_GblDriverStatus */
  return (LddTAUInCounterValue);
} /* End of API Icu_GetTAUCountValue */

#define ICU_STOP_SEC_PUBLIC_CODE_GLOBAL
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif
/***********************************************************************************************************************
** Function Name       : Icu_SetDriverStatus
**
** Service ID          : Not Applicable
**
** Description         : This function updates Icu_SetDriverStatus. The puporse of this function is
**                       to prevent the order of instructions being changed by the compiler.
**
** Sync/Async          : Synchronous
**
** Re-entrancy         : Non-Reentrant
**
** Input Parameters    : LblStatus: New status value
**
** InOut Parameters    : None
**
** Output Parameters   : None
**
** Return parameter    : None
**
** Preconditions       : None
**
** Global Variable     : Icu_GblDriverStatus
**
** Function invoked    : None
**
** Registers Used      : None
**
** Reference ID        : ICU_DUD_ACT_087, ICU_DUD_ACT_087_GBL001
***********************************************************************************************************************/
#define ICU_START_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

STATIC FUNC(void, ICU_PRIVATE_CODE) Icu_SetDriverStatus(const boolean LblStatus)
{
  Icu_GblDriverStatus = LblStatus;
}

#define ICU_STOP_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
