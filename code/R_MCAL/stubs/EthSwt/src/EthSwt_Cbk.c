/*============================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                         */
/* Module       = EthSwt_Cbk.c                                                */
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
 * 2.2.0      31/12/2024     Update SW-VERSION for Ver22.02.00(D) U2Bx Final Release
 * 2.1.2      31/10/2024     Update SW-VERSION to 2.1.2
 * 2.1.1      24/07/2024     Update SW-VERSION to 2.1.1
 * 2.1.0      06/03/2024     Update SW-VERSION to 2.1.0
 * 2.0.1      22/09/2023     Initial Version
 */
/******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "EthSwt_Cbk.h"
#include <stdio.h>
#include <string.h>
/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
/* AUTOSAR release version information */
#define ETHSWT_C_AR_RELEASE_MAJOR_VERSION    ETH_AR_RELEASE_MAJOR_VERSION_VALUE
#define ETHSWT_C_AR_RELEASE_MINOR_VERSION    ETH_AR_RELEASE_MINOR_VERSION_VALUE
#define ETHSWT_C_AR_RELEASE_REVISION_VERSION ETH_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define ETHSWT_SW_MAJOR_VERSION    ETH_SW_MAJOR_VERSION
#define ETHSWT_SW_MINOR_VERSION    ETH_SW_MINOR_VERSION

/*******************************************************************************
**                         Global Data                                        **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** EthSwt_EthTxAdaptBufferLength                                              **
*******************************************************************************/
void EthSwt_EthTxAdaptBufferLength(
  uint16* LengthPtr)
{
  *LengthPtr += ETHSWT_MANAGEMENT_INFORMATION;
}

/*******************************************************************************
** EthSwt_EthTxPrepareFrame                                                   **
*******************************************************************************/
Std_ReturnType EthSwt_EthTxPrepareFrame(
  uint8 CtrlIdx, Eth_BufIdxType BufIdx, uint8** DataPtr, uint16* LengthPtr)
{
  /* Set management information in the EtherType position and move the EtherType by 2 bytes */
  *DataPtr   += ETHSWT_MANAGEMENT_INFORMATION;
  *LengthPtr += ETHSWT_MANAGEMENT_INFORMATION;

  return E_OK;
}

/*******************************************************************************
** EthSwt_EthTxProcessFrame                                                   **
*******************************************************************************/
Std_ReturnType EthSwt_EthTxProcessFrame(
  uint8 CtrlIdx, Eth_BufIdxType BufIdx, uint8** DataPtr, uint16* LengthPtr)
{
  EthSwt_EDSATagType *LpData;

  LpData = (EthSwt_EDSATagType *)*DataPtr;
  LpData->usEtherType = ETHSWT_DSA_TAG_ETHER_TYPE;
  LpData->stDSA.ucSwtPort = (uint8)0U;

  *DataPtr   += ETHSWT_MANAGEMENT_INFORMATION;
  *LengthPtr += ETHSWT_MANAGEMENT_INFORMATION;
  return E_OK;
}

/*******************************************************************************
** EthSwt_EthRxProcessFrame                                                   **
*******************************************************************************/
Std_ReturnType EthSwt_EthRxProcessFrame(
  uint8 CtrlIdx, Eth_BufIdxType BufIdx, uint8** DataPtr, uint16* LengthPtr, boolean* IsMgmtFrameOnlyPtr)
{
  if(ETHSWT_DSA_TAG_ETHER_TYPE == ((EthSwt_EDSATagType *)*DataPtr)->usEtherType)
  {
    *DataPtr   += ETHSWT_MANAGEMENT_INFORMATION;
    *LengthPtr -= ETHSWT_MANAGEMENT_INFORMATION;
  }
  return E_OK;
}

/*******************************************************************************
** EthSwt_EthRxFinishedIndication                                             **
*******************************************************************************/
Std_ReturnType EthSwt_EthRxFinishedIndication(
  uint8 CtrlIdx, Eth_BufIdxType BufIdx)
{
  return E_OK;
}
/*******************************************************************************
** EthSwt_EthTxFinishedIndication                                             **
*******************************************************************************/
Std_ReturnType EthSwt_EthTxFinishedIndication(
  uint8 CtrlIdx, Eth_BufIdxType BufIdx)
{
  return E_OK;
}
/*******************************************************************************
                          End of the file
*******************************************************************************/
