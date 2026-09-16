/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Eth_Ram.h                                                                                           */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2023 - 2025 Renesas Electronics Corporation. All rights reserved.                                              */
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
 * 2.4.0: 30/06/2025    : Update SW-VERSION for RH850/Ver22.01.00 (D) U2Ax release
 * 2.3.1: 31/03/2025    : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 * 2.3.0: 28/02/2025    : Updated QA-C 9.5.0 comments
 * 2.2.0: 31/12/2024    : Update SW-VERSION for Ver22.02.00(D) U2Bx Final Release
 *        26/11/2024    : Updated QA-C 9.5.0 comments
 * 2.1.2: 31/10/2024    : Increase SW-VERSION to 2.1.2
 * 2.1.1: 16/07/2024    : Add Eth_GpDemEventUnintendedIntChk
 *        01/06/2024    : Add Eth_GaaRxBufferIndex
 * 2.0.2: 17/04/2024    : Update QAC message.
 *        15/04/2024    : Remove declare of Eth_GaaGetCoreId2Index, Eth_GenDriverState
 *                        Add declare of Eth_GpCoreId2Index, Eth_GpDriverState, Eth_GpTotalCtrlConfig, Eth_CtrlConfigIdx
 *        28/03/2024    : Add declare of Eth_GpDemEventAccess, Eth_GpDemEventRxFramesLost, Eth_GpDemEventCRC,
 *                        Eth_GpDemEventUnderSizeFrame, Eth_GpDemEventOverSizeFrame, Eth_GpDemEventAlignment,
 *                        Eth_GpDemEventSinglecollision, Eth_GpDemEventMultiplecollision, Eth_GpDemEventLatecollision,
 *                        Eth_GpDemEventIntInconsistent, Eth_GpDemEventDmaError, Eth_GpDemEventEccError,
 *                        Eth_GpDemEventTimerincFailed, Eth_GpDemEventRegisterCorruption,
 *                        Eth_GpDemEventTimeroffsetFailed.
 *        18/03/2024    : Add declare of Eth_GaaGetCoreId2Index global variable.
 *                      : Convert declare of Eth_GenDriverState variable from variable to array variable.
 *        12/12/2023    : Added QA-C warning 3684 according to QA-C 10.3.0
 *        20/11/2023    : Initial Version
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
/* Message (2:3684)    : Array declared with unknown size.                                                            */
/* Rule                : CERTCCM ARR02, MISRA C:2012 Rule-8.11                                                        */
/* JV-01 Justification : Arrays used are verified in the file which are only declarations and size is configuration   */
/*                       dependent.                                                                                   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/**********************************************************************************************************************/
#ifndef ETH_RAM_H
#define ETH_RAM_H
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
/* AUTOSAR release version information */
#define ETH_RAM_AR_RELEASE_MAJOR_VERSION    ETH_AR_RELEASE_MAJOR_VERSION
#define ETH_RAM_AR_RELEASE_MINOR_VERSION    ETH_AR_RELEASE_MINOR_VERSION
#define ETH_RAM_AR_RELEASE_REVISION_VERSION ETH_AR_RELEASE_REVISION_VERSION

/* Module Software version information */
#define ETH_RAM_SW_MAJOR_VERSION            ETH_SW_MAJOR_VERSION
#define ETH_RAM_SW_MINOR_VERSION            ETH_SW_MINOR_VERSION
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

#if (ETH_MULTI_CORE_SUPPORT == STD_ON)
#define ETH_START_SEC_CONST_8
#include "Eth_MemMap.h"
/* Global variable to store core index */
extern P2CONST(uint8, ETH_VAR_INIT, ETH_CONFIG_CONST) Eth_GpCoreId2Index;

#define ETH_STOP_SEC_CONST_8
#include "Eth_MemMap.h"
#endif

#define ETH_START_SEC_VAR_NO_INIT_32
#include "Eth_MemMap.h"

extern VAR(Eth_BufIdxType, ETH_VAR_NO_INIT) Eth_GaaRxBufferIndex[ETH_TOTAL_CTRL_CONFIG];

extern VAR(Eth_RxFrameType, ETH_VAR_NO_INIT) Eth_GaaRxFrame[ETH_TOTAL_CTRL_CONFIG];

#define ETH_STOP_SEC_VAR_NO_INIT_32
#include "Eth_MemMap.h"

#define ETH_START_SEC_VAR_NO_INIT_PTR
#include "Eth_MemMap.h"

extern P2VAR(void, ETH_VAR_FAST_NO_INIT, ETH_VAR_FAST_NO_INIT) Eth_GaaHeap[ETH_TOTAL_CTRL_CONFIG];

/* Global variable to store pointer to Configuration */
extern P2CONST(Eth_CtrlConfigType, ETH_CONST, ETH_CONFIG_CONST) volatile Eth_GpCtrlConfigPtr;

extern P2CONST(Eth_EthConfigType, ETH_CONST, ETH_CONFIG_CONST) volatile Eth_GpEthConfigPtr;

#define ETH_STOP_SEC_VAR_NO_INIT_PTR
#include "Eth_MemMap.h"

#define ETH_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Eth_MemMap.h"

extern VAR(Eth_MacAddressType, ETH_VAR_NO_INIT) Eth_GaaAddressFilters[ETH_TOTAL_CTRL_CONFIG][ETH_MAX_FILTERS];

extern VAR(Eth_ControllerStatusType, ETH_VAR_NO_INIT) Eth_GaaCtrlStat[ETH_TOTAL_CTRL_CONFIG];

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

extern P2VAR(uint16, ETH_VAR_INIT, ETH_VAR_INIT) Eth_GpDemEventAccess;                                                  /* PRQA S 3432 # JV-01 */

extern P2VAR(uint16, ETH_VAR_INIT, ETH_VAR_INIT) Eth_GpDemEventRxFramesLost;                                            /* PRQA S 3432 # JV-01 */

extern P2VAR(uint16, ETH_VAR_INIT, ETH_VAR_INIT) Eth_GpDemEventCRC;                                                     /* PRQA S 3432 # JV-01 */

extern P2VAR(uint16, ETH_VAR_INIT, ETH_VAR_INIT) Eth_GpDemEventUnderSizeFrame;                                          /* PRQA S 3432 # JV-01 */

extern P2VAR(uint16, ETH_VAR_INIT, ETH_VAR_INIT) Eth_GpDemEventOverSizeFrame;                                           /* PRQA S 3432 # JV-01 */

extern P2VAR(uint16, ETH_VAR_INIT, ETH_VAR_INIT) Eth_GpDemEventAlignment;                                               /* PRQA S 3432 # JV-01 */

extern P2VAR(uint16, ETH_VAR_INIT, ETH_VAR_INIT) Eth_GpDemEventSinglecollision;                                         /* PRQA S 3432 # JV-01 */

extern P2VAR(uint16, ETH_VAR_INIT, ETH_VAR_INIT) Eth_GpDemEventMultiplecollision;                                       /* PRQA S 3432 # JV-01 */

extern P2VAR(uint16, ETH_VAR_INIT, ETH_VAR_INIT) Eth_GpDemEventLatecollision;                                           /* PRQA S 3432 # JV-01 */

#if ( ETH_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
extern P2VAR(uint16, ETH_VAR_INIT, ETH_VAR_INIT) Eth_GpDemEventIntInconsistent;                                         /* PRQA S 3432 # JV-01 */
#endif

extern P2VAR(uint16, ETH_VAR_INIT, ETH_VAR_INIT) Eth_GpDemEventDmaError;                                                /* PRQA S 3432 # JV-01 */

extern P2VAR(uint16, ETH_VAR_INIT, ETH_VAR_INIT) Eth_GpDemEventEccError;                                                /* PRQA S 3432 # JV-01 */

#if (ETH_MACRO_ETNB == STD_ON || ETH_MACRO_ETNF ==STD_ON)
#if (ETH_GLOBAL_TIME_SUPPORT == STD_ON)
extern P2VAR(uint16, ETH_VAR_INIT, ETH_VAR_INIT) Eth_GpDemEventTimerincFailed;                                          /* PRQA S 3432 # JV-01 */

extern P2VAR(uint16, ETH_VAR_INIT, ETH_VAR_INIT) Eth_GpDemEventTimeroffsetFailed;                                       /* PRQA S 3432 # JV-01 */
#endif
#if ((ETH_REGISTER_CHECK_INITTIME == STD_ON) || (ETH_REGISTER_CHECK_RUNTIME == STD_ON))
extern P2VAR(uint16, ETH_VAR_INIT, ETH_VAR_INIT) Eth_GpDemEventRegisterCorruption;                                      /* PRQA S 3432 # JV-01 */
#endif
#endif

#if (ETH_MACRO_ETNE == STD_ON)
#if (ETH_UNINTENDED_INTERRUPT_CHECK == STD_ON)
extern P2VAR(uint16, ETH_VAR_INIT, ETH_VAR_INIT) Eth_GpDemEventUnintendedIntChk;                                        /* PRQA S 3432 # JV-01 */
#endif
#endif

#define ETH_STOP_SEC_VAR_INIT_16
#include "Eth_MemMap.h"

#define ETH_START_SEC_VAR_INIT_32
#include "Eth_MemMap.h"

#define ETH_STOP_SEC_VAR_INIT_32
#include "Eth_MemMap.h"

#define ETH_START_SEC_VAR_INIT_PTR
#include "Eth_MemMap.h"
/* Function pointer variable for ETN# configuration */
extern P2CONST(Eth_HwFuncTableType, ETH_VAR_INIT, ETH_CONFIG_DATA) Eth_GaaHwFunc[];                                     /* PRQA S 3684 # JV-01 */
#define ETH_STOP_SEC_VAR_INIT_PTR
#include "Eth_MemMap.h"

#define ETH_START_SEC_VAR_INIT_UNSPECIFIED
#include "Eth_MemMap.h"

extern P2VAR(Eth_StateType, ETH_VAR_INIT, ETH_VAR_INIT) Eth_GpDriverState;                                              /* PRQA S 3432 # JV-01 */
#define ETH_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Eth_MemMap.h"

#define ETH_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Eth_MemMap.h"
extern P2CONST(uint32, ETH_VAR_INIT, ETH_CONFIG_DATA) Eth_GpTotalCtrlConfig;
extern uint32 Eth_CtrlConfigIdx[ETH_TOTAL_CORE_CONFIG][ETH_MAX_CTRL_CONFIG_PER_CODE];
#define ETH_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Eth_MemMap.h"

/***********************************************************************************************************************
**                                                   Macro Defines                                                    **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/
#define ETH_START_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"

#define ETH_STOP_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"
#endif /* ETH_ETNF_RAM_H  */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
