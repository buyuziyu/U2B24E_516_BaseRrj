/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Eth_ETNF_LLDriver.c                                                                                 */
/*====================================================================================================================*/
/*                                              COPYRIGHT                                                             */
/*====================================================================================================================*/
/* (c) 2023 - 2025 Renesas Electronics Corporation. All rights reserved.                                              */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains ETNF specific operations of Eth Driver Component.                                               */
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
/* Renesas shall not have any obligation to maintain, service or provide bug fixes for the supplied Product(s)        */
/* and/or the Application.                                                                                            */
/*                                                                                                                    */
/* Each User is solely responsible for determining the appropriateness of using the Product(s) and assumes all risks  */
/* associated with its exercise of rights under this Agreement, including, but not limited to the risks and costs     */
/* of program errors, compliance with applicable laws, damage to or loss of data, programs or equipment,              */
/* and unavailability or interruption of operations.                                                                  */
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
/*                                      Devices:        X2x                                                           */
/*====================================================================================================================*/

/***********************************************************************************************************************
**                                       Revision Control History                                                     **
***********************************************************************************************************************/
/*
 * 2.4.0: 30/05/2025    : Remove the SW-VERSION from header of file
 * 2.3.1: 31/03/2025    : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 * 2.3.0: 28/02/2025    : - As per ticket ARDAACL-53039:
 *                         Change Eth_HwReadMiiBit and Eth_HwWriteMiiBit from void to return function 
 *                         and add checking ECSR status.
 *                        - As per ticket ARDAACJ-695:
 *                        + Update the impact to change name of function Eth_ETNF_GetTimeOutValue to 
 *                        Eth_ETNF_GetElapsedTimeValue on the functions: Eth_ETNF_HwInit, Eth_ETNF_HwEnableController
 * 2.2.0: 31/12/2024    : Update SW-VERSION for Ver22.02.00(D) U2Bx Final Release
 * 2.1.2: 31/10/2024    : Increase SW-VERSION to 2.1.2
 * 2.1.1: 22/07/2024    : Update QAC message
 * 2.0.2: 28/03/2024    : Change variable name 
 *                        from Eth_GaaDemEventRxFramesLost to Eth_GpDemEventRxFramesLost,
 *                        from Eth_GaaDemEventCRC to Eth_GpDemEventCRC,
 *                        from Eth_GaaDemEventUnderSizeFrame to Eth_GpDemEventUnderSizeFrame,
 *                        from Eth_GaaDemEventOverSizeFrame to Eth_GpDemEventOverSizeFrame,
 *                        from Eth_GaaDemEventAlignment to Eth_GpDemEventAlignment,
 *                        from Eth_GaaDemEventRegisterCorruption to Eth_GpDemEventRegisterCorruption,
 *                        from Eth_GaaDemEventTimerincFailed to Eth_GpDemEventTimerincFailed,
 *                        from Eth_GaaDemEventTimeroffsetFailed to Eth_GpDemEventTimeroffsetFailed.
 *        25/03/2024    : Add set timestamp T1s through ulRIMR register
 *        26/12/2023    : Update QAC message.
 *        19/12/2023    : Initial Version
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                          Include Section                                                           **
***********************************************************************************************************************/
#include "Eth.h"
#include "Eth_Ram.h"
#include "Eth_ETNF_Ram.h"
#include "Eth_ETNF_Dma.h"
#include "Eth_ETNF_LLDriver.h"

#include "EthIf_Cbk.h"

#if (ETH_CRITICAL_SECTION_PROTECTION == STD_ON)
/* Included for the declaration of the critical section protection functions */
#include "SchM_Eth.h"
#endif
#if (ETH_ETHSWITCH_MANAGEMENT_SUPPORT == STD_ON)
#include "EthSwt_Cbk.h"
#endif

/***********************************************************************************************************************
**                                          Version Information                                                       **
***********************************************************************************************************************/
#if (ETH_MACRO_ETNF == STD_ON)
/* AUTOSAR release version information */
#define ETH_ETNF_C_AR_RELEASE_MAJOR_VERSION ETH_AR_RELEASE_MAJOR_VERSION_VALUE
#define ETH_ETNF_C_AR_RELEASE_MINOR_VERSION ETH_AR_RELEASE_MINOR_VERSION_VALUE
#define ETH_ETNF_C_AR_RELEASE_REVISION_VERSION ETH_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define ETH_ETNF_C_SW_MAJOR_VERSION    ETH_SW_MAJOR_VERSION_VALUE
#define ETH_ETNF_C_SW_MINOR_VERSION    ETH_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                           Version Check                                                            **
***********************************************************************************************************************/
#if (ETH_ETNF_AR_RELEASE_MAJOR_VERSION != ETH_ETNF_C_AR_RELEASE_MAJOR_VERSION)
#error "Eth_ETNF_LLDriver.c : Mismatch in Release Major Version"
#endif
#if (ETH_ETNF_AR_RELEASE_MINOR_VERSION != ETH_ETNF_C_AR_RELEASE_MINOR_VERSION)
#error "Eth_ETNF_LLDriver.c : Mismatch in Release Minor Version"
#endif
#if (ETH_ETNF_AR_RELEASE_REVISION_VERSION != ETH_ETNF_C_AR_RELEASE_REVISION_VERSION)
#error "Eth_ETNF_LLDriver.c : Mismatch in Release Revision Version"
#endif

#if (ETH_ETNF_SW_MAJOR_VERSION != ETH_ETNF_C_SW_MAJOR_VERSION)
#error "Eth_ETNF_LLDriver.c : Mismatch in Software Major Version"
#endif
#if (ETH_ETNF_SW_MINOR_VERSION != ETH_ETNF_C_SW_MINOR_VERSION)
#error "Eth_ETNF_LLDriver.c : Mismatch in Software Minor Version"
#endif

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:0306)    : [I] Cast between a pointer to object and an integral type.                                   */
/* Rule                : CERTCCM INT36, MISRA C:2012 Rule-11.4                                                        */
/*                       REFERENCE - ISO:C90-6.3.4  Semantics                                                         */
/* JV-01 Justification : This cast is essential to declare a pointer which points an I/O register.                    */
/*       Verification  : These pointers are const values and only used for I/O accesses, any problem doesn't occur.   */
/**********************************************************************************************************************/
/* Message (1:1514)    : The object 'entity' is only referenced by function 'func', in the translation unit where     */
/*                       it is defined                                                                                */
/* Rule                : MISRA C:2012 Rule-8.9                                                                        */
/* JV-01 Justification : When using interrupt mode, this global variable is referenced by an external source          */
/*                       interrupt handler. Therefore, this variable is not the only variable used by Eth_HwInit.     */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3218)    : File scope static 'Lin_GstSleepPdu' is only accessed in one function.                        */
/* Rule                : CERTCCM DCL19, MISRA C:2012 Rule-8.9                                                         */
/* JV-01 Justification : This is for better readability of code and easier to maintence. There is no problem because  */
/*                       the code is reviewed.                                                                        */
/*       Verification  : The scope of const objects don't affect the behavior.                                        */
/**********************************************************************************************************************/
/* Message (4:5087)    : (4:5087) #include statements in a file should only be preceded by other preprocessor         */
/*                       directives or comments.                                                                      */
/* Rule                : MISRA C:2012 Rule-20.1                                                                       */
/* JV-01 Justification : This is accepted, due to implementation for include memmap is following AUTOSAR rule.        */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0751)    : Casting to char pointer type.                                                                */
/* Rule                : CERTCCM EXP11, EXP39                                                                         */
/* JV-01 Justification : Since EICnEIMK exists in the lower 8 bits, there is no problem casting to char type.         */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3464)    : Argument to macro '%s' contains a side effect that will be evaluated more than once.         */
/* Rule                : CERTCCM PRE31                                                                                */
/* JV-01 Justification : After reviewing coding, it is concluded that this implementation is okay as it is since      */
/*                       the memory used to access this volatile variable is user RAM, not a specific HW              */
/*                       register, so there is no worry about potential side effects in this case.                    */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0316)    : [I] Cast from a pointer to void to a pointer to object type.                                 */
/* Rule                : MISRA C:2012 Rule-11.5                                                                       */
/* JV-01 Justification : Typecasting from void* is necessary to hide internal types from the header files which       */
/*                       are exposed to user.                                                                         */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:3383)    : Cannot identify wraparound guard for unsigned arithmetic expression.                         */
/* Rule                : CERTCCM INT30                                                                                */
/* JV-01 Justification : Wraparound can't be occur in this unsigned integer arithmetic so there is no need to add     */
/*                       a wraparound guard here.                                                                     */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3469)    : This usage of a function-like macro looks like it could be replaced by an equivalent         */
/*                       function call.                                                                               */
/* Rule                : MISRA C:2012 Dir-4.9                                                                         */
/* JV-01 Justification : To prevent overhead and speed up the processing, there is no need to call a function         */
/*                       here for such a small operation.                                                             */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7                                                                       */
/*                       REFERENCE - ISO:C90-6.3.1 Primary Expressions                                                */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is           */
/*                       accepted.                                                                                    */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:3384)    : Cannot identify wraparound guard for dependent unsigned arithmetic expression.               */
/* Rule                : CERTCCM INT30                                                                                */
/* JV-01 Justification : Wraparound can't be occur in this unsigned integer arithmetic so there is no need to add     */
/*                       a wraparound guard here.                                                                     */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3387)    : A full expression containing an increment (++) or decrement (--) operator should have no     */
/*                       potential side effects other than that caused by the increment or decrement operator.        */
/* Rule                : MISRA C:2012 Rule-13.3                                                                       */
/*                       REFERENCE - ISO:C90-5.1.2.3 Program Execution                                                */
/* JV-01 Justification : After reviewing coding, it is concluded that this implementation is okay as it is since      */
/*                       the memory used to access this volatile variable is user RAM, not a specific HW              */
/*                       register, so there is no worry about potential side effects in this case.                    */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0488)    : Performing pointer arithmetic.                                                               */
/* Rule                : CERTCCM EXP08, MISRA C:2012 Rule-18.4                                                        */
/* JV-01 Justification : To simplify the register checking by using the table.                                        */
/*       Verification  : Both of the arithmetic operands are constant values, it can be verified by the static        */
/*                       code analysis.                                                                               */
/**********************************************************************************************************************/
/* Message (2:3678)    : The object referenced by '%1s' is not modified through it, so '%1s' could be declared        */
/*                       with type '%2s'.                                                                             */
/* Rule                : MISRA C:2012 Rule-8.13                                                                       */
/* JV-01 Justification : The object addressed by this pointer change so it can not be of type "pointer to const"      */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:1881)    : The operands of this equality operator are expressions of different 'essential type'         */
/*                       categories (enum and unsigned).                                                              */
/* Rule                : CERTCCM INT02, MISRA C:2012 Rule-10.4                                                        */
/* JV-01 Justification : All are unsigned long type variables and do not correspond to the pointed out contents.      */
/*                       No problem.                                                                                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3416)    : Logical operation performed on expression with possible side effects.                        */
/* Rule                : CERTCCM EXP45                                                                                */
/* JV-01 Justification : This is necessary for suppressing optimization by dummy loop.                                */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (7:4399)    : An expression which is the result of a ~ or << has been cast to a wider type.                */
/* Rule                : MISRA-C:2012 Rule 10.8                                                                       */
/* JV-01 Justification : Since the -strictrank option is not used, int and long types are guaranteed to be equivalent.*/
/*                       Therefore, it does not affect the result of the arithmetic processing of the corresponding   */
/*                       part.                                                                                        */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3006)    : This function contains a mixture of in-line assembler statements and C statements.           */
/* Rule                : MISRA C:2012 Dir-4.3, CWE Rule CWE-398, CWE-569                                              */
/* JV-01 Justification : This is accepted, due to the Synchronization Processing Instruction is following hardware    */
/*                       specification.                                                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:1006)    : [E] This in-line assembler construct is a language extension. The code has been ignored.     */
/* Rule                : MISRA-C:2012 Dir-1.1, Rule-1.2, Dir-4.2, CERTC 1.2.4 MSC14                                   */
/* JV-01 Justification : Inline assembler support for syncp instruction.                                              */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3416)    : Logical operation performed on expression with persistent side effects.                      */
/* Rule                : CERTCCM EXP45, CWE Rule CWE-398, CWE-569, CWE-737                                            */
/* JV-01 Justification : Logical operation accesses volatile object which is a register access. All register          */
/*                       addresses are generated with volatile qualifiers. There is no impact on the functionality    */
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
/* Rule                : CERTCCM MSC07, MSC13, MISRA C:2012 Rule-2.2, CWE Rule CWE-398, CWE-561, CWE-569, CWE-633     */
/* JV-01 Justification : The content of LusReqSize will be changed if the user enables the EthSwt option, so the value*/
/*                       of this result is not always that of the left-hand operand.                                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:2844)    : Possible: Dereference of an invalid pointer value.                                           */
/* Rule                : CERTCCM ARR30, CWE Rule CWE-120, CWE-121, CWE-122, CWE-124, CWE-125, CWE-126, CWE-127        */
/*                       CWE-129, CWE-131, CWE-466, CWE-786, CWE-787, CWE-788, CWE-805, CWE-465, CWE-633, CWE-740     */
/* JV-01 Justification : To prevent overhead and excessive nesting of condition statements, this pointer has been     */
/*                       tested valid with many test cases, so there is no problem with the current implementation.   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:2824)    : Possible: Arithmetic operation on NULL pointer.                                              */
/* Rule                : CERTCCM EXP34, CWE Rule CWE-468, CWE-476, CWE-465, CWE-737                                   */
/* JV-01 Justification : To prevent overhead and excessive nesting of condition statements, this pointer has been     */
/*                       tested valid with many test cases, so there is no problem with the current implementation.   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1532)    : The function '%1s' is only referenced in one translation unit - but not the one in which it  */
/*                       is defined.                                                                                  */
/* Rule                : CERTCCM DCL19, MISRA C:2012 Rule-8.7, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : This is accepted, due to the specific coding rule, function of each hardware unit is         */
/*                       implemented in separated files for this hardware unit. Could not be static function.         */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:2934)    : Possible: Computing an invalid pointer value.                                                */
/* Rule                : CERTCCM ARR30, ARR37, ARR38, EXP08                                                           */
/* JV-01 Justification : To prevent overhead and excessive nesting of condition statements, this pointer has been     */
/*                       tested valid with many test cases, so there is no problem with the current implementation.   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (7:0404)    : More than one read access to volatile objects between sequence points.                       */
/* Rule                : CERTCCM EXP10, EXP30, MISRA C:2012 Rule-1.3, Rule-13.2                                       */
/* JV-01 Justification : This is to get elements in the global structure through the volatile global pointer. The     */
/*                       order in which it is used is not significant, so there is no problem using it.               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:2814)    : Possible: Dereference of NULL pointer.                                                       */
/* Rule                : CERTCCM EXP34, CWE Rule CWE-476, CWE-465, CWE-737, CWE-690                                   */
/* JV-01 Justification : This is accepted, due to the implementation following hardware specification.                */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (7:2755)    : Analysis time of function '%1s' has exceeded the configured maximum: '%2sms'. Dataflow       */
/*                       analysis continues with the next function.                                                   */
/* Rule                : MISRA C:2012 CMN-0.4, CERTCCM CMN-0.4, CWE Rule CMN-0.4                                      */
/* JV-01 Justification : This is depends on Hardware Specification for each module                                    */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:4461)    : A non-constant expression of 'essentially unsigned' type (%1s) is being converted to         */
/*                       narrower unsigned type, '%2s' on assignment.                                                 */
/* Rule                : MISRA-C:2012 Rule 10.3, CWE-681, CWE-136, CWE-192                                            */
/* JV-01 Justification : This operation is necessary to offset a 32-bit address on RAM to a 16-bit buffer address.    */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                             Global Data                                                            **
***********************************************************************************************************************/

#define ETH_START_SEC_CONST_32
#include "Eth_MemMap.h"

#if (ETH_REGISTER_CHECK_INITTIME == STD_ON)
/* Check pattern to check sticking registers */
STATIC CONST(Eth_ETNFCheckRWRegType, ETH_CONST)
  Eth_GaaCSRDataRW[] =                                                                                                  /* PRQA S 3218 # JV-01 */
{
  /* Register offset,            Mask,         All 0 pat,    All 1 pat    */
  { ETH_CCC,                  0x03130183UL, 0x00000001UL, 0x03010101UL },
  { ETH_DBAT,                 0xFFFFFFFFUL, 0x00000000UL, 0xFFFFFFFCUL },
  { ETH_RIMR,                 0x00000001UL, 0x00000000UL, 0x00000001UL },
  { ETH_RCR,                  0x1FFF003FUL, 0x18000000UL, 0x1FFC003FUL },
  { ETH_RQC0,                 0x73737373UL, 0x00000000UL, 0x70707070UL },
  { ETH_RQC1,                 0x73737373UL, 0x00000000UL, 0x70707070UL },
  { ETH_RQC2,                 0x73737373UL, 0x00000000UL, 0x70707070UL },
  { ETH_RQC3,                 0x73737373UL, 0x00000000UL, 0x70707070UL },
  { ETH_RQC4,                 0x73737373UL, 0x00000000UL, 0x00007070UL },
  { ETH_RPC,                  0x00FF0700UL, 0x00000100UL, 0x00FF0700UL },
  { ETH_SFO,                  0x0000003FUL, 0x00000000UL, 0x0000003FUL },
  { ETH_SFP00,                0xFFFFFFFFUL, 0x00000000UL, 0xFFFFFFFFUL },
  { ETH_SFP01,                0xFFFFFFFFUL, 0x00000000UL, 0xFFFFFFFFUL },
  { ETH_SFP02,                0xFFFFFFFFUL, 0x00000000UL, 0xFFFFFFFFUL },
  { ETH_SFP03,                0xFFFFFFFFUL, 0x00000000UL, 0xFFFFFFFFUL },
  { ETH_SFP04,                0xFFFFFFFFUL, 0x00000000UL, 0xFFFFFFFFUL },
  { ETH_SFP05,                0xFFFFFFFFUL, 0x00000000UL, 0xFFFFFFFFUL },
  { ETH_SFP06,                0xFFFFFFFFUL, 0x00000000UL, 0xFFFFFFFFUL },
  { ETH_SFP07,                0xFFFFFFFFUL, 0x00000000UL, 0xFFFFFFFFUL },
  { ETH_SFP08,                0xFFFFFFFFUL, 0x00000000UL, 0xFFFFFFFFUL },
  { ETH_SFP09,                0xFFFFFFFFUL, 0x00000000UL, 0xFFFFFFFFUL },
  { ETH_SFP10,                0xFFFFFFFFUL, 0x00000000UL, 0xFFFFFFFFUL },
  { ETH_SFP11,                0xFFFFFFFFUL, 0x00000000UL, 0xFFFFFFFFUL },
  { ETH_SFP12,                0xFFFFFFFFUL, 0x00000000UL, 0xFFFFFFFFUL },
  { ETH_SFP13,                0xFFFFFFFFUL, 0x00000000UL, 0xFFFFFFFFUL },
  { ETH_SFP14,                0xFFFFFFFFUL, 0x00000000UL, 0xFFFFFFFFUL },
  { ETH_SFP15,                0xFFFFFFFFUL, 0x00000000UL, 0xFFFFFFFFUL },
  { ETH_SFP16,                0xFFFFFFFFUL, 0x00000000UL, 0xFFFFFFFFUL },
  { ETH_SFP17,                0xFFFFFFFFUL, 0x00000000UL, 0xFFFFFFFFUL },
  { ETH_SFP18,                0xFFFFFFFFUL, 0x00000000UL, 0xFFFFFFFFUL },
  { ETH_SFP19,                0xFFFFFFFFUL, 0x00000000UL, 0xFFFFFFFFUL },
  { ETH_SFP20,                0xFFFFFFFFUL, 0x00000000UL, 0xFFFFFFFFUL },
  { ETH_SFP21,                0xFFFFFFFFUL, 0x00000000UL, 0xFFFFFFFFUL },
  { ETH_SFP22,                0xFFFFFFFFUL, 0x00000000UL, 0xFFFFFFFFUL },
  { ETH_SFP23,                0xFFFFFFFFUL, 0x00000000UL, 0xFFFFFFFFUL },
  { ETH_SFP24,                0xFFFFFFFFUL, 0x00000000UL, 0xFFFFFFFFUL },
  { ETH_SFP25,                0xFFFFFFFFUL, 0x00000000UL, 0xFFFFFFFFUL },
  { ETH_SFP26,                0xFFFFFFFFUL, 0x00000000UL, 0xFFFFFFFFUL },
  { ETH_SFP27,                0xFFFFFFFFUL, 0x00000000UL, 0xFFFFFFFFUL },
  { ETH_SFP28,                0xFFFFFFFFUL, 0x00000000UL, 0xFFFFFFFFUL },
  { ETH_SFP29,                0xFFFFFFFFUL, 0x00000000UL, 0xFFFFFFFFUL },
  { ETH_SFP30,                0xFFFFFFFFUL, 0x00000000UL, 0xFFFFFFFFUL },
  { ETH_SFP31,                0xFFFFFFFFUL, 0x00000000UL, 0xFFFFFFFFUL },
  { ETH_SFM0,                 0xFFFFFFFFUL, 0x00000000UL, 0xFFFFFFFFUL },
  { ETH_SFM1,                 0xFFFFFFFFUL, 0x00000000UL, 0xFFFFFFFFUL },
  { ETH_TGC,                  0x0033333FUL, 0x00222200UL, 0x00222230UL },
  { ETH_TCCR,                 0x0003030FUL, 0x00000000UL, 0x00010100UL },
  { ETH_CIVR0,                0xFFFFFFFFUL, 0x00000001UL, 0x0000FFFFUL },
  { ETH_CIVR1,                0xFFFFFFFFUL, 0x00000001UL, 0x0000FFFFUL },
  { ETH_CDVR0,                0xFFFFFFFFUL, 0xFFFFFFFFUL, 0xFFFF0000UL },
  { ETH_CDVR1,                0xFFFFFFFFUL, 0xFFFFFFFFUL, 0xFFFF0000UL },
  { ETH_CUL0,                 0x7FFFFFFFUL, 0x7FFFFFFFUL, 0x00000000UL },
  { ETH_CUL1,                 0x7FFFFFFFUL, 0x7FFFFFFFUL, 0x00000000UL },
  { ETH_CLL0,                 0xFFFFFFFFUL, 0x80000001UL, 0xFFFFFFFFUL },
  { ETH_CLL1,                 0xFFFFFFFFUL, 0x80000001UL, 0xFFFFFFFFUL },
  { ETH_DIC,                  0x0000FFFEUL, 0x00000000UL, 0x0000FFFEUL },
  { ETH_EIC,                  0x000007FFUL, 0x00000000UL, 0x000007FFUL },
  { ETH_RIC0,                 0x0003FFFFUL, 0x00000000UL, 0x0003FFFFUL },
  { ETH_RIC2,                 0x8003FFFFUL, 0x00000000UL, 0x8003FFFFUL },
  { ETH_TIC,                  0x000F0F0FUL, 0x00000000UL, 0x000F0F0FUL },
  { ETH_RIC3,                 0x0003FFFFUL, 0x00000000UL, 0x0003FFFFUL },
  { ETH_GCCR,                 0x0078033FUL, 0x0000002CUL, 0x0078002CUL },
  { ETH_GTI,                  0x0FFFFFFFUL, 0x00000001UL, 0x0FFFFFFFUL },
  { ETH_GTO0,                 0xFFFFFFFFUL, 0x00000000UL, 0x3FFFFFFFUL },
  { ETH_GTO1,                 0xFFFFFFFFUL, 0x00000000UL, 0xFFFFFFFFUL },
  { ETH_GTO2,                 0xFFFFFFFFUL, 0x00000000UL, 0x0000FFFFUL },
  { ETH_GIC,                  0x000003FCUL, 0x00000000UL, 0x000003FCUL },
  { ETH_ECMR,                 0x04BF0263UL, 0x00000000UL, 0x00BF0203UL },
  { ETH_RFLR,                 0x0003FFFFUL, 0x00000000UL, 0x0003FFFFUL },
  { ETH_ECSIPR,               0x0000000FUL, 0x00000000UL, 0x0000000FUL },
  { ETH_MAHR,                 0xFFFFFFFFUL, 0x00000000UL, 0xFFFFFFFFUL },
  { ETH_MALR,                 0x0000FFFFUL, 0x00000000UL, 0x0000FFFFUL }
};

/* Reset default values for read only and clear only registers */
STATIC CONST(Eth_ETNFCheckRORegType, ETH_CONST)
  Eth_GaaCSRDataRO[] =                                                                                                  /* PRQA S 3218 # JV-01 */
{
  /* Register offset,            Mask,         Default val  */
  { ETH_DLR,                  0x003FFFFFUL, 0x003FFFFFUL },
  { ETH_CSR,                  0x001F010FUL, 0x00000002UL },
  { ETH_ESR,                  0x00001F1FUL, 0x00000000UL },
  { ETH_UFCV0,                0x3F3F3F3FUL, 0x00000000UL },
  { ETH_UFCV1,                0x3F3F3F3FUL, 0x00000000UL },
  { ETH_UFCV2,                0x3F3F3F3FUL, 0x00000000UL },
  { ETH_UFCV3,                0x3F3F3F3FUL, 0x00000000UL },
  { ETH_UFCV4,                0x3F3F3F3FUL, 0x00000000UL },
  { ETH_UFCD0,                0x3F3F3F3FUL, 0x00000000UL },
  { ETH_UFCD1,                0x3F3F3F3FUL, 0x00000000UL },
  { ETH_UFCD2,                0x3F3F3F3FUL, 0x00000000UL },
  { ETH_UFCD3,                0x3F3F3F3FUL, 0x00000000UL },
  { ETH_UFCD4,                0x3F3F3F3FUL, 0x00000000UL },
  { ETH_TFA0,                 0xFFFFFFFFUL, 0x00000000UL },
  { ETH_TFA1,                 0xFFFFFFFFUL, 0x00000000UL },
  { ETH_TFA2,                 0x03FFFFFFUL, 0x00000000UL },
  { ETH_DIS,                  0x0000FFFEUL, 0x00000000UL },
  { ETH_EIS,                  0x000107FFUL, 0x00000000UL },
  { ETH_RIS0,                 0x0003FFFFUL, 0x00000000UL },
  { ETH_CEFCR,                0xFFFFFFFFUL, 0x00000000UL },
  { ETH_FRECR,                0xFFFFFFFFUL, 0x00000000UL },
  { ETH_TSFRCR,               0xFFFFFFFFUL, 0x00000000UL },
  { ETH_TLFRCR,               0xFFFFFFFFUL, 0x00000000UL },
  { ETH_RFCR,                 0xFFFFFFFFUL, 0x00000000UL },
  { ETH_MAFCR,                0xFFFFFFFFUL, 0x00000000UL },
  { ETH_DCDC,                 0xFFFFFFFFUL, 0x00000000UL }  
};
#endif /* (ETH_REGISTER_CHECK_INITTIME == STD_ON) */

#if (ETH_REGISTER_CHECK_RUNTIME == STD_ON)
/* Expected values of registers while the controller is ACTIVE */
STATIC CONST(Eth_ETNFCheckRORegType, ETH_CONST)
  Eth_GaaCBRData[] =                                                                                                    /* PRQA S 3218 # JV-01 */
{
  /* Register offset,           Mask,         Expected val */
  { ETH_RFLR,                0x00000FFFUL, (uint32)(ETH_RX_BUF_LENGTH + ETH_FCS_LENGTH) },
  { ETH_ECSIPR,              0x0000000FUL, 0x00000000UL }

};
#endif /* (ETH_REGISTER_CHECK_RUNTIME == STD_ON) */

#define ETH_STOP_SEC_CONST_32
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
**                                            Function Definitions                                                    **
***********************************************************************************************************************/
#define ETH_START_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Prottypes for register checking functions */
#if (ETH_REGISTER_CHECK_INITTIME == STD_ON)
STATIC FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_HwCheckStuckRegister(
  CONST(uint32, AUTOMATIC) LulCtrlIdx);
#endif

#if (ETH_REGISTER_CHECK_RUNTIME == STD_ON)
STATIC FUNC(void, ETH_PRIVATE_CODE) Eth_HwCheckBrokenRegister(
  CONST(uint32, AUTOMATIC) LulCtrlIdx);
#endif


STATIC FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_Hw_ETNF_EnableRamArea(
  CONST(uint32, AUTOMATIC) LulCtrlIdx);

#if (ETH_CTRL_ENABLE_MII == STD_ON) || defined(ETHAVB1)
STATIC FUNC(void, ETH_PRIVATE_CODE) Eth_WaitNanoSec(CONST(uint32, AUTOMATIC) LulNanosec);
#endif

/***********************************************************************************************************************
** Function Name         : Eth_ETNF_HwInit
**
** Service ID            : N/A
**
** Description           : Initialize a ETNF HWUnit
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulCtrlIdx     : Index of a controller
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
** Global Variable(s)    : Eth_GaaETNFRegs, Eth_GaaETNFEICRegs
**                         Eth_GaaCtrlStat, Eth_GpEthConfigPtr,Eth_GpDemEventAccess
**
** Function(s) invoked   : Eth_HwCheckStuckRegister,
**                         Eth_Hw_ETNF_DMACStructConfig,
**                         Eth_Hw_ETNF_OpModeChange, Eth_Hw_ETNF_DMACInit,
**                         Eth_Hw_ETNF_SGMIIInit, Eth_ETNF_GetElapsedTimeValue
**
** Registers Used        : EIC(INTETNFn), ETNFnMALR, ETNFnMAHR,
**                         ETNFnRFLR, ETNFnECSIPR, ETNFnRIMR, ETNFnTCCR
**
** Reference ID          : ETH_DUD_ACT_440,
** Reference ID          : ETH_DUD_ACT_440_GBL001, ETH_DUD_ACT_440_GBL002
** Reference ID          : ETH_DUD_ACT_440_GBL003, ETH_DUD_ACT_440_GBL004
** Reference ID          : ETH_DUD_ACT_440_GBL005, ETH_DUD_ACT_440_GBL006
** Reference ID          : ETH_DUD_ACT_440_GBL007, ETH_DUD_ACT_440_GBL008
** Reference ID          : ETH_DUD_ACT_440_GBL009, ETH_DUD_ACT_440_GBL010
** Reference ID          : ETH_DUD_ACT_440_GBL011, ETH_DUD_ACT_440_GBL012
** Reference ID          : ETH_DUD_ACT_440_GBL013, ETH_DUD_ACT_440_GBL014
** Reference ID          : ETH_DUD_ACT_440_GBL015, ETH_DUD_ACT_440_GBL016
** Reference ID          : ETH_DUD_ACT_440_GBL017, ETH_DUD_ACT_440_REG001
** Reference ID          : ETH_DUD_ACT_440_REG002, ETH_DUD_ACT_440_REG003
** Reference ID          : ETH_DUD_ACT_440_REG004, ETH_DUD_ACT_440_REG005
** Reference ID          : ETH_DUD_ACT_440_REG006, ETH_DUD_ACT_440_REG008
** Reference ID          : ETH_DUD_ACT_440_REG009, ETH_DUD_ACT_440_REG010
** Reference ID          : ETH_DUD_ACT_440_REG011, ETH_DUD_ACT_440_REG012
***********************************************************************************************************************/
FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_ETNF_HwInit(                                                                 /* PRQA S 3006 # JV-01 */
  CONST(uint32, AUTOMATIC) LulCtrlIdx)
{
  Std_ReturnType LucResult;
  uint32 LulRegVal;
  TickType LulTimeOutCountInit;
  TickType LulTimeoutCountElap;

  Eth_GaaCtrlStat[LulCtrlIdx].stHwStatEtnf.enDevStatus = ETH_UNINIT;                                                    
  LulRegVal = Eth_GaaETNFRegs[LulCtrlIdx]->ulCCC & ETH_ETNF_CCC_OPC_MASK;                                               

  if (ETH_ETNF_CCC_OPC_OPERATION == LulRegVal)
  {
    Eth_GaaETNFRegs[LulCtrlIdx]->ulCCC |= ETH_ETNF_CCC_DTSR;

    LulTimeOutCountInit = 0UL;
    LulTimeoutCountElap = 0UL;
    (void)GetCounterValue(ETH_OS_COUNTER_ID, &LulTimeOutCountInit);
    do
    {
      LulTimeoutCountElap = LulTimeoutCountElap + Eth_ETNF_GetElapsedTimeValue(&LulTimeOutCountInit);                   /* PRQA S 3383 # JV-01 */
      LulRegVal = Eth_GaaETNFRegs[LulCtrlIdx]->ulCSR & ETH_ETNF_CSR_DTS;
    } while ((LulRegVal != ETH_ETNF_CSR_DTS) && (LulTimeoutCountElap <= ETH_TIMEOUT_COUNT));
  }
  else
  {
    /* HW UM does not require anything for transition from Operation mode to other than Reset mode. */
  }

  #if (ETH_REGISTER_CHECK_INITTIME == STD_ON)
  /* Reset a controller before the register checking */
  (void)Eth_Hw_ETNF_OpModeChange(LulCtrlIdx, ETH_RESET);
  LucResult = Eth_Hw_ETNF_OpModeChange(LulCtrlIdx, ETH_CONFIG);

  if (E_OK == LucResult)
  {
    /* Check whether registers are not stucked */
    LucResult = Eth_HwCheckStuckRegister(LulCtrlIdx);
  }
  else
  {
    /* No action required */
  }

  if (E_NOT_OK == LucResult)
  {
    /* Return immediately */
  }
  else
  #endif
  {
    /* Initialize AVB DMAC Configuration Structure */
    Eth_Hw_ETNF_DMACStructConfig(LulCtrlIdx);

    /* Initialize Statistics */
    #if (ETH_GET_TX_STATS_API == STD_ON || ETH_GET_RX_STATS_API == STD_ON)
    Eth_GaaCtrlStat[LulCtrlIdx].stTxRxStat.ulStatsBroadcastPkts = 0UL;                                                  
    Eth_GaaCtrlStat[LulCtrlIdx].stTxRxStat.ulRxStatsPkts = 0UL;                                                         
    Eth_GaaCtrlStat[LulCtrlIdx].stTxRxStat.ulRxStatsOctets = 0UL;                                                       
    Eth_GaaCtrlStat[LulCtrlIdx].stTxRxStat.ulRxStatsPkts64Octets = 0UL;                                                 
    Eth_GaaCtrlStat[LulCtrlIdx].stTxRxStat.ulRxStatsPkts65to127Octets = 0UL;                                            
    Eth_GaaCtrlStat[LulCtrlIdx].stTxRxStat.ulRxStatsPkts128to255Octets = 0UL;                                           
    Eth_GaaCtrlStat[LulCtrlIdx].stTxRxStat.ulRxStatsPkts256to511Octets = 0UL;                                           
    Eth_GaaCtrlStat[LulCtrlIdx].stTxRxStat.ulRxStatsPkts512to1023Octets = 0UL;                                          
    Eth_GaaCtrlStat[LulCtrlIdx].stTxRxStat.ulRxStatsPkts1024to1518Octets = 0UL;                                         
    Eth_GaaCtrlStat[LulCtrlIdx].stTxRxStat.ulRxUnicastFrames = 0UL;                                                     
    Eth_GaaCtrlStat[LulCtrlIdx].stTxRxStat.ulTxNumberOfOctets = 0UL;                                                    
    Eth_GaaCtrlStat[LulCtrlIdx].stTxRxStat.ulTxNUcastPkts = 0UL;                                                        
    Eth_GaaCtrlStat[LulCtrlIdx].stTxRxStat.ulTxUniCastPkts = 0UL;                                                       
    #endif

    #if (ETH_REGISTER_CHECK_RUNTIME == STD_ON)
    /* Initialize error flag */
    Eth_GaaCtrlStat[LulCtrlIdx].stHwStatEtnf.ulECMRCopy = 0UL;                                                          
    Eth_GaaCtrlStat[LulCtrlIdx].stHwStatEtnf.blErrDetected = ETH_FALSE;                                                 
    Eth_GaaCtrlStat[LulCtrlIdx].stHwStatEtnf.blErrReported = ETH_FALSE;                                                 
    #endif

    /* Change mode to ETH_RESET mode */
    (void)Eth_Hw_ETNF_OpModeChange(LulCtrlIdx, ETH_RESET);

    /* Change mode to ETH_CONFIG mode */
    LucResult = Eth_Hw_ETNF_OpModeChange(LulCtrlIdx, ETH_CONFIG);

    if (E_OK == LucResult)
    {
      /* configure MAC */
      /* Set MAC address */
      /************ Little Endian Core **************/
      /* Write into MALR */
      Eth_GaaETNFRegs[LulCtrlIdx]->ulMALR = Eth_GaaCtrlStat[LulCtrlIdx].stMacAddr.ulL16;                                
      /* Write into MAHR */
      Eth_GaaETNFRegs[LulCtrlIdx]->ulMAHR = Eth_GaaCtrlStat[LulCtrlIdx].stMacAddr.ulH32;

      /*********** Big Endian ***********************/
      /* V2H */

      /* Set the receive frame length including the FCS length */
      Eth_GaaETNFRegs[LulCtrlIdx]->ulRFLR = (uint32)(ETH_RX_BUF_LENGTH + ETH_FCS_LENGTH);

      /* set MAC interrupt */
      Eth_GaaETNFRegs[LulCtrlIdx]->ulECSIPR = 0UL;
      /* for RMII speed setting */
      if (ETH_RMII == Eth_GpEthConfigPtr[LulCtrlIdx].enEthPHYInterface)                                           /* PRQA S 3416 # JV-01 */
      {
        Eth_GaaETNFRegs[LulCtrlIdx]->ulRIMR = (uint32)Eth_GpEthConfigPtr[LulCtrlIdx].enEthSpeed;
      }
      else
      {
        /* No action required */
      }

      /* for T1s timestamp setting */
      if (ETH_T1S_MODE == Eth_GpEthConfigPtr[LulCtrlIdx].enEthDuplex)                                                   /* PRQA S 3416 # JV-01 */
      {
        Eth_GaaETNFRegs[LulCtrlIdx]->ulRIMR = (ETH_ETND_TSEL_TIMESTAMP_T1S << 2UL);
      }
      else
      {
        /* No action required */
      }

      /* configure DMAC */
      Eth_Hw_ETNF_DMACInit(LulCtrlIdx);

      /* configure interrupt */
      /* In 4.2.2, Eth_Hw_ETNF_InterruptEnable is called inside API Eth_Init.
         According to ticket ARDAAAJ-1354, critical section is not used
         in Eth_Init. */
      if ((ETH_ENABLE == Eth_GpEthConfigPtr[LulCtrlIdx].enTxInterruptMode) ||                                           /* PRQA S 3416 # JV-01 */
        (ETH_ENABLE == Eth_GpEthConfigPtr[LulCtrlIdx].enRxInterruptMode))                                               /* PRQA S 3415, 3416 # JV-01, JV-01 */
      {
        /* Enable transmit/receive interrupt */
        /* Since EICnEIMK exists in the lower 8 bits, there is no problem casting to uint8. */
        RH850_SV_MODE_ICR_AND(8, &Eth_GaaETNFEICRegs[LulCtrlIdx]->usDATA, (uint8)(~ETH_EIC_EIMK_MASK));                 /* PRQA S 0751, 3464 # JV-01, JV-01 */
      }
      else
      {
        /* No action required */
      }

      #if (ETH_GLOBAL_TIME_SUPPORT == STD_ON)
      /* Enable management interrupt */
      /* Since EICnEIMK exists in the lower 8 bits, there is no problem casting to uint8. */
      RH850_SV_MODE_ICR_AND(8, &Eth_GaaETNFEICRegs[LulCtrlIdx]->usMNG, (uint8)(~ETH_EIC_EIMK_MASK));                    /* PRQA S 0751, 3464 # JV-01, JV-01 */
      #endif /* (ETH_GLOBAL_TIME_SUPPORT == STD_ON) */

      /* Enable error interrupt */
      /* Since EICnEIMK exists in the lower 8 bits, there is no problem casting to uint8. */
      RH850_SV_MODE_ICR_AND(8, &Eth_GaaETNFEICRegs[LulCtrlIdx]->usERR, (uint8)(~ETH_EIC_EIMK_MASK));                    /* PRQA S 0751, 3464 # JV-01, JV-01 */

      RH850_SV_MODE_REG_READ_ONLY(16, &Eth_GaaETNFEICRegs[LulCtrlIdx]->usERR);
      EXECUTE_SYNCP();                                                                                                  /* PRQA S 1006 # JV-01 */

      #if (ETH_GLOBAL_TIME_SUPPORT == STD_ON)
      /* Select the peripheral bus clock for gPTP clock */
      Eth_GaaETNFRegs[LulCtrlIdx]->ulCCC |= ETH_ETNF_CCC_CSEL_PTP_CLK_SRC;
      /* enable Time Stamping */
      Eth_GaaETNFRegs[LulCtrlIdx]->ulTCCR |= ETH_ETNF_TCCR_TFEN;
      #endif
    }
    else
    {
      /* No action required */
    }
  }
  return LucResult;
}

/***********************************************************************************************************************
** Function Name         : Eth_ETNF_HwDisableController
**
** Service ID            : N/A
**
** Description           : Changes the state of an ETNF controller as DOWN
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
** Return parameter      : E_OK : Success
**                         E_NOT_OK : Failure
**
** Preconditions         : None
**
** Global Variable(s)    : Eth_GaaCtrlStat, Eth_GaaETNFRegs
**
** Function(s) invoked   : Eth_Hw_ETNF_DisableController, Eth_Hw_ETNF_OpModeChange,
**                         Eth_ETNF_FindTxBufferHandler, Eth_ReleaseTxBuffer,
**
** Registers Used        : ETNFnCCC, ETNFnCSR, ETNFnECMR
**
** Reference ID          : ETH_DUD_ACT_441,
** Reference ID          : ETH_DUD_ACT_441_GBL005, ETH_DUD_ACT_441_GBL006
** Reference ID          : ETH_DUD_ACT_441_GBL007, ETH_DUD_ACT_441_GBL008
** Reference ID          : ETH_DUD_ACT_441_GBL009
***********************************************************************************************************************/
FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_ETNF_HwDisableController(                                                    
  CONST(uint32, AUTOMATIC) LulCtrlIdx)
{
  uint16 LusInc;
  Std_ReturnType LucErrorValue;
  P2CONST(Eth_BufHandlerType, AUTOMATIC, ETH_APPL_DATA) LpBufHandlerPtr;

  LucErrorValue = Eth_Hw_ETNF_DisableController(LulCtrlIdx);

  /* Reset all Buffer Locks or pending Transmit */
  if (E_OK == LucErrorValue)
  {
    for (LusInc = 0U; LusInc < ETH_TX_DESC_MAX; LusInc++)
    {
      LpBufHandlerPtr = Eth_ETNF_FindTxBufferHandler(LulCtrlIdx, (uint32)LusInc);
      if (NULL_PTR != LpBufHandlerPtr)
      {
        Eth_ETNF_ReleaseTxBuffer(LulCtrlIdx, LusInc);
      }
      else
      {
        /* No action required */
      }
    }

    for (LusInc = 0U; LusInc < ETH_TXQ_NUM; LusInc++)
    {
      Eth_GaaCtrlStat[LulCtrlIdx].stHwStatEtnf.aaBufTxCnt[LusInc] = 0UL;                                                
    }

    if (ETH_MODE_DOWN != Eth_GaaCtrlStat[LulCtrlIdx].enMode)                                                            
    {
      /* Set operating mode to standby mode */
      LucErrorValue = Eth_Hw_ETNF_OpModeChange(LulCtrlIdx, ETH_STANDBY);
    }
    else
    {
      /* No action required */
    }

    #if (ETH_REGISTER_CHECK_RUNTIME == STD_ON)
    /* Reset error flag */
    Eth_GaaCtrlStat[LulCtrlIdx].stHwStatEtnf.ulECMRCopy = Eth_GaaETNFRegs[LulCtrlIdx]->ulECMR;                          
    Eth_GaaCtrlStat[LulCtrlIdx].stHwStatEtnf.blErrDetected = ETH_FALSE;                                                 
    Eth_GaaCtrlStat[LulCtrlIdx].stHwStatEtnf.blErrReported = ETH_FALSE;                                                 
    #endif
  }
  else
  {
    Eth_GaaCtrlStat[LulCtrlIdx].enMode = ETH_MODE_ACTIVE;                                                               
  }

  return LucErrorValue;
}

/***********************************************************************************************************************
** Function Name         : Eth_ETNF_HwEnableController
**
** Service ID            : N/A
**
** Description           : Changes the state of an ETNF controller as ACTIVE
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulCtrlIdx     : Index of a controller
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
** Global Variable(s)    : Eth_GpCtrlConfigPtr, Eth_GaaCtrlStat
**                         Eth_GaaETNFRegs, Eth_GaaRxConfig
**
** Function(s) invoked   : Eth_Hw_ETNF_OpModeChange, Eth_Hw_ETNF_EnableRamArea
**                         Eth_Hw_ETNF_DescConfig, Eth_Hw_ETNF_RxDescChainConfig
**                         Eth_ETNF_HwSetIncrementTimeForGptp, Eth_ETNF_GetElapsedTimeValue
**
** Registers Used        : ETNFnECMR, ETNFnMALR, ETNFnMAHR
**
** Reference ID          : ETH_DUD_ACT_442,
** Reference ID          : ETH_DUD_ACT_442_GBL008, ETH_DUD_ACT_442_REG002
** Reference ID          : ETH_DUD_ACT_442_REG003, ETH_DUD_ACT_442_REG004
***********************************************************************************************************************/
FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_ETNF_HwEnableController(CONST(uint32, AUTOMATIC) LulCtrlIdx)                 
{
  #if (ETH_GLOBAL_TIME_SUPPORT == STD_ON)
  TickType LulTimeOutCountInit;
  TickType LulTimeoutCountElap;
  uint32 LulIncrementValue;
  Std_ReturnType LulIncrementResult;
  #endif
  P2CONST(Eth_ETNFConfigType, AUTOMATIC, ETH_APPL_DATA) LpHwUnitConfig;
  uint32 LulQCount;
  uint8 LucQidx;
  Std_ReturnType LucReturnValue;
  uint32 LulECMRVal;

  LpHwUnitConfig =
    (P2CONST(Eth_ETNFConfigType, AUTOMATIC, ETH_APPL_DATA))Eth_GpCtrlConfigPtr[LulCtrlIdx].pHwUnitConfig;               /* PRQA S 0316 # JV-01 */

  /* Entering Operation mode, must enter Config mode.  */
  LucReturnValue = Eth_Hw_ETNF_OpModeChange(LulCtrlIdx, ETH_CONFIG);
  if (E_OK == LucReturnValue)
  {
    LucReturnValue = Eth_Hw_ETNF_EnableRamArea(LulCtrlIdx);
  }
  else
  {
    /* No action required */
  }
  if (E_OK == LucReturnValue)
  {
    /* Configure Tx and Rx Descriptor chain */
    Eth_Hw_ETNF_DescConfig(LulCtrlIdx);

    /* Initialize variable */
    LulQCount = 0UL;

    do
    {
      LucQidx = LpHwUnitConfig->stQueueConfig.pRxQueueConfig[LulQCount].ucEthRxQueueId;                                 

      (void)Eth_Hw_ETNF_RxDescChainConfig(LulCtrlIdx, &(Eth_GaaRxConfig[LucQidx]));                                     
      LulQCount++;                                                                                                      /* PRQA S 3383 # JV-01 */
    } while (LulQCount < (uint32)LpHwUnitConfig->stQueueConfig.ucNumberOfRxQueue);
    if (ETH_T1S_MODE == Eth_GpEthConfigPtr[LulCtrlIdx].enEthDuplex)                                                     /* PRQA S 3416 # JV-01 */
    {
       /* Set MAC mode as T1S mode and enable Rx/Tx */
      LulECMRVal = ETH_ETNF_ECMR_DM_T1S | ETH_ETNF_ECMR_RE_TE;
      /* Set CRS assert check in T1S mode*/
      #if (ETH_CRS_ASSERT_CHECK == STD_OFF)
      {
       LulECMRVal |= ETH_ETNF_ECMR_ZPF_CRS_NOT_CHECKED;
      }
      #endif
    }
    else
    {
       /* Set MAC mode as Full-duplex mode and enable Rx/Tx */
       LulECMRVal = ETH_ETNF_ECMR_DM_FULL_DUPLEX | ETH_ETNF_ECMR_RE_TE;
    }
    
    

    /* Set MAC address */
    /************ Little Endian Core **************/
    /* Write into MALR */
    Eth_GaaETNFRegs[LulCtrlIdx]->ulMALR = Eth_GaaCtrlStat[LulCtrlIdx].stMacAddr.ulL16;                                  

    /* Write into MAHR */
    Eth_GaaETNFRegs[LulCtrlIdx]->ulMAHR = Eth_GaaCtrlStat[LulCtrlIdx].stMacAddr.ulH32;

    /*********** Big Endian ***********************/
    /* V2H */
    #if (ETH_UPDATE_PHYS_ADDR_FILTER == STD_ON)
    if (ETH_TRUE == Eth_GaaCtrlStat[LulCtrlIdx].blPromiscuous)
    {
      LulECMRVal |= ETH_ETNF_ECMR_PRM;
    }
    else
    {
      LulECMRVal &= ~ETH_ETNF_ECMR_PRM;                                                                                 /* PRQA S 2985 # JV-01 */
    }
    #endif

    Eth_GaaETNFRegs[LulCtrlIdx]->ulECMR = LulECMRVal;

    #if (ETH_REGISTER_CHECK_RUNTIME == STD_ON)
    /* Backup ECMR register value for the verification */
    Eth_GaaCtrlStat[LulCtrlIdx].stHwStatEtnf.ulECMRCopy = LulECMRVal;                                                   
    #endif

    /* Set Pulse Generation Mode */
    #if (ETH_PPS_CORRECTED_GPTP == STD_ON)
      Eth_GaaETNFRegs[LulCtrlIdx]->ulGCCR = ETH_ETNF_GCCR_PGM;
    #endif /* (ETH_PPS_CORRECTED_GPTP == STD_ON) */

    /* Set operating mode to operation mode */
    LucReturnValue = Eth_Hw_ETNF_OpModeChange(LulCtrlIdx, ETH_OPERATION);

    #if (ETH_GLOBAL_TIME_SUPPORT == STD_ON)
    /* Set gPTP.TIC if TIMESTAMP is selected */
    LulIncrementValue = ETH_HZ2NS(ETH_PERI_CLOCK_HZ);                                                                   /* PRQA S 3469 # JV-01 */
    LulIncrementValue = ETH_ETNF_SET_GTI_TIV(LulIncrementValue);                                                        /* PRQA S 3469 # JV-01 */
    /* Set Increment into HW */
    LulTimeOutCountInit = 0UL;
    LulTimeoutCountElap = 0UL;
    (void)GetCounterValue(ETH_OS_COUNTER_ID, &LulTimeOutCountInit);
    do
    {
      LulTimeoutCountElap = LulTimeoutCountElap + Eth_ETNF_GetElapsedTimeValue(&LulTimeOutCountInit);                   /* PRQA S 3383 # JV-01 */
      LulIncrementResult = Eth_ETNF_HwSetIncrementTimeForGptp(LulCtrlIdx, LulIncrementValue);
    } while ((LulIncrementResult != E_OK) && (LulTimeoutCountElap <= ETH_TIMEOUT_COUNT));
    LucReturnValue |= LulIncrementResult;
    #endif /* (ETH_GLOBAL_TIME_SUPPORT == STD_ON) */
  }
  else
  {
    /* No action required */
  }

  return LucReturnValue;
}

/***********************************************************************************************************************
** Function Name         : Eth_ETNF_HwTransmit
**
** Service ID            : N/A
**
** Description           : Initiates a transmission on an ETNF controller.
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
** Global Variable(s)    : None
**
** Function(s) invoked   : Eth_FindTxBufferHandler,
**                         Eth_Hw_ETNF_SingleDescFrameSend
**                         ETH_ENTER_CRITICAL_SECTION, ETH_EXIT_CRITICAL_SECTION
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_443,
** Reference ID          : ETH_DUD_ACT_443_CRT001, ETH_DUD_ACT_443_CRT002
***********************************************************************************************************************/
FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_ETNF_HwTransmit(                                                             
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulBufIdx,
  CONST(uint32, AUTOMATIC) LulLenByte, CONST(boolean, AUTOMATIC) LblConfirmation)
{
  Std_ReturnType LucReturnValue;
  P2VAR(Eth_BufHandlerType, AUTOMATIC, ETH_APPL_DATA) LpBufHandlerPtr;                                                  /* PRQA S 3432 # JV-01 */

  ETH_ENTER_CRITICAL_SECTION(ETH_RAM_DATA_PROTECTION);

  /* Find Tx buffer handler */
  LpBufHandlerPtr = Eth_ETNF_FindTxBufferHandler(LulCtrlIdx, LulBufIdx);

  ETH_EXIT_CRITICAL_SECTION(ETH_RAM_DATA_PROTECTION);

  /* Set Tx request length */
  LpBufHandlerPtr->ulTxLength = (uint32)ETH_HEADER_SIZE + LulLenByte;                                                   /* PRQA S 3383 # JV-01 */

  /* Set Tx confirmation flag */
  LpBufHandlerPtr->blTxConfirm = LblConfirmation;

  /* Transmit request */
  LucReturnValue = Eth_Hw_ETNF_SingleDescFrameSend(LulCtrlIdx, LpBufHandlerPtr);

  return LucReturnValue;
}

/***********************************************************************************************************************
** Function Name         : Eth_ETNF_HwTxConfirmation
**
** Service ID            : N/A
**
** Description           : Performs transmission processing, notifies the upper layer
**                         of transmission completion and releases the Tx buffer.
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
** Global Variable(s)    : Eth_GaaETNFRegs, Eth_GaaCtrlStat
**
** Function(s) invoked   : Eth_FindTxBufferHandler, Eth_ReleaseTxBuffer,
**                         EthIf_TxConfirmation, EthSwt_EthTxFinishedIndication
**                         ETH_ENTER_CRITICAL_SECTION, ETH_EXIT_CRITICAL_SECTION
**
** Registers Used        : ETNFnDIS
**
** Reference ID          : ETH_DUD_ACT_444,
** Reference ID          : ETH_DUD_ACT_444_CRT001, ETH_DUD_ACT_444_CRT002
** Reference ID          : ETH_DUD_ACT_444_GBL001, ETH_DUD_ACT_444_GBL002
** Reference ID          : ETH_DUD_ACT_444_GBL003, ETH_DUD_ACT_444_GBL004
** Reference ID          : ETH_DUD_ACT_444_GBL005, ETH_DUD_ACT_444_GBL007
** Reference ID          : ETH_DUD_ACT_444_REG001
***********************************************************************************************************************/
FUNC(void, ETH_PRIVATE_CODE) Eth_ETNF_HwTxConfirmation(                                                                 
  CONST(uint32, AUTOMATIC) LulCtrlIdx)
{
  uint32 LulQIdx;
  uint32 LulCnt;
  uint32 LulTxCnt;
  uint32 LulBufIdx;
  P2VAR(Eth_DataDescType, AUTOMATIC, ETH_APPL_DATA) LpDataDesc;                                                         /* PRQA S 3432 # JV-01 */
  P2CONST(Eth_BufHandlerType, AUTOMATIC, ETH_APPL_DATA) LpBufHandlerPtr;
  #if (ETH_GET_TX_STATS_API == STD_ON)
  Eth_MacAddressType LstMacAddr;
  #endif

  /* Get and clear descriptor interrupt status */
  Eth_GaaETNFRegs[LulCtrlIdx]->ulDIS = ~Eth_GaaETNFRegs[LulCtrlIdx]->ulDIS;                                             

  /* Check the status of the tx descriptor */
  for (LulQIdx = 0UL; LulQIdx < (uint32)ETH_TXQ_NUM; LulQIdx++)
  {
    /* Get on-transmit count */
    LulTxCnt = Eth_GaaCtrlStat[LulCtrlIdx].stHwStatEtnf.aaBufTxCnt[LulQIdx];                                            
    LpDataDesc = (Eth_DataDescType *)Eth_GaaCtrlStat[LulCtrlIdx].stHwStatEtnf.aaHeadTxDesc[LulQIdx];                    /* PRQA S 0306 # JV-01 */
    for (LulCnt = 0UL; LulCnt < LulTxCnt; LulCnt++)
    {
      if (ETH_DESC_FEMPTY_AVB != LpDataDesc->stHeader.ulDt)                                                             
      {
        /* Transmit not completed yet */
        break;
      }
      else
      {
        /* No action required */
      }

      /* Get Tx buffer handler */
      LulBufIdx = (uint32)((LpDataDesc->stHeader.ulCtrl) & ETH_DESCR_TAG_MASK);
      LpBufHandlerPtr = Eth_GaaTxBufferIndex[LulCtrlIdx][LulBufIdx].pBufferHdr;                                         

      #if (ETH_GET_TX_STATS_API == STD_ON)
      Eth_GaaCtrlStat[LulCtrlIdx].stTxRxStat.ulTxNumberOfOctets += LpBufHandlerPtr->ulTxLength;                         /* PRQA S 3383 # JV-01 */
      ETH_PACK_ADDRESS_FROM_8(((uint8 *)LpBufHandlerPtr->ulbufAddr), LstMacAddr);                                       /* PRQA S 0306, 3469 # JV-01, JV-01 */
      if ((0UL == ETH_COMPARE_MAC(LstMacAddr, Eth_GstBroadcastAddr))                                                    /* PRQA S 3469 # JV-01 */
          || (0UL != ETH_CHECK_MULTICAST(LstMacAddr)))                                                                  /* PRQA S 3469 # JV-01 */
      {
        Eth_GaaCtrlStat[LulCtrlIdx].stTxRxStat.ulTxNUcastPkts++;                                                        /* PRQA S 3383 # JV-01 */
      }
      else
      {
        Eth_GaaCtrlStat[LulCtrlIdx].stTxRxStat.ulTxUniCastPkts++;                                                       /* PRQA S 3383 # JV-01 */
      }
      #endif

      /* Check whether the transmission confirmation was enabled */
      if (ETH_TRUE == LpBufHandlerPtr->blTxConfirm)                                                                     
      {
        /* Call the callback function */
        /* Since the maximum value of controller index is 1, casting to uint8 does no problem. */
        EthIf_TxConfirmation((uint8)LulCtrlIdx, (Eth_BufIdxType)LpBufHandlerPtr->ulbufIdx, E_OK);
      }
      else
      {
        /* No action required */
      }

      #if (ETH_ETHSWITCH_MANAGEMENT_SUPPORT == STD_ON)
      /* Indication for a finished transmit process for a specific Ethernet frame. */
      /* Since the maximum value of controller index is 1, casting to uint8 does no problem. */
      (void)EthSwt_EthTxFinishedIndication((uint8)LulCtrlIdx, (Eth_BufIdxType)LpBufHandlerPtr->ulbufIdx);
      #endif

      ETH_ENTER_CRITICAL_SECTION(ETH_RAM_DATA_PROTECTION);

      /* Release the tx buffer resource */
      Eth_ETNF_ReleaseTxBuffer(LulCtrlIdx, LpBufHandlerPtr->ulbufIdx);

      /* Clear tx descriptor */
      LpDataDesc->stHeader.ulDie = 0U;
      LpDataDesc->stHeader.ulCtrl = 0U;
      LpDataDesc->stHeader.ulDs = 0U;
      LpDataDesc->ulDptr = 0U;

      /* Decrease the number of on-transmission buffer of current Tx queue */
      Eth_GaaCtrlStat[LulCtrlIdx].stHwStatEtnf.aaBufTxCnt[LulQIdx]--;                                                   /* PRQA S 3383 # JV-01 */

      ETH_EXIT_CRITICAL_SECTION(ETH_RAM_DATA_PROTECTION);

      /* Update start descriptor */
      LpDataDesc++;                                                                                                     
      while ((LpDataDesc->stHeader.ulDt == ETH_DESC_LINKFIX) || (LpDataDesc->stHeader.ulDt == ETH_DESC_LINK_AVB))       
      {
        LpDataDesc = (Eth_DataDescType *)LpDataDesc->ulDptr;                                                            /* PRQA S 0306 # JV-01 */
      }
      Eth_GaaCtrlStat[LulCtrlIdx].stHwStatEtnf.aaHeadTxDesc[LulQIdx] = (uint32)LpDataDesc;                              /* PRQA S 0306 # JV-01 */
    }
  }
}

#if (ETH_CTRL_ENABLE_RX_POLLING == STD_ON)
/***********************************************************************************************************************
** Function Name         : Eth_ETNF_HwReceive
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
**                         LulQueueIdx     : Index of a Fifo
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
** Global Variable(s)    : None
**
** Function(s) invoked   : Eth_Hw_ETNF_UFCounterGet, Eth_Hw_ETNF_RxQueueProcess
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_445
***********************************************************************************************************************/
FUNC(Eth_RxStatusType, ETH_PRIVATE_CODE) Eth_ETNF_HwReceive(                                                            
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulQueueIdx)
{
  uint32 LulCnt;
  uint32 LulUnreadFrameCnt;
  boolean LblQueueValid;
  Eth_RxStatusType LenRetValue;

  /* Initialize receive status */
  LenRetValue = ETH_NOT_RECEIVED;

  /* Read UFCV from the LulCtrlIdx and LulQueueIdx */
  LulUnreadFrameCnt = Eth_Hw_ETNF_UFCounterGet(LulCtrlIdx, LulQueueIdx);

  for (LulCnt = 0UL; LulCnt < LulUnreadFrameCnt; LulCnt++)
  {
    LblQueueValid = Eth_Hw_ETNF_RxQueueProcess(LulCtrlIdx, (uint8)LulQueueIdx);
    if (ETH_TRUE == LblQueueValid)
    {
      /* A frame is processed, decrease the counter */
      LulUnreadFrameCnt = LulUnreadFrameCnt - LulCnt;                                                                   /* PRQA S 3383 # JV-01 */
      if (1UL < LulUnreadFrameCnt)
      {
        /* More frames are available */
        LenRetValue = ETH_RECEIVED_MORE_DATA_AVAILABLE;
      }
      else
      {
        /* Frame valid - Update status */
        LenRetValue = ETH_RECEIVED;
      }
      break;
    }
    else
    {
      /* No action required */
    }
  }

  return LenRetValue;
}

/***********************************************************************************************************************
** Function Name         : Eth_ETNF_HwCheckFifoIndex
**
** Service ID            : N/A
**
** Description           : Check the validity of the FIFO index specified
**                         in the Eth_Receive.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LulCtrlIdx     : Index of a controller
**                         LulQueueIdx     : the FIFO index
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : LucReturnValue E_OK / E_NOT_OK
**
** Preconditions         : None
**
** Global Variable(s)    : None
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_446
***********************************************************************************************************************/
FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_ETNF_HwCheckFifoIndex(                                                       
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulQueueIdx)
{
  Std_ReturnType LucReturnValue;

  (void)LulCtrlIdx;

  LucReturnValue = E_OK;

  /* Validity check for the FIFO index */
  if (ETH_RXQ_NUM <= LulQueueIdx)
  {
    LucReturnValue = E_NOT_OK;
  }
  else
  {
    /* No action required */
  }

  return LucReturnValue;
}
#endif /* (ETH_CTRL_ENABLE_RX_POLLING == STD_ON) */

#if (ETH_CTRL_ENABLE_MII == STD_ON)
/***********************************************************************************************************************
** Function Name         : Eth_HwReadMiiBit (ETNF)
**
** Service ID            : N/A
**
** Description           : Read one bit from the PHY management interface
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
** Return parameter      : Result bit (0 or 1)
**
** Preconditions         : None
**
** Global Variable(s)    : Eth_GaaETNFRegs
**
** Function(s) invoked   : Eth_WaitNanoSec
**
** Registers Used        : ETNFnPIR, ETNFnECSR
**
** Reference ID          : ETH_DUD_ACT_447, ETH_DUD_ACT_447_REG001,
** Reference ID          : ETH_DUD_ACT_447_REG002
***********************************************************************************************************************/
FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_HwReadMiiBit(                                                                /* PRQA S 3006 # JV-01 */
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONSTP2VAR(uint16, AUTOMATIC, ETH_APPL_DATA) LpRegValPtr)                        /* PRQA S 3432 # JV-01 */
{
  TickType LulTimeOutCountInit;
  TickType LulTimeoutCountElap;
  Std_ReturnType LucResult;

  *LpRegValPtr = ETH_ETNF_GET_MDI(Eth_GaaETNFRegs[LulCtrlIdx]->ulPIR);                                                  /* PRQA S 3469, 4461 # JV-01, JV-01 */

  Eth_GaaETNFRegs[LulCtrlIdx]->ulPIR = ETH_ETNF_PIR_MDC;
  EXECUTE_SYNCP();                                                                                                      /* PRQA S 1006 # JV-01 */
  Eth_WaitNanoSec(ETH_MDIO_SETUP_TIME + ETH_ETNF_WORST_SLEW_RATE);
  Eth_GaaETNFRegs[LulCtrlIdx]->ulPIR = 0UL;
  EXECUTE_SYNCP();                                                                                                      /* PRQA S 1006 # JV-01 */
  Eth_WaitNanoSec(ETH_MDIO_SETUP_TIME + ETH_ETNF_WORST_SLEW_RATE);

  /* Wait until ECSR.ICD returns to 0 */
  LulTimeOutCountInit = 0UL;
  LulTimeoutCountElap = 0UL;
  (void)GetCounterValue(ETH_OS_COUNTER_ID, &LulTimeOutCountInit);
  do
  {
    LulTimeoutCountElap = LulTimeoutCountElap + Eth_ETNF_GetElapsedTimeValue(&LulTimeOutCountInit);                     /* PRQA S 3383 # JV-01 */
  } while (((Eth_GaaETNFRegs[LulCtrlIdx]->ulECSR & ETH_ETNF_ECSR_ICD_MASK) != 0UL)
                                && (LulTimeoutCountElap <= ETH_TIMEOUT_COUNT));

  if (ETH_TIMEOUT_COUNT < LulTimeoutCountElap)
  {
    LucResult = E_NOT_OK;
  }
  else
  {
    LucResult = E_OK;
  }
  return LucResult;
}

/***********************************************************************************************************************
** Function Name         : Eth_HwWriteMiiBit (ETNF)
**
** Service ID            : N/A
**
** Description           : Write one bit to the PHY management interface
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : LulCtrlIdx     : Index of a controller
**                         LulBit         : a bit to be written (0 or 1)
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variable(s)    : Eth_GaaETNFRegs
**
** Function(s) invoked   : Eth_WaitNanoSec
**
** Registers Used        : ETNFnPIR, ETNFnECSR
**
** Reference ID          : ETH_DUD_ACT_448, ETH_DUD_ACT_448_REG001
** Reference ID          : ETH_DUD_ACT_448_REG002, ETH_DUD_ACT_448_REG003
***********************************************************************************************************************/
FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_HwWriteMiiBit(                                                               /* PRQA S 3006 # JV-01 */
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulBit)
{
  TickType LulTimeOutCountInit;
  TickType LulTimeoutCountElap;
  Std_ReturnType LucResult;
  CONST(uint32, AUTOMATIC) LulMDO = ETH_ETNF_PIR_MMD | (ETH_ETNF_PIR_MDO * LulBit);                                     /* PRQA S 3383 # JV-01 */

  Eth_GaaETNFRegs[LulCtrlIdx]->ulPIR = LulMDO;                                                                          
  EXECUTE_SYNCP();                                                                                                      /* PRQA S 1006 # JV-01 */
  Eth_WaitNanoSec(ETH_MDIO_SETUP_TIME + ETH_ETNF_WORST_SLEW_RATE);

  Eth_GaaETNFRegs[LulCtrlIdx]->ulPIR = LulMDO | ETH_ETNF_PIR_MDC;
  EXECUTE_SYNCP();                                                                                                      /* PRQA S 1006 # JV-01 */
  Eth_WaitNanoSec(ETH_MDIO_SETUP_TIME + ETH_ETNF_WORST_SLEW_RATE);

  Eth_GaaETNFRegs[LulCtrlIdx]->ulPIR = LulMDO;
  EXECUTE_SYNCP();                                                                                                      /* PRQA S 1006 # JV-01 */
  Eth_WaitNanoSec(ETH_ETNF_WORST_SLEW_RATE);

  /* Wait until ECSR.ICD returns to 0 */
  LulTimeOutCountInit = 0UL;
  LulTimeoutCountElap = 0UL;
  (void)GetCounterValue(ETH_OS_COUNTER_ID, &LulTimeOutCountInit);
  do
  {
    LulTimeoutCountElap = LulTimeoutCountElap + Eth_ETNF_GetElapsedTimeValue(&LulTimeOutCountInit);                     /* PRQA S 3383 # JV-01 */
  } while (((Eth_GaaETNFRegs[LulCtrlIdx]->ulECSR & ETH_ETNF_ECSR_ICD_MASK) != 0UL)
                                && (LulTimeoutCountElap <= ETH_TIMEOUT_COUNT));

  if (ETH_TIMEOUT_COUNT < LulTimeoutCountElap)
  {
    LucResult = E_NOT_OK;
  }
  else
  {
    LucResult = E_OK;
  }

  return LucResult;

}
#endif /* (ETH_CTRL_ENABLE_MII == STD_ON) */

#if (ETH_GET_COUNTER_VALUES_API == STD_ON)
/***********************************************************************************************************************
** Function Name         : Eth_ETNF_HwGetCounterValues
**
** Service ID            : N/A
**
** Description           : Get drop frame counts for each error factor
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : LulCtrlIdx: Index of a controller
**
** InOut Parameters      : None
**
** Output Parameters     : LpCounterPtr: Drop frame counter information
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variable(s)    : Eth_GaaETNFRegs
**
** Function(s) invoked   : None
**
** Registers Used        : ETNFnFRECR, ETNFnCEFCR, ETNFnTSFRCR, ETNFnTLFRCR,
**                         ETNFnRFCR
**
** Reference ID          : ETH_DUD_ACT_449
***********************************************************************************************************************/
FUNC(void, ETH_PRIVATE_CODE) Eth_ETNF_HwGetCounterValues(                                                               
  CONST(uint32, AUTOMATIC) LulCtrlIdx,
  CONSTP2VAR(Eth_CounterType, AUTOMATIC, ETH_APPL_DATA) LpCounterPtr)                                                   /* PRQA S 3432 # JV-01 */
{
  /* Statistics Available */
  LpCounterPtr->DropPktBufOverrun = Eth_GaaETNFRegs[LulCtrlIdx]->ulFRECR;                                               
  LpCounterPtr->DropPktCrc = Eth_GaaETNFRegs[LulCtrlIdx]->ulCEFCR;
  LpCounterPtr->UndersizePkt = Eth_GaaETNFRegs[LulCtrlIdx]->ulTSFRCR;
  LpCounterPtr->OversizePkt = Eth_GaaETNFRegs[LulCtrlIdx]->ulTLFRCR;
  LpCounterPtr->AlgnmtErr = Eth_GaaETNFRegs[LulCtrlIdx]->ulRFCR;
  LpCounterPtr->SqeTestErr = ETH_NOT_AVAILABLE;
  LpCounterPtr->DiscInbdPkt = ETH_NOT_AVAILABLE;
  LpCounterPtr->ErrInbdPkt = ETH_NOT_AVAILABLE;
  LpCounterPtr->DiscOtbdPkt = ETH_NOT_AVAILABLE;
  LpCounterPtr->ErrOtbdPkt = ETH_NOT_AVAILABLE;
  LpCounterPtr->SnglCollPkt = ETH_NOT_AVAILABLE;
  LpCounterPtr->MultCollPkt = ETH_NOT_AVAILABLE;
  LpCounterPtr->DfrdPkt = ETH_NOT_AVAILABLE;
  LpCounterPtr->LatCollPkt = Eth_GaaETNFRegs[LulCtrlIdx]->ulDCDC;
  LpCounterPtr->HwDepCtr0 = ETH_NOT_AVAILABLE;
  LpCounterPtr->HwDepCtr1 = ETH_NOT_AVAILABLE;
  LpCounterPtr->HwDepCtr2 = ETH_NOT_AVAILABLE;
  LpCounterPtr->HwDepCtr3 = ETH_NOT_AVAILABLE;
}
#endif /* (ETH_GET_COUNTER_VALUES_API == STD_ON) */

#if (ETH_GET_RX_STATS_API == STD_ON)
/***********************************************************************************************************************
** Function Name         : Eth_ETNF_HwGetRxStats (ETNF)
**
** Service ID            : N/A
**
** Description           : Get Rx statistics information
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : LulCtrlIdx     : Index of a controller
**
** InOut Parameters      : None
**
** Output Parameters     : LpRxStats: Rx statistics counter information
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variable(s)    : Eth_GaaCtrlStat, Eth_GaaETNFRegs
**
** Function(s) invoked   : None
**
** Registers Used        : ETNFnMAFCR, ETNFnCEFCR, ETNFnRFCR, ETNFnTSFRCR,
**                         ETNFnTLFRCR
**
** Reference ID          : ETH_DUD_ACT_450
***********************************************************************************************************************/
FUNC(void, ETH_PRIVATE_CODE) Eth_ETNF_HwGetRxStats(                                                                     
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONSTP2VAR(Eth_RxStatsType, AUTOMATIC, ETH_APPL_DATA) LpRxStats)                 /* PRQA S 3432 # JV-01 */
{
  /* Rx Drop Events */
  LpRxStats->RxStatsDropEvents = ETH_NOT_AVAILABLE;                                                                     

  /* Rx Stats Fragments */
  LpRxStats->RxStatsFragments  = ETH_NOT_AVAILABLE;

  /* Rx Stats Jabbers */
  LpRxStats->RxStatsJabbers    = ETH_NOT_AVAILABLE;

  /* Rx Stats Collisions */
  LpRxStats->RxStatsCollisions = ETH_NOT_AVAILABLE;

  /* Rx Octet Counter */
  LpRxStats->RxStatsOctets = Eth_GaaCtrlStat[LulCtrlIdx].stTxRxStat.ulRxStatsOctets;                                    

  /* Rx Packet Counter */
  LpRxStats->RxStatsPkts = Eth_GaaCtrlStat[LulCtrlIdx].stTxRxStat.ulRxStatsPkts;

  /* Rx Broadcast Counter */
  LpRxStats->RxStatsBroadcastPkts = Eth_GaaCtrlStat[LulCtrlIdx].stTxRxStat.ulStatsBroadcastPkts;

  /* Rx 64 Octets */
  LpRxStats->RxStatsPkts64Octets = Eth_GaaCtrlStat[LulCtrlIdx].stTxRxStat.ulRxStatsPkts64Octets;

  /* Rx 65-127 Octets */
  LpRxStats->RxStatsPkts65to127Octets = Eth_GaaCtrlStat[LulCtrlIdx].stTxRxStat.ulRxStatsPkts65to127Octets;

  /* Rx 128-255 Octets */
  LpRxStats->RxStatsPkts128to255Octets = Eth_GaaCtrlStat[LulCtrlIdx].stTxRxStat.ulRxStatsPkts128to255Octets;

  /* Rx 256-511 Octets */
  LpRxStats->RxStatsPkts256to511Octets = Eth_GaaCtrlStat[LulCtrlIdx].stTxRxStat.ulRxStatsPkts256to511Octets;

  /* Rx 512-1023 Octets */
  LpRxStats->RxStatsPkts512to1023Octets = Eth_GaaCtrlStat[LulCtrlIdx].stTxRxStat.ulRxStatsPkts512to1023Octets;

  /* Rx 1024-1518 Octets */
  LpRxStats->RxStatsPkts1024to1518Octets = Eth_GaaCtrlStat[LulCtrlIdx].stTxRxStat.ulRxStatsPkts1024to1518Octets;

  /* Rx unicast frames */
  LpRxStats->RxUnicastFrames = Eth_GaaCtrlStat[LulCtrlIdx].stTxRxStat.ulRxUnicastFrames;

  /* Multicast Frame Counter */
  LpRxStats->RxStatsMulticastPkts = Eth_GaaETNFRegs[LulCtrlIdx]->ulMAFCR;                                               

  /* Crc + Alignment Error Counter  */
  LpRxStats->RxStatsCrcAlignErrors = Eth_GaaETNFRegs[LulCtrlIdx]->ulCEFCR;
  LpRxStats->RxStatsCrcAlignErrors += Eth_GaaETNFRegs[LulCtrlIdx]->ulRFCR;                                              /* PRQA S 3384 # JV-01 */

  /* Too Short Frames Counter */
  LpRxStats->RxStatsUndersizePkts = Eth_GaaETNFRegs[LulCtrlIdx]->ulTSFRCR;

  /* Too Long Frames Counter  */
  LpRxStats->RxStatsOversizePkts = Eth_GaaETNFRegs[LulCtrlIdx]->ulTLFRCR;
}
#endif /* (ETH_GET_RX_STATS_API == STD_ON) */

#if (ETH_GET_TX_STATS_API == STD_ON)
/***********************************************************************************************************************
** Function Name         : Eth_ETNF_HwGetTxStats
**
** Service ID            : N/A
**
** Description           : Get Tx statistics information
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : LulCtrlIdx     : Index of a controller
**
** InOut Parameters      : None
**
** Output Parameters     : LpTxStats: Tx statistics counter information
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variable(s)    : Eth_GaaCtrlStat
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_451
***********************************************************************************************************************/
FUNC(void, ETH_PRIVATE_CODE) Eth_ETNF_HwGetTxStats(                                                                     
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONSTP2VAR(Eth_TxStatsType, AUTOMATIC, ETH_APPL_DATA) LpTxStats)                 /* PRQA S 3432 # JV-01 */
{
  /* Tx Octet Counter */
  LpTxStats->TxNumberOfOctets = Eth_GaaCtrlStat[LulCtrlIdx].stTxRxStat.ulTxNumberOfOctets;                              

  /* Tx Not Unicast Packet Counter */
  LpTxStats->TxNUcastPkts = Eth_GaaCtrlStat[LulCtrlIdx].stTxRxStat.ulTxNUcastPkts;

  /* Tx Unicast Packet Counter */
  LpTxStats->TxUniCastPkts = Eth_GaaCtrlStat[LulCtrlIdx].stTxRxStat.ulTxUniCastPkts;
}
#endif /* (ETH_GET_TX_STATS_API == STD_ON) */

#if (ETH_GET_TX_ERROR_COUNTER_VALUES_API == STD_ON)
/***********************************************************************************************************************
** Function Name         : Eth_ETNF_HwGetTxErrorCounterValues (ETNF)
**
** Service ID            : N/A
**
** Description           : Get error statuses
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : LulCtrlIdx     : Index of a controller
**
** InOut Parameters      : None
**
** Output Parameters     : LpTxErrorCounterValues: Tx error counter information
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
** Reference ID          : ETH_DUD_ACT_452
***********************************************************************************************************************/
FUNC(void, ETH_PRIVATE_CODE) Eth_ETNF_HwGetTxErrorCounterValues(                                                        
  CONST(uint32, AUTOMATIC) LulCtrlIdx,
  CONSTP2VAR(Eth_TxErrorCounterValuesType, AUTOMATIC, ETH_APPL_DATA) LpTxErrorCounterValues)                            /* PRQA S 3432 # JV-01 */
{
  (void)LulCtrlIdx;

  /* This HW is cannot get Tx error statistics */
  LpTxErrorCounterValues->TxDroppedNoErrorPkts = ETH_NOT_AVAILABLE;                                                     
  LpTxErrorCounterValues->TxDroppedErrorPkts = ETH_NOT_AVAILABLE;
  LpTxErrorCounterValues->TxDeferredTrans = ETH_NOT_AVAILABLE;
  LpTxErrorCounterValues->TxSingleCollision = ETH_NOT_AVAILABLE;
  LpTxErrorCounterValues->TxLateCollision = Eth_GaaETNFRegs[LulCtrlIdx]->ulDCDC;                                        
  LpTxErrorCounterValues->TxExcessiveCollison = ETH_NOT_AVAILABLE;
}
#endif /* (ETH_GET_TX_ERROR_COUNTER_VALUES_API == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Eth_ETNF_HwMainFunction
**
** Service ID            : N/A
**
** Description           : Check receive errors and report DEM if exist
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variable(s)    : Eth_GaaETNFRegs, Eth_GpDemEventRxFramesLost, Eth_GpDemEventCRC,
**                         Eth_GpDemEventUnderSizeFrame, Eth_GpDemEventOverSizeFrame,
**                         Eth_GpDemEventAlignment
**
** Function(s) invoked   : Eth_DemConfigCheck, Eth_HwCheckBrokenRegister
**
** Registers Used        : ETNFnFRECR, ETNFnCEFCR, ETNFnTSFRCR, ETNFnTLFRCR, ETNFnRFCR
**
** Reference ID          : ETH_DUD_ACT_453,
** Reference ID          : ETH_DUD_ACT_453_ERR001, ETH_DUD_ACT_453_ERR002
** Reference ID          : ETH_DUD_ACT_453_ERR003, ETH_DUD_ACT_453_ERR004
** Reference ID          : ETH_DUD_ACT_453_ERR005
***********************************************************************************************************************/
FUNC(void, ETH_PRIVATE_CODE) Eth_ETNF_HwMainFunction(CONST(uint32, AUTOMATIC) LulCtrlIdx)                               
{
  /* Report Extended DEM (if any) */

  /* Read FRECR - Rx Frame Lost Counter */
  if (0UL < Eth_GaaETNFRegs[LulCtrlIdx]->ulFRECR)                                                                       
  {
    /* Call DEM */
    Eth_DemConfigCheck(Eth_GpDemEventRxFramesLost[LulCtrlIdx], DEM_EVENT_STATUS_PREFAILED);                             
  }
  else
  {
    /* No action required */
  }
  /* Read CEFCR - CRC Error Counter */
  if (0UL < Eth_GaaETNFRegs[LulCtrlIdx]->ulCEFCR)
  {
    /* Call DEM */
    Eth_DemConfigCheck(Eth_GpDemEventCRC[LulCtrlIdx], DEM_EVENT_STATUS_PREFAILED);                                      
  }
  else
  {
    /* No action required */
  }
  /* Read TSFRCR - Too Short Frame Counter */
  if (0UL < Eth_GaaETNFRegs[LulCtrlIdx]->ulTSFRCR)
  {
    /* Call DEM */
    Eth_DemConfigCheck(Eth_GpDemEventUnderSizeFrame[LulCtrlIdx], DEM_EVENT_STATUS_PREFAILED);                           
  }
  else
  {
    /* No action required */
  }
  /* Read TLFRCR - Too Long Frames Counter */
  if (0UL < Eth_GaaETNFRegs[LulCtrlIdx]->ulTLFRCR)
  {
    /* Call DEM */
    Eth_DemConfigCheck(Eth_GpDemEventOverSizeFrame[LulCtrlIdx], DEM_EVENT_STATUS_PREFAILED);                            
  }
  else
  {
    /* No action required */
  }
  /*Read RFCR - Frame Alignment Error Counter */
  if (0UL < Eth_GaaETNFRegs[LulCtrlIdx]->ulRFCR)
  {
    /* Call DEM */
    Eth_DemConfigCheck(Eth_GpDemEventAlignment[LulCtrlIdx], DEM_EVENT_STATUS_PREFAILED);                                
  }
  else
  {
    /* No action required */
  }
  #if (ETH_REGISTER_CHECK_RUNTIME == STD_ON)
  /* Verify whether registers are not corrupted */
  Eth_HwCheckBrokenRegister(LulCtrlIdx);
  #endif
}

#if (ETH_REGISTER_CHECK_INITTIME == STD_ON)
/***********************************************************************************************************************
** Function Name         : Eth_HwCheckStuckRegister (ETNF)
**
** Service ID            : N/A
**
** Description           : Check whether relevant registers can be written
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
** Return parameter      : Std_ReturnType
**                         E_OK: No error was detected.
**                         E_NOT_OK: Any of errors were detected.
**
** Preconditions         : Controller must be DOWN and the state never changed
**                         during this function.
**
** Global Variable(s)    : Eth_GaaCSRDataRW, Eth_GaaCSRDataRO, Eth_GaaETNFRegs
**                         Eth_GpDemEventRegisterCorruption
**
** Function(s) invoked   : Eth_DemConfigCheck
**
** Registers Used        : See Eth_GaaCSRDataRW and Eth_GaaCSRDataRO
**
** Reference ID          : ETH_DUD_ACT_454,
** Reference ID          : ETH_DUD_ACT_454_ERR001, ETH_DUD_ACT_454_REG001
** Reference ID          : ETH_DUD_ACT_454_REG002
***********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_HwCheckStuckRegister(
  CONST(uint32, AUTOMATIC) LulCtrlIdx)
{
  Std_ReturnType LucResult;
  uint32 LulIndex;
  uint32 LulResult;
  P2VAR(volatile uint32, AUTOMATIC, REGSPACE) LpReg;

  /* Intialize the register error check result */
  LulResult = 0UL;

  /* Confirm R/W registers can be written with arbitrary value */
  for (LulIndex = 0UL; LulIndex < (uint32)(sizeof(Eth_GaaCSRDataRW) / sizeof(Eth_ETNFCheckRWRegType)); LulIndex++)
  {
    LpReg = &Eth_GaaETNFRegs[LulCtrlIdx]->ulCCC + (Eth_GaaCSRDataRW[LulIndex].ulOffset / (uint32)sizeof(uint32));       /* PRQA S 0488 # JV-01 */

    /* Write test pattern 1 */
    *LpReg = Eth_GaaCSRDataRW[LulIndex].ulWritePattern1;                                                                
    /* Accumulate the diff between the result and the expected value */
    LulResult |= ((*LpReg ^ Eth_GaaCSRDataRW[LulIndex].ulWritePattern1) & Eth_GaaCSRDataRW[LulIndex].ulMaskValue);
    /* Write test pattern 0 */
    *LpReg = Eth_GaaCSRDataRW[LulIndex].ulWritePattern0;
    /* Accumulate the diff between the result and the expected value */
    LulResult |= ((*LpReg ^ Eth_GaaCSRDataRW[LulIndex].ulWritePattern0) & Eth_GaaCSRDataRW[LulIndex].ulMaskValue);
  }

  /* Confirm Read-Only and Clear-Only regiters have the default value */
  for (LulIndex = 0UL; LulIndex < (uint32)(sizeof(Eth_GaaCSRDataRO) / sizeof(Eth_ETNFCheckRORegType)); LulIndex++)
  {
    LpReg = &Eth_GaaETNFRegs[LulCtrlIdx]->ulCCC + (Eth_GaaCSRDataRO[LulIndex].ulOffset / (uint32)sizeof(uint32));       /* PRQA S 0488 # JV-01 */

    /* Accumulate the diff between the result and the expected value */
    LulResult |= ((*LpReg ^ Eth_GaaCSRDataRO[LulIndex].ulExpectedValue) & Eth_GaaCSRDataRO[LulIndex].ulMaskValue);      
  }

  /* If any register didn't have the expected value, report DEM */
  if (0UL != LulResult)
  {
    Eth_DemConfigCheck(Eth_GpDemEventRegisterCorruption[LulCtrlIdx], DEM_EVENT_STATUS_FAILED);                          
    LucResult = E_NOT_OK;
  }
  else
  {
    LucResult = E_OK;
  }

  return LucResult;
}
#endif /* (ETH_REGISTER_CHECK_INITTIME == STD_ON) */

#if (ETH_REGISTER_CHECK_RUNTIME == STD_ON)
/***********************************************************************************************************************
** Function Name         : Eth_HwCheckBrokenRegister (ETNF)
**
** Service ID            : N/A
**
** Description           : Check whether relevant registers have not been
**                         corrupted
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
** Preconditions         : Controller must be ACTIVE and the state never changed
**                         during this function.
**
** Global Variable(s)    : Eth_GaaCBRData, Eth_GaaETNFRegs, Eth_GaaCtrlStat
**                         Eth_GpDemEventRegisterCorruption
**
** Function(s) invoked   : Eth_DemConfigCheck
**
** Registers Used        : See Eth_GaaCBRData
**
** Reference ID          : ETH_DUD_ACT_455,
** Reference ID          : ETH_DUD_ACT_455_ERR001, ETH_DUD_ACT_455_GBL001
** Reference ID          : ETH_DUD_ACT_455_GBL002
***********************************************************************************************************************/
STATIC FUNC(void, ETH_PRIVATE_CODE) Eth_HwCheckBrokenRegister(
  CONST(uint32, AUTOMATIC) LulCtrlIdx)
{
  uint32 LulIndex;
  uint32 LulResult;
  P2VAR(volatile uint32, AUTOMATIC, REGSPACE) LpReg;                                                                    /* PRQA S 3678 # JV-01 */

  /* Intialize the register error check result */
  LulResult = 0UL;

  /* Check registers which have const values */
  for (LulIndex = 0UL; LulIndex < (uint32)(sizeof(Eth_GaaCBRData) / sizeof(Eth_ETNFCheckRORegType)); LulIndex++)
  {
    LpReg = &Eth_GaaETNFRegs[LulCtrlIdx]->ulCCC + (Eth_GaaCBRData[LulIndex].ulOffset / (uint32)sizeof(uint32));         /* PRQA S 0488 # JV-01 */

    LulResult |= ((*LpReg ^ Eth_GaaCBRData[LulIndex].ulExpectedValue) & Eth_GaaCBRData[LulIndex].ulMaskValue);          
  }

  /* Confirm ECMR has not been changed */
  LulResult |= ((Eth_GaaETNFRegs[LulCtrlIdx]->ulECMR ^ Eth_GaaCtrlStat[LulCtrlIdx].stHwStatEtnf.ulECMRCopy)             
    & ETH_ETNF_ECMR_CHECK_MASK);

  /* Confirm MAC address registers have not been changed */
  LulResult |= (Eth_GaaETNFRegs[LulCtrlIdx]->ulMAHR ^ Eth_GaaCtrlStat[LulCtrlIdx].stMacAddr.ulH32);
  LulResult |= (Eth_GaaETNFRegs[LulCtrlIdx]->ulMALR ^ Eth_GaaCtrlStat[LulCtrlIdx].stMacAddr.ulL16);

  /* If any register didn't have the expected value, set the error flag */
  if (0UL != LulResult)
  {
    Eth_GaaCtrlStat[LulCtrlIdx].stHwStatEtnf.blErrDetected = ETH_TRUE;                                                  
  }
  else
  {
    /* No action required */
  }

  /* If any error has been detected and not reported yet, report DEM */
  if ((ETH_TRUE == Eth_GaaCtrlStat[LulCtrlIdx].stHwStatEtnf.blErrDetected) &&                                           
    (ETH_FALSE == Eth_GaaCtrlStat[LulCtrlIdx].stHwStatEtnf.blErrReported))
  {
    Eth_DemConfigCheck(Eth_GpDemEventRegisterCorruption[LulCtrlIdx], DEM_EVENT_STATUS_FAILED);                          
    /* Set already reported flag to prevent repeated reports */
    Eth_GaaCtrlStat[LulCtrlIdx].stHwStatEtnf.blErrReported = ETH_TRUE;                                                  
  }
  else
  {
    /* No action required */
  }
}
#endif /* (ETH_REGISTER_CHECK_RUNTIME == STD_ON) */

#if (ETH_GLOBAL_TIME_SUPPORT == STD_ON)
/***********************************************************************************************************************
** Function Name         : Eth_ETNF_HwGetCurrentTime
**
** Service ID            : NA
**
** Description           : Return TimeStamp from the HW register
**                         previously started.
**                       : It returns adjusted gPTP timer value (TCSS = 01)
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : LulCtrlIdx     : Index of a controller
**
** InOut Parameters      : None
**
** Output Parameters     : LpTimeQualPtr  : Quality of the HW TimeStamp returned
**                       : LpTimeStampPtr : Current TimeStamp value
**
** Return parameter      : LucReturnValue E_OK / E_NOT_OK
**
** Preconditions         : Component Requires previous controller
**                         initialization using Eth_ControllerInit..
**
** Global Variable(s)    : Eth_GaaETNFRegs
**
** Function(s) invoked   : Eth_Hw_ETNF_WaitPTPRequestIsComplete
**
** Registers Used        : ETNFnCCC, ETNFnGCCR, ETNFnGCT0, ETNFnGCT1, ETNFnGCT2
**
** Reference ID          : ETH_DUD_ACT_456,
** Reference ID          : ETH_DUD_ACT_456_REG001, ETH_DUD_ACT_456_REG002
***********************************************************************************************************************/
FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_ETNF_HwGetCurrentTime(                                                       
  CONST(uint32, AUTOMATIC) LulCtrlIdx,
  CONSTP2VAR(Eth_TimeStampQualType, AUTOMATIC, ETH_APPL_DATA) LpTimeQualPtr,                                            /* PRQA S 3432 # JV-01 */
  CONSTP2VAR(Eth_TimeStampType, AUTOMATIC, ETH_APPL_DATA) LpTimeStampPtr)                                               /* PRQA S 3432 # JV-01 */
{
  /* ucReturnValue = Eth_Hw_ETNF_GetPTPTime(LulCtrlIdx, timeQualPtr, timeStampPtr); */
  Std_ReturnType LucReturnValue;

  if ((0UL != (Eth_GaaETNFRegs[LulCtrlIdx]->ulCCC & ETH_ETNF_CCC_CSEL_MASK)) &&                                         
    (0UL == (Eth_GaaETNFRegs[LulCtrlIdx]->ulGCCR & ETH_GPTP_CAPTURE_MASK)))
  {
    /* There is a clock to gPTP and no Active Time Request */
    /* Set Source as gPTP Timer value TCSS = 01 */
    Eth_GaaETNFRegs[LulCtrlIdx]->ulGCCR =
      (Eth_GaaETNFRegs[LulCtrlIdx]->ulGCCR & ~ETH_ETNF_GCCR_TCSS_MASK) | ETH_ETNF_GCCR_TCSS_ADJUSTED_GPTP;

    /* Set GCCR.TCR = 11 */
    Eth_GaaETNFRegs[LulCtrlIdx]->ulGCCR |= ETH_ETNF_GCCR_TCR_CAP_START;

    /* Wait for GCCR.TCR = 00 */
    LucReturnValue = Eth_Hw_ETNF_WaitPTPRequestIsComplete(LulCtrlIdx, ETH_ETNF_GCCR_TCR_MASK);

    if (E_OK == LucReturnValue)
    {
      /* Timeout Not Occurred - Return Valid TimeStamp */
      *LpTimeQualPtr = ETH_VALID;                                                                                       
      LucReturnValue = E_OK;
    }
    else
    {
      /* Timeout !!! - Return Not valid TimeStamp  */
      *LpTimeQualPtr = ETH_INVALID;
      LucReturnValue = E_NOT_OK;
    }
  }
  else
  {
    *LpTimeQualPtr = ETH_INVALID;
    LucReturnValue = E_NOT_OK;
  }

  if (ETH_VALID == *LpTimeQualPtr)
  {
    LpTimeStampPtr->nanoseconds = Eth_GaaETNFRegs[LulCtrlIdx]->ulGCT[0];                                                
    LpTimeStampPtr->seconds     = Eth_GaaETNFRegs[LulCtrlIdx]->ulGCT[1];
    /* In ETNFnGCT2, only the lower 16 bits are valid, casting to uint16 does no problem. */
    LpTimeStampPtr->secondsHi   = (uint16) Eth_GaaETNFRegs[LulCtrlIdx]->ulGCT[2];
  }
  else
  {
    /* Return 0 as TS */
    LpTimeStampPtr->nanoseconds = (uint32)0x0U;
    LpTimeStampPtr->seconds     = (uint32)0x0U;
    LpTimeStampPtr->secondsHi   = (uint16)0x0U;
  }

  return (LucReturnValue);

}

/***********************************************************************************************************************
** Function Name         : Eth_ETNF_HwGetEgressTimeStamp
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
** Return parameter      : None
**
** Preconditions         : Component Requires previous controller
**                         initialization using Eth_ControllerInit..
**
** Global Variable(s)    : Eth_GaaTxBufferIndex
**
** Function(s) invoked   : ETH_ENTER_CRITICAL_SECTION, ETH_EXIT_CRITICAL_SECTION
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_457
** Reference ID          : ETH_DUD_ACT_457_CRT001, ETH_DUD_ACT_457_CRT002
***********************************************************************************************************************/

FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_ETNF_HwGetEgressTimeStamp(                                                   
  CONST(uint32, AUTOMATIC) LulCtrlIdx,
  CONST(Eth_BufIdxType, AUTOMATIC) LulBufIdx,
  CONSTP2VAR(Eth_TimeStampQualType, AUTOMATIC, ETH_APPL_DATA) LpTimeQualPtr,                                            /* PRQA S 3432 # JV-01 */
  CONSTP2VAR(Eth_TimeStampType, AUTOMATIC, ETH_APPL_DATA) LpTimeStampPtr)                                               /* PRQA S 3432 # JV-01 */
{
  P2VAR(Eth_TxBufferType, AUTOMATIC, ETH_APPL_DATA) LpTxBuffer;                                                         /* PRQA S 3432 # JV-01 */

  /* Critical section is required to protect updating of enTimeQual from MNG interrupt
     during getting egress time stamp in buffer. */
  ETH_ENTER_CRITICAL_SECTION(ETH_RAM_DATA_PROTECTION);

  /* Initialize pointer to timestamp buffer */
  LpTxBuffer = (Eth_TxBufferType *)&Eth_GaaTxBufferIndex[LulCtrlIdx][LulBufIdx];                                        

  *LpTimeQualPtr = LpTxBuffer->enTimeQual;                                                                              

  *LpTimeStampPtr = LpTxBuffer->stTimeStamp;                                                                            

  LpTxBuffer->enTimeQual = ETH_INVALID;

  ETH_EXIT_CRITICAL_SECTION(ETH_RAM_DATA_PROTECTION);

  return (E_OK);
}

/***********************************************************************************************************************
** Function Name         : Eth_ETNF_HwGetIngressTimeStamp
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
** Return parameter      : None
**
** Preconditions         : Component Requires previous controller
**                         initialization using Eth_ControllerInit..
**
** Global Variables Used : Eth_GaaRxFrame
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_458
***********************************************************************************************************************/
FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_ETNF_HwGetIngressTimeStamp(                                                  
  CONST(uint32, AUTOMATIC) LulCtrlIdx,
  CONSTP2CONST(Eth_DataType, AUTOMATIC, ETH_APPL_DATA) LpDataPtr,
  CONSTP2VAR(Eth_TimeStampQualType, AUTOMATIC, ETH_APPL_DATA) LpTimeQualPtr,                                            /* PRQA S 3432 # JV-01 */
  CONSTP2VAR(Eth_TimeStampType, AUTOMATIC, ETH_APPL_DATA) LpTimeStampPtr)                                               /* PRQA S 3432 # JV-01 */
{

  P2VAR(Eth_DataType, AUTOMATIC, ETH_APPL_DATA) LpCompPtr;                                                              /* PRQA S 3432, 3678 # JV-01, JV-01 */

  /* Read TimeStamp from the rxframe.Timestamp */
  LpCompPtr = (Eth_DataType *)(Eth_GaaRxFrame[LulCtrlIdx].ulEthTypeAddr + (uint32)ETH_ETHERTYPE_SIZE);                  /* PRQA S 0306, 3383 # JV-01, JV-01 */
  if (LpCompPtr == LpDataPtr)
  {
    LpTimeStampPtr->nanoseconds = Eth_GaaRxFrame[LulCtrlIdx].stTimestamp.ulTimestamp0;                                  
    LpTimeStampPtr->seconds = Eth_GaaRxFrame[LulCtrlIdx].stTimestamp.ulTimestamp1;
    LpTimeStampPtr->secondsHi = Eth_GaaRxFrame[LulCtrlIdx].stTimestamp.usTimestamp2;
    /* TimeStamp is valid  */
    *LpTimeQualPtr = Eth_GaaRxFrame[LulCtrlIdx].enTimeQual;                                                             
  }
  else
  {
    LpTimeStampPtr->nanoseconds = 0U;
    LpTimeStampPtr->seconds = 0U;
    LpTimeStampPtr->secondsHi = 0U;
    /* TimeStamp is invalid  */
    *LpTimeQualPtr = ETH_INVALID;
  }
  return (E_OK);
}

/***********************************************************************************************************************
** Function Name         : Eth_ETNF_HwSetIncrementTimeForGptp
**
** Service ID            : NA
**
** Description           : Set a value to GTI and issue a load request
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant for the same Ctrl ,
**                         Re-entrant for different
**
** Input Parameters      : LulCtrlIdx     : Index of a controller
**                         LulIncVal      : New increment value for the gPTP timer
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : LucReturnValue E_OK / E_NOT_OK
**
** Preconditions         : Component Requires previous controller
**                         initialization using Eth_ControllerInit..
**
** Global Variable(s)    : Eth_GaaETNFRegs, Eth_GpDemEventTimerincFailed
**
** Function(s) invoked   : Eth_Hw_ETNF_WaitPTPRequestIsComplete, Eth_DemConfigCheck
**
** Registers Used        : ETNFnCCC, ETNFnGCCR, ETNFnGTI
**
** Reference ID          : ETH_DUD_ACT_459,
** Reference ID          : ETH_DUD_ACT_459_ERR001, ETH_DUD_ACT_459_REG001
** Reference ID          : ETH_DUD_ACT_459_REG002
***********************************************************************************************************************/
FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_ETNF_HwSetIncrementTimeForGptp(
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulIncVal)
{
  uint32 LulOpMode;
  uint32 LulLoadTimeInc;
  Std_ReturnType LucReturnValue;

  LulOpMode = Eth_GaaETNFRegs[LulCtrlIdx]->ulCCC & ETH_ETNF_CCC_OPC_MASK;                                               
  LulLoadTimeInc = Eth_GaaETNFRegs[LulCtrlIdx]->ulGCCR & ETH_ETNF_GCCR_LTI;
  if (0UL == ((ETH_ETNF_CCC_OPC_OPERATION == LulOpMode) && (0UL != LulLoadTimeInc)))                                    /* PRQA S 1881 # JV-01 */
  {
    /* Set GTI */
    Eth_GaaETNFRegs[LulCtrlIdx]->ulGTI = LulIncVal;

    /* Set Request to load GTI */
    Eth_GaaETNFRegs[LulCtrlIdx]->ulGCCR |= ETH_ETNF_GCCR_LTI;

    LucReturnValue = Eth_Hw_ETNF_WaitPTPRequestIsComplete(LulCtrlIdx, ETH_ETNF_GCCR_LTI);
  }
  else
  {
    /* Another Request is pending to gPTP */
    LucReturnValue = E_NOT_OK;
  }

  /* Setting increment time into HW failed - DEM is required */
  if (E_OK == LucReturnValue)
  {
    /* No action required */
  }
  else
  {
    Eth_DemConfigCheck(Eth_GpDemEventTimerincFailed[LulCtrlIdx], DEM_EVENT_STATUS_FAILED);                              
  }

  return (LucReturnValue);
}

/***********************************************************************************************************************
** Function Name         : Eth_ETNF_HwSetOffsetTimeForGptp
**
** Service ID            : NA
**
** Description           : Adjust gPTP with an given delta
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant for the same Ctrl ,
**                         Re-entrant for different
**
** Input Parameters      : LulCtrlIdx     : Index of a controller
**                       : LpTimeOffsetPtr: Delta TimeStamp
**
** InOut Parameters      : None
**
** Output Parameters     : E_OK - gPTP Request is completed w/o timeout
**                       : E_NOT_OK - gPTP Request not completed due to timeout
**
** Return parameter      : LucReturnValue - E_OK / E_NOT_OK
**
** Preconditions         : Component Requires previous controller
**                         initialization using Eth_ControllerInit..
**
** Global Variable(s)    : Eth_GaaETNFRegs
**
** Function(s) invoked   : Eth_Hw_ETNF_WaitPTPRequestIsComplete
**
** Registers Used        : ETNFnCCC, ETNFnGTO0, ETNFnGTO1, ETNFnGTO2, ETNFnGCCR
**
** Reference ID          : ETH_DUD_ACT_460,
** Reference ID          : ETH_DUD_ACT_460_ERR001, ETH_DUD_ACT_460_REG001,
** Reference ID          : ETH_DUD_ACT_460_REG002
***********************************************************************************************************************/
FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_ETNF_HwSetOffsetTimeForGptp(                                                 
  CONST(uint32, AUTOMATIC) LulCtrlIdx,
  CONSTP2CONST(Eth_TimeStampType, AUTOMATIC, ETH_APPL_DATA) LpTimeOffsetPtr)
{
  uint32 LulOpMode;
  uint32 LulLoadTimeOffset;
  Std_ReturnType LucReturnValue;

  LulOpMode = Eth_GaaETNFRegs[LulCtrlIdx]->ulCCC & ETH_ETNF_CCC_OPC_MASK;                                               
  LulLoadTimeOffset = Eth_GaaETNFRegs[LulCtrlIdx]->ulGCCR & ETH_ETNF_GCCR_LTO;
  if (0UL == ((ETH_ETNF_CCC_OPC_OPERATION == LulOpMode) && (0UL != LulLoadTimeOffset)))                                 /* PRQA S 1881 # JV-01 */
  {
    /* Set gPTP Timer Offset */
    if (LpTimeOffsetPtr->nanoseconds > ETH_GPTP_OFFSET_NANOSEC_MAXVALUE)                                                
    {
      /* The upper limit is 0x3B9AC9FF */
      Eth_GaaETNFRegs[LulCtrlIdx]->ulGTO[0] = ETH_GPTP_OFFSET_NANOSEC_MAXVALUE;
    }
    else
    {
      Eth_GaaETNFRegs[LulCtrlIdx]->ulGTO[0] = LpTimeOffsetPtr->nanoseconds;
    }
    Eth_GaaETNFRegs[LulCtrlIdx]->ulGTO[1] = LpTimeOffsetPtr->seconds;
    Eth_GaaETNFRegs[LulCtrlIdx]->ulGTO[2] = (uint32)LpTimeOffsetPtr->secondsHi;

    /* Set Request to update GTO */
    Eth_GaaETNFRegs[LulCtrlIdx]->ulGCCR |= ETH_ETNF_GCCR_LTO;

    LucReturnValue = Eth_Hw_ETNF_WaitPTPRequestIsComplete(LulCtrlIdx, ETH_ETNF_GCCR_TCR_MASK);
  }
  else
  {
    /* Another Request is pending to gPTP */
    LucReturnValue = E_NOT_OK;
  }

  /* Setting offset time into HW failed - DEM is required */
  if (E_OK == LucReturnValue)
  {
    /* No action required */
  }
  else
  {
    Eth_DemConfigCheck(Eth_GpDemEventTimeroffsetFailed[LulCtrlIdx], DEM_EVENT_STATUS_FAILED);                           
  }

  return (LucReturnValue);
}

#endif /* (ETH_GLOBAL_TIME_SUPPORT == STD_ON) */

#if (ETH_STREAM_FILTERING == STD_ON)
#if (ETH_DEV_ERROR_DETECT == STD_ON)
/***********************************************************************************************************************
** Function Name         : Eth_HwCheckRxStreamQueueIndex (ETNF)
**
** Service ID            : N/A
**
** Description           : Check whether relevant registers have not been
**                         corrupted
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : LulCtrlIdx     : Index of a controller
**                         LulQueIdx      : Index of the receive queue
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : Controller must be ACTIVE and the state never changed
**                         during this function.
**
** Global Variable(s)    : Eth_GpCtrlConfigPtr
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_461
***********************************************************************************************************************/
FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_HwCheckRxStreamQueueIndex(                                                   
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulQueIdx)
{
  uint32 LulCnt;
  P2CONST(Eth_ETNFConfigType, AUTOMATIC, ETH_APPL_DATA) LpHwUnitConfig;
  Std_ReturnType LucReturnValue;

  LucReturnValue = E_NOT_OK;

  if ((LulQueIdx >= (uint32)ETH_RX_QUEUE_INDEX_AVAILABLE_FILTER) && (LulQueIdx < (uint32)ETH_RXQ_NUM))
  {
    LpHwUnitConfig =
      (P2CONST(Eth_ETNFConfigType, AUTOMATIC, ETH_APPL_DATA))Eth_GpCtrlConfigPtr[LulCtrlIdx].pHwUnitConfig;             /* PRQA S 0316 # JV-01 */

    /* Check the specified stream queue exists */
    for (LulCnt = 0U; LulCnt < LpHwUnitConfig->stQueueConfig.ucNumberOfRxQueue; LulCnt++)                               
    {
      if (LpHwUnitConfig->stQueueConfig.pRxQueueConfig[LulCnt].ucEthRxQueueId == LulQueIdx)                             
      {
        LucReturnValue = E_OK;
        break;
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

  return LucReturnValue;
}
#endif /* End of (ETH_DEV_ERROR_DETECT == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Eth_HwUpdateStreamFilter (ETNF)
**
** Service ID            : N/A
**
** Description           : Check whether relevant registers have not been
**                         corrupted
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : LulCtrlIdx     : Index of a controller
**                         LulQueIdx      : Index of the receive queue
**
** InOut Parameters      : None
**
** Output Parameters     : StreamIdPtr    : Update the stream id for separate filtering
**
** Return parameter      : None
**
** Preconditions         : Controller must be ACTIVE and the state never changed
**                         during this function.
**
** Global Variable(s)    : None
**
** Function(s) invoked   : Eth_Hw_ETNF_WriteIntoSFPReg
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_462
***********************************************************************************************************************/
FUNC(void, ETH_PRIVATE_CODE) Eth_HwUpdateStreamFilter(                                                                  
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulQueIdx,
  CONSTP2CONST(uint8, AUTOMATIC, ETH_APPL_DATA) StreamIdPtr)
{
  /* Since the maximum value of Rx queue index is 17, casting to uint8 does no problem. */
  Eth_Hw_ETNF_WriteIntoSFPReg(LulCtrlIdx, StreamIdPtr, (uint8)LulQueIdx);
}
#endif /* End of (ETH_STREAM_FILTERING == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Eth_Hw_ETNF_EnableRamArea
**
** Service ID            : N/A
**
** Description           : Secure the RAM area.
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
** Return parameter      : Std_ReturnType
**
** Preconditions         : None
**
** Global Variable(s)    : Eth_GaaCtrlStat, Eth_GaaMemPoolBufferTable, Eth_GaaRamSize,
**                         Eth_GaaETNFRegs,
**
** Function(s) invoked   : Eth_Ram_Init, Eth_Ram_GetNextFreeAddr, Eth_Hw_ETNF_SYS_AllocDescBuffer
**                         Eth_Hw_ETNF_RxMemAlloc, Eth_Ram_SetCircularAddr
**
** Registers Used        : ETNFnDBAT
**
** Reference ID          : ETH_DUD_ACT_463,
** Reference ID          : ETH_DUD_ACT_463_GBL001, ETH_DUD_ACT_463_REG001
***********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_Hw_ETNF_EnableRamArea(CONST(uint32, AUTOMATIC) LulCtrlIdx)
{
  Std_ReturnType LucReturnValue;

  /* URAM Base Address Init  */
  Eth_Ram_Init(LulCtrlIdx, (uint32)Eth_GaaMemPoolBufferTable[LulCtrlIdx], Eth_GaaRamSize[LulCtrlIdx]);                  /* PRQA S 0306 # JV-01 */
  /* Enable the DMAC and MAC of Controller */
  /* configure message handler */
  Eth_GaaCtrlStat[LulCtrlIdx].stHwStatEtnf.ulDescTableAddr = Eth_Ram_GetNextFreeAddr(LulCtrlIdx);                       

  /* Allocate memory for base address table and Tx,Rx descriptor chain */
  LucReturnValue = Eth_Hw_ETNF_SYS_AllocDescBuffer(LulCtrlIdx);

  if (E_OK == LucReturnValue)
  {
    /* Allocate Rx Buffers */
    LucReturnValue = Eth_Hw_ETNF_RxMemAlloc(LulCtrlIdx);
  }
  else
  {
    /* No action required */
  }

  if (E_OK == LucReturnValue)
  {
    /* Set circular address for Tx bufffers */
    Eth_Ram_SetCircularAddr(LulCtrlIdx);
    /* configure DBAT register */
    Eth_GaaETNFRegs[LulCtrlIdx]->ulDBAT = Eth_GaaCtrlStat[LulCtrlIdx].stHwStatEtnf.ulDescTableAddr;                     
  }
  else
  {
    /* No action required */
  }

  return LucReturnValue;
}

#if (ETH_CTRL_ENABLE_MII == STD_ON) || defined(ETHAVB1)
/***********************************************************************************************************************
** Function Name         : Eth_WaitNanoSec
**
** Service ID            : NA
**
** Description           : Wait for the specified nanosecond.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulNanosec     : Waiting time (nano sec)
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
** Reference ID          : ETH_DUD_ACT_464
***********************************************************************************************************************/
STATIC FUNC(void, ETH_PRIVATE_CODE) Eth_WaitNanoSec(CONST(uint32, AUTOMATIC) LulNanosec)
{
  CONST(uint32, AUTOMATIC) LulCycle = ETH_NS2HZ_AVB(LulNanosec) + 1UL;                                                  /* PRQA S 3469, 3383 # JV-01, JV-01 */
  volatile uint32 LulCount;

  for (LulCount = 0UL; LulCount < LulCycle; LulCount++)                                                                 /* PRQA S 3416, 3387 # JV-01, JV-01 */
  {
    /* No action required */
  }
}
#endif /* (ETH_CTRL_ENABLE_MII == STD_ON) || defined(ETHAVB1) */

#define ETH_STOP_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* (ETH_MACRO_ETNF == STD_ON) */

/***********************************************************************************************************************
**                                                End of File                                                         **
***********************************************************************************************************************/
