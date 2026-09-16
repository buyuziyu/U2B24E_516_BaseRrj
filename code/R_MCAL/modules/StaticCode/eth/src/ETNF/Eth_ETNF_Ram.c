/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Eth_ETNF_Ram.c                                                                                      */
/*====================================================================================================================*/
/*                                                COPYRIGHT                                                           */
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
**                                            Revision Control History                                                **
***********************************************************************************************************************/
/*
 * 2.4.1: 30/06/2025    : Remove the SW-VERSION from header of file
 * 2.4.0: 30/05/2025    : Update SW-VERSION for RH850/Ver22.01.02 U2Cx release
 * 2.3.1: 31/03/2025    : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 * 2.3.0: 28/02/2025    : Update SW-VERSION for Ver22.01.00/Ver22.01.00.D U2Cx Release
 * 2.2.0: 31/12/2024    : Update SW-VERSION for Ver22.02.00(D) U2Bx Final Release
 * 2.1.2: 31/10/2024    : Increase SW-VERSION to 2.1.2
 * 2.1.1: 22/07/2024    : Update QAC message
 *        31/05/2024    : Remove declaration of Eth_GaaRxBufferIndex
 * 2.0.2: 26/12/2023    : Update QAC message.
 *        14/12/2023    : Fix order Function pointer invoked in Function table when using interrupt mode by 
 *                        adding Null pointer
 * 1.0.0: 14/12/2023    : Initial Version
 */
/******************************************************************************/

/***********************************************************************************************************************
**                                               Include Section                                                      **
***********************************************************************************************************************/
/* Included for Eth.h inclusion and macro definitions */
#include "Eth.h"
/* Header file inclusion */
#include "Eth_ETNF_Ram.h"
#include "Eth_Ram.h"
#if (ETH_ETHSWITCH_MANAGEMENT_SUPPORT == STD_ON)
#include "EthSwt_Cbk.h"
#endif

#if (ETH_CRITICAL_SECTION_PROTECTION == STD_ON)
/* Included for the declaration of the critical section protection functions */
#include "SchM_Eth.h"
#endif

/***********************************************************************************************************************
**                                              Version Information                                                   **
***********************************************************************************************************************/
#if (ETH_MACRO_ETNF == STD_ON)
/* AUTOSAR release version information */
#define ETH_ETNF_RAM_C_AR_RELEASE_MAJOR_VERSION ETH_AR_RELEASE_MAJOR_VERSION_VALUE
#define ETH_ETNF_RAM_C_AR_RELEASE_MINOR_VERSION ETH_AR_RELEASE_MINOR_VERSION_VALUE
#define ETH_ETNF_RAM_C_AR_RELEASE_REVISION_VERSION ETH_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define ETH_ETNF_RAM_C_SW_MAJOR_VERSION    ETH_SW_MAJOR_VERSION_VALUE
#define ETH_ETNF_RAM_C_SW_MINOR_VERSION    ETH_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                 Version Check                                                      **
***********************************************************************************************************************/

#if (ETH_ETNF_RAM_AR_RELEASE_MAJOR_VERSION != ETH_ETNF_RAM_C_AR_RELEASE_MAJOR_VERSION)
  #error "Eth_ETNF_Ram.c : Mismatch in Release Major Version"
#endif
#if (ETH_ETNF_RAM_AR_RELEASE_MINOR_VERSION != ETH_ETNF_RAM_C_AR_RELEASE_MINOR_VERSION)
  #error "Eth_ETNF_Ram.c : Mismatch in Release Minor Version"
#endif
#if (ETH_ETNF_RAM_AR_RELEASE_REVISION_VERSION != ETH_ETNF_RAM_C_AR_RELEASE_REVISION_VERSION)
  #error "Eth_ETNF_Ram.c : Mismatch in Release Revision Version"
#endif


#if (ETH_ETNF_RAM_SW_MAJOR_VERSION != ETH_ETNF_RAM_C_SW_MAJOR_VERSION)
   #error "Eth_ETNF_Ram.c : Mismatch in Software Major Version"
#endif
#if (ETH_ETNF_RAM_SW_MINOR_VERSION != ETH_ETNF_RAM_C_SW_MINOR_VERSION)
   #error "Eth_ETNF_Ram.c : Mismatch in Software Minor Version"
#endif

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (4:5087)    : (4:5087) #include statements in a file should only be preceded by other preprocessor         */
/*                       directives or comments.                                                                      */
/* Rule                : MISRA C:2012 Rule-20.1                                                                       */
/* JV-01 Justification : This is accepted, due to implementation for include memmap is following AUTOSAR rule.        */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7                                                                       */
/*                       REFERENCE - ISO:C90-6.3.1 Primary Expressions                                                */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is           */
/*                       accepted.                                                                                    */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1504)    : The object 'name' is only referenced in the translation unit where it is defined.            */
/* Rule                : CERTCCM DCL15, DCL19, MISRA C:2012 Rule-8.7                                                  */
/* JV-01 Justification : This is accepted, due to following coding rule, internal function can be defined in          */
/*                       other C source files                                                                         */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3206)    : The parameter 'ucApiId' is not used in this function.                                        */
/* Rule                : CERTCCM MSC07, MSC13, MISRA C:2012 Rule-2.7                                                  */
/* JV-01 Justification : This argument is not used since only one controller is used. However, it is prepared         */
/*                       because it is used by another IP. There is no problem because it is as designed.             */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:3384)    : Cannot identify wraparound guard for dependent unsigned arithmetic expression.               */
/* Rule                : CERTCCM INT30                                                                                */
/* JV-01 Justification : Wraparound can't be occur in this unsigned integer arithmetic so there is no need to add     */
/*                       a wraparound guard here.                                                                     */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0306)    : [I] Cast between a pointer to object and an integral type.                                   */
/* Rule                : CERTCCM INT36, MISRA C:2012 Rule-11.4                                                        */
/*                       REFERENCE - ISO:C90-6.3.4  Semantics                                                         */
/* JV-01 Justification : Decided that this typecast is necessary as process.                                          */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:3383)    : Cannot identify wraparound guard for unsigned arithmetic expression.                         */
/* Rule                : CERTCCM INT30                                                                                */
/* JV-01 Justification : Wraparound can't be occur in this unsigned integer arithmetic so there is no need to add     */
/*                       a wraparound guard here.                                                                     */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3678)    : The object referenced by '%1s' is not modified through it, so '%1s' could be declared        */
/*                       with type '%2s'.                                                                             */
/* Rule                : MISRA C:2012 Rule-8.13                                                                       */
/* JV-01 Justification : The object addressed by this pointer change so it can not be of type "pointer to const"      */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0310)    : Casting to different object pointer type.                                                    */
/* Rule                : MISRA-C:2004 Rule 11.4                                                                       */
/*                       REFERENCE - ISO-6.3.4 Cast Operators                                                         */
/* JV-01 Justification : This is necessary to set pointer conform with function declaration.                          */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3469)    : This usage of a function-like macro looks like it could be replaced by an equivalent         */
/*                       function call.                                                                               */
/* Rule                : MISRA C:2012 Dir-4.9                                                                         */
/* JV-01 Justification : To prevent overhead and speed up the processing, there is no need to call a function         */
/*                       here for such a small operation.                                                             */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0488)    : Performing pointer arithmetic.                                                               */
/* Rule                : CERTCCM EXP08, MISRA C:2012 Rule-18.4                                                        */
/* JV-01 Justification : This implementation is required for heap memory allocation algorithm                         */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (6:3305)    : Pointer cast to stricter alignment.                                                          */
/* Rule                : CERTCCM EXP36, EXP39, MISRA C:2012 Rule-11.3                                                 */
/* JV-01 Justification : It is an implementation required to manage heap memory. There is no problem because the      */
/*                       4-byte alignment boundary is guaranteed by the implementation of the heap memory             */
/*                       operation algorithm.                                                                         */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0751)    : Casting to char pointer type.                                                                */
/* Rule                : CERTCCM EXP11, EXP39                                                                         */
/* JV-01 Justification : Since EICnEIMK exists in the lower 8 bits, there is no problem casting to char type.         */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1505)    : The function 'name' is only referenced in the translation unit where it is defined.          */
/* Rule                : CERTCCM DCL19, MISRA C:2012 Rule-8.7                                                         */
/* JV-01 Justification : This is accepted, due to following coding rule, internal function can be defined in          */
/*                       other C source files                                                                         */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0316)    : [I] Cast from a pointer to void to a pointer to object type.                                 */
/* Rule                : MISRA C:2012 Rule-11.5                                                                       */
/* JV-01 Justification : Typecasting from void* is necessary to hide internal types from the header files which       */
/*                       are exposed to user.                                                                         */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:4342)    : [I] An expression of 'essentially unsigned' type (%1s) is being cast to enum type '%2s'.     */
/* Rule                : MISRA-C:2012 Rule 10.5                                                                       */
/* JV-01 Justification : Code review confirmed that values within an enumerated type are cast, so no problem.         */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:4391)    : A composite expression of 'essentially unsigned' type (unsigned char) is being cast to a     */
/*                       wider unsigned type 'unsigned short'.                                                        */
/* Rule                : MISRA C:2012 Rule-10.8                                                                       */
/* JV-01 Justification : This casting is necessary and is confirmed to be no problem.                                 */
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
/* Message (1:1531)    : The object '%1s' is referenced in only one translation unit - but not the one in which it    */
/*                       is defined.                                                                                  */
/* Rule                : CERTCCM DCL15, DCL19, MISRA C:2012 Rule-8.7, CWE Rule CWE-398, CWE-569                       */
/* JV-01 Justification : Followed coding rules, the objects (global variable/const) is define in separated source     */
/*                       file, so this could be accepted                                                              */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:2844)    : Possible: Dereference of an invalid pointer value.                                           */
/* Rule                : CERTCCM ARR30, CWE Rule CWE-120, CWE-121, CWE-122, CWE-124, CWE-125, CWE-126, CWE-127        */
/*                       CWE-129, CWE-131, CWE-466, CWE-786, CWE-787, CWE-788, CWE-805, CWE-465, CWE-633, CWE-740     */
/* JV-01 Justification : To prevent overhead and excessive nesting of condition statements, this pointer has been     */
/*                       tested valid with many test cases, so there is no problem with the current implementation.   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:2814)    : Possible: Dereference of NULL pointer.                                                       */
/* Rule                : CERTCCM EXP34, CWE Rule CWE-476, CWE-465, CWE-737, CWE-690                                   */
/* JV-01 Justification : This is accepted, due to the implementation following hardware specification.                */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0315)    : Implicit conversion from a pointer to object type to a pointer to void.                      */
/* Rule                : MISRA C:2012 Dir-1.1                                                                         */
/* JV-01 Justification : Typecasting is done as per the register size, to access hardware registers.                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Global Data                                                          **
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

#define ETH_STOP_SEC_VAR_NO_INIT_32
#include "Eth_MemMap.h"                                                                                                 

#define ETH_START_SEC_VAR_NO_INIT_PTR
#include "Eth_MemMap.h"                                                                                                 
P2VAR(Eth_MemManagerType, ETH_VAR_FAST_NO_INIT, ETH_VAR_FAST_NO_INIT)                                                   /* PRQA S 3432 # JV-01 */
  Eth_GpRamManager[ETH_TOTAL_CTRL_CONFIG];                                                                              /* PRQA S 1504 # JV-01 */

#define ETH_STOP_SEC_VAR_NO_INIT_PTR
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define ETH_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

VAR(Eth_ListType, ETH_VAR_NO_INIT) Eth_GaaBufferLock[ETH_TOTAL_CTRL_CONFIG][ETH_TXQ_NUM];                               /* PRQA S 1504 # JV-01 */

VAR(Eth_RxChConfigType, ETH_VAR_NO_INIT) Eth_GaaRxConfig[ETH_RXQ_NUM];

VAR(Eth_QConfigType, ETH_VAR_NO_INIT) Eth_GaaQConfig[ETH_RXQ_NUM];                                                      

VAR(Eth_AvbConfigType, ETH_VAR_NO_INIT) Eth_GaaAvbConfig[ETH_TOTAL_CTRL_CONFIG];                                        

VAR(Eth_TxBufferType, ETH_VAR_NO_INIT) Eth_GaaTxBufferIndex[ETH_TOTAL_CTRL_CONFIG][ETH_TX_DESC_MAX];

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

#define ETH_STOP_SEC_VAR_INIT_16
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define ETH_START_SEC_VAR_INIT_32
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define ETH_STOP_SEC_VAR_INIT_32
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define ETH_START_SEC_VAR_PORT_BUFFER_0
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define ETH_STOP_SEC_VAR_PORT_BUFFER_0
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define ETH_START_SEC_VAR_PORT_BUFFER_1
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define ETH_STOP_SEC_VAR_PORT_BUFFER_1
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define ETH_START_SEC_VAR_INIT_PTR
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define ETH_STOP_SEC_VAR_INIT_PTR
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define ETH_START_SEC_VAR_INIT_UNSPECIFIED
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* The Function table for ETNF */
VAR(Eth_HwFuncTableType, ETH_VAR_INIT) Eth_EtnfFunc =                                                                   
{
  &Eth_ETNF_InitializeBuffer,
  &Eth_ETNF_PreprocessBuffer,
  &Eth_ETNF_GetTxBuffer,
  &Eth_ETNF_ReleaseTxBuffer,
  &Eth_ETNF_CheckProvideBuffer,
  &Eth_ETNF_PreprocessFrame,
  &Eth_ETNF_FindTxBufferHandler,
  &Eth_ETNF_HwInit,
  #if (ETH_DEINIT_API == STD_ON)
  NULL_PTR, /* pHwDeInit */
  #endif
  &Eth_ETNF_HwDisableController,
  &Eth_ETNF_HwEnableController,
  &Eth_ETNF_HwTransmit,
  #if (ETH_GET_COUNTER_VALUES_API == STD_ON)
  &Eth_ETNF_HwGetCounterValues,
  #endif
  #if (ETH_GET_RX_STATS_API == STD_ON)
  &Eth_ETNF_HwGetRxStats,
  #endif
  #if (ETH_GET_TX_STATS_API == STD_ON)
  &Eth_ETNF_HwGetTxStats,
  #endif
  #if (ETH_GET_TX_ERROR_COUNTER_VALUES_API == STD_ON)
  &Eth_ETNF_HwGetTxErrorCounterValues,
  #endif
  &Eth_ETNF_HwMainFunction,
  &Eth_ETNF_HwTxConfirmation,
  #if (ETH_CTRL_ENABLE_RX_POLLING == STD_ON)
  #if (ETH_AR_VERSION >= ETH_AR_431_VERSION)
  &Eth_ETNF_HwCheckFifoIndex,
  #endif
  #endif
  #if (ETH_CTRL_ENABLE_RX_POLLING == STD_ON)
  &Eth_ETNF_HwReceive,
  #else
  NULL_PTR, /* pHwReceive */
  #endif
  #if (ETH_GLOBAL_TIME_SUPPORT == STD_ON)
  &Eth_ETNF_HwSetIncrementTimeForGptp,
  &Eth_ETNF_HwSetOffsetTimeForGptp,
  &Eth_ETNF_HwGetCurrentTime,
  &Eth_ETNF_HwGetEgressTimeStamp,
  &Eth_ETNF_HwGetIngressTimeStamp,
  #endif
  #if (ETH_CTRL_ENABLE_MII == STD_ON)
  #if ((ETH_MACRO_ETND == STD_ON) || (ETH_MACRO_ETNE == STD_ON))
  NULL_PTR, /* pHwWriteMii */
  NULL_PTR, /* pHwReadMii */
  #endif
  #if ((ETH_MACRO_ETNB == STD_ON) || (ETH_MACRO_ETNC == STD_ON) || (ETH_MACRO_ETNF == STD_ON))
  &Eth_HwWriteMiiBit,
  &Eth_HwReadMiiBit
  #endif
  #endif
};

#define ETH_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
**                                         Function Definitions                                                       **
***********************************************************************************************************************/
#define ETH_START_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#if (ETH_QOS_SUPPORT == STD_ON)
STATIC FUNC(Eth_TxChannelType, ETH_PRIVATE_CODE) FindTxQueue(
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint8, AUTOMATIC) LucPriority);
#endif

/***********************************************************************************************************************
** Function Name         : Eth_ETNF_InitializeBuffer
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
** Global Variables Used : Eth_GaaCtrlStat, Eth_GaaBufferLock,
**                         Eth_GaaRxBufferIndex, Eth_GaaTxBufferIndex,
**                         Eth_GaaRxFrame
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_465,
** Reference ID          : ETH_DUD_ACT_465_GBL001, ETH_DUD_ACT_465_GBL002
** Reference ID          : ETH_DUD_ACT_465_GBL003, ETH_DUD_ACT_465_GBL004
** Reference ID          : ETH_DUD_ACT_465_GBL005, ETH_DUD_ACT_465_GBL006
** Reference ID          : ETH_DUD_ACT_465_GBL007
***********************************************************************************************************************/
FUNC(void, ETH_PRIVATE_CODE) Eth_ETNF_InitializeBuffer(                                                                 /* PRQA S 1505 # JV-01 */
  CONST(uint32, AUTOMATIC) LulCtrlIdx)
{
  uint16 LusCnt;
  P2VAR(Eth_TxBufferType, AUTOMATIC, ETH_APPL_DATA) LpTxBuffer;                                                         /* PRQA S 3432 # JV-01 */

  /* Initialize resource information */
  Eth_GaaRxBufferIndex[LulCtrlIdx] = 0UL;                                                                               
  Eth_GaaRxFrame[LulCtrlIdx].ulFrameAddr = 0UL;                                                                         
  Eth_GaaRxFrame[LulCtrlIdx].ulFrameLength = 0UL;                                                                       
  Eth_GaaRxFrame[LulCtrlIdx].ulEthTypeAddr = 0UL;                                                                       
  Eth_GaaRxFrame[LulCtrlIdx].stTimestamp.ulTimestamp0 = 0UL;                                                            
  Eth_GaaRxFrame[LulCtrlIdx].stTimestamp.ulTimestamp1 = 0UL;                                                            
  Eth_GaaRxFrame[LulCtrlIdx].stTimestamp.usTimestamp2 = 0U;                                                             
  Eth_GaaRxFrame[LulCtrlIdx].enTimeQual = ETH_INVALID;                                                                  

  /* Initialize Tx buffer index list */
  Eth_GaaCtrlStat[LulCtrlIdx].ulTxBufTail = 0UL;                                                                        
  for (LusCnt = 0U; LusCnt < ETH_TX_DESC_MAX; LusCnt++)
  {
    LpTxBuffer = (Eth_TxBufferType *)&Eth_GaaTxBufferIndex[LulCtrlIdx][LusCnt];                                         
    LpTxBuffer->pBufferHdr = NULL_PTR;
    LpTxBuffer->blLocked   = ETH_FALSE;
    #if (ETH_GLOBAL_TIME_SUPPORT == STD_ON)
    LpTxBuffer->enTimeQual = ETH_INVALID;
    LpTxBuffer->stTimeStamp.nanoseconds = (uint32)0U;
    LpTxBuffer->stTimeStamp.seconds     = (uint32)0U;
    LpTxBuffer->stTimeStamp.secondsHi   = (uint16)0U;
    #endif
  }

  /* Initialize buffer counter */
  for (LusCnt = 0U; LusCnt < ETH_TXQ_NUM; LusCnt++)
  {
    Eth_GaaCtrlStat[LulCtrlIdx].stHwStatEtnf.aaBufTxCnt[LusCnt] = 0UL;                                                  
    Eth_Util_IniLinkedList(&Eth_GaaBufferLock[LulCtrlIdx][LusCnt]);                                                     
  }
}

/***********************************************************************************************************************
** Function Name         : Eth_ETNF_PreprocessBuffer
**
** Service ID            : N/A
**
** Description           : Write source address to all Tx Buffers in advance
**                         because source address is never changed while
**                         a controller mode is ACTIVE.
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
** Global Variables Used : None
**
** Function(s) invoked   : None
**
** Registers Used        : None
***********************************************************************************************************************/
FUNC(void, ETH_PRIVATE_CODE) Eth_ETNF_PreprocessBuffer(                                                                 /* PRQA S 1505 # JV-01 */
  CONST(uint32, AUTOMATIC) LulCtrlIdx)                                                                                  /* PRQA S 3206 # JV-01 */
{
  /* No action required because this function is retained for ETNC compatibility. */
}

/***********************************************************************************************************************
** Function Name         : Eth_ETNF_GetTxBuffer
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
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : A index of acquired buffer
**
** Preconditions         : None
**
** Global Variables Used : Eth_GaaBufferLock, Eth_GaaTxBufferIndex,
**                         Eth_GaaCtrlStat
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_467
** Reference ID          : ETH_DUD_ACT_467_CRT001, ETH_DUD_ACT_467_CRT002
** Reference ID          : ETH_DUD_ACT_467_GBL001, ETH_DUD_ACT_467_GBL002
***********************************************************************************************************************/
FUNC(BufReq_ReturnType , ETH_PRIVATE_CODE) Eth_ETNF_GetTxBuffer(                                                        /* PRQA S 1505 # JV-01 */
  CONST(uint32, AUTOMATIC) LulCtrlIdx,
  CONST(uint8, AUTOMATIC) LucPriority,                                                                                  /* PRQA S 3206 # JV-01 */
  CONSTP2VAR(Eth_BufIdxType, AUTOMATIC, ETH_APPL_DATA) LpBufIdxPtr,                                                     /* PRQA S 3432 # JV-01 */
  CONSTP2VAR(uint8*, AUTOMATIC, ETH_APPL_DATA) LpBufPtr,                                                                /* PRQA S 3432 # JV-01 */
  CONSTP2VAR(uint16, AUTOMATIC, ETH_APPL_DATA) LenBytePtr)                                                              /* PRQA S 3432 # JV-01 */
{
  BufReq_ReturnType LenReturnValue;
  Eth_TxChannelType LenQid;
  Eth_BufHandlerType* LpTxBufferNode;
  uint32 LulRingIdx;
  uint32 LulTxAllocCnt;
  #if (ETH_QOS_SUPPORT == STD_ON)
  uint32 LulCnt;
  #endif
  uint16 LusReqSize;
  #if (ETH_ETHSWITCH_MANAGEMENT_SUPPORT == STD_ON)
  P2VAR(uint8, AUTOMATIC, ETH_APPL_DATA) LpDataPtr;                                                                     /* PRQA S 3432 # JV-01 */
  Std_ReturnType LucReturnValue;
  #endif

  /* If the requested size is smaller than the minimum size, expand it to the minimum size */
  if ((uint16)ETH_MIN_PAYLOAD_SIZE_AVB > *LenBytePtr)                                                                   
  {
    *LenBytePtr = (uint16)ETH_MIN_PAYLOAD_SIZE_AVB;
  }
  else
  {
    /* No action required */
  }

  LusReqSize = *LenBytePtr;
  #if (ETH_ETHSWITCH_MANAGEMENT_SUPPORT == STD_ON)
  /* Added Switch Management Information */
  EthSwt_EthTxAdaptBufferLength(&LusReqSize);
  #endif

  /* Get the current tail pointer */
  /* If the requested size is larger than the buffer, return error */
  if (LusReqSize > (uint16)ETH_MAX_TX_PAYLOAD_LENGTH)
  {
    *LenBytePtr = (uint16)((uint16)ETH_MAX_TX_PAYLOAD_LENGTH - (LusReqSize - *LenBytePtr));
    LenReturnValue = BUFREQ_E_OVFL;
  }
  else
  {
    #if (ETH_QOS_SUPPORT == STD_ON)
    LenQid = FindTxQueue(LulCtrlIdx, LucPriority);
    #else
    /* Use BE Queue for any Traffic */
    LenQid = ETH_TX_BE;
    #endif
    /* Enter the critical section protection */
    ETH_ENTER_CRITICAL_SECTION(ETH_RAM_DATA_PROTECTION);
    /* Check the number of buffers allocated for a specific queue */
    #if (ETH_QOS_SUPPORT == STD_ON)
    LulTxAllocCnt = 0UL;
    for (LulCnt = 0UL; LulCnt < (uint32)ETH_TXQ_NUM; LulCnt++)
    {
      LulTxAllocCnt += Eth_Util_GetCountFromList(&Eth_GaaBufferLock[LulCtrlIdx][LulCnt]);                               /* PRQA S 3384 # JV-01 */
    }
    #else
    LulTxAllocCnt = Eth_Util_GetCountFromList(&Eth_GaaBufferLock[LulCtrlIdx][LenQid]);                                  
    #endif

    if (LulTxAllocCnt < (uint32)ETH_TX_DESC_MAX)
    {
      /* Get the Tx buffer management node and Tx buffer */
      LpTxBufferNode = (Eth_BufHandlerType *)Eth_Ram_Alloc(LulCtrlIdx,                                                  /* PRQA S 0306 # JV-01 */
        (uint32)(LusReqSize + ETH_HEADER_SIZE + sizeof(Eth_BufHandlerType)));                                           /* PRQA S 3383 # JV-01 */
      if (NULL_PTR != LpTxBufferNode)
      {
        /* Get tx buffer index */
        LulRingIdx = Eth_GaaCtrlStat[LulCtrlIdx].ulTxBufTail;                                                           
        /* This process never goes into an infinite loop */
        while (ETH_FALSE != Eth_GaaTxBufferIndex[LulCtrlIdx][LulRingIdx].blLocked)                                      
        {
          /* Next buffer index */
          LulRingIdx = (LulRingIdx + 1UL) % ETH_TX_DESC_MAX;                                                            /* PRQA S 3383 # JV-01 */
        }
        /* Set next buffer index */
        Eth_GaaCtrlStat[LulCtrlIdx].ulTxBufTail = (LulRingIdx + 1UL) % ETH_TX_DESC_MAX;                                 /* PRQA S 3383 # JV-01 */

        LpTxBufferNode->ulbufIdx = LulRingIdx;
        Eth_GaaTxBufferIndex[LulCtrlIdx][LulRingIdx].pBufferHdr = LpTxBufferNode;                                       
        Eth_GaaTxBufferIndex[LulCtrlIdx][LulRingIdx].blLocked = ETH_TRUE;                                               
        #if (ETH_GLOBAL_TIME_SUPPORT == STD_ON)
        Eth_GaaTxBufferIndex[LulCtrlIdx][LulRingIdx].enTimeQual = ETH_INVALID;                                          
        #endif

        LpTxBufferNode->ulbufAddr = (uint32)LpTxBufferNode + (uint32)sizeof(Eth_BufHandlerType);                        /* PRQA S 0306, 3383 # JV-01, JV-01 */
        LpTxBufferNode->ulEthTypeAddr = LpTxBufferNode->ulbufAddr + ETH_SRC_DST_ADDRESS_SIZE;                           /* PRQA S 3383 # JV-01 */
        LpTxBufferNode->ulTxLength = 0UL;
        LpTxBufferNode->enChannel = LenQid;
        LpTxBufferNode->blbenableTS = ETH_FALSE;
        LpTxBufferNode->blTxConfirm = ETH_FALSE;

        *LpBufIdxPtr = (Eth_BufIdxType)LpTxBufferNode->ulbufIdx;                                                        
        *LpBufPtr = (uint8 *)(LpTxBufferNode->ulbufAddr + (uint32)ETH_HEADER_SIZE);                                     /* PRQA S 0306, 3383 # JV-01, JV-01 */

        #if (ETH_ETHSWITCH_MANAGEMENT_SUPPORT == STD_ON)
        LpDataPtr = (uint8 *)LpTxBufferNode->ulEthTypeAddr;                                                             /* PRQA S 0306 # JV-01 */
        /* Added Switch Management Information */
        LusReqSize = *LenBytePtr;
        /* Since the maximum value of controller index is 1, casting to uint8 does no problem. */
        LucReturnValue = EthSwt_EthTxPrepareFrame((uint8)LulCtrlIdx, *LpBufIdxPtr, &LpDataPtr, &LusReqSize);
        if (E_OK == LucReturnValue)
        {
          LpTxBufferNode->ulEthTypeAddr = (uint32)LpDataPtr;                                                            /* PRQA S 0306 # JV-01 */
          *LpBufPtr = (uint8 *)((uint32)LpDataPtr + ETH_ETHERTYPE_SIZE);                                                /* PRQA S 0306, 3383 # JV-01, JV-01 */
        }
        else
        {
          /* If it is not a switch frame, use it as a normal frame */
        }
        #endif

        LenReturnValue = BUFREQ_OK;

        /* Enqueue Tx buffer management node */
        (void)Eth_Util_EnqToList(&Eth_GaaBufferLock[LulCtrlIdx][LenQid], LpTxBufferNode);                               
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
    ETH_EXIT_CRITICAL_SECTION(ETH_RAM_DATA_PROTECTION);
  }

  return LenReturnValue;
}

/***********************************************************************************************************************
** Function Name         : Eth_ETNF_ReleaseTxBuffer
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
**                         LulBufIdx      : index of a tx buffer
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variables Used : Eth_GaaBufferLock, Eth_GaaTxBufferIndex
**
** Function(s) invoked   : Eth_Ram_Free, Eth_Util_RemoveToList
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_468,
** Reference ID          : ETH_DUD_ACT_468_GBL001
***********************************************************************************************************************/
FUNC(void, ETH_PRIVATE_CODE) Eth_ETNF_ReleaseTxBuffer(
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulBufIdx)
{
  P2VAR(Eth_BufHandlerType, AUTOMATIC, ETH_APPL_DATA) LpTemp;                                                           /* PRQA S 3432 # JV-01 */

  /* Release tx buffer handler */
  LpTemp = Eth_GaaTxBufferIndex[LulCtrlIdx][LulBufIdx].pBufferHdr;                                                      
  (void)Eth_Util_RemoveToList(&Eth_GaaBufferLock[LulCtrlIdx][LpTemp->enChannel], (void **)&LpTemp);                     /* PRQA S 0310 # JV-01 */
  Eth_Ram_Free(LulCtrlIdx, (uint32)Eth_GaaTxBufferIndex[LulCtrlIdx][LulBufIdx].pBufferHdr);                             /* PRQA S 0306 # JV-01 */
  Eth_GaaTxBufferIndex[LulCtrlIdx][LulBufIdx].pBufferHdr = NULL_PTR;                                                    
  Eth_GaaTxBufferIndex[LulCtrlIdx][LulBufIdx].blLocked = ETH_FALSE;                                                     
}

/***********************************************************************************************************************
** Function Name         : Eth_ETNF_PreprocessFrame
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
** Global Variables Used : None
**
** Function(s) invoked   : Eth_FindTxBufferHandler, EthSwt_EthTxProcessFrame,
**                         ETH_ENTER_CRITICAL_SECTION, ETH_EXIT_CRITICAL_SECTION
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_469,
** Reference ID          : ETH_DUD_ACT_469_CRT001, ETH_DUD_ACT_469_CRT002
***********************************************************************************************************************/
FUNC(void, ETH_PRIVATE_CODE) Eth_ETNF_PreprocessFrame(                                                                  /* PRQA S 1505 # JV-01 */
  CONST(uint32, AUTOMATIC) LulCtrlIdx,
  CONST(uint32, AUTOMATIC) LulBufIdx,
  CONST(uint32, AUTOMATIC) LulFrameType,
  CONSTP2CONST(uint8, AUTOMATIC, ETH_APPL_DATA) LpPhysAddrPtr,
  CONSTP2VAR(uint16, AUTOMATIC, ETH_APPL_DATA) LpPayloadLen)                                                            /* PRQA S 3432, 3206 # JV-01, JV-01 */
{
  P2VAR(Eth_DataType, AUTOMATIC, ETH_APPL_DATA) LpBufPtr;                                                               /* PRQA S 3432 # JV-01 */
  P2VAR(Eth_BufHandlerType, AUTOMATIC, ETH_APPL_DATA) LpBufHandlerPtr;                                                  /* PRQA S 3432, 3678 # JV-01, JV-01 */
  #if (ETH_ETHSWITCH_MANAGEMENT_SUPPORT == STD_ON)
  P2VAR(uint8, AUTOMATIC, ETH_APPL_DATA) LpDataPtr;                                                                     /* PRQA S 3432 # JV-01 */
  uint16 LusTxLength;
  Std_ReturnType LucReturnValue;
  #endif

  ETH_ENTER_CRITICAL_SECTION(ETH_RAM_DATA_PROTECTION);

  /* Get Tx buffer address */
  LpBufHandlerPtr = Eth_ETNF_FindTxBufferHandler(LulCtrlIdx, LulBufIdx);

  ETH_EXIT_CRITICAL_SECTION(ETH_RAM_DATA_PROTECTION);

  LpBufPtr = (Eth_DataType *)LpBufHandlerPtr->ulbufAddr;                                                                /* PRQA S 0306 # JV-01 */

  #if (ETH_ETHSWITCH_MANAGEMENT_SUPPORT == STD_ON)
  LpDataPtr = (P2VAR(uint8, AUTOMATIC, ETH_APPL_DATA))(LpBufHandlerPtr->ulbufAddr + ETH_SRC_DST_ADDRESS_SIZE);          /* PRQA S 0306, 3432, 3383 # JV-01, JV-01, JV-01 */
  /* Since the maximum value of buffer size is 1518, casting to uint16 does no problem. */
  LusTxLength = *LpPayloadLen;                                                                                          
  /* decreased by the management information length */
  /* Since the maximum value of controller index is 1, casting to uint8 does no problem. */
  LucReturnValue = EthSwt_EthTxProcessFrame((uint8)LulCtrlIdx, LpBufHandlerPtr->ulbufIdx, &LpDataPtr, &LusTxLength);
  if (E_OK == LucReturnValue)
  {
    /* Adjusted for switch processing */
    LpBufPtr = (Eth_DataType *)(LpBufHandlerPtr->ulEthTypeAddr -                                                        /* PRQA S 0306, 3383 # JV-01, JV-01 */
                                (ETH_SRC_DST_ADDRESS_SIZE + (uint32)(LusTxLength - *LpPayloadLen)));                    /* PRQA S 3383, 4391 # JV-01, JV-01 */
    LpBufHandlerPtr->ulbufAddr = (uint32)LpBufPtr;                                                                      /* PRQA S 0306 # JV-01 */
    *LpPayloadLen = LusTxLength;
  }
  else
  {
    /* If EthSwt_SetMgmtInfo is not called, normal operation */
  }
  #endif

  /* Copy destination address */
  ETH_COPY_MAC_ADDRESS((CONST(uint8, AUTOMATIC) *)LpPhysAddrPtr, (uint8 *)LpBufPtr);                                    /* PRQA S 3469 # JV-01 */
  LpBufPtr = LpBufPtr + ETH_MACADDR_SIZE;                                                                               /* PRQA S 0488 # JV-01 */

  ETH_UNPACK_ADDRESS_TO_8(Eth_GaaCtrlStat[LulCtrlIdx].stMacAddr, LpBufPtr);                                             /* PRQA S 3469 # JV-01 */

  /* Casted to uint8 to extract the required 1 byte. */
  LpBufPtr = (Eth_DataType *)LpBufHandlerPtr->ulEthTypeAddr;                                                            /* PRQA S 0306 # JV-01 */
  *LpBufPtr = (Eth_DataType)((uint8)(LulFrameType >> ETH_BYTE_BITS));                                                   
  LpBufPtr++;                                                                                                           
  /* Casted to uint8 to extract the required 1 byte. */
  *LpBufPtr = (Eth_DataType)((uint8)LulFrameType);                                                                      
}

/***********************************************************************************************************************
** Function Name         : Eth_ETNF_CheckProvideBuffer
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
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variables Used : Eth_GaaTxBufferIndex
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_470
***********************************************************************************************************************/
FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_ETNF_CheckProvideBuffer(
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulBufIdx)
{
  Std_ReturnType LucReturnValue;

  /* Find tx buffer handler */
  if (ETH_TRUE == Eth_GaaTxBufferIndex[LulCtrlIdx][LulBufIdx].blLocked)                                                 
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
** Function Name         : Eth_Ram_Init
**
** Service ID            : NA
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
** Global Variable(s)    : Eth_GpRamManager
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_471,
** Reference ID          : ETH_DUD_ACT_471_GBL001, ETH_DUD_ACT_471_GBL002
** Reference ID          : ETH_DUD_ACT_471_GBL003, ETH_DUD_ACT_471_GBL004
** Reference ID          : ETH_DUD_ACT_471_GBL005
***********************************************************************************************************************/
FUNC(void, ETH_PRIVATE_CODE) Eth_Ram_Init(                                                                              
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulBaseAddr, CONST(uint32, AUTOMATIC) LulRamSize)
{
  Eth_GpRamManager[LulCtrlIdx] = (Eth_MemManagerType *)LulBaseAddr;                                                     /* PRQA S 0306 # JV-01 */
  Eth_GpRamManager[LulCtrlIdx]->pNext = Eth_GpRamManager[LulCtrlIdx];                                                   
  Eth_GpRamManager[LulCtrlIdx]->pPrev = Eth_GpRamManager[LulCtrlIdx];
  Eth_GpRamManager[LulCtrlIdx]->ulHeapSize = LulRamSize;
  Eth_GpRamManager[LulCtrlIdx]->blHeapLock = ETH_FALSE;
}

/***********************************************************************************************************************
** Function Name         : Eth_Ram_Alloc
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
** Global Variable(s)    : Eth_GpRamManager
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_472,
** Reference ID          : ETH_DUD_ACT_472_GBL002
***********************************************************************************************************************/
FUNC(uint32, ETH_PRIVATE_CODE) Eth_Ram_Alloc(
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulRamSize)
{
  CONST(uint32, AUTOMATIC) LulRequiredSize = ETH_ALIGN_TO_32BIT((LulRamSize + (uint32)sizeof(Eth_MemManagerType)));     /* PRQA S 3384, 3469, 3383 # JV-01, JV-01, JV-01 */

  uint32 LulRetAddress;
  Eth_MemManagerType *LpHeapNode;
  Eth_MemManagerType *LpNewBlock;

  LulRetAddress = 0U;

  /* Allocation algorithm with circular list */
  LpHeapNode = Eth_GpRamManager[LulCtrlIdx];                                                                            
  do
  {
    /* If block of heap node is not reserved and block size is more than required size */
    if ((ETH_FALSE == LpHeapNode->blHeapLock) && (LpHeapNode->ulHeapSize >= LulRequiredSize))                           
    {
      /* If block size of heap node-whether required size exceeds management area size of heap node */
      if ((LpHeapNode->ulHeapSize - LulRequiredSize) > (uint32)sizeof(Eth_MemManagerType))                              
      {
        /* The create heap node */
        LpNewBlock = (Eth_MemManagerType *)((uint8 *)LpHeapNode + LulRequiredSize);                                     /* PRQA S 3305, 0310, 0751, 0488 # JV-01, JV-01, JV-01, JV-01 */
        LpNewBlock->ulHeapSize = LpHeapNode->ulHeapSize - LulRequiredSize;                                              
        LpNewBlock->blHeapLock = ETH_FALSE;

        /* Re-chain as circular list */
        LpHeapNode->pNext->pPrev = LpNewBlock;
        LpNewBlock->pNext = LpHeapNode->pNext;
        LpHeapNode->pNext = LpNewBlock;
        LpNewBlock->pPrev = LpHeapNode;

        /* Reserved this heap block */
        LpHeapNode->ulHeapSize = LulRequiredSize;
        LpHeapNode->blHeapLock = ETH_TRUE;

        /* Set next heap node search start position */
        Eth_GpRamManager[LulCtrlIdx] = LpNewBlock;                                                                      
      }
      else
      {
        /* Allocate this heap node without separate the heap node */
        LpHeapNode->blHeapLock = ETH_TRUE;
      }
      LulRetAddress = (uint32)LpHeapNode + (uint32)sizeof(Eth_MemManagerType);                                          /* PRQA S 0306, 3383 # JV-01, JV-01 */
      break;
    }
    else
    {
      LpHeapNode = LpHeapNode->pNext;
    }
  } while (LpHeapNode != Eth_GpRamManager[LulCtrlIdx]);

  return (LulRetAddress);
}
/***********************************************************************************************************************
** Function Name         : Eth_Ram_Free
**
** Service ID            : NA
**
** Description           : This free RAM at given address
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulCtrlIdx - Index of the controller
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
** Global Variable(s)    : Eth_GpRamManager
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_473,
** Reference ID          : ETH_DUD_ACT_473_GLB001, ETH_DUD_ACT_473_GLB002
***********************************************************************************************************************/
FUNC(void, ETH_PRIVATE_CODE) Eth_Ram_Free(                                                                              /* PRQA S 1505 # JV-01 */
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulMemAddr)
{
  Eth_MemManagerType *LpFreeNode;

  if (0UL != LulMemAddr)
  {
    /* Get the address of memory node */
    LpFreeNode = (Eth_MemManagerType *)(LulMemAddr - (uint32)sizeof(Eth_MemManagerType));                               /* PRQA S 0306, 3383 # JV-01, JV-01 */

    /* If the next node is empty and the next node does not to LpFreeNode */
    if ((ETH_FALSE == LpFreeNode->pNext->blHeapLock) && (LpFreeNode != LpFreeNode->pNext))                              
    {
      if (LpFreeNode < LpFreeNode->pNext)
      {
        /* Marge next heap block into the LpFreeNode */
        if (LpFreeNode->pNext == Eth_GpRamManager[LulCtrlIdx])                                                          
        {
          /* Change heap search start position to the LpFreeNode */
          Eth_GpRamManager[LulCtrlIdx] = LpFreeNode;                                                                    
        }
        else
        {
          /* No action required */
        }

        /* Re-chain circular list */
        LpFreeNode->ulHeapSize += LpFreeNode->pNext->ulHeapSize;                                                        /* PRQA S 3383 # JV-01 */
        LpFreeNode->pNext->pNext->pPrev = LpFreeNode;
        LpFreeNode->pNext = LpFreeNode->pNext->pNext;
      }
      else
      {
        /* No action required */
      }
    }
    else
    {
      /* No action required */
    }

    /* If the prev node is empty and the prev node does not to LpFreeNode */
    if ((ETH_FALSE == LpFreeNode->pPrev->blHeapLock) && (LpFreeNode != LpFreeNode->pPrev))                              
    {
      if (LpFreeNode > LpFreeNode->pPrev)
      {
        /* Marge LpFreeNode into the prev node */
        if (LpFreeNode == Eth_GpRamManager[LulCtrlIdx])                                                                 
        {
          /* Change heap search start position to the prev node */
          Eth_GpRamManager[LulCtrlIdx] = LpFreeNode->pPrev;                                                             
        }
        else
        {
          /* No action required */
        }

        /* Re-chain circular list */
        LpFreeNode->pPrev->ulHeapSize += LpFreeNode->ulHeapSize;                                                        /* PRQA S 3383 # JV-01 */
        LpFreeNode->pNext->pPrev = LpFreeNode->pPrev;
        LpFreeNode->pPrev->pNext = LpFreeNode->pNext;
      }
      else
      {
        /* No action required */
      }
    }
    else
    {
      /* No action required */
    }
    LpFreeNode->blHeapLock = ETH_FALSE;
  }
  else
  {
    /* No action required */
  }
}
/***********************************************************************************************************************
** Function Name         : Eth_Ram_GetNextFreeAddr
**
** Service ID            : NA
**
** Description           : This returns the next free memory address
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulCtrlIdx - Index of the controller
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : LulRamNextFreeAddr - Next free memory address
**
** Preconditions         : None
**
** Global Variable(s)    : Eth_GpRamManager
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_474, ETH_DUD_ACT_474_GBL001
***********************************************************************************************************************/
FUNC(uint32, ETH_PRIVATE_CODE) Eth_Ram_GetNextFreeAddr(                                                                 
  CONST(uint32, AUTOMATIC) LulCtrlIdx)
{
  return (uint32)Eth_GpRamManager[LulCtrlIdx] + (uint32)sizeof(Eth_MemManagerType);                                     /* PRQA S 0306, 3383 # JV-01, JV-01 */
}
/***********************************************************************************************************************
** Function Name         : Eth_Ram_SetCircularAddr
**
** Service ID            : NA
**
** Description           : This set the circular address
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulCtrlIdx - Index of the controller
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variable(s)    : Eth_GpRamManager
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_475, ETH_DUD_ACT_475_GBL001
***********************************************************************************************************************/
FUNC(void, ETH_PRIVATE_CODE) Eth_Ram_SetCircularAddr(                                                                   
  CONST(uint32, AUTOMATIC) LulCtrlIdx)
{
  Eth_GpRamManager[LulCtrlIdx]->pNext = Eth_GpRamManager[LulCtrlIdx];                                                   
  Eth_GpRamManager[LulCtrlIdx]->pPrev = Eth_GpRamManager[LulCtrlIdx];
}
/***********************************************************************************************************************
** Function Name         : Eth_ETNF_FindTxBufferHandler
**
** Service ID            : NA
**
** Description           : This get the tx buffer handler associated with
**                         the specified buffer index.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulCtrlIdx - Index of controller
**                         LulBufIdx  - Index of tx buffer
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variable(s)    : Eth_GaaTxBufferIndex
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_476, ETH_DUD_ACT_476_GBL001
***********************************************************************************************************************/
FUNC(Eth_BufHandlerType *, ETH_PRIVATE_CODE) Eth_ETNF_FindTxBufferHandler(
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulBufIdx)
{
  return Eth_GaaTxBufferIndex[LulCtrlIdx][LulBufIdx].pBufferHdr;                                                        
}

/***********************************************************************************************************************
** Function Name         : FindTxQueue
**
** Service ID            : NA
**
** Description           : This function find the Tx Queue associated
**                         with the passed priority. Otherwise return the default Queue.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LucPriority
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : LucRetQidx
**
** Preconditions         : None
**
** Global Variables Used : Eth_GpCtrlConfigPtr
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_477
***********************************************************************************************************************/
#if (ETH_QOS_SUPPORT == STD_ON)
STATIC FUNC(Eth_TxChannelType, ETH_PRIVATE_CODE) FindTxQueue(
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint8, AUTOMATIC) LucPriority)
{
  uint8 LucRetQidx;
  uint8 LucIdx;
  uint8 LucTotalPriorities;
  P2CONST(Eth_ETNFConfigType, AUTOMATIC, ETH_APPL_DATA) LpHwUnitConfig;
  LpHwUnitConfig = (P2CONST(Eth_ETNFConfigType, AUTOMATIC, ETH_APPL_DATA))                                              /* PRQA S 0316 # JV-01 */
    Eth_GpCtrlConfigPtr[LulCtrlIdx].pHwUnitConfig;
  LucRetQidx = LpHwUnitConfig->stCtrlPriority.ucDflTxQueue;                                                             
  LucTotalPriorities = LpHwUnitConfig->stCtrlPriority.ucNumberOfPriorities;

  for (LucIdx = 0U; LucIdx < LucTotalPriorities; LucIdx++)
  {
    if (LpHwUnitConfig->stCtrlPriority.pPriorityTable[LucIdx].ucEthCtrlPriorityValue == LucPriority)                    
    {
      /* Found Traffic associated to the passed Priority */
      /* Return Corresponding Tx Queue and exit */
      LucRetQidx = LpHwUnitConfig->stCtrlPriority.pPriorityTable[LucIdx].ucEthCtrlTxQueueId;
      /* Exit the loop */
      break;
    }
    else
    {
      /* No action required */
    }
  }

  return ((Eth_TxChannelType)LucRetQidx);                                                                               /* PRQA S 4342 # JV-01 */
}
#endif

#define ETH_STOP_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* ETH_MACRO_ETNF == STD_ON */
/***********************************************************************************************************************
**                                               End of File                                                          **
***********************************************************************************************************************/
