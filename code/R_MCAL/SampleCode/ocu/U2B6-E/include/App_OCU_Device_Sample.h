/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2X MCAL Components                                                                 */
/* Module       = App_OCU_Device_Sample.h                                                                             */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2024,2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Header file information for application.                                                                           */
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
/*              Devices:        X2x                                                                                   */
/*====================================================================================================================*/

/***********************************************************************************************************************
**                                              Revision Control History                                              **
***********************************************************************************************************************/
/*
 * 1.4.1:  30/06/2025    : Add macro INTC2_EIBD(n)
 * 1.4.0:  30/05/2025    : Add definition to testing GTM channel
 * 1.3.1:  31/03/2025    : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 and RH850/U2Bx-E MCAL Ver22.00.02 Release
 * 1.3.0:  30/06/2025    : Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.03 release
 * 1.2.0:  31/12/2024    : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 * 1.0.3:  22/04/2024    : Initial Version.
 *         18/05/2024    : Remove OCU_CHANNEL, OCU_CHANNEL_001 and add GaaListChannel
 */
/**********************************************************************************************************************/
#ifndef APP_OCU_DEVICE_SAMPLE_H
#define APP_OCU_DEVICE_SAMPLE_H

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
#include "Platform_Types.h"
extern void Port_Init(void);
extern void Clock_Init(void);
extern void Mcu_Init(void);
extern void Wdg_Init(void);
extern void Reg_Init(void);
extern void Mcal_Ocu_Init(void);
extern void Guard_Enable_PE(void);
/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/

/* Standby Controller setting */
#define MSR_TAUJ            (*((volatile uint32 *)0xFF988E20UL))
#define MSRKCPROT           (*((volatile uint32 *)0xFF981710UL))
#define CKS_ATAUJC          (*((volatile uint32 *)0xFF988210UL))
/* GTM */
#define MSR_GTM             (*(volatile uint32*)0xff981020UL)
#define GTM0CMUCLKEN        (*(volatile uint32*)0xff600080UL)
#define CMU_GCLK_NUM        (*(volatile uint32*)0xff600084UL)
#define CMU_GCLK_DEN        (*(volatile uint32*)0xff600088UL)
#define INTC2_EIBD961            (*((volatile uint32 *)0xfff82f04UL)) 
#define INTC2_EIBD963            (*((volatile uint32 *)0xfff82f0cUL)) 


/* Register Definitions for configuring ports (Pn) */
#define PORT_base     0xFFD90000UL
#define OCU_PFC(n)    *((volatile uint16 *)(PORT_base + 0x0018UL + 0x40UL*n))
#define OCU_PFCE(n)   *((volatile uint16 *)(PORT_base + 0x001CUL + 0x40UL*n))
#define OCU_PFCAE(n)  *((volatile uint16 *)(PORT_base + 0x0028UL + 0x40UL*n))
#define OCU_PFCEAE(n) *((volatile uint16 *)(PORT_base + 0x002CUL + 0x40UL*n))
#define OCU_PM(n)     *((volatile uint16 *)(PORT_base + 0x0010UL + 0x40UL*n))
#define OCU_PMC(n)    *((volatile uint16 *)(PORT_base + 0x0014UL + 0x40UL*n))
#define OCU_PSR(n)    *((volatile uint32 *)(PORT_base + 0x0004UL + 0x40UL*n))
#define OCU_P(n)      *((volatile uint16 *)(PORT_base + 0x0000UL + 0x40UL*n))

/* clock setting */
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

/* EIC and Macro for open and lock write permission */
#define DISABLE_WRITE_KEY_CODE  (0xA5A5A500UL)
#define ENABLE_WRITE_KEY_CODE   (0xA5A5A501UL)
#define OCU_EIC_BASE_ADDR       (0xFFF80000UL)
#define OCU_EIC_ADDR(n)         ((OCU_EIC_BASE_ADDR) + ((n) * 2UL))
#define INTC2_EIBD(n)           (*((volatile uint32 *)((OCU_EIC_BASE_ADDR) + 0x2000 + ((n) * 4UL))))

/* OS Timer Registers (OSTM0) */
#define OCU_OSTM0CMP        (*((volatile uint32 *)0xFFBF0000UL))
#define OCU_OSTM0TS         (*((volatile uint8 *)0xFFBF0014UL))
#define OCU_OSTM0TT         (*((volatile uint8 *)0xFFBF0018UL))
#define OCU_OSTM0CTL        (*((volatile uint8 *)0xFFBF0020UL))
#define MSR_OSTM            (*((volatile uint32 *)0xFF981180UL))

/* Macro for channel selection */
#define Ocu_OcuChannelConfiguration0 OcuConf_OcuChannel_OcuChannel
#define Ocu_OcuChannelConfiguration1 OcuConf_OcuChannel_OcuChannel_001
#define Ocu_OcuChannelConfiguration2 OcuConf_OcuChannel_OcuChannel_002
#define Ocu_OcuChannelConfiguration3 OcuConf_OcuChannel_OcuChannel_003
#define Ocu_OcuChannelConfiguration4 OcuConf_OcuChannel_OcuChannel_004
#define Ocu_OcuChannelConfiguration5 OcuConf_OcuChannel_OcuChannel_005

/* Array of testing channels*/
extern uint8 GaaListChannel[5];

#define CHANNEL_1 GaaListChannel[0]
#define CHANNEL_2 GaaListChannel[1]
#define CHANNEL_3 GaaListChannel[2]
#define CHANNEL_4 GaaListChannel[3]
#define CHANNEL_5 GaaListChannel[4]

/***********************************************************************************************************************
**                                            Global Function Prototypes                                              **
***********************************************************************************************************************/
/* Schedule period (us) */
extern void App_Ocu_Start_Timer0(uint32 ulPeriod);
extern void App_Ocu_Stop_Timer0(void);
#endif /* APP_OCU_DEVICE_SAMPLE_H */

/***********************************************************************************************************************
**                                                  End of File                                                       **
***********************************************************************************************************************/
