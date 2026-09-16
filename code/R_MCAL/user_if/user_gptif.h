#ifndef _USER_GPTIF_H_
#define _USER_GPTIF_H_

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "Gpt.h"
#include "r_cg_macrodriver.h"
/*******************************************************************************
|    Macro Definition
|******************************************************************************/

/*******************************************************************************
|    typedef
|******************************************************************************/

/*******************************************************************************
|    variables Declaration  
|******************************************************************************/
extern uint8_t ostm_1ms_flg_PE0;
extern uint8_t ostm_10ms_flg_PE0;
extern uint8_t ostm_20ms_flg_PE0;
extern uint8_t ostm_100ms_flg_PE0;
extern uint8_t ostm_1s_flg_PE0;

extern uint8_t ostm_1ms_flg_PE1;
extern uint8_t ostm_10ms_flg_PE1;
extern uint8_t ostm_20ms_flg_PE1;
extern uint8_t ostm_100ms_flg_PE1;
extern uint8_t ostm_1s_flg_PE1;

extern uint8_t ostm_1ms_flg_PE2;
extern uint8_t ostm_10ms_flg_PE2;
extern uint8_t ostm_20ms_flg_PE2;
extern uint8_t ostm_100ms_flg_PE2;
extern uint8_t ostm_1s_flg_PE2;

extern uint8_t ostm_1ms_flg_PE3;
extern uint8_t ostm_10ms_flg_PE3;
extern uint8_t ostm_20ms_flg_PE3;
extern uint8_t ostm_100ms_flg_PE3;
extern uint8_t ostm_1s_flg_PE3;

extern uint8_t ostm_1ms_flg_PE4;
extern uint8_t ostm_10ms_flg_PE4;
extern uint8_t ostm_20ms_flg_PE4;
extern uint8_t ostm_100ms_flg_PE4;
extern uint8_t ostm_1s_flg_PE4;

extern uint8_t ostm_1ms_flg_PE5;
extern uint8_t ostm_10ms_flg_PE5;
extern uint8_t ostm_20ms_flg_PE5;
extern uint8_t ostm_100ms_flg_PE5;
extern uint8_t ostm_1s_flg_PE5;

/*******************************************************************************
|    Global Function Prototypes
|******************************************************************************/

void GptIf_Init(void);
void GptIf_Start(void);

#endif
