/*====================================================================================================================*/
/* Project      = RH850/X2x AR4 MCAL Development                                                                      */
/* Module       = Pwm_DIAG_Irq.c                                                                                      */
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
 ** 2.5.1: 30/06/2025 : Remove SW-VERSION in header comment                                                           **
 ** 2.5.0: 30/06/2025 : Update SW-VERSION for U2Ax Ver22.01.00(D) Final Release                                       **
 ** 2.4.0: 31/05/2025 : Update SW-VERSION for U2Cx Ver21.01.01 Final Release                                          **
 ** 2.3.2: 29/04/2025 : Update SW-VERSION for U2Ax Ver22.00.04 Beta Release                                           **
 ** 2.3.1: 31/03/2025 : Update SW-VERSION for U2Ax Ver22.00.03 Beta2 Release                                          **
 ** 2.3.0: 28/02/2025 : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release                       **
 ** 2.2.0: 31/12/2024 : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release                                 **
 ** 2.1.2: 31/10/2024 : Update SW-VERSION for Ver22.00.05 U2Cx Beta2 Release                                          **
 ** 2.1.1: 30/08/2024 : As part of U2Cx Diag support, following changes are made                                      **
 **                     1. Insert QAC message                                                                         **
 ** 2.0.2: 14/12/2023 : Update version in header comment                                                              **
 ** 2.0.1: 25/10/2023 : Update version in header comment                                                              **
 ** 2.0.0: 05/07/2023 : Update from "Pwm_Mapping.h to "Pwm_MemMap.h"                                                  **
 ** 1.4.3: 08/04/2022 : Corrected error content from "Pwm_DIAG_Irq.c : Mismatch in Release Patch Version" to          **
 **                     "Pwm_DIAG_Irq.c : Mismatch in Release Revision Version"                                       **
 ** 1.0.0: 23/08/2021 : Initial Version.                                                                              **
 **                                                                                                                   */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (1:1503)    : The function '%1s' is defined but is not used within this project.                           */
/* Rule                : CERTCCM MSC07, MISRA C:2012 Rule-2.1, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : This is accepted, due to the module's API is exported for user's usage.                      */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3408)    : %s' has external linkage and is being defined without any previous declaration.              */
/* Rule                : CERTCCM DCL07, MISRA C:2012 Rule-8.4, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : It is accepted, due to the declaration will be taken care by Os                              */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:5087)    : Use of #include directive after code fragment.                                               */
/* Rule                : MISRA C:2012 Rule-20.1                                                                       */
/* JV-01 Justification : This is done as per Memory Requirement, (MEMMAP003 - Specification of Memory Mapping).       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                              Include Section                                                       **
***********************************************************************************************************************/
/* Included for Pwm.h inclusion and macro definitions */
#include "Pwm.h"
/* Included for declaration of the ISRs */
#include "Pwm_DIAG_Irq.h"
#include "Pwm_DIAG_LLDriver.h"
#include "Pwm_DIAG_PBTypes.h"
/***********************************************************************************************************************
**                                              Version Information                                                   **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define PWM_DIAG_IRQ_C_AR_RELEASE_MAJOR_VERSION       PWM_AR_RELEASE_MAJOR_VERSION_VALUE
#define PWM_DIAG_IRQ_C_AR_RELEASE_MINOR_VERSION       PWM_AR_RELEASE_MINOR_VERSION_VALUE
#define PWM_DIAG_IRQ_C_AR_RELEASE_REVISION_VERSION    PWM_AR_RELEASE_REVISION_VERSION_VALUE

/* Module software version information */
#define PWM_DIAG_IRQ_C_SW_MAJOR_VERSION               PWM_SW_MAJOR_VERSION_VALUE
#define PWM_DIAG_IRQ_C_SW_MINOR_VERSION               PWM_SW_MINOR_VERSION_VALUE
#define PWM_DIAG_IRQ_C_SW_PATCH_VERSION               PWM_SW_PATCH_VERSION_VALUE
/***********************************************************************************************************************
**                                              Version Check                                                         **
***********************************************************************************************************************/
#if (PWM_DIAG_IRQ_AR_RELEASE_MAJOR_VERSION != PWM_DIAG_IRQ_C_AR_RELEASE_MAJOR_VERSION)
  #error "Pwm_DIAG_Irq.c : Mismatch in Release Major Version"
#endif
#if (PWM_DIAG_IRQ_AR_RELEASE_MINOR_VERSION != PWM_DIAG_IRQ_C_AR_RELEASE_MINOR_VERSION)
  #error "Pwm_DIAG_Irq.c : Mismatch in Release Minor Version"
#endif
#if (PWM_DIAG_IRQ_AR_RELEASE_REVISION_VERSION != PWM_DIAG_IRQ_C_AR_RELEASE_REVISION_VERSION)
  #error "Pwm_DIAG_Irq.c : Mismatch in Release Revision Version"
#endif

#if (PWM_DIAG_IRQ_SW_MAJOR_VERSION != PWM_DIAG_IRQ_C_SW_MAJOR_VERSION)
  #error "Pwm_DIAG_Irq.c : Mismatch in Software Major Version"
#endif
#if (PWM_DIAG_IRQ_SW_MINOR_VERSION != PWM_DIAG_IRQ_C_SW_MINOR_VERSION)
  #error "Pwm_DIAG_Irq.c : Mismatch in Software Minor Version"
#endif
#if (PWM_DIAG_IRQ_SW_PATCH_VERSION != PWM_DIAG_IRQ_C_SW_PATCH_VERSION)
  #error "Pwm_DIAG_Irq.c : Mismatch in Software Patch Version"
#endif

/***********************************************************************************************************************
**                                              Function Definitions                                                  **
***********************************************************************************************************************/
#if (PWM_DIAG_UNIT_USED == STD_ON)
/***********************************************************************************************************************
** Function Name        : PWGCGxx_ISR
**
** Service ID           : NA
**
** Description          : These are Interrupt routines for Pwm Diag Channels.
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
** Preconditions        : PWGCGxx_ISR_API is STD_ON
**
** Global Variables     : None
**
** Functions invoked    : Pwm_HW_DIAG_Callback
**
** Registers Used       : None
**
** Reference ID         : PWM_DUD_ACT_093
***********************************************************************************************************************/
#define PWM_START_SEC_CODE_FAST
#include "Pwm_MemMap.h"

#if (PWGCG00_ISR_API == STD_ON)
#if defined (Os_PWGCG00_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
ISR(PWGCG00_CAT2_ISR)                                                                                                   /* PRQA S 1503, 3408 # JV-01, JV-01 */
#else /* Defines the CAT1 interrupt mapping */
_INTERRUPT_ FUNC(void, PWM_CODE_FAST) PWGCG00_ISR(void)                                                                 /* PRQA S 1503 # JV-01 */
#endif
{
  /* Nofify Group 0 and GROUP0 (00..31) */
  Pwm_HW_DIAG_Callback(PWM_DIAG_NOTI_GR0, PWM_DIAG_GROUP0);
}
#endif /* End of PWGCG00_ISR_API == STD_ON */


#if (PWGCG01_ISR_API == STD_ON)
#if defined (Os_PWGCG01_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
ISR(PWGCG01_CAT2_ISR)                                                                                                   /* PRQA S 1503, 3408 # JV-01, JV-01 */
#else /* Defines the CAT1 interrupt mapping */
_INTERRUPT_ FUNC(void, PWM_CODE_FAST) PWGCG01_ISR(void)                                                                 /* PRQA S 1503 # JV-01 */
#endif
{
  /* Nofify Group 0 and GROUP1 (32..63) */
  Pwm_HW_DIAG_Callback(PWM_DIAG_NOTI_GR0, PWM_DIAG_GROUP1);
}
#endif /* End of PWGCG01_ISR_API == STD_ON */


#if (PWGCG02_ISR_API == STD_ON)
#if defined (Os_PWGCG02_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
ISR(PWGCG02_CAT2_ISR)                                                                                                   /* PRQA S 3408, 1503 # JV-01, JV-01 */
#else /* Defines the CAT1 interrupt mapping */
_INTERRUPT_ FUNC(void, PWM_CODE_FAST) PWGCG02_ISR(void)                                                                 /* PRQA S 1503 # JV-01 */
#endif
{
  /* Nofify Group 0 and GROUP2 (64..95) */
  Pwm_HW_DIAG_Callback(PWM_DIAG_NOTI_GR0, PWM_DIAG_GROUP2);
}
#endif /* End of PWGCG02_ISR_API == STD_ON */


#if (PWGCG10_ISR_API == STD_ON)
#if defined (Os_PWGCG10_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
ISR(PWGCG10_CAT2_ISR)                                                                                                   /* PRQA S 3408, 1503 # JV-01, JV-01 */
#else /* Defines the CAT1 interrupt mapping */
_INTERRUPT_ FUNC(void, PWM_CODE_FAST) PWGCG10_ISR(void)                                                                 /* PRQA S 1503 # JV-01 */
#endif
{
  /* Nofify Group 1 and GROUP0 (00..31) */
  Pwm_HW_DIAG_Callback(PWM_DIAG_NOTI_GR1, PWM_DIAG_GROUP0);
}
#endif /* End of PWGCG10_ISR_API == STD_ON */


#if (PWGCG11_ISR_API == STD_ON)
#if defined (Os_PWGCG11_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
ISR(PWGCG11_CAT2_ISR)                                                                                                   /* PRQA S 3408, 1503 # JV-01, JV-01 */
#else /* Defines the CAT1 interrupt mapping */
_INTERRUPT_ FUNC(void, PWM_CODE_FAST) PWGCG11_ISR(void)                                                                 /* PRQA S 1503 # JV-01 */
#endif
{
  /* Nofify Group 1 and GROUP1 (32..63) */
  Pwm_HW_DIAG_Callback(PWM_DIAG_NOTI_GR1, PWM_DIAG_GROUP1);
}
#endif /* End of PWGCG11_ISR_API == STD_ON */


#if (PWGCG12_ISR_API == STD_ON)
#if defined (Os_PWGCG12_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
ISR(PWGCG12_CAT2_ISR)                                                                                                   /* PRQA S 3408, 1503 # JV-01, JV-01 */
#else /* Defines the CAT1 interrupt mapping */
_INTERRUPT_ FUNC(void, PWM_CODE_FAST) PWGCG12_ISR(void)                                                                 /* PRQA S 1503 # JV-01 */
#endif
{
  /* Nofify Group 1 and GROUP2 (64..95) */
  Pwm_HW_DIAG_Callback(PWM_DIAG_NOTI_GR1, PWM_DIAG_GROUP2);
}
#endif /* End of PWGCG12_ISR_API == STD_ON */


#if (PWGCG20_ISR_API == STD_ON)
#if defined (Os_PWGCG20_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
ISR(PWGCG20_CAT2_ISR)                                                                                                   /* PRQA S 3408, 1503 # JV-01, JV-01 */
#else /* Defines the CAT1 interrupt mapping */
_INTERRUPT_ FUNC(void, PWM_CODE_FAST) PWGCG20_ISR(void)                                                                 /* PRQA S 1503 # JV-01 */
#endif
{
  /* Nofify Group 2 and GROUP0 (00..31) */
  Pwm_HW_DIAG_Callback(PWM_DIAG_NOTI_GR2, PWM_DIAG_GROUP0);
}
#endif /* End of PWGCG20_ISR_API == STD_ON */


#if (PWGCG21_ISR_API == STD_ON)
#if defined (Os_PWGCG21_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
ISR(PWGCG21_CAT2_ISR)                                                                                                   /* PRQA S 3408, 1503 # JV-01, JV-01 */
#else /* Defines the CAT1 interrupt mapping */
_INTERRUPT_ FUNC(void, PWM_CODE_FAST) PWGCG21_ISR(void)                                                                 /* PRQA S 1503 # JV-01 */
#endif
{
  /* Nofify Group 2 and GROUP1 (32..63) */
  Pwm_HW_DIAG_Callback(PWM_DIAG_NOTI_GR2, PWM_DIAG_GROUP1);
}
#endif /* End of PWGCG21_ISR_API == STD_ON */


#if (PWGCG22_ISR_API == STD_ON)
#if defined (Os_PWGCG22_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
ISR(PWGCG22_CAT2_ISR)                                                                                                   /* PRQA S 3408, 1503 # JV-01, JV-01 */
#else /* Defines the CAT1 interrupt mapping */
_INTERRUPT_ FUNC(void, PWM_CODE_FAST) PWGCG22_ISR(void)                                                                 /* PRQA S 1503 # JV-01 */
#endif
{
  /* Nofify Group 2 and GROUP2 (64..95) */
  Pwm_HW_DIAG_Callback(PWM_DIAG_NOTI_GR2, PWM_DIAG_GROUP2);
}
#endif /* End of PWGCG22_ISR_API == STD_ON */


#if (PWGCG30_ISR_API == STD_ON)
#if defined (Os_PWGCG30_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
ISR(PWGCG30_CAT2_ISR)                                                                                                   /* PRQA S 3408, 1503 # JV-01, JV-01 */
#else /* Defines the CAT1 interrupt mapping */
_INTERRUPT_ FUNC(void, PWM_CODE_FAST) PWGCG30_ISR(void)                                                                 /* PRQA S 1503 # JV-01 */
#endif
{
  /* Nofify Group 3 and GROUP0 (00..31) */
  Pwm_HW_DIAG_Callback(PWM_DIAG_NOTI_GR3, PWM_DIAG_GROUP0);
}
#endif /* End of PWGCG30_ISR_API == STD_ON */


#if (PWGCG31_ISR_API == STD_ON)
#if defined (Os_PWGCG31_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
ISR(PWGCG31_CAT2_ISR)                                                                                                   /* PRQA S 3408, 1503 # JV-01, JV-01 */
#else /* Defines the CAT1 interrupt mapping */
_INTERRUPT_ FUNC(void, PWM_CODE_FAST) PWGCG31_ISR(void)                                                                 /* PRQA S 1503 # JV-01 */
#endif
{
  /* Nofify Group 3 and GROUP1 (32..63) */
  Pwm_HW_DIAG_Callback(PWM_DIAG_NOTI_GR3, PWM_DIAG_GROUP1);
}
#endif /* End of PWGCG31_ISR_API == STD_ON */


#if (PWGCG32_ISR_API == STD_ON)
#if defined (Os_PWGCG32_CAT2_ISR) || (PWM_ISR_CATEGORY_2 == STD_ON)
ISR(PWGCG32_CAT2_ISR)                                                                                                   /* PRQA S 3408, 1503 # JV-01, JV-01 */
#else /* Defines the CAT1 interrupt mapping */
_INTERRUPT_ FUNC(void, PWM_CODE_FAST) PWGCG32_ISR(void)                                                                 /* PRQA S 1503 # JV-01 */
#endif
{
  /* Nofify Group 3 and GROUP2 (64..95) */
  Pwm_HW_DIAG_Callback(PWM_DIAG_NOTI_GR3, PWM_DIAG_GROUP2);
}
#endif /* End of PWGCG32_ISR_API == STD_ON */

#define PWM_STOP_SEC_CODE_FAST
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* End of PWM_DIAG_UNIT_USED == STD_ON */
/***********************************************************************************************************************
**                                              End of File                                                           **
***********************************************************************************************************************/
