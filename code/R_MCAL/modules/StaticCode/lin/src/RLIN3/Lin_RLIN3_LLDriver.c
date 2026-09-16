/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Lin_RLIN3_LLDriver.c                                                                                */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Low-level Driver code of the LIN Driver Component.                                                                 */
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
 *                       Add new QAC message 3006, remove redundant message 1532, 2844, 2814, 2824, 4399
 *                       In Lin_HwInit, add Lin interrupt mux selection for slave channel
 * 2.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.1.2:  31/10/2024  : As part of QAC 9.5.0 support, following changes are made:
 *                       1. Update SW-VERSION to 2.1.2
 *                       2. Fix findings for QA-C 9.5.0
 *                       3. Remove redundant QAC message and correct header description
 * 2.0.1:  21/10/2023  : Update to improve for critical section, Lin_ErrorReport in Lin_HwSendHeaderInternal,
 *                       Lin_HwHandleWakeupRequest
 *                       Update to improve critical section in Lin_HwSlaveProcessData
 *                       Update header description to fix TA finding:
 *                       Lin_HwErrorProcessing, Lin_HwInit, Lin_HwSetMasterMode, Lin_SetStatus:
 *                       Update "Input Parameters" to correct for input parameter
 *                       Lin_HwSlaveStartHeaderReception: Update "Functions invoked" to correct for invoked function
 *         11/10/2023  : Update AR version "LIN_AR_R21_11_VERSION" to "LIN_AR_R22_11_VERSION"
 *                       Update "LIN_INTERRUPT_CONTROL_PROTECTION_GLOBAL" to "LIN_INTERRUPT_CONTROL_PROTECTION".
 *                       Modify pointer casting type to fix QA-C messages
 * 2.0.0:  23/08/2023  : Update critical section in functions: Lin_HwSendHeaderInternal, Lin_HwWakeupOnGoing,
 *                       Lin_HwHandleWakeupRequest
 *                       Remove unused argument "LucApiId" in function Lin_HwSetMasterMode
 *                       Correct for report DEM, DET error in function Lin_HwWakeupOnGoing
 *         26/07/2023  : Add information about CWE violation ID
 *         24/07/2023  : Add QAC messages (2:2824)
 *                       Update to support for Multicore:
 *                       Update function Lin_TxIsr, Lin_RxIsr, Lin_ErrIsr, Lin_HwSendHeaderInternal, 
 *                       Lin_HwWakeUpFromBus, Lin_HwProcessData, Lin_HwErrorProcessing, Lin_HwLoadTxBuffer, 
 *                       Lin_HwWakeupOnGoing, Lin_HwSetMasterMode, Lin_HwScheduleInterrupt, 
 *                       Add new argument in function "Lin_HwInit", "Lin_SetStatus".
 *                       Update "LIN_INTERRUPT_CONTROL_PROTECTION_GLOBAL" for EIC.
 *                       Update critical section for function Lin_HwSlaveProcessData.
 *                       Update function Lin_HWInit to remove cricical section call in Init
 *                       Update function "Lin_ErrorReport" from static to extern function to correct Critical section
 *                       call in Lin_HWSetMasterMode.
 *         27/06/2023  : Change type of LulTimeoutCounter in Lin_HwSetMasterMode from uint32 to uint16
 *                       Add QAC message (2:1006), remove redundant QAC message (7:0791)
 *         21/06/2023  : In Lin_HwWakeupOnGoing:
 *                       Add Lin_HwSetMasterMode(RLIN3_OPERATION_MODE) to change LIN mode to operation mode
 *                       Add Lin_HwSlaveStartHeaderReception() only for a slave channel
 *                       Change the call of Lin_HwScheduleInterrupt(LIN_INTERRUPT_DIS) only for a master channel.
 *                       In Lin_HwInit, change setting for call Lin_HwScheduleInterrupt and remove redundant call of
 *                       Lin_HwSetMasterMode
 *         20/06/2023  : In Lin_HwSendHeaderInternal, change the setting value of "LpRamVars->enChannelStatus" from
 *                       'LIN_RX_BUSY' to 'LIN_TX_BUSY' when frame type is LIN_FRAMERESPONSE_RX/LIN_SLAVE_RESPONSE
 *                       In Lin_HwProcessData, change the transition of "LpRamVars->enChannelStatus" as
 *                       LIN_TX_BUSY -> LIN_RX_NO_RESPONSE -> LIN_RX_BUSY -> LIN_RX_OK when frame type is
 *                       LIN_FRAMERESPONSE_RX/LIN_SLAVE_RESPONSE.
 *                       In Function invoked of Lin_TxIsr, Lin_RxIsr, Lin_ErrIsr, Lin_HwErrorProcessing and
 *                       Lin_ErrorReport change Dem_SetEventStatus (for AR4.3.1) or Dem_ReportErrorStatus
 *                       (for AR4.2.2) to LIN_DEM_REPORT_ERROR
 *                       Add Std_ReturnType in Return parameter of Lin_HwSendHeaderInternal
 *                       Add LIN_ENTER_CRITICAL_SECTION, LIN_EXIT_CRITICAL_SECTION in Function Invoked of
 *                       Lin_HwProcessData, Lin_HwSlaveStartHeaderReception 
 *                       Remove LIN_ENTER_CRITICAL_SECTION, LIN_EXIT_CRITICAL_SECTION in Global Variable of
 *                       Lin_HwProcessData and Lin_HwSlaveProcessData
 *                       Remove LulIndex in Input Parameters of Lin_ErrorReport
 *                       Remove uint8 in Input Parameters of Lin_HwSlaveErrorProcessing
 *         25/05/2023  : Change name of AR version LIN_AR_2111_VERSION to LIN_AR_R21_11_VERSION
 *         22/05/2023  : Remove redundant QAC message
 *         08/05/2023  : Update reference ID for function Lin_HwErrorProcessing, Lin_HwInit
 *         06/05/2023  : Update Lin_HWInit to correct support for both mode Lin master and Lin slave
 *         28/04/2023  : Update QAC message 9.5.0 and remove message (7:2961)
 *                       Update to reduce STCYC <= 20 in function Lin_HwErrorProcessing
 *                       Update function Lin_HwSlaveProcessData to fix QAC message 9.5.0 (7:2961)
 *                       Add LpLin3ChannelPtr->ucBaudRate1 for LIN Baud Rate Prescaler 1 in function Lin_HwInit to
 *                       support baudrate in Slave mode
 *         20/04/2023  : Add Lin_HwScheduleInterrupt to Functions invoked in header of Lin_HwSlaveStartHeaderReception
 *                       Add Lin_HwSlaveProcessData to Functions invoked in header of Lin_TxIsr, Lin_RxIsr
 *                       Add Lin_HwSlaveErrorProcessing to Functions invoked in header of Lin_ErrIsr
 * 1.5.0:  09/04/2023  : Add QAC message 9.5.0 (7:2961).
 *         07/04/2023  : Add 3 new functions: Lin_HwSlaveErrorProcessing, Lin_HwSlaveProcessData,
 *                       Lin_HwSlaveStartHeaderReception
 *                       Add MACRO LIN_MASTER_MODE_SUPPORT, LIN_SLAVE_MODE_SUPPORT to Lin_TxIsr, Lin_RxIsr,
 *                       Lin_ErrIsr, Lin_HwProcessData, Lin_HwErrorProcessing, Lin_HwInit, Lin_HwSlaveProcessData,
 *                       Lin_HwSlaveErrorProcessing, Lin_HwSendHeaderInternal
 *                       Add conditons to Lin_TxIsr, Lin_RxIsr, Lin_ErrIsr, Lin_HwProcessData, Lin_HwErrorProcessing,
 *                       Lin_HwInit, to support slave mode (AR21-11)
 * 1.4.4:  24/06/2022  : Add QAC message 9.5.0.
 *         22/06/2022  : Modify the access size passed in RH850_SV_MODE_ICR_AND, when only MKn bits are updated. 
 * 1.4.3:  17/05/2022  : Update Lin_HwInit, add setting value for Interrupt Select register.
 *         10/05/2022  : Remove "else" statement don't use when no action required.
 *         20/04/2022  : Change from ucLin3IntMuxNumer to ucLin3IntMuxNumber
 *         14/04/2022  : Update SW-VERSION to 1.4.3
 * 1.4.2:  04/03/2022  : Fix QAC findings for QAC message 4399.
 * 1.4.1:  30/12/2021  : Update Lin_HwInit, add setting value for Interrupt Select register.
 *                       Add QAC message 9.5.0 (4:0312).
 * 1.4.0:  18/11/2021  : Update Critical section nesting for Lin_HwSendHeaderInternal and Lin_HwHandleWakeupRequest
 * 1.3.2:  25/08/2021  : Add condition to check interrupt disable or enable for Lin_HwSetMasterMode
 *                       Add clear error flag after changing mode for Lin_HwSetMasterMode 
 * 1.3.1:  02/07/2021  : Add QAC message 9.5.0.
 *                       Format source code to 120 characters.
 *                       Improve Violation tag (remove START/END).
 *         20/05/2021  : Fix QAC findings.
 * 1.2.0:  26/08/2020  : Release.
 * 1.1.0:  19/06/2020  : Release.
 * 1.0.2:  08/04/2020  : Update Lin_HWInit, add macros to set wakeup baud rate specifications.
 * 1.0.1:  25/03/2020  : Update Format dd/mm/yyyy and revision format.
 * 1.0.0:  30/03/2020  : Initial Version.
 *
 */
/**********************************************************************************************************************/

/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Lin APIs header file */
#include "Lin.h"

/* Included for extern declarations of global variables */
#include "Lin_Ram.h"

/* Lin Transmit receive header for the target */
#include "Lin_RLIN3_LLDriver.h"
#if (LIN_DEV_ERROR_DETECT == STD_ON)
/* Default Error header */
#include "Det.h"
#endif
/* Included for declaration of the function Dem_SetEventStatus() and Dem_ReportErrorStatus() */
#include "Dem.h"
#if (LIN_WAKEUP_SUPPORT == STD_ON)
#if (LIN_AR_VERSION == LIN_AR_R22_11_VERSION)
/* Included for the declaration of EcuM_CheckWakeup() */
/* EcuM Callback header file */
#include "EcuM.h"
#else
/* Included for the declaration of EcuM_CheckWakeup() */
/* EcuM Callback header file */
#include "EcuM_Cbk.h"
#endif
#endif
/* Schedule Manager header */
#if (LIN_CRITICAL_SECTION_PROTECTION == STD_ON)
#include "SchM_Lin.h"
#endif
/* Provision for platform dependent types */
#include "rh850_Types.h"

/* SWS_Lin_00235 */
#if (LIN_SLAVE_MODE_SUPPORT == STD_ON)
#include "LinIf.h"
#endif /* #if (LIN_SLAVE_MODE_SUPPORT == STD_ON) */

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR Release version information */
#define LIN_RLIN3_LLDRIVER_C_AR_RELEASE_MAJOR_VERSION    LIN_AR_RELEASE_MAJOR_VERSION_VALUE
#define LIN_RLIN3_LLDRIVER_C_AR_RELEASE_MINOR_VERSION    LIN_AR_RELEASE_MINOR_VERSION_VALUE
#define LIN_RLIN3_LLDRIVER_C_AR_RELEASE_REVISION_VERSION LIN_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define LIN_RLIN3_LLDRIVER_C_SW_MAJOR_VERSION            LIN_SW_MAJOR_VERSION_VALUE
#define LIN_RLIN3_LLDRIVER_C_SW_MINOR_VERSION            LIN_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (LIN_RLIN3_LLDRIVER_AR_RELEASE_MAJOR_VERSION != LIN_RLIN3_LLDRIVER_C_AR_RELEASE_MAJOR_VERSION)
#error "Lin_RLIN3_LLDriver.c : Mismatch in Release Major Version"
#endif

#if (LIN_RLIN3_LLDRIVER_AR_RELEASE_MINOR_VERSION != LIN_RLIN3_LLDRIVER_C_AR_RELEASE_MINOR_VERSION)
#error "Lin_RLIN3_LLDriver.c : Mismatch in Release Minor Version"
#endif

#if (LIN_RLIN3_LLDRIVER_AR_RELEASE_REVISION_VERSION != LIN_RLIN3_LLDRIVER_C_AR_RELEASE_REVISION_VERSION)
#error "Lin_RLIN3_LLDriver.c : Mismatch in Release Revision Version"
#endif

#if (LIN_RLIN3_LLDRIVER_SW_MAJOR_VERSION != LIN_RLIN3_LLDRIVER_C_SW_MAJOR_VERSION)
#error "Lin_RLIN3_LLDriver.c : Mismatch in Software Major Version"
#endif

#if (LIN_RLIN3_LLDRIVER_SW_MINOR_VERSION != LIN_RLIN3_LLDRIVER_C_SW_MINOR_VERSION)
#error "Lin_RLIN3_LLDriver.c : Mismatch in Software Minor Version"
#endif

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (4:5087)    : Use of #include directive after code fragment.                                               */
/* Rule                : MISRA C:2012 Rule-20.1                                                                       */
/* JV-01 Justification : This is done as per Memory Requirement, (MEMMAP003 - Specification of Memory Mapping).       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE Rule CWE-398, CWE-569                                            */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is accepted. */
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
/* Message (3:3387)    : A full expression containing an increment (++) or decrement (--) operator should have no     */
/*                       potential side effects other than that caused by the increment or decrement operator.        */
/* Rule                : MISRA C:2012 Rule-13.3                                                                       */
/* JV-01 Justification : An increment/decrement is created a side affect. In this case it's accessing a volatile      */
/*                       object. This can be accepted.                                                                */
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
/* Message (3:3206)    : The parameter '%s' is not used in this function.                                             */
/* Rule                : CERTCCM MSC07, MSC13, MISRA C:2012 Rule-2.7, CWE Rule CWE-398, CWE-563, CWE-569              */
/* JV-01 Justification : This is done as per implementation requirement.                                              */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1281)    : Integer literal constant is of an unsigned type but does not include a "U" suffix.           */
/* Rule                : MISRA C:2012 Rule-7.2, CWE Rule CWE-398, CWE-569                                             */
/* JV-01 Justification : Integer literal constant is of an unsigned type but does not include a "U" suffix.           */
/*       Verification  : Lack of using "U" is accepted since it cause no problem in software behavior.                */
/**********************************************************************************************************************/
/* Message (3:3416)    : Logical operation performed on expression with persistent side effects.                      */
/* Rule                : CERTCCM EXP45, CWE Rule CWE-398, CWE-569, CWE-737                                            */
/* JV-01 Justification : Logical operation accesses volatile object which is a register access. All register          */
/*                       addresses are generated with volatile qualifier. There is no impact on the functionality     */
/*                       due to this conditional check for mode change.                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3415)    : Right hand operand of '&&' or '||' is an expression with persistent side effects.            */
/* Rule                : CERTCCM EXP02, MISRA C:2012 Rule-13.5, CWE Rule CWE-398, CWE-768, CWE-569                    */
/* JV-01 Justification : Although it is a volatile object, it is not a direct access to the HW register, and there    */
/*                       is no side effect.                                                                           */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:3384)    : Cannot identify wraparound guard for dependent unsigned arithmetic expression.               */
/* Rule                : CERTCCM INT30                                                                                */
/* JV-01 Justification : LIN_ZERO is the lower constraint for the parameter.                                          */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0751)    : Casting to char pointer type.                                                                */
/* Rule                : CERTCCM EXP11, EXP39, CWE Rule CWE-188, CWE-398, CWE-468, CWE-588, CWE-465, CWE-569, CWE-737 */
/* JV-01 Justification : Using void due to specific requirement of input parameter. So, this can be skipped.          */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3464)    : Argument to macro '%s' contains a side effect that will be evaluated more than once.         */
/* Rule                : CERTCCM PRE31                                                                                */
/* JV-01 Justification : This message is only emitted for expressions expanded from argument tokens written out at    */
/*                       the top level, that did not themselves originate from a macro expansion.                     */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:4391)    : A composite expression of 'essentially unsigned' type (unsigned char) is being cast to a     */
/*                       wider unsigned type 'unsigned short'.                                                        */
/* Rule                : MISRA C:2012 Rule-10.8, CWE Rule CWE-136                                                     */
/* JV-01 Justification : This is necessary to support configuration. The actuall array can't be decided statically.   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:0312)    : Dangerous pointer cast results in loss of volatile qualification.                            */
/* Rule                : CERTCCM EXP32, MISRA C:2012 Rule-11.8, CWE Rule CWE-737                                      */
/* JV-01 Justification : According to the coding guide, all global variables must have volatile attribute, but        */
/*                       volatile must be removed when return these variables from APIs according to the AUTOSAR      */
/*                       specification.                                                                               */
/*       Verification  : Since these are normal memory objects, any problem doesn't occurs.                           */
/**********************************************************************************************************************/
/* Message (2:1006)    : [E] This in-line assembler construct is a language extension. The code has been ignored.     */
/* Rule                : MISRA-C:2012 Dir-1.1, Rule-1.2, Dir-4.2, CERTC 1.2.4 MSC14                                   */
/* JV-01 Justification : Inline assembler support for syncp instruction.                                              */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3006)    : This function contains a mixture of in-line assembler statements and C statements.           */
/* Rule                : MISRA C:2012 Dir-4.3                                                                         */
/* JV-01 Justification : This is accepted, due to the implementation is following hardware specification.             */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/
/***********************************************************************************************************************
**                                             Local Function Prototypes                                              **
***********************************************************************************************************************/
#define LIN_START_SEC_CODE_FAST
#include "Lin_MemMap.h"

#if (LIN_MASTER_MODE_SUPPORT == STD_ON)
STATIC FUNC(void, LIN_CODE_FAST) Lin_HwProcessData(const uint8 LucChannel);

STATIC FUNC(void, LIN_CODE_FAST) Lin_HwErrorProcessing(const uint8 LucChannel);
#endif /* #if (LIN_MASTER_MODE_SUPPORT == STD_ON) */

#if (LIN_SLAVE_MODE_SUPPORT == STD_ON)
STATIC FUNC(void, LIN_CODE_FAST) Lin_HwSlaveProcessData(const uint8 LucChannel);

STATIC FUNC(void, LIN_CODE_FAST) Lin_HwSlaveErrorProcessing(const uint8 LucChannel);
#endif /* #if (LIN_SLAVE_MODE_SUPPORT == STD_ON) */

#if (LIN_WAKEUP_SUPPORT == STD_ON)
STATIC FUNC(void, LIN_CODE_FAST) Lin_HwWakeUpFromBus(const uint8 LucChannel);
#endif

STATIC FUNC(void, LIN_CODE_FAST) Lin_HwWakeupOnGoing(const uint8 LucChannel);

#define LIN_STOP_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define LIN_START_SEC_PRIVATE_CODE
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

STATIC FUNC(void, LIN_PRIVATE_CODE) Lin_HwLoadTxBuffer(const uint8 LucChannel);

#define LIN_STOP_SEC_PRIVATE_CODE
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/

/***********************************************************************************************************************
** Function Name         : Lin_TxIsr
**
** Service ID            : None
**
** Description           : Interrupt Service Handler for transmission interrupt.
**
** Sync/Async            : Sync
**
** Reentrancy            : Non-Reentrant for same channel
**
** Input Parameters      : LucChannel : Number of LIN channel
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variable(s)    : Lin_GaaGlobalAccPoint,
**                         Lin_GaaChannelId2CoreIndex (LIN_MULTI_CORE_SUPPORT == STD_ON)
**
** Function(s) invoked   : LIN_DEM_REPORT_ERROR,
**                         Lin_HwWakeupOnGoing(when calling Lin_Wakeup),
**                         Lin_HwProcessData(when calling Lin_SendFrame with
**                         LIN_MASTER_RESPONSE or Lin_GoToSleep)
**                         Lin_HwSlaveProcessData
**
** Registers Used        : None
**
** Reference ID          : LIN_DUD_ACT_013,
** Reference ID          : LIN_DUD_ACT_013_ERR001,
** Reference ID          : LIN_DUD_ACT_013_ERR002
***********************************************************************************************************************/
#define LIN_START_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(void, LIN_CODE_FAST) Lin_TxIsr(const uint8 LucChannel)
{
  uint8 LucChannelRamIndex;
  uint8 LucCoreIndex;

  #if (LIN_MULTI_CORE_SUPPORT == STD_ON)
  /* LucChannel is channel id, need to convert to chanel index */
  LucCoreIndex = Lin_GaaChannelId2CoreIndex[LucChannel];
  /* Get Channel Ram Index for each core */
  LucChannelRamIndex = (*(Lin_GaaGlobalAccPoint[LucCoreIndex].pChannelConfig))[LucChannel].ucChannelRamIndex;
  #else
  LucCoreIndex = LIN_ZERO;
  /* single core - Channel Ram index = channel id */
  LucChannelRamIndex = LucChannel;
  #endif /* #if (LIN_MULTI_CORE_SUPPORT == STD_ON) */

#if (LIN_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Check if the EIMK bit of the EIC register is set */
  if (LIN_EIC_EIMK_MASK ==                                                                                              /* PRQA S 0404 # JV-01 */
      (uint16)((*((*(Lin_GaaGlobalAccPoint[LucCoreIndex].pRLIN3Properties))[LucChannel].pLin3IntTxEicReg))
      & (uint16)LIN_EIC_EIMK_MASK))
  {
    #ifdef LIN_E_INT_INCONSISTENT
    /* Reporting to DEM that interrupt from unknown source */
    LIN_DEM_REPORT_ERROR(LIN_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
    #endif /* #ifdef LIN_E_INT_INCONSISTENT */
  }
  else
#endif /* (LIN_INTERRUPT_CONSISTENCY_CHECK == STD_ON) */
  {
    if(LIN_TRUE == (Lin_GaaGlobalAccPoint[LucCoreIndex].pChannelRamData)[LucChannelRamIndex].blWakeupCalled)
    {
      Lin_HwWakeupOnGoing(LucChannel);
    }
    else
    {
      #if (LIN_SLAVE_MODE_SUPPORT == STD_ON)
      if (LIN_SLAVE_NODE == (*(Lin_GaaGlobalAccPoint[LucCoreIndex].pChannelConfig))[LucChannel].enNodeType)
      {
        /* Invoke Lin_HwSlaveProcessData to deal with the Tx Interrupt */
        Lin_HwSlaveProcessData(LucChannel);
      }
      else
      #endif /* (LIN_SLAVE_MODE_SUPPORT == STD_ON) */
      {
        #if (LIN_MASTER_MODE_SUPPORT == STD_ON)
        /* Invoke Lin_HwProcessData to deal with the Tx Interrupt */
        Lin_HwProcessData(LucChannel);
        #endif /* #if (LIN_MASTER_MODE_SUPPORT == STD_ON) */
      }
    }
  }
}
#define LIN_STOP_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Lin_RxIsr
**
** Service ID            : None
**
** Description           : Interrupt Service Handler for reception interrupt.
**
** Sync/Async            : Sync
**
** Reentrancy            : Non-Reentrant for same channel
**
** Input Parameters      : LucChannel : Number of LIN channel
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variable(s)    : Lin_GaaGlobalAccPoint
**                         Lin_GaaChannelId2CoreIndex (LIN_MULTI_CORE_SUPPORT == STD_ON)
**
** Function(s) invoked   : LIN_DEM_REPORT_ERROR,
**                         Lin_HwWakeUpFromBus(when detecting a wake-up pulse),
**                         Lin_HwProcessData(when calling Lin_SendFrame with
**                         LIN_SLAVE_RESPONSE)
**                         Lin_HwSlaveProcessData
**
** Registers Used        : None
**
** Reference ID          : LIN_DUD_ACT_014,
** Reference ID          : LIN_DUD_ACT_014_ERR001,
** Reference ID          : LIN_DUD_ACT_014_ERR002
***********************************************************************************************************************/
#define LIN_START_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(void, LIN_CODE_FAST) Lin_RxIsr(const uint8 LucChannel)
{
  #if ((LIN_INTERRUPT_CONSISTENCY_CHECK == STD_ON) || (LIN_WAKEUP_SUPPORT == STD_ON) || \
                                                                                     (LIN_SLAVE_MODE_SUPPORT == STD_ON))
  uint8 LucCoreIndex;
  #endif
  #if (LIN_WAKEUP_SUPPORT == STD_ON)
  uint8 LucChannelRamIndex;
  #endif /* #if (LIN_WAKEUP_SUPPORT == STD_ON) */

  #if ((LIN_INTERRUPT_CONSISTENCY_CHECK == STD_ON) || (LIN_WAKEUP_SUPPORT == STD_ON) || \
                                                                                     (LIN_SLAVE_MODE_SUPPORT == STD_ON))
  #if (LIN_MULTI_CORE_SUPPORT == STD_ON)
  /* LucChannel is channel id, need to convert to chanel index */
  LucCoreIndex = Lin_GaaChannelId2CoreIndex[LucChannel];
  #else
  LucCoreIndex = LIN_ZERO;
  #endif /* #if (LIN_MULTI_CORE_SUPPORT == STD_ON) */
  #endif

  #if (LIN_WAKEUP_SUPPORT == STD_ON)
  #if (LIN_MULTI_CORE_SUPPORT == STD_ON)
  /* Get Channel Ram Index for each core */
  LucChannelRamIndex = (*(Lin_GaaGlobalAccPoint[LucCoreIndex].pChannelConfig))[LucChannel].ucChannelRamIndex;
  #else
  LucChannelRamIndex = LucChannel;
  #endif /* #if (LIN_MULTI_CORE_SUPPORT == STD_ON) */
  #endif /* #if (LIN_WAKEUP_SUPPORT == STD_ON) */

#if (LIN_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Check if the EIMK bit of the EIC register is set */
  if (LIN_EIC_EIMK_MASK ==                                                                                              /* PRQA S 0404 # JV-01 */
      (uint16)((*((*(Lin_GaaGlobalAccPoint[LucCoreIndex].pRLIN3Properties))[LucChannel].pLin3IntRxEicReg))
      & (uint16)LIN_EIC_EIMK_MASK))
  {
    #ifdef LIN_E_INT_INCONSISTENT
    /* Reporting to DEM that interrupt from unknown source */
    LIN_DEM_REPORT_ERROR(LIN_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
    #endif /* #ifdef LIN_E_INT_INCONSISTENT */
  }
  else
#endif /* (LIN_INTERRUPT_CONSISTENCY_CHECK == STD_ON) */
  {
  /* Check if global wakeup support is enabled */
  #if (LIN_WAKEUP_SUPPORT == STD_ON)
    /* Check if channel status is sleep */
    if ((LIN_CH_SLEEP == (Lin_GaaGlobalAccPoint[LucCoreIndex].pChannelRamData)[LucChannelRamIndex].enChannelStatus) ||
       (LIN_TRUE == (Lin_GaaGlobalAccPoint[LucCoreIndex].pChannelRamData)[LucChannelRamIndex].blSleepPending))
    {
      /* Invoke Lin_HwWakeUpFromBus() */
      Lin_HwWakeUpFromBus(LucChannel);
    }
    else
  #endif
    {
      #if (LIN_SLAVE_MODE_SUPPORT == STD_ON)
      if (LIN_SLAVE_NODE == (*(Lin_GaaGlobalAccPoint[LucCoreIndex].pChannelConfig))[LucChannel].enNodeType)
      {
        /* Invoke Lin_HwSlaveProcessData to deal with the Rx Interrupt */
        Lin_HwSlaveProcessData(LucChannel);
      }
      else
      #endif /* (LIN_SLAVE_MODE_SUPPORT == STD_ON) */
      {
        #if (LIN_MASTER_MODE_SUPPORT == STD_ON)
        /* Invoke Lin_HwProcessData to deal with the Rx Interrupt */
        Lin_HwProcessData(LucChannel);
        #endif /* #if (LIN_MASTER_MODE_SUPPORT == STD_ON) */
      }
    }
  }
}
#define LIN_STOP_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Lin_ErrIsr
**
** Service ID            : None
**
** Description           : Interrupt Service Handler for error interrupt.
**
** Sync/Async            : Sync
**
** Reentrancy            : Non-Reentrant for same channel
**
** Input Parameters      : LucChannel : Number of LIN channel
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variable(s)    : Lin_GaaGlobalAccPoint,
**                         Lin_GaaChannelId2CoreIndex (LIN_MULTI_CORE_SUPPORT == STD_ON)
**
** Function(s) invoked   : LIN_DEM_REPORT_ERROR,
**                         Lin_HwErrorProcessing
**                         Lin_HwSlaveErrorProcessing
**
** Registers Used        : None
**
** Reference ID          : LIN_DUD_ACT_015,
** Reference ID          : LIN_DUD_ACT_015_ERR001,
** Reference ID          : LIN_DUD_ACT_015_ERR002
***********************************************************************************************************************/
#define LIN_START_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(void, LIN_CODE_FAST) Lin_ErrIsr(const uint8 LucChannel)
{
  #if ((LIN_INTERRUPT_CONSISTENCY_CHECK == STD_ON)||(LIN_SLAVE_MODE_SUPPORT == STD_ON))
  uint8 LucCoreIndex;
  #endif /* #if ((LIN_INTERRUPT_CONSISTENCY_CHECK == STD_ON)||(LIN_SLAVE_MODE_SUPPORT == STD_ON)) */

  #if ((LIN_INTERRUPT_CONSISTENCY_CHECK == STD_ON)||(LIN_SLAVE_MODE_SUPPORT == STD_ON))
  #if (LIN_MULTI_CORE_SUPPORT == STD_ON)
  /* LucChannel is channel id, need to convert to chanel index */
  LucCoreIndex = Lin_GaaChannelId2CoreIndex[LucChannel];
  #else
  LucCoreIndex = LIN_ZERO;
  #endif /* #if (LIN_MULTI_CORE_SUPPORT == STD_ON) */
  #endif /* #if ((LIN_INTERRUPT_CONSISTENCY_CHECK == STD_ON)||(LIN_SLAVE_MODE_SUPPORT == STD_ON)) */

#if (LIN_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Check if the EIMK bit of the EIC register is set */
  if (LIN_EIC_EIMK_MASK ==                                                                                              /* PRQA S 0404 # JV-01 */
      (uint16)((*((*(Lin_GaaGlobalAccPoint[LucCoreIndex].pRLIN3Properties))[LucChannel].pLin3IntStEicReg))
      & (uint16)LIN_EIC_EIMK_MASK))
  {
    #ifdef LIN_E_INT_INCONSISTENT
    /* Reporting to DEM that interrupt from unknown source */
    LIN_DEM_REPORT_ERROR(LIN_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
    #endif /* #ifdef LIN_E_INT_INCONSISTENT */
  }
  else
#endif /* (LIN_INTERRUPT_CONSISTENCY_CHECK == STD_ON) */
  {
    #if (LIN_SLAVE_MODE_SUPPORT == STD_ON)
    if (LIN_SLAVE_NODE == (*(Lin_GaaGlobalAccPoint[LucCoreIndex].pChannelConfig))[LucChannel].enNodeType)
    {
      /* Calling error processing API for error check */
      Lin_HwSlaveErrorProcessing(LucChannel);
    }
    else
    #endif /* (LIN_SLAVE_MODE_SUPPORT == STD_ON) */
    {
      #if (LIN_MASTER_MODE_SUPPORT == STD_ON)
      /* Calling error processing API for error check */
      Lin_HwErrorProcessing(LucChannel);
      #endif /* #if (LIN_MASTER_MODE_SUPPORT == STD_ON) */
    }
  }
}
#define LIN_STOP_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name      : Lin_HwSendHeaderInternal
**
** Service ID         : NA
**
** Description        : Internal Function to start frame transmission
**
** Sync/Async         : Synchronous
**
** Re-entrancy        : Non Re-entrant
**
** Input Parameters   : LucChannel, LpPduInfoPtr, LucApiId
**
** Output Parameters  : None
**
** Return parameter   : Std_ReturnType
**
** Preconditions      : None
**
** Global Variables   : Lin_GaaGlobalAccPoint,
**                      Lin_GaaChannelId2CoreIndex (LIN_MULTI_CORE_SUPPORT == STD_ON)
**
** Functions invoked  : Lin_HwLoadTxBuffer, Lin_HwSetMasterMode,
**                      Lin_HwScheduleInterrupt
**                      LIN_ENTER_CRITICAL_SECTION, LIN_EXIT_CRITICAL_SECTION,
**                      Lin_ErrorReport
**
** Registers Used     : ucRLN3nLIDB,
**                      ucRLN3nLDFC,
**                      ucRLN3nLTRC
**
** Reference ID       : LIN_DUD_ACT_016, LIN_DUD_ACT_016_GBL001, LIN_DUD_ACT_016_CRT003, LIN_DUD_ACT_016_CRT004,
** Reference ID       : LIN_DUD_ACT_016_GBL002, LIN_DUD_ACT_016_GBL003,
** Reference ID       : LIN_DUD_ACT_016_GBL004, LIN_DUD_ACT_016_GBL005,
** Reference ID       : LIN_DUD_ACT_016_GBL006, LIN_DUD_ACT_016_GBL007,
** Reference ID       : LIN_DUD_ACT_016_GBL008, LIN_DUD_ACT_016_REG001,
** Reference ID       : LIN_DUD_ACT_016_REG002, LIN_DUD_ACT_016_REG003,
** Reference ID       : LIN_DUD_ACT_016_REG004, LIN_DUD_ACT_016_REG005,
** Reference ID       : LIN_DUD_ACT_016_REG006, LIN_DUD_ACT_016_REG007,
** Reference ID       : LIN_DUD_ACT_016_CRT001, LIN_DUD_ACT_016_CRT002,
** Reference ID       : LIN_DUD_ACT_016_REG008, LIN_DUD_ACT_016_ERR001
***********************************************************************************************************************/
#if (LIN_MASTER_MODE_SUPPORT == STD_ON)
#define LIN_START_SEC_PRIVATE_CODE
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, LIN_PRIVATE_CODE)
Lin_HwSendHeaderInternal(const uint8 LucChannel, CONSTP2CONST(Lin_PduType, AUTOMATIC, LIN_PRIVATE_CONST) LpPduInfoPtr,
                         const uint8 LucApiId)
{
  uint8 LucChannelRamIndex;
  uint8 LucCoreIndex;

  volatile P2CONST(Lin3_ChannelConfigType, AUTOMATIC, LIN_PRIVATE_CONST) LpLin3ChannelPtr;
  volatile P2VAR(RLin3_UartRegs, AUTOMATIC, REGSPACE) LpLN3ChannelRegs;                                                 /* PRQA S 3432 # JV-01 */
  volatile P2VAR(Lin_RamData, AUTOMATIC, LIN_VAR_FAST_NO_INIT) LpRamVars;                                               /* PRQA S 3432 # JV-01 */
  Std_ReturnType LucReturnValue;

  Lin_FrameResponseType LenFrameType;


  #if (LIN_MULTI_CORE_SUPPORT == STD_ON)
  /* LucChannel is channel id, need to convert to chanel index */
  LucCoreIndex = Lin_GaaChannelId2CoreIndex[LucChannel];
  /* Get Channel Ram Index for each core */
  LucChannelRamIndex = (*(Lin_GaaGlobalAccPoint[LucCoreIndex].pChannelConfig))[LucChannel].ucChannelRamIndex;
  #else
  LucCoreIndex = LIN_ZERO;
  /* single core - Channel Ram index = channel id */
  LucChannelRamIndex = LucChannel;
  #endif /* #if (LIN_MULTI_CORE_SUPPORT == STD_ON) */

  /* Initialize the return value */
  LucReturnValue = E_NOT_OK;                                                                                            /* PRQA S 2982 # JV-01 */

  /* Get the pointer to channel RAM data */
  LpRamVars = &((Lin_GaaGlobalAccPoint[LucCoreIndex].pChannelRamData)[LucChannelRamIndex]);

  /* Copy the frame Id to frame data structure */
  LpRamVars->ucFrameId = LpPduInfoPtr->Pid;

  /* Copy the checksum model to frame data structure */
  LpRamVars->enCheckSumModel = LpPduInfoPtr->Cs;

  /* Copy the data length to frame data structure */
  LpRamVars->ucFrameLength = LpPduInfoPtr->Dl;

  /* Copy the frame type to frame data structure */
  LpRamVars->enFrameType = LpPduInfoPtr->Drc;

  LpLin3ChannelPtr = &((*(Lin_GaaGlobalAccPoint[LucCoreIndex].pRLIN3Properties))[LucChannel]);

  /* Get the RLIN3 Channel Base Address */
  LpLN3ChannelRegs = LpLin3ChannelPtr->pLn3ChanlBaseAddress;

  /* Get frame type */
  LenFrameType = LpRamVars->enFrameType;

  if (LIN_TRUE == LpRamVars->blWakeupCalled)
  {
    /* Reset the LinIf wake-up flag */
    LpRamVars->blWakeupCalled = LIN_FALSE;
  } /* else No action required */

  /* Enter the protection area */
  LIN_ENTER_CRITICAL_SECTION(LIN_INTERRUPT_CONTROL_PROTECTION);

  /* Set RLIN3 to Reset Mode */
  LucReturnValue = Lin_HwSetMasterMode(LucChannel, RLIN3_RESET_MODE);

  if (E_OK == LucReturnValue)
  {
    /* Set RLIN3 to Operation Mode */
    LucReturnValue = Lin_HwSetMasterMode(LucChannel, RLIN3_OPERATION_MODE);
  }

  /* Exit the protection area */
  LIN_EXIT_CRITICAL_SECTION(LIN_INTERRUPT_CONTROL_PROTECTION);

  if (E_OK == LucReturnValue)
  {
    /* Set the frame Id */
    LpLN3ChannelRegs->ucRLN3nLIDB = LpRamVars->ucFrameId;

    /* Reset of LIN data Field Configuration Register */
    LpLN3ChannelRegs->ucRLN3nLDFC = LIN_RESET_VALUE;

    /* If checksum model is of type CLASSIC */
    if (LIN_CLASSIC_CS == LpRamVars->enCheckSumModel)
    {
      /* Set the checksum model to CLASSIC */
      LpLN3ChannelRegs->ucRLN3nLDFC = (LpLN3ChannelRegs->ucRLN3nLDFC & LIN_SET_CLS_CHKSUM);
    }
    /* If checksum model is of type ENHANCED */
    else
    {
      /* Set the checksum model to ENHANCED */
      LpLN3ChannelRegs->ucRLN3nLDFC = (LpLN3ChannelRegs->ucRLN3nLDFC | LIN_SET_ENH_CHKSUM);
    }

    /* Set length of total bytes in a RLIN3 Frame(Response data + Checksum) */
    LpLN3ChannelRegs->ucRLN3nLDFC = (LpLN3ChannelRegs->ucRLN3nLDFC | LpPduInfoPtr->Dl);

    #if (LIN_AR_VERSION == LIN_AR_R22_11_VERSION)
    /* AR22-11 use LIN_FRAMERESPONSE_TX instead of LIN_MASTER_RESPONSE */
    if (LIN_FRAMERESPONSE_TX == LenFrameType)
    #else
    if (LIN_MASTER_RESPONSE == LenFrameType)
    #endif /* #if (LIN_AR_VERSION == LIN_AR_R22_11_VERSION) */
    {
      /* To Set the Transmit Data */
      /*Call the internal function to load Tx Buffer and start the frame
        transmission */
      Lin_HwLoadTxBuffer(LucChannel);

      /* Set Response direction for Transmit */
      LpLN3ChannelRegs->ucRLN3nLDFC = (LpLN3ChannelRegs->ucRLN3nLDFC | LIN_MASTER_DIRECTION);
    }
    else
    {
      /* Set Response direction for Receive */
      LpLN3ChannelRegs->ucRLN3nLDFC = (LpLN3ChannelRegs->ucRLN3nLDFC & LIN_SLAVE_DIRECTION);
    }

    /* Enter the protection area */
    LIN_ENTER_CRITICAL_SECTION(LIN_INTERRUPT_CONTROL_PROTECTION);

    /* Enable RLIN3 Interrupt */
    Lin_HwScheduleInterrupt(LucChannel, LIN_INTERRUPT_EN);

    /* Exit the protection area */
    LIN_EXIT_CRITICAL_SECTION(LIN_INTERRUPT_CONTROL_PROTECTION);
    #if (LIN_AR_VERSION == LIN_AR_R22_11_VERSION)
    switch (LenFrameType)
    {
    /* AR22-11 use LIN_FRAMERESPONSE_TX instead of LIN_MASTER_RESPONSE */
    case LIN_FRAMERESPONSE_TX:
      /* Check if the transmitted frame is for go-to-sleep command */
      if (LIN_SET_SLEEP_REQUEST == LpRamVars->ucSlpRqst_RespRdy)
      {
        /* No action required, keep LpRamVars->blSleepPending as LIN_TRUE */
      }
      else
      {
        /* Set the Channel Status */
        LpRamVars->enChannelStatus = LIN_TX_BUSY;
      }
      break;
    /* AR22-11 use LIN_FRAMERESPONSE_IGNORE instead of LIN_SLAVE_TO_SLAVE */
    case LIN_FRAMERESPONSE_IGNORE:
      /* Set the Channel Status */
      LpRamVars->enChannelStatus = LIN_TX_BUSY;
      break;
    /* AR22-11 use LIN_FRAMERESPONSE_RX instead of LIN_SLAVE_RESPONSE */
    case LIN_FRAMERESPONSE_RX:
      /* Set the Channel Status */
      LpRamVars->enChannelStatus = LIN_TX_BUSY;
      break;
    default:
      /* No action required */
      break;
    }
    #else
    switch (LenFrameType)
    {
    case LIN_MASTER_RESPONSE:
      /* Check if the transmitted frame is for go-to-sleep command */
      if (LIN_SET_SLEEP_REQUEST == LpRamVars->ucSlpRqst_RespRdy)
      {
        /* No action required, keep LpRamVars->blSleepPending as LIN_TRUE */
      }
      else
      {
        /* Set the Channel Status */
        LpRamVars->enChannelStatus = LIN_TX_BUSY;
      }
      break;
    case LIN_SLAVE_TO_SLAVE:
      /* Set the Channel Status */
      LpRamVars->enChannelStatus = LIN_TX_BUSY;
      break;
    case LIN_SLAVE_RESPONSE:
      /* Set the Channel Status */
      LpRamVars->enChannelStatus = LIN_TX_BUSY;
      break;
    default:
      /* No action required */
      break;
    }
    #endif /* #if (LIN_AR_VERSION == LIN_AR_R22_11_VERSION) */

    /* Initiate Transmission */
    LpLN3ChannelRegs->ucRLN3nLTRC = (LpLN3ChannelRegs->ucRLN3nLTRC | LIN_START_TRANSMIT);
  } /* End of if (E_OK == LucReturnValue) */
  else
  {
    #if defined(LIN_E_TIMEOUT) || (LIN_DEV_ERROR_DETECT == STD_ON)
    /* Report Error to DEM or DET */
    LucReturnValue = Lin_ErrorReport(LucApiId);
    #endif /* #if defined(LIN_E_TIMEOUT) || (LIN_DEV_ERROR_DETECT == STD_ON) */
  }
  return (LucReturnValue);
}
#define LIN_STOP_SEC_PRIVATE_CODE
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* #if (LIN_MASTER_MODE_SUPPORT ==STD_ON) */

/***********************************************************************************************************************
** Function Name      : Lin_HwWakeUpFromBus
**
** Service ID         : NA
**
** Description        : This service does wake-up (from the bus) processing
**
** Sync/Async         : Synchronous
**
** Re-entrancy        : Non Re-entrant for the same channel
**
** Input Parameters   : LucChannel
**
** Output Parameters  : None
**
** Return parameter   : None
**
** Preconditions      : None
**
** Global Variables   : Lin_GaaGlobalAccPoint,
**                      Lin_GaaChannelId2CoreIndex (LIN_MULTI_CORE_SUPPORT == STD_ON)
**
** Functions invoked  : EcuM_CheckWakeup
**
** Registers Used     : ucRLN3nLST
**
** Reference ID       : LIN_DUD_ACT_017, LIN_DUD_ACT_017_GBL001,
** Reference ID       : LIN_DUD_ACT_017_REG001
***********************************************************************************************************************/
#if (LIN_WAKEUP_SUPPORT == STD_ON)
#define LIN_START_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
STATIC FUNC(void, LIN_CODE_FAST) Lin_HwWakeUpFromBus(const uint8 LucChannel)
{
  volatile P2CONST(Lin_ChannelInfo, AUTOMATIC, LIN_CONST) LpLinChannelPtr;
  volatile P2CONST(Lin3_ChannelConfigType, AUTOMATIC, LIN_CONST) LpLin3ChannelPtr;
  volatile P2VAR(RLin3_UartRegs, AUTOMATIC, REGSPACE) LpLN3ChannelRegs;                                                 /* PRQA S 3432 # JV-01 */
  volatile P2VAR(Lin_RamData, AUTOMATIC, LIN_VAR_FAST_NO_INIT) LpRamVars;                                               /* PRQA S 3432 # JV-01 */
  uint8 LucChannelRamIndex;
  uint8 LucCoreIndex;

  #if (LIN_MULTI_CORE_SUPPORT == STD_ON)
  /* LucChannel is channel id, need to convert to chanel index */
  LucCoreIndex = Lin_GaaChannelId2CoreIndex[LucChannel];
  /* Get Channel Ram Index for each core */
  LucChannelRamIndex = (*(Lin_GaaGlobalAccPoint[LucCoreIndex].pChannelConfig))[LucChannel].ucChannelRamIndex;
  #else
  LucCoreIndex = LIN_ZERO;
  /* single core - Channel Ram index = channel id */
  LucChannelRamIndex = LucChannel;
  #endif /* #if (LIN_MULTI_CORE_SUPPORT == STD_ON) */

  /* Get the address of LIN Channel structure */
  LpLinChannelPtr = &((*(Lin_GaaGlobalAccPoint[LucCoreIndex].pChannelConfig))[LucChannel]);

/* Get the address of LIN Channel structure */
  LpRamVars = &((Lin_GaaGlobalAccPoint[LucCoreIndex].pChannelRamData)[LucChannelRamIndex]);

  /* Check if channel specific wake-up is enabled */
  if (LIN_TRUE == LpLinChannelPtr->blWakeupSupport)
  {
    LpLin3ChannelPtr = &((*(Lin_GaaGlobalAccPoint[LucCoreIndex].pRLIN3Properties))[LucChannel]);

    /* Get the RLIN3 Channel Base Address */
    LpLN3ChannelRegs = LpLin3ChannelPtr->pLn3ChanlBaseAddress;

    if (LIN_RESPONSE_COMPLETE == (uint8)(LpLN3ChannelRegs->ucRLN3nLST & LIN_RESPONSE_COMPLETE))
    {
      /* Clear sleep requested bit */
      LpRamVars->ucSlpRqst_RespRdy = LIN_WAKEUP;

      /* Clear the reception interrupt */
      LpLN3ChannelRegs->ucRLN3nLST = (LpLN3ChannelRegs->ucRLN3nLST & LIN_RECEPTION_DONE);
    } /* else No action required */

    /* Invoke the upper layer wakeup notification */
    EcuM_CheckWakeup((EcuM_WakeupSourceType)LIN_ONE << (LpLinChannelPtr->ucWakeupSourceId));

  } /* Channel specific wakeup is enabled */ /* else No action required */
}
#define LIN_STOP_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* #if (LIN_WAKEUP_SUPPORT == STD_ON) */

/***********************************************************************************************************************
** Function Name      : Lin_HwProcessData
**
** Service ID         : NA
**
** Description        : This service processes the transmit and receive
**                      interrupt requests
**
** Sync/Async         : Synchronous
**
** Re-entrancy        : Non Re-entrant for the same channel
**
** Input Parameters   : LucChannel
**
** Output Parameters  : None
**
** Return parameter   : None
**
** Preconditions      : None
**
** Global Variables   : Lin_GaaGlobalAccPoint,
**                      Lin_GaaChannelId2CoreIndex (LIN_MULTI_CORE_SUPPORT == STD_ON)
**
** Functions invoked  : Lin_HwHandleWakeupRequest, Lin_HwScheduleInterrupt
**                      LIN_ENTER_CRITICAL_SECTION, LIN_EXIT_CRITICAL_SECTION
**
** Registers Used     : ucRLN3nLST,  ucRLN3nLDBR
**
** Reference ID       : LIN_DUD_ACT_018, LIN_DUD_ACT_018_GBL001,
** Reference ID       : LIN_DUD_ACT_018_GBL002, LIN_DUD_ACT_018_GBL003,
** Reference ID       : LIN_DUD_ACT_018_GBL004, LIN_DUD_ACT_018_GBL005,
** Reference ID       : LIN_DUD_ACT_018_GBL006, LIN_DUD_ACT_018_GBL007,
** Reference ID       : LIN_DUD_ACT_018_REG001, LIN_DUD_ACT_018_REG002
** Reference ID       : LIN_DUD_ACT_018_REG003, LIN_DUD_ACT_018_REG004,
** Reference ID       : LIN_DUD_ACT_018_REG005, LIN_DUD_ACT_018_REG006,
** Reference ID       : LIN_DUD_ACT_018_REG007,
** Reference ID       : LIN_DUD_ACT_018_CRT001, LIN_DUD_ACT_018_CRT002,
** Reference ID       : LIN_DUD_ACT_018_CRT003, LIN_DUD_ACT_018_CRT004
***********************************************************************************************************************/
#if (LIN_MASTER_MODE_SUPPORT == STD_ON)
#define LIN_START_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
STATIC FUNC(void, LIN_CODE_FAST) Lin_HwProcessData(const uint8 LucChannel)
{
  #if (LIN_WAKEUP_SUPPORT == STD_ON)
  volatile P2CONST(Lin_ChannelInfo, AUTOMATIC, LIN_CONST) LpLinChannelPtr;
  #endif /* #if (LIN_WAKEUP_SUPPORT == STD_ON) */
  volatile P2VAR(Lin_RamData, AUTOMATIC, LIN_VAR_FAST_NO_INIT) LpRamVars;                                               /* PRQA S 3432 # JV-01 */
  volatile P2VAR(uint8, AUTOMATIC, LIN_VAR_FAST_NO_INIT) volatile LpStartDataBuffer;                                    /* PRQA S 3432 # JV-01 */
  Lin_FrameResponseType LenFrameType;
  uint8 LucIndex;
  uint8 LucDataLength;

  volatile P2CONST(Lin3_ChannelConfigType, AUTOMATIC, LIN_CONST) LpLin3ChannelPtr;
  volatile P2VAR(RLin3_UartRegs, AUTOMATIC, REGSPACE) LpLN3ChannelRegs;                                                 /* PRQA S 3432 # JV-01 */

  uint8 LucChannelRamIndex;
  uint8 LucCoreIndex;

  #if (LIN_MULTI_CORE_SUPPORT == STD_ON)
  /* LucChannel is channel id, need to convert to chanel index */
  LucCoreIndex = Lin_GaaChannelId2CoreIndex[LucChannel];
  /* Get Channel Ram Index for each core */
  LucChannelRamIndex = (*(Lin_GaaGlobalAccPoint[LucCoreIndex].pChannelConfig))[LucChannel].ucChannelRamIndex;
  #else
  LucCoreIndex = LIN_ZERO;
  /* single core - Channel Ram index = channel id */
  LucChannelRamIndex = LucChannel;
  #endif /* #if (LIN_MULTI_CORE_SUPPORT == STD_ON) */

  #if (LIN_WAKEUP_SUPPORT == STD_ON)
  /* Get the pointer to requested channel configuration */
  LpLinChannelPtr = &((*(Lin_GaaGlobalAccPoint[LucCoreIndex].pChannelConfig))[LucChannel]);
  #endif /* #if (LIN_WAKEUP_SUPPORT == STD_ON) */
  
  /* Get the address of LIN Channel structure */
  LpRamVars = &((Lin_GaaGlobalAccPoint[LucCoreIndex].pChannelRamData)[LucChannelRamIndex]);
  
  LpLin3ChannelPtr = &((*(Lin_GaaGlobalAccPoint[LucCoreIndex].pRLIN3Properties))[LucChannel]);

  /* Get the RLIN3 Channel Base Address */
  LpLN3ChannelRegs = LpLin3ChannelPtr->pLn3ChanlBaseAddress;

  /* Copy the data length to local variable */
  LucDataLength = LpRamVars->ucFrameLength;

  /* Check if the transmitted frame is for go-to-sleep command */
  if (LIN_SET_SLEEP_REQUEST == LpRamVars->ucSlpRqst_RespRdy)
  {

    /* Clear the sleep requested bit */
    LpRamVars->ucSlpRqst_RespRdy = LIN_CLR_SLEEP_REQUEST;

    /* Check for Frame Transmit Successfully */
    if (LIN_FRAME_COMPLETE == (uint8)(LpLN3ChannelRegs->ucRLN3nLST & LIN_FRAME_COMPLETE))
    {
      /* Clear the transmit interrupt */
      LpLN3ChannelRegs->ucRLN3nLST = (LpLN3ChannelRegs->ucRLN3nLST & LIN_TRANSMIT_DONE);
    } /* else No action required */

    #if (LIN_WAKEUP_SUPPORT == STD_ON)
    /* Check if channel specific wake-up support is enabled */
    if (LIN_TRUE == LpLinChannelPtr->blWakeupSupport)
    {
      /* Set RLIN3 to Slave Wake-up */
      (void)Lin_HwHandleWakeupRequest(LucChannel, LIN_SLAVE_ISSUE, LIN_GO_TO_SLEEP_SID);
    }
    else
    #endif /* #if (LIN_WAKEUP_SUPPORT == STD_ON) */
    {
      /* Enter the protection area */
      LIN_ENTER_CRITICAL_SECTION(LIN_INTERRUPT_CONTROL_PROTECTION);

      /* Disable RLIN3 Interrupt */
      Lin_HwScheduleInterrupt(LucChannel, LIN_INTERRUPT_DIS);

      /* Exit the protection area */
      LIN_EXIT_CRITICAL_SECTION(LIN_INTERRUPT_CONTROL_PROTECTION);
    }
  }
  /* If the transmitted frame is not a sleep frame */
  else
  {
    /* Get the frame type */
    LenFrameType = LpRamVars->enFrameType;

    #if (LIN_AR_VERSION == LIN_AR_R22_11_VERSION)
    switch (LenFrameType)
    {
    /* Frame is of type LIN_FRAMERESPONSE_RX */
    /* AR22-11 use LIN_FRAMERESPONSE_RX instead of LIN_SLAVE_RESPONSE */
    case LIN_FRAMERESPONSE_RX:
      /* If LATIT is generated for Header part in Rx Mode */
      if (LIN_TX_BUSY == LpRamVars->enChannelStatus)
      {
        if (LIN_HEADER_COMPLETE == (uint8)(LpLN3ChannelRegs->ucRLN3nLST & LIN_HEADER_COMPLETE))
        {
          /* Clear the header interrupt */
          LpLN3ChannelRegs->ucRLN3nLST = (LpLN3ChannelRegs->ucRLN3nLST & LIN_HEADER_DONE);
          /* Update channel status to LIN_RX_NO_RESPONSE */
          LpRamVars->enChannelStatus = LIN_RX_NO_RESPONSE;
        } /* else No action required */
      } /* else No action required */
      /* If LATIR is generated for data 1 part in Rx Mode */
      if (LIN_RX_NO_RESPONSE == LpRamVars->enChannelStatus)
      {
        if (LIN_DATA1RX_COMPLETE == (uint8)(LpLN3ChannelRegs->ucRLN3nLST & LIN_DATA1RX_COMPLETE))
        {
          /* Clear the data interrupt */
          LpLN3ChannelRegs->ucRLN3nLST = (LpLN3ChannelRegs->ucRLN3nLST & LIN_DATA1RX_DONE);
          /* Update channel status to LIN_RX_BUSY */
          LpRamVars->enChannelStatus = LIN_RX_BUSY;
        } /* else No action required */
      } /* else No action required */
      /* If LATIR is generated for response part in Rx Mode */
      if (LIN_RX_BUSY == LpRamVars->enChannelStatus)
      {
        if (LIN_RESPONSE_COMPLETE == (uint8)(LpLN3ChannelRegs->ucRLN3nLST & LIN_RESPONSE_COMPLETE))
        {
          /* Clear the reception interrupt */
          LpLN3ChannelRegs->ucRLN3nLST = (LpLN3ChannelRegs->ucRLN3nLST & LIN_RECEPTION_DONE);

          LpStartDataBuffer = &LpRamVars->aaFrameData[(uint32)LIN_ZERO];

          /* Copy data to Tx Buffer */
          for (LucIndex = LIN_ZERO; LucDataLength > LucIndex; LucIndex++)
          {
            *LpStartDataBuffer = LpLN3ChannelRegs->ucRLN3nLDBR[LucIndex];                                               /* PRQA S 0404 # JV-01 */
            LpStartDataBuffer++;                                                                                        /* PRQA S 3387 # JV-01 */
          }
          /* Update channel status to LIN_RX_OK */
          LpRamVars->enChannelStatus = LIN_RX_OK;
        } /* else No action required */
      } /* else No action required */
      break;
    /* Frame is of type LIN_FRAMERESPONSE_TX */
    /* AR22-11 use LIN_FRAMERESPONSE_TX instead of LIN_MASTER_RESPONSE */
    case LIN_FRAMERESPONSE_TX:
      /* Check for Frame Transmit Successfully */
      if (LIN_FRAME_COMPLETE == (uint8)(LpLN3ChannelRegs->ucRLN3nLST & LIN_FRAME_COMPLETE))
      {
        /* Clear the transmit interrupt */
        LpLN3ChannelRegs->ucRLN3nLST = (LpLN3ChannelRegs->ucRLN3nLST & LIN_TRANSMIT_DONE);
        /* Update channel status to LIN_TX_OK */
        LpRamVars->enChannelStatus = LIN_TX_OK;
      } /* else No action required */
      break;
    /* Frame is of type LIN_FRAMERESPONSE_IGNORE */
    /* AR22-11 use LIN_FRAMERESPONSE_IGNORE instead of LIN_SLAVE_TO_SLAVE */
    case LIN_FRAMERESPONSE_IGNORE:
      if (LIN_HEADER_COMPLETE == (uint8)(LpLN3ChannelRegs->ucRLN3nLST & LIN_HEADER_COMPLETE))
      {
        /* Clear the header interrupt */
        LpLN3ChannelRegs->ucRLN3nLST = (LpLN3ChannelRegs->ucRLN3nLST & LIN_HEADER_DONE);
        /* Set the channel status to LIN_TX_OK */
        LpRamVars->enChannelStatus = LIN_TX_OK;
      } /* else No action required */
      if (LIN_RESPONSE_COMPLETE == (uint8)(LpLN3ChannelRegs->ucRLN3nLST & LIN_RESPONSE_COMPLETE))
      {
        /* Clear the reception interrupt */
        LpLN3ChannelRegs->ucRLN3nLST = (LpLN3ChannelRegs->ucRLN3nLST & LIN_RECEPTION_DONE);
      } /* else No action required */
      break;
    default:
      /* No action required */
      break;
    }
    #else
    switch (LenFrameType)
    {
    /* Frame is of type LIN_SLAVE_RESPONSE */
    case LIN_SLAVE_RESPONSE:
      /* If LATIT is generated for Header part in Rx Mode */
      if (LIN_RX_BUSY == LpRamVars->enChannelStatus)
      {
        if (LIN_HEADER_COMPLETE == (uint8)(LpLN3ChannelRegs->ucRLN3nLST & LIN_HEADER_COMPLETE))
        {
          /* Clear the header interrupt */
          LpLN3ChannelRegs->ucRLN3nLST = (LpLN3ChannelRegs->ucRLN3nLST & LIN_HEADER_DONE);
          /* Update channel status to LIN_RX_NO_RESPONSE */
          LpRamVars->enChannelStatus = LIN_RX_NO_RESPONSE;
        } /* else No action required */
      } /* else No action required */
      /* If LATIR is generated for data 1 part in Rx Mode */
      if (LIN_RX_NO_RESPONSE == LpRamVars->enChannelStatus)
      {
        if (LIN_DATA1RX_COMPLETE == (uint8)(LpLN3ChannelRegs->ucRLN3nLST & LIN_DATA1RX_COMPLETE))
        {
          /* Clear the data interrupt */
          LpLN3ChannelRegs->ucRLN3nLST = (LpLN3ChannelRegs->ucRLN3nLST & LIN_DATA1RX_DONE);
          /* Update channel status to LIN_RX_BUSY */
          LpRamVars->enChannelStatus = LIN_RX_BUSY;
        } /* else No action required */
      } /* else No action required */
      /* If LATIR is generated for response part in Rx Mode */
      if (LIN_RX_BUSY == LpRamVars->enChannelStatus)
      {
        if (LIN_RESPONSE_COMPLETE == (uint8)(LpLN3ChannelRegs->ucRLN3nLST & LIN_RESPONSE_COMPLETE))
        {
          /* Clear the reception interrupt */
          LpLN3ChannelRegs->ucRLN3nLST = (LpLN3ChannelRegs->ucRLN3nLST & LIN_RECEPTION_DONE);

          LpStartDataBuffer = &LpRamVars->aaFrameData[(uint32)LIN_ZERO];

          /* Copy data to Tx Buffer */
          for (LucIndex = LIN_ZERO; LucDataLength > LucIndex; LucIndex++)
          {
            *LpStartDataBuffer = LpLN3ChannelRegs->ucRLN3nLDBR[LucIndex];

            LpStartDataBuffer++;
          }
          /* Update channel status to LIN_RX_OK */
          LpRamVars->enChannelStatus = LIN_RX_OK;
        } /* else No action required */
      } /* else No action required */
      break;
    /* Frame is of type LIN_MASTER_RESPONSE */
    case LIN_MASTER_RESPONSE:
      /* Check for Frame Transmit Successfully */
      if (LIN_FRAME_COMPLETE == (uint8)(LpLN3ChannelRegs->ucRLN3nLST & LIN_FRAME_COMPLETE))
      {
        /* Clear the transmit interrupt */
        LpLN3ChannelRegs->ucRLN3nLST = (LpLN3ChannelRegs->ucRLN3nLST & LIN_TRANSMIT_DONE);
        /* Update channel status to LIN_TX_OK */
        LpRamVars->enChannelStatus = LIN_TX_OK;
      } /* else No action required */
      break;
    /* Frame is of type LIN_SLAVE_TO_SLAVE */
    case LIN_SLAVE_TO_SLAVE:
      if (LIN_HEADER_COMPLETE == (uint8)(LpLN3ChannelRegs->ucRLN3nLST & LIN_HEADER_COMPLETE))
      {
        /* Clear the header interrupt */
        LpLN3ChannelRegs->ucRLN3nLST = (LpLN3ChannelRegs->ucRLN3nLST & LIN_HEADER_DONE);
        /* Set the channel status to LIN_TX_OK */
        LpRamVars->enChannelStatus = LIN_TX_OK;
      } /* else No action required */
      if (LIN_RESPONSE_COMPLETE == (uint8)(LpLN3ChannelRegs->ucRLN3nLST & LIN_RESPONSE_COMPLETE))
      {
        /* Clear the reception interrupt */
        LpLN3ChannelRegs->ucRLN3nLST = (LpLN3ChannelRegs->ucRLN3nLST & LIN_RECEPTION_DONE);
      } /* else No action required */
      break;
    default:
      /* No action required */
      break;
    }
    #endif /* #if (LIN_AR_VERSION == LIN_AR_R22_11_VERSION) */

    /* Enter the protection area */
    LIN_ENTER_CRITICAL_SECTION(LIN_INTERRUPT_CONTROL_PROTECTION);

    /* Disable RLIN3 Interrupt */
    Lin_HwScheduleInterrupt(LucChannel, LIN_INTERRUPT_DIS);

    /* Exit the protection area */
    LIN_EXIT_CRITICAL_SECTION(LIN_INTERRUPT_CONTROL_PROTECTION);
  }
}
#define LIN_STOP_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* #if (LIN_MASTER_MODE_SUPPORT == STD_ON) */

/***********************************************************************************************************************
** Function Name      : Lin_HwErrorProcessing
**
** Service ID         : NA
**
** Description        : This service processes the status interrupt requests
**
** Sync/Async         : Synchronous
**
** Re-entrancy        : Non Re-entrant for the same channel
**
** Input Parameters   : LucChannel
**
** Output Parameters  : None
**
** Return parameter   : None
**
** Preconditions      : None
**
** Global Variables   : Lin_GaaGlobalAccPoint,
**                      Lin_GaaChannelId2CoreIndex (LIN_MULTI_CORE_SUPPORT == STD_ON)
**
** Functions invoked  : LIN_DEM_REPORT_ERROR,
**                      Lin_HwHandleWakeupRequest,
**                      Lin_HwScheduleInterrupt
**                      LIN_ENTER_CRITICAL_SECTION, LIN_EXIT_CRITICAL_SECTION
**
** Registers Used     : ucRLN3nLEST, ucRLN3nLST
**
** Reference ID       : LIN_DUD_ACT_019, LIN_DUD_ACT_019_ERR001,
** Reference ID       : LIN_DUD_ACT_019_ERR002, LIN_DUD_ACT_019_ERR003,
** Reference ID       : LIN_DUD_ACT_019_ERR004, LIN_DUD_ACT_019_GBL001,
** Reference ID       : LIN_DUD_ACT_019_GBL002, LIN_DUD_ACT_019_GBL003,
** Reference ID       : LIN_DUD_ACT_019_GBL005, LIN_DUD_ACT_019_GBL006,
** Reference ID       : LIN_DUD_ACT_019_GBL008, LIN_DUD_ACT_019_GBL009,
** Reference ID       : LIN_DUD_ACT_019_GBL010, LIN_DUD_ACT_019_GBL011,
** Reference ID       : LIN_DUD_ACT_019_GBL012, LIN_DUD_ACT_019_GBL013,
** Reference ID       : LIN_DUD_ACT_019_GBL014, LIN_DUD_ACT_019_GBL015,
** Reference ID       : LIN_DUD_ACT_019_REG001, LIN_DUD_ACT_019_REG002,
** Reference ID       : LIN_DUD_ACT_019_REG003, LIN_DUD_ACT_019_REG005,
** Reference ID       : LIN_DUD_ACT_019_REG006, LIN_DUD_ACT_019_REG007,
** Reference ID       : LIN_DUD_ACT_019_REG009, LIN_DUD_ACT_019_REG010,
** Reference ID       : LIN_DUD_ACT_019_REG011, LIN_DUD_ACT_019_REG012,
** Reference ID       : LIN_DUD_ACT_019_REG015, LIN_DUD_ACT_019_CRT001,
** Reference ID       : LIN_DUD_ACT_019_CRT002, LIN_DUD_ACT_019_CRT003,
** Reference ID       : LIN_DUD_ACT_019_CRT004, LIN_DUD_ACT_019_CRT005
** Reference ID       : LIN_DUD_ACT_019_CRT006, LIN_DUD_ACT_019_CRT007
** Reference ID       : LIN_DUD_ACT_019_CRT008
***********************************************************************************************************************/
#if (LIN_MASTER_MODE_SUPPORT == STD_ON)
#define LIN_START_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
STATIC FUNC(void, LIN_CODE_FAST) Lin_HwErrorProcessing(const uint8 LucChannel)
{
  #if (LIN_WAKEUP_SUPPORT == STD_ON)
  volatile P2CONST(Lin_ChannelInfo, AUTOMATIC, LIN_CONST) LpLinChannelPtr;
  #endif /* #if (LIN_WAKEUP_SUPPORT == STD_ON) */
  volatile P2CONST(Lin3_ChannelConfigType, AUTOMATIC, LIN_CONST) LpLin3ChannelPtr;
  volatile P2VAR(RLin3_UartRegs, AUTOMATIC, REGSPACE) LpLN3ChannelRegs;                                                 /* PRQA S 3432 # JV-01 */
  volatile P2VAR(Lin_RamData, AUTOMATIC, LIN_VAR_FAST_NO_INIT) LpRamVars;                                               /* PRQA S 3432 # JV-01 */

  Lin_FrameResponseType LenFrameType;
  uint8 LucChannelRamIndex;
  uint8 LucCoreIndex;

  #if (LIN_MULTI_CORE_SUPPORT == STD_ON)
  /* LucChannel is channel id, need to convert to chanel index */
  LucCoreIndex = Lin_GaaChannelId2CoreIndex[LucChannel];
  /* Get Channel Ram Index for each core */
  LucChannelRamIndex = (*(Lin_GaaGlobalAccPoint[LucCoreIndex].pChannelConfig))[LucChannel].ucChannelRamIndex;
  #else
  LucCoreIndex = LIN_ZERO;
  /* single core - Channel Ram index = channel id */
  LucChannelRamIndex = LucChannel;
  #endif /* #if (LIN_MULTI_CORE_SUPPORT == STD_ON) */

  #if (LIN_WAKEUP_SUPPORT == STD_ON)
  /* Get the pointer to requested channel configuration */
  LpLinChannelPtr = &((*(Lin_GaaGlobalAccPoint[LucCoreIndex].pChannelConfig))[LucChannel]);
  #endif /* #if (LIN_WAKEUP_SUPPORT == STD_ON) */

  /* Get the pointer to channel RAM data */
  LpRamVars = &((Lin_GaaGlobalAccPoint[LucCoreIndex].pChannelRamData)[LucChannelRamIndex]);

  /* Get the channel index */
  LpLin3ChannelPtr = &((*(Lin_GaaGlobalAccPoint[LucCoreIndex].pRLIN3Properties))[LucChannel]);

  /* Get the RLIN3 Channel Base Address */
  LpLN3ChannelRegs = LpLin3ChannelPtr->pLn3ChanlBaseAddress;

  /* Get frame type */
  LenFrameType = LpRamVars->enFrameType;

  /* Check for any error occurred */
  if (LIN_ERROR_OCCURED == (uint8)(LpLN3ChannelRegs->ucRLN3nLST & LIN_ERROR_OCCURED))
  {
    /* Check if the transmitted frame is for go-to-sleep command */
    if (LIN_SET_SLEEP_REQUEST == LpRamVars->ucSlpRqst_RespRdy)
    {
      /* LIN_CH_SLEEP:                                                       */
      /* Lin_GetStatus() has already been called after calling Lin_GoToSleep */
      /* or                                                                  */
      /* LIN_CH_SLEEP_PENDING:                                               */
      /* Lin_GetStatus() has not been called yet after calling Lin_GoToSleep */
      /* The status of channel must not be changed while issuing the         */
      /* go-to-sleep command even if some errors have occured.               */
      if ((LIN_CH_SLEEP == LpRamVars->enChannelStatus) || (LIN_TRUE == LpRamVars->blSleepPending))
      {
        /* Clear the sleep requested bit */
        LpRamVars->ucSlpRqst_RespRdy = LIN_CLR_SLEEP_REQUEST;

        if (LIN_HEADER_COMPLETE == (uint8)(LpLN3ChannelRegs->ucRLN3nLST & LIN_HEADER_COMPLETE))
        {
          /* Clear the header interrupt */
          LpLN3ChannelRegs->ucRLN3nLST = (LpLN3ChannelRegs->ucRLN3nLST & LIN_HEADER_DONE);
        } /* else No action required */

        /* Clear all error flags and the ERR bit of the RLN3nLST register is automatically cleared */
        LpLN3ChannelRegs->ucRLN3nLEST = LIN_RESET_VALUE;

        #if (LIN_WAKEUP_SUPPORT == STD_ON)
        /* Check if channel specific wake-up support is enabled */
        if (LIN_TRUE == LpLinChannelPtr->blWakeupSupport)
        {
          /* Set RLIN3 to Slave Wake-up */
          (void)Lin_HwHandleWakeupRequest(LucChannel, LIN_SLAVE_ISSUE, LIN_GO_TO_SLEEP_SID);
        }
        else
        #endif /* #if (LIN_WAKEUP_SUPPORT == STD_ON) */
        {

          /* Enter the protection area */
          LIN_ENTER_CRITICAL_SECTION(LIN_INTERRUPT_CONTROL_PROTECTION);

          /* Disable RLIN3 Interrupt */
          Lin_HwScheduleInterrupt(LucChannel, LIN_INTERRUPT_DIS);

          /* Exit the protection area */
          LIN_EXIT_CRITICAL_SECTION(LIN_INTERRUPT_CONTROL_PROTECTION);
        }
      } /* else No action required */
    }
    /* Check if an error was occurred in Lin_Wakeup() */
    else if (LIN_TRUE == LpRamVars->blWakeupCalled)
    {
      /* Reset the LinIf wake-up flag */
      LpRamVars->blWakeupCalled = LIN_FALSE;

      /* Check for Bit error and Header Transmission error*/
      if (LIN_ERROR_FREE != (uint8)(LpLN3ChannelRegs->ucRLN3nLEST & (LIN_BIT_ERROR | LIN_PBUS_ERROR)))
      {
        /* Update channel status to LIN_TX_HEADER_ERROR */
        LpRamVars->enChannelStatus = LIN_TX_HEADER_ERROR;

        /* Clear BER and PBER bit */
        LpLN3ChannelRegs->ucRLN3nLEST = (LpLN3ChannelRegs->ucRLN3nLEST & (LIN_BIT_CLEAR & LIN_PBUS_CLEAR));
      } /* else No action required */

      /* Enter the protection area */
      LIN_ENTER_CRITICAL_SECTION(LIN_INTERRUPT_CONTROL_PROTECTION);

      /* Disable RLIN3 Interrupt */
      Lin_HwScheduleInterrupt(LucChannel, LIN_INTERRUPT_DIS);

      /* Exit the protection area */
      LIN_EXIT_CRITICAL_SECTION(LIN_INTERRUPT_CONTROL_PROTECTION);
    }
    /* Other than go-to-sleep command and Lin_Wakeup(), Lin_SendFrame() with LIN_SLAVE_TO_SLAVE */
    /* Lin_SendFrame() with LIN_FRAMERESPONSE_IGNORE (for AR22-11) instead of LIN_SLAVE_TO_SLAVE*/
    #if (LIN_AR_VERSION == LIN_AR_R22_11_VERSION)
    else if (LIN_FRAMERESPONSE_IGNORE == LenFrameType)
    {
      /* An error was occurred in response part */
      if (LIN_HEADER_COMPLETE == (uint8)(LpLN3ChannelRegs->ucRLN3nLST & LIN_HEADER_COMPLETE))
      {
        /* Clear the header interrupt */
        LpLN3ChannelRegs->ucRLN3nLST = (LpLN3ChannelRegs->ucRLN3nLST & LIN_HEADER_DONE);

        /* Set the channel status to LIN_TX_OK */
        LpRamVars->enChannelStatus = LIN_TX_OK;

        /* Clear all error flags and the ERR bit of the RLN3nLST register is automatically cleared */
        LpLN3ChannelRegs->ucRLN3nLEST = LIN_RESET_VALUE;
      }
      /* an error was occurred in header part */
      else
      {
        /* Check for Bit error and Header Transmission error */
        if (LIN_ERROR_FREE != (uint8)(LpLN3ChannelRegs->ucRLN3nLEST & (LIN_BIT_ERROR | LIN_PBUS_ERROR)))
        {
          /* Update channel status to LIN_TX_HEADER_ERROR */
          LpRamVars->enChannelStatus = LIN_TX_HEADER_ERROR;

          /* Clear BER and PBER bit */
          LpLN3ChannelRegs->ucRLN3nLEST = (LpLN3ChannelRegs->ucRLN3nLEST & (LIN_BIT_CLEAR & LIN_PBUS_CLEAR));
        } /* else No action required */

        /* Check for any Time out error */
        if (LIN_TIMEOUT_ERROR == (uint8)(LpLN3ChannelRegs->ucRLN3nLEST & LIN_TIMEOUT_ERROR))
        {
          /* Update channel status to LIN_TX_HEADER_ERROR */
          LpRamVars->enChannelStatus = LIN_TX_HEADER_ERROR;

          #ifdef LIN_E_TIMEOUT_FAILURE
          /* Report Error to DEM */
          LIN_DEM_REPORT_ERROR(LIN_E_TIMEOUT_FAILURE, DEM_EVENT_STATUS_FAILED);
          #endif /* #ifdef LIN_E_TIMEOUT_FAILURE */

          /* Clear FTER bit */
          LpLN3ChannelRegs->ucRLN3nLEST = (LpLN3ChannelRegs->ucRLN3nLEST & LIN_TIMEOUT_CLEAR);
        } /* else No action required */
      }

      /* Enter the protection area */
      LIN_ENTER_CRITICAL_SECTION(LIN_INTERRUPT_CONTROL_PROTECTION);

      /* Disable RLIN3 Interrupt */
      Lin_HwScheduleInterrupt(LucChannel, LIN_INTERRUPT_DIS);

      /* Exit the protection area */
      LIN_EXIT_CRITICAL_SECTION(LIN_INTERRUPT_CONTROL_PROTECTION);
    }
    #else
    /* Other than go-to-sleep command and Lin_Wakeup(), Lin_SendFrame() 
       with LIN_SLAVE_TO_SLAVE (for AR4.3.1 and AR4,2,2) */
    else if (LIN_SLAVE_TO_SLAVE == LenFrameType)
    {
      /* An error was occurred in response part */
      if (LIN_HEADER_COMPLETE == (uint8)(LpLN3ChannelRegs->ucRLN3nLST & LIN_HEADER_COMPLETE))
      {
        /* Clear the header interrupt */
        LpLN3ChannelRegs->ucRLN3nLST = (LpLN3ChannelRegs->ucRLN3nLST & LIN_HEADER_DONE);

        /* Set the channel status to LIN_TX_OK */
        LpRamVars->enChannelStatus = LIN_TX_OK;

        /* Clear all error flags and the ERR bit of the RLN3nLST register is automatically cleared */
        LpLN3ChannelRegs->ucRLN3nLEST = LIN_RESET_VALUE;
      }
      /* an error was occurred in header part */
      else
      {
        /* Check for Bit error and Header Transmission error */
        if (LIN_ERROR_FREE != (uint8)(LpLN3ChannelRegs->ucRLN3nLEST & (LIN_BIT_ERROR | LIN_PBUS_ERROR)))
        {
          /* Update channel status to LIN_TX_HEADER_ERROR */
          LpRamVars->enChannelStatus = LIN_TX_HEADER_ERROR;

          /* Clear BER and PBER bit */
          LpLN3ChannelRegs->ucRLN3nLEST = (LpLN3ChannelRegs->ucRLN3nLEST & (LIN_BIT_CLEAR & LIN_PBUS_CLEAR));
        } /* else No action required */

        /* Check for any Time out error */
        if (LIN_TIMEOUT_ERROR == (uint8)(LpLN3ChannelRegs->ucRLN3nLEST & LIN_TIMEOUT_ERROR))
        {
          /* Update channel status to LIN_TX_HEADER_ERROR */
          LpRamVars->enChannelStatus = LIN_TX_HEADER_ERROR;

          #ifdef LIN_E_TIMEOUT_FAILURE
          /* Report Error to DEM */
          LIN_DEM_REPORT_ERROR(LIN_E_TIMEOUT_FAILURE, DEM_EVENT_STATUS_FAILED);
          #endif /* #ifdef LIN_E_TIMEOUT_FAILURE */

          /* Clear FTER bit */
          LpLN3ChannelRegs->ucRLN3nLEST = (LpLN3ChannelRegs->ucRLN3nLEST & LIN_TIMEOUT_CLEAR);
        } /* else No action required */
      }

      /* Enter the protection area */
      LIN_ENTER_CRITICAL_SECTION(LIN_INTERRUPT_CONTROL_PROTECTION);

      /* Disable RLIN3 Interrupt */
      Lin_HwScheduleInterrupt(LucChannel, LIN_INTERRUPT_DIS);

      /* Exit the protection area */
      LIN_EXIT_CRITICAL_SECTION(LIN_INTERRUPT_CONTROL_PROTECTION);
    }
    #endif /* #if (LIN_AR_VERSION == LIN_AR_R22_11_VERSION) */
    /* Lin_SendFrame() with LIN_FRAMERESPONSE_TX and LIN_FRAMERESPONSE_RX (for AR22-11)
    or LIN_MASTER_RESPONSE and LIN_SLAVE_RESPONSE (for AR4.3.1 and AR4.2.2) */
    else
    {
      /* Check for any checksum field error or any framing error */
      if (LIN_ERROR_FREE != (uint8)(LpLN3ChannelRegs->ucRLN3nLEST & (LIN_CHECKSUM_ERROR | LIN_FRAMING_ERROR)))
      {
        /* Update channel status to LIN_RX_ERROR */
        LpRamVars->enChannelStatus = LIN_RX_ERROR;

        /* Clear CSER and FER bit */
        LpLN3ChannelRegs->ucRLN3nLEST = (LpLN3ChannelRegs->ucRLN3nLEST & (LIN_CHECKSUM_CLEAR & LIN_FRAMING_CLEAR));
      } /* else No action required */

      /* Check for any Time out error */
      if (LIN_TIMEOUT_ERROR == (uint8)(LpLN3ChannelRegs->ucRLN3nLEST & LIN_TIMEOUT_ERROR))
      {
        /* Check if header frame transmit successfully */
        if (LIN_HEADER_COMPLETE == (uint8)(LpLN3ChannelRegs->ucRLN3nLST & LIN_HEADER_COMPLETE))
        {
          #if (LIN_AR_VERSION == LIN_AR_R22_11_VERSION)
          /* AR22-11 use LIN_FRAMERESPONSE_TX instead of LIN_MASTER_RESPONSE */
          if (LIN_FRAMERESPONSE_TX == LenFrameType)
          {
            /* An error was occurred in response transmission part */
            /* Update channel status to LIN_TX_ERROR */
            LpRamVars->enChannelStatus = LIN_TX_ERROR;
          }
          #else
          if (LIN_MASTER_RESPONSE == LenFrameType)
          {
            /* An error was occurred in response transmission part */
            /* Update channel status to LIN_TX_ERROR */
            LpRamVars->enChannelStatus = LIN_TX_ERROR;
          }
          #endif /* (LIN_AR_VERSION == LIN_AR_R22_11_VERSION) */
          /* Frame type is of LIN_SLAVE_RESPONSE (for AR4.3.1 and AR4.2.2) */
          /* Frame type is of LIN_FRAMERESPONSE_RX (for AR22-11) */
          else
          {
            /* An error was occurred in response reception part */
            /* Check if at least 1 response byte has been received */
            if (LIN_DATA1RX_COMPLETE == (uint8)(LpLN3ChannelRegs->ucRLN3nLST & LIN_DATA1RX_COMPLETE))
            {
              /* Update channel status to LIN_RX_ERROR */
              LpRamVars->enChannelStatus = LIN_RX_ERROR;
            }
            /* If no response byte has been received */
            else
            {
              /* Update channel status to LIN_RX_NO_RESPONSE */
              LpRamVars->enChannelStatus = LIN_RX_NO_RESPONSE;
            }
          }
        }
        /* An error was occurred in header part */
        else
        {
          /* Update channel status to LIN_TX_HEADER_ERROR */
          LpRamVars->enChannelStatus = LIN_TX_HEADER_ERROR;
        }
        #ifdef LIN_E_TIMEOUT_FAILURE
        /* Report Error to DEM */
        LIN_DEM_REPORT_ERROR(LIN_E_TIMEOUT_FAILURE, DEM_EVENT_STATUS_FAILED);
        #endif /* #ifdef LIN_E_TIMEOUT_FAILURE */

        /* Clear FTER bit */
        LpLN3ChannelRegs->ucRLN3nLEST = (LpLN3ChannelRegs->ucRLN3nLEST & LIN_TIMEOUT_CLEAR);
      } /* else No action required */

      /* Check for Bit error */
      if (LIN_ERROR_FREE != (uint8)(LpLN3ChannelRegs->ucRLN3nLEST & (LIN_BIT_ERROR | LIN_PBUS_ERROR)))
      {
        /* Check if header frame transmit successfully */
        if (LIN_HEADER_COMPLETE == (uint8)(LpLN3ChannelRegs->ucRLN3nLST & LIN_HEADER_COMPLETE))
        {
          /* Update channel status to LIN_TX_ERROR */
          LpRamVars->enChannelStatus = LIN_TX_ERROR;
        }
        /* Check if header frame transmit not successful */
        else
        {
          /* Update channel status to LIN_TX_HEADER_ERROR */
          LpRamVars->enChannelStatus = LIN_TX_HEADER_ERROR;
        }

        /* Clear BER and PBER bit */
        LpLN3ChannelRegs->ucRLN3nLEST = (LpLN3ChannelRegs->ucRLN3nLEST & (LIN_BIT_CLEAR & LIN_PBUS_CLEAR));
      } /* else No action required */

      if (LIN_HEADER_COMPLETE == (uint8)(LpLN3ChannelRegs->ucRLN3nLST & LIN_HEADER_COMPLETE))
      {
        /* Clear the header interrupt */
        LpLN3ChannelRegs->ucRLN3nLST = (LpLN3ChannelRegs->ucRLN3nLST & LIN_HEADER_DONE);
      } /* else No action required */

      /* Enter the protection area */
      LIN_ENTER_CRITICAL_SECTION(LIN_INTERRUPT_CONTROL_PROTECTION);

      /* Disable RLIN3 Interrupt */
      Lin_HwScheduleInterrupt(LucChannel, LIN_INTERRUPT_DIS);

      /* Exit the protection area */
      LIN_EXIT_CRITICAL_SECTION(LIN_INTERRUPT_CONTROL_PROTECTION);
    }
  } /* else No action required */
}
#define LIN_STOP_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* #if (LIN_MASTER_MODE_SUPPORT == STD_ON) */
/***********************************************************************************************************************
** Function Name      : Lin_HwLoadTxBuffer
**
** Service ID         : NA
**
** Description        : This service copies data to Tx buffer
**
** Sync/Async         : Synchronous
**
** Re-entrancy        : Non Re-entrant for the same channel
**
** Input Parameters   : LucChannel
**
** Output Parameters  : None
**
** Return parameter   : None
**
** Preconditions      : None
**
** Global Variables   : Lin_GaaGlobalAccPoint,
**                      Lin_GaaChannelId2CoreIndex (LIN_MULTI_CORE_SUPPORT == STD_ON)
**
** Functions invoked  : None
**
** Registers Used     : ucRLN3nLDBR
**
** Reference ID       : LIN_DUD_ACT_020, LIN_DUD_ACT_020_REG001
***********************************************************************************************************************/
#define LIN_START_SEC_PRIVATE_CODE
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
STATIC FUNC(void, LIN_PRIVATE_CODE) Lin_HwLoadTxBuffer(const uint8 LucChannel)
{
  volatile P2CONST(Lin3_ChannelConfigType, AUTOMATIC, LIN_PRIVATE_CONST) LpLin3ChannelPtr;
  volatile P2VAR(RLin3_UartRegs, AUTOMATIC, REGSPACE) LpLN3ChannelRegs;                                                 /* PRQA S 3432 # JV-01 */
  volatile P2VAR(Lin_RamData, AUTOMATIC, LIN_VAR_FAST_NO_INIT) LpRamVars;                                               /* PRQA S 3432, 3678 # JV-01, JV-01 */
  volatile P2VAR(uint8, AUTOMATIC, LIN_VAR_FAST_NO_INIT) volatile LpStartDataBuffer;                                    /* PRQA S 3432, 3678 # JV-01, JV-01 */
  uint8 LucIncrement;
  uint8 LucDataLength;
  uint8 LucChannelRamIndex;
  uint8 LucCoreIndex;

  #if (LIN_MULTI_CORE_SUPPORT == STD_ON)
  /* LucChannel is channel id, need to convert to chanel index */
  LucCoreIndex = Lin_GaaChannelId2CoreIndex[LucChannel];
  /* Get Channel Ram Index for each core */
  LucChannelRamIndex = (*(Lin_GaaGlobalAccPoint[LucCoreIndex].pChannelConfig))[LucChannel].ucChannelRamIndex;
  #else
  LucCoreIndex = LIN_ZERO;
  /* single core - Channel Ram index = channel id */
  LucChannelRamIndex = LucChannel;
  #endif /* #if (LIN_MULTI_CORE_SUPPORT == STD_ON) */

  /* Get the address of LIN Channel structure */
  LpRamVars = &((Lin_GaaGlobalAccPoint[LucCoreIndex].pChannelRamData)[LucChannelRamIndex]);

  /* Copy the data length to local variable */
  LucDataLength = LpRamVars->ucFrameLength;

  LpStartDataBuffer = &LpRamVars->aaFrameData[(uint32)LIN_ZERO];

  LpLin3ChannelPtr = &((*(Lin_GaaGlobalAccPoint[LucCoreIndex].pRLIN3Properties))[LucChannel]);

  /* Get the RLIN3 Channel Base Address */
  LpLN3ChannelRegs = LpLin3ChannelPtr->pLn3ChanlBaseAddress;

  /* Copy data to Tx Buffer */
  for (LucIncrement = LIN_ZERO; LucDataLength > LucIncrement; LucIncrement++)
  {
    LpLN3ChannelRegs->ucRLN3nLDBR[LucIncrement] = *LpStartDataBuffer;                                                   /* PRQA S 0404 # JV-01 */

    LpStartDataBuffer++;                                                                                                /* PRQA S 3387 # JV-01 */
  }
}
#define LIN_STOP_SEC_PRIVATE_CODE
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name      : Lin_HwWakeupOnGoing
**
** Service ID         : NA
**
** Description        : This service does wake-up processing
**
** Sync/Async         : Synchronous
**
** Re-entrancy        : Non Re-entrant for the same channel
**
** Input Parameters   : LucChannel
**
** Output Parameters  : None
**
** Return parameter   : None
**
** Preconditions      : None
**
** Global Variables   : Lin_GaaGlobalAccPoint,
**                      Lin_GaaChannelId2CoreIndex (LIN_MULTI_CORE_SUPPORT == STD_ON)
**
** Functions invoked  : Lin_HwScheduleInterrupt, Lin_HwSetMasterMode,
**                      Lin_HwSlaveStartHeaderReception, Lin_ErrorReport
**                      LIN_ENTER_CRITICAL_SECTION, LIN_EXIT_CRITICAL_SECTION
**
** Registers Used     : ucRLN3nLST
**
** Reference ID       : LIN_DUD_ACT_021, LIN_DUD_ACT_021_GBL001,
** Reference ID       : LIN_DUD_ACT_021_GBL002, LIN_DUD_ACT_021_REG001,
** Reference ID       : LIN_DUD_ACT_021_CRT001, LIN_DUD_ACT_021_CRT002,
** Reference ID       : LIN_DUD_ACT_021_ERR001, LIN_DUD_ACT_021_CRT003,
** Reference ID       : LIN_DUD_ACT_021_CRT004
***********************************************************************************************************************/
#define LIN_START_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
STATIC FUNC(void, LIN_CODE_FAST) Lin_HwWakeupOnGoing(const uint8 LucChannel)
{
  volatile P2CONST(Lin3_ChannelConfigType, AUTOMATIC, LIN_CONST) LpLin3ChannelPtr;
  volatile P2VAR(RLin3_UartRegs, AUTOMATIC, REGSPACE) LpLN3ChannelRegs;                                                 /* PRQA S 3432 # JV-01 */
  volatile P2VAR(Lin_RamData, AUTOMATIC, LIN_VAR_FAST_NO_INIT) LpRamVars;                                               /* PRQA S 3432 # JV-01 */
  uint8 LucChannelRamIndex;
  uint8 LucCoreIndex;

  #if (LIN_SLAVE_MODE_SUPPORT == STD_ON)
  Std_ReturnType LucReturnValue;
  /* Initialize the return value */
  LucReturnValue = E_NOT_OK;                                                                                            /* PRQA S 2982 # JV-01 */
  #endif /* (LIN_SLAVE_MODE_SUPPORT == STD_ON) */

  #if (LIN_MULTI_CORE_SUPPORT == STD_ON)
  /* LucChannel is channel id, need to convert to chanel index */
  LucCoreIndex = Lin_GaaChannelId2CoreIndex[LucChannel];
  /* Get Channel Ram Index for each core */
  LucChannelRamIndex = (*(Lin_GaaGlobalAccPoint[LucCoreIndex].pChannelConfig))[LucChannel].ucChannelRamIndex;
  #else
  LucCoreIndex = LIN_ZERO;
  /* single core - Channel Ram index = channel id */
  LucChannelRamIndex = LucChannel;
  #endif /* #if (LIN_MULTI_CORE_SUPPORT == STD_ON) */

  /* Get the pointer to channel RAM data */
  LpRamVars = &((Lin_GaaGlobalAccPoint[LucCoreIndex].pChannelRamData)[LucChannelRamIndex]);

  /* Get the address of RLIN3 Channel structure */
  LpLin3ChannelPtr = &((*(Lin_GaaGlobalAccPoint[LucCoreIndex].pRLIN3Properties))[LucChannel]);

  /* Get the RLIN3 Channel Base Address */
  LpLN3ChannelRegs = LpLin3ChannelPtr->pLn3ChanlBaseAddress;

  /* Check for Wakeup Transmit Successfully */
  if (LIN_FRAME_COMPLETE == (uint8)(LpLN3ChannelRegs->ucRLN3nLST & LIN_FRAME_COMPLETE))
  {
    /* Clear the transmit interrupt */
    LpLN3ChannelRegs->ucRLN3nLST = (LpLN3ChannelRegs->ucRLN3nLST & LIN_TRANSMIT_DONE);

    /* Set the channel status */
    LpRamVars->enChannelStatus = LIN_OPERATIONAL;

    #if (LIN_SLAVE_MODE_SUPPORT == STD_ON)
    if (LIN_SLAVE_NODE == (*(Lin_GaaGlobalAccPoint[LucCoreIndex].pChannelConfig))[LucChannel].enNodeType)
    {
      /* Enter the protection area */
      LIN_ENTER_CRITICAL_SECTION(LIN_INTERRUPT_CONTROL_PROTECTION);

      LucReturnValue = Lin_HwSetMasterMode(LucChannel, RLIN3_OPERATION_MODE);

      /* Exit the protection area */
      LIN_EXIT_CRITICAL_SECTION(LIN_INTERRUPT_CONTROL_PROTECTION);

      if (E_OK == LucReturnValue)
      {
        /* SWS_Lin_00272
        The LIN driver shall be able to receive a LIN header at any time in LIN_CH_OPERATIONAL state */
        Lin_HwSlaveStartHeaderReception(LucChannel);
      } /* else No action required */
      else
      {
        #if defined(LIN_E_TIMEOUT) || (LIN_DEV_ERROR_DETECT == STD_ON)
        /* Report Error to DEM or DET */
        (void)Lin_ErrorReport(LIN_WAKEUP_SID);
        #endif /* #if defined(LIN_E_TIMEOUT) || (LIN_DEV_ERROR_DETECT == STD_ON) */
      }
    } /* else No action required */
    #endif /* (LIN_SLAVE_MODE_SUPPORT == STD_ON) */
  }
  else
  {
    /* Reset the LinIf wake-up flag */
    LpRamVars->blWakeupCalled = LIN_FALSE;
  }

  /* Enter the protection area */
  LIN_ENTER_CRITICAL_SECTION(LIN_INTERRUPT_CONTROL_PROTECTION);

  #if (LIN_SLAVE_MODE_SUPPORT == STD_ON)
  if (LIN_MASTER_NODE == (*(Lin_GaaGlobalAccPoint[LucCoreIndex].pChannelConfig))[LucChannel].enNodeType)
  {
    /* Disable RLIN3 Interrupt */
    Lin_HwScheduleInterrupt(LucChannel, LIN_INTERRUPT_DIS);
  } /* else No action required */
  #else
  /* Disable RLIN3 Interrupt */
  Lin_HwScheduleInterrupt(LucChannel, LIN_INTERRUPT_DIS);
  #endif /* (LIN_SLAVE_MODE_SUPPORT == STD_ON) */

  /* Exit the protection area */
  LIN_EXIT_CRITICAL_SECTION(LIN_INTERRUPT_CONTROL_PROTECTION);
}
#define LIN_STOP_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name      : Lin_HwInit
**
** Service ID         : None
**
** Description        : This service initializes all configured RLIN3 channels.
**
** Sync/Async         : Synchronous
**
** Re-entrancy        : Non-Reentrant
**
** Input Parameters   : LucChannel, LucCoreIndex
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return Parameter   : Std_ReturnType
**
** Preconditions      : None
**
** Global Variables   : Lin_GaaGlobalAccPoint
**
** Functions invoked  : Lin_HwSetMasterMode, Lin_HwScheduleInterrupt
**                      Lin_ErrorReport
**
** Registers Used     : ucRLN3nLWBR,
**                      ucRLN3nLBRP0,
**                      ucRLN3nLBRP1,
**                      ucRLN3nLMD,
**                      ucRLN3nLBFC,
**                      ucRLN3nLSC,
**                      ucRLN3nLIE,
**                      ucRLN3nLEDE,
**                      ucRLN3nLDFC,
**                      ucRLN3nLWUP,
**                      ucRLN3nLTRC
**
** Reference ID       : LIN_DUD_ACT_022, LIN_DUD_ACT_022_REG001,
** Reference ID       : LIN_DUD_ACT_022_REG002, LIN_DUD_ACT_022_REG003,
** Reference ID       : LIN_DUD_ACT_022_REG004, LIN_DUD_ACT_022_REG005,
** Reference ID       : LIN_DUD_ACT_022_REG006, LIN_DUD_ACT_022_REG007,
** Reference ID       : LIN_DUD_ACT_022_REG008, LIN_DUD_ACT_022_REG009,
** Reference ID       : LIN_DUD_ACT_022_REG010, LIN_DUD_ACT_022_REG011,
** Reference ID       : LIN_DUD_ACT_022_REG012, LIN_DUD_ACT_022_REG013,
** Reference ID       : LIN_DUD_ACT_022_REG014, LIN_DUD_ACT_022_REG015,
** Reference ID       : LIN_DUD_ACT_022_REG016, LIN_DUD_ACT_022_REG017,
** Reference ID       : LIN_DUD_ACT_022_REG018, LIN_DUD_ACT_022_REG019,
** Reference ID       : LIN_DUD_ACT_022_REG020, LIN_DUD_ACT_022_REG021,
** Reference ID       : LIN_DUD_ACT_022_ERR001, LIN_DUD_ACT_022_ERR002,
** Reference ID       : LIN_DUD_ACT_022_ERR003
***********************************************************************************************************************/
#define LIN_START_SEC_PRIVATE_CODE
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, LIN_PRIVATE_CODE) Lin_HwInit(const uint8 LucChannel, const uint8 LucCoreIndex)
{
  volatile P2CONST(Lin_ChannelInfo, AUTOMATIC, LIN_PRIVATE_CONST) LpLinChannelPtr;
  volatile P2CONST(Lin3_ChannelConfigType, AUTOMATIC, LIN_PRIVATE_CONST) LpLin3ChannelPtr;
  volatile P2VAR(RLin3_UartRegs, AUTOMATIC, REGSPACE) LpLN3ChannelRegs;                                                 /* PRQA S 3432 # JV-01 */
  #if (LIN_INTERRUPT_MUX_SUPPORT == STD_ON)
  volatile P2VAR(uint16, AUTOMATIC, LIN_VAR_FAST_NO_INIT) LpIntMuxAddress;                                              /* PRQA S 3432 # JV-01 */
  #endif

  uint8 LucLWBR;
  #if (LIN_INTERRUPT_MUX_SUPPORT == STD_ON)
  uint8 LucIntMuxShift;
  uint16 LusLn3IntMuxMask;
  #endif

  Std_ReturnType LucReturnValue;

  /* Initialize the return value */
  LucReturnValue = E_NOT_OK;                                                                                            /* PRQA S 2982 # JV-01 */

  /* Get the address of Channel info structure */
  LpLinChannelPtr = &((*(Lin_GaaGlobalAccPoint[LucCoreIndex].pChannelConfig))[LucChannel]);

  /* Get the address of RLIN3 Channel structure */
  LpLin3ChannelPtr = &((*(Lin_GaaGlobalAccPoint[LucCoreIndex].pRLIN3Properties))[LucChannel]);

  /* Get the pointer to RLIN3 Channel Base Address */
  LpLN3ChannelRegs = LpLin3ChannelPtr->pLn3ChanlBaseAddress;

  /* Set RLIN3 to Reset Mode */
  LucReturnValue = Lin_HwSetMasterMode(LucChannel, RLIN3_RESET_MODE);

  /* Set Prescaler Clock Select */
  LucLWBR = (uint8)(LpLin3ChannelPtr->ucPrescalerClk_Select << LIN_ONE);

  /* Set Value for number of samples in 1 Bit time period */
  LucLWBR |= (uint8)(LpLin3ChannelPtr->ucBitSamples << LIN_FOUR);

  if (E_OK == LucReturnValue)
  {
    #if (LIN_SLAVE_MODE_SUPPORT == STD_ON)
    if (LIN_SLAVE_NODE == LpLinChannelPtr->enNodeType)
    {
      /* Set Baud Rate Selector register */
      LpLN3ChannelRegs->ucRLN3nLWBR = LucLWBR;

      /* Set Baud Rate Prescaler0 register */
      LpLN3ChannelRegs->ucRLN3nLBRP0 = LpLin3ChannelPtr->ucBaudRate;

      /* Set Baud Rate Prescaler1 register */
      LpLN3ChannelRegs->ucRLN3nLBRP1 = LpLin3ChannelPtr->ucBaudRate1;

      /* Enable LIN & Disable UART Interrupt Enable Register */
      /* Rx/Tx/Status Interrupt are used */
      LpLN3ChannelRegs->ucRLN3nLMD = RLIN3_INTERRUPT_REG;

      /* [AR22-11] Slave node, Reception Break Detection Width Setting is fixed as default (RLN3nLBFC.LBLT = 0) */
      /* Break Field Configure */
      LpLN3ChannelRegs->ucRLN3nLBFC = LpLinChannelPtr->ucRLINBreakfieldwidth;

      /* Set Inter-byte Header & Response Space width */
      LpLN3ChannelRegs->ucRLN3nLSC = LpLinChannelPtr->ucRLINInterbytespace;
      /* Set RLIN3 Module to LIN Slave mode */
      LpLN3ChannelRegs->ucRLN3nLMD = (LpLN3ChannelRegs->ucRLN3nLMD | LIN_RLIN3_SLAVE_MODE);
      /* Set Interrupt Enable Register */
      LpLN3ChannelRegs->ucRLN3nLIE = LIN_SLAVE_ENABLE_INTERRUPT;
      /* Set Error Detection Enable Register */
      LpLN3ChannelRegs->ucRLN3nLEDE = LIN_SLAVE_ERROR_DETECTION;
    }
    else
    #endif /* #if (LIN_SLAVE_MODE_SUPPORT == STD_ON) */
    {
      #if (LIN_MASTER_MODE_SUPPORT == STD_ON)
      /* Check for LIN protocol specification 1.3 */
      if (LIN_FALSE == LpLin3ChannelPtr->blLinSpec_Select)
      {
        /* Set Baud Rate Selector register for LIN specification 1.3 */
        LpLN3ChannelRegs->ucRLN3nLWBR = LucLWBR & LIN_SET_WAKEUP_BAUDRATE_SPEC_13;
      }
      else
      {
        /* Set Baud Rate Selector register for LIN specification 2.x */
        LpLN3ChannelRegs->ucRLN3nLWBR = LucLWBR | LIN_SET_WAKEUP_BAUDRATE_SPEC_21;
      }

      /* Set Baud Rate Prescaler0 register */
      LpLN3ChannelRegs->ucRLN3nLBRP0 = LpLin3ChannelPtr->ucBaudRate;

      /* Set Baud Rate Prescaler1 register */
      LpLN3ChannelRegs->ucRLN3nLBRP1 = LIN_RESET_VALUE;

      /* Enable LIN & Disable UART Interrupt Enable Register */
      /* Rx/Tx/Status Interrupt are used */
      LpLN3ChannelRegs->ucRLN3nLMD = RLIN3_INTERRUPT_REG;

      /* Set System Clock */
      LpLN3ChannelRegs->ucRLN3nLMD = (LpLN3ChannelRegs->ucRLN3nLMD | LpLinChannelPtr->ucModReg);                        /* PRQA S 0404 # JV-01 */
      /* Break Field Configure */
      LpLN3ChannelRegs->ucRLN3nLBFC = LpLinChannelPtr->ucRLINBreakfieldwidth;

      /* Set Inter-byte Header & Response Space width */
      LpLN3ChannelRegs->ucRLN3nLSC = LpLinChannelPtr->ucRLINInterbytespace;

      /* Set RLIN3 Module to LIN Master mode */
      LpLN3ChannelRegs->ucRLN3nLMD = (LpLN3ChannelRegs->ucRLN3nLMD & RLIN3_MASTER_MODE);

      /* Set Interrupt Enable Register */
      LpLN3ChannelRegs->ucRLN3nLIE = LIN_MASTER_ENABLE_INTERRUPT;

      /* Set Error Detection Enable Register */
      LpLN3ChannelRegs->ucRLN3nLEDE = LIN_MASTER_ERROR_DETECTION;

      /* Set LIN for Frame Mode */
      LpLN3ChannelRegs->ucRLN3nLDFC = (LpLN3ChannelRegs->ucRLN3nLDFC & LIN_FRAME_MODE);
      #endif /* #if (LIN_MASTER_MODE_SUPPORT == STD_ON) */
    }

    #if (LIN_INTERRUPT_MUX_SUPPORT == STD_ON)
    if (NULL_PTR != LpLin3ChannelPtr->pLin3IntMuxAddress)
    {
      /* Get the address of Interrupt Select register */
      LpIntMuxAddress = LpLin3ChannelPtr->pLin3IntMuxAddress;

      /* Calculate position of MUXn in Interrupt Select register */
      LucIntMuxShift = LpLin3ChannelPtr->ucLin3IntMuxNumber * LIN_FIVE;

      /* Set the mask before writing value to Interrupt Select register */
      LusLn3IntMuxMask = (uint16)(LIN_INTSEL_MUX_MASK << LucIntMuxShift);                                               /* PRQA S 4391 # JV-01 */

      /* Set Interrupt Select register for LIN channel*/
      *(LpIntMuxAddress) = (uint16)(*(LpIntMuxAddress) & (~LusLn3IntMuxMask)) |                                         /* PRQA S 0404 # JV-01 */
        (uint16)(LpLin3ChannelPtr->ucLin3IntMuxValue << LucIntMuxShift);                                                /* PRQA S 4391 # JV-01 */
    } /* else No action required */
    #endif /* #if (LIN_INTERRUPT_MUX_SUPPORT == STD_ON) */

    #if (LIN_AR_VERSION == LIN_AR_422_VERSION)
    /* Set RLIN3 to Operational Mode */
    LucReturnValue = Lin_HwSetMasterMode(LucChannel, RLIN3_OPERATION_MODE);

    if (E_NOT_OK == LucReturnValue)
    {
      #if defined(LIN_E_TIMEOUT) || (LIN_DEV_ERROR_DETECT == STD_ON)
      /* Report Error to DEM or DET */
      LucReturnValue = Lin_ErrorReport(LIN_INIT_SID);
      #endif /* #if defined(LIN_E_TIMEOUT) || (LIN_DEV_ERROR_DETECT == STD_ON) */
    }

    /* Disable RLIN3 Interrupt */
    Lin_HwScheduleInterrupt(LucChannel, LIN_INTERRUPT_DIS);

    #elif ((LIN_AR_VERSION == LIN_AR_431_VERSION) || (LIN_AR_VERSION == LIN_AR_R22_11_VERSION))
    /* SWS_Lin_00171: enable the wake-up detection (if enabled by LinChannelWakeupSupport) */
    /* Check if global wake-up support is enabled */
    #if (LIN_WAKEUP_SUPPORT == STD_ON)

    /* Check if channel specific wake-up support is enabled */
    if (LIN_TRUE == LpLinChannelPtr->blWakeupSupport)
    {
      /* Set RLIN3 Wake-up Low width */
      LpLN3ChannelRegs->ucRLN3nLWUP = LIN_LOW_WIDTH;

      /* Set the Direction of RLIN3 as Reception */
      LpLN3ChannelRegs->ucRLN3nLDFC = (LpLN3ChannelRegs->ucRLN3nLDFC & LIN_SLAVE_DIRECTION);

      /* Set RLIN3 to Wake-up Mode */
      LucReturnValue = Lin_HwSetMasterMode(LucChannel, RLIN3_WAKEUP_MODE);

      if (E_NOT_OK == LucReturnValue)
      {
        #if defined(LIN_E_TIMEOUT) || (LIN_DEV_ERROR_DETECT == STD_ON)
        /* Report Error to DEM or DET */
        LucReturnValue = Lin_ErrorReport(LIN_INIT_SID);
        #endif /* #if defined(LIN_E_TIMEOUT) || (LIN_DEV_ERROR_DETECT == STD_ON) */
      }

      if (E_OK == LucReturnValue)
      {
        /* Enable RLIN3 Interrupt */
        Lin_HwScheduleInterrupt(LucChannel, LIN_INTERRUPT_EN);

        /* Initiate wake-up reception */
        LpLN3ChannelRegs->ucRLN3nLTRC = (LpLN3ChannelRegs->ucRLN3nLTRC | LIN_START_TRANSMIT);
      }
    }
    else
    #endif /* #if (LIN_WAKEUP_SUPPORT == STD_ON) */
    {
      /* Disable RLIN3 Interrupt */
      Lin_HwScheduleInterrupt(LucChannel, LIN_INTERRUPT_DIS);

      /* Update the return value */
      LucReturnValue = E_OK;
    }
    #endif /* #if (LIN_AR_VERSION == LIN_AR_422_VERSION) */
  }
  else
  {
    #if defined(LIN_E_TIMEOUT) || (LIN_DEV_ERROR_DETECT == STD_ON)
    /* Report Error to DEM or DET */
    LucReturnValue = Lin_ErrorReport(LIN_INIT_SID);
    #endif /* #if defined(LIN_E_TIMEOUT) || (LIN_DEV_ERROR_DETECT == STD_ON) */
  }

  return (LucReturnValue);
}
#define LIN_STOP_SEC_PRIVATE_CODE
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name      : Lin_HwSetMasterMode
**
** Service ID         : NA
**
** Description        : This service sets RLIN3 to the corresponding
**                      Master Mode.
**                      It initiates a transition to the requested Master Mode.
**
** Sync/Async         : Synchronous
**
** Re-entrancy        : Non Re-entrant for the same channel
**
** Input Parameters   : LucChannel, LenModeType
**
** Output Parameters  : None
**
** Return parameter   : Std_ReturnType
**
** Preconditions      : None
**
** Global Variables   : Lin_GaaGlobalAccPoint,
**                      Lin_GaaChannelId2CoreIndex (LIN_MULTI_CORE_SUPPORT == STD_ON)
**
** Functions invoked  : Lin_HwScheduleInterrupt
**
** Registers Used     : ucRLN3nLCUC, ucRLN3nLEST
**                      ucRLN3nLMST, pLin3IntTxEicReg,
**                      pLin3IntRxEicReg,
**                      pLin3IntStEicReg
**
** Reference ID       : LIN_DUD_ACT_023,
** Reference ID       : LIN_DUD_ACT_023_REG001, LIN_DUD_ACT_023_REG002,
** Reference ID       : LIN_DUD_ACT_023_REG003, LIN_DUD_ACT_023_REG004,
** Reference ID       : LIN_DUD_ACT_023_REG005, LIN_DUD_ACT_023_REG006,
** Reference ID       : LIN_DUD_ACT_023_REG007
***********************************************************************************************************************/
#define LIN_START_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, LIN_CODE_FAST)
Lin_HwSetMasterMode(const uint8 LucChannel, const Lin_ModeType LenModeType)                                             /* PRQA S 3006 # JV-01 */
{
  volatile P2CONST(Lin3_ChannelConfigType, AUTOMATIC, LIN_CONST) LpLin3ChannelPtr;
  volatile P2VAR(RLin3_UartRegs, AUTOMATIC, REGSPACE) LpLN3ChannelRegs;                                                 /* PRQA S 3432 # JV-01 */

  Std_ReturnType LucReturnValue;
  boolean LblIntEnabling;
  volatile uint32 LulTimeoutCounter;
  uint8 LucCoreIndex;

  #if (LIN_MULTI_CORE_SUPPORT == STD_ON)
  /* Isr - LucChannel is channel id, need to convert to chanel index */
  LucCoreIndex = Lin_GaaChannelId2CoreIndex[LucChannel];
  #else
  LucCoreIndex = LIN_ZERO;
  #endif /* #if (LIN_MULTI_CORE_SUPPORT == STD_ON) */

  /* Initialize the return value */
  LucReturnValue = E_NOT_OK;                                                                                            /* PRQA S 2982 # JV-01 */

  /* Get the address of RLIN3 Channel structure */
  LpLin3ChannelPtr = &((*(Lin_GaaGlobalAccPoint[LucCoreIndex].pRLIN3Properties))[LucChannel]);

  /* Get the pointer to RLIN3 Channel Base Address */
  LpLN3ChannelRegs = LpLin3ChannelPtr->pLn3ChanlBaseAddress;

  /* Set max value of loop counter */
  LulTimeoutCounter = (uint16)LIN_TIMEOUT_DURATION;
  /*  Check if Interrupt processing is disabled */
  if (LIN_EIC_EIMK_MASK == ((*(volatile uint8 *)LpLin3ChannelPtr->pLin3IntTxEicReg) & LIN_EIC_EIMK_MASK))               /* PRQA S 0404, 0751 # JV-01, JV-01 */
  {
    /* Flag to know that interrupt is not enabled before */
    LblIntEnabling = LIN_FALSE;
  }
  else
  {
    /* Temporary disable interrupt */
    Lin_HwScheduleInterrupt(LucChannel, LIN_INTERRUPT_DIS);
    /* Flag to know that interrupt is enabled before */
    LblIntEnabling = LIN_TRUE;
  }
  /* Change RLIN3 to the specified LucMode mode */
  switch (LenModeType)
  {
  case RLIN3_RESET_MODE:
    /* Set RLIN3 to Reset Mode */
    LpLN3ChannelRegs->ucRLN3nLCUC = LIN_RESET_VALUE;

    if ((uint16)LIN_ZERO == LulTimeoutCounter)                                                                          /* PRQA S 3416 # JV-01 */
    {
      if (LIN_RESET_VALUE == (uint8)(LpLN3ChannelRegs->ucRLN3nLMST & LIN_SET_VALUE))
      {
        LulTimeoutCounter = (uint16)LIN_ONE;
      } /* else No action required */
    }
    else
    {
      /* After writing to bit[0], further write access to this register is not allowed until bit LMST[0] is 0 */
      while ((LIN_SET_VALUE ==
              (uint8)(LpLN3ChannelRegs->ucRLN3nLMST & LIN_SET_VALUE)) && ((uint16)LIN_ZERO < LulTimeoutCounter))        /* PRQA S 3415, 3416 # JV-01, JV-01 */
      {
        LulTimeoutCounter--;                                                                                            /* PRQA S 3384, 3387 # JV-01, JV-01 */
      }
    }
    break;
  case RLIN3_OPERATION_MODE:
    /* Set RLIN3 to Normal Mode*/
    LpLN3ChannelRegs->ucRLN3nLCUC = LIN_SET_OPERATION_MODE;

    if ((uint16)LIN_ZERO == LulTimeoutCounter)                                                                          /* PRQA S 3416 # JV-01 */
    {
      if (LIN_SET_OPERATION_MODE == (uint8)(LpLN3ChannelRegs->ucRLN3nLMST & LIN_SET_OPERATION_MODE))
      {
        LulTimeoutCounter = (uint16)LIN_ONE;
      } /* else No action required */
    }
    else
    {
      /* After writing to bit[0], further write access to this register is not allowed until bit LMST[0] is 0 */
      while ((LIN_SET_OPERATION_MODE !=
              (uint8)(LpLN3ChannelRegs->ucRLN3nLMST & LIN_SET_OPERATION_MODE)) &&
             ((uint16)LIN_ZERO < LulTimeoutCounter))                                                                    /* PRQA S 3415, 3416 # JV-01, JV-01 */
      {
        LulTimeoutCounter--;                                                                                            /* PRQA S 3384, 3387 # JV-01, JV-01 */
      }
    }
    break;
  case RLIN3_WAKEUP_MODE:
    /* Set RLIN3 to Wake-up Mode*/
    LpLN3ChannelRegs->ucRLN3nLCUC = LIN_SET_VALUE;

    if ((uint16)LIN_ZERO == LulTimeoutCounter)                                                                          /* PRQA S 3416 # JV-01 */
    {
      if (LIN_SET_VALUE == (uint8)(LpLN3ChannelRegs->ucRLN3nLMST & LIN_SET_OPERATION_MODE))
      {
        LulTimeoutCounter = (uint16)LIN_ONE;
      } /* else No action required */
    }
    else
    {
      /* After writing 1 to bit[0], further write access to this register
         is not allowed until bit LMST[0] is 1 and bit LMST[1] is 0*/
      while ((LIN_SET_VALUE !=
              (uint8)(LpLN3ChannelRegs->ucRLN3nLMST & LIN_SET_OPERATION_MODE)) &&
             ((uint16)LIN_ZERO < LulTimeoutCounter))                                                                    /* PRQA S 3415, 3416 # JV-01, JV-01 */
      {
        LulTimeoutCounter--;                                                                                            /* PRQA S 3384, 3387 # JV-01, JV-01 */
      }
    }
    break;
  default:
    /* No action required */
    break;
  }

  #if defined(LIN_E_TIMEOUT) || (LIN_DEV_ERROR_DETECT == STD_ON)
  if ((uint16)LIN_ZERO == LulTimeoutCounter)                                                                            /* PRQA S 3416 # JV-01 */
  {
    /* Return value is E_NOT_OK to report Error to DEM or DET */
    LucReturnValue = E_NOT_OK;
  }
  else
  #endif /* LIN_E_TIMEOUT || (LIN_DEV_ERROR_DETECT == STD_ON) */
  {
    LucReturnValue = E_OK;
  }

  /*  Clear Timeout error flag */
  LpLN3ChannelRegs->ucRLN3nLEST = (LpLN3ChannelRegs->ucRLN3nLEST & LIN_TIMEOUT_CLEAR);

  /*  Clear pending interrupt */
  RH850_SV_MODE_ICR_AND(16, LpLin3ChannelPtr->pLin3IntTxEicReg, LIN_EIC_PENDING_CLEAR);                                 /* PRQA S 0404, 3464 # JV-01, JV-01 */
  RH850_SV_MODE_ICR_AND(16, LpLin3ChannelPtr->pLin3IntRxEicReg, LIN_EIC_PENDING_CLEAR);                                 /* PRQA S 0404, 3464 # JV-01, JV-01 */
  RH850_SV_MODE_ICR_AND(16, LpLin3ChannelPtr->pLin3IntStEicReg, LIN_EIC_PENDING_CLEAR);                                 /* PRQA S 0404, 3464 # JV-01, JV-01 */
  /* Dummy read */
  RH850_SV_MODE_REG_READ_ONLY(16, LpLin3ChannelPtr->pLin3IntStEicReg);                                                  /* PRQA S 0404 # JV-01 */
  /* SYNCP execution */
  EXECUTE_SYNCP();                                                                                                      /* PRQA S 1006 # JV-01 */

  /*  Check if Interrupt processing is disabled  */
  if (LIN_TRUE == LblIntEnabling)
  {
    /* Re-enable interrupt processing */
    Lin_HwScheduleInterrupt(LucChannel, LIN_INTERRUPT_EN);
  } /* else No action required */

  return (LucReturnValue);
}
#define LIN_STOP_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name      : Lin_HwScheduleInterrupt
**
** Service ID         : None
**
** Description        : This service enables or disables the interrupts
**                      (transmission, reception and error status) of the
**                      requested RLIN3 channel, using the EIMK bit of the
**                      EIC register.
**
** Sync/Async         : Synchronous
**
** Re-entrancy        : Non-Reentrant for the same channel
**
** Input Parameters   : LucChannel, LenInterruptScheduleType
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return Parameter   : None
**
** Preconditions      : None
**
** Global Variables   : Lin_GaaGlobalAccPoint,
**                      Lin_GaaChannelId2CoreIndex (LIN_MULTI_CORE_SUPPORT == STD_ON)
**
** Functions invoked  : None
**
** Registers Used     : pLin3IntTxEicReg,
**                      pLin3IntRxEicReg,
*                       pLin3IntStEicReg
**
** Reference ID       : LIN_DUD_ACT_024, LIN_DUD_ACT_024_REG001,
** Reference ID       : LIN_DUD_ACT_024_REG002, LIN_DUD_ACT_024_REG003,
** Reference ID       : LIN_DUD_ACT_024_REG004, LIN_DUD_ACT_024_REG005,
** Reference ID       : LIN_DUD_ACT_024_REG006
***********************************************************************************************************************/
#define LIN_START_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(void, LIN_CODE_FAST)
Lin_HwScheduleInterrupt(const uint8 LucChannel, const Lin_InterruptScheduleType LenInterruptScheduleType)               /* PRQA S 3006 # JV-01 */
{
  volatile P2CONST(Lin3_ChannelConfigType, AUTOMATIC, LIN_CONST) LpLin3ChannelPtr;
  uint8 LucCoreIndex;

  #if (LIN_MULTI_CORE_SUPPORT == STD_ON)
  /* Isr - LucChannel is channel id, need to convert to chanel index */
  LucCoreIndex = Lin_GaaChannelId2CoreIndex[LucChannel];
  #else
  LucCoreIndex = LIN_ZERO;
  #endif /* #if (LIN_MULTI_CORE_SUPPORT == STD_ON) */

  /* Get the address of RLIN3 Channel structure */
  LpLin3ChannelPtr = &((*(Lin_GaaGlobalAccPoint[LucCoreIndex].pRLIN3Properties))[LucChannel]);

  switch (LenInterruptScheduleType)
  {
  /* Disable RLIN3 Tx/Rx/St Interrupts */
  case LIN_INTERRUPT_DIS:
    /* Disable Interrupts, set the EIMKn bit of the EICn register */
    RH850_SV_MODE_ICR_OR(8, LpLin3ChannelPtr->pLin3IntTxEicReg, LIN_EIC_EIMK_MASK);                                     /* PRQA S 0751, 0404, 3464 # JV-01, JV-01, JV-01 */
    RH850_SV_MODE_ICR_OR(8, LpLin3ChannelPtr->pLin3IntRxEicReg, LIN_EIC_EIMK_MASK);                                     /* PRQA S 0404, 0751, 3464 # JV-01, JV-01, JV-01 */
    RH850_SV_MODE_ICR_OR(8, LpLin3ChannelPtr->pLin3IntStEicReg, LIN_EIC_EIMK_MASK);                                     /* PRQA S 0751, 0404, 3464 # JV-01, JV-01, JV-01 */
    /* Dummy read */
    RH850_SV_MODE_REG_READ_ONLY(8, LpLin3ChannelPtr->pLin3IntStEicReg);                                                 /* PRQA S 0404, 0751 # JV-01, JV-01 */
    /* SYNCP execution */
    EXECUTE_SYNCP();                                                                                                    /* PRQA S 1006 # JV-01 */
    break;
  /* Enable RLIN3 Tx/Rx/St Interrupts */
  case LIN_INTERRUPT_EN:
    /* Enable Interrupts, clear the EIMKn bit of the EICn register and clear pending interrupts */
    RH850_SV_MODE_ICR_AND(8, LpLin3ChannelPtr->pLin3IntTxEicReg, LIN_EIC_EIMK_MASK_CLEAR);                              /* PRQA S 0404, 3464, 0751 # JV-01, JV-01, JV-01 */
    RH850_SV_MODE_ICR_AND(8, LpLin3ChannelPtr->pLin3IntRxEicReg, LIN_EIC_EIMK_MASK_CLEAR);                              /* PRQA S 0404, 3464, 0751 # JV-01, JV-01, JV-01 */
    RH850_SV_MODE_ICR_AND(8, LpLin3ChannelPtr->pLin3IntStEicReg, LIN_EIC_EIMK_MASK_CLEAR);                              /* PRQA S 0404, 3464, 0751 # JV-01, JV-01, JV-01 */
    /* Dummy read */
    RH850_SV_MODE_REG_READ_ONLY(8, LpLin3ChannelPtr->pLin3IntStEicReg);                                                 /* PRQA S 0404, 0751 # JV-01, JV-01 */
    /* SYNCP execution */
    EXECUTE_SYNCP();                                                                                                    /* PRQA S 1006 # JV-01 */
    break;
  default:
    /* No action required */
    break;
  }
}
#define LIN_STOP_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name      : Lin_HwHandleWakeupRequest
**
** Service ID         : NA
**
** Sync/Async         : Synchronous
**
** Description        : This service enables a wake-up detection from the
**                      LIN bus or issues a wake-up command to the LIN bus
**                      according to the wake-up requested.
**
** Re-entrancy        : Non Re-entrant for the same channel
**
** Input Parameters   : LucChannel, LenWakeupType, LucApiId
**
** Output Parameters  : None
**
** Return parameter   : Std_ReturnType
**
** Preconditions      : None
**
** Global Variables   : Lin_GaaGlobalAccPoint,
**                      Lin_GaaChannelId2CoreIndex (LIN_MULTI_CORE_SUPPORT == STD_ON)
**
** Functions invoked  : Lin_HwSetMasterMode, Lin_HwScheduleInterrupt
**                      LIN_ENTER_CRITICAL_SECTION, LIN_EXIT_CRITICAL_SECTION,
**                      Lin_ErrorReport
**
** Registers Used     : ucRLN3nLWUP,
**                      ucRLN3nLDFC,
**                      ucRLN3nLTRC
**
** Reference ID       : LIN_DUD_ACT_025, LIN_DUD_ACT_025_REG001,
** Reference ID       : LIN_DUD_ACT_025_REG002, LIN_DUD_ACT_025_REG003,
** Reference ID       : LIN_DUD_ACT_025_REG004, LIN_DUD_ACT_025_ERR001,
** Reference ID       : LIN_DUD_ACT_025_CRT001, LIN_DUD_ACT_025_CRT002,
** Reference ID       : LIN_DUD_ACT_025_CRT003, LIN_DUD_ACT_025_CRT004,
***********************************************************************************************************************/
#define LIN_START_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, LIN_CODE_FAST)
Lin_HwHandleWakeupRequest(const uint8 LucChannel, const Lin_WakeupType LenWakeupType, const uint8 LucApiId)
{
  volatile P2CONST(Lin3_ChannelConfigType, AUTOMATIC, LIN_CONST) LpLin3ChannelPtr;
  volatile P2VAR(RLin3_UartRegs, AUTOMATIC, REGSPACE) LpLN3ChannelRegs;                                                 /* PRQA S 3432 # JV-01 */
  uint8 LucCoreIndex;
  Std_ReturnType LucReturnValue;

  /* Initialize the return value */
  LucReturnValue = E_NOT_OK;                                                                                            /* PRQA S 2982 # JV-01 */

  #if (LIN_MULTI_CORE_SUPPORT == STD_ON)
  /* Isr - LucChannel is channel id, need to convert to chanel index */
  LucCoreIndex = Lin_GaaChannelId2CoreIndex[LucChannel];
  #else
  LucCoreIndex = LIN_ZERO;
  #endif /* #if (LIN_MULTI_CORE_SUPPORT == STD_ON) */

  /* Get the address of RLIN3 Channel structure */
  LpLin3ChannelPtr = &((*(Lin_GaaGlobalAccPoint[LucCoreIndex].pRLIN3Properties))[LucChannel]);

  /* Get the pointer to RLIN3 Channel Base Address */
  LpLN3ChannelRegs = LpLin3ChannelPtr->pLn3ChanlBaseAddress;

  /* Enter the protection area */
  LIN_ENTER_CRITICAL_SECTION(LIN_INTERRUPT_CONTROL_PROTECTION);

  /* Set RLIN3 to Reset Mode */
  LucReturnValue = Lin_HwSetMasterMode(LucChannel, RLIN3_RESET_MODE);

  if (E_OK == LucReturnValue)
  {

    /* Set RLIN3 Wake-up Low width */
    LpLN3ChannelRegs->ucRLN3nLWUP = LIN_LOW_WIDTH;

    switch (LenWakeupType)
    {
    case LIN_SLAVE_ISSUE:
      /* Set the Direction of RLIN3 as Reception */
      LpLN3ChannelRegs->ucRLN3nLDFC = (LpLN3ChannelRegs->ucRLN3nLDFC & LIN_SLAVE_DIRECTION);
      break;
    case LIN_MASTER_ISSUE:
      /* Set the Direction of RLIN3 as Transmit */
      LpLN3ChannelRegs->ucRLN3nLDFC = (LpLN3ChannelRegs->ucRLN3nLDFC | LIN_MASTER_DIRECTION);
      break;
    default:
      /* No action required */
      break;
    }

    /* Set RLIN3 to Wake-up Mode */
    LucReturnValue = Lin_HwSetMasterMode(LucChannel, RLIN3_WAKEUP_MODE);
  }

  /* Exit the protection area */
  LIN_EXIT_CRITICAL_SECTION(LIN_INTERRUPT_CONTROL_PROTECTION);

  if (E_OK == LucReturnValue)
  {
    /* Enter the protection area */
    LIN_ENTER_CRITICAL_SECTION(LIN_INTERRUPT_CONTROL_PROTECTION);

    /* Enable RLIN3 Interrupt */
    Lin_HwScheduleInterrupt(LucChannel, LIN_INTERRUPT_EN);

    /* Initiate Communication */
    LpLN3ChannelRegs->ucRLN3nLTRC = (LpLN3ChannelRegs->ucRLN3nLTRC | LIN_START_TRANSMIT);

    /* Exit the protection area */
    LIN_EXIT_CRITICAL_SECTION(LIN_INTERRUPT_CONTROL_PROTECTION);
  } /* else No action required */
  else
  {
    #if defined(LIN_E_TIMEOUT) || (LIN_DEV_ERROR_DETECT == STD_ON)
    /* Report Error to DEM or DET */
    LucReturnValue = Lin_ErrorReport(LucApiId);
    #endif /* #if defined(LIN_E_TIMEOUT) || (LIN_DEV_ERROR_DETECT == STD_ON) */
  }
  return (LucReturnValue);
}
#define LIN_STOP_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name      : Lin_ErrorReport
**
** Service ID         : NA
**
** Sync/Async         : Synchronous
**
** Description        : This service reports an error to DEM or DET if a
**                      loop-processing-time-out error occurs
**
** Re-entrancy        : Re-entrant
**
** Input Parameters   : LucApiId
**
** Output Parameters  : None
**
** Return parameter   : Std_ReturnType
**
** Preconditions      : None
**
** Global Variables   : None
**
** Functions invoked  : Det_ReportError, LIN_DEM_REPORT_ERROR
**
** Registers Used     : None
**
** Reference ID       : LIN_DUD_ACT_026, LIN_DUD_ACT_026_ERR001,
** Reference ID       : LIN_DUD_ACT_026_ERR002, LIN_DUD_ACT_026_ERR003
***********************************************************************************************************************/
#define LIN_START_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#if defined(LIN_E_TIMEOUT) || (LIN_DEV_ERROR_DETECT == STD_ON)
FUNC(Std_ReturnType, LIN_CODE_FAST) Lin_ErrorReport(const uint8 LucApiId)                                               /* PRQA S 3206 # JV-01 */
{
  Std_ReturnType LucReturnValue;

  /* Initialize the return value */
  LucReturnValue = E_OK;                                                                                                /* PRQA S 2982 # JV-01 */

  #ifdef LIN_E_TIMEOUT
    /* Report Error to DEM */
    LIN_DEM_REPORT_ERROR(LIN_E_TIMEOUT, DEM_EVENT_STATUS_FAILED);
    LucReturnValue = E_NOT_OK;
  #else
  #if (LIN_DEV_ERROR_DETECT == STD_ON)
    /* Report to DET */
    (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LucApiId, LIN_E_DET_TIMEOUT);
    LucReturnValue = E_NOT_OK;
  #endif /* (LIN_DEV_ERROR_DETECT == STD_ON) */
  #endif /* LIN_E_TIMEOUT */

  return (LucReturnValue);
}
#endif /* LIN_E_TIMEOUT || (LIN_DEV_ERROR_DETECT == STD_ON) */
#define LIN_STOP_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name      : Lin_SetStatus
**
** Service ID         : None
**
** Description        : This function updates the status of Lin_GblDriverState.
**                      The purpose of this function is to prevent the order of
**                      instructions being changed by the compiler.
**
** Sync/Async         : Synchronous
**
** Re-entrancy        : Non-Reentrant
**
** Input Parameters   : LblStatus, LucCoreIndex
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return Parameter   : None
**
** Preconditions      : None
**
** Global Variables   : Lin_GaaGlobalAccPoint
**
** Functions invoked  : None
**
** Registers Used     : None
**
** Reference ID       : LIN_DUD_ACT_027, LIN_DUD_ACT_027_GBL001
***********************************************************************************************************************/
#define LIN_START_SEC_PRIVATE_CODE
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(void, LIN_PRIVATE_CODE) Lin_SetStatus(const boolean LblStatus, const uint8 LucCoreIndex)
{
  /* Set Lin_GblDriverState to LblStatus */
  *(Lin_GaaGlobalAccPoint[LucCoreIndex].pDriverState) = LblStatus;
}
#define LIN_STOP_SEC_PRIVATE_CODE
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name      : Lin_HwSlaveStartHeaderReception
**
** Service ID         : NA
**
** Description        : This service start header reception for slave channel
**
** Sync/Async         : Synchronous
**
** Re-entrancy        : Non Re-entrant for the same channel
**
** Input Parameters   : LucChannel
**
** Output Parameters  : None
**
** Return parameter   : None
**
** Preconditions      : None
**
** Global Variables   : Lin_GaaGlobalAccPoint,
**                      Lin_GaaChannelId2CoreIndex (LIN_MULTI_CORE_SUPPORT == STD_ON)
**
** Functions invoked  : Lin_HwScheduleInterrupt, LIN_ENTER_CRITICAL_SECTION, LIN_EXIT_CRITICAL_SECTION
**
** Registers Used     : ucRLN3nLTRC, ucRLN3nLDFC
**
** Reference ID       : LIN_DUD_ACT_028, LIN_DUD_ACT_028_GBL001,
** Reference ID       : LIN_DUD_ACT_028_GBL002, LIN_DUD_ACT_028_GBL003,
** Reference ID       : LIN_DUD_ACT_028_REG001, LIN_DUD_ACT_028_REG002,
** Reference ID       : LIN_DUD_ACT_028_CRT001, LIN_DUD_ACT_028_CRT002
***********************************************************************************************************************/
#if (LIN_SLAVE_MODE_SUPPORT == STD_ON)
#define LIN_START_SEC_PRIVATE_CODE
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(void, LIN_PRIVATE_CODE) Lin_HwSlaveStartHeaderReception(const uint8 LucChannel)
{
  volatile P2CONST(Lin3_ChannelConfigType, AUTOMATIC, LIN_PRIVATE_CONST) LpLin3ChannelPtr;
  volatile P2VAR(RLin3_UartRegs, AUTOMATIC, REGSPACE)LpLN3ChannelRegs;                                                  /* PRQA S 3432 # JV-01 */
  uint8 LucCoreIndex;

  #if (LIN_MULTI_CORE_SUPPORT == STD_ON)
  /* Isr - LucChannel is channel id, need to convert to chanel index */
  LucCoreIndex = Lin_GaaChannelId2CoreIndex[LucChannel];
  #else
  LucCoreIndex = LIN_ZERO;
  #endif /* #if (LIN_MULTI_CORE_SUPPORT == STD_ON) */

  LpLin3ChannelPtr = &((*(Lin_GaaGlobalAccPoint[LucCoreIndex].pRLIN3Properties))[LucChannel]);

  /* Get the RLIN3 Channel Base Address */
  LpLN3ChannelRegs = LpLin3ChannelPtr->pLn3ChanlBaseAddress;

  /* Set the Direction of RLIN3 as Reception */
  LpLN3ChannelRegs->ucRLN3nLDFC = (LpLN3ChannelRegs->ucRLN3nLDFC & LIN_SLAVE_DIRECTION);

  /* Enter the protection area */
  LIN_ENTER_CRITICAL_SECTION(LIN_INTERRUPT_CONTROL_PROTECTION);

  /* Enable RLIN3 Interrupt */
  Lin_HwScheduleInterrupt(LucChannel, LIN_INTERRUPT_EN);

  /* Initiate Communication */
  LpLN3ChannelRegs->ucRLN3nLTRC = (LpLN3ChannelRegs->ucRLN3nLTRC | LIN_START_TRANSMIT);

  /* Exit the protection area */
  LIN_EXIT_CRITICAL_SECTION(LIN_INTERRUPT_CONTROL_PROTECTION);
}
#define LIN_STOP_SEC_PRIVATE_CODE
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* #if (LIN_SLAVE_MODE_SUPPORT == STD_ON) */

/***********************************************************************************************************************
** Function Name      : Lin_HwSlaveProcessData
**
** Service ID         : NA
**
** Description        : This service processes the transmit and receive
**                      interrupt requests
**
** Sync/Async         : Synchronous
**
** Re-entrancy        : Non Re-entrant for the same channel
**
** Input Parameters   : LucChannel
**
** Output Parameters  : None
**
** Return parameter   : None
**
** Preconditions      : None
**
** Global Variables   : Lin_GaaGlobalAccPoint,
**                      Lin_GaaChannelId2CoreIndex (LIN_MULTI_CORE_SUPPORT == STD_ON)
**
** Functions invoked  : LinIf_HeaderIndication, Lin_HwLoadTxBuffer,
**                      LinIf_RxIndication, LinIf_TxConfirmation,
**                      LIN_ENTER_CRITICAL_SECTION, LIN_EXIT_CRITICAL_SECTION
**
** Registers Used     : ucRLN3nLST, ucRLN3nLDBR, ucRLN3nLIDB, ucRLN3nLDFC, ucRLN3nLTRC
**
** Reference ID       : LIN_DUD_ACT_029, LIN_DUD_ACT_029_GBL001,
** Reference ID       : LIN_DUD_ACT_029_GBL002, LIN_DUD_ACT_029_GBL003,
** Reference ID       : LIN_DUD_ACT_029_GBL004, LIN_DUD_ACT_029_REG001,
** Reference ID       : LIN_DUD_ACT_029_REG002, LIN_DUD_ACT_029_REG003,
** Reference ID       : LIN_DUD_ACT_029_REG004, LIN_DUD_ACT_029_REG005,
** Reference ID       : LIN_DUD_ACT_029_REG006, LIN_DUD_ACT_029_REG007,
** Reference ID       : LIN_DUD_ACT_029_REG008, LIN_DUD_ACT_029_REG009,
** Reference ID       : LIN_DUD_ACT_029_REG010, LIN_DUD_ACT_029_REG011,
** Reference ID       : LIN_DUD_ACT_029_GBL005, LIN_DUD_ACT_029_GBL006,
** Reference ID       : LIN_DUD_ACT_029_CRT001, LIN_DUD_ACT_029_CRT002,
***********************************************************************************************************************/
#if (LIN_SLAVE_MODE_SUPPORT == STD_ON)
#define LIN_START_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
STATIC FUNC(void, LIN_CODE_FAST) Lin_HwSlaveProcessData(const uint8 LucChannel)
{
  volatile P2CONST(Lin3_ChannelConfigType, AUTOMATIC, LIN_CONST) LpLin3ChannelPtr;
  volatile P2VAR(RLin3_UartRegs, AUTOMATIC, REGSPACE) LpLN3ChannelRegs;                                                 /* PRQA S 3432 # JV-01 */
  volatile P2VAR(Lin_RamData, AUTOMATIC, LIN_APPL_DATA) LpRamVars;                                                      /* PRQA S 3432 # JV-01 */

  Lin_PduType LddPduInfo;
  Std_ReturnType LucReturnValue;

  Lin_FrameResponseType LenFrameType;
  uint8 LucIndex;
  uint8 LucDataLength;
  uint8 LucChannelRamIndex;
  uint8 LucCoreIndex;

  #if (LIN_MULTI_CORE_SUPPORT == STD_ON)
  /* LucChannel is channel id, need to convert to chanel index */
  LucCoreIndex = Lin_GaaChannelId2CoreIndex[LucChannel];
  /* Get Channel Ram Index for each core */
  LucChannelRamIndex = (*(Lin_GaaGlobalAccPoint[LucCoreIndex].pChannelConfig))[LucChannel].ucChannelRamIndex;
  #else
  LucCoreIndex = LIN_ZERO;
  /* single core - Channel Ram index = channel id */
  LucChannelRamIndex = LucChannel;
  #endif /* #if (LIN_MULTI_CORE_SUPPORT == STD_ON) */

  /* Get the address of LIN Channel structure */
  LpRamVars = &((Lin_GaaGlobalAccPoint[LucCoreIndex].pChannelRamData)[LucChannelRamIndex]);

  /* Get the channel index */
  LpLin3ChannelPtr = &((*(Lin_GaaGlobalAccPoint[LucCoreIndex].pRLIN3Properties))[LucChannel]);

  /* Get the RLIN3 Channel Base Address */
  LpLN3ChannelRegs = LpLin3ChannelPtr->pLn3ChanlBaseAddress;

  /* Initialize Header completion flag */
  LpRamVars->blHeaderComplete = LIN_FALSE;

  if (LIN_HEADER_COMPLETE == (uint8)(LpLN3ChannelRegs->ucRLN3nLST & LIN_HEADER_COMPLETE))
  {
    /* Set header status flag */
    LpRamVars->blHeaderComplete = LIN_TRUE;
    /* Clear the header interrupt */
    LpLN3ChannelRegs->ucRLN3nLST = (LpLN3ChannelRegs->ucRLN3nLST & LIN_HEADER_DONE);

    LpRamVars->ucFrameId = LpLN3ChannelRegs->ucRLN3nLIDB;

    LddPduInfo.Pid = LpRamVars->ucFrameId;

    LddPduInfo.SduPtr = (uint8 *)(&LpRamVars->aaFrameData[(uint32)LIN_ZERO]);                                           /* PRQA S 0312 # JV-01 */

    /* SWS_Lin_00280 */
    LucReturnValue = LinIf_HeaderIndication((NetworkHandleType)LucChannel, &LddPduInfo);

    /* Enter the protection area */
    LIN_ENTER_CRITICAL_SECTION(LIN_INTERRUPT_CONTROL_PROTECTION);

    if (E_OK == LucReturnValue)
    {
      /* SWS_Lin_00282 */
      /* Copy the frame type to frame data structure */
      LpRamVars->enFrameType = LddPduInfo.Drc;

      /* Get the frame type */
      LenFrameType = LpRamVars->enFrameType;

      switch (LenFrameType)
      {
        case LIN_FRAMERESPONSE_RX:
          /* SWS_Lin_00284, LIN response is going to be received*/
        case LIN_FRAMERESPONSE_TX:
          /* SWS_Lin_00283, LIN response is going to be transmitted */

          /* Copy the checksum model to frame data structure */
          LpRamVars->enCheckSumModel = LddPduInfo.Cs;

          /* Copy the data length to frame data structure */
          LpRamVars->ucFrameLength = LddPduInfo.Dl;

          /* Reset of LIN data Field Configuration Register */
          LpLN3ChannelRegs->ucRLN3nLDFC = LIN_RESET_VALUE;

          /* If checksum model is of type CLASSIC */
          if (LIN_CLASSIC_CS == LpRamVars->enCheckSumModel)
          {
            /* Set the checksum model to CLASSIC */
            LpLN3ChannelRegs->ucRLN3nLDFC = (LpLN3ChannelRegs->ucRLN3nLDFC & LIN_SET_CLS_CHKSUM);
          }
          /* If checksum model is of type ENHANCED */
          else
          {
            /* Set the checksum model to ENHANCED */
            LpLN3ChannelRegs->ucRLN3nLDFC = (LpLN3ChannelRegs->ucRLN3nLDFC | LIN_SET_ENH_CHKSUM);
          }

          /* Set length of total bytes in a RLIN3 Frame(Response data + Checksum) */
          LpLN3ChannelRegs->ucRLN3nLDFC = (LpLN3ChannelRegs->ucRLN3nLDFC | LddPduInfo.Dl);

          if (LIN_FRAMERESPONSE_TX == LenFrameType)
          {
            /* To Set the Transmit Data */

            /* Clear LinIf wake-up flag */
            LpRamVars->blWakeupCalled = LIN_FALSE;

            /*Call the internal function to load Tx Buffer and start the frame transmission */
            /* SRS_Lin_01503 */
            Lin_HwLoadTxBuffer(LucChannel);

            /* Set Response direction for Transmit */
            LpLN3ChannelRegs->ucRLN3nLDFC = (LpLN3ChannelRegs->ucRLN3nLDFC | LIN_MASTER_DIRECTION);
          }
          else
          {
            /* Set Response direction for Receive */
            LpLN3ChannelRegs->ucRLN3nLDFC = (LpLN3ChannelRegs->ucRLN3nLDFC & LIN_SLAVE_DIRECTION);
          }
          /* Response transmission/reception is started */
          LpLN3ChannelRegs->ucRLN3nLTRC = LIN_START_RESPONSE;
          break;
        case LIN_FRAMERESPONSE_IGNORE:
          /* SWS_Lin_00286, LIN driver shall ignore the response */
          /* No response for the reception ID */
          LpLN3ChannelRegs->ucRLN3nLTRC = LIN_NO_RESPONSE;
          break;
        default:
          /* No action required */
          break;
      }
    }
    else
    {
      /* SWS_Lin_00286, No response for the reception ID */
      LpLN3ChannelRegs->ucRLN3nLTRC = LIN_NO_RESPONSE;
    }

    /* Exit the protection area */
    LIN_EXIT_CRITICAL_SECTION(LIN_INTERRUPT_CONTROL_PROTECTION);
    }
  else
  {
    LenFrameType = LpRamVars->enFrameType;
    switch (LenFrameType)
    {
      /* SWS_Lin_00274, make the received data available to the LIN interface module */
      case LIN_FRAMERESPONSE_RX:
        if (LIN_RESPONSE_COMPLETE == (uint8)(LpLN3ChannelRegs->ucRLN3nLST & LIN_RESPONSE_COMPLETE))
        {
          /* Clear the reception interrupt */
          LpLN3ChannelRegs->ucRLN3nLST = (LpLN3ChannelRegs->ucRLN3nLST & LIN_RECEPTION_DONE);

          /* Copy the data length to local variable */
          LucDataLength = LpRamVars->ucFrameLength;
          /* Copy data to Tx Buffer */
          for (LucIndex = LIN_ZERO; LucDataLength > LucIndex; LucIndex++)
          {
            LpRamVars->aaFrameData[LucIndex] = LpLN3ChannelRegs->ucRLN3nLDBR[LucIndex];
          }
          /* Copy data to LddPduInfo.SduPtr */
          LddPduInfo.SduPtr = (uint8 *)(&LpRamVars->aaFrameData[(uint32)LIN_ZERO]);                                     /* PRQA S 0312 # JV-01 */
          /* Update channel status to LIN_RX_OK */
          LpRamVars->enChannelStatus = LIN_RX_OK;
          /* make the received data available to the LIN interface module */
          LinIf_RxIndication((NetworkHandleType)LucChannel, LddPduInfo.SduPtr);
        }
        else
        {
          /* No action required */
        }
        break;
      case LIN_FRAMERESPONSE_TX:
        if (LIN_FRAME_COMPLETE == (uint8)(LpLN3ChannelRegs->ucRLN3nLST & LIN_FRAME_COMPLETE))
        {
          /* Clear the transmit interrupt */
          LpLN3ChannelRegs->ucRLN3nLST = (LpLN3ChannelRegs->ucRLN3nLST & LIN_TRANSMIT_DONE);
          /* SWS_Lin_00275,  Successful transmission, send confirmation to the LIN Interface module */
          LinIf_TxConfirmation((NetworkHandleType)LucChannel);
        }
        else
        {
          /* No action required */
        }
        break;
      case LIN_FRAMERESPONSE_IGNORE:
        /* SWS_Lin_00276, The LIN driver shall not report any events to the LIN interface module */
        break;
      default:
        /* No action required */
        break;
    }
  }
}
#define LIN_STOP_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* (LIN_SLAVE_MODE_SUPPORT == STD_ON) */

/***********************************************************************************************************************
** Function Name      : Lin_HwSlaveErrorProcessing
**
** Service ID         : NA
**
** Description        : This service processes the status interrupt requests for slave channel
**
** Sync/Async         : Synchronous
**
** Re-entrancy        : Non Re-entrant for the same channel
**
** Input Parameters   : LucChannel
**
** Output Parameters  : None
**
** Return parameter   : None
**
** Preconditions      : None
**
** Global Variables   : Lin_GaaGlobalAccPoint,
**                      Lin_GaaChannelId2CoreIndex (LIN_MULTI_CORE_SUPPORT == STD_ON)
**
** Functions invoked  : LinIf_LinErrorIndication
**
** Registers Used     : ucRLN3nLEST, ucRLN3nLST
**
** Reference ID       : LIN_DUD_ACT_030, LIN_DUD_ACT_030_GBL001,
** Reference ID       : LIN_DUD_ACT_030_GBL002, LIN_DUD_ACT_030_GBL003,
** Reference ID       : LIN_DUD_ACT_030_GBL004, LIN_DUD_ACT_030_REG001,
** Reference ID       : LIN_DUD_ACT_030_REG002, LIN_DUD_ACT_030_REG003,
** Reference ID       : LIN_DUD_ACT_030_REG004, LIN_DUD_ACT_030_REG005,
** Reference ID       : LIN_DUD_ACT_030_REG006, LIN_DUD_ACT_030_REG007,
** Reference ID       : LIN_DUD_ACT_030_REG008, LIN_DUD_ACT_030_GBL005,
** Reference ID       : LIN_DUD_ACT_030_GBL006
***********************************************************************************************************************/
#if (LIN_SLAVE_MODE_SUPPORT == STD_ON)
#define LIN_START_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
STATIC FUNC(void, LIN_CODE_FAST) Lin_HwSlaveErrorProcessing(const uint8 LucChannel)
{
  volatile P2CONST(Lin3_ChannelConfigType, AUTOMATIC, LIN_CONST) LpLin3ChannelPtr;
  volatile P2VAR(RLin3_UartRegs, AUTOMATIC, REGSPACE)LpLN3ChannelRegs;                                                  /* PRQA S 3432 # JV-01 */
  volatile P2VAR(Lin_RamData, AUTOMATIC, LIN_VAR_FAST_NO_INIT)LpRamVars;                                                /* PRQA S 3432 # JV-01 */

  Lin_FrameResponseType LenFrameType;
  Lin_SlaveErrorType LenErrorStatus;
  uint8 LucChannelRamIndex;
  uint8 LucCoreIndex;

  #if (LIN_MULTI_CORE_SUPPORT == STD_ON)
  /* LucChannel is channel id, need to convert to chanel index */
  LucCoreIndex = Lin_GaaChannelId2CoreIndex[LucChannel];
  /* Get Channel Ram Index for each core */
  LucChannelRamIndex = (*(Lin_GaaGlobalAccPoint[LucCoreIndex].pChannelConfig))[LucChannel].ucChannelRamIndex;
  #else
  LucCoreIndex = LIN_ZERO;
  /* single core - Channel Ram index = channel id */
  LucChannelRamIndex = LucChannel;
  #endif /* #if (LIN_MULTI_CORE_SUPPORT == STD_ON) */

  /* Get the pointer to channel RAM data */
  LpRamVars = &((Lin_GaaGlobalAccPoint[LucCoreIndex].pChannelRamData)[LucChannelRamIndex]);

  /* Get the channel index */
  LpLin3ChannelPtr = &((*(Lin_GaaGlobalAccPoint[LucCoreIndex].pRLIN3Properties))[LucChannel]);

  /* Get the RLIN3 Channel Base Address */
  LpLN3ChannelRegs = LpLin3ChannelPtr->pLn3ChanlBaseAddress;

  /* Check for any error occurred */
  if (LIN_ERROR_OCCURED == (uint8)(LpLN3ChannelRegs->ucRLN3nLST & LIN_ERROR_OCCURED))
  {
    /* Check if an error was occurred in Lin_Wakeup() */
    if (LIN_TRUE == LpRamVars->blWakeupCalled)
    {
      /* Reset LinIf WakeUp Flag */
      LpRamVars->blWakeupCalled = LIN_FALSE;

      /* Check for Bit error */
      if (LIN_ERROR_FREE != (uint8)(LpLN3ChannelRegs->ucRLN3nLEST & LIN_BIT_ERROR))
      {
        /* SWS_Lin_00281 invalid LIN header */
        LenErrorStatus = LIN_ERR_HEADER;
        /* Clear BER bit */
        LpLN3ChannelRegs->ucRLN3nLEST = LIN_BIT_CLEAR;
        /* SWS_Lin_00277, Once an error is detected, error indication callback is called */
        LinIf_LinErrorIndication((NetworkHandleType)LucChannel, LenErrorStatus);
      }
      else
      {
        /* No action required */
      }
    }
    /* Check if header frame transmit successfully */
    else if (LpRamVars->blHeaderComplete == LIN_TRUE)
    {
      /* Clear Header Complete Flag */
      LpRamVars->blHeaderComplete = LIN_FALSE;
      /* Error in Response part */
      /* Get frame type */
      LenFrameType = LpRamVars->enFrameType;

      switch (LenFrameType)
      {
        case LIN_FRAMERESPONSE_TX:
          if (LIN_ERROR_FREE != (uint8)(LpLN3ChannelRegs->ucRLN3nLEST & (LIN_BIT_ERROR | LIN_TIMEOUT_ERROR)))
          {
            /* SWS_Lin_00277 errors during response transmission */
            LenErrorStatus = LIN_ERR_RESP_DATABIT;
            /* Clear BER and TER bit */
            LpLN3ChannelRegs->ucRLN3nLEST = (LIN_BIT_CLEAR & LIN_TIMEOUT_CLEAR);
            /* SWS_Lin_00277, Once an error is detected, error indication callback is called */
            LinIf_LinErrorIndication((NetworkHandleType)LucChannel, LenErrorStatus);
          }
          else
          {
            /* Do Nothing */
          }
          break;
        case LIN_FRAMERESPONSE_IGNORE:
          /* only clear error */
          LpLN3ChannelRegs->ucRLN3nLEST = LIN_ERROR_FREE;
          break;
        case LIN_FRAMERESPONSE_RX:
          /* SWS_Lin_00285 LIN response must be completed by a call to LinIf_LinErrorIndication */
          LenErrorStatus = LIN_ERR_NO_RESP;
          /* SWS_Lin_00277, Once an error is detected, error indication callback is called */
          LinIf_LinErrorIndication((NetworkHandleType)LucChannel, LenErrorStatus);

          /* Check for any Time out error */
          if (LIN_ERROR_FREE != (uint8)(LpLN3ChannelRegs->ucRLN3nLEST & LIN_TIMEOUT_ERROR))
          {
            /* Check if at least 1 response byte has been received */
            if (LIN_DATA1RX_COMPLETE == (uint8)(LpLN3ChannelRegs->ucRLN3nLST & LIN_DATA1RX_COMPLETE))
            {
              /* SWS_Lin_00277 errors during response reception */
              LenErrorStatus = LIN_ERR_INC_RESP;
            }
            else
            {
              /* SWS_Lin_00277 errors during response reception */
              LenErrorStatus = LIN_ERR_NO_RESP;
            }
            /* Clear TER bit */
            LpLN3ChannelRegs->ucRLN3nLEST = LIN_TIMEOUT_CLEAR;
            /* SWS_Lin_00277, Once an error is detected, error indication callback is called */
            LinIf_LinErrorIndication((NetworkHandleType)LucChannel, LenErrorStatus);
          }
          else
          {
            /* No action required */
          }

          /* Check for any framing error */
          if (LIN_ERROR_FREE != (uint8)(LpLN3ChannelRegs->ucRLN3nLEST & LIN_FRAMING_ERROR))
          {
            /* SWS_Lin_00277 errors during response reception */
            LenErrorStatus = LIN_ERR_RESP_STOPBIT;
            /* Clear FER bit */
            LpLN3ChannelRegs->ucRLN3nLEST = LIN_FRAMING_CLEAR;
            /* SWS_Lin_00277, Once an error is detected, error indication callback is called */
            LinIf_LinErrorIndication((NetworkHandleType)LucChannel, LenErrorStatus);
          }
          else
          {
            /* No action required */
          }

          /* Check for any checksum field error */
          if (LIN_ERROR_FREE != (uint8)(LpLN3ChannelRegs->ucRLN3nLEST & LIN_CHECKSUM_ERROR))
          {
            /* SWS_Lin_00277 errors during response reception */
            LenErrorStatus = LIN_ERR_RESP_CHKSUM;
            /* Clear CSER bit */
            LpLN3ChannelRegs->ucRLN3nLEST = LIN_CHECKSUM_CLEAR;
            /* SWS_Lin_00277, Once an error is detected, error indication callback is called */
            LinIf_LinErrorIndication((NetworkHandleType)LucChannel, LenErrorStatus);
          }
          else
          {
            /* No action required */
          }
          /* Check for any Response Preparation Error */
          if (LIN_ERROR_FREE != (uint8)(LpLN3ChannelRegs->ucRLN3nLEST & LIN_RESPRE_ERROR))
          {
            /* SWS_Lin_00281 invalid LIN header */
            LenErrorStatus = LIN_ERR_INC_RESP;
            /* Clear RPER bit */
            LpLN3ChannelRegs->ucRLN3nLEST = LIN_RESPRE_CLEAR;
            /* SWS_Lin_00277, Once an error is detected, error indication callback is called */
            LinIf_LinErrorIndication((NetworkHandleType)LucChannel, LenErrorStatus);
          }
          else
          {

          }
          break;
        default:
          /* No action required */
          break;
      }
    }
    else
    {
      /* Error in Header part */
      /* Check for any Time out error, Sync field error, or ID parity error */
      if (LIN_ERROR_FREE !=
        (uint8)(LpLN3ChannelRegs->ucRLN3nLEST & (LIN_TIMEOUT_ERROR | LIN_SYNC_ERROR | LIN_IDPARITY_ERROR)))
      {
        /* SWS_Lin_00281 invalid LIN header */
        LenErrorStatus = LIN_ERR_HEADER;
        /* Clear IPER, SFER, TER bit */
        LpLN3ChannelRegs->ucRLN3nLEST = (LIN_TIMEOUT_CLEAR & LIN_SYNC_CLEAR & LIN_IDPARITY_CLEAR);
        /* SWS_Lin_00277, Once an error is detected, error indication callback is called */
        LinIf_LinErrorIndication((NetworkHandleType)LucChannel, LenErrorStatus);
      }
      else
      {
        /* No action required */
      }
    }
  }
  else
  {
    /* No action required */
  }
}
#define LIN_STOP_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* #if (LIN_SLAVE_MODE_SUPPORT == STD_ON) */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
