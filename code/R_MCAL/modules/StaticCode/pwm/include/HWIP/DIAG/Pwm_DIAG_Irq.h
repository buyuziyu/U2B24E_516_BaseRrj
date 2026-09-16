/*====================================================================================================================*/
/* Project      = RH850/X2x AR4 MCAL Development                                                                      */
/* Module       = Pwm_DIAG_Irq.h                                                                                      */
/*                                                                                                                    */
/*====================================================================================================================*/
/*                                              COPYRIGHT                                                             */
/*====================================================================================================================*/
/* (c) 2021-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* ISR functions of the PWM Driver Component                                                                          */
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
 * 2.3.1: 31/03/2025 : Update SW-VERSION for U2Ax Ver22.00.03 Beta2 Release                                           **
 * 2.3.0: 28/02/2025 : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release                        **
 * 2.2.0: 31/12/2024 : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release                                  **
 * 2.1.2: 31/10/2024 : Update SW-VERSION for Ver22.00.05 U2Cx Beta2 Release                                           **
 * 2.0.2: 14/12/2023 : Update version in header comment                                                               **
 * 2.0.1: 25/10/2023 : Update version in header comment                                                               **
 * 2.0.0: 05/07/2023 : Update from "Pwm_Mapping.h to "Pwm_MemMap.h". Remove #ifdef PWM_INSTANCE_INDEX                 **
 *                     Remove message 0841                                                                            **
 * 1.0.0: 23/08/2021 : Initial Version.                                                                               **
 *                                                                                                                    */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/

#ifndef PWM_DIAG_IRQ_H
#define PWM_DIAG_IRQ_H

/***********************************************************************************************************************
**                                              Include Section                                                       **
***********************************************************************************************************************/
/* Included for interrupt category definitions */
#include "Os.h"

/***********************************************************************************************************************
**                                              Version Information                                                   **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define PWM_DIAG_IRQ_AR_RELEASE_MAJOR_VERSION       PWM_AR_RELEASE_MAJOR_VERSION
#define PWM_DIAG_IRQ_AR_RELEASE_MINOR_VERSION       PWM_AR_RELEASE_MINOR_VERSION
#define PWM_DIAG_IRQ_AR_RELEASE_REVISION_VERSION    PWM_AR_RELEASE_REVISION_VERSION

/* Module software version information */
#define PWM_DIAG_IRQ_SW_MAJOR_VERSION               PWM_SW_MAJOR_VERSION
#define PWM_DIAG_IRQ_SW_MINOR_VERSION               PWM_SW_MINOR_VERSION
#define PWM_DIAG_IRQ_SW_PATCH_VERSION               PWM_SW_PATCH_VERSION

/***********************************************************************************************************************
**                                              Function Prototypes                                                   **
***********************************************************************************************************************/
#if (PWM_DIAG_UNIT_USED == STD_ON)
#define PWM_START_SEC_CODE_FAST
#include "Pwm_MemMap.h"

#if (PWGCG00_ISR_API == STD_ON)
#if defined (Os_PWGCG00_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
#else /* Defines the CAT1 interrupt mapping */
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) PWGCG00_ISR(void);
#endif
#endif /* End of PWGCG00_ISR_API == STD_ON */
#if (PWGCG01_ISR_API == STD_ON)
#if defined (Os_PWGCG01_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
#else /* Defines the CAT1 interrupt mapping */
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) PWGCG01_ISR(void);
#endif
#endif /* End of PWGCG01_ISR_API == STD_ON */
#if (PWGCG02_ISR_API == STD_ON)
#if defined (Os_PWGCG02_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
#else /* Defines the CAT1 interrupt mapping */
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) PWGCG02_ISR(void);
#endif
#endif /* End of PWGCG02_ISR_API == STD_ON */
#if (PWGCG10_ISR_API == STD_ON)
#if defined (Os_PWGCG10_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
#else /* Defines the CAT1 interrupt mapping */
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) PWGCG10_ISR(void);
#endif
#endif /* End of PWGCG10_ISR_API == STD_ON */
#if (PWGCG11_ISR_API == STD_ON)
#if defined (Os_PWGCG11_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
#else /* Defines the CAT1 interrupt mapping */
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) PWGCG11_ISR(void);
#endif
#endif /* End of PWGCG11_ISR_API == STD_ON */
#if (PWGCG12_ISR_API == STD_ON)
#if defined (Os_PWGCG12_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
#else /* Defines the CAT1 interrupt mapping */
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) PWGCG12_ISR(void);
#endif
#endif /* End of PWGCG12_ISR_API == STD_ON */
#if (PWGCG20_ISR_API == STD_ON)
#if defined (Os_PWGCG20_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
#else /* Defines the CAT1 interrupt mapping */
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) PWGCG20_ISR(void);
#endif
#endif /* End of PWGCG20_ISR_API == STD_ON */
#if (PWGCG21_ISR_API == STD_ON)
#if defined (Os_PWGCG21_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
#else /* Defines the CAT1 interrupt mapping */
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) PWGCG21_ISR(void);
#endif
#endif /* End of PWGCG21_ISR_API == STD_ON */
#if (PWGCG22_ISR_API == STD_ON)
#if defined (Os_PWGCG22_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
#else /* Defines the CAT1 interrupt mapping */
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) PWGCG22_ISR(void);
#endif
#endif /* End of PWGCG22_ISR_API == STD_ON */
#if (PWGCG30_ISR_API == STD_ON)
#if defined (Os_PWGCG30_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
#else /* Defines the CAT1 interrupt mapping */
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) PWGCG30_ISR(void);
#endif
#endif /* End of PWGCG30_ISR_API == STD_ON */
#if (PWGCG31_ISR_API == STD_ON)
#if defined (Os_PWGCG31_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
#else /* Defines the CAT1 interrupt mapping */
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) PWGCG31_ISR(void);
#endif
#endif /* End of PWGCG31_ISR_API == STD_ON */
#if (PWGCG32_ISR_API == STD_ON)
#if defined (Os_PWGCG32_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
#else /* Defines the CAT1 interrupt mapping */
extern _INTERRUPT_ FUNC(void, PWM_CODE_FAST) PWGCG32_ISR(void);
#endif
#endif /* End of PWGCG32_ISR_API == STD_ON */

#define PWM_STOP_SEC_CODE_FAST
#include "Pwm_MemMap.h"

#endif /* End of PWM_DIAG_UNIT_USED == STD_ON */
#endif /* End of PWM_DIAG_IRQ_H */
/***********************************************************************************************************************
**                                              End of File                                                           **
***********************************************************************************************************************/
