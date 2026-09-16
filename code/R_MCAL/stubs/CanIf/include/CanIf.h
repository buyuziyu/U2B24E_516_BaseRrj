/*============================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                         */
/* Module       = CanIf.h                                                     */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2023-2025 Renesas Electronics Corporation. All rights reserved         */
/*============================================================================*/
/* Purpose:                                                                   */
/* Provision of external declaration of constants, global data, type          */
/* definitions, APIs and service IDs.                                         */
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
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final 
 *                       Release
 * 2.1.3:   31/10/2024: Update SW Version
 * 2.1.2:   30/09/2024: Update SW Version
 * 2.1.1:   16/06/2024: Change CANIF_SW_MINOR_VERSION to 1U
 *          01/06/2024: Add global variable to support multicore
 * 2.1.0:   23/02/2024: Update SW-VERSION to 2.1.0
 * 2.0.1:   22/09/2023: Initial Version
 */
/******************************************************************************/

#ifndef CANIF_H
#define CANIF_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* Com Stack Types Header File */
#include "ComStack_Types.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR Specification Version Information */
#define CANIF_AR_RELEASE_MAJOR_VERSION         4U
#define CANIF_AR_RELEASE_MINOR_VERSION         8U
#define CANIF_AR_RELEASE_REVISION_VERSION      0U

/* Software Version Information */
#define CANIF_SW_MAJOR_VERSION         2U
#define CANIF_SW_MINOR_VERSION         4U

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* Vendor ID */
#define CANIF_VENDOR_ID (uint8)59

/* Module ID */
#define CANIF_MODULE_ID (uint16)80

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/

/*******************************************************************************
**                   CanIf_WakeupSourceType                                   **
*******************************************************************************/
/* Return value of the WakeupSourceType. */
typedef enum ETag_CanIf_WakeupSourceType
{
  CANIF_CONTROLLER_WAKEUP = 0,
  CANIF_TRANSCEIVER_WAKEUP
} CanIf_WakeupSourceType;

/*******************************************************************************
**                   CanIf_TransceiverModeType                                **
*******************************************************************************/
/* Return value of the CanIf_TransceiverModeType. */
typedef enum ETag_CanIf_TransceiverModeType
{
  CANIF_TRCV_MODE_NORMAL = 0,
  CANIF_TRCV_MODE_STANDBY,
  CANIF_TRCV_MODE_SLEEP
} CanIf_TransceiverModeType;
/*******************************************************************************
**                   CanIf_TrcvWakeupReasonType                               **
*******************************************************************************/

/* Return value of the CanIf_TrcvWakeupReasonType. */
typedef enum ETag_CanIf_TrcvWakeupReasonType
{
  CANIF_TRCV_WU_ERROR = 0,
  CANIF_TRCV_WU_NOT_SUPPORTED,
  CANIF_TRCV_WU_BY_BUS,
  CANIF_TRCV_WU_INTERNALLY,
  CANIF_TRCV_WU_RESET,
  CANIF_TRCV_WU_POWER_ON
} CanIf_TrcvWakeupReasonType;
/*******************************************************************************
**                   CanIf_TrcvWakeupModeType                                 **
*******************************************************************************/
/* Return value of the CanIf_TrcvWakeupModeType. */
typedef enum ETag_CanIf_TrcvWakeupModeType
{
  CANIF_TRCV_WU_ENABLE = 0,
  CANIF_TRCV_WU_DISABLE,
  CANIF_TRCV_WU_CLEAR
} CanIf_TrcvWakeupModeType;

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
#ifndef CAN_USE_MULTICORE
extern volatile uint8 GucTransmitCount;
extern volatile uint8 GucReceiveCount;
#else
extern volatile uint8 GucTransmitCount_0;
extern volatile uint8 GucReceiveCount_0;
extern volatile uint8 GucTransmitCount_1;
extern volatile uint8 GucReceiveCount_1;
#endif
extern uint8 GucCancelCount;
extern uint8 GucTestCount;
extern uint8 GucTestIndex;
extern uint8 GucTestCaseIndex;
extern uint8 GucErrFlag;
// extern uint8 GucWakeupCount;
extern uint8 GucBusOffCount;
extern uint8 GucStartCount;
extern uint8 Can_GaaDataArray[];
extern uint8 sdu10[];
extern uint8 GblStartFlag;
extern uint8 GucCount;
extern uint16 GucServiceId;
extern uint16 GusTimeoutCount;
extern uint8 GucDelayCount;
extern volatile uint8 GucReturnCount;
extern uint8 GucDetCount;
extern uint8 GucDemCount;
extern uint8 GucTestCaseId;


extern uint8 *GpDataArray1;
extern uint8 *GpDataArray2;



extern uint16 App_Can_GaaPassTestCaseId[];
extern uint16 App_Can_GaaFailTestCaseId[];

extern boolean Appl_Can_DataCompare
                  (const uint8 *CanSduPtr, const uint8 *DataPtr, uint8 CanDlc);

extern void Can_Increment_TxByteValue(uint8 *SduPtr, uint8 Length);
extern void Can_Increment_RxByteValue(uint16 offset , uint8 Length);

/* Controller state transition referring to the corresponding CAN controller */
extern Std_ReturnType CanIf_TriggerTransmit(PduIdType TxPduId, 
                  PduInfoType* PduInfoPtr);

#endif /* CANIF_H */


/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
