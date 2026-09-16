/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Icu_TAUJ_Irq.h                                                                                      */
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
 * 2.3.1:  31/03/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 and RH850/U2Bx-E MCAL Ver22.00.02 Release
 * 2.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release 
 * 2.1.2:  31/10/2024  : Update SW-VERSION for Ver22.01.02 Beta2 Release 
 *                       As part of support GTM HWIP into common code, following changes are made:
 *                       1.Add precompile condition ICU_TAUJ_UNIT_USED
 * 2.0.1:  25/10/2023  : Update SW-VERSION to 2.0.1
 * 2.0.0:  03/08/2023  : #include "Icu_Mapping.h" update to #include "Icu_MemMap.h" 
 *                       Remove all multi-instance including methods
 *                       Remove all supported multi-instance header file
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
#ifndef ICU_TAUJ_IRQ_H
#define ICU_TAUJ_IRQ_H
/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for interrupt category definitions */
#include "Os.h"

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define ICU_TAUJ_IRQ_AR_RELEASE_MAJOR_VERSION    ICU_AR_RELEASE_MAJOR_VERSION
#define ICU_TAUJ_IRQ_AR_RELEASE_MINOR_VERSION    ICU_AR_RELEASE_MINOR_VERSION
#define ICU_TAUJ_IRQ_AR_RELEASE_REVISION_VERSION ICU_AR_RELEASE_REVISION_VERSION

/* File version information */
#define ICU_TAUJ_IRQ_SW_MAJOR_VERSION            ICU_SW_MAJOR_VERSION
#define ICU_TAUJ_IRQ_SW_MINOR_VERSION            ICU_SW_MINOR_VERSION

/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/
#if (ICU_TAUJ_UNIT_USED == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"

#if (ICU_TAUJ0_CH00_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUJ0_CH00_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) TAUJ0_CH00_ISR(void);
#endif
#endif /* End of ICU_TAUJ0_CH00_ISR_API == STD_ON */

#if (ICU_TAUJ0_CH01_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUJ0_CH01_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) TAUJ0_CH01_ISR(void);
#endif
#endif /* End of ICU_TAUJ0_CH01_ISR_API == STD_ON */

#if (ICU_TAUJ0_CH02_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUJ0_CH02_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) TAUJ0_CH02_ISR(void);
#endif
#endif /* End of ICU_TAUJ0_CH02_ISR_API == STD_ON */

#if (ICU_TAUJ0_CH03_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUJ0_CH03_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) TAUJ0_CH03_ISR(void);
#endif
#endif /* End of ICU_TAUJ0_CH03_ISR_API == STD_ON */

#if (ICU_TAUJ1_CH00_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUJ1_CH00_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) TAUJ1_CH00_ISR(void);
#endif
#endif /* End of ICU_TAUJ1_CH00_ISR_API == STD_ON */

#if (ICU_TAUJ1_CH01_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUJ1_CH01_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) TAUJ1_CH01_ISR(void);
#endif
#endif /* End of ICU_TAUJ1_CH01_ISR_API == STD_ON */

#if (ICU_TAUJ1_CH02_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUJ1_CH02_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) TAUJ1_CH02_ISR(void);
#endif
#endif /* End of ICU_TAUJ1_CH02_ISR_API == STD_ON */

#if (ICU_TAUJ1_CH03_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUJ1_CH03_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) TAUJ1_CH03_ISR(void);
#endif
#endif /* End of ICU_TAUJ1_CH03_ISR_API == STD_ON */

#if (ICU_TAUJ2_CH00_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUJ2_CH00_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) TAUJ2_CH00_ISR(void);
#endif
#endif /* End of ICU_TAUJ2_CH00_ISR_API == STD_ON */

#if (ICU_TAUJ2_CH01_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUJ2_CH01_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) TAUJ2_CH01_ISR(void);
#endif
#endif /* End of ICU_TAUJ2_CH01_ISR_API == STD_ON */

#if (ICU_TAUJ2_CH02_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUJ2_CH02_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) TAUJ2_CH02_ISR(void);
#endif
#endif /* End of ICU_TAUJ2_CH02_ISR_API == STD_ON */

#if (ICU_TAUJ2_CH03_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUJ2_CH03_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) TAUJ2_CH03_ISR(void);
#endif
#endif /* End of ICU_TAUJ2_CH03_ISR_API == STD_ON */

#if (ICU_TAUJ3_CH00_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUJ3_CH00_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) TAUJ3_CH00_ISR(void);
#endif
#endif /* End of ICU_TAUJ3_CH00_ISR_API == STD_ON */

#if (ICU_TAUJ3_CH01_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUJ3_CH01_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) TAUJ3_CH01_ISR(void);
#endif
#endif /* End of ICU_TAUJ3_CH01_ISR_API == STD_ON */

#if (ICU_TAUJ3_CH02_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUJ3_CH02_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) TAUJ3_CH02_ISR(void);
#endif
#endif /* End of ICU_TAUJ3_CH02_ISR_API == STD_ON */

#if (ICU_TAUJ3_CH03_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUJ3_CH03_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) TAUJ3_CH03_ISR(void);
#endif
#endif /* End of ICU_TAUJ3_CH03_ISR_API == STD_ON */

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"
#endif /* #if (ICU_TAUJ_UNIT_USED == STD_ON) */
#endif /* ICU_TAUJ_IRQ_H */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
