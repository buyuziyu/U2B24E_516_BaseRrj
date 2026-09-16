/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = App_SPI_Multi_Sample.c                                                                              */
/*====================================================================================================================*/
/*                                                COPYRIGHT                                                           */
/*====================================================================================================================*/
/* Copyright(c) 2019-2025 Renesas Electronics Corporation                                                             */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains sample application for SPI Driver Component                                                     */
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
/*              Devices:        X2x                                                                                   */
/*====================================================================================================================*/

/***********************************************************************************************************************
**                      Revision Control History                                                                      **
***********************************************************************************************************************/
/*
 * 2.5.1:  30/06/2025  : Remove SW-VERSION in file header
 * 2.5.0:  30/06/2025  : Update SW-VERSION for RH850/Ver21.01.00(D) U2Ax release
 * 2.4.0:  31/05/2025  : Update SW-VERSION for RH850/Ver21.01.01 U2Cx release
 * 2.3.2:  30/04/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 Release
 * 2.3.1:  31/03/2025  : Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02 Release
 * 2.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00(D) U2Bx Final Release
 * 2.1.3:  31/10/2024  : Update SW-VERSION up to 2.1.3
 * 2.1.2:  30/09/2024  : Update SW-VERSION up to 2.1.2
 *                     : Remove macro device in Init_MCAL
 * 2.1.0:  27/02/2024  : Update SW-VERSION to 2.1.0
 * 2.0.2:  14/12/2023  : Update SW-VERSION to 2.0.2
 * 2.0.1:  28/10/2023  : Updated SW-VERSION.
 * 2.0.0:  17/07/2023  : Updated SW-VERSION. Update to support Multi-core
 * 1.5.0:  29/03/2023  : Move Spi_Init() invoked before Port_Init()
 *         07/03/2023  : Updated SW-VERSION
 * 1.4.4:  20/07/2022  : Added Guard_Init into Init_MCAL
 * 1.4.2:  02/03/2022  : Updated SW-VERSION
 * 1.2.0:  17/07/2020  : Release
 * 1.1.0:  19/06/2020  : Release
 * 1.0.1:  19/05/2020  : Remove polling-flags to utilize barrier-sync
 * 1.0.0:  14/03/2019  : Initial Version
 */
/******************************************************************************/

/***********************************************************************************************************************
**                      Include Section                                                                               **
***********************************************************************************************************************/
#include "Std_Types.h"
#include "Spi.h"
#include "App_SPI_Device_Sample.h"
#include "App_SPI_Multi_Sample.h"
#include "App_SPI_Common_Sample_0.h"
#include "App_SPI_Common_Sample_1.h"
/***********************************************************************************************************************
**                            Macros                                                                                  **
***********************************************************************************************************************/


/***********************************************************************************************************************
**                        Global variables                                                                            **
***********************************************************************************************************************/
volatile uint8 App_GucSequenceControl = 0;
volatile uint8 App_GucKernelExcutionFlag = 0;
/***********************************************************************************************************************
**                        User function prototypes                                                                    **
***********************************************************************************************************************/

/***********************************************************************************************************************
*                      Function Definitions                                                                           **
***********************************************************************************************************************/

/***********************************************************************************************************************
** Function Name         : Spi_Init_Barrier_Sync
**
** Description           : Barrier-Synchronization initialization
***********************************************************************************************************************/
void Spi_Init_Barrier_Sync(void)
{
  /* Step_01: Set clear register BR0EN */
  /* Step_02: Set Barrier-Synchronization Participation enable for PE0 and PE1 */
  /* Step_03: Set clear registers BR0CHK0 to 3 and registers BR0SYNC0 to 3 by
             writing 1B to Barrier-Synchronization 0 Initialization Register */
  SPI_SYNC_BR0EN = SPI_SYNC_CLEAR;
  SPI_SYNC_BR0EN = (SPI_SYNC_ENABLE_PE0|SPI_SYNC_ENABLE_PE1);
  SPI_SYNC_BR0INIT = SPI_SYNC_INIT;
}

/***********************************************************************************************************************
** Function Name         : Spi_PassTo_PE0
**
** Description           : Enable barrier synchronization to pass the sequence
**                         to the application in the other instance
***********************************************************************************************************************/
void Spi_PassTo_PE0 (void)
{
  App_GucSequenceControl = 0;

  while (App_GucSequenceControl == 0)
  {
      /* No action required */
  }
}

/***********************************************************************************************************************
** Function Name         : Spi_PassTo_PE1
**
** Description           : Enable barrier synchronization to pass the sequence
**                         to the application in the other instance
***********************************************************************************************************************/
void Spi_PassTo_PE1 (void)
{
  App_GucSequenceControl = 1;

  while (App_GucSequenceControl == 1)
  {
      /* No action required */
  }
}

/***********************************************************************************************************************
** Function Name         : Spi_PassTo_PE1
**
** Description           : Enable barrier synchronization to pass the sequence
**                         to the application in the other instance
***********************************************************************************************************************/
void Spi_AllCoreRun (void)
{
  App_GucSequenceControl = 2;
}

/***********************************************************************************************************************
** Function Name         : Init_MCAL
**
** Description           : Init Mcu, Port, Spi
***********************************************************************************************************************/
Std_ReturnType Init_MCAL(void)
{
  /* Initialize Watchdog */
  Wdg_Init();

  /* Initialize MCU */
  Mcu_Init();

  /* Initialize GPT */
  Gpt_Init();

  /* Start timer for asynchronous transmission in polling mode */
  Gpt_Start();
  
  /* Initialize SPI */
  Spi_Init(Spi_Config);

  /* Initialize PORT */
  Port_Init();

  /* Initialize GUARD */
  Guard_Init();

  return E_OK;
}/* End of Init_MCAL() function */

/***********************************************************************************************************************
**                          End of File                                                                               **
***********************************************************************************************************************/
