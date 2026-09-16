/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Eth_ETNF_Dma.c                                                                                      */
/*====================================================================================================================*/
/*                                            COPYRIGHT                                                               */
/*====================================================================================================================*/
/* (c) 2023 - 2025 Renesas Electronics Corporation. All rights reserved.                                              */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains DMAC functions implementation of Ethernet Driver  Component.                                    */
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
/*                                        Devices:        X2x                                                         */
/*====================================================================================================================*/

/***********************************************************************************************************************
**                                     Revision Control History                                                       **
***********************************************************************************************************************/
/*
 * 2.4.1: 30/06/2025    : Remove the SW-VERSION from header of file
 * 2.4.0: 30/05/2025    : Update SW-VERSION for RH850/Ver22.01.02 U2Cx release
 * 2.3.1: 31/03/2025    : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 * 2.3.0: 28/02/2025    : - As per ticket ARDAACJ-695:
 *                        + Update to provide correct support for the function Eth_ETNF_GetTimeOutValue and 
 *                        change the name to Eth_ETNF_GetElapsedTimeValue
 *                        + Update the impact on the functions: Eth_Hw_ETNF_OpModeChange, Eth_Hw_ETNF_DisableController
 *                        Eth_Hw_ETNF_WaitPTPRequestIsComplete
 * 2.2.0: 31/12/2024    : Update SW-VERSION for Ver22.02.00(D) U2Bx Final Release
 * 2.1.2: 31/10/2024    : Increase SW-VERSION to 2.1.2
 * 2.1.1: 12/08/2024    : Changed logic code for searching Tx/Rx configuration index in SetDescChanin
 *        22/07/2024    : Update QAC message
 * 2.0.2: 17/04/2024    : Update QAC message.
 *        10/01/2024    : Added a condition to get time stamp status for Stream channel in SetDescChain
 *        04/01/2024    : Redesign SetDescChain to improve function metric STCYC
 *        26/12/2023    : Update QAC message.
 *        30/11/2023    : Add configures if MAC transmission status of the frame is stored in MAC status FIFO
 * 1.0.0: 30/11/2023    : Initial Version
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                        Include Section                                                             **
***********************************************************************************************************************/
/* Included for module version information and other types declarations */
#include "Eth.h"
/* Included for prototypes for internal functions of Ethernet Component */
#include "Eth_ETNF_Dma.h"
/* Included for Ethernet Component register types used within the module */
#include "Eth_ETNF_Ram.h"
#include "Eth_Ram.h"
#include "EthIf_Cbk.h"

#if (ETH_CRITICAL_SECTION_PROTECTION == STD_ON)
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
#define ETH_ETNF_DMA_C_AR_RELEASE_MAJOR_VERSION  ETH_AR_RELEASE_MAJOR_VERSION_VALUE
#define ETH_ETNF_DMA_C_AR_RELEASE_MINOR_VERSION  ETH_AR_RELEASE_MINOR_VERSION_VALUE
#define ETH_ETNF_DMA_C_AR_RELEASE_REVISION_VERSION  ETH_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define ETH_ETNF_DMA_C_SW_MAJOR_VERSION    ETH_SW_MAJOR_VERSION_VALUE
#define ETH_ETNF_DMA_C_SW_MINOR_VERSION    ETH_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                          Version Check                                                             **
***********************************************************************************************************************/

/* Functionality related to R4.0 */
#if (ETH_ETNF_DMA_AR_RELEASE_MAJOR_VERSION !=  ETH_ETNF_DMA_C_AR_RELEASE_MAJOR_VERSION)
  #error "Eth_ETNF_Dma.c : Mismatch in Release Major Version"
#endif
#if (ETH_ETNF_DMA_AR_RELEASE_MINOR_VERSION !=  ETH_ETNF_DMA_C_AR_RELEASE_MINOR_VERSION)
  #error "Eth_ETNF_Dma.c : Mismatch in Release Minor Version"
#endif
#if (ETH_ETNF_DMA_AR_RELEASE_REVISION_VERSION !=  ETH_ETNF_DMA_C_AR_RELEASE_REVISION_VERSION)
  #error "Eth_ETNF_Dma.c : Mismatch in Release Revision Version"
#endif

#if (ETH_ETNF_DMA_SW_MAJOR_VERSION != ETH_ETNF_DMA_C_SW_MAJOR_VERSION)
  #error "Eth_ETNF_Dma.c : Mismatch in Software Major Version"
#endif
#if (ETH_ETNF_DMA_SW_MINOR_VERSION != ETH_ETNF_DMA_C_SW_MINOR_VERSION)
  #error "Eth_ETNF_Dma.c : Mismatch in Software Minor Version"
#endif

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7                                                                       */
/*                       REFERENCE - ISO:C90-6.3.1 Primary Expressions                                                */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is           */
/*                       accepted.                                                                                    */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3678)    : The object referenced by '%1s' is not modified through it, so '%1s' could be declared        */
/*                       with type '%2s'.                                                                             */
/* Rule                : MISRA C:2012 Rule-8.13                                                                       */
/* JV-01 Justification : The object addressed by this pointer change so it can not be of type "pointer to const"      */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0306)    : [I] Cast between a pointer to object and an integral type.                                   */
/* Rule                : CERTCCM INT36, MISRA C:2012 Rule-11.4                                                        */
/*                       REFERENCE - ISO:C90-6.3.4  Semantics                                                         */
/* JV-01 Justification : The address is cast into a field provided by the hardware. The address passed has been       */
/*                       reviewed and found to be okay.                                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0316)    : [I] Cast from a pointer to void to a pointer to object type.                                 */
/* Rule                : MISRA C:2012 Rule-11.5                                                                       */
/* JV-01 Justification : The information required for each IP is different, so it is declared as void pointer.        */
/*       Verification  : Out-of-range access does not occur because Generation Tool outputs with Eth_ETNFConfigType.  */
/**********************************************************************************************************************/
/* Message (2:3469)    : This usage of a function-like macro looks like it could be replaced by an equivalent         */
/*                       function call.                                                                               */
/* Rule                : MISRA C:2012 Dir-4.9                                                                         */
/* JV-01 Justification : To prevent overhead and speed up the processing, there is no need to call a function         */
/*                       here for such a small operation.                                                             */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3673)    : The object addressed by the pointer parameter '%s' is not modified and so the pointer        */
/*                       could be of type 'pointer to const'.                                                         */
/* Rule                : CERTCCM DCL00, DCL13, MISRA C:2012 Rule-8.13                                                 */
/* JV-01 Justification : Pointer variable is used to modify the value at the address so the pointer cannot be         */
/*                       declared as 'pointer to const' type.                                                         */
/*       Verification  : It cannot be declared in cosnt because it may be overwritten.                                */
/**********************************************************************************************************************/
/* Message (2:0759)    : An object of union type has been defined.                                                    */
/* Rule                : MISRA C:2012 Rule-19.2                                                                       */
/* JV-01 Justification : Data access of larger data types is used to achieve better throughput.                       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:3383)    : Cannot identify wraparound guard for unsigned arithmetic expression.                         */
/* Rule                : CERTCCM INT30                                                                                */
/* JV-01 Justification : Wraparound can't be occur in this unsigned integer arithmetic so there is no need to add     */
/*                       a wraparound guard here.                                                                     */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1505)    : The function 'name' is only referenced in the translation unit where it is defined.          */
/* Rule                : CERTCCM DCL19, MISRA C:2012 Rule-8.7                                                         */
/* JV-01 Justification : This is accepted, due to following coding rule, internal function can be defined in          */
/*                       other C source files                                                                         */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:3384)    : Cannot identify wraparound guard for dependent unsigned arithmetic expression.               */
/* Rule                : CERTCCM INT30                                                                                */
/* JV-01 Justification : Wraparound can't be occur in this unsigned integer arithmetic so there is no need to add     */
/*                       a wraparound guard here.                                                                     */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:2469)    : Loop control variable in this 'for' statement LucCount is modified in the body of the        */
/*                       loop.                                                                                        */
/* Rule                : MISRA C:2012 Rule-14.2                                                                       */
/* JV-01 Justification : This is to exit from the linear search loop when the required channel Id is found.           */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:4391)    : A composite expression of 'essentially unsigned' type (unsigned char) is being cast to a     */
/*                       wider unsigned type 'unsigned short'.                                                        */
/* Rule                : MISRA C:2012 Rule-10.8                                                                       */
/* JV-01 Justification : This is necessary to support configuration. The actuall array can't be decided statically.   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0488)    : Performing pointer arithmetic.                                                               */
/* Rule                : CERTCCM EXP08, MISRA C:2012 Rule-18.4                                                        */
/* JV-01 Justification : This implementation is required for heap memory allocation algorithm                         */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3416)    : Logical operation performed on expression with possible side effects.                        */
/* Rule                : CERTCCM EXP45, CWE Rule CWE-398, CWE-569, CWE-737                                            */
/* JV-01 Justification : This is necessary for suppressing optimization by dummy loop.                                */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:5087)    : Use of #include directive after code fragment.                                               */
/* Rule                : MISRA C:2012 Rule-20.1                                                                       */
/* JV-01 Justification : This is accepted, due to implementation for include memmap is following AUTOSAR rule.        */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3206)    : The parameter '%s' is not used in this function.                                             */
/* Rule                : CERTCCM MSC07, MSC13, MISRA C:2012 Rule-2.7, CWE Rule CWE-398, CWE-563, CWE-569              */
/* JV-01 Justification : This is done as per implementation requirement                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:2814)    : Possible: Dereference of NULL pointer.                                                       */
/* Rule                : CERTCCM EXP34, CWE Rule CWE-476, CWE-465, CWE-737, CWE-690                                   */
/* JV-01 Justification : To prevent overhead and excessive nesting of condition statements, this pointer has been     */
/*                       tested valid with many test cases, so there is no problem with the current implementation.   */
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
/* Rule                : CERTCCM EXP08, ARR30, ARR37, ARR38, CWE Rule CWE-120, CWE-121, CWE-122, CWE-124, CWE-125,    */
/*                       CWE-126, CWE-127, CWE-129, CWE-131, CWE-469, CWE-823, CWE-465, CWE-633, CWE-740              */
/* JV-01 Justification : This message prevents existing of an out-of-range pointer                                    */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                              Global Data                                                           **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                              Function Definitions                                                  **
***********************************************************************************************************************/
#define ETH_START_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"

STATIC FUNC(void, ETH_PRIVATE_CODE) RxBeProcess(CONST(uint32, AUTOMATIC) LulCtrlIdx,
  CONSTP2VAR(Eth_RxFrameType, AUTOMATIC, ETH_APPL_DATA) LpSingleRxFramePtr,                                             /* PRQA S 3432 # JV-01 */
  CONST(uint32, AUTOMATIC) LulDescPtr);

STATIC FUNC(void, ETH_PRIVATE_CODE) RxNcProcess(CONST(uint32, AUTOMATIC) LulCtrlIdx,
  CONSTP2VAR(Eth_RxFrameType, AUTOMATIC, ETH_APPL_DATA) LpSingleRxFramePtr,                                             /* PRQA S 3432 # JV-01 */
  CONST(uint32, AUTOMATIC) LulDescPtr);

STATIC FUNC(void, ETH_PRIVATE_CODE) RxSProcess(CONST(uint32, AUTOMATIC) LulCtrlIdx,
  CONSTP2VAR(Eth_RxFrameType, AUTOMATIC, ETH_APPL_DATA) LpSingleRxFramePtr,                                             /* PRQA S 3432 # JV-01 */
  CONST(uint32, AUTOMATIC) LulChannelNum, CONST(uint32, AUTOMATIC) LulDescPtr);

STATIC FUNC(void, ETH_PRIVATE_CODE) SetDescChain(
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulAddr, CONST(uint8, AUTOMATIC) LucQidx,
  CONST(Eth_DirectionType, AUTOMATIC) LenDir);

STATIC FUNC(void, ETH_PRIVATE_CODE) SetFempty(
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONSTP2VAR(Eth_DataDescType, AUTOMATIC, ETH_APPL_DATA) LpDescr,                  /* PRQA S 3432 # JV-01 */
  CONST(uint8, AUTOMATIC) LucQidx, CONST(Eth_DirectionType, AUTOMATIC) LenQdir,
  CONST(Eth_BufIdxType, AUTOMATIC) LulBufIdx);

STATIC FUNC(void, ETH_PRIVATE_CODE) SetExtFempty(
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONSTP2VAR(Eth_ExtDataDescType, AUTOMATIC, ETH_APPL_DATA) LpDescr,               /* PRQA S 3432 # JV-01 */
  CONST(uint8, AUTOMATIC) LucQidx, CONST(Eth_DirectionType, AUTOMATIC) LenQdir,
  CONST(Eth_BufIdxType, AUTOMATIC) LulBufIdx);

STATIC FUNC(void, ETH_PRIVATE_CODE) SetLinkFix(
  CONST(uint32, AUTOMATIC) LulLinkDesc, CONST(uint32, AUTOMATIC) LulAddrToLink);

STATIC FUNC(void, ETH_PRIVATE_CODE) TxRxConfig(
  CONST(uint32, AUTOMATIC) LulCtrlIdx,
  CONSTP2CONST(Eth_TxConfigType, AUTOMATIC, ETH_APPL_DATA) LpTxConfig,
  CONSTP2CONST(Eth_RxConfigTypeEtnf, AUTOMATIC, ETH_APPL_DATA) LpRxConfig);

STATIC FUNC(uint32, ETH_PRIVATE_CODE) DescUpdate(
  CONST(uint32, AUTOMATIC) LulDescPtr);

STATIC FUNC(uint32, ETH_PRIVATE_CODE) DescTsUpdate(
  CONST(uint32, AUTOMATIC) LulDescPtr);

STATIC FUNC(void, ETH_PRIVATE_CODE) RxQueueSet(
  CONST(uint32, AUTOMATIC) LulCtrlIdx);

STATIC FUNC(uint32, ETH_PRIVATE_CODE) RxDescChainUpdate(
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulDescPtr,
  CONSTP2CONST(Eth_RxChConfigType, AUTOMATIC, ETH_APPL_DATA) LpChConfig);

STATIC FUNC(void, ETH_PRIVATE_CODE) RxCallEthIf(
  CONST(uint32, AUTOMATIC) LulCtrlIdx,
  CONSTP2CONST(Eth_RxFrameType, AUTOMATIC,ETH_APPL_DATA) LpFrame);

STATIC FUNC(void, ETH_PRIVATE_CODE) TxRxIntConfig(
  CONST(uint32, AUTOMATIC) LulCtrlIdx);

STATIC FUNC(uint32, ETH_PRIVATE_CODE) AllocMemForDesc(
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint8, AUTOMATIC) LucQidx,
  CONST(Eth_DirectionType, AUTOMATIC) LenQdir);

STATIC FUNC(void, ETH_PRIVATE_CODE) FillDescMemory(
  CONSTP2VAR(Eth_LinkDescType, AUTOMATIC, ETH_APPL_DATA) LpLinkDescr, CONST(uint32, AUTOMATIC) LulDescAddr);            /* PRQA S 3432 # JV-01 */

STATIC FUNC(boolean, ETH_PRIVATE_CODE) IsQueueConfigured(
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint8, AUTOMATIC) LucQidx,
  CONST(Eth_DirectionType, AUTOMATIC) LenDir);

#if (ETH_STREAM_FILTERING == STD_ON)
STATIC FUNC(void,  ETH_PRIVATE_CODE) SetRxFilter(
  CONST(uint32, AUTOMATIC) LulCtrlIdx);
#endif

#if (ETH_UPDATE_PHYS_ADDR_FILTER == STD_ON)
STATIC FUNC(boolean, ETH_PRIVATE_CODE) IsRxFrameValid(
  CONST(uint32, AUTOMATIC) LulCtrlIdx,
  CONSTP2CONST(Eth_RxFrameType, AUTOMATIC, ETH_APPL_DATA) LpRxFrame);
#endif

#if (ETH_QOS_SUPPORT == STD_ON)
STATIC FUNC(void, ETH_PRIVATE_CODE) SetCbsParameter(
  CONST(uint32, AUTOMATIC) LulCtrlIdx);
#endif

/***********************************************************************************************************************
** Function Name         : RxBeProcess
**
** Service ID            : NA
**
** Description           : This process best effort queue
**                         (The PS bit isn't checked.)
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulCtrlIdx - Ethernet channel number
**                       : LulRxFramePtr - pointer to rx frame
**                       : LulDescPtr - pointer to rx Descriptor
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
** Reference ID          : ETH_DUD_ACT_401,
** Reference ID          : ETH_DUD_ACT_401_GBL001, ETH_DUD_ACT_401_GBL002
** Reference ID          : ETH_DUD_ACT_401_GBL003
***********************************************************************************************************************/
STATIC FUNC(void, ETH_PRIVATE_CODE) RxBeProcess(
  CONST(uint32, AUTOMATIC) LulCtrlIdx,
  CONSTP2VAR(Eth_RxFrameType, AUTOMATIC, ETH_APPL_DATA) LpSingleRxFramePtr,                                             /* PRQA S 3432 # JV-01 */
  CONST(uint32, AUTOMATIC) LulDescPtr)
{
  P2VAR(Eth_DataDescType, AUTOMATIC, ETH_APPL_DATA) LpDataDesc;                                                         /* PRQA S 3432, 3678 # JV-01, JV-01 */
  P2VAR(Eth_ExtDataDescType, AUTOMATIC, ETH_APPL_DATA) LpExtDataDesc;                                                   /* PRQA S 3432, 3678 # JV-01, JV-01 */
  Eth_OptionType LenRxBeTimestamp;

  LenRxBeTimestamp = Eth_GaaCtrlStat[LulCtrlIdx].stHwStatEtnf.enRxBeTimestamp;                                          

  /* single frame single buffer */
  if (ETH_ENABLE == LenRxBeTimestamp)
  {
    /* timestamp enabled */
    LpExtDataDesc = (P2VAR(Eth_ExtDataDescType, AUTOMATIC, ETH_APPL_DATA)) LulDescPtr;                                  /* PRQA S 0306, 3432 # JV-01, JV-01 */

    if (ETH_DESC_FSINGLE_AVB == LpExtDataDesc->stHeader.ulDt)                                                           
    {
      /* descriptor type correct */
      LpSingleRxFramePtr->ulFrameAddr   = LpExtDataDesc->ulDptr;                                                        
      LpSingleRxFramePtr->ulEthTypeAddr = LpExtDataDesc->ulDptr + ETH_SRC_DST_ADDRESS_SIZE;                             /* PRQA S 3383 # JV-01 */
      LpSingleRxFramePtr->ulFrameLength = LpExtDataDesc->stHeader.ulDs;
      LpSingleRxFramePtr->stTimestamp   = LpExtDataDesc->stTimestamp;
      LpSingleRxFramePtr->enTimeQual    = ETH_VALID;
    }
    else
    {
      /* descriptor type incorrect */
      LpSingleRxFramePtr->ulFrameAddr   = 0UL;
      LpSingleRxFramePtr->ulFrameLength = 0UL;
    }
    LpExtDataDesc++;                                                                                                    
    while ((LpExtDataDesc->stHeader.ulDt == ETH_DESC_LINKFIX) ||                                                        
      (LpExtDataDesc->stHeader.ulDt == ETH_DESC_LINK_AVB))
    {
      LpExtDataDesc = (P2VAR(Eth_ExtDataDescType, AUTOMATIC, ETH_APPL_DATA)) LpExtDataDesc->ulDptr;                     /* PRQA S 0306, 3432 # JV-01, JV-01 */

    }

    Eth_GaaCtrlStat[LulCtrlIdx].stHwStatEtnf.aaNextRxDesc[(uint32)ETH_BECHANNEL] = (uint32)LpExtDataDesc;               /* PRQA S 0306 # JV-01 */
  }
  else
  {
    /* timestamp disabled */
    LpDataDesc = (P2VAR(Eth_DataDescType, AUTOMATIC, ETH_APPL_DATA)) LulDescPtr;                                        /* PRQA S 0306, 3432 # JV-01, JV-01 */

    if (ETH_DESC_FSINGLE_AVB == LpDataDesc->stHeader.ulDt)                                                              
    {
      /* descriptor type correct */
      LpSingleRxFramePtr->ulFrameAddr   = LpDataDesc->ulDptr;
      LpSingleRxFramePtr->ulEthTypeAddr = LpDataDesc->ulDptr + ETH_SRC_DST_ADDRESS_SIZE;                                /* PRQA S 3383 # JV-01 */
      LpSingleRxFramePtr->ulFrameLength = LpDataDesc->stHeader.ulDs;
      LpSingleRxFramePtr->enTimeQual    = ETH_INVALID;
    }
    else
    {
      /* descriptor type incorrect */
      LpSingleRxFramePtr->ulFrameAddr   = 0UL;
      LpSingleRxFramePtr->ulFrameLength = 0UL;
    }
    LpDataDesc++;                                                                                                       

    while ((LpDataDesc->stHeader.ulDt == ETH_DESC_LINKFIX) ||                                                           
      (LpDataDesc->stHeader.ulDt == ETH_DESC_LINK_AVB))
    {
      LpDataDesc = (P2VAR(Eth_DataDescType, AUTOMATIC, ETH_APPL_DATA)) LpDataDesc->ulDptr;                              /* PRQA S 0306, 3432 # JV-01, JV-01 */
    }

    Eth_GaaCtrlStat[LulCtrlIdx].stHwStatEtnf.aaNextRxDesc[(uint32)ETH_BECHANNEL] = (uint32)LpDataDesc;                  /* PRQA S 0306 # JV-01 */
  }

}

/***********************************************************************************************************************
** Function Name         : RxNcProcess
**
** Service ID            : NA
**
** Description           : This  process network control queue
**                         (The PS bit isn't checked.)
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulCtrlIdx - Ethernet channel number
**                       : LulRxFramePtr - pointer to rx frame
**                       : LulDescPtr - pointer to rx Descriptor
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
** Reference ID          : ETH_DUD_ACT_402,
** Reference ID          : ETH_DUD_ACT_402_GBL001, ETH_DUD_ACT_402_GBL002
***********************************************************************************************************************/
STATIC FUNC(void, ETH_PRIVATE_CODE) RxNcProcess(
  CONST(uint32, AUTOMATIC) LulCtrlIdx,
  CONSTP2VAR(Eth_RxFrameType, AUTOMATIC, ETH_APPL_DATA) LpSingleRxFramePtr,                                             /* PRQA S 3432 # JV-01 */
  CONST(uint32, AUTOMATIC) LulDescPtr)
{
  P2VAR(Eth_ExtDataDescType, AUTOMATIC, ETH_APPL_DATA) LpExtDataDesc;                                                   /* PRQA S 3432, 3678 # JV-01, JV-01 */

  LpExtDataDesc = (P2VAR(Eth_ExtDataDescType, AUTOMATIC, ETH_APPL_DATA)) LulDescPtr;                                    /* PRQA S 0306, 3432 # JV-01, JV-01 */

  if (ETH_DESC_FSINGLE_AVB == LpExtDataDesc->stHeader.ulDt)                                                             
  {
    /* descriptor type correct */
    LpSingleRxFramePtr->ulFrameAddr   = LpExtDataDesc->ulDptr;                                                          
    LpSingleRxFramePtr->ulEthTypeAddr = LpExtDataDesc->ulDptr + ETH_SRC_DST_ADDRESS_SIZE;                               /* PRQA S 3383 # JV-01 */
    LpSingleRxFramePtr->ulFrameLength = LpExtDataDesc->stHeader.ulDs;
    LpSingleRxFramePtr->stTimestamp   = LpExtDataDesc->stTimestamp;
    LpSingleRxFramePtr->enTimeQual    = ETH_VALID;
  }
  else
  {
    /* descriptor type incorrect */
    LpSingleRxFramePtr->ulFrameAddr   = 0UL;
    LpSingleRxFramePtr->ulFrameLength = 0UL;
  }

  LpExtDataDesc++;                                                                                                      
  while ((LpExtDataDesc->stHeader.ulDt == ETH_DESC_LINKFIX) ||                                                          
    (LpExtDataDesc->stHeader.ulDt == ETH_DESC_LINK_AVB))
  {
    LpExtDataDesc = (P2VAR(Eth_ExtDataDescType, AUTOMATIC, ETH_APPL_DATA)) LpExtDataDesc->ulDptr;                       /* PRQA S 0306, 3432 # JV-01, JV-01 */
  }

  Eth_GaaCtrlStat[LulCtrlIdx].stHwStatEtnf.aaNextRxDesc[(uint32)ETH_NCCHANNEL] = (uint32)LpExtDataDesc;                 /* PRQA S 0306 # JV-01 */
}

/***********************************************************************************************************************
** Function Name         : RxSProcess
**
** Service ID            : NA
**
** Description           : This  process stream queue
**                         (The PS bit isn't checked.)
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulCtrlIdx       - Instance number
**                       : LulRxFramePtr - pointer to rx frame
**                       : LulChannelNum - stream channel number
**                       : LulDescPtr - pointer to rx Descriptor
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
** Reference ID          : ETH_DUD_ACT_403,
** Reference ID          : ETH_DUD_ACT_403_GBL001, ETH_DUD_ACT_403_GBL002
** Reference ID          : ETH_DUD_ACT_403_GBL003
***********************************************************************************************************************/
STATIC FUNC(void, ETH_PRIVATE_CODE) RxSProcess(
  CONST(uint32, AUTOMATIC) LulCtrlIdx,
  CONSTP2VAR(Eth_RxFrameType, AUTOMATIC, ETH_APPL_DATA) LpSingleRxFramePtr,                                             /* PRQA S 3432 # JV-01 */
  CONST(uint32, AUTOMATIC) LulChannelNum, CONST(uint32, AUTOMATIC) LulDescPtr)
{
  P2VAR(Eth_DataDescType, AUTOMATIC, ETH_APPL_DATA) LpDataDesc;                                                         /* PRQA S 3432, 3678 # JV-01, JV-01 */
  P2VAR(Eth_ExtDataDescType, AUTOMATIC, ETH_APPL_DATA) LpExtDataDesc;                                                   /* PRQA S 3432, 3678 # JV-01, JV-01 */
  Eth_OptionType LenRxSTimestamp;

  LenRxSTimestamp = Eth_GaaCtrlStat[LulCtrlIdx].stHwStatEtnf.enRxSTimestamp;                                            

  /* single frame single buffer */
  if (ETH_ENABLE == LenRxSTimestamp)
  {
    /* timestamp enabled */
    LpExtDataDesc = (P2VAR(Eth_ExtDataDescType, AUTOMATIC, ETH_APPL_DATA)) LulDescPtr;                                  /* PRQA S 0306, 3432 # JV-01, JV-01 */

    if (ETH_DESC_FSINGLE_AVB == LpExtDataDesc->stHeader.ulDt)                                                           
    {
      /* descriptor type correct */
      LpSingleRxFramePtr->ulFrameAddr   = LpExtDataDesc->ulDptr;                                                        
      LpSingleRxFramePtr->ulEthTypeAddr = LpExtDataDesc->ulDptr + ETH_SRC_DST_ADDRESS_SIZE;                             /* PRQA S 3383 # JV-01 */
      LpSingleRxFramePtr->ulFrameLength = LpExtDataDesc->stHeader.ulDs;
      LpSingleRxFramePtr->stTimestamp   = LpExtDataDesc->stTimestamp;
      LpSingleRxFramePtr->enTimeQual    = ETH_VALID;
    }
    else
    {
      /* descriptor type incorrect */
      LpSingleRxFramePtr->ulFrameAddr   = 0UL;
      LpSingleRxFramePtr->ulFrameLength = 0UL;
    }
    LpExtDataDesc++;                                                                                                    
    while ((LpExtDataDesc->stHeader.ulDt == ETH_DESC_LINKFIX) ||                                                        
      (LpExtDataDesc->stHeader.ulDt == ETH_DESC_LINK_AVB))
    {
      LpExtDataDesc = (P2VAR(Eth_ExtDataDescType, AUTOMATIC, ETH_APPL_DATA)) LpExtDataDesc->ulDptr;                     /* PRQA S 0306, 3432 # JV-01, JV-01 */
    }

    Eth_GaaCtrlStat[LulCtrlIdx].stHwStatEtnf.aaNextRxDesc[LulChannelNum] = (uint32)LpExtDataDesc;                       /* PRQA S 0306 # JV-01 */
  }
  else
  {
    /* timestamp disabled */
    LpDataDesc = (P2VAR(Eth_DataDescType, AUTOMATIC, ETH_APPL_DATA)) LulDescPtr;                                        /* PRQA S 0306, 3432 # JV-01, JV-01 */

    if (ETH_DESC_FSINGLE_AVB == LpDataDesc->stHeader.ulDt)                                                              
    {
      /* descriptor type correct */
      LpSingleRxFramePtr->ulFrameAddr   = LpDataDesc->ulDptr;
      LpSingleRxFramePtr->ulEthTypeAddr = LpDataDesc->ulDptr + ETH_SRC_DST_ADDRESS_SIZE;                                /* PRQA S 3383 # JV-01 */
      LpSingleRxFramePtr->ulFrameLength = LpDataDesc->stHeader.ulDs;
      LpSingleRxFramePtr->enTimeQual    = ETH_INVALID;
    }
    else
    {
      /* descriptor type incorrect */
      LpSingleRxFramePtr->ulFrameAddr   = 0UL;
      LpSingleRxFramePtr->ulFrameLength = 0UL;
    }

    LpDataDesc++;                                                                                                       
    while ((LpDataDesc->stHeader.ulDt == ETH_DESC_LINKFIX) ||                                                           
      (LpDataDesc->stHeader.ulDt == ETH_DESC_LINK_AVB))
    {
      LpDataDesc = (P2VAR(Eth_DataDescType, AUTOMATIC, ETH_APPL_DATA)) LpDataDesc->ulDptr;                              /* PRQA S 0306, 3432 # JV-01, JV-01 */
    }

    Eth_GaaCtrlStat[LulCtrlIdx].stHwStatEtnf.aaNextRxDesc[LulChannelNum] = (uint32)LpDataDesc;                          /* PRQA S 0306 # JV-01 */
  }

}

/***********************************************************************************************************************
** Function Name         : Eth_Hw_ETNF_DMACStructConfig
**
** Service ID            : NA
**
** Description           : This Initializes and enables Ethernet peripheral.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulCtrlIdx - Index of a controller
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variable(s)    : Eth_GaaAvbConfig,
**                       : Eth_GaaRxConfig, Eth_GaaQConfig
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_404,
** Reference ID          : ETH_DUD_ACT_404_GBL001, ETH_DUD_ACT_404_GBL002
** Reference ID          : ETH_DUD_ACT_404_GBL003, ETH_DUD_ACT_404_GBL004
** Reference ID          : ETH_DUD_ACT_404_GBL005, ETH_DUD_ACT_404_GBL009
** Reference ID          : ETH_DUD_ACT_404_GBL010, ETH_DUD_ACT_404_GBL011
***********************************************************************************************************************/
FUNC(void, ETH_PRIVATE_CODE)Eth_Hw_ETNF_DMACStructConfig(                                                               
  CONST(uint32, AUTOMATIC) LulCtrlIdx)
{
  uint32 LulIdx;
  uint8 LucQidx;
  P2CONST(Eth_ETNFConfigType, AUTOMATIC, ETH_APPL_DATA) LpHwUnitConfig;

  LpHwUnitConfig = (P2CONST(Eth_ETNFConfigType, AUTOMATIC, ETH_APPL_DATA))                                              /* PRQA S 0316 # JV-01 */
    Eth_GpCtrlConfigPtr[LulCtrlIdx].pHwUnitConfig;
  /* AVB part */
  Eth_GaaAvbConfig[LulCtrlIdx].stRxConfig.enEncf = LpHwUnitConfig->stRxConfig.enEncf;                                   
  Eth_GaaAvbConfig[LulCtrlIdx].stRxConfig.enEsf  = LpHwUnitConfig->stRxConfig.enEsf;                                    
  Eth_GaaAvbConfig[LulCtrlIdx].stRxConfig.enEts0 = LpHwUnitConfig->stRxConfig.enEts0;                                   
  Eth_GaaAvbConfig[LulCtrlIdx].stRxConfig.enEts2 = LpHwUnitConfig->stRxConfig.enEts2;                                   
  Eth_GaaAvbConfig[LulCtrlIdx].stRxConfig.ulRfcl = ETH_RX_FIFO_CRIT_LVL;                                                
  #if (ETH_STREAM_FILTERING == STD_ON)
  Eth_GaaAvbConfig[LulCtrlIdx].stRxConfig.enSRPTalkerFiltering = LpHwUnitConfig->stRxConfig.enSRPTalkerFiltering;       
  #endif
  Eth_GaaAvbConfig[LulCtrlIdx].stTxConfig.enTsm0 = ETH_TXNORMAL;                                                        
  Eth_GaaAvbConfig[LulCtrlIdx].stTxConfig.enTsm1 = ETH_TXNORMAL;                                                        
  Eth_GaaAvbConfig[LulCtrlIdx].stTxConfig.enTsm2 = ETH_TXNORMAL;                                                        
  Eth_GaaAvbConfig[LulCtrlIdx].stTxConfig.enTsm3 = ETH_TXNORMAL;                                                        
  Eth_GaaAvbConfig[LulCtrlIdx].stTxConfig.enEcbs = LpHwUnitConfig->enEcbs;                                              
  Eth_GaaAvbConfig[LulCtrlIdx].stTxConfig.enTqp = LpHwUnitConfig->enTxConfig;                                           


  /* Read the number of Rx Queue Configured */
  for (LulIdx = 0UL; LulIdx < (uint32)LpHwUnitConfig->stQueueConfig.ucNumberOfRxQueue; LulIdx++)
  {
    LucQidx = LpHwUnitConfig->stQueueConfig.pRxQueueConfig[LulIdx].ucEthRxQueueId;                                      

    Eth_GaaRxConfig[LucQidx].ucChNum    = LucQidx;                                                                      

    if (ETH_BECHANNEL == Eth_GaaRxConfig[LucQidx].ucChNum)
    {
      /* This is Rx BE */
      Eth_GaaRxConfig[LucQidx].enChType = ETH_RX_BE;                                                                    
    }
    else if (ETH_NCCHANNEL == Eth_GaaRxConfig[LucQidx].ucChNum)
    {
      /* This is Rx NC */
      Eth_GaaRxConfig[LucQidx].enChType = ETH_RX_NC;                                                                    
    }
    else
    {
      /* Rx Stream */
      Eth_GaaRxConfig[LucQidx].enChType = ETH_RX_S;                                                                     
    }

    /* Queue Configuration */
    Eth_GaaQConfig[LulIdx].enPia = ETH_GAP32;                                                                           
    Eth_GaaQConfig[LulIdx].enUfcc = ETH_UFCC0;                                                                          
    Eth_GaaQConfig[LulIdx].enRsm = ETH_RXNORMAL;                                                                        

    #if (ETH_STREAM_FILTERING == STD_ON)
    /* Save Pattern Address if Filtering is enabled */
    ETH_COPY_STREAM_ADDRESS(LpHwUnitConfig->stQueueConfig.pRxQueueConfig[LulIdx].aaEthPatternStream,                    /* PRQA S 3469 # JV-01 */
      Eth_GaaRxConfig[LucQidx].aaPatternStream);
    #endif
  }
}

/***********************************************************************************************************************
** Function Name         : Eth_Hw_ETNF_SingleDescFrameSend
**
** Service ID            : NA
**
** Description           : send frame (single frame single buffer)
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulCtrlIdx - Instance number
**                       : LenQIndex - Queue Index
**                       : LpFrame - Tx Frame Pointer
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : LucReturnValue - E_OK / E_NOT_OK
**
** Preconditions         : None
**
** Global Variable(s)    : Eth_GaaCtrlStat, Eth_GaaETNFRegs
**
** Function(s) invoked   : ETH_ENTER_CRITICAL_SECTION,
**                         ETH_EXIT_CRITICAL_SECTION,
**                         Eth_ETNF_CheckProvideBuffer
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_405,
** Reference ID          : ETH_DUD_ACT_405_CRT001, ETH_DUD_ACT_405_CRT002
** Reference ID          : ETH_DUD_ACT_405_GBL001, ETH_DUD_ACT_405_REG001
***********************************************************************************************************************/
FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_Hw_ETNF_SingleDescFrameSend(                                                 
  CONST(uint32, AUTOMATIC) LulCtrlIdx,
  CONSTP2VAR(Eth_BufHandlerType, AUTOMATIC, ETH_APPL_DATA) LpTxBufHdr)                                                  /* PRQA S 3432, 3673 # JV-01, JV-01 */
{
  uint32 LulBufIdx;
  Std_ReturnType LucTxBufferProvide;
  P2VAR(Eth_DataDescType, AUTOMATIC, ETH_APPL_DATA) LpDataDesc;                                                         /* PRQA S 3432 # JV-01 */
  Eth_TxRxCtrl  LunTxCtrl;                                                                                              /* PRQA S 0759 # JV-01 */
  Std_ReturnType LucReturnValue;

  LucTxBufferProvide = E_NOT_OK;
  LucReturnValue = E_OK;

  /* Get next free descriptor */
  LpDataDesc = (P2VAR(Eth_DataDescType, AUTOMATIC, ETH_APPL_DATA))                                                      /* PRQA S 0306, 3432 # JV-01, JV-01 */
    Eth_GaaCtrlStat[LulCtrlIdx].stHwStatEtnf.aaLastTxDesc[LpTxBufHdr->enChannel];                                       

  if (0UL != LpDataDesc->ulDptr)                                                                                        
  {
    /* Check previous TxBuffer release status (The memory leak protect) */
    LulBufIdx = (uint32)((LpDataDesc->stHeader.ulCtrl) & ETH_DESCR_TAG_MASK);
    LucTxBufferProvide = Eth_ETNF_CheckProvideBuffer(LulCtrlIdx, LulBufIdx);
  }
  else
  {
    /* No action required */
  }

  if ((ETH_DESC_FEMPTY_AVB == LpDataDesc->stHeader.ulDt) && (E_NOT_OK == LucTxBufferProvide))
  {
    LunTxCtrl.ulWord = 0UL;
    if (ETH_TRUE == LpTxBufHdr->blbenableTS)
    {
      LunTxCtrl.stTxCtrl.ulTsr = ETH_DESC_RETAIN_TS;
    }
    else
    {
      /* No action required */
    }
    /* Justify typecast to smaller datatype */
    LunTxCtrl.stTxCtrl.ulTag = LpTxBufHdr->ulbufIdx;

    /* Configures if MAC transmission status of the frame is stored in MAC status FIFO */
    LunTxCtrl.stTxCtrl.ulMsr = ETH_DESC_MAC_FIFO;

    /* build the descriptor */
    LpDataDesc->stHeader.ulDie  = (uint32)LpTxBufHdr->enChannel + 1UL;                                                  /* PRQA S 3383 # JV-01 */
    LpDataDesc->stHeader.ulCtrl = LunTxCtrl.ulWord;
    LpDataDesc->stHeader.ulDs   = LpTxBufHdr->ulTxLength;
    LpDataDesc->ulDptr          = LpTxBufHdr->ulbufAddr;
    LpDataDesc->stHeader.ulDt   = ETH_DESC_FSINGLE_AVB;

    /* Set next descriptor */
    LpDataDesc++;                                                                                                       
    while ((LpDataDesc->stHeader.ulDt == ETH_DESC_LINKFIX) || (LpDataDesc->stHeader.ulDt == ETH_DESC_LINK_AVB))         
    {
      LpDataDesc = (P2VAR(Eth_DataDescType, AUTOMATIC, ETH_APPL_DATA)) LpDataDesc->ulDptr;                              /* PRQA S 0306, 3432 # JV-01, JV-01 */
    }

    Eth_GaaCtrlStat[LulCtrlIdx].stHwStatEtnf.aaLastTxDesc[LpTxBufHdr->enChannel] = (uint32)LpDataDesc;                  /* PRQA S 0306 # JV-01 */

    ETH_ENTER_CRITICAL_SECTION(ETH_RAM_DATA_PROTECTION);

    /* Increase the number of buffer of current Tx queue */
    Eth_GaaCtrlStat[LulCtrlIdx].stHwStatEtnf.aaBufTxCnt[LpTxBufHdr->enChannel]++;                                       /* PRQA S 3383 # JV-01 */

    ETH_EXIT_CRITICAL_SECTION(ETH_RAM_DATA_PROTECTION);

    /* Transmit start request */
    Eth_GaaETNFRegs[LulCtrlIdx]->ulTCCR |= (uint32)(1UL << (uint32)LpTxBufHdr->enChannel);                              
  }
  else
  {
    LucReturnValue = E_NOT_OK;
  }

  return LucReturnValue;
}

/***********************************************************************************************************************
** Function Name         : Eth_Hw_ETNF_RxQueueProcess
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
**                       : LucQidx - Rx queue index
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variable(s)    : Eth_GaaCtrlStat, Eth_GaaRxConfig,
**                         Eth_GaaETNFRegs, Eth_GaaRxFrame
**
** Function(s) invoked   : RxBeProcess, RxNcProcess,
**                       : RxSProcess, RxDescChainUpdate,
**                       : IsRxFrameValid, RxCallEthIf
**
** Registers Used        : UFCD
**
** Reference ID          : ETH_DUD_ACT_406,
** Reference ID          : ETH_DUD_ACT_406_REG001
** Reference ID          : ETH_DUD_ACT_406_GBL001, ETH_DUD_ACT_406_GBL002
** Reference ID          : ETH_DUD_ACT_406_GBL003, ETH_DUD_ACT_406_GBL004
** Reference ID          : ETH_DUD_ACT_406_GBL005, ETH_DUD_ACT_406_GBL006
** Reference ID          : ETH_DUD_ACT_406_GBL007
***********************************************************************************************************************/
FUNC(boolean, ETH_PRIVATE_CODE) Eth_Hw_ETNF_RxQueueProcess(                                                             /* PRQA S 1505 # JV-01 */
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint8, AUTOMATIC) LucQidx)
{
  uint32 LulDescAddr;
  boolean LblRxFrameValid;
  P2CONST(Eth_RxChConfigType, AUTOMATIC, ETH_APPL_DATA) LpChConfig;

  #if (ETH_GET_RX_STATS_API == STD_ON)
  uint32 LulLengthWithFCS;
  #endif

  #if (ETH_ETHSWITCH_MANAGEMENT_SUPPORT == STD_ON)
  Eth_BufIdxType LulBufIdx;
  P2VAR(uint8, AUTOMATIC, ETH_APPL_DATA) LpDataPtr;                                                                     /* PRQA S 3432 # JV-01 */
  boolean LblIsMgmtFrameOnlyPtr;
  uint16 LusLength;
  Std_ReturnType LucReturnValue;
  #endif

  LblRxFrameValid = ETH_TRUE;
  /*Get Rx queue configuration */
  LpChConfig = &Eth_GaaRxConfig[LucQidx];                                                                               

  LulDescAddr = Eth_GaaCtrlStat[LulCtrlIdx].stHwStatEtnf.aaNextRxDesc[LpChConfig->ucChNum];                             


  if (ETH_BECHANNEL == LpChConfig->ucChNum)
  {
    /* best effort channel */
    RxBeProcess(LulCtrlIdx, &Eth_GaaRxFrame[LulCtrlIdx], LulDescAddr);                                                  

    #if (ETH_UPDATE_PHYS_ADDR_FILTER == STD_ON)
    /* check whether received frame is valid or not */
    LblRxFrameValid = IsRxFrameValid(LulCtrlIdx, &Eth_GaaRxFrame[LulCtrlIdx]);                                          
    #endif
  }
  else if (ETH_NCCHANNEL == LpChConfig->ucChNum)
  {
    /* network control channel */
    RxNcProcess(LulCtrlIdx, &Eth_GaaRxFrame[LulCtrlIdx], LulDescAddr);
  }
  else
  {
    /* stream channel */
    RxSProcess(LulCtrlIdx, &Eth_GaaRxFrame[LulCtrlIdx], (uint32)LpChConfig->ucChNum, LulDescAddr);

    #if (ETH_UPDATE_PHYS_ADDR_FILTER == STD_ON)
    /* check whether received frame is valid or not */
    LblRxFrameValid = IsRxFrameValid(LulCtrlIdx, &Eth_GaaRxFrame[LulCtrlIdx]);                                          
    #endif
  }
  /* Decrement ETNFnUFCD.DVr by 1 */
  Eth_GaaETNFRegs[LulCtrlIdx]->ulUFCD[ETH_ETNF_GET_UFCDi(LucQidx)] = ETH_ETNF_SET_UFCDi_DVr(1UL, LucQidx);              /* PRQA S 3469, 3384 # JV-01, JV-01 */

  if (ETH_TRUE == LblRxFrameValid)
  {
    #if (ETH_GET_RX_STATS_API == STD_ON)
    Eth_GaaCtrlStat[LulCtrlIdx].stTxRxStat.ulRxStatsPkts++;                                                             /* PRQA S 3383 # JV-01 */
    LulLengthWithFCS = Eth_GaaRxFrame[LulCtrlIdx].ulFrameLength + ETH_FCS_LENGTH;                                       /* PRQA S 3383 # JV-01 */
    Eth_GaaCtrlStat[LulCtrlIdx].stTxRxStat.ulRxStatsOctets += LulLengthWithFCS;                                         /* PRQA S 3383 # JV-01 */
    if (LulLengthWithFCS <= 64UL)
    {
      /* Since the receive data size that does not include padding data is set in the receive descriptor,
         frames of 64 or less are collected by the statistical counter. */
      Eth_GaaCtrlStat[LulCtrlIdx].stTxRxStat.ulRxStatsPkts64Octets++;                                                   /* PRQA S 3383 # JV-01 */
    }
    else if (LulLengthWithFCS <= 127UL)
    {
      Eth_GaaCtrlStat[LulCtrlIdx].stTxRxStat.ulRxStatsPkts65to127Octets++;                                              /* PRQA S 3383 # JV-01 */
    }
    else if (LulLengthWithFCS <= 255UL)
    {
      Eth_GaaCtrlStat[LulCtrlIdx].stTxRxStat.ulRxStatsPkts128to255Octets++;                                             /* PRQA S 3383 # JV-01 */
    }
    else if (LulLengthWithFCS <= 511UL)
    {
      Eth_GaaCtrlStat[LulCtrlIdx].stTxRxStat.ulRxStatsPkts256to511Octets++;                                             /* PRQA S 3383 # JV-01 */
    }
    else if (LulLengthWithFCS <= 1023UL)
    {
      Eth_GaaCtrlStat[LulCtrlIdx].stTxRxStat.ulRxStatsPkts512to1023Octets++;                                            /* PRQA S 3383 # JV-01 */
    }
    else
    {
      /* When VLAN tag is supported, the maximum data size is 1522. */
      /* The maximum frame size that HW can receive is set to 1522. */
      Eth_GaaCtrlStat[LulCtrlIdx].stTxRxStat.ulRxStatsPkts1024to1518Octets++;                                           /* PRQA S 3383 # JV-01 */
    }
    #endif

    #if (ETH_ETHSWITCH_MANAGEMENT_SUPPORT == STD_ON)
    LulBufIdx = *(P2VAR(Eth_BufIdxType, AUTOMATIC, ETH_APPL_DATA))                                                      /* PRQA S 0306, 3432 # JV-01, JV-01 */
      (Eth_GaaRxFrame[LulCtrlIdx].ulFrameAddr - sizeof(Eth_BufIdxType) - ETH_RX_DPTR_OFFSET);                           /* PRQA S 3383, 3384 # JV-01, JV-01 */

    LpDataPtr = (P2VAR(uint8, AUTOMATIC, ETH_APPL_DATA))Eth_GaaRxFrame[LulCtrlIdx].ulEthTypeAddr;                       /* PRQA S 0306, 3432 # JV-01, JV-01 */
    /* Since the maximum value of buffer size is 1518, casting to uint16 does no problem. */
    LusLength = (uint16)(Eth_GaaRxFrame[LulCtrlIdx].ulFrameLength - ETH_HEADER_SIZE);                                   /* PRQA S 3383 # JV-01 */
    LblIsMgmtFrameOnlyPtr = ETH_FALSE;
    /* Since the maximum value of controller index is 1, casting to uint8 does no problem. */
    LucReturnValue = EthSwt_EthRxProcessFrame((uint8)LulCtrlIdx, LulBufIdx, &LpDataPtr,
      &LusLength, &LblIsMgmtFrameOnlyPtr);
    if (E_OK == LucReturnValue)
    {
      Eth_GaaRxFrame[LulCtrlIdx].ulEthTypeAddr = (uint32)LpDataPtr;                                                     /* PRQA S 0306 # JV-01 */
      Eth_GaaRxFrame[LulCtrlIdx].ulFrameLength = (uint32)(LusLength + ETH_HEADER_SIZE);                                 /* PRQA S 3383 # JV-01 */

      if (ETH_FALSE == LblIsMgmtFrameOnlyPtr)
      {
        /* Call EthIf if the Frame Received is valid */
        RxCallEthIf(LulCtrlIdx, &Eth_GaaRxFrame[LulCtrlIdx]);                                                           
      }
      else
      {
        /* Must not be the Rx processed */
        /* Since the maximum value of controller index is 1, casting to uint8 does no problem. */
        (void)EthSwt_EthRxFinishedIndication((uint8)LulCtrlIdx, LulBufIdx);
      }
    }
    else
    {
      /* Normal operation if E_NOT_OK */
      RxCallEthIf(LulCtrlIdx, &Eth_GaaRxFrame[LulCtrlIdx]);                                                             
    }
    #else
    /* Call EthIf if the Frame Received is valid */
    RxCallEthIf(LulCtrlIdx, &Eth_GaaRxFrame[LulCtrlIdx]);                                                               
    #endif
  }
  else
  {
    /* Frame Invalid - E.g. Multicast to be discarded */
    /* No Call of EthIf */
  }

  /* update descriptor chain */
  (void)RxDescChainUpdate(LulCtrlIdx, LulDescAddr, LpChConfig);

  return LblRxFrameValid;
}

/***********************************************************************************************************************
** Function Name         : RxCallEthIf
**
** Service ID            : NA
**
** Description           : Wrapper for the Callback to the Eth Interface for each frame received
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
** Global Variables Used : Eth_GstBroadcastAddr, Eth_GaaCtrlStat
**
** Function(s) invoked   : EthIf_RxIndication, EthSwt_EthRxFinishedIndication,
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_407,
** Reference ID          : ETH_DUD_ACT_407_GBL002, ETH_DUD_ACT_407_GBL009
***********************************************************************************************************************/
STATIC FUNC (void, ETH_PRIVATE_CODE) RxCallEthIf(
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
  P2CONST(Eth_EtherFrameTypeEtnf, AUTOMATIC, ETH_APPL_DATA) LstEtherFrame;

  LstEtherFrame = (P2CONST(Eth_EtherFrameTypeEtnf, AUTOMATIC, ETH_APPL_DATA)) LpFrame->ulFrameAddr;                     /* PRQA S 0306 # JV-01 */
  ETH_PACK_ADDRESS_FROM_8(LstEtherFrame->ucDstAddr, LstMacAddr);                                                        /* PRQA S 3469 # JV-01 */

  if (0UL == ETH_COMPARE_MAC(LstMacAddr, Eth_GstBroadcastAddr))                                                         /* PRQA S 3469 # JV-01 */
  {
    LblBroadcast = ETH_TRUE;
    #if (ETH_GET_RX_STATS_API == STD_ON)
    Eth_GaaCtrlStat[LulCtrlIdx].stTxRxStat.ulStatsBroadcastPkts++;                                                      /* PRQA S 3383 # JV-01 */
    #endif
  }
  else
  {
    LblBroadcast = ETH_FALSE;
    #if (ETH_GET_RX_STATS_API == STD_ON)
    if (0UL == ETH_CHECK_MULTICAST(LstMacAddr))                                                                         /* PRQA S 3469 # JV-01 */
    {
      /* Unicast frame */
      Eth_GaaCtrlStat[LulCtrlIdx].stTxRxStat.ulRxUnicastFrames++;                                                       /* PRQA S 3383 # JV-01 */
    }
    else
    {
      /* No action required */
    }
    #endif
  }

  LpFrameType = (const Eth_DataType *)LpFrame->ulEthTypeAddr;                                                           /* PRQA S 0306 # JV-01 */
  LddFrameType = (Eth_FrameType)((uint32)LpFrameType[0] << ETH_BYTE_BITS);                                              
  LddFrameType |= (Eth_FrameType)LpFrameType[1];

  /* Since the maximum value of Controller Index is 1, casting to uint8 does no problem. */
  EthIf_RxIndication((uint8)LulCtrlIdx, LddFrameType, LblBroadcast, LstEtherFrame->ucSrcAddr,
    LpFrameType + ETH_ETHERTYPE_SIZE, (uint16)(LpFrame->ulFrameLength - ETH_HEADER_SIZE));                              /* PRQA S 0488, 3383 # JV-01, JV-01 */

  #if (ETH_ETHSWITCH_MANAGEMENT_SUPPORT == STD_ON)
  LulBufIdx = *(P2VAR(Eth_BufIdxType, AUTOMATIC, ETH_APPL_DATA))                                                        /* PRQA S 0306, 3432 # JV-01, JV-01 */
    (LpFrame->ulFrameAddr - sizeof(Eth_BufIdxType) - ETH_RX_DPTR_OFFSET);                                               /* PRQA S 3383, 3384 # JV-01, JV-01 */
  (void)EthSwt_EthRxFinishedIndication((uint8)LulCtrlIdx, LulBufIdx);
  #endif
}

/***********************************************************************************************************************
** Function Name         : Eth_Hw_ETNF_RxMemAlloc
**
** Service ID            : NA
**
** Description           : Allocate buffer memory for Rx queues.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulCtrlIdx - Instance number
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variable(s)    : Eth_GpCtrlConfigPtr, Eth_GaaCtrlStat,
**                         Eth_GaaRxBufferIndex
**
** Function(s) invoked   : Eth_Ram_Alloc,
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_408,
** Reference ID          : ETH_DUD_ACT_408_GBL001, ETH_DUD_ACT_408_GBL002
** Reference ID          : ETH_DUD_ACT_408_GBL003, ETH_DUD_ACT_408_GBL004
***********************************************************************************************************************/
FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_Hw_ETNF_RxMemAlloc(                                                          
  CONST(uint32, AUTOMATIC) LulCtrlIdx)
{
  uint8 LucInc;
  uint8 LucQid;
  uint16 LusBufIdx;
  uint32 LulBufAddress;
  P2CONST(Eth_ETNFConfigType, AUTOMATIC, ETH_APPL_DATA) LpHwUnitConfig;
  Std_ReturnType LucReturnValue;
  uint32 LulRxDptrOffset;
  LucReturnValue = E_OK;
  LulRxDptrOffset = (uint32)sizeof(Eth_BufIdxType) + ETH_RX_DPTR_OFFSET;
  LpHwUnitConfig = (P2CONST(Eth_ETNFConfigType, AUTOMATIC, ETH_APPL_DATA))                                              /* PRQA S 0316 # JV-01 */
    Eth_GpCtrlConfigPtr[LulCtrlIdx].pHwUnitConfig;
  for (LucInc = 0U; LucInc < LpHwUnitConfig->stQueueConfig.ucNumberOfRxQueue; LucInc++)                                 
  {
    LucQid = LpHwUnitConfig->stQueueConfig.pRxQueueConfig[LucInc].ucEthRxQueueId;                                       
    LusBufIdx = 0U;
    do
    {
      LulBufAddress = Eth_Ram_Alloc(LulCtrlIdx,
        (uint32)ETH_RX_BUF_LENGTH + (uint32)sizeof(Eth_BufIdxType) + ETH_RX_DPTR_OFFSET);
      if (0UL == LulBufAddress)
      {
        /* Allocation memory error due to lack of resources */
        LucReturnValue = E_NOT_OK;
        LucInc = LpHwUnitConfig->stQueueConfig.ucNumberOfRxQueue;                                                       /* PRQA S 2469 # JV-01 */
        break;
      }
      else
      {
        /* Add receive buffer index */
        *(P2VAR(Eth_BufIdxType, AUTOMATIC, ETH_APPL_DATA)) LulBufAddress = Eth_GaaRxBufferIndex[LulCtrlIdx];            /* PRQA S 0306, 3432 # JV-01, JV-01 */
        Eth_GaaRxBufferIndex[LulCtrlIdx]++;                                                                             /* PRQA S 3383 # JV-01 */
      }

      switch (LucQid)
      {
      case ETH_BECHANNEL:
        /* Best Effort Queue */
        Eth_GaaCtrlStat[LulCtrlIdx].stHwStatEtnf.aaRxBeQueueBuf[LusBufIdx] = LulBufAddress + LulRxDptrOffset;           /* PRQA S 3383 # JV-01 */
        break;

      case ETH_NCCHANNEL:
        /* Network Control Queue */
        Eth_GaaCtrlStat[LulCtrlIdx].stHwStatEtnf.aaRxNcQueueBuf[LusBufIdx] = LulBufAddress + LulRxDptrOffset;           /* PRQA S 3383 # JV-01 */
        break;

      default :
        /* Stream Queue */
        Eth_GaaCtrlStat[LulCtrlIdx].stHwStatEtnf.aaRxSQueueBuf[LucQid][LusBufIdx] = LulBufAddress + LulRxDptrOffset;    /* PRQA S 3383 # JV-01 */
        break;
      }
      LusBufIdx++;                                                                                                      /* PRQA S 3383 # JV-01 */
    } while (LusBufIdx < LpHwUnitConfig->stQueueConfig.pRxQueueConfig[LucInc].usEthRxQueueBufs);
  }

  return LucReturnValue;
}

/***********************************************************************************************************************
** Function Name         : Eth_Hw_ETNF_DescConfig
**
** Service ID            : NA
**
** Description           : Configure descriptor.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulCtrlIdx - Controlled Id
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variable(s)    : Eth_GaaCtrlStat, Eth_GpCtrlConfigPtr
**
** Function(s) invoked   : SetDescChain
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_409
***********************************************************************************************************************/
FUNC(void, ETH_PRIVATE_CODE) Eth_Hw_ETNF_DescConfig(                                                                    
  CONST(uint32, AUTOMATIC) LulCtrlIdx)
{
  uint8 LucQid; /* Index for the Queue */
  uint8 LucCnt;
  P2VAR(Eth_LinkDescType, AUTOMATIC, ETH_APPL_DATA) LpLinkAddr;                                                         /* PRQA S 3432, 3678 # JV-01, JV-01 */
  P2VAR(Eth_LinkDescType, AUTOMATIC, ETH_APPL_DATA) LpTargetAddr;                                                       /* PRQA S 3432, 3678 # JV-01, JV-01 */
  P2CONST(Eth_ETNFConfigType, AUTOMATIC, ETH_APPL_DATA) LpHwUnitConfig;

  LpHwUnitConfig = (P2CONST(Eth_ETNFConfigType, AUTOMATIC, ETH_APPL_DATA))                                              /* PRQA S 0316 # JV-01 */
    Eth_GpCtrlConfigPtr[LulCtrlIdx].pHwUnitConfig;
  /* init link descriptor */
  LpLinkAddr = (P2VAR(Eth_LinkDescType, AUTOMATIC, ETH_APPL_DATA))                                                      /* PRQA S 0306, 3432 # JV-01, JV-01 */
    (Eth_GaaCtrlStat[LulCtrlIdx].stHwStatEtnf.ulDescTableAddr);                                                         

  /*======TX Queues ========*/
  for (LucCnt = 0U; LucCnt < LpHwUnitConfig->stQueueConfig.ucNumberOfTxQueue; LucCnt++)                                 
  {
    /* Calculate target descriptor table address */
    LpTargetAddr = LpLinkAddr + LpHwUnitConfig->stQueueConfig.pTxQueueConfig[LucCnt].ucEthTxQueueId;                    /* PRQA S 0488 # JV-01 */
    if (0UL != LpTargetAddr->ulDptr)                                                                                    
    {
      /* Get Tx LucQid */
      LucQid = LpHwUnitConfig->stQueueConfig.pTxQueueConfig[LucCnt].ucEthTxQueueId;
      SetDescChain(LulCtrlIdx, (LpTargetAddr->ulDptr), LucQid, ETH_TX);
    }
    else
    {
      /* This Queue is not configured */
    }
  }

  /* Set Rx Queues start position */
  LpLinkAddr = LpLinkAddr + ETH_RXBEQ_OFFSET;                                                                           /* PRQA S 0488 # JV-01 */

  /*======RX Queues ========*/
  for (LucCnt = 0U; LucCnt < LpHwUnitConfig->stQueueConfig.ucNumberOfRxQueue; LucCnt++)
  {
    /* Calculate target descriptor table address */
    LpTargetAddr = LpLinkAddr + LpHwUnitConfig->stQueueConfig.pRxQueueConfig[LucCnt].ucEthRxQueueId;                    /* PRQA S 0488 # JV-01 */
    if (0UL != LpTargetAddr->ulDptr)                                                                                    
    {
      LucQid = LpHwUnitConfig->stQueueConfig.pRxQueueConfig[LucCnt].ucEthRxQueueId;
      SetDescChain(LulCtrlIdx, (LpTargetAddr->ulDptr), LucQid, ETH_RX);
    }
    else
    {
      /* This Queue is not configured */
    }
  }
}

/***********************************************************************************************************************
** Function Name         : SetDescChain
**
** Service ID            : NA
**
** Description           : Configured the Descriptor chain for each Queue (Circular Chain).
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulCtrlIdx - Controlled Id
**                       : LulAddr - Addr of the first descriptor in Queue
**                       : LucQidx - Index of the Queue (0..3 for Tx 0..17 for Rx)
**                       : LenDir - Queue Direction (e.g. TX or RX)
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variable(s)    : Eth_GaaCtrlStat, Eth_GpCtrlConfigPtr
**
** Function(s) invoked   : SetFempty, SetLinkFix, SetExtFempty,
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_410
***********************************************************************************************************************/
STATIC FUNC(void, ETH_PRIVATE_CODE) SetDescChain(
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulAddr,
  CONST(uint8, AUTOMATIC) LucQidx, CONST(Eth_DirectionType, AUTOMATIC) LenDir)
{
  uint32 LulIdx;
  uint32 LulCfgIdx;
  Eth_OptionType LenRxTimestamp;
  P2VAR(Eth_DataDescType, AUTOMATIC, ETH_APPL_DATA) LpCurrentDataDesc;                                                  /* PRQA S 3432 # JV-01 */
  P2VAR(Eth_ExtDataDescType, AUTOMATIC, ETH_APPL_DATA) LpCurrentExtDataDesc;                                            /* PRQA S 3432 # JV-01 */
  P2CONST(Eth_ETNFConfigType, AUTOMATIC, ETH_APPL_DATA) LpHwUnitConfig;

  LpHwUnitConfig = (P2CONST(Eth_ETNFConfigType, AUTOMATIC, ETH_APPL_DATA))                                              /* PRQA S 0316 # JV-01 */
    Eth_GpCtrlConfigPtr[LulCtrlIdx].pHwUnitConfig;
  /* Initialize the counter for any Queue */
  LulIdx = 0UL;

  if (0UL != LulAddr)
  {
    if (ETH_TX == LenDir)
    {
      /* TX */
      /* Search for Tx configuration index */
      for (LulCfgIdx = 0; LulCfgIdx < LpHwUnitConfig->stQueueConfig.ucNumberOfTxQueue; LulCfgIdx++)                     
      {
        if (LucQidx == LpHwUnitConfig->stQueueConfig.pTxQueueConfig[LulCfgIdx].ucEthTxQueueId)                          
        {
          break;
        }
        else
        {
          /* No action required */
        }
      }

      LpCurrentDataDesc = (P2VAR(Eth_DataDescType, AUTOMATIC, ETH_APPL_DATA)) (LulAddr);                                /* PRQA S 0306, 3432 # JV-01, JV-01 */
      do
      {
        if ((uint32)(LpHwUnitConfig->stQueueConfig.pTxQueueConfig[LulCfgIdx].usEthTxQueueBufs -                         /* PRQA S 4391 # JV-01 */
          (uint16)ETH_CYCLIC_DESC_NUM) >= LulIdx)
        {
          /* Set FEmpty */
          SetFempty(LulCtrlIdx, LpCurrentDataDesc, LucQidx, ETH_TX, LulIdx);
        }
        else
        {
          /* Set LinkFix */
          SetLinkFix((uint32)LpCurrentDataDesc, LulAddr);                                                               /* PRQA S 0306 # JV-01 */
        }

        LpCurrentDataDesc++;
        LulIdx++;                                                                                                       /* PRQA S 3383 # JV-01 */
      }
      while (LulIdx <= (uint32)LpHwUnitConfig->stQueueConfig.pTxQueueConfig[LulCfgIdx].usEthTxQueueBufs);
    }
    else
    {
      /* RX */
     /* Search for Rx configuration index */
      for (LulCfgIdx = 0; LulCfgIdx < LpHwUnitConfig->stQueueConfig.ucNumberOfRxQueue; LulCfgIdx++)
      {
        if (LucQidx == LpHwUnitConfig->stQueueConfig.pRxQueueConfig[LulCfgIdx].ucEthRxQueueId)                          
        {
          break;
        }
        else
        {
          /* No action required */
        }
      }

      /* Get Time Stamp status */
      if (ETH_NCCHANNEL == LucQidx)
      {
        LenRxTimestamp = ETH_ENABLE;
      }
      else if (ETH_BECHANNEL == LucQidx)
      {
        LenRxTimestamp = Eth_GaaCtrlStat[LulCtrlIdx].stHwStatEtnf.enRxBeTimestamp;                                      
      }
      else 
      {
        LenRxTimestamp = Eth_GaaCtrlStat[LulCtrlIdx].stHwStatEtnf.enRxSTimestamp;
      }

      if (ETH_ENABLE == LenRxTimestamp)
      {
        /* TS Enable */
        LpCurrentExtDataDesc = (P2VAR(Eth_ExtDataDescType, AUTOMATIC, ETH_APPL_DATA)) (LulAddr);                        /* PRQA S 0306, 3432 # JV-01, JV-01 */

        do
        {
          if ((uint32)LpHwUnitConfig->stQueueConfig.pRxQueueConfig[LulCfgIdx].usEthRxQueueBufs > LulIdx)
          {
            /* Extended Data Descriptor */
            SetExtFempty(LulCtrlIdx, LpCurrentExtDataDesc, LucQidx, ETH_RX, LulIdx);
          }
          else
          {
            SetLinkFix((uint32)LpCurrentExtDataDesc, LulAddr);                                                          /* PRQA S 0306 # JV-01 */
          }
          LulIdx++;                                                                                                     /* PRQA S 3383 # JV-01 */
          LpCurrentExtDataDesc++;
        }
        while (LulIdx <= (uint32)LpHwUnitConfig->stQueueConfig.pRxQueueConfig[LulCfgIdx].usEthRxQueueBufs);
      }
      else
      {
       /* TS Disable */
        LpCurrentDataDesc = (P2VAR(Eth_DataDescType, AUTOMATIC, ETH_APPL_DATA)) (LulAddr);                              /* PRQA S 0306, 3432 # JV-01, JV-01 */
        do
        {
          if ((uint32)LpHwUnitConfig->stQueueConfig.pRxQueueConfig[LulCfgIdx].usEthRxQueueBufs > LulIdx)
          {
            SetFempty(LulCtrlIdx, LpCurrentDataDesc, LucQidx, ETH_RX, LulIdx);
          }
          else
          {
            SetLinkFix((uint32)LpCurrentDataDesc, LulAddr);                                                             /* PRQA S 0306 # JV-01 */
          }
          LpCurrentDataDesc++;

          LulIdx++;                                                                                                     /* PRQA S 3383 # JV-01 */
        }
        while (LulIdx <= (uint32)LpHwUnitConfig->stQueueConfig.pRxQueueConfig[LulCfgIdx].usEthRxQueueBufs);
        /* Better to repeat this code for any Queue */
        /* as in future we may have different No of buffers */
      }
    }
  }
}


/***********************************************************************************************************************
** Function Name         : SetFempty
**
** Service ID            : NA
**
** Description           : Set Fempty in the standard (8Bytes) descriptor
**                         chain for passed Queue and Buffer Index
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulCtrlIdx - Controlled Id
**                       : LpDescr - Pointer to a Data Descriptor
**                       : LucQidx-Index of the Queue (0..3 for Tx 0..17 for Rx)
**                       : LenQdir - Queue Direction (e.g. TX or RX)
**                       : LusBufidx - Index ot the TX or RX buffer
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
** Reference ID          : ETH_DUD_ACT_411
***********************************************************************************************************************/
STATIC FUNC(void, ETH_PRIVATE_CODE) SetFempty(
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONSTP2VAR(Eth_DataDescType, AUTOMATIC, ETH_APPL_DATA) LpDescr,                  /* PRQA S 3432 # JV-01 */
  CONST(uint8, AUTOMATIC) LucQidx, CONST(Eth_DirectionType, AUTOMATIC) LenQdir,
  CONST(Eth_BufIdxType, AUTOMATIC) LulBufIdx)
{
  if (NULL_PTR != LpDescr)
  {
    if (ETH_TX == LenQdir)
    {
      /* TX Queue */
      LpDescr->stHeader.ulDie = 0U;
      LpDescr->stHeader.ulCtrl = 0U;
      /* It will be set only during Transmission at run time */
      LpDescr->stHeader.ulDs = 0U;
      LpDescr->ulDptr = (uint32)0x0U;
      LpDescr->stHeader.ulDt = ETH_DESC_FEMPTY_AVB;
    }
    else if (ETH_BECHANNEL == LucQidx)
    {
      /* RX BE */
      LpDescr->stHeader.ulDie = 0U;
      LpDescr->stHeader.ulCtrl = 0U;
      LpDescr->stHeader.ulDs = ETH_RX_BUF_LENGTH;
      LpDescr->ulDptr = Eth_GaaCtrlStat[LulCtrlIdx].stHwStatEtnf.aaRxBeQueueBuf[LulBufIdx];                             
      LpDescr->stHeader.ulDt = ETH_DESC_FEMPTY_AVB;
    }
    else if (ETH_NCCHANNEL == LucQidx)
    {
      /* RX NC */
      /* This is an Error as RX NC is always Extended Descriptor */
    }
    else
    {
      /* RX S */
      LpDescr->stHeader.ulDie = 0U;
      LpDescr->stHeader.ulCtrl = 0U;
      LpDescr->stHeader.ulDs = ETH_RX_BUF_LENGTH;
      /* Attention Q index!*/
      LpDescr->ulDptr = Eth_GaaCtrlStat[LulCtrlIdx].stHwStatEtnf.aaRxSQueueBuf[LucQidx][LulBufIdx];
      LpDescr->stHeader.ulDt = ETH_DESC_FEMPTY_AVB;
    }
  }
  else
  {
    /* Cannot Set Fempty for NULL Address */
  }
}


/***********************************************************************************************************************
** Function Name       : SetExtFempty
**
** Service ID          : NA
**
** Description         : Set Fempty in the extended (20Bytes) descriptor
**                       chain for passed Queue and Buffer Index
**
** Sync/Async          : Synchronous
**
** Reentrancy          : Non-Reentrant
**
** Input Parameters    : LulCtrlIdx - Controlled Id
**                     : LpDescr - Pointer to a Data Descriptor
**                     : LucQidx - Index of the Queue (0..3 for Tx 0..17 for Rx)
**                     : LenQdir - Queue Direction (e.g. TX or RX)
**                     : LulBufIdx - Index ot the TX or RX buffer
**
** InOut Parameters    : None
**
** Output Parameters   : None
**
** Return parameter    : None
**
** Preconditions       : None
**
** Global Variable(s)  : Eth_GaaCtrlStat
**
** Function(s) invoked : None
**
** Registers Used      : None
**
** Reference ID        : ETH_DUD_ACT_412
***********************************************************************************************************************/
STATIC FUNC(void, ETH_PRIVATE_CODE) SetExtFempty(
  CONST(uint32, AUTOMATIC) LulCtrlIdx,
  CONSTP2VAR(Eth_ExtDataDescType, AUTOMATIC, ETH_APPL_DATA) LpDescr,                                                    /* PRQA S 3432 # JV-01 */
  CONST(uint8, AUTOMATIC) LucQidx, CONST(Eth_DirectionType, AUTOMATIC) LenQdir,
  CONST(Eth_BufIdxType, AUTOMATIC) LulBufIdx)
{
  if (((NULL_PTR != LpDescr) && (ETH_TX != LenQdir)))
  {
    LpDescr->stHeader.ulDie = 0U;
    LpDescr->stHeader.ulCtrl = 0U;
    LpDescr->stHeader.ulDs = ETH_RX_BUF_LENGTH;
    LpDescr->stTimestamp.ulTimestamp0 = 0x0U;
    LpDescr->stTimestamp.ulTimestamp1 = 0x0U;
    LpDescr->stTimestamp.usTimestamp2 = 0x0U;
    if (ETH_BECHANNEL == LucQidx)
    {
      /* RX BE */
      LpDescr->ulDptr = Eth_GaaCtrlStat[LulCtrlIdx].stHwStatEtnf.aaRxBeQueueBuf[LulBufIdx];                             
    }
    else if (ETH_NCCHANNEL == LucQidx)
    {
      /* RX NC */
      LpDescr->ulDptr = Eth_GaaCtrlStat[LulCtrlIdx].stHwStatEtnf.aaRxNcQueueBuf[LulBufIdx];
    }
    else
    {
      /* RX S */
      /* Attention Q index!*/
      LpDescr->ulDptr = Eth_GaaCtrlStat[LulCtrlIdx].stHwStatEtnf.aaRxSQueueBuf[LucQidx][LulBufIdx];
    }
    LpDescr->stHeader.ulDt = ETH_DESC_FEMPTY_AVB;
  }
  else
  {
    /* Cannot Set Fempty for NULL Address */
    /* Error as TX Descr are always Standard and not extended */
  }
}


/***********************************************************************************************************************
** Function Name         : SetLinkFix
**
** Service ID            : NA
**
** Description           : Set LinkFix in the descriptor chain passed as first Argument
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulLinkDesc - Pointer to the Descriptor to be set
**                       : LulAddrToLink - Link Address to be set
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
** Reference ID          : ETH_DUD_ACT_413
***********************************************************************************************************************/
STATIC FUNC(void, ETH_PRIVATE_CODE) SetLinkFix(
  CONST(uint32, AUTOMATIC) LulLinkDesc, CONST(uint32, AUTOMATIC) LulAddrToLink)
{
  P2VAR(Eth_LinkDescType, AUTOMATIC, ETH_APPL_DATA) LpLinkDesc;                                                         /* PRQA S 3432 # JV-01 */
  LpLinkDesc = (P2VAR(Eth_LinkDescType, AUTOMATIC, ETH_APPL_DATA)) LulLinkDesc;                                         /* PRQA S 0306, 3432 # JV-01, JV-01 */

  LpLinkDesc->stHeader.ulDie = 0U;                                                                                      
  LpLinkDesc->stHeader.ulRes = 0U;
  LpLinkDesc->ulDptr         = LulAddrToLink;
  LpLinkDesc->stHeader.ulDt  = ETH_DESC_LINKFIX;
}

/***********************************************************************************************************************
** Function Name         : DescUpdate
**
** Service ID            : NA
**
** Description           : update descriptor chain (without timestamp support).
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulDescPtr - pointer to descriptor to be updated
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : LpDataDesc - last descriptor address
**
** Preconditions         : None
**
** Global Variable(s)    : Eth_GaaCtrlStat
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_414
***********************************************************************************************************************/
STATIC FUNC(uint32, ETH_PRIVATE_CODE) DescUpdate(
  CONST(uint32, AUTOMATIC) LulDescPtr)
{
  P2VAR(Eth_DataDescType, AUTOMATIC, ETH_APPL_DATA) LpDataDesc;                                                         /* PRQA S 3432 # JV-01 */
  LpDataDesc = (P2VAR(Eth_DataDescType, AUTOMATIC, ETH_APPL_DATA)) LulDescPtr;                                          /* PRQA S 0306, 3432 # JV-01, JV-01 */

  LpDataDesc->stHeader.ulDie  = 0U;                                                                                     
  LpDataDesc->stHeader.ulCtrl = 0U;
  LpDataDesc->stHeader.ulDs   = ETH_RX_BUF_LENGTH;
  LpDataDesc->stHeader.ulDt   = ETH_DESC_FEMPTY_AVB;

  return ((uint32)LpDataDesc);                                                                                          /* PRQA S 0306 # JV-01 */
}

/***********************************************************************************************************************
** Function Name         : DescTsUpdate
**
** Service ID            : NA
**
** Description           : update descriptor chain (with timestamp support).
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulDescPtr - pointer to descriptor to be updated
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : LpExtDataDesc - last descriptor address
**
** Preconditions         : None
**
** Global Variable(s)    : Eth_GaaCtrlStat
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_415
***********************************************************************************************************************/
STATIC FUNC(uint32, ETH_PRIVATE_CODE) DescTsUpdate(
  CONST(uint32, AUTOMATIC) LulDescPtr)
{
  P2VAR(Eth_ExtDataDescType, AUTOMATIC, ETH_APPL_DATA) LpExtDataDesc;                                                   /* PRQA S 3432 # JV-01 */
  LpExtDataDesc = (P2VAR(Eth_ExtDataDescType, AUTOMATIC, ETH_APPL_DATA)) LulDescPtr;                                    /* PRQA S 0306, 3432 # JV-01, JV-01 */

  LpExtDataDesc->stHeader.ulDie  = 0U;                                                                                  
  LpExtDataDesc->stHeader.ulCtrl = 0U;
  LpExtDataDesc->stHeader.ulDs   = ETH_RX_BUF_LENGTH;
  LpExtDataDesc->stTimestamp.ulTimestamp0 = 0UL;
  LpExtDataDesc->stTimestamp.ulTimestamp1 = 0UL;
  LpExtDataDesc->stTimestamp.usTimestamp2 = 0U;
  LpExtDataDesc->stHeader.ulDt   = ETH_DESC_FEMPTY_AVB;

  return ((uint32)LpExtDataDesc);                                                                                       /* PRQA S 0306 # JV-01 */
}

/***********************************************************************************************************************
** Function Name         : Eth_Hw_ETNF_DMACInit
**
** Service ID            : NA
**
** Description           : Initialize DMAC
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulCtrlIdx - Index of a controller
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variable(s)    : Eth_GaaAvbConfig, Eth_GaaETNFRegs
**
** Function(s) invoked   : TxRxConfig, TxRxIntConfig, SetCbsParameter,
**                         RxQueueSet, SetRxFilter
**
** Registers Used        : CCC, EIC, GIC, RPC
**
** Reference ID          : ETH_DUD_ACT_416,
** Reference ID          : ETH_DUD_ACT_416_GBL001, ETH_DUD_ACT_416_GBL002
** Reference ID          : ETH_DUD_ACT_416_GBL003, ETH_DUD_ACT_416_GBL004
***********************************************************************************************************************/
FUNC(void, ETH_PRIVATE_CODE) Eth_Hw_ETNF_DMACInit(                                                                      
  CONST(uint32, AUTOMATIC) LulCtrlIdx)
{
  /* configure CCC register */
  if (ETH_ENABLE == Eth_GpEthConfigPtr[LulCtrlIdx].enInternalLoopBackMode)                                              /* PRQA S 3416 # JV-01 */
  {
    Eth_GaaETNFRegs[LulCtrlIdx]->ulCCC |= ETH_ETNF_CCC_LBME;                                                            
  }
  else
  {
    /* No action required */
  }

  /* configure Error interrupt mask - EIC register */
  Eth_GaaETNFRegs[LulCtrlIdx]->ulEIC = ETH_ETNF_EIC_ERROR;
  /* configure reception part - RCR register */
  /* configure transmission part - TGC register */
  TxRxConfig(LulCtrlIdx, &(Eth_GaaAvbConfig[LulCtrlIdx].stTxConfig), &(Eth_GaaAvbConfig[LulCtrlIdx].stRxConfig));       

  TxRxIntConfig(LulCtrlIdx);

  #if (ETH_QOS_SUPPORT == STD_ON)
  /* Set CBS Counter parameters (CIV and CDV)  */
  SetCbsParameter(LulCtrlIdx);
  #endif

  /* set GIC interrupt */
  Eth_GaaETNFRegs[LulCtrlIdx]->ulGIC = 0UL;

  /* Set RQCi register */
  RxQueueSet(LulCtrlIdx);

  /* Set padding to zero - Padding Not used */
  Eth_GaaETNFRegs[LulCtrlIdx]->ulRPC = 0UL;

  /* Set Common RX Filter if enabled */
  #if (ETH_STREAM_FILTERING == STD_ON)
  SetRxFilter(LulCtrlIdx);
  #endif
}

/***********************************************************************************************************************
** Function Name         : Eth_Hw_ETNF_OpModeChange
**
** Service ID            : NA
**
** Description           : To change Operating Mode.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulCtrlIdx - Instance number
**                       : LenMode - Mode to change
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : Ethernet Error
**
** Preconditions         : None
**
** Global Variable(s)    : Eth_GaaCtrlStat, Eth_GaaETNFRegs
**
** Function(s) invoked   : GetCounterValue, Eth_ETNF_GetElapsedTimeValue
**
** Registers Used        : CCC, CSR
**
** Reference ID          : ETH_DUD_ACT_417,
** Reference ID          : ETH_DUD_ACT_417_GBL001, ETH_DUD_ACT_417_REG001
***********************************************************************************************************************/
FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_Hw_ETNF_OpModeChange(
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(Eth_OpStatusType, AUTOMATIC) LenMode)
{
  Std_ReturnType LucReturnValue;
  uint32 LulRegVal;
  TickType LulTimeOutCountInit;
  TickType LulTimeoutCountElap;

  LulTimeOutCountInit = 0UL;
  LulTimeoutCountElap = 0UL;

  if (Eth_GaaCtrlStat[LulCtrlIdx].stHwStatEtnf.enDevStatus != LenMode)                                                  
  {
    LulRegVal = Eth_GaaETNFRegs[LulCtrlIdx]->ulCCC & ~ETH_ETNF_CCC_OPC_MASK;                                            
    Eth_GaaETNFRegs[LulCtrlIdx]->ulCCC = LulRegVal | (uint32)LenMode;

    (void)GetCounterValue((CounterType)ETH_OS_COUNTER_ID, &LulTimeOutCountInit);
    do
    {
      LulTimeoutCountElap = LulTimeoutCountElap + Eth_ETNF_GetElapsedTimeValue(&LulTimeOutCountInit);                   /* PRQA S 3383 # JV-01 */
      LulRegVal = Eth_GaaETNFRegs[LulCtrlIdx]->ulCSR & ETH_ETNF_CSR_OPS;
    } while ((LulRegVal != (1UL << (uint32)LenMode)) && (LulTimeoutCountElap <= ETH_TIMEOUT_COUNT));

    if ((1UL << (uint32)LenMode) == LulRegVal)
    {
      /* No Time-out - mode changed  */
      Eth_GaaCtrlStat[LulCtrlIdx].stHwStatEtnf.enDevStatus = LenMode;                                                   
      LucReturnValue = E_OK;
    }
    else
    {
      /* Return Error - as mode not changed */
      LucReturnValue = E_NOT_OK;
    }
  }
  else
  {
    /* Controller is already in the requested state */
    LucReturnValue = E_OK;
  }

  return LucReturnValue;
}

/***********************************************************************************************************************
** Function Name         : RxQueueSet
**
** Service ID            : NA
**
** Description           : Set Receive Queue
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulCtrlIdx - Instance number
**                       : LpQconfig  - Queue config structure pointer
**                       : LulQIndex - Queue Index
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variable(s)    : Eth_GpCtrlConfigPtr, Eth_GaaETNFRegs,
**                         Eth_GaaQConfig
**
** Function(s) invoked   : None
**
** Registers Used        : RQCi
**
** Reference ID          : ETH_DUD_ACT_418, ETH_DUD_ACT_418_GBL001
***********************************************************************************************************************/
STATIC FUNC(void, ETH_PRIVATE_CODE) RxQueueSet(
  CONST(uint32, AUTOMATIC) LulCtrlIdx)
{
  uint32 LulIdx;
  uint32 LulQIndex;
  uint32 LulConfig;
  P2CONST(Eth_ETNFConfigType, AUTOMATIC, ETH_APPL_DATA) LpHwUnitConfig;

  LpHwUnitConfig = (P2CONST(Eth_ETNFConfigType, AUTOMATIC, ETH_APPL_DATA))                                              /* PRQA S 0316 # JV-01 */
    Eth_GpCtrlConfigPtr[LulCtrlIdx].pHwUnitConfig;

  for (LulIdx = 0UL; LulIdx < (uint32)LpHwUnitConfig->stQueueConfig.ucNumberOfRxQueue; LulIdx++)                        
  {
    LulQIndex = (uint32) (LpHwUnitConfig->stQueueConfig.pRxQueueConfig[LulIdx].ucEthRxQueueId);                         

    LulConfig = (uint32)(ETH_ETNF_SET_RQCi_RSMr(Eth_GaaQConfig[LulIdx].enRsm, LulQIndex) |                              /* PRQA S 3384, 3469 # JV-01, JV-01 */
      ETH_ETNF_SET_RQCi_UFCCr(Eth_GaaQConfig[LulIdx].enUfcc, LulQIndex) |                                               /* PRQA S 3384, 3383, 3469 # JV-01, JV-01, JV-01 */
      ETH_ETNF_SET_RQCi_PIAr(Eth_GaaQConfig[LulIdx].enPia, LulQIndex));                                                 /* PRQA S 3383, 3469, 3384 # JV-01, JV-01, JV-01 */
    Eth_GaaETNFRegs[LulCtrlIdx]->ulRQC[ETH_ETNF_GET_RQCi(LulQIndex)] = LulConfig;                                       /* PRQA S 3469 # JV-01 */
  }
}

/***********************************************************************************************************************
** Function Name         : Eth_Hw_ETNF_UFCounterGet
**
** Service ID            : NA
**
** Description           : Get Unread Frame Counter
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulCtrlIdx - Instance number
**                       : LulQIndex - Queue Index
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : LulUFCount - Number of unread frames
**
** Preconditions         : None
**
** Global Variable(s)    : Eth_GaaETNFRegs
**
** Function(s) invoked   : None
**
** Registers Used        : UFCVi
**
** Reference ID          : ETH_DUD_ACT_419
***********************************************************************************************************************/
FUNC(uint32, ETH_PRIVATE_CODE) Eth_Hw_ETNF_UFCounterGet(                                                                /* PRQA S 1505 # JV-01 */
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulQIndex)
{
  uint32  LulUfcv;
  uint32  LulUFCount;
  LulUfcv = Eth_GaaETNFRegs[LulCtrlIdx]->ulUFCV[ETH_ETNF_GET_UFCVi(LulQIndex)];                                         /* PRQA S 3469 # JV-01 */
  LulUFCount = ETH_ETNF_GET_UFCVi_CVr(LulUfcv, LulQIndex);                                                              /* PRQA S 3384 # JV-01 */
  return (LulUFCount);
}

/***********************************************************************************************************************
** Function Name         : Eth_Hw_ETNF_RxDescChainConfig
**
** Service ID            : NA
**
** Description           : configure Rx descriptor chain
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulCtrlIdx - Instance number
**                       : LpChConfig - Channel Config Pointer Index
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variable(s)    : Eth_GaaCtrlStat, Eth_GaaETNFRegs
**
** Function(s) invoked   : RxDescChainUpdate,
**
** Registers Used        : DLR
**
** Reference ID          : ETH_DUD_ACT_420,
** Reference ID          : ETH_DUD_ACT_420_GBL002, ETH_DUD_ACT_420_GBL003
***********************************************************************************************************************/
FUNC(void, ETH_PRIVATE_CODE) Eth_Hw_ETNF_RxDescChainConfig(                                                             
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONSTP2CONST(Eth_RxChConfigType, AUTOMATIC, ETH_APPL_DATA) LpChConfig)
{
  P2VAR(Eth_LinkDescType, AUTOMATIC, ETH_APPL_DATA) LpLinkAddr;                                                         /* PRQA S 3432, 3678 # JV-01, JV-01 */
  P2VAR(Eth_DataDescType, AUTOMATIC, ETH_APPL_DATA) LpDataDesc;                                                         /* PRQA S 3432, 3678 # JV-01, JV-01 */
  P2VAR(Eth_ExtDataDescType, AUTOMATIC, ETH_APPL_DATA) LpExtDataDesc;                                                   /* PRQA S 3432, 3678 # JV-01, JV-01 */
  LpLinkAddr = (P2VAR(Eth_LinkDescType, AUTOMATIC, ETH_APPL_DATA))                                                      /* PRQA S 0306, 3432 # JV-01, JV-01 */
    (Eth_GaaCtrlStat[LulCtrlIdx].stHwStatEtnf.ulDescTableAddr);                                                         

  LpLinkAddr += (ETH_RXBEQ_OFFSET + LpChConfig->ucChNum);                                                               /* PRQA S 0488 # JV-01 */
  Eth_GaaCtrlStat[LulCtrlIdx].stHwStatEtnf.aaNextRxDesc[LpChConfig->ucChNum] = (uint32)(LpLinkAddr->ulDptr);            

  if (ETH_BECHANNEL == LpChConfig->ucChNum)
  {
    /* best effort channel */
    if (ETH_DISABLE == Eth_GaaCtrlStat[LulCtrlIdx].stHwStatEtnf.enRxBeTimestamp)
    {
      LpDataDesc = (P2VAR(Eth_DataDescType, AUTOMATIC, ETH_APPL_DATA))                                                  /* PRQA S 0306, 3432 # JV-01, JV-01 */
        Eth_GaaCtrlStat[LulCtrlIdx].stHwStatEtnf.aaNextRxDesc[LpChConfig->ucChNum];
      do
      {
        LpDataDesc = (P2VAR(Eth_DataDescType, AUTOMATIC, ETH_APPL_DATA))                                                /* PRQA S 0306, 3432 # JV-01, JV-01 */
          RxDescChainUpdate(LulCtrlIdx, (uint32)LpDataDesc, LpChConfig);                                                /* PRQA S 0306 # JV-01 */
        LpDataDesc++;                                                                                                   
      } while (LpDataDesc->stHeader.ulDt != ETH_DESC_LINKFIX);                                                          
    }
    else
    {
      LpExtDataDesc = (P2VAR(Eth_ExtDataDescType, AUTOMATIC, ETH_APPL_DATA))                                            /* PRQA S 0306, 3432 # JV-01, JV-01 */
        Eth_GaaCtrlStat[LulCtrlIdx].stHwStatEtnf.aaNextRxDesc[LpChConfig->ucChNum];
      do
      {
        LpExtDataDesc = (P2VAR(Eth_ExtDataDescType, AUTOMATIC, ETH_APPL_DATA))                                          /* PRQA S 0306, 3432 # JV-01, JV-01 */
          RxDescChainUpdate(LulCtrlIdx, (uint32)LpExtDataDesc, LpChConfig);                                             /* PRQA S 0306 # JV-01 */
        LpExtDataDesc++;                                                                                                
      } while (LpExtDataDesc->stHeader.ulDt != ETH_DESC_LINKFIX);                                                       
    }
  }
  else if (ETH_NCCHANNEL == LpChConfig->ucChNum)
  {
    /* network control channel */
    LpExtDataDesc = (P2VAR(Eth_ExtDataDescType, AUTOMATIC, ETH_APPL_DATA))                                              /* PRQA S 0306, 3432 # JV-01, JV-01 */
      Eth_GaaCtrlStat[LulCtrlIdx].stHwStatEtnf.aaNextRxDesc[LpChConfig->ucChNum];
    do
    {
      LpExtDataDesc = (P2VAR(Eth_ExtDataDescType, AUTOMATIC, ETH_APPL_DATA))                                            /* PRQA S 0306, 3432 # JV-01, JV-01 */
        RxDescChainUpdate(LulCtrlIdx, (uint32)LpExtDataDesc, LpChConfig);                                               /* PRQA S 0306 # JV-01 */
      LpExtDataDesc++;                                                                                                  
    } while (LpExtDataDesc->stHeader.ulDt != ETH_DESC_LINKFIX);                                                         

  }
  else
  {
    /* stream channel */
    if (ETH_DISABLE == Eth_GaaCtrlStat[LulCtrlIdx].stHwStatEtnf.enRxSTimestamp)
    {
      LpDataDesc = (P2VAR(Eth_DataDescType, AUTOMATIC, ETH_APPL_DATA))                                                  /* PRQA S 0306, 3432 # JV-01, JV-01 */
        Eth_GaaCtrlStat[LulCtrlIdx].stHwStatEtnf.aaNextRxDesc[LpChConfig->ucChNum];
      do
      {
        LpDataDesc = (P2VAR(Eth_DataDescType, AUTOMATIC, ETH_APPL_DATA))                                                /* PRQA S 0306, 3432 # JV-01, JV-01 */
          RxDescChainUpdate(LulCtrlIdx, (uint32)LpDataDesc, LpChConfig);                                                /* PRQA S 0306 # JV-01 */

        LpDataDesc++;                                                                                                   
      } while (LpDataDesc->stHeader.ulDt != ETH_DESC_LINKFIX);                                                          
    }
    else
    {
      LpExtDataDesc = (P2VAR(Eth_ExtDataDescType, AUTOMATIC, ETH_APPL_DATA))                                            /* PRQA S 0306, 3432 # JV-01, JV-01 */
        Eth_GaaCtrlStat[LulCtrlIdx].stHwStatEtnf.aaNextRxDesc[LpChConfig->ucChNum];
      do
      {
        LpExtDataDesc = (P2VAR(Eth_ExtDataDescType, AUTOMATIC, ETH_APPL_DATA))                                          /* PRQA S 0306, 3432 # JV-01, JV-01 */
          RxDescChainUpdate(LulCtrlIdx, (uint32)LpExtDataDesc, LpChConfig);                                             /* PRQA S 0306 # JV-01 */

        LpExtDataDesc++;                                                                                                
      } while (LpExtDataDesc->stHeader.ulDt != ETH_DESC_LINKFIX);                                                       
    }
  }
  /* reload desc. base address */
  if (ETH_OPERATION == Eth_GaaCtrlStat[LulCtrlIdx].stHwStatEtnf.enDevStatus)                                            
  {
    Eth_GaaETNFRegs[LulCtrlIdx]->ulDLR = (1UL << (LpChConfig->ucChNum + ETH_RXBEQ_OFFSET));                             
  }
  else
  {
    /* No action required */
  }
}

/***********************************************************************************************************************
** Function Name         : RxDescChainUpdate
**
** Service ID            : NA
**
** Description           : Update receive descriptor chain
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulCtrlIdx - Instance number
**                       : LulDescPtr - Descriptor pointer
**                       : LpChConfig - Channel Config Pointer
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : LulLastDesc - Last processed descriptor address
**
** Preconditions         : None
**
** Global Variable(s)    : Eth_GaaCtrlStat
**
** Function(s) invoked   : DescUpdate, DescTsUpdate
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_421
***********************************************************************************************************************/
STATIC FUNC(uint32, ETH_PRIVATE_CODE) RxDescChainUpdate(
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulDescPtr,
  CONSTP2CONST(Eth_RxChConfigType, AUTOMATIC, ETH_APPL_DATA) LpChConfig)
{
  uint32 LulLastDesc;

  switch (LpChConfig->enChType)                                                                                         
  {
  case ETH_RX_BE:
    if (ETH_DISABLE == Eth_GaaCtrlStat[LulCtrlIdx].stHwStatEtnf.enRxBeTimestamp)                                        
    {
      LulLastDesc = DescUpdate(LulDescPtr);
    }
    else
    {
      LulLastDesc = DescTsUpdate(LulDescPtr);
    }
    break;
  case ETH_RX_S:
    if (ETH_DISABLE == Eth_GaaCtrlStat[LulCtrlIdx].stHwStatEtnf.enRxSTimestamp)
    {
      LulLastDesc = DescUpdate(LulDescPtr);
    }
    else
    {
      LulLastDesc = DescTsUpdate(LulDescPtr);
    }
    break;
  /* ETH_RX_NC */
  default:
    LulLastDesc = DescTsUpdate(LulDescPtr);
    break;
  }
  return (LulLastDesc);
}

/***********************************************************************************************************************
** Function Name         : TxRxConfig
**
** Service ID            : NA
**
** Description           : Tx parameters Config
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulCtrlIdx - Instance number
**                       : LpTxConfig - Tx Config Pointer
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variable(s)    : Eth_GaaCtrlStat, Eth_GaaETNFRegs
**
** Function(s) invoked   : None
**
** Registers Used        : RCR, TGC
**
** Reference ID          : ETH_DUD_ACT_422,
** Reference ID          : ETH_DUD_ACT_422_GBL001, ETH_DUD_ACT_422_GBL002
** Reference ID          : ETH_DUD_ACT_422_GBL003
***********************************************************************************************************************/
STATIC FUNC(void, ETH_PRIVATE_CODE) TxRxConfig(
  CONST(uint32, AUTOMATIC) LulCtrlIdx,
  CONSTP2CONST(Eth_TxConfigType, AUTOMATIC, ETH_APPL_DATA) LpTxConfig,
  CONSTP2CONST(Eth_RxConfigTypeEtnf, AUTOMATIC, ETH_APPL_DATA) LpRxConfig)
{
  uint32 LulRegVal;
  LulRegVal = (uint32)(((uint32)LpRxConfig->enEncf << ETH_ETNF_RCR_ENCF_SHIFT) |                                        
              ((uint32)LpRxConfig->enEsf << ETH_ETNF_RCR_ESF_SHIFT) |
              ((uint32)LpRxConfig->enEts0 << ETH_ETNF_RCR_ETS0_SHIFT) |
              ((uint32)LpRxConfig->enEts2 << ETH_ETNF_RCR_ETS2_SHIFT) |
              ((uint32)LpRxConfig->ulRfcl << ETH_ETNF_RCR_RFCL_SHIFT));

  Eth_GaaETNFRegs[LulCtrlIdx]->ulRCR = LulRegVal;                                                                       

  Eth_GaaCtrlStat[LulCtrlIdx].stHwStatEtnf.enRxBeTimestamp = LpRxConfig->enEts0;                                        
  Eth_GaaCtrlStat[LulCtrlIdx].stHwStatEtnf.enRxSTimestamp = LpRxConfig->enEts2;                                         
  LulRegVal = (uint32)(((uint32)LpTxConfig->enTsm0) |                                                                   
              ((uint32)LpTxConfig->enTsm1 << ETH_ETNF_TGC_TSM1_SHIFT) |
              ((uint32)LpTxConfig->enTsm2 << ETH_ETNF_TGC_TSM2_SHIFT) |
              ((uint32)LpTxConfig->enTsm3 << ETH_ETNF_TGC_TSM3_SHIFT) |
              ((uint32)LpTxConfig->enEcbs << ETH_ETNF_TGC_TQP0_SHIFT) |
              ((uint32)LpTxConfig->enTqp << ETH_ETNF_TGC_TQP1_SHIFT) |
               ETH_ETNF_TGC_TBDn_VALUE);

  Eth_GaaETNFRegs[LulCtrlIdx]->ulTGC = LulRegVal;
}

/***********************************************************************************************************************
** Function Name         : TxRxIntConfig
**
** Service ID            : NA
**
** Description           : Tx/Rx Interrupt config
**
** Sync/Async            : NA
**
** Reentrancy            : NA
**
** Input Parameters      : LulCtrlIdx - Instance number
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variable(s)    : Eth_GpCtrlConfigPtr, Eth_GaaETNFRegs
**                         Eth_GpEthConfigPtr
**
** Function(s) invoked   : None
**
** Registers Used        : RIC0, RIC2, RIC3, DIC, TIC
**
** Reference ID          : ETH_DUD_ACT_423,
** Reference ID          : ETH_DUD_ACT_423_GBL001, ETH_DUD_ACT_423_GBL002
** Reference ID          : ETH_DUD_ACT_423_GBL003
***********************************************************************************************************************/
STATIC FUNC(void, ETH_PRIVATE_CODE) TxRxIntConfig(
  CONST(uint32, AUTOMATIC) LulCtrlIdx)                                                                                  /* PRQA S 3206 # JV-01 */
{
  #if (ETH_CTRL_ENABLE_TX_INTERRUPT == STD_ON || ETH_CTRL_ENABLE_RX_INTERRUPT == STD_ON)
  P2CONST(Eth_ETNFConfigType, AUTOMATIC, ETH_APPL_DATA) LpHwUnitConfig;
  uint8 LucIdx;
  #endif
  #if (ETH_CTRL_ENABLE_TX_INTERRUPT == STD_ON)
  uint8 LucQIdx;
  #endif
  #if (ETH_CTRL_ENABLE_RX_INTERRUPT == STD_ON)
  uint8 LucBitNo;
  #endif

  #if (ETH_CTRL_ENABLE_TX_INTERRUPT == STD_ON || ETH_CTRL_ENABLE_RX_INTERRUPT == STD_ON)
  LpHwUnitConfig = (P2CONST(Eth_ETNFConfigType, AUTOMATIC, ETH_APPL_DATA))                                              /* PRQA S 0316 # JV-01 */
    Eth_GpCtrlConfigPtr[LulCtrlIdx].pHwUnitConfig;
  #endif

  #if (ETH_CTRL_ENABLE_RX_INTERRUPT == STD_ON)
  if (ETH_ENABLE == Eth_GpEthConfigPtr[LulCtrlIdx].enRxInterruptMode)                                                   /* PRQA S 3416 # JV-01 */
  {
    /* set RIC0 interrupt */
    for (LucIdx = 0U; LucIdx < LpHwUnitConfig->stQueueConfig.ucNumberOfRxQueue; LucIdx++)                               
    {
      LucBitNo = LpHwUnitConfig->stQueueConfig.pRxQueueConfig[LucIdx].ucEthRxQueueId;                                   
      Eth_GaaETNFRegs[LulCtrlIdx]->ulRIC0 |= (1UL << LucBitNo);                                                         
    }
  }
  else
  {
    /* No action required */
  }
  #endif

  #if (ETH_CTRL_ENABLE_TX_INTERRUPT == STD_ON)
  if (ETH_ENABLE == Eth_GpEthConfigPtr[LulCtrlIdx].enTxInterruptMode)                                                   /* PRQA S 3416 # JV-01 */
  {
    /* set descriptor interrupt */
    for (LucIdx = 0U; LucIdx < LpHwUnitConfig->stQueueConfig.ucNumberOfTxQueue; LucIdx++)
    {
      /* Get Tx queue id */
      LucQIdx = LpHwUnitConfig->stQueueConfig.pTxQueueConfig[LucIdx].ucEthTxQueueId;                                    
      /* Enable descriptor interrupt
      Queue n (n = 0..3): corresponding to descriptor interrupt (n + 1) */
      Eth_GaaETNFRegs[LulCtrlIdx]->ulDIC |= (1UL << (LucQIdx + 1U));                                                    /* PRQA S 3383 # JV-01 */
    }
  }
  else
  {
    /* No action required */
  }
  #endif

  #if (ETH_GLOBAL_TIME_SUPPORT == STD_ON)
  Eth_GaaETNFRegs[LulCtrlIdx]->ulTIC = ETH_TIC_TFUE;
  #endif
}

/***********************************************************************************************************************
** Function Name         : Eth_Hw_ETNF_SYS_AllocDescBuffer
**
** Service ID            : NA
**
** Description           : Allocate memory for DBA (Descriptor Base Address)
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulCtrlIdx - Instance number
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : Std_ReturnType
**
** Preconditions         : None
**
** Global Variable(s)    : None
**
** Function(s) invoked   : Eth_Ram_Alloc, AllocMemForDesc, FillDescMemory
**                         IsQueueConfigured
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_424
***********************************************************************************************************************/
FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_Hw_ETNF_SYS_AllocDescBuffer(                                                 
  CONST(uint32, AUTOMATIC) LulCtrlIdx)
{
  Eth_DirectionType LenQdirection; /* Direction Tx or Rx of the Queue */
  uint8 LucQid;                   /* Index of the Queue  */
  uint8 LucIdx;
  uint32 LulDescAddr;
  boolean LblQueueConfig;
  Std_ReturnType LucReturnValue;

  P2VAR(Eth_LinkDescType, AUTOMATIC, ETH_APPL_DATA) LpLinkDesc;                                                         /* PRQA S 3432 # JV-01 */

  LucReturnValue = E_OK;

  LpLinkDesc  = (P2VAR(Eth_LinkDescType, AUTOMATIC, ETH_APPL_DATA))                                                     /* PRQA S 0306, 3432 # JV-01, JV-01 */
    Eth_Ram_Alloc(LulCtrlIdx, (ETH_TXQ_NUM + ETH_RXQ_NUM) * (uint32)ETH_NORMAL_DESC_SIZE);
  if (NULL_PTR != LpLinkDesc)
  {
    for (LucIdx = 0U; LucIdx < (ETH_TXQ_NUM + ETH_RXQ_NUM); LucIdx++)
    {
      /* !!!!!!!Attention index need to be reduced by 4 for a RX Queue !!!!! */
      if (ETH_TXQ_NUM > LucIdx)
      {
        /* TX Queue */
        LenQdirection = ETH_TX;
        LucQid = LucIdx;
      }
      else
      {
        /* Rx Queue */
        LenQdirection = ETH_RX;
        LucQid = (LucIdx - (uint8)ETH_TXQ_NUM);
      }

      LblQueueConfig = IsQueueConfigured(LulCtrlIdx, LucQid, LenQdirection);

      if (ETH_TRUE == LblQueueConfig)
      {
        /* Queue has been configured */
        /* Alloc Desc Chain Memory */

        LulDescAddr = AllocMemForDesc(LulCtrlIdx, LucQid, LenQdirection);
        if (0UL != LulDescAddr)
        {
          FillDescMemory(LpLinkDesc, LulDescAddr);
        }
        else
        {
          /* Memory allocation error due to lack of resources */
          LucReturnValue = E_NOT_OK;
          break;
        }
      }
      else
      {
        /* Queue not configured */
        /* Set Null Dptr field in Link Descriptor */
        FillDescMemory(LpLinkDesc, (uint32)0x0U);
      }
      /* Go to the next DBA element */
      LpLinkDesc++;
    } /* end loop for all Tx and Rx Queues  */
  }
  else
  {
    /* Memory allocation error due to lack of resources */
    LucReturnValue = E_NOT_OK;
  }

  return LucReturnValue;
}

/***********************************************************************************************************************
** Function Name         : AllocMemForDesc
**
** Service ID            : NA
**
** Description           : Alloc Memory for Descriptor Chain
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulCtrlIdx - Controller Index
**                       : LucQidx - Queue Index
**                       : LenQdir - Queue Direction
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : LulDescAddr
**
** Preconditions         : None
**
** Global Variable(s)    : Eth_GpCtrlConfigPtr, Eth_GaaCtrlStat
**
** Function(s) invoked   : Eth_Ram_Alloc,
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_425,
** Reference ID          : ETH_DUD_ACT_425_GBL001
***********************************************************************************************************************/
STATIC FUNC(uint32, ETH_PRIVATE_CODE) AllocMemForDesc(
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint8, AUTOMATIC) LucQidx, CONST(Eth_DirectionType, AUTOMATIC) LenQdir)
{
  uint32 LulDescAddr;
  uint32 LulCfgIdx;
  P2CONST(Eth_ETNFConfigType, AUTOMATIC, ETH_APPL_DATA) LpHwUnitConfig;

  LpHwUnitConfig = (P2CONST(Eth_ETNFConfigType, AUTOMATIC, ETH_APPL_DATA))                                              /* PRQA S 0316 # JV-01 */
    Eth_GpCtrlConfigPtr[LulCtrlIdx].pHwUnitConfig;
  if (ETH_TX == LenQdir)
  {
    /* Search for Tx configuration index */
    for (LulCfgIdx = 0; LulCfgIdx < LpHwUnitConfig->stQueueConfig.ucNumberOfTxQueue; LulCfgIdx++)                       
    {
      if (LucQidx == LpHwUnitConfig->stQueueConfig.pTxQueueConfig[LulCfgIdx].ucEthTxQueueId)                            
      {
        break;
      }
      else
      {
        /* No action required */
      }
    }

    /* TX */
    LulDescAddr = Eth_Ram_Alloc(LulCtrlIdx,
      (uint32)((LpHwUnitConfig->stQueueConfig.pTxQueueConfig[LulCfgIdx].usEthTxQueueBufs + ETH_CYCLIC_DESC_NUM)         /* PRQA S 4391, 3383 # JV-01, JV-01 */
      * ETH_NORMAL_DESC_SIZE));                                                                                         /* PRQA S 3384 # JV-01 */
    /* Store the current Tx descriptor address */
    Eth_GaaCtrlStat[LulCtrlIdx].stHwStatEtnf.aaLastTxDesc[LucQidx] = LulDescAddr;                                       
    Eth_GaaCtrlStat[LulCtrlIdx].stHwStatEtnf.aaHeadTxDesc[LucQidx] = LulDescAddr;                                       
  }
  else
  {
    /* Search for Rx configuration index */
    for (LulCfgIdx = 0; LulCfgIdx < LpHwUnitConfig->stQueueConfig.ucNumberOfRxQueue; LulCfgIdx++)
    {
      if (LucQidx == LpHwUnitConfig->stQueueConfig.pRxQueueConfig[LulCfgIdx].ucEthRxQueueId)                            
      {
        break;
      }
      else
      {
        /* No action required */
      }
    }

    /* Rx */
    switch (LucQidx)
    {
    case ETH_BECHANNEL:
      /* RX BE */
      if (ETH_ENABLE == LpHwUnitConfig->stRxConfig.enEts0)
      {
        /* TS Enabled for RX BE */
        LulDescAddr = Eth_Ram_Alloc(LulCtrlIdx,
          (uint32)((LpHwUnitConfig->stQueueConfig.pRxQueueConfig[LulCfgIdx].usEthRxQueueBufs + ETH_CYCLIC_DESC_NUM)     /* PRQA S 4391, 3383 # JV-01, JV-01 */
          * ETH_SPECIAL_DESC_SIZE));                                                                                    /* PRQA S 3384 # JV-01 */
      }
      else
      {
        /* TS Disabled for RX BE */
        LulDescAddr = Eth_Ram_Alloc(LulCtrlIdx,
          (uint32)((LpHwUnitConfig->stQueueConfig.pRxQueueConfig[LulCfgIdx].usEthRxQueueBufs + ETH_CYCLIC_DESC_NUM)     /* PRQA S 4391, 3383 # JV-01, JV-01 */
          * ETH_NORMAL_DESC_SIZE));                                                                                     /* PRQA S 3384 # JV-01 */
      }

      break;

    case ETH_NCCHANNEL:
      /* RX NC */
      LulDescAddr = Eth_Ram_Alloc(LulCtrlIdx,
        (uint32)((LpHwUnitConfig->stQueueConfig.pRxQueueConfig[LulCfgIdx].usEthRxQueueBufs + ETH_CYCLIC_DESC_NUM)       /* PRQA S 4391, 3383 # JV-01, JV-01 */
        * ETH_SPECIAL_DESC_SIZE));                                                                                      /* PRQA S 3384 # JV-01 */
      break;

    default:
      /* RX Stream */
      if (ETH_ENABLE == LpHwUnitConfig->stRxConfig.enEts2)
      {
        /* TS enabled for Rx Stream */
        LulDescAddr = Eth_Ram_Alloc(LulCtrlIdx,
          (uint32)(((LpHwUnitConfig->stQueueConfig.pRxQueueConfig[LulCfgIdx].usEthRxQueueBufs + ETH_CYCLIC_DESC_NUM)    /* PRQA S 4391, 3383 # JV-01, JV-01 */
          * ETH_SPECIAL_DESC_SIZE)));                                                                                   /* PRQA S 3384 # JV-01 */
      }
      else
      {
        /* TS disabled for Rx Stream  */
        LulDescAddr = Eth_Ram_Alloc(LulCtrlIdx,
          (uint32)((LpHwUnitConfig->stQueueConfig.pRxQueueConfig[LulCfgIdx].usEthRxQueueBufs + ETH_CYCLIC_DESC_NUM)     /* PRQA S 4391, 3383 # JV-01, JV-01 */
          * ETH_NORMAL_DESC_SIZE));                                                                                     /* PRQA S 3384 # JV-01 */
      }

      break;
    }
  }

  return (LulDescAddr);
}

/***********************************************************************************************************************
** Function Name         : FillDescMemory
**
** Service ID            : NA
**
** Description           : Set LinkFix for all DBA for each Queue
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulDescAddr
**
** InOut Parameters      : LpLinkDescr
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
** Reference ID          : ETH_DUD_ACT_426
***********************************************************************************************************************/
STATIC FUNC(void, ETH_PRIVATE_CODE) FillDescMemory(
  CONSTP2VAR(Eth_LinkDescType, AUTOMATIC, ETH_APPL_DATA) LpLinkDescr, CONST(uint32, AUTOMATIC) LulDescAddr)             /* PRQA S 3432 # JV-01 */
{
  if (NULL_PTR != LpLinkDescr)
  {
    LpLinkDescr->stHeader.ulDie  = 0U;
    LpLinkDescr->stHeader.ulRes  = 0U;
    LpLinkDescr->ulDptr      = LulDescAddr;
    LpLinkDescr->stHeader.ulDt   = ETH_DESC_LINKFIX;
  }
  else
  {
    /* No action at this level */
  }
}

/***********************************************************************************************************************
** Function Name         : IsQueueConfigured
**
** Service ID            : NA
**
** Description           : Use the Binary Search Algo to discover if
**                         a Queue is configured and in this case return
**                         Direction otherwise return false and
**                         Direction is irrelevant
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LucQidx - Queue Index to see if configured
**                       : LenDir - Direction Type
**
** InOut Parameters      : None
**
** Output Parameters     : pDir Direction of the Queue Configured
**
** Return parameter      : True: Qidx found in config structure
**                       : False: Qidx not found in config struct
**
** Preconditions         : None
**
** Global Variable(s)    : Eth_GpCtrlConfigPtr
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_427
***********************************************************************************************************************/
STATIC FUNC(boolean, ETH_PRIVATE_CODE) IsQueueConfigured(
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint8, AUTOMATIC) LucQidx, CONST(Eth_DirectionType, AUTOMATIC) LenDir)
{
  uint8 LucVal;
  boolean LblReturnVal;
  P2CONST(Eth_ETNFConfigType, AUTOMATIC, ETH_APPL_DATA) LpHwUnitConfig;

  LpHwUnitConfig = (P2CONST(Eth_ETNFConfigType, AUTOMATIC, ETH_APPL_DATA))                                              /* PRQA S 0316 # JV-01 */
    Eth_GpCtrlConfigPtr[LulCtrlIdx].pHwUnitConfig;
  LucVal = 0U;
  LblReturnVal = ETH_FALSE;

  if (ETH_TX == LenDir)
  {
    /* Tx Queues */
    do
    {
      if (LucQidx == LpHwUnitConfig->stQueueConfig.pTxQueueConfig[LucVal].ucEthTxQueueId)                               
      {
        LblReturnVal = ETH_TRUE;
      }
      else
      {
        LucVal++;                                                                                                       /* PRQA S 3383 # JV-01 */
      }
    }
    while ((ETH_FALSE == LblReturnVal) && (LucVal < LpHwUnitConfig->stQueueConfig.ucNumberOfTxQueue));
  }
  else
  {
    /* Rx Queues */
    do
    {
      if (LucQidx == LpHwUnitConfig->stQueueConfig.pRxQueueConfig[LucVal].ucEthRxQueueId)                               
      {
        LblReturnVal = ETH_TRUE;
      }
      else
      {
        LucVal++;                                                                                                       /* PRQA S 3383 # JV-01 */
      }
    }
    while ((ETH_FALSE == LblReturnVal) && (LucVal < LpHwUnitConfig->stQueueConfig.ucNumberOfRxQueue));
  }

  return (LblReturnVal);
}

/***********************************************************************************************************************
** Function Name         : Eth_Hw_ETNF_DisableController
**
** Service ID            : NA
**
** Description           : This Disables the indexed Ethernet Controller
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulCtrlIdx - Ethernet Controller index
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
** Function(s) invoked   : GetCounterValue, Eth_ETNF_GetElapsedTimeValue,
**                         Eth_Hw_ETNF_OpModeChange
**
** Registers Used        : ETNFnCCC, ETNFnECMR, ETNFnTCCR, ETNFnCSR
**
** Reference ID          : ETH_DUD_ACT_428,
** Reference ID          : ETH_DUD_ACT_428_GBL001, ETH_DUD_ACT_428_REG001
** Reference ID          : ETH_DUD_ACT_428_REG002, ETH_DUD_ACT_428_REG003
** Reference ID          : ETH_DUD_ACT_428_REG005, ETH_DUD_ACT_428_REG007
***********************************************************************************************************************/
FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_Hw_ETNF_DisableController(                                                   
  CONST(uint32, AUTOMATIC) LulCtrlIdx)
{
  Std_ReturnType LucErrorValue;
  TickType LulTimeOutCountInit;
  TickType LulTimeoutCountElap;
  uint32 LulRegVal;

  if (ETH_OPERATION == Eth_GaaCtrlStat[LulCtrlIdx].stHwStatEtnf.enDevStatus)                                            
  {
    /* Disable the DMAC and MAC of Controller for pending Tx or Rx */
    Eth_GaaETNFRegs[LulCtrlIdx]->ulECMR &= ~ETH_ETNF_ECMR_RE_TE;                                                        

    /* Wait for completion of transmission request */
    LulTimeOutCountInit = 0UL;
    LulTimeoutCountElap = 0UL;
    (void)GetCounterValue((CounterType)ETH_OS_COUNTER_ID, &LulTimeOutCountInit);
    do
    {
      LulTimeoutCountElap = LulTimeoutCountElap + Eth_ETNF_GetElapsedTimeValue(&LulTimeOutCountInit);                   /* PRQA S 3383 # JV-01 */
      LulRegVal = Eth_GaaETNFRegs[LulCtrlIdx]->ulTCCR & ETH_TCCR_TSRQX_MASK;
    } while ((LulRegVal != 0UL) && (LulTimeoutCountElap <= ETH_TIMEOUT_COUNT));
    /* Wait for completion of reception/transmit process */
    LulTimeOutCountInit = 0UL;
    LulTimeoutCountElap = 0UL;
    (void)GetCounterValue((CounterType)ETH_OS_COUNTER_ID, &LulTimeOutCountInit);
    do
    {
      LulTimeoutCountElap = LulTimeoutCountElap + Eth_ETNF_GetElapsedTimeValue(&LulTimeOutCountInit);                   /* PRQA S 3383 # JV-01 */
      LulRegVal = Eth_GaaETNFRegs[LulCtrlIdx]->ulCSR & ETH_CSR_TDUO_RPO_TPOX_MASK;
    } while ((LulRegVal != 0UL) && (LulTimeoutCountElap <= ETH_TIMEOUT_COUNT));

    /* Process all required status information */
    /* In ETNF, necessary information is not reset in CONFIG and STANDBY mode.*/
    Eth_GaaETNFRegs[LulCtrlIdx]->ulCCC |= ETH_ETNF_CCC_DTSR;

    LulTimeOutCountInit = 0UL;
    LulTimeoutCountElap = 0UL;
    (void)GetCounterValue((CounterType)ETH_OS_COUNTER_ID, &LulTimeOutCountInit);
    do
    {
      LulTimeoutCountElap = LulTimeoutCountElap + Eth_ETNF_GetElapsedTimeValue(&LulTimeOutCountInit);                   /* PRQA S 3383 # JV-01 */
      LulRegVal = Eth_GaaETNFRegs[LulCtrlIdx]->ulCSR & ETH_ETNF_CSR_DTS;
    } while ((LulRegVal != ETH_ETNF_CSR_DTS) && (LulTimeoutCountElap <= ETH_TIMEOUT_COUNT));
  }
  else
  {
    /* No action required */
  }

  LucErrorValue = Eth_Hw_ETNF_OpModeChange(LulCtrlIdx, ETH_CONFIG);

  if (ETH_CONFIG != Eth_GaaCtrlStat[LulCtrlIdx].stHwStatEtnf.enDevStatus)                                               
  {
    LulRegVal = Eth_GaaETNFRegs[LulCtrlIdx]->ulCCC & ~ETH_ETNF_CCC_OPC_MASK;
    Eth_GaaETNFRegs[LulCtrlIdx]->ulCCC = LulRegVal | ETH_ETNF_CCC_OPC_OPERATION;
    Eth_GaaETNFRegs[LulCtrlIdx]->ulCCC &= ~ETH_ETNF_CCC_DTSR;

    /* Wait for completion of reception/transmit process */
    LulTimeOutCountInit = 0UL;
    LulTimeoutCountElap = 0UL;
    (void)GetCounterValue((CounterType)ETH_OS_COUNTER_ID, &LulTimeOutCountInit);
    do
    {
      LulTimeoutCountElap = LulTimeoutCountElap + Eth_ETNF_GetElapsedTimeValue(&LulTimeOutCountInit);                   /* PRQA S 3383 # JV-01 */
      LulRegVal = Eth_GaaETNFRegs[LulCtrlIdx]->ulCSR & ETH_ETNF_CSR_TDUO_RPO;
    } while ((LulRegVal != 0UL) && (LulTimeoutCountElap <= ETH_TIMEOUT_COUNT));

    Eth_GaaETNFRegs[LulCtrlIdx]->ulCCC |= ETH_ETNF_CCC_DTSR;

    LulTimeOutCountInit = 0UL;
    LulTimeoutCountElap = 0UL;
    (void)GetCounterValue((CounterType)ETH_OS_COUNTER_ID, &LulTimeOutCountInit);
    do
    {
      LulTimeoutCountElap = LulTimeoutCountElap + Eth_ETNF_GetElapsedTimeValue(&LulTimeOutCountInit);                   /* PRQA S 3383 # JV-01 */
      LulRegVal = Eth_GaaETNFRegs[LulCtrlIdx]->ulCSR & ETH_ETNF_CSR_DTS;
    } while ((LulRegVal != ETH_ETNF_CSR_DTS) && (LulTimeoutCountElap <= ETH_TIMEOUT_COUNT));

    LucErrorValue = Eth_Hw_ETNF_OpModeChange(LulCtrlIdx, ETH_CONFIG);
  }
  else
  {
    /* No action required */
  }
  Eth_GaaETNFRegs[LulCtrlIdx]->ulCCC &= ~ETH_ETNF_CCC_DTSR;

  return LucErrorValue;
}

/***********************************************************************************************************************
** Function Name         : Eth_ETNF_GetElapsedTimeValue
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
** Reference ID          : ETH_DUD_ACT_429
***********************************************************************************************************************/
FUNC(TickType, ETH_PRIVATE_CODE) Eth_ETNF_GetElapsedTimeValue(
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

#if (ETH_STREAM_FILTERING == STD_ON)
/***********************************************************************************************************************
** Function Name         : SetRxFilter
**
** Service ID            : NA
**
** Description           : Configure SFO, SFM, SFP
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulCtrlIdx - Ethernet Controller index
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : void
**
** Preconditions         : None
**
** Global Variable(s)    : Eth_GaaETNFRegs, Eth_GaaAvbConfig
**                         Eth_GpCtrlConfigPtr
**
** Function(s) invoked   : Eth_Hw_ETNF_WriteIntoSFPReg
**
** Registers Used        : SFO, SFM0, SFM1
**
** Reference ID          : ETH_DUD_ACT_430,
** Reference ID          : ETH_DUD_ACT_430_GBL001, ETH_DUD_ACT_430_GBL002
** Reference ID          : ETH_DUD_ACT_430_GBL003, ETH_DUD_ACT_430_GBL004
** Reference ID          : ETH_DUD_ACT_430_GBL005
***********************************************************************************************************************/
STATIC FUNC (void,  ETH_PRIVATE_CODE) SetRxFilter(
  CONST(uint32, AUTOMATIC) LulCtrlIdx)
{
  #if (ETH_STREAM_FILTERING == STD_ON)
  VAR(uint8, AUTOMATIC) LucNumberOfRxQueue;
  VAR(uint8, AUTOMATIC) LucCount;
  VAR(uint8, AUTOMATIC) LucQidx;
  #endif
  P2CONST(Eth_ETNFConfigType, AUTOMATIC, ETH_APPL_DATA) LpHwUnitConfig;

  LpHwUnitConfig = (P2CONST(Eth_ETNFConfigType, AUTOMATIC, ETH_APPL_DATA))                                              /* PRQA S 0316 # JV-01 */
    Eth_GpCtrlConfigPtr[LulCtrlIdx].pHwUnitConfig;
  Eth_GaaETNFRegs[LulCtrlIdx]->ulSFO = ETH_ETNF_SFO_FBP_VALUE;                                                          
  if (ETH_ENABLE == Eth_GaaAvbConfig[LulCtrlIdx].stRxConfig.enSRPTalkerFiltering)                                       
  {
    Eth_GaaETNFRegs[LulCtrlIdx]->ulSFM[0] = ETH_ETNF_SFM0_TALKERFILTER;
    Eth_GaaETNFRegs[LulCtrlIdx]->ulSFM[1] = ETH_ETNF_SFM1_TALKERFILTER;
  }
  else
  {
    Eth_GaaETNFRegs[LulCtrlIdx]->ulSFM[0] = ETH_ETNF_SFM0_LISNERFILTER;
    Eth_GaaETNFRegs[LulCtrlIdx]->ulSFM[1] = ETH_ETNF_SFM1_LISNERFILTER;
  }

  #if (ETH_STREAM_FILTERING == STD_ON)
  /* Get number of configured queues */
  LucNumberOfRxQueue = LpHwUnitConfig->stQueueConfig.ucNumberOfRxQueue;                                                 
  for (LucCount = 0U; LucCount < LucNumberOfRxQueue; LucCount++)
  {
    LucQidx = LpHwUnitConfig->stQueueConfig.pRxQueueConfig[LucCount].ucEthRxQueueId;                                    

    /* If Rx Queue is Stream set corresponding SPFI register */
    if (ETH_NCCHANNEL < LucQidx)
    {
      /* Write into SFP Register */
      Eth_Hw_ETNF_WriteIntoSFPReg(
        LulCtrlIdx, LpHwUnitConfig->stQueueConfig.pRxQueueConfig[LucCount].aaEthPatternStream, LucQidx);
    }
    else
    {
      /* NO action as this is not a RX Stream Queue */
    }
  }
  #endif
}

/***********************************************************************************************************************
** Function Name         : Eth_Hw_ETNF_WriteIntoSFPReg
**
** Service ID            : NA
**
** Description           : Write In corresponding SFPi the passed address
**                         (for Rx Filter)
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulCtrlIdx - Ethernet Controller index
**                       : LpMacAddrPtr - Pointer to the address to be stored
**                       : LucQueueIdx - In case of clear this is the index of
**                         the SFP register minus offset
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : AVB shall be into Config Mode
**
** Global Variable(s)    : Eth_GaaAvbConfig, Eth_GaaETNFRegs
**
** Function(s) invoked   : None
**
** Registers Used        : CCC, SFV, SFL, SFPi i = 0,1..31
**
** Reference ID          : ETH_DUD_ACT_431,
** Reference ID          : ETH_DUD_ACT_431_GBL001, ETH_DUD_ACT_431_GBL002
** Reference ID          : ETH_DUD_ACT_431_GBL003, ETH_DUD_ACT_431_GBL004
** Reference ID          : ETH_DUD_ACT_431_GBL005
***********************************************************************************************************************/
FUNC (void, ETH_PRIVATE_CODE) Eth_Hw_ETNF_WriteIntoSFPReg(
  CONST(uint32,AUTOMATIC) LulCtrlIdx, CONSTP2CONST(uint8, AUTOMATIC, ETH_APPL_DATA) LpMacAddrPtr,
  CONST(uint8,AUTOMATIC) LucQueueIdx)
{
  uint32 LulValHigh;
  uint32 LulValLow;
  uint32 LulVal;
  uint8 LucSFPidx;
  /************ Little Endian Core **************/
  LucSFPidx = LucQueueIdx - ETH_RX_QUEUE_INDEX_AVAILABLE_FILTER;                                                        /* PRQA S 3383 # JV-01 */
  /* Write into SFP1,3,...31 */
  if (ETH_ENABLE == Eth_GaaAvbConfig[LulCtrlIdx].stRxConfig.enSRPTalkerFiltering)                                       
  {
    LulValHigh = ((uint32)LpMacAddrPtr[5] << 8U) | ((uint32)LpMacAddrPtr[4]);                                           
  }
  else
  {
    LulValHigh = ((uint32)LpMacAddrPtr[7] << 24U) | ((uint32)LpMacAddrPtr[6] << 16U) |
      ((uint32)LpMacAddrPtr[5] << 8U) | ((uint32)LpMacAddrPtr[4]);
  }
  /* Write into SFP0,2,..30 */
  LulValLow = ((uint32)LpMacAddrPtr[3] << 24U) | ((uint32)LpMacAddrPtr[2] << 16U) |
    ((uint32)LpMacAddrPtr[1] << 8U) | ((uint32)LpMacAddrPtr[0]);
  /* Read Opc */
  if (ETH_OPERATION == Eth_GaaCtrlStat[LulCtrlIdx].stHwStatEtnf.enDevStatus)                                            
  {
    Eth_GaaETNFRegs[LulCtrlIdx]->ulSFV[0] = LulValLow;                                                                  
    Eth_GaaETNFRegs[LulCtrlIdx]->ulSFV[1] = LulValHigh;
    /* Check it can be updated */

    do
    {
      LulVal = Eth_GaaETNFRegs[LulCtrlIdx]->ulSFL;
    } while (ETH_NO_LOAD_REQ != (LulVal & ETH_SFL_MASK));

    /* SFP update request */
    LulVal = (uint32)LucSFPidx;
    Eth_GaaETNFRegs[LulCtrlIdx]->ulSFL = LulVal;
  }
  else
  {
    Eth_GaaETNFRegs[LulCtrlIdx]->ulSFP[ETH_ETNF_GET_LOW_SFPi(LucSFPidx)] = LulValLow;                                   /* PRQA S 3469, 3383 # JV-01, JV-01 */
    Eth_GaaETNFRegs[LulCtrlIdx]->ulSFP[ETH_ETNF_GET_HIGH_SFPi(LucSFPidx)] = LulValHigh;                                 /* PRQA S 3469, 3383 # JV-01, JV-01 */
  }

}
#endif /* (ETH_STREAM_FILTERING == STD_ON) */

#if (ETH_GLOBAL_TIME_SUPPORT == STD_ON)
/***********************************************************************************************************************
** Function Name         : Eth_Hw_ETNF_WaitPTPRequestIsComplete
**
** Service ID            : NA
**
** Description           : Service Api to wait a Gptp request is complete
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant for the same Ctrl ,
**                         Re-entrant for different
**
** Input Parameters      : LulCtrlIdx   Index of the controller within the
**                         context of the Ethernet Driver
**                       : LucBit Which Bit to poll in GCCR Register
**
** InOut Parameters      : None
**
** Output Parameters     : E_OK   gPTP Request is completed w/o timeout
**                       : E_NOT_OK gPTP Request not completed due to timeout
**
** Return parameter      : LucReturnValue E_OK / E_NOT_OK
**
** Preconditions         : Component Requires previous controller
**                         initialization using Eth_ControllerInit..
**
** Global Variable(s)    : Eth_GaaETNFRegs
**
** Function(s) invoked   : GetCounterValue, Eth_ETNF_GetElapsedTimeValue
**
** Registers Used        : GCCR
**
** Reference ID          : ETH_DUD_ACT_432
***********************************************************************************************************************/
FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_Hw_ETNF_WaitPTPRequestIsComplete(                                            
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32,AUTOMATIC) LulMask)
{
  Std_ReturnType LucReturnValue;
  uint32 LulRegValue;
  TickType LulTimeOutCountInit;
  TickType LulTimeoutCountElap;

  LulTimeOutCountInit = 0UL;
  LulTimeoutCountElap = 0UL;

  (void)GetCounterValue((CounterType)ETH_OS_COUNTER_ID, &LulTimeOutCountInit);
  do
  {
    LulTimeoutCountElap = LulTimeoutCountElap + Eth_ETNF_GetElapsedTimeValue(&LulTimeOutCountInit);                     /* PRQA S 3383 # JV-01 */
    LulRegValue = Eth_GaaETNFRegs[LulCtrlIdx]->ulGCCR & LulMask;                                                        
  } while ((LulRegValue != 0UL) && (LulTimeoutCountElap <= ETH_TIMEOUT_COUNT));

  if (ETH_TIMEOUT_COUNT < LulTimeoutCountElap)
  {
    /* Timeout Occurred */
    LucReturnValue = E_NOT_OK;
  }
  else
  {
    /* Success */
    LucReturnValue = E_OK;
  }
 return (LucReturnValue);
}

#endif /* ETH_GLOBAL_TIME_SUPPORT */

#if (ETH_UPDATE_PHYS_ADDR_FILTER == STD_ON)
/***********************************************************************************************************************
** Function Name         : IsRxFrameValid
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
** Global Variables Used : Eth_GaaCtrlStat, Eth_GaaCtrlFilterAddr,
**                         Eth_GaaAddressFilters
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_433
***********************************************************************************************************************/
STATIC FUNC(boolean, ETH_PRIVATE_CODE) IsRxFrameValid(
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONSTP2CONST(Eth_RxFrameType, AUTOMATIC, ETH_APPL_DATA) LpRxFrame)
{
  Eth_MacAddressType LstDstAddress;
  boolean LblPass;
  uint32 LulFilterIdx;
  uint32 LulRemainBits;

  LblPass = ETH_FALSE;
  ETH_PACK_ADDRESS_FROM_8(((P2VAR(uint8, AUTOMATIC, ETH_APPL_DATA))LpRxFrame->ulFrameAddr), LstDstAddress);             /* PRQA S 3432, 3469, 0306 # JV-01, JV-01, JV-01 */

  /* Check whether promiscuous mode, broadcast, own unicast, multicast address is not registed */
  if ((ETH_TRUE == Eth_GaaCtrlStat[LulCtrlIdx].blPromiscuous) ||                                                        
      (0UL == ETH_COMPARE_MAC(LstDstAddress, Eth_GstBroadcastAddr)) ||                                                  /* PRQA S 3469 # JV-01 */
      (0UL == ETH_COMPARE_MAC(LstDstAddress, Eth_GaaCtrlStat[LulCtrlIdx].stMacAddr)))                                   /* PRQA S 3469 # JV-01 */
  {
    LblPass = ETH_TRUE;
  }
  else
  {
    /* Otherwise, do the filter operation */

    /* To skip empty filters efficiently, copy active bits to the local var */
    LulRemainBits = Eth_GaaCtrlStat[LulCtrlIdx].ulActiveFilterBits;
    LulFilterIdx = 0UL;
    /* Loop until any filter hits or pass all active filters */
    while (0UL != LulRemainBits)
    {
      if ((0UL != (LulRemainBits & (1UL << LulFilterIdx))) &&
          (0UL == ETH_COMPARE_MAC(LstDstAddress, Eth_GaaAddressFilters[LulCtrlIdx][LulFilterIdx])))                     /* PRQA S 3469 # JV-01 */
      {
        LblPass = ETH_TRUE;
        break;
      }
      else
      {
        /* No action required */
      }
      /* Clear the compared filter bit */
      LulRemainBits &= ~(1UL << LulFilterIdx);
      LulFilterIdx++;                                                                                                   /* PRQA S 3383 # JV-01 */
    }
  }

  return (LblPass);
}
#endif  /* (ETH_UPDATE_PHYS_ADDR_FILTER == STD_ON) */

#if (ETH_QOS_SUPPORT == STD_ON)
/***********************************************************************************************************************
** Function Name         : SetCbsParameter
**
** Service ID            : NA
**
** Description           : Set Tx queues configured
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : LulCtrlIdx - Index of the controller within the
**                         context of the Ethernet Driver
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variable(s)    : Eth_GaaETNFRegs, Eth_GpCtrlConfigPtr
**
** Function(s) invoked   : None
**
** Registers Used        : CIVR0..1, CDVR0..1, CUL0..1, CLL..10
**
** Reference ID          : ETH_DUD_ACT_434,
** Reference ID          : ETH_DUD_ACT_434_GBL001, ETH_DUD_ACT_434_GBL002
** Reference ID          : ETH_DUD_ACT_434_GBL003, ETH_DUD_ACT_434_GBL004
** Reference ID          : ETH_DUD_ACT_434_GBL005, ETH_DUD_ACT_434_GBL006
** Reference ID          : ETH_DUD_ACT_434_GBL007, ETH_DUD_ACT_434_GBL008
***********************************************************************************************************************/
STATIC FUNC(void, ETH_PRIVATE_CODE) SetCbsParameter(
  CONST(uint32, AUTOMATIC) LulCtrlIdx)
{
  uint32 LulQidx;

  uint32 LulCIV_tmp;
  uint32 LulCDV_tmp; /* negative number represented in 2'complement */
  P2CONST(Eth_ETNFConfigType, AUTOMATIC, ETH_APPL_DATA) LpHwUnitConfig;

  LpHwUnitConfig = (P2CONST(Eth_ETNFConfigType, AUTOMATIC, ETH_APPL_DATA))                                              /* PRQA S 0316 # JV-01 */
    Eth_GpCtrlConfigPtr[LulCtrlIdx].pHwUnitConfig;
  /* loop through all Tx Queues configured */
  LulQidx = 0UL;
  do
  {
    if (((uint8)(ETH_TX_SB) == LpHwUnitConfig->stQueueConfig.pTxQueueConfig[LulQidx].ucEthTxQueueId) &&                 
      (ETH_CBS == LpHwUnitConfig->stQueueConfig.pTxQueueConfig[LulQidx].stTxQueueShaper.enTxQPolicy))
    {
      /* Q2 */
      LulCIV_tmp = (uint32)(LpHwUnitConfig->stQueueConfig.pTxQueueConfig[LulQidx].stTxQueueShaper.ulCiv);

      LulCDV_tmp = (uint32)(LpHwUnitConfig->stQueueConfig.pTxQueueConfig[LulQidx].stTxQueueShaper.slCdv);
      /* Write into CIVR0 , CDVR0 */
      Eth_GaaETNFRegs[LulCtrlIdx]->ulCIVR[0] = LulCIV_tmp;                                                              
      Eth_GaaETNFRegs[LulCtrlIdx]->ulCDVR[0] = LulCDV_tmp;
      /* Set Upper Limit => 65535 */
      Eth_GaaETNFRegs[LulCtrlIdx]->ulCUL[0] = ETH_MAX_CIV;
      /* Set Lower Limit => -65536 */
      Eth_GaaETNFRegs[LulCtrlIdx]->ulCLL[0] = ETH_MIN_CDV;
    }
    else if (((uint8)(ETH_TX_SA) == LpHwUnitConfig->stQueueConfig.pTxQueueConfig[LulQidx].ucEthTxQueueId) &&
      (ETH_CBS == LpHwUnitConfig->stQueueConfig.pTxQueueConfig[LulQidx].stTxQueueShaper.enTxQPolicy))
    {
      /* Q3 */
      LulCIV_tmp = (uint32)(LpHwUnitConfig->stQueueConfig.pTxQueueConfig[LulQidx].stTxQueueShaper.ulCiv);

      LulCDV_tmp = (uint32)(LpHwUnitConfig->stQueueConfig.pTxQueueConfig[LulQidx].stTxQueueShaper.slCdv);

      /* Write into CIVR1 , CDVR1 */
      Eth_GaaETNFRegs[LulCtrlIdx]->ulCIVR[1] = LulCIV_tmp;
      Eth_GaaETNFRegs[LulCtrlIdx]->ulCDVR[1] = LulCDV_tmp;
      /* Set Upper Limit => 65535 */
      Eth_GaaETNFRegs[LulCtrlIdx]->ulCUL[1] = ETH_MAX_CIV;
      /* Set Lower Limit => -65536 */
      Eth_GaaETNFRegs[LulCtrlIdx]->ulCLL[1] = ETH_MIN_CDV;
    }
    else
    {
      /* Nothing to set for this Tx Queue */
    }

    LulQidx++;                                                                                                          /* PRQA S 3383 # JV-01 */
  } while (LulQidx < (uint32)LpHwUnitConfig->stQueueConfig.ucNumberOfTxQueue);
}
#endif

#if (ETH_CTRL_ENABLE_RX_INTERRUPT == STD_ON)
/***********************************************************************************************************************
** Function Name         : Eth_Hw_ETNF_RxIrqHdlr
**
** Service ID            : NA
**
** Description           : This API Handles frame reception interrupts
**                         of the indexed controller
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
** Preconditions         : Component Requires previous controller
**                         initialization using Eth_ControllerInit..
**
** Global Variables Used : Eth_GpCtrlConfigPtr, Eth_GaaETNFRegs
**
** Function(s) invoked   : Eth_Hw_ETNF_UFCounterGet,
**                         Eth_Hw_ETNF_RxQueueProcess
**
** Registers Used        : RIS0
**
** Reference ID          : ETH_DUD_ACT_435
***********************************************************************************************************************/
FUNC(void, ETH_PRIVATE_CODE) Eth_Hw_ETNF_RxIrqHdlr(                                                                     
  CONST(uint32, AUTOMATIC) LulCtrlIdx)
{
  uint32 LulRIS0;
  uint32 LulIdx;
  uint8 LucQidx;
  uint32 LulCnt;
  uint32 LulUnreadFrameCnt;
  P2CONST(Eth_ETNFConfigType, AUTOMATIC, ETH_APPL_DATA) LpHwUnitConfig;
  LpHwUnitConfig = (P2CONST(Eth_ETNFConfigType, AUTOMATIC, ETH_APPL_DATA))                                              /* PRQA S 0316 # JV-01 */
    Eth_GpCtrlConfigPtr[LulCtrlIdx].pHwUnitConfig;
  /* Initialize the counter */
  LulIdx = 0UL;
  /* Get receive interrupt status */
  LulRIS0 = Eth_GaaETNFRegs[LulCtrlIdx]->ulRIS0 & ETH_RX_INT_MASK;                                                      

  while (0UL != LulRIS0)
  {
    LucQidx = LpHwUnitConfig->stQueueConfig.pRxQueueConfig[LulIdx].ucEthRxQueueId;                                      
    if (ETH_BIT1_SET_32 == ((LulRIS0 >> LucQidx) & ETH_BIT1_SET_32))
    {
      LulUnreadFrameCnt = Eth_Hw_ETNF_UFCounterGet(LulCtrlIdx, (uint32)LucQidx);

      /* Queue that has received some frame/s */
      for (LulCnt = 0UL; LulCnt < LulUnreadFrameCnt; LulCnt++)
      {
        /* Rx frame data processing */
        (void)Eth_Hw_ETNF_RxQueueProcess(LulCtrlIdx, LucQidx);
      }
    }
    else
    {
      /* No action required */
    }

    if (LulIdx < (uint32)(LpHwUnitConfig->stQueueConfig.ucNumberOfRxQueue - 1U))                                        /* PRQA S 4391, 3383 # JV-01, JV-01 */
    {
      /* Next configured queue */
      LulIdx++;
    }
    else
    {
      /* Clear the flag to exit loop */
      LulRIS0 = 0UL;
    }
  }
}
#endif /* (ETH_CTRL_ENABLE_RX_INTERRUPT == STD_ON) */

#define ETH_STOP_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* (ETH_MACRO_ETNF == STD_ON) */
/***********************************************************************************************************************
**                                               End of File                                                          **
***********************************************************************************************************************/
