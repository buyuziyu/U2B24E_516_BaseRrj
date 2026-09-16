/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = App_ADC_Common_Sample_0.c                                                                           */
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
 * 2.3.1:  28/02/2025  : As part of ARDAACL-54066, following changes are made:
 *                       1. Update the pointer name passed to Adc_GetStreamLastPointer()
 *         28/02/2025  : Update SW-VERSION for Ver22.00.02 U2Ax Beta 1 Release
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
**                      Global Data                                                                                   **
***********************************************************************************************************************/
/* Declaration for the result buffers */
volatile Adc_ValueGroupType    GddSetBuffGroup0[TEST_ADC_NUMB_CHNL_G0_0* TEST_ADC_NUMB_SAMPLE_G0_0];
volatile Adc_ValueGroupType    GddSetBuffGroup1[TEST_ADC_NUMB_CHNL_G1_0* TEST_ADC_NUMB_SAMPLE_G1_0];
volatile Adc_ValueGroupType    GddSetBuffGroup2[TEST_ADC_NUMB_CHNL_G2_0* TEST_ADC_NUMB_SAMPLE_G2_0];
volatile Adc_ValueGroupType    GddSetBuffGroup3[TEST_ADC_NUMB_CHNL_G3_0* TEST_ADC_NUMB_SAMPLE_G3_0];

/* Variable used to store the return value for Read group API Core0*/
volatile Adc_ValueGroupType    GddReadResultGroup0[TEST_ADC_NUMB_CHNL_G0_0];
volatile Adc_ValueGroupType    GddReadResultGroup1[TEST_ADC_NUMB_CHNL_G1_0];
volatile Adc_ValueGroupType    GddReadResultGroup2[TEST_ADC_NUMB_CHNL_G2_0];
volatile Adc_ValueGroupType    GddReadResultGroup3[TEST_ADC_NUMB_CHNL_G3_0];

/* Variable used to store the return value for Read group API Core1*/
volatile Adc_ValueGroupType    GddReadResultGroup1_1[TEST_ADC_NUMB_CHNL_G1_1];
volatile Adc_ValueGroupType    GddReadResultGroup3_1[TEST_ADC_NUMB_CHNL_G3_1];

/* Variable used to store the return value for Adc_GetStreamLastPointer API */
volatile Adc_ValueGroupType *PtrToSample0;
volatile Adc_ValueGroupType **PtrToSamplePtr0;
volatile Adc_ValueGroupType *PtrToSample2;
volatile Adc_ValueGroupType **PtrToSamplePtr2;

/* Variable used to capture the number of samples that is converted */
volatile Adc_StreamNumSampleType GucNumSamples0;
volatile Adc_StreamNumSampleType GucNumSamples2;


volatile Adc_ValueGroupType *PtrToSample1_1;
volatile Adc_ValueGroupType **PtrToSamplePtr1_1;
volatile Adc_StreamNumSampleType GucNumSamples1_1;

/* Variable used to store the Module Version Info */
Std_VersionInfoType versioninfo;

/* Variable used to store the return value */
Std_ReturnType ret;

/* Variables to store the version info for ADC Driver */
volatile uint16 GusModuleID;
volatile uint16 GusVendorID;
volatile uint8 GucInstanceID;
volatile uint8 GucSwMajorVersion;
volatile uint8 GucSwMinorVersion;
volatile uint8 GucSwPatchVersion;

/* Global Variable for 1msec timer counter */
volatile uint32 Gul1msecCount = 0;

/* Variable used to store the conversion status of Groups */
volatile Adc_StatusType GaaGroupStatus0[4][4];

/***********************************************************************************************************************
**                      User Function Prototype                                                                       **
***********************************************************************************************************************/
void task1(void);
void task2(void);
/***********************************************************************************************************************
**                      Function Definitions                                                                          **
***********************************************************************************************************************/

/***********************************************************************************************************************
** Function Name         : main
**
** Description           : Sample application of ADC instance 0.
**
***********************************************************************************************************************/

int main()
{
  /* Init ADC MCAL drvier by stub init PORT, MCU... */
  Adc_Init_MCAL();
	
  /* Enable interrupt using EI instruction */
  ENABLE_INTERRUPT();
  
  /* Notify the other instance that startup and module initialization has been finished */
  GblSyncFlag = 1;
  
  /* Invoke OSTM timer, the OSTM counter duration is 1ms */ 
  Adc_Start_OSTM();
	
  /* Loop until the SW timer reaches 100ms */
  while(Gul1msecCount < 100)
  {
	/* Invoke task 2 at 20ms */
	if (20 == Gul1msecCount)
    {
      /* Task 2 */
      task2();
    }
  }

  /* Wait until core 1 is done with task3 */
  while(1U == GblSyncFlag);

  /*
   * De-Initialization of ADC Driver. After the driver is de-initialized, no other API calls except Adc_Init() are
   * valid. User should take care of re-initialising the ADC Driver with a valid database before invoking other APIs.
   */
  /* Exclusive Control De-Initialization Adc MCAL module*/
  Adc_DeInit();

  /* End trap */
  sample_end();
  return 0;
}


/* Task1, Kernel API*/
void task1(void)
{
  #if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
  Adc_Kernel_StartGroupConversion();

  Adc_Kernel_StopGroupConversion();
  #endif /* (ADC_ENABLE_START_STOP_GROUP_API == STD_ON) */
	
  #if (ADC_HW_TRIGGER_API == STD_ON)
  Adc_Kernel_EnableHardwareTrigger();

  Adc_Kernel_DisableHardwareTrigger();
  #endif /* (ADC_HW_TRIGGER_API == STD_ON) */
}

void task2(void)
{
  /* To get the version of the ADC Driver module */
  Adc_GetVersionInfo(&versioninfo);
  /* Module ID of the ADC Driver */
  GusModuleID = versioninfo.moduleID;
  /* Vendor ID information */
  GusVendorID = versioninfo.vendorID;
  /* Software major version of the ADC Driver */
  GucSwMajorVersion = versioninfo.sw_major_version;
  /* Software minor version of the ADC Driver */
  GucSwMinorVersion = versioninfo.sw_minor_version;
  /* Software patch version */
  GucSwPatchVersion = versioninfo.sw_patch_version;
  
  /* Get the conversion status of Group0 to Group3 after initialization */
  GaaGroupStatus0[0][0] = Adc_GetGroupStatus(Adc_AdcGroup_000);
  GaaGroupStatus0[1][0] = Adc_GetGroupStatus(Adc_AdcGroup_001);
  GaaGroupStatus0[2][0] = Adc_GetGroupStatus(Adc_AdcGroup_002);
  GaaGroupStatus0[3][0] = Adc_GetGroupStatus(Adc_AdcGroup_003);
  
  /* Update variable used to store return value of Adc_GetStreamLastPointer */
  PtrToSamplePtr0 = &PtrToSample0;
  PtrToSamplePtr2 = &PtrToSample2;
  
  /* This API will set the result buffer for the group 0 which is passed as input parameter */
  ret = Adc_SetupResultBuffer(Adc_AdcGroup_000, (Adc_ValueGroupType *)GddSetBuffGroup0);

  /* This API will set the result buffer for the group 1 which is passed as input parameter */
  ret = Adc_SetupResultBuffer(Adc_AdcGroup_001, (Adc_ValueGroupType *)GddSetBuffGroup1);

  /* This API will set the result buffer for the group 2 which is passed as input parameter */
  ret = Adc_SetupResultBuffer(Adc_AdcGroup_002, (Adc_ValueGroupType *)GddSetBuffGroup2);

  /* This API will set the result buffer for the group 3 which is passed as input parameter */
  ret = Adc_SetupResultBuffer(Adc_AdcGroup_003, (Adc_ValueGroupType *)GddSetBuffGroup3);
  /*********************************************************************************************************************
   * Group0 configuration:
   * + Software trigger.
   * + One shot conversion.
   * + Single access mode.
   * + Result access mode: ISR mode without using DMA transfer.
   ********************************************************************************************************************/
   /*
   * On completion of the conversion, the call-back notification will be invoked only if the API
   * Adc_EnableGroupNotification is invoked
   */
  Adc_EnableGroupNotification(Adc_AdcGroup_000);
  
  /* To disable the channel in group */
  Adc_DisableChannel(Adc_AdcGroup_000, 0x0002);
  
  /*
  * Starts the conversion of group 0.
  */
  Adc_StartGroupConversion(Adc_AdcGroup_000);
  while (CheckSlaveRequest(Adc_AdcGroup_000, ADC_START_GROUP_CONVERSION_SID));
  
  /* Get the conversion status of Group0 after starting the group */
  GaaGroupStatus0[0][1] = Adc_GetGroupStatus(Adc_AdcGroup_000);
  
  /*Wait till the conversion of group 0 is completed */
  while (ADC_STREAM_COMPLETED != Adc_GetGroupStatus(Adc_AdcGroup_000))
  {
    /*No Action Required*/
  };
  
  /*Disable the Group notification for the group 0 */
  Adc_DisableGroupNotification(Adc_AdcGroup_000);
  
  /*
  * API Adc_GetStreamLastPointer reads the samples of all channels in group 0, the variable GucNumSamples0 will
  * indicate the number of samples that is converted and SamplePtr will be updated with the address of the streaming
  * buffer which holds all the channel's digital output
  */
  GucNumSamples0 = Adc_GetStreamLastPointer(Adc_AdcGroup_000, (Adc_ValueGroupType **)PtrToSamplePtr0);
  
  /* Copy result data to application buffer */
  GddReadResultGroup0[0] = *PtrToSample0;
  
  /*
  * Stops the conversion of group 0, the conversion status of the group 0 is changed ADC_IDLE and the notification
  * status is disabled
  */
  Adc_StopGroupConversion(Adc_AdcGroup_000);
  while (CheckSlaveRequest(Adc_AdcGroup_000, ADC_STOP_GROUP_CONVERSION_SID));
  
  /* Get the conversion status of Group0 after stopping the group */
  GaaGroupStatus0[0][3] = Adc_GetGroupStatus(Adc_AdcGroup_000);

  /*  To enable the channel in group */
  Adc_EnableChannel(Adc_AdcGroup_000, 0x0002);

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
  Adc_EnableGroupNotification(Adc_AdcGroup_001);

  /*
   * Starts the conversion of group 1.
   */
  Adc_StartGroupConversion(Adc_AdcGroup_001);
  while (CheckSlaveRequest(Adc_AdcGroup_001, ADC_START_GROUP_CONVERSION_SID));

  /* Get the conversion status of Group1 after starting the group */
  GaaGroupStatus0[1][1] = Adc_GetGroupStatus(Adc_AdcGroup_001);

  /* Wait till the conversion of group 1 core0 is completed */
  do
  {
    ret = Adc_ReadGroup(Adc_AdcGroup_001, (Adc_ValueGroupType *)GddReadResultGroup1);
  }while (ADC_STREAM_COMPLETED != Adc_GetGroupStatus(Adc_AdcGroup_001));
  


  /* Disable the Group notification for the group 1 */
  Adc_DisableGroupNotification(Adc_AdcGroup_001);  

  /*
   * Stops the conversion of group 1, the conversion status of the group 1 is changed ADC_IDLE and the notification
   * status is disabled
   */
  Adc_StopGroupConversion(Adc_AdcGroup_001);
  while (CheckSlaveRequest(Adc_AdcGroup_001, ADC_STOP_GROUP_CONVERSION_SID));

  /* Get the conversion status of Group1 after stopping the group */
  GaaGroupStatus0[1][3] = Adc_GetGroupStatus(Adc_AdcGroup_001); 

  /*********************************************************************************************************************
   * Group2 configuration:
   * + Software trigger.
   * + Continuous conversion.
   * + Single access mode.
   * + Result access mode: POLLING mode with using DMA transfer
   ********************************************************************************************************************/  
  /*
   * On completion of the conversion, the call-back notification will be invoked only if the the API
   * Adc_EnableGroupNotification is invoked
   */
  Adc_EnableGroupNotification(Adc_AdcGroup_002);
  
  /*
   * Starts the conversion of group 2.
   */
  Adc_StartGroupConversion(Adc_AdcGroup_002);
  while (CheckSlaveRequest(Adc_AdcGroup_002, ADC_START_GROUP_CONVERSION_SID));

  /* Get the conversion status of Group2 after starting the group */
  GaaGroupStatus0[2][1] = Adc_GetGroupStatus(Adc_AdcGroup_002);

  /* Wait till the conversion of group 2 is completed */
  do
  {
    ret = Adc_ReadGroup(Adc_AdcGroup_002, (Adc_ValueGroupType *)GddReadResultGroup2);
  }while (ADC_STREAM_COMPLETED != Adc_GetGroupStatus(Adc_AdcGroup_002));

  /* Disable the Group notification for the group 2 */
  Adc_DisableGroupNotification(Adc_AdcGroup_002);

  /*
   * Stops the conversion of group 2, the conversion status of the group 2 is changed ADC_IDLE and the notification
   * status is disabled
   */
  Adc_StopGroupConversion(Adc_AdcGroup_002);
  while (CheckSlaveRequest(Adc_AdcGroup_002, ADC_STOP_GROUP_CONVERSION_SID));

  /* Get the conversion status of Group2 after stopping the group */
  GaaGroupStatus0[2][3] = Adc_GetGroupStatus(Adc_AdcGroup_002);

  /*********************************************************************************************************************
   * Group3 configuration:
   * + Hardware trigger.
   * + Oneshort conversion.
   * + Single access mode.
   * + Result access mode: ISR mode with using DMA transfer
   ********************************************************************************************************************/
  /*
   * On completion of the conversion, the call-back notification will be invoked only if the the API
   * Adc_EnableGroupNotification is invoked
   */
  Adc_EnableGroupNotification(Adc_AdcGroup_003);

  /*
   * Enables the hardware trigger for group 2, the external or timer triggers should be given only after calling this
   * API for the ADC conversion to start
   */
  Adc_EnableHardwareTrigger(Adc_AdcGroup_003);
  while (CheckSlaveRequest(Adc_AdcGroup_003, ADC_ENABLE_HARDWARE_TRIGGER_SID));

  /* Get the conversion status after enabling the group */
  GaaGroupStatus0[3][1] = Adc_GetGroupStatus(Adc_AdcGroup_003);

  /* Provide timer trigger so that the conversion of group 2 can start */
  Start_Timer0();  

  /* Wait till the conversion of group 2 is completed */
  while (ADC_STREAM_COMPLETED != Adc_GetGroupStatus(Adc_AdcGroup_003))
  {
    /*No Action Required*/
  };
  /* Disable the Group notification for the group 2 */
  Adc_DisableGroupNotification(Adc_AdcGroup_003);

  /* To read the ADC values */
  ret = Adc_ReadGroup(Adc_AdcGroup_003, (Adc_ValueGroupType *)GddReadResultGroup3);  

  /*
   * Disables the hardware trigger for group 2, even if any external or timer triggers are given after calling this
   * API the ADC conversion will not be started
   */
  Adc_DisableHardwareTrigger(Adc_AdcGroup_003);
  while (CheckSlaveRequest(Adc_AdcGroup_003, ADC_DISABLE_HARDWARE_TRIGGER_SID));

  /* Get the conversion status after disabling the group */
  GaaGroupStatus0[3][3] = Adc_GetGroupStatus(Adc_AdcGroup_003);  

}

/* End of function */


/***********************************************************************************************************************
**                           Timer Interrupt Routine                                                                  **
***********************************************************************************************************************/
/* 1 msec timer interrupt */
_INTERRUPT_ void Timer0_Interrupt(void)
{
  /* Increase the SW counter */
  Gul1msecCount++;
  /* Invoke task 1 every 1 ms */
  task1();
}

/***********************************************************************************************************************
**                           ReadGroup Functions                                                                      **
***********************************************************************************************************************/
void Adc_ReadGroup_Group101(void)
{
	
  PtrToSamplePtr1_1 = &PtrToSample1_1;
  /* Wait till the conversion of group 1 core 1 is completed */
  do
  {
    ret = Adc_ReadGroup(Adc_AdcGroup_101, (Adc_ValueGroupType *)GddReadResultGroup1_1);
  }while (ADC_STREAM_COMPLETED != Adc_GetGroupStatus(Adc_AdcGroup_101));
}

void Adc_ReadGroup_Group103(void)
{
  /* Wait till the conversion of group 3 core 1 is completed */
  do
  {
    ret = Adc_ReadGroup(Adc_AdcGroup_103, (Adc_ValueGroupType *)GddReadResultGroup3_1);
  }while (ADC_STREAM_COMPLETED != Adc_GetGroupStatus(Adc_AdcGroup_103));
}

/***********************************************************************************************************************
**                           Notification Functions                                                                   **
***********************************************************************************************************************/
#define ADC_START_SEC_APPL_CODE
#include "Adc_MemMap.h"

void IoHwAb_Adc_Notification_Group000(void)
{
  /* Call the notification function */

  /* Get the conversion status of Group0 when the conversion end notification callback is called */
  GaaGroupStatus0[0][2] = Adc_GetGroupStatus(Adc_AdcGroup_000);
}
void IoHwAb_Adc_Notification_Group001(void)
{
  /* Call the notification function */

  /* Get the conversion status of Group1 when the conversion end notification callback is called */
  GaaGroupStatus0[1][2] = Adc_GetGroupStatus(Adc_AdcGroup_001);
}
void IoHwAb_Adc_Notification_Group002(void)
{
  /* Call the notification function */

  /* Get the conversion status of Group2 when the conversion end notification callback is called */
  GaaGroupStatus0[2][2] = Adc_GetGroupStatus(Adc_AdcGroup_002);
}
void IoHwAb_Adc_Notification_Group003(void)
{
  /* Call the notification function */

  /* Get the conversion status of Group3 when the conversion end notification callback is called */
  GaaGroupStatus0[3][2] = Adc_GetGroupStatus(Adc_AdcGroup_003);
}

void IoHwAb_Adc_ErrNotification_000(uint8 Lucchannel)
{
  /* Call the notification function */
}
void IoHwAb_Adc_ErrNotificationSG(uint8 Lucchannel)
{
  /* Call the notification function */
}

#define ADC_STOP_SEC_APPL_CODE
#include "Adc_MemMap.h"
/***********************************************************************************************************************
**                          End of File                                                                               **
***********************************************************************************************************************/
