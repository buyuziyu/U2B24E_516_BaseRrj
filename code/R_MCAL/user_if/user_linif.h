#ifndef _USER_LINIF_H_
#define _USER_LINIF_H_

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "Lin.h"

/*******************************************************************************
|    Macro Definition
|******************************************************************************/
#define LIN_COUNT_INITIAL_VALUE           (uint8)0x00
#define LIN_DATA_SIZE                     (uint8)0x08
#define LIN_WAIT_5MS                      (uint8)0x05
#define LIN_SEND_PID                      (uint8)0xDD
#define LIN_RESP_PID                      (uint8)0x39
#define LIN_CHANNEL_0                     (uint8)0x00
#define LIN_CHANNEL_1                     (uint8)0x01
#define LIN_MAX_TIMEOUT_COUNT             (uint8)0x10

/* RLIN3 Status Register */
#define LIN_RLN31LST        (*((volatile uint8 *)0xFFC7C012UL))
#define LIN_RLN31LEST       (*((volatile uint8 *)0xFFC7C013UL))

/*******************************************************************************
|    typedef
|******************************************************************************/

/*******************************************************************************
|    variables Declaration  
|******************************************************************************/

/*******************************************************************************
|    Global Function Prototypes
|******************************************************************************/

void LinIf_Init(void);
void LinIf_Sample_test(void);
void IinIf_timer_task(void);

#endif
