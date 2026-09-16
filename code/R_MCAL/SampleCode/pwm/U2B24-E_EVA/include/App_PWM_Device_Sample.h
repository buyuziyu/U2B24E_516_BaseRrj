/*============================================================================*/
/* Project      = RH850/X2x AR4 MCAL Development                              */
/* Module       = App_PWM_Device_Sample.h                                     */
/*                                                                            */
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
/*                                                                            **
 * 2.5.1:  30/06/2025 : Remove SW-VERSION in header comment                   **
 * 2.3.2:  29/04/2025 : Update SW-VERSION for U2Ax Ver22.00.04 Beta Release   **
 * 2.3.1:  31/03/2025 : Update SW-VERSION for U2BxE Ver22.00.02 Beta Release  **
 *                      As part of U2BxE support, following changes are made: **
 *                      1. Add function Guard_Enable_PE, GblSyncCoreFlag      **
 *                      2. Add the define for registers INTC2_EIBD            **
 * 2.3.0:  31/01/2025 : Update SW-VERSION for Ver22.00.06 Beta Release        **
 *                      For GTM support:                                      **
 *                      Add MSR_GTM, PWM_MSR_GTM_OPERATING_VALUE              **
 *                      GTM0CMUCLKEN                                          **
 * 2.2.0:  31/12/2024 : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final **
 *                      Release                                               **
 * 2.1.2:  31/10/2024 : Update SW-VERSION for Ver22.01.02 U2Bx Beta2 Release  **
 * 2.1.1:  23/05/2024 : Initial Version.                                      **
 *                                                                            */
/******************************************************************************/

#ifndef APP_PWM_DEVICE_SAMPLE_H
#define APP_PWM_DEVICE_SAMPLE_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Std_Types.h"

extern void Port_Init(void);
extern void Clock_Init(void);
extern void Mcu_Init(void);
extern void Wdg_Init(void);
extern void Reg_Init(void);
extern void Mcal_Pwm_Init(void);
/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/
/* Module Standby */
#define MSR_TAUD            (*((volatile uint32 *)0xFF981130UL))
#define MSR_TAUJ            (*((volatile uint32 *)0xFF988e20UL))
#define MSR_OSTM            (*((volatile uint32 *)0xFF981180UL))
#define MSR_GTM             (*((volatile uint32 *)0xff981020UL))
#define MSRKCPROT           (*((volatile uint32 *)0xFF981710UL))

/* clock setting */
#define PLLE                (*((volatile uint32 *)0xFF980000UL))                /* PLL Enable Register */
#define PLLS                (*((volatile uint32 *)0xFF980004UL))                /* PLL Status Register */
#define PLLSTPM             (*((volatile uint32 *)0xFF98000CUL))                /* PLL Stop Mask Register */
#define MOSCE               (*((volatile uint32 *)0xFF988000UL))                /* MainOSC Enable Register */
#define MOSCS               (*((volatile uint32 *)0xFF988004UL))                /* MainOSC Status Register */
#define MOSCC               (*((volatile uint32 *)0xFF988008UL))                /* MainOSC Control Register */
#define MOSCSTPM            (*((volatile uint32 *)0xFF98800CUL))                /* MainOSC Stop Mask Register */
#define HSOSCS              (*((volatile uint32 *)0xFF988100UL))                /* HSIntOSC Status Register */
#define HSOSCSTPM           (*((volatile uint32 *)0xFF988104UL))                /* HSIntOSC Stop Mask Register */
#define CKSC_CPUC           (*((volatile uint32 *)0xFF980100UL))                /* CLK_CPU Selector Control Register */
#define CKSC_CPUS           (*((volatile uint32 *)0xFF980108UL))                /* CLK_CPU Selector Status Register */

/* Clock Controller Register Key Code Protection Register 1 */
#define CLKKCPROT1          (*((volatile unsigned long *)0xFF980700UL))
/* Clock Controller Register Key Code Protection Register 2 */
#define CLKKCPROT2          (*((volatile unsigned long *)0xFF980710UL))
/* Clock Controller Register Key Code Protection Register 3 */
#define CLKKCPROT3          (*((volatile unsigned long *)0xFF980720UL))

#define PWM_MSR_TAUD_OPERATING_VALUE      (0x00000000UL) /* TAUD */
#define PWM_MSR_TAUJ_OPERATING_VALUE      (0x00000000UL) /* TAUJ */
#define PWM_MSR_OSTM_OPERATING_VALUE      (0x800003FEUL) /* OSTM0 */
#define PWM_MSR_GTM_OPERATING_VALUE       (0x00000000UL) /* GTM */

#define PWM_PORT_DISABLE_WRITE_ACCESS_VALUE 0xA5A5A500UL
#define PWM_PORT_ENABLE_WRITE_ACCESS_VALUE  0xA5A5A501UL
#define PWM_PWE_ENABLE_WRITE_ACCESS_VALUE   0x003B7FFFUL

/* Protection key codes */
#define DISABLE_WRITE_KEY_CODE            (0xA5A5A500UL)
#define ENABLE_WRITE_KEY_CODE             (0xA5A5A501UL)
#define PWM_EIC_BASE_ADDR                 (0xFFF80000UL)
#define PWM_EIC_PE0_BASE_ADDR             (0xFFFC4000UL)
#define PWM_EIC_ADDR(n)                   ((PWM_EIC_BASE_ADDR) + ((n) * 2UL))
#define PWM_EIC0_ADDR(n)                  ((PWM_EIC_PE0_BASE_ADDR) + ((n) * 2UL))

/* OS Timer Registers (OSTM0) */
#define PWM_OSTM0CMP        (*((volatile uint32 *)0xFFBF0000UL))
#define PWM_OSTM0CNT        (*((volatile uint32 *)0xFFBF0004UL))
#define PWM_OSTM0TE         (*((volatile uint8 *)0xFFBF0010UL))
#define PWM_OSTM0TS         (*((volatile uint8 *)0xFFBF0014UL))
#define PWM_OSTM0TT         (*((volatile uint8 *)0xFFBF0018UL))
#define PWM_OSTM0CTL        (*((volatile uint8 *)0xFFBF0020UL))

/* Register Definitions for configuring ports (Pn): n is the Port group */
#define PORT_base           0xFFD90000UL
#define PWM_PFC(n)          (*((volatile uint16 *)(PORT_base + 0x0018UL + 0x40UL*n)))
#define PWM_PFCE(n)         (*((volatile uint16 *)(PORT_base + 0x001CUL + 0x40UL*n)))
#define PWM_PFCAE(n)        (*((volatile uint16 *)(PORT_base + 0x0028UL + 0x40UL*n)))
#define PWM_PFCEAE(n)       (*((volatile uint16 *)(PORT_base + 0x002CUL + 0x40UL*n)))
#define PWM_PM(n)           (*((volatile uint16 *)(PORT_base + 0x0010UL + 0x40UL*n)))
#define PWM_PMC(n)          (*((volatile uint16 *)(PORT_base + 0x0014UL + 0x40UL*n)))
#define PWM_PSR(n)          (*((volatile uint32 *)(PORT_base + 0x0004UL + 0x40UL*n)))
#define PWM_P(n)            (*((volatile uint16 *)(PORT_base + 0x0000UL + 0x40UL*n)))

/* Clock Controller */
#define PWM_PLLCLKS         (*(volatile uint32*)0xFF703200)
#define PWM_CKSC0C          (*(volatile uint32*)0xFF703100)
#define PWM_CKSC0S          (*(volatile uint32*)0xFF703108)
#define PWM_CLKD0DIV        (*(volatile uint32*)0xFF703000)
#define PWM_CLKD0STAT       (*(volatile uint32*)0xFF703004)
#define PWM_CLKKCPROT0      (*(volatile uint32*)0xFF703700)

//EIDB: EI Level Interrupt Bind Register
#define INTC2_EIBD86        (*((volatile uint32 *)0xfff82158UL)) 
#define INTC2_EIBD87        (*((volatile uint32 *)0xfff8215cUL)) 
#define INTC2_EIBD88        (*((volatile uint32 *)0xfff82160UL)) 
#define INTC2_EIBD89        (*((volatile uint32 *)0xfff82164UL))
#define INTC2_EIBD330       (*((volatile uint32 *)0xfff82528UL)) 
#define INTC2_EIBD331       (*((volatile uint32 *)0xfff8252cUL)) 
#define INTC2_EIBD960       (*((volatile uint32 *)0xfff82f00UL)) 
#define INTC2_EIBD961       (*((volatile uint32 *)0xfff82f04UL)) 

#define TAUD3INTSEL         (*(volatile uint32*)0xFF090830UL)

/* GTM */
#define GTM0CMUCLKEN        (*(volatile uint32*)0xff600080UL)

/* Option for period measurement */
#define USE_FREERUN_TIMER

/*******************************************************************************
**                      Global Function Prototypes                            **
*******************************************************************************/
#ifdef USE_FREERUN_TIMER
/* Function for Starting Free-run Timer */
extern void App_Start_FreeRun_Timer(void);
#endif

extern void App_Pwm_Start_Timer0(void);
extern void App_Pwm_Stop_Timer0(void);
extern void Timer0_Interrupt(void);
extern void Guard_Enable_PE(void);
extern volatile uint8 GblSyncCoreFlag;
#endif /* APP_PWM_DEVICE_SAMPLE_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
