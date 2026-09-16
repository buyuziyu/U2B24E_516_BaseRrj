/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Icu_GTM_Irq.h                                                                                       */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2024-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains ISRs prototypes for all Timers of ICU Driver                                                    */
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
 * 2.4.1:  30/06/2025  : Remove SW-VERSION in file header
 * 2.4.0:  30/05/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.01 Release
 * 2.3.1:  31/03/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 and RH850/U2Bx-E MCAL Ver22.00.02 Release
 * 2.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release 
 * 2.1.2:  31/10/2024  : Initial version
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
#ifndef ICU_GTM_IRQ_H
#define ICU_GTM_IRQ_H

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for interrupt category definitions */
#include "Os.h"

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
#if (ICU_GTM_TIMER_UNIT_USED == STD_ON)
/* AUTOSAR release version information */
#define ICU_GTM_IRQ_AR_RELEASE_MAJOR_VERSION    ICU_AR_RELEASE_MAJOR_VERSION
#define ICU_GTM_IRQ_AR_RELEASE_MINOR_VERSION    ICU_AR_RELEASE_MINOR_VERSION
#define ICU_GTM_IRQ_AR_RELEASE_REVISION_VERSION ICU_AR_RELEASE_REVISION_VERSION

/* File version information */
#define ICU_GTM_IRQ_SW_MAJOR_VERSION            ICU_SW_MAJOR_VERSION
#define ICU_GTM_IRQ_SW_MINOR_VERSION            ICU_SW_MINOR_VERSION

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"

#if (ICU_GTM_TIM0_CH0_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM0_CH0_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM0_CH0_ISR(void);
#endif
#endif

#if (ICU_GTM_TIM0_CH1_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM0_CH1_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM0_CH1_ISR(void);
#endif
#endif

#if (ICU_GTM_TIM0_CH2_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM0_CH2_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM0_CH2_ISR(void);
#endif
#endif

#if (ICU_GTM_TIM0_CH3_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM0_CH3_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM0_CH3_ISR(void);
#endif
#endif

#if (ICU_GTM_TIM0_CH4_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM0_CH4_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM0_CH4_ISR(void);
#endif
#endif

#if (ICU_GTM_TIM0_CH5_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM0_CH5_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM0_CH5_ISR(void);
#endif
#endif

#if (ICU_GTM_TIM0_CH6_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM0_CH6_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM0_CH6_ISR(void);
#endif
#endif

#if (ICU_GTM_TIM0_CH7_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM0_CH7_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM0_CH7_ISR(void);
#endif
#endif

#if (ICU_GTM_TIM1_CH0_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM1_CH0_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM1_CH0_ISR(void);
#endif
#endif

#if (ICU_GTM_TIM1_CH1_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM1_CH1_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM1_CH1_ISR(void);
#endif
#endif

#if (ICU_GTM_TIM1_CH2_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM1_CH2_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM1_CH2_ISR(void);
#endif
#endif

#if (ICU_GTM_TIM1_CH3_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM1_CH3_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM1_CH3_ISR(void);
#endif
#endif

#if (ICU_GTM_TIM1_CH4_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM1_CH4_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM1_CH4_ISR(void);
#endif
#endif

#if (ICU_GTM_TIM1_CH5_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM1_CH5_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM1_CH5_ISR(void);
#endif
#endif

#if (ICU_GTM_TIM1_CH6_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM1_CH6_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM1_CH6_ISR(void);
#endif
#endif

#if (ICU_GTM_TIM1_CH7_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM1_CH7_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM1_CH7_ISR(void);
#endif
#endif

#if (ICU_GTM_TIM2_CH0_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM2_CH0_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM2_CH0_ISR(void);
#endif
#endif

#if (ICU_GTM_TIM2_CH1_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM2_CH1_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM2_CH1_ISR(void);
#endif
#endif

#if (ICU_GTM_TIM2_CH2_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM2_CH2_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM2_CH2_ISR(void);
#endif
#endif

#if (ICU_GTM_TIM2_CH3_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM2_CH3_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM2_CH3_ISR(void);
#endif
#endif

#if (ICU_GTM_TIM2_CH4_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM2_CH4_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM2_CH4_ISR(void);
#endif
#endif

#if (ICU_GTM_TIM2_CH5_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM2_CH5_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM2_CH5_ISR(void);
#endif
#endif

#if (ICU_GTM_TIM2_CH6_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM2_CH6_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM2_CH6_ISR(void);
#endif
#endif

#if (ICU_GTM_TIM2_CH7_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM2_CH7_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM2_CH7_ISR(void);
#endif
#endif

#if (ICU_GTM_TIM3_CH0_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM3_CH0_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM3_CH0_ISR(void);
#endif
#endif

#if (ICU_GTM_TIM3_CH1_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM3_CH1_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM3_CH1_ISR(void);
#endif
#endif

#if (ICU_GTM_TIM3_CH2_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM3_CH2_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM3_CH2_ISR(void);
#endif
#endif

#if (ICU_GTM_TIM3_CH3_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM3_CH3_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM3_CH3_ISR(void);
#endif
#endif

#if (ICU_GTM_TIM3_CH4_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM3_CH4_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM3_CH4_ISR(void);
#endif
#endif

#if (ICU_GTM_TIM3_CH5_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM3_CH5_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM3_CH5_ISR(void);
#endif
#endif

#if (ICU_GTM_TIM3_CH6_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM3_CH6_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM3_CH6_ISR(void);
#endif
#endif

#if (ICU_GTM_TIM3_CH7_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM3_CH7_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM3_CH7_ISR(void);
#endif
#endif

#if (ICU_GTM_TIM4_CH0_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM4_CH0_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM4_CH0_ISR(void);
#endif
#endif

#if (ICU_GTM_TIM4_CH1_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM4_CH1_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM4_CH1_ISR(void);
#endif
#endif

#if (ICU_GTM_TIM4_CH2_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM4_CH2_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM4_CH2_ISR(void);
#endif
#endif

#if (ICU_GTM_TIM4_CH3_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM4_CH3_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM4_CH3_ISR(void);
#endif
#endif

#if (ICU_GTM_TIM4_CH4_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM4_CH4_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM4_CH4_ISR(void);
#endif
#endif

#if (ICU_GTM_TIM4_CH5_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM4_CH5_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM4_CH5_ISR(void);
#endif
#endif

#if (ICU_GTM_TIM4_CH6_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM4_CH6_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM4_CH6_ISR(void);
#endif
#endif

#if (ICU_GTM_TIM4_CH7_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM4_CH7_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM4_CH7_ISR(void);
#endif
#endif

#if (ICU_GTM_TIM5_CH0_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM5_CH0_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM5_CH0_ISR(void);
#endif
#endif

#if (ICU_GTM_TIM5_CH1_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM5_CH1_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM5_CH1_ISR(void);
#endif
#endif

#if (ICU_GTM_TIM5_CH2_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM5_CH2_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM5_CH2_ISR(void);
#endif
#endif

#if (ICU_GTM_TIM5_CH3_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM5_CH3_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM5_CH3_ISR(void);
#endif
#endif

#if (ICU_GTM_TIM5_CH4_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM5_CH4_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM5_CH4_ISR(void);
#endif
#endif

#if (ICU_GTM_TIM5_CH5_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM5_CH5_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM5_CH5_ISR(void);
#endif
#endif

#if (ICU_GTM_TIM5_CH6_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM5_CH6_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM5_CH6_ISR(void);
#endif
#endif

#if (ICU_GTM_TIM5_CH7_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM5_CH7_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM5_CH7_ISR(void);
#endif
#endif

#if (ICU_GTM_TIM6_CH0_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM6_CH0_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM6_CH0_ISR(void);
#endif
#endif

#if (ICU_GTM_TIM6_CH1_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM6_CH1_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM6_CH1_ISR(void);
#endif
#endif

#if (ICU_GTM_TIM6_CH2_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM6_CH2_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM6_CH2_ISR(void);
#endif
#endif

#if (ICU_GTM_TIM6_CH3_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM6_CH3_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM6_CH3_ISR(void);
#endif
#endif

#if (ICU_GTM_TIM6_CH4_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM6_CH4_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM6_CH4_ISR(void);
#endif
#endif

#if (ICU_GTM_TIM6_CH5_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM6_CH5_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM6_CH5_ISR(void);
#endif
#endif

#if (ICU_GTM_TIM6_CH6_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM6_CH6_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM6_CH6_ISR(void);
#endif
#endif

#if (ICU_GTM_TIM6_CH7_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM6_CH7_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM6_CH7_ISR(void);
#endif
#endif

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"
#endif
#endif /* ICU_IRQ_H */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
