/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Eth.h                                                                                               */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains macros, ETH type definitions, structure data types and API function prototypes of ETH Driver    */
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
 *                        Update ETH_SW_MINOR_VERSION to 3
 * 2.2.0: 31/12/2024    : Update SW-VERSION for Ver22.02.00(D) U2Bx Final Release
 * 2.1.2: 31/10/2024    : Increase ETH_SW_PATCH_VERSION version to 2
 * 2.1.1: 30/08/2024    : Update QAC message
 *        01/06/2024    : Update ETH_SW_MAJOR_VERSION to 1
 *                      : Update ETH_SW_MINOR_VERSION to 1
 *                      : Update QAC message.
 *                      : Increase ETH_SW_PATCH_VERSION version
 *                      : Update Declaration from fix array size as 1 to unfix.
 *                      : Add defien ETH_MAINFUNCTION_SID, ETH_SETSTATUS_SID.
 *                      : Increase ETH_SW_PATCH_VERSION version
 *                        Add define of ETH_E_INVALID_CORE and ETH_INVALID_CORE macro
 *                            when ETH_MULTI_CORE_SUPPORT is STD_ON.
 *                        Add define ETH_ZERO constant.
 *                      : Remove QA-C Warning 1534
 *                      : Added QA-C warning 3684 according to QA-C 10.3.0
 * 2.1.0: 04/03/2024    : Update SW-VERSION to 2.1.0
 * 2.0.1: 18/10/2023    : Added QA-C Warning 1534 according to QA-C 10.3.0
 *                        Added QA-C 10.3.0 comments 
 *        13/10/2023    : Change FifoIdx to QueueIdx in Eth_Receive
 *        12/10/2023    : Change ETH_START_SEC_DBTOC_DATA_UNSPECIFIED to ETH_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
 *        11/10/2023    : Update ETH_SW_PATCH_VERSION to 1 and ETH_AR_VERSION to 4.8.0
 *        21/09/2023    : Add define ETH_GETSPISTATUS_SID
 * 2.0.0: 27/07/2023    : Add CWE rule into QAC header
 *        18/07/2023    : Remove redundant QA-C warning 0791
 *        27/06/2023    : Add Eth_GetSpiStatus API
 *        25/05/2023    : Add QA-C Warning 0791, 3432
 *                      : Change Eth_GetEgressTimeStamp and Eth_GetIngressTimeStamp to Std_ReturnType for R21_11.
 *                      : Change AR Version Name 
 *        20/05/2023    : Define ETH_E_COMMUNICATION 
 *        21/04/2023    : Update ETH_SW_MAJOR_VERSION to 2
 *                      : Update ETH_SW_MINOR_VERSION to 0
 * 1.6.0: 20/04/2023    : Update AUTOSAR release version information for R21-11
 *                      : Change precompile for Eth_GetEgressTimeStamp, Eth_GetIngressTimeStamp support R21-11
 *        03/03/2023    : Update ETH_SW_MINOR_VERSION to 6
 *                        Update ETH_SW_PATCH_VERSION to 0
 * 1.5.5: 09/12/2022    : Update ETH_SW_PATCH_VERSION to 5
 * 1.5.4: 26/07/2022    : Update ETH_SW_PATCH_VERSION to 4
 * 1.5.2: 04/03/2022    : Remove the prototype definition of Eth_MainFunction.
 * 1.5.1: 18/10/2021    : Change the memory section of the Eth_DemConfigCheck function to ETH_PRIVATE_CODE.
 *        12/01/2021    : Update QA-C 9.5.0 comments
 * 1.4.2: 24/08/2021    : Modify the format to 120 characters
 *        26/08/2021    : Updated QA-C 9.5.0 comments
 * 1.4.1: 24/06/2021    : Update Eth_GetEgressTimeStamp and Eth_GetIngressTimeStamp for R19-11 support.
 *      : 07/05/2021    : Remove vendor ID from the file name, API names
 *                        and parameters according to BSW00347 requirement
 *        09/06/2021    : Remove QA-C Warning 0791 and 3432 according to QA-C 9.5.0
 *                        Add QA-C Warning 3451
 *        06/07/2021    : Updated QA-C 9.5.0 comments.
 * 1.4.0: 19/04/2021    : Update Module Software version information
 * 1.3.0: 24/11/2020    : Update Module Software version information
 * 1.2.0: 13/07/2020    : Release
 *        29/07/2020    : Add QAC 9.3.1 comment.
 * 1.1.0: 19/06/2020    : Release
 * 1.0.1: 04/06/2020    : To support Transmit/Receive interrupts for each controller.
 *                        Re define ETH_59_E_UNINIT.
 *                        Change Module Software version information from macro to hard-code.
 *                        Changed the parameter of Eth_59_SetOffsetTimeForGptp.
 * 1.0.0: 25/03/2020    : Initial Version
 */
/**********************************************************************************************************************/

#ifndef ETH_H
#define ETH_H

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE Rule CWE-398, CWE-569                                            */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is accepted. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3451)    : An external object or function shall be declared once in one and only one file               */
/* Rule                : MISRA C:2012 Rule-8.5, CWE Rule CWE-398, CWE-569                                             */
/* JV-01 Justification : It does not affect the behavior of the driver.                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (7:0791)    : Macro identifier does not differ from other macro identifier(s) (e.g. '%s') within the       */
/*                       specified number of significant characters.                                                  */
/* Rule                : CERTCCM DCL23, MISRA C:2012 Rule-5.4                                                         */
/* JV-01 Justification : This macro identifier is following AUTOSAR standard rule (Symbolic Name or Published         */
/*                       Macro's name), so this is accepted.                                                          */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3684)    : Array declared with unknown size.                                                            */
/* Rule                : CERTCCM ARR02, MISRA C:2012 Rule-8.11                                                        */
/* JV-01 Justification : Arrays used are verified in the file which are only declarations and size is configuration   */
/*                       dependent.                                                                                   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* To publish the type ETH_ConfigType */
#include "Eth_Types.h"
#include "Eth_Common_LLDriver.h"
#include "Dem.h"
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* Module identifications */
#define ETH_VENDOR_ID              (uint8)ETH_VENDOR_ID_VALUE
#define ETH_MODULE_ID              (uint16)ETH_MODULE_ID_VALUE
#define ETH_INSTANCE_ID            (uint8)ETH_INSTANCE_ID_VALUE

/* AUTOSAR release version information */
#if (ETH_AR_VERSION == ETH_AR_431_VERSION)
#define ETH_AR_RELEASE_MAJOR_VERSION    4U
#define ETH_AR_RELEASE_MINOR_VERSION    3U
#define ETH_AR_RELEASE_REVISION_VERSION 1U
#elif (ETH_AR_VERSION == ETH_AR_R21_11_VERSION)
#define ETH_AR_RELEASE_MAJOR_VERSION    4U
#define ETH_AR_RELEASE_MINOR_VERSION    7U
#define ETH_AR_RELEASE_REVISION_VERSION 0U
#elif (ETH_AR_VERSION == ETH_AR_R22_11_VERSION)
#define ETH_AR_RELEASE_MAJOR_VERSION    4U
#define ETH_AR_RELEASE_MINOR_VERSION    8U
#define ETH_AR_RELEASE_REVISION_VERSION 0U
#else
#define ETH_AR_RELEASE_MAJOR_VERSION    4U
#define ETH_AR_RELEASE_MINOR_VERSION    2U
#define ETH_AR_RELEASE_REVISION_VERSION 2U
#endif

/* Module Software version information */
#define ETH_SW_MAJOR_VERSION            2U
#define ETH_SW_MINOR_VERSION            4U
#define ETH_SW_PATCH_VERSION            1U

/***********************************************************************************************************************
**                                               API Service Id Macros                                                **
***********************************************************************************************************************/
/* Service Id of Eth_Init */
#define ETH_INIT_SID                    (uint8)0x01U
/* Service Id of Eth_SetControllerMode */
#define ETH_SETCONTROLLERMODE_SID       (uint8)0x03U
/* Service Id of Eth_GetControllerMode */
#define ETH_GETCONTROLLERMODE_SID       (uint8)0x04U
/* Service Id of Eth_WriteMii */
#define ETH_WRITEMII_SID                (uint8)0x05U
/* Service Id of Eth_ReadMii */
#define ETH_READMII_SID                 (uint8)0x06U
/* Service Id of Eth_GetPhysAddr */
#define ETH_GETPHYSADDR_SID             (uint8)0x08U
/* Service Id of Eth_ProvideTxBuffer */
#define ETH_PROVIDETXBUFFER_SID         (uint8)0x09U
/* Service Id of Eth_Transmit */
#define ETH_TRANSMIT_SID                (uint8)0x0AU
/* Service Id of Eth_Receive */
#define ETH_RECEIVE_SID                 (uint8)0x0BU
/* Service Id of Eth_TxConfirmation */
#define ETH_TXCONFIRMATION_SID          (uint8)0x0CU
/* Service Id of Eth_GetVersionInfo */
#define ETH_GET_VERSION_INFO_SID        (uint8)0x0DU
/* Service Id of Eth_UpdatePhysAddrFilter */
#define ETH_UPDATEPHYSADDRFILTER_SID    (uint8)0x12U
/* Service Id of Eth_SetPhysAddr */
#define ETH_SETPHYSADDR_SID             (uint8)0x13U
/* Service Id of Eth_GetDropCount */
#define ETH_GETDROPCOUNT_SID            (uint8)0x14U
/* Service Id of Eth_GetCounterValues */
#define ETH_GETCOUNTERVALUES_SID        (uint8)0x14U
/* Service Id of Eth_GetEtherStats */
#define ETH_GETETHERSTATS_SID           (uint8)0x15U
/* Service Id of Eth_GetRxStats */
#define ETH_GETRXSTATS_SID              (uint8)0x15U
/* Service Id of Eth_GetTxStats */
#define ETH_GETTXSTATS_SID              (uint8)0x1CU
/* Service Id of Eth_GetTxErrorCounterValues */
#define ETH_GETTXERRORCOUNTERVALUES_SID (uint8)0x1DU
/* Service Id of Eth_GetSpiStatus */
#define ETH_GETSPISTATUS_SID            (uint8)0x1EU

/*********gPTP TimeStamp Apis *****************/
/* Service Id of Eth_GetCurrentTime */
#define ETH_GETCURRENTTIME_SID          (uint8)0x16U

/* Service Id of Eth_EnableEgressTimeStamp  */
#define ETH_ENEGRESSTS_SID              (uint8)0x17U

/* Service Id of Eth_GetEgressTimeStamp  */
#define ETH_GETEGRESSTS_SID             (uint8)0x18U

/* Service Id of Eth_GetIngressTimeStamp  */
#define ETH_GETINGRESSTS_SID            (uint8)0x19U

/* Service Id of Eth_SetCorrectionTime  */
#define ETH_SETCORRECTIONTIME_SID       (uint8)0x1AU

/* Service Id of Eth_SetGlobalTime  */
#define ETH_SETGLOBALTIME_SID           (uint8)0x1BU

/* Service Id of Eth_MainFunction  */
#define ETH_MAINFUNCTION_SID            (uint8)0x20U

/* Service Id of Eth_SetStatus  */
#define ETH_SETSTATUS_SID               (uint8)0xFFU

/* Service Id of Eth_UpdateStreamFilter */
#define ETH_UPDATESTREAMFILTER_SID      (uint8)0xA0U

#if (ETH_GLOBAL_TIME_SUPPORT == STD_ON && ETH_AR_VERSION >= ETH_AR_431_VERSION)
/* Service Id of Eth_SetIncrementTimeForGptp */
#define ETH_SETINCREMENTTIMEFORGPTP_SID (uint8)0xA1U

/* Service Id of Eth_SetOffsetTimeForGptp */
#define ETH_SETOFFSETTIMEFORGPTP_SID    (uint8)0xA2U
#endif

#if (ETH_DEINIT_API == STD_ON)
/* Service Id of Eth_DeInit */
#define ETH_DEINIT_SID                  (uint8)0xA3U
#endif

/***********************************************************************************************************************
**                                                  DET Error Codes                                                   **
***********************************************************************************************************************/
/* Invalid controller index */
#define ETH_E_INV_CTRL_IDX              (uint8)0x01U

#if (ETH_AR_VERSION >= ETH_AR_431_VERSION)
/* Eth module or controller was not initialized */
#define ETH_E_UNINIT                    (uint8)0x02U
#else
/* Definition of ETH_E_NOT_INITIALIZED is kept in AR4.2.2 to prevent any issue while integration. */
#define ETH_E_UNINIT                    ETH_E_NOT_INITIALIZED
#define ETH_E_NOT_INITIALIZED           (uint8)0x02U
#endif

/* Invalid pointer in parameter list. */
#define ETH_E_PARAM_POINTER             (uint8)0x03U

/* A wrong parameter passed to the APIs */
#define ETH_E_INV_PARAM                 (uint8)0x04U

/* Invalid mode */
#define ETH_E_INV_MODE                  (uint8)0x05U

/* Failure or incorrect communication with the Ethernet Controller */
#define ETH_E_COMMUNICATION             (uint8)0x06U

/* When valid Database is not available */
#define ETH_E_INVALID_DATABASE          (uint8)0xEFU
/* DET Error - Call in invalid core */
#if (ETH_MULTI_CORE_SUPPORT == STD_ON)
#define ETH_E_INVALID_CORE              (uint8)0xF1U
#endif /* #if (ETH_MULTI_CORE_SUPPORT == STD_ON) */
/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/
/* ETH_ZERO constant */
#define ETH_ZERO                        (uint8)0x00U

/* ETH_INVALID_CORE constant */
#if (ETH_MULTI_CORE_SUPPORT == STD_ON)
#define ETH_INVALID_CORE                (uint8)0xFFU
#endif /* #if (ETH_MULTI_CORE_SUPPORT == STD_ON) */

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/

#define ETH_START_SEC_PUBLIC_CODE
#include "Eth_MemMap.h"

extern FUNC(void, ETH_PUBLIC_CODE) Eth_Init(P2CONST(Eth_ConfigType, AUTOMATIC, ETH_APPL_CONST) CfgPtr);
#if (ETH_DEINIT_API == STD_ON)
extern FUNC(Std_ReturnType, ETH_PUBLIC_CODE) Eth_DeInit(CONST(boolean, AUTOMATIC) ForceReset);
#endif
extern FUNC(Std_ReturnType, ETH_PUBLIC_CODE) Eth_SetControllerMode(uint8 CtrlIdx, Eth_ModeType CtrlMode);

extern FUNC(Std_ReturnType, ETH_PUBLIC_CODE)
    Eth_GetControllerMode(uint8 CtrlIdx,
                          P2VAR(Eth_ModeType, AUTOMATIC, ETH_APPL_DATA) CtrlModePtr);                                   /* PRQA S 3432 # JV-01 */

extern FUNC(void, ETH_PUBLIC_CODE)
    Eth_GetPhysAddr(uint8 CtrlIdx, P2VAR(uint8, AUTOMATIC, ETH_APPL_DATA) PhysAddrPtr);                                 /* PRQA S 3432 # JV-01 */

extern FUNC(void, ETH_PUBLIC_CODE) Eth_SetPhysAddr(uint8 CtrlIdx, P2CONST(uint8, AUTOMATIC, ETH_APPL_DATA) PhysAddrPtr);

#if (ETH_UPDATE_PHYS_ADDR_FILTER == STD_ON)
extern FUNC(Std_ReturnType, ETH_PUBLIC_CODE)
    Eth_UpdatePhysAddrFilter(uint8 CtrlIdx, P2CONST(uint8, AUTOMATIC, ETH_APPL_DATA) PhysAddrPtr,
                             Eth_FilterActionType Action);
#endif

#if (ETH_CTRL_ENABLE_MII == STD_ON)
extern FUNC(Std_ReturnType, ETH_PUBLIC_CODE) Eth_WriteMii(uint8 CtrlIdx, uint8 TrcvIdx, uint8 RegIdx, uint16 RegVal);

extern FUNC(Std_ReturnType, ETH_PUBLIC_CODE)
    Eth_ReadMii(uint8 CtrlIdx, uint8 TrcvIdx, uint8 RegIdx,
                P2VAR(uint16, AUTOMATIC, ETH_APPL_DATA) RegValPtr);                                                     /* PRQA S 3432 # JV-01 */
#endif

#if (ETH_GET_DROP_COUNT_API == STD_ON)
extern FUNC(Std_ReturnType, ETH_PUBLIC_CODE)
    Eth_GetDropCount(uint8 CtrlIdx, uint8 CountValues,
                     P2VAR(uint32, AUTOMATIC, ETH_APPL_DATA) DropCount);                                                
#endif

#if (ETH_GET_COUNTER_VALUES_API == STD_ON)
extern FUNC(Std_ReturnType, ETH_PUBLIC_CODE)
    Eth_GetCounterValues(uint8 CtrlIdx,
                         P2VAR(Eth_CounterType, AUTOMATIC, ETH_APPL_DATA) CounterPtr);                                  /* PRQA S 3432 # JV-01 */
#endif

#if (ETH_GET_ETHER_STATS_API == STD_ON)
FUNC(Std_ReturnType, ETH_PUBLIC_CODE)
    Eth_GetEtherStats(uint8 CtrlIdx, P2VAR(uint32, AUTOMATIC, ETH_APPL_DATA) etherStats);                               
#endif

#if (ETH_GET_RX_STATS_API == STD_ON)
FUNC(Std_ReturnType, ETH_PUBLIC_CODE)
    Eth_GetRxStats(uint8 CtrlIdx, P2VAR(Eth_RxStatsType, AUTOMATIC, ETH_APPL_DATA) RxStats);                            /* PRQA S 3432 # JV-01 */
#endif

#if (ETH_GET_TX_STATS_API == STD_ON)
FUNC(Std_ReturnType, ETH_PUBLIC_CODE)
    Eth_GetTxStats(uint8 CtrlIdx, P2VAR(Eth_TxStatsType, AUTOMATIC, ETH_APPL_DATA) TxStats);                            /* PRQA S 3432 # JV-01 */
#endif

#if (ETH_GET_TX_ERROR_COUNTER_VALUES_API == STD_ON)
FUNC(Std_ReturnType, ETH_PUBLIC_CODE)
    Eth_GetTxErrorCounterValues(uint8 CtrlIdx,
                                P2VAR(Eth_TxErrorCounterValuesType, AUTOMATIC, ETH_APPL_DATA) TxErrorCounterValues);    /* PRQA S 3432 # JV-01 */
#endif

extern FUNC(BufReq_ReturnType, ETH_PUBLIC_CODE)
    Eth_ProvideTxBuffer(uint8 CtrlIdx,
#if (ETH_AR_VERSION >= ETH_AR_431_VERSION)
                        uint8 Priority,
#endif
                        P2VAR(Eth_BufIdxType, AUTOMATIC, ETH_APPL_DATA) BufIdxPtr,                                      /* PRQA S 3432 # JV-01 */
                        P2VAR(P2VAR(uint8, AUTOMATIC, ETH_APPL_DATA), AUTOMATIC, ETH_APPL_DATA) BufPtr,                 /* PRQA S 3432 # JV-01 */
                        P2VAR(uint16, AUTOMATIC, ETH_APPL_DATA) LenBytePtr);                                            /* PRQA S 3432 # JV-01 */

extern FUNC(Std_ReturnType, ETH_PUBLIC_CODE)
    Eth_Transmit(uint8 CtrlIdx, Eth_BufIdxType BufIdx, Eth_FrameType FrameType, boolean TxConfirmation, uint16 LenByte,
                 P2CONST(uint8, AUTOMATIC, ETH_APPL_DATA) PhysAddrPtr);

#if (ETH_CTRL_ENABLE_RX_POLLING == STD_ON)
extern FUNC(void, ETH_PUBLIC_CODE)
    Eth_Receive(uint8 CtrlIdx,
#if (ETH_AR_VERSION >= ETH_AR_431_VERSION)
                uint8 QueueIdx,
#endif
                P2VAR(Eth_RxStatusType, AUTOMATIC, ETH_APPL_DATA) RxStatusPtr);                                         /* PRQA S 3432 # JV-01 */
#endif

#if (ETH_CTRL_ENABLE_TX_POLLING == STD_ON)
extern FUNC(void, ETH_PUBLIC_CODE) Eth_TxConfirmation(uint8 CtrlIdx);
#endif

#if (ETH_VERSION_INFO_API == STD_ON)
extern FUNC(void, ETH_PUBLIC_CODE)
    Eth_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, ETH_APPL_DATA) VersionInfoPtr);                            /* PRQA S 3432 # JV-01 */
#endif

#if (ETH_GLOBAL_TIME_SUPPORT == STD_ON)
extern FUNC(Std_ReturnType, ETH_PUBLIC_CODE)
    Eth_GetCurrentTime(uint8 CtrlIdx,
                       P2VAR(Eth_TimeStampQualType, AUTOMATIC, ETH_APPL_DATA) timeQualPtr,                              /* PRQA S 3432 # JV-01 */
                       P2VAR(Eth_TimeStampType, AUTOMATIC, ETH_APPL_DATA) timeStampPtr);                                /* PRQA S 3432 # JV-01 */

extern FUNC(void, ETH_PUBLIC_CODE) Eth_EnableEgressTimeStamp(uint8 CtrlIdx, Eth_BufIdxType BufIdx);

#if (ETH_AR_VERSION >= ETH_AR_R19_11_VERSION)
extern FUNC(Std_ReturnType, ETH_PUBLIC_CODE)
    Eth_GetEgressTimeStamp(uint8 CtrlIdx, Eth_BufIdxType BufIdx,
                           P2VAR(Eth_TimeStampQualType, AUTOMATIC, ETH_APPL_DATA) timeQualPtr,                          /* PRQA S 3432 # JV-01 */
                           P2VAR(Eth_TimeStampType, AUTOMATIC, ETH_APPL_DATA) timeStampPtr);                            /* PRQA S 3432 # JV-01 */
#else
extern FUNC(void, ETH_PUBLIC_CODE)
    Eth_GetEgressTimeStamp(uint8 CtrlIdx, Eth_BufIdxType BufIdx,
                           P2VAR(Eth_TimeStampQualType, AUTOMATIC, ETH_APPL_DATA) timeQualPtr,                          
                           P2VAR(Eth_TimeStampType, AUTOMATIC, ETH_APPL_DATA) timeStampPtr);                            
#endif

#if (ETH_AR_VERSION >= ETH_AR_R19_11_VERSION)
extern FUNC(Std_ReturnType, ETH_PUBLIC_CODE)
    Eth_GetIngressTimeStamp(uint8 CtrlIdx, P2CONST(Eth_DataType, AUTOMATIC, ETH_APPL_DATA) DataPtr,
                            P2VAR(Eth_TimeStampQualType, AUTOMATIC, ETH_APPL_DATA) timeQualPtr,                         /* PRQA S 3432 # JV-01 */
                            P2VAR(Eth_TimeStampType, AUTOMATIC, ETH_APPL_DATA) timeStampPtr);                           /* PRQA S 3432 # JV-01 */
#else
extern FUNC(void, ETH_PUBLIC_CODE)
    Eth_GetIngressTimeStamp(uint8 CtrlIdx, P2CONST(Eth_DataType, AUTOMATIC, ETH_APPL_DATA) DataPtr,
                            P2VAR(Eth_TimeStampQualType, AUTOMATIC, ETH_APPL_DATA) timeQualPtr,                         
                            P2VAR(Eth_TimeStampType, AUTOMATIC, ETH_APPL_DATA) timeStampPtr);                           
#endif

extern FUNC(void, ETH_PUBLIC_CODE)
    Eth_SetCorrectionTime(uint8 CtrlIdx, P2CONST(Eth_TimeIntDiffType, AUTOMATIC, ETH_APPL_DATA) timeOffsetPtr,
                          P2CONST(Eth_RateRatioType, AUTOMATIC, ETH_APPL_DATA) rateRatioPtr);

extern FUNC(Std_ReturnType, ETH_PUBLIC_CODE)
    Eth_SetGlobalTime(uint8 CtrlIdx, P2CONST(Eth_TimeStampType, AUTOMATIC, ETH_APPL_DATA) timeStampPtr);

#if (ETH_AR_VERSION >= ETH_AR_431_VERSION)
extern FUNC(Std_ReturnType, ETH_PUBLIC_CODE)
    Eth_SetIncrementTimeForGptp(CONST(uint8, AUTOMATIC) CtrlIdx, CONST(uint32, AUTOMATIC) IncVal);

extern FUNC(Std_ReturnType, ETH_PUBLIC_CODE)
    Eth_SetOffsetTimeForGptp(CONST(uint8, AUTOMATIC) CtrlIdx,
                             CONSTP2CONST(Eth_TimeStampType, AUTOMATIC, ETH_APPL_DATA) pTimeOffsetPtr);
#endif
#endif

#if (ETH_STREAM_FILTERING == STD_ON)
extern FUNC(Std_ReturnType, ETH_PUBLIC_CODE)
    Eth_UpdateStreamFilter(CONST(uint8, AUTOMATIC) CtrlIdx, CONST(uint8, AUTOMATIC) QueIdx,
                           CONSTP2CONST(uint8, AUTOMATIC, ETH_APPL_DATA) StreamIdPtr);
#endif

#if (ETH_CTRL_ENABLE_SPI_INTERFACE_API == STD_ON)
extern FUNC(Std_ReturnType, ETH_PUBLIC_CODE) Eth_GetSpiStatus(
    CONST(uint8, AUTOMATIC) CtrlIdx, P2VAR(Eth_SpiStatusType, AUTOMATIC, ETH_APPL_DATA) SpiStatusType);                 /* PRQA S 3432 # JV-01 */
#endif

#define ETH_STOP_SEC_PUBLIC_CODE
#include "Eth_MemMap.h"

#define ETH_START_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"

extern FUNC(void, ETH_PRIVATE_CODE)
    Eth_DemConfigCheck(CONST(Dem_EventIdType, AUTOMATIC) EventId, CONST(Dem_EventStatusType, AUTOMATIC) EventStatus);

#define ETH_STOP_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"

#define ETH_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Eth_MemMap.h"

/* Declaration for ETH Database */
/* Multiple configuration is not supported */
extern CONST(Eth_ConfigType, ETH_CONST) Eth_GaaConfiguration[];                                                         /* PRQA S 3684 # JV-01 */

/* Array of structures for HW-IP Configuration */
extern CONST(Eth_HWIPType, ETH_CONST) Eth_GaaHWIP[];                                                                    /* PRQA S 3684 # JV-01 */

#define ETH_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Eth_MemMap.h"

#endif /* ETH_H */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
