/*============================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                         */
/* Module       = App_ETH_Device_Sample.h                                     */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2024, 2025 Renesas Electronics Corporation. All rights reserved.       */
/*============================================================================*/
/* Purpose:                                                                   */
/* This file contains macros/function prototypes/variables required for       */
/* source application file.                                                   */
/*                                                                            */
/*============================================================================*/
/*                                                                            */
/* Unless otherwise agreed upon in writing between your company and           */
/* Renesas Electronics Corporation the following shall apply!                 */
/*                                                                            */
/* Warranty Disclaimer                                                        */
/*                                                                            */
/* There is no warranty of any kind whatsoever granted by Renesas. Any        */
/* warranty is expressly disclaimed and excluded by Renesas, either expressed */
/* or implied, including but not limited to those for non-infringement of     */
/* intellectual property, merchantability and/or fitness for the particular   */
/* purpose.                                                                   */
/*                                                                            */
/* Renesas shall not have any obligation to maintain, service or provide bug  */
/* fixes for the supplied Product(s) and/or the Application.                  */
/*                                                                            */
/* Each User is solely responsible for determining the appropriateness of     */
/* using the Product(s) and assumes all risks associated with its exercise    */
/* of rights under this Agreement, including, but not limited to the risks    */
/* and costs of program errors, compliance with applicable laws, damage to    */
/* or loss of data, programs or equipment, and unavailability or              */
/* interruption of operations.                                                */
/*                                                                            */
/* Limitation of Liability                                                    */
/*                                                                            */
/* In no event shall Renesas be liable to the User for any incidental,        */
/* consequential, indirect, or punitive damage (including but not limited     */
/* to lost profits) regardless of whether such liability is based on breach   */
/* of contract, tort, strict liability, breach of warranties, failure of      */
/* essential purpose or otherwise and even if advised of the possibility of   */
/* such damages. Renesas shall not be liable for any services or products     */
/* provided by third party vendors, developers or consultants identified or   */
/* referred to the User by Renesas in connection with the Product(s) and/or   */
/* the Application.                                                           */
/*                                                                            */
/*============================================================================*/
/* Environment:                                                               */
/*              Devices:        X2x                                           */
/*============================================================================*/

/*******************************************************************************
**                      Revision Control History                              **
*******************************************************************************/
/*
 * 2.4.1: 30/06/2025    : Remove the SW-VERSION from header of file
 * 2.3.1: 31/03/2025    : Added extern GulPortId
 *                      : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 * 2.3.0: 28/02/2025    : Add new macro MSR_ETNF
 * 2.2.0: 31/12/2024    : Update SW-VERSION for Ver22.02.00(D) U2Bx Final Release
 * 2.1.2: 31/10/2024    : Increase SW-VERSION to 2.1.2
 * 2.1.1: 31/05/2024    : Initial Version.
 */
/******************************************************************************/
#ifndef APP_ETH_DEVICE_SAMPLE_H
#define APP_ETH_DEVICE_SAMPLE_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Det.h"
#include "Eth.h"
#include "SchM_Eth.h"
#include "Eth_Ram.h"
/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/
//#define ETH_TX_SAMPLE_TOTAL                7U

/* Functional Safety - ECC and Address Parity */   /* Modified for Test */
/* ECCCNT_CFP_PE0CL0_base + 0x0 */
#define CFCECCCTL_PE0  (*((volatile unsigned long *)0xFFC48000UL))
/* MECCCAP_CFL_base + 0x0 */
#define CF_ERRINT      (*((volatile unsigned long *)0xFFC52400UL))
/* MECCCAP_CFL_base + 0x14 */
#define CF_DSTCLR      (*((volatile unsigned long *)0xFFC52414UL))
/* MECCCAP_CFL_base + 0x24 */
#define CF_DERSTR      (*((volatile unsigned long *)0xFFC52424UL))

#define ECCKCPROT      (*((volatile unsigned long *)0xFFFB2800UL))

/* --- Merged from Mcu driver --- */
#define MCU_ECMKCPROT                               (*((volatile uint32 *)0xFFD384B4ul))
#define MCU_ECM_DISABLE_WRITE_ACCESS_VALUE          0xA5A5A500UL
#define MCU_ECM_ENABLE_WRITE_ACCESS_VALUE           0xA5A5A501UL
#define MCU_ECMMECLR                                (*((volatile uint32 *)0xFFD39004UL))
#define MCU_ECMCECLR                                (*((volatile uint32 *)0xFFD3A004UL))
#define MCU_ECM_ECLR_ERRCLR_VALUE                   (uint32)0x01U
#define MCU_ECM_ECMESSTCn_ADDRESS                   0xFFD38478ul

/* Standby Controller setting */
#define MSR_ETN             (*((volatile uint32 *)0xFF981030UL))
#define MSR_ETNF            (*((volatile uint32 *)0xFF981034UL))
#define MSRKCPROT           (*((volatile uint32 *)0xFF981710UL))

/* clock setting */
#define PLLE              (*((volatile unsigned long *)0xFF980000UL)) /* PLL Enable Register */
#define PLLS              (*((volatile unsigned long *)0xFF980004UL)) /* PLL Status Register */
#define MOSCE             (*((volatile unsigned long *)0xFF988000UL)) /* MainOSC Enable Register */
#define MOSCS             (*((volatile unsigned long *)0xFF988004UL)) /* MainOSC Status Register */

#define CKS_CLEANC        (*((volatile unsigned long *)0xFF980100UL)) /* CLK_CLEAN Selector Control Register */
#define CKS_CLEANS        (*((volatile unsigned long *)0xFF980108UL)) /* CLK_CLEAN Selector Status Register */
#define CKS_SSCGC         (*((volatile unsigned long *)0xFF980110UL)) /* CLK_SSCG Selector Control Register */
#define CKS_SSCGS         (*((volatile unsigned long *)0xFF980114UL)) /* CLK_SSCG Selector Status Register */
#define CKS_SSCG1C        (*((volatile unsigned long *)0xFF980118UL)) /* CLK_SSCG1 Selector Control Register */
#define CKS_SSCG1S        (*((volatile unsigned long *)0xFF98011CUL)) /* CLK_SSCG1 Selector Status Register */

#define CKD_PLLC          (*((volatile unsigned long *)0xFF980120UL)) /* CLK_PLLO Divider Control Register */
#define CKD_SSCGC         (*((volatile unsigned long *)0xFF980130UL)) /* CLK_SSCGO Divider Control Register */
#define CKD_SSCG1C        (*((volatile unsigned long *)0xFF980138UL)) /* CLK_SSCG1O Divider Control Register */
#define CKD_PLLS          (*((volatile unsigned long *)0xFF980128UL)) /* CLK_PLLO Divider Status Register */
#define CKD_SSCGS         (*((volatile unsigned long *)0xFF980134UL)) /* CLK_SSCGO Divider Status Register */
#define CKD_SSCG1S        (*((volatile unsigned long *)0xFF98013CUL)) /* CLK_SSCG1O Divider Status Register */

#define HSOSCS        *((volatile uint32 *)0xFF988100UL) /* HSIntOSC Status Register */
#define HSOSCSTPM     *((volatile uint32 *)0xFF988104UL) /* HSIntOSC Stop Mask Register */
#define MOSCSTPM      *((volatile uint32 *)0xFF98800CUL) /* MainOSC Stop Mask Register */
#define PLLSTPM       *((volatile uint32 *)0xFF98000CUL) /* PLL Stop Mask Register */
#define CKSC_CPUC     *((volatile uint32 *)0xFF980100UL) /* CLK_CPU Selector Control Register */
#define CKSC_CPUS     *((volatile uint32 *)0xFF980108UL) /* CLK_CPU Selector Status Register */

#define CLKKCPROT1        (*((volatile unsigned long *)0xFF980700UL)) /* Clock Controller Register Key Code Protection Register 1 */

/* intrrupt setting */
/* RSW */
#define EIC708              (*((volatile uint16 *)(0xFFF80000UL + (708UL * 2UL))))
#define EIC709              (*((volatile uint16 *)(0xFFF80000UL + (709UL * 2UL))))
#define EIC710              (*((volatile uint16 *)(0xFFF80000UL + (710UL * 2UL))))
#define EIC711              (*((volatile uint16 *)(0xFFF80000UL + (711UL * 2UL))))
#define EIC712              (*((volatile uint16 *)(0xFFF80000UL + (712UL * 2UL))))
#define EIC713              (*((volatile uint16 *)(0xFFF80000UL + (713UL * 2UL))))
#define EIC714              (*((volatile uint16 *)(0xFFF80000UL + (714UL * 2UL))))
#define EIC715              (*((volatile uint16 *)(0xFFF80000UL + (715UL * 2UL))))

/* AVBT1S0 */
#define EIC964              (*((volatile uint16 *)(0xFFF80000UL + (964UL * 2UL))))
#define EIC965              (*((volatile uint16 *)(0xFFF80000UL + (965UL * 2UL))))
#define EIC966              (*((volatile uint16 *)(0xFFF80000UL + (966UL * 2UL))))
#define EIC967              (*((volatile uint16 *)(0xFFF80000UL + (967UL * 2UL))))
/* EIBD */
#ifdef RUN_OTHER_PE
#define EIBD708             *(volatile uint16 *) 0xfff82b10UL
#define EIBD709             *(volatile uint16 *) 0xfff82b14UL
#define EIBD710             *(volatile uint16 *) 0xfff82b18UL
#define EIBD711             *(volatile uint16 *) 0xfff82b1cUL
#define EIBD712             *(volatile uint16 *) 0xfff82b20UL
#define EIBD713             *(volatile uint16 *) 0xfff82b24UL
#define EIBD714             *(volatile uint16 *) 0xfff82b28UL
#define EIBD715             *(volatile uint16 *) 0xfff82b2cUL
#define EIBD716             *(volatile uint16 *) 0xfff82b30UL
#endif

/* PE Guard Register */
#ifdef RUN_OTHER_PE
#define PBGERRSLV20                                            0xFFDE1000
#define PBGERRSLV8L0                                           0xFF97A200
#define PBGKCPROT(BusGroup)                                    (*(volatile uint32*)(PBGERRSLV##BusGroup + 0x18))
#define PBG20                                                  0xFFDE0B00
#define PBG21                                                  0xffde0c00
#define PBG8L0                                                 0xff97a000
#define PBGKCPROT0(BusGroup, BusChannel)                       (*(volatile uint32*)(PBG##BusGroup + BusChannel*0x08))
#define PBGKCPROT1(BusGroup, BusChannel)                       (*(volatile uint32*)(PBG##BusGroup + 0x04 + BusChannel*0x08))
#else/* Registers base adrress */
#define GUARD_PE0CL0    0xFFC6C000
#define GUARD_PE1CL0    0xFFC6C100
#define PBGERRSLV40     0xFFC75400
#define PBG40           0xFFC75300
#define PBGERRSLV50     0xFFC7B000
#define PBG52           0xFFC7A500

#define PBGERRSLV90     0xFF0A1400
#define PBG90           0xFF0A1300
#define PBGERRSLV8L0    0xFF97A200
#define PBG8L0          0xFF97A000

/* PEGKCPROT */
#define PEGKCPROT0      (*(volatile uint32*)GUARD_PE0CL0)
#define PEGKCPROT1      (*(volatile uint32*)GUARD_PE1CL0)

/* PEGPROTm */
#define PEGPROT0(m)     (*(volatile uint32*)(GUARD_PE0CL0 + 0x40UL + m * 0x10UL))
#define PEGPROT1(m)     (*(volatile uint32*)(GUARD_PE1CL0 + 0x40UL + m * 0x10UL))

/* PEGSPIDm */
#define PEGSPID0(m)     (*(volatile uint32*)(GUARD_PE0CL0 + 0x44UL + m * 0x10UL))
#define PEGSPID1(m)     (*(volatile uint32*)(GUARD_PE1CL0 + 0x44UL + m * 0x10UL))

/* PBGKCPROTn */
#define PBGKCPROT40      (*(volatile uint32*)(PBGERRSLV40 + 0x18UL))
#define PBGKCPROT52      (*(volatile uint32*)(PBGERRSLV50 + 0x18UL))
#define PBGKCPROT90      (*(volatile uint32*)(PBGERRSLV90 + 0x18UL))
#define PBGKCPROT8L0     (*(volatile uint32*)(PBGERRSLV8L0 + 0x18UL))

/* PBGnPROT0_m */
#define PBG40PROT0(m)   (*(volatile uint32*)(PBG40 + m * 0x08UL))
#define PBG52PROT0(m)   (*(volatile uint32*)(PBG52 + m * 0x08UL))
#define PBG90PROT0(m)   (*(volatile uint32*)(PBG90 + m * 0x08UL))
#define PBG8L0PROT0(m)  (*(volatile uint32*)(PBG8L0 + m * 0x08UL))
#endif


/* port setting */
#define PTADDR    (0xFFD90000UL)
#define REG_PKCPROT     *(volatile uint32*)(PTADDR + 0x2F40UL)
#define REG_PWE         *(volatile uint32*)(PTADDR + 0x2F44UL)
#define REG_P(n)     (PTADDR +            ((uint32)(n) * 0x40UL))
#define REG_PCR(n, m) (PTADDR + 0x2000UL + ((uint32)(n) * 0x40UL) + ((uint32)(m) * 0x4UL))

#define PCR_PUCC_BIT_POSITION        25
#define PCR_PDSC_BIT_POSITION        24
#define PCR_PISA_BIT_POSITION        22
#define PCR_PIS_BIT_POSITION         20
#define PCR_PBDC_BIT_POSITION        17
#define PCR_PIBC_BIT_POSITION        16
#define PCR_PMC_BIT_POSITION          6
#define PCR_PIPC_BIT_POSITION         5
#define PCR_PM_BIT_POSITION           4
#define PCR_PFCEAE_BIT_POSITION       3
#define PCR_PFCAE_BIT_POSITION        2
#define PCR_PFCE_BIT_POSITION         1
#define PCR_PFC_BIT_POSITION          0

#define KCPROT_CLR 0xA5A5A500UL
#define KCPROT_SET 0xA5A5A501UL

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
extern void Wdg_Init(void);
extern void Clock_Init(void);
extern void Mcu_Init(void);
extern void Port_Init(void);
extern void Phy_Init(void);
extern void Eth_InitT1s(uint8 LucCtrlIdx);
extern void R_ETNF_ConfigPLCA (uint8 LucCtrlIdx);
extern void regWrite(uint8 LucCtrlIdx, uint32 regAddr45, uint16 reg_val);
extern uint16 regRead(uint8 LucCtrlIdx, uint32 regAddr45);
extern void Eth_InitSgmii(uint8 LucCtrlIdx);
extern volatile uint16 EthTxTotal[ETH_TOTAL_CTRL_CONFIG];

void regWrite_SGMII(uint8 ctrlIdx, uint16 phyAddr, uint16 devAddr, uint16 regAddr, uint16 data);
uint16 regRead_SGMII(uint8 ctrlIdx, uint16 phyAddr, uint16 devAddr, uint16 regAddr);
uint16 getRevNum(uint8 ctrlIdx, uint16 phyAddr);
uint16 getSpeed(uint8 ctrlIdx, uint16 phyAddr);
uint8 checkPCSLink(uint8 ctrlIdx, uint16 phyAddr);
uint8 checkSGMIILink(uint8 ctrlIdx, uint16 phyAddr);

#endif /* APP_ETH_DEVICE_SAMPLE_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
