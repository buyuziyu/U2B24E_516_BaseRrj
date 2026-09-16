/*====================================================================================================================*/
/* Project      = RH850/X2x AR4 MCAL Development                                                                      */
/* Module       = Pwm_TAUJ_Irq.c                                                                                      */
/*                                                                                                                    */
/*====================================================================================================================*/
/*                                                       COPYRIGHT                                                    */
/*====================================================================================================================*/
/* (c) 2020,2021,2023-2025 Renesas Electronics Corporation. All rights reserved.                                      */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains ISRs for all Timers of PWM Driver                                                               */
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
** 2.5.1: 30/06/2025 : Remove SW-VERSION in header comment                                                            **
** 2.5.0: 30/06/2025 : Update SW-VERSION for U2Ax Ver22.01.00(D) Final Release                                        **
** 2.4.0: 31/05/2025 : Update SW-VERSION for U2Cx Ver21.01.01 Final Release                                           **
** 2.3.2: 29/04/2025 : Update SW-VERSION for U2Ax Ver22.00.04 Beta Release                                            **
** 2.3.1: 31/03/2025 : Update SW-VERSION for U2BxE Ver22.00.02 Beta Release                                           **
** 2.3.0: 28/02/2025 : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release                        **
** 2.2.0: 31/12/2024 : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release                                  **
** 2.1.2: 31/10/2024 : Update SW-VERSION for Ver22.01.02 U2Bx, Ver22.00.05 U2Cx Beta2 Release                         **
** 2.1.1: 30/08/2024 : Update SW-VERSION for Ver22.01.01 U2Bx Beta Release                                            **
** 2.0.1: 25/10/2023 : Update version in header comment                                                               **
** 2.0.0: 05/07/2023 : Update from "Pwm_Mapping.h to "Pwm_MemMap.h"                                                   **
** 1.3.1: 02/07/2021 : Add QAC message 9.5.0                                                                          **
**                     Format source code to 120 characters                                                           **
**                     Improve Violation tag (remove START/END)                                                       **
**        15/05/2021 : Fixed Coding Rule and tailor space                                                             **
** 1.2.0: 28/07/2020 : Release                                                                                        **
** 1.1.1: 16/07/2020 : Changed "TAUJn_CHmm_CAT2_ISR" to                                                               **
**                               "PWM_ISR_CATEGORY_2 == STD_ON"                                                       **
** 1.1.0: 19/06/2020 : Release                                                                                        **
** 1.0.0: 24/03/2020 : Initial Version.                                                                               **
**                                                                                                                    */
/**********************************************************************************************************************/
/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for Pwm.h inclusion and macro definitions */
#include "Pwm.h"

#include "Pwm_Ram.h"
/* Included for declaration of the ISRs */
#include "Pwm_TAUJ_Irq.h"

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define PWM_TAUJ_IRQ_C_AR_RELEASE_MAJOR_VERSION    PWM_AR_RELEASE_MAJOR_VERSION_VALUE
#define PWM_TAUJ_IRQ_C_AR_RELEASE_MINOR_VERSION    PWM_AR_RELEASE_MINOR_VERSION_VALUE
#define PWM_TAUJ_IRQ_C_AR_RELEASE_REVISION_VERSION PWM_AR_RELEASE_REVISION_VERSION_VALUE

/* Module software version information */
#define PWM_TAUJ_IRQ_C_SW_MAJOR_VERSION            PWM_SW_MAJOR_VERSION_VALUE
#define PWM_TAUJ_IRQ_C_SW_MINOR_VERSION            PWM_SW_MINOR_VERSION_VALUE
#define PWM_TAUJ_IRQ_C_SW_PATCH_VERSION            PWM_SW_PATCH_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (PWM_TAUJ_IRQ_AR_RELEASE_MAJOR_VERSION != PWM_TAUJ_IRQ_C_AR_RELEASE_MAJOR_VERSION)
  #error "Pwm_TAUJ_Irq.c : Mismatch in Release Major Version"
#endif

#if (PWM_TAUJ_IRQ_AR_RELEASE_MINOR_VERSION != PWM_TAUJ_IRQ_C_AR_RELEASE_MINOR_VERSION)
  #error "Pwm_TAUJ_Irq.c : Mismatch in Release Minor Version"
#endif

#if (PWM_TAUJ_IRQ_AR_RELEASE_REVISION_VERSION != PWM_TAUJ_IRQ_C_AR_RELEASE_REVISION_VERSION)
  #error "Pwm_TAUJ_Irq.c : Mismatch in Release Revision Version"
#endif

#if (PWM_TAUJ_IRQ_SW_MAJOR_VERSION != PWM_TAUJ_IRQ_C_SW_MAJOR_VERSION)
  #error "Pwm_TAUJ_Irq.c : Mismatch in Software Major Version"
#endif

#if (PWM_TAUJ_IRQ_SW_MINOR_VERSION != PWM_TAUJ_IRQ_C_SW_MINOR_VERSION)
  #error "Pwm_TAUJ_Irq.c : Mismatch in Software Minor Version"
#endif

#if (PWM_TAUJ_IRQ_SW_PATCH_VERSION != PWM_TAUJ_IRQ_C_SW_PATCH_VERSION)
  #error "Pwm_TAUJ_Irq.c : Mismatch in Software Patch Version"
#endif
/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (1:1503)    : The function '%1s' is defined but is not used within this project.                           */
/* Rule                : MISRA C:2012 Rule-2.1, CERTCCM MSC07, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : This is accepted, due to the module's API is exported for user's usage.                      */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3408)    : '%s' has external linkage and is being defined without any previous declaration.             */
/* Rule                : MISRA C:2012 Rule-8.4, CERTCCM DCL07, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : It is accepted, due to the declaration will be taken care by Os                              */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:5087)    : Use of #include directive after code fragment.                                               */
/* Rule                : MISRA C:2012 Rule-20.1                                                                       */
/* JV-01 Justification : This is done as per Memory Requirement, (MEMMAP003 - Specification of Memory Mapping).       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/

/***********************************************************************************************************************
** Function Name        : TAUJn_CHm_ISR
**
** Service ID           : NA
**
** Description          : These are Interrupt routines for the timer TAUJn
**                        Channel m, where n represents the TAUJ Units and
**                        m represents channels associated for each Unit.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Non-Reentrant
**
** Input Parameters     : None
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return parameter     : None
**
** Preconditions        : None
**
** Global Variable(s)   : None
**
** Function(s) invoked  : Pwm_HW_TAUJ_Callback
**
** Registers Used       : None
**
** Reference ID         : PWM_DUD_ACT_059
***********************************************************************************************************************/
#if (PWM_TAUJ0_CH00_ISR_API == STD_ON)
#define PWM_START_SEC_CODE_FAST
#include "Pwm_MemMap.h"

/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUJ0_CH00_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
ISR(TAUJ0_CH00_CAT2_ISR)                                                                                                /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUJ0_CH00_ISR(void)                                                              /* PRQA S 1503 # JV-01 */
#endif
{
  Pwm_HW_TAUJ_Callback(PWM_TAUJ0_CH00);
}

#define PWM_STOP_SEC_CODE_FAST
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of PWM_TAUJ0_CH00_ISR_API == STD_ON */

#if (PWM_TAUJ0_CH01_ISR_API == STD_ON)
#define PWM_START_SEC_CODE_FAST
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUJ0_CH01_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
ISR(TAUJ0_CH01_CAT2_ISR)                                                                                                /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUJ0_CH01_ISR(void)                                                              /* PRQA S 1503 # JV-01 */
#endif
{
  Pwm_HW_TAUJ_Callback(PWM_TAUJ0_CH01);
}

#define PWM_STOP_SEC_CODE_FAST
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of PWM_TAUJ0_CH01_ISR_API == STD_ON */

#if (PWM_TAUJ0_CH02_ISR_API == STD_ON)
#define PWM_START_SEC_CODE_FAST
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUJ0_CH02_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
ISR(TAUJ0_CH02_CAT2_ISR)                                                                                                /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUJ0_CH02_ISR(void)                                                              /* PRQA S 1503 # JV-01 */
#endif
{
  Pwm_HW_TAUJ_Callback(PWM_TAUJ0_CH02);
}

#define PWM_STOP_SEC_CODE_FAST
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of PWM_TAUJ0_CH02_ISR_API == STD_ON */

#if (PWM_TAUJ0_CH03_ISR_API == STD_ON)
#define PWM_START_SEC_CODE_FAST
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUJ0_CH03_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
ISR(TAUJ0_CH03_CAT2_ISR)                                                                                                /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUJ0_CH03_ISR(void)                                                              /* PRQA S 1503 # JV-01 */
#endif
{
  Pwm_HW_TAUJ_Callback(PWM_TAUJ0_CH03);
}

#define PWM_STOP_SEC_CODE_FAST
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of PWM_TAUJ0_CH03_ISR_API == STD_ON */

#if (PWM_TAUJ1_CH00_ISR_API == STD_ON)
#define PWM_START_SEC_CODE_FAST
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUJ1_CH00_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
ISR(TAUJ1_CH00_CAT2_ISR)                                                                                                /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUJ1_CH00_ISR(void)                                                              /* PRQA S 1503 # JV-01 */
#endif
{
  Pwm_HW_TAUJ_Callback(PWM_TAUJ1_CH00);
}

#define PWM_STOP_SEC_CODE_FAST
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of PWM_TAUJ1_CH00_ISR_API == STD_ON */

#if (PWM_TAUJ1_CH01_ISR_API == STD_ON)
#define PWM_START_SEC_CODE_FAST
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUJ1_CH01_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
ISR(TAUJ1_CH01_CAT2_ISR)                                                                                                /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUJ1_CH01_ISR(void)                                                              /* PRQA S 1503 # JV-01 */
#endif
{
  Pwm_HW_TAUJ_Callback(PWM_TAUJ1_CH01);
}

#define PWM_STOP_SEC_CODE_FAST
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of PWM_TAUJ1_CH01_ISR_API == STD_ON */

#if (PWM_TAUJ1_CH02_ISR_API == STD_ON)
#define PWM_START_SEC_CODE_FAST
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUJ1_CH02_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
ISR(TAUJ1_CH02_CAT2_ISR)                                                                                                /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUJ1_CH02_ISR(void)                                                              /* PRQA S 1503 # JV-01 */
#endif
{
  Pwm_HW_TAUJ_Callback(PWM_TAUJ1_CH02);
}

#define PWM_STOP_SEC_CODE_FAST
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of PWM_TAUJ1_CH02_ISR_API == STD_ON */

#if (PWM_TAUJ1_CH03_ISR_API == STD_ON)
#define PWM_START_SEC_CODE_FAST
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUJ1_CH03_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
ISR(TAUJ1_CH03_CAT2_ISR)                                                                                                /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUJ1_CH03_ISR(void)                                                              /* PRQA S 1503 # JV-01 */
#endif
{
  Pwm_HW_TAUJ_Callback(PWM_TAUJ1_CH03);
}

#define PWM_STOP_SEC_CODE_FAST
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of PWM_TAUJ1_CH03_ISR_API == STD_ON */

#if (PWM_TAUJ2_CH00_ISR_API == STD_ON)
#define PWM_START_SEC_CODE_FAST
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUJ2_CH00_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
ISR(TAUJ2_CH00_CAT2_ISR)                                                                                                /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUJ2_CH00_ISR(void)                                                              /* PRQA S 1503 # JV-01 */
#endif
{
  Pwm_HW_TAUJ_Callback(PWM_TAUJ2_CH00);
}

#define PWM_STOP_SEC_CODE_FAST
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of PWM_TAUJ2_CH00_ISR_API == STD_ON */

#if (PWM_TAUJ2_CH01_ISR_API == STD_ON)
#define PWM_START_SEC_CODE_FAST
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUJ2_CH01_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
ISR(TAUJ2_CH01_CAT2_ISR)                                                                                                /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUJ2_CH01_ISR(void)                                                              /* PRQA S 1503 # JV-01 */
#endif
{
  Pwm_HW_TAUJ_Callback(PWM_TAUJ2_CH01);
}

#define PWM_STOP_SEC_CODE_FAST
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of PWM_TAUJ2_CH01_ISR_API == STD_ON */

#if (PWM_TAUJ2_CH02_ISR_API == STD_ON)
#define PWM_START_SEC_CODE_FAST
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUJ2_CH02_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
ISR(TAUJ2_CH02_CAT2_ISR)                                                                                                /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUJ2_CH02_ISR(void)                                                              /* PRQA S 1503 # JV-01 */
#endif
{
  Pwm_HW_TAUJ_Callback(PWM_TAUJ2_CH02);
}

#define PWM_STOP_SEC_CODE_FAST
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of PWM_TAUJ2_CH02_ISR_API == STD_ON */

#if (PWM_TAUJ2_CH03_ISR_API == STD_ON)
#define PWM_START_SEC_CODE_FAST
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUJ2_CH03_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
ISR(TAUJ2_CH03_CAT2_ISR)                                                                                                /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUJ2_CH03_ISR(void)                                                              /* PRQA S 1503 # JV-01 */
#endif
{
  Pwm_HW_TAUJ_Callback(PWM_TAUJ2_CH03);
}

#define PWM_STOP_SEC_CODE_FAST
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of PWM_TAUJ2_CH03_ISR_API == STD_ON */

#if (PWM_TAUJ3_CH00_ISR_API == STD_ON)
#define PWM_START_SEC_CODE_FAST
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUJ3_CH00_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
ISR(TAUJ3_CH00_CAT2_ISR)                                                                                                /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUJ3_CH00_ISR(void)                                                              /* PRQA S 1503 # JV-01 */
#endif
{
  Pwm_HW_TAUJ_Callback(PWM_TAUJ3_CH00);
}

#define PWM_STOP_SEC_CODE_FAST
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of PWM_TAUJ3_CH00_ISR_API == STD_ON */

#if (PWM_TAUJ3_CH01_ISR_API == STD_ON)
#define PWM_START_SEC_CODE_FAST
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUJ3_CH01_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
ISR(TAUJ3_CH01_CAT2_ISR)                                                                                                /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUJ3_CH01_ISR(void)                                                              /* PRQA S 1503 # JV-01 */
#endif
{
  Pwm_HW_TAUJ_Callback(PWM_TAUJ3_CH01);
}

#define PWM_STOP_SEC_CODE_FAST
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of PWM_TAUJ3_CH01_ISR_API == STD_ON */

#if (PWM_TAUJ3_CH02_ISR_API == STD_ON)
#define PWM_START_SEC_CODE_FAST
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUJ3_CH02_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
ISR(TAUJ3_CH02_CAT2_ISR)                                                                                                /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUJ3_CH02_ISR(void)                                                              /* PRQA S 1503 # JV-01 */
#endif
{
  Pwm_HW_TAUJ_Callback(PWM_TAUJ3_CH02);
}

#define PWM_STOP_SEC_CODE_FAST
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of PWM_TAUJ3_CH02_ISR_API == STD_ON */

#if (PWM_TAUJ3_CH03_ISR_API == STD_ON)
#define PWM_START_SEC_CODE_FAST
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUJ3_CH03_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
ISR(TAUJ3_CH03_CAT2_ISR)                                                                                                /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, PWM_CODE_FAST) TAUJ3_CH03_ISR(void)                                                              /* PRQA S 1503 # JV-01 */
#endif
{
  Pwm_HW_TAUJ_Callback(PWM_TAUJ3_CH03);
}

#define PWM_STOP_SEC_CODE_FAST
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of PWM_TAUJ3_CH03_ISR_API == STD_ON */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
