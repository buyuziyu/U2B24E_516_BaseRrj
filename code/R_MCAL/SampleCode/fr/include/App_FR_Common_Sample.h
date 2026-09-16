/*============================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                         */
/* Module       = App_FR_Common_Sample.h                                      */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2018,2020-2025 Renesas Electronics Corporation. All rights reserved.   */
/*============================================================================*/
/* Purpose:                                                                   */
/* This application file contains declarations needed for sample test         */
/* application of FlexRay Driver                                              */
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
 * 2.4.1:   30/06/2025   : Remove SW-VERSION in file header
 * 2.4.0:   30/06/2025   : Update SW-VERSION for RH850/U2Ax MCAL Ver22.01.00(D) Final Release
 * 2.3.2:   29/04/2025   : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 Release
 *                       : As part of CCRH support, following changes are made:
 *                         1. Add Fr_GblInvoked, Fr_GucInvoked[] with volatile
 *                         2. Add preprocessor directive for macro CCRH
 * 2.3.1:   31/03/2025   : Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02 Release
 *                         As part of G4KH support for U2Bx-E, following changes are made:
 *                         + Add Mcu_Init()
 * 2.3.0:   28/02/2025   : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.1:   31/12/2024   : Update SW-VERSION for Ver22.00.01 U2Ax Release
 * 2.2.0:   31/12/2024   : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 * 2.1.3:   31/10/2024   : Update SW-VERSION to 2.1.3
 * 2.1.0:   24/02/2024   : Change SW-VERSION to 2.1.0
 * 2.0.1:   11/10/2023   : Add new variable Fr_output_data, Fr_59_Gstoutput_data
 *                         Fr_59_Gstoutput_table
 * 1.4.2:   09/05/2022   : Change SW-VERSION to 1.4.3
 * 1.4.2:   02/03/2022   : Change SW-VERSION to 1.4.2
 * 1.4.0:   11/10/2021   : Change SW-VERSION to 1.4.0
 * 1.3.2:   14/08/2021   : Change SW-VERSION to 1.3.2
 * 1.2.0:   19/06/2020   : Release
 * 1.1.0:   19/06/2020   : Release
 * 1.0.0:   15/06/2018   : Initial Version
 */
/******************************************************************************/

#ifndef APP_FR_COMMON_SAMPLE_H
#define APP_FR_COMMON_SAMPLE_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Fr_59_Renesas.h"

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/

#if defined CCRH
extern boolean volatile Fr_GblInvoked;
extern uint8 volatile Fr_GucInvoked[2];
#else
extern boolean Fr_GblInvoked;
extern uint8 Fr_GucInvoked[2];
#endif
extern VAR(Fr_59_Renesas_OutputPointerTableType, FR_DATA) Fr_59_Gstoutput_table[4];
extern VAR(Fr_59_Renesas_OutputDataStrType, FR_DATA) Fr_59_Gstoutput_data[4];
extern VAR(Fr_59_Renesas_OutputConstdataType, FR_DATA) Fr_output_data[6];

extern VAR(Fr_59_Renesas_InputConstdataType, FR_DATA) Fr_input_data[6];
extern VAR(Fr_59_Renesas_InputDataStrType, FR_DATA) Fr_59_Gstinput_data[4];
extern VAR(Fr_59_Renesas_InputPointerTableType, FR_DATA) Fr_59_Gstinput_table[4];

/* Function to invoke other init functions */
extern void Appl_Init(void);
/* Wait all nodes are completely awakened */
extern void WaitWakeup(void);
/* Need to init Clock for PE6 at PE0 */
extern void Mcu_Init(void);

#endif /* #ifndef APP_FR_COMMON_SAMPLE_H */

/*******************************************************************************
**                     End of file                                            **
*******************************************************************************/

