/*============================================================================*/
/* Project      = RH850/X2x MCAL PF Development                               */
/* Module       = App_DIO_Device_Sample.h                                     */
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
 * 2.1.2:   06/02/2025  : Initial Version
 */
/******************************************************************************/
#ifndef APP_DIO_DEVICE_SAMPLE_H
#define APP_DIO_DEVICE_SAMPLE_H

/*******************************************************************************
**                     Include Section                                        **
*******************************************************************************/
#include "Dio_Cfg.h"
#include "Det.h"

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/
/* Port Base Address */
#define PORT_BASE            (uint32)0xFFD90000
#define JPORT_BASE           (uint32)0xFFDA0000

/* Port group 02: configuration registers */
#define PSR02            (*((volatile uint32 *)(PORT_BASE + 0x0004 + (2 * 0x40))))
#define PMSR02           (*((volatile uint32 *)(PORT_BASE + 0x0020 + (2 * 0x40))))
#define PMCSR02          (*((volatile uint32 *)(PORT_BASE + 0x0024 + (2 * 0x40))))
#define PIBC02           (*((volatile uint16 *)(PORT_BASE + 0x4000 + (2 * 0x40))))
#define PBDC02           (*((volatile uint16 *)(PORT_BASE + 0x4004 + (2 * 0x40))))
#define PIPC02           (*((volatile uint16 *)(PORT_BASE + 0x4008 + (2 * 0x40))))
#define PWE              (*((volatile uint32 *)(PORT_BASE + 0x2F44)))
#define PKCPROT          (*((volatile uint32 *)(PORT_BASE + 0x2F40)))
/* Port group 10: configuration registers */
#define PSR10            (*((volatile uint32 *)(PORT_BASE + 0x0004 + (10 * 0x40))))
#define PMSR10           (*((volatile uint32 *)(PORT_BASE + 0x0020 + (10 * 0x40))))
#define PMCSR10          (*((volatile uint32 *)(PORT_BASE + 0x0024 + (10 * 0x40))))
#define PIBC10           (*((volatile uint16 *)(PORT_BASE + 0x4000 + (10 * 0x40))))
#define PBDC10           (*((volatile uint16 *)(PORT_BASE + 0x4004 + (10 * 0x40))))
#define PIPC10           (*((volatile uint16 *)(PORT_BASE + 0x4008 + (10 * 0x40))))

/* Port group 22: configuration registers */
#define PSR22            (*((volatile uint32 *)(PORT_BASE + 0x0004 + (22 * 0x40))))
#define PMSR22           (*((volatile uint32 *)(PORT_BASE + 0x0020 + (22 * 0x40))))
#define PMCSR22          (*((volatile uint32 *)(PORT_BASE + 0x0024 + (22 * 0x40))))
#define PIBC22           (*((volatile uint16 *)(PORT_BASE + 0x4000 + (22 * 0x40))))
#define PBDC22           (*((volatile uint16 *)(PORT_BASE + 0x4004 + (22 * 0x40))))
#define PIPC22           (*((volatile uint16 *)(PORT_BASE + 0x4008 + (22 * 0x40))))

/* Port group 20: configuration registers */
#define PSR20            (*((volatile uint32 *)(PORT_BASE + 0x0004 + (20 * 0x40))))
#define PMSR20           (*((volatile uint32 *)(PORT_BASE + 0x0020 + (20 * 0x40))))
#define PMCSR20          (*((volatile uint32 *)(PORT_BASE + 0x0024 + (20 * 0x40))))
#define PIBC20           (*((volatile uint16 *)(PORT_BASE + 0x4000 + (20 * 0x40))))
#define PBDC20           (*((volatile uint16 *)(PORT_BASE + 0x4004 + (20 * 0x40))))
#define PIPC20           (*((volatile uint16 *)(PORT_BASE + 0x4008 + (20 * 0x40))))


/* PE Guard Registers*/
#define PBGERRSLV20                       0xFFDE1000
#define PBGKCPROT(BusGroup)               (*(volatile uint32*)(PBGERRSLV##BusGroup + 0x18))
#define PBG20                             0xFFDE0B00
#define PBG21                             0xFFDE0C00
#define PBGCKPROT1(BusGroup, BusChannel)  (*(volatile uint32*)(PBG##BusGroup + 0x04 + BusChannel*0x08))
/* Value of Key Code Protection Register */
#define DIO_KCPROT_SET    0xA5A5A501UL
#define DIO_KCPROT_CLR    0xA5A5A500UL

extern volatile boolean GblSyncFlag;
/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
extern void sample_end(void);
/* Controller Port(s) Initialization */
extern void Port_Init(void);
/* System Initialization */
extern void Mcu_Init(void);
/* Wathdog Initialization */
extern void Wdg_Init(void);

extern void Guard_Enable_PE(void);

extern void Guard_Init(void);
#endif /* APP_DIO_DEVICE_SAMPLE_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
