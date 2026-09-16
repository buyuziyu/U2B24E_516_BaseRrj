#include "r_cg_macrodriver.h"
#include "r_sys.h"
#include "Compiler.h"
#include "user_mcuif.h"
#include "r_sys.h"
#include "r_br.h"
/*******************************************************************************
|    Macro Definition
|******************************************************************************/

uint8_t CoreID2;

extern uint8_t u8LEDFLIP_PE2;

/**********************************************************
* main_PE2 from U2Ax_startup_PEn.850
**********************************************************/
void main_PE2(void)
{
    R_BR_SetChk(0U);
    while (!R_BR_GetSync(0U));

    CoreID2 = STSR(0,2);

    while(1)
    {
        if(ostm_1ms_flg_PE2)
        {
            ostm_1ms_flg_PE2 = 0;
        }

        if(ostm_10ms_flg_PE2)
        {
            ostm_10ms_flg_PE2 = 0;
        }

        if(ostm_20ms_flg_PE2)
        {
            ostm_20ms_flg_PE2 = 0;
        }

        if(ostm_100ms_flg_PE2)
        {
            ostm_100ms_flg_PE2 = 0;
        }

        if(ostm_1s_flg_PE2)
        {
            ostm_1s_flg_PE2 = 0;

            u8LEDFLIP_PE2 = 1u;
        }
    }
}

