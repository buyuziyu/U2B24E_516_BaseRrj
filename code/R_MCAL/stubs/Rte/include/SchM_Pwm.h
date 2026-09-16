/*============================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                         */
/* Module       = SchM_Pwm.h                                                  */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2022-2025 Renesas Electronics Corporation. All rights reserved.        */
/*============================================================================*/
/* Purpose:                                                                   */
/* This file is a stub for SchM Component                                     */
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
 * 2.4.0:  30/06/2025  : Update SW-VERSION for U2Ax Ver22.01.00(D) Final Release
 * 2.3.2:  29/04/2025  : Update SW-VERSION for U2Ax Ver22.00.04 Beta Release
 * 2.3.1:  31/03/2025  : Update SW-VERSION for Ver22.00.03 Release
 * 2.3.0:  28/02/2025  : Update TOOL-VERSION for RH850/U2Cx MCAL
 *                       Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final 
 *                       Release
 * 2.1.2:  31/10/2024  : Update SW-VERSION to 2.1.2
 * 2.1.1:  27/06/2024  : Update SW-VERSION to 2.1.1
 * 2.1.0:  23/02/2024  : Update SW-VERSION to 2.1.0
 * 2.0.0:  27/06/2023  : Add Enter/Exit_INTERRUPT_CONTROL_PROTECTION_GLOBAL and
 *                       Enter/Exit_RAM_DATA_PROTECTION_GLOBAL
 * 1.4.5:  28/09/2022  : Initial Version
 */
/******************************************************************************/
#ifndef SCHM_PWM_H
#define SCHM_PWM_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Std_Types.h"

/*******************************************************************************
**                      Version Information                                  **
*******************************************************************************/

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

extern void SchM_Enter_Pwm_PWM_INTERRUPT_CONTROL_PROTECTION(void);
extern void SchM_Exit_Pwm_PWM_INTERRUPT_CONTROL_PROTECTION(void);
extern void SchM_Enter_Pwm_PWM_INTERRUPT_CONTROL_PROTECTION_GLOBAL(void);
extern void SchM_Exit_Pwm_PWM_INTERRUPT_CONTROL_PROTECTION_GLOBAL(void);
extern void SchM_Enter_Pwm_PWM_RAM_DATA_PROTECTION_GLOBAL(void);
extern void SchM_Exit_Pwm_PWM_RAM_DATA_PROTECTION_GLOBAL(void);
#endif /* SCHM_PWM_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
