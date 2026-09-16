/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = App_ADC_Common_Sample_1.c                                                                           */
/*====================================================================================================================*/
/*                                  COPYRIGHT                                                                         */
/*====================================================================================================================*/
/* (c) 2023-2025 Renesas Electronics Corporation. All rights reserved.                                                */
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
 * 2.3.1:  28/02/2025  : Update SW-VERSION for Ver22.00.02 U2Ax Beta 1 Release
 * 2.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 * 2.1.3:  31/10/2024  : Update SW-VERSION 2.1.3
 * 2.1.2:  30/09/2024  : Update SW-VERSION 2.1.2
 * 2.0.0:  25/07/2023  : Initial version.
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                      Include Section                                                                               **
***********************************************************************************************************************/
#include "App_ADC_Common_Sample_0.h"
#include "App_ADC_Common_Sample_1.h"
#include "App_ADC_Multi_Sample.h"
/***********************************************************************************************************************
**                      Defines                                                                                       **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                         Global Data                                                                                **
***********************************************************************************************************************/
/* Declaration for the result buffers */
volatile Adc_ValueGroupType    GddSetBuffGroup0_1[TEST_ADC_NUMB_CHNL_G0_1* TEST_ADC_NUMB_SAMPLE_G0_1];
volatile Adc_ValueGroupType    GddSetBuffGroup1_1[TEST_ADC_NUMB_CHNL_G1_1* TEST_ADC_NUMB_SAMPLE_G1_1];
volatile Adc_ValueGroupType    GddSetBuffGroup2_1[TEST_ADC_NUMB_CHNL_G2_1* TEST_ADC_NUMB_SAMPLE_G2_1];
volatile Adc_ValueGroupType    GddSetBuffGroup3_1[TEST_ADC_NUMB_CHNL_G3_1* TEST_ADC_NUMB_SAMPLE_G3_1];

/* Variable used to store the return value for Read group API */
volatile Adc_ValueGroupType    GddReadResultGroup0_1[TEST_ADC_NUMB_CHNL_G0_1];
volatile Adc_ValueGroupType    GddReadResultGroup2_1[TEST_ADC_NUMB_CHNL_G2_1];

/* Variable used to store the return value for Adc_GetStreamLastPointer API */
volatile Adc_ValueGroupType *PtrToSample0_1;
volatile Adc_ValueGroupType **PtrToSamplePtr0_1;
volatile Adc_ValueGroupType *PtrToSample2_1;
volatile Adc_ValueGroupType **PtrToSamplePtr2_1;

/* Variable used to capture the number of samples that is converted */
volatile Adc_StreamNumSampleType GucNumSamples0_1;
volatile Adc_StreamNumSampleType GucNumSamples2_1;


/* Variable used to store the return value */
Std_ReturnType ret_1;

/* Global Variable for 1msec timer counter */
extern volatile uint32 Gul1msecCount;


/* Variable used to store the conversion status of Groups */
volatile Adc_StatusType GaaGroupStatus1[4][4];

/***********************************************************************************************************************
**                      User Function Prototype                                                                       **
***********************************************************************************************************************/
void task3(void);
/***********************************************************************************************************************
**                      Function Definitions                                                                          **
***********************************************************************************************************************/

/***********************************************************************************************************************
** Function Name         : main_PE1
**
** Description           : Sample application of ADC instance 1.
**
***********************************************************************************************************************/
int main_PE1(void)
{
  /* Wait until Master core is done Initialization */
  while(0U == GblSyncFlag);

  /* Loop until the SW timer reaches 100ms */
  while(Gul1msecCount < 100)
  {
    /* Invoke task 3 at 20ms */
    if (Gul1msecCount == 20U)
    {
      /* Task 3 with execute with hardware unit 1 */
      task3();
    }
  }
  
  /* Notify core 0 as a task done from core 1 */
  GblSyncFlag = 0;

  /* End trap */
  sample_end();
  return(0);
}


void task3(void)
{  
  /* Get the conversion status of Group0 to Group3 after initialization */
  GaaGroupStatus1[0][0] = Adc_GetGroupStatus(Adc_AdcGroup_100);
  GaaGroupStatus1[1][0] = Adc_GetGroupStatus(Adc_AdcGroup_101);
  GaaGroupStatus1[2][0] = Adc_GetGroupStatus(Adc_AdcGroup_102);
  GaaGroupStatus1[3][0] = Adc_GetGroupStatus(Adc_AdcGroup_103);
  
  /* Enable the Global interrupts */
  ENABLE_INTERRUPT();
  
  /* Update variable used to store return value of Adc_GetStreamLastPointer */
  PtrToSamplePtr0_1 = &PtrToSample0_1;
  PtrToSamplePtr2_1 = &PtrToSample2_1;

  /* This API will set the result buffer for the group 0 which is passed as input parameter */
  ret_1 = Adc_SetupResultBuffer(Adc_AdcGroup_100, (Adc_ValueGroupType *)GddSetBuffGroup0_1);

  /* This API will set the result buffer for the group 1 which is passed as input parameter */
  ret_1 = Adc_SetupResultBuffer(Adc_AdcGroup_101, (Adc_ValueGroupType *)GddSetBuffGroup1_1);

  /* This API will set the result buffer for the group 2 which is passed as input parameter */
  ret_1 = Adc_SetupResultBuffer(Adc_AdcGroup_102, (Adc_ValueGroupType *)GddSetBuffGroup2_1);

  /* This API will set the result buffer for the group 3 which is passed as input parameter */
  ret_1 = Adc_SetupResultBuffer(Adc_AdcGroup_103, (Adc_ValueGroupType *)GddSetBuffGroup3_1);

  /*********************************************************************************************************************
   * Group0 configuration:
   * + Software trigger.
   * + One shot conversion.
   * + Single access mode.
   * + Result access mode: ISR mode without using DMA transfer.
   ********************************************************************************************************************/
  /*
   * On completion of the conversion, the call-back notification will be invoked only if the the API
   * Adc_EnableGroupNotification is invoked
   */
  Adc_EnableGroupNotification(Adc_AdcGroup_100);

  /*  To disable the channel in group */
  Adc_DisableChannel(Adc_AdcGroup_100, 0x0002);

  /*
   * Starts the conversion of group 0.
   */
  Adc_StartGroupConversion(Adc_AdcGroup_100);
  while (CheckSlaveRequest(Adc_AdcGroup_100, ADC_START_GROUP_CONVERSION_SID));

  /* Get the conversion status of Group0 after starting the group */
  GaaGroupStatus1[0][1] = Adc_GetGroupStatus(Adc_AdcGroup_100);

  /* Wait till the conversion of group 0 is completed */
  while (ADC_STREAM_COMPLETED != GaaGroupStatus1[0][2]);

  /* Disable the Group notification for the group 0 */
  Adc_DisableGroupNotification(Adc_AdcGroup_100);

  /*
   * API Adc_GetStreamLastPointer reads the samples of all the channels in group 0, the variable GucNumSamples0 will
   * indicate the number of samples that is converted and SamplePtr will be updated with the address of the streaming
   * buffer which holds all the channel's digital output
   */
  GucNumSamples0_1 = Adc_GetStreamLastPointer(Adc_AdcGroup_100, (Adc_ValueGroupType **)PtrToSamplePtr0_1);

  /* Copy result data to application buffer */
  GddReadResultGroup0_1[0] = *PtrToSample0_1;
  

  /*
   * Stops the conversion of group 0, the conversion status of the group 0 is changed ADC_IDLE and the notification
   * status is disabled
   */
  Adc_StopGroupConversion(Adc_AdcGroup_100);
  while (CheckSlaveRequest(Adc_AdcGroup_100, ADC_STOP_GROUP_CONVERSION_SID));

  /* Get the conversion status of Group0 after stopping the group */
  GaaGroupStatus1[0][3] = Adc_GetGroupStatus(Adc_AdcGroup_100);

  /*  To enable the channel in group */
  Adc_EnableChannel(Adc_AdcGroup_100, 0x0002);

  /*********************************************************************************************************************
   * Group1 configuration:
   * + Software trigger.
   * + Continuous conversion.
   * + Linear streaming access mode.
   * + Result access mode: POLLING mode without using DMA transfer.
   ********************************************************************************************************************/
  /*
   * On completion of the conversion, the call-back notification will be invoked only if the the API
   * Adc_EnableGroupNotification is invoked
   */
  Adc_EnableGroupNotification(Adc_AdcGroup_101);

  /*
   * Starts the conversion of group 1.
   */
  Adc_StartGroupConversion(Adc_AdcGroup_101);
  while (CheckSlaveRequest(Adc_AdcGroup_101, ADC_START_GROUP_CONVERSION_SID));

  /* Get the conversion status of Group1 after starting the group */
  GaaGroupStatus1[1][1] = Adc_GetGroupStatus(Adc_AdcGroup_101);
  
  /* Wait till the conversion of group 1 is completed */
  Adc_ReadGroup_Group101();

  /* Disable the Group notification for the group 1 */
  Adc_DisableGroupNotification(Adc_AdcGroup_101);

  /*
   * Stops the conversion of group 1, the conversion status of the group 1 is changed ADC_IDLE and the notification
   * status is disabled
   */
  Adc_StopGroupConversion(Adc_AdcGroup_101);
  while (CheckSlaveRequest(Adc_AdcGroup_101, ADC_STOP_GROUP_CONVERSION_SID));

  /* Get the conversion status of Group1 after stopping the group */
  GaaGroupStatus1[1][3] = Adc_GetGroupStatus(Adc_AdcGroup_101);

  /*********************************************************************************************************************
   * Group2 configuration:
   * + Software trigger.
   * + Continuous conversion.
   * + Single access mode.
   * + Result access mode: ISR mode with using DMA transfer
   ********************************************************************************************************************/
  /*
   * On completion of the conversion, the call-back notification will be invoked only if the the API
   * Adc_EnableGroupNotification is invoked
   */
  Adc_EnableGroupNotification(Adc_AdcGroup_102);

  /*
   * Starts the conversion of group 2.
   */
  Adc_StartGroupConversion(Adc_AdcGroup_102);
  while (CheckSlaveRequest(Adc_AdcGroup_102, ADC_START_GROUP_CONVERSION_SID));

  /* Get the conversion status of Group2 after starting the group */
  GaaGroupStatus1[2][1] = Adc_GetGroupStatus(Adc_AdcGroup_102);

  /* Wait till the conversion of group 2 is completed */
  while (ADC_STREAM_COMPLETED != Adc_GetGroupStatus(Adc_AdcGroup_102))
  {
    /*No Action Required*/
  };
  /* Disable the Group notification for the group 2 */
  Adc_DisableGroupNotification(Adc_AdcGroup_102);

  /*
   * API Adc_GetStreamLastPointer reads the samples of all the channels in group 2, the variable GucNumSamples2
   * will indicate the number of samples that is converted and SamplePtr will be updated with the address of the
   * streaming buffer which holds all the channel's digital output
   */
  GucNumSamples2_1 = Adc_GetStreamLastPointer(Adc_AdcGroup_102, (Adc_ValueGroupType **)PtrToSamplePtr2_1);

  /* Copy result data to application buffer */
  GddReadResultGroup2_1[0] = *PtrToSample2_1;

  /*
   * Stops the conversion of group 2, the conversion status of the group 2 is changed ADC_IDLE and the notification
   * status is disabled
   */
  Adc_StopGroupConversion(Adc_AdcGroup_102);
  while (CheckSlaveRequest(Adc_AdcGroup_102, ADC_STOP_GROUP_CONVERSION_SID));

  /* Get the conversion status of Group2 after stopping the group */
  GaaGroupStatus1[2][3] = Adc_GetGroupStatus(Adc_AdcGroup_102);

  /*********************************************************************************************************************
   * Group3 configuration:
   * + Software trigger.
   * + Oneshort conversion.
   * + Single access mode.
   * + Result access mode: POLLING mode with using DMA transfer
   ********************************************************************************************************************/
  /*
   * On completion of the conversion, the call-back notification will be invoked only if the the API
   * Adc_EnableGroupNotification is invoked
   */
  Adc_EnableGroupNotification(Adc_AdcGroup_103);

  /*
   * Starts the conversion of group 3.
   */
  Adc_StartGroupConversion(Adc_AdcGroup_103);
  while (CheckSlaveRequest(Adc_AdcGroup_103, ADC_START_GROUP_CONVERSION_SID));

  /* Get the conversion status of Group3 after starting the group */
  GaaGroupStatus1[3][1] = Adc_GetGroupStatus(Adc_AdcGroup_103);

  /* Wait till the conversion of group 3 is completed */
  Adc_ReadGroup_Group103();

  /* Disable the Group notification for the group 3 */
  Adc_DisableGroupNotification(Adc_AdcGroup_103);

  /*
   * Stops the conversion of group 3, the conversion status of the group 3 is changed ADC_IDLE and the notification
   * status is disabled
   */
  Adc_StopGroupConversion(Adc_AdcGroup_103);
  while (CheckSlaveRequest(Adc_AdcGroup_103, ADC_STOP_GROUP_CONVERSION_SID));

  /* Get the conversion status of Group3 after stopping the group */
  GaaGroupStatus1[3][3] = Adc_GetGroupStatus(Adc_AdcGroup_103);

}


/**********************************************************************************************************************
**                           Notification Functions                                                                  **
**********************************************************************************************************************/
#define ADC_START_SEC_APPL_CODE
#include "Adc_MemMap.h"

void IoHwAb_Adc_Notification_Group100(void)
{
  /* Call the notification function */

  /* Get the conversion status of Group0 when the conversion end notification callback is called */
  GaaGroupStatus1[0][2] = Adc_GetGroupStatus(Adc_AdcGroup_100);
}
void IoHwAb_Adc_Notification_Group101(void)
{
  /* Call the notification function */

  /* Get the conversion status of Group1 when the conversion end notification callback is called */
  GaaGroupStatus1[1][2] = Adc_GetGroupStatus(Adc_AdcGroup_101);
}
void IoHwAb_Adc_Notification_Group102(void)
{
  /* Call the notification function */

  /* Get the conversion status of Group2 when the conversion end notification callback is called */
  GaaGroupStatus1[2][2] = Adc_GetGroupStatus(Adc_AdcGroup_102);
}
void IoHwAb_Adc_Notification_Group103(void)
{
  /* Call the notification function */

  /* Get the conversion status of Group3 when the conversion end notification callback is called */
  GaaGroupStatus1[3][2] = Adc_GetGroupStatus(Adc_AdcGroup_103);
}
void IoHwAb_Adc_ErrNotification_001(uint8 Lucchannel)
{
  /* Call the notification function */
}

#define ADC_STOP_SEC_APPL_CODE
#include "Adc_MemMap.h"
/***********************************************************************************************************************
**                          End of File                                                                               **
***********************************************************************************************************************/
