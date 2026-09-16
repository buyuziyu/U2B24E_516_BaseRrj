/*******************************************************************************
|    Header File Inclusion
|******************************************************************************/
#include "user_icuif.h"
#include "r_cg_macrodriver.h"
#include "r_sys.h"

#include "Mcu.h"

/*******************************************************************************
|    Macro Definition
|******************************************************************************/
#define ICU_TIMESTAMP_MAX     10U

/*******************************************************************************
|    Typedef Definition
|******************************************************************************/

/*******************************************************************************
|    variables Declaration  
|******************************************************************************/
Icu_DutyCycleType GddDutyCycleValues[6];

Icu_ValueType GusTimestamp_0[ICU_TIMESTAMP_MAX];
Icu_ValueType GusTimestamp_1[ICU_TIMESTAMP_MAX];
Icu_ValueType GusTimestamp_2[ICU_TIMESTAMP_MAX];

/*******************************************************************************
|    code Declaration  
|******************************************************************************/

void IcuIf_Init(void)
{
    Icu_Init(Icu_Config);

    // DNFA10.DNFAEN_TAUD0 = 0x0015;
    // DNFA11.DNFAEN_TAUD1 = 0x0001;
    // DNFA.EN_TAUD2 = 0x0041;

    // PIC1.TAUD0SEL.UINT32 = 0x00000444;
    // PIC1.TAUD1SEL.UINT32 = 0x00000004;
    // PIC1.SELB_TAUD2I.UINT16 = 0x0082;

    // Icu_EnableEdgeDetection(IcuConf_IcuChannel_IcuChannel_INTP16);
    // Icu_EnableEdgeDetection(IcuConf_IcuChannel_IcuChannel_INTP17);
    // Icu_EnableNotification(IcuConf_IcuChannel_IcuChannel_INTP16);
    // Icu_EnableNotification(IcuConf_IcuChannel_IcuChannel_INTP17);

    // Icu_EnableEdgeDetection(IcuConf_IcuChannel_IcuChannel_TAUD2I13);
    // Icu_EnableNotification(IcuConf_IcuChannel_IcuChannel_TAUD2I13);

    // Icu_EnableWakeup(IcuConf_IcuChannel_IcuChannel_INTP17);

    // Icu_SetActivationCondition(IcuConf_IcuChannel_IcuChannel_timestamp_0, ICU_BOTH_EDGES);
    // Icu_EnableNotification(IcuConf_IcuChannel_IcuChannel_timestamp_0);
    // Icu_StartTimestamp(IcuConf_IcuChannel_IcuChannel_timestamp_0, &GusTimestamp_0[0], ICU_TIMESTAMP_MAX, 5);

    // Icu_SetActivationCondition(IcuConf_IcuChannel_IcuChannel_timestamp_1, ICU_BOTH_EDGES);
    // Icu_EnableNotification(IcuConf_IcuChannel_IcuChannel_timestamp_1);
    // Icu_StartTimestamp(IcuConf_IcuChannel_IcuChannel_timestamp_1, &GusTimestamp_1[0], ICU_TIMESTAMP_MAX, 5);

    // Icu_SetActivationCondition(IcuConf_IcuChannel_IcuChannel_timestamp_2, ICU_BOTH_EDGES);
    // Icu_EnableNotification(IcuConf_IcuChannel_IcuChannel_timestamp_2);
    // Icu_StartTimestamp(IcuConf_IcuChannel_IcuChannel_timestamp_2, &GusTimestamp_2[0], ICU_TIMESTAMP_MAX, 5);

}

void IcuIf_Sample_test(void)
{
    /* Signal measurement: Duty */
    // Icu_StartSignalMeasurement (IcuConf_IcuChannel_IcuChannel_5V_PWMIO_0);

    /* Signal DutyCycle has been captured */
    // Icu_GetDutyCycleValues(IcuConf_IcuChannel_IcuChannel_5V_PWMIO_0, &GddDutyCycleValues[0]);

}


FUNC(void, ICU_APPL_CODE) ICU_Notification_INTP16 (void)
{
    // Mcu_ClearAndSetWakeUpFactor(McuConf_McuModeSettingConf_McuModeSettingConf_deepstop);
    // Mcu_SetMode(McuConf_McuModeSettingConf_McuModeSettingConf_deepstop);
}

FUNC(void, ICU_APPL_CODE) ICU_Notification_INTP17 (void)
{

}

FUNC(void, ICU_APPL_CODE) ICU_Notification_TAUD2I13 (void)
{

}

FUNC(void, ICU_APPL_CODE) ICU_Notification_timestamp_0 (void)
{

}

FUNC(void, ICU_APPL_CODE) ICU_Notification_timestamp_1 (void)
{

}

FUNC(void, ICU_APPL_CODE) ICU_Notification_timestamp_2 (void)
{

}

FUNC(void, ICU_APPL_CODE) IcuSignalEdgeDetectionNotification_INTP13 (void){}
