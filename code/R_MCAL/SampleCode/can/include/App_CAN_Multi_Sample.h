/*============================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                         */
/* Module       = App_CAN_Multi_Sample.h                                      */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2021, 2023-2025 Renesas Electronics Corporation. All rights reserved   */
/*============================================================================*/
/* Purpose:                                                                   */
/* Header file information for application                                    */
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
**                      Revision Control History                              **
*******************************************************************************/
/*
 * 2.4.1: 30/06/2025  : Remove the SW-VERSION from header of file
 * 2.4.0: 30/05/2025  : Update SW-VERSION for RH850/Ver22.01.00 (D) U2Ax Release
 * 2.3.1: 31/03/2025  : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 * 2.3.0: 28/02/2025  : Update SW-VERSION for RH850/Ver22.01.00/Ver22.01.00.D 
 *                      Final Release
 * 2.2.0: 31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final 
 *                      Release
 * 2.1.3: 31/10/2024  : Update SW Version
 * 2.1.2: 30/09/2024  : Increase SW-VERSION to 2.1.2
 * 2.1.1: 30/08/2024  : Add new macro to support multicore CANXL 
 *                    : Add new macro CANXL_FRAME_SUPPORTED
 *                    : Add global variable GblCheckInit_1, GblCheckInit_2
 *                    : Remove macro U2Cx_VLAB_CAN_USED
 *                    : Support multicore for CANXL
 * 2.0.0: 09/08/2023  : Update to support Multicore
 * 1.0.0: 30/08/2021  : Initial Version
 */
/******************************************************************************/
#ifndef APP_CAN_MULTI_SAMPLE_H
#define APP_CAN_MULTI_SAMPLE_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Std_Types.h"
#include "SchM_Can.h"
#include "Can.h"
#include "App_CAN_Device_Sample.h"
#include "Os.h"
#include "CanIf.h"
#include "Can_Ram.h"
/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/
extern volatile uint32 LulCounter;
#if (CAN_CANXL_SUPPORTED == STD_ON)
extern const uint8 GaaByteArrayXL0[];
extern const uint8 GaaByteArrayXL1[];
extern const uint8 GaaByteArray64[];
/* Eth variable */
extern Eth_ModeType EthControllerMode[2];
extern volatile uint8 GaaRxEthFrame[2][1522];
extern volatile uint8 GaaRxSrcAddr[2][6];
extern volatile Eth_FrameType GusRxFrameType[2];
extern volatile uint16 GusRxLenByte[2];
extern volatile uint16 GusRxFrameCnt[2];
extern volatile uint8 GucTxConfirmed[2];
extern volatile uint16 GusMsgLength[2];
/* Target MAC address */
extern uint8 mac_tgt_addr[2U][6U];

extern uint8 mac_board_addr[2U][6U];

extern uint8 RetrieveMacAddr[2][6];
/*---------------------------------------------------*/
/* Receive and Transmit Buffers */
/*---------------------------------------------------*/
extern uint8 TxEthFrame[6][63];
extern Eth_RxStatusType LenEthRxStatus[2];

#endif /* CAN_CANXL_SUPPORTED */

/*******************************************************************************
**                      Global Data Type                                      **
*******************************************************************************/
extern volatile uint8 GblCheckInit;
extern volatile uint8 GblCheckInit_1;
extern volatile uint8 GblCheckInit_2;
extern volatile uint8 GblCheckInit_1;
extern volatile uint8 GblCheckInit_2;
extern volatile uint8 GblDone_Core0;
extern volatile uint8 GblDone_Core1;
extern volatile uint8 GblDone_DeInit_Core1;
extern volatile uint8 GblDone_Init_Core0;
extern volatile uint8  GblCheck_Init_Core1;
extern volatile uint8 GblCheck_DeInit_Core0;
extern volatile uint8 GucReturnCount_0 ;
extern volatile uint8 GucReturnCount_1 ;
extern volatile uint8 GblCheck_Transmit_Core1;
extern volatile uint8 GblCheck_Transmit_Core0;
/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
extern void Can_SampleApp_End(void);

#if (CAN_CANXL_SUPPORTED == STD_ON)
extern void SendEthFrame( uint8 CtrlIdx, uint8 *Buf, uint16 LenByte, Eth_FrameType FrameType,
                   uint8 Priority, const uint8* PhysAddrPtr);
#endif /* CAN_CANXL_SUPPORTED */
#endif /* APP_CAN_MULTI_SAMPLE_H */

/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
