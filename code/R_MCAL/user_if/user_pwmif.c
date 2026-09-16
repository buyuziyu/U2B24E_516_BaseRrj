/*******************************************************************************
|    Header File Inclusion
|******************************************************************************/
#include "r_cg_macrodriver.h"
#include "user_pwmif.h"

/*******************************************************************************
|    Macro Definition
|******************************************************************************/

/*******************************************************************************
|    Typedef Definition
|******************************************************************************/

/*******************************************************************************
|    variables Declaration  
|******************************************************************************/

/*******************************************************************************
|    code Declaration  
|******************************************************************************/

void PwmIf_Init(void)
{
    Pwm_Init(Pwm_Config);
}

void PwmIf_Start(void)
{
    // Pwm_SetPeriodAndDuty(PwmConf_PwmChannel_PwmChannel_00_master, 0x7FFF, 0x2000);
    //Pwm_SetDutyCycle(PwmConf_PwmDiagChannel_PwmDiagChannel, 0x2000);
    // Pwm_SetDutyCycle(PwmConf_PwmChannel_PwmChannel_00_slave, 0x8000); 
    // Pwm_SetDutyCycle(PwmConf_PwmChannel_PwmChannel_00_slave, 0x2000);
    // Pwm_SetDutyCycle(PwmConf_PwmChannel_PwmChannel_00_slave, 0x00); 
    // Pwm_SetDutyCycle(PwmConf_PwmChannel_PwmChannel_00_slave, 0x7FFF);
    // Pwm_EnableNotification(PwmConf_PwmChannel_PwmChannel_00_slave,PWM_BOTH_EDGES);
    // Pwm_EnableNotification(PwmConf_PwmDiagChannel_PwmDiagChannel,PWM_BOTH_EDGES);
    // INTC2.EIC400.BIT.EIMK400 = _INT_PROCESSING_ENABLED;
    // INTC2.EIC410.BIT.EIMK410 = _INT_PROCESSING_ENABLED;
}



/******************************************************************************
    user callback 
******************************************************************************/
FUNC(void, PWM_APPL_CODE) Pwm_Notification_PwmChannel (void)
{

}

FUNC(void, PWM_APPL_CODE) Pwm_Notification_PwmChannel_001 (void)
{
    
}

FUNC(void, PWM_APPL_CODE) PwmChGroup0Notification (uint32 LulIntFactor)
{

}
FUNC(void, PWM_APPL_CODE) PwmChGroup1Notification (uint32 LulIntFactor)
{

}
FUNC(void, PWM_APPL_CODE) PwmChGroup2Notification (uint32 LulIntFactor)
{

}


FUNC(void, PWM_APPL_CODE) PwmNotification_Master (void)
{

}

FUNC(void, PWM_APPL_CODE) PwmNotification_Slave (void)
{
    
}
