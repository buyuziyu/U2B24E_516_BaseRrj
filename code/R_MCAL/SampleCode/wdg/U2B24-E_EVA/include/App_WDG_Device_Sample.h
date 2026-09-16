/*============================================================================*/
/* Project      = RH850/X2x MCAL PF Development                               */
/* Module       = App_WDG_Device_Sample.h                                     */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2024-2025 Renesas Electronics Corporation. All rights reserved.        */
/*============================================================================*/
/* Purpose:                                                                   */
/* Sample Application Common header file.                                     */
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
/*              Devices:        U2B24-E_EVA                                   */
/*============================================================================*/

/*******************************************************************************
**                      Revision Control History                              **
*******************************************************************************/
/*
 * 2.4.1:  30/06/2025    : Remove SW-VERSION in file header 
 * 2.3.2:  29/04/2025    : Update SW-VERSION for RH850/Ver22.00.03 U2Bx-E
 * 2.3.1:  31/03/2025    : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 *                         Added PEG & PBG: Function safety register definition
 * 2.3.0:  31/01/2025    : Update SW-VERSION for Ver22.00.06 U2Cx Beta Release
 * 2.2.0:  31/12/2024    : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D
 *                         Final release
 * 2.1.2:  30/10/2024    : Update SW-VERSION to 2.1.2
 * 2.1.1:  31/08/2024    : Update SW-VERSION to 2.1.1
 *                       : Initial Version
 */
/******************************************************************************/
#ifndef APP_WDG_DEVICE_SAMPLE_H
#define APP_WDG_DEVICE_SAMPLE_H
/*******************************************************************************
**                     Include Section                                        **
*******************************************************************************/
/* Include macro of uint16, uint32  */
#include "Std_Types.h"
/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/

#define ENABLE_INTERRUPT()      __asm("ei")

/* EIC of WDG */
#define EIC22_PE0               *((volatile uint16*)0xFFFC402CUL)
#define EIC22_PE1               *((volatile uint16*)0xFFFC802CUL)
#define EIC22_PE2               *((volatile uint16*)0xFFFCC02CUL)
#define EIC22_PE3               *((volatile uint16*)0xFFFD002CUL)
#define EIC22_PE4               *((volatile uint16*)0xFFFD402CUL)
#define EIC22_PE5               *((volatile uint16*)0xFFFD802CUL)
#define EIC22_PE6               *((volatile uint16*)0xFFFDC02CUL)
#define EIC981                  *((volatile uint16*)0xFFF807AAUL)

/* STBC */
#define CKSC_WDTC               (*((volatile uint32*)0xFF988300))
#define CKSC_AWDTC              (*((volatile uint32*)0xFF988200))
#define CLKKCPROT1              (*((volatile uint32*)0xFF980700))
#define WDG_KCPROT_CLR          0xA5A5A500UL
#define WDG_KCPROT_SET          0xA5A5A501UL

#define APP_WDG_RESF            *((volatile uint32*)0xFF988500UL)
#define REG_RESFC               *((volatile uint32*)0xFF980C00UL) 
#define RESF_SRES2F2_POS        0x06

/* Define macro to check variant used */
#define VARIANT_RESET              (*((volatile uint32*)0xFE160000UL))

/* ECM system reset 2 flag */
#define APP_WDG_RESF_BIT_POS    0x6

#define APP_WDG_RST_FLAG_VALUE  0x1
/* WDTBA system reset 2 flag */
#define APP_WDG_RESF_BIT_POS_WDTBA     0x7

/* EI level interrupt bind register for WDTBA (EIC981) */
#define EIBD                           (*((uint32*)0xfff82f54UL))
#define EIBD_PEID_BOUND_PE0_VALUE      (uint32)0xFFFFFFF8UL
/* PBG register*/

#define PBG20                                     0xFFDE0B00UL
#define PBGERRSLV20                               0xFFDE1000UL
#define PBG11H0                                   0xFF8B1400UL
#define PBGERRSLV11H0                             0xFF8B2000UL

#define PBG51                                     0xFFC7A400UL
#define PBG50                                     0xFFC7A300UL
#define PBGERRSLV50                               0xFFC7B000UL
//
//#define PBGKCPROT(PBG_group)                      (*(volatile uint32*)(PBGERRSLV##PBG_group + 0x18UL))
//#define PBGKCPROT0(PBG_group, PBG_channel)        (*(volatile uint32*)(PBG##PBG_group + 0x00UL + PBG_channel*0x08UL))
//#define PBGKCPROT1(PBG_group, PBG_channel)        (*(volatile uint32*)(PBG##PBG_group + 0x04UL + PBG_channel*0x08UL))

#define PBGKCPROT11      (*(volatile uint32*)(PBGERRSLV11H0 + 0x18UL))
#define PBGKCPROT50      (*(volatile uint32*)(PBGERRSLV50 + 0x18UL))
#define PBGKCPROT20      (*(volatile uint32*)(PBGERRSLV20 + 0x18UL))

/* PBGnPROT0_m */
#define PBG11PROT0(m)   (*(volatile uint32*)(PBG11H0 + m * 0x08UL))
#define PBG51PROT0(m)   (*(volatile uint32*)(PBG51 + m * 0x08UL))
#define PBG50PROT0(m)   (*(volatile uint32*)(PBG50 + m * 0x08UL))
#define PBG20PROT0(m)   (*(volatile uint32*)(PBG20 + m * 0x08UL))
/*******************************************************************************
**                  PEG & PBG: Function safety register definition            **
*******************************************************************************/
/* Registers base adrress */
#define GUARD_PE0CL0    0xFFC6C000
#define GUARD_PE1CL0    0xFFC6C100
#define GUARD_PE6CL3    0xFFC6C600
#define PBGERRSLV30     0xFFC73200
#define PBG30           0xFFC72B00
#define PBGERRSLV40     0xFFC75400
#define PBG40           0xFFC75300

/* PBGnPROT0_m */
#define PBG11PROT0(m)   (*(volatile uint32*)(PBG11H0 + m * 0x08UL))
#define PBG51PROT0(m)   (*(volatile uint32*)(PBG51 + m * 0x08UL))
#define PBG50PROT0(m)   (*(volatile uint32*)(PBG50 + m * 0x08UL))
#define PBG20PROT0(m)   (*(volatile uint32*)(PBG20 + m * 0x08UL))

/* PEGKCPROT */
#define PEGKCPROT0      (*(volatile uint32*)GUARD_PE0CL0)
#define PEGKCPROT1      (*(volatile uint32*)GUARD_PE1CL0)
#define PEGKCPROT6      (*(volatile uint32*)GUARD_PE6CL3)

/* PEGPROTm */
#define PEGPROT0(m)     (*(volatile uint32*)(GUARD_PE0CL0 + 0x40UL + m * 0x10UL))
#define PEGPROT1(m)     (*(volatile uint32*)(GUARD_PE1CL0 + 0x40UL + m * 0x10UL))
#define PEGPROT6(m)     (*(volatile uint32*)(GUARD_PE6CL3 + 0x40UL + m * 0x10UL))

/* PEGSPIDm */
#define PEGSPID0(m)     (*(volatile uint32*)(GUARD_PE0CL0 + 0x44UL + m * 0x10UL))
#define PEGSPID1(m)     (*(volatile uint32*)(GUARD_PE1CL0 + 0x44UL + m * 0x10UL))
#define PEGSPID6(m)     (*(volatile uint32*)(GUARD_PE6CL3 + 0x44UL + m * 0x10UL))

/* PBGKCPROTn */
#define PBGKCPROT30      (*(volatile uint32*)(PBGERRSLV30 + 0x18UL))
#define PBGKCPROT40      (*(volatile uint32*)(PBGERRSLV40 + 0x18UL))

/* PBGnPROT0_m */
#define PBG30PROT0(m)   (*(volatile uint32*)(PBG30 + m * 0x08UL))
#define PBG40PROT0(m)   (*(volatile uint32*)(PBG40 + m * 0x08UL))

#if defined(RUN_PE6)
#define INTC1_EIBD22        *(uint32*)(0xFFFDC158UL)
#endif
#define INTC2_EIBD981       *(uint32*)(0xFFF82F54UL)
/*******************************************************************************
**                       Function Prototypes                                  **
*******************************************************************************/

#endif /* APP_WDG_DEVICE_SAMPLE_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
