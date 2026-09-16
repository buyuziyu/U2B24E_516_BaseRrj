/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = App_ADC_Multi_Sample.c                                                                              */
/*====================================================================================================================*/
/*                                  COPYRIGHT                                                                         */
/*====================================================================================================================*/
/* (c) 2019-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains sample application for ADC Driver Component                                                     */
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
**                                                 Revision Control History                                           **
***********************************************************************************************************************/
/*
 * 2.5.1:  30/06/2025  : Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.03 release
 *                       Remove SW-VERSION in file header
 *                       Remove SW-VERSION in file header
 * 2.5.0:  30/06/2025  : Update SW-VERSION for RH850/Ver22.01.00 (D) U2Ax release
 * 2.3.1: 28/02/2025   : Update SW-VERSION for Ver22.00.02 U2Ax Beta 1 Release
 * 2.3.0: 28/02/2025   : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0: 31/12/2024   : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 * 2.1.3: 31/10/2024   : Update SW-VERSION 2.1.3
 * 2.1.2: 30/09/2024   : As part of Multi-core support, following changes are made:
 *                       1.Remove functions Adc_DeInit_MCAL() and Adc_DeInit_PE0()
 *                       2.Update Adc_EnableHardwareTriggerInfo[GroupIndex - ADC_MAX_SW_TRIGGER]
 *                       3.Update Adc_DisableHardwareTriggerInfo[GroupIndex - ADC_MAX_SW_TRIGGER]
 * 1.4.3: 27/05/2022   : Modify the format to 120 characters.
 * 1.2.0: 14/07/2020   : Release
 * 1.1.0: 19/06/2020   : Release
 * 1.0.0: 01/03/2019   : Initial Version
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                     Include Section                                                                                **
***********************************************************************************************************************/
#include "Std_Types.h"
#include "App_ADC_Device_Sample.h"
#include "App_ADC_Multi_Sample.h"
#include "App_ADC_Common_Sample_0.h"
#include "App_ADC_Common_Sample_1.h"
/***********************************************************************************************************************
**                            Macros                                                                                  **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                        Global variables                                                                            **
***********************************************************************************************************************/
volatile boolean GblSyncFlag = 0;

/***********************************************************************************************************************
**                        User function prototypes                                                                    **
***********************************************************************************************************************/
extern void Port_Init(void);
extern void Mcu_Init(void);
extern void Wdg_Init(void);

/***********************************************************************************************************************
**                      Function Definitions                                                                          **
***********************************************************************************************************************/
/***********************************************************************************************************************
*    ADC both PE0, PE1 Initialization
***********************************************************************************************************************/
Std_ReturnType Adc_Init_MCAL(void)
{
  /* Initialize Watchdog */
  Wdg_Init();

  /* Initialize MCU */
  Mcu_Init();

  /* Initialize PORT */
  Port_Init();

  /* ADC Interrupt registers EITBn initialization */
  Adc_Set_TableReference();

  /* ADC Interrupt Bind Register Initialization */
  Adc_Set_EI_Bind();

  /* Initialize Adc_Init */
  Adc_Init(Adc_Config);

  /* DMA Master Enable Initialization */
  Adc_DMA_DME_Enable();

  return E_OK;
}/* End of Adc_Init_MCAL() function */

/***********************************************************************************************************************
**                         Kernel function                                                                      **
***********************************************************************************************************************/

/* Trap CPU at the end of application */
void sample_end(void)
{
  while(1);
}

/* Check the Slave requested or not */
boolean CheckSlaveRequest(uint8 GroupIndex, uint8 ApiID)
{
  boolean LblReturnResult = 1;
  switch(ApiID)
  {
    case ADC_START_GROUP_CONVERSION_SID:
      LblReturnResult = Adc_StartGroupConversionInfo[GroupIndex].blSetRequest;
      break;
    case ADC_STOP_GROUP_CONVERSION_SID:
      LblReturnResult = Adc_StopGroupConversionInfo[GroupIndex].blSetRequest;
      break;
    case ADC_ENABLE_HARDWARE_TRIGGER_SID:
      LblReturnResult = Adc_EnableHardwareTriggerInfo[GroupIndex - ADC_MAX_SW_TRIGGER].blSetRequest;
      break;
    case ADC_DISABLE_HARDWARE_TRIGGER_SID:
      LblReturnResult = Adc_DisableHardwareTriggerInfo[GroupIndex - ADC_MAX_SW_TRIGGER].blSetRequest;
      break;
    default:
      break;
  }
  return LblReturnResult;
}
/***********************************************************************************************************************
**                          End of File                                                                               **
***********************************************************************************************************************/
