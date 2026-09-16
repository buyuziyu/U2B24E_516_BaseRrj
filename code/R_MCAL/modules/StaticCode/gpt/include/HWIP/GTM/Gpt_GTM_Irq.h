/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Gpt_GTM_Irq.h                                                                                       */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2024, 2025 Renesas Electronics Corporation. All rights reserved.                                               */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains ISRs for all Timers of GPT Driver                                                               */
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
 *  2.4.0  30/06/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.01.00 (D) release
 *  2.3.2  25/04/2025  : As part of GTM HWIP support for U2Ax, following changes are made:
 *                       1. Modify interrupt function to improve interrupt merge for GTM
 *  2.3.1  31/03/2025  : Update SW-VERSION for RH850/U2BxE MCAL Ver22.00.02/Ver22.00.02.D Release
 *  2.3.0  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 *  2.2.0  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 *  2.1.2  31/10/2024  : Initial Version.
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/

#ifndef GPT_GTM_IRQ_H
#define GPT_GTM_IRQ_H

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for using Std Type(e.g. STD_ON), Compiler Macros(e.g. P2FUNC), Platform Types(e.g. uint8) */
#include "Std_Types.h"
/* Included for interrupt category definitions */
#include "Os.h"
/* Include difinition of multi instance */

/* Included for GPT module specific definitions */
#include "Gpt_Cfg.h"
/* Included for macro definitions (e.g. Service IDs)*/
#include "Gpt.h"

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define GPT_GTM_IRQ_AR_RELEASE_MAJOR_VERSION    GPT_AR_RELEASE_MAJOR_VERSION
#define GPT_GTM_IRQ_AR_RELEASE_MINOR_VERSION    GPT_AR_RELEASE_MINOR_VERSION
#define GPT_GTM_IRQ_AR_RELEASE_REVISION_VERSION GPT_AR_RELEASE_REVISION_VERSION
/* File version information */
#define GPT_GTM_IRQ_SW_MAJOR_VERSION    GPT_SW_MAJOR_VERSION
#define GPT_GTM_IRQ_SW_MINOR_VERSION    GPT_SW_MINOR_VERSION

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/
#if (GPT_TIMER_IP_GTM == STD_ON)
#define GPT_START_SEC_CODE_FAST
#include "Gpt_MemMap.h"

#if ((GPT_TOM0_CH00_ISR_API == STD_ON)||(GPT_TOM0_CH01_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM0_IRQ0_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM0_IRQ0_ISR(void);
#endif
#endif /* End of (GPT_TOM0_CH00_ISR_API == STD_ON)||(GPT_TOM0_CH01_ISR_API == STD_ON) */

#if ((GPT_TOM0_CH02_ISR_API == STD_ON)||(GPT_TOM0_CH03_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM0_IRQ1_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM0_IRQ1_ISR(void);
#endif
#endif /* End of (GPT_TOM0_CH02_ISR_API == STD_ON)||(GPT_TOM0_CH03_ISR_API == STD_ON) */

#if ((GPT_TOM0_CH04_ISR_API == STD_ON)||(GPT_TOM0_CH05_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM0_IRQ2_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM0_IRQ2_ISR(void);
#endif
#endif /* End of (GPT_TOM0_CH03_ISR_API == STD_ON)||(GPT_TOM0_CH04_ISR_API == STD_ON) */

#if ((GPT_TOM0_CH06_ISR_API == STD_ON)||(GPT_TOM0_CH07_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM0_IRQ3_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM0_IRQ3_ISR(void);
#endif
#endif /* End of (GPT_TOM0_CH06_ISR_API == STD_ON)||(GPT_TOM0_CH07_ISR_API == STD_ON) */

#if ((GPT_TOM0_CH08_ISR_API == STD_ON)||(GPT_TOM0_CH09_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM0_IRQ4_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM0_IRQ4_ISR(void);
#endif
#endif /* End of (GPT_TOM0_CH08_ISR_API == STD_ON)||(GPT_TOM0_CH09_ISR_API == STD_ON) */

#if ((GPT_TOM0_CH10_ISR_API == STD_ON)||(GPT_TOM0_CH11_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM0_IRQ5_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM0_IRQ5_ISR(void);
#endif
#endif /* End of (GPT_TOM0_CH10_ISR_API == STD_ON)||(GPT_TOM0_CH11_ISR_API == STD_ON) */

#if ((GPT_TOM0_CH12_ISR_API == STD_ON)||(GPT_TOM0_CH13_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM0_IRQ6_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM0_IRQ6_ISR(void);
#endif
#endif /* End of (GPT_TOM0_CH12_ISR_API == STD_ON)||(GPT_TOM0_CH13_ISR_API == STD_ON) */

#if ((GPT_TOM0_CH14_ISR_API == STD_ON)||(GPT_TOM0_CH15_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM0_IRQ7_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM0_IRQ7_ISR(void);
#endif
#endif /* End of (GPT_TOM0_CH14_ISR_API == STD_ON)||(GPT_TOM0_CH15_ISR_API == STD_ON) */

#if ((GPT_TOM1_CH00_ISR_API == STD_ON)||(GPT_TOM1_CH01_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM1_IRQ0_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM1_IRQ0_ISR(void);
#endif
#endif /* End of (GPT_TOM1_CH00_ISR_API == STD_ON)||(GPT_TOM1_CH01_ISR_API == STD_ON) */

#if ((GPT_TOM1_CH02_ISR_API == STD_ON)||(GPT_TOM1_CH03_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM1_IRQ1_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM1_IRQ1_ISR(void);
#endif
#endif /* End of (GPT_TOM1_CH02_ISR_API == STD_ON)||(GPT_TOM1_CH03_ISR_API == STD_ON) */

#if ((GPT_TOM1_CH04_ISR_API == STD_ON)||(GPT_TOM1_CH05_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM1_IRQ2_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM1_IRQ2_ISR(void);
#endif
#endif /* End of (GPT_TOM1_CH03_ISR_API == STD_ON)||(GPT_TOM1_CH04_ISR_API == STD_ON) */

#if ((GPT_TOM1_CH06_ISR_API == STD_ON)||(GPT_TOM1_CH07_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM1_IRQ3_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM1_IRQ3_ISR(void);
#endif
#endif /* End of (GPT_TOM1_CH06_ISR_API == STD_ON)||(GPT_TOM1_CH07_ISR_API == STD_ON) */

#if ((GPT_TOM1_CH08_ISR_API == STD_ON)||(GPT_TOM1_CH09_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM1_IRQ4_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM1_IRQ4_ISR(void);
#endif
#endif /* End of (GPT_TOM1_CH08_ISR_API == STD_ON)||(GPT_TOM1_CH09_ISR_API == STD_ON) */

#if ((GPT_TOM1_CH10_ISR_API == STD_ON)||(GPT_TOM1_CH11_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM1_IRQ5_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM1_IRQ5_ISR(void);
#endif
#endif /* End of (GPT_TOM1_CH10_ISR_API == STD_ON)||(GPT_TOM1_CH11_ISR_API == STD_ON) */

#if ((GPT_TOM1_CH12_ISR_API == STD_ON)||(GPT_TOM1_CH13_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM1_IRQ6_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM1_IRQ6_ISR(void);
#endif
#endif /* End of (GPT_TOM1_CH12_ISR_API == STD_ON)||(GPT_TOM1_CH13_ISR_API == STD_ON) */

#if ((GPT_TOM1_CH14_ISR_API == STD_ON)||(GPT_TOM1_CH15_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM1_IRQ7_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM1_IRQ7_ISR(void);
#endif
#endif /* End of (GPT_TOM1_CH14_ISR_API == STD_ON)||(GPT_TOM1_CH15_ISR_API == STD_ON) */

#if ((GPT_TOM2_CH00_ISR_API == STD_ON)||(GPT_TOM2_CH01_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM2_IRQ0_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM2_IRQ0_ISR(void);
#endif
#endif /* End of (GPT_TOM2_CH00_ISR_API == STD_ON)||(GPT_TOM2_CH01_ISR_API == STD_ON) */

#if ((GPT_TOM2_CH02_ISR_API == STD_ON)||(GPT_TOM2_CH03_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM2_IRQ1_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM2_IRQ1_ISR(void);
#endif
#endif /* End of (GPT_TOM2_CH02_ISR_API == STD_ON)||(GPT_TOM2_CH03_ISR_API == STD_ON) */

#if ((GPT_TOM2_CH04_ISR_API == STD_ON)||(GPT_TOM2_CH05_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM2_IRQ2_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM2_IRQ2_ISR(void);
#endif
#endif /* End of (GPT_TOM2_CH03_ISR_API == STD_ON)||(GPT_TOM2_CH04_ISR_API == STD_ON) */

#if ((GPT_TOM2_CH06_ISR_API == STD_ON)||(GPT_TOM2_CH07_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM2_IRQ3_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM2_IRQ3_ISR(void);
#endif
#endif /* End of (GPT_TOM2_CH06_ISR_API == STD_ON)||(GPT_TOM2_CH07_ISR_API == STD_ON) */

#if ((GPT_TOM2_CH08_ISR_API == STD_ON)||(GPT_TOM2_CH09_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM2_IRQ4_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM2_IRQ4_ISR(void);
#endif
#endif /* End of (GPT_TOM2_CH08_ISR_API == STD_ON)||(GPT_TOM2_CH09_ISR_API == STD_ON) */

#if ((GPT_TOM2_CH10_ISR_API == STD_ON)||(GPT_TOM2_CH11_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM2_IRQ5_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM2_IRQ5_ISR(void);
#endif
#endif /* End of (GPT_TOM2_CH10_ISR_API == STD_ON)||(GPT_TOM2_CH11_ISR_API == STD_ON) */

#if ((GPT_TOM2_CH12_ISR_API == STD_ON)||(GPT_TOM2_CH13_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM2_IRQ6_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM2_IRQ6_ISR(void);
#endif
#endif /* End of (GPT_TOM2_CH12_ISR_API == STD_ON)||(GPT_TOM2_CH13_ISR_API == STD_ON) */

#if ((GPT_TOM2_CH14_ISR_API == STD_ON)||(GPT_TOM2_CH15_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM2_IRQ7_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM2_IRQ7_ISR(void);
#endif
#endif /* End of (GPT_TOM2_CH14_ISR_API == STD_ON)||(GPT_TOM2_CH15_ISR_API == STD_ON) */

#if ((GPT_TOM3_CH00_ISR_API == STD_ON)||(GPT_TOM3_CH01_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM3_IRQ0_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM3_IRQ0_ISR(void);
#endif
#endif /* End of (GPT_TOM3_CH00_ISR_API == STD_ON)||(GPT_TOM3_CH01_ISR_API == STD_ON) */

#if ((GPT_TOM3_CH02_ISR_API == STD_ON)||(GPT_TOM3_CH03_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM3_IRQ1_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM3_IRQ1_ISR(void);
#endif
#endif /* End of (GPT_TOM3_CH02_ISR_API == STD_ON)||(GPT_TOM3_CH03_ISR_API == STD_ON) */

#if ((GPT_TOM3_CH04_ISR_API == STD_ON)||(GPT_TOM3_CH05_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM3_IRQ2_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM3_IRQ2_ISR(void);
#endif
#endif /* End of (GPT_TOM3_CH03_ISR_API == STD_ON)||(GPT_TOM3_CH04_ISR_API == STD_ON) */

#if ((GPT_TOM3_CH06_ISR_API == STD_ON)||(GPT_TOM3_CH07_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM3_IRQ3_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM3_IRQ3_ISR(void);
#endif
#endif /* End of (GPT_TOM3_CH06_ISR_API == STD_ON)||(GPT_TOM3_CH07_ISR_API == STD_ON) */

#if ((GPT_TOM3_CH08_ISR_API == STD_ON)||(GPT_TOM3_CH09_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM3_IRQ4_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM3_IRQ4_ISR(void);
#endif
#endif /* End of (GPT_TOM3_CH08_ISR_API == STD_ON)||(GPT_TOM3_CH09_ISR_API == STD_ON) */

#if ((GPT_TOM3_CH10_ISR_API == STD_ON)||(GPT_TOM3_CH11_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM3_IRQ5_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM3_IRQ5_ISR(void);
#endif
#endif /* End of (GPT_TOM3_CH10_ISR_API == STD_ON)||(GPT_TOM3_CH11_ISR_API == STD_ON) */

#if ((GPT_TOM3_CH12_ISR_API == STD_ON)||(GPT_TOM3_CH13_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM3_IRQ6_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM3_IRQ6_ISR(void);
#endif
#endif /* End of (GPT_TOM3_CH12_ISR_API == STD_ON)||(GPT_TOM3_CH13_ISR_API == STD_ON) */

#if ((GPT_TOM3_CH14_ISR_API == STD_ON)||(GPT_TOM3_CH15_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM3_IRQ7_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM3_IRQ7_ISR(void);
#endif
#endif /* End of (GPT_TOM3_CH14_ISR_API == STD_ON)||(GPT_TOM3_CH15_ISR_API == STD_ON) */

#if ((GPT_TOM4_CH00_ISR_API == STD_ON)||(GPT_TOM4_CH01_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM4_IRQ0_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM4_IRQ0_ISR(void);
#endif
#endif /* End of (GPT_TOM4_CH00_ISR_API == STD_ON)||(GPT_TOM4_CH01_ISR_API == STD_ON) */

#if ((GPT_TOM4_CH02_ISR_API == STD_ON)||(GPT_TOM4_CH03_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM4_IRQ1_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM4_IRQ1_ISR(void);
#endif
#endif /* End of (GPT_TOM4_CH02_ISR_API == STD_ON)||(GPT_TOM4_CH03_ISR_API == STD_ON) */

#if ((GPT_TOM4_CH04_ISR_API == STD_ON)||(GPT_TOM4_CH05_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM4_IRQ2_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM4_IRQ2_ISR(void);
#endif
#endif /* End of (GPT_TOM4_CH03_ISR_API == STD_ON)||(GPT_TOM4_CH04_ISR_API == STD_ON) */

#if ((GPT_TOM4_CH06_ISR_API == STD_ON)||(GPT_TOM4_CH07_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM4_IRQ3_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM4_IRQ3_ISR(void);
#endif
#endif /* End of (GPT_TOM4_CH06_ISR_API == STD_ON)||(GPT_TOM4_CH07_ISR_API == STD_ON) */

#if ((GPT_TOM4_CH08_ISR_API == STD_ON)||(GPT_TOM4_CH09_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM4_IRQ4_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM4_IRQ4_ISR(void);
#endif
#endif /* End of (GPT_TOM4_CH08_ISR_API == STD_ON)||(GPT_TOM4_CH09_ISR_API == STD_ON) */

#if ((GPT_TOM4_CH10_ISR_API == STD_ON)||(GPT_TOM4_CH11_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM4_IRQ5_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM4_IRQ5_ISR(void);
#endif
#endif /* End of (GPT_TOM4_CH10_ISR_API == STD_ON)||(GPT_TOM4_CH11_ISR_API == STD_ON) */

#if ((GPT_TOM4_CH12_ISR_API == STD_ON)||(GPT_TOM4_CH13_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM4_IRQ6_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM4_IRQ6_ISR(void);
#endif
#endif /* End of (GPT_TOM4_CH12_ISR_API == STD_ON)||(GPT_TOM4_CH13_ISR_API == STD_ON) */

#if ((GPT_TOM4_CH14_ISR_API == STD_ON)||(GPT_TOM4_CH15_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM4_IRQ7_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM4_IRQ7_ISR(void);
#endif
#endif /* End of (GPT_TOM4_CH14_ISR_API == STD_ON)||(GPT_TOM4_CH15_ISR_API == STD_ON) */

#if ((GPT_ATOM0_CH00_ISR_API == STD_ON)||(GPT_ATOM0_CH01_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM0_IRQ0_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM0_IRQ0_ISR(void);
#endif
#endif /* End of (GPT_ATOM0_CH00_ISR_API == STD_ON)||(GPT_ATOM0_CH01_ISR_API == STD_ON) */

#if ((GPT_ATOM0_CH02_ISR_API == STD_ON)||(GPT_ATOM0_CH03_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM0_IRQ1_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM0_IRQ1_ISR(void);
#endif
#endif /* End of (GPT_ATOM0_CH02_ISR_API == STD_ON)||(GPT_ATOM0_CH03_ISR_API == STD_ON) */

#if ((GPT_ATOM0_CH04_ISR_API == STD_ON)||(GPT_ATOM0_CH05_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM0_IRQ2_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM0_IRQ2_ISR(void);
#endif
#endif /* End of (GPT_ATOM0_CH04_ISR_API == STD_ON)||(GPT_ATOM0_CH05_ISR_API == STD_ON) */

#if ((GPT_ATOM0_CH06_ISR_API == STD_ON)||(GPT_ATOM0_CH07_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM0_IRQ3_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM0_IRQ3_ISR(void);
#endif
#endif /* End of (GPT_ATOM0_CH05_ISR_API == STD_ON)||(GPT_ATOM0_CH07_ISR_API == STD_ON) */

#if ((GPT_ATOM1_CH00_ISR_API == STD_ON)||(GPT_ATOM1_CH01_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM1_IRQ0_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM1_IRQ0_ISR(void);
#endif
#endif /* End of (GPT_ATOM1_CH00_ISR_API == STD_ON)||(GPT_ATOM1_CH01_ISR_API == STD_ON) */

#if ((GPT_ATOM1_CH02_ISR_API == STD_ON)||(GPT_ATOM1_CH03_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM1_IRQ1_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM1_IRQ1_ISR(void);
#endif
#endif /* End of (GPT_ATOM1_CH02_ISR_API == STD_ON)||(GPT_ATOM1_CH03_ISR_API == STD_ON) */

#if ((GPT_ATOM1_CH04_ISR_API == STD_ON)||(GPT_ATOM1_CH05_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM1_IRQ2_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM1_IRQ2_ISR(void);
#endif
#endif /* End of (GPT_ATOM1_CH04_ISR_API == STD_ON)||(GPT_ATOM1_CH05_ISR_API == STD_ON) */

#if ((GPT_ATOM1_CH06_ISR_API == STD_ON)||(GPT_ATOM1_CH07_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM1_IRQ3_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM1_IRQ3_ISR(void);
#endif
#endif /* End of (GPT_ATOM1_CH05_ISR_API == STD_ON)||(GPT_ATOM1_CH07_ISR_API == STD_ON) */

#if ((GPT_ATOM2_CH00_ISR_API == STD_ON)||(GPT_ATOM2_CH01_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM2_IRQ0_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM2_IRQ0_ISR(void);
#endif
#endif /* End of (GPT_ATOM2_CH00_ISR_API == STD_ON)||(GPT_ATOM2_CH01_ISR_API == STD_ON) */

#if ((GPT_ATOM2_CH02_ISR_API == STD_ON)||(GPT_ATOM2_CH03_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM2_IRQ1_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM2_IRQ1_ISR(void);
#endif
#endif /* End of (GPT_ATOM2_CH02_ISR_API == STD_ON)||(GPT_ATOM2_CH03_ISR_API == STD_ON) */

#if ((GPT_ATOM2_CH04_ISR_API == STD_ON)||(GPT_ATOM2_CH05_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM2_IRQ2_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM2_IRQ2_ISR(void);
#endif
#endif /* End of (GPT_ATOM2_CH04_ISR_API == STD_ON)||(GPT_ATOM2_CH05_ISR_API == STD_ON) */

#if ((GPT_ATOM2_CH06_ISR_API == STD_ON)||(GPT_ATOM2_CH07_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM2_IRQ3_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM2_IRQ3_ISR(void);
#endif
#endif /* End of (GPT_ATOM2_CH05_ISR_API == STD_ON)||(GPT_ATOM2_CH07_ISR_API == STD_ON) */

#if ((GPT_ATOM3_CH00_ISR_API == STD_ON)||(GPT_ATOM3_CH01_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM3_IRQ0_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM3_IRQ0_ISR(void);
#endif
#endif /* End of (GPT_ATOM3_CH00_ISR_API == STD_ON)||(GPT_ATOM3_CH01_ISR_API == STD_ON) */

#if ((GPT_ATOM3_CH02_ISR_API == STD_ON)||(GPT_ATOM3_CH03_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM3_IRQ1_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM3_IRQ1_ISR(void);
#endif
#endif /* End of (GPT_ATOM3_CH02_ISR_API == STD_ON)||(GPT_ATOM3_CH03_ISR_API == STD_ON) */

#if ((GPT_ATOM3_CH04_ISR_API == STD_ON)||(GPT_ATOM3_CH05_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM3_IRQ2_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM3_IRQ2_ISR(void);
#endif
#endif /* End of (GPT_ATOM3_CH04_ISR_API == STD_ON)||(GPT_ATOM3_CH05_ISR_API == STD_ON) */

#if ((GPT_ATOM3_CH06_ISR_API == STD_ON)||(GPT_ATOM3_CH07_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM3_IRQ3_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM3_IRQ3_ISR(void);
#endif
#endif /* End of (GPT_ATOM3_CH05_ISR_API == STD_ON)||(GPT_ATOM3_CH07_ISR_API == STD_ON) */

#if ((GPT_ATOM4_CH00_ISR_API == STD_ON)||(GPT_ATOM4_CH01_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM4_IRQ0_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM4_IRQ0_ISR(void);
#endif
#endif /* End of (GPT_ATOM4_CH00_ISR_API == STD_ON)||(GPT_ATOM4_CH01_ISR_API == STD_ON) */

#if ((GPT_ATOM4_CH02_ISR_API == STD_ON)||(GPT_ATOM4_CH03_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM4_IRQ1_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM4_IRQ1_ISR(void);
#endif
#endif /* End of (GPT_ATOM4_CH02_ISR_API == STD_ON)||(GPT_ATOM4_CH03_ISR_API == STD_ON) */

#if ((GPT_ATOM4_CH04_ISR_API == STD_ON)||(GPT_ATOM4_CH05_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM4_IRQ2_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM4_IRQ2_ISR(void);
#endif
#endif /* End of (GPT_ATOM4_CH04_ISR_API == STD_ON)||(GPT_ATOM4_CH05_ISR_API == STD_ON) */

#if ((GPT_ATOM4_CH06_ISR_API == STD_ON)||(GPT_ATOM4_CH07_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM4_IRQ3_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM4_IRQ3_ISR(void);
#endif
#endif /* End of (GPT_ATOM4_CH05_ISR_API == STD_ON)||(GPT_ATOM4_CH07_ISR_API == STD_ON) */

#if ((GPT_ATOM5_CH00_ISR_API == STD_ON)||(GPT_ATOM5_CH01_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM5_IRQ0_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM5_IRQ0_ISR(void);
#endif
#endif /* End of (GPT_ATOM5_CH00_ISR_API == STD_ON)||(GPT_ATOM5_CH01_ISR_API == STD_ON) */

#if ((GPT_ATOM5_CH02_ISR_API == STD_ON)||(GPT_ATOM5_CH03_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM5_IRQ1_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM5_IRQ1_ISR(void);
#endif
#endif /* End of (GPT_ATOM5_CH02_ISR_API == STD_ON)||(GPT_ATOM5_CH03_ISR_API == STD_ON) */

#if ((GPT_ATOM5_CH04_ISR_API == STD_ON)||(GPT_ATOM5_CH05_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM5_IRQ2_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM5_IRQ2_ISR(void);
#endif
#endif /* End of (GPT_ATOM5_CH04_ISR_API == STD_ON)||(GPT_ATOM5_CH05_ISR_API == STD_ON) */

#if ((GPT_ATOM5_CH06_ISR_API == STD_ON)||(GPT_ATOM5_CH07_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM5_IRQ3_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM5_IRQ3_ISR(void);
#endif
#endif /* End of (GPT_ATOM5_CH05_ISR_API == STD_ON)||(GPT_ATOM5_CH07_ISR_API == STD_ON) */

#if ((GPT_ATOM6_CH00_ISR_API == STD_ON)||(GPT_ATOM6_CH01_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM6_IRQ0_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM6_IRQ0_ISR(void);
#endif
#endif /* End of (GPT_ATOM6_CH00_ISR_API == STD_ON)||(GPT_ATOM6_CH01_ISR_API == STD_ON) */

#if ((GPT_ATOM6_CH02_ISR_API == STD_ON)||(GPT_ATOM6_CH03_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM6_IRQ1_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM6_IRQ1_ISR(void);
#endif
#endif /* End of (GPT_ATOM6_CH02_ISR_API == STD_ON)||(GPT_ATOM6_CH03_ISR_API == STD_ON) */

#if ((GPT_ATOM6_CH04_ISR_API == STD_ON)||(GPT_ATOM6_CH05_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM6_IRQ2_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM6_IRQ2_ISR(void);
#endif
#endif /* End of (GPT_ATOM6_CH04_ISR_API == STD_ON)||(GPT_ATOM6_CH05_ISR_API == STD_ON) */

#if ((GPT_ATOM6_CH06_ISR_API == STD_ON)||(GPT_ATOM6_CH07_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM6_IRQ3_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM6_IRQ3_ISR(void);
#endif
#endif /* End of (GPT_ATOM6_CH05_ISR_API == STD_ON)||(GPT_ATOM6_CH07_ISR_API == STD_ON) */

#if ((GPT_ATOM7_CH00_ISR_API == STD_ON)||(GPT_ATOM7_CH01_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM7_IRQ0_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM7_IRQ0_ISR(void);
#endif
#endif /* End of (GPT_ATOM7_CH00_ISR_API == STD_ON)||(GPT_ATOM7_CH01_ISR_API == STD_ON) */

#if ((GPT_ATOM7_CH02_ISR_API == STD_ON)||(GPT_ATOM7_CH03_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM7_IRQ1_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM7_IRQ1_ISR(void);
#endif
#endif /* End of (GPT_ATOM7_CH02_ISR_API == STD_ON)||(GPT_ATOM7_CH03_ISR_API == STD_ON) */

#if ((GPT_ATOM7_CH04_ISR_API == STD_ON)||(GPT_ATOM7_CH05_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM7_IRQ2_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM7_IRQ2_ISR(void);
#endif
#endif /* End of (GPT_ATOM7_CH04_ISR_API == STD_ON)||(GPT_ATOM7_CH05_ISR_API == STD_ON) */

#if ((GPT_ATOM7_CH06_ISR_API == STD_ON)||(GPT_ATOM7_CH07_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM7_IRQ3_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM7_IRQ3_ISR(void);
#endif
#endif /* End of (GPT_ATOM7_CH05_ISR_API == STD_ON)||(GPT_ATOM7_CH07_ISR_API == STD_ON) */

#if ((GPT_ATOM8_CH00_ISR_API == STD_ON)||(GPT_ATOM8_CH01_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM8_IRQ0_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM8_IRQ0_ISR(void);
#endif
#endif /* End of (GPT_ATOM8_CH00_ISR_API == STD_ON)||(GPT_ATOM8_CH01_ISR_API == STD_ON) */

#if ((GPT_ATOM8_CH02_ISR_API == STD_ON)||(GPT_ATOM8_CH03_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM8_IRQ1_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM8_IRQ1_ISR(void);
#endif
#endif /* End of (GPT_ATOM8_CH02_ISR_API == STD_ON)||(GPT_ATOM8_CH03_ISR_API == STD_ON) */

#if ((GPT_ATOM8_CH04_ISR_API == STD_ON)||(GPT_ATOM8_CH05_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM8_IRQ2_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM8_IRQ2_ISR(void);
#endif
#endif /* End of (GPT_ATOM8_CH04_ISR_API == STD_ON)||(GPT_ATOM8_CH05_ISR_API == STD_ON) */

#if ((GPT_ATOM8_CH06_ISR_API == STD_ON)||(GPT_ATOM8_CH07_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM8_IRQ3_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM8_IRQ3_ISR(void);
#endif
#endif /* End of (GPT_ATOM8_CH05_ISR_API == STD_ON)||(GPT_ATOM8_CH07_ISR_API == STD_ON) */

#if ((GPT_ATOM9_CH00_ISR_API == STD_ON)||(GPT_ATOM9_CH01_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM9_IRQ0_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM9_IRQ0_ISR(void);
#endif
#endif /* End of (GPT_ATOM9_CH00_ISR_API == STD_ON)||(GPT_ATOM9_CH01_ISR_API == STD_ON) */

#if ((GPT_ATOM9_CH02_ISR_API == STD_ON)||(GPT_ATOM9_CH03_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM9_IRQ1_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM9_IRQ1_ISR(void);
#endif
#endif /* End of (GPT_ATOM9_CH02_ISR_API == STD_ON)||(GPT_ATOM9_CH03_ISR_API == STD_ON) */

#if ((GPT_ATOM9_CH04_ISR_API == STD_ON)||(GPT_ATOM9_CH05_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM9_IRQ2_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM9_IRQ2_ISR(void);
#endif
#endif /* End of (GPT_ATOM9_CH04_ISR_API == STD_ON)||(GPT_ATOM9_CH05_ISR_API == STD_ON) */

#if ((GPT_ATOM9_CH06_ISR_API == STD_ON)||(GPT_ATOM9_CH07_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM9_IRQ3_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM9_IRQ3_ISR(void);
#endif
#endif /* End of (GPT_ATOM9_CH05_ISR_API == STD_ON)||(GPT_ATOM9_CH07_ISR_API == STD_ON) */

#define GPT_STOP_SEC_CODE_FAST
#include "Gpt_MemMap.h"
#endif /* GPT_TIMER_IP_GTM == STD_ON */
#endif /* GPT_GTM_IRQ_H */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
