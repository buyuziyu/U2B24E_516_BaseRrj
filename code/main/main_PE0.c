/*******************************************************************************
|    Header File Inclusion
|******************************************************************************/
#include "dr7f7025bx_f_0.h"

#include "r_cg_macrodriver.h"
#include "Compiler.h"

#include "Dio.h"

#include "r_sys.h"
#include "user_mcuif.h"

/* SMC header files <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/
//#include "Config_INTC.h"
//#include "Config_STBC.h"
/* SMC header files <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/

/*******************************************************************************
|    Macro Definition
|******************************************************************************/
#define PEID_PE0                   0x00UL

/*******************************************************************************
|    variables Declaration  
|******************************************************************************/
uint8_t CoreID0;
uint8_t u8Counter = 0u;

uint8_t u8LEDFLIP_PE1 = 0U;
uint8_t u8LEDFLIP_PE2 = 0U;
uint8_t u8LEDFLIP_PE3 = 0U;

uint8_t u8LED1FLIP = 0U;

uint32_t u32BistResult[77] = {0u};

/*******************************************************************************
|    code Declaration  
|******************************************************************************/
int main(void)
{
    uint32 u32Index = 0u;

    u32BistResult[0] = BIST.LBISTREF1.UINT32;
    u32BistResult[1] = BIST.LBISTREF2.UINT32;
    u32BistResult[2] = BIST.MBISTREF1.UINT32;
    u32BistResult[3] = BIST.MBISTREF3.UINT32;
    u32BistResult[4] = BIST.MBISTREF4.UINT32;
    u32BistResult[5] = BIST.MBISTREF5.UINT32;
    u32BistResult[6] = BIST.MBISTREF6.UINT32;
    u32BistResult[7] = BIST.MBISTREF7.UINT32;
    u32BistResult[8] = BIST.MBISTREF8.UINT32;
    u32BistResult[9] = BIST.LBISTSIG1.UINT32;
    u32BistResult[10] = BIST.LBISTSIG2.UINT32;
    u32BistResult[11] = BIST.MBISTSIG1.UINT32;
    u32BistResult[12] = BIST.MBISTSIG3.UINT32;
    u32BistResult[13] = BIST.MBISTSIG4.UINT32;
    u32BistResult[14] = BIST.MBISTSIG5.UINT32;
    u32BistResult[15] = BIST.MBISTSIG6.UINT32;
    u32BistResult[16] = BIST.MBISTSIG7.UINT32;
    u32BistResult[17] = BIST.MBISTSIG8.UINT32;

    for(u32Index = 0u; u32Index < 8u; u32Index++)
    {
        u32BistResult[18 + u32Index] = (*(volatile uint32  *)(0xFF9A6028UL + 4*u32Index));   /* MBIST1FTAGn*/
        u32BistResult[44 + u32Index] = (*(volatile uint32  *)(0xFF9A6088UL + 4*u32Index));   /* MBIST1ECCn*/

    }

    for(u32Index = 0u; u32Index < 3u; u32Index++)
    {
        u32BistResult[26 + u32Index] = (*(volatile uint32  *)(0xFF9A6100UL + 4*u32Index));   /* MBIST3FTAGn*/
        u32BistResult[52 + u32Index] = (*(volatile uint32  *)(0xFF9A6200UL + 4*u32Index));   /* MBIST3ECCn*/
    }

    for(u32Index = 0u; u32Index < 2u; u32Index++)
    {
        u32BistResult[29 + u32Index] = (*(volatile uint32  *)(0xFF9A6110UL + 4*u32Index));   /* MBIST4FTAGn*/
        u32BistResult[31 + u32Index] = (*(volatile uint32  *)(0xFF9A6120UL + 4*u32Index));   /* MBIST5FTAGn*/
        u32BistResult[33 + u32Index] = (*(volatile uint32  *)(0xFF9A6130UL + 4*u32Index));   /* MBIST6FTAGn*/
        u32BistResult[35 + u32Index] = (*(volatile uint32  *)(0xFF9A6140UL + 4*u32Index));   /* MBIST7FTAGn*/

        u32BistResult[55 + u32Index] = (*(volatile uint32  *)(0xFF9A6210UL + 4*u32Index));   /* MBIST4ECCn*/
        u32BistResult[57 + u32Index] = (*(volatile uint32  *)(0xFF9A6220UL + 4*u32Index));   /* MBIST5ECCn*/
        u32BistResult[59 + u32Index] = (*(volatile uint32  *)(0xFF9A6230UL + 4*u32Index));   /* MBIST6ECCn*/
        u32BistResult[61 + u32Index] = (*(volatile uint32  *)(0xFF9A6240UL + 4*u32Index));   /* MBIST7ECCn*/
    }

    for(u32Index = 0u; u32Index < 7u; u32Index++)
    {
        u32BistResult[37 + u32Index] = (*(volatile uint32  *)(0xFF9A6150UL + 4*u32Index));   /* MBIST8FTAGn*/
        u32BistResult[63 + u32Index] = (*(volatile uint32  *)(0xFF9A6250UL + 4*u32Index));   /* MBIST8ECCn*/
    }

    u32BistResult[70] = BIST.BSEQ0ST.UINT32;
    u32BistResult[71] = BIST.BSEQ0STB.UINT32;
    u32BistResult[72] = BIST.ST.UINT32;
    u32BistResult[73] = BIST.BSEQ0SEL.UINT32;
    u32BistResult[74] = SYS0.BSEQ0CTL.UINT32;
    u32BistResult[75] = SYS0.BSEQ1CTL.UINT32;
    u32BistResult[76] = SYS0.BSEQ2CTL.UINT32;
    
    R_PBG_Reassign_Permissions();
    CoreID0 = STSR(0,2);

    /* Initialization */
    McuIf_Init();
    DISABLE_INTERRUPT();

    user_STBC_Init();
    user_Interrupt_Init_PE0();

    PortIf_Init();
    GptIf_Init();

    /* MCAL Module Init <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/
    /* MCAL Module Init >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/


    /* SMC Module Init <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/
    /* SMC Module Init >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/

    ENABLE_INTERRUPT();    

    /* Start */
    R_BR_SetChk(0U);
    while (!R_BR_GetSync(0U));

    GptIf_Start();
    
    while(1)
    {
        if(ostm_1ms_flg_PE0)
        {
            ostm_1ms_flg_PE0 = 0;
        }

        if(ostm_10ms_flg_PE0)
        {
            ostm_10ms_flg_PE0 = 0;
        }

        if(ostm_20ms_flg_PE0)
        {
            ostm_20ms_flg_PE0 = 0;
        }

        if(ostm_100ms_flg_PE0)
        {
            ostm_100ms_flg_PE0 = 0;
        }

        if(ostm_1s_flg_PE0)
        {
            ostm_1s_flg_PE0 = 0;

            u8LED1FLIP += 1u;
            if((u8LED1FLIP % 2u) == 0u)
            {
                PortIf_LEDCtrl(LED9,   LEDON);
                PortIf_LEDCtrl(LED10,  LEDON);
                PortIf_LEDCtrl(LED11,  LEDON);
            }
            else \
            if((u8LED1FLIP % 2u) == 1u)
            {
                PortIf_LEDCtrl(LED9,   LEDOFF);
                PortIf_LEDCtrl(LED10,  LEDOFF);
                PortIf_LEDCtrl(LED11,  LEDOFF);
            }
        }
    }
}
