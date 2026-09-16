/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2X MCAL Components                                                                 */
/* Module       = App_OCU_Multi_Sample.h                                                                              */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2023-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Header file information for application.                                                                           */
/*                                                                                                                    */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Provision of API and database declaration, Service Id and DET error Macros                                         */
/* and Module version information Macros.                                                                             */
/*                                                                                                                    */
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
 *  1.4.1  30/06/2025  : Add PE synchronous register, function
 *  1.4.0  30/05/2025  : Add GblSyncFlagChannel and update size of GaaNotificationEntered
 *  1.3.1  31/03/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 and RH850/U2Bx-E MCAL Ver22.00.02 Release
 *  1.3.0  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 *  1.2.0  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 *  1.0.0  04/04/2023  : Initial Version.
 */
/**********************************************************************************************************************/
/**********************************************************************************************************************/
#ifndef APP_OCU_MULTI_SAMPLE_H
#define APP_OCU_MULTI_SAMPLE_H

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/

#include "Std_Types.h"
#include "Ocu.h"
#include "Ocu_Kernel.h"
#include "App_OCU_Device_Sample.h"
/***********************************************************************************************************************
**                                                  Global Symbols                                                    **
***********************************************************************************************************************/
//Global flag for sync information between cores
extern volatile boolean GblSyncFlag;
extern volatile uint16 GaaNotificationEntered[8];

/* Used for X2x devices */
extern volatile boolean GblCore0SyncInit;
extern volatile boolean GblCore1SyncInit;
/* Barrier-Synchronization init Register */
#define BR0INIT                  *(volatile uint8*)(0xFFFB8000UL)
/*Barrier-Synchronization n Barrier Participating PE setting Register*/
#define BR0EN                    *(volatile uint8*)(0xFFFB8004UL)
/*Barrier-Synchronization n - barrier check self-register*/
#define BR0CHKS                  *(volatile uint8*)(0xFFFB8100UL)
/*Barrier-Synchronization n – barrier synchronization completion self-register*/
#define BR0SYNCS                 *(volatile uint8*)(0xFFFB8104UL)
/*arrier-Synchronization n Barrier Check Register m*/
#define BR0CHK0                  *(volatile uint8*)(0xFFFB8800UL)
#define BR0CHK1                  *(volatile uint8*)(0xFFFB8900UL)

/*Barrier-Synchronization n Barrier Synchronization Completion Register m*/
#define BR0SYNC0                 *(volatile uint8*)(0xFFFB8804UL)
#define BR0SYNC1                 *(volatile uint8*)(0xFFFB8904UL)
#define OCU_SYNC_INIT                           BR0INIT
#define OCU_SYNC_PARTICIPATING_PE_EN            BR0EN
#define OCU_SYNC_CHECK_0_PE0                    BR0CHK0
#define OCU_SYNC_CHECK_0_PE1                    BR0CHK1
#define OCU_SYNC_COMPLETION_PE0                 BR0SYNC0
#define OCU_SYNC_COMPLETION_PE1                 BR0SYNC1
#define OCU_SYNC_CLEAR               0x01UL
#define OCU_SYNC_START_PE0           0x01UL
#define OCU_SYNC_START_PE1           0x01UL << 1
#define OCU_SYNC_ENABLE              0x01UL
#define OCU_SYNC_COMPLETION          0x01UL
#define OCU_SYNC_UNCOMPLETION        0x00UL
/***********************************************************************************************************************
**                                            Global Function Prototypes                                              **
***********************************************************************************************************************/
/* Used for X2x devices */
extern void OCU_SYNC_CORE(void);
extern void PE0_SYNC(void);
extern void PE1_SYNC(void);
extern void PE0_SYNC_INIT_CHECK(void);
extern void PE1_SYNC_INIT_CHECK(void);

/* Trap CPU at the end of the application */
extern void sample_end(void);

/* Check the request has been executed or not */
extern boolean CheckSlaveRequest(uint8 channel_index, uint8 api_id);

#endif /* End of APP_OCU_MULTI_SAMPLE_H */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
