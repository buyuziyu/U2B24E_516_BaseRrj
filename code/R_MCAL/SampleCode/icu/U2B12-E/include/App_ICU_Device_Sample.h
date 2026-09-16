/*============================================================================*/
/* Project      = RH850/X2x MCAL PF Development                               */
/* Module       = App_ICU_Device_Sample.h                                     */
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
/*              Devices: RH850/U2B12-E                                        */
/*============================================================================*/

/*******************************************************************************
**                      Revision Control History                              **
*******************************************************************************/
/*
 * 2.4.1:  30/06/2025  : Remove SW-VERSION in file header
 * 2.3.1:  31/03/2025  : As part of GTM support the following are made:
 *                       + Add GTM specific stub setting
 *                       As part of G4KH U2Bx-E support, the following are made:
 *                       + Add register address for: EIBD960 to EIBD963,
 *                         EIBD328 to EIBD330, EIBD86 to EIBD90, EIBD765
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D 
 *                       Final Release
 * 2.1.2:  31/10/2024  : Update SW-VERSION for Ver22.01.02 Beta2 Release 
 * 2.0.2:  24/06/2024  : Initial Version
 */
/******************************************************************************/
#ifndef APP_ICU_DEVICE_SAMPLE_H
#define APP_ICU_DEVICE_SAMPLE_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/
#include <stdio.h>
#define ICU_SAMPLE_ZERO               0U

extern void Guard_Enable_PE(void);

/* EI level Interrupt Bind Register */
#define INTC2_EIBD960            (*((volatile uint32 *)0xfff82f00UL)) 
#define INTC2_EIBD961            (*((volatile uint32 *)0xfff82f04UL)) 
#define INTC2_EIBD962            (*((volatile uint32 *)0xfff82f08UL)) 
#define INTC2_EIBD963            (*((volatile uint32 *)0xfff82f0cUL)) 
#define INTC2_EIBD328            (*((volatile uint32 *)0xfff82520UL)) 
#define INTC2_EIBD329            (*((volatile uint32 *)0xfff82524UL)) 
#define INTC2_EIBD330            (*((volatile uint32 *)0xfff82528UL)) 
#define INTC2_EIBD86             (*((volatile uint32 *)0xfff82158UL)) 
#define INTC2_EIBD87             (*((volatile uint32 *)0xfff8215cUL)) 
#define INTC2_EIBD88             (*((volatile uint32 *)0xfff82160UL)) 
#define INTC2_EIBD89             (*((volatile uint32 *)0xfff82164UL))
#define INTC2_EIBD90             (*((volatile uint32 *)0xfff82168UL))
#define INTC2_EIBD765            (*((volatile uint32 *)0xfff82bf4UL))

/* Register Definitions for configuring ports (Pn) */
#define PORT_base     0xFFD90000UL
#define ICU_PFC(n)    *((volatile uint16 *)(PORT_base + 0x0018UL + 0x40UL*n))
#define ICU_PFCE(n)   *((volatile uint16 *)(PORT_base + 0x001CUL + 0x40UL*n))
#define ICU_PFCAE(n)  *((volatile uint16 *)(PORT_base + 0x0028UL + 0x40UL*n))
#define ICU_PFCEAE(n) *((volatile uint16 *)(PORT_base + 0x002CUL + 0x40UL*n))
#define ICU_PM(n)     *((volatile uint16 *)(PORT_base + 0x0010UL + 0x40UL*n))
#define ICU_PMC(n)    *((volatile uint16 *)(PORT_base + 0x0014UL + 0x40UL*n))
#define ICU_PSR(n)    *((volatile uint32 *)(PORT_base + 0x0004UL + 0x40UL*n))
#define ICU_P(n)      *((volatile uint16 *)(PORT_base + 0x0000UL + 0x40UL*n))
#define ICU_PKCPROT   *((volatile uint32 *)0xFFD92F40UL)
#define ICU_PWE       *((volatile uint32 *)0xFFD92F44UL)

/* Disable write access to protected registers */
#define ICU_PORT_DISABLE_WRITE_ACCESS_VALUE 0xA5A5A500UL

/* Enable write access to protected registers */
#define ICU_PORT_ENABLE_WRITE_ACCESS_VALUE  0xA5A5A501UL
#define ICU_PWE_ENABLE_WRITE_ACCESS_VALUE   0x05F1FDDDUL

/* Register Definitions for Digital Noise Filter */
#define ICU_DNFAEN_TAUJ2 *((volatile uint16 *)0xffed1604UL)

/* Clock controller registers */
#define PLLE          *((volatile uint32 *)0xFF980000UL) /* PLL Enable Register */
#define PLLS          *((volatile uint32 *)0xFF980004UL) /* PLL Status Register */
#define PLLSTPM       *((volatile uint32 *)0xFF98000CUL) /* PLL Stop Mask Register */
#define MOSCE         *((volatile uint32 *)0xFF988000UL) /* MainOSC Enable Register */
#define MOSCS         *((volatile uint32 *)0xFF988004UL) /* MainOSC Status Register */
#define MOSCSTPM      *((volatile uint32 *)0xFF98800CUL) /* MainOSC Stop Mask Register */
#define HSOSCS        *((volatile uint32 *)0xFF988100UL) /* HSIntOSC Status Register */
#define HSOSCSTPM     *((volatile uint32 *)0xFF988104UL) /* HSIntOSC Stop Mask Register */
#define CKSC_CPUC     *((volatile uint32 *)0xFF980100UL) /* CLK_CPU Selector Control Register */
#define CKSC_CPUS     *((volatile uint32 *)0xFF980108UL) /* CLK_CPU Selector Status Register */
#define CLKKCPROT1    *((volatile uint32 *)0xFF980700UL) /* Clock Controller Register Key Code Protection Register 1 */

#define DISABLE_WRITE_KEY_CODE  (0xA5A5A500UL)
#define ENABLE_WRITE_KEY_CODE   (0xA5A5A501UL)

#define ICU_MSR_TAUJ_AWO  (*(volatile uint32*)0xFF988E20UL)
#define ICU_MSRKCPROT     (*(volatile uint32*)0xFF981710UL)
#define GTM0CMUCLKEN      (*(volatile uint32*)0xff600080UL)
#define ICU_MSR_GTM       (*(volatile uint32*)0xff981020UL)

/* EIC address */
#define ICU_EIC_BASE_INTC2            (0xFFF80000UL)
#define ICU_EIC_INTC2(n)              ((ICU_EIC_BASE_INTC2) + ((n) * 2UL))
#define ICU_EIC_BASE_INTC1_PE0        (0xFFFC4000UL)
#define ICU_EIC_INTC1_PE0(n)          ((ICU_EIC_BASE_INTC1_PE0) + ((n) * 2UL))
#define ICU_EIC_BASE_INTC1_PE1        (0xFFFC8000UL)
#define ICU_EIC_INTC1_PE1(n)          ((ICU_EIC_BASE_INTC1_PE1) + ((n) * 2UL))

/* Protection key codes */
#define ICU_KCPROT_CLR 0xA5A5A500UL
#define ICU_KCPROT_SET 0xA5A5A501UL

/* Enable all modules in this MSR register */
#define ICU_MSR_ACTIVE 0x00000000UL
/* Disable all modules in this MSR register */
#define ICU_MSR_STOP   0xFFFFFFFFUL

/* OS Timer Registers (OSTM0) */
#define EIC360              *((volatile uint16*)0xfff802d0UL)
#define ICU_OSTM0CMP        *((volatile uint32*)0xFFBF0000UL)
#define ICU_OSTM0TS         *((volatile uint8 *)0xFFBF0014UL)
#define ICU_OSTM0TT         *((volatile uint8 *)0xFFBF0018UL)
#define ICU_OSTM0CTL        *((volatile uint8 *)0xFFBF0020UL)
#define MSR_OSTM            *((volatile uint32*)0xFF981180UL)

/*******************************************************************************
**                      Global Function Prototypes                            **
*******************************************************************************/
extern void Port_Init(void);
extern void Mcu_Init(void);
extern void Wdg_Init(void);
extern void Reg_Init(void);
extern void App_Icu_Start_Timer0(void);
#endif /* APP_ICU_DEVICE_SAMPLE_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
