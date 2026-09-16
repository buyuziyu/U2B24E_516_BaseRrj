/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Eth_ETNE_LLDriver.c                                                                                 */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2024, 2025 Renesas Electronics Corporation. All rights reserved.                                               */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains ETNE specific operations of Eth Driver Component.                                               */
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
 * 2.4.1: 30/06/2025    : Change ETH_TOTAL_CTRL_CONFIG to ETH_ETNE_CTRLS_SUPPORTED
 *                      : Remove the SW-VERSION from header of file
 * 2.4.0: 30/06/2025    : Update SW-VERSION for RH850/Ver22.01.00 (D) U2Ax release
 * 2.3.1: 31/03/2025    : Change pointer to address to pointer for selection interrupt in Eth_InterruptHandling
 :                      : Added setting reference internal clock into Eth_SGMIIInit
 *                      : Change precompile Eth_Gwca_TSDIS_Common_Isr by ETH_GWCA0_TSDATA_ISR macro
 *                      : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 * 2.3.0: 28/02/2025    : - As per ticket ARDAACJ-695:
 *                        + Update to provide correct support for the function Eth_GetTimeOutValue and 
 *                        change the name to Eth_GetElapsedTimeValue
 *                        + Update the impact on the functions: Eth_HwMFWD_Layer3TableResetFlow, 
 *                        Eth_HwMFWD_MacTableResetFlow, Eth_HwMFWD_VlanTableResetFlow, 
 *                        Eth_HwMFWD_Layer2Layer3UpdateTableResetFlow, Eth_HwMFWD_GateRamResetFlow, 
 *                        Eth_HwGWCA_ModeTransitionFlow, Eth_HwGWCA_MulticastTableResetFlow, 
 *                        Eth_HwGWCA_AxiRamResetFlow, Eth_HwETHA_ModeTransitionFlow, 
 *                        Eth_HwETHA_TasRamResetFlow, Eth_HwETHA_TasSettingFlow, 
 *                        Eth_HwETHA_TasDisablingFlow, Eth_HwETHA_TasEntryILearnFlow, 
 *                        Eth_HwRMAC_PhyMdioWriteAccessFlow, Eth_HwRMAC_PhyMdioReadAccessFlow, 
 *                        Eth_HwRMAC_LinkVerification, COMA_BufferPoolnitializationFlow, GWCA_FullSettingFlow
 *                        - As per ticket ARDAACJ-699: 
 *                        + Update to provide correct support for reading Mii in the functions Eth_ETNE_HwReadMii and 
 *                        Eth_HwRMAC_PhyMdioReadAccessFlow
 *                        - As per ticket ARDAACJ-680:
 *                        + Update to support SGMII mode in the functions Eth_SGMIIInit and Eth_ETNE_HwInit,
 *                        RMAC_InitializationFlow
 *                        + Update to support for interrupt in Eth_HwPreCommonInit, Eth_HwPreCommonDeInit
 *                        + Add new function Eth_InterruptHandling, Eth_Etha_SGMII_Common_Isr to support for handling 
 *                        interrupt
 *                        - As per ticket ARDAACJ-663: 
 *                        + Add a condition check ETH_TRUE == Eth_GaaRsw2PortValid[LulPortIdx] before calling 
 *                        Eth_HwETHA_ModeTransitionFlow()
 *                        - As per ticket ARDAACJ-684
 *                        + Update the function Eth_ETNE_HwEnableController to correct the initial flow for RMAC 
 *                        in Eth_HwETHA_InitializationFlow
 *                        - As per ticket ARDAACJ-689, ARDAACJ-700:
 *                        + Update the RMAC initialization flow in the function RMAC_InitializationFlow to correct 
 *                        the assigned value for the MPIC register and to support loopback mode
 *                        - As per ticket ARDAACJ-696:
 *                        + Update to provide correct support for the element ulMaxFrameSize in the functions: 
 *                        Eth_HwPreCommonInit, Eth_ETNE_HwDisableController, Eth_TxRxDescConfig, and Eth_RxQueueProcess
 *                        - Improve the coding rule for else condition
 *                        - Update to correct memory section to ETH_CODE_FAST for functions: 
 *                        + Eth_Gwca_DIS_Common_Isr, Eth_Gwca_TSDIS_Common_Isr, Eth_Gwca_ERR_Common_Isr,
 *                        Eth_Coma_ERR_Common_Isr, Eth_Etha_ERR_Common_Isr, Eth_Etha_SGMII_Common_Isr
 * 2.2.0: 31/12/2024    : Update SW-VERSION for Ver22.02.00(D) U2Bx Final Release
 * 2.1.2: 31/10/2024    : Increase SW-VERSION to 2.1.2
 * 2.1.1: 17/07/2024    : Change ETH_RXQ_NUM to ETH_RXQ_NUM_RSW2
 *                        Update QAC message
 *        16/07/2024    : Change Eth_GaaDemEventUnintendedIntChk to Eth_GpDemEventUnintendedIntChk
 *        15/07/2024    : Remove Set GWCA Mode Register Security Level in Eth_HwPostCommonInit
 *                      : Add more 10Mpbs setting MPIC.LSC in RMAC_InitializationFlow
 *                      : Add Set duplex mode write MPIC.FHDM in RMAC_InitializationFlow
 *        22/06/2024    : Change variable name following :
 *                        from Eth_GaaDemEventAccess to Eth_GbDemEventAccess,
 *                        from Eth_GaaDemEventRxFramesLost to Eth_GbDemEventRxFramesLost,
 *                        from Eth_GaaDemEventCRC to Eth_GbDemEventCRC,
 *                        from Eth_GaaDemEventUnderSizeFrame to Eth_GbDemEventUnderSizeFrame,
 *                        from Eth_GaaDemEventOverSizeFrame to Eth_GbDemEventOverSizeFrame,
 *                        from Eth_GaaDemEventAlignment to Eth_GbDemEventAlignment,
 *                        from Eth_GaaDemEventSinglecollision to Eth_GbDemEventSinglecollision,
 *                        from Eth_GaaDemEventMultiplecollision to Eth_GbDemEventMultiplecollision,
 *                        from Eth_GaaDemEventLatecollision to Eth_GbDemEventLatecollision.
 *        19/06/2024    : Change stTimestamp to stTimestampRsw2 in Eth_ETNE_HwGetIngressTimeStamp and Eth_RxQueueProcess
 *        31/05/2024    : Initial Version 
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
#include "Eth.h"
#include "Eth_Ram.h"
#include "Eth_ETNE_Ram.h"
#include "Eth_ETNE_LLDriver.h"
#include "EthIf_Cbk.h"

#if (ETH_CRITICAL_SECTION_PROTECTION == STD_ON)
/* Included for the declaration of the critical section protection functions */
#include "SchM_Eth.h"
#endif
#if (ETH_ETHSWITCH_MANAGEMENT_SUPPORT == STD_ON)
#include "EthSwt_Cbk.h"
#endif

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
#if (ETH_MACRO_ETNE == STD_ON)
/* AUTOSAR release version information */
#define ETH_ETNE_C_AR_RELEASE_MAJOR_VERSION ETH_AR_RELEASE_MAJOR_VERSION_VALUE
#define ETH_ETNE_C_AR_RELEASE_MINOR_VERSION ETH_AR_RELEASE_MINOR_VERSION_VALUE
#define ETH_ETNE_C_AR_RELEASE_REVISION_VERSION ETH_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define ETH_ETNE_C_SW_MAJOR_VERSION    ETH_SW_MAJOR_VERSION_VALUE
#define ETH_ETNE_C_SW_MINOR_VERSION    ETH_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (ETH_ETNE_AR_RELEASE_MAJOR_VERSION != ETH_ETNE_C_AR_RELEASE_MAJOR_VERSION)
#error "Eth_ETNE_LLDriver.c : Mismatch in Release Major Version"
#endif
#if (ETH_ETNE_AR_RELEASE_MINOR_VERSION != ETH_ETNE_C_AR_RELEASE_MINOR_VERSION)
#error "Eth_ETNE_LLDriver.c : Mismatch in Release Minor Version"
#endif
#if (ETH_ETNE_AR_RELEASE_REVISION_VERSION != ETH_ETNE_C_AR_RELEASE_REVISION_VERSION)
#error "Eth_ETNE_LLDriver.c : Mismatch in Release Revision Version"
#endif

#if (ETH_ETNE_SW_MAJOR_VERSION != ETH_ETNE_C_SW_MAJOR_VERSION)
#error "Eth_ETNE_LLDriver.c : Mismatch in Software Major Version"
#endif
#if (ETH_ETNE_SW_MINOR_VERSION != ETH_ETNE_C_SW_MINOR_VERSION)
#error "Eth_ETNE_LLDriver.c : Mismatch in Software Minor Version"
#endif

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:0316)    : Cast from a pointer to void to a pointer to object type.                                     */
/* Rule                : MISRA C:2012 Rule-11.5, CWE Rule CWE-188, CWE-398, CWE-569                                   */
/* JV-01 Justification : Typecasting from void* is necessary to hide internal types from the header files which are   */
/*                       exposed to user.                                                                             */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0306)    : Cast between a pointer to object and an integral type.                                       */
/* Rule                : CERTCCM INT36, MISRA C:2012 Rule-11.4, CWE Rule CWE-398, CWE-569, CWE-738                    */
/* JV-01 Justification : Typecasting is done as per the register size or hardware specific structure.                 */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:3383)    : Cannot identify wraparound guard for unsigned arithmetic expression.                         */
/* Rule                : CERTCCM INT30                                                                                */
/* JV-01 Justification : Wraparound can't be occur in this unsigned integer arithmetic so there is no need to add a   */
/*                       wraparound guard here.                                                                       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:2982)    : This assignment is redundant. The value of this object is never used before being modified.  */
/* Rule                : CERTCCM MSC07, MSC13, MISRA C:2012 Rule-2.2                                                  */
/* JV-01 Justification : The variable needs to be initialized before using it.                                        */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (7:0404)    : More than one read access to volatile objects between sequence points.                       */
/* Rule                : CERTCCM EXP10, EXP30, MISRA C:2012 Rule-1.3, Rule-13.2                                       */
/* JV-01 Justification : This is to get elements in the global structure through the volatile global pointer. The     */
/*                       order in which it is used is not significant, so there is no problem using it.               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1503)    : The function '%1s' is defined but is not used within this project.                           */
/* Rule                : CERTCCM MSC07, MISRA C:2012 Rule-2.1                                                         */
/* JV-01 Justification : This is accepted, due to the module's API is exported for user's usage.                      */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3469)    : This usage of a function-like macro looks like it could be replaced by an equivalent         */
/*                       function call.                                                                               */
/* Rule                : MISRA C:2012 Dir-4.9                                                                         */
/* JV-01 Justification : To prevent overhead and speed up the processing, there is no need to call a function here    */
/*                       for such a small operation.                                                                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:3384)    : Cannot identify wraparound guard for dependent unsigned arithmetic expression.               */
/* Rule                : CERTCCM INT30                                                                                */
/* JV-01 Justification : Wraparound can't be occur in this unsigned integer arithmetic so there is no need to add a   */
/*                       wraparound guard here.                                                                       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3678)    : The object referenced by '%1s' is not modified through it, so '%1s' could be declared with   */
/*                       type '%2s'.                                                                                  */
/* Rule                : MISRA C:2012 Rule-8.13                                                                       */
/* JV-01 Justification : The object addressed by this pointer change so it can not be of type "pointer to const"      */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (6:3305)    : Pointer cast to stricter alignment.                                                          */
/* Rule                : CERTCCM EXP36, EXP39, MISRA C:2012 Rule-11.3                                                 */
/* JV-01 Justification : It is an implementation required to manage heap memory. There is no problem because the      */
/*                       4-byte alignment boundary is guaranteed by the implementation of the heap memory operation   */
/*                       algorithm.                                                                                   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0310)    : Casting to different object pointer type.                                                    */
/* Rule                : CERTCCM EXP11, EXP39, MISRA C:2012 Rule-11.3                                                 */
/* JV-01 Justification : There is no problem because it is as designed.                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0488)    : Performing pointer arithmetic.                                                               */
/* Rule                : CERTCCM EXP08, MISRA C:2012 Rule-18.4                                                        */
/* JV-01 Justification : This implementation is required for heap memory allocation algorithm                         */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1505)    : The function '%1s' is only referenced in the translation unit where it is defined.           */
/* Rule                : CERTCCM DCL19, MISRA C:2012 Rule-8.7                                                         */
/* JV-01 Justification : This is accepted, due to following coding rule, internal function can be defined in other C  */
/*                       source files                                                                                 */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:5087)    : Use of #include directive after code fragment.                                               */
/* Rule                : MISRA C:2012 Rule-20.1                                                                       */
/* JV-01 Justification : This is done as per Memory Requirement, (MEMMAP003 - Specification of Memory Mapping).       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:4322)    : An expression of 'essentially enum' type (ETag_Eth_RxExtStatusType) is being cast to a       */
/*                       different enum type, 'ETag_Eth_RxStatusType'.                                                */
/* Rule                : MISRA C:2012 Rule-10.5                                                                       */
/* JV-01 Justification : It is confirmed that no data loss occurs during the type casting process, so it is accepted. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3416)    : Logical operation performed on expression with possible side effects.                        */
/* Rule                : CERTCCM EXP45                                                                                */
/* JV-01 Justification : This is necessary for suppressing optimization by dummy loop.                                */
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
/* Message (6:2877)    : This loop will never be executed more than once.                                             */
/* Rule                : CERTCCM MSC07, MISRA C:2012 Dir-4.1                                                          */
/* JV-01 Justification : This loop will only be executed at least once, depends on user configuration.                */
/*       Verification  : This is Hardware Specification, X2x only provides 1 Unit. So it is not having any impact.    */
/**********************************************************************************************************************/
/* Message (1:1504)    : The object '%1s' is only referenced in the translation unit where it is defined.             */
/* Rule                : CERTCCM DCL15, DCL19, MISRA C:2012 Rule-8.7                                                  */
/* JV-01 Justification : This is accepted, due to following coding rule, internal function can be defined in other C  */
/*                       source files                                                                                 */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE Rule CWE-398, CWE-569                                            */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is accepted. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
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
/* Message (2:3673)    : The object addressed by the pointer parameter '%s' is not modified and so the pointer        */
/*                       could be of type 'pointer to const'.                                                         */
/* Rule                : CERTCCM DCL00, DCL13, MISRA C:2012 Rule-8.13                                                 */
/* JV-01 Justification : Pointer variable is used to modify the value at the address so the pointer cannot be         */
/*                       declared as 'pointer to const' type.                                                         */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:2983)    : This assignment is redundant. The value of this object is never subsequently used.           */
/* Rule                : MISRA C:2012 Rule-2.2, CERTCCM MSC07, MSC13, CWE Rule CWE-14, CWE-398, CWE-561, CWE-563,     */
/*                       CWE-569, CWE-633                                                                             */
/* JV-01 Justification : The value is to increment the pointer to the next item.                                      */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0317)    : [I] Implicit conversion from a pointer to void to a pointer to object type.                  */
/* Rule                : MISRA C:2012 Rule-11.5                                                                       */
/* JV-01 Justification : This coversion from void* for matching with function argument's type.                        */
/*       Verification  : However, part of the code is verified manually and it is not having any impact               */
/**********************************************************************************************************************/
/* Message (2:3200)    : '%s' returns a value which is not being used.                                                */
/* Rule                : CERTCCM ERR33, EXP12, POS54, MISRA C:2012 Rule-17.7, CWE Rule CWE-252, CWE-391, CWE-398      */
/*                       CWE-389, CWE-569, CWE-746, CWE-748                                                           */
/* JV-01 Justification : The usage of the return value of this function is not required for the interrupt handler.    */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:2985)    : This operation is redundant. The value of the result is always that of the left-hand operand.*/
/* Rule                : CERTCCM MSC07, MSC13, MISRA C:2012 Rule-2.2, CWE Rule CWE-398, CWE-561, CWE-569, CWE-633     */
/* JV-01 Justification : The content of LusReqSize will be changed if the user enables the EthSwt option, so the value*/
/*                       of this result is not always that of the left-hand operand.                                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:2986)    : This operation is redundant. The value of the result is always that of the right-hand        */
/*                       operand.                                                                                     */
/* Rule                : MISRA C:2012 Rule-2.2, CERTCCM MSC07, MSC13, CWE Rule CWE-398, CWE-561, CWE-569, CWE-633     */
/* JV-01 Justification : The operation is correct                                                                     */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (6:2992)    : The value of this 'if' controlling expression is always 'false'.                             */
/* Rule                : MISRA C:2012 Rule-14.3                                                                       */
/* JV-01 Justification : This is to support different configuration, macro value can be generated so that such        */
/*                       conditional statement can be either true or false                                            */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (6:2996)    : The result of this logical operation is always 'false'.                                      */
/* Rule                : MISRA C:2012 Rule-2.2, CWE Rule CWE-561, CWE-633                                             */
/* JV-01 Justification : Depending on device status, there is case where the 'if' will return 'true'.                 */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (6:2842)    : Apparent: Dereference of an invalid pointer value.                                           */
/* Rule                : CERTCCM ARR30, CWE Rule CWE-120, CWE-121, CWE-122, CWE-124, CWE-125, CWE-126, CWE-127        */
/*                       CWE-129, CWE-131, CWE-466, CWE-786, CWE-787, CWE-788, CWE-805, CWE-465, CWE-633, CWE-740     */
/* JV-01 Justification : To prevent overhead and excessive nesting of condition statements, this pointer has been     */
/*                       tested valid with many test cases, so there is no problem with the current implementation.   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:0686)    : Array has fewer initializers than its declared size. Default initialization is applied to    */
/*                       the remainder of the array elements.                                                         */
/* Rule                : MISRA C:2012 Rule-9.3, CWE Rule CWE-665, CWE-452                                             */
/* JV-01 Justification : This initialization to avoid passing address of uninitialized object. This can be accepted.  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0303)    : [I] Cast between a pointer to volatile object and an integral type.                          */
/* Rule                : CERTCCM INT36, MISRA C:2012 Rule-11.4                                                        */
/*                       REFERENCE - ISO-6.3.4 Semantics                                                              */
/* JV-01 Justification : This is necessary to compare register values and pointers.                                   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3464)    : Argument to macro '%s' contains a side effect that will be evaluated more than once.         */
/* Rule                : CERTCCM PRE31                                                                                */
/* JV-01 Justification : After reviewing coding, it is concluded that this implementation is okay as it is since the  */
/*                       memory used to access this volatile variable is user RAM, not a specific HW register, so     */
/*                       there is no worry about potential side effects in this case.                                 */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1502)    : The object 'name' is defined but is not used within this project.                            */
/* Rule                : MISRA C:2012 Rule-2.8, CWE Rule CWE-398, CWE-569, CERTC Rule MSC13                           */
/* JV-01 Justification : Array is used in another part of driver code. There is no problem in use                     */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:0311)    : Dangerous pointer cast results in loss of const qualification.                               */
/* Rule                : MISRA C:2012 Rule-11.8, CERTCCM EXP05                                                        */
/* JV-01 Justification : This is to achieve throughput in the code.                                                   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0751)    : Casting to char pointer type.                                                                */
/* Rule                : CERTCCM EXP11, EXP39, CWE Rule CWE-188, CWE-398, CWE-468, CWE-588, CWE-465, CWE-569, CWE-737 */
/* JV-01 Justification : Using void due to specific requirement of input parameter. So, this can be skipped           */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
 
/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/
#define ETH_START_SEC_CONST_UNSPECIFIED
#include "Eth_MemMap.h"

/* RSW2 TOP module register */
CONSTP2VAR(volatile Eth_RSW2_TOPRegType, ETH_CONST, REGSPACE)
  Eth_GpRSW2_TOPRegs = (Eth_RSW2_TOPRegType *)ETH_ETNE_TOP_ADDRESS;                                                     /* PRQA S 0306, 1502 # JV-01, JV-01 */

/* RSW2 COMA module register */
CONSTP2VAR(volatile Eth_RSW2_COMARegType, ETH_CONST, REGSPACE)
  Eth_GpRSW2_COMARegs = (Eth_RSW2_COMARegType *)ETH_ETNE_COMA_ADDRESS;                                                  /* PRQA S 0306, 1504 # JV-01, JV-01 */

/* RSW2 MFWD module register */
CONSTP2VAR(volatile Eth_RSW2_MFWDRegType, ETH_CONST, REGSPACE)
  Eth_GpRSW2_MFWDRegs = (Eth_RSW2_MFWDRegType *)ETH_ETNE_MFWD_ADDRESS;                                                  /* PRQA S 0306, 1504 # JV-01, JV-01 */

/* RSW2 GWCA module register */
CONSTP2VAR(volatile Eth_RSW2_GWCARegType, ETH_CONST, REGSPACE) Eth_GaaRSW2_GWCARegs[ETH_MAX_GWCA_SUPPORTED] =           /* PRQA S 1504 # JV-01 */
{
  (Eth_RSW2_GWCARegType *)ETH_ETNE_GWCA0_ADDRESS                                                                        /* PRQA S 0306 # JV-01 */
};

/* RSW2 ETHA module register */
CONSTP2VAR(volatile Eth_RSW2_ETHARegType, ETH_CONST, REGSPACE) Eth_GaaRSW2_ETHARegs[ETH_MAX_TSNA_SUPPORTED] =           /* PRQA S 1504 # JV-01 */
{
  (Eth_RSW2_ETHARegType *)ETH_ETNE_TSNA0_ADDRESS,                                                                       /* PRQA S 0306 # JV-01 */
#if defined(ETH_CTRL1_ETHA_ADDRESS)
  (Eth_RSW2_ETHARegType *)ETH_ETNE_TSNA1_ADDRESS                                                                        /* PRQA S 0306 # JV-01 */
#endif
};                                                                                                                      /* PRQA S 0686 # JV-01 */

/* RSW2 RMAC module register */
CONSTP2VAR(volatile Eth_RSW2_RMACRegType, ETH_CONST, REGSPACE) Eth_GaaRSW2_RMACRegs[ETH_MAX_RMAC_SUPPORTED] =           /* PRQA S 1504 # JV-01 */
{
  (Eth_RSW2_RMACRegType *)ETH_ETNE_RMAC0_ADDRESS,                                                                       /* PRQA S 0306 # JV-01 */
#if defined(ETH_CTRL1_RMAC_ADDRESS)
  (Eth_RSW2_RMACRegType *)ETH_ETNE_RMAC1_ADDRESS                                                                        /* PRQA S 0306 # JV-01 */
#endif
};                                                                                                                      /* PRQA S 0686 # JV-01 */

/* RSW2 gPTP module register */
CONSTP2VAR(volatile Eth_RSW2_gPTPRegType, ETH_CONST, REGSPACE)
 Eth_GpRSW2_GPTPRegs = (Eth_RSW2_gPTPRegType *)ETH_ETNE_GPTP_ADDRESS;                                                   /* PRQA S 0306, 1504, 1502 # JV-01, JV-01, JV-01 */

/* RSW2 ETHA module register for controller */
CONSTP2VAR(volatile Eth_RSW2_ETHARegType, ETH_CONST, REGSPACE) Eth_GaaCtrl_ETHARegs[ETH_RACE_PORT_TSNA_N] =             /* PRQA S 1502 # JV-01 */
{
  (Eth_RSW2_ETHARegType *)ETH_CTRL0_ETHA_ADDRESS,                                                                       /* PRQA S 0306 # JV-01 */
#if defined(ETH_CTRL1_ETHA_ADDRESS)
  (Eth_RSW2_ETHARegType *)ETH_CTRL1_ETHA_ADDRESS,                                                                       /* PRQA S 0306 # JV-01 */
#else
  (Eth_RSW2_ETHARegType *)0x00000000UL,
#endif
};

/* RSW2 RMAC module register for controller */
CONSTP2VAR(volatile Eth_RSW2_RMACRegType, ETH_CONST, REGSPACE) Eth_GaaCtrl_RMACRegs[ETH_RACE_PORT_TSNA_N] =             /* PRQA S 1504 # JV-01 */
{
  (Eth_RSW2_RMACRegType *)ETH_CTRL0_RMAC_ADDRESS,                                                                       /* PRQA S 0306 # JV-01 */
#if defined(ETH_CTRL1_RMAC_ADDRESS)
  (Eth_RSW2_RMACRegType *)ETH_CTRL1_RMAC_ADDRESS,                                                                       /* PRQA S 0306 # JV-01 */
#else
  (Eth_RSW2_RMACRegType *)0x00000000UL,
#endif
};

CONST(uint32, ETH_CONST)
  Eth_GaaRsw2PortType[ETH_RACE_PORT_N] =                                                                                /* PRQA S 1504 # JV-01 */
{
  ETH_RSW2_PORT_TYPE_ETHA,
  ETH_RSW2_PORT_TYPE_ETHA,
  ETH_RSW2_PORT_TYPE_GWCA
};

CONST(uint32, ETH_CONST)
  Eth_GaaRsw2PortMap[ETH_RACE_PORT_N] =                                                                                 /* PRQA S 1504 # JV-01 */
{
  ETH_RACE_PORT_ETHA0,
  ETH_RACE_PORT_ETHA1,
  ETH_RACE_PORT_GWCA0
};
 
#define ETH_STOP_SEC_CONST_UNSPECIFIED
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/
#define ETH_START_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#if (ETH_GLOBAL_TIME_SUPPORT == STD_ON)
STATIC FUNC(void, ETH_PRIVATE_CODE) Eth_TsDescConfig(void);
#endif /* (ETH_GLOBAL_TIME_SUPPORT == STD_ON) */

FUNC(void, ETH_PRIVATE_CODE) Eth_WaitNanoSec(CONST(uint32, AUTOMATIC) LulNanosec);

STATIC FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_TxRxDescConfig(CONST(uint32, AUTOMATIC) LulCtrlIdx);

#if (ETH_UPDATE_PHYS_ADDR_FILTER == STD_ON)
STATIC FUNC(boolean, ETH_PRIVATE_CODE) Eth_IsRxFrameValid(
  CONST(uint32, AUTOMATIC) LulCtrlIdx,
  CONSTP2CONST(Eth_RxFrameType, AUTOMATIC, ETH_APPL_DATA) LpRxFrame);
#endif  /* (ETH_UPDATE_PHYS_ADDR_FILTER == STD_ON) */

STATIC FUNC(void, ETH_PRIVATE_CODE) Eth_RxCallEthIf(
  CONST(uint32, AUTOMATIC) LulCtrlIdx,
  CONSTP2CONST(Eth_RxFrameType, AUTOMATIC, ETH_APPL_DATA) LpFrame);

STATIC FUNC(void, ETH_PRIVATE_CODE) Eth_TxConfirmationQueueProcess(
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulQIdx);

STATIC FUNC(TickType, ETH_PRIVATE_CODE) Eth_GetElapsedTimeValue(
  P2VAR(TickType, AUTOMATIC, ETH_APPL_DATA) LusTimeOutCount);                                                           /* PRQA S 3432 # JV-01 */

#if ((ETH_CTRL_ENABLE_TX_INTERRUPT == STD_ON) || (ETH_CTRL_ENABLE_RX_INTERRUPT == STD_ON))
STATIC FUNC(void, ETH_PRIVATE_CODE) Eth_HwEnableInterrupt(void);
#endif /* ((ETH_CTRL_ENABLE_TX_INTERRUPT == STD_ON) || (ETH_CTRL_ENABLE_RX_INTERRUPT == STD_ON)) */

#if ((ETH_GWCA_ERR_ISR == STD_ON) || (ETH_COMA_ERR_ISR == STD_ON) || (ETH_ETHA_ERR_ISR == STD_ON))
STATIC FUNC(void, ETH_PRIVATE_CODE) Eth_HwEnableErrorInterrupt(void);
#endif /* ((ETH_GWCA_ERR_ISR == STD_ON) || (ETH_COMA_ERR_ISR == STD_ON) || (ETH_ETHA_ERR_ISR == STD_ON)) */

STATIC FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_HwTOP_SwitchInitializationFlow(void);

#if (ETH_SWITCHING_MODE == ETH_SWMODE_ENDSTATION)
STATIC FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_HwTOP_SwitchResetFlow(void);
#endif /* (ETH_SWITCHING_MODE == ETH_SWMODE_ENDSTATION) */

STATIC FUNC(void, ETH_PRIVATE_CODE) Eth_HwMFWD_PortISettingFlow(
  CONST(uint32, AUTOMATIC) LulPortIdx);

#if (ETH_SWITCHING_MODE == ETH_SWMODE_ENDSTATION)
STATIC FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_HwMFWD_Layer3TableResetFlow(void);

STATIC FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_HwMFWD_MacTableResetFlow(void);

STATIC FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_HwMFWD_VlanTableResetFlow(void);
#endif /* ETH_SWITCHING_MODE == ETH_SWMODE_ENDSTATION */

STATIC FUNC(void, ETH_PRIVATE_CODE) Eth_HwMFWD_PortIPortBasedSettingFlow(
  CONST(uint32, AUTOMATIC) LulPortIdx);

STATIC FUNC(void, ETH_PRIVATE_CODE) Eth_HwMFWD_PortIPortBasedDisableFlow(
  CONST(uint32, AUTOMATIC) LulPortIdx);

#if (ETH_SWITCHING_MODE == ETH_SWMODE_ENDSTATION)
STATIC FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_HwMFWD_Layer2Layer3UpdateTableResetFlow(void);

STATIC FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_HwMFWD_GateRamResetFlow(void);
#endif /* ETH_SWITCHING_MODE == ETH_SWMODE_ENDSTATION */

STATIC FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_HwGWCA_ModeTransitionFlow(
  CONST(uint32, AUTOMATIC) LulGWCAIdx,
  CONST(uint32, AUTOMATIC) LenMode);

STATIC FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_HwGWCA_InitializationFlow(
  CONST(uint32, AUTOMATIC) LulGWCAIdx);

STATIC FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_HwGWCA_MulticastTableResetFlow(
  CONST(uint32, AUTOMATIC) LulGWCAIdx);

STATIC FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_HwGWCA_AxiRamResetFlow(
  CONST(uint32, AUTOMATIC) LulGWCAIdx);

STATIC FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_HwETHA_ModeTransitionFlow(
  CONST(uint32, AUTOMATIC) LulETHAIdx,
  CONST(uint32, AUTOMATIC) LenMode);

STATIC FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_HwETHA_InitializationFlow(
  CONST(uint32, AUTOMATIC) LulETHAIdx);

STATIC FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_HwETHA_TasRamResetFlow(
  CONST(uint32, AUTOMATIC) LulETHAIdx);

STATIC FUNC(void, ETH_PRIVATE_CODE) Eth_HwETHA_CbsQSettingFlow(
  CONST(uint32, AUTOMATIC) LulETHAIdx);

#if (ETH_GLOBAL_TIME_SUPPORT == STD_ON)
STATIC FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_HwETHA_TasSettingFlow(
  CONST(uint32, AUTOMATIC) LulETHAIdx);

STATIC FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_HwETHA_TasDisablingFlow(
  CONST(uint32, AUTOMATIC) LulETHAIdx);

STATIC FUNC(void, ETH_PRIVATE_CODE) Eth_HwETHA_TasEnablingFlow(
  CONST(uint32, AUTOMATIC) LulETHAIdx);

STATIC FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_HwETHA_TasEntryILearnFlow(
  CONST(uint32, AUTOMATIC) LulETHAIdx,
  CONST(uint32, AUTOMATIC) LulSaveTasConfigAddr,
  CONSTP2CONST(Eth_TASEntryType, AUTOMATIC, ETH_APPL_DATA) LpCtrlConfig);
#endif /* (ETH_GLOBAL_TIME_SUPPORT == STD_ON) */

#if (ETH_CTRL_ENABLE_MII == STD_ON)
STATIC FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_HwRMAC_PhyMdioWriteAccessFlow(
  CONST(uint32, AUTOMATIC) LulRMACIdx, CONST(uint8, AUTOMATIC) LucTrcvIdx,
  CONST(uint8, AUTOMATIC) LucRegIdx, CONST(uint16, AUTOMATIC) LusWriteVal);

STATIC FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_HwRMAC_PhyMdioReadAccessFlow(
  CONST(uint32, AUTOMATIC) LulRMACIdx, 
  CONST(uint8, AUTOMATIC) LucTrcvIdx, 
  CONST(uint8, AUTOMATIC) LucRegIdx,
  CONSTP2VAR(uint16, AUTOMATIC, ETH_APPL_DATA) LpRegValPtr);                                                            /* PRQA S 3432 # JV-01 */
#endif /* (ETH_CTRL_ENABLE_MII == STD_ON) */

STATIC FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_HwRMAC_LinkVerification(
  CONST(uint32, AUTOMATIC) LulRMACIdx);

#if (ETH_GLOBAL_TIME_SUPPORT == STD_ON)
STATIC FUNC(void, ETH_PRIVATE_CODE) Eth_HwGPTP_TimerTOffsetSettingFlow(
  CONST(uint32, AUTOMATIC) LulTimerIdx,
  CONST(uint32, AUTOMATIC) LulNanoSeconds,
  CONST(uint32, AUTOMATIC) LulSecondsLower,
  CONST(uint16, AUTOMATIC) LusSecondsHigher);

STATIC FUNC(void, ETH_PRIVATE_CODE) Eth_HwGPTP_Avtp64TimerTReadingFlow(
  CONST(uint32, AUTOMATIC) LulTimerIdx,
  CONSTP2VAR(uint32, AUTOMATIC, ETH_APPL_DATA) ulAVTP_Upper,                                                            /* PRQA S 3432 # JV-01 */
  CONSTP2VAR(uint32, AUTOMATIC, ETH_APPL_DATA) ulAVTP_Downer);                                                          /* PRQA S 3432 # JV-01 */

STATIC FUNC(void, ETH_PRIVATE_CODE) Eth_HwGPTP_gPTPTimerTReadingFlow(
  CONST(uint32, AUTOMATIC) LulTimerIdx,
  CONSTP2VAR(uint32, AUTOMATIC, ETH_APPL_DATA) LpNanoSeconds,                                                           /* PRQA S 3432 # JV-01 */
  CONSTP2VAR(uint32, AUTOMATIC, ETH_APPL_DATA) LpSecondsLower,                                                          /* PRQA S 3432 # JV-01 */
  CONSTP2VAR(uint16, AUTOMATIC, ETH_APPL_DATA) LpSecondsHigher);                                                        /* PRQA S 3432 # JV-01 */
#endif /* (ETH_GLOBAL_TIME_SUPPORT == STD_ON) */

STATIC FUNC(Std_ReturnType, ETH_PRIVATE_CODE) COMA_BufferPoolnitializationFlow(void);

#if (ETH_SWITCHING_MODE == ETH_SWMODE_ENDSTATION)
STATIC FUNC(void, ETH_PRIVATE_CODE) COMA_RSwitchResetFlow(void);
#endif /* ETH_SWITCHING_MODE == ETH_SWMODE_ENDSTATION */

STATIC FUNC(void, ETH_PRIVATE_CODE) COMA_AgentIClockEnableFlow(
  CONST(uint32, AUTOMATIC) LulPortIdx);

STATIC FUNC(void, ETH_PRIVATE_CODE) COMA_AgentIClockDisableFlow(
  CONST(uint32, AUTOMATIC) LulPortIdx);

STATIC FUNC(boolean, ETH_PRIVATE_CODE) COMA_AgentIClockStatusCheckFlow(
  CONST(uint32, AUTOMATIC) LulPortIdx);

#if (ETH_SWITCHING_MODE == ETH_SWMODE_ENDSTATION)
STATIC FUNC(void, ETH_PRIVATE_CODE) COMA_SwitchClockEnableFlow(void);
#endif /* ETH_SWITCHING_MODE == ETH_SWMODE_ENDSTATION */

STATIC FUNC(Std_ReturnType, ETH_PRIVATE_CODE) MFWD_FullSettingFlow(void);

#if (ETH_SWITCHING_MODE == ETH_SWMODE_ENDSTATION)
STATIC FUNC(Std_ReturnType, ETH_PRIVATE_CODE) MFWD_Layer3ForwardingRoutingFilteringSettingFlow(void);

STATIC FUNC(Std_ReturnType, ETH_PRIVATE_CODE) MFWD_Layer2ForwardingSettingFlow(void);
#endif /* ETH_SWITCHING_MODE == ETH_SWMODE_ENDSTATION */

STATIC FUNC(void, ETH_PRIVATE_CODE) MFWD_PortBasedForwardingSettingFlow(void);

#if (ETH_SWITCHING_MODE == ETH_SWMODE_ENDSTATION)
STATIC FUNC(Std_ReturnType, ETH_PRIVATE_CODE) MFWD_Layer2Layer3UpdateSettingFlow(void);

STATIC FUNC(Std_ReturnType, ETH_PRIVATE_CODE) MFWD_PsfpSettingFlow(void);
#endif /* ETH_SWITCHING_MODE == ETH_SWMODE_ENDSTATION */

STATIC FUNC(Std_ReturnType, ETH_PRIVATE_CODE) GWCA_FullSettingFlow(
  CONST(uint32, AUTOMATIC) LulGWCAIdx);

STATIC FUNC(void, ETH_PRIVATE_CODE) ETHA_FullSettingFlow(
  CONST(uint32, AUTOMATIC) LulETHAIdx);

STATIC FUNC(Std_ReturnType, ETH_PRIVATE_CODE) RMAC_InitializationFlow(
  CONST(uint32, AUTOMATIC) LulRMACIdx);

#if (ETH_GET_COUNTER_VALUES_API == STD_ON)
STATIC FUNC(void, ETH_PRIVATE_CODE) Eth_InitCounterValues(
  CONST(uint32, AUTOMATIC) LulCtrlIdx);
STATIC FUNC(void, ETH_PRIVATE_CODE) Eth_HwRMAC_CountCounterValues(
  CONST(uint32, AUTOMATIC) LulCtrlIdx,
  CONSTP2VAR(Eth_StatsRegValueType, AUTOMATIC, ETH_APPL_DATA) LpStats);                                                 /* PRQA S 3432 # JV-01 */
#endif /* (ETH_GET_COUNTER_VALUES_API == STD_ON) */

#if (ETH_GET_RX_STATS_API == STD_ON)
STATIC FUNC(void, ETH_PRIVATE_CODE) Eth_InitRxStats(
  CONST(uint32, AUTOMATIC) LulCtrlIdx);
STATIC FUNC(void, ETH_PRIVATE_CODE) Eth_HwRMAC_CountRxStats(
  CONST(uint32, AUTOMATIC) LulCtrlIdx,
  CONSTP2VAR(Eth_StatsRegValueType, AUTOMATIC, ETH_APPL_DATA) LpStats);                                                 /* PRQA S 3432 # JV-01 */
#endif /* (ETH_GET_RX_STATS_API == STD_ON) */

#if (ETH_GET_TX_STATS_API == STD_ON)
STATIC FUNC(void, ETH_PRIVATE_CODE) Eth_InitTxStats(
  CONST(uint32, AUTOMATIC) LulCtrlIdx);
STATIC FUNC(void, ETH_PRIVATE_CODE) Eth_HwRMAC_CountTxStats(
  CONST(uint32, AUTOMATIC) LulCtrlIdx,
  CONSTP2VAR(Eth_StatsRegValueType, AUTOMATIC, ETH_APPL_DATA) LpStats);                                                 /* PRQA S 3432 # JV-01 */
#endif /* (ETH_GET_TX_STATS_API == STD_ON) */

#if (ETH_GET_TX_ERROR_COUNTER_VALUES_API == STD_ON)
STATIC FUNC(void, ETH_PRIVATE_CODE) Eth_InitTxErrorCounterValues(
  CONST(uint32, AUTOMATIC) LulCtrlIdx);
STATIC FUNC(void, ETH_PRIVATE_CODE) Eth_HwRMAC_CountTxErrorCounterValues(
  CONST(uint32, AUTOMATIC) LulCtrlIdx,
  CONSTP2VAR(Eth_StatsRegValueType, AUTOMATIC, ETH_APPL_DATA) LpStats);                                                 /* PRQA S 3432 # JV-01 */
#endif /* (ETH_GET_TX_ERROR_COUNTER_VALUES_API == STD_ON) */

STATIC FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_SGMIIInit(
  CONST(uint32, AUTOMATIC) LulCtrlIdx,
  CONST(Eth_OptionType, AUTOMATIC) LenBypassMode);

#if ((ETH_GWCA0_DATA_ISR == STD_ON) || (ETH_GLOBAL_TIME_SUPPORT == STD_ON) || (ETH_GWCA0_ERR_ISR == STD_ON) || \
  (ETH_COMA_ERR_ISR == STD_ON) || (ETH_ETHA1_ERR_ISR == STD_ON) || (ETH_SGMII_ISR == STD_ON))
STATIC FUNC(void, ETH_PRIVATE_CODE) Eth_InterruptHandling(
  CONST(Eth_InterruptHandlingType, AUTOMATIC) LenInterruptType);
#endif /* #if ((ETH_GWCA0_DATA_ISR == STD_ON) || (ETH_GLOBAL_TIME_SUPPORT == STD_ON) || (ETH_GWCA0_ERR_ISR == STD_ON) ||
  (ETH_COMA_ERR_ISR == STD_ON) || (ETH_ETHA1_ERR_ISR == STD_ON) || (ETH_SGMII_ISR == STD_ON)) */

/***********************************************************************************************************************
** Function Name         : Eth_HwPreCommonInit (RSW2)
**
** Service ID            : N/A
**
** Description           : Pre-Initialize the common parts of RSW2 HWUnit
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
** Return parameter      : E_OK : Success
**
** Preconditions         : None
**
** Global Variable(s)    : Eth_GaaRsw2PortType, Eth_GaaLinkFixTable,
**                         Eth_GaaRsw2GWCACtrlValid, Eth_GpCtrlConfigPtr
**                         Eth_GstDescChainMap
**
** Function(s) invoked   : Eth_TsDescConfig, Eth_InterruptHandling
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_408
** Reference ID          : ETH_DUD_ACT_408_GBL001, ETH_DUD_ACT_408_GBL002
** Reference ID          : ETH_DUD_ACT_408_GBL003, ETH_DUD_ACT_408_GBL004
** Reference ID          : ETH_DUD_ACT_408_GBL005, ETH_DUD_ACT_408_GBL006
** Reference ID          : ETH_DUD_ACT_408_GBL007, ETH_DUD_ACT_408_GBL008
** Reference ID          : ETH_DUD_ACT_408_GBL009, ETH_DUD_ACT_408_GBL010
** Reference ID          : ETH_DUD_ACT_408_GBL011, ETH_DUD_ACT_408_GBL012
** Reference ID          : ETH_DUD_ACT_408_GBL013, ETH_DUD_ACT_408_GBL014
** Reference ID          : ETH_DUD_ACT_408_GBL015, ETH_DUD_ACT_408_GBL016
** Reference ID          : ETH_DUD_ACT_408_GBL017, ETH_DUD_ACT_408_GBL018
** Reference ID          : ETH_DUD_ACT_408_GBL019
** Reference ID          : ETH_DUD_ACT_408_REG001, ETH_DUD_ACT_408_REG002
** Reference ID          : ETH_DUD_ACT_408_REG003, ETH_DUD_ACT_408_REG004
** Reference ID          : ETH_DUD_ACT_408_REG005, ETH_DUD_ACT_408_REG006
** Reference ID          : ETH_DUD_ACT_408_REG007, ETH_DUD_ACT_408_REG008
** Reference ID          : ETH_DUD_ACT_408_REG009, ETH_DUD_ACT_408_REG010
** Reference ID          : ETH_DUD_ACT_408_REG011, ETH_DUD_ACT_408_REG012
** Reference ID          : ETH_DUD_ACT_408_REG013, ETH_DUD_ACT_408_REG014
** Reference ID          : ETH_DUD_ACT_408_REG015, ETH_DUD_ACT_408_REG016
** Reference ID          : ETH_DUD_ACT_408_REG017, ETH_DUD_ACT_408_REG018
** Reference ID          : ETH_DUD_ACT_408_REG019, ETH_DUD_ACT_408_REG020
** Reference ID          : ETH_DUD_ACT_408_REG021, ETH_DUD_ACT_408_REG022
** Reference ID          : ETH_DUD_ACT_408_REG023, ETH_DUD_ACT_408_REG024
** Reference ID          : ETH_DUD_ACT_408_REG025, ETH_DUD_ACT_408_REG026
** Reference ID          : ETH_DUD_ACT_408_REG027
** Reference ID          : ETH_DUD_ACT_408_REG029, ETH_DUD_ACT_408_REG030
** Reference ID          : ETH_DUD_ACT_408_REG031, ETH_DUD_ACT_408_REG032
** Reference ID          : ETH_DUD_ACT_408_REG033, ETH_DUD_ACT_408_REG034
** Reference ID          : ETH_DUD_ACT_408_REG035, ETH_DUD_ACT_408_REG036
** Reference ID          : ETH_DUD_ACT_408_REG037, ETH_DUD_ACT_408_REG038
** Reference ID          : ETH_DUD_ACT_408_REG039, ETH_DUD_ACT_408_REG040
***********************************************************************************************************************/
 FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_HwPreCommonInit(void)                                                       
 {
   P2CONST(Eth_ETNEConfigType, AUTOMATIC, ETH_APPL_DATA) LpHwUnitConfig;
   P2VAR(Eth_LinkDescTypeRsw2, AUTOMATIC, ETH_APPL_DATA) LpLinkDesc;                                                    /* PRQA S 3432 # JV-01 */
   Std_ReturnType LucResult;
   uint32 LulCtrlIdx;
   uint8 LucIdx;
 
   LucResult = E_OK;
   Eth_GpDescHeap = Eth_Util_RamInit(Eth_GaaMemPoolDesc, (uint32)sizeof(Eth_GaaMemPoolDesc));                           
   /* Initialize linkfix table */
   LpLinkDesc = &Eth_GaaLinkFixTable[0];
   for (LucIdx = 0U; LucIdx < ETH_RACE_AXI_CHAIN_N; LucIdx++)
   {
     LpLinkDesc[LucIdx].ulDie    = 0U;
     LpLinkDesc[LucIdx].ulDptrH  = 0U;
     LpLinkDesc[LucIdx].ulDptr   = 0U;
     LpLinkDesc[LucIdx].ulErr    = 0U;
     LpLinkDesc[LucIdx].ulDse    = 0U;
     LpLinkDesc[LucIdx].ulAxie   = 0U;
     LpLinkDesc[LucIdx].ulInfo0  = 0U;
     LpLinkDesc[LucIdx].ulDs     = 0U;
     LpLinkDesc[LucIdx].ulDt     = ETH_DESC_LINKFIX_RSW2;
   }
 
   /* Initialize Descriptor Chain Map */
   Eth_GstDescChainMap.ulValidChainNum = 0;
 
   Eth_GaaRsw2GWCACtrlValid = ETH_FALSE;
 
   for (LulCtrlIdx = 0U; LulCtrlIdx < (uint32)ETH_ETNE_CTRLS_SUPPORTED; LulCtrlIdx++)                                   /* PRQA S 2877 # JV-01 */
   {
     LpHwUnitConfig =
       (P2CONST(Eth_ETNEConfigType, AUTOMATIC, ETH_APPL_DATA))Eth_GpCtrlConfigPtr[LulCtrlIdx].pHwUnitConfig;            /* PRQA S 0316 # JV-01 */
     if (ETH_RSW2_PORT_TYPE_GWCA == Eth_GaaRsw2PortType[LpHwUnitConfig->ulEthPortId])                                   
     {
       Eth_GaaRsw2GWCACtrlValid = ETH_TRUE;
     }
     if (Eth_GulRxMaxFrameSize > LpHwUnitConfig->stRxConfig.ulMaxFrameSize)
     {
       Eth_GulRxMaxFrameSize = LpHwUnitConfig->stRxConfig.ulMaxFrameSize;
     }
   }
 
   #if (ETH_GLOBAL_TIME_SUPPORT == STD_ON)
   /* Ts descriptor chain setting */
   Eth_TsDescConfig();
   #endif
 
   #if ((ETH_GWCA0_DATA_ISR == STD_ON) || (ETH_GLOBAL_TIME_SUPPORT == STD_ON) || (ETH_GWCA0_ERR_ISR == STD_ON) || \
   (ETH_COMA_ERR_ISR == STD_ON) || (ETH_ETHA1_ERR_ISR == STD_ON) || (ETH_SGMII_ISR == STD_ON))
   /* Enable interrupt handling */
   Eth_InterruptHandling(ETH_ENABLE_INTERRUPT);
   #endif /* #if ((ETH_GWCA0_DATA_ISR == STD_ON) || (ETH_GLOBAL_TIME_SUPPORT == STD_ON) || (ETH_GWCA0_ERR_ISR == STD_ON)
   || (ETH_COMA_ERR_ISR == STD_ON) || (ETH_ETHA1_ERR_ISR == STD_ON) || (ETH_SGMII_ISR == STD_ON)) */
 
   return LucResult;
 }
 
 #if ((ETH_GWCA0_DATA_ISR == STD_ON) || (ETH_GLOBAL_TIME_SUPPORT == STD_ON) || (ETH_GWCA0_ERR_ISR == STD_ON) || \
   (ETH_COMA_ERR_ISR == STD_ON) || (ETH_ETHA1_ERR_ISR == STD_ON) || (ETH_SGMII_ISR == STD_ON))
/**********************************************************************************************************************
** Function Name         : Eth_InterruptHandling (RSW2)
**
** Service ID            : N/A
**
** Description           : This service enables or disables the interrupts
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LenInterruptType
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variable(s)    : Eth_RSW2_IntReg, Eth_RSW2_IntReg,
**
** Function(s) invoked   : RH850_SV_MODE_ICR_AND, RH850_SV_MODE_ICR_OR
**
** Registers Used        : EICn, INTETNE_SELn
**
** Reference ID          : ETH_DUD_ACT_536
** Reference ID          : ETH_DUD_ACT_536_REG001, ETH_DUD_ACT_536_REG002, ETH_DUD_ACT_536_REG003
** Reference ID          : ETH_DUD_ACT_536_REG004, ETH_DUD_ACT_536_REG005, ETH_DUD_ACT_536_REG006
** Reference ID          : ETH_DUD_ACT_536_REG007, ETH_DUD_ACT_536_REG008, ETH_DUD_ACT_536_REG009
** Reference ID          : ETH_DUD_ACT_536_REG010, ETH_DUD_ACT_536_REG011, ETH_DUD_ACT_536_REG012
** Reference ID          : ETH_DUD_ACT_536_REG013, ETH_DUD_ACT_536_REG014, ETH_DUD_ACT_536_REG015
** Reference ID          : ETH_DUD_ACT_536_REG016, ETH_DUD_ACT_536_REG017, ETH_DUD_ACT_536_REG018
** Reference ID          : ETH_DUD_ACT_536_REG019, ETH_DUD_ACT_536_REG020, ETH_DUD_ACT_536_REG021
** Reference ID          : ETH_DUD_ACT_536_REG022, ETH_DUD_ACT_536_REG023, ETH_DUD_ACT_536_REG024
** Reference ID          : ETH_DUD_ACT_536_REG025, ETH_DUD_ACT_536_REG026, ETH_DUD_ACT_536_REG027
** Reference ID          : ETH_DUD_ACT_536_REG028, ETH_DUD_ACT_536_REG029, ETH_DUD_ACT_536_REG030
** Reference ID          : ETH_DUD_ACT_536_REG031, ETH_DUD_ACT_536_REG032
***********************************************************************************************************************/
 STATIC FUNC(void, ETH_PRIVATE_CODE) Eth_InterruptHandling(CONST(Eth_InterruptHandlingType, AUTOMATIC) LenInterruptType)
 {
   CONSTP2CONST(volatile Eth_ETNE_EICRegType, AUTOMATIC, REGSPACE) LpEICIntReg = Eth_RSW2_IntReg.pEICReg;               
   CONSTP2CONST(volatile Eth_ETNE_INTSMRegType, AUTOMATIC, REGSPACE) LpINTSMIntReg = Eth_RSW2_IntReg.pINTSMReg;         
 
  switch (LenInterruptType)
  {
  case ETH_ENABLE_INTERRUPT:
    #if (ETH_GWCA0_DATA_ISR == STD_ON)
    /* Bit 0, 1 - DISS[0, 1] - GWDIS Data Interrupt Status 0/ 1 output source select */
    RH850_SV_MODE_ICR_OR(32, &LpINTSMIntReg->ulINTETNESEL0, (uint32) ETH_INTSM_GWDIS01_MASK);                           /* PRQA S 3464, 0311 # JV-01, JV-01 */
    RH850_SV_MODE_ICR_AND(8, &LpEICIntReg->usINTETNE00, (uint8)(~ETH_EIC_EIMK_MASK));                                   /* PRQA S 3464, 0311, 0751 # JV-01, JV-01, JV-01 */
    #endif /* #if (ETH_GWCA0_DATA_ISR == STD_ON) */

    #if (ETH_GLOBAL_TIME_SUPPORT == STD_ON)
    /* Bit 8, 9 - TSS[0, 1] - TimeStamp Data Interrupt Status 0/ 1 output source select */
    RH850_SV_MODE_ICR_OR(32, &LpINTSMIntReg->ulINTETNESEL1, (uint32)ETH_INTSM_TSS_MASK);                                /* PRQA S 3464, 0311 # JV-01, JV-01 */
    RH850_SV_MODE_ICR_AND(8, &LpEICIntReg->usINTETNE01, (uint8)(~ETH_EIC_EIMK_MASK));                                   /* PRQA S 3464, 0311, 0751 # JV-01, JV-01, JV-01 */
    #endif /* #if (ETH_GLOBAL_TIME_SUPPORT == STD_ON) */

    #if (ETH_GWCA0_ERR_ISR == STD_ON)
    /* Bit 16 - ESS[2] - GWCA0 Error Interrupt output source select */
    RH850_SV_MODE_ICR_OR(32, &LpINTSMIntReg->ulINTETNESEL2, (uint32) ETH_INTSM_GWCA0_ERR_MASK);                         /* PRQA S 3464, 0311 # JV-01, JV-01 */
    RH850_SV_MODE_ICR_AND(8, &LpEICIntReg->usINTETNE02, (uint8)(~ETH_EIC_EIMK_MASK));                                   /* PRQA S 3464, 0311, 0751 # JV-01, JV-01, JV-01 */
    #endif /* #if (ETH_GWCA0_ERR_ISR == STD_ON) */

    #if (ETH_COMA_ERR_ISR == STD_ON)
    /* Bit 18 - ESS[4] - Common Error Interrupt Mapping output source select */
    RH850_SV_MODE_ICR_OR(32, &LpINTSMIntReg->ulINTETNESEL3, (uint32) ETH_INTSM_COMA_ERR_MASK);                          /* PRQA S 3464, 0311 # JV-01, JV-01 */
    RH850_SV_MODE_ICR_AND(8, &LpEICIntReg->usINTETNE03, (uint8)(~ETH_EIC_EIMK_MASK));                                   /* PRQA S 3464, 0311, 0751 # JV-01, JV-01, JV-01 */
    #endif /* #if (ETH_COMA_ERR_ISR == STD_ON) */

    #if (ETH_ETHA0_ERR_ISR == STD_ON)
    /* Bit 14, 15 - ESS[0, 1] - ETHA0/1 Error Interrupt output source select */
    RH850_SV_MODE_ICR_OR(32, &LpINTSMIntReg->ulINTETNESEL4, (uint32) ETH_INTSM_ETHA0_ERR_MASK);                         /* PRQA S 3464, 0311 # JV-01, JV-01 */
    RH850_SV_MODE_ICR_AND(8, &LpEICIntReg->usINTETNE04, (uint8)(~ETH_EIC_EIMK_MASK));                                   /* PRQA S 3464, 0311, 0751 # JV-01, JV-01, JV-01 */
    #endif /* #if (ETH_ETHA0_ERR_ISR == STD_ON) */

    #if (ETH_ETHA1_ERR_ISR == STD_ON)
    /* Bit 14, 15 - ESS[0, 1] - ETHA0/1 Error Interrupt output source select */
    RH850_SV_MODE_ICR_OR(32, &LpINTSMIntReg->ulINTETNESEL5, (uint32) ETH_INTSM_ETHA1_ERR_MASK);                         /* PRQA S 3464, 0311 # JV-01, JV-01 */
    RH850_SV_MODE_ICR_AND(8, &LpEICIntReg->usINTETNE05, (uint8)(~ETH_EIC_EIMK_MASK));                                   /* PRQA S 3464, 0311, 0751 # JV-01, JV-01, JV-01 */
    #endif /* #if (ETH_ETHA1_ERR_ISR == STD_ON) */

    /* SGMII01 */
    #if (ETH_SGMII_ISR == STD_ON)
    /* Bit 21 - IISS[1] - SGMII interrupt 0 output source select */
    RH850_SV_MODE_ICR_OR(32, &LpINTSMIntReg->ulINTETNESEL7, (uint32)ETH_INTSM_SGMII0_MASK);                             /* PRQA S 3464, 0311 # JV-01, JV-01 */
    RH850_SV_MODE_ICR_AND(8, &LpEICIntReg->usINTETNE07, (uint8)(~ETH_EIC_EIMK_MASK));                                   /* PRQA S 3464, 0311, 0751 # JV-01, JV-01, JV-01 */

    /* Bit 20 - IISS[0] - SGMII interrupt 1 output source select */
    RH850_SV_MODE_ICR_OR(32, &LpINTSMIntReg->ulINTETNESEL8, (uint32)ETH_INTSM_SGMII1_MASK);                             /* PRQA S 3464, 0311 # JV-01, JV-01 */
    RH850_SV_MODE_ICR_AND(8, &LpEICIntReg->usINTETNE08, (uint8)(~ETH_EIC_EIMK_MASK));                                   /* PRQA S 3464, 0311, 0751 # JV-01, JV-01, JV-01 */
    #endif /* #if (ETH_SGMII_ISR == STD_ON) */
    break;

  case ETH_DISABLE_INTERRUPT:
    #if (ETH_GWCA0_DATA_ISR == STD_ON)
    /* Bit 0, 1 - DISS[0, 1] - GWDIS Data Interrupt Status 0/ 1 output source select */
    RH850_SV_MODE_ICR_AND(32, &LpINTSMIntReg->ulINTETNESEL0, (uint32)(~ETH_INTSM_GWDIS01_MASK));                        /* PRQA S 3464, 0311 # JV-01, JV-01 */
    RH850_SV_MODE_ICR_OR(8, &LpEICIntReg->usINTETNE00, (uint8)(ETH_EIC_EIMK_MASK));                                     /* PRQA S 3464, 0311, 0751 # JV-01, JV-01, JV-01 */
    #endif /* #if (ETH_GWCA0_DATA_ISR == STD_ON) */

    #if (ETH_GLOBAL_TIME_SUPPORT == STD_ON)
    /* Bit 8, 9 - TSS[0, 1] - TimeStamp Data Interrupt Status 0/ 1 output source select */
    RH850_SV_MODE_ICR_AND(32, &LpINTSMIntReg->ulINTETNESEL1, (uint32)(~ETH_INTSM_TSS_MASK));                            /* PRQA S 3464, 0311 # JV-01, JV-01 */
    RH850_SV_MODE_ICR_OR(8, &LpEICIntReg->usINTETNE01, (uint8)(ETH_EIC_EIMK_MASK));                                     /* PRQA S 3464, 0311, 0751 # JV-01, JV-01, JV-01 */
    #endif /* #if (ETH_GLOBAL_TIME_SUPPORT == STD_ON) */

    #if (ETH_GWCA0_ERR_ISR == STD_ON)
    /* Bit 16 - ESS[2] - GWCA0 Error Interrupt output source select */
    RH850_SV_MODE_ICR_AND(32, &LpINTSMIntReg->ulINTETNESEL2, (uint32)(~ETH_INTSM_GWCA0_ERR_MASK));                      /* PRQA S 3464, 0311 # JV-01, JV-01 */
    RH850_SV_MODE_ICR_OR(8, &LpEICIntReg->usINTETNE02, (uint8)(ETH_EIC_EIMK_MASK));                                     /* PRQA S 3464, 0311, 0751 # JV-01, JV-01, JV-01 */
    #endif /* #if (ETH_GWCA0_ERR_ISR == STD_ON) */

    #if (ETH_COMA_ERR_ISR == STD_ON)
    /* Bit 18 - ESS[4] - Common Error Interrupt Mapping output source select */
    RH850_SV_MODE_ICR_AND(32, &LpINTSMIntReg->ulINTETNESEL3, (uint32)(~ETH_INTSM_COMA_ERR_MASK));                       /* PRQA S 3464, 0311 # JV-01, JV-01 */
    RH850_SV_MODE_ICR_OR(8, &LpEICIntReg->usINTETNE03, (uint8)(ETH_EIC_EIMK_MASK));                                     /* PRQA S 3464, 0311, 0751 # JV-01, JV-01, JV-01 */
    #endif /* #if (ETH_COMA_ERR_ISR == STD_ON) */

    #if (ETH_ETHA0_ERR_ISR == STD_ON)
    /* Bit 14, 15 - ESS[0, 1] - ETHA0/1 Error Interrupt output source select */
    RH850_SV_MODE_ICR_AND(32, &LpINTSMIntReg->ulINTETNESEL4, (uint32)(~ETH_INTSM_ETHA0_ERR_MASK));                      /* PRQA S 3464, 0311 # JV-01, JV-01 */
    RH850_SV_MODE_ICR_OR(8, &LpEICIntReg->usINTETNE04, (uint8)(ETH_EIC_EIMK_MASK));                                     /* PRQA S 3464, 0311, 0751 # JV-01, JV-01, JV-01 */
    #endif /* #if (ETH_ETHA0_ERR_ISR == STD_ON) */

    #if (ETH_ETHA1_ERR_ISR == STD_ON)
    /* Bit 14, 15 - ESS[0, 1] - ETHA0/1 Error Interrupt output source select */
    RH850_SV_MODE_ICR_AND(32, &LpINTSMIntReg->ulINTETNESEL5, (uint32)(~ETH_INTSM_ETHA1_ERR_MASK));                      /* PRQA S 3464, 0311 # JV-01, JV-01 */
    RH850_SV_MODE_ICR_OR(8, &LpEICIntReg->usINTETNE05, (uint8)(ETH_EIC_EIMK_MASK));                                     /* PRQA S 3464, 0311, 0751 # JV-01, JV-01, JV-01 */
    #endif /* #if (ETH_ETHA1_ERR_ISR == STD_ON) */

    /* SGMII01 */
    #if (ETH_SGMII_ISR == STD_ON)
    /* Bit 21 - IISS[1] - SGMII interrupt 0 output source select */
    RH850_SV_MODE_ICR_AND(32, &LpINTSMIntReg->ulINTETNESEL7, (uint32)(~ETH_INTSM_SGMII0_MASK));                         /* PRQA S 3464, 0311 # JV-01, JV-01 */
    RH850_SV_MODE_ICR_OR(8, &LpEICIntReg->usINTETNE07, (uint8)(ETH_EIC_EIMK_MASK));                                     /* PRQA S 3464, 0311, 0751 # JV-01, JV-01, JV-01 */

    /* Bit 20 - IISS[0] - SGMII interrupt 1 output source select */
    RH850_SV_MODE_ICR_AND(32, &LpINTSMIntReg->ulINTETNESEL8, (uint32)(~ETH_INTSM_SGMII1_MASK));                         /* PRQA S 3464, 0311 # JV-01, JV-01 */
    RH850_SV_MODE_ICR_OR(8, &LpEICIntReg->usINTETNE08, (uint8)(ETH_EIC_EIMK_MASK));                                     /* PRQA S 3464, 0311, 0751 # JV-01, JV-01, JV-01 */
    #endif /* #if (ETH_SGMII_ISR == STD_ON) */
    break;
  
  default:
    /* No action required */
    break;
  }
 }
#endif /* #if ((ETH_GWCA0_DATA_ISR == STD_ON) || (ETH_GLOBAL_TIME_SUPPORT == STD_ON) || (ETH_GWCA0_ERR_ISR == STD_ON) ||
  (ETH_COMA_ERR_ISR == STD_ON) || (ETH_ETHA1_ERR_ISR == STD_ON) || (ETH_SGMII_ISR == STD_ON)) */
 
/***********************************************************************************************************************
** Function Name         : Eth_HwPostCommonInit (RSW2)
**
** Service ID            : N/A
**
** Description           : Post-Initialize the common parts of RSW2 HWUnit
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
** Return parameter      : E_OK : Success
**                         E_NOT_OK : Failure
**
** Preconditions         : None
**
** Global Variable(s)    : Eth_GaaRsw2GWCACtrlValid, Eth_GpRSW2_GPTPRegs,
**                         Eth_GaaRSW2_GWCARegs, Eth_GpGwcaRegPtr
**
** Function(s) invoked   : Eth_HwTOP_SwitchResetFlow,Eth_HwTOP_SwitchInitializationFlow,
**                         Eth_HwEnableInterrupt,Eth_HwEnableErrorInterrupt,
**                         Eth_HwGWCA_ModeTransitionFlow
**
** Registers Used        : PTPTIVCt, PTPTMEC, GWTSDIE, GWSCR0
**
** Reference ID          : ETH_DUD_ACT_441
** Reference ID          : ETH_DUD_ACT_441_GBL001, ETH_DUD_ACT_441_GBL002
** Reference ID          : ETH_DUD_ACT_441_GBL003, ETH_DUD_ACT_441_GBL004
** Reference ID          : ETH_DUD_ACT_441_REG001, ETH_DUD_ACT_441_REG002
** Reference ID          : ETH_DUD_ACT_441_REG003, ETH_DUD_ACT_441_REG004
***********************************************************************************************************************/
FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_HwPostCommonInit(void)                                                       
{
  Std_ReturnType LucResult;

  /**** Initialize RSW2 *****************************************************/
  #if (ETH_SWITCHING_MODE == ETH_SWMODE_ENDSTATION)
  /* [TOP] Switch Reset Flow */
  LucResult = Eth_HwTOP_SwitchResetFlow();

  if (E_OK == LucResult)
  {
    /* [TOP] Switch Initialization Flow */ 
    LucResult = Eth_HwTOP_SwitchInitializationFlow();
  } /* else No action required */
  #else
  /* [TOP] Switch Initialization Flow */
  LucResult = Eth_HwTOP_SwitchInitializationFlow();
  #endif /* ETH_SWITCHING_MODE == ETH_SWMODE_ENDSTATION */

  #if ((ETH_CTRL_ENABLE_TX_INTERRUPT == STD_ON) || (ETH_CTRL_ENABLE_RX_INTERRUPT == STD_ON))
  if (E_OK == LucResult)
  {
    /* Enable GWCA Interrupt */
    Eth_HwEnableInterrupt();
  } /* else No action required */
  #endif /* ((ETH_CTRL_ENABLE_TX_INTERRUPT == STD_ON) || (ETH_CTRL_ENABLE_RX_INTERRUPT == STD_ON)) */

  #if ((ETH_GWCA_ERR_ISR == STD_ON) || (ETH_COMA_ERR_ISR == STD_ON) || (ETH_ETHA_ERR_ISR == STD_ON))
  if (E_OK == LucResult)
  {
    /* Enable GWCA / COMA / ETHA Error Interrupt */
    Eth_HwEnableErrorInterrupt();
  } /* else No action required */
  #endif /* ((ETH_GWCA_ERR_ISR == STD_ON) || (ETH_COMA_ERR_ISR == STD_ON) || (ETH_ETHA_ERR_ISR == STD_ON)) */

  if (E_OK == LucResult)
  {
    #if (ETH_GLOBAL_TIME_SUPPORT == STD_ON)
    Eth_GpRSW2_GPTPRegs->PTP[ETH_GPTP_TIMER_DOMAIN].ulPTPTIVCt= ETH_GPTP_SET_PTPTIVC_320MHZ;
    Eth_GpRSW2_GPTPRegs->ulPTPTMEC = ETH_GPTP_TIMER_DOMAIN_ENABLE << ETH_GPTP_TIMER_DOMAIN;
    Eth_GaaRSW2_GWCARegs[ETH_RSW2_GWCA_ID]->ulGWTSDIE = ETH_GPTP_TIMER_DOMAIN_ENABLE << ETH_GPTP_TIMER_DOMAIN;          
    #endif /* ETH_GLOBAL_TIME_SUPPORT == STD_ON */

    if (ETH_TRUE != Eth_GaaRsw2GWCACtrlValid)
    {
      /* Mode transition flow to OPERATION mode */
      LucResult = Eth_HwGWCA_ModeTransitionFlow(ETH_RSW2_GWCA_ID, ETH_RSW2_GWCA_DISABLE_MODE);
      if (E_OK == LucResult)
      {
        LucResult = Eth_HwGWCA_ModeTransitionFlow(ETH_RSW2_GWCA_ID, ETH_RSW2_GWCA_OPERATION_MODE);
      } /* else No action required */
    }
  } /* else No action required */

  return LucResult;
}

/***********************************************************************************************************************
** Function Name         : Eth_ETNE_HwInit (RSW2)
**
** Service ID            : N/A
**
** Description           : Initialize a RSW2 HWUnit
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
** Global Variable(s)    : Eth_GpCtrlConfigPtr, Eth_GaaHeap,
**                         Eth_GaaMemPoolBufferTable, Eth_GaaRamSize,
**                         Eth_GaaRsw2PortValid, Eth_GaaRsw2PortCtrlIdx
**
** Function(s) invoked   : Eth_InitCounterValues,Eth_InitRxStats,
**                         Eth_InitTxStats,Eth_InitTxErrorCounterValues,
**                         Eth_Util_RamInit,Eth_TxRxDescConfig,
**                         Eth_Util_RamSetCircularAddr
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_308
** Reference ID          : ETH_DUD_ACT_409_GBL001, ETH_DUD_ACT_409_GBL002
** Reference ID          : ETH_DUD_ACT_409_GBL003
***********************************************************************************************************************/
FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_ETNE_HwInit(CONST(uint32, AUTOMATIC) LulCtrlIdx)                             
{
  P2CONST(Eth_ETNEConfigType, AUTOMATIC, ETH_APPL_DATA) LpHwUnitConfig;
  Std_ReturnType LucResult = E_NOT_OK;                                                                                  

  LpHwUnitConfig =
    (P2CONST(Eth_ETNEConfigType, AUTOMATIC, ETH_APPL_DATA))Eth_GpCtrlConfigPtr[LulCtrlIdx].pHwUnitConfig;               /* PRQA S 0316 # JV-01 */

  /* Initialize Statistics */
  #if (ETH_GET_COUNTER_VALUES_API == STD_ON)
  Eth_InitCounterValues(LulCtrlIdx);
  #endif
  #if (ETH_GET_RX_STATS_API == STD_ON)
  Eth_InitRxStats(LulCtrlIdx);
  #endif
  #if (ETH_GET_TX_STATS_API == STD_ON)
  Eth_InitTxStats(LulCtrlIdx);
  #endif
  #if (ETH_GET_TX_ERROR_COUNTER_VALUES_API == STD_ON)
  Eth_InitTxErrorCounterValues(LulCtrlIdx);
  #endif

  Eth_GaaHeap[LulCtrlIdx] = Eth_Util_RamInit(Eth_GaaMemPoolBufferTable[LulCtrlIdx], Eth_GaaRamSize[LulCtrlIdx]);        
  if (NULL_PTR != Eth_GaaHeap[LulCtrlIdx])
  {
    /* Tx/Rx descriptor chain setting */
    LucResult = Eth_TxRxDescConfig(LulCtrlIdx);
    if (E_OK == LucResult)
    {
      /* Set circular address for Tx buffers */
      Eth_Util_RamSetCircularAddr(Eth_GaaHeap[LulCtrlIdx]);                                                             

      /* Rx Multicast(Mirroring) setting table is not supported */

    } /* else: No action required */
  }
  else
  {
    LucResult = E_NOT_OK;
  }

  if (E_OK == LucResult)
  {
    Eth_GaaRsw2PortValid[LpHwUnitConfig->ulEthPortId] = ETH_TRUE;                                                       
    Eth_GaaRsw2PortCtrlIdx[LpHwUnitConfig->ulEthPortId] = LulCtrlIdx;                                                   
  }
  else
  {
    Eth_GaaRsw2PortValid[LpHwUnitConfig->ulEthPortId] = ETH_FALSE;                                                      
  }

  return LucResult;
}

#ifdef ETH_HW_COMMON_DEINIT
/***********************************************************************************************************************
** Function Name         : Eth_HwPreCommonDeInit (ETNE)
**
** Service ID            : N/A
**
** Description           : Initialize the common parts of ETNE HwDeInit
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
** Return parameter      : E_OK : Success
**
** Preconditions         : None
**
** Global Variable(s)    : None
**
** Function(s) invoked   : Eth_InterruptHandling
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_372
***********************************************************************************************************************/
FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_HwPreCommonDeInit(void)                                                      /* PRQA S 1503 # JV-01 */
{
  #if ((ETH_GWCA0_DATA_ISR == STD_ON) || (ETH_GLOBAL_TIME_SUPPORT == STD_ON) || (ETH_GWCA0_ERR_ISR == STD_ON) || \
  (ETH_COMA_ERR_ISR == STD_ON) || (ETH_ETHA1_ERR_ISR == STD_ON) || (ETH_SGMII_ISR == STD_ON))
  /* Disable interrupt handling */
  Eth_InterruptHandling(ETH_DISABLE_INTERRUPT);
  #endif /* #if ((ETH_GWCA0_DATA_ISR == STD_ON) || (ETH_GLOBAL_TIME_SUPPORT == STD_ON) || (ETH_GWCA0_ERR_ISR == STD_ON)
  || (ETH_COMA_ERR_ISR == STD_ON) || (ETH_ETHA1_ERR_ISR == STD_ON) || (ETH_SGMII_ISR == STD_ON)) */

  return E_OK;
}

/***********************************************************************************************************************
** Function Name         : Eth_HwPostCommonDeInit (ETNE)
**
** Service ID            : N/A
**
** Description           : Initialize the common parts of ETNE HwDeInit
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
** Return parameter      : E_OK : Success
**
** Preconditions         : None
**
** Global Variable(s)    : None
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_373
***********************************************************************************************************************/
FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_HwPostCommonDeInit(void)                                                     /* PRQA S 1503 # JV-01 */
{
  return E_OK;
}
#endif /* ETH_HW_COMMON_DEINIT*/

/***********************************************************************************************************************
** Function Name         : Eth_ETNE_HwDisableController (RSW2)
**
** Service ID            : N/A
**
** Description           : Changes the state of an RSW2 controller as DOWN
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
** Global Variable(s)    : Eth_GpCtrlConfigPtr, Eth_GaaTxBufferTotal,
**                         Eth_GaaTxBufferMgrTable, Eth_GaaCtrlStat,
**                         Eth_GaaRsw2PortType,
**
** Function(s) invoked   : Eth_HwETHA_ModeTransitionFlow,Eth_HwETHA_TasDisablingFlow,
**                         Eth_HwGWCA_ModeTransitionFlow,Eth_ReleaseTxBuffer
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_410
** Reference ID          : ETH_DUD_ACT_410_GBL001, ETH_DUD_ACT_410_GBL002
** Reference ID          : ETH_DUD_ACT_410_GBL003, ETH_DUD_ACT_410_GBL004
** Reference ID          : ETH_DUD_ACT_410_GBL005
***********************************************************************************************************************/
FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_ETNE_HwDisableController(                                                    
  CONST(uint32, AUTOMATIC) LulCtrlIdx)
{
  P2CONST(Eth_ETNEConfigType, AUTOMATIC, ETH_APPL_DATA) LpHwUnitConfig;
  P2VAR(Eth_ExtTxDirDescType, AUTOMATIC, ETH_APPL_DATA) LpTxDirDesc;                                                    /* PRQA S 3432 # JV-01 */
  P2VAR(Eth_ExtRxEthDescType, AUTOMATIC, ETH_APPL_DATA) LpRxEthDesc;                                                    /* PRQA S 3432 # JV-01 */
  Std_ReturnType LucResult = E_OK;
  uint32 LulCnt;
  uint32 LulETHAIdx;
  uint32 LulGWCAIdx;
  uint32 LulQIdx;

  LpHwUnitConfig =
    (P2CONST(Eth_ETNEConfigType, AUTOMATIC, ETH_APPL_DATA))Eth_GpCtrlConfigPtr[LulCtrlIdx].pHwUnitConfig;               /* PRQA S 0316 # JV-01 */

  if (ETH_RSW2_PORT_TYPE_ETHA == Eth_GaaRsw2PortType[LpHwUnitConfig->ulEthPortId])                                      
  {

    LulETHAIdx = ETH_CONV_PORTID_TO_ETHAID(LpHwUnitConfig->ulEthPortId);                                                /* PRQA S 3469 # JV-01 */

    /* Set to CONFIG mode to enable MDIO communication.  */
    LucResult = Eth_HwETHA_ModeTransitionFlow(LulETHAIdx, ETH_RSW2_ETHA_DISABLE_MODE);
    if (E_OK == LucResult)
    {
      LucResult = Eth_HwETHA_ModeTransitionFlow(LulETHAIdx, ETH_RSW2_ETHA_CONFIG_MODE);
      #if (ETH_GLOBAL_TIME_SUPPORT == STD_ON)
      if ((ETH_ENABLE == LpHwUnitConfig->stTASConfig.enTasEnable) && (E_OK == LucResult))
      {
        /* Set to TAS disable. */
        LucResult = Eth_HwETHA_TasDisablingFlow(LulETHAIdx);
      } /* else No action required */
      #endif /* ETH_GLOBAL_TIME_SUPPORT == STD_ON */
    } /* else No action required */

    /* When DISABLE of ETHA is requested, ETHA discards any subsequent Descriptors.
     * In addition, ETHA waits until the processing of all Descriptors being processed is
     * completed before transitioning to DISBALE.
     * This Descriptor is a Descriptor for ETHA, not the GWCA's Descriptor used by the driver.
     * That is, after exiting the above function, all ETHA Descriptors are FEMPTY,
     * but GWCA Descriptors are not always FEMPTY.
     * Since GWCA continues to move even after ETHA becomes DISABLE,
     * GWCA's Descriptor will also be FEMPTY at the end, but the timing will be different.
     * The order of changes in ETHA status and changes in GWCA Descriptor is in no particular order. */
  }
  else /* GWCA */
  {
    /* Set to CONFIG mode to enable MDIO communication.  */
    LulGWCAIdx = ETH_CONV_PORTID_TO_GWCAID(LpHwUnitConfig->ulEthPortId);                                                /* PRQA S 3383, 3432 # JV-01, JV-01 */
    LucResult = Eth_HwGWCA_ModeTransitionFlow(LulGWCAIdx, ETH_RSW2_GWCA_DISABLE_MODE);
    if (E_OK == LucResult)
    {
      LucResult = Eth_HwGWCA_ModeTransitionFlow(LulGWCAIdx, ETH_RSW2_GWCA_CONFIG_MODE);
    } /* else No action required */

    /* When DISABLE of GWCA is requested, GWCA waits until the processing of
     * all GWCA Descriptors being processed is completed before transitioning to DISBALE.
     * That is, after exiting the above function, all GWCA Descriptors are FEMPTY. */
  }


  if (E_OK == LucResult)
  {
    /* Release all Tx Buffer */
    for (LulCnt = 0UL; LulCnt < Eth_GaaTxBufferTotal[LulCtrlIdx]; LulCnt++)                                             
    {
      if (NULL_PTR != Eth_GaaTxBufferMgrTable[LulCtrlIdx][LulCnt].pBufferHdr)                                           
      {
        Eth_ETNE_ReleaseTxBuffer(LulCtrlIdx, Eth_GaaTxBufferMgrTable[LulCtrlIdx][LulCnt].pBufferHdr->ulbufIdx);         
      } /* else No action required */
    }

    /* Release all Tx Descriptor */
    for (LulQIdx = 0UL; LulQIdx < (uint32)LpHwUnitConfig->stQueueConfig.ucNumberOfTxQueue; LulQIdx++)
    {
      LpTxDirDesc = Eth_GaaCtrlStat[LulCtrlIdx].stHwStat.aaHeadTxDesc[LulQIdx];                                         
      while (LpTxDirDesc != Eth_GaaCtrlStat[LulCtrlIdx].stHwStat.aaNextTxDesc[LulQIdx])
      {
        /* Clear Tx Descriptor */
        LpTxDirDesc->stHeader.ulDs    = 0U;                                                                             
        LpTxDirDesc->stHeader.ulInfo0 = 0U;
        LpTxDirDesc->stHeader.ulErr   = 0U;
        LpTxDirDesc->stHeader.ulDse   = 0U;
        LpTxDirDesc->stHeader.ulAxie  = 0U;
        LpTxDirDesc->stHeader.ulDie   = 0U;
        LpTxDirDesc->stHeader.ulDptrH = 0U;
        LpTxDirDesc->stHeader.ulDptr  = 0U;
        LpTxDirDesc->ulTxc = 0U;
        LpTxDirDesc->ulTsun = 0U;
        LpTxDirDesc->stHeader.ulDt    = ETH_DESC_FEMPTY;

        /* Set next descriptor */
        LpTxDirDesc++;                                                                                                  
        while (LpTxDirDesc->stHeader.ulDt == ETH_DESC_LINKFIX_RSW2)                                                     
        {
          LpTxDirDesc = (Eth_ExtTxDirDescType *)LpTxDirDesc->stHeader.ulDptr;                                           /* PRQA S 0306 # JV-01 */
        }
      }
      Eth_GaaCtrlStat[LulCtrlIdx].stHwStat.aaHeadTxDesc[LulQIdx] = LpTxDirDesc;                                         
      Eth_GaaCtrlStat[LulCtrlIdx].stHwStat.aaBufTxCnt[LulQIdx] = 0UL;                                                   
    }

    /* Release all Rx Descriptor */
    for (LulQIdx = 0UL; LulQIdx < (uint32)LpHwUnitConfig->stQueueConfig.ucNumberOfRxQueue; LulQIdx++)
    {
      LpRxEthDesc = Eth_GaaCtrlStat[LulCtrlIdx].stHwStat.aaNextRxDesc[LulQIdx];                                         
      while (ETH_DESC_FSINGLE == LpRxEthDesc->stHeader.ulDt)
      {
        /* Clear Rx Descriptor */
        LpRxEthDesc->stHeader.ulDs      = LpHwUnitConfig->stRxConfig.ulMaxFrameSize;
        LpRxEthDesc->stHeader.ulInfo0   = 0U;
        LpRxEthDesc->stHeader.ulAxie    = 0U;
        LpRxEthDesc->stHeader.ulDse     = 0U;
        LpRxEthDesc->stHeader.ulErr     = 0U;
        #if (ETH_GLOBAL_TIME_SUPPORT == STD_ON)
        LpRxEthDesc->stTimestamp.ulTSNS = (uint32)0UL;
        LpRxEthDesc->stTimestamp.ulTSV  = 0U;
        LpRxEthDesc->stTimestamp.ulTSD  = 0U;
        LpRxEthDesc->stTimestamp.ulTSS  = 0U;
        #endif /* ETH_GLOBAL_TIME_SUPPORT */
        LpRxEthDesc->stHeader.ulDt      = ETH_DESC_FEMPTY;

        /* Set next descriptor */
        LpRxEthDesc++;
        while (LpRxEthDesc->stHeader.ulDt == ETH_DESC_LINKFIX_RSW2)
        {
          LpRxEthDesc = (Eth_ExtRxEthDescType *)LpRxEthDesc->stHeader.ulDptr;                                           /* PRQA S 0306 # JV-01 */
        }
      }
      Eth_GaaCtrlStat[LulCtrlIdx].stHwStat.aaNextRxDesc[LulQIdx] = LpRxEthDesc;
    }
  }
  else
  {
    Eth_GaaCtrlStat[LulCtrlIdx].enMode = ETH_MODE_ACTIVE;
  }

  return LucResult;
}

/***********************************************************************************************************************
** Function Name         : Eth_ETNE_HwEnableController (RSW2)
**
** Service ID            : N/A
**
** Description           : Changes the state of an RSW2 controller as ACTIVE
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
** Global Variable(s)    : Eth_GaaCtrlStat, Eth_GpCtrlConfigPtr,
**                         Eth_GaaRsw2PortType, Eth_GaaCtrl_RMACRegs,
**                         Eth_GaaRSW2_GWCARegs
**
** Function(s) invoked   : Eth_HwETHA_TasSettingFlow,Eth_HwETHA_TasEnablingFlow,
**                         Eth_HwETHA_ModeTransitionFlow,Eth_HwGWCA_ModeTransitionFlow
**                         Eth_HwRMAC_LinkVerification
**
** Registers Used        : MRMAC0, MRMAC1, GWMAC0, GWMAC1
**
** Reference ID          : ETH_DUD_ACT_411
** Reference ID          : ETH_DUD_ACT_411_GBL001, ETH_DUD_ACT_411_GBL002
** Reference ID          : ETH_DUD_ACT_411_GBL003, ETH_DUD_ACT_411_GBL004
** Reference ID          : ETH_DUD_ACT_411_GBL005, ETH_DUD_ACT_411_GBL006
** Reference ID          : ETH_DUD_ACT_411_REG001, ETH_DUD_ACT_411_REG002
** Reference ID          : ETH_DUD_ACT_411_REG003, ETH_DUD_ACT_411_REG004
***********************************************************************************************************************/
FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_ETNE_HwEnableController(CONST(uint32, AUTOMATIC) LulCtrlIdx)                 
{
  P2CONST(Eth_ETNEConfigType, AUTOMATIC, ETH_APPL_DATA) LpHwUnitConfig;
  Std_ReturnType LucResult = E_OK;

  uint32 LulETHAIdx;
  uint32 LulGWCAIdx;

  LpHwUnitConfig =
    (P2CONST(Eth_ETNEConfigType, AUTOMATIC, ETH_APPL_DATA))Eth_GpCtrlConfigPtr[LulCtrlIdx].pHwUnitConfig;               /* PRQA S 0316 # JV-01 */

  if (ETH_RSW2_PORT_TYPE_ETHA == Eth_GaaRsw2PortType[LpHwUnitConfig->ulEthPortId])                                      
  {
    /* Set MAC address */
    Eth_GaaCtrl_RMACRegs[LulCtrlIdx]->ulMRMAC0 =                                                                        
      Eth_GaaCtrlStat[LulCtrlIdx].stMacAddr.ulH32 >> 16UL;                                                              
    Eth_GaaCtrl_RMACRegs[LulCtrlIdx]->ulMRMAC1 =
      (Eth_GaaCtrlStat[LulCtrlIdx].stMacAddr.ulH32 << 16UL) | Eth_GaaCtrlStat[LulCtrlIdx].stMacAddr.ulL16;

    LulETHAIdx = ETH_CONV_PORTID_TO_ETHAID(LpHwUnitConfig->ulEthPortId);                                                /* PRQA S 3469 # JV-01 */

    #if (ETH_GLOBAL_TIME_SUPPORT == STD_ON)
    if (ETH_ENABLE == LpHwUnitConfig->stTASConfig.enTasEnable)
    {
      /*TAS setting flow*/
      LucResult = Eth_HwETHA_TasSettingFlow(LulETHAIdx);
      if (E_OK == LucResult)
      {
        /*TAS enabling flow*/
        Eth_HwETHA_TasEnablingFlow(LulETHAIdx);
      } /* else No action required */
    } /* else No action required */
    #endif /* ETH_GLOBAL_TIME_SUPPORT */

    if (E_OK == LucResult)                                                                                              /* PRQA S 2991, 2995 # JV-01, JV-01 */
    {
      /* Set EAMC mode to OPERATION */
      LucResult = Eth_HwETHA_ModeTransitionFlow(LulETHAIdx, ETH_RSW2_ETHA_DISABLE_MODE);
      if (E_OK == LucResult)
      {
        LucResult = Eth_HwETHA_ModeTransitionFlow(LulETHAIdx, ETH_RSW2_ETHA_OPERATION_MODE);
      } /* else No action required */
    } /* else No action required */
  }
  else /* GWCA */
  {
    LulGWCAIdx = ETH_CONV_PORTID_TO_GWCAID(LpHwUnitConfig->ulEthPortId);                                                /* PRQA S 3383, 3432 # JV-01, JV-01 */

    /* Set MAC address */
    /* GWMAC0 Set */
    Eth_GaaRSW2_GWCARegs[LulGWCAIdx]->ulGWMAC0 =                                                                        
      Eth_GaaCtrlStat[LulCtrlIdx].stMacAddr.ulH32 >> 16UL;
    /* GWMAC1 Set */
    Eth_GaaRSW2_GWCARegs[LulGWCAIdx]->ulGWMAC1 =
      (Eth_GaaCtrlStat[LulCtrlIdx].stMacAddr.ulH32 << 16UL) | Eth_GaaCtrlStat[LulCtrlIdx].stMacAddr.ulL16;

    /* Set GWCA mode to OPERATION */
    LucResult = Eth_HwGWCA_ModeTransitionFlow(LulGWCAIdx, ETH_RSW2_GWCA_DISABLE_MODE);
    if (E_OK == LucResult)
    {
      LucResult = Eth_HwGWCA_ModeTransitionFlow(LulGWCAIdx, ETH_RSW2_GWCA_OPERATION_MODE);
    } /* else No action required */
  }

  return LucResult;
}

/***********************************************************************************************************************
** Function Name         : Eth_ETNE_HwTransmit (RSW2)
**
** Service ID            : N/A
**
** Description           : Initiates a transmission on an RSW2 controller.
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
** Global Variable(s)    : Eth_GpCtrlConfigPtr,
**                         Eth_GaaTxBufferMgrTable, Eth_GaaCtrlStat,
**                         Eth_GaaRsw2PortType, Eth_GaaRSW2_GWCARegs
**
** Function(s) invoked   : Eth_CheckProvideBuffer, EthSwt_EthTxFinishedIndication
**
** Registers Used        : GWTRCi
**
** Reference ID          : ETH_DUD_ACT_412
** Reference ID          : ETH_DUD_ACT_412_CRT001, ETH_DUD_ACT_412_CRT002
** Reference ID          : ETH_DUD_ACT_412_CRT003, ETH_DUD_ACT_412_CRT004
** Reference ID          : ETH_DUD_ACT_412_GBL001, ETH_DUD_ACT_412_GBL002
** Reference ID          : ETH_DUD_ACT_412_GBL003, ETH_DUD_ACT_412_GBL004
** Reference ID          : ETH_DUD_ACT_412_GBL005
** Reference ID          : ETH_DUD_ACT_412_REG001
***********************************************************************************************************************/
FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_ETNE_HwTransmit(                                                             
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulBufIdx,
  CONST(uint32, AUTOMATIC) LulLenByte, CONST(boolean, AUTOMATIC) LblConfirmation)
{
  P2CONST(Eth_ETNEConfigType, AUTOMATIC, ETH_APPL_DATA) LpHwUnitConfig;
  P2VAR(Eth_ExtTxDirDescType, AUTOMATIC, ETH_APPL_DATA) LpDataDesc;                                                     /* PRQA S 3432 # JV-01 */
  Std_ReturnType LucTxBufferProvide;
  Std_ReturnType LucReturnValue;
  P2VAR(Eth_BufHandlerType, AUTOMATIC, ETH_APPL_DATA) LpBufHandlerPtr;                                                  /* PRQA S 3432 # JV-01 */
  uint32 LulOldBufIdx;
  uint32 LulChainId;
  uint32 LulRegSet;
  uint32 LulRegSetBit;

  LucTxBufferProvide = E_NOT_OK;
  LucReturnValue = E_OK;

  LpHwUnitConfig =
    (P2CONST(Eth_ETNEConfigType, AUTOMATIC, ETH_APPL_DATA))Eth_GpCtrlConfigPtr[LulCtrlIdx].pHwUnitConfig;               /* PRQA S 0316 # JV-01 */

  ETH_ENTER_CRITICAL_SECTION(ETH_RAM_DATA_PROTECTION);

  /* Get Tx buffer handler */
  Eth_GaaTxBufferMgrTable[LulCtrlIdx][LulBufIdx].blTxOngoing = ETH_TRUE;                                                
  LpBufHandlerPtr = Eth_GaaTxBufferMgrTable[LulCtrlIdx][LulBufIdx].pBufferHdr;

  ETH_EXIT_CRITICAL_SECTION(ETH_RAM_DATA_PROTECTION);

  /* Set Tx request length */
  LpBufHandlerPtr->ulTxLength = (uint32)ETH_HEADER_SIZE + LulLenByte;                                                   /* PRQA S 3383 # JV-01 */

  /* Set Tx confirmation flag */
  LpBufHandlerPtr->blTxConfirm = LblConfirmation;

  /* Get next free descriptor */
  LpDataDesc = Eth_GaaCtrlStat[LulCtrlIdx].stHwStat.aaNextTxDesc[LpBufHandlerPtr->ucPriority];                          

  if (0UL != LpDataDesc->stHeader.ulDptr)                                                                               
  {
    /* Check previous TxBuffer release status (The memory leak protect) */
    LulOldBufIdx = (uint32)((uint32)LpDataDesc->ulTsun - (LulCtrlIdx * ETH_TX_DESCR_TSUN_OFFSET));                      /* PRQA S 3383, 3384 # JV-01, JV-01 */
    LucTxBufferProvide = Eth_ETNE_CheckProvideBuffer(LulCtrlIdx, LulOldBufIdx);
  } /* else No action required */

  if ((ETH_DESC_FEMPTY == LpDataDesc->stHeader.ulDt) && (E_NOT_OK == LucTxBufferProvide))
  {
    /* build the descriptor */
    LpDataDesc->stHeader.ulInfo0 = 0x0U;
    LpDataDesc->stHeader.ulDs    = LpBufHandlerPtr->ulTxLength;
    LpDataDesc->stHeader.ulDptrH = 0x0U;
    LpDataDesc->stHeader.ulDptr  = LpBufHandlerPtr->ulbufAddr;
    LpDataDesc->ulTsun           = (uint8)(LpBufHandlerPtr->ulbufIdx + (LulCtrlIdx * ETH_TX_DESCR_TSUN_OFFSET));        /* PRQA S 3383 # JV-01 */
    if (ETH_RSW2_PORT_TYPE_ETHA == Eth_GaaRsw2PortType[LpHwUnitConfig->ulEthPortId])                                    
    {
      LpDataDesc->ulDv           = (1UL << LpHwUnitConfig->ulEthPortId);
      LpDataDesc->ulIpv          = LpBufHandlerPtr->ucPriority;
    } /* else No action required */

    if (ETH_TRUE == LpBufHandlerPtr->blbenableTS)
    {
      LpDataDesc->ulTxc = 0x1U; /* TX Timestamp capture */
      LpDataDesc->ulTn = ETH_GPTP_TIMER_DOMAIN;
    }
    else
    {
      LpDataDesc->ulTxc = 0x0U;
    }

    if (ETH_ENABLE == Eth_GpCtrlConfigPtr[LulCtrlIdx].pEthConfig->enTxInterruptMode)                                    /* PRQA S 3416 # JV-01 */
    {
      LpDataDesc->stHeader.ulDie = 0x1U;
    }
    else
    {
      LpDataDesc->stHeader.ulDie = 0x0U;
    }
    LpDataDesc->stHeader.ulDt    = ETH_DESC_FSINGLE;

    /* Set next descriptor */
    LpDataDesc++;                                                                                                       
    while (LpDataDesc->stHeader.ulDt == ETH_DESC_LINKFIX_RSW2)                                                          
    {
      LpDataDesc = (P2VAR(Eth_ExtTxDirDescType, AUTOMATIC, ETH_APPL_DATA)) LpDataDesc->stHeader.ulDptr;                 /* PRQA S 0306, 3432 # JV-01, JV-01 */
    }

    Eth_GaaCtrlStat[LulCtrlIdx].stHwStat.aaNextTxDesc[LpBufHandlerPtr->ucPriority] = LpDataDesc;                        

    ETH_ENTER_CRITICAL_SECTION(ETH_RAM_DATA_PROTECTION);

    /* Increase the number of buffer of current Tx queue */
    Eth_GaaCtrlStat[LulCtrlIdx].stHwStat.aaBufTxCnt[LpBufHandlerPtr->ucPriority]++;                                     /* PRQA S 3383 # JV-01 */

    ETH_EXIT_CRITICAL_SECTION(ETH_RAM_DATA_PROTECTION);

    /* Transmit start request */
    LulChainId = LpHwUnitConfig->stQueueConfig.pTxQueueConfig[LpBufHandlerPtr->ucPriority].ulChainId;                   
    LulRegSet = LulChainId / ETH_RSW2_GWCA_NUM_OF_CHAIN_PER_REG;
    LulRegSetBit = LulChainId % ETH_RSW2_GWCA_NUM_OF_CHAIN_PER_REG;
    Eth_GaaRSW2_GWCARegs[ETH_RSW2_GWCA_ID]->ulGWTRCi[LulRegSet] = (uint32)(1UL << LulRegSetBit);                        

    #if (ETH_ETHSWITCH_MANAGEMENT_SUPPORT == STD_ON)
    /* Indication for a finished transmit process for a specific Ethernet frame. */
    /* Since the maximum value of controller index is 4, casting to uint8 does no problem. */
    (void)EthSwt_EthTxFinishedIndication((uint8)LulCtrlIdx, (Eth_BufIdxType)LpBufHandlerPtr->ulbufIdx);
    #endif
  }
  else
  {
    LucReturnValue = E_NOT_OK;
  }

  return LucReturnValue;
}

#if (ETH_CTRL_ENABLE_TX_POLLING == STD_ON)
/***********************************************************************************************************************
** Function Name         : Eth_ETNE_HwTxConfirmation (RSW2)
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
** Global Variable(s)    : Eth_GaaCtrlStat
**
** Function(s) invoked   : Eth_TxConfirmationQueueProcess
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_413
** Reference ID          : ETH_DUD_ACT_413_GBL001, ETH_DUD_ACT_413_GBL002
***********************************************************************************************************************/
FUNC(void, ETH_PRIVATE_CODE) Eth_ETNE_HwTxConfirmation(CONST(uint32, AUTOMATIC) LulCtrlIdx)                             
{
  P2CONST(Eth_ETNEConfigType, AUTOMATIC, ETH_APPL_DATA) LpHwUnitConfig;
  uint32 LulQIdx;

  LpHwUnitConfig =
    (P2CONST(Eth_ETNEConfigType, AUTOMATIC, ETH_APPL_DATA))Eth_GpCtrlConfigPtr[LulCtrlIdx].pHwUnitConfig;               /* PRQA S 0316 # JV-01 */

  /* Check the status of the tx descriptor */
  for (LulQIdx = 0UL; LulQIdx < (uint32)LpHwUnitConfig->stQueueConfig.ucNumberOfTxQueue; LulQIdx++)                     
  {
    if (Eth_GaaCtrlStat[LulCtrlIdx].stHwStat.aaBufTxCnt[LulQIdx] > 0UL)                                                 
    {
      Eth_TxConfirmationQueueProcess(LulCtrlIdx, LulQIdx);
    }
  }
}
#endif /* (ETH_CTRL_ENABLE_TX_POLLING == STD_ON) */

#if (ETH_CTRL_ENABLE_RX_POLLING == STD_ON)
/***********************************************************************************************************************
** Function Name         : Eth_ETNE_HwReceive (RSW2)
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
**                         LulFifoIdx     : Index of a Fifo
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
** Function(s) invoked   : Eth_RxQueueProcess
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_313
** Reference ID          : ETH_DUD_ACT_313_GBL001, ETH_DUD_ACT_313_GBL002
** Reference ID          : ETH_DUD_ACT_313_GBL003
** Reference ID          : ETH_DUD_ACT_313_REG001
***********************************************************************************************************************/
FUNC(Eth_RxStatusType, ETH_PRIVATE_CODE) Eth_ETNE_HwReceive(                                                            
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulQueueIdx)
{
  Eth_ExtRxStatusType LenRetValue;

  /* Receive the specified queue */
  do
  {
    LenRetValue = Eth_RxQueueProcess(LulCtrlIdx, (uint8)LulQueueIdx);
  } while (ETH_EXT_NOT_RECEIVED_MORE_DATA_AVAILABLE == LenRetValue);
  return (Eth_RxStatusType)LenRetValue;                                                                                 /* PRQA S 4322 # JV-01 */
}
/***********************************************************************************************************************
** Function Name         : Eth_ETNE_HwCheckFifoIndex (RSW2)
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
**                         LulFifoIdx     : the FIFO index
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
** Reference ID          : ETH_DUD_ACT_328
***********************************************************************************************************************/
FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_ETNE_HwCheckFifoIndex(                                                       
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulQueueIdx)
{
  Std_ReturnType LucReturnValue;

  (void)LulCtrlIdx;

  LucReturnValue = E_OK;

  /* Validity check for the FIFO index */
  if (ETH_RXQ_NUM_RSW2 <= LulQueueIdx)
  {
    LucReturnValue = E_NOT_OK;
  } /* else No action required */

  return LucReturnValue;
}
#endif /* (ETH_CTRL_ENABLE_RX_POLLING == STD_ON) */

#if (ETH_CTRL_ENABLE_MII == STD_ON)
/***********************************************************************************************************************
** Function Name         : Eth_ETNE_HwReadMii (RSW2)
**
** Service ID            : N/A
**
** Description           : Read data from the PHY management interface
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : LulCtrlIdx     : Index of a controller
**                         LucTrcvIdx     : Index of the transceiver on the MII
**                         LucRegIdx      : Index of the transceiver register on the MII
**                         LpRegValPtr    : Value of indexed register
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : LucResult (E_OK / E_NOT_OK)
**
** Preconditions         : None
**
** Global Variable(s)    : Eth_GaaRsw2PortType, Eth_GpCtrlConfigPtr
**
** Function(s) invoked   : Eth_HwRMAC_PhyMdioReadAccessFlow
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_416
** Reference ID          : ETH_DUD_ACT_416_GBL001, ETH_DUD_ACT_416_GBL002
***********************************************************************************************************************/
FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_ETNE_HwReadMii(                                                              
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint8, AUTOMATIC) LucTrcvIdx, CONST(uint8, AUTOMATIC) LucRegIdx,
  CONSTP2VAR(uint16, AUTOMATIC, ETH_APPL_DATA) LpRegValPtr)                                                             /* PRQA S 3432 # JV-01 */
{
  P2CONST(Eth_ETNEConfigType, AUTOMATIC, ETH_APPL_DATA) LpHwUnitConfig;
  Std_ReturnType LucResult;

  LpHwUnitConfig =
    (P2CONST(Eth_ETNEConfigType, AUTOMATIC, ETH_APPL_DATA))Eth_GpCtrlConfigPtr[LulCtrlIdx].pHwUnitConfig;               /* PRQA S 0316 # JV-01 */

  if (ETH_RSW2_PORT_TYPE_ETHA == Eth_GaaRsw2PortType[LpHwUnitConfig->ulEthPortId])                                      

  {
    LucResult = Eth_HwRMAC_PhyMdioReadAccessFlow(
    ETH_CONV_PORTID_TO_RMACID(LpHwUnitConfig->ulEthPortId), LucTrcvIdx, LucRegIdx, LpRegValPtr);                        /* PRQA S 3469 # JV-01 */
  }
  else
  {
    *LpRegValPtr = (uint16)0x0UL;                                                                                       
    LucResult = E_NOT_OK;
  }

  return LucResult;                                                                                                     
}

/***********************************************************************************************************************
** Function Name         : Eth_ETNE_HwWriteMii (RSW2)
**
** Service ID            : N/A
**
** Description           : Write data to the PHY management interface
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : LulCtrlIdx     : Index of a controller
**                         LucTrcvIdx     : Index of the transceiver on the MII
**                         LucRegIdx      : Index of the transceiver register on the MII
**                         LusRegVal      : Value to be written into the indexed
**                                          register
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : LucResult (E_OK / E_NOT_OK)
**
** Preconditions         : None
**
** Global Variable(s)    : Eth_GaaRsw2PortType, Eth_GpCtrlConfigPtr
**
** Function(s) invoked   : Eth_HwRMAC_PhyMdioWriteAccessFlow
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_417
** Reference ID          : ETH_DUD_ACT_417_GBL001, ETH_DUD_ACT_417_GBL002
***********************************************************************************************************************/
FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_ETNE_HwWriteMii(                                                             
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint8, AUTOMATIC) LucTrcvIdx,
  CONST(uint8, AUTOMATIC) LucRegIdx, CONST(uint16, AUTOMATIC) LusRegVal)
{
  P2CONST(Eth_ETNEConfigType, AUTOMATIC, ETH_APPL_DATA) LpHwUnitConfig;
  Std_ReturnType LucResult = E_NOT_OK;

  LpHwUnitConfig =
    (P2CONST(Eth_ETNEConfigType, AUTOMATIC, ETH_APPL_DATA))Eth_GpCtrlConfigPtr[LulCtrlIdx].pHwUnitConfig;               /* PRQA S 0316 # JV-01 */

  if (ETH_RSW2_PORT_TYPE_ETHA == Eth_GaaRsw2PortType[LpHwUnitConfig->ulEthPortId])                                      
  {
    LucResult = Eth_HwRMAC_PhyMdioWriteAccessFlow(
      ETH_CONV_PORTID_TO_RMACID(LpHwUnitConfig->ulEthPortId), LucTrcvIdx, LucRegIdx, LusRegVal);                        /* PRQA S 3469 # JV-01 */
  } /* else No action required */

  return LucResult;
}
#endif /* (ETH_CTRL_ENABLE_MII == STD_ON) */

#if (ETH_GET_COUNTER_VALUES_API == STD_ON)
/***********************************************************************************************************************
** Function Name         : Eth_ETNE_HwGetCounterValues (RSW2)
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
** Global Variable(s)    : Eth_GaaCtrlStat
**
** Function(s) invoked   : Eth_InitCounterValues
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_316
** Reference ID          : ETH_DUD_ACT_316_GBL001
***********************************************************************************************************************/
FUNC(void, ETH_PRIVATE_CODE) Eth_ETNE_HwGetCounterValues(                                                               
  CONST(uint32, AUTOMATIC) LulCtrlIdx,
  CONSTP2VAR(Eth_CounterType, AUTOMATIC, ETH_APPL_DATA) LpCounterPtr)                                                   /* PRQA S 3432 # JV-01 */
{
  CONSTP2VAR(Eth_CounterType, AUTOMATIC, ETH_APPL_DATA) LpCounter =                                                     /* PRQA S 3432, 3678 # JV-01, JV-01 */
    (Eth_CounterType *)&Eth_GaaCtrlStat[LulCtrlIdx].stCounter;                                                          

  LpCounterPtr->DropPktBufOverrun = LpCounter->DropPktBufOverrun;                                                       
  LpCounterPtr->DropPktCrc        = LpCounter->DropPktCrc;
  LpCounterPtr->UndersizePkt      = LpCounter->UndersizePkt;
  LpCounterPtr->OversizePkt       = LpCounter->OversizePkt;
  LpCounterPtr->AlgnmtErr         = LpCounter->AlgnmtErr;
  LpCounterPtr->SqeTestErr        = LpCounter->SqeTestErr;
  LpCounterPtr->DiscInbdPkt       = LpCounter->DiscInbdPkt;
  LpCounterPtr->ErrInbdPkt        = LpCounter->ErrInbdPkt;
  LpCounterPtr->DiscOtbdPkt       = LpCounter->DiscOtbdPkt;
  LpCounterPtr->ErrOtbdPkt        = LpCounter->ErrOtbdPkt;
  LpCounterPtr->SnglCollPkt       = LpCounter->SnglCollPkt;
  LpCounterPtr->MultCollPkt       = LpCounter->MultCollPkt;
  LpCounterPtr->DfrdPkt           = LpCounter->DfrdPkt;
  LpCounterPtr->LatCollPkt        = LpCounter->LatCollPkt;
  LpCounterPtr->HwDepCtr0         = LpCounter->HwDepCtr0;
  LpCounterPtr->HwDepCtr1         = LpCounter->HwDepCtr1;
  LpCounterPtr->HwDepCtr2         = LpCounter->HwDepCtr2;
  LpCounterPtr->HwDepCtr3         = LpCounter->HwDepCtr3;

  /* Initialize Statistics */
  Eth_InitCounterValues(LulCtrlIdx);
}

/***********************************************************************************************************************
** Function Name         : Eth_InitCounterValues (RSW2)
**
** Service ID            : N/A
**
** Description           : Initialize information that drop frame counts for each error factor
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulCtrlIdx : Index of a controller
**
** InOut Parameters      : None
**
** Output Parameters     : None
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
** Reference ID          : ETH_DUD_ACT_505
** Reference ID          : ETH_DUD_ACT_505_GBL001, ETH_DUD_ACT_505_GBL002
** Reference ID          : ETH_DUD_ACT_505_GBL003
***********************************************************************************************************************/
STATIC FUNC(void, ETH_PRIVATE_CODE) Eth_InitCounterValues(
  CONST(uint32, AUTOMATIC) LulCtrlIdx)
{
  P2CONST(Eth_ETNEConfigType, AUTOMATIC, ETH_APPL_DATA) LpHwUnitConfig;
  CONSTP2VAR(Eth_CounterType, AUTOMATIC, ETH_APPL_DATA) LpCounter =                                                     /* PRQA S 3432 # JV-01 */
    (Eth_CounterType *)&Eth_GaaCtrlStat[LulCtrlIdx].stCounter;                                                          

  LpHwUnitConfig =
    (P2CONST(Eth_ETNEConfigType, AUTOMATIC, ETH_APPL_DATA))Eth_GpCtrlConfigPtr[LulCtrlIdx].pHwUnitConfig;               /* PRQA S 0316 # JV-01 */

  if (ETH_RSW2_PORT_TYPE_ETHA == Eth_GaaRsw2PortType[LpHwUnitConfig->ulEthPortId])                                      
  {
    LpCounter->DropPktBufOverrun = 0UL;                                                                                 
    LpCounter->DropPktCrc        = 0UL;
    LpCounter->UndersizePkt      = 0UL;
    LpCounter->OversizePkt       = 0UL;
    LpCounter->AlgnmtErr         = 0UL;
  }
  else
  {
    /* GWCA controller is not supported */
    LpCounter->DropPktBufOverrun = ETH_NOT_AVAILABLE;
    LpCounter->DropPktCrc        = ETH_NOT_AVAILABLE;
    LpCounter->UndersizePkt      = ETH_NOT_AVAILABLE;
    LpCounter->OversizePkt       = ETH_NOT_AVAILABLE;
    LpCounter->AlgnmtErr         = ETH_NOT_AVAILABLE;
  }

  /* not supported parameters */
  LpCounter->SqeTestErr          = ETH_NOT_AVAILABLE;
  LpCounter->DiscInbdPkt         = ETH_NOT_AVAILABLE;
  LpCounter->ErrInbdPkt          = ETH_NOT_AVAILABLE;
  LpCounter->DiscOtbdPkt         = ETH_NOT_AVAILABLE;
  LpCounter->ErrOtbdPkt          = ETH_NOT_AVAILABLE;
  LpCounter->SnglCollPkt         = ETH_NOT_AVAILABLE;
  LpCounter->MultCollPkt         = ETH_NOT_AVAILABLE;
  LpCounter->DfrdPkt             = ETH_NOT_AVAILABLE;
  LpCounter->LatCollPkt          = ETH_NOT_AVAILABLE;
  LpCounter->HwDepCtr0           = ETH_NOT_AVAILABLE;
  LpCounter->HwDepCtr1           = ETH_NOT_AVAILABLE;
  LpCounter->HwDepCtr2           = ETH_NOT_AVAILABLE;
  LpCounter->HwDepCtr3           = ETH_NOT_AVAILABLE;
}

/***********************************************************************************************************************
** Function Name         : Eth_HwRMAC_CountCounterValues (RSW2)
**
** Service ID            : N/A
**
** Description           : Add count information that drop frame counts for each error factor
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulCtrlIdx : Index of a controller
**                         LpStats    : Statistics counter register values
**
** InOut Parameters      : None
**
** Output Parameters     : None
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
** Reference ID          : ETH_DUD_ACT_506
** Reference ID          : ETH_DUD_ACT_506_GBL001, ETH_DUD_ACT_506_GBL002
** Reference ID          : ETH_DUD_ACT_506_GBL003, ETH_DUD_ACT_506_GBL004
** Reference ID          : ETH_DUD_ACT_506_GBL005, ETH_DUD_ACT_506_GBL006
** Reference ID          : ETH_DUD_ACT_506_GBL007, ETH_DUD_ACT_506_GBL008
***********************************************************************************************************************/
STATIC FUNC(void, ETH_PRIVATE_CODE) Eth_HwRMAC_CountCounterValues(
  CONST(uint32, AUTOMATIC) LulCtrlIdx,
  CONSTP2VAR(Eth_StatsRegValueType, AUTOMATIC, ETH_APPL_DATA) LpStats)                                                  /* PRQA S 3432, 3673 # JV-01, JV-01 */
{
  CONSTP2VAR(Eth_CounterType, AUTOMATIC, ETH_APPL_DATA) LpCounter =                                                     /* PRQA S 3432 # JV-01 */
    (Eth_CounterType *)&Eth_GaaCtrlStat[LulCtrlIdx].stCounter;                                                          

  /* DropPktBufOverrun: dropped packets due to buffer overrun */
  if ((ETH_UINT32_MAXVALUE - LpCounter->DropPktBufOverrun) >= LpStats->ulMROVFC)                                        
  {
    /* MROVFC : Receive overflow Counter */
    LpCounter->DropPktBufOverrun = ETH_STATISTICS_LIMIT(LpCounter->DropPktBufOverrun + LpStats->ulMROVFC);              /* PRQA S 3384, 3469 # JV-01, JV-01 */
  }
  else
  {
    LpCounter->DropPktBufOverrun = ETH_STATISTICS_MAXVALUE;
  }

  /* DropPktCrc: dropped packets due to CRC errors */
  if ((ETH_UINT32_MAXVALUE - LpCounter->DropPktCrc) >= LpStats->ulMRFMEFC)
  {
    /* MRFMEFC : RMAC Received FCS/mCRC error frame count */
    LpCounter->DropPktCrc = ETH_STATISTICS_LIMIT(LpCounter->DropPktCrc + LpStats->ulMRFMEFC);                           /* PRQA S 3384, 3469 # JV-01, JV-01 */
  }
  else
  {
    LpCounter->DropPktCrc = ETH_STATISTICS_MAXVALUE;
  }

  /* UndersizePkt: number of undersize packets which were less than 64 octets long      */
  /* (excluding framing bits, but including FCS octets) and were otherwise well formed. */
  if ((ETH_UINT32_MAXVALUE - LpCounter->UndersizePkt) >= LpStats->ulMRGUEFC)
  {
    /* MRGUEFC : RMAC Received good undersize error frame count */
    LpCounter->UndersizePkt = ETH_STATISTICS_LIMIT(LpCounter->UndersizePkt + LpStats->ulMRGUEFC);                       /* PRQA S 3384, 3469 # JV-01, JV-01 */
  }
  else
  {
    LpCounter->UndersizePkt = ETH_STATISTICS_MAXVALUE;
  }

  if ((ETH_UINT32_MAXVALUE - LpCounter->UndersizePkt) >= LpStats->ulMRBUEFC)
  {
    /* MRBUEFC : RMAC Received bad undersize error frame count */
    LpCounter->UndersizePkt = ETH_STATISTICS_LIMIT(LpCounter->UndersizePkt + LpStats->ulMRBUEFC);                       /* PRQA S 3384, 3469 # JV-01, JV-01 */
  }
  else
  {
    LpCounter->UndersizePkt = ETH_STATISTICS_MAXVALUE;
  }

  /* OversizePkt: number of oversize packets which are longer than 1518 octets          */
  /* (excluding framing bits, but including FCS octets) and were otherwise well formed. */
  if ((ETH_UINT32_MAXVALUE - LpCounter->OversizePkt) >= LpStats->ulMRGOEFC)
  {
    /* MRGOEFC : RMAC Received good oversize error frame count */
    LpCounter->OversizePkt = ETH_STATISTICS_LIMIT(LpCounter->OversizePkt + LpStats->ulMRGOEFC);                         /* PRQA S 3384, 3469 # JV-01, JV-01 */
  }
  else
  {
    LpCounter->OversizePkt = ETH_STATISTICS_MAXVALUE;
  }

  if ((ETH_UINT32_MAXVALUE - LpCounter->OversizePkt) >= LpStats->ulMRBOEFC)
  {
    /* MRBOEFC : RMAC Received bad oversize error frame count */
    LpCounter->OversizePkt = ETH_STATISTICS_LIMIT(LpCounter->OversizePkt + LpStats->ulMRBOEFC);                         /* PRQA S 3384, 3469 # JV-01, JV-01 */
  }
  else
  {
    LpCounter->OversizePkt = ETH_STATISTICS_MAXVALUE;
  }

  /* AlgnmtErr: number of alignment errors, i.e. packets which are received and */
  /* are not an integral number of octets in length and do not pass the CRC.    */
  if ((ETH_UINT32_MAXVALUE - LpCounter->AlgnmtErr) >= LpStats->ulMRNEFC)
  {
    /* MRNEFC : RMAC Received nibble error frame count */
    LpCounter->AlgnmtErr = ETH_STATISTICS_LIMIT(LpCounter->AlgnmtErr + LpStats->ulMRNEFC);                              /* PRQA S 3384, 3469 # JV-01, JV-01 */
  }
  else
  {
    LpCounter->AlgnmtErr = ETH_STATISTICS_MAXVALUE;
  }
}
#endif /* (ETH_GET_COUNTER_VALUES_API == STD_ON) */

#if (ETH_GET_RX_STATS_API == STD_ON)
/***********************************************************************************************************************
** Function Name         : Eth_ETNE_HwGetRxStats (RSW2)
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
** Global Variable(s)    : Eth_GaaCtrlStat
**
** Function(s) invoked   : Eth_InitRxStats
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_317
** Reference ID          : ETH_DUD_ACT_317_GBL001
***********************************************************************************************************************/
FUNC(void, ETH_PRIVATE_CODE) Eth_ETNE_HwGetRxStats(                                                                     
  CONST(uint32, AUTOMATIC) LulCtrlIdx, 
  CONSTP2VAR(Eth_RxStatsType, AUTOMATIC, ETH_APPL_DATA) LpRxStats)                                                      /* PRQA S 3432 # JV-01 */
{
  CONSTP2VAR(Eth_RxStatsType, AUTOMATIC, ETH_APPL_DATA) LpCounter =                                                     /* PRQA S 3432, 3678 # JV-01, JV-01 */

    (Eth_RxStatsType *)&Eth_GaaCtrlStat[LulCtrlIdx].stRxStat;                                                           

  LpRxStats->RxStatsDropEvents           = LpCounter->RxStatsDropEvents;                                                
  LpRxStats->RxStatsOctets               = LpCounter->RxStatsOctets;
  LpRxStats->RxStatsPkts                 = LpCounter->RxStatsPkts;
  LpRxStats->RxStatsBroadcastPkts        = LpCounter->RxStatsBroadcastPkts;
  LpRxStats->RxStatsMulticastPkts        = LpCounter->RxStatsMulticastPkts;
  LpRxStats->RxStatsCrcAlignErrors       = LpCounter->RxStatsCrcAlignErrors;
  LpRxStats->RxStatsUndersizePkts        = LpCounter->RxStatsUndersizePkts;
  LpRxStats->RxStatsOversizePkts         = LpCounter->RxStatsOversizePkts;
  LpRxStats->RxStatsFragments            = LpCounter->RxStatsFragments;
  LpRxStats->RxStatsJabbers              = LpCounter->RxStatsJabbers;
  LpRxStats->RxStatsCollisions           = LpCounter->RxStatsCollisions;
  LpRxStats->RxStatsPkts64Octets         = LpCounter->RxStatsPkts64Octets;
  LpRxStats->RxStatsPkts65to127Octets    = LpCounter->RxStatsPkts65to127Octets;
  LpRxStats->RxStatsPkts128to255Octets   = LpCounter->RxStatsPkts128to255Octets;
  LpRxStats->RxStatsPkts256to511Octets   = LpCounter->RxStatsPkts256to511Octets;
  LpRxStats->RxStatsPkts512to1023Octets  = LpCounter->RxStatsPkts512to1023Octets;
  LpRxStats->RxStatsPkts1024to1518Octets = LpCounter->RxStatsPkts1024to1518Octets;
  LpRxStats->RxUnicastFrames             = LpCounter->RxUnicastFrames;

  /* Initialize Statistics */
  Eth_InitRxStats(LulCtrlIdx);
}

/***********************************************************************************************************************
** Function Name         : Eth_InitRxStats (RSW2)
**
** Service ID            : N/A
**
** Description           : Initialize Rx statistics information
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulCtrlIdx : Index of a controller
**
** InOut Parameters      : None
**
** Output Parameters     : None
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
** Reference ID          : ETH_DUD_ACT_507
** Reference ID          : ETH_DUD_ACT_507_GBL001, ETH_DUD_ACT_507_GBL002
** Reference ID          : ETH_DUD_ACT_507_GBL003
***********************************************************************************************************************/
STATIC FUNC(void, ETH_PRIVATE_CODE) Eth_InitRxStats(
  CONST(uint32, AUTOMATIC) LulCtrlIdx)
{
  P2CONST(Eth_ETNEConfigType, AUTOMATIC, ETH_APPL_DATA) LpHwUnitConfig;
  CONSTP2VAR(Eth_RxStatsType, AUTOMATIC, ETH_APPL_DATA) LpCounter =                                                     /* PRQA S 3432 # JV-01 */
    (Eth_RxStatsType *)&Eth_GaaCtrlStat[LulCtrlIdx].stRxStat;                                                           

  LpHwUnitConfig =
    (P2CONST(Eth_ETNEConfigType, AUTOMATIC, ETH_APPL_DATA))Eth_GpCtrlConfigPtr[LulCtrlIdx].pHwUnitConfig;               /* PRQA S 0316 # JV-01 */

  if (ETH_RSW2_PORT_TYPE_ETHA == Eth_GaaRsw2PortType[LpHwUnitConfig->ulEthPortId])                                      
  {
    LpCounter->RxStatsOctets             = 0UL;                                                                         
    LpCounter->RxStatsPkts               = 0UL;
    LpCounter->RxStatsBroadcastPkts      = 0UL;
    LpCounter->RxStatsMulticastPkts      = 0UL;
    LpCounter->RxStatsCrcAlignErrors     = 0UL;
    LpCounter->RxStatsUndersizePkts      = 0UL;
    LpCounter->RxStatsOversizePkts       = 0UL;
    LpCounter->RxStatsFragments          = 0UL;
    LpCounter->RxUnicastFrames           = 0UL;
  }
  else
  {
    /* GWCA controller is not supported */
    LpCounter->RxStatsOctets             = ETH_NOT_AVAILABLE;
    LpCounter->RxStatsPkts               = ETH_NOT_AVAILABLE;
    LpCounter->RxStatsBroadcastPkts      = ETH_NOT_AVAILABLE;
    LpCounter->RxStatsMulticastPkts      = ETH_NOT_AVAILABLE;
    LpCounter->RxStatsCrcAlignErrors     = ETH_NOT_AVAILABLE;
    LpCounter->RxStatsUndersizePkts      = ETH_NOT_AVAILABLE;
    LpCounter->RxStatsOversizePkts       = ETH_NOT_AVAILABLE;
    LpCounter->RxStatsFragments          = ETH_NOT_AVAILABLE;
    LpCounter->RxUnicastFrames           = ETH_NOT_AVAILABLE;
  }

  /* not supported parameters */
  LpCounter->RxStatsDropEvents           = ETH_NOT_AVAILABLE;
  LpCounter->RxStatsJabbers              = ETH_NOT_AVAILABLE;
  LpCounter->RxStatsCollisions           = ETH_NOT_AVAILABLE;
  LpCounter->RxStatsPkts64Octets         = ETH_NOT_AVAILABLE;
  LpCounter->RxStatsPkts65to127Octets    = ETH_NOT_AVAILABLE;
  LpCounter->RxStatsPkts128to255Octets   = ETH_NOT_AVAILABLE;
  LpCounter->RxStatsPkts256to511Octets   = ETH_NOT_AVAILABLE;
  LpCounter->RxStatsPkts512to1023Octets  = ETH_NOT_AVAILABLE;
  LpCounter->RxStatsPkts1024to1518Octets = ETH_NOT_AVAILABLE;
}

/***********************************************************************************************************************
** Function Name         : Eth_HwRMAC_CountRxStats (RSW2)
**
** Service ID            : N/A
**
** Description           : Add count Rx statistics information
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulCtrlIdx : Index of a controller
**                         LpStats    : Statistics counter register values
**
** InOut Parameters      : None
**
** Output Parameters     : None
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
** Reference ID          : ETH_DUD_ACT_508
** Reference ID          : ETH_DUD_ACT_508_GBL001, ETH_DUD_ACT_508_GBL002
** Reference ID          : ETH_DUD_ACT_508_GBL003, ETH_DUD_ACT_508_GBL004
** Reference ID          : ETH_DUD_ACT_508_GBL005, ETH_DUD_ACT_508_GBL006
** Reference ID          : ETH_DUD_ACT_508_GBL007, ETH_DUD_ACT_508_GBL008
** Reference ID          : ETH_DUD_ACT_508_GBL009, ETH_DUD_ACT_508_GBL010
** Reference ID          : ETH_DUD_ACT_508_GBL011, ETH_DUD_ACT_508_GBL012
** Reference ID          : ETH_DUD_ACT_508_GBL013, ETH_DUD_ACT_508_GBL014
** Reference ID          : ETH_DUD_ACT_508_GBL015
***********************************************************************************************************************/
STATIC FUNC(void, ETH_PRIVATE_CODE) Eth_HwRMAC_CountRxStats(
  CONST(uint32, AUTOMATIC) LulCtrlIdx,
  CONSTP2VAR(Eth_StatsRegValueType, AUTOMATIC, ETH_APPL_DATA) LpStats)                                                  /* PRQA S 3432, 3673 # JV-01, JV-01 */
{
  CONSTP2VAR(Eth_RxStatsType, AUTOMATIC, ETH_APPL_DATA) LpCounter =                                                     /* PRQA S 3432 # JV-01 */
    (Eth_RxStatsType *)&Eth_GaaCtrlStat[LulCtrlIdx].stRxStat;                                                           

  /* RxStatsOctets: The total number of octets of data (including those in bad packets) received on the network */
  /* (excluding framing bits but including FCS octets).                                                         */
  if ((0UL < LpStats->ulMRXBCEU) || (0UL < LpStats->ulMRXBCPU))                                                         
  {
    /* MRXBCEU : RMAC Received byte counter E-frames upper side */
    /* MRXBCPU : RMAC Received byte counter E-frames lower side */
    LpCounter->RxStatsOctets = ETH_STATISTICS_MAXVALUE;                                                                 
  }
  else
  {
    if ((ETH_UINT32_MAXVALUE - LpCounter->RxStatsOctets) >= LpStats->ulMRXBCEL)
    {
      /* MRXBCEL : RMAC Received byte counter P-frames upper side */
      LpCounter->RxStatsOctets = ETH_STATISTICS_LIMIT(LpCounter->RxStatsOctets + LpStats->ulMRXBCEL);                   /* PRQA S 3384, 3469 # JV-01, JV-01 */
    }
    else
    {
      LpCounter->RxStatsOctets = ETH_STATISTICS_MAXVALUE;
    }
    if ((ETH_UINT32_MAXVALUE - LpCounter->RxStatsOctets) >= LpStats->ulMRXBCPL)
    {
      /* MRXBCPL : RMAC Received byte counter P-frames lower side */
      LpCounter->RxStatsOctets = ETH_STATISTICS_LIMIT(LpCounter->RxStatsOctets + LpStats->ulMRXBCPL);                   /* PRQA S 3384, 3469 # JV-01, JV-01 */
    }
    else
    {
      LpCounter->RxStatsOctets = ETH_STATISTICS_MAXVALUE;
    }
  }

  /* RxStatsPkts: The total number of packets (including bad packets, broadcast packets, 
  and multicast packets) received. */
  if ((ETH_UINT32_MAXVALUE - LpCounter->RxStatsPkts) >= LpStats->ulMRFC)
  {
    /* MRFC : RMAC Received fragment count error frame count */
    LpCounter->RxStatsPkts = ETH_STATISTICS_LIMIT(LpCounter->RxStatsPkts + LpStats->ulMRFC);                            /* PRQA S 3384, 3469 # JV-01, JV-01 */
  }
  else
  {
    LpCounter->RxStatsPkts = ETH_STATISTICS_MAXVALUE;
  }

  /* RxStatsBroadcastPkts: The total number of good packets received that were directed to the broadcast address. */
  if ((ETH_UINT32_MAXVALUE - LpCounter->RxStatsBroadcastPkts) >= LpStats->ulMRBFC)
  {
    /* MRBFC : RMAC Received good broadcast frame counter */
    LpCounter->RxStatsBroadcastPkts = ETH_STATISTICS_LIMIT(LpCounter->RxStatsBroadcastPkts + LpStats->ulMRBFC);         /* PRQA S 3384, 3469 # JV-01, JV-01 */
  }
  else
  {
    LpCounter->RxStatsBroadcastPkts = ETH_STATISTICS_MAXVALUE;
  }

  /* RxStatsMulticastPkts: The total number of good packets received that were directed to a multicast address. */
  if ((ETH_UINT32_MAXVALUE - LpCounter->RxStatsMulticastPkts) >= LpStats->ulMRMFC)
  {
    /* MRMFC : RMAC Received good multicast frame counter */
    LpCounter->RxStatsMulticastPkts = ETH_STATISTICS_LIMIT(LpCounter->RxStatsMulticastPkts + LpStats->ulMRMFC);         /* PRQA S 3384, 3469 # JV-01, JV-01 */
  }
  else
  {
    LpCounter->RxStatsMulticastPkts = ETH_STATISTICS_MAXVALUE;
  }

  /* RxStatsCrcAlignErrors: The total number of packets received that had a length of bertween 64 and 1518 octets */
  /* that had either a bad Frame Check Sequence (FCS) with an integral number of octets (FCS Error) or            */
  /* a bad FCS with a non-integral number of octets (Alignment Error).                                            */
  if ((ETH_UINT32_MAXVALUE - LpCounter->RxStatsCrcAlignErrors) >= LpStats->ulMRFMEFC)
  {
    /* MRFMEFC : RMAC Received FCS/mCRC error frame count */
    LpCounter->RxStatsCrcAlignErrors = ETH_STATISTICS_LIMIT(LpCounter->RxStatsCrcAlignErrors + LpStats->ulMRFMEFC);     /* PRQA S 3384, 3469 # JV-01, JV-01 */
  }
  else
  {
    LpCounter->RxStatsCrcAlignErrors = ETH_STATISTICS_MAXVALUE;
  }
  if ((ETH_UINT32_MAXVALUE - LpCounter->RxStatsCrcAlignErrors) >= LpStats->ulMRNEFC)
  {
    /* MRNEFC : RMAC Received nibble error frame count */
    LpCounter->RxStatsCrcAlignErrors = ETH_STATISTICS_LIMIT(LpCounter->RxStatsCrcAlignErrors + LpStats->ulMRNEFC);      /* PRQA S 3384, 3469 # JV-01, JV-01 */
  }
  else
  {
    LpCounter->RxStatsCrcAlignErrors = ETH_STATISTICS_MAXVALUE;
  }

  /* RxStatsUndersizePkts: The total number of packets received that were less than 64 octets long */
  /* (excluding framing bits, but including FCS octets) and were otherwise well formed.            */
  if ((ETH_UINT32_MAXVALUE - LpCounter->RxStatsUndersizePkts) >= LpStats->ulMRGUEFC)
  {
    /* MRGUEFC : RMAC Received good undersize error frame count */
    LpCounter->RxStatsUndersizePkts = ETH_STATISTICS_LIMIT(LpCounter->RxStatsUndersizePkts + LpStats->ulMRGUEFC);       /* PRQA S 3384, 3469 # JV-01, JV-01 */
  }
  else
  {
    LpCounter->RxStatsUndersizePkts = ETH_STATISTICS_MAXVALUE;
  }
  if ((ETH_UINT32_MAXVALUE - LpCounter->RxStatsUndersizePkts) >= LpStats->ulMRBUEFC)
  {
    /* MRBUEFC : RMAC Received bad undersize error frame count */
    LpCounter->RxStatsUndersizePkts = ETH_STATISTICS_LIMIT(LpCounter->RxStatsUndersizePkts + LpStats->ulMRBUEFC);       /* PRQA S 3384, 3469 # JV-01, JV-01 */
  }
  else
  {
    LpCounter->RxStatsUndersizePkts = ETH_STATISTICS_MAXVALUE;
  }

  /* RxStatsOversizePkts: The total number of packets received that were longer than 1518 octets */
  /* (excluding framing bits, but including FCS octets) and were otherwise well formed.          */
  if ((ETH_UINT32_MAXVALUE - LpCounter->RxStatsOversizePkts) >= LpStats->ulMRGOEFC)
  {
    /* MRGOEFC : RMAC Received good oversize error frame count */
    LpCounter->RxStatsOversizePkts = ETH_STATISTICS_LIMIT(LpCounter->RxStatsOversizePkts + LpStats->ulMRGOEFC);         /* PRQA S 3384, 3469 # JV-01, JV-01 */
  }
  else
  {
    LpCounter->RxStatsOversizePkts = ETH_STATISTICS_MAXVALUE;
  }

  if ((ETH_UINT32_MAXVALUE - LpCounter->RxStatsOversizePkts) >= LpStats->ulMRBOEFC)
  {
    /* MRBOEFC : RMAC Received bad oversize error frame count */
    LpCounter->RxStatsOversizePkts = ETH_STATISTICS_LIMIT(LpCounter->RxStatsOversizePkts + LpStats->ulMRBOEFC);         /* PRQA S 3384, 3469 # JV-01, JV-01 */
  }
  else
  {
    LpCounter->RxStatsOversizePkts = ETH_STATISTICS_MAXVALUE;
  }

  /* RxStatsFragments: The total number of packets received that were less than 64 octets in length                   */
  /* (excluding framing bits but including FCS octets) and had either a bad Frame Check Sequence (FCS)                */
  /* with an integral number of octets (FCS Error) or a bad FCS with a non-integral number of octets(Alignment Error) */
  if ((ETH_UINT32_MAXVALUE - LpCounter->RxStatsFragments) >= LpStats->ulMRFCEFC)
  {
    /* MRFCEFC : RMAC Received fragment count error frame count */
    LpCounter->RxStatsFragments = ETH_STATISTICS_LIMIT(LpCounter->RxStatsFragments + LpStats->ulMRFCEFC);               /* PRQA S 3384, 3469 # JV-01, JV-01 */
  }
  else
  {
    LpCounter->RxStatsFragments = ETH_STATISTICS_MAXVALUE;
  }

  /* RxUnicastFrames: The number of subnetwork-unicast packets delivered to a higher-layer protocol. */
  if ((ETH_UINT32_MAXVALUE - LpCounter->RxUnicastFrames) >= LpStats->ulMRUFC)
  {
    /* MRUFC : RMAC Received good unicast frame counter */
    LpCounter->RxUnicastFrames = ETH_STATISTICS_LIMIT(LpCounter->RxUnicastFrames + LpStats->ulMRUFC);                   /* PRQA S 3384, 3469 # JV-01, JV-01 */
  }
  else
  {
    LpCounter->RxUnicastFrames = ETH_STATISTICS_MAXVALUE;
  }
}
#endif /* (ETH_GET_RX_STATS_API == STD_ON) */

#if (ETH_GET_TX_STATS_API == STD_ON)
/***********************************************************************************************************************
** Function Name         : Eth_ETNE_HwGetTxStats (RSW2)
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
** Function(s) invoked   : Eth_InitTxStats
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_318
** Reference ID          : ETH_DUD_ACT_318_GBL001
***********************************************************************************************************************/
FUNC(void, ETH_PRIVATE_CODE) Eth_ETNE_HwGetTxStats(                                                                     
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONSTP2VAR(Eth_TxStatsType, AUTOMATIC, ETH_APPL_DATA) LpTxStats)                 /* PRQA S 3432 # JV-01 */
{
  CONSTP2VAR(Eth_TxStatsType, AUTOMATIC, ETH_APPL_DATA) LpCounter =                                                     /* PRQA S 3432, 3678 # JV-01, JV-01 */
    (Eth_TxStatsType *)&Eth_GaaCtrlStat[LulCtrlIdx].stTxStat;                                                           

  LpTxStats->TxNumberOfOctets = LpCounter->TxNumberOfOctets;                                                            
  LpTxStats->TxNUcastPkts     = LpCounter->TxNUcastPkts;
  LpTxStats->TxUniCastPkts    = LpCounter->TxUniCastPkts;

  /* Initialize Statistics */
  Eth_InitTxStats(LulCtrlIdx);
}

/***********************************************************************************************************************
** Function Name         : Eth_InitTxStats (RSW2)
**
** Service ID            : N/A
**
** Description           : Initialize Tx statistics information
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulCtrlIdx : Index of a controller
**
** InOut Parameters      : None
**
** Output Parameters     : None
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
** Reference ID          : ETH_DUD_ACT_509
** Reference ID          : ETH_DUD_ACT_509_GBL001, ETH_DUD_ACT_509_GBL002
** Reference ID          : ETH_DUD_ACT_509_GBL003
***********************************************************************************************************************/
STATIC FUNC(void, ETH_PRIVATE_CODE) Eth_InitTxStats(
  CONST(uint32, AUTOMATIC) LulCtrlIdx)
{
  P2CONST(Eth_ETNEConfigType, AUTOMATIC, ETH_APPL_DATA) LpHwUnitConfig;
  CONSTP2VAR(Eth_TxStatsType, AUTOMATIC, ETH_APPL_DATA) LpCounter =                                                     /* PRQA S 3432 # JV-01 */
    (Eth_TxStatsType *)&Eth_GaaCtrlStat[LulCtrlIdx].stTxStat;                                                           

  LpHwUnitConfig =
    (P2CONST(Eth_ETNEConfigType, AUTOMATIC, ETH_APPL_DATA))Eth_GpCtrlConfigPtr[LulCtrlIdx].pHwUnitConfig;               /* PRQA S 0316 # JV-01 */

  if (ETH_RSW2_PORT_TYPE_ETHA == Eth_GaaRsw2PortType[LpHwUnitConfig->ulEthPortId])                                      
  {
    LpCounter->TxNumberOfOctets = 0UL;                                                                                  
    LpCounter->TxNUcastPkts     = 0UL;
    LpCounter->TxUniCastPkts    = 0UL;
  }
  else
  {
    /* GWCA controller is not supported */
    LpCounter->TxNumberOfOctets = ETH_NOT_AVAILABLE;
    LpCounter->TxNUcastPkts     = ETH_NOT_AVAILABLE;
    LpCounter->TxUniCastPkts    = ETH_NOT_AVAILABLE;
  }
}

/***********************************************************************************************************************
** Function Name         : Eth_HwRMAC_CountTxStats (RSW2)
**
** Service ID            : N/A
**
** Description           : Add count Tx statistics information
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulCtrlIdx : Index of a controller
**                         LpStats    : Statistics counter register values
**
** InOut Parameters      : None
**
** Output Parameters     : None
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
** Reference ID          : ETH_DUD_ACT_510
** Reference ID          : ETH_DUD_ACT_510_GBL001, ETH_DUD_ACT_510_GBL002
** Reference ID          : ETH_DUD_ACT_510_GBL003, ETH_DUD_ACT_510_GBL004
** Reference ID          : ETH_DUD_ACT_510_GBL005, ETH_DUD_ACT_510_GBL006
** Reference ID          : ETH_DUD_ACT_510_GBL007
***********************************************************************************************************************/
STATIC FUNC(void, ETH_PRIVATE_CODE) Eth_HwRMAC_CountTxStats(
  CONST(uint32, AUTOMATIC) LulCtrlIdx,
  CONSTP2VAR(Eth_StatsRegValueType, AUTOMATIC, ETH_APPL_DATA) LpStats)                                                  /* PRQA S 3432, 3673 # JV-01, JV-01 */
{
  CONSTP2VAR(Eth_TxStatsType, AUTOMATIC, ETH_APPL_DATA) LpCounter =                                                     /* PRQA S 3432 # JV-01 */
    (Eth_TxStatsType *)&Eth_GaaCtrlStat[LulCtrlIdx].stTxStat;                                                           

  /* TxNumberOfOctets: The total number of octets transmitted out of the interface, including framing characters. */
  if ((0UL < LpStats->ulMTXBCEU) || (0UL < LpStats->ulMTXBCPU))                                                         
  {
    /* MTXBCEU : RMAC Transmitted byte counter E-frames upper side */
    /* MTXBCPU : RMAC Transmitted byte counter E-frames lower side */
    LpCounter->TxNumberOfOctets = ETH_STATISTICS_MAXVALUE;                                                              
  }
  else
  {
    if ((ETH_UINT32_MAXVALUE - LpCounter->TxNumberOfOctets) >= LpStats->ulMTXBCEL)
    {
      /* MTXBCEL : RMAC Transmitted byte counter P-frames upper side */
      LpCounter->TxNumberOfOctets = ETH_STATISTICS_LIMIT(LpCounter->TxNumberOfOctets + LpStats->ulMTXBCEL);             /* PRQA S 3384, 3469 # JV-01, JV-01 */
    }
    else
    {
      LpCounter->TxNumberOfOctets = ETH_STATISTICS_MAXVALUE;
    }
    if ((ETH_UINT32_MAXVALUE - LpCounter->TxNumberOfOctets) >= LpStats->ulMTXBCPL)
    {
      /* MTXBCPL : RMAC Transmitted byte counter P-frames lower side */
      LpCounter->TxNumberOfOctets = ETH_STATISTICS_LIMIT(LpCounter->TxNumberOfOctets + LpStats->ulMTXBCPL);             /* PRQA S 3384, 3469 # JV-01, JV-01 */
    }
    else
    {
      LpCounter->TxNumberOfOctets = ETH_STATISTICS_MAXVALUE;
    }
  }

  /* TxNUcastPkts: The total number of packets that higher-level protocols requested be transmitted to a non-unicast  */
  /* (i.e., a subnetwork-broadcast or subnetwork-multicast) address, including those that were discarded or not sent. */
  if ((ETH_UINT32_MAXVALUE - LpCounter->TxNUcastPkts) >= LpStats->ulMTBFC)
  {
    /* MTBFC : RMAC Transmitted broadcast frame counter */
    LpCounter->TxNUcastPkts = ETH_STATISTICS_LIMIT(LpCounter->TxNUcastPkts + LpStats->ulMTBFC);                         /* PRQA S 3384, 3469 # JV-01, JV-01 */
  }
  else
  {
    LpCounter->TxNUcastPkts = ETH_STATISTICS_MAXVALUE;
  }

  if ((ETH_UINT32_MAXVALUE - LpCounter->TxNUcastPkts) >= LpStats->ulMTMFC)
  {
    /* MTMFC : RMAC Transmitted multicast frame counter */
    LpCounter->TxNUcastPkts = ETH_STATISTICS_LIMIT(LpCounter->TxNUcastPkts + LpStats->ulMTMFC);                         /* PRQA S 3384, 3469 # JV-01, JV-01 */
  }
  else
  {
    LpCounter->TxNUcastPkts = ETH_STATISTICS_MAXVALUE;
  }

  /* TxUniCastPkts: The total number of packets that higher-level protocols requested be transmitted */
  /* to a subnetwork-unicast address, including those that were discarded or not sent.               */
  if ((ETH_UINT32_MAXVALUE - LpCounter->TxUniCastPkts) >= LpStats->ulMTUFC)
  {
    /* MTUFC : RMAC Transmitted unicast frame counter */
    LpCounter->TxUniCastPkts = ETH_STATISTICS_LIMIT(LpCounter->TxUniCastPkts + LpStats->ulMTUFC);                       /* PRQA S 3384, 3469 # JV-01, JV-01 */
  }
  else
  {
    LpCounter->TxUniCastPkts = ETH_STATISTICS_MAXVALUE;
  }
}
#endif /* (ETH_GET_TX_STATS_API == STD_ON) */

#if (ETH_GET_TX_ERROR_COUNTER_VALUES_API == STD_ON)
/***********************************************************************************************************************
** Function Name         : Eth_ETNE_HwGetTxErrorCounterValues (RSW2)
**
** Service ID            : N/A
**
** Description           : Get error statuses
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : LulCtrlIdx: Index of a controller
**
** InOut Parameters      : None
**
** Output Parameters     : LpTxErrorCounterValues: Tx error counter information
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variable(s)    : Eth_GaaCtrlStat
**
** Function(s) invoked   : Eth_InitTxErrorCounterValues
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_319
** Reference ID          : ETH_DUD_ACT_319_GBL001
***********************************************************************************************************************/
FUNC(void, ETH_PRIVATE_CODE) Eth_ETNE_HwGetTxErrorCounterValues(                                                        
  CONST(uint32, AUTOMATIC) LulCtrlIdx,
  CONSTP2VAR(Eth_TxErrorCounterValuesType, AUTOMATIC, ETH_APPL_DATA) LpTxErrorCounterValues)                            /* PRQA S 3432 # JV-01 */
{
  CONSTP2VAR(Eth_TxErrorCounterValuesType, AUTOMATIC, ETH_APPL_DATA) LpCounter =                                        /* PRQA S 3432, 3678 # JV-01, JV-01 */
    (Eth_TxErrorCounterValuesType *)&Eth_GaaCtrlStat[LulCtrlIdx].stTxError;                                             

  LpTxErrorCounterValues->TxDroppedNoErrorPkts = LpCounter->TxDroppedNoErrorPkts;                                       
  LpTxErrorCounterValues->TxDroppedErrorPkts   = LpCounter->TxDroppedErrorPkts;
  LpTxErrorCounterValues->TxDeferredTrans      = LpCounter->TxDeferredTrans;
  LpTxErrorCounterValues->TxSingleCollision    = LpCounter->TxSingleCollision;
  LpTxErrorCounterValues->TxMultipleCollision  = LpCounter->TxMultipleCollision;
  LpTxErrorCounterValues->TxLateCollision      = LpCounter->TxLateCollision;
  LpTxErrorCounterValues->TxExcessiveCollison  = LpCounter->TxExcessiveCollison;

  /* Initialize Statistics */
  Eth_InitTxErrorCounterValues(LulCtrlIdx);
}

/***********************************************************************************************************************
** Function Name         : Eth_InitTxErrorCounterValues (RSW2)
**
** Service ID            : N/A
**
** Description           : Initialize error statistics information
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulCtrlIdx : Index of a controller
**
** InOut Parameters      : None
**
** Output Parameters     : None
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
** Reference ID          : ETH_DUD_ACT_511
** Reference ID          : ETH_DUD_ACT_511_GBL001, ETH_DUD_ACT_511_GBL002
** Reference ID          : ETH_DUD_ACT_511_GBL003
***********************************************************************************************************************/
STATIC FUNC(void, ETH_PRIVATE_CODE) Eth_InitTxErrorCounterValues(
  CONST(uint32, AUTOMATIC) LulCtrlIdx)
{
  P2CONST(Eth_ETNEConfigType, AUTOMATIC, ETH_APPL_DATA) LpHwUnitConfig;
  CONSTP2VAR(Eth_TxErrorCounterValuesType, AUTOMATIC, ETH_APPL_DATA) LpCounter =                                        /* PRQA S 3432 # JV-01 */
    (Eth_TxErrorCounterValuesType *)&Eth_GaaCtrlStat[LulCtrlIdx].stTxError;                                             

  LpHwUnitConfig =
    (P2CONST(Eth_ETNEConfigType, AUTOMATIC, ETH_APPL_DATA))Eth_GpCtrlConfigPtr[LulCtrlIdx].pHwUnitConfig;               /* PRQA S 0316 # JV-01 */

  if (ETH_RSW2_PORT_TYPE_ETHA == Eth_GaaRsw2PortType[LpHwUnitConfig->ulEthPortId])                                      
  {
    LpCounter->TxDroppedErrorPkts = 0UL;                                                                                
  }
  else
  {
    /* GWCA controller is not supported */
    LpCounter->TxDroppedErrorPkts = ETH_NOT_AVAILABLE;
  }

  /* not supported parameters */
  LpCounter->TxDroppedNoErrorPkts = ETH_NOT_AVAILABLE;
  LpCounter->TxDeferredTrans      = ETH_NOT_AVAILABLE;
  LpCounter->TxSingleCollision    = ETH_NOT_AVAILABLE;
  LpCounter->TxMultipleCollision  = ETH_NOT_AVAILABLE;
  LpCounter->TxLateCollision      = ETH_NOT_AVAILABLE;
  LpCounter->TxExcessiveCollison  = ETH_NOT_AVAILABLE;
}

/***********************************************************************************************************************
** Function Name         : Eth_HwRMAC_CountTxErrorCounterValues (RSW2)
**
** Service ID            : N/A
**
** Description           : Add count error statistics information
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulCtrlIdx : Index of a controller
**                         LpStats    : Statistics counter register values
**
** InOut Parameters      : None
**
** Output Parameters     : None
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
** Reference ID          : ETH_DUD_ACT_512
** Reference ID          : ETH_DUD_ACT_512_GBL001, ETH_DUD_ACT_512_GBL002
***********************************************************************************************************************/
STATIC FUNC(void, ETH_PRIVATE_CODE) Eth_HwRMAC_CountTxErrorCounterValues(
  CONST(uint32, AUTOMATIC) LulCtrlIdx,
  CONSTP2VAR(Eth_StatsRegValueType, AUTOMATIC, ETH_APPL_DATA) LpStats)                                                  /* PRQA S 3432, 3673 # JV-01, JV-01 */
{
  CONSTP2VAR(Eth_TxErrorCounterValuesType, AUTOMATIC, ETH_APPL_DATA) LpCounter =                                        /* PRQA S 3432 # JV-01 */
    (Eth_TxErrorCounterValuesType *)&Eth_GaaCtrlStat[LulCtrlIdx].stTxError;                                             

  /* TxDroppedErrorPkts: transmitted because of errors. */
  if ((ETH_UINT32_MAXVALUE - LpCounter->TxDroppedErrorPkts) >= LpStats->ulMTEFC)                                        
  {
    /* MTEFC : RMAC Transmitted error frame counter */
    LpCounter->TxDroppedErrorPkts = ETH_STATISTICS_LIMIT(LpCounter->TxDroppedErrorPkts + LpStats->ulMTEFC);             /* PRQA S 3384, 3469 # JV-01, JV-01 */
  }
  else
  {
    LpCounter->TxDroppedErrorPkts = ETH_STATISTICS_MAXVALUE;
  }
}
#endif /* (ETH_GET_TX_ERROR_COUNTER_VALUES_API == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Eth_ETNE_HwMainFunction (RSW2)
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
** Global Variable(s)    : Eth_GaaCtrl_RMACRegs, Eth_GpCtrlConfigPtr
**                         Eth_GpDemEventRxFramesLost, Eth_GpDemEventCRC,
**                         Eth_GpDemEventUnderSizeFrame, Eth_GpDemEventOverSizeFrame,
**                         Eth_GpDemEventAlignment, Eth_GaaRsw2PortType
**
** Function(s) invoked   : Eth_HwRMAC_CountCounterValues,Eth_HwRMAC_CountRxStats,
**                         Eth_HwRMAC_CountTxStats,Eth_HwRMAC_CountTxErrorCounterValues,
**                         Eth_DemConfigCheck
**
** Registers Used        : MROVFC, MRFMEFC, MRGUEFC, MRBUEFC, MRGOEFC, MRBOEFC,
**                         MRNEFC, MRFCEFC, MRXBCEU, MRXBCEL, MRXBCPU, MRXBCPL,
**                         MRFC, MRBFC, MRUFC, MRMFC, MTXBCEU, MTXBCEL, MTXBCPU,
**                         MTXBCPL, MTBFC, MTMFC, MTUFC, MTEFC, MRPEFC
**
** Reference ID          : ETH_DUD_ACT_320
** Reference ID          : ETH_DUD_ACT_320_ERR001, ETH_DUD_ACT_320_ERR002
** Reference ID          : ETH_DUD_ACT_320_ERR003, ETH_DUD_ACT_320_ERR004
** Reference ID          : ETH_DUD_ACT_320_ERR005
** Reference ID          : ETH_DUD_ACT_320_GBL001, ETH_DUD_ACT_320_GBL002
** Reference ID          : ETH_DUD_ACT_320_GBL003, ETH_DUD_ACT_320_GBL004
** Reference ID          : ETH_DUD_ACT_320_GBL005, ETH_DUD_ACT_320_GBL006
** Reference ID          : ETH_DUD_ACT_320_GBL007, ETH_DUD_ACT_320_GBL008
** Reference ID          : ETH_DUD_ACT_320_REG001, ETH_DUD_ACT_320_REG002
** Reference ID          : ETH_DUD_ACT_320_REG003, ETH_DUD_ACT_320_REG004
** Reference ID          : ETH_DUD_ACT_320_REG005, ETH_DUD_ACT_320_REG006
** Reference ID          : ETH_DUD_ACT_320_REG007
***********************************************************************************************************************/
FUNC(void, ETH_PRIVATE_CODE) Eth_ETNE_HwMainFunction(CONST(uint32, AUTOMATIC) LulCtrlIdx)                               
{
  P2CONST(Eth_ETNEConfigType, AUTOMATIC, ETH_APPL_DATA) LpHwUnitConfig;
  P2VAR(volatile Eth_RSW2_RMACRegType, AUTOMATIC, REGSPACE) LpRmacsRegs;                                                /* PRQA S 3678 # JV-01 */

  /* Report Extended DEM (if any) */

  Eth_StatsRegValueType LstStats;

  LpHwUnitConfig =
    (P2CONST(Eth_ETNEConfigType, AUTOMATIC, ETH_APPL_DATA))Eth_GpCtrlConfigPtr[LulCtrlIdx].pHwUnitConfig;               /* PRQA S 0316 # JV-01 */

  if (ETH_RSW2_PORT_TYPE_ETHA == Eth_GaaRsw2PortType[LpHwUnitConfig->ulEthPortId])                                      
  {
    LpRmacsRegs = (volatile Eth_RSW2_RMACRegType *)Eth_GaaCtrl_RMACRegs[LulCtrlIdx];                                    

    /* Read RMAC counter register (and register clear) */
    LstStats.ulMROVFC  = LpRmacsRegs->ulMROVFC;  /* Receive overflow Counter */                                         /* PRQA S 2983 # JV-01 */
    LstStats.ulMRFMEFC = LpRmacsRegs->ulMRFMEFC; /* RMAC Received FCS/mCRC error frame count */
    LstStats.ulMRGUEFC = LpRmacsRegs->ulMRGUEFC; /* RMAC Received good undersize error frame count */
    LstStats.ulMRBUEFC = LpRmacsRegs->ulMRBUEFC; /* RMAC Received bad undersize error frame count */
    LstStats.ulMRGOEFC = LpRmacsRegs->ulMRGOEFC; /* RMAC Received good oversize error frame count */
    LstStats.ulMRBOEFC = LpRmacsRegs->ulMRBOEFC; /* RMAC Received bad oversize error frame count */
    LstStats.ulMRNEFC  = LpRmacsRegs->ulMRNEFC;  /* RMAC Received nibble error frame count */
    LstStats.ulMRFCEFC = LpRmacsRegs->ulMRFCEFC; /* RMAC Received fragment count error frame count */                   /* PRQA S 2983 # JV-01 */
    LstStats.ulMRXBCEU = LpRmacsRegs->ulMRXBCEU; /* RMAC Received byte counter E-frames upper side */                   /* PRQA S 2983 # JV-01 */
    LstStats.ulMRXBCEL = LpRmacsRegs->ulMRXBCEL; /* RMAC Received byte counter E-frames lower side */                   /* PRQA S 2983 # JV-01 */
    LstStats.ulMRXBCPU = LpRmacsRegs->ulMRXBCPU; /* RMAC Received byte counter P-frames upper side */                   /* PRQA S 2983 # JV-01 */
    LstStats.ulMRXBCPL = LpRmacsRegs->ulMRXBCPL; /* RMAC Received byte counter P-frames lower side */                   /* PRQA S 2983 # JV-01 */
    LstStats.ulMRFC    = LpRmacsRegs->ulMRFC;    /* RMAC Received fragment count error frame count */                   /* PRQA S 2983 # JV-01 */
    LstStats.ulMRBFC   = LpRmacsRegs->ulMRBFC;   /* RMAC Received good broadcast frame counter */                       /* PRQA S 2983 # JV-01 */
    LstStats.ulMRUFC   = LpRmacsRegs->ulMRUFC;   /* RMAC Received good unicast frame counter */                         /* PRQA S 2983 # JV-01 */
    LstStats.ulMRMFC   = LpRmacsRegs->ulMRMFC;   /* RMAC Received good multicast frame counter */                       /* PRQA S 2983 # JV-01 */
    LstStats.ulMTXBCEU = LpRmacsRegs->ulMTXBCEU; /* RMAC Transmitted byte counter E-frames upper side */                /* PRQA S 2983 # JV-01 */
    LstStats.ulMTXBCEL = LpRmacsRegs->ulMTXBCEL; /* RMAC Transmitted byte counter E-frames lower side */                /* PRQA S 2983 # JV-01 */
    LstStats.ulMTXBCPU = LpRmacsRegs->ulMTXBCPU; /* RMAC Transmitted byte counter P-frames upper side */                /* PRQA S 2983 # JV-01 */
    LstStats.ulMTXBCPL = LpRmacsRegs->ulMTXBCPL; /* RMAC Transmitted byte counter P-frames lower side */                /* PRQA S 2983 # JV-01 */
    LstStats.ulMTBFC   = LpRmacsRegs->ulMTBFC;   /* RMAC Transmitted broadcast frame counter */                         /* PRQA S 2983 # JV-01 */
    LstStats.ulMTMFC   = LpRmacsRegs->ulMTMFC;   /* RMAC Transmitted multicast frame counter */                         /* PRQA S 2983 # JV-01 */
    LstStats.ulMTUFC   = LpRmacsRegs->ulMTUFC;   /* RMAC Transmitted unicast frame counter */                           /* PRQA S 2983 # JV-01 */
    LstStats.ulMTEFC   = LpRmacsRegs->ulMTEFC;   /* RMAC Transmitted error frame counter */                             /* PRQA S 2983 # JV-01 */
    LstStats.ulMRPEFC  = LpRmacsRegs->ulMRPEFC;  /* RMAC Received PHY error frame count */

    #if (ETH_GET_COUNTER_VALUES_API == STD_ON)
    /* Add count information that drop frame counts for each error factor */
    Eth_HwRMAC_CountCounterValues(LulCtrlIdx, &LstStats);
    #endif /* (ETH_GET_COUNTER_VALUES_API == STD_ON) */

    #if (ETH_GET_RX_STATS_API == STD_ON)
    /* Add count Rx statistics information */
    Eth_HwRMAC_CountRxStats(LulCtrlIdx, &LstStats);
    #endif /* (ETH_GET_RX_STATS_API == STD_ON) */

    #if (ETH_GET_TX_STATS_API == STD_ON)
    /* Add count Tx statistics information */
    Eth_HwRMAC_CountTxStats(LulCtrlIdx, &LstStats);
    #endif /* (ETH_GET_TX_STATS_API == STD_ON) */

    #if (ETH_GET_TX_ERROR_COUNTER_VALUES_API == STD_ON)
    /* Add count error statistics information */
    Eth_HwRMAC_CountTxErrorCounterValues(LulCtrlIdx, &LstStats);
    #endif /* (ETH_GET_TX_ERROR_COUNTER_VALUES_API == STD_ON) */

    /* MRPEFC - Received PHY error frame counter */
    if (0UL < LstStats.ulMRPEFC)
    {
      /* Call DEM */
      Eth_DemConfigCheck(Eth_GpDemEventRxFramesLost[LulCtrlIdx], DEM_EVENT_STATUS_PREFAILED);                           
    } /* else No action required */

    /* MRFMEFC - Received FCS/mCRC error frame counter */
    if (0UL < LstStats.ulMRFMEFC)
    {
      /* Call DEM */
      Eth_DemConfigCheck(Eth_GpDemEventCRC[LulCtrlIdx], DEM_EVENT_STATUS_PREFAILED);                                    
    } /* else No action required */

    /* MRGUEFC - Received good undersize error frame counter */
    /* MRBUEFC - Received bad undersize error frame counter */
    if ((0UL < LstStats.ulMRGUEFC) || (0UL < LstStats.ulMRBUEFC))
    {
      /* Call DEM */
      Eth_DemConfigCheck(Eth_GpDemEventUnderSizeFrame[LulCtrlIdx], DEM_EVENT_STATUS_PREFAILED);                         
    } /* else No action required */

    /* MRGOEFC - Received good oversize error frame counter */
    /* MRBOEFC - Received bad oversize error frame counter */
    if ((0UL < LstStats.ulMRGOEFC) || (0UL < LstStats.ulMRBOEFC))
    {
      /* Call DEM */
      Eth_DemConfigCheck(Eth_GpDemEventOverSizeFrame[LulCtrlIdx], DEM_EVENT_STATUS_PREFAILED);                          
    } /* else No action required */

    /* MRNEFC - Received nibble error frame counter */
    if (0UL < LstStats.ulMRNEFC)
    {
      /* Call DEM */
      Eth_DemConfigCheck(Eth_GpDemEventAlignment[LulCtrlIdx], DEM_EVENT_STATUS_PREFAILED);                              
    } /* else No action required */
  } /* else No action required */
}

#if (ETH_GLOBAL_TIME_SUPPORT == STD_ON)
/***********************************************************************************************************************
** Function Name         : Eth_ETNE_HwGetCurrentTime
**
** Service ID            : NA
**
** Description           : Return TimeStamp from the HW register
**                         previously started.
**                       : It returns adjusted gPTP timer value
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
** Global Variable(s)    : Eth_GpRSW2_GPTPRegs
**
** Function(s) invoked   : Eth_HwGPTP_gPTPTimerTReadingFlow
**
** Registers Used        : PTPTMEC
**
** Reference ID          : ETH_DUD_ACT_321
** Reference ID          : ETH_DUD_ACT_321_GBL001
** Reference ID          : ETH_DUD_ACT_321_REG001
***********************************************************************************************************************/
FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_ETNE_HwGetCurrentTime(                                                       
  CONST(uint32, AUTOMATIC) LulCtrlIdx,
  CONSTP2VAR(Eth_TimeStampQualType, AUTOMATIC, ETH_APPL_DATA) LpTimeQualPtr,                                            /* PRQA S 3432 # JV-01 */
  CONSTP2VAR(Eth_TimeStampType, AUTOMATIC, ETH_APPL_DATA) LpTimeStampPtr)                                               /* PRQA S 3432 # JV-01 */
{
  Std_ReturnType LucReturnValue;

  /* Remove warning message */
  (void)LulCtrlIdx;

  /* gPTP timer status check */
  if (0UL != (Eth_GpRSW2_GPTPRegs->ulPTPTMEC & ETH_GPTP_TIMER_DOMAIN_MASK))
  {
    *LpTimeQualPtr = ETH_VALID;                                                                                         
    LucReturnValue = E_OK;
  }
  else
  {
    *LpTimeQualPtr = ETH_INVALID;
    LucReturnValue = E_NOT_OK;
  }

  if (E_OK == LucReturnValue)
  {
    Eth_HwGPTP_gPTPTimerTReadingFlow(
      ETH_GPTP_TIMER_DOMAIN, &LpTimeStampPtr->nanoseconds,                                                              
      &LpTimeStampPtr->seconds, &LpTimeStampPtr->secondsHi);
  } /* else No action required */

  return (LucReturnValue);
}

/***********************************************************************************************************************
** Function Name         : Eth_ETNE_HwGetEgressTimeStamp
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
**                         initialization using Eth_ControllerInit..
**
** Global Variable(s)    : Eth_GaaTxBufferMgrTable
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_424
** Reference ID          : ETH_DUD_ACT_424_GBL001
***********************************************************************************************************************/
FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_ETNE_HwGetEgressTimeStamp(                                                   
  CONST(uint32, AUTOMATIC) LulCtrlIdx,
  CONST(Eth_BufIdxType, AUTOMATIC) LulBufIdx,
  CONSTP2VAR(Eth_TimeStampQualType, AUTOMATIC, ETH_APPL_DATA) LpTimeQualPtr,                                            /* PRQA S 3432 # JV-01 */
  CONSTP2VAR(Eth_TimeStampType, AUTOMATIC, ETH_APPL_DATA) LpTimeStampPtr)                                               /* PRQA S 3432 # JV-01 */
{
  P2VAR(Eth_BufHandlerType, AUTOMATIC, ETH_APPL_DATA) LpTxBufferNode;                                                   /* PRQA S 3432, 3678 # JV-01, JV-01 */

  /* Initialize pointer to timestamp buffer */
  LpTxBufferNode = (Eth_BufHandlerType *)Eth_GaaTxBufferMgrTable[LulCtrlIdx][LulBufIdx].pBufferHdr;                     

  *LpTimeQualPtr = LpTxBufferNode->enTimeQual;                                                                          

  *LpTimeStampPtr = LpTxBufferNode->stTimeStamp;                                                                        

  return (E_OK);
}

/***********************************************************************************************************************
** Function Name         : Eth_ETNE_HwGetIngressTimeStamp
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
**                         initialization using Eth_ControllerInit..
**
** Global Variables Used : Eth_GaaRxFrame
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_425
** Reference ID          : ETH_DUD_ACT_425_GBL001
***********************************************************************************************************************/
FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_ETNE_HwGetIngressTimeStamp(                                                  
  CONST(uint32, AUTOMATIC) LulCtrlIdx,
  CONSTP2CONST(Eth_DataType, AUTOMATIC, ETH_APPL_DATA) LpDataPtr,
  CONSTP2VAR(Eth_TimeStampQualType, AUTOMATIC, ETH_APPL_DATA) LpTimeQualPtr,                                            /* PRQA S 3432 # JV-01 */
  CONSTP2VAR(Eth_TimeStampType, AUTOMATIC, ETH_APPL_DATA) LpTimeStampPtr)                                               /* PRQA S 3432 # JV-01 */
{
  P2VAR(Eth_DataType, AUTOMATIC, ETH_APPL_DATA) LpCompPtr;                                                              /* PRQA S 3432, 3678 # JV-01, JV-01 */
  Std_ReturnType LucReturnValue = E_NOT_OK;
  /* Read TimeStamp from the rxframe.Timestamp */
  LpCompPtr = (Eth_DataType *)(Eth_GaaRxFrame[LulCtrlIdx].ulEthTypeAddr + (uint32)ETH_ETHERTYPE_SIZE);                  /* PRQA S 0306, 3383 # JV-01, JV-01 */
  if (LpCompPtr == LpDataPtr)
  {
    LpTimeStampPtr->nanoseconds = Eth_GaaRxFrame[LulCtrlIdx].stTimestampRsw2.ulTSNS;                                    
    LpTimeStampPtr->seconds = Eth_GaaRxFrame[LulCtrlIdx].stTimestampRsw2.ulTSS;

    /* In RSW2, secondsHi is invalid. */
    /* Table 8-25: Reception ethernet descriptor format INFO and TS field descriptions */
    /*  TSS's Restrictions: The 16-upper bits of the gPTP [PTP] second part are truncated. */
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

/***********************************************************************************************************************
** Function Name         : Eth_ETNE_HwSetIncrementTimeForGptp
**
** Service ID            : NA
**
** Description           : Set a value to PTPTIVCt and issue a load request
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
** Return parameter      : E_OK - PTPTIVCt update success
**
** Preconditions         : Component Requires previous controller
**                         initialization using Eth_ControllerInit..
**
** Global Variable(s)    : Eth_GpRSW2_GPTPRegs
**
** Function(s) invoked   : None
**
** Registers Used        : PTPTIVCt
**
** Reference ID          : ETH_DUD_ACT_426
** Reference ID          : ETH_DUD_ACT_426_GBL001
** Reference ID          : ETH_DUD_ACT_426_REG001
***********************************************************************************************************************/
FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_ETNE_HwSetIncrementTimeForGptp(                                              
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulIncVal)
{
  /* Remove warning message */
  (void)LulCtrlIdx;

  /* R-Switch should use only one gPTP timer domain */
  Eth_GpRSW2_GPTPRegs->PTP[ETH_GPTP_TIMER_DOMAIN].ulPTPTIVCt= LulIncVal;
  return E_OK;
}

/***********************************************************************************************************************
** Function Name         : Eth_ETNE_HwSetOffsetTimeForGptp
**
** Service ID            : NA
**
** Description           : Adjust gPTP with an given delta
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant for the same Ctrl,
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
**                         initialization using Eth_ControllerInit.
**
** Global Variable(s)    : None
**
** Function(s) invoked   : Eth_HwGPTP_TimerTOffsetSettingFlow
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_427
***********************************************************************************************************************/
FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_ETNE_HwSetOffsetTimeForGptp(                                                 
  CONST(uint32, AUTOMATIC) LulCtrlIdx,
  CONSTP2CONST(Eth_TimeStampType, AUTOMATIC, ETH_APPL_DATA) LpTimeOffsetPtr)
{
  /* Remove warning message */
  (void)LulCtrlIdx;

  Eth_HwGPTP_TimerTOffsetSettingFlow(
    ETH_GPTP_TIMER_DOMAIN, LpTimeOffsetPtr->nanoseconds,                                                                
    LpTimeOffsetPtr->seconds, LpTimeOffsetPtr->secondsHi);

  return E_OK;
}

/***********************************************************************************************************************
** Function Name         : Eth_TsDescConfig
**
** Service ID            : NA
**
** Description           : Create timestamp descriptor chain & lerning descriptor.
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
** Preconditions         : None
**
** Global Variable(s)    : Eth_GaaTsDescChain, Eth_GpNextTsDesc
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_428
** Reference ID          : ETH_DUD_ACT_428_GBL001, ETH_DUD_ACT_428_GBL002
***********************************************************************************************************************/
STATIC FUNC(void, ETH_PRIVATE_CODE) Eth_TsDescConfig(void)
{
  P2VAR(Eth_BasicDescType, AUTOMATIC, ETH_APPL_DATA) LpLinkDesc;                                                        /* PRQA S 3432 # JV-01 */
  uint32 LulCnt;

  /* TS descriptor chain setting */
  for (LulCnt = 0UL; LulCnt < ETH_MAX_TS_DESCRIPTOR; LulCnt++)
  {
    /* Set frame empty type */
    Eth_GaaTsDescChain[LulCnt].ulDs    = 0U;
    Eth_GaaTsDescChain[LulCnt].ulInfo0 = 0U;
    Eth_GaaTsDescChain[LulCnt].ulErr   = 0U;
    Eth_GaaTsDescChain[LulCnt].ulDse   = 0U;
    Eth_GaaTsDescChain[LulCnt].ulAxie  = 0U;
    Eth_GaaTsDescChain[LulCnt].ulDie   = 1U;
    Eth_GaaTsDescChain[LulCnt].stTimestamp.ulTSNS    = 0U;
    Eth_GaaTsDescChain[LulCnt].stTimestamp.ulTSS     = 0U;
    Eth_GaaTsDescChain[LulCnt].ulDt    = ETH_DESC_FEMPTY_ND;
  }
  LpLinkDesc = (P2VAR(Eth_BasicDescType, AUTOMATIC, ETH_APPL_DATA))&Eth_GaaTsDescChain[LulCnt];                         /* PRQA S 3432, 0310 # JV-01, JV-01 */
  /* Set link type for cyclic descriptor */
  LpLinkDesc->ulDs    = 0U;
  LpLinkDesc->ulInfo0 = 0U;
  LpLinkDesc->ulErr   = 0U;
  LpLinkDesc->ulDse   = 0U;
  LpLinkDesc->ulAxie  = 0U;
  LpLinkDesc->ulDie   = 0U;
  LpLinkDesc->ulDptrH = 0U;
  LpLinkDesc->ulDptr  = (uint32)&Eth_GaaTsDescChain[0];                                                                 /* PRQA S 0306 # JV-01 */
  LpLinkDesc->ulDt    = ETH_DESC_LINKFIX_RSW2;

  Eth_GpNextTsDesc = &Eth_GaaTsDescChain[0];
}
#endif /* (ETH_GLOBAL_TIME_SUPPORT == STD_ON) */

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
** Reference ID          : ETH_DUD_ACT_327
***********************************************************************************************************************/
FUNC(void, ETH_PRIVATE_CODE) Eth_WaitNanoSec(CONST(uint32, AUTOMATIC) LulNanosec)                                       /* PRQA S 1505 # JV-01 */
{
  CONST(uint32, AUTOMATIC) LulCycle = ETH_NS2HZ(LulNanosec) + 1UL;                                                      /* PRQA S 3469, 3383 # JV-01, JV-01 */
  volatile uint32 LulCount;

  for (LulCount = 0UL; LulCount < LulCycle; LulCount++)                                                                 /* PRQA S 3387, 3416 # JV-01, JV-01 */
  {
    /* No action required */
  }
}

/***********************************************************************************************************************
** Function Name         : Eth_TxRxDescConfig
**
** Service ID            : NA
**
** Description           : Create descriptor chain & lerning descriptor.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulCtrlIdx : Index of a controller
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : E_OK - Success in lerning Tx/Rx descriptor.
**                         E_NOT_OK - Faile in lerning Tx/Rx descriptor.
**
** Preconditions         : None
**
** Global Variable(s)    : Eth_GpCtrlConfigPtr, Eth_GaaHeap, Eth_GaaCtrlStat,
**                         Eth_GaaLinkFixTable, Eth_GaaRsw2PortType
**                         Eth_GstDescChainMap
**
** Function(s) invoked   : Eth_Util_RamAlloc
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_435
** Reference ID          : ETH_DUD_ACT_435_GBL001, ETH_DUD_ACT_435_GBL002
** Reference ID          : ETH_DUD_ACT_435_GBL003, ETH_DUD_ACT_435_GBL004
** Reference ID          : ETH_DUD_ACT_435_GBL005, ETH_DUD_ACT_435_GBL006
** Reference ID          : ETH_DUD_ACT_435_GBL012, ETH_DUD_ACT_435_GBL013
***********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_TxRxDescConfig(CONST(uint32, AUTOMATIC) LulCtrlIdx)                   
{
  P2CONST(Eth_ETNEConfigType, AUTOMATIC, ETH_APPL_DATA) LpHwUnitConfig;
  P2VAR(Eth_ExtTxDirDescType, AUTOMATIC, ETH_APPL_DATA) LpTxDescChain;                                                  /* PRQA S 3432 # JV-01 */
  P2VAR(Eth_ExtRxEthDescType, AUTOMATIC, ETH_APPL_DATA) LpRxDescChain;                                                  /* PRQA S 3432 # JV-01 */
  P2VAR(Eth_DescChainInfo, AUTOMATIC, ETH_APPL_DATA) LpChainInfo;                                                       /* PRQA S 3432 # JV-01 */
  P2VAR(uint8, AUTOMATIC, ETH_APPL_DATA) LpRxBuffer;                                                                    /* PRQA S 3432 # JV-01 */
  uint32 LulRxBufferIndex;
  uint32 LulChainId;
  uint32 LulCntI;
  uint32 LulCntJ;
  Std_ReturnType LucResult;
  P2VAR(Eth_LinkDescTypeRsw2, AUTOMATIC, ETH_APPL_DATA) LpLinkDesc;                                                     /* PRQA S 3432 # JV-01 */

  LucResult = E_OK;

  LpHwUnitConfig =
    (P2CONST(Eth_ETNEConfigType, AUTOMATIC, ETH_APPL_DATA))Eth_GpCtrlConfigPtr[LulCtrlIdx].pHwUnitConfig;               /* PRQA S 0316 # JV-01 */

  /* Create Tx descriptor */
  for (LulCntI = 0UL; LulCntI < (uint32)LpHwUnitConfig->stQueueConfig.ucNumberOfTxQueue; LulCntI++)                     
  {
    LpTxDescChain = (P2VAR(Eth_ExtTxDirDescType, AUTOMATIC, ETH_APPL_DATA))Eth_Util_RamAlloc(Eth_GpDescHeap,            /* PRQA S 0316, 0317, 3432 # JV-01, JV-01, JV-01 */
                        (LpHwUnitConfig->stQueueConfig.pTxQueueConfig[LulCntI].ulQueueBufs + ETH_CYCLIC_DESC_NUM)       /* PRQA S 3383 # JV-01 */
                        * ETH_EXT_TX_DIR_DESC_SIZE);                                                                    /* PRQA S 3384 # JV-01 */

    if (NULL_PTR == LpTxDescChain)
    {
      LucResult = E_NOT_OK;
      break;
    } /* else No action required */
    
    /* Store the head Tx descriptor address */
    Eth_GaaCtrlStat[LulCtrlIdx].stHwStat.aaNextTxDesc[LulCntI] = LpTxDescChain;                                         
    Eth_GaaCtrlStat[LulCtrlIdx].stHwStat.aaHeadTxDesc[LulCntI] = LpTxDescChain;                                         

    /* Set Tx descriptor chain to LINKFIX table */
    LpLinkDesc = &Eth_GaaLinkFixTable[0];
    
    /* Get Target Chain Id */
    LulChainId = LpHwUnitConfig->stQueueConfig.pTxQueueConfig[LulCntI].ulChainId;
    LpLinkDesc[LulChainId].ulDptrH = 0U;                                                                                
    LpLinkDesc[LulChainId].ulDptr = (uint32)LpTxDescChain;                                                              /* PRQA S 0306 # JV-01 */

    /* Set Descriptor Chain Map Info */
    LpChainInfo = &(Eth_GstDescChainMap.aaChainInfo[LulChainId]);                                                       
    LpChainInfo->enDir = ETH_TX_RSW2;                                                                                   
    LpChainInfo->ulCtrlIdx = LulCtrlIdx;
    LpChainInfo->ulFifoIdx = LpHwUnitConfig->stQueueConfig.pTxQueueConfig[LulCntI].ulQueueId;
    LpChainInfo->enInterrupt = Eth_GpCtrlConfigPtr[LulCtrlIdx].pEthConfig->enTxInterruptMode;                           
    Eth_GstDescChainMap.ucValidChainId[Eth_GstDescChainMap.ulValidChainNum] =                                           
      (uint8)(LulChainId % ETH_RACE_AXI_CHAIN_N);
    Eth_GstDescChainMap.ulValidChainNum++;                                                                              /* PRQA S 3383 # JV-01 */
    
    /* Set descriptor chain */
    for (LulCntJ = 0UL; LulCntJ < LpHwUnitConfig->stQueueConfig.pTxQueueConfig[LulCntI].ulQueueBufs; LulCntJ++)
    {
      /* Set frame empty type */
      LpTxDescChain->stHeader.ulErr = 0U;
      LpTxDescChain->stHeader.ulDse = 0U;
      LpTxDescChain->stHeader.ulAxie = 0U;
      LpTxDescChain->stHeader.ulInfo0 = 0U;
      LpTxDescChain->stHeader.ulDie = 0U;
      /* It will be set only during Transmission at run time */
      LpTxDescChain->stHeader.ulDs = 0U;
      LpTxDescChain->stHeader.ulDptrH = 0U;
      LpTxDescChain->stHeader.ulDptr = 0U;

      if (ETH_RSW2_PORT_TYPE_GWCA == Eth_GaaRsw2PortType[LpHwUnitConfig->ulEthPortId])                                  
      {
        LpTxDescChain->ulFmt = 0U; /* Format Ethernet Descpriter */
      }
      else
      {
        LpTxDescChain->ulFmt = 1U; /* Format Direct Descpriter */
      }
      LpTxDescChain->stHeader.ulDt = ETH_DESC_FEMPTY;

      /* Next data descriptor */
      LpTxDescChain++;
    }
    /* Set link type for cyclic descriptor */
    LpTxDescChain->stHeader.ulDie    = 0U;                                                                              
    LpTxDescChain->stHeader.ulDptrH  = 0U;
    LpTxDescChain->stHeader.ulDptr   = (uint32)Eth_GaaCtrlStat[LulCtrlIdx].stHwStat.aaHeadTxDesc[LulCntI];              /* PRQA S 0306 # JV-01 */
    LpTxDescChain->stHeader.ulInfo0  = 0U;
    LpTxDescChain->stHeader.ulAxie   = 0U;
    LpTxDescChain->stHeader.ulDse    = 0U;
    LpTxDescChain->stHeader.ulErr    = 0U;
    LpTxDescChain->stHeader.ulDt     = ETH_DESC_LINKFIX_RSW2;
  }

  /* Create Rx descriptor */
  LulRxBufferIndex = 0UL;
  for (LulCntI = 0UL;
       (LulCntI < (uint32)LpHwUnitConfig->stQueueConfig.ucNumberOfRxQueue) && (E_OK == LucResult); LulCntI++)
  {
    LpRxDescChain = (P2VAR(Eth_ExtRxEthDescType, AUTOMATIC, ETH_APPL_DATA))Eth_Util_RamAlloc(Eth_GpDescHeap,            /* PRQA S 0316, 0317, 3432 # JV-01, JV-01, JV-01 */
                        (LpHwUnitConfig->stQueueConfig.pRxQueueConfig[LulCntI].ulQueueBufs + ETH_CYCLIC_DESC_NUM)       /* PRQA S 3383 # JV-01 */
                        * ETH_EXT_RX_ETH_DESC_SIZE);                                                                    /* PRQA S 3384 # JV-01 */

    if (NULL_PTR == LpRxDescChain)
    {
      LucResult = E_NOT_OK;
      break;
    } /* else No action required */

    /* Store the head Rx descriptor address */
    Eth_GaaCtrlStat[LulCtrlIdx].stHwStat.aaHeadRxDesc[LulCntI] = LpRxDescChain;                                         
    Eth_GaaCtrlStat[LulCtrlIdx].stHwStat.aaNextRxDesc[LulCntI] = LpRxDescChain;                                         

    /* Set Rx descriptor chain to LINKFIX table */
    LpLinkDesc = &Eth_GaaLinkFixTable[0];
    
    /* Get Target Chain Id */
    LulChainId = LpHwUnitConfig->stQueueConfig.pRxQueueConfig[LulCntI].ulChainId;
    LpLinkDesc[LulChainId].ulDptrH = 0U;                                                                                
    LpLinkDesc[LulChainId].ulDptr = (uint32)LpRxDescChain;                                                              /* PRQA S 0306 # JV-01 */

    /* Set Descriptor Chain Map Info */
    LpChainInfo = &(Eth_GstDescChainMap.aaChainInfo[LulChainId]);                                                       
    LpChainInfo->enDir = ETH_RX_RSW2;                                                                                   
    LpChainInfo->ulCtrlIdx = LulCtrlIdx;
    LpChainInfo->ulFifoIdx = LpHwUnitConfig->stQueueConfig.pRxQueueConfig[LulCntI].ulQueueId;
    LpChainInfo->enInterrupt = Eth_GpCtrlConfigPtr[LulCtrlIdx].pEthConfig->enRxInterruptMode;
    Eth_GstDescChainMap.ucValidChainId[Eth_GstDescChainMap.ulValidChainNum] = 
      (uint8)(LulChainId % ETH_RACE_AXI_CHAIN_N);
    Eth_GstDescChainMap.ulValidChainNum++;                                                                              /* PRQA S 3383 # JV-01 */
    
    /* Set Rx descriptor chain */
    for (LulCntJ = 0UL; LulCntJ < LpHwUnitConfig->stQueueConfig.pRxQueueConfig[LulCntI].ulQueueBufs; LulCntJ++)
    {
      LpRxBuffer = (P2VAR(uint8, AUTOMATIC, ETH_APPL_DATA)) Eth_Util_RamAlloc(&Eth_GaaHeap[LulCtrlIdx],                 /* PRQA S 0316, 3432 # JV-01, JV-01 */
                  LpHwUnitConfig->stRxConfig.ulMaxFrameSize + (uint32)sizeof(Eth_BufIdxType) + ETH_RX_PAYLOAD_PADDING); /* PRQA S 3383 # JV-01 */

      if (NULL_PTR == LpRxBuffer)
      {
        /* Allocation memory error due to lack of resources */
        LucResult = E_NOT_OK;
        break;
      } /* else No action required */

      /* Add receive buffer index */
      *(P2VAR(Eth_BufIdxType, AUTOMATIC, ETH_APPL_DATA))LpRxBuffer = LulRxBufferIndex;                                  /* PRQA S 0310, 3305, 3432 # JV-01, JV-01, JV-01 */
      LulRxBufferIndex++;                                                                                               /* PRQA S 3383 # JV-01 */
      /* Set frame empty type */
      LpRxDescChain->stHeader.ulErr   = 0U;
      LpRxDescChain->stHeader.ulDse   = 0U;
      LpRxDescChain->stHeader.ulAxie  = 0U;
      LpRxDescChain->stHeader.ulInfo0 = 0U;
      LpRxDescChain->stHeader.ulDs    = LpHwUnitConfig->stRxConfig.ulMaxFrameSize;
      LpRxDescChain->stHeader.ulDptrH = 0U;
      LpRxDescChain->stHeader.ulDptr  = (uint32)(LpRxBuffer + (uint32)sizeof(Eth_BufIdxType) + ETH_RX_PAYLOAD_PADDING); /* PRQA S 0306, 0488 # JV-01, JV-01 */

      if (ETH_ENABLE == Eth_GpCtrlConfigPtr[LulCtrlIdx].pEthConfig->enRxInterruptMode)                                  /* PRQA S 3416 # JV-01 */
      {
        LpRxDescChain->stHeader.ulDie = 1U;
      }
      else
      {
        LpRxDescChain->stHeader.ulDie = 0U;
      }
      LpRxDescChain->stHeader.ulDt    = ETH_DESC_FEMPTY;

      /* Next data descriptor */
      LpRxDescChain++;
    }
    /* Set link type for cyclic descriptor */
    LpRxDescChain->stHeader.ulDie   = 0U;
    LpRxDescChain->stHeader.ulDptrH = 0U;
    LpRxDescChain->stHeader.ulDptr  = (uint32)Eth_GaaCtrlStat[LulCtrlIdx].stHwStat.aaHeadRxDesc[LulCntI];               /* PRQA S 0306 # JV-01 */
    LpRxDescChain->stHeader.ulInfo0 = 0U;
    LpRxDescChain->stHeader.ulAxie  = 0U;
    LpRxDescChain->stHeader.ulDse   = 0U;
    LpRxDescChain->stHeader.ulErr   = 0U;
    LpRxDescChain->stHeader.ulDt    = ETH_DESC_LINKFIX_RSW2;
  }

  return LucResult;
}

/***********************************************************************************************************************
** Function Name         : Eth_RxQueueProcess
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
**                       : LucFifoIdx - Rx queue index
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : When polling mode:
**                           ETH_EXT_NOT_RECEIVED : there was no received frame
**                           ETH_EXT_RECEIVED     : there was one received frame
**                           ETH_EXT_RECEIVED_MORE_DATA_AVAILABLE:
**                                 there were more than one received frames
**                           ETH_EXT_NOT_RECEIVED_MORE_DATA_AVAILABLE:
**                                 there was no received, but there are still receive frames.
**
** Preconditions         : None
**
** Global Variable(s)    : Eth_GaaCtrlStat, Eth_GaaRxFrame
**
** Function(s) invoked   : Eth_IsRxFrameValid, EthSwt_EthRxProcessFrame,
**                         Eth_RxCallEthIf, EthSwt_EthRxFinishedIndication
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_437
** Reference ID          : ETH_DUD_ACT_437_GBL001, ETH_DUD_ACT_437_GBL002
** Reference ID          : ETH_DUD_ACT_437_GBL003, ETH_DUD_ACT_437_GBL004
** Reference ID          : ETH_DUD_ACT_437_GBL005, ETH_DUD_ACT_437_GBL006
** Reference ID          : ETH_DUD_ACT_437_GBL007, ETH_DUD_ACT_437_GBL008
** Reference ID          : ETH_DUD_ACT_437_GBL009
***********************************************************************************************************************/
FUNC(Eth_ExtRxStatusType, ETH_PRIVATE_CODE) Eth_RxQueueProcess(                                                         /* PRQA S 1505 # JV-01 */
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint8, AUTOMATIC) LulQueueIdx)
{
  P2VAR(Eth_ExtRxEthDescType, AUTOMATIC, ETH_APPL_DATA) LpDataDesc;                                                     /* PRQA S 3432 # JV-01 */
  P2VAR(Eth_ExtRxEthDescType, AUTOMATIC, ETH_APPL_DATA) LpTempDesc;                                                     /* PRQA S 3432 # JV-01 */
  P2CONST(Eth_ETNEConfigType, AUTOMATIC, ETH_APPL_DATA) LpHwUnitConfig;
  boolean LblRxFrameValid = ETH_TRUE;                                                                                   
  Eth_ExtRxStatusType LenRetValue;

  #if (ETH_ETHSWITCH_MANAGEMENT_SUPPORT == STD_ON)
  Eth_BufIdxType LulBufIdx;
  P2VAR(uint8, AUTOMATIC, ETH_APPL_DATA) LpDataPtr;                                                                     /* PRQA S 3432 # JV-01 */
  boolean LblIsMgmtFrameOnlyPtr;
  uint16 LusLength;
  Std_ReturnType LucReturnValue;
  #endif

  LenRetValue = ETH_EXT_NOT_RECEIVED;

  LpHwUnitConfig =
    (P2CONST(Eth_ETNEConfigType, AUTOMATIC, ETH_APPL_DATA))Eth_GpCtrlConfigPtr[LulCtrlIdx].pHwUnitConfig;               /* PRQA S 0316 # JV-01 */

  /* Get descriptor for read */
  LpDataDesc = Eth_GaaCtrlStat[LulCtrlIdx].stHwStat.aaNextRxDesc[LulQueueIdx];                                          
  LpTempDesc = LpDataDesc;

  if (ETH_DESC_FSINGLE == LpDataDesc->stHeader.ulDt)                                                                    
  {
    /* Set Rx descriptor info */
    Eth_GaaRxFrame[LulCtrlIdx].ulFrameAddr   = LpDataDesc->stHeader.ulDptr;                                             
    Eth_GaaRxFrame[LulCtrlIdx].ulEthTypeAddr = LpDataDesc->stHeader.ulDptr + ETH_SRC_DST_ADDRESS_SIZE;                  /* PRQA S 3383 # JV-01 */
    Eth_GaaRxFrame[LulCtrlIdx].ulFrameLength = LpDataDesc->stHeader.ulDs;                                               
    #if (ETH_GLOBAL_TIME_SUPPORT == STD_ON)
    Eth_GaaRxFrame[LulCtrlIdx].stTimestampRsw2   = LpDataDesc->stTimestamp;                                             
    #endif

    /* Set descriptor to be read next */
    LpDataDesc++;                                                                                                       
    while (LpDataDesc->stHeader.ulDt == ETH_DESC_LINKFIX_RSW2)                                                          
    {
      LpDataDesc = (P2VAR(Eth_ExtRxEthDescType, AUTOMATIC, ETH_APPL_DATA))LpDataDesc->stHeader.ulDptr;                  /* PRQA S 0306, 3432 # JV-01, JV-01 */
    }

    #if (ETH_UPDATE_PHYS_ADDR_FILTER == STD_ON)
    /* check whether received frame is valid or not */
    LblRxFrameValid = Eth_IsRxFrameValid(LulCtrlIdx, &Eth_GaaRxFrame[LulCtrlIdx]);                                      
    #endif

    if (ETH_TRUE == LblRxFrameValid)
    {
      if (ETH_DESC_FSINGLE == LpDataDesc->stHeader.ulDt)                                                                
      {
        /* More frames are available */
        LenRetValue = ETH_EXT_RECEIVED_MORE_DATA_AVAILABLE;
      }
      else
      {
        /* Frame valid - Update status */
        LenRetValue = ETH_EXT_RECEIVED;
      }

      #if (ETH_ETHSWITCH_MANAGEMENT_SUPPORT == STD_ON)
      LulBufIdx = *(P2VAR(Eth_BufIdxType, AUTOMATIC, ETH_APPL_DATA))                                                    /* PRQA S 0306, 3432 # JV-01, JV-01 */
        (Eth_GaaRxFrame[LulCtrlIdx].ulFrameAddr - sizeof(Eth_BufIdxType) - ETH_RX_PAYLOAD_PADDING);                     /* PRQA S 3383, 3384 # JV-01, JV-01 */
      LpDataPtr = (P2VAR(uint8, AUTOMATIC, ETH_APPL_DATA))Eth_GaaRxFrame[LulCtrlIdx].ulEthTypeAddr;                     /* PRQA S 0306, 3432 # JV-01, JV-01 */

      /* Since the maximum value of buffer size is 1518, casting to uint16 does no problem. */
      LusLength = (uint16)(Eth_GaaRxFrame[LulCtrlIdx].ulFrameLength - ETH_HEADER_SIZE);                                 /* PRQA S 3383 # JV-01 */
      LblIsMgmtFrameOnlyPtr = ETH_FALSE;

      /* Since the maximum value of controller index is 4, casting to uint8 does no problem. */
      LucReturnValue = EthSwt_EthRxProcessFrame((uint8)LulCtrlIdx, LulBufIdx, &LpDataPtr,
                                                &LusLength, &LblIsMgmtFrameOnlyPtr);
      if (E_OK == LucReturnValue)
      {
        Eth_GaaRxFrame[LulCtrlIdx].ulEthTypeAddr = (uint32)LpDataPtr;                                                   /* PRQA S 0306 # JV-01 */
        Eth_GaaRxFrame[LulCtrlIdx].ulFrameLength = (uint32)(LusLength + ETH_HEADER_SIZE);                               /* PRQA S 3383 # JV-01 */

        if (ETH_FALSE == LblIsMgmtFrameOnlyPtr)
        {
          /* Call EthIf if the Frame Received is valid */
          Eth_RxCallEthIf(LulCtrlIdx, &Eth_GaaRxFrame[LulCtrlIdx]);                                                     
        }
        else
        {
          /* Must not be the Rx processed */
          /* Since the maximum value of controller index is 4, casting to uint8 does no problem. */
          (void)EthSwt_EthRxFinishedIndication((uint8)LulCtrlIdx, LulBufIdx);
        }
      }
      else
      {
        /* Normal operation if E_NOT_OK */
        Eth_RxCallEthIf(LulCtrlIdx, &Eth_GaaRxFrame[LulCtrlIdx]);                                                       
      }
      #else
      /* Call EthIf if the Frame Received is valid */
      Eth_RxCallEthIf(LulCtrlIdx, &Eth_GaaRxFrame[LulCtrlIdx]);                                                         
      #endif
      
    }
    else
    {
      /* Frame Invalid - E.g. Multicast to be discarded */
      /* No Call of EthIf */
      if (ETH_DESC_FSINGLE == LpDataDesc->stHeader.ulDt)
      {
        /* Not received, but more frames are available */
        LenRetValue = ETH_EXT_NOT_RECEIVED_MORE_DATA_AVAILABLE;
      } /* else No action required */
    }
    Eth_GaaCtrlStat[LulCtrlIdx].stHwStat.aaNextRxDesc[LulQueueIdx] = LpDataDesc;                                        

    /* Reset Rx descriptor */
    LpTempDesc->stHeader.ulDs      = LpHwUnitConfig->stRxConfig.ulMaxFrameSize;                                         
    LpTempDesc->stHeader.ulInfo0   = 0U;
    LpTempDesc->stHeader.ulAxie    = 0U;
    LpTempDesc->stHeader.ulDse     = 0U;
    LpTempDesc->stHeader.ulErr     = 0U;
    #if (ETH_GLOBAL_TIME_SUPPORT == STD_ON)
    LpTempDesc->stTimestamp.ulTSNS = (uint32)0UL;
    LpTempDesc->stTimestamp.ulTSV  = 0U;
    LpTempDesc->stTimestamp.ulTSD  = 0U;
    LpTempDesc->stTimestamp.ulTSS  = 0U;
    #endif /* ETH_GLOBAL_TIME_SUPPORT */
    LpTempDesc->stHeader.ulDt      = ETH_DESC_FEMPTY;
  } /* else No action required */

  return LenRetValue;
}

#if (ETH_UPDATE_PHYS_ADDR_FILTER == STD_ON)
/***********************************************************************************************************************
** Function Name         : Eth_IsRxFrameValid
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
** Function(s) invoked   : Eth_IsMatchFilter
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_332
***********************************************************************************************************************/
STATIC FUNC(boolean, ETH_PRIVATE_CODE) Eth_IsRxFrameValid(
  CONST(uint32, AUTOMATIC) LulCtrlIdx,
  CONSTP2CONST(Eth_RxFrameType, AUTOMATIC, ETH_APPL_DATA) LpRxFrame)
{
  Eth_MacAddressType LstDstAddress;
  boolean LblPass;

  ETH_PACK_ADDRESS_FROM_8(((P2VAR(uint8, AUTOMATIC, ETH_APPL_DATA))LpRxFrame->ulFrameAddr), LstDstAddress);             /* PRQA S 0306, 3432, 3469 # JV-01, JV-01, JV-01 */

  LblPass = Eth_IsMatchFilter(LulCtrlIdx, &LstDstAddress);

  return LblPass;
}
#endif  /* (ETH_UPDATE_PHYS_ADDR_FILTER == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Eth_RxCallEthIf
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
** Global Variables Used : Eth_GstBroadcastAddr
**
** Function(s) invoked   : EthIf_RxIndication, EthSwt_EthRxFinishedIndication,
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_439
** Reference ID          : ETH_DUD_ACT_439_GBL002
***********************************************************************************************************************/
STATIC FUNC(void, ETH_PRIVATE_CODE) Eth_RxCallEthIf(
  CONST(uint32, AUTOMATIC) LulCtrlIdx,
  CONSTP2CONST(Eth_RxFrameType, AUTOMATIC, ETH_APPL_DATA) LpFrame)
{
  boolean LblBroadcast;
  P2CONST(Eth_DataType, AUTOMATIC, ETH_APPL_DATA) LpFrameType;
  Eth_FrameType LddFrameType;
  Eth_MacAddressType LstMacAddr;
  #if (ETH_ETHSWITCH_MANAGEMENT_SUPPORT == STD_ON)
  Eth_BufIdxType LulBufIdx;
  #endif
  P2CONST(Eth_EtherFrameType, AUTOMATIC, ETH_APPL_DATA) LstEtherFrame;

  LstEtherFrame = (P2CONST(Eth_EtherFrameType, AUTOMATIC, ETH_APPL_DATA)) LpFrame->ulFrameAddr;                         /* PRQA S 0306 # JV-01 */

  ETH_PACK_ADDRESS_FROM_8(LstEtherFrame->ucDstAddr, LstMacAddr);                                                        /* PRQA S 3469 # JV-01 */

  if (0UL == ETH_COMPARE_MAC(LstMacAddr, Eth_GstBroadcastAddr))                                                         /* PRQA S 3469 # JV-01 */
  {
    LblBroadcast = ETH_TRUE;
  }
  else
  {
    LblBroadcast = ETH_FALSE;
  }

  LpFrameType = (const Eth_DataType *)LpFrame->ulEthTypeAddr;                                                           /* PRQA S 0306 # JV-01 */
  LddFrameType = (Eth_FrameType)((uint32)LpFrameType[0] << ETH_BYTE_BITS);                                              
  LddFrameType |= (Eth_FrameType)LpFrameType[1];

  /* Since the maximum value of Controller Index is 4, casting to uint8 does no problem. */
  EthIf_RxIndication((uint8)LulCtrlIdx, LddFrameType, LblBroadcast, LstEtherFrame->ucSrcAddr,
    LpFrameType + ETH_ETHERTYPE_SIZE, (uint16)(LpFrame->ulFrameLength - ETH_HEADER_SIZE));                              /* PRQA S 0488, 3383 # JV-01, JV-01 */

  #if (ETH_ETHSWITCH_MANAGEMENT_SUPPORT == STD_ON)
  LulBufIdx = *(P2VAR(Eth_BufIdxType, AUTOMATIC, ETH_APPL_DATA))                                                        /* PRQA S 0306, 3432 # JV-01, JV-01 */
    (LpFrame->ulFrameAddr - sizeof(Eth_BufIdxType) - ETH_RX_PAYLOAD_PADDING);                                           /* PRQA S 3383, 3384 # JV-01, JV-01 */
  (void)EthSwt_EthRxFinishedIndication((uint8)LulCtrlIdx, LulBufIdx);
  #endif
}

/***********************************************************************************************************************
** Function Name         : Eth_TxConfirmationQueueProcess (RSW2)
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
** Global Variable(s)    : Eth_GaaCtrlStat, Eth_GaaTxBufferMgrTable
**
** Function(s) invoked   : EthIf_TxConfirmation,Eth_ReleaseTxBuffer
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_496
** Reference ID          : ETH_DUD_ACT_496_CRT001, ETH_DUD_ACT_496_CRT002
** Reference ID          : ETH_DUD_ACT_496_GBL001, ETH_DUD_ACT_496_GBL002
***********************************************************************************************************************/
STATIC FUNC(void, ETH_PRIVATE_CODE) Eth_TxConfirmationQueueProcess(
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulQIdx)
{
  uint32 LulCnt;
  uint32 LulTxCnt;
  uint32 LulBufIdx;
  P2VAR(Eth_ExtTxDirDescType, AUTOMATIC, ETH_APPL_DATA) LpDataDesc;                                                     /* PRQA S 3432 # JV-01 */
  P2VAR(Eth_BufHandlerType, AUTOMATIC, ETH_APPL_DATA) LpBufHandlerPtr;                                                  /* PRQA S 3432, 3678 # JV-01, JV-01 */

  /* Get on-transmit count */
  LulTxCnt = Eth_GaaCtrlStat[LulCtrlIdx].stHwStat.aaBufTxCnt[LulQIdx];                                                  
  LpDataDesc = (Eth_ExtTxDirDescType *)Eth_GaaCtrlStat[LulCtrlIdx].stHwStat.aaHeadTxDesc[LulQIdx];
  for (LulCnt = 0UL; (LulCnt < LulTxCnt) && (ETH_DESC_FEMPTY == LpDataDesc->stHeader.ulDt); LulCnt++)                   
  {
    /* Get Tx buffer handler */
    LulBufIdx = (LpDataDesc->ulTsun - (LulCtrlIdx * ETH_TX_DESCR_TSUN_OFFSET));                                         /* PRQA S 3383 # JV-01 */
    LpBufHandlerPtr = Eth_GaaTxBufferMgrTable[LulCtrlIdx][LulBufIdx].pBufferHdr;                                        

    /* Check whether the transmission confirmation was enabled */
    if (ETH_TRUE == LpBufHandlerPtr->blTxConfirm)                                                                       
    {
      #if (ETH_GLOBAL_TIME_SUPPORT == STD_ON)
      if ((ETH_TRUE == LpBufHandlerPtr->blbenableTS) && (ETH_INVALID == LpBufHandlerPtr->enTimeQual))
      {
        /* Transmit is complete, but TS doesn't exist yet */
        break;
      }
      else
      {
        /* No action required */
      }
      #endif /* (ETH_GLOBAL_TIME_SUPPORT == STD_ON) */
      /* Call the callback function */
      /* Since the maximum value of controller index is 4, casting to uint8 does no problem. */
      EthIf_TxConfirmation((uint8)LulCtrlIdx, (Eth_BufIdxType)LpBufHandlerPtr->ulbufIdx, E_OK);
    }
    else
    {
      /* No action required */
    }

    ETH_ENTER_CRITICAL_SECTION(ETH_RAM_DATA_PROTECTION);

    /* Release the tx buffer resource */
    Eth_ETNE_ReleaseTxBuffer(LulCtrlIdx, LulBufIdx);

    /* Decrease the number of on-transmission buffer of current Tx queue */
    Eth_GaaCtrlStat[LulCtrlIdx].stHwStat.aaBufTxCnt[LulQIdx]--;                                                         /* PRQA S 3383 # JV-01 */

    ETH_EXIT_CRITICAL_SECTION(ETH_RAM_DATA_PROTECTION);

    /* Clear tx descriptor */
    LpDataDesc->stHeader.ulDs    = 0U;
    LpDataDesc->stHeader.ulInfo0 = 0U;
    LpDataDesc->stHeader.ulErr   = 0U;
    LpDataDesc->stHeader.ulDse   = 0U;
    LpDataDesc->stHeader.ulAxie  = 0U;
    LpDataDesc->stHeader.ulDie   = 0U;
    LpDataDesc->stHeader.ulDptrH = 0U;
    LpDataDesc->stHeader.ulDptr  = 0U;
    LpDataDesc->ulTxc = 0U;
    LpDataDesc->ulTsun = 0U;
    LpDataDesc->stHeader.ulDt    = ETH_DESC_FEMPTY;

    /* Update start descriptor */
    LpDataDesc++;                                                                                                       
    while (LpDataDesc->stHeader.ulDt == ETH_DESC_LINKFIX_RSW2)                                                          
    {
      LpDataDesc = (Eth_ExtTxDirDescType *)LpDataDesc->stHeader.ulDptr;                                                 /* PRQA S 0306 # JV-01 */
    }
    Eth_GaaCtrlStat[LulCtrlIdx].stHwStat.aaHeadTxDesc[LulQIdx] = LpDataDesc;                                            
  }
}

/***********************************************************************************************************************
** Function Name         : Eth_GetElapsedTimeValue
**
** Service ID            : NA
**
** Description           : This returns the elapsed timeout value of  Os timer
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LusTimeOutCount_Init
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : LulTimeOutCount_Elapsed - TickType
**
** Preconditions         : None
**
** Global Variable(s)    : None
**
** Function(s) invoked   : GetCounterValue
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_331
***********************************************************************************************************************/
STATIC FUNC(TickType, ETH_PRIVATE_CODE) Eth_GetElapsedTimeValue(
  P2VAR(TickType, AUTOMATIC, ETH_APPL_DATA) LusTimeOutCount)                                                            /* PRQA S 3432 # JV-01 */
{
  TickType LulTimeOutCount_Curr;
  TickType LulTimeOutCount_Elapsed;
  TickType LusTimeOutCount_Init;

  LusTimeOutCount_Init = *LusTimeOutCount;                                                                              

  LulTimeOutCount_Curr = 0UL;

  /* Get the current tick value from OS Counter */
  (void)GetCounterValue((CounterType)ETH_OS_COUNTER_ID, &LulTimeOutCount_Curr);

  /* Check whether current time out exceeds initial time out value */
  if (LulTimeOutCount_Curr >= LusTimeOutCount_Init)
  {
    /* Get elapsed time out count */
    LulTimeOutCount_Elapsed = LulTimeOutCount_Curr - LusTimeOutCount_Init;                                              
  }
  else
  {
    /* Get elapsed time out count */
    LulTimeOutCount_Elapsed = ((uint32)ETH_OS_COUNTER_MAX_VALUE - LusTimeOutCount_Init) + LulTimeOutCount_Curr;         /* PRQA S 3383 # JV-01 */
  }

  *LusTimeOutCount = LulTimeOutCount_Curr;

  return LulTimeOutCount_Elapsed;
}

#if ((ETH_CTRL_ENABLE_TX_INTERRUPT == STD_ON) || (ETH_CTRL_ENABLE_RX_INTERRUPT == STD_ON))
/***********************************************************************************************************************
** Function Name         : Eth_HwEnableInterrupt (RSW2)
**
** Service ID            : N/A
**
** Description           : Enable GWCA Interrupt
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulCtrlIdx : Control index
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : (ETH_CTRL_ENABLE_TX_INTERRUPT == STD_ON)
**                         || (ETH_CTRL_ENABLE_RX_INTERRUPT == STD_ON)
**
** Global Variable(s)    : Eth_GstDescChainMap, Eth_GaaRSW2_GWCARegs
**
** Function(s) invoked   : None
**
** Registers Used        : GWDIEi
**
** Reference ID          : ETH_DUD_ACT_442
** Reference ID          : ETH_DUD_ACT_442_GBL001
** Reference ID          : ETH_DUD_ACT_442_GBL002, ETH_DUD_ACT_442_GBL003
** Reference ID          : ETH_DUD_ACT_442_REG001
***********************************************************************************************************************/
STATIC FUNC(void, ETH_PRIVATE_CODE) Eth_HwEnableInterrupt(void)
{
  uint32 LulRegVal[ETH_RACE_AXI_CHAIN_N / ETH_RSW2_GWCA_NUM_OF_CHAIN_PER_REG];
  uint32 LulIdx;
  uint8  LucTargetChainId;

  /* Init Register Value */
  for (LulIdx = 0UL; LulIdx < (ETH_RACE_AXI_CHAIN_N / ETH_RSW2_GWCA_NUM_OF_CHAIN_PER_REG); LulIdx++)
  {
    LulRegVal[LulIdx] = 0UL;
  }

  /* Set GWDIEi Register Value */
  for (LulIdx = 0UL;  LulIdx < Eth_GstDescChainMap.ulValidChainNum; LulIdx++)
  {
    /* Get Target Chain Id */
    LucTargetChainId = Eth_GstDescChainMap.ucValidChainId[LulIdx];                                                      
    
    if (ETH_ENABLE == Eth_GstDescChainMap.aaChainInfo[LucTargetChainId].enInterrupt)                                    
    {
      LulRegVal[LucTargetChainId / ETH_RSW2_GWCA_NUM_OF_CHAIN_PER_REG] |=                                               
        (1UL << (LucTargetChainId % ETH_RSW2_GWCA_NUM_OF_CHAIN_PER_REG));
    }
  }
  
  for (LulIdx = 0; LulIdx < (ETH_RACE_AXI_CHAIN_N / ETH_RSW2_GWCA_NUM_OF_CHAIN_PER_REG); LulIdx++)
  {
    Eth_GaaRSW2_GWCARegs[ETH_RSW2_GWCA_ID]->GWDI[LulIdx].ulGWDIEi = LulRegVal[LulIdx];                                  
  }
}
#endif /* ((ETH_CTRL_ENABLE_TX_INTERRUPT == STD_ON) || (ETH_CTRL_ENABLE_RX_INTERRUPT == STD_ON)) */

#if ((ETH_GWCA_ERR_ISR == STD_ON) || (ETH_COMA_ERR_ISR == STD_ON) || (ETH_ETHA_ERR_ISR == STD_ON))
/***********************************************************************************************************************
** Function Name         : Eth_HwEnableErrorInterrupt (RSW2)
**
** Service ID            : N/A
**
** Description           : Enable GWCA / COMA / ETHA Error Interrupt
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
** Return parameter      : void
**
** Preconditions         : (ETH_GWCA_ERR_ISR == STD_ON)
**                         || (ETH_COMA_ERR_ISR == STD_ON)
**                         || (ETH_ETHA_ERR_ISR == STD_ON)
**
** Global Variable(s)    : Eth_GaaRSW2_GWCARegs, Eth_GpRSW2_COMARegs
**                         Eth_GaaRSW2_ETHARegs
**
** Function(s) invoked   : None
**
** Registers Used        : GWEIE0, CAEIE0, EAEIE0
**
** Reference ID          : ETH_DUD_ACT_513
** Reference ID          : ETH_DUD_ACT_513_GBL001, ETH_DUD_ACT_513_GBL002
** Reference ID          : ETH_DUD_ACT_513_GBL003, ETH_DUD_ACT_513_GBL004
** Reference ID          : ETH_DUD_ACT_513_GBL005, ETH_DUD_ACT_513_GBL006
** Reference ID          : ETH_DUD_ACT_513_REG001, ETH_DUD_ACT_513_REG002
** Reference ID          : ETH_DUD_ACT_513_REG003, ETH_DUD_ACT_513_REG004
** Reference ID          : ETH_DUD_ACT_513_REG005, ETH_DUD_ACT_513_REG006
***********************************************************************************************************************/
STATIC FUNC(void, ETH_PRIVATE_CODE) Eth_HwEnableErrorInterrupt(void)
{
  uint32 LulRegVal;

  #if (ETH_GWCA0_ERR_ISR == STD_ON)
  /* Enable GWCA Error Interrupt */
  LulRegVal = ETH_RSW2_GWCA_DMA_ERROR_MASK | ETH_RSW2_GWCA_ECC_ERROR_MASK;
  #if (ETH_GWCA0_ERR_ISR == STD_ON)
  Eth_GaaRSW2_GWCARegs[ETH_RACE_ID_GWCA0]->ulGWEIE0 |= LulRegVal;                                                       
  #endif
  #endif /* (ETH_GWCA0_ERR_ISR == STD_ON) */

  #if (ETH_COMA_ERR_ISR == STD_ON)
  /* Enable COMA Error Interrupt */
  LulRegVal = ETH_RSW2_COMA_ECC_ERROR_MASK;
  Eth_GpRSW2_COMARegs->ulCAEIE0 |= LulRegVal;
  #endif

  #if ((ETH_ETHA0_ERR_ISR == STD_ON) || (ETH_ETHA1_ERR_ISR == STD_ON))
  /* Enable ETHA Error Interrupt */
  LulRegVal = ETH_RSW2_ETHA_ECC_ERROR_MASK;
  #if (ETH_ETHA0_ERR_ISR == STD_ON)
  Eth_GaaRSW2_ETHARegs[ETH_RACE_ID_ETHA0]->ulEAEIE0 |= LulRegVal;                                                       
  #endif
  #if (ETH_ETHA1_ERR_ISR == STD_ON)
  Eth_GaaRSW2_ETHARegs[ETH_RACE_ID_ETHA1]->ulEAEIE0 |= LulRegVal;
  #endif
  #endif /* ((ETH_ETHA0_ERR_ISR == STD_ON) || (ETH_ETHA1_ERR_ISR == STD_ON)) */
}
#endif /* ((ETH_GWCA_ERR_ISR == STD_ON) || (ETH_COMA_ERR_ISR == STD_ON) || (ETH_ETHA_ERR_ISR == STD_ON)) */

/***********************************************************************************************************************
** Function Name         : Eth_HwTOP_SwitchInitializationFlow (RSW2)
**
** Service ID            : N/A
**
** Description           : TOP Switch Initialization Flow
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
** Return parameter      : E_OK : Success
**                         E_NOT_OK : Failure
**
** Preconditions         : None
**
** Global Variable(s)    : Eth_GaaRsw2PortValid
**
** Function(s) invoked   : COMA_SwitchClockEnableFlow,COMA_BufferPoolnitializationFlow,
**                         MFWD_FullSettingFlow,Eth_HwGWCA_InitializationFlow,
**                         Eth_HwGWCA_ModeTransitionFlow,Eth_HwETHA_InitializationFlow,
**                         Eth_HwETHA_ModeTransitionFlow
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_444
** Reference ID          : ETH_DUD_ACT_444_GBL001
***********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_HwTOP_SwitchInitializationFlow(void)
{
  Std_ReturnType LucResult;
  uint32 LulPortIdx;
  uint32 LulETHAIdx;
  LucResult = E_OK;                                                                                                     /* PRQA S 2982 # JV-01 */

  #if (ETH_SWITCHING_MODE == ETH_SWMODE_ENDSTATION)
  /* Common agent Switch clock enable flow [COMA] */
  COMA_SwitchClockEnableFlow();
  #endif /* ETH_SWITCHING_MODE == ETH_SWMODE_ENDSTATION */

  /* Common agent Buffer pool initialization flow [COMA] */
  LucResult = COMA_BufferPoolnitializationFlow();

  if (E_OK == LucResult)
  {
    /* Forwarding engine Full setting flow [FWD] */
    MFWD_FullSettingFlow();                                                                                             /* PRQA S 3200 # JV-01 */

    /* For all agents,  initialization flow [GWCA] */
    LucResult = Eth_HwGWCA_InitializationFlow(ETH_RSW2_GWCA_ID);
    if (E_OK == LucResult)
    {
      LucResult = Eth_HwGWCA_ModeTransitionFlow(ETH_RSW2_GWCA_ID, ETH_RSW2_GWCA_CONFIG_MODE);
    } /* else No action required */

    /* For all agents,  initialization flow [ETHA] */
    for (LulPortIdx = 0; (LulPortIdx < ETH_RACE_PORT_TSNA_N) && (E_OK == LucResult); LulPortIdx++)
    {
      if (ETH_TRUE == Eth_GaaRsw2PortValid[LulPortIdx])
      {
        LulETHAIdx = ETH_CONV_PORTID_TO_ETHAID(LulPortIdx);                                                             /* PRQA S 3469 # JV-01 */
        LucResult = Eth_HwETHA_InitializationFlow(LulETHAIdx);

        if (E_OK == LucResult)
        {
          LucResult = Eth_HwETHA_ModeTransitionFlow(LulETHAIdx, ETH_RSW2_ETHA_CONFIG_MODE);
        } /* else No action required */
      } /* else No action required */
    }
  } /* else No action required */

  return LucResult;
}

#if (ETH_SWITCHING_MODE == ETH_SWMODE_ENDSTATION)
/***********************************************************************************************************************
** Function Name         : Eth_HwTOP_SwitchResetFlow (RSW2)
**
** Service ID            : N/A
**
** Description           : TOP Switch Initialization Flow
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
** Return parameter      : E_OK : Success
**                         E_NOT_OK : Failure
**
** Preconditions         : None
**
** Global Variable(s)    : None
**
** Function(s) invoked   : Eth_HwGWCA_ModeTransitionFlow,
**                         Eth_HwETHA_ModeTransitionFlow,
**                         COMA_RSwitchResetFlow
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_445
***********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_HwTOP_SwitchResetFlow(void)
{
  Std_ReturnType LucResult;
  uint32 LulGWCAIdx;
  uint32 LulETHAIdx;
  uint32 LulPortIdx;
  LucResult = E_OK;

  /* For all Agents, Mode transition flow to DISABLE */
  for (LulGWCAIdx = 0; (LulGWCAIdx < ETH_RACE_PORT_GWCA_N) && (E_OK == LucResult); LulGWCAIdx++)                        /* PRQA S 2877 # JV-01 */
  {
    LucResult = Eth_HwGWCA_ModeTransitionFlow(LulGWCAIdx, ETH_RSW2_GWCA_DISABLE_MODE);
  }

  for (LulPortIdx = 0; (LulPortIdx < ETH_RACE_PORT_TSNA_N) && (E_OK == LucResult); LulPortIdx++)
  {
    if (ETH_TRUE == Eth_GaaRsw2PortValid[LulPortIdx])
    {
      LulETHAIdx = ETH_CONV_PORTID_TO_ETHAID(LulPortIdx);                                                               /* PRQA S 3469 # JV-01 */
      LucResult = Eth_HwETHA_ModeTransitionFlow(LulETHAIdx, ETH_RSW2_ETHA_DISABLE_MODE);
    }
  }

  /* Common agent R-Switch reset flow */
  if (E_OK == LucResult)
  {
    COMA_RSwitchResetFlow();
  }

  return LucResult;
}
#endif /* (ETH_SWITCHING_MODE == ETH_SWMODE_ENDSTATION) */

/***********************************************************************************************************************
** Function Name         : Eth_HwMFWD_PortISettingFlow (RSW2)
**
** Service ID            : N/A
**
** Description           : MFWD Port i  Setting Flow
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
** Preconditions         : None
**
** Global Variable(s)    : Eth_GaaRsw2PortType, Eth_GpRSW2_MFWDRegs
**
** Function(s) invoked   : None
**
** Registers Used        : FWPC1i
**
** Reference ID          : ETH_DUD_ACT_446
** Reference ID          : ETH_DUD_ACT_446_GBL001, ETH_DUD_ACT_446_GBL002
** Reference ID          : ETH_DUD_ACT_446_GBL003
** Reference ID          : ETH_DUD_ACT_446_REG001, ETH_DUD_ACT_446_REG002
***********************************************************************************************************************/
STATIC FUNC(void, ETH_PRIVATE_CODE) Eth_HwMFWD_PortISettingFlow(
  CONST(uint32, AUTOMATIC) LulPortIdx)
{
  uint32 LulRegVal;

  /* Set FWPC1i */

  /* Set FWPC1i */
  if (ETH_RSW2_PORT_TYPE_GWCA == Eth_GaaRsw2PortType[LulPortIdx])                                                       
  {
    if (ETH_RSW2_GWCA_ID == ETH_CONV_PORTID_TO_GWCAID(LulPortIdx))                                                      /* PRQA S 3383, 3432 # JV-01, JV-01 */
    {
      LulRegVal = Eth_GpRSW2_MFWDRegs->FWPC[LulPortIdx].ulFWPC1i;
      LulRegVal = (LulRegVal & ~ETH_RSW2_MFWD_FWPC1_DDE_DDSL_MASK);
      Eth_GpRSW2_MFWDRegs->FWPC[LulPortIdx].ulFWPC1i =
        (LulRegVal | ETH_RSW2_MFWD_FWPC1_DDE | ETH_RSW2_MFWD_FWPC1_DDSL);
    } /* else No action required */
  } /* else No action required */

  /* Set FWPC2i */
}

#if (ETH_SWITCHING_MODE == ETH_SWMODE_ENDSTATION)
/***********************************************************************************************************************
** Function Name         : Eth_HwMFWD_Layer3TableResetFlow (RSW2)
**
** Service ID            : N/A
**
** Description           : MFWD Layer 3 table reset flow
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
** Return parameter      : E_OK : Success
**                         E_NOT_OK : Failure
**
** Preconditions         : None
**
** Global Variable(s)    : Eth_GpRSW2_MFWDRegs
**
** Function(s) invoked   : GetCounterValue,
**                         Eth_GetElapsedTimeValue
**
** Registers Used        : FWLTHTIM
**
** Reference ID          : ETH_DUD_ACT_447
** Reference ID          : ETH_DUD_ACT_447_GBL001, ETH_DUD_ACT_447_GBL002
** Reference ID          : ETH_DUD_ACT_447_REG001, ETH_DUD_ACT_447_REG002
***********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_HwMFWD_Layer3TableResetFlow(void)
{
  Std_ReturnType LucResult = E_OK;                                                                                      
  TickType LulTickStart;
  TickType LulTickElap;

  /* Set FWLTHTIM.LTHTIOG */
  Eth_GpRSW2_MFWDRegs->ulFWLTHTIM = ETH_RSW2_MFWD_FWLTHTIM_LTHTIOG;

  /* Read FWLTHTIM.LTHTR */
  /* Wait until FWLTHTIM.LTHTR returns to 1 */
  LulTickStart = 0UL;
  LulTickElap = 0UL;
  (void)GetCounterValue(ETH_OS_COUNTER_ID, &LulTickStart);
  do
  {
    LulTickElap = LulTickElap + Eth_GetElapsedTimeValue(&LulTickStart);                                                 /* PRQA S 3383 # JV-01 */
  } while (((Eth_GpRSW2_MFWDRegs->ulFWLTHTIM & ETH_RSW2_MFWD_FWLTHTIM_LTHTR) != ETH_RSW2_MFWD_FWLTHTIM_LTHTR) && 
           (LulTickElap <= ETH_TIMEOUT_COUNT));

  if (ETH_TIMEOUT_COUNT < LulTickElap)
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
** Function Name         : Eth_HwMFWD_MacTableResetFlow (RSW2)
**
** Service ID            : N/A
**
** Description           : MFWD MAC table reset flow
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
** Return parameter      : E_OK : Success
**                         E_NOT_OK : Failure
**
** Preconditions         : None
**
** Global Variable(s)    : Eth_GpRSW2_MFWDRegs
**
** Function(s) invoked   : GetCounterValue,
**                         Eth_GetElapsedTimeValue
**
** Registers Used        : FWMACTIM
**
** Reference ID          : ETH_DUD_ACT_448
** Reference ID          : ETH_DUD_ACT_448_GBL001, ETH_DUD_ACT_448_GBL002
** Reference ID          : ETH_DUD_ACT_448_REG001, ETH_DUD_ACT_448_REG002
***********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_HwMFWD_MacTableResetFlow(void)
{
  Std_ReturnType LucResult = E_OK;                                                                                      
  TickType LulTickStart;
  TickType LulTickElap;

  /* Set FWMACTIM.MACTIOG */
  Eth_GpRSW2_MFWDRegs->ulFWMACTIM = ETH_RSW2_MFWD_FWMACTIM_MACTIOG;

  /* Read FWMACTIM.MACTR */
  /* Wait until FWMACTIM.MACTR returns to 1 */
  LulTickStart = 0UL;
  LulTickElap = 0UL;
  (void)GetCounterValue(ETH_OS_COUNTER_ID, &LulTickStart);
  do
  {
    LulTickElap = LulTickElap + Eth_GetElapsedTimeValue(&LulTickStart);                                                 /* PRQA S 3383 # JV-01 */
  } while (((Eth_GpRSW2_MFWDRegs->ulFWMACTIM & ETH_RSW2_MFWD_FWMACTIM_MACTR) != ETH_RSW2_MFWD_FWMACTIM_MACTR) &&
           (LulTickElap <= ETH_TIMEOUT_COUNT));

  if (ETH_TIMEOUT_COUNT < LulTickElap)
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
** Function Name         : Eth_HwMFWD_VlanTableResetFlow (RSW2)
**
** Service ID            : N/A
**
** Description           : MFWD VLAN table reset flow
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
** Return parameter      : E_OK : Success
**                         E_NOT_OK : Failure
**
** Preconditions         : None
**
** Global Variable(s)    : Eth_GpRSW2_MFWDRegs
**
** Function(s) invoked   : GetCounterValue,
**                         Eth_GetElapsedTimeValue
**
** Registers Used        : FWVLANTIM
**
** Reference ID          : ETH_DUD_ACT_449
** Reference ID          : ETH_DUD_ACT_449_GBL001, ETH_DUD_ACT_449_GBL002
** Reference ID          : ETH_DUD_ACT_449_REG001, ETH_DUD_ACT_449_REG002
***********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_HwMFWD_VlanTableResetFlow(void)
{
  Std_ReturnType LucResult = E_OK;                                                                                      
  TickType LulTickStart;
  TickType LulTickElap;

  /* Set FWVLANTIM.VLANTIOG */
  Eth_GpRSW2_MFWDRegs->ulFWVLANTIM = ETH_RSW2_MFWD_FWVLANTIM_VLANTIOG;

  /* Read FWVLANTIM.VLANTR */
  /* Wait until FWVLANTIM.VLANTR returns to 1 */
  LulTickStart = 0UL;
  LulTickElap = 0UL;
  (void)GetCounterValue(ETH_OS_COUNTER_ID, &LulTickStart);
  do
  {
    LulTickElap = LulTickElap + Eth_GetElapsedTimeValue(&LulTickStart);                                                 /* PRQA S 3383 # JV-01 */
  } while (((Eth_GpRSW2_MFWDRegs->ulFWVLANTIM & ETH_RSW2_MFWD_FWVLANTIM_VLANTR) != ETH_RSW2_MFWD_FWVLANTIM_VLANTR) && 
           (LulTickElap <= ETH_TIMEOUT_COUNT));

  if (ETH_TIMEOUT_COUNT < LulTickElap)
  {
    LucResult = E_NOT_OK;
  }
  else
  {
    LucResult = E_OK;
  }

  return LucResult;
}
#endif /* ETH_SWITCHING_MODE == ETH_SWMODE_ENDSTATION */

/***********************************************************************************************************************
** Function Name         : Eth_HwMFWD_PortIPortBasedSettingFlow (RSW2)
**
** Service ID            : N/A
**
** Description           : MFWD Port i Port Based Setting Flow
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulPortIdx : RSW2 port index
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variable(s)    : Eth_GaaRsw2PortValid, Eth_GaaRsw2PortCtrlIdx,
**                         Eth_GpCtrlConfigPtr, Eth_GpRSW2_MFWDRegs,
**                         Eth_GaaRsw2PortType
**
** Function(s) invoked   : Eth_HwMFWD_PortIPortBasedDisableFlow
**
** Registers Used        : FWPBFCSDCji, FWPBFCi
**
** Reference ID          : ETH_DUD_ACT_450
** Reference ID          : ETH_DUD_ACT_450_GBL001, ETH_DUD_ACT_450_GBL002
** Reference ID          : ETH_DUD_ACT_450_GBL003, ETH_DUD_ACT_450_GBL004
** Reference ID          : ETH_DUD_ACT_450_GBL005, ETH_DUD_ACT_450_GBL006
** Reference ID          : ETH_DUD_ACT_450_GBL008
** Reference ID          : ETH_DUD_ACT_450_REG001, ETH_DUD_ACT_450_REG002
***********************************************************************************************************************/
STATIC FUNC(void, ETH_PRIVATE_CODE) Eth_HwMFWD_PortIPortBasedSettingFlow(
  CONST(uint32, AUTOMATIC) LulPortIdx)
{
  P2CONST(Eth_ETNEConfigType, AUTOMATIC, ETH_APPL_DATA) LpHwUnitConfig;
  P2CONST(uint32, AUTOMATIC, ETH_APPL_DATA) LpCsd;
  uint32 LulRegVal;
  uint32 LulIdx;
  uint32 LulCtrlIdx;
  uint32 LulFwdVectorId;

  LpCsd = NULL_PTR;
  LulFwdVectorId = 0x00000000UL;

  if (ETH_TRUE == Eth_GaaRsw2PortValid[LulPortIdx])                                                                     
  {
    LulCtrlIdx = Eth_GaaRsw2PortCtrlIdx[LulPortIdx];                                                                    
    LpHwUnitConfig = Eth_GpCtrlConfigPtr[LulCtrlIdx].pHwUnitConfig;                                                     /* PRQA S 0317 # JV-01 */
    LpCsd = &LpHwUnitConfig->aaFwdCsd[0];                                                                               
    LulFwdVectorId = LpHwUnitConfig->ulFwdVectorId;
  } /* else No action required */
  /* This function needs to be reexamined when supporting multi-queue */

  /* Port i port-based disable flow*/
  Eth_HwMFWD_PortIPortBasedDisableFlow(LulPortIdx);

  /* Set FWPBFCSDCi Set CPU sub destinations */
  if (NULL_PTR != LpCsd)
  {
    /* Forwarding using FWPBFCSDCi applies */
    for (LulIdx = 0; LulIdx < ETH_RACE_PORT_GWCA_N; LulIdx++)                                                           /* PRQA S 2877 # JV-01 */
    {
      Eth_GpRSW2_MFWDRegs->FWPBF[LulPortIdx].ulFWPBFCSDCji[LulIdx] = LpCsd[LulIdx];                                     
    }
  }/* else No action required */

  /* Set FWPBFCi */
  if (0x00000000UL != LulFwdVectorId)
  {
    LulRegVal = Eth_GpRSW2_MFWDRegs->FWPBF[LulPortIdx].ulFWPBFCi;                                                       
    Eth_GpRSW2_MFWDRegs->FWPBF[LulPortIdx].ulFWPBFCi = LulRegVal | LulFwdVectorId;                                      
  } /* else No action required */
}

/***********************************************************************************************************************
** Function Name         : Eth_HwMFWD_PortIPortBasedDisableFlow (RSW2)
**
** Service ID            : N/A
**
** Description           : MFWD Port l Port Based Disable Flow
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulPortIdx : RSW2 port index
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variable(s)    : Eth_GpRSW2_MFWDRegs
**
** Function(s) invoked   : None
**
** Registers Used        : FWPBFCi
**
** Reference ID          : ETH_DUD_ACT_451
** Reference ID          : ETH_DUD_ACT_451_GBL001
** Reference ID          : ETH_DUD_ACT_451_REG001
***********************************************************************************************************************/
STATIC FUNC(void, ETH_PRIVATE_CODE) Eth_HwMFWD_PortIPortBasedDisableFlow(
  CONST(uint32, AUTOMATIC) LulPortIdx)
{
  uint32 LulRegVal;

  LulRegVal = Eth_GpRSW2_MFWDRegs->FWPBF[LulPortIdx].ulFWPBFCi;                                                         
  Eth_GpRSW2_MFWDRegs->FWPBF[LulPortIdx].ulFWPBFCi = LulRegVal & ~ETH_RACE_PORT_ALL;                                    
}

#if (ETH_SWITCHING_MODE == ETH_SWMODE_ENDSTATION)
/***********************************************************************************************************************
** Function Name         : Eth_HwMFWD_Layer2Layer3UpdateTableResetFlow (RSW2)
**
** Service ID            : N/A
**
** Description           : MFWD Layer 2/Layer 3 update table reset flow
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
** Return parameter      : E_OK : Success
**                         E_NOT_OK : Failure
**
** Preconditions         : None
**
** Global Variable(s)    : Eth_GpRSW2_MFWDRegs
**
** Function(s) invoked   : GetCounterValue,
**                         Eth_GetElapsedTimeValue
**
** Registers Used        : FWL23UTIM
**
** Reference ID          : ETH_DUD_ACT_452
** Reference ID          : ETH_DUD_ACT_452_GBL001, ETH_DUD_ACT_452_GBL002
** Reference ID          : ETH_DUD_ACT_452_REG001, ETH_DUD_ACT_452_REG002
***********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_HwMFWD_Layer2Layer3UpdateTableResetFlow(void)
{
  Std_ReturnType LucResult = E_OK;                                                                                      
  TickType LulTickStart;
  TickType LulTickElap;

  /* Set FWL23UTIM.L23UTIOG */
  Eth_GpRSW2_MFWDRegs->ulFWL23UTIM = ETH_RSW2_MFWD_FWL23UTIM_L23UTIOG;

  /* Read FWL23UTIM.L23UTR */
  /* Wait until FWL23UTIM.L23UTR returns to 1 */
  LulTickStart = 0UL;
  LulTickElap = 0UL;
  (void)GetCounterValue(ETH_OS_COUNTER_ID, &LulTickStart);
  do
  {
    LulTickElap = LulTickElap + Eth_GetElapsedTimeValue(&LulTickStart);                                                 /* PRQA S 3383 # JV-01 */
  } while (((Eth_GpRSW2_MFWDRegs->ulFWL23UTIM & ETH_RSW2_MFWD_FWL23UTIM_L23UTR) != ETH_RSW2_MFWD_FWL23UTIM_L23UTR) && 
           (LulTickElap <= ETH_TIMEOUT_COUNT));

  if (ETH_TIMEOUT_COUNT < LulTickElap)
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
** Function Name         : Eth_HwMFWD_GateRamResetFlow (RSW2)
**
** Service ID            : N/A
**
** Description           : MFWD Gate Ram Reset Flow
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
** Return parameter      : E_OK : Success
**                         E_NOT_OK : Failure
**
** Preconditions         : None
**
** Global Variable(s)    : Eth_GpRSW2_MFWDRegs
**
** Function(s) invoked   : Eth_GetElapsedTimeValue,
**                         GetCounterValue
**
** Registers Used        : FWPGFRIM
**
** Reference ID          : ETH_DUD_ACT_453
** Reference ID          : ETH_DUD_ACT_453_GBL001, ETH_DUD_ACT_453_GBL002
** Reference ID          : ETH_DUD_ACT_453_REG001, ETH_DUD_ACT_453_REG002
***********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_HwMFWD_GateRamResetFlow(void)
{
  Std_ReturnType LucResult = E_OK;                                                                                      

  return LucResult;
}
#endif /* ETH_SWITCHING_MODE == ETH_SWMODE_ENDSTATION */

/***********************************************************************************************************************
** Function Name         : Eth_HwGWCA_ModeTransitionFlow (RSW2)
**
** Service ID            : N/A
**
** Description           : GWCA Mode Transition Flow
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulGWCAIdx : GWCA index
**                         LenMode    : new mode
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
** Global Variable(s)    : Eth_GaaRSW2_GWCARegs
**
** Function(s) invoked   : GetCounterValue,
**                         Eth_GetElapsedTimeValue,
**                         COMA_AgentIClockStatusCheckFlow,
**                         COMA_AgentIClockEnableFlow,
**                         COMA_AgentIClockDisableFlow
**
** Registers Used        : GWMC, GWMS
**
** Reference ID          : ETH_DUD_ACT_454
** Reference ID          : ETH_DUD_ACT_454_GBL001, ETH_DUD_ACT_454_GBL002
** Reference ID          : ETH_DUD_ACT_454_REG001, ETH_DUD_ACT_454_REG002
***********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_HwGWCA_ModeTransitionFlow(
  CONST(uint32, AUTOMATIC) LulGWCAIdx,
  CONST(uint32, AUTOMATIC) LenMode)
{
  Std_ReturnType LucResult = E_OK;                                                                                      
  boolean LblClockEnabled;
  TickType LulTickStart;
  TickType LulTickElap;

  /* Agent i clock status check */
  LblClockEnabled = COMA_AgentIClockStatusCheckFlow(ETH_CONV_GWCAID_TO_PORTID(LulGWCAIdx));                             /* PRQA S 3383, 3432 # JV-01, JV-01 */

  /* TSNA clock enabled? */
  if (ETH_FALSE == LblClockEnabled)
  {
    /* Agent i clock enable flow */
    COMA_AgentIClockEnableFlow(ETH_CONV_GWCAID_TO_PORTID(LulGWCAIdx));                                                  /* PRQA S 3383, 3432 # JV-01, JV-01 */
  }
  /* Set GWMC.OPC */
  Eth_GaaRSW2_GWCARegs[LulGWCAIdx]->ulGWMC = LenMode;                                                                   

  /* Read GWMS.OPS */
  /* Wait until GWMS.OPS returns to "new mode" */
  LulTickStart = 0UL;
  LulTickElap = 0UL;
  (void)GetCounterValue(ETH_OS_COUNTER_ID, &LulTickStart);
  do
  {
    LulTickElap = LulTickElap + Eth_GetElapsedTimeValue(&LulTickStart);                                                 /* PRQA S 3383 # JV-01 */
  } while (((Eth_GaaRSW2_GWCARegs[LulGWCAIdx]->ulGWMS & ETH_RSW2_GWCA_GWMS_OPS_MASK) != LenMode) &&
           (LulTickElap <= ETH_TIMEOUT_COUNT));

  if (ETH_TIMEOUT_COUNT < LulTickElap)
  {
    LucResult = E_NOT_OK;
  }
  else
  {
    LucResult = E_OK;
  }

  /* Next_mode = DISABLE? */
  if (ETH_RSW2_GWCA_DISABLE_MODE == LenMode)
  {
    /* Agent i clock disable flow [COMA] */
    COMA_AgentIClockDisableFlow(ETH_CONV_GWCAID_TO_PORTID(LulGWCAIdx));                                                 /* PRQA S 3383, 3432 # JV-01, JV-01 */
  }
  return LucResult;
}

/***********************************************************************************************************************
** Function Name         : Eth_HwGWCA_InitializationFlow (RSW2)
**
** Service ID            : N/A
**
** Description           : GWCA Initialization Flow
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulGWCAIdx : GWCA index
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
** Function(s) invoked   : Eth_HwGWCA_ModeTransitionFlow
**                         GWCA_FullSettingFlow
**                         Eth_HwGWCA_MulticastTableResetFlow
**                         Eth_HwGWCA_AxiRamResetFlow
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_455
***********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_HwGWCA_InitializationFlow(
  CONST(uint32, AUTOMATIC) LulGWCAIdx)
{
  Std_ReturnType LucResult;

  /* Mode transition flow to DISABLE mode */
  LucResult = Eth_HwGWCA_ModeTransitionFlow(LulGWCAIdx, ETH_RSW2_GWCA_DISABLE_MODE);

  if (E_OK == LucResult)
  {
    /* Mode transition flow to CONFIG mode */
    LucResult = Eth_HwGWCA_ModeTransitionFlow(LulGWCAIdx, ETH_RSW2_GWCA_CONFIG_MODE);

    if (E_OK == LucResult)
    {
      /* Multicast table reset flow */
      LucResult = Eth_HwGWCA_MulticastTableResetFlow(LulGWCAIdx);
      /* AXI RAM reset flow */
      if (E_OK == LucResult)
      {
        LucResult = Eth_HwGWCA_AxiRamResetFlow(LulGWCAIdx);
        if (E_OK == LucResult)
        {
          /* Full setting flow */
          LucResult = GWCA_FullSettingFlow(LulGWCAIdx);
          if (E_OK == LucResult)
          {
            /* Mode transition flow to DISABLE mode */
            LucResult = Eth_HwGWCA_ModeTransitionFlow(LulGWCAIdx, ETH_RSW2_GWCA_DISABLE_MODE);
          } /* else No action required */
        } /* else No action required */
      } /* else No action required */
    } /* else No action required */
  } /* else No action required */

  return LucResult;
}

/***********************************************************************************************************************
** Function Name         : Eth_HwGWCA_MulticastTableResetFlow (RSW2)
**
** Service ID            : N/A
**
** Description           : GWCA Multicast Table Reset Flow
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulGWCAIdx : GWCA index
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
** Global Variable(s)    : Eth_GaaRSW2_GWCARegs
**
** Function(s) invoked   : GetCounterValue,
**                         Eth_GetElapsedTimeValue
**
** Registers Used        : GWMTIRM
**
** Reference ID          : ETH_DUD_ACT_456
** Reference ID          : ETH_DUD_ACT_456_GBL001, ETH_DUD_ACT_456_GBL002
** Reference ID          : ETH_DUD_ACT_456_REG001, ETH_DUD_ACT_456_REG002
***********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_HwGWCA_MulticastTableResetFlow(
  CONST(uint32, AUTOMATIC) LulGWCAIdx)
{
  Std_ReturnType LucResult = E_OK;                                                                                      
  TickType LulTickStart;
  TickType LulTickElap;

  /* GWMTIRM.MTIOG Set */
  Eth_GaaRSW2_GWCARegs[LulGWCAIdx]->ulGWMTIRM = ETH_RSW2_GWCA_GWMTIRM_MTIOG;                                            

  /* Read GWMTIRM.MTR */
  /* Wait until GWMTIRM.MTR returns to 1 */
  LulTickStart = 0UL;
  LulTickElap = 0UL;
  (void)GetCounterValue(ETH_OS_COUNTER_ID, &LulTickStart);
  do
  {
    LulTickElap = LulTickElap + Eth_GetElapsedTimeValue(&LulTickStart);                                                 /* PRQA S 3383 # JV-01 */
  } while (((Eth_GaaRSW2_GWCARegs[LulGWCAIdx]->ulGWMTIRM & ETH_RSW2_GWCA_GWMTIRM_MTR) != ETH_RSW2_GWCA_GWMTIRM_MTR) &&
           (LulTickElap <= ETH_TIMEOUT_COUNT));

  if (ETH_TIMEOUT_COUNT < LulTickElap)
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
** Function Name         : Eth_HwGWCA_AxiRamResetFlow (RSW2)
**
** Service ID            : N/A
**
** Description           : GWCA AXI RAM reset Flow
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulGWCAIdx : GWCA index
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
** Global Variable(s)    : Eth_GaaRSW2_GWCARegs
**
** Function(s) invoked   : GetCounterValue,
**                         Eth_GetElapsedTimeValue
**
** Registers Used        : GWARIRM
**
** Reference ID          : ETH_DUD_ACT_457
** Reference ID          : ETH_DUD_ACT_457_GBL001, ETH_DUD_ACT_457_GBL002
** Reference ID          : ETH_DUD_ACT_457_REG001, ETH_DUD_ACT_457_REG002
***********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_HwGWCA_AxiRamResetFlow(
  CONST(uint32, AUTOMATIC) LulGWCAIdx)
{
  Std_ReturnType LucResult = E_OK;                                                                                      
  TickType LulTickStart;
  TickType LulTickElap;

  /* GWARIRM.ARIOG Set */
  Eth_GaaRSW2_GWCARegs[LulGWCAIdx]->ulGWARIRM = ETH_RSW2_GWCA_GWARIRM_ARIOG;                                            

  /* Read GWARIRM.ARR */
  /* Wait until GWARIRM.ARR returns to 1 */
  LulTickStart = 0UL;
  LulTickElap = 0UL;
  (void)GetCounterValue(ETH_OS_COUNTER_ID, &LulTickStart);
  do
  {
    LulTickElap = LulTickElap + Eth_GetElapsedTimeValue(&LulTickStart);                                                 /* PRQA S 3383 # JV-01 */
  } while (((Eth_GaaRSW2_GWCARegs[LulGWCAIdx]->ulGWARIRM & ETH_RSW2_GWCA_GWARIRM_ARR) != ETH_RSW2_GWCA_GWARIRM_ARR) &&
           (LulTickElap <= ETH_TIMEOUT_COUNT));

  if (ETH_TIMEOUT_COUNT < LulTickElap)
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
** Function Name         : Eth_HwETHA_ModeTransitionFlow (RSW2)
**
** Service ID            : N/A
**
** Description           : ETHA Mode Transition Flow
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulETHAIdx : ETHA index
**                         LenMode    : new mode
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
** Global Variable(s)    : Eth_GaaRSW2_ETHARegs
**
** Function(s) invoked   : GetCounterValue,
**                         Eth_GetElapsedTimeValue,
**                         COMA_AgentIClockStatusCheckFlow,
**                         COMA_AgentIClockEnableFlow,
**                         COMA_AgentIClockDisableFlow
**
** Registers Used        : EAMC, EAMS
**
** Reference ID          : ETH_DUD_ACT_458
** Reference ID          : ETH_DUD_ACT_458_GBL001, ETH_DUD_ACT_458_GBL002
** Reference ID          : ETH_DUD_ACT_458_REG001, ETH_DUD_ACT_458_REG002
***********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_HwETHA_ModeTransitionFlow(
  CONST(uint32, AUTOMATIC) LulETHAIdx,
  CONST(uint32, AUTOMATIC) LenMode)
{
  Std_ReturnType LucResult = E_OK;                                                                                      
  boolean LblClockEnabled;
  TickType LulTickStart;
  TickType LulTickElap;

  /* Agent i clock status check [COMA] */
  LblClockEnabled = COMA_AgentIClockStatusCheckFlow(ETH_CONV_ETHAID_TO_PORTID(LulETHAIdx));                             /* PRQA S 3469 # JV-01 */

  /* TSNA clock enabled? */
  if (ETH_FALSE == LblClockEnabled)
  {
    /* Agent i clock enable flow [COMA] */
    COMA_AgentIClockEnableFlow(ETH_CONV_ETHAID_TO_PORTID(LulETHAIdx));                                                  /* PRQA S 3469 # JV-01 */
  }

  /* Set EAMC.OPC */
  Eth_GaaRSW2_ETHARegs[LulETHAIdx]->ulEAMC = LenMode;                                                                   

  /* Read EAMS.OPS */
  /* Wait until EAMS.OPS is "new mode" */
  LulTickStart = 0UL;
  LulTickElap = 0UL;
  (void)GetCounterValue(ETH_OS_COUNTER_ID, &LulTickStart);
  do
  {
    LulTickElap = LulTickElap + Eth_GetElapsedTimeValue(&LulTickStart);                                                 /* PRQA S 3383 # JV-01 */
  } while (((Eth_GaaRSW2_ETHARegs[LulETHAIdx]->ulEAMS & ETH_RSW2_ETHA_EAMS_OPS_MASK) != LenMode) && 
           (LulTickElap <= ETH_TIMEOUT_COUNT));

  if (ETH_TIMEOUT_COUNT < LulTickElap)
  {
    LucResult = E_NOT_OK;
  }
  else
  {
    LucResult = E_OK;
  }

  /* Next_mode = DISABLE? */
  if (ETH_RSW2_ETHA_DISABLE_MODE == LenMode)
  {
    /* Agent i clock disable flow [COMA] */
    COMA_AgentIClockDisableFlow(ETH_CONV_ETHAID_TO_PORTID(LulETHAIdx));                                                 /* PRQA S 3469 # JV-01 */
  }

  return LucResult;
}

/***********************************************************************************************************************
** Function Name         : Eth_HwETHA_InitializationFlow (RSW2)
**
** Service ID            : N/A
**
** Description           : ETHA Initialization Flow
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulETHAIdx : ETHA index
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
** Function(s) invoked   : Eth_HwETHA_ModeTransitionFlow
**                         ETHA_FullSettingFlow
**                         RMAC_InitializationFlow
**                         Eth_HwETHA_TasRamResetFlow
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_459
***********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_HwETHA_InitializationFlow(
  CONST(uint32, AUTOMATIC) LulETHAIdx)
{
  Std_ReturnType LucResult;

  /* Mode transition flow to DISABLE mode */
  LucResult = Eth_HwETHA_ModeTransitionFlow(LulETHAIdx, ETH_RSW2_ETHA_DISABLE_MODE);

  if (E_OK == LucResult)
  {
    /* Mode transition flow to CONFIG mode */
    LucResult = Eth_HwETHA_ModeTransitionFlow(LulETHAIdx, ETH_RSW2_ETHA_CONFIG_MODE);

    if (E_OK == LucResult)
    {
      /* TAS RAM reset flow */
      LucResult = Eth_HwETHA_TasRamResetFlow(LulETHAIdx);
      if (E_OK == LucResult)
      {
        /* Full setting flow */
        ETHA_FullSettingFlow(LulETHAIdx);

        /* Figure 28.88 Initialization flow */
        LucResult = RMAC_InitializationFlow(LulETHAIdx);

        if (E_OK == LucResult)
        {
          /* Mode transition flow to DISABLE mode */
          LucResult = Eth_HwETHA_ModeTransitionFlow(LulETHAIdx, ETH_RSW2_ETHA_DISABLE_MODE);
        } /* else: No action required */
      } /* else No action required */
    } /* else No action required */
  } /* else No action required */

  return LucResult;
}

/***********************************************************************************************************************
** Function Name         : Eth_HwETHA_TasRamResetFlow (RSW2)
**
** Service ID            : N/A
**
** Description           : ETHA TAS RAM reset Flow
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulETHAIdx : ETHA index
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
** Global Variable(s)    : Eth_GaaRSW2_ETHARegs
**
** Function(s) invoked   : GetCounterValue,
**                         Eth_GetElapsedTimeValue
**
** Registers Used        : EATASRIRM
**
** Reference ID          : ETH_DUD_ACT_460
** Reference ID          : ETH_DUD_ACT_460_GBL001, ETH_DUD_ACT_460_GBL002
** Reference ID          : ETH_DUD_ACT_460_REG001, ETH_DUD_ACT_460_REG002
***********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_HwETHA_TasRamResetFlow(
  CONST(uint32, AUTOMATIC) LulETHAIdx)
{
  Std_ReturnType LucResult = E_OK;                                                                                      
  TickType LulTickStart;
  TickType LulTickElap;

  /* EATASRIRM.TASRIOG Set */
  Eth_GaaRSW2_ETHARegs[LulETHAIdx]->ulEATASRIRM = ETH_RSW2_ETHA_TASRIRM_TASRIOG;                                        

  /* Read EATASRIRM.TASRR */
  /* Wait until EATASRIRM.TASRR returns to 1 */
  LulTickStart = 0UL;
  LulTickElap = 0UL;
  (void)GetCounterValue(ETH_OS_COUNTER_ID, &LulTickStart);
  do
  {
    LulTickElap = LulTickElap + Eth_GetElapsedTimeValue(&LulTickStart);                                                 /* PRQA S 3383 # JV-01 */
  } while 
  (((Eth_GaaRSW2_ETHARegs[LulETHAIdx]->ulEATASRIRM & ETH_RSW2_ETHA_TASRIRM_TASRR) != ETH_RSW2_ETHA_TASRIRM_TASRR) && 
  (LulTickElap <= ETH_TIMEOUT_COUNT));

  if (ETH_TIMEOUT_COUNT < LulTickElap)
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
** Function Name         : Eth_HwETHA_CbsQSettingFlow (RSW2)
**
** Service ID            : N/A
**
** Description           : CBS q setting flow
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulETHAIdx : ETHA index
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variable(s)    : Eth_GpCtrlConfigPtr, Eth_GaaRSW2_ETHARegs
**                       : Eth_GaaRsw2PortCtrlIdx
**
** Function(s) invoked   : None
**
** Registers Used        : EACAIVCq, EACAULCq, EACAEC, EACC
**
** Reference ID          : ETH_DUD_ACT_517
** Reference ID          : ETH_DUD_ACT_517_GBL001, ETH_DUD_ACT_517_GBL002
** Reference ID          : ETH_DUD_ACT_517_GBL003, ETH_DUD_ACT_517_GBL004
** Reference ID          : ETH_DUD_ACT_517_GBL005, ETH_DUD_ACT_517_GBL006
** Reference ID          : ETH_DUD_ACT_517_REG001, ETH_DUD_ACT_517_REG002
** Reference ID          : ETH_DUD_ACT_517_REG003, ETH_DUD_ACT_517_REG004
***********************************************************************************************************************/
STATIC FUNC(void, ETH_PRIVATE_CODE) Eth_HwETHA_CbsQSettingFlow (
  CONST(uint32, AUTOMATIC) LulETHAIdx)
{
  P2CONST(Eth_ETNEConfigType, AUTOMATIC, ETH_APPL_DATA) LpHwUnitConfig;
  uint32 LulCnt;
  uint32 LulCtrlIdx;

  LulCtrlIdx = Eth_GaaRsw2PortCtrlIdx[ETH_CONV_ETHAID_TO_PORTID(LulETHAIdx)];                                           /* PRQA S 3469 # JV-01 */

  LpHwUnitConfig =
    (P2CONST(Eth_ETNEConfigType, AUTOMATIC, ETH_APPL_DATA))Eth_GpCtrlConfigPtr[LulCtrlIdx].pHwUnitConfig;               /* PRQA S 0316 # JV-01 */

  for (LulCnt = 0UL; LulCnt < (uint32)LpHwUnitConfig->stQueueConfig.ucNumberOfTxQueue; LulCnt++)                        
  {
    Eth_GaaRSW2_ETHARegs[LulETHAIdx]->ulEACAIVCq[LulCnt] =                                                              
      LpHwUnitConfig->stQueueConfig.pTxQueueConfig[LulCnt].stCBSConfig.ulCIV;                                           
    Eth_GaaRSW2_ETHARegs[LulETHAIdx]->ulEACAULCq[LulCnt] = 
      LpHwUnitConfig->stQueueConfig.pTxQueueConfig[LulCnt].stCBSConfig.ulCUL;
    Eth_GaaRSW2_ETHARegs[LulETHAIdx]->ulEACAEC |=
      LpHwUnitConfig->stQueueConfig.pTxQueueConfig[LulCnt].stCBSConfig.ulCE << LulCnt;
    Eth_GaaRSW2_ETHARegs[LulETHAIdx]->ulEACC |= 1UL << LulCnt;
  }
}

#if (ETH_GLOBAL_TIME_SUPPORT == STD_ON)
/***********************************************************************************************************************
** Function Name         : Eth_HwETHA_TasSettingFlow (RSW2)
**
** Service ID            : N/A
**
** Description           : TAS setting flow
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulETHAIdx : ETHA index
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variable(s)    : Eth_GpCtrlConfigPtr, Eth_GaaRSW2_ETHARegs,
**                         Eth_GpRSW2_GPTPRegs
**
** Function(s) invoked   : Eth_TASEntryLearnFlow,GetCounterValue
**                         Eth_HwGPTP_Avtp64TimerTReadingFlow
**                         Eth_GetElapsedTimeValue
**
** Registers Used        : EATASC, EATASENCi, 
**                         EATASCSTC0, EATASCSTC1, EATASCTC
**
** Reference ID          :  ETH_DUD_ACT_522
** Reference ID          :  ETH_DUD_ACT_522_REG001,ETH_DUD_ACT_522_REG002
** Reference ID          :  ETH_DUD_ACT_522_REG003,ETH_DUD_ACT_522_REG004
** Reference ID          :  ETH_DUD_ACT_522_REG005,ETH_DUD_ACT_522_REG006
** Reference ID          :  ETH_DUD_ACT_522_REG007,ETH_DUD_ACT_522_REG008
** Reference ID          :  ETH_DUD_ACT_522_REG009
** Reference ID          :  ETH_DUD_ACT_522_GBL001,ETH_DUD_ACT_522_GBL002
** Reference ID          :  ETH_DUD_ACT_522_GBL003,ETH_DUD_ACT_522_GBL004
** Reference ID          :  ETH_DUD_ACT_522_GBL005
***********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_HwETHA_TasSettingFlow(
  CONST(uint32, AUTOMATIC) LulETHAIdx)
{
  P2CONST(Eth_ETNEConfigType, AUTOMATIC, ETH_APPL_DATA) LpHwUnitConfig;
  uint64 LulCycleStartTime;
  TickType LulTickStart;
  TickType LulTickElap;
  uint32 LulSaveTasConfigAddr;
  uint32 LulTasTableIdx;
  uint32 LulQIdx;
  uint32 LulAVTP_Upper;
  uint32 LulAVTP_Downer;
  uint32 LulETHARegsTmp;
  uint32 LulCtrlIdx;
  Std_ReturnType LucResult;

  LulTickStart = 0UL;
  LulAVTP_Upper = 0UL;
  LulAVTP_Downer = 0UL;
  LulTickElap = 0UL;

  /* Read TAS status */
  (void)GetCounterValue(ETH_OS_COUNTER_ID, &LulTickStart);
  do
  {
    LulTickElap = LulTickElap + Eth_GetElapsedTimeValue(&LulTickStart);                                                 /* PRQA S 3383 # JV-01 */
  } while (((Eth_GaaRSW2_ETHARegs[LulETHAIdx]->ulEATASC & ETH_RSW2_ETHA_EATASC_TASCI) == ETH_RSW2_ETHA_EATASC_TASCI) && 
           (LulTickElap <= ETH_TIMEOUT_COUNT));

  if (ETH_TIMEOUT_COUNT < LulTickElap)
  {
    LucResult = E_NOT_OK;
  }
  else
  {
    LucResult = E_OK;
    /*Save TAS config address in i variable*/
    LulSaveTasConfigAddr = ((Eth_GaaRSW2_ETHARegs[LulETHAIdx]->ulEATASC & ETH_RSW2_ETHA_EATASC_TASCA) >> 16UL );
    /* Set gate entry numbers */
    LulCtrlIdx = Eth_GaaRsw2PortCtrlIdx[ETH_CONV_ETHAID_TO_PORTID(LulETHAIdx)];                                         /* PRQA S 3469 # JV-01 */

    LpHwUnitConfig =
      (P2CONST(Eth_ETNEConfigType, AUTOMATIC, ETH_APPL_DATA))Eth_GpCtrlConfigPtr[LulCtrlIdx].pHwUnitConfig;             /* PRQA S 0316 # JV-01 */
    for (LulQIdx = 0UL; LulQIdx < (uint32)LpHwUnitConfig->stQueueConfig.ucNumberOfTxQueue; LulQIdx++)                   
    {
      if (LpHwUnitConfig->stTASConfig.aaEntryNumber[LulQIdx] != 0UL)                                                    
      {
        Eth_GaaRSW2_ETHARegs[LulETHAIdx]->ulEATASENCi[LulQIdx] = 
          (uint32)(LpHwUnitConfig->stTASConfig.aaEntryNumber[LulQIdx] - 1UL);
      }
      else
      {
        /* No action required */
      }
    }

    /* Set cycle start time */
    Eth_HwGPTP_Avtp64TimerTReadingFlow(ETH_AVTP_TIMER_DOMAIN, &LulAVTP_Upper, &LulAVTP_Downer);

    LulCycleStartTime = ((((uint64)LulAVTP_Upper << ETH_RSW2_64_TO_32_SHIFT) | (uint64)LulAVTP_Downer) +                /* PRQA S 3383 # JV-01 */
                         ETH_RSW2_SETCYCLE_START)  - (uint64)(LpHwUnitConfig->stTASConfig.ulTxMiniLatency);             /* PRQA S 3384 # JV-01 */

    Eth_GaaRSW2_ETHARegs[LulETHAIdx]->ulEATASCSTC0 = (uint32)(LulCycleStartTime & ETH_RSW2_64_TO_32_LOW);

    Eth_GaaRSW2_ETHARegs[LulETHAIdx]->ulEATASCSTC1 = (uint32)((LulCycleStartTime & ETH_RSW2_64_TO_32_HIGH) >> 
                                                              ETH_RSW2_64_TO_32_SHIFT);

    /* ulCycleTime will be the same for all Queue, so enter the value for the first Queue. */
    LulQIdx = 0UL;
    /* Set cycle time */
    Eth_GaaRSW2_ETHARegs[LulETHAIdx]->ulEATASCTC = LpHwUnitConfig->stQueueConfig.pTxQueueConfig[LulQIdx].ulCycleTime;   
    for (LulTasTableIdx = 0; LulTasTableIdx < (uint32)LpHwUnitConfig->stTASConfig.ulNumberOfTasTable; LulTasTableIdx++)
    {
      LucResult = Eth_HwETHA_TasEntryILearnFlow(LulETHAIdx,
                                                LulSaveTasConfigAddr,
                                                LpHwUnitConfig->stTASConfig.pTasTable + LulTasTableIdx);                /* PRQA S 0488 # JV-01 */
      if (E_OK == LucResult)
      {
        LulSaveTasConfigAddr = LulSaveTasConfigAddr + 1UL;                                                              /* PRQA S 3383 # JV-01 */
      }
      else
      {
        break;
      }
    }

    if (E_OK == LucResult)
    {
      /* EATASC.TASE == 1'b1? */
      /* Note */
      /* - The TSNA hardware manual has specifications for both cases where TASE is 1 and 0, */
      /* - but MCAL's operational case is only for TASE 0. */
      /* - Therefore, only the case where TASE is 0 is implemented. */
      if (ETH_RSW2_ETHA_EATASC_TASE != (ETH_RSW2_ETHA_EATASC_TASE & Eth_GaaRSW2_ETHARegs[LulETHAIdx]->ulEATASC))
      {
        /*Set EATASC register with TASE to 1'b1 and TASCC to 1'b0*/
        LulETHARegsTmp = Eth_GaaRSW2_ETHARegs[LulETHAIdx]->ulEATASC;
        LulETHARegsTmp |= ETH_RSW2_ETHA_EATASC_TASE;
        LulETHARegsTmp &= ~ETH_RSW2_ETHA_EATASC_TASCC;
        Eth_GaaRSW2_ETHARegs[LulETHAIdx]->ulEATASC = LulETHARegsTmp;
      }
      else
      {
        /* No action required */
      }
    }
  }
  
  return LucResult;
}

/***********************************************************************************************************************
** Function Name         : Eth_HwETHA_TasDisablingFlow (RSW2)
**
** Service ID            : N/A
**
** Description           : TAS disabling flow
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulETHAIdx : ETHA index
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variable(s)    : Eth_GaaRSW2_ETHARegs
**
** Function(s) invoked   : GetCounterValue, Eth_GetElapsedTimeValue
**
** Registers Used        : EATASC
**
** Reference ID          : ETH_DUD_ACT_518
** Reference ID          : ETH_DUD_ACT_518_REG001,ETH_DUD_ACT_518_REG002
***********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_HwETHA_TasDisablingFlow(
  CONST(uint32, AUTOMATIC) LulETHAIdx)
{
  TickType LulTickStart;
  TickType LulTickElap;
  Std_ReturnType LucResult;
  /* Read TAS status */
  LulTickStart = 0UL;
  LulTickElap = 0UL;
  (void)GetCounterValue(ETH_OS_COUNTER_ID, &LulTickStart);
  do
  {
    LulTickElap = LulTickElap + Eth_GetElapsedTimeValue(&LulTickStart);                                                 /* PRQA S 3383 # JV-01 */
  } while (((Eth_GaaRSW2_ETHARegs[LulETHAIdx]->ulEATASC & ETH_RSW2_ETHA_EATASC_TASCI) == ETH_RSW2_ETHA_EATASC_TASCI) && 
           (LulTickElap <= ETH_TIMEOUT_COUNT));
  if (ETH_TIMEOUT_COUNT < LulTickElap)
  {
    LucResult = E_NOT_OK;
  }
  else
  {
    LucResult = E_OK;
    /*Set EATASC register with TASE to 1'b0 and TASCC to 1'b0*/
    Eth_GaaRSW2_ETHARegs[LulETHAIdx]->ulEATASC &= ~(ETH_RSW2_ETHA_EATASC_TASE | ETH_RSW2_ETHA_EATASC_TASCC);
  }

  return LucResult;
}

/***********************************************************************************************************************
** Function Name         : Eth_HwETHA_TasEnablingFlow (RSW2)
**
** Service ID            : N/A
**
** Description           : TAS enabling flow
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulETHAIdx : ETHA index
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variable(s)    : Eth_GaaRSW2_ETHARegs
**
** Function(s) invoked   : None
**
** Registers Used        : EATASC
**
** Reference ID          : ETH_DUD_ACT_519
** Reference ID          : ETH_DUD_ACT_519_REG001,ETH_DUD_ACT_519_REG002
***********************************************************************************************************************/
STATIC FUNC(void, ETH_PRIVATE_CODE) Eth_HwETHA_TasEnablingFlow(
  CONST(uint32, AUTOMATIC) LulETHAIdx)
{
  uint32 LulETHARegsTmp;
  LulETHARegsTmp = Eth_GaaRSW2_ETHARegs[LulETHAIdx]->ulEATASC;                                                          
  LulETHARegsTmp |= ETH_RSW2_ETHA_EATASC_TASE;
  LulETHARegsTmp &= ~ETH_RSW2_ETHA_EATASC_TASCC;

  Eth_GaaRSW2_ETHARegs[LulETHAIdx]->ulEATASC = LulETHARegsTmp;

}

/***********************************************************************************************************************
** Function Name         : Eth_HwETHA_TasEntryILearnFlow (RSW2)
**
** Service ID            : N/A
**
** Description           : The TAS entry i learn flow
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulETHAIdx : ETHA index
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variable(s)    : Eth_GaaRSW2_ETHARegs
**
** Function(s) invoked   : GetCounterValue,Eth_GetElapsedTimeValue
**
** Registers Used        : EATASGL0, EATASGL1, EATASGLR
**
** Reference ID          : ETH_DUD_ACT_520
** Reference ID          : ETH_DUD_ACT_520_REG001,ETH_DUD_ACT_520_REG002
** Reference ID          : ETH_DUD_ACT_520_GBL001
***********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_HwETHA_TasEntryILearnFlow(
  CONST(uint32, AUTOMATIC) LulETHAIdx,
  CONST(uint32, AUTOMATIC) LulSaveTasConfigAddr,
  CONSTP2CONST(Eth_TASEntryType, AUTOMATIC, ETH_APPL_DATA) LpCtrlConfig)
{
  TickType LulTickStart;
  TickType LulTickElap;
  Std_ReturnType LucResult;
  /* Set address to be learnt to i */
  Eth_GaaRSW2_ETHARegs[LulETHAIdx]->ulEATASGL0 = LulSaveTasConfigAddr;                                                  

  /* Set entry to be learnt */
  Eth_GaaRSW2_ETHARegs[LulETHAIdx]->ulEATASGL1 =
    (((uint32)LpCtrlConfig->enGateState << 28UL) | LpCtrlConfig->ulTimeInterval);                                       

  /* Read Ethernet Agent TAS Gate Learn Result */
  LulTickStart = 0UL;
  LulTickElap = 0UL;
  (void)GetCounterValue(ETH_OS_COUNTER_ID, &LulTickStart);
  do
  {
    LulTickElap = LulTickElap + Eth_GetElapsedTimeValue(&LulTickStart);                                                 /* PRQA S 3383 # JV-01 */
  } while (((Eth_GaaRSW2_ETHARegs[LulETHAIdx]->ulEATASGLR & ETH_RSW2_ETHA_EATASGLR_GL) == ETH_RSW2_ETHA_EATASGLR_GL) && 
           (LulTickElap <= ETH_TIMEOUT_COUNT));

  if (ETH_TIMEOUT_COUNT < LulTickElap)
  {
    LucResult = E_NOT_OK;
  }
  else
  {
    LucResult = E_OK;
  }

  return LucResult;
}
#endif  /* (ETH_GLOBAL_TIME_SUPPORT == STD_ON) */
#if (ETH_CTRL_ENABLE_MII == STD_ON)

/***********************************************************************************************************************
** Function Name         : Eth_HwRMAC_PhyMdioWriteAccessFlow (RSW2)
**
** Service ID            : N/A
**
** Description           : Write data from the PHY management interface
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : LulRMACIdx : Index of a RMAC
**                         LucTrcvIdx : Index of the transceiver on the MII
**                         LucRegIdx  : Index of the transceiver register on the MII
**                         LusWriteVal: Value to be written into the indexed register
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : LusRetData (Read data from PHY)
**
** Preconditions         : (ETH_CTRL_ENABLE_MII == STD_ON)
**
** Global Variable(s)    : Eth_GaaRSW2_RMACRegs
**
** Function(s) invoked   : GetCounterValue, Eth_GetElapsedTimeValue
**
** Registers Used        : MPSM
**
** Reference ID          : ETH_DUD_ACT_461
** Reference ID          : ETH_DUD_ACT_461_GBL001, ETH_DUD_ACT_461_GBL002
** Reference ID          : ETH_DUD_ACT_461_REG001, ETH_DUD_ACT_461_REG002
***********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_HwRMAC_PhyMdioWriteAccessFlow(
  CONST(uint32, AUTOMATIC) LulRMACIdx, CONST(uint8, AUTOMATIC) LucTrcvIdx,
  CONST(uint8, AUTOMATIC) LucRegIdx, CONST(uint16, AUTOMATIC) LusWriteVal)
{
  Std_ReturnType LucResult = E_OK;                                                                                      
  TickType LulTickStart;
  TickType LulTickElap;

  /* Request a write access */
  Eth_GaaRSW2_RMACRegs[LulRMACIdx]->ulMPSM =                                                                            
    ETH_RSW2_MPSM_SET(LucRegIdx, LucTrcvIdx, ETH_RSW2_RMAC_MPSM_POP_WRITE, LusWriteVal);                                /* PRQA S 3432, 2985 # JV-01, JV-01 */

  /* Wait until MPSM.PSME returns to 0 */
  LulTickStart = 0UL;
  LulTickElap = 0UL;
  (void)GetCounterValue(ETH_OS_COUNTER_ID, &LulTickStart);
  do
  {
    LulTickElap = LulTickElap + Eth_GetElapsedTimeValue(&LulTickStart);                                                 /* PRQA S 3383 # JV-01 */
  } while (((Eth_GaaRSW2_RMACRegs[LulRMACIdx]->ulMPSM & ETH_RSW2_RMAC_MPSM_PSME) != 0UL) && 
           (LulTickElap <= ETH_TIMEOUT_COUNT));

  if (ETH_TIMEOUT_COUNT < LulTickElap)
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
** Function Name         : Eth_HwRMAC_PhyMdioReadAccessFlow (RSW2)
**
** Service ID            : N/A
**
** Description           : Read data from the PHY management interface
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : LulRMACIdx     : Index of a RMAC
**                         LucTrcvIdx     : Index of the transceiver on the MII
**                         LucRegIdx      : Index of the transceiver register on the MII
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : LusRetData (Read data from PHY)
**
** Preconditions         : (ETH_CTRL_ENABLE_MII == STD_ON)
**
** Global Variable(s)    : Eth_GaaRSW2_RMACRegs
**
** Function(s) invoked   : GetCounterValue, Eth_GetElapsedTimeValue
**
** Registers Used        : MPSM
**
** Reference ID          : ETH_DUD_ACT_462
** Reference ID          : ETH_DUD_ACT_462_GBL001, ETH_DUD_ACT_462_GBL002
** Reference ID          : ETH_DUD_ACT_462_GBL003
** Reference ID          : ETH_DUD_ACT_462_REG001, ETH_DUD_ACT_462_REG002
** Reference ID          : ETH_DUD_ACT_462_REG003
***********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_HwRMAC_PhyMdioReadAccessFlow(
                                                            CONST(uint32, AUTOMATIC) LulRMACIdx, 
                                                            CONST(uint8, AUTOMATIC) LucTrcvIdx,
                                                            CONST(uint8, AUTOMATIC) LucRegIdx,
                                                            CONSTP2VAR(uint16, AUTOMATIC, ETH_APPL_DATA) LpRegValPtr)   /* PRQA S 3432 # JV-01 */
{
  TickType LulTickStart;
  TickType LulTickElap;
  Std_ReturnType LucResult;
  uint32 LulRdata;

  LucResult = E_OK;

  /* Request a read access */
  Eth_GaaRSW2_RMACRegs[LulRMACIdx]->ulMPSM =                                                                            
    ETH_RSW2_MPSM_SET(LucRegIdx, LucTrcvIdx, ETH_RSW2_RMAC_MPSM_POP_READ, 0x0U);                                        /* PRQA S 3432, 2985, 2986 # JV-01, JV-01, JV-01 */

  /* Wait until MPSM.PSME returns to 0 */
  LulTickStart = 0UL;
  LulTickElap = 0UL;
  (void)GetCounterValue(ETH_OS_COUNTER_ID, &LulTickStart);
  do
  {
    LulTickElap = LulTickElap + Eth_GetElapsedTimeValue(&LulTickStart);                                                 /* PRQA S 3383 # JV-01 */
  } while (((Eth_GaaRSW2_RMACRegs[LulRMACIdx]->ulMPSM & ETH_RSW2_RMAC_MPSM_PSME) != 0UL) &&
           (LulTickElap <= ETH_TIMEOUT_COUNT));

  if (ETH_TIMEOUT_COUNT < LulTickElap)
  {
    *LpRegValPtr = (uint16)0x0UL;                                                                                       
    LucResult = E_NOT_OK;
  }
  else
  {
    LulRdata = Eth_GaaRSW2_RMACRegs[LulRMACIdx]->ulMPSM;
    *LpRegValPtr = ETH_RSW2_SET_MPSM_PRD_READ(LulRdata);                                                                /* PRQA S 3469 # JV-01 */
  }

  return LucResult;
}
#endif /* (ETH_CTRL_ENABLE_MII == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Eth_HwRMAC_LinkVerification (RSW2)
**
** Service ID            : N/A
**
** Description           : RMAC Link Verification
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulRMACIdx : RMAC index
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
** Global Variable(s)    : Eth_GaaRSW2_RMACRegs
**
** Function(s) invoked   : GetCounterValue,
**                         Eth_GetElapsedTimeValue
**
** Registers Used        : MLVC
**
** Reference ID          : ETH_DUD_ACT_463
** Reference ID          : ETH_DUD_ACT_463_GBL001, ETH_DUD_ACT_463_GBL002
** Reference ID          : ETH_DUD_ACT_463_REG001, ETH_DUD_ACT_463_REG002
***********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_HwRMAC_LinkVerification(
  CONST(uint32, AUTOMATIC) LulRMACIdx)
{
  Std_ReturnType LucResult = E_OK;                                                                                      
  TickType LulTickStart;
  TickType LulTickElap;

  /* Request Link Verification */
  Eth_GaaRSW2_RMACRegs[LulRMACIdx]->ulMLVC =                                                                            
    (ETH_RSW2_RMAC_MLVC_PLV | ETH_RSW2_RMAC_MLVC_PASE | ETH_RSW2_RMAC_MLVC_LVT);

  /* Complete Link Verification */
  /* Wait until MLVC.PLV returns to 0 */
  LulTickStart = 0UL;
  LulTickElap = 0UL;
  (void)GetCounterValue(ETH_OS_COUNTER_ID, &LulTickStart);
  do
  {
    LulTickElap = LulTickElap + Eth_GetElapsedTimeValue(&LulTickStart);                                                 /* PRQA S 3383 # JV-01 */
  } while (((Eth_GaaRSW2_RMACRegs[LulRMACIdx]->ulMLVC & ETH_RSW2_RMAC_MLVC_PLV) != 0UL) && 
           (LulTickElap <= ETH_TIMEOUT_COUNT));

  if (ETH_TIMEOUT_COUNT < LulTickElap)
  {
    LucResult = E_NOT_OK;
  }
  else
  {
    LucResult = E_OK;
  }

  return LucResult;
}

#if (ETH_GLOBAL_TIME_SUPPORT == STD_ON)
/***********************************************************************************************************************
** Function Name         : Eth_HwGPTP_TimerTOffsetSettingFlow (RSW2)
**
** Service ID            : N/A
**
** Description           : Timer Offset Setting Flow
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulTimerIdx : gPTP index
**                       : LulNanoSeconds : gPTP timer NanoSeconds
**                       : LulSecondsLower : gPTP timer Seconds
**                       : LusSecondsHigher : gPTP timer Seconds High
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : (ETH_GLOBAL_TIME_SUPPORT == STD_ON)
**
** Global Variable(s)    : Eth_GpRSW2_GPTPRegs
**
** Function(s) invoked   : None
**
** Registers Used        : PTPTOVC0t, PTPTOVC1t, PTPTOVC2t
**
** Reference ID          : ETH_DUD_ACT_464
** Reference ID          : ETH_DUD_ACT_464_GBL001, ETH_DUD_ACT_464_GBL002
** Reference ID          : ETH_DUD_ACT_464_GBL003, ETH_DUD_ACT_464_GBL004
** Reference ID          : ETH_DUD_ACT_464_REG001, ETH_DUD_ACT_464_REG002
** Reference ID          : ETH_DUD_ACT_464_REG003, ETH_DUD_ACT_464_REG004
***********************************************************************************************************************/
STATIC FUNC(void, ETH_PRIVATE_CODE) Eth_HwGPTP_TimerTOffsetSettingFlow(
  CONST(uint32, AUTOMATIC) LulTimerIdx,
  CONST(uint32, AUTOMATIC) LulNanoSeconds,
  CONST(uint32, AUTOMATIC) LulSecondsLower,
  CONST(uint16, AUTOMATIC) LusSecondsHigher)
{
  Eth_GpRSW2_GPTPRegs->PTP[LulTimerIdx].ulPTPTOVC2t = (uint32)LusSecondsHigher;                                         
  Eth_GpRSW2_GPTPRegs->PTP[LulTimerIdx].ulPTPTOVC1t = LulSecondsLower;
  if (LulNanoSeconds > ETH_GPTP_OFFSET_NANOSEC_MAXVALUE)
  {
    /* The upper limit is 0x3B9AC9FF */
    Eth_GpRSW2_GPTPRegs->PTP[LulTimerIdx].ulPTPTOVC0t = ETH_GPTP_OFFSET_NANOSEC_MAXVALUE;
  }
  else
  {
    Eth_GpRSW2_GPTPRegs->PTP[LulTimerIdx].ulPTPTOVC0t = LulNanoSeconds;
  }
}

/***********************************************************************************************************************
** Function Name         : Eth_HwGPTP_Avtp64TimerTReadingFlow (RSW2)
**
** Service ID            : N/A
**
** Description           : AVTP Timer Reading Flow
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulTimerIdx  : AVTP index
**                         ulAVTP_Upper : AVTP Timer upper bits
**                         ulAVTP_Downer: AVTP Timer lower bits
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variable(s)    : Eth_GpRSW2_GPTPRegs
**
** Function(s) invoked   : None
**
** Registers Used        : PTPAVTPTM0t, PTPAVTPTM1t
**
** Reference ID          : ETH_DUD_ACT_521
** Reference ID          : ETH_DUD_ACT_521_REG001, ETH_DUD_ACT_521_REG002
***********************************************************************************************************************/
STATIC FUNC(void, ETH_PRIVATE_CODE) Eth_HwGPTP_Avtp64TimerTReadingFlow(
  CONST(uint32, AUTOMATIC) LulTimerIdx,
  CONSTP2VAR(uint32, AUTOMATIC, ETH_APPL_DATA) ulAVTP_Upper,                                                            /* PRQA S 3432 # JV-01 */
  CONSTP2VAR(uint32, AUTOMATIC, ETH_APPL_DATA) ulAVTP_Downer)                                                           /* PRQA S 3432 # JV-01 */
{
  /*Read 64-bit AVTP timer downer 32 bits */
  *ulAVTP_Downer = Eth_GpRSW2_GPTPRegs->PTP[LulTimerIdx].ulPTPAVTPTM0t;                                                 
  
  /* Read 64-bit AVTP timer upper 32 bits */
  *ulAVTP_Upper  = Eth_GpRSW2_GPTPRegs->PTP[LulTimerIdx].ulPTPAVTPTM1t;                                                 
}

/***********************************************************************************************************************
** Function Name         : Eth_HwGPTP_gPTPTimerTReadingFlow (RSW2)
**
** Service ID            : N/A
**
** Description           : gPTP Timer Reading Flow
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulTimerIdx : gPTP index
**                       : LpNanoSeconds : gPTP timer NanoSeconds
**                       : LpSecondsLower : gPTP timer Seconds
**                       : LpSecondsHigher : gPTP timer Seconds High
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : (ETH_GLOBAL_TIME_SUPPORT == STD_ON)
**
** Global Variable(s)    : Eth_GpRSW2_GPTPRegs
**
** Function(s) invoked   : None
**
** Registers Used        : PTPGPTPTM0t, PTPGPTPTM1t, PTPGPTPTM2t
**
** Reference ID          : ETH_DUD_ACT_465
** Reference ID          : ETH_DUD_ACT_465_GBL001, ETH_DUD_ACT_465_GBL002
** Reference ID          : ETH_DUD_ACT_465_GBL003
** Reference ID          : ETH_DUD_ACT_465_REG001, ETH_DUD_ACT_465_REG002
** Reference ID          : ETH_DUD_ACT_465_REG003
***********************************************************************************************************************/
STATIC FUNC(void, ETH_PRIVATE_CODE) Eth_HwGPTP_gPTPTimerTReadingFlow(
  CONST(uint32, AUTOMATIC) LulTimerIdx,
  CONSTP2VAR(uint32, AUTOMATIC, ETH_APPL_DATA) LpNanoSeconds,                                                           /* PRQA S 3432 # JV-01 */
  CONSTP2VAR(uint32, AUTOMATIC, ETH_APPL_DATA) LpSecondsLower,                                                          /* PRQA S 3432 # JV-01 */
  CONSTP2VAR(uint16, AUTOMATIC, ETH_APPL_DATA) LpSecondsHigher)                                                         /* PRQA S 3432 # JV-01 */
{
  uint32 LulseconHi;

  *LpNanoSeconds = Eth_GpRSW2_GPTPRegs->PTP[LulTimerIdx].ulPTPGPTPTM0t;                                                 
  *LpSecondsLower = Eth_GpRSW2_GPTPRegs->PTP[LulTimerIdx].ulPTPGPTPTM1t;                                                
  LulseconHi = Eth_GpRSW2_GPTPRegs->PTP[LulTimerIdx].ulPTPGPTPTM2t;
  /* In PTPGPTPTM2t, only the lower 16 bits are valid, casting to uint16 does no problem. */
  *LpSecondsHigher = (uint16)LulseconHi;                                                                                
}
#endif /* (ETH_GLOBAL_TIME_SUPPORT == STD_ON) */

/***********************************************************************************************************************
** Function Name         : COMA_BufferPoolnitializationFlow (RSW2)
**
** Service ID            : N/A
**
** Description           : COMA Switch Clock Enable Flow
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
** Return parameter      : E_OK : Success
**                         E_NOT_OK : Failure
**
** Preconditions         : None
**
** Global Variable(s)    : Eth_GpRSW2_COMARegs
**
** Function(s) invoked   : GetCounterValue,
**                         Eth_GetElapsedTimeValue
**
** Registers Used        : CABPIRM, CABPPFLCi, CABPPPFLCij
**
** Reference ID          : ETH_DUD_ACT_466
** Reference ID          : ETH_DUD_ACT_466_GBL001, ETH_DUD_ACT_466_GBL002
** Reference ID          : ETH_DUD_ACT_466_GBL003, ETH_DUD_ACT_466_GBL004
** Reference ID          : ETH_DUD_ACT_466_GBL005, ETH_DUD_ACT_466_GBL006
** Reference ID          : ETH_DUD_ACT_466_GBL007, ETH_DUD_ACT_466_GBL008
** Reference ID          : ETH_DUD_ACT_466_REG001, ETH_DUD_ACT_466_REG002
** Reference ID          : ETH_DUD_ACT_466_REG003, ETH_DUD_ACT_466_REG004
** Reference ID          : ETH_DUD_ACT_466_REG005, ETH_DUD_ACT_466_REG006
***********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, ETH_PRIVATE_CODE) COMA_BufferPoolnitializationFlow(void)
{
  P2CONST(Eth_ETNEConfigType, AUTOMATIC, ETH_APPL_DATA) LpHwUnitConfig;
  Std_ReturnType LucResult = E_OK;                                                                                      
  uint32 LulCtrlIdx;
  uint32 LulPasLvl;
  uint32 LulPortIdx;
  #if (ETH_SWITCHING_MODE == ETH_SWMODE_ENDSTATION)
  TickType LulTickStart;
  TickType LulTickElap;
  #endif /* ETH_SWITCHING_MODE == ETH_SWMODE_ENDSTATION */

  /* CABPIBWMCi Set */

  /* CABPWMLC Set */

  /* CABPPFLCi Set */
  for (LulPasLvl = 0; LulPasLvl < ETH_RACE_PAS_LVL_N; LulPasLvl++)
  {
    if (ETH_ENABLE == Eth_GpGlobalPauseCfgPtr[LulPasLvl].enGlobalPause)                                                 /* PRQA S 3416 # JV-01 */
    {
      Eth_GpRSW2_COMARegs->ulCABPPFLCi[LulPasLvl] =                                                                     /* PRQA S 0404 # JV-01 */
        (uint32)(((uint32)Eth_GpGlobalPauseCfgPtr[LulPasLvl].ulPauseAssertionLevel << 16UL) |
                 ((uint32)Eth_GpGlobalPauseCfgPtr[LulPasLvl].ulPauseDeAssertionLevel));
    } /* else No action required */
  }
  /* CABPPWMLCi Set */

  /* CABPPPFLCij Set */
  for (LulPortIdx = 0; LulPortIdx < ETH_RACE_PORT_N; LulPortIdx++)
  {
    if (ETH_TRUE == Eth_GaaRsw2PortValid[LulPortIdx])
    {
      LulCtrlIdx = Eth_GaaRsw2PortCtrlIdx[LulPortIdx];
      LpHwUnitConfig =
        (P2CONST(Eth_ETNEConfigType, AUTOMATIC, ETH_APPL_DATA))Eth_GpCtrlConfigPtr[LulCtrlIdx].pHwUnitConfig;           /* PRQA S 0316 # JV-01 */
      if (ETH_ENABLE == LpHwUnitConfig->stFlowControlConfig.enPauseFrame)                                               
      {
        /* When RMAC is PAUSE mode, set only level 0 */
        Eth_GpRSW2_COMARegs->ulCABPPPFLCij[LulPortIdx][0] =
          (uint32)(((uint32)LpHwUnitConfig->stFlowControlConfig.stPauseLevelConfig.ulPauseAssertionLevel << 16UL) |
                   ((uint32)LpHwUnitConfig->stFlowControlConfig.stPauseLevelConfig.ulPauseDeAssertionLevel));
      }
      else if (ETH_ENABLE == LpHwUnitConfig->stPFCConfig.enPFCFrame)
      {
        /* When RMAC is PFC mode, set levels 0 and 1 */
        for (LulPasLvl = 0; LulPasLvl < ETH_RACE_PAS_LVL_N; LulPasLvl++)
        {
          Eth_GpRSW2_COMARegs->ulCABPPPFLCij[LulPortIdx][LulPasLvl] =
            (uint32)(((uint32)LpHwUnitConfig->stPFCConfig.stPFCPauseLevelConfig[LulPasLvl]
                                                                                       .ulPauseAssertionLevel << 16UL) |
                     ((uint32)LpHwUnitConfig->stPFCConfig.stPFCPauseLevelConfig[LulPasLvl].ulPauseDeAssertionLevel));
        }
      }
      else
      {
        // No action required
      }
    }/* No action required */
  }

  #if (ETH_SWITCHING_MODE == ETH_SWMODE_ENDSTATION)
  /* CABPULCi Set */

  /* CABPIRM.BPIOG Set */
  Eth_GpRSW2_COMARegs->ulCABPIRM = ETH_RSW2_COMA_CABPIRM_BPIOG;

  /* Read CABPIRM.BPR */
  /* Wait until CABPIRM.BPR returns to 1 */
  LulTickStart = 0UL;
  LulTickElap = 0UL;
  (void)GetCounterValue(ETH_OS_COUNTER_ID, &LulTickStart);
  do
  {
    LulTickElap = LulTickElap + Eth_GetElapsedTimeValue(&LulTickStart);                                                 /* PRQA S 3383 # JV-01 */
  } while (((Eth_GpRSW2_COMARegs->ulCABPIRM & ETH_RSW2_COMA_CABPIRM_BPR) != ETH_RSW2_COMA_CABPIRM_BPR) && 
           (LulTickElap <= ETH_TIMEOUT_COUNT));

  if (ETH_TIMEOUT_COUNT < LulTickElap)
  {
    LucResult = E_NOT_OK;
  }
  else
  {
    LucResult = E_OK;
  }
  #endif /* ETH_SWITCHING_MODE == ETH_SWMODE_ENDSTATION */

  return LucResult;
}

#if (ETH_SWITCHING_MODE == ETH_SWMODE_ENDSTATION)
/***********************************************************************************************************************
** Function Name         : COMA_RSwitchResetFlow (RSW2)
**
** Service ID            : N/A
**
** Description           : R-Switch Reset Flow
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
** Preconditions         : None
**
** Global Variable(s)    : Eth_GpRSW2_COMARegs
**
** Function(s) invoked   : None
**
** Registers Used        : RRC
**
** Reference ID          : ETH_DUD_ACT_467
** Reference ID          : ETH_DUD_ACT_467_GBL001, ETH_DUD_ACT_467_GBL002
** Reference ID          : ETH_DUD_ACT_467_REG001, ETH_DUD_ACT_467_REG002
***********************************************************************************************************************/
STATIC FUNC(void, ETH_PRIVATE_CODE) COMA_RSwitchResetFlow(void)
{
  volatile uint32 i, loopLimit;
  loopLimit = 1;

  /* Set R-Switch reset */
  Eth_GpRSW2_COMARegs->ulRRC = 0x00000001UL;

  for (i=0; i < loopLimit; i++)                                                                                         /* PRQA S 0404, 3387, 3416 # JV-01, JV-01, JV-01 */
  {
    /* wait for 1 clock */
  }

  /* Release R-Switch reset */
  Eth_GpRSW2_COMARegs->ulRRC = 0x00000000UL;
}
#endif /* ETH_SWITCHING_MODE == ETH_SWMODE_ENDSTATION */

/***********************************************************************************************************************
** Function Name         : COMA_AgentIClockEnableFlow (RSW2)
**
** Service ID            : N/A
**
** Description           : COMA agent i clock enable flow
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulPortIdx : RSW2 port index
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variable(s)    : Eth_GaaRsw2PortMap, Eth_GpRSW2_COMARegs
**
** Function(s) invoked   : None
**
** Registers Used        : RCEC
**
** Reference ID          : ETH_DUD_ACT_468
** Reference ID          : ETH_DUD_ACT_468_GBL001, ETH_DUD_ACT_468_GBL002
** Reference ID          : ETH_DUD_ACT_468_GBL003
** Reference ID          : ETH_DUD_ACT_468_REG001, ETH_DUD_ACT_468_REG002
***********************************************************************************************************************/
STATIC FUNC(void, ETH_PRIVATE_CODE) COMA_AgentIClockEnableFlow(
  CONST(uint32, AUTOMATIC) LulPortIdx)
{
  uint32 LulRegVal;

  LulRegVal = Eth_GpRSW2_COMARegs->ulRCEC;
  LulRegVal = (LulRegVal | Eth_GaaRsw2PortMap[LulPortIdx] | ETH_RSW2_COMA_RCEC_RCE);                                    
  Eth_GpRSW2_COMARegs->ulRCEC = LulRegVal;
}

/***********************************************************************************************************************
** Function Name         : COMA_AgentIClockDisableFlow (RSW2)
**
** Service ID            : N/A
**
** Description           : COMA agent i clock disable flow
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulPortIdx : RSW2 port index
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variable(s)    : Eth_GaaRsw2PortMap, Eth_GpRSW2_COMARegs
**
** Function(s) invoked   : None
**
** Registers Used        : RCDC
**
** Reference ID          : ETH_DUD_ACT_469
** Reference ID          : ETH_DUD_ACT_469_GBL001
** Reference ID          : ETH_DUD_ACT_469_REG001
***********************************************************************************************************************/
STATIC FUNC(void, ETH_PRIVATE_CODE) COMA_AgentIClockDisableFlow(
  CONST(uint32, AUTOMATIC) LulPortIdx)
{
  Eth_GpRSW2_COMARegs->ulRCDC = Eth_GaaRsw2PortMap[LulPortIdx];                                                         
}

/***********************************************************************************************************************
** Function Name         : COMA_AgentIClockStatusCheckFlow (RSW2)
**
** Service ID            : N/A
**
** Description           : COMA agent i clock status check flow
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulPortIdx : RSW2 port index
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : ETH_TRUE : clock enabled
**                         ETH_FALSE :clock disabled
**
** Preconditions         : None
**
** Global Variable(s)    : Eth_GaaRsw2PortMap, Eth_GpRSW2_COMARegs
**
** Function(s) invoked   : None
**
** Registers Used        : RCEC
**
** Reference ID          : ETH_DUD_ACT_470
** Reference ID          : ETH_DUD_ACT_470_GBL001, ETH_DUD_ACT_470_GBL002
** Reference ID          : ETH_DUD_ACT_470_REG001
***********************************************************************************************************************/
STATIC FUNC(boolean, ETH_PRIVATE_CODE) COMA_AgentIClockStatusCheckFlow(
  CONST(uint32, AUTOMATIC) LulPortIdx)
{
  uint32 LulRegVal;
  boolean LblClockEnabled;

  LulRegVal = Eth_GpRSW2_COMARegs->ulRCEC;

  if ((LulRegVal & (ETH_RSW2_COMA_RCEC_RCE | Eth_GaaRsw2PortMap[LulPortIdx])) ==                                        
      (ETH_RSW2_COMA_RCEC_RCE | Eth_GaaRsw2PortMap[LulPortIdx]))
  {
    LblClockEnabled = ETH_TRUE;
  }
  else
  {
    LblClockEnabled = ETH_FALSE;
  }

  return LblClockEnabled;
}

#if (ETH_SWITCHING_MODE == ETH_SWMODE_ENDSTATION)
/***********************************************************************************************************************
** Function Name         : COMA_SwitchClockEnableFlow (RSW2)
**
** Service ID            : N/A
**
** Description           : COMA Switch Clock Enable Flow
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
** Preconditions         : None
**
** Global Variable(s)    : Eth_GpRSW2_COMARegs
**
** Function(s) invoked   : None
**
** Registers Used        : RCEC
**
** Reference ID          : ETH_DUD_ACT_471
** Reference ID          : ETH_DUD_ACT_471_GBL001
** Reference ID          : ETH_DUD_ACT_471_REG001
***********************************************************************************************************************/
STATIC FUNC(void, ETH_PRIVATE_CODE) COMA_SwitchClockEnableFlow(void)
{
  Eth_GpRSW2_COMARegs->ulRCEC = ETH_RSW2_COMA_RCEC_RCE;
}
#endif /* ETH_SWITCHING_MODE == ETH_SWMODE_ENDSTATION */

/***********************************************************************************************************************
** Function Name         : MFWD_FullSettingFlow (RSW2)
**
** Service ID            : N/A
**
** Description           : MFWD Full Setting Flow
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
** Preconditions         : None
**
** Global Variable(s)    : None
**
** Function(s) invoked   : MFWD_PortBasedForwardingSettingFlow,
**                         Eth_HwMFWD_PortISettingFlow,
**                         MFWD_Layer3ForwardingRoutingFilteringSettingFlow,
**                         MFWD_Layer2ForwardingSettingFlow,
**                         MFWD_Layer2Layer3UpdateSettingFlow,
**                         MFWD_PsfpSettingFlow
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_472
***********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, ETH_PRIVATE_CODE) MFWD_FullSettingFlow(void)
{
  Std_ReturnType LucResult = E_OK;                                                                                      
  uint32 LulPortIdx;

  #if (ETH_SWITCHING_MODE == ETH_SWMODE_ENDSTATION)
  /* General function setting flow */

  /* Layer 3 forearding/routing/filtering setting flow */
  LucResult = MFWD_Layer3ForwardingRoutingFilteringSettingFlow();

  /* Layer 2 forwarding setting flow */
  if (E_OK == LucResult)
  {
    LucResult = MFWD_Layer2ForwardingSettingFlow();
  } /* else No action required */
  #endif /* ETH_SWITCHING_MODE == ETH_SWMODE_ENDSTATION */

  /* Port-based forwarding setting flow */
  if (E_OK == LucResult)                                                                                                /* PRQA S 2991, 2995 # JV-01, JV-01 */
  {
    MFWD_PortBasedForwardingSettingFlow();
  } /* else No action required */

  #if (ETH_SWITCHING_MODE == ETH_SWMODE_ENDSTATION)
  /* Layer 2/Layer 3 update setting flow */
  if (E_OK == LucResult)
  {
    LucResult = MFWD_Layer2Layer3UpdateSettingFlow();
  } /* else No action required */

  /* PSFP setting flow */
  if (E_OK == LucResult)
  {
    LucResult = MFWD_PsfpSettingFlow();
  } /* else No action required */
  #endif /* ETH_SWITCHING_MODE == ETH_SWMODE_ENDSTATION */

  /* Port i setting flow */
  if (E_OK == LucResult)                                                                                                /* PRQA S 2991, 2995 # JV-01, JV-01 */
  {
    for (LulPortIdx = 0; LulPortIdx < ETH_RACE_PORT_N; LulPortIdx++)
    {
      /* Port i setting flow  */
      Eth_HwMFWD_PortISettingFlow(LulPortIdx);
    }
  } /* else No action required */

  return LucResult;
}

#if (ETH_SWITCHING_MODE == ETH_SWMODE_ENDSTATION)
/***********************************************************************************************************************
** Function Name         : MFWD_Layer3ForwardingRoutingFilteringSettingFlow (RSW2)
**
** Service ID            : N/A
**
** Description           : MFWD Layer 3 forearding/routing/filtering setting flow
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
** Preconditions         : None
**
** Global Variable(s)    : None
**
** Function(s) invoked   : Eth_HwMFWD_Layer3TableResetFlow
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_473
***********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, ETH_PRIVATE_CODE) MFWD_Layer3ForwardingRoutingFilteringSettingFlow(void)
{
  Std_ReturnType LucResult;

  /* Layer 3 table reset flow */
  LucResult = Eth_HwMFWD_Layer3TableResetFlow();

  /* Subsequent processing is not processed by MCAL/ETH */

  return LucResult;
}

/***********************************************************************************************************************
** Function Name         : MFWD_Layer2ForwardingSettingFlow (RSW2)
**
** Service ID            : N/A
**
** Description           : MFWD Layer 2 forwarding setting flow
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
** Preconditions         : None
**
** Global Variable(s)    : None
**
** Function(s) invoked   : Eth_HwMFWD_MacTableResetFlow
**                         Eth_HwMFWD_VlanTableResetFlow
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_474
***********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, ETH_PRIVATE_CODE) MFWD_Layer2ForwardingSettingFlow(void)
{
  Std_ReturnType LucResult;

  /* MAC table reset flow  */
  LucResult = Eth_HwMFWD_MacTableResetFlow();

  if (E_OK == LucResult)
  {
    /* VLAN table reset flow  */
    LucResult = Eth_HwMFWD_VlanTableResetFlow();
  } /* else No action required */

  /* Subsequent processing is not processed by MCAL/ETH */

  return LucResult;
}
#endif /* ETH_SWITCHING_MODE == ETH_SWMODE_ENDSTATION */

/***********************************************************************************************************************
** Function Name         : MFWD_PortBasedForwardingSettingFlow (RSW2)
**
** Service ID            : N/A
**
** Description           : MFWD Port Based Forwarding Setting Flow
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
** Preconditions         : None
**
** Global Variable(s)    : None
**
** Function(s) invoked   : Eth_HwMFWD_PortIPortBasedSettingFlow
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_475
***********************************************************************************************************************/
STATIC FUNC(void, ETH_PRIVATE_CODE) MFWD_PortBasedForwardingSettingFlow(void)
{
  uint32 LulPortIdx;

  for (LulPortIdx = 0; LulPortIdx < ETH_RACE_PORT_N; LulPortIdx++)
  {
    /* Port i port-based setting flow  */
    Eth_HwMFWD_PortIPortBasedSettingFlow(LulPortIdx);
  }
}

#if (ETH_SWITCHING_MODE == ETH_SWMODE_ENDSTATION)
/***********************************************************************************************************************
** Function Name         : MFWD_Layer2Layer3UpdateSettingFlow (RSW2)
**
** Service ID            : N/A
**
** Description           : MFWD Layer 2/Layer 3 update setting flow
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
** Preconditions         : None
**
** Global Variable(s)    : None
**
** Function(s) invoked   : Eth_HwMFWD_Layer2Layer3UpdateTableResetFlow
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_476
***********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, ETH_PRIVATE_CODE) MFWD_Layer2Layer3UpdateSettingFlow(void)
{
  Std_ReturnType LucResult;

  /* Layer 2/Layer 3 update table reset flow */
  LucResult = Eth_HwMFWD_Layer2Layer3UpdateTableResetFlow();

  /* Subsequent processing is not processed by MCAL/ETH */

  return LucResult;
}

/***********************************************************************************************************************
** Function Name         : MFWD_PsfpSettingFlow (RSW2)
**
** Service ID            : N/A
**
** Description           : MFWD PSFP setting flow
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
** Preconditions         : None
**
** Global Variable(s)    : None
**
** Function(s) invoked   : Eth_HwMFWD_GateRamResetFlow
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_477
***********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, ETH_PRIVATE_CODE) MFWD_PsfpSettingFlow(void)
{
  Std_ReturnType LucResult;

  /* Gate RAM reset flow */
  LucResult = Eth_HwMFWD_GateRamResetFlow();

  /* Subsequent processing is not processed by MCAL/ETH */

  return LucResult;
}
#endif /* ETH_SWITCHING_MODE == ETH_SWMODE_ENDSTATION */

/***********************************************************************************************************************
** Function Name         : GWCA_FullSettingFlow (RSW2)
**
** Service ID            : N/A
**
** Description           : GWCA Full Setting Flow
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulGWCAIdx : GWCA index
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variable(s)    : Eth_GaaTSDescTableAddr, Eth_GaaLinkFixTable,
**                         Eth_GaaRsw2PortValid, Eth_GaaRsw2PortCtrlIdx,
**                         Eth_GaaCtrlStat, Eth_GaaTsDescChain,
**                         Eth_GpGwcaRegPtr, Eth_GaaRSW2_GWCARegs,
**                         Eth_GstDescChainMap
**
** Function(s) invoked   : Eth_GetElapsedTimeValue,
**                         GetCounterValue
**
** Registers Used        : GWMAC0, GWMAC1, GWVCC, GWVTC, GWTTFC,
**                         GWDCBAC0, GWDCBAC1, GWTSDCCs, GWDCCi
**                         GWRMFSCq, GWTDCAC0s, GWTDCAC1s,
**                         GWGRLC, GWGRLULC, GWRLCi, GWRLULCi
**
** Reference ID          : ETH_DUD_ACT_478
** Reference ID          : ETH_DUD_ACT_478_GBL001, ETH_DUD_ACT_478_GBL002
** Reference ID          : ETH_DUD_ACT_478_GBL003, ETH_DUD_ACT_478_GBL004
** Reference ID          : ETH_DUD_ACT_478_GBL005, ETH_DUD_ACT_478_GBL006
** Reference ID          : ETH_DUD_ACT_478_GBL007, ETH_DUD_ACT_478_GBL008
** Reference ID          : ETH_DUD_ACT_478_GBL009, ETH_DUD_ACT_478_GBL010
** Reference ID          : ETH_DUD_ACT_478_GBL011, ETH_DUD_ACT_478_GBL012
** Reference ID          : ETH_DUD_ACT_478_GBL013, ETH_DUD_ACT_478_GBL014
** Reference ID          : ETH_DUD_ACT_478_GBL015, ETH_DUD_ACT_478_GBL016
** Reference ID          : ETH_DUD_ACT_478_GBL017, ETH_DUD_ACT_478_GBL018
** Reference ID          : ETH_DUD_ACT_478_REG001, ETH_DUD_ACT_478_REG002
** Reference ID          : ETH_DUD_ACT_478_REG003, ETH_DUD_ACT_478_REG004
** Reference ID          : ETH_DUD_ACT_478_REG005, ETH_DUD_ACT_478_REG006
** Reference ID          : ETH_DUD_ACT_478_REG007, ETH_DUD_ACT_478_REG008
** Reference ID          : ETH_DUD_ACT_478_REG009, ETH_DUD_ACT_478_REG010
** Reference ID          : ETH_DUD_ACT_478_REG011, ETH_DUD_ACT_478_REG012
** Reference ID          : ETH_DUD_ACT_478_REG013, ETH_DUD_ACT_478_REG014
** Reference ID          : ETH_DUD_ACT_478_REG015, ETH_DUD_ACT_478_REG016
***********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, ETH_PRIVATE_CODE) GWCA_FullSettingFlow(
  CONST(uint32, AUTOMATIC) LulGWCAIdx)
{
  P2VAR(volatile Eth_RSW2_GWCARegType, AUTOMATIC, REGSPACE) LpGwcaReg;
  P2CONST(Eth_ETNEConfigType, AUTOMATIC, ETH_APPL_DATA) LpHwUnitConfig;
  TickType LulTickStart;
  TickType LulTickElap;
  uint32 LulRegVal;
  uint32 LulCtrlIdx;
  uint32 LulFifoIdx;
  uint8 LucChainId;
  uint32 LulIdx;
  uint8 LucResult;
  uint32 LulChainId;
  uint32 LulGWRLIdx;

  LucResult = E_OK;
  LpGwcaReg = Eth_GaaRSW2_GWCARegs[LulGWCAIdx];                                                                         
  LulCtrlIdx = Eth_GaaRsw2PortCtrlIdx[ETH_CONV_GWCAID_TO_PORTID(LulGWCAIdx)];                                           /* PRQA S 3383, 3432 # JV-01, JV-01 */

  /* Set GWIRC Set queue priority remapping */

  /* Set GWRDQSC Set queue security level */

  /* Set GWRDQAC Set Queue arbitration */

  /* Set GWRGC Set CRC reception */

  /* Set GWRMFSCq Set queue max frame size */
  for (LulFifoIdx = 0UL; LulFifoIdx < (uint32)ETH_GWCA_FRM_PRIO_N; LulFifoIdx++)
  {
    /* Add FCS size becouse PDF setting value dosen't include FCS size */
    LpGwcaReg->ulGWRMFSCq[LulFifoIdx] = Eth_GulRxMaxFrameSize + ETH_FCS_LENGTH;                                         /* PRQA S 3383 # JV-01 */
  }
  /* Set GWRDQDCq Set descriptor queue depths */

  /* Set GWMAC0/1 Set MAC address */
  if (ETH_TRUE == Eth_GaaRsw2PortValid[ETH_CONV_GWCAID_TO_PORTID(LulGWCAIdx)])                                          /* PRQA S 3383, 3432 # JV-01, JV-01 */
  {
    /* GWMAC0 Set */
    LpGwcaReg->ulGWMAC0 = Eth_GaaCtrlStat[LulCtrlIdx].stMacAddr.ulH32 >> 16UL;                                          
    /* GWMAC1 Set */
    LpGwcaReg->ulGWMAC1 =
      (Eth_GaaCtrlStat[LulCtrlIdx].stMacAddr.ulH32 << 16UL) | Eth_GaaCtrlStat[LulCtrlIdx].stMacAddr.ulL16;
  } /* else No action required */

  /* Set GWVCC Set VLAN modes */
  LpGwcaReg->ulGWVCC = Eth_GpGwcaRegPtr->ulGWVCCValue;

  /* Set GWVTC Set VLAN TAGs */
  LpGwcaReg->ulGWVTC = Eth_GpGwcaRegPtr->ulGWVTCValue;

  /* Set GWTTFC Set TAG filtering */
  LpGwcaReg->ulGWTTFC = Eth_GpGwcaRegPtr->ulGWTTFCValue;

  /* Set GWTDCA0s/1s Set timestamp chain address */
  #if (ETH_GLOBAL_TIME_SUPPORT == STD_ON)
  LulRegVal = (uint32)&Eth_GaaTsDescChain[0];                                                                           /* PRQA S 0306 # JV-01 */
  LpGwcaReg->GWTDCAC[ETH_GPTP_TIMER_DOMAIN].ulGWTDCAC1s = LulRegVal;
  LpGwcaReg->GWTDCAC[ETH_GPTP_TIMER_DOMAIN].ulGWTDCAC0s = 0x0UL;
  #endif

  /* Set GWTSDCCs Set timestamp queues */
  #if (ETH_GLOBAL_TIME_SUPPORT == STD_ON)
  LpGwcaReg->ulGWTSDCCs[ETH_GPTP_TIMER_DOMAIN] = 0x1UL;
  #endif

  /* Multicast table setting flow */

  /* LINKFIX table setting */
  /* This process is skipped because "LINKFIX table" has already been created. */

  /* Set GWDCBAC0/1 Set AXI base address */
  LpGwcaReg->ulGWDCBAC0 = 0x0UL;

  LulRegVal = (uint32)&Eth_GaaLinkFixTable[0];                                                                          /* PRQA S 0306 # JV-01 */
  LpGwcaReg->ulGWDCBAC1 = LulRegVal;

  /* Set GWIICBSC Set inter-IP block size */

  /* Set GWMDNC Set maximum descriptor limits */

  /* Set GWTPCp Set queue pause */

  /* Set GWDCCi Set descriptor chains */
  for (LulIdx = 0; LulIdx < Eth_GstDescChainMap.ulValidChainNum; LulIdx++)
  {
    LulRegVal = ETH_RSW2_GWCA_GWDCC_EDE;
    LucChainId = Eth_GstDescChainMap.ucValidChainId[LulIdx];                                                            
    
    if (ETH_TX_RSW2 == Eth_GstDescChainMap.aaChainInfo[LucChainId].enDir)                                               
    {
      LulRegVal |= ETH_RSW2_GWCA_GWDCC_TX;
      LulRegVal |= ETH_RSW2_GWCA_GWDCC_DCP_SET(Eth_GstDescChainMap.aaChainInfo[LucChainId].ulFifoIdx);                  /* PRQA S 3432 # JV-01 */
    }
    else
    {
      LulRegVal |= ETH_RSW2_GWCA_GWDCC_RX;
#if (ETH_GLOBAL_TIME_SUPPORT == STD_ON)
      LulRegVal |= ETH_RSW2_GWCA_GWDCC_ETS;
#endif
    }

    LpGwcaReg->ulGWDCCi[LucChainId] = LulRegVal;                                                                        
    LpGwcaReg->ulGWDCCi[LucChainId] |= ETH_RSW2_GWCA_GWDCC_BALR;
    
    /* Wait until BALR returns to 0 */
    LulTickStart = 0UL;
    LulTickElap = 0UL;
    (void)GetCounterValue(ETH_OS_COUNTER_ID, &LulTickStart);
    do
    {
      LulTickElap = LulTickElap + Eth_GetElapsedTimeValue(&LulTickStart);                                               /* PRQA S 3383 # JV-01 */
    } while (((LpGwcaReg->ulGWDCCi[LucChainId] & ETH_RSW2_GWCA_GWDCC_BALR) != 0UL) && 
             (LulTickElap <= ETH_TIMEOUT_COUNT));

    if (ETH_TIMEOUT_COUNT < LulTickElap)
    {
       LucResult = E_NOT_OK;
       break;
    }
    else
    {
       LucResult = E_OK;
    }
  }

  /* Global rate limiter setting flow */
  LpGwcaReg->ulGWGRLULC = Eth_GpGwcaRegPtr->ulGWGRLULCValue;
  LpGwcaReg->ulGWGRLC = Eth_GpGwcaRegPtr->ulGWGRLCValue;

  /* Rate limiter i setting flow (i from 0 to AXI_TLIM_N) */
  for (LulIdx = 0UL; LulIdx < (uint32)ETH_ETNE_CTRLS_SUPPORTED; LulIdx++)                                               /* PRQA S 2877 # JV-01 */
  {
    LpHwUnitConfig =
    (P2CONST(Eth_ETNEConfigType, AUTOMATIC, ETH_APPL_DATA))Eth_GpCtrlConfigPtr[LulIdx].pHwUnitConfig;                   /* PRQA S 0316 # JV-01 */
    for (LulFifoIdx = 0UL; LulFifoIdx < (uint32)LpHwUnitConfig->stQueueConfig.ucNumberOfTxQueue; LulFifoIdx++)          
    {
      LulChainId = LpHwUnitConfig->stQueueConfig.pTxQueueConfig[LulFifoIdx].ulChainId;                                  
      if ((ETH_RACE_AXI_CHAIN_RLMIN_N <= LulChainId))
      {
        LulGWRLIdx = (ETH_RACE_AXI_CHAIN_N - 1UL) - LulChainId;                                                         /* PRQA S 3383 # JV-01 */
        LpGwcaReg->GWRL[LulGWRLIdx].ulGWRLULCi = 
          LpHwUnitConfig->stQueueConfig.pTxQueueConfig[LulFifoIdx].stPerQueRLConfig.ulGWRLULCiValue;

        LpGwcaReg->GWRL[LulGWRLIdx].ulGWRLCi = 
          LpHwUnitConfig->stQueueConfig.pTxQueueConfig[LulFifoIdx].stPerQueRLConfig.ulGWRLCiValue;
      }
    }
  }
  /* Set GWIDPC Set interrupt delay prescaler */

  /* Set GWIDCi Set interrupt delays */

  return LucResult;
}

/***********************************************************************************************************************
** Function Name         : ETHA_FullSettingFlow (RSW2)
**
** Service ID            : N/A
**
** Description           : Full Setting HWUnit(ETHA)
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulETHAIdx : ETHA index
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variable(s)    : Eth_GaaRsw2PortCtrlIdx, Eth_GaaRSW2_ETHARegs,
**                         Eth_GpCtrlConfigPtr
**
** Function(s) invoked   : Eth_HwETHA_CbsQSettingFlow
**
** Registers Used        : EAVCC, EAVTC, EARTFC, EATASIGSC, EATASHCC
**                       : EATMFSCq, EATPEC
**
** Reference ID          : ETH_DUD_ACT_479
** Reference ID          : ETH_DUD_ACT_479_GBL001, ETH_DUD_ACT_479_GBL002
** Reference ID          : ETH_DUD_ACT_479_GBL003, ETH_DUD_ACT_479_GBL004
** Reference ID          : ETH_DUD_ACT_479_GBL005, ETH_DUD_ACT_479_GBL006
** Reference ID          : ETH_DUD_ACT_479_GBL007, ETH_DUD_ACT_479_GBL008
** Reference ID          : ETH_DUD_ACT_479_GBL009
** Reference ID          : ETH_DUD_ACT_479_REG001, ETH_DUD_ACT_479_REG002
** Reference ID          : ETH_DUD_ACT_479_REG003, ETH_DUD_ACT_479_REG004
** Reference ID          : ETH_DUD_ACT_479_REG005, ETH_DUD_ACT_479_REG006
** Reference ID          : ETH_DUD_ACT_479_REG007
***********************************************************************************************************************/
STATIC FUNC(void, ETH_PRIVATE_CODE) ETHA_FullSettingFlow(
  CONST(uint32, AUTOMATIC) LulETHAIdx)
{
  P2CONST(Eth_ETNEConfigType, AUTOMATIC, ETH_APPL_DATA) LpHwUnitConfig;
  uint32 LulCtrlIdx;
  uint32 LulPriority;
  uint32 LulQIdx;
  uint32 LulInitGateState;
  uint32 LulRegVal;

  LulInitGateState = 0;
  LulCtrlIdx = Eth_GaaRsw2PortCtrlIdx[ETH_CONV_ETHAID_TO_PORTID(LulETHAIdx)];                                           /* PRQA S 3469 # JV-01 */

  LpHwUnitConfig =
    (P2CONST(Eth_ETNEConfigType, AUTOMATIC, ETH_APPL_DATA))Eth_GpCtrlConfigPtr[LulCtrlIdx].pHwUnitConfig;               /* PRQA S 0316 # JV-01 */

  /* Set EAIRC Set queue priority remapping */

  /* Set EATDQSC Set queue security level */

  /* Set EATDQAC Set Queue arbitration */

  /* Set EATPEC Set queue type */
  LulRegVal = 0UL;
  for (LulPriority = 0UL; LulPriority < (uint32)LpHwUnitConfig->stQueueConfig.ucNumberOfTxQueue; LulPriority++)         
  {
    LulRegVal |= ((uint32)LpHwUnitConfig->stQueueConfig.pTxQueueConfig[LulPriority].enFrameType << LulPriority);        
  }
  Eth_GaaRSW2_ETHARegs[LulETHAIdx]->ulEATPEC = ((uint32)LpHwUnitConfig->enTxFragment << 16UL) | LulRegVal;              

  /* Set EATMFSCq Set queue max frame size */
  for (LulPriority = 0UL; LulPriority < (uint32)LpHwUnitConfig->stQueueConfig.ucNumberOfTxQueue; LulPriority++)
  {
    /* Add FCS size becouse PDF setting value dosen't include FCS size */
    Eth_GaaRSW2_ETHARegs[LulETHAIdx]->ulEATMFSCq[LulPriority] = 
      LpHwUnitConfig->stQueueConfig.pTxQueueConfig[LulPriority].ulMaxFrameSize + ETH_FCS_LENGTH;                        /* PRQA S 3383 # JV-01 */
  }
  /* Set EATDQDCq Set descriptor queue depths */

  /* Set EAVCC Set VLAN modes */
  Eth_GaaRSW2_ETHARegs[LulETHAIdx]->ulEAVCC =
    Eth_GpCtrlConfigPtr[LulCtrlIdx].stSWConfig.stTsnaRegValue.ulEAVCCValue;

  /* Set EAVTC Set VLAN TAGs */
  Eth_GaaRSW2_ETHARegs[LulETHAIdx]->ulEAVTC =
    Eth_GpCtrlConfigPtr[LulCtrlIdx].stSWConfig.stTsnaRegValue.ulEAVTCValue;

  /* Set EARTFC Set VLAN TAGs */
  Eth_GaaRSW2_ETHARegs[LulETHAIdx]->ulEARTFC =
    Eth_GpCtrlConfigPtr[LulCtrlIdx].stSWConfig.stTsnaRegValue.ulEARTFCValue;

  /* CBS q setting flow (q from 0 to FRM_PRIO_N-1) */
  Eth_HwETHA_CbsQSettingFlow(LulETHAIdx);

  /* Set EATASIGSC Set TAS initial gate states */
  for (LulQIdx = 0; LulQIdx < (uint32)LpHwUnitConfig->stQueueConfig.ucNumberOfTxQueue; LulQIdx++)
  {
    LulInitGateState |= ((uint32)LpHwUnitConfig->stQueueConfig.pTxQueueConfig[LulQIdx].enInitGateState << LulQIdx);
  }
  Eth_GaaRSW2_ETHARegs[LulETHAIdx]->ulEATASIGSC = LulInitGateState;

  /* Set EATASHCC Set TAS jitter */
  Eth_GaaRSW2_ETHARegs[LulETHAIdx]->ulEATASHCC = LpHwUnitConfig->stTASConfig.ulTxJitter;
  /* TAS setting flow */
  /* In order for TAS to function, it is necessary to acquire the AVTP timer value. */
  /* At this timing, the AVTP timer value cannot be obtained, */
  /* so the TAS setting flow is executed every time the controller is activated. */
}

/***********************************************************************************************************************
** Function Name         : RMAC_InitializationFlow (RSW2)
**
** Service ID            : N/A
**
** Description           : RMAC Initialization Flow
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulRMACIdx : RMAC index
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variable(s)    : Eth_GaaCtrlStat, Eth_GaaRsw2PortCtrlIdx,
**                         Eth_GpEthConfigPtr, Eth_GaaRSW2_RMACRegs,
**                         Eth_GpCtrlConfigPtr
**
** Function(s) invoked   : None
**
** Registers Used        : MRMAC0, MRMAC1, MPIC, MTFFC, MTPFC, MTPFC2, 
**                         MTPFC3t, MRGC, MRFSCE, MRFSCP, MTRC
**
** Reference ID          : ETH_DUD_ACT_480
** Reference ID          : ETH_DUD_ACT_480_GBL001, ETH_DUD_ACT_480_GBL002
** Reference ID          : ETH_DUD_ACT_480_GBL003, ETH_DUD_ACT_480_GBL004
** Reference ID          : ETH_DUD_ACT_480_GBL005, ETH_DUD_ACT_480_GBL006
** Reference ID          : ETH_DUD_ACT_480_GBL007
** Reference ID          : ETH_DUD_ACT_480_GBL009, ETH_DUD_ACT_480_GBL010
** Reference ID          : ETH_DUD_ACT_480_GBL011, ETH_DUD_ACT_480_GBL012
** Reference ID          : ETH_DUD_ACT_480_GBL013, ETH_DUD_ACT_480_GBL014
** Reference ID          : ETH_DUD_ACT_480_GBL015, ETH_DUD_ACT_480_GBL016
** Reference ID          : ETH_DUD_ACT_480_GBL017, ETH_DUD_ACT_480_GBL018
** Reference ID          : ETH_DUD_ACT_480_GBL019, ETH_DUD_ACT_480_GBL020
** Reference ID          : ETH_DUD_ACT_480_REG001, ETH_DUD_ACT_480_REG002
** Reference ID          : ETH_DUD_ACT_480_REG003, ETH_DUD_ACT_480_REG004
** Reference ID          : ETH_DUD_ACT_480_REG006
** Reference ID          : ETH_DUD_ACT_480_REG007, ETH_DUD_ACT_480_REG008
** Reference ID          : ETH_DUD_ACT_480_REG009, ETH_DUD_ACT_480_REG010
** Reference ID          : ETH_DUD_ACT_480_REG011, ETH_DUD_ACT_480_REG012
** Reference ID          : ETH_DUD_ACT_480_REG013, ETH_DUD_ACT_480_REG014
** Reference ID          : ETH_DUD_ACT_480_REG015, ETH_DUD_ACT_480_REG016
** Reference ID          : ETH_DUD_ACT_480_REG017
***********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, ETH_PRIVATE_CODE) RMAC_InitializationFlow(
  CONST(uint32, AUTOMATIC) LulRMACIdx)
{
  /* Figure 28.88 Initialization flow */
  P2CONST(Eth_ETNEConfigType, AUTOMATIC, ETH_APPL_DATA) LpHwUnitConfig;
  uint32 LulRegVal;
  uint32 LulCtrlIdx;
  Std_ReturnType LucResult;

  LucResult = E_OK;

  LulRegVal = 0;

  LulCtrlIdx = Eth_GaaRsw2PortCtrlIdx[ETH_CONV_RMACID_TO_PORTID(LulRMACIdx)];                                           /* PRQA S 3469 # JV-01 */

  LpHwUnitConfig =
    (P2CONST(Eth_ETNEConfigType, AUTOMATIC, ETH_APPL_DATA))Eth_GpCtrlConfigPtr[LulCtrlIdx].pHwUnitConfig;               /* PRQA S 0316 # JV-01 */

  /* Set MAC address write MRMAC0/MRMAC1 */
  /* MRAMAC0 Set */
  Eth_GaaRSW2_RMACRegs[LulRMACIdx]->ulMRMAC0 =                                                                          
    Eth_GaaCtrlStat[LulCtrlIdx].stMacAddr.ulH32 >> 16UL;                                                                
  /* MRAMAC1 Set */
  Eth_GaaRSW2_RMACRegs[LulRMACIdx]->ulMRMAC1 =
    (Eth_GaaCtrlStat[LulCtrlIdx].stMacAddr.ulH32 << 16UL) | Eth_GaaCtrlStat[LulCtrlIdx].stMacAddr.ulL16;

  /* Set xMII function */
  if (ETH_SGMII == Eth_GpEthConfigPtr[LulCtrlIdx].enEthPHYInterface)                                                    /* PRQA S 3416 # JV-01 */
  {
    LulRegVal = ETH_RSW2_RMAC_MPIC_PIS_XGMII;
  }

  LulRegVal |= (uint32) Eth_GpEthConfigPtr[LulCtrlIdx].enEthSpeed << 3UL;

  /* Set duplex mode write MPIC.FHDM */
  if (ETH_HALF_DUPLEX == Eth_GpEthConfigPtr[LulCtrlIdx].enEthDuplex)                                                    /* PRQA S 3416 # JV-01 */
  {
    /* Full / Half-duplex mode select */
    LulRegVal = ETH_RSW2_RMAC_MPIC_FHDM << 7UL;
  } /* else No action required */

  /* Set Station Management Clock write MPIC.PSMCS */
  LulRegVal |= 
    (uint32)(((uint32)LpHwUnitConfig->stPHYConfig.enPSMCaptureTime    << 28UL) |                                        
             ((uint32)LpHwUnitConfig->stPHYConfig.enPSMHoldTime       << 24UL) |  /* Hold time       */
             (LpHwUnitConfig->stPHYConfig.ulPSMClockSelection << 16UL));          /* Clock Selection */
  Eth_GaaRSW2_RMACRegs[LulRMACIdx]->ulMPIC = LulRegVal;

  /* Set Interrupt enable write MEIE, MMIE0, MMIE1, MMEI2 */

  /* Set Tx function write MTFFC, MTPFC, MTPFC2, MTPFC3_t, MTATCt */
  if (ETH_ENABLE == LpHwUnitConfig->stFlowControlConfig.enPauseFrame)
  {
    /* PAUSE mode */
    Eth_GaaRSW2_RMACRegs[LulRMACIdx]->ulMTFFC = (uint32)(ETH_RSW2_RMAC_MTFFC_PAUSE << 1UL);
    Eth_GaaRSW2_RMACRegs[LulRMACIdx]->ulMTPFC =                                   /* Automatic mode */
    (uint32)((LpHwUnitConfig->stFlowControlConfig.ulRetransmissionTime << 16UL) | /* Pause frame retransmission time */
             (LpHwUnitConfig->stFlowControlConfig.ulPauseTime));                  /* Pause Time */
    /* Pause Frame Transmission with TIME = 0 */
    Eth_GaaRSW2_RMACRegs[LulRMACIdx]->ulMTPFC2 =
    (uint32)(((uint32)LpHwUnitConfig->stFlowControlConfig.enPauseTimeZero << 16UL));
    Eth_GaaRSW2_RMACRegs[LulRMACIdx]->ulMTPFC3t[0] = 0x01UL; /* level0 */
  }
  else if (ETH_ENABLE == LpHwUnitConfig->stPFCConfig.enPFCFrame)
  {
    /* PFC mode */
    Eth_GaaRSW2_RMACRegs[LulRMACIdx]->ulMTFFC = (uint32)(ETH_RSW2_RMAC_MTFFC_PFC << 1UL);
    Eth_GaaRSW2_RMACRegs[LulRMACIdx]->ulMTPFC =                           /* Automatic mode */
    (uint32)((LpHwUnitConfig->stPFCConfig.ulRetransmissionTime << 16UL) | /* Pause frame retransmission time(PFC) */
             (LpHwUnitConfig->stPFCConfig.ulPauseTime ));                 /* Pause Time(PFC) */
    /* PFC Frame Transmission with TIME = 0 PRO LVL 1 */
    /* PFC Frame Transmission with TIME = 0 PRO LVL 0 */
    Eth_GaaRSW2_RMACRegs[LulRMACIdx]->ulMTPFC2 =
    (uint32)(((uint32)LpHwUnitConfig->stPFCConfig.enPauseTimeZero << 1UL) | 
             ((uint32)LpHwUnitConfig->stPFCConfig.enPauseTimeZero));
    /* level0 */
    Eth_GaaRSW2_RMACRegs[LulRMACIdx]->ulMTPFC3t[0] = LpHwUnitConfig->stPFCConfig.stPFCPauseLevelConfig[0]
                                                                                                       .ulPausePriority;
    /* level1 */
    Eth_GaaRSW2_RMACRegs[LulRMACIdx]->ulMTPFC3t[1] = LpHwUnitConfig->stPFCConfig.stPFCPauseLevelConfig[1]
                                                                                                       .ulPausePriority;
  }
  else
  {
    /* else No action required */
  }

  /* Set Rx function write MRGC, MRFSCE, MRFSCP, MTRC */
  if (ETH_ENABLE == LpHwUnitConfig->stFlowControlConfig.enPauseFrame)
  {
    /* PAUSE mode */
    Eth_GaaRSW2_RMACRegs[LulRMACIdx]->ulMRGC =
    (uint32)(((uint32)LpHwUnitConfig->stFlowControlConfig.enPauseTimeZero << 2UL) | 
             ((uint32)LpHwUnitConfig->stFlowControlConfig.enPauseFrame    << 1UL)); 
  }
  else if (ETH_ENABLE == LpHwUnitConfig->stPFCConfig.enPFCFrame)
  {
    /* PFC mode */
    /* PFC Frame Reception Control */
    /* Pause or PFC Frame Reception with Time = 0 */
    Eth_GaaRSW2_RMACRegs[LulRMACIdx]->ulMRGC =
    (uint32)(((LpHwUnitConfig->stPFCConfig.stPFCPauseLevelConfig[0].ulPausePriority |
               (uint32)LpHwUnitConfig->stPFCConfig.stPFCPauseLevelConfig[1].ulPausePriority) << 16UL) |
              ((uint32)LpHwUnitConfig->stPFCConfig.enPauseTimeZero << 2UL));
  }
  else
  {
    /* else No action required */
  }

  /* Correct FCS is not passed to the MHD on current RMAC settings. (MRGC register) */
  /* So, no need to add FCS size */
  Eth_GaaRSW2_RMACRegs[LulRMACIdx]->ulMRFSCE = Eth_GulRxMaxFrameSize;
  Eth_GaaRSW2_RMACRegs[LulRMACIdx]->ulMRFSCP = Eth_GulRxMaxFrameSize;

  #if (ETH_GLOBAL_TIME_SUPPORT == STD_ON)
  Eth_GaaRSW2_RMACRegs[LulRMACIdx]->ulMTRC = ETH_RSW2_RMAC_MTRC_TRHFME_ENABLE << ETH_GPTP_TIMER_DOMAIN;
  #endif

  /* Setting for loopback mode - MAC Loopback configuration */
  if (ETH_ENABLE == Eth_GpEthConfigPtr[LulCtrlIdx].enInternalLoopBackMode)                                              /* PRQA S 3416 # JV-01 */
  {
    Eth_GaaRSW2_RMACRegs[LulRMACIdx]->ulMLBC = ETH_ETNE_MLBC_CONFIG;
  } /* else No action required */

  /* Set Address Filtering function write MRSCE, MRSCP, MRAFC */

  /* Set PTP Filtering function write MPFCt */

  /* Set XGMII function write MXGMIIC, MPCH, MANMt */

  /* Setting SGMII mode for ETHA */
  if (ETH_SGMII == Eth_GpEthConfigPtr[LulCtrlIdx].enEthPHYInterface)                                                    /* PRQA S 3416 # JV-01 */
  {
    LucResult = Eth_SGMIIInit(LulCtrlIdx, LpHwUnitConfig->enBypassMode);
  } /* else: No action required */

  if (E_OK == LucResult)
  {
    /* Link Verification */
    LucResult = Eth_HwRMAC_LinkVerification(LulCtrlIdx);
  } /* else: No action required */

  return LucResult;
}

/***********************************************************************************************************************
** Function Name         : Eth_SGMIIInit (ETNE)
**
** Service ID            : N/A
**
** Description           : Initialize SGMII for ETND/ETNE HWUnit
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : LulCtrlIdx : Index of a controller
**                       : LenBypassMode : Bypass mode
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variable(s)    : Eth_GstETNE_Regs
**
** Function(s) invoked   : None
**
** Registers Used        : ulETNEzSGSRST, ucETNEzSGSDS, ucETNEzSGCLKSEL, ucETNEzSGRCIE, ulETNEzSGINTM
**
** Reference ID          : ETH_DUD_ACT_326,
** Reference ID          : ETH_DUD_ACT_326_REG001, ETH_DUD_ACT_326_REG002
** Reference ID          : ETH_DUD_ACT_326_REG003, ETH_DUD_ACT_326_REG004
** Reference ID          : ETH_DUD_ACT_326_REG005, ETH_DUD_ACT_326_REG006
** Reference ID          : ETH_DUD_ACT_326_REG007
***********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_SGMIIInit(
  CONST(uint32, AUTOMATIC) LulCtrlIdx,
  CONST(Eth_OptionType, AUTOMATIC) LenBypassMode)
{
  uint8 LucRegVal;
  Std_ReturnType LucResult;
  TickType LulTickStart;
  TickType LulTickElap;

  CONSTP2VAR(volatile Eth_ETNE_SGMIIRegType, AUTOMATIC, REGSPACE) LpSgmiiRegs = Eth_GstETNE_Regs.pSGMII[LulCtrlIdx];    

  LucResult = E_OK;

  /* Execute SW-Reset on SGMII interface */
  LpSgmiiRegs->ulETNEzSGSRST = ETH_ETNE_SGSRST_SRST;                                                                    
  LpSgmiiRegs->ulETNEzSGSRST = 0UL;

  /* Wait 4us */
  Eth_WaitNanoSec(ETH_ETNE_WAIT_FOR_SGMII);

  /* Wait until the power supply for the SGMII SerDes is turned on */
  /* (ETNB1SGSDS.PWS[1:0] == 11B) */
  LulTickStart = 0UL;
  LulTickElap = 0UL;
  (void)GetCounterValue(ETH_OS_COUNTER_ID, &LulTickStart);
  do
  {
    LulTickElap = LulTickElap + Eth_GetElapsedTimeValue(&LulTickStart);                                                 /* PRQA S 3383 # JV-01 */
    LucRegVal = (uint8)LpSgmiiRegs->stPWRCTL.ucETNEzSGSDS & ETH_ETNE_SGSDS_PWS_ON;
  } while ((LucRegVal != ETH_ETNE_SGSDS_PWS_ON) && (LulTickElap <= ETH_TIMEOUT_COUNT));

  if (ETH_TIMEOUT_COUNT < LulTickElap)
  {
    /* Timeout */
    LucResult = E_NOT_OK;
  } /* else: No action required */

  /* Select the reference clock */
  LpSgmiiRegs->stPWRCTL.ucETNEzSGCLKSEL = ETH_ETNE_SGCLKSEL_SEL;

  /* Wait until the reference clock which is supplied by the external
    oscillator or the internal MainOSC becomes stable */

  /* Enable the reference clock input */
  LpSgmiiRegs->stPWRCTL.ucETNEzSGRCIE = ETH_ETNE_SGRCIE_RCIE;

  /* Wait until the SerDes startup is completed */
  LulTickStart = 0UL;
  LulTickElap = 0UL;
  (void)GetCounterValue(ETH_OS_COUNTER_ID, &LulTickStart);
  do
  {
    LulTickElap = LulTickElap + Eth_GetElapsedTimeValue(&LulTickStart);                                                 /* PRQA S 3383 # JV-01 */
    LucRegVal = (uint8)LpSgmiiRegs->stPWRCTL.ucETNEzSGSDS & ETH_ETNE_SGSDS_SUC;
  } while ((LucRegVal != ETH_ETNE_SGSDS_SUC) && (LulTickElap <= ETH_TIMEOUT_COUNT));

  if (ETH_TIMEOUT_COUNT < LulTickElap)
  {
    /* Timeout */
    LucResult = E_NOT_OK;
  } /* else: No action required */

  if (ETH_ENABLE == LenBypassMode)
  {
    /* Manual set the operation mode */
    switch (Eth_GpEthConfigPtr[LulCtrlIdx].enEthSpeed)
    {
    case ETH_MAC_LAYER_SPEED_10M:
      /* Set operation mode to 10base */
      LpSgmiiRegs->ulETNEzSGOPMC = ETH_ETNE_SGOPMC_10M;
      break;
    case ETH_MAC_LAYER_SPEED_100M:
      /* Set operation mode to 100base */
      LpSgmiiRegs->ulETNEzSGOPMC = ETH_ETNE_SGOPMC_100M;
      break;
    default:
      /* Set operation mode to 1000base */
      LpSgmiiRegs->ulETNEzSGOPMC = ETH_ETNE_SGOPMC_1G;
      break;
    }
  } /* else: No action required */

  /* Enable Ready Interrupt */
  LpSgmiiRegs->ulETNEzSGINTM = ~((uint32)ETH_ETNE_SGINTM_URDYIM | (uint32)ETH_ETNE_SGINTM_RDYIM);

  return LucResult;
}

#define ETH_STOP_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define ETH_START_SEC_CODE_FAST
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#if ((ETH_CTRL_ENABLE_TX_INTERRUPT == STD_ON) || (ETH_CTRL_ENABLE_RX_INTERRUPT == STD_ON))
/***********************************************************************************************************************
** Function Name         : Eth_Gwca_DIS_Common_Isr (RSW2)
**
** Service ID            : N/A
**
** Description           : GWCA Data ISR
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulGWCAIdx : GWCA index
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : (ETH_CTRL_ENABLE_TX_INTERRUPT == STD_ON)
**                         || (ETH_CTRL_ENABLE_RX_INTERRUPT == STD_ON)
**
** Global Variable(s)    : Eth_GstDescChainMap, Eth_GaaRSW2_GWCARegs,
**                       : Eth_GaaDemEventUnintendedIntChk
**
** Function(s) invoked   : Eth_RxQueueProcess, Eth_TxConfirmationQueueProcess
**                       : Eth_DemConfigCheck
**
** Registers Used        : GWDISi, GWDIEi
**
** Reference ID          : ETH_DUD_ACT_443
** Reference ID          : ETH_DUD_ACT_443_REG001, ETH_DUD_ACT_443_REG002
** Reference ID          : ETH_DUD_ACT_443_REG003
** Reference ID          : ETH_DUD_ACT_443_GLB001, ETH_DUD_ACT_443_GLB002
** Reference ID          : ETH_DUD_ACT_443_GLB003, ETH_DUD_ACT_443_GLB004
** Reference ID          : ETH_DUD_ACT_443_GLB005, ETH_DUD_ACT_443_GLB006
***********************************************************************************************************************/
FUNC(void, ETH_CODE_FAST) Eth_Gwca_DIS_Common_Isr(                                                                   
  CONST(uint32, AUTOMATIC) LulGWCAIdx)
{
  Eth_ExtRxStatusType LenRetValue;
  P2CONST(Eth_DescChainInfo, AUTOMATIC, ETH_APPL_DATA) LpChainInfo;
  uint32 LulRegVal[ETH_RACE_AXI_CHAIN_N / ETH_RSW2_GWCA_NUM_OF_CHAIN_PER_REG];
  uint32 LulIdx;
  uint8 LucTargetChainId;
#if (ETH_UNINTENDED_INTERRUPT_CHECK == STD_ON)
  boolean LblStatusFail;
  boolean LblEnableFail;
  uint32 LulUnintBit;

  LblStatusFail = ETH_TRUE;
  LblEnableFail = ETH_FALSE;
#endif

  for (LulIdx = 0; LulIdx < (ETH_RACE_AXI_CHAIN_N / ETH_RSW2_GWCA_NUM_OF_CHAIN_PER_REG); LulIdx++)
  {
    /* Get GWCA Data Interrupt Status */
    LulRegVal[LulIdx] = Eth_GaaRSW2_GWCARegs[LulGWCAIdx]->GWDI[LulIdx].ulGWDISi;                                        

    /* Clear GWCA Data Interrupt Status */
    Eth_GaaRSW2_GWCARegs[LulGWCAIdx]->GWDI[LulIdx].ulGWDISi = LulRegVal[LulIdx];

#if (ETH_UNINTENDED_INTERRUPT_CHECK == STD_ON)
    /* Unintended Interrupt Check */
    if (0UL != LulRegVal[LulIdx])
    {
      /* Status Check is successful */
      LblStatusFail = ETH_FALSE;
      
      LulUnintBit = (~(Eth_GaaRSW2_GWCARegs[LulGWCAIdx]->GWDI[LulIdx].ulGWDIEi)) & LulRegVal[LulIdx];
      if (0UL != LulUnintBit)
      {
        /* Enable Check is failed */
        LblEnableFail = ETH_TRUE;
        
        /* Mask to avoid handling unintended interrupts */
        LulRegVal[LulIdx] &= ~(LulUnintBit);
      } /* else No action required */
    } /* else No action required */
#endif
  }

#if (ETH_UNINTENDED_INTERRUPT_CHECK == STD_ON)
  if ((ETH_TRUE == LblStatusFail) || (ETH_TRUE == LblEnableFail))
  {
    /* Issue DEM Error to all Controller */
    for (LulIdx = 0; LulIdx < (uint32)ETH_ETNE_CTRLS_SUPPORTED; LulIdx++)
    {
      Eth_DemConfigCheck(Eth_GpDemEventUnintendedIntChk[LulIdx], DEM_EVENT_STATUS_FAILED);                              
    }
  } /* else No action required */
#endif

  for (LulIdx = 0UL;  LulIdx < Eth_GstDescChainMap.ulValidChainNum; LulIdx++)
  {
    /* Get Target Chain Id */
    LucTargetChainId = Eth_GstDescChainMap.ucValidChainId[LulIdx];                                                      
    
    /* Check the Data Interrupt Status bit for Target Chain */
    if (0UL != (LulRegVal[LucTargetChainId / ETH_RSW2_GWCA_NUM_OF_CHAIN_PER_REG]                                        
              & (1UL << (LucTargetChainId % ETH_RSW2_GWCA_NUM_OF_CHAIN_PER_REG))))
    {
      LpChainInfo = &Eth_GstDescChainMap.aaChainInfo[LucTargetChainId];                                                 
     
      if (ETH_RX_RSW2 == LpChainInfo->enDir)                                                                            
      {
        do
        {
          /* Update Descriptor */
          LenRetValue = Eth_RxQueueProcess(LpChainInfo->ulCtrlIdx, (uint8)LpChainInfo->ulFifoIdx);
        } while ((ETH_EXT_RECEIVED_MORE_DATA_AVAILABLE == LenRetValue) || 
                 (ETH_EXT_NOT_RECEIVED_MORE_DATA_AVAILABLE == LenRetValue));
      }
      else
      {
        /* Tx Confirmation Process */
        Eth_TxConfirmationQueueProcess(LpChainInfo->ulCtrlIdx, (uint8)LpChainInfo->ulFifoIdx);
      }
    }
  }
}
#endif /* ((ETH_CTRL_ENABLE_TX_INTERRUPT == STD_ON) || (ETH_CTRL_ENABLE_RX_INTERRUPT == STD_ON)) */

#if (ETH_GWCA0_TSDATA_ISR == STD_ON)
/***********************************************************************************************************************
** Function Name         : Eth_Gwca_TSDIS_Common_Isr
**
** Service ID            : NA
**
** Description           : GWCA TS Data ISR
**
** Sync/Async            : NA
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulCtrlIdx
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variable(s)    : Eth_GaaTsDescChain, Eth_GpNextTsDesc,
**                         Eth_GaaRSW2_GWCARegs, Eth_GpCtrlConfigPtr
**                         Eth_GaaDemEventUnintendedIntChk
**
** Function(s) invoked   : Eth_TxConfirmationQueueProcess, Eth_DemConfigCheck
**
** Registers Used        : GWTSDIS, GWTSDIE
**
** Reference ID          : ETH_DUD_ACT_495
** Reference ID          : ETH_DUD_ACT_495_GBL001, ETH_DUD_ACT_495_GBL002
** Reference ID          : ETH_DUD_ACT_495_GBL003, ETH_DUD_ACT_495_GBL004
** Reference ID          : ETH_DUD_ACT_495_GBL005, ETH_DUD_ACT_495_GBL006
** Reference ID          : ETH_DUD_ACT_495_GBL007, ETH_DUD_ACT_495_GBL008
** Reference ID          : ETH_DUD_ACT_495_REG001, ETH_DUD_ACT_495_REG002
** Reference ID          : ETH_DUD_ACT_495_REG003
***********************************************************************************************************************/
FUNC(void, ETH_CODE_FAST) Eth_Gwca_TSDIS_Common_Isr(CONST(uint32, AUTOMATIC) LulGWCAIdx)                             
{
  P2VAR(Eth_BufHandlerType, AUTOMATIC, ETH_APPL_DATA) LpTxBufferNode;                                                   /* PRQA S 3432 # JV-01 */
  P2VAR(Eth_BasicDescType, AUTOMATIC, ETH_APPL_DATA) LpLinkDesc;                                                        /* PRQA S 3432, 3678 # JV-01, JV-01 */
  uint32 LulCtrlIdx;
  uint32 LulBufIdx;
  uint32 LulReg;
#if (ETH_UNINTENDED_INTERRUPT_CHECK == STD_ON)
  boolean LblStatusFail;
  boolean LblEnableFail;

  LblStatusFail = ETH_FALSE;
  LblEnableFail = ETH_FALSE;
#endif

  LulReg = Eth_GaaRSW2_GWCARegs[LulGWCAIdx]->ulGWTSDIS;                                                                 

  /* Clear the TS Descriptor Data Interrupt Status bit */
  Eth_GaaRSW2_GWCARegs[LulGWCAIdx]->ulGWTSDIS = LulReg;

  if (0UL != (LulReg & (ETH_GPTP_TIMER_DOMAIN_ENABLE << ETH_GPTP_TIMER_DOMAIN)))
  {
#if (ETH_UNINTENDED_INTERRUPT_CHECK == STD_ON)
    if (0UL == (Eth_GaaRSW2_GWCARegs[ETH_RSW2_GWCA_ID]->ulGWTSDIE & ETH_GPTP_TIMER_DOMAIN_MASK))
    {
      /* Enable Check is failed */
      LblEnableFail = ETH_TRUE;
    }
    else
#endif
    {
      /* Search timestamp descriptor */
      while (ETH_DESC_FSINGLE == Eth_GpNextTsDesc->ulDt)                                                                
      {
        LulBufIdx = Eth_GpNextTsDesc->ulTsun % ETH_TX_DESCR_TSUN_OFFSET;                                                
        LulCtrlIdx = (uint32)(Eth_GpNextTsDesc->ulTsun / ETH_TX_DESCR_TSUN_OFFSET);                                     
        if (NULL_PTR != Eth_GaaTxBufferMgrTable[LulCtrlIdx][LulBufIdx].pBufferHdr)                                      
        {
          LpTxBufferNode = (Eth_BufHandlerType *)Eth_GaaTxBufferMgrTable[LulCtrlIdx][LulBufIdx].pBufferHdr;

          /* Read timestamp value to Tx buffer */
          LpTxBufferNode->stTimeStamp.nanoseconds = Eth_GpNextTsDesc->stTimestamp.ulTSNS;                               
          LpTxBufferNode->stTimeStamp.seconds     = Eth_GpNextTsDesc->stTimestamp.ulTSS;
          LpTxBufferNode->stTimeStamp.secondsHi   = (uint16)0U;

          /* Set timestamp quality information as ETH_VALID */
          LpTxBufferNode->enTimeQual = ETH_VALID;

          if (ETH_ENABLE == Eth_GpCtrlConfigPtr[LulCtrlIdx].pEthConfig->enTxInterruptMode)                              /* PRQA S 3416 # JV-01 */
          {
            Eth_TxConfirmationQueueProcess(LulCtrlIdx, LpTxBufferNode->ucPriority);
          }
        }
        /* Release timestamp descriptor */
        Eth_GpNextTsDesc->ulDs    = 0U;                                                                                 
        Eth_GpNextTsDesc->ulInfo0 = 0U;
        Eth_GpNextTsDesc->ulErr   = 0U;
        Eth_GpNextTsDesc->ulDse   = 0U;
        Eth_GpNextTsDesc->ulAxie  = 0U;
        Eth_GpNextTsDesc->ulDie   = 1U;
        Eth_GpNextTsDesc->stTimestamp.ulTSNS    = 0U;
        Eth_GpNextTsDesc->stTimestamp.ulTSS     = 0U;
        Eth_GpNextTsDesc->ulDt = ETH_DESC_FEMPTY_ND;

        /* Set descriptor to be read next */
        Eth_GpNextTsDesc++;                                                                                             
        while (Eth_GpNextTsDesc->ulDt == ETH_DESC_LINKFIX_RSW2)                                                         
        {
          LpLinkDesc = (P2VAR(Eth_BasicDescType, AUTOMATIC, ETH_APPL_DATA))Eth_GpNextTsDesc;                            /* PRQA S 3432, 0310 # JV-01, JV-01 */
          Eth_GpNextTsDesc = (P2VAR(Eth_TSDescType, AUTOMATIC, ETH_APPL_DATA))LpLinkDesc->ulDptr;                       /* PRQA S 3432, 0306 # JV-01, JV-01 */
        }
      }
    }
  }
  else
  {
#if (ETH_UNINTENDED_INTERRUPT_CHECK == STD_ON)
    /* Status Check is failed */
    LblStatusFail = ETH_TRUE;
#else
    /* No Action Required */
#endif
  }

#if (ETH_UNINTENDED_INTERRUPT_CHECK == STD_ON)
  if ((ETH_TRUE == LblStatusFail) || (ETH_TRUE == LblEnableFail))
  {
    /* Issue DEM Error to all Controller */
    for (LulCtrlIdx = 0; LulCtrlIdx < (uint32)ETH_ETNE_CTRLS_SUPPORTED; LulCtrlIdx++)
    {
      Eth_DemConfigCheck(Eth_GpDemEventUnintendedIntChk[LulCtrlIdx], DEM_EVENT_STATUS_FAILED);                          
    }
  } /* else No action required */
#endif
}
#endif /* ETH_GLOBAL_TIME_SUPPORT == STD_ON */

#if (ETH_GWCA0_ERR_ISR == STD_ON)
/***********************************************************************************************************************
** Function Name         : Eth_Gwca_ERR_Common_Isr (RSW2)
**
** Service ID            : N/A
**
** Description           : GWCA Error ISR
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulGWCAIdx : Index of a GWCA
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : void
**
** Preconditions         : (ETH_GWCA0_ERR_ISR == STD_ON)
**
** Global Variable(s)    : Eth_GaaRSW2_GWCARegs, Eth_GpDemEventUnintendedIntChk
**                         Eth_GpDemEventDmaError, Eth_GpDemEventEccError
**
** Function(s) invoked   : Eth_DemConfigCheck
**
** Registers Used        : GWEIS0
**
** Reference ID          : ETH_DUD_ACT_514
** Reference ID          : ETH_DUD_ACT_514_GBL001, ETH_DUD_ACT_514_GBL002
** Reference ID          : ETH_DUD_ACT_514_GBL003, ETH_DUD_ACT_514_GBL004
** Reference ID          : ETH_DUD_ACT_514_GBL005
** Reference ID          : ETH_DUD_ACT_514_REG001, ETH_DUD_ACT_514_REG002
***********************************************************************************************************************/
FUNC(void, ETH_CODE_FAST) Eth_Gwca_ERR_Common_Isr(                                                                   
  CONST(uint32, AUTOMATIC) LulGWCAIdx)
{
  uint32 LulRegVal;
  uint32 LulIdx;

  /* Get GWCA Error Interrupt Status */
  LulRegVal = Eth_GaaRSW2_GWCARegs[LulGWCAIdx]->ulGWEIS0;                                                               

  /* Clear GWCA Error Interrupt Status */
  Eth_GaaRSW2_GWCARegs[LulGWCAIdx]->ulGWEIS0 = LulRegVal;

#if (ETH_UNINTENDED_INTERRUPT_CHECK == STD_ON)
  /* Unintended Interrupt Check */
  if (0UL == LulRegVal)
  {
    /* Issue DEM Error to all Controller */
    for (LulIdx = 0; LulIdx < (uint32)ETH_ETNE_CTRLS_SUPPORTED; LulIdx++)
    {
      Eth_DemConfigCheck(Eth_GpDemEventUnintendedIntChk[LulIdx], DEM_EVENT_STATUS_FAILED);                              
    }
  } /* else No action required */
#endif

  /* Check AXI Bus Error */
  if (0UL != (LulRegVal & ETH_RSW2_GWCA_DMA_ERROR_MASK))
  {
    /* Issue DEM Error to all Controller */
    for (LulIdx = 0; LulIdx < (uint32)ETH_ETNE_CTRLS_SUPPORTED; LulIdx++)
    {
      Eth_DemConfigCheck(Eth_GpDemEventDmaError[LulIdx], DEM_EVENT_STATUS_FAILED);                                      
    }
  } /* else No action required */

  /* Check ECC Error */
  if (0UL != (LulRegVal & ETH_RSW2_GWCA_ECC_ERROR_MASK))
  {
    /* Issue DEM Error to all Controller */
    for (LulIdx = 0; LulIdx < (uint32)ETH_ETNE_CTRLS_SUPPORTED; LulIdx++)
    {
      Eth_DemConfigCheck(Eth_GpDemEventEccError[LulIdx], DEM_EVENT_STATUS_FAILED);                                      
    }
  } /* else No action required */
}
#endif /* (ETH_GWCA0_ERR_ISR == STD_ON) */

#if (ETH_COMA_ERR_ISR == STD_ON)
/***********************************************************************************************************************
** Function Name         : Eth_Coma_ERR_Common_Isr (RSW2)
**
** Service ID            : N/A
**
** Description           : COMA Error ISR
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
** Return parameter      : void
**
** Preconditions         : (ETH_COMA_ERR_ISR == STD_ON)
**
** Global Variable(s)    : Eth_GpRSW2_COMARegs, Eth_GpDemEventUnintendedIntChk
**                         Eth_GpDemEventEccError
**
** Function(s) invoked   : Eth_DemConfigCheck
**
** Registers Used        : CAEIS0
**
** Reference ID          : ETH_DUD_ACT_515
** Reference ID          : ETH_DUD_ACT_515_GBL001, ETH_DUD_ACT_515_GBL002
** Reference ID          : ETH_DUD_ACT_515_GBL003, ETH_DUD_ACT_515_GBL004
** Reference ID          : ETH_DUD_ACT_515_REG001, ETH_DUD_ACT_515_REG002
***********************************************************************************************************************/
FUNC(void, ETH_CODE_FAST) Eth_Coma_ERR_Common_Isr(void)                                                              
{
  uint32 LulRegVal;
  uint32 LulIdx;

  /* Get COMA Error Interrupt Status */
  LulRegVal = Eth_GpRSW2_COMARegs->ulCAEIS0;

  /* Clear COMA Error Interrupt Status */
  Eth_GpRSW2_COMARegs->ulCAEIS0 = LulRegVal;

#if (ETH_UNINTENDED_INTERRUPT_CHECK == STD_ON)
  /* Unintended Interrupt Check */
  if (0UL == LulRegVal)
  {
    /* Issue DEM Error to all Controller */
    for (LulIdx = 0; LulIdx < (uint32)ETH_ETNE_CTRLS_SUPPORTED; LulIdx++)
    {
      Eth_DemConfigCheck(Eth_GpDemEventUnintendedIntChk[LulIdx], DEM_EVENT_STATUS_FAILED);                              
    }
  } /* else No action required */
#endif

  /* Check ECC Error */
  if (0UL != (LulRegVal & ETH_RSW2_COMA_ECC_ERROR_MASK))
  {
    /* Issue DEM Error to all Controller */
    for (LulIdx = 0; LulIdx < (uint32)ETH_ETNE_CTRLS_SUPPORTED; LulIdx++)
    {
      Eth_DemConfigCheck(Eth_GpDemEventEccError[LulIdx], DEM_EVENT_STATUS_FAILED);                                      
    }
  } /* else No action required */
}
#endif /* (ETH_COMA_ERR_ISR == STD_ON) */

#if ((ETH_ETHA0_ERR_ISR == STD_ON) || (ETH_ETHA1_ERR_ISR == STD_ON))
/***********************************************************************************************************************
** Function Name         : Eth_Etha_ERR_Common_Isr (RSW2)
**
** Service ID            : N/A
**
** Description           : ETHA Error ISR
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulETHAIdx : Index of a ETHA
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : void
**
** Preconditions         : (ETH_ETHA0_ERR_ISR == STD_ON)
**                         || (ETH_ETHA1_ERR_ISR == STD_ON)
**
** Global Variable(s)    : Eth_GaaRSW2_ETHARegs, Eth_GaaRsw2PortValid
**                         Eth_GaaRsw2PortCtrlIdx, Eth_GpDemEventUnintendedIntChk
**                         Eth_GpDemEventEccError
**
** Function(s) invoked   : Eth_DemConfigCheck
**
** Registers Used        : EAEIS0
**
** Reference ID          : ETH_DUD_ACT_516
** Reference ID          : ETH_DUD_ACT_516_GBL001, ETH_DUD_ACT_516_GBL002
** Reference ID          : ETH_DUD_ACT_516_GBL003, ETH_DUD_ACT_516_GBL004
** Reference ID          : ETH_DUD_ACT_516_GBL005, ETH_DUD_ACT_516_GBL006
** Reference ID          : ETH_DUD_ACT_516_REG001, ETH_DUD_ACT_516_REG002
***********************************************************************************************************************/
FUNC(void, ETH_CODE_FAST) Eth_Etha_ERR_Common_Isr(                                                                      
  CONST(uint32, AUTOMATIC) LulETHAIdx)
{
  uint32 LulRegVal;
  uint32 LulIdx;

  /* Get ETHA Error Interrupt Status */
  LulRegVal = Eth_GaaRSW2_ETHARegs[LulETHAIdx]->ulEAEIS0;                                                               
  /* Clear ETHA Error Interrupt Status */
  Eth_GaaRSW2_ETHARegs[LulETHAIdx]->ulEAEIS0 = LulRegVal;
  if (ETH_TRUE == Eth_GaaRsw2PortValid[ETH_CONV_ETHAID_TO_PORTID(LulETHAIdx)])                                          /* PRQA S 3469 # JV-01 */
  {
    LulIdx = Eth_GaaRsw2PortCtrlIdx[ETH_CONV_ETHAID_TO_PORTID(LulETHAIdx)];                                             /* PRQA S 3469 # JV-01 */

    #if (ETH_UNINTENDED_INTERRUPT_CHECK == STD_ON)
    /* Unintended Interrupt Check */
    if (0UL == LulRegVal)
    {
      /* Issue DEM Error to corresponding Controller */
      Eth_DemConfigCheck(Eth_GpDemEventUnintendedIntChk[LulIdx], DEM_EVENT_STATUS_FAILED);                              
    } /* else No action required */
    #endif

    /* Check ECC Error */
    if (0UL != (LulRegVal & ETH_RSW2_ETHA_ECC_ERROR_MASK))
    {
      /* Issue DEM Error to corresponding Controller */
      Eth_DemConfigCheck(Eth_GpDemEventEccError[LulIdx], DEM_EVENT_STATUS_FAILED);                                      
    } /* else No action required */
  } /* else No action required */
}
#endif /* ((ETH_ETHA0_ERR_ISR == STD_ON) || (ETH_ETHA1_ERR_ISR == STD_ON)) */

#if (ETH_SGMII_ISR == STD_ON)
/***********************************************************************************************************************
** Function Name         : Eth_Etha_SGMII_Common_Isr (RSW2)
**
** Service ID            : N/A
**
** Description           : Service to handle interrupt for SGMII
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
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variable(s)    : Eth_GstETNE_Regs, Eth_GpDemEventIntInconsistent
**
** Function(s) invoked   : Eth_DemConfigCheck
**
** Registers Used        : ETNEzSGINTS, ETNEzSGOPMS, MPIC
**
** Reference ID          : ETH_DUD_ACT_535
** Reference ID          : ETH_DUD_ACT_535_REG001, ETH_DUD_ACT_535_REG002,
** Reference ID          : ETH_DUD_ACT_535_REG003, ETH_DUD_ACT_535_REG004,
****************************************** ****************************************************************************/
FUNC(void, ETH_CODE_FAST) Eth_Etha_SGMII_Common_Isr(CONST(uint32, AUTOMATIC) LulCtrlIdx)                                
{
  uint32 LulRegVal;
  uint32 LulLinkState;
  CONSTP2VAR(volatile Eth_ETNE_SGMIIRegType, AUTOMATIC, REGSPACE) LpSgmiiRegs = Eth_GstETNE_Regs.pSGMII[LulCtrlIdx];    

  #if (ETH_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  if (0UL == (LpSgmiiRegs->ulETNEzSGINTS & (uint32)ETH_ETNE_SGINTS_RDY_UNRDY))                                          
  {
    Eth_DemConfigCheck(Eth_GpDemEventIntInconsistent[LulCtrlIdx], DEM_EVENT_STATUS_FAILED);                             
  }
  else
  #endif
  {
    LulRegVal = LpSgmiiRegs->ulETNEzSGINTS;                                                                             
    LulLinkState = LpSgmiiRegs->ulETNEzSGOPMS;
    if ((ETH_ETNE_SGINTS_RDY == LulRegVal) ||
      ((ETH_ETNE_SGINTS_RDY_UNRDY == LulRegVal) && (ETH_SGOPMS_DATA_COM == (LulLinkState & ETH_SGOPMS_XMIT_MASK))))
    {
      Eth_GaaRSW2_RMACRegs[LulCtrlIdx]->ulMPIC =                                                                        
        (Eth_GaaRSW2_RMACRegs[LulCtrlIdx]->ulMPIC & ~ETH_SGOPMS_SPEED_MASK) | (LulLinkState & ETH_SGOPMS_SPEED_MASK);
    }
    else
    {
      Eth_GaaRSW2_RMACRegs[LulCtrlIdx]->ulMPIC &= ~ETH_SGOPMS_SPEED_MASK;
    }
    LpSgmiiRegs->ulETNEzSGINTS = LulRegVal;
  }
}
#endif /* #if (ETH_SGMII_ISR == STD_ON) */

#define ETH_STOP_SEC_CODE_FAST
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* (ETH_USING_MACRO == ETH_MACRO_ETNE) */

/***********************************************************************************************************************
**                                                  End of File                                                       **
***********************************************************************************************************************/