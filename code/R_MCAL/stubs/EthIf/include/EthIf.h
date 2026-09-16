/*============================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                         */
/* Module       = Eth.h                                                       */
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
 * 2.1.0      23/02/2024     Update SW-VERSION to 2.1.0
 * 2.0.1      22/09/2023     Initial Version
 */
/******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Eth_GeneralTypes.h"

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
extern BufReq_ReturnType EthIf_ProvideTxBuffer(
  uint8 CtrlIdx, Eth_FrameType FrameType, uint8 Priority,
  Eth_BufIdxType* BufIdxPtr, uint8** BufPtr, uint16* LenBytePtr);

extern Std_ReturnType EthIf_Transmit(
  uint8 CtrlIdx, Eth_BufIdxType BufIdx, Eth_FrameType FrameType,
  boolean TxConfirmation, uint16 LenByte, const uint8* PhysAddrPtr);

extern void EthIf_GetVersionInfo(
  P2VAR(Std_VersionInfoType, AUTOMATIC, ETH_APPL_DATA)VersionInfoPtr);

extern void EthIf_MainFunctionRx(void);

extern void EthIf_MainFunctionTx(void);
/*******************************************************************************
                          End of the file
*******************************************************************************/
