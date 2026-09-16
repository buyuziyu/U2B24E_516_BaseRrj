/*******************************************************************************
|    Header File Inclusion
|******************************************************************************/
#include "r_sys.h"
#include "r_cg_macrodriver.h"

/*****************************************************************************
 Macro definitions
 *****************************************************************************/
#define KCPROT_ENABLE          0xA5A5A501UL
#define KCPROT_DISABLE         0xA5A5A500UL

/*****************************************************************************
 Typedef definitions
 *****************************************************************************/

/*****************************************************************************
 Global variables
 *****************************************************************************/
uint32 sys_delay_cnt = 0;
uint8_t MCU_INIT_FINISH = 0U;

extern R_INTC_UNINIT_INTERVAL[1][2];
extern R_INTC_UNINIT_SINGLE[10];

/*****************************************************************************
 Global static variables
 *****************************************************************************/

/*****************************************************************************
 Static functions
 *****************************************************************************/


/*****************************************************************************
--------------------- Global functions --------------------------------------
 *****************************************************************************/
/*****************************************************************************
 * Declaration : None
 * Description : None
 * Parameters  : None
 * Return      : None
 *****************************************************************************/
void user_STBC_Init(void)
{
    R_STBC_CfgMsr(MSR_RSCFD,        0x00UL);
    R_STBC_CfgMsr(MSR_FLXA,         0x00UL);
    R_STBC_CfgMsr(MSR_GTM,          0x00UL);
    R_STBC_CfgMsr(MSR_ETN,          0x00UL);
    R_STBC_CfgMsr(MSR_RSENT,        0x00UL);
    R_STBC_CfgMsr(MSR_MSPI,         0x00UL);
    R_STBC_CfgMsr(MSR_RLIN3,        0x00UL);
    R_STBC_CfgMsr(MSR_DSADC_CADC,   0x00UL);
    R_STBC_CfgMsr(MSR_ADCK_ISO,     0x00UL);
    R_STBC_CfgMsr(MSR_CXPI,         0x00UL);
    R_STBC_CfgMsr(MSR_MMCA,         0x00UL);
    R_STBC_CfgMsr(MSR_ENCA,         0x00UL);
    R_STBC_CfgMsr(MSR_PSI5,         0x00UL);
    R_STBC_CfgMsr(MSR_PSI5S,        0x00UL);
    R_STBC_CfgMsr(MSR_RHSIF,        0x00UL);
    R_STBC_CfgMsr(MSR_RHSB,         0x00UL);
    R_STBC_CfgMsr(MSR_RIIC,         0x00UL);
    R_STBC_CfgMsr(MSR_SFMA,         0x00UL);
    R_STBC_CfgMsr(MSR_TAPA,         0x00UL);
    R_STBC_CfgMsr(MSR_TAUD,         0x00UL);
    R_STBC_CfgMsr(MSR_TPBA,         0x00UL);
    R_STBC_CfgMsr(MSR_TSG3,         0x00UL);
    R_STBC_CfgMsr(MSR_OSTM,         0x00UL);
    R_STBC_CfgMsr(MSR_ATU,          0x00UL);
    R_STBC_CfgMsr(MSR_DFE,          0x00UL);
    R_STBC_CfgMsr(MSR_DFP,          0x00UL);
    R_STBC_CfgMsr(MSR_RDC,          0x00UL);
    R_STBC_CfgMsr(MSR_FCOMP,        0x00UL);
    R_STBC_CfgMsr(MSR_EMU,          0x00UL);
    R_STBC_CfgMsr(MSR_HRPWM,        0x00UL);
    R_STBC_CfgMsr(MSR_ADCK_AWO,     0x00UL);
    R_STBC_CfgMsr(MSR_RTCA,         0x00UL);
    R_STBC_CfgMsr(MSR_TAUJ_AWO,     0x00UL);
    R_STBC_CfgMsr(MSR_WDTB_AWO,     0x00UL);
}

void sys_Delay_ms(uint32 ms)
{
    sys_delay_cnt = ms;
    while(sys_delay_cnt)
    {
        ASM_NOP();
    }
}

/*****************************************************************************
 * Declaration : None
 * Description : None
 * Parameters  : None
 * Return      : None
 *****************************************************************************/
void user_Interrupt_Init_PE0(void)
{
    uint32_t u32Counter = 0u;

    for(u32Counter = 0u; u32Counter < 629u; u32Counter++)
    {
        if(u8Check_Interrupt_Init_Request(u32Counter))
        {
            R_INTC_Init(u32Counter,    INTC_EITB & INTC_EIMK | INTC_EIP(15UL));
        }
    }
}


uint8_t u8Check_Interrupt_Init_Request(uint32_t u32InterruptNumber)
{
    uint32_t u32Counter = 0u;

    for(u32Counter = 0u; u32Counter < (sizeof(R_INTC_UNINIT_INTERVAL) / 2); u32Counter++)
    {
        if((R_INTC_UNINIT_INTERVAL[u32Counter][0] <= u32InterruptNumber) && (u32InterruptNumber <= R_INTC_UNINIT_INTERVAL[u32Counter][1]))
        {
            return 0u;
        }
    }


    for(u32Counter = 0u; u32Counter < sizeof(R_INTC_UNINIT_SINGLE); u32Counter++)
    {
        if(u32InterruptNumber == R_INTC_UNINIT_SINGLE[u32Counter])
        {
            return 0u;
        }
    }

    return 1u;
}


/*****************************************************************************
 * Declaration : None
 * Description : None
 * Parameters  : None
 * Return      : None
 *****************************************************************************/
void Guard_Init(void)
{
    #define PEGKCPROT0   REG32(0XFFC6C000UL)
    #define PEGKCPROT1   REG32(0XFFC6C100UL)
    #define PBGKCPROT40  REG32(0XFFC75418UL)
    #define PBGKCPROT52  REG32(0XFFC7B018UL)

    #define PEGPROT0(m)  REG32(0XFFC6C000UL+0X40UL+m*0X10UL)
    #define PEGPROT1(m)  REG32(0XFFC6C100UL+0X40UL+m*0X10UL)
    
    #define PBG40PROT0(m)  REG32(0XFFC75300UL+m*0X08UL)
    #define PBG52PROT0(m)  REG32(0XFFC7A500UL+m*0X08UL)

    #define PBG50PROT0(m)  REG32(0XFFC7A300UL+m*0X08UL)

    PEGKCPROT0=0XA5A5A501UL;
    PEGKCPROT1=0XA5A5A501UL;
    PBGKCPROT40=0XA5A5A501UL;
    PBGKCPROT52=0XA5A5A501UL;

    /*Enable read/write Loacal RAM by DMA */
    PEGPROT0(0)|=0X143UL;
    PEGPROT0(1)|=0X143UL;
    PEGPROT0(2)|=0X143UL;

    PEGPROT0(3)|=0X143UL;
    PEGPROT0(4)|=0X143UL;
    PEGPROT0(5)|=0X143UL;

    PEGPROT0(6)|=0X143UL;
    PEGPROT0(7)|=0X143UL;

    PEGPROT1(0)|=0X143UL;
    PEGPROT1(1)|=0X143UL;
    PEGPROT1(2)|=0X143UL;

    PEGPROT1(3)|=0X143UL;
    PEGPROT1(4)|=0X143UL;
    PEGPROT1(5)|=0X143UL;

    PEGPROT1(6)|=0X143UL;
    PEGPROT1(7)|=0X143UL;

    /*Enable read/write MSPI RAM by DMA */
    PBG40PROT0(0)|=0X143UL;
    PBG40PROT0(1)|=0X143UL;
    PBG40PROT0(2)|=0X143UL;
    PBG40PROT0(3)|=0X143UL;
    PBG40PROT0(4)|=0X143UL;
    PBG40PROT0(5)|=0X143UL;
    PBG40PROT0(6)|=0X143UL;
    PBG40PROT0(7)|=0X143UL;

    PBG52PROT0(6)|=0X143UL;
    PBG52PROT0(7)|=0X143UL;
    PBG52PROT0(8)|=0X143UL;
    PBG52PROT0(9)|=0X143UL;
    PBG52PROT0(10)|=0X143UL;

    PBG50PROT0(0)|=0X143UL;
    PBG50PROT0(1)|=0X143UL;
    PBG50PROT0(2)|=0X143UL;
    PBG50PROT0(3)|=0X143UL;
    PBG50PROT0(4)|=0X143UL;
    PBG50PROT0(5)|=0X143UL;
    PBG50PROT0(6)|=0X143UL;
    PBG50PROT0(7)|=0X143UL;

}
