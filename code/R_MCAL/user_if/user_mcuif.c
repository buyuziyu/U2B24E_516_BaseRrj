/*******************************************************************************
|    Header File Inclusion
|******************************************************************************/
#include "user_mcuif.h"
#include "Mcu.h"
#include "Gpt.h"

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

void McuIf_Init(void)
{   
    volatile uint32 LucIntCount;

	/* Mcu Clk Configuration */
    Mcu_Init(Mcu_Config);

    /* Initialize clock */
    #if (MCU_INIT_CLOCK == STD_ON)
    /* Canceling Module standby mode of GTM follow HWUM caution */  
    if (MCU_SWMRESS_GTM == 0)
    {
        MCU_MSRKCPROT = 0xA5A5A501;
        MCU_MSR_GTM   = 0x00;
        MCU_MSRKCPROT = 0xA5A5A500;
    }
    Mcu_InitClock(MCU_MCUCLOCKSETTINGCONFIG);
    #endif /* (MCU_INIT_CLOCK == STD_ON) */

    LucIntCount = 10000;
    while((LucIntCount > 0) && (MCU_PLL_LOCKED != Mcu_GetPllStatus()))
    {
        LucIntCount--;
    }

    #if (MCU_NO_PLL == STD_OFF)
    Mcu_DistributePllClock();
    #endif /* (MCU_NO_PLL == STD_OFF) */

    /* Invoke Mcu_SetMode with RUN MODE */
    Mcu_SetMode(MCU_MODE_SETTING_0);


    Mcu_ReleaseIoBufferHold();

}

void user_ERROROUT_set(void)
{
    ECM.KCPROT.UINT32 = 0xA5A5A501;

    ECM.PEM.UINT32 = 0x00000003;
    ECM.ESSTC0.UINT32 = 0xFFFFFFFF;
	ECM.ESSTC1.UINT32 = 0xFFFFFFFF;
    ECMM.ESET.UINT32 = 0x00000001;
    //ECM.PEM = 0x00000000;

    ECM.KCPROT.UINT32 = 0xA5A5A500;
}

void user_ERROROUT_clr(void)
{
    ECM.KCPROT.UINT32 = 0xA5A5A501;

    ECM.PEM.UINT32 = 0x00000003;
    ECM.ESSTC0.UINT32 = 0xFFFFFFFF;
	ECM.ESSTC1.UINT32 = 0xFFFFFFFF;
    ECMM.ECLR.UINT32 = 0x00000001;
    //ECM.PEM.UINT32 = 0x00000000;

    ECM.KCPROT.UINT32 = 0xA5A5A500;
}

FUNC(void, MCU_APPL_CODE) Mcu_EcmNotification_EI(uint16 McuErrorNumber)
{
    //INFO("ECM Notification\r\n");

    //Gpt_StopTimer(GPT_OSTM01_CH0);

    // ECM.KCPROT = 0xA5A5A501;

    // ECM.PEM = 0x00000003;
    // ECM.ESSTC0 = 0xFFFFFFFF;
	// ECM.ESSTC1 = 0xFFFFFFFF;
    // ECMM.ESET = 0x00000001;
    // //ECM.PEM = 0x00000000;

    // ECM.PEM = 0x00000003;
    // ECM.ESSTC0 = 0xFFFFFFFF;
	// ECM.ESSTC1 = 0xFFFFFFFF;
    // ECMM.ECLR = 0x00000001;
    // //ECM.PEM = 0x00000000;

    // ECM.KCPROT = 0xA5A5A500;
}
FUNC(void, MCU_APPL_CODE) Mcu_EcmNotification_FE(uint16 McuErrorNumber)
{

}

FUNC(void, MCU_APPL_CODE) Mcu_EcmNotification_DCLS(uint16 McuErrorNumber)
{

}

FUNC(void, MCU_PUBLIC_CODE) MCU_RESET_CALLOUT(void)
{

}

void DCLSCOMPAREERRORPE0_test(void)
{
    __asm(
            "mov 0x11111111, r12\n\t"
            "mov 0x22222222, r13\n\t"
            "LDSR r12, 0, 12\n\t"
            "LDSR r13, 1, 12\n\t"
            "STSR 0, r12, 12\n\t"
            "STSR 0, r13, 12\n\t"
            "mov 0xfdc0f000, r10\n\t"
            "st.w r12, 0[r10]\n\t"
        );
}

void DCLSCOMPAREERRORPE1_test(void)
{
    __asm(
            "mov 0x11111111, r12\n\t"
            "mov 0x22222222, r13\n\t"
            "LDSR r12, 0, 12\n\t"
            "LDSR r13, 1, 12\n\t"
            "STSR 0, r12, 12\n\t"
            "STSR 0, r13, 12\n\t"
            "mov 0xfda09000, r10\n\t"
            "st.w r12, 0[r10]\n\t"
        );
}


void Mcu_EcmNotification(uint16 EcmErrorNum)
{
    
}
