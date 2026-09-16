/*============================================================================*/
/* Project      = RH850 X2x MCAL Ver22.01.00.D                                */
/* Module       = App_GPT_Multi_Sample.c                                      */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2020,2023-2025 Renesas Electronics Corporation. All rights reserved.   */
/*============================================================================*/
/* Purpose:                                                                   */
/* This file contains sample application for GPT Driver Component             */
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
 *  2.4.0  30/06/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.01.00 (D) release
 *  2.3.2  25/04/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03
 *  2.3.1  31/03/2025  : Update SW-VERSION for RH850/U2BxE MCAL
 *                       Ver22.00.02/Ver22.00.02.D Release
 *  2.3.0  28/02/2025  : Update SW-VERSION for
 *                       RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 *  2.2.0  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D
 *                       Final Release
 *  2.1.2  31/10/2024  : Update SW-VERSION for U2Bx Beta2 release
 *  2.1.1  30/08/2024  : Update Project Name
 *                     : Add global variable GblSyncFlag
 *  2.0.0  26/07/2023  : Remove multi-instance support
 *         12/05/2023  : Update SW version 2.0.0
 *  1.2.0  17/07/2020  : Release
 *  1.1.0  19/06/2020  : Release
 *  1.0.0  01/01/2020  : Initial Version
 */
/******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Std_Types.h"
#include "App_GPT_Device_Sample.h"
#include "App_GPT_Multi_Sample.h"
#include "App_GPT_Common_Sample_0.h"
#include "App_GPT_Common_Sample_1.h"
/*******************************************************************************
**                            Macros                                          **
*******************************************************************************/

/*******************************************************************************
**                        Global variables                                    **
*******************************************************************************/
volatile uint8 GaaNotificationEntered_global[10];
/* Global flag for sync information between cores */
volatile boolean GblSyncFlag = 0;
/*******************************************************************************
**                        User function prototypes                            **
*******************************************************************************/
extern void Clock_Init(void);
extern void Port_Init(void);
extern void Mcu_Init(void);
extern void Wdg_Init(void);
extern void Reg_Init(void);
/********************************************************************************
*                      Function Definitions                                  **
*******************************************************************************/

Std_ReturnType Init_MCAL(void)
{
  /* Initialize Clock */
  Clock_Init();
  /* Initialize MCU */
  Mcu_Init();
  /* Initialize the Port pins */
  Port_Init();
  /* Initialize the Watchdog timer */
  Wdg_Init();
  /* Initialization of the table reference bit in ICR register */
  Reg_Init();

  return E_OK;

}/* End of Init_MCAL() function */

/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
