#ifndef R_SYS_H
#define R_SYS_H

/*****************************************************************************
 Includes   <System Includes> , "Project Includes"
 *****************************************************************************/
#include "Platform_Types.h"
#include "r_stbc.h"
#include "r_compiler.h"
#include "r_cg_macrodriver.h"
#include "Compiler.h"

#include "r_br.h"
#include "r_clk.h"
#include "r_delay.h"
#include "r_driver.h"
#include "r_dsadc.h"
#include "r_intc.h"
#include "r_slave_guard.h"
#include "r_pic.h"
#include "r_port.h"
#include "r_rdc.h"
#include "r_sys.h"
#include "r_tapa.h"
#include "r_tpba.h"
#include "r_tsg3.h"


/*****************************************************************************
 Macro definitions
 *****************************************************************************/
#define PEID_PE0                   0x00UL
#define PEID_PE1                   0x01UL
#define PEID_PE2                   0x02UL
#define PEID_PE3                   0x03UL
#define PEID_PE4                   0x04UL
#define PEID_PE5                   0x05UL

#define KCPROT_ENABLE          0xA5A5A501UL
#define KCPROT_DISABLE         0xA5A5A500UL

#define LEDOFF      0
#define LEDON       1
#define LEDFLIP     2


#define LED9           DioConf_DioChannel_DioChannel_P14_11_LED9
#define LED10          DioConf_DioChannel_DioChannel_P14_12_LED10
#define LED11          DioConf_DioChannel_DioChannel_P14_13_LED11


 /*****************************************************************************
 Typedef definitions
 *****************************************************************************/
#if 1
#define VMON_BASE                   0xFF983000

#define VMONKCPROT                  (*(volatile uint32  *)(VMON_BASE+0xF00))

#define VMONF                       (*(volatile uint8  *)(VMON_BASE+0x000))
#define VMONFC                      (*(volatile uint8  *)(VMON_BASE+0x004))   //VMONKCPROT
#define VMONDIAGME                  (*(volatile uint8  *)(VMON_BASE+0x008))
#define VMONDIAGMEW                 (*(volatile uint8  *)(VMON_BASE+0x00C))   //VMONKCPROT
#define VMONDMASK                   (*(volatile uint8  *)(VMON_BASE+0x010))
#define VMONDIAG                    (*(volatile uint8  *)(VMON_BASE+0x014))
#define VMONDIAGFE                  (*(volatile uint8  *)(VMON_BASE+0x018))
#define VMONOUTF                    (*(volatile uint8  *)(VMON_BASE+0x01C))
#define VMONOUTFC                   (*(volatile uint8  *)(VMON_BASE+0x020))   //VMONKCPROT
#define VMONMON                     (*(volatile uint8  *)(VMON_BASE+0x024))
#define VMONLATCHLOCK                   (*(volatile uint8  *)(VMON_BASE+0x054))
 
#define ISOVDDDE                    (*(volatile uint8  *)(VMON_BASE+0x080))   //VMONKCPROT
#define ISOVDDFCR                   (*(volatile uint8  *)(VMON_BASE+0x084))
#define AWOVDDDE                    (*(volatile uint8  *)(VMON_BASE+0x088))   //VMONKCPROT
#define AWOVDDFCR                   (*(volatile uint8  *)(VMON_BASE+0x08C))

#define VCCDE                       (*(volatile uint8  *)(VMON_BASE+0x100))   //VMONKCPROT
#define VCCFCR                      (*(volatile uint8  *)(VMON_BASE+0x104))
#define E0VCCDE                     (*(volatile uint8  *)(VMON_BASE+0x180))   //VMONKCPROT
#define E0VCCFCR                    (*(volatile uint8  *)(VMON_BASE+0x184))
#define VMONDSCR                    (*(volatile uint8  *)(VMON_BASE+0x1C0))

//TPTM
#define IUSTR0                      0x01
#define GUARD_TPTM_base             0xffc6a600
#define TPTGKCPROT                  (*(volatile uint32  *)(GUARD_TPTM_base + 0x18))

#define TPTM_base                   0xfffbb000
#define TPTM0FRUN                   (*(volatile uint32  *)(TPTM_base + 0x120))
#define TPTM0FRRUN                  (*(volatile uint32  *)(TPTM_base + 0x124))
#define TPTM0FCNT                   (*(volatile uint32  *)(TPTM_base + 0x1a0))
#define TPTM0FSTP                   (*(volatile uint8  *)(TPTM_base + 0x128))
#define TPTM0FSTR                   (*(volatile uint32  *)(TPTM_base + 0x12c))
#define TPTM0UIEN                   (*(volatile uint32  *)(TPTM_base + 0x150))
#define TPTM0UCMP00                 (*(volatile uint32  *)(TPTM_base + 0x1c4))
#define TPTM0URUN                   (*(volatile uint32  *)(TPTM_base + 0x140))
#define TPTM0USTP                   (*(volatile uint8  *)(TPTM_base + 0x148))
#define TPTM0UCNT0                  (*(volatile uint32  *)(TPTM_base + 0x1C0 + 0x100*0 + 0x20*0))
#define TPTM0UCNT1                  (*(volatile uint32  *)(TPTM_base + 0x1C0 + 0x100*0 + 0x20*1))
#define TPTM1FRUN                   (*(volatile uint32  *)(TPTM_base + 0x220))
#define TPTM1FCNT                   (*(volatile uint32  *)(TPTM_base + 0x2a0))
#define TPTM1FSTP                   (*(volatile uint8  *)(TPTM_base + 0x228))
#define TPTM0IRUN                   (*(volatile uint32  *)(TPTM_base + 0x100))
#define TPTM0ISTP                   (*(volatile uint8  *)(TPTM_base + 0x108)) // Counter Stop Register of Interval Timer for PEn
#define TPTM0ICNT0                  (*(volatile uint32  *)(TPTM_base + 0x180))
#define TPTM0ILD0                   (*(volatile uint32  *)(TPTM_base + 0x184)) // Load Channel m Register of Interval Timer for PEn
#define TPTM0ICNT1                  (*(volatile uint32  *)(TPTM_base + 0x188))
#define TPTM0ILD1                   (*(volatile uint32  *)(TPTM_base + 0x18C))
#define TPTM0IUSTRm                 (*(volatile uint32 *)(TPTM_base + 0x114))  // Underflow Status Register of Interval Timer for PEn

#define TPTM0IIEN (*(volatile uint32_t *)(TPTM_base + 0x110))  // Interrupt Enable Register of Interval Timer for PEn
#define TPTMSEL0  (*(volatile uint32_t *)(INTIF_base + 0x200)) // TPTM Interrupt FE EI Select Register
#define TPTM0IRUN (*(volatile uint32_t *)(TPTM_base + 0x100))  // Counter Start Register of Interval Timer for PEn
#define TPTM0ISTR (*(volatile uint32_t *)(TPTM_base + 0x10C))
#define TPTM0IDIV (*(volatile uint32_t *)(TPTM_base + 0x118))
#endif
// #define CKS_RCANC                   (*(volatile uint32  *)0xFF980150)
/*****************************************************************************
 Global variables
 *****************************************************************************/
extern uint32 sys_delay_cnt;

/*****************************************************************************
 Global functions
 *****************************************************************************/
extern void R_STBC_CfgMsr(uint32 Pu4Src, uint32 Pu4Cfg);

extern void R_INTC_Init(uint16 Pu2IntcX, uint16 Pu2Cfg);
extern void R_INTC_Bind(uint16 Pu2IntcX, uint32 Pu4Cfg);

extern uint8 R_BR_SetChk(uint8 Pu1Channel);
extern uint8 R_BR_GetSync(uint8 Pu1Channel);

extern void user_STBC_Init(void);
extern void user_Interrupt_Init_PE0(void);

extern void sys_Delay_ms(uint32 ms);

extern void Guard_Init(void);

uint8_t u8Check_Interrupt_Init_Request(uint32_t u32InterruptNumber);

#endif
