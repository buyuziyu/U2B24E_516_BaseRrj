/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = SchM_Ocu.c                                                                                          */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2023-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This application file contains the Schm LIN Stub functions.                                                        */
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
/*              Devices:        X2x                                                                                   */
/*====================================================================================================================*/

/***********************************************************************************************************************
**                                              Revision Control History                                              **
***********************************************************************************************************************/
/*
 * 1.4.0:  30/05/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.01
 * 1.3.1:  31/03/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 and RH850/U2Bx-E MCAL Ver22.00.02 Release
 * 1.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 1.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 * 1.1.0:  06/03/2024  : Update SW-VERSION to 1.1.0
 * 1.0.0:  01/04/2023  : Initial Version
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
#include "SchM_Ocu.h"
#include "Compiler.h"
#include "Std_Types.h"
#include "Os.h"
/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/
/***********************************************************************************************************************
**                                 SchM_Enter_Ocu_OCU_INTERRUPT_CONTROL_PROTECTION()                                  **
***********************************************************************************************************************/
void SchM_Enter_Ocu_OCU_INTERRUPT_CONTROL_PROTECTION(void)
{
  DISABLE_INTERRUPT();
}

/***********************************************************************************************************************
**                                  SchM_Exit_Ocu_OCU_INTERRUPT_CONTROL_PROTECTION()                                  **
***********************************************************************************************************************/
void SchM_Exit_Ocu_OCU_INTERRUPT_CONTROL_PROTECTION(void)
{
  ENABLE_INTERRUPT();
}


/***********************************************************************************************************************
**                                  SchM_Enter_Ocu_OCU_INTERRUPT_CONTROL_PROTECTION_GLOBAL()                          **
***********************************************************************************************************************/
void SchM_Enter_Ocu_OCU_INTERRUPT_CONTROL_PROTECTION_GLOBAL(void)
{
  #ifdef USE_MULTI_CORE
  (void)GetSpinlock(SpinlockAllISRs);
  #else
  DISABLE_INTERRUPT();
  #endif
}

/***********************************************************************************************************************
**                                  SchM_Exit_Ocu_OCU_INTERRUPT_CONTROL_PROTECTION_GLOBAL()                           **
***********************************************************************************************************************/
void SchM_Exit_Ocu_OCU_INTERRUPT_CONTROL_PROTECTION_GLOBAL(void)
{
  #ifdef USE_MULTI_CORE
  (void)ReleaseSpinlock(SpinlockAllISRs);
  #else
  ENABLE_INTERRUPT();
  #endif
}

/***********************************************************************************************************************
**                                  SchM_Enter_Ocu_OCU_RAM_DATA_PROTECTION_GLOBAL()                                   **
***********************************************************************************************************************/
void SchM_Enter_Ocu_OCU_RAM_DATA_PROTECTION_GLOBAL(void)
{
  #ifdef USE_MULTI_CORE
  (void)GetSpinlock(SpinlockNothing);
  #else
  DISABLE_INTERRUPT();
  #endif
}

/***********************************************************************************************************************
**                                  SchM_Exit_Ocu_OCU_RAM_DATA_PROTECTION_GLOBAL()                                    **
***********************************************************************************************************************/
void SchM_Exit_Ocu_OCU_RAM_DATA_PROTECTION_GLOBAL(void)
{
  #ifdef USE_MULTI_CORE
  (void)ReleaseSpinlock(SpinlockNothing);
  #else
  ENABLE_INTERRUPT();
  #endif
}

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
