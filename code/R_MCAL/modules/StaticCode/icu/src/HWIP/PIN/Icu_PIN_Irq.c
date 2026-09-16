/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Icu_PIN_Irq.c                                                                                       */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.                                                */
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
 * 2.3.1:  31/03/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 and RH850/U2Bx-E MCAL Ver22.00.02 Release
 * 2.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release 
 * 2.1.2:  31/10/2024  : Update SW-VERSION for Ver22.01.02 Beta2 Release 
 *                       As part of support U2Bx-E, following changes are made:
 *                       1. Add INTP44 and INTP45
 * 2.0.1:  25/10/2023  : Update SW-VERSION to 2.0.1
 *         18/10/2023  : Remove QAC message 0857
 * 2.0.0:  03/08/2023  : #include "Icu_Mapping.h" update to #include "Icu_MemMap.h" 
 *                       Remove all multi-instance including methods
 *                       Remove all supported multi-instance header file
 * 1.4.3:  17/04/2022  : Merge QAC message from U2Ax, E2x and U2Bx
 * 1.4.1:  18/10/2021  : Add QAC message 9.5.0
 *         16/09/2021  : Correct preprocessor directives
 * 1.3.2:  30/08/2021  : Change from #include "Icu_MemMap.h" to #include "Icu_Mapping.h".
 * 1.3.1:  02/07/2021  : Add QAC message 9.5.0
 *                       Format source code to 120 characters
 *                       Improve Violation tag (remove START/END)
 * 1.2.0:  17/07/2020  : Release
 * 1.1.0:  19/06/2020  : Release
 * 1.0.0:  25/03/2020  : Initial Version
 */
/**********************************************************************************************************************/

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

/* Included for declaration of the Icu_CbkNotification() function */
#include "Icu_PIN_LLDriver.h"
/* Included for declaration of the ISRs */
#include "Icu_PIN_Irq.h"
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define ICU_PIN_IRQ_C_AR_RELEASE_MAJOR_VERSION    ICU_AR_RELEASE_MAJOR_VERSION_VALUE
#define ICU_PIN_IRQ_C_AR_RELEASE_MINOR_VERSION    ICU_AR_RELEASE_MINOR_VERSION_VALUE
#define ICU_PIN_IRQ_C_AR_RELEASE_REVISION_VERSION ICU_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define ICU_PIN_IRQ_C_SW_MAJOR_VERSION            ICU_SW_MAJOR_VERSION_VALUE
#define ICU_PIN_IRQ_C_SW_MINOR_VERSION            ICU_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (ICU_PIN_IRQ_AR_RELEASE_MAJOR_VERSION != ICU_PIN_IRQ_C_AR_RELEASE_MAJOR_VERSION)
  #error "Icu_PIN_Irq.c : Mismatch in Release Major Version"
#endif

#if (ICU_PIN_IRQ_AR_RELEASE_MINOR_VERSION != ICU_PIN_IRQ_C_AR_RELEASE_MINOR_VERSION)
  #error "Icu_PIN_Irq.c : Mismatch in Release Minor Version"
#endif

#if (ICU_PIN_IRQ_AR_RELEASE_REVISION_VERSION != ICU_PIN_IRQ_C_AR_RELEASE_REVISION_VERSION)
  #error "Icu_PIN_Irq.c : Mismatch in Release Revision Version"
#endif

#if (ICU_PIN_IRQ_SW_MAJOR_VERSION != ICU_PIN_IRQ_C_SW_MAJOR_VERSION)
  #error "Icu_PIN_Irq.c : Mismatch in Software Major Version"
#endif

#if (ICU_PIN_IRQ_SW_MINOR_VERSION != ICU_PIN_IRQ_C_SW_MINOR_VERSION)
  #error "Icu_PIN_Irq.c : Mismatch in Software Minor Version"
#endif

/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/
/* For IRQ */
#if (STD_ON == ICU_IRQ_EDGE_DETECT)

/***********************************************************************************************************************
** Function Name        : EXT_IRQ_CHm_ISR
**
** Service ID           : NA
**
** Description          : These are Interrupt Service routines for the External
**                        Interrupts where m represents instances of external interrupts.
**
** Sync/Async           : Synchronous
**
** Reentrancy           : Non-Reentrant
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
** Function(s) invoked  : Icu_HW_Pin_ExternalInterruptIsr
**
** Registers Used       : None
**
** Reference ID         : ICU_DUD_ACT_086
***********************************************************************************************************************/
#if (ICU_EXT_IRQ_CH00_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"

/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_IRQ_CH00_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(EXT_IRQ_CH00_CAT2_ISR)
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_IRQ_CH00_ISR(void)
#endif
{
  Icu_HW_Pin_ExternalInterruptIsr((Icu_ChannelType)ICU_EXT_IRQ_CH00);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"
#endif /* End of ICU_EXT_IRQ_CH00_ISR_API == STD_ON */

#if (ICU_EXT_IRQ_CH01_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"

/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_IRQ_CH01_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(EXT_IRQ_CH01_CAT2_ISR)
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_IRQ_CH01_ISR(void)
#endif
{
  Icu_HW_Pin_ExternalInterruptIsr((Icu_ChannelType)ICU_EXT_IRQ_CH01);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"
#endif /* End of ICU_EXT_IRQ_CH01_ISR_API == STD_ON */

#if (ICU_EXT_IRQ_CH02_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"

/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_IRQ_CH02_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(EXT_IRQ_CH02_CAT2_ISR)
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_IRQ_CH02_ISR(void)
#endif
{
  Icu_HW_Pin_ExternalInterruptIsr((Icu_ChannelType)ICU_EXT_IRQ_CH02);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"
#endif /* End of ICU_EXT_IRQ_CH02_ISR_API == STD_ON */

#if (ICU_EXT_IRQ_CH03_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"

/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_IRQ_CH03_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(EXT_IRQ_CH03_CAT2_ISR)
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_IRQ_CH03_ISR(void)
#endif
{
  Icu_HW_Pin_ExternalInterruptIsr((Icu_ChannelType)ICU_EXT_IRQ_CH03);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"
#endif /* End of ICU_EXT_IRQ_CH03_ISR_API == STD_ON */

#if (ICU_EXT_IRQ_CH04_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"

/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_IRQ_CH04_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(EXT_IRQ_CH04_CAT2_ISR)
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_IRQ_CH04_ISR(void)
#endif
{
  Icu_HW_Pin_ExternalInterruptIsr((Icu_ChannelType)ICU_EXT_IRQ_CH04);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"
#endif /* End of ICU_EXT_IRQ_CH04_ISR_API == STD_ON */

#if (ICU_EXT_IRQ_CH05_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"

/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_IRQ_CH05_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(EXT_IRQ_CH05_CAT2_ISR)
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_IRQ_CH05_ISR(void)
#endif
{
  Icu_HW_Pin_ExternalInterruptIsr((Icu_ChannelType)ICU_EXT_IRQ_CH05);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"
#endif /* End of ICU_EXT_IRQ_CH05_ISR_API == STD_ON */

#if (ICU_EXT_IRQ_CH06_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"

/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_IRQ_CH06_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(EXT_IRQ_CH06_CAT2_ISR)
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_IRQ_CH06_ISR(void)
#endif
{
  Icu_HW_Pin_ExternalInterruptIsr((Icu_ChannelType)ICU_EXT_IRQ_CH06);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"
#endif /* End of ICU_EXT_IRQ_CH06_ISR_API == STD_ON */

#if (ICU_EXT_IRQ_CH07_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"

/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_IRQ_CH07_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(EXT_IRQ_CH07_CAT2_ISR)
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_IRQ_CH07_ISR(void)
#endif
{
  Icu_HW_Pin_ExternalInterruptIsr((Icu_ChannelType)ICU_EXT_IRQ_CH07);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"
#endif /* End of ICU_EXT_IRQ_CH07_ISR_API == STD_ON */

#if (ICU_EXT_IRQ_CH08_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"

/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_IRQ_CH08_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(EXT_IRQ_CH08_CAT2_ISR)
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_IRQ_CH08_ISR(void)
#endif
{
  Icu_HW_Pin_ExternalInterruptIsr((Icu_ChannelType)ICU_EXT_IRQ_CH08);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"
#endif /* End of ICU_EXT_IRQ_CH08_ISR_API == STD_ON */

#if (ICU_EXT_IRQ_CH09_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"

/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_IRQ_CH09_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(EXT_IRQ_CH09_CAT2_ISR)
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_IRQ_CH09_ISR(void)
#endif
{
  Icu_HW_Pin_ExternalInterruptIsr((Icu_ChannelType)ICU_EXT_IRQ_CH09);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"
#endif /* End of ICU_EXT_IRQ_CH09_ISR_API == STD_ON */

#if (ICU_EXT_IRQ_CH10_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"

/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_IRQ_CH10_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(EXT_IRQ_CH10_CAT2_ISR)
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_IRQ_CH10_ISR(void)
#endif
{
  Icu_HW_Pin_ExternalInterruptIsr((Icu_ChannelType)ICU_EXT_IRQ_CH10);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"
#endif /* End of ICU_EXT_IRQ_CH10_ISR_API == STD_ON */

#if (ICU_EXT_IRQ_CH11_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"

/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_IRQ_CH11_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(EXT_IRQ_CH11_CAT2_ISR)
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_IRQ_CH11_ISR(void)
#endif
{
  Icu_HW_Pin_ExternalInterruptIsr((Icu_ChannelType)ICU_EXT_IRQ_CH11);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"
#endif /* End of ICU_EXT_IRQ_CH11_ISR_API == STD_ON */

#endif /* End of STD_ON == ICU_IRQ_EDGE_DETECT */
/* For INTP */
#if (STD_ON == ICU_INTP_EDGE_DETECT)

/***********************************************************************************************************************
** Function Name        : EXT_INTP_CHm_ISR
**
** Service ID           : NA
**
** Description          : These are Interrupt Service routines for the External
**                        Interrupts where m represents instances of external
**                        interrupts (0 to 15).
**
** Sync/Async           : Synchronous
**
** Reentrancy           : Non-Reentrant
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
** Function(s) invoked  : Icu_HW_Pin_ExternalInterruptIsr
**
** Registers Used       : None
**
** Reference ID         : ICU_DUD_ACT_068
***********************************************************************************************************************/
#if (ICU_EXT_INTP_CH00_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"

/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH00_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(EXT_INTP_CH00_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH00_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_HW_Pin_ExternalInterruptIsr(ICU_EXT_INTP_CH00);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_EXT_INTP_CH00_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH01_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH01_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(EXT_INTP_CH01_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH01_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_HW_Pin_ExternalInterruptIsr(ICU_EXT_INTP_CH01);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_EXT_INTP_CH01_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH02_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH02_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(EXT_INTP_CH02_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH02_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_HW_Pin_ExternalInterruptIsr(ICU_EXT_INTP_CH02);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_EXT_INTP_CH02_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH03_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH03_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(EXT_INTP_CH03_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH03_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_HW_Pin_ExternalInterruptIsr(ICU_EXT_INTP_CH03);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_EXT_INTP_CH03_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH04_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH04_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(EXT_INTP_CH04_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH04_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_HW_Pin_ExternalInterruptIsr(ICU_EXT_INTP_CH04);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_EXT_INTP_CH04_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH05_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH05_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(EXT_INTP_CH05_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH05_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_HW_Pin_ExternalInterruptIsr(ICU_EXT_INTP_CH05);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_EXT_INTP_CH05_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH06_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH06_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(EXT_INTP_CH06_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH06_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_HW_Pin_ExternalInterruptIsr(ICU_EXT_INTP_CH06);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_EXT_INTP_CH06_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH07_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH07_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(EXT_INTP_CH07_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH07_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_HW_Pin_ExternalInterruptIsr(ICU_EXT_INTP_CH07);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_EXT_INTP_CH07_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH08_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH08_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(EXT_INTP_CH08_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH08_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_HW_Pin_ExternalInterruptIsr(ICU_EXT_INTP_CH08);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_EXT_INTP_CH08_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH09_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH09_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(EXT_INTP_CH09_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH09_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_HW_Pin_ExternalInterruptIsr(ICU_EXT_INTP_CH09);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_EXT_INTP_CH09_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH10_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH10_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(EXT_INTP_CH10_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH10_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_HW_Pin_ExternalInterruptIsr(ICU_EXT_INTP_CH10);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_EXT_INTP_CH10_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH11_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH11_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(EXT_INTP_CH11_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH11_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_HW_Pin_ExternalInterruptIsr(ICU_EXT_INTP_CH11);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_EXT_INTP_CH11_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH12_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH12_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(EXT_INTP_CH12_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH12_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_HW_Pin_ExternalInterruptIsr(ICU_EXT_INTP_CH12);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_EXT_INTP_CH12_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH13_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH13_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(EXT_INTP_CH13_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH13_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_HW_Pin_ExternalInterruptIsr(ICU_EXT_INTP_CH13);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_EXT_INTP_CH13_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH14_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH14_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(EXT_INTP_CH14_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH14_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_HW_Pin_ExternalInterruptIsr(ICU_EXT_INTP_CH14);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_EXT_INTP_CH14_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH15_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH15_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(EXT_INTP_CH15_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH15_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_HW_Pin_ExternalInterruptIsr(ICU_EXT_INTP_CH15);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_EXT_INTP_CH15_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH16_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH16_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(EXT_INTP_CH16_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH16_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_HW_Pin_ExternalInterruptIsr(ICU_EXT_INTP_CH16);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_EXT_INTP_CH16_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH17_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH17_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(EXT_INTP_CH17_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH17_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_HW_Pin_ExternalInterruptIsr(ICU_EXT_INTP_CH17);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_EXT_INTP_CH17_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH18_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH18_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(EXT_INTP_CH18_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH18_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_HW_Pin_ExternalInterruptIsr(ICU_EXT_INTP_CH18);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_EXT_INTP_CH18_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH19_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH19_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(EXT_INTP_CH19_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH19_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_HW_Pin_ExternalInterruptIsr(ICU_EXT_INTP_CH19);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_EXT_INTP_CH19_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH20_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH20_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(EXT_INTP_CH20_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH20_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_HW_Pin_ExternalInterruptIsr(ICU_EXT_INTP_CH20);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_EXT_INTP_CH20_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH21_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH21_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(EXT_INTP_CH21_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH21_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_HW_Pin_ExternalInterruptIsr(ICU_EXT_INTP_CH21);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_EXT_INTP_CH21_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH22_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH22_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(EXT_INTP_CH22_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH22_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_HW_Pin_ExternalInterruptIsr(ICU_EXT_INTP_CH22);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_EXT_INTP_CH22_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH23_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH23_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(EXT_INTP_CH23_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH23_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_HW_Pin_ExternalInterruptIsr(ICU_EXT_INTP_CH23);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_EXT_INTP_CH23_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH24_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH24_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(EXT_INTP_CH24_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH24_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_HW_Pin_ExternalInterruptIsr(ICU_EXT_INTP_CH24);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_EXT_INTP_CH24_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH25_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH25_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(EXT_INTP_CH25_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH25_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_HW_Pin_ExternalInterruptIsr(ICU_EXT_INTP_CH25);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_EXT_INTP_CH25_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH26_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH26_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(EXT_INTP_CH26_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH26_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_HW_Pin_ExternalInterruptIsr(ICU_EXT_INTP_CH26);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_EXT_INTP_CH26_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH27_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH27_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(EXT_INTP_CH27_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH27_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_HW_Pin_ExternalInterruptIsr(ICU_EXT_INTP_CH27);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_EXT_INTP_CH27_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH28_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH28_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(EXT_INTP_CH28_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH28_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_HW_Pin_ExternalInterruptIsr(ICU_EXT_INTP_CH28);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_EXT_INTP_CH28_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH29_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH29_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(EXT_INTP_CH29_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH29_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_HW_Pin_ExternalInterruptIsr(ICU_EXT_INTP_CH29);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_EXT_INTP_CH29_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH30_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH30_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(EXT_INTP_CH30_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH30_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_HW_Pin_ExternalInterruptIsr(ICU_EXT_INTP_CH30);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_EXT_INTP_CH30_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH31_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH31_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(EXT_INTP_CH31_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH31_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_HW_Pin_ExternalInterruptIsr(ICU_EXT_INTP_CH31);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_EXT_INTP_CH31_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH32_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH32_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(EXT_INTP_CH32_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH32_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_HW_Pin_ExternalInterruptIsr(ICU_EXT_INTP_CH32);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_EXT_INTP_CH32_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH33_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH33_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(EXT_INTP_CH33_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH33_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_HW_Pin_ExternalInterruptIsr(ICU_EXT_INTP_CH33);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_EXT_INTP_CH33_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH34_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH34_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(EXT_INTP_CH34_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH34_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_HW_Pin_ExternalInterruptIsr(ICU_EXT_INTP_CH34);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_EXT_INTP_CH34_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH35_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH35_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(EXT_INTP_CH35_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH35_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_HW_Pin_ExternalInterruptIsr(ICU_EXT_INTP_CH35);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_EXT_INTP_CH35_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH36_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH36_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(EXT_INTP_CH36_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH36_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_HW_Pin_ExternalInterruptIsr(ICU_EXT_INTP_CH36);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_EXT_INTP_CH36_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH37_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH37_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(EXT_INTP_CH37_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH37_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_HW_Pin_ExternalInterruptIsr(ICU_EXT_INTP_CH37);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_EXT_INTP_CH37_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH38_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH38_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(EXT_INTP_CH38_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH38_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_HW_Pin_ExternalInterruptIsr(ICU_EXT_INTP_CH38);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_EXT_INTP_CH38_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH39_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH39_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(EXT_INTP_CH39_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH39_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_HW_Pin_ExternalInterruptIsr(ICU_EXT_INTP_CH39);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_EXT_INTP_CH39_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH40_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH40_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(EXT_INTP_CH40_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH40_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_HW_Pin_ExternalInterruptIsr(ICU_EXT_INTP_CH40);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_EXT_INTP_CH40_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH41_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH41_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(EXT_INTP_CH41_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH41_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_HW_Pin_ExternalInterruptIsr(ICU_EXT_INTP_CH41);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_EXT_INTP_CH41_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH42_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH42_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(EXT_INTP_CH42_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH42_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_HW_Pin_ExternalInterruptIsr(ICU_EXT_INTP_CH42);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_EXT_INTP_CH42_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH43_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH43_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(EXT_INTP_CH43_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH43_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_HW_Pin_ExternalInterruptIsr(ICU_EXT_INTP_CH43);
}
#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_EXT_INTP_CH43_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH44_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH44_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(EXT_INTP_CH44_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH44_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_HW_Pin_ExternalInterruptIsr(ICU_EXT_INTP_CH44);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_EXT_INTP_CH44_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH45_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH45_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(EXT_INTP_CH45_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH45_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_HW_Pin_ExternalInterruptIsr(ICU_EXT_INTP_CH45);
}
#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_EXT_INTP_CH45_ISR_API == STD_ON */

#endif /* End of STD_ON == ICU_INTP_EDGE_DETECT */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
