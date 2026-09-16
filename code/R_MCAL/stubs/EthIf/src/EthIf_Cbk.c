/*============================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                         */
/* Module       = EthIf_Cbk.c                                                 */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2023-2025 Renesas Electronics Corporation. All rights reserved.        */
/*============================================================================*/
/* Purpose:                                                                   */
/* This application file contains execution sequences to demonstrate the usage*/
/* of ETH Driver APIs.                                                        */
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
 * 2.3.0      28/02/2025     Update to support multicore.
 * 2.2.0      31/12/2024     Update SW-VERSION for Ver22.02.00(D) U2Bx Final Release
 * 2.1.3      31/10/2024     Update for CAN XL stubs
 * 2.1.2      30/09/2024     Update for CAN XL stubs
 * 2.1.1      24/07/2024     Update SW-VERSION to 2.1.1
 * 2.1.0      01/06/2024     Add modification of variable when supporting multicore.
 *                           Update SW-VERSION to 2.1.0
 * 2.0.1      22/09/2023     Initial Version
 */
/******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "EthIf_Cbk.h"
#include <stdio.h>
#include <string.h>
/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
/* AUTOSAR release version information */
#define ETHIF_C_AR_RELEASE_MAJOR_VERSION   ETH_AR_RELEASE_MAJOR_VERSION_VALUE
#define ETHIF_C_AR_RELEASE_MINOR_VERSION   ETH_AR_RELEASE_MINOR_VERSION_VALUE
#define ETHIF_C_AR_RELEASE_REVISION_VERSION \
                                        ETH_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define ETHIF_SW_MAJOR_VERSION    ETH_SW_MAJOR_VERSION
#define ETHIF_SW_MINOR_VERSION    ETH_SW_MINOR_VERSION

/*******************************************************************************
**                         Global Data                                        **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
**                             EthIf_RxIndication                             **
*******************************************************************************/

void EthIf_RxIndication(uint8 CtrlIdx,
                        Eth_FrameType FrameType,
                        boolean IsBroadcast,
                        const uint8* PhysAddrPtr,
                        const Eth_DataType* DataPtr,
                        uint16 LenByte)
{

  #if (GLOBAL_TIME_SUPPORT == STD_ON)
  #ifndef CAN_MODULE_SAMPLE
  Eth_TimeStampQualType LenEthTimeQualPtr;
  Eth_TimeStampType LstIngressTime;
  #endif
  #ifdef CAN_MODULE_SAMPLE
  #if (CAN_MULTI_CORE_SUPPORT == STD_OFF)
  CanXL_GetIngressTimeStamp(CtrlIdx, (Eth_DataType*)DataPtr, &RxTimeQual, &RxTimeStamp[CtrlIdx-2]);
  #else
  if(0 == GetCoreID())
  {
    CanXL_GetIngressTimeStamp(CtrlIdx, (Eth_DataType*)DataPtr, &RxTimeQual_0, &RxTimeStamp_0[CtrlIdx-2]);
  }
  else
  {
    #if !defined (CAN_U2B6E_USED)
    CanXL_GetIngressTimeStamp(CtrlIdx, (Eth_DataType*)DataPtr, &RxTimeQual_1, &RxTimeStamp_1[CtrlIdx-2]);
    #endif
  }
  #endif
  #else

  #if (ETH_MULTI_CORE_SUPPORT == STD_OFF)
  Eth_GetIngressTimeStamp(CtrlIdx, (Eth_DataType*)DataPtr, &LenEthTimeQualPtr, &LstIngressTime);
  if (ETH_VALID == LenEthTimeQualPtr)
  {
    EthPassedCount[EthCheckCount] = ETH_PASSED;
  }
  EthCheckCount++;
  #else
  Eth_GetIngressTimeStamp(CtrlIdx, (Eth_DataType*)DataPtr, &LenEthTimeQualPtr, &LstIngressTime);
  if(0 == GetCoreID())
  {
    if (ETH_VALID == LenEthTimeQualPtr)
    {
      EthPassedCount_0[EthCheckCount_0] = ETH_PASSED;
    }
    EthCheckCount_0++;
  }
  else
  {
    if (ETH_VALID == LenEthTimeQualPtr)
    {
      EthPassedCount_1[EthCheckCount_1] = ETH_PASSED;
    }
    EthCheckCount_1++;
  }
  #endif
  #endif
  #endif

  #ifdef ETH_DEBUG_CONSOLE_MODE
  printf("Rx: Controller Index = %d, Received LenByte = %d, FrameType = 0x%04x IsBroadcast = %d \n",
    CtrlIdx, LenByte, FrameType, IsBroadcast);
  #endif

  /* memcpy Received message */
  #ifdef CAN_MODULE_SAMPLE
  GusMsgLength[CtrlIdx-2] = LenByte;
  GusRxFrameCnt[CtrlIdx-2]++;
  GusRxFrameType[CtrlIdx-2] = FrameType; 
  memcpy((uint8*)GaaRxEthFrame[CtrlIdx-2], (uint8*)DataPtr, GusMsgLength[CtrlIdx-2]);
  #else
  #if (ETH_MULTI_CORE_SUPPORT == STD_OFF)
  /* LenByte contains the payload length */
  GusMsgLength[CtrlIdx] = LenByte;

  /* memcpy Received message */
  memcpy((uint8*)GaaRxEthFrame[CtrlIdx], (uint8*)DataPtr, GusMsgLength[CtrlIdx]);
  memcpy((uint8*)GaaRxSrcAddr[CtrlIdx][0], PhysAddrPtr, 6);
  GusRxFrameType[CtrlIdx] = FrameType;
  /* Store entire frame size (with header) to GusRxLenByte */
  GusRxLenByte[CtrlIdx] = LenByte + 14U;
  GusRxFrameCnt[CtrlIdx]++;
  #else
  if(0 == GetCoreID())
  {
    /* LenByte contains the payload length */
    GusMsgLength_0[CtrlIdx] = LenByte;
    memcpy((uint8*)GaaRxEthFrame_0[CtrlIdx], (uint8*)DataPtr, GusMsgLength_0[CtrlIdx]);
    memcpy((uint8*)GaaRxSrcAddr_0[CtrlIdx], PhysAddrPtr, 6);
    GusRxFrameType_0[CtrlIdx] = FrameType;
    /* Store entire frame size (with header) to GusRxLenByte */
    GusRxLenByte_0[CtrlIdx] = LenByte + 14U;
    GusRxFrameCnt_0[CtrlIdx]++;
  }
  else
  {
    GusMsgLength_1[CtrlIdx] = LenByte;
    memcpy((uint8*)GaaRxEthFrame_1[CtrlIdx], (uint8*)DataPtr, GusMsgLength_1[CtrlIdx]);
    memcpy((uint8*)GaaRxSrcAddr_1[CtrlIdx], PhysAddrPtr, 6);
    GusRxFrameType_1[CtrlIdx] = FrameType;
    /* Store entire frame size (with header) to GusRxLenByte */
    GusRxLenByte_1[CtrlIdx] = LenByte + 14U;
    GusRxFrameCnt_1[CtrlIdx]++;
  }
  #endif
  #endif
}

/*******************************************************************************
**                             EthIf_TxConfirmation                           **
*******************************************************************************/
void EthIf_TxConfirmation(uint8 CtrlIdx, Eth_BufIdxType BufIdx, Std_ReturnType Result)
{
  #ifndef CAN_MODULE_SAMPLE
  #ifdef ETH_DEBUG_CONSOLE_MODE
  printf("Tx: Controller Index = %d, Confirmed BufIdx = %d \n", CtrlIdx, BufIdx);
  #endif

  #if (GLOBAL_TIME_SUPPORT == STD_ON)
  #if (ETH_MULTI_CORE_SUPPORT == STD_OFF)
  TxTimeQual = ETH_INVALID;
  #else
  TxTimeQual_0 = ETH_INVALID;
  TxTimeQual_1 = ETH_INVALID;
  #endif
  #if (ETH_MULTI_CORE_SUPPORT == STD_OFF)
  do
  {
    Eth_GetEgressTimeStamp(CtrlIdx, BufIdx, &TxTimeQual, &TxTimeStamp[CtrlIdx]);
  } while (ETH_INVALID == TxTimeQual);
  if (ETH_VALID == TxTimeQual)
  {
    EthPassedCount[EthCheckCount] = ETH_PASSED;
  }
  EthCheckCount++;
  #else
  if(0 == GetCoreID())
  {
    do
    {
      Eth_GetEgressTimeStamp(CtrlIdx, BufIdx, &TxTimeQual_0, &TxTimeStamp_0[CtrlIdx]);
    } while (ETH_INVALID == TxTimeQual_0);
    if (ETH_VALID == TxTimeQual_0)
    {
      EthPassedCount_0[EthCheckCount_0] = ETH_PASSED;
    }
    EthCheckCount_0++;
  }
  else
  {
    do
    {
      Eth_GetEgressTimeStamp(CtrlIdx, BufIdx, &TxTimeQual_1, &TxTimeStamp_1[CtrlIdx]);
    } while (ETH_INVALID == TxTimeQual_1);
    if (ETH_VALID == TxTimeQual_1)
    {
      EthPassedCount_1[EthCheckCount_1] = ETH_PASSED;
    }
    EthCheckCount_1++;
  }
  #endif
  #endif
  #endif


  #ifdef CAN_MODULE_SAMPLE
  #if (GLOBAL_TIME_SUPPORT == STD_ON)
  #if (CAN_MULTI_CORE_SUPPORT == STD_OFF)
  do
  {
    CanXL_GetEgressTimeStamp(CtrlIdx, BufIdx, &TxTimeQual, &TxTimeStamp[CtrlIdx-2]);
  } while (ETH_INVALID == TxTimeQual);
  #else
  if(0 == GetCoreID())
  {
    do
    {
      CanXL_GetEgressTimeStamp(CtrlIdx, BufIdx, &TxTimeQual_0, &TxTimeStamp_0[CtrlIdx-2]);
    } while (ETH_INVALID == TxTimeQual_0);
  }
  else
  {
    #if !defined (CAN_U2B6E_USED)
    do
    {
      CanXL_GetEgressTimeStamp(CtrlIdx, BufIdx, &TxTimeQual_1, &TxTimeStamp_1[CtrlIdx-2]);
    } while (ETH_INVALID == TxTimeQual_1);
    #endif
  }
  #endif
  GucTxConfirmed[CtrlIdx-2]++;
  #endif
  #else
  #if (ETH_MULTI_CORE_SUPPORT == STD_OFF)
    GucTxConfirmed[CtrlIdx] = 1U;
  #else
    GucTxConfirmed_0[CtrlIdx] = 1U;
    GucTxConfirmed_1[CtrlIdx] = 1U;
  #endif
  #endif
}

/*******************************************************************************
**                             EthIf_TxConfirmation                           **
*******************************************************************************/
void EthIf_CtrlModeIndication( uint8 CtrlIdx, Eth_ModeType CtrlMode)
{
  #ifdef ETH_DEBUG_CONSOLE_MODE
  printf("Controller Index = %d, Mode changed CtrlMode = %d \n", CtrlIdx, CtrlMode);
  #endif
}

/*******************************************************************************
                          End of the file
*******************************************************************************/
