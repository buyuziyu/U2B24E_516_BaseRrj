/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Icu_ATU_Irq.h                                                                                       */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.                                                */
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
 * 2.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release 
 * 2.1.2:  31/10/2024  : As part of support GTM HWIP into common code, following changes are made:
 *                       1.Add precompile ICU_ATU_TIMER_UNIT_USED to support code seperation
 * 2.0.1:  25/10/2023  : Update SW-VERSION to 2.0.1
 * 2.0.0:  03/08/2023  : #include "Icu_Mapping.h" update to #include "Icu_MemMap.h" 
 *                       Remove all multi-instance including methods
 *                       Remove all supported multi-instance header file
 * 1.4.1:  15/09/2021  : Add ISR for TimerC 14.
 * 1.3.2:  30/08/2021  : Change from #include "Icu_MemMap.h" to #include "Icu_Mapping.h".
 *                       Update header file macro.
 * 1.3.1:  02/07/2021  : Add QAC message 9.5.0
 *                       Format source code to 120 characters
 *                       Improve Violation tag (remove START/END)
 * 1.2.0:  17/07/2020  : Release
 * 1.1.0:  19/06/2020  : Release
 * 1.0.0:  25/03/2020  : Initial Version
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/

/**********************************************************************************************************************/
#ifndef ICU_ATU_IRQ_H
#define ICU_ATU_IRQ_H
/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for interrupt category definitions */
#include "Os.h"

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define ICU_ATU_IRQ_AR_RELEASE_MAJOR_VERSION    ICU_AR_RELEASE_MAJOR_VERSION
#define ICU_ATU_IRQ_AR_RELEASE_MINOR_VERSION    ICU_AR_RELEASE_MINOR_VERSION
#define ICU_ATU_IRQ_AR_RELEASE_REVISION_VERSION ICU_AR_RELEASE_REVISION_VERSION

/* File version information */
#define ICU_ATU_IRQ_SW_MAJOR_VERSION            ICU_SW_MAJOR_VERSION
#define ICU_ATU_IRQ_SW_MINOR_VERSION            ICU_SW_MINOR_VERSION

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/
#if (ICU_ATU_TIMER_UNIT_USED == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERA0_CH00_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERA0_CH00_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERA0_CH01_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERA0_CH01_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERA0_CH02_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERA0_CH02_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERA0_CH03_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERA0_CH03_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERA0_CH04_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERA0_CH04_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERA0_CH05_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERA0_CH05_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERA0_CH06_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERA0_CH06_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERA0_CH07_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERA0_CH07_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC0_CH00_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC0_CH00_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC0_CH01_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC0_CH01_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC0_CH02_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC0_CH02_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC0_CH03_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC0_CH03_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC1_CH00_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC1_CH00_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC1_CH01_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC1_CH01_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC1_CH02_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC1_CH02_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC1_CH03_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC1_CH03_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC2_CH00_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC2_CH00_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC2_CH01_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC2_CH01_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC2_CH02_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC2_CH02_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC2_CH03_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC2_CH03_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC3_CH00_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC3_CH00_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC3_CH01_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC3_CH01_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC3_CH02_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC3_CH02_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC3_CH03_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC3_CH03_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC4_CH00_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC4_CH00_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC4_CH01_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC4_CH01_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC4_CH02_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC4_CH02_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC4_CH03_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC4_CH03_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC5_CH00_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC5_CH00_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC5_CH01_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC5_CH01_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC5_CH02_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC5_CH02_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC5_CH03_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC5_CH03_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC6_CH00_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC6_CH00_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC6_CH01_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC6_CH01_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC6_CH02_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC6_CH02_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC6_CH03_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC6_CH03_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC7_CH00_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC7_CH00_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC7_CH01_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC7_CH01_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC7_CH02_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC7_CH02_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC7_CH03_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC7_CH03_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC8_CH00_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC8_CH00_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC8_CH01_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC8_CH01_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC8_CH02_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC8_CH02_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC8_CH03_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC8_CH03_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC9_CH00_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC9_CH00_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC9_CH01_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC9_CH01_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC9_CH02_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC9_CH02_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC9_CH03_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC9_CH03_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC10_CH00_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC10_CH00_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC10_CH01_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC10_CH01_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC10_CH02_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC10_CH02_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC10_CH03_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC10_CH03_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC11_CH00_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC11_CH00_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC11_CH01_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC11_CH01_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC11_CH02_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC11_CH02_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC11_CH03_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC11_CH03_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC12_CH00_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC12_CH00_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC12_CH01_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC12_CH01_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC12_CH02_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC12_CH02_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC12_CH03_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC12_CH03_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC13_CH00_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC13_CH00_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC13_CH01_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC13_CH01_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC13_CH02_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC13_CH02_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC13_CH03_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC13_CH03_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC14_CH00_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC14_CH00_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC14_CH01_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC14_CH01_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC14_CH02_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC14_CH02_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC14_CH03_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC14_CH03_ISR(void);
#endif

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"
#endif /* #if (ICU_ATU_TIMER_UNIT_USED == STD_ON) */
#endif /* ICU_ATU_IRQ_H */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
