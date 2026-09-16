#ifndef _USER_MCUIF_H_
#define _USER_MCUIF_H_

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "Mcu.h"
#include "r_cg_macrodriver.h"

#include "user_mcuif.h"
#include "user_wdgif.h"
#include "user_portif.h"
#include "user_adcif.h"
#include "user_gptif.h"
#include "user_pwmif.h"
#include "user_icuif.h"
#include "user_spiif.h"
#include "user_canif.h"
#include "user_linif.h"
#include "user_ethif.h"

/*******************************************************************************
|    Macro Definition
|******************************************************************************/
#define MCU_MSRKCPROT                *((volatile uint32 *)0xff981710UL)
#define MCU_SWMRESS_GTM              *((volatile uint32 *)0xff980924UL)
#define MCU_MSR_GTM                  *((volatile uint32 *)0xff981020UL)

#define MCU_MCUCLOCKSETTINGCONFIG \
                  McuConf_McuClockSettingConfig_McuClockSettingConfig

#define MCU_MODE_SETTING_0 \
                  McuConf_McuModeSettingConf_McuModeSettingConf

/*******************************************************************************
|    typedef
|******************************************************************************/

/*******************************************************************************
|    variables Declaration  
|******************************************************************************/

/*******************************************************************************
|    Global Function Prototypes
|******************************************************************************/
extern void McuIf_Init(void);

void user_ERROROUT_set(void);
void user_ERROROUT_clr(void);

void DCLSCOMPAREERRORPE0_test(void);
void DCLSCOMPAREERRORPE1_test(void);

#endif
