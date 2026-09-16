/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Eth_Ram.c                                                                                           */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2023 - 2025 Renesas Electronics Corporation. All rights reserved.                                              */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Global RAM variable definitions for Eth Driver an RAM allocation functions                                         */
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
 * 2.4.1: 30/06/2025    : Remove the SW-VERSION from header of file
 * 2.4.0: 30/06/2025    : Update SW-VERSION for RH850/Ver22.01.00 (D) U2Ax release
 * 2.3.1: 31/03/2025    : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 * 2.3.0: 28/02/2025    : Updated QA-C 9.5.0 comments
 * 2.2.0: 31/12/2024    : Update SW-VERSION for Ver22.02.00(D) U2Bx Final Release
 *        26/11/2024    : Updated QA-C 9.5.0 comments
 * 2.1.2: 31/10/2024    : Increase SW-VERSION to 2.1.2
 * 2.1.1: 22/07/2024    : Update QAC message
 *        16/07/2024    : Add Eth_GpDemEventUnintendedIntChk
 *        31/05/2024    : Add declare of Eth_GaaRxBufferIndex
 * 2.0.2: 17/04/2024    : Update QAC message.
 *        15/04/2024    : Add declare of Eth_GpCoreId2Index, Eth_GpDriverState, Eth_GpTotalCtrlConfig, Eth_CtrlConfigIdx
 *        28/03/2024    : Add declare of Eth_GpDemEventAccess, Eth_GpDemEventRxFramesLost, Eth_GpDemEventCRC,
 *                        Eth_GpDemEventUnderSizeFrame, Eth_GpDemEventOverSizeFrame, Eth_GpDemEventAlignment,
 *                        Eth_GpDemEventSinglecollision, Eth_GpDemEventMultiplecollision, Eth_GpDemEventLatecollision,
 *                        Eth_GpDemEventIntInconsistent, Eth_GpDemEventDmaError, Eth_GpDemEventEccError,
 *                        Eth_GpDemEventTimerincFailed, Eth_GpDemEventRegisterCorruption,
 *                        Eth_GpDemEventTimeroffsetFailed.
 *        18/03/2024    : Remove define of Eth_GenDriverState.
 *        26/11/2023    : Initial Version
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for Eth.h inclusion and macro definitions */
#include "Eth.h"
/* Header file inclusion */
#include "Eth_Ram.h"
#if (ETH_ETHSWITCH_MANAGEMENT_SUPPORT == STD_ON)
#include "EthSwt_Cbk.h"
#endif

#if (ETH_CRITICAL_SECTION_PROTECTION == STD_ON)
/* Included for the declaration of the critical section protection functions */
#include "SchM_Eth.h"
#endif

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define ETH_RAM_C_AR_RELEASE_MAJOR_VERSION ETH_AR_RELEASE_MAJOR_VERSION_VALUE
#define ETH_RAM_C_AR_RELEASE_MINOR_VERSION ETH_AR_RELEASE_MINOR_VERSION_VALUE
#define ETH_RAM_C_AR_RELEASE_REVISION_VERSION ETH_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define ETH_RAM_C_SW_MAJOR_VERSION    ETH_SW_MAJOR_VERSION_VALUE
#define ETH_RAM_C_SW_MINOR_VERSION    ETH_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/

#if (ETH_RAM_AR_RELEASE_MAJOR_VERSION != ETH_RAM_C_AR_RELEASE_MAJOR_VERSION)
  #error "Eth_Ram.c : Mismatch in Release Major Version"
#endif
#if (ETH_RAM_AR_RELEASE_MINOR_VERSION != ETH_RAM_C_AR_RELEASE_MINOR_VERSION)
  #error "Eth_Ram.c : Mismatch in Release Minor Version"
#endif
#if (ETH_RAM_AR_RELEASE_REVISION_VERSION != ETH_RAM_C_AR_RELEASE_REVISION_VERSION)
  #error "Eth_Ram.c : Mismatch in Release Revision Version"
#endif


#if (ETH_RAM_SW_MAJOR_VERSION != ETH_RAM_C_SW_MAJOR_VERSION)
   #error "Eth_Ram.c : Mismatch in Software Major Version"
#endif
#if (ETH_RAM_SW_MINOR_VERSION != ETH_RAM_C_SW_MINOR_VERSION)
   #error "Eth_Ram.c : Mismatch in Software Minor Version"
#endif
/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/**********************************************************************************************************************/
/* Message (1:1532)    : The function '%1s' is only referenced in one translation unit - but not the one in which it  */
/*                       is defined.                                                                                  */
/* Rule                : CERTCCM DCL19, MISRA C:2012 Rule-8.7, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : This is accepted, due to the specific coding rule, function of each hardware unit is         */
/*                       implemented in separated files for this hardware unit. Could not be static function.         */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE Rule CWE-398, CWE-569                                            */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is accepted. */
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
/* Message (2:2814)    : Possible: Dereference of NULL pointer.                                                       */
/* Rule                : CERTCCM EXP34, CWE Rule CWE-476, CWE-465, CWE-737, CWE-690                                   */
/* JV-01 Justification : To prevent overhead and excessive nesting of condition statements, this pointer has been     */
/*                       tested valid with many test cases, so there is no problem with the current implementation.   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3206)    : The parameter '%s' is not used in this function.                                             */
/* Rule                : CERTCCM MSC07, MSC13, MISRA C:2012 Rule-2.7, CWE Rule CWE-398, CWE-563, CWE-569              */
/* JV-01 Justification : This is done as per implementation requirement                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0316)    : Cast from a pointer to void to a pointer to object type.                                     */
/* Rule                : MISRA C:2012 Rule-11.5, CWE Rule CWE-188, CWE-398, CWE-569                                   */
/* JV-01 Justification : Typecasting from void* is necessary to hide internal types from the header files which are   */
/*                       exposed to user.                                                                             */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:3383)    : Cannot identify wraparound guard for unsigned arithmetic expression.                         */
/* Rule                : CERTCCM INT30                                                                                */
/* JV-01 Justification : Wraparound can't be occur in this unsigned integer arithmetic so there is no need to add a   */
/*                       wraparound guard here.                                                                       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:2985)    : This operation is redundant. The value of the result is always that of the left-hand operand.*/
/* Rule                : CERTCCM MSC07, MSC13, MISRA C:2012 Rule-2.2, CWE Rule CWE-398, CWE-561, CWE-569, CWE-633     */
/* JV-01 Justification : The content of LusReqSize will be changed if the user enables the EthSwt option, so the value*/
/*                       of this result is not always that of the left-hand operand.                                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:2834)    : Possible: Division by zero.                                                                  */
/* Rule                : CERTCCM INT33, CWE Rule CWE-128, CWE-369, CWE-738, CWE-680                                   */
/* JV-01 Justification : Value generated by generation tool is always different from zero.                            */
/*       Verification  : It's not impact to driver source code implementation                                         */
/**********************************************************************************************************************/
/* Message (2:2934)    : Possible: Computing an invalid pointer value.                                                */
/* Rule                : CERTCCM ARR30, ARR37, ARR38, EXP08, CWE Rule CWE-120, CWE-121, CWE-122, CWE-124, CWE-125     */
/*                       CWE-126, CWE-127, CWE-129, CWE-131, CWE-469, CWE-823, CWE-465, CWE-633, CWE-740              */
/* JV-01 Justification : To prevent overhead and excessive nesting of condition statements, this pointer has been     */
/*                       tested valid with many test cases, so there is no problem with the current implementation.   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0306)    : Cast between a pointer to object and an integral type.                                       */
/* Rule                : CERTCCM INT36, MISRA C:2012 Rule-11.4, CWE Rule CWE-398, CWE-569, CWE-738                    */
/* JV-01 Justification : Typecasting is done as per the register size or hardware specific structure.                 */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0314)    : Cast from a pointer to object type to a pointer to void.                                     */
/* Rule                : MISRA C:2012 Dir-1.1, CWE Rule CWE-188, CWE-398, CWE-569                                     */
/* JV-01 Justification : This is necessary to set pointer value to DMA register.                                      */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3678)    : The object referenced by '%1s' is not modified through it, so '%1s' could be declared with   */
/*                       type '%2s'.                                                                                  */
/* Rule                : MISRA C:2012 Rule-8.13                                                                       */
/* JV-01 Justification : The object addressed by this pointer change so it can not be of type "pointer to const"      */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3469)    : This usage of a function-like macro looks like it could be replaced by an equivalent         */
/*                       function call.                                                                               */
/* Rule                : MISRA C:2012 Dir-4.9                                                                         */
/* JV-01 Justification : To prevent overhead and speed up the processing, there is no need to call a function here    */
/*                       for such a small operation.                                                                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0488)    : Performing pointer arithmetic.                                                               */
/* Rule                : CERTCCM EXP08, MISRA C:2012 Rule-18.4, CWE Rule CWE-188, CWE-398, CWE-569                    */
/* JV-01 Justification : This implementation is required for heap memory allocation algorithm                         */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1503)    : The function '%1s' is defined but is not used within this project.                           */
/* Rule                : CERTCCM MSC07, MISRA C:2012 Rule-2.1, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : This is accepted, due to the module's API is exported for user's usage.                      */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:4391)    : A composite expression of 'essentially unsigned' type (unsigned char) is being cast to a     */
/*                       wider unsigned type 'unsigned short'.                                                        */
/* Rule                : MISRA C:2012 Rule-10.8, CWE Rule CWE-136                                                     */
/* JV-01 Justification : This casting is necessary and is confirmed to be no problem.                                 */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:5087)    : Use of #include directive after code fragment.                                               */
/* Rule                : MISRA C:2012 Rule-20.1                                                                       */
/* JV-01 Justification : This is done as per Memory Requirement, (MEMMAP003 - Specification of Memory Mapping).       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1533)    : The object 'entity' is only referenced by function 'func'.                                   */
/* Rule                : MISRA C:2012 Rule-8.9, CWE Rule CWE-398, CWE-569                                             */
/* JV-01 Justification : This is accepted, due to the object is defined in seperated cource C file to followed        */
/*                       coding rule                                                                                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1514)    : The object '%1s' is only referenced by function '%2s', in the translation unit where it is   */
/*                       defined                                                                                      */
/* Rule                : MISRA C:2012 Rule-8.9, CWE Rule CWE-398, CWE-569                                             */
/* JV-01 Justification : This object is used outside of this translation unit and  in other  translation unit         */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1531)    : The object '%1s' is referenced in only one translation unit - but not the one in which it    */
/*                       is defined.                                                                                  */
/* Rule                : CERTCCM DCL15, DCL19, MISRA C:2012 Rule-8.7, CWE Rule CWE-398, CWE-569                       */
/* JV-01 Justification : Followed coding rules, the objects (global variable/const) is define in separated source     */
/*                       file, so this could be accepted                                                              */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1502)    : The object 'name' is defined but is not used within this project.                            */
/* Rule                : MISRA C:2012 Rule-2.8, CWE Rule CWE-398, CWE-569, CERTC Rule MSC13                           */
/* JV-01 Justification : Array is used in another part of driver code. There is no problem in use                     */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/
#define ETH_START_SEC_VAR_NO_INIT_8
#include "Eth_MemMap.h"

#define ETH_STOP_SEC_VAR_NO_INIT_8
#include "Eth_MemMap.h"

#define ETH_START_SEC_VAR_NO_INIT_16
#include "Eth_MemMap.h"

#define ETH_STOP_SEC_VAR_NO_INIT_16
#include "Eth_MemMap.h"

#define ETH_START_SEC_VAR_NO_INIT_32
#include "Eth_MemMap.h"

VAR(Eth_BufIdxType, ETH_VAR_NO_INIT) Eth_GaaRxBufferIndex[ETH_TOTAL_CTRL_CONFIG];                                       /* PRQA S 1533 # JV-01 */

VAR(Eth_RxFrameType, ETH_VAR_NO_INIT) Eth_GaaRxFrame[ETH_TOTAL_CTRL_CONFIG];

#define ETH_STOP_SEC_VAR_NO_INIT_32
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define ETH_START_SEC_VAR_NO_INIT_PTR
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

P2VAR(void, ETH_VAR_FAST_NO_INIT, ETH_VAR_FAST_NO_INIT) Eth_GaaHeap[ETH_TOTAL_CTRL_CONFIG];                             /* PRQA S 1502 # JV-01 */

/* Global variable to store pointer to Configuration */
P2CONST(Eth_CtrlConfigType, ETH_CONST, ETH_CONFIG_CONST) volatile Eth_GpCtrlConfigPtr;
P2CONST(Eth_EthConfigType, ETH_CONST, ETH_CONFIG_CONST) volatile Eth_GpEthConfigPtr;

#define ETH_STOP_SEC_VAR_NO_INIT_PTR
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define ETH_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Multicast address filter list */
VAR(Eth_MacAddressType, ETH_VAR_NO_INIT) Eth_GaaAddressFilters[ETH_TOTAL_CTRL_CONFIG][ETH_MAX_FILTERS];                 

/* Status of controller(s) */
VAR(Eth_ControllerStatusType, ETH_VAR_NO_INIT) Eth_GaaCtrlStat[ETH_TOTAL_CTRL_CONFIG];

#define ETH_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define ETH_START_SEC_VAR_INIT_BOOLEAN
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define ETH_STOP_SEC_VAR_INIT_BOOLEAN
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define ETH_START_SEC_VAR_INIT_8
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define ETH_STOP_SEC_VAR_INIT_8
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define ETH_START_SEC_VAR_INIT_16
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
P2VAR(uint16, ETH_VAR_INIT, ETH_VAR_INIT) Eth_GpDemEventAccess;                                                         /* PRQA S 3432 # JV-01 */

P2VAR(uint16, ETH_VAR_INIT, ETH_VAR_INIT) Eth_GpDemEventRxFramesLost;                                                   /* PRQA S 3432 # JV-01 */

P2VAR(uint16, ETH_VAR_INIT, ETH_VAR_INIT) Eth_GpDemEventCRC;                                                            /* PRQA S 3432 # JV-01 */

P2VAR(uint16, ETH_VAR_INIT, ETH_VAR_INIT) Eth_GpDemEventUnderSizeFrame;                                                 /* PRQA S 3432 # JV-01 */

P2VAR(uint16, ETH_VAR_INIT, ETH_VAR_INIT) Eth_GpDemEventOverSizeFrame;                                                  /* PRQA S 3432 # JV-01 */

P2VAR(uint16, ETH_VAR_INIT, ETH_VAR_INIT) Eth_GpDemEventAlignment;                                                      /* PRQA S 3432 # JV-01 */

P2VAR(uint16, ETH_VAR_INIT, ETH_VAR_INIT) Eth_GpDemEventSinglecollision;                                                /* PRQA S 3432 # JV-01 */

P2VAR(uint16, ETH_VAR_INIT, ETH_VAR_INIT) Eth_GpDemEventMultiplecollision;                                              /* PRQA S 3432 # JV-01 */

P2VAR(uint16, ETH_VAR_INIT, ETH_VAR_INIT) Eth_GpDemEventLatecollision;                                                  /* PRQA S 3432 # JV-01 */

#if ( ETH_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
P2VAR(uint16, ETH_VAR_INIT, ETH_VAR_INIT) Eth_GpDemEventIntInconsistent;                                                /* PRQA S 3432 # JV-01 */
#endif

P2VAR(uint16, ETH_VAR_INIT, ETH_VAR_INIT) Eth_GpDemEventDmaError;                                                       /* PRQA S 3432 # JV-01 */

P2VAR(uint16, ETH_VAR_INIT, ETH_VAR_INIT) Eth_GpDemEventEccError;                                                       /* PRQA S 3432, 1533 # JV-01, JV-01 */

#if (ETH_MACRO_ETNB == STD_ON || ETH_MACRO_ETNF ==STD_ON)
#if (ETH_GLOBAL_TIME_SUPPORT == STD_ON)
P2VAR(uint16, ETH_VAR_INIT, ETH_VAR_INIT) Eth_GpDemEventTimerincFailed;                                                 /* PRQA S 3432 # JV-01 */

P2VAR(uint16, ETH_VAR_INIT, ETH_VAR_INIT) Eth_GpDemEventTimeroffsetFailed;                                              /* PRQA S 3432 # JV-01 */
#endif
#if ((ETH_REGISTER_CHECK_INITTIME == STD_ON) || (ETH_REGISTER_CHECK_RUNTIME == STD_ON))
P2VAR(uint16, ETH_VAR_INIT, ETH_VAR_INIT) Eth_GpDemEventRegisterCorruption;                                             /* PRQA S 3432 # JV-01 */
#endif
#endif

#if (ETH_MACRO_ETNE == STD_ON)
#if (ETH_UNINTENDED_INTERRUPT_CHECK == STD_ON)
P2VAR(uint16, ETH_VAR_INIT, ETH_VAR_INIT) Eth_GpDemEventUnintendedIntChk;                                               /* PRQA S 3432, 1533 # JV-01, JV-01 */
#endif
#endif

#define ETH_STOP_SEC_VAR_INIT_16
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define ETH_START_SEC_VAR_INIT_32
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define ETH_STOP_SEC_VAR_INIT_32
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define ETH_START_SEC_VAR_INIT_PTR
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define ETH_STOP_SEC_VAR_INIT_PTR
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define ETH_START_SEC_VAR_INIT_UNSPECIFIED
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
P2VAR(Eth_StateType, ETH_VAR_INIT, ETH_VAR_INIT) Eth_GpDriverState;                                                     /* PRQA S 3432 # JV-01 */

#define ETH_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define ETH_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
P2CONST(uint32, ETH_VAR_INIT, ETH_CONFIG_DATA) Eth_GpTotalCtrlConfig;                                                   
uint32 Eth_CtrlConfigIdx[ETH_TOTAL_CORE_CONFIG][ETH_MAX_CTRL_CONFIG_PER_CODE];                                          
#define ETH_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#if (ETH_MULTI_CORE_SUPPORT == STD_ON)
#define ETH_START_SEC_CONST_8
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/* Global variable to store core index */
P2CONST(uint8, ETH_VAR_INIT, ETH_CONFIG_CONST) Eth_GpCoreId2Index;                                                      

#define ETH_STOP_SEC_CONST_8
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif


/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/
#define ETH_START_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define ETH_STOP_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
