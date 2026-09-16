/*============================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                         */
/* Module       = Lin_GeneralTypes.h                                          */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2023 - 2025 Renesas Electronics Corporation. All rights reserved.      */
/*============================================================================*/
/* Purpose:                                                                   */
/* C header file for LIN Driver type definitions.                             */
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
 * 2.4.0      30/06/2025     Remove the SW-VERSION from header of file
 * 2.3.2      25/04/2025     Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03
 *                           Release
 * 2.3.1      31/03/2025     Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02
 *                           Release
 * 2.3.0      28/02/2025     Update SW-VERSION for RH850/U2Cx MCAL
 *                           Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0      31/12/2024     Update SW-VERSION for Ver22.02.00(D) U2Bx Final
 *                           Release
 * 2.1.1      17/05/2024     Add Version Information
 * 2.1.0      23/02/2024     Update SW-VERSION to 2.1.0
 * 2.0.1      22/09/2023     Initial Version
 */
/******************************************************************************/

#ifndef LIN_GENERALTYPES_H
#define LIN_GENERALTYPES_H

/*******************************************************************************
**                     Include Section                                        **
*******************************************************************************/
/* Included for Global type declarations */
#include "Std_Types.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR Specification Version Information */
#define LIN_GENERALTYPES_AR_RELEASE_MAJOR_VERSION       4U
#define LIN_GENERALTYPES_AR_RELEASE_MINOR_VERSION       8U
#define LIN_GENERALTYPES_AR_RELEASE_REVISION_VERSION    0U

/* Software Version Information */
#define LIN_GENERALTYPES_SW_MAJOR_VERSION               2U
#define LIN_GENERALTYPES_SW_MINOR_VERSION               4U

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/*The Lin identifier Type, (0 to 0x3F) together with its two parity bits */
typedef uint8 Lin_FramePidType;

/* Checksum model for the Lin Frame  */
typedef enum ETag_Lin_FrameCsModelType
{
  LIN_ENHANCED_CS = 0x00,
  LIN_CLASSIC_CS  = 0x01
} Lin_FrameCsModelType;

/* Lin Frame data length  */
typedef uint8 Lin_FrameDlType;

/* Lin Frame Type- Tx or Rx or anonymous */
typedef enum ETag_Lin_FrameResponseType
{
  LIN_FRAMERESPONSE_TX      = 0x00,
  LIN_FRAMERESPONSE_RX      = 0x01,
  LIN_FRAMERESPONSE_IGNORE  = 0x02
} Lin_FrameResponseType;

/* Lin PDU Type */
typedef struct STag_Lin_PduType
{
  Lin_FramePidType      Pid;
  Lin_FrameCsModelType  Cs;
  Lin_FrameResponseType Drc;
  Lin_FrameDlType       Dl;
  uint8 *SduPtr;
} Lin_PduType;

/* Lin channel status Type */
typedef enum ETag_Lin_StatusType
{
  LIN_NOT_OK           = 0x00,
  LIN_TX_OK            = 0x01,
  LIN_TX_BUSY          = 0x02,
  LIN_TX_HEADER_ERROR  = 0x03,
  LIN_TX_ERROR         = 0x04,
  LIN_RX_OK            = 0x05,
  LIN_RX_BUSY          = 0x06,
  LIN_RX_ERROR         = 0x07,
  LIN_RX_NO_RESPONSE   = 0x08,
  LIN_OPERATIONAL      = 0x09,
  LIN_CH_SLEEP         = 0x0A
} Lin_StatusType;

/* Lin slave error type */
typedef enum ETag_Lin_Slave_ErrorType
{
  LIN_ERR_HEADER        = 0x00,
  LIN_ERR_RESP_STOPBIT  = 0x01,
  LIN_ERR_RESP_CHKSUM   = 0x02,
  LIN_ERR_RESP_DATABIT  = 0x03,
  LIN_ERR_NO_RESP       = 0x04,
  LIN_ERR_INC_RESP      = 0x05
} Lin_SlaveErrorType;

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#endif /* LIN_GENERALTYPES_H */

/*******************************************************************************
**                          End Of File                                       **
*******************************************************************************/
