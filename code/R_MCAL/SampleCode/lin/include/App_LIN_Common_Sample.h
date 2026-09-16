/*============================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                         */
/* Module       = App_LIN_Common_Sample.h                                     */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2017-2025 Renesas Electronics Corporation. All rights reserved.        */
/*============================================================================*/
/* Purpose:                                                                   */
/* This file contains macros/function prototypes/variables required for       */
/* source application file.                                                   */
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
 * 2.4.0:  30/06/2025  : Remove the SW-VERSION from header of file
 * 2.3.2:  25/04/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03
 *                       Release
 * 2.3.1:  31/03/2025  : Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02
 *                       Release
 * 2.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL
 *                       Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00(D) U2Bx Final Release
 * 2.1.2:  31/10/2024  : Update SW-VERSION
 * 2.1.1:  30/08/2024  : As part of U2BxE support, following changes are made:
 *                       1. Add precondition for U2BxE
 *                       As part of multi-core and post build variant support,
 *                       following changes are made:
 *                       1. Add macro LIN_WAIT_MS(t)
 *                       2. Remove redudant parameter after update include
 *                       header file
 * 2.0.1:  29/10/2023  : Update macro "LIN_MAX_TIMEOUT_COUNT" for U2Cx device
 * 2.0.0:  18/07/2023  : Update to correct for Sample app after update code
 *                       to support multicore
 *         03/07/2023  : Update Sample App to cover Slave mode
 *         14/05/2023  : Remove redundant precondition for U2Bx
 * 1.4.4:  13/06/2022  : Update SW-VERSION to 1.4.4
 * 1.4.3:  14/04/2022  : Update SW-VERSION to 1.4.3
 * 1.4.2:  04/03/2022  : Update SW-VERSION
 * 1.4.1:  13/12/2021  : Update LIN_MAX_TIMEOUT_COUNT for U2Bx
 * 1.2.0:  26/08/2020  : Release
 *         11/11/2021  : Add condition for U2Bx 
 * 1.1.0:  19/06/2020  : Release
 * 1.0.2:  25/03/2020  : Update Common/Date, Version format
 * 1.0.1:  08/03/2018  : QAC improvement
 * 1.0.0:  31/03/2017  : Initial Version
 *
 */
/******************************************************************************/
#ifndef APP_LIN_COMMON_SAMPLE_H
#define APP_LIN_COMMON_SAMPLE_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Compiler.h"
#include "Std_Types.h"
#include "Lin_GeneralTypes.h"
#include "LinIf.h"
/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/
#define LIN_COUNT_INITIAL_VALUE           (uint8)0x00
#define LIN_DATA_SIZE                     (uint8)0x08
#define LIN_WAIT_5MS                      (uint8)0x05
#define LIN_SEND_PID                      (uint8)0xDD
#define LIN_RESP_PID                      (uint8)0x39
#define LIN_CHANNEL_MASTER                (uint8)0x00
#define LIN_CHANNEL_SLAVE                 (uint8)0x01
#if (DEVICE == E2x)
#define LIN_MAX_TIMEOUT_COUNT             (uint8)0x04
#elif (DEVICE == U2Ax)
#define LIN_MAX_TIMEOUT_COUNT             (uint8)0x03
#elif (DEVICE == U2Bx || DEVICE == U2BxE)
#define LIN_MAX_TIMEOUT_COUNT             (uint8)0x04
#elif (DEVICE == U2Cx)
#define LIN_MAX_TIMEOUT_COUNT             (uint8)0x04
#endif //#if (DEVICE == E2x)
#define LIN_WAIT_MS(t)  { volatile uint32 cnt; \
  for ( cnt = 0;cnt < (((uint32)360 * ((uint32)t)) + (uint32)1);cnt++ ); }
/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

extern void Appl_Scheduler_Task(void);
extern void Appl_Lin_Init(void);

/* Timer ISR */
extern _INTERRUPT_ void Timer0_Interrupt(void);

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/


#endif /* APP_LIN_COMMON_SAMPLE_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
