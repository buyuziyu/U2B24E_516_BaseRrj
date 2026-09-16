#ifndef _USER_ETHIF_H_
#define _USER_ETHIF_H_

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "Eth.h"
#include "r_cg_macrodriver.h"

/*******************************************************************************
|    Macro Definition
|******************************************************************************/
#define ETH_WAIT_NS(t)  { volatile uint32 cnt; \
  for ( cnt = 0;cnt < ((((uint32)ETH_CPUCLK_MHZ * ((uint32)t)) / (uint32)1000) + (uint32)1);cnt++ ); }

#define DISABLE_WRITE_KEY_CODE  (0xA5A5A500UL)
#define ENABLE_WRITE_KEY_CODE   (0xA5A5A501UL)

#define REG_APCR0_8 *(volatile uint32*)(0xFFD90000 + 0x2C80 + 0x40*0 + 0x4*8)
#define REG_APM0    *(volatile uint32*)(0xFFD90000 + 0x0C90 + 0x40*0        )
#define REG_AP0     *(volatile uint32*)(0xFFD90000 + 0x0C80 + 0x40*0        )
#define ETNB1SGOPMC *(volatile uint32*)(0xFF0A4000 + 0x0C80 + 0x40*0        )

/* port setting */
#define PTADDR    (0xFFD90000UL)
#define REG_PKCPROT     *(volatile uint32*)(PTADDR + 0x2F40UL)
#define REG_PWE         *(volatile uint32*)(PTADDR + 0x2F44UL)
#define REG_P(n)     (PTADDR +            ((uint32)(n) * 0x40UL))
#define REG_PCR(n,m) (PTADDR + 0x2000UL + ((uint32)(n) * 0x40UL) + ((uint32)(m) * 0x4UL))

#define PCR_PIS_BIT_POSITION         20
#define PCR_PBDC_BIT_POSITION        17
#define PCR_PIBC_BIT_POSITION        16
#define PCR_PMC_BIT_POSITION          6
#define PCR_PIPC_BIT_POSITION         5
#define PCR_PM_BIT_POSITION           4
#define PCR_PFCAE_BIT_POSITION        2
#define PCR_PFCE_BIT_POSITION         1
#define PCR_PFC_BIT_POSITION          0

#define PCR_MASK ( \
       (1 << PCR_PMC_BIT_POSITION)   | \
       (1 << PCR_PM_BIT_POSITION)    | \
       (1 << PCR_PIBC_BIT_POSITION)  | \
       (1 << PCR_PIPC_BIT_POSITION)  | \
       (1 << PCR_PBDC_BIT_POSITION)  | \
       (1 << PCR_PFCAE_BIT_POSITION) | \
       (1 << PCR_PFCE_BIT_POSITION)  | \
       (1 << PCR_PFC_BIT_POSITION)   )

#define PCR_NML_IN_PMC              0UL
#define PCR_NML_IN_PM               1UL
#define PCR_NML_IN_PIS              0UL
#define PCR_NML_IN_PIBC             0UL
#define PCR_NML_IN_PIPC             0UL
#define PCR_NML_IN_PBDC             0UL
#define PCR_NML_IN_PFCAE            0UL
#define PCR_NML_IN_PFCE             0UL
#define PCR_NML_IN_PFC              0UL
#define PCR_NML_IN_SOFTIOCNT ( \
       (PCR_NML_IN_PMC   << PCR_PMC_BIT_POSITION)   | \
       (PCR_NML_IN_PM    << PCR_PM_BIT_POSITION)    | \
       (PCR_NML_IN_PIS   << PCR_PIS_BIT_POSITION)   | \
       (PCR_NML_IN_PIBC  << PCR_PIBC_BIT_POSITION)  | \
       (PCR_NML_IN_PIPC  << PCR_PIPC_BIT_POSITION)  | \
       (PCR_NML_IN_PBDC  << PCR_PBDC_BIT_POSITION)  | \
       (PCR_NML_IN_PFCAE << PCR_PFCAE_BIT_POSITION) | \
       (PCR_NML_IN_PFCE  << PCR_PFCE_BIT_POSITION)  | \
       (PCR_NML_IN_PFC   << PCR_PFC_BIT_POSITION)   )

#define PCR_NML_OUT_PMC              0UL
#define PCR_NML_OUT_PM               0UL
#define PCR_NML_OUT_PIS              0UL
#define PCR_NML_OUT_PIBC             0UL
#define PCR_NML_OUT_PIPC             0UL
#define PCR_NML_OUT_PBDC             0UL
#define PCR_NML_OUT_PFCAE            0UL
#define PCR_NML_OUT_PFCE             0UL
#define PCR_NML_OUT_PFC              0UL
#define PCR_NML_OUT_SOFTIOCNT ( \
       (PCR_NML_OUT_PMC   << PCR_PMC_BIT_POSITION)   | \
       (PCR_NML_OUT_PM    << PCR_PM_BIT_POSITION)    | \
       (PCR_NML_OUT_PIS   << PCR_PIS_BIT_POSITION)   | \
       (PCR_NML_OUT_PIBC  << PCR_PIBC_BIT_POSITION)  | \
       (PCR_NML_OUT_PIPC  << PCR_PIPC_BIT_POSITION)  | \
       (PCR_NML_OUT_PBDC  << PCR_PBDC_BIT_POSITION)  | \
       (PCR_NML_OUT_PFCAE << PCR_PFCAE_BIT_POSITION) | \
       (PCR_NML_OUT_PFCE  << PCR_PFCE_BIT_POSITION)  | \
       (PCR_NML_OUT_PFC   << PCR_PFC_BIT_POSITION)   )

#define PCR_AF1_IN_PMC               1UL
#define PCR_AF1_IN_PM                1UL
#define PCR_AF1_IN_PIS               0UL
#define PCR_AF1_IN_PIBC              0UL
#define PCR_AF1_IN_PIPC              0UL
#define PCR_AF1_IN_PBDC              0UL
#define PCR_AF1_IN_PFCAE             0UL
#define PCR_AF1_IN_PFCE              0UL
#define PCR_AF1_IN_PFC               0UL
#define PCR_AF1_IN_SOFTIOCNT ( \
       (PCR_AF1_IN_PMC   << PCR_PMC_BIT_POSITION)   | \
       (PCR_AF1_IN_PM    << PCR_PM_BIT_POSITION)    | \
       (PCR_AF1_IN_PIS   << PCR_PIS_BIT_POSITION)   | \
       (PCR_AF1_IN_PIBC  << PCR_PIBC_BIT_POSITION)  | \
       (PCR_AF1_IN_PIPC  << PCR_PIPC_BIT_POSITION)  | \
       (PCR_AF1_IN_PBDC  << PCR_PBDC_BIT_POSITION)  | \
       (PCR_AF1_IN_PFCAE << PCR_PFCAE_BIT_POSITION) | \
       (PCR_AF1_IN_PFCE  << PCR_PFCE_BIT_POSITION)  | \
       (PCR_AF1_IN_PFC   << PCR_PFC_BIT_POSITION)   )

#define PCR_AF1_OUT_PMC              1UL
#define PCR_AF1_OUT_PM               0UL
#define PCR_AF1_OUT_PIS              0UL
#define PCR_AF1_OUT_PIBC             0UL
#define PCR_AF1_OUT_PIPC             0UL
#define PCR_AF1_OUT_PBDC             0UL
#define PCR_AF1_OUT_PFCAE            0UL
#define PCR_AF1_OUT_PFCE             0UL
#define PCR_AF1_OUT_PFC              0UL
#define PCR_AF1_OUT_SOFTIOCNT ( \
       (PCR_AF1_OUT_PMC   << PCR_PMC_BIT_POSITION)   | \
       (PCR_AF1_OUT_PM    << PCR_PM_BIT_POSITION)    | \
       (PCR_AF1_OUT_PIS   << PCR_PIS_BIT_POSITION)   | \
       (PCR_AF1_OUT_PIBC  << PCR_PIBC_BIT_POSITION)  | \
       (PCR_AF1_OUT_PIPC  << PCR_PIPC_BIT_POSITION)  | \
       (PCR_AF1_OUT_PBDC  << PCR_PBDC_BIT_POSITION)  | \
       (PCR_AF1_OUT_PFCAE << PCR_PFCAE_BIT_POSITION) | \
       (PCR_AF1_OUT_PFCE  << PCR_PFCE_BIT_POSITION)  | \
       (PCR_AF1_OUT_PFC   << PCR_PFC_BIT_POSITION)   )

#define PCR_AF2_IN_PMC               1UL
#define PCR_AF2_IN_PM                1UL
#define PCR_AF2_IN_PIS               0UL
#define PCR_AF2_IN_PIBC              0UL
#define PCR_AF2_IN_PIPC              0UL
#define PCR_AF2_IN_PBDC              0UL
#define PCR_AF2_IN_PFCAE             0UL
#define PCR_AF2_IN_PFCE              0UL
#define PCR_AF2_IN_PFC               1UL
#define PCR_AF2_IN_SOFTIOCNT ( \
       (PCR_AF2_IN_PMC   << PCR_PMC_BIT_POSITION)   | \
       (PCR_AF2_IN_PM    << PCR_PM_BIT_POSITION)    | \
       (PCR_AF2_IN_PIS   << PCR_PIS_BIT_POSITION)   | \
       (PCR_AF2_IN_PIBC  << PCR_PIBC_BIT_POSITION)  | \
       (PCR_AF2_IN_PIPC  << PCR_PIPC_BIT_POSITION)  | \
       (PCR_AF2_IN_PBDC  << PCR_PBDC_BIT_POSITION)  | \
       (PCR_AF2_IN_PFCAE << PCR_PFCAE_BIT_POSITION) | \
       (PCR_AF2_IN_PFCE  << PCR_PFCE_BIT_POSITION)  | \
       (PCR_AF2_IN_PFC   << PCR_PFC_BIT_POSITION)   )

#define PCR_AF2_OUT_PMC              1UL
#define PCR_AF2_OUT_PM               0UL
#define PCR_AF2_OUT_PIS              0UL
#define PCR_AF2_OUT_PIBC             0UL
#define PCR_AF2_OUT_PIPC             0UL
#define PCR_AF2_OUT_PBDC             0UL
#define PCR_AF2_OUT_PFCAE            0UL
#define PCR_AF2_OUT_PFCE             0UL
#define PCR_AF2_OUT_PFC              1UL
#define PCR_AF2_OUT_SOFTIOCNT ( \
       (PCR_AF2_OUT_PMC   << PCR_PMC_BIT_POSITION)   | \
       (PCR_AF2_OUT_PM    << PCR_PM_BIT_POSITION)    | \
       (PCR_AF2_OUT_PIS   << PCR_PIS_BIT_POSITION)   | \
       (PCR_AF2_OUT_PIBC  << PCR_PIBC_BIT_POSITION)  | \
       (PCR_AF2_OUT_PIPC  << PCR_PIPC_BIT_POSITION)  | \
       (PCR_AF2_OUT_PBDC  << PCR_PBDC_BIT_POSITION)  | \
       (PCR_AF2_OUT_PFCAE << PCR_PFCAE_BIT_POSITION) | \
       (PCR_AF2_OUT_PFCE  << PCR_PFCE_BIT_POSITION)  | \
       (PCR_AF2_OUT_PFC   << PCR_PFC_BIT_POSITION)   )

#define PCR_AF2_PIPC_PMC             1UL
#define PCR_AF2_PIPC_PM              0UL
#define PCR_AF2_PIPC_PIS             0UL
#define PCR_AF2_PIPC_PIBC            0UL
#define PCR_AF2_PIPC_PIPC            1UL
#define PCR_AF2_PIPC_PBDC            0UL
#define PCR_AF2_PIPC_PFCAE           0UL
#define PCR_AF2_PIPC_PFCE            0UL
#define PCR_AF2_PIPC_PFC             1UL
#define PCR_AF2_PIPC_SOFTIOCNT ( \
       (PCR_AF2_PIPC_PMC   << PCR_PMC_BIT_POSITION)   | \
       (PCR_AF2_PIPC_PM    << PCR_PM_BIT_POSITION)    | \
       (PCR_AF2_PIPC_PIS   << PCR_PIS_BIT_POSITION)   | \
       (PCR_AF2_PIPC_PIBC  << PCR_PIBC_BIT_POSITION)  | \
       (PCR_AF2_PIPC_PIPC  << PCR_PIPC_BIT_POSITION)  | \
       (PCR_AF2_PIPC_PBDC  << PCR_PBDC_BIT_POSITION)  | \
       (PCR_AF2_PIPC_PFCAE << PCR_PFCAE_BIT_POSITION) | \
       (PCR_AF2_PIPC_PFCE  << PCR_PFCE_BIT_POSITION)  | \
       (PCR_AF2_PIPC_PFC   << PCR_PFC_BIT_POSITION)   )

#define PCR_AF3_IN_PMC               1UL
#define PCR_AF3_IN_PM                1UL
#define PCR_AF3_IN_PIS               0UL
#define PCR_AF3_IN_PIBC              0UL
#define PCR_AF3_IN_PIPC              0UL
#define PCR_AF3_IN_PBDC              0UL
#define PCR_AF3_IN_PFCAE             0UL
#define PCR_AF3_IN_PFCE              1UL
#define PCR_AF3_IN_PFC               0UL
#define PCR_AF3_IN_SOFTIOCNT ( \
       (PCR_AF3_IN_PMC   << PCR_PMC_BIT_POSITION)   | \
       (PCR_AF3_IN_PM    << PCR_PM_BIT_POSITION)    | \
       (PCR_AF3_IN_PIS   << PCR_PIS_BIT_POSITION)   | \
       (PCR_AF3_IN_PIBC  << PCR_PIBC_BIT_POSITION)  | \
       (PCR_AF3_IN_PIPC  << PCR_PIPC_BIT_POSITION)  | \
       (PCR_AF3_IN_PBDC  << PCR_PBDC_BIT_POSITION)  | \
       (PCR_AF3_IN_PFCAE << PCR_PFCAE_BIT_POSITION) | \
       (PCR_AF3_IN_PFCE  << PCR_PFCE_BIT_POSITION)  | \
       (PCR_AF3_IN_PFC   << PCR_PFC_BIT_POSITION)   )

#define PCR_AF3_OUT_PMC              1UL
#define PCR_AF3_OUT_PM               0UL
#define PCR_AF3_OUT_PIS              0UL
#define PCR_AF3_OUT_PIBC             0UL
#define PCR_AF3_OUT_PIPC             0UL
#define PCR_AF3_OUT_PBDC             0UL
#define PCR_AF3_OUT_PFCAE            0UL
#define PCR_AF3_OUT_PFCE             1UL
#define PCR_AF3_OUT_PFC              0UL
#define PCR_AF3_OUT_SOFTIOCNT ( \
       (PCR_AF3_OUT_PMC   << PCR_PMC_BIT_POSITION)   | \
       (PCR_AF3_OUT_PM    << PCR_PM_BIT_POSITION)    | \
       (PCR_AF3_OUT_PIS   << PCR_PIS_BIT_POSITION)   | \
       (PCR_AF3_OUT_PIBC  << PCR_PIBC_BIT_POSITION)  | \
       (PCR_AF3_OUT_PIPC  << PCR_PIPC_BIT_POSITION)  | \
       (PCR_AF3_OUT_PBDC  << PCR_PBDC_BIT_POSITION)  | \
       (PCR_AF3_OUT_PFCAE << PCR_PFCAE_BIT_POSITION) | \
       (PCR_AF3_OUT_PFCE  << PCR_PFCE_BIT_POSITION)  | \
       (PCR_AF3_OUT_PFC   << PCR_PFC_BIT_POSITION)   )

/* Modified for Test */
#define PCR_AF3_PIPC_PMC             1UL
#define PCR_AF3_PIPC_PM              0UL
#define PCR_AF3_PIPC_PIS             0UL
#define PCR_AF3_PIPC_PIBC            0UL
#define PCR_AF3_PIPC_PIPC            1UL
#define PCR_AF3_PIPC_PBDC            0UL
#define PCR_AF3_PIPC_PFCAE           0UL
#define PCR_AF3_PIPC_PFCE            1UL
#define PCR_AF3_PIPC_PFC             0UL
#define PCR_AF3_PIPC_SOFTIOCNT ( \
       (PCR_AF3_PIPC_PMC   << PCR_PMC_BIT_POSITION)   | \
       (PCR_AF3_PIPC_PM    << PCR_PM_BIT_POSITION)    | \
       (PCR_AF3_PIPC_PIS   << PCR_PIS_BIT_POSITION)   | \
       (PCR_AF3_PIPC_PIBC  << PCR_PIBC_BIT_POSITION)  | \
       (PCR_AF3_PIPC_PIPC  << PCR_PIPC_BIT_POSITION)  | \
       (PCR_AF3_PIPC_PBDC  << PCR_PBDC_BIT_POSITION)  | \
       (PCR_AF3_PIPC_PFCAE << PCR_PFCAE_BIT_POSITION) | \
       (PCR_AF3_PIPC_PFCE  << PCR_PFCE_BIT_POSITION)  | \
       (PCR_AF3_PIPC_PFC   << PCR_PFC_BIT_POSITION)   )

#define PCR_AF4_IN_PMC               1UL
#define PCR_AF4_IN_PM                1UL
#define PCR_AF4_IN_PIS               0UL
#define PCR_AF4_IN_PIBC              0UL
#define PCR_AF4_IN_PIPC              0UL
#define PCR_AF4_IN_PBDC              0UL
#define PCR_AF4_IN_PFCAE             0UL
#define PCR_AF4_IN_PFCE              1UL
#define PCR_AF4_IN_PFC               1UL
#define PCR_AF4_IN_SOFTIOCNT ( \
       (PCR_AF4_IN_PMC   << PCR_PMC_BIT_POSITION)   | \
       (PCR_AF4_IN_PM    << PCR_PM_BIT_POSITION)    | \
       (PCR_AF4_IN_PIS   << PCR_PIS_BIT_POSITION)   | \
       (PCR_AF4_IN_PIBC  << PCR_PIBC_BIT_POSITION)  | \
       (PCR_AF4_IN_PIPC  << PCR_PIPC_BIT_POSITION)  | \
       (PCR_AF4_IN_PBDC  << PCR_PBDC_BIT_POSITION)  | \
       (PCR_AF4_IN_PFCAE << PCR_PFCAE_BIT_POSITION) | \
       (PCR_AF4_IN_PFCE  << PCR_PFCE_BIT_POSITION)  | \
       (PCR_AF4_IN_PFC   << PCR_PFC_BIT_POSITION)   )

#define PCR_AF4_OUT_PMC              1UL
#define PCR_AF4_OUT_PM               0UL
#define PCR_AF4_OUT_PIS              0UL
#define PCR_AF4_OUT_PIBC             0UL
#define PCR_AF4_OUT_PIPC             0UL
#define PCR_AF4_OUT_PBDC             0UL
#define PCR_AF4_OUT_PFCAE            0UL
#define PCR_AF4_OUT_PFCE             1UL
#define PCR_AF4_OUT_PFC              1UL
#define PCR_AF4_OUT_SOFTIOCNT ( \
       (PCR_AF4_OUT_PMC   << PCR_PMC_BIT_POSITION)   | \
       (PCR_AF4_OUT_PM    << PCR_PM_BIT_POSITION)    | \
       (PCR_AF4_OUT_PIS   << PCR_PIS_BIT_POSITION)   | \
       (PCR_AF4_OUT_PIBC  << PCR_PIBC_BIT_POSITION)  | \
       (PCR_AF4_OUT_PIPC  << PCR_PIPC_BIT_POSITION)  | \
       (PCR_AF4_OUT_PBDC  << PCR_PBDC_BIT_POSITION)  | \
       (PCR_AF4_OUT_PFCAE << PCR_PFCAE_BIT_POSITION) | \
       (PCR_AF4_OUT_PFCE  << PCR_PFCE_BIT_POSITION)  | \
       (PCR_AF4_OUT_PFC   << PCR_PFC_BIT_POSITION)   )

#define PCR_AF5_IN_PMC               1UL
#define PCR_AF5_IN_PM                1UL
#define PCR_AF5_IN_PIS               0UL
#define PCR_AF5_IN_PIBC              0UL
#define PCR_AF5_IN_PIPC              0UL
#define PCR_AF5_IN_PBDC              0UL
#define PCR_AF5_IN_PFCAE             1UL
#define PCR_AF5_IN_PFCE              0UL
#define PCR_AF5_IN_PFC               0UL
#define PCR_AF5_IN_SOFTIOCNT ( \
       (PCR_AF5_IN_PMC   << PCR_PMC_BIT_POSITION)   | \
       (PCR_AF5_IN_PM    << PCR_PM_BIT_POSITION)    | \
       (PCR_AF5_IN_PIS   << PCR_PIS_BIT_POSITION)   | \
       (PCR_AF5_IN_PIBC  << PCR_PIBC_BIT_POSITION)  | \
       (PCR_AF5_IN_PIPC  << PCR_PIPC_BIT_POSITION)  | \
       (PCR_AF5_IN_PBDC  << PCR_PBDC_BIT_POSITION)  | \
       (PCR_AF5_IN_PFCAE << PCR_PFCAE_BIT_POSITION) | \
       (PCR_AF5_IN_PFCE  << PCR_PFCE_BIT_POSITION)  | \
       (PCR_AF5_IN_PFC   << PCR_PFC_BIT_POSITION)   )

#define PCR_AF5_OUT_PMC              1UL
#define PCR_AF5_OUT_PM               0UL
#define PCR_AF5_OUT_PIS              0UL
#define PCR_AF5_OUT_PIBC             0UL
#define PCR_AF5_OUT_PIPC             0UL
#define PCR_AF5_OUT_PBDC             0UL
#define PCR_AF5_OUT_PFCAE            1UL
#define PCR_AF5_OUT_PFCE             0UL
#define PCR_AF5_OUT_PFC              0UL
#define PCR_AF5_OUT_SOFTIOCNT ( \
       (PCR_AF5_OUT_PMC   << PCR_PMC_BIT_POSITION)   | \
       (PCR_AF5_OUT_PM    << PCR_PM_BIT_POSITION)    | \
       (PCR_AF5_OUT_PIS   << PCR_PIS_BIT_POSITION)   | \
       (PCR_AF5_OUT_PIBC  << PCR_PIBC_BIT_POSITION)  | \
       (PCR_AF5_OUT_PIPC  << PCR_PIPC_BIT_POSITION)  | \
       (PCR_AF5_OUT_PBDC  << PCR_PBDC_BIT_POSITION)  | \
       (PCR_AF5_OUT_PFCAE << PCR_PFCAE_BIT_POSITION) | \
       (PCR_AF5_OUT_PFCE  << PCR_PFCE_BIT_POSITION)  | \
       (PCR_AF5_OUT_PFC   << PCR_PFC_BIT_POSITION)   )

#define PCR_AF6_IN_PMC               1UL
#define PCR_AF6_IN_PM                1UL
#define PCR_AF6_IN_PIS               0UL
#define PCR_AF6_IN_PIBC              0UL
#define PCR_AF6_IN_PIPC              0UL
#define PCR_AF6_IN_PBDC              0UL
#define PCR_AF6_IN_PFCAE             1UL
#define PCR_AF6_IN_PFCE              0UL
#define PCR_AF6_IN_PFC               1UL
#define PCR_AF6_IN_SOFTIOCNT ( \
       (PCR_AF6_IN_PMC   << PCR_PMC_BIT_POSITION)   | \
       (PCR_AF6_IN_PM    << PCR_PM_BIT_POSITION)    | \
       (PCR_AF6_IN_PIS   << PCR_PIS_BIT_POSITION)   | \
       (PCR_AF6_IN_PIBC  << PCR_PIBC_BIT_POSITION)  | \
       (PCR_AF6_IN_PIPC  << PCR_PIPC_BIT_POSITION)  | \
       (PCR_AF6_IN_PBDC  << PCR_PBDC_BIT_POSITION)  | \
       (PCR_AF6_IN_PFCAE << PCR_PFCAE_BIT_POSITION) | \
       (PCR_AF6_IN_PFCE  << PCR_PFCE_BIT_POSITION)  | \
       (PCR_AF6_IN_PFC   << PCR_PFC_BIT_POSITION)   )

#define PCR_AF6_OUT_PMC              1UL
#define PCR_AF6_OUT_PM               0UL
#define PCR_AF6_OUT_PIS              0UL
#define PCR_AF6_OUT_PIBC             0UL
#define PCR_AF6_OUT_PIPC             0UL
#define PCR_AF6_OUT_PBDC             0UL
#define PCR_AF6_OUT_PFCAE            1UL
#define PCR_AF6_OUT_PFCE             0UL
#define PCR_AF6_OUT_PFC              1UL
#define PCR_AF6_OUT_SOFTIOCNT ( \
       (PCR_AF6_OUT_PMC   << PCR_PMC_BIT_POSITION)   | \
       (PCR_AF6_OUT_PM    << PCR_PM_BIT_POSITION)    | \
       (PCR_AF6_OUT_PIS   << PCR_PIS_BIT_POSITION)   | \
       (PCR_AF6_OUT_PIBC  << PCR_PIBC_BIT_POSITION)  | \
       (PCR_AF6_OUT_PIPC  << PCR_PIPC_BIT_POSITION)  | \
       (PCR_AF6_OUT_PBDC  << PCR_PBDC_BIT_POSITION)  | \
       (PCR_AF6_OUT_PFCAE << PCR_PFCAE_BIT_POSITION) | \
       (PCR_AF6_OUT_PFCE  << PCR_PFCE_BIT_POSITION)  | \
       (PCR_AF6_OUT_PFC   << PCR_PFC_BIT_POSITION)   )

#define PCR_AF7_IN_PMC               1UL
#define PCR_AF7_IN_PM                1UL
#define PCR_AF7_IN_PIS               0UL
#define PCR_AF7_IN_PIBC              0UL
#define PCR_AF7_IN_PIPC              0UL
#define PCR_AF7_IN_PBDC              0UL
#define PCR_AF7_IN_PFCAE             1UL
#define PCR_AF7_IN_PFCE              1UL
#define PCR_AF7_IN_PFC               0UL
#define PCR_AF7_IN_SOFTIOCNT ( \
       (PCR_AF7_IN_PMC   << PCR_PMC_BIT_POSITION)   | \
       (PCR_AF7_IN_PM    << PCR_PM_BIT_POSITION)    | \
       (PCR_AF7_IN_PIS   << PCR_PIS_BIT_POSITION)   | \
       (PCR_AF7_IN_PIBC  << PCR_PIBC_BIT_POSITION)  | \
       (PCR_AF7_IN_PIPC  << PCR_PIPC_BIT_POSITION)  | \
       (PCR_AF7_IN_PBDC  << PCR_PBDC_BIT_POSITION)  | \
       (PCR_AF7_IN_PFCAE << PCR_PFCAE_BIT_POSITION) | \
       (PCR_AF7_IN_PFCE  << PCR_PFCE_BIT_POSITION)  | \
       (PCR_AF7_IN_PFC   << PCR_PFC_BIT_POSITION)   )

#define PCR_AF7_OUT_PMC              1UL
#define PCR_AF7_OUT_PM               0UL
#define PCR_AF7_OUT_PIS              0UL
#define PCR_AF7_OUT_PIBC             0UL
#define PCR_AF7_OUT_PIPC             0UL
#define PCR_AF7_OUT_PBDC             0UL
#define PCR_AF7_OUT_PFCAE            1UL
#define PCR_AF7_OUT_PFCE             1UL
#define PCR_AF7_OUT_PFC              0UL
#define PCR_AF7_OUT_SOFTIOCNT ( \
       (PCR_AF7_OUT_PMC   << PCR_PMC_BIT_POSITION)   | \
       (PCR_AF7_OUT_PM    << PCR_PM_BIT_POSITION)    | \
       (PCR_AF7_OUT_PIS   << PCR_PIS_BIT_POSITION)   | \
       (PCR_AF7_OUT_PIBC  << PCR_PIBC_BIT_POSITION)  | \
       (PCR_AF7_OUT_PIPC  << PCR_PIPC_BIT_POSITION)  | \
       (PCR_AF7_OUT_PBDC  << PCR_PBDC_BIT_POSITION)  | \
       (PCR_AF7_OUT_PFCAE << PCR_PFCAE_BIT_POSITION) | \
       (PCR_AF7_OUT_PFCE  << PCR_PFCE_BIT_POSITION)  | \
       (PCR_AF7_OUT_PFC   << PCR_PFC_BIT_POSITION)   )

#define PCR_AF8_IN_PMC               1UL
#define PCR_AF8_IN_PM                1UL
#define PCR_AF8_IN_PIS               0UL
#define PCR_AF8_IN_PIBC              0UL
#define PCR_AF8_IN_PIPC              0UL
#define PCR_AF8_IN_PBDC              0UL
#define PCR_AF8_IN_PFCAE             1UL
#define PCR_AF8_IN_PFCE              1UL
#define PCR_AF8_IN_PFC               1UL
#define PCR_AF8_IN_SOFTIOCNT ( \
       (PCR_AF8_IN_PMC   << PCR_PMC_BIT_POSITION)   | \
       (PCR_AF8_IN_PM    << PCR_PM_BIT_POSITION)    | \
       (PCR_AF8_IN_PIS   << PCR_PIS_BIT_POSITION)   | \
       (PCR_AF8_IN_PIBC  << PCR_PIBC_BIT_POSITION)  | \
       (PCR_AF8_IN_PIPC  << PCR_PIPC_BIT_POSITION)  | \
       (PCR_AF8_IN_PBDC  << PCR_PBDC_BIT_POSITION)  | \
       (PCR_AF8_IN_PFCAE << PCR_PFCAE_BIT_POSITION) | \
       (PCR_AF8_IN_PFCE  << PCR_PFCE_BIT_POSITION)  | \
       (PCR_AF8_IN_PFC   << PCR_PFC_BIT_POSITION)   )

#define PCR_AF8_OUT_PMC              1UL
#define PCR_AF8_OUT_PM               0UL
#define PCR_AF8_OUT_PIS              0UL
#define PCR_AF8_OUT_PIBC             0UL
#define PCR_AF8_OUT_PIPC             0UL
#define PCR_AF8_OUT_PBDC             0UL
#define PCR_AF8_OUT_PFCAE            1UL
#define PCR_AF8_OUT_PFCE             1UL
#define PCR_AF8_OUT_PFC              1UL
#define PCR_AF8_OUT_SOFTIOCNT ( \
       (PCR_AF8_OUT_PMC   << PCR_PMC_BIT_POSITION)   | \
       (PCR_AF8_OUT_PM    << PCR_PM_BIT_POSITION)    | \
       (PCR_AF8_OUT_PIS   << PCR_PIS_BIT_POSITION)   | \
       (PCR_AF8_OUT_PIBC  << PCR_PIBC_BIT_POSITION)  | \
       (PCR_AF8_OUT_PIPC  << PCR_PIPC_BIT_POSITION)  | \
       (PCR_AF8_OUT_PBDC  << PCR_PBDC_BIT_POSITION)  | \
       (PCR_AF8_OUT_PFCAE << PCR_PFCAE_BIT_POSITION) | \
       (PCR_AF8_OUT_PFCE  << PCR_PFCE_BIT_POSITION)  | \
       (PCR_AF8_OUT_PFC   << PCR_PFC_BIT_POSITION)   )


#define KCPROT_CLR 0xA5A5A500UL
#define KCPROT_SET 0xA5A5A501UL

/*******************************************************************************
|    typedef
|******************************************************************************/

/*******************************************************************************
|    variables Declaration  
|******************************************************************************/

/*******************************************************************************
|    Global Function Prototypes
|******************************************************************************/
void EthIf_Init(void);
void EthIf_Sample_test(void);
void Eth_InitSgmii(void);

void ETH_Port_Init(void);

#endif
