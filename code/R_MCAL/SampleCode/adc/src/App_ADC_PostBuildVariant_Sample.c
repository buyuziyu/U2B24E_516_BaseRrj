/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = App_ADC_Common_Sample.c                                                                             */
/*====================================================================================================================*/
/*                                  COPYRIGHT                                                                         */
/*====================================================================================================================*/
/* (c) 2024, 2025 Renesas Electronics Corporation. All rights reserved.                                               */
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
**                      Revision Control History                                                                      **
***********************************************************************************************************************/
/*
 * 2.5.1:  30/06/2025  : Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.03 release
 *                       Remove SW-VERSION in file header
 *                       Remove SW-VERSION in file header
 * 2.5.0:  30/06/2025  : Update SW-VERSION for RH850/Ver22.01.00 (D) U2Ax release
 * 2.3.1:  28/02/2025  : Update SW-VERSION for Ver22.00.02 U2Ax Beta 1 Release
 *                       As part of support U2Bx-E SampleApp on G4KH, following changes are made:
 *                       1. Add main_PEn(), Guard_Enable_PE()
 * 2.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 * 2.1.3:  31/10/2024  : Update SW-VERSION 2.1.3
 * 2.1.2:  30/09/2024  : Update SW-VERSION 2.1.2
 * 1.4.6:  22/02/2024  : Initial version.
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                      Include Section                                                                               **
***********************************************************************************************************************/
#include "App_ADC_Common_PostBuildVariant_Sample.h"
#include "App_ADC_Device_Sample.h"
#include "Adc.h"
/***********************************************************************************************************************
**                      Defines                                                                                       **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                      Global Data                                                                                   **
***********************************************************************************************************************/
/* Declaration for the result buffers */
volatile Adc_ValueGroupType    GddSetBuffGroup0_Var1[TEST_ADC_NUMB_CHNL_G0_1 * TEST_ADC_NUMB_SAMPLE_G0_1];
volatile Adc_ValueGroupType    GddSetBuffGroup1_Var1[TEST_ADC_NUMB_CHNL_G1_1 * TEST_ADC_NUMB_SAMPLE_G1_1];
volatile Adc_ValueGroupType    GddSetBuffGroup2_Var1[TEST_ADC_NUMB_CHNL_G2_1 * TEST_ADC_NUMB_SAMPLE_G2_1];
volatile Adc_ValueGroupType    GddSetBuffGroup3_Var1[TEST_ADC_NUMB_CHNL_G3_1 * TEST_ADC_NUMB_SAMPLE_G3_1];

volatile Adc_ValueGroupType    GddSetBuffGroup0_Var2[TEST_ADC_NUMB_CHNL_G0_2 * TEST_ADC_NUMB_SAMPLE_G0_2];
volatile Adc_ValueGroupType    GddSetBuffGroup1_Var2[TEST_ADC_NUMB_CHNL_G1_2 * TEST_ADC_NUMB_SAMPLE_G1_2];
volatile Adc_ValueGroupType    GddSetBuffGroup2_Var2[TEST_ADC_NUMB_CHNL_G2_2 * TEST_ADC_NUMB_SAMPLE_G2_2];
volatile Adc_ValueGroupType    GddSetBuffGroup3_Var2[TEST_ADC_NUMB_CHNL_G3_2 * TEST_ADC_NUMB_SAMPLE_G3_2];

/* Variable used to store the return value for Read group API */
volatile Adc_ValueGroupType    GddReadResultGroup0_Var1[TEST_ADC_NUMB_CHNL_G0_1];
volatile Adc_ValueGroupType    GddReadResultGroup1_Var1[TEST_ADC_NUMB_CHNL_G1_1];
volatile Adc_ValueGroupType    GddReadResultGroup2_Var1[TEST_ADC_NUMB_CHNL_G2_1];
volatile Adc_ValueGroupType    GddReadResultGroup3_Var1[TEST_ADC_NUMB_CHNL_G3_1];

volatile Adc_ValueGroupType    GddReadResultGroup0_Var2[TEST_ADC_NUMB_CHNL_G0_2];
volatile Adc_ValueGroupType    GddReadResultGroup1_Var2[TEST_ADC_NUMB_CHNL_G1_2];
volatile Adc_ValueGroupType    GddReadResultGroup2_Var2[TEST_ADC_NUMB_CHNL_G2_2];
volatile Adc_ValueGroupType    GddReadResultGroup3_Var2[TEST_ADC_NUMB_CHNL_G3_2];

/* Variable used to store the return value for Adc_GetStreamLastPointer API */
volatile Adc_ValueGroupType* PtrToSample0;
volatile Adc_ValueGroupType* PtrToSample1;

/* Variable used to capture the number of samples that is converted */
volatile Adc_StreamNumSampleType GucNumSamples0;
volatile Adc_StreamNumSampleType GucNumSamples1;

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

/* Variable used to store the conversion status of Groups */
volatile Adc_StatusType GaaGroupStatus[8][4];

#if defined(RUN_OTHER_PE)
extern void Guard_Enable_PE(void);
#endif
extern void Guard_Init(void);

/***********************************************************************************************************************
**                      User Function Prototype                                                                       **
***********************************************************************************************************************/
/* Function prototype variant support */
void Adc_VariantSupport_1(void);
void Adc_VariantSupport_2(void);

/***********************************************************************************************************************
**                      Function Definitions                                                                          **
***********************************************************************************************************************/

/***********************************************************************************************************************
** Function Name         : main
**
** Description           : Sample application of ADC instance 0.
**
***********************************************************************************************************************/
int main(void)
#if defined(RUN_OTHER_PE)
{
  Guard_Enable_PE();
  while(1);
}
#if defined(RUN_PE1)
int main_PE1(void)
#elif defined(RUN_PE2)
int main_PE2(void)
#elif defined(RUN_PE3)
int main_PE3(void)
#elif defined(RUN_PE4)
int main_PE4(void)
#elif defined(RUN_PE5)
int main_PE5(void)
#elif defined(RUN_PE6)
int main_PE6(void)
#endif
#endif
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
  /* Software patch version of the ADC Driver */
  GucSwPatchVersion = versioninfo.sw_patch_version;

  #if defined(RUN_OTHER_PE)
  /* Enable guard for all PE */
  Guard_Enable_PE();
  #endif

  /* Initialize MCU */
  Mcu_Init();
  
  /* Initialize guard to un-protect for ADC HW units */
  Guard_Init();

  /* Initialize PORT */
  Port_Init();

  /* Initialize Watchdog */
  Wdg_Init();

  /* ADC Interrupt Initialization */
  Adc_Set_TableReference();

  #if !defined(RUN_PE6)
  /* ADC Interrupt Bind Register Initialization */
  Adc_Set_EI_Bind();
  #endif

  /* DMA Master Enable Initialization */
  Adc_DMA_DME_Enable();

  /* Enable the Global interrupts */
  ENABLE_INTERRUPT();

  /* ======= VARIANT_1 ========= */
  /* Initialize ADC at Variant 1 */
  Adc_Init(Adc_Config_Variant_1);

  /* Invoke function variant 1 */
  Adc_VariantSupport_1();

  /* De-Initialize ADC at Variant 1 */
  Adc_DeInit();

  /* ======= VARIANT_2 ========= */
  /* Initialize ADC at Variant 2 */
  Adc_Init(Adc_Config_Variant_2);

  /* Invoke function variant 2 */
  Adc_VariantSupport_2();

  /*
   * De-Initialization of ADC Driver Variant 2. After the driver is de-initialized, no other API calls except Adc_Init() are
   * valid. User should take care of re-initialising the ADC Driver with a valid database before invoking other APIs.
   */
  Adc_DeInit();

  return(0);
}

/* End of main() function */

/* Function Adc Variant 1 */
void Adc_VariantSupport_1()
{
  /* Get the conversion status of Group0 to Group3 after initialization */
  GaaGroupStatus[0][0] = Adc_GetGroupStatus(Adc_AdcGroup_000);
  GaaGroupStatus[1][0] = Adc_GetGroupStatus(Adc_AdcGroup_001);
  GaaGroupStatus[2][0] = Adc_GetGroupStatus(Adc_AdcGroup_002);
  GaaGroupStatus[3][0] = Adc_GetGroupStatus(Adc_AdcGroup_003);

  /* This API will set the result buffer for the group 0 which is passed as input parameter */
  ret = Adc_SetupResultBuffer(Adc_AdcGroup_000, (Adc_ValueGroupType *)GddSetBuffGroup0_Var1);

  /* This API will set the result buffer for the group 1 which is passed as input parameter */
  ret = Adc_SetupResultBuffer(Adc_AdcGroup_001, (Adc_ValueGroupType *)GddSetBuffGroup1_Var1);

  /* This API will set the result buffer for the group 2 which is passed as input parameter */
  ret = Adc_SetupResultBuffer(Adc_AdcGroup_002, (Adc_ValueGroupType *)GddSetBuffGroup2_Var1);

  /* This API will set the result buffer for the group 3 which is passed as input parameter */
  ret = Adc_SetupResultBuffer(Adc_AdcGroup_003, (Adc_ValueGroupType *)GddSetBuffGroup3_Var1);

  /*********************************************************************************************************************
   * Group0 configuration:
   * + Software trigger.
   * + One shot conversion.
   * + Single access mode.
   * + Result access mode: ISR mode without using DMA transfer.
   ********************************************************************************************************************/

  /*
   * On completion of the conversion, the call-back notification will be invoked only if the API
   * Adc_EnableGroupNotification is invoked.
   */
  Adc_EnableGroupNotification(Adc_AdcGroup_000);

  /* Disable the channel in group */
  Adc_DisableChannel(Adc_AdcGroup_000, 0x0002);

  /* Start the conversion of group 0. */
  Adc_StartGroupConversion(Adc_AdcGroup_000);

  /* Get the conversion status of Group0 after starting the group */
  GaaGroupStatus[0][1] = Adc_GetGroupStatus(Adc_AdcGroup_000);

  /* Wait till the conversion of group 0 is completed */
  while (ADC_STREAM_COMPLETED != Adc_GetGroupStatus(Adc_AdcGroup_000))
  {
    /*No Action Required*/
  };

  /* Disable the Group notification for the group 0 */
  Adc_DisableGroupNotification(Adc_AdcGroup_000);

  /*
   * API Adc_GetStreamLastPointer reads the number of valid samples stored in the result buffer
   * and a pointer to the top of the channel for the result of the last sample that completed the conversion.
   * The variable GucNumSamples0 will indicate the number of samples, and the pointer PtrToSample0
   * will be updated with the pointer to the streaming buffer which holds all the channel's digital output.
   */
  GucNumSamples0 = Adc_GetStreamLastPointer(Adc_AdcGroup_000, (Adc_ValueGroupType**)&PtrToSample0);

  /* Copy result data to application buffer */
  GddReadResultGroup0_Var1[0] = *PtrToSample0;

  /*
   * Stop the conversion of group 0, the conversion status of the group 0 is changed to ADC_IDLE, and the notification
   * status is disabled.
   */
  Adc_StopGroupConversion(Adc_AdcGroup_000);

  /* Get the conversion status of Group0 after stopping the group */
  GaaGroupStatus[0][3] = Adc_GetGroupStatus(Adc_AdcGroup_000);

  /*  Enable the channel in group */
  Adc_EnableChannel(Adc_AdcGroup_000, 0x0002);

  /*********************************************************************************************************************
   * Group1 configuration:
   * + Software trigger.
   * + Continuous conversion.
   * + Linear streaming access mode.
   * + Result access mode: POLLING mode without using DMA transfer.
   ********************************************************************************************************************/

  /*
   * On completion of the conversion, the call-back notification will be invoked only if the API
   * Adc_EnableGroupNotification is invoked.
   */
  Adc_EnableGroupNotification(Adc_AdcGroup_001);

  /* Start the conversion of group 1. */
  Adc_StartGroupConversion(Adc_AdcGroup_001);

  /* Get the conversion status of Group1 after starting the group */
  GaaGroupStatus[1][1] = Adc_GetGroupStatus(Adc_AdcGroup_001);

  /* Wait till the conversion of group 1 is completed */
  do
  {
    ret = Adc_ReadGroup(Adc_AdcGroup_001, (Adc_ValueGroupType *)GddReadResultGroup1_Var1);
  } while (ADC_STREAM_COMPLETED != Adc_GetGroupStatus(Adc_AdcGroup_001));

  /* Disable the Group notification for the group 1 */
  Adc_DisableGroupNotification(Adc_AdcGroup_001);

  /* Stop the conversion of group 1, the conversion status of the group 1 is changed to ADC_IDLE. */
  Adc_StopGroupConversion(Adc_AdcGroup_001);

  /* Get the conversion status of Group1 after stopping the group */
  GaaGroupStatus[1][3] = Adc_GetGroupStatus(Adc_AdcGroup_001);

  /*********************************************************************************************************************
   * Group2 configuration:
   * + Software trigger.
   * + Continuous conversion.
   * + Single access mode.
   * + Result access mode: POLLING mode with using DMA transfer
   ********************************************************************************************************************/

  /*
   * On completion of the conversion, the call-back notification will be invoked only if the API
   * Adc_EnableGroupNotification is invoked.
   */
  Adc_EnableGroupNotification(Adc_AdcGroup_002);

  /* Start the conversion of group 2. */
  Adc_StartGroupConversion(Adc_AdcGroup_002);

  /* Get the conversion status of Group2 after starting the group */
  GaaGroupStatus[2][1] = Adc_GetGroupStatus(Adc_AdcGroup_002);

  /* Wait till the conversion of group 2 is completed */
  do
  {
    ret = Adc_ReadGroup(Adc_AdcGroup_002, (Adc_ValueGroupType *)GddReadResultGroup2_Var1);
  } while (ADC_STREAM_COMPLETED != Adc_GetGroupStatus(Adc_AdcGroup_002));

  /* Disable the Group notification for the group 2 */
  Adc_DisableGroupNotification(Adc_AdcGroup_002);

  /* Stop the conversion of group 2, the conversion status of the group 2 is changed to ADC_IDLE. */
  Adc_StopGroupConversion(Adc_AdcGroup_002);

  /* Get the conversion status of Group2 after stopping the group */
  GaaGroupStatus[2][3] = Adc_GetGroupStatus(Adc_AdcGroup_002);

  /*********************************************************************************************************************
   * Group3 configuration:
   * + Hardware trigger.
   * + One shot conversion.
   * + Single access mode.
   * + Result access mode: ISR mode with using DMA transfer
   ********************************************************************************************************************/
  /*
   * On completion of the conversion, the call-back notification will be invoked only if the API
   * Adc_EnableGroupNotification is invoked.
   */
  Adc_EnableGroupNotification(Adc_AdcGroup_003);

  /*
   * Enable the hardware trigger for group 3, the external or timer triggers should be given only after calling this
   * API for the ADC conversion to start.
   */
  Adc_EnableHardwareTrigger(Adc_AdcGroup_003);

  /* Get the conversion status after enabling the group */
  GaaGroupStatus[3][1] = Adc_GetGroupStatus(Adc_AdcGroup_003);

  /* Provide timer trigger so that the conversion of group 3 can start */
  Start_Timer0();

  /* Wait till the conversion of group 3 is completed */
  while (ADC_STREAM_COMPLETED != Adc_GetGroupStatus(Adc_AdcGroup_003))
  {
    /*No Action Required*/
  };

  /* Disable the Group notification for the group 3 */
  Adc_DisableGroupNotification(Adc_AdcGroup_003);

  /* Read the result values */
  ret = Adc_ReadGroup(Adc_AdcGroup_003, (Adc_ValueGroupType *)GddReadResultGroup3_Var1);

  /*
   * Disable the hardware trigger for group 3, even if any external or timer triggers are given after calling this API,
   * the ADC conversion will not be started.
   */
  Adc_DisableHardwareTrigger(Adc_AdcGroup_003);

  /* Get the conversion status after disabling the group */
  GaaGroupStatus[3][3] = Adc_GetGroupStatus(Adc_AdcGroup_003);

}

/* Function Adc Variant 2 */
void Adc_VariantSupport_2()
{
  /* Get the conversion status of Group0 to Group3 after initialization */
  GaaGroupStatus[4][0] = Adc_GetGroupStatus(Adc_AdcGroup_000);
  GaaGroupStatus[5][0] = Adc_GetGroupStatus(Adc_AdcGroup_001);
  GaaGroupStatus[6][0] = Adc_GetGroupStatus(Adc_AdcGroup_002);
  GaaGroupStatus[7][0] = Adc_GetGroupStatus(Adc_AdcGroup_003);

  /* This API will set the result buffer for the group 0 which is passed as input parameter */
  ret = Adc_SetupResultBuffer(Adc_AdcGroup_000, (Adc_ValueGroupType *)GddSetBuffGroup0_Var2);

  /* This API will set the result buffer for the group 1 which is passed as input parameter */
  ret = Adc_SetupResultBuffer(Adc_AdcGroup_001, (Adc_ValueGroupType *)GddSetBuffGroup1_Var2);

  /* This API will set the result buffer for the group 2 which is passed as input parameter */
  ret = Adc_SetupResultBuffer(Adc_AdcGroup_002, (Adc_ValueGroupType *)GddSetBuffGroup2_Var2);

  /* This API will set the result buffer for the group 3 which is passed as input parameter */
  ret = Adc_SetupResultBuffer(Adc_AdcGroup_003, (Adc_ValueGroupType *)GddSetBuffGroup3_Var2);

  /*********************************************************************************************************************
   * Group0 configuration:
   * + Software trigger.
   * + One shot conversion.
   * + Single access mode.
   * + Result access mode: ISR mode without using DMA transfer.
   ********************************************************************************************************************/

  /*
   * On completion of the conversion, the call-back notification will be invoked only if the API
   * Adc_EnableGroupNotification is invoked.
   */
  Adc_EnableGroupNotification(Adc_AdcGroup_000);

  /* Disable the channel in group */
  Adc_DisableChannel(Adc_AdcGroup_000, 0x0002);

  /* Start the conversion of group 0. */
  Adc_StartGroupConversion(Adc_AdcGroup_000);

  /* Get the conversion status of Group0 after starting the group */
  GaaGroupStatus[4][1] = Adc_GetGroupStatus(Adc_AdcGroup_000);

  /* Wait till the conversion of group 0 is completed */
  while (ADC_STREAM_COMPLETED != Adc_GetGroupStatus(Adc_AdcGroup_000))
  {
    /*No Action Required*/
  };

  /* Disable the Group notification for the group 0 */
  Adc_DisableGroupNotification(Adc_AdcGroup_000);

  /*
   * API Adc_GetStreamLastPointer reads the number of valid samples stored in the result buffer
   * and a pointer to the top of the channel for the result of the last sample that completed the conversion.
   * The variable GucNumSamples1 will indicate the number of samples, and the pointer PtrToSample1
   * will be updated with the pointer to the streaming buffer which holds all the channel's digital output.
   */
  GucNumSamples1 = Adc_GetStreamLastPointer(Adc_AdcGroup_000, (Adc_ValueGroupType**)&PtrToSample1);

  /* Copy result data to application buffer */
  GddReadResultGroup0_Var2[0] = *PtrToSample1;

  /*
   * Stop the conversion of group 0, the conversion status of the group 0 is changed to ADC_IDLE, and the notification
   * status is disabled.
   */
  Adc_StopGroupConversion(Adc_AdcGroup_000);

  /* Get the conversion status of Group0 after stopping the group */
  GaaGroupStatus[4][3] = Adc_GetGroupStatus(Adc_AdcGroup_000);

  /*  Enable the channel in group */
  Adc_EnableChannel(Adc_AdcGroup_000, 0x0002);

  /*********************************************************************************************************************
   * Group1 configuration:
   * + Software trigger.
   * + Continuous conversion.
   * + Linear streaming access mode.
   * + Result access mode: POLLING mode without using DMA transfer.
   ********************************************************************************************************************/

  /*
   * On completion of the conversion, the call-back notification will be invoked only if the API
   * Adc_EnableGroupNotification is invoked.
   */
  Adc_EnableGroupNotification(Adc_AdcGroup_001);

  /* Start the conversion of group 1. */
  Adc_StartGroupConversion(Adc_AdcGroup_001);

  /* Get the conversion status of Group1 after starting the group */
  GaaGroupStatus[5][1] = Adc_GetGroupStatus(Adc_AdcGroup_001);

  /* Wait till the conversion of group 1 is completed */
  do
  {
    ret = Adc_ReadGroup(Adc_AdcGroup_001, (Adc_ValueGroupType *)GddReadResultGroup1_Var2);
  } while (ADC_STREAM_COMPLETED != Adc_GetGroupStatus(Adc_AdcGroup_001));

  /* Disable the Group notification for the group 1 */
  Adc_DisableGroupNotification(Adc_AdcGroup_001);

  /* Stop the conversion of group 1, the conversion status of the group 1 is changed to ADC_IDLE. */
  Adc_StopGroupConversion(Adc_AdcGroup_001);

  /* Get the conversion status of Group1 after stopping the group */
  GaaGroupStatus[5][3] = Adc_GetGroupStatus(Adc_AdcGroup_001);

  /*********************************************************************************************************************
   * Group2 configuration:
   * + Software trigger.
   * + Continuous conversion.
   * + Single access mode.
   * + Result access mode: POLLING mode with using DMA transfer
   ********************************************************************************************************************/

  /*
   * On completion of the conversion, the call-back notification will be invoked only if the API
   * Adc_EnableGroupNotification is invoked.
   */
  Adc_EnableGroupNotification(Adc_AdcGroup_002);

  /* Start the conversion of group 2. */
  Adc_StartGroupConversion(Adc_AdcGroup_002);

  /* Get the conversion status of Group2 after starting the group */
  GaaGroupStatus[6][1] = Adc_GetGroupStatus(Adc_AdcGroup_002);

  /* Wait till the conversion of group 2 is completed */
  do
  {
    ret = Adc_ReadGroup(Adc_AdcGroup_002, (Adc_ValueGroupType *)GddReadResultGroup2_Var2);
  } while (ADC_STREAM_COMPLETED != Adc_GetGroupStatus(Adc_AdcGroup_002));

  /* Disable the Group notification for the group 2 */
  Adc_DisableGroupNotification(Adc_AdcGroup_002);

  /* Stop the conversion of group 2, the conversion status of the group 2 is changed to ADC_IDLE. */
  Adc_StopGroupConversion(Adc_AdcGroup_002);

  /* Get the conversion status of Group2 after stopping the group */
  GaaGroupStatus[6][3] = Adc_GetGroupStatus(Adc_AdcGroup_002);

  /*********************************************************************************************************************
   * Group3 configuration:
   * + Hardware trigger.
   * + One shot conversion.
   * + Single access mode.
   * + Result access mode: ISR mode with using DMA transfer
   ********************************************************************************************************************/
  /*
   * On completion of the conversion, the call-back notification will be invoked only if the API
   * Adc_EnableGroupNotification is invoked.
   */
  Adc_EnableGroupNotification(Adc_AdcGroup_003);

  /*
   * Enable the hardware trigger for group 3, the external or timer triggers should be given only after calling this
   * API for the ADC conversion to start.
   */
  Adc_EnableHardwareTrigger(Adc_AdcGroup_003);

  /* Get the conversion status after enabling the group */
  GaaGroupStatus[7][1] = Adc_GetGroupStatus(Adc_AdcGroup_003);

  /* Provide timer trigger so that the conversion of group 3 can start */
  Start_Timer0();

  /* Wait till the conversion of group 3 is completed */
  while (ADC_STREAM_COMPLETED != Adc_GetGroupStatus(Adc_AdcGroup_003))
  {
    /*No Action Required*/
  };

  /* Disable the Group notification for the group 3 */
  Adc_DisableGroupNotification(Adc_AdcGroup_003);

  /* Read the result values */
  ret = Adc_ReadGroup(Adc_AdcGroup_003, (Adc_ValueGroupType *)GddReadResultGroup3_Var2);

  /*
   * Disable the hardware trigger for group 3, even if any external or timer triggers are given after calling this API,
   * the ADC conversion will not be started.
   */
  Adc_DisableHardwareTrigger(Adc_AdcGroup_003);

  /* Get the conversion status after disabling the group */
  GaaGroupStatus[7][3] = Adc_GetGroupStatus(Adc_AdcGroup_003);

}
/**********************************************************************************************************************
**                           Notification Functions                                                                  **
**********************************************************************************************************************/
#define ADC_START_SEC_APPL_CODE
#include "Adc_MemMap.h"

/* ========= VARIANT_1 ===== */
/* Notification of Variant 1 */
void IoHwAb_Adc_Notification_Group0(void)
{
  /* Call the notification function */

  /* Get the conversion status of Group0 when the conversion end notification callback is called */
  GaaGroupStatus[0][2] = Adc_GetGroupStatus(Adc_AdcGroup_000);
}

void IoHwAb_Adc_Notification_Group1(void)
{
  /* Call the notification function */

  /* Get the conversion status of Group1 when the conversion end notification callback is called */
  GaaGroupStatus[1][2] = Adc_GetGroupStatus(Adc_AdcGroup_001);
}

void IoHwAb_Adc_Notification_Group2(void)
{
  /* Call the notification function */

  /* Get the conversion status of Group2 when the conversion end notification callback is called */
  GaaGroupStatus[2][2] = Adc_GetGroupStatus(Adc_AdcGroup_002);
}

void IoHwAb_Adc_Notification_Group3(void)
{
  /* Call the notification function */

  /* Get the conversion status of Group3 when the conversion end notification callback is called */
  GaaGroupStatus[3][2] = Adc_GetGroupStatus(Adc_AdcGroup_003);
}

/* ========= VARIANT_2 ===== */
/* Notification of Variant 2 */
void IoHwAb_Adc_Notification_Group0_Variant2(void)
{
  /* Call the notification function */

  /* Get the conversion status of Group0 when the conversion end notification callback is called */
  GaaGroupStatus[4][2] = Adc_GetGroupStatus(Adc_AdcGroup_000);
}

void IoHwAb_Adc_Notification_Group1_Variant2(void)
{
  /* Call the notification function */

  /* Get the conversion status of Group1 when the conversion end notification callback is called */
  GaaGroupStatus[5][2] = Adc_GetGroupStatus(Adc_AdcGroup_001);
}

void IoHwAb_Adc_Notification_Group2_Variant2(void)
{
  /* Call the notification function */

  /* Get the conversion status of Group2 when the conversion end notification callback is called */
  GaaGroupStatus[6][2] = Adc_GetGroupStatus(Adc_AdcGroup_002);
}

void IoHwAb_Adc_Notification_Group3_Variant2(void)
{
  /* Call the notification function */

  /* Get the conversion status of Group3 when the conversion end notification callback is called */
  GaaGroupStatus[7][2] = Adc_GetGroupStatus(Adc_AdcGroup_003);
}

/* Notification in Adc HW Unit */
void IoHwAb_Adc_ErrNotification_000(uint8 LucChannel)
{
  /* Call the notification function */
  (void)LucChannel;
}

void IoHwAb_Adc_ErrNotificationSG(uint8 LucScanGroup)
{
  /* Call the notification function */
  (void)LucScanGroup;
}

#define ADC_STOP_SEC_APPL_CODE
#include "Adc_MemMap.h"
/***********************************************************************************************************************
**                          End of File                                                                               **
***********************************************************************************************************************/
