/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Eth_ETNF_Ram.h                                                                                      */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2024, 2025 Renesas Electronics Corporation. All rights reserved.                                               */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains Ethernet driver global variables and the                                                        */
/* Ram Allocation functions                                                                                           */
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
 * 2.3.0: 28/02/2025    : Update SW-VERSION for Ver22.01.00/Ver22.01.00.D U2Cx Release
 * 2.2.0: 31/12/2024    : Update SW-VERSION for Ver22.02.00(D) U2Bx Final Release
 * 2.1.2: 31/10/2024    : Increase SW-VERSION to 2.1.2
 * 2.1.1: 03/06/2024    : Remove extern of Eth_GaaRxBufferIndex
 * 2.0.2: 22/01/2024    : Initial Version
 */
/**********************************************************************************************************************/

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
/* Message (2:3472)    : All toplevel uses of this function-like macro look like they could be replaced by            */
/*                       equivalent function calls.                                                                   */
/* Rule                : MISRA C:2012 Dir-4.9                                                                         */
/* JV-01 Justification : To prevent overhead and speed up the processing, there is no need to use function call for   */
/*                       such a small operation.                                                                      */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/**********************************************************************************************************************/
#ifndef ETH_ETNF_RAM_H
#define ETH_ETNF_RAM_H
/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for utility definitions */
#include "Eth_Common_LLDriver.h"

/* Included for Type definitions */
#include "Eth_Types.h"

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
#if (ETH_MACRO_ETNF == STD_ON)
/* AUTOSAR release version information */
#define ETH_ETNF_RAM_AR_RELEASE_MAJOR_VERSION    ETH_AR_RELEASE_MAJOR_VERSION
#define ETH_ETNF_RAM_AR_RELEASE_MINOR_VERSION    ETH_AR_RELEASE_MINOR_VERSION
#define ETH_ETNF_RAM_AR_RELEASE_REVISION_VERSION ETH_AR_RELEASE_REVISION_VERSION

/* Module Software version information */
#define ETH_ETNF_RAM_SW_MAJOR_VERSION            ETH_SW_MAJOR_VERSION
#define ETH_ETNF_RAM_SW_MINOR_VERSION            ETH_SW_MINOR_VERSION
/***********************************************************************************************************************
**                                              MISRA C Rule Violations                                               **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                    QAC Warning                                                     **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/
#define ETH_START_SEC_VAR_NO_INIT_BOOLEAN
#include "Eth_MemMap.h"

#define ETH_STOP_SEC_VAR_NO_INIT_BOOLEAN
#include "Eth_MemMap.h"

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

extern P2VAR(Eth_MemManagerType, ETH_VAR_FAST_NO_INIT, ETH_VAR_FAST_NO_INIT)                                            /* PRQA S 3432 # JV-01 */
    Eth_GpRamManager[ETH_TOTAL_CTRL_CONFIG];

#define ETH_STOP_SEC_VAR_NO_INIT_PTR
#include "Eth_MemMap.h"

#define ETH_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Eth_MemMap.h"

extern VAR(Eth_ListType, ETH_VAR_NO_INIT) Eth_GaaBufferLock[ETH_TOTAL_CTRL_CONFIG][ETH_TXQ_NUM];

extern VAR(Eth_RxChConfigType, ETH_VAR_NO_INIT) Eth_GaaRxConfig[ETH_RXQ_NUM];

extern VAR(Eth_AvbConfigType, ETH_VAR_NO_INIT) Eth_GaaAvbConfig[ETH_TOTAL_CTRL_CONFIG];

extern VAR(Eth_QConfigType, ETH_VAR_NO_INIT) Eth_GaaQConfig[ETH_RXQ_NUM];

extern VAR(Eth_TxBufferType, ETH_VAR_NO_INIT) Eth_GaaTxBufferIndex[ETH_TOTAL_CTRL_CONFIG][ETH_TX_DESC_MAX];

#define ETH_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Eth_MemMap.h"

#define ETH_START_SEC_VAR_INIT_BOOLEAN
#include "Eth_MemMap.h"

#define ETH_STOP_SEC_VAR_INIT_BOOLEAN
#include "Eth_MemMap.h"

#define ETH_START_SEC_VAR_INIT_8
#include "Eth_MemMap.h"

#define ETH_STOP_SEC_VAR_INIT_8
#include "Eth_MemMap.h"

#define ETH_START_SEC_VAR_INIT_16
#include "Eth_MemMap.h"

#define ETH_STOP_SEC_VAR_INIT_16
#include "Eth_MemMap.h"

#define ETH_START_SEC_VAR_INIT_32
#include "Eth_MemMap.h"

#define ETH_STOP_SEC_VAR_INIT_32
#include "Eth_MemMap.h"

#define ETH_START_SEC_VAR_INIT_PTR
#include "Eth_MemMap.h"
#define ETH_STOP_SEC_VAR_INIT_PTR
#include "Eth_MemMap.h"

#define ETH_START_SEC_VAR_INIT_UNSPECIFIED
#include "Eth_MemMap.h"
/* Function pointer variable for OSTM Unit configuration */
extern VAR(Eth_HwFuncTableType, ETH_VAR_INIT) Eth_EtnfFunc;
#define ETH_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Eth_MemMap.h"

/***********************************************************************************************************************
**                                                   Macro Defines                                                    **
***********************************************************************************************************************/
#define ETH_DWORD_SIZE        4UL
#define ETH_ALIGN_TO_32BIT(n) ((((n) + ETH_DWORD_SIZE) - 1UL) & 0xFFFFFFFCUL)                                           /* PRQA S 3472 # JV-01 */

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/
#define ETH_START_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"
extern FUNC(void, ETH_PRIVATE_CODE) Eth_ETNF_InitializeBuffer(CONST(uint32, AUTOMATIC) LulCtrlIdx);
extern FUNC(void, ETH_PRIVATE_CODE) Eth_ETNF_PreprocessBuffer(CONST(uint32, AUTOMATIC) LulCtrlIdx);
extern FUNC(BufReq_ReturnType, ETH_PRIVATE_CODE)
    Eth_ETNF_GetTxBuffer(CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint8, AUTOMATIC) LucPriority,
                    CONSTP2VAR(Eth_BufIdxType, AUTOMATIC, ETH_APPL_DATA) LpBufIdxPtr,                                   /* PRQA S 3432 # JV-01 */
                    CONSTP2VAR(uint8 *, AUTOMATIC, ETH_APPL_DATA) LpBufPtr,                                             /* PRQA S 3432 # JV-01 */
                    CONSTP2VAR(uint16, AUTOMATIC, ETH_APPL_DATA) LenBytePtr);                                           /* PRQA S 3432 # JV-01 */
extern FUNC(void, ETH_PRIVATE_CODE)
    Eth_ETNF_ReleaseTxBuffer(CONST(uint32, AUTOMATIC) LulCtrlIdx,
                        CONST(uint32, AUTOMATIC) LulBufIdx);
extern FUNC(Std_ReturnType, ETH_PRIVATE_CODE)
    Eth_ETNF_CheckProvideBuffer(CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulBufIdx);
extern FUNC(void, ETH_PRIVATE_CODE)
    Eth_ETNF_PreprocessFrame(CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulBufIdx,
                        CONST(uint32, AUTOMATIC) LulFrameType,
                        CONSTP2CONST(uint8, AUTOMATIC, ETH_APPL_DATA) LpPhysAddrPtr,
                        CONSTP2VAR(uint16, AUTOMATIC, ETH_APPL_DATA) LpPayloadLen);                                     /* PRQA S 3432 # JV-01 */
extern FUNC(void, ETH_PRIVATE_CODE)
    Eth_Ram_Init(CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulBaseAddr,
                 CONST(uint32, AUTOMATIC) LulRamSize);

extern FUNC(uint32, ETH_PRIVATE_CODE)
    Eth_Ram_Alloc(CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulRamSize);

extern FUNC(void, ETH_PRIVATE_CODE)
    Eth_Ram_Free(CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulMemAddr);

extern FUNC(uint32, ETH_PRIVATE_CODE) Eth_Ram_GetNextFreeAddr(CONST(uint32, AUTOMATIC) LulCtrlIdx);

extern FUNC(void, ETH_PRIVATE_CODE) Eth_Ram_SetCircularAddr(CONST(uint32, AUTOMATIC) LulCtrlIdx);

extern FUNC(boolean, ETH_PRIVATE_CODE)
    Eth_Ram_CheckValidAddr(Eth_ListType *LpList, uint32 *LpStartAddr, uint32 LulRamSize);

extern FUNC(Eth_BufHandlerType *, ETH_PRIVATE_CODE)
    Eth_ETNF_FindTxBufferHandler(CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulBufIdx);

#define ETH_STOP_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"
#endif /* ETH_ETNF_RAM_H  */
#endif /* ETH_MACRO_ETNF == STD_ON */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
