/*============================================================================*/
/* Project      = RH850/X2x MCAL PF Development                               */
/* Module       = App_CAN_Device_Sample.h                                     */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2024, 2025 Renesas Electronics Corporation. All rights reserved.       */
/*============================================================================*/
/* Purpose:                                                                   */
/* Header file information for application                                    */
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
/*              Devices:        U2B6-E                                        */
/*============================================================================*/

/*******************************************************************************
**                      Revision Control History                              **
*******************************************************************************/
/*
 * 2.4.1: 30/06/2025  : Remove the SW-VERSION from header of file
 * 2.3.1: 31/03/2025  : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 * 2.2.0: 31/12/2024  : Add new macro related check point.
 * 2.1.2: 31/10/2024  : Add new macro 
 *                              TOTAL_CHECKPOINT_MUTILCORE_SINGLEVARIANT_CORE1
 * 2.1.1: 21/06/2024  : Remove Mcu_Reset
 *        11/05/2024  : Initial Version
 */
/******************************************************************************/
#ifndef APP_CAN_DEVICE_SAMPLE_H
#define APP_CAN_DEVICE_SAMPLE_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "Can.h"

/*******************************************************************************
**                      Global variable                                       **
*******************************************************************************/

extern uint8 GaaByteArray0[];
extern uint8 GaaByteArray1[];


/*******************************************************************************
**                      Global Symbols                                   **
*******************************************************************************/
#define TOTAL_CHECKPOINT_SINGLECORE_SINGLEVARIANT 55
#define TOTAL_CHECKPOINT_SINGLECORE_MULTIVARIANT 75
#define TOTAL_CHECKPOINT_MULTICORE_SINGLEVARIANT_CORE0   48
#define TOTAL_CHECKPOINT_MUTILCORE_SINGLEVARIANT_CORE1   13
#define TOTAL_CHECKPOINT_MULTICORE_POSTBUILD_CORE0   42
#define TOTAL_CHECKPOINT_MULTICORE_POSTBUILD_CORE1   18

typedef struct STag_Can_Port0RegSetType
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
  uint16 usPSFSC;                       /* +0034H+n*40H PSFSCn  */
  uint16 usReserved10;
  uint16 usPSFSD;                       /* +0038H+n*40H PSFSDn  */
  uint16 usReserved11;
  uint16 PSFSCE;                        /* +003CH+n*40H PSFSCEn */
  uint16 usReserved12;
} Can_Port0RegSetType;

typedef struct STag_Can_Port1RegSetType
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
  uint16 usPODC;                        /* +4014H+n*40H PODCn   */
  uint16 usReserved5;
  uint16 usPODCE;                       /* +4018H+n*40H PODCEn  */
  uint16 usReserved6;
  uint16 usPSDC;                        /* +401CH+n*40H PSDCn   */
  uint16 usReserved7;
  uint16 usPIS;                         /* +4020H+n*40H PISn    */
  uint16 usReserved8;
  uint16 usPISA;                        /* +4024H+n*40H PISAn   */
  uint16 usReserved9;
  uint16 usPUCC;                        /* +4028H+n*40H PUCCn   */
  uint16 aaReserved10[11];
} Can_Port1RegSetType;

typedef struct STag_Can_ATU5GChRegSetType
{
  uint8  ucTCRG;                        /* +0010H+n*10H TCRGn   */
  uint8  ucReseved0;
  uint8  ucTSRG;                        /* +0012H+n*10H TSRGn   */
  uint8  ucTSCRG;                       /* +0013H+n*10H TSCRGn  */
  uint32 ulTCNTG;                       /* +0014H+n*10H TCNTGn  */
  uint32 ulOCRG;                        /* +0018H+n*10H OCRGn   */
  uint32 ulRLDG;                        /* +001CH+n*10H RLDGn   */
} Can_ATU5GChRegSetType;

typedef struct STag_Can_ATU5GRegSetType
{
  uint16 usTSTRG;                       /* +0000H TSTRG         */
  uint16 usReserved0;
  uint16 usTIERG;                       /* +0004H TIERG         */
  uint16 usReserved1;
  uint16 usRLDCRG;                      /* +0008H RLDCRG        */
  uint16 usReserved2;
  uint32 ulReserved3;
  Can_ATU5GChRegSetType aaCh[10];
} Can_ATU5GRegSetType;

/* Clock controller registers */
#define CAN_PLLCLKS       (*(volatile uint32*)0xFF703200)
#define CAN_CLKSTAB       0x00000002UL
#define CAN_CKSC0C        (*(volatile uint32*)0xFF703100)
#define CAN_CKSC0S        (*(volatile uint32*)0xFF703108)
#define CAN_CKSC0_PLL     0x00000001UL
#define CAN_CLKD0DIV      (*(volatile uint32*)0xFF703000)
#define CAN_CLKD0DIV_DIV1 0x00000001UL
#define CAN_CLKD0STAT     (*(volatile uint32*)0xFF703004)
#define CAN_CLKD0SYNC     0x00000002UL
#define CAN_CLKKCPROT0    (*(volatile uint32*)0xFF703700)

/* Module standby registers */
#define CAN_MSR_ETN         (*(volatile uint32*)0xFF981030UL) 
#define CAN_MSR_RCAN        (*(volatile uint32*)0xFF981000UL)
#define CAN_MSR_TAUD        (*(volatile uint32*)0xFF981130UL)
#define CAN_MSRKCPROT       (*(volatile uint32*)0xFF981710UL)

/* Enable all modules in this MSR register */
#define CAN_MSR_ACTIVE      0x00000000UL

/* Protection key codes */
#define CAN_KCPROT_CLR 0xA5A5A500UL
#define CAN_KCPROT_SET 0xA5A5A501UL

/* Enable all modules in this MSR register */
#define CAN_MSR_ACTIVE 0x00000000UL
/* Disable all modules in this MSR register */
#define CAN_MSR_STOP   0xFFFFFFFFUL

/* INTC2 base address */
#define CAN_EIC           ((volatile uint16*)0xFFF80000UL)
/* Number of EIC registers */
#define CAN_EIC_NUMBER    512UL

#if 0
#define CAN_PORT0         ((volatile Can_Port0RegSetType*)0xFF610000UL)
#define CAN_PORT1         ((volatile Can_Port1RegSetType*)0xFF614000UL)
#else
#define CAN_PORT0         ((volatile Can_Port0RegSetType*)0xFFD90000UL)
#define CAN_PORT1         ((volatile Can_Port1RegSetType*)0xFFD94000UL)
#define CAN_PKCPROT       (*(volatile uint32*)0xFFD92F40UL)
#define CAN_PWE           (*(volatile uint32*)0xFFD92F44UL)
#endif

#if 0 /* ATU5 -> OSTM0 */
#define CAN_ATU5G         ((volatile Can_ATU5GRegSetType*)0xFFE65C00UL)
#define CAN_ATUENR        (*(volatile uint8*)0xFFE60000UL)
#define CAN_PSCR0         (*(volatile uint16*)0xFFE60080UL)
#define CAN_TSTRG         (*(volatile uint16*)0xFFE65C00UL)
#define CAN_TIERG         (*(volatile uint16*)0xFFE65C04UL)
#define CAN_RLDCRG        (*(volatile uint16*)0xFFE65C08UL)
#define CAN_TCRG0         (*(volatile uint8*)0xFFE65C10UL)
#define CAN_TCNTG0        (*(volatile uint32*)0xFFE65C14UL)
#define CAN_OCRG0         (*(volatile uint32*)0xFFE65C18UL)
#else
/* Timer Registers */
#define CAN_OSTM0CMP        (*((volatile uint32 *)0xFFBF0000UL))
#define CAN_OSTM0CNT        (*((volatile uint32 *)0xFFBF0004UL))
#define CAN_OSTM0TO         (*((volatile uint8  *)0xFFBF0008UL))
#define CAN_OSTM0TOE        (*((volatile uint8  *)0xFFBF000CUL))
#define CAN_OSTM0TE         (*((volatile uint8  *)0xFFBF0010UL))
#define CAN_OSTM0TS         (*((volatile uint8  *)0xFFBF0014UL))
#define CAN_OSTM0TT         (*((volatile uint8  *)0xFFBF0018UL))
#define CAN_OSTM0CTL        (*((volatile uint8  *)0xFFBF0020UL))

#define CAN_ICOSTM018       (*((volatile uint16 *)0xFFFC0024UL)) /* EIC018 */

#endif

/* PCLK(LSB): 40MHz */
#define CAN_PCLK_HZ         40000000UL
/* Interval of Can_MainFunction_Handling: 10ms */
#define CAN_POLLING_INTERVAL_MS 10UL

/* Interrupt Vector Setting: Table mode, priority 7 */
#define CAN_EIC_PRI       (uint16)0x0007
#define CAN_EITB          (uint16)0x0040
#define CAN_EIMK          (uint16)0x0080

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
#define MSRKCPROT           (*((volatile uint32 *)0xFF981710UL))

/* clock setting */
#define PLLE              (*((volatile unsigned long *)0xFF980000UL)) /* PLL Enable Register */
#define PLLS              (*((volatile unsigned long *)0xFF980004UL)) /* PLL Status Register */
#define MOSCE             (*((volatile unsigned long *)0xFF988000UL)) /* MainOSC Enable Register */
#define MOSCS             (*((volatile unsigned long *)0xFF988004UL)) /* MainOSC Status Register */
#define HSOSCS            (*((volatile unsigned long *)0xFF988100UL)) /* HSIntOSC Status Register */
#define HSOSCSTPM         (*((volatile unsigned long *)0xFF988104UL)) /* HSIntOSC Stop Mask Register */
#define MOSCSTPM          (*((volatile unsigned long *)0xFF98800CUL)) /* MainOSC Stop Mask Register */
#define PLLSTPM           (*((volatile unsigned long *)0xFF98000CUL)) /* PLL Stop Mask Register */

#define CKS_CLEANC        (*((volatile unsigned long *)0xFF980100UL)) /* CLK_CLEAN Selector Control Register */
#define CKS_CLEANS        (*((volatile unsigned long *)0xFF980108UL)) /* CLK_CLEAN Selector Status Register */
#define CKS_SSCGC         (*((volatile unsigned long *)0xFF980110UL)) /* CLK_SSCG Selector Control Register */
#define CKS_SSCGS         (*((volatile unsigned long *)0xFF980114UL)) /* CLK_SSCG Selector Status Register */
#define CKS_SSCG1C        (*((volatile unsigned long *)0xFF980118UL)) /* CLK_SSCG1 Selector Control Register */
#define CKS_SSCG1S        (*((volatile unsigned long *)0xFF98011CUL)) /* CLK_SSCG1 Selector Status Register */
#define CKS_RCANC         (*((volatile unsigned long *)0xFF980150UL)) /* CLK_CANFD_C/CLK_CANFD_XIN Selector Control Register */
#define CKS_RCANS         (*((volatile unsigned long *)0xFF980158UL)) /* CLK_CANFD_C/CLK_CANFD_XIN Selector Status Register */

#define CKS_CANXL0C       (*((volatile unsigned long *)0xFF9801A0UL)) /* CLK_SSCG1O Divider Status Register */
#define CKS_CANXL0S       (*((volatile unsigned long *)0xFF9801A8UL)) /* CLK_SSCG1O Divider Status Register */
#define CKS_CANXL1C       (*((volatile unsigned long *)0xFF9801B0UL)) /* CLK_SSCG1O Divider Status Register */
#define CKS_CANXL1S       (*((volatile unsigned long *)0xFF9801B8UL)) /* CLK_SSCG1O Divider Status Register */

#define CKD_PLLC          (*((volatile unsigned long *)0xFF980120UL)) /* CLK_PLLO Divider Control Register */
#define CKD_SSCGC         (*((volatile unsigned long *)0xFF980130UL)) /* CLK_SSCGO Divider Control Register */
#define CKD_SSCG1C        (*((volatile unsigned long *)0xFF980138UL)) /* CLK_SSCG1O Divider Control Register */
#define CKD_PLLS          (*((volatile unsigned long *)0xFF980128UL)) /* CLK_PLLO Divider Status Register */
#define CKD_SSCGS         (*((volatile unsigned long *)0xFF980134UL)) /* CLK_SSCGO Divider Status Register */
#define CKD_SSCG1S        (*((volatile unsigned long *)0xFF98013CUL)) /* CLK_SSCG1O Divider Status Register */

#define CLKKCPROT1        (*((volatile unsigned long *)0xFF980700UL)) /* Clock Controller Register Key Code Protection Register 1 */

/* Clock controller registers */

#define CAN_TAUD0_TOP_ADDR 0xFFBF4000UL
#define CAN_TAUD0TPS        (*((volatile uint16 *)(CAN_TAUD0_TOP_ADDR + 0x240U)))
#define CAN_TAUD0CDR0       (*((volatile uint16 *)(CAN_TAUD0_TOP_ADDR + 0x000U)))
#define CAN_TAUD0CMOR0      (*((volatile uint16 *)(CAN_TAUD0_TOP_ADDR + 0x200U)))
#define CAN_TAUD0TS         (*((volatile uint16 *)(CAN_TAUD0_TOP_ADDR + 0x1C4U)))
#define CAN_TAUD0TT         (*((volatile uint16 *)(CAN_TAUD0_TOP_ADDR + 0x1C8U)))

#define CAN_TAUD2_TOP_ADDR 0xFFBF6000UL
#define CAN_TAUD2TPS        (*((volatile uint16 *)(CAN_TAUD2_TOP_ADDR + 0x240U)))
#define CAN_TAUD2CDR0       (*((volatile uint16 *)(CAN_TAUD2_TOP_ADDR + 0x000U)))
#define CAN_TAUD2CMOR0      (*((volatile uint16 *)(CAN_TAUD2_TOP_ADDR + 0x200U)))
#define CAN_TAUD2TS         (*((volatile uint16 *)(CAN_TAUD2_TOP_ADDR + 0x1C4U)))
#define CAN_TAUD2TT         (*((volatile uint16 *)(CAN_TAUD2_TOP_ADDR + 0x1C8U)))

#define CAN_INTC1_TOP_ADDR  0xFFFC4000UL
#define CAN_EIC_INTTAUD0I0  (*((volatile uint16 *)(CAN_INTC1_TOP_ADDR + (0x2UL * 10U))))
#define CAN_INTC2_TOP_ADDR  0xFFF80000UL
#define CAN_EIC_INTTAUD2I0  (*((volatile uint16 *)(CAN_INTC2_TOP_ADDR + (0x2UL * 344U))))
/* Boundary PE */
#define PEID_PE1_VALUE                    0x00000001UL
#define PEID_PE2_VALUE                    0x00000002UL
#define CAN_EIBD2                         ((volatile uint32*)0xFFF82000UL)
#define GPTMA_TME              (*((volatile unsigned long *)0xFF920010UL)) /* GPTMA timer */
#define GPTMA_GTIV             (*((volatile unsigned long *)0xFF920020UL)) /* GPTMA timer */

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

extern void Clock_Init(void);
/* Timer Initialization */
extern void Gpt_Init(void);
extern void Gpt_Init_1(void);
/* Controller Port(s) Initialization */
extern void Port_Init(void);
/* Watchdog Initialization */
extern void Wdg_Init(void);
/* System Initialization */
extern void Mcu_Init(void);

#endif /* APP_CAN_DEVICE_SAMPLE_H */

/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
