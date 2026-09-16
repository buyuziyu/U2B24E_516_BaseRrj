/*============================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                         */
/* Module       = CanXLTrcv.c                                                 */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* Copyright(c) 2024, 2025 Renesas Electronics Corporation.                   */
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
/*              Devices:        CPF                                           */
/*============================================================================*/

/*******************************************************************************
**                      Revision History                                      **
*******************************************************************************/
/*
 * 2.4.1:  30/06/2025  : Remove the SW-VERSION from header of file
 * 2.4.0:  30/05/2025  : Update SW-VERSION for RH850/Ver22.01.01 U2Cx Release
 * 2.3.1:  31/03/2025  : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 * 2.3.0:  28/02/2025  : Update SW-VERSION for RH850/Ver22.01.00/Ver22.01.00.D 
 *                       Final Release
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D
 *                       Final Release
 * 2.1.3:  31/10/2024  : Update SW Version
 * 2.1.2:  30/09/2024  : Update SW Version
 * 2.1.0:  06/03/2024  : Update SW-VERSION to 2.1.0
 * 2.0.3:  12/04/2024  : Initial Version
 */
/******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanXLTrcv.h"
#include "CanIf.h"
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

/*******************************************************************************
**                         Global Data                                        **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
                              CanXLTrcv_ReportErrorState
*******************************************************************************/
Std_ReturnType CanXLTrcv_ReportErrorState(uint8 Transceiver,
                                      Can_ErrorStateType ErrorState)
{
  (void)Transceiver;
  (void)ErrorState;
  return E_OK;
}

/*******************************************************************************
                          End of the file
*******************************************************************************/
