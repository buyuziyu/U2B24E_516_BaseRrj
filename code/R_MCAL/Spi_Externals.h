/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Spi_Externals.h                                                                                     */
/* SW-VERSION   = 2.2.0                                                                                               */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* Copyright(c) 2023-2024 Renesas Electronics Corporation.                                                            */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains the type definitions for post-build time parameters                                             */
/*====================================================================================================================*/
/*                                                                                                                    */
/* Unless otherwise agreed upon in writing between your company and Renesas Electronics Corporation the following     */
/* shall apply!                                                                                                       */
/*                                                                                                                    */
/* Warranty Disclaimer                                                                                                */
/*                                                                                                                    */
/* There is no warranty of any kind whatsoever granted by Renesas. Any warranty is expressly disclaimed and excluded  */
/* by Renesas, either expressed or implied, including but not limited to those for non-infringement of intellectual   */
/* property, merchantability and/or fitness for the particular purpose.                                               */
/*                                                                                                                    */
/* Renesas shall not have any obligation to maintain, service or provide bug fixes for the supplied Product(s) and/or */
/* the Application.                                                                                                   */
/*                                                                                                                    */
/* Each User is solely responsible for determining the appropriateness of using the Product(s) and assumes all risks  */
/* associated with its exercise of rights under this Agreement, including, but not limited to the risks and costs of  */
/* program errors, compliance with applicable laws, damage to or loss of data, programs or equipment, and             */
/* unavailability or interruption of operations.                                                                      */
/*                                                                                                                    */
/* Limitation of Liability                                                                                            */
/*                                                                                                                    */
/* In no event shall Renesas be liable to the User for any incidental, consequential, indirect, or punitive damage    */
/* (including but not limited to lost profits) regardless of whether such liability is based on breach of contract,   */
/* tort, strict liability, breach of warranties, failure of essential purpose or otherwise and even if advised of the */
/* possibility of such damages. Renesas shall not be liable for any services or products provided by third party      */
/* vendors, developers or consultants identified or referred to the User by Renesas in connection with the Product(s) */
/* and/or the Application.                                                                                            */
/*                                                                                                                    */
/*====================================================================================================================*/
/* Environment:                                                                                                       */
/*              Devices:        X2x                                                                                   */
/*====================================================================================================================*/

/***********************************************************************************************************************
**                                              Revision Control History                                              **
***********************************************************************************************************************/
/*
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00(D) U2Bx Final Release
 * 2.1.3:  31/10/2024  : Update SW-VERSION up to 2.1.3
 * 2.1.2:  30/09/2024  : Update SW-VERSION up to 2.1.2
 * 2.1.0:  27/02/2024  : Update SW-VERSION to 2.1.0
 * 2.0.2:  14/12/2023  : Update SW-VERSION to 2.0.2
 * 2.0.1:  28/10/2023  : Updated SW-VERSION.
 * 2.0.0:  10/05/2023  : Initial version
 */

#ifndef SPI_EXTERNALS_H
#define SPI_EXTERNALS_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Prototypes                            **
*******************************************************************************/
#define SPI_START_SEC_APPL_CODE
#include "Spi_MemMap.h"

extern FUNC(void, SPI_APPL_CODE) SpiJob0Notification(void);
extern FUNC(void, SPI_APPL_CODE) SpiSequence0EndNotification(void);
extern FUNC(void, SPI_APPL_CODE) SpiJob0Notification_0(void);
extern FUNC(void, SPI_APPL_CODE) SpiSequence0EndNotification_0(void);
extern FUNC(void, SPI_APPL_CODE) SpiSequence0StartNotification_0(void);
extern FUNC(void, SPI_APPL_CODE) SpiJob0Notification_1(void);
extern FUNC(void, SPI_APPL_CODE) SpiSequence0EndNotification_1(void);
extern FUNC(void, SPI_APPL_CODE) SpiSequence0StartNotification_1(void);


#define SPI_STOP_SEC_APPL_CODE
#include "Spi_MemMap.h"

#endif /* SPI_EXTERNALS_H */

/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
