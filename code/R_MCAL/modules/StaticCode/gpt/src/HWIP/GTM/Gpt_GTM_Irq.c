/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Gpt_GTM_Irq.c                                                                                       */
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
 *  2.4.1  30/06/2025  : As part of GTM HWIP support for U2Bx, following changes are made:
 *                       Correct the interrupt for TOMx_CH14_ISR_API and TOMx_CH15_ISR_API (x:0 to 4)
 *  2.4.0  30/06/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.01.00 (D) release
 *  2.3.2  25/04/2025  : As part of GTM HWIP support for U2Ax, following changes are made:
 *                       1. Modify interrupt function to improve interrupt merge for GTM
 *  2.3.1  31/03/2025  : Update SW-VERSION for RH850/U2BxE MCAL Ver22.00.02/Ver22.00.02.D Release
 *  2.3.0  28/02/2025  : As part of support U2BxE HWUM 0.5, following changes is made:
 *                       1. Add interrupt mapping for channel ATOM8xy, ATOM9xy (with xy = 00 to 07)
 *  2.2.0  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 *  2.1.2  31/10/2024  : Initial Version
 */
/**********************************************************************************************************************/
/***********************************************************************************************************************
**                                             Margin for Control History                                             **
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
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for declaration of the ISRs */
#include "Gpt_GTM_Irq.h"
/* Included for declaration of the Gpt_HW_GTM_CbkNotification() function */
#include "Gpt_GTM_LLDriver.h"
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define GPT_GTM_IRQ_C_AR_RELEASE_MAJOR_VERSION    GPT_AR_RELEASE_MAJOR_VERSION_VALUE
#define GPT_GTM_IRQ_C_AR_RELEASE_MINOR_VERSION    GPT_AR_RELEASE_MINOR_VERSION_VALUE
#define GPT_GTM_IRQ_C_AR_RELEASE_REVISION_VERSION GPT_AR_RELEASE_REVISION_VERSION_VALUE
/* File version information */
#define GPT_GTM_IRQ_C_SW_MAJOR_VERSION            GPT_SW_MAJOR_VERSION_VALUE
#define GPT_GTM_IRQ_C_SW_MINOR_VERSION            GPT_SW_MINOR_VERSION_VALUE
/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (GPT_GTM_IRQ_AR_RELEASE_MAJOR_VERSION != GPT_GTM_IRQ_C_AR_RELEASE_MAJOR_VERSION)
#error "Gpt_GTM_Irq.c : Mismatch in Release Major Version"
#endif
#if (GPT_GTM_IRQ_AR_RELEASE_MINOR_VERSION != GPT_GTM_IRQ_C_AR_RELEASE_MINOR_VERSION)
#error "Gpt_GTM_Irq.c : Mismatch in Release Minor Version"
#endif
#if (GPT_GTM_IRQ_AR_RELEASE_REVISION_VERSION != GPT_GTM_IRQ_C_AR_RELEASE_REVISION_VERSION)
#error "Gpt_GTM_Irq.c : Mismatch in Release Revision Version"
#endif
#if (GPT_GTM_IRQ_SW_MAJOR_VERSION != GPT_GTM_IRQ_C_SW_MAJOR_VERSION)
#error "Gpt_GTM_Irq.c : Mismatch in Software Major Version"
#endif
#if (GPT_GTM_IRQ_SW_MINOR_VERSION != GPT_GTM_IRQ_C_SW_MINOR_VERSION)
#error "Gpt_GTM_Irq.c : Mismatch in Software Minor Version"
#endif

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/
#if (GPT_TIMER_IP_GTM == STD_ON)
#define GPT_START_SEC_CODE_FAST
#include "Gpt_MemMap.h"

/***********************************************************************************************************************
** Function Name        : GTM_TOMn_IRQx_ISR
**
** Service ID           : NA
**
** Description          : These are Interrupt routines for the TOM. Timer channels, where represents by 
**                        configuration.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant
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
** Function(s) invoked  : Gpt_HW_Gtm_CbkNotification
**
** Registers Used       : None
**
** Reference ID         : GPT_DUD_ACT_087
***********************************************************************************************************************/
#if ((GPT_TOM0_CH00_ISR_API == STD_ON) || (GPT_TOM0_CH01_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM0_IRQ0_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TOM0_IRQ0_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM0_IRQ0_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_TOM0_CH00_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM0_CH00);
  #endif
  #if (GPT_TOM0_CH01_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM0_CH01);
  #endif
}
#endif /* End of (GPT_TOM0_CH00_ISR_API == STD_ON) || (GPT_TOM0_CH01_ISR_API == STD_ON) */

#if ((GPT_TOM0_CH02_ISR_API == STD_ON) || (GPT_TOM0_CH03_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM0_IRQ1_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TOM0_IRQ1_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM0_IRQ1_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_TOM0_CH02_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM0_CH02);
  #endif
  #if (GPT_TOM0_CH03_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM0_CH03);
  #endif
}
#endif /* End of (GPT_TOM0_CH02_ISR_API == STD_ON) || (GPT_TOM0_CH03_ISR_API == STD_ON) */

#if ((GPT_TOM0_CH04_ISR_API == STD_ON) || (GPT_TOM0_CH05_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM0_IRQ2_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TOM0_IRQ2_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM0_IRQ2_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_TOM0_CH04_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM0_CH04);
  #endif
  #if (GPT_TOM0_CH05_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM0_CH05);
  #endif
}
#endif /* End of (GPT_TOM0_CH04_ISR_API == STD_ON) || (GPT_TOM0_CH05_ISR_API == STD_ON) */

#if ((GPT_TOM0_CH06_ISR_API == STD_ON) || (GPT_TOM0_CH07_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM0_IRQ3_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TOM0_IRQ3_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM0_IRQ3_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_TOM0_CH06_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM0_CH06);
  #endif
  #if (GPT_TOM0_CH07_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM0_CH07);
  #endif
}
#endif /* End of (GPT_TOM0_CH06_ISR_API == STD_ON) || (GPT_TOM0_CH07_ISR_API == STD_ON) */

#if ((GPT_TOM0_CH08_ISR_API == STD_ON) || (GPT_TOM0_CH09_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM0_IRQ4_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TOM0_IRQ4_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM0_IRQ4_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_TOM0_CH08_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM0_CH08);
  #endif
  #if (GPT_TOM0_CH09_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM0_CH09);
  #endif
}
#endif /* End of (GPT_TOM0_CH08_ISR_API == STD_ON) || (GPT_TOM0_CH09_ISR_API == STD_ON) */

#if ((GPT_TOM0_CH10_ISR_API == STD_ON) || (GPT_TOM0_CH11_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM0_IRQ5_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TOM0_IRQ5_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM0_IRQ5_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_TOM0_CH10_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM0_CH10);
  #endif
  #if (GPT_TOM0_CH11_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM0_CH11);
  #endif
}
#endif /* End of (GPT_TOM0_CH10_ISR_API == STD_ON) || (GPT_TOM0_CH11_ISR_API == STD_ON) */

#if ((GPT_TOM0_CH12_ISR_API == STD_ON) || (GPT_TOM0_CH13_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM0_IRQ6_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TOM0_IRQ6_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM0_IRQ6_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_TOM0_CH12_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM0_CH12);
  #endif
  #if (GPT_TOM0_CH13_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM0_CH13);
  #endif
}
#endif /* End of (GPT_TOM0_CH12_ISR_API == STD_ON) || (GPT_TOM0_CH13_ISR_API == STD_ON) */

#if ((GPT_TOM0_CH14_ISR_API == STD_ON) || (GPT_TOM0_CH15_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM0_IRQ7_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TOM0_IRQ7_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM0_IRQ7_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_TOM0_CH14_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM0_CH14);
  #endif
  #if (GPT_TOM0_CH15_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM0_CH15);
  #endif
}
#endif /* End of (GPT_TOM0_CH14_ISR_API == STD_ON) || (GPT_TOM0_CH15_ISR_API == STD_ON) */

#if ((GPT_TOM1_CH00_ISR_API == STD_ON) || (GPT_TOM1_CH01_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM1_IRQ0_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TOM1_IRQ0_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM1_IRQ0_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_TOM1_CH00_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM1_CH00);
  #endif
  #if (GPT_TOM1_CH01_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM1_CH01);
  #endif
}
#endif /* End of (GPT_TOM1_CH00_ISR_API == STD_ON) || (GPT_TOM1_CH01_ISR_API == STD_ON) */

#if ((GPT_TOM1_CH02_ISR_API == STD_ON) || (GPT_TOM1_CH03_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM1_IRQ1_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TOM1_IRQ1_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM1_IRQ1_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_TOM1_CH02_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM1_CH02);
  #endif
  #if (GPT_TOM1_CH03_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM1_CH03);
  #endif
}
#endif /* End of (GPT_TOM1_CH02_ISR_API == STD_ON) || (GPT_TOM1_CH03_ISR_API == STD_ON) */

#if ((GPT_TOM1_CH04_ISR_API == STD_ON) || (GPT_TOM1_CH05_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM1_IRQ2_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TOM1_IRQ2_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM1_IRQ2_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_TOM1_CH04_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM1_CH04);
  #endif
  #if (GPT_TOM1_CH05_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM1_CH05);
  #endif
}
#endif /* End of (GPT_TOM1_CH04_ISR_API == STD_ON) || (GPT_TOM1_CH05_ISR_API == STD_ON) */

#if ((GPT_TOM1_CH06_ISR_API == STD_ON) || (GPT_TOM1_CH07_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM1_IRQ3_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TOM1_IRQ3_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM1_IRQ3_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_TOM1_CH06_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM1_CH06);
  #endif
  #if (GPT_TOM1_CH07_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM1_CH07);
  #endif
}
#endif /* End of (GPT_TOM1_CH06_ISR_API == STD_ON) || (GPT_TOM1_CH07_ISR_API == STD_ON) */

#if ((GPT_TOM1_CH08_ISR_API == STD_ON) || (GPT_TOM1_CH09_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM1_IRQ4_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TOM1_IRQ4_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM1_IRQ4_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_TOM1_CH08_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM1_CH08);
  #endif
  #if (GPT_TOM1_CH09_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM1_CH09);
  #endif
}
#endif /* End of (GPT_TOM1_CH08_ISR_API == STD_ON) || (GPT_TOM1_CH09_ISR_API == STD_ON) */

#if ((GPT_TOM1_CH10_ISR_API == STD_ON) || (GPT_TOM1_CH11_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM1_IRQ5_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TOM1_IRQ5_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM1_IRQ5_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_TOM1_CH10_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM1_CH10);
  #endif
  #if (GPT_TOM1_CH11_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM1_CH11);
  #endif
}
#endif /* End of (GPT_TOM1_CH10_ISR_API == STD_ON) || (GPT_TOM1_CH11_ISR_API == STD_ON) */

#if ((GPT_TOM1_CH12_ISR_API == STD_ON) || (GPT_TOM1_CH13_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM1_IRQ6_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TOM1_IRQ6_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM1_IRQ6_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_TOM1_CH12_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM1_CH12);
  #endif
  #if (GPT_TOM1_CH13_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM1_CH13);
  #endif
}
#endif /* End of (GPT_TOM1_CH12_ISR_API == STD_ON) || (GPT_TOM1_CH13_ISR_API == STD_ON) */

#if ((GPT_TOM1_CH14_ISR_API == STD_ON) || (GPT_TOM1_CH15_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM1_IRQ7_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TOM1_IRQ7_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM1_IRQ7_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_TOM1_CH14_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM1_CH14);
  #endif
  #if (GPT_TOM1_CH15_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM1_CH15);
  #endif
}
#endif /* End of (GPT_TOM1_CH14_ISR_API == STD_ON) || (GPT_TOM1_CH15_ISR_API == STD_ON) */

#if ((GPT_TOM2_CH00_ISR_API == STD_ON) || (GPT_TOM2_CH01_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM2_IRQ0_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TOM2_IRQ0_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM2_IRQ0_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_TOM2_CH00_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM2_CH00);
  #endif
  #if (GPT_TOM2_CH01_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM2_CH01);
  #endif
}
#endif /* End of (GPT_TOM2_CH00_ISR_API == STD_ON) || (GPT_TOM2_CH01_ISR_API == STD_ON) */

#if ((GPT_TOM2_CH02_ISR_API == STD_ON) || (GPT_TOM2_CH03_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM2_IRQ1_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TOM2_IRQ1_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM2_IRQ1_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_TOM2_CH02_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM2_CH02);
  #endif
  #if (GPT_TOM2_CH03_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM2_CH03);
  #endif
}
#endif /* End of (GPT_TOM2_CH02_ISR_API == STD_ON) || (GPT_TOM2_CH03_ISR_API == STD_ON) */

#if ((GPT_TOM2_CH04_ISR_API == STD_ON) || (GPT_TOM2_CH05_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM2_IRQ2_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TOM2_IRQ2_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM2_IRQ2_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_TOM2_CH04_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM2_CH04);
  #endif
  #if (GPT_TOM2_CH05_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM2_CH05);
  #endif
}
#endif /* End of (GPT_TOM2_CH04_ISR_API == STD_ON) || (GPT_TOM2_CH05_ISR_API == STD_ON) */

#if ((GPT_TOM2_CH06_ISR_API == STD_ON) || (GPT_TOM2_CH07_ISR_API == STD_ON))

/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM2_IRQ3_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TOM2_IRQ3_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM2_IRQ3_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_TOM2_CH06_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM2_CH06);
  #endif
  #if (GPT_TOM2_CH07_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM2_CH07);
  #endif
}
#endif /* End of (GPT_TOM2_CH06_ISR_API == STD_ON) || (GPT_TOM2_CH07_ISR_API == STD_ON) */

#if ((GPT_TOM2_CH08_ISR_API == STD_ON) || (GPT_TOM2_CH09_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM2_IRQ4_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TOM2_IRQ4_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM2_IRQ4_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_TOM2_CH08_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM2_CH08);
  #endif
  #if (GPT_TOM2_CH09_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM2_CH09);
  #endif
}
#endif /* End of (GPT_TOM2_CH08_ISR_API == STD_ON) || (GPT_TOM2_CH09_ISR_API == STD_ON) */

#if ((GPT_TOM2_CH10_ISR_API == STD_ON) || (GPT_TOM2_CH11_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM2_IRQ5_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TOM2_IRQ5_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM2_IRQ5_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_TOM2_CH10_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM2_CH10);
  #endif
  #if (GPT_TOM2_CH11_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM2_CH11);
  #endif
}
#endif /* End of (GPT_TOM2_CH10_ISR_API == STD_ON) || (GPT_TOM2_CH11_ISR_API == STD_ON) */

#if ((GPT_TOM2_CH12_ISR_API == STD_ON) || (GPT_TOM2_CH13_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM2_IRQ6_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TOM2_IRQ6_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM2_IRQ6_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_TOM2_CH12_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM2_CH12);
  #endif
  #if (GPT_TOM2_CH13_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM2_CH13);
  #endif
}
#endif /* End of (GPT_TOM2_CH12_ISR_API == STD_ON) || (GPT_TOM2_CH13_ISR_API == STD_ON) */

#if ((GPT_TOM2_CH14_ISR_API == STD_ON) || (GPT_TOM2_CH15_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM2_IRQ7_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TOM2_IRQ7_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM2_IRQ7_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_TOM2_CH14_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM2_CH14);
  #endif
  #if (GPT_TOM2_CH15_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM2_CH15);
  #endif
}
#endif /* End of (GPT_TOM2_CH14_ISR_API == STD_ON) || (GPT_TOM2_CH15_ISR_API == STD_ON) */

#if ((GPT_TOM3_CH00_ISR_API == STD_ON) || (GPT_TOM3_CH01_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM3_IRQ0_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TOM3_IRQ0_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM3_IRQ0_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_TOM3_CH00_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM3_CH00);
  #endif
  #if (GPT_TOM3_CH01_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM3_CH01);
  #endif
}
#endif /* End of (GPT_TOM3_CH00_ISR_API == STD_ON) || (GPT_TOM3_CH01_ISR_API == STD_ON) */

#if ((GPT_TOM3_CH02_ISR_API == STD_ON) || (GPT_TOM3_CH03_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM3_IRQ1_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TOM3_IRQ1_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM3_IRQ1_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_TOM3_CH02_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM3_CH02);
  #endif
  #if (GPT_TOM3_CH03_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM3_CH03);
  #endif
}
#endif /* End of (GPT_TOM3_CH02_ISR_API == STD_ON) || (GPT_TOM3_CH03_ISR_API == STD_ON) */

#if ((GPT_TOM3_CH04_ISR_API == STD_ON) || (GPT_TOM3_CH05_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM3_IRQ2_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TOM3_IRQ2_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM3_IRQ2_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_TOM3_CH04_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM3_CH04);
  #endif
  #if (GPT_TOM3_CH05_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM3_CH05);
  #endif
}
#endif /* End of (GPT_TOM3_CH04_ISR_API == STD_ON) || (GPT_TOM3_CH05_ISR_API == STD_ON) */

#if ((GPT_TOM3_CH06_ISR_API == STD_ON) || (GPT_TOM3_CH07_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM3_IRQ3_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TOM3_IRQ3_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM3_IRQ3_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_TOM3_CH06_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM3_CH06);
  #endif
  #if (GPT_TOM3_CH07_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM3_CH07);
  #endif
}
#endif /* End of (GPT_TOM3_CH06_ISR_API == STD_ON) || (GPT_TOM3_CH07_ISR_API == STD_ON) */

#if ((GPT_TOM3_CH08_ISR_API == STD_ON) || (GPT_TOM3_CH09_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM3_IRQ4_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TOM3_IRQ4_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM3_IRQ4_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_TOM3_CH08_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM3_CH08);
  #endif
  #if (GPT_TOM3_CH09_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM3_CH09);
  #endif
}
#endif /* End of (GPT_TOM3_CH08_ISR_API == STD_ON) || (GPT_TOM3_CH09_ISR_API == STD_ON) */

#if ((GPT_TOM3_CH10_ISR_API == STD_ON) || (GPT_TOM3_CH11_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM3_IRQ5_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TOM3_IRQ5_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM3_IRQ5_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_TOM3_CH10_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM3_CH10);
  #endif
  #if (GPT_TOM3_CH11_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM3_CH11);
  #endif
}
#endif /* End of (GPT_TOM3_CH10_ISR_API == STD_ON) || (GPT_TOM3_CH11_ISR_API == STD_ON) */

#if ((GPT_TOM3_CH12_ISR_API == STD_ON) || (GPT_TOM3_CH13_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM3_IRQ6_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TOM3_IRQ6_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM3_IRQ6_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_TOM3_CH12_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM3_CH12);
  #endif
  #if (GPT_TOM3_CH13_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM3_CH13);
  #endif
}
#endif /* End of (GPT_TOM3_CH12_ISR_API == STD_ON) || (GPT_TOM3_CH13_ISR_API == STD_ON) */

#if ((GPT_TOM3_CH14_ISR_API == STD_ON) || (GPT_TOM3_CH15_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM3_IRQ7_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TOM3_IRQ7_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM3_IRQ7_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_TOM3_CH14_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM3_CH14);
  #endif
  #if (GPT_TOM3_CH15_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM3_CH15);
  #endif
}
#endif /* End of (GPT_TOM3_CH14_ISR_API == STD_ON) || (GPT_TOM3_CH15_ISR_API == STD_ON) */

#if ((GPT_TOM4_CH00_ISR_API == STD_ON) || (GPT_TOM4_CH01_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM4_IRQ0_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TOM4_IRQ0_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM4_IRQ0_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_TOM4_CH00_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM4_CH00);
  #endif
  #if (GPT_TOM4_CH01_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM4_CH01);
  #endif
}
#endif /* End of (GPT_TOM4_CH00_ISR_API == STD_ON) || (GPT_TOM4_CH01_ISR_API == STD_ON) */

#if ((GPT_TOM4_CH02_ISR_API == STD_ON) || (GPT_TOM4_CH03_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM4_IRQ1_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TOM4_IRQ1_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM4_IRQ1_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_TOM4_CH02_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM4_CH02);
  #endif
  #if (GPT_TOM4_CH03_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM4_CH03);
  #endif
}
#endif /* End of (GPT_TOM4_CH02_ISR_API == STD_ON) || (GPT_TOM4_CH03_ISR_API == STD_ON) */

#if ((GPT_TOM4_CH04_ISR_API == STD_ON) || (GPT_TOM4_CH05_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM4_IRQ2_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TOM4_IRQ2_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM4_IRQ2_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_TOM4_CH04_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM4_CH04);
  #endif
  #if (GPT_TOM4_CH05_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM4_CH05);
  #endif
}
#endif /* End of (GPT_TOM4_CH04_ISR_API == STD_ON) || (GPT_TOM4_CH05_ISR_API == STD_ON) */

#if ((GPT_TOM4_CH06_ISR_API == STD_ON) || (GPT_TOM4_CH07_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM4_IRQ3_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TOM4_IRQ3_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM4_IRQ3_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_TOM4_CH06_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM4_CH06);
  #endif
  #if (GPT_TOM4_CH07_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM4_CH07);
  #endif
}
#endif /* End of (GPT_TOM4_CH06_ISR_API == STD_ON) || (GPT_TOM4_CH07_ISR_API == STD_ON) */

#if ((GPT_TOM4_CH08_ISR_API == STD_ON) || (GPT_TOM4_CH09_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM4_IRQ4_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TOM4_IRQ4_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM4_IRQ4_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_TOM4_CH08_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM4_CH08);
  #endif
  #if (GPT_TOM4_CH09_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM4_CH09);
  #endif
}
#endif /* End of (GPT_TOM4_CH08_ISR_API == STD_ON) || (GPT_TOM4_CH09_ISR_API == STD_ON) */

#if ((GPT_TOM4_CH10_ISR_API == STD_ON) || (GPT_TOM4_CH11_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM4_IRQ5_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TOM4_IRQ5_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM4_IRQ5_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_TOM4_CH10_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM4_CH10);
  #endif
  #if (GPT_TOM4_CH11_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM4_CH11);
  #endif
}
#endif /* End of (GPT_TOM4_CH10_ISR_API == STD_ON) || (GPT_TOM4_CH11_ISR_API == STD_ON) */

#if ((GPT_TOM4_CH12_ISR_API == STD_ON) || (GPT_TOM4_CH13_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM4_IRQ6_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TOM4_IRQ6_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM4_IRQ6_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_TOM4_CH12_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM4_CH12);
  #endif
  #if (GPT_TOM4_CH13_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM4_CH13);
  #endif
}
#endif /* End of (GPT_TOM4_CH12_ISR_API == STD_ON) || (GPT_TOM4_CH13_ISR_API == STD_ON) */

#if ((GPT_TOM4_CH14_ISR_API == STD_ON) || (GPT_TOM4_CH15_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_TOM4_IRQ7_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_TOM4_IRQ7_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_TOM4_IRQ7_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_TOM4_CH14_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM4_CH14);
  #endif
  #if (GPT_TOM4_CH15_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_TOM4_CH15);
  #endif
}
#endif /* End of (GPT_TOM4_CH14_ISR_API == STD_ON) || (GPT_TOM4_CH15_ISR_API == STD_ON) */

/***********************************************************************************************************************
** Function Name        : GTM_ATOMn_IRQx_ISR
**
** Service ID           : NA
**
** Description          : These are Interrupt routines for the TOM. Timer channels, where represents by
**                        configuration.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant
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
** Function(s) invoked  : Gpt_HW_Gtm_CbkNotification
**
** Registers Used       : None
**
** Reference ID         : GPT_DUD_ACT_088
***********************************************************************************************************************/
#if ((GPT_ATOM0_CH00_ISR_API == STD_ON) || (GPT_ATOM0_CH01_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM0_IRQ0_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_ATOM0_IRQ0_CAT2_ISR)                                                                                            /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM0_IRQ0_ISR(void)                                                          /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_ATOM0_CH00_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM0_CH00);
  #endif
  #if (GPT_ATOM0_CH01_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM0_CH01);
  #endif
}
#endif /* End of (GPT_ATOM0_CH00_ISR_API == STD_ON) || (GPT_ATOM0_CH01_ISR_API == STD_ON) */

#if ((GPT_ATOM0_CH02_ISR_API == STD_ON) || (GPT_ATOM0_CH03_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM0_IRQ1_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_ATOM0_IRQ1_CAT2_ISR)                                                                                            /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM0_IRQ1_ISR(void)                                                          /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_ATOM0_CH02_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM0_CH02);
  #endif
  #if (GPT_ATOM0_CH03_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM0_CH03);
  #endif
}
#endif /* End of (GPT_ATOM0_CH02_ISR_API == STD_ON) || (GPT_ATOM0_CH03_ISR_API == STD_ON) */

#if ((GPT_ATOM0_CH04_ISR_API == STD_ON) || (GPT_ATOM0_CH05_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM0_IRQ2_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_ATOM0_IRQ2_CAT2_ISR)                                                                                            /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM0_IRQ2_ISR(void)                                                          /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_ATOM0_CH04_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM0_CH04);
  #endif
  #if (GPT_ATOM0_CH05_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM0_CH05);
  #endif
}
#endif /* End of (GPT_ATOM0_CH04_ISR_API == STD_ON) || (GPT_ATOM0_CH05_ISR_API == STD_ON) */

#if ((GPT_ATOM0_CH06_ISR_API == STD_ON) || (GPT_ATOM0_CH07_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM0_IRQ3_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_ATOM0_IRQ3_CAT2_ISR)                                                                                            /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM0_IRQ3_ISR(void)                                                          /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_ATOM0_CH06_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM0_CH06);
  #endif
  #if (GPT_ATOM0_CH07_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM0_CH07);
  #endif
}
#endif /* End of (GPT_ATOM0_CH06_ISR_API == STD_ON) || (GPT_ATOM0_CH07_ISR_API == STD_ON) */

#if ((GPT_ATOM1_CH00_ISR_API == STD_ON) || (GPT_ATOM1_CH01_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM1_IRQ0_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_ATOM1_IRQ0_CAT2_ISR)                                                                                            /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM1_IRQ0_ISR(void)                                                          /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_ATOM1_CH00_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM1_CH00);
  #endif
  #if (GPT_ATOM1_CH01_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM1_CH01);
  #endif
}
#endif /* End of (GPT_ATOM1_CH00_ISR_API == STD_ON) || (GPT_ATOM1_CH01_ISR_API == STD_ON) */

#if ((GPT_ATOM1_CH02_ISR_API == STD_ON) || (GPT_ATOM1_CH03_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM1_IRQ1_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_ATOM1_IRQ1_CAT2_ISR)                                                                                            /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM1_IRQ1_ISR(void)                                                          /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_ATOM1_CH02_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM1_CH02);
  #endif
  #if (GPT_ATOM1_CH03_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM1_CH03);
  #endif
}
#endif /* End of (GPT_ATOM1_CH02_ISR_API == STD_ON) || (GPT_ATOM1_CH03_ISR_API == STD_ON) */

#if ((GPT_ATOM1_CH04_ISR_API == STD_ON) || (GPT_ATOM1_CH05_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM1_IRQ2_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_ATOM1_IRQ2_CAT2_ISR)                                                                                            /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM1_IRQ2_ISR(void)                                                          /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_ATOM1_CH04_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM1_CH04);
  #endif
  #if (GPT_ATOM1_CH05_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM1_CH05);
  #endif
}
#endif /* End of (GPT_ATOM1_CH04_ISR_API == STD_ON) || (GPT_ATOM1_CH05_ISR_API == STD_ON) */

#if ((GPT_ATOM1_CH06_ISR_API == STD_ON) || (GPT_ATOM1_CH07_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM1_IRQ3_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_ATOM1_IRQ3_CAT2_ISR)                                                                                            /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM1_IRQ3_ISR(void)                                                          /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_ATOM1_CH06_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM1_CH06);
  #endif
  #if (GPT_ATOM1_CH07_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM1_CH07);
  #endif
}
#endif /* End of (GPT_ATOM1_CH06_ISR_API == STD_ON) || (GPT_ATOM1_CH07_ISR_API == STD_ON) */

#if ((GPT_ATOM2_CH00_ISR_API == STD_ON) || (GPT_ATOM2_CH01_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM2_IRQ0_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_ATOM2_IRQ0_CAT2_ISR)                                                                                            /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM2_IRQ0_ISR(void)                                                          /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_ATOM2_CH00_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM2_CH00);
  #endif
  #if (GPT_ATOM2_CH01_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM2_CH01);
  #endif
}
#endif /* End of (GPT_ATOM2_CH00_ISR_API == STD_ON) || (GPT_ATOM2_CH01_ISR_API == STD_ON) */

#if ((GPT_ATOM2_CH02_ISR_API == STD_ON) || (GPT_ATOM2_CH03_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM2_IRQ1_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_ATOM2_IRQ1_CAT2_ISR)                                                                                            /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM2_IRQ1_ISR(void)                                                          /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_ATOM2_CH02_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM2_CH02);
  #endif
  #if (GPT_ATOM2_CH03_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM2_CH03);
  #endif
}
#endif /* End of (GPT_ATOM2_CH02_ISR_API == STD_ON) || (GPT_ATOM2_CH03_ISR_API == STD_ON) */

#if ((GPT_ATOM2_CH04_ISR_API == STD_ON) || (GPT_ATOM2_CH05_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM2_IRQ2_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_ATOM2_IRQ2_CAT2_ISR)                                                                                            /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM2_IRQ2_ISR(void)                                                          /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_ATOM2_CH04_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM2_CH04);
  #endif
  #if (GPT_ATOM2_CH05_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM2_CH05);
  #endif
}
#endif /* End of (GPT_ATOM2_CH04_ISR_API == STD_ON) || (GPT_ATOM2_CH05_ISR_API == STD_ON) */

#if ((GPT_ATOM2_CH06_ISR_API == STD_ON) || (GPT_ATOM2_CH07_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM2_IRQ3_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_ATOM2_IRQ3_CAT2_ISR)                                                                                            /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM2_IRQ3_ISR(void)                                                          /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_ATOM2_CH06_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM2_CH06);
  #endif
  #if (GPT_ATOM2_CH07_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM2_CH07);
  #endif
}
#endif /* End of (GPT_ATOM2_CH06_ISR_API == STD_ON) || (GPT_ATOM2_CH07_ISR_API == STD_ON) */

#if ((GPT_ATOM3_CH00_ISR_API == STD_ON) || (GPT_ATOM3_CH01_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM3_IRQ0_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_ATOM3_IRQ0_CAT2_ISR)                                                                                            /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM3_IRQ0_ISR(void)                                                          /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_ATOM3_CH00_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM3_CH00);
  #endif
  #if (GPT_ATOM3_CH01_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM3_CH01);
  #endif
}
#endif /* End of (GPT_ATOM3_CH00_ISR_API == STD_ON) || (GPT_ATOM3_CH01_ISR_API == STD_ON) */

#if ((GPT_ATOM3_CH02_ISR_API == STD_ON) || (GPT_ATOM3_CH03_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM3_IRQ1_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_ATOM3_IRQ1_CAT2_ISR)                                                                                            /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM3_IRQ1_ISR(void)                                                          /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_ATOM3_CH02_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM3_CH02);
  #endif
  #if (GPT_ATOM3_CH03_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM3_CH03);
  #endif
}
#endif /* End of (GPT_ATOM3_CH02_ISR_API == STD_ON) || (GPT_ATOM3_CH03_ISR_API == STD_ON) */

#if ((GPT_ATOM3_CH04_ISR_API == STD_ON) || (GPT_ATOM3_CH05_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM3_IRQ2_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_ATOM3_IRQ2_CAT2_ISR)                                                                                            /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM3_IRQ2_ISR(void)                                                          /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_ATOM3_CH04_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM3_CH04);
  #endif
  #if (GPT_ATOM3_CH05_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM3_CH05);
  #endif
}
#endif /* End of (GPT_ATOM3_CH04_ISR_API == STD_ON) || (GPT_ATOM3_CH05_ISR_API == STD_ON) */

#if ((GPT_ATOM3_CH06_ISR_API == STD_ON) || (GPT_ATOM3_CH07_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM3_IRQ3_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_ATOM3_IRQ3_CAT2_ISR)                                                                                            /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM3_IRQ3_ISR(void)                                                          /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_ATOM3_CH06_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM3_CH06);
  #endif
  #if (GPT_ATOM3_CH07_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM3_CH07);
  #endif
}
#endif /* End of (GPT_ATOM3_CH06_ISR_API == STD_ON) || (GPT_ATOM3_CH07_ISR_API == STD_ON) */

#if ((GPT_ATOM4_CH00_ISR_API == STD_ON) || (GPT_ATOM4_CH01_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM4_IRQ0_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_ATOM4_IRQ0_CAT2_ISR)                                                                                            /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM4_IRQ0_ISR(void)                                                          /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_ATOM4_CH00_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM4_CH00);
  #endif
  #if (GPT_ATOM4_CH01_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM4_CH01);
  #endif
}
#endif /* End of (GPT_ATOM4_CH00_ISR_API == STD_ON) || (GPT_ATOM4_CH01_ISR_API == STD_ON) */

#if ((GPT_ATOM4_CH02_ISR_API == STD_ON) || (GPT_ATOM4_CH03_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM4_IRQ1_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_ATOM4_IRQ1_CAT2_ISR)                                                                                            /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM4_IRQ1_ISR(void)                                                          /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_ATOM4_CH02_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM4_CH02);
  #endif
  #if (GPT_ATOM4_CH03_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM4_CH03);
  #endif
}
#endif /* End of (GPT_ATOM4_CH02_ISR_API == STD_ON) || (GPT_ATOM4_CH03_ISR_API == STD_ON) */

#if ((GPT_ATOM4_CH04_ISR_API == STD_ON) || (GPT_ATOM4_CH05_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM4_IRQ2_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_ATOM4_IRQ2_CAT2_ISR)                                                                                            /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM4_IRQ2_ISR(void)                                                          /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_ATOM4_CH04_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM4_CH04);
  #endif
  #if (GPT_ATOM4_CH05_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM4_CH05);
  #endif
}
#endif /* End of (GPT_ATOM4_CH04_ISR_API == STD_ON) || (GPT_ATOM4_CH05_ISR_API == STD_ON) */

#if ((GPT_ATOM4_CH06_ISR_API == STD_ON) || (GPT_ATOM4_CH07_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM4_IRQ3_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_ATOM4_IRQ3_CAT2_ISR)                                                                                            /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM4_IRQ3_ISR(void)                                                          /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_ATOM4_CH06_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM4_CH06);
  #endif
  #if (GPT_ATOM4_CH07_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM4_CH07);
  #endif
}
#endif /* End of (GPT_ATOM4_CH06_ISR_API == STD_ON) || (GPT_ATOM4_CH07_ISR_API == STD_ON) */

#if ((GPT_ATOM5_CH00_ISR_API == STD_ON) || (GPT_ATOM5_CH01_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM5_IRQ0_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_ATOM5_IRQ0_CAT2_ISR)                                                                                            /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM5_IRQ0_ISR(void)                                                          /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_ATOM5_CH00_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM5_CH00);
  #endif
  #if (GPT_ATOM5_CH01_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM5_CH01);
  #endif
}
#endif /* End of (GPT_ATOM5_CH00_ISR_API == STD_ON) || (GPT_ATOM5_CH01_ISR_API == STD_ON) */

#if ((GPT_ATOM5_CH02_ISR_API == STD_ON) || (GPT_ATOM5_CH03_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM5_IRQ1_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_ATOM5_IRQ1_CAT2_ISR)                                                                                            /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM5_IRQ1_ISR(void)                                                          /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_ATOM5_CH02_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM5_CH02);
  #endif
  #if (GPT_ATOM5_CH03_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM5_CH03);
  #endif
}
#endif /* End of (GPT_ATOM5_CH02_ISR_API == STD_ON) || (GPT_ATOM5_CH03_ISR_API == STD_ON) */

#if ((GPT_ATOM5_CH04_ISR_API == STD_ON) || (GPT_ATOM5_CH05_ISR_API == STD_ON))

/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM5_IRQ2_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_ATOM5_IRQ2_CAT2_ISR)                                                                                            /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM5_IRQ2_ISR(void)                                                          /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_ATOM5_CH04_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM5_CH04);
  #endif
  #if (GPT_ATOM5_CH05_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM5_CH05);
  #endif
}
#endif /* End of (GPT_ATOM5_CH04_ISR_API == STD_ON) || (GPT_ATOM5_CH05_ISR_API == STD_ON) */

#if ((GPT_ATOM5_CH06_ISR_API == STD_ON) || (GPT_ATOM5_CH07_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM5_IRQ3_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_ATOM5_IRQ3_CAT2_ISR)                                                                                            /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM5_IRQ3_ISR(void)                                                          /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_ATOM5_CH06_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM5_CH06);
  #endif
  #if (GPT_ATOM5_CH07_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM5_CH07);
  #endif
}
#endif /* End of (GPT_ATOM5_CH06_ISR_API == STD_ON) || (GPT_ATOM5_CH07_ISR_API == STD_ON) */

#if ((GPT_ATOM6_CH00_ISR_API == STD_ON) || (GPT_ATOM6_CH01_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM6_IRQ0_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_ATOM6_IRQ0_CAT2_ISR)                                                                                            /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM6_IRQ0_ISR(void)                                                          /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_ATOM6_CH00_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM6_CH00);
  #endif
  #if (GPT_ATOM6_CH01_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM6_CH01);
  #endif
}
#endif /* End of (GPT_ATOM6_CH00_ISR_API == STD_ON) || (GPT_ATOM6_CH01_ISR_API == STD_ON) */

#if ((GPT_ATOM6_CH02_ISR_API == STD_ON) || (GPT_ATOM6_CH03_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM6_IRQ1_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_ATOM6_IRQ1_CAT2_ISR)                                                                                            /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM6_IRQ1_ISR(void)                                                          /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_ATOM6_CH02_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM6_CH02);
  #endif
  #if (GPT_ATOM6_CH03_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM6_CH03);
  #endif
}
#endif /* End of (GPT_ATOM6_CH02_ISR_API == STD_ON) || (GPT_ATOM6_CH03_ISR_API == STD_ON) */

#if ((GPT_ATOM6_CH04_ISR_API == STD_ON) || (GPT_ATOM6_CH05_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM6_IRQ2_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_ATOM6_IRQ2_CAT2_ISR)                                                                                            /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM6_IRQ2_ISR(void)                                                          /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_ATOM6_CH04_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM6_CH04);
  #endif
  #if (GPT_ATOM6_CH05_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM6_CH05);
  #endif
}
#endif /* End of (GPT_ATOM6_CH04_ISR_API == STD_ON) || (GPT_ATOM6_CH05_ISR_API == STD_ON) */

#if ((GPT_ATOM6_CH06_ISR_API == STD_ON) || (GPT_ATOM6_CH07_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM6_IRQ3_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_ATOM6_IRQ3_CAT2_ISR)                                                                                            /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM6_IRQ3_ISR(void)                                                          /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_ATOM6_CH06_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM6_CH06);
  #endif
  #if (GPT_ATOM6_CH07_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM6_CH07);
  #endif
}
#endif /* End of (GPT_ATOM6_CH06_ISR_API == STD_ON) || (GPT_ATOM6_CH07_ISR_API == STD_ON) */

#if ((GPT_ATOM7_CH00_ISR_API == STD_ON) || (GPT_ATOM7_CH01_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM7_IRQ0_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_ATOM7_IRQ0_CAT2_ISR)                                                                                            /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM7_IRQ0_ISR(void)                                                          /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_ATOM7_CH00_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM7_CH00);
  #endif
  #if (GPT_ATOM7_CH01_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM7_CH01);
  #endif
}
#endif /* End of (GPT_ATOM7_CH00_ISR_API == STD_ON) || (GPT_ATOM7_CH01_ISR_API == STD_ON) */

#if ((GPT_ATOM7_CH02_ISR_API == STD_ON) || (GPT_ATOM7_CH03_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM7_IRQ1_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_ATOM7_IRQ1_CAT2_ISR)                                                                                            /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM7_IRQ1_ISR(void)                                                          /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_ATOM7_CH02_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM7_CH02);
  #endif
  #if (GPT_ATOM7_CH03_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM7_CH03);
  #endif
}
#endif /* End of (GPT_ATOM7_CH02_ISR_API == STD_ON) || (GPT_ATOM7_CH03_ISR_API == STD_ON) */

#if ((GPT_ATOM7_CH04_ISR_API == STD_ON) || (GPT_ATOM7_CH05_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM7_IRQ2_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_ATOM7_IRQ2_CAT2_ISR)                                                                                            /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM7_IRQ2_ISR(void)                                                          /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_ATOM7_CH04_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM7_CH04);
  #endif
  #if (GPT_ATOM7_CH05_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM7_CH05);
  #endif
}
#endif /* End of (GPT_ATOM7_CH04_ISR_API == STD_ON) || (GPT_ATOM7_CH05_ISR_API == STD_ON) */

#if ((GPT_ATOM7_CH06_ISR_API == STD_ON) || (GPT_ATOM7_CH07_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM7_IRQ3_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_ATOM7_IRQ3_CAT2_ISR)                                                                                            /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM7_IRQ3_ISR(void)                                                          /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_ATOM7_CH06_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM7_CH06);
  #endif
  #if (GPT_ATOM7_CH07_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM7_CH07);
  #endif
}
#endif /* End of (GPT_ATOM7_CH06_ISR_API == STD_ON) || (GPT_ATOM7_CH07_ISR_API == STD_ON) */

#if ((GPT_ATOM8_CH00_ISR_API == STD_ON) || (GPT_ATOM8_CH01_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM8_IRQ0_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_ATOM8_IRQ0_CAT2_ISR)                                                                                            /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM8_IRQ0_ISR(void)                                                          /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_ATOM8_CH00_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM8_CH00);
  #endif
  #if (GPT_ATOM8_CH01_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM8_CH01);
  #endif
}
#endif /* End of (GPT_ATOM8_CH00_ISR_API == STD_ON) || (GPT_ATOM8_CH01_ISR_API == STD_ON) */

#if ((GPT_ATOM8_CH02_ISR_API == STD_ON) || (GPT_ATOM8_CH03_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM8_IRQ1_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_ATOM8_IRQ1_CAT2_ISR)                                                                                            /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM8_IRQ1_ISR(void)                                                          /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_ATOM8_CH02_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM8_CH02);
  #endif
  #if (GPT_ATOM8_CH03_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM8_CH03);
  #endif
}
#endif /* End of (GPT_ATOM8_CH02_ISR_API == STD_ON) || (GPT_ATOM8_CH03_ISR_API == STD_ON) */

#if ((GPT_ATOM8_CH04_ISR_API == STD_ON) || (GPT_ATOM8_CH05_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM8_IRQ2_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_ATOM8_IRQ2_CAT2_ISR)                                                                                            /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM8_IRQ2_ISR(void)                                                          /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_ATOM8_CH04_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM8_CH04);
  #endif
  #if (GPT_ATOM8_CH05_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM8_CH05);
  #endif
}
#endif /* End of (GPT_ATOM8_CH04_ISR_API == STD_ON) || (GPT_ATOM8_CH05_ISR_API == STD_ON) */

#if ((GPT_ATOM8_CH06_ISR_API == STD_ON) || (GPT_ATOM8_CH07_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM8_IRQ3_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_ATOM8_IRQ3_CAT2_ISR)                                                                                            /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM8_IRQ3_ISR(void)                                                          /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_ATOM8_CH06_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM8_CH06);
  #endif
  #if (GPT_ATOM8_CH07_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM8_CH07);
  #endif
}
#endif /* End of (GPT_ATOM8_CH06_ISR_API == STD_ON) || (GPT_ATOM8_CH07_ISR_API == STD_ON) */

#if ((GPT_ATOM9_CH00_ISR_API == STD_ON) || (GPT_ATOM9_CH01_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM9_IRQ0_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_ATOM9_IRQ0_CAT2_ISR)                                                                                            /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM9_IRQ0_ISR(void)                                                          /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_ATOM9_CH00_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM9_CH00);
  #endif
  #if (GPT_ATOM9_CH01_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM9_CH01);
  #endif
}
#endif /* End of (GPT_ATOM9_CH00_ISR_API == STD_ON) || (GPT_ATOM9_CH01_ISR_API == STD_ON) */

#if ((GPT_ATOM9_CH02_ISR_API == STD_ON) || (GPT_ATOM9_CH03_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM9_IRQ1_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_ATOM9_IRQ1_CAT2_ISR)                                                                                            /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM9_IRQ1_ISR(void)                                                          /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_ATOM9_CH02_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM9_CH02);
  #endif
  #if (GPT_ATOM9_CH03_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM9_CH03);
  #endif
}
#endif /* End of (GPT_ATOM9_CH02_ISR_API == STD_ON) || (GPT_ATOM9_CH03_ISR_API == STD_ON) */

#if ((GPT_ATOM9_CH04_ISR_API == STD_ON) || (GPT_ATOM9_CH05_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM9_IRQ2_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_ATOM9_IRQ2_CAT2_ISR)                                                                                            /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM9_IRQ2_ISR(void)                                                          /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_ATOM9_CH04_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM9_CH04);
  #endif
  #if (GPT_ATOM9_CH05_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM9_CH05);
  #endif
}
#endif /* End of (GPT_ATOM9_CH04_ISR_API == STD_ON) || (GPT_ATOM9_CH05_ISR_API == STD_ON) */

#if ((GPT_ATOM9_CH06_ISR_API == STD_ON) || (GPT_ATOM9_CH07_ISR_API == STD_ON))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_GTM_ATOM9_IRQ3_CAT2_ISR) || (GPT_ISR_CATEGORY_2 == STD_ON)
ISR(GTM_ATOM9_IRQ3_CAT2_ISR)                                                                                            /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, GPT_CODE_FAST) GTM_ATOM9_IRQ3_ISR(void)                                                          /* PRQA S 1503 # JV-01 */
#endif
{
  #if (GPT_ATOM9_CH06_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM9_CH06);
  #endif
  #if (GPT_ATOM9_CH07_ISR_API == STD_ON)
  Gpt_HW_Gtm_CbkNotification((uint8)GPT_ATOM9_CH07);
  #endif
}
#endif /* End of (GPT_ATOM9_CH06_ISR_API == STD_ON) || (GPT_ATOM9_CH07_ISR_API == STD_ON) */

#define GPT_STOP_SEC_CODE_FAST
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* GPT_TIMER_IP_GTM == STD_ON */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
