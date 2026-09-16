/*====================================================================================================================*/
/* Project      = RH850/X2x AR4 MCAL Development                                                                      */
/* Module       = Pwm_DIAG_Ram.h                                                                                      */
/*                                                                                                                    */
/*====================================================================================================================*/
/*                                              COPYRIGHT                                                             */
/*====================================================================================================================*/
/* (c) 2021-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Global variable definitions of PWM Driver                                                                          */
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
/*                                              Devices:        X2x                                                   */
/*====================================================================================================================*/
/***********************************************************************************************************************
**                                              Revision Control History                                              **
***********************************************************************************************************************/
/*                                                                                                                    **
 * 2.5.1: 30/06/2025 : Remove SW-VERSION in header comment                                                            **
 * 2.5.0: 30/06/2025 : Update SW-VERSION for U2Ax Ver22.01.00(D) Final Release                                        **
 * 2.4.0: 31/05/2025 : Update SW-VERSION for U2Cx Ver21.01.01 Final Release                                           **
 * 2.3.2: 29/04/2025 : Update SW-VERSION for U2Ax Ver22.00.04 Beta Release                                            **
 * 2.3.1: 31/03/2025 : Update SW-VERSION for U2Ax Ver22.00.03 Beta2 Release                                           **
 * 2.3.0: 28/02/2025 : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release                        **
 * 2.2.0: 31/12/2024 : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release                                  **
 * 2.1.2: 31/10/2024 : Update SW-VERSION for Ver22.00.05 U2Cx Beta2 Release                                           **
 * 2.0.2: 14/12/2023 : Update version in header comment                                                               **
 * 2.0.1: 25/10/2023 : Update version in header comment                                                               **
 * 2.0.0: 05/07/2023 : Update from "Pwm_Mapping.h to "Pwm_MemMap.h". Remove #ifdef PWM_INSTANCE_INDEX                 **
 *                     Update START/STOP_SEC_VAR_INIT_UNSPECIFIED to START/STOP_SEC_CONST_PTR for Pwm_DiagFunc        **
 *                     Remove message 0841                                                                            **
 * 1.0.0: 23/08/2021 : Initial Version.                                                                               **
 *                                                                                                                    */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                              Include Section                                                       **
***********************************************************************************************************************/

#ifndef PWM_DIAG_RAM_H
#define PWM_DIAG_RAM_H

#include "Pwm_DIAG_PBTypes.h"
/***********************************************************************************************************************
**                                              Version Information                                                   **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define PWM_DIAG_RAM_AR_RELEASE_MAJOR_VERSION      PWM_AR_RELEASE_MAJOR_VERSION
#define PWM_DIAG_RAM_AR_RELEASE_MINOR_VERSION      PWM_AR_RELEASE_MINOR_VERSION
#define PWM_DIAG_RAM_AR_RELEASE_REVISION_VERSION   PWM_AR_RELEASE_REVISION_VERSION

/* Software module version information */
#define PWM_DIAG_RAM_SW_MAJOR_VERSION              PWM_SW_MAJOR_VERSION
#define PWM_DIAG_RAM_SW_MINOR_VERSION              PWM_SW_MINOR_VERSION
#define PWM_DIAG_RAM_SW_PATCH_VERSION              PWM_SW_PATCH_VERSION

/***********************************************************************************************************************
**                                              Global configuration constants                                        **
***********************************************************************************************************************/
#if (PWM_DIAG_UNIT_USED == STD_ON)

#define PWM_START_SEC_VAR_NO_INIT_PTR
#include "Pwm_MemMap.h"

extern P2CONST(Pwm_DiagUnitConfigType, PWM_VAR_NO_INIT, PWM_CONFIG_DATA) Pwm_GpDiagConfig;

#define PWM_STOP_SEC_VAR_NO_INIT_PTR
#include "Pwm_MemMap.h"

#define PWM_START_SEC_CONST_PTR
#include "Pwm_MemMap.h"

extern CONST(Pwm_HwFuncTableType, PWM_CONST) Pwm_DiagFunc;

#define PWM_STOP_SEC_CONST_PTR
#include "Pwm_MemMap.h"

#endif /* End of PWM_DIAG_UNIT_USED == STD_ON */
#endif /* End of PWM_DIAG_RAM_H */
/***********************************************************************************************************************
**                                              End of File                                                           **
***********************************************************************************************************************/
