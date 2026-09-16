/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Adc_Irq.h                                                                                           */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains ISRs prototypes for all Timers of ADC Driver                                                    */
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
 * 2.5.1: 30/06/2025 : Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.03 release
 *                     Remove SW-VERSION in file header
 * 2.5.0: 30/06/2025 : Update SW-VERSION for RH850/Ver22.01.00 (D) U2Ax release
 * 2.4.0: 31/05/2025 : Update SW-VERSION for RH850/Ver21.01.01 U2Cx release
 * 2.3.1: 31/03/2025 : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 * 2.3.1: 28/02/2025 : Update SW-VERSION for Ver22.00.02 U2Ax Beta 1 Release
 * 2.3.0: 28/02/2025 : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0: 31/12/2024 : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 * 2.1.3: 31/10/2024 : Update SW-VERSION 2.1.3
 * 2.1.2: 30/09/2024 : Update SW-VERSION 2.1.2
 * 2.0.0: 28/08/2023 : Removed Multi-Instance define. Change Adc_Mapping.h to Adc_Memmap.h
 * 1.4.1: 24/11/2021 : Added ISRs of SG and ERR for ADCKA.
 *                     Added instance 4 to the suppression of duplicate inclusion.
 * 1.3.2: 06/09/2021 : Update header file macro to call file multiple times.
 * 1.3.1: 07/07/2021 : Changed comment format to 120 columns
 *        07/04/2021 : Changed to comply with coding rules.
 * 1.2.0: 14/07/2020 : Release
 *        27/07/2020 : Add QAC 9.3.1 comment.
 * 1.1.0: 19/06/2020 : Release
 * 1.0.1: 13/04/2020 : Update software version definition.
 * 1.0.0: 09/01/2020 : Initial Version
 */
/**********************************************************************************************************************/
#ifndef ADC_IRQ_H
#define ADC_IRQ_H


/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for interrupt category definitions */
#include "Os.h"

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define ADC_IRQ_AR_RELEASE_MAJOR_VERSION    ADC_AR_RELEASE_MAJOR_VERSION
#define ADC_IRQ_AR_RELEASE_MINOR_VERSION    ADC_AR_RELEASE_MINOR_VERSION
#define ADC_IRQ_AR_RELEASE_REVISION_VERSION ADC_AR_RELEASE_REVISION_VERSION

/* File version information */
#define ADC_IRQ_SW_MAJOR_VERSION            ADC_SW_MAJOR_VERSION
#define ADC_IRQ_SW_MINOR_VERSION            ADC_SW_MINOR_VERSION

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/
#define ADC_START_SEC_CODE_FAST
#include "Adc_MemMap.h"

/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC0_SG0_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC0_SG0_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC0_SG1_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC0_SG1_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC0_SG2_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC0_SG2_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC0_SG3_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC0_SG3_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC0_SG4_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC0_SG4_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC0_ERR_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC0_ERR_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC1_SG0_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC1_SG0_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC1_SG1_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC1_SG1_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC1_SG2_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC1_SG2_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC1_SG3_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC1_SG3_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC1_SG4_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC1_SG4_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC1_ERR_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC1_ERR_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC2_SG0_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC2_SG0_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC2_SG1_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC2_SG1_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC2_SG2_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC2_SG2_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC2_SG3_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC2_SG3_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC2_SG4_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC2_SG4_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC2_ERR_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC2_ERR_ISR(void);
#endif

#if ((ADC_IP_ADCH == STD_ON) || (ADC_IP_ADCK == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC3_SG0_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC3_SG0_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC3_SG1_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC3_SG1_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC3_SG2_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC3_SG2_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC3_SG3_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC3_SG3_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC3_SG4_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC3_SG4_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC3_ERR_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC3_ERR_ISR(void);
#endif
#endif /* ((ADC_IP_ADCH == STD_ON) || (ADC_IP_ADCK == STD_ON)) */

#if (ADC_IP_ADCK == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADCA_SG0_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADCA_SG0_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADCA_SG1_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADCA_SG1_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADCA_SG2_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADCA_SG2_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADCA_SG3_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADCA_SG3_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADCA_SG4_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADCA_SG4_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADCA_ERR_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADCA_ERR_ISR(void);
#endif
#endif /* (ADC_IP_ADCK == STD_ON) */

/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC_DMA0_CH00_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC_DMA0_CH00_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC_DMA0_CH01_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC_DMA0_CH01_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC_DMA0_CH02_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC_DMA0_CH02_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC_DMA0_CH03_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC_DMA0_CH03_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC_DMA0_CH04_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC_DMA0_CH04_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC_DMA0_CH05_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC_DMA0_CH05_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC_DMA0_CH06_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC_DMA0_CH06_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC_DMA0_CH07_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC_DMA0_CH07_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC_DMA0_CH08_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC_DMA0_CH08_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC_DMA0_CH09_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC_DMA0_CH09_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC_DMA0_CH10_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC_DMA0_CH10_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC_DMA0_CH11_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC_DMA0_CH11_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC_DMA0_CH12_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC_DMA0_CH12_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC_DMA0_CH13_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC_DMA0_CH13_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC_DMA0_CH14_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC_DMA0_CH14_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC_DMA0_CH15_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC_DMA0_CH15_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC_DMA1_CH00_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC_DMA1_CH00_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC_DMA1_CH01_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC_DMA1_CH01_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC_DMA1_CH02_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC_DMA1_CH02_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC_DMA1_CH03_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC_DMA1_CH03_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC_DMA1_CH04_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC_DMA1_CH04_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC_DMA1_CH05_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC_DMA1_CH05_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC_DMA1_CH06_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC_DMA1_CH06_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC_DMA1_CH07_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC_DMA1_CH07_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC_DMA1_CH08_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC_DMA1_CH08_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC_DMA1_CH09_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC_DMA1_CH09_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC_DMA1_CH10_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC_DMA1_CH10_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC_DMA1_CH11_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC_DMA1_CH11_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC_DMA1_CH12_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC_DMA1_CH12_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC_DMA1_CH13_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC_DMA1_CH13_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC_DMA1_CH14_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC_DMA1_CH14_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC_DMA1_CH15_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC_DMA1_CH15_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC_PARITY_ERR_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC_PARITY_ERR_ISR(void);
#endif

#define ADC_STOP_SEC_CODE_FAST
#include "Adc_MemMap.h"

#endif /* ADC_IRQ_H */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
