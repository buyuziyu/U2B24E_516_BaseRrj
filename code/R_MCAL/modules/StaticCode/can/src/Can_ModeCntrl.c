/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Can_ModeCntrl.c                                                                                     */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2019-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Provision of Controller Mode Control Functionality.                                                                */
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
/*              Devices:       X2x                                                                                    */
/*====================================================================================================================*/

/***********************************************************************************************************************
**                                                  Revision History                                                  **
***********************************************************************************************************************/
/*
 * 2.4.1: 30/06/2025  : Remove the SW-VERSION from header of file
 * 2.4.0: 30/05/2025  : Update Can_SetControllerMode, Can_SleepMode, Can_WakeupMode, Can_StartMode, Can_StopMode
 *                      Fixing QAC message
 * 2.3.1: 31/03/2025  : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 *                     : Add message 3006, 3416 to support QA-C version 11.6.0
 * 2.3.0: 28/02/2025  : Update SW-VERSION for RH850/Ver22.01.00/Ver22.01.00.D Final Release
 * 2.2.0: 31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 *                      As part of CANXL driver support, following changes are made:
 *                      1. Update Can_GetControllerErrorState
 * 2.1.2: 31/10/2024  : As part of U2Cx support, following changes are made:
 *                      1. Update Can_SleepMode, Can_WakeupMode
 *                      2. Fixing QAC message. Remove messages: 3006, 3416. Add messages: 2983, 2995, 2991, 3206, 2880
 *                      3. Update Can_GetControllerErrorState
 * 2.1.1: 30/08/2024  : As part of CANXL driver support, following changes are made:
 *                      1. Update Can_SetControllerMode, Can_SleepMode, Can_WakeupMode
 *                      2. Add precondition to include CanXL.h
 *                      3. Remove redundant condition in Can_SetControllerMode function
 *                      4. Update Can_SetControllerMode, Can_GetControllerErrorState
 *                      5. Update function Can_SetControllerMode to support CANXL
 * 2.0.1: 19/10/2023  : Remove message 1532, 0857, 2844, 2814
 *                      Add message 3416, 3006
 *        14/10/2023  : Change macro CAN_AR_R21_11_VERSION to CAN_AR_R22_11_VERSION
 * 2.0.0: 16/08/2023  : Update critical section to support multi core
 *        02/08/2023  : Update function Can_SetControllerMode, Can_SleepMode, Can_WakeupMode to support multi core
 *                      Change from Can_Mapping.h to Can_MemMap.h
 *                      Add QAC message
 *                      Update description of function
 *                      Add CWE Rule
 *                      Remove redundant QAC message
 *        28/06/2023  : Remove redundant QAC message
 *        31/05/2023  : Remove redundant QAC message
 * 1.5.0: 27/03/2023  : Add AUTOSAR release version information AUTOSAR R21-11
 * 1.4.4: 15/06/2022  : Add DummyRead and SYNCP
 * 1.4.3: 12/05/2022  : Add QAC message 2004
          11/05/2022  : Change COMMON_OK to CAN_COMMON_OK; COMMON_NOT_OK to CAN_COMMON_NOT_OK;
                        Common_ReturnType to Can_CommonReturnType; COMMON_STATE_STARTED to CAN_COMMON_STATE_STARTED;
                        COMMON_STATE_STOPPED to CAN_COMMON_STATE_STOPPED;
                        COMMON_STATE_SLEEP to CAN_COMMON_STATE_SLEEP;
                        Common_ControllerStateType to Can_CommonControllerStateType;
                        COMMON_STATE_WAKEUP to CAN_COMMON_STATE_WAKEUP;
                        MAX_VALID_STATE_TRANSITION to CAN_MAX_VALID_STATE_TRANSITION;
                        COMMON_IF_STATE_STARTED to CAN_COMMON_IF_STATE_STARTED;
                        COMMON_IF_STATE_STOPPED to CAN_COMMON_IF_STATE_STOPPED;
                        COMMON_IF_STATE_SLEEP to CAN_COMMON_IF_STATE_SLEEP
          10/05/2022  : Remove "else" statement don't use when no action required. 
 * 1.3.3: 13/04/2022  : Add QAC message 0857
 * 1.3.2: 30/08/2021  : Update to support multi-instance:
 *                      - Change include to Can_Mapping.h
 * 1.3.1: 02/07/2021  : Add QAC message 9.5.0
 *                      Format source code to 120 characters
 *                      Improve Violation tag (remove START/END)
 *        05/05/2021  : Update the memory section, memclass, ptrclass to change
 *                      the CAN_RSCAN prefix to CAN.
 *                      Function Can_SleepMode, update condition checks to place
 *                      the macro to the left side of equality comparisons.
 *                      Function Can_SetControllerMode, change the condition
 *                      call Can_StopMode from sub-state is tentative transition
 *                      to controller not busoff.
 *                      Function Can_StopMode, remove condition check
 *                      is not busoff before indicating mode change to CanIf.
 * 1.3.0: 23/01/2021  : Function Can_GlobalModeChange, Can_ChannelModeChange,
 *                      Can_WaitRegisterChange:
 *                      + Change memclass of CONSTP2VAR input parameter from
 *                      CAN_RSCAN_PRIVATE_CONST to CAN_RSCAN_APPL_DATA.
 * 1.2.0: 09/07/2020  : Release.
 *        28/07/2020  : Add QAC 9.3.1 comment.
 * 1.1.0: 19/06/2020  : Release.
 * 1.0.2: 16/04/2020  : As per #266253, Add CAN_CONTROLLER_OFFSET to
 *                      ControllerID when invoke to CanIf
 *        06/04/2020  : As per Redmine #263780:
 *                      + Add preprocessor check (CAN_GATEWAY_QUEUE == STD_ON)
 *                      when declare and define function Can_EnableTxBuffers.
 *                      + Add preprocessor check (CAN_GATEWAY_QUEUE == STD_ON)
 *                      when invoke Can_EnableTxBuffers in Can_StartMode.
 * 1.0.1: 27/03/2020  : Update to change bit-size passed from 16 to 8 when
 *                      access bit EIMK of EIC register.
 *        25/03/2020  : Remove redundant check (CAN_PENDING_STOP_WAIT_RESET ==
 *                      LenSubState) in Can_StopMode().
 *        04/03/2020  : Add null check for pFCLAReg.
 *        03/02/2020  : Add Can_GetControllerMode and
 *                      Can_GetControllerErrorState definition for AR 4.3.1
 *        20/01/2020  : Use common controller state macro for commonization of
 *                      AUTOSAR version 4.2.2 and 4.3.1 for the change of
 *                      controller state machine function.
 *        09/01/2020  : Support AUTOSAR version 4.3.1
 *                      - Use Can_CommonReturnType as representative of
 *                        Can_ReturnType and Std_ReturnType depending on
 *                        AUTOSAR Version
 * 1.0.0: 09/12/2019  : Initial version.
 */
/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* CAN module header file */
#include "Can.h"

#if (CAN_CANXL_SUPPORTED == STD_ON)
/* CANXL module header file */
#include "CanXL.h"
#endif

/* Included for RAM variable declarations */
#include "Can_Ram.h"

#include "Can_Irq.h"

#if (CAN_DEV_ERROR_DETECT == STD_ON)
/* Included for the declaration of Det_ReportError() */
#include "Det.h"
#endif

/* CAN Interface call-back Header File */
#if (CAN_AR_VERSION == CAN_AR_R22_11_VERSION)
#include "CanIf_Can.h"
#else
#include "CanIf_Cbk.h"
#endif

/*
 * OS Header File to have the prototype of GetCounterValue() for getting current
 * tick of OS
 */
#include "Os.h"

/* Included for RH850_SV_MODE macros */
#include "rh850_Types.h"

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define CAN_MODECNTRL_C_AR_RELEASE_MAJOR_VERSION    CAN_AR_RELEASE_MAJOR_VERSION_VALUE
#define CAN_MODECNTRL_C_AR_RELEASE_MINOR_VERSION    CAN_AR_RELEASE_MINOR_VERSION_VALUE
#define CAN_MODECNTRL_C_AR_RELEASE_REVISION_VERSION CAN_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define CAN_MODECNTRL_C_SW_MAJOR_VERSION            CAN_SW_MAJOR_VERSION_VALUE
#define CAN_MODECNTRL_C_SW_MINOR_VERSION            CAN_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (CAN_MODECNTRL_C_AR_RELEASE_MAJOR_VERSION != CAN_MODECNTRL_AR_RELEASE_MAJOR_VERSION)
  #error "Can_ModeCntrl.c : Mismatch in Release Major Version"
#endif
#if (CAN_MODECNTRL_C_AR_RELEASE_MINOR_VERSION != CAN_MODECNTRL_AR_RELEASE_MINOR_VERSION)
  #error "Can_ModeCntrl.c : Mismatch in Release Minor Version"
#endif
#if (CAN_MODECNTRL_C_AR_RELEASE_REVISION_VERSION != CAN_MODECNTRL_AR_RELEASE_REVISION_VERSION)
  #error "Can_ModeCntrl.c : Mismatch in Release Revision Version"
#endif

#if (CAN_MODECNTRL_C_SW_MAJOR_VERSION != CAN_MODECNTRL_SW_MAJOR_VERSION)
  #error "Can_ModeCntrl.c : Mismatch in Software Major Version"
#endif

#if (CAN_MODECNTRL_C_SW_MINOR_VERSION != CAN_MODECNTRL_SW_MINOR_VERSION)
  #error "Can_ModeCntrl.c : Mismatch in Software Minor Version"
#endif

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (1:1505)    : The function '%1s' is only referenced in the translation unit where it is defined.           */
/* Rule                : CERTCCM DCL19, MISRA C:2012 Rule-8.7, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : This is accepted, due to following coding rule, internal function can be defined in other C  */
/*                       source files                                                                                 */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:1006)    : [E] This in-line assembler construct is a language extension. The code has been ignored.     */
/* Rule                : MISRA-C:2012 Dir-1.1, Rule-1.2, Dir-4.2, CERTC 1.2.4 MSC14                                   */
/* JV-01 Justification : Inline assembler support for syncp instruction.                                              */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:2004)    : No concluding 'else' exists in this 'if'-'else'-'if' statement.                              */
/* Rule                : CERTCCM EXP02, MISRA C:2012 Rule-15.7, CWE Rule CWE-398, CWE-569                             */
/* JV-01 Justification : The "else"statement with empty content is removed to improve readability.                    */
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
/* Message (1:3383)    : Cannot identify wraparound guard for unsigned arithmetic expression.                         */
/* Rule                : CERTCCM INT30                                                                                */
/* JV-01 Justification : It can still result in values that are out of range for the intended use, as intuitive       */
/*                       "invariants" may not hold                                                                    */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0751)    : Casting to char pointer type.                                                                */
/* Rule                : CERTCCM EXP11, EXP39, CWE Rule CWE-188, CWE-398, CWE-468, CWE-588, CWE-465, CWE-569, CWE-737 */
/* JV-01 Justification : Using void due to specific requirement of input parameter. So, this can be skipped           */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE Rule CWE-398, CWE-569                                            */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is accepted. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:2983)    : This assignment is redundant. The value of this object is never subsequently used.           */
/* Rule                : CERTCCM MSC07, MSC13, MISRA C:2012 Rule-2.2                                                  */
/* JV-01 Justification : The value is to increment the pointer to the next item.                                      */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (6:2995)    : The result of this logical operation is always 'true'.                                       */
/* Rule                : MISRA C:2012 Rule-2.2, CWE-561, CWE-633                                                      */
/* JV-01 Justification : Depending on device configuration, there is case where the 'if' will return 'false'.         */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (6:2991)    : The value of this 'if' controlling expression is always 'true'.                              */
/* Rule                : MISRA C:2012 Rule-14.3                                                                       */
/* JV-01 Justification : Depending on device configuration, there is case where the 'if' will return 'false'.         */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3206)    : The parameter '%s' is not used in this function.                                             */
/* Rule                : CERTCCM MSC07, MSC13, MISRA C:2012 Rule-2.7, CWE Rule CWE-398, CWE-563, CWE-569              */
/* JV-01 Justification : This is done as per implementation requirement                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (6:2880)    : This code is unreachable.                                                                    */
/* Rule                : CERTCCM MSC07, MISRA C:2012 Rule-2.1                                                         */
/* JV-01 Justification : Part of the code is manually check and confirmed to be executable depending on the           */
/*                       configuration                                                                                */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3006)    : This function contains a mixture of in-line assembler statements and C statements.           */
/* Rule                : MISRA C:2012 Dir-4.3                                                                         */
/* JV-01 Justification : This is accepted, due to the implementation is following hardware specification.             */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3416)    : Logical operation performed on expression with persistent side effects.                      */
/* Rule                : CERTCCM EXP45, CWE Rule CWE-398, CWE-569, CWE-737                                            */
/* JV-01 Justification : Logical operation accesses volatile object which is a register access. All register          */
/*                       addresses are generated with volatile qualifier. There is no impact on the functionality     */
/*                       due to this conditional check for mode change.                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:2985)    : This operation is redundant. The value of the result is always that of the left-hand operand.*/
/* Rule                : CERTCCM MSC07, MSC13, MISRA C:2012 Rule-2.2                                                  */
/* JV-01 Justification : For readability, setting to registers will used redundant macros and is based on hardware    */
/*                       user's manual                                                                                */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/
#define CAN_START_SEC_PRIVATE_CODE
#include "Can_MemMap.h"

#if (CAN_RX_OBJECT == STD_ON)
STATIC FUNC(void, CAN_PRIVATE_CODE)
                            Can_ClearRxBuffers(CONST(uint8, AUTOMATIC) LucUnit, CONST(uint8, AUTOMATIC) LucCtrlIndex);
#endif

#if ((CAN_TX_COMFIFO == STD_ON) || (CAN_GATEWAY_COMFIFO == STD_ON) || (CAN_TX_QUEUE == STD_ON) || \
     (CAN_GATEWAY_QUEUE == STD_ON))
STATIC FUNC(void, CAN_PRIVATE_CODE)
                            Can_EnableTxBuffers(CONST(uint8, AUTOMATIC) LucUnit, CONST(uint8, AUTOMATIC) LucCtrlIndex);
#endif

#define CAN_STOP_SEC_PRIVATE_CODE
#include "Can_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Can_SetControllerMode
**
** Service ID            : 0x03
**
** Description           : This function calls the corresponding CAN Driver
**                         service for changing the CAN Controller Mode. It
**                         initiates a transition to the requested CAN
**                         Controller Mode.
**
** Sync/Async            : Asynchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : Controller : Controller ID
**                         Transition : Target state
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : Can_CommonReturnType
**
** Preconditions         : The CAN Driver must be initialized and during the
**                         function executes the Wake-up interrupt must be
**                         disabled so that the Wake-up status can be checked
**                         inside this function.
**
** Global Variables Used : Can_GaaCtrlState, Can_GpPCController
**
** Function(s) invoked   : Can_CommonDetCheck, Det_ReportError, Can_SleepMode,
**                         Can_StartMode, Can_StopMode, Can_WakeupMode,
**                         CanXL_StartMode, CanXL_StopMode
**
** Registers Used        : None
**
** Reference ID          : CAN_DUD_ACT_003
** Reference ID          : CAN_DUD_ACT_003_CRT001, CAN_DUD_ACT_003_CRT002,
** Reference ID          : CAN_DUD_ACT_003_CRT003, CAN_DUD_ACT_003_CRT004,
** Reference ID          : CAN_DUD_ACT_003_ERR001, CAN_DUD_ACT_003_ERR002,
** Reference ID          : CAN_DUD_ACT_003_GBL001, CAN_DUD_ACT_003_GBL002,
** Reference ID          : CAN_DUD_ACT_003_GBL003, CAN_DUD_ACT_003_REG001
***********************************************************************************************************************/
#define CAN_START_SEC_PUBLIC_CODE
#include "Can_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(Can_CommonReturnType, CAN_PUBLIC_CODE)
Can_SetControllerMode                                                                                                   /* PRQA S 1503, 3006 # JV-01, JV-01 */
(VAR(uint8, CAN_APPL_DATA) Controller, VAR(Can_CommonControllerStateType, CAN_APPL_DATA) Transition)
{
  VAR(Can_CommonControllerStateType, AUTOMATIC) LenCurrentMode;
  VAR(Can_CommonReturnType, AUTOMATIC) LenReturnValue;
  #if (CAN_WAKEUP_SUPPORT == STD_ON)
  P2CONST(Can_ControllerPCConfigType, AUTOMATIC, CAN_CONFIG_DATA) LpPCController;
  #endif

  /* Get the current mode of the Controller */
  LenCurrentMode = Can_GaaCtrlState[Controller].enMode;

  #if (CAN_DEV_ERROR_DETECT == STD_ON)
  LenReturnValue = Can_CommonDetCheck(CAN_SET_MODECNTRL_SID, Controller);
  if (CAN_COMMON_OK != LenReturnValue)
  {
    /* Return LenReturnValue as is */
  }
  /* Report to DET, if the transition is out of range */
  else if ((uint32)CAN_MAX_VALID_STATE_TRANSITION < (uint32)Transition)
  {
    (void)Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_SET_MODECNTRL_SID, CAN_E_TRANSITION);
    LenReturnValue = CAN_COMMON_NOT_OK;
  }
  /* Report to DET, if the transition is not valid */
  else if (
      #if (CAN_AR_VERSION == CAN_AR_422_VERSION)
      ((CAN_COMMON_STATE_STARTED == LenCurrentMode) && (CAN_COMMON_STATE_WAKEUP == Transition)) ||
      ((CAN_COMMON_STATE_SLEEP == LenCurrentMode) && (CAN_COMMON_STATE_STOPPED == Transition)) ||
      #endif
      ((CAN_COMMON_STATE_SLEEP == LenCurrentMode) && (CAN_COMMON_STATE_STARTED == Transition)) ||
      ((CAN_COMMON_STATE_STARTED == LenCurrentMode) && (CAN_COMMON_STATE_SLEEP == Transition)))
  {
    (void)Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_SET_MODECNTRL_SID, CAN_E_TRANSITION);
    LenReturnValue = CAN_COMMON_NOT_OK;
  }
  else
  #endif /* #if (CAN_DEV_ERROR_DETECT == STD_ON) */
  {
    LenReturnValue = CAN_COMMON_OK;
    /* If Transition is to the Same State */
    if (LenCurrentMode == Transition)
    {
      /* Indicate mode change to CanIf, if Transition is to the Same State */
      if (CAN_COMMON_STATE_STARTED == Transition)
      {
        /* Indicate mode change to CanIf */
        CanIf_ControllerModeIndication((uint8)(Controller + CAN_CONTROLLER_OFFSET), CAN_COMMON_IF_STATE_STARTED);       /* PRQA S 3383, 2985 # JV-01, JV-01 */
      }
      else if (CAN_COMMON_STATE_STOPPED == Transition)
      {
        /* Indicate mode change to CanIf */
        CanIf_ControllerModeIndication((uint8)(Controller + CAN_CONTROLLER_OFFSET), CAN_COMMON_IF_STATE_STOPPED);       /* PRQA S 3383, 2985 # JV-01, JV-01 */
      }
      else if (CAN_COMMON_STATE_SLEEP == Transition)                                                                    /* PRQA S 2004 # JV-01 */
      {
        /* Indicate mode change to CanIf */
        CanIf_ControllerModeIndication((uint8)(Controller + CAN_CONTROLLER_OFFSET), CAN_COMMON_IF_STATE_SLEEP);         /* PRQA S 3383, 2985 # JV-01, JV-01 */
      } /* else No action required */
    }
    else
    { 
      /* Invoke corresponding function based on the transition */
      switch (Transition)
      {
      case CAN_COMMON_STATE_STARTED:
        #if (CAN_CANXL_SUPPORTED == STD_ON)
        if(CAN_XL == Can_GpPCController[Controller].enControllerType)                                                   /* PRQA S 3416 # JV-01 */
        {
          CanXL_StartMode(Controller);
        }
        else
        #endif
        {
          Can_StartMode(Controller);
        }
        break;
      case CAN_COMMON_STATE_STOPPED:
        #if ((CAN_AR_VERSION == CAN_AR_431_VERSION) || (CAN_AR_VERSION == CAN_AR_R22_11_VERSION))
        if (CAN_COMMON_STATE_STARTED == LenCurrentMode)
        #endif
        {
          /*
          * The transition START to STOP is done by the following triggers:
          *  - Can_SetControllerMode(CAN_COMMON_STATE_STOPPED)
          *  - Busoff
          * To avoid the state transition is done twice by both of triggers,
          * the exclusive control is required.
          */
          CAN_ENTER_CRITICAL_SECTION(CAN_RAM_DATA_PROTECTION);
          if (CAN_NO_PENDING_TRANSITION == Can_GaaCtrlState[Controller].enSubState)
          {
            /* Mark subState as "TENTATIVE" to block the transition by ISR */
            Can_GaaCtrlState[Controller].enSubState = CAN_TENTATIVE_TRANSITION;
          } /* else No action required */
          CAN_EXIT_CRITICAL_SECTION(CAN_RAM_DATA_PROTECTION);
          if (CAN_FALSE == Can_GaaCtrlState[Controller].blBusOff)
          {
            /* Start the transition to STOP state */
            #if (CAN_CANXL_SUPPORTED == STD_ON)
            if(CAN_XL == Can_GpPCController[Controller].enControllerType)                                               /* PRQA S 3416 # JV-01 */
            {
              CanXL_StopMode(Controller);
            }
            else
            #endif
            {
              Can_StopMode(Controller);
            }
          } /* else No action required */
        }
        #if (CAN_AR_VERSION == CAN_AR_422_VERSION)
          break;
        case CAN_COMMON_STATE_WAKEUP:
        #elif ((CAN_AR_VERSION == CAN_AR_431_VERSION) || (CAN_AR_VERSION == CAN_AR_R22_11_VERSION))
        else
        #endif
        {
          #if (CAN_WAKEUP_SUPPORT == STD_ON)
          LpPCController = &Can_GpPCController[Controller];
          /*
          * The transition SLEEP to STOP is done by the following triggers:
          *  - Can_SetControllerMode(CAN_COMMON_STATE_WAKEUP) (AR422)
          *  - Can_SetControllerMode(CAN_COMMON_STATE_STOPPED) (AR431)
          *  - Wake-up trigger by the HW
          * To avoid the state transition is done twice by both of triggers,
          * the exclusive control is required.
          * This critical section must be INTERRUPT_CONTROL_PROTECTION,
          * because EIC register is manipulated and the exclusive control is
          * also required against Can_EnableControllerInterrupts.
          */
          CAN_ENTER_CRITICAL_SECTION(CAN_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
          if ((CAN_COMMON_STATE_SLEEP == Can_GaaCtrlState[Controller].enMode) &&
              (CAN_NO_PENDING_TRANSITION == Can_GaaCtrlState[Controller].enSubState))
          {
            /* Mark subState as "TENTATIVE" to block the transition by ISR */
            Can_GaaCtrlState[Controller].enSubState = CAN_TENTATIVE_TRANSITION;
            /* Wakeup is triggered by SW */
            Can_GaaCtrlState[Controller].blWakeupByHW = CAN_FALSE;
            /* Disable Wake-up ISR */
            if (NULL_PTR != LpPCController->pICWakeup)
            {
              RH850_SV_MODE_ICR_OR(8, LpPCController->pICWakeup, CAN_EIC_EIMK_MASK);                                    /* PRQA S 0751 # JV-01 */
              /* DummyRead & SYNCP */
              RH850_SV_MODE_REG_READ_ONLY(16, LpPCController->pICWakeup);
              EXECUTE_SYNCP();                                                                                          /* PRQA S 1006 # JV-01 */
            } /* else No action required */
          } /* else No action required. The transition to CAN_COMMON_STATE_STOPPED by ISR has been started */
          CAN_EXIT_CRITICAL_SECTION(CAN_INTERRUPT_CONTROL_PROTECTION_GLOBAL);

          if (CAN_TENTATIVE_TRANSITION != Can_GaaCtrlState[Controller].enSubState)
          {
            /* The state transition has been started by the ISR.
              Return CAN_COMMON_NOT_OK according to SWS_Can_00048. */
            LenReturnValue = CAN_COMMON_NOT_OK;
          }
          else
          #endif /* (CAN_WAKEUP_SUPPORT == STD_ON) */
          {
            /* Start the transition to STOP sate */
            Can_WakeupMode(Controller);
          }
        }
        break;
        default: /* CAN_COMMON_STATE_SLEEP */
        Can_SleepMode(Controller);
        break;
      }
    }
  }
  /* Return LenCanReturnType */
  return (LenReturnValue);
}
#define CAN_STOP_SEC_PUBLIC_CODE
#include "Can_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Can_GetControllerErrorState
**
** Service ID            : 0x11
**
** Description           : This function calls the corresponding CAN Driver
**                         service for getting the CAN Controller error state.
**                         It returns the error state of corresponding inputted
**                         ID of CAN Controller.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant for the same ControllerId
**
** Input Parameters      : ControllerID : Controller ID
**
** InOut Parameters      : None
**
** Output Parameters     : ErrorStatePtr : Pointer to the location storing
**                         the current error state of Controller
**
** Return parameter      : Std_ReturnType(E_OK/E_NOT_OK)
**
** Preconditions         : CanSetBaudrateApi is configured as true.
**                         CAN Driver must be initialized.
**
** Global Variables Used : Can_GpPCController, Can_GaaRegs, Can_GpConfig, CanXL_GaaCtrlStat
**
** Function(s) invoked   : Can_CommonDetCheck, Det_ReportError
**
** Registers Used        : CFDCmSTS
**
** Reference ID          : CAN_DUD_ACT_016
** Reference ID          : CAN_DUD_ACT_016_ERR001, CAN_DUD_ACT_016_GBL001,
** Reference ID          : CAN_DUD_ACT_016_GBL002, CAN_DUD_ACT_016_GBL003
***********************************************************************************************************************/
#if ((CAN_AR_VERSION == CAN_AR_431_VERSION) || (CAN_AR_VERSION == CAN_AR_R22_11_VERSION))
#define CAN_START_SEC_PUBLIC_CODE
#include "Can_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, CAN_PUBLIC_CODE) Can_GetControllerErrorState(VAR(uint8, CAN_APPL_DATA) ControllerId,               /* PRQA S 1503 # JV-01 */
                                                    P2VAR(Can_ErrorStateType, AUTOMATIC, CAN_APPL_DATA) ErrorStatePtr)  /* PRQA S 3432 # JV-01 */
{
  VAR(Std_ReturnType, AUTOMATIC) LenReturnValue;
  P2CONST(Can_ControllerPCConfigType, AUTOMATIC, CAN_CONFIG_DATA) LpPCController;
  #if (CAN_RSCANFD_CONFIGURED == STD_ON)
  VAR(uint8, AUTOMATIC) LucUnit;
  #endif
  VAR(uint8, AUTOMATIC) LucCh;
  #if (CAN_CANXL_SUPPORTED == STD_ON)
  VAR(uint8, AUTOMATIC) LucCtrlInfoIndex;
  #endif /* (CAN_CANXL_SUPPORTED == STD_ON) */

  #if (CAN_DEV_ERROR_DETECT == STD_ON)
  LenReturnValue = Can_CommonDetCheck(CAN_GET_ERRSTATECNTRL_SID, ControllerId);
  if (E_OK != LenReturnValue)
  {
    /* Return LenReturnValue as it is */
  }
  /* Check if parameter passed is equal to Null pointer */
  else if (NULL_PTR == ErrorStatePtr)
  {
    /* Report to DET  */
    (void)Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_GET_ERRSTATECNTRL_SID, CAN_E_PARAM_POINTER);
    LenReturnValue = E_NOT_OK;
  }
  else
  #endif /* #if (CAN_DEV_ERROR_DETECT == STD_ON) */
  {
    LenReturnValue = E_OK;
    LpPCController = &Can_GpPCController[ControllerId];
    #if (CAN_RSCANFD_CONFIGURED == STD_ON)
    LucUnit = LpPCController->ucUnit;
    #endif
    LucCh = LpPCController->ucCh;
    #if (CAN_CANXL_SUPPORTED == STD_ON)
    if(CAN_FD == LpPCController->enControllerType)
    #endif
    {
      #if (CAN_RSCANFD_CONFIGURED == STD_ON)
      /* Get the current error state of the Controller */
      if (0UL != (Can_GaaRegs[LucUnit].pCmn->aaChReg[LucCh].ulSTS & CAN_RSCAN_BOSTS))
      {
        *ErrorStatePtr = CAN_ERRORSTATE_BUSOFF;
      }
      else if (0UL != (Can_GaaRegs[LucUnit].pCmn->aaChReg[LucCh].ulSTS & CAN_RSCAN_EPSTS))
      {
        *ErrorStatePtr = CAN_ERRORSTATE_PASSIVE;
      }
      else
      {
        *ErrorStatePtr = CAN_ERRORSTATE_ACTIVE;
      }
      #endif
    }
    #if (CAN_CANXL_SUPPORTED == STD_ON)
    else
    {
      LucCtrlInfoIndex = Can_GpConfig->pCanXLSecondPhysicalControllerToIndex[LucCh];
      if (CAN_TRUE == CanXL_GaaCtrlStat[LucCtrlInfoIndex].blErrorSignaling)
      {
        /* Get the current error state of the Controller */
        if (0UL != (CanXL_GaaRegs[LucCtrlInfoIndex].pPRT->ulSTAT & CAN_CANXL_BOEF))
        {
          *ErrorStatePtr = CAN_ERRORSTATE_BUSOFF;
        }
        else if (0UL != (CanXL_GaaRegs[LucCtrlInfoIndex].pPRT->ulSTAT & CAN_CANXL_EPEF))
        {
          *ErrorStatePtr = CAN_ERRORSTATE_PASSIVE;
        }
        else
        {
          *ErrorStatePtr = CAN_ERRORSTATE_ACTIVE;
        }
      }
      else
      {
        /* Get the current error state of the Controller */
        if (CAN_TRUE == Can_GaaCtrlState[ControllerId].blBusOff)
        {
          *ErrorStatePtr = CAN_ERRORSTATE_BUSOFF;
        }
        else if ((CanXL_GaaCtrlStat[LucCtrlInfoIndex].ulTEC >= 128UL) || 
                (CanXL_GaaCtrlStat[LucCtrlInfoIndex].ulREC >= 128UL))
        {
          *ErrorStatePtr = CAN_ERRORSTATE_PASSIVE;
        }
        else
        {
          *ErrorStatePtr = CAN_ERRORSTATE_ACTIVE;
        }
      }
    }
    #endif
  }
  /* Return LenReturnValue */
  return (LenReturnValue);
}
#define CAN_STOP_SEC_PUBLIC_CODE
#include "Can_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif

/***********************************************************************************************************************
** Function Name         : Can_GetControllerMode
**
** Service ID            : 0x12
**
** Description           : This function calls the corresponding CAN Driver
**                         service for getting the CAN Controller Mode. It
**                         returns the state of corresponding inputted ID of
**                         CAN Controller.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : Controller : Controller ID
**
** InOut Parameters      : None
**
** Output Parameters     : ControllerModePtr : Pointer to the location storing
**                         the current mode of Controller
**
** Return parameter      : Std_ReturnType(E_OK/E_NOT_OK)
**
** Preconditions         : The CAN Driver must be initialized.
**
** Global Variables Used : Can_GaaCtrlState
**
** Function(s) invoked   : Can_CommonDetCheck, Det_ReportError
**
** Registers Used        : None
**
** Reference ID          : CAN_DUD_ACT_017
** Reference ID          : CAN_DUD_ACT_017_ERR001
***********************************************************************************************************************/
#if ((CAN_AR_VERSION == CAN_AR_431_VERSION) || (CAN_AR_VERSION == CAN_AR_R22_11_VERSION))
#define CAN_START_SEC_PUBLIC_CODE
#include "Can_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, CAN_PUBLIC_CODE) Can_GetControllerMode(VAR(uint8, CAN_APPL_DATA) Controller,                       /* PRQA S 1503 # JV-01 */
                                            P2VAR(Can_ControllerStateType, AUTOMATIC, CAN_APPL_DATA) ControllerModePtr) /* PRQA S 3432 # JV-01 */
{
  VAR(Std_ReturnType, AUTOMATIC) LenReturnValue;

  #if (CAN_DEV_ERROR_DETECT == STD_ON)
  LenReturnValue = Can_CommonDetCheck(CAN_GET_MODECNTRL_SID, Controller);
  if (E_OK != LenReturnValue)
  {
    /* Return LenReturnValue as it is */
  }
  /* Check if parameter passed is equal to Null pointer */
  else if (NULL_PTR == ControllerModePtr)
  {
    /* Report to DET  */
    (void)Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_GET_MODECNTRL_SID, CAN_E_PARAM_POINTER);
    LenReturnValue = E_NOT_OK;
  }
  else
  #endif /* #if (CAN_DEV_ERROR_DETECT == STD_ON) */
  {
    LenReturnValue = E_OK;
    /* Get the current mode of the Controller */
    *ControllerModePtr = Can_GaaCtrlState[Controller].enMode;
  }
  /* Return LenReturnValue */
  return (LenReturnValue);
}
#define CAN_STOP_SEC_PUBLIC_CODE
#include "Can_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif

#define CAN_START_SEC_PRIVATE_CODE
#include "Can_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Can_SleepMode
**
** Service ID            : Not Applicable
**
** Description           : This function initiates a transition to sleep mode.
**
** Sync/Async            : None
**
** Reentrancy            : Reentrant from Can_SetControllerMode and
**                         Can_MainFunction_Mode.
**                         Non-reentrant from same API.
**
** Input Parameters      : LucController
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : The availability of the index and state transition
**                         must be guaranteed by the upper layer.
**
** Global Variables Used : Can_GpPCController, Can_GaaCtrlState,
**                         Can_GaaRegs, Can_GaaActiveControllers,
**                         Can_GaaGlobalStateTransition
**
** Function(s) invoked   : Can_GlobalModeChange, Can_ChannelModeChange,
**                         CanIf_ControllerModeIndication
**
** Registers Used        : (CFD)GSTS, (CFD)CmSTS
**
** Reference ID          : CAN_DUD_ACT_035
** Reference ID          : CAN_DUD_ACT_035_CRT001, CAN_DUD_ACT_035_CRT002,
** Reference ID          : CAN_DUD_ACT_035_CRT003, CAN_DUD_ACT_035_CRT004,
** Reference ID          : CAN_DUD_ACT_035_GBL001, CAN_DUD_ACT_035_GBL002,
** Reference ID          : CAN_DUD_ACT_035_GBL003, CAN_DUD_ACT_035_GBL005,
** Reference ID          : CAN_DUD_ACT_035_GBL006, CAN_DUD_ACT_035_GBL007,
** Reference ID          : CAN_DUD_ACT_035_GBL008, CAN_DUD_ACT_035_GBL009,
** Reference ID          : CAN_DUD_ACT_035_REG001, CAN_DUD_ACT_035_REG002
** Reference ID          : CAN_DUD_ACT_035_REG003, CAN_DUD_ACT_035_CRT005
** Reference ID          : CAN_DUD_ACT_035_CRT006 
***********************************************************************************************************************/
FUNC(void, CAN_PRIVATE_CODE) Can_SleepMode(CONST(uint8, AUTOMATIC) LucCtrlIndex)                                        /* PRQA S 1505, 3006 # JV-01, JV-01 */
{
  #if (CAN_WAKEUP_SUPPORT == STD_ON)
  P2CONST(Can_ControllerPCConfigType, AUTOMATIC, CAN_CONFIG_DATA) LpPCController;
  VAR(Std_ReturnType, AUTOMATIC) LucResult;
  #if (CAN_RSCANFD_CONFIGURED == STD_ON)
  VAR(uint32, AUTOMATIC) LulTimeoutDuration;
  VAR(uint8, AUTOMATIC) LucUnit;
  VAR(uint8, AUTOMATIC) LucCh;
  VAR(boolean, AUTOMATIC) LblGlobalTransitionRequired;
  #endif
  VAR(Can_SubStatusType, AUTOMATIC) LenSubState;

  LpPCController = &Can_GpPCController[LucCtrlIndex];
  #if (CAN_RSCANFD_CONFIGURED == STD_ON)
  LulTimeoutDuration = CAN_TIMEOUT_COUNT;
  LucUnit = LpPCController->ucUnit;
  LucCh = LpPCController->ucCh;
  #endif

  LenSubState = Can_GaaCtrlState[LucCtrlIndex].enSubState;                                                              /* PRQA S 2983 # JV-01 */
  LucResult = E_OK;

  /*
   * STEP 1:
   * Start to change to CHANNEL_STOP.
   * At this time, global state transition is never on-going.
   * Because:
   * - While GLOBAL_STOP -> GLOBAL_OPERATION is on-going, it means that all
   *   Controllers are CAN_COMMON_STATE_SLEEP or during transition to
   *   CAN_COMMON_STATE_STOPPED.
   * - While GLOBAL_OPERATION -> GLOBAL_STOP is on-going, it means that one
   *   Controller is during transition to CAN_COMMON_STATE_SLEEP and other
   *   Controllers are CAN_COMMON_STATE_SLEEP.
   * - When Can_SetControllerMode(CAN_COMMON_STATE_SLEEP) is invoked for a
   *   Controller which is CAN_COMMON_STATE_SLEEP already, Can_SetControllerMode
   *   returns immediately.
   * - When Can_SetControllerMode(CAN_COMMON_STATE_SLEEP) is invoked for a
   *   Controller which is during state transition, it causes the DET error.
   */
  #if (CAN_CANXL_SUPPORTED == STD_ON)
  if(CAN_XL != LpPCController->enControllerType)
  #endif
  {
    #if (CAN_RSCANFD_CONFIGURED == STD_ON)
    if (CAN_NO_PENDING_TRANSITION == LenSubState)
    {
      LenSubState = CAN_PENDING_SLEEP_WAIT_STOP;
      LucResult = Can_ChannelModeChange(LucUnit, LucCh, CAN_RSCAN_CSLPR | CAN_RSCAN_CHMDC_RESET, &LulTimeoutDuration);
      /* Continue to STEP 3 */
    }
    /*
    * STEP 2:
    * If necessary, wait for CHANNEL_STOP.
    */
    else if ((CAN_PENDING_SLEEP_WAIT_STOP == LenSubState) &&                                                            /* PRQA S 2004 # JV-01 */
            (0UL == (Can_GaaRegs[LucUnit].pCmn->aaChReg[LucCh].ulSTS & CAN_RSCAN_CSLPSTS)))
    {
      /* Continue to pending */
      LucResult = E_NOT_OK;
    } /* else No action required */
    /*
    * STEP 3:
    * If all Controllers slept, change global state to GLOBAL_RESET.
    */
    
    if ((E_OK == LucResult) && (CAN_PENDING_SLEEP_WAIT_STOP == LenSubState))
    {
    /* Critical section is required in case entering to sleep and waking up occur on different channels at same time */
      CAN_ENTER_CRITICAL_SECTION(CAN_RAM_DATA_PROTECTION_GLOBAL);
      /* Clear active bit of this Controller */
      Can_GaaActiveControllers[LucUnit] &= ~(1UL << LucCtrlIndex);
      if (0UL == Can_GaaActiveControllers[LucUnit])
      {
        /* If all Controllers have been entered to CANNEL_STOP, start the global state change:
        GLOBAL_OPERATION -> GLOBAL_STOP */
        Can_GaaGlobalStateTransition[LucUnit] = CAN_TRUE;
        LblGlobalTransitionRequired = CAN_TRUE;
      }
      else
      {
        LblGlobalTransitionRequired = CAN_FALSE;
      }
      CAN_EXIT_CRITICAL_SECTION(CAN_RAM_DATA_PROTECTION_GLOBAL);
      /* If all controllers stopped, enter GLOBAL_STOP mode */
      if (CAN_TRUE == LblGlobalTransitionRequired)
      {
        /* At first, change to GLOBAL_RESET mode. This takes 2 CAN bits. */
        LenSubState = CAN_PENDING_SLEEP_WAIT_GLOBALRESET;
        LucResult = Can_GlobalModeChange(LucUnit, CAN_RSCAN_GMDC_RESET, &LulTimeoutDuration);
        /* Continue to STEP 5 */
      } /* else No action required. Continue to STEP 7 */
    }
    /*
    * STEP 4:
    * If necessary, wait for GLOBAL_RESET.
    */
    else if ((E_OK == LucResult) && (CAN_PENDING_SLEEP_WAIT_GLOBALRESET == LenSubState) &&                              /* PRQA S 2004 # JV-01 */
            (CAN_RSCAN_GRSTSTS != (Can_GaaRegs[LucUnit].pCmn->ulGSTS & CAN_RSCAN_GSTSMASK)))
    {
      /* Continue to pending */
      LucResult = E_NOT_OK;
    } /* else No action required */

    /*
    * STEP 5:
    * If necessary, enter GLOBAL_STOP.
    */
    if ((E_OK == LucResult) && (CAN_PENDING_SLEEP_WAIT_GLOBALRESET == LenSubState))
    {
      LenSubState = CAN_PENDING_SLEEP_WAIT_GLOBALSTOP;
      LucResult = Can_GlobalModeChange(LucUnit, CAN_RSCAN_GSLPR | CAN_RSCAN_GMDC_RESET, &LulTimeoutDuration);
      /* Continue to STEP 7 */
    }
    /*
    * STEP 6:
    * If necessary, wait for GLOBAL_STOP.
    */
    else if ((E_OK == LucResult) && (CAN_PENDING_SLEEP_WAIT_GLOBALSTOP == LenSubState) &&                               /* PRQA S 2004 # JV-01 */
            (0UL != (Can_GaaRegs[LucUnit].pCmn->ulGSTS & CAN_RSCAN_GSLPSTS)))
    {
      /* Continue to pending */
      LucResult = E_NOT_OK;
    } /* else No action required */
    #endif
  }
  /*
   * STEP 7:
   * Finish transition.
   */
  if (E_OK == LucResult)                                                                                                /* PRQA S 2995, 2991 # JV-01, JV-01 */
  {
    #if (CAN_RSCANFD_CONFIGURED == STD_ON)
    #if (CAN_CANXL_SUPPORTED == STD_ON)
    if (CAN_XL != LpPCController->enControllerType)
    #endif
    {
      /* Clear Global transition on-going flag */
      if (CAN_PENDING_SLEEP_WAIT_GLOBALSTOP == LenSubState)
      {
        /* No critical section is required because this can be done atomically */
        Can_GaaGlobalStateTransition[LucUnit] = CAN_FALSE;
      } /* else No action required */
    }
    #endif
    /* Critical section is required to avoid confliction with
       Can_DisableControllerInterrupts */
    CAN_ENTER_CRITICAL_SECTION(CAN_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
    Can_GaaCtrlState[LucCtrlIndex].enMode = CAN_COMMON_STATE_SLEEP;
    Can_GaaCtrlState[LucCtrlIndex].enSubState = CAN_NO_PENDING_TRANSITION;
    if (NULL_PTR != LpPCController->pICWakeup)
    {
      /* Enable wakeup interrupt */
      if ((0U != (LpPCController->ucIntEnable & CAN_CHECK_INT_WAKEUP)) &&
          (0UL == Can_GaaCtrlState[LucCtrlIndex].ulIntCount))
      {
        /* Clear EIMK and EIRF */
        RH850_SV_MODE_ICR_AND(16, LpPCController->pICWakeup,
                              (uint16)(~(CAN_EIC_EIRF_MASK | (uint16)CAN_EIC_EIMK_MASK)));
      }
      else
      {
        /* If the interrupt is disabled, clear EIRF only */
        RH850_SV_MODE_ICR_AND(16, LpPCController->pICWakeup, (uint16)(~CAN_EIC_EIRF_MASK));
      }
        /* DummyRead & SYNCP */
        RH850_SV_MODE_REG_READ_ONLY(16, LpPCController->pICWakeup);
        EXECUTE_SYNCP();                                                                                                /* PRQA S 1006 # JV-01 */
      #ifdef CAN_FILTER_CONTROL_SUPPORT
      if (NULL_PTR != LpPCController->pFCLAReg)
      {
        /* Setting the filter control register for falling edge detection */
        *(LpPCController->pFCLAReg) = CAN_RSCAN_FCLA_FALLING_EDGE;
      } /* else No action required */
      #endif
    } /* else No action required. Wakeup is not available on this Controller, nothing to do */
    CAN_EXIT_CRITICAL_SECTION(CAN_INTERRUPT_CONTROL_PROTECTION_GLOBAL);

    /* Notify CanIf of completion of transition to SLEEP state */
    CanIf_ControllerModeIndication((uint8)(LucCtrlIndex + CAN_CONTROLLER_OFFSET), CAN_COMMON_IF_STATE_SLEEP);           /* PRQA S 3383, 2985 # JV-01, JV-01 */
  }
  else
  {
    /* If timeout occurred, update the pending status.
    This should be done at the end of this function once to avoid reentrant
    call from Can_SetControllerMode and Can_MainFunction_Mode. */
    Can_GaaCtrlState[LucCtrlIndex].enSubState = LenSubState;                                                            /* PRQA S 2880 # JV-01 */
  }
  #else /* (CAN_WAKEUP_SUPPORT == STD_ON) */
  /* Set the Controller to sleep mode */
  Can_GaaCtrlState[LucCtrlIndex].enMode = CAN_COMMON_STATE_SLEEP;
  Can_GaaCtrlState[LucCtrlIndex].enSubState = CAN_NO_PENDING_TRANSITION;
  /* Indicate mode change to CanIf */
  CanIf_ControllerModeIndication((uint8)(LucCtrlIndex + CAN_CONTROLLER_OFFSET), CAN_COMMON_IF_STATE_SLEEP);             /* PRQA S 3383, 2985 # JV-01, JV-01 */
  #endif /* (CAN_WAKEUP_SUPPORT == STD_ON) */
}

/***********************************************************************************************************************
** Function Name         : Can_WakeupMode
**
** Service ID            : Not Applicable
**
** Description           : This function initiates the transition to wakeup from
**                         sleep Mode.
**
** Sync/Async            : None
**
** Reentrancy            : Reentrant from Can_SetControllerMode and
**                         Can_MainFunction_Mode.
**                         Non-reentrant from same API.
**
** Input Parameters      : LucCtrlIndex      : Index of a Controller
**                         LulTimeoutDuration : Timer count which is allowed
**                         to be spent in this function.
**                         When this function is invoked from ISRs,
**                         this parameter must be zero.
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : The availability of the index and state transition
**                         must beguaranteed by the upper layer.
**
** Global Variables Used : Can_GpPCController, Can_GaaCtrlState,
**                         Can_GaaGlobalStateTransition,
**                         Can_GaaActiveControllers, Can_GaaRegs
**
** Function(s) invoked   : Can_GlobalModeChange, Can_ChannelModeChange,
**                         CanIf_ControllerModeIndication
**
** Registers Used        : (CFD)GSTS, (CFD)CmSTS
**
** Reference ID          : CAN_DUD_ACT_036
** Reference ID          : CAN_DUD_ACT_036_CRT001, CAN_DUD_ACT_036_CRT002,
** Reference ID          : CAN_DUD_ACT_036_GBL001, CAN_DUD_ACT_036_GBL002,
** Reference ID          : CAN_DUD_ACT_036_GBL003, CAN_DUD_ACT_036_GBL004,
** Reference ID          : CAN_DUD_ACT_036_GBL005, CAN_DUD_ACT_036_GBL006,
** Reference ID          : CAN_DUD_ACT_036_GBL007, CAN_DUD_ACT_036_GBL008
***********************************************************************************************************************/
FUNC(void, CAN_PRIVATE_CODE) Can_WakeupMode(CONST(uint8, AUTOMATIC) LucCtrlIndex)                                       /* PRQA S 1505 # JV-01 */
{
  #if (CAN_WAKEUP_SUPPORT == STD_ON)
  P2CONST(Can_ControllerPCConfigType, AUTOMATIC, CAN_CONFIG_DATA) LpPCController;
  VAR(Std_ReturnType, AUTOMATIC) LucResult;
  #if (CAN_RSCANFD_CONFIGURED == STD_ON)
  VAR(uint32, AUTOMATIC) LulTimeoutDuration;
  VAR(uint8, AUTOMATIC) LucUnit;
  VAR(uint8, AUTOMATIC) LucCh;
  VAR(boolean, AUTOMATIC) LblGlobalTransitionRequired;
  #endif
  VAR(Can_SubStatusType, AUTOMATIC) LenSubState;

  LpPCController = &Can_GpPCController[LucCtrlIndex];
  #if (CAN_RSCANFD_CONFIGURED == STD_ON)
  LucUnit = LpPCController->ucUnit;
  LucCh = LpPCController->ucCh;
  LulTimeoutDuration = CAN_TIMEOUT_COUNT;
  LblGlobalTransitionRequired = CAN_FALSE;
  #endif

  LucResult = E_OK;
  LenSubState = Can_GaaCtrlState[LucCtrlIndex].enSubState;                                                              /* PRQA S 2983 # JV-01 */

  /*
   * STEP 1:
   * If Global state transition is on-going,
   * hold to start the state transition of a Controller.
   * If wakeup was invoked from Can_SetControllerMode,
   * the first subState is CAN_TENTATIVE_TRANSITION.
   * If wakeup was invoked from the wakeup interrupt,
   * the first subState is CAN_PENDING_WAKEUP_REQUESTED.
   */
  #if (CAN_CANXL_SUPPORTED == STD_ON)
  if(CAN_XL != LpPCController->enControllerType)
  #endif
  {
    #if (CAN_RSCANFD_CONFIGURED == STD_ON)
    if ((CAN_TENTATIVE_TRANSITION == LenSubState) || (CAN_PENDING_WAKEUP_REQUESTED == LenSubState) ||
        (CAN_PENDING_WAKEUP_WAIT_GLOBALCHANGE == LenSubState))
    {
      /* Critical section is required in case entering to sleep and
        waking up occur on different channels at same time */
      CAN_ENTER_CRITICAL_SECTION(CAN_RAM_DATA_PROTECTION_GLOBAL);
      if (CAN_TRUE == Can_GaaGlobalStateTransition[LucUnit])
      {
        /* If any global state transition is on-going now on this RS-CAN unit,
          hold to start the state transition of Controllers */
        LenSubState = CAN_PENDING_WAKEUP_WAIT_GLOBALCHANGE;
        LucResult = E_NOT_OK;
      }
      else
      {
        if (0UL == Can_GaaActiveControllers[LucUnit])
        {
          /* If this is the first wake-up on the Unit,
            start the global state change: GLOBAL_STOP -> GLOBAL_OPERATION */
          Can_GaaGlobalStateTransition[LucUnit] = CAN_TRUE;
          LblGlobalTransitionRequired = CAN_TRUE;
        } /* else No action required */
        /* Set the active (not sleep) bit of this Controller */
        Can_GaaActiveControllers[LucUnit] |= (1UL << LucCtrlIndex);
      }
      CAN_EXIT_CRITICAL_SECTION(CAN_RAM_DATA_PROTECTION_GLOBAL);
      if (CAN_TRUE == LblGlobalTransitionRequired)
      {
        /* At first, GLOBAL_STOP -> GLOBAL_RESET */
        LenSubState = CAN_PENDING_WAKEUP_WAIT_GLOBALRESET;
        LucResult = Can_GlobalModeChange(LucUnit, CAN_RSCAN_GMDC_RESET, &LulTimeoutDuration);
        /* Continue to STEP 3 */
      } /* else No action required */
    }
    /*
    * STEP 2:
    * If necessary, wait for GLOBAL_RESET.
    */
    else if ((CAN_PENDING_WAKEUP_WAIT_GLOBALRESET == LenSubState) &&                                                    /* PRQA S 2004 # JV-01 */
            (0UL == (Can_GaaRegs[LucUnit].pCmn->ulGSTS & CAN_RSCAN_GRSTSTS)))
    {
      /* Continue pending */
      LucResult = E_NOT_OK;
    } /* else No action required */
    /*
    * STEP 3:
    * After GLOBAL_RESET, change to GLOBAL_OPEARTION.
    */
    if ((E_OK == LucResult) && (CAN_PENDING_WAKEUP_WAIT_GLOBALRESET == LenSubState))
    {
      LenSubState = CAN_PENDING_WAKEUP_WAIT_GLOBALOP;
      LucResult = Can_GlobalModeChange(LucUnit, CAN_RSCAN_GMDC_OP, &LulTimeoutDuration);
    }
    /*
    * STEP 4:
    * If necessary, wait for GLOBAL_OPERATION.
    */
    else if ((E_OK == LucResult) && (CAN_PENDING_WAKEUP_WAIT_GLOBALOP == LenSubState) &&                                /* PRQA S 2004 # JV-01 */
            (CAN_RSCAN_GOPSTS != Can_GaaRegs[LucUnit].pCmn->ulGSTS))
    {
      /* Continue pending */
      LucResult = E_NOT_OK;
    } /* else No action required */
    /*
    * STEP 5:
    * Change to CHANNEL_RESET.
    */
    if ((E_OK == LucResult) && (CAN_PENDING_WAKEUP_WAIT_RESET != LenSubState))
    {
      /* Clear Global transition on-going flag */
      if (CAN_PENDING_WAKEUP_WAIT_GLOBALOP == LenSubState)
      {
        /* No critical section is required because this can be done atomically */
        Can_GaaGlobalStateTransition[LucUnit] = CAN_FALSE;
      } /* else No action required */

      LenSubState = CAN_PENDING_WAKEUP_WAIT_RESET;
      LucResult = Can_ChannelModeChange(LucUnit, LucCh, CAN_RSCAN_CHMDC_RESET, &LulTimeoutDuration);
      /* Continue to STEP 7 */
    }
    /*
    * STEP 6:
    * Wait for CHANNEL_RESET.
    */
    else if ((E_OK == LucResult) &&                                                                                     /* PRQA S 2004 # JV-01 */
            (CAN_RSCAN_CRSTSTS != (Can_GaaRegs[LucUnit].pCmn->aaChReg[LucCh].ulSTS & CAN_RSCAN_CSTSMASK)))
    {
      LucResult = E_NOT_OK;
    } /* else No action required.  Continue to STEP 7 */
    #endif
  }
  /*
   * STEP 7:
   * Finish transition.
   */
  if (E_OK == LucResult)                                                                                                /* PRQA S 2995, 2991 # JV-01, JV-01 */
  {
    Can_GaaCtrlState[LucCtrlIndex].enMode = CAN_COMMON_STATE_STOPPED;
    Can_GaaCtrlState[LucCtrlIndex].enSubState = CAN_NO_PENDING_TRANSITION;
    /* Indicate mode change to CanIf */
    if (CAN_TRUE == Can_GaaCtrlState[LucCtrlIndex].blWakeupByHW)
    {
      /* If the wakeup transition was triggered by HW, don't call CanIf */
    }
    else
    {
      CanIf_ControllerModeIndication((uint8)(LucCtrlIndex + CAN_CONTROLLER_OFFSET), CAN_COMMON_IF_STATE_STOPPED);       /* PRQA S 3383, 2985 # JV-01, JV-01 */
    }
  }
  else
  {
    /* If timeout occurred, update the pending status.
    This should be done at the end of this function once to avoid reentrant
    call from Can_SetControllerMode and Can_MainFunction_Mode. */
    Can_GaaCtrlState[LucCtrlIndex].enSubState = LenSubState;                                                            /* PRQA S 2880 # JV-01 */
  }
  #else /* (CAN_WAKEUP_SUPPORT == STD_ON) */
  /* If the wakeup feature is not supported, just change the logical state */
  Can_GaaCtrlState[LucCtrlIndex].enMode = CAN_COMMON_STATE_STOPPED;
  Can_GaaCtrlState[LucCtrlIndex].enSubState = CAN_NO_PENDING_TRANSITION;
  /* Indicate mode change to CanIf */
  CanIf_ControllerModeIndication((uint8)(LucCtrlIndex + CAN_CONTROLLER_OFFSET), CAN_COMMON_IF_STATE_STOPPED);           /* PRQA S 3383, 2985 # JV-01, JV-01 */
  #endif /* (CAN_WAKEUP_SUPPORT == STD_ON) */
}

/***********************************************************************************************************************
** Function Name         : Can_StartMode
**
** Service ID            : Not Applicable
**
** Description           : This function initiates the transition to the normal
**                         operating mode with complete functionality.
**
** Sync/Async            : None
**
** Reentrancy            : Reentrant from Can_SetControllerMode and
**                         Can_MainFunction_Mode.
**                         Non-reentrant from same API.
**
** Input Parameters      : LucCtrlIndex : Index of Controller config table
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : The CAN Driver must be initialized and
**                         Controller state must be CAN_T_STOP (AR422),
**                         CAN_T_WAKEUP (AR422) or CAN_CS_STOPPED (AR431)
**
** Global Variables Used : Can_GaaCtrlState, Can_GpPCController,
**                         Can_GaaRegs
**
** Function(s) invoked   : Can_ClearRxBuffers, Can_EnableTxBuffers,
**                         CanIf_ControllerModeIndication
**
** Registers Used        : (CFD)CmSTS, (CFD)CmERFL, (CFD)THLCCm
**
** Reference ID          : CAN_DUD_ACT_037
** Reference ID          : CAN_DUD_ACT_037_GBL001, CAN_DUD_ACT_037_GBL002,
** Reference ID          : CAN_DUD_ACT_037_GBL003, CAN_DUD_ACT_037_GBL004,
** Reference ID          : CAN_DUD_ACT_037_REG001, CAN_DUD_ACT_037_REG002
***********************************************************************************************************************/
FUNC(void, CAN_PRIVATE_CODE) Can_StartMode(CONST(uint8, AUTOMATIC) LucCtrlIndex)
{
  VAR(uint8, AUTOMATIC) LucUnit;
  VAR(uint8, AUTOMATIC) LucCh;
  VAR(uint32, AUTOMATIC) LulTimeoutDuration;
  VAR(Can_SubStatusType, AUTOMATIC) LenSubState;
  VAR(Std_ReturnType, AUTOMATIC) LucResult;
  P2CONST(Can_ControllerPCConfigType, AUTOMATIC, CAN_CONFIG_DATA) LpPCController;

  LucResult = E_OK;
  LulTimeoutDuration = CAN_TIMEOUT_COUNT;
  LenSubState = Can_GaaCtrlState[LucCtrlIndex].enSubState;
  LpPCController = &Can_GpPCController[LucCtrlIndex];
  LucUnit = LpPCController->ucUnit;
  LucCh = LpPCController->ucCh;

  /*
   * STEP 1:
   * If current state is BusOff, Controller should be CHANNEL_HALT.
   * Change to CHANNEL_RESET to clear tx buffers before start.
   */
  if ((CAN_NO_PENDING_TRANSITION == LenSubState) && (CAN_TRUE == Can_GaaCtrlState[LucCtrlIndex].blBusOff))
  {
    #if (CAN_RSCANFD_CONFIGURED == STD_ON)
    /* Clear error flags */
    Can_GaaRegs[LucUnit].pCmn->aaChReg[LucCh].ulERFL = CAN_RSCAN_ERFL_CLEAR;
    #endif
    Can_GaaCtrlState[LucCtrlIndex].blBusOff = CAN_FALSE;
    /* Change to CHANNEL_RESET mode */
    LenSubState = CAN_PENDING_START_WAIT_RESET;
    LucResult = Can_ChannelModeChange(LucUnit, LucCh, CAN_RSCAN_CHMDC_RESET, &LulTimeoutDuration);
  }
  /*
   * STEP 2:
   * If necessary, wait for CHANNEL_RESET.
   */
  #if (CAN_RSCANFD_CONFIGURED == STD_ON)
  else if ((CAN_PENDING_START_WAIT_RESET == LenSubState) &&                                                             /* PRQA S 2004 # JV-01 */
           (0UL == (Can_GaaRegs[LucUnit].pCmn->aaChReg[LucCh].ulSTS & CAN_RSCAN_CRSTSTS)))
  {
    LucResult = E_NOT_OK;
  } /* else No action required. Continue to STEP 3 */
  #endif
  /*
   * STEP 3:
   * Change to CHANNEL_COMMUNICATION mode.
   */
  if ((E_OK == LucResult) &&
      ((CAN_NO_PENDING_TRANSITION == LenSubState) || (CAN_PENDING_START_WAIT_RESET == LenSubState)))
  {
    #if (CAN_RX_OBJECT == STD_ON)
    /*
     * Clear all buffers
     * TX_BUFFER, TX_QUEUE and TXRX_FIFO(TxMode) are cleared automatically
     * in CHANNEL_RESET mode.
     * RX_BUFFER, RX_FIFO, TXRX_FIFO(RxMode) must be cleared by software.
     */
    Can_ClearRxBuffers(LucUnit, LucCtrlIndex);
    #endif /* (CAN_RX_OBJECT == STD_ON) */

    /* Change Channel Mode to Communication Mode */
    LenSubState = CAN_PENDING_START_WAIT_COM;
    LucResult = Can_ChannelModeChange(LucUnit, LucCh, CAN_RSCAN_CHMDC_COM, &LulTimeoutDuration);
  }
  /*
   * STEP 4:
   * Wait for CHANNEL_COMMUNICATION.
   */
  #if (CAN_RSCANFD_CONFIGURED == STD_ON)
  else if ((E_OK == LucResult) && (CAN_PENDING_START_WAIT_COM == LenSubState) &&                                        /* PRQA S 2004 # JV-01 */
           (CAN_RSCAN_COPSTS != (Can_GaaRegs[LucUnit].pCmn->aaChReg[LucCh].ulSTS & CAN_RSCAN_CSTSMASK)))
  {
    /* Continue pending */
    LucResult = E_NOT_OK;
  } /* else No action required */
  #endif
  /*
   * STEP 5:
   * Finish transition.
   */
  if (E_OK == LucResult)
  {
    #if ((CAN_TX_COMFIFO == STD_ON) || (CAN_GATEWAY_COMFIFO == STD_ON) || (CAN_TX_QUEUE == STD_ON) || \
        (CAN_GATEWAY_QUEUE == STD_ON))
    /* Re-enable CFCC.CFE and TXQCC.TXQE
       since these registers are cleared in CHANNEL_RESET */
    Can_EnableTxBuffers(LucUnit, LucCtrlIndex);
    #endif
    #if (CAN_RSCANFD_CONFIGURED == STD_ON)
    /* Enable transmit history buffer */
    Can_GaaRegs[LucUnit].pCmn->aaTHLCC[LucCh] = LpPCController->ulTHLCC | CAN_RSCAN_THLE;
    #endif
    /* Inform the upper layer */
    Can_GaaCtrlState[LucCtrlIndex].enMode = CAN_COMMON_STATE_STARTED;
    Can_GaaCtrlState[LucCtrlIndex].enSubState = CAN_NO_PENDING_TRANSITION;
    CanIf_ControllerModeIndication((uint8)(LucCtrlIndex + CAN_CONTROLLER_OFFSET), CAN_COMMON_IF_STATE_STARTED);         /* PRQA S 3383, 2985 # JV-01, JV-01 */
  }
  else
  {
    /* If timeout occurred, update the pending status.
      This should be done at the end of this function once to avoid reentrant
      call from Can_SetControllerMode and Can_MainFunction_Mode. */
    Can_GaaCtrlState[LucCtrlIndex].enSubState = LenSubState;
  }
}

/***********************************************************************************************************************
** Function Name         : Can_ClearRxBuffers
**
** Service ID            : Not Applicable
**
** Description           : This function clears rx buffers when a Controller
**                         enters CHANNEL_RESET mode.
**
** Sync/Async            : None
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LucUnit      : RS-CAN(FD) unit index
**                         LucCtrlIndex : Controller index
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : The availability of ID must be guaranteed
*                          by the upper layer.
**
** Global Variables Used : Can_GpConfig, Can_GpHohConfig,
**                         Can_GaaRegs
**
** Function(s) invoked   : None
**
** Registers Used        : (CFD)CFCCk, (CFD)RFCCx, (CFD)RMNDy
**
** Reference ID          : CAN_DUD_ACT_051
** Reference ID          : CAN_DUD_ACT_051_REG001, CAN_DUD_ACT_051_REG002,
** Reference ID          : CAN_DUD_ACT_051_REG003, CAN_DUD_ACT_051_REG004
** Reference ID          : CAN_DUD_ACT_051_REG005
***********************************************************************************************************************/
#if (CAN_RX_OBJECT == STD_ON)
STATIC FUNC(void, CAN_PRIVATE_CODE)
                              Can_ClearRxBuffers(CONST(uint8, AUTOMATIC) LucUnit, CONST(uint8, AUTOMATIC) LucCtrlIndex)
{
  P2CONST(Can_HohConfigType, AUTOMATIC, CAN_CONFIG_DATA) LpHoh;
  VAR(uint16, AUTOMATIC) LusHohIndex;
  #if (CAN_RX_BUFFER == STD_ON)
  VAR(uint32, AUTOMATIC) LulRMNDIndex;
  VAR(uint32, AUTOMATIC) LulRMNDMask;
  #endif

  /* Scan all HOH objects */
  for (LusHohIndex = 0U; LusHohIndex < Can_GpConfig->usNoOfHohs; LusHohIndex++)                                         /* PRQA S 3416 # JV-01 */
  {
    LpHoh = &Can_GpHohConfig[LusHohIndex];
    /* If ths HOH is HRH and belongs to this Controller, process it */
    if ((LpHoh->ucController == LucCtrlIndex) && (CAN_HOH_HRH == LpHoh->enHoh))
    {
      switch (LpHoh->enBufferType)
      {
      #if (CAN_RX_COMFIFO == STD_ON)
      case CAN_BUFFERTYPE_TXRXFIFO:
        /* Disable TxRxFIFO(RxMode) */
        Can_GaaRegs[LucUnit].pCmn->aaCFCC[LpHoh->usBufferIndex] = LpHoh->ulXXCCRegValue;
        /* Re-Enable TxRxFIFO(RxMode) */
        Can_GaaRegs[LucUnit].pCmn->aaCFCC[LpHoh->usBufferIndex] = LpHoh->ulXXCCRegValue | CAN_RSCAN_CFE;
        break;
      #endif
      #if (CAN_RX_FIFO == STD_ON)
      case CAN_BUFFERTYPE_RXFIFO:
        /* Disable Rx FIFO */
        Can_GaaRegs[LucUnit].pCmn->aaRFCC[LpHoh->usBufferIndex] = LpHoh->ulXXCCRegValue;
        /* Re-Enable Rx FIFO */
        Can_GaaRegs[LucUnit].pCmn->aaRFCC[LpHoh->usBufferIndex] = LpHoh->ulXXCCRegValue | CAN_RSCAN_RFE;
        break;
      #endif
      #if (CAN_RX_BUFFER == STD_ON)
      case CAN_BUFFERTYPE_BUFFER:
        /* Get index and bit position of RMND registers for this buffer */
        LulRMNDIndex = CAN_RSCAN_RMND_GET_INDEX(LpHoh->usBufferIndex);
        LulRMNDMask = CAN_RSCAN_RMND_GET_BITMASK(LpHoh->usBufferIndex);
        /* Clear receive flag */
        Can_GaaRegs[LucUnit].pCmn->aaRMND[LulRMNDIndex] = ~LulRMNDMask;
        break;
      #endif
      default:
        /* Never executed */
        break;
      } /* switch (LpHoh->enBufferType) */
    } /* else No action required */
  }
}
#endif

/***********************************************************************************************************************
** Function Name         : Can_EnableTxBuffers
**
** Service ID            : Not Applicable
**
** Description           : This function enables Tx buffers when
**                         a Controller is re-started.
**
** Sync/Async            : None
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LucUnit      : RS-CAN(FD) unit index
**                         LucCtrlIndex : Controller index
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : The availability of ID must be guaranteed
*                          by the upper layer.
**
** Global Variables Used : Can_GpConfig, Can_GpHohConfig,
**                         Can_GaaRegs
**
** Function(s) invoked   : None
**
** Registers Used        : (CFD)CFCCk, (CFD)TXQCCm
**
** Reference ID          : CAN_DUD_ACT_052
** Reference ID          : CAN_DUD_ACT_052_REG001, CAN_DUD_ACT_052_REG002
***********************************************************************************************************************/
#if ((CAN_TX_COMFIFO == STD_ON) || (CAN_GATEWAY_COMFIFO == STD_ON) || (CAN_TX_QUEUE == STD_ON) || \
     (CAN_GATEWAY_QUEUE == STD_ON))
STATIC FUNC(void, CAN_PRIVATE_CODE)
                              Can_EnableTxBuffers(CONST(uint8, AUTOMATIC) LucUnit, CONST(uint8, AUTOMATIC) LucCtrlIndex)
{
  P2CONST(Can_HohConfigType, AUTOMATIC, CAN_CONFIG_DATA) LpHoh;
  VAR(uint16, AUTOMATIC) LusHohIndex;
  #if ((CAN_TX_QUEUE == STD_ON) || (CAN_GATEWAY_QUEUE == STD_ON))
  VAR(uint32, AUTOMATIC) LulTxQCh;
  VAR(uint32, AUTOMATIC) LulTxQIdx;
  #endif

  /* Scan all HOH objects */
  for (LusHohIndex = 0U; LusHohIndex < Can_GpConfig->usNoOfHohs; LusHohIndex++)                                         /* PRQA S 3416 # JV-01 */
  {
    LpHoh = &Can_GpHohConfig[LusHohIndex];
    /* If this HOH belongs to this Controller, process it according to a type */
    if (LpHoh->ucController == LucCtrlIndex)
    {
      #if ((CAN_TX_COMFIFO == STD_ON) || (CAN_GATEWAY_COMFIFO == STD_ON))
      if (((CAN_BUFFERTYPE_TXRXFIFO == LpHoh->enBufferType) && (CAN_HOH_HTH == LpHoh->enHoh)) ||
          (CAN_BUFFERTYPE_GATEWAY == LpHoh->enBufferType))
      {
        Can_GaaRegs[LucUnit].pCmn->aaCFCC[LpHoh->usBufferIndex] = LpHoh->ulXXCCRegValue | CAN_RSCAN_CFE;
      } /* else No action required if (CAN_TX_QUEUE == STD_OFF) && (CAN_GATEWAY_QUEUE == STD_OFF*/
      #endif
      #if ((CAN_TX_QUEUE == STD_ON) || (CAN_GATEWAY_QUEUE == STD_ON))
      if (CAN_BUFFERTYPE_TXQUEUE == LpHoh->enBufferType)
      {
        LulTxQCh = (uint32)LpHoh->usBufferIndex / CAN_RSCAN_TXQUEUE_PER_CH;
        LulTxQIdx = (uint32)LpHoh->usBufferIndex % CAN_RSCAN_TXQUEUE_PER_CH;
        Can_GaaRegs[LucUnit].pCmn->aaTQueueReg[LulTxQIdx].aaTXQCC[LulTxQCh] = LpHoh->ulXXCCRegValue | CAN_RSCAN_TXQE;
      } /* else No action required */
      #endif
    } /* else No action required */
  }
}
#endif /* ((CAN_TX_COMFIFO == STD_ON) || (CAN_GATEWAY_COMFIFO == STD_ON) || \
      (CAN_TX_QUEUE == STD_ON) || (CAN_GATEWAY_QUEUE == STD_ON)) */

/***********************************************************************************************************************
** Function Name         : Can_StopMode
**
** Service ID            : Not Applicable
**
** Description           : This function initiates the transition to stop mode.
**
** Sync/Async            : None
**
** Reentrancy            : Reentrant from Can_SetControllerMode and
**                         Can_MainFunction_Mode.
**                         Non-reentrant from same API.
**
** Input Parameters      : LucCtrlIndex : Index of Controller config table
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : The CAN Driver must be initialized.
**
** Global Variables Used : Can_GaaCtrlState, Can_GpPCController,
**                         Can_GaaRegs
**
** Function(s) invoked   : Can_ChannelModeChange,
**                         CanIf_ControllerModeIndication
**
** Registers Used        : (CFD)CmSTS
**
** Reference ID          : CAN_DUD_ACT_038
** Reference ID          : CAN_DUD_ACT_038_GBL001, CAN_DUD_ACT_038_GBL002
** Reference ID          : CAN_DUD_ACT_038_GBL003
***********************************************************************************************************************/
FUNC(void, CAN_PRIVATE_CODE) Can_StopMode(CONST(uint8, AUTOMATIC) LucCtrlIndex)
{
  VAR(uint32, AUTOMATIC) LulTimeoutDuration;
  VAR(Can_SubStatusType, AUTOMATIC) LenSubState;
  VAR(Std_ReturnType, AUTOMATIC) LucResult;
  VAR(uint8, AUTOMATIC) LucUnit;
  VAR(uint8, AUTOMATIC) LucCh;

  LucResult = E_OK;
  LulTimeoutDuration = CAN_TIMEOUT_COUNT;
  LenSubState = Can_GaaCtrlState[LucCtrlIndex].enSubState;
  LucUnit = Can_GpPCController[LucCtrlIndex].ucUnit;
  LucCh = Can_GpPCController[LucCtrlIndex].ucCh;

  /*
   * STEP 1:
   * If the current state is START, change to HALT mode before RESET mode
   * to wait the completion of on-going transmission or reception.
   * If the STOP transition is invoked from Can_SetControlerMode,
   * the first subState is CAN_TENTATIVE_TRANSITION.
   * If the STOP transition is invoked from BusOff,
   * the state transition is done immediately and this function is not invoked.
   */
  if (CAN_TENTATIVE_TRANSITION == LenSubState)
  {
    LenSubState = CAN_PENDING_STOP_WAIT_HALT;
    LucResult = Can_ChannelModeChange(LucUnit, LucCh, CAN_RSCAN_CHMDC_HALT, &LulTimeoutDuration);
  }
  /*
   * STEP 2:
   * If necessary, wait for the completion to change to CHANNEL_HALT mode.
   */
  #if (CAN_RSCANFD_CONFIGURED == STD_ON)
  else if ((CAN_PENDING_STOP_WAIT_HALT == LenSubState) &&                                                               /* PRQA S 2004 # JV-01 */
           (0UL == (Can_GaaRegs[LucUnit].pCmn->aaChReg[LucCh].ulSTS & CAN_RSCAN_CHLTSTS)))
  {
    LucResult = E_NOT_OK;
  } /* else No action required */
  #endif

  /*
   * STEP 3:
   * Change the controller to CHANNEL_RESET mode.
   */
  if ((E_OK == LucResult) && (CAN_PENDING_STOP_WAIT_RESET != LenSubState))
  {
    LenSubState = CAN_PENDING_STOP_WAIT_RESET;
    LucResult = Can_ChannelModeChange(LucUnit, LucCh, CAN_RSCAN_CHMDC_RESET, &LulTimeoutDuration);
  }
  /*
   * STEP 4:
   * Wait for the completion to change to CHANNEL_RESET mode.
   */
  #if (CAN_RSCANFD_CONFIGURED == STD_ON)
  else if ((E_OK == LucResult) && (0UL == (Can_GaaRegs[LucUnit].pCmn->aaChReg[LucCh].ulSTS & CAN_RSCAN_CRSTSTS)))       /* PRQA S 2004 # JV-01 */
  {
    /* Continue to pending */
    LucResult = E_NOT_OK;
  } /* else No action required */
  #endif
  /*
   * STEP 5:
   * Clear all received data and notify CanIf.
   */
  if (E_OK == LucResult)
  {
    /* Set the Controller to stop mode */
    Can_GaaCtrlState[LucCtrlIndex].enMode = CAN_COMMON_STATE_STOPPED;
    Can_GaaCtrlState[LucCtrlIndex].enSubState = CAN_NO_PENDING_TRANSITION;

    /* Indicate mode change to CanIf */
    CanIf_ControllerModeIndication((uint8)(LucCtrlIndex + CAN_CONTROLLER_OFFSET), CAN_COMMON_IF_STATE_STOPPED);         /* PRQA S 3383, 2985 # JV-01, JV-01 */
  }
  else
  {
    /* If timeout occurred, update the pending status.
    This should be done at the end of this function once to avoid reentrant
    call from Can_SetControllerMode and Can_MainFunction_Mode. */
    Can_GaaCtrlState[LucCtrlIndex].enSubState = LenSubState;
  }
}

/***********************************************************************************************************************
** Function Name         : Can_GlobalModeChange
**
** Service ID            : Not Applicable
**
** Description           : Perform global mode change of RACAN.
**
** Sync/Async            : None
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LucUnit   : Module number of RSCANn
**                         LulMdBits : Mode bits of GCTR register
**
** InOut Parameters      : LpTimeoutDuration  Timeout counts with OsCounter,
**                                  actual elapsed time is subtracted from this.
**
** Output Parameters     : None
**
** Return parameter      : Std_ReturnType
**
** Preconditions         : None
**
** Global Variables Used : Can_GaaRegs
**
** Function(s) invoked   : Can_WaitRegisterChange
**
** Registers Used        : (CFD)GCTR, (CFD)GSTS
**
** Reference ID          : CAN_DUD_ACT_039
** Reference ID          : CAN_DUD_ACT_039_REG001
***********************************************************************************************************************/
FUNC(Std_ReturnType, CAN_PRIVATE_CODE) Can_GlobalModeChange(CONST(uint8, AUTOMATIC) LucUnit,                            /* PRQA S 3206, 1503 # JV-01, JV-01 */
 CONST(uint32, AUTOMATIC) LulMdBits, CONSTP2VAR(uint32, AUTOMATIC, CAN_APPL_DATA) LpTimeoutDuration)                    /* PRQA S 3432, 3206 # JV-01, JV-01 */
{
  VAR(Std_ReturnType, AUTOMATIC) LucResult;
  #if (CAN_RSCANFD_CONFIGURED == STD_ON)
  Can_GaaRegs[LucUnit].pCmn->ulGCTR = LulMdBits;

  LucResult =
      Can_WaitRegisterChange(&Can_GaaRegs[LucUnit].pCmn->ulGSTS, CAN_RSCAN_GSTSMASK, LulMdBits, LpTimeoutDuration);
  #else
  LucResult = E_NOT_OK;
  #endif
  return LucResult;
}

/***********************************************************************************************************************
** Function Name         : Can_ChannelModeChange
**
** Service ID            : Not Applicable
**
** Description           : Perform channel mode change of RACAN.
**
** Sync/Async            : None
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LucUnit   : Module number of RSCANn
**                         LucCh     : Channel number
**                         LulMdBits : Mode bits of CmCTR register
**
** InOut Parameters      : LpTimeoutDuration  Timeout counts with OsCounter,
**                                  actual elapsed time is subtracted from this.
**
** Output Parameters     : None
**
** Return parameter      : Std_ReturnType
**
** Preconditions         : None
**
** Global Variables Used : Can_GaaRegs
**
** Function(s) invoked   : Can_WaitRegisterChange
**
** Registers Used        : (CFD)CmCTR, (CFD)CmSTS
**
** Reference ID          : CAN_DUD_ACT_040
** Reference ID          : CAN_DUD_ACT_040_REG001
***********************************************************************************************************************/
FUNC(Std_ReturnType, CAN_PRIVATE_CODE) Can_ChannelModeChange(CONST(uint8, AUTOMATIC) LucUnit,                           /* PRQA S 1505, 3206 # JV-01, JV-01 */
  CONST(uint8, AUTOMATIC) LucCh,CONST(uint32, AUTOMATIC) LulMdBits,                                                     /* PRQA S 3206 # JV-01 */
  CONSTP2VAR(uint32, AUTOMATIC, CAN_APPL_DATA) LpTimeoutDuration)                                                       /* PRQA S 3432, 3206 # JV-01, JV-01 */
{
  VAR(Std_ReturnType, AUTOMATIC) LucResult;
  #if (CAN_RSCANFD_CONFIGURED == STD_ON)
  P2CONST(volatile uint32, AUTOMATIC, REGSPACE) LpSTSReg;

  Can_GaaRegs[LucUnit].pCmn->aaChReg[LucCh].ulCTR =
                                (Can_GaaRegs[LucUnit].pCmn->aaChReg[LucCh].ulCTR & ~CAN_RSCAN_CHMDC_MASK) | LulMdBits;

  LpSTSReg = &Can_GaaRegs[LucUnit].pCmn->aaChReg[LucCh].ulSTS;
  LucResult = Can_WaitRegisterChange(LpSTSReg, CAN_RSCAN_CSTSMASK, LulMdBits, LpTimeoutDuration);
  #else
  LucResult = E_NOT_OK;
  #endif

  return LucResult;
}

/***********************************************************************************************************************
** Function Name         : Can_WaitRegisterChange
**
** Service ID            : Not Applicable
**
** Description           : Wait for change of status register
**
** Sync/Async            : None
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LpReg   : Address of status register
**                         LulMask : Mask bits to be compared
**                         LulBits : Comparition bits
**
** InOut Parameters      : LpTimeoutDuration  Timeout counts with OsCounter,
**                                  actual elapsed time is subtracted from this.
**
** Output Parameters     : None
**
** Return parameter      : Std_ReturnType
**
** Preconditions         : The availability of parameters must be guaranteed
**                         by the upper layer.
**
** Global Variables Used : None
**
** Function(s) invoked   : GetCounterValue()
**
** Registers Used        : Depend on LpReg
**
** Reference ID          : CAN_DUD_ACT_041
***********************************************************************************************************************/
FUNC(Std_ReturnType, CAN_PRIVATE_CODE)
Can_WaitRegisterChange(volatile CONSTP2CONST(uint32, AUTOMATIC, REGSPACE) LpReg, CONST(uint32, AUTOMATIC) LulMask,
                      CONST(uint32, AUTOMATIC) LulBits, CONSTP2VAR(uint32, AUTOMATIC, CAN_APPL_DATA) LpTimeoutDuration) /* PRQA S 3432 # JV-01 */
{
  VAR(Std_ReturnType, AUTOMATIC) LucResult;
  VAR(TickType, AUTOMATIC) LddPrevTime;
  VAR(TickType, AUTOMATIC) LddCurrentTime;
  VAR(uint32, AUTOMATIC) LulTimeLapse;

  LulTimeLapse = 0UL;
  LucResult = E_OK;

  /* Get initial count */
  (void)GetCounterValue(CAN_OS_COUNTER_ID, &LddPrevTime);

  /* Wait until mode change completion or timeout */
  while (((*LpReg & LulMask) != LulBits) && (E_OK == LucResult))
  {
    /* Get current count */
    (void)GetCounterValue(CAN_OS_COUNTER_ID, &LddCurrentTime);
    /* Check whether timer lapped */
    if (LddPrevTime > LddCurrentTime)
    {
      /* When timer lapped, add remained counts from previous value to lapping.
         '1UL' means extra one count when lapping (MAX -> 0). */
      LulTimeLapse =
          LulTimeLapse + (uint32)((((TickType)CAN_OS_COUNTER_MAX_VALUE - LddPrevTime) + 1UL) + LddCurrentTime);         /* PRQA S 3383 # JV-01 */
    }
    else
    {
      /* Otherwise, accumulate the delta counts simply. */
      LulTimeLapse = LulTimeLapse + (uint32)(LddCurrentTime - LddPrevTime);                                             /* PRQA S 3383 # JV-01 */
    }
    /* Update the previous count */
    LddPrevTime = LddCurrentTime;
    /* Check timeout */
    if (*LpTimeoutDuration <= LulTimeLapse)
    {
      /* Set error and break wait loop */
      LucResult = E_NOT_OK;
    } /* else No action required */
  }
  /* Subtruct actual elapsed time from the parameter */
  *LpTimeoutDuration = *LpTimeoutDuration - LulTimeLapse;                                                               /* PRQA S 3383 # JV-01 */

  return LucResult;
}
#define CAN_STOP_SEC_PRIVATE_CODE
#include "Can_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
