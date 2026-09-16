/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Icu_GTM_Irq.c                                                                                       */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2024-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains ISRs for all Timers of ICU Driver                                                               */
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
 * 2.3.1:  31/03/2025  : As part of support QAC 11.6.0, following changes are made:
                         1. Remove 3214
 * 2.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release 
 * 2.1.2:  31/10/2024  : Initial Version
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for Icu.h inclusion and macro definitions */
#include "Icu.h"
/* Included for declaration of the Icu_CbkNotification() function */
#include "Icu_GTM_LLDriver.h"
/* Included for declaration of the ISRs */
#include "Icu_GTM_Irq.h"
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define ICU_GTM_IRQ_C_AR_RELEASE_MAJOR_VERSION    ICU_AR_RELEASE_MAJOR_VERSION_VALUE
#define ICU_GTM_IRQ_C_AR_RELEASE_MINOR_VERSION    ICU_AR_RELEASE_MINOR_VERSION_VALUE
#define ICU_GTM_IRQ_C_AR_RELEASE_REVISION_VERSION ICU_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define ICU_GTM_IRQ_C_SW_MAJOR_VERSION            ICU_SW_MAJOR_VERSION_VALUE
#define ICU_GTM_IRQ_C_SW_MINOR_VERSION            ICU_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (ICU_GTM_TIMER_UNIT_USED == STD_ON)
#if (ICU_GTM_IRQ_AR_RELEASE_MAJOR_VERSION != ICU_GTM_IRQ_C_AR_RELEASE_MAJOR_VERSION)
#error "Icu_Gtm_Irq.c : Mismatch in Release Major Version"
#endif

#if (ICU_GTM_IRQ_AR_RELEASE_MINOR_VERSION != ICU_GTM_IRQ_C_AR_RELEASE_MINOR_VERSION)
#error "Icu_Gtm_Irq.c : Mismatch in Release Minor Version"
#endif

#if (ICU_GTM_IRQ_AR_RELEASE_REVISION_VERSION != ICU_GTM_IRQ_C_AR_RELEASE_REVISION_VERSION)
#error "Icu_Gtm_Irq.c : Mismatch in Release Patch Version"
#endif

#if (ICU_GTM_IRQ_SW_MAJOR_VERSION != ICU_GTM_IRQ_C_SW_MAJOR_VERSION)
#error "Icu_Gtm_Irq.c : Mismatch in Software Major Version"
#endif

#if (ICU_GTM_IRQ_SW_MINOR_VERSION != ICU_GTM_IRQ_C_SW_MINOR_VERSION)
#error "Icu_Gtm_Irq.c : Mismatch in Software Minor Version"
#endif

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
** Function Name        : GTM_TIMn_CHm_ISR
**
** Service ID           : NA
**
** Description          : These are Interrupt routines for the timer GTM TIM, cluster n
**                        Channel m, where m represents channels associated for
**                        each n cluster.
**
** Sync/Async           : Synchronous
**
** Reentrancy           : Reentrant
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
** Function(s) invoked  : Icu_Gtm_TimerIsr
**
** Registers Used       : None
**
** Reference ID         : ICU_DUD_ACT_107
***********************************************************************************************************************/
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"

#if (ICU_GTM_TIM0_CH0_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM0_CH0_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TIM0_CH0_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM0_CH0_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_Gtm_TimerIsr(ICU_GTM_TIM0_CH0);
}
#endif

#if (ICU_GTM_TIM0_CH1_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM0_CH1_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TIM0_CH1_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM0_CH1_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_Gtm_TimerIsr(ICU_GTM_TIM0_CH1);
}
#endif

#if (ICU_GTM_TIM0_CH2_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM0_CH2_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TIM0_CH2_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM0_CH2_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_Gtm_TimerIsr(ICU_GTM_TIM0_CH2);
}
#endif

#if (ICU_GTM_TIM0_CH3_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM0_CH3_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TIM0_CH3_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM0_CH3_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_Gtm_TimerIsr(ICU_GTM_TIM0_CH3);
}
#endif

#if (ICU_GTM_TIM0_CH4_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM0_CH4_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TIM0_CH4_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM0_CH4_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_Gtm_TimerIsr(ICU_GTM_TIM0_CH4);
}
#endif

#if (ICU_GTM_TIM0_CH5_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM0_CH5_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TIM0_CH5_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM0_CH5_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_Gtm_TimerIsr(ICU_GTM_TIM0_CH5);
}
#endif

#if (ICU_GTM_TIM0_CH6_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM0_CH6_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TIM0_CH6_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM0_CH6_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_Gtm_TimerIsr(ICU_GTM_TIM0_CH6);
}
#endif

#if (ICU_GTM_TIM0_CH7_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM0_CH7_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TIM0_CH7_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM0_CH7_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_Gtm_TimerIsr(ICU_GTM_TIM0_CH7);
}
#endif

#if (ICU_GTM_TIM1_CH0_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM1_CH0_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TIM1_CH0_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM1_CH0_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_Gtm_TimerIsr(ICU_GTM_TIM1_CH0);
}
#endif

#if (ICU_GTM_TIM1_CH1_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM1_CH1_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TIM1_CH1_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM1_CH1_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_Gtm_TimerIsr(ICU_GTM_TIM1_CH1);
}
#endif

#if (ICU_GTM_TIM1_CH2_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM1_CH2_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TIM1_CH2_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM1_CH2_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_Gtm_TimerIsr(ICU_GTM_TIM1_CH2);
}
#endif

#if (ICU_GTM_TIM1_CH3_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM1_CH3_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TIM1_CH3_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM1_CH3_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_Gtm_TimerIsr(ICU_GTM_TIM1_CH3);
}
#endif

#if (ICU_GTM_TIM1_CH4_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM1_CH4_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TIM1_CH4_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM1_CH4_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_Gtm_TimerIsr(ICU_GTM_TIM1_CH4);
}
#endif

#if (ICU_GTM_TIM1_CH5_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM1_CH5_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TIM1_CH5_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM1_CH5_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_Gtm_TimerIsr(ICU_GTM_TIM1_CH5);
}
#endif

#if (ICU_GTM_TIM1_CH6_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM1_CH6_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TIM1_CH6_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM1_CH6_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_Gtm_TimerIsr(ICU_GTM_TIM1_CH6);
}
#endif

#if (ICU_GTM_TIM1_CH7_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM1_CH7_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TIM1_CH7_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM1_CH7_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_Gtm_TimerIsr(ICU_GTM_TIM1_CH7);
}
#endif

#if (ICU_GTM_TIM2_CH0_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM2_CH0_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TIM2_CH0_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM2_CH0_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_Gtm_TimerIsr(ICU_GTM_TIM2_CH0);
}
#endif

#if (ICU_GTM_TIM2_CH1_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM2_CH1_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TIM2_CH1_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM2_CH1_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_Gtm_TimerIsr(ICU_GTM_TIM2_CH1);
}
#endif

#if (ICU_GTM_TIM2_CH2_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM2_CH2_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TIM2_CH2_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM2_CH2_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_Gtm_TimerIsr(ICU_GTM_TIM2_CH2);
}
#endif

#if (ICU_GTM_TIM2_CH3_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM2_CH3_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TIM2_CH3_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM2_CH3_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_Gtm_TimerIsr(ICU_GTM_TIM2_CH3);
}
#endif

#if (ICU_GTM_TIM2_CH4_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM2_CH4_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TIM2_CH4_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM2_CH4_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_Gtm_TimerIsr(ICU_GTM_TIM2_CH4);
}
#endif

#if (ICU_GTM_TIM2_CH5_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM2_CH5_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TIM2_CH5_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM2_CH5_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_Gtm_TimerIsr(ICU_GTM_TIM2_CH5);
}
#endif

#if (ICU_GTM_TIM2_CH6_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM2_CH6_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TIM2_CH6_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM2_CH6_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_Gtm_TimerIsr(ICU_GTM_TIM2_CH6);
}
#endif

#if (ICU_GTM_TIM2_CH7_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM2_CH7_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TIM2_CH7_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM2_CH7_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_Gtm_TimerIsr(ICU_GTM_TIM2_CH7);
}
#endif

#if (ICU_GTM_TIM3_CH0_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM3_CH0_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TIM3_CH0_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM3_CH0_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_Gtm_TimerIsr(ICU_GTM_TIM3_CH0);
}
#endif

#if (ICU_GTM_TIM3_CH1_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM3_CH1_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TIM3_CH1_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM3_CH1_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_Gtm_TimerIsr(ICU_GTM_TIM3_CH1);
}
#endif

#if (ICU_GTM_TIM3_CH2_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM3_CH2_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TIM3_CH2_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM3_CH2_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_Gtm_TimerIsr(ICU_GTM_TIM3_CH2);
}
#endif

#if (ICU_GTM_TIM3_CH3_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM3_CH3_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TIM3_CH3_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM3_CH3_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_Gtm_TimerIsr(ICU_GTM_TIM3_CH3);
}
#endif

#if (ICU_GTM_TIM3_CH4_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM3_CH4_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TIM3_CH4_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM3_CH4_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_Gtm_TimerIsr(ICU_GTM_TIM3_CH4);
}
#endif

#if (ICU_GTM_TIM3_CH5_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM3_CH5_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TIM3_CH5_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM3_CH5_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_Gtm_TimerIsr(ICU_GTM_TIM3_CH5);
}
#endif

#if (ICU_GTM_TIM3_CH6_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM3_CH6_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TIM3_CH6_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM3_CH6_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_Gtm_TimerIsr(ICU_GTM_TIM3_CH6);
}
#endif

#if (ICU_GTM_TIM3_CH7_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM3_CH7_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TIM3_CH7_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM3_CH7_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_Gtm_TimerIsr(ICU_GTM_TIM3_CH7);
}
#endif

#if (ICU_GTM_TIM4_CH0_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM4_CH0_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TIM4_CH0_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM4_CH0_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_Gtm_TimerIsr(ICU_GTM_TIM4_CH0);
}
#endif

#if (ICU_GTM_TIM4_CH1_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM4_CH1_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TIM4_CH1_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM4_CH1_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_Gtm_TimerIsr(ICU_GTM_TIM4_CH1);
}
#endif

#if (ICU_GTM_TIM4_CH2_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM4_CH2_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TIM4_CH2_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM4_CH2_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_Gtm_TimerIsr(ICU_GTM_TIM4_CH2);
}
#endif

#if (ICU_GTM_TIM4_CH3_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM4_CH3_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TIM4_CH3_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM4_CH3_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_Gtm_TimerIsr(ICU_GTM_TIM4_CH3);
}
#endif

#if (ICU_GTM_TIM4_CH4_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM4_CH4_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TIM4_CH4_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM4_CH4_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_Gtm_TimerIsr(ICU_GTM_TIM4_CH4);
}
#endif

#if (ICU_GTM_TIM4_CH5_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM4_CH5_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TIM4_CH5_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM4_CH5_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_Gtm_TimerIsr(ICU_GTM_TIM4_CH5);
}
#endif

#if (ICU_GTM_TIM4_CH6_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM4_CH6_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TIM4_CH6_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM4_CH6_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_Gtm_TimerIsr(ICU_GTM_TIM4_CH6);
}
#endif

#if (ICU_GTM_TIM4_CH7_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM4_CH7_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TIM4_CH7_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM4_CH7_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_Gtm_TimerIsr(ICU_GTM_TIM4_CH7);
}
#endif

#if (ICU_GTM_TIM5_CH0_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM5_CH0_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TIM5_CH0_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM5_CH0_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_Gtm_TimerIsr(ICU_GTM_TIM5_CH0);
}
#endif

#if (ICU_GTM_TIM5_CH1_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM5_CH1_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TIM5_CH1_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM5_CH1_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_Gtm_TimerIsr(ICU_GTM_TIM5_CH1);
}
#endif

#if (ICU_GTM_TIM5_CH2_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM5_CH2_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TIM5_CH2_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM5_CH2_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_Gtm_TimerIsr(ICU_GTM_TIM5_CH2);
}
#endif

#if (ICU_GTM_TIM5_CH3_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM5_CH3_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TIM5_CH3_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM5_CH3_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_Gtm_TimerIsr(ICU_GTM_TIM5_CH3);
}
#endif

#if (ICU_GTM_TIM5_CH4_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM5_CH4_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TIM5_CH4_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM5_CH4_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_Gtm_TimerIsr(ICU_GTM_TIM5_CH4);
}
#endif

#if (ICU_GTM_TIM5_CH5_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM5_CH5_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TIM5_CH5_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM5_CH5_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_Gtm_TimerIsr(ICU_GTM_TIM5_CH5);
}
#endif

#if (ICU_GTM_TIM5_CH6_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM5_CH6_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TIM5_CH6_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM5_CH6_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_Gtm_TimerIsr(ICU_GTM_TIM5_CH6);
}
#endif

#if (ICU_GTM_TIM5_CH7_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM5_CH7_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TIM5_CH7_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM5_CH7_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_Gtm_TimerIsr(ICU_GTM_TIM5_CH7);
}
#endif

#if (ICU_GTM_TIM6_CH0_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM6_CH0_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TIM6_CH0_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM6_CH0_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_Gtm_TimerIsr(ICU_GTM_TIM6_CH0);
}
#endif

#if (ICU_GTM_TIM6_CH1_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM6_CH1_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TIM6_CH1_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM6_CH1_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_Gtm_TimerIsr(ICU_GTM_TIM6_CH1);
}
#endif

#if (ICU_GTM_TIM6_CH2_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM6_CH2_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TIM6_CH2_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM6_CH2_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_Gtm_TimerIsr(ICU_GTM_TIM6_CH2);
}
#endif

#if (ICU_GTM_TIM6_CH3_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM6_CH3_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TIM6_CH3_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM6_CH3_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_Gtm_TimerIsr(ICU_GTM_TIM6_CH3);
}
#endif

#if (ICU_GTM_TIM6_CH4_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM6_CH4_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TIM6_CH4_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM6_CH4_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_Gtm_TimerIsr(ICU_GTM_TIM6_CH4);
}
#endif

#if (ICU_GTM_TIM6_CH5_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM6_CH5_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TIM6_CH5_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM6_CH5_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_Gtm_TimerIsr(ICU_GTM_TIM6_CH5);
}
#endif

#if (ICU_GTM_TIM6_CH6_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM6_CH6_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TIM6_CH6_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM6_CH6_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_Gtm_TimerIsr(ICU_GTM_TIM6_CH6);
}
#endif

#if (ICU_GTM_TIM6_CH7_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_GTM_TIM6_CH7_ISR_API) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TIM6_CH7_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) GTM_TIM6_CH7_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_Gtm_TimerIsr(ICU_GTM_TIM6_CH7);
}
#endif

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* #if (ICU_GTM_TIMER_UNIT_USED == STD_ON) */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
