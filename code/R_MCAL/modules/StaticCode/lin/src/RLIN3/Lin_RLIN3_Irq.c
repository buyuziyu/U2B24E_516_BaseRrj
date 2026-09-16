/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Lin_RLIN3_Irq.c                                                                                     */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2019-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* ISR functions of the LIN Driver Component.                                                                         */
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
 *
 * 2.4.0:  30/06/2025  : Remove the SW-VERSION from header of file
 * 2.3.2:  25/04/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 Release
 * 2.3.1:  31/03/2025  : Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02 Release
 * 2.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00(D) U2Bx Final Release
 * 2.1.2:  31/10/2024  : As part of QAC 9.5.0 support, following changes are made:
 *                       1. Update SW-VERSION to 2.1.2
 *                       2. Fix QAC findings
 *                       3. Remove redundant QAC message
 * 2.0.0:  26/07/2023  : Add information about CWE violation ID
 * 1.4.3:  14/04/2022  : Update SW-VERSION to 1.4.3
 * 1.3.2:  04/03/2022  : Update SW-VERSION to 1.4.2
 * 1.3.1:  02/07/2021  : Add QAC message 9.5.0.
 *                       Format source code to 120 characters.
 *                       Improve Violation tag (remove START/END).
 * 1.2.0:  26/08/2020  : Release.
 * 1.1.0:  19/06/2020  : Release.
 * 1.0.1:  25/03/2020  : Update Format dd/mm/yyyy and revision format.
 * 1.0.0:  12/03/2019  : Initial Version.
 *
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Lin header file */
#include "Lin.h"

/* Global RAM variables header file */
#include "Lin_Ram.h"

/* Header file for Lin_Irq.c */
#include "Lin_RLIN3_Irq.h"

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define LIN_RLIN3_IRQ_C_AR_RELEASE_MAJOR_VERSION    LIN_AR_RELEASE_MAJOR_VERSION_VALUE
#define LIN_RLIN3_IRQ_C_AR_RELEASE_MINOR_VERSION    LIN_AR_RELEASE_MINOR_VERSION_VALUE
#define LIN_RLIN3_IRQ_C_AR_RELEASE_REVISION_VERSION LIN_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define LIN_RLIN3_IRQ_C_SW_MAJOR_VERSION            LIN_SW_MAJOR_VERSION_VALUE
#define LIN_RLIN3_IRQ_C_SW_MINOR_VERSION            LIN_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:3408)    : '%s' has external linkage and is being defined without any previous declaration.             */
/* Rule                : CERTCCM DCL07, MISRA C:2012 Rule-8.4, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : It is accepted, due to the declaration will be taken care by Os.                             */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1503)    : The function '%1s' is defined but is not used within this project.                           */
/* Rule                : CERTCCM MSC07, MISRA C:2012 Rule-2.1, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : This is accepted, due to the module's API is exported for user's usage.                      */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:5087)    : Use of #include directive after code fragment.                                               */
/* Rule                : MISRA C:2012 Rule-20.1                                                                       */
/* JV-01 Justification : This is done as per Memory Requirement, (MEMMAP003 - Specification of Memory Mapping).       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (LIN_RLIN3_IRQ_AR_RELEASE_MAJOR_VERSION != LIN_RLIN3_IRQ_C_AR_RELEASE_MAJOR_VERSION)
#error "Lin_RLIN3_Irq.c : Mismatch in Release Major Version"
#endif

#if (LIN_RLIN3_IRQ_AR_RELEASE_MINOR_VERSION != LIN_RLIN3_IRQ_C_AR_RELEASE_MINOR_VERSION)
#error "Lin_RLIN3_Irq.c : Mismatch in Release Minor Version"
#endif

#if (LIN_RLIN3_IRQ_AR_RELEASE_REVISION_VERSION != LIN_RLIN3_IRQ_C_AR_RELEASE_REVISION_VERSION)
#error "Lin_RLIN3_Irq.c : Mismatch in Release Revision Version"
#endif

#if (LIN_RLIN3_IRQ_SW_MAJOR_VERSION != LIN_RLIN3_IRQ_C_SW_MAJOR_VERSION)
#error "Lin_RLIN3_Irq.c : Mismatch in Software Major Version"
#endif

#if (LIN_RLIN3_IRQ_SW_MINOR_VERSION != LIN_RLIN3_IRQ_C_SW_MINOR_VERSION)
#error "Lin_RLIN3_Irq.c : Mismatch in Software Minor Version"
#endif

/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                    LinChannel_0                                                    **
***********************************************************************************************************************/
#if (LIN_CHANNEL0_CONFIGURED == STD_ON)
#define LIN_START_SEC_CODE_FAST
#include "Lin_MemMap.h"

/***********************************************************************************************************************
** Function Name        : LIN_CHANNELn_TX_ISR
**
** Service ID           : NA
**
** Description          : These are Interrupt routines for the RLIN3n
**                        Transmission, where n represents the RLIN3n channels.
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
** Function(s) invoked  : Lin_TxIsr
**
** Registers Used       : None
**
** Reference ID         : LIN_DUD_ACT_010
***********************************************************************************************************************/
/* RLIN3n Transmission Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL0_TX_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL0_TX_CAT2_ISR)                                                                                           /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL0_TX_ISR(void)                                                         /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_TxIsr(LIN_CHANNEL0);
}

/***********************************************************************************************************************
** Function Name        : LIN_CHANNELn_RX_ISR
**
** Service ID           : NA
**
** Description          : These are Interrupt routines for the RLIN3n
**                        Reception, where n represents the RLIN3n channels.
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
** Function(s) invoked  : Lin_RxIsr
**
** Registers Used       : None
**
** Reference ID         : LIN_DUD_ACT_011
***********************************************************************************************************************/
/* RLIN3n Successful Reception Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL0_RX_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL0_RX_CAT2_ISR)                                                                                           /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL0_RX_ISR(void)                                                         /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_RxIsr(LIN_CHANNEL0);
}

/***********************************************************************************************************************
** Function Name        : LIN_CHANNELn_ERR_ISR
**
** Service ID           : NA
**
** Description          : These are Interrupt routines for the RLIN3n
**                        Error, where n represents the RLIN3n channels.
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
** Function(s) invoked  : Lin_ErrIsr
**
** Registers Used       : None
**
** Reference ID         : LIN_DUD_ACT_012
***********************************************************************************************************************/
/* RLIN3n Status Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL0_ERR_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL0_ERR_CAT2_ISR)                                                                                          /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL0_ERR_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_ErrIsr(LIN_CHANNEL0);
}
#define LIN_STOP_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* #if (LIN_CHANNEL0_CONFIGURED == STD_ON) */

/***********************************************************************************************************************
**                                                    LinChannel_1                                                    **
***********************************************************************************************************************/
#if (LIN_CHANNEL1_CONFIGURED == STD_ON)
#define LIN_START_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* RLIN3n Transmission Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL1_TX_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL1_TX_CAT2_ISR)                                                                                           /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL1_TX_ISR(void)                                                         /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_TxIsr(LIN_CHANNEL1);
}

/* RLIN3n Successful Reception Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL1_RX_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL1_RX_CAT2_ISR)                                                                                           /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL1_RX_ISR(void)                                                         /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_RxIsr(LIN_CHANNEL1);
}

/* RLIN3n Status Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL1_ERR_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL1_ERR_CAT2_ISR)                                                                                          /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL1_ERR_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_ErrIsr(LIN_CHANNEL1);
}
#define LIN_STOP_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* #if (LIN_CHANNEL1_CONFIGURED == STD_ON) */
/***********************************************************************************************************************
**                                                    LinChannel_2                                                    **
***********************************************************************************************************************/
#if (LIN_CHANNEL2_CONFIGURED == STD_ON)
#define LIN_START_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* RLIN3n Transmission Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL2_TX_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL2_TX_CAT2_ISR)                                                                                           /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL2_TX_ISR(void)                                                         /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_TxIsr(LIN_CHANNEL2);
}

/* RLIN3n Successful Reception Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL2_RX_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL2_RX_CAT2_ISR)                                                                                           /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL2_RX_ISR(void)                                                         /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_RxIsr(LIN_CHANNEL2);
}

/* RLIN3n Status Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL2_ERR_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL2_ERR_CAT2_ISR)                                                                                          /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL2_ERR_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_ErrIsr(LIN_CHANNEL2);
}
#define LIN_STOP_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* #if (LIN_CHANNEL2_CONFIGURED == STD_ON) */

/***********************************************************************************************************************
**                                                    LinChannel_3                                                    **
***********************************************************************************************************************/
#if (LIN_CHANNEL3_CONFIGURED == STD_ON)
#define LIN_START_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* RLIN3n Transmission Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL3_TX_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL3_TX_CAT2_ISR)                                                                                           /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL3_TX_ISR(void)                                                         /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_TxIsr(LIN_CHANNEL3);
}

/* RLIN3n Successful Reception Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL3_RX_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL3_RX_CAT2_ISR)                                                                                           /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL3_RX_ISR(void)                                                         /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_RxIsr(LIN_CHANNEL3);
}

/* RLIN3n Status Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL3_ERR_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL3_ERR_CAT2_ISR)                                                                                          /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL3_ERR_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_ErrIsr(LIN_CHANNEL3);
}
#define LIN_STOP_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* #if (LIN_CHANNEL3_CONFIGURED == STD_ON) */

/***********************************************************************************************************************
**                                                    LinChannel_4                                                    **
***********************************************************************************************************************/
#if (LIN_CHANNEL4_CONFIGURED == STD_ON)
#define LIN_START_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* RLIN3n Transmission Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL4_TX_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL4_TX_CAT2_ISR)                                                                                           /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL4_TX_ISR(void)                                                         /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_TxIsr(LIN_CHANNEL4);
}

/* RLIN3n Successful Reception Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL4_RX_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL4_RX_CAT2_ISR)                                                                                           /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL4_RX_ISR(void)                                                         /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_RxIsr(LIN_CHANNEL4);
}

/* RLIN3n Status Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL4_ERR_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL4_ERR_CAT2_ISR)                                                                                          /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL4_ERR_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_ErrIsr(LIN_CHANNEL4);
}
#define LIN_STOP_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* #if (LIN_CHANNEL4_CONFIGURED == STD_ON) */

/***********************************************************************************************************************
**                                                    LinChannel_5                                                    **
***********************************************************************************************************************/
#if (LIN_CHANNEL5_CONFIGURED == STD_ON)
#define LIN_START_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* RLIN3n Transmission Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL5_TX_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL5_TX_CAT2_ISR)                                                                                           /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL5_TX_ISR(void)                                                         /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_TxIsr(LIN_CHANNEL5);
}

/* RLIN3n Successful Reception Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL5_RX_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL5_RX_CAT2_ISR)                                                                                           /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL5_RX_ISR(void)                                                         /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_RxIsr(LIN_CHANNEL5);
}

/* RLIN3n Status Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL5_ERR_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL5_ERR_CAT2_ISR)                                                                                          /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL5_ERR_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_ErrIsr(LIN_CHANNEL5);
}
#define LIN_STOP_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* #if (LIN_CHANNEL5_CONFIGURED == STD_ON) */

/***********************************************************************************************************************
**                                                    LinChannel_6                                                    **
***********************************************************************************************************************/
#if (LIN_CHANNEL6_CONFIGURED == STD_ON)
#define LIN_START_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* RLIN3n Transmission Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL6_TX_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL6_TX_CAT2_ISR)                                                                                           /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL6_TX_ISR(void)                                                         /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_TxIsr(LIN_CHANNEL6);
}

/* RLIN3n Successful Reception Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL6_RX_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL6_RX_CAT2_ISR)                                                                                           /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL6_RX_ISR(void)                                                         /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_RxIsr(LIN_CHANNEL6);
}

/* RLIN3n Status Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL6_ERR_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL6_ERR_CAT2_ISR)                                                                                          /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL6_ERR_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_ErrIsr(LIN_CHANNEL6);
}
#define LIN_STOP_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* #if (LIN_CHANNEL6_CONFIGURED == STD_ON) */

/***********************************************************************************************************************
**                                                    LinChannel_7                                                    **
***********************************************************************************************************************/
#if (LIN_CHANNEL7_CONFIGURED == STD_ON)
#define LIN_START_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* RLIN3n Transmission Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL7_TX_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL7_TX_CAT2_ISR)                                                                                           /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL7_TX_ISR(void)                                                         /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_TxIsr(LIN_CHANNEL7);
}

/* RLIN3n Successful Reception Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL7_RX_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL7_RX_CAT2_ISR)                                                                                           /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL7_RX_ISR(void)                                                         /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_RxIsr(LIN_CHANNEL7);
}

/* RLIN3n Status Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL7_ERR_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL7_ERR_CAT2_ISR)                                                                                          /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL7_ERR_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_ErrIsr(LIN_CHANNEL7);
}
#define LIN_STOP_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* #if (LIN_CHANNEL7_CONFIGURED == STD_ON) */

/***********************************************************************************************************************
**                                                    LinChannel_8                                                    **
***********************************************************************************************************************/
#if (LIN_CHANNEL8_CONFIGURED == STD_ON)
#define LIN_START_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* RLIN3n Transmission Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL8_TX_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL8_TX_CAT2_ISR)                                                                                           /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL8_TX_ISR(void)                                                         /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_TxIsr(LIN_CHANNEL8);
}

/* RLIN3n Successful Reception Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL8_RX_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL8_RX_CAT2_ISR)                                                                                           /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL8_RX_ISR(void)                                                         /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_RxIsr(LIN_CHANNEL8);
}

/* RLIN3n Status Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL8_ERR_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL8_ERR_CAT2_ISR)                                                                                          /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL8_ERR_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_ErrIsr(LIN_CHANNEL8);
}
#define LIN_STOP_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* #if (LIN_CHANNEL8_CONFIGURED == STD_ON) */

/***********************************************************************************************************************
**                                                    LinChannel_9                                                    **
***********************************************************************************************************************/
#if (LIN_CHANNEL9_CONFIGURED == STD_ON)
#define LIN_START_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* RLIN3n Transmission Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL9_TX_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL9_TX_CAT2_ISR)                                                                                           /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL9_TX_ISR(void)                                                         /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_TxIsr(LIN_CHANNEL9);
}

/* RLIN3n Successful Reception Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL9_RX_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL9_RX_CAT2_ISR)                                                                                           /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL9_RX_ISR(void)                                                         /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_RxIsr(LIN_CHANNEL9);
}

/* RLIN3n Status Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL9_ERR_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL9_ERR_CAT2_ISR)                                                                                          /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL9_ERR_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_ErrIsr(LIN_CHANNEL9);
}
#define LIN_STOP_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* #if (LIN_CHANNEL9_CONFIGURED == STD_ON) */

/***********************************************************************************************************************
**                                                   LinChannel_10                                                    **
***********************************************************************************************************************/
#if (LIN_CHANNEL10_CONFIGURED == STD_ON)
#define LIN_START_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* RLIN3n Transmission Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL10_TX_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL10_TX_CAT2_ISR)                                                                                          /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL10_TX_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_TxIsr(LIN_CHANNEL10);
}

/* RLIN3n Successful Reception Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL10_RX_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL10_RX_CAT2_ISR)                                                                                          /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL10_RX_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_RxIsr(LIN_CHANNEL10);
}

/* RLIN3n Status Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL10_ERR_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL10_ERR_CAT2_ISR)                                                                                         /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL10_ERR_ISR(void)                                                       /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_ErrIsr(LIN_CHANNEL10);
}
#define LIN_STOP_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* #if (LIN_CHANNEL10_CONFIGURED == STD_ON) */

/***********************************************************************************************************************
**                                                   LinChannel_11                                                    **
***********************************************************************************************************************/
#if (LIN_CHANNEL11_CONFIGURED == STD_ON)
#define LIN_START_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* RLIN3n Transmission Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL11_TX_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL11_TX_CAT2_ISR)                                                                                          /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL11_TX_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_TxIsr(LIN_CHANNEL11);
}

/* RLIN3n Successful Reception Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL11_RX_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL11_RX_CAT2_ISR)                                                                                          /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL11_RX_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_RxIsr(LIN_CHANNEL11);
}

/* RLIN3n Status Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL11_ERR_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL11_ERR_CAT2_ISR)                                                                                         /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL11_ERR_ISR(void)                                                       /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_ErrIsr(LIN_CHANNEL11);
}
#define LIN_STOP_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* #if (LIN_CHANNEL11_CONFIGURED == STD_ON) */

/***********************************************************************************************************************
**                                                   LinChannel_12                                                    **
***********************************************************************************************************************/
#if (LIN_CHANNEL12_CONFIGURED == STD_ON)
#define LIN_START_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* RLIN3n Transmission Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL12_TX_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL12_TX_CAT2_ISR)                                                                                          /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL12_TX_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_TxIsr(LIN_CHANNEL12);
}

/* RLIN3n Successful Reception Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL12_RX_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL12_RX_CAT2_ISR)                                                                                          /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL12_RX_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_RxIsr(LIN_CHANNEL12);
}

/* RLIN3n Status Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL12_ERR_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL12_ERR_CAT2_ISR)                                                                                         /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL12_ERR_ISR(void)                                                       /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_ErrIsr(LIN_CHANNEL12);
}
#define LIN_STOP_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* #if (LIN_CHANNEL12_CONFIGURED == STD_ON) */

/***********************************************************************************************************************
**                                                   LinChannel_13                                                    **
***********************************************************************************************************************/
#if (LIN_CHANNEL13_CONFIGURED == STD_ON)
#define LIN_START_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* RLIN3n Transmission Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL13_TX_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL13_TX_CAT2_ISR)                                                                                          /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL13_TX_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_TxIsr(LIN_CHANNEL13);
}

/* RLIN3n Successful Reception Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL13_RX_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL13_RX_CAT2_ISR)                                                                                          /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL13_RX_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_RxIsr(LIN_CHANNEL13);
}

/* RLIN3n Status Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL13_ERR_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL13_ERR_CAT2_ISR)                                                                                         /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL13_ERR_ISR(void)                                                       /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_ErrIsr(LIN_CHANNEL13);
}
#define LIN_STOP_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* #if (LIN_CHANNEL13_CONFIGURED == STD_ON) */

/***********************************************************************************************************************
**                                                   LinChannel_14                                                    **
***********************************************************************************************************************/
#if (LIN_CHANNEL14_CONFIGURED == STD_ON)
#define LIN_START_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* RLIN3n Transmission Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL14_TX_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL14_TX_CAT2_ISR)                                                                                          /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL14_TX_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_TxIsr(LIN_CHANNEL14);
}

/* RLIN3n Successful Reception Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL14_RX_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL14_RX_CAT2_ISR)                                                                                          /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL14_RX_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_RxIsr(LIN_CHANNEL14);
}

/* RLIN3n Status Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL14_ERR_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL14_ERR_CAT2_ISR)                                                                                         /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL14_ERR_ISR(void)                                                       /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_ErrIsr(LIN_CHANNEL14);
}
#define LIN_STOP_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* #if (LIN_CHANNEL14_CONFIGURED == STD_ON) */

/***********************************************************************************************************************
**                                                   LinChannel_15                                                    **
***********************************************************************************************************************/
#if (LIN_CHANNEL15_CONFIGURED == STD_ON)
#define LIN_START_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* RLIN3n Transmission Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL15_TX_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL15_TX_CAT2_ISR)                                                                                          /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL15_TX_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_TxIsr(LIN_CHANNEL15);
}

/* RLIN3n Successful Reception Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL15_RX_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL15_RX_CAT2_ISR)                                                                                          /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL15_RX_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_RxIsr(LIN_CHANNEL15);
}

/* RLIN3n Status Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL15_ERR_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL15_ERR_CAT2_ISR)                                                                                         /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL15_ERR_ISR(void)                                                       /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_ErrIsr(LIN_CHANNEL15);
}
#define LIN_STOP_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* #if (LIN_CHANNEL15_CONFIGURED == STD_ON) */

/***********************************************************************************************************************
**                                                   LinChannel_16                                                    **
***********************************************************************************************************************/
#if (LIN_CHANNEL16_CONFIGURED == STD_ON)
#define LIN_START_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* RLIN3n Transmission Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL16_TX_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL16_TX_CAT2_ISR)                                                                                          /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL16_TX_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_TxIsr(LIN_CHANNEL16);
}

/* RLIN3n Successful Reception Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL16_RX_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL16_RX_CAT2_ISR)                                                                                          /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL16_RX_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_RxIsr(LIN_CHANNEL16);
}

/* RLIN3n Status Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL16_ERR_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL16_ERR_CAT2_ISR)                                                                                         /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL16_ERR_ISR(void)                                                       /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_ErrIsr(LIN_CHANNEL16);
}
#define LIN_STOP_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* #if (LIN_CHANNEL16_CONFIGURED == STD_ON) */

/***********************************************************************************************************************
**                                                   LinChannel_17                                                    **
***********************************************************************************************************************/
#if (LIN_CHANNEL17_CONFIGURED == STD_ON)
#define LIN_START_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* RLIN3n Transmission Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL17_TX_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL17_TX_CAT2_ISR)                                                                                          /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL17_TX_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_TxIsr(LIN_CHANNEL17);
}

/* RLIN3n Successful Reception Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL17_RX_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL17_RX_CAT2_ISR)                                                                                          /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL17_RX_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_RxIsr(LIN_CHANNEL17);
}

/* RLIN3n Status Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL17_ERR_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL17_ERR_CAT2_ISR)                                                                                         /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL17_ERR_ISR(void)                                                       /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_ErrIsr(LIN_CHANNEL17);
}
#define LIN_STOP_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* #if (LIN_CHANNEL17_CONFIGURED == STD_ON) */

/***********************************************************************************************************************
**                                                   LinChannel_18                                                    **
***********************************************************************************************************************/
#if (LIN_CHANNEL18_CONFIGURED == STD_ON)
#define LIN_START_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* RLIN3n Transmission Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL18_TX_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL18_TX_CAT2_ISR)                                                                                          /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL18_TX_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_TxIsr(LIN_CHANNEL18);
}

/* RLIN3n Successful Reception Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL18_RX_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL18_RX_CAT2_ISR)                                                                                          /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL18_RX_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_RxIsr(LIN_CHANNEL18);
}

/* RLIN3n Status Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL18_ERR_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL18_ERR_CAT2_ISR)                                                                                         /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL18_ERR_ISR(void)                                                       /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_ErrIsr(LIN_CHANNEL18);
}
#define LIN_STOP_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* #if (LIN_CHANNEL18_CONFIGURED == STD_ON) */

/***********************************************************************************************************************
**                                                   LinChannel_19                                                    **
***********************************************************************************************************************/
#if (LIN_CHANNEL19_CONFIGURED == STD_ON)
#define LIN_START_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* RLIN3n Transmission Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL19_TX_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL19_TX_CAT2_ISR)                                                                                          /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL19_TX_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_TxIsr(LIN_CHANNEL19);
}

/* RLIN3n Successful Reception Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL19_RX_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL19_RX_CAT2_ISR)                                                                                          /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL19_RX_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_RxIsr(LIN_CHANNEL19);
}

/* RLIN3n Status Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL19_ERR_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL19_ERR_CAT2_ISR)                                                                                         /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL19_ERR_ISR(void)                                                       /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_ErrIsr(LIN_CHANNEL19);
}
#define LIN_STOP_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* #if (LIN_CHANNEL19_CONFIGURED == STD_ON) */

/***********************************************************************************************************************
**                                                   LinChannel_20                                                    **
***********************************************************************************************************************/
#if (LIN_CHANNEL20_CONFIGURED == STD_ON)
#define LIN_START_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* RLIN3n Transmission Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL20_TX_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL20_TX_CAT2_ISR)                                                                                          /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL20_TX_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_TxIsr(LIN_CHANNEL20);
}

/* RLIN3n Successful Reception Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL20_RX_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL20_RX_CAT2_ISR)                                                                                          /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL20_RX_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_RxIsr(LIN_CHANNEL20);
}

/* RLIN3n Status Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL20_ERR_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL20_ERR_CAT2_ISR)                                                                                         /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL20_ERR_ISR(void)                                                       /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_ErrIsr(LIN_CHANNEL20);
}
#define LIN_STOP_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* #if (LIN_CHANNEL20_CONFIGURED == STD_ON) */

/***********************************************************************************************************************
**                                                   LinChannel_21                                                    **
***********************************************************************************************************************/
#if (LIN_CHANNEL21_CONFIGURED == STD_ON)
#define LIN_START_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* RLIN3n Transmission Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL21_TX_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL21_TX_CAT2_ISR)                                                                                          /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL21_TX_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_TxIsr(LIN_CHANNEL21);
}

/* RLIN3n Successful Reception Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL21_RX_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL21_RX_CAT2_ISR)                                                                                          /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL21_RX_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_RxIsr(LIN_CHANNEL21);
}

/* RLIN3n Status Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL21_ERR_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL21_ERR_CAT2_ISR)                                                                                         /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL21_ERR_ISR(void)                                                       /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_ErrIsr(LIN_CHANNEL21);
}
#define LIN_STOP_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* #if (LIN_CHANNEL21_CONFIGURED == STD_ON) */

/***********************************************************************************************************************
**                                                   LinChannel_22                                                    **
***********************************************************************************************************************/
#if (LIN_CHANNEL22_CONFIGURED == STD_ON)
#define LIN_START_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* RLIN3n Transmission Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL22_TX_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL22_TX_CAT2_ISR)                                                                                          /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL22_TX_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_TxIsr(LIN_CHANNEL22);
}

/* RLIN3n Successful Reception Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL22_RX_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL22_RX_CAT2_ISR)                                                                                          /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL22_RX_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_RxIsr(LIN_CHANNEL22);
}

/* RLIN3n Status Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL22_ERR_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL22_ERR_CAT2_ISR)                                                                                         /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL22_ERR_ISR(void)                                                       /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_ErrIsr(LIN_CHANNEL22);
}
#define LIN_STOP_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* #if (LIN_CHANNEL22_CONFIGURED == STD_ON) */

/***********************************************************************************************************************
**                                                   LinChannel_23                                                    **
***********************************************************************************************************************/
#if (LIN_CHANNEL23_CONFIGURED == STD_ON)
#define LIN_START_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* RLIN3n Transmission Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL23_TX_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL23_TX_CAT2_ISR)                                                                                          /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL23_TX_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_TxIsr(LIN_CHANNEL23);
}

/* RLIN3n Successful Reception Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL23_RX_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL23_RX_CAT2_ISR)                                                                                          /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL23_RX_ISR(void)                                                        /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_RxIsr(LIN_CHANNEL23);
}

/* RLIN3n Status Interrupt */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL23_ERR_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
ISR(LIN_CHANNEL23_ERR_CAT2_ISR)                                                                                         /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL23_ERR_ISR(void)                                                       /* PRQA S 1503 # JV-01 */
#endif
{
  Lin_ErrIsr(LIN_CHANNEL23);
}
#define LIN_STOP_SEC_CODE_FAST
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* #if (LIN_CHANNEL23_CONFIGURED == STD_ON) */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
