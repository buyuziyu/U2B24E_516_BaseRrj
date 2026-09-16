/*============================================================================*/
/* Project      = RH850/X2x MCAL PF Development                               */
/* Module       = App_FR_Device_Sample.h                                      */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2024-2025 Renesas Electronics Corporation. All rights reserved.        */
/*============================================================================*/
/* Purpose:                                                                   */
/* Header file information for application.                                   */
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
 * 2.4.1:  30/06/2025    : Remove SW-VERSION in file header
 * 2.3.1:  31/03/2025    : Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02 Release
 *                         As per multicore support, following changes are made:
 *                         + Add HBG93, HBGERRSLV93 to support FLXA1
 * 2.3.0:  28/02/2025    : Update SW-VERSION for Ver22.01.00/Ver22.01.00.D U2Cx Release
 * 2.2.0:  31/12/2024    : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 *                         Add macro FLXA1INTNOSEL0, U2B24_E
 * 2.1.3:  31/10/2024    : Update SW-VERSION to 2.1.3
 *                         Add HBG91, HBGERRSLV91
 * 2.0.2:  26/03/2024    : Initial Version
 */
/******************************************************************************/

#ifndef APP_FR_DEVICE_SAMPLE_H
#define APP_FR_DEVICE_SAMPLE_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "App_FR_Device_Sample.h"
#include "App_FR_Common_Sample.h"

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/

typedef struct STag_Fr_Port0RegSetType
{
  uint16 usP;                           /* +0000H+n*40H Pn      */
  uint16 usReserved0;
  uint32 ulPSR;                         /* +0004H+n*40H PSRn    */
  uint16 usPNOT;                        /* +0008H+n*40H PNOTn   */
  uint16 usReserved1;
  uint16 usPPR;                         /* +000CH+n*40H PPRn    */
  uint16 usReserved2;
  uint16 usPM;                          /* +0010H+n*40H PMn     */
  uint16 usReserved3;
  uint16 usPMC;                         /* +0014H+n*40H PMCn    */
  uint16 usReserved4;
  uint16 usPFC;                         /* +0018H+n*40H PFCn    */
  uint16 usReserved5;
  uint16 usPFCE;                        /* +001CH+n*40H PFCEn   */
  uint16 usReserved6;
  uint32 ulPMSR;                        /* +0020H+n*40H PMSRn   */
  uint32 ulPMCSR;                       /* +0024H+n*40H PMCSRn  */
  uint16 usPFCAE;                       /* +0028H+n*40H PFCAEn  */
  uint16 usRserved7;
  uint16 usPFCEAE;                      /* +002CH+n*40H PFCEAEn */
  uint16 usReserved8;
  uint16 usPINV;                        /* +0030H+n*40H PINVn   */
  uint16 usReserved9;
  uint32 ulReserved10;                  /* +0034H+n*40H         */
  uint32 ulReserved11;                  /* +0038H+n*40H         */
  uint32 ulReserved12;                  /* +003CH+n*40H         */
} Fr_Port0RegSetType;

typedef struct STag_Fr_Port1RegSetType
{
  uint16 usPIBC;                        /* +4000H+n*40H PIBCn   */
  uint16 usReserved0;
  uint16 usPBDC;                        /* +4004H+n*40H PBDCn   */
  uint16 usReserved1;
  uint16 usPIPC;                        /* +4008H+n*40H PIPCn   */
  uint16 usReserved2;
  uint16 usPU;                          /* +400CH+n*40H PUn     */
  uint16 usReserved3;
  uint16 usPD;                          /* +4010H+n*40H PDn     */
  uint16 usReserved4;
  uint32 ulPODC;                        /* +4014H+n*40H PODCn   */
  uint32 ulPDSC;                        /* +4018H+n*40H PDSCn   */
  uint16 usPIS;                         /* +401CH+n*40H PISn    */
  uint16 usReserved5;
  uint32 ulReserved6;                   /* +4020H+n*40H         */
  uint16 usPISA;                        /* +4024H+n*40H PISAn   */
  uint16 usReserved7;
  uint32 ulPUCC;                        /* +4028H+n*40H PUCCn   */
  uint32 ulReserved8;                   /* +402CH+n*40H         */
  uint32 ulReserved9;                   /* +4030H+n*40H         */
  uint32 ulReserved10;                  /* +4034H+n*40H         */
  uint32 ulPODCE;                       /* +4038H+n*40H PODCEn  */
  uint32 ulReserved11;                  /* +403CH+n*40H         */
} Fr_Port1RegSetType;

/*******************************************************************************
**                          Defines                                           **
*******************************************************************************/
#define FR_59_RENESAS_LSDULENGHT        254U
/* Register addresses */
/* INTC2 Base address */
#define FR_EIC           ((volatile uint16 *)0xFFF80000UL)
/* FROS - FlexRay operation status register */
#define FROS0            *((volatile uint32 *)0x1002000CUL)
#define FROS1            *((volatile uint32 *)0x1002100CUL)
/* FRSIR - FlexRay status interrupt register */
#define FRSIR0           *((volatile uint32 *)0x10020024UL)
#define FRSIR1           *((volatile uint32 *)0x10021024UL)

/* clock setting */
#define PLLE                (*((volatile unsigned long *)0xFF980000UL)) /* PLL Enable Register */
#define PLLS                (*((volatile unsigned long *)0xFF980004UL)) /* PLL Status Register */
#define PLLSTPM             (*((volatile unsigned long *)0xFF98000CUL)) /* PLL Stop Mask Register */
#define MOSCE               (*((volatile unsigned long *)0xFF988000UL)) /* MainOSC Enable Register */
#define MOSCS               (*((volatile unsigned long *)0xFF988004UL)) /* MainOSC Status Register */
#define MOSCC               (*((volatile unsigned long *)0xFF988008UL)) /* MainOSC Control Register */
#define MOSCSTPM            (*((volatile unsigned long *)0xFF98800CUL)) /* MainOSC Stop Mask Register */
#define MOSCAS              (*((volatile unsigned long *)0xFF988014UL)) /* MainOSC ADET Status Register */
#define MOSCAGC             (*((volatile unsigned long *)0xFF988018UL)) /* MainOSC Auto Gain Control Register */
#define MOSCAGCS            (*((volatile unsigned long *)0xFF98801CUL)) /* MainOSC Auto Gain Control Status Register */
#define HSOSCS              (*((volatile unsigned long *)0xFF988100UL)) /* HSIntOSC Status Register */
#define HSOSCSTPM           (*((volatile unsigned long *)0xFF988104UL)) /* HSIntOSC Stop Mask Register */
#define HSOSCUT             (*((volatile unsigned long *)0xFF988108UL)) /* HSIntOSC User Trimming Register */
#define CKS_CLEANC          (*((volatile unsigned long *)0xFF980100UL)) /* CLK_SYS_CLEAN Selector Control Register */
#define CKS_CLEANS          (*((volatile unsigned long *)0xFF980108UL)) /* CLK_SYS_CLEAN Selector Status Register */
#define CLKD_PLLC           (*((volatile unsigned long *)0xFF980120UL)) /* CLK_PLLO Divider Control Register */
#define CLKD_PLLS           (*((volatile unsigned long *)0xFF980128UL)) /* CLK_PLLO Divider Status Register */
#define CKSC_WDTC           (*((volatile unsigned long *)0xFF980130UL)) /* CLK_WDT Selector Control Register */
#define CKSC_WDTS           (*((volatile unsigned long *)0xFF980138UL)) /* CLK_WDT Selector Status Register */
#define CKSC_RLINC          (*((volatile unsigned long *)0xFF980140UL)) /* CLK_RLIN Selector Control Register */
#define CKSC_RLINS          (*((volatile unsigned long *)0xFF980148UL)) /* CLK_RLIN Selector Status Register */
#define CKSC_RCANC          (*((volatile unsigned long *)0xFF980150UL)) /* CLK_RCANOSC Selector Control Register */
#define CKSC_RCANS          (*((volatile unsigned long *)0xFF980158UL)) /* CLK_RCANOSC Selector Status Register */
#define CKSC_ADCC           (*((volatile unsigned long *)0xFF980160UL)) /* CLK_ADC Selector Control Register */
#define CKSC_ADCS           (*((volatile unsigned long *)0xFF980168UL)) /* CLK_ADC Selector Status Register */
#define CKSC_MSPIC          (*((volatile unsigned long *)0xFF980170UL)) /* CLK_MSPI Selector Control Register */
#define CKSC_MSPIS          (*((volatile unsigned long *)0xFF980178UL)) /* CLK_MSPI Selector Status Register */
#define CKSC_AWDTC          (*((volatile unsigned long *)0xFF988200UL)) /* CLKA_WDT Selector Control Register */
#define CKSC_AWDTS          (*((volatile unsigned long *)0xFF988208UL)) /* CLKA_WDT Selector Status Register */
#define CKSC_ATAUJC         (*((volatile unsigned long *)0xFF988210UL)) /* CLKA_TAUJ Selector Control Register */
#define CKSC_ATAUJS         (*((volatile unsigned long *)0xFF988218UL)) /* CLKA_TAUJ Selector Status Register */
#define CKSC_ARTCAC         (*((volatile unsigned long *)0xFF988220UL)) /* CLKA_RTCA Selector Control Register */
#define CKSC_ARTCAS         (*((volatile unsigned long *)0xFF988228UL)) /* CLKA_RTCA Selector Status Register */
#define CKSC_AADCC          (*((volatile unsigned long *)0xFF988230UL)) /* CLKA_ADC Selector Control Register */
#define CKSC_AADCS          (*((volatile unsigned long *)0xFF988238UL)) /* CLKA_ADC Selector Status Register */
#define CLKD_AADCC          (*((volatile unsigned long *)0xFF988240UL)) /* CLKA_ADC Divider Control Register */
#define CLKD_AADCS          (*((volatile unsigned long *)0xFF988248UL)) /* CLKA_ADC Divider Status Register */
#define CKSC_FOUT0C         (*((volatile unsigned long *)0xFF988250UL)) /* FOUT0 Clock Selector Control Register */
#define CKSC_FOUT0S         (*((volatile unsigned long *)0xFF988258UL)) /* FOUT0 Clock Selector Status Register */
#define CLKD_FOUT0C         (*((volatile unsigned long *)0xFF988260UL)) /* FOUT0 Clock Divider Control Register */
#define CLKD_FOUT0S         (*((volatile unsigned long *)0xFF988268UL)) /* FOUT0 Clock Divider Status Register */
#define CKSC_FOUT1C         (*((volatile unsigned long *)0xFF988270UL)) /* FOUT1 Clock Selector Control Register */
#define CKSC_FOUT1S         (*((volatile unsigned long *)0xFF988278UL)) /* FOUT1 Clock Selector Status Register */
#define CLKD_FOUT1C         (*((volatile unsigned long *)0xFF988280UL)) /* FOUT1 Clock Divider Control Register */
#define CLKD_FOUT1S         (*((volatile unsigned long *)0xFF988288UL)) /* FOUT1 Clock Divider Status Register */
#define CLKKCPROT1          (*((volatile unsigned long *)0xFF980700UL)) /* Clock Controller Register Key Code Protection Register 1 */
#define CLKKCPROT2          (*((volatile unsigned long *)0xFF980710UL)) /* Clock Controller Register Key Code Protection Register 2 */
#define CLKKCPROT3          (*((volatile unsigned long *)0xFF980720UL)) /* Clock Controller Register Key Code Protection Register 3 */

/* Clock controller registers */
#define FR_PLLCLKS       (*(volatile uint32*)0xFF703200)
#define FR_CLKSTAB       0x00000002UL
#define FR_CKSC0C        (*(volatile uint32*)0xFF703100)
#define FR_CKSC0S        (*(volatile uint32*)0xFF703108)
#define FR_CKSC0_PLL     0x00000001UL
#define FR_CLKD0DIV      (*(volatile uint32*)0xFF703000)
#define FR_CLKD0DIV_DIV1 0x00000001UL
#define FR_CLKD0STAT     (*(volatile uint32*)0xFF703004)
#define FR_CLKD0SYNC     0x00000002UL
#define FR_CLKKCPROT0    (*(volatile uint32*)0xFF703700)

/* PE Guard Registers*/
#define PBGERRSLV0                        0xFFC6B000
#define PBGERRSLV20                       0xFFDE1000
#define PBGERRSLV10                       0xFFC63100
#define PBGERRSLV60                       0xFFC83000
#define PBGERRSLV62                       0xFFC83040
#define PBGKCPROT(BusGroup)               (*(volatile uint32*)(PBGERRSLV##BusGroup + 0x18))
#define PBG0                              0xFFC6B080
#define PBG20                             0xFFDE0B00
#define PBG21                             0xFFDE0C00
#define PBG10                             0xFFC63000
#define PBG60                             0xFFC81000
#define PBG62                             0xFFC82000
#define PBGCKPROT0(BusGroup, BusChannel)  (*(volatile uint32*)(PBG##BusGroup + BusChannel*0x08))
#define PBGCKPROT1(BusGroup, BusChannel)  (*(volatile uint32*)(PBG##BusGroup + 0x04 + BusChannel*0x08))
#define HBG93                              0xFF0D0400
#define HBG92                              0xFF0D0000
#define HBG91                              0xFF0D1000
#define HBGERRSLV93                        0xFF0D4200 
#define HBGERRSLV92                        0xFF0D4000 
#define HBGERRSLV91                        0xFF0D4800 
#define HBGPROT0(BusGroup)               (*(volatile uint32*)(HBG##BusGroup + 0x00))
#define HBGPROT1(BusGroup)               (*(volatile uint32*)(HBG##BusGroup + 0x04))
#define HBGKCPROT(BusGroup)              (*(volatile uint32*)(HBGERRSLV##BusGroup + 0x18))

#define INTC2GKCPROT        (*(volatile uint32*)(0xFFC64018))
#define INTC2GMPID(ID)      (*(volatile uint32*)(0xFFC64040 + 0x04*ID))
#define INTC2GPROT(ID)      (*(volatile uint32*)(0xFFC64100 + 0x04*ID))
#define INTC2GPROT_GR       (*(volatile uint32*)(0xFFC640F0))
#define INTC2GPROT_IMR       (*(volatile uint32*)(0xFFC640F4))
#define FLXA1INTNOSEL0      (*(volatile uint32*)(0xFF090838))

/* Protection key codes */
#define KCPROT_CLR 0xA5A5A500UL
#define KCPROT_SET 0xA5A5A501UL

/* MSR registers */
#define MSR_FLXA    (*(volatile uint32*)0xFF981010UL)
#define MSRKCPROT   (*(volatile uint32*)0xFF981710UL)

/* Enable all modules in this MSR register */
#define MSR_ACTIVE 0xFFFFFFFCUL
/* Disable all modules in this MSR register */
#define MSR_STOP   0xFFFFFFFFUL
/* Enable Timer 0 */
#define FR_TIMER0    STD_ON
/* Enable Timer 1 */
#define FR_TIMER1    STD_ON
/* Enable Timer 2 */
#define FR_TIMER2    STD_ON
/* PORT baseaddress */
#define FR_PORT0         ((volatile Fr_Port0RegSetType*)0xFFD90000UL)
#define FR_PORT1         ((volatile Fr_Port1RegSetType*)0xFFD94000UL)

/* Port Registers */
#define PKCPROT             (*((volatile uint32 *)0xFFD92F40UL))        /* Port Keycode Register */
#define PWE                 (*((volatile uint32 *)0xFFD92F44UL))        /* Port Write Enable Register */

/* This delay time waits all nodes are completely awakened and configured.
The value depends on the hardware used. */
#define APP_FR_WAIT_WAKEUP    0x00000FFFUL

#define APP_RESF            *((volatile uint32*)0xFF988500UL)

/* SW Reset */
#define APP_MCU_RESF_BIT_POS    0x8

#define APP_MCU_RST_FLAG_VALUE  0x1

/* This macro is used checking reset flag */
#define GET_BIT(REG, BIT) (((REG) >> BIT) & 0x1)

/* Function to invoke other init functions */
extern void Appl_Init(void);
/* Function for MCU Register initialization */
extern void Mcu_Init(void);
/* Function for Port Register initialization */
extern void Port_Init(void);
/* Interrupt function to initialize the interrupt registers */
extern void IH_Init(void);
/* Wait all nodes are completely awakened */
extern void WaitWakeup(void);
/* MCU Reset */
extern void Mcu_Reset(void);

/*Interrupt vector address*/
extern _INTERRUPT_ void INTFLX0TIM0(void);
extern _INTERRUPT_ void INTFLX0TIM2(void);

extern _INTERRUPT_ void INTFLX1TIM0(void);
extern _INTERRUPT_ void INTFLX1TIM2(void);

#endif /* APP_FR_DEVICE_SAMPLE_H */

/*******************************************************************************
**                     End of file                                            **
*******************************************************************************/
