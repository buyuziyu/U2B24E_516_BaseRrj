/*============================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                         */
/* Module       = CanIf_Cbk.c                                                 */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2023-2025 Renesas Electronics Corporation. All rights reserved.        */
/*============================================================================*/
/* Purpose:                                                                   */
/* This application file contains execution sequences to demonstrate the usage*/
/* of CAN Driver APIs.                                                        */
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
 * 2.4.1:  30/06/2025  : Remove the SW-VERSION from header of file
 * 2.4.0:  30/05/2025  : Add volatile
 * 2.3.1:  31/03/2025  : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 * 2.3.0:  28/02/2025  : Update SW-VERSION for RH850/Ver22.01.00/Ver22.01.00.D 
 *                       Final Release
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D 
 *                       Final Release
 * 2.1.3:  31/10/2024  : Update SW Version
 * 2.1.2:  30/09/2024  : Update SW Version
 * 2.1.1:  12/08/2024  : Update CanIf_RxIndication
 *         09/06/2024  : Update CanIf_TxConfirmation, CanIf_XLRxIndication
 *         06/06/2024  : Add Function Definition for CanIf_XLRxIndication
 * 2.1.0:  23/02/2024  : Update SW-VERSION to 2.1.0
 * 2.0.1:  22/09/2023  : Initial Version
 */
/******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "CanIf_Can.h"
#include "Os.h"

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
/* AUTOSAR release version information */
#define CANIF_C_AR_RELEASE_MAJOR_VERSION CAN_AR_RELEASE_MAJOR_VERSION_VALUE
#define CANIF_C_AR_RELEASE_MINOR_VERSION CAN_AR_RELEASE_MINOR_VERSION_VALUE
#define CANIF_C_AR_RELEASE_REVISION_VERSION \
  CAN_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define CANIF_C_SW_MAJOR_VERSION CAN_SW_MAJOR_VERSION
#define CANIF_C_SW_MINOR_VERSION CAN_SW_MINOR_VERSION

#ifndef CAN_USE_MULTICORE
volatile uint8 GucTransmitCount;
volatile uint8 GucReceiveCount;
#else
volatile uint8 GucTransmitCount_0;
volatile uint8 GucReceiveCount_0;
volatile uint8 GucTransmitCount_1;
volatile uint8 GucReceiveCount_1;
#endif
uint8 GucCancelCount;
volatile uint8 GucReceiveCount;
uint8 GucErrFlag;
uint8 GblStartFlag;
uint8 GucCount;
// uint8 GucWakeupCount;
uint8 GucBusOffCount;
uint8 GucStartCount;
uint16 GusTimeoutCount;
uint8 GucDelayCount;
uint8 GucTestCount;
volatile uint8 GucReturnCount;
uint8 GucDetCount;
uint8 GucTestIndex;
uint8 GucTestCaseIndex;
uint8 GucDemCount;
uint8 sdu10[8];

/*******************************************************************************
**                         Global Data                                        **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
**                             CanIf_RxIndication                             **
*******************************************************************************/
void CanIf_RxIndication(const Can_HwType* Mailbox, \
                    const PduInfoType* PduInfoPtr)
{
  #ifdef CAN_USE_MULTICORE
  uint8 LucCoreId;
  /* Get Core id for code branching */
  LucCoreId = (uint8)GetCoreID();
  
  if (LucCoreId == 0 )
  {
    GucReceiveCount_0 ++;
  }
  else
  {
    GucReceiveCount_1 ++;
  }
  #else
  GucReceiveCount++;
  #endif
  
  (void)Mailbox;
  (void)PduInfoPtr;
}

/*******************************************************************************
**                             CanIf_XLRxIndication                             **
*******************************************************************************/
void CanIf_XLRxIndication(const CanXL_HwType* Mailbox,
                          const PduInfoType* PduInfoPtr)
{
  #ifdef CAN_USE_MULTICORE
  uint8 LucCoreId;
  /* Get Core id for code branching */
  LucCoreId = (uint8)GetCoreID();
  
  if (LucCoreId == 0 )
  {
    GucReceiveCount_0 ++;
  }
  else
  {
    GucReceiveCount_1 ++;
  }
  #else
  GucReceiveCount++;
  #endif
  
  (void)Mailbox;
  (void)PduInfoPtr;
}

/*******************************************************************************
**                             CanIf_TxConfirmation                           **
*******************************************************************************/
void CanIf_TxConfirmation(PduIdType CanTxPduId)
{
  #ifdef CAN_USE_MULTICORE
  uint8 LucCoreId;
  /* Get Core id for code branching */
  LucCoreId = (uint8)GetCoreID();
  
  if (LucCoreId == 0 )
  {
    GucTransmitCount_0 ++;
  }
  else
  {
    GucTransmitCount_1 ++;
  } 
  #else
  GucTransmitCount++;
  #endif
  
  (void) CanTxPduId;
}
/*******************************************************************************
                              CanIf_ControllerBusOff
*******************************************************************************/

void CanIf_ControllerBusOff (uint8 Controller)
{

}

/*******************************************************************************
                              CanIf_ControllerModeIndication
*******************************************************************************/

void CanIf_ControllerModeIndication (uint8 Controller, \
                                        Can_ControllerStateType ControllerMode)
{

}

Std_ReturnType CanIf_TriggerTransmit(PduIdType TxPduId, PduInfoType* PduInfoPtr)
{

  return E_OK;
}

/*******************************************************************************
                              CanIf_ControllerErrorStatePassive
*******************************************************************************/

void CanIf_ControllerErrorStatePassive(uint8 ControllerId, \
                                       uint16 RxErrorCounter, \
                                       uint16 TxErrorCounter)
{

}

/*******************************************************************************
                              CanIf_ErrorNotification
*******************************************************************************/
void CanIf_ErrorNotification(uint8 ControllerId, \
                                    Can_ErrorType CanErrorType)
{

}

/*******************************************************************************
                          End of the file
*******************************************************************************/
