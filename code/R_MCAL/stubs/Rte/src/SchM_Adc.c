/*============================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                         */
/* Module       = SchM_Adc.c                                                  */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2022-2025 Renesas Electronics Corporation. All rights reserved.        */
/*============================================================================*/
/* Purpose:                                                                   */
/* This application file contains the Schm ADC Stub functions.                */
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
/*                                                                            */
/*============================================================================*/

/*******************************************************************************
**                      Revision Control History                              **
*******************************************************************************/
/*
 * 2.5.1:  30/06/2025  : Update SW-VERSION for 
 *                       RH850/U2Bx-E MCAL Ver22.00.03 release
 *                       Remove SW-VERSION in file header
 * 2.5.0:  30/06/2025  : Update SW-VERSION for 
 *                       RH850/Ver22.01.00 (D) U2Ax release
 * 2.4.0:  31/05/2025  : Update SW-VERSION for RH850/Ver21.01.01 U2Cx release
 * 2.3.1:  31/03/2025  : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 * 2.3.1:  28/02/2025  : Update SW-VERSION for Ver22.00.02 U2Ax Beta 1 Release
 * 2.3.0:  28/02/2025  : Update SW-VERSION for 
 *                       RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024  : Update SW-VERSION for 
 *                       Ver22.02.00/Ver22.02.00.D Final Release
 * 2.1.3:  31/10/2024  : Update SW-VERSION 2.1.3
 * 2.1.2:  30/09/2024  : Update SW-VERSION 2.1.2
 * 2.1.0:  06/03/2024  : Update SW-VERSION 2.1.0
 * 2.0.0:  25/07/2023  : Add SchM_Enter/Exit_ADC_RAM_DATA_PROTECTION_GLOBAL
 *                       to support multi core.
 * 1.4.5:  28/09/2022  : Initial Version
 */
/******************************************************************************/

/*******************************************************************************
**                     Include Section                                        **
*******************************************************************************/
#include "SchM_Adc.h"
#include "Compiler.h"
#include "Std_Types.h"
#include "Os.h"

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/
static uint32 SchM_AdcIntNestCount[NUM_CPU] = {0UL, 0UL, 0UL, 0UL, 0UL, 0UL};
static uint32 SchM_AdcRamNestCount[NUM_CPU] = {0UL, 0UL, 0UL, 0UL, 0UL, 0UL};

/*******************************************************************************
**        SchM_Enter_Adc_INTERRUPT_CONTROL_PROTECTION()                       **
*******************************************************************************/
void SchM_Enter_Adc_ADC_INTERRUPT_CONTROL_PROTECTION(void)
{
  uint8 LucPE = 0;
  LucPE = STSR(PEID);
  DISABLE_INTERRUPT();
  SchM_AdcIntNestCount[LucPE]++;
}

/*******************************************************************************
**        SchM_Exit_Adc_INTERRUPT_CONTROL_PROTECTION()                        **
*******************************************************************************/
void SchM_Exit_Adc_ADC_INTERRUPT_CONTROL_PROTECTION(void)
{
  uint8 LucPE = 0;
  LucPE = STSR(PEID);
  if (0U < SchM_AdcIntNestCount[LucPE])
  {
    SchM_AdcIntNestCount[LucPE]--;
    if (0U == SchM_AdcIntNestCount[LucPE])
    {
      ENABLE_INTERRUPT();
    }
    else
    {
      // Do nothing
    }
  }
  else
  {
    // Do nothing
  }
}

/*******************************************************************************
**        SchM_Enter_ADC_Adc_RAM_DATA_PROTECTION()                            **
*******************************************************************************/
void SchM_Enter_Adc_ADC_RAM_DATA_PROTECTION(void)
{
  uint8 LucPE = 0;
  LucPE = STSR(PEID);
  DISABLE_INTERRUPT();
  SchM_AdcRamNestCount[LucPE]++;
}

/*******************************************************************************
**        SchM_Exit_Adc_RAM_DATA_PROTECTION()                                 **
*******************************************************************************/
void SchM_Exit_Adc_ADC_RAM_DATA_PROTECTION(void)
{
  uint8 LucPE = 0;
  LucPE = STSR(PEID);
  if (0U < SchM_AdcRamNestCount[LucPE])
  {
    SchM_AdcRamNestCount[LucPE]--;
    if (0U == SchM_AdcRamNestCount[LucPE])
    {
        ENABLE_INTERRUPT();
    }
    else
    {
      // Do nothing
    }
  }
  else
  {
    // Do nothing
  }
}

/*******************************************************************************
**        SchM_Enter_ADC_RAM_DATA_PROTECTION_GLOBAL()                          **
*******************************************************************************/
void SchM_Enter_Adc_ADC_RAM_DATA_PROTECTION_GLOBAL()
{
  #ifdef USE_MULTI_CORE
  (void)GetSpinlock(SpinlockNothing);
  #else
  DISABLE_INTERRUPT();
  #endif
}

/*******************************************************************************
**        SchM_Exit_ADC_RAM_DATA_PROTECTION_GLOBAL()                           **
*******************************************************************************/

void SchM_Exit_Adc_ADC_RAM_DATA_PROTECTION_GLOBAL()
{
  #ifdef USE_MULTI_CORE
  (void)ReleaseSpinlock(SpinlockNothing);
  #else
  ENABLE_INTERRUPT();
  #endif
}

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
