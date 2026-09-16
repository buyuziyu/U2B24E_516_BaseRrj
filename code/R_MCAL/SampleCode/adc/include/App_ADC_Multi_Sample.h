/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = App_ADC_Multi_Sample.h                                                                              */
/*====================================================================================================================*/
/*                                  COPYRIGHT                                                                         */
/*====================================================================================================================*/
/* (c) 2019-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains sample application for ADC Driver Component                                                     */
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
**                                                 Revision Control History                                           **
***********************************************************************************************************************/
/*
 * 2.5.1:  30/06/2025    : Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.03 release
 *                         Remove SW-VERSION in file header
 * 2.5.0:  30/06/2025    : Update SW-VERSION for RH850/Ver22.01.00 (D) U2Ax release
 * 2.3.1:  28/02/2025    : Update SW-VERSION for Ver22.00.02 U2Ax Beta 1 Release
 * 2.3.0:  28/02/2025    : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024    : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 * 2.1.3:  31/10/2024    : Update SW-VERSION 2.1.3
 * 2.1.2:  30/09/2024    : As part of Multi-core support, following changes are made:
 *                         1.Remove function Adc_DeInit_MCAL()
 * 1.4.3:  27/05/2022    : Modify the format to 120 characters.
 * 1.2.0:  14/07/2020    : Release
 * 1.1.0:  19/06/2020    : Release
 * 1.0.0:  11/03/2019    : Initial Version
 */
/**********************************************************************************************************************/
#ifndef APP_ADC_MULTI_SAMPLE_H
#define APP_ADC_MULTI_SAMPLE_H

/***********************************************************************************************************************
**                      Include Section                                                                               **
***********************************************************************************************************************/
#include "Std_Types.h"
#include "Adc.h"
#include "Adc_Kernel.h"
/***********************************************************************************************************************
**                      Global Symbols                                                                                **
***********************************************************************************************************************/
/* The register for inter core exclucive control */
/* For ADCH */
#define G0MEV1                                *((volatile uint32*)0xFFFBA004UL)
#define G0MEV2                                *((volatile uint32*)0xFFFBA008UL)
#define G0MEV3                                *((volatile uint32*)0xFFFBA00CUL)
#define G0MEV4                                *((volatile uint32*)0xFFFBA010UL)

/* For ADCJ */
#define BR0INIT                  *(volatile uint8*)(0xFFFB8000UL)
/*Barrier-Synchronization n Barrier Participating PE setting Register*/
#define BR0EN                    *(volatile uint8*)(0xFFFB8004UL)
/*Barrier-Synchronization n - barrier synchronization completion self-register*/
#define BR0SYNCS                 *(volatile uint8*)(0xFFFB8114UL)
/*arrier-Synchronization n Barrier Check Register m*/
#define BR0CHK0                  *(volatile uint8*)(0xFFFB8800UL)
#define BR0CHK1                  *(volatile uint8*)(0xFFFB8900UL)
/*Barrier-Synchronization n Barrier Synchronization Completion Register m*/
#define BR0SYNC0                 *(volatile uint8*)(0xFFFB8804UL)
#define BR0SYNC1                 *(volatile uint8*)(0xFFFB8904UL)

/* Exclusive Items */
#define ADC_INIT_EXCLUSIVE       G0MEV1 /* ADC Initializing */
#define ADC_DEINIT_EXCLUSIVE     G0MEV2 /* ADC De-Initializing */
#define ADC_PE0_RUN              G0MEV3 /* ADC Instance 0 runing on PE0 */
#define ADC_PE1_RUN              G0MEV4 /* ADC Instance 1 runing on PE1 */

/* Macro to set PE0 and PE1 to participate to synchronization */
#define ADC_PARTICIPATE_SYNC_PE0_PE1          0x03UL
/* Macro to clear BR0CHK0 to 3 and BR0SYNC0 to 3 */
#define ADC_SYNC_CLEAR                        0x01UL
#define BR0EN_CLEAR                           0x00UL
#define ADC_SYNC_ENABLE                       0x01UL
#define ADC_SYNC_COMPLETE                     0x01UL
/* Exclusive Status */
#define ADC_GETTING                           0xAAAAAAAAUL
#define ADC_RELEASE                           0x00000000UL

/* Bounding register for select interrupt table */
/* PE 0 */
#define BOUND_PE0      0xFFFFFFF8UL

/* PE 1 */
#define BOUND_PE1      0x00000001UL

#define ADC_COUNTBYTE_INIT            0

/* DMA DMAjOR registers */
#define ADC_DMA0OR        *(volatile uint16*)0xfff90060UL
#define ADC_DMA1OR        *(volatile uint16*)0xfff98060UL
#define ADC_DME_ENABLE    0x0001

/* Global flag for sync information between cores */
extern volatile boolean GblSyncFlag;

/***********************************************************************************************************************
**                      Global Function Prototypes                                                                    **
***********************************************************************************************************************/
extern Std_ReturnType Adc_Init_MCAL(void);
extern void Adc_Set_TableReference(void);
extern void Adc_Set_EI_Bind(void);
extern void Adc_DMA_DME_Enable(void);
extern void Start_Timer0(void);


extern void Adc_Start_OSTM(void);
extern void Adc_Stop_OSTM(void);

/* Trap CPU at the end of application */
extern void sample_end(void);

/* Check the Slave requested or not */
extern boolean CheckSlaveRequest(uint8 GroupIndex, uint8 ApiID);
#endif /* End of APP_ADC_MULTI_SAMPLE_H */
/***********************************************************************************************************************
**                      End of File                                                                                   **
***********************************************************************************************************************/
