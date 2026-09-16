#include "r_cg_macrodriver.h"
#include "Compiler.h"
#include "r_sys.h"
#include "r_br.h"

uint8_t CoreID4;

/**********************************************************
* main_PE4 from U2Ax_startup_PEn.850
**********************************************************/
void main_PE4(void)
{
    R_BR_SetChk(0U);
    while (!R_BR_GetSync(0U));
    
    CoreID4 = STSR(0,2);

    while(1)
    {
        ;
    }
}
