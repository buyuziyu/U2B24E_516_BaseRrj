/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Fr_59_Renesas.c                                                                                     */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2019-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains API function implementations of FR Driver.                                                      */
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
 * 2.4.1:  30/06/2025     : Remove SW-VERSION in file header
 * 2.4.0:  30/06/2025     : Update SW-VERSION for RH850/U2Ax MCAL Ver22.01.00(D) Final Release
 * 2.3.2:  29/04/2025     : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 Release
 *                          As part of QAC 11.6.0 support, following changes are made: 
 *                          1. Add QAC comment of message 2877
 * 2.3.1:  31/03/2025     : Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02 Release
 *                          As part of QAC 11.6.0 support, following changes are made: 
 *                          1. Remove QAC comments of message 2814, 2824, 2844, 2877
 * 2.3.0:  28/02/2025     : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.1:  31/12/2024     : Update specific for U2Ax: Add ID FR_DUD_ACT_016_ERR010 to Fr_59_Renesas_ReconfigLPdu
 * 2.2.0:  31/12/2024     : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 * 2.1.3:  31/10/2024     : Update SW-VERSION to 2.1.3
 *                          As part of QAC 9.5.0 support, following changes are made: update for QAC messages 2877
 * 2.1.2:  20/08/2024     : As part of R22-11 support, following changes are made:
 *                          Remove preprocessor FR_59_RENESAS_AR_431_VERSION
 *                        : As part of QAC 9.5.0 support, following changes are made:
 *                          1. Support QAC 9.5.0 for messages: 2814, 2824, 2844, 2877
 *                          2. Fix QAC messages (2:0604) in Fr_59_Renesas_ControllerInit,
 *                          Fr_59_Renesas_SetAbsoluteTimer, Fr_59_Renesas_HaltInputQueue,
 *                          Fr_59_Renesas_SetCycleCounterFiltering
 *                          3. Sort QAC message header in ascending order
 *                          4. Update Global Variables Used, Reference ID for all APIs
 * 2.1.1:  29/07/2024     : As part of multiple postbuild variant support, following changes are made:
 *                          1. Update ECODE reference ID for APIs, not impact behavior of code
 *                          2. Add new global variable Fr_59_Renesas_GpPeriodTimeConfigPtr
 *                        : As part of QAC 9.5.0 support, following changes are made:
 *                          1. Updated variable declarion order to support qac 9.5.0. Not impact on behavior of code.
 *                          2. Update Reference ID for all APIs
 *                          As part of multicore support, following changes are made:
 *                          1. Unify LblDevErrDetect to LblErrDetect in all functions
 *                          2. Add new include "Os.h"
 *                          3. Update API Fr_59_Renesas_Init to initialize Fleray when using multicore
 *                          4. Others API: add multicore section and det check for multicore
 *                        : As part of QAC 10.3.0 support, following changes are made:
 *                          Remove redundant QAC message: 0857, 2814, 2824, 2844, 3469
 * 2.1.0:  24/02/2024     : Change SW-VERSION to 2.1.0
 * 2.0.1:   27/09/2023    : Change FR_59_RENESAS_AR_R21_11_VERSION with
 *                         FR_59_RENESAS_AR_R22_11_VERSION to support AR22-11
 * 2.0.0:   30/07/2023    : Add CWE rule into QAC header (1503, 2814, 2877, 3432, 2982, 3416, 2824, 2844, 2985, 3415,
 *                         3673 messages)
 *          10/06/2023    : Improve Fr_59_Renesas_ReconfigLPdu to get the channel configured for AR2111
 *          26/05/2023    : Change FR_59_RENESAS_AR_2111_VERSION to FR_59_RENESAS_AR_R21_11_VERSION
 *          21/04/2023    : For support AR2111:
 *                          + Update description of Function Invoked for APIs:
 *                          Fr_59_Renesas_StartCommunication
 *                          Fr_59_Renesas_AllowColdstart
 *                          Fr_59_Renesas_AllSlots
 *                          Fr_59_Renesas_HaltCommunication
 *                          Fr_59_Renesas_SendWUP
 *                          Fr_59_Renesas_SetWakeupChannel
 *                          Fr_59_Renesas_SetAbsoluteTimer
 *                          Fr_59_Renesas_SetCycleCounterFiltering
 *                          + Update description of Output Parameters, Function Invoked and Syntax for APIs
 *                          Fr_59_Renesas_TransmitTxLPdu
 *                          Fr_59_Renesas_ReceiveRxLPdu
 *                          Fr_59_Renesas_CheckTxLPduStatus
 *          19/04/2023    : Implement improvement actions from Technical Assessment
 *                         + Add Fr_59_Renesas_GblTransferHandlerInitDone to Global Variables description of APIs:
 *                            Fr_59_Renesas_TransferHandlerInit, Fr_59_Renesas_TransferQueueTable,
 *                            Fr_59_Renesas_ReceiveQueueTable, Fr_59_Renesas_InputTransferDisable,
 *                            Fr_59_Renesas_OutputTransferDisable, Fr_59_Renesas_UserInputTransferRequest,
 *                            Fr_59_Renesas_UserOutputTransferRequest, Fr_59_Renesas_HaltInputQueue.
 *                         + Add Fr_59_Renesas_GpControllerConfigPtr to Global Variables description of APIs:
 *                            Fr_59_Renesas_CancelAbsoluteTimer, Fr_59_Renesas_EnableAbsoluteTimerIRQ,
 *                            Fr_59_Renesas_AckAbsoluteTimerIRQ, Fr_59_Renesas_DisableAbsoluteTimerIRQ,
 *                            Fr_59_Renesas_GetAbsoluteTimerIRQStatus.
 *                         + Add Fr_59_Renesas_GpCtrlRegSet to Global Variables description of API:
 *                            Fr_59_Renesas_Init.
 *                         + Add Fr_FIFOTableContentPtr to Global Variables description of API:
 *                            Fr_59_Renesas_TransferHandlerInit.
 *                         + Add Fr_OutputTableContentPtr to Global Variables description of APIs:
 *                            Fr_59_Renesas_TransferHandlerInit.
 *                         + Remove Dem_ReportErrorStatus(AR422)and Dem_SetEventStatus(AR431) in Functions Invoked of 
 *                          APIs:
 *                            Fr_59_Renesas_StartCommunication, Fr_59_Renesas_AllowColdstart,
 *                            Fr_59_Renesas_AllSlots, Fr_59_Renesas_HaltCommunication, Fr_59_Renesas_SendWUP,
 *                            Fr_59_Renesas_SetWakeupChannel, Fr_59_Renesas_GetNmVector,
 *                            Fr_59_Renesas_SetCycleCounterFiltering.
 * 1.4.3:   09/05/2022    : Change SW-VERSION to 1.4.3, Remove "else" statement don't use when no action required.
 *                          Add QAC message 0857
 * 1.3.3:   02/03/2022    : Change SW-VERSION to 1.4.2
 * 1.3.2:   13/08/2021    : Change SW-VERSION to 1.3.2
 * 1.3.1:   02/07/2021    : Add QAC message 9.5.0.
 *                          Format source code to 120 characters.
 *                          Improve Violation tag (remove START/END).
 *          04/05/2021    : + In API Fr_59_Renesas_Init, remove redundant space in pointer Fr_ConfigPtr to follow coding
 *                          guideline Style_Format_008.
 *                          + Update to include SchM_Fr_59_Renesas.h header file in case critical section is enabled.
 *          29/04/2021    : + Implemented Critical Section in API Fr_59_Renesas_ControllerInit for sequence before
 *                          execute internal function Fr_59_Renesas_UnlockSequence and after writing CHI command READY
 *                          to register FLXAnFRSUCC1 (internal function Fr_59_Renesas_WriteCHICmd) to fully comply with
 *                          Hardware UM note for register FLXAnFRLCK.
 *          28/04/2021    : + Corrected condition to check for value of input parameter Fr_HeaderCRC
 *                          in API Fr_59_Renesas_ReconfigLPdu before report DET error FR_59_RENESAS_E_INV_HEADERCRC.
 *                          + Corrected wrong information in header note of API Fr_59_Renesas_GetVersionInfo.
 * 1.3.0:   20/01/2021    : + Update function prototype for following Renesas APIs
 *                          Fr_59_Renesas_TransferHandlerInit
 *                          Fr_59_Renesas_TransferQueueTable
 *                          Fr_59_Renesas_ReceiveQueueTable
 *                          Fr_59_Renesas_InputTransferDisable
 *                          Fr_59_Renesas_OutputTransferDisable
 *                          Fr_59_Renesas_UserInputTransferRequest
 *                          Fr_59_Renesas_UserOutputTransferRequest
 *                          Fr_59_Renesas_HaltInputQueue
 *                          Fr_59_Renesas_SetCycleCounterFiltering
 *                          + Add QAC comments to accept messages 3673 and 3227
 *          17/11/2020    : Update the condition to check FR_59_RENESAS_E_INV_TIMER_IDX error
 *                          in functions:
 *                          Fr_59_Renesas_SetAbsoluteTimer, Fr_59_Renesas_CancelAbsoluteTimer,
 *                          Fr_59_Renesas_EnableAbsoluteTimerIRQ, Fr_59_Renesas_AckAbsoluteTimerIRQ,
 *                          Fr_59_Renesas_DisableAbsoluteTimerIRQ, Fr_59_Renesas_GetAbsoluteTimerIRQStatus,
 *                          Fr_59_Renesas_SetCycleCounterFiltering.
 *                          Add comment for QAC message 2962.
 * 1.2.0:   26/08/2020    : Release.
 * 1.1.0:   19/06/2020    : Release.
 *          28/07/2020    : Add QAC 9.3.1 comment.
 * 1.0.3:   16/06/2020    : + Remove Critical Section implementation in Fr_59_Renesas_TransmitTxLPdu,
 *                          Fr_59_Renesas_CheckTxLPduStatus.
 *                          + Add DET check for CHI command in Fr_59_Renesas_AllowColdstart.
 *                          + Update Fr_59_Renesas_SetWakeupChannel, Fr_59_Renesas_StartCommunication,
 *                          Fr_59_Renesas_AllowColdstart, Fr_59_Renesas_AllSlots, Fr_59_Renesas_HaltCommunication,
 *                          Fr_59_Renesas_SendWUP API to avoid calling Fr_59_Renesas_GetPOCStsFlag
 *                          internal function 2 times.
 *          02/06/2020    : Improve Fr_59_Renesas_SetWakeupChannel to call Fr_59_Renesas_GetPOCStsFlag only one time.
 *          28/05/2020    : Remove MISRA C Rule Violation (2:2982), (2:3227).
 *          24/05/2020    : Add MISRA C Rule Violation (3:3415), (2:3673), (4:2985).
 *          21/05/2020    : Add LOC to get return value from Fr_59_Renesas_UpdateDataTransferMode in
 *                          Fr_59_Renesas_TransmitTxLPdu.
 *          06/05/2020    : Update the condition to check FR_59_RENESAS_E_INIT_FAILED and FR_59_RENESAS_E_PARAM_POINTER
 *                          Fr_59_Renesas_TransferHandlerInit, Fr_59_Renesas_TransferQueueTable,
 *                          Fr_59_Renesas_ReceiveQueueTable, Fr_59_Renesas_OutputTransferDisable,
 *                          Fr_59_Renesas_UserInputTransferRequest, Fr_59_Renesas_UserOutputTransferRequest,
 *                          Fr_59_Renesas_HaltInputQueue, Fr_59_Renesas_InputTransferDisable.
 *          04/05/2020    : + Update range check for Fr_ListSize argument in Fr_59_Renesas_GetSyncFrameList.
 *                          + Add range check for Fr_FrameId from 0 to 2047 in Fr_59_Renesas_ReconfigLPdu.
 * 1.0.2:   25/04/2020    : Remove argument definition using Compiler.h's macros.
 *          19/04/2020    : Change FR_59_RENESAS_C_SW_MAJOR_VERSION and FR_59_RENESAS_C_SW_MINOR_VERSION to refer
 *                          to FR_59_RENESAS_SW_MAJOR_VERSION_VALUE and FR_59_RENESAS_SW_MINOR_VERSION_VALUE.
 *          17/04/2020    : Update the header files including.
 * 1.0.1:   23/03/2020    : + Update description for Fr_59_Renesas_CheckTxLPduStatus.
 *                          + Add function call for Fr_59_Renesas_WriteOutputBufferCommand in
 *                            Fr_59_Renesas_CheckTxLPduStatus.
 *          20/03/2020    : + Change traceability ID format from "FR_DDD_" to
 *                           "FR_DUD_".
 *                          + Update function call in Fr_59_Renesas_ReceiveRxLPdu.
 *          13/03/2020    : + Correct macro contain for declared and using LblErrDetect. Refer to #259237.
 *          11/02/2020    : + Correct FR_59_RENESAS_DEV_ERROR_DETECT
 *                           macro implementation in
 *                           Fr_59_Renesas_StartCommunication,
 *                           Fr_59_Renesas_AllowColdstart,
 *                           Fr_59_Renesas_AllSlots, Fr_59_Renesas_SendWUP,
 *                           Fr_59_Renesas_AbortCommunication,
 *                           Fr_59_Renesas_HaltCommunication,
 *                           Fr_59_Renesas_SetWakeupChannel,
 *                           Fr_59_Renesas_SetAbsoluteTimer,
 *                           Fr_59_Renesas_SetCycleCounterFiltering
 *          04/02/2020    : + Correct FR_VAR ptrclass in pointer definition.
 *                          + For Redmine #250032, correct condition to check
 *                           POC state in Fr_59_Renesas_SetAbsoluteTimer.
 *          15/01/2020    : + Change from use Dem_ReportStatus() to
 *                           FR_59_RENESAS_DEM_REPORT_ERROR.
 *                          + Change FR_59_RENESAS_E_INV_POCSTATE to a runtime
 *                           error when using AUTOSAR R4.3.1.
 * 1.0.0:   11/12/2019    : Initial Version.
 */
/*****************************************************************************/
/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/

/* Included for the declaration of API functions */
#include "Fr_59_Renesas.h"

/* Included for the declaration of the internal functions */
#include "Fr_59_Renesas_LLDriver.h"

#if (((FR_59_RENESAS_AR_VERSION == FR_59_RENESAS_AR_422_VERSION) && (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)) || \
                                                    (FR_59_RENESAS_AR_VERSION == FR_59_RENESAS_AR_R22_11_VERSION))

/* Included for the declaration of Det_ReportError() and Det_ReportRuntimeError */
#include "Det.h"
#endif

/* Included for declaration of the function Dem_ReportErrorStatus(AR422), Dem_SetEventStatus(AR2211) */
#include "Dem.h"

#if (FR_59_RENESAS_CRITICAL_SECTION_PROTECTION == STD_ON)
/* Included for the declaration of the critical section protection functions */
#include "SchM_Fr_59_Renesas.h"
#endif

/**
 * include os
*/
#if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
#include "Os.h"
#endif

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/

/* AUTOSAR Release version information */
#define FR_59_RENESAS_C_AR_RELEASE_MAJOR_VERSION    FR_59_RENESAS_AR_RELEASE_MAJOR_VERSION_VALUE
#define FR_59_RENESAS_C_AR_RELEASE_MINOR_VERSION    FR_59_RENESAS_AR_RELEASE_MINOR_VERSION_VALUE
#define FR_59_RENESAS_C_AR_RELEASE_REVISION_VERSION FR_59_RENESAS_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define FR_59_RENESAS_C_SW_MAJOR_VERSION            FR_59_RENESAS_SW_MAJOR_VERSION_VALUE
#define FR_59_RENESAS_C_SW_MINOR_VERSION            FR_59_RENESAS_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (FR_59_RENESAS_AR_RELEASE_MAJOR_VERSION != FR_59_RENESAS_C_AR_RELEASE_MAJOR_VERSION)
  #error "Fr_59_Renesas.c : Mismatch in Release Major Version"
#endif

#if (FR_59_RENESAS_AR_RELEASE_MINOR_VERSION != FR_59_RENESAS_C_AR_RELEASE_MINOR_VERSION)
  #error "Fr_59_Renesas.c : Mismatch in Release Minor Version"
#endif

#if (FR_59_RENESAS_AR_RELEASE_REVISION_VERSION != FR_59_RENESAS_C_AR_RELEASE_REVISION_VERSION)
  #error "Fr_59_Renesas.c : Mismatch in Release Revision Version"
#endif

#if (FR_59_RENESAS_SW_MAJOR_VERSION != FR_59_RENESAS_C_SW_MAJOR_VERSION)
  #error "Fr_59_Renesas.c : Mismatch in Software Major Version"
#endif

#if (FR_59_RENESAS_SW_MINOR_VERSION != FR_59_RENESAS_C_SW_MINOR_VERSION)
  #error "Fr_59_Renesas.c : Mismatch in Software Minor Version"
#endif

/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:1338)    : The parameter '%s' is being modified.                                                        */
/* Rule                : MISRA C:2012 Rule-17.8                                                                       */
/* JV-01 Justification : This in case, parameter is not const, it could be accepted for modification                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1503)    : The function '%1s' is defined but is not used within this project.                           */
/* Rule                : CERTCCM MSC07, MISRA C:2012 Rule-2.1, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : This is accepted, due to the module's API is exported for user's usage.                      */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:2814)    : Possible: Dereference of NULL pointer.                                                       */
/* Rule                : CERTCCM EXP34                                                                                */
/* JV-01 Justification : This is accepted, due to the implementation is following hardware specification.             */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:2824)    : Possible: Arithmetic operation on NULL pointer.                                              */
/* Rule                : CERTCCM EXP34                                                                                */
/* JV-01 Justification : This is accepted, due to the implementation is following hardware specification.             */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:2844)    : Possible: Dereference of an invalid pointer value.                                           */
/* Rule                : CERTCCM ARR30                                                                                */
/* JV-01 Justification : It is specific for device register accessing and confirmed has no issue in software behavior.*/
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (6:2877)    : This loop will never be executed more than once.                                             */
/* Rule                : CERTCCM MSC07, MISRA C:2012 Dir-4.1, CWE Rule CWE-670                                        */
/* JV-01 Justification : This loop will only be executed at least once, depends on user configuration.                */
/*       Verification  : This is Hardware Specification, X2x only provides 1 Unit. So it is not having any impact.    */
/**********************************************************************************************************************/
/* Message (2:2982)    : This assignment is redundant. The value of this object is never used before being modified.  */
/* Rule                : CERTCCM MSC07, MSC13, MISRA C:2012 Rule-2.2, CWE Rule CWE-14, CWE-398, CWE-561, CWE-563      */
/*                       CWE-569, CWE-633                                                                             */
/* JV-01 Justification : The variable needs to be initialized before using it.                                        */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:2985)    : This operation is redundant. The value of the result is always that of the left-hand operand.*/
/* Rule                : CERTCCM MSC07, MSC13, MISRA C:2012 Rule-2.2, CWE Rule CWE-398, CWE-561, CWE-569, CWE-633     */
/* JV-01 Justification : For readability, setting to registers will used redundant macros and is based on hardware    */
/*                       user's manual.                                                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:3383)    : Cannot identify wraparound guard for unsigned arithmetic expression.                         */
/* Rule                : CERTCCM INT30                                                                                */
/* JV-01 Justification : It can still result in values that are out of range for the intended use, as intuitive       */
/*                       "invariants" may not hold.                                                                   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE Rule CWE-398, CWE-569                                            */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is accepted. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3673)    : The object addressed by the pointer parameter '%s' is not modified and so the pointer could  */
/*                       be of type 'pointer to const'.                                                               */
/* Rule                : CERTCCM DCL00, DCL13, MISRA C:2012 Rule-8.13, CWE Rule CWE-398, CWE-569                      */
/* JV-01 Justification : Pointer variable is used to modify the value at the address so the pointer cannot be         */
/*                       declared as 'pointer to const' type.                                                         */
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
/* Message (4:5087)    : Use of #include directive after code fragment.                                               */
/* Rule                : MISRA C:2012 Rule-20.1                                                                       */
/* JV-01 Justification : This is done as per Memory Requirement, (MEMMAP003 - Specification of Memory Mapping).       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/**********************************************************************************************************************/

/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_Init
**
** Service ID            : 0x1c
**
** Description           : This service initialize the Fr driver and
**                         hardware.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : Fr_ConfigPtr Pointer to the configuration
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : None
**
** Preconditions         : None
**
** Global Variables Used : Fr_59_Renesas_GpBufReconfigStatusPtr,
**                         Fr_59_Renesas_GpControllerConfigPtr,
**                         Fr_59_Renesas_GpCtrlRegSet,
**                         Fr_59_Renesas_GpPeriodTimeConfigPtr
**                         Fr_59_Renesas_GaaGetCoreId2Index
**                         Fr_59_Renesas_GaaGetController2CoreIndex
**
** Functions Invoked     : Det_ReportError, Fr_59_Renesas_InitDone
**
** Registers Used        : None
**
** Reference ID          : FR_DUD_ACT_001, FR_DUD_ACT_001_ERR001,
** Reference ID          : FR_DUD_ACT_001_ERR002, FR_DUD_ACT_001_ERR003,
** Reference ID          : FR_DUD_ACT_001_GBL001,
** Reference ID          : FR_DUD_ACT_001_GBL002, FR_DUD_ACT_001_GBL003,
** Reference ID          : FR_DUD_ACT_001_GBL004
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"
FUNC(void, FR_PUBLIC_CODE) Fr_59_Renesas_Init(const Fr_59_Renesas_ConfigType *Fr_ConfigPtr)                             /* PRQA S 1503 # JV-01 */
{
  #if (FR_59_RENESAS_RECONFIG_LPDU == STD_ON) || (FR_59_RENESAS_PREPARE_LPDU == STD_ON) || \
                                                                                 (FR_59_RENESAS_DISABLE_LPDU == STD_ON)
  /* Declare pointer to control table configuration */
  P2CONST(Fr_59_Renesas_CtrlTableType, AUTOMATIC, FR_CONFIG_DATA) LpCtrlTable;
  /* Declare variable to store the index of reconfigurable frame */
  uint16 LusFrameCnt;
  #endif
  /* Declare the variable to store the index of Fr controller */
  uint8 LucCtrlIdx;
  #if ((FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) || (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON))
  uint8 LucCoreIndex;
  #endif
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  uint8 ucCoreId;
  /* Get Core id for code branching */
  ucCoreId = (uint8)GetCoreID();
  /* Covert Core Id to Core Index */
  LucCoreIndex = Fr_59_Renesas_GaaGetCoreId2Index[ucCoreId];                                                            
  #else
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
    /* if Multicore is not configure, default coreid is 0x00
  To optimize implementation */
  LucCoreIndex = FR_59_RENESAS_ZERO;
  #endif
  #endif
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  /* Check invalid core for calling API */
  if (FR_59_RENESAS_INVALID_CORE == LucCoreIndex)
  {
    /* Report to DET */
    (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_INIT_SID,
                                                                                          FR_59_RENESAS_E_INVALID_CORE);
  }
  else
  #endif
  /* Check whether the input pointer is null */
  if (NULL_PTR == Fr_ConfigPtr)
  {
    /* Report Error to DET */
    (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_INIT_SID,
                                                                                        FR_59_RENESAS_E_PARAM_POINTER);
  }
  /* Check whether the existing database is correct */
  else if (FR_59_RENESAS_DBTOC_VALUE != Fr_ConfigPtr->ulStartOfDbToc)
  {
    /* Report Error to DET */
    (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_INIT_SID,
                                                                                     FR_59_RENESAS_E_INVALID_DATABASE);
  }
  else
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  /* Assign the config pointer value to global pointer */
  {
    /* Store the global pointer to the controller structure */
    Fr_59_Renesas_GpPeriodTimeConfigPtr = Fr_ConfigPtr->pPeriodTimeConfig;                                              
    Fr_59_Renesas_GpControllerConfigPtr = Fr_ConfigPtr->pControllerConfig;

    for (LucCtrlIdx = FR_59_RENESAS_ZERO; LucCtrlIdx < FR_59_RENESAS_NUM_CTRL_SUPPORTED; LucCtrlIdx++)                  /* PRQA S 2877 # JV-01 */      
    #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
    {
    if (LucCoreIndex == Fr_59_Renesas_GaaGetController2CoreIndex[LucCtrlIdx])
    #endif
    {
      /* Initialize global pointer to the Hardware register structure */
      Fr_59_Renesas_GpCtrlRegSet[LucCtrlIdx] = Fr_59_Renesas_GpControllerConfigPtr[LucCtrlIdx].pCtrlReg;
      #if (FR_59_RENESAS_RECONFIG_LPDU == STD_ON) || (FR_59_RENESAS_PREPARE_LPDU == STD_ON) || \
                                                                                 (FR_59_RENESAS_DISABLE_LPDU == STD_ON)
      /* Initialize global pointer of Buffer Reconfig Status */
      Fr_59_Renesas_GpBufReconfigStatusPtr[LucCtrlIdx] = (P2VAR(
              uint16, AUTOMATIC, FR_APPL_DATA))(Fr_59_Renesas_GpControllerConfigPtr[LucCtrlIdx].pBufferReConfigStatus); /* PRQA S 3432 # JV-01 */
      /* Store the global pointer to FlexRay Control Table */
      LpCtrlTable = (P2CONST(Fr_59_Renesas_CtrlTableType, AUTOMATIC,
                                          FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[LucCtrlIdx].pCtrlTable);
      /* Initialize the value invalid LPdu index for all reconfigured frame */
      for (LusFrameCnt = FR_59_RENESAS_ZERO; LusFrameCnt < LpCtrlTable->usMaxFrames; LusFrameCnt++)                     
      {
        Fr_59_Renesas_GpBufReconfigStatusPtr[LucCtrlIdx][LusFrameCnt] = FR_59_RENESAS_INVALID_LPDUID;
      }
      #endif
    }
    #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
    }
    #endif
    #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
    Fr_59_Renesas_InitDone(LucCoreIndex);
    #endif
  }
} /* End of API Fr_59_Renesas_Init */
#define FR_59_RENESAS_STOP_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_ControllerInit
**
** Service ID            : 0x00
**
** Description           : This service configures all the cluster and node
**                         related parameters and sets the CC in
**                         POC:Config state
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : The FlexRay Driver module should be initialized.
**
** Global Variables Used : Fr_59_Renesas_GpControllerConfigPtr,
**                         Fr_59_Renesas_GaaGlobalAccPoint
**                         Fr_59_Renesas_GaaGetCoreId2Index
**                         Fr_59_Renesas_GaaGetController2CoreIndex
**
** Functions Invoked     : Det_ReportError,
**                         Fr_59_Renesas_LoadCfgLowLevelParameters,
**                         Fr_59_Renesas_CfgBuffer, Fr_59_Renesas_CheckCCConfig,
**                         Fr_59_Renesas_OperationEnable,
**                         Fr_59_Renesas_SwitchCCToConfig,
**                         Fr_59_Renesas_UnlockSequence,
**                         Fr_59_Renesas_WriteCHICmd,
**
** Registers Used        : None
**
** Reference ID          : FR_DUD_ACT_002, FR_DUD_ACT_002_ERR001,
** Reference ID          : FR_DUD_ACT_002_ERR002, FR_DUD_ACT_002_ERR003
** Reference ID          : FR_DUD_ACT_002_CRT001, FR_DUD_ACT_002_CRT002
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PUBLIC_CODE) Fr_59_Renesas_ControllerInit(uint8 Fr_CtrlIdx)                                     /* PRQA S 1503 # JV-01 */
{
  /* Declare local pointer to Low Level configuration */
  P2CONST(Fr_59_Renesas_LowLevelConfSetType, TYPEDEF, FR_CONFIG_DATA) LpLowLevelConfigPtr;
  /* Declare the variable to store the return value */
  Std_ReturnType LucReturnValue;
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  /* Declare the variable to store the DET return value */
  boolean LblErrDetect;
  /* Declare the variable to store the core index */
  uint8 LucCoreIndex;
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  uint8 ucCoreId;
  /* Get Core id for code branching */
  ucCoreId = (uint8)GetCoreID();
  /* Covert Core Id to Core Index */
  LucCoreIndex = Fr_59_Renesas_GaaGetCoreId2Index[ucCoreId];                                                            
  #else
  /* if Multicore is not configure, default coreid is 0x00
    To optimize implementation */
  LucCoreIndex = FR_59_RENESAS_ZERO;
  #endif /* (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON) */
  /* Initialize development detection flag */
  LblErrDetect = FR_59_RENESAS_FALSE;
  #endif /* (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  /* Initialize the return value */
  LucReturnValue = E_OK;                                                                                                /* PRQA S 2982 # JV-01 */
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  /* Check invalid core for calling API */
  if (FR_59_RENESAS_INVALID_CORE == LucCoreIndex)
  {
    /* Report to DET */
    (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_CONTROLLER_INIT_SID,
                                                                                          FR_59_RENESAS_E_INVALID_CORE);
    /* Default error is detected */
    LblErrDetect = FR_59_RENESAS_TRUE;
  }
  else
  #endif
  {
    /* Check if the module is initialized */
    if (FR_59_RENESAS_FALSE == *(Fr_59_Renesas_GaaGlobalAccPoint[LucCoreIndex].pInitDone))                              
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_CONTROLLER_INIT_SID,
                                                                                          FR_59_RENESAS_E_INIT_FAILED);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    } /* else No Action required */
    /* Check if the controller index is greater than the number of controller configured */
    if (FR_59_RENESAS_NUM_CTRL_SUPPORTED <= Fr_CtrlIdx)
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_CONTROLLER_INIT_SID,
                                                                                          FR_59_RENESAS_E_INV_CTRL_IDX);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    }
    else
    {
      #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
      /* Check invalid core for calling API */
      if (LucCoreIndex != Fr_59_Renesas_GaaGetController2CoreIndex[Fr_CtrlIdx])
      {
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_CONTROLLER_INIT_SID,
                                                                                         FR_59_RENESAS_E_INVALID_CORE);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
      }
      #endif
    }
  }
  /* Check if no any DET error has occurred */
  if (FR_59_RENESAS_FALSE == LblErrDetect)
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  {
    LpLowLevelConfigPtr = (P2CONST(Fr_59_Renesas_LowLevelConfSetType, TYPEDEF,
                                     FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pLowLevelConfig);
    LucReturnValue = Fr_59_Renesas_OperationEnable(Fr_CtrlIdx);
    if (E_OK == LucReturnValue)
    {
      LucReturnValue = Fr_59_Renesas_SwitchCCToConfig(Fr_CtrlIdx);
      if (E_OK == LucReturnValue)
      {
        /* Configure Low Level Parameters of the CC */
        LucReturnValue = Fr_59_Renesas_LoadCfgLowLevelParameters(Fr_CtrlIdx, LpLowLevelConfigPtr);
        if (E_OK == LucReturnValue)
        {
          /* Configure message buffers */
          LucReturnValue = Fr_59_Renesas_CfgBuffer(Fr_CtrlIdx);
          /* Check if the buffer value configuration is success */
          if (E_OK == LucReturnValue)
          {
            /* Check if critical section protection is required */
            #if (FR_59_RENESAS_CRITICAL_SECTION_PROTECTION == STD_ON)
            /* Enter the Critical Section Area */
            FR_59_RENESAS_ENTER_CRITICAL_SECTION(FR_INTERRUPT_CONTROL_PROTECTION);
            #endif
            /* Execute the unlock sequence */
            Fr_59_Renesas_UnlockSequence(Fr_CtrlIdx);
            /* Command READY: CONFIG to READY state */
            LucReturnValue = Fr_59_Renesas_WriteCHICmd(Fr_CtrlIdx, FR_59_RENESAS_READY);
            /* Check if critical section protection is required */
            #if (FR_59_RENESAS_CRITICAL_SECTION_PROTECTION == STD_ON)
            /* Exit the Critical Section Area */
            FR_59_RENESAS_EXIT_CRITICAL_SECTION(FR_INTERRUPT_CONTROL_PROTECTION);
            #endif
            if (E_OK == LucReturnValue)
            {
              /* Command FR_59_RENESAS_RESET_STATUS_INDICATORS to reset
                                                             FLXAnFRCCSV.CSNI, FLXAnFRCCSV.CSAI, and FLXAnFRCCSV.WSV */
              LucReturnValue = Fr_59_Renesas_WriteCHICmd(Fr_CtrlIdx, FR_59_RENESAS_RESET_STATUS_INDICATORS);
              if (E_OK == LucReturnValue)
              {
                /* Perform CC Test */
                LucReturnValue = Fr_59_Renesas_CheckCCConfig(Fr_CtrlIdx, LpLowLevelConfigPtr);
              } /* else No Action required */
            } /* else No Action required */
          } /* else No Action required */
        } /* else No Action required */
      } /* else No Action required */
    } /* else No Action required */
  }
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  else
  {
    LucReturnValue = E_NOT_OK;
  }
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  /* Return the value */
  return (LucReturnValue);
} /* End of API Fr_59_Renesas_ControllerInit */
#define FR_59_RENESAS_STOP_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_StartCommunication
**
** Service ID            : 0x03
**
** Description           : This service invokes the RUN command and set the CC
**                         in POC:Normal Active or POC:Normal Passive state
**
** Sync/Async            : Asynchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : The POC state of communication controller should be
**                         in READY POCState
**
** Global Variables Used : Fr_59_Renesas_GpControllerConfigPtr,
**                         Fr_59_Renesas_GaaGlobalAccPoint
**                         Fr_59_Renesas_GaaGetCoreId2Index
**                         Fr_59_Renesas_GaaGetController2CoreIndex
**
** Functions Invoked     : Det_ReportError,
**                         FR_59_RENESAS_DEM_REPORT_ERROR,
**                         Det_ReportRuntimeError(AR2211),
**                         Fr_59_Renesas_GetPOCStsFlag,
**                         Fr_59_Renesas_WriteCHICmd
**
** Registers Used        : None
**
** Reference ID          : FR_DUD_ACT_003, FR_DUD_ACT_003_ERR001,
** Reference ID          : FR_DUD_ACT_003_ERR002, FR_DUD_ACT_003_ERR003,
** Reference ID          : FR_DUD_ACT_003_ERR004, FR_DUD_ACT_003_ERR005, FR_DUD_ACT_003_ERR006
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PUBLIC_CODE) Fr_59_Renesas_StartCommunication(uint8 Fr_CtrlIdx)                                 /* PRQA S 1503 # JV-01 */
{
  uint32 LulData;
  /* Declare the variable to store the return value */
  Std_ReturnType LucReturnValue;
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  /* Declare the variable to store the DET return value */
  boolean LblErrDetect;
  /* Declare the variable to store the core index */
  uint8 LucCoreIndex;
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  uint8 ucCoreId;
  /* Get Core id for code branching */
  ucCoreId = (uint8)GetCoreID();
  /* Covert Core Id to Core Index */
  LucCoreIndex = Fr_59_Renesas_GaaGetCoreId2Index[ucCoreId];                                                            
  #else
  /* if Multicore is not configure, default coreid is 0x00
    To optimize implementation */
  LucCoreIndex = FR_59_RENESAS_ZERO;
  #endif
  /* Initialize development detection flag */
  LblErrDetect = FR_59_RENESAS_FALSE;
  #endif
  #if ((FR_59_RENESAS_DEV_ERROR_DETECT != STD_ON) && (FR_59_RENESAS_AR_VERSION == FR_59_RENESAS_AR_422_VERSION))
  P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF, FR_CONFIG_DATA) LpDemEventId;
  #endif
  /* Initialize the return value */
  LucReturnValue = E_OK;                                                                                                /* PRQA S 2982 # JV-01 */
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  /* Check invalid core for calling API */
  if (FR_59_RENESAS_INVALID_CORE == LucCoreIndex)
  {
    /* Report to DET */
    (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_STARTCOMMUNICATION_SID,
                                                                                          FR_59_RENESAS_E_INVALID_CORE);
    /* Default error is detected */
    LblErrDetect = FR_59_RENESAS_TRUE;
  }
  else
  #endif
  {
    /* Check if the module is initialized */
    if (FR_59_RENESAS_FALSE == *(Fr_59_Renesas_GaaGlobalAccPoint[LucCoreIndex].pInitDone))                              
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_STARTCOMMUNICATION_SID,
                                                                                         FR_59_RENESAS_E_INIT_FAILED);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    } /* else No Action required */
    /* Check if the controller index is greater than the number of controller configured */
    if (FR_59_RENESAS_NUM_CTRL_SUPPORTED <= Fr_CtrlIdx)
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_STARTCOMMUNICATION_SID,
                                                                                        FR_59_RENESAS_E_INV_CTRL_IDX);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    }
    else
    {
      #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
      /* Check invalid core for calling API */
      if (LucCoreIndex != Fr_59_Renesas_GaaGetController2CoreIndex[Fr_CtrlIdx])
      {
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_STARTCOMMUNICATION_SID,
                                                                                         FR_59_RENESAS_E_INVALID_CORE);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
      }
      #endif
    }
  }
  /* Check if any DET error has occurred */
  if (FR_59_RENESAS_FALSE == LblErrDetect)
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Read the POC state by getting the FRCCSV register value */
    LulData = Fr_59_Renesas_GetPOCStsFlag(Fr_CtrlIdx);
    /* Check if POC is not in READY State */
    if (FR_59_RENESAS_READY_STATE != LulData)
    {
      #if (FR_59_RENESAS_AR_VERSION == FR_59_RENESAS_AR_422_VERSION)
      #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_STARTCOMMUNICATION_SID,
                                                                                         FR_59_RENESAS_E_INV_POCSTATE);
      #else /* FR_59_RENESAS_DEV_ERROR_DETECT == STD_OFF */
      LpDemEventId = (P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF,
                                         FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pDemEventId);
      if (FR_59_RENESAS_DEM_NOT_CONFIGURED != LpDemEventId->usHardwareTestFailure)
      {
        FR_59_RENESAS_DEM_REPORT_ERROR(LpDemEventId->usHardwareTestFailure, DEM_EVENT_STATUS_FAILED);
      } /* else No Action required */

      #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
      #endif /* #if (FR_59_RENESAS_AR_VERSION == FR_59_RENESAS_AR_422_VERSION)*/
      #if (FR_59_RENESAS_AR_VERSION == FR_59_RENESAS_AR_R22_11_VERSION)
      /* Report to DET */
      (void)Det_ReportRuntimeError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID,
                                                   FR_59_RENESAS_STARTCOMMUNICATION_SID, FR_59_RENESAS_E_INV_POCSTATE);
      #endif /* #if (FR_59_RENESAS_AR_VERSION == FR_59_RENESAS_AR_R22_11_VERSION) */
      /* Set return value to E_NOT_OK */
      LucReturnValue = E_NOT_OK;
    }
    else
    {
      /* Update the command in Configuration register */
      LucReturnValue = Fr_59_Renesas_WriteCHICmd(Fr_CtrlIdx, FR_59_RENESAS_RUN);
    }
  }
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  else
  {
    LucReturnValue = E_NOT_OK;
  }
  #endif /* End of (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  /* Return the value */
  return (LucReturnValue);
} /* End of API Fr_59_Renesas_StartCommunication */
#define FR_59_RENESAS_STOP_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_AllowColdstart
**
** Service ID            : 0x23
**
** Description           : This service invokes the CC CHI command
**                         'ALLOW_COLDSTART'.
**
** Sync/Async            : Asynchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : The POC state of communication controller should be
**                         in POC:ready or POC:startup
**
** Global Variables Used : Fr_59_Renesas_GaaGlobalAccPoint,
**                         Fr_59_Renesas_GpControllerConfigPtr
**                         Fr_59_Renesas_GaaGetCoreId2Index
**                         Fr_59_Renesas_GaaGetController2CoreIndex
**
** Functions Invoked     : Det_ReportError,
**                         FR_59_RENESAS_DEM_REPORT_ERROR,
**                         Det_ReportRuntimeError(AR2211),
**                         Fr_59_Renesas_GetPOCStsFlag,
**                         Fr_59_Renesas_WriteCHICmd
**
** Registers Used        : None
**
** Reference ID          : FR_DUD_ACT_004, FR_DUD_ACT_004_ERR001,
** Reference ID          : FR_DUD_ACT_004_ERR002, FR_DUD_ACT_004_ERR003,
** Reference ID          : FR_DUD_ACT_004_ERR004, FR_DUD_ACT_004_ERR005,
** Reference ID          : FR_DUD_ACT_004_ERR006, FR_DUD_ACT_004_ERR007
***********************************************************************************************************************/

#define FR_59_RENESAS_START_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PUBLIC_CODE) Fr_59_Renesas_AllowColdstart(uint8 Fr_CtrlIdx)                                     /* PRQA S 1503 # JV-01 */
{
  uint32 LulData;
  /* Declare the variable to store the return value */
  Std_ReturnType LucReturnValue;
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  /* Declare local pointer to Control Table */
  P2CONST(Fr_59_Renesas_CtrlTableType, TYPEDEF, FR_CONFIG_DATA) LpCtrlTable;
  /* Declare the variable to store the DET return value */
  boolean LblErrDetect;
  /* Declare the variable to store the core index */
  uint8 LucCoreIndex;
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  uint8 ucCoreId;
  /* Get Core id for code branching */
  ucCoreId = (uint8)GetCoreID();
  /* Covert Core Id to Core Index */
  LucCoreIndex = Fr_59_Renesas_GaaGetCoreId2Index[ucCoreId];                                                            
  #else
  /* if Multicore is not configure, default coreid is 0x00
    To optimize implementation */
  LucCoreIndex = FR_59_RENESAS_ZERO;
  #endif
  /* Initialize development detection flag */
  LblErrDetect = FR_59_RENESAS_FALSE;
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON ) */
  #if ((FR_59_RENESAS_DEV_ERROR_DETECT != STD_ON) && (FR_59_RENESAS_AR_VERSION == FR_59_RENESAS_AR_422_VERSION))
  P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF, FR_CONFIG_DATA) LpDemEventId;
  #endif
  /* Initialize the return value */
  LucReturnValue = E_OK;                                                                                                /* PRQA S 2982 # JV-01 */
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  /* Check invalid core for calling API */
  if (FR_59_RENESAS_INVALID_CORE == LucCoreIndex)
  {
    /* Report to DET */
    (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_ALLOWCOLDSTART_SID,
                                                                                        FR_59_RENESAS_E_INVALID_CORE);
    /* Default error is detected */
    LblErrDetect = FR_59_RENESAS_TRUE;
  }
  else
  #endif
  {
    /* Check if the module is initialized */
    if (FR_59_RENESAS_FALSE == *(Fr_59_Renesas_GaaGlobalAccPoint[LucCoreIndex].pInitDone))                              
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_ALLOWCOLDSTART_SID,
                                                                                          FR_59_RENESAS_E_INIT_FAILED);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    } /* else No Action required */
    /* Check if the controller index is greater than the number of controller configured */
    if (FR_59_RENESAS_NUM_CTRL_SUPPORTED <= Fr_CtrlIdx)
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_ALLOWCOLDSTART_SID,
                                                                                        FR_59_RENESAS_E_INV_CTRL_IDX);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    }
    else
    {
      #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
      /* Check invalid core for calling API */
      if (LucCoreIndex != Fr_59_Renesas_GaaGetController2CoreIndex[Fr_CtrlIdx])
      {
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_ALLOWCOLDSTART_SID,
                                                                                         FR_59_RENESAS_E_INVALID_CORE);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
      }
      #endif
    }
  }
  /* Check if any DET error has occurred */
  if (FR_59_RENESAS_FALSE == LblErrDetect)
  {
    /* Check if the controller is not allowed to lead coldstart */
    /* Store the global pointer to FlexRay Control Table */
    LpCtrlTable = (P2CONST(Fr_59_Renesas_CtrlTableType, AUTOMATIC,
                                          FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pCtrlTable);
    if (FR_59_RENESAS_FALSE == LpCtrlTable->blAllowColdStart)                                                           
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_ALLOWCOLDSTART_SID,
                                                                                      FR_59_RENESAS_E_INV_CHI_COMMAND);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    } /* else No Action required */
  } /* else No Action required */
  /* Check if any DET error has occurred */
  if (FR_59_RENESAS_FALSE == LblErrDetect)
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Read the POC state by getting the FRCCSV register value */
    LulData = Fr_59_Renesas_GetPOCStsFlag(Fr_CtrlIdx);
    /* Check if POC is not in READY State */
    if ((FR_59_RENESAS_DEFAULT_CONFIG_STATE == LulData) || (FR_59_RENESAS_CONFIG_STATE == LulData) ||
                                                                                 (FR_59_RENESAS_HALT_STATE == LulData))
    {
      #if (FR_59_RENESAS_AR_VERSION == FR_59_RENESAS_AR_422_VERSION)
      #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_ALLOWCOLDSTART_SID,
                                                                                         FR_59_RENESAS_E_INV_POCSTATE);
      #else /* FR_59_RENESAS_DEV_ERROR_DETECT == STD_OFF */
      LpDemEventId = (P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF,
                                         FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pDemEventId);
      if (FR_59_RENESAS_DEM_NOT_CONFIGURED != LpDemEventId->usHardwareTestFailure)
      {
        FR_59_RENESAS_DEM_REPORT_ERROR(LpDemEventId->usHardwareTestFailure, DEM_EVENT_STATUS_FAILED);
      } /* else No Action required */

      #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
      #endif /* #if (FR_59_RENESAS_AR_VERSION == FR_59_RENESAS_AR_422_VERSION)*/
      #if (FR_59_RENESAS_AR_VERSION == FR_59_RENESAS_AR_R22_11_VERSION)
      /* Report to DET */
      (void)Det_ReportRuntimeError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, 
                                                        FR_59_RENESAS_ALLOWCOLDSTART_SID,FR_59_RENESAS_E_INV_POCSTATE);
      #endif /* #if (FR_59_RENESAS_AR_VERSION == FR_59_RENESAS_AR_R22_11_VERSION) */
      /* Set return value to E_NOT_OK */
      LucReturnValue = E_NOT_OK;
    }
    else
    {
      /* Update the command in Configuration register */
      LucReturnValue = Fr_59_Renesas_WriteCHICmd(Fr_CtrlIdx, FR_59_RENESAS_ALLOW_COLDSTART);
    }
  }
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  else
  {
    LucReturnValue = E_NOT_OK;
  }
  #endif /* End of (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  return (LucReturnValue);
} /* End of API Fr_59_Renesas_AllowColdstart */
#define FR_59_RENESAS_STOP_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_AllSlots
**
** Service ID            : 0x24
**
** Description           : This service invokes the CC CHI command
**                         'ALL_SLOTS'.
**
** Sync/Async            : Asynchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : The POC state of communication controller should be
**                         either NORMAL ACTIVE or NORMAL PASSIVE
**
** Global Variables Used : Fr_59_Renesas_GaaGlobalAccPoint,
**                         Fr_59_Renesas_GpControllerConfigPtr
**                         Fr_59_Renesas_GaaGetCoreId2Index
**                         Fr_59_Renesas_GaaGetController2CoreIndex
**
** Functions Invoked     : Det_ReportError,
**                         FR_59_RENESAS_DEM_REPORT_ERROR,
**                         Det_ReportRuntimeError(AR2211),
**                         Fr_59_Renesas_GetPOCStsFlag,
**                         Fr_59_Renesas_WriteCHICmd
**
** Registers Used        : None
**
** Reference ID          : FR_DUD_ACT_005, FR_DUD_ACT_005_ERR001,
** Reference ID          : FR_DUD_ACT_005_ERR002, FR_DUD_ACT_005_ERR003,
** Reference ID          : FR_DUD_ACT_005_ERR004, FR_DUD_ACT_005_ERR005, FR_DUD_ACT_005_ERR006
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PUBLIC_CODE) Fr_59_Renesas_AllSlots(uint8 Fr_CtrlIdx)                                           /* PRQA S 1503 # JV-01 */
{
  uint32 LulData;
  /* Declare the variable to store the return value */
  Std_ReturnType LucReturnValue;
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  /* Declare the variable to store the DET return value */
  boolean LblErrDetect;
  /* Declare the variable to store the core index */
  uint8 LucCoreIndex;
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  uint8 ucCoreId;
  /* Get Core id for code branching */
  ucCoreId = (uint8)GetCoreID();
  /* Covert Core Id to Core Index */
  LucCoreIndex = Fr_59_Renesas_GaaGetCoreId2Index[ucCoreId];                                                            
  #else
  /* if Multicore is not configure, default coreid is 0x00
    To optimize implementation */
  LucCoreIndex = FR_59_RENESAS_ZERO;
  #endif
  /* Initialize development detection flag */
  LblErrDetect = FR_59_RENESAS_FALSE;
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  #if ((FR_59_RENESAS_DEV_ERROR_DETECT != STD_ON) && (FR_59_RENESAS_AR_VERSION == FR_59_RENESAS_AR_422_VERSION))
  P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF, FR_CONFIG_DATA) LpDemEventId;
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */

  /* Initialize the return value */
  LucReturnValue = E_OK;                                                                                                /* PRQA S 2982 # JV-01 */

  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  /* Check invalid core for calling API */
  if (FR_59_RENESAS_INVALID_CORE == LucCoreIndex)
  {
    /* Report to DET */
    (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_ALLSLOTS_SID,
                                                                                          FR_59_RENESAS_E_INVALID_CORE);
    /* Default error is detected */
    LblErrDetect = FR_59_RENESAS_TRUE;
  }
  else
  #endif
  {
    /* Check if the module is initialized */
    if (FR_59_RENESAS_FALSE == *(Fr_59_Renesas_GaaGlobalAccPoint[LucCoreIndex].pInitDone))                              
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_ALLSLOTS_SID,
                                                                                        FR_59_RENESAS_E_INIT_FAILED);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    } /* else No Action required */
    /* Check if the controller index is greater than the number of controller configured */
    if (FR_59_RENESAS_NUM_CTRL_SUPPORTED <= Fr_CtrlIdx)
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_ALLSLOTS_SID,
                                                                                       FR_59_RENESAS_E_INV_CTRL_IDX);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    }
    else
    {
      #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
      /* Check invalid core for calling API */
      if (LucCoreIndex != Fr_59_Renesas_GaaGetController2CoreIndex[Fr_CtrlIdx])
      {
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_ALLSLOTS_SID,
                                                                                         FR_59_RENESAS_E_INVALID_CORE);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
      }
      #endif
    }
  }
  /* Check if any DET error has occurred */
  if (FR_59_RENESAS_FALSE == LblErrDetect)
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Read the POC state by getting the FRCCSV register value */
    LulData = Fr_59_Renesas_GetPOCStsFlag(Fr_CtrlIdx);
    /* Check if POC is not in READY State */
    if ((FR_59_RENESAS_NORMAL_ACTIVE_STATE != LulData) && (FR_59_RENESAS_NORMAL_PASSIVE_STATE != LulData))
    {
      #if (FR_59_RENESAS_AR_VERSION == FR_59_RENESAS_AR_422_VERSION)
      #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_ALLSLOTS_SID,
                                                                                         FR_59_RENESAS_E_INV_POCSTATE);
      #else /* FR_59_RENESAS_DEV_ERROR_DETECT == STD_OFF */
      LpDemEventId = (P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF,
                                         FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pDemEventId);
      if (FR_59_RENESAS_DEM_NOT_CONFIGURED != LpDemEventId->usHardwareTestFailure)
      {
        FR_59_RENESAS_DEM_REPORT_ERROR(LpDemEventId->usHardwareTestFailure, DEM_EVENT_STATUS_FAILED);
      } /* else No Action required */

      #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
      #endif /* #if (FR_59_RENESAS_AR_VERSION == FR_59_RENESAS_AR_422_VERSION)*/
      #if (FR_59_RENESAS_AR_VERSION == FR_59_RENESAS_AR_R22_11_VERSION)
      /* Report to DET */
      (void)Det_ReportRuntimeError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_ALLSLOTS_SID,
                                                                                         FR_59_RENESAS_E_INV_POCSTATE);
      #endif /* #if (FR_59_RENESAS_AR_VERSION == FR_59_RENESAS_AR_R22_11_VERSION) */
      /* Set return value to E_NOT_OK */
      LucReturnValue = E_NOT_OK;
    }
    else
    {
      /* Update the command in Configuration register */
      LucReturnValue = Fr_59_Renesas_WriteCHICmd(Fr_CtrlIdx, FR_59_RENESAS_ALL_SLOTS);
    }
  }
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  else
  {
    LucReturnValue = E_NOT_OK;
  }
  #endif /* End of (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  return (LucReturnValue);
} /* End of API Fr_59_Renesas_AllSlots */
#define FR_59_RENESAS_STOP_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_HaltCommunication
**
** Service ID            : 0x04
**
** Description           : This service invokes the CC CHI command
**                         'DEFERRED_HALT' or 'HALT'.
**
** Sync/Async            : Asynchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : The POC state of communication controller should be
**                         either NORMAL ACTIVE or NORMAL PASSIVE
**
** Global Variables Used : Fr_59_Renesas_GaaGlobalAccPoint,
**                         Fr_59_Renesas_GpControllerConfigPtr
**                         Fr_59_Renesas_GaaGetCoreId2Index
**                         Fr_59_Renesas_GaaGetController2CoreIndex
**
** Functions Invoked     : Det_ReportError,
**                         FR_59_RENESAS_DEM_REPORT_ERROR,
**                         Det_ReportRuntimeError(AR2211),
**                         Fr_59_Renesas_GetPOCStsFlag,
**                         Fr_59_Renesas_WriteCHICmd
**
** Registers Used        : None
**
** Reference ID          : FR_DUD_ACT_006, FR_DUD_ACT_006_ERR001,
** Reference ID          : FR_DUD_ACT_006_ERR002, FR_DUD_ACT_006_ERR003,
** Reference ID          : FR_DUD_ACT_006_ERR004, FR_DUD_ACT_006_ERR005, FR_DUD_ACT_006_ERR006
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PUBLIC_CODE) Fr_59_Renesas_HaltCommunication(uint8 Fr_CtrlIdx)                                  /* PRQA S 1503 # JV-01 */
{
  uint32 LulData;
  /* Declare the variable to store the return value */
  Std_ReturnType LucReturnValue;
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  /* Declare the variable to store the DET return value */
  boolean LblErrDetect;
  /* Declare the variable to store the core index */
  uint8 LucCoreIndex;
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  uint8 ucCoreId;
  /* Get Core id for code branching */
  ucCoreId = (uint8)GetCoreID();
  /* Covert Core Id to Core Index */
  LucCoreIndex = Fr_59_Renesas_GaaGetCoreId2Index[ucCoreId];                                                            
  #else
  /* if Multicore is not configure, default coreid is 0x00
    To optimize implementation */
  LucCoreIndex = FR_59_RENESAS_ZERO;
  #endif
  /* Initialize development detection flag */
  LblErrDetect = FR_59_RENESAS_FALSE;
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  #if ((FR_59_RENESAS_DEV_ERROR_DETECT != STD_ON) && (FR_59_RENESAS_AR_VERSION == FR_59_RENESAS_AR_422_VERSION))
  P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF, FR_CONFIG_DATA) LpDemEventId;
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  /* Initialize the return value */
  LucReturnValue = E_OK;                                                                                                /* PRQA S 2982 # JV-01 */
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  /* Check invalid core for calling API */
  if (FR_59_RENESAS_INVALID_CORE == LucCoreIndex)
  {
    /* Report to DET */
    (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_HALTCOMMUNICATION_SID,
                                                                                        FR_59_RENESAS_E_INVALID_CORE);
    /* Default error is detected */
  LblErrDetect = FR_59_RENESAS_TRUE;
  }
  else
  #endif
  {
    /* Check if the module is initialized */
    if (FR_59_RENESAS_FALSE == *(Fr_59_Renesas_GaaGlobalAccPoint[LucCoreIndex].pInitDone))                              
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_HALTCOMMUNICATION_SID,
                                                                                         FR_59_RENESAS_E_INIT_FAILED);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    } /* else No Action required */
    /* Check if the controller index is greater than the number of controller configured */
    if (FR_59_RENESAS_NUM_CTRL_SUPPORTED <= Fr_CtrlIdx)
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_HALTCOMMUNICATION_SID,
                                                                                      FR_59_RENESAS_E_INV_CTRL_IDX);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    }
    else
    {
      #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
      /* Check invalid core for calling API */
      if (LucCoreIndex != Fr_59_Renesas_GaaGetController2CoreIndex[Fr_CtrlIdx])
      {
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_HALTCOMMUNICATION_SID,
                                                                                        FR_59_RENESAS_E_INVALID_CORE);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
      }
      #endif
    }
  }
  /* Check if any DET error has occurred */
  if (FR_59_RENESAS_FALSE == LblErrDetect)
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Read the POC state by getting the FRCCSV register value */
    LulData = Fr_59_Renesas_GetPOCStsFlag(Fr_CtrlIdx);
    /* Check if POC is not in READY State */
    if ((FR_59_RENESAS_NORMAL_ACTIVE_STATE != LulData) && (FR_59_RENESAS_NORMAL_PASSIVE_STATE != LulData))
    {
      #if (FR_59_RENESAS_AR_VERSION == FR_59_RENESAS_AR_422_VERSION)
      #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_HALTCOMMUNICATION_SID,
                                                                                         FR_59_RENESAS_E_INV_POCSTATE);
      #else /* FR_59_RENESAS_DEV_ERROR_DETECT == STD_OFF */
      LpDemEventId = (P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF,
                                        FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pDemEventId);
      if (FR_59_RENESAS_DEM_NOT_CONFIGURED != LpDemEventId->usHardwareTestFailure)
      {
        FR_59_RENESAS_DEM_REPORT_ERROR(LpDemEventId->usHardwareTestFailure, DEM_EVENT_STATUS_FAILED);
      } /* else No Action required */

      #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
      #endif /* #if (FR_59_RENESAS_AR_VERSION == FR_59_RENESAS_AR_422_VERSION)*/
      #if (FR_59_RENESAS_AR_VERSION == FR_59_RENESAS_AR_R22_11_VERSION)
      /* Report to DET */
      (void)Det_ReportRuntimeError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID,
                                                    FR_59_RENESAS_HALTCOMMUNICATION_SID, FR_59_RENESAS_E_INV_POCSTATE);
      #endif /* #if (FR_59_RENESAS_AR_VERSION == FR_59_RENESAS_AR_R22_11_VERSION) */
      /* Set return value to E_NOT_OK */
      LucReturnValue = E_NOT_OK;
    }
    else
    {
      /* Update the command in Configuration register */
      LucReturnValue = Fr_59_Renesas_WriteCHICmd(Fr_CtrlIdx, FR_59_RENESAS_HALT);
    }
  }
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  else
  {
    LucReturnValue = E_NOT_OK;
  }
  #endif /* End of (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  return (LucReturnValue);
} /* End of API Fr_59_Renesas_HaltCommunication */
#define FR_59_RENESAS_STOP_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_AbortCommunication
**
** Service ID            : 0x05
**
** Description           : This service invokes the CC CHI command FREEZE.
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : The FlexRay Driver module should be initialized.
**
** Global Variables Used : Fr_59_Renesas_GaaGlobalAccPoint
**                         Fr_59_Renesas_GaaGetCoreId2Index
**                         Fr_59_Renesas_GaaGetController2CoreIndex
**
** Functions Invoked     : Det_ReportError, Fr_59_Renesas_WriteCHICmd
**
** Registers Used        : None
**
** Reference ID          : FR_DUD_ACT_007, FR_DUD_ACT_007_ERR001,
** Reference ID          : FR_DUD_ACT_007_ERR002, FR_DUD_ACT_007_ERR003
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PUBLIC_CODE) Fr_59_Renesas_AbortCommunication(uint8 Fr_CtrlIdx)                                 /* PRQA S 1503 # JV-01 */
{
  /* Declare the variable to store the return value */
  Std_ReturnType LucReturnValue;
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  /* Declare the variable to store the DET return value */
  boolean LblErrDetect;
  /* Declare the variable to store the core index */
  uint8 LucCoreIndex;
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  uint8 ucCoreId;
  /* Get Core id for code branching */
  ucCoreId = (uint8)GetCoreID();
  /* Covert Core Id to Core Index */
  LucCoreIndex = Fr_59_Renesas_GaaGetCoreId2Index[ucCoreId];                                                            
  #else
  /* if Multicore is not configure, default coreid is 0x00
    To optimize implementation */
  LucCoreIndex = FR_59_RENESAS_ZERO;
  #endif
  /* Initialize development detection flag */
  LblErrDetect = FR_59_RENESAS_FALSE;
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  /* Initialize the return value */
  LucReturnValue = E_OK;                                                                                                /* PRQA S 2982 # JV-01 */
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  /* Check invalid core for calling API */
  if (FR_59_RENESAS_INVALID_CORE == LucCoreIndex)
  {
    /* Report to DET */
    (void)Det_ReportError(FR_59_RENESAS_MODULE_ID,FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_ABORTCOMMUNICATION_SID,
                                                                                        FR_59_RENESAS_E_INVALID_CORE);
    /* Default error is detected */
    LblErrDetect = FR_59_RENESAS_TRUE;
  }
  else
  #endif
  {
    /* Check if the module is initialized */
    if (FR_59_RENESAS_FALSE == *(Fr_59_Renesas_GaaGlobalAccPoint[LucCoreIndex].pInitDone))                              
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_ABORTCOMMUNICATION_SID,
                                                                                         FR_59_RENESAS_E_INIT_FAILED);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    } /* else No Action required */
    /* Check if the controller index is greater than the number of controller configured */
    if (FR_59_RENESAS_NUM_CTRL_SUPPORTED <= Fr_CtrlIdx)
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_ABORTCOMMUNICATION_SID,
                                                                                         FR_59_RENESAS_E_INV_CTRL_IDX);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    }
    else
    {
      #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
      /* Check invalid core for calling API */
      if (LucCoreIndex != Fr_59_Renesas_GaaGetController2CoreIndex[Fr_CtrlIdx])
      {
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_ABORTCOMMUNICATION_SID,
                                                                                         FR_59_RENESAS_E_INVALID_CORE);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
      }
      #endif
    }
  }
  /* Check if any DET error has occurred */
  if (FR_59_RENESAS_FALSE == LblErrDetect)
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Update the command in Configuration register */
    LucReturnValue = Fr_59_Renesas_WriteCHICmd(Fr_CtrlIdx, FR_59_RENESAS_FREEZE);
  }
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  else
  {
    LucReturnValue = E_NOT_OK;
  }
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  /* Return the value */
  return (LucReturnValue);
} /* End of API Fr_59_Renesas_AbortCommunication */
#define FR_59_RENESAS_STOP_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_SendWUP
**
** Service ID            : 0x06
**
** Description           : This service sends a wakeup pattern on the configured
**                         channel
**
** Sync/Async            : Asynchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : The POC state of Communication Controller should be
**                         in READY.
**
** Global Variables Used : Fr_59_Renesas_GaaGlobalAccPoint,
**                         Fr_59_Renesas_GpControllerConfigPtr
**                         Fr_59_Renesas_GaaGetCoreId2Index
**                         Fr_59_Renesas_GaaGetController2CoreIndex
**
** Functions Invoked     : Det_ReportError,
**                         FR_59_RENESAS_DEM_REPORT_ERROR,
**                         Det_ReportRuntimeError(AR2211),
**                         Fr_59_Renesas_GetPOCStsFlag,
**                         Fr_59_Renesas_WriteCHICmd
**
** Registers Used        : None
**
** Reference ID          : FR_DUD_ACT_008, FR_DUD_ACT_008_ERR001,
** Reference ID          : FR_DUD_ACT_008_ERR002, FR_DUD_ACT_008_ERR003,
** Reference ID          : FR_DUD_ACT_008_ERR004, FR_DUD_ACT_008_ERR005, FR_DUD_ACT_008_ERR006
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PUBLIC_CODE) Fr_59_Renesas_SendWUP(uint8 Fr_CtrlIdx)                                            /* PRQA S 1503 # JV-01 */
{
  uint32 LulData;
  /* Declare the variable to store the return value */
  Std_ReturnType LucReturnValue;
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  /* Declare the variable to store the DET return value */
  boolean LblErrDetect;
  /* Declare the variable to store the core index */
  uint8 LucCoreIndex;
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  uint8 ucCoreId;
  /* Get Core id for code branching */
  ucCoreId = (uint8)GetCoreID();
  /* Covert Core Id to Core Index */
  LucCoreIndex = Fr_59_Renesas_GaaGetCoreId2Index[ucCoreId];                                                            
  #else
  /* if Multicore is not configure, default coreid is 0x00
    To optimize implementation */
  LucCoreIndex = FR_59_RENESAS_ZERO;
  #endif
  /* Initialize development detection flag */
  LblErrDetect = FR_59_RENESAS_FALSE;
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  #if ((FR_59_RENESAS_DEV_ERROR_DETECT != STD_ON) && (FR_59_RENESAS_AR_VERSION == FR_59_RENESAS_AR_422_VERSION))
  P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF, FR_CONFIG_DATA) LpDemEventId;
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */

  /* Initialize the return value */
  LucReturnValue = E_OK;                                                                                                /* PRQA S 2982 # JV-01 */
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  /* Check invalid core for calling API */
  if (FR_59_RENESAS_INVALID_CORE == LucCoreIndex)
  {
    /* Report to DET */
    (void)Det_ReportError(FR_59_RENESAS_MODULE_ID,FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_SENDWUP_SID,
                                                                                        FR_59_RENESAS_E_INVALID_CORE);
    /* Default error is detected */
    LblErrDetect = FR_59_RENESAS_TRUE;
  }
  else
  #endif
  {
    /* Check if the module is initialized */
    if (FR_59_RENESAS_FALSE == *(Fr_59_Renesas_GaaGlobalAccPoint[LucCoreIndex].pInitDone))                              
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_SENDWUP_SID,
                                                                                         FR_59_RENESAS_E_INIT_FAILED);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    } /* else No Action required */
    /* Check if the controller index is greater than the number of controller configured */
    if (FR_59_RENESAS_NUM_CTRL_SUPPORTED <= Fr_CtrlIdx)
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_SENDWUP_SID,
                                                                                      FR_59_RENESAS_E_INV_CTRL_IDX);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    }
    else
    {
      #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
      /* Check invalid core for calling API */
      if (LucCoreIndex != Fr_59_Renesas_GaaGetController2CoreIndex[Fr_CtrlIdx])
      {
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_SENDWUP_SID,
                                                                                        FR_59_RENESAS_E_INVALID_CORE);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
      }
      #endif
    }
  }
  /* Check if any DET error has occurred */
  if (FR_59_RENESAS_FALSE == LblErrDetect)
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Read the POC state by getting the FRCCSV register value */
    LulData = Fr_59_Renesas_GetPOCStsFlag(Fr_CtrlIdx);
    /* Check if POC is not in READY State */
    if (FR_59_RENESAS_READY_STATE != LulData)
    {
      #if (FR_59_RENESAS_AR_VERSION == FR_59_RENESAS_AR_422_VERSION)
      #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_SENDWUP_SID,
                                                                                         FR_59_RENESAS_E_INV_POCSTATE);
      #else /* FR_59_RENESAS_DEV_ERROR_DETECT == STD_OFF */
      LpDemEventId = (P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF,
                                         FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pDemEventId);
      if (FR_59_RENESAS_DEM_NOT_CONFIGURED != LpDemEventId->usHardwareTestFailure)
      {
        FR_59_RENESAS_DEM_REPORT_ERROR(LpDemEventId->usHardwareTestFailure, DEM_EVENT_STATUS_FAILED);
      } /* else No Action required */

      #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
      #endif /* #if (FR_59_RENESAS_AR_VERSION == FR_59_RENESAS_AR_422_VERSION)*/
      #if (FR_59_RENESAS_AR_VERSION == FR_59_RENESAS_AR_R22_11_VERSION)
      /* Report to DET */
      (void)Det_ReportRuntimeError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_SENDWUP_SID,
                                                                                         FR_59_RENESAS_E_INV_POCSTATE);
      #endif /* #if (FR_59_RENESAS_AR_VERSION == FR_59_RENESAS_AR_R22_11_VERSION) */
      /* Set return value to E_NOT_OK */
      LucReturnValue = E_NOT_OK;
    }
    else
    {
      /* Update the command in Configuration register */
      LucReturnValue = Fr_59_Renesas_WriteCHICmd(Fr_CtrlIdx, FR_59_RENESAS_WAKEUP);
    }
  }
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  else
  {
    LucReturnValue = E_NOT_OK;
  }
  #endif /* End of (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  /* Return the value */
  return (LucReturnValue);
} /* End of API Fr_59_Renesas_SendWUP */
#define FR_59_RENESAS_STOP_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_SetWakeupChannel
**
** Service ID            : 0x07
**
** Description           : This service sets a wakeup channel
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx, Fr_ChnlIdx
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : The POC state of Communication Controller should be
**                         in READY.
**
** Global Variables Used : Fr_59_Renesas_GaaGlobalAccPoint,
**                         Fr_59_Renesas_GpControllerConfigPtr
**                         Fr_59_Renesas_GaaGetCoreId2Index
**                         Fr_59_Renesas_GaaGetController2CoreIndex
**
** Functions Invoked     : Det_ReportError, Fr_59_Renesas_CheckIfCCBusy,
**                         FR_59_RENESAS_DEM_REPORT_ERROR,
**                         Det_ReportRuntimeError(AR2211),
**                         Fr_59_Renesas_GetPOCStsFlag,
**                         Fr_59_Renesas_WriteCHICmd,
**                         Fr_59_Renesas_SetWakeupChannelProcess
**
** Registers Used        : None
**
** Reference ID          : FR_DUD_ACT_009, FR_DUD_ACT_009_ERR001,
** Reference ID          : FR_DUD_ACT_009_ERR002, FR_DUD_ACT_009_ERR003,
** Reference ID          : FR_DUD_ACT_009_ERR004, FR_DUD_ACT_009_ERR005,
** Reference ID          : FR_DUD_ACT_009_ERR006, FR_DUD_ACT_009_ERR007
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PUBLIC_CODE) Fr_59_Renesas_SetWakeupChannel(uint8 Fr_CtrlIdx, Fr_ChannelType Fr_ChnlIdx)        /* PRQA S 1503 # JV-01 */
{
  uint32 LulData;
  /* Declare the variable to store the return value */
  Std_ReturnType LucReturnValue;
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  /* Declare the variable to store the DET return value */
  boolean LblErrDetect;
  /* Declare the variable to store the core index */
  uint8 LucCoreIndex;
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  uint8 ucCoreId;
  /* Get Core id for code branching */
  ucCoreId = (uint8)GetCoreID();
  /* Covert Core Id to Core Index */
  LucCoreIndex = Fr_59_Renesas_GaaGetCoreId2Index[ucCoreId];                                                            
  #else
  /* if Multicore is not configure, default coreid is 0x00
    To optimize implementation */
  LucCoreIndex = FR_59_RENESAS_ZERO;
  #endif
  /* Initialize development detection flag */
  LblErrDetect = FR_59_RENESAS_FALSE;
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON )*/
  #if ((FR_59_RENESAS_DEV_ERROR_DETECT != STD_ON) && (FR_59_RENESAS_AR_VERSION == FR_59_RENESAS_AR_422_VERSION))
  P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF, FR_CONFIG_DATA) LpDemEventId;
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  /* Initialize the return value */
  LucReturnValue = E_OK;                                                                                                /* PRQA S 2982 # JV-01 */
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  /* Check invalid core for calling API */
  if (FR_59_RENESAS_INVALID_CORE == LucCoreIndex)
  {
    /* Report to DET */
    (void)Det_ReportError(FR_59_RENESAS_MODULE_ID,FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_SETWAKEUPCHANNEL_SID,
                                                                                        FR_59_RENESAS_E_INVALID_CORE);
    /* Default error is detected */
    LblErrDetect = FR_59_RENESAS_TRUE;
  }
  else
  #endif
  {
    /* Check if the module is initialized */
    if (FR_59_RENESAS_FALSE == *(Fr_59_Renesas_GaaGlobalAccPoint[LucCoreIndex].pInitDone))                              
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_SETWAKEUPCHANNEL_SID,
                                                                                         FR_59_RENESAS_E_INIT_FAILED);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    } /* else No Action required */
    /* Check if the controller index is greater than the number of controller configured */
    if (FR_59_RENESAS_NUM_CTRL_SUPPORTED <= Fr_CtrlIdx)
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_SETWAKEUPCHANNEL_SID,
                                                                                        FR_59_RENESAS_E_INV_CTRL_IDX);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    }
    else
    {
      #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
      /* Check invalid core for calling API */
      if (LucCoreIndex != Fr_59_Renesas_GaaGetController2CoreIndex[Fr_CtrlIdx])
      {
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_SETWAKEUPCHANNEL_SID,
                                                                                        FR_59_RENESAS_E_INVALID_CORE);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
      }
      #endif
    }
    /* Check if the channel is invalid */
    if (FR_CHANNEL_AB <= Fr_ChnlIdx)
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_SETWAKEUPCHANNEL_SID,
                                                                                        FR_59_RENESAS_E_INV_CHNL_IDX);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    } /* else No Action required */
  }
  /* Check if any DET error has occurred */
  if (FR_59_RENESAS_FALSE == LblErrDetect)
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Read the POC state by getting the FRCCSV register value */
    LulData = Fr_59_Renesas_GetPOCStsFlag(Fr_CtrlIdx);
    /* Check if POC is not in READY State */
    if (FR_59_RENESAS_READY_STATE != LulData)
    {
      #if (FR_59_RENESAS_AR_VERSION == FR_59_RENESAS_AR_422_VERSION)
      #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_SETWAKEUPCHANNEL_SID,
                                                                                         FR_59_RENESAS_E_INV_POCSTATE);
      #else /* FR_59_RENESAS_DEV_ERROR_DETECT == STD_OFF */
      LpDemEventId = (P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF,
                                         FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pDemEventId);
      if (FR_59_RENESAS_DEM_NOT_CONFIGURED != LpDemEventId->usHardwareTestFailure)
      {
        FR_59_RENESAS_DEM_REPORT_ERROR(LpDemEventId->usHardwareTestFailure, DEM_EVENT_STATUS_FAILED);
      } /* else No Action required */

      #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
      #endif /* #if (FR_59_RENESAS_AR_VERSION == FR_59_RENESAS_AR_422_VERSION)*/
      #if (FR_59_RENESAS_AR_VERSION == FR_59_RENESAS_AR_R22_11_VERSION)
      /* Report to DET */
      (void)Det_ReportRuntimeError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID,
                                                     FR_59_RENESAS_SETWAKEUPCHANNEL_SID, FR_59_RENESAS_E_INV_POCSTATE);
      #endif /* #if (FR_59_RENESAS_AR_VERSION == FR_59_RENESAS_AR_R22_11_VERSION) */
      /* Set return value to E_NOT_OK */
      LucReturnValue = E_NOT_OK;
    }
    else
    {
      /* Wait until CC is busy */
      LucReturnValue = Fr_59_Renesas_CheckIfCCBusy(Fr_CtrlIdx);
      /* Check if the CC has not become idle */
      if (E_OK == LucReturnValue)
      {
        (void)Fr_59_Renesas_WriteCHICmd(Fr_CtrlIdx, FR_59_RENESAS_CONFIG);
        LucReturnValue = Fr_59_Renesas_CheckIfCCBusy(Fr_CtrlIdx);
        /* Check if the CC has not become idle */
        if (E_OK == LucReturnValue)
        {
          /* Set wakeup channel */
          LucReturnValue = Fr_59_Renesas_SetWakeupChannelProcess(Fr_CtrlIdx, Fr_ChnlIdx);
        } /* else No Action required */
      } /* else No Action required */
    }
  }
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  else
  {
    /* Set return value to E_NOT_OK */
    LucReturnValue = E_NOT_OK;
  }
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  /* Return the value */
  return (LucReturnValue);
} /* End of API Fr_59_Renesas_SetWakeupChannel */
#define FR_59_RENESAS_STOP_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_GetPOCStatus
**
** Service ID            : 0x0a
**
** Description           : This service gets the POC Status of CC
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx
**
** InOut Parameters      : None
**
** Output Parameters     : Fr_POCStatusPtr
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : The FlexRay Driver module should be initialized.
**
** Global Variables Used : Fr_59_Renesas_GaaGlobalAccPoint
**                         Fr_59_Renesas_GaaGetCoreId2Index
**                         Fr_59_Renesas_GaaGetController2CoreIndex
**
** Functions Invoked     : Det_ReportError, Fr_59_Renesas_UpdatePOCSts
**
** Registers Used        : None
**
** Reference ID          : FR_DUD_ACT_010, FR_DUD_ACT_010_ERR001,
** Reference ID          : FR_DUD_ACT_010_ERR002, FR_DUD_ACT_010_ERR003, FR_DUD_ACT_010_ERR004
***********************************************************************************************************************/

#define FR_59_RENESAS_START_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PUBLIC_CODE) Fr_59_Renesas_GetPOCStatus(uint8 Fr_CtrlIdx, Fr_POCStatusType *Fr_POCStatusPtr)    /* PRQA S 1503 # JV-01 */
{
  /* Declare the variable to store the return value */
  Std_ReturnType LucReturnValue;
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  /* Declare the variable to store the DET return value */
  boolean LblErrDetect;
  /* Declare the variable to store the core index */
  uint8 LucCoreIndex;
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  uint8 ucCoreId;
  /* Get Core id for code branching */
  ucCoreId = (uint8)GetCoreID();
  /* Covert Core Id to Core Index */
  LucCoreIndex = Fr_59_Renesas_GaaGetCoreId2Index[ucCoreId];                                                            
  #else
  /* if Multicore is not configure, default coreid is 0x00
    To optimize implementation */
  LucCoreIndex = FR_59_RENESAS_ZERO;
  #endif
  /* Initialize development detection flag */
  LblErrDetect = FR_59_RENESAS_FALSE;
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  /* Initialize the return value */
  LucReturnValue = E_OK;                                                                                                /* PRQA S 2982 # JV-01 */
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  /* Check invalid core for calling API */
  if (FR_59_RENESAS_INVALID_CORE == LucCoreIndex)
  {
    /* Report to DET */
    (void)Det_ReportError(FR_59_RENESAS_MODULE_ID,FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_GETPOCSTATUS_SID,
                                                                                        FR_59_RENESAS_E_INVALID_CORE);
    /* Default error is detected */
    LblErrDetect = FR_59_RENESAS_TRUE;
  }
  else
  #endif
  {
    /* Check if the module is initialized */
    if (FR_59_RENESAS_FALSE == *(Fr_59_Renesas_GaaGlobalAccPoint[LucCoreIndex].pInitDone))                              
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_GETPOCSTATUS_SID,
                                                                                        FR_59_RENESAS_E_INIT_FAILED);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    } /* else No Action required */
    /* Check if the controller index is greater than the number of controller configured */
    if (FR_59_RENESAS_NUM_CTRL_SUPPORTED <= Fr_CtrlIdx)
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_GETPOCSTATUS_SID,
                                                                                      FR_59_RENESAS_E_INV_CTRL_IDX);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    }
    else
    {
      #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
      /* Check invalid core for calling API */
      if (LucCoreIndex != Fr_59_Renesas_GaaGetController2CoreIndex[Fr_CtrlIdx])
      {
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_GETPOCSTATUS_SID,
                                                                                         FR_59_RENESAS_E_INVALID_CORE);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
      }
      #endif
    }
    /* Check if the output parameter Fr_POCStatusPtr is NULL pointer */
    if (NULL_PTR == Fr_POCStatusPtr)
    {
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_GETPOCSTATUS_SID,
                                                                                       FR_59_RENESAS_E_PARAM_POINTER);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    } /* else No Action required */
  }
  /* Check if any DET error has occurred */
  if (FR_59_RENESAS_FALSE == LblErrDetect)
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Update the POC status to output pointer */
    LucReturnValue = Fr_59_Renesas_UpdatePOCSts(Fr_CtrlIdx, Fr_POCStatusPtr);
  }
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  else
  {
    LucReturnValue = E_NOT_OK;
  }
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  /* Return the value */
  return (LucReturnValue);
} /* End of API Fr_59_Renesas_GetPOCStatus */
#define FR_59_RENESAS_STOP_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_TransmitTxLPdu
**
** Service ID            : 0x0b
**
** Description           : This service copies the Fr_LSduLength bytes from
**                         address Fr_LSduPtr into the FlexRay CC transmission
**                         resource mapped to the FlexRay frame
**
** Sync/Async            : Asynchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx, Fr_LPduIdx, Fr_LSduPtr, Fr_LSduLength, Fr_SlotAssignmentPtr
**
** InOut Parameters      : None
**
** Output Parameters     : Fr_SlotAssignmentPtr
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : The FlexRay Driver module should be initialized.
**
** Global Variables Used : Fr_59_Renesas_GaaGlobalAccPoint,
**                         Fr_59_Renesas_GpBufReconfigStatusPtr,
**                         Fr_59_Renesas_GpControllerConfigPtr
**                         Fr_59_Renesas_GaaGetCoreId2Index
**                         Fr_59_Renesas_GaaGetController2CoreIndex
**
** Functions Invoked     : Det_ReportError,
**                         Fr_59_Renesas_CfgBufferHeader,
**                         Fr_59_Renesas_CheckErrorInterrupt,
**                         Fr_59_Renesas_GetBufferCommand,
**                         Fr_59_Renesas_UpdateInputBuffer,
**                         Fr_59_Renesas_UpdateDataTransferMode
**                         Fr_59_Renesas_GetSlotAssignment
**
** Registers Used        : None
**
** Reference ID          : FR_DUD_ACT_011,
** Reference ID          : FR_DUD_ACT_011_ERR001,
** Reference ID          : FR_DUD_ACT_011_ERR002, FR_DUD_ACT_011_ERR003,
** Reference ID          : FR_DUD_ACT_011_ERR004, FR_DUD_ACT_011_ERR005, FR_DUD_ACT_011_ERR006
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PUBLIC_CODE)
Fr_59_Renesas_TransmitTxLPdu(uint8 Fr_CtrlIdx, uint16 Fr_LPduIdx, const uint8 *Fr_LSduPtr, uint8 Fr_LSduLength,         /* PRQA S 1503 # JV-01 */
                                                                  Fr_SlotAssignmentType *Fr_SlotAssignmentPtr)
{
  P2CONST(Fr_59_Renesas_FrameHeaderType, TYPEDEF, FR_CONFIG_DATA) LpHeaderPtr;
  P2CONST(Fr_59_Renesas_FrameHeaderType, AUTOMATIC, FR_APPL_CONST)
  LpBufferHeaderPtr;
  #if (FR_59_RENESAS_RECONFIG_LPDU == STD_ON) || (FR_59_RENESAS_PREPARE_LPDU == STD_ON) || \
                                                                                 (FR_59_RENESAS_DISABLE_LPDU == STD_ON)
  P2VAR(volatile uint16, AUTOMATIC, FR_APPL_DATA) LpBufReconfigStatusPtr;                                               /* PRQA S 3678 # JV-01 */
  #endif
  Std_ReturnType LucReturnValue;
  uint8 LucMessageBuffer;
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  /* Declare local pointer to Control Table */
  P2CONST(Fr_59_Renesas_CtrlTableType, TYPEDEF, FR_CONFIG_DATA) LpCtrlTable;
  /* Declare the variable to store the DET return value */
  boolean LblErrDetect;
  /* Declare the variable to store the core index */
  uint8 LucCoreIndex;
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  uint8 ucCoreId;
  /* Get Core id for code branching */
  ucCoreId = (uint8)GetCoreID();
  /* Covert Core Id to Core Index */
  LucCoreIndex = Fr_59_Renesas_GaaGetCoreId2Index[ucCoreId];                                                            
  #else
  /* if Multicore is not configure, default coreid is 0x00
    To optimize implementation */
  LucCoreIndex = FR_59_RENESAS_ZERO;
  #endif
  /* Initialize development detection flag */
  LblErrDetect = FR_59_RENESAS_FALSE;
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  /* Initialize the return value */
  LucReturnValue = E_OK;                                                                                                /* PRQA S 2982 # JV-01 */
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  /* Check invalid core for calling API */
  if (FR_59_RENESAS_INVALID_CORE == LucCoreIndex)
  {
    /* Report to DET */
    (void)Det_ReportError(FR_59_RENESAS_MODULE_ID,FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_TRANSMITTXLPDU_SID,
                                                                                        FR_59_RENESAS_E_INVALID_CORE);
    /* Default error is detected */
    LblErrDetect = FR_59_RENESAS_TRUE;
  }
  else
  #endif
  {
    /* Check if the module is initialized */
    if (FR_59_RENESAS_FALSE == *(Fr_59_Renesas_GaaGlobalAccPoint[LucCoreIndex].pInitDone))                              
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_TRANSMITTXLPDU_SID,
                                                                                         FR_59_RENESAS_E_INIT_FAILED);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    } /* else No Action required */
    /* Check if the controller index is greater than the number of controller configured */
    if (FR_59_RENESAS_NUM_CTRL_SUPPORTED <= Fr_CtrlIdx)
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_TRANSMITTXLPDU_SID,
                                                                                       FR_59_RENESAS_E_INV_CTRL_IDX);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    }
    else
    {
      #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
      /* Check invalid core for calling API */
      if (LucCoreIndex != Fr_59_Renesas_GaaGetController2CoreIndex[Fr_CtrlIdx])
      {
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_TRANSMITTXLPDU_SID,
                                                                                        FR_59_RENESAS_E_INVALID_CORE);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
      }
      #endif
    }
  }
  /* Check if any DET error has occurred */
  if (FR_59_RENESAS_FALSE == LblErrDetect)
  {
    #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
    /* Initialize local pointer */
    LpHeaderPtr = (P2CONST(Fr_59_Renesas_FrameHeaderType, TYPEDEF,
                                        FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pFrameConfig);
    #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
    LpCtrlTable = (P2CONST(Fr_59_Renesas_CtrlTableType, AUTOMATIC,
                                          FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pCtrlTable);
    /* Check if the value of LPduIdx is greater than the number of frames configured */
    if (Fr_LPduIdx >= LpCtrlTable->usMaxFrames)                                                                         
    {
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_TRANSMITTXLPDU_SID,
                                                                                         FR_59_RENESAS_E_INV_LPDU_IDX);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    }
    else
    {
    #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
      /* Initialize pointer of frame header */
      LpBufferHeaderPtr = &LpHeaderPtr[Fr_LPduIdx];                                                                     
      #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
      /* Check if the length is greater the value of length configured for the Lpdu */
      if (Fr_LSduLength > ((uint8)(LpBufferHeaderPtr->ucPayloadLength << FR_59_RENESAS_ONE)))                           
      {
        /* Report to DET */
        (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_TRANSMITTXLPDU_SID,
                                                                                           FR_59_RENESAS_E_INV_LENGTH);
        /* Default error is detected */
        LblErrDetect = FR_59_RENESAS_TRUE;
      } /* else No Action required */
    }
  } /* else No Action required */
  /* Check if the output parameter Fr_LSduPtr is NULL pointer */
  if (NULL_PTR == Fr_LSduPtr)
  {
    /* Report to DET */
    (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_TRANSMITTXLPDU_SID,
                                                                                        FR_59_RENESAS_E_PARAM_POINTER);
    /* Default error is detected */
    LblErrDetect = FR_59_RENESAS_TRUE;
  } /* else No Action required */
  /* Check if any DET error has occurred */
  if (FR_59_RENESAS_FALSE == LblErrDetect)
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Read the value of FLXAnFREIR register and check if there is any interrupt */
    LucReturnValue = Fr_59_Renesas_CheckErrorInterrupt(Fr_CtrlIdx);
    if (E_OK == LucReturnValue)
    {
      #if (FR_59_RENESAS_RECONFIG_LPDU == STD_ON) || (FR_59_RENESAS_PREPARE_LPDU == STD_ON) || \
                                                                                 (FR_59_RENESAS_DISABLE_LPDU == STD_ON)
      /* Initialize local pointer of Buffer Reconfig Status */
      LpBufReconfigStatusPtr = Fr_59_Renesas_GpBufReconfigStatusPtr[Fr_CtrlIdx];                                        
      LucMessageBuffer = LpBufferHeaderPtr->ucMsgBuffer;                                                                
      if (((LpBufferHeaderPtr->blBufferReConfig != LpBufferHeaderPtr->blFrIfReconfigurable) &&
                                      (LpBufReconfigStatusPtr[LucMessageBuffer] == Fr_LPduIdx)) ||                      
                                              ((FR_59_RENESAS_FALSE == LpBufferHeaderPtr->blBufferReConfig) &&
                                                     (FR_59_RENESAS_FALSE == LpBufferHeaderPtr->blFrIfReconfigurable)))
      #endif
      {
        LucReturnValue = Fr_59_Renesas_GetBufferCommand(Fr_CtrlIdx);
        /* Check if the return value is E_OK */
        if (E_OK == LucReturnValue)
        {
          /* Check if Allow dynamic length is supported */
          if ((FR_59_RENESAS_TRUE == LpBufferHeaderPtr->blAllowDynLength) &&
                               ((Fr_LSduLength <= (uint8)((LpBufferHeaderPtr->ucPayloadLength) << FR_59_RENESAS_ONE))))
          {
            /*
             * Reconfigure buffer header to match with Fr_LSduLength and
             * input param Fr_LSduLength is less than configured ucPayloadLength
             */
            LucReturnValue = Fr_59_Renesas_CfgBufferHeader(
                 Fr_CtrlIdx, Fr_LPduIdx, ((Fr_LSduLength + (Fr_LSduLength % FR_59_RENESAS_TWO)) >> FR_59_RENESAS_ONE)); /* PRQA S 3383 # JV-01 */
          } /* else No Action required */
          if (E_OK == LucReturnValue)
          {
            /* Check if Frame Receive or Frame Id is 0,
             * return E_NOT_OK
             */
            if ((FR_59_RENESAS_CFG_TRANSMIT == LpBufferHeaderPtr->ucFrameConfig) &&
                                                                  (FR_59_RENESAS_ZERO != LpBufferHeaderPtr->usFrameId))
            {
              Fr_59_Renesas_UpdateInputBuffer(Fr_CtrlIdx, Fr_LSduLength, Fr_LSduPtr);
              LucMessageBuffer = LpBufferHeaderPtr->ucMsgBuffer;
              /* Select Load Data Mode */
              LucReturnValue = Fr_59_Renesas_UpdateDataTransferMode(Fr_CtrlIdx, LucMessageBuffer);
            }
            else
            {
              LucReturnValue = E_NOT_OK;
            }
            /* Copy ChannelId, FrameId and CycleId of transmitted frame */
            #if (FR_59_RENESAS_EXTENDED_LPDU_REPORTING == STD_ON)
            if ((E_OK == LucReturnValue) && (NULL_PTR != Fr_SlotAssignmentPtr))
            {
              LucReturnValue = Fr_59_Renesas_GetSlotAssignment(Fr_CtrlIdx, Fr_LPduIdx, Fr_SlotAssignmentPtr);
            } /* else No Action required */
            #endif /* (FR_59_RENESAS_EXTENDED_LPDU_REPORTING == STD_ON) */
          } /* else No Action required */
        } /* else No Action required */
      }
      #if (FR_59_RENESAS_RECONFIG_LPDU == STD_ON) || (FR_59_RENESAS_PREPARE_LPDU == STD_ON) || \
                                                                                 (FR_59_RENESAS_DISABLE_LPDU == STD_ON)
      else
      {
        LucReturnValue = E_NOT_OK;
      }
      #endif
    } /* else No Action required */
  }
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  else
  {
    LucReturnValue = E_NOT_OK;
  }
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  /* Return the value */
  return (LucReturnValue);
} /* End of API Fr_59_Renesas_TransmitTxLPdu */
#define FR_59_RENESAS_STOP_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_CancelTxLPdu
**
** Service ID            : 0x2d
**
** Description           : This service Cancels the already pending transmission
**                         of a LPdu contained in a controllers physical
**                         transmit resource
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx, Fr_LPduIdx
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : The FlexRay Driver module should be initialized.
**
** Global Variables Used : Fr_59_Renesas_GaaGlobalAccPoint,
**                         Fr_59_Renesas_GpControllerConfigPtr,
**                         Fr_59_Renesas_GpBufReconfigStatusPtr.
**                         Fr_59_Renesas_GaaGetCoreId2Index
**                         Fr_59_Renesas_GaaGetController2CoreIndex
**
** Functions Invoked     : Det_ReportError, Fr_59_Renesas_ClearTxReq
**
** Registers Used        : None
**
** Reference ID          : FR_DUD_ACT_012, FR_DUD_ACT_012_ERR001,
** Reference ID          : FR_DUD_ACT_012_ERR002, FR_DUD_ACT_012_ERR003, FR_DUD_ACT_012_ERR004
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PUBLIC_CODE) Fr_59_Renesas_CancelTxLPdu(uint8 Fr_CtrlIdx, uint16 Fr_LPduIdx)                    /* PRQA S 1503 # JV-01 */
{
  #if (FR_59_RENESAS_RECONFIG_LPDU == STD_ON) || (FR_59_RENESAS_PREPARE_LPDU == STD_ON) || \
                                                                                 (FR_59_RENESAS_DISABLE_LPDU == STD_ON)
  /* Define fine the variable to store frame configuration */
  P2VAR(volatile uint16, AUTOMATIC, FR_APPL_DATA) LpBufReconfigStatusPtr;                                               /* PRQA S 3678 # JV-01 */

  #endif
  /* Declare pointer to frame configuration */
  P2CONST(Fr_59_Renesas_FrameHeaderType, AUTOMATIC, FR_APPL_CONST) LpFrameConfigPtr;
  P2CONST(Fr_59_Renesas_FrameHeaderType, TYPEDEF, FR_CONFIG_DATA) LpFrameConfig;
  /* Declare the variable to store the return value */
  Std_ReturnType LucReturnValue;
  uint8 LucMessageBuffer;
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  /* Declare local pointer to Control Table */
  P2CONST(Fr_59_Renesas_CtrlTableType, TYPEDEF, FR_CONFIG_DATA) LpCtrlTable;
  /* Declare the variable to store the DET return value */
  boolean LblErrDetect;
  /* Declare the variable to store the core index */
  uint8 LucCoreIndex;
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  uint8 ucCoreId;
  /* Get Core id for code branching */
  ucCoreId = (uint8)GetCoreID();
  /* Covert Core Id to Core Index */
  LucCoreIndex = Fr_59_Renesas_GaaGetCoreId2Index[ucCoreId];                                                            
  #else
  /* if Multicore is not configure, default coreid is 0x00
    To optimize implementation */
  LucCoreIndex = FR_59_RENESAS_ZERO;
  #endif
  /* Initialize development detection flag */
  LblErrDetect = FR_59_RENESAS_FALSE;
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  /* Initialize the return value */
  LucReturnValue = E_OK;                                                                                                /* PRQA S 2982 # JV-01 */
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  /* Check invalid core for calling API */
  if (FR_59_RENESAS_INVALID_CORE == LucCoreIndex)
  {
    /* Report to DET */
    (void)Det_ReportError(FR_59_RENESAS_MODULE_ID,FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_CANCELTXLPDU_SID,
                                                                                        FR_59_RENESAS_E_INVALID_CORE);
    /* Default error is detected */
    LblErrDetect = FR_59_RENESAS_TRUE;
  }
  else
  #endif
  {
    /* Check if the module is initialized */
    if (FR_59_RENESAS_FALSE == *(Fr_59_Renesas_GaaGlobalAccPoint[LucCoreIndex].pInitDone))                              
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_CANCELTXLPDU_SID,
                                                                                           FR_59_RENESAS_E_INIT_FAILED);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    } /* else No Action required */
    /* Check if the controller index is greater than the number of controller configured */
    if (FR_59_RENESAS_NUM_CTRL_SUPPORTED <= Fr_CtrlIdx)
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_CANCELTXLPDU_SID,
                                                                                         FR_59_RENESAS_E_INV_CTRL_IDX);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    }
    else
    {
      #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
      /* Check invalid core for calling API */
      if (LucCoreIndex != Fr_59_Renesas_GaaGetController2CoreIndex[Fr_CtrlIdx])
      {
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_CANCELTXLPDU_SID,
                                                                                          FR_59_RENESAS_E_INVALID_CORE);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
      }
      #endif
    }
    /* Check if any DET error has occurred */
    if (FR_59_RENESAS_FALSE == LblErrDetect)
    {
      /* Initialize local pointer */
      LpCtrlTable = (P2CONST(Fr_59_Renesas_CtrlTableType, AUTOMATIC,
                                           FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pCtrlTable);
      /*
      * Check if the value of LPduIdx is greater than the number of frames configured
      */
      if (Fr_LPduIdx >= LpCtrlTable->usMaxFrames)                                                                       
      {
        /* Report to DET */
        (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_CANCELTXLPDU_SID,
                                                                                          FR_59_RENESAS_E_INV_LPDU_IDX);
        /* Default error is detected */
        LblErrDetect = FR_59_RENESAS_TRUE;
      } /* else No Action required */
    } /* else No Action required */
  }
  /* Check if any DET error has occurred */
  if (FR_59_RENESAS_FALSE == LblErrDetect)
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  {
    LpFrameConfig = (P2CONST(Fr_59_Renesas_FrameHeaderType, TYPEDEF,
                                        FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pFrameConfig);
    LpFrameConfigPtr = &LpFrameConfig[Fr_LPduIdx];                                                                      
    LucMessageBuffer = LpFrameConfigPtr->ucMsgBuffer;                                                                   
    #if (FR_59_RENESAS_RECONFIG_LPDU == STD_ON) || (FR_59_RENESAS_PREPARE_LPDU == STD_ON) || \
                                                                                 (FR_59_RENESAS_DISABLE_LPDU == STD_ON)
    /* Initialize local pointer of Buffer Reconfig Status */
    LpBufReconfigStatusPtr = Fr_59_Renesas_GpBufReconfigStatusPtr[Fr_CtrlIdx];                                          
    if (((LpFrameConfigPtr->blBufferReConfig != LpFrameConfigPtr->blFrIfReconfigurable) &&
                                    (LpBufReconfigStatusPtr[LucMessageBuffer] == Fr_LPduIdx)) ||                        
                                              ((FR_59_RENESAS_FALSE == LpFrameConfigPtr->blBufferReConfig) &&
                                                      (FR_59_RENESAS_FALSE == LpFrameConfigPtr->blFrIfReconfigurable)))
    #endif
    {
      /* Check if Frame is not receive frame and Frame id not equal to zero */
      if ((FR_59_RENESAS_CFG_TRANSMIT == LpFrameConfigPtr->ucFrameConfig) &&
                                                                   (FR_59_RENESAS_ZERO != LpFrameConfigPtr->usFrameId))
      {
        /* Update the LPdu status */
        LucReturnValue = Fr_59_Renesas_ClearTxReq(Fr_CtrlIdx, LucMessageBuffer);
      }
      else /* Receive frame or Startup frame */
      {
        /* Update the return value to E_NOT_OK */
        LucReturnValue = E_NOT_OK;
      }
    }
    #if (FR_59_RENESAS_RECONFIG_LPDU == STD_ON) || (FR_59_RENESAS_PREPARE_LPDU == STD_ON) || \
                                                                                 (FR_59_RENESAS_DISABLE_LPDU == STD_ON)
    else
    {
      LucReturnValue = E_NOT_OK;
    }
  #endif
  }
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  else
  {
    LucReturnValue = E_NOT_OK;
  }
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  /* Return the value */
  return (LucReturnValue);
} /* End of API Fr_59_Renesas_CancelTxLPdu */
#define FR_59_RENESAS_STOP_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_ReceiveRxLPdu
**
** Service ID            : 0x0c
**
** Description           : This service copies the received payload data to
**                         address Fr_LSduPtr. The length of the data and status
**                         of the frame received are updated by this service
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx, Fr_LPduIdx
**
** InOut Parameters      : None
**
** Output Parameters     : Fr_LSduPtr, Fr_LPduStatusPtr, Fr_LSduLengthPtr, Fr_SlotAssignmentPtr
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : The FlexRay Driver module should be initialized.
**
** Global Variables Used : Fr_59_Renesas_GaaGlobalAccPoint,
**                         Fr_59_Renesas_GpControllerConfigPtr,
**                         Fr_59_Renesas_GpBufReconfigStatusPtr
**                         Fr_59_Renesas_GaaGetCoreId2Index
**                         Fr_59_Renesas_GaaGetController2CoreIndex
**
** Functions Invoked     : Det_ReportError,
**                         Fr_59_Renesas_CheckErrorInterrupt,
**                         Fr_59_Renesas_UpdateStsLength, Fr_59_Renesas_NewData,
**                         Fr_59_Renesas_WriteOutputBufferCommand,
**                         Fr_59_Renesas_ReadReceiveData
**                         Fr_59_Renesas_GetSlotAssignment
**
** Registers Used        : None
**
** Reference ID          : FR_DUD_ACT_013, FR_DUD_ACT_013_ERR001,
** Reference ID          : FR_DUD_ACT_013_ERR002, FR_DUD_ACT_013_ERR003,
** Reference ID          : FR_DUD_ACT_013_ERR004, FR_DUD_ACT_013_ERR005,
** Reference ID          : FR_DUD_ACT_013_ERR006, FR_DUD_ACT_013_ERR007
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PUBLIC_CODE)
Fr_59_Renesas_ReceiveRxLPdu(uint8 Fr_CtrlIdx, uint16 Fr_LPduIdx, uint8 *Fr_LSduPtr,                                     /* PRQA S 1503 # JV-01 */
            Fr_RxLPduStatusType *Fr_LPduStatusPtr, uint8 *Fr_LSduLengthPtr, Fr_SlotAssignmentType *Fr_SlotAssignmentPtr)
{
  P2CONST(Fr_59_Renesas_FrameHeaderType, AUTOMATIC, FR_APPL_CONST) LpFrameConfigPtr;
  P2CONST(Fr_59_Renesas_FrameHeaderType, TYPEDEF, FR_CONFIG_DATA) LpFrameConfig;
  #if (FR_59_RENESAS_RECONFIG_LPDU == STD_ON) || (FR_59_RENESAS_PREPARE_LPDU == STD_ON) || \
                                                                                 (FR_59_RENESAS_DISABLE_LPDU == STD_ON)
  P2VAR(volatile uint16, AUTOMATIC, FR_APPL_DATA) LpBufReconfigStatusPtr;                                               /* PRQA S 3678 # JV-01 */
  #endif
  Std_ReturnType LucReturnValue;
  uint8 LucMessageBuffer;
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  /* Declare local pointer to Control Table */
  P2CONST(Fr_59_Renesas_CtrlTableType, TYPEDEF, FR_CONFIG_DATA) LpCtrlTable;
  /* Declare the variable to store the DET return value */
  boolean LblErrDetect;
  /* Declare the variable to store the core index */
  uint8 LucCoreIndex;
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  uint8 ucCoreId;
  /* Get Core id for code branching */
  ucCoreId = (uint8)GetCoreID();
  /* Covert Core Id to Core Index */
  LucCoreIndex = Fr_59_Renesas_GaaGetCoreId2Index[ucCoreId];                                                            
  #else
  /* if Multicore is not configure, default coreid is 0x00
    To optimize implementation */
  LucCoreIndex = FR_59_RENESAS_ZERO;
  #endif
  /* Initialize development detection flag */
  LblErrDetect = FR_59_RENESAS_FALSE;
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  /* Initialize the return value */
  LucReturnValue = E_OK;                                                                                                /* PRQA S 2982 # JV-01 */
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  /* Check invalid core for calling API */
  if (FR_59_RENESAS_INVALID_CORE == LucCoreIndex)
  {
    /* Report to DET */
    (void)Det_ReportError(FR_59_RENESAS_MODULE_ID,FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_RECEIVERXLPDU_SID,
                                                                                        FR_59_RENESAS_E_INVALID_CORE);
    /* Default error is detected */
    LblErrDetect = FR_59_RENESAS_TRUE;
  }
  else
  #endif
  {
    /* Check if the module is initialized */
    if (FR_59_RENESAS_FALSE == *(Fr_59_Renesas_GaaGlobalAccPoint[LucCoreIndex].pInitDone))                              
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_RECEIVERXLPDU_SID,
                                                                                           FR_59_RENESAS_E_INIT_FAILED);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    } /* else No Action required */
    /* Check if the controller index is greater than the number of controller configured */
    if (FR_59_RENESAS_NUM_CTRL_SUPPORTED <= Fr_CtrlIdx)
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_RECEIVERXLPDU_SID,
                                                                                          FR_59_RENESAS_E_INV_CTRL_IDX);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    }
    else
    {
      #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
      /* Check invalid core for calling API */
      if (LucCoreIndex != Fr_59_Renesas_GaaGetController2CoreIndex[Fr_CtrlIdx])
      {
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_RECEIVERXLPDU_SID,
                                                                                         FR_59_RENESAS_E_INVALID_CORE);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
      }
      #endif
    }
  }
  /* Check if default error is detected */
  if (FR_59_RENESAS_FALSE == LblErrDetect)
  {
    /* Check if the value of LPduIdx is greater than the number of frames configured */
    LpCtrlTable = (P2CONST(Fr_59_Renesas_CtrlTableType, AUTOMATIC,
                                          FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pCtrlTable);
    if (Fr_LPduIdx >= LpCtrlTable->usMaxFrames)                                                                         
    {
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_RECEIVERXLPDU_SID,
                                                                                         FR_59_RENESAS_E_INV_LPDU_IDX);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    } /* else No Action required */
  } /* else No Action required */
  /* Check if the output parameter Fr_LSduPtr is NULL pointer */
  if (NULL_PTR == Fr_LSduPtr)
  {
    /* Report to DET */
    (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_RECEIVERXLPDU_SID,
                                                                                        FR_59_RENESAS_E_PARAM_POINTER);
    /* Default error is detected */
    LblErrDetect = FR_59_RENESAS_TRUE;
  } /* else No Action required */
  /* Check if the output parameter Fr_LPduStatusPtr is NULL pointer */
  if (NULL_PTR == Fr_LPduStatusPtr)
  {
    /* Report to DET */
    (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_RECEIVERXLPDU_SID,
                                                                                        FR_59_RENESAS_E_PARAM_POINTER);
    /* Default error is detected */
    LblErrDetect = FR_59_RENESAS_TRUE;
  } /* else No Action required */
  /* Check if the output parameter Fr_LSduLengthPtr is NULL pointer */
  if (NULL_PTR == Fr_LSduLengthPtr)
  {
    /* Report to DET */
    (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_RECEIVERXLPDU_SID,
                                                                                        FR_59_RENESAS_E_PARAM_POINTER);
    /* Default error is detected */
    LblErrDetect = FR_59_RENESAS_TRUE;
  } /* else No Action required */
  /* Check if default error is detected */
  if (FR_59_RENESAS_TRUE == LblErrDetect)
  {
    LucReturnValue = E_NOT_OK;
    if ((NULL_PTR != Fr_LPduStatusPtr) && (NULL_PTR != Fr_LSduLengthPtr))
    {
      /* Set the status as not received */
      *Fr_LPduStatusPtr = FR_NOT_RECEIVED;
      /* Set the received length as zero */
      *Fr_LSduLengthPtr = FR_59_RENESAS_ZERO;
    } /* else No Action required */
  }
  else
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Initialize local pointer */
    LpFrameConfig = (P2CONST(Fr_59_Renesas_FrameHeaderType, TYPEDEF,
                                        FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pFrameConfig);
    LpFrameConfigPtr = &LpFrameConfig[Fr_LPduIdx];                                                                      
    /* Read the value of FLXAnFREIR register and check if there is any
     interrupt */
    LucReturnValue = Fr_59_Renesas_CheckErrorInterrupt(Fr_CtrlIdx);
    if (E_OK == LucReturnValue)
    {
      /* Check that frame is not transmit frame and also Frame ID is not equal to ZERO */
      if ((FR_59_RENESAS_CFG_RECEIVE == LpFrameConfigPtr->ucFrameConfig) &&                                             
                                                                   (FR_59_RENESAS_ZERO != LpFrameConfigPtr->usFrameId))
      {
        /* Check if frame is configured to FIFO */
        if (FR_59_RENESAS_TRUE == LpFrameConfigPtr->blIsFIFOConfig)
        {
          /* Update the LPdu status and LSdu length */
          Fr_59_Renesas_UpdateStsLength(Fr_CtrlIdx, Fr_LPduStatusPtr, Fr_LSduLengthPtr);
        }
        else
        {
          /* Read the Message Buffer configured to the frame */
          LucMessageBuffer = LpFrameConfigPtr->ucMsgBuffer;
          #if (FR_59_RENESAS_RECONFIG_LPDU == STD_ON) || (FR_59_RENESAS_PREPARE_LPDU == STD_ON) || \
                                                                                 (FR_59_RENESAS_DISABLE_LPDU == STD_ON)
          /* Initialize local pointer of Buffer Reconfig Status */
          LpBufReconfigStatusPtr = Fr_59_Renesas_GpBufReconfigStatusPtr[Fr_CtrlIdx];                                    
          if (((LpFrameConfigPtr->blBufferReConfig != LpFrameConfigPtr->blFrIfReconfigurable) &&
                               (LpBufReconfigStatusPtr[LucMessageBuffer] == Fr_LPduIdx)) ||                             
                                            ((FR_59_RENESAS_FALSE == LpFrameConfigPtr->blBufferReConfig) &&
                                                      (FR_59_RENESAS_FALSE == LpFrameConfigPtr->blFrIfReconfigurable)))
          #endif
          {
            LucReturnValue = Fr_59_Renesas_NewData(Fr_CtrlIdx, LucMessageBuffer, Fr_LPduStatusPtr, Fr_LSduLengthPtr);
          }
          #if (FR_59_RENESAS_RECONFIG_LPDU == STD_ON) || (FR_59_RENESAS_PREPARE_LPDU == STD_ON) || \
                                                                                 (FR_59_RENESAS_DISABLE_LPDU == STD_ON)
          else
          {
            LucReturnValue = E_NOT_OK;
          }
          #endif
        }
        if ((FR_RECEIVED == *Fr_LPduStatusPtr) && (E_OK == LucReturnValue))                                             
        {
          /* Request transfer Header and Data from Message RAM to Output buffer */
          LucReturnValue = Fr_59_Renesas_WriteOutputBufferCommand(Fr_CtrlIdx, Fr_LPduIdx);
          if (E_OK == LucReturnValue)
          {
            /* Read Slot Status Errors from register FLXnMBS */
            LucReturnValue =
                 Fr_59_Renesas_ReadReceiveData(Fr_CtrlIdx, Fr_LPduIdx, Fr_LSduPtr, Fr_LPduStatusPtr, Fr_LSduLengthPtr);
          }
          else
          {
            /* Set the status Ptr and Sdu Length Ptr */
            *Fr_LPduStatusPtr = FR_NOT_RECEIVED;
            *Fr_LSduLengthPtr = FR_59_RENESAS_ZERO;                                                                     
          }
          #if (FR_59_RENESAS_EXTENDED_LPDU_REPORTING == STD_ON)
          if (((FR_RECEIVED == *Fr_LPduStatusPtr) || (FR_RECEIVED_MORE_DATA_AVAILABLE == *Fr_LPduStatusPtr)) && \
               (NULL_PTR != Fr_SlotAssignmentPtr))
          {
            LucReturnValue = Fr_59_Renesas_GetSlotAssignment(Fr_CtrlIdx, Fr_LPduIdx, Fr_SlotAssignmentPtr);
          } /* else No Action required */
          #endif /* (FR_59_RENESAS_EXTENDED_LPDU_REPORTING == STD_ON) */
        } /* else No Action required */
      } /* else No Action required */
      else
      {
        LucReturnValue = E_NOT_OK;
      }
      /* Check if the return value is E_NOT_OK */
      if (E_NOT_OK == LucReturnValue)
      {
        /* Set the status as not received */
        *Fr_LPduStatusPtr = FR_NOT_RECEIVED;
        /* Set the received length as zero */
        *Fr_LSduLengthPtr = FR_59_RENESAS_ZERO;
      } /* else No Action required */
    } /* else No Action required */
  }
  /* Return the value */
  return (LucReturnValue);
} /* End of API Fr_59_Renesas_ReceiveRxLPdu */
#define FR_59_RENESAS_STOP_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_CheckTxLPduStatus
**
** Service ID            : 0x0d
**
** Description           : This service checks the transmit status of the LSdu
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx, Fr_LPduIdx
**
** InOut Parameters      : None
**
** Output Parameters     : Fr_TxLPduStatusPtr, Fr_SlotAssignmentPtr
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : The FlexRay Driver module should be initialized.
**
** Global Variables Used : Fr_59_Renesas_GaaGlobalAccPoint,
**                         Fr_59_Renesas_GpBufReconfigStatusPtr,
**                         Fr_59_Renesas_GpControllerConfigPtr
**                         Fr_59_Renesas_GaaGetCoreId2Index
**                         Fr_59_Renesas_GaaGetController2CoreIndex
**
** Functions Invoked     : Det_ReportError,
**                         Fr_59_Renesas_UpdateLPduTxSts,
**                         Fr_59_Renesas_MessageBufferStatus, Fr_59_Renesas_WriteOutputBufferCommand
**                         Fr_59_Renesas_GetSlotAssignment
**
** Registers Used        : None
**
** Reference ID          : FR_DUD_ACT_014, FR_DUD_ACT_014_ERR001,
** Reference ID          : FR_DUD_ACT_014_ERR002, FR_DUD_ACT_014_ERR003,
** Reference ID          : FR_DUD_ACT_014_ERR004, FR_DUD_ACT_014_ERR005
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PUBLIC_CODE)
Fr_59_Renesas_CheckTxLPduStatus(uint8 Fr_CtrlIdx, uint16 Fr_LPduIdx, Fr_TxLPduStatusType *Fr_TxLPduStatusPtr,           /* PRQA S 1503 # JV-01 */
                                                                     Fr_SlotAssignmentType *Fr_SlotAssignmentPtr)
{
  P2CONST(Fr_59_Renesas_FrameHeaderType, AUTOMATIC, FR_APPL_CONST) LpFrameConfigPtr;
  P2CONST(Fr_59_Renesas_FrameHeaderType, TYPEDEF, FR_CONFIG_DATA) LpFrameConfig;
  #if (FR_59_RENESAS_RECONFIG_LPDU == STD_ON) || (FR_59_RENESAS_PREPARE_LPDU == STD_ON) || \
                                                                                 (FR_59_RENESAS_DISABLE_LPDU == STD_ON)
  P2VAR(volatile uint16, AUTOMATIC, FR_APPL_DATA) LpBufReconfigStatusPtr;                                               /* PRQA S 3678 # JV-01 */
  #endif
  /* Declare the variable to store the return value */
  Std_ReturnType LucReturnValue;
  uint8 LucMessageBuffer;
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  /* Declare local pointer to Control Table */
  P2CONST(Fr_59_Renesas_CtrlTableType, TYPEDEF, FR_CONFIG_DATA) LpCtrlTable;
  /* Declare the variable to store the DET return value */
  boolean LblErrDetect;
  /* Declare the variable to store the core index */
  uint8 LucCoreIndex;
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  uint8 ucCoreId;
  /* Get Core id for code branching */
  ucCoreId = (uint8)GetCoreID();
  /* Covert Core Id to Core Index */
  LucCoreIndex = Fr_59_Renesas_GaaGetCoreId2Index[ucCoreId];                                                            
  #else
  /* if Multicore is not configure, default coreid is 0x00
    To optimize implementation */
  LucCoreIndex = FR_59_RENESAS_ZERO;
  #endif
  /* Initialize development detection flag */
  LblErrDetect = FR_59_RENESAS_FALSE;
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  /* Initialize the return value to E_OK */
  LucReturnValue = E_OK;                                                                                                /* PRQA S 2982 # JV-01 */
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  /* Check invalid core for calling API */
  if (FR_59_RENESAS_INVALID_CORE == LucCoreIndex)
  {
    /* Report to DET */
    (void)Det_ReportError(FR_59_RENESAS_MODULE_ID,FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_CHECKTXLPDU_STATUS_SID,
                                                                                        FR_59_RENESAS_E_INVALID_CORE);
    /* Default error is detected */
    LblErrDetect = FR_59_RENESAS_TRUE;
  }
  else
  #endif
  {
    /* Check if the module is initialized */
    if (FR_59_RENESAS_FALSE == *(Fr_59_Renesas_GaaGlobalAccPoint[LucCoreIndex].pInitDone))                              
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_CHECKTXLPDU_STATUS_SID,
                                                                                         FR_59_RENESAS_E_INIT_FAILED);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    } /* else No Action required */
    /* Check if the controller index is greater than the number of controller configured */
    if (FR_59_RENESAS_NUM_CTRL_SUPPORTED <= Fr_CtrlIdx)
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_CHECKTXLPDU_STATUS_SID,
                                                                                        FR_59_RENESAS_E_INV_CTRL_IDX);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    }
    else
    {
      #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
      /* Check invalid core for calling API */
      if (LucCoreIndex != Fr_59_Renesas_GaaGetController2CoreIndex[Fr_CtrlIdx])
      {
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_CHECKTXLPDU_STATUS_SID,
                                                                                        FR_59_RENESAS_E_INVALID_CORE);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
      }
      #endif
    }
    /* Check if any DET error has occurred */
    if (FR_59_RENESAS_FALSE == LblErrDetect)
    {
      /* Check if the value of LPduIdx is greater than the number of frames configured */
      LpCtrlTable = (P2CONST(Fr_59_Renesas_CtrlTableType, AUTOMATIC,
                                          FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pCtrlTable);
      if (Fr_LPduIdx >= LpCtrlTable->usMaxFrames)                                                                       
      {
        /* Report to DET */
        (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_CHECKTXLPDU_STATUS_SID,
                                                                                         FR_59_RENESAS_E_INV_LPDU_IDX);
        /* Default error is detected */
        LblErrDetect = FR_59_RENESAS_TRUE;
      } /* else No Action required */
    } /* else No Action required */
  }
  /* Check if the output parameter Fr_TxLPduStatusPtr is NULL pointer */
  if (NULL_PTR == Fr_TxLPduStatusPtr)
  {
    /* Report to DET */
    (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_CHECKTXLPDU_STATUS_SID,
                                                                                        FR_59_RENESAS_E_PARAM_POINTER);
    /* Default error is detected */
    LblErrDetect = FR_59_RENESAS_TRUE;
  } /* else No Action required */
  /* Check if any DET error has occurred */
  if (FR_59_RENESAS_FALSE == LblErrDetect)
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Initialize local pointer */
    LpFrameConfig = (P2CONST(Fr_59_Renesas_FrameHeaderType, TYPEDEF,
                                        FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pFrameConfig);
    LpFrameConfigPtr = &LpFrameConfig[Fr_LPduIdx];                                                                      
    /* Read the Message Buffer configured to the frame */
    LucMessageBuffer = LpFrameConfigPtr->ucMsgBuffer;                                                                   
    /* Initialize the *Fr_TxLPduStatusPtr as FR_NOT_TRANSMITTED. */
    *Fr_TxLPduStatusPtr = FR_NOT_TRANSMITTED;                                                                           
    #if (FR_59_RENESAS_RECONFIG_LPDU == STD_ON) || (FR_59_RENESAS_PREPARE_LPDU == STD_ON) || \
                                                                                 (FR_59_RENESAS_DISABLE_LPDU == STD_ON)
    /* Initialize local pointer of Buffer Reconfig Status */
    LpBufReconfigStatusPtr = Fr_59_Renesas_GpBufReconfigStatusPtr[Fr_CtrlIdx];                                          
    if (((LpFrameConfigPtr->blBufferReConfig != LpFrameConfigPtr->blFrIfReconfigurable) &&
                                        (LpBufReconfigStatusPtr[LucMessageBuffer] == Fr_LPduIdx)) ||                    
                                                ((FR_59_RENESAS_FALSE == LpFrameConfigPtr->blBufferReConfig) &&
                                                      (FR_59_RENESAS_FALSE == LpFrameConfigPtr->blFrIfReconfigurable)))
    #endif
    {
      #if (FR_59_RENESAS_EXTENDED_LPDU_REPORTING == STD_ON)
      if (NULL_PTR != Fr_SlotAssignmentPtr)
      {
        LucReturnValue = Fr_59_Renesas_GetSlotAssignment(Fr_CtrlIdx, Fr_LPduIdx, Fr_SlotAssignmentPtr);                 /* PRQA S 2982 # JV-01 */
      } /* else No action required */
      #endif /* (FR_59_RENESAS_EXTENDED_LPDU_REPORTING == STD_ON) */
      /* Check if Frame is not receive frame and Frame id is not equal to zero */
      if ((FR_59_RENESAS_CFG_TRANSMIT == LpFrameConfigPtr->ucFrameConfig) &&
                                                                   (FR_59_RENESAS_ZERO != LpFrameConfigPtr->usFrameId))
      {
        /* Update the status of LPdu */
        LucReturnValue = Fr_59_Renesas_UpdateLPduTxSts(Fr_CtrlIdx, Fr_LPduIdx, LucMessageBuffer, Fr_TxLPduStatusPtr);
      }
      else /* Receive frame or Startup frame */
      {
        /* Update the return value to E_NOT_OK */
        LucReturnValue = E_NOT_OK;
      }
      /* DEM report for slot status information is enable and TransmissionMode is Single Shot */
      if (((FR_59_RENESAS_TRUE == LpFrameConfigPtr->blIsFrIfDemFTSlotStatusConfig) &&
                                          (FR_59_RENESAS_TXM_SINGLESHOT == LpFrameConfigPtr->ucTransmissionMode)) &&
                                                                                              (LucReturnValue == E_OK))
      {
        #if (FR_59_RENESAS_AR_VERSION == FR_59_RENESAS_AR_422_VERSION)
        LucReturnValue = Fr_59_Renesas_WriteOutputBufferCommand(Fr_CtrlIdx, Fr_LPduIdx);
        if (E_OK == LucReturnValue)
        {
        #endif
          LucReturnValue = Fr_59_Renesas_MessageBufferStatus(Fr_CtrlIdx, Fr_LPduIdx);
        #if (FR_59_RENESAS_AR_VERSION == FR_59_RENESAS_AR_422_VERSION)
        }
        else
        {
          /* No action require */
        }
        #endif
      } /* else No Action required */
    }
    #if (FR_59_RENESAS_RECONFIG_LPDU == STD_ON) || (FR_59_RENESAS_PREPARE_LPDU == STD_ON) || \
                                                                                 (FR_59_RENESAS_DISABLE_LPDU == STD_ON)
    else
    {
      LucReturnValue = E_NOT_OK;
    }
    #endif
  }
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  else
  {
    LucReturnValue = E_NOT_OK;
  }
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  /* Return the value */
  return (LucReturnValue);
} /* End of API Fr_59_Renesas_CheckTxLPduStatus */
#define FR_59_RENESAS_STOP_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_PrepareLPdu
**
** Service ID            : 0x1f
**
** Description           : This service figures out the physical resource mapped
**                         to Fr_LPduIdx and configures the physical resource
**                         appropriate for LPduIdx operation if required by
**                         Fr configuration
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx, Fr_LPduIdx
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : The FlexRay Driver module should be initialized.
**
** Global Variables Used : Fr_59_Renesas_GaaGlobalAccPoint,
**                         Fr_59_Renesas_GpBufReconfigStatusPtr,
**                         Fr_59_Renesas_GpControllerConfigPtr
**                         Fr_59_Renesas_GaaGetCoreId2Index
**                         Fr_59_Renesas_GaaGetController2CoreIndex
**
** Functions Invoked     : Det_ReportError, Fr_59_Renesas_CfgBufferHeader
**
** Registers Used        : None
**
** Reference ID          : FR_DUD_ACT_015, FR_DUD_ACT_015_ERR001,
** Reference ID          : FR_DUD_ACT_015_ERR002, FR_DUD_ACT_015_ERR003,
** Reference ID          : FR_DUD_ACT_015_ERR004, FR_DUD_ACT_015_GBL001
***********************************************************************************************************************/

#if (FR_59_RENESAS_PREPARE_LPDU == STD_ON)
#define FR_59_RENESAS_START_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PUBLIC_CODE) Fr_59_Renesas_PrepareLPdu(uint8 Fr_CtrlIdx, uint16 Fr_LPduIdx)                     /* PRQA S 1503 # JV-01 */
{
  /* Declare the variable to store the return value */
  Std_ReturnType LucReturnValue;
  P2CONST(Fr_59_Renesas_FrameHeaderType, AUTOMATIC, FR_APPL_CONST) LpBufferHeader;
  P2CONST(Fr_59_Renesas_FrameHeaderType, TYPEDEF, FR_CONFIG_DATA) LpFrameConfig;
  P2VAR(volatile uint16, AUTOMATIC, FR_APPL_DATA) LpBufReconfigStatusPtr;

  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  /* Declare local pointer to Control Table */
  P2CONST(Fr_59_Renesas_CtrlTableType, TYPEDEF, FR_CONFIG_DATA) LpCtrlTable;
  /* Declare the variable to store the DET return value */
  boolean LblErrDetect;
  /* Declare the variable to store the core index */
  uint8 LucCoreIndex;
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  uint8 ucCoreId;
  /* Get Core id for code branching */
  ucCoreId = (uint8)GetCoreID();
  /* Covert Core Id to Core Index */
  LucCoreIndex = Fr_59_Renesas_GaaGetCoreId2Index[ucCoreId];                                                            
  #else
  /* if Multicore is not configure, default coreid is 0x00
    To optimize implementation */
  LucCoreIndex = FR_59_RENESAS_ZERO;
  #endif
  /* Initialize development detection flag */
  LblErrDetect = FR_59_RENESAS_FALSE;
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  /*Initialize the return value*/
  LucReturnValue = E_OK;
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  /* Check invalid core for calling API */
  if (FR_59_RENESAS_INVALID_CORE == LucCoreIndex)
  {
    /* Report to DET */
    (void)Det_ReportError(FR_59_RENESAS_MODULE_ID,FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_PREPARELPDU_SID,
                                                                                        FR_59_RENESAS_E_INVALID_CORE);
    /* Default error is detected */
    LblErrDetect = FR_59_RENESAS_TRUE;
  }
  else
  #endif
  {
    /* Check if the module is initialized*/
    if (FR_59_RENESAS_FALSE == *(Fr_59_Renesas_GaaGlobalAccPoint[LucCoreIndex].pInitDone))                              
    {
      /* Report Error to DET*/
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_PREPARELPDU_SID,
                                                                                          FR_59_RENESAS_E_INIT_FAILED);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    }
    else
    {
      /* No action required*/
    }
    /* Check if the controller index is greater than the number of controller configured */
    if (FR_59_RENESAS_NUM_CTRL_SUPPORTED <= Fr_CtrlIdx)
    {
      /*Report Error to DET*/
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_PREPARELPDU_SID,
                                                                                          FR_59_RENESAS_E_INV_CTRL_IDX);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    }
    else
    {
      #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
      /* Check invalid core for calling API */
      if (LucCoreIndex != Fr_59_Renesas_GaaGetController2CoreIndex[Fr_CtrlIdx])
      {
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_PREPARELPDU_SID,
                                                                                         FR_59_RENESAS_E_INVALID_CORE);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
      }
      #endif
    }
    /* Check if any DET error has occurred */
    if (FR_59_RENESAS_FALSE == LblErrDetect)
    {
      /* Check if the value of LPduIdx is greater than the number of frames
      * configured*/
      LpCtrlTable = (P2CONST(Fr_59_Renesas_CtrlTableType, AUTOMATIC,
                                         FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pCtrlTable);
      if (Fr_LPduIdx >= LpCtrlTable->usMaxFrames)                                                                       
      {
        /*Report to DET*/
        (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_PREPARELPDU_SID,
                                                                                          FR_59_RENESAS_E_INV_LPDU_IDX);
        /* Default error is detected */
        LblErrDetect = FR_59_RENESAS_TRUE;
      }
      else
      {
        /* No action required*/
      }
    } /* else No Action required */
  }
  /* Check if any DET error has occurred */
  if (FR_59_RENESAS_FALSE == LblErrDetect)
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)*/
  {
    /* Initialize frame header pointer */
    LpFrameConfig = (P2CONST(Fr_59_Renesas_FrameHeaderType, TYPEDEF,
                                        FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pFrameConfig);
    LpBufferHeader = &LpFrameConfig[Fr_LPduIdx];                                                                        
    LpBufReconfigStatusPtr = Fr_59_Renesas_GpBufReconfigStatusPtr[Fr_CtrlIdx];                                          
    if (FR_59_RENESAS_TRUE == LpBufferHeader->blBufferReConfig)                                                         
    {
      /* Read the frame pointer */
      /* Invoke the function to calculate and load the header value in the corresponding register */
      LucReturnValue = Fr_59_Renesas_CfgBufferHeader(Fr_CtrlIdx, Fr_LPduIdx, LpBufferHeader->ucPayloadLength);
      if (E_OK == LucReturnValue)
      {
        /* Get the message buffer Id configured for the frame and update
         * the frame Id in the corresponding buffer reconfiguration status array
         */
        LpBufReconfigStatusPtr[LpBufferHeader->ucMsgBuffer] = Fr_LPduIdx;                                               
      } /* else No Action required */
    } /* else No Action required */
  }
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  else
  {
    LucReturnValue = E_NOT_OK;
  }
  #endif /*#if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)*/
  /* Return the value */
  return (LucReturnValue);
} /* End of API Fr_59_Renesas_PrepareLPdu */
#define FR_59_RENESAS_STOP_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
#endif /*#if (FR_59_RENESAS_PREPARE_LPDU == STD_ON)*/

/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_ReconfigLPdu
**
** Service ID            : 0x25
**
** Description           : This service reconfigures a given LPdu according to
**                         the parameters (FrameId, Channel, CycleRepetition,
**                         CycleOffset, PayloadLength, HeaderCRC) at runtime
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx, Fr_LPduIdx, Fr_FrameId,
**                         Fr_CycleRepetition, Fr_CycleOffset, Fr_PayloadLength,
**                         Fr_HeaderCRC, Fr_ChnlIdx
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : The FlexRay Driver module should be initialized.
**
** Global Variables Used : Fr_59_Renesas_GaaGlobalAccPoint,
**                         Fr_59_Renesas_GpControllerConfigPtr,
**                         Fr_59_Renesas_GpBufReconfigStatusPtr
**                         Fr_59_Renesas_GaaGetCoreId2Index
**                         Fr_59_Renesas_GaaGetController2CoreIndex
**
** Functions Invoked     : Det_ReportError, Fr_59_Renesas_UpdateWRHReg,
**                         Fr_59_Renesas_CalHeaderCRC
**
** Registers Used        : None
**
** Reference ID          : FR_DUD_ACT_016, FR_DUD_ACT_016_ERR001,
** Reference ID          : FR_DUD_ACT_016_ERR002, FR_DUD_ACT_016_ERR003,
** Reference ID          : FR_DUD_ACT_016_ERR004, FR_DUD_ACT_016_ERR005,
** Reference ID          : FR_DUD_ACT_016_ERR006, FR_DUD_ACT_016_ERR007, FR_DUD_ACT_016_ERR008
** Reference ID          : FR_DUD_ACT_016_ERR009, FR_DUD_ACT_016_ERR010, FR_DUD_ACT_016_GBL001
***********************************************************************************************************************/
#if (FR_59_RENESAS_RECONFIG_LPDU == STD_ON)
#define FR_59_RENESAS_START_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PUBLIC_CODE)
Fr_59_Renesas_ReconfigLPdu(uint8 Fr_CtrlIdx, uint16 Fr_LPduIdx, uint16 Fr_FrameId, Fr_ChannelType Fr_ChnlIdx,           /* PRQA S 1503 # JV-01 */
                           uint8 Fr_CycleRepetition, uint8 Fr_CycleOffset, uint8 Fr_PayloadLength, uint16 Fr_HeaderCRC)
{
  /* Define fine the variable to store frame configuration */
  P2VAR(volatile uint16, AUTOMATIC, FR_APPL_DATA) LpBufReconfigStatusPtr;
  P2CONST(Fr_59_Renesas_FrameHeaderType, AUTOMATIC, FR_APPL_CONST) LpBufferHeader;
  P2CONST(Fr_59_Renesas_FrameHeaderType, TYPEDEF, FR_CONFIG_DATA) LpFrameConfig;
  /* Declare the variable to store the register value */
  uint32 LulRegData;
  /* Declare the variable to store the return value */
  Std_ReturnType LucReturnValue;
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  /* Declare local pointer to Control Table */
  P2CONST(Fr_59_Renesas_CtrlTableType, TYPEDEF, FR_CONFIG_DATA) LpCtrlTable;
  /* Declare the variable to store the DET return value */
  boolean LblErrDetect;
  /* Declare the variable to store the core index */
  uint8 LucCoreIndex;
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  uint8 ucCoreId;
  /* Get Core id for code branching */
  ucCoreId = (uint8)GetCoreID();
  /* Covert Core Id to Core Index */
  LucCoreIndex = Fr_59_Renesas_GaaGetCoreId2Index[ucCoreId];                                                            
  #else
  /* if Multicore is not configure, default coreid is 0x00
    To optimize implementation */
  LucCoreIndex = FR_59_RENESAS_ZERO;
  #endif
  /* Initialize development detection flag */
  LblErrDetect = FR_59_RENESAS_FALSE;
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  /* Initialize the return value */
  LucReturnValue = E_OK;                                                                                                /* PRQA S 2982 # JV-01 */
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  /* Check invalid core for calling API */
  if (FR_59_RENESAS_INVALID_CORE == LucCoreIndex)
  {
    /* Report to DET */
    (void)Det_ReportError(FR_59_RENESAS_MODULE_ID,FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_RECONFIGLPDU_SID,
                                                                                        FR_59_RENESAS_E_INVALID_CORE);
    /* Default error is detected */
    LblErrDetect = FR_59_RENESAS_TRUE;
  }
  else
  #endif
  {
    /* Check if the module is initialized */
    if (FR_59_RENESAS_FALSE == *(Fr_59_Renesas_GaaGlobalAccPoint[LucCoreIndex].pInitDone))                              
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_RECONFIGLPDU_SID,
                                                                                          FR_59_RENESAS_E_INIT_FAILED);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    } /* else No Action required */
    /* Check if the controller index is greater than the number of controller configured */
    if (FR_59_RENESAS_NUM_CTRL_SUPPORTED <= Fr_CtrlIdx)
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_RECONFIGLPDU_SID,
                                                                                         FR_59_RENESAS_E_INV_CTRL_IDX);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    }
    else
    {
      #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
      /* Check invalid core for calling API */
      if (LucCoreIndex != Fr_59_Renesas_GaaGetController2CoreIndex[Fr_CtrlIdx])
      {
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_RECONFIGLPDU_SID,
                                                                                         FR_59_RENESAS_E_INVALID_CORE);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
      }
      #endif
    }
    /* Check if any DET error has occurred */
    if (FR_59_RENESAS_FALSE == LblErrDetect)
    {
      /*
      * Check if the value of LPduIdx is greater than the number of frames
      * configured
      */
      LpCtrlTable = (P2CONST(Fr_59_Renesas_CtrlTableType, AUTOMATIC,
                                        FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pCtrlTable);
      if (Fr_LPduIdx >= LpCtrlTable->usMaxFrames)                                                                       
      {
        /* Report to DET */
        (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_RECONFIGLPDU_SID,
                                                                                       FR_59_RENESAS_E_INV_LPDU_IDX);
        /* Default error is detected */
        LblErrDetect = FR_59_RENESAS_TRUE;
      } /* else No Action required */
      /* Check if the output parameter Fr_ChnlIdx is Valid */
      if ((FR_CHANNEL_AB < Fr_ChnlIdx) || ((Fr_ChnlIdx != LpCtrlTable->ddChannels) && (FR_CHANNEL_AB != Fr_ChnlIdx) &&
                                                                        (FR_CHANNEL_AB != LpCtrlTable->ddChannels)))
      {
        /* Report to DET */
        (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_RECONFIGLPDU_SID,
                                                                                       FR_59_RENESAS_E_INV_CHNL_IDX);
        /* Default error is detected */
        LblErrDetect = FR_59_RENESAS_TRUE;
      } /* else No Action required */
      if (FR_59_RENESAS_MAX_FRAMEID < Fr_FrameId)
      {
        /* Report Error to DET */
        (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_RECONFIGLPDU_SID,
                                                                                         FR_59_RENESAS_E_INV_FRAMEID);
        /* Default error is detected */
        LblErrDetect = FR_59_RENESAS_TRUE;
      } /* else No Action required */
      #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
      /* Check if Fr_PayloadLength is a even number */
      if (FR_59_RENESAS_ZERO == (Fr_PayloadLength % FR_59_RENESAS_TWO))
      {
        /* Convert the Received Payload length to WORDS */
        Fr_PayloadLength = Fr_PayloadLength >> FR_59_RENESAS_ONE;                                                       /* PRQA S 1338 # JV-01 */
      }
      else
      {
        /* Convert the Received Payload length to WORDS */
        Fr_PayloadLength = (Fr_PayloadLength + FR_59_RENESAS_ONE) >> FR_59_RENESAS_ONE;                                 /* PRQA S 1338, 3383 # JV-01, JV-01 */
        /* Recaculate HeaderCRC if Payload length is odd */
        Fr_HeaderCRC = Fr_59_Renesas_CalHeaderCRC(Fr_CtrlIdx, Fr_LPduIdx, Fr_PayloadLength, Fr_FrameId);                /* PRQA S 1338 # JV-01 */
      }
      #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
      /* Check invalid value of Fr_PayloadLength parameter */
      if (Fr_PayloadLength > FR_59_RENESAS_PAYLOADLENGTHMAX)
      {
        /* Report to DET */
        (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_RECONFIGLPDU_SID,
                                                                                          FR_59_RENESAS_E_INV_LENGTH);
        /* Default error is detected */
        LblErrDetect = FR_59_RENESAS_TRUE;
      } /* else No Action required */
    } /* else No Action required */
  }
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */

  /* Check if the input parameter Fr_CycleRepetition values 1, 2, 4, 8, 16, 32 and 64 */
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  if ((FR_59_RENESAS_ONE == Fr_CycleRepetition) || (FR_59_RENESAS_TWO == Fr_CycleRepetition) ||
      (FR_59_RENESAS_FOUR == Fr_CycleRepetition) || (FR_59_RENESAS_EIGHT == Fr_CycleRepetition) ||
           (FR_59_RENESAS_SIXTEEN == Fr_CycleRepetition) || (FR_59_RENESAS_THIRTYTWO == Fr_CycleRepetition) ||
                                                                       (FR_59_RENESAS_SIXTYFOUR == Fr_CycleRepetition))
  {
    /* No action required */
  }
  else
  {
    /* Report to DET */
    (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_RECONFIGLPDU_SID,
                                                                                            FR_59_RENESAS_E_INV_CYCLE);
    /* Default error is detected */
    LblErrDetect = FR_59_RENESAS_TRUE;
  }
  /* Check if the output parameter Fr_CycleOffset value is in between 0 to (Fr_CycleRepetition minus 1) */
  if (Fr_CycleOffset <= (Fr_CycleRepetition - FR_59_RENESAS_ONE))                                                       /* PRQA S 3383 # JV-01 */
  {
    /* No action required */
  }
  else
  {
    /* Report to DET */
    (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_RECONFIGLPDU_SID,
                                                                                            FR_59_RENESAS_E_INV_CYCLE);
    /* Default error is detected */
    LblErrDetect = FR_59_RENESAS_TRUE;
  }
  /* Check that Fr_HeaderCRC parameter is in the allowed range (0 to 2047) */
  if (FR_59_RENESAS_MAX_CRC < Fr_HeaderCRC)
  {
    /* Report to DET */
    (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_RECONFIGLPDU_SID,
                                                                                        FR_59_RENESAS_E_INV_HEADERCRC);
    /* Default error is detected */
    LblErrDetect = FR_59_RENESAS_TRUE;
  } /* else No Action required */
  /* Check if any DET error has occurred */
  if (FR_59_RENESAS_FALSE == LblErrDetect)
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Initialize local pointer */
    LpBufReconfigStatusPtr = Fr_59_Renesas_GpBufReconfigStatusPtr[Fr_CtrlIdx];                                          
    LpFrameConfig = (P2CONST(Fr_59_Renesas_FrameHeaderType, TYPEDEF,
                                        FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pFrameConfig);
    LpBufferHeader = &LpFrameConfig[Fr_LPduIdx];                                                                        
    /* Read the frame pointer */
    /* Check whether the frame is reconfigurable. */
    if (FR_59_RENESAS_TRUE == LpBufferHeader->blFrIfReconfigurable)                                                     
    {
      /* Get the frame Id */
      LulRegData = (Fr_FrameId & FR_59_RENESAS_FID_MASK);                                                               /* PRQA S 2985 # JV-01 */
      #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
      /* Get the configured cycle code */
      /* Since the Fr_CycleRepetition and Fr_CycleOffset masking is */
      /* considered when FR_59_RENESAS_DEV_ERROR_DETECT is ON */
      LulRegData = LulRegData | (((uint32)Fr_CycleRepetition | Fr_CycleOffset) << FR_59_RENESAS_CYC_SHIFT);
      #else
      /* Get the configured cycle code */
      LulRegData = LulRegData | ((((uint32)Fr_CycleRepetition | Fr_CycleOffset) & FR_59_RENESAS_CYC_MASK)
                                                                                           << FR_59_RENESAS_CYC_SHIFT);
      #endif
      /* Get the channel configured */
      #if (FR_59_RENESAS_AR_VERSION == FR_59_RENESAS_AR_R22_11_VERSION)
      LulRegData = LulRegData | (((uint32)Fr_ChnlIdx & FR_59_RENESAS_CHNL_MASK) << FR_59_RENESAS_CHNL_SHIFT);
      #else
      LulRegData = LulRegData | ((((uint32)Fr_ChnlIdx + (uint32)FR_59_RENESAS_ONE) & FR_59_RENESAS_CHNL_MASK)
                                                                                          << FR_59_RENESAS_CHNL_SHIFT);
      #endif
      /* Get the message buffer direction configuration bit */
      LulRegData =
          LulRegData | ((uint32)((LpBufferHeader->ucFrameConfig) & FR_59_RENESAS_CFG_MASK) << FR_59_RENESAS_CFG_SHIFT);
      /* Get the PPIT bit configured */
      LulRegData =
               LulRegData | ((uint32)((LpBufferHeader->ucPpit) & FR_59_RENESAS_PPIT_MASK) << FR_59_RENESAS_PPIT_SHIFT);
      /* Get the Transmission mode configured */
      LulRegData = LulRegData |
                  ((uint32)((LpBufferHeader->ucTransmissionMode) & FR_59_RENESAS_TXM_MASK) << FR_59_RENESAS_TXM_SHIFT);
      /* Get the message buffer interrupt configured */
      LulRegData = LulRegData | ((uint32)((LpBufferHeader->ucMsgBufferInterrupt) & FR_59_RENESAS_MBI_MASK)
                                                                                           << FR_59_RENESAS_MBI_SHIFT);

      /* Write the value of the header in FlexRay Write Header Section Register 1 and mirror address */
      LucReturnValue = Fr_59_Renesas_UpdateWRHReg(Fr_CtrlIdx, LulRegData, Fr_HeaderCRC, Fr_PayloadLength, Fr_LPduIdx);
      if (E_OK == LucReturnValue)
      {
        /* Get the message buffer Id configured for the frame and update the frame Id in the corresponding buffer
         * reconfiguration status array
         */
        LpBufReconfigStatusPtr[LpBufferHeader->ucMsgBuffer] = Fr_LPduIdx;                                               
      } /* else No Action required */
    }
    else
    {
      /* Frame is not reconfigurable */
      LucReturnValue = E_NOT_OK;
    }
  }
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  else
  {
    LucReturnValue = E_NOT_OK;
  }
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  /* Return the value */
  return (LucReturnValue);
} /* End of API Fr_59_Renesas_ReconfigLPdu */
#define FR_59_RENESAS_STOP_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
#endif /* #if (FR_59_RENESAS_RECONFIG_LPDU == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_DisableLPdu
**
** Service ID            : 0x26
**
** Description           : This service Disables the hardware resource of a
**                         LPdu for transmission/reception
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx, Fr_LPduIdx
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : The FlexRay Driver module should be initialized.
**
** Global Variables Used : Fr_59_Renesas_GaaGlobalAccPoint,
**                         Fr_59_Renesas_GpControllerConfigPtr
**                         Fr_59_Renesas_GaaGetCoreId2Index
**                         Fr_59_Renesas_GaaGetController2CoreIndex
**
** Functions Invoked     : Det_ReportError, Fr_59_Renesas_ResetWriteHeader
**
** Registers Used        : None
**
** Reference ID          : FR_DUD_ACT_017, FR_DUD_ACT_017_ERR001,
** Reference ID          : FR_DUD_ACT_017_ERR002, FR_DUD_ACT_017_ERR003, FR_DUD_ACT_017_ERR004
***********************************************************************************************************************/
#if (FR_59_RENESAS_DISABLE_LPDU == STD_ON)
#define FR_59_RENESAS_START_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PUBLIC_CODE) Fr_59_Renesas_DisableLPdu(uint8 Fr_CtrlIdx, uint16 Fr_LPduIdx)                     /* PRQA S 1503 # JV-01 */
{
  P2CONST(Fr_59_Renesas_FrameHeaderType, AUTOMATIC, FR_APPL_CONST) LpBufferHeader;
  P2CONST(Fr_59_Renesas_FrameHeaderType, TYPEDEF, FR_CONFIG_DATA) LpFrameConfig;
  /* Declare the variable to store the return value */
  Std_ReturnType LucReturnValue;
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  /* Declare local pointer to Control Table */
  P2CONST(Fr_59_Renesas_CtrlTableType, TYPEDEF, FR_CONFIG_DATA) LpCtrlTable;
  /* Declare the variable to store the DET return value */
  boolean LblErrDetect;
  /* Declare the variable to store the core index */
  uint8 LucCoreIndex;
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  uint8 ucCoreId;
  /* Get Core id for code branching */
  ucCoreId = (uint8)GetCoreID();
  /* Covert Core Id to Core Index */
  LucCoreIndex = Fr_59_Renesas_GaaGetCoreId2Index[ucCoreId];                                                            
  #else
  /* if Multicore is not configure, default coreid is 0x00
    To optimize implementation */
  LucCoreIndex = FR_59_RENESAS_ZERO;
  #endif
  /* Initialize development detection flag */
  LblErrDetect = FR_59_RENESAS_FALSE;
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  /* Initialize the return value */
  LucReturnValue = E_OK;                                                                                                /* PRQA S 2982 # JV-01 */
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  /* Check invalid core for calling API */
  if (FR_59_RENESAS_INVALID_CORE == LucCoreIndex)
  {
    /* Report to DET */
    (void)Det_ReportError(FR_59_RENESAS_MODULE_ID,FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_DISABLELPDU_SID,
                                                                                    FR_59_RENESAS_E_INVALID_CORE);
    /* Default error is detected */
    LblErrDetect = FR_59_RENESAS_TRUE;
  }
  else
  #endif
  {
    /* Check if the module is initialized */
    if (FR_59_RENESAS_FALSE == *(Fr_59_Renesas_GaaGlobalAccPoint[LucCoreIndex].pInitDone))                              
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_DISABLELPDU_SID,
                                                                                        FR_59_RENESAS_E_INIT_FAILED);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    } /* else No Action required */
    /* Check if the controller index is greater than the number of controller configured */
    if (FR_59_RENESAS_NUM_CTRL_SUPPORTED <= Fr_CtrlIdx)
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_DISABLELPDU_SID,
                                                                                      FR_59_RENESAS_E_INV_CTRL_IDX);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    }
    else
    {
      #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
      /* Check invalid core for calling API */
      if (LucCoreIndex != Fr_59_Renesas_GaaGetController2CoreIndex[Fr_CtrlIdx])
      {
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_DISABLELPDU_SID,
                                                                                         FR_59_RENESAS_E_INVALID_CORE);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
      }
      #endif
    }
    /* Check if any DET error has occurred */
    if (FR_59_RENESAS_FALSE == LblErrDetect)
    {
      /* Check if the value of LPduIdx is greater than the number of frames configured */
      LpCtrlTable = (P2CONST(Fr_59_Renesas_CtrlTableType, AUTOMATIC,
                                         FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pCtrlTable);
      if (Fr_LPduIdx >= LpCtrlTable->usMaxFrames)                                                                       
      {
        /* Report to DET */
        (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_DISABLELPDU_SID,
                                                                                      FR_59_RENESAS_E_INV_LPDU_IDX);
        /* Default error is detected */
        LblErrDetect = FR_59_RENESAS_TRUE;
      } /* else No Action required */
    } /* else No Action required */
  }
  /* Check if any DET error has occurred */
  if (FR_59_RENESAS_FALSE == LblErrDetect)
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Initialize local pointer */
    LpFrameConfig = (P2CONST(Fr_59_Renesas_FrameHeaderType, TYPEDEF,
                                        FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pFrameConfig);
    LpBufferHeader = &LpFrameConfig[Fr_LPduIdx];                                                                        
    if (FR_59_RENESAS_TRUE == LpBufferHeader->blFrIfReconfigurable)                                                     
    {
      /* Write zero to register FRWRHS1 since rest of the fields are irrelevant. */
      LucReturnValue = Fr_59_Renesas_ResetWriteHeader(Fr_CtrlIdx, Fr_LPduIdx);
    }
    else
    {
      /* Update the return value to E_NOT_OK */
      LucReturnValue = E_NOT_OK;
    }
  }
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  else
  {
    LucReturnValue = E_NOT_OK;
  }
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  /* Return the value */
  return (LucReturnValue);
} /* End of API Fr_59_Renesas_DisableLPdu */
#define FR_59_RENESAS_STOP_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
#endif /* #if (FR_59_RENESAS_DISABLE_LPDU == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_GetGlobalTime
**
** Service ID            : 0x10
**
** Description           : This service gets current global FlexRay time.
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx
**
** InOut Parameters      : None
**
** Output Parameters     : Fr_CyclePtr, Fr_MacroTickPtr
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : The POC state of Communication Controller should be
**                         in NORMAL ACTIVE STATE
**
** Global Variables Used : Fr_59_Renesas_GaaGlobalAccPoint
**                         Fr_59_Renesas_GaaGetCoreId2Index
**                         Fr_59_Renesas_GaaGetController2CoreIndex
**
** Functions Invoked     : Det_ReportError, Fr_59_Renesas_GetCycleCounter
**
** Registers Used        : None
**
** Reference ID          : FR_DUD_ACT_018, FR_DUD_ACT_018_ERR001,
** Reference ID          : FR_DUD_ACT_018_ERR002, FR_DUD_ACT_018_ERR003,
** Reference ID          : FR_DUD_ACT_018_ERR004, FR_DUD_ACT_018_ERR005
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PUBLIC_CODE)
Fr_59_Renesas_GetGlobalTime(uint8 Fr_CtrlIdx, uint8 *Fr_CyclePtr, uint16 *Fr_MacroTickPtr)                              /* PRQA S 1503 # JV-01 */
{
  /* Declare the variable to store the return value */
  Std_ReturnType LucReturnValue;
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  /* Declare the variable to store the DET return value */
  boolean LblErrDetect;
  /* Declare the variable to store the core index */
  uint8 LucCoreIndex;
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  uint8 ucCoreId;
  /* Get Core id for code branching */
  ucCoreId = (uint8)GetCoreID();
  /* Covert Core Id to Core Index */
  LucCoreIndex = Fr_59_Renesas_GaaGetCoreId2Index[ucCoreId];                                                            
  #else
  /* if Multicore is not configure, default coreid is 0x00
    To optimize implementation */
  LucCoreIndex = FR_59_RENESAS_ZERO;
  #endif
  /* Initialize development detection flag */
  LblErrDetect = FR_59_RENESAS_FALSE;
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  /* Initialize the return value */
  LucReturnValue = E_OK;                                                                                                /* PRQA S 2982 # JV-01 */
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  /* Check invalid core for calling API */
  if (FR_59_RENESAS_INVALID_CORE == LucCoreIndex)
  {
    /* Report to DET */
    (void)Det_ReportError(FR_59_RENESAS_MODULE_ID,FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_GETGLOBALTIME_SID,
                                                                                        FR_59_RENESAS_E_INVALID_CORE);
    /* Default error is detected */
    LblErrDetect = FR_59_RENESAS_TRUE;
  }
  else
  #endif
  {
    /* Check if the module is initialized */
    if (FR_59_RENESAS_FALSE == *(Fr_59_Renesas_GaaGlobalAccPoint[LucCoreIndex].pInitDone))                              
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_GETGLOBALTIME_SID,
                                                                                        FR_59_RENESAS_E_INIT_FAILED);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    } /* else No Action required */
    /* Check if the controller index is greater than the number of controller configured */
    if (FR_59_RENESAS_NUM_CTRL_SUPPORTED <= Fr_CtrlIdx)
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_GETGLOBALTIME_SID,
                                                                                         FR_59_RENESAS_E_INV_CTRL_IDX);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    }
    else
    {
      #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
      /* Check invalid core for calling API */
      if (LucCoreIndex != Fr_59_Renesas_GaaGetController2CoreIndex[Fr_CtrlIdx])
      {
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_GETGLOBALTIME_SID,
                                                                                          FR_59_RENESAS_E_INVALID_CORE);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
      }
      #endif
    }
    /* Check if the output parameter Fr_CyclePtr is NULL pointer */
    if (NULL_PTR == Fr_CyclePtr)
    {
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_GETGLOBALTIME_SID,
                                                                                        FR_59_RENESAS_E_PARAM_POINTER);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    } /* else No Action required */
    /* Check if the output parameter Fr_MacroTickPtr is NULL pointer */
    if (NULL_PTR == Fr_MacroTickPtr)
    {
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_GETGLOBALTIME_SID,
                                                                                        FR_59_RENESAS_E_PARAM_POINTER);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    } /* else No Action required */
  }
  /* Check if any DET error has occurred */
  if (FR_59_RENESAS_FALSE == LblErrDetect)
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Read the POC State by getting FLX0CCSV register value */
    LucReturnValue = Fr_59_Renesas_GetCycleCounter(Fr_CtrlIdx, Fr_CyclePtr, Fr_MacroTickPtr);
  }
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  else
  {
    LucReturnValue = E_NOT_OK;
  }
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  /* Return the value */
  return (LucReturnValue);
} /* End of API Fr_59_Renesas_GetGlobalTime */
#define FR_59_RENESAS_STOP_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_GetNmVector
**
** Service ID            : 0x22
**
** Description           : This service Gets the network management vector of
**                         the last communication cycle.
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx
**
** InOut Parameters      : None
**
** Output Parameters     : Fr_NmVectorPtr
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : The POC state of Communication Controller should be
**                         in NORMAL ACTIVE STATE
**
** Global Variables Used : Fr_59_Renesas_GaaGlobalAccPoint,
**                         Fr_59_Renesas_GpControllerConfigPtr
**                         Fr_59_Renesas_GaaGetCoreId2Index
**                         Fr_59_Renesas_GaaGetController2CoreIndex
**
** Functions Invoked     : Det_ReportError,
**                         FR_59_RENESAS_DEM_REPORT_ERROR,
**                         Fr_59_Renesas_GetPOCStsFlag,
**                         Fr_59_Renesas_NetworkManagement
**
** Registers Used        : None
**
** Reference ID          : FR_DUD_ACT_019, FR_DUD_ACT_019_ERR001,
** Reference ID          : FR_DUD_ACT_019_ERR002, FR_DUD_ACT_019_ERR003,
** Reference ID          : FR_DUD_ACT_019_ERR004, FR_DUD_ACT_019_ERR005
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PUBLIC_CODE) Fr_59_Renesas_GetNmVector(uint8 Fr_CtrlIdx, uint8 *Fr_NmVectorPtr)                 /* PRQA S 1503 # JV-01 */
{
  /* Declare local pointer to Dem Event Id */
  P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF, FR_CONFIG_DATA) LpDemEventId;
  /* Declare the variable to store the POC state */
  uint32 LulData;
  /* Declare the variable to store the return value */
  Std_ReturnType LucReturnValue;
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  /* Declare the variable to store the DET return value */
  boolean LblErrDetect;
  /* Declare the variable to store the core index */
  uint8 LucCoreIndex;
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  uint8 ucCoreId;
  /* Get Core id for code branching */
  ucCoreId = (uint8)GetCoreID();
  /* Covert Core Id to Core Index */
  LucCoreIndex = Fr_59_Renesas_GaaGetCoreId2Index[ucCoreId];                                                            
  #else
  /* if Multicore is not configure, default coreid is 0x00
    To optimize implementation */
  LucCoreIndex = FR_59_RENESAS_ZERO;
  #endif
  /* Initialize development detection flag */
  LblErrDetect = FR_59_RENESAS_FALSE;
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  /* Initialize the return value */
  LucReturnValue = E_OK;                                                                                                /* PRQA S 2982 # JV-01 */
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  /* Check invalid core for calling API */
  if (FR_59_RENESAS_INVALID_CORE == LucCoreIndex)
  {
    /* Report to DET */
    (void)Det_ReportError(FR_59_RENESAS_MODULE_ID,FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_GETNMVECTOR_SID,
                                                                                        FR_59_RENESAS_E_INVALID_CORE);
    /* Default error is detected */
    LblErrDetect = FR_59_RENESAS_TRUE;
  }
  else
  #endif
  {
    /* Check if the module is initialized */
    if (FR_59_RENESAS_FALSE == *(Fr_59_Renesas_GaaGlobalAccPoint[LucCoreIndex].pInitDone))                              
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_GETNMVECTOR_SID,
                                                                                          FR_59_RENESAS_E_INIT_FAILED);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    } /* else No Action required */
    /* Check if the controller index is greater than the number of controller configured */
    if (FR_59_RENESAS_NUM_CTRL_SUPPORTED <= Fr_CtrlIdx)
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_GETNMVECTOR_SID,
                                                                                         FR_59_RENESAS_E_INV_CTRL_IDX);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    }
    else
    {
      #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
      /* Check invalid core for calling API */
      if (LucCoreIndex != Fr_59_Renesas_GaaGetController2CoreIndex[Fr_CtrlIdx])
      {
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_GETNMVECTOR_SID,
                                                                                         FR_59_RENESAS_E_INVALID_CORE);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
      }
      #endif
    }
    /* Check if the output parameter Fr_NmVectorPtr is NULL pointer */
    if (NULL_PTR == Fr_NmVectorPtr)
    {
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_GETNMVECTOR_SID,
                                                                                      FR_59_RENESAS_E_PARAM_POINTER);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    } /* else No Action required */
    /* Check if any DET error has occurred */
  }
  if (FR_59_RENESAS_FALSE == LblErrDetect)
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Read the POC State by getting FLX0CCSV register value */
    LulData = Fr_59_Renesas_GetPOCStsFlag(Fr_CtrlIdx);
    /* Check if the CC is in normal active state */
    if ((FR_59_RENESAS_NORMAL_ACTIVE_STATE == LulData) || (FR_59_RENESAS_NORMAL_PASSIVE_STATE == LulData))
    {
      /* Update value to NM vector output pointer */
      LucReturnValue = Fr_59_Renesas_NetworkManagement(Fr_CtrlIdx, Fr_NmVectorPtr);
    }
    else
    {
      /* Report Error to DEM */
      LpDemEventId = (P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF,
                                         FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pDemEventId);
      if (FR_59_RENESAS_DEM_NOT_CONFIGURED != LpDemEventId->usHardwareTestFailure)                                      
      {
        FR_59_RENESAS_DEM_REPORT_ERROR(LpDemEventId->usHardwareTestFailure, DEM_EVENT_STATUS_FAILED);
      } /* else No Action required */
      /* Set Return Value as E_NOT_OK */
      LucReturnValue = E_NOT_OK;
    }
  }
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  else
  {
    LucReturnValue = E_NOT_OK;
  }
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  /* Return the value */
  return (LucReturnValue);
} /* End of API Fr_59_Renesas_GetNmVector */
#define FR_59_RENESAS_STOP_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_GetNumOfStartupFrames
**
** Service ID            : 0x27
**
** Description           : This service gets the current number of startup
**                         frames seen on the cluster.
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx
**
** InOut Parameters      : None
**
** Output Parameters     : Fr_NumOfStartupFramesPtr
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : The POC state of Communication Controller should be
**                         in NORMAL ACTIVE STATE
**
** Global Variables Used : Fr_59_Renesas_GaaGlobalAccPoint
**                         Fr_59_Renesas_GaaGetCoreId2Index
**                         Fr_59_Renesas_GaaGetController2CoreIndex
**
** Functions Invoked     : Det_ReportError,
**                         Fr_59_Renesas_UpdateNumOfStartupFrame
**
** Registers Used        : None
**
** Reference ID          : FR_DUD_ACT_020, FR_DUD_ACT_020_ERR001,
** Reference ID          : FR_DUD_ACT_020_ERR002, FR_DUD_ACT_020_ERR003, FR_DUD_ACT_020_ERR004
***********************************************************************************************************************/

#define FR_59_RENESAS_START_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PUBLIC_CODE)
                                 Fr_59_Renesas_GetNumOfStartupFrames(uint8 Fr_CtrlIdx, uint8 *Fr_NumOfStartupFramesPtr) /* PRQA S 1503 # JV-01 */
{
  /* Declare the variable to store the return value */
  Std_ReturnType LucReturnValue;
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  /* Declare the variable to store the DET return value */
  boolean LblErrDetect;
  /* Declare the variable to store the core index */
  uint8 LucCoreIndex;
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  uint8 ucCoreId;
  /* Get Core id for code branching */
  ucCoreId = (uint8)GetCoreID();
  /* Covert Core Id to Core Index */
  LucCoreIndex = Fr_59_Renesas_GaaGetCoreId2Index[ucCoreId];                                                            
  #else
  /* if Multicore is not configure, default coreid is 0x00
    To optimize implementation */
  LucCoreIndex = FR_59_RENESAS_ZERO;
  #endif
  /* Initialize development detection flag */
  LblErrDetect = FR_59_RENESAS_FALSE;
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  /* Initialize the return value */
  LucReturnValue = E_OK;                                                                                                /* PRQA S 2982 # JV-01 */
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  /* Check invalid core for calling API */
  if (FR_59_RENESAS_INVALID_CORE == LucCoreIndex)
  {
    /* Report to DET */
    (void)Det_ReportError(FR_59_RENESAS_MODULE_ID,FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_GETNUMOFSTARTUPFRAMES_SID,
                                                                                        FR_59_RENESAS_E_INVALID_CORE);
    /* Default error is detected */
    LblErrDetect = FR_59_RENESAS_TRUE;
  }
  else
  #endif
  {
    /* Check if the module is initialized */
    if (FR_59_RENESAS_FALSE == *(Fr_59_Renesas_GaaGlobalAccPoint[LucCoreIndex].pInitDone))                              
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_GETNUMOFSTARTUPFRAMES_SID,
                                                                                          FR_59_RENESAS_E_INIT_FAILED);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    } /* else No Action required */
    /* Check if the controller index is greater than the number of controller configured */
    if (FR_59_RENESAS_NUM_CTRL_SUPPORTED <= Fr_CtrlIdx)
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_GETNUMOFSTARTUPFRAMES_SID,
                                                                                         FR_59_RENESAS_E_INV_CTRL_IDX);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    }
    else
    {
      #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
      /* Check invalid core for calling API */
      if (LucCoreIndex != Fr_59_Renesas_GaaGetController2CoreIndex[Fr_CtrlIdx])
      {
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_GETNUMOFSTARTUPFRAMES_SID,
                                                                                         FR_59_RENESAS_E_INVALID_CORE);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
      }
      #endif
    }
    /* Check if the output parameter Fr_NumOfStartupFramesPtr is NULL pointer */
    if (NULL_PTR == Fr_NumOfStartupFramesPtr)
    {
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_GETNUMOFSTARTUPFRAMES_SID,
                                                                                        FR_59_RENESAS_E_PARAM_POINTER);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    } /* else No Action required */
  }
  /* Check if any DET error has occurred */
  if (FR_59_RENESAS_FALSE == LblErrDetect)
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  {
    LucReturnValue = Fr_59_Renesas_UpdateNumOfStartupFrame(Fr_CtrlIdx, Fr_NumOfStartupFramesPtr);
  }
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  else
  {
    LucReturnValue = E_NOT_OK;
  }
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  /* Return the value */
  return (LucReturnValue);
} /* End of API Fr_59_Renesas_GetNumOfStartupFrames */
#define FR_59_RENESAS_STOP_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_GetChannelStatus
**
** Service ID            : 0x28
**
** Description           : This service gets the channel status information.
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx
**
** InOut Parameters      : None
**
** Output Parameters     : Fr_ChannelAStatusPtr, Fr_ChannelBStatusPtr.
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : The POC state of Communication Controller should be
**                         in NORMAL ACTIVE STATE
**
** Global Variables Used : Fr_59_Renesas_GaaGlobalAccPoint
**                         Fr_59_Renesas_GaaGetCoreId2Index
**                         Fr_59_Renesas_GaaGetController2CoreIndex
**
** Functions Invoked     : Det_ReportError,
**                         Fr_59_Renesas_ReadAggregatedStatus
**
** Registers Used        : None
**
** Reference ID          : FR_DUD_ACT_021, FR_DUD_ACT_021_ERR001,
** Reference ID          : FR_DUD_ACT_021_ERR002, FR_DUD_ACT_021_ERR003,
** Reference ID          : FR_DUD_ACT_021_ERR004, FR_DUD_ACT_021_ERR005
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PUBLIC_CODE)
           Fr_59_Renesas_GetChannelStatus(uint8 Fr_CtrlIdx, uint16 *Fr_ChannelAStatusPtr, uint16 *Fr_ChannelBStatusPtr) /* PRQA S 1503 # JV-01 */
{
  /* Declare the variable to store the return value */
  Std_ReturnType LucReturnValue;
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  /* Declare the variable to store the DET return value */
  boolean LblErrDetect;
  /* Declare the variable to store the core index */
  uint8 LucCoreIndex;
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  uint8 ucCoreId;
  /* Get Core id for code branching */
  ucCoreId = (uint8)GetCoreID();
  /* Covert Core Id to Core Index */
  LucCoreIndex = Fr_59_Renesas_GaaGetCoreId2Index[ucCoreId];                                                            
  #else
  /* if Multicore is not configure, default coreid is 0x00
    To optimize implementation */
  LucCoreIndex = FR_59_RENESAS_ZERO;
  #endif
  /* Initialize development detection flag */
  LblErrDetect = FR_59_RENESAS_FALSE;
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  /* Initialize the return value */
  LucReturnValue = E_OK;                                                                                                /* PRQA S 2982 # JV-01 */
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  /* Check invalid core for calling API */
  if (FR_59_RENESAS_INVALID_CORE == LucCoreIndex)
  {
    /* Report to DET */
    (void)Det_ReportError(FR_59_RENESAS_MODULE_ID,FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_GETCHANNELSTATUS_SID,
                                                                                        FR_59_RENESAS_E_INVALID_CORE);
    /* Default error is detected */
    LblErrDetect = FR_59_RENESAS_TRUE;
  }
  else
  #endif
  {
    /* Check if the module is initialized */
    if (FR_59_RENESAS_FALSE == *(Fr_59_Renesas_GaaGlobalAccPoint[LucCoreIndex].pInitDone))                              
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_GETCHANNELSTATUS_SID,
                                                                                          FR_59_RENESAS_E_INIT_FAILED);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    } /* else No Action required */
    /* Check if the controller index is greater than the number of controller configured */
    if (FR_59_RENESAS_NUM_CTRL_SUPPORTED <= Fr_CtrlIdx)
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_GETCHANNELSTATUS_SID,
                                                                                       FR_59_RENESAS_E_INV_CTRL_IDX);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    }
    else
    {
      #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
      /* Check invalid core for calling API */
      if (LucCoreIndex != Fr_59_Renesas_GaaGetController2CoreIndex[Fr_CtrlIdx])
      {
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_GETCHANNELSTATUS_SID,
                                                                                         FR_59_RENESAS_E_INVALID_CORE);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
      }
      #endif
    }
    /* Check if the output parameter Fr_ChannelAStatusPtr is NULL pointer */
    if (NULL_PTR == Fr_ChannelAStatusPtr)
    {
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_GETCHANNELSTATUS_SID,
                                                                                         FR_59_RENESAS_E_PARAM_POINTER);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    } /* else No Action required */
    /* Check if the output parameter Fr_ChannelBStatusPtr is NULL pointer */
    if (NULL_PTR == Fr_ChannelBStatusPtr)
    {
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_GETCHANNELSTATUS_SID,
                                                                                        FR_59_RENESAS_E_PARAM_POINTER);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    } /* else No Action required */
  }
  /* Check if any DET error has occurred */
  if (FR_59_RENESAS_FALSE == LblErrDetect)
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Update Channel status pointer */
    LucReturnValue = Fr_59_Renesas_ReadAggregatedStatus(Fr_CtrlIdx, Fr_ChannelAStatusPtr, Fr_ChannelBStatusPtr);
  }
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  else
  {
    LucReturnValue = E_NOT_OK;
  }
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  /* Return the value */
  return (LucReturnValue);
} /* End of API Fr_59_Renesas_GetChannelStatus */
#define FR_59_RENESAS_STOP_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_GetClockCorrection
**
** Service ID            : 0x29
**
** Description           : This service gets the current clock correction
**                         values.
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx
**
** InOut Parameters      : None
**
** Output Parameters     : Fr_RateCorrectionPtr, Fr_OffsetCorrectionPtr.
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : The FlexRay Driver module should be initialized.
**
** Global Variables Used : Fr_59_Renesas_GaaGlobalAccPoint
**                         Fr_59_Renesas_GaaGetCoreId2Index
**                         Fr_59_Renesas_GaaGetController2CoreIndex
**
** Functions Invoked     : Det_ReportError,
**                         Fr_59_Renesas_GetCorrectionValue
**
** Registers Used        : None
**
** Reference ID          : FR_DUD_ACT_022, FR_DUD_ACT_022_ERR001,
** Reference ID          : FR_DUD_ACT_022_ERR002, FR_DUD_ACT_022_ERR003,
** Reference ID          : FR_DUD_ACT_022_ERR004, FR_DUD_ACT_022_ERR005
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PUBLIC_CODE)
       Fr_59_Renesas_GetClockCorrection(uint8 Fr_CtrlIdx, sint16 *Fr_RateCorrectionPtr, sint32 *Fr_OffsetCorrectionPtr) /* PRQA S 1503 # JV-01 */
{
  /* Declare the variable to store the return value */
  Std_ReturnType LucReturnValue;
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  /* Declare the variable to store the DET return value */
  boolean LblErrDetect;
  /* Declare the variable to store the core index */
  uint8 LucCoreIndex;
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  uint8 ucCoreId;
  /* Get Core id for code branching */
  ucCoreId = (uint8)GetCoreID();
  /* Covert Core Id to Core Index */
  LucCoreIndex = Fr_59_Renesas_GaaGetCoreId2Index[ucCoreId];                                                            
  #else
  /* if Multicore is not configure, default coreid is 0x00
    To optimize implementation */
  LucCoreIndex = FR_59_RENESAS_ZERO;
  #endif
  /* Initialize development detection flag */
  LblErrDetect = FR_59_RENESAS_FALSE;
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  /* Initialize the return value */
  LucReturnValue = E_OK;                                                                                                /* PRQA S 2982 # JV-01 */
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  /* Check invalid core for calling API */
  if (FR_59_RENESAS_INVALID_CORE == LucCoreIndex)
  {
    /* Report to DET */
    (void)Det_ReportError(FR_59_RENESAS_MODULE_ID,FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_GETCLOCKCORRECTION_SID,
                                                                                        FR_59_RENESAS_E_INVALID_CORE);
    /* Default error is detected */
    LblErrDetect = FR_59_RENESAS_TRUE;
  }
  else
  #endif
  {
    /* Check if the module is initialized */
    if (FR_59_RENESAS_FALSE == *(Fr_59_Renesas_GaaGlobalAccPoint[LucCoreIndex].pInitDone))                              
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_GETCLOCKCORRECTION_SID,
                                                                                           FR_59_RENESAS_E_INIT_FAILED);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    } /* else No Action required */
    /* Check if the controller index is greater than the number of controller configured */
    if (FR_59_RENESAS_NUM_CTRL_SUPPORTED <= Fr_CtrlIdx)
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_GETCLOCKCORRECTION_SID,
                                                                                        FR_59_RENESAS_E_INV_CTRL_IDX);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    }
    else
    {
      #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
      /* Check invalid core for calling API */
      if (LucCoreIndex != Fr_59_Renesas_GaaGetController2CoreIndex[Fr_CtrlIdx])
      {
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_GETCLOCKCORRECTION_SID,
                                                                                        FR_59_RENESAS_E_INVALID_CORE);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
      }
      #endif
    }
    /* Check if the output parameter Fr_RateCorrectionPtr is NULL pointer */
    if (NULL_PTR == Fr_RateCorrectionPtr)
    {
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_GETCLOCKCORRECTION_SID,
                                                                                      FR_59_RENESAS_E_PARAM_POINTER);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    } /* else No Action required */
    /* Check if the output parameter Fr_OffsetCorrectionPtr is NULL pointer */
    if (NULL_PTR == Fr_OffsetCorrectionPtr)
    {
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_GETCLOCKCORRECTION_SID,
                                                                                       FR_59_RENESAS_E_PARAM_POINTER);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    } /* else No Action required */
  }
  /* Check if any DET error has occurred */
  if (FR_59_RENESAS_FALSE == LblErrDetect)
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Update Rate correction and Offset correction value to input pointer */
    LucReturnValue = Fr_59_Renesas_GetCorrectionValue(Fr_CtrlIdx, Fr_RateCorrectionPtr, Fr_OffsetCorrectionPtr);
  }
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  else
  {
    LucReturnValue = E_NOT_OK;
  }
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  /* Return the value */
  return (LucReturnValue);
} /* End of API Fr_59_Renesas_GetClockCorrection */
#define FR_59_RENESAS_STOP_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_GetSyncFrameList
**
** Service ID            : 0x2a
**
** Description           : This service Gets a list of syncframes received or
**                         transmitted on channel A and channel B via the even
**                         and odd communication cycle.
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx, Fr_ListSize
**
** InOut Parameters      : None
**
** Output Parameters     : Fr_ChannelAEvenListPtr, Fr_ChannelBEvenListPtr,
**                         Fr_ChannelAOddListPtr and Fr_ChannelBOddListPtr.
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : The FlexRay Driver module should be initialized.
**
** Global Variables Used : Fr_59_Renesas_GaaGlobalAccPoint
**                         Fr_59_Renesas_GaaGetCoreId2Index
**                         Fr_59_Renesas_GaaGetController2CoreIndex
**
** Functions Invoked     : Det_ReportError, Fr_59_Renesas_UpdateSyncFrameList
**
** Registers Used        : None
**
** Reference ID          : FR_DUD_ACT_023, FR_DUD_ACT_023_ERR001,
** Reference ID          : FR_DUD_ACT_023_ERR002, FR_DUD_ACT_023_ERR003,
** Reference ID          : FR_DUD_ACT_023_ERR004, FR_DUD_ACT_023_ERR005,
** Reference ID          : FR_DUD_ACT_023_ERR006, FR_DUD_ACT_023_ERR007, FR_DUD_ACT_023_ERR008
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PUBLIC_CODE)
Fr_59_Renesas_GetSyncFrameList(uint8 Fr_CtrlIdx, uint8 Fr_ListSize, uint16 *Fr_ChannelAEvenListPtr,                     /* PRQA S 1503 # JV-01 */
                          uint16 *Fr_ChannelBEvenListPtr, uint16 *Fr_ChannelAOddListPtr, uint16 *Fr_ChannelBOddListPtr)
{
  /* Declare the variable to store the return value */
  Std_ReturnType LucReturnValue;
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  /* Declare the variable to store the DET return value */
  boolean LblErrDetect;
  /* Declare the variable to store the core index */
  uint8 LucCoreIndex;
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  uint8 ucCoreId;
  /* Get Core id for code branching */
  ucCoreId = (uint8)GetCoreID();
  /* Covert Core Id to Core Index */
  LucCoreIndex = Fr_59_Renesas_GaaGetCoreId2Index[ucCoreId];                                                            
  #else
  /* if Multicore is not configure, default coreid is 0x00
    To optimize implementation */
  LucCoreIndex = FR_59_RENESAS_ZERO;
  #endif
  /* Initialize development detection flag */
  LblErrDetect = FR_59_RENESAS_FALSE;
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  /* Initialize the return value to E_OK */
  LucReturnValue = E_OK;
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  /* Check invalid core for calling API */
  if (FR_59_RENESAS_INVALID_CORE == LucCoreIndex)
  {
    /* Report to DET */
    (void)Det_ReportError(FR_59_RENESAS_MODULE_ID,FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_GETSYNCFRAMELIST_SID,
                                                                                        FR_59_RENESAS_E_INVALID_CORE);
    /* Default error is detected */
    LblErrDetect = FR_59_RENESAS_TRUE;
  }
  else
  #endif
  {
    /* Check if the module is initialized */
    if (FR_59_RENESAS_FALSE == *(Fr_59_Renesas_GaaGlobalAccPoint[LucCoreIndex].pInitDone))                              
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_GETSYNCFRAMELIST_SID,
                                                                                         FR_59_RENESAS_E_INIT_FAILED);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    } /* else No Action required */
    /* Check if the controller index is greater than the number of controller configured */
    if (FR_59_RENESAS_NUM_CTRL_SUPPORTED <= Fr_CtrlIdx)
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_GETSYNCFRAMELIST_SID,
                                                                                        FR_59_RENESAS_E_INV_CTRL_IDX);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    }
    else
    {
      #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
      /* Check invalid core for calling API */
      if (LucCoreIndex != Fr_59_Renesas_GaaGetController2CoreIndex[Fr_CtrlIdx])
      {
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_GETSYNCFRAMELIST_SID,
                                                                                         FR_59_RENESAS_E_INVALID_CORE);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
      }
      #endif
    }
    /* Check if the input Fr_ListSize is not in range 1..15 */
    if ((FR_59_RENESAS_MAX_FRAMELIST_SIZE < Fr_ListSize) || (FR_59_RENESAS_ZERO == Fr_ListSize))
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_GETSYNCFRAMELIST_SID,
                                                                                 FR_59_RENESAS_E_INV_FRAMELIST_SIZE);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    } /* else No Action required */
    /* Check if the output parameter Fr_ChannelAEvenListPtr is NULL pointer */
    if (NULL_PTR == Fr_ChannelAEvenListPtr)
    {
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_GETSYNCFRAMELIST_SID,
                                                                                       FR_59_RENESAS_E_PARAM_POINTER);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    } /* else No Action required */
    /* Check if the output parameter Fr_ChannelBEvenListPtr is NULL pointer */
    if (NULL_PTR == Fr_ChannelBEvenListPtr)
    {
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_GETSYNCFRAMELIST_SID,
                                                                                      FR_59_RENESAS_E_PARAM_POINTER);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    } /* else No Action required */
    /* Check if the output parameter Fr_ChannelAOddListPtr is NULL pointer */
    if (NULL_PTR == Fr_ChannelAOddListPtr)
    {
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_GETSYNCFRAMELIST_SID,
                                                                                      FR_59_RENESAS_E_PARAM_POINTER);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    } /* else No Action required */
    /* Check if the output parameter Fr_ChannelBOddListPtr is NULL pointer */
    if (NULL_PTR == Fr_ChannelBOddListPtr)
    {
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_GETSYNCFRAMELIST_SID,
                                                                                      FR_59_RENESAS_E_PARAM_POINTER);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    } /* else No Action required */
  }
  /* Check if any DET error has occurred */
  if (FR_59_RENESAS_FALSE == LblErrDetect)
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  {
    Fr_59_Renesas_UpdateSyncFrameList(Fr_CtrlIdx, Fr_ListSize, Fr_ChannelAEvenListPtr, Fr_ChannelBEvenListPtr,
                                                                         Fr_ChannelAOddListPtr, Fr_ChannelBOddListPtr);
  }
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  else
  {
    LucReturnValue = E_NOT_OK;
  }
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  /* Return the value */
  return (LucReturnValue);
} /* End of API Fr_59_Renesas_GetSyncFrameList */
#define FR_59_RENESAS_STOP_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_GetWakeupRxStatus
**
** Service ID            : 0x2b
**
** Description           : This service Gets the wakeup received information
**                         from the FlexRay controller.
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx
**
** InOut Parameters      : None
**
** Output Parameters     : Fr_WakeupRxStatusPtr
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : The FlexRay Driver module should be initialized.
**
** Global Variables Used : Fr_59_Renesas_GaaGlobalAccPoint
**                         Fr_59_Renesas_GaaGetCoreId2Index
**                         Fr_59_Renesas_GaaGetController2CoreIndex
**
** Functions Invoked     : Det_ReportError, Fr_59_Renesas_UpdateWakeupRxSts
**
** Registers Used        : None
**
** Reference ID          : FR_DUD_ACT_024, FR_DUD_ACT_024_ERR001,
** Reference ID          : FR_DUD_ACT_024_ERR002, FR_DUD_ACT_024_ERR003, FR_DUD_ACT_024_ERR004
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PUBLIC_CODE) Fr_59_Renesas_GetWakeupRxStatus(uint8 Fr_CtrlIdx, uint8 *Fr_WakeupRxStatusPtr)     /* PRQA S 1503 # JV-01 */
{
  /* Declare the variable to store the return value */
  Std_ReturnType LucReturnValue;
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  /* Declare the variable to store the DET return value */
  boolean LblErrDetect;
  /* Declare the variable to store the core index */
  uint8 LucCoreIndex;
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  uint8 ucCoreId;
  /* Get Core id for code branching */
  ucCoreId = (uint8)GetCoreID();
  /* Covert Core Id to Core Index */
  LucCoreIndex = Fr_59_Renesas_GaaGetCoreId2Index[ucCoreId];                                                            
  #else
  /* if Multicore is not configure, default coreid is 0x00
    To optimize implementation */
  LucCoreIndex = FR_59_RENESAS_ZERO;
  #endif
  /* Initialize development detection flag */
  LblErrDetect = FR_59_RENESAS_FALSE;
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  /* Initialize the return value */
  LucReturnValue = E_OK;                                                                                                /* PRQA S 2982 # JV-01 */
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  /* Check invalid core for calling API */
  if (FR_59_RENESAS_INVALID_CORE == LucCoreIndex)
  {
    /* Report to DET */
    (void)Det_ReportError(FR_59_RENESAS_MODULE_ID,FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_GETWAKEUPRXSTATUS_SID,
                                                                                        FR_59_RENESAS_E_INVALID_CORE);
    /* Default error is detected */
    LblErrDetect = FR_59_RENESAS_TRUE;
  }
  else
  #endif
  {
    /* Check if the module is initialized */
    if (FR_59_RENESAS_FALSE == *(Fr_59_Renesas_GaaGlobalAccPoint[LucCoreIndex].pInitDone))                              
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_GETWAKEUPRXSTATUS_SID,
                                                                                         FR_59_RENESAS_E_INIT_FAILED);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    } /* else No Action required */
    /* Check if the controller index is greater than the number of controller configured */
    if (FR_59_RENESAS_NUM_CTRL_SUPPORTED <= Fr_CtrlIdx)
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_GETWAKEUPRXSTATUS_SID,
                                                                                       FR_59_RENESAS_E_INV_CTRL_IDX);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    }
    else
    {
      #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
      /* Check invalid core for calling API */
      if (LucCoreIndex != Fr_59_Renesas_GaaGetController2CoreIndex[Fr_CtrlIdx])
      {
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_GETWAKEUPRXSTATUS_SID,
                                                                                         FR_59_RENESAS_E_INVALID_CORE);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
      }
      #endif
    }
    /* Check if the output parameter Fr_WakeupRxStatusPtr is NULL pointer */
    if (NULL_PTR == Fr_WakeupRxStatusPtr)
    {
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_GETWAKEUPRXSTATUS_SID,
                                                                                      FR_59_RENESAS_E_PARAM_POINTER);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    } /* else No Action required */
  }
  /* Check if any DET error has occurred */
  if (FR_59_RENESAS_FALSE == LblErrDetect)
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Update value for Wakeup Rx status */
    LucReturnValue = Fr_59_Renesas_UpdateWakeupRxSts(Fr_CtrlIdx, Fr_WakeupRxStatusPtr);
  }
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  else
  {
    LucReturnValue = E_NOT_OK;
  }
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  /* Return the value */
  return (LucReturnValue);
} /* End of API Fr_59_Renesas_GetWakeupRxStatus */
#define FR_59_RENESAS_STOP_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_SetAbsoluteTimer
**
** Service ID            : 0x11
**
** Description           : This service sets the cycle and macrotick offset
**                         value at which the absolute timer interrupt occurs.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx, Fr_AbsTimerIdx, Fr_Cycle and Fr_Offset
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : The POC state of Communication Controller should be
**                         in NORMAL ACTIVE STATE
**
** Global Variables Used : Fr_59_Renesas_GaaGlobalAccPoint,
**                         Fr_59_Renesas_GpControllerConfigPtr
**                         Fr_59_Renesas_GaaGetCoreId2Index
**                         Fr_59_Renesas_GaaGetController2CoreIndex
**
** Functions Invoked     : Det_ReportError,
**                         Fr_59_Renesas_GetPOCStsFlag,
**                         Fr_59_Renesas_StartTimer,
**                         Det_ReportRuntimeError(AR2211)
**
** Registers Used        : None
**
** Reference ID          : FR_DUD_ACT_025, FR_DUD_ACT_025_ERR001,
** Reference ID          : FR_DUD_ACT_025_ERR002, FR_DUD_ACT_025_ERR003,
** Reference ID          : FR_DUD_ACT_025_ERR004, FR_DUD_ACT_025_ERR005,
** Reference ID          : FR_DUD_ACT_025_ERR006, FR_DUD_ACT_025_ERR007, FR_DUD_ACT_025_ERR008
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PUBLIC_CODE)
Fr_59_Renesas_SetAbsoluteTimer(uint8 Fr_CtrlIdx, uint8 Fr_AbsTimerIdx, uint8 Fr_Cycle, uint16 Fr_Offset)                /* PRQA S 1503 # JV-01 */
{
  /* Declare the variable to store POC state */
  uint32 LulData;
  /* Declare the variable to store the return value */
  Std_ReturnType LucReturnValue;
  #if ((FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) || (FR_59_RENESAS_AR_VERSION == FR_59_RENESAS_AR_R22_11_VERSION))
  /* Declare the variable to store the DET return value */
  boolean LblErrDetect;
  #endif
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  /* Declare local pointer to Control Table */
  P2CONST(Fr_59_Renesas_CtrlTableType, TYPEDEF, FR_CONFIG_DATA) LpCtrlTable;
  /* Declare the variable to store the core index */
  uint8 LucCoreIndex;
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  uint8 ucCoreId;
  /* Get Core id for code branching */
  ucCoreId = (uint8)GetCoreID();
  /* Covert Core Id to Core Index */
  LucCoreIndex = Fr_59_Renesas_GaaGetCoreId2Index[ucCoreId];                                                            
  #else
  /* if Multicore is not configure, default coreid is 0x00
    To optimize implementation */
  LucCoreIndex = FR_59_RENESAS_ZERO;
  #endif
  #endif
  #if ((FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) || (FR_59_RENESAS_AR_VERSION == FR_59_RENESAS_AR_R22_11_VERSION))
  /* Initialize development detection flag */
  LblErrDetect = FR_59_RENESAS_FALSE;
  #endif
  /* Initialize the return value */
  LucReturnValue = E_OK;                                                                                                /* PRQA S 2982 # JV-01 */
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  /* Check invalid core for calling API */
  if (FR_59_RENESAS_INVALID_CORE == LucCoreIndex)
  {
    /* Report to DET */
    (void)Det_ReportError(FR_59_RENESAS_MODULE_ID,FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_SETABSOLUTETIMER_SID,
                                                                                        FR_59_RENESAS_E_INVALID_CORE);
    /* Default error is detected */
    LblErrDetect = FR_59_RENESAS_TRUE;
  }
  else
  #endif
  {
    /* Check if the module is initialized */
    if (FR_59_RENESAS_FALSE == *(Fr_59_Renesas_GaaGlobalAccPoint[LucCoreIndex].pInitDone))                              
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_SETABSOLUTETIMER_SID,
                                                                                         FR_59_RENESAS_E_INIT_FAILED);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    } /* else No Action required */
    /* Check if the controller index is greater than the number of controller configured */
    if (FR_59_RENESAS_NUM_CTRL_SUPPORTED <= Fr_CtrlIdx)
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_SETABSOLUTETIMER_SID,
                                                                                      FR_59_RENESAS_E_INV_CTRL_IDX);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    }
    else
    {
      #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
      /* Check invalid core for calling API */
      if (LucCoreIndex != Fr_59_Renesas_GaaGetController2CoreIndex[Fr_CtrlIdx])
      {
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_SETABSOLUTETIMER_SID,
                                                                                         FR_59_RENESAS_E_INVALID_CORE);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
      }
      #endif
    }
    }
  /* Check if any DET error has occurred */
  if (FR_59_RENESAS_FALSE == LblErrDetect)
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
    /* Check if the input parameter Fr_Offset is greater than the maximum value of macroticks per cycle */
    LpCtrlTable = (P2CONST(Fr_59_Renesas_CtrlTableType, AUTOMATIC,
                                          FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pCtrlTable);
    if (Fr_Offset > (LpCtrlTable->usMaxMacroPerCycle))                                                                  
    {
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_SETABSOLUTETIMER_SID,
                                                                                           FR_59_RENESAS_E_INV_OFFSET);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    } /* else No Action required */
    /*
     * Check if the absolute timer configured is greater than the number
     * of absolute timers configured for this controller
     */
    if ((LpCtrlTable->ucAbsTimerCount) <= Fr_AbsTimerIdx)
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_SETABSOLUTETIMER_SID,
                                                                                        FR_59_RENESAS_E_INV_TIMER_IDX);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    } /* else No Action required */
    /*
     * Check if the input parameter Fr_Cycle is greater than the maximum
     * number of cycles in the communication cycle
     */
    if (FR_59_RENESAS_MAX_CYCLE_COUNT < Fr_Cycle)
    {
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_SETABSOLUTETIMER_SID,
                                                                                            FR_59_RENESAS_E_INV_CYCLE);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    } /* else No Action required */
    #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
    /* Read the POC state by getting the value of the register FRCCSV */
    LulData = Fr_59_Renesas_GetPOCStsFlag(Fr_CtrlIdx);
    /* Check if the POC is not in NORMAL_ACTIVE or NORMAL_PASSIVE State */
    if ((FR_59_RENESAS_NORMAL_ACTIVE_STATE != LulData) && (FR_59_RENESAS_NORMAL_PASSIVE_STATE != LulData))
    {
      #if ((FR_59_RENESAS_AR_VERSION == FR_59_RENESAS_AR_422_VERSION) && (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON))
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_SETABSOLUTETIMER_SID,
                                                                                         FR_59_RENESAS_E_INV_POCSTATE);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
      #endif
      #if (FR_59_RENESAS_AR_VERSION == FR_59_RENESAS_AR_R22_11_VERSION)
      /* Report to DET */
      (void)Det_ReportRuntimeError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID,
                                                     FR_59_RENESAS_SETABSOLUTETIMER_SID, FR_59_RENESAS_E_INV_POCSTATE);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
      #endif
    } /* else No Action required */
  }
  #if ((FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) ||(FR_59_RENESAS_AR_VERSION == FR_59_RENESAS_AR_R22_11_VERSION))
  /* Check if any DET error has occurred */
  if (FR_59_RENESAS_FALSE == LblErrDetect)
  #endif
  {
    /* Enable to start the timer */
    LucReturnValue = Fr_59_Renesas_StartTimer(Fr_CtrlIdx, Fr_AbsTimerIdx, Fr_Cycle, Fr_Offset);
  }
  #if ((FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) || (FR_59_RENESAS_AR_VERSION == FR_59_RENESAS_AR_R22_11_VERSION))
  else
  {
    LucReturnValue = E_NOT_OK;
  }
  #endif
  /* Return the value */
  return (LucReturnValue);
} /* End of API Fr_59_Renesas_SetAbsoluteTimer */
#define FR_59_RENESAS_STOP_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_CancelAbsoluteTimer
**
** Service ID            : 0x13
**
** Description           : This service stops the absolute timer specified by
**                         the absolute timer index
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx, Fr_AbsTimerIdx
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : The FlexRay Driver module should be initialized
**
** Global Variables Used : Fr_59_Renesas_GaaGlobalAccPoint,
**                         Fr_59_Renesas_GpControllerConfigPtr
**                         Fr_59_Renesas_GaaGetCoreId2Index
**                         Fr_59_Renesas_GaaGetController2CoreIndex
**
** Functions Invoked     : Det_ReportError, Fr_59_Renesas_CancelTimerInterrupt
**
** Registers Used        : None
**
** Reference ID          : FR_DUD_ACT_026, FR_DUD_ACT_026_ERR001,
** Reference ID          : FR_DUD_ACT_026_ERR002, FR_DUD_ACT_026_ERR003, FR_DUD_ACT_026_ERR004
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PUBLIC_CODE) Fr_59_Renesas_CancelAbsoluteTimer(uint8 Fr_CtrlIdx, uint8 Fr_AbsTimerIdx)          /* PRQA S 1503 # JV-01 */
{
  /* Declare the variable to store the return value */
  Std_ReturnType LucReturnValue;
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  /* Declare local pointer to Control Table */
  P2CONST(Fr_59_Renesas_CtrlTableType, TYPEDEF, FR_CONFIG_DATA) LpCtrlTable;
  /* Declare the variable to store the DET return value */
  boolean LblErrDetect;
  /* Declare the variable to store the core index */
  uint8 LucCoreIndex;
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  uint8 ucCoreId;
  /* Get Core id for code branching */
  ucCoreId = (uint8)GetCoreID();
  /* Covert Core Id to Core Index */
  LucCoreIndex = Fr_59_Renesas_GaaGetCoreId2Index[ucCoreId];                                                            
  #else
  /* if Multicore is not configure, default coreid is 0x00
    To optimize implementation */
  LucCoreIndex = FR_59_RENESAS_ZERO;
  #endif
  /* Initialize development detection flag */
  LblErrDetect = FR_59_RENESAS_FALSE;
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  /* Initialize the return value to E_OK */
  LucReturnValue = E_OK;
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  /* Check invalid core for calling API */
  if (FR_59_RENESAS_INVALID_CORE == LucCoreIndex)
  {
    /* Report to DET */
    (void)Det_ReportError(FR_59_RENESAS_MODULE_ID,FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_CANCELABSOLUTETIMER_SID,
                                                                                        FR_59_RENESAS_E_INVALID_CORE);
    /* Default error is detected */
    LblErrDetect = FR_59_RENESAS_TRUE;
  }
  else
  #endif
  {
    /* Check if the module is initialized */
    if (FR_59_RENESAS_FALSE == *(Fr_59_Renesas_GaaGlobalAccPoint[LucCoreIndex].pInitDone))                              
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_CANCELABSOLUTETIMER_SID,
                                                                                         FR_59_RENESAS_E_INIT_FAILED);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    } /* else No Action required */
    /* Check if the controller index is greater than the number of controller configured */
    if (FR_59_RENESAS_NUM_CTRL_SUPPORTED <= Fr_CtrlIdx)
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_CANCELABSOLUTETIMER_SID,
                                                                                       FR_59_RENESAS_E_INV_CTRL_IDX);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    }
    else
    {
      #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
      /* Check invalid core for calling API */
      if (LucCoreIndex != Fr_59_Renesas_GaaGetController2CoreIndex[Fr_CtrlIdx])
      {
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_CANCELABSOLUTETIMER_SID,
                                                                                        FR_59_RENESAS_E_INVALID_CORE);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
      }
      #endif
    }
    /* Check if any DET error has occurred */
    if (FR_59_RENESAS_FALSE == LblErrDetect)
    {
      /* Store the global pointer to FlexRay Control Table */
      LpCtrlTable = (P2CONST(Fr_59_Renesas_CtrlTableType, AUTOMATIC,
                                        FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pCtrlTable);
      /*
      * Check if the absolute timer configured is greater than the number
      * of absolute timers configured for this controller
      */
      if ((LpCtrlTable->ucAbsTimerCount) <= Fr_AbsTimerIdx)                                                             
      {
        /* Report Error to DET */
        (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_CANCELABSOLUTETIMER_SID,
                                                                                        FR_59_RENESAS_E_INV_TIMER_IDX);
        /* Default error is detected */
        LblErrDetect = FR_59_RENESAS_TRUE;
      } /* else No Action required */
    } /* else No Action required */
  }
  /* Check if any DET error has occurred */
  if (FR_59_RENESAS_FALSE == LblErrDetect)
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Halt to cancel the timer */
    Fr_59_Renesas_CancelTimerInterrupt(Fr_CtrlIdx, Fr_AbsTimerIdx);
  }
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  else
  {
    LucReturnValue = E_NOT_OK;
  }
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  /* Return the value */
  return (LucReturnValue);
} /* End of API Fr_59_Renesas_CancelAbsoluteTimer */
#define FR_59_RENESAS_STOP_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_EnableAbsoluteTimerIRQ
**
** Service ID            : 0x15
**
** Description           : This service enables the interrupt line related to
**                         the absolute timer index
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx, Fr_AbsTimerIdx
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : The FlexRay Driver module should be initialized.
**
** Global Variables Used : Fr_59_Renesas_GaaGlobalAccPoint,
**                         Fr_59_Renesas_GpControllerConfigPtr
**                         Fr_59_Renesas_GaaGetCoreId2Index
**                         Fr_59_Renesas_GaaGetController2CoreIndex
**
** Functions Invoked     : Det_ReportError, Fr_59_Renesas_EnableTimerInterrupt
**
** Registers Used        : None
**
** Reference ID          : FR_DUD_ACT_027, FR_DUD_ACT_027_ERR001,
** Reference ID          : FR_DUD_ACT_027_ERR002, FR_DUD_ACT_027_ERR003, FR_DUD_ACT_027_ERR004
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PUBLIC_CODE) Fr_59_Renesas_EnableAbsoluteTimerIRQ(uint8 Fr_CtrlIdx, uint8 Fr_AbsTimerIdx)       /* PRQA S 1503 # JV-01 */
{
  /* Declare the variable to store the return value */
  Std_ReturnType LucReturnValue;
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  /* Declare local pointer to Control Table */
  P2CONST(Fr_59_Renesas_CtrlTableType, TYPEDEF, FR_CONFIG_DATA) LpCtrlTable;
  /* Declare the variable to store the DET return value */
  boolean LblErrDetect;
  /* Declare the variable to store the core index */
  uint8 LucCoreIndex;
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  uint8 ucCoreId;
  /* Get Core id for code branching */
  ucCoreId = (uint8)GetCoreID();
  /* Covert Core Id to Core Index */
  LucCoreIndex = Fr_59_Renesas_GaaGetCoreId2Index[ucCoreId];                                                            
  #else
  /* if Multicore is not configure, default coreid is 0x00
    To optimize implementation */
  LucCoreIndex = FR_59_RENESAS_ZERO;
  #endif
  /* Initialize development detection flag */
  LblErrDetect = FR_59_RENESAS_FALSE;
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  /* Initialize the return value to E_OK */
  LucReturnValue = E_OK;
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  /* Check invalid core for calling API */
  if (FR_59_RENESAS_INVALID_CORE == LucCoreIndex)
  {
    /* Report to DET */
    (void)Det_ReportError(FR_59_RENESAS_MODULE_ID,FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_ENABLEABSOLUTETIMER_IRQ_SID,
                                                                                        FR_59_RENESAS_E_INVALID_CORE);
    /* Default error is detected */
    LblErrDetect = FR_59_RENESAS_TRUE;
  }
  else
  #endif
  {
    /* Check if the module is initialized */
    if (FR_59_RENESAS_FALSE == *(Fr_59_Renesas_GaaGlobalAccPoint[LucCoreIndex].pInitDone))                              
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, 
                                             FR_59_RENESAS_ENABLEABSOLUTETIMER_IRQ_SID, FR_59_RENESAS_E_INIT_FAILED);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    } /* else No Action required */
    /* Check if the controller index is greater than the number of controller configured */
    if (FR_59_RENESAS_NUM_CTRL_SUPPORTED <= Fr_CtrlIdx)
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID,
                                            FR_59_RENESAS_ENABLEABSOLUTETIMER_IRQ_SID, FR_59_RENESAS_E_INV_CTRL_IDX);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    }
    else
    {
      #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
      /* Check invalid core for calling API */
      if (LucCoreIndex != Fr_59_Renesas_GaaGetController2CoreIndex[Fr_CtrlIdx])
      {
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID,
                                             FR_59_RENESAS_ENABLEABSOLUTETIMER_IRQ_SID, FR_59_RENESAS_E_INVALID_CORE);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
      }
      #endif
    }
    /* Check if any DET error has occurred */
    if (FR_59_RENESAS_FALSE == LblErrDetect)
    {
      /* Store the global pointer to FlexRay Control Table */
      LpCtrlTable = (P2CONST(Fr_59_Renesas_CtrlTableType, AUTOMATIC,
                                          FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pCtrlTable);
      /*
      * Check if the absolute timer configured is greater than the number
      * of absolute timers configured for this controller
      */
      if ((LpCtrlTable->ucAbsTimerCount) <= Fr_AbsTimerIdx)                                                             
      {
        /* Report Error to DET */
        (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID,
                                            FR_59_RENESAS_ENABLEABSOLUTETIMER_IRQ_SID, FR_59_RENESAS_E_INV_TIMER_IDX);
        /* Default error is detected */
        LblErrDetect = FR_59_RENESAS_TRUE;
      } /* else No Action required */
    } /* else No Action required */
  }
  /* Check if any DET error has occurred */
  if (FR_59_RENESAS_FALSE == LblErrDetect)
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Enable the target Timer Interrupt */
    Fr_59_Renesas_EnableTimerInterrupt(Fr_CtrlIdx, Fr_AbsTimerIdx);
  }
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  else
  {
    LucReturnValue = E_NOT_OK;
  }
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  /* Return the value */
  return (LucReturnValue);
} /* End of API Fr_59_Renesas_EnableAbsoluteTimerIRQ */
#define FR_59_RENESAS_STOP_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_AckAbsoluteTimerIRQ
**
** Service ID            : 0x17
**
** Description           : This service resets the interrupt condition of
**                         the absolute timer
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx, Fr_AbsTimerIdx
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : The FlexRay Driver module should be initialized
**
** Global Variables Used : Fr_59_Renesas_GaaGlobalAccPoint,
**                         Fr_59_Renesas_GpControllerConfigPtr
**                         Fr_59_Renesas_GaaGetCoreId2Index
**                         Fr_59_Renesas_GaaGetController2CoreIndex
**
** Functions Invoked     : Det_ReportError, Fr_59_Renesas_ClearTimerInterrupt
**
** Registers Used        : None
**
** Reference ID          : FR_DUD_ACT_028, FR_DUD_ACT_028_ERR001,
** Reference ID          : FR_DUD_ACT_028_ERR002, FR_DUD_ACT_028_ERR003, FR_DUD_ACT_028_ERR004
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PUBLIC_CODE) Fr_59_Renesas_AckAbsoluteTimerIRQ(uint8 Fr_CtrlIdx, uint8 Fr_AbsTimerIdx)          /* PRQA S 1503 # JV-01 */
{
  /* Declare the variable to store the return value */
  Std_ReturnType LucReturnValue;
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  /* Declare local pointer to Control Table */
  P2CONST(Fr_59_Renesas_CtrlTableType, TYPEDEF, FR_CONFIG_DATA) LpCtrlTable;
  /* Declare the variable to store the DET return value */
  boolean LblErrDetect;
  /* Declare the variable to store the core index */
  uint8 LucCoreIndex;
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  uint8 ucCoreId;
  /* Get Core id for code branching */
  ucCoreId = (uint8)GetCoreID();
  /* Covert Core Id to Core Index */
  LucCoreIndex = Fr_59_Renesas_GaaGetCoreId2Index[ucCoreId];                                                            
  #else
  /* if Multicore is not configure, default coreid is 0x00
    To optimize implementation */
  LucCoreIndex = FR_59_RENESAS_ZERO;
  #endif
  /* Initialize development detection flag */
  LblErrDetect = FR_59_RENESAS_FALSE;
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  /* Initialize the return value */
  LucReturnValue = E_OK;                                                                                                /* PRQA S 2982 # JV-01 */
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  /* Check invalid core for calling API */
  if (FR_59_RENESAS_INVALID_CORE == LucCoreIndex)
  {
    /* Report to DET */
    (void)Det_ReportError(FR_59_RENESAS_MODULE_ID,FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_ACKABSOLUTETIMERIRQ_SID,
                                                                                        FR_59_RENESAS_E_INVALID_CORE);
    /* Default error is detected */
    LblErrDetect = FR_59_RENESAS_TRUE;
  }
  else
  #endif
  {
    /* Check if the module is initialized */
    if (FR_59_RENESAS_FALSE == *(Fr_59_Renesas_GaaGlobalAccPoint[LucCoreIndex].pInitDone))                              
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_ACKABSOLUTETIMERIRQ_SID,
                                                                                        FR_59_RENESAS_E_INIT_FAILED);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    } /* else No Action required */
    /* Check if the controller index is greater than the number of controller configured */
    if (FR_59_RENESAS_NUM_CTRL_SUPPORTED <= Fr_CtrlIdx)
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_ACKABSOLUTETIMERIRQ_SID,
                                                                                       FR_59_RENESAS_E_INV_CTRL_IDX);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    }
    else
    {
      #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
      /* Check invalid core for calling API */
      if (LucCoreIndex != Fr_59_Renesas_GaaGetController2CoreIndex[Fr_CtrlIdx])
      {
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_ACKABSOLUTETIMERIRQ_SID,
                                                                                        FR_59_RENESAS_E_INVALID_CORE);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
      }
      #endif
    }
    /* Check if any DET error has occurred */
    if (FR_59_RENESAS_FALSE == LblErrDetect)
    {
      /* Store the global pointer to FlexRay Control Table */
      LpCtrlTable = (P2CONST(Fr_59_Renesas_CtrlTableType, AUTOMATIC,
                                          FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pCtrlTable);
      /*
      * Check if the absolute timer configured is greater than the number
      * of absolute timers configured for this controller
      */
      if ((LpCtrlTable->ucAbsTimerCount) <= Fr_AbsTimerIdx)                                                             
      {
        /* Report Error to DET */
        (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_ACKABSOLUTETIMERIRQ_SID,
                                                                                        FR_59_RENESAS_E_INV_TIMER_IDX);
        /* Default error is detected */
        LblErrDetect = FR_59_RENESAS_TRUE;
      } /* else No Action required */
    } /* else No Action required */
  }
  /* Check if any DET error has occurred */
  if (FR_59_RENESAS_FALSE == LblErrDetect)
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  {
    LucReturnValue = Fr_59_Renesas_ClearTimerInterrupt(Fr_CtrlIdx, Fr_AbsTimerIdx);
  }
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  else
  {
    LucReturnValue = E_NOT_OK;
  }
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  /* Return the value */
  return (LucReturnValue);
} /* End of API Fr_59_Renesas_AckAbsoluteTimerIRQ */
#define FR_59_RENESAS_STOP_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_DisableAbsoluteTimerIRQ
**
** Service ID            : 0x19
**
** Description           : This service disables the interrupt line of an
**                         absolute timer
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx, Fr_AbsTimerIdx
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : The FlexRay Driver module should be initialized
**
** Global Variables Used : Fr_59_Renesas_GaaGlobalAccPoint,
**                         Fr_59_Renesas_GpControllerConfigPtr
**                         Fr_59_Renesas_GaaGetCoreId2Index
**                         Fr_59_Renesas_GaaGetController2CoreIndex
**
** Functions Invoked     : Det_ReportError, Fr_59_Renesas_DisableTimer
**
** Registers Used        : None
**
** Reference ID          : FR_DUD_ACT_029, FR_DUD_ACT_029_ERR001,
** Reference ID          : FR_DUD_ACT_029_ERR002, FR_DUD_ACT_029_ERR003, FR_DUD_ACT_029_ERR004
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PUBLIC_CODE) Fr_59_Renesas_DisableAbsoluteTimerIRQ(uint8 Fr_CtrlIdx, uint8 Fr_AbsTimerIdx)      /* PRQA S 1503 # JV-01 */
{
  /* Declare the variable to store the return value */
  Std_ReturnType LucReturnValue;
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  /* Declare local pointer to Control Table */
  P2CONST(Fr_59_Renesas_CtrlTableType, TYPEDEF, FR_CONFIG_DATA) LpCtrlTable;
  /* Declare the variable to store the DET return value */
  boolean LblErrDetect;
  /* Declare the variable to store the core index */
  uint8 LucCoreIndex;
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  uint8 ucCoreId;
  /* Get Core id for code branching */
  ucCoreId = (uint8)GetCoreID();
  /* Covert Core Id to Core Index */
  LucCoreIndex = Fr_59_Renesas_GaaGetCoreId2Index[ucCoreId];                                                            
  #else
  /* if Multicore is not configure, default coreid is 0x00
    To optimize implementation */
  LucCoreIndex = FR_59_RENESAS_ZERO;
  #endif
  /* Initialize development detection flag */
  LblErrDetect = FR_59_RENESAS_FALSE;
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  /* Initialize the return value to E_OK */
  LucReturnValue = E_OK;
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  /* Check invalid core for calling API */
  if (FR_59_RENESAS_INVALID_CORE == LucCoreIndex)
  {
    /* Report to DET */
    (void)Det_ReportError(FR_59_RENESAS_MODULE_ID,FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_DISABLEABSOLUTETIMERIRQ_SID,
                                                                                        FR_59_RENESAS_E_INVALID_CORE);
    /* Default error is detected */
    LblErrDetect = FR_59_RENESAS_TRUE;
  }
  else
  #endif
  {
    /* Check if the module is initialized */
    if (FR_59_RENESAS_FALSE == *(Fr_59_Renesas_GaaGlobalAccPoint[LucCoreIndex].pInitDone))                              
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, 
                                                FR_59_RENESAS_DISABLEABSOLUTETIMERIRQ_SID, FR_59_RENESAS_E_INIT_FAILED);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    } /* else No Action required */
    /* Check if the controller index is greater than the number of controller configured */
    if (FR_59_RENESAS_NUM_CTRL_SUPPORTED <= Fr_CtrlIdx)
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID,
                                            FR_59_RENESAS_DISABLEABSOLUTETIMERIRQ_SID, FR_59_RENESAS_E_INV_CTRL_IDX);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    }
    else
    {
      #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
      /* Check invalid core for calling API */
      if (LucCoreIndex != Fr_59_Renesas_GaaGetController2CoreIndex[Fr_CtrlIdx])
      {
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID,
                                             FR_59_RENESAS_DISABLEABSOLUTETIMERIRQ_SID, FR_59_RENESAS_E_INVALID_CORE);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
      }
      #endif
    }
    /* Check if any DET error has occurred */
    if (FR_59_RENESAS_FALSE == LblErrDetect)
    {
      /* Store the global pointer to FlexRay Control Table */
      LpCtrlTable = (P2CONST(Fr_59_Renesas_CtrlTableType, AUTOMATIC,
                                         FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pCtrlTable);
      /*
      * Check if the absolute timer configured is greater than the number
      * of absolute timers configured for this controller
      */
      if ((LpCtrlTable->ucAbsTimerCount) <= Fr_AbsTimerIdx)                                                             
      {
        /* Report Error to DET */
        (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID,
                                           FR_59_RENESAS_DISABLEABSOLUTETIMERIRQ_SID, FR_59_RENESAS_E_INV_TIMER_IDX);
        /* Default error is detected */
        LblErrDetect = FR_59_RENESAS_TRUE;
      } /* else No Action required */
    } /* else No Action required */
  }
  /* Check if any DET error has occurred */
  if (FR_59_RENESAS_FALSE == LblErrDetect)
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  {
    Fr_59_Renesas_DisableTimer(Fr_CtrlIdx, Fr_AbsTimerIdx);
  }
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  else
  {
    LucReturnValue = E_NOT_OK;
  }
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  /* Return the value */
  return (LucReturnValue);
} /* End of API Fr_59_Renesas_DisableAbsoluteTimerIRQ */
#define FR_59_RENESAS_STOP_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_GetAbsoluteTimerIRQStatus
**
** Service ID            : 0x20
**
** Description           : This service reads the interrupt status of an
**                         absolute timer
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx, Fr_AbsTimerIdx
**
** InOut Parameters      : None
**
** Output Parameters     : Fr_IRQStatusPtr
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : The FlexRay Driver module should be initialized
**
** Global Variables Used : Fr_59_Renesas_GaaGlobalAccPoint,
**                         Fr_59_Renesas_GpControllerConfigPtr
**                         Fr_59_Renesas_GaaGetCoreId2Index
**                         Fr_59_Renesas_GaaGetController2CoreIndex
**
** Functions Invoked     : Det_ReportError, Fr_59_Renesas_GetIrqSts
**
** Registers Used        : None
**
** Reference ID          : FR_DUD_ACT_030, FR_DUD_ACT_030_ERR001,
** Reference ID          : FR_DUD_ACT_030_ERR002, FR_DUD_ACT_030_ERR003,
** Reference ID          : FR_DUD_ACT_030_ERR004, FR_DUD_ACT_030_ERR005
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PUBLIC_CODE)
Fr_59_Renesas_GetAbsoluteTimerIRQStatus(uint8 Fr_CtrlIdx, uint8 Fr_AbsTimerIdx, boolean *Fr_IRQStatusPtr)               /* PRQA S 1503 # JV-01 */
{
  /* Declare the variable to store the return value */
  Std_ReturnType LucReturnValue;
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  /* Declare local pointer to Control Table */
  P2CONST(Fr_59_Renesas_CtrlTableType, TYPEDEF, FR_CONFIG_DATA) LpCtrlTable;
  /* Declare the variable to store the DET return value */
  boolean LblErrDetect;
  /* Declare the variable to store the core index */
  uint8 LucCoreIndex;
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  uint8 ucCoreId;
  /* Get Core id for code branching */
  ucCoreId = (uint8)GetCoreID();
  /* Covert Core Id to Core Index */
  LucCoreIndex = Fr_59_Renesas_GaaGetCoreId2Index[ucCoreId];                                                            
  #else
  /* if Multicore is not configure, default coreid is 0x00
    To optimize implementation */
  LucCoreIndex = FR_59_RENESAS_ZERO;
  #endif
  /* Initialize development detection flag */
  LblErrDetect = FR_59_RENESAS_FALSE;
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  /* Initialize the return value to E_OK */
  LucReturnValue = E_OK;
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  /* Check invalid core for calling API */
  if (FR_59_RENESAS_INVALID_CORE == LucCoreIndex)
  {
    /* Report to DET */
    (void)Det_ReportError(FR_59_RENESAS_MODULE_ID,FR_59_RENESAS_INSTANCE_ID,
                                             FR_59_RENESAS_GETABSOLUTETIMERIRQSTATUS_SID, FR_59_RENESAS_E_INVALID_CORE);
    /* Default error is detected */
    LblErrDetect = FR_59_RENESAS_TRUE;
  }
  else
  #endif
  {
    /* Check if the module is initialized */
    if (FR_59_RENESAS_FALSE == *(Fr_59_Renesas_GaaGlobalAccPoint[LucCoreIndex].pInitDone))                              
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID,
                                          FR_59_RENESAS_GETABSOLUTETIMERIRQSTATUS_SID, FR_59_RENESAS_E_INIT_FAILED);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    } /* else No Action required */
    /* Check if the controller index is greater than the number of controller configured */
    if (FR_59_RENESAS_NUM_CTRL_SUPPORTED <= Fr_CtrlIdx)
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID,
                                           FR_59_RENESAS_GETABSOLUTETIMERIRQSTATUS_SID, FR_59_RENESAS_E_INV_CTRL_IDX);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    }
    else
    {
      #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
      /* Check invalid core for calling API */
      if (LucCoreIndex != Fr_59_Renesas_GaaGetController2CoreIndex[Fr_CtrlIdx])
      {
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID,FR_59_RENESAS_INSTANCE_ID,
                                           FR_59_RENESAS_GETABSOLUTETIMERIRQSTATUS_SID, FR_59_RENESAS_E_INVALID_CORE);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
      }
      #endif
    }
    /* Check if any DET error has occurred */
    if (FR_59_RENESAS_FALSE == LblErrDetect)
    {
      /* Store the global pointer to FlexRay Control Table */
      LpCtrlTable = (P2CONST(Fr_59_Renesas_CtrlTableType, AUTOMATIC,
                                        FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pCtrlTable);
      /*
      * Check if the absolute timer configured is greater than the number
      * of absolute timers configured for this controller
      */
      if ((LpCtrlTable->ucAbsTimerCount) <= Fr_AbsTimerIdx)                                                             
      {
        /* Report Error to DET */
        (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID,
                                            FR_59_RENESAS_GETABSOLUTETIMERIRQSTATUS_SID, FR_59_RENESAS_E_INV_TIMER_IDX);
        /* Default error is detected */
        LblErrDetect = FR_59_RENESAS_TRUE;
      } /* else No Action required */
    } /* else No Action required */
    /* Check if the output parameter Fr_IRQStatusPtr is NULL pointer */
    if (NULL_PTR == Fr_IRQStatusPtr)
    {
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID,
                                         FR_59_RENESAS_GETABSOLUTETIMERIRQSTATUS_SID, FR_59_RENESAS_E_PARAM_POINTER);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    } /* else No Action required */
  }
  /* Check if any DET error has occurred */
  if (FR_59_RENESAS_FALSE == LblErrDetect)
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  {
    Fr_59_Renesas_GetIrqSts(Fr_CtrlIdx, Fr_AbsTimerIdx, Fr_IRQStatusPtr);
  }
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  else
  {
    LucReturnValue = E_NOT_OK;
  }
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  /* Return the value */
  return (LucReturnValue);
} /* End of API Fr_59_Renesas_GetAbsoluteTimerIRQStatus */
#define FR_59_RENESAS_STOP_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_ReadCCConfig
**
** Service ID            : 0x2e
**
** Description           : This service reads a FlexRay protocol configuration
**                         parameter for a particular FlexRay controller out of
**                         the module's configuration.
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx, Fr_ConfigParamIdx
**
** InOut Parameters      : None
**
** Output Parameters     : Fr_ConfigParamValuePtr
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : The FlexRay Driver module should be initialized
**
** Global Variables Used : Fr_59_Renesas_GaaGlobalAccPoint
**                         Fr_59_Renesas_GaaGetCoreId2Index
**                         Fr_59_Renesas_GaaGetController2CoreIndex
**
** Functions Invoked     : Det_ReportError, Fr_59_Renesas_UpdateCCConfig
**
** Registers Used        : None
**
** Reference ID          : FR_DUD_ACT_031, FR_DUD_ACT_031_ERR001,
** Reference ID          : FR_DUD_ACT_031_ERR002, FR_DUD_ACT_031_ERR003,
** Reference ID          : FR_DUD_ACT_031_ERR004, FR_DUD_ACT_031_ERR005
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PUBLIC_CODE)
Fr_59_Renesas_ReadCCConfig(uint8 Fr_CtrlIdx, uint8 Fr_ConfigParamIdx, uint32 *Fr_ConfigParamValuePtr)                   /* PRQA S 1503 # JV-01 */
{
  /* Declare the variable to store the return value */
  Std_ReturnType LucReturnValue;
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  /* Declare the variable to store the DET return value */
  boolean LblErrDetect;
  /* Declare the variable to store the core index */
  uint8 LucCoreIndex;
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  uint8 ucCoreId;
  /* Get Core id for code branching */
  ucCoreId = (uint8)GetCoreID();
  /* Covert Core Id to Core Index */
  LucCoreIndex = Fr_59_Renesas_GaaGetCoreId2Index[ucCoreId];                                                            
  #else
  /* if Multicore is not configure, default coreid is 0x00
    To optimize implementation */
  LucCoreIndex = FR_59_RENESAS_ZERO;
  #endif
  /* Initialize development detection flag */
  LblErrDetect = FR_59_RENESAS_FALSE;
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  /* Initialize the return value */
  LucReturnValue = E_OK;                                                                                                /* PRQA S 2982 # JV-01 */
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  /* Check invalid core for calling API */
  if (FR_59_RENESAS_INVALID_CORE == LucCoreIndex)
  {
    /* Report to DET */
    (void)Det_ReportError(FR_59_RENESAS_MODULE_ID,FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_READCCCONFIG_SID,
                                                                                        FR_59_RENESAS_E_INVALID_CORE);
    /* Default error is detected */
    LblErrDetect = FR_59_RENESAS_TRUE;
  }
  else
  #endif
  {
    /* Check if the module is initialized */
    if (FR_59_RENESAS_FALSE == *(Fr_59_Renesas_GaaGlobalAccPoint[LucCoreIndex].pInitDone))                              
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_READCCCONFIG_SID,
                                                                                         FR_59_RENESAS_E_INIT_FAILED);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    } /* else No Action required */
    /* Check if the controller index is greater than the number of controller configured */
    if (FR_59_RENESAS_NUM_CTRL_SUPPORTED <= Fr_CtrlIdx)
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_READCCCONFIG_SID,
                                                                                      FR_59_RENESAS_E_INV_CTRL_IDX);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    }
    else
    {
      #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
      /* Check invalid core for calling API */
      if (LucCoreIndex != Fr_59_Renesas_GaaGetController2CoreIndex[Fr_CtrlIdx])
      {
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_READCCCONFIG_SID,
                                                                                         FR_59_RENESAS_E_INVALID_CORE);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
      }
      #endif
    }
    /* Check if the Configuration parameter index is greater than the last parameter */
    if (FR_CIDX_PTWOKEYSLOTMODE < Fr_ConfigParamIdx)
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_READCCCONFIG_SID,
                                                                                     FR_59_RENESAS_E_INV_CONFIG_IDX);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    } /* else No Action required */
    /* Check if the output parameter Fr_ConfigParamValuePtr is NULL pointer */
    if (NULL_PTR == Fr_ConfigParamValuePtr)
    {
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_READCCCONFIG_SID,
                                                                                       FR_59_RENESAS_E_PARAM_POINTER);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    } /* else No Action required */
  }
  /* Check if any DET error has occurred */
  if (FR_59_RENESAS_FALSE == LblErrDetect)
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  {
    LucReturnValue = Fr_59_Renesas_UpdateCCConfig(Fr_CtrlIdx, Fr_ConfigParamIdx, Fr_ConfigParamValuePtr);
  }
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  else
  {
    LucReturnValue = E_NOT_OK;
  }
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  /* Return the value */
  return (LucReturnValue);
} /* End of API Fr_59_Renesas_ReadCCConfig */
/* Variable to store the module initialization status */
#define FR_59_RENESAS_STOP_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_GetVersionInfo
**
** Service ID            : 0x1b
**
** Description           : This service returns the version information of this
**                         module.
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Re-entrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : VersioninfoPtr
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variables Used : None
**
** Function(s) invoked   : Det_ReportError
**
** Registers Used        : None
**
** Reference ID          : FR_DUD_ACT_032, FR_DUD_ACT_032_ERR001
***********************************************************************************************************************/
#if (FR_59_RENESAS_VERSION_INFO_API == STD_ON)
#define FR_59_RENESAS_START_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(void, FR_PUBLIC_CODE) Fr_59_Renesas_GetVersionInfo(Std_VersionInfoType *VersioninfoPtr)                            /* PRQA S 1503 # JV-01 */
{
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  /* Report to DET, if VersioninfoPtr pointer is equal to Null */
  if (NULL_PTR == VersioninfoPtr)
  {
    /* Report to DET */
    (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_GETVERSIONINFO_SID,
                                                                                        FR_59_RENESAS_E_PARAM_POINTER);
  }
  else
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Copy the vendor Id */
    VersioninfoPtr->vendorID = (uint16)FR_59_RENESAS_VENDOR_ID;                                                         
    /* Copy the module Id */
    VersioninfoPtr->moduleID = (uint16)FR_59_RENESAS_MODULE_ID;
    /* Copy Software Major Version */
    VersioninfoPtr->sw_major_version = FR_59_RENESAS_SW_MAJOR_VERSION;
    /* Copy Software Minor Version */
    VersioninfoPtr->sw_minor_version = FR_59_RENESAS_SW_MINOR_VERSION;
    /* Copy Software Patch Version */
    VersioninfoPtr->sw_patch_version = FR_59_RENESAS_SW_PATCH_VERSION_VALUE;
  }
} /* End of API Fr_59_Renesas_GetVersionInfo */
#define FR_59_RENESAS_STOP_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
#endif /*(FR_59_RENESAS_VERSION_INFO_API == STD_ON)*/

/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_TransferHandlerInit
**
** Service ID            : 0xA0
**
** Description           : This service Activates the input/output transfer
**                         function and initialize output pointer table
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx, Fr_OutputTableContentPtr, Fr_FIFOTableContentPtr
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : None
**
** Global Variables Used : Fr_59_Renesas_GaaGlobalAccPoint
**                         Fr_59_Renesas_GaaGetCoreId2Index
**                         Fr_59_Renesas_GaaGetController2CoreIndex
**
** Functions Invoked     : Det_ReportError,
**                         Fr_59_Renesas_ResumeInputQueueTransfer,
**                         Fr_59_Renesas_DataAvailable
**
** Registers Used        : None
**
** Reference ID          : FR_DUD_ACT_033, FR_DUD_ACT_033_ERR001,
** Reference ID          : FR_DUD_ACT_033_ERR002, FR_DUD_ACT_033_ERR003, FR_DUD_ACT_033_ERR004,
** Reference ID          : FR_DUD_ACT_033_ERR005, FR_DUD_ACT_033_GBL001, FR_DUD_ACT_033_GBL002
***********************************************************************************************************************/
#if ((FR_59_RENESAS_ENABLE_INPUT_TX_HANDLER == STD_ON) || (FR_59_RENESAS_ENABLE_OUTPUT_RX_HANDLER == STD_ON) || \
                                                               (FR_59_RENESAS_ENABLE_OUTPUT_RX_FIFO_HANDLER == STD_ON))
#define FR_59_RENESAS_START_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PUBLIC_CODE)
Fr_59_Renesas_TransferHandlerInit(uint8 Fr_CtrlIdx,                                                                     /* PRQA S 1503 # JV-01 */
                                  volatile Fr_59_Renesas_OutputPointerTableType *Fr_OutputTableContentPtr,
                                                 volatile Fr_59_Renesas_OutputPointerTableType *Fr_FIFOTableContentPtr)
{
  /* Declare the variable to store the return value */
  Std_ReturnType LucReturnValue;
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  /* Declare the variable to store the DET return value */
  boolean LblErrDetect;
  /* Declare the variable to store the core index */
  uint8 LucCoreIndex;
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  uint8 ucCoreId;
  /* Get Core id for code branching */
  ucCoreId = (uint8)GetCoreID();
  /* Covert Core Id to Core Index */
  LucCoreIndex = Fr_59_Renesas_GaaGetCoreId2Index[ucCoreId];                                                            
  #else
  /* if Multicore is not configure, default coreid is 0x00
    To optimize implementation */
  LucCoreIndex = FR_59_RENESAS_ZERO;
  #endif
  /* Initialize development detection flag */
  LblErrDetect = FR_59_RENESAS_FALSE;
  #endif
  /* Initialize the return value */
  LucReturnValue = E_OK;                                                                                                /* PRQA S 2982 # JV-01 */
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  /* Check invalid core for calling API */
  if (FR_59_RENESAS_INVALID_CORE == LucCoreIndex)
  {
    /* Report to DET */
    (void)Det_ReportError(FR_59_RENESAS_MODULE_ID,FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_TRANSFERHANDLERINIT_SID,
                                                                                        FR_59_RENESAS_E_INVALID_CORE);
    /* Default error is detected */
    LblErrDetect = FR_59_RENESAS_TRUE;
  }
  else
  #endif
  {
    /* Check if the module is initialized */
    if (FR_59_RENESAS_FALSE == *(Fr_59_Renesas_GaaGlobalAccPoint[LucCoreIndex].pInitDone))                              
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_TRANSFERHANDLERINIT_SID,
                                                                                        FR_59_RENESAS_E_INIT_FAILED);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    } /* else No Action required */
    /* Check the validity of the parameter Fr_CtrlIdx */
    if (FR_59_RENESAS_NUM_CTRL_SUPPORTED <= Fr_CtrlIdx)
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_TRANSFERHANDLERINIT_SID,
                                                                                       FR_59_RENESAS_E_INV_CTRL_IDX);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    }
    else
    {
      #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
      /* Check invalid core for calling API */
      if (LucCoreIndex != Fr_59_Renesas_GaaGetController2CoreIndex[Fr_CtrlIdx])
      {
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_TRANSFERHANDLERINIT_SID,
                                                                                        FR_59_RENESAS_E_INVALID_CORE);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
      }
      #endif
    }
    #if (FR_59_RENESAS_ENABLE_OUTPUT_RX_HANDLER == STD_ON)
    /* Check if Fr_OutputTableContentPtr is a NULL pointer or the input pointer and value is invalid */
    if ((NULL_PTR == Fr_OutputTableContentPtr) || ((NULL_PTR == Fr_OutputTableContentPtr
             ->Fr_59_Renesas_pOutputDataPtr) || (FR_59_RENESAS_MAX_MB_NUMBER < Fr_OutputTableContentPtr->ucMsgBuffer)))
    {
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_TRANSFERHANDLERINIT_SID,
                                                                                      FR_59_RENESAS_E_PARAM_POINTER);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    } /* else No Action required */
    #endif /* #if ((FR_59_RENESAS_ENABLE_OUTPUT_RX_HANDLER == STD_ON) */
    #if (FR_59_RENESAS_ENABLE_OUTPUT_RX_FIFO_HANDLER == STD_ON)
    /* Check if Fr_FIFOTableContentPtr is a NULL pointer or the input pointer and value is invalid */
    if ((NULL_PTR == Fr_FIFOTableContentPtr) || ((NULL_PTR == Fr_FIFOTableContentPtr->Fr_59_Renesas_pOutputDataPtr) ||
                                                (FR_59_RENESAS_MAX_MB_NUMBER < Fr_FIFOTableContentPtr->ucMsgBuffer)))
    {
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_TRANSFERHANDLERINIT_SID,
                                                                                      FR_59_RENESAS_E_PARAM_POINTER);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    } /* else No Action required */
    #endif /* #if (FR_59_RENESAS_ENABLE_OUTPUT_RX_FIFO_HANDLER == STD_ON) */
  }
  /* Check if any DET error has occurred */
  if (FR_59_RENESAS_FALSE == LblErrDetect)
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Input transfer */
    #if (FR_59_RENESAS_ENABLE_INPUT_TX_HANDLER == STD_ON)
    LucReturnValue = Fr_59_Renesas_ResumeInputQueueTransfer(Fr_CtrlIdx);
    /* End of input transfer */
    #endif
    /* Output transfer */
    #if ((FR_59_RENESAS_ENABLE_OUTPUT_RX_HANDLER == STD_ON) || (FR_59_RENESAS_ENABLE_OUTPUT_RX_FIFO_HANDLER == STD_ON))
    if (E_OK == LucReturnValue)
    {
      /* Update to New Data register */
      LucReturnValue = Fr_59_Renesas_DataAvailable(Fr_CtrlIdx, Fr_OutputTableContentPtr, Fr_FIFOTableContentPtr);
      /*end of output transfer */
    } /* else No Action required */
    #endif /* #if ((FR_59_RENESAS_ENABLE_OUTPUT_RX_HANDLER == STD_ON) || \
                                                            (FR_59_RENESAS_ENABLE_OUTPUT_RX_FIFO_HANDLER == STD_ON)) */
    #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
    if (E_OK == LucReturnValue)
    {
      /* Set the init state of transfer handler to true */
      *(Fr_59_Renesas_GaaGlobalAccPoint[LucCoreIndex].pTransferHandlerInitDone) = FR_59_RENESAS_TRUE;
    }
    else
    {
      /* Set the init state of transfer hander to fasle as failed initialization */
      *(Fr_59_Renesas_GaaGlobalAccPoint[LucCoreIndex].pTransferHandlerInitDone) = FR_59_RENESAS_FALSE;
    }
    #endif
  }
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  else
  {
    LucReturnValue = E_NOT_OK;
  }
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  return (LucReturnValue);
} /* End of API Fr_59_Renesas_TransferHandlerInit */
#define FR_59_RENESAS_STOP_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
#endif

/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_TransferQueueTable
**
** Service ID            : 0xA1
**
** Description           : This service load the input pointer table pointer
**                         in Local/Global RAM
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_InputTableContentPtr, Fr_CtrlIdx
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : None
**
** Global Variables Used : Fr_59_Renesas_GaaGlobalAccPoint
**                         Fr_59_Renesas_GaaGetCoreId2Index
**                         Fr_59_Renesas_GaaGetController2CoreIndex
**
** Functions Invoked     : Det_ReportError, Fr_59_Renesas_UpdateInputPtrTable
**
** Registers Used        : None
**
** Reference ID          : FR_DUD_ACT_034, FR_DUD_ACT_034_ERR001,
** Reference ID          : FR_DUD_ACT_034_ERR002, FR_DUD_ACT_034_ERR003, FR_DUD_ACT_034_ERR004
***********************************************************************************************************************/
#if (FR_59_RENESAS_ENABLE_INPUT_TX_HANDLER == STD_ON)
#define FR_59_RENESAS_START_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PUBLIC_CODE) Fr_59_Renesas_TransferQueueTable(uint8 Fr_CtrlIdx,                                 /* PRQA S 1503 # JV-01 */
                                                 volatile Fr_59_Renesas_InputPointerTableType *Fr_InputTableContentPtr)
{
  /* Declare the variable to store the return value */
  Std_ReturnType LucReturnValue;
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  /* Declare the variable to store the DET return value */
  boolean LblErrDetect;
  /* Declare the variable to store the core index */
  uint8 LucCoreIndex;
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  uint8 ucCoreId;
  /* Get Core id for code branching */
  ucCoreId = (uint8)GetCoreID();
  /* Covert Core Id to Core Index */
  LucCoreIndex = Fr_59_Renesas_GaaGetCoreId2Index[ucCoreId];                                                            
  #else
  /* if Multicore is not configure, default coreid is 0x00
    To optimize implementation */
  LucCoreIndex = FR_59_RENESAS_ZERO;
  #endif
  /* Initialize development detection flag */
  LblErrDetect = FR_59_RENESAS_FALSE;
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  /* Initialize the return value */
  LucReturnValue = E_OK;                                                                                                /* PRQA S 2982 # JV-01 */
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  /* Check invalid core for calling API */
  if (FR_59_RENESAS_INVALID_CORE == LucCoreIndex)
  {
    /* Report to DET */
    (void)Det_ReportError(FR_59_RENESAS_MODULE_ID,FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_TRANSFERQUEUETABLE_SID,
                                                                                        FR_59_RENESAS_E_INVALID_CORE);
    /* Default error is detected */
    LblErrDetect = FR_59_RENESAS_TRUE;
  }
  else
  #endif
  {
    /* Check if the module and transfer handler are initialized */
    if ((FR_59_RENESAS_FALSE == *(Fr_59_Renesas_GaaGlobalAccPoint[LucCoreIndex].pInitDone)) ||                          
        (FR_59_RENESAS_FALSE == *(Fr_59_Renesas_GaaGlobalAccPoint[LucCoreIndex].pTransferHandlerInitDone)))
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_TRANSFERQUEUETABLE_SID,
                                                                                        FR_59_RENESAS_E_INIT_FAILED);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    } /* else No Action required */
    /* Check the validity of the parameter Fr_CtrlIdx */
    if (FR_59_RENESAS_NUM_CTRL_SUPPORTED <= Fr_CtrlIdx)
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_TRANSFERQUEUETABLE_SID,
                                                                                      FR_59_RENESAS_E_INV_CTRL_IDX);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    }
    else
    {
      #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
      /* Check invalid core for calling API */
      if (LucCoreIndex != Fr_59_Renesas_GaaGetController2CoreIndex[Fr_CtrlIdx])
      {
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_TRANSFERQUEUETABLE_SID,
                                                                                        FR_59_RENESAS_E_INVALID_CORE);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
      }
      #endif
    }
    /* Check if Fr_InputTableContentPtr is a NULL pointer or Fr_59_Renesas_pInputDataPtr element is NULL_PTR */
    if ((NULL_PTR == Fr_InputTableContentPtr) || (NULL_PTR == Fr_InputTableContentPtr->Fr_59_Renesas_pInputDataPtr))
    {
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_TRANSFERQUEUETABLE_SID,
                                                                                       FR_59_RENESAS_E_PARAM_POINTER);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    } /* else No Action required */
  }
  /* Check if any DET error has occurred */
  if (FR_59_RENESAS_FALSE == LblErrDetect)
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  {
    LucReturnValue = Fr_59_Renesas_UpdateInputPtrTable(Fr_CtrlIdx, Fr_InputTableContentPtr);
  }
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  else
  {
    LucReturnValue = E_NOT_OK;
  }
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  return (LucReturnValue);
} /* End of API Fr_59_Renesas_TransferQueueTable */
#define FR_59_RENESAS_STOP_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
#endif

/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_ReceiveQueueTable
**
** Service ID            : 0xA2
**
** Description           : This service clears the bit of message buffer
**                         appropriate to the received frames from local RAM/
**                         Cluster RAM
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_OutputTableContentPtr, Fr_CtrlIdx
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : None
**
** Global Variables Used : Fr_59_Renesas_GaaGlobalAccPoint
**                         Fr_59_Renesas_GaaGetCoreId2Index
**                         Fr_59_Renesas_GaaGetController2CoreIndex
**
** Functions Invoked     : Det_ReportError,
**                         Fr_59_Renesas_UpdateOutputPtrTable
**
** Registers Used        : None
**
** Reference ID          : FR_DUD_ACT_035, FR_DUD_ACT_035_ERR001,
** Reference ID          : FR_DUD_ACT_035_ERR002, FR_DUD_ACT_035_ERR003, FR_DUD_ACT_035_ERR004
***********************************************************************************************************************/
#if ((FR_59_RENESAS_ENABLE_OUTPUT_RX_HANDLER == STD_ON) || (FR_59_RENESAS_ENABLE_OUTPUT_RX_FIFO_HANDLER == STD_ON))
#define FR_59_RENESAS_START_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PUBLIC_CODE)
                              Fr_59_Renesas_ReceiveQueueTable(uint8 Fr_CtrlIdx,                                         /* PRQA S 1503 # JV-01 */
                                               volatile Fr_59_Renesas_OutputPointerTableType *Fr_OutputTableContentPtr) /* PRQA S 3673 # JV-01 */
{
  /* Declare the variable to store the return value */
  Std_ReturnType LucReturnValue;
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  /* Declare the variable to store the DET return value */
  boolean LblErrDetect;
  /* Declare the variable to store the core index */
  uint8 LucCoreIndex;
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  uint8 ucCoreId;
  /* Get Core id for code branching */
  ucCoreId = (uint8)GetCoreID();
  /* Covert Core Id to Core Index */
  LucCoreIndex = Fr_59_Renesas_GaaGetCoreId2Index[ucCoreId];                                                            
  #else
  /* if Multicore is not configure, default coreid is 0x00
    To optimize implementation */
  LucCoreIndex = FR_59_RENESAS_ZERO;
  #endif
  /* Initialize development detection flag */
  LblErrDetect = FR_59_RENESAS_FALSE;
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  /* Initialize the return value */
  LucReturnValue = E_OK;                                                                                                /* PRQA S 2982 # JV-01 */
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  /* Check invalid core for calling API */
  if (FR_59_RENESAS_INVALID_CORE == LucCoreIndex)
  {
    /* Report to DET */
    (void)Det_ReportError(FR_59_RENESAS_MODULE_ID,FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_RECEIVEQUEUETABLE_SID,
                                                                                        FR_59_RENESAS_E_INVALID_CORE);
    /* Default error is detected */
    LblErrDetect = FR_59_RENESAS_TRUE;
  }
  else
  #endif
  {
    /* Check if the module and trasnfer handler are initialized */
    if ((FR_59_RENESAS_FALSE == *(Fr_59_Renesas_GaaGlobalAccPoint[LucCoreIndex].pInitDone)) ||                          
        (FR_59_RENESAS_FALSE == *(Fr_59_Renesas_GaaGlobalAccPoint[LucCoreIndex].pTransferHandlerInitDone)))
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_RECEIVEQUEUETABLE_SID,
                                                                                        FR_59_RENESAS_E_INIT_FAILED);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    } /* else No Action required */
    /* Check the validity of the parameter Fr_CtrlIdx */
    if (FR_59_RENESAS_NUM_CTRL_SUPPORTED <= Fr_CtrlIdx)
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_RECEIVEQUEUETABLE_SID,
                                                                                       FR_59_RENESAS_E_INV_CTRL_IDX);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    }
    else
    {
      #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
      /* Check invalid core for calling API */
      if (LucCoreIndex != Fr_59_Renesas_GaaGetController2CoreIndex[Fr_CtrlIdx])
      {
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_RECEIVEQUEUETABLE_SID,
                                                                                        FR_59_RENESAS_E_INVALID_CORE);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
      }
      #endif
    }
    /* Check if Fr_OutputTableContentPtr is a NULL pointer or the input pointer and value is invalid */
    if ((NULL_PTR == Fr_OutputTableContentPtr) || ((NULL_PTR == Fr_OutputTableContentPtr
            ->Fr_59_Renesas_pOutputDataPtr) || (FR_59_RENESAS_MAX_MB_NUMBER < Fr_OutputTableContentPtr->ucMsgBuffer)))
    {
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_RECEIVEQUEUETABLE_SID,
                                                                                      FR_59_RENESAS_E_PARAM_POINTER);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    } /* else No Action required */
  }
  /* Check if any DET error has occurred */
  if (FR_59_RENESAS_FALSE == LblErrDetect)
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Update the Output table content */
    LucReturnValue = Fr_59_Renesas_UpdateOutputPtrTable(Fr_CtrlIdx, Fr_OutputTableContentPtr);
  }
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  else
  {
    /* Set Return Value as E_NOT_OK */
    LucReturnValue = E_NOT_OK;
  }
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  return (LucReturnValue);
} /* End of API Fr_59_Renesas_ReceiveQueueTable */
#define FR_59_RENESAS_STOP_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
#endif

/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_InputTransferDisable
**
** Service ID            : 0xA3
**
** Description           : This service disable the input transfer handler
**                         from Local/Global RAM to Message RAM
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : None
**
** Global Variables Used : Fr_59_Renesas_GaaGlobalAccPoint
**                         Fr_59_Renesas_GaaGetController2CoreIndex
**
** Functions Invoked     : Det_ReportError,
**                         Fr_59_Renesas_ResetInputTransfer
**
** Registers Used        : None
**
** Reference ID          : FR_DUD_ACT_036, FR_DUD_ACT_036_ERR001,
** Reference ID          : FR_DUD_ACT_036_ERR002, FR_DUD_ACT_036_ERR003
***********************************************************************************************************************/
#if (FR_59_RENESAS_ENABLE_INPUT_TX_HANDLER == STD_ON)
#define FR_59_RENESAS_START_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PUBLIC_CODE) Fr_59_Renesas_InputTransferDisable(uint8 Fr_CtrlIdx)                               /* PRQA S 1503 # JV-01 */
{
  Std_ReturnType LucReturnValue;
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  /* Declare the variable to store the DET return value */
  boolean LblErrDetect;
  /* Declare the variable to store the core index */
  uint8 LucCoreIndex;
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  uint8 ucCoreId;
  /* Get Core id for code branching */
  ucCoreId = (uint8)GetCoreID();
  /* Covert Core Id to Core Index */
  LucCoreIndex = Fr_59_Renesas_GaaGetCoreId2Index[ucCoreId];                                                            
  #else
  /* if Multicore is not configure, default coreid is 0x00
    To optimize implementation */
  LucCoreIndex = FR_59_RENESAS_ZERO;
  #endif
  /* Initialize development detection flag */
  LblErrDetect = FR_59_RENESAS_FALSE;
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  /* Initialize the return value */
  LucReturnValue = E_OK;                                                                                                /* PRQA S 2982 # JV-01 */
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  /* Check invalid core for calling API */
  if (FR_59_RENESAS_INVALID_CORE == LucCoreIndex)
  {
    /* Report to DET */
    (void)Det_ReportError(FR_59_RENESAS_MODULE_ID,FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_INPUTTRANSFERDISABLE_SID,
                                                                                        FR_59_RENESAS_E_INVALID_CORE);
    /* Default error is detected */
    LblErrDetect = FR_59_RENESAS_TRUE;
  }
  else
  #endif
  {
    /* Check if the module and transfer handler are initialized */
    if ((FR_59_RENESAS_FALSE == *(Fr_59_Renesas_GaaGlobalAccPoint[LucCoreIndex].pInitDone)) ||                          
        (FR_59_RENESAS_FALSE == *(Fr_59_Renesas_GaaGlobalAccPoint[LucCoreIndex].pTransferHandlerInitDone)))
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_INPUTTRANSFERDISABLE_SID,
                                                                                         FR_59_RENESAS_E_INIT_FAILED);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    } /* else No Action required */
    /* Check the validity of the parameter Fr_CtrlIdx */
    if (FR_59_RENESAS_NUM_CTRL_SUPPORTED <= Fr_CtrlIdx)
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_INPUTTRANSFERDISABLE_SID,
                                                                                       FR_59_RENESAS_E_INV_CTRL_IDX);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    }
    else
    {
      #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
      /* Check invalid core for calling API */
      if (LucCoreIndex != Fr_59_Renesas_GaaGetController2CoreIndex[Fr_CtrlIdx])
      {
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_INPUTTRANSFERDISABLE_SID,
                                                                                         FR_59_RENESAS_E_INVALID_CORE);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
      }
      #endif
    }
  }
  /* Check if any DET error has occurred */
  if (FR_59_RENESAS_FALSE == LblErrDetect)
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  {
    LucReturnValue = Fr_59_Renesas_ResetInputTransfer(Fr_CtrlIdx);
  }
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  else
  {
    /* Set Return Value as E_NOT_OK */
    LucReturnValue = E_NOT_OK;
  }
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  return (LucReturnValue);
} /* End of API Fr_59_Renesas_InputTransferDisable */
#define FR_59_RENESAS_STOP_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
#endif

/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_OutputTransferDisable
**
** Service ID            : 0xA4
**
** Description           : This service disable the output transfer handler
**                         from Message RAM to Local/Global RAM
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : None
**
** Global Variables Used : Fr_59_Renesas_GaaGlobalAccPoint
**                         Fr_59_Renesas_GaaGetCoreId2Index
**                         Fr_59_Renesas_GaaGetController2CoreIndex
**
** Functions Invoked     : Det_ReportError
**                         Fr_59_Renesas_ResetOutputTransfer
**
** Registers Used        : None
**
** Reference ID          : FR_DUD_ACT_037, FR_DUD_ACT_037_ERR001,
** Reference ID          : FR_DUD_ACT_037_ERR002, FR_DUD_ACT_037_ERR003
***********************************************************************************************************************/
#if ((FR_59_RENESAS_ENABLE_OUTPUT_RX_HANDLER == STD_ON) || (FR_59_RENESAS_ENABLE_OUTPUT_RX_FIFO_HANDLER == STD_ON))
#define FR_59_RENESAS_START_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PUBLIC_CODE) Fr_59_Renesas_OutputTransferDisable(uint8 Fr_CtrlIdx)                              /* PRQA S 1503 # JV-01 */
{
  Std_ReturnType LucReturnValue;
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  /* Declare the variable to store the DET return value */
  boolean LblErrDetect;
  /* Declare the variable to store the core index */
  uint8 LucCoreIndex;
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  uint8 ucCoreId;
  /* Get Core id for code branching */
  ucCoreId = (uint8)GetCoreID();
  /* Covert Core Id to Core Index */
  LucCoreIndex = Fr_59_Renesas_GaaGetCoreId2Index[ucCoreId];                                                            
  #else
  /* if Multicore is not configure, default coreid is 0x00
    To optimize implementation */
  LucCoreIndex = FR_59_RENESAS_ZERO;
  #endif
  /* Initialize development detection flag */
  LblErrDetect = FR_59_RENESAS_FALSE;
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  /* Initialize the return value */
  LucReturnValue = E_OK;                                                                                                /* PRQA S 2982 # JV-01 */
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  /* Check invalid core for calling API */
  if (FR_59_RENESAS_INVALID_CORE == LucCoreIndex)
  {
    /* Report to DET */
    (void)Det_ReportError(FR_59_RENESAS_MODULE_ID,FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_OUTPUTTRANSFERDISABLE_SID,
                                                                                        FR_59_RENESAS_E_INVALID_CORE);
    /* Default error is detected */
    LblErrDetect = FR_59_RENESAS_TRUE;
  }
  else
  #endif
  {
    /* Check if the module and transfer handler are initialized */
    if ((FR_59_RENESAS_FALSE == *(Fr_59_Renesas_GaaGlobalAccPoint[LucCoreIndex].pInitDone)) ||                          
        (FR_59_RENESAS_FALSE == *(Fr_59_Renesas_GaaGlobalAccPoint[LucCoreIndex].pTransferHandlerInitDone)))
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_OUTPUTTRANSFERDISABLE_SID,
                                                                                         FR_59_RENESAS_E_INIT_FAILED);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    } /* else No Action required */
    /* Check the validity of the parameter Fr_CtrlIdx */
    if (FR_59_RENESAS_NUM_CTRL_SUPPORTED <= Fr_CtrlIdx)
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_OUTPUTTRANSFERDISABLE_SID,
                                                                                       FR_59_RENESAS_E_INV_CTRL_IDX);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    }
    else
    {
      #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
      /* Check invalid core for calling API */
      if (LucCoreIndex != Fr_59_Renesas_GaaGetController2CoreIndex[Fr_CtrlIdx])
      {
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_OUTPUTTRANSFERDISABLE_SID,
                                                                                        FR_59_RENESAS_E_INVALID_CORE);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
      }
      #endif
    }
  }
  /* Check if any DET error has occurred */
  if (FR_59_RENESAS_FALSE == LblErrDetect)
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Read current value of FLX0FROTC register */
    LucReturnValue = Fr_59_Renesas_ResetOutputTransfer(Fr_CtrlIdx);
  }
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  else
  {
    /* Set Return Value as E_NOT_OK */
    LucReturnValue = E_NOT_OK;
  }
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  return (LucReturnValue);
} /* End of API Fr_59_Renesas_OutputTransferDisable */
#define FR_59_RENESAS_STOP_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
#endif
/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_UserInputTransferRequest
**
** Service ID            : 0xA5
**
** Description           : This service perform user requested input transfer
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx, Fr_InputTableContentPtr
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : None
**
** Global Variables Used : Fr_59_Renesas_GaaGlobalAccPoint
**                         Fr_59_Renesas_GaaGetCoreId2Index
**                         Fr_59_Renesas_GaaGetController2CoreIndex
**
** Functions Invoked     : Det_ReportError,
**                         Fr_59_Renesas_InputTransferRequest
**
** Registers Used        : None
**
** Reference ID          : FR_DUD_ACT_038, FR_DUD_ACT_038_ERR001,
** Reference ID          : FR_DUD_ACT_038_ERR002, FR_DUD_ACT_038_ERR003, FR_DUD_ACT_038_ERR004
***********************************************************************************************************************/
#if ((FR_59_RENESAS_ENABLE_INPUT_TX_HANDLER == STD_ON) && (FR_59_RENESAS_ENABLE_USER_REQUEST_INPUT_TRANSFER == STD_ON))
#define FR_59_RENESAS_START_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PUBLIC_CODE) Fr_59_Renesas_UserInputTransferRequest(uint8 Fr_CtrlIdx,                           /* PRQA S 1503 # JV-01 */
                                                 volatile Fr_59_Renesas_InputPointerTableType *Fr_InputTableContentPtr)
{
  Std_ReturnType LucReturnValue;
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  /* Declare the variable to store the DET return value */
  boolean LblErrDetect;
  /* Declare the variable to store the core index */
  uint8 LucCoreIndex;
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  uint8 ucCoreId;
  /* Get Core id for code branching */
  ucCoreId = (uint8)GetCoreID();
  /* Covert Core Id to Core Index */
  LucCoreIndex = Fr_59_Renesas_GaaGetCoreId2Index[ucCoreId];                                                            
  #else
  /* if Multicore is not configure, default coreid is 0x00
    To optimize implementation */
  LucCoreIndex = FR_59_RENESAS_ZERO;
  #endif
  /* Initialize development detection flag */
  LblErrDetect = FR_59_RENESAS_FALSE;
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  /* Initialize the return value */
  LucReturnValue = E_OK;                                                                                                /* PRQA S 2982 # JV-01 */
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  /* Check invalid core for calling API */
  if (FR_59_RENESAS_INVALID_CORE == LucCoreIndex)
  {
    /* Report to DET */
    (void)Det_ReportError(FR_59_RENESAS_MODULE_ID,FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_USERINPUTTRANSFERREQUEST_SID,
                                                                                        FR_59_RENESAS_E_INVALID_CORE);
    /* Default error is detected */
    LblErrDetect = FR_59_RENESAS_TRUE;
  }
  else
  #endif
  {
    /* Check if the module and transfer handler are initialized */
    if ((FR_59_RENESAS_FALSE == *(Fr_59_Renesas_GaaGlobalAccPoint[LucCoreIndex].pInitDone)) ||                          
        (FR_59_RENESAS_FALSE == *(Fr_59_Renesas_GaaGlobalAccPoint[LucCoreIndex].pTransferHandlerInitDone)))
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID,
                                             FR_59_RENESAS_USERINPUTTRANSFERREQUEST_SID, FR_59_RENESAS_E_INIT_FAILED);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    } /* else No Action required */
    /* Check the validity of the parameter Fr_CtrlIdx */
    if (FR_59_RENESAS_NUM_CTRL_SUPPORTED <= Fr_CtrlIdx)
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID,
                                            FR_59_RENESAS_USERINPUTTRANSFERREQUEST_SID, FR_59_RENESAS_E_INV_CTRL_IDX);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    }
    else
    {
      #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
      /* Check invalid core for calling API */
      if (LucCoreIndex != Fr_59_Renesas_GaaGetController2CoreIndex[Fr_CtrlIdx])
      {
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID,FR_59_RENESAS_INSTANCE_ID,
                                            FR_59_RENESAS_USERINPUTTRANSFERREQUEST_SID, FR_59_RENESAS_E_INVALID_CORE);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
      }
      #endif
    }
    /* Check if Fr_InputTableContentPtr is a NULL pointer or Fr_59_Renesas_pInputDataPtr element is NULL_PTR */
    if ((NULL_PTR == Fr_InputTableContentPtr) || (NULL_PTR == Fr_InputTableContentPtr->Fr_59_Renesas_pInputDataPtr))
    {
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID,
                                           FR_59_RENESAS_USERINPUTTRANSFERREQUEST_SID, FR_59_RENESAS_E_PARAM_POINTER);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    } /* else No Action required */
  }
  /* Check if any DET error has occurred */
  if (FR_59_RENESAS_FALSE == LblErrDetect)
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Update the Input pointer table index requested for input transfer */
    LucReturnValue = Fr_59_Renesas_InputTransferRequest(Fr_CtrlIdx, Fr_InputTableContentPtr);
  }
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  else
  {
    /* Set Return Value as E_NOT_OK */
    LucReturnValue = E_NOT_OK;
  }
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  return (LucReturnValue);
} /* End of API Fr_59_Renesas_UserInputTransferRequest */
#define FR_59_RENESAS_STOP_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
#endif

/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_UserOutputTransferRequest
**
** Service ID            : 0xA6
**
** Description           : This service perform user requested output transfer
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx, Fr_OutputTableContentPtr
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : None
**
** Global Variables Used : Fr_59_Renesas_GaaGlobalAccPoint
**                         Fr_59_Renesas_GaaGetCoreId2Index
**                         Fr_59_Renesas_GaaGetController2CoreIndex
**
** Functions Invoked     : Det_ReportError,
**                         Fr_59_Renesas_OutputTransferRequest
**
** Registers Used        : None
**
** Reference ID          : FR_DUD_ACT_039, FR_DUD_ACT_039_ERR001,
** Reference ID          : FR_DUD_ACT_039_ERR002, FR_DUD_ACT_039_ERR003, FR_DUD_ACT_039_ERR004
***********************************************************************************************************************/
#if ((FR_59_RENESAS_ENABLE_OUTPUT_RX_HANDLER == STD_ON) && \
                                                         (FR_59_RENESAS_ENABLE_USER_REQUEST_OUTPUT_TRANSFER == STD_ON))
#define FR_59_RENESAS_START_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PUBLIC_CODE) Fr_59_Renesas_UserOutputTransferRequest(uint8 Fr_CtrlIdx,                          /* PRQA S 1503 # JV-01 */
                                               volatile Fr_59_Renesas_OutputPointerTableType *Fr_OutputTableContentPtr)
{
  Std_ReturnType LucReturnValue;
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  /* Declare the variable to store the DET return value */
  boolean LblErrDetect;
  /* Declare the variable to store the core index */
  uint8 LucCoreIndex;
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  uint8 ucCoreId;
  /* Get Core id for code branching */
  ucCoreId = (uint8)GetCoreID();
  /* Covert Core Id to Core Index */
  LucCoreIndex = Fr_59_Renesas_GaaGetCoreId2Index[ucCoreId];                                                            
  #else
  /* if Multicore is not configure, default coreid is 0x00
    To optimize implementation */
  LucCoreIndex = FR_59_RENESAS_ZERO;
  #endif
  /* Initialize development detection flag */
  LblErrDetect = FR_59_RENESAS_FALSE;
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  /* Initialize the return value */
  LucReturnValue = E_OK;                                                                                                /* PRQA S 2982 # JV-01 */
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  /* Check invalid core for calling API */
  if (FR_59_RENESAS_INVALID_CORE == LucCoreIndex)
  {
    /* Report to DET */
    (void)Det_ReportError(FR_59_RENESAS_MODULE_ID,FR_59_RENESAS_INSTANCE_ID,
                                          FR_59_RENESAS_USEROUTPUTTRANSFERREQUEST_SID, FR_59_RENESAS_E_INVALID_CORE);
    /* Default error is detected */
    LblErrDetect = FR_59_RENESAS_TRUE;
  }
  else
  #endif
  {
    /* Check if the module and transfer handler initialized */
    if ((FR_59_RENESAS_FALSE == *(Fr_59_Renesas_GaaGlobalAccPoint[LucCoreIndex].pInitDone)) ||                          
        (FR_59_RENESAS_FALSE == *(Fr_59_Renesas_GaaGlobalAccPoint[LucCoreIndex].pTransferHandlerInitDone)))
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID,
                                          FR_59_RENESAS_USEROUTPUTTRANSFERREQUEST_SID, FR_59_RENESAS_E_INIT_FAILED);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    } /* else No Action required */
    /* Check the validity of the parameter Fr_CtrlIdx */
    if (FR_59_RENESAS_NUM_CTRL_SUPPORTED <= Fr_CtrlIdx)
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID,
                                           FR_59_RENESAS_USEROUTPUTTRANSFERREQUEST_SID, FR_59_RENESAS_E_INV_CTRL_IDX);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    }
    else
    {
      #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
      /* Check invalid core for calling API */
      if (LucCoreIndex != Fr_59_Renesas_GaaGetController2CoreIndex[Fr_CtrlIdx])
      {
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID,FR_59_RENESAS_INSTANCE_ID,
                                         FR_59_RENESAS_USEROUTPUTTRANSFERREQUEST_SID, FR_59_RENESAS_E_INVALID_CORE);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
      }
      #endif
    }
    /* Check if Fr_OutputTableContentPtr is a NULL pointer or the input pointer and value is invalid */
    if ((NULL_PTR == Fr_OutputTableContentPtr) || ((NULL_PTR == Fr_OutputTableContentPtr
            ->Fr_59_Renesas_pOutputDataPtr) || (FR_59_RENESAS_MAX_MB_NUMBER < Fr_OutputTableContentPtr->ucMsgBuffer)))
    {
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID,
                                         FR_59_RENESAS_USEROUTPUTTRANSFERREQUEST_SID, FR_59_RENESAS_E_PARAM_POINTER);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    } /* else No Action required */
  }
  /* Check if any DET error has occurred */
  if (FR_59_RENESAS_FALSE == LblErrDetect)
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  {
    LucReturnValue = Fr_59_Renesas_OutputTransferRequest(Fr_CtrlIdx, Fr_OutputTableContentPtr);
  }
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  else
  {
    /* Set Return Value as E_NOT_OK */
    LucReturnValue = E_NOT_OK;
  }
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  return (LucReturnValue);
} /* End of API Fr_59_Renesas_UserOutputTransferRequest */
#define FR_59_RENESAS_STOP_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
#endif

/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_HaltInputQueue
**
** Service ID            : 0xA7
**
** Description           : This service is used to halt input transfer handler
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_InputTableContentPtr, Fr_CtrlIdx
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : None
**
** Global Variables Used : Fr_59_Renesas_GaaGlobalAccPoint
**                         Fr_59_Renesas_GaaGetCoreId2Index
**                         Fr_59_Renesas_GaaGetController2CoreIndex
**
** Functions Invoked     : Det_ReportError,
**                         Fr_59_Renesas_HaltInputQueueProcess
**
** Registers Used        : None
**
** Reference ID          : FR_DUD_ACT_040, FR_DUD_ACT_040_ERR001,
** Reference ID          : FR_DUD_ACT_040_ERR002, FR_DUD_ACT_040_ERR003, FR_DUD_ACT_040_ERR004
***********************************************************************************************************************/
#if (FR_59_RENESAS_ENABLE_INPUT_TX_HANDLER == STD_ON)
#define FR_59_RENESAS_START_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PUBLIC_CODE)
  Fr_59_Renesas_HaltInputQueue(uint8 Fr_CtrlIdx, volatile Fr_59_Renesas_InputPointerTableType *Fr_InputTableContentPtr) /* PRQA S 1503, 3673 # JV-01, JV-01 */
{
  Std_ReturnType LucReturnValue;
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  /* Declare the variable to store the DET return value */
  boolean LblErrDetect;
  /* Declare the variable to store the core index */
  uint8 LucCoreIndex;
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  uint8 ucCoreId;
  /* Get Core id for code branching */
  ucCoreId = (uint8)GetCoreID();
  /* Covert Core Id to Core Index */
  LucCoreIndex = Fr_59_Renesas_GaaGetCoreId2Index[ucCoreId];                                                            
  #else
  /* if Multicore is not configure, default coreid is 0x00
    To optimize implementation */
  LucCoreIndex = FR_59_RENESAS_ZERO;
  #endif /* (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON) */
  /* Initialize development detection flag */
  LblErrDetect = FR_59_RENESAS_FALSE;
  #endif /* (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  /* Initialize the return value */
  LucReturnValue = E_OK;                                                                                                /* PRQA S 2982 # JV-01 */
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  /* Check invalid core for calling API */
  if (FR_59_RENESAS_INVALID_CORE == LucCoreIndex)
  {
    /* Report to DET */
    (void)Det_ReportError(FR_59_RENESAS_MODULE_ID,FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_HALTINPUTQUEUE_SID,
                                                                                        FR_59_RENESAS_E_INVALID_CORE);
    /* Default error is detected */
    LblErrDetect = FR_59_RENESAS_TRUE;
  }
  else
  #endif
  {
    /* Check if the module and transfer handler are initialized */
    if ((FR_59_RENESAS_FALSE == *(Fr_59_Renesas_GaaGlobalAccPoint[LucCoreIndex].pInitDone)) ||                          
        (FR_59_RENESAS_FALSE == *(Fr_59_Renesas_GaaGlobalAccPoint[LucCoreIndex].pTransferHandlerInitDone)))
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_HALTINPUTQUEUE_SID,
                                                                                         FR_59_RENESAS_E_INIT_FAILED);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    } /* else No Action required */
    /* Check the validity of the parameter Fr_CtrlIdx */
    if (FR_59_RENESAS_NUM_CTRL_SUPPORTED <= Fr_CtrlIdx)
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_HALTINPUTQUEUE_SID,
                                                                                       FR_59_RENESAS_E_INV_CTRL_IDX);
      /* Set Return Value as E_NOT_OK */
      LblErrDetect = FR_59_RENESAS_TRUE;
    }
    else
    {
      #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
      /* Check invalid core for calling API */
      if (LucCoreIndex != Fr_59_Renesas_GaaGetController2CoreIndex[Fr_CtrlIdx])
      {
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_HALTINPUTQUEUE_SID,
                                                                                        FR_59_RENESAS_E_INVALID_CORE);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
      }
      #endif
    }
    /* Check if Fr_InputTableContentPtr is a NULL pointer or Fr_59_Renesas_pInputDataPtr element is NULL_PTR */
    if ((NULL_PTR == Fr_InputTableContentPtr) || (NULL_PTR == Fr_InputTableContentPtr->Fr_59_Renesas_pInputDataPtr))
    {
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_HALTINPUTQUEUE_SID,
                                                                                      FR_59_RENESAS_E_PARAM_POINTER);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    } /* else No Action required */
  }
  /* Check if any DET error has occurred */
  if (FR_59_RENESAS_FALSE == LblErrDetect)
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Halt the input queue */
    LucReturnValue = Fr_59_Renesas_HaltInputQueueProcess(Fr_CtrlIdx, Fr_InputTableContentPtr);
  }
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  else
  {
    /* Set Return Value as E_NOT_OK */
    LucReturnValue = E_NOT_OK;
  }
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  return (LucReturnValue);
} /* End of API Fr_59_Renesas_HaltInputQueue */
#define FR_59_RENESAS_STOP_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
#endif
/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_SetCycleCounterFiltering
**
** Service ID            : 0xA8
**
** Description           : This service sets the cycle code and macrotick offset
**                         value at which the absolute timer interrupt occurs.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx, Fr_AbsTimerIdx, Fr_CycleCode, Fr_Offset
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : The POC state of Communication Controller should be
**                         in NORMAL ACTIVE STATE
**
** Global Variables Used : Fr_59_Renesas_GaaGlobalAccPoint,
**                         Fr_59_Renesas_GpControllerConfigPtr
**                         Fr_59_Renesas_GaaGetCoreId2Index
**                         Fr_59_Renesas_GaaGetController2CoreIndex
**
** Functions Invoked     : Det_ReportError,
**                         FR_59_RENESAS_DEM_REPORT_ERROR,
**                         Fr_59_Renesas_GetPOCStsFlag,
**                         Fr_59_Renesas_SetCycleOffset,
**                         Det_ReportRuntimeError (AR2211)
**
** Registers Used        : None
**
** Reference ID          : FR_DUD_ACT_041, FR_DUD_ACT_041_ERR001,
** Reference ID          : FR_DUD_ACT_041_ERR002, FR_DUD_ACT_041_ERR003,
** Reference ID          : FR_DUD_ACT_041_ERR004, FR_DUD_ACT_041_ERR005,
** Reference ID          : FR_DUD_ACT_041_ERR006, FR_DUD_ACT_041_ERR007,
** Reference ID          : FR_DUD_ACT_041_ERR008, FR_DUD_ACT_041_ERR009
***********************************************************************************************************************/
#if (FR_59_RENESAS_SET_CYCLE_COUNTER_FILTERING_API == STD_ON)
#define FR_59_RENESAS_START_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PUBLIC_CODE)
   Fr_59_Renesas_SetCycleCounterFiltering(uint8 Fr_CtrlIdx, uint8 Fr_AbsTimerIdx, uint8 Fr_CycleCode, uint16 Fr_Offset) /* PRQA S 1503 # JV-01 */
{
  /* Declare the variable to store the return value */
  Std_ReturnType LucReturnValue;
  uint32 LulData;
  #if ((FR_59_RENESAS_DEV_ERROR_DETECT != STD_ON) && (FR_59_RENESAS_AR_VERSION == FR_59_RENESAS_AR_422_VERSION))
  /* Declare local pointer to Dem Event Id */
  P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF, FR_CONFIG_DATA) LpDemEventId;
  #endif
  #if ((FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) || (FR_59_RENESAS_AR_VERSION == FR_59_RENESAS_AR_R22_11_VERSION))
  /* Declare the variable to store the DET return value */
  boolean LblErrDetect;
  #endif
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  /* Declare local pointer to Control Table */
  P2CONST(Fr_59_Renesas_CtrlTableType, TYPEDEF, FR_CONFIG_DATA) LpCtrlTable;
  /* Declare the variable to store the core index */
  uint8 LucCoreIndex;
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  uint8 ucCoreId;
  /* Get Core id for code branching */
  ucCoreId = (uint8)GetCoreID();
  /* Covert Core Id to Core Index */
  LucCoreIndex = Fr_59_Renesas_GaaGetCoreId2Index[ucCoreId];                                                            
  #else
  /* if Multicore is not configure, default coreid is 0x00
  To optimize implementation */
  LucCoreIndex = FR_59_RENESAS_ZERO;
  #endif /* (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON) */
  #endif /* (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  #if ((FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) || (FR_59_RENESAS_AR_VERSION == FR_59_RENESAS_AR_R22_11_VERSION))
  /* Initialize development detection flag */
  LblErrDetect = FR_59_RENESAS_FALSE;
  #endif /* (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  /* Initialize the return value */
  LucReturnValue = E_OK;                                                                                                /* PRQA S 2982 # JV-01 */
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
  /* Check invalid core for calling API */
    if (FR_59_RENESAS_INVALID_CORE == LucCoreIndex)
  {
    /* Report to DET */
    (void)Det_ReportError(FR_59_RENESAS_MODULE_ID,FR_59_RENESAS_INSTANCE_ID, FR_59_RENESAS_SETCYCLECOUNTERFILTERING_SID,
                                                                                        FR_59_RENESAS_E_INVALID_CORE);
  /* Default error is detected */
  LblErrDetect = FR_59_RENESAS_TRUE;
  }
  else
  #endif
  {
    /* Check if the module is initialized */
    if (FR_59_RENESAS_FALSE == *(Fr_59_Renesas_GaaGlobalAccPoint[LucCoreIndex].pInitDone))                              
    {
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID,
                                            FR_59_RENESAS_SETCYCLECOUNTERFILTERING_SID, FR_59_RENESAS_E_INIT_FAILED);
      LblErrDetect = FR_59_RENESAS_TRUE;
    } /* else No Action required */
    /* Check if the controller index is greater than the number of controller configured */
    if (FR_59_RENESAS_NUM_CTRL_SUPPORTED <= Fr_CtrlIdx)
    {
      /* Report Error to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID,
                                          FR_59_RENESAS_SETCYCLECOUNTERFILTERING_SID, FR_59_RENESAS_E_INV_CTRL_IDX);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    }
    else
    {
      #if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
      /* Check invalid core for calling API */
      if (LucCoreIndex != Fr_59_Renesas_GaaGetController2CoreIndex[Fr_CtrlIdx])
      {
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID,
                                            FR_59_RENESAS_SETCYCLECOUNTERFILTERING_SID, FR_59_RENESAS_E_INVALID_CORE);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
      }
      #endif
    }
    /* Check if any DET error has occurred */
    if (FR_59_RENESAS_FALSE == LblErrDetect)
    {
      /* Check if the input parameter Fr_Offset is greater than the maximum value of macroticks per cycle */
      LpCtrlTable = (P2CONST(Fr_59_Renesas_CtrlTableType, AUTOMATIC,
                                        FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pCtrlTable);

      if (Fr_Offset > (LpCtrlTable->usMaxMacroPerCycle))                                                                
      {
        /* Report to DET */
        (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID,
                                             FR_59_RENESAS_SETCYCLECOUNTERFILTERING_SID, FR_59_RENESAS_E_INV_OFFSET);
        /* Default error is detected */
        LblErrDetect = FR_59_RENESAS_TRUE;
      } /* else No Action required */
      /*
      * Check if the absolute timer configured is greater than the number
      * of absolute timers configured for this controller
      */
      if ((LpCtrlTable->ucAbsTimerCount) <= Fr_AbsTimerIdx)
      {
        /* Report Error to DET */
        (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID,
                                           FR_59_RENESAS_SETCYCLECOUNTERFILTERING_SID, FR_59_RENESAS_E_INV_TIMER_IDX);
        /* Default error is detected */
        LblErrDetect = FR_59_RENESAS_TRUE;
      } /* else No Action required */
    } /* else No Action required */
    /*
    * Check if the input parameter Fr_Cycle is greater than the maximum
    * number of cycles in the communication cycle
    */
    if (FR_59_RENESAS_MAX_CYCLE_CODE < Fr_CycleCode)
    {
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID,
                                         FR_59_RENESAS_SETCYCLECOUNTERFILTERING_SID, FR_59_RENESAS_E_INV_CYCLE_CODE);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    } /* else No Action required */
  }
  if (FR_59_RENESAS_FALSE == LblErrDetect)
  #endif /* #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Read the POC state by getting the value of the register FRCCSV */
    LulData = Fr_59_Renesas_GetPOCStsFlag(Fr_CtrlIdx);
    /* Check if the POC is not in READY State */
    if ((FR_59_RENESAS_NORMAL_ACTIVE_STATE != LulData) && (FR_59_RENESAS_NORMAL_PASSIVE_STATE != LulData))
    {
      #if ((FR_59_RENESAS_AR_VERSION == FR_59_RENESAS_AR_422_VERSION) && (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON))
      /* Report to DET */
      (void)Det_ReportError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID,
                                             FR_59_RENESAS_SETCYCLECOUNTERFILTERING_SID, FR_59_RENESAS_E_INV_POCSTATE);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
      #endif /* #if ((FR_59_RENESAS_AR_VERSION == FR_59_RENESAS_AR_422_VERSION) \
                                                                      &&\ (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON))*/
      #if (FR_59_RENESAS_AR_VERSION == FR_59_RENESAS_AR_R22_11_VERSION)
      /* Report to DET */
      (void)Det_ReportRuntimeError(FR_59_RENESAS_MODULE_ID, FR_59_RENESAS_INSTANCE_ID,
                                             FR_59_RENESAS_SETCYCLECOUNTERFILTERING_SID, FR_59_RENESAS_E_INV_POCSTATE);
      /* Default error is detected */
      LblErrDetect = FR_59_RENESAS_TRUE;
    #endif
    } /* else No Action required */
  } /* else No Action required */
  #if ((FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) || (FR_59_RENESAS_AR_VERSION == FR_59_RENESAS_AR_R22_11_VERSION))
  /* Check if any DET error has occurred */
  if (FR_59_RENESAS_FALSE == LblErrDetect)
  #endif
  {
    #if ((FR_59_RENESAS_DEV_ERROR_DETECT != STD_ON) && (FR_59_RENESAS_AR_VERSION == FR_59_RENESAS_AR_422_VERSION))
    /* Read the POC State by getting FLX0CCSV register value */
    LulData = Fr_59_Renesas_GetPOCStsFlag(Fr_CtrlIdx);
    /* Check if the CC is in normal active state */
    if ((FR_59_RENESAS_NORMAL_ACTIVE_STATE == LulData) || (FR_59_RENESAS_NORMAL_PASSIVE_STATE == LulData))
    #endif
    {
      /* Set the filter for cycle counter */
      LucReturnValue = Fr_59_Renesas_SetCycleOffset(Fr_CtrlIdx, Fr_AbsTimerIdx, Fr_CycleCode, Fr_Offset);
    }
    #if ((FR_59_RENESAS_DEV_ERROR_DETECT != STD_ON) && (FR_59_RENESAS_AR_VERSION == FR_59_RENESAS_AR_422_VERSION))
    else
    {

      /* Report Error to DEM */
      LpDemEventId = (P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF,
                                         FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pDemEventId);
      if (FR_59_RENESAS_DEM_NOT_CONFIGURED != LpDemEventId->usHardwareTestFailure)
      {
        FR_59_RENESAS_DEM_REPORT_ERROR(LpDemEventId->usHardwareTestFailure, DEM_EVENT_STATUS_FAILED);
      } /* else No Action required */
      /* Set Return Value as E_NOT_OK */
      LucReturnValue = E_NOT_OK;
    }
    #endif
  }
  #if ((FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) || (FR_59_RENESAS_AR_VERSION == FR_59_RENESAS_AR_R22_11_VERSION))
  else
  {
    LucReturnValue = E_NOT_OK;
  }
  #endif
  /* Return the value */
  return (LucReturnValue);
} /* End of API Fr_59_Renesas_SetCycleCounterFiltering */
#define FR_59_RENESAS_STOP_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
#endif /* (FR_59_RENESAS_SET_CYCLE_COUNTER_FILTERING_API == STD_ON) */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
