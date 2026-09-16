/*============================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                         */
/* Module       = App_ICU_Multi_Sample.h                                      */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.        */
/*============================================================================*/
/* Purpose:                                                                   */
/* Header file information for application.                                   */
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
 * 2.4.1:  30/06/2025  : Remove SW-VERSION in file header
 * 2.4.0:  30/05/2025  : Update SW-VERSION for RH850/U2Cx MCAL 
 *                       Ver22.01.01 Release
 * 2.3.1:  31/03/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 
 *                       and RH850/U2Bx-E MCAL Ver22.00.02 Release
 * 2.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL
 *                       Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D 
 *                       Final Release
 * 2.1.2:  31/10/2024  : As part of support GTM HWIP into common sample app, 
 *                       following changes are made:
 *                       1. Remove function sample_end add new Guard_Enable_PE
 * 2.0.1:  25/10/2023  : Update SW-VERSION to 2.0.1
 * 1.4.4:  28/06/2022  : Update EIBD configuration for U2Bx
 *         13/09/2022  : Update EIBD configuration for U2Cx
 * 1.2.0:  17/07/2020  : Release
 * 1.1.0:  19/06/2020  : Release
 * 1.0.0:  25/03/2020  : Initial Version
 */
/******************************************************************************/
#ifndef APP_ICU_MULTI_SAMPLE_H
#define APP_ICU_MULTI_SAMPLE_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "Std_Types.h"
#include "Icu.h"
#include "Icu_Kernel.h"
#include "Icu_Ram.h"
#include "App_Icu_Common_Sample.h"
#include "App_ICU_Device_Sample.h"
/***********************************************************************************************************************
**                                                  Global Symbols                                                    **
***********************************************************************************************************************/
//Global flag for sync information between cores
extern volatile boolean GblSyncFlag;
#define ICU_SMT_VALUE  3 /* Signal Measurement Target Value */
#define ICU_TST_VALUE  8 /* Time Stamps Target Value */

/***********************************************************************************************************************
**                                            Global Function Prototypes                                              **
***********************************************************************************************************************/
void Guard_Enable_PE(void);
/* Check the request has been executed or not */
extern boolean CheckSlaveRequest(uint8 channel_index, uint8 api_id);

#endif /* End of APP_ICU_MULTI_SAMPLE_H */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
