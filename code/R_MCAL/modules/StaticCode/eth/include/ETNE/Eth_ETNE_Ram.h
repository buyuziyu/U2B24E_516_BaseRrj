/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Eth_ETNE_Ram.h                                                                                      */
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
 * 2.4.1: 30/06/2025    : Change ETH_TOTAL_CTRL_CONFIG to ETH_ETNE_CTRLS_SUPPORTED
 *                      : Remove the SW-VERSION from header of file
 * 2.4.0: 30/06/2025    : Update SW-VERSION for RH850/Ver22.01.00 (D) U2Ax release
 * 2.3.1: 31/03/2025    : Change size of Eth_GaaDemEventTimeroffsetFailed and Add QAC-3684
 *                      : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 * 2.3.0: 28/02/2025    : Update SW-VERSION for Ver22.01.00/Ver22.01.00.D U2Cx Release
 * 2.2.0: 31/12/2024    : Update SW-VERSION for Ver22.02.00(D) U2Bx Final Release
 * 2.1.2: 31/10/2024    : Increase SW-VERSION to 2.1.2
 * 2.1.1: 17/07/2024    : Add precompile all source code by ETH_MACRO_ETNE == STD_ON
 *        31/05/2024    : Initial Version
 */
/**********************************************************************************************************************/
/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE Rule CWE-398, CWE-569                                            */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is accepted. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3684)    : Array declared with unknown size.                                                            */
/* Rule                : CERTCCM ARR02, MISRA C:2012 Rule-8.11                                                        */
/* JV-01 Justification : Arrays used are verified in the file which are only declarations and size is configuration   */
/*                       dependent.                                                                                   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/**********************************************************************************************************************/
#ifndef ETH_ETNE_RAM_H
#define ETH_ETNE_RAM_H
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
#if (ETH_MACRO_ETNE == STD_ON)
/* AUTOSAR release version information */
#define ETH_ETNE_RAM_AR_RELEASE_MAJOR_VERSION    ETH_AR_RELEASE_MAJOR_VERSION
#define ETH_ETNE_RAM_AR_RELEASE_MINOR_VERSION    ETH_AR_RELEASE_MINOR_VERSION
#define ETH_ETNE_RAM_AR_RELEASE_REVISION_VERSION ETH_AR_RELEASE_REVISION_VERSION

/* Module Software version information */
#define ETH_ETNE_RAM_SW_MAJOR_VERSION            ETH_SW_MAJOR_VERSION
#define ETH_ETNE_RAM_SW_MINOR_VERSION            ETH_SW_MINOR_VERSION
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

extern P2VAR(void, ETH_VAR_FAST_NO_INIT, ETH_VAR_FAST_NO_INIT) Eth_GpDescHeap;

/* Global variable to store pointer to Configuration */
extern P2CONST(Eth_GwcaRegValue, ETH_CONST, ETH_CONFIG_CONST) volatile Eth_GpGwcaRegPtr;
extern P2CONST(Eth_GlobalPauseConfiguration, ETH_CONST, ETH_CONFIG_CONST) volatile Eth_GpGlobalPauseCfgPtr;
extern P2CONST(Eth_BothCoreConfiguration, ETH_CONST, ETH_CONFIG_CONST) volatile Eth_GpBothCoreCfgPtr;
extern P2CONST(Eth_EthConfigType, ETH_CONST, ETH_CONFIG_CONST) volatile
  Eth_GaaSerdesChConfig[ETH_RACE_PORT_TSNA_N];

#if (ETH_GLOBAL_TIME_SUPPORT == STD_ON)
extern P2VAR(Eth_TSDescType, ETH_VAR_FAST_NO_INIT, ETH_VAR_FAST_NO_INIT) Eth_GpNextTsDesc;                              /* PRQA S 3432 # JV-01 */
#endif

#define ETH_STOP_SEC_VAR_NO_INIT_PTR
#include "Eth_MemMap.h"

#define ETH_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Eth_MemMap.h"
#if (ETH_UPDATE_PHYS_ADDR_FILTER == STD_ON)
extern VAR(Eth_MacFilterMng, ETH_VAR_NO_INIT) Eth_GaaMacFilterMng[ETH_MAX_CTRLS_SUPPORTED];
#endif /* (ETH_UPDATE_PHYS_ADDR_FILTER == STD_ON) */

/* Descriptor Chain information Map table */
extern VAR(Eth_DescChainMap, ETH_VAR_NO_INIT) Eth_GstDescChainMap;

#define ETH_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Eth_MemMap.h"

#define ETH_START_SEC_VAR_INIT_BOOLEAN
#include "Eth_MemMap.h"

extern VAR(boolean, ETH_VAR_INIT)Eth_GaaRsw2PortValid[ETH_RACE_PORT_N];
extern VAR(boolean, ETH_VAR_INIT)Eth_GaaRsw2GWCACtrlValid;

#define ETH_STOP_SEC_VAR_INIT_BOOLEAN
#include "Eth_MemMap.h"

#define ETH_START_SEC_VAR_INIT_8
#include "Eth_MemMap.h"

#define ETH_STOP_SEC_VAR_INIT_8
#include "Eth_MemMap.h"

#define ETH_START_SEC_VAR_INIT_16
#include "Eth_MemMap.h"

extern VAR(uint16, ETH_VAR_INIT) Eth_GaaDemEventTimeroffsetFailed[];                                                    /* PRQA S 3684 # JV-01 */

#define ETH_STOP_SEC_VAR_INIT_16
#include "Eth_MemMap.h"

#define ETH_START_SEC_VAR_INIT_32
#include "Eth_MemMap.h"

extern VAR(uint32, ETH_VAR_INIT) Eth_GulRxMaxFrameSize;

#define ETH_STOP_SEC_VAR_INIT_32
#include "Eth_MemMap.h"

#define ETH_START_SEC_VAR_CLEARED_DESCRIPTOR_32
#include "Eth_MemMap.h"

/* LINKFIX table */
extern VAR(Eth_LinkDescTypeRsw2, ETH_VAR_NO_INIT) Eth_GaaLinkFixTable[ETH_RACE_AXI_CHAIN_N];

#if (ETH_GLOBAL_TIME_SUPPORT == STD_ON)
/* Timestamp descriptor chain */
extern VAR(Eth_TSDescType, ETH_VAR_NO_INIT) Eth_GaaTsDescChain[ETH_MAX_TS_DESCRIPTOR + ETH_CYCLIC_DESC_NUM];
#endif

extern VAR(uint8, ETH_VAR_NO_INIT)Eth_GaaMemPoolDesc[ETH_ETNE_CTRLS_SUPPORTED * \
                                            ((ETH_TXQ_NUM_RSW2 * (16UL + ((64UL + 1UL) * ETH_EXT_TX_DIR_DESC_SIZE))) + \
                                            (ETH_RXQ_NUM_RSW2 * (16UL + ((64UL + 1UL) * ETH_EXT_RX_ETH_DESC_SIZE))))];

#define ETH_STOP_SEC_VAR_CLEARED_DESCRIPTOR_32
#include "Eth_MemMap.h"

#define ETH_START_SEC_VAR_INIT_PTR
#include "Eth_MemMap.h"

#define ETH_STOP_SEC_VAR_INIT_PTR
#include "Eth_MemMap.h"

#define ETH_START_SEC_VAR_INIT_UNSPECIFIED
#include "Eth_MemMap.h"

/* Function pointer variable for OSTM Unit configuration */
extern VAR(Eth_HwFuncTableType, ETH_VAR_INIT) Eth_EtneFunc;

#define ETH_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Eth_MemMap.h"

#define ETH_START_SEC_VAR_CLEARED_USER_RAM_UNSPECIFIED
#include "Eth_MemMap.h"

extern VAR(uint32, ETH_VAR_NO_INIT) Eth_GaaRsw2PortCtrlIdx[ETH_RACE_PORT_N];

#define ETH_STOP_SEC_VAR_CLEARED_USER_RAM_UNSPECIFIED
#include "Eth_MemMap.h"

/*******************************************************************************
**                      Macro Defines                                         **
*******************************************************************************/


/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define ETH_START_SEC_PRIVATE_CODE
#include "Eth_MemMap.h" 
extern FUNC(void, ETH_PRIVATE_CODE) Eth_ETNE_InitializeBuffer(CONST(uint32, AUTOMATIC) LulCtrlIdx);
extern FUNC(void, ETH_PRIVATE_CODE) Eth_ETNE_PreprocessBuffer(CONST(uint32, AUTOMATIC) LulCtrlIdx);
extern FUNC(BufReq_ReturnType, ETH_PRIVATE_CODE) Eth_ETNE_GetTxBuffer(
                              CONST(uint32, AUTOMATIC) LulCtrlIdx,
                              CONST(uint8, AUTOMATIC) LucPriority,
                              CONSTP2VAR(Eth_BufIdxType, AUTOMATIC, ETH_APPL_DATA) LpBufIdxPtr,                         /* PRQA S 3432 # JV-01 */
                              CONSTP2VAR(uint8*, AUTOMATIC, ETH_APPL_DATA) LpBufPtr,                                    /* PRQA S 3432 # JV-01 */
                              CONSTP2VAR(uint16, AUTOMATIC, ETH_APPL_DATA) LenBytePtr);                                 /* PRQA S 3432 # JV-01 */
extern FUNC(void, ETH_PRIVATE_CODE) Eth_ETNE_ReleaseTxBuffer(
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulBufIdx);
extern FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_ETNE_CheckProvideBuffer(
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulBufIdx);
extern FUNC(void, ETH_PRIVATE_CODE) Eth_ETNE_PreprocessFrame(
                              CONST(uint32, AUTOMATIC) LulCtrlIdx,
                              CONST(uint32, AUTOMATIC) LulBufIdx,
                              CONST(uint32, AUTOMATIC) LulFrameType,
                              CONSTP2CONST(uint8, AUTOMATIC, ETH_APPL_DATA) LpPhysAddrPtr,
                              CONSTP2VAR(uint16, AUTOMATIC, ETH_APPL_DATA) LpPayloadLen);                               /* PRQA S 3432 # JV-01 */

extern FUNC(Eth_BufHandlerType *, ETH_PRIVATE_CODE) Eth_ETNE_FindTxBufferHandler(
  CONST(uint32, AUTOMATIC) LulCtrlIdx,
  CONST(uint32, AUTOMATIC) LulBufIdx);

#define ETH_STOP_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"
#endif /* ETH_RSW2_RAM_H  */
#endif /* ETH_MACRO_ETNE == STD_ON */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
