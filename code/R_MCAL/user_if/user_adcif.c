/*******************************************************************************
|    Header File Inclusion
|******************************************************************************/
#include "r_cg_macrodriver.h"
#include "user_adcif.h"

#include "Dio.h"

/*******************************************************************************
|    Macro Definition
|******************************************************************************/

/*******************************************************************************
|    Typedef Definition
|******************************************************************************/

/*******************************************************************************
|    variables Declaration  
|******************************************************************************/
volatile Adc_ValueGroupType    GddReadResultGroup_1_0[4];
volatile Adc_ValueGroupType    GddReadResultGroup_1_1[4];
volatile Adc_ValueGroupType    GddReadResultGroup_1_2[4];
volatile Adc_ValueGroupType    GddReadResultGroup_1_3[4];
volatile Adc_ValueGroupType    GddReadResultGroup_1_4[16*10];



/*******************************************************************************
|    code Declaration  
|******************************************************************************/

void AdcIf_Init(void)
{
    uint8_t ret;

    Adc_Init(Adc_Config);

    // Adc_EnableGroupNotification(AdcConf_AdcGroup_AdcGroup_1_4);

    // ret = Adc_SetupResultBuffer(AdcConf_AdcGroup_AdcGroup_1_0,(Adc_ValueGroupType *)GddReadResultGroup_1_0);
    // ret = Adc_SetupResultBuffer(AdcConf_AdcGroup_AdcGroup_1_1,(Adc_ValueGroupType *)GddReadResultGroup_1_1);
    // ret = Adc_SetupResultBuffer(AdcConf_AdcGroup_AdcGroup_1_2,(Adc_ValueGroupType *)GddReadResultGroup_1_1);
    // ret = Adc_SetupResultBuffer(AdcConf_AdcGroup_AdcGroup_1_3,(Adc_ValueGroupType *)GddReadResultGroup_1_3);
    // ret = Adc_SetupResultBuffer(AdcConf_AdcGroup_AdcGroup_1_4,(Adc_ValueGroupType *)GddReadResultGroup_1_4);

    // Adc_EnableHardwareTrigger(4);
}


void AdcIf_Sample_test(void)
{
    uint8_t ret;

    // do
    // {
    //     ret = Adc_ReadGroup(AdcConf_AdcGroup_AdcGroup_1_4, (Adc_ValueGroupType *)GddReadResultGroup_1_4);
    // } 
    // while (ADC_STREAM_COMPLETED != Adc_GetGroupStatus(AdcConf_AdcGroup_AdcGroup_1_4));
}



/******************************************************************************
    user callback 
******************************************************************************/
FUNC(void, ADC_APPL_CODE) Adc_Notification_1_0(void){}
FUNC(void, ADC_APPL_CODE) Adc_Notification_1_1(void){}
FUNC(void, ADC_APPL_CODE) Adc_Notification_1_2(void){}
FUNC(void, ADC_APPL_CODE) Adc_Notification_1_3(void){}
FUNC(void, ADC_APPL_CODE) Adc_Notification_1_4(void){}
