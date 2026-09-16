/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas R22-11 X2x MCAL Components                                                          */
/* Module       = Fee_InternalFct.c                                                                                   */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2024-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains FEE internal function related API implementations                                               */
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
/*              Devices:        RH850/X2x                                                                             */
/*====================================================================================================================*/

/***********************************************************************************************************************
**                                              Revision Control History                                              **
***********************************************************************************************************************/
/*
 * 1.1.1:  30/06/2025:  Remove SW-VERSION in file header
 * 1.1.0:  30/06/2025:  Update SW-VERSION for U2Ax Ver22.01.00(D) Final Release
 * 1.0.3:  25/04/2025:  As part of ARDAACL-54617, Add condition check for Fee_JobWriteValidateBlock
 *                      Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03
 * 1.0.2:  31/03/2025:  Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02 Release
 *                      As part of <QAC 11.6.0> support, following changes are made
 *                      Removed message 2844, 2824, 2814, 1532, 3673
 * 1.0.1   28/02/2025:  Remove redundant else condition to check Block Status in Fee_JobSwapHeaderBlock
 * 1.0.0   31/12/2024:  Correct release version macro.
 *                      Update check MemAcc job resut condition in Fee_CheckMemIfJobResult.
 * 0.0.2:  31/10/2024:  Remove internal function Fee_MainFunctionPeriod.
 *                      Update Fee_PrepareHeaderAddrArea, Fee_PrepareHeaderBlockData remove redundant While condition.
 *                      Update Fee_PrepareHeaderFlag change FEE_ONE_UNIT_SIZE to FEE_FOUR_UNIT_SIZE.
 *                      Update Fee_CheckHeaderDataFlag remove redundant condition.
 *                      Add QAC Msg 5087, 0612, 0686, 1531.
 *                      Convert For Loop to While Loop.
 * 0.0.1:  30/08/2024:  Initial Version.
 */

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/

#include "Fee.h"

#include "Fee_InternalFct.h"

#include "Fee_Ram.h"

#include "Fee_Types.h"

#include "NvM_MemIf.h"

/* Det module */
#include "Det.h"

#include "MemAcc.h"

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define FEE_INTERNALFCT_C_AR_RELEASE_MAJOR_VERSION    FEE_AR_RELEASE_MAJOR_VERSION_VALUE
#define FEE_INTERNALFCT_C_AR_RELEASE_MINOR_VERSION    FEE_AR_RELEASE_MINOR_VERSION_VALUE
#define FEE_INTERNALFCT_C_AR_RELEASE_REVISION_VERSION FEE_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define FEE_INTERNALFCT_C_SW_MAJOR_VERSION            FEE_SW_MAJOR_VERSION_VALUE
#define FEE_INTERNALFCT_C_SW_MINOR_VERSION            FEE_SW_MINOR_VERSION_VALUE
/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (FEE_INTERNALFCT_AR_RELEASE_MAJOR_VERSION != FEE_INTERNALFCT_C_AR_RELEASE_MAJOR_VERSION)
#error "Fee_InternalFct.c : Mismatch in Release Major Version"
#endif

#if (FEE_INTERNALFCT_AR_RELEASE_MINOR_VERSION != FEE_INTERNALFCT_C_AR_RELEASE_MINOR_VERSION)
#error "Fee_InternalFct.c : Mismatch in Release Minor Version"
#endif

#if (FEE_INTERNALFCT_AR_RELEASE_REVISION_VERSION != FEE_INTERNALFCT_C_AR_RELEASE_REVISION_VERSION)
#error "Fee_InternalFct.c : Mismatch in Release Revision Version"
#endif

#if (FEE_INTERNALFCT_SW_MAJOR_VERSION != FEE_INTERNALFCT_C_SW_MAJOR_VERSION)
#error "Fee_InternalFct.c : Mismatch in Software Major Version"
#endif

#if (FEE_INTERNALFCT_SW_MINOR_VERSION != FEE_INTERNALFCT_C_SW_MINOR_VERSION)
#error "Fee_InternalFct.c : Mismatch in Software Minor Version"
#endif

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (4:5087)    : #include directives should only be preceded by preprocessor directives or comments           */
/* Rule                : MISRA C:2012 Rule 20.1                                                                       */
/* JV-01 Justification : This is done as per Memory Requirement, (MEMMAP003 - Specification of Memory Mapping).       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:1338)    : The parameter '%s' is being modified.                                                        */
/* Rule                : MISRA C:2012 Rule-17.8                                                                       */
/* JV-01 Justification : This in case, parameter is not const, it could be accepted for modification                  */
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
/* Message (2:3678)    : The object referenced by '%1s' is not modified through it, so '%1s' could be declared with   */
/*                       type '%2s'.                                                                                  */
/* Rule                : MISRA C:2012 Rule-8.13                                                                       */
/* JV-01 Justification : This is accepted. It is just advice for improve safety by reducing the possibility that the  */
/*                       referenced data is unintentionally modified through an unexpected alias and improves         */
/*                       clarity by indicating that the referenced data is not intended to be modified through this   */
/*                       alias or those depending on it                                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0488)    : Performing pointer arithmetic.                                                               */
/* Rule                : CERTCCM EXP08, MISRA C:2012 Rule-18.4                                                        */
/* JV-01 Justification : This is to get the ID in the data structure in the code.                                     */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0310)    : Casting to different object pointer type.                                                    */
/* Rule                : CERTCCM EXP11, EXP39, MISRA C:2012 Rule-11.3                                                 */
/* JV-01 Justification : For accessing 8-bit and 16-bit PNOT and JPNOT register respectively, the 32-bit pointer is   */
/*                       typecasted.                                                                                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (6:3305)    : Pointer cast to stricter alignment.                                                          */
/* Rule                : CERTCCM EXP36, EXP39, MISRA C:2012 Rule-11.3                                                 */
/* JV-01 Justification : It is an implementation required to manage heap memory. There is no problem because the      */
/*                       4-byte alignment boundary is guaranteed by the implementation of the heap memory             */
/*                       operation algorithm.                                                                         */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0488)    : Performing pointer arithmetic.                                                               */
/* Rule                : CERTCCM EXP08, MISRA C:2012 Rule-18.4                                                        */
/* JV-01 Justification : This is to get the ID in the data structure in the code.                                     */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:2905)    : Constant: Positive integer value truncated by cast to a smaller unsigned type.               */
/* Rule                : CERTCCM INT31, CWE Rule CWE-197, CWE-681, CWE-704, CWE-192, CWE-738                          */
/* JV-01 Justification : To perform 8bit operations on a 16bit register, a cast to uint8 is required.                 */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (7:2821)    : Definite: Arithmetic operation on NULL pointer.                                              */
/* Rule                : CERTCCM EXP34, MISRA C:2012 Dir-4.1, CWE Rule CWE-468, CWE-476, CWE-465, CWE-737             */
/* JV-01 Justification : The value of this pointer is generated by Generation tool, so it can not be NULL             */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:0311)    : Dangerous pointer cast results in loss of const qualification.                               */
/* Rule                : MISRA C:2012 Rule-11.8, CERTCCM EXP05                                                        */
/* JV-01 Justification : This is to achieve throughput in the code.                                                   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:2469)    : Loop control variable in this 'for' statement LucCount is modified in the body of the        */
/*                       loop.                                                                                        */
/* Rule                : MISRA C:2012 Rule-14.2                                                                       */
/* JV-01 Justification : This is to exit from the linear search loop when the required channel Id is found.           */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3416)    : Logical operation performed on expression with persistent side effects.                      */
/* Rule                : CERTCCM EXP45, CWE Rule CWE-398, CWE-569, CWE-737                                            */
/* JV-01 Justification : Logical operation accesses volatile object which is a register access. All register          */
/*                       addresses are generated with volatile qualifier. There is no impact on the functionality     */
/*                       due to this conditional check for mode change.                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3415)    : Right hand operand of '&&' or '||' is an expression with persistent side effects.            */
/* Rule                : MISRA C:2012 Rule-13.5, CERTCCM EXP02, CWE Rule CWE-398, CWE-768, CWE-569                    */
/* JV-01 Justification : Although it is a volatile object, it does not have direct access to the HW register, and     */
/*                       there is no side effect.                                                                     */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:2985)    : This operation is redundant. The value of the result is always that of the left-hand operand.*/
/* Rule                : CERTCCM MSC07, MSC13, MISRA C:2012 Rule-2.2                                                  */
/* JV-01 Justification : For readability, setting to registers will used redundant macros and is based on hardware    */
/*                       user's manual                                                                                */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (6:2991)    : The value of this 'if' controlling expression is always 'true'.                              */
/* Rule                : MISRA C:2012 Rule-14.3                                                                       */
/* JV-01 Justification : Depending on device configuration, there is case where the 'if' will return 'false'.         */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3219)    : Static function '%s()' is not used within this translation unit.                             */
/* Rule                : CERTCCM MSC07, MSC13, MISRA C:2012 Rule-2.2                                                  */
/* JV-01 Justification : This Msg is enabled because it is enforced by MISRA-C Mandatory/Required/AdvisoryRule(s) item*/
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (7:2930)    : Constant: Computing an invalid pointer value.                                                */
/* Rule                : CERTCCM EXP08, ARR30, ARR37, ARR38, MISRA C:2012 Rule-18.1, CWE-120, CWE-121, CWE-122,       */
/*                       CWE-124, CWE-125, CWE-126, CWE-127, CWE-129, CWE-131, CWE-469, CWE-823, CWE-465, CWE-633,    */
/*                       CWE-740                                                                                      */
/* JV-01 Justification : This Msg is enabled because it is enforced by MISRA-C Mandatory/Required/AdvisoryRule(s) item*/
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:2910)    : Constant: Wraparound in unsigned arithmetic operation.                                       */
/* Rule                : CERTCCM INT30, INT08, MISRA C:2012 Rule-12.4, CWE-128, CWE-190, CWE-191, CWE-738, CWE-680    */
/* JV-01 Justification : This Msg is enabled because it is enforced by MISRA-C Mandatory/Required/AdvisoryRule(s) item*/
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (6:2842)    : Apparent: Dereference of an invalid pointer value.                                           */
/* Rule                : MISRA C:2012 Rule-21.18, Rule-18.1, Dir-4.1, CWE-120, CWE-121, CWE-122, CWE-124, CWE-125,    */
/*                       CWE-126, CWE-127, CWE-129, CWE-131, CWE-466, CWE-786, CWE-787, CWE-788, CWE-805, CWE-465,    */
/*                       CWE-633, CWE-740                                                                             */
/* JV-01 Justification : This Msg is enabled because it is enforced by MISRA-C Mandatory/Required/AdvisoryRule(s) item*/
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (6:2995)    : The result of this logical operation is always 'true'.                                       */
/* Rule                : MISRA C:2012 Rule-2.2, CWE-561, CWE-633                                                      */
/* JV-01 Justification : This Msg is enabled because it is enforced by MISRA-C Mandatory/Required/AdvisoryRule(s) item*/
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (6:2880)    : This code is unreachable.                                                                    */
/* Rule                : MISRA C:2012 Rule-2.1, CERTCCM MSC07, CWE Rule CWE-670                                       */
/* JV-01 Justification : Part of the code is manually check and confirmed to be executable depending on the           */
/*                       configuration                                                                                */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (5:2976)    : Definite: Passing address of partially initialized object '%s' to a function parameter       */
/*                       declared as a pointer to const.                                                              */
/* Rule                : CERTCCM EXP33, CWE Rule CWE-456, CWE-908, CWE-452, CWE-737                                   */
/* JV-01 Justification : The message propose that address should be initialized before passed to function             */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:2950)    : Constant: Negative value used in array subscript or pointer arithmetic operation.            */
/* Rule                : CERTCCM ARR30, CWE Rule CWE-120, CWE-121, CWE-122, CWE-124, CWE-125, CWE-126, CWE-127,       */
/*                       CWE-129, CWE-131, CWE-633, CWE-740                                                           */
/* JV-01 Justification : The message propose that address should be initialized before passed to function             */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1503)    : The function '%1s' is defined but is not used within this project.                           */
/* Rule                : MISRA C:2012 Rule-2.1, CERTCCM MSC07, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : This is accepted, due to the module's API is exported for user's usage.                      */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3408)    : '%s' has external linkage and is being defined without any previous declaration.             */
/* Rule                : MISRA C:2012 Rule-8.4, CERTCCM DCL07, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : It is accepted, due to the declaration will be taken care by Os                              */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3387)    : A full expression containing an increment (++) or decrement (--) operator should have no     */
/*                       potential side effects other than that caused by the increment or decrement operator.        */
/* Rule                : MISRA C:2012 Rule-13.3                                                                       */
/* JV-01 Justification : An increment/decrement is created as a side effect. In this case, it's accessing a volatile  */
/*                       object. This can be accepted.                                                                */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:2843)    : Suspicious: Dereference of an invalid pointer value.                                         */
/* Rule                : CERTCCM ARR30, MISRA C:2012 Rule-13.3, CWE-120, CWE-121, CWE-122, CWE-124, CWE-125, CWE-126, */
/*                       CWE-127, CWE-129, CWE-131, CWE-466, CWE-786, CWE-787, CWE-788, CWE-805, CWE-465, CWE-633,    */
/*                       CWE-740                                                                                      */
/* JV-01 Justification : An increment/decrement is created as a side effect. In this case, it's accessing a volatile  */
/*                       object. This can be accepted.                                                                */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:2841)    : Definite: Dereference of an invalid pointer value.                                           */
/* Rule                : MISRA C:2012 Rule-21.18, Rule-18.1, Dir-4.1, CWE-120, CWE-121, CWE-122, CWE-124, CWE-125,    */
/*                       CWE-127, CWE-129, CWE-131, CWE-466, CWE-786, CWE-787, CWE-788, CWE-805, CWE-465, CWE-633,    */
/*                       CWE-740, CWE-126                                                                             */
/* JV-01 Justification : Because this Msg is enforced by MISRA Mandatory,  there is just some info qac-9.5.0-1594,    */
/*                       qac-9.5.0-1594, qac-9.5.0-1575, nothing important                                            */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:2906)    : Definite: Positive integer value truncated by cast to a smaller unsigned type.               */
/* Rule                : CERTCCM INT31                                                                                */
/* JV-01 Justification : Typecasting is done as per the register size, to access hardware registers.                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3205)    : The identifier '%s' is not used and could be removed.                                        */
/* Rule                : CERTCCM MSC07, MSC13, MISRA C:2012 Rule-2.3                                                  */
/* JV-01 Justification : This identifier is used by other file.                                                       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:2004)    : No concluding 'else' exists in this 'if'-'else'-'if' statement.                              */
/* Rule                : CERTCCM MSC01, MISRA C:2012 Rule-15.7                                                        */
/* JV-01 Justification : The "else" statement with empty content is removed to improve readability.                   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (6:2996)    : The result of this logical operation is always 'false'.                                      */
/* Rule                : MISRA C:2012 Rule-2.2, CWE Rule CWE-561, CWE-633                                             */
/* JV-01 Justification : Depending on device status, there is case where the 'if' will return 'true'.                 */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE rule CWE-398, CWE-569                                            */
/*                       REFERENCE - ISO:C90-6.3.1 Primary Expressions                                                */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is           */
/*                       accepted.                                                                                    */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0751)    : Casting to char pointer type.                                                                */
/* Rule                : CERTCCM EXP39, EXP11, CWE Rule CWE-188, CWE-398, CWE-468, CWE-588, CWE-465, CWE-569, CWE-737 */
/* JV-01 Justification : Using void due to specific requirement of input parameter. So, this can be skipped           */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (6:2994)    : The value of this 'while' or 'for' loop controlling expression is always 'false'.            */
/*                       The loop will not be entered.                                                                */
/* Rule                : MISRA C:2012 Rule-14.3                                                                       */
/* JV-01 Justification : Depending on device status, there is case where the 'if' will return 'true'.                 */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:3670)    : Recursive call to function containing this call.                                             */
/* Rule                : MISRA C:2012 Rule-14.3, CERTC MEM05                                                          */
/* JV-01 Justification : This Msg is enabled because it is enforced by MISRA-C Mandatory/Required/AdvisoryRule(s) item*/
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:2983)    : This assignment is redundant. The value of this object is never subsequently used.           */
/* Rule                : CERTCCM MSC07, MSC13, MISRA C:2012 Rule-2.2                                                  */
/* JV-01 Justification : The value is to increment the pointer to the next item.                                      */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3397)    : Extra parentheses recommended. A binary operation is the operand of a binary operator with   */
/*                       different precedence.                                                                        */
/* Rule                : CERTCCM EXP00, MISRA C:2012 Rule-12.1, CWE Rule CWE-398, CWE-783, CWE-569                    */
/* JV-01 Justification : It is confirmed that no data loss occurs if Loss of parentheses , so it is accepted          */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:4461)    : A non-constant expression of 'essentially unsigned' type (%1s) is being converted to         */
/*                       narrower unsigned type, '%2s' on assignment.                                                 */
/* Rule                : MISRA C:2012 Rule-10.3, CERTCCM INT02, CWE Rule CWE-681, CWE-136, CWE-192                    */
/* JV-01 Justification : This operation is necessary to offset a 32-bit address on RAM to a 16-bit buffer address.    */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Internal function                                                   **
***********************************************************************************************************************/

#define FEE_START_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"

STATIC FUNC(MemIf_JobResultType, FEE_PRIVATE_CODE) Fee_InternalRead(MemAcc_AddressType LusSourceAddress, 
                                                  MemAcc_DataType* LpDestinationDataPtr, MemAcc_LengthType LusLength);

STATIC FUNC(MemIf_JobResultType, FEE_PRIVATE_CODE) Fee_InternalWrite(MemAcc_AddressType LusTargetAddress, 
                                                const MemAcc_DataType* LusSourceDataPtr, MemAcc_LengthType LusLength);

STATIC FUNC(uint16, FEE_PRIVATE_CODE) Fee_AlignToVirtualPageSize(uint16 LuBlockSize);

STATIC FUNC(void, FEE_PRIVATE_CODE) Fee_PrepareHeaderFlag(uint8 *LpTargetAreaAddr, const uint32 LucTargetValue);

STATIC FUNC(void, FEE_PRIVATE_CODE) Fee_WriteData2AlignPageSize(const uint8 *LpSourceDataPtr, uint8 *LpDesDataPtr, 
                                                                                              const uint16 LusLength);

STATIC FUNC(Std_ReturnType, FEE_PRIVATE_CODE) Fee_CheckHeaderDataFlag(const uint8 * const LpTargetAddr, 
                                                                    const uint32 LucTargetValue, boolean* LpFlagValue);

STATIC FUNC(Std_ReturnType, FEE_PRIVATE_CODE) Fee_BlankCheck(const uint8 *LpStartAddr, const uint8 *LpEndAddr);

STATIC FUNC(MemIf_JobResultType, FEE_PRIVATE_CODE) Fee_InitScanHeaderAddrArea(void);

STATIC FUNC(Fee_AddrAreaStatusType, FEE_PRIVATE_CODE) 
            Fee_InitGetAreaHeaderInfo(Fee_AddrAreaHeaderType *LpAddrAreaHeaderInfo, const uint8 *LpHeaderDataBufferPtr);

STATIC FUNC(MemIf_JobResultType, FEE_PRIVATE_CODE) Fee_InitScanAddrArea(void);

STATIC FUNC(MemIf_JobResultType, FEE_PRIVATE_CODE) Fee_InitReadBlockHeader(void);

STATIC FUNC(MemIf_JobResultType, FEE_PRIVATE_CODE) Fee_InitEraseAddrArea(void);

STATIC FUNC(void, FEE_PRIVATE_CODE) Fee_PrepareHeaderAddrArea(const Fee_AddrAreaHeaderType *LpAddrAreaHeader, 
                                                                                                uint8 *LpPageHeaderPtr);

STATIC FUNC(Fee_BlockStatusType, FEE_PRIVATE_CODE) Fee_GetBlockDataHeaderInfo(Fee_BlockHeaderType * const LpBlockInfor, 
                                                                                          const uint8 * LpBlockHeader);

STATIC FUNC(void, FEE_PRIVATE_CODE) Fee_PrepareHeaderBlockData(const Fee_BlockHeaderType* LpBlockHeaderInfo,
                                                                                                  uint8 *LpBlockHeader);

STATIC FUNC(MemIf_JobResultType, FEE_PRIVATE_CODE) Fee_JobMainInit(void);

STATIC FUNC(MemIf_JobResultType, FEE_PRIVATE_CODE) Fee_JobInitHeaderParse(void);

STATIC FUNC(MemIf_JobResultType, FEE_PRIVATE_CODE) Fee_JobInitScanBlockHeaderParse(void);

STATIC FUNC(MemIf_JobResultType, FEE_PRIVATE_CODE) Fee_JobInitWriteHeaderFormat(void);

STATIC FUNC(MemIf_JobResultType, FEE_PRIVATE_CODE) Fee_JobInitWriteHeaderFormatDone(void);

STATIC FUNC(MemIf_JobResultType, FEE_PRIVATE_CODE) Fee_JobSwapPrepareNextAddressArea(void);

STATIC FUNC(MemIf_JobResultType, FEE_PRIVATE_CODE) Fee_JobSwapWriteValidAddrArea(void);

STATIC FUNC(MemIf_JobResultType, FEE_PRIVATE_CODE) Fee_JobSwapAddrArea(void);

STATIC FUNC(MemIf_JobResultType, FEE_PRIVATE_CODE) Fee_JobSwapHeaderBlock(void);

STATIC FUNC(MemIf_JobResultType, FEE_PRIVATE_CODE) Fee_JobSwapReadDataBlock(void);

STATIC FUNC(MemIf_JobResultType, FEE_PRIVATE_CODE) Fee_JobSwapWriteDataBlock(void);

STATIC FUNC(MemIf_JobResultType, FEE_PRIVATE_CODE) Fee_JobSwapWriteValidBlock(void);

STATIC FUNC(MemIf_JobResultType, FEE_PRIVATE_CODE) Fee_JobSwapValidAddrArea(void);

STATIC FUNC(MemIf_JobResultType, FEE_PRIVATE_CODE) Fee_JobWriteHeaderData(void);

STATIC FUNC(MemIf_JobResultType, FEE_PRIVATE_CODE) Fee_JobSwapDone(void);

#define FEE_STOP_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/
/***********************************************************************************************************************
** Function Name             : Fee_InternalRead
**
** Service ID                : None
**
** Description               : This Function will initiate the reading jobs to read the flash memory.
**
** Sync/Async                : Asynchronous
**
** Reentrancy                : Non Reentrant
**
** Input Parameters          : LusSourceAddress, LpDestinationDataPtr, LusLength
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : MemIf_JobResultType
**                             MEMIF_JOB_PENDING: The last job is waiting for execution or currently being executed.
**                             MEMIF_JOB_FAILED: The last job has not been finished successfully (it failed).
**
** Preconditions             : None
**
** Global Variables Used     : Fee_GaaAddrAreaConfig[], Fee_GusCurrAddrAreaId(W), Fee_GblWaitMemAccResult
**
** Function(s) invoked       : MemAcc_Read 
**
** Registers Used            : None
**
** Reference ID              : FEE_DUD_ACT_012, FEE_DUD_ACT_012_GBL001
***********************************************************************************************************************/
#define FEE_START_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
STATIC FUNC(MemIf_JobResultType, FEE_PRIVATE_CODE) Fee_InternalRead(MemAcc_AddressType LusSourceAddress, 
                                                    MemAcc_DataType* LpDestinationDataPtr, MemAcc_LengthType LusLength)
{
  Std_ReturnType LucExtReturnValue;
  MemIf_JobResultType LenReturnValue;

  MemAcc_AddressAreaIdType LusAddressAreaId;

  LusAddressAreaId = Fee_GaaAddrAreaConfig[Fee_GusCurrAddrAreaId].usAddrAreaID;

  LucExtReturnValue = MemAcc_Read(LusAddressAreaId, LusSourceAddress, LpDestinationDataPtr, LusLength);

  if (E_OK == LucExtReturnValue)
  {
    /* Reading process has been accepted */
    LenReturnValue = MEMIF_JOB_PENDING;
    /* Set checking MemAcc result flag */
    Fee_GblWaitMemAccResult = FEE_TRUE;
  }
  else
  {
    /* Reading process has not been accepted */
    LenReturnValue = MEMIF_JOB_FAILED;
  }

  /* Return value */
  return (LenReturnValue);
}
#define FEE_STOP_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name             : Fee_InternalWrite
**
** Service ID                : None
**
** Description               : This Function will initiate the writing jobs to write to the flash memory.
**
** Sync/Async                : Asynchronous
**
** Reentrancy                : Non Reentrant
**
** Input Parameters          : LusTargetAddress, LusSourceDataPtr, LusLength
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : MemIf_JobResultType
**                             MEMIF_JOB_PENDING: The last job is waiting for execution or currently being executed.
**                             MEMIF_JOB_FAILED: The last job has not been finished successfully (it failed).
**
** Preconditions             : None
**
** Global Variables Used     : Fee_GaaAddrAreaConfig[], Fee_GusCurrAddrAreaId(W), Fee_GblWaitMemAccResult
**
** Function(s) invoked       : MemAcc_Write
**
** Registers Used            : None
**
** Reference ID              : FEE_DUD_ACT_014, FEE_DUD_ACT_014_GBL001
***********************************************************************************************************************/
#define FEE_START_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
STATIC FUNC(MemIf_JobResultType, FEE_PRIVATE_CODE) Fee_InternalWrite(MemAcc_AddressType LusTargetAddress, 
                                                  const MemAcc_DataType* LusSourceDataPtr, MemAcc_LengthType LusLength)
{
  Std_ReturnType LucExtReturnValue;
  MemIf_JobResultType LenReturnValue;

  MemAcc_AddressAreaIdType LusAddressAreaId;

  LusAddressAreaId = Fee_GaaAddrAreaConfig[Fee_GusCurrAddrAreaId].usAddrAreaID;

  LucExtReturnValue = MemAcc_Write(LusAddressAreaId, LusTargetAddress, LusSourceDataPtr, LusLength);

  if (E_OK == LucExtReturnValue)
  {
    /* Writing header processing has been accept */
    LenReturnValue = MEMIF_JOB_PENDING;
    /* Set checking MemAcc result flag */
    Fee_GblWaitMemAccResult = FEE_TRUE;
  }
  else
  {
    /* Writing header processing has not been accept */
    LenReturnValue = MEMIF_JOB_FAILED;
  }

  /* Return value */
  return (LenReturnValue);
}
#define FEE_STOP_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name             : Fee_AlignToVirtualPageSize
**
** Service ID                : None
**
** Description               : This function is to support align the block size with configured from 
**                             FEE_VIRTUAL_PAGE_SIZE
**
** Sync/Async                : Asynchronous
**
** Reentrancy                : Non Reentrant
**
** Input Parameters          : None
**
** InOut Parameters          : LuBlockSize
**
** Output Parameters         : None
**
** Return parameter          : uint16
**
** Preconditions             : None
**
** Global Variables Used     : None
**
** Function(s) invoked       : None
**
** Registers Used            : None
**
** Reference ID              : FEE_DUD_ACT_015
***********************************************************************************************************************/
#define FEE_START_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
STATIC FUNC(uint16, FEE_PRIVATE_CODE) Fee_AlignToVirtualPageSize(uint16 LuBlockSize)
{
  /* Check whether the block size is integer multiple of FEE_VIRTUAL_PAGE_SIZE */
  if (FEE_ZERO == (LuBlockSize % FEE_VIRTUAL_PAGE_SIZE))
  {
    /* Block size is an integer multiple of FEE_VIRTUAL_PAGE_SIZE */
  }
  else
  {
    LuBlockSize = (uint16)(((LuBlockSize / FEE_VIRTUAL_PAGE_SIZE) + FEE_ONE) * FEE_VIRTUAL_PAGE_SIZE);                  /* PRQA S 1338, 3383, 3384 # JV-01, JV-01, JV-01 */
  }

  return (LuBlockSize);
}
#define FEE_STOP_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name             : Fee_GetBlockIndex
**
** Service ID                : None
**
** Description               : This function is the main function of API Fee_InvalidateBlock, asynchronous from
**                             Fee_MainFunction()
**                             This function is to support check/writing Invalidate Flag on Invlid Address area of block
**
** Sync/Async                : Asynchronous
**
** Reentrancy                : Non Reentrant
**
** Input Parameters          : LusBlockNumber
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : uint16
**
** Preconditions             : None
**
** Global Variables Used     : Fee_GaaBlockConfig(W)
**
** Function(s) invoked       : None
**
** Registers Used            : None
**
** Reference ID              : FEE_DUD_ACT_016
***********************************************************************************************************************/
#define FEE_START_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(uint16, FEE_PRIVATE_CODE) Fee_GetBlockIndex(uint16 LusBlockNumber)
{
  /* Update the pointer to first element of the structure array */
  P2CONST(Fee_ConfigType, AUTOMATIC, FEE_PRIVATE_DATA) LpBlockConfig;

  /* Initialize the middle index to the center element in structure array */
  uint16 LusMidIdx;

  /* Initialize the bottom index to first element */
  uint16 LusBottomIdx = FEE_ONE;

  /* Initialize the top index to last element of structure array */
  uint16 LusTopIdx = FEE_MAX_CONFIGURED_BLOCK_NUMBER - FEE_ONE;

  /* Initialize the default value to 0xFFFF which is other than blocks configured */
  uint16 LusReturnValue = FEE_INVALID_BLOCK_IDX;

  /* Get the pointer to block configuration array */
  LpBlockConfig = &Fee_GaaBlockConfig[FEE_ZERO];

  /* Check whether LusBlockNumber is in range */
  if ((LusBlockNumber >= (LpBlockConfig->usFeeBlockNumber)) && \
                                                        (LusBlockNumber <= (LpBlockConfig[LusTopIdx].usFeeBlockNumber)))
  {
    /* Check whether requested LusBlockNumber is not equal to first LusBlockNumber of the list */
    if (LusBlockNumber != (LpBlockConfig->usFeeBlockNumber))
    {
      do
      {
        /* Get the middle index number */
        LusMidIdx = ((LusTopIdx + LusBottomIdx) >> FEE_ONE);

        /* Compare LusBlockNumber with the requested one */
        if ((LpBlockConfig[LusMidIdx].usFeeBlockNumber) == LusBlockNumber)
        {
          /* Update the block index found with middle index */
          LusReturnValue = LusMidIdx;
          /* Set LusTopIdx to zero to break the loop */
          LusTopIdx = FEE_ZERO;
        }
        else
        {
          /* Compare the LusBlockNumber with the requested one */
          if (LusBlockNumber < (LpBlockConfig[LusMidIdx].usFeeBlockNumber))
          {
            LusTopIdx = LusMidIdx - FEE_ONE;
          }
          else
          {
            /* If the priority is higher, update LusBottomIdx */
            LusBottomIdx = LusMidIdx + FEE_ONE;
          }
        }
      } while (LusBottomIdx <= LusTopIdx);
    }
    else
    {
      LusReturnValue = FEE_ZERO;
    }
  }
  else
  {
    /* No action required */
  }

  return LusReturnValue;
}
#define FEE_STOP_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name             : Fee_PrepareHeaderFlag
**
** Service ID                : None
**
** Description               : This function is to support serial flag header of page/block
**
** Sync/Async                : Asynchronous
**
** Reentrancy                : Non Reentrant
**
** Input Parameters          : LpTargetAreaAddr, LucTargetValue
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : None
**
** Preconditions             : None
**
** Global Variables Used     : None
**
** Function(s) invoked       : None
**
** Registers Used            : None
**
** Reference ID              : FEE_DUD_ACT_017
***********************************************************************************************************************/
#define FEE_START_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
STATIC FUNC(void, FEE_PRIVATE_CODE) Fee_PrepareHeaderFlag(uint8 *LpTargetAreaAddr, const uint32 LucTargetValue)
{
  uint8 *LpTargetAreaAddrAddr;                                                                                          /* PRQA S 3678 # JV-01 */

  /* todo: In feasibility: Page status: Valid flag: 4 bytes + Invalid flag: 4 bytes + Not used (8 bytes) */
  LpTargetAreaAddrAddr = LpTargetAreaAddr + FEE_FOUR_UNIT_SIZE;                                                         /* PRQA S 0488 # JV-01 */
  /* Active/Inactive flag */
  *(uint32 *) LpTargetAreaAddr = LucTargetValue;                                                                        /* PRQA S 0310, 3305 # JV-01, JV-01 */
  FEE_ADDRESS_OFFSET(LpTargetAreaAddr, uint32);                                                                         /* PRQA S 0488, 1338 # JV-01, JV-01 */
  /* Reserved if any */

  LpTargetAreaAddr++;                                                                                                   /* PRQA S 1338 # JV-01 */
  while (LpTargetAreaAddr < LpTargetAreaAddrAddr)
  {
    *LpTargetAreaAddr = (uint8) FEE_ERASED_VALUE;                                                                       /* PRQA S 2905 # JV-01 */
    LpTargetAreaAddr++;                                                                                                 /* PRQA S 1338 # JV-01 */
  }
}
#define FEE_STOP_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name             : Fee_WriteData2AlignPageSize
**
** Service ID                : None
**
** Description               : This function to support for write block data
**
** Sync/Async                : Asynchronous
**
** Reentrancy                : Non Reentrant
**
** Input Parameters          : LpSourceDataPtr, LpDesDataPtr, LusLength
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : None
**
** Preconditions             : None
**
** Global Variables Used     : None
**
** Function(s) invoked       : None
**
** Registers Used            : None
**
** Reference ID              : FEE_DUD_ACT_018
***********************************************************************************************************************/
#define FEE_START_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
STATIC FUNC(void, FEE_PRIVATE_CODE) Fee_WriteData2AlignPageSize(const uint8 *LpSourceDataPtr, uint8 *LpDesDataPtr, 
                                                                                                const uint16 LusLength)
{
  uint8 *LpTargetAddr;                                                                                                  /* PRQA S 3678 # JV-01 */
  uint8 *LpEndAddrPtr;                                                                                                  /* PRQA S 3678 # JV-01 */

  LpTargetAddr = LpDesDataPtr + LusLength;                                                                              /* PRQA S 0488 # JV-01 */

  LpEndAddrPtr = LpDesDataPtr + FEE_VIRTUAL_PAGE_SIZE;                                                                  /* PRQA S 0488 # JV-01 */

  while (LpDesDataPtr < LpTargetAddr)
  {
    *LpDesDataPtr = *LpSourceDataPtr;
    LpSourceDataPtr++;                                                                                                  /* PRQA S 1338 # JV-01 */
    LpDesDataPtr++;                                                                                                     /* PRQA S 1338 # JV-01 */
  }
  
  while (LpDesDataPtr < LpEndAddrPtr)
  {
    *LpDesDataPtr = (uint8)FEE_ERASED_VALUE;                                                                            /* PRQA S 2905 # JV-01 */
    LpDesDataPtr++;                                                                                                     /* PRQA S 1338 # JV-01 */
  }
}
#define FEE_STOP_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name             : Fee_CheckHeaderDataFlag
**
** Service ID                : None
**
** Description               : The function to support check value of Valid/Invalid Flag
**
** Sync/Async                : Asynchronous
**
** Reentrancy                : Non Reentrant
**
** Input Parameters          : LpTargetAddr, LucTargetValue, LpFlagValue
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : Std_ReturnType
**                             E_OK: The requested job has been accepted by the module.
**                             E_NOT_OK - only if DET is enabled: The requested job has not been accepted by the module.
**
** Preconditions             : None
**
** Global Variables Used     : None
**
** Function(s) invoked       : None
**
** Registers Used            : None
**
** Reference ID              : FEE_DUD_ACT_019
***********************************************************************************************************************/
#define FEE_START_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
STATIC FUNC(Std_ReturnType, FEE_PRIVATE_CODE) Fee_CheckHeaderDataFlag(const uint8 * const LpTargetAddr, 
                                                                      const uint32 LucTargetValue, boolean* LpFlagValue)
{
  Std_ReturnType LucReturnValue = E_OK;

  if (LucTargetValue == *(uint32 *) LpTargetAddr)                                                                       /* PRQA S 3305, 0310, 0311 # JV-01, JV-01, JV-01 */                                                                    
  {
      *LpFlagValue = (boolean) TRUE;
  }
  else if (FEE_ERASED_VALUE == *(uint32 *) LpTargetAddr)                                                                /* PRQA S 3305, 0310, 0311 # JV-01, JV-01, JV-01 */
  {
      *LpFlagValue = (boolean) FALSE;
  }
  else
  {
    LucReturnValue = E_NOT_OK;
  }

  /* Return value */
  return (LucReturnValue);
}
#define FEE_STOP_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name             : Fee_BlankCheck
**
** Service ID                : None
**
** Description               : The function to support check blank check of start address to end address from input
**
** Sync/Async                : Asynchronous
**
** Reentrancy                : Non Reentrant
**
** Input Parameters          : LpStartAddr, LpEndAddr
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : Std_ReturnType
**                             E_OK: The requested job has been accepted by the module.
**                             E_NOT_OK - only if DET is enabled: The requested job has not been accepted by the module.
**
** Preconditions             : None
**
** Global Variables Used     : None
**
** Function(s) invoked       : None
**
** Registers Used            : None
**
** Reference ID              : FEE_DUD_ACT_020
***********************************************************************************************************************/
#define FEE_START_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
STATIC FUNC(Std_ReturnType, FEE_PRIVATE_CODE) Fee_BlankCheck(const uint8 *LpStartAddr, const uint8 *LpEndAddr)
{
  /* Declare the return value */
  Std_ReturnType LucReturnValue = E_OK;

  while (LpStartAddr < LpEndAddr)
  {
    if (FEE_ERASED_VALUE == *(uint32 *)LpStartAddr)                                                                     /* PRQA S 0311, 0310, 3305 # JV-01, JV-01, JV-01 */
    {
      /* Do nothing */
    }
    else
    {
      /* Move to the end of checked address */
      LpStartAddr = LpEndAddr;                                                                                          /* PRQA S 1338 # JV-01 */

      /* Return to E_NOT_OK when address is not blank*/
      LucReturnValue = E_NOT_OK;
    }
    LpStartAddr = LpStartAddr + sizeof(uint32);                                                                         /* PRQA S 1338, 0488 # JV-01, JV-01 */
  }

  /* Return value */
  return (LucReturnValue);
}
#define FEE_STOP_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name             : Fee_PrepareHeaderAddrArea
**
** Service ID                : None
**
** Description               : This function is to support serial page data header
**
** Sync/Async                : Asynchronous
**
** Reentrancy                : Non Reentrant
**
** Input Parameters          : LpAddrAreaHeader, LpPageHeaderPtr
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : None
**
** Preconditions             : None
**
** Global Variables Used     : None
**
** Function(s) invoked       : None
**
** Registers Used            : None
**
** Reference ID              : FEE_DUD_ACT_021
***********************************************************************************************************************/
#define FEE_START_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
STATIC FUNC(void, FEE_PRIVATE_CODE) Fee_PrepareHeaderAddrArea(const Fee_AddrAreaHeaderType *LpAddrAreaHeader, 
                                                                                                uint8 *LpPageHeaderPtr)
{
  /* Address area header ID */
  *(uint32 *) LpPageHeaderPtr = (uint32) LpAddrAreaHeader->usAddrAreaID;                                                /* PRQA S 0310, 3305 # JV-01, JV-01 */
  FEE_ADDRESS_OFFSET(LpPageHeaderPtr, uint32);                                                                          /* PRQA S 0488, 1338 # JV-01, JV-01 */

  /* Address area start address */
  *(MemAcc_AddressType *) LpPageHeaderPtr = LpAddrAreaHeader->ulStartAreaAddr;                                          /* PRQA S 0310, 3305 # JV-01, JV-01 */
  FEE_ADDRESS_OFFSET(LpPageHeaderPtr, MemAcc_AddressType);                                                              /* PRQA S 0488, 1338 # JV-01, JV-01 */

  /* Address area size */
  *(MemAcc_AddressType *) LpPageHeaderPtr = LpAddrAreaHeader->ulAddrAreaSize;                                           /* PRQA S 0310, 3305 # JV-01, JV-01 */
  FEE_ADDRESS_OFFSET(LpPageHeaderPtr, MemAcc_AddressType);                                                              /* PRQA S 0488, 1338 # JV-01, JV-01 */

  /* Address area data direction */
  *(uint32 *) LpPageHeaderPtr = LpAddrAreaHeader->ulConfigDirection;                                                    /* PRQA S 0310, 3305 # JV-01, JV-01 */
  FEE_ADDRESS_OFFSET(LpPageHeaderPtr, uint32);                                                                          /* PRQA S 0488, 1338, 2983 # JV-01, JV-01, JV-01 */

}
#define FEE_STOP_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name             : Fee_InitGetAreaHeaderInfo
**
** Service ID                : None
**
** Description               : The function to support get address from input Data Buffer of function 
**                             Fee_InitScanHeaderAddrArea
**
** Sync/Async                : Asynchronous
**
** Reentrancy                : Non Reentrant
**
** Input Parameters          : LpAddrAreaHeaderInfo, LpHeaderDataBufferPtr
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : Fee_AddrAreaStatusType
**                             FEE_ADDRESS_AREA_VALID: Fee Page is valid.
**                             FEE_ADDRESS_AREA_INVALID - Fee Page is invalid.
**                             FEE_ADDRESS_AREA_INCONSISTENT - Fee Page is inconsistent.
**                             FEE_ADDRESS_AREA_HEADER_INVALID - Fee Page is garbled.
**
** Preconditions             : None
**
** Global Variables Used     : None
**
** Function(s) invoked       : Fee_BlankCheck, Fee_CheckHeaderDataFlag                         
**
** Registers Used            : None
**
** Reference ID              : FEE_DUD_ACT_022
***********************************************************************************************************************/
/* Address Area Header: 
  Address Area ID (4 bytes) + Address Area Address (4 bytes) + Address Area Size (4 bytes) + Direction (4 bytes) 
*/
#define FEE_START_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
STATIC FUNC(Fee_AddrAreaStatusType, FEE_PRIVATE_CODE) Fee_InitGetAreaHeaderInfo(
                                      Fee_AddrAreaHeaderType *LpAddrAreaHeaderInfo, const uint8 *LpHeaderDataBufferPtr)
{
  /* Declaring the return value */
  Fee_AddrAreaStatusType LenReturnValue;
  boolean LblValidFlag;
  boolean LblFlagInvalid;
  const uint8 *LpEndHeaderAreaAddr;
  VAR(Std_ReturnType, AUTOMATIC) LenBlankCheckReturnValue;
  VAR(Std_ReturnType, AUTOMATIC) LenFlagValidReturnValue;
  VAR(Std_ReturnType, AUTOMATIC) LenFlagInvalidReturnValue;

  /* Initialize the first return value and default value for Valid/InValid Flag*/
  LenReturnValue = FEE_ADDRESS_AREA_HEADER_INVALID;

  LblValidFlag = FALSE;
  LblFlagInvalid = FALSE;

  /* Calculate end address of current block */
  LpEndHeaderAreaAddr = LpHeaderDataBufferPtr + (FEE_PAGE_OVERHEAD - FEE_VALID_ADDRESS_AREA_OFFSET_ADDR);               /* PRQA S 0488 # JV-01 */

  /* ID of Address Area header */
  LpAddrAreaHeaderInfo->usAddrAreaID = *((const MemAcc_AddressAreaIdType *)LpHeaderDataBufferPtr);                      /* PRQA S 3305, 0310 # JV-01, JV-01 */
  /* To align with 4 bytes */
  FEE_ADDRESS_OFFSET(LpHeaderDataBufferPtr, uint32);                                                                    /* PRQA S 1338, 0488 # JV-01, JV-01 */

  /* Status of Address Area header */
  LpAddrAreaHeaderInfo->ulStartAreaAddr = *((const MemAcc_AddressType *)LpHeaderDataBufferPtr);                         /* PRQA S 0310, 3305 # JV-01, JV-01 */
  FEE_ADDRESS_OFFSET(LpHeaderDataBufferPtr, MemAcc_AddressType);                                                        /* PRQA S 0488, 1338 # JV-01, JV-01 */

  /* Size of Address Area header */
  LpAddrAreaHeaderInfo->ulAddrAreaSize = *((const MemAcc_LengthType *)LpHeaderDataBufferPtr);                           /* PRQA S 0310, 3305 # JV-01, JV-01 */
  FEE_ADDRESS_OFFSET(LpHeaderDataBufferPtr, MemAcc_LengthType);                                                         /* PRQA S 0488, 1338 # JV-01, JV-01 */

  /* Data direction */
  LpAddrAreaHeaderInfo->ulConfigDirection = *((const uint32 *)LpHeaderDataBufferPtr);                                   /* PRQA S 0310, 3305 # JV-01, JV-01 */
  FEE_ADDRESS_OFFSET(LpHeaderDataBufferPtr, uint32);                                                                    /* PRQA S 0488, 1338 # JV-01, JV-01 */

  LenBlankCheckReturnValue = Fee_BlankCheck(LpHeaderDataBufferPtr, LpEndHeaderAreaAddr);
  LenFlagValidReturnValue = Fee_CheckHeaderDataFlag(LpEndHeaderAreaAddr, FEE_VALIDATED_VALUE, &LblValidFlag);
  LenFlagInvalidReturnValue = Fee_CheckHeaderDataFlag(LpEndHeaderAreaAddr + FEE_ONE_UNIT_SIZE,                          /* PRQA S 0488 # JV-01 */
                                                              FEE_INVALIDATED_FLAG_VALUE, &LblFlagInvalid);

  /* Check status of Addr Area: Valid/InValid Flag  */
  if ((E_NOT_OK == LenBlankCheckReturnValue) || (E_NOT_OK == LenFlagValidReturnValue) ||
                                                                  (E_NOT_OK == LenFlagInvalidReturnValue))
  {
    /* FEE_ADDRESS_AREA_HEADER_INVALID */
  }
  else
  {
    if ((FALSE == LblValidFlag) && (FALSE == LblFlagInvalid))
    {
      /* Invalid header: 0xFFFF FFFF FFFF FFFF */
      LenReturnValue = FEE_ADDRESS_AREA_INCONSISTENT;
    }
    else if ((TRUE == LblValidFlag) && (FALSE == LblFlagInvalid))
    {
      /* Active header: 0x5555 FFFF FFFF FFFF */
      LenReturnValue = FEE_ADDRESS_AREA_VALID;
    }
    else
    {
      /* Inactive header: 0x5555 5555 FFFF FFFF */
      LenReturnValue = FEE_ADDRESS_AREA_INVALID;
    }
  }

  /* Return value */
  return (LenReturnValue);
}
#define FEE_STOP_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name             : Fee_PrepareHeaderBlockData
**
** Service ID                : None
**
** Description               : This function to support for serial data block header
**
** Sync/Async                : Asynchronous
**
** Reentrancy                : Non Reentrant
**
** Input Parameters          : LpBlockHeaderInfo, LpBlockHeader
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : None
**
** Preconditions             : None
**
** Global Variables Used     : None
**
** Function(s) invoked       : None
**
** Registers Used            : None
**
** Reference ID              : FEE_DUD_ACT_023
***********************************************************************************************************************/
#define FEE_START_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
STATIC FUNC(void, FEE_PRIVATE_CODE) Fee_PrepareHeaderBlockData(const Fee_BlockHeaderType* LpBlockHeaderInfo,
                                                                                                  uint8 *LpBlockHeader)
{
  uint32 ulCRC;

  /* Block ID */
  *(uint16 *)LpBlockHeader = (uint16) LpBlockHeaderInfo->usFeeBlockNumber;                                              /* PRQA S 0310, 3305 # JV-01, JV-01 */
  FEE_ADDRESS_OFFSET(LpBlockHeader, uint16);                                                                            /* PRQA S 1338, 0488 # JV-01, JV-01 */
  
  /* Block Size */
  *(uint16 *)LpBlockHeader = (uint16) LpBlockHeaderInfo->usBlockSize;                                                   /* PRQA S 0310, 3305 # JV-01, JV-01 */
  FEE_ADDRESS_OFFSET(LpBlockHeader, uint16);                                                                            /* PRQA S 1338, 0488 # JV-01, JV-01 */

  /* Block Data Address */
  *(uint32 *)LpBlockHeader = (uint32) LpBlockHeaderInfo->ulBlockDataAddr;                                               /* PRQA S 0310, 3305 # JV-01, JV-01 */
  FEE_ADDRESS_OFFSET(LpBlockHeader, uint32);                                                                            /* PRQA S 0488, 1338 # JV-01, JV-01 */

  /* Block WE Cycle */
  *(uint32 *)LpBlockHeader = (uint32) LpBlockHeaderInfo->ulWECycles;                                                    /* PRQA S 0310, 3305 # JV-01, JV-01 */
  FEE_ADDRESS_OFFSET(LpBlockHeader, uint32);                                                                            /* PRQA S 0488, 1338 # JV-01, JV-01 */

  /* ulCRC */
  /* Update argorithm to calculate CRC */
  ulCRC = ((uint32)LpBlockHeaderInfo->usFeeBlockNumber + (uint32)LpBlockHeaderInfo->usBlockSize +                       /* PRQA S 3384 # JV-01 */
                  (uint32)LpBlockHeaderInfo->ulBlockDataAddr + (uint32)LpBlockHeaderInfo->ulWECycles) & FEE_UINT32_MASK;/* PRQA S 2985, 3384 # JV-01, JV-01 */
  *(uint32 *)LpBlockHeader = ulCRC;                                                                                     /* PRQA S 0310, 3305 # JV-01, JV-01 */
  FEE_ADDRESS_OFFSET(LpBlockHeader, uint32);                                                                            /* PRQA S 0488, 1338, 2983 # JV-01, JV-01, JV-01 */

}
#define FEE_STOP_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name             : Fee_GetBlockDataHeaderInfo
**
** Service ID                : None
**
** Description               : This function is to support deserialize data of block header
**
** Sync/Async                : Asynchronous
**
** Reentrancy                : Non Reentrant
**
** Input Parameters          : LpBlockInfor, LpBlockHeader
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : Fee_BlockStatusType
**                             FEE_BLOCK_VALID: Fee block is valid.
**                             FEE_BLOCK_INVALID - Fee block is invalid.
**                             FEE_BLOCK_INCONSISTENT - Fee block is inconsistent.
**                             FEE_BLOCK_HEADER_INVALID - Fee block is garbled.
**                             FEE_BLOCK_HEADER_BLANK - Fee block header is blank.
**
** Preconditions             : None
**
** Global Variables Used     : None
**
** Function(s) invoked       : Fee_BlankCheck, Fee_CheckHeaderDataFlag
**
** Registers Used            : None
**
** Reference ID              : FEE_DUD_ACT_024
***********************************************************************************************************************/
/* todo: Parameter pImmediateBlock have not been implemented */
#define FEE_START_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
STATIC FUNC(Fee_BlockStatusType, FEE_PRIVATE_CODE) Fee_GetBlockDataHeaderInfo(Fee_BlockHeaderType *const LpBlockInfor, 
                                                                                            const uint8 * LpBlockHeader)
{
  Fee_BlockStatusType LenReturnValue;
  boolean LblFlagValid;
  boolean LblFlagInValid;
  VAR(Std_ReturnType, AUTOMATIC) LenBlankCheckReturnValue;
  VAR(Std_ReturnType, AUTOMATIC) LenFlagValidReturnValue;
  VAR(Std_ReturnType, AUTOMATIC) LenFlagInvalidReturnValue;

  const uint8 *LpValidBlockAddr;

  uint32 LulCRC;

  LblFlagValid = FALSE;
  LblFlagInValid = FALSE;

  LenReturnValue = FEE_BLOCK_HEADER_INVALID;
  LenBlankCheckReturnValue = Fee_BlankCheck(LpBlockHeader,LpBlockHeader + FEE_BLOCK_OVERHEAD -                             /* PRQA S 0488 # JV-01 */
                                                                                      FEE_INVALID_BLOCK_OFFSET_ADDR);

  /* Size of block header is 20 bytes */
  if (E_OK == LenBlankCheckReturnValue)
  {
    LenReturnValue = FEE_BLOCK_HEADER_BLANK;
  }
  else
  {
    LpValidBlockAddr = LpBlockHeader + FEE_BLOCK_OVERHEAD - FEE_VALID_BLOCK_OFFSET_ADDR;                                /* PRQA S 0488 # JV-01 */

    LpBlockInfor->usFeeBlockNumber = *(uint16 *) LpBlockHeader;                                                         /* PRQA S 0311, 0310, 3305 # JV-01, JV-01, JV-01 */
    FEE_ADDRESS_OFFSET(LpBlockHeader, uint16);                                                                          /* PRQA S 1338, 0488 # JV-01, JV-01 */

    LpBlockInfor->usBlockSize = *(uint16 *) (LpBlockHeader);                                                            /* PRQA S 0311, 3305, 0310 # JV-01, JV-01, JV-01 */
    FEE_ADDRESS_OFFSET(LpBlockHeader, uint16);                                                                          /* PRQA S 0488, 1338 # JV-01, JV-01 */

    LpBlockInfor->ulBlockDataAddr = *(MemAcc_AddressType *) (LpBlockHeader);                                            /* PRQA S 0311, 3305, 0310 # JV-01, JV-01, JV-01 */
    FEE_ADDRESS_OFFSET(LpBlockHeader, MemAcc_AddressType);                                                              /* PRQA S 0488, 1338 # JV-01, JV-01 */

    LpBlockInfor->ulWECycles = *(uint32 *) (LpBlockHeader);                                                             /* PRQA S 0311, 3305, 0310 # JV-01, JV-01, JV-01 */
    FEE_ADDRESS_OFFSET(LpBlockHeader, uint32);                                                                          /* PRQA S 0488, 1338 # JV-01, JV-01 */

    LpBlockInfor->ulBlockCRC = *(MemAcc_AddressType *) (LpBlockHeader);                                                 /* PRQA S 0311, 3305, 0310 # JV-01, JV-01, JV-01 */
    FEE_ADDRESS_OFFSET(LpBlockHeader, MemAcc_AddressType);                                                              /* PRQA S 0488, 1338 # JV-01, JV-01 */

    /* Calculate check sum of header block */
    LulCRC = (uint32)LpBlockInfor->usFeeBlockNumber + (uint32)LpBlockInfor->usBlockSize +                               /* PRQA S 3384 # JV-01 */
                                              (uint32)LpBlockInfor->ulBlockDataAddr + (uint32)LpBlockInfor->ulWECycles; /* PRQA S 3384 # JV-01 */
    LenBlankCheckReturnValue = Fee_BlankCheck(LpBlockHeader, LpValidBlockAddr);
    LenFlagValidReturnValue = Fee_CheckHeaderDataFlag(LpValidBlockAddr, FEE_VALIDATED_VALUE, &LblFlagValid);               
    LenFlagInvalidReturnValue = Fee_CheckHeaderDataFlag(LpValidBlockAddr + FEE_ONE_UNIT_SIZE,                              /* PRQA S 0488 # JV-01 */
                                                            FEE_INVALIDATED_FLAG_VALUE, &LblFlagInValid);
                                                            
    if (((LpBlockInfor->ulBlockCRC & FEE_UINT32_MASK) != (LulCRC & FEE_UINT32_MASK)) ||                                 /* PRQA S 2985 # JV-01 */
    (E_NOT_OK == LenBlankCheckReturnValue) || (E_NOT_OK == LenFlagValidReturnValue) ||
                                                                  (E_NOT_OK == LenFlagInvalidReturnValue))
    {
      /* FEE_BLOCK_HEADER_INVALID */
    }
    else
    {
      if ((FEE_FALSE == LblFlagValid) && (FEE_FALSE == LblFlagInValid))
      {
        LenReturnValue = FEE_BLOCK_INCONSISTENT;
      }
      else if ((FEE_TRUE == LblFlagValid) && (FEE_FALSE == LblFlagInValid))
      {
        LenReturnValue = FEE_BLOCK_VALID;
      }
      else
      {
        LenReturnValue = FEE_BLOCK_INVALID;
      }
    }
  }

  return (LenReturnValue);
}
#define FEE_STOP_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
**                                                 Fee_Init()                                                         **
***********************************************************************************************************************/
/***********************************************************************************************************************
** Function Name             : Fee_JobMainInit
**
** Service ID                : None
**
** Description               : This function is the main function of API Fee_Init, asynchronous from
**                             Fee_MainFunction()
**                             This function is to support initilize the Init processing
**
** Sync/Async                : Asynchronous
**
** Reentrancy                : Non Reentrant
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : MemIf_JobResultType
**                             MEMIF_JOB_OK: The last job has been finished successfully.
**                             MEMIF_JOB_PENDING: The last job is waiting for execution or currently being executed.
**                             MEMIF_JOB_FAILED: The last job has not been finished successfully (it failed).
**
** Preconditions             : None
**
** Global Variables Used     : None
**
** Function(s) invoked       : Fee_InitScanHeaderAddrArea
**
** Registers Used            : None
**
** Reference ID              : FEE_DUD_ACT_025
***********************************************************************************************************************/
/* After invoke API Fee_Init() -> Fee_MainFunction() 
+ Fee_InitScanHeaderAddrArea: Consistent approach for user when using Fee_MainFunction()
*/
#define FEE_START_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
STATIC FUNC(MemIf_JobResultType, FEE_PRIVATE_CODE) Fee_JobMainInit(void)
{
  /* Define return value */
  MemIf_JobResultType LenReturnValue;

  /* Scan the Page header: RAED */
  LenReturnValue = Fee_InitScanHeaderAddrArea();

  /* Return value */
  return LenReturnValue;
}
#define FEE_STOP_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name             : Fee_InitScanHeaderAddrArea
**
** Service ID                : None
**
** Description               : This function is to support scan Page header if it valid or not of previous stored data
**
** Sync/Async                : Asynchronous
**
** Reentrancy                : Non Reentrant
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : MemIf_JobResultType
**                             MEMIF_JOB_PENDING: The last job is waiting for execution or currently being executed.
**                             MEMIF_JOB_FAILED: The last job has not been finished successfully (it failed).
**
** Preconditions             : None
**
** Global Variables Used     : Fee_GenRequestedCmd(W), Fee_GaaAddrAreaConfig(W), Fee_GusCurrAddrAreaId,
**                           : Fee_GusCurrSubAddrAreaId
**
** Function(s) invoked       : Fee_InternalRead, Fee_GaaDataBuffer
**
** Registers Used            : None
**
** Reference ID              : FEE_DUD_ACT_026, FEE_DUD_ACT_026_GBL001
***********************************************************************************************************************/
#define FEE_START_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
STATIC FUNC(MemIf_JobResultType, FEE_PRIVATE_CODE) Fee_InitScanHeaderAddrArea(void)
{
  MemIf_JobResultType LenReturnValue;
  MemAcc_AddressType LulHeaderAddr;

  /* Get the current start address */
  LulHeaderAddr = Fee_GaaAddrAreaConfig[Fee_GusCurrAddrAreaId].pSubAddrArea[Fee_GusCurrSubAddrAreaId].ulStartAreaAddr;

  /* Scan header to read status of the current address area id */
  LenReturnValue = Fee_InternalRead(LulHeaderAddr, (P2VAR(uint8, AUTOMATIC, FEE_APPL_DATA))                             /* PRQA S 0751, 3432 # JV-01, JV-01 */
                                                                               Fee_GaaDataBuffer, FEE_PAGE_OVERHEAD);   

  /* Scan header successfully => Move to the next step of the initialize phase */
  /* Update Command -> Async proceed by Mainfunction */
  Fee_GenRequestedCmd = FEE_CMD_INIT_ADDRESS_AREA_HEADER_PARSE;

  return (LenReturnValue);
}
#define FEE_STOP_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name             : Fee_JobInitHeaderParse
**
** Service ID                : None
**
** Description               : This function is to support read data and confirm data in header address area
**
** Sync/Async                : Asynchronous
**
** Reentrancy                : Non Reentrant
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : MemIf_JobResultType
**                             MEMIF_JOB_OK: The last job has been finished successfully.
**                             MEMIF_JOB_PENDING: The last job is waiting for execution or currently being executed.
**                             MEMIF_JOB_FAILED: The last job has not been finished successfully (it failed).
**
** Preconditions             : None
**
** Global Variables Used     : Fee_GaaAddrAreaConfig[], Fee_GaaAddrAreaInfo[], Fee_GusCurrAddrAreaId,
**                           : Fee_GusCurrSubAddrAreaId, Fee_GaaDataBuffer
**
** Function(s) invoked       : Fee_InitGetAreaHeaderInfo, Fee_InitScanAddrArea
**                             Fee_InitScanHeaderAddrArea
**
** Registers Used            : None
**
** Reference ID              : FEE_DUD_ACT_027, FEE_DUD_ACT_027_GBL001, FEE_DUD_ACT_027_GBL002
** Reference ID              : FEE_DUD_ACT_027_GBL003, FEE_DUD_ACT_027_GBL004, FEE_DUD_ACT_027_GBL005
***********************************************************************************************************************/
#define FEE_START_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
STATIC FUNC(MemIf_JobResultType, FEE_PRIVATE_CODE) Fee_JobInitHeaderParse(void)
{
  MemIf_JobResultType LenReturnValue;
  Fee_AddrAreaStatusType LenAreaAddrStatus;

  /* Structure of address area header infor */
  Fee_AddrAreaHeaderType LstHeaderInfo;
  /* Structure of conigured address area */
  Fee_AddrAreaHeaderType LstAddrAreaConfig;

  /* Get the address area ID */
  LstAddrAreaConfig.usAddrAreaID = Fee_GaaAddrAreaConfig[Fee_GusCurrAddrAreaId].usAddrAreaID;

  /* Get the current config start address */
  LstAddrAreaConfig.ulStartAreaAddr = 
                    Fee_GaaAddrAreaConfig[Fee_GusCurrAddrAreaId].pSubAddrArea[Fee_GusCurrSubAddrAreaId].ulStartAreaAddr;

  /* Get the current config area size */
  LstAddrAreaConfig.ulAddrAreaSize = 
                    Fee_GaaAddrAreaConfig[Fee_GusCurrAddrAreaId].pSubAddrArea[Fee_GusCurrSubAddrAreaId].ulAddrAreaSize;

  /* Get the information of header */
  LenAreaAddrStatus = Fee_InitGetAreaHeaderInfo(&LstHeaderInfo, (P2CONST(uint8, AUTOMATIC, FEE_APPL_CONST))             /* PRQA S 0751 # JV-01 */
                                                                                                    Fee_GaaDataBuffer); 
  /* Check for the information of Page header is equal with Defined Page */
  if ((FEE_ADDRESS_AREA_VALID == LenAreaAddrStatus) && \
      (LstAddrAreaConfig.usAddrAreaID < LstHeaderInfo.usAddrAreaID ) && \
      (LstAddrAreaConfig.ulStartAreaAddr == LstHeaderInfo.ulStartAreaAddr) && \
      (LstAddrAreaConfig.ulAddrAreaSize == LstHeaderInfo.ulAddrAreaSize) && \
      (FEE_DATA_DIRECTION == LstHeaderInfo.ulConfigDirection))
  {
    /* Found valid address area */
    Fee_GaaAddrAreaInfo[Fee_GusCurrAddrAreaId].usAddrAreaID = (uint32)LstHeaderInfo.usAddrAreaID - (uint32)FEE_ONE;     /* PRQA S 3384 # JV-01 */
    Fee_GaaAddrAreaInfo[Fee_GusCurrAddrAreaId].usSubAddrAreaIndex = Fee_GusCurrSubAddrAreaId;
  }
  else
  {
    /* Invalid, Inconsistent address area */
  }

  /* Move to next sub-address area configuration */
  Fee_GusCurrSubAddrAreaId++;                                                                                           /* PRQA S 3383 # JV-01 */

  if (Fee_GusCurrSubAddrAreaId == Fee_GaaAddrAreaConfig[Fee_GusCurrAddrAreaId].usNumOfSubAddrArea)
  {
    /* Move to next address area */
    Fee_GusCurrAddrAreaId++;                                                                                            /* PRQA S 3383 # JV-01 */
    Fee_GusCurrSubAddrAreaId = FEE_ZERO;
  }

  /* If the current address area is equal to number of configured address area */
  /* Reset the current address value to 0 to begin scan the configured data */
  if (FEE_MAX_DEFINED_ADDRESS_AREA_NUMBER == Fee_GusCurrAddrAreaId)
  {
    /*  End of Address Area Coniguration */
    Fee_GusCurrAddrAreaId = FEE_ZERO;

    /* Begin scan the configured data */
    LenReturnValue = Fee_InitScanAddrArea();
  }
  else
  {
    /* Read the next address area header */
    LenReturnValue = Fee_InitScanHeaderAddrArea();
  }

  /* Return value */
  return (LenReturnValue);
}
#define FEE_STOP_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name             : Fee_InitScanAddrArea
**
** Service ID                : None
**
** Description               : The function to support scan active address area of current area or erase and format 
**                             the first address area if an active address area can not be found
**
** Sync/Async                : Asynchronous
**
** Reentrancy                : Non Reentrant
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : MemIf_JobResultType
**                             MEMIF_JOB_OK: The last job has been finished successfully.
**                             MEMIF_JOB_PENDING: The last job is waiting for execution or currently being executed.
**                             MEMIF_JOB_FAILED: The last job has not been finished successfully (it failed).
**
** Preconditions             : None
**
** Global Variables Used     : Fee_GaaAddrAreaInfo[], Fee_GaaAddrAreaConfig[], Fee_GusCurrAddrAreaId,
**                           : Fee_GenRequestedCmd
**
** Function(s) invoked       : Fee_InitEraseAddrArea, Fee_InitReadBlockHeader
**
** Registers Used            : None
**
** Reference ID              : FEE_DUD_ACT_028, FEE_DUD_ACT_028_GBL001, FEE_DUD_ACT_028_GBL002
** Reference ID              : FEE_DUD_ACT_028_GBL003, FEE_DUD_ACT_028_GBL004, FEE_DUD_ACT_028_GBL005
***********************************************************************************************************************/
#define FEE_START_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
STATIC FUNC(MemIf_JobResultType, FEE_PRIVATE_CODE) Fee_InitScanAddrArea(void)
{
  MemIf_JobResultType LenReturnValue;
  
  uint16 LusSubAddrAreaIndex;
  MemAcc_AddressType LulStartAreaAddr;
  #if (FEE_WRITE_DATA_IN_REVERT_DIRECTION == STD_ON)
  MemAcc_LengthType LulAddrAreaSize;
  #endif /* #if (FEE_WRITE_DATA_IN_REVERT_DIRECTION == STD_ON) */

  LenReturnValue = MEMIF_JOB_OK;

  /* Check if the current address area is maximum of number of configured address area */
  if (FEE_MAX_DEFINED_ADDRESS_AREA_NUMBER == Fee_GusCurrAddrAreaId)
  {
    /* Update request to no pending */
    Fee_GenRequestedCmd = FEE_CMD_NO_PENDING;
  }
  else
  {
    /* Check if there is no any address area are found */
    if (FEE_INVALID_ADDRESS_AREA_IDX == Fee_GaaAddrAreaInfo[Fee_GusCurrAddrAreaId].usAddrAreaID)
    {
      Fee_GusCurrSubAddrAreaId = FEE_ZERO;

      /* No Address Area found -> Erase and Format the first address area one */
      LenReturnValue = Fee_InitEraseAddrArea();
    }
    else
    {
      /* Get index of address area */
      LusSubAddrAreaIndex = Fee_GaaAddrAreaInfo[Fee_GusCurrAddrAreaId].usSubAddrAreaIndex;

      /* Get start address of current address area */
      LulStartAreaAddr = Fee_GaaAddrAreaConfig[Fee_GusCurrAddrAreaId].pSubAddrArea[LusSubAddrAreaIndex].ulStartAreaAddr;

      /* Calculate the address of first block */
      Fee_GulJobRefAreaAddr = LulStartAreaAddr + FEE_PAGE_OVERHEAD;                                                     /* PRQA S 3383 # JV-01 */

      /* Update the current address */
      Fee_GaaAddrAreaInfo[Fee_GusCurrAddrAreaId].ulCurrHeaderAreaAddr = Fee_GulJobRefAreaAddr;

      #if (FEE_WRITE_DATA_IN_REVERT_DIRECTION == STD_ON)
      /* Get the current address area size */
      LulAddrAreaSize = 
                  Fee_GaaAddrAreaConfig[Fee_GusCurrAddrAreaId].pSubAddrArea[LusSubAddrAreaIndex].ulAddrAreaSize;

      Fee_GulJobDataAddr = LulStartAreaAddr + LulAddrAreaSize;                                                          /* PRQA S 3383 # JV-01 */

      /* Assign the current data address area */
      Fee_GaaAddrAreaInfo[Fee_GusCurrAddrAreaId].ulCurrDataAreaAddr = Fee_GulJobDataAddr;
      #endif

      /* Read the first block Header */
      LenReturnValue = Fee_InitReadBlockHeader();
    }
  }

  /* Return value */
  return (LenReturnValue);
}
#define FEE_STOP_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name             : Fee_InitReadBlockHeader
**
** Service ID                : None
**
** Description               : This function is to support read the header of block
**
** Sync/Async                : Asynchronous
**
** Reentrancy                : Non Reentrant
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : MemIf_JobResultType
**                             MEMIF_JOB_PENDING: The last job is waiting for execution or currently being executed.
**                             MEMIF_JOB_FAILED: The last job has not been finished successfully (it failed).
**
** Preconditions             : None
**
** Global Variables Used     : Fee_GenRequestedCmd, Fee_GaaDataBuffer
**
** Function(s) invoked       : Fee_InternalRead
**
** Registers Used            : None
**
** Reference ID              : FEE_DUD_ACT_029, FEE_DUD_ACT_029_GBL001
***********************************************************************************************************************/
#define FEE_START_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
STATIC FUNC(MemIf_JobResultType, FEE_PRIVATE_CODE) Fee_InitReadBlockHeader(void)
{
  MemIf_JobResultType LenReturnValue;

  /* Read the header of block: */
  LenReturnValue = Fee_InternalRead(Fee_GulJobRefAreaAddr, (P2VAR(uint8, AUTOMATIC, FEE_APPL_DATA)) Fee_GaaDataBuffer,  /* PRQA S 0751, 3432 # JV-01, JV-01 */
                                                              FEE_BLOCK_OVERHEAD - FEE_HEADER_INFOR_BLOCK_OFFSET_ADDR);
  /* Async proceed by main function */
  Fee_GenRequestedCmd = FEE_CMD_INIT_SCAN_BLOCK_HEADER_PARSE;
  return (LenReturnValue);
}
#define FEE_STOP_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name             : Fee_InitEraseAddrArea
**
** Service ID                : None
**
** Description               : This function is to support erase the page in Init when the current is not satified
**
** Sync/Async                : Asynchronous
**
** Reentrancy                : Non Reentrant
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : MemIf_JobResultType
**                             MEMIF_JOB_OK: The last job has been finished successfully.
**                             MEMIF_JOB_PENDING: The last job is waiting for execution or currently being executed.
**                             MEMIF_JOB_FAILED: The last job has not been finished successfully (it failed).
**
** Preconditions             : None
**
** Global Variables Used     : Fee_GaaAddrAreaConfig[], Fee_GenRequestedCmd, Fee_GblWaitMemAccResult
**
** Function(s) invoked       : MemAcc_Erase
**
** Registers Used            : None
**
** Reference ID              : FEE_DUD_ACT_030, FEE_DUD_ACT_030_GBL001, FEE_DUD_ACT_030_GBL002
***********************************************************************************************************************/
#define FEE_START_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
STATIC FUNC(MemIf_JobResultType, FEE_PRIVATE_CODE) Fee_InitEraseAddrArea(void)
{
  MemIf_JobResultType LenReturnValue;
  Std_ReturnType LucExtReturnValue;

  MemAcc_AddressType LulStartAreaAddr;
  MemAcc_LengthType LulAddrAreaSize;

  MemAcc_AddressAreaIdType LusAreaId;

  /* Get the configured start address area */
  LulStartAreaAddr =Fee_GaaAddrAreaConfig[Fee_GusCurrAddrAreaId].pSubAddrArea[Fee_GusCurrSubAddrAreaId].ulStartAreaAddr;

  /* Get the configured size of address area */
  LulAddrAreaSize = Fee_GaaAddrAreaConfig[Fee_GusCurrAddrAreaId].pSubAddrArea[Fee_GusCurrSubAddrAreaId].ulAddrAreaSize;

  LusAreaId = Fee_GaaAddrAreaConfig[Fee_GusCurrAddrAreaId].usAddrAreaID;

  LucExtReturnValue = MemAcc_Erase(LusAreaId, LulStartAreaAddr, LulAddrAreaSize);

  if (E_OK == LucExtReturnValue)
  {
    /* Erasing process has been accepted */
    LenReturnValue = MEMIF_JOB_PENDING;
    /* Set checking MemAcc result flag */
    Fee_GblWaitMemAccResult = FEE_TRUE;
  }
  else
  {
    /* Erasing process has not been accepted */
    LenReturnValue = MEMIF_JOB_FAILED;
  }

  /* Schedule format Job */
  /* MemAcc_Erase/Fee_Erase -> Update Command -> Async proceed by Mainfunction */
  Fee_GenRequestedCmd = FEE_CMD_INIT_WRITE_HEADER_FORMAT;

  /* Return value */
  return (LenReturnValue);
}
#define FEE_STOP_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name             : Fee_JobInitScanBlockHeaderParse
**
** Service ID                : None
**
** Description               : This function is to support read the header of block
**
** Sync/Async                : Asynchronous
**
** Reentrancy                : Non Reentrant
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : MemIf_JobResultType
**                             MEMIF_JOB_OK: The last job has been finished successfully.
**                             MEMIF_JOB_PENDING: The last job is waiting for execution or currently being executed.
**                             MEMIF_JOB_FAILED: The last job has not been finished successfully (it failed).
**
** Preconditions             : None
**
** Global Variables Used     : Fee_GstVar, Fee_GaaAddrAreaInfo[], Fee_GpBlockConfig[], Fee_GaaBlockInfo[],
**                           : Fee_GusCurrAddrAreaId, Fee_GaaDataBuffer
**
** Function(s) invoked       : Fee_GetBlockDataHeaderInfo, Fee_InitEraseAddrArea
**                             Fee_InitReadBlockHeader, Fee_InitScanAddrArea
**                             Fee_GetBlockIndex, Fee_AlignToVirtualPageSize
**
** Registers Used            : None
**
** Reference ID              : FEE_DUD_ACT_031, FEE_DUD_ACT_031_GBL001, FEE_DUD_ACT_031_GBL002
** Reference ID              : FEE_DUD_ACT_031_GBL003, FEE_DUD_ACT_031_GBL004, FEE_DUD_ACT_031_GBL005
** Reference ID              : FEE_DUD_ACT_031_GBL006, FEE_DUD_ACT_031_GBL007, FEE_DUD_ACT_031_GBL008
** Reference ID              : FEE_DUD_ACT_031_GBL009, FEE_DUD_ACT_031_GBL010, FEE_DUD_ACT_031_GBL011
** Reference ID              : FEE_DUD_ACT_031_GBL012, FEE_DUD_ACT_031_GBL013
***********************************************************************************************************************/
#define FEE_START_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
STATIC FUNC(MemIf_JobResultType, FEE_PRIVATE_CODE) Fee_JobInitScanBlockHeaderParse(void)
{
  /* Declaring the return value */
  MemIf_JobResultType LenReturnValue;
  Fee_BlockStatusType LenBlockStatus;

  Fee_BlockHeaderType LstBlockInfor;

  uint16 LusBlockIndex;
  uint8 LucIndexAddrArea;
  #if (FEE_WRITE_DATA_IN_REVERT_DIRECTION == STD_OFF)
  uint16 LusAlignedBlockSize;
  #endif /* #if (FEE_WRITE_DATA_IN_REVERT_DIRECTION == STD_OFF) */

  /* Deserialize block header from read buffer */
  LenBlockStatus = Fee_GetBlockDataHeaderInfo(&LstBlockInfor, (P2CONST(uint8, AUTOMATIC, FEE_APPL_CONST))               /* PRQA S 0751 # JV-01 */
                                                                                                    Fee_GaaDataBuffer);

  if (FEE_BLOCK_HEADER_INVALID == LenBlockStatus)
  {
    /* Update the ref address of block header */
    #if (FEE_WRITE_DATA_IN_REVERT_DIRECTION == STD_ON)
    Fee_GulJobRefAreaAddr = Fee_GulJobRefAreaAddr + FEE_BLOCK_OVERHEAD;                                                 /* PRQA S 3383 # JV-01 */

    /* Update the block header address */
    Fee_GaaAddrAreaInfo[Fee_GusCurrAddrAreaId].ulCurrHeaderAreaAddr = Fee_GulJobRefAreaAddr;

    /* Move to the next block header */
    LenReturnValue = Fee_InitReadBlockHeader();
    #else
    /* Erase the address area due to data have been INVALID -> Cannot continue to scan the other data */
    Fee_GusCurrSubAddrAreaId = Fee_GaaAddrAreaInfo[Fee_GusCurrAddrAreaId].usSubAddrAreaIndex;
    /* No Address Area found -> Erase and Format the first address area one */
    LenReturnValue = Fee_InitEraseAddrArea();
    #endif /* #if (FEE_WRITE_DATA_IN_REVERT_DIRECTION == STD_OFF) */
  }
  else if (FEE_BLOCK_HEADER_BLANK == LenBlockStatus)
  {
    /* End of the list, move to the next address area */
    Fee_GusCurrAddrAreaId++;                                                                                            /* PRQA S 3383 # JV-01 */

    LenReturnValue = Fee_InitScanAddrArea();
  }
  else
  {
    /* Looking for found block in the block configuration */
    LusBlockIndex = Fee_GetBlockIndex(LstBlockInfor.usFeeBlockNumber);
    if ((FEE_INVALID_BLOCK_IDX != LusBlockIndex))
    {
      LucIndexAddrArea = Fee_GaaBlockConfig[LusBlockIndex].usIndexAddrArea;                                             /* PRQA S 4461 # JV-01 */
      if ((Fee_GaaAddrAreaInfo[Fee_GusCurrAddrAreaId].usAddrAreaID
                                        == (Fee_GaaAddrAreaConfig[LucIndexAddrArea].usAddrAreaID)) &&
      (LstBlockInfor.usBlockSize == Fee_GpBlockConfig[LusBlockIndex].usBlockSize))
      {
        /* Update for Block */
        /* Update status of block */
        Fee_GaaBlockInfo[LusBlockIndex].enBlockStatus = LenBlockStatus;

        /* Update the block header data address */
        Fee_GaaBlockInfo[LusBlockIndex].ulBlockRefAddr = Fee_GulJobRefAreaAddr;

        /* Update Data Block Address */
        Fee_GaaBlockInfo[LusBlockIndex].ulBlockDataAddr = LstBlockInfor.ulBlockDataAddr;

        /* Update W/E cycle of block */
        Fee_GaaBlockInfo[LusBlockIndex].ulBlockWECycle = LstBlockInfor.ulWECycles;
      }
    }

    /* Move on to next block header */
    #if (FEE_WRITE_DATA_IN_REVERT_DIRECTION == STD_ON)
    /* Update the current Data Address Area Address */
    Fee_GaaAddrAreaInfo[Fee_GusCurrAddrAreaId].ulCurrDataAreaAddr = LstBlockInfor.ulBlockDataAddr;

    /* Update the current Job Ref Addr */
    Fee_GulJobRefAreaAddr = Fee_GulJobRefAreaAddr + FEE_BLOCK_OVERHEAD;                                                 /* PRQA S 3383 # JV-01 */
    #else
    /* Calculate the alignment of the block size. */
    LusAlignedBlockSize = Fee_AlignToVirtualPageSize(LstBlockInfor.usBlockSize);

    /* Update the current Job Ref Addr */
    Fee_GulJobRefAreaAddr = Fee_GulJobRefAreaAddr + FEE_BLOCK_OVERHEAD + LusAlignedBlockSize;                           /* PRQA S 3383 # JV-01 */
    #endif /* #if (FEE_WRITE_DATA_IN_REVERT_DIRECTION == STD_ON) */

    /* Update the block header address */
    Fee_GaaAddrAreaInfo[Fee_GusCurrAddrAreaId].ulCurrHeaderAreaAddr = Fee_GulJobRefAreaAddr;
    /* Read the next header */
    LenReturnValue = Fee_InitReadBlockHeader();
  }

  /* Update the return value */
  return (LenReturnValue);
}
#define FEE_STOP_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name             : Fee_JobInitWriteHeaderFormat
**
** Service ID                : None
**
** Description               : This function is to support write a new header after erase/format page
**
** Sync/Async                : Asynchronous
**
** Reentrancy                : Non Reentrant
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : MemIf_JobResultType
**                             MEMIF_JOB_PENDING: The last job is waiting for execution or currently being executed.
**                             MEMIF_JOB_FAILED: The last job has not been finished successfully (it failed).
**
** Preconditions             : None
**
** Global Variables Used     : Fee_GaaAddrAreaConfig[], Fee_GenRequestedCmd, Fee_GaaDataBuffer
**
** Function(s) invoked       : Fee_PrepareHeaderAddrArea, Fee_PrepareHeaderFlag
**                             Fee_InternalWrite
**
** Registers Used            : None
**
** Reference ID              : FEE_DUD_ACT_032, FEE_DUD_ACT_032_GBL001
***********************************************************************************************************************/
#define FEE_START_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
STATIC FUNC(MemIf_JobResultType, FEE_PRIVATE_CODE) Fee_JobInitWriteHeaderFormat(void)
{
  /* Declaring the return value */
  MemIf_JobResultType LenReturnValue;
  /* Local structure for Addr Area Header */
  Fee_AddrAreaHeaderType LstAddrAreaHeader;

  /* Get the configured start address of address area */
  LstAddrAreaHeader.ulStartAreaAddr = 
                    Fee_GaaAddrAreaConfig[Fee_GusCurrAddrAreaId].pSubAddrArea[Fee_GusCurrSubAddrAreaId].ulStartAreaAddr;

  /* Get the current page size */
  LstAddrAreaHeader.ulAddrAreaSize = 
                    Fee_GaaAddrAreaConfig[Fee_GusCurrAddrAreaId].pSubAddrArea[Fee_GusCurrSubAddrAreaId].ulAddrAreaSize;

  /* Assign the first index for first address area */
  LstAddrAreaHeader.usAddrAreaID = Fee_GaaAddrAreaConfig[Fee_GusCurrAddrAreaId].usAddrAreaID + FEE_ONE;

  /* Data direction in the memory */
  LstAddrAreaHeader.ulConfigDirection = FEE_DATA_DIRECTION;

  /* Initialize address area header: Address area ID - Start Address - Address Area Size */
  Fee_PrepareHeaderAddrArea(&LstAddrAreaHeader, (P2VAR(uint8, AUTOMATIC, FEE_APPL_DATA)) Fee_GaaDataBuffer);            /* PRQA S 0751, 3432 # JV-01, JV-01 */

  /* Initilaize address area status */                     
  Fee_PrepareHeaderFlag(( (P2VAR(uint8, AUTOMATIC, FEE_APPL_DATA)) Fee_GaaDataBuffer +                                  /* PRQA S 0488, 0751, 3432 # JV-01, JV-01, JV-01 */
                        (FEE_PAGE_OVERHEAD - FEE_VALID_ADDRESS_AREA_OFFSET_ADDR)), FEE_VALIDATED_VALUE);

  LenReturnValue = Fee_InternalWrite(LstAddrAreaHeader.ulStartAreaAddr, (P2CONST(uint8, AUTOMATIC, FEE_APPL_CONST))     /* PRQA S 0751 # JV-01 */
                                           Fee_GaaDataBuffer, FEE_PAGE_OVERHEAD - FEE_INVALID_ADDRESS_AREA_OFFSET_ADDR);

  /* Schedule format Job -> Async proceed by Mainfunction */
  Fee_GenRequestedCmd = FEE_CMD_INIT_WRITE_HEADER_FORMAT_DONE;
  return (LenReturnValue);
}
#define FEE_STOP_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name             : Fee_JobInitWriteHeaderFormatDone
**
** Service ID                : None
**
** Description               : This function is to support serial address area data header
**
** Sync/Async                : Asynchronous
**
** Reentrancy                : Non Reentrant
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : MemIf_JobResultType
**                             MEMIF_JOB_OK: The last job has been finished successfully.
**                             MEMIF_JOB_PENDING: The last job is waiting for execution or currently being executed.
**                             MEMIF_JOB_FAILED: The last job has not been finished successfully (it failed).
**
** Preconditions             : None
**
** Global Variables Used     : Fee_GaaAddrAreaConfig[], Fee_GaaAddrAreaInfo[], Fee_GusCurrAddrAreaId
**
** Function(s) invoked       : Fee_InitScanAddrArea
**
** Registers Used            : None
**
** Reference ID              : FEE_DUD_ACT_033, FEE_DUD_ACT_033_GBL001, FEE_DUD_ACT_033_GBL002
** Reference ID              : FEE_DUD_ACT_033_GBL003, FEE_DUD_ACT_033_GBL004
***********************************************************************************************************************/
#define FEE_START_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
STATIC FUNC(MemIf_JobResultType, FEE_PRIVATE_CODE) Fee_JobInitWriteHeaderFormatDone(void)
{
  /* Declaring the return value */
  MemIf_JobResultType LenReturnValue;
  MemAcc_AddressType LulStartAreaAddr;
  #if (FEE_WRITE_DATA_IN_REVERT_DIRECTION == STD_ON)
  MemAcc_LengthType LulAddrAreaSize;
  #endif /* #if (FEE_WRITE_DATA_IN_REVERT_DIRECTION == STD_ON) */

  /* Get the configure start address off Address Area */
  LulStartAreaAddr =Fee_GaaAddrAreaConfig[Fee_GusCurrAddrAreaId].pSubAddrArea[Fee_GusCurrSubAddrAreaId].ulStartAreaAddr;
  /* After finishing writing header format for Erasing process */
  Fee_GaaAddrAreaInfo[Fee_GusCurrAddrAreaId].usAddrAreaID = Fee_GaaAddrAreaConfig[Fee_GusCurrAddrAreaId].usAddrAreaID;
  Fee_GaaAddrAreaInfo[Fee_GusCurrAddrAreaId].usSubAddrAreaIndex = Fee_GusCurrSubAddrAreaId;

  /* Initialize block header address */
  Fee_GaaAddrAreaInfo[Fee_GusCurrAddrAreaId].ulCurrHeaderAreaAddr = LulStartAreaAddr + FEE_PAGE_OVERHEAD;               /* PRQA S 3383 # JV-01 */

  #if (FEE_WRITE_DATA_IN_REVERT_DIRECTION == STD_ON)
  /* Get the current page size of address area */
  LulAddrAreaSize = 
          Fee_GaaAddrAreaConfig[Fee_GusCurrAddrAreaId].pSubAddrArea[Fee_GusCurrSubAddrAreaId].ulAddrAreaSize;

  /* Initialize block data address */
  Fee_GaaAddrAreaInfo[Fee_GusCurrAddrAreaId].ulCurrDataAreaAddr = LulStartAreaAddr + LulAddrAreaSize;                   /* PRQA S 3383 # JV-01 */
  #endif /* #if (FEE_WRITE_DATA_IN_REVERT_DIRECTION == STD_ON) */
  /* Move to next address area */
  Fee_GusCurrAddrAreaId++;                                                                                              /* PRQA S 3383 # JV-01 */
  /* Scan next address area */
  LenReturnValue = Fee_InitScanAddrArea();

  /* Return value */
  return (LenReturnValue);
}
#define FEE_STOP_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
**                                       Internal function: Fee_Read()                                                **
***********************************************************************************************************************/
/***********************************************************************************************************************
** Function Name             : Fee_JobReadMain
**
** Service ID                : None
**
** Description               : This function is the main function of API Fee_Read, asynchronous from
**                             Fee_MainFunction()
**
** Sync/Async                : Asynchronous
**
** Reentrancy                : Non Reentrant
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : MemIf_JobResultType
**                             MEMIF_JOB_PENDING: The last job is waiting for execution or currently being executed.
**                             MEMIF_JOB_FAILED: The last job has not been finished successfully (it failed).
**                             MEMIF_BLOCK_INVALID: The requested block has been invalidated, the requested read
**                                                  operation can not be performed.
**                             MEMIF_BLOCK_INCONSISTENT: The requested block is inconsistent, it may contain
**                                                       corrupted data.
**
** Preconditions             : None
**
** Global Variables Used     : Fee_GpBlockConfig[], Fee_GaaAddrAreaInfo[], Fee_GaaBlockInfo[], Fee_GstVar,
**                           : Fee_GenRequestedCmd
**
** Function(s) invoked       : Fee_InternalRead
**
** Registers Used            : None
**
** Reference ID              : FEE_DUD_ACT_034, FEE_DUD_ACT_034_GBL001, FEE_DUD_ACT_034_GBL002
** Reference ID              : FEE_DUD_ACT_034_GBL003
***********************************************************************************************************************/
#define FEE_START_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(MemIf_JobResultType, FEE_PRIVATE_CODE) Fee_JobReadMain(void)
{
  MemIf_JobResultType LenReturnValue;

  Fee_BlockStatusType LenBlockStatus;
  MemAcc_AddressType LuBlockAddress;
  uint16 LusAlignLengthRead;

  /* Initialize the return value to MEMIF_JOB_FAILED */
  LenReturnValue = MEMIF_JOB_FAILED;
  /* Update the current Address/Sub-Address area of block */
  Fee_GusCurrAddrAreaId = Fee_GpBlockConfig[Fee_GstVar.usBlockIndex].usIndexAddrArea;
  Fee_GusCurrSubAddrAreaId = Fee_GaaAddrAreaInfo[Fee_GusCurrAddrAreaId].usSubAddrAreaIndex;
  /* SWS_Fee_00021 */
  /* Calculate address */
  LuBlockAddress = Fee_GaaBlockInfo[Fee_GstVar.usBlockIndex].ulBlockDataAddr;

  /* Get the status of block */
  LenBlockStatus = Fee_GaaBlockInfo[Fee_GstVar.usBlockIndex].enBlockStatus;

  /* Check for the current Block Status */
  if (FEE_BLOCK_VALID == LenBlockStatus)
  {
    /* ECUC_Fee_00156 */
    if (FEE_ZERO == (Fee_GstVar.usBlockLength % FEE_MIN_READ_PAGE_SIZE))
    {
      LusAlignLengthRead = (uint16)Fee_GstVar.usBlockLength;
    }
    else
    {
      LusAlignLengthRead = ((uint16)(Fee_GstVar.usBlockLength / FEE_MIN_READ_PAGE_SIZE) +
                                                                      (uint16)FEE_ONE) * (uint16)FEE_MIN_READ_PAGE_SIZE;
    }

    /* Request to underlying module */
    LenReturnValue = Fee_InternalRead(LuBlockAddress + Fee_GstVar.usBlockOffset, Fee_GstVar.pJobReadDatatPtr,           /* PRQA S 3383 # JV-01 */
                                                                                                    LusAlignLengthRead);
  }
  else if (FEE_BLOCK_INVALID == LenBlockStatus)
  {
    /* Block is invalid */
    LenReturnValue = MEMIF_BLOCK_INVALID;
  }
  else
  {
    /* SWS_Fee_00023 */
    if (FEE_BLOCK_INCONSISTENT == LenBlockStatus)
    {
      LenReturnValue = MEMIF_BLOCK_INCONSISTENT;
    }
  }
  /* There is no consecutive job to schedule */
  Fee_GenRequestedCmd = FEE_CMD_READ_DONE;
  /* Return value */
  return(LenReturnValue);
}
#define FEE_STOP_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name             : Fee_JobReadDone
**
** Service ID                : None
**
** Description               : This function to support for remark the read process is done
**
** Sync/Async                : Asynchronous
**
** Reentrancy                : Non Reentrant
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : MemIf_JobResultType
**                             MEMIF_JOB_OK: The last job has been finished successfully.
**
** Preconditions             : None
**
** Global Variables Used     : Fee_GenRequestedCmd
**
** Function(s) invoked       : None
**
** Registers Used            : None
**
** Reference ID              : FEE_DUD_ACT_035, FEE_DUD_ACT_035_GBL001
***********************************************************************************************************************/
#define FEE_START_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(MemIf_JobResultType, FEE_PRIVATE_CODE) Fee_JobReadDone(void)
{
  MemIf_JobResultType LenReturnValue;

  LenReturnValue = MEMIF_JOB_OK;
  /* Update the schedule is No pending Job */
  Fee_GenRequestedCmd = FEE_CMD_NO_PENDING;
  Fee_GstVar.enCmdJobRequest = FEE_CMD_NO_PENDING;
  /* Return value */
  return LenReturnValue;
}
#define FEE_STOP_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
**                                       Internal function: Fee_Write()                                               **
***********************************************************************************************************************/
/***********************************************************************************************************************
** Function Name             : Fee_JobWriteMain
**
** Service ID                : None
**
** Description               : This function is the main function of API Fee_Write, asynchronous from
**                             Fee_Write()
**
** Sync/Async                : Asynchronous
**
** Reentrancy                : Non Reentrant
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : MemIf_JobResultType
**                             MEMIF_JOB_OK: The last job has been finished successfully.
**                             MEMIF_JOB_PENDING: The last job is waiting for execution or currently being executed.
**                             MEMIF_JOB_FAILED: The last job has not been finished successfully (it failed).
**
** Preconditions             : None
**
** Global Variables Used     : Fee_GpBlockConfig[], Fee_GaaAddrAreaInfo[], Fee_GaaBlockInfo[], Fee_GstVar
**
** Function(s) invoked       : Fee_JobWriteHeaderData
**
** Registers Used            : None
**
** Reference ID              : FEE_DUD_ACT_036, FEE_DUD_ACT_036_GBL001, FEE_DUD_ACT_036_GBL002
** Reference ID              : FEE_DUD_ACT_036_GBL003
***********************************************************************************************************************/
#define FEE_START_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(MemIf_JobResultType, FEE_PRIVATE_CODE) Fee_JobWriteMain(void)
{
  /* Declaring the return value */
  MemIf_JobResultType LenReturnValue;
  /* Calculate the address area that block belong to */
  Fee_GusCurrAddrAreaId = Fee_GpBlockConfig[Fee_GstVar.usBlockIndex].usIndexAddrArea;
  Fee_GusCurrSubAddrAreaId = Fee_GaaAddrAreaInfo[Fee_GusCurrAddrAreaId].usSubAddrAreaIndex;

  /* SWS_Fee_00153: 
  When a block write operation is started, the FEE module shall mark the corresponding block as corrupted. */
  Fee_GaaBlockInfo[Fee_GstVar.usBlockIndex].enBlockStatus = FEE_BLOCK_INCONSISTENT;
  /* Invoke the internal function to support write header of block */
  LenReturnValue = Fee_JobWriteHeaderData();

  /* Return value */
  return LenReturnValue;
}
#define FEE_STOP_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name             : Fee_JobWriteHeaderData
**
** Service ID                : None
**
** Description               : This function to support write not immediate block data
**
** Sync/Async                : Asynchronous
**
** Reentrancy                : Non Reentrant
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : MemIf_JobResultType
**                             MEMIF_JOB_OK: The last job has been finished successfully.
**                             MEMIF_JOB_PENDING: The last job is waiting for execution or currently being executed.
**                             MEMIF_JOB_FAILED: The last job has not been finished successfully (it failed).
**
** Preconditions             : None
**
** Global Variables Used     : Fee_GaaAddrAreaInfo[], Fee_GaaAddrAreaConfig[], Fee_GpBlockConfig[], Fee_GaaDataBuffer,
**                             Fee_enPreviousRequestCmd, Fee_GulJobRefAreaAddr, Fee_GulJobDataAddr, 
**                             Fee_GusCurrAddrAreaId, Fee_GusCurrSubAddrAreaId, Fee_GenModuleState, Fee_GenRequestedCmd
**
** Function(s) invoked       : Fee_AlignToVirtualPageSize, Fee_JobSwapPrepareNextAddressArea
**                             Fee_PrepareHeaderBlockData, Fee_InternalWrite
**
** Registers Used            : None
**
** Reference ID              : FEE_DUD_ACT_037, FEE_DUD_ACT_037_GBL001, FEE_DUD_ACT_037_GBL002
** Reference ID              : FEE_DUD_ACT_037_GBL006, FEE_DUD_ACT_037_GBL007, FEE_DUD_ACT_037_GBL011
** Reference ID              : FEE_DUD_ACT_037_GBL012, FEE_DUD_ACT_037_GBL014
***********************************************************************************************************************/
/* Description: This function support for both immediate and non immediate block data */
/* For 
+ Immediate block data: The condition check the remaining space to support write the normal block data If user does not
invoke Fee_EraseImmediateBlockData first, to support pre-allocate the free space for immdefiate block data.
+ None immediate block data: Support normally                                                                         */
#define FEE_START_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
STATIC FUNC(MemIf_JobResultType, FEE_PRIVATE_CODE) Fee_JobWriteHeaderData(void)
{
  /* Declare the return value */
  MemIf_JobResultType LenReturnValue;

  uint16 LusAlignedBlockSize;

  Fee_BlockHeaderType LpBlockHeaderInfo;

  MemAcc_AddressType LulBlockRefAddr;
  MemAcc_AddressType LulRemainSpaceSize;
  #if (FEE_WRITE_DATA_IN_REVERT_DIRECTION == STD_OFF)
  MemAcc_AddressType LulStartAreaAddr;
  MemAcc_AddressType LulAddrAreaSize;
  #endif /* #if (FEE_WRITE_DATA_IN_REVERT_DIRECTION == STD_OFF) */

  /* Get the current address */
  LulBlockRefAddr = Fee_GaaAddrAreaInfo[Fee_GusCurrAddrAreaId].ulCurrHeaderAreaAddr;

  #if (FEE_WRITE_DATA_IN_REVERT_DIRECTION == STD_ON)
  /* Remain address = current ref address - current data address */
  LulRemainSpaceSize = Fee_GaaAddrAreaInfo[Fee_GusCurrAddrAreaId].ulCurrDataAreaAddr - LulBlockRefAddr;                 /* PRQA S 3383 # JV-01 */
  #else

  /* Get the configure start address off Address Area */
  LulStartAreaAddr =Fee_GaaAddrAreaConfig[Fee_GusCurrAddrAreaId].pSubAddrArea[Fee_GusCurrSubAddrAreaId].ulStartAreaAddr;

  /* Get the current address area size */
  LulAddrAreaSize = Fee_GaaAddrAreaConfig[Fee_GusCurrAddrAreaId].pSubAddrArea[Fee_GusCurrSubAddrAreaId].ulAddrAreaSize;

  /* Calculate the remaining size */
  LulRemainSpaceSize = LulStartAreaAddr + LulAddrAreaSize - LulBlockRefAddr;                                            /* PRQA S 3383, 3384 # JV-01, JV-01 */
  #endif /* #if (FEE_WRITE_DATA_IN_REVERT_DIRECTION == STD_ON) */

  /* Get the configured block size */
  LpBlockHeaderInfo.usBlockSize = Fee_GpBlockConfig[Fee_GstVar.usBlockIndex].usBlockSize;

  /* Calculate the align value */
  LusAlignedBlockSize = Fee_AlignToVirtualPageSize(LpBlockHeaderInfo.usBlockSize);

  /* Check with align block size of block size value - Not check with block Size value */
  if (LulRemainSpaceSize < (((uint32)LusAlignedBlockSize) + (((uint32)3)*((uint32)FEE_BLOCK_OVERHEAD))))                /* PRQA S 3383 # JV-01 */                                                                            
  {
    /* There is no remaining space in this address area */
    Fee_enPreviousRequestCmd = FEE_CMD_SWAP_WRITE_HEADER_DATA;
    LenReturnValue = Fee_JobSwapPrepareNextAddressArea();
  }
  else
  {
    /* Update the schedule is No pending Job after finish swap feature */
    if (FEE_CMD_SWAP_WRITE_HEADER_DATA == Fee_enPreviousRequestCmd)
    {
      Fee_enPreviousRequestCmd = FEE_CMD_NO_PENDING;
    }

    /* Get the block ID */
    LpBlockHeaderInfo.usFeeBlockNumber = Fee_GpBlockConfig[Fee_GstVar.usBlockIndex].usFeeBlockNumber;

    #if (FEE_WRITE_DATA_IN_REVERT_DIRECTION == STD_ON)
    LpBlockHeaderInfo.ulBlockDataAddr = 
                                  Fee_GaaAddrAreaInfo[Fee_GusCurrAddrAreaId].ulCurrDataAreaAddr - LusAlignedBlockSize;  /* PRQA S 3383 # JV-01 */
    #else
    /* Calculate the data address */
    LpBlockHeaderInfo.ulBlockDataAddr = LulBlockRefAddr + FEE_BLOCK_OVERHEAD;                                           /* PRQA S 3383 # JV-01 */
    #endif /* #if (FEE_WRITE_DATA_IN_REVERT_DIRECTION == STD_ON) */

    /* Increase for WE cycle */
    LpBlockHeaderInfo.ulWECycles = (uint32) Fee_GaaBlockInfo[Fee_GstVar.usBlockIndex].ulBlockWECycle + FEE_ONE;         /* PRQA S 3383 # JV-01 */

    /* Serial block data header */
    Fee_PrepareHeaderBlockData(&LpBlockHeaderInfo, (P2VAR(uint8, AUTOMATIC, FEE_APPL_DATA)) Fee_GaaDataBuffer);         /* PRQA S 2976, 0751, 3432 # JV-01, JV-01, JV-01 */
    /* Update the current header address and data address */
    Fee_GulJobRefAreaAddr = LulBlockRefAddr;
    Fee_GulJobDataAddr = LpBlockHeaderInfo.ulBlockDataAddr;
    /* Write header data */
    LenReturnValue = Fee_InternalWrite(LulBlockRefAddr, (P2CONST(uint8, AUTOMATIC, FEE_APPL_CONST)) Fee_GaaDataBuffer,  /* PRQA S 0751 # JV-01 */
                                                                                         FEE_VALID_BLOCK_OFFSET_ADDR);
    /* Update CMD Request to implement for Fee_Write data for block number */
    /* Fee_Write -> Update Command -> Async proceed by Mainfunction */
    Fee_GenRequestedCmd = FEE_CMD_WRITE_BLOCK_DATA;
  }

  /* Return value */
  return (LenReturnValue);
}
#define FEE_STOP_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name             : Fee_JobWriteBlockData
**
** Service ID                : None
**
** Description               : This function to support for write block data
**
** Sync/Async                : Asynchronous
**
** Reentrancy                : Non Reentrant
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : MemIf_JobResultType
**                             MEMIF_JOB_PENDING: The last job is waiting for execution or currently being executed.
**                             MEMIF_JOB_FAILED: The last job has not been finished successfully (it failed).
**
** Preconditions             : None
**
** Global Variables Used     : Fee_GaaAddrAreaInfo[], Fee_GusCurrAddrAreaId, Fee_GpBlockConfig, Fee_GstVar
**                             Fee_GenRequestedCmd, Fee_GaaDataBuffer
**
** Function(s) invoked       : Fee_AlignToVirtualPageSize, Fee_WriteData2AlignPageSize
**                             Fee_InternalWrite
**
** Registers Used            : None
**
** Reference ID              : FEE_DUD_ACT_038, FEE_DUD_ACT_038_GBL001, FEE_DUD_ACT_038_GBL007
** Reference ID              : FEE_DUD_ACT_038_GBL009, FEE_DUD_ACT_038_GBL011
***********************************************************************************************************************/
#define FEE_START_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(MemIf_JobResultType, FEE_PRIVATE_CODE) Fee_JobWriteBlockData(void)
{
  /* Declare the return value */
  MemIf_JobResultType LenReturnValue;

  uint16 LusBlockSize;
  uint16 LulBlockDataSize;
  uint16 LusAlignedBlockSize;

  const uint8* LpDataBufferr;
  const uint8 *LpWriteDataBuffer;

  MemAcc_AddressType LulBlockDataAddr;
  /* After successful writing header for block */
  /* Update the header and data address area */
  Fee_GaaAddrAreaInfo[Fee_GusCurrAddrAreaId].ulCurrHeaderAreaAddr =
                                Fee_GaaAddrAreaInfo[Fee_GusCurrAddrAreaId].ulCurrHeaderAreaAddr + FEE_BLOCK_OVERHEAD;   /* PRQA S 3383 # JV-01 */
  /* Get the configured block size */
  LusBlockSize = Fee_GpBlockConfig[Fee_GstVar.usBlockIndex].usBlockSize;

  /* Calculate the align value */
  LusAlignedBlockSize = Fee_AlignToVirtualPageSize(LusBlockSize);

  #if (FEE_WRITE_DATA_IN_REVERT_DIRECTION == STD_ON)
  LulBlockDataAddr = Fee_GaaAddrAreaInfo[Fee_GusCurrAddrAreaId].ulCurrDataAreaAddr - LusAlignedBlockSize;               /* PRQA S 3383 # JV-01 */
  #else
  /* Define the address of Fee block data */
  LulBlockDataAddr = Fee_GaaAddrAreaInfo[Fee_GusCurrAddrAreaId].ulCurrHeaderAreaAddr;
  #endif /* #if (FEE_WRITE_DATA_IN_REVERT_DIRECTION == STD_ON) */

  /* Get the write data buffer */
  LpDataBufferr = Fee_GstVar.pJobWriteDatatPtr;

  /* Check alignmnet of block size */
  if (FEE_ZERO == (LusBlockSize % FEE_VIRTUAL_PAGE_SIZE))
  {
    /* Copy buffer data to local pointer */
    LpWriteDataBuffer = Fee_GstVar.pJobWriteDatatPtr;

    /* Copy the block size to local variable */
    LulBlockDataSize = LusBlockSize;
    /* Update Command -> Async proceed by Mainfunction */
    Fee_GenRequestedCmd = FEE_CMD_WRITE_VALIDATE_BLOCK;
  }
  else
  {
    if (LusBlockSize < FEE_VIRTUAL_PAGE_SIZE)
    {
      /* Buffer data is less than FEE_VIRTUAL_PAGE_SIZE -> Minimumsize is FEE_VIRTUAL_PAGE_SIZE */
      Fee_WriteData2AlignPageSize(LpDataBufferr, (P2VAR(uint8, AUTOMATIC, FEE_APPL_DATA)) Fee_GaaDataBuffer,            /* PRQA S 0751, 3432 # JV-01, JV-01 */
                                                                                                  LusBlockSize);

      /* Copy buffer data to local pointer */
      LpWriteDataBuffer = (P2CONST(uint8, AUTOMATIC, FEE_APPL_CONST)) Fee_GaaDataBuffer;                                /* PRQA S 0751 # JV-01 */

      /* Assign the minimum value to data size of write */
      LulBlockDataSize = FEE_VIRTUAL_PAGE_SIZE;
      /* Update Command -> Async proceed by Mainfunction */
      Fee_GenRequestedCmd = FEE_CMD_WRITE_VALIDATE_BLOCK;
    }
    else
    {
      /* Copy write data ptr to local ptr */
      LpWriteDataBuffer = Fee_GstVar.pJobWriteDatatPtr;

      /* Calculate the actual write size */
      LulBlockDataSize = LusAlignedBlockSize - FEE_VIRTUAL_PAGE_SIZE;                                                   /* PRQA S 3383 # JV-01 */
      /* Update Command -> Async proceed by Mainfunction */
      Fee_GenRequestedCmd = FEE_CMD_WRITE_UNALIGNED_BLOCK;
    }
  }

  /* The block size is aligned with FEE_VIRTUAL_PAGE_SIZE and No need to update data of block */
  LenReturnValue = Fee_InternalWrite(LulBlockDataAddr, LpWriteDataBuffer, LulBlockDataSize);

  /* Return value */
  return LenReturnValue;
}
#define FEE_STOP_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name             : Fee_WriteUnalignedBlockData
**
** Service ID                : None
**
** Description               : This function to support for write unaligned block data
**
** Sync/Async                : Asynchronous
**
** Reentrancy                : Non Reentrant
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : MemIf_JobResultType
**                             MEMIF_JOB_PENDING: The last job is waiting for execution or currently being executed.
**                             MEMIF_JOB_FAILED: The last job has not been finished successfully (it failed).
**
** Preconditions             : None
**
** Global Variables Used     : Fee_GpBlockConfig[], Fee_GaaAddrAreaInfo[], Fee_GusCurrAddrAreaId, Fee_GenRequestedCmd,
**                           : Fee_GstVar, Fee_GaaDataBuffer
**
** Function(s) invoked       : Fee_AlignToVirtualPageSize, Fee_WriteData2AlignPageSize
**                             Fee_InternalWrite
**
** Registers Used            : None
**
** Reference ID              : FEE_DUD_ACT_054, FEE_DUD_ACT_054_GBL003, FEE_DUD_ACT_054_GBL004
** Reference ID              : FEE_DUD_ACT_054_GBL007
***********************************************************************************************************************/
#define FEE_START_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(MemIf_JobResultType, FEE_PRIVATE_CODE) Fee_WriteUnalignedBlockData(void)
{
  MemIf_JobResultType LenReturnValue;

  MemAcc_AddressType LulBlockDataAddr;
  uint16 LusBlockSize;
  uint16 LusAlignBlockSize;
  uint16 LusNumOfDataWritten;
  uint16 LusNumOfDataRemain;
  const uint8* LpDataBufferr;

  /* Get the write data buffer */
  LpDataBufferr = Fee_GstVar.pJobWriteDatatPtr;

  /* Get the block size */
  LusBlockSize = Fee_GpBlockConfig[Fee_GstVar.usBlockIndex].usBlockSize;

  /* Calculate the aligment of block size */
  LusAlignBlockSize = Fee_AlignToVirtualPageSize(LusBlockSize);

  /* Update the data address after successfull write for unligned data block */
  #if (FEE_WRITE_DATA_IN_REVERT_DIRECTION == STD_ON)
  Fee_GaaAddrAreaInfo[Fee_GusCurrAddrAreaId].ulCurrDataAreaAddr =
                                    Fee_GaaAddrAreaInfo[Fee_GusCurrAddrAreaId].ulCurrDataAreaAddr - LusAlignBlockSize;  /* PRQA S 3383 # JV-01 */
  #else
  Fee_GaaAddrAreaInfo[Fee_GusCurrAddrAreaId].ulCurrHeaderAreaAddr =
                                    Fee_GaaAddrAreaInfo[Fee_GusCurrAddrAreaId].ulCurrHeaderAreaAddr + LusAlignBlockSize;/* PRQA S 3383 # JV-01 */
  #endif /* #if (FEE_WRITE_DATA_IN_REVERT_DIRECTION == STD_ON) */

  /* Number of data have been written */
  LusNumOfDataWritten = LusAlignBlockSize - FEE_VIRTUAL_PAGE_SIZE;                                                      /* PRQA S 3383 # JV-01 */

  /* The remain data to write */
  LusNumOfDataRemain = LusBlockSize % FEE_VIRTUAL_PAGE_SIZE;

  /* Calculate the remain address to write for the remaining data */
  #if (FEE_WRITE_DATA_IN_REVERT_DIRECTION == STD_ON)
  LulBlockDataAddr = Fee_GaaAddrAreaInfo[Fee_GusCurrAddrAreaId].ulCurrDataAreaAddr + (uint32) LusNumOfDataWritten;      /* PRQA S 3383 # JV-01 */
  #else
  LusAlignBlockSize = Fee_AlignToVirtualPageSize(LusNumOfDataRemain);

  LulBlockDataAddr = Fee_GaaAddrAreaInfo[Fee_GusCurrAddrAreaId].ulCurrHeaderAreaAddr - LusAlignBlockSize;               /* PRQA S 3383 # JV-01 */
  #endif /* #if (FEE_WRITE_DATA_IN_REVERT_DIRECTION == STD_ON) */

  /* Copy the remain data to buffer */
  Fee_WriteData2AlignPageSize(&LpDataBufferr[LusNumOfDataWritten], (P2VAR(uint8, AUTOMATIC, FEE_APPL_DATA))             /* PRQA S 0751, 3432 # JV-01, JV-01 */
                                                                            Fee_GaaDataBuffer, LusNumOfDataRemain);              

  /* The block size is aligned with FEE_VIRTUAL_PAGE_SIZE and No need to update data of block */
  LenReturnValue = Fee_InternalWrite(LulBlockDataAddr, (P2CONST(uint8, AUTOMATIC, FEE_APPL_CONST)) Fee_GaaDataBuffer,   /* PRQA S 0751 # JV-01 */
                                                                                                FEE_VIRTUAL_PAGE_SIZE);
  /* Update Command -> Async proceed by Mainfunction */
  Fee_GenRequestedCmd = FEE_CMD_WRITE_VALIDATE_BLOCK;
  /* Return value */
  return LenReturnValue;
}
#define FEE_STOP_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name             : Fee_JobWriteValidateBlock
**
** Service ID                : None
**
** Description               : This function to support for write validate block
**
** Sync/Async                : Asynchronous
**
** Reentrancy                : Non Reentrant
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : MemIf_JobResultType
**                             MEMIF_JOB_PENDING: The last job is waiting for execution or currently being executed.
**                             MEMIF_JOB_FAILED: The last job has not been finished successfully (it failed).
**
** Preconditions             : None
**
** Global Variables Used     : Fee_GpBlockConfig[], Fee_GaaAddrAreaInfo[], Fee_GusCurrAddrAreaId, Fee_GenRequestedCmd,
**                           : Fee_GstVar, Fee_GaaBlockInfo[], Fee_GaaDataBuffer
**
** Function(s) invoked       : Fee_AlignToVirtualPageSize, Fee_PrepareHeaderFlag
**                             Fee_InternalWrite
**
** Registers Used            : None
**
** Reference ID              : FEE_DUD_ACT_039, FEE_DUD_ACT_039_GBL002, FEE_DUD_ACT_039_GBL003
** Reference ID              : FEE_DUD_ACT_039_GBL004, FEE_DUD_ACT_039_GBL006
***********************************************************************************************************************/
#define FEE_START_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(MemIf_JobResultType, FEE_PRIVATE_CODE) Fee_JobWriteValidateBlock(void)
{
  /* Declaring the return value */
  MemIf_JobResultType LenReturnValue;

  uint16 LusBlockSize;
  uint16 LusAlignedBlockSize;

  MemAcc_AddressType LulBlockValidAddr;

  /* Get the configured block size */
  LusBlockSize = Fee_GpBlockConfig[Fee_GstVar.usBlockIndex].usBlockSize;

  /* Calculate the align value with FEE_VIRTUAL_PAGE_SIZE */
  LusAlignedBlockSize = Fee_AlignToVirtualPageSize(LusBlockSize);

  /* Update the current address of address area */
  #if (FEE_WRITE_DATA_IN_REVERT_DIRECTION == STD_ON)
  if ((LusAlignedBlockSize == LusBlockSize) || (LusBlockSize < FEE_VIRTUAL_PAGE_SIZE))
  {
    Fee_GaaAddrAreaInfo[Fee_GusCurrAddrAreaId].ulCurrDataAreaAddr =
                                Fee_GaaAddrAreaInfo[Fee_GusCurrAddrAreaId].ulCurrDataAreaAddr - LusAlignedBlockSize;    /* PRQA S 3383 # JV-01 */
  }
  #else
  if ((LusAlignedBlockSize == LusBlockSize) || (LusBlockSize < FEE_VIRTUAL_PAGE_SIZE))
  {
    Fee_GaaAddrAreaInfo[Fee_GusCurrAddrAreaId].ulCurrHeaderAreaAddr =
                                Fee_GaaAddrAreaInfo[Fee_GusCurrAddrAreaId].ulCurrHeaderAreaAddr + LusAlignedBlockSize;  /* PRQA S 3383 # JV-01 */
  }
  #endif

  /* After success update data for block */
  Fee_GaaBlockInfo[Fee_GstVar.usBlockIndex].ulBlockRefAddr = Fee_GulJobRefAreaAddr;
  Fee_GaaBlockInfo[Fee_GstVar.usBlockIndex].ulBlockDataAddr = Fee_GulJobDataAddr;
  Fee_GaaBlockInfo[Fee_GstVar.usBlockIndex].ulBlockWECycle++;                                                           /* PRQA S 3383 # JV-01 */
  /* Address of Active Area Flag */
  LulBlockValidAddr = 
          Fee_GaaBlockInfo[Fee_GstVar.usBlockIndex].ulBlockRefAddr + FEE_BLOCK_OVERHEAD - FEE_VALID_BLOCK_OFFSET_ADDR;  /* PRQA S 3384, 3383 # JV-01, JV-01 */

  /* Serialize the valid flag for Block */
  Fee_PrepareHeaderFlag((P2VAR(uint8, AUTOMATIC, FEE_APPL_DATA))Fee_GaaDataBuffer, FEE_VALIDATED_VALUE);                /* PRQA S 0751, 3432 # JV-01, JV-01 */

  LenReturnValue = Fee_InternalWrite(LulBlockValidAddr, (P2CONST(uint8, AUTOMATIC, FEE_APPL_CONST)) Fee_GaaDataBuffer,  /* PRQA S 0751 # JV-01 */
                                                                                                    FEE_ONE_UNIT_SIZE);
  /* Update Command -> Async proceed by Mainfunction */
  Fee_GenRequestedCmd = FEE_CMD_WRITE_DONE;
  /* Return value */
  return LenReturnValue;
}
#define FEE_STOP_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name             : Fee_JobWriteDone
**
** Service ID                : None
**
** Description               : This function to support for remark the wite process is done
**
** Sync/Async                : Asynchronous
**
** Reentrancy                : Non Reentrant
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : MemIf_JobResultType
**                             MEMIF_JOB_OK: The last job has been finished successfully.
**
** Preconditions             : None
**
** Global Variables Used     : Fee_GaaBlockInfo[], Fee_GenRequestedCmd, Fee_GstVar
**
** Function(s) invoked       : None
**
** Registers Used            : None
**
** Reference ID              : FEE_DUD_ACT_040, FEE_DUD_ACT_040_GBL001, FEE_DUD_ACT_040_GBL002
***********************************************************************************************************************/
#define FEE_START_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(MemIf_JobResultType, FEE_PRIVATE_CODE) Fee_JobWriteDone(void)
{

  MemIf_JobResultType LenReturnValue;

  LenReturnValue = MEMIF_JOB_OK;
  /* Update the status of Block is VALID */
  /* SWS_Fee_00154 */
  Fee_GaaBlockInfo[Fee_GstVar.usBlockIndex].enBlockStatus = FEE_BLOCK_VALID;

  /* Update the schedule is No pending Job */
  Fee_GenRequestedCmd = FEE_CMD_NO_PENDING;
  Fee_GstVar.enCmdJobRequest = FEE_CMD_NO_PENDING;
  /* Return value */
  return LenReturnValue;
}
#define FEE_STOP_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
**                                    Internal feature: Swap feature                                                  **
***********************************************************************************************************************/
/***********************************************************************************************************************
** Function Name             : Fee_JobSwapPrepareNextAddressArea
**
** Service ID                : None
**
** Description               : This function to support erase the next address area for swap data
**
** Sync/Async                : Asynchronous
**
** Reentrancy                : Non Reentrant
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : MemIf_JobResultType
**                             MEMIF_JOB_OK: The last job has been finished successfully.
**                             MEMIF_JOB_PENDING: The last job is waiting for execution or currently being executed.
**                             MEMIF_JOB_FAILED: The last job has not been finished successfully (it failed).
**
** Preconditions             : None
**
** Global Variables Used     : Fee_GaaAddrAreaConfig[], Fee_GusCurrAddrAreaId, Fee_GblWaitMemAccResult
**
** Function(s) invoked       : MemAcc_Erase
**
** Registers Used            : None
**
** Reference ID              : FEE_DUD_ACT_041, FEE_DUD_ACT_041_GBL004, FEE_DUD_ACT_041_GBL006
***********************************************************************************************************************/
#define FEE_START_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
STATIC FUNC(MemIf_JobResultType, FEE_PRIVATE_CODE) Fee_JobSwapPrepareNextAddressArea(void)
{
  MemIf_JobResultType LenReturnValue;
  Std_ReturnType LucExtReturnValue;

  MemAcc_AddressType LulStartAreaAddr;
  MemAcc_LengthType LulAddrAreaSize;

  MemAcc_AddressAreaIdType LusAreaId;

  uint16 LusNextSubAddrAreaIndex;

  /* Move to the next sub address area */
  LusNextSubAddrAreaIndex = Fee_GusCurrSubAddrAreaId + FEE_ONE;

  /* Check for number of sub area that configured */
  if (LusNextSubAddrAreaIndex >= Fee_GaaAddrAreaConfig[Fee_GusCurrAddrAreaId].usNumOfSubAddrArea)
  {
    LusNextSubAddrAreaIndex = FEE_ZERO;
  }

  /* Get the configured start address of the next address area */
  LulStartAreaAddr = Fee_GaaAddrAreaConfig[Fee_GusCurrAddrAreaId].pSubAddrArea[LusNextSubAddrAreaIndex].ulStartAreaAddr;

  /* Get the current size of address area */
  LulAddrAreaSize = Fee_GaaAddrAreaConfig[Fee_GusCurrAddrAreaId].pSubAddrArea[LusNextSubAddrAreaIndex].ulAddrAreaSize;

  LusAreaId = Fee_GaaAddrAreaConfig[Fee_GusCurrAddrAreaId].usAddrAreaID;

  LucExtReturnValue = MemAcc_Erase(LusAreaId, LulStartAreaAddr, LulAddrAreaSize);

  if (E_OK == LucExtReturnValue)
  {
    /* Writing procesing has been accepted */
    LenReturnValue = MEMIF_JOB_PENDING;
    /* Set checking MemAcc result flag */
    Fee_GblWaitMemAccResult = FEE_TRUE;
  }
  else
  {
    /* Writing procesing has not been accepted */
    LenReturnValue = MEMIF_JOB_FAILED;
  }
  /* Schedule format Job */
  /* Fee_Write -> Update Command -> Async proceed by Mainfunction */
  Fee_GenRequestedCmd = FEE_CMD_SWAP_ADDRESS_AREA;
  /* Return value */
  return LenReturnValue;
}
#define FEE_STOP_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


/***********************************************************************************************************************
** Function Name             : Fee_JobSwapAddrArea
**
** Service ID                : None
**
** Description               : This function to support initilialize the header of page in case swap
**
** Sync/Async                : Asynchronous
**
** Reentrancy                : Non Reentrant
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : MemIf_JobResultType
**                             MEMIF_JOB_PENDING: The last job is waiting for execution or currently being executed.
**                             MEMIF_JOB_FAILED: The last job has not been finished successfully (it failed).
**
** Preconditions             : None
**
** Global Variables Used     : Fee_GusCurrSubAddrAreaId, Fee_GaaAddrAreaConfig[], Fee_GusCurrAddrAreaId,
**                           : Fee_GulJobRefAreaAddr, Fee_GenRequestedCmd, Fee_GaaDataBuffer
**
** Function(s) invoked       : Fee_PrepareHeaderAddrArea, Fee_InternalWrite
**
** Registers Used            : None
**
** Reference ID              : FEE_DUD_ACT_042, FEE_DUD_ACT_042_GBL002
** Reference ID              : FEE_DUD_ACT_042_GBL006, FEE_DUD_ACT_042_GBL007, FEE_DUD_ACT_042_GBL008
***********************************************************************************************************************/
#define FEE_START_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
STATIC FUNC(MemIf_JobResultType, FEE_PRIVATE_CODE) Fee_JobSwapAddrArea(void)
{
  MemIf_JobResultType LenReturnValue;

  /* Local structure for address area header */
  Fee_AddrAreaHeaderType LstAddrAreaHeader;
  uint16 LusNextSubAddrAreaIndex;

  /* Move to the next sub address area */
  LusNextSubAddrAreaIndex = Fee_GusCurrSubAddrAreaId + FEE_ONE;

  /* Check for number of sub area that configured */
  if (LusNextSubAddrAreaIndex >= Fee_GaaAddrAreaConfig[Fee_GusCurrAddrAreaId].usNumOfSubAddrArea)
  {
    LusNextSubAddrAreaIndex = FEE_ZERO;
  }
  /* Assign FEE_ZERO for the first block */
  Fee_GusBlockIndex = FEE_ZERO;
  /* Get the configured start address */
  LstAddrAreaHeader.usAddrAreaID = Fee_GaaAddrAreaConfig[Fee_GusCurrAddrAreaId].usAddrAreaID + FEE_ONE;

  LstAddrAreaHeader.ulStartAreaAddr = 
                    Fee_GaaAddrAreaConfig[Fee_GusCurrAddrAreaId].pSubAddrArea[LusNextSubAddrAreaIndex].ulStartAreaAddr;

  /* Get the current size of address area */
  LstAddrAreaHeader.ulAddrAreaSize = 
                    Fee_GaaAddrAreaConfig[Fee_GusCurrAddrAreaId].pSubAddrArea[LusNextSubAddrAreaIndex].ulAddrAreaSize;

  /* Data direction in the memory */
  LstAddrAreaHeader.ulConfigDirection = FEE_DATA_DIRECTION;

  /* Initialize address area header: Address area ID - address of address area - address area size */
  Fee_PrepareHeaderAddrArea(&LstAddrAreaHeader, (P2VAR(uint8, AUTOMATIC, FEE_APPL_DATA)) Fee_GaaDataBuffer);            /* PRQA S 0751, 3432 # JV-01, JV-01 */
  /* Reset global reference pointer to new address area */
  Fee_GulJobRefAreaAddr = LstAddrAreaHeader.ulStartAreaAddr;
  Fee_GulJobRefAreaAddr = Fee_GulJobRefAreaAddr + FEE_PAGE_OVERHEAD;                                                    /* PRQA S 3383 # JV-01 */

  #if (FEE_WRITE_DATA_IN_REVERT_DIRECTION == STD_ON)
  Fee_GulJobDataAddr = LstAddrAreaHeader.ulStartAreaAddr + LstAddrAreaHeader.ulAddrAreaSize;                            /* PRQA S 3383 # JV-01 */
  #endif /* #if (FEE_WRITE_DATA_IN_REVERT_DIRECTION == STD_ON) */
  LenReturnValue = Fee_InternalWrite(LstAddrAreaHeader.ulStartAreaAddr, (P2CONST(uint8, AUTOMATIC, FEE_APPL_CONST))     /* PRQA S 0751 # JV-01 */
                                                Fee_GaaDataBuffer, FEE_PAGE_OVERHEAD - FEE_HEADE_VALID_INFOR_ADDRESS);                                                                
  /* Schedule format Job */
  /* fee_Write -> Update Command -> Async proceed by Mainfunction */
  Fee_GenRequestedCmd = FEE_CMD_SWAP_HEADER_BLOCK;
  /* Return value */
  return LenReturnValue;
}
#define FEE_STOP_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name             : Fee_JobSwapHeaderBlock
**
** Service ID                : None
**
** Description               : This function to support calculate header block data
**
** Sync/Async                : Asynchronous
**
** Reentrancy                : Non Reentrant
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : MemIf_JobResultType
**                             MEMIF_JOB_PENDING: The last job is waiting for execution or currently being executed.
**                             MEMIF_JOB_FAILED: The last job has not been finished successfully (it failed).
**
** Preconditions             : None
**
** Global Variables Used     : Fee_GaaAddrAreaConfig[], Fee_GusCurrAddrAreaId, Fee_GaaBlockInfo[], Fee_GpBlockConfig[]
**                             Fee_GusBlockIndex, Fee_GenRequestedCmd, Fee_GaaDataBuffer
**
** Function(s) invoked       : Fee_JobSwapWriteValidAddrArea, Fee_AlignToVirtualPageSize
**                             Fee_PrepareHeaderBlockData, Fee_InternalWrite
**
** Registers Used            : None
**
** Reference ID              : FEE_DUD_ACT_043, FEE_DUD_ACT_043_GBL002, FEE_DUD_ACT_043_GBL005
** Reference ID              : FEE_DUD_ACT_043_GBL006
***********************************************************************************************************************/
#define FEE_START_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
STATIC FUNC(MemIf_JobResultType, FEE_PRIVATE_CODE) Fee_JobSwapHeaderBlock(void)
{
  /* Declare the return value */
  MemIf_JobResultType LenReturnValue;
  Fee_BlockStatusType LenBlockStatus;
  uint16 LusBlockIndex;
  uint8 LucIndexAddrArea;
  #if (FEE_WRITE_DATA_IN_REVERT_DIRECTION == STD_ON)
  uint16 LusAlignedBlockSize;
  #endif /* #if (FEE_WRITE_DATA_IN_REVERT_DIRECTION == STD_ON) */
  Fee_BlockHeaderType LpBlockHeaderInfo;

  /* Loop for all block in the current address area */
  for (LusBlockIndex = Fee_GusBlockIndex; LusBlockIndex < FEE_MAX_CONFIGURED_BLOCK_NUMBER; LusBlockIndex++)
  {
    LucIndexAddrArea = Fee_GaaBlockConfig[LusBlockIndex].usIndexAddrArea;                                               /* PRQA S 4461 # JV-01 */
    /* Check the address area that block belong to */
    if (Fee_GaaAddrAreaConfig[Fee_GusCurrAddrAreaId].usAddrAreaID ==
                                                          Fee_GaaAddrAreaConfig[LucIndexAddrArea].usAddrAreaID)
    {
      /* Get the status of block */
      LenBlockStatus = Fee_GaaBlockInfo[LusBlockIndex].enBlockStatus;
      /* Check status of block header and the target block for swap is not the current block for request */
      if ((FEE_BLOCK_VALID == LenBlockStatus) && (LusBlockIndex != Fee_GstVar.usBlockIndex))
      {
        /* Assign the current Block Index to global variable */
        Fee_GusBlockIndex = LusBlockIndex;
        break;
      }
    }
  }
  /* Reaching the maximum number of configured block */
  if (FEE_MAX_CONFIGURED_BLOCK_NUMBER == LusBlockIndex)
  {
    /* Validate for this address area */
    LenReturnValue = Fee_JobSwapWriteValidAddrArea();
  }
  else /* Found a valid block, prepare block header in new page */
  {
    /* Get the information of block */
    /* Block ID */
    LpBlockHeaderInfo.usFeeBlockNumber = Fee_GpBlockConfig[LusBlockIndex].usFeeBlockNumber;
    /* Block size */
    LpBlockHeaderInfo.usBlockSize = Fee_GpBlockConfig[LusBlockIndex].usBlockSize;
    /* Block Data Address */
    /* Calculate with new address data */
    #if (FEE_WRITE_DATA_IN_REVERT_DIRECTION == STD_ON)
    /* Calculate the alignment of the block size. */
    LusAlignedBlockSize = Fee_AlignToVirtualPageSize(LpBlockHeaderInfo.usBlockSize);
    LpBlockHeaderInfo.ulBlockDataAddr = Fee_GulJobDataAddr - LusAlignedBlockSize;                                       /* PRQA S 3383 # JV-01 */
    #else
    LpBlockHeaderInfo.ulBlockDataAddr = Fee_GulJobRefAreaAddr + FEE_BLOCK_OVERHEAD;                                     /* PRQA S 3383 # JV-01 */
    #endif /* #if (FEE_WRITE_DATA_IN_REVERT_DIRECTION == STD_ON) */
    /* Block W/E Cycle */
    LpBlockHeaderInfo.ulWECycles = Fee_GaaBlockInfo[LusBlockIndex].ulBlockWECycle + FEE_ONE;                            /* PRQA S 3383, 2843 # JV-01, JV-01 */
    /* Serialize block data header */
    Fee_PrepareHeaderBlockData(&LpBlockHeaderInfo, (P2VAR(uint8, AUTOMATIC, FEE_APPL_DATA)) Fee_GaaDataBuffer);         /* PRQA S 0751, 3432, 2976 # JV-01, JV-01, JV-01 */
    /* Write header of block */
    LenReturnValue = Fee_InternalWrite(Fee_GulJobRefAreaAddr, (P2CONST(uint8, AUTOMATIC, FEE_APPL_CONST))               /* PRQA S 0751 # JV-01 */
                                              Fee_GaaDataBuffer, FEE_BLOCK_OVERHEAD - FEE_VALID_BLOCK_OFFSET_ADDR);
    /* After writing successfull -> Read data */
    Fee_GenRequestedCmd = FEE_CMD_SWAP_READ_BLOCK_DATA;
    /* Move to the next block header */
    #if (FEE_WRITE_DATA_IN_REVERT_DIRECTION == STD_ON)
    Fee_GulJobRefAreaAddr = Fee_GulJobRefAreaAddr + FEE_BLOCK_OVERHEAD;                                                 /* PRQA S 3383 # JV-01 */
    #endif /* #if (FEE_WRITE_DATA_IN_REVERT_DIRECTION == STD_ON) */
  }
  /* Return value */
  return LenReturnValue;
}
#define FEE_STOP_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name             : Fee_JobSwapReadDataBlock
**
** Service ID                : None
**
** Description               : This function to support swap data of block when header have been written successfully
**
** Sync/Async                : Asynchronous
**
** Reentrancy                : Non Reentrant
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : MemIf_JobResultType
**                             MEMIF_JOB_PENDING: The last job is waiting for execution or currently being executed.
**                             MEMIF_JOB_FAILED: The last job has not been finished successfully (it failed).
**
** Preconditions             : None
**
** Global Variables Used     : Fee_GpBlockConfig[], Fee_GaaBlockInfo[], Fee_GenRequestedCmd, Fee_GaaDataBuffer
**
** Function(s) invoked       : Fee_AlignToVirtualPageSize, Fee_InternalRead
**
** Registers Used            : None
**
** Reference ID              : FEE_DUD_ACT_044, FEE_DUD_ACT_044_GBL001
***********************************************************************************************************************/
#define FEE_START_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
STATIC FUNC(MemIf_JobResultType, FEE_PRIVATE_CODE) Fee_JobSwapReadDataBlock(void)
{
  MemIf_JobResultType LenReturnValue;
  MemAcc_AddressType LuBlockAddress;
  uint16 LusAlignedBlockSize;
  uint16 LusBlockSize;

  /* Get size of swapped block */
  /* Block size */
  LusBlockSize = Fee_GpBlockConfig[Fee_GusBlockIndex].usBlockSize;

  /* Aligned block (If blocksize is not algined with Virtual page size) */
  /* Calculate the alignment of the block size. */
  LusAlignedBlockSize = Fee_AlignToVirtualPageSize(LusBlockSize);

  /* Get the address of data block */
  LuBlockAddress = Fee_GaaBlockInfo[Fee_GusBlockIndex].ulBlockDataAddr;

  /* Write data block for valid block data */
  LenReturnValue = Fee_InternalRead(LuBlockAddress, (P2VAR(uint8, AUTOMATIC, FEE_APPL_DATA)) Fee_GaaDataBuffer,         /* PRQA S 0751, 3432 # JV-01, JV-01 */
                                                                                                LusAlignedBlockSize);
  /* fee_Read -> Update Command -> Async proceed by Mainfunction */
  Fee_GenRequestedCmd = FEE_CMD_SWAP_BLOCK_DATA_WRITE;
  /* Return value */
  return LenReturnValue;
}
#define FEE_STOP_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name             : Fee_JobSwapWriteDataBlock
**
** Service ID                : None
**
** Description               : This function to support swap data of block when header have been written successfully
**
** Sync/Async                : Asynchronous
**
** Reentrancy                : Non Reentrant
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : MemIf_JobResultType
**                             MEMIF_JOB_PENDING: The last job is waiting for execution or currently being executed.
**                             MEMIF_JOB_FAILED: The last job has not been finished successfully (it failed).
**
** Preconditions             : None
**
** Global Variables Used     : Fee_GpBlockConfig[], Fee_GusBlockIndex, Fee_GulJobRefAreaAddr, Fee_GenRequestedCmd
**                           : Fee_GaaDataBuffer
**
** Function(s) invoked       : Fee_AlignToVirtualPageSize, Fee_InternalWrite
**
** Registers Used            : None
**
** Reference ID              : FEE_DUD_ACT_045, FEE_DUD_ACT_045_GBL001, FEE_DUD_ACT_045_GBL002
** Reference ID              : FEE_DUD_ACT_045_GBL003
***********************************************************************************************************************/
#define FEE_START_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
STATIC FUNC(MemIf_JobResultType, FEE_PRIVATE_CODE) Fee_JobSwapWriteDataBlock(void)
{
  MemIf_JobResultType LenReturnValue;
  MemAcc_AddressType LuBlockDataAddress;

  uint16 LusBlockSize;
  uint16 LusAlignedBlockSize;

  /* Get size of swapped block */
  /* Block size */
  LusBlockSize = Fee_GpBlockConfig[Fee_GusBlockIndex].usBlockSize;

  /* Aligened block (If blocksize is not algined with Virtual page size) */
  /* Calculate the alignment of the block size. */
  LusAlignedBlockSize = Fee_AlignToVirtualPageSize(LusBlockSize);

  /* Calculate the data address */
  #if (FEE_WRITE_DATA_IN_REVERT_DIRECTION == STD_ON)
  LuBlockDataAddress = Fee_GulJobDataAddr - LusAlignedBlockSize;                                                        /* PRQA S 3383 # JV-01 */
  #else
  LuBlockDataAddress = Fee_GulJobRefAreaAddr + FEE_BLOCK_OVERHEAD;                                                      /* PRQA S 3383 # JV-01 */
  #endif /* #if (FEE_WRITE_DATA_IN_REVERT_DIRECTION == STD_ON) */

  /* Invoke write function for write for new sub-address area */
  LenReturnValue = Fee_InternalWrite(LuBlockDataAddress, (P2CONST(uint8, AUTOMATIC, FEE_APPL_CONST)) Fee_GaaDataBuffer, /* PRQA S 0751 # JV-01 */
                                                                                                  LusAlignedBlockSize);
  /* Move to next block */
  #if (FEE_WRITE_DATA_IN_REVERT_DIRECTION == STD_ON)
  Fee_GulJobDataAddr = Fee_GulJobDataAddr - LusAlignedBlockSize;                                                        /* PRQA S 3383 # JV-01 */
  #else
  Fee_GulJobRefAreaAddr = Fee_GulJobRefAreaAddr + FEE_BLOCK_OVERHEAD + LusAlignedBlockSize;                             /* PRQA S 3383 # JV-01 */
  #endif /* #if (FEE_WRITE_DATA_IN_REVERT_DIRECTION == STD_ON) */

  /* Validate the writed data block */
  Fee_GenRequestedCmd = FEE_CMD_SWAP_DATA_VALIDATE_BLOCK;
  /* Return value */
  return LenReturnValue;
}
#define FEE_STOP_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name             : Fee_JobSwapWriteValidBlock
**
** Service ID                : None
**
** Description               : This function to support write validate flag in case write data successfully
**
** Sync/Async                : Asynchronous
**
** Reentrancy                : Non Reentrant
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : MemIf_JobResultType
**                             MEMIF_JOB_PENDING: The last job is waiting for execution or currently being executed.
**                             MEMIF_JOB_FAILED: The last job has not been finished successfully (it failed).
**
** Preconditions             : None
**
** Global Variables Used     : Fee_GpBlockConfig[], Fee_GulJobRefAreaAddr, Fee_GusBlockIndex, Fee_GenRequestedCmd
**                           : Fee_GaaDataBuffer
**
** Function(s) invoked       : Fee_AlignToVirtualPageSize, Fee_PrepareHeaderFlag
**                             Fee_InternalWrite
**
** Registers Used            : None
**
** Reference ID              : FEE_DUD_ACT_046, FEE_DUD_ACT_046_GBL004, FEE_DUD_ACT_046_GBL005
***********************************************************************************************************************/
#define FEE_START_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
STATIC FUNC(MemIf_JobResultType, FEE_PRIVATE_CODE) Fee_JobSwapWriteValidBlock(void)
{
  MemIf_JobResultType LenReturnValue;
  MemAcc_AddressType LuBlockAddress;
  #if (FEE_WRITE_DATA_IN_REVERT_DIRECTION == STD_OFF)
  uint16 LusBlockSize;
  uint16 LusAlignedBlockSize;

  /* Block size */
  LusBlockSize = Fee_GpBlockConfig[Fee_GusBlockIndex].usBlockSize;

  /* Align block (If blocksize is not algined with Virtual page size) */
  LusAlignedBlockSize = Fee_AlignToVirtualPageSize(LusBlockSize);
  #endif /* #if (FEE_WRITE_DATA_IN_REVERT_DIRECTION == STD_OFF) */

  #if (FEE_WRITE_DATA_IN_REVERT_DIRECTION == STD_ON)
  LuBlockAddress = Fee_GulJobRefAreaAddr - FEE_VALID_BLOCK_OFFSET_ADDR;                                                 /* PRQA S 3383 # JV-01 */
  #else
  LuBlockAddress = Fee_GulJobRefAreaAddr - LusAlignedBlockSize - FEE_VALID_BLOCK_OFFSET_ADDR;                           /* PRQA S 3383, 3384 # JV-01, JV-01 */
  #endif /* #if (FEE_WRITE_DATA_IN_REVERT_DIRECTION == STD_ON) */

  /* Serial valid flag block */
  Fee_PrepareHeaderFlag((P2VAR(uint8, AUTOMATIC, FEE_APPL_DATA))Fee_GaaDataBuffer, FEE_VALIDATED_VALUE);                /* PRQA S 0751, 3432 # JV-01, JV-01 */

  /* Write header to flash */
  LenReturnValue = Fee_InternalWrite(LuBlockAddress, (P2CONST(uint8, AUTOMATIC, FEE_APPL_CONST)) Fee_GaaDataBuffer,     /* PRQA S 0751 # JV-01 */
                                                                                                    FEE_ONE_UNIT_SIZE);
  /* Increase to the next block */
  Fee_GusBlockIndex++;                                                                                                  /* PRQA S 3383 # JV-01 */

  /* Move to next block header */
  Fee_GenRequestedCmd = FEE_CMD_SWAP_HEADER_BLOCK;
  /* Return value */
  return LenReturnValue;
}
#define FEE_STOP_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name             : Fee_JobSwapWriteValidAddrArea
**
** Service ID                : None
**
** Description               : This function to support validate page in case swap all block data successfully
**
** Sync/Async                : Asynchronous
**
** Reentrancy                : Non Reentrant
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : MemIf_JobResultType
**                             MEMIF_JOB_PENDING: The last job is waiting for execution or currently being executed.
**                             MEMIF_JOB_FAILED: The last job has not been finished successfully (it failed).
**
** Preconditions             : None
**
** Global Variables Used     : Fee_GusCurrSubAddrAreaId, Fee_GaaAddrAreaConfig[], Fee_GenRequestedCmd, Fee_GaaDataBuffer
**
** Function(s) invoked       : Fee_PrepareHeaderFlag, Fee_InternalWrite
**
** Registers Used            : None
**
** Reference ID              : FEE_DUD_ACT_047, FEE_DUD_ACT_047_GBL001
***********************************************************************************************************************/
#define FEE_START_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
STATIC FUNC(MemIf_JobResultType, FEE_PRIVATE_CODE) Fee_JobSwapWriteValidAddrArea(void)
{
  MemIf_JobResultType LenReturnValue;

  uint32 LulAddrAreaInvalidAddr;
  uint16 LusNextSubAddrAreaIndex;

  LusNextSubAddrAreaIndex = Fee_GusCurrSubAddrAreaId + FEE_ONE;

  if (LusNextSubAddrAreaIndex >= Fee_GaaAddrAreaConfig[Fee_GusCurrAddrAreaId].usNumOfSubAddrArea)
  {
    LusNextSubAddrAreaIndex = FEE_ZERO;
  }

  /* Invalidate the current address area after successfull swap all data block to new address area */
  /* Prepare Invalid Flag value to write */
  Fee_PrepareHeaderFlag((P2VAR(uint8, AUTOMATIC, FEE_APPL_DATA))Fee_GaaDataBuffer, FEE_INVALIDATED_FLAG_VALUE);         /* PRQA S 0751, 3432 # JV-01, JV-01 */

  /* Invoke MemAcc_Write()/Fee_Write() for write invalidate on flash memory */
  LulAddrAreaInvalidAddr = 
        Fee_GaaAddrAreaConfig[Fee_GusCurrAddrAreaId].pSubAddrArea[LusNextSubAddrAreaIndex].ulStartAreaAddr +            /* PRQA S 3383 # JV-01 */
                                                              (FEE_PAGE_OVERHEAD - FEE_VALID_ADDRESS_AREA_OFFSET_ADDR);

  /* Write header address area to remark the current address area is INVALID */
  LenReturnValue = Fee_InternalWrite(LulAddrAreaInvalidAddr, (P2CONST(uint8, AUTOMATIC, FEE_APPL_CONST))                /* PRQA S 0751 # JV-01 */
                                                                                Fee_GaaDataBuffer, FEE_ONE_UNIT_SIZE);
  Fee_GenRequestedCmd = FEE_CMD_SWAP_VALIDATED_ADDRESS_AREA;
  /* Return value */
  return LenReturnValue;
}
#define FEE_STOP_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name             : Fee_JobSwapValidAddrArea
**
** Service ID                : None
**
** Description               : This function to support validate page in case swap all block data successfully
**
** Sync/Async                : Asynchronous
**
** Reentrancy                : Non Reentrant
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : MemIf_JobResultType
**                             MEMIF_JOB_PENDING: The last job is waiting for execution or currently being executed.
**                             MEMIF_JOB_FAILED: The last job has not been finished successfully (it failed).
**
** Preconditions             : None
**
** Global Variables Used     : Fee_GaaAddrAreaConfig[], Fee_GusCurrSubAddrAreaId, Fee_GulJobDataAddr, Fee_GaaDataBuffer
**                             Fee_GusCurrAddrAreaId, Fee_GpBlockConfig[], Fee_GaaBlockInfo[], Fee_GulJobRefAreaAddr 
**
** Function(s) invoked       : Fee_AlignToVirtualPageSize, Fee_PrepareHeaderFlag
**                             Fee_InternalWrite
**
** Registers Used            : None
**
** Reference ID              : FEE_DUD_ACT_048, FEE_DUD_ACT_048_GBL002
** Reference ID              : FEE_DUD_ACT_048_GBL003, FEE_DUD_ACT_048_GBL004, FEE_DUD_ACT_048_GBL005
** Reference ID              : FEE_DUD_ACT_048_GBL006, FEE_DUD_ACT_048_GBL007, FEE_DUD_ACT_048_GBL008
** Reference ID              : FEE_DUD_ACT_048_GBL009, FEE_DUD_ACT_048_GBL010, FEE_DUD_ACT_048_GBL011
** Reference ID              : FEE_DUD_ACT_048_GBL012, FEE_DUD_ACT_048_GBL013, FEE_DUD_ACT_048_GBL014
** Reference ID              : FEE_DUD_ACT_048_GBL015, FEE_DUD_ACT_048_GBL016, FEE_DUD_ACT_048_GBL017
** Reference ID              : FEE_DUD_ACT_048_GBL018, FEE_DUD_ACT_048_GBL019
***********************************************************************************************************************/
#define FEE_START_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
STATIC FUNC(MemIf_JobResultType, FEE_PRIVATE_CODE) Fee_JobSwapValidAddrArea(void)
{
  MemIf_JobResultType LenReturnValue;
  Fee_BlockStatusType LenBlockStatus;
  uint32 LulAddrAreaInvalidAddr;
  uint16 LusBlockIndex;
  uint8 LucIndexAddrArea;
  uint16 LusBlockSize;
  uint16 LusAlignedBlockSize;
  uint8 LusNextSubAddrAreaIndex;

  LusNextSubAddrAreaIndex = (uint8)Fee_GusCurrSubAddrAreaId + FEE_ONE;

  if (LusNextSubAddrAreaIndex >= Fee_GaaAddrAreaConfig[Fee_GusCurrAddrAreaId].usNumOfSubAddrArea)
  {
    LusNextSubAddrAreaIndex = FEE_ZERO;
  }
  /* Get the address area start address */
  Fee_GulJobRefAreaAddr = 
                    Fee_GaaAddrAreaConfig[Fee_GusCurrAddrAreaId].pSubAddrArea[LusNextSubAddrAreaIndex].ulStartAreaAddr;

  /* Get the current address area size */
  Fee_GulJobDataAddr = Fee_GulJobRefAreaAddr +                                                                          /* PRQA S 3383 # JV-01 */
                      Fee_GaaAddrAreaConfig[Fee_GusCurrAddrAreaId].pSubAddrArea[LusNextSubAddrAreaIndex].ulAddrAreaSize;

  /* Move to first block header */
  Fee_GulJobRefAreaAddr = Fee_GulJobRefAreaAddr + FEE_PAGE_OVERHEAD;                                                    /* PRQA S 3383 # JV-01 */

  /* Loop for all configured block */
  /* Convert all information of configured block to new address area */
  for (LusBlockIndex = FEE_ZERO; LusBlockIndex < FEE_MAX_CONFIGURED_BLOCK_NUMBER; LusBlockIndex++)
  {
    LucIndexAddrArea = Fee_GaaBlockConfig[LusBlockIndex].usIndexAddrArea;                                               /* PRQA S 4461 # JV-01 */
    if (Fee_GaaAddrAreaConfig[Fee_GusCurrAddrAreaId].usAddrAreaID == 
                                                           Fee_GaaAddrAreaConfig[LucIndexAddrArea].usAddrAreaID)
    {
      /* Get the status of block */
      LenBlockStatus = Fee_GaaBlockInfo[LusBlockIndex].enBlockStatus;

      /* Check status of block header */
      if ((FEE_BLOCK_VALID == LenBlockStatus) && (LusBlockIndex != Fee_GstVar.usBlockIndex))
      {
        /* Get the block size */
        LusBlockSize = Fee_GpBlockConfig[LusBlockIndex].usBlockSize;

        /* Calculate the alignment of the block size. */
        LusAlignedBlockSize = Fee_AlignToVirtualPageSize(LusBlockSize);

        #if (FEE_WRITE_DATA_IN_REVERT_DIRECTION == STD_ON)
        Fee_GulJobDataAddr = Fee_GulJobDataAddr - LusAlignedBlockSize;                                                  /* PRQA S 3383 # JV-01 */

        /* Update the data header address */
        Fee_GaaBlockInfo[LusBlockIndex].ulBlockRefAddr = Fee_GulJobRefAreaAddr;

        /* Update the data pointer address */
        Fee_GaaBlockInfo[LusBlockIndex].ulBlockDataAddr = Fee_GulJobDataAddr;

        /* Update the W/E cycle of block */
        Fee_GaaBlockInfo[LusBlockIndex].ulBlockWECycle = Fee_GaaBlockInfo[LusBlockIndex].ulBlockWECycle + FEE_ONE;      /* PRQA S 3383 # JV-01 */

        /* Point to the next address */
        Fee_GulJobRefAreaAddr = Fee_GulJobRefAreaAddr + FEE_BLOCK_OVERHEAD;                                             /* PRQA S 3383 # JV-01 */
        #else
        /* Update the reference pointer for block header */
        Fee_GaaBlockInfo[LusBlockIndex].ulBlockRefAddr = Fee_GulJobRefAreaAddr;

        /* Update the reference pointer for block data */
        Fee_GaaBlockInfo[LusBlockIndex].ulBlockDataAddr = Fee_GulJobRefAreaAddr + FEE_BLOCK_OVERHEAD;                   /* PRQA S 3383 # JV-01 */

        /* Update the W/E cycle of block */
        Fee_GaaBlockInfo[LusBlockIndex].ulBlockWECycle = Fee_GaaBlockInfo[LusBlockIndex].ulBlockWECycle + FEE_ONE;      /* PRQA S 3383 # JV-01 */

        /* Update the reference pointer of current address area */
        Fee_GulJobRefAreaAddr = Fee_GulJobRefAreaAddr + FEE_BLOCK_OVERHEAD + LusAlignedBlockSize;                       /* PRQA S 3383 # JV-01 */
        #endif /* #if (FEE_WRITE_DATA_IN_REVERT_DIRECTION == STD_ON) */
      }
      else
      {
        /* Update Block Status to BLOCK INVALID in case BLOCK INVALID or BLOCK INCONSISTENT or 
        BLOCK of ERASE IMMEDIATE or BLOCK of WRITE request */
        Fee_GaaBlockInfo[LusBlockIndex].enBlockStatus = FEE_BLOCK_INVALID;

        /* Update the reference pointer for block header */
        Fee_GaaBlockInfo[LusBlockIndex].ulBlockRefAddr = 0U;

        /* Update the reference pointer for block data */
        Fee_GaaBlockInfo[LusBlockIndex].ulBlockDataAddr = 0U;
      }
    }
  }

  /* Switch all information to new page */
  Fee_GaaAddrAreaInfo[Fee_GusCurrAddrAreaId].usSubAddrAreaIndex = LusNextSubAddrAreaIndex;
  Fee_GaaAddrAreaInfo[Fee_GusCurrAddrAreaId].ulCurrHeaderAreaAddr = Fee_GulJobRefAreaAddr;
  #if (FEE_WRITE_DATA_IN_REVERT_DIRECTION == STD_ON)
  Fee_GaaAddrAreaInfo[Fee_GusCurrAddrAreaId].ulCurrDataAreaAddr = Fee_GulJobDataAddr;
  #endif /* #if (FEE_WRITE_DATA_IN_REVERT_DIRECTION == STD_ON) */
  /* Invalidate the current address area after successfull swap all data block to new address area */
  /* Prepare Invalid Flag value to write */
  Fee_PrepareHeaderFlag((P2VAR(uint8, AUTOMATIC, FEE_APPL_DATA))Fee_GaaDataBuffer, FEE_INVALIDATED_FLAG_VALUE);         /* PRQA S 0751, 3432 # JV-01, JV-01 */

  /* Invoke MemAcc_Write()/Fee_Write() for write invalidate on flash memory */
  LulAddrAreaInvalidAddr = 
        Fee_GaaAddrAreaConfig[Fee_GusCurrAddrAreaId].pSubAddrArea[Fee_GusCurrSubAddrAreaId].ulStartAreaAddr +           /* PRQA S 3383 # JV-01 */
                                                            (FEE_PAGE_OVERHEAD - FEE_INVALID_ADDRESS_AREA_OFFSET_ADDR);

  /* Write header address area to remark the current address area is INVALID */
  LenReturnValue = Fee_InternalWrite(LulAddrAreaInvalidAddr, (P2CONST(uint8, AUTOMATIC, FEE_APPL_CONST))                /* PRQA S 0751 # JV-01 */
                                                                                  Fee_GaaDataBuffer, FEE_ONE_UNIT_SIZE);
  /* Invalidate block is done */
  Fee_GenRequestedCmd = FEE_CMD_SWAP_DONE;
  /* Return value */
  return LenReturnValue;
}
#define FEE_STOP_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name             : Fee_JobSwapDone
**
** Service ID                : None
**
** Description               : This function to support return to orginal request after swap feature done for no 
**                             enough in the current address area
**
** Sync/Async                : Asynchronous
**
** Reentrancy                : Non Reentrant
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : MemIf_JobResultType
**                             MEMIF_JOB_PENDING: The last job is waiting for execution or currently being executed.
**
** Preconditions             : None
**
** Global Variables Used     : Fee_GenModuleState, Fee_GenRequestedCmd
**
** Function(s) invoked       : None
**
** Registers Used            : None
**
** Reference ID              : FEE_DUD_ACT_049, FEE_DUD_ACT_049_GBL001, FEE_DUD_ACT_049_GBL002
***********************************************************************************************************************/
#define FEE_START_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
STATIC FUNC(MemIf_JobResultType, FEE_PRIVATE_CODE) Fee_JobSwapDone(void)
{
  MemIf_JobResultType LenReturnValue;

  /* The the return value to MEMIF_JOB_PENDING to support next excute in Fee_MainFunction */
  LenReturnValue = MEMIF_JOB_PENDING;

  /* Update the Driver status */
  Fee_GenModuleState = MEMIF_BUSY;

  /* Return to orgin Job */
  Fee_GenRequestedCmd = Fee_enPreviousRequestCmd;

  /* Return value */
  return LenReturnValue;
}
#define FEE_STOP_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
**                                          Internal function: Fee_InvalidateBlock()                                  **
***********************************************************************************************************************/
/***********************************************************************************************************************
** Function Name             : Fee_JobInvalidateBlock
**
** Service ID                : None
**
** Description               : This function is the main function of API Fee_InvalidateBlock, asynchronous from
**                             Fee_MainFunction()
**                             This function is to support check/writing Invalidate Flag on Invlid Address area of block
**
** Sync/Async                : Asynchronous
**
** Reentrancy                : Non Reentrant
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : MemIf_JobResultType
**                             MEMIF_JOB_OK: The last job has been finished successfully.
**                             MEMIF_JOB_PENDING: The last job is waiting for execution or currently being executed.
**                             MEMIF_JOB_FAILED: The last job has not been finished successfully (it failed).
**
** Preconditions             : None
**
** Global Variables Used     : Fee_GaaBlockInfo[], Fee_GstVar, Fee_GenRequestedCmd, Fee_GpBlockConfig[],
**                           : Fee_GaaDataBuffer
**
** Function(s) invoked       : Fee_PrepareHeaderFlag, Fee_InternalWrite
**
** Registers Used            : None
**
** Reference ID              : FEE_DUD_ACT_050, FEE_DUD_ACT_050_GBL001, FEE_DUD_ACT_050_GBL002
** Reference ID              : FEE_DUD_ACT_050_GBL003, FEE_DUD_ACT_050_GBL004, FEE_DUD_ACT_050_GBL005
** Reference ID              : FEE_DUD_ACT_050_GBL006
***********************************************************************************************************************/
#define FEE_START_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(MemIf_JobResultType, FEE_PRIVATE_CODE) Fee_JobInvalidateBlock(void)
{
  MemIf_JobResultType LenReturnValue;

  /* Define variable for Block Status */
  Fee_BlockStatusType LenBlockStatus;
  MemAcc_AddressType LulBlockInvalidAddr;

  /* Get the status of block */
  LenBlockStatus = Fee_GaaBlockInfo[Fee_GstVar.usBlockIndex].enBlockStatus;

  if (FEE_BLOCK_INVALID == LenBlockStatus)
  {
    /* Block have been invalid before */
    /* No need to validate again */
    /*  Update the schedule is No pending Job */
    Fee_GenRequestedCmd = FEE_CMD_NO_PENDING;
    Fee_GstVar.enCmdJobRequest = FEE_CMD_NO_PENDING;
    /* Return to MEMIF_JOB_OK */
    LenReturnValue = MEMIF_JOB_OK;
  }
  else
  {
    if (FEE_BLOCK_INCONSISTENT == LenBlockStatus)
    {
      /* Block have been written from Init or before */
      /* Remark block is INVALID without write on flash memory */
      Fee_GaaBlockInfo[Fee_GstVar.usBlockIndex].enBlockStatus = FEE_BLOCK_INVALID;

      /*  Update the schedule is No pending Job */
      Fee_GenRequestedCmd = FEE_CMD_NO_PENDING;
      /* Return to MEMIF_JOB_OK */
      LenReturnValue = MEMIF_JOB_OK;
    }
    else
    {
      /* Update the current address area to support Fee_Cancel() */
      Fee_GusCurrAddrAreaId = Fee_GpBlockConfig[Fee_GstVar.usBlockIndex].usIndexAddrArea;
      /* Prepare Invalid Flag value to write on flash */
      Fee_PrepareHeaderFlag((P2VAR(uint8, AUTOMATIC, FEE_APPL_DATA))Fee_GaaDataBuffer, FEE_INVALIDATED_FLAG_VALUE);     /* PRQA S 0751, 3432 # JV-01, JV-01 */

      /* Invoke MemAcc_Write()/Fee_Write() for write invalidate on flash memory */
      LulBlockInvalidAddr = Fee_GaaBlockInfo[Fee_GstVar.usBlockIndex].ulBlockRefAddr +                                  /* PRQA S 3383 # JV-01 */
                                                                    FEE_BLOCK_OVERHEAD - FEE_INVALID_BLOCK_OFFSET_ADDR; /* PRQA S 3384 # JV-01 */

      /* Write header data */
      /* SWS_Fee_00037 */
      LenReturnValue = Fee_InternalWrite(LulBlockInvalidAddr, (P2CONST(uint8, AUTOMATIC, FEE_APPL_CONST))               /* PRQA S 0751 # JV-01 */
                                                                                  Fee_GaaDataBuffer, FEE_ONE_UNIT_SIZE);
      /* Invalidate block is done */
      Fee_GenRequestedCmd = FEE_CMD_INVALIDATE_DONE;
    }
  }

  /* Return value */
  return LenReturnValue;
}
#define FEE_STOP_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name             : Fee_JobInvalidateBlockDone
**
** Service ID                : None
**
** Description               : This function is to support remark the done process validate on the block
**                             Set the status of block is FEE_BLOCK_INVALID.
**                             Set the job is no pending and waiting for new job
**
** Sync/Async                : Asynchronous
**
** Reentrancy                : Non Reentrant
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : MemIf_JobResultType
**                             MEMIF_JOB_OK: The last job has been finished successfully.
**
** Preconditions             : None
**
** Global Variables Used     : Fee_GaaBlockInfo[], Fee_GstVar, Fee_GenRequestedCmd
**
** Function(s) invoked       : None
**
** Registers Used            : None
**
** Reference ID              : FEE_DUD_ACT_051, FEE_DUD_ACT_051_GBL001, FEE_DUD_ACT_051_GBL002
***********************************************************************************************************************/
#define FEE_START_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(MemIf_JobResultType, FEE_PRIVATE_CODE) Fee_JobInvalidateBlockDone(void)
{
  /* Declare the return value */
  MemIf_JobResultType LenReturnValue = MEMIF_JOB_OK;
  /* SWS_Fee_00037 */
  /* After finish write on invalid address are, remark the status of block */
  Fee_GaaBlockInfo[Fee_GstVar.usBlockIndex].enBlockStatus = FEE_BLOCK_INVALID;
  
  /* No job is pending, waiting for new job */
  Fee_GenRequestedCmd = FEE_CMD_NO_PENDING;
  Fee_GstVar.enCmdJobRequest = FEE_CMD_NO_PENDING;
  /* Return value */
  return LenReturnValue;
}
#define FEE_STOP_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
**                                      Internal function: Fee_EraseImmediateBlock()                                  **
***********************************************************************************************************************/
/***********************************************************************************************************************
** Function Name             : Fee_JobEraseImmediate
**
** Service ID                : None
**
** Description               : 
**
** Sync/Async                : Asynchronous
**
** Reentrancy                : Non Reentrant
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : MemIf_JobResultType
**                             MEMIF_JOB_OK: The last job has been finished successfully.
**                             MEMIF_JOB_PENDING: The last job is waiting for execution or currently being executed.
**                             MEMIF_JOB_FAILED: The last job has not been finished successfully (it failed).
**
** Preconditions             : None
**
** Global Variables Used     : Fee_GpBlockConfig[], Fee_GstVar, Fee_GaaAddrAreaInfo[], Fee_GusCurrAddrAreaId, 
**                             Fee_enPreviousRequestCmd, Fee_GenRequestedCmd, Fee_GusCurrSubAddrAreaId
**
** Function(s) invoked       : Fee_AlignToVirtualPageSize, Fee_JobSwapPrepareNextAddressArea
**                             Fee_JobInvalidateBlock
**
** Registers Used            : None
**
** Reference ID              : FEE_DUD_ACT_052, FEE_DUD_ACT_052_GBL001, FEE_DUD_ACT_052_GBL002,
** Reference ID              : FEE_DUD_ACT_052_GBL003, FEE_DUD_ACT_052_GBL004, FEE_DUD_ACT_052_GBL005
***********************************************************************************************************************/
#define FEE_START_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(MemIf_JobResultType, FEE_PRIVATE_CODE) Fee_JobEraseImmediate(void)
{
  /* Declaring the return value */
  MemIf_JobResultType LenReturnValue;

  #if (FEE_WRITE_DATA_IN_REVERT_DIRECTION == STD_OFF)
  MemAcc_AddressType LulStartAreaAddr;
  MemAcc_AddressType LulAddrAreaSize;
  #endif /* #if (FEE_WRITE_DATA_IN_REVERT_DIRECTION == STD_OFF) */

  MemAcc_AddressType LulRemainSpaceSize;
  uint16 LusBlockSize;
  uint16 LusAlignedBlockSize;
  uint32 LulHeaderAddr;

  LenReturnValue = MEMIF_JOB_OK;
  /* Update the current address/sub-address area id */
  Fee_GusCurrAddrAreaId = Fee_GpBlockConfig[Fee_GstVar.usBlockIndex].usIndexAddrArea;
  Fee_GusCurrSubAddrAreaId = Fee_GaaAddrAreaInfo[Fee_GusCurrAddrAreaId].usSubAddrAreaIndex;
  /* Get the current header address of address area */
  LulHeaderAddr = Fee_GaaAddrAreaInfo[Fee_GusCurrAddrAreaId].ulCurrHeaderAreaAddr;

  #if (FEE_WRITE_DATA_IN_REVERT_DIRECTION == STD_ON)
  /* Calculate the remaining space in address area */
  LulRemainSpaceSize = Fee_GaaAddrAreaInfo[Fee_GusCurrAddrAreaId].ulCurrDataAreaAddr - LulHeaderAddr;                   /* PRQA S 3383 # JV-01 */
  #else

  /* Get the configure start address off Address Area */
  LulStartAreaAddr =Fee_GaaAddrAreaConfig[Fee_GusCurrAddrAreaId].pSubAddrArea[Fee_GusCurrSubAddrAreaId].ulStartAreaAddr;

  /* Get the current address area size */
  LulAddrAreaSize = Fee_GaaAddrAreaConfig[Fee_GusCurrAddrAreaId].pSubAddrArea[Fee_GusCurrSubAddrAreaId].ulAddrAreaSize;

  LulRemainSpaceSize = LulStartAreaAddr + LulAddrAreaSize - LulHeaderAddr;                                              /* PRQA S 3383, 3384 # JV-01, JV-01 */
  #endif /* #if (FEE_WRITE_DATA_IN_REVERT_DIRECTION == STD_ON) */

  /* Get the configured block size */
  LusBlockSize = Fee_GpBlockConfig[Fee_GstVar.usBlockIndex].usBlockSize;

  /* Calculate the align value */
  LusAlignedBlockSize = Fee_AlignToVirtualPageSize(LusBlockSize);

  /* SWS_Fee_00067 */
  /* Check for the remain space in current page */
  if (LulRemainSpaceSize < (((uint32)LusAlignedBlockSize) + (((uint32)3)*((uint32)FEE_BLOCK_OVERHEAD))))                /* PRQA S 3383 # JV-01 */ 
  {
    /* Store the current request */
    Fee_enPreviousRequestCmd = FEE_CMD_SWAP_ERASE_IMMEDIATE_BLOCK_DATA;
    LenReturnValue = Fee_JobSwapPrepareNextAddressArea();
  }
  else
  {
    if (FEE_CMD_SWAP_ERASE_IMMEDIATE_BLOCK_DATA != Fee_enPreviousRequestCmd)
    {
      /* If there is the remain space, invalidate the previous block to remark the immediate block have been INVALID,
      reduce the number of W/E on the memory */
      LenReturnValue = Fee_JobInvalidateBlock();
    }
    else
    {
      /* Update the schedule is No pending Job */
      Fee_enPreviousRequestCmd = FEE_CMD_NO_PENDING;
      Fee_GenRequestedCmd = FEE_CMD_NO_PENDING;
      Fee_GstVar.enCmdJobRequest = FEE_CMD_NO_PENDING;
    }
  }

  /* Return value */
  return LenReturnValue;
}
#define FEE_STOP_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
**                                      Internal function: Fee_MainFunction()                                         **
***********************************************************************************************************************/
/***********************************************************************************************************************
** Function Name            : Fee_CheckMemIfJobResult
**
** Service ID               : NA
**
** Description              : This Function check MemAcc wait Result and Memif job result
**
** Sync/Async               : Asynchronous
**
** Re-entrancy              : Non Re-entrant
**
** Input Parameters         : None
**
** InOut Parameters         : None
**
** Output Parameters        : None
**
** Return parameter         : None
**
** Preconditions            : None
**
** Global Variables Used    : Fee_GaaAddrAreaConfig[], Fee_GenRequestedCmd, Fee_GenJobResult
**                            Fee_GenModuleState
**
** Function(s) invoked      : MemAcc_GetJobStatus, MemAcc_GetJobResult
**
** Registers Used           : None
**
** Reference ID             : FEE_DUD_ACT_013, FEE_DUD_ACT_013_GBL002
** Reference ID             : FEE_DUD_ACT_013_GBL003, FEE_DUD_ACT_013_GBL004, FEE_DUD_ACT_013_GBL005
** Reference ID             : FEE_DUD_ACT_013_GBL008,
** Reference ID             : FEE_DUD_ACT_013_GBL009, FEE_DUD_ACT_013_GBL010, FEE_DUD_ACT_013_GBL011
***********************************************************************************************************************/
/* todo: Check and Update for Fee */
#define FEE_START_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(void, FEE_PRIVATE_CODE) Fee_CheckMemIfJobResult(MemIf_JobResultType LenJobResult)
{
  #if (FEE_POLLING_MODE == STD_ON)
  MemAcc_JobStatusType LenMemAccJobStatus;
  MemAcc_JobResultType LenMemAccJobResult; 
  MemAcc_AddressAreaIdType LusAddressAreaId;
  
  if (FEE_TRUE == Fee_GblWaitMemAccResult)
  {
    LusAddressAreaId = Fee_GaaAddrAreaConfig[Fee_GusCurrAddrAreaId].usAddrAreaID;
    /* Get MemAcc job status */
    LenMemAccJobStatus = MemAcc_GetJobStatus(LusAddressAreaId);
    if (MEMACC_JOB_PENDING != LenMemAccJobStatus)
    {
      /* Get MemAcc job result */
      LenMemAccJobResult = MemAcc_GetJobResult(LusAddressAreaId);
        if (MEMACC_MEM_OK != LenMemAccJobResult && MEMACC_MEM_CANCELED != LenMemAccJobResult)                           /* PRQA S 3397 # JV-01 */
        {
          /* Set the JOB result as failed */
          LenJobResult = MEMIF_JOB_FAILED;                                                                              /* PRQA S 1338 # JV-01 */
        }
      /* Reset MemAcc flag */
      Fee_GblWaitMemAccResult = FEE_FALSE;
    }
  }
  #endif
  /* Post process if job is failed */
  if ((MEMIF_JOB_FAILED == LenJobResult) || (MEMIF_BLOCK_INVALID == LenJobResult) ||
    (MEMIF_BLOCK_INCONSISTENT == LenJobResult))
  {
    if (MEMIF_BUSY_INTERNAL != Fee_GenModuleState)
    {
      /* Call job error notification function */
      FEE_CALLBACK_ERROR_NOTIFICATION;
    }
    /* Update job result */
    Fee_GenJobResult = LenJobResult;
    /* Update final status */
    Fee_GenModuleState = MEMIF_IDLE;
    /* Stop current operation */
    Fee_GenRequestedCmd = FEE_CMD_NO_PENDING;
  }
  else if (MEMIF_JOB_OK == LenJobResult)                                                                                /* PRQA S 2004 # JV-01 */
  {
    if (FEE_CMD_NO_PENDING == Fee_GenRequestedCmd)
    {
      if (MEMIF_BUSY == Fee_GenModuleState)
      {
        /* If module state is busy, check if need to execute user request after finish internal management */
        if (FEE_CMD_NO_PENDING != Fee_GstVar.enCmdJobRequest)
        {
          /* Restore user request to handle next cycle */
          Fee_GenRequestedCmd = Fee_GstVar.enCmdJobRequest;
        }
        else
        {
          /* Set job result to OK */
          Fee_GenJobResult = MEMIF_JOB_OK;
          /* Update final status */
          Fee_GenModuleState = MEMIF_IDLE;
          /* Call job end notification function */
          FEE_CALLBACK_END_NOTIFICATION;
        }
      }
      else
      {
        /* Update final status */
        Fee_GenModuleState = MEMIF_IDLE;
      }
    }
  } /* Pending, continue handle in next cycle */
} /* End of function Fee_CheckMemIfJobResult */

#define FEE_STOP_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
**                                      Internal function: Fee_MainFunction()                                         **
***********************************************************************************************************************/
/***********************************************************************************************************************
** Function Name            : Fee_HandleInternalManagementCommands
**
** Service ID               : NA
**
** Description              : This Function Handle Internal Management Commands
**
** Sync/Async               : Asynchronous
**
** Re-entrancy              : Non Re-entrant
**
** Input Parameters         : None
**
** InOut Parameters         : None
**
** Output Parameters        : None
**
** Return parameter         : None
**
** Preconditions            : None
**
** Global Variables Used    : Fee_GenRequestedCmd
**
** Function(s) invoked      : Fee_JobSwapAddrArea, Fee_JobSwapHeaderBlock,
**                            Fee_JobSwapReadDataBlock, Fee_JobSwapWriteDataBlock, Fee_JobSwapWriteValidBlock,
**                            Fee_JobSwapValidAddrArea, Fee_JobSwapDone, Fee_JobMainInit, 
**                            Fee_JobInitHeaderParse, Fee_JobInitScanBlockHeaderParse,
**                            Fee_JobInitWriteHeaderFormat, Fee_JobInitWriteHeaderFormatDone
**
** Registers Used           : None
**
** Reference ID             : FEE_DUD_ACT_056
***********************************************************************************************************************/
#define FEE_START_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(MemIf_JobResultType, FEE_PRIVATE_CODE) Fee_HandleInternalManagementCommands(void)
{
    MemIf_JobResultType LenJobResult = MEMIF_JOB_PENDING;

    switch (Fee_GenRequestedCmd)
    {
      /* Fee_Init() related jobs */
      case FEE_CMD_INITIALIZE:
          LenJobResult = Fee_JobMainInit();
          break;
      case FEE_CMD_INIT_ADDRESS_AREA_HEADER_PARSE:
          LenJobResult = Fee_JobInitHeaderParse();
          break;
      case FEE_CMD_INIT_SCAN_BLOCK_HEADER_PARSE:
          LenJobResult = Fee_JobInitScanBlockHeaderParse();
          break;
      case FEE_CMD_INIT_WRITE_HEADER_FORMAT:
          LenJobResult = Fee_JobInitWriteHeaderFormat();
          break;
      case FEE_CMD_INIT_WRITE_HEADER_FORMAT_DONE:
          LenJobResult = Fee_JobInitWriteHeaderFormatDone();
          break;

      /* SWAP-related jobs */
      case FEE_CMD_SWAP_ADDRESS_AREA:
          LenJobResult = Fee_JobSwapAddrArea();
          break;
      case FEE_CMD_SWAP_HEADER_BLOCK:
          LenJobResult = Fee_JobSwapHeaderBlock();
          break;
      case FEE_CMD_SWAP_READ_BLOCK_DATA:
          LenJobResult = Fee_JobSwapReadDataBlock();
          break;
      case FEE_CMD_SWAP_BLOCK_DATA_WRITE:
          LenJobResult = Fee_JobSwapWriteDataBlock();
          break;
      case FEE_CMD_SWAP_DATA_VALIDATE_BLOCK:
          LenJobResult = Fee_JobSwapWriteValidBlock();
          break;
      case FEE_CMD_SWAP_VALIDATED_ADDRESS_AREA:
          LenJobResult = Fee_JobSwapValidAddrArea();
          break;
      case FEE_CMD_SWAP_WRITE_HEADER_DATA:
          LenJobResult = Fee_JobWriteHeaderData();
          break;
      case FEE_CMD_SWAP_DONE:
          LenJobResult = Fee_JobSwapDone();
          break;
      case FEE_CMD_NO_PENDING:
      default:
          /* Do nothing command */
          break;
    }

    return LenJobResult;
}

#define FEE_STOP_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
