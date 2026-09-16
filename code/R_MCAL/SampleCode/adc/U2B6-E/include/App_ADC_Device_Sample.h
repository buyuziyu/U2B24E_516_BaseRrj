/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas U2B6E MCAL Components                                                               */
/* Module       = App_ADC_Device_Sample.h                                                                             */
/*====================================================================================================================*/
/*                                  COPYRIGHT                                                                         */
/*====================================================================================================================*/
/* (c) 2025 Renesas Electronics Corporation. All rights reserved.                                                     */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains macros/function prototypes/variables required for  source application file.                     */
/*                                                                                                                    */
/*====================================================================================================================*/
/*                                                                                                                    */
/* Unless otherwise agreed upon in writing between your company and Renesas Electronics Corporation the following     */
/* shall apply!                                                                                                       */
/*                                                                                                                    */
/* Warranty Disclaimer                                                                                                */
/*                                                                                                                    */
/* There is no warranty of any kind whatsoever granted by Renesas. Any warranty is expressly disclaimed and excluded  */
/* by Renesas, either expressed or implied, including but not limited to those for non-infringement of intellectual   */
/* property, merchantability and/or fitness for the particular purpose.                                               */
/*                                                                                                                    */
/* Renesas shall not have any obligation to maintain, service or provide bug fixes for the supplied Product(s) and/or */
/* the Application.                                                                                                   */
/*                                                                                                                    */
/* Each User is solely responsible for determining the appropriateness of using the Product(s) and assumes all risks  */
/* associated with its exercise of rights under this Agreement, including, but not limited to the risks and costs of  */
/* program errors, compliance with applicable laws, damage to or loss of data, programs or equipment, and             */
/* unavailability or interruption of operations.                                                                      */
/*                                                                                                                    */
/* Limitation of Liability                                                                                            */
/*                                                                                                                    */
/* In no event shall Renesas be liable to the User for any incidental, consequential, indirect, or punitive damage    */
/* (including but not limited to lost profits) regardless of whether such liability is based on breach of contract,   */
/* tort, strict liability, breach of warranties, failure of essential purpose or otherwise and even if advised of the */
/* possibility of such damages. Renesas shall not be liable for any services or products provided by third party      */
/* vendors, developers or consultants identified or referred to the User by Renesas in connection with the Product(s) */
/* and/or the Application.                                                                                            */
/*                                                                                                                    */
/*====================================================================================================================*/
/* Environment:                                                                                                       */
/*              Devices:        U2B6E                                                                                 */
/*====================================================================================================================*/

/***********************************************************************************************************************
**                      Revision Control History                                                                      **
***********************************************************************************************************************/
/*
 * 2.5.1:  30/06/2025  : Initial Version
 */
/**********************************************************************************************************************/
#ifndef APP_ADC_DEVICE_SAMPLE_H
#define APP_ADC_DEVICE_SAMPLE_H

/***********************************************************************************************************************
**                      Include Section                                                                               **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                      Global Symbols                                                                                **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                          Defines                                                                                   **
***********************************************************************************************************************/
/* Interrupt control registers base addresses*/
#define ADC_INTCREG_BASEADD_ADCK0    (volatile uint16 *)0xFFF80372 /* EIC 441 to 445 */
#define ADC_INTCREG_BASEADD_ADCK1    (volatile uint16 *)0xFFF80386 /* EIC 451 to 455 */
#define ADC_INTCREG_BASEADD_ADCK2    (volatile uint16 *)0xFFF8037C /* EIC 446 to 450 */
#define ADC_ADCK_NUM_OF_INTERRUPTS   5UL

#define ADC_INTCREG_BASEADD_ADE      (volatile uint16 *)0xFFF8039A /* EIC 461 to 463 */
#define ADC_ADE_NUM_OF_INTERRUPTS    3UL

#define ADC_INTCREG_BASEADD_SDMAC0   (volatile uint16 *)0xFFF8008C
#define ADC_SDMAC_NUM_OF_INTERRUPTS  16UL

#define EIC08                        (*((volatile uint16 *)0xFFFC4010UL))

#define PKCPROT                      (*((volatile uint32 *)0xFFD92F40UL))
#define PWE                          (*((volatile uint32 *)0xFFD92F44UL))

#define P33                          (*((volatile uint16 *)0XFFD90840UL))
#define PM33                         (*((volatile uint16 *)0xFFD90850UL))
#define PMC33                        (*((volatile uint16 *)0xFFD90854UL))
#define PFC33                        (*((volatile uint16 *)0xFFD90858UL))
#define PFCE33                       (*((volatile uint16 *)0xFFD9085CUL))
#define PFCAE33                      (*((volatile uint16 *)0xFFD90868UL))
#define PFCEAE33                     (*((volatile uint16 *)0xFFD9086CUL))

#define PCR1_0                       (*((volatile uint16 *)0xffd92040UL))

/* Module standby registers */
#define ADC_MSRKCPROT                (*((volatile uint32 *)0xFF981710UL))
#define ADC_MSR_ADC_ISO              (*((volatile uint32 *)0xFF981078UL))

/* Enable all modules in this MSR register */
#define ADC_MSR_ACTIVE               0x00000000UL

/* Protection key codes */
#define ADC_KCPROT_CLR               0xA5A5A500UL
#define ADC_KCPROT_SET               0xA5A5A501UL

#define ADC_EIC_EITB                 (uint16)(1U << 6)
#define ADC_EIC_EIP_MASK             (uint16)0x0007U
#define ADC_EIC_EIP_LOWEST           (uint16)0x0007U
#define ADC_EIC_EIP_MIDDLE           (uint16)0x0004U

#define MSR_GTM                      (*((volatile uint32 *)0xff981020UL))

/* Definition for GTM TOM0 */
#define GTM0_TOM0_CH0_CTRL                 *((volatile uint32 *)0xFF601000UL)
#define GTM0_TOM0_CH0_CM0                  *((volatile uint32 *)0xFF60100CUL)
#define GTM0_TOM0_CH0_CN0                  *((volatile uint32 *)0xFF601014UL)
#define GTM0_TOM0_CH0_CM1                  *((volatile uint32 *)0xFF601010UL)
#define GTM0_TOM0_CH0_SR0                  *((volatile uint32 *)0xFF601004UL)
#define GTM0_TOM0_CH0_SR1                  *((volatile uint32 *)0xFF601008UL)
#define GTM0_TOM0_TGC0_OUTEN_STAT          *((volatile uint32 *)0xFF60147CUL)
#define GTM0_TOM0_TGC0_ENDIS_STAT          *((volatile uint32 *)0xFF601474UL)
#define GTM0_TOM0_TGC0_GLB_CTRL            *((volatile uint32 *)0xFF601430UL)
#define GTM0_TOM0_TGC0_FUPD_CTRL           *((volatile uint32 *)0xFF601438UL)
#define GTM0_TOM0_TGC0_ACT_TB              *((volatile uint32 *)0xFF601434UL)

/* CMU register */
#define CMU_GCLK_NUM                  *((volatile uint32 *)0xff600084UL)
#define CMU_GCLK_DEN                  *((volatile uint32 *)0xff600088UL)
#define CMU_CLK_0_CTRL                *((volatile uint32 *)0xff60008cUL)
#define CMU_CLK_EN                    *((volatile uint32 *)0xff600080UL)

/* FCLK register */
#define CMU_FXCLK_CTRL                     *((volatile uint32 *)0xff6000c4UL)

/* clock setting */
#define PLLE          (*((volatile uint32*)0xFF980000UL)) /* PLL Enable Register */
#define PLLS          (*((volatile uint32*)0xFF980004UL)) /* PLL Status Register */
#define PLLSTPM       (*((volatile uint32*)0xFF98000CUL)) /* PLL Stop Mask Register */
#define MOSCE         (*((volatile uint32*)0xFF988000UL)) /* MainOSC Enable Register */
#define MOSCS         (*((volatile uint32*)0xFF988004UL)) /* MainOSC Status Register */
#define MOSCC         (*((volatile uint32*)0xFF988008UL)) /* MainOSC Control Register */
#define MOSCSTPM      (*((volatile uint32*)0xFF98800CUL)) /* MainOSC Stop Mask Register */
#define MOSCAS        (*((volatile uint32*)0xFF988014UL)) /* MainOSC ADET Status Register */
#define MOSCAGC       (*((volatile uint32*)0xFF988018UL)) /* MainOSC Auto Gain Control Register */
#define MOSCAGCS      (*((volatile uint32*)0xFF98801CUL)) /* MainOSC Auto Gain Control Status Register */
#define HSOSCS        (*((volatile uint32*)0xFF988100UL)) /* HSIntOSC Status Register */
#define HSOSCSTPM     (*((volatile uint32*)0xFF988104UL)) /* HSIntOSC Stop Mask Register */
#define HSOSCUT       (*((volatile uint32*)0xFF988108UL)) /* HSIntOSC User Trimming Register */
#define CKSC_RLINC    (*((volatile uint32*)0xFF980140UL)) /* CLK_RLIN Selector Control Register */
#define CKSC_RLINS    (*((volatile uint32*)0xFF980148UL)) /* CLK_RLIN Selector Status Register */
#define CKSC_RCANC    (*((volatile uint32*)0xFF980150UL)) /* CLK_RCANOSC Selector Control Register */
#define CKSC_RCANS    (*((volatile uint32*)0xFF980158UL)) /* CLK_RCANOSC Selector Status Register */
#define CKSC_ADCC     (*((volatile uint32*)0xFF980160UL)) /* CLK_ADC Selector Control Register */
#define CKSC_ADCS     (*((volatile uint32*)0xFF980168UL)) /* CLK_ADC Selector Status Register */
#define CKSC_MSPIC    (*((volatile uint32*)0xFF980170UL)) /* CLK_MSPI Selector Control Register */
#define CKSC_MSPIS    (*((volatile uint32*)0xFF980178UL)) /* CLK_MSPI Selector Status Register */
#define CKSC_AWDTC    (*((volatile uint32*)0xFF988200UL)) /* CLKA_WDT Selector Control Register */
#define CKSC_AWDTS    (*((volatile uint32*)0xFF988208UL)) /* CLKA_WDT Selector Status Register */
#define CKSC_ATAUJC   (*((volatile uint32*)0xFF988210UL)) /* CLKA_TAUJ Selector Control Register */
#define CKSC_ATAUJS   (*((volatile uint32*)0xFF988218UL)) /* CLKA_TAUJ Selector Status Register */
#define CKSC_ARTCAC   (*((volatile uint32*)0xFF988220UL)) /* CLKA_RTCA Selector Control Register */
#define CKSC_ARTCAS   (*((volatile uint32*)0xFF988228UL)) /* CLKA_RTCA Selector Status Register */
#define CKSC_AADCC    (*((volatile uint32*)0xFF988230UL)) /* CLKA_ADC Selector Control Register */
#define CKSC_AADCS    (*((volatile uint32*)0xFF988238UL)) /* CLKA_ADC Selector Status Register */
#define CLKD_AADCC    (*((volatile uint32*)0xFF988240UL)) /* CLKA_ADC Divider Control Register */
#define CLKD_AADCS    (*((volatile uint32*)0xFF988248UL)) /* CLKA_ADC Divider Status Register */
#define CKSC_FOUT0C   (*((volatile uint32*)0xFF988250UL)) /* FOUT0 Clock Selector Control Register */
#define CKSC_FOUT0S   (*((volatile uint32*)0xFF988258UL)) /* FOUT0 Clock Selector Status Register */
#define CLKD_FOUT0C   (*((volatile uint32*)0xFF988260UL)) /* FOUT0 Clock Divider Control Register */
#define CLKD_FOUT0S   (*((volatile uint32*)0xFF988268UL)) /* FOUT0 Clock Divider Status Register */
#define CKSC_FOUT1C   (*((volatile uint32*)0xFF988270UL)) /* FOUT1 Clock Selector Control Register */
#define CKSC_FOUT1S   (*((volatile uint32*)0xFF988278UL)) /* FOUT1 Clock Selector Status Register */
#define CLKD_FOUT1C   (*((volatile uint32*)0xFF988280UL)) /* FOUT1 Clock Divider Control Register */
#define CLKD_FOUT1S   (*((volatile uint32*)0xFF988288UL)) /* FOUT1 Clock Divider Status Register */
#define CLKKCPROT1    (*((volatile uint32*)0xFF980700UL)) /* Clock Controller Register Key Code Protection Register 1 */
#define CKD_PLLC      (*((volatile uint32*)0xFF980120UL)) /* CLK_PLLO Divider Control Register */
#define CKD_SSCGC     (*((volatile uint32*)0xFF980130UL)) /* CLK_SSCGO Divider Control Register */
#define CKD_SSCG1C    (*((volatile uint32*)0xFF980138UL)) /* CLK_SSCG1O Divider Control Register */
#define CKD_PLLS      (*((volatile uint32*)0xFF980128UL)) /* CLK_PLLO Divider Status Register */
#define CKD_SSCGS     (*((volatile uint32*)0xFF980134UL)) /* CLK_SSCGO Divider Status Register */
#define CKD_SSCG1S    (*((volatile uint32*)0xFF98013CUL)) /* CLK_SSCG1O Divider Status Register */
#define CKS_CLEANC    (*((volatile uint32*)0xFF980100UL)) /* CLK_SYS_CLEAN Selector Control Register */
#define CKS_CLEANS    (*((volatile uint32*)0xFF980108UL)) /* CLK_SYS_CLEAN Selector Status Register */
#define CKS_SSCGC     (*((volatile uint32*)0xFF980110UL)) /* CLK_SYS_SSCG Selector Control Register */
#define CKS_SSCGS     (*((volatile uint32*)0xFF980114UL)) /* CLK_SYS_SSCG Selector Status Register */
#define CKS_SSCG1C    (*((volatile uint32*)0xFF980118UL)) /* CLK_SYS_SSCG1 Selector Control Register */
#define CKS_SSCG1S    (*((volatile uint32*)0xFF98011CUL)) /* CLK_SYS_SSCG1 Selector Status Register */

/* Bounding register for select interrupt table */
/* PE 0 */
#define EIBD442        *((volatile uint32*)0xfff826E8UL) /* ADI01: EIC442  */
#define EIBD72         *((volatile uint32*)0xfff82120UL) /* DMA0_02: EIC72 */

/* PE 1 */
#define EIBD453        *((volatile uint32*)0xfff82714UL) /* ADI12: EIC453  */
#define EIBD85         *((volatile uint32*)0xfff82154UL) /* DMA0_15: EIC85 */

/* Bounding register for select interrupt table */
#define ADC_EIBD_PEID_MASK     0xFFFFFFF8UL
/* PE 0 */
#define ADC_EIBD_PEID_PE0      0x00000000UL
/* PE 1 */
#define ADC_EIBD_PEID_PE1      0x00000001UL

/* PEG and PBG: Function safety register definition */
/* Registers base adrress */
#define GUARD_PE0CL0    0xFFC6C000
#define GUARD_PE1CL0    0xFFC6C100
#define PBGERRSLV60     0xFFC83000
#define PBG60           0xFFC81000
#define PBGERRSLV70     0xFFF4A000
#define PBG70           0xFFF49400

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
#define PBGKCPROT60      (*(volatile uint32*)(PBGERRSLV60 + 0x18UL))
#define PBGKCPROT70      (*(volatile uint32*)(PBGERRSLV70 + 0x18UL))

/* PBGnPROT0_m */
#define PBG60PROT0(m)   (*(volatile uint32*)(PBG60 + m * 0x08UL))
#define PBG70PROT0(m)   (*(volatile uint32*)(PBG70 + m * 0x08UL))

/* OS Timer register OSTM0 */
#define ADC_OSTM0CMP        (*((volatile uint32 *)0xFFBF0000UL))
#define ADC_OSTM0TS         (*((volatile uint8 *)0xFFBF0014UL))
#define ADC_OSTM0TT         (*((volatile uint8 *)0xFFBF0018UL))
#define ADC_OSTM0CTL        (*((volatile uint8 *)0xFFBF0020UL))
#define ADC_MSR_OSTM        (*((volatile uint32 *)0xFF981180UL))
#define ADC_EIC_BASE_ADDR       (0xFFF80000UL)
#define ADC_EIC_ADDR(n)         ((ADC_EIC_BASE_ADDR) + ((n) * 2UL))

//EIDB: EI Level Interrupt Bind Register
#define INTC2_EIBD360       *(uint32*)(0xFFF825A0UL)
#define INTC2_EIBD8         *(uint32*)(0xFFF82020UL)
#define INTC2_EIBD70        *(uint32*)(0xFFF82118UL)
#define INTC2_EIBD71        *(uint32*)(0xFFF8211CUL)
#define INTC2_EIBD72        *(uint32*)(0xFFF82120UL)
#define INTC2_EIBD73        *(uint32*)(0xFFF82124UL)
#define INTC2_EIBD74        *(uint32*)(0xFFF82128UL)
#define INTC2_EIBD75        *(uint32*)(0xFFF8212CUL)
#define INTC2_EIBD76        *(uint32*)(0xFFF82130UL)
#define INTC2_EIBD77        *(uint32*)(0xFFF82134UL)
#define INTC2_EIBD78        *(uint32*)(0xFFF82138UL)
#define INTC2_EIBD79        *(uint32*)(0xFFF8213CUL)
#define INTC2_EIBD80        *(uint32*)(0xFFF82140UL)
#define INTC2_EIBD81        *(uint32*)(0xFFF82144UL)
#define INTC2_EIBD82        *(uint32*)(0xFFF82148UL)
#define INTC2_EIBD83        *(uint32*)(0xFFF8214CUL)
#define INTC2_EIBD84        *(uint32*)(0xFFF82150UL)
#define INTC2_EIBD85        *(uint32*)(0xFFF82154UL)
#define INTC2_EIBD825       *(uint32*)(0xFFF82CE4UL)
#define INTC2_EIBD826       *(uint32*)(0xFFF82CE8UL)
#define INTC2_EIBD827       *(uint32*)(0xFFF82CECUL)
#define INTC2_EIBD828       *(uint32*)(0xFFF82CF0UL)
#define INTC2_EIBD829       *(uint32*)(0xFFF82CF4UL)
#define INTC2_EIBD830       *(uint32*)(0xFFF82CF8UL)
#define INTC2_EIBD831       *(uint32*)(0xFFF82CFCUL)
#define INTC2_EIBD832       *(uint32*)(0xFFF82D00UL)
#define INTC2_EIBD833       *(uint32*)(0xFFF82D04UL)
#define INTC2_EIBD834       *(uint32*)(0xFFF82D08UL)
#define INTC2_EIBD835       *(uint32*)(0xFFF82D0CUL)
#define INTC2_EIBD836       *(uint32*)(0xFFF82D10UL)
#define INTC2_EIBD837       *(uint32*)(0xFFF82D14UL)
#define INTC2_EIBD838       *(uint32*)(0xFFF82D18UL)
#define INTC2_EIBD839       *(uint32*)(0xFFF82D1CUL)
#define INTC2_EIBD840       *(uint32*)(0xFFF82D20UL)
#define INTC2_EIBD441       *(uint32*)(0xFFF826E4UL)
#define INTC2_EIBD442       *(uint32*)(0xFFF826E8UL)
#define INTC2_EIBD443       *(uint32*)(0xFFF826ECUL)
#define INTC2_EIBD444       *(uint32*)(0xFFF826F0UL)
#define INTC2_EIBD445       *(uint32*)(0xFFF826F4UL)
#define INTC2_EIBD451       *(uint32*)(0xFFF8270CUL)
#define INTC2_EIBD452       *(uint32*)(0xFFF82710UL)
#define INTC2_EIBD453       *(uint32*)(0xFFF82714UL)
#define INTC2_EIBD454       *(uint32*)(0xFFF82718UL)
#define INTC2_EIBD455       *(uint32*)(0xFFF8271CUL)
#define INTC2_EIBD446       *(uint32*)(0xFFF826F8UL)
#define INTC2_EIBD447       *(uint32*)(0xFFF826FCUL)
#define INTC2_EIBD448       *(uint32*)(0xFFF82700UL)
#define INTC2_EIBD449       *(uint32*)(0xFFF82704UL)
#define INTC2_EIBD450       *(uint32*)(0xFFF82708UL)
#define INTC2_EIBD456       *(uint32*)(0xFFF82720UL)
#define INTC2_EIBD457       *(uint32*)(0xFFF82724UL)
#define INTC2_EIBD458       *(uint32*)(0xFFF82728UL)
#define INTC2_EIBD459       *(uint32*)(0xFFF8272CUL)
#define INTC2_EIBD460       *(uint32*)(0xFFF82730UL)
#define INTC2_EIBD461       *(uint32*)(0xFFF82734UL)
#define INTC2_EIBD463       *(uint32*)(0xFFF8273CUL)
#define INTC2_EIBD462       *(uint32*)(0xFFF82738UL)
#define INTC2_EIBD464       *(uint32*)(0xFFF82740UL)

/***********************************************************************************************************************
**                      Function Prototypes                                                                           **
***********************************************************************************************************************/

extern void Timer0_Interrupt(void);

#endif /* APP_ADC_DEVICE_SAMPLE_H */

/***********************************************************************************************************************
**                      End of File                                                                                   **
***********************************************************************************************************************/
