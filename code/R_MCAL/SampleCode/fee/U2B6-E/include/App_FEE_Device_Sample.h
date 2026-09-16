/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas R22.11 X2x MCAL Components                                                          */
/* Module       = App_FEE_Device_Sample.h                                                                             */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2025 Renesas Electronics Corporation. All rights reserved.                                                     */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains sample application for FEE Component                                                            */
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
/*              Devices:        U2B6-E                                                                                */
/*====================================================================================================================*/

/***********************************************************************************************************************
**                                              Revision Control History                                              **
***********************************************************************************************************************/
/*
 * 1.1.1:  30/06/2025:  Remove SW-VERSION in file header
 * 1.0.2:  31/03/2025:  Initial Version. 
 */
/**********************************************************************************************************************/

#ifndef APP_FEE_DEVICE_SAMPLE_H
#define APP_FEE_DEVICE_SAMPLE_H

/***********************************************************************************************************************
**                                                Include Section                                                     **
***********************************************************************************************************************/
#include "Fee.h" /* Fee header */

/***********************************************************************************************************************
**                                                Global Data                                                         **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Global Data Types                                                   **
***********************************************************************************************************************/

#define HSOSCS            (*((volatile unsigned long *)0xFF988100UL)) /* HSIntOSC Status Register */
#define HSOSCSTPM         (*((volatile unsigned long *)0xFF988104UL)) /* HSIntOSC Stop Mask Register */
/* Clock Controller Register Key Code Protection Register 1 */
#define CLKKCPROT1        (*((volatile unsigned long *)0xFF980700UL))

/* Protection key codes */
#define FEE_KCPROT_CLR    0xA5A5A500UL
#define FEE_KCPROT_SET    0xA5A5A501UL

#define MOSCE             (*((volatile unsigned long *)0xFF988000UL)) /* MainOSC Enable Register */
#define MOSCS             (*((volatile unsigned long *)0xFF988004UL)) /* MainOSC Status Register */
#define MOSCC             (*((volatile unsigned long *)0xFF988008UL)) /* MainOSC Control Register */
#define MOSCSTPM          (*((volatile unsigned long *)0xFF98800CUL)) /* MainOSC Stop Mask Register */
#define PLLE              (*((volatile unsigned long *)0xFF980000UL)) /* PLL Enable Register */
#define PLLS              (*((volatile unsigned long *)0xFF980004UL)) /* PLL Status Register */
#define PLLSTPM           (*((volatile unsigned long *)0xFF98000CUL)) /* PLL Stop Mask Register */
#define CKSC_CPUS         (*((volatile unsigned long *)0xFF980108UL)) /* CLK_CPU Selector Status Register */
#define CKSC_CPUC         (*((volatile unsigned long *)0xFF980100UL)) /* CLK_CPU Selector Control Register */

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/

/* System Initialization */
extern void Mcu_Init(void);

/* Wathdog Initialization */
extern void Wdg_Init(void);

/* Timer Initialization */
extern void Timer_Init(void);

/* Stub all areas before initalazation Fee_Init */
extern void Fee_StubPrepareAreas(void);

#endif /* APP_FEE_DEVICE_SAMPLE_H */

/***********************************************************************************************************************
**                                                End of File                                                         **
***********************************************************************************************************************/
