/*====================================================================================================================*/
/* Project      = RH850/X2x AR4 MCAL Development                                                                      */
/* Module       = Pwm_TAUD_Irq.h                                                                                      */
/*                                                                                                                    */
/*====================================================================================================================*/
/*                                                       COPYRIGHT                                                    */
/*====================================================================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains ISRs prototypes for TAUD Timers of PWM Driver                                                   */
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
/*                                              Devices:        X2x                                                   */
/*====================================================================================================================*/
/***********************************************************************************************************************
**                                              Revision Control History                                              **
***********************************************************************************************************************/
/*                                                                                                                    **
 * 2.5.1: 30/06/2025 : Remove SW-VERSION in header comment                                                            **
 * 2.5.0: 30/06/2025 : Update SW-VERSION for U2Ax Ver22.01.00(D) Final Release                                        **
 * 2.4.0: 31/05/2025 : Update SW-VERSION for U2Cx Ver21.01.01 Final Release                                           **
 * 2.3.2: 29/04/2025 : Update SW-VERSION for U2Ax Ver22.00.04 Beta Release                                            **
 * 2.3.1: 31/03/2025 : Update SW-VERSION for U2BxE Ver22.00.02 Beta Release                                           **
 * 2.3.0: 28/02/2025 : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release                        **
 * 2.2.0: 31/12/2024 : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release                                  **
 * 2.1.2: 31/10/2024 : Update SW-VERSION for Ver22.01.02 U2Bx, Ver22.00.05 U2Cx Beta2 Release                         **
 * 2.1.1: 30/08/2024 : Update SW-VERSION for Ver22.01.01 U2Bx Beta Release                                            **
 * 2.0.1: 25/10/2023 : Update version in header comment                                                               **
 * 2.0.0: 05/07/2023 : Update from "Pwm_Mapping.h to "Pwm_MemMap.h". Remove #ifdef PWM_INSTANCE_INDEX                 **
 *                     Remove message 0841                                                                            **
 * 1.4.1: 25/02/2022 : Remove redundant header.                                                                       **
 * 1.4.0: 11/11/2021 : Added channel for TAUD3On ( n =0..15).                                                         **
 * 1.3.2: 02/08/2021 : Added the INSTANCE INDEX                                                                       **
 * 1.3.1: 02/07/2021 : Add QAC message 9.5.0                                                                          **
 *                     Format source code to 120 characters                                                           **
 *                     Improve Violation tag (remove START/END)                                                       **
 * 1.2.0: 28/07/2020 : Release                                                                                        **
 * 1.1.1: 16/07/2020 : Changed "TAUDn_CHmm_CAT2_ISR" to                                                               **
 *                               "PWM_ISR_CATEGORY_2 == STD_ON"                                                       **
 * 1.1.0: 19/06/2020 : Release                                                                                        **
 * 1.0.0: 24/03/2020 : Initial Version.                                                                               **
 *                                                                                                                    */
/**********************************************************************************************************************/

#ifndef PWM_TAUD_IRQ_H
#define PWM_TAUD_IRQ_H

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for interrupt category definitions */
#include "Os.h"

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define PWM_TAUD_IRQ_AR_RELEASE_MAJOR_VERSION    PWM_AR_RELEASE_MAJOR_VERSION
#define PWM_TAUD_IRQ_AR_RELEASE_MINOR_VERSION    PWM_AR_RELEASE_MINOR_VERSION
#define PWM_TAUD_IRQ_AR_RELEASE_REVISION_VERSION PWM_AR_RELEASE_REVISION_VERSION

/* Module software version information */
#define PWM_TAUD_IRQ_SW_MAJOR_VERSION            PWM_SW_MAJOR_VERSION
#define PWM_TAUD_IRQ_SW_MINOR_VERSION            PWM_SW_MINOR_VERSION
#define PWM_TAUD_IRQ_SW_PATCH_VERSION            PWM_SW_PATCH_VERSION

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/
/***********************************************************************************************************************
**                                                    QAC Warning                                                     **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/
#define PWM_START_SEC_CODE_FAST
#include "Pwm_MemMap.h"

#if (PWM_TAUD0_CH00_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD0_CH00_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
extern ISR(TAUD0_CH00_CAT2_ISR);
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUD0_CH00_ISR(void);
#endif
#endif /* End of PWM_TAUD0_CH00_ISR_API == STD_ON */

#if (PWM_TAUD0_CH01_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD0_CH01_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
extern ISR(TAUD0_CH01_CAT2_ISR);
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUD0_CH01_ISR(void);
#endif
#endif /* End of PWM_TAUD0_CH01_ISR_API == STD_ON */

#if (PWM_TAUD0_CH02_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD0_CH02_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
extern ISR(TAUD0_CH02_CAT2_ISR);
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUD0_CH02_ISR(void);
#endif
#endif /* End of PWM_TAUD0_CH02_ISR_API == STD_ON */

#if (PWM_TAUD0_CH03_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD0_CH03_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
extern ISR(TAUD0_CH03_CAT2_ISR);
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUD0_CH03_ISR(void);
#endif
#endif /* End of PWM_TAUD0_CH03_ISR_API == STD_ON */

#if (PWM_TAUD0_CH04_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD0_CH04_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
extern ISR(TAUD0_CH04_CAT2_ISR);
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUD0_CH04_ISR(void);
#endif
#endif /* End of PWM_TAUD0_CH04_ISR_API == STD_ON */

#if (PWM_TAUD0_CH05_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD0_CH05_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
extern ISR(TAUD0_CH05_CAT2_ISR);
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUD0_CH05_ISR(void);
#endif
#endif /* End of PWM_TAUD0_CH05_ISR_API == STD_ON */

#if (PWM_TAUD0_CH06_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD0_CH06_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
extern ISR(TAUD0_CH06_CAT2_ISR);
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUD0_CH06_ISR(void);
#endif
#endif /* End of PWM_TAUD0_CH06_ISR_API == STD_ON */

#if (PWM_TAUD0_CH07_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD0_CH07_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
extern ISR(TAUD0_CH07_CAT2_ISR);
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUD0_CH07_ISR(void);
#endif
#endif /* End of PWM_TAUD0_CH07_ISR_API == STD_ON */

#if (PWM_TAUD0_CH08_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD0_CH08_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
extern ISR(TAUD0_CH08_CAT2_ISR);
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUD0_CH08_ISR(void);
#endif
#endif /* End of PWM_TAUD0_CH08_ISR_API == STD_ON */

#if (PWM_TAUD0_CH09_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD0_CH09_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
extern ISR(TAUD0_CH09_CAT2_ISR);
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUD0_CH09_ISR(void);
#endif
#endif /* End of PWM_TAUD0_CH09_ISR_API == STD_ON */

#if (PWM_TAUD0_CH10_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD0_CH10_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
extern ISR(TAUD0_CH10_CAT2_ISR);
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUD0_CH10_ISR(void);
#endif
#endif /* End of PWM_TAUD0_CH10_ISR_API == STD_ON */

#if (PWM_TAUD0_CH11_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD0_CH11_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
extern ISR(TAUD0_CH11_CAT2_ISR);
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUD0_CH11_ISR(void);
#endif
#endif /* End of PWM_TAUD0_CH11_ISR_API == STD_ON */

#if (PWM_TAUD0_CH12_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD0_CH12_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
extern ISR(TAUD0_CH12_CAT2_ISR);
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUD0_CH12_ISR(void);
#endif
#endif /* End of PWM_TAUD0_CH12_ISR_API == STD_ON */

#if (PWM_TAUD0_CH13_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD0_CH13_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
extern ISR(TAUD0_CH13_CAT2_ISR);
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUD0_CH13_ISR(void);
#endif
#endif /* End of PWM_TAUD0_CH13_ISR_API == STD_ON */

#if (PWM_TAUD0_CH14_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD0_CH14_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
extern ISR(TAUD0_CH14_CAT2_ISR);
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUD0_CH14_ISR(void);
#endif
#endif /* End of PWM_TAUD0_CH14_ISR_API == STD_ON */

#if (PWM_TAUD0_CH15_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD0_CH15_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
extern ISR(TAUD0_CH15_CAT2_ISR);
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUD0_CH15_ISR(void);
#endif
#endif /* End of PWM_TAUD0_CH15_ISR_API == STD_ON */

#if (PWM_TAUD1_CH00_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD1_CH00_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
extern ISR(TAUD1_CH00_CAT2_ISR);
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUD1_CH00_ISR(void);
#endif
#endif /* End of PWM_TAUD1_CH00_ISR_API == STD_ON */

#if (PWM_TAUD1_CH01_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD1_CH01_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
extern ISR(TAUD1_CH01_CAT2_ISR);
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUD1_CH01_ISR(void);
#endif
#endif /* End of PWM_TAUD1_CH01_ISR_API == STD_ON */

#if (PWM_TAUD1_CH02_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD1_CH02_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
extern ISR(TAUD1_CH02_CAT2_ISR);
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUD1_CH02_ISR(void);
#endif
#endif /* End of PWM_TAUD1_CH02_ISR_API == STD_ON */

#if (PWM_TAUD1_CH03_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD1_CH03_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
extern ISR(TAUD1_CH03_CAT2_ISR);
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUD1_CH03_ISR(void);
#endif
#endif /* End of PWM_TAUD1_CH03_ISR_API == STD_ON */

#if (PWM_TAUD1_CH04_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD1_CH04_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
extern ISR(TAUD1_CH04_CAT2_ISR);
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUD1_CH04_ISR(void);
#endif
#endif /* End of PWM_TAUD1_CH04_ISR_API == STD_ON */

#if (PWM_TAUD1_CH05_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD1_CH05_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
extern ISR(TAUD1_CH05_CAT2_ISR);
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUD1_CH05_ISR(void);
#endif
#endif /* End of PWM_TAUD1_CH05_ISR_API == STD_ON */

#if (PWM_TAUD1_CH06_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD1_CH06_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
extern ISR(TAUD1_CH06_CAT2_ISR);
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUD1_CH06_ISR(void);
#endif
#endif /* End of PWM_TAUD1_CH06_ISR_API == STD_ON */

#if (PWM_TAUD1_CH07_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD1_CH07_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
extern ISR(TAUD1_CH07_CAT2_ISR);
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUD1_CH07_ISR(void);
#endif
#endif /* End of PWM_TAUD1_CH07_ISR_API == STD_ON */

#if (PWM_TAUD1_CH08_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD1_CH08_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
extern ISR(TAUD1_CH08_CAT2_ISR);
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUD1_CH08_ISR(void);
#endif
#endif /* End of PWM_TAUD1_CH08_ISR_API == STD_ON */

#if (PWM_TAUD1_CH09_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD1_CH09_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
extern ISR(TAUD1_CH09_CAT2_ISR);
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUD1_CH09_ISR(void);
#endif
#endif /* End of PWM_TAUD1_CH09_ISR_API == STD_ON */

#if (PWM_TAUD1_CH10_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD1_CH10_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
extern ISR(TAUD1_CH10_CAT2_ISR);
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUD1_CH10_ISR(void);
#endif
#endif /* End of PWM_TAUD1_CH10_ISR_API == STD_ON */

#if (PWM_TAUD1_CH11_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD1_CH11_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
extern ISR(TAUD1_CH11_CAT2_ISR);
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUD1_CH11_ISR(void);
#endif
#endif /* End of PWM_TAUD1_CH11_ISR_API == STD_ON */

#if (PWM_TAUD1_CH12_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD1_CH12_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
extern ISR(TAUD1_CH12_CAT2_ISR);
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUD1_CH12_ISR(void);
#endif
#endif /* End of PWM_TAUD1_CH12_ISR_API == STD_ON */

#if (PWM_TAUD1_CH13_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD1_CH13_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
extern ISR(TAUD1_CH13_CAT2_ISR);
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUD1_CH13_ISR(void);
#endif
#endif /* End of PWM_TAUD1_CH13_ISR_API == STD_ON */

#if (PWM_TAUD1_CH14_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD1_CH14_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
extern ISR(TAUD1_CH14_CAT2_ISR);
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUD1_CH14_ISR(void);
#endif
#endif /* End of PWM_TAUD1_CH14_ISR_API == STD_ON */

#if (PWM_TAUD1_CH15_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD1_CH15_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
extern ISR(TAUD1_CH15_CAT2_ISR);
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUD1_CH15_ISR(void);
#endif
#endif /* End of PWM_TAUD1_CH15_ISR_API == STD_ON */

#if (PWM_TAUD2_CH00_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD2_CH00_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
extern ISR(TAUD2_CH00_CAT2_ISR);
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUD2_CH00_ISR(void);
#endif
#endif /* End of PWM_TAUD2_CH00_ISR_API == STD_ON */

#if (PWM_TAUD2_CH01_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD2_CH01_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
extern ISR(TAUD2_CH01_CAT2_ISR);
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUD2_CH01_ISR(void);
#endif
#endif /* End of PWM_TAUD2_CH01_ISR_API == STD_ON */

#if (PWM_TAUD2_CH02_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD2_CH02_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
extern ISR(TAUD2_CH02_CAT2_ISR);
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUD2_CH02_ISR(void);
#endif
#endif /* End of PWM_TAUD2_CH02_ISR_API == STD_ON */

#if (PWM_TAUD2_CH03_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD2_CH03_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
extern ISR(TAUD2_CH03_CAT2_ISR);
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUD2_CH03_ISR(void);
#endif
#endif /* End of PWM_TAUD2_CH03_ISR_API == STD_ON */

#if (PWM_TAUD2_CH04_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD2_CH04_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
extern ISR(TAUD2_CH04_CAT2_ISR);
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUD2_CH04_ISR(void);
#endif
#endif /* End of PWM_TAUD2_CH04_ISR_API == STD_ON */

#if (PWM_TAUD2_CH05_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD2_CH05_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
extern ISR(TAUD2_CH05_CAT2_ISR);
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUD2_CH05_ISR(void);
#endif
#endif /* End of PWM_TAUD2_CH05_ISR_API == STD_ON */

#if (PWM_TAUD2_CH06_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD2_CH06_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
extern ISR(TAUD2_CH06_CAT2_ISR);
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUD2_CH06_ISR(void);
#endif
#endif /* End of PWM_TAUD2_CH06_ISR_API == STD_ON */

#if (PWM_TAUD2_CH07_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD2_CH07_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
extern ISR(TAUD2_CH07_CAT2_ISR);
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUD2_CH07_ISR(void);
#endif
#endif /* End of PWM_TAUD2_CH07_ISR_API == STD_ON */

#if (PWM_TAUD2_CH08_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD2_CH08_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
extern ISR(TAUD2_CH08_CAT2_ISR);
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUD2_CH08_ISR(void);
#endif
#endif /* End of PWM_TAUD2_CH08_ISR_API == STD_ON */

#if (PWM_TAUD2_CH09_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD2_CH09_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
extern ISR(TAUD2_CH09_CAT2_ISR);
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUD2_CH09_ISR(void);
#endif
#endif /* End of PWM_TAUD2_CH09_ISR_API == STD_ON */

#if (PWM_TAUD2_CH10_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD2_CH10_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
extern ISR(TAUD2_CH10_CAT2_ISR);
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUD2_CH10_ISR(void);
#endif
#endif /* End of PWM_TAUD2_CH10_ISR_API == STD_ON */

#if (PWM_TAUD2_CH11_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD2_CH11_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
extern ISR(TAUD2_CH11_CAT2_ISR);
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUD2_CH11_ISR(void);
#endif
#endif /* End of PWM_TAUD2_CH11_ISR_API == STD_ON */

#if (PWM_TAUD2_CH12_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD2_CH12_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
extern ISR(TAUD2_CH12_CAT2_ISR);
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUD2_CH12_ISR(void);
#endif
#endif /* End of PWM_TAUD2_CH12_ISR_API == STD_ON */

#if (PWM_TAUD2_CH13_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD2_CH13_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
extern ISR(TAUD2_CH13_CAT2_ISR);
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUD2_CH13_ISR(void);
#endif
#endif /* End of PWM_TAUD2_CH13_ISR_API == STD_ON */

#if (PWM_TAUD2_CH14_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD2_CH14_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
extern ISR(TAUD2_CH14_CAT2_ISR);
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUD2_CH14_ISR(void);
#endif
#endif /* End of PWM_TAUD2_CH14_ISR_API == STD_ON */

#if (PWM_TAUD2_CH15_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD2_CH15_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
extern ISR(TAUD2_CH15_CAT2_ISR);
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUD2_CH15_ISR(void);
#endif
#endif /* End of PWM_TAUD2_CH15_ISR_API == STD_ON */
#if (PWM_TAUD3_CH00_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD3_CH00_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
extern ISR(TAUD3_CH00_CAT2_ISR);
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUD3_CH00_ISR(void);
#endif
#endif /* End of PWM_TAUD3_CH00_ISR_API == STD_ON */

#if (PWM_TAUD3_CH01_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD3_CH01_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
extern ISR(TAUD3_CH01_CAT2_ISR);
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUD3_CH01_ISR(void);
#endif
#endif /* End of PWM_TAUD3_CH01_ISR_API == STD_ON */

#if (PWM_TAUD3_CH02_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD3_CH02_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
extern ISR(TAUD3_CH02_CAT2_ISR);
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUD3_CH02_ISR(void);
#endif
#endif /* End of PWM_TAUD3_CH02_ISR_API == STD_ON */

#if (PWM_TAUD3_CH03_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD3_CH03_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
extern ISR(TAUD3_CH03_CAT2_ISR);
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUD3_CH03_ISR(void);
#endif
#endif /* End of PWM_TAUD3_CH03_ISR_API == STD_ON */

#if (PWM_TAUD3_CH04_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD3_CH04_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
extern ISR(TAUD3_CH04_CAT2_ISR);
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUD3_CH04_ISR(void);
#endif
#endif /* End of PWM_TAUD3_CH04_ISR_API == STD_ON */

#if (PWM_TAUD3_CH05_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD3_CH05_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
extern ISR(TAUD3_CH05_CAT2_ISR);
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUD3_CH05_ISR(void);
#endif
#endif /* End of PWM_TAUD3_CH05_ISR_API == STD_ON */

#if (PWM_TAUD3_CH06_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD3_CH06_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
extern ISR(TAUD3_CH06_CAT2_ISR);
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUD3_CH06_ISR(void);
#endif
#endif /* End of PWM_TAUD3_CH06_ISR_API == STD_ON */

#if (PWM_TAUD3_CH07_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD3_CH07_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
extern ISR(TAUD3_CH07_CAT2_ISR);
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUD3_CH07_ISR(void);
#endif
#endif /* End of PWM_TAUD3_CH07_ISR_API == STD_ON */

#if (PWM_TAUD3_CH08_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD3_CH08_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
extern ISR(TAUD3_CH08_CAT2_ISR);
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUD3_CH08_ISR(void);
#endif
#endif /* End of PWM_TAUD3_CH08_ISR_API == STD_ON */

#if (PWM_TAUD3_CH09_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD3_CH09_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
extern ISR(TAUD3_CH09_CAT2_ISR);
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUD3_CH09_ISR(void);
#endif
#endif /* End of PWM_TAUD3_CH09_ISR_API == STD_ON */

#if (PWM_TAUD3_CH10_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD3_CH10_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
extern ISR(TAUD3_CH10_CAT2_ISR);
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUD3_CH10_ISR(void);
#endif
#endif /* End of PWM_TAUD3_CH10_ISR_API == STD_ON */

#if (PWM_TAUD3_CH11_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD3_CH11_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
extern ISR(TAUD3_CH11_CAT2_ISR);
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUD3_CH11_ISR(void);
#endif
#endif /* End of PWM_TAUD3_CH11_ISR_API == STD_ON */

#if (PWM_TAUD3_CH12_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD3_CH12_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
extern ISR(TAUD3_CH12_CAT2_ISR);
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUD3_CH12_ISR(void);
#endif
#endif /* End of PWM_TAUD3_CH12_ISR_API == STD_ON */

#if (PWM_TAUD3_CH13_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD3_CH13_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
extern ISR(TAUD3_CH13_CAT2_ISR);
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUD3_CH13_ISR(void);
#endif
#endif /* End of PWM_TAUD3_CH13_ISR_API == STD_ON */

#if (PWM_TAUD3_CH14_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD3_CH14_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
extern ISR(TAUD3_CH14_CAT2_ISR);
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUD3_CH14_ISR(void);
#endif
#endif /* End of PWM_TAUD3_CH14_ISR_API == STD_ON */

#if (PWM_TAUD3_CH15_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD3_CH15_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
extern ISR(TAUD3_CH15_CAT2_ISR);
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUD3_CH15_ISR(void);
#endif
#endif /* End of PWM_TAUD3_CH15_ISR_API == STD_ON */

#define PWM_STOP_SEC_CODE_FAST
#include "Pwm_MemMap.h"

#endif /* PWM_TAUD_IRQ_H */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
