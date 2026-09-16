/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Icu_ATU_Irq.c                                                                                       */
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
 * 2.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release 
 * 2.1.2:  31/10/2024  : Update SW-VERSION for Ver22.01.02 Beta2 Release 
 *                       As part of support GTM HWIP into common code, following changes are made:
 *                       1. Add preprocesser ICU_ATU_TIMER_UNIT_USED
 * 2.0.1:  18/10/2023  : Remove QAC message 0857
 * 2.0.0:  03/08/2023  : #include "Icu_Mapping.h" update to #include "Icu_MemMap.h" 
 *                       Remove all multi-instance including methods
 *                       Remove all supported multi-instance header file
 * 1.4.3:  17/04/2022  : Merge QAC message from U2Ax, E2x and U2Bx
 * 1.4.1:  18/10/2021  : Add QAC message 9.5.0
 *                       Add new ISR for TimerC14
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
/* Included for Icu.h inclusion and macro definitions */
#include "Icu.h"
/* Included for declaration of the Icu_CbkNotification() function */
#include "Icu_ATU_LLDriver.h"
/* Included for declaration of the ISRs */
#include "Icu_ATU_Irq.h"

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define ICU_ATU_IRQ_C_AR_RELEASE_MAJOR_VERSION    ICU_AR_RELEASE_MAJOR_VERSION_VALUE
#define ICU_ATU_IRQ_C_AR_RELEASE_MINOR_VERSION    ICU_AR_RELEASE_MINOR_VERSION_VALUE
#define ICU_ATU_IRQ_C_AR_RELEASE_REVISION_VERSION ICU_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define ICU_ATU_IRQ_C_SW_MAJOR_VERSION            ICU_SW_MAJOR_VERSION_VALUE
#define ICU_ATU_IRQ_C_SW_MINOR_VERSION            ICU_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (ICU_ATU_IRQ_AR_RELEASE_MAJOR_VERSION != ICU_ATU_IRQ_C_AR_RELEASE_MAJOR_VERSION)
  #error "Icu_ATU_Irq.c : Mismatch in Release Major Version"
#endif

#if (ICU_ATU_IRQ_AR_RELEASE_MINOR_VERSION != ICU_ATU_IRQ_C_AR_RELEASE_MINOR_VERSION)
  #error "Icu_ATU_Irq.c : Mismatch in Release Minor Version"
#endif

#if (ICU_ATU_IRQ_AR_RELEASE_REVISION_VERSION != ICU_ATU_IRQ_C_AR_RELEASE_REVISION_VERSION)
  #error "Icu_ATU_Irq.c : Mismatch in Release Patch Version"
#endif

#if (ICU_ATU_IRQ_SW_MAJOR_VERSION != ICU_ATU_IRQ_C_SW_MAJOR_VERSION)
  #error "Icu_ATU_Irq.c : Mismatch in Software Major Version"
#endif

#if (ICU_ATU_IRQ_SW_MINOR_VERSION != ICU_ATU_IRQ_C_SW_MINOR_VERSION)
  #error "Icu_ATU_Irq.c : Mismatch in Software Minor Version"
#endif

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/
#if (ICU_ATU_TIMER_UNIT_USED == STD_ON)
/***********************************************************************************************************************
** Function Name        : ATU_TIMERA_CHm_ISR
**
** Service ID           : NA
**
** Description          : These are Interrupt routines for the timer ATU TIMERA Channel m, where m represents 
**                        channels associated for each Unit.
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
** Function(s) invoked  : Icu_TimerIsr
**
** Registers Used       : None
**
** Reference ID          : ICU_DUD_ACT_084
***********************************************************************************************************************/
#if (ICU_ATU_TIMERA0_CH00_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERA0_CH00_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(ATU_TIMERA0_CH00_CAT2_ISR)                                                                                          /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERA0_CH00_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_TimerIsr((Icu_ChannelType)ICU_ATU_TIMERA0_CH00);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_ATU_TIMERA0_CH00_ISR_API == STD_ON */

#if (ICU_ATU_TIMERA0_CH01_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERA0_CH01_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(ATU_TIMERA0_CH01_CAT2_ISR)                                                                                          /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERA0_CH01_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_TimerIsr((Icu_ChannelType)ICU_ATU_TIMERA0_CH01);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_ATU_TIMERA0_CH01_ISR_API == STD_ON */

#if (ICU_ATU_TIMERA0_CH02_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERA0_CH02_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(ATU_TIMERA0_CH02_CAT2_ISR)                                                                                          /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERA0_CH02_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_TimerIsr((Icu_ChannelType)ICU_ATU_TIMERA0_CH02);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_ATU_TIMERA0_CH02_ISR_API == STD_ON */

#if (ICU_ATU_TIMERA0_CH03_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERA0_CH03_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(ATU_TIMERA0_CH03_CAT2_ISR)                                                                                          /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERA0_CH03_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_TimerIsr((Icu_ChannelType)ICU_ATU_TIMERA0_CH03);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_ATU_TIMERA0_CH03_ISR_API == STD_ON */

#if (ICU_ATU_TIMERA0_CH04_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERA0_CH04_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(ATU_TIMERA0_CH04_CAT2_ISR)                                                                                          /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERA0_CH04_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_TimerIsr((Icu_ChannelType)ICU_ATU_TIMERA0_CH04);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_ATU_TIMERA0_CH04_ISR_API == STD_ON */

#if (ICU_ATU_TIMERA0_CH05_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERA0_CH05_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(ATU_TIMERA0_CH05_CAT2_ISR)                                                                                          /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERA0_CH05_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_TimerIsr((Icu_ChannelType)ICU_ATU_TIMERA0_CH05);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_ATU_TIMERA0_CH05_ISR_API == STD_ON */

#if (ICU_ATU_TIMERA0_CH06_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERA0_CH06_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(ATU_TIMERA0_CH06_CAT2_ISR)                                                                                          /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERA0_CH06_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_TimerIsr((Icu_ChannelType)ICU_ATU_TIMERA0_CH06);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_ATU_TIMERA0_CH06_ISR_API == STD_ON */

#if (ICU_ATU_TIMERA0_CH07_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERA0_CH07_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(ATU_TIMERA0_CH07_CAT2_ISR)                                                                                          /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERA0_CH07_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_TimerIsr((Icu_ChannelType)ICU_ATU_TIMERA0_CH07);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_ATU_TIMERA0_CH07_ISR_API == STD_ON */

/***********************************************************************************************************************
** Function Name        : ATU_TIMERC_CHm_ISR
**
** Service ID           : NA
**
** Description          : These are Interrupt routines for the timer ATU TIMERCn Channel m, where n represents 
**                        the ATU TIMERC Units and m represents channels associated for each Unit.
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
** Function(s) invoked  : Icu_TimerIsr
**
** Registers Used       : None
**
** Reference ID          : ICU_DUD_ACT_085
***********************************************************************************************************************/

#if (ICU_ATU_TIMERC0_CH00_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC0_CH00_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(ATU_TIMERC0_CH00_CAT2_ISR)                                                                                          /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC0_CH00_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_TimerIsr((Icu_ChannelType)ICU_ATU_TIMERC0_CH00);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_ATU_TIMERC0_CH00_ISR_API == STD_ON */

#if (ICU_ATU_TIMERC0_CH01_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC0_CH01_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(ATU_TIMERC0_CH01_CAT2_ISR)                                                                                          /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC0_CH01_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_TimerIsr((Icu_ChannelType)ICU_ATU_TIMERC0_CH01);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_ATU_TIMERC0_CH01_ISR_API == STD_ON */

#if (ICU_ATU_TIMERC0_CH02_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC0_CH02_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(ATU_TIMERC0_CH02_CAT2_ISR)                                                                                          /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC0_CH02_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_TimerIsr((Icu_ChannelType)ICU_ATU_TIMERC0_CH02);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_ATU_TIMERC0_CH02_ISR_API == STD_ON */

#if (ICU_ATU_TIMERC0_CH03_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC0_CH03_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(ATU_TIMERC0_CH03_CAT2_ISR)                                                                                          /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC0_CH03_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_TimerIsr((Icu_ChannelType)ICU_ATU_TIMERC0_CH03);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_ATU_TIMERC0_CH03_ISR_API == STD_ON */

#if (ICU_ATU_TIMERC1_CH00_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC1_CH00_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(ATU_TIMERC1_CH00_CAT2_ISR)                                                                                          /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC1_CH00_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_TimerIsr((Icu_ChannelType)ICU_ATU_TIMERC1_CH00);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_ATU_TIMERC1_CH00_ISR_API == STD_ON */

#if (ICU_ATU_TIMERC1_CH01_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC1_CH01_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(ATU_TIMERC1_CH01_CAT2_ISR)                                                                                          /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC1_CH01_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_TimerIsr((Icu_ChannelType)ICU_ATU_TIMERC1_CH01);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_ATU_TIMERC1_CH01_ISR_API == STD_ON */

#if (ICU_ATU_TIMERC1_CH02_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC1_CH02_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(ATU_TIMERC1_CH02_CAT2_ISR)                                                                                          /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC1_CH02_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_TimerIsr((Icu_ChannelType)ICU_ATU_TIMERC1_CH02);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_ATU_TIMERC1_CH02_ISR_API == STD_ON */

#if (ICU_ATU_TIMERC1_CH03_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC1_CH03_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(ATU_TIMERC1_CH03_CAT2_ISR)                                                                                          /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC1_CH03_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_TimerIsr((Icu_ChannelType)ICU_ATU_TIMERC1_CH03);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_ATU_TIMERC1_CH03_ISR_API == STD_ON */

#if (ICU_ATU_TIMERC2_CH00_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC2_CH00_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(ATU_TIMERC2_CH00_CAT2_ISR)                                                                                          /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC2_CH00_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_TimerIsr((Icu_ChannelType)ICU_ATU_TIMERC2_CH00);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_ATU_TIMERC2_CH00_ISR_API == STD_ON */

#if (ICU_ATU_TIMERC2_CH01_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC2_CH01_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(ATU_TIMERC2_CH01_CAT2_ISR)                                                                                          /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC2_CH01_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_TimerIsr((Icu_ChannelType)ICU_ATU_TIMERC2_CH01);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_ATU_TIMERC2_CH01_ISR_API == STD_ON */

#if (ICU_ATU_TIMERC2_CH02_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC2_CH02_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(ATU_TIMERC2_CH02_CAT2_ISR)                                                                                          /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC2_CH02_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_TimerIsr((Icu_ChannelType)ICU_ATU_TIMERC2_CH02);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_ATU_TIMERC2_CH02_ISR_API == STD_ON */

#if (ICU_ATU_TIMERC2_CH03_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC2_CH03_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(ATU_TIMERC2_CH03_CAT2_ISR)                                                                                          /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC2_CH03_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_TimerIsr((Icu_ChannelType)ICU_ATU_TIMERC2_CH03);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_ATU_TIMERC2_CH03_ISR_API == STD_ON */

#if (ICU_ATU_TIMERC3_CH00_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC3_CH00_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(ATU_TIMERC3_CH00_CAT2_ISR)                                                                                          /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC3_CH00_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_TimerIsr((Icu_ChannelType)ICU_ATU_TIMERC3_CH00);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_ATU_TIMERC3_CH00_ISR_API == STD_ON */

#if (ICU_ATU_TIMERC3_CH01_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC3_CH01_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(ATU_TIMERC3_CH01_CAT2_ISR)                                                                                          /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC3_CH01_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_TimerIsr((Icu_ChannelType)ICU_ATU_TIMERC3_CH01);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_ATU_TIMERC3_CH01_ISR_API == STD_ON */

#if (ICU_ATU_TIMERC3_CH02_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC3_CH02_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(ATU_TIMERC3_CH02_CAT2_ISR)                                                                                          /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC3_CH02_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_TimerIsr((Icu_ChannelType)ICU_ATU_TIMERC3_CH02);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_ATU_TIMERC3_CH02_ISR_API == STD_ON */

#if (ICU_ATU_TIMERC3_CH03_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC3_CH03_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(ATU_TIMERC3_CH03_CAT2_ISR)                                                                                          /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC3_CH03_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_TimerIsr((Icu_ChannelType)ICU_ATU_TIMERC3_CH03);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_ATU_TIMERC3_CH03_ISR_API == STD_ON */

#if (ICU_ATU_TIMERC4_CH00_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC4_CH00_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(ATU_TIMERC4_CH00_CAT2_ISR)                                                                                          /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC4_CH00_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_TimerIsr((Icu_ChannelType)ICU_ATU_TIMERC4_CH00);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_ATU_TIMERC4_CH00_ISR_API == STD_ON */

#if (ICU_ATU_TIMERC4_CH01_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC4_CH01_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(ATU_TIMERC4_CH01_CAT2_ISR)                                                                                          /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC4_CH01_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_TimerIsr((Icu_ChannelType)ICU_ATU_TIMERC4_CH01);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_ATU_TIMERC4_CH01_ISR_API == STD_ON */

#if (ICU_ATU_TIMERC4_CH02_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC4_CH02_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(ATU_TIMERC4_CH02_CAT2_ISR)                                                                                          /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC4_CH02_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_TimerIsr((Icu_ChannelType)ICU_ATU_TIMERC4_CH02);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_ATU_TIMERC4_CH02_ISR_API == STD_ON */

#if (ICU_ATU_TIMERC4_CH03_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC4_CH03_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(ATU_TIMERC4_CH03_CAT2_ISR)                                                                                          /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC4_CH03_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_TimerIsr((Icu_ChannelType)ICU_ATU_TIMERC4_CH03);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_ATU_TIMERC4_CH03_ISR_API == STD_ON */

#if (ICU_ATU_TIMERC5_CH00_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC5_CH00_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(ATU_TIMERC5_CH00_CAT2_ISR)                                                                                          /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC5_CH00_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_TimerIsr((Icu_ChannelType)ICU_ATU_TIMERC5_CH00);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_ATU_TIMERC5_CH00_ISR_API == STD_ON */

#if (ICU_ATU_TIMERC5_CH01_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC5_CH01_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(ATU_TIMERC5_CH01_CAT2_ISR)                                                                                          /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC5_CH01_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_TimerIsr((Icu_ChannelType)ICU_ATU_TIMERC5_CH01);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_ATU_TIMERC5_CH01_ISR_API == STD_ON */

#if (ICU_ATU_TIMERC5_CH02_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC5_CH02_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(ATU_TIMERC5_CH02_CAT2_ISR)                                                                                          /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC5_CH02_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_TimerIsr((Icu_ChannelType)ICU_ATU_TIMERC5_CH02);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_ATU_TIMERC5_CH02_ISR_API == STD_ON */

#if (ICU_ATU_TIMERC5_CH03_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC5_CH03_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(ATU_TIMERC5_CH03_CAT2_ISR)                                                                                          /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC5_CH03_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_TimerIsr((Icu_ChannelType)ICU_ATU_TIMERC5_CH03);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_ATU_TIMERC5_CH03_ISR_API == STD_ON */

#if (ICU_ATU_TIMERC6_CH00_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC6_CH00_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(ATU_TIMERC6_CH00_CAT2_ISR)                                                                                          /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC6_CH00_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_TimerIsr((Icu_ChannelType)ICU_ATU_TIMERC6_CH00);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_ATU_TIMERC6_CH00_ISR_API == STD_ON */

#if (ICU_ATU_TIMERC6_CH01_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC6_CH01_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(ATU_TIMERC6_CH01_CAT2_ISR)                                                                                          /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC6_CH01_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_TimerIsr((Icu_ChannelType)ICU_ATU_TIMERC6_CH01);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_ATU_TIMERC6_CH01_ISR_API == STD_ON */

#if (ICU_ATU_TIMERC6_CH02_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC6_CH02_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(ATU_TIMERC6_CH02_CAT2_ISR)                                                                                          /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC6_CH02_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_TimerIsr((Icu_ChannelType)ICU_ATU_TIMERC6_CH02);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_ATU_TIMERC6_CH02_ISR_API == STD_ON */

#if (ICU_ATU_TIMERC6_CH03_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC6_CH03_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(ATU_TIMERC6_CH03_CAT2_ISR)                                                                                          /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC6_CH03_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_TimerIsr((Icu_ChannelType)ICU_ATU_TIMERC6_CH03);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_ATU_TIMERC6_CH03_ISR_API == STD_ON */

#if (ICU_ATU_TIMERC7_CH00_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC7_CH00_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(ATU_TIMERC7_CH00_CAT2_ISR)                                                                                          /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC7_CH00_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_TimerIsr((Icu_ChannelType)ICU_ATU_TIMERC7_CH00);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_ATU_TIMERC7_CH00_ISR_API == STD_ON */

#if (ICU_ATU_TIMERC7_CH01_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC7_CH01_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(ATU_TIMERC7_CH01_CAT2_ISR)                                                                                          /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC7_CH01_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_TimerIsr((Icu_ChannelType)ICU_ATU_TIMERC7_CH01);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_ATU_TIMERC7_CH01_ISR_API == STD_ON */

#if (ICU_ATU_TIMERC7_CH02_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC7_CH02_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(ATU_TIMERC7_CH02_CAT2_ISR)                                                                                          /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC7_CH02_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_TimerIsr((Icu_ChannelType)ICU_ATU_TIMERC7_CH02);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_ATU_TIMERC7_CH02_ISR_API == STD_ON */

#if (ICU_ATU_TIMERC7_CH03_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC7_CH03_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(ATU_TIMERC7_CH03_CAT2_ISR)                                                                                          /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC7_CH03_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_TimerIsr((Icu_ChannelType)ICU_ATU_TIMERC7_CH03);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_ATU_TIMERC7_CH03_ISR_API == STD_ON */

#if (ICU_ATU_TIMERC8_CH00_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC8_CH00_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(ATU_TIMERC8_CH00_CAT2_ISR)                                                                                          /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC8_CH00_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_TimerIsr((Icu_ChannelType)ICU_ATU_TIMERC8_CH00);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_ATU_TIMERC8_CH00_ISR_API == STD_ON */

#if (ICU_ATU_TIMERC8_CH01_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC8_CH01_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(ATU_TIMERC8_CH01_CAT2_ISR)                                                                                          /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC8_CH01_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_TimerIsr((Icu_ChannelType)ICU_ATU_TIMERC8_CH01);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_ATU_TIMERC8_CH01_ISR_API == STD_ON */

#if (ICU_ATU_TIMERC8_CH02_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC8_CH02_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(ATU_TIMERC8_CH02_CAT2_ISR)                                                                                          /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC8_CH02_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_TimerIsr((Icu_ChannelType)ICU_ATU_TIMERC8_CH02);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_ATU_TIMERC8_CH02_ISR_API == STD_ON */

#if (ICU_ATU_TIMERC8_CH03_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC8_CH03_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(ATU_TIMERC8_CH03_CAT2_ISR)                                                                                          /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC8_CH03_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_TimerIsr((Icu_ChannelType)ICU_ATU_TIMERC8_CH03);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_ATU_TIMERC8_CH03_ISR_API == STD_ON */

#if (ICU_ATU_TIMERC9_CH00_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC9_CH00_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(ATU_TIMERC9_CH00_CAT2_ISR)                                                                                          /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC9_CH00_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_TimerIsr((Icu_ChannelType)ICU_ATU_TIMERC9_CH00);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_ATU_TIMERC9_CH00_ISR_API == STD_ON */

#if (ICU_ATU_TIMERC9_CH01_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC9_CH01_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(ATU_TIMERC9_CH01_CAT2_ISR)                                                                                          /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC9_CH01_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_TimerIsr((Icu_ChannelType)ICU_ATU_TIMERC9_CH01);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_ATU_TIMERC9_CH01_ISR_API == STD_ON */

#if (ICU_ATU_TIMERC9_CH02_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC9_CH02_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(ATU_TIMERC9_CH02_CAT2_ISR)                                                                                          /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC9_CH02_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_TimerIsr((Icu_ChannelType)ICU_ATU_TIMERC9_CH02);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_ATU_TIMERC9_CH02_ISR_API == STD_ON */

#if (ICU_ATU_TIMERC9_CH03_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC9_CH03_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(ATU_TIMERC9_CH03_CAT2_ISR)                                                                                          /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC9_CH03_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_TimerIsr((Icu_ChannelType)ICU_ATU_TIMERC9_CH03);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_ATU_TIMERC9_CH03_ISR_API == STD_ON */

#if (ICU_ATU_TIMERC10_CH00_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC10_CH00_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(ATU_TIMERC10_CH00_CAT2_ISR)                                                                                         /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC10_CH00_ISR(void)                                                       /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_TimerIsr((Icu_ChannelType)ICU_ATU_TIMERC10_CH00);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_ATU_TIMERC10_CH00_ISR_API == STD_ON */

#if (ICU_ATU_TIMERC10_CH01_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC10_CH01_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(ATU_TIMERC10_CH01_CAT2_ISR)                                                                                         /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC10_CH01_ISR(void)                                                       /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_TimerIsr((Icu_ChannelType)ICU_ATU_TIMERC10_CH01);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_ATU_TIMERC10_CH01_ISR_API == STD_ON */

#if (ICU_ATU_TIMERC10_CH02_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC10_CH02_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(ATU_TIMERC10_CH02_CAT2_ISR)                                                                                         /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC10_CH02_ISR(void)                                                       /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_TimerIsr((Icu_ChannelType)ICU_ATU_TIMERC10_CH02);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_ATU_TIMERC10_CH02_ISR_API == STD_ON */

#if (ICU_ATU_TIMERC10_CH03_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC10_CH03_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(ATU_TIMERC10_CH03_CAT2_ISR)                                                                                         /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC10_CH03_ISR(void)                                                       /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_TimerIsr((Icu_ChannelType)ICU_ATU_TIMERC10_CH03);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_ATU_TIMERC10_CH03_ISR_API == STD_ON */

#if (ICU_ATU_TIMERC11_CH00_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC11_CH00_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(ATU_TIMERC11_CH00_CAT2_ISR)                                                                                         /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC11_CH00_ISR(void)                                                       /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_TimerIsr((Icu_ChannelType)ICU_ATU_TIMERC11_CH00);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_ATU_TIMERC11_CH00_ISR_API == STD_ON */

#if (ICU_ATU_TIMERC11_CH01_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC11_CH01_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(ATU_TIMERC11_CH01_CAT2_ISR)                                                                                         /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC11_CH01_ISR(void)                                                       /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_TimerIsr((Icu_ChannelType)ICU_ATU_TIMERC11_CH01);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_ATU_TIMERC11_CH01_ISR_API == STD_ON */

#if (ICU_ATU_TIMERC11_CH02_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC11_CH02_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(ATU_TIMERC11_CH02_CAT2_ISR)                                                                                         /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC11_CH02_ISR(void)                                                       /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_TimerIsr((Icu_ChannelType)ICU_ATU_TIMERC11_CH02);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_ATU_TIMERC11_CH02_ISR_API == STD_ON */

#if (ICU_ATU_TIMERC11_CH03_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC11_CH03_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(ATU_TIMERC11_CH03_CAT2_ISR)                                                                                         /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC11_CH03_ISR(void)                                                       /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_TimerIsr((Icu_ChannelType)ICU_ATU_TIMERC11_CH03);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_ATU_TIMERC11_CH03_ISR_API == STD_ON */

#if (ICU_ATU_TIMERC12_CH00_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC12_CH00_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(ATU_TIMERC12_CH00_CAT2_ISR)                                                                                         /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC12_CH00_ISR(void)                                                       /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_TimerIsr((Icu_ChannelType)ICU_ATU_TIMERC12_CH00);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_ATU_TIMERC12_CH00_ISR_API == STD_ON */

#if (ICU_ATU_TIMERC12_CH01_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC12_CH01_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(ATU_TIMERC12_CH01_CAT2_ISR)                                                                                         /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC12_CH01_ISR(void)                                                       /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_TimerIsr((Icu_ChannelType)ICU_ATU_TIMERC12_CH01);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_ATU_TIMERC12_CH01_ISR_API == STD_ON */

#if (ICU_ATU_TIMERC12_CH02_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC12_CH02_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(ATU_TIMERC12_CH02_CAT2_ISR)                                                                                         /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC12_CH02_ISR(void)                                                       /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_TimerIsr((Icu_ChannelType)ICU_ATU_TIMERC12_CH02);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_ATU_TIMERC12_CH02_ISR_API == STD_ON */

#if (ICU_ATU_TIMERC12_CH03_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC12_CH03_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(ATU_TIMERC12_CH03_CAT2_ISR)                                                                                         /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC12_CH03_ISR(void)                                                       /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_TimerIsr((Icu_ChannelType)ICU_ATU_TIMERC12_CH03);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_ATU_TIMERC12_CH03_ISR_API == STD_ON */

#if (ICU_ATU_TIMERC13_CH00_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC13_CH00_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(ATU_TIMERC13_CH00_CAT2_ISR)                                                                                         /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC13_CH00_ISR(void)                                                       /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_TimerIsr((Icu_ChannelType)ICU_ATU_TIMERC13_CH00);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_ATU_TIMERC13_CH00_ISR_API == STD_ON */

#if (ICU_ATU_TIMERC13_CH01_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC13_CH01_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(ATU_TIMERC13_CH01_CAT2_ISR)                                                                                         /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC13_CH01_ISR(void)                                                       /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_TimerIsr((Icu_ChannelType)ICU_ATU_TIMERC13_CH01);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_ATU_TIMERC13_CH01_ISR_API == STD_ON */

#if (ICU_ATU_TIMERC13_CH02_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC13_CH02_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(ATU_TIMERC13_CH02_CAT2_ISR)                                                                                         /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC13_CH02_ISR(void)                                                       /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_TimerIsr((Icu_ChannelType)ICU_ATU_TIMERC13_CH02);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_ATU_TIMERC13_CH02_ISR_API == STD_ON */

#if (ICU_ATU_TIMERC13_CH03_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC13_CH03_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(ATU_TIMERC13_CH03_CAT2_ISR)                                                                                         /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC13_CH03_ISR(void)                                                       /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_TimerIsr((Icu_ChannelType)ICU_ATU_TIMERC13_CH03);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_ATU_TIMERC13_CH03_ISR_API == STD_ON */

#if (ICU_ATU_TIMERC14_CH00_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC14_CH00_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(ATU_TIMERC14_CH00_CAT2_ISR)                                                                                         /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC14_CH00_ISR(void)                                                       /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_TimerIsr((Icu_ChannelType)ICU_ATU_TIMERC14_CH00);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_ATU_TIMERC14_CH00_ISR_API == STD_ON */

#if (ICU_ATU_TIMERC14_CH01_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC14_CH01_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(ATU_TIMERC14_CH01_CAT2_ISR)                                                                                         /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC14_CH01_ISR(void)                                                       /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_TimerIsr((Icu_ChannelType)ICU_ATU_TIMERC14_CH01);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_ATU_TIMERC14_CH01_ISR_API == STD_ON */

#if (ICU_ATU_TIMERC14_CH02_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC14_CH02_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(ATU_TIMERC14_CH02_CAT2_ISR)                                                                                         /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC14_CH02_ISR(void)                                                       /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_TimerIsr((Icu_ChannelType)ICU_ATU_TIMERC14_CH02);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_ATU_TIMERC14_CH02_ISR_API == STD_ON */

#if (ICU_ATU_TIMERC14_CH03_ISR_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined(Os_ATU_TIMERC14_CH03_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
ISR(ATU_TIMERC14_CH03_CAT2_ISR)                                                                                         /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ICU_CODE_FAST) ATU_TIMERC14_CH03_ISR(void)                                                       /* PRQA S 1503 # JV-01 */
#endif
{
  Icu_TimerIsr((Icu_ChannelType)ICU_ATU_TIMERC14_CH03);
}

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ICU_ATU_TIMERC14_CH03_ISR_API == STD_ON */
#endif /* End of #if (STD_ON == ICU_ATU_TIMER_UNIT_USED) */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
