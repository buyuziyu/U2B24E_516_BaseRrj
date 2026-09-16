/*====================================================================================================================*/
/* Project      = RH850/X2x AR4 MCAL Development                                                                      */
/* Module       = Pwm.c                                                                                               */
/*                                                                                                                    */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains API function implementations of PWM Driver                                                      */
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
/*                                              Devices:        X2x                                                   */
/*====================================================================================================================*/
/***********************************************************************************************************************
**                                              Revision Control History                                              **
***********************************************************************************************************************/
/*                                                                                                                    **
 ** 2.5.1: 30/06/2025 : Update macro name for elements of Pwm_ClockSourceType                                         **
 ** 2.5.0: 30/06/2025 : Update SW-VERSION for U2Ax Ver22.01.00(D) Final Release                                       **
 ** 2.4.0: 31/05/2025 : Update SW-VERSION for U2Cx Ver21.01.01 Final Release                                          **
 ** 2.3.2: 29/04/2025 : Update SW-VERSION for U2Ax Ver22.00.04 Beta Release                                           **
 ** 2.3.1: 31/03/2025 : Update SW-VERSION for U2BxE Ver22.00.02 Beta Release                                          **
 **                     To support QAC 11.6.0: Add message 3205                                                       **
 **                     Function Pwm_SynchronousInit: Remove QAC message 2877                                         **
 ** 2.3.0: 28/02/2025 : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release                       **
 ** 2.2.0: 31/12/2024 : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release                                 **
 ** 2.1.2: 31/10/2024 : As part of GTM support, following changes are made                                            **
 **                     1. Update function Pwm_SelectChannelClk for GTM                                               **
 ** 2.1.1: 30/08/2024 : As part of U2Cx Diag support, following changes are made                                      **
 **                     1. Update ChannelNumber to LddChannelNumber and add QAC massage 3432 in fuction               **
 **                        Pwm_SetTriggerDelay                                                                        **
 **                     2. Move LulAdConvResult get out macro PWM_DEV_ERROR_DETECT in fuction Pwm_DiagReadAdConvResult**
 **                     3. Add QAC message 2877 for line 1601, 1708, 1809                                             **
 **                     As part of ARDAACL-40198 support, following changes are made                                  **
 **                     1. Add refer Id PWM_DUD_ACT_001_GBL008 and Pwm_GucKernelCoreId into header comment of Pwm_Init**
 **                     2. Change macro PWM_KERNEL_COREID to global variable Pwm_GucKernelCoreId                      **
 **                     3. Update Pwm_Init to get the kernel core Id from input Pwm_Config                            **
 **                     4. Remove redundant QAC message                                                               **
 **                     5. Update version in header comment                                                           **
 ** 2.0.1: 24/10/2023 : Cast PWM_TRUE to uint8, add QAC message 4304                                                  **
 **                      Add new QAC message 0404                                                                     **
 **                      Add QAC comment 3416, 3432                                                                   **
 **                      Remove QAC message 2814, 2844                                                                **
 ** 2.0.1: 18/10/2023 : Add QAC message 1881                                                                          **
 **        14/10/2023 : Move error checking for PWM_E_UNINIT to be performed first in API Pwm_DeInit,                 **
 **                     Pwm_SynchronousInit, Pwm_SynchronousStart, Pwm_SynchronousStop                                **
 ** 2.0.0: 28/08/2023 : - Remove condition check PWM_DEV_ERROR_DETECT == STD_ON for Pwm_SetStatus                     **
 **        05/07/2023 : - Update from "Pwm_Mapping.h to "Pwm_MemMap.h".                                               **
 **                     - Update Exclusive_Area of PWM_ENTER_CRITICAL_SECTION/PWM_EXIT_CRITICAL_SECTION               **
 **                     - Change from PWM_START/END_SEC_PUBLIC_CODE to PWM_START/END_SEC_PUBLIC_CODE_LOCAL/GLOBAL     **
 **                     - Add #include "Pwm_Kernel.h" and "Os.h" to support Multicore                                 **
 **                     - Remove pre-compile condition check for PWM_ENTER_CRITICAL_SECTION/PWM_EXIT_CRITICAL_SECTION **
 **                     - Add DET error check for PWM_E_INVALID_CORE in Pwm_CheckDetErrors, Pwm_Init, Pwm_DeInit,     **
 **                     Pwm_SynchronousInit, Pwm_SynchronousStart, Pwm_SynchronousStop.                               **
 **                     - Add Pwm_LockProcess/Pwm_UnLockProcess process and DET error check for PWM_E_REQUEST_FALSE   **
 **                     in Pwm_SetDutyCycle, Pwm_SetPeriodAndDuty, Pwm_SetOutputToIdle, Pwm_SetChannelOutput,         **
 **                     Pwm_SelectChannelClk, Pwm_SetTriggerDelay.                                                    **
 **                     - Add the "Clear the buffer request" process in Pwm_Init, Pwm_DeInit                          **
 **                     - Update QAC message                                                                          **
 **        20/04/2023 : Update header description for all APIs                                                        **
 ** 1.4.3: 23/05/2022 : Remove redundant QAC header of message 2916, 1281, 0488                                       **
 **        18/04/2022 : Changed MAX_DUTY_CYCLE to PWM_MAX_DUTY_CYCLE_VALUE and                                        **
 **                             MIN_DUTY_CYCLE to PWM_MIN_DUTY_CYCLE_VALUE                                            **
 ** 1.4.0: 07/10/2021 : Updated macro cover for Pwm_CheckDetErrors.                                                   **
 ** 1.3.2: 06/09/2021 : Added Critical Section into Pwm_SynchronousStart, Pwm_SynchronousStop                         **
 **        04/09/2021 : Update Reentrancy information of API Pwm_GetVersionInfo from "Non-Reentrant" to "Reentrant".  **
 **                     Update Reentrancy information of APIs Pwm_SynchronousInit, Pwm_SynchronousStart,              **
 **                     Pwm_SynchronousStop from "Reentrant" to "Non-Reentrant".                                      **
 **      : 23/08/2021 : To support PWM-Diag feature.                                                                  **
 **      : 04/08/2021 : Device specific implementation move to device specific file.                                  **
 **                     Error checking is moved from device specific part at Pwm_SetPeriodAndDuty API.                **
 **                     Format source code unified within module.                                                     **
 ** 1.3.1: 02/07/2021 : Add QAC message 9.5.0                                                                         **
 **                     Format source code to 120 characters                                                          **
 **                     Improve Violation tag (remove START/END)                                                      **
 **        22/05/2021 : Fixed QAC CWM, removed Msg 1476                                                               **
 **        19/05/2021 : removed redundant loop and changed the way to invoke the sub-functions in these APIs:         **
 **                     Pwm_SetDutyCycle, Pwm_SetPeriodAndDuty, Pwm_SetOutputToIdle, Pwm_GetOutputState,              **
 **                     Pwm_DisableNotification, Pwm_EnableNotification, Pwm_SelectChannelClk, Pwm_SetChannelOutput   **
 **        15/05/2021 : Fixed Coding Rule and tailor space                                                            **
 **        12/05/2021 : Changed PWM_HW_ATU to PWM_ATU_UNIT_INDEX, PWM_HW_TAUD to PWM_TAUD_UNIT_INDEX, and PWM_HW_TAUD **
 **                     to PWM_TAUJ_UNIT_INDEX                                                                        **
 ** 1.2.0: 28/07/2020 : Release                                                                                       **
 ** 1.1.0: 19/06/2020 : Release                                                                                       **
 ** 1.0.2: 27/05/2020 : Moved "LenRetOutputState = PWM_LOW;" to out of "PWM_DEV_ERROR_DETECT == STD_ON"               **
 ** 1.0.1: 25/05/2020 : Apply "Pwm_GaaChannelIdleStatus" and "PWM_E_ALREADY_INITIALIZED" macro to E2x                 **
 ** 1.0.0: 30/03/2020 : Initial Version.                                                                              **
 **                                                                                                                   */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for module version information and other types declarations */
#include "Pwm.h"
#include "Pwm_Ram.h"
/* Included for the declaration of Det_ReportError(), Det_ReportRuntimeError()*/
#include "Det.h"
#if ((PWM_CRITICAL_SECTION_PROTECTION == STD_ON) || (PWM_LOW_POWER_STATE_SUPPORT == STD_ON))
/* Included for the declaration of the critical section protection functions */
#include "SchM_Pwm.h"
#endif
/* Included for the declaration for multicore support */
#if (PWM_MULTI_CORE_SUPPORT == STD_ON)
#include "Pwm_Kernel.h"
#include "Os.h"
#endif

#define PWM_START_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"

#if ((PWM_DEV_ERROR_DETECT == STD_ON) && ((PWM_GET_OUTPUT_STATE_API == STD_ON) || (PWM_SET_DUTY_CYCLE_API == STD_ON)|| \
(PWM_SET_OUTPUT_TO_IDLE_API == STD_ON) || (PWM_SET_PERIOD_AND_DUTY_API == STD_ON) || \
(PWM_SELECT_CHANNEL_CLK_API == STD_ON) || (PWM_SET_CHANNEL_OUTPUT_API == STD_ON) || \
(PWM_SET_TRIGGER_DELAY_API == STD_ON) || (PWM_READ_CONV_RESLUT_API == STD_ON) || \
(PWM_ENABLE_DISABLE_AD_TRG_API == STD_ON) || (PWM_NOTIFICATION_SUPPORTED == STD_ON)))
STATIC FUNC(Std_ReturnType, PWM_PRIVATE_CODE) Pwm_CheckDetErrors(Pwm_ChannelType LddChannelNumber, uint8 LucApiSid);
#endif
STATIC FUNC(void, PWM_PRIVATE_CODE) Pwm_SetStatus(boolean LblStatus);

#define PWM_STOP_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define PWM_C_AR_RELEASE_MAJOR_VERSION    PWM_AR_RELEASE_MAJOR_VERSION_VALUE
#define PWM_C_AR_RELEASE_MINOR_VERSION    PWM_AR_RELEASE_MINOR_VERSION_VALUE
#define PWM_C_AR_RELEASE_REVISION_VERSION PWM_AR_RELEASE_REVISION_VERSION_VALUE

/* Module software version information */
#define PWM_C_SW_MAJOR_VERSION            PWM_SW_MAJOR_VERSION_VALUE
#define PWM_C_SW_MINOR_VERSION            PWM_SW_MINOR_VERSION_VALUE
#define PWM_C_SW_PATCH_VERSION            PWM_SW_PATCH_VERSION_VALUE
/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (PWM_AR_RELEASE_MAJOR_VERSION != PWM_C_AR_RELEASE_MAJOR_VERSION)
  #error "Pwm.c : Mismatch in Release Major Version"
#endif
#if (PWM_AR_RELEASE_MINOR_VERSION != PWM_C_AR_RELEASE_MINOR_VERSION)
  #error "Pwm.c : Mismatch in Release Minor Version"
#endif
#if (PWM_AR_RELEASE_REVISION_VERSION != PWM_C_AR_RELEASE_REVISION_VERSION)
  #error "Pwm.c : Mismatch in Release Revision Version"
#endif
#if (PWM_SW_MAJOR_VERSION != PWM_C_SW_MAJOR_VERSION)
  #error "Pwm.c : Mismatch in Software Major Version"
#endif
#if (PWM_SW_MINOR_VERSION != PWM_C_SW_MINOR_VERSION)
  #error "Pwm.c : Mismatch in Software Minor Version"
#endif
#if (PWM_SW_PATCH_VERSION != PWM_C_SW_PATCH_VERSION)
  #error "Pwm.c : Mismatch in Software Patch Version"
#endif
/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:0316)    : Cast from a pointer to void to a pointer to object type.                                     */
/* Rule                : MISRA C:2012 Rule-11.5, CWE Rule CWE-188, CWE-398, CWE-569                                   */
/* JV-01 Justification : A cast should not be performed between a pointer to object type and a different pointer to   */
/*                       object type.                                                                                 */
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
/* Message (6:2877)    : This loop will never be executed more than once.                                             */
/* Rule                : MISRA C:2012 Dir-4.1, CERTCCM MSC07, CWE Rule CWE-670                                        */
/* JV-01 Justification : This loop will only be executed at least once, depends on user configuration.                */
/*       Verification  : This is Hardware Specification, X2x only provides 1 Unit. So it is not having any impact.    */
/**********************************************************************************************************************/
/* Message (3:3415)    : Right hand operand of '&&' or '||' is an expression with persistent side effects.            */
/* Rule                : MISRA C:2012 Rule-13.5, CERTCCM EXP02, CWE Rule CWE-398, CWE-768, CWE-569                    */
/* JV-01 Justification : Although it is a volatile object, it does not have direct access to the HW register, and     */
/*                       there is no side effect.                                                                     */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:4304)    : An expression of 'essentially Boolean' type (%1s) is being cast to unsigned type '%2s'.      */
/* Rule                : MISRA C:2012 Rule-10.5, CWE Rule CWE-704                                                     */
/* JV-01 Justification : This is accepted. This casting from boolean to unsigned type for values 0 and 1 does not     */
/*                       make data conflict.                                                                          */
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
/* Message (7:0404)    : More than one read access to volatile objects between sequence points.                       */
/* Rule                : MISRA C:2012 Rule-1.3, Rule-13.2, CERTCCM EXP30, EXP10, CWE Rule CWE-682, CWE-758, CWE-737   */
/* JV-01 Justification : This is to get an element in the array of struct, volatile of the counter variable of 'for'  */
/*                       loop is used to ensure no optimization. It is accepted                                       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:1881)    : The operands of this equality operator are expressions of different 'essential type'         */
/*                       categories (enum and unsigned).                                                              */
/* Rule                : CERTCCM INT02, MISRA C:2012 Rule-10.4                                                        */
/* JV-01 Justification : All are unsigned long type variables and do not correspond to the pointed out contents.      */
/*                       No problem.                                                                                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3205)    : The identifier '%s' is not used and could be removed.                                        */
/* Rule                : CERTCCM MSC07, MSC13, MISRA C:2012 Rule-2.3                                                  */
/* JV-01 Justification : This identifier is used by other file.                                                       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/

/***********************************************************************************************************************
** Function Name        : Pwm_Init
**
** Service ID           : 0x00
**
** Description          : This API performs the initialization of PWM Driver component.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Non-Reentrant
**
** Input Parameters     : ConfigPtr
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return parameter     : None
**
** Preconditions        : None
**
** Global Variables     : Pwm_GblDriverStatus, Pwm_GpChannelConfig, Pwm_GaaHwFunc, Pwm_GaaHWIP_Used,
**                        Pwm_GaaSetDutyCycleBuffer, Pwm_GaaSetPeriodAndDutyBuffer, Pwm_GaaSetOutputToIdleBuffer,
**                        Pwm_GaaSelectChannelClkBuffer, Pwm_GaaSetChannelOutputBuffer, Pwm_GaaSetTriggerDelayBuffer,
**                        Pwm_GucKernelCoreId
**
** Functions invoked    : Det_ReportError, Pwm_<HW-IP>_InitUnit, Pwm_<HW-IP>_InitChannel,
**                        Pwm_<HW-IP>_StartOutput, Pwm_SetStatus
**
** Registers Used       : None
**
** Reference ID         : PWM_DUD_ACT_001, PWM_DUD_ACT_001_ERR001, PWM_DUD_ACT_001_ERR002, PWM_DUD_ACT_001_ERR003,
** Reference ID         : PWM_DUD_ACT_001_ERR004, PWM_DUD_ACT_001_GBL006, PWM_DUD_ACT_001_GBL007, PWM_DUD_ACT_001_GBL008
***********************************************************************************************************************/
#define PWM_START_SEC_PUBLIC_CODE_LOCAL
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, PWM_PUBLIC_CODE) Pwm_Init(P2CONST(Pwm_ConfigType, PWM_VAR_NO_INIT, PWM_APPL_CONST) ConfigPtr)                /* PRQA S 1503 # JV-01 */
{
  /* Index of HW IP Type */
  VAR(volatile uint8, AUTOMATIC) LucHWIPType;
  VAR(uint32, AUTOMATIC)  LulCount;
  #if (PWM_DEV_ERROR_DETECT == STD_ON)
  /* Declare the variable to store the DET return value */
  VAR(uint8, AUTOMATIC) LucDetErrFlag;

  #if (PWM_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare the local variable to store the current used core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = (uint8)GetCoreID();
  #endif /* PWM_MULTI_CORE_SUPPORT == STD_ON */

  /* Initialize error flag */
  LucDetErrFlag = E_OK;

  #if (PWM_ALREADY_INIT_DET_CHECK == STD_ON)
  /* Check if the PWM Driver is already initialized */
  if (PWM_INITIALIZED == Pwm_GblDriverStatus)                                                                           /* PRQA S 3416 # JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(PWM_MODULE_ID, PWM_INSTANCE_ID, PWM_INIT_SID, PWM_E_ALREADY_INITIALIZED);
    LucDetErrFlag = E_NOT_OK;
  } /* else No action required */
  #endif

  /* Check if ConfigPtr is NULL_PTR */
  if (NULL_PTR == ConfigPtr)
  {
    /* Report Error to DET */
    (void)Det_ReportError(PWM_MODULE_ID, PWM_INSTANCE_ID, PWM_INIT_SID, PWM_E_INIT_FAILED);
    LucDetErrFlag = E_NOT_OK;
  }
  else
  {
    #if (PWM_MULTI_CORE_SUPPORT == STD_ON)
    /* Holds the kernal core ID in multicore */
    Pwm_GucKernelCoreId = ConfigPtr->ucKernelCoreId;
    /* Check if the control API is executed on the Master core */
    if (Pwm_GucKernelCoreId != LucCoreID)                                                                               /* PRQA S 3416 # JV-01 */
    {
      /* Report Error to DET */
      (void)Det_ReportError(PWM_MODULE_ID, PWM_INSTANCE_ID, PWM_INIT_SID, PWM_E_INVALID_CORE);
      LucDetErrFlag = E_NOT_OK;
    } /* else No action required */
    #endif /* PWM_MULTI_CORE_SUPPORT == STD_ON */
  }

  /* If there is no valid database present */
  if ((E_OK == LucDetErrFlag) && ((uint32)PWM_DBTOC_VALUE != ConfigPtr->ulStartOfDbToc))
  {
    /* Report Error to DET */
    (void)Det_ReportError(PWM_MODULE_ID, PWM_INSTANCE_ID, PWM_INIT_SID, PWM_E_INVALID_DATABASE);
    LucDetErrFlag = E_NOT_OK;
  } /* else No action required */

  if (E_OK == LucDetErrFlag)
  #endif /* End of PWM_DEV_ERROR_DETECT == STD_ON */
  {
    /* Save the start of channel Configuration in the global pointer */
    Pwm_GpChannelConfig = (P2CONST(Pwm_ChannelConfigType, PWM_VAR_NO_INIT, PWM_CONFIG_DATA))                            /* PRQA S 0316 # JV-01 */
    (ConfigPtr->pChannelConfig);
    for (LulCount = (uint32)PWM_ZERO; LulCount < (uint32)PWM_TOTAL_HW_IP_CONFIG; LulCount++)                            /* PRQA S 2877 # JV-01 */
    {
      LucHWIPType = Pwm_GaaHWIP_Used[LulCount].ucIndex;
      if (NULL_PTR != Pwm_GaaHwFunc[LucHWIPType]->pHWInitUnit)                                                          /* PRQA S 3416 # JV-01 */
      {
        /* Invoke low level driver for initializing the hardware */
        Pwm_GaaHwFunc[LucHWIPType]->pHWInitUnit(ConfigPtr);
      } /* else  No action required */
    }

    /* Initialize all PWM channels */
    for (LulCount = (uint32)PWM_ZERO; LulCount < (uint32)PWM_TOTAL_HW_IP_CONFIG; LulCount++)                            /* PRQA S 2877 # JV-01 */
    {
      LucHWIPType = Pwm_GaaHWIP_Used[LulCount].ucIndex;

      if (NULL_PTR != Pwm_GaaHwFunc[LucHWIPType]->pHWInitChannel)                                                       /* PRQA S 3416 # JV-01 */
      {
        /* Invoke low level driver for initializing the hardware */
        Pwm_GaaHwFunc[LucHWIPType]->pHWInitChannel();
      } /* else  No action required */
    }

    for (LulCount = (uint32)PWM_ZERO; LulCount < (uint32)PWM_TOTAL_HW_IP_CONFIG; LulCount++)                            /* PRQA S 2877 # JV-01 */
    {
      LucHWIPType = Pwm_GaaHWIP_Used[LulCount].ucIndex;

      if (NULL_PTR != Pwm_GaaHwFunc[LucHWIPType]->pHWStartOutput)                                                       /* PRQA S 3416 # JV-01 */
      {
        /* Invoke low level driver for initializing the hardware */
        Pwm_GaaHwFunc[LucHWIPType]->pHWStartOutput();
      } /* else  No action required */
    }

    #if (PWM_MULTI_CORE_SUPPORT == STD_ON)
    /* Clear the buffer request */
    for (LulCount = (uint32)PWM_ZERO; LulCount < (uint32)PWM_TOTAL_CHANNELS_CONFIG; LulCount++)
    {
      #if (PWM_SET_DUTY_CYCLE_API == STD_ON)
      Pwm_GaaSetDutyCycleBuffer[LulCount].lusDutyCycle = (uint16)PWM_ZERO;
      Pwm_GaaSetDutyCycleBuffer[LulCount].blSetReq = PWM_FALSE;
      Pwm_GaaSetDutyCycleBuffer[LulCount].blBufferLock = PWM_FALSE;
      #endif

      #if (PWM_SET_PERIOD_AND_DUTY_API == STD_ON)
      Pwm_GaaSetPeriodAndDutyBuffer[LulCount].lusDutyCycle = (uint16)PWM_ZERO;
      Pwm_GaaSetPeriodAndDutyBuffer[LulCount].lddPeriod = (uint32)PWM_ZERO;
      Pwm_GaaSetPeriodAndDutyBuffer[LulCount].blSetReq = PWM_FALSE;
      Pwm_GaaSetPeriodAndDutyBuffer[LulCount].blBufferLock = PWM_FALSE;
      #endif

      #if (PWM_SET_OUTPUT_TO_IDLE_API == STD_ON)
      Pwm_GaaSetOutputToIdleBuffer[LulCount].blSetReq = PWM_FALSE;
      Pwm_GaaSetOutputToIdleBuffer[LulCount].blBufferLock = PWM_FALSE;
      #endif

      #if (PWM_SELECT_CHANNEL_CLK_API == STD_ON)
      Pwm_GaaSelectChannelClkBuffer[LulCount].lddClockSource = PWM_CLKBUSLINE0;
      Pwm_GaaSelectChannelClkBuffer[LulCount].blSetReq = PWM_FALSE;
      Pwm_GaaSelectChannelClkBuffer[LulCount].blBufferLock = PWM_FALSE;
      #endif

      #if (PWM_SET_CHANNEL_OUTPUT_API == STD_ON)
      Pwm_GaaSetChannelOutputBuffer[LulCount].lddState = PWM_HIGH;
      Pwm_GaaSetChannelOutputBuffer[LulCount].blSetReq = PWM_FALSE;
      Pwm_GaaSetChannelOutputBuffer[LulCount].blBufferLock = PWM_FALSE;
      #endif

      #if (PWM_SET_TRIGGER_DELAY_API == STD_ON)
      Pwm_GaaSetTriggerDelayBuffer[LulCount].lusTriggerDelay = (uint16)PWM_ZERO;
      Pwm_GaaSetTriggerDelayBuffer[LulCount].blSetReq = PWM_FALSE;
      Pwm_GaaSetTriggerDelayBuffer[LulCount].blBufferLock = PWM_FALSE;
      #endif
    }
    #endif

    /* Set PWM Driver status to initialized */
    Pwm_SetStatus(PWM_INITIALIZED);
  } /* else No action required */
  /* End of if (E_OK == LucDetErrFlag) */
}

#define PWM_STOP_SEC_PUBLIC_CODE_LOCAL
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name        : Pwm_DeInit
**
** Service ID           : 0x01
**
** Description          : This service performs de-initialization of the PWM Driver component.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Non-Reentrant
**
** Input Parameters     : None
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return parameter     : None
**
** Preconditions        : 1.PWM Driver should be initialized.
**                        2.This API is available only if the pre-compile option PWM_DE_INIT_API is STD_ON.
**
** Global Variables     : Pwm_GblDriverStatus, Pwm_GblSyncInitStatus, Pwm_GblSyncOperationStatus, Pwm_GaaHwFunc
**                        Pwm_GaaHWIP_Used, Pwm_GaaSetDutyCycleBuffer, Pwm_GaaSetPeriodAndDutyBuffer,
**                        Pwm_GaaSetOutputToIdleBuffer, Pwm_GaaSelectChannelClkBuffer, Pwm_GaaSetChannelOutputBuffer,
**                        Pwm_GaaSetTriggerDelayBuffer
**
** Functions invoked    : Det_ReportError, Pwm_<HW-IP>_DeInitUnit, Pwm_<HW-IP>_DeInitChannel, Pwm_SetStatus
**
** Registers Used       : None
**
** Reference ID         : PWM_DUD_ACT_002, PWM_DUD_ACT_002_ERR001, PWM_DUD_ACT_002_GBL001, PWM_DUD_ACT_002_GBL002,
** Reference ID         : PWM_DUD_ACT_002_GBL003, PWM_DUD_ACT_002_ERR002
***********************************************************************************************************************/
#if (PWM_DE_INIT_API == STD_ON)
#define PWM_START_SEC_PUBLIC_CODE_LOCAL
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, PWM_PUBLIC_CODE) Pwm_DeInit(void)                                                                            /* PRQA S 1503 # JV-01 */
{
  /* Index of HW IP Type */
  VAR(volatile uint8, AUTOMATIC) LucHWIPType;
  VAR(uint32, AUTOMATIC) LulCount;

  #if (PWM_DEV_ERROR_DETECT == STD_ON)
  /* Check if PWM Driver is initialized */
  if (PWM_INITIALIZED != Pwm_GblDriverStatus)                                                                           /* PRQA S 3416 # JV-01 */
  {
    /* Report to DET module */
    (void)Det_ReportError(PWM_MODULE_ID, PWM_INSTANCE_ID, PWM_DEINIT_SID, PWM_E_UNINIT);
  }
  else
  #endif /* End of PWM_DEV_ERROR_DETECT == STD_ON */
  {
    #if (PWM_DEV_ERROR_DETECT == STD_ON)
    #if (PWM_MULTI_CORE_SUPPORT == STD_ON)
    /* Declare the local variable to store the current used core ID */
    VAR(volatile uint8, AUTOMATIC) LucCoreID;
    /* Get the current core ID by OS service */
    LucCoreID = (uint8)GetCoreID();
    
    /* Check if the control API is executed on the Master core */
    if (Pwm_GucKernelCoreId != LucCoreID)                                                                               /* PRQA S 3416 # JV-01 */
    {
      /* Report Error to DET */
      (void)Det_ReportError(PWM_MODULE_ID, PWM_INSTANCE_ID, PWM_DEINIT_SID, PWM_E_INVALID_CORE);
    }
    else
    #endif /* End of PWM_MULTI_CORE_SUPPORT == STD_ON */ 
    #endif /* End of PWM_DEV_ERROR_DETECT == STD_ON */ 
    {
      /* Set PWM Driver status to uninitialized */
      Pwm_SetStatus(PWM_UNINITIALIZED);
    
      #if ((PWM_DEV_ERROR_DETECT == STD_ON) && (PWM_SYNC_START_SUPPORT == STD_ON))
      /* Set PWM Synchronous Init status to uninitialized */
      Pwm_GblSyncInitStatus = PWM_UNINITIALIZED;
    
      /* Set PWM Synchronous Operation status to stopped */
      Pwm_GblSyncOperationStatus = PWM_SYNC_STOPPED;
      #endif /* End of PWM_SYNC_START_SUPPORT == STD_ON */
    
      /* DeInitialize all PWM channels */
      for (LulCount = (uint32)PWM_ZERO; LulCount < (uint32)PWM_TOTAL_HW_IP_CONFIG; LulCount++)                          /* PRQA S 2877 # JV-01 */
      {
        LucHWIPType = Pwm_GaaHWIP_Used[LulCount].ucIndex;
        if (NULL_PTR != Pwm_GaaHwFunc[LucHWIPType]->pHWDeInitUnit)                                                      /* PRQA S 3416 # JV-01 */
        {
          /* Invoke low level driver for initializing the hardware */
          Pwm_GaaHwFunc[LucHWIPType]->pHWDeInitUnit();
        } /* else No action required */
    
        if (NULL_PTR != Pwm_GaaHwFunc[LucHWIPType]->pHWDeInitChannel)                                                   /* PRQA S 3416 # JV-01 */
        {
          /* Invoke low level driver for initializing the hardware */
          Pwm_GaaHwFunc[LucHWIPType]->pHWDeInitChannel();
        } /* else No action required */
      }
    
      #if (PWM_MULTI_CORE_SUPPORT == STD_ON)
      /* Clear the buffer request */
      for (LulCount = (uint32)PWM_ZERO; LulCount < (uint32)PWM_TOTAL_CHANNELS_CONFIG; LulCount++)
      {
        #if (PWM_SET_DUTY_CYCLE_API == STD_ON)
        Pwm_GaaSetDutyCycleBuffer[LulCount].lusDutyCycle = (uint16)PWM_ZERO;
        Pwm_GaaSetDutyCycleBuffer[LulCount].blSetReq = PWM_FALSE;
        Pwm_GaaSetDutyCycleBuffer[LulCount].blBufferLock = PWM_FALSE;
        #endif
    
        #if (PWM_SET_PERIOD_AND_DUTY_API == STD_ON)
        Pwm_GaaSetPeriodAndDutyBuffer[LulCount].lusDutyCycle = (uint16)PWM_ZERO;
        Pwm_GaaSetPeriodAndDutyBuffer[LulCount].lddPeriod = (uint32)PWM_ZERO;
        Pwm_GaaSetPeriodAndDutyBuffer[LulCount].blSetReq = PWM_FALSE;
        Pwm_GaaSetPeriodAndDutyBuffer[LulCount].blBufferLock = PWM_FALSE;
        #endif
    
        #if (PWM_SET_OUTPUT_TO_IDLE_API == STD_ON)
        Pwm_GaaSetOutputToIdleBuffer[LulCount].blSetReq = PWM_FALSE;
        Pwm_GaaSetOutputToIdleBuffer[LulCount].blBufferLock = PWM_FALSE;
        #endif
    
        #if (PWM_SELECT_CHANNEL_CLK_API == STD_ON)
        Pwm_GaaSelectChannelClkBuffer[LulCount].lddClockSource = PWM_CLKBUSLINE0;
        Pwm_GaaSelectChannelClkBuffer[LulCount].blSetReq = PWM_FALSE;
        Pwm_GaaSelectChannelClkBuffer[LulCount].blBufferLock = PWM_FALSE;
        #endif
    
        #if (PWM_SET_CHANNEL_OUTPUT_API == STD_ON)
        Pwm_GaaSetChannelOutputBuffer[LulCount].lddState = PWM_HIGH;
        Pwm_GaaSetChannelOutputBuffer[LulCount].blSetReq = PWM_FALSE;
        Pwm_GaaSetChannelOutputBuffer[LulCount].blBufferLock = PWM_FALSE;
        #endif
    
        #if (PWM_SET_TRIGGER_DELAY_API == STD_ON)
        Pwm_GaaSetTriggerDelayBuffer[LulCount].lusTriggerDelay = (uint16)PWM_ZERO;
        Pwm_GaaSetTriggerDelayBuffer[LulCount].blSetReq = PWM_FALSE;
        Pwm_GaaSetTriggerDelayBuffer[LulCount].blBufferLock = PWM_FALSE;
        #endif
      }
      #endif /* End of PWM_MULTI_CORE_SUPPORT == STD_ON */
    }
  } /* (PWM_INITIALIZED == Pwm_GblDriverStatus) */ 
}

#define PWM_STOP_SEC_PUBLIC_CODE_LOCAL
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of (PWM_DE_INIT_API == STD_ON) */

/***********************************************************************************************************************
** Function Name        : Pwm_SetDutyCycle
**
** Service ID           : 0x02
**
** Description          : This API is used to set the required Duty cycle for a PWM channel.
**
** Sync/Async           : Synchronous (Single core)/Asynchronous (Multi core)
**
** Re-entrancy          : Reentrant
**
** Input Parameters     : ChannelNumber and DutyCycle.
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return parameter     : None
**
** Preconditions        : 1.PWM Driver should be initialized.
**                        2.This API is available only if the pre-compile option PWM_SET_DUTY_CYCLE_API is STD_ON.
**
** Global Variables     : Pwm_GpChannelConfig, Pwm_GaaHwFunc, Pwm_GaaSetDutyCycleBuffer
**
** Functions invoked    : Det_ReportError, Pwm_<HW-IP>_SetDutyCycle, Pwm_CheckDetErrors
**
** Registers Used       : None
**
** Reference ID         : PWM_DUD_ACT_003, PWM_DUD_ACT_003_ERR001, PWM_DUD_ACT_003_ERR002, PWM_DUD_ACT_003_CRT001,
** Reference ID         : PWM_DUD_ACT_003_CRT002, PWM_DUD_ACT_003_CRT003
***********************************************************************************************************************/
#if (PWM_SET_DUTY_CYCLE_API == STD_ON)
#define PWM_START_SEC_PUBLIC_CODE_GLOBAL
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, PWM_PUBLIC_CODE) Pwm_SetDutyCycle(Pwm_ChannelType ChannelNumber, uint16 DutyCycle)                           /* PRQA S 1503 # JV-01 */
{
  #if (PWM_MULTI_CORE_SUPPORT == STD_OFF)
  /* Pointer pointing to the channel configuration */
  P2CONST(Pwm_ChannelConfigType, AUTOMATIC, PWM_CONFIG_CONST) LpChannelConfig;
  /* Index of HW IP Type */
  VAR(volatile uint8, AUTOMATIC) LucTimerUnitType;
  #endif

  #if (PWM_DEV_ERROR_DETECT == STD_ON)
  /* Declare the variable to store the DET return value */
  VAR(uint8, AUTOMATIC) LucDetErrFlag;

  /* Checking Det error */
  LucDetErrFlag = Pwm_CheckDetErrors(ChannelNumber, PWM_SET_DUTYCYCLE_SID);

  /* Check for valid Duty range */
  if ((E_OK == LucDetErrFlag) && (PWM_MAX_DUTY_CYCLE_VALUE < DutyCycle))
  {
    /* Report to DET module */
    (void)Det_ReportError(PWM_MODULE_ID, PWM_INSTANCE_ID, PWM_SET_DUTYCYCLE_SID, PWM_E_PARAM_VALUE);
    LucDetErrFlag = E_NOT_OK;
  } /* else  No action required */

  if (E_OK == LucDetErrFlag)
  #endif /* End of (PWM_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (PWM_MULTI_CORE_SUPPORT == STD_ON)
    /* Get the spinlock */
    /* Enter Protected area */
    PWM_ENTER_CRITICAL_SECTION(PWM_RAM_DATA_PROTECTION_GLOBAL);
    /* Set request to the master core if the shared buffer is ready - not locked by Satellite */
    if (Pwm_UnLockedStatus(Pwm_GaaSetDutyCycleBuffer[ChannelNumber].blBufferLock))                                      /* PRQA S 3432 # JV-01 */
    {
      /* Lock the shared buffer */
      Pwm_LockProcess(Pwm_GaaSetDutyCycleBuffer[ChannelNumber].blBufferLock);                                           /* PRQA S 3432 # JV-01 */
      /* Release the spinlock */
      PWM_EXIT_CRITICAL_SECTION(PWM_RAM_DATA_PROTECTION_GLOBAL);
      /* Update the request */
      Pwm_GaaSetDutyCycleBuffer[ChannelNumber].lusDutyCycle = DutyCycle;
      /* Request is issued */
      Pwm_GaaSetDutyCycleBuffer[ChannelNumber].blSetReq = PWM_TRUE;
      /* Release Lock */
      Pwm_UnLockProcess(Pwm_GaaSetDutyCycleBuffer[ChannelNumber].blBufferLock);                                         /* PRQA S 3432 # JV-01 */
    }
    else
    {
      /* Release the spinlock */
      PWM_EXIT_CRITICAL_SECTION(PWM_RAM_DATA_PROTECTION_GLOBAL);
      /* Report to Development Errors */
      (void)Det_ReportRuntimeError(PWM_MODULE_ID, PWM_INSTANCE_ID, PWM_SET_DUTYCYCLE_SID, PWM_E_REQUEST_FALSE);
    }
    #else
    /* Updating the channel config parameter to the current channel */
    LpChannelConfig = &Pwm_GpChannelConfig[ChannelNumber];
    /* Get the Timer Unit Type*/
    LucTimerUnitType = LpChannelConfig->ucTimerUnitType;

    if (NULL_PTR != Pwm_GaaHwFunc[LucTimerUnitType]->pHWSetDutyCycle)                                                   /* PRQA S 3416 # JV-01 */
    {
      /* Invoke low level driver for initializing the hardware */
      Pwm_GaaHwFunc[LucTimerUnitType]->pHWSetDutyCycle(ChannelNumber, DutyCycle);
    } /* else No action required */
    #endif /* End of (PWM_MULTI_CORE_SUPPORT == STD_ON) */
  } /* else No action required */
}
#define PWM_STOP_SEC_PUBLIC_CODE_GLOBAL
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif

/***********************************************************************************************************************
** Function Name        : Pwm_SetPeriodAndDuty
**
** Service ID           : 0x03
**
** Description          : This API is used to set the required Period and Duty cycle for a PWM channel.
**
** Sync/Async           : Synchronous (Single core)/Asynchronous (Multi core)
**
** Re-entrancy          : Reentrant
**
** Input Parameters     : ChannelNumber, Period and DutyCycle.
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return parameter     : None
**
** Preconditions        : 1.PWM Driver should be initialized.
**                        2.This API is available only if the pre-compile option PWM_SET_PERIOD_AND_DUTY_API is STD_ON.
**
** Global Variables     : Pwm_GpChannelConfig, Pwm_GaaHwFunc, Pwm_GaaSetPeriodAndDutyBuffer
**
** Functions invoked    : Det_ReportError, Pwm_<HW-IP>_SetPeriodAndDuty, Pwm_CheckDetErrors
**
** Registers Used       : None
**
** Reference ID         : PWM_DUD_ACT_004, PWM_DUD_ACT_004_ERR001, PWM_DUD_ACT_004_ERR002, PWM_DUD_ACT_004_ERR003,
** Reference ID         : PWM_DUD_ACT_004_CRT001, PWM_DUD_ACT_004_CRT002, PWM_DUD_ACT_004_CRT003
***********************************************************************************************************************/
#if (PWM_SET_PERIOD_AND_DUTY_API == STD_ON)
#define PWM_START_SEC_PUBLIC_CODE_GLOBAL
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, PWM_PUBLIC_CODE)
                           Pwm_SetPeriodAndDuty(Pwm_ChannelType ChannelNumber, Pwm_PeriodType Period, uint16 DutyCycle) /* PRQA S 1503 # JV-01 */
{
  #if (PWM_MULTI_CORE_SUPPORT == STD_OFF)
  /* Index of HW IP Type */
  VAR(volatile uint8, AUTOMATIC) LucTimerUnitType;
  #endif
  #if ((PWM_MULTI_CORE_SUPPORT == STD_OFF) || (PWM_DEV_ERROR_DETECT == STD_ON))
  /* Pointer pointing to the channel configuration */
  P2CONST(Pwm_ChannelConfigType, AUTOMATIC, PWM_CONFIG_CONST) LpChannelConfig;
  #endif
  
  #if (PWM_DEV_ERROR_DETECT == STD_ON)
  /* Declare the variable to store the DET return value */
  VAR(uint8, AUTOMATIC) LucDetErrFlag;

  /* Checking Det error */
  LucDetErrFlag = Pwm_CheckDetErrors(ChannelNumber, PWM_SET_PERIODANDDUTY_SID);
  #endif /* PWM_DEV_ERROR_DETECT == STD_ON */

  #if (PWM_DEV_ERROR_DETECT == STD_ON) || (PWM_MULTI_CORE_SUPPORT == STD_OFF)
  /* Updating the channel config parameter to the current channel */
  LpChannelConfig = &Pwm_GpChannelConfig[ChannelNumber];
  #endif
  
  #if (PWM_DEV_ERROR_DETECT == STD_ON)
  /* Check for valid Duty range */
  if (E_OK == LucDetErrFlag)
  {
    if (PWM_MAX_DUTY_CYCLE_VALUE < DutyCycle)
    {
      /* Report to DET module */
      (void)Det_ReportError(PWM_MODULE_ID, PWM_INSTANCE_ID, PWM_SET_PERIODANDDUTY_SID, PWM_E_PARAM_VALUE);
      LucDetErrFlag = E_NOT_OK;
    }

    /* Check if the Channel is of fixed period type */
    if ((PWM_FIXED_PERIOD == LpChannelConfig->enClassType)
      || (PWM_FIXED_PERIOD_SHIFTED == LpChannelConfig->enClassType))
    {
      /* Report to DET module */
      (void)Det_ReportError(PWM_MODULE_ID, PWM_INSTANCE_ID, PWM_SET_PERIODANDDUTY_SID, PWM_E_PERIOD_UNCHANGEABLE);
      LucDetErrFlag = E_NOT_OK;
    } /* else No action required */
  } /* else  No action required */

  if (E_OK == LucDetErrFlag)
  #endif /* PWM_DEV_ERROR_DETECT == STD_ON */
  {
    #if (PWM_MULTI_CORE_SUPPORT == STD_ON)
    /* Get the spinlock */
    /* Enter Protected area */
    PWM_ENTER_CRITICAL_SECTION(PWM_RAM_DATA_PROTECTION_GLOBAL);
    /* Set request to the master core if the shared buffer is ready - not locked by Satellite */
    if (Pwm_UnLockedStatus(Pwm_GaaSetPeriodAndDutyBuffer[ChannelNumber].blBufferLock))                                  /* PRQA S 3432 # JV-01 */
    {
      /* Lock the shared buffer */
      Pwm_LockProcess(Pwm_GaaSetPeriodAndDutyBuffer[ChannelNumber].blBufferLock);                                       /* PRQA S 3432 # JV-01 */
      /* Release the spinlock */
      PWM_EXIT_CRITICAL_SECTION(PWM_RAM_DATA_PROTECTION_GLOBAL);
      /* Update the request */
      Pwm_GaaSetPeriodAndDutyBuffer[ChannelNumber].lusDutyCycle = DutyCycle;
      Pwm_GaaSetPeriodAndDutyBuffer[ChannelNumber].lddPeriod = Period;
      /* Request is issued */
      Pwm_GaaSetPeriodAndDutyBuffer[ChannelNumber].blSetReq = PWM_TRUE;
      /* Release Lock */
      Pwm_UnLockProcess(Pwm_GaaSetPeriodAndDutyBuffer[ChannelNumber].blBufferLock);                                     /* PRQA S 3432 # JV-01 */
    }
    else
    {
      /* Release the spinlock */
      PWM_EXIT_CRITICAL_SECTION(PWM_RAM_DATA_PROTECTION_GLOBAL);
      /* Report to Development Errors */
      (void)Det_ReportRuntimeError(PWM_MODULE_ID, PWM_INSTANCE_ID, PWM_SET_PERIODANDDUTY_SID, PWM_E_REQUEST_FALSE);
    }
    #else
    /* Get the Timer Unit Type*/
    LucTimerUnitType = LpChannelConfig->ucTimerUnitType;
    /* Set Period and Duty cycle for the required channel */
    if (NULL_PTR != Pwm_GaaHwFunc[LucTimerUnitType]->pHWSetPeriodAndDuty)                                               /* PRQA S 3416 # JV-01 */
    {
      /* Invoke low level driver for initializing the hardware */
      Pwm_GaaHwFunc[LucTimerUnitType]->pHWSetPeriodAndDuty(ChannelNumber, Period, DutyCycle);
    } /* else  No action required */
    #endif /* End of (PWM_MULTI_CORE_SUPPORT == STD_ON) */
  } /* else  No action required */
}

#define PWM_STOP_SEC_PUBLIC_CODE_GLOBAL
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif

/***********************************************************************************************************************
** Function Name        : Pwm_SetOutputToIdle
**
** Service ID           : 0x04
**
** Description          : This API is used to set the output of PWM channel to its configured Idle state.
**                        This API also sets the output of PWM channel to idle state with pin level low.
**
** Sync/Async           : Synchronous (Single core)/Asynchronous (Multi core)
**
** Re-entrancy          : Reentrant
**
** Input Parameters     : ChannelNumber
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return parameter     : None
**
** Preconditions        : 1.PWM Driver should be initialized.
**                        2.This API is available only if the pre-compile option PWM_SET_OUTPUT_TO_IDLE_API is STD_ON.
**
** Global Variables     : Pwm_GpChannelConfig, Pwm_GaaHwFunc, Pwm_GaaSetOutputToIdleBuffer
**
** Functions invoked    : Pwm_<HW-IP>_SetOutputToIdle, Pwm_CheckDetErrors
**
** Registers Used       : None
**
** Reference ID         : PWM_DUD_ACT_005, PWM_DUD_ACT_005_ERR001, PWM_DUD_ACT_005_CRT001, PWM_DUD_ACT_005_CRT002,
** Reference ID         : PWM_DUD_ACT_005_CRT003
***********************************************************************************************************************/
#if (PWM_SET_OUTPUT_TO_IDLE_API == STD_ON)
#define PWM_START_SEC_PUBLIC_CODE_GLOBAL
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, PWM_PUBLIC_CODE) Pwm_SetOutputToIdle(Pwm_ChannelType ChannelNumber)                                          /* PRQA S 1503 # JV-01 */
{
  #if (PWM_MULTI_CORE_SUPPORT == STD_OFF)
  /* Pointer pointing to the channel configuration */
  P2CONST(Pwm_ChannelConfigType, AUTOMATIC, PWM_CONFIG_CONST) LpChannelConfig;
  /* Index of HW IP Type */
  VAR(volatile uint8, AUTOMATIC) LucTimerUnitType;
  #endif

  #if (PWM_DEV_ERROR_DETECT == STD_ON)
  /* Declare the variable to store the DET return value */
  VAR(uint8, AUTOMATIC) LucDetErrFlag;
  /* Checking Det error */
  LucDetErrFlag = Pwm_CheckDetErrors(ChannelNumber, PWM_SET_OUTPUTTOIDLE_SID);

  if (E_OK == LucDetErrFlag)
  #endif /* End of PWM_DEV_ERROR_DETECT == STD_ON */
  {
    #if (PWM_MULTI_CORE_SUPPORT == STD_ON)
    /* Get the spinlock */
    /* Enter Protected area */
    PWM_ENTER_CRITICAL_SECTION(PWM_RAM_DATA_PROTECTION_GLOBAL);
    /* Set request to the master core if the shared buffer is ready - not locked by Satellite */
    if (Pwm_UnLockedStatus(Pwm_GaaSetOutputToIdleBuffer[ChannelNumber].blBufferLock))                                   /* PRQA S 3432 # JV-01 */
    {
      /* Lock the shared buffer */
      Pwm_LockProcess(Pwm_GaaSetOutputToIdleBuffer[ChannelNumber].blBufferLock);                                        /* PRQA S 3432 # JV-01 */
      /* Release the spinlock */
      PWM_EXIT_CRITICAL_SECTION(PWM_RAM_DATA_PROTECTION_GLOBAL);
      /* Request is issued */
      Pwm_GaaSetOutputToIdleBuffer[ChannelNumber].blSetReq = PWM_TRUE;
      /* Release Lock */
      Pwm_UnLockProcess(Pwm_GaaSetOutputToIdleBuffer[ChannelNumber].blBufferLock);                                      /* PRQA S 3432 # JV-01 */
    }
    else
    {
      /* Release the spinlock */
      PWM_EXIT_CRITICAL_SECTION(PWM_RAM_DATA_PROTECTION_GLOBAL);
      /* Report to Development Errors */
      (void)Det_ReportRuntimeError(PWM_MODULE_ID, PWM_INSTANCE_ID, PWM_SET_OUTPUTTOIDLE_SID, PWM_E_REQUEST_FALSE);
    }
    #else
    /* Updating the channel config parameter to the current channel */
    LpChannelConfig = &Pwm_GpChannelConfig[ChannelNumber];
    /* Get the Timer Unit Type*/
    LucTimerUnitType = LpChannelConfig->ucTimerUnitType;
    /* Set the output of a channel to its Idle state */
    if (NULL_PTR != Pwm_GaaHwFunc[LucTimerUnitType]->pHWSetOutputToIdle)                                                /* PRQA S 3416 # JV-01 */
    {
      /* Invoke low level driver for initializing the hardware */
      Pwm_GaaHwFunc[LucTimerUnitType]->pHWSetOutputToIdle(ChannelNumber);
    } /* else No action required */
    #endif /* End of (PWM_MULTI_CORE_SUPPORT == STD_ON) */
  } /* else No action required */
}

#define PWM_STOP_SEC_PUBLIC_CODE_GLOBAL
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif

/***********************************************************************************************************************
** Function Name        : Pwm_GetOutputState
**
** Service ID           : 0x05
**
** Description          : This API is used to get the output state of PWM channel.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant
**
** Input Parameters     : ChannelNumber
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return parameter     : Pwm_OutputStateType (PWM_LOW / PWM_HIGH)
**
** Preconditions        : 1.PWM Driver should be initialized.
**                        2.This API is available only if the pre-compile option PWM_GET_OUTPUT_STATE_API is STD_ON.
**
** Global Variables     : Pwm_GpChannelConfig, Pwm_GaaHwFunc
**
** Functions invoked    : Pwm_<HW-IP>_GetOutputState, Pwm_CheckDetErrors
**
** Registers Used       : None
**
** Reference ID         : PWM_DUD_ACT_006
***********************************************************************************************************************/
#if (PWM_GET_OUTPUT_STATE_API == STD_ON)
#define PWM_START_SEC_PUBLIC_CODE_GLOBAL
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(Pwm_OutputStateType, PWM_PUBLIC_CODE) Pwm_GetOutputState(Pwm_ChannelType ChannelNumber)                            /* PRQA S 1503 # JV-01 */
{
  /* Pointer pointing to the channel configuration */
  P2CONST(Pwm_ChannelConfigType, AUTOMATIC, PWM_CONFIG_CONST) LpChannelConfig;
  VAR(Pwm_OutputStateType, AUTOMATIC) LenRetOutputState;
  VAR(volatile uint8, AUTOMATIC) LucTimerUnitType;
  #if (PWM_DEV_ERROR_DETECT == STD_ON)
  /* Declare the variable to store the DET return value */
  VAR(uint8, AUTOMATIC) LucDetErrFlag;
  /* Checking Det error */
  LucDetErrFlag = Pwm_CheckDetErrors(ChannelNumber, PWM_GET_OUTPUTSTATE_SID);
  #endif /* End of PWM_DEV_ERROR_DETECT == STD_ON */

  /* Initialize the return value in case of DET error */
  LenRetOutputState = PWM_LOW;

  #if (PWM_DEV_ERROR_DETECT == STD_ON)
  if (E_OK == LucDetErrFlag)
  #endif /* End of PWM_DEV_ERROR_DETECT == STD_ON */
  {
    /* Updating the channel config parameter to the current channel */
    LpChannelConfig = &Pwm_GpChannelConfig[ChannelNumber];
    /* Get the Timer Unit Type*/
    LucTimerUnitType = LpChannelConfig->ucTimerUnitType;

    /* Set the output of a channel to its Idle state */
    if (NULL_PTR != Pwm_GaaHwFunc[LucTimerUnitType]->pHWGetOutputState)                                                 /* PRQA S 3416 # JV-01 */
    {
      /* Invoke low level driver for initializing the hardware */
      LenRetOutputState = Pwm_GaaHwFunc[LucTimerUnitType]->pHWGetOutputState(ChannelNumber);
    } /* else No action required */
  } /* else No action required */

  return LenRetOutputState;
}
#define PWM_STOP_SEC_PUBLIC_CODE_GLOBAL
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of (PWM_GET_OUTPUT_STATE_API == STD_ON) */

/***********************************************************************************************************************
** Function Name        : Pwm_DisableNotification
**
** Service ID           : 0x06
**
** Description          : This API is used to disable notification of PWM channel.
**
** Sync/Async           : Asynchronous
**
** Re-entrancy          : Reentrant
**
** Input Parameters     : ChannelNumber
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return parameter     : None
**
** Preconditions        : 1.PWM Driver should be initialized.
**                        2.This API is available only if the pre-compile option PWM_NOTIFICATION_SUPPORTED is STD_ON.
**
** Global Variables     : Pwm_GpChannelConfig, Pwm_GaaNotifStatus, Pwm_GaaHwFunc
**
** Functions invoked    : Det_ReportError, Pwm_<HW-IP>_DisableNotification, Pwm_CheckDetErrors
**
** Registers Used       : None
**
** Reference ID         : PWM_DUD_ACT_007, PWM_DUD_ACT_007_ERR001, PWM_DUD_ACT_007_ERR002, PWM_DUD_ACT_007_GBL001
***********************************************************************************************************************/
#if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
#define PWM_START_SEC_PUBLIC_CODE_GLOBAL
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, PWM_PUBLIC_CODE) Pwm_DisableNotification(Pwm_ChannelType ChannelNumber)                                      /* PRQA S 1503 # JV-01 */
{
  /* Pointer to channel configuration */
  P2CONST(Pwm_ChannelConfigType, PWM_VAR_NO_INIT, PWM_CONFIG_DATA) LpChannelConfig;
  /* Index of HW IP Type */
  VAR(volatile uint8, AUTOMATIC) LucTimerUnitType;
  #if (PWM_DEV_ERROR_DETECT == STD_ON)
  /* Declare the variable to store the DET return value */
  VAR(uint8, AUTOMATIC) LucDetErrFlag;
  /* Checking Det error */
  LucDetErrFlag = Pwm_CheckDetErrors(ChannelNumber, PWM_DISABLENOTIFICATION_SID);

  if (E_OK == LucDetErrFlag)
  #endif /* End of (PWM_DEV_ERROR_DETECT == STD_ON) */
  {
    LpChannelConfig = &Pwm_GpChannelConfig[ChannelNumber];

    #if (PWM_DEV_ERROR_DETECT == STD_ON)
    /* Check the notification is already disabled */
    if (PWM_FALSE == Pwm_GaaNotifStatus[ChannelNumber])                                                                 /* PRQA S 1881 # JV-01 */
    {
      /* Report to DET module */
      (void)Det_ReportError(PWM_MODULE_ID, PWM_INSTANCE_ID, PWM_DISABLENOTIFICATION_SID, PWM_E_ALREADY_DISABLED);
      LucDetErrFlag = E_NOT_OK;
    } /* else No action required */

    if (NULL_PTR == LpChannelConfig->pPwmEdgeNotifPtr)
    {
      /* Report to DET module */
      (void)Det_ReportError(PWM_MODULE_ID, PWM_INSTANCE_ID, PWM_DISABLENOTIFICATION_SID, PWM_E_NOTIFY_NOTCONFIG);
      LucDetErrFlag = E_NOT_OK;
    } /* else No action required */

    if (E_OK == LucDetErrFlag)
    #endif
    {
      /* Get the Timer Unit Type*/
      LucTimerUnitType = LpChannelConfig->ucTimerUnitType;
      /* Disable Interrupt Processing */
      if (NULL_PTR != Pwm_GaaHwFunc[LucTimerUnitType]->pHWDisableNotification)                                          /* PRQA S 3416 # JV-01 */
      {
        /* Invoke low level driver for initializing the hardware */
        Pwm_GaaHwFunc[LucTimerUnitType]->pHWDisableNotification(ChannelNumber);
      } /* else No action required */

      /* Check whether any notifications is configured for this channel */
      if (NULL_PTR != LpChannelConfig->pPwmEdgeNotifPtr)
      {
        /* Notification is disabled */
        Pwm_GaaNotifStatus[ChannelNumber] = (uint8)PWM_FALSE;                                                           /* PRQA S 4304 # JV-01 */
      } /* else  No action required */
    }  /* else  No action required */
  }/* End of if (E_OK == LucDetErrFlag) */
}
#define PWM_STOP_SEC_PUBLIC_CODE_GLOBAL
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of (PWM_NOTIFICATION_SUPPORTED == STD_ON) */

/***********************************************************************************************************************
** Function Name        : Pwm_EnableNotification
**
** Service ID           : 0x07
**
** Description          : This API is used to enable notification for TAU channel.
** Sync/Async           : Asynchronous
**
** Re-entrancy          : Reentrant
**
** Input Parameters     : ChannelNumber and Notification
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return parameter     : None
**
** Preconditions        : 1.PWM Driver should be initialized.
**                        2.This API is available only if the pre-compile option PWM_NOTIFICATION_SUPPORTED is STD_ON.
**
** Global Variables     : Pwm_GpChannelConfig, Pwm_GaaNotifStatus, Pwm_GaaHwFunc
**
** Functions invoked    : Det_ReportError, Pwm_<HW-IP>_EnableNotification, Pwm_CheckDetErrors
**
** Registers Used       : None
**
** Reference ID         : PWM_DUD_ACT_008, PWM_DUD_ACT_008_ERR001, PWM_DUD_ACT_008_ERR002
***********************************************************************************************************************/
#if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
#define PWM_START_SEC_PUBLIC_CODE_GLOBAL
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, PWM_PUBLIC_CODE)
                           Pwm_EnableNotification(Pwm_ChannelType ChannelNumber, Pwm_EdgeNotificationType Notification) /* PRQA S 1503 # JV-01 */
{
  /* Pointer pointing to the channel configuration */
  P2CONST(Pwm_ChannelConfigType, AUTOMATIC, PWM_CONFIG_CONST) LpChannelConfig;
  /* Index of HW IP Type */
  VAR(volatile uint8, AUTOMATIC) LucTimerUnitType;
  #if (PWM_DEV_ERROR_DETECT == STD_ON)
  /* Declare the variable to store the DET return value */
  VAR(uint8, AUTOMATIC) LucDetErrFlag;

  /* Checking Det error */
  LucDetErrFlag = Pwm_CheckDetErrors(ChannelNumber, PWM_ENABLENOTIFICATION_SID);

  if (E_OK == LucDetErrFlag)
  #endif /* End of (PWM_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (PWM_DEV_ERROR_DETECT == STD_ON)
    if (PWM_BOTH_EDGES < Notification)
    {
      /* Report to DET module */
      (void)Det_ReportError(PWM_MODULE_ID, PWM_INSTANCE_ID, PWM_ENABLENOTIFICATION_SID, PWM_E_PARAM_VALUE);
      LucDetErrFlag = E_NOT_OK;
    } /* else No action required */

    /* Check if notification status is already TRUE */
    if (PWM_TRUE == Pwm_GaaNotifStatus[ChannelNumber])                                                                  /* PRQA S 1881 # JV-01 */
    {
      /* Report to DET module */
      (void)Det_ReportError(PWM_MODULE_ID, PWM_INSTANCE_ID, PWM_ENABLENOTIFICATION_SID, PWM_E_ALREADY_ENABLED);
      LucDetErrFlag = E_NOT_OK;
    } /* else No action required */

    if (E_OK == LucDetErrFlag)
    #endif /* (PWM_DEV_ERROR_DETECT == STD_ON) */
    {
      /* Updating the channel config parameter to the current channel */
      LpChannelConfig = &Pwm_GpChannelConfig[ChannelNumber];
      /* Get the Timer Unit Type*/
      LucTimerUnitType = LpChannelConfig->ucTimerUnitType;
      /* Clear the Pending Interrupts and Enable Interrupt Processing for Slave */
      if (NULL_PTR != Pwm_GaaHwFunc[LucTimerUnitType]->pHWEnableNotification)                                           /* PRQA S 3416 # JV-01 */
      {
        /* Invoke low level driver for initializing the hardware */
        Pwm_GaaHwFunc[LucTimerUnitType]->pHWEnableNotification(ChannelNumber, Notification);
      } /* else No action required */
    } /* else No action required */
  } /* else No action required */
  /* End of LucDetErrFlag is E_OK */
}
#define PWM_STOP_SEC_PUBLIC_CODE_GLOBAL
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of (PWM_NOTIFICATION_SUPPORTED == STD_ON) */

/***********************************************************************************************************************
** Function Name        : Pwm_GetVersionInfo
**
** Service ID           : 0x08
**
** Description          : This service returns the version information of this module.
**
** Sync/Async           : Synchronous
**
** Reentrancy           : Reentrant
**
** Input Parameters     : None
**
** InOut Parameters     : None
**
** Output Parameters    : versioninfo
**
** Return parameter     : None
**
** Preconditions        : None
**
** Global Variables     : None
**
** Functions Invoked    : Det_ReportError
**
** Registers Used       : None
**
** Reference ID         : PWM_DUD_ACT_009, PWM_DUD_ACT_009_ERR001
***********************************************************************************************************************/
#if (PWM_VERSION_INFO_API == STD_ON)
#define PWM_START_SEC_PUBLIC_CODE_GLOBAL
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, PWM_PUBLIC_CODE) Pwm_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, PWM_APPL_DATA) versioninfo)        /* PRQA S 1503, 3432 # JV-01, JV-01 */
{
  #if (PWM_DEV_ERROR_DETECT == STD_ON)
  /* Check if parameter passed is equal to Null pointer */
  if (NULL_PTR == versioninfo)
  {
    (void)Det_ReportError(PWM_MODULE_ID, PWM_INSTANCE_ID, PWM_GET_VERSION_INFO_SID, PWM_E_PARAM_POINTER);
  }
  else
  #endif /* (PWM_DEV_ERROR_DETECT == STD_ON) */
  {
    versioninfo->vendorID = PWM_VENDOR_ID;
    versioninfo->moduleID = PWM_MODULE_ID;
    versioninfo->sw_major_version = PWM_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version = PWM_SW_MINOR_VERSION;
    versioninfo->sw_patch_version = PWM_SW_PATCH_VERSION;
  }
}

#define PWM_STOP_SEC_PUBLIC_CODE_GLOBAL
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* (PWM_VERSION_INFO_API == STD_ON) */

/***********************************************************************************************************************
** Function Name        : Pwm_CheckDetErrors
**
** Service ID           : None
**
** Description          : This API is used to report DET for invalid initialization and invalid LddChannelNumber
**                        in this file.
**
** Sync/Async           : -
**
** Re-entrancy          : -
**
** Input Parameters     : LddChannelNumber, LucApiSid
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return parameter     : Std_ReturnType
**
** Preconditions        : NA
**
** Global Variables     : Pwm_GblDriverStatus, Pwm_GpChannelConfig
**
** Functions invoked    : Det_ReportError
**
** Registers Used       : None
**
** Reference ID         : PWM_DUD_ACT_016, PWM_DUD_ACT_016_ERR001, PWM_DUD_ACT_016_ERR002. PWM_DUD_ACT_016_ERR003
***********************************************************************************************************************/
#if ((PWM_DEV_ERROR_DETECT == STD_ON) && ((PWM_GET_OUTPUT_STATE_API == STD_ON) || (PWM_SET_DUTY_CYCLE_API == STD_ON)|| \
(PWM_SET_OUTPUT_TO_IDLE_API == STD_ON) || (PWM_SET_PERIOD_AND_DUTY_API == STD_ON) || \
(PWM_SELECT_CHANNEL_CLK_API == STD_ON) || (PWM_SET_CHANNEL_OUTPUT_API == STD_ON) || \
(PWM_SET_TRIGGER_DELAY_API == STD_ON) || (PWM_READ_CONV_RESLUT_API == STD_ON) || \
(PWM_ENABLE_DISABLE_AD_TRG_API == STD_ON) || (PWM_NOTIFICATION_SUPPORTED == STD_ON)))
#define PWM_START_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

static FUNC(Std_ReturnType, PWM_PRIVATE_CODE) Pwm_CheckDetErrors(Pwm_ChannelType LddChannelNumber, uint8 LucApiSid)
{
  VAR(Std_ReturnType, AUTOMATIC) LucReturnValue;

  #if (PWM_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare the local variable to store the current used core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = PWM_ONE << (uint8)GetCoreID();
  #endif /* End of PWM_MULTI_CORE_SUPPORT == STD_ON */

  /* Initialize return value */
  LucReturnValue = E_OK;

  /* Check if the PWM Driver is initialized properly */
  if (PWM_INITIALIZED != Pwm_GblDriverStatus)                                                                           /* PRQA S 3416 # JV-01 */
  {
    /* Report to DET module */
    (void)Det_ReportError(PWM_MODULE_ID, PWM_INSTANCE_ID, LucApiSid, PWM_E_UNINIT);
    LucReturnValue = E_NOT_OK;
  }
  else
  {
    /* Check LddChannelNumber is in the valid range */
    if (PWM_MAX_CHANNEL_ID_CONFIGURED < LddChannelNumber)
    {
      /* Report to DET module */
      (void)Det_ReportError(PWM_MODULE_ID, PWM_INSTANCE_ID, LucApiSid, PWM_E_PARAM_CHANNEL);
      LucReturnValue = E_NOT_OK;
    }
    #if (PWM_MULTI_CORE_SUPPORT == STD_ON)
    /* Check that the target core is mapping into this channel */
    else if (PWM_ZERO == (Pwm_GpChannelConfig[LddChannelNumber].ucCoreIndex & LucCoreID))                               /* PRQA S 2004, 3416, 0404 # JV-01, JV-01, JV-01 */
    {
      /* Report to DET module */
      (void)Det_ReportError(PWM_MODULE_ID, PWM_INSTANCE_ID, LucApiSid, PWM_E_INVALID_CORE);
      LucReturnValue = E_NOT_OK;
    } /* else No action required */
    #endif /* End of PWM_MULTI_CORE_SUPPORT == STD_ON */
  }

  return (LucReturnValue);
}
#define PWM_STOP_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of (PWM_DEV_ERROR_DETECT == STD_ON) */

/***********************************************************************************************************************
** Function Name        : Pwm_SelectChannelClk
**
** Service ID           : 0xA0
**
** Description          : This API is used to select one of the four clock sources for both TAUD and TAUJ channel
**                        at run time.
**
** Sync/Async           : Synchronous (Single core)/Asynchronous (Multi core)
**
** Re-entrancy          : Reentrant
**
** Input Parameters     : ChannelNumber
**                        ClockSource
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return parameter     : None
**
** Preconditions        : 1.PWM Driver should be initialized.
**                        2.This API is available only if the pre-compile option PWM_SELECT_CHANNEL_CLK_API is STD_ON.
**
** Global Variables     : Pwm_GpChannelConfig, Pwm_GaaHwFunc, Pwm_GaaSelectChannelClkBuffer
**
** Functions invoked    : Det_ReportError, Pwm_<HW-IP>_SelectChannelClk, Pwm_CheckDetErrors
**
** Registers Used       : None
**
** Reference ID         : PWM_DUD_ACT_010, PWM_DUD_ACT_010_ERR001, PWM_DUD_ACT_010_ERR002, PWM_DUD_ACT_010_CRT001
** Reference ID         : PWM_DUD_ACT_010_CRT002, PWM_DUD_ACT_010_CRT003, PWM_DUD_ACT_010_ERR003
***********************************************************************************************************************/
#if (PWM_SELECT_CHANNEL_CLK_API == STD_ON)
#define PWM_START_SEC_PUBLIC_CODE_GLOBAL
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, PWM_PUBLIC_CODE) Pwm_SelectChannelClk(Pwm_ChannelType ChannelNumber, Pwm_ClockSourceType ClockSource)        /* PRQA S 1503 # JV-01 */
{
  #if (PWM_MULTI_CORE_SUPPORT == STD_OFF || PWM_DEV_ERROR_DETECT == STD_ON)
  /* Pointer pointing to the channel configuration */
  P2CONST(Pwm_ChannelConfigType, AUTOMATIC, PWM_CONFIG_CONST) LpChannelConfig;
  /* Index of HW IP Type */
  VAR(volatile uint8, AUTOMATIC) LucTimerUnitType;                                                                      /* PRQA S 3205 # JV-01 */
  #endif

  #if (PWM_DEV_ERROR_DETECT == STD_ON)
  /* Declare the variable to store the DET return value */
  VAR(uint8, AUTOMATIC) LucDetErrFlag;
  LpChannelConfig = &Pwm_GpChannelConfig[ChannelNumber];
  /* Checking Det error */
  LucDetErrFlag = Pwm_CheckDetErrors(ChannelNumber, PWM_SELECT_CHANNEL_CLK_SID);
  /* Check for valid Clock source */
  if (E_OK == LucDetErrFlag)
  {
    if((PWM_HWIP_GTM == LpChannelConfig->ucTimerUnitType) &&
    ((PWM_CCM_FXCLK_RES0 > ClockSource) || (PWM_CCM_CLK_RES_7 < ClockSource)))
    {
      /* Report to DET module */
      (void)Det_ReportError(PWM_MODULE_ID, PWM_INSTANCE_ID, PWM_SELECT_CHANNEL_CLK_SID, PWM_E_PARAM_VALUE);
      LucDetErrFlag = E_NOT_OK;
    }
    else if((PWM_HWIP_GTM != LpChannelConfig->ucTimerUnitType) && (ClockSource > PWM_CLKBUSLINE3))                      /* PRQA S 2004 # JV-01 */
    {
      /* Report to DET module */
      (void)Det_ReportError(PWM_MODULE_ID, PWM_INSTANCE_ID, PWM_SELECT_CHANNEL_CLK_SID, PWM_E_PARAM_VALUE);
      LucDetErrFlag = E_NOT_OK;
    } /* else nothing */
  } /* else nothing */

  if (E_OK == LucDetErrFlag)
  #endif /* End of PWM_DEV_ERROR_DETECT == STD_ON */
  {
    #if (PWM_MULTI_CORE_SUPPORT == STD_ON)
    /* Get the spinlock */
    /* Enter Protected area */
    PWM_ENTER_CRITICAL_SECTION(PWM_RAM_DATA_PROTECTION_GLOBAL);
    /* Set request to the master core if the shared buffer is ready - not locked by Satellite */
    if (Pwm_UnLockedStatus(Pwm_GaaSelectChannelClkBuffer[ChannelNumber].blBufferLock))                                  /* PRQA S 3432 # JV-01 */
    {
      /* Lock the shared buffer */
      Pwm_LockProcess(Pwm_GaaSelectChannelClkBuffer[ChannelNumber].blBufferLock);                                       /* PRQA S 3432 # JV-01 */
      /* Release the spinlock */
      PWM_EXIT_CRITICAL_SECTION(PWM_RAM_DATA_PROTECTION_GLOBAL);
      /* Update the request */
      Pwm_GaaSelectChannelClkBuffer[ChannelNumber].lddClockSource = ClockSource;
      /* Request is issued */
      Pwm_GaaSelectChannelClkBuffer[ChannelNumber].blSetReq = PWM_TRUE;
      /* Release Lock */
      Pwm_UnLockProcess(Pwm_GaaSelectChannelClkBuffer[ChannelNumber].blBufferLock);                                     /* PRQA S 3432 # JV-01 */
    }
    else
    {
      /* Release the spinlock */
      PWM_EXIT_CRITICAL_SECTION(PWM_RAM_DATA_PROTECTION_GLOBAL);
      /* Report to Development Errors */
      (void)Det_ReportRuntimeError(PWM_MODULE_ID, PWM_INSTANCE_ID, PWM_SELECT_CHANNEL_CLK_SID, PWM_E_REQUEST_FALSE);
    }
    #else
    /* Updating the channel config parameter to the current channel */
    LpChannelConfig = &Pwm_GpChannelConfig[ChannelNumber];
    /* Get the Timer Unit Type*/
    LucTimerUnitType = LpChannelConfig->ucTimerUnitType;

    /* Set the Duty cycle for the required channel */
    if (NULL_PTR != Pwm_GaaHwFunc[LucTimerUnitType]->pHWSelectChannelClk)                                               /* PRQA S 3416 # JV-01 */
    {
      /* Invoke low level driver for initializing the hardware */
      Pwm_GaaHwFunc[LucTimerUnitType]->pHWSelectChannelClk(ChannelNumber, ClockSource);
    } /* else No action required */
    #endif /* End of (PWM_MULTI_CORE_SUPPORT == STD_ON) */
  } /* else No action required */
}
#define PWM_STOP_SEC_PUBLIC_CODE_GLOBAL
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of (PWM_SELECT_CHANNEL_CLK_API == STD_ON) */

/***********************************************************************************************************************
** Function Name        : Pwm_SetChannelOutput
**
** Service ID           : 0x0B
**
** Description          : This API is used to set the PWM output to a constant signal for the duration of
*                         the current period.
**
** Sync/Async           : Synchronous (Single core)/Asynchronous (Multi core)
**
** Re-entrancy          : Reentrant
**
** Input Parameters     : ChannelNumber
**                        State
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return parameter     : None
**
** Preconditions        : 1.PWM Driver should be initialized.
**                        2.This API is available only if the pre-compile option PWM_SET_CHANNEL_OUTPUT_API is STD_ON.
**
** Global Variables     : Pwm_GpChannelConfig, Pwm_GaaHwFunc, Pwm_GaaSetChannelOutputBuffer
**
** Functions invoked    : Det_ReportError, Pwm_<HW-IP>_SetChannelOutput, Pwm_CheckDetErrors
**
** Registers Used       : None
**
** Reference ID         : PWM_DUD_ACT_014, PWM_DUD_ACT_014_ERR001, PWM_DUD_ACT_014_CRT001, PWM_DUD_ACT_014_CRT002,
** Reference ID         : PWM_DUD_ACT_014_CRT003, PWM_DUD_ACT_014_ERR002
***********************************************************************************************************************/
#if (PWM_SET_CHANNEL_OUTPUT_API == STD_ON)
#define PWM_START_SEC_PUBLIC_CODE_GLOBAL
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, PWM_PUBLIC_CODE) Pwm_SetChannelOutput(Pwm_ChannelType ChannelNumber, Pwm_OutputStateType State)              /* PRQA S 1503 # JV-01 */
{
  #if (PWM_MULTI_CORE_SUPPORT == STD_OFF)
  /* Pointer pointing to the channel configuration */
  P2CONST(Pwm_ChannelConfigType, AUTOMATIC, PWM_CONFIG_CONST) LpChannelConfig;
  /* Index of HW IP Type */
  VAR(volatile uint8, AUTOMATIC) LucTimerUnitType;
  #endif

  #if (PWM_DEV_ERROR_DETECT == STD_ON)
  /* Declare the variable to store the DET return value */
  VAR(uint8, AUTOMATIC) LucDetErrFlag;

  /* Checking Det error */
  LucDetErrFlag = Pwm_CheckDetErrors(ChannelNumber, PWM_SET_CHANNEL_OUTPUT_SID);

  /* Check for valid state */
  if (E_OK == LucDetErrFlag)
  {
    if ((PWM_LOW != State) && (PWM_HIGH != State))
    {
      /* Report to DET module */
      (void)Det_ReportError(PWM_MODULE_ID, PWM_INSTANCE_ID, PWM_SET_CHANNEL_OUTPUT_SID, PWM_E_PARAM_VALUE);
      LucDetErrFlag = E_NOT_OK;
    } /* else  No action required */
  } /* else No action required */

  if (E_OK == LucDetErrFlag)
  #endif /* End of (PWM_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (PWM_MULTI_CORE_SUPPORT == STD_ON)
    /* Get the spinlock */
    /* Enter Protected area  */
    PWM_ENTER_CRITICAL_SECTION(PWM_RAM_DATA_PROTECTION_GLOBAL);
    /* Set request to the master core if the shared buffer is ready - not locked by Satellite */
    if (Pwm_UnLockedStatus(Pwm_GaaSetChannelOutputBuffer[ChannelNumber].blBufferLock))                                  /* PRQA S 3432 # JV-01 */
    {
      /* Lock the shared buffer */
      Pwm_LockProcess(Pwm_GaaSetChannelOutputBuffer[ChannelNumber].blBufferLock);                                       /* PRQA S 3432 # JV-01 */
      /* Release the spinlock */
      PWM_EXIT_CRITICAL_SECTION(PWM_RAM_DATA_PROTECTION_GLOBAL);
      /* Update the request */
      Pwm_GaaSetChannelOutputBuffer[ChannelNumber].lddState = State;
      /* Request is issued */
      Pwm_GaaSetChannelOutputBuffer[ChannelNumber].blSetReq = PWM_TRUE;
      /* Release Lock */
      Pwm_UnLockProcess(Pwm_GaaSetChannelOutputBuffer[ChannelNumber].blBufferLock);                                     /* PRQA S 3432 # JV-01 */
    }
    else
    {
      /* Release the spinlock */
      PWM_EXIT_CRITICAL_SECTION(PWM_RAM_DATA_PROTECTION_GLOBAL);
      /* Report to Development Errors */
      (void)Det_ReportRuntimeError(PWM_MODULE_ID, PWM_INSTANCE_ID, PWM_SET_CHANNEL_OUTPUT_SID, PWM_E_REQUEST_FALSE);
    }
    #else
    /* Updating the channel config parameter to the current channel */
    LpChannelConfig = &Pwm_GpChannelConfig[ChannelNumber];
    /* Get the Timer Unit Type*/
    LucTimerUnitType = LpChannelConfig->ucTimerUnitType;

    /* Set the output of a channel to constant signal High or Low for current period */
    if (NULL_PTR != Pwm_GaaHwFunc[LucTimerUnitType]->pHWSetChannelOutput)                                               /* PRQA S 3416 # JV-01 */
    {
      /* Invoke low level driver for initializing the hardware */
      Pwm_GaaHwFunc[LucTimerUnitType]->pHWSetChannelOutput(ChannelNumber, State);
    } /* else No action required */
    #endif /* End of (PWM_MULTI_CORE_SUPPORT == STD_ON) */
  } /* else No action required */
}

#define PWM_STOP_SEC_PUBLIC_CODE_GLOBAL
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif

/***********************************************************************************************************************
** Function Name        : Pwm_SynchronousInit
**
** Service ID           : 0xA1
**
** Description          : This API performs the initialization of PWM channels configured to support synchronous
**                        start/stop of timers.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Non-Reentrant
**
** Input Parameters     : None.
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return parameter     : None
**
** Preconditions        : 1.PWM Driver should be initialized.
**                        2.This API is available only if the pre-compile option PWM_SYNC_START_SUPPORT is STD_ON.
**
** Global Variables     : Pwm_GblDriverStatus, Pwm_GblSyncInitStatus, Pwm_GaaHwFunc, Pwm_GaaHWIP_Used
**
** Functions invoked    : Det_ReportError, Pwm_<HW-IP>_SynchronousInit
**
** Registers Used       : None
**
** Reference ID         : PWM_DUD_ACT_011, PWM_DUD_ACT_011_ERR001, PWM_DUD_ACT_011_ERR002, PWM_DUD_ACT_011_GBL001,
** Reference ID         : PWM_DUD_ACT_011_ERR003
***********************************************************************************************************************/
#if (PWM_SYNC_START_SUPPORT == STD_ON)
#define PWM_START_SEC_PUBLIC_CODE_LOCAL
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, PWM_PUBLIC_CODE) Pwm_SynchronousInit(void)                                                                   /* PRQA S 1503 # JV-01 */
{
  /* Index of HW IP Type */
  VAR(volatile uint8, AUTOMATIC) LucHWIPType;
  VAR(uint32, AUTOMATIC) LulCount;
  #if (PWM_DEV_ERROR_DETECT == STD_ON)
  /* Declare the variable to store the DET return value */
  VAR(uint8, AUTOMATIC) LucDetErrFlag;
    /* Initialize error flag */
  LucDetErrFlag = E_OK;
  
  /* Check if the PWM Driver is initialized or not */
  if (PWM_INITIALIZED != Pwm_GblDriverStatus)                                                                           /* PRQA S 3416 # JV-01 */
  {
    /* Report to DET */
    (void)Det_ReportError(PWM_MODULE_ID, PWM_INSTANCE_ID, PWM_SYNCHRONOUS_INIT_SID, PWM_E_UNINIT);
    LucDetErrFlag = E_NOT_OK;
  }
  else
  {
    #if (PWM_MULTI_CORE_SUPPORT == STD_ON)
    /* Declare the local variable to store the current used core ID */
    VAR(volatile uint8, AUTOMATIC) LucCoreID;
    /* Get the current core ID by OS service */
    LucCoreID = (uint8)GetCoreID();
    
    /* Check if the control API is executed on the Master core */
    if (Pwm_GucKernelCoreId != LucCoreID)                                                                               /* PRQA S 3416 # JV-01 */
    {
      /* Report Error to DET */
      (void)Det_ReportError(PWM_MODULE_ID, PWM_INSTANCE_ID, PWM_SYNCHRONOUS_INIT_SID, PWM_E_INVALID_CORE);
      LucDetErrFlag = E_NOT_OK;
    }
    else
    #endif /* End of (PWM_MULTI_CORE_SUPPORT == STD_ON) */
    {
      if (PWM_INITIALIZED == Pwm_GblSyncInitStatus)                                                                     /* PRQA S 3416 # JV-01 */
      {
        /* Report to DET */
        (void)Det_ReportError(PWM_MODULE_ID, PWM_INSTANCE_ID, PWM_SYNCHRONOUS_INIT_SID, PWM_E_ALREADY_INITIALIZED);
        LucDetErrFlag = E_NOT_OK;
      } /* else No action required */
    } /* End of PWM_INITIALIZED != Pwm_GblDriverStatus */
  }
  if (E_OK == LucDetErrFlag)
  #endif /* End of (PWM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Initialize all PWM channels configured to support synchronous start/stop of timers, this excludes
      initialization of channels that will be handled by complex drivers */
    for (LulCount = (uint32)PWM_ZERO; LulCount < (uint32)PWM_TOTAL_HW_IP_CONFIG; LulCount++)                            /* PRQA S 2877 # JV-01 */
    {
      LucHWIPType = Pwm_GaaHWIP_Used[LulCount].ucIndex;

      if (NULL_PTR != Pwm_GaaHwFunc[LucHWIPType]->pHWSynchronousInit)                                                   /* PRQA S 3416 # JV-01 */
      {
        /* Invoke low level driver for initializing the hardware */
        Pwm_GaaHwFunc[LucHWIPType]->pHWSynchronousInit();
      } /* else No action required */
    }

    #if (PWM_DEV_ERROR_DETECT == STD_ON)
    Pwm_GblSyncInitStatus = PWM_INITIALIZED;
    #endif
  } /* else No action required */
}
#define PWM_STOP_SEC_PUBLIC_CODE_LOCAL
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* (PWM_SYNC_START_SUPPORT == STD_ON) */

/***********************************************************************************************************************
** Function Name        : Pwm_SynchronousStart
**
** Service ID           : 0xA2
**
** Description          : This API starts PWM channels configured to support synchronous start/stop of timers.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Non-Reentrant
**
** Input Parameters     : None.
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return parameter     : None
**
** Preconditions        : 1.APIs Pwm_Init and Pwm_SynchronousInit should be invoked.
**                        2.This API is available only if the pre-compile option PWM_SYNC_START_SUPPORT is STD_ON.
**
** Global Variables     : Pwm_GblDriverStatus, Pwm_GblSyncInitStatus, Pwm_GblSyncOperationStatus, Pwm_GaaHwFunc
**                        Pwm_GaaHWIP_Used
**
** Functions invoked    : Det_ReportError, Pwm_<HW-IP>_SynchronousStart
**
** Registers Used       : None
**
** Reference ID         : PWM_DUD_ACT_012, PWM_DUD_ACT_012_ERR001, PWM_DUD_ACT_012_ERR002, PWM_DUD_ACT_012_GBL001,
** Reference ID         : PWM_DUD_ACT_012_CRT001, PWM_DUD_ACT_012_CRT002, PWM_DUD_ACT_012_ERR003
***********************************************************************************************************************/
#if (PWM_SYNC_START_SUPPORT == STD_ON)
#define PWM_START_SEC_PUBLIC_CODE_LOCAL
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, PWM_PUBLIC_CODE) Pwm_SynchronousStart(void)                                                                  /* PRQA S 1503 # JV-01 */
{
  /* Index of HW IP Type */
  VAR(volatile uint8, AUTOMATIC) LucHWIPType;
  VAR(uint32, AUTOMATIC) LulCount;
  #if (PWM_DEV_ERROR_DETECT == STD_ON)
  /* Declare the variable to store the DET return value */
  VAR(uint8, AUTOMATIC) LucDetErrFlag;
  /* Initialize error flag */
  LucDetErrFlag = E_OK;

  /* Check if the PWM Driver is initialized and API Pwm_SynchronousInit is invoked or not */
  if ((PWM_INITIALIZED != Pwm_GblDriverStatus) || (PWM_INITIALIZED != Pwm_GblSyncInitStatus))                           /* PRQA S 3415, 3416 # JV-01, JV-01 */
  {
    /* Report to DET */
    (void)Det_ReportError(PWM_MODULE_ID, PWM_INSTANCE_ID, PWM_SYNCHRONOUS_START_SID, PWM_E_UNINIT);
    LucDetErrFlag = E_NOT_OK;
  }
  else
  {
     #if (PWM_MULTI_CORE_SUPPORT == STD_ON)
     /* Declare the local variable to store the current used core ID */
     VAR(volatile uint8, AUTOMATIC) LucCoreID;
     /* Get the current core ID by OS service */
     LucCoreID = (uint8)GetCoreID();
     
     /* Check if the control API is executed on the Master core */
     if (Pwm_GucKernelCoreId != LucCoreID)                                                                              /* PRQA S 3416 # JV-01 */
     {
       /* Report Error to DET */
       (void)Det_ReportError(PWM_MODULE_ID, PWM_INSTANCE_ID, PWM_SYNCHRONOUS_START_SID, PWM_E_INVALID_CORE);
       LucDetErrFlag = E_NOT_OK;
     }
     else
     #endif /* End of (PWM_MULTI_CORE_SUPPORT == STD_ON) */
    {
      if (PWM_SYNC_STOPPED != Pwm_GblSyncOperationStatus)                                                               /* PRQA S 3416 # JV-01 */
      {
        /* Report to DET */
        (void)Det_ReportError(PWM_MODULE_ID, PWM_INSTANCE_ID, PWM_SYNCHRONOUS_START_SID, PWM_E_ALREADY_STARTED);
        LucDetErrFlag = E_NOT_OK;
      } /* else No action required */
    }
  }

  if (E_OK == LucDetErrFlag)
  #endif /* End of (PWM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Enter Protected area */
    PWM_ENTER_CRITICAL_SECTION(PWM_INTERRUPT_CONTROL_PROTECTION);

    for (LulCount = (uint32)PWM_ZERO; LulCount < (uint32)PWM_TOTAL_HW_IP_CONFIG; LulCount++)                            /* PRQA S 2877 # JV-01 */
    {
      LucHWIPType = Pwm_GaaHWIP_Used[LulCount].ucIndex;
      if (NULL_PTR != Pwm_GaaHwFunc[LucHWIPType]->pHWSynchronousStart)                                                  /* PRQA S 3416 # JV-01 */
      {
        /* Invoke low level driver for initializing the hardware */
        Pwm_GaaHwFunc[LucHWIPType]->pHWSynchronousStart();
      } /* else No action required */
    }

    #if (PWM_DEV_ERROR_DETECT == STD_ON)
    Pwm_GblSyncOperationStatus = PWM_SYNC_STARTED;
    #endif

    /* Exit Protected area */
    PWM_EXIT_CRITICAL_SECTION(PWM_INTERRUPT_CONTROL_PROTECTION);
  }
}
#define PWM_STOP_SEC_PUBLIC_CODE_LOCAL
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of (PWM_SYNC_START_SUPPORT == STD_ON) */

/***********************************************************************************************************************
** Function Name        : Pwm_SynchronousStop
**
** Service ID           : 0xA3
**
** Description          : This API stops PWM channels configured to support synchronous start/stop of timers.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Non-Reentrant
**
** Input Parameters     : None.
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return parameter     : None
**
** Preconditions        : 1.APIs Pwm_Init and Pwm_SynchronousInit should be invoked.
**                        2.This API is available only if the pre-compile option PWM_SYNC_START_SUPPORT is STD_ON.
**
** Global Variables     : Pwm_GblDriverStatus, Pwm_GblSyncInitStatus, Pwm_GblSyncOperationStatus, Pwm_GaaHwFunc
**                        Pwm_GaaHWIP_Used
**
** Functions invoked    : Det_ReportError, Pwm_<HW-IP>_SynchronousStop
**
** Registers Used       : None
**
** Reference ID         : PWM_DUD_ACT_013, PWM_DUD_ACT_013_ERR001, PWM_DUD_ACT_013_GBL001, PWM_DUD_ACT_013_ERR002,
** Reference ID         : PWM_DUD_ACT_013_CRT001, PWM_DUD_ACT_013_CRT002
***********************************************************************************************************************/
#if (PWM_SYNC_START_SUPPORT == STD_ON)
#define PWM_START_SEC_PUBLIC_CODE_LOCAL
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, PWM_PUBLIC_CODE) Pwm_SynchronousStop(void)                                                                   /* PRQA S 1503 # JV-01 */
{
  /* Index of HW IP Type */
  VAR(volatile uint8, AUTOMATIC) LucHWIPType;
  VAR(uint32, AUTOMATIC) LulCount;
  #if (PWM_DEV_ERROR_DETECT == STD_ON)
  /* Declare the variable to store the DET return value */
  VAR(uint8, AUTOMATIC) LucDetErrFlag;
  /* Initialize error flag */
  LucDetErrFlag = E_OK;

  /* Check if the PWM Driver is initialized and API Pwm_SynchronousInit is invoked or not */
  if ((PWM_INITIALIZED != Pwm_GblDriverStatus) || (PWM_INITIALIZED != Pwm_GblSyncInitStatus))                           /* PRQA S 3415, 3416 # JV-01, JV-01 */
  {
    /* Report to DET */
    (void)Det_ReportError(PWM_MODULE_ID, PWM_INSTANCE_ID, PWM_SYNCHRONOUS_STOP_SID, PWM_E_UNINIT);
    LucDetErrFlag = E_NOT_OK;
  }  /* else  No action required */
  else
  {
    #if (PWM_MULTI_CORE_SUPPORT == STD_ON)
    /* Declare the local variable to store the current used core ID */
    VAR(volatile uint8, AUTOMATIC) LucCoreID;
    /* Get the current core ID by OS service */
    LucCoreID = (uint8)GetCoreID();
    
    /* Check if the control API is executed on the Master core */
    if (Pwm_GucKernelCoreId != LucCoreID)                                                                               /* PRQA S 3416 # JV-01 */
    {
      /* Report Error to DET */
      (void)Det_ReportError(PWM_MODULE_ID, PWM_INSTANCE_ID, PWM_SYNCHRONOUS_STOP_SID, PWM_E_INVALID_CORE);
      LucDetErrFlag = E_NOT_OK;
    }
    #endif /* End of (PWM_MULTI_CORE_SUPPORT == STD_ON) */
  }
  if (E_OK == LucDetErrFlag)
  #endif /* End of (PWM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Enter Protected area */
    PWM_ENTER_CRITICAL_SECTION(PWM_INTERRUPT_CONTROL_PROTECTION);

    /* Stop all PWM channels configured to support synchronous start/stop of timers, this excludes stopping of channels
    that will be handled by complex drivers */
    for (LulCount = (uint32)PWM_ZERO; LulCount < (uint32)PWM_TOTAL_HW_IP_CONFIG; LulCount++)                            /* PRQA S 2877 # JV-01 */
    {
      LucHWIPType = Pwm_GaaHWIP_Used[LulCount].ucIndex;
      if (NULL_PTR != Pwm_GaaHwFunc[LucHWIPType]->pHWSynchronousStop)                                                   /* PRQA S 3416 # JV-01 */
      {
        /* Invoke low level driver for initializing the hardware */
        Pwm_GaaHwFunc[LucHWIPType]->pHWSynchronousStop();
      } /* else  No action required */
    }

    #if (PWM_DEV_ERROR_DETECT == STD_ON)
    Pwm_GblSyncOperationStatus = PWM_SYNC_STOPPED;
    #endif

    /* Exit Protected area */
    PWM_EXIT_CRITICAL_SECTION(PWM_INTERRUPT_CONTROL_PROTECTION);
  }
}
#define PWM_STOP_SEC_PUBLIC_CODE_LOCAL
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of (PWM_SYNC_START_SUPPORT == STD_ON) */

/***********************************************************************************************************************
** Function Name        : Pwm_SetStatus
**
** Service ID           : none
**
** Description          : This function is change Pwm_GblDriverStatus
**
** Sync/Async           : Synchronous
**
** Reentrancy           : Non-Reentrant
**
** Input Parameters     : LblStatus
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return parameter     : None
**
** Preconditions        : None
**
** Global Variables     : Pwm_GblDriverStatus
**
** Functions Invoked    : None
**
** Registers Used       : None
**
** Reference ID         : PWM_DUD_ACT_015, PWM_DUD_ACT_015_GBL001
***********************************************************************************************************************/
#define PWM_START_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

STATIC FUNC(void, PWM_PRIVATE_CODE) Pwm_SetStatus(boolean LblStatus)
{
  Pwm_GblDriverStatus = LblStatus;
}
#define PWM_STOP_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name        : Pwm_SetTriggerDelay
**
** Service ID           : 0xA5
**
** Description          : This service set A/D Trigger timing for Diag channel during runtime.
**
** Sync/Async           : Synchronous (Single core)/Asynchronous (Multi core)
**
** Re-entrancy          : Reentrant for different channel
**
** Input Parameters     : LddChannelNumber, LusTriggerDelay
**
** InOut Parameters     : none
**
** Output Parameters    : none
**
** Return parameter     : none
**
** Preconditions        : PWM_SET_TRIGGER_DELAY_API is STD_ON
**
** Global Variables     : Pwm_GpChannelConfig, Pwm_GaaHwFunc, Pwm_GaaSetTriggerDelayBuffer
**
** Functions invoked    : Det_ReportError, Pwm_CheckDetErrors, Pwm_HW_DIAG_SetTriggerDelay
**
** Registers Used       : none
**
** Reference ID         : PWM_DUD_ACT_094, PWM_DUD_ACT_094_ERR001, PWM_DUD_ACT_094_ERR002
***********************************************************************************************************************/
#if (PWM_SET_TRIGGER_DELAY_API == STD_ON)
#define PWM_START_SEC_PUBLIC_CODE_GLOBAL
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, PWM_PUBLIC_CODE) Pwm_SetTriggerDelay(Pwm_ChannelType LddChannelNumber, uint16 LusTriggerDelay)               /* PRQA S 1503 # JV-01 */
{
  #if (PWM_MULTI_CORE_SUPPORT == STD_OFF)
  VAR(uint8, AUTOMATIC) LucHWIPType;
  #endif

  #if (PWM_DEV_ERROR_DETECT == STD_ON)
  VAR(uint8, AUTOMATIC) LucDetErrFlag;

  /* Checking error */
  LucDetErrFlag = Pwm_CheckDetErrors(LddChannelNumber, PWM_SET_TRIGGER_DELAY_SID);
  if (E_OK == LucDetErrFlag)
  {
    if (PWM_MAX_DUTY_CYCLE_VALUE < LusTriggerDelay)
    {
      /* Report to DET */
      (void)Det_ReportError(PWM_MODULE_ID, PWM_INSTANCE_ID, PWM_SET_TRIGGER_DELAY_SID, PWM_E_PARAM_VALUE);
      LucDetErrFlag = E_NOT_OK;
    } /* else: No action */
  } /* else: No action */

  if (E_OK == LucDetErrFlag)
  #endif /* End of (PWM_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (PWM_MULTI_CORE_SUPPORT == STD_ON)
    /* Get the spinlock */
    /* Enter Protected area  */
    PWM_ENTER_CRITICAL_SECTION(PWM_RAM_DATA_PROTECTION_GLOBAL);
    /* Set request to the master core if the shared buffer is ready - not locked by Satellite */
    if (Pwm_UnLockedStatus(Pwm_GaaSetTriggerDelayBuffer[LddChannelNumber].blBufferLock))                                /* PRQA S 3432 # JV-01 */
    {
      /* Lock the shared buffer */
      Pwm_LockProcess(Pwm_GaaSetTriggerDelayBuffer[LddChannelNumber].blBufferLock);                                     /* PRQA S 3432 # JV-01 */
      /* Release the spinlock */
      PWM_EXIT_CRITICAL_SECTION(PWM_RAM_DATA_PROTECTION_GLOBAL);
      /* Update the request */
      Pwm_GaaSetTriggerDelayBuffer[LddChannelNumber].lusTriggerDelay = LusTriggerDelay;
      /* Request is issued */
      Pwm_GaaSetTriggerDelayBuffer[LddChannelNumber].blSetReq = PWM_TRUE;
      /* Release Lock */
      Pwm_UnLockProcess(Pwm_GaaSetTriggerDelayBuffer[LddChannelNumber].blBufferLock);                                   /* PRQA S 3432 # JV-01 */
    }
    else
    {
      /* Release the spinlock */
      PWM_EXIT_CRITICAL_SECTION(PWM_RAM_DATA_PROTECTION_GLOBAL);
      /* Report to Development Errors */
      (void)Det_ReportRuntimeError(PWM_MODULE_ID, PWM_INSTANCE_ID, PWM_SET_TRIGGER_DELAY_SID, PWM_E_REQUEST_FALSE);
    }
    #else
    LucHWIPType = Pwm_GpChannelConfig[LddChannelNumber].ucTimerUnitType;
    if (NULL_PTR != Pwm_GaaHwFunc[LucHWIPType]->pHWSetTriggerDelay)
    {
      /* Invoke low level driver for initializing the hardware */
      Pwm_GaaHwFunc[LucHWIPType]->pHWSetTriggerDelay(LddChannelNumber, LusTriggerDelay);
    } /* else: No action */
    #endif /* End of (PWM_MULTI_CORE_SUPPORT == STD_ON) */
  } /* else: No action */
}

#define PWM_STOP_SEC_PUBLIC_CODE_GLOBAL
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* (PWM_SET_TRIGGER_DELAY_API == STD_ON) */

/***********************************************************************************************************************
** Function Name        : Pwm_DiagReadAdConvResult
**
** Service ID           : 0xA6
**
** Description          : This service gets value of A/D converted result base on input channel.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant for different channel
**
** Input Parameters     : LddChannelNumber
**
** InOut Parameters     : none
**
** Output Parameters    : none
**
** Return parameter     : uint32
**
** Preconditions        : PWM_READ_CONV_RESLUT_API is STD_ON
**
** Global Variables     : Pwm_GpChannelConfig, Pwm_GaaHwFunc
**
** Functions invoked    : Pwm_CheckDetErrors, Pwm_HW_DIAG_DiagReadAdConvResult
**
** Registers Used       : none
**
** Reference ID         : PWM_DUD_ACT_095
***********************************************************************************************************************/
#if (PWM_READ_CONV_RESLUT_API == STD_ON)
#define PWM_START_SEC_PUBLIC_CODE_GLOBAL
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(uint32, PWM_PUBLIC_CODE) Pwm_DiagReadAdConvResult(Pwm_ChannelType LddChannelNumber)                                /* PRQA S 1503 # JV-01 */
{
  VAR(uint32, AUTOMATIC) LulAdConvResult;
  VAR(uint8, AUTOMATIC) LucHWIPType;
  #if (PWM_DEV_ERROR_DETECT == STD_ON)
  VAR(uint8, AUTOMATIC) LucDetErrFlag;
  #endif /* End of (PWM_DEV_ERROR_DETECT == STD_ON) */

  /* Initialize return value */
  LulAdConvResult = (uint32)PWM_ZERO;

  #if (PWM_DEV_ERROR_DETECT == STD_ON)
  /* Checking error */
  LucDetErrFlag = Pwm_CheckDetErrors(LddChannelNumber, PWM_READ_ADCONV_RESULT_SID);

  if (E_OK == LucDetErrFlag)
  #endif /* End of (PWM_DEV_ERROR_DETECT == STD_ON) */
  {
    LucHWIPType = Pwm_GpChannelConfig[LddChannelNumber].ucTimerUnitType;
    if (NULL_PTR != Pwm_GaaHwFunc[LucHWIPType]->pHWReadAdConvResult)
    {
      /* Invoke low level driver for initializing the hardware */
      LulAdConvResult = Pwm_GaaHwFunc[LucHWIPType]->pHWReadAdConvResult(LddChannelNumber);
    } /* else: No action */
  } /* else: No action */

  /* Return A/D conversion result value */
  return LulAdConvResult;
}

#define PWM_STOP_SEC_PUBLIC_CODE_GLOBAL
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* (PWM_READ_CONV_RESLUT_API == STD_ON) */

/***********************************************************************************************************************
** Function Name        : Pwm_DiagDisableAdTrigger
**
** Service ID           : 0xA7
**
** Description          : This service control disabling A/D Trigger
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant for different channel
**
** Input Parameters     : LddChannelNumber
**
** InOut Parameters     : none
**
** Output Parameters    : none
**
** Return parameter     : none
**
** Preconditions        : PWM_ENABLE_DISABLE_AD_TRG_API is STD_ON
**
** Global Variables     : Pwm_GpChannelConfig, Pwm_GaaHwFunc
**
** Functions invoked    : Pwm_CheckDetErrors, Pwm_HW_DIAG_DisableAdTrigger
**
** Registers Used       : none
**
** Reference ID         : PWM_DUD_ACT_096
***********************************************************************************************************************/
#if (PWM_ENABLE_DISABLE_AD_TRG_API == STD_ON)
#define PWM_START_SEC_PUBLIC_CODE_GLOBAL
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, PWM_PUBLIC_CODE) Pwm_DiagDisableAdTrigger(Pwm_ChannelType LddChannelNumber)                                  /* PRQA S 1503 # JV-01 */
{
  VAR(uint8, AUTOMATIC) LucHWIPType;
  #if (PWM_DEV_ERROR_DETECT == STD_ON)
  VAR(uint8, AUTOMATIC) LucDetErrFlag;
  /* Checking error */
  LucDetErrFlag = Pwm_CheckDetErrors(LddChannelNumber, PWM_DISABLE_AD_TRIGGER_SID);

  if (E_OK == LucDetErrFlag)
  #endif /* End of (PWM_DEV_ERROR_DETECT == STD_ON) */
  {
    LucHWIPType = Pwm_GpChannelConfig[LddChannelNumber].ucTimerUnitType;

    if (NULL_PTR != Pwm_GaaHwFunc[LucHWIPType]->pHWDisableAdTrigger)
    {
      /* Invoke low level driver for initializing the hardware */
      Pwm_GaaHwFunc[LucHWIPType]->pHWDisableAdTrigger(LddChannelNumber);
    } /* else: No action */
  } /* else: No action */
}

#define PWM_STOP_SEC_PUBLIC_CODE_GLOBAL
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* (PWM_ENABLE_DISABLE_AD_TRG_API == STD_ON) */

/***********************************************************************************************************************
** Function Name        : Pwm_DiagEnableAdTrigger
**
** Service ID           : 0xA8
**
** Description          : This service control enabling A/D Trigger
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant for different channel
**
** Input Parameters     : LddChannelNumber
**
** InOut Parameters     : none
**
** Output Parameters    : none
**
** Return parameter     : none
**
** Preconditions        : PWM_ENABLE_DISABLE_AD_TRG_API is STD_ON
**
** Global Variables     : Pwm_GpChannelConfig, Pwm_GaaHwFunc
**
** Functions invoked    : Pwm_CheckDetErrors, Pwm_HW_DIAG_EnableAdTrigger
**
** Registers Used       : none
**
** Reference ID         : PWM_DUD_ACT_097
***********************************************************************************************************************/
#if (PWM_ENABLE_DISABLE_AD_TRG_API == STD_ON)
#define PWM_START_SEC_PUBLIC_CODE_GLOBAL
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, PWM_PUBLIC_CODE) Pwm_DiagEnableAdTrigger(Pwm_ChannelType LddChannelNumber)                                   /* PRQA S 1503 # JV-01 */
{
  VAR(uint8, AUTOMATIC) LucHWIPType;
  #if (PWM_DEV_ERROR_DETECT == STD_ON)
  VAR(uint8, AUTOMATIC) LucDetErrFlag;

  /* Checking error */
  LucDetErrFlag = Pwm_CheckDetErrors(LddChannelNumber, PWM_ENABLE_AD_TRIGGER_SID);

  if (E_OK == LucDetErrFlag)
  #endif /* End of (PWM_DEV_ERROR_DETECT == STD_ON) */
  {
    LucHWIPType = Pwm_GpChannelConfig[LddChannelNumber].ucTimerUnitType;
    if (NULL_PTR != Pwm_GaaHwFunc[LucHWIPType]->pHWEnableAdTrigger)
    {
      /* Invoke low level driver for initializing the hardware */
      Pwm_GaaHwFunc[LucHWIPType]->pHWEnableAdTrigger(LddChannelNumber);
    } /* else: No action */
  } /* else: No action */
}

#define PWM_STOP_SEC_PUBLIC_CODE_GLOBAL
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* (PWM_ENABLE_DISABLE_AD_TRG_API == STD_ON) */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
