/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Eth_ETNF_Dma.h                                                                                      */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2023 - 2025 Renesas Electronics Corporation. All rights reserved.                                              */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Provision of prototypes for internal functions of Ethernet DMAC Component.                                         */
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
 * 2.4.0: 30/05/2025    : Update SW-VERSION for RH850/Ver22.01.02 U2Cx release
 * 2.3.1: 31/03/2025    : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 * 2.3.0: 28/02/2025    : - As per ticket ARDAACJ-695:
 *                        + Update to provide correct support for the function Eth_ETNF_GetTimeOutValue and 
 *                        change the name to Eth_ETNF_GetElapsedTimeValue
 * 2.2.0: 31/12/2024    : Update SW-VERSION for Ver22.02.00(D) U2Bx Final Release
 * 2.1.2: 31/10/2024    : Increase SW-VERSION to 2.1.2
 * 2.0.2: 19/12/2023    : Initial Version
 */
/**********************************************************************************************************************/
#ifndef ETH_ETNF_DMA_H
#define ETH_ETNF_DMA_H
/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for version information macros */
#include "Eth_Common_LLDriver.h"
#include "Os.h"

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
#if (ETH_MACRO_ETNF == STD_ON)
/* AUTOSAR release version information */
#define ETH_ETNF_DMA_AR_RELEASE_MAJOR_VERSION    ETH_AR_RELEASE_MAJOR_VERSION
#define ETH_ETNF_DMA_AR_RELEASE_MINOR_VERSION    ETH_AR_RELEASE_MINOR_VERSION
#define ETH_ETNF_DMA_AR_RELEASE_REVISION_VERSION ETH_AR_RELEASE_REVISION_VERSION

/* Module Software version information */
#define ETH_ETNF_DMA_SW_MAJOR_VERSION            ETH_SW_MAJOR_VERSION
#define ETH_ETNF_DMA_SW_MINOR_VERSION            ETH_SW_MINOR_VERSION

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

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/
#define ETH_START_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"

extern FUNC(void, ETH_PRIVATE_CODE) Eth_Hw_ETNF_DMACStructConfig(CONST(uint32, AUTOMATIC) LulCtrlIdx);

extern FUNC(void, ETH_PRIVATE_CODE) Eth_Hw_ETNF_DMACInit(CONST(uint32, AUTOMATIC) LulCtrlIdx);

extern FUNC(Std_ReturnType, ETH_PRIVATE_CODE)
    Eth_Hw_ETNF_OpModeChange(CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(Eth_OpStatusType, AUTOMATIC) LenMode);

extern FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_Hw_ETNF_RxMemAlloc(CONST(uint32, AUTOMATIC) LulCtrlIdx);

extern FUNC(void, ETH_PRIVATE_CODE) Eth_Hw_ETNF_DescConfig(CONST(uint32, AUTOMATIC) LulCtrlIdx);

extern FUNC(uint32, ETH_PRIVATE_CODE)
    Eth_Hw_ETNF_UFCounterGet(CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulQIndex);

extern FUNC(void, ETH_PRIVATE_CODE)
    Eth_Hw_ETNF_RxDescChainConfig(CONST(uint32, AUTOMATIC) LulCtrlIdx,
                                  CONSTP2CONST(Eth_RxChConfigType, AUTOMATIC, ETH_APPL_DATA) LpChConfig);

extern FUNC(boolean, ETH_PRIVATE_CODE)
    Eth_Hw_ETNF_RxQueueProcess(CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint8, AUTOMATIC) LucQidx);

extern FUNC(Std_ReturnType, ETH_PRIVATE_CODE)
    Eth_Hw_ETNF_SingleDescFrameSend(CONST(uint32, AUTOMATIC) LulCtrlIdx,
                                    CONSTP2VAR(Eth_BufHandlerType, AUTOMATIC, ETH_APPL_DATA) LpTxBufHdr);               /* PRQA S 3432 # JV-01 */

extern FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_Hw_ETNF_SYS_AllocDescBuffer(CONST(uint32, AUTOMATIC) LulCtrlIdx);

extern FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_Hw_ETNF_DisableController(CONST(uint32, AUTOMATIC) LulCtrlIdx);

extern FUNC(TickType, ETH_PRIVATE_CODE) Eth_ETNF_GetElapsedTimeValue(
    P2VAR(TickType, AUTOMATIC, ETH_APPL_DATA) LusTimeOutCount);                                                         /* PRQA S 3432 # JV-01 */

#if (ETH_STREAM_FILTERING == STD_ON)
extern FUNC(void, ETH_PRIVATE_CODE)
    Eth_Hw_ETNF_WriteIntoSFPReg(CONST(uint32, AUTOMATIC) LulCtrlIdx,
                                CONSTP2CONST(uint8, AUTOMATIC, ETH_APPL_DATA) LpMacAddrPtr,
                                CONST(uint8, AUTOMATIC) LucQueueIdx);
#endif

#if (ETH_GLOBAL_TIME_SUPPORT == STD_ON)
extern FUNC(Std_ReturnType, ETH_PRIVATE_CODE)
    Eth_Hw_ETNF_WaitPTPRequestIsComplete(CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulMask);
#endif

#if (ETH_CTRL_ENABLE_RX_INTERRUPT == STD_ON)
extern FUNC(void, ETH_PRIVATE_CODE) Eth_Hw_ETNF_RxIrqHdlr(CONST(uint32, AUTOMATIC) LulCtrlIdx);
#endif

#define ETH_STOP_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"

#endif /* ETH_ETNF_DMA_H */
#endif /* (ETH_MACRO_ETNF == STD_ON) */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
