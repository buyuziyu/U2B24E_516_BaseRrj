#include "r_cg_macrodriver.h"
#include "Compiler.h"
#include "r_sys.h"
#include "r_br.h"

uint8_t CoreID5;

/**********************************************************
* main_PE5 from U2Ax_startup_PEn.850
**********************************************************/
void main_PE5(void)
{
    R_BR_SetChk(0U);
    while (!R_BR_GetSync(0U));
    
    CoreID5 = STSR(0,2);

    while(1)
    {
        ;
    }
}
