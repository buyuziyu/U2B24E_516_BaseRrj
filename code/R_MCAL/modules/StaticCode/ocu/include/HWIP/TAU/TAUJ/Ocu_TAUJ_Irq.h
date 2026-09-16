/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2X MCAL Components                                                                 */
/* Module       = Ocu_TAUJ_Irq.h                                                                                      */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2023-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains ISRs for all Timers of OCU Driver                                                               */
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
 *  1.4.0  30/05/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.01
 *  1.3.1  31/03/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 and RH850/U2Bx-E MCAL Ver22.00.02 Release
 *  1.3.0  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 *  1.2.0  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 *  1.0.1  23/10/2023  : Change from OCU_AR_RELEASE_MAJOR_VERSION_VALUE to OCU_AR_RELEASE_MAJOR_VERSION
                         Change from OCU_AR_RELEASE_MINOR_VERSION_VALUE to OCU_AR_RELEASE_MINOR_VERSION
                         Change from OCU_AR_RELEASE_REVISION_VERSION_VALUE to OCU_AR_RELEASE_REVISION_VERSION
           17/10/2023  : Add new QAC message 1534
 *  1.0.0  31/03/2023  : Initial Version.
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/

#ifndef OCU_TAUJ_IRQ_H
#define OCU_TAUJ_IRQ_H

/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for using Std Type(e.g. STD_ON), Compiler Macros(e.g. P2FUNC), Platform Types(e.g. uint8) */
#include "Std_Types.h"
/* Included for interrupt category definitions */
#include "Os.h"
/* Included for OCU module specific definitions */
#include "Ocu_Cfg.h"
/* Included for macro definitions (e.g. Service IDs)*/
#include "Ocu.h"
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR Release version information */
#define OCU_TAUJ_IRQ_AR_RELEASE_MAJOR_VERSION    OCU_AR_RELEASE_MAJOR_VERSION
#define OCU_TAUJ_IRQ_AR_RELEASE_MINOR_VERSION    OCU_AR_RELEASE_MINOR_VERSION
#define OCU_TAUJ_IRQ_AR_RELEASE_REVISION_VERSION OCU_AR_RELEASE_REVISION_VERSION
/* File version information */
#define OCU_TAUJ_IRQ_SW_MAJOR_VERSION            OCU_SW_MAJOR_VERSION
#define OCU_TAUJ_IRQ_SW_MINOR_VERSION            OCU_SW_MINOR_VERSION
#define OCU_TAUJ_IRQ_SW_PATCH_VERSION            OCU_SW_PATCH_VERSION
/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/
#if (OCU_TIMER_IP_TAUJ == STD_ON)
#define OCU_START_SEC_CODE_FAST
#include "Ocu_MemMap.h"

#if (OCU_TAUJ0_CH01_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUJ0_CH01_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) TAUJ0_CH01_ISR(void);
#endif
#endif /* End of OCU_TAUJ0_CH01_ISR_API == STD_ON */

#if (OCU_TAUJ0_CH03_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUJ0_CH03_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) TAUJ0_CH03_ISR(void);
#endif
#endif /* End of OCU_TAUJ0_CH03_ISR_API == STD_ON */

#if (OCU_TAUJ1_CH01_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUJ1_CH01_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) TAUJ1_CH01_ISR(void);
#endif
#endif /* End of OCU_TAUJ1_CH01_ISR_API == STD_ON */

#if (OCU_TAUJ1_CH03_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUJ1_CH03_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) TAUJ1_CH03_ISR(void);
#endif
#endif /* End of OCU_TAUJ1_CH03_ISR_API == STD_ON */

#if (OCU_TAUJ2_CH01_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUJ2_CH01_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) TAUJ2_CH01_ISR(void);
#endif
#endif /* End of OCU_TAUJ2_CH01_ISR_API == STD_ON */

#if (OCU_TAUJ2_CH03_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUJ2_CH03_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) TAUJ2_CH03_ISR(void);
#endif
#endif /* End of OCU_TAUJ2_CH03_ISR_API == STD_ON */

#if (OCU_TAUJ3_CH01_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUJ3_CH01_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) TAUJ3_CH01_ISR(void);
#endif
#endif /* End of OCU_TAUJ3_CH01_ISR_API == STD_ON */

#if (OCU_TAUJ3_CH03_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUJ3_CH03_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, OCU_CODE_FAST) TAUJ3_CH03_ISR(void);
#endif
#endif /* End of OCU_TAUJ3_CH03_ISR_API == STD_ON */

#define OCU_STOP_SEC_CODE_FAST
#include "Ocu_MemMap.h"

#endif /* OCU_TIMER_IP_TAUJ == STD_ON */
#endif /* OCU_TAUJ_IRQ_HEADER */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
