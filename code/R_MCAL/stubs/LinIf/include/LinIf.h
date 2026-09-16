/*============================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                         */
/* Module       = LinIf.h                                                     */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2023 - 2025 Renesas Electronics Corporation. All rights reserved.      */
/*============================================================================*/
/* Purpose:                                                                   */
/* This file is a stub for LinIf Component                                    */
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
/* to lost profits) regardless of whLINer such liability is based on breach   */
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
 * 2.4.0      30/06/2025     Remove the SW-VERSION from header of file
 * 2.3.2      25/04/2025     Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03
 *                           Release
 * 2.3.1      31/03/2025     Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02
 *                           Release
 * 2.3.0      28/02/2025     Update SW-VERSION for RH850/U2Cx MCAL
 *                           Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0      31/12/2024     Update SW-VERSION for Ver22.02.00(D) U2Bx Final
 *                           Release
 * 2.1.2      31/10/2024     Add new parameter "GucWakeupCount"
 * 2.1.1      17/05/2024     Add Version Information
 * 2.1.0      23/02/2024     Update SW-VERSION to 2.1.0
 * 2.0.1      22/09/2023     Initial Version
 */

#ifndef LINIF_H
#define LINIF_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "EcuM.h"
#include "ComStack_Types.h"
#include "Lin_GeneralTypes.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR Specification Version Information */
#define LINIF_AR_RELEASE_MAJOR_VERSION       4U
#define LINIF_AR_RELEASE_MINOR_VERSION       8U
#define LINIF_AR_RELEASE_REVISION_VERSION    0U

/* Software Version Information */
#define LINIF_SW_MAJOR_VERSION               2U
#define LINIF_SW_MINOR_VERSION               4U

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/
#define NUM_CPU                                                     (uint8)0x06U
/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
extern uint8 GblLinIfHeaderReceivedFlag[NUM_CPU];
extern uint8 GblLinIfRxReceivedFlag[NUM_CPU];
extern uint8 GblLinIfTxTransmitFlag[NUM_CPU];

extern uint8 GblLinIfErrorHeaderErrorFlag[NUM_CPU];
extern uint8 GblLinIfErrorFramingResponseErrorFlag[NUM_CPU];
extern uint8 GblLinIfErrorChecksumErrorFlag[NUM_CPU];
extern uint8 GblLinIfErrorDataBitResponseErrorFlag[NUM_CPU];
extern uint8 GblLinIfErrorNoResponseFlag[NUM_CPU];
extern uint8 GblLinIfErrorIncompleteResponseFlag[NUM_CPU];

extern uint8 LIN_CHANNEL_ID[NUM_CPU];

extern Lin_PduType Linif_GstSlavePdu[NUM_CPU];

// extern uint8 GucWakeupCount[NUM_CPU];

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

/* Wakeup Confirmaton event referring to a LIN Network */
extern void LinIf_WakeupConfirmation( EcuM_WakeupSourceType WakeupSource);

extern Std_ReturnType LinIf_HeaderIndication( NetworkHandleType Channel, Lin_PduType* Pduptr);

extern void LinIf_RxIndication( NetworkHandleType Channel, uint8* Pduptr);

extern void LinIf_TxConfirmation( NetworkHandleType Channel);

extern void LinIf_LinErrorIndication( NetworkHandleType Channel, Lin_SlaveErrorType ErrorStatus);

#endif /* LINIF_CBK_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
