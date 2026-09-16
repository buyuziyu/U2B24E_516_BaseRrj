/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2X MCAL Components                                                                 */
/* Module       = Ocu_TAUD_Irq.c                                                                                      */
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
 *  1.0.0  29/03/2023  : Initial Version
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

/**********************************************************************************************************************/

/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for declaration of the ISRs */
#include "Ocu_TAUD_Irq.h"
/* Included for declaration of the Ocu_HW_Taud_CbkNotification() function */
#include "Ocu_TAUD_LLDriver.h"
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define OCU_TAUD_IRQ_C_AR_RELEASE_MAJOR_VERSION    OCU_AR_RELEASE_MAJOR_VERSION_VALUE
#define OCU_TAUD_IRQ_C_AR_RELEASE_MINOR_VERSION    OCU_AR_RELEASE_MINOR_VERSION_VALUE
#define OCU_TAUD_IRQ_C_AR_RELEASE_REVISION_VERSION OCU_AR_RELEASE_REVISION_VERSION_VALUE
/* File version information */
#define OCU_TAUD_IRQ_C_SW_MAJOR_VERSION            OCU_SW_MAJOR_VERSION_VALUE
#define OCU_TAUD_IRQ_C_SW_MINOR_VERSION            OCU_SW_MINOR_VERSION_VALUE
/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (OCU_TAUD_IRQ_AR_RELEASE_MAJOR_VERSION != OCU_TAUD_IRQ_C_AR_RELEASE_MAJOR_VERSION)
#error "Ocu_TAUD_Irq.c : Mismatch in Release Major Version"
#endif
#if (OCU_TAUD_IRQ_AR_RELEASE_MINOR_VERSION != OCU_TAUD_IRQ_C_AR_RELEASE_MINOR_VERSION)
#error "Ocu_TAUD_Irq.c : Mismatch in Release Minor Version"
#endif
#if (OCU_TAUD_IRQ_AR_RELEASE_REVISION_VERSION != OCU_TAUD_IRQ_C_AR_RELEASE_REVISION_VERSION)
#error "Ocu_TAUD_Irq.c : Mismatch in Release Revision Version"
#endif
#if (OCU_TAUD_IRQ_SW_MAJOR_VERSION != OCU_TAUD_IRQ_C_SW_MAJOR_VERSION)
#error "Ocu_TAUD_Irq.c : Mismatch in Software Major Version"
#endif
#if (OCU_TAUD_IRQ_SW_MINOR_VERSION != OCU_TAUD_IRQ_C_SW_MINOR_VERSION)
#error "Ocu_TAUD_Irq.c : Mismatch in Software Minor Version"
#endif

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/
#if (OCU_TIMER_IP_TAUD == STD_ON)
/***********************************************************************************************************************
** Function Name        : TAUDx_CHmn_ISR
**
** Service ID           : NA
**
** Description          : These are Interrupt routines for the timer TAUDn Channel mn, where x represents the
**                        TAUD Units and mn represents channels associated for each Unit.
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
** Function(s) invoked  : Ocu_HW_Taud_CbkNotification
**
** Registers Used       : None
**
** Reference ID         : OCU_DUD_ACT_043
***********************************************************************************************************************/
#define OCU_START_SEC_CODE_FAST
#include "Ocu_MemMap.h"

#if (OCU_TAUD0_CH01_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD0_CH01_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
ISR(TAUD0_CH01_CAT2_ISR)                                                                                                /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, OCU_CODE_FAST) TAUD0_CH01_ISR(void)                                                              /* PRQA S 1503 # JV-01 */
#endif
{
  Ocu_HW_Taud_CbkNotification((uint8)OCU_TAUD0_CH01);
}
#endif /* End of OCU_TAUD0_CH01_ISR_API == STD_ON */

#if (OCU_TAUD0_CH03_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD0_CH03_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
ISR(TAUD0_CH03_CAT2_ISR)                                                                                                /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, OCU_CODE_FAST) TAUD0_CH03_ISR(void)                                                              /* PRQA S 1503 # JV-01 */
#endif
{
  Ocu_HW_Taud_CbkNotification((uint8)OCU_TAUD0_CH03);
}
#endif /* End of OCU_TAUD0_CH03_ISR_API == STD_ON */

#if (OCU_TAUD0_CH05_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD0_CH05_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
ISR(TAUD0_CH05_CAT2_ISR)                                                                                                /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, OCU_CODE_FAST) TAUD0_CH05_ISR(void)                                                              /* PRQA S 1503 # JV-01 */
#endif
{
  Ocu_HW_Taud_CbkNotification((uint8)OCU_TAUD0_CH05);
}
#endif /* End of OCU_TAUD0_CH05_ISR_API == STD_ON */

#if (OCU_TAUD0_CH07_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD0_CH07_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
ISR(TAUD0_CH07_CAT2_ISR)                                                                                                /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, OCU_CODE_FAST) TAUD0_CH07_ISR(void)                                                              /* PRQA S 1503 # JV-01 */
#endif
{
  Ocu_HW_Taud_CbkNotification((uint8)OCU_TAUD0_CH07);
}
#endif /* End of OCU_TAUD0_CH07_ISR_API == STD_ON */

#if (OCU_TAUD0_CH09_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD0_CH09_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
ISR(TAUD0_CH09_CAT2_ISR)                                                                                                /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, OCU_CODE_FAST) TAUD0_CH09_ISR(void)                                                              /* PRQA S 1503 # JV-01 */
#endif
{
  Ocu_HW_Taud_CbkNotification((uint8)OCU_TAUD0_CH09);
}
#endif /* End of OCU_TAUD0_CH09_ISR_API == STD_ON */

#if (OCU_TAUD0_CH11_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD0_CH11_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
ISR(TAUD0_CH11_CAT2_ISR)                                                                                                /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, OCU_CODE_FAST) TAUD0_CH11_ISR(void)                                                              /* PRQA S 1503 # JV-01 */
#endif
{
  Ocu_HW_Taud_CbkNotification((uint8)OCU_TAUD0_CH11);
}
#endif /* End of OCU_TAUD0_CH11_ISR_API == STD_ON */

#if (OCU_TAUD0_CH13_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD0_CH13_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
ISR(TAUD0_CH13_CAT2_ISR)                                                                                                /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, OCU_CODE_FAST) TAUD0_CH13_ISR(void)                                                              /* PRQA S 1503 # JV-01 */
#endif
{
  Ocu_HW_Taud_CbkNotification((uint8)OCU_TAUD0_CH13);
}
#endif /* End of OCU_TAUD0_CH13_ISR_API == STD_ON */

#if (OCU_TAUD0_CH15_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD0_CH15_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
ISR(TAUD0_CH15_CAT2_ISR)                                                                                                /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, OCU_CODE_FAST) TAUD0_CH15_ISR(void)                                                              /* PRQA S 1503 # JV-01 */
#endif
{
  Ocu_HW_Taud_CbkNotification((uint8)OCU_TAUD0_CH15);
}
#endif /* End of OCU_TAUD0_CH15_ISR_API == STD_ON */

#if (OCU_TAUD1_CH01_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD1_CH01_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
ISR(TAUD1_CH01_CAT2_ISR)                                                                                                /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, OCU_CODE_FAST) TAUD1_CH01_ISR(void)                                                              /* PRQA S 1503 # JV-01 */
#endif
{
  Ocu_HW_Taud_CbkNotification((uint8)OCU_TAUD1_CH01);
}
#endif /* End of OCU_TAUD1_CH01_ISR_API == STD_ON */

#if (OCU_TAUD1_CH03_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD1_CH03_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
ISR(TAUD1_CH03_CAT2_ISR)                                                                                                /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, OCU_CODE_FAST) TAUD1_CH03_ISR(void)                                                              /* PRQA S 1503 # JV-01 */
#endif
{
  Ocu_HW_Taud_CbkNotification((uint8)OCU_TAUD1_CH03);
}
#endif /* End of OCU_TAUD1_CH03_ISR_API == STD_ON */

#if (OCU_TAUD1_CH05_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD1_CH05_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
ISR(TAUD1_CH05_CAT2_ISR)                                                                                                /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, OCU_CODE_FAST) TAUD1_CH05_ISR(void)                                                              /* PRQA S 1503 # JV-01 */
#endif
{
  Ocu_HW_Taud_CbkNotification((uint8)OCU_TAUD1_CH05);
}
#endif /* End of OCU_TAUD1_CH05_ISR_API == STD_ON */

#if (OCU_TAUD1_CH07_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD1_CH07_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
ISR(TAUD1_CH07_CAT2_ISR)                                                                                                /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, OCU_CODE_FAST) TAUD1_CH07_ISR(void)                                                              /* PRQA S 1503 # JV-01 */
#endif
{
  Ocu_HW_Taud_CbkNotification((uint8)OCU_TAUD1_CH07);
}
#endif /* End of OCU_TAUD1_CH07_ISR_API == STD_ON */

#if (OCU_TAUD1_CH09_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD1_CH09_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
ISR(TAUD1_CH09_CAT2_ISR)                                                                                                /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, OCU_CODE_FAST) TAUD1_CH09_ISR(void)                                                              /* PRQA S 1503 # JV-01 */
#endif
{
  Ocu_HW_Taud_CbkNotification((uint8)OCU_TAUD1_CH09);
}
#endif /* End of OCU_TAUD1_CH09_ISR_API == STD_ON */

#if (OCU_TAUD1_CH11_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD1_CH11_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
ISR(TAUD1_CH11_CAT2_ISR)                                                                                                /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, OCU_CODE_FAST) TAUD1_CH11_ISR(void)                                                              /* PRQA S 1503 # JV-01 */
#endif
{
  Ocu_HW_Taud_CbkNotification((uint8)OCU_TAUD1_CH11);
}
#endif /* End of OCU_TAUD1_CH11_ISR_API == STD_ON */

#if (OCU_TAUD1_CH13_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD1_CH13_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
ISR(TAUD1_CH13_CAT2_ISR)                                                                                                /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, OCU_CODE_FAST) TAUD1_CH13_ISR(void)                                                              /* PRQA S 1503 # JV-01 */
#endif
{
  Ocu_HW_Taud_CbkNotification((uint8)OCU_TAUD1_CH13);
}
#endif /* End of OCU_TAUD1_CH13_ISR_API == STD_ON */

#if (OCU_TAUD1_CH15_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD1_CH15_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
ISR(TAUD1_CH15_CAT2_ISR)                                                                                                /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, OCU_CODE_FAST) TAUD1_CH15_ISR(void)                                                              /* PRQA S 1503 # JV-01 */
#endif
{
  Ocu_HW_Taud_CbkNotification((uint8)OCU_TAUD1_CH15);
}
#endif /* End of OCU_TAUD1_CH15_ISR_API == STD_ON */

#if (OCU_TAUD2_CH01_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD2_CH01_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
ISR(TAUD2_CH01_CAT2_ISR)                                                                                                /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, OCU_CODE_FAST) TAUD2_CH01_ISR(void)                                                              /* PRQA S 1503 # JV-01 */
#endif
{
  Ocu_HW_Taud_CbkNotification((uint8)OCU_TAUD2_CH01);
}
#endif /* End of OCU_TAUD2_CH01_ISR_API == STD_ON */

#if (OCU_TAUD2_CH03_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD2_CH03_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
ISR(TAUD2_CH03_CAT2_ISR)                                                                                                /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, OCU_CODE_FAST) TAUD2_CH03_ISR(void)                                                              /* PRQA S 1503 # JV-01 */
#endif
{
  Ocu_HW_Taud_CbkNotification((uint8)OCU_TAUD2_CH03);
}
#endif /* End of OCU_TAUD2_CH03_ISR_API == STD_ON */

#if (OCU_TAUD2_CH05_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD2_CH05_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
ISR(TAUD2_CH05_CAT2_ISR)                                                                                                /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, OCU_CODE_FAST) TAUD2_CH05_ISR(void)                                                              /* PRQA S 1503 # JV-01 */
#endif
{
  Ocu_HW_Taud_CbkNotification((uint8)OCU_TAUD2_CH05);
}
#endif /* End of OCU_TAUD2_CH05_ISR_API == STD_ON */

#if (OCU_TAUD2_CH07_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD2_CH07_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
ISR(TAUD2_CH07_CAT2_ISR)                                                                                                /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, OCU_CODE_FAST) TAUD2_CH07_ISR(void)                                                              /* PRQA S 1503 # JV-01 */
#endif
{
  Ocu_HW_Taud_CbkNotification((uint8)OCU_TAUD2_CH07);
}
#endif /* End of OCU_TAUD2_CH07_ISR_API == STD_ON */

#if (OCU_TAUD2_CH09_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD2_CH09_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
ISR(TAUD2_CH09_CAT2_ISR)                                                                                                /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, OCU_CODE_FAST) TAUD2_CH09_ISR(void)                                                              /* PRQA S 1503 # JV-01 */
#endif
{
  Ocu_HW_Taud_CbkNotification((uint8)OCU_TAUD2_CH09);
}
#endif /* End of OCU_TAUD2_CH09_ISR_API == STD_ON */

#if (OCU_TAUD2_CH11_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD2_CH11_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
ISR(TAUD2_CH11_CAT2_ISR)                                                                                                /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, OCU_CODE_FAST) TAUD2_CH11_ISR(void)                                                              /* PRQA S 1503 # JV-01 */
#endif
{
  Ocu_HW_Taud_CbkNotification((uint8)OCU_TAUD2_CH11);
}
#endif /* End of OCU_TAUD2_CH11_ISR_API == STD_ON */

#if (OCU_TAUD2_CH13_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD2_CH13_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
ISR(TAUD2_CH13_CAT2_ISR)                                                                                                /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, OCU_CODE_FAST) TAUD2_CH13_ISR(void)                                                              /* PRQA S 1503 # JV-01 */
#endif
{
  Ocu_HW_Taud_CbkNotification((uint8)OCU_TAUD2_CH13);
}
#endif /* End of OCU_TAUD2_CH13_ISR_API == STD_ON */

#if (OCU_TAUD2_CH15_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD2_CH15_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
ISR(TAUD2_CH15_CAT2_ISR)                                                                                                /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, OCU_CODE_FAST) TAUD2_CH15_ISR(void)                                                              /* PRQA S 1503 # JV-01 */
#endif
{
  Ocu_HW_Taud_CbkNotification((uint8)OCU_TAUD2_CH15);
}
#endif /* End of OCU_TAUD2_CH15_ISR_API == STD_ON */

#if (OCU_TAUD3_CH01_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD3_CH01_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
ISR(TAUD3_CH01_CAT2_ISR)                                                                                                /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, OCU_CODE_FAST) TAUD3_CH01_ISR(void)                                                              /* PRQA S 1503 # JV-01 */
#endif
{
  Ocu_HW_Taud_CbkNotification((uint8)OCU_TAUD3_CH01);
}
#endif /* End of OCU_TAUD3_CH01_ISR_API == STD_ON */

#if (OCU_TAUD3_CH03_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD3_CH03_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
ISR(TAUD3_CH03_CAT2_ISR)                                                                                                /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, OCU_CODE_FAST) TAUD3_CH03_ISR(void)                                                              /* PRQA S 1503 # JV-01 */
#endif
{
  Ocu_HW_Taud_CbkNotification((uint8)OCU_TAUD3_CH03);
}
#endif /* End of OCU_TAUD3_CH03_ISR_API == STD_ON */

#if (OCU_TAUD3_CH05_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD3_CH05_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
ISR(TAUD3_CH05_CAT2_ISR)                                                                                                /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, OCU_CODE_FAST) TAUD3_CH05_ISR(void)                                                              /* PRQA S 1503 # JV-01 */
#endif
{
  Ocu_HW_Taud_CbkNotification((uint8)OCU_TAUD3_CH05);
}
#endif /* End of OCU_TAUD3_CH05_ISR_API == STD_ON */

#if (OCU_TAUD3_CH07_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD3_CH07_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
ISR(TAUD3_CH07_CAT2_ISR)                                                                                                /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, OCU_CODE_FAST) TAUD3_CH07_ISR(void)                                                              /* PRQA S 1503 # JV-01 */
#endif
{
  Ocu_HW_Taud_CbkNotification((uint8)OCU_TAUD3_CH07);
}
#endif /* End of OCU_TAUD3_CH07_ISR_API == STD_ON */

#if (OCU_TAUD3_CH09_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD3_CH09_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
ISR(TAUD3_CH09_CAT2_ISR)                                                                                                /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, OCU_CODE_FAST) TAUD3_CH09_ISR(void)                                                              /* PRQA S 1503 # JV-01 */
#endif
{
  Ocu_HW_Taud_CbkNotification((uint8)OCU_TAUD3_CH09);
}
#endif /* End of OCU_TAUD3_CH09_ISR_API == STD_ON */

#if (OCU_TAUD3_CH11_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD3_CH11_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
ISR(TAUD3_CH11_CAT2_ISR)                                                                                                /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, OCU_CODE_FAST) TAUD3_CH11_ISR(void)                                                              /* PRQA S 1503 # JV-01 */
#endif
{
  Ocu_HW_Taud_CbkNotification((uint8)OCU_TAUD3_CH11);
}
#endif /* End of OCU_TAUD3_CH11_ISR_API == STD_ON */

#if (OCU_TAUD3_CH13_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD3_CH13_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
ISR(TAUD3_CH13_CAT2_ISR)                                                                                                /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, OCU_CODE_FAST) TAUD3_CH13_ISR(void)                                                              /* PRQA S 1503 # JV-01 */
#endif
{
  Ocu_HW_Taud_CbkNotification((uint8)OCU_TAUD3_CH13);
}
#endif /* End of OCU_TAUD3_CH13_ISR_API == STD_ON */

#if (OCU_TAUD3_CH15_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_TAUD3_CH15_CAT2_ISR) || (OCU_ISR_CATEGORY_2 == STD_ON)
ISR(TAUD3_CH15_CAT2_ISR)                                                                                                /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, OCU_CODE_FAST) TAUD3_CH15_ISR(void)                                                              /* PRQA S 1503 # JV-01 */
#endif
{
  Ocu_HW_Taud_CbkNotification((uint8)OCU_TAUD3_CH15);
}
#endif /* End of OCU_TAUD3_CH15_ISR_API == STD_ON */

#define OCU_STOP_SEC_CODE_FAST
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* OCU_TIMER_IP_TAUD == STD_ON */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
