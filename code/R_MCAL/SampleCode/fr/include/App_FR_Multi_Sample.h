/*============================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                         */
/* Module       = App_FR_Common_Sample.h                                      */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2024-2025 Renesas Electronics Corporation. All rights reserved.        */
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
 *                         1. Add GucStubInitFlag, GblPE0Done, GblPE1Done with volatile
 *                         2. Add preprocessor directive for macro CCRH
 * 2.3.1:   31/03/2025   : Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02 Release
 * 2.3.0:   28/02/2025   : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 *                         As per multicore support, following changes are made:
 *                         + add GblPE1Done, GblPE0Done
 * 2.2.1:   31/12/2024   : Update SW-VERSION for Ver22.00.01 U2Ax Release
 * 2.2.0:   31/12/2024   : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 * 2.1.3:   31/10/2024   : Update SW-VERSION to 2.1.3
 * 2.1.1:   16/05/2024   : Initial Version
 */
/******************************************************************************/

#ifndef APP_FR_MULTI_SAMPLE_H
#define APP_FR_MULTI_SAMPLE_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Fr_59_Renesas.h"

/*******************************************************************************
**                      Global variables                                      **
*******************************************************************************/
#if defined CCRH || defined IAR
extern uint8 volatile GucStubInitFlag;
extern boolean volatile GblPE0Done;
extern boolean volatile GblPE1Done;
#else
extern uint8 GucStubInitFlag;
extern boolean GblPE0Done;
extern boolean GblPE1Done;
#endif
/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/

/* Function to invoke other init functions */
extern void Appl_Init(void);
/* Wait all nodes are completely awakened */
extern void WaitWakeup(void);

extern void sample_end(void);

extern void BoundIntToPEMax(void);
#endif /* #ifndef APP_FR_COMMON_SAMPLE_H */

/*******************************************************************************
**                     End of file                                            **
*******************************************************************************/

