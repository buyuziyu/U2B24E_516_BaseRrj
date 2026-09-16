/*============================================================================*/
/* Project      = RH850/X2x MCAL PF Development                               */
/* Module       = App_SPI_Device_Sample.h                                     */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* Copyright(c) 2025 Renesas Electronics Corporation.                         */
/*============================================================================*/
/* Purpose:                                                                   */
/* This file contains macros/function prototypes/variables required for       */
/* source application file.                                                   */
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
 * 2.5.1:  30/06/2025  : Remove SW-VERSION in file header
 * 2.5.0:  30/06/2025  : Update SW-VERSION for RH850/Ver21.01.00(D) U2Ax release
 * 2.4.0:  31/05/2025  : Update SW-VERSION for RH850/Ver21.01.01 U2Cx release
 * 2.3.2:  30/04/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 Release
 * 2.3.1:  31/03/2025  : Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02 Release
 *                       Add definition of trigger relay porrt_pin
 * 2.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00(D) U2Bx Final Release
 * 2.1.3:  31/10/2024  : Update SW-VERSION up to 2.1.3
 * 2.1.2:  30/09/2024  : Update SW-VERSION up to 2.1.2
 * 2.0.3:  14/04/2024  : Update register for TAUD2 to support for
 *                       post build variant
 *         19/03/2024  : Initial Version
 */
/******************************************************************************/
#ifndef APP_SPI_DEVICE_SAMPLE_H
#define APP_SPI_DEVICE_SAMPLE_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Std_Types.h"

/*******************************************************************************
**                         Local Definitions                                  **
*******************************************************************************/
#define DISABLE_WRITE_KEY_CODE  (0xA5A5A500UL)
#define ENABLE_WRITE_KEY_CODE   (0xA5A5A501UL)

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/

typedef struct STag_Spi_Port0RegSetType
{
   uint16 usP;          /* 0000H + 40H*n        Port register */
   uint16 usReserved0;
   uint32 ulPSR;        /* 0004H + 40H*n        Port Set Reset register */
   uint16 usPNOT;       /* 0008H + 40H*n        Port NOT register */
   uint16 usReserved1;
   uint16 usPPR;        /* 000CH + 40H*n        Port Pin Read register */
   uint16 usReserved2;
   uint16 usPM;         /* 0010H + 40H*n        Port Mode register */
   uint16 usReserved3;
   uint16 usPMC;        /* 0014H + 40H*n        Port Mode Control register */
   uint16 usReserved4;
   uint16 usPFC;        /* 0018H + 40H*n        Port Function Control register */
   uint16 usReserved5;
   uint16 usPFCE;       /* 001CH + 40H*n        Port Function Control Expansion register */
   uint16 usReserved6;
   uint32 ulPMSR;       /* 0020H + 40H*n        Port Mode Set Reset register */
   uint32 ulPMCSR;      /* 0024H + 40H*n        Port Mode Control Set Reset register */
   uint16 usPFCAE;      /* 0028H + 40H*n        Port Function Control Additional Expansion register */
   uint32 ulReserved7;
   uint16 usReserved8;
   uint16 usPINV;       /* 0030H + 40H*n        Port output value Inversion register */
   uint32 aaReserved9[3];
} Spi_Port0RegSetType;

typedef struct STag_Spi_Port1RegSetType
{
   uint16 usPIBC;       /* 4000H + 40H*n        Port Input Buffer Control register */
   uint16 usReserved0;
   uint16 usPBDC;       /* 4004H + 40H*n        Port Bi-Direction Control register */
   uint16 usReserved1;
   uint16 usPIPC;       /* 4008H + 40H*n        Port IP Control register */
   uint16 usReserved2;
   uint16 usPU;         /* 400CH + 40H*n        Pull-Up option register */
   uint16 usReserved3;
   uint16 usPD;         /* 4010H + 40H*n        Pull-Down option register */
   uint16 usReserved4;
   uint32 ulPODC;       /* 4014H + 40H*n        Port Open Drain Control register */
   uint32 ulPDSC;       /* 4018H + 40H*n        Port Drive Strength Control register */
   uint16 usPIS;        /* 401CH + 40H*n        Port Input buffer Selection register */
   uint16 usReserved5;
   uint32 ulReserved6;
   uint16 usPISA;       /* 4024H + 40H*n        Port Input buffer Selection Advanced register */
   uint16 usReserved7;
   uint32 ulPUCC;       /* 4028H + 40H*n        Port Universal Characteristic Control register */
   uint32 ulReserved8;
   uint32 ulReserved9;
   uint32 ulReserved10;
   uint32 ulPODCE;      /* 4038H + 40H*n        Port Open Drain Control Expansion register */
   uint32 ulReserved11;
} Spi_Port1RegSetType;

typedef struct STag_Spi_DMAGlobalRegSetType
{
  uint32 aaReserved0[4];
  uint32 ulESTA;                        /* +0010H ESTA          */
  uint32 aaReserved1[3];
  uint32 ulSTA;                         /* +0020H STA           */
  uint32 aaReserved2[7];
  uint32 ulCHPRI;                       /* +0040H CHPRI         */
  uint32 aaReserved3[7];
  uint16 usOR;                          /* +0060H OR            */
  uint16 aaReserved4[15];
  uint32 ulCHRST;                       /* +0080H CHRST         */
  uint32 aaReserved5[31];
  uint32 aaCM[16];                      /* +0100H+n*4H CM_n     */
} Spi_DMAGlobalRegSetType;

typedef struct STag_Spi_ATU5GChRegSetType
{
  uint8  ucTCRG;                        /* +0010H+n*10H TCRGn   */
  uint8  ucReseved0;
  uint8  ucTSRG;                        /* +0012H+n*10H TSRGn   */
  uint8  ucTSCRG;                       /* +0013H+n*10H TSCRGn  */
  uint32 ulTCNTG;                       /* +0014H+n*10H TCNTGn  */
  uint32 ulOCRG;                        /* +0018H+n*10H OCRGn   */
  uint32 ulRLDG;                        /* +001CH+n*10H RLDGn   */
} Spi_ATU5GChRegSetType;

typedef struct STag_Spi_ATU5GRegSetType
{
  uint16 usTSTRG;                       /* +0000H TSTRG         */
  uint16 usReserved0;
  uint16 usTIERG;                       /* +0004H TIERG         */
  uint16 usReserved1;
  uint16 usRLDCRG;                      /* +0008H RLDCRG        */
  uint16 usReserved2;
  uint32 ulReserved3;
  Spi_ATU5GChRegSetType aaCh[10];
} Spi_ATU5GRegSetType;

/* Clock controller registers */
#define PLLE              (*((volatile unsigned long *)0xFF980000UL)) /* PLL Enable Register */
#define PLLS              (*((volatile unsigned long *)0xFF980004UL)) /* PLL Status Register */
#define PLLSTPM           (*((volatile unsigned long *)0xFF98000CUL)) /* PLL Stop Mask Register */
#define MOSCE             (*((volatile unsigned long *)0xFF988000UL)) /* MainOSC Enable Register */
#define MOSCS             (*((volatile unsigned long *)0xFF988004UL)) /* MainOSC Status Register */
#define MOSCSTPM          (*((volatile unsigned long *)0xFF98800CUL)) /* MainOSC Stop Mask Register */
#define MOSCM             (*((volatile unsigned long *)0xFF988010UL)) /* MainOSC Mode Control Register */
#define HSOSCS            (*((volatile unsigned long *)0xFF988100UL)) /* HSIntOSC Status Register */
#define HSOSCSTPM         (*((volatile unsigned long *)0xFF988104UL)) /* HSIntOSC Stop Mask Register */
#define CKSC_CPUC         (*((volatile unsigned long *)0xFF980100UL)) /* CLK_CPU Selector Control Register */
#define CKSC_CPUS         (*((volatile unsigned long *)0xFF980108UL)) /* CLK_CPU Selector Status Register */
#define CLKKCPROT1        (*((volatile unsigned long *)0xFF980700UL)) /* Clock Controller Register Key Code Protection Register 1 */
#define CLKD_PLLC         (*((volatile unsigned long *)0xFF980120UL)) /* CLK_PLLO Divider Control Register */

/* Module standby registers */
#define SPI_MSR_MSPI      (*(volatile uint32*)0xFF981050UL)
#define SPI_MSR_TAUD      (*(volatile uint32*)0xFF981130UL)
#define SPI_MSRKCPROT     (*(volatile uint32*)0xFF981710UL)

/* Protection key codes */
#define SPI_KCPROT_CLR 0xA5A5A500UL
#define SPI_KCPROT_SET 0xA5A5A501UL

/* Enable all modules in this MSR register */
#define SPI_MSR_ACTIVE 0x00000000UL

/* Disable all modules in this MSR register */
#define SPI_MSR_STOP   0xFFFFFFFFUL

/* INTC1 base address */
#define SPI_EIC1          ((volatile uint16*)0xFFFC0000UL)
#define SPI_EIC1_PE0      ((volatile uint16*)0xFFFC4000UL)
#define SPI_EIC1_PE1      ((volatile uint16*)0xFFFC8000UL)
/* INTC2 base address */
#define SPI_EIC2          ((volatile uint16*)0xFFF80000UL)
#define SPI_EIBD2         ((volatile uint32*)0xFFF82000UL)

/* Number of EIC registers */
#define SPI_EIC_NUMBER    512UL

#define SPI_PORT0         ((volatile Spi_Port0RegSetType*)0xFFD90000UL)
#define SPI_PORT1         ((volatile Spi_Port1RegSetType*)0xFFD94000UL)

#define SPI_DMA0          ((volatile Spi_DMAGlobalRegSetType*)0xFFF90000UL)
#define SPI_DMA1          ((volatile Spi_DMAGlobalRegSetType*)0xFFF98000UL)
#define SPI_ATU5G         ((volatile Spi_ATU5GRegSetType*)0xFFE65C00UL)
#define SPI_DMA0OR        (*(volatile uint16*)0xFFF90060UL)
#define SPI_DMA1OR        (*(volatile uint16*)0xFFF98060UL)
#define SPI_ATUENR        (*(volatile uint8*)0xFFE60000UL)
#define SPI_PSCR0         (*(volatile uint16*)0xFFE60080UL)
#define SPI_TSTRG         (*(volatile uint16*)0xFFE65C00UL)
#define SPI_TIERG         (*(volatile uint16*)0xFFE65C04UL)
#define SPI_RLDCRG        (*(volatile uint16*)0xFFE65C08UL)
#define SPI_TCRG0         (*(volatile uint8*)0xFFE65C10UL)
#define SPI_TCNTG0        (*(volatile uint32*)0xFFE65C14UL)
#define SPI_OCRG0         (*(volatile uint32*)0xFFE65C18UL)

/* PCLK(LSB): 40MHz */
#define SPI_PCLK_HZ         40000000UL

/* Interval of Spi_MainFunction_Handling: 1ms */
#define SPI_POLLING_INTERVAL_MS 1UL

/* Interrupt Vector Setting: Table mode, priority 7 */
#define SPI_EIC_PRI       (uint16)0x000F
#define SPI_EITB          (uint16)0x0040
#define SPI_EIMK          (uint16)0x0080
#define SPI_EIBD_PE1      0x00000001UL

/* TAUD0 */
#define SPI_TAUD0_TOP_ADDR 0xFFBF4000UL
#define SPI_TAUD0TPS        (*((volatile uint16 *)(SPI_TAUD0_TOP_ADDR + 0x240U)))
#define SPI_TAUD0CDR0       (*((volatile uint16 *)(SPI_TAUD0_TOP_ADDR + 0x000U)))
#define SPI_TAUD0CMOR0      (*((volatile uint16 *)(SPI_TAUD0_TOP_ADDR + 0x200U)))
#define SPI_TAUD0TS         (*((volatile uint16 *)(SPI_TAUD0_TOP_ADDR + 0x1C4U)))
#define SPI_TAUD0TT         (*((volatile uint16 *)(SPI_TAUD0_TOP_ADDR + 0x1C8U)))

#define SPI_INTC1_TOP_ADDR  0xFFFC4000UL
#define SPI_EIC_INTTAUD0I0  (*((volatile uint16 *)(SPI_INTC1_TOP_ADDR + (0x2UL * 10U))))

/* TAUD2 */
#define SPI_TAUD2_TOP_ADDR  0xFFBF6000UL
#define SPI_TAUD2TPS        (*((volatile uint16 *)(SPI_TAUD2_TOP_ADDR + 0x240U)))
#define SPI_TAUD2CDR0       (*((volatile uint16 *)(SPI_TAUD2_TOP_ADDR + 0x000U)))
#define SPI_TAUD2CMOR0      (*((volatile uint16 *)(SPI_TAUD2_TOP_ADDR + 0x200U)))
#define SPI_TAUD2TS         (*((volatile uint16 *)(SPI_TAUD2_TOP_ADDR + 0x1C4U)))
#define SPI_TAUD2TT         (*((volatile uint16 *)(SPI_TAUD2_TOP_ADDR + 0x1C8U)))
#define SPI_INTC2_TOP_ADDR  0xFFF80000UL
#define SPI_EIC_INTTAUD2I0  (*((volatile uint16 *)(SPI_INTC2_TOP_ADDR + (0x2UL * 344U))))

/* Port address register */
#define PTADDR          (0xFFD90000UL)

/* Port controller register setting */
#define REG_P(n)        *(volatile uint16*)(PTADDR + 0x0000UL + ((uint32)(n) * 0x40UL))
#define REG_PSR(n)      *(volatile uint32*)(PTADDR + 0x0004UL + ((uint32)(n) * 0x40UL))
#define REG_PNOT(n)     *(volatile uint32*)(PTADDR + 0x0008UL + ((uint32)(n) * 0x40UL))
#define REG_PPR(n)      *(volatile uint16*)(PTADDR + 0x000CUL + ((uint32)(n) * 0x40UL))
#define REG_PM(n)       *(volatile uint16*)(PTADDR + 0x0010UL + ((uint32)(n) * 0x40UL))
#define REG_PMC(n)      *(volatile uint16*)(PTADDR + 0x0014UL + ((uint32)(n) * 0x40UL))
#define REG_PFC(n)      *(volatile uint16*)(PTADDR + 0x0018UL + ((uint32)(n) * 0x40UL))
#define REG_PFCE(n)     *(volatile uint16*)(PTADDR + 0x001CUL + ((uint32)(n) * 0x40UL))
#define REG_PFCAE(n)    *(volatile uint16*)(PTADDR + 0x0028UL + ((uint32)(n) * 0x40UL))
#define REG_PFCEAE(n)   *(volatile uint16*)(PTADDR + 0x002CUL + ((uint32)(n) * 0x40UL))
#define REG_PIPC(n)     *(volatile uint16*)(PTADDR + 0x4008UL + ((uint32)(n) * 0x40UL))
#define REG_PMSR(n)     *(volatile uint32*)(PTADDR + 0x0020UL + ((uint32)(n) * 0x40UL))
#define REG_PMCSR(n)    *(volatile uint32*)(PTADDR + 0x0024UL + ((uint32)(n) * 0x40UL))
#define REG_PODC(n)     *(volatile uint32*)(PTADDR + 0x4014UL + ((uint32)(n) * 0x40UL))
#define REG_PDSC(n)     *(volatile uint32*)(PTADDR + 0x4018UL + ((uint32)(n) * 0x40UL))
#define REG_PUCC(n)     *(volatile uint32*)(PTADDR + 0x4028UL + ((uint32)(n) * 0x40UL))
#define REG_PKCPROT     *(volatile uint32*)(PTADDR + 0x2F40UL)
#define REG_PWE         *(volatile uint32*)(PTADDR + 0x2F44UL)

#define ALT_OUT1        (uint8)0U
#define ALT_OUT2        (uint8)2U
#define ALT_OUT3        (uint8)4U
#define ALT_OUT4        (uint8)6U
#define ALT_OUT5        (uint8)8U
#define ALT_OUT6        (uint8)10U
#define ALT_OUT7        (uint8)12U
#define ALT_OUT8        (uint8)14U
#define ALT_OUT9        (uint8)16U
#define ALT_OUT10       (uint8)18U
#define ALT_OUT11       (uint8)20U
#define ALT_OUT12       (uint8)22U
#define ALT_OUT13       (uint8)24U
#define ALT_OUT14       (uint8)26U
#define ALT_OUT15       (uint8)28U
#define ALT_OUT16       (uint8)30U

#define ALT_IN1         (uint8)1U
#define ALT_IN2         (uint8)3U
#define ALT_IN3         (uint8)5U
#define ALT_IN4         (uint8)7U
#define ALT_IN5         (uint8)9U
#define ALT_IN6         (uint8)11U
#define ALT_IN7         (uint8)13U
#define ALT_IN8         (uint8)15U
#define ALT_IN9         (uint8)17U
#define ALT_IN10        (uint8)19U
#define ALT_IN11        (uint8)21U
#define ALT_IN12        (uint8)23U
#define ALT_IN13        (uint8)25U
#define ALT_IN14        (uint8)27U
#define ALT_IN15        (uint8)29U
#define ALT_IN16        (uint8)31U

#define ALT_INOUT1      (uint8)1U
#define ALT_INOUT2      (uint8)3U
#define ALT_INOUT3      (uint8)5U
#define ALT_INOUT4      (uint8)7U
#define ALT_INOUT5      (uint8)9U
#define ALT_INOUT6      (uint8)11U
#define ALT_INOUT7      (uint8)13U
#define ALT_INOUT8      (uint8)15U
#define ALT_INOUT9      (uint8)17U
#define ALT_INOUT10     (uint8)19U
#define ALT_INOUT11     (uint8)21U
#define ALT_INOUT12     (uint8)23U
#define ALT_INOUT13     (uint8)25U
#define ALT_INOUT14     (uint8)27U
#define ALT_INOUT15     (uint8)29U

// Setting relay pin
#define BIT2            (1<<2)

/*******************************************************************************
**                             Barrier-Synchronization                        **
*******************************************************************************/
/* Barrier-Synchronization register addresses*/
#define BARR_base         *(volatile uint8*)(0xFFFB8000UL)
#define BR0INIT           *(volatile uint8*)(0xFFFB8000UL)
#define BR0EN             *(volatile uint8*)(0xFFFB8004UL)
#define BR0CHKS           *(volatile uint8*)(0xFFFB8100UL)
#define BR0SYNCS          *(volatile uint8*)(0xFFFB8104UL)
#define BR0CHK0           *(volatile uint8*)(0xFFFB8800UL)
#define BR0CHK1           *(volatile uint8*)(0xFFFB8900UL)
#define BR0SYNC0          *(volatile uint8*)(0xFFFB8804UL)
#define BR0SYNC1          *(volatile uint8*)(0xFFFB8904UL)

/* Barrier-Synchronization register definition */
#define SPI_SYNC_BR0EN                  BR0EN
#define SPI_SYNC_BR0INIT                BR0INIT
#define SPI_SYNC_BR0CHK0                BR0CHK0
#define SPI_SYNC_BR0CHK1                BR0CHK1
#define SPI_SYNC_BR0SYNC0               BR0SYNC0
#define SPI_SYNC_BR0SYNC1               BR0SYNC1

/* Barrier-Synchronization register bit settings */
#define SPI_SYNC_CLEAR                  0x00UL
#define SPI_SYNC_INIT                   0x01UL
#define SPI_SYNC_ENABLE_PE0             0x01UL
#define SPI_SYNC_ENABLE_PE1             0x02UL
#define SPI_SYNC_ENABLE_PE2             0x04UL
#define SPI_SYNC_ENABLE_PE3             0x08UL
#define SPI_SYNC_ENABLE_PE4             0x10UL
#define SPI_SYNC_ENABLE_PE5             0x20UL
#define SPI_SYNC_IS_ENABLED             0x01UL
#define SPI_SYNC_IS_COMPLETED           0x01UL
#define SPI_SYNC_IS_INCOMPLETED         0x00UL

/*******************************************************************************
**                  PEG & PBG: Function safety register definition            **
*******************************************************************************/
/* Registers base adrress */
#define GUARD_PE0CL0    0xFFC6C000
#define GUARD_PE1CL0    0xFFC6C100
#define PBGERRSLV30     0xFFC73200
#define PBG30           0xFFC72B00
#define PBGERRSLV40     0xFFC75400
#define PBG40           0xFFC75300

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
#define PBGKCPROT30      (*(volatile uint32*)(PBGERRSLV30 + 0x18UL))
#define PBGKCPROT40      (*(volatile uint32*)(PBGERRSLV40 + 0x18UL))

/* PBGnPROT0_m */
#define PBG30PROT0(m)   (*(volatile uint32*)(PBG30 + m * 0x08UL))
#define PBG40PROT0(m)   (*(volatile uint32*)(PBG40 + m * 0x08UL))

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#endif /* APP_SPI_DEVICE_SAMPLE_H */

/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
