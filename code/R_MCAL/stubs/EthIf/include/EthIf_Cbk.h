/*============================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                         */
/* Module       = EthIf_Cbk.h                                                 */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2023-2025 Renesas Electronics Corporation. All rights reserved.        */
/*============================================================================*/
/* Purpose:                                                                   */
/* This file is a stub for EthIf Component                                    */
/*                                                                            */
/*============================================================================*/
/*                                                                            */
/* Unless otherwise agreed upon in writing between your company and           */
/* Renesas Electronics Corporation the following shall apply!                 */
/*                                                                            */
/* Warranty Disclaimer                                                        */
/*                                                                            */
/* There is no warranty of any kind whatsoever granted by Renesas. Any        */
/* warranty is expressly disclaimed and excluded by Renesas, either expressed */
/* or implied, including but not limited to those for non-infringement of     */
/* intellectual property, merchantability and/or fitness for the particular   */
/* purpose.                                                                   */
/*                                                                            */
/* Renesas shall not have any obligation to maintain, service or provide bug  */
/* fixes for the supplied Product(s) and/or the Application.                  */
/*                                                                            */
/* Each User is solely responsible for determining the appropriateness of     */
/* using the Product(s) and assumes all risks associated with its exercise    */
/* of rights under this Agreement, including, but not limited to the risks    */
/* and costs of program errors, compliance with applicable laws, damage to    */
/* or loss of data, programs or equipment, and unavailability or              */
/* interruption of operations.                                                */
/*                                                                            */
/* Limitation of Liability                                                    */
/*                                                                            */
/* In no event shall Renesas be liable to the User for any incidental,        */
/* consequential, indirect, or punitive damage (including but not limited     */
/* to lost profits) regardless of whether such liability is based on breach   */
/* of contract, tort, strict liability, breach of warranties, failure of      */
/* essential purpose or otherwise and even if advised of the possibility of   */
/* such damages. Renesas shall not be liable for any services or products     */
/* provided by third party vendors, developers or consultants identified or   */
/* referred to the User by Renesas in connection with the Product(s) and/or   */
/* the Application.                                                           */
/*                                                                            */
/*============================================================================*/
/* Environment:                                                               */
/*              Devices:        X2x                                           */
/*============================================================================*/

/*******************************************************************************
**                      Revision History                                      **
*******************************************************************************/
/*
 * 2.4.1      30/06/2025     Remove the SW-VERSION from header of file
 * 2.4.0      30/06/2025     Update SW-VERSION for RH850/Ver22.01.00 (D) U2Ax Release
 * 2.3.1      31/03/2025     Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02 Release
 * 2.2.0      31/12/2024     Update SW-VERSION for Ver22.02.00(D) U2Bx Final Release
 * 2.1.2      31/10/2024     Update SW-VERSION to 2.1.2
 * 2.1.1      24/07/2024     Update SW-VERSION to 2.1.1
 * 2.1.0      01/06/2024     Update SW-VERSION to 2.1.0
 *                           Add declared of variable when supporting multicore.
 * 2.0.1      22/09/2023     Initial Version
 */
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#ifndef ETHIF_CBK_H
#define ETHIF_CBK_H

/* Eth Driver Header File */
#include "EthIf_Types.h"
#ifdef CAN_MODULE_SAMPLE
  #include "CanXL.h"
#else
  #include "Eth.h"
#endif
/*******************************************************************************
**                         Global Data                                        **
*******************************************************************************/
#ifdef ETH_MODULE_SAMPLE
#define GLOBAL_TIME_SUPPORT ETH_GLOBAL_TIME_SUPPORT 
#elif (defined CAN_MODULE_SAMPLE)
	#define ETH_MULTI_CORE_SUPPORT STD_OFF
  #if defined CAN_CANXL_GLOBAL_TIME_SUPPORT
    #define GLOBAL_TIME_SUPPORT CAN_CANXL_GLOBAL_TIME_SUPPORT
  #else
    #define GLOBAL_TIME_SUPPORT   STD_OFF
  #endif
#endif 
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/
#if (ETH_MULTI_CORE_SUPPORT == STD_ON)
/* The instances are declared in the sample program */
extern volatile uint8 GaaRxEthFrame_0[2][1522];
extern volatile uint8 GaaRxSrcAddr_0[2][6];
extern volatile Eth_FrameType GusRxFrameType_0[2];
extern volatile uint16 GusRxLenByte_0[2];
extern volatile uint16 GusRxFrameCnt_0[2];
extern volatile uint8 GucTxConfirmed_0[2];
extern volatile uint16 GusMsgLength_0[2];
#if (GLOBAL_TIME_SUPPORT == STD_ON)
extern Eth_TimeStampQualType TxTimeQual_0;
extern Eth_TimeStampType TxTimeStamp_0[2];
#endif
extern volatile uint8 EthPassedCount_0[70];
extern volatile uint8 EthCheckCount_0;

/* The instances are declared in the sample program */
extern volatile uint8 GaaRxEthFrame_1[2][1522];
extern volatile uint8 GaaRxSrcAddr_1[2][6];
extern volatile Eth_FrameType GusRxFrameType_1[2];
extern volatile uint16 GusRxLenByte_1[2];
extern volatile uint16 GusRxFrameCnt_1[2];
extern volatile uint8 GucTxConfirmed_1[2];
extern volatile uint16 GusMsgLength_1[2];
#if (GLOBAL_TIME_SUPPORT == STD_ON)
extern Eth_TimeStampQualType TxTimeQual_1;
extern Eth_TimeStampType TxTimeStamp_1[2];
#endif
extern volatile uint8 EthPassedCount_1[70];
extern volatile uint8 EthCheckCount_1;

#else
/* The instances are declared in the sample program */
extern volatile uint8 GaaRxEthFrame[2][1522];
extern volatile uint8 GaaRxSrcAddr[2][6];
extern volatile Eth_FrameType GusRxFrameType[2];
extern volatile uint16 GusRxLenByte[2];
extern volatile uint16 GusRxFrameCnt[2];
extern volatile uint8 GucTxConfirmed[2];
extern volatile uint16 GusMsgLength[2];

#if (GLOBAL_TIME_SUPPORT == STD_ON)
extern Eth_TimeStampQualType TxTimeQual;
extern Eth_TimeStampType TxTimeStamp[2];
#endif
extern volatile uint8 EthPassedCount[70];
extern volatile uint8 EthCheckCount;
#endif

#ifdef CAN_MODULE_SAMPLE
#if (GLOBAL_TIME_SUPPORT == STD_ON)
#if (CAN_MULTI_CORE_SUPPORT == STD_ON)
extern Eth_TimeStampQualType RxTimeQual_0;
extern Eth_TimeStampType RxTimeStamp_0[2];
extern Eth_TimeStampQualType TxTimeQual_0;
extern Eth_TimeStampType TxTimeStamp_0[2];
extern Eth_TimeStampQualType RxTimeQual_1;
extern Eth_TimeStampType RxTimeStamp_1[2];
extern Eth_TimeStampQualType TxTimeQual_1;
extern Eth_TimeStampType TxTimeStamp_1[2];
#else
extern Eth_TimeStampQualType RxTimeQual;
extern Eth_TimeStampType RxTimeStamp[2];
extern Eth_TimeStampQualType TxTimeQual;
extern Eth_TimeStampType TxTimeStamp[2];
#endif
#endif
#endif

#define ETH_PASSED                    1
/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

/* RxIndication event referring to a Ethernet Network */
extern void EthIf_RxIndication(uint8 CtrlIdx,
                               Eth_FrameType FrameType,
                               boolean IsBroadcast,
                               const uint8* PhysAddrPtr,
                               const Eth_DataType* DataPtr,
                               uint16 LenByte);

/* TxConfirmaton event referring to a Ethernet Network */
extern void EthIf_TxConfirmation(uint8 CtrlIdx, Eth_BufIdxType BufIdx, Std_ReturnType Result);

/*Called asynchronously when mode has been read out.
 Triggered by previous Eth_SetControllerMode call.
 Can directly be called within the trigger functions. */
extern void EthIf_CtrlModeIndication(uint8 CtrlIdx, Eth_ModeType CtrlMode);

#endif /* ETHIF_CBK_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
