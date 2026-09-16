/*====================================================================================================================*/
/* Project      = RH850/U2Bx,U2Cx MCAL Ver21.00.00.D                                                                  */
/* Module       = Ocu_GTM_Irq.h                                                                                       */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2025 Renesas Electronics Corporation. All rights reserved.                                                     */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains ISRs for all Timers of GPT Driver                                                               */
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
 * 1.4.0: 30/05/2025 : Initial Version.
 */
/**********************************************************************************************************************/
#ifndef OCU_GTM_IRQ_H
#define OCU_GTM_IRQ_H
/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for using Std Type(e.g. STD_ON), Compiler Macros(e.g. P2FUNC), Platform Types(e.g. uint8) */
#include "Std_Types.h"
/* Included for interrupt category definitions */
#include "Os.h"
/* Included for OCU module-specific definitions */
#include "Ocu_Cfg.h"
/* Included for Type of Ocu_ChannelType and Ocu_ValueType */
#include "Ocu_Types.h"
/* Included for macro definitions (e.g. Service IDs)*/
#include "Ocu.h"
/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define OCU_GTM_IRQ_AR_RELEASE_MAJOR_VERSION    OCU_AR_RELEASE_MAJOR_VERSION
#define OCU_GTM_IRQ_AR_RELEASE_MINOR_VERSION    OCU_AR_RELEASE_MINOR_VERSION
#define OCU_GTM_IRQ_AR_RELEASE_REVISION_VERSION OCU_AR_RELEASE_REVISION_VERSION
/* File version information */
#define OCU_GTM_IRQ_SW_MAJOR_VERSION    OCU_SW_MAJOR_VERSION
#define OCU_GTM_IRQ_SW_MINOR_VERSION    OCU_SW_MINOR_VERSION
/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/
#define OCU_START_SEC_CODE_FAST
#include "Ocu_MemMap.h"
#if(STD_ON == OCU_GTM_ATOM_USED)
/***********************************************************************************************************************
** Function Name        : ATOM(TOM)n_IRQm_(CAT2_)ISR
***********************************************************************************************************************/
#if (OCU_ATOM0_CH00_ISR_API == STD_ON) || (OCU_ATOM0_CH01_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM0_IRQ0_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_ATOM0_IRQ0_ISR(void);
#endif
#endif

#if (OCU_ATOM0_CH02_ISR_API == STD_ON) || (OCU_ATOM0_CH03_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM0_IRQ1_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_ATOM0_IRQ1_ISR(void);
#endif
#endif

#if (OCU_ATOM0_CH04_ISR_API == STD_ON) || (OCU_ATOM0_CH05_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM0_IRQ2_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_ATOM0_IRQ2_ISR(void);
#endif
#endif

#if (OCU_ATOM0_CH06_ISR_API == STD_ON) || (OCU_ATOM0_CH07_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM0_IRQ3_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_ATOM0_IRQ3_ISR(void);
#endif
#endif

#if (OCU_ATOM1_CH00_ISR_API == STD_ON) || (OCU_ATOM1_CH01_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM1_IRQ0_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_ATOM1_IRQ0_ISR(void);
#endif
#endif

#if (OCU_ATOM1_CH02_ISR_API == STD_ON) || (OCU_ATOM1_CH03_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM1_IRQ1_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_ATOM1_IRQ1_ISR(void);
#endif
#endif

#if (OCU_ATOM1_CH04_ISR_API == STD_ON) || (OCU_ATOM1_CH05_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM1_IRQ2_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_ATOM1_IRQ2_ISR(void);
#endif
#endif

#if (OCU_ATOM1_CH06_ISR_API == STD_ON) || (OCU_ATOM1_CH07_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM1_IRQ3_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_ATOM1_IRQ3_ISR(void);
#endif
#endif

#if (OCU_ATOM2_CH00_ISR_API == STD_ON) || (OCU_ATOM2_CH01_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM2_IRQ0_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_ATOM2_IRQ0_ISR(void);
#endif
#endif

#if (OCU_ATOM2_CH02_ISR_API == STD_ON) || (OCU_ATOM2_CH03_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM2_IRQ1_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_ATOM2_IRQ1_ISR(void);
#endif
#endif

#if (OCU_ATOM2_CH04_ISR_API == STD_ON) || (OCU_ATOM2_CH05_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM2_IRQ2_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_ATOM2_IRQ2_ISR(void);
#endif
#endif

#if (OCU_ATOM2_CH06_ISR_API == STD_ON) || (OCU_ATOM2_CH07_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM2_IRQ3_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_ATOM2_IRQ3_ISR(void);
#endif
#endif

#if (OCU_ATOM3_CH00_ISR_API == STD_ON) || (OCU_ATOM3_CH01_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM3_IRQ0_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_ATOM3_IRQ0_ISR(void);
#endif
#endif

#if (OCU_ATOM3_CH02_ISR_API == STD_ON) || (OCU_ATOM3_CH03_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM3_IRQ1_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_ATOM3_IRQ1_ISR(void);
#endif
#endif

#if (OCU_ATOM3_CH04_ISR_API == STD_ON) || (OCU_ATOM3_CH05_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM3_IRQ2_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_ATOM3_IRQ2_ISR(void);
#endif
#endif

#if (OCU_ATOM3_CH06_ISR_API == STD_ON) || (OCU_ATOM3_CH07_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM3_IRQ3_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_ATOM3_IRQ3_ISR(void);
#endif
#endif

#if (OCU_ATOM4_CH00_ISR_API == STD_ON) || (OCU_ATOM4_CH01_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM4_IRQ0_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_ATOM4_IRQ0_ISR(void);
#endif
#endif

#if (OCU_ATOM4_CH02_ISR_API == STD_ON) || (OCU_ATOM4_CH03_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM4_IRQ1_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_ATOM4_IRQ1_ISR(void);
#endif
#endif

#if (OCU_ATOM4_CH04_ISR_API == STD_ON) || (OCU_ATOM4_CH05_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM4_IRQ2_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_ATOM4_IRQ2_ISR(void);
#endif
#endif

#if (OCU_ATOM4_CH06_ISR_API == STD_ON) || (OCU_ATOM4_CH07_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM4_IRQ3_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_ATOM4_IRQ3_ISR(void);
#endif
#endif

#if (OCU_ATOM5_CH00_ISR_API == STD_ON) || (OCU_ATOM5_CH01_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM5_IRQ0_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_ATOM5_IRQ0_ISR(void);
#endif
#endif

#if (OCU_ATOM5_CH02_ISR_API == STD_ON) || (OCU_ATOM5_CH03_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM5_IRQ1_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_ATOM5_IRQ1_ISR(void);
#endif
#endif

#if (OCU_ATOM5_CH04_ISR_API == STD_ON) || (OCU_ATOM5_CH05_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM5_IRQ2_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_ATOM5_IRQ2_ISR(void);
#endif
#endif

#if (OCU_ATOM5_CH06_ISR_API == STD_ON) || (OCU_ATOM5_CH07_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM5_IRQ3_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_ATOM5_IRQ3_ISR(void);
#endif
#endif

#if (OCU_ATOM6_CH00_ISR_API == STD_ON) || (OCU_ATOM6_CH01_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM6_IRQ0_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_ATOM6_IRQ0_ISR(void);
#endif
#endif

#if (OCU_ATOM6_CH02_ISR_API == STD_ON) || (OCU_ATOM6_CH03_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM6_IRQ1_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_ATOM6_IRQ1_ISR(void);
#endif
#endif

#if (OCU_ATOM6_CH04_ISR_API == STD_ON) || (OCU_ATOM6_CH05_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM6_IRQ2_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_ATOM6_IRQ2_ISR(void);
#endif
#endif

#if (OCU_ATOM6_CH06_ISR_API == STD_ON) || (OCU_ATOM6_CH07_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM6_IRQ3_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_ATOM6_IRQ3_ISR(void);
#endif
#endif

#if (OCU_ATOM7_CH00_ISR_API == STD_ON) || (OCU_ATOM7_CH01_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM7_IRQ0_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_ATOM7_IRQ0_ISR(void);
#endif
#endif

#if (OCU_ATOM7_CH02_ISR_API == STD_ON) || (OCU_ATOM7_CH03_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM7_IRQ1_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_ATOM7_IRQ1_ISR(void);
#endif
#endif

#if (OCU_ATOM7_CH04_ISR_API == STD_ON) || (OCU_ATOM7_CH05_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM7_IRQ2_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_ATOM7_IRQ2_ISR(void);
#endif
#endif

#if (OCU_ATOM7_CH06_ISR_API == STD_ON) || (OCU_ATOM7_CH07_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM7_IRQ3_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_ATOM7_IRQ3_ISR(void);
#endif
#endif

#if (OCU_ATOM8_CH00_ISR_API == STD_ON) || (OCU_ATOM8_CH01_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM8_IRQ0_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_ATOM8_IRQ0_ISR(void);
#endif
#endif

#if (OCU_ATOM8_CH02_ISR_API == STD_ON) || (OCU_ATOM8_CH03_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM8_IRQ1_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_ATOM8_IRQ1_ISR(void);
#endif
#endif

#if (OCU_ATOM8_CH04_ISR_API == STD_ON) || (OCU_ATOM8_CH05_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM8_IRQ2_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_ATOM8_IRQ2_ISR(void);
#endif
#endif

#if (OCU_ATOM8_CH06_ISR_API == STD_ON) || (OCU_ATOM8_CH07_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM8_IRQ3_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_ATOM8_IRQ3_ISR(void);
#endif
#endif

#if (OCU_ATOM9_CH00_ISR_API == STD_ON) || (OCU_ATOM9_CH01_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM9_IRQ0_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_ATOM9_IRQ0_ISR(void);
#endif
#endif

#if (OCU_ATOM9_CH02_ISR_API == STD_ON) || (OCU_ATOM9_CH03_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM9_IRQ1_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_ATOM9_IRQ1_ISR(void);
#endif
#endif

#if (OCU_ATOM9_CH04_ISR_API == STD_ON) || (OCU_ATOM9_CH05_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM9_IRQ2_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_ATOM9_IRQ2_ISR(void);
#endif
#endif

#if (OCU_ATOM9_CH06_ISR_API == STD_ON) || (OCU_ATOM9_CH07_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM9_IRQ3_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_ATOM9_IRQ3_ISR(void);
#endif
#endif
#endif /* End of OCU_GTM_ATOM_USED */

#if(STD_ON == OCU_GTM_TOM_USED)
#if (OCU_TOM0_CH00_ISR_API == STD_ON) || (OCU_TOM0_CH01_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM0_IRQ0_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_TOM0_IRQ0_ISR(void);
#endif
#endif

#if (OCU_TOM0_CH02_ISR_API == STD_ON) || (OCU_TOM0_CH03_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM0_IRQ1_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_TOM0_IRQ1_ISR(void);
#endif
#endif

#if (OCU_TOM0_CH04_ISR_API == STD_ON) || (OCU_TOM0_CH05_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM0_IRQ2_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_TOM0_IRQ2_ISR(void);
#endif
#endif

#if (OCU_TOM0_CH06_ISR_API == STD_ON) || (OCU_TOM0_CH07_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM0_IRQ3_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_TOM0_IRQ3_ISR(void);
#endif
#endif

#if (OCU_TOM0_CH08_ISR_API == STD_ON) || (OCU_TOM0_CH09_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM0_IRQ4_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_TOM0_IRQ4_ISR(void);
#endif
#endif

#if (OCU_TOM0_CH10_ISR_API == STD_ON) || (OCU_TOM0_CH11_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM0_IRQ5_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_TOM0_IRQ5_ISR(void);
#endif
#endif

#if (OCU_TOM0_CH12_ISR_API == STD_ON) || (OCU_TOM0_CH13_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM0_IRQ6_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_TOM0_IRQ6_ISR(void);
#endif
#endif

#if (OCU_TOM0_CH14_ISR_API == STD_ON) || (OCU_TOM0_CH15_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM0_IRQ3_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_TOM0_IRQ7_ISR(void);
#endif
#endif

#if (OCU_TOM1_CH00_ISR_API == STD_ON) || (OCU_TOM1_CH01_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM1_IRQ0_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_TOM1_IRQ0_ISR(void);
#endif
#endif

#if (OCU_TOM1_CH02_ISR_API == STD_ON) || (OCU_TOM1_CH03_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM1_IRQ1_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_TOM1_IRQ1_ISR(void);
#endif
#endif

#if (OCU_TOM1_CH04_ISR_API == STD_ON) || (OCU_TOM1_CH05_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM1_IRQ2_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_TOM1_IRQ2_ISR(void);
#endif
#endif

#if (OCU_TOM1_CH06_ISR_API == STD_ON) || (OCU_TOM1_CH07_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM1_IRQ3_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_TOM1_IRQ3_ISR(void);
#endif
#endif

#if (OCU_TOM1_CH08_ISR_API == STD_ON) || (OCU_TOM1_CH09_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM1_IRQ4_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_TOM1_IRQ4_ISR(void);
#endif
#endif

#if (OCU_TOM1_CH10_ISR_API == STD_ON) || (OCU_TOM1_CH11_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM1_IRQ5_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_TOM1_IRQ5_ISR(void);
#endif
#endif

#if (OCU_TOM1_CH12_ISR_API == STD_ON) || (OCU_TOM1_CH13_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM1_IRQ6_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_TOM1_IRQ6_ISR(void);
#endif
#endif

#if (OCU_TOM1_CH14_ISR_API == STD_ON) || (OCU_TOM1_CH15_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM1_IRQ3_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_TOM1_IRQ7_ISR(void);
#endif
#endif

#if (OCU_TOM2_CH00_ISR_API == STD_ON) || (OCU_TOM2_CH01_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM2_IRQ0_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_TOM2_IRQ0_ISR(void);
#endif
#endif

#if (OCU_TOM2_CH02_ISR_API == STD_ON) || (OCU_TOM2_CH03_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM2_IRQ1_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_TOM2_IRQ1_ISR(void);
#endif
#endif

#if (OCU_TOM2_CH04_ISR_API == STD_ON) || (OCU_TOM2_CH05_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM2_IRQ2_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_TOM2_IRQ2_ISR(void);
#endif
#endif

#if (OCU_TOM2_CH06_ISR_API == STD_ON) || (OCU_TOM2_CH07_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM2_IRQ3_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_TOM2_IRQ3_ISR(void);
#endif
#endif

#if (OCU_TOM2_CH08_ISR_API == STD_ON) || (OCU_TOM2_CH09_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM2_IRQ4_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_TOM2_IRQ4_ISR(void);
#endif
#endif

#if (OCU_TOM2_CH10_ISR_API == STD_ON) || (OCU_TOM2_CH11_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM2_IRQ5_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_TOM2_IRQ5_ISR(void);
#endif
#endif

#if (OCU_TOM2_CH12_ISR_API == STD_ON) || (OCU_TOM2_CH13_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM2_IRQ6_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_TOM2_IRQ6_ISR(void);
#endif
#endif

#if (OCU_TOM2_CH14_ISR_API == STD_ON) || (OCU_TOM2_CH15_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM2_IRQ3_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_TOM2_IRQ7_ISR(void);
#endif
#endif

#if (OCU_TOM2_CH00_ISR_API == STD_ON) || (OCU_TOM2_CH01_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM2_IRQ0_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_TOM3_IRQ0_ISR(void);
#endif
#endif

#if (OCU_TOM2_CH02_ISR_API == STD_ON) || (OCU_TOM2_CH03_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM2_IRQ1_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_TOM3_IRQ1_ISR(void);
#endif
#endif

#if (OCU_TOM2_CH04_ISR_API == STD_ON) || (OCU_TOM2_CH05_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM2_IRQ2_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_TOM3_IRQ2_ISR(void);
#endif
#endif

#if (OCU_TOM2_CH06_ISR_API == STD_ON) || (OCU_TOM2_CH07_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM2_IRQ3_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_TOM3_IRQ3_ISR(void);
#endif
#endif

#if (OCU_TOM2_CH08_ISR_API == STD_ON) || (OCU_TOM2_CH09_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM2_IRQ4_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_TOM3_IRQ4_ISR(void);
#endif
#endif

#if (OCU_TOM2_CH10_ISR_API == STD_ON) || (OCU_TOM2_CH11_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM2_IRQ5_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_TOM3_IRQ5_ISR(void);
#endif
#endif

#if (OCU_TOM2_CH12_ISR_API == STD_ON) || (OCU_TOM2_CH13_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM2_IRQ6_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_TOM3_IRQ6_ISR(void);
#endif
#endif

#if (OCU_TOM2_CH14_ISR_API == STD_ON) || (OCU_TOM2_CH15_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM2_IRQ3_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_TOM3_IRQ7_ISR(void);
#endif
#endif

#if (OCU_TOM4_CH00_ISR_API == STD_ON) || (OCU_TOM4_CH01_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM4_IRQ0_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_TOM4_IRQ0_ISR(void);
#endif
#endif

#if (OCU_TOM4_CH02_ISR_API == STD_ON) || (OCU_TOM4_CH03_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM4_IRQ1_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_TOM4_IRQ1_ISR(void);
#endif
#endif

#if (OCU_TOM4_CH04_ISR_API == STD_ON) || (OCU_TOM4_CH05_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM4_IRQ2_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_TOM4_IRQ2_ISR(void);
#endif
#endif

#if (OCU_TOM4_CH06_ISR_API == STD_ON) || (OCU_TOM4_CH07_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM4_IRQ3_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_TOM4_IRQ3_ISR(void);
#endif
#endif

#if (OCU_TOM4_CH08_ISR_API == STD_ON) || (OCU_TOM4_CH09_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM4_IRQ4_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_TOM4_IRQ4_ISR(void);
#endif
#endif

#if (OCU_TOM4_CH10_ISR_API == STD_ON) || (OCU_TOM4_CH11_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM4_IRQ5_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_TOM4_IRQ5_ISR(void);
#endif
#endif

#if (OCU_TOM4_CH12_ISR_API == STD_ON) || (OCU_TOM4_CH13_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM4_IRQ6_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_TOM4_IRQ6_ISR(void);
#endif
#endif

#if (OCU_TOM4_CH14_ISR_API == STD_ON) || (OCU_TOM4_CH15_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM4_IRQ3_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) GTM_TOM4_IRQ7_ISR(void);
#endif
#endif
#endif /* End of OCU_GTM_TOM_USED */

#define OCU_STOP_SEC_CODE_FAST
#include "Ocu_MemMap.h"
#endif /* OCU_GTM_IRQ_H */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
