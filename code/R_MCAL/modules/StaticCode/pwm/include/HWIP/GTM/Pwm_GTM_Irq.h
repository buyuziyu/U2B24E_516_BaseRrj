/*====================================================================================================================*/
/* Project      = RH850/X2x AR4 MCAL Development                                                                      */
/* Module       = Pwm_GTM_Irq.h                                                                                       */
/*                                                                                                                    */
/*====================================================================================================================*/
/*                                                       COPYRIGHT                                                    */
/*====================================================================================================================*/
/* (c) 2024,2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* API function implementations of PWM  Driver                                                                        */
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
 * 2.3.2: 29/04/2025 : As part of GTM support, following changes are made                                             **
 *                     1. Update ATOM ISR, TOM ISR for GTM                                                            **
 * 2.3.1: 31/03/2025 : Update SW-VERSION for U2BxE Ver22.00.02 Beta Release                                           **
 * 2.3.0: 28/02/2025 : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release                        **
 * 2.2.0: 31/12/2024 : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release                                  **
 * 2.1.2: 31/10/2024 : Initial Version.                                                                               **
 *                                                                                                                    */
/**********************************************************************************************************************/

#ifndef PWM_GTM_IRQ_H
#define PWM_GTM_IRQ_H

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for interrupt category definitions */
#include "Os.h"
#include "Pwm_Cfg.h"
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define PWM_GTM_AR_RELEASE_MAJOR_VERSION    PWM_AR_RELEASE_MAJOR_VERSION
#define PWM_GTM_AR_RELEASE_MINOR_VERSION    PWM_AR_RELEASE_MINOR_VERSION
#define PWM_GTM_AR_RELEASE_REVISION_VERSION PWM_AR_RELEASE_REVISION_VERSION

/* Module software version information */
#define PWM_GTM_SW_MAJOR_VERSION            PWM_SW_MAJOR_VERSION
#define PWM_GTM_SW_MINOR_VERSION            PWM_SW_MINOR_VERSION
#define PWM_GTM_SW_PATCH_VERSION            PWM_SW_PATCH_VERSION

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/

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
#if (PWM_GTM_UNIT_USED == STD_ON)
#define PWM_START_SEC_CODE_FAST
#include "Pwm_MemMap.h"

#if ((PWM_ATOM0_CH00_ISR_API == STD_ON) || (PWM_ATOM0_CH01_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM0_IRQ0_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_ATOM0_IRQ0_ISR(void);
#endif
#endif


#if ((PWM_ATOM0_CH02_ISR_API == STD_ON) || (PWM_ATOM0_CH03_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM0_IRQ1_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_ATOM0_IRQ1_ISR(void);
#endif
#endif


#if ((PWM_ATOM0_CH04_ISR_API == STD_ON) || (PWM_ATOM0_CH05_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM0_IRQ2_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_ATOM0_IRQ2_ISR(void);
#endif
#endif


#if ((PWM_ATOM0_CH06_ISR_API == STD_ON) || (PWM_ATOM0_CH07_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM0_IRQ3_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_ATOM0_IRQ3_ISR(void);
#endif
#endif

#if ((PWM_ATOM1_CH00_ISR_API == STD_ON) || (PWM_ATOM1_CH01_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM1_IRQ0_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_ATOM1_IRQ0_ISR(void);
#endif
#endif


#if ((PWM_ATOM1_CH02_ISR_API == STD_ON) || (PWM_ATOM1_CH03_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM1_IRQ1_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_ATOM1_IRQ1_ISR(void);
#endif
#endif


#if ((PWM_ATOM1_CH04_ISR_API == STD_ON) || (PWM_ATOM1_CH05_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM1_IRQ2_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_ATOM1_IRQ2_ISR(void);
#endif
#endif


#if ((PWM_ATOM1_CH06_ISR_API == STD_ON) || (PWM_ATOM1_CH07_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM1_IRQ3_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_ATOM1_IRQ3_ISR(void);
#endif
#endif


#if ((PWM_ATOM2_CH00_ISR_API == STD_ON) || (PWM_ATOM2_CH01_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM2_IRQ0_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_ATOM2_IRQ0_ISR(void);
#endif
#endif


#if ((PWM_ATOM2_CH02_ISR_API == STD_ON) || (PWM_ATOM2_CH03_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM2_IRQ1_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_ATOM2_IRQ1_ISR(void);
#endif
#endif


#if ((PWM_ATOM2_CH04_ISR_API == STD_ON) || (PWM_ATOM2_CH05_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM2_IRQ2_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_ATOM2_IRQ2_ISR(void);
#endif
#endif


#if ((PWM_ATOM2_CH06_ISR_API == STD_ON) || (PWM_ATOM2_CH07_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM2_IRQ3_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_ATOM2_IRQ3_ISR(void);
#endif
#endif

#if ((PWM_ATOM3_CH00_ISR_API == STD_ON) || (PWM_ATOM3_CH01_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM3_IRQ0_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_ATOM3_IRQ0_ISR(void);
#endif
#endif

#if ((PWM_ATOM3_CH02_ISR_API == STD_ON) || (PWM_ATOM3_CH03_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM3_IRQ1_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_ATOM3_IRQ1_ISR(void);
#endif
#endif

#if ((PWM_ATOM3_CH04_ISR_API == STD_ON) || (PWM_ATOM3_CH05_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM3_IRQ2_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_ATOM3_IRQ2_ISR(void);
#endif
#endif


#if ((PWM_ATOM3_CH06_ISR_API == STD_ON) || (PWM_ATOM3_CH07_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM3_IRQ3_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_ATOM3_IRQ3_ISR(void);
#endif
#endif


#if ((PWM_ATOM4_CH00_ISR_API == STD_ON) || (PWM_ATOM4_CH01_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM4_IRQ0_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_ATOM4_IRQ0_ISR(void);
#endif
#endif


#if ((PWM_ATOM4_CH02_ISR_API == STD_ON) || (PWM_ATOM4_CH03_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM4_IRQ1_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_ATOM4_IRQ1_ISR(void);
#endif
#endif


#if ((PWM_ATOM4_CH04_ISR_API == STD_ON) || (PWM_ATOM4_CH05_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM4_IRQ2_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_ATOM4_IRQ2_ISR(void);
#endif
#endif


#if ((PWM_ATOM4_CH06_ISR_API == STD_ON) || (PWM_ATOM4_CH07_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM4_IRQ3_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_ATOM4_IRQ3_ISR(void);
#endif
#endif


#if ((PWM_ATOM5_CH00_ISR_API == STD_ON) || (PWM_ATOM5_CH01_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM5_IRQ0_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_ATOM5_IRQ0_ISR(void);
#endif
#endif


#if ((PWM_ATOM5_CH02_ISR_API == STD_ON) || (PWM_ATOM5_CH03_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM5_IRQ1_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_ATOM5_IRQ1_ISR(void);
#endif
#endif


#if ((PWM_ATOM5_CH04_ISR_API == STD_ON) || (PWM_ATOM5_CH05_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM5_IRQ2_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_ATOM5_IRQ2_ISR(void);
#endif
#endif


#if ((PWM_ATOM5_CH06_ISR_API == STD_ON) || (PWM_ATOM5_CH07_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM5_IRQ3_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_ATOM5_IRQ3_ISR(void);
#endif
#endif


#if ((PWM_ATOM6_CH00_ISR_API == STD_ON) || (PWM_ATOM6_CH01_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM6_IRQ0_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_ATOM6_IRQ0_ISR(void);
#endif
#endif


#if ((PWM_ATOM6_CH02_ISR_API == STD_ON) || (PWM_ATOM6_CH03_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM6_IRQ1_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_ATOM6_IRQ1_ISR(void);
#endif
#endif


#if ((PWM_ATOM6_CH04_ISR_API == STD_ON) || (PWM_ATOM6_CH05_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM6_IRQ2_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_ATOM6_IRQ2_ISR(void);
#endif
#endif


#if ((PWM_ATOM6_CH06_ISR_API == STD_ON) || (PWM_ATOM6_CH07_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM6_IRQ3_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_ATOM6_IRQ3_ISR(void);
#endif
#endif


#if ((PWM_ATOM7_CH00_ISR_API == STD_ON) || (PWM_ATOM7_CH01_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM7_IRQ0_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_ATOM7_IRQ0_ISR(void);
#endif
#endif


#if ((PWM_ATOM7_CH02_ISR_API == STD_ON) || (PWM_ATOM7_CH03_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM7_IRQ1_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_ATOM7_IRQ1_ISR(void);
#endif
#endif


#if ((PWM_ATOM7_CH04_ISR_API == STD_ON) || (PWM_ATOM7_CH05_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM7_IRQ2_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_ATOM7_IRQ2_ISR(void);
#endif
#endif


#if ((PWM_ATOM7_CH06_ISR_API == STD_ON) || (PWM_ATOM7_CH07_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM7_IRQ3_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_ATOM7_IRQ3_ISR(void);
#endif
#endif


#if ((PWM_ATOM8_CH00_ISR_API == STD_ON) || (PWM_ATOM8_CH01_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM8_IRQ0_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_ATOM8_IRQ0_ISR(void);
#endif
#endif


#if ((PWM_ATOM8_CH02_ISR_API == STD_ON) || (PWM_ATOM8_CH03_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM8_IRQ1_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_ATOM8_IRQ1_ISR(void);
#endif
#endif


#if ((PWM_ATOM8_CH04_ISR_API == STD_ON) || (PWM_ATOM8_CH05_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM8_IRQ2_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_ATOM8_IRQ2_ISR(void);
#endif
#endif


#if ((PWM_ATOM8_CH06_ISR_API == STD_ON) || (PWM_ATOM8_CH07_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM8_IRQ3_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_ATOM8_IRQ3_ISR(void);
#endif
#endif


#if ((PWM_ATOM9_CH00_ISR_API == STD_ON) || (PWM_ATOM9_CH01_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM9_IRQ0_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_ATOM9_IRQ0_ISR(void);
#endif
#endif


#if ((PWM_ATOM9_CH02_ISR_API == STD_ON) || (PWM_ATOM9_CH03_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM9_IRQ1_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_ATOM9_IRQ1_ISR(void);
#endif
#endif


#if ((PWM_ATOM9_CH04_ISR_API == STD_ON) || (PWM_ATOM9_CH05_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM9_IRQ2_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_ATOM9_IRQ2_ISR(void);
#endif
#endif


#if ((PWM_ATOM9_CH06_ISR_API == STD_ON) || (PWM_ATOM9_CH07_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM9_IRQ3_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_ATOM9_IRQ3_ISR(void);
#endif
#endif


#if ((PWM_TOM0_CH00_ISR_API == STD_ON) || (PWM_TOM0_CH01_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_PWM_TOM0_IRQ0_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_TOM0_IRQ0_ISR(void);
#endif
#endif


#if ((PWM_TOM0_CH02_ISR_API == STD_ON) || (PWM_TOM0_CH03_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_PWM_TOM0_IRQ1_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_TOM0_IRQ1_ISR(void);
#endif
#endif


#if ((PWM_TOM0_CH04_ISR_API == STD_ON) || (PWM_TOM0_CH05_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_PWM_TOM0_IRQ2_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_TOM0_IRQ2_ISR(void);
#endif
#endif


#if ((PWM_TOM0_CH06_ISR_API == STD_ON) || (PWM_TOM0_CH07_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_PWM_TOM0_IRQ3_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_TOM0_IRQ3_ISR(void);
#endif
#endif


#if ((PWM_TOM0_CH08_ISR_API == STD_ON) || (PWM_TOM0_CH09_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_PWM_TOM0_IRQ4_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_TOM0_IRQ4_ISR(void);
#endif
#endif


#if ((PWM_TOM0_CH10_ISR_API == STD_ON) || (PWM_TOM0_CH11_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_PWM_TOM0_IRQ5_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_TOM0_IRQ5_ISR(void);
#endif
#endif


#if ((PWM_TOM0_CH12_ISR_API == STD_ON) || (PWM_TOM0_CH13_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_PWM_TOM0_IRQ6_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_TOM0_IRQ6_ISR(void);
#endif
#endif


#if ((PWM_TOM0_CH14_ISR_API == STD_ON) || (PWM_TOM0_CH15_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_PWM_TOM0_IRQ7_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_TOM0_IRQ7_ISR(void);
#endif
#endif


#if ((PWM_TOM1_CH00_ISR_API == STD_ON) || (PWM_TOM1_CH01_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_PWM_TOM1_IRQ0_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_TOM1_IRQ0_ISR(void);
#endif
#endif


#if ((PWM_TOM1_CH02_ISR_API == STD_ON) || (PWM_TOM1_CH03_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_PWM_TOM1_IRQ1_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_TOM1_IRQ1_ISR(void);
#endif
#endif


#if ((PWM_TOM1_CH04_ISR_API == STD_ON) || (PWM_TOM1_CH05_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_PWM_TOM1_IRQ2_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_TOM1_IRQ2_ISR(void);
#endif
#endif


#if ((PWM_TOM1_CH06_ISR_API == STD_ON) || (PWM_TOM1_CH07_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_PWM_TOM1_IRQ3_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_TOM1_IRQ3_ISR(void);
#endif
#endif


#if ((PWM_TOM1_CH08_ISR_API == STD_ON) || (PWM_TOM1_CH09_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_PWM_TOM1_IRQ4_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_TOM1_IRQ4_ISR(void);
#endif
#endif


#if ((PWM_TOM1_CH10_ISR_API == STD_ON) || (PWM_TOM1_CH11_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_PWM_TOM1_IRQ5_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_TOM1_IRQ5_ISR(void);
#endif
#endif


#if ((PWM_TOM1_CH12_ISR_API == STD_ON) || (PWM_TOM1_CH13_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_PWM_TOM1_IRQ6_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_TOM1_IRQ6_ISR(void);
#endif
#endif


#if ((PWM_TOM1_CH14_ISR_API == STD_ON) || (PWM_TOM1_CH15_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_PWM_TOM1_IRQ7_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_TOM1_IRQ7_ISR(void);
#endif
#endif


#if ((PWM_TOM2_CH00_ISR_API == STD_ON) || (PWM_TOM2_CH01_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_PWM_TOM2_IRQ0_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_TOM2_IRQ0_ISR(void);
#endif
#endif


#if ((PWM_TOM2_CH02_ISR_API == STD_ON) || (PWM_TOM2_CH03_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_PWM_TOM2_IRQ1_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_TOM2_IRQ1_ISR(void);
#endif
#endif


#if ((PWM_TOM2_CH04_ISR_API == STD_ON) || (PWM_TOM2_CH05_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_PWM_TOM2_IRQ2_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_TOM2_IRQ2_ISR(void);
#endif
#endif


#if ((PWM_TOM2_CH06_ISR_API == STD_ON) || (PWM_TOM2_CH07_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_PWM_TOM2_IRQ3_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_TOM2_IRQ3_ISR(void);
#endif
#endif


#if ((PWM_TOM2_CH08_ISR_API == STD_ON) || (PWM_TOM2_CH09_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_PWM_TOM2_IRQ4_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_TOM2_IRQ4_ISR(void);
#endif
#endif


#if ((PWM_TOM2_CH10_ISR_API == STD_ON) || (PWM_TOM2_CH11_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_PWM_TOM2_IRQ5_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_TOM2_IRQ5_ISR(void);
#endif
#endif


#if ((PWM_TOM2_CH12_ISR_API == STD_ON) || (PWM_TOM2_CH13_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_PWM_TOM2_IRQ6_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_TOM2_IRQ6_ISR(void);
#endif
#endif


#if ((PWM_TOM2_CH14_ISR_API == STD_ON) || (PWM_TOM2_CH15_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_PWM_TOM2_IRQ7_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_TOM2_IRQ7_ISR(void);
#endif
#endif


#if ((PWM_TOM3_CH00_ISR_API == STD_ON) || (PWM_TOM3_CH01_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_PWM_TOM3_IRQ0_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_TOM3_IRQ0_ISR(void);
#endif
#endif


#if ((PWM_TOM3_CH02_ISR_API == STD_ON) || (PWM_TOM3_CH03_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_PWM_TOM3_IRQ1_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_TOM3_IRQ1_ISR(void);
#endif
#endif


#if ((PWM_TOM3_CH04_ISR_API == STD_ON) || (PWM_TOM3_CH05_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_PWM_TOM3_IRQ2_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_TOM3_IRQ2_ISR(void);
#endif
#endif


#if ((PWM_TOM3_CH06_ISR_API == STD_ON) || (PWM_TOM3_CH07_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_PWM_TOM3_IRQ3_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_TOM3_IRQ3_ISR(void);
#endif
#endif


#if ((PWM_TOM3_CH08_ISR_API == STD_ON) || (PWM_TOM3_CH09_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_PWM_TOM3_IRQ4_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_TOM3_IRQ4_ISR(void);
#endif
#endif


#if ((PWM_TOM3_CH10_ISR_API == STD_ON) || (PWM_TOM3_CH11_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_PWM_TOM3_IRQ5_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_TOM3_IRQ5_ISR(void);
#endif
#endif


#if ((PWM_TOM3_CH12_ISR_API == STD_ON) || (PWM_TOM3_CH13_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_PWM_TOM3_IRQ6_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_TOM3_IRQ6_ISR(void);
#endif
#endif


#if ((PWM_TOM3_CH14_ISR_API == STD_ON) || (PWM_TOM3_CH15_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_PWM_TOM3_IRQ7_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_TOM3_IRQ7_ISR(void);
#endif
#endif


#if ((PWM_TOM4_CH00_ISR_API == STD_ON) || (PWM_TOM4_CH01_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_PWM_TOM4_IRQ0_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_TOM4_IRQ0_ISR(void);
#endif
#endif


#if ((PWM_TOM4_CH02_ISR_API == STD_ON) || (PWM_TOM4_CH03_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_PWM_TOM4_IRQ1_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_TOM4_IRQ1_ISR(void);
#endif
#endif


#if ((PWM_TOM4_CH04_ISR_API == STD_ON) || (PWM_TOM4_CH05_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_PWM_TOM4_IRQ2_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_TOM4_IRQ2_ISR(void);
#endif
#endif


#if ((PWM_TOM4_CH06_ISR_API == STD_ON) || (PWM_TOM4_CH07_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_PWM_TOM4_IRQ3_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_TOM4_IRQ3_ISR(void);
#endif
#endif


#if ((PWM_TOM4_CH08_ISR_API == STD_ON) || (PWM_TOM4_CH09_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_PWM_TOM4_IRQ4_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_TOM4_IRQ4_ISR(void);
#endif
#endif


#if ((PWM_TOM4_CH10_ISR_API == STD_ON) || (PWM_TOM4_CH11_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_PWM_TOM4_IRQ5_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_TOM4_IRQ5_ISR(void);
#endif
#endif


#if ((PWM_TOM4_CH12_ISR_API == STD_ON) || (PWM_TOM4_CH13_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_PWM_TOM4_IRQ6_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_TOM4_IRQ6_ISR(void);
#endif
#endif


#if ((PWM_TOM4_CH14_ISR_API == STD_ON) || (PWM_TOM4_CH15_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_PWM_TOM4_IRQ7_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) GTM_TOM4_IRQ7_ISR(void);
#endif
#endif

#define PWM_STOP_SEC_CODE_FAST
#include "Pwm_MemMap.h"
#endif
#endif /* PWM_GTM_IRQ_H */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
