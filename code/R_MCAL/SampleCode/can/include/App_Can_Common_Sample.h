/*============================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                         */
/* Module       = App_CAN_Common_Sample.h                                     */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2018-2025 Renesas Electronics Corporation. All rights reserved.        */
/*============================================================================*/
/* Purpose:                                                                   */
/* Header file information for application                                    */
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
 * 2.4.1: 30/06/2025  : Remove the SW-VERSION from header of file
 * 2.4.0: 30/05/2025  : Update SW-VERSION for RH850/Ver22.01.00 (D) U2Ax Release
 * 2.3.1: 31/03/2025  : Add macro support G4KH core for U2Bx-E devive
 *                      Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 * 2.3.0: 28/02/2025  : Update SW-VERSION for RH850/Ver22.01.00/Ver22.01.00.D 
 *                      Final Release
 * 2.2.0: 31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final 
 *                      Release
 * 2.1.3: 31/10/2024  : Update to support CANXL frame
 * 2.1.2: 30/09/2024  : Update to support CANXL frame
 * 1.3.2: 30/08/2021  : Update to support multi-instance
 * 1.3.1: 05/05/2021  : Update the memory section, memclass, ptrclass to change
 *                      the CAN_RSCAN prefix to CAN
 * 1.2.0: 09/07/2020  : Release.
 * 1.1.0: 19/06/2020  : Release.
 * 1.0.2: 19/03/2020  : Changed from __interrupt to _INTERRUPT_
 * 1.0.1: 02/07/2019  : - Added Wdg_Init() function.
 *                      - Update new format for revision
 * 1.0.0: 15/06/2018  : Initial Version
 */
/******************************************************************************/
#ifndef APP_CAN_COMMON_SAMPLE_H
#define APP_CAN_COMMON_SAMPLE_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "Std_Types.h"

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/
/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

extern void Clock_Init(void);
/* Timer Initialization */
extern void Gpt_Init(void);
/* Controller Port(s) Initialization */
extern void Port_Init(void);
/* Watchdog Initialization */
extern void Wdg_Init(void);
/* System Initialization */
extern void Mcu_Init(void);
/* Timer Task */
extern _INTERRUPT_ void Timer_Task(void);

extern void Switch_To_ControllerId(uint8 controller);

#if defined (CAN_U2BxE_USED) && defined (RUN_OTHER_PE)
#define CAN_EIC_EIBDOSTM    (*((volatile uint16 *)0xFFF825A0UL)) /* EIC360 */
#endif

#endif /* APP_CAN_COMMON_SAMPLE_H */

/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
