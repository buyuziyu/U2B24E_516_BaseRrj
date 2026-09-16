/*============================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                         */
/* Module       = CanIf_Types.h                                               */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2023-2025 Renesas Electronics Corporation. All rights reserved.        */
/*============================================================================*/
/* Purpose:                                                                   */
/* Provision of Type definitions                                              */
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
 * 2.4.0:  30/05/2025  : Update SW-VERSION for RH850/Ver22.01.00 (D) U2Ax Release
 * 2.3.1:  31/03/2025: Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 * 2.3.0:  28/02/2025: Update SW-VERSION for RH850/Ver22.01.00/Ver22.01.00.D 
 *                     Final Release
 * 2.2.0:  31/12/2024: Update SW-VERSION for Ver22.02.00/Ver22.02.00.D 
 *                     Final Release
 * 2.1.3:  31/10/2024: Update SW Version
 * 2.1.2:  30/09/2024: Update SW Version
 *                         Remove SW Patch Version
 * 2.1.1:  16/05/2024: Change CANIF_SW_MINOR_VERSION to 1U
 *                         Change CANIF_SW_PATCH_VERSION to 1U
 * 2.1.0:  23/02/2024: Update SW-VERSION to 2.1.0
 * 2.0.1:  22/09/2023: Initial Version
 */
/*******************************************************************************
**                         Input File                                         **
*******************************************************************************/

#ifndef CANIF_TYPES_H
#define CANIF_TYPES_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanIf_Can.h"    /* CAN Driver Module Header File */


/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR Specification Version Information */
#define CANIF_AR_MAJOR_VERSION     CAN_AR_MAJOR_VERSION_VALUE
#define CANIF_AR_MINOR_VERSION     CAN_AR_MINOR_VERSION_VALUE
/* Software Version Information */
#define CANIF_SW_MAJOR_VERSION  2
#define CANIF_SW_MINOR_VERSION  4

/*******************************************************************************
**                              Macros                                        **
*******************************************************************************/
/* Invalid CAN ID is reported using following error code */
#define CANIF_E_PARAM_CANID            (uint8)10

/* Invalid DLC is reported using following error code */
#define CANIF_E_PARAM_DLC              (uint8)11

/* Invalid PduId is reported using following error code */
#define CANIF_E_PARAM_LPDU             (uint8)12

/* Invalid HRH is reported using following error code */
#define CANIF_E_PARAM_HRH              (uint8)13

/* Invalid channel ID is reported using following error code */
#define CANIF_E_PARAM_CHANNEL          (uint8)14

/* Invalid controller ID is reported using following error code */
#define CANIF_E_PARAM_CONTROLLER       (uint8)15

/* Invalid network is reported using following error code BUG #12129*/
#define CANIF_E_PARAM_NETWORK          (uint8)16

/* Invalid mode request is reported using following error code */
#define CANIF_E_PARAM_MODEREQUEST      (uint8)17

/* Invalid pointer input is reported using following error code */
#define CANIF_E_PARAM_POINTER          (uint8)20

/* API service used without module initialization */
#define CANIF_E_UNINIT                 (uint8)30

/* Not supported API request is reported using following error code */
#define CANIF_E_NOK_NOSUPPORT          (uint8)40

#define CANIF_WAKEUP_DISABLED          (uint8)0x00

#define CANIF_WAKEUP_ENABLED           (uint8)0x01

#define CANIF_STANDARD_CANID_TYPE      (uint8) 0x00

#define CANIF_EXTENDED_CANID_TYPE      (uint8) 0x01

#define CANIF_MIXED_CANID_TYPE         (uint8) 0x02

typedef uint32 CanIf_WakeupEvent;


/* State transitions that are used by the function CanIf_SetControllerMode */
typedef enum
{
  CANIF_CS_UNINIT = 0,
  CANIF_CS_STOPPED,
  CANIF_CS_STARTED,
  CANIF_CS_SLEEP
} CanIf_ControllerModeType;

/* State transitions that are used by the function CanIf_SetChannelMode */
typedef enum
{
  CANIF_SET_OFFLINE = 0,
  CANIF_SET_RX_OFFLINE,
  CANIF_SET_RX_ONLINE,
  CANIF_SET_TX_OFFLINE,
  CANIF_SET_TX_ONLINE,
  CANIF_SET_ONLINE,
  CANIF_SET_TX_OFFLINE_ACTIVE
} CanIf_ChannelSetModeType;

typedef enum
{
  CANIF_GET_OFFLINE = 0,
  CANIF_GET_RX_ONLINE,
  CANIF_GET_TX_ONLINE,
  CANIF_GET_ONLINE,
  CANIF_GET_OFFLINE_ACTIVE,
  CANIF_GET_OFFLINE_ACTIVE_RX_ONLINE

} CanIf_ChannelGetModeType;

/* Return value of the Notification Status API */
typedef enum
{
  CANIF_NO_NOTIFICATION =0,
  CANIF_TX_RX_NOTIFICATION
} CanIf_NotifStatusType;

/* Return value of the WakeupSourceType. */
typedef enum
{
  CANIF_CONTROLLER_WAKEUP = 0,
  CANIF_TRANSCEIVER_WAKEUP
}CanIf_WakeupSourceType;

/* Return value of the CanIf_TransceiverModeType. */
typedef enum
{
  CANIF_TRCV_MODE_NORMAL = 0,
  CANIF_TRCV_MODE_STANDBY,
  CANIF_TRCV_MODE_SLEEP
}CanIf_TransceiverModeType;

/* Return value of the CanIf_TrcvWakeupReasonType. */
typedef enum
{
  CANIF_TRCV_WU_ERROR = 0,
  CANIF_TRCV_WU_NOT_SUPPORTED,
  CANIF_TRCV_WU_BY_BUS,
  CANIF_TRCV_WU_INTERNALLY,
  CANIF_TRCV_WU_RESET,
  CANIF_TRCV_WU_POWER_ON
}CanIf_TrcvWakeupReasonType;

/* Return value of the CanIf_TrcvWakeupModeType. */
typedef enum
{
  CANIF_TRCV_WU_ENABLE = 0,
  CANIF_TRCV_WU_DISABLE,
  CANIF_TRCV_WU_CLEAR
}CanIf_TrcvWakeupModeType;

/*******************************************************************************
**                      Global Function Prototypes                            **
*******************************************************************************/

#endif /* CANIF_TYPES_H */


/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
