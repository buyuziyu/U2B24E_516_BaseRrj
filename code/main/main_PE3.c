#include "r_cg_macrodriver.h"
#include "Compiler.h"
#include "r_sys.h"
#include "r_br.h"

uint8_t CoreID3;

/**********************************************************
* main_PE3 from U2Ax_startup_PEn.850
**********************************************************/
void main_PE3(void)
{
    R_BR_SetChk(0U);
    while (!R_BR_GetSync(0U));
    
    CoreID3 = STSR(0,2);

    while(1)
    {
        ;
    }
}
