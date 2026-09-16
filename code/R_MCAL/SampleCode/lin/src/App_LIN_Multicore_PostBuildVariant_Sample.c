/*============================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                         */
/* Module       = App_LIN_Common_Sample.c                                     */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2024-2025 Renesas Electronics Corporation. All rights reserved.        */
/*============================================================================*/
/* Purpose:                                                                   */
/* This file contains sample application for LIN Driver Component             */
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
 *                       Add ASM_NOP() to support IAR compiler
 * 2.3.2:  25/04/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03
 *                       Release
 *                       Add ASM_NOP() to support CCRH compiler
 * 2.3.1:  31/03/2025  : Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02
 *                       Release
 * 2.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL
 *                       Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00(D) U2Bx Final Release
 * 2.1.2:  31/10/2024  : Update SW-VERSION
 * 2.0.3:  13/04/2024  : Initialize version for SA support multi-core and
 *                       post build variant
 */
/******************************************************************************/

/*******************************************************************************
**                     Include Section                                        **
*******************************************************************************/
#include "App_LIN_Multi_Sample.h"
#include "App_LIN_Device_Sample.h"
#include "App_LIN_Common_Sample_0.h"
#include "App_LIN_Common_Sample_1.h"

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/
volatile uint8 GucStubInitFlag = 0;
volatile uint8 GucStubVariantFlag0 = 0;
volatile uint8 GucStubVariantFlag1 = 0;
/******************************************************************************
* F U N C T I O N    D E F I N I T I O N S
******************************************************************************/
void sample_end(void)
{
  if (GET_BIT(APP_RESF, APP_MCU_RESF_BIT_POS) == APP_MCU_RST_FLAG_VALUE)
  {
    ASM_NOP();// Not required
  }
  else
  {
    /* Initialize the watchdog in the first variant */
    Mcu_Reset();
  }
  
  while (1)
  {
    ASM_NOP();/* No action required*/
  }
}
/*****************************************************************************
                        LIN Module Initialization
*****************************************************************************/
void Init_MCAL(void)
{
  Guard_Enable_PE();
  /* System Initialisation
   * Clock Initialisation, Programmable Peripheral I/O register, selecting
   * the clock for the LIN Module */
  /* Clock Initialisation */
  Clock_Init();

  /* Initialize the watchdog */
  Wdg_Init();
  
  /* System Initialisation */
  Mcu_Init();
  
  /* LIN Port Pin Configuration */
  Port_Init();

  /* LIN Global as well as Channel initialisation */
  Appl_Lin_Init();
}
/*******************************************************************************
                              Timer Interrupt routine
*******************************************************************************/

/****************************************************************************
                          End of the file
****************************************************************************/
