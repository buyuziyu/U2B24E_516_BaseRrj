/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = CanXL.c                                                                                             */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2023-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Provision of Initialization, ReInitialization and Version Control Functionality.                                   */
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
/*              Devices:                         X2x                                                                  */
/*====================================================================================================================*/

/***********************************************************************************************************************
**                                              Revision Control History                                              **
***********************************************************************************************************************/
/* 
 * 2.4.1: 30/06/2025  : Remove the SW-VERSION from header of file
 * 2.4.0: 30/05/2025  : Update CanXL_DeInitController, CanXL_InitMHModule, CanXL_HWSettingRXFilter, CanXL_StartMode,
 *                      CanXL_StopMode, CanXL_Transmit, CanXL_TxConfirmation, CanXL_SetControllerMode,
 *                      CanXL_RxCallEthIf, CanXL_TxConfirmationQueueProcess
 *                      Fixing QAC message
 * 2.3.1: 31/03/2025  : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 *                    : Update CanXL_ConsistentCheck, CanXL_RxQueueProcess
 *                    : Add message 0404, 0489, 3006, 3415 to support QA-C version 11.6.0
 *                    : Update CanXL_Transmit, CanXL_CommonDetCheck
 * 2.3.0: 28/02/2025  : As part of ARDAACL-52560: Update CanXL_Transmit, CanXL_StartMode,
 *                      CanXL_InitMHModule, CanXL_RxQueueProcess, CanXL_HwTransmit, CanXL_FindTxBuffer,
 *                      CanXL_WriteRxData, CanXL_SetControllerMode, CanXL_DeInitController, CanXL_HwDescriptorInit
 *                      CanXL_AddAddressFilter, CanXL_InitializeBuffer, CanXL_TxConfirmationQueueProcess
 *                      CanXL_WriteRxData, CanXL_ConsistentCheck
 * 2.2.0: 31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 *                      As part of CANXL driver support, following changes are made:
 *                      1. Update Can_CanXLInit, CanXL_StartMode, CanXL_InitMHModule, CanXL_DeInitController,
 *                      CanXL_HwDescriptorInit, CanXL_InitializeBuffer, CanXL_IsMatchFilter, CanXL_IsRxFrameValid,
 *                      CanXL_IsMatchVCID, CanXL_RxQueueProcess, CanXL_HwReceive, CanXL_HwTransmit,
 *                      CanXL_TxConfirmationQueueProcess, CanXL_HwTxConfirmation, CanXL_ConsistentCheck, 
 *                      CanXL_HwGetIngressTimeStamp
 *                      2. Add new CanXL_TECEmulator, CanXL_WriteRxData
 * 2.1.2: 31/10/2024  : As part of CANXL driver support, following changes are made:
 *                      1. Fixing QAC message. Remove messages: 0303, 3415, 3006, 0404, 0489
 *                      Update CanXL_IsMatchVCID, CanXL_SetControllerMode, CanXL_Receive, CanXL_StartMode, 
 *                      CanXL_InitMHModule, CanXL_DeInitController, CanXL_HwCheckQueueIndex, CanXL_RxQueueProcess
 *                      CanXL_ReleaseTxBuffer, CanXL_ConsistentCheck to fix findings
 * 2.1.1: 08/08/2024  : As part of CANXL driver support, following changes are made:
 *                      1. Update CanXL_GetTxBuffer
 *        07/08/2024  : As part of CANXL driver support, following changes are made:
 *                      1. Update CanXL_TxConfirmationQueueProcess, CanXL_Transmit
 *        06/08/2024  : As part of CANXL driver support, following changes are made:
 *                      1. Update CanXL_StopMode, CanXL_DeInitController, CanXL_IsMatchFilter
 *        29/07/2024  : As part of CANXL driver support, following changes are made:
 *                      1. Update CanXL_SetControllerMode, CanXL_GetControllerMode, CanXL_Transmit, CanXL_GetTxBuffer,
 *                       CanXL_GetIngressTimeStamp, Can_CanXLInit, CanXL_StartMode, CanXL_StopMode, CanXL_RamAlloc
 *                       CanXL_IsMatchFilter, CanXL_IsMatchFilter, CanXL_HwReceive, CanXL_TxConfirmationQueueProcess
 *        24/06/2024  : As part of CANXL driver support, following changes are made:
 *                      1. Update CanXL_StopMode, CanXL_StopMode, CanXL_HwDescriptorInit, Can_CanXLInit 
 *                      Add CanXL_DeInitModule
 *                      2. Add QAC message 2986, 2004
 *        10/06/2024  : As part of CANXL driver support, following changes are made:
 *                      1. Update API CanXL_StopMode to fix issue related to CANXL controller STOP MODE change
 *                      Update API CanXL_HwDescriptorInit, CanXL_GetTxBuffer, CanXL_HwTransmit, 
 *                      CanXL_TxConfirmationQueueProcess to fix issue related to RX_FQ_INT_STS, 
 *                      TX_FQ_INT_STS register
 *                      2. Correct DET ID in API CanXL_GetControllerMode
 *        29/05/2024  : As part of CANXL driver support, following changes are made:
 *                      1. In CanXL_CommonDetCheck, support multicore for CANXL to check CANXL_E_INVALID_CORE
 *                      In CanXL_InitMHModule, add to support CAN_INTERRUPT_CONTROL_PROTECTION_GLOBAL
 *                      In CanXL_TxConfirmationQueueProcess to fix issue FIFO QUEUE
 * 2.0.3: 13/04/2024  : CanXL_ProvideTxBuffer, CanXL_StartMode, CanXL_StopMode, CanXL_InitMHModule,
 *                      CanXL_HwDescriptorInit, CanXL_GetTxBuffer, CanXL_IsMatchFilter, CanXL_RxQueueProcess,
 *                      CanXL_TxConfirmationQueueProcess
 *        12/04/2024  : Add header message 0312
 * 2.0.2: 23/02/2024  : Add macro CAN_CANXL_SUPPORTED to cover CANXL RegStruct
 *        21/01/2024  : Add Can_Irq.h into Include Section
 *        19/01/2024  : Update reference ID ro support CANXL
 *        09/01/2024  : Add reference ID for Can_CanXLInit, CanXL_StartMode, CanXL_StopMode, CanXL_InitMHModule
 *                      CanXL_RamInit
 *        25/12/2023  : Initial version.
 */
/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
#include "CanXL.h"
#include "CanIf_Can.h"
#include "rh850_Types.h"
#include "Can_Ram.h"
#include "Can_Irq.h"
#include "Det.h"
#if (CAN_CANXL_SUPPORTED == STD_ON)
/* Register structure */
#include "CanXL_RegStruct.h"
#include "CanXLTrcv.h"
#endif
/* Scheduler */
#include "SchM_Can.h"
/* including DEM header file */
#include "Dem.h"
/* Included for the declaration of Det_ReportError() */
#if (CAN_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define CANXL_C_AR_RELEASE_MAJOR_VERSION    CAN_AR_RELEASE_MAJOR_VERSION_VALUE
#define CANXL_C_AR_RELEASE_MINOR_VERSION    CAN_AR_RELEASE_MINOR_VERSION_VALUE                                          
#define CANXL_C_AR_RELEASE_REVISION_VERSION CAN_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define CANXL_C_SW_MAJOR_VERSION            CAN_SW_MAJOR_VERSION_VALUE
#define CANXL_C_SW_MINOR_VERSION            CAN_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (CANXL_C_AR_RELEASE_MAJOR_VERSION != CAN_AR_RELEASE_MAJOR_VERSION)
  #error "CanXL.c : Mismatch in Release Major Version"
#endif
#if (CANXL_C_AR_RELEASE_MINOR_VERSION != CAN_AR_RELEASE_MINOR_VERSION)
  #error "CanXL.c : Mismatch in Release Minor Version"
#endif
#if (CANXL_C_AR_RELEASE_REVISION_VERSION != CAN_AR_RELEASE_REVISION_VERSION)
  #error "CanXL.c : Mismatch in Release Revision Version"
#endif

#if (CANXL_C_SW_MAJOR_VERSION != CAN_SW_MAJOR_VERSION)
  #error "CanXL.c : Mismatch in Software Major Version"
#endif

#if (CANXL_C_SW_MINOR_VERSION != CAN_SW_MINOR_VERSION)
  #error "CanXL.c : Mismatch in Software Minor Version"
#endif

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (3:2004)    : No concluding 'else' exists in this 'if'-'else'-'if' statement.                              */
/* Rule                : CERTCCM EXP02, MISRA C:2012 Rule-15.7, CWE Rule CWE-398, CWE-569                             */
/* JV-01 Justification : The "else"statement with empty content is removed to improve readability.                    */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:2986)    : This operation is redundant. The value of the result is always that of the right-hand        */
/*                       operand.                                                                                     */
/* Rule                : CERTCCM MSC07, MSC13, MISRA C:2012 Rule-2.2                                                  */
/* JV-01 Justification : This operation is an important operation for calculating the decrement value as the          */
/*                       increment value, so it is necessary and not redundant.                                       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:5087)    : Use of #include directive after code fragment.                                               */
/* Rule                : MISRA C:2012 Rule-20.1                                                                       */
/* JV-01 Justification : This is done as per Memory Requirement, (MEMMAP003 - Specification of Memory Mapping).       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7                                                                       */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is accepted. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0316)    : Cast from a pointer to void to a pointer to object type.                                     */
/* Rule                : MISRA C:2012 Rule-11.5                                                                       */
/* JV-01 Justification : A cast should not be performed between a pointer to object type and a different pointer to   */
/*                       object type.                                                                                 */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3469)    : This usage of a function-like macro looks like it could be replaced by an equivalent         */
/*                       function call.                                                                               */
/* Rule                : MISRA C:2012 Dir-4.9                                                                         */
/* JV-01 Justification : This message indicates that a candidate macro may be suitable for replacement by a           */
/*                       function, based on an actual call-site and the arguments passed to it there. (Other uses of  */
/*                       the macro may not necessarily be suitable for replacement.)                                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0310)    : Casting to different object pointer type.                                                    */
/* Rule                : CERTCCM EXP11, EXP39, MISRA C:2012 Rule-11.3                                                 */
/* JV-01 Justification : For accessing 8-bit and 16-bit PNOT and JPNOT register respectively, the 32-bit pointer is   */
/*                       typecasted.                                                                                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0488)    : Performing pointer arithmetic.                                                               */
/* Rule                : CERTCCM EXP08, MISRA C:2012 Rule-18.4                                                        */
/* JV-01 Justification : This is to get the ID in the data structure in the code.                                     */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:3383)    : Cannot identify wraparound guard for unsigned arithmetic expression.                         */
/* Rule                : CERTCCM INT30                                                                                */
/* JV-01 Justification : It can still result in values that are out of range for the intended use, as intuitive       */
/*                       "invariants" may not hold                                                                    */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0306)    : Cast between a pointer to object and an integral type.                                       */
/* Rule                : CERTCCM INT36, MISRA C:2012 Rule-11.4                                                        */
/* JV-01 Justification : Typecasting is done as per the register size, to access hardware registers.                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1504)    : The object '%1s' is only referenced in the translation unit where it is defined.             */
/* Rule                : CERTCCM DCL15, DCL19, MISRA C:2012 Rule-8.7                                                  */
/* JV-01 Justification : This is accepted, due to following coding rule, internal function can be defined in other C  */
/*                       source files                                                                                 */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3408)    : %s' has external linkage and is being defined without any previous declaration.              */
/* Rule                : CERTCCM DCL07, MISRA C:2012 Rule-8.4                                                         */
/* JV-01 Justification : It is accepted, due to the declaration will be taken care by Os                              */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1503)    : The function '%1s' is defined but is not used within this project.                           */
/* Rule                : CERTCCM MSC07, MISRA C:2012 Rule-2.1                                                         */
/* JV-01 Justification : This is accepted, due to the module's API is exported for user's usage.                      */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3673)    : The object addressed by the pointer parameter '%s' is not modified and so the pointer        */
/*                       could be of type 'pointer to const'.                                                         */
/* Rule                : CERTCCM DCL00, DCL13, MISRA C:2012 Rule-8.13                                                 */
/* JV-01 Justification : Pointer variable is used to modify the value at the address so the pointer cannot be         */
/*                       declared as 'pointer to const' type.                                                         */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3416)    : Logical operation performed on expression with persistent side effects.                      */
/* Rule                : CERTCCM EXP45                                                                                */
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
/* Message (6:3305)    : Pointer cast to stricter alignment.                                                          */
/* Rule                : CERTCCM EXP36, EXP39, MISRA C:2012 Rule-11.3                                                 */
/* JV-01 Justification : It is an implementation required to manage heap memory. There is no problem because the      */
/*                       4-byte alignment boundary is guaranteed by the implementation of the heap memory             */
/*                       operation algorithm.                                                                         */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:2982)    : This assignment is redundant. The value of this object is never used before being modified.  */
/* Rule                : CERTCCM MSC07, MSC13, MISRA C:2012 Rule-2.2                                                  */
/* JV-01 Justification : The variable needs to be initialized before using it.                                        */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:3384)    : Cannot identify wraparound guard for dependent unsigned arithmetic expression.               */
/* Rule                : CERTCCM INT30                                                                                */
/* JV-01 Justification : In order to effectively guard against overflow and wraparound at all stages, the expression  */
/*                       should be split up into individual dynamic operations, with their own guards where applicable*/
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0751)    : Casting to char pointer type.                                                                */
/* Rule                : CERTCCM EXP11, EXP39                                                                         */
/* JV-01 Justification : Using void due to specific requirement of input parameter. So, this can be skipped           */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3464)    : Argument to macro '%s' contains a side effect that will be evaluated more than once.         */
/* Rule                : CERTCCM PRE31                                                                                */
/* JV-01 Justification : This message is only emitted for expressions expanded from argument tokens written out at    */
/*                       the top level, that did not themselves originate from a macro expansion.                     */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1505)    : The function '%1s' is only referenced in the translation unit where it is defined.           */
/* Rule                : CERTCCM DCL19, MISRA C:2012 Rule-8.7                                                         */
/* JV-01 Justification : This is accepted, due to following coding rule, internal function can be defined in other C  */
/*                       source files                                                                                 */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:4322)    : An expression of 'essentially enum' type (ETag_Eth_RxExtStatusType) is being cast to a       */
/*                       different enum type, 'ETag_Eth_RxStatusType'.                                                */
/* Rule                : MISRA C:2012 Rule-10.5                                                                       */
/* JV-01 Justification : It is confirmed that no data loss occurs during the type casting process, so it is accepted. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3473)    : This usage of a function-like setter macro looks like it could be replaced by a similar      */
/*                       function call.                                                                               */
/* Rule                : MISRA C:2012 Dir-4.9                                                                         */
/* JV-01 Justification : This message is an improvement to refactor function-like macros to be implemented as true C  */
/*                       functions. It not affect to driver operation and can be accepted                             */
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
/* JV-01 Justification : This is accepted. It just an advise for improve safety by reducing the possibility that the  */
/*                       referenced data is unintentionally modified through an unexpected alias and improves         */
/*                       clarity by indicating that the referenced data is not intended to be modified through this   */
/*                       alias or those depending on it                                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message(2:2907)     : Apparent: Positive integer value truncated by cast to a smaller unsigned type.               */
/* Rule                : CWE-197, CWE-681, CWE-704, CWE-192, CWE-738                                                  */
/* JV-01 Justification : Typecasting is done as the return types of functions are different                           */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:1006)    : This in-line assembler construct is a language extension. The code has been ignored.         */
/* Rule                : CERTCCM MSC14, MISRA C:2012 Dir-1.1, Rule-1.2, Dir-4.2                                       */
/* JV-01 Justification : This is accepted, due to the Synchronization Processing Instruction is following hardware    */
/*                       specification.                                                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:0312)    : Dangerous pointer cast results in loss of volatile qualification.                            */
/* Rule                : CERTCCM EXP32, MISRA C:2012 Rule 11.8                                                        */
/* JV-01 Justification : According to the coding guide, all global variables must have volatile attribute, but        */
/*                       volatile must be removed when return these variables from APIs according to the AUTOSAR      */
/*                       specification.                                                                               */
/*       Verification  : Since these are normal memory objects, any problem doesn't occurs.                           */
/**********************************************************************************************************************/
/* Message (4:2963)    : Suspicious: Using value of uninitialized automatic object '%s'.                              */
/* Rule                : CERTCCM EXP33                                                                                */
/* JV-01 Justification : It will be initialized based on scope of 'if' statements where at least an 'if' statement    */
/*                       will be executed that will initialize the variable in question.                              */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (7:0404)    : More than one read access to volatile objects between sequence points.                       */
/* Rule                : MISRA C:2012 Rule-1.3, Rule-13.2, CERTCCM EXP30, EXP10, CWE Rule CWE-682, CWE-758, CWE-737   */
/* JV-01 Justification : This is to get an element in the array of struct, volatile of the counter variable of 'for'  */
/*                       loop is used to ensure no optimization. It is accepted                                       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3006)    : This function contains a mixture of in-line assembler statements and C statements.           */
/* Rule                : MISRA C:2012 Dir-4.3                                                                         */
/* JV-01 Justification : This is accepted, due to the implementation is following hardware specification.             */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3415)    : Right hand operand of '&&' or '||' is an expression with persistent side effects.            */
/* Rule                : MISRA C:2012 Rule-13.5, CERTCCM EXP02, CWE Rule CWE-398, CWE-768, CWE-569                    */
/* JV-01 Justification : Although it is a volatile object, it does not have direct access to the HW register, and     */
/*                       there is no side effect.                                                                     */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0489)    : The integer value 1 is being added or subtracted from a pointer.                             */
/* Rule                : MISRA C:2012 Rule-18.4, CWE-188, CWE-468, CWE-398, CWE-465, CWE-569                          */
/* JV-01 Justification : This is to get the ID in the data structure in the code.                                     */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

#if (CAN_CANXL_SUPPORTED == STD_ON)
#define CAN_START_SEC_CONST_32
#include "Can_MemMap.h"
/* Const values of broadcast and null address to be compared */
CONST(CanXL_MacAddressType, CAN_CONST) CanXL_GstBroadcastAddr =                                                         /* PRQA S 1504, 3408 # JV-01, JV-01 */
{
  0xFFFFFFFFUL, 0x0000FFFFU
};
CONST(CanXL_MacAddressType, CAN_CONST) CanXL_GstNullAddr =                                                              /* PRQA S 1504, 3408 # JV-01, JV-01 */
{
  0x00000000UL, 0x00000000U
};
#define CAN_STOP_SEC_CONST_32
#include "Can_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* CAN_CANXL_SUPPORTED */

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/
#if (CAN_CANXL_SUPPORTED == STD_ON)
/* Sub function to initialize Message Handler for CANXL */
#define CAN_START_SEC_PRIVATE_CODE
#include "Can_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
STATIC FUNC(boolean, CAN_PRIVATE_CODE) CanXL_InitMHModule(uint8 LucController);
STATIC FUNC(void, CAN_PRIVATE_CODE) CanXL_HwDescriptorInit(uint8 LucController);
STATIC FUNC(void, CAN_PRIVATE_CODE) CanXL_HWSettingRXFilter(uint8 LucControllerID);

STATIC FUNC(void, CAN_PRIVATE_CODE) CanXL_ClearAllAddressFilters(
  CONST(uint32, AUTOMATIC) LulCtrlIdx);
STATIC FUNC(Std_ReturnType, CAN_PRIVATE_CODE) CanXL_RemoveAddressFilter(
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONSTP2CONST(CanXL_MacAddressType, AUTOMATIC, CANXL_APPL_DATA) LpMacAddr);
STATIC FUNC(Std_ReturnType, CAN_PRIVATE_CODE) CanXL_AddAddressFilter( 
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONSTP2CONST(CanXL_MacAddressType, AUTOMATIC, CAN_APPL_DATA) LpMacAddr);
STATIC FUNC(Std_ReturnType, CAN_PRIVATE_CODE) CanXL_CheckProvideBuffer(
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulBufIdx);
STATIC FUNC(void, CAN_PRIVATE_CODE) CanXL_RamInit(
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulBaseAddr, CONST(uint32, AUTOMATIC) LulRamSize);
STATIC FUNC(uint32, CAN_PRIVATE_CODE) CanXL_RamAlloc(CONST(uint32, AUTOMATIC) LulCtrlIdx, 
                                                                                   CONST(uint32, AUTOMATIC) LulRamSize);
STATIC FUNC(BufReq_ReturnType , CAN_PRIVATE_CODE) CanXL_GetTxBuffer(
  CONST(uint32, AUTOMATIC) LulCtrlIdx,
  CONST(uint8, AUTOMATIC) LucPriority,
  CONSTP2VAR(Eth_BufIdxType, AUTOMATIC, CAN_APPL_DATA) LpBufIdxPtr,                                                     /* PRQA S 3432 # JV-01 */
  CONSTP2VAR(uint8*, AUTOMATIC, CAN_APPL_DATA) LpBufPtr,                                                                /* PRQA S 3432 # JV-01 */
  CONSTP2VAR(uint16, AUTOMATIC, CAN_APPL_DATA) LenBytePtr);                                                             /* PRQA S 3432 # JV-01 */

STATIC FUNC(void, CAN_PRIVATE_CODE) CanXL_InitializeBuffer(CONST(uint32, AUTOMATIC) LulCtrlIdx);
STATIC FUNC(Std_ReturnType, CAN_PRIVATE_CODE) CanXL_HwCheckQueueIndex( CONST(uint32, AUTOMATIC) CtrlIdx, 
                                           VAR(uint32, AUTOMATIC) LulQueueIdx, VAR(uint32 *, AUTOMATIC) LulOutQueueIdx);
STATIC FUNC(Std_ReturnType, CAN_PRIVATE_CODE) CanXL_IsMatchFilter(
  CONST(uint32, AUTOMATIC) LulCtrlIdx,
  CONSTP2CONST(CanXL_MacAddressType, AUTOMATIC, CAN_APPL_DATA) LpMacAddr);
STATIC FUNC(Std_ReturnType, CAN_PRIVATE_CODE) CanXL_IsRxFrameValid(
  CONST(uint32, AUTOMATIC) LulCtrlIdx,
  CONSTP2CONST(CanXL_RxFrameType, AUTOMATIC, CAN_APPL_DATA) LpRxFrame);
STATIC FUNC(void, CAN_PRIVATE_CODE) CanXL_RxCallEthIf(
  CONST(uint32, AUTOMATIC) LulCtrlIdx,
  CONSTP2CONST(CanXL_RxFrameType, AUTOMATIC, CAN_APPL_DATA) LpFrame);
STATIC FUNC(Eth_RxStatusType, CAN_PRIVATE_CODE) CanXL_HwReceive(
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulQueueIdx);
STATIC FUNC(void, CAN_PRIVATE_CODE) CanXL_PreprocessFrame(
  CONST(uint32, AUTOMATIC) LulCtrlIdx,
  CONST(uint32, AUTOMATIC) LulBufIdx,
  CONST(uint32, AUTOMATIC) LulFrameType,
  CONSTP2CONST(uint8, AUTOMATIC, CAN_APPL_DATA) LpPhysAddrPtr,
  P2VAR(uint32, AUTOMATIC, CAN_APPL_DATA) LpVCID);                                                                      /* PRQA S 3432 # JV-01 */
STATIC FUNC(Std_ReturnType, CAN_PRIVATE_CODE) CanXL_HwTransmit(
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulBufIdx,
  CONST(uint32, AUTOMATIC) LulLenByte, CONST(boolean, AUTOMATIC) LblConfirmation,
  CONSTP2CONST(uint8, AUTOMATIC, CAN_APPL_DATA) LpPhysAddrPtr, uint32 LulVICD);
STATIC FUNC(void, CAN_PRIVATE_CODE) CanXL_Util_RamFree(
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONSTP2VAR(void, AUTOMATIC, CAN_APPL_DATA) LpMemAddr);
STATIC FUNC(uint32, CAN_PRIVATE_CODE) CanXL_FindTxBuffer(
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulQIdx);
STATIC FUNC(Std_ReturnType, CAN_PRIVATE_CODE) CanXL_IsMatchVCID( CONST(uint32, AUTOMATIC) LulCtrlIdx, 
          CONST(uint32, AUTOMATIC) LulQueueIdx, P2VAR(Can_RxDescriptorsType, AUTOMATIC, CAN_APPL_DATA) LpTargetDesc);   /* PRQA S 3432 # JV-01 */
STATIC FUNC(void, CAN_PRIVATE_CODE) CanXL_TxConfirmationQueueProcess(
        CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulQIdx, Can_BufferType LucTxQueueType);
#if (CAN_DEV_ERROR_DETECT == STD_ON)
STATIC FUNC(Can_CommonReturnType, CAN_PRIVATE_CODE) CanXL_CommonDetCheck(
  CONST(uint8, AUTOMATIC) LucSID, CONST(uint8, AUTOMATIC) LucController);
#endif
#if(CAN_CANXL_GLOBAL_TIME_SUPPORT == STD_ON)
STATIC FUNC(Std_ReturnType, CAN_PRIVATE_CODE) CanXL_HwGetIngressTimeStamp(
  CONST(uint32, AUTOMATIC) LulCtrlIdx,
  CONSTP2CONST(Eth_DataType, AUTOMATIC, CAN_APPL_DATA) LpDataPtr,
  CONSTP2VAR(Eth_TimeStampQualType, AUTOMATIC, CAN_APPL_DATA) LpTimeQualPtr,                                            /* PRQA S 3432 # JV-01 */
  CONSTP2VAR(Eth_TimeStampType, AUTOMATIC, CAN_APPL_DATA) LpTimeStampPtr);                                              /* PRQA S 3432 # JV-01 */
STATIC FUNC(Std_ReturnType, CAN_PRIVATE_CODE) CanXL_HwGetEgressTimeStamp(
  CONST(uint32, AUTOMATIC) LulCtrlIdx,
  CONST(Eth_BufIdxType, AUTOMATIC) LulBufIdx,
  CONSTP2VAR(Eth_TimeStampQualType, AUTOMATIC, CAN_APPL_DATA) LpTimeQualPtr,                                            /* PRQA S 3432 # JV-01 */
  CONSTP2VAR(Eth_TimeStampType, AUTOMATIC, CAN_APPL_DATA) LpTimeStampPtr);                                              /* PRQA S 3432 # JV-01 */
#endif /* CAN_CANXL_GLOBAL_TIME_SUPPORT */
#define CAN_STOP_SEC_PRIVATE_CODE
#include "Can_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* (CAN_CANXL_SUPPORTED == STD_ON) */

#if (CAN_CANXL_SUPPORTED == STD_ON)
#define CAN_START_SEC_PUBLIC_CODE
#include "Can_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : CanXL_SetControllerMode
**
** Service ID            : 0x03
**
** Description           : Enables/Disables Rx/Tx communication of the indexed controller. The result is reported
**                         asynchronously via EthIf_CtrlModeIndication.
**
** Sync/Async            : Asynchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : CtrlIdx:  Index of the controller within the context of the Driver
**                         CtrlMode: Enable/Disable controller
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : Std_ReturnType
**                         E_OK: success.
**                         E_NOT_OK: controller mode could not be changed.
**
** Preconditions         : None
**
** Global Variables Used : CanXL_GaaCtrlStat, Can_GpPCController, Can_GpConfig
**
** Function(s) invoked   : EthIf_CtrlModeIndication, CanXL_CommonDetCheck.
**
** Registers Used        : None
**
** Reference ID          : CAN_DUD_ACT_131
** Reference ID          : CAN_DUD_ACT_131_GBL001, CAN_DUD_ACT_131_GBL002, CAN_DUD_ACT_131_GBL003
***********************************************************************************************************************/
FUNC(Std_ReturnType, CAN_PUBLIC_CODE) CanXL_SetControllerMode (uint8 CtrlIdx, Eth_ModeType CtrlMode)                    /* PRQA S 1503 # JV-01 */
{
  /* Define return value */
  Std_ReturnType LucReturnValue;
  uint8 LucChannelId;
  uint8 LucCtrlInfoIndex;
  uint32 LulCounter;
  P2CONST(CanXL_BufHandlerType, AUTOMATIC, CAN_APPL_DATA) LpBufHandlerPtr;

  LucReturnValue = E_OK;                                                                                                /* PRQA S 2982 # JV-01 */
  
  #if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* Report to DET, if module is not initialized */
  LucReturnValue = CanXL_CommonDetCheck(CANXL_SET_CONTROLLER_MODE_SID, CtrlIdx);
  if ((ETH_MODE_ACTIVE != CtrlMode) && (ETH_MODE_DOWN != CtrlMode))
  {
    (void)Det_ReportError(CANXL_MODULE_ID, CANXL_INSTANCE_ID, CANXL_SET_CONTROLLER_MODE_SID, CANXL_E_INV_MODE);
    LucReturnValue = E_NOT_OK;
  }/* else No action required */

  if (E_OK != LucReturnValue)
  {
    /* No action required */
  }
  else
  #endif
  {
    LucChannelId = Can_GpPCController[CtrlIdx].ucCh;
    LucCtrlInfoIndex = Can_GpConfig->pCanXLSecondPhysicalControllerToIndex[LucChannelId]; 
    if (CanXL_GaaCtrlStat[LucCtrlInfoIndex].enMode != CtrlMode)
    {
      if (ETH_MODE_DOWN == CtrlMode)
      {
        for(LulCounter = 0UL; LulCounter < CanXL_GaaTxBufferTotal[LucCtrlInfoIndex]; LulCounter++)
        {
          LpBufHandlerPtr = CanXL_GaaTxBufferMgrTable[LucCtrlInfoIndex][LulCounter].pBufferHdr;
          /* Check Buffer handler is not NULL */
          if (NULL_PTR != LpBufHandlerPtr)
          {
            /* Release all Tx buffer */
            CanXL_ReleaseTxBuffer(LucCtrlInfoIndex, LulCounter);
          } /* else no action required*/
        }
        /* Disable all of Tx/Rx Buffers were asigned */
        CanXL_InitializeBuffer(LucCtrlInfoIndex);
      } /* else no action required*/
      /* Store new state of controller mode */
      CanXL_GaaCtrlStat[LucCtrlInfoIndex].enMode = CtrlMode;
      /* Since this function is implemented as asynchronous, indicate a mode switch to EthIf here */
      EthIf_CtrlModeIndication((uint8)(CtrlIdx + CAN_CONTROLLER_OFFSET), CtrlMode);                                     /* PRQA S 3383, 2985 # JV-01, JV-01 */
    } /* else no action required*/
  }
  return(LucReturnValue);
} /* End of API CanXL_SetControllerMode */

/***********************************************************************************************************************
** Function Name         : CanXL_GetControllerMode
**
** Service ID            : 0x04
**
** Description           : Obtains the communication state of the indexed controller.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : CtrlIdx:  Index of the controller within the context of the Driver
**                         CtrlModePtr: 
**                         ETH_MODE_DOWN: the Rx/Tx communication of the controller is disabled
**                         ETH_MODE_ACTIVE: the Rx/Tx communication of the controller is enabled
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : Std_ReturnType
**                         E_OK: success.
**                         E_NOT_OK: controller mode could not be changed.
**
** Preconditions         : Can_GpPCController, Can_GpConfig
**
** Global Variables Used : CanXL_GaaCtrlStat
**
** Function(s) invoked   : CanXL_CommonDetCheck.
**
** Registers Used        : None
**
** Reference ID          : CAN_DUD_ACT_132
***********************************************************************************************************************/
FUNC(Std_ReturnType, CAN_PUBLIC_CODE) CanXL_GetControllerMode (uint8 CtrlIdx, Eth_ModeType* CtrlModePtr)                /* PRQA S 1503 # JV-01 */
{
  /* Define return value */
  Std_ReturnType LucReturnValue;
  uint8 LucChannelId;
  uint8 LucCtrlInfoIndex;
  #if (CAN_DEV_ERROR_DETECT == STD_ON)
  Std_ReturnType LucCommonResult;
  LucReturnValue = E_OK;
  LucCommonResult = CanXL_CommonDetCheck(CANXL_GET_CONTROLLER_MODE_SID, CtrlIdx);
  /* Report to DET, if module is not initialized */
  if (E_OK != LucCommonResult)
  {
    /* Set the error status flag to true */
    LucReturnValue = E_NOT_OK;
  } /* else no action required*/
  if (NULL_PTR == CtrlModePtr)
  {
    (void)Det_ReportError(CANXL_MODULE_ID, CANXL_INSTANCE_ID, CANXL_GET_CONTROLLER_MODE_SID, CANXL_E_PARAM_POINTER);
    LucReturnValue = E_NOT_OK;
  } /* else no action required*/
  if (E_OK != LucReturnValue)
  {
    /* No action required */
  }
  else
  #endif
  {
    LucChannelId = Can_GpPCController[CtrlIdx].ucCh;
    LucCtrlInfoIndex = Can_GpConfig->pCanXLSecondPhysicalControllerToIndex[LucChannelId]; 
    *CtrlModePtr = CanXL_GaaCtrlStat[LucCtrlInfoIndex].enMode;
    LucReturnValue = E_OK;
  }
  return(LucReturnValue);
} /* End of API CanXL_GetControllerMode */

/*******************************************************************************
** Function Name         : CanXL_ProvideTxBuffer
**
** Service ID            : 0x09
**
** Description           : This API Provides access to a transmit buffer of the
**                         specified controller
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : CtrlIdx:  Index of the controller
**                         Priority: Frame priority for transmit buffer FIFO
**                                   selection
**
** InOut Parameters      : LenBytePtr: In:  desired length in bytes,
**                                     Out: granted length in bytes
**
** Output Parameters     : BufIdxPtr: Index to the granted buffer resource
**                         BufPtr:    Pointer to the granted buffer
**
** Return parameter      : BufReq_ReturnType
**                         BUFREQ_OK:       success
**                         BUFREQ_E_NOT_OK: development error detected
**                         BUFREQ_E_BUSY:   all buffers in use
**                         BUFREQ_E_OVFL:   the requested size is larger than
**                                          the buffer
**
** Preconditions         : Component Requires previous controller initialization
**                         using Can_Init.
**
** Global Variables Used : Can_GpPCController
**
** Function(s) invoked   : Det_ReportError, CanXL_CommonDetCheck
**                         CanXL_GetTxBuffer
**
** Registers Used        : None
**
** Reference ID          : CAN_DUD_ACT_133
** Reference ID          : CAN_DUD_ACT_133_ERR001
*******************************************************************************/
FUNC(BufReq_ReturnType, CAN_PUBLIC_CODE) CanXL_ProvideTxBuffer (uint8 CtrlIdx, uint8 Priority,                          /* PRQA S 1503 # JV-01 */
                                                          Eth_BufIdxType* BufIdxPtr, uint8** BufPtr, uint16* LenBytePtr)
{
  BufReq_ReturnType LenReturnValue;
  VAR(uint8, AUTOMATIC) LucChannelId;
  VAR(uint8, AUTOMATIC) LucCtrlInfoIndex;
  #if (CAN_DEV_ERROR_DETECT == STD_ON)
  Std_ReturnType LucCommonResult;
  LenReturnValue = BUFREQ_OK;
  LucCommonResult = CanXL_CommonDetCheck(CANXL_PROVIDETXBUFFER_SID, CtrlIdx);
  if (E_OK != LucCommonResult)
  {
    LenReturnValue = BUFREQ_E_NOT_OK;
  } /* else no action required*/
  /* Report Error to DET, if the BufIdxPtr pointer value is NULL */
  if ((NULL_PTR == BufIdxPtr) || (NULL_PTR == BufPtr) || (NULL_PTR == LenBytePtr))
  {
    (void)Det_ReportError(CANXL_MODULE_ID, CANXL_INSTANCE_ID, CANXL_PROVIDETXBUFFER_SID, CANXL_E_PARAM_POINTER);
    LenReturnValue = BUFREQ_E_NOT_OK;
  } /* else no action required*/

  if (BUFREQ_OK != LenReturnValue)
  {
    /* No action required */
  }
  else
  #endif
  {
    /* Get channel index of CANXL */
    LucChannelId = Can_GpPCController[CtrlIdx].ucCh;
    LucCtrlInfoIndex = Can_GpConfig->pCanXLSecondPhysicalControllerToIndex[LucChannelId]; 
    /* Get a buffer from the TxBufferRing */
    LenReturnValue = CanXL_GetTxBuffer((uint32)LucCtrlInfoIndex, Priority, BufIdxPtr, BufPtr, LenBytePtr);
  }
  return(LenReturnValue);
}

/***********************************************************************************************************************
** Function Name         : CanXL_Transmit
**
** Service ID            : 0x0A
**
** Description           : Triggers transmission of a previously filled transmit buffer
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant for different buffer indexes and Ctrl indexes
**
** Input Parameters      : CtrlIdx          : Controller index
**                         BufIdx           : Buffer index
**                         FrameType        : EtherType
**                         TxConfirmation   : Flag Tx Confirmation
**                         LenByte          : Length of Eth Frame
**                         PhysAddrPtr      : Destination address
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : E_OK/E_NOT_OK 
**
** Preconditions         : CANXL Driver must be initialized and CANXL Controller
**                         is in state ETH_MODE_ACTIVE.
**
** Global Variables Used : Can_GpPCController, Can_GpConfig
**
** Functions Invoked     : Det_ReportError, CanXL_CheckProvideBuffer, CanXL_PreprocessFrame, CanXL_HwTransmit,
**                         CanXL_CommonDetCheck
**
** Registers Used        : None
**
** Reference ID          : CAN_DUD_ACT_134
** Reference ID          : CAN_DUD_ACT_134_ERR001, CAN_DUD_ACT_134_ERR002
***********************************************************************************************************************/
FUNC(Std_ReturnType, CAN_PUBLIC_CODE) CanXL_Transmit (uint8 CtrlIdx, Eth_BufIdxType BufIdx, Eth_FrameType FrameType ,   /* PRQA S 1503 # JV-01 */
                               boolean TxConfirmation, uint16 LenByte, const uint8* PhysAddrPtr)
{
  /* SDU Type 05h (mapped tunneled 802.3 Ethernet frames)is exclusively used by CanXL_Transmit(). */
  Std_ReturnType LucReturnValue;
  VAR(uint8, AUTOMATIC) LucCtrlInfoIndex;
  VAR(uint32, AUTOMATIC) LulCanXLVCID;
  
  #if (CAN_DEV_ERROR_DETECT == STD_ON)
  LucReturnValue = CanXL_CommonDetCheck(CANXL_TRANSMIT_SID, CtrlIdx);
  if (E_OK != LucReturnValue)
  {
    /* No action required */
  }
  /* Report Error to DET, if the PhysAddrPtr pointer value is NULL */
  else if (NULL_PTR == PhysAddrPtr)                                                                                     /* PRQA S 2004 # JV-01 */
  {
    (void)Det_ReportError(CANXL_MODULE_ID, CANXL_INSTANCE_ID, CANXL_TRANSMIT_SID, CANXL_E_PARAM_POINTER);
    LucReturnValue = E_NOT_OK;
  } /* else no action required*/

  if (E_OK != LucReturnValue)
  {
    /* No action required */
  }
  else
  #endif
  {
    LucCtrlInfoIndex = Can_GpConfig->pCanXLSecondPhysicalControllerToIndex[Can_GpPCController[CtrlIdx].ucCh];           /* PRQA S 0404 # JV-01 */
    /* Report Error to DET, if the BufIdx is out of range */
    if (CanXL_GaaTxBufferTotal[LucCtrlInfoIndex] <= BufIdx)
    {
      (void)Det_ReportError(CANXL_MODULE_ID, CANXL_INSTANCE_ID, CANXL_TRANSMIT_SID, CANXL_E_INV_PARAM);
      LucReturnValue = E_NOT_OK;
    } 
    /* Report Error to DET, if the controller mode Is not Active */
    else if ((ETH_MODE_ACTIVE != CanXL_GaaCtrlStat[LucCtrlInfoIndex].enMode)
               || (CAN_COMMON_STATE_STARTED != Can_GaaCtrlState[CtrlIdx].enMode))
    {
      #if (CAN_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CANXL_MODULE_ID, CANXL_INSTANCE_ID, CANXL_TRANSMIT_SID, CANXL_E_INV_MODE);
      #endif
      LucReturnValue = E_NOT_OK;
    }
    else
    {
      LucReturnValue = CanXL_CheckProvideBuffer((uint32)LucCtrlInfoIndex, (uint32)BufIdx);
      /* If the buffer has not been provided, report the error */
      if (E_OK != LucReturnValue)
      {
        #if (CAN_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError(CANXL_MODULE_ID, CANXL_INSTANCE_ID, CANXL_TRANSMIT_SID, CANXL_E_INV_PARAM);
        #endif
      }
      else
      {
        /* Prepare a frame for transmission.*/
        CanXL_PreprocessFrame((uint32)LucCtrlInfoIndex, (uint32)BufIdx, (uint32)FrameType, PhysAddrPtr, &LulCanXLVCID); 
        
        /* Send a transmit request to the low level driver */
        LucReturnValue = CanXL_HwTransmit((uint32)CtrlIdx, (uint32)BufIdx, (uint32)LenByte, 
                                                                     TxConfirmation, PhysAddrPtr, (uint32)LulCanXLVCID);
      }
    }
  }
  return LucReturnValue;
}

#if(CAN_CANXL_GLOBAL_TIME_SUPPORT == STD_ON)
/*******************************************************************************
** Function Name         : CanXL_EnableEgressTimeStamp
**
** Service ID            : 0x17
**
** Description           : Enable TimeStamp capture for the message that
**                         will be transmitted
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : CtrlIdx: Index of the controller
**                         BufIdx:  Index of the message buffer
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : This function is pre-compile time configurable
**                         (STD_ON/STD_OFF) by the configuration parameter
**                         CanXLGlobalTimeSupport.
**
** Global Variables Used : None
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : CAN_DUD_ACT_135
*******************************************************************************/
FUNC(void, CAN_PUBLIC_CODE) CanXL_EnableEgressTimeStamp (uint8 CtrlIdx, Eth_BufIdxType BufIdx)                          /* PRQA S 1503 # JV-01 */
{
  (void)CtrlIdx;
  (void)BufIdx;
  /* [CP_SWS_CanXL_00123] The service CanXL_EnableEgressTimeStamp() has
      no functionality and shall return without performing any action. */
}

/*******************************************************************************
** Function Name         : CanXL_GetCurrentTime
**
** Service ID            : 0x16
**
** Description           : Returns a time value out of the HW registers
**                         according to the capability of the HW
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : CtrlIdx: Index of the controller
**
** InOut Parameters      : None
**
** Output Parameters     : timeQualPtr:  Quality of the HW TimeStamp returned
**                         timeStampPtr: Current TimeStamp value
**
** Return parameter      : Std_ReturnType
**                         E_OK: Success
**                         E_NOT_OK: Failed
**
** Preconditions         : This function is pre-compile time configurable
**                         (STD_ON/STD_OFF) by the configuration parameter
**                         CanXLGlobalTimeSupport.
**
** Global Variables Used : Can_GpPCController
**
** Function(s) invoked   : Det_ReportError, CanXL_CommonDetCheck.
**
** Registers Used        : None
**
** Reference ID          : CAN_DUD_ACT_136
** Reference ID          : CAN_DUD_ACT_136_ERR001
*******************************************************************************/
FUNC(Std_ReturnType, CAN_PUBLIC_CODE) CanXL_GetCurrentTime (uint8 CtrlIdx, Eth_TimeStampQualType* timeQualPtr,          /* PRQA S 1503, 3673 # JV-01, JV-01 */
                                                                                    Eth_TimeStampType* timeStampPtr)    /* PRQA S 3673 # JV-01 */
{
  Std_ReturnType LucReturnValue;
  /* Get channel index of CANXL */
  #if (CAN_DEV_ERROR_DETECT == STD_ON)
  LucReturnValue = CanXL_CommonDetCheck(CANXL_GETCURRENTTIME_SID, CtrlIdx);
  if ((NULL_PTR == timeQualPtr) || (NULL_PTR == timeStampPtr))
  {
    /* Report Error to DET */
    (void)Det_ReportError(CANXL_MODULE_ID, CANXL_INSTANCE_ID, CANXL_GETCURRENTTIME_SID, CANXL_E_PARAM_POINTER);
    LucReturnValue = E_NOT_OK;
  } /* else no action required*/
  if (E_OK != LucReturnValue)
  {
    /* No Action required */
  }
  else
  #endif
  {
    /* Avoid QAC message */
    (void)timeQualPtr;
    (void)timeStampPtr;
    (void)CtrlIdx;
    LucReturnValue = E_OK;
  }
  return LucReturnValue;
}

/*******************************************************************************
** Function Name         : CanXL_GetEgressTimeStamp
**
** Service ID            : 0x18
**
** Description           : Reads back the egress time stamp on a dedicated
**                         message object.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : CtrlIdx: Index of the controller
**                         BufIdx:  Index of the message buffer
**
** InOut Parameters      : None
**
** Output Parameters     : timeQualPtr:  Quality of HW time stamp
**                         timeStampPtr: Current time stamp
**
** Return parameter      : Std_ReturnType
**                         E_OK: Success
**                         E_NOT_OK: Failed
**
** Preconditions         : This function is pre-compile time configurable
**                        (STD_ON/STD_OFF) by the configuration parameter
**                         CanXLGlobalTimeSupport.
**
** Global Variables Used : Can_GpPCController
**
** Function(s) invoked   : Det_ReportError, CanXL_CommonDetCheck, CanXL_HwGetEgressTimeStamp
**
** Registers Used        : None
**
** Reference ID          : CAN_DUD_ACT_137
** Reference ID          : CAN_DUD_ACT_137_ERR001
*******************************************************************************/
FUNC(Std_ReturnType, CAN_PUBLIC_CODE) CanXL_GetEgressTimeStamp (uint8 CtrlIdx, Eth_BufIdxType BufIdx,                   /* PRQA S 1503 # JV-01 */ 
                                                    Eth_TimeStampQualType* timeQualPtr, Eth_TimeStampType* timeStampPtr)
{
  Std_ReturnType LucReturnValue;
  VAR(uint8, AUTOMATIC) LucChannelId;
  VAR(uint8, AUTOMATIC) LucCtrlInfoIndex;
  #if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* Local variable to hold the DET value */
  LucReturnValue = CanXL_CommonDetCheck(CANXL_GETEGRESSTS_SID, CtrlIdx);
  if ((NULL_PTR == timeQualPtr) || (NULL_PTR == timeStampPtr))
  {
    /* Report Error to DET */
    (void)Det_ReportError(CANXL_MODULE_ID, CANXL_INSTANCE_ID, CANXL_GETEGRESSTS_SID, CANXL_E_PARAM_POINTER);
    LucReturnValue = E_NOT_OK;
  } /* else no action required*/
  if (E_OK != LucReturnValue)
  {
    /* No Action required */
  }
  else
  #endif
  {
    /* Get channel index of CANXL */
    LucChannelId = Can_GpPCController[CtrlIdx].ucCh;
    LucCtrlInfoIndex = Can_GpConfig->pCanXLSecondPhysicalControllerToIndex[LucChannelId]; 
    LucReturnValue = CanXL_HwGetEgressTimeStamp((uint32)LucCtrlInfoIndex, BufIdx, timeQualPtr, timeStampPtr);
  }
  return LucReturnValue;
}

/*******************************************************************************
** Function Name         : CanXL_GetIngressTimeStamp
**
** Service ID            : 0x19
**
** Description           : Return TimeStamp from the HW register
**                         previously started
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : CtrlIdx: Index of the controller
**                         DataPtr: Pointer to the message buffer
**
** InOut Parameters      : None
**
** Output Parameters     : timeQualPtr:  Quality of HW time stamp
**                         timeStampPtr: Current time stamp
**
** Return parameter      : Std_ReturnType
**                         E_OK: Success
**                         E_NOT_OK: Failed
**
** Preconditions         : This function is pre-compile time configurable
**                        (STD_ON/STD_OFF) by the configuration parameter
**                         CanXLGlobalTimeSupport.
**
** Global Variables Used : Can_GpPCController
**
** Function(s) invoked   : Det_ReportError, CanXL_CommonDetCheck, CanXL_HwGetIngressTimeStamp
**
** Registers Used        : None
**
** Reference ID          : CAN_DUD_ACT_138, CAN_DUD_ACT_138_ERR001
*******************************************************************************/
FUNC(Std_ReturnType, CAN_PUBLIC_CODE) CanXL_GetIngressTimeStamp (uint8 CtrlIdx, const Eth_DataType* DataPtr,            /* PRQA S 1503 # JV-01 */
                                                    Eth_TimeStampQualType* timeQualPtr, Eth_TimeStampType* timeStampPtr)
{
  Std_ReturnType LucReturnValue;
  VAR(uint8, AUTOMATIC) LucChannelId;
  VAR(uint8, AUTOMATIC) LucCtrlInfoIndex;
  #if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* Local variable to hold the DET value */
  LucReturnValue = CanXL_CommonDetCheck(CANXL_GETINGRESSTS_SID, CtrlIdx);
  if ((NULL_PTR == DataPtr) || (NULL_PTR == timeQualPtr) || (NULL_PTR == timeStampPtr))
  {
    /* Report Error to DET */
    (void)Det_ReportError(CANXL_MODULE_ID, CANXL_INSTANCE_ID, CANXL_GETINGRESSTS_SID, CANXL_E_PARAM_POINTER);
    LucReturnValue = E_NOT_OK;
  } /* else no action required*/
  if (E_OK != LucReturnValue)
  {
    /* No Action required */
  }
  else
  #endif
  {
    /* Get channel index of CANXL */
    LucChannelId = Can_GpPCController[CtrlIdx].ucCh;
    LucCtrlInfoIndex = Can_GpConfig->pCanXLSecondPhysicalControllerToIndex[LucChannelId];
    LucReturnValue = CanXL_HwGetIngressTimeStamp((uint32)LucCtrlInfoIndex, DataPtr, timeQualPtr, timeStampPtr);
  }
  return LucReturnValue;
}
#endif /* CAN_CANXL_GLOBAL_TIME_SUPPORT == STD_ON */

/***********************************************************************************************************************
** Function Name         : CanXL_GetPhysAddr
**
** Service ID            : 0x08
**
** Description           : This API obtains the physical source address
**                         (MAC Address) configured for the indexed controller.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : CtrlIdx: Index of the controller
**
** InOut Parameters      : None
**
** Output Parameters     : PhysAddrPtr: Pointer to memory containing the
**                         physical source address (MAC address) in network
**                         byte order.
**
** Return parameter      : None
**
** Preconditions         : Component Requires previous controller initialization
**                         using Can_Init.
**
** Global Variables Used : CanXL_GaaCtrlStat, Can_GpPCController
**
** Function(s) invoked   : Det_ReportError, CanXL_CommonDetCheck
**
** Registers Used        : None
**
** Reference ID          : CAN_DUD_ACT_139
** Reference ID          : CAN_DUD_ACT_139_ERR001
***********************************************************************************************************************/
FUNC(void, CAN_PUBLIC_CODE) CanXL_GetPhysAddr (uint8 CtrlIdx, uint8* PhysAddrPtr)                                       /* PRQA S 1503 # JV-01 */
{
  VAR(uint8, AUTOMATIC) LucChannelId;
  VAR(uint8, AUTOMATIC) LucCtrlInfoIndex;
  #if (CAN_DEV_ERROR_DETECT == STD_ON)
  Std_ReturnType LucReturnValue;
  LucReturnValue = CanXL_CommonDetCheck(CANXL_GETPHYSADDR_SID, CtrlIdx);
  /* Report Error to DET, if the PhysAddrPtr pointer value is NULL */
  if (NULL_PTR == PhysAddrPtr)
  {
    (void)Det_ReportError(CANXL_MODULE_ID, CANXL_INSTANCE_ID, CANXL_GETPHYSADDR_SID, CANXL_E_PARAM_POINTER);
     LucReturnValue  = E_NOT_OK;
  } /* else no action required*/
  if (E_OK != LucReturnValue)
  {
    /* No action required */
  }
  else
  #endif /* (CAN_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Get channel index of CANXL */
    LucChannelId = Can_GpPCController[CtrlIdx].ucCh;
    LucCtrlInfoIndex = Can_GpConfig->pCanXLSecondPhysicalControllerToIndex[LucChannelId];
    CANXL_UNPACK_ADDRESS_TO_8(CanXL_GaaCtrlStat[LucCtrlInfoIndex].stMacAddr, PhysAddrPtr);                              /* PRQA S 3469 # JV-01 */
  }
}/* End of API CanXL_GetPhysAddr */

/*******************************************************************************
** Function Name         : CanXL_SetPhysAddr
**
** Service ID            : 0x13
**
** Description           : Sets the physical source address used by the indexed
**                         controller.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant for the same CtrlIdx,
**                         reentrant for different
**
** Input Parameters      : CtrlIdx:     Index of the controller
**                         PhysAddrPtr: Pointer to memory containing the
**                                      physical source address (MAC address)
**                                      in network byte order.
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : Component Requires previous controller initialization
**                         using Can_Init.
**
** Global Variables Used : CanXL_GaaCtrlStat, Can_GpPCController
**
** Function(s) invoked   : Det_ReportError, CanXL_CommonDetCheck
**
** Registers Used        : None
**
** Reference ID          : CAN_DUD_ACT_140
** Reference ID          : CAN_DUD_ACT_140_ERR001
*******************************************************************************/
FUNC(void, CAN_PUBLIC_CODE) CanXL_SetPhysAddr (uint8 CtrlIdx, const uint8* PhysAddrPtr)                                 /* PRQA S 1503 # JV-01 */
{
  VAR(uint8, AUTOMATIC) LucChannelId;
  VAR(uint8, AUTOMATIC) LucCtrlInfoIndex;
  #if (CAN_DEV_ERROR_DETECT == STD_ON)
  Std_ReturnType LucReturnValue;
  LucReturnValue = CanXL_CommonDetCheck(CANXL_SETPHYSADDR_SID, CtrlIdx);
  /* Report Error to DET, if the PhysAddrPtr pointer value is NULL */
  if (NULL_PTR == PhysAddrPtr)
  {
    (void)Det_ReportError(CANXL_MODULE_ID, CANXL_INSTANCE_ID, CANXL_SETPHYSADDR_SID, CANXL_E_PARAM_POINTER);
    LucReturnValue = E_NOT_OK;
  } /* else no action required*/
  if (E_OK != LucReturnValue)
  {
    /* No action required */
  }
  else
  #endif
  {
    /* Get channel index of CANXL */
    LucChannelId = Can_GpPCController[CtrlIdx].ucCh;
    LucCtrlInfoIndex = Can_GpConfig->pCanXLSecondPhysicalControllerToIndex[LucChannelId];
    CANXL_PACK_ADDRESS_FROM_8(PhysAddrPtr, CanXL_GaaCtrlStat[LucCtrlInfoIndex].stMacAddr);                              /* PRQA S 3469 # JV-01 */
  }
}

/*******************************************************************************
** Function Name         : CanXL_Receive
**
** Service ID            : 0x0B
**
** Description           : This API Triggers frame reception
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant for different Queues.
**                         Non Reentrant for the same Queue.
**
** Input Parameters      : CtrlIdx: Index of the controller
**                         QueueIdx: Specifies the related Queue
**
** InOut Parameters      : None
**
** Output Parameters     : RxStatusPtr: Indicates whether a frame has been
**                                      received and if so, whether more frames
**                                      are available or frames got lost.
**
** Return parameter      : None
**
** Preconditions         : Component Requires previous controller initialization
**                         using Can_Init.
**
** Global Variables Used : CanXL_GaaCtrlStat, Can_GpPCController
**
** Function(s) invoked   : Det_ReportError, CanXL_CommonDetCheck,
**                         CanXL_HwCheckQueueIndex, CanXL_HwReceive
**
** Registers Used        : None
**
** Reference ID          : CAN_DUD_ACT_141
** Reference ID          : CAN_DUD_ACT_141_ERR001
*******************************************************************************/
FUNC(void, CAN_PUBLIC_CODE) CanXL_Receive(uint8 CtrlIdx, uint8 QueueIdx, Eth_RxStatusType* RxStatusPtr)                 /* PRQA S 1503 # JV-01 */
{
  Std_ReturnType LucReturnValue;
  VAR(uint8, AUTOMATIC) LucChannelId;
  VAR(uint8, AUTOMATIC) LucCtrlInfoIndex;
  VAR(uint32, AUTOMATIC) LulQueueIdx;
  #if (CAN_DEV_ERROR_DETECT == STD_ON)
  LucReturnValue = CanXL_CommonDetCheck(CANXL_RECEIVE_SID, CtrlIdx);
  if (E_OK == LucReturnValue)
  {
    /* Report Error to DET, if the RxStatusPtr pointer value is NULL */
    if (NULL_PTR == RxStatusPtr)
    {
      (void)Det_ReportError(CANXL_MODULE_ID, CANXL_INSTANCE_ID, CANXL_RECEIVE_SID, CANXL_E_PARAM_POINTER);
      LucReturnValue = E_NOT_OK;
    }
    else
    {
      /* Initial Value Set */
      *RxStatusPtr = ETH_NOT_RECEIVED;
    }
  } /* else no action required*/

  if (E_OK != LucReturnValue)
  {
    /* No action required */
  }
  else
  #endif /* (CAN_DEV_ERROR_DETECT == STD_ON) */
  {
     /* Set to ETH_NOT_RECEIVED */
    *RxStatusPtr = ETH_NOT_RECEIVED;
    /* Get channel index of CANXL */
    LucChannelId = Can_GpPCController[CtrlIdx].ucCh;
    LucCtrlInfoIndex = Can_GpConfig->pCanXLSecondPhysicalControllerToIndex[LucChannelId];
    /* Check if this controller is not Rx interrupt mode */
    if(0U == (Can_GpPCController[CtrlIdx].ucIntEnable & CAN_CHECK_INT_RX))                                              /* PRQA S 3416 # JV-01 */
    {
      /* Check Queue index */
      LucReturnValue = CanXL_HwCheckQueueIndex((uint32) LucCtrlInfoIndex, (uint32)QueueIdx, &LulQueueIdx);
      if (E_OK != LucReturnValue)
      {
        /* No action require */
      }
      else
      {
        *RxStatusPtr = CanXL_HwReceive((uint32)CtrlIdx, LulQueueIdx);
      }
    } /* else no action required*/
  }
}

/*******************************************************************************
** Function Name         : CanXL_GetTxErrorCounterValues
**
** Service ID            : 0x1D
**
** Description           : This API Returns the list of Transmission Error
**                         Counters out of IETF RFC1213 and RFC1643 defined with
**                         Eth_TxErrorCounterValuesType, where the maximal
**                         possible value shall denote an invalid value.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : CtrlIdx: Index of the controller
**
** InOut Parameters      : None
**
** Output Parameters     : TxErrorCounterValues: List of values to read
**                                            statistic values for transmission.
**
** Return parameter      : Std_ReturnType
**                         E_OK: success
**                         E_NOT_OK: Tx-statistics could not be obtained
**
** Preconditions         : None
**
** Global Variables Used : None
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : CAN_DUD_ACT_144
*******************************************************************************/
FUNC(Std_ReturnType, CAN_PUBLIC_CODE) CanXL_GetTxErrorCounterValues (uint8 CtrlIdx,                                     /* PRQA S 1503 # JV-01 */
                                                                     Eth_TxErrorCounterValuesType* TxErrorCounterValues)/* PRQA S 3673 # JV-01 */
{
  (void)CtrlIdx;
  (void)TxErrorCounterValues;
  /* [CP_SWS_CanXL_00021] The service CanXL_GetTxErrorCounterValues()
   has no functionality and shall always return E_NOT_OK without performing any action. */
   
  return(E_NOT_OK);
}

/***********************************************************************************************************************
** Function Name         : CanXL_GetTxStats
**
** Service ID            : 0x1C
**
** Description           : This API Returns the list of Transmission Statistics
**                         out of IETF RFC1213 defined with Eth_TxStatsType,
**                         where the  maximal possible value shall denote an
**                         invalid value.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : CtrlIdx: Index of the controller
**
** InOut Parameters      : None
**
** Output Parameters     : TxStats: List of values to read statistic values for
**                                  transmission.
**
** Return parameter      : Std_ReturnType
**                         E_OK: success
**                         E_NOT_OK: Tx-statistics could not be obtained
**
** Preconditions         : None
**
** Global Variables Used : None
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : CAN_DUD_ACT_145
***********************************************************************************************************************/
FUNC(Std_ReturnType, CAN_PUBLIC_CODE) CanXL_GetTxStats (uint8 CtrlIdx, Eth_TxStatsType* TxStats)                        /* PRQA S 1503, 3673 # JV-01, JV-01 */
{
  (void)CtrlIdx;
  (void)TxStats;
  /* [CP_SWS_CanXL_00022] The service CanXL_GetTxStats() has no functionality
     and shall always return E_NOT_OK without performing any action.*/
   
  return(E_NOT_OK);
}

/***********************************************************************************************************************
** Function Name         : CanXL_GetRxStats
**
** Service ID            : 0x15
**
** Description           : This API Returns the following list according to
**                         IETF RFC2819, where the maximal possible value
**                         shall denote an invalid value.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : CtrlIdx: Index of the controller
**
** InOut Parameters      : None
**
** Output Parameters     : RxStats: List of values according to IETF RFC 2819
**                                  (Remote Network Monitoring Management
**                                  Information Base).
**
** Return parameter      : Std_ReturnType
**                         E_OK: success
**                         E_NOT_OK: drop counter could not be obtained
**
** Preconditions         : None
**
** Global Variables Used : None
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : CAN_DUD_ACT_146
***********************************************************************************************************************/
FUNC(Std_ReturnType, CAN_PUBLIC_CODE) CanXL_GetRxStats (uint8 CtrlIdx, Eth_RxStatsType* RxStats)                        /* PRQA S 1503, 3673 # JV-01, JV-01 */
{
  (void)CtrlIdx;
  (void)RxStats;
  /* [CP_SWS_CanXL_00020] The service CanXL_GetRxStats() has no functionality
      and shall always return E_NOT_OK without performing any action.*/
   
  return(E_NOT_OK);
}

/***********************************************************************************************************************
** Function Name         : CanXL_GetCounterValues
**
** Service ID            : 0x14
**
** Description           : This API Reads a list with drop counter values of
**                         the corresponding controller.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : CtrlIdx: Index of the controller
**
** InOut Parameters      : None
**
** Output Parameters     : CounterPtr: counter values according to IETF RFC 1757
**                                     , RFC 1643 and RFC 2233.
**
** Return parameter      : Std_ReturnType
**                         E_OK: success
**                         E_NOT_OK: counter values read failure
**
** Preconditions         : None
**
** Global Variables Used : None
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : CAN_DUD_ACT_147
***********************************************************************************************************************/
FUNC(Std_ReturnType, CAN_PUBLIC_CODE) CanXL_GetCounterValues (uint8 CtrlIdx, Eth_CounterType* CounterPtr)               /* PRQA S 1503, 3673 # JV-01, JV-01 */
{
  (void)CtrlIdx;
  (void)CounterPtr;
  /* [CP_SWS_CanXL_00048] The service CanXL_GetCounterValues() has no functionality
      and shall always return E_NOT_OK without performing any action.*/
   
  return(E_NOT_OK);
}

/***********************************************************************************************************************
** Function Name         : CanXL_UpdatePhysAddrFilter
**
** Service ID            : 0x12
**
** Description           : Update the physical source address to/from the
**                         indexed controller filter.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant for the same CtrlIdx,
**                         reentrant for different
**
** Input Parameters      : CtrlIdx:    Index of the controller
**                         PhyAddrPtr: Pointer to memory containing the physical
**                                     destination address (MAC address)
**                                     in network byte order.
**                         Action:     Add or remove the address from the
**                                     Ethernet controllers
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : Std_ReturnType
**                         E_OK: filter was successfully changed
**                         E_NOT_OK: filter could not be changed
**
** Preconditions         : Component Requires previous controller initialization
**                         using Can_Init..
**
** Global Variables Used : CanXL_GaaCtrlStat, CanXL_GstBroadcastAddr,
**                         CanXL_GstNullAddr, Can_GpPCController
**
** Function(s) invoked   : Det_ReportError, CanXL_CommonDetCheck,
**                         CanXL_AddAddressFilter, CanXL_RemoveAddressFilter,
**
** Registers Used        : None
**
** Reference ID          : CAN_DUD_ACT_148
** Reference ID          : CAN_DUD_ACT_148_ERR001
***********************************************************************************************************************/
FUNC(Std_ReturnType, CAN_PUBLIC_CODE) CanXL_UpdatePhysAddrFilter (uint8 CtrlIdx,                                        /* PRQA S 1503 # JV-01 */
                                                                  const uint8* PhysAddrPtr, Eth_FilterActionType Action)
{
  CanXL_MacAddressType LstMacAddr;
  Std_ReturnType LucReturnValue;
  VAR(uint8, AUTOMATIC) LucChannelId;
  VAR(uint8, AUTOMATIC) LucCtrlInfoIndex;
#if (CAN_DEV_ERROR_DETECT == STD_ON)
  LucReturnValue = CanXL_CommonDetCheck(CANXL_UPDATEPHYSADDRFILTER_SID, CtrlIdx);
  /* Report Error to DET, if the PhysAddrPtr pointer value is NULL */
  if (NULL_PTR == PhysAddrPtr)
  {
    (void)Det_ReportError(CANXL_MODULE_ID, CANXL_INSTANCE_ID, CANXL_UPDATEPHYSADDRFILTER_SID, CANXL_E_PARAM_POINTER);
    LucReturnValue = E_NOT_OK;
  } /* else no action required*/

  if (E_OK != LucReturnValue)
  {
    /* No action required */
  }
  else
#endif /* (CAN_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Get channel index of CANXL */
    LucChannelId = Can_GpPCController[CtrlIdx].ucCh;
    LucCtrlInfoIndex = Can_GpConfig->pCanXLSecondPhysicalControllerToIndex[LucChannelId];
    /* Pack MAC address from user to the structure to be compared */
    CANXL_PACK_ADDRESS_FROM_8(PhysAddrPtr, LstMacAddr);                                                                 /* PRQA S 3469 # JV-01 */

    if (ETH_ADD_TO_FILTER == Action)
    {
      LucReturnValue = CanXL_AddAddressFilter((uint32)LucCtrlInfoIndex, &LstMacAddr);
    }
    else
    {
      LucReturnValue = CanXL_RemoveAddressFilter((uint32)LucCtrlInfoIndex, &LstMacAddr);
    }
      
#if (CAN_DEV_ERROR_DETECT == STD_ON)
    /* If the specified address is not registered, report error */
    if (E_OK != LucReturnValue)
    {
      (void)Det_ReportError(CANXL_MODULE_ID, CANXL_INSTANCE_ID,
            CANXL_UPDATEPHYSADDRFILTER_SID, CANXL_E_INV_PARAM);
    } /* else no action required*/
#endif /* (CAN_DEV_ERROR_DETECT == STD_ON */
  }

  return LucReturnValue;
}

/***********************************************************************************************************************
** Function Name         : CanXL_TxConfirmation
**
** Service ID            : 0x0C
**
** Description           : This API Triggers frame transmission confirmation
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : CtrlIdx: Index of the controller
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : Component Requires previous controller initialization
**                         using Can_Init.
**
** Global Variables Used : CanXL_GaaCtrlStat, Can_GpPCController.
**
** Function(s) invoked   : Det_ReportError, CanXL_CommonDetCheck,
**                         CanXL_HwTxConfirmation
**
** Registers Used        : None
**
** Reference ID          : CAN_DUD_ACT_149
** Reference ID          : CAN_DUD_ACT_149_ERR001
***********************************************************************************************************************/
FUNC(void, CAN_PUBLIC_CODE) CanXL_TxConfirmation (uint8 CtrlIdx)                                                        /* PRQA S 1503 # JV-01 */
{
  VAR(uint8, AUTOMATIC) LucChannelId;
  VAR(uint8, AUTOMATIC) LucCtrlInfoIndex;
  #if (CAN_DEV_ERROR_DETECT == STD_ON)
  Std_ReturnType LucReturnValue;
  LucReturnValue = CanXL_CommonDetCheck(CANXL_TXCONFIRMATION_SID, CtrlIdx);
  if (E_OK != LucReturnValue)
  {
    /* No action required */
  }
  else
  #endif
  {
    /* Get channel index of CANXL */
    LucChannelId = Can_GpPCController[CtrlIdx].ucCh;
    LucCtrlInfoIndex = Can_GpConfig->pCanXLSecondPhysicalControllerToIndex[LucChannelId];
    /* Report Error to DET, if the controller mode Is not Active */
    if ((ETH_MODE_ACTIVE != CanXL_GaaCtrlStat[LucCtrlInfoIndex].enMode)
         || (CAN_COMMON_STATE_STARTED != Can_GaaCtrlState[CtrlIdx].enMode))
    {
      #if (CAN_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CANXL_MODULE_ID, CANXL_INSTANCE_ID, CANXL_TXCONFIRMATION_SID, CANXL_E_INV_MODE);
      #endif
    }
    else
    {
      /* Check if this controller is not Tx interrupt mode */
      if(0U == (Can_GpPCController[CtrlIdx].ucIntEnable & CAN_CHECK_INT_TX))                                            /* PRQA S 3416 # JV-01 */
      {
        CanXL_HwTxConfirmation((uint32)LucCtrlInfoIndex);
      } /* else no action required*/
    }
  }
}
#define CAN_STOP_SEC_PUBLIC_CODE
#include "Can_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* CAN_CANXL_SUPPORTED */

#if (CAN_CANXL_SUPPORTED == STD_ON)
#define CAN_START_SEC_PRIVATE_CODE
#include "Can_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : CanXL_CommonDetCheck
**
** Service ID            : Not Applicable
**
** Description           : Perform DET checking for Controller ID
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LulSID        : Service ID
**                         LucController : Controller ID
**
** Output Parameters     : None
**
** Return parameter      : Can_CommonReturnType (CAN_COMMON_OK / CAN_COMMON_NOT_OK)
**
** Preconditions         : None
**
** Global Variables Used : Can_GblInitialized, Can_GpConfig
**                         Can_GpPCController
**
** Functions Invoked     : Det_ReportError
**
** Registers Used        : None
**
** Reference ID          : CAN_DUD_ACT_150
** Reference ID          : CAN_DUD_ACT_150_GBL001, CAN_DUD_ACT_150_ERR003
** Reference ID          : CAN_DUD_ACT_150_ERR001, CAN_DUD_ACT_150_ERR002
***********************************************************************************************************************/
#if (CAN_DEV_ERROR_DETECT == STD_ON)
STATIC FUNC(Can_CommonReturnType, CAN_PRIVATE_CODE) CanXL_CommonDetCheck(
  CONST(uint8, AUTOMATIC) LucSID, CONST(uint8, AUTOMATIC) LucController)
{
  VAR(Can_CommonReturnType, AUTOMATIC) LenReturnValue;

  #if (CAN_MULTI_CORE_SUPPORT == STD_ON)
  VAR(uint8, AUTOMATIC) LucCoreId;
  /* Get Core id for code branching */
  LucCoreId = (uint8)GetCoreID();
  #endif /* #if (CAN_MULTI_CORE_SUPPORT == STD_ON) */

  /* Report to DET, if module is not initialized */
  if (CAN_FALSE == Can_GblInitialized)                                                                                  /* PRQA S 3416 # JV-01 */
  {
    (void)Det_ReportError(CANXL_MODULE_ID, CANXL_INSTANCE_ID, LucSID, CANXL_E_UNINIT);
    LenReturnValue = CAN_COMMON_NOT_OK;
  }
  /* Report to DET, if the Controller Id is out of range */
  else if ((Can_GpConfig->ucNoOfControllers <= LucController) ||                                                        /* PRQA S 3416 # JV-01 */
           (CAN_FALSE == Can_GpPCController[LucController].blActivation))                                               /* PRQA S 3415, 3416 # JV-01, JV-01 */
  {
    (void)Det_ReportError(CANXL_MODULE_ID, CANXL_INSTANCE_ID, LucSID, CANXL_E_PARAM_CONTROLLER);
    LenReturnValue = CAN_COMMON_NOT_OK;
  }
  else if (CAN_XL != Can_GpPCController[LucController].enControllerType)                                                /* PRQA S 3415, 3416 # JV-01, JV-01 */
  {
    (void)Det_ReportError(CANXL_MODULE_ID, CANXL_INSTANCE_ID, LucSID, CANXL_E_PARAM_CONTROLLER);
    LenReturnValue = CAN_COMMON_NOT_OK;
  }
  #if (CAN_MULTI_CORE_SUPPORT == STD_ON)
  else if(LucCoreId != Can_GpPBController[LucController].ucCoreId)                                                      /* PRQA S 3416 # JV-01 */
  {
    /* Report to DET */
    (void)Det_ReportError(CANXL_MODULE_ID, CANXL_INSTANCE_ID, LucSID, CANXL_E_INVALID_CORE);
    LenReturnValue = CAN_COMMON_NOT_OK;
  }
  #endif
  else
  {
    LenReturnValue = CAN_COMMON_OK;
  }

  return LenReturnValue;
}
#endif /* (CAN_DEV_ERROR_DETECT == STD_ON) */
#if(CAN_CANXL_GLOBAL_TIME_SUPPORT == STD_ON)
/*******************************************************************************
** Function Name         : CanXL_HwGetIngressTimeStamp
**
** Service ID            : NA
**
** Description           : Read TimeStamp from a message received and
**                         store in Autosar Format
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant for the same Ctrl ,
**                         Re-entrant for different
**
** Input Parameters      : LulCtrlIdx     : Index of a controller
**                         LpDataPtr      : Pointer to the message buffer,
**                                          where Application expects ingress time stamping
**
** InOut Parameters      : None
**
** Output Parameters     : LpTimeQualPtr  : Quality of the Time Stamp
**                       : LpTimeStampPtr : TS read from the Rx Descriptor.
**
** Return parameter      : LucReturnValue E_OK / E_NOT_OK
**
** Preconditions         : Component Requires previous controller
**                         initialization using Can_Init.
**
** Global Variables Used : CanXL_GaaRxFrame
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : CAN_DUD_ACT_142
*******************************************************************************/
STATIC FUNC(Std_ReturnType, CAN_PRIVATE_CODE) CanXL_HwGetIngressTimeStamp(
  CONST(uint32, AUTOMATIC) LulCtrlIdx,
  CONSTP2CONST(Eth_DataType, AUTOMATIC, CAN_APPL_DATA) LpDataPtr,
  CONSTP2VAR(Eth_TimeStampQualType, AUTOMATIC, CAN_APPL_DATA) LpTimeQualPtr,                                            /* PRQA S 3432 # JV-01 */
  CONSTP2VAR(Eth_TimeStampType, AUTOMATIC, CAN_APPL_DATA) LpTimeStampPtr)                                               /* PRQA S 3432 # JV-01 */
{
  P2CONST(Eth_DataType, AUTOMATIC, CAN_APPL_DATA) LpCompPtr;

  Std_ReturnType LucReturnValue = E_NOT_OK;
  /* Read TimeStamp from the rxframe.Timestamp */
  LpCompPtr = (Eth_DataType *)(CanXL_GaaRxFrame[LulCtrlIdx].ulFrameAddr + CANXL_HEADER_SIZE);                           /* PRQA S 0306, 3383 # JV-01, JV-01 */

  if (LpCompPtr == LpDataPtr)
  {
    LpTimeStampPtr->nanoseconds = CanXL_GaaRxFrame[LulCtrlIdx].stTimestamp.ulElement2TS0;
    LpTimeStampPtr->seconds = CanXL_GaaRxFrame[LulCtrlIdx].stTimestamp.ulElement3TS1;

    /* In CANXL, secondsHi is invalid. */
    LpTimeStampPtr->secondsHi = 0;

    /* TimeStamp is valid  */
    *LpTimeQualPtr = ETH_VALID;
    LucReturnValue = E_OK;
  }
  else
  {
    LpTimeStampPtr->nanoseconds = 0U;
    LpTimeStampPtr->seconds = 0U;
    LpTimeStampPtr->secondsHi = 0U;
    /* TimeStamp is invalid  */
    *LpTimeQualPtr = ETH_INVALID;
  }
  return (LucReturnValue);
}

/*******************************************************************************
** Function Name         : CanXL_HwGetEgressTimeStamp
**
** Service ID            : NA
**
** Description           : Read TimeStamp from a message just transmitted
**                         if tag match with Buf idx
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant for the same Ctrl ,
**                         Re-entrant for different
**
** Input Parameters      : LulCtrlIdx     : Index of a controller
**                       : LulBufIdx      : Index of the message buffer
**
** InOut Parameters      : None
**
** Output Parameters     : LpTimeQualPtr  : Quality of the Read TS
**                       : LpTimeStampPtr : Value passed above
**
** Return parameter      : LucReturnValue E_OK / E_NOT_OK
**
** Preconditions         : Component Requires previous controller
**                         initialization using Can_Init.
**
** Global Variable(s)    : CanXL_GaaTxBufferMgrTable
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : CAN_DUD_ACT_143, CAN_DUD_ACT_143_GBL001
*******************************************************************************/
STATIC FUNC(Std_ReturnType, CAN_PRIVATE_CODE) CanXL_HwGetEgressTimeStamp(
  CONST(uint32, AUTOMATIC) LulCtrlIdx,
  CONST(Eth_BufIdxType, AUTOMATIC) LulBufIdx,
  CONSTP2VAR(Eth_TimeStampQualType, AUTOMATIC, CAN_APPL_DATA) LpTimeQualPtr,                                            /* PRQA S 3432 # JV-01 */
  CONSTP2VAR(Eth_TimeStampType, AUTOMATIC, CAN_APPL_DATA) LpTimeStampPtr)                                               /* PRQA S 3432 # JV-01 */
{
  P2CONST(CanXL_BufHandlerType, AUTOMATIC, CAN_APPL_DATA) LpTxBufferNode;

  /* Initialize pointer to timestamp buffer */
  LpTxBufferNode = (CanXL_BufHandlerType *)CanXL_GaaTxBufferMgrTable[LulCtrlIdx][LulBufIdx].pBufferHdr;

  *LpTimeQualPtr = LpTxBufferNode->enTimeQual;

  *LpTimeStampPtr = LpTxBufferNode->stTimeStamp;

  return (E_OK);
}
#endif /* CAN_CANXL_GLOBAL_TIME_SUPPORT */
/***********************************************************************************************************************
** Function Name         : Can_CanXLInit
**
** Service ID            : N/A
**
** Description           : Initialize HW Unit for CAN XL Driver
**
** Sync/Async            : None
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LucControllerID - Controller index
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : CAN_TRUE/CAN_FALSE
**
** Preconditions         : None
**
** Global Variables Used : Can_GpPCController, CanXL_GaaRegs, CanXL_GaaCtrlStat
**
** Functions Invoked     : CanXL_InitMHModule, Can_WaitRegisterChange, CAN_DEM_REPORT_ERROR, CanXL_HWSettingRXFilter,
**                         CanXL_InitializeBuffer, CanXL_ClearAllAddressFilters
**
** Registers Used        : ulCXLCCLKC
**
** Reference ID          : CAN_DUD_ACT_125
** Reference ID          : CAN_DUD_ACT_125_GBL001, CAN_DUD_ACT_125_GBL002
** Reference ID          : CAN_DUD_ACT_125_ERR001, CAN_DUD_ACT_125_ERR002, CAN_DUD_ACT_125_ERR003
***********************************************************************************************************************/
FUNC(boolean, CAN_PRIVATE_CODE) Can_CanXLInit (CONST(uint8, AUTOMATIC) LucControllerID)
{
  VAR(Std_ReturnType, AUTOMATIC) LucTimeoutResult;
  VAR(boolean, AUTOMATIC) LblErrFlag;
  VAR(uint32, AUTOMATIC) LulTimeoutDuration;
  VAR(uint8, AUTOMATIC) LucController;
  VAR(uint8, AUTOMATIC) LucCtrlInfoIndex;
  
  LblErrFlag = CAN_FALSE;                                                                                               /* PRQA S 2982 # JV-01 */
  LucController = Can_GpPCController[LucControllerID].ucCh;
  LucCtrlInfoIndex = Can_GpConfig->pCanXLSecondPhysicalControllerToIndex[LucController];
  /*************************************** Initiliaze for ETH Frame ***************************************************/
  /* Initialize controller state as DOWN */
  CanXL_GaaCtrlStat[LucCtrlInfoIndex].enMode = ETH_MODE_DOWN;
  
  /* Initialize TxBuffer */
  CanXL_InitializeBuffer(LucCtrlInfoIndex);
  /* Initialize Address filters */
  CanXL_ClearAllAddressFilters(LucCtrlInfoIndex);
  
  /******************************************** Initiliaze HW CANXL ***************************************************/
  /**
   * 1. Confirm if RAM Initialization is finished
  */
  LulTimeoutDuration = CAN_TIMEOUT_COUNT;
  
  LucTimeoutResult = Can_WaitRegisterChange(&CanXL_GaaRegs[LucCtrlInfoIndex].pGLB->ulCXLGSTS,
                                            CAN_CXLGSTS_LRAMINIT_MASK, 0UL, &LulTimeoutDuration);
  /* If LRAMINIT flag was not set, report error */
  if (E_OK != LucTimeoutResult)
  {
    #if defined(CAN_E_TIMEOUT_FAILURE)
    CAN_DEM_REPORT_ERROR(CAN_E_TIMEOUT_FAILURE, DEM_EVENT_STATUS_FAILED);
    #endif
    LblErrFlag = CAN_TRUE;
  }
  else
  {
    /**
     * 2. Enable clock: Host clock, Can Clock and Time base clock (write 32'h0000_C407 to CXLCCLKC)
    */
    CanXL_GaaRegs[LucCtrlInfoIndex].pGLB->ulCXLCCLKC = 0xC400UL;
    CanXL_GaaRegs[LucCtrlInfoIndex].pGLB->ulCXLCCLKC = (uint32)(CAN_CXLCCLKC_KEY_VALUE | 
                                                             CAN_CXLCCLKC_HCLKC_MASK |
                                                             CAN_CXLCCLKC_CCLKC_MASK |
                                                             CAN_CXLCCLKC_TCLKC_MASK);
    /**
    * 3. RX filter settings */
    /* Set the base address of the RX Filter elements */
    CanXL_HWSettingRXFilter(LucControllerID);
    /**
    * 4. Check that the XCAN clock is valid
    * - MH_STS.CLOCK_ACTIVE = 1
    * - STAT.CLKA = 1
    */

    LulTimeoutDuration = CAN_TIMEOUT_COUNT;
    /* Waiting Clock active */
    LucTimeoutResult = Can_WaitRegisterChange(&CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulSTS,
                                              CAN_MH_STS_CLOCK_ACTIVE, CAN_MH_STS_CLOCK_ACTIVE, &LulTimeoutDuration);
    /* If LRAMINIT flag was not set, report error */
    if (E_OK != LucTimeoutResult)
    {
      #if defined(CAN_E_TIMEOUT_FAILURE)
      CAN_DEM_REPORT_ERROR(CAN_E_TIMEOUT_FAILURE, DEM_EVENT_STATUS_FAILED);
      #endif
      LblErrFlag = CAN_TRUE;
    }
    else
    {
      LulTimeoutDuration = CAN_TIMEOUT_COUNT;
    /* Waiting status Clock */
      LucTimeoutResult = Can_WaitRegisterChange(&CanXL_GaaRegs[LucCtrlInfoIndex].pPRT->ulSTAT,
                                                CAN_STAT_CLKA, CAN_STAT_CLKA, &LulTimeoutDuration);
      /* If LRAMINIT flag was not set, report error */
      if (E_OK != LucTimeoutResult)
      {
        #if defined(CAN_E_TIMEOUT_FAILURE)
        CAN_DEM_REPORT_ERROR(CAN_E_TIMEOUT_FAILURE, DEM_EVENT_STATUS_FAILED);
        #endif
        LblErrFlag = CAN_TRUE;
      }
      else
      {
        /* Initialize Message Handler */
        LblErrFlag = CanXL_InitMHModule(LucControllerID);
      }
    }
  }
  return LblErrFlag;
}
/***********************************************************************************************************************
** Function Name         : CanXL_StartMode
**
** Service ID            : N/A
**
** Description           : Specific for starting Can Xl Controller
**
** Sync/Async            : None
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LucController - COntroller index
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : None
**
** Preconditions         : None
**
** Global Variables Used : CanXL_GaaRegs, Can_GpConfig, Can_GaaCtrlState
**
** Functions Invoked     : Can_WaitRegisterChange, CanIf_ControllerModeIndication
**
** Registers Used        : MH_CTRL, RX_FQ_CTRL2, RX_FQ_CTRL0, RX_FQ_STS0, MH_STS
**
** Reference ID          : CAN_DUD_ACT_126
** Reference ID          : CAN_DUD_ACT_126_GBL001, CAN_DUD_ACT_126_GBL002, CAN_DUD_ACT_126_REG001,
** Reference ID          : CAN_DUD_ACT_126_REG002, CAN_DUD_ACT_126_REG003.
***********************************************************************************************************************/
FUNC(void, CAN_PRIVATE_CODE) CanXL_StartMode (uint8 LucController)
{
  /* Define return value */
  VAR(uint32, AUTOMATIC) LulTimeoutDuration;
  VAR(Std_ReturnType, AUTOMATIC) LenReturnValue;
  VAR(uint8, AUTOMATIC) LucCtrlIndex;
  VAR(uint8, AUTOMATIC) LucCtrlInfoIndex;
  VAR(uint8, AUTOMATIC) LucTransceiverID;
  P2CONST(Can_CanXLHWUnitInfoType, AUTOMATIC, CAN_CONFIG_DATA) LpCanXLHWInfo;
  VAR(Can_SubStatusType, AUTOMATIC) LenSubState;

  LenReturnValue = E_OK;                                                                                                /* PRQA S 2982 # JV-01 */
  LenSubState = Can_GaaCtrlState[LucController].enSubState;
  LucCtrlIndex = Can_GpPCController[LucController].ucCh;
  LucCtrlInfoIndex = Can_GpConfig->pCanXLSecondPhysicalControllerToIndex[LucCtrlIndex]; 
  /* Get PBConfig data for this CANXL unit */
  LpCanXLHWInfo = (P2CONST(Can_CanXLHWUnitInfoType, AUTOMATIC, CAN_CONFIG_DATA))Can_GpConfig->pCanXLHWUnitInfo;         /* PRQA S 0316 # JV-01 */
  
  /* INITIALIZATION OF DESCRIPTORS and buffers */
  CanXL_HwDescriptorInit(LucCtrlIndex);
  CanXL_InitializeBuffer(LucCtrlInfoIndex);
  /* Start the Message Handler */
  CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulCTRL = CAN_MH_START;
  
  if(0UL != LpCanXLHWInfo[LucCtrlInfoIndex].ulRXFQUsed)
  {
    if(CAN_NO_PENDING_TRANSITION == LenSubState)
    {
      LenSubState = CANXL_START_WAIT_RXQUEUE_START;
      /* Enable the RX FIFO Queue {n} before a start */
      CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulRXFQCTRL2 = LpCanXLHWInfo[LucCtrlInfoIndex].ulRXFQUsed;
      /* Start the RX FIFO Queue */
      CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulRXFQCTRL0 = LpCanXLHWInfo[LucCtrlInfoIndex].ulRXFQUsed;
  
      /* Check the BUSY bit of RX FIFO Status */
      LulTimeoutDuration = CAN_TIMEOUT_COUNT;
      LenReturnValue = Can_WaitRegisterChange(&CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulRXFQSTS0,
                     LpCanXLHWInfo[LucCtrlInfoIndex].ulRXFQUsed, LpCanXLHWInfo[LucCtrlInfoIndex].ulRXFQUsed,
                      &LulTimeoutDuration);
    }else if ((CANXL_START_WAIT_RXQUEUE_START == LenSubState) &&                                                        /* PRQA S 2004 # JV-01 */
      (LpCanXLHWInfo[LucCtrlInfoIndex].ulRXFQUsed != CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulRXFQSTS0))
    {
      LenReturnValue = E_NOT_OK;
    } /* else no action required*/
  } /* else no action required*/

  if ((E_OK == LenReturnValue) &&
        ((CAN_NO_PENDING_TRANSITION == LenSubState) || (CANXL_START_WAIT_RXQUEUE_START == LenSubState)))
  {
    LenSubState = CANXL_START_WAIT_PRT_START;
    /* Start the Protocol Controller */
    CanXL_GaaRegs[LucCtrlInfoIndex].pPRT->ulCTRL |= CAN_PRT_START;

    /* Check if the ENABLE signal is set high by the PRT */
    LulTimeoutDuration = CAN_TIMEOUT_COUNT;
    LenReturnValue = Can_WaitRegisterChange(&CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulSTS,
                                            CAN_MH_ENABLE_MASK, CAN_MH_ENABLE_MASK, &LulTimeoutDuration);
  }
  else if((CANXL_START_WAIT_PRT_START == LenSubState) &&                                                                /* PRQA S 2004 # JV-01 */
              (CAN_MH_ENABLE_MASK != (CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulSTS & CAN_MH_ENABLE_MASK)))                /* PRQA S 2004 # JV-01 */
  {
    LenReturnValue = E_NOT_OK;
  } /* else no action required*/

  /* Check CAN Bus_Off Recovery Sequence is done yet if Controller was in Bus-Off state before */
  if ((E_OK == LenReturnValue) && (CAN_TRUE == CanXL_GaaCtrlStat[LucCtrlInfoIndex].blErrorSignaling))
  {
    if (0UL != (CanXL_GaaRegs[LucCtrlInfoIndex].pPRT->ulSTAT & CAN_CANXL_BOEF))
    {
      if(CANXL_START_WAIT_PRT_START == LenSubState)
      {
        LenSubState = CANXL_START_WAIT_BUSOFF_RECOVERY;
      } /* else no action required*/
      LulTimeoutDuration = CAN_TIMEOUT_COUNT;
      LenReturnValue = Can_WaitRegisterChange(&CanXL_GaaRegs[LucCtrlInfoIndex].pPRT->ulSTAT,
                      CAN_CANXL_BOEF, 0, &LulTimeoutDuration);
    } /* else no action required*/
  } /* else no action required*/
  
  if (E_OK == LenReturnValue)
  {
    /* Trigger TX FIFO Queue to update current descriptor registor */
    /* Enable the TX FIFO Queue {n} before a start */
    CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulTXFQCTRL2 = LpCanXLHWInfo[LucCtrlInfoIndex].ulTXFQUsed;
    /* Start the TX FIFO Queue */
    CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulTXFQCTRL0 = LpCanXLHWInfo[LucCtrlInfoIndex].ulTXFQUsed;
    /* Inform the upper layer */
    Can_GaaCtrlState[LucController].enMode = CAN_COMMON_STATE_STARTED;
    Can_GaaCtrlState[LucController].enSubState = CAN_NO_PENDING_TRANSITION;
    if (CAN_TRUE == Can_GaaCtrlState[LucController].blBusOff)
    {
      Can_GaaCtrlState[LucController].blBusOff = CAN_FALSE;
      LucTransceiverID = LpCanXLHWInfo[LucCtrlInfoIndex].ucTransceiverID;
      (void)(CanXLTrcv_ReportErrorState(LucTransceiverID, CAN_ERRORSTATE_ACTIVE));
    } /* else no action required*/
    CanIf_ControllerModeIndication((uint8)(LucController + CAN_CONTROLLER_OFFSET), CAN_COMMON_IF_STATE_STARTED);        /* PRQA S 3383, 2985 # JV-01, JV-01 */
  }
  else
  {
    Can_GaaCtrlState[LucCtrlIndex].enSubState = LenSubState;
  }
}
/***********************************************************************************************************************
** Function Name         : CanXL_StopMode
**
** Service ID            : N/A
**
** Description           : Specific for stopping Can Xl Controller
**
** Sync/Async            : None
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LucController - COntroller index
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : None
**
** Preconditions         : None
**
** Global Variables Used : CanXL_GaaRegs, Can_GpConfig, Can_GaaCtrlState
**
** Functions Invoked     : CanIf_ControllerModeIndication
**
** Registers Used        : LOCK, AXI_PARAMS_CLOCK, PRT_CTRL, TX_PQ_CTRL1, TX_PQ_CTRL2, RX_FQ_CTRL1,
**                         RX_FQ_CTRL2, TX_FQ_CTRL1, TX_FQ_CTRL2, MH_CTRL.
**
** Reference ID          : CAN_DUD_ACT_127
** Reference ID          : CAN_DUD_ACT_127_REG001, CAN_DUD_ACT_127_REG002, CAN_DUD_ACT_127_REG003, 
** Reference ID          : CAN_DUD_ACT_127_REG004, CAN_DUD_ACT_127_REG005, CAN_DUD_ACT_127_REG006, 
** Reference ID          : CAN_DUD_ACT_127_GBL001, CAN_DUD_ACT_127_GBL002
***********************************************************************************************************************/
FUNC(void, CAN_PRIVATE_CODE) CanXL_StopMode(uint8 LucController)                                                        /* PRQA S 3006 # JV-01 */
{
  VAR(uint32, AUTOMATIC) LulTimeoutDuration;
  VAR(uint32, AUTOMATIC) LucCtrlIndex;
  Std_ReturnType LucReturnValue;
  P2CONST(Can_CanXLHWUnitInfoType, AUTOMATIC, CAN_CONFIG_DATA) LpCanXLHWInfo;
  VAR(uint8, AUTOMATIC) LucCtrlInfoIndex;
  VAR(Can_SubStatusType, AUTOMATIC) LenSubState;

  LucReturnValue = E_OK;                                                                                                /* PRQA S 2982 # JV-01 */
  LenSubState = Can_GaaCtrlState[LucController].enSubState;
  LucCtrlIndex = Can_GpPCController[LucController].ucCh;
  LucCtrlInfoIndex = Can_GpConfig->pCanXLSecondPhysicalControllerToIndex[LucCtrlIndex];
  LpCanXLHWInfo = (P2CONST(Can_CanXLHWUnitInfoType, AUTOMATIC, CAN_CONFIG_DATA))Can_GpConfig->pCanXLHWUnitInfo;         /* PRQA S 0316 # JV-01 */
  /**************************************************************************************************************/
  /**                                    Stop Protocol Controller                                              **/
  /**************************************************************************************************************/
  if (CAN_TENTATIVE_TRANSITION == LenSubState)
  {
    LenSubState = CANXL_STOP_WAIT_PRT_STOP;
    CanXL_GaaRegs[LucCtrlInfoIndex].pPRT->ulLOCK = (uint32)0x1234UL;
    CanXL_GaaRegs[LucCtrlInfoIndex].pPRT->ulLOCK = (uint32)0x4321UL;
    CanXL_GaaRegs[LucCtrlInfoIndex].pPRT->ulCTRL |= CAN_PRT_STOP;

    LulTimeoutDuration = CAN_TIMEOUT_COUNT;
    LucReturnValue = Can_WaitRegisterChange(&CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulSTS,
                                          CAN_MH_ENABLE_MASK, 0UL, &LulTimeoutDuration);
  }
  else if ((CANXL_STOP_WAIT_PRT_STOP == LenSubState) &&                                                                 /* PRQA S 2004 # JV-01 */
           (0UL != (CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulSTS & CAN_MH_ENABLE_MASK)))
  {
    LucReturnValue = E_NOT_OK;
  } /* else no action required*/

  /**************************************************************************************************************/
  /**                              Abort all TX Priority Queue slots                                           **/
  /**************************************************************************************************************/
  if ((E_OK == LucReturnValue) 
           && ((CANXL_STOP_WAIT_PRT_STOP == LenSubState) || (CANXL_STOP_WAIT_TXRXQUEUE_STOP == LenSubState)))
  {
    LenSubState = CANXL_STOP_WAIT_TXRXQUEUE_STOP;
    if ((CAN_TRUE == LpCanXLHWInfo[LucCtrlInfoIndex].blTxPQEnable) && 
         (CANXL_TX_PQ_CLEAR_ENABLE != CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulTXPQCTRL2))
    {
      /* Write 1 to the TX_PQ_CTRL1.ABORT[n] (n = {0, 1, ..., 31}) bit register */
      CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulLOCK = (uint32)0x1234UL;
      CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulLOCK = (uint32)0x4321UL;
      CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulTXPQCTRL1 = LpCanXLHWInfo[LucCtrlInfoIndex].ulTXPQUsed;

      /* DummyRead & SYNCP */
      RH850_SV_MODE_REG_READ_ONLY(32, &CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulTXPQSTS0);
      EXECUTE_SYNCP();                                                                                                  /* PRQA S 1006 # JV-01 */
 
      /* Wait for the TX_PQ_STS0.BUSY[n] (n = {0, 1, ..., 31}) bit status register to be set to 0 */
      if ((CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulTXPQSTS0 & CANXL_TX_PQ_STS_MASK) != CANXL_TX_PQ_NOT_BUSY)
      {
        /* Return E_NOT_Ok */
        LucReturnValue = E_NOT_OK;
      }
      else
      {
        /* Write 0 to the TX_PQ_CTRL1.ABORT[n] (n = {0, 1, ..., 31}) bit register */
        CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulLOCK = (uint32)0x1234UL;
        CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulLOCK = (uint32)0x4321UL;
        CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulTXPQCTRL1 = CANXL_TX_PQ_CLEAR_ABORT;

        /* Set the TX_PQ_CTRL2.ENABLE[n] (n = {0, 1, ..., 31}) back to 0 to protect the TX Priority Queue slot n from
        being restarted */
        CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulTXPQCTRL2 = CANXL_TX_PQ_CLEAR_ENABLE;
      }
    } /* else no action required*/
    /**************************************************************************************************************/
    /**                                   Abort all RX FIFO Queues                                               **/
    /**************************************************************************************************************/
    if ((E_OK == LucReturnValue) && (CANXL_RX_FIFO_QUEUE_DISABLE != CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulRXFQCTRL2))
    {
      /* Write 1 to the RX_FQ_CTRL1.ABORT[n] (n = {0, 1, ..., 7}) bit register (the RX_FQ_CTRL2.ENABLE[n] bit register
      must be still set to 1) */
      CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulLOCK = (uint32)0x1234UL;
      CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulLOCK = (uint32)0x4321UL;
      CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulRXFQCTRL1 = LpCanXLHWInfo[LucCtrlInfoIndex].ulRXFQUsed;

      /* Wait for the RX_FQ_STS0.BUSY[n] and RX_FQ_STS0.STOP[n] (n = {0, 1, ..., 7}) bit status register to be set to
      0. All status bit registers related to the RX FIFO Queue n are cleared, RX_FQ_STS1.ERROR[n] and
      RX_FQ_STS1.UNVALID[n] are set to 0. Once done the RX FIFO Queue n is considered as no more active */
      /* DummyRead & SYNCP */
      RH850_SV_MODE_REG_READ_ONLY(32, &CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulRXFQSTS0);
      EXECUTE_SYNCP();                                                                                                  /* PRQA S 1006 # JV-01 */

      /* DummyRead & SYNCP */
      RH850_SV_MODE_REG_READ_ONLY(32, &CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulRXFQSTS1);
      EXECUTE_SYNCP();                                                                                                  /* PRQA S 1006 # JV-01 */

      if((CANXL_RX_FQ_NOT_BUSY == (CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulRXFQSTS0 & CANXL_RX_FQ_STS_MASK)) && 
        (CANXL_RX_FQ_NOT_ON_HOLD == (CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulRXFQSTS1 &CANXL_RX_FQ_STS_MASK)))
      {
        /* Write 0 to the RX_FQ_CTRL1.ABORT[n] (n = {0, 1, ..., 7}) bit register */
        CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulLOCK = (uint32)0x1234UL;
        CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulLOCK = (uint32)0x4321UL;
        CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulRXFQCTRL1 = CANXL_RX_FQ_CLEAR_ABORT;

        /* Set the RX_FQ_CTRL2.ENABLE[n] (n = {0, 1, ..., 7}) bit register back to 0 to protect the RX
        FIFO Queue n from being restarted */
        CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulRXFQCTRL2 = CANXL_RX_FIFO_QUEUE_DISABLE;
      }
      else
      {
        /* Return E_NOT_Ok */
        LucReturnValue = E_NOT_OK;
      }
    } /* else no action required*/
    /**************************************************************************************************************/
    /**                                   Abort all TX FIFO Queues                                               **/
    /**************************************************************************************************************/
    if ((CAN_TRUE == LpCanXLHWInfo[LucCtrlInfoIndex].blTxFQEnable) && (E_OK == LucReturnValue)
        && (CANXL_TX_FIFO_QUEUE_DISABLE != CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulTXFQCTRL2))
    {
      /* Write 1 to the TX_FQ_CTRL1.ABORT[n] (n = {0, 1, ..., 7}) bit register */
      CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulLOCK = (uint32)0x1234UL;
      CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulLOCK = (uint32)0x4321UL;
      CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulTXFQCTRL1 = LpCanXLHWInfo[LucCtrlInfoIndex].ulTXFQUsed; 

      /* Wait for the TX_FQ_STS0.BUSY[n] and TX_FQ_STS0.STOP[n](n = {0,1,..,7}) bit status register to be set to 0 */
      /* DummyRead & SYNCP */
      RH850_SV_MODE_REG_READ_ONLY(32, &CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulTXFQSTS0);
      EXECUTE_SYNCP();                                                                                                  /* PRQA S 1006 # JV-01 */

      if(CANXL_TX_FQ_NOT_BUSY == (CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulTXFQSTS0 & CANXL_TX_FQ_STS_MASK))
      {
        /* Write 0 to the TX_FQ_CTRL1.ABORT[n] (n = {0, 1, ..., 7}) bit register */
        CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulLOCK = (uint32)0x1234UL;
        CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulLOCK = (uint32)0x4321UL;
        CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulTXFQCTRL1 = CANXL_TX_FQ_CLEAR_ABORT;

        /* Set the TX_FQ_CTRL2.ENABLE[n] (n = {0, 1, ..., 7}) bit register back to 0 to protect the TX FIFO Queue
        n from being restarted*/
        CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulTXFQCTRL2 = CANXL_TX_FIFO_QUEUE_DISABLE;
      }
      else
      {
        /* Return E_NOT_Ok */
        LucReturnValue = E_NOT_OK;
      }
    } /* else no action required*/
  }
  /**************************************************************************************************************/
  /**                                       Stop Message Handler                                               **/
  /**************************************************************************************************************/
  /* Unlocks the MH global configuration registers */
  if (E_OK == LucReturnValue)
  {
    if(CANXL_STOP_WAIT_TXRXQUEUE_STOP == LenSubState)
    {
      LenSubState = CANXL_STOP_WAIT_MH_STOP;
      CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulCTRL &= (~CAN_MH_START);
      /* Wait for the TX_FQ_STS0.BUSY[n] and TX_FQ_STS0.STOP[n] (n = {0, 1, ..., 7}) 
         bit status register to be set to 0 */
      /* DummyRead & SYNCP */
      RH850_SV_MODE_REG_READ_ONLY(32, &CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulSTS);
      EXECUTE_SYNCP();                                                                                                  /* PRQA S 1006 # JV-01 */
    } /* else no action required*/
    
    if(CAN_MH_STS_CLOCK_ACTIVE != (CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulSTS | CAN_MH_STS_CLOCK_ACTIVE))
    {
      /* Return E_NOT_OK */
      LucReturnValue = E_NOT_OK;
    } /* else no action required*/
  } /* else no action required*/
  
  if (E_OK == LucReturnValue)
  {
    /* Set the Controller to stop mode */
    Can_GaaCtrlState[LucController].enMode = CAN_COMMON_STATE_STOPPED;
    Can_GaaCtrlState[LucController].enSubState = CAN_NO_PENDING_TRANSITION;

    if(CAN_TRUE != Can_GaaCtrlState[LucController].blBusOff)
    {
      /* Indicate mode change to CanIf */
      CanIf_ControllerModeIndication((uint8)(LucController + CAN_CONTROLLER_OFFSET), CAN_COMMON_IF_STATE_STOPPED);      /* PRQA S 3383, 2985 # JV-01, JV-01 */
    } /* else no action required*/
  }
  else
  {
    Can_GaaCtrlState[LucController].enSubState = LenSubState;
  }
}
/***********************************************************************************************************************
** Function Name         : CanXL_InitMHModule
**
** Service ID            : To be defined
**
** Description           : Initialize Message Handler of CANXL module.
**
** Sync/Async            : None
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LucController - COntroller index
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : CAN_TRUE/CAN_FALSE
**
** Preconditions         : None
**
** Global Variables Used : CanXL_GaaRegs, Can_GpConfig, CanXL_GaaCtrlStat, Can_GpPCController,
**                         CanXL_GaaMemPoolBufferTable, CanXL_GaaRamSize
**
** Functions Invoked     : CanXL_HwDescriptorInit, CanXL_RamInit
**
** Registers Used        : MH_CFG, MH_SFTY_CFG, MH_SFTY_CTRL, AXI_ADD_EXT, AXI_PARAMS,
**                         RX_STATISTICS, TX_STATISTICS, FUNC_ENA, ERR_ENA, SAFETY_ENA, MODE, NBTP, DBTP, XBTP, PCFG
**                         RX_FQ_START_ADD, RX_FQ_SIZE, TX_FQ_START_ADD, TX_FQ_SIZE, TX_PQ_START_ADD.
**
** Reference ID          : CAN_DUD_ACT_128
** Reference ID          : CAN_DUD_ACT_128_REG001, CAN_DUD_ACT_128_REG002, CAN_DUD_ACT_128_REG003, 
** Reference ID          : CAN_DUD_ACT_128_REG004, CAN_DUD_ACT_128_REG005, CAN_DUD_ACT_128_REG006, 
** Reference ID          : CAN_DUD_ACT_128_REG007, CAN_DUD_ACT_128_REG014, CAN_DUD_ACT_128_REG015, 
** Reference ID          : CAN_DUD_ACT_128_REG018, CAN_DUD_ACT_128_REG019, CAN_DUD_ACT_128_REG020, 
** Reference ID          : CAN_DUD_ACT_128_REG022, CAN_DUD_ACT_128_REG023, CAN_DUD_ACT_128_REG024, 
** Reference ID          : CAN_DUD_ACT_128_REG026, CAN_DUD_ACT_128_REG027, CAN_DUD_ACT_128_REG021, 
** Reference ID          : CAN_DUD_ACT_128_REG028, CAN_DUD_ACT_128_REG029, CAN_DUD_ACT_128_REG030, 
** Reference ID          : CAN_DUD_ACT_128_GBL001, CAN_DUD_ACT_128_GBL002, CAN_DUD_ACT_128_GBL003
***********************************************************************************************************************/
STATIC FUNC(boolean, CAN_PRIVATE_CODE) CanXL_InitMHModule(uint8 LucController)                                          /* PRQA S 3006 # JV-01 */
{
  VAR(uint16, AUTOMATIC) LusMaxNum;
  VAR(uint16, AUTOMATIC) LusPayload;
  VAR(uint8, AUTOMATIC) LucCount;
  VAR(uint8, AUTOMATIC) LucQueueIdx;
  VAR(boolean, AUTOMATIC) LblErrFlag;
  VAR(uint8, AUTOMATIC) LucCtrlIndex;
  VAR(uint8, AUTOMATIC) LucCtrlInfoIndex;
  P2CONST(Can_CanXLHWUnitInfoType, AUTOMATIC, CAN_CONFIG_DATA) LpCanXLHWInfo;
  P2CONST(Can_BaudrateConfigType, AUTOMATIC, CAN_APPL_DATA) LpBaudrateConfig;
  /* Get baudrate CANXL */
  LpBaudrateConfig = &Can_GpPBController[LucController].pBaudrateConfig[CAN_DEFAULT_BAUDRATE_INDEX];
  /* Get Controller index of CANXL */
  LucCtrlIndex = Can_GpPCController[LucController].ucCh;
  LucCtrlInfoIndex = Can_GpConfig->pCanXLSecondPhysicalControllerToIndex[LucCtrlIndex];
  LblErrFlag = CAN_FALSE;
  LucQueueIdx = 0U;                                                                                                     /* PRQA S 2982 # JV-01 */
  /* Get PBConfig data for this CANXL unit */
  LpCanXLHWInfo = (P2CONST(Can_CanXLHWUnitInfoType, AUTOMATIC, CAN_CONFIG_DATA))Can_GpConfig->pCanXLHWUnitInfo;         /* PRQA S 0316 # JV-01 */ 

  /* Copy the configured MAC address as inital value */
  CANXL_PACK_ADDRESS_FROM_8(LpCanXLHWInfo[LucCtrlInfoIndex].aaEthMACAddr,                                               /* PRQA S 3469 # JV-01 */ 
                                                  CanXL_GaaCtrlStat[LucCtrlInfoIndex].stMacAddr);
  
  /* Check if the Message Handler is not started */
  if(CAN_MH_INITIAL_VALUE == (CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulSTS & CAN_MH_START))
  {
    /**************************************************************************************************************/
    /**                              INITIALIZATION OF MH GLOBAL REGISTER                                        **/
    /**************************************************************************************************************/
    /* Initialize Instance number and number of TX message re-tranmission for MH_CFG register */
    CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulCFG = LpCanXLHWInfo[LucCtrlInfoIndex].ulGCFG;

    /* Initialize MH_SFTY register */
    /* Setting maximum timeout for DMA_AXI/MEM_AXI/(RX/TX)_MSG Interface until 
       a read or write access has to be completed*/
    CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulSFTYCFG  = LpCanXLHWInfo[LucCtrlInfoIndex].ulSTYCFG;
    CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulSFTYCTRL = LpCanXLHWInfo[LucCtrlInfoIndex].ulSTYCTRL;

    /* Initialize AXI register */
    /* Define the MSB of the read/write AXI address bus used on the DMA_AXI interface
       If the AXI address is up to 64bit this register is used */
    CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulAXIADD = CANXL_MH_AXIADD_DEFAULT;
    /* Define the maximum read/write pending transactions on DMA_AXI interface */
    CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulAXIPAR = LpCanXLHWInfo[LucCtrlInfoIndex].ulAXIPARAM;

    /* Set the successful/unsuccessful transmission counter of TX/RX to 0 */
    CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulRXSTAT = CAN_MH_INITIAL_VALUE;
    CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulTXSTAT = CAN_MH_INITIAL_VALUE;

    /**************************************************************************************************************/
    /**                               INITIALIZATION OF RX FIFO QUEUES                                           **/
    /**************************************************************************************************************/
    /* Loop all RX FIFO Queue were configured. */
    for (LucCount = 0; (LucCount < LpCanXLHWInfo[LucCtrlInfoIndex].ucNoOfRxFIFOQueues) && 
                                                                            (CAN_FALSE == LblErrFlag); LucCount++)
    {
      /* Get Rx FIFO Queue index */
      LucQueueIdx = LpCanXLHWInfo[LucCtrlInfoIndex].pRxFIFOQueueConfig[LucCount].ucQueueId;
      LusMaxNum = LpCanXLHWInfo[LucCtrlInfoIndex].pRxFIFOQueueConfig[LucCount].usMaxNumDesc;
      LusPayload = LpCanXLHWInfo[LucCtrlInfoIndex].pRxFIFOQueueConfig[LucCount].usPayloadSize;
      /* Check if the RX FIFO Queue n is not busy */
      if (0UL == (CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulRXFQSTS0 & (uint32)(0x01UL << LucQueueIdx)))
      {
        /* Defines the address of the First RX Descriptor of the linked list */
        CanXL_GaaRegs[LucCtrlInfoIndex].pMH->aaRXFQReg[LucQueueIdx].ulRXSTADD = 
                                   (uint32)LpCanXLHWInfo[LucCtrlInfoIndex].pRxFIFOQueueConfig[LucCount].pStartAddress;  /* PRQA S 0306 # JV-01 */ 
        /* Provides the size of the linked list in number of RX descriptors and
        provides the size of the data container attached to every RX descriptor */
        CanXL_GaaRegs[LucCtrlInfoIndex].pMH->aaRXFQReg[LucQueueIdx].ulRXSIZE = 
                                                            CANXL_RXFIFO_SIZE((uint32)LusMaxNum, (uint32)LusPayload);
      }
      else
      {
        /* Return CAN_TRUE when the RX FIFO Queue {n} is busy */
        LblErrFlag = CAN_TRUE;
      }
    }
    /**************************************************************************************************************/
    /**                               INITIALIZATION OF TX FIFO QUEUES                                           **/
    /**************************************************************************************************************/
    /* Defines the base address to store the TX descriptors for the TX FIFO Queues and TX Priority Queue in L_RAM */
    CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulTXDADD = LpCanXLHWInfo[LucCtrlInfoIndex].ulTXDESCLMEM;
    /* Loop all TX FIFO Queue were configured. */
    for (LucCount = 0; (LucCount < LpCanXLHWInfo[LucCtrlInfoIndex].ucNoOfTxFIFOQueues) && 
                                                                            (CAN_FALSE == LblErrFlag); LucCount++)
    {
      /* Get Tx FIFO Queue index */
      LucQueueIdx = LpCanXLHWInfo[LucCtrlInfoIndex].pTxFIFOQueueConfig[LucCount].ucQueueId;
      /* Check if the TX FIFO Queue n is not busy */
      if (0UL == (CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulTXFQSTS0 & (uint32)(0x01UL << LucQueueIdx)))
      {
        /* Defines the address of the First TX Descriptor of the linked list*/
        CanXL_GaaRegs[LucCtrlInfoIndex].pMH->aaTXFQReg[LucQueueIdx].ulTXSTADD = 
                                (uint32)LpCanXLHWInfo[LucCtrlInfoIndex].pTxFIFOQueueConfig[LucCount].pStartAddress;     /* PRQA S 0306 # JV-01 */
        /* Provides the size of the linked list in number of TX descriptors */
        CanXL_GaaRegs[LucCtrlInfoIndex].pMH->aaTXFQReg[LucQueueIdx].ulTXSIZE = 
                                        LpCanXLHWInfo[LucCtrlInfoIndex].pTxFIFOQueueConfig[LucCount].usMaxNumDesc;
      }
      else
      {
        /* Return CAN_TRUE when the TX FIFO Queue {n} is busy */
        LblErrFlag = CAN_TRUE;
      }
    }
    /**************************************************************************************************************/
    /**                               INITIALIZATION OF TX PRIORITY QUEUE                                        **/
    /**************************************************************************************************************/
    if ((CANXL_TX_PQ_NOT_BUSY == (CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulTXPQSTS0 & CANXL_TX_PQ_STS_MASK)) && 
                                                                                      (CAN_FALSE == LblErrFlag))
    {
      /* Define the TX Priority Queue start address in the TX_PQ_START_ADD register */
      CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulTXPQSTADD = 
                      (uint32)LpCanXLHWInfo[LucCtrlInfoIndex].pTxPriorityQueueConfig->pStartAddress;                    /* PRQA S 0306 # JV-01 */ 
    }
    else
    {
      /* Return CAN_TRUE when the TX Priority Queue is busy */
      LblErrFlag = CAN_TRUE;
    }
    /**************************************************************************************************************/
    /**                               INITIALIZATION OF INTERRUPTION CONTROLLER                                  **/
    /**************************************************************************************************************/
    if (CAN_FALSE == LblErrFlag)
    {
      /* Enable interrupts */
      RH850_SV_MODE_ICR_AND(8, LpCanXLHWInfo[LucCtrlInfoIndex].pICFunc, (uint8)(~CAN_EIC_EIMK_MASK));                   /* PRQA S 0751 # JV-01 */
      RH850_SV_MODE_ICR_AND(8, LpCanXLHWInfo[LucCtrlInfoIndex].pICErr, (uint8)(~CAN_EIC_EIMK_MASK));                    /* PRQA S 0751 # JV-01 */
      /* DummyRead & SYNCP */
      RH850_SV_MODE_REG_READ_ONLY(16, LpCanXLHWInfo[LucCtrlInfoIndex].pICErr);
      EXECUTE_SYNCP();                                                                                                  /* PRQA S 1006 # JV-01 */
      /* Enable all events of Functional Interurpt */
      CanXL_GaaRegs[LucCtrlInfoIndex].pIRC->ulFUNCENA = LpCanXLHWInfo[LucCtrlInfoIndex].ulFUNCIRC;
      /* Enable all events of Error Interurpt */
      CanXL_GaaRegs[LucCtrlInfoIndex].pIRC->ulERRENA = LpCanXLHWInfo[LucCtrlInfoIndex].ulERRCIRC;
      /**************************************************************************************************************/
      /**                                 INITIALIZATION OF PROTOCOL CONTROLLER                                    **/
      /**************************************************************************************************************/
      /* MODE */
      /* Setting Operation Mode for Protocol Controller */
      CanXL_GaaRegs[LucCtrlInfoIndex].pPRT->ulMODE = LpCanXLHWInfo[LucCtrlInfoIndex].ulPRTMODE;
      /* Setting Time Stamp position */
      #if (CAN_CANXL_GLOBAL_TIME_SUPPORT == STD_ON)
      CanXL_GaaRegs[LucCtrlInfoIndex].pPRT->ulMODE |= CANXL_PRT_TIME_STAMP;
      #endif /* CAN_CANXL_GLOBAL_TIME_SUPPORT */

      /* NBTP */
      /* Setting Prescaler */
      /* Setting Phase Seg */
      /* Setting Nominal Synchronization Jump Width */
      CanXL_GaaRegs[LucCtrlInfoIndex].pPRT->ulNBTP = LpBaudrateConfig->ulCFG;

      /* DBTP */
      /* Setting Phase Seg */
      CanXL_GaaRegs[LucCtrlInfoIndex].pPRT->ulDBTP = LpBaudrateConfig->ulDCFG;
      /* Setting Nominal Synchronization Jump Width */
      /* Setting Transmitter Delay Compensation Offset for XL frames */

      /* XBTP */
      /* Setting Phase Seg */
      /* Setting Nominal Synchronization Jump Width */
      /* Setting Transmitter Delay Compensation Offset for XL frames */
      CanXL_GaaRegs[LucCtrlInfoIndex].pPRT->ulXBTP = LpBaudrateConfig->ulXLCFG;

      /* PCFG */
      /* Defines the parameters needed for the PWM coding */
      CanXL_GaaRegs[LucCtrlInfoIndex].pPRT->ulPCFG = LpBaudrateConfig->ulPWMCFG;

      /* Error Signaling */
      if(CAN_FALSE == LpBaudrateConfig->blErrorSignalingEnabled)
      {
        CanXL_GaaRegs[LucCtrlInfoIndex].pPRT->ulMODE |= CANXL_PRT_EFDI_BIT;
      }
      else
      {
        CanXL_GaaRegs[LucCtrlInfoIndex].pPRT->ulMODE &= ~CANXL_PRT_EFDI_BIT;
      }

      /* PWM Transceiver */
      if(CAN_TRUE == LpBaudrateConfig->blTrcvPwmMode)
      {
        CanXL_GaaRegs[LucCtrlInfoIndex].pPRT->ulMODE |= CANXL_PRT_XLTR_BIT;
      }
      else
      {
        CanXL_GaaRegs[LucCtrlInfoIndex].pPRT->ulMODE &= ~CANXL_PRT_XLTR_BIT;
      }

      /* TDCO */
      if(CAN_TRUE == LpBaudrateConfig->blTDCO)
      {
        CanXL_GaaRegs[LucCtrlInfoIndex].pPRT->ulMODE |= CANXL_PRT_TDCO_BIT;
      }
      else
      {
        CanXL_GaaRegs[LucCtrlInfoIndex].pPRT->ulMODE &= ~CANXL_PRT_TDCO_BIT;
      }
      
      CanXL_GaaCtrlStat[LucCtrlInfoIndex].blErrorSignaling = LpBaudrateConfig->blErrorSignalingEnabled;
      CanXL_GaaCtrlStat[LucCtrlInfoIndex].ulTEC = 0U;
      CanXL_GaaCtrlStat[LucCtrlInfoIndex].ulREC = 0U;
      /**************************************************************************************************************/
      /**                                       INITIALIZATION OF TX BUFFER for ETH Frame                          **/
      /**************************************************************************************************************/
      CanXL_RamInit((uint32)LucCtrlInfoIndex, (uint32)CanXL_GaaMemPoolBufferTable[LucCtrlInfoIndex],                    /* PRQA S 0306 # JV-01 */
                                                                         (uint32)CanXL_GaaRamSize[LucCtrlInfoIndex]);
    } /* else no action required*/
  }
  else
  {
    /* Return CAN_FALSE when Message Handler is started */
    LblErrFlag = CAN_TRUE;
  }
  return (LblErrFlag);
}
/***********************************************************************************************************************
** Function Name         : CanXL_DeInitController
**
** Service ID            : To be defined
**
** Description           : De-Initialize of CANXL module.
**
** Sync/Async            : None
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LucController - Controller index
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : CAN_TRUE/CAN_FALSE
**
** Preconditions         : None
**
** Global Variables Used : CanXL_GaaRegs, Can_GpConfig, CanXL_GaaCtrlStat, Can_GpPCController,
**                         CanXL_GaaMemPoolBufferTable, CanXL_GaaRamSize
**
** Functions Invoked     : CanXL_HwDescriptorInit, CanXL_RamInit
**
** Registers Used        : MH_CFG, MH_SFTY_CFG, MH_SFTY_CTRL, AXI_ADD_EXT, AXI_PARAMS,
**                         RX_STATISTICS, TX_STATISTICS, FUNC_ENA, ERR_ENA, SAFETY_ENA, MODE, NBTP, DBTP, XBTP, PCFG
**                         RX_FQ_START_ADD, RX_FQ_SIZE, TX_FQ_START_ADD, TX_FQ_SIZE, TX_PQ_START_ADD,
**
** Reference ID          : CAN_DUD_ACT_188
** Reference ID          : CAN_DUD_ACT_188_REG001, CAN_DUD_ACT_188_REG002, CAN_DUD_ACT_188_REG003,
** Reference ID          : CAN_DUD_ACT_188_REG004, CAN_DUD_ACT_188_REG005, CAN_DUD_ACT_188_REG006, 
** Reference ID          : CAN_DUD_ACT_188_REG007, CAN_DUD_ACT_188_REG014, CAN_DUD_ACT_188_REG015, 
** Reference ID          : CAN_DUD_ACT_188_REG016, CAN_DUD_ACT_188_REG017, CAN_DUD_ACT_188_REG018, 
** Reference ID          : CAN_DUD_ACT_188_REG019, CAN_DUD_ACT_188_REG020, CAN_DUD_ACT_188_REG021, 
** Reference ID          : CAN_DUD_ACT_188_REG022, CAN_DUD_ACT_188_REG023, CAN_DUD_ACT_188_REG024, 
** Reference ID          : CAN_DUD_ACT_188_REG025, CAN_DUD_ACT_188_REG026, CAN_DUD_ACT_188_REG027, 
** Reference ID          : CAN_DUD_ACT_188_REG028, CAN_DUD_ACT_188_REG029, CAN_DUD_ACT_188_REG030,
** Reference ID          : CAN_DUD_ACT_188_GBL001, CAN_DUD_ACT_188_GBL002, CAN_DUD_ACT_188_GBL003
***********************************************************************************************************************/
FUNC(boolean, CAN_PRIVATE_CODE) CanXL_DeInitController(uint8 LucController)                                             /* PRQA S 3006 # JV-01 */
{
  VAR(boolean, AUTOMATIC) LblErrFlag;
  VAR(Std_ReturnType, AUTOMATIC) LucTimeoutResult;
  VAR(uint32, AUTOMATIC) LulTimeoutDuration;
  VAR(uint16, AUTOMATIC) LusIdx;
  VAR(uint8, AUTOMATIC) LucCount;
  VAR(uint8, AUTOMATIC) LucQueueIdx;
  VAR(uint8, AUTOMATIC) LucCtrlIndex;
  VAR(uint8, AUTOMATIC) LucCtrlInfoIndex;
  VAR(uint16, AUTOMATIC) LucFilIdx;
  VAR(uint16, AUTOMATIC) LucCounter;
  VAR(uint8, TYPEDEF) aaResetMACValue[] = {0, 0, 0, 0, 0 ,0};                                                           /* PRQA S 3678 # JV-01 */
  P2CONST(Can_CanXLHWUnitInfoType, AUTOMATIC, CAN_CONFIG_DATA) LpCanXLHWInfo;
  P2VAR(Can_TxDescriptorsType, AUTOMATIC, CAN_CONFIG_DATA) LpFQTxDescriptors;                                           /* PRQA S 3432 # JV-01 */
  P2VAR(Can_TxDescriptorsType, AUTOMATIC, CAN_CONFIG_DATA) LpPQTxDescriptors;                                           /* PRQA S 3432 # JV-01 */
  P2VAR(Can_RxDescriptorsType, AUTOMATIC, CAN_CONFIG_DATA) LpFQRxDescriptors;                                           /* PRQA S 3432 # JV-01 */
  P2VAR(volatile uint32, AUTOMATIC, CAN_CONFIG_DATA)LpRxFilterElement;
  P2VAR(volatile uint32, AUTOMATIC, CAN_CONFIG_DATA)LpRxFilterRef;
  P2VAR(volatile uint32, AUTOMATIC, CAN_CONFIG_DATA)LpRxFilterMask;
  LblErrFlag = CAN_FALSE;
  /* Get Controller index of CANXL */
  LucCtrlIndex = Can_GpPCController[LucController].ucCh;
  LucCtrlInfoIndex = Can_GpConfig->pCanXLSecondPhysicalControllerToIndex[LucCtrlIndex];
  /* Get PBConfig data for this CANXL unit */
  LpCanXLHWInfo = (P2CONST(Can_CanXLHWUnitInfoType, AUTOMATIC, CAN_CONFIG_DATA))Can_GpConfig->pCanXLHWUnitInfo;         /* PRQA S 0316 # JV-01 */
  /* De-Initialize the MAC address as inital value */
  CANXL_PACK_ADDRESS_FROM_8(aaResetMACValue, CanXL_GaaCtrlStat[LucCtrlInfoIndex].stMacAddr);                            /* PRQA S 3469 # JV-01 */
  /* De-Initialize TxBuffer for ETH Frame */
  CanXL_GpRamManager[LucCtrlInfoIndex] = NULL_PTR;
  /**************************************************************************************************************/
  /**                                 DE-INITIALIZATION OF INTERRUPT CONTROLLER                                **/
  /**************************************************************************************************************/
  /* Disable all events of Functional Interurpt */
  CanXL_GaaRegs[LucCtrlInfoIndex].pIRC->ulFUNCENA = CANXL_IRC_ENABLE_DEFAULT;
  /* Disable all events of Error Interurpt */
  CanXL_GaaRegs[LucCtrlInfoIndex].pIRC->ulERRENA = CANXL_IRC_ENABLE_DEFAULT;
  /* Disable interrupts */
  RH850_SV_MODE_ICR_OR(8, LpCanXLHWInfo[LucCtrlInfoIndex].pICFunc, CAN_EIC_EIMK_MASK);                                  /* PRQA S 0751 # JV-01 */
  RH850_SV_MODE_ICR_OR(8, LpCanXLHWInfo[LucCtrlInfoIndex].pICErr, CAN_EIC_EIMK_MASK);                                   /* PRQA S 0751 # JV-01 */
  /* DummyRead & SYNCP */
  RH850_SV_MODE_REG_READ_ONLY(16, LpCanXLHWInfo[LucCtrlInfoIndex].pICErr);
  EXECUTE_SYNCP();                                                                                                      /* PRQA S 1006 # JV-01 */
  /**************************************************************************************************************/
  /**                                 DE-INITIALIZATION OF PROTOCOL CONTROLLER                                 **/
  /**************************************************************************************************************/
  /* Trigger Software reset to clear all EVNT flags*/
  CanXL_GaaRegs[LucCtrlInfoIndex].pPRT->ulCTRL |= CANXL_PRT_SRES_BIT;
  /* Clear PRT.MODE register*/
  CanXL_GaaRegs[LucCtrlInfoIndex].pPRT->ulMODE = CANXL_PRT_MODE_DEFAULT;
  /* Clear bitrate registers */
  CanXL_GaaRegs[LucCtrlInfoIndex].pPRT->ulNBTP = CANXL_PRT_BITRATE_DEFAULT;
  CanXL_GaaRegs[LucCtrlInfoIndex].pPRT->ulDBTP = CANXL_PRT_BITRATE_DEFAULT;
  CanXL_GaaRegs[LucCtrlInfoIndex].pPRT->ulXBTP = CANXL_PRT_BITRATE_DEFAULT;
  /* Clear PWM registers */
  CanXL_GaaRegs[LucCtrlInfoIndex].pPRT->ulPCFG = CANXL_PRT_PWM_DEFAULT;
  /**************************************************************************************************************/
  /**                                 DE-INITIALIZATION OF MESSAGE HANDLER                                    **/
  /**************************************************************************************************************/
  /* De-Initialize  for MH_CFG register */
  CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulCFG = CANXL_MH_CFG_DEFAULT;
  /* De-Initialize MH_SFTY register */
  CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulSFTYCFG  = CANXL_MH_SFTYCFG_DEFAULT;
  CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulSFTYCTRL = CANXL_MH_SFTYCTRL_DEFAULT;
  /* De-Initialize AXI register */
  CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulAXIADD = CANXL_MH_AXIADD_DEFAULT;
  CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulAXIPAR = CANXL_MH_AXIPAR_DEFAULT;
  
  /**************************************************************************************************************/
  /**                               DE-INITIALIZATION OF RX/TX FIFO QUEUES                                     **/
  /**************************************************************************************************************/
  /* Reset the base address to store the TX descriptors for the TX FIFO Queues and TX Priority Queue in L_RAM */
  CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulTXDADD = CANXL_MH_TXDADD_DEFAULT;
  /* Reset the TX Priority Queue start address in the TX_PQ_START_ADD register */
  CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulTXPQSTADD = CANXL_MH_TXSTADD_DEFAULT;
  /* Loop all TX FIFO Queue were configured. */
  for (LucCount = 0; LucCount < LpCanXLHWInfo[LucCtrlInfoIndex].ucNoOfTxFIFOQueues; LucCount++)
  {
    /* Get Tx FIFO Queue index */
    LucQueueIdx = LpCanXLHWInfo[LucCtrlInfoIndex].pTxFIFOQueueConfig[LucCount].ucQueueId;
    /* Reset the address of the First TX Descriptor of the linked list*/
    CanXL_GaaRegs[LucCtrlInfoIndex].pMH->aaTXFQReg[LucQueueIdx].ulTXSTADD = CANXL_MH_TXSTADD_DEFAULT;
    /* Reset the size of the linked list in number of TX descriptors */
    CanXL_GaaRegs[LucCtrlInfoIndex].pMH->aaTXFQReg[LucQueueIdx].ulTXSIZE = CANXL_MH_TXSIZE_DEFAULT;
    /* Reset value for each descriptor in each Queues */
    LpFQTxDescriptors =
          (Can_TxDescriptorsType*)LpCanXLHWInfo[LucCtrlInfoIndex].pTxFIFOQueueConfig[LucQueueIdx].pStartAddress;
    for (LusIdx = 0U; LusIdx < LpCanXLHWInfo[LucCtrlInfoIndex].pTxFIFOQueueConfig[LucCount].usMaxNumDesc; LusIdx++)
    {
      LpFQTxDescriptors[LusIdx].ulElement0 = CANXL_DESCRIPTOR_DEFAULT;
      LpFQTxDescriptors[LusIdx].ulElement1 = CANXL_DESCRIPTOR_DEFAULT;
      LpFQTxDescriptors[LusIdx].ulElement2TS0 = CANXL_DESCRIPTOR_DEFAULT;
      LpFQTxDescriptors[LusIdx].ulElement3TS1 = CANXL_DESCRIPTOR_DEFAULT;
      LpFQTxDescriptors[LusIdx].ulElement4T0 = CANXL_DESCRIPTOR_DEFAULT;
      LpFQTxDescriptors[LusIdx].ulElement5T1 = CANXL_DESCRIPTOR_DEFAULT;
      LpFQTxDescriptors[LusIdx].ulElement6T2TD0 = CANXL_DESCRIPTOR_DEFAULT;
      LpFQTxDescriptors[LusIdx].ulElement7TX_APTD1 = CANXL_DESCRIPTOR_DEFAULT;
    }
  }
  /* Reset descriptor for TX Priority Queue by 32 slot */
  LpPQTxDescriptors = (Can_TxDescriptorsType*)LpCanXLHWInfo[LucCtrlInfoIndex].pTxPriorityQueueConfig->pStartAddress;
  for (LucQueueIdx = 0U; LucQueueIdx < CANXL_MAX_PRIORITYQUEUE_SLOT; LucQueueIdx++)
  {
    if(0UL != (LpCanXLHWInfo[LucCtrlInfoIndex].ulTXPQUsed & (1UL << LucQueueIdx)))
    {
      LpPQTxDescriptors[LucQueueIdx].ulElement0 = CANXL_DESCRIPTOR_DEFAULT;
      LpPQTxDescriptors[LucQueueIdx].ulElement1 = CANXL_DESCRIPTOR_DEFAULT;
      LpPQTxDescriptors[LucQueueIdx].ulElement2TS0 = CANXL_DESCRIPTOR_DEFAULT;
      LpPQTxDescriptors[LucQueueIdx].ulElement3TS1 = CANXL_DESCRIPTOR_DEFAULT;
      LpPQTxDescriptors[LucQueueIdx].ulElement4T0 = CANXL_DESCRIPTOR_DEFAULT;
      LpPQTxDescriptors[LucQueueIdx].ulElement5T1 = CANXL_DESCRIPTOR_DEFAULT;
      LpPQTxDescriptors[LucQueueIdx].ulElement6T2TD0 = CANXL_DESCRIPTOR_DEFAULT;
      LpPQTxDescriptors[LucQueueIdx].ulElement7TX_APTD1 = CANXL_DESCRIPTOR_DEFAULT;
    } /* else no action required*/
  }
  /* Loop all RX FIFO Queue were configured. */
  for (LucCount = 0; LucCount < LpCanXLHWInfo[LucCtrlInfoIndex].ucNoOfRxFIFOQueues; LucCount++)
  {
    /* Get Rx FIFO Queue index */
    LucQueueIdx = LpCanXLHWInfo[LucCtrlInfoIndex].pRxFIFOQueueConfig[LucCount].ucQueueId;
    /* Reset the address of the First RX Descriptor of the linked list */
    CanXL_GaaRegs[LucCtrlInfoIndex].pMH->aaRXFQReg[LucQueueIdx].ulRXSTADD = CANXL_MH_RXSTADD_DEFAULT;
    /* Reset the size of the linked list in number of RX descriptors */
    CanXL_GaaRegs[LucCtrlInfoIndex].pMH->aaRXFQReg[LucQueueIdx].ulRXSIZE = CANXL_MH_RXSIZE_DEFAULT;
    /* Reset value for each descriptor in each Queues */
    LpFQRxDescriptors =
          (Can_RxDescriptorsType*)LpCanXLHWInfo[LucCtrlInfoIndex].pRxFIFOQueueConfig[LucQueueIdx].pStartAddress;
    for (LusIdx = 0U; LusIdx < LpCanXLHWInfo[LucCtrlInfoIndex].pRxFIFOQueueConfig[LucCount].usMaxNumDesc; LusIdx++)
    {
      LpFQRxDescriptors[LusIdx].ulElement0 = CANXL_DESCRIPTOR_DEFAULT;
      LpFQRxDescriptors[LusIdx].ulElement1 = CANXL_DESCRIPTOR_DEFAULT;
      LpFQRxDescriptors[LusIdx].ulElement2TS0 = CANXL_DESCRIPTOR_DEFAULT;
      LpFQRxDescriptors[LusIdx].ulElement3TS1 = CANXL_DESCRIPTOR_DEFAULT;
    }
  }
  /**************************************************************************************************************/
  /**                               DE-INITIALIZATION OF RX FILTER                                             **/
  /**************************************************************************************************************/
  /* Setting the RX Filter Base Address */
  CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulRXFADD = CANXL_MH_RXFADD_DEFAULT;
  if (0U == LucCtrlIndex)
  {
    /* Set the RX filter Element 0 to the base address of L_MEM */
    LpRxFilterElement = (uint32*)(LpCanXLHWInfo[LucCtrlInfoIndex].ulRXFILTLMEM | CAN_LRAM_BASE_ADDR_CH0);               /* PRQA S 0306 # JV-01 */
  }
  else
  {
    /* Set the RX filter Element 0 to the base address of L_MEM */
    LpRxFilterElement = (uint32*)(LpCanXLHWInfo[LucCtrlInfoIndex].ulRXFILTLMEM | CAN_LRAM_BASE_ADDR_CH1);               /* PRQA S 0306 # JV-01 */
  }
  /* Set the address to RX filter Reference 0 */
  LpRxFilterRef = (volatile uint32*)(LpRxFilterElement + LpCanXLHWInfo[LucCtrlInfoIndex].ucNoOfFilters);                /* PRQA S 0488 # JV-01 */
  /* Set the address to RX filter Mask 0 */
  LpRxFilterMask = (volatile uint32*)(LpRxFilterRef + 0x01UL);                                                          /* PRQA S 0489 # JV-01 */

  /* Setting the RX Filter Element in L_MEM */
  for(LucCounter = 0U; LucCounter < LpCanXLHWInfo[LucCtrlInfoIndex].ucNoOfFilters; LucCounter++)
  {
    /* Setting Comparison Reference Index */
    LpRxFilterElement[LucCounter] = CANXL_RXFILTER_DEFAULT;
  }
  
  /* Setting the RX Filter Reference/Mask in L_MEM */
  for(LucCounter = 0U; LucCounter < LpCanXLHWInfo[LucCtrlInfoIndex].usNoOfRxFilterRefPairs; LucCounter++)
  {
    /* Get filter index */
    LucFilIdx = (LpCanXLHWInfo[LucCtrlInfoIndex].pRxFilterRefPairConfig[LucCounter].usRxRefPairId * 2U);                 /* PRQA S 3383 # JV-01 */
    /* Setting Reference Value */
    LpRxFilterRef[LucFilIdx] = CANXL_RXFILTER_DEFAULT;
    /* Setting Mask Value */
    LpRxFilterMask[LucFilIdx] = CANXL_RXFILTER_DEFAULT;
  }
  /* Initialize the number of Rx Filter Element */
  CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulRXFTCTRL0 = CANXL_RXFILTER_DEFAULT;
  /* Disable clock: Host clock, Can Clock and Time base clock */
  CanXL_GaaRegs[LucCtrlInfoIndex].pGLB->ulCXLCCLKC = 0xC400UL;
  LulTimeoutDuration = CAN_TIMEOUT_COUNT;
  /* Waiting Clock active */
  LucTimeoutResult = Can_WaitRegisterChange(&CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulSTS,
                                            CAN_MH_STS_CLOCK_ACTIVE, 0UL, &LulTimeoutDuration);
  /* If LRAMINIT flag was not set, report error */
  if (E_OK != LucTimeoutResult)
  {
    #if defined(CAN_E_TIMEOUT_FAILURE)
    CAN_DEM_REPORT_ERROR(CAN_E_TIMEOUT_FAILURE, DEM_EVENT_STATUS_FAILED);
    #endif
    LblErrFlag = CAN_TRUE;
  }
  else
  {
    LulTimeoutDuration = CAN_TIMEOUT_COUNT;
  /* Waiting status Clock */
    LucTimeoutResult = Can_WaitRegisterChange(&CanXL_GaaRegs[LucCtrlInfoIndex].pPRT->ulSTAT,
                                              CAN_STAT_CLKA, 0UL, &LulTimeoutDuration);
    /* If LRAMINIT flag was not set, report error */
    if (E_OK != LucTimeoutResult)
    {
      #if defined(CAN_E_TIMEOUT_FAILURE)
      CAN_DEM_REPORT_ERROR(CAN_E_TIMEOUT_FAILURE, DEM_EVENT_STATUS_FAILED);
      #endif
      LblErrFlag = CAN_TRUE;
    }
  }
  return LblErrFlag;
}
/*******************************************************************************
** Function Name         : CanXL_HwDescriptorInit
**
** Service ID            : N/A
**
** Description           : Pre-Initialize the common parts of Descriptors
**
** Sync/Async            : None
**
** Reentrancy            : None
**
** Input Parameters      : LucController - Controller index
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variable(s)    : Can_GpConfig, Can_GpPCController, CanXL_GaaCtrlStat
**
** Function(s) invoked   : CanXL_ComputeCRC.
**
** Registers Used        : None
**
** Reference ID          : CAN_DUD_ACT_129
** Reference ID          : CAN_DUD_ACT_129_GBL001, CAN_DUD_ACT_129_GBL002,
** Reference ID          : CAN_DUD_ACT_129_GBL003, CAN_DUD_ACT_129_GBL004
***********************************************************************************************************************/
STATIC FUNC(void, CAN_PRIVATE_CODE) CanXL_HwDescriptorInit(uint8 LucController)
{
  VAR(uint16, AUTOMATIC) LusIdx;
  VAR(uint16, AUTOMATIC) LusCRC;
  VAR(uint16, AUTOMATIC) LusPayload;
  VAR(uint8, AUTOMATIC) LucRCIdx;
  VAR(uint8, AUTOMATIC) LucQueueIdx;
  VAR(uint8, AUTOMATIC) LucCount;
  VAR(uint8, AUTOMATIC) LucCtrlInfoIndex;
  VAR(uint16, AUTOMATIC) LusLastIdQueue;
  
  P2CONST(uint8, AUTOMATIC, CAN_CONFIG_DATA) LpDataContainer;
  P2CONST(Can_CanXLHWUnitInfoType, AUTOMATIC, CAN_CONFIG_DATA) LpCanXLHWInfo;
  /* declare desscriptors */
  P2VAR(Can_TxDescriptorsType, AUTOMATIC, CAN_CONFIG_DATA) LpFQTxDescriptors;                                           /* PRQA S 3432 # JV-01 */
  P2VAR(Can_TxDescriptorsType, AUTOMATIC, CAN_CONFIG_DATA) LpPQTxDescriptors;                                           /* PRQA S 3432 # JV-01 */
  P2VAR(Can_RxDescriptorsType, AUTOMATIC, CAN_CONFIG_DATA) LpRxDescriptors;                                             /* PRQA S 3432 # JV-01 */
  LucCtrlInfoIndex = Can_GpConfig->pCanXLSecondPhysicalControllerToIndex[LucController];
  LusLastIdQueue = 0U;
  /* Get PBConfig data for this CANXL unit */
  LpCanXLHWInfo = (P2CONST(Can_CanXLHWUnitInfoType, AUTOMATIC, CAN_CONFIG_DATA))Can_GpConfig->pCanXLHWUnitInfo;         /* PRQA S 0316 # JV-01 */
  if( CAN_TRUE == LpCanXLHWInfo[LucCtrlInfoIndex].blTxFQEnable)
  {
    /* Initialize descriptor for TX FIFO Queue */
    for (LucCount = 0U; LucCount < LpCanXLHWInfo[LucCtrlInfoIndex].ucNoOfTxFIFOQueues; LucCount++)
    {
      /* Get Tx FIFO Queue index */
      LucQueueIdx = LpCanXLHWInfo[LucCtrlInfoIndex].pTxFIFOQueueConfig[LucCount].ucQueueId;
      /* Get descriptors for each Queues (0,1,2...)  */
      LpFQTxDescriptors =
              (Can_TxDescriptorsType*)LpCanXLHWInfo[LucCtrlInfoIndex].pTxFIFOQueueConfig[LucCount].pStartAddress;
      /* Initiliaze Head descriptor for each Queues */
      CanXL_GaaCtrlStat[LucCtrlInfoIndex].stHwStatFixed.aaFirstTxDesc[LucQueueIdx] = LpFQTxDescriptors;
      CanXL_GaaCtrlStat[LucCtrlInfoIndex].stHwStatNonSDT5.aaHeadTxDesc[LucQueueIdx] = LpFQTxDescriptors;
      CanXL_GaaCtrlStat[LucCtrlInfoIndex].stHwStatSDT5.aaHeadTxDesc[LucQueueIdx] = LpFQTxDescriptors;
      /* Initialize value for each descriptor in each Queues (0,1,2...) */
      for (LusIdx = 0U; LusIdx < LpCanXLHWInfo[LucCtrlInfoIndex].pTxFIFOQueueConfig[LucCount].usMaxNumDesc; LusIdx++)
      {
        LucRCIdx = (uint8)(LusIdx) % 32U;
        LpFQTxDescriptors[LusIdx].ulElement0 = CANXL_DMA1_FIXED_FQ | CANXL_BIT_RC((uint32)LucRCIdx) |                   /* PRQA S 3469, 2985 # JV-01, JV-01 */
                                              CANXL_BIT_FQN(LucQueueIdx) | CANXL_BIT_IRQ(1UL);                          /* PRQA S 3469 # JV-01 */
        LpFQTxDescriptors[LusIdx].ulElement1 = CANXL_DMA2_FIXED_FQ | CANXL_BIT_IN(((uint32)LucController));             /* PRQA S 3469 # JV-01 */
        LusLastIdQueue = LusIdx;
      }
      /* Initiliaze Last descriptor for each Queues */
      CanXL_GaaCtrlStat[LucCtrlInfoIndex].stHwStatFixed.aaLastTxDesc[LucQueueIdx] = &LpFQTxDescriptors[LusLastIdQueue];
    }
  } /* else no action required*/

  if( CAN_TRUE == LpCanXLHWInfo[LucCtrlInfoIndex].blTxPQEnable)
  {
    /* Initialize descriptor for TX Priority Queue by 32 slot */
    LpPQTxDescriptors = (Can_TxDescriptorsType*)LpCanXLHWInfo[LucCtrlInfoIndex].pTxPriorityQueueConfig->pStartAddress;
    for (LucQueueIdx = 0U; LucQueueIdx < CANXL_MAX_PRIORITYQUEUE_SLOT; LucQueueIdx++)
    {
      if(0UL != (LpCanXLHWInfo[LucCtrlInfoIndex].ulTXPQUsed & (1UL << LucQueueIdx)))
      {
        LpPQTxDescriptors[LucQueueIdx].ulElement0 = CANXL_DMA1_FIXED_PQ | CANXL_BIT_RC(0UL) |                           /* PRQA S 3469 # JV-01 */
                                          CANXL_BIT_PQSN(LucQueueIdx) | CANXL_BIT_IRQ(1UL);                             /* PRQA S 3469 # JV-01 */
        LpPQTxDescriptors[LucQueueIdx].ulElement1 = CANXL_DMA2_FIXED_PQ | CANXL_BIT_IN((uint32)LucController);          /* PRQA S 3469, 2986 # JV-01, JV-01 */
      } /* else no action required*/
    }
  } /* else no action required*/

  /* Initialize descriptor for RX FIFO Queue */
  for (LucCount = 0U; LucCount < LpCanXLHWInfo[LucCtrlInfoIndex].ucNoOfRxFIFOQueues; LucCount++)
  {
    /* Get Rx FIFO Queue index */
    LucQueueIdx = LpCanXLHWInfo[LucCtrlInfoIndex].pRxFIFOQueueConfig[LucCount].ucQueueId;
    /* Get descriptors for each Queues (0,1,2...)  */
    LpRxDescriptors =
           (Can_RxDescriptorsType *) LpCanXLHWInfo[LucCtrlInfoIndex].pRxFIFOQueueConfig[LucCount].pStartAddress;
    /* Initiliaze Next descriptor for each Queues */
    CanXL_GaaCtrlStat[LucCtrlInfoIndex].stHwStatFixed.aaFirstRxDesc[LucQueueIdx] = LpRxDescriptors;
    CanXL_GaaCtrlStat[LucCtrlInfoIndex].stHwStatNonSDT5.aaHeadRxDesc[LucQueueIdx] = LpRxDescriptors;
    CanXL_GaaCtrlStat[LucCtrlInfoIndex].stHwStatSDT5.aaHeadRxDesc[LucQueueIdx] = LpRxDescriptors;
    /* Initialize value for each descriptor in each Queues (0,1,2...) */
    for (LusIdx = 0U; LusIdx < LpCanXLHWInfo[LucCtrlInfoIndex].pRxFIFOQueueConfig[LucCount].usMaxNumDesc; LusIdx++)
    {
      LucRCIdx = (uint8)(LusIdx) % 32U;
      LpRxDescriptors[LusIdx].ulElement0 = CANXL_RX_DMA1_FIXED | CANXL_RX_BIT_RC((uint32)LucRCIdx) |                    /* PRQA S 3469, 2985, 2986 # JV-01, JV-01, JV-01 */
          CANXL_RX_BIT_IN((uint32)LucController) | CANXL_RX_BIT_FQN((uint32)LucQueueIdx) | CANXL_RX_BIT_IRQ(1UL);       /* PRQA S 3469 # JV-01 */
      LusPayload = LpCanXLHWInfo[LucCtrlInfoIndex].pRxFIFOQueueConfig[LucCount].usPayloadSize;
      /* Get Buffer address */
      LpDataContainer =
          &LpCanXLHWInfo[LucCtrlInfoIndex].pRxFIFOQueueConfig[LucCount].pDataContainer[LusIdx * LusPayload * 32U];      /* PRQA S 3384 # JV-01 */
      /* Provide Buffer address for RxFIFO */
      LpRxDescriptors[LusIdx].ulElement1 = (uint32)LpDataContainer;                                                     /* PRQA S 0306 # JV-01 */
    
      /* Initialize Rx Timestamp */
      #if (CAN_CANXL_GLOBAL_TIME_SUPPORT == STD_ON)
      LpRxDescriptors[LusIdx].ulElement2TS0 = 0UL;
      LpRxDescriptors[LusIdx].ulElement3TS1 = 0UL;
      #endif
      /* Caculate CRC code */
      LusCRC = CanXL_ComputeCRC((uint32 *)(LpRxDescriptors + LusIdx), CANXL_RX_DESC);                                   /* PRQA S 0310, 0488 # JV-01, JV-01 */
      LpRxDescriptors[LusIdx].ulElement0 |= CANXL_RX_BIT_CRC(LusCRC);                                                   /* PRQA S 3469 # JV-01 */
      LusLastIdQueue = LusIdx;
    }
    /* Initiliaze Last descriptor for each Queues */
    CanXL_GaaCtrlStat[LucCtrlInfoIndex].stHwStatFixed.aaLastRxDesc[LucQueueIdx] = &LpRxDescriptors[LusLastIdQueue];
  }
}
/*******************************************************************************
** Function Name         : CanXL_HWSettingRXFilter
**
** Service ID            : N/A
**
** Description           : Pre-Initialize the RX Filter
**
** Sync/Async            : None
**
** Reentrancy            : None
**
** Input Parameters      : LucController
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variable(s)    : CanXL_GaaRegs, Can_GpConfig 
**
** Function(s) invoked   : To be defined
**
** Registers Used        : RX_FILTER_MEM_ADD, RX_FILTER_CTRL
**
** Reference ID          : CAN_DUD_ACT_130
** Reference ID          : CAN_DUD_ACT_130_REG001, CAN_DUD_ACT_130_REG002
*******************************************************************************/
STATIC FUNC(void, CAN_PRIVATE_CODE) CanXL_HWSettingRXFilter(uint8 LucControllerID)
{
  P2VAR(volatile uint32, AUTOMATIC, CAN_CONFIG_DATA)LpRxFilterElement;
  P2VAR(volatile uint32, AUTOMATIC, CAN_CONFIG_DATA)LpRxFilterRef;
  P2VAR(volatile uint32, AUTOMATIC, CAN_CONFIG_DATA)LpRxFilterMask;
  VAR(uint16, AUTOMATIC) LucFilIdx;
  VAR(uint16, AUTOMATIC) LucCounter;
  VAR(uint8, AUTOMATIC) LucCtrlInfoIndex;
  VAR(uint8, AUTOMATIC) LucController;
  P2CONST(Can_CanXLHWUnitInfoType, AUTOMATIC, CAN_CONFIG_DATA) LpCanXLHWInfo;
  
  /* Get PBConfig data for this CANXL unit */
  LucController = Can_GpPCController[LucControllerID].ucCh;
  LucCtrlInfoIndex = Can_GpConfig->pCanXLSecondPhysicalControllerToIndex[LucController];
  LpCanXLHWInfo = (P2CONST(Can_CanXLHWUnitInfoType, AUTOMATIC, CAN_CONFIG_DATA))Can_GpConfig->pCanXLHWUnitInfo;         /* PRQA S 0316 # JV-01 */
  /* Setting the RX Filter Base Address */
  CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulRXFADD = LpCanXLHWInfo[LucCtrlInfoIndex].ulRXFILTLMEM;
  if (0U == LucController)
  {
    /* Set the RX filter Element 0 to the base address of L_MEM */
    LpRxFilterElement = (uint32*)(LpCanXLHWInfo[LucCtrlInfoIndex].ulRXFILTLMEM | CAN_LRAM_BASE_ADDR_CH0);               /* PRQA S 0306 # JV-01 */
  }
  else
  {
    /* Set the RX filter Element 0 to the base address of L_MEM */
    LpRxFilterElement = (uint32*)(LpCanXLHWInfo[LucCtrlInfoIndex].ulRXFILTLMEM | CAN_LRAM_BASE_ADDR_CH1);               /* PRQA S 0306 # JV-01 */
  }
  /* Set the address to RX filter Reference 0 */
  LpRxFilterRef = (volatile uint32*)(LpRxFilterElement + LpCanXLHWInfo[LucCtrlInfoIndex].ucNoOfFilters);                /* PRQA S 0488 # JV-01 */
  /* Set the address to RX filter Mask 0 */
  LpRxFilterMask = (volatile uint32*)(LpRxFilterRef + 0x01UL);                                                          /* PRQA S 0489 # JV-01 */

  /* Setting the RX Filter Element in L_MEM */
  for(LucCounter = 0U; LucCounter < LpCanXLHWInfo[LucCtrlInfoIndex].ucNoOfFilters; LucCounter++)
  {
    /* Setting Comparison Reference Index */
    LpRxFilterElement[LucCounter] = LpCanXLHWInfo[LucCtrlInfoIndex].pFilterConfig[LucCounter].ulRxFilterVal;
  }
  
  /* Setting the RX Filter Reference/Mask in L_MEM */
  for(LucCounter = 0U; LucCounter < LpCanXLHWInfo[LucCtrlInfoIndex].usNoOfRxFilterRefPairs; LucCounter++)
  {
    /* Get filter index */
    LucFilIdx = (LpCanXLHWInfo[LucCtrlInfoIndex].pRxFilterRefPairConfig[LucCounter].usRxRefPairId * 2U);                 /* PRQA S 3383 # JV-01 */
    /* Setting Reference Value */
    LpRxFilterRef[LucFilIdx] = LpCanXLHWInfo[LucCtrlInfoIndex].pRxFilterRefPairConfig[LucCounter].ulRefVal;
    /* Setting Mask Value */
    LpRxFilterMask[LucFilIdx] = LpCanXLHWInfo[LucCtrlInfoIndex].pRxFilterRefPairConfig[LucCounter].ulMask;
  }
  /* Initialize the number of Rx Filter Element */
  CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulRXFTCTRL0 = LpCanXLHWInfo[LucCtrlInfoIndex].ulRXFILCTRL0;
}

/***********************************************************************************************************************
** Function Name         : CanXL_ClearAllAddressFilters
**
** Service ID            : N/A
**
** Description           : Remove all filters from the filter list and turn off
**                         promiscuous mode
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : LulCtrlIdx: Index of a controller
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variable(s)    : CanXL_GaaMacFilterMng
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : CAN_DUD_ACT_151
** Reference ID          : CAN_DUD_ACT_151_GBL001
***********************************************************************************************************************/
STATIC FUNC(void, CAN_PRIVATE_CODE) CanXL_ClearAllAddressFilters(CONST(uint32, AUTOMATIC) LulCtrlIdx)
{
  CanXL_MacFilterMng* LpMng;
  uint32 LulIdx;

  /* Get Filter Manager */
  LpMng = &(CanXL_GaaMacFilterMng[LulCtrlIdx]);

  LpMng->ulPromiscuousCount = 0;

  for (LulIdx = 0; LulIdx < CANXL_MAX_FILTERS; LulIdx++)
  {
    LpMng->stFilter[LulIdx].ulCount = 0;
    LpMng->stFilter[LulIdx].stMacAddr.ulH32 = 0UL;
    LpMng->stFilter[LulIdx].stMacAddr.ulL16 = 0UL;
  }
}

/***********************************************************************************************************************
** Function Name         : CanXL_RemoveAddressFilter
**
** Service ID            : N/A
**
** Description           : Remove a filter from the filter list
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : LulCtrlIdx  : Index of a controller
**                       : LpMacAddr   : Pointer to a MAC address to be removed
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : Std_ReturnType
**                         E_OK: filter was successfully changed
**                         E_NOT_OK: filter could not be changed
**
** Preconditions         : None
**
** Global Variable(s)    : CanXL_GaaMacFilterMng, CanXL_GstBroadcastAddr, CanXL_GstNullAddr
**
** Function(s) invoked   : CanXL_ClearAllAddressFilters
**
** Registers Used        : None
**
** Reference ID          : CAN_DUD_ACT_152
** Reference ID          : CAN_DUD_ACT_152_CRT001, CAN_DUD_ACT_152_CRT002, CAN_DUD_ACT_152_GBL001
***********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, CAN_PRIVATE_CODE) CanXL_RemoveAddressFilter(
          CONST(uint32, AUTOMATIC) LulCtrlIdx, CONSTP2CONST(CanXL_MacAddressType, AUTOMATIC, CANXL_APPL_DATA) LpMacAddr)
{
  Std_ReturnType LucReturnValue;
  CanXL_MacFilterMng* LpMng;
  uint32 LulIdx;

  LucReturnValue = E_NOT_OK;

  LpMng = &(CanXL_GaaMacFilterMng[LulCtrlIdx]);

  if (0UL == CANXL_COMPARE_MAC(*LpMacAddr, CanXL_GstBroadcastAddr))                                                     /* PRQA S 3469 # JV-01 */
  {
    /* Broadcast Address (FF:FF:FF:FF:FF:FF) */
    if (0UL < LpMng->ulPromiscuousCount)
    {
      /* Descrement Promiscuous Counter */
      LpMng->ulPromiscuousCount--;
      LucReturnValue = E_OK;
    } /* else no action required*/
  }
  else if (0UL == CANXL_COMPARE_MAC(*LpMacAddr, CanXL_GstNullAddr))                                                     /* PRQA S 2985, 3469 # JV-01, JV-01 */
  {
    /* NULL Address (00:00:00:00:00:00) */
    /* Filter Initialize & Force-quit Promiscuous Mode */
    CAN_ENTER_CRITICAL_SECTION(CAN_RAM_DATA_PROTECTION);
    CanXL_ClearAllAddressFilters(LulCtrlIdx);
    CAN_EXIT_CRITICAL_SECTION(CAN_RAM_DATA_PROTECTION);
    
    LucReturnValue = E_OK;
  }
  else
  {
    /* Remove Filter */
    for (LulIdx = 0; LulIdx < CANXL_MAX_FILTERS; LulIdx++)
    {
      if ((0UL < LpMng->stFilter[LulIdx].ulCount) &&
        (0UL == CANXL_COMPARE_MAC(*LpMacAddr, LpMng->stFilter[LulIdx].stMacAddr)))                                      /* PRQA S 3469 # JV-01 */
      {
        CAN_ENTER_CRITICAL_SECTION(CAN_RAM_DATA_PROTECTION);
        /* Descrement Filter Counter */
        LpMng->stFilter[LulIdx].ulCount--;
        
        if (0UL == LpMng->stFilter[LulIdx].ulCount)
        {
          /* Clear Filter Address */
          LpMng->stFilter[LulIdx].stMacAddr.ulH32 = 0UL;
          LpMng->stFilter[LulIdx].stMacAddr.ulL16 = 0UL;
        } /* else no action required*/
        
        CAN_EXIT_CRITICAL_SECTION(CAN_RAM_DATA_PROTECTION);
        
        LucReturnValue = E_OK;
        break;
      } /* else no action required*/
    }
  }
  
  return LucReturnValue;
}

/***********************************************************************************************************************
** Function Name         : CanXL_AddAddressFilter
**
** Service ID            : N/A
**
** Description           : Add a address filter to the filter list
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : LulCtrlIdx: Index of a controller
**                         LpMacAddr : Pointer to a MAC address to be added
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : Std_ReturnType
**                         E_OK: filter was successfully changed
**                         E_NOT_OK: filter could not be changed
**
** Preconditions         : At least there is an empty entry in the FilterArray
**
** Global Variable(s)    : CanXL_GaaMacFilterMng, CanXL_GstBroadcastAddr, CanXL_GstNullAddr
**
** Function(s) invoked   : CanXL_ClearAllAddressFilters
**
** Registers Used        : None
**
** Reference ID          : CAN_DUD_ACT_153
** Reference ID          : CAN_DUD_ACT_153_CRT001, CAN_DUD_ACT_153_CRT002
***********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, CAN_PRIVATE_CODE) CanXL_AddAddressFilter( 
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONSTP2CONST(CanXL_MacAddressType, AUTOMATIC, CAN_APPL_DATA) LpMacAddr)
{
  Std_ReturnType LucReturnValue;
  CanXL_MacFilterMng* LpMng;
  CanXL_MacFilter* LpTarget;
  uint32 LulIdx;

  LucReturnValue = E_OK;

  /* Get Mac Filter Manager */
  LpMng = &(CanXL_GaaMacFilterMng[LulCtrlIdx]);
  if (0UL == CANXL_COMPARE_MAC(*LpMacAddr, CanXL_GstBroadcastAddr))                                                     /* PRQA S 3469 # JV-01 */
  {
    /* Broadcast Address (FF:FF:FF:FF:FF:FF) */
    if (CANXL_FILTER_COUNT_MAX > LpMng->ulPromiscuousCount)
    {
      /* Enter Promiscuous Mode */
      LpMng->ulPromiscuousCount++;
    }
    else
    {
      /* Promiscuous Counter Overflow */
      LucReturnValue = E_NOT_OK;
    }
  }
  else if (0UL == CANXL_COMPARE_MAC(*LpMacAddr, CanXL_GstNullAddr))                                                     /* PRQA S 3469, 2985 # JV-01, JV-01 */
  {
    /* NULL Address (00:00:00:00:00:00) */
    /* Filter Initialize & Force-quit Promiscuous Mode */
    CAN_ENTER_CRITICAL_SECTION(CAN_RAM_DATA_PROTECTION);
    CanXL_ClearAllAddressFilters(LulCtrlIdx);
    CAN_EXIT_CRITICAL_SECTION(CAN_RAM_DATA_PROTECTION);
  }
  else if (0UL == CANXL_CHECK_MULTICAST(*LpMacAddr))                                                                    /* PRQA S 3469 # JV-01 */
  {
    /* The specified address is not a multicast address */
    LucReturnValue = E_NOT_OK;
  }
  else
  {
    LpTarget = NULL_PTR;
    
    /* Serch the Target array space */
    for (LulIdx = 0; LulIdx < CANXL_MAX_FILTERS; LulIdx++)
    {
      if (0UL == CANXL_COMPARE_MAC(LpMng->stFilter[LulIdx].stMacAddr, CanXL_GstNullAddr))                               /* PRQA S 3469, 2985 # JV-01, JV-01 */
      {
        /* Blank array space found */
        if (NULL_PTR == LpTarget)
        {
          LpTarget = &(LpMng->stFilter[LulIdx]);
        } /* else no action required*/
      }
      else if (0UL == CANXL_COMPARE_MAC(*LpMacAddr, LpMng->stFilter[LulIdx].stMacAddr))                                 /* PRQA S 3469, 2004 # JV-01, JV-01 */
      {
        /* The same MAC address is already registered */
        LpTarget = &(LpMng->stFilter[LulIdx]);
        break;
      } /* else no action required*/
    }
    
    if (NULL_PTR != LpTarget)
    {
      if (CANXL_FILTER_COUNT_MAX > LpTarget->ulCount)
      {
        CAN_ENTER_CRITICAL_SECTION(CAN_RAM_DATA_PROTECTION);
        /* Add Mac Address */
        LpTarget->stMacAddr.ulH32 = LpMacAddr->ulH32;
        LpTarget->stMacAddr.ulL16 = LpMacAddr->ulL16;
        /* Increment Counter */
        LpTarget->ulCount++;
        CAN_EXIT_CRITICAL_SECTION(CAN_RAM_DATA_PROTECTION);
      }
      else
      {
        /* Counter Overflow */
        LucReturnValue = E_NOT_OK;
      }
    }
    else
    {
      /* The filter array is full */
      LucReturnValue = E_NOT_OK;
    }
  }
  
  return LucReturnValue;
}

/***********************************************************************************************************************
** Function Name         : CanXL_CheckProvideBuffer
**
** Service ID            : N/A
**
** Description           : This function checks whether the memory
**                         at the specified buffer index has been allocated.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulCtrlIdx     : controller index
**                         LulBufIdx      : index to the buffer
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : E_OK : Success
**                         E_NOT_OK : Failure
**
** Preconditions         : None
**
** Global Variables Used : CanXL_GaaTxBufferMgrTable
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : CAN_DUD_ACT_154
***********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, CAN_PRIVATE_CODE) CanXL_CheckProvideBuffer(
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulBufIdx)
{
  Std_ReturnType LucReturnValue;

  /* Find tx buffer handler */
  if ((NULL_PTR != CanXL_GaaTxBufferMgrTable[LulCtrlIdx][LulBufIdx].pBufferHdr) && 
      (CAN_FALSE == CanXL_GaaTxBufferMgrTable[LulCtrlIdx][LulBufIdx].blTxOngoing))
  {
    LucReturnValue = E_OK;
  }
  else
  {
    LucReturnValue = E_NOT_OK;
  }

  return LucReturnValue;
}

/***********************************************************************************************************************
** Function Name         : CanXL_RamInit
**
** Service ID            : N/A
**
** Description           : This Initialize base address of RAM for application
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulCtrlIdx - Index of the controller
**                       : LulBaseAddr - Start Address for the Ram
**                       : LulRamSize  - size of all available memory (in Byte)
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variable(s)    : CanXL_GpRamManager
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : CAN_DUD_ACT_155,
** Reference ID          : CAN_DUD_ACT_155_GBL001, CAN_DUD_ACT_155_GBL002
** Reference ID          : CAN_DUD_ACT_155_GBL003, CAN_DUD_ACT_155_GBL004
** Reference ID          : CAN_DUD_ACT_155_GBL005
*******************************************************************************/
STATIC FUNC(void, CAN_PRIVATE_CODE) CanXL_RamInit(                                                              
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulBaseAddr, CONST(uint32, AUTOMATIC) LulRamSize)
{
  CanXL_GpRamManager[LulCtrlIdx] = (CanXL_MemManagerType *)LulBaseAddr;                                                 /* PRQA S 0306 # JV-01 */
  CanXL_GpRamManager[LulCtrlIdx]->pNext = CanXL_GpRamManager[LulCtrlIdx];                                          
  CanXL_GpRamManager[LulCtrlIdx]->pPrev = CanXL_GpRamManager[LulCtrlIdx];                            
  CanXL_GpRamManager[LulCtrlIdx]->ulHeapSize = LulRamSize;
  CanXL_GpRamManager[LulCtrlIdx]->blHeapLock = CAN_FALSE;
}

/***********************************************************************************************************************
** Function Name         : CanXL_RamAlloc
**
** Service ID            : NA
**
** Description           : This Allocate RAM with given size
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulCtrlIdx - Index of the controller
**                       : LulRamSize - size of memory to be allocated
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : LulRetAddress
**
** Preconditions         : None
**
** Global Variable(s)    : CanXL_GpRamManager
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : CAN_DUD_ACT_156
** Reference ID          : CAN_DUD_ACT_156_GBL001
***********************************************************************************************************************/
STATIC FUNC(uint32, CAN_PRIVATE_CODE) CanXL_RamAlloc(CONST(uint32, AUTOMATIC) LulCtrlIdx, 
                                                                                  CONST(uint32, AUTOMATIC) LulRamSize)
{
  VAR(uint32, AUTOMATIC) LulRequiredSize;
  
  uint32 LulRetAddress;
  CanXL_MemManagerType *LpHeapNode;
  CanXL_MemManagerType *LpNewBlock;

  LulRetAddress = 0U;

  LulRequiredSize = CAN_ALIGN_TO_32BIT((LulRamSize + (uint32)sizeof(CanXL_MemManagerType)));                            /* PRQA S 3469, 3383, 3384 # JV-01, JV-01, JV-01 */
  /* Allocation algorithm with circular list */
  LpHeapNode = CanXL_GpRamManager[LulCtrlIdx];
  do
  {
    /* If block of heap node is not reserved and block size is more than required size */
    if ((CAN_FALSE == LpHeapNode->blHeapLock) && (LpHeapNode->ulHeapSize >= LulRequiredSize))
    {
      /* If block size of heap node-whether required size exceeds management area size of heap node */
      if ((LpHeapNode->ulHeapSize - LulRequiredSize) > (uint32)sizeof(CanXL_MemManagerType))
      {
        /* The create heap node */
        LpNewBlock = (CanXL_MemManagerType *)((uint8 *)LpHeapNode + LulRequiredSize);                                   /* PRQA S 3305, 0751, 0310, 0488 # JV-01, JV-01, JV-01, JV-01 */
        LpNewBlock->ulHeapSize = LpHeapNode->ulHeapSize - LulRequiredSize;
        LpNewBlock->blHeapLock = CAN_FALSE;

        /* Re-chain as circular list */
        LpHeapNode->pNext->pPrev = LpNewBlock;
        LpNewBlock->pNext = LpHeapNode->pNext;
        LpHeapNode->pNext = LpNewBlock;
        LpNewBlock->pPrev = LpHeapNode;

        /* Reserved this heap block */
        LpHeapNode->ulHeapSize = LulRequiredSize;
        LpHeapNode->blHeapLock = CAN_TRUE;

        /* Set next heap node search start position */
        CanXL_GpRamManager[LulCtrlIdx] = LpNewBlock;
      }
      else
      {
        /* Allocate this heap node without separate the heap node */
        LpHeapNode->blHeapLock = CAN_TRUE;
      }
      LulRetAddress = (uint32)LpHeapNode + (uint32)sizeof(CanXL_MemManagerType);                                        /* PRQA S 0306, 3383 # JV-01, JV-01 */
      break;
    }
    else
    {
      LpHeapNode = LpHeapNode->pNext;
    }    
  } while (LpHeapNode != CanXL_GpRamManager[LulCtrlIdx]);

  return (LulRetAddress);
}

/***********************************************************************************************************************
** Function Name         : CanXL_GetTxBuffer
**
** Service ID            : N/A
**
** Description           : Get a buffer from the Tx buffer ring
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LulCtrlIdx     : controller index
**                         LucPriority
**
** InOut Parameters      : LenBytePtr
**
** Output Parameters     : LpBufIdxPtr
**                         LpBufPtr
**
** Return parameter      : BUFREQ_OK
**                         BUFREQ_E_NOT_OK
**                         BUFREQ_E_OVFL
**                         BUFREQ_E_BUSY
**
** Preconditions         : None
**
** Global Variables Used : Can_GpConfig, CanXL_GaaTxAllocCnt, CanXL_GaaTxBufferMgrTable, CanXL_GaaCtrlStat
**
** Function(s) invoked   : CanXL_RamAlloc. 
**
** Registers Used        : None
**
** Reference ID          : CAN_DUD_ACT_157
** Reference ID          : CAN_DUD_ACT_157_GBL001, CAN_DUD_ACT_157_GBL002, CAN_DUD_ACT_157_GBL003, 
** Reference ID          : CAN_DUD_ACT_157_GBL004, CAN_DUD_ACT_157_CRT001, CAN_DUD_ACT_157_CRT002.
***********************************************************************************************************************/
STATIC FUNC(BufReq_ReturnType , CAN_PRIVATE_CODE) CanXL_GetTxBuffer(
  CONST(uint32, AUTOMATIC) LulCtrlIdx,
  CONST(uint8, AUTOMATIC) LucPriority,
  CONSTP2VAR(Eth_BufIdxType, AUTOMATIC, CAN_APPL_DATA) LpBufIdxPtr,                                                     /* PRQA S 3432 # JV-01 */
  CONSTP2VAR(uint8*, AUTOMATIC, CAN_APPL_DATA) LpBufPtr,                                                                /* PRQA S 3432 # JV-01 */
  CONSTP2VAR(uint16, AUTOMATIC, CAN_APPL_DATA) LenBytePtr)                                                              /* PRQA S 3432 # JV-01 */
{
  uint32 LulRingIdx;
  uint32 LulTxBufferMax;
  uint32 LulCounter;
  uint32 LulPriorityId;
  uint16 LusTxPayloadMax;
  uint8 LucQueueId;
  uint8 LucOffsetQueue;  
  Can_BufferType LucTxEthBuffer;
  BufReq_ReturnType LenReturnValue;
  P2CONST(Can_CanXLHWUnitInfoType, AUTOMATIC, CAN_APPL_DATA) LpHwUnitConfig;
  P2VAR(CanXL_BufHandlerType, AUTOMATIC, CAN_APPL_DATA) LpTxBufferNode;                                                 /* PRQA S 3432 # JV-01 */
  
  LpHwUnitConfig = (P2CONST(Can_CanXLHWUnitInfoType, AUTOMATIC, CAN_CONFIG_DATA))Can_GpConfig->pCanXLHWUnitInfo;        /* PRQA S 0316 # JV-01 */
  LpHwUnitConfig = &LpHwUnitConfig[LulCtrlIdx];
  
  /* Follow requirement CP_SWS_CanXL_00059: In case a matching configuration for parameter Priority exists in 
     CanXLEthEgressFifoIdx of the controller, the contained parameter CanXLEthEgressFifoCanXLPriority and 
     CanXLEthEgressFifoCanXLQueue shall be used. Otherwise the defaults CanXLCtrlEthDefaultPriority and 
     CanXLEthDefaultQueue do apply.*/
  
  if(0xFFU != LpHwUnitConfig->pTxEthQueueConfig->ucEthDefaultQueue)
  {
    /* Initialize Default Queue */
    LucQueueId = LpHwUnitConfig->pTxEthQueueConfig->ucEthDefaultQueue;
    /* Initialize CanXL priority ID */
    LulPriorityId = LpHwUnitConfig->pTxEthQueueConfig->usEthDefaultPriority;
    /* Initialize Tx Queue Type */
    LucTxEthBuffer = LpHwUnitConfig->pTxEthQueueConfig->ucTxDefaultQueueType;
    /* Loop all Eth Egress Fifo for Queue are configured */
    for (LulCounter = 0UL; LulCounter < LpHwUnitConfig->pTxEthQueueConfig->ulNoOfEthEgressFifo; LulCounter++)
    {
      /* check if match specific Queue is configured */
      if (LucPriority == LpHwUnitConfig->pTxEthQueueConfig->pTxEthEthEgressFifo[LulCounter].ucEthEgressFifoIdx)
      {
        /* Update new LucQueueId */
        LucQueueId = LpHwUnitConfig->pTxEthQueueConfig->pTxEthEthEgressFifo[LulCounter].ucEthQueue;
        /* Update new LulPriorityId */
        LulPriorityId = (uint32)LpHwUnitConfig->pTxEthQueueConfig->pTxEthEthEgressFifo[LulCounter].usEthPriority;
        /* Update new LucTxEthBuffer */
        LucTxEthBuffer = LpHwUnitConfig->pTxEthQueueConfig->pTxEthEthEgressFifo[LulCounter].ucTxQueueType;
        break;
      } /* else no action required*/
    }
  
    if (CANXL_QUEUETYPE_TXFIFO == LucTxEthBuffer)
    {
      /* get number of TX FIFO Queue */
      LulTxBufferMax = (uint32)LpHwUnitConfig->pTxFIFOQueueConfig[LucQueueId].usMaxNumDesc;
      /* get payloadmax: 14UL = 6 bytes SRC + 6 bytes DST + 2 byte EthType */
      LusTxPayloadMax = LpHwUnitConfig->pTxFIFOQueueConfig[LucQueueId].usPayloadSize;
      /* Initialize offset Queue */
      LucOffsetQueue = 0U;    
    }
    else
    {
      /* get number of TX Priority Queue */
      LulTxBufferMax = 1UL;
      /* get payloadmax: 14UL = 6 bytes SRC + 6 bytes DST + 2 byte EthType */
      LusTxPayloadMax = LpHwUnitConfig->pTxPriorityQueueConfig->usPayloadSize;
      /* Initialize offset Queue */
      LucOffsetQueue = CANXL_MAX_TXFIFOQUEUE; 
    }
    LucQueueId += LucOffsetQueue;                                                                                       /* PRQA S 3383 # JV-01 */ 
  
    /* If the requested size is smaller than the minimum size, expand it to the minimum size */
    /* if CANXL Frame is VLAN frame, so the minimun size need expand to 2 bytes for TCI(include VICD) */
    if ((uint16)2U > *LenBytePtr)
    {
      *LenBytePtr = (uint16)2U;
    } /* else no action required*/
  
    if (0UL == LulTxBufferMax)
    {
      LenReturnValue = BUFREQ_E_NOT_OK;
    }
    else if (*LenBytePtr > LusTxPayloadMax)
    {
      /* If the requested size is larger than the buffer, return error */
      *LenBytePtr = LusTxPayloadMax;
      LenReturnValue = BUFREQ_E_OVFL;
    }
    else
    {
      /* Enter the critical section protection */
      CAN_ENTER_CRITICAL_SECTION(CAN_RAM_DATA_PROTECTION);
      /* Check the number of the Tx buffers allocated */
      if (CanXL_GaaTxAllocCnt[LulCtrlIdx][LucQueueId] < LulTxBufferMax)
      {
        /* Get tx buffer index */
        LulRingIdx = CanXL_GaaCtrlStat[LulCtrlIdx].ulTxBufTail;
        LulCounter = 0U;
        while ((NULL_PTR != CanXL_GaaTxBufferMgrTable[LulCtrlIdx][LulRingIdx].pBufferHdr) && 
              (LulCounter <= CanXL_GaaTxBufferTotal[LulCtrlIdx]))
        {
          LulCounter++;
          LulRingIdx = (LulRingIdx + 1UL) % CanXL_GaaTxBufferTotal[LulCtrlIdx];                                         /* PRQA S 3383 # JV-01 */
        }
        /* new function */
        LpTxBufferNode = (CanXL_BufHandlerType *)CanXL_RamAlloc(LulCtrlIdx,                                             /* PRQA S 0306 # JV-01 */
                (uint32)(*LenBytePtr + CANXL_HEADER_SIZE + sizeof(CanXL_BufHandlerType)));                              /* PRQA S 3383 # JV-01 */
      
        if (NULL_PTR != LpTxBufferNode)
        {
          CanXL_GaaCtrlStat[LulCtrlIdx].ulTxBufTail = (LulRingIdx + 1UL) % CanXL_GaaTxBufferTotal[LulCtrlIdx];          /* PRQA S 3383 # JV-01 */
          CanXL_GaaTxBufferMgrTable[LulCtrlIdx][LulRingIdx].pBufferHdr = LpTxBufferNode;
          CanXL_GaaTxBufferMgrTable[LulCtrlIdx][LulRingIdx].blTxOngoing = CAN_FALSE;
        
          LpTxBufferNode->ulbufIdx = LulRingIdx;
          LpTxBufferNode->ulbufAddr = (uint32)LpTxBufferNode + sizeof(CanXL_BufHandlerType);                            /* PRQA S 3383, 0306 # JV-01, JV-01 */
          LpTxBufferNode->ulTxLength  = 0UL;
          LpTxBufferNode->ulPriority  = LulPriorityId;
          LpTxBufferNode->ucQueue     = LucQueueId;
          LpTxBufferNode->ucQueueType = LucTxEthBuffer;
          LpTxBufferNode->blbenableTS = CAN_FALSE;
          LpTxBufferNode->blTxConfirm = CAN_FALSE;
          #if (CAN_CANXL_GLOBAL_TIME_SUPPORT == STD_ON)
          LpTxBufferNode->enTimeQual = ETH_INVALID;
          LpTxBufferNode->stTimeStamp.nanoseconds = (uint32)0UL;
          LpTxBufferNode->stTimeStamp.seconds     = (uint32)0UL;
          LpTxBufferNode->stTimeStamp.secondsHi   = (uint16)0U;
          #endif
        
          *LpBufIdxPtr = (Eth_BufIdxType)LpTxBufferNode->ulbufIdx;
          *LpBufPtr = (uint8 *)(LpTxBufferNode->ulbufAddr + CANXL_HEADER_SIZE);                                           /* PRQA S 3383, 0306 # JV-01, JV-01 */
          LpTxBufferNode->ulEthTypeAddr = LpTxBufferNode->ulbufAddr + CANXL_SRC_DST_ADDRESS_SIZE;                         /* PRQA S 3383 # JV-01 */
          LenReturnValue = BUFREQ_OK;
          /* Increment Tx buffer counter */
          CanXL_GaaTxAllocCnt[LulCtrlIdx][LucQueueId]++;
        }
        else
        {
          LenReturnValue = BUFREQ_E_BUSY;
        }
      }
      else
      {
        LenReturnValue = BUFREQ_E_BUSY;
      }
      /* Exit the critical section protection */
      CAN_EXIT_CRITICAL_SECTION(CAN_RAM_DATA_PROTECTION);
    }
  }
  else
  {
    LenReturnValue = BUFREQ_E_NOT_OK;
  }
  return LenReturnValue;
}

/***********************************************************************************************************************
** Function Name         : CanXL_InitializeBuffer
**
** Service ID            : N/A
**
** Description           : Initialize the Tx buffer ring
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : LulCtrlIdx     : controller index
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variables Used : CanXL_GaaTxAllocCnt, CanXL_GaaTxBufferTotal,
**                         CanXL_GaaTxBufferMgrTable, CanXL_GaaCtrlStat,
**                         CanXL_GaaRxFrame
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : CAN_DUD_ACT_158,
** Reference ID          : CAN_DUD_ACT_158_GBL001, CAN_DUD_ACT_158_GBL002, CAN_DUD_ACT_158_GBL003, 
** Reference ID          : CAN_DUD_ACT_158_GBL004, CAN_DUD_ACT_158_GBL005, CAN_DUD_ACT_158_GBL006,
** Reference ID          : CAN_DUD_ACT_158_GBL007, CAN_DUD_ACT_158_GBL008, CAN_DUD_ACT_158_GBL009,
** Reference ID          : CAN_DUD_ACT_158_GBL010
***********************************************************************************************************************/
STATIC FUNC(void, CAN_PRIVATE_CODE) CanXL_InitializeBuffer(CONST(uint32, AUTOMATIC) LulCtrlIdx)
{
  uint32 LulCnt;
  P2VAR(volatile CanXL_TxBufferType, AUTOMATIC, CanXL_APPL_DATA) LpTxBuffer;

  /* Initialize resource information */
  CanXL_GaaCtrlStat[LulCtrlIdx].ulTxBufTail = 0UL;
  CanXL_GaaRxFrame[LulCtrlIdx].ulFrameAddr = 0UL;
  CanXL_GaaRxFrame[LulCtrlIdx].ulEthTypeAddr = 0UL;
  CanXL_GaaRxFrame[LulCtrlIdx].ulFrameLength = 0UL;
  #if (CAN_CANXL_GLOBAL_TIME_SUPPORT == STD_ON)
  /* Reset Timestamp value */
  CanXL_GaaRxFrame[LulCtrlIdx].stTimestamp.ulElement2TS0 = 0UL;
  CanXL_GaaRxFrame[LulCtrlIdx].stTimestamp.ulElement3TS1 = 0UL;
  #endif
  /* Initialize Tx buffer index list */
  for (LulCnt = 0UL; LulCnt < CanXL_GaaTxBufferTotal[LulCtrlIdx]; LulCnt++)
  {
    LpTxBuffer = (P2VAR(volatile CanXL_TxBufferType, 
                         AUTOMATIC, CANXL_APPL_DATA))&CanXL_GaaTxBufferMgrTable[LulCtrlIdx][LulCnt];
    /* Reset buffers */
    LpTxBuffer->pBufferHdr = NULL_PTR;
    /* Reset Tx Buffer status */
    LpTxBuffer->blTxOngoing = CAN_FALSE;
  }

  /* Initialize buffer counter */
  for (LulCnt = 0UL; LulCnt < CANXL_MAX_TXQUEUE; LulCnt++)
  {
    /* Reset Tx buffer was allocated */
    CanXL_GaaTxAllocCnt[LulCtrlIdx][LulCnt] = 0UL;
    CanXL_GaaCtrlStat[LulCtrlIdx].stHwStatSDT5.aaBufTxCnt[LulCnt] = 0UL;
  }
}

/***********************************************************************************************************************
** Function Name         : CanXL_HwCheckQueueIndex
**
** Service ID            : N/A
**
** Description           : Check the validity of the Queue index specified
**                         in the CanXL_Receive.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LulCtrlIdx     : Index of a controller
**                         LulQueueIdx    : the Queue index
**
** InOut Parameters      : None
**
** Output Parameters     : LulOutQueueIdx : Queue index
**
** Return parameter      : LucReturnValue E_OK / E_NOT_OK
**
** Preconditions         : None
**
** Global Variable(s)    : Can_GpConfig
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : CAN_DUD_ACT_172
***********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, CAN_PRIVATE_CODE) CanXL_HwCheckQueueIndex( CONST(uint32, AUTOMATIC) CtrlIdx, 
                                           VAR(uint32, AUTOMATIC) LulQueueIdx, VAR(uint32 *, AUTOMATIC) LulOutQueueIdx)
{
  Std_ReturnType LucReturnValue;
  uint8 LucCounter;
  P2CONST(Can_CanXLHWUnitInfoType, AUTOMATIC, CAN_CONFIG_DATA) LpCanXLHWInfo;

  LpCanXLHWInfo = (P2CONST(Can_CanXLHWUnitInfoType, AUTOMATIC, CAN_CONFIG_DATA))Can_GpConfig->pCanXLHWUnitInfo;         /* PRQA S 0316 # JV-01 */
  LucReturnValue = E_NOT_OK;
  *LulOutQueueIdx = 0UL;
  
  /* Validity check for the Queue index */
  if (0U == LpCanXLHWInfo[CtrlIdx].pRxEthQueueConfig->ucNoOfEthIngressFifo)
  {
    /* No action require */
  }
  else
  {
    for (LucCounter = 0U; LucCounter < LpCanXLHWInfo[CtrlIdx].pRxEthQueueConfig->ucNoOfEthIngressFifo;LucCounter++)
    {
      if(LulQueueIdx == LpCanXLHWInfo[CtrlIdx].pRxEthQueueConfig->pRxEthIngressFifo[LucCounter].ucEthIngressFifoIdx)
      {
        /* Get Queue index */
        *LulOutQueueIdx = LpCanXLHWInfo[CtrlIdx].pRxEthQueueConfig->pRxEthIngressFifo[LucCounter].ucEthFIFOQueue;
        LucReturnValue = E_OK;
        break;
      } /* else no action required*/
    }
  }

  return LucReturnValue;
}

/***********************************************************************************************************************
** Function Name         : CanXL_IsMatchFilter
**
** Service ID            : N/A
**
** Description           : Add a address filter to the filter list
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : LulCtrlIdx: Index of a controller
**                         LpMacAddr : Pointer to a MAC address
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : boolean
**                         CAN_TRUE  : Allow reception to specified MACaddress
**                         CAN_FALSE : Reject reception to specified MACaddress
**
** Preconditions         : None
**
** Global Variable(s)    : CanXL_GaaMacFilterMng, CanXL_GaaCtrlStat,
**                         CanXL_GstBroadcastAddr
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : CAN_DUD_ACT_159
** Reference ID          : CAN_DUD_ACT_159_CRT001, CAN_DUD_ACT_159_CRT002, CAN_DUD_ACT_159_CRT003
** Reference ID          : CAN_DUD_ACT_159_GBL001
***********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, CAN_PRIVATE_CODE) CanXL_IsMatchFilter(
  CONST(uint32, AUTOMATIC) LulCtrlIdx,
  CONSTP2CONST(CanXL_MacAddressType, AUTOMATIC, CAN_APPL_DATA) LpMacAddr)
{
  P2CONST(CanXL_MacFilterMng, AUTOMATIC, CAN_APPL_DATA) LpMng;
  uint32 LulIdx;
  Std_ReturnType LbResult;
  
  LbResult = E_NOT_OK;

  /* Get Mac Filter Manager */
  LpMng = &(CanXL_GaaMacFilterMng[LulCtrlIdx]);
  
  if (0UL < LpMng->ulPromiscuousCount)
  {
    /* Always returns True when in promiscuous mode */
    LbResult = E_OK;
  }
  else if (0UL == CANXL_COMPARE_MAC(*LpMacAddr, CanXL_GstBroadcastAddr))                                                /* PRQA S 3469 # JV-01 */
  {
    /* Always returns True when Broadcat Address */
    LbResult = E_OK;
  }
  else
  {
    if (0UL == CANXL_COMPARE_MAC(*LpMacAddr, CanXL_GaaCtrlStat[LulCtrlIdx].stMacAddr))                                  /* PRQA S 3464, 3469, 0404 # JV-01, JV-01, JV-01 */
    {
      /* Always returns True when Own MAC Address */
      LbResult = E_OK;
    }
    else
    {
      /* Check Filter Macthing */
      for (LulIdx = 0; ((LulIdx < CANXL_MAX_FILTERS) && (E_NOT_OK == LbResult)); LulIdx++)
      {
        if ((0UL < LpMng->stFilter[LulIdx].ulCount) &&
          (0UL == CANXL_COMPARE_MAC(*LpMacAddr, LpMng->stFilter[LulIdx].stMacAddr)))                                    /* PRQA S 3469 # JV-01 */
        {
          LbResult = E_OK;
        } /* else no action required*/
      }
    }
  }

  return LbResult;
}

/***********************************************************************************************************************
** Function Name         : CanXL_IsRxFrameValid
**
** Service ID            : NA
**
** Description           : Compare Mac Address Frame just received with
**                         Broadcast and Controller Mac Address.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LpRxFrame. Pointer to the Frame just received
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : LblPass
**                         True : Frame DA is Broadcast or
**                         matches with the Source Address of this Controller
**                         False : Otherwise
**
** Preconditions         : None
**
** Global Variables Used : None
**                         
**
** Function(s) invoked   : CanXL_IsMatchFilter
**
** Registers Used        : None
**
** Reference ID          : CAN_DUD_ACT_171
***********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, CAN_PRIVATE_CODE) CanXL_IsRxFrameValid(
  CONST(uint32, AUTOMATIC) LulCtrlIdx,
  CONSTP2CONST(CanXL_RxFrameType, AUTOMATIC, CAN_APPL_DATA) LpRxFrame)
{
  CanXL_MacAddressType LstDstAddress;
  Std_ReturnType LblPass;

  CANXL_PACK_ADDRESS_FROM_8(((P2VAR(uint8, AUTOMATIC, CAN_APPL_DATA))LpRxFrame->ulFrameAddr), LstDstAddress);           /* PRQA S 3432, 3469, 0306 # JV-01, JV-01, JV-01 */
  
  LblPass = CanXL_IsMatchFilter(LulCtrlIdx, &LstDstAddress);

  return LblPass;
}

/***********************************************************************************************************************
** Function Name         : CanXL_RxCallEthIf
**
** Service ID            : NA
**
** Description           : Wrapper for the Callback to the Eth Interface
**                         for each frame received
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulCtrlIdx - Controller / Channel Index
**                       : LpFrame - Address of the Received Frame in URAM
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : NA
**
** Global Variables Used : CanXL_GstBroadcastAddr
**
** Function(s) invoked   : EthIf_RxIndication,
**
** Registers Used        : None
**
** Reference ID          : CAN_DUD_ACT_160
***********************************************************************************************************************/
STATIC FUNC(void, CAN_PRIVATE_CODE) CanXL_RxCallEthIf(
  CONST(uint32, AUTOMATIC) LulCtrlIdx,
  CONSTP2CONST(CanXL_RxFrameType, AUTOMATIC, CAN_APPL_DATA) LpFrame)
{
  boolean LblBroadcast;

  P2CONST(Eth_DataType, AUTOMATIC, CAN_APPL_DATA) LpFrameType;
  P2CONST(Eth_DataType, AUTOMATIC, CAN_APPL_DATA) LpData;

  Eth_FrameType LddFrameType;
  CanXL_MacAddressType LstMacAddr;

  P2CONST(CanXL_EtherFrameType, AUTOMATIC, CAN_APPL_DATA) LstEtherFrame;

  LstEtherFrame = (P2CONST(CanXL_EtherFrameType, AUTOMATIC, CAN_APPL_DATA)) LpFrame->ulFrameAddr;                       /* PRQA S 0306 # JV-01 */
  LpData = (const Eth_DataType *)LstEtherFrame;                                                                         /* PRQA S 0751 # JV-01 */
  CANXL_PACK_ADDRESS_FROM_8(LstEtherFrame->ucDstAddr, LstMacAddr);                                                      /* PRQA S 3469 # JV-01 */

  if (0UL == CANXL_COMPARE_MAC(LstMacAddr, CanXL_GstBroadcastAddr))                                                     /* PRQA S 3469 # JV-01 */
  {
    LblBroadcast = CAN_TRUE;
  }
  else
  {
    LblBroadcast = CAN_FALSE;
  }

  LpFrameType = (const Eth_DataType *)LpFrame->ulEthTypeAddr;                                                           /* PRQA S 0306 # JV-01 */

  LddFrameType = (Eth_FrameType)((uint32)LpFrameType[0] << CANXL_BYTE_BITS);

  LddFrameType |= (Eth_FrameType)LpFrameType[1];

  /* Since the maximum value of Controller Index is 4, casting to uint8 does no problem. */
  EthIf_RxIndication((uint8)(LulCtrlIdx + CAN_CONTROLLER_OFFSET), LddFrameType, LblBroadcast, LstEtherFrame->ucSrcAddr, /* PRQA S 3383, 2985 # JV-01, JV-01 */
    LpData + CANXL_HEADER_SIZE, (uint16)(LpFrame->ulFrameLength - CANXL_HEADER_SIZE));                                  /* PRQA S 0488, 3383 # JV-01, JV-01 */

}
/***********************************************************************************************************************
** Function Name         : CanXL_IsMatchVCID
**
** Service ID            : NA
**
** Description           : Process check VCID Queue.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulCtrlIdx  - Instance number
**                       : LucQueueIdx - Rx queue index
**                       : LpTargetDesc - Target descriptor
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : CAN_TRUE/CAN_FALSE
**
** Preconditions         : None
**
** Global Variable(s)    : Can_GpConfig
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : CAN_DUD_ACT_161
***********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, CAN_PRIVATE_CODE) CanXL_IsMatchVCID( CONST(uint32, AUTOMATIC) LulCtrlIdx, 
            CONST(uint32, AUTOMATIC) LulQueueIdx, P2VAR(Can_RxDescriptorsType, AUTOMATIC, CAN_APPL_DATA) LpTargetDesc)  /* PRQA S 3673, 3432 # JV-01, JV-01 */
{
  Std_ReturnType LucReturn;
  uint8 LucNoOfVCID;
  uint8 LucCounter;
  uint8 LucRxFIFOQueue;
  uint8 LucEthVCID;
  uint8 LucCtrlInfoIndex;
  uint8 LucVcidCounter;
  P2CONST(uint8, TYPEDEF, CAN_CONFIG_DATA) LpRxVICD;
  P2CONST(Can_CanXLHWUnitInfoType, AUTOMATIC, CAN_CONFIG_DATA) LpCanXLHWInfo;
  /* Get PBConfig data for this CANXL unit */
  LpCanXLHWInfo = (P2CONST(Can_CanXLHWUnitInfoType, AUTOMATIC, CAN_CONFIG_DATA))Can_GpConfig->pCanXLHWUnitInfo;         /* PRQA S 0316 # JV-01 */
  LucCtrlInfoIndex = Can_GpConfig->pCanXLSecondPhysicalControllerToIndex[LulCtrlIdx];
  LucReturn = E_NOT_OK;
  /* Get VCID from new frame is comming */
  LucEthVCID = (uint8)((*((uint32 *)LpTargetDesc->ulElement1) & CANXL_RX_VCID_MASK ) >> 8U);                            /* PRQA S 0306 # JV-01 */
  /* Loop for all Rx ETh Queue is configured */
  for (LucCounter = 0U;  ((LucCounter < LpCanXLHWInfo[LucCtrlInfoIndex].pRxEthQueueConfig->ucNoOfEthIngressFifo)
                          && (E_NOT_OK == LucReturn)); LucCounter++)
  {
    /* Get Queue index is configured */
    LucRxFIFOQueue = LpCanXLHWInfo[LucCtrlInfoIndex].pRxEthQueueConfig->pRxEthIngressFifo[LucCounter].ucEthFIFOQueue;
    if(LulQueueIdx == LucRxFIFOQueue)
    {
      /* Get VCID is configured */
      LucNoOfVCID = LpCanXLHWInfo[LucCtrlInfoIndex].pRxEthQueueConfig->
                                                pRxEthIngressFifo[LucCounter].ucNoOfVCIDConfigured;
      /* check a VCID to be accepted by this FIFO. If not present, all VCIDs shall be accepted. */
      if(0U != LucNoOfVCID)
      {
        LpRxVICD = LpCanXLHWInfo[LucCtrlInfoIndex].pRxEthQueueConfig->pRxEthIngressFifo[LucCounter].pVcidConfig;
        for(LucVcidCounter = 0U; LucVcidCounter < LucNoOfVCID; LucVcidCounter++)
        {
          if(LucEthVCID == LpRxVICD[LucVcidCounter])
          {
            /* Match VCID */
            LucReturn = E_OK;
            break;
          } /* else do nothing*/
        }
      }
      else
      {
        LucReturn = E_OK;
        break;
      }
    } /* else do nothing*/
  }
  return LucReturn;
}
/***********************************************************************************************************************
** Function Name         : CanXL_RxQueueProcess
**
** Service ID            : NA
**
** Description           : Process Receive Queue.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulCtrlIdx  - Instance number
**                       : LucQueueIdx - Rx queue index
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : When polling mode:
**                           CANXL_EXT_NOT_RECEIVED : there was no received frame
**                           CANXL_EXT_RECEIVED     : there was one received frame
**                           CANXL_EXT_RECEIVED_MORE_DATA_AVAILABLE:
**                                 there were more than one received frames
**                           CANXL_EXT_NOT_RECEIVED_MORE_DATA_AVAILABLE:
**                                 there was no received, but there are still receive frames.
**
** Preconditions         : None
**
** Global Variable(s)    : CanXL_GaaCtrlStat, CanXL_GaaRxFrame, CanXL_GaaRegs
**
** Function(s) invoked   : CanXL_IsRxFrameValid, CanXL_RxCallEthIf, CanXL_IsMatchVCID
**
** Registers Used        : ulRXFQINSTS, ulFUNCCLR
**
** Reference ID          : CAN_DUD_ACT_162,
** Reference ID          : CAN_DUD_ACT_162_GBL001, CAN_DUD_ACT_162_GBL002, CAN_DUD_ACT_162_GBL003, 
** Reference ID          : CAN_DUD_ACT_162_GBL004, CAN_DUD_ACT_162_GBL005, CAN_DUD_ACT_162_GBL006,
** Reference ID          : CAN_DUD_ACT_162_REG001, CAN_DUD_ACT_162_ERR001
***********************************************************************************************************************/
FUNC(CanXL_ExtRxStatusType, CAN_PRIVATE_CODE) CanXL_RxQueueProcess(                                                     /* PRQA S 1505, 3006 # JV-01, JV-01 */
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulQueueIdx)
{
  CanXL_ExtRxStatusType LenRetValue;
  VAR(Std_ReturnType, AUTOMATIC) LenResult;
  VAR(uint32, CAN_VAR_NO_INIT) LaaCanSdu[CANXL_MAX_PAYLOAD / sizeof(uint32)];
  P2VAR(Can_RxDescriptorsType, AUTOMATIC, CAN_APPL_DATA) LpCurrentDesc;                                                 /* PRQA S 3432 # JV-01 */
  P2VAR(volatile uint32, AUTOMATIC, CAN_APPL_DATA) LpData;
  P2VAR(Can_RxDescriptorsType, AUTOMATIC, CAN_APPL_DATA) LpDataDesc;                                                    /* PRQA S 3432 # JV-01 */
  P2VAR(Can_RxDescriptorsType, AUTOMATIC, CAN_APPL_DATA) LpTmpDesc;                                                     /* PRQA S 3432 # JV-01 */
  VAR(uint8, AUTOMATIC) LucChannelId;
  VAR(uint8, AUTOMATIC) LucCtrlInfoIndex;

  LucChannelId = Can_GpPCController[LulCtrlIdx].ucCh;
  LucCtrlInfoIndex = Can_GpConfig->pCanXLSecondPhysicalControllerToIndex[LucChannelId];
  LenRetValue = CANXL_EXT_NOT_RECEIVED;

  if (0UL != (CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulRXFQINSTS & (1UL << LulQueueIdx)))
  {
    /* Check if RX FIFO Queue is on-hold or not */
    if (0UL != (CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulRXFQSTS1 & (1UL << LulQueueIdx)))
    {
      /* Report to DET runtime error*/
      (void)Det_ReportRuntimeError(CANXL_MODULE_ID, CANXL_INSTANCE_ID, CANXL_RECEIVE_SID, CAN_E_DATALOST);
      RH850_SET_IOREG_SYNCP(32, &CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulRXFQCTRL0, (1UL << LulQueueIdx));               /* PRQA S 3464, 1006 # JV-01, JV-01 */
    }/* else no action required */

    /* Read next descriptor */
    LpDataDesc = CanXL_GaaCtrlStat[LucCtrlInfoIndex].stHwStatSDT5.aaHeadRxDesc[LulQueueIdx];

    if(CAN_COMMON_STATE_STARTED == Can_GaaCtrlState[LulCtrlIdx].enMode)
    {
      LpCurrentDesc = 
                  (Can_RxDescriptorsType *)(CanXL_GaaRegs[LucCtrlInfoIndex].pMH->aaRXFQReg[LulQueueIdx].ulRXADDPT);     /* PRQA S 0306 # JV-01 */
    }
    else
    {
      LpCurrentDesc = LpDataDesc;
    }  
    /* Loop target descriptor to current pointer addess  */
    do
    {
      /* Check if the next target descriptor is ETH Frame */
      if ((CANXL_EXT_NOT_RECEIVED == LenRetValue) && \
          (((CANXL_BIT_SDT(5U) | CANXL_BIT_XLF)) == ((*((uint32 *)LpDataDesc->ulElement1)) & CANXL_RX_SDT_MASK)) &&     /* PRQA S 0306, 3469 # JV-01, JV-01 */\
          (0UL != (LpDataDesc->ulElement0 & CANXL_RX_BIT_VALID(0x01U))))                                                /* PRQA S 3469 # JV-01 */
      {
        /* Store a Rx descriptor to Temp descriptor local variable */
        LpTmpDesc = LpDataDesc;
        /* Update return Value */
        LenRetValue = CANXL_EXT_RECEIVED;
      } /* else no action required*/

      /* Get Next descriptor */
      if(LpDataDesc != CanXL_GaaCtrlStat[LucCtrlInfoIndex].stHwStatFixed.aaLastRxDesc[LulQueueIdx])
      {
        LpDataDesc += 1UL;                                                                                              /* PRQA S 0489 # JV-01 */
      }
      else
      {
        LpDataDesc = CanXL_GaaCtrlStat[LucCtrlInfoIndex].stHwStatFixed.aaFirstRxDesc[LulQueueIdx];
      }
      /* Check if the next target descriptor is ETH Frame & previous descriptor is ETH Frame too */
      if ((CANXL_EXT_RECEIVED == LenRetValue) && \
          (((CANXL_BIT_SDT(5U) | CANXL_BIT_XLF)) == ((*((uint32 *)LpDataDesc->ulElement1)) & CANXL_RX_SDT_MASK)) &&     /* PRQA S 0306, 3469 # JV-01, JV-01 */\
          (0UL != (LpDataDesc->ulElement0 & CANXL_RX_BIT_VALID(0x01U))))                                                /* PRQA S 3469 # JV-01 */
      {
        /* Update return value of next frames is AVAILABLE */
        LenRetValue = CANXL_EXT_RECEIVED_MORE_DATA_AVAILABLE;
        break;
      } /* else no action required*/
      /* Check the next descriptor equal to current pointer addess */
    } while (LpDataDesc != LpCurrentDesc);
  }

  /* Check descriptor is invalid & SDU Type is 5UL */
  if (CANXL_EXT_NOT_RECEIVED != LenRetValue)
  {
    LpData = (uint32 *)LpTmpDesc->ulElement1;                                                                           /* PRQA S 0306, 2963 # JV-01, JV-01 */
    LenResult = CanXL_ConsistentCheck(LucCtrlInfoIndex, LpData, 5);
    if(E_NOT_OK == LenResult)
    {
      #if (CAN_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportRuntimeError(CANXL_MODULE_ID, CANXL_INSTANCE_ID, CANXL_RECEIVE_SID, CANXL_E_INV_DATA);
      #endif
    }
    else
    {
      /* Check VCID */
      LenResult = CanXL_IsMatchVCID(LucChannelId, LulQueueIdx, LpTmpDesc);                                              /* PRQA S 2963 # JV-01 */
      if (E_OK == LenResult)
      {
        CanXL_WriteRxData(LucCtrlInfoIndex, LulQueueIdx, LpTmpDesc, &LaaCanSdu[0]);
        CAN_ENTER_CRITICAL_SECTION(CAN_RAM_DATA_PROTECTION);
        /* Set Rx descriptor info */
        CanXL_GaaRxFrame[LucCtrlInfoIndex].ulFrameAddr = (uint32)LaaCanSdu;                                             /* PRQA S 0306 # JV-01 */
        CanXL_GaaRxFrame[LucCtrlInfoIndex].ulEthTypeAddr = (uint32)(LaaCanSdu + 3U);                                    /* PRQA S 0488, 0306 # JV-01, JV-01 */
        CanXL_GaaRxFrame[LucCtrlInfoIndex].ulFrameLength = (((*(LpData + 1UL)) >> 16U) & CANXL_DLC_MASK) + 1U;          /* PRQA S 3383, 0489 # JV-01, JV-01 */

        #if (CAN_CANXL_GLOBAL_TIME_SUPPORT == STD_ON)
        CanXL_GaaRxFrame[LucCtrlInfoIndex].stTimestamp.ulElement2TS0 = LpTmpDesc->ulElement2TS0;                        /* PRQA S 2963 # JV-01 */
        CanXL_GaaRxFrame[LucCtrlInfoIndex].stTimestamp.ulElement3TS1 = LpTmpDesc->ulElement3TS1;                        /* PRQA S 2963 # JV-01 */
        #endif

        /* check whether received frame is valid or not */
        LenResult = CanXL_IsRxFrameValid(LucCtrlInfoIndex, &CanXL_GaaRxFrame[LucCtrlInfoIndex]);

        if (E_OK == LenResult)
        {
          /* Call EthIf if the Frame Received is valid */
          CanXL_RxCallEthIf(LulCtrlIdx, &CanXL_GaaRxFrame[LucCtrlInfoIndex]);
        } /* else do nothing */
          /* Frame Invalid - E.g. Multicast to be discarded */
          /* No Call of EthIf */
          /* Update return value */
        CAN_EXIT_CRITICAL_SECTION(CAN_RAM_DATA_PROTECTION);
      } /* else do nothing */
        /* VCID Invalid - E.g.*/
        /* No Call of EthIf */
        /* Update return value */
    }
    
    /* Reset Rx descriptor */
    LpTmpDesc-> ulElement0 &= ~(0xF000000FUL);                                                                          /* PRQA S 2963 # JV-01 */
    *LpData = 0UL;
    #if (CAN_CANXL_GLOBAL_TIME_SUPPORT == STD_ON)
    LpTmpDesc->ulElement2TS0 = 0UL;
    LpTmpDesc->ulElement3TS1 = 0UL;
    #endif /* CANXL_GLOBAL_TIME_SUPPORT */
    
    if(LenRetValue == CANXL_EXT_RECEIVED)
    {
      /* Clear interrupt */
      CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulRXFQINSTS &= (1UL << (LulQueueIdx));
      
      /* Update Next descriptor */
      CanXL_GaaCtrlStat[LucCtrlInfoIndex].stHwStatSDT5.aaHeadRxDesc[LulQueueIdx] = LpCurrentDesc;
    }
    else
    {
      /* Update Next descriptor */
      CanXL_GaaCtrlStat[LucCtrlInfoIndex].stHwStatSDT5.aaHeadRxDesc[LulQueueIdx] = LpDataDesc;
    }
            
    if(E_NOT_OK == LenResult)
    {
      if(LenRetValue == CANXL_EXT_RECEIVED)
      {
        LenRetValue = CANXL_EXT_NOT_RECEIVED;
      }
      else
      {
        LenRetValue = CANXL_EXT_NOT_RECEIVED_MORE_DATA_AVAILABLE;
      } /* else no action required*/
    }
  } /* else no action required*/
  return LenRetValue;
}

/***********************************************************************************************************************
** Function Name         : CanXL_HwReceive
**
** Service ID            : N/A
**
** Description           : Performs reception processing in polling mode.
**                         When polling mode:
**                           Receive one frame and indicate it EthIf
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : LulCtrlIdx     : Index of a controller
**                         LulQueueIdx    : Index of a Queue
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : When polling mode:
**                           ETH_NOT_RECEIVED : there was no received frame
**                           ETH_RECEIVED     : there was one received frame
**                           ETH_RECEIVED_MORE_DATA_AVAILABLE:
**                                 there were more than one received frames
**
** Preconditions         : None
**
** Global Variable(s)    : CanXL_GaaRegs, Can_GpConfig
**
** Function(s) invoked   : CanXL_RxQueueProcess, Can_WaitRegisterChange
**
** Registers Used        : None
**
** Reference ID          : CAN_DUD_ACT_163
***********************************************************************************************************************/
STATIC FUNC(Eth_RxStatusType, CAN_PRIVATE_CODE) CanXL_HwReceive(
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulQueueIdx)
{
  CanXL_ExtRxStatusType LenRetValue;

  do
  {
  LenRetValue = CanXL_RxQueueProcess(LulCtrlIdx, LulQueueIdx);
  } while (CANXL_EXT_NOT_RECEIVED_MORE_DATA_AVAILABLE == LenRetValue);
  return (Eth_RxStatusType)LenRetValue;                                                                                 /* PRQA S 4322 # JV-01 */
}

/***********************************************************************************************************************
** Function Name         : CanXL_PreprocessFrame
**
** Service ID            : N/A
**
** Description           : This function sets the destination MAC address
**                         and Ethernet type for the Tx buffer.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulCtrlIdx     : controller index
**                         LulBufIdx      : index to the buffer
**                         LulFrameType   : ether type
**                         LpPhysAddrPtr  : destination mac address
**                         LpPayloadLen   : payload length
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variables Used : CanXL_GaaTxBufferMgrTable, CanXL_GaaCtrlStat
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : CAN_DUD_ACT_164
** Reference ID          : CAN_DUD_ACT_164_CRT001, CAN_DUD_ACT_164_CRT002,
** Reference ID          : CAN_DUD_ACT_164_GBL001, CAN_DUD_ACT_164_GBL002
***********************************************************************************************************************/
STATIC FUNC(void, CAN_PRIVATE_CODE) CanXL_PreprocessFrame(
  CONST(uint32, AUTOMATIC) LulCtrlIdx,
  CONST(uint32, AUTOMATIC) LulBufIdx,
  CONST(uint32, AUTOMATIC) LulFrameType,
  CONSTP2CONST(uint8, AUTOMATIC, CAN_APPL_DATA) LpPhysAddrPtr,
  P2VAR(uint32, AUTOMATIC, CAN_APPL_DATA) LpVCID)                                                                       /* PRQA S 3432 # JV-01 */
{
  P2VAR(Eth_DataType, AUTOMATIC, CAN_APPL_DATA) LpBufPtr;                                                               /* PRQA S 3432 # JV-01 */
  P2CONST(CanXL_BufHandlerType, AUTOMATIC, CAN_APPL_DATA) LpBufHandlerPtr;

  CAN_ENTER_CRITICAL_SECTION(CAN_RAM_DATA_PROTECTION);

  /* Get Tx buffer address */
  LpBufHandlerPtr = CanXL_GaaTxBufferMgrTable[LulCtrlIdx][LulBufIdx].pBufferHdr;

  CAN_EXIT_CRITICAL_SECTION(CAN_RAM_DATA_PROTECTION);

  LpBufPtr = (Eth_DataType *)LpBufHandlerPtr->ulbufAddr;                                                                /* PRQA S 0306 # JV-01 */

  /* Get VICD if EtherType is C-LAN or S-VLAN */
  /* refer to section 5.6 IEEE 802.3 (MAC frame) mapped tunneling into SDT specification file */
  if ((CANXL_CVLAN_TAG == LulFrameType) || (CANXL_SVLAN_TAG == LulFrameType))
  {
    *LpVCID = *(LpBufPtr + CANXL_HEADER_SIZE + 1UL);                                                                    /* PRQA S 0488, 0489 # JV-01, JV-01 */
  }      
  else
  {
    *LpVCID = 0U;
  }

  /* Copy destination address */
  CANXL_COPY_MAC_ADDRESS((CONST(uint8, AUTOMATIC) *)LpPhysAddrPtr, (uint8 *)LpBufPtr);                                  /* PRQA S 3469 # JV-01 */

  LpBufPtr = LpBufPtr + 6UL;                                                                                            /* PRQA S 0488 # JV-01 */

  CANXL_UNPACK_ADDRESS_TO_8(CanXL_GaaCtrlStat[LulCtrlIdx].stMacAddr, LpBufPtr);                                         /* PRQA S 3469 # JV-01 */

  LpBufPtr = LpBufPtr + 6UL;                                                                                            /* PRQA S 0488, 2982 # JV-01, JV-01 */

  /* Casted to uint8 to extract the required 1 byte. */
  LpBufPtr = (Eth_DataType *)LpBufHandlerPtr->ulEthTypeAddr;                                                            /* PRQA S 0306 # JV-01 */

  *LpBufPtr = (Eth_DataType)((uint8)(LulFrameType >> CANXL_BYTE_BITS));

  LpBufPtr++;
  /* Casted to uint8 to extract the required 1 byte. */
  *LpBufPtr = (Eth_DataType)((uint8)(LulFrameType));                                                                    /* PRQA S 2907 # JV-01 */
  
}

/***********************************************************************************************************************
** Function Name         : CanXL_HwTransmit
**
** Service ID            : N/A
**
** Description           : Initiates a transmission on an CANXL controller.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : LulCtrlIdx     : Index of a controller
**                         LulBufIdx      : index of a tx buffer
**                         LulLenByte     : byte length of a payload
**                         LblConfirmation: Whether TxConfirmation is required when a transmission finished
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : E_OK : Success
**                         E_NOT_OK : Failure
**
** Preconditions         : None
**
** Global Variable(s)    : Can_GpConfig, CanXL_GaaRegs, CanXL_GaaTxBufferMgrTable, Can_GpPCController.
**
** Function(s) invoked   : None
**
** Registers Used        : ulTXFQCTRL2, ulTXFQCTRL0, ulTXPQCTRL2, ulTXPQCTRL0.
**
** Reference ID          : CAN_DUD_ACT_165
** Reference ID          : CAN_DUD_ACT_165_CRT001, CAN_DUD_ACT_165_CRT002, CAN_DUD_ACT_165_REG001,
** Reference ID          : CAN_DUD_ACT_165_REG002, CAN_DUD_ACT_165_REG003, CAN_DUD_ACT_165_REG004,
** Reference ID          : CAN_DUD_ACT_165_GBL001, CAN_DUD_ACT_165_GBL002. 
***********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, CAN_PRIVATE_CODE) CanXL_HwTransmit(
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulBufIdx,
  CONST(uint32, AUTOMATIC) LulLenByte, CONST(boolean, AUTOMATIC) LblConfirmation,
  CONSTP2CONST(uint8, AUTOMATIC, CAN_APPL_DATA) LpPhysAddrPtr, uint32 LulVICD)
{
  
  uint32 LulAcceptanceFiled;
  uint16 LusSize;
  uint32 LusPriority;
  uint8 LucControllerId;
  uint8 LucTxQueue;
  uint8 LucCtrlInfoIndex;
  uint32 LulMaxNum;
  uint32 LulCount;
  uint16 LusCRC;

  Std_ReturnType LucReturnValue;
  P2VAR(Can_TxDescriptorsType, AUTOMATIC, CAN_APPL_DATA) LpDataDesc;                                                    /* PRQA S 3432 # JV-01 */
  P2VAR(CanXL_BufHandlerType, AUTOMATIC, CAN_APPL_DATA) LpBufHandlerPtr;                                                /* PRQA S 3432 # JV-01 */

  LucReturnValue = E_OK;
  LucControllerId = Can_GpPCController[LulCtrlIdx].ucCh;
  LucCtrlInfoIndex = Can_GpConfig->pCanXLSecondPhysicalControllerToIndex[LucControllerId]; 
  CAN_ENTER_CRITICAL_SECTION(CAN_RAM_DATA_PROTECTION);

  /* Get Tx buffer handler */
  CanXL_GaaTxBufferMgrTable[LucCtrlInfoIndex][LulBufIdx].blTxOngoing = CAN_TRUE;
  LpBufHandlerPtr = CanXL_GaaTxBufferMgrTable[LucCtrlInfoIndex][LulBufIdx].pBufferHdr;

  CAN_EXIT_CRITICAL_SECTION(CAN_RAM_DATA_PROTECTION);

  /* Set Tx request length */
  LpBufHandlerPtr->ulTxLength = CANXL_HEADER_SIZE + LulLenByte;                                                         /* PRQA S 3383 # JV-01 */

  /* Set Tx confirmation flag */
  LpBufHandlerPtr->blTxConfirm = LblConfirmation;
  
  /* Get Tx Buffer size equal to the lenght of data / 4  */
  LusSize = (uint16)((LpBufHandlerPtr->ulTxLength - 1U) / 4U) + 1U;                                                     /* PRQA S 3383 # JV-01 */

  LusPriority = LpBufHandlerPtr->ulPriority;
  
  if (CANXL_QUEUETYPE_TXFIFO == LpBufHandlerPtr->ucQueueType)
  {
    LulCount = 0;
    LucTxQueue = LpBufHandlerPtr->ucQueue;
    /* Get current descriptor used in FIFO Queue */
    LpDataDesc = (Can_TxDescriptorsType *)(CanXL_GaaRegs[LucCtrlInfoIndex].pMH->aaTXFQReg[LucTxQueue].ulTXADDPT);       /* PRQA S 0306 # JV-01 */
    /* Get the size of Tx FIFO Queue */
    LulMaxNum = CanXL_GaaRegs[LucCtrlInfoIndex].pMH->aaTXFQReg[LucTxQueue].ulTXSIZE;
    /* Check if current descriptor is not used yet NULL */
    while ((0UL != ((uint32)(LpDataDesc->ulElement0) & (CANXL_BIT_VALID(1U)))) && (LulMaxNum >= LulCount))              /* PRQA S 3469 # JV-01 */
    {
      if(LpDataDesc == CanXL_GaaCtrlStat[LucCtrlInfoIndex].stHwStatFixed.aaLastTxDesc[LucTxQueue])
      {
        /* Assign new target descriptor with START pointer in Queue */
        LpDataDesc = (Can_TxDescriptorsType *)(CanXL_GaaRegs[LucCtrlInfoIndex].pMH->aaTXFQReg[LucTxQueue].ulTXSTADD);   /* PRQA S 0306 # JV-01 */
      }
      else
      {
        /* Increment to new free descriptor */
        LpDataDesc++;
      }
      LulCount++;
    }
    if(LulCount > LulMaxNum)
    {
      /* Set Descriptor is NULL and return to E_NOT_OK*/
      LpDataDesc = NULL_PTR;
    } /* else Do nothing */
  }
  else
  {
    LucTxQueue = LpBufHandlerPtr->ucQueue - CANXL_MAX_TXFIFOQUEUE;                                                      /* PRQA S 3383 # JV-01 */
    /* Get descriptor of Tx Priority Queue */
    LpDataDesc = (Can_TxDescriptorsType *)(CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulTXPQSTADD);                           /* PRQA S 0306 # JV-01 */
    LpDataDesc = LpDataDesc + (uint32)LucTxQueue;                                                                       /* PRQA S 0488 # JV-01 */
    if (0UL != ((uint32)(LpDataDesc->ulElement0) & (CANXL_BIT_VALID(1U))))                                              /* PRQA S 3469 # JV-01 */
    {
      /* Set Descriptor is NULL and return to E_NOT_OK*/
      LpDataDesc = NULL_PTR;
    } /* else Do nothing */
  }
  
  if(NULL_PTR != LpDataDesc)
  {
    /* Set descriptor is VALID */
    LpDataDesc->ulElement0 |= CANXL_BIT_VALID(0x01);                                                                    /* PRQA S 3469 # JV-01 */
    /* Set size and instance information for descriptor */
    LpDataDesc->ulElement1 |= CANXL_BIT_SIZE(LusSize) | CANXL_BIT_PLSRC(1UL);                                           /* PRQA S 3469 # JV-01 */
    /* Update for element 2 */
    LpDataDesc->ulElement2TS0 = 0UL;
    /* Update for element 3 */
    LpDataDesc->ulElement3TS1 = 0UL;
    /* Set SDT=5H and VCID information for descriptor */
    LpDataDesc->ulElement4T0 = CANXL_T0_FIXED | CANXL_BIT_SDT(5U) | CANXL_BIT_VCID(LulVICD)                             /* PRQA S 3469 # JV-01 */
                                | CANXL_BIT_PRID(LusPriority);                                                          /* PRQA S 3469 # JV-01 */
    /* Set data length  */
    LpDataDesc->ulElement5T1 = (uint32)(CANXL_T1_FIXED | CANXL_BIT_DLCXL(LpBufHandlerPtr->ulTxLength - 1U));            /* PRQA S 2986, 3383 # JV-01, JV-01 */
  
    /* Set Acceptance Filed */
    CANXL_PACK_ADDRESS_FROM_4((CONST(uint8, AUTOMATIC) *)LpPhysAddrPtr, LulAcceptanceFiled);                            /* PRQA S 3473, 3432 # JV-01, JV-01 */
    LpDataDesc->ulElement6T2TD0 = LulAcceptanceFiled;
    /* Asign Bufer Address to Pointer data filed */
    LpDataDesc->ulElement7TX_APTD1 = LpBufHandlerPtr->ulbufAddr;
  
    /* Calculate CRC code */
    LusCRC = CanXL_ComputeCRC((uint32 *)LpDataDesc, CANXL_TX_DESC);                                                     /* PRQA S 0310 # JV-01 */
    LpDataDesc->ulElement0 |= CANXL_BIT_CRC(LusCRC);                                                                    /* PRQA S 3469 # JV-01 */
  
    /* Transmit start request */
    if (CANXL_QUEUETYPE_TXFIFO == LpBufHandlerPtr->ucQueueType)
    {
      /* TX FIFO Queue n is enabled*/
      CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulTXFQCTRL2 |= 1UL << (LucTxQueue);
      /* Tx FIFO Queue n is started */
      CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulTXFQCTRL0 |= 1UL << (LucTxQueue);
    }
    else
    {
      /* Tx Priority start transmit*/
      CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulTXPQCTRL2 |= 1UL << (LucTxQueue);
      CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulTXPQCTRL0 |= 1UL << (LucTxQueue);
    }

    CAN_ENTER_CRITICAL_SECTION(CAN_RAM_DATA_PROTECTION);

    /* Increase the number of buffer of current Tx queue */
    CanXL_GaaCtrlStat[LucCtrlInfoIndex].stHwStatSDT5.aaBufTxCnt[LpBufHandlerPtr->ucQueue]++;                            /* PRQA S 3387, 3383 # JV-01, JV-01 */

    CAN_EXIT_CRITICAL_SECTION(CAN_RAM_DATA_PROTECTION);
  }
  else
  {
    LucReturnValue = E_NOT_OK;
  }
  return LucReturnValue;
}

/***********************************************************************************************************************
** Function Name         : CanXL_Util_RamFree
**
** Service ID            : NA
**
** Description           : This free RAM at given address
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LpHeap - Heap handler
**                       : LulMemAddr - Memory Address need to be freed
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variable(s)    : CanXL_GpRamManager
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : CAN_DUD_ACT_166
** Reference ID          : CAN_DUD_ACT_166_GBL001, CAN_DUD_ACT_166_GBL002
***********************************************************************************************************************/
STATIC FUNC(void, CAN_PRIVATE_CODE) CanXL_Util_RamFree(
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONSTP2VAR(void, AUTOMATIC, CAN_APPL_DATA) LpMemAddr)
{
  CONSTP2VAR(CanXL_MemManagerType *, AUTOMATIC, CAN_APPL_DATA) LpMemMgr = &CanXL_GpRamManager[LulCtrlIdx];              /* PRQA S 3678, 3432 # JV-01, JV-01 */
  P2VAR(CanXL_MemManagerType, AUTOMATIC, CAN_APPL_DATA) LpFreeNode;                                                     /* PRQA S 3432 # JV-01 */
  if ((NULL_PTR != LpMemMgr) && (NULL_PTR != LpMemAddr))
  {
    /* Get the address of memory node */
    LpFreeNode =
      (P2VAR(CanXL_MemManagerType, AUTOMATIC, CAN_APPL_DATA))((uint8 *)LpMemAddr - sizeof(CanXL_MemManagerType));       /* PRQA S 3305, 0310, 3432, 0316, 0488 # JV-01, JV-01, JV-01, JV-01, JV-01 */

    /* If the next node is empty and the next node does not to LpFreeNode */
    if ((CAN_FALSE == LpFreeNode->pNext->blHeapLock) && (LpFreeNode != LpFreeNode->pNext))
    {
      if (LpFreeNode < LpFreeNode->pNext)
      {
        /* Marge next heap block into the LpFreeNode */
        if (LpFreeNode->pNext == *LpMemMgr)
        {
          /* Change heap search start position to the LpFreeNode */
          CanXL_GpRamManager[LulCtrlIdx] = LpFreeNode;
        } /* else no action required*/

        /* Re-chain circular list */
        LpFreeNode->ulHeapSize += LpFreeNode->pNext->ulHeapSize;                                                        /* PRQA S 3383 # JV-01 */
        LpFreeNode->pNext->pNext->pPrev = LpFreeNode;
        LpFreeNode->pNext = LpFreeNode->pNext->pNext;
      } /* else no action required*/
    } /* else no action required*/

    /* If the prev node is empty and the prev node does not to LpFreeNode */
    if ((CAN_FALSE == LpFreeNode->pPrev->blHeapLock) && (LpFreeNode != LpFreeNode->pPrev))
    {
      if (LpFreeNode > LpFreeNode->pPrev)
      {
        /* Marge LpFreeNode into the prev node */
        if (LpFreeNode == *LpMemMgr)
        {
          /* Change heap search start position to the prev node */
          CanXL_GpRamManager[LulCtrlIdx] = LpFreeNode->pPrev;
        } /* else no action required*/

        /* Re-chain circular list */
        LpFreeNode->pPrev->ulHeapSize += LpFreeNode->ulHeapSize;                                                        /* PRQA S 3383 # JV-01 */
        LpFreeNode->pNext->pPrev = LpFreeNode->pPrev;
        LpFreeNode->pPrev->pNext = LpFreeNode->pNext;
      } /* else no action required*/
    } /* else no action required*/
    LpFreeNode->blHeapLock = CAN_FALSE;
  } /* else no action required*/
}

/***********************************************************************************************************************
** Function Name         : CanXL_ReleaseTxBuffer
**
** Service ID            : N/A
**
** Description           : Release a Tx buffer and store it to the tail of the
**                         Tx buffer ring
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LulCtrlIdx     : controller index
**                         LulBufIdx      : index to the buffer
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variables Used : CanXL_GaaTxBufferMgrTable, CanXL_GaaTxAllocCnt
**
** Function(s) invoked   : CanXL_Util_RamFree
**
** Registers Used        : None
**
** Reference ID          : CAN_DUD_ACT_167, 
** Reference ID          : CAN_DUD_ACT_167_GBL001, CAN_DUD_ACT_167_GBL002
***********************************************************************************************************************/
FUNC(void, CAN_PRIVATE_CODE) CanXL_ReleaseTxBuffer(
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulBufIdx)
{
  CONST(uint8, AUTOMATIC) LucQueue = CanXL_GaaTxBufferMgrTable[LulCtrlIdx][LulBufIdx].pBufferHdr->ucQueue;

  /* Release tx buffer handler */
  CanXL_Util_RamFree(LulCtrlIdx, (void *)CanXL_GaaTxBufferMgrTable[LulCtrlIdx][LulBufIdx].pBufferHdr);

  CanXL_GaaTxBufferMgrTable[LulCtrlIdx][LulBufIdx].pBufferHdr = NULL_PTR;
  
  CanXL_GaaTxAllocCnt[LulCtrlIdx][LucQueue]--;                                                                          /* PRQA S 3383 # JV-01 */
}


/*******************************************************************************
** Function Name         : CanXL_FindTxBuffer
**
** Service ID            : N/A
**
** Description           : Finding Tx buffer.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LulCtrlIdx     : controller index
**                         LulQIdx        : Queue index
**
** InOut Parameters      : None
**
** Output Parameters     : index to the buffer
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variables Used : CanXL_GaaTxBufferMgrTable
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : CAN_DUD_ACT_168
***********************************************************************************************************************/
STATIC FUNC(uint32, CAN_PRIVATE_CODE) CanXL_FindTxBuffer(
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulQIdx)
{
  uint32 LulBufIdx = 0UL;
  uint32 LulCounter;
  P2CONST(CanXL_BufHandlerType, AUTOMATIC, CAN_APPL_DATA) LpBufHandlerPtr;
  boolean LblOngoing;
  
  for(LulCounter = 0UL; LulCounter < CanXL_GaaTxBufferTotal[LulCtrlIdx]; LulCounter++)
  {
    LpBufHandlerPtr = CanXL_GaaTxBufferMgrTable[LulCtrlIdx][LulCounter].pBufferHdr;
    LblOngoing = CanXL_GaaTxBufferMgrTable[LulCtrlIdx][LulCounter].blTxOngoing;
    /* Check Buffer handler is not NULL */
    if ((NULL_PTR != LpBufHandlerPtr) && (LblOngoing == CAN_TRUE))
    {
      /* Check Buffer if macthed Queue index */
      if (LulQIdx == LpBufHandlerPtr->ucQueue)
      {
          /* Found it */
          LulBufIdx = LulCounter;
          break;
      } /* else no action required*/
    } /* else no action required*/
  }

  return (LulBufIdx);
}

/***********************************************************************************************************************
** Function Name         : CanXL_TxConfirmationQueueProcess
**
** Service ID            : N/A
**
** Description           : Performs transmission processing, notifies the upper layer
**                         of transmission completion and releases the Tx buffer.
**                         This function scans the specified queue.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : LulCtrlIdx     : Index of a controller
**                         LulQIdx        : Index of a Tx Queue
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variable(s)    : CanXL_GaaCtrlStat, CanXL_GaaTxBufferMgrTable, CanXL_GaaRegs, Can_GpConfig
**
** Function(s) invoked   : EthIf_TxConfirmation, CanXL_ReleaseTxBuffer
**
** Registers Used        : None
**
** Reference ID          : CAN_DUD_ACT_169
** Reference ID          : CAN_DUD_ACT_169_REG001, CAN_DUD_ACT_169_REG002, CAN_DUD_ACT_169_CRT001, 
** Reference ID          : CAN_DUD_ACT_169_CRT002, CAN_DUD_ACT_169_GBL001, CAN_DUD_ACT_169_GBL002,
** Reference ID          : CAN_DUD_ACT_169_GBL003, CAN_DUD_ACT_169_GBL004
***********************************************************************************************************************/
STATIC FUNC(void, CAN_PRIVATE_CODE) CanXL_TxConfirmationQueueProcess(                                                   /* PRQA S 3006 # JV-01 */
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulQIdx, Can_BufferType LucTxQueueType)
{
  uint8 LucCtrlId;
  uint32 LulBufIdx;
  uint8 LucQueueSlots;
  boolean LblTransmit;
  Std_ReturnType LblSuccess;
  P2VAR(Can_TxDescriptorsType, AUTOMATIC, CAN_APPL_DATA) LpDataDesc;                                                    /* PRQA S 3432 # JV-01 */ 
  P2VAR(Can_TxDescriptorsType, AUTOMATIC, CAN_APPL_DATA) LpCurrentDesc;                                                 /* PRQA S 3432 # JV-01 */
  P2VAR(CanXL_BufHandlerType, AUTOMATIC, CAN_APPL_DATA) LpBufHandlerPtr;                                                /* PRQA S 3432, 3678 # JV-01, JV-01 */
  LblTransmit = CAN_FALSE;
  LblSuccess = E_NOT_OK;
  if(CANXL_QUEUETYPE_TXFIFO == LucTxQueueType)
  {
    /* FIFO Queue Confirmation */
    LpCurrentDesc = (Can_TxDescriptorsType *)(CanXL_GaaRegs[LulCtrlIdx].pMH->aaTXFQReg[LulQIdx].ulTXADDPT);             /* PRQA S 0306 # JV-01 */
    /* Check if TX FIFO queue is on hold while storing VALID descriptor */
    if((0UL != (CanXL_GaaRegs[LulCtrlIdx].pMH->ulTXFQSTS0 & (uint32)(1UL << (LulQIdx + 16UL)))) &&                      /* PRQA S 3383 # JV-01 */
      (0UL != (CanXL_GaaRegs[LulCtrlIdx].pMH->ulTXFQSTS1 & (uint32)(1UL << LulQIdx))))
    {
      if (0UL != ((uint32)(LpCurrentDesc->ulElement0) & (CANXL_BIT_VALID(1U))))                                         /* PRQA S 3469 # JV-01 */
      {
        RH850_SET_IOREG_SYNCP(32, &CanXL_GaaRegs[LulCtrlIdx].pMH->ulTXFQCTRL0, (1UL << LulQIdx));                       /* PRQA S 3464, 1006 # JV-01, JV-01 */
      }
    }
    /* Check if TX FIFO queue sent any frame yet */
    LpDataDesc = CanXL_GaaCtrlStat[LulCtrlIdx].stHwStatSDT5.aaHeadTxDesc[LulQIdx];
    if(0U != (CanXL_GaaRegs[LulCtrlIdx].pMH->ulTXFQINSTS & (uint32)(1UL << LulQIdx)))
    {
      LblTransmit = CAN_TRUE;
    } /*else do nothing*/
  }
  else
  {
    /* Compute Queue slots */
    LucQueueSlots = (uint8)LulQIdx - CANXL_MAX_TXFIFOQUEUE;                                                             /* PRQA S 3384 # JV-01 */
    if(0U != (CanXL_GaaRegs[LulCtrlIdx].pMH->ulTXPQINSTS0 & (uint32)(1UL << LucQueueSlots)))
    {
      /* Priority Queue Confirmation */
      LpCurrentDesc = (Can_TxDescriptorsType *)(CanXL_GaaRegs[LulCtrlIdx].pMH->ulTXPQSTADD) + LucQueueSlots;            /* PRQA S 0306, 0488 # JV-01, JV-01 */
      LpDataDesc = LpCurrentDesc;
      LblTransmit = CAN_TRUE;
    } /*else do nothing*/
  }
  
  /* Check if Current point is NULL */
  if((CAN_TRUE == LblTransmit))
  {
    /* Loop all descriptors */
    do
    {
      /* Loop all buffers were assigned for descriptor */
      if (((CANXL_BIT_SDT(5U) | CANXL_BIT_XLF) == (LpDataDesc->ulElement4T0 & 0x400000FFUL)) &&                         /* PRQA S 3469 # JV-01 */
         (0UL != ((LpDataDesc->ulElement0) & 0x0000000FUL)))
        {
        /* Find Buffer index for Queue index */
        LulBufIdx = CanXL_FindTxBuffer(LulCtrlIdx, LulQIdx);
        /* Get Tx Buffer handler */
        LpBufHandlerPtr = CanXL_GaaTxBufferMgrTable[LulCtrlIdx][LulBufIdx].pBufferHdr;
        /* Get Tx timestamp */
        #if (CAN_CANXL_GLOBAL_TIME_SUPPORT == STD_ON)
        LpBufHandlerPtr->stTimeStamp.nanoseconds = LpDataDesc->ulElement2TS0;
        LpBufHandlerPtr->stTimeStamp.seconds     = LpDataDesc->ulElement3TS1;
        LpBufHandlerPtr->stTimeStamp.secondsHi   = (uint16)0U;
        
        /* Set timestamp quality information as ETH_VALID */
        LpBufHandlerPtr->enTimeQual = ETH_VALID;
        #endif
        if(1UL == ((LpDataDesc->ulElement0) & 0x0000000FUL))
        {
          LblSuccess = E_OK;
        }
        else
        {
          LblSuccess = E_NOT_OK;
        }
        /* Check whether the transmission confirmation was enabled */
        if (CAN_TRUE == LpBufHandlerPtr->blTxConfirm)
        {
          LucCtrlId = Can_GpConfig->pCanXLPhysicalControllerToIndex[LulCtrlIdx];
          /* Call the callback function */
          /* Since the maximum value of controller index is 2, casting to uint8 does no problem. */
          EthIf_TxConfirmation((uint8)(LucCtrlId + CAN_CONTROLLER_OFFSET),                                              /* PRQA S 3383, 2985 # JV-01, JV-01 */
                                (Eth_BufIdxType)LpBufHandlerPtr->ulbufIdx, LblSuccess);
        } /* No action required */
        CAN_ENTER_CRITICAL_SECTION(CAN_RAM_DATA_PROTECTION);

        /* Release the tx buffer resource */
        CanXL_ReleaseTxBuffer(LulCtrlIdx, LulBufIdx);

        if(CAN_FALSE == CanXL_GaaCtrlStat[LulCtrlIdx].blErrorSignaling)
        {
          CanXL_TECEmulator((uint8)LulCtrlIdx, LpDataDesc);
        } /* else no action required*/

        if(0U != CanXL_GaaCtrlStat[LulCtrlIdx].stHwStatSDT5.aaBufTxCnt[LulQIdx])
        {
        /* Decrease the number of on-transmission buffer of current Tx queue */
          CanXL_GaaCtrlStat[LulCtrlIdx].stHwStatSDT5.aaBufTxCnt[LulQIdx]--;                                             /* PRQA S 3387, 3384 # JV-01, JV-01 */
        } /* else no action required*/
        CAN_EXIT_CRITICAL_SECTION(CAN_RAM_DATA_PROTECTION);
        
        /* re-initialize descriptor */
        LpDataDesc->ulElement0 &= CAN_DMA1_RESET_VALUE;
        LpDataDesc->ulElement1 &= CAN_DMA2_RESET_VALUE;
        LpDataDesc->ulElement4T0 = CAN_MH_INITIAL_VALUE;

        if(CANXL_QUEUETYPE_TXFIFO != LucTxQueueType)
        {
          /* Clear interrupt */
          CanXL_GaaRegs[LulCtrlIdx].pMH->ulTXPQINSTS0 &= (uint32)(1UL << LucQueueSlots);
        } /* else no action required*/
      } /* else no action required*/
      
      if(CANXL_QUEUETYPE_TXFIFO == LucTxQueueType)
      {
        if(LpDataDesc != CanXL_GaaCtrlStat[LulCtrlIdx].stHwStatFixed.aaLastTxDesc[LulQIdx])
        {
          LpDataDesc += 1UL;                                                                                            /* PRQA S 0489 # JV-01 */
        }
        else
        {
          LpDataDesc = CanXL_GaaCtrlStat[LulCtrlIdx].stHwStatFixed.aaFirstTxDesc[LulQIdx];
        }
      }
      else
      {
        break;
      }
    }
    while ((LpDataDesc != LpCurrentDesc) && 
              (0U != CanXL_GaaCtrlStat[LulCtrlIdx].stHwStatSDT5.aaBufTxCnt[LulQIdx]));
    if(CANXL_QUEUETYPE_TXFIFO == LucTxQueueType)
    {
      CanXL_GaaCtrlStat[LulCtrlIdx].stHwStatSDT5.aaHeadTxDesc[LulQIdx] = LpCurrentDesc;
      /* Clear interrupt */
      CanXL_GaaRegs[LulCtrlIdx].pMH->ulTXFQINSTS &= (uint32)(1UL << LulQIdx);
    } /* else no action required*/
  } /* else no action required*/
}

/***********************************************************************************************************************
** Function Name         : CanXL_HwTxConfirmation
**
** Service ID            : N/A
**
** Description           : Performs transmission processing, notifies the upper layer
**                         of transmission completion and releases the Tx buffer.
**                         This function scans all queues.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : LulCtrlIdx     : Index of a controller
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variable(s)    : CanXL_GaaCtrlStat, Can_GpConfig
**
** Function(s) invoked   : CanXL_TxConfirmationQueueProcess
**
** Registers Used        : None
**
** Reference ID          : CAN_DUD_ACT_170
***********************************************************************************************************************/
FUNC(void, CAN_PRIVATE_CODE) CanXL_HwTxConfirmation(CONST(uint32, AUTOMATIC) LulCtrlIdx)                                /* PRQA S 1505 # JV-01 */
{
  uint32 LulCounter;
  uint32 LulTxQueueId;
  Can_BufferType LucTxEthBuffer; 
  P2CONST(Can_CanXLHWUnitInfoType, AUTOMATIC, CAN_APPL_DATA) LpHwUnitConfig;

  LpHwUnitConfig = (P2CONST(Can_CanXLHWUnitInfoType, AUTOMATIC, CAN_CONFIG_DATA))Can_GpConfig->pCanXLHWUnitInfo;        /* PRQA S 0316 # JV-01 */
  LpHwUnitConfig = &LpHwUnitConfig[LulCtrlIdx];
  /* Eth Egress Fifo */
  for (LulCounter = 0UL; LulCounter < LpHwUnitConfig->pTxEthQueueConfig->ulNoOfEthEgressFifo; LulCounter++)
  {
    LulTxQueueId = LpHwUnitConfig->pTxEthQueueConfig->pTxEthEthEgressFifo[LulCounter].ucEthQueue;
    LucTxEthBuffer = LpHwUnitConfig->pTxEthQueueConfig->pTxEthEthEgressFifo[LulCounter].ucTxQueueType;
    if (CANXL_QUEUETYPE_TXPRIORITY == LucTxEthBuffer)
    {
      LulTxQueueId += CANXL_MAX_TXFIFOQUEUE;                                                                            /* PRQA S 3383 # JV-01 */
    } /* else no action required*/
    if (CanXL_GaaCtrlStat[LulCtrlIdx].stHwStatSDT5.aaBufTxCnt[LulTxQueueId] > 0UL)
    {
      CanXL_TxConfirmationQueueProcess(LulCtrlIdx, LulTxQueueId, LucTxEthBuffer);
    } /* else no action required*/
  }
  /* Default queue */
  LulTxQueueId = LpHwUnitConfig->pTxEthQueueConfig->ucEthDefaultQueue;
  /* Initialize Tx Queue Type */
  LucTxEthBuffer = LpHwUnitConfig->pTxEthQueueConfig->ucTxDefaultQueueType;
  if (CANXL_QUEUETYPE_TXPRIORITY == LucTxEthBuffer)
  {
    LulTxQueueId += CANXL_MAX_TXFIFOQUEUE;                                                                              /* PRQA S 3383 # JV-01 */
  } /* else no action required*/
  if (CanXL_GaaCtrlStat[LulCtrlIdx].stHwStatSDT5.aaBufTxCnt[LulTxQueueId] > 0UL)
  {
    CanXL_TxConfirmationQueueProcess(LulCtrlIdx, LulTxQueueId, LucTxEthBuffer);
  } /* else no action required*/
  }
/***********************************************************************************************************************
** Function Name         : CanXL_ConsistentCheck
**
** Service ID            : N/A
**
** Description           : The frame shall be checked for consistency with CiA 611-1 chapter 5 SDU types 
**                         specification by this function
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : LpTargetData     : Pointer to frame
**                         LucSdtType       : SDU type to be checked
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variable(s)    : None
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : CAN_DUD_ACT_181
***********************************************************************************************************************/
FUNC(Std_ReturnType, CAN_PRIVATE_CODE) CanXL_ConsistentCheck(CONST(uint8, AUTOMATIC) LucCtrlIndex, 
      P2CONST(volatile uint32, AUTOMATIC, CAN_APPL_DATA) LpTargetData, CONST(uint8, AUTOMATIC) LucSdtType)
{
  VAR(Std_ReturnType, AUTOMATIC) LenResult;
  VAR(uint32, AUTOMATIC) LulAF;
  VAR(uint32, AUTOMATIC) LulAFLLC;
  VAR(uint32, AUTOMATIC) LulDLC;
  VAR(uint16, AUTOMATIC) LusEtherType;
  VAR(uint16, AUTOMATIC) LusEtherTypeRx;
  VAR(uint8, AUTOMATIC) LucVCID;
  VAR(uint8, AUTOMATIC) LucVCIDLLC;
  VAR(uint32, AUTOMATIC) LulExtendID;
  VAR(uint8, AUTOMATIC) LucIDE;
  VAR(uint8, AUTOMATIC) LucCount;

  LenResult = E_OK;
  LulAF = *(LpTargetData + 2);                                                                                          /* PRQA S 0488 # JV-01 */
  if(5U == LucSdtType)
  { 
    LusEtherType = (uint16)(*(LpTargetData + 6U));                                                                      /* PRQA S 0488 # JV-01 */
    LusEtherTypeRx = (uint16)(LusEtherType << 8U) | (uint16)((LusEtherType & 0xFFFFU) >> 8U);                           /* PRQA S 2985 # JV-01 */
    LucVCID = (uint8)(((*LpTargetData) & CANXL_RX_VCID_MASK ) >> 8U);
    LucVCIDLLC = (uint8)((*(LpTargetData + 6U) >> 24U) & 0xFFU);                                                        /* PRQA S 0488 # JV-01 */
    if(((LusEtherTypeRx == CANXL_CVLAN_TAG) || (LusEtherTypeRx == CANXL_SVLAN_TAG)))
    {
      if((LucVCID == 0U) || (LucVCID != LucVCIDLLC))
      {
      LenResult = E_NOT_OK;
      } /* else no action required */
    }
    
    CANXL_PACK_ADDRESS_FROM_4((CONST(uint8, AUTOMATIC) *)(LpTargetData + 3U), LulAFLLC);                                /* PRQA S 0751, 3473, 3432, 0312, 0488 # JV-01, JV-01, JV-01, JV-01, JV-01 */
    if(LulAF != LulAFLLC)
    {
      LenResult = E_NOT_OK;
    } /* else no action required*/
  }
  else if(3U == LucSdtType)                                                                                             /* PRQA S 2004 # JV-01 */
  {
    LulExtendID = (LulAF >> 11) & 0x3FFFFU;
    LucIDE = (uint8)(LulAF >> 29U) & 0x01U;
    if((0U != LulExtendID) && (0U == LucIDE))
    {
      LenResult = E_NOT_OK;
    }
    else
    {
      LulDLC = (CANXL_RX_BIT_DLCXL(*(LpTargetData + 1UL)) & 0x7FFUL);                                                   /* PRQA S 3469, 0489 # JV-01, JV-01 */
      if((8UL < LulDLC) && ((LulAF >> 31UL) == 0U))
      {
        LenResult = E_NOT_OK;
      }
      else
      {
        for(LucCount = 0U; LucCount < 16U; LucCount++)
        {
          if(LulDLC == Can_GaaPayloadFromDLCTable[LucCount])
          {
            break;
          } /* else no action required*/
        }
        if(LucCount == 16U)
        {
          LenResult = E_NOT_OK;
        } /* else no action required*/
      }
    }
  } /* else no action required*/
  if(CAN_FALSE == CanXL_GaaCtrlStat[LucCtrlIndex].blErrorSignaling)
  {
    if((E_OK == LenResult) && (CanXL_GaaCtrlStat[LucCtrlIndex].ulREC != 0U))
    {
      CanXL_GaaCtrlStat[LucCtrlIndex].ulREC -= 1U;                                                                      /* PRQA S 3384 # JV-01 */
    }
    else if ((E_NOT_OK == LenResult) && (CanXL_GaaCtrlStat[LucCtrlIndex].ulREC < 128U))                                 /* PRQA S 2004 # JV-01 */
    {
      CanXL_GaaCtrlStat[LucCtrlIndex].ulREC += 1U;                                                                      /* PRQA S 3384 # JV-01 */
    }
  } /* else no action required*/
  return LenResult;
}
/***********************************************************************************************************************
** Function Name         : CanXL_TECEmulator
**
** Service ID            : N/A
**
** Description           : The frame shall be checked for consistency with CiA 611-1 chapter 5 SDU types 
**                         specification by this function
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : LucCtrlIndex     : Pointer to frame
**                         Descriptor       : SDU type to be checked
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variable(s)    : CanXL_GaaCtrlStat
**
** Function(s) invoked   : None
**
** Registers Used        : PRT
**
** Reference ID          : CAN_DUD_ACT_200
** Reference ID          : CAN_DUD_ACT_200_GBL001, CAN_DUD_ACT_200_REG001
***********************************************************************************************************************/
FUNC(void, CAN_PRIVATE_CODE) CanXL_TECEmulator(CONST(uint8, AUTOMATIC) LulCtrlIdx, 
                                                  P2VAR(Can_TxDescriptorsType, AUTOMATIC, CAN_CONFIG_DATA) Descriptor)  /* PRQA S 3432, 3673 # JV-01, JV-01 */
{ 
  if((CanXL_GaaCtrlStat[LulCtrlIdx].ulTEC != 0U) && (1U == ((Descriptor->ulElement0) & 0x0FU)))
  {
    CanXL_GaaCtrlStat[LulCtrlIdx].ulTEC -= 1U;                                                                          /* PRQA S 3384 # JV-01 */
  }
  else if ((CanXL_GaaCtrlStat[LulCtrlIdx].ulTEC < 255U) && (2U == ((Descriptor->ulElement0) & 0x0FUL)) &&               /* PRQA S 2004 # JV-01 */
  (0UL != (CanXL_GaaRegs[LulCtrlIdx].pPRT->ulEVNT & CANXL_PRT_EVENT_ACK)))
  {
    CanXL_GaaCtrlStat[LulCtrlIdx].ulTEC += 8U;                                                                          /* PRQA S 3384 # JV-01 */
    if(255U < CanXL_GaaCtrlStat[LulCtrlIdx].ulTEC)
    {
      CanXL_GaaCtrlStat[LulCtrlIdx].ulTEC = 255U;
    }
  } /* else no action required*/
}
/***********************************************************************************************************************
** Function Name         : CanXL_WriteRxData
**
** Service ID            : N/A
**
** Description           : The frame shall be checked for consistency with CiA 611-1 chapter 5 SDU types 
**                         specification by this function
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : LucCtrlIndex     : Pointer to frame
**                         Descriptor       : SDU type to be checked
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variable(s)    : Can_GpConfig, CanXL_GaaCtrlStat
**
** Function(s) invoked   : None
**
** Registers Used        : RXDCSTADD, RXRDADDPT
**
** Reference ID          : CAN_DUD_ACT_201
** Reference ID          : CAN_DUD_ACT_201_GBL001, CAN_DUD_ACT_201_GBL002, CAN_DUD_ACT_201_REG001
***********************************************************************************************************************/
FUNC(void, CAN_PRIVATE_CODE) CanXL_WriteRxData(CONST(uint8, AUTOMATIC) LucCtrlInfoIndex, 
  VAR(uint32, AUTOMATIC) LulQueueIndex, P2VAR(Can_RxDescriptorsType, AUTOMATIC, CAN_CONFIG_DATA) Descriptor,            /* PRQA S 3432, 3673 # JV-01, JV-01 */
  P2VAR(uint32, AUTOMATIC, CAN_VAR_NO_INIT) LpCanSdu)                                                                   /* PRQA S 3432 # JV-01 */
{ 
  VAR(uint32, AUTOMATIC) LucWrapFlag;
  VAR(uint32, AUTOMATIC) LulCheck;
  VAR(uint32, AUTOMATIC) LulWordIndex;
  VAR(uint32, AUTOMATIC) LulPlWordIndex;
  VAR(uint32, AUTOMATIC) LulHeaderSize;
  VAR(uint32, AUTOMATIC) LucDCRemain;
  VAR(uint32, AUTOMATIC) LulCount;
  VAR(uint32, AUTOMATIC) LusPayload;
  VAR(uint32, AUTOMATIC) LusMaxNum;
  VAR(uint32, AUTOMATIC) LulActualSize;
  VAR(uint32, AUTOMATIC) LulR0;
  VAR(uint32, AUTOMATIC) LulR1;
  P2VAR(uint32, AUTOMATIC, CAN_CONFIG_DATA) LpDCAddress;                                                                /* PRQA S 3432, 3678 # JV-01, JV-01 */
  P2VAR(Can_RxDescriptorsType, AUTOMATIC, CAN_CONFIG_DATA) LpStartDec;                                                  /* PRQA S 3432, 3678 # JV-01, JV-01 */
  P2VAR(uint32, AUTOMATIC, CAN_CONFIG_DATA) LpPayload;                                                                  /* PRQA S 3432, 3678 # JV-01, JV-01 */
  P2CONST(Can_CanXLHWUnitInfoType, AUTOMATIC, CAN_CONFIG_DATA) LpCanXLHWInfo;

  LpCanXLHWInfo = (P2CONST(Can_CanXLHWUnitInfoType, AUTOMATIC, CAN_CONFIG_DATA))Can_GpConfig->pCanXLHWUnitInfo;         /* PRQA S 0316 # JV-01 */ 

  /* Get the data container address and fetch Rx element of this message */
  LpStartDec = (Can_RxDescriptorsType *)CanXL_GaaCtrlStat[LucCtrlInfoIndex].stHwStatFixed.aaFirstRxDesc[LulQueueIndex];
  LusMaxNum = LpCanXLHWInfo[LucCtrlInfoIndex].pRxFIFOQueueConfig[LulQueueIndex].usMaxNumDesc;
  LusPayload = LpCanXLHWInfo[LucCtrlInfoIndex].pRxFIFOQueueConfig[LulQueueIndex].usPayloadSize;
  /* Calculate the remaining data container size in this RX FIFO queue */
  LpDCAddress = (uint32 *)(Descriptor->ulElement1);                                                                     /* PRQA S 0306 # JV-01 */
  LulR0 = *(LpDCAddress);
  LulR1 = *(LpDCAddress + 1UL);                                                                                         /* PRQA S 0489 # JV-01 */
  LulCount = 0UL;
  LucWrapFlag = 0U;
  LulWordIndex = 0U;
  LulPlWordIndex = 0U;
  if((LulR0 & CANXL_BIT_XLF) == 0UL)
  {
    LulActualSize = Can_GaaPayloadFromDLCTable[CANXL_RX_BIT_DLCXL(LulR1) & 0x0FUL];                                     /* PRQA S 3469 # JV-01 */
    LulHeaderSize = 2;
  }
  else
  {
    LulActualSize = (CANXL_RX_BIT_DLCXL(LulR1) & 0x7FFUL) + 1UL;                                                        /* PRQA S 3469, 3383 # JV-01, JV-01 */
    LulHeaderSize = 3;
  }
  LpPayload = LpDCAddress + LulHeaderSize;                                                                              /* PRQA S 0488 # JV-01 */
  LucDCRemain = (((LusMaxNum - (uint32)(Descriptor - LpStartDec)) * LusPayload) * 32UL) - (LulHeaderSize * 4UL);        /* PRQA S 3383, 3384, 0488 # JV-01, JV-01, JV-01 */
  /* Loop for all data word of payload */
  while(LulCount < (CAN_ALIGN_4(LulActualSize) / (uint32)sizeof(uint32)))                                               /* PRQA S 3469, 3383 # JV-01, JV-01 */
  {
    /* If the payload of this message is large than the remainning data container and the wrap-back not occured yet */
    if((LulActualSize > LucDCRemain) && (LucWrapFlag != 1U))
    {
    /* Set an amount of word data that equal to the the remainning data container, the missing part will be written
      when wrap-back */
      LulCheck = LucDCRemain / (uint32)sizeof(uint32);
      /* Set the wrap-back flag */
      LucWrapFlag = 1U;
    }
    /* If the payload of this message is large than the remainning data container and the wrap-back has occured */
    else if(LucWrapFlag == 1U)
    {
      /* Re-calculate the remaining data word and its address to continue writing to the local variable */
      LulCheck += CAN_ALIGN_4(LulActualSize - LucDCRemain) / (uint32)sizeof(uint32);                                    /* PRQA S 3469, 3383, 3384 # JV-01, JV-01, JV-01 */
      LpPayload = (uint32 *)(LpStartDec->ulElement1);                                                                   /* PRQA S 0306 # JV-01 */
      LulPlWordIndex = 0;
    }
    else
    {
      /* Simply set the data word equal to DLC */
      LulCheck = CAN_ALIGN_4(LulActualSize) / (uint32)sizeof(uint32);                                                   /* PRQA S 3469, 3383 # JV-01, JV-01 */
    }
    while(LulWordIndex < LulCheck)
    {
      /* Copy data payload from the data container to the local array */
      LpCanSdu[LulWordIndex] = LpPayload[LulPlWordIndex];
      LulCount++;
      LulWordIndex++;
      LulPlWordIndex++;                                                                                                 /* PRQA S 3383 # JV-01 */
    }
    LulWordIndex = LulCheck;
  }
  /* Update the PduInfoPtr */
}
#define CAN_STOP_SEC_PRIVATE_CODE
#include "Can_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* (CAN_CANXL_SUPPORTED == STD_ON) */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
