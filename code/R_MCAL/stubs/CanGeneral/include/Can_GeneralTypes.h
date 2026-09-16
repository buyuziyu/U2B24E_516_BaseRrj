/*============================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                         */
/* Module       = Can_GeneralTypes.h                                          */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2022-2025 Renesas Electronics Corporation. All rights reserved.        */
/*============================================================================*/
/* Purpose:                                                                   */
/* C header file for CAN Driver type definitions.                             */
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
 * 2.4.1:  30/06/2025  : Remove the SW-VERSION from header of file
 * 2.4.0:  30/05/2025  : Update SW-VERSION for RH850/Ver22.01.00 (D) U2Ax Release
 * 2.3.1:  31/03/2025  : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 * 2.3.0:  28/02/2025  : Update SW-VERSION for RH850/Ver22.01.00/Ver22.01.00.D 
 *                       Final Release
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final 
 *                       Release
 * 2.1.3:  31/10/2024  : Update SW Version
 * 2.1.2:  30/09/2024  : Update SW Version
 * 2.1.1:  16/06/2024  : Add Version Information
 *         06/06/2024  : Add CanXL_Params, CanXL_PduType, CanXL_HwType
 * 2.1.0:  23/02/2024  : Update SW-VERSION to 2.1.0
 * 2.0.0:  28/04/2023  : Add enum Can_ErrorType
 *         27/04/2023  : Update CANIF_SW_MAJOR_VERSION to 2
 *                       Update CANIF_SW_MINOR_VERSION to 0
 * 1.4.5:  28/09/2022  : Initial Version
 */
/******************************************************************************/
#ifndef CAN_GENERALTYPES_H
#define CAN_GENERALTYPES_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "ComStack_Types.h"
/******************************************************************************/

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR Specification Version Information */
#define CAN_GENERALTYPES_AR_RELEASE_MAJOR_VERSION         4U
#define CAN_GENERALTYPES_AR_RELEASE_MINOR_VERSION         8U
#define CAN_GENERALTYPES_AR_RELEASE_REVISION_VERSION      0U

/* Software Version Information */
#define CAN_GENERALTYPES_SW_MAJOR_VERSION         2U
#define CAN_GENERALTYPES_SW_MINOR_VERSION         4U

/* Vendor ID */
#define CAN_GENERALTYPES_VENDOR_ID (uint8)59

/* Module ID */
#define CAN_GENERALTYPES_MODULE_ID (uint16)80

/*******************************************************************************
**                      Can_PduType                                           **
*******************************************************************************/
/* General Types */
#ifdef CAN_CANTYPE_DECLARATION_UINT16
typedef uint8 Can_HwHandleType;
#else
typedef uint16 Can_HwHandleType;
#endif
typedef uint32 Can_IdType;


/* This is used to provide CAN-ID, DLC and SDU from CanIf to CAN Driver */
typedef struct STag_Can_PduType
{
  /* Pointer to L-SDU */
  uint8      *sdu;
  /* CAN-ID */
  Can_IdType id;
  /* swPduHandle */
  PduIdType  swPduHandle;
  /* DLC */
  uint8 length;
} Can_PduType;

/*******************************************************************************
**                      Can_ControllerStateType                               **
*******************************************************************************/
/* State transitions that are used by the function Can_SetControllerMode and */
/* Can_GetControllerMode. */
typedef enum ETag_Can_ControllerStateType
{
  CAN_CS_UNINIT = 0,
  CAN_CS_STARTED,
  CAN_CS_STOPPED,
  CAN_CS_SLEEP
} Can_ControllerStateType;

/*******************************************************************************
**                      Can_ErrorStateType                               **
*******************************************************************************/
/* Error states of a CAN controller that are used by the function */
/* Can_GetControllerErrorState */
typedef enum ETag_Can_ErrorStateType
{
  CAN_ERRORSTATE_ACTIVE = 0,
  CAN_ERRORSTATE_PASSIVE,
  CAN_ERRORSTATE_BUSOFF
} Can_ErrorStateType;

/*******************************************************************************
**                      Can_ReturnType                                        **
*******************************************************************************/
/*
CAN_BUSY    : Transmit request could not be processed because no
              transmit object was available
*/
/* Return values of CAN Driver API */
typedef enum ETag_Can_ReturnType
{
  CAN_BUSY = 2
} Can_ReturnType;

/*******************************************************************************
**                      Can_HwType                                            **
*******************************************************************************/
/* This type defines a data structure which clearly provides an Hardware Object
Handle including its corresponding CAN Controller and therefore CanDrv as well
as the specific CanId. */
typedef struct STag_Can_HwType
{
  Can_IdType        CanId;
  Can_HwHandleType  Hoh;
  uint8             ControllerId;
}Can_HwType;

/*******************************************************************************
**                      CanXL_Params                                          **
*******************************************************************************/
/* Contains CAN XL specific information. */
typedef struct CanXL_Params_STag
{
  /* Priority ID of a CAN XL message. */
  uint16 PriorityId;
  /* VCID of a CAN XL message. */
  uint16 Vcid;
  /* SDU type of a CAN XL message */
  uint8 SduType;
  /* Acceptance field of a CAN XL message. */
  uint32 AcceptanceField;
  /* Simple extended content field of a CAN XL message. */
  uint8 Sec;
} CanXL_Params;

/*******************************************************************************
**                      CanXL_PduType                                         **
*******************************************************************************/
/* This type extends the classical Can_PduType with a larger PDU length, the CanXL_Params and a
sec to indicate simple or extended content. */
typedef struct CanXL_PduType_Stag
{
  /* Contains the PDU ID. */
  PduIdType swPduHandle;
  /* Length of the data */
  uint16 length;
  /* SDU data pointer. */
  uint8 *sdu;
  /* Pointer to CAN XL params. */
  CanXL_Params *XLParams;
} CanXL_PduType;

/*******************************************************************************
**                      CanXL_HwType                                          **
*******************************************************************************/
/* This type defines a data structure which provides a CAN XL Hardware Object Handle including its
corresponding CAN Controller and therefore CanDrv as well as the specific CAN XL parameters. */
typedef struct CanXL_HwType_Stag
{
  /* Pointer to CAN XL params. */
  CanXL_Params *XLParams;
  /* ControllerId provided by CanIf, identifies the corresponding CAN XL controller. */
  uint8 ControllerId;
  /* ID of the corresponding CAN XL Hardware Object Range */
  Can_HwHandleType Hoh;
} CanXL_HwType;

/*******************************************************************************
**                      Can_ErrorType                                         **
*******************************************************************************/
/* Can Bus Error of a CAN controller that are used by the function*/
/* CanIf_ErrorNotification */
typedef enum ETag_Can_ErrorType
{
  CAN_ERROR_BIT_MONITORING1 = 0x01,
  CAN_ERROR_BIT_MONITORING0 = 0x02,
  CAN_ERROR_BIT = 0x03,
  CAN_ERROR_CHECK_ACK_FAILED = 0x04,
  CAN_ERROR_ACK_DELIMITER = 0x05,
  CAN_ERROR_ARBITRATION_LOST = 0x06,
  CAN_ERROR_OVERLOAD = 0x07,
  CAN_ERROR_CHECK_FORM_FAILED = 0x08,
  CAN_ERROR_CHECK_STUFFING_FAILED = 0x09,
  CAN_ERROR_CHECK_CRC_FAILED = 0x0A,
  CAN_ERROR_BUS_LOCK = 0x0B
} Can_ErrorType;
/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#endif /* CAN_GENERALTYPES_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
