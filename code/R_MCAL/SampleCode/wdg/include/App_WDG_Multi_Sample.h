/*============================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                         */
/* Module       = App_WDG_Multi_Sample.h                                      */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.        */
/*============================================================================*/
/* Purpose:                                                                   */
/* Sample Application Common header file.                                     */
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
 * 2.4.1:  30/06/2025    : Remove SW-VERSION in file header    
 * 2.4.0: 30/06/2025     : Update SW-VERSION for                               
 *                         RH850/Ver22.01.00 (D) U2Ax release
 * 2.3.1:  31/03/2025    : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E   
 * 2.3.0:  28/02/2025    : Update SW-VERSION for RH850/U2Cx MCAL                
 *                         Ver22.01.00/Ver22.01.00.D Release   
 * 2.2.0:  31/12/2024    : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D
 *                         Final release
 * 2.1.2:  30/10/2024    : Update SW-VERSION to 2.1.2
 * 2.1.1:  31/08/2024    : Update SW-VERSION to 2.1.1
 * 2.0.0:  08/08/2023    : Update Sample app for supporting multicore
 * 1.4.3:  10/05/2022    : Release
 * 1.2.0:  26/08/2020    : Release
 * 1.1.0:  19/06/2020    : Release
 * 1.0.0:  20/03/2020    : Initial Version
 */
/******************************************************************************/
#ifndef APP_WDG_MULTI_SAMPLE_H
#define APP_WDG_MULTI_SAMPLE_H

/*******************************************************************************
**                     Include Section                                        **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Std_Types.h"
#include "App_WDG_Device_Sample.h"
/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/
extern Std_ReturnType Init_MCAL(void);

/* The flag synchronous between multi core in order to excluusive control */
extern volatile uint8 Wdg_GucInitSyncFlag;
extern volatile uint8 Wdg_GucInitSuccessFlag;

/* The register for inter core exclucive control */

/* For U2x */
/* Barrier-Synchronization n Initialization Register */
#define BR0INIT                  *(volatile uint8*)(0xFFFB8000UL)
/*Barrier-Synchronization n Barrier Participating PE setting Register*/
#define BR0EN                    *(volatile uint8*)(0xFFFB8004UL)
/*Barrier-Synchronization n - barrier check self-register*/
#define BR0CHKS                  *(volatile uint8*)(0xFFFB8110UL)
/*Barrier-Synchronization n - barrier synchronization completion self-register*/
#define BR0SYNCS                 *(volatile uint8*)(0xFFFB8114UL)
/*arrier-Synchronization n Barrier Check Register m*/
#define BR0CHK0                  *(volatile uint8*)(0xFFFB8800UL)
#define BR0CHK1                  *(volatile uint8*)(0xFFFB8900UL)
/*Barrier-Synchronization n Barrier Synchronization Completion Register m*/
#define BR0SYNC0                 *(volatile uint8*)(0xFFFB8804UL)
#define BR0SYNC1                 *(volatile uint8*)(0xFFFB8904UL)
/* Macro to set PE0 and PE1 to participate to synchronization */
#define WDG_PARTICIPATE_SYNC_PE0_PE1          0x03UL
/* Macro to clear BR0CHK0 to 3 and BR0SYNC0 to 3 */
#define WDG_SYNC_CLEAR                        0x01UL
#define BR0EN_CLEAR                           0x00UL
#define WDG_SYNC_ENABLE                       0x01UL
#define WDG_SYNC_COMPLETE                     0x01UL
/* Exclusive Status */
#define WDG_GETTING                           0xAAAAAAAAUL
#define WDG_RELEASE                           0x00000000UL

/*******************************************************************************
**                       Function Prototypes                                  **
*******************************************************************************/

#endif /* APP_WDG_COMMON_SAMPLE */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
