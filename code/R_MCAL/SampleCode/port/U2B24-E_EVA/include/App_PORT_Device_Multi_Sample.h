/*============================================================================*/
/* Project      = RH850/X2x MCAL PF Development                               */
/* Module       = App_PORT_Device_Multi_Sample.h                              */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2024 - 2025 Renesas Electronics Corporation. All rights reserved.      */
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
/*              Devices:        U2B24E                                        */
/*============================================================================*/

/*******************************************************************************
**                      Revision Control History                              **
*******************************************************************************/
/* 2.3.1:  31/03/2025   : Update SW-VERSION for RH850/U2Bx-E MCAL             */
/*                        Ver22.00.02 Release                                 */
/* 2.1.2:  31/10/2024   : Update SW-VERSION 2.1.2 for Ver22.01.02 U2Bx Beta2  */
/* 2.1.1:  29/06/2024   : Initial Version                                     */
/*                                                                            */
/******************************************************************************/

#ifndef APP_PORT_DEVICE_MULTI_SAMPLE_H
#define APP_PORT_DEVICE_MULTI_SAMPLE_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "Port.h"
#include "Port_Device.h"                       /** Users should not include. **/

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/
#define PORT_FAIL                    0
#define PORT_PASS                    1

/* Port Base Address */
#define PORT_BASE       (uint32)0xFFD90000
#define JPORT_BASE      (uint32)0xFFDA0000
#define APORT_BASE      (uint32)0xFFD90C80

#define RANGE_PORT      (uint32)0x40

#define OFFSET_P        (uint32)0x00000000
#define OFFSET_PSR      (uint32)0x00000004
#define OFFSET_PM       (uint32)0x00000010
#define OFFSET_PMC      (uint32)0x00000014
#define OFFSET_PFC      (uint32)0x00000018
#define OFFSET_PFCE     (uint32)0x0000001C
#define OFFSET_PMSR     (uint32)0x00000020
#define OFFSET_PMCSR    (uint32)0x00000024
#define OFFSET_PFCAE    (uint32)0x00000028
#define OFFSET_PFCEAE   (uint32)0x0000002C
#define OFFSET_PINV     (uint32)0x00000030
#define OFFSET_PSFSC    (uint32)0x00006000
#define OFFSET_PSFSD    (uint32)0x00006010
#define OFFSET_PSFSOE   (uint32)0x00006014
#define OFFSET_PIBC     (uint32)0x00004000
#define OFFSET_PBDC     (uint32)0x00004004
#define OFFSET_PIPC     (uint32)0x00004008
#define OFFSET_PU       (uint32)0x0000400C
#define OFFSET_PD       (uint32)0x00004010
#define OFFSET_PODC     (uint32)0x00004014
#define OFFSET_PODCE    (uint32)0x00004038
#define OFFSET_PDSC     (uint32)0x00004018
#define OFFSET_PIS      (uint32)0x0000401C
#define OFFSET_PISA     (uint32)0x00004024
#define OFFSET_PUCC     (uint32)0x00004028

#define PCore0          (uint8)10
#define PCore1          (uint8)2

/* Core 0 */
/* Port group 10: configuration registers */
#define PMC10           (*((volatile uint16 *)(PORT_BASE+RANGE_PORT*PCore0+OFFSET_PMC)))
#define PIPC10          (*((volatile uint16 *)(PORT_BASE+RANGE_PORT*PCore0+OFFSET_PIPC)))
#define PFCEAE10        (*((volatile uint16 *)(PORT_BASE+RANGE_PORT*PCore0+OFFSET_PFCEAE)))
#define PFCAE10         (*((volatile uint16 *)(PORT_BASE+RANGE_PORT*PCore0+OFFSET_PFCAE)))
#define PFCE10          (*((volatile uint16 *)(PORT_BASE+RANGE_PORT*PCore0+OFFSET_PFCE)))
#define PFC10           (*((volatile uint16 *)(PORT_BASE+RANGE_PORT*PCore0+OFFSET_PFC)))
#define PM10            (*((volatile uint16 *)(PORT_BASE+RANGE_PORT*PCore0+OFFSET_PM)))
#define PU10            (*((volatile uint16 *)(PORT_BASE+RANGE_PORT*PCore0+OFFSET_PU)))
#define PD10            (*((volatile uint16 *)(PORT_BASE+RANGE_PORT*PCore0+OFFSET_PD)))
#define PIS10           (*((volatile uint16 *)(PORT_BASE+RANGE_PORT*PCore0+OFFSET_PIS)))
#define PISA10          (*((volatile uint16 *)(PORT_BASE+RANGE_PORT*PCore0+OFFSET_PISA)))
#define PINV10          (*((volatile uint16 *)(PORT_BASE+RANGE_PORT*PCore0+OFFSET_PINV)))
#define PODC10          (*((volatile uint16 *)(PORT_BASE+RANGE_PORT*PCore0+OFFSET_PODC)))
#define PODCE10         (*((volatile uint16 *)(PORT_BASE+RANGE_PORT*PCore0+OFFSET_PODCE)))
#define PDSC10          (*((volatile uint16 *)(PORT_BASE+RANGE_PORT*PCore0+OFFSET_PDSC)))
#define PUCC10          (*((volatile uint16 *)(PORT_BASE+RANGE_PORT*PCore0+OFFSET_PUCC)))
#define P10             (*((volatile uint16 *)(PORT_BASE+RANGE_PORT*PCore0+OFFSET_P)))
#define PIBC10          (*((volatile uint16 *)(PORT_BASE+RANGE_PORT*PCore0+OFFSET_PIBC)))
#define PMSR10          (*((volatile uint32 *)(PORT_BASE+RANGE_PORT*PCore0+OFFSET_PMSR)))
#define PMCSR10         (*((volatile uint32 *)(PORT_BASE+RANGE_PORT*PCore0+OFFSET_PMCSR)))
#define PBDC10          (*((volatile uint32 *)(PORT_BASE+RANGE_PORT*PCore0+OFFSET_PBDC)))

/* Core 1 */
/* Port group 2: configuration registers */
#define PMC2        (*((volatile uint16 *)(PORT_BASE+RANGE_PORT*PCore1+OFFSET_PMC)))
#define PIPC2       (*((volatile uint16 *)(PORT_BASE+RANGE_PORT*PCore1+OFFSET_PIPC)))
#define PFCEAE2     (*((volatile uint16 *)(PORT_BASE+RANGE_PORT*PCore1+OFFSET_PFCEAE)))
#define PFCAE2      (*((volatile uint16 *)(PORT_BASE+RANGE_PORT*PCore1+OFFSET_PFCAE)))
#define PFCE2       (*((volatile uint16 *)(PORT_BASE+RANGE_PORT*PCore1+OFFSET_PFCE)))
#define PFC2        (*((volatile uint16 *)(PORT_BASE+RANGE_PORT*PCore1+OFFSET_PFC)))
#define PM2         (*((volatile uint16 *)(PORT_BASE+RANGE_PORT*PCore1+OFFSET_PM)))
#define PU2         (*((volatile uint16 *)(PORT_BASE+RANGE_PORT*PCore1+OFFSET_PU)))
#define PD2         (*((volatile uint16 *)(PORT_BASE+RANGE_PORT*PCore1+OFFSET_PD)))
#define PIS2        (*((volatile uint16 *)(PORT_BASE+RANGE_PORT*PCore1+OFFSET_PIS)))
#define PISA2       (*((volatile uint16 *)(PORT_BASE+RANGE_PORT*PCore1+OFFSET_PISA)))
#define PINV2       (*((volatile uint16 *)(PORT_BASE+RANGE_PORT*PCore1+OFFSET_PINV)))
#define PODC2       (*((volatile uint16 *)(PORT_BASE+RANGE_PORT*PCore1+OFFSET_PODC)))
#define PODCE2      (*((volatile uint16 *)(PORT_BASE+RANGE_PORT*PCore1+OFFSET_PODCE)))
#define PDSC2       (*((volatile uint16 *)(PORT_BASE+RANGE_PORT*PCore1+OFFSET_PDSC)))
#define PUCC2       (*((volatile uint16 *)(PORT_BASE+RANGE_PORT*PCore1+OFFSET_PUCC)))
#define P2          (*((volatile uint16 *)(PORT_BASE+RANGE_PORT*PCore1+OFFSET_P)))
#define PIBC2       (*((volatile uint16 *)(PORT_BASE+RANGE_PORT*PCore1+OFFSET_PIBC)))
#define PMSR2       (*((volatile uint32 *)(PORT_BASE+RANGE_PORT*PCore1+OFFSET_PMSR)))
#define PMCSR2      (*((volatile uint32 *)(PORT_BASE+RANGE_PORT*PCore1+OFFSET_PMCSR)))
#define PBDC2       (*((volatile uint32 *)(PORT_BASE+RANGE_PORT*PCore1+OFFSET_PBDC)))


#define PKCPROT_REG     (*((volatile uint32 *)(PORT_BASE+0x2F40)))
#define PWE_REG         (*((volatile uint32 *)(PORT_BASE+0x2F44)))

extern volatile uint8 GucStubInitFlag;
extern volatile uint8 GucRefreshPinFlag;
extern volatile uint8 GucStubInitFlag_Variant1;
extern volatile uint8 GucRefreshPinFlag_Variant1;
extern volatile uint8 GucStubInitFlag_Variant2;
extern volatile uint8 GucRefreshPinFlag_Variant2;
/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
extern void sample_end(void);

#endif /* APP_PORT_DEVICE_SAMPLE_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
