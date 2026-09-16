/*******************************************************************************
|    Header File Inclusion
|******************************************************************************/
#include "user_gptif.h"
#include "r_cg_macrodriver.h"
#include "user_linif.h"
#include "r_sys.h"

/*******************************************************************************
|    Macro Definition
|******************************************************************************/

/*******************************************************************************
|    Typedef Definition
|******************************************************************************/

/*******************************************************************************
|    variables Declaration  
|******************************************************************************/
uint32_t cnt_ostm0 = 0;

uint8_t ostm_1ms_flg_PE0 = 0u;
uint8_t ostm_10ms_flg_PE0 = 0u;
uint8_t ostm_20ms_flg_PE0 = 0u;
uint8_t ostm_100ms_flg_PE0 = 0u;
uint8_t ostm_1s_flg_PE0 = 0u;

uint8_t ostm_1ms_flg_PE1 = 0u;
uint8_t ostm_10ms_flg_PE1 = 0u;
uint8_t ostm_20ms_flg_PE1 = 0u;
uint8_t ostm_100ms_flg_PE1 = 0u;
uint8_t ostm_1s_flg_PE1 = 0u;

uint8_t ostm_1ms_flg_PE2 = 0u;
uint8_t ostm_10ms_flg_PE2 = 0u;
uint8_t ostm_20ms_flg_PE2 = 0u;
uint8_t ostm_100ms_flg_PE2 = 0u;
uint8_t ostm_1s_flg_PE2 = 0u;

uint8_t ostm_1ms_flg_PE3 = 0u;
uint8_t ostm_10ms_flg_PE3 = 0u;
uint8_t ostm_20ms_flg_PE3 = 0u;
uint8_t ostm_100ms_flg_PE3 = 0u;
uint8_t ostm_1s_flg_PE3 = 0u;

uint8_t ostm_1ms_flg_PE4 = 0u;
uint8_t ostm_10ms_flg_PE4 = 0u;
uint8_t ostm_20ms_flg_PE4 = 0u;
uint8_t ostm_100ms_flg_PE4 = 0u;
uint8_t ostm_1s_flg_PE4 = 0u;

uint8_t ostm_1ms_flg_PE5 = 0u;
uint8_t ostm_10ms_flg_PE5 = 0u;
uint8_t ostm_20ms_flg_PE5 = 0u;
uint8_t ostm_100ms_flg_PE5 = 0u;
uint8_t ostm_1s_flg_PE5 = 0u;

/*******************************************************************************
|    code Declaration  
|******************************************************************************/

void GptIf_Init(void)
{
    Gpt_Init(Gpt_Config);
}

void GptIf_Start(void)
{  
    Gpt_StartTimer(GPT_OSTM00_CH0,80000-1);           //1ms
    Gpt_EnableNotification(GPT_OSTM00_CH0);

    // Gpt_StartTimer(GPT_OSTM01_CH0,80000000-1);        
    // Gpt_EnableNotification(GPT_OSTM01_CH0);

//    Gpt_StartTimer(GPT_TAUD1_CH05, (80000-1)*1000);
    // Gpt_EnableNotification(GPT_TAUD1_CH05);
}



/******************************************************************************
    user callback 
******************************************************************************/
void Gpt_Notification_OSTM0(void)
{
    cnt_ostm0++;

    ostm_1ms_flg_PE0 = 1;
    ostm_1ms_flg_PE1 = 1;
    ostm_1ms_flg_PE2 = 1;
    ostm_1ms_flg_PE3 = 1;

    if(!(cnt_ostm0%10))
    {
        ostm_10ms_flg_PE0 = 1;
        ostm_10ms_flg_PE1 = 1;
        ostm_10ms_flg_PE2 = 1;
        ostm_10ms_flg_PE3 = 1;
    }
    if(!(cnt_ostm0%20))
    {
        ostm_20ms_flg_PE0 = 1;
        ostm_20ms_flg_PE1 = 1;
        ostm_20ms_flg_PE2 = 1;
        ostm_20ms_flg_PE3 = 1;
    }
    if(!(cnt_ostm0%100))
    {
        ostm_100ms_flg_PE0 = 1;
        ostm_100ms_flg_PE1 = 1;
        ostm_100ms_flg_PE2 = 1;
        ostm_100ms_flg_PE3 = 1;
    }
    if(!(cnt_ostm0%1000))
    {
        ostm_1s_flg_PE0 = 1;
        ostm_1s_flg_PE1 = 1;
        ostm_1s_flg_PE2 = 1;
        ostm_1s_flg_PE3 = 1;
    }

    if(sys_delay_cnt)
    {
        sys_delay_cnt--;
    }

#if LIN_TEST_MCAL
    IinIf_timer_task();
#endif

}

void Gpt_Notification_OSTM1(void){}
void Gpt_Notification_OSTM2(void){}
void Gpt_Notification_OSTM3(void){}

FUNC(void, GPT_APPL_CODE) Gpt_Notification_TAUD1(void){}
