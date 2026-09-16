/*============================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                         */
/* Module       = App_MEM_Device_Sample.h                                     */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2025 Renesas Electronics Corporation. All rights reserved.             */
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
/*              Devices:        U2B12-E                                       */
/*============================================================================*/

/*******************************************************************************
**                      Revision Control History                              **
*******************************************************************************/
/*
 * 1.1.1:  30/06/2025  : Update address
 * 1.0.2:  31/03/2025  : Initial Version.
 */
/******************************************************************************/
#ifndef APP_MEM_59_RENESAS_DEVICE_SAMPLE_H
#define APP_MEM_59_RENESAS_DEVICE_SAMPLE_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Mem_59_Renesas.h"
#include "Mem_59_Renesas_Types.h"
#include "Mem_59_Renesas_Ram.h"
#include "Mem_59_Renesas_Cfg.h"
#if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif
#include "SchM_Mem_59_Renesas.h"

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/
/* Define for Common Flash */
#define   MEM_59_RENESAS_SAMPLE_INSTANCE_ID  0
#define   MEM_59_RENESAS_DELAY_TIME        0x000111FFuL
#define   MEM_59_RENESAS_INPUT_OPBT        0x04UL

/* Define for Code Flash */
#define MEM_59_RENESAS_SAMPLE_CF_LEN_16KB            0x4000u
#define MEM_59_RENESAS_SAMPLE_CF_ADDR1               0x00400000ul
#define MEM_59_RENESAS_SAMPLE_CF_WRITE_BURST_SIZE    0x00000200UL
#define MEM_59_RENESAS_SAMPLE_CF_LEN_4KB             0x1000u
#define MEM_59_RENESAS_SAMPLE_CF_READ_LEN            0x00000200UL
/* Define for Data Flash */
#define   MEM_59_RENESAS_SAMPLE_WRITE_BURST_SIZE 0x00000080UL
#define   MEM_59_RENESAS_SAMPLE_LEN_4KB    0x1000u
#define   MEM_59_RENESAS_SAMPLE_LEN_8KB    0x2000u
#define   MEM_59_RENESAS_APP_BUFFER_SIZE   MEM_59_RENESAS_SAMPLE_LEN_8KB
#define   MEM_59_RENESAS_SAMPLE_ADDR1      0xff200000UL
/*******************************************************************************
**                          Defines                                           **
*******************************************************************************/
/* Clock setting */
#define PLLE              (*((volatile unsigned long *)0xFF980000UL)) /* PLL Enable Register */
#define PLLS              (*((volatile unsigned long *)0xFF980004UL)) /* PLL Status Register */
#define PLLSTPM           (*((volatile unsigned long *)0xFF98000CUL)) /* PLL Stop Mask Register */
#define MOSCE             (*((volatile unsigned long *)0xFF988000UL)) /* MainOSC Enable Register */
#define MOSCS             (*((volatile unsigned long *)0xFF988004UL)) /* MainOSC Status Register */
#define MOSCC             (*((volatile unsigned long *)0xFF988008UL)) /* MainOSC Control Register */
#define MOSCSTPM          (*((volatile unsigned long *)0xFF98800CUL)) /* MainOSC Stop Mask Register */
#define MOSCAS            (*((volatile unsigned long *)0xFF988014UL)) /* MainOSC ADET Status Register */
#define MOSCAGC           (*((volatile unsigned long *)0xFF988018UL)) /* MainOSC Auto Gain Control Register */
#define MOSCAGCS          (*((volatile unsigned long *)0xFF98801CUL)) /* MainOSC Auto Gain Control Status Register */
#define HSOSCS            (*((volatile unsigned long *)0xFF988100UL)) /* HSIntOSC Status Register */
#define HSOSCSTPM         (*((volatile unsigned long *)0xFF988104UL)) /* HSIntOSC Stop Mask Register */
#define HSOSCUT           (*((volatile unsigned long *)0xFF988108UL)) /* HSIntOSC User Trimming Register */
#define CKSC_CPUC         (*((volatile unsigned long *)0xFF980100UL)) /* CLK_CPU Selector Control Register */
#define CKSC_CPUS         (*((volatile unsigned long *)0xFF980108UL)) /* CLK_CPU Selector Status Register */
#define CLKD_PLLC         (*((volatile unsigned long *)0xFF980120UL)) /* CLK_PLLO Divider Control Register */
#define CLKD_PLLS         (*((volatile unsigned long *)0xFF980128UL)) /* CLK_PLLO Divider Status Register */
#define CKSC_WDTC         (*((volatile unsigned long *)0xFF980130UL)) /* CLK_WDT Selector Control Register */
#define CKSC_WDTS         (*((volatile unsigned long *)0xFF980138UL)) /* CLK_WDT Selector Status Register */
#define CKSC_RLINC        (*((volatile unsigned long *)0xFF980140UL)) /* CLK_RLIN Selector Control Register */
#define CKSC_RLINS        (*((volatile unsigned long *)0xFF980148UL)) /* CLK_RLIN Selector Status Register */
#define CKSC_RCANC        (*((volatile unsigned long *)0xFF980150UL)) /* CLK_RCANOSC Selector Control Register */
#define CKSC_RCANS        (*((volatile unsigned long *)0xFF980158UL)) /* CLK_RCANOSC Selector Status Register */
#define CKSC_ADCC         (*((volatile unsigned long *)0xFF980160UL)) /* CLK_ADC Selector Control Register */
#define CKSC_ADCS         (*((volatile unsigned long *)0xFF980168UL)) /* CLK_ADC Selector Status Register */
#define CKSC_MSPIC        (*((volatile unsigned long *)0xFF980170UL)) /* CLK_MSPI Selector Control Register */
#define CKSC_MSPIS        (*((volatile unsigned long *)0xFF980178UL)) /* CLK_MSPI Selector Status Register */
#define CKSC_AWDTC        (*((volatile unsigned long *)0xFF988200UL)) /* CLKA_WDT Selector Control Register */
#define CKSC_AWDTS        (*((volatile unsigned long *)0xFF988208UL)) /* CLKA_WDT Selector Status Register */
#define CKSC_ATAUJC       (*((volatile unsigned long *)0xFF988210UL)) /* CLKA_TAUJ Selector Control Register */
#define CKSC_ATAUJS       (*((volatile unsigned long *)0xFF988218UL)) /* CLKA_TAUJ Selector Status Register */
#define CKSC_ARTCAC       (*((volatile unsigned long *)0xFF988220UL)) /* CLKA_RTCA Selector Control Register */
#define CKSC_ARTCAS       (*((volatile unsigned long *)0xFF988228UL)) /* CLKA_RTCA Selector Status Register */
#define CKSC_AADCC        (*((volatile unsigned long *)0xFF988230UL)) /* CLKA_ADC Selector Control Register */
#define CKSC_AADCS        (*((volatile unsigned long *)0xFF988238UL)) /* CLKA_ADC Selector Status Register */
#define CLKD_AADCC        (*((volatile unsigned long *)0xFF988240UL)) /* CLKA_ADC Divider Control Register */
#define CLKD_AADCS        (*((volatile unsigned long *)0xFF988248UL)) /* CLKA_ADC Divider Status Register */
#define CKSC_FOUT0C       (*((volatile unsigned long *)0xFF988250UL)) /* FOUT0 Clock Selector Control Register */
#define CKSC_FOUT0S       (*((volatile unsigned long *)0xFF988258UL)) /* FOUT0 Clock Selector Status Register */
#define CLKD_FOUT0C       (*((volatile unsigned long *)0xFF988260UL)) /* FOUT0 Clock Divider Control Register */
#define CLKD_FOUT0S       (*((volatile unsigned long *)0xFF988268UL)) /* FOUT0 Clock Divider Status Register */
#define CKSC_FOUT1C       (*((volatile unsigned long *)0xFF988270UL)) /* FOUT1 Clock Selector Control Register */
#define CKSC_FOUT1S       (*((volatile unsigned long *)0xFF988278UL)) /* FOUT1 Clock Selector Status Register */
#define CLKD_FOUT1C       (*((volatile unsigned long *)0xFF988280UL)) /* FOUT1 Clock Divider Control Register */
#define CLKD_FOUT1S       (*((volatile unsigned long *)0xFF988288UL)) /* FOUT1 Clock Divider Status Register */

/* Clock Controller Register Key Code Protection Register 1 */
#define CLKKCPROT1        (*((volatile unsigned long *)0xFF980700UL))

/* Clock Controller Register Key Code Protection Register 2 */
#define CLKKCPROT2        (*((volatile unsigned long *)0xFF980710UL))

/* Clock Controller Register Key Code Protection Register 3 */
#define CLKKCPROT3        (*((volatile unsigned long *)0xFF980720UL))

/* Clock controller registers */
#define MEM_59_RENESAS_PLLCLKS       (*(volatile uint32*)0xFF703200)
#define MEM_59_RENESAS_CLKSTAB       0x00000002UL
#define MEM_59_RENESAS_CKSC0C        (*(volatile uint32*)0xFF703100)
#define MEM_59_RENESAS_CKSC0S        (*(volatile uint32*)0xFF703108)
#define MEM_59_RENESAS_CKSC0_PLL     0x00000001UL
#define MEM_59_RENESAS_CLKD0DIV      (*(volatile uint32*)0xFF703000)
#define MEM_59_RENESAS_CLKD0DIV_DIV1 0x00000001UL
#define MEM_59_RENESAS_CLKD0STAT     (*(volatile uint32*)0xFF703004)
#define MEM_59_RENESAS_CLKD0SYNC     0x00000002UL
#define MEM_59_RENESAS_CLKKCPROT0    (*(volatile uint32*)0xFF703700)

/* Protection key codes */
#define MEM_59_RENESAS_KCPROT_CLR    0xA5A5A500UL
#define MEM_59_RENESAS_KCPROT_SET    0xA5A5A501UL

/* Interrupt Vector Setting: Table mode, priority 7 */
#define MEM_59_RENESAS_EIC_PRI       (uint16)0x0007
#define MEM_59_RENESAS_EITB          (uint16)0x0040
#define MEM_59_RENESAS_EIMK          (uint16)0x0080

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#endif /* APP_MEM_59_RENESAS_DEVICE_SAMPLE_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
