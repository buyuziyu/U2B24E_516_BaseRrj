/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Eth_ETNE_Irq.c                                                                                      */
/*====================================================================================================================*/
/*                                             COPYRIGHT                                                              */
/*====================================================================================================================*/
/* (c) 2024, 2025 Renesas Electronics Corporation. All rights reserved.                                               */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains Interrupt Service Routine for  Ethernet Driver Component                                        */
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
/* Renesas shall not have any obligation to maintain, service or provide bug fixes for the supplied Product(s)        */
/* and/or the Application.                                                                                            */
/*                                                                                                                    */
/* Each User is solely responsible for determining the appropriateness of using the Product(s) and assumes all risks  */
/* associated with its exercise of rights under this Agreement, including, but not limited to the risks and costs     */
/* of program errors, compliance with applicable laws, damage to or loss of data, programs or equipment,              */
/* and unavailability or interruption of operations.                                                                  */
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
/*                                      Devices:        X2x                                                           */
/*====================================================================================================================*/

/***********************************************************************************************************************
**                                       Revision Control History                                                     **
***********************************************************************************************************************/
/*
 * 2.4.1: 30/06/2025    : Remove the SW-VERSION from header of file
 * 2.4.0: 30/06/2025    : Update SW-VERSION for RH850/Ver22.01.00 (D) U2Ax release
 * 2.4.1: 30/06/2025    : Update SW-VERSION for RH850/Ver22.00.04 U2BxE
 * 2.3.1: 31/03/2025    : Change precompile ETH_GWCA0TSDISISR by ETH_GWCA0_TSDATA_ISR macro
 *                      : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 * 2.3.0: 28/02/2025    : - As per ticket ARDAACJ-680:
 *                        Add new function ETH_ETHA0SGMIIISR, ETH_ETHA1SGMIIISR to support interrupt for SGMII mode
 * 2.2.0: 31/12/2024    : Update SW-VERSION for Ver22.02.00(D) U2Bx Final Release
 * 2.1.2: 31/10/2024    : Increase SW-VERSION to 2.1.2
 * 2.1.1: 31/05/2024    : Initial Version 
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                       Include Section                                                              **
***********************************************************************************************************************/
#include "Eth.h"
#include "Eth_ETNE_Irq.h"
#include "Eth_ETNE_Ram.h"
/* Included for declaration of the function Dem_ReportErrorStatus() */
#include "Dem.h"
/***********************************************************************************************************************
**                                      Version Information                                                           **
***********************************************************************************************************************/

/* AUTOSAR release version information */
#define ETH_ETNE_IRQ_C_AR_RELEASE_MAJOR_VERSION    ETH_AR_RELEASE_MAJOR_VERSION_VALUE
#define ETH_ETNE_IRQ_C_AR_RELEASE_MINOR_VERSION    ETH_AR_RELEASE_MINOR_VERSION_VALUE
#define ETH_ETNE_IRQ_C_AR_RELEASE_REVISION_VERSION ETH_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define ETH_ETNE_IRQ_C_SW_MAJOR_VERSION    ETH_SW_MAJOR_VERSION_VALUE
#define ETH_ETNE_IRQ_C_SW_MINOR_VERSION    ETH_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                      Version Check                                                                 **
***********************************************************************************************************************/

/* Functionality related to R4.0 */
#if (ETH_AR_RELEASE_MAJOR_VERSION != ETH_ETNE_IRQ_C_AR_RELEASE_MAJOR_VERSION)
  #error "Eth_ETNE_Irq.c : Mismatch in Release Major Version"
#endif
#if (ETH_AR_RELEASE_MINOR_VERSION != ETH_ETNE_IRQ_C_AR_RELEASE_MINOR_VERSION)
  #error "Eth_ETNE_Irq.c : Mismatch in Release Minor Version"
#endif
#if (ETH_AR_RELEASE_REVISION_VERSION != ETH_ETNE_IRQ_C_AR_RELEASE_REVISION_VERSION)
  #error "Eth_ETNE_Irq.c : Mismatch in Release Revision Version"
#endif

#if (ETH_SW_MAJOR_VERSION != ETH_ETNE_IRQ_C_SW_MAJOR_VERSION)
  #error "Eth_ETNE_Irq.c : Mismatch in Software Major Version"
#endif
#if (ETH_SW_MINOR_VERSION != ETH_ETNE_IRQ_C_SW_MINOR_VERSION)
  #error "Eth_ETNE_Irq.c : Mismatch in Software Minor Version"
#endif

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
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
/* Message (2:3408)    : %s' has external linkage and is being defined without any previous declaration.              */
/* Rule                : CERTCCM DCL07, MISRA C:2012 Rule-8.4, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : It is accepted, due to the declaration will be taken care by Os                              */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/**                                              Global Data                                                          **
***********************************************************************************************************************/
/***********************************************************************************************************************
**                                             Function Definitions                                                   **
***********************************************************************************************************************/
#define ETH_START_SEC_CODE_FAST
#include "Eth_MemMap.h"

/***********************************************************************************************************************
** Function Name         : ETH_GWCA0DISISR
**
** Service ID            : NA
**
** Description           : Data Interrupt Service Handler
**
** Sync/Async            : NA
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variable(s)    : None
**
** Function(s) invoked   : Eth_Gwca_DIS_Common_Isr
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_523
***********************************************************************************************************************/
#if (ETH_GWCA0_DATA_ISR == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_ETH_GWCA0DISISR_CAT2) || (ETH_ISR_CATEGORY_2 == STD_ON)
ISR(ETH_GWCA0DISISR_CAT2)                                                                                               /* PRQA S 1503, 3408 # JV-01, JV-01 */
#else
 _INTERRUPT_ FUNC(void, ETH_CODE_FAST) ETH_GWCA0DISISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  Eth_Gwca_DIS_Common_Isr(ETH_RSW2_GWCA0);
}
#endif

/***********************************************************************************************************************
** Function Name         : ETH_GWCA0TSDISISR
**
** Service ID            : NA
**
** Description           : Time Stamp Data Interrupt Service Handler  (GWCA0)
**
** Sync/Async            : NA
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variable(s)    : None
**
** Function(s) invoked   : Eth_Gwca_TSDIS_Common_Isr
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_525
***********************************************************************************************************************/
#if (ETH_GWCA0_TSDATA_ISR == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_ETH_GWCA0TSDISISR_CAT2) || (ETH_ISR_CATEGORY_2 == STD_ON)
ISR(ETH_GWCA0TSDISISR_CAT2)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
#else
 _INTERRUPT_ FUNC(void, ETH_CODE_FAST) ETH_GWCA0TSDISISR(void)                                                          /* PRQA S 1503 # JV-01 */
#endif
{
  Eth_Gwca_TSDIS_Common_Isr(ETH_RSW2_GWCA0);
}
#endif

/***********************************************************************************************************************
** Function Name         : ETH_GWCA0ERRISR
**
** Service ID            : NA
**
** Description           : Error Interrupt Service Handler (GWCA0)
**
** Sync/Async            : NA
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variable(s)    : None
**
** Function(s) invoked   : Eth_Gwca_ERR_Common_Isr
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_527
***********************************************************************************************************************/
#if (ETH_GWCA0_ERR_ISR == STD_ON)
#if defined (Os_ETH_GWCA0ERRISR_CAT2) || (ETH_ISR_CATEGORY_2 == STD_ON)
ISR(ETH_GWCA0ERRISR_CAT2)                                                                                               /* PRQA S 1503, 3408 # JV-01, JV-01 */
#else
_INTERRUPT_ FUNC(void, ETH_CODE_FAST) ETH_GWCA0ERRISR(void)                                                             /* PRQA S 1503 # JV-01 */
#endif
{
  Eth_Gwca_ERR_Common_Isr(ETH_RACE_ID_GWCA0);
}
#endif /* (ETH_GWCA0_ERR_ISR == STD_ON) */

/***********************************************************************************************************************
** Function Name         : ETH_COMAERRISR
**
** Service ID            : NA
**
** Description           : Error Interrupt Service Handler (COMA)
**
** Sync/Async            : NA
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variable(s)    : None
**
** Function(s) invoked   : Eth_Coma_ERR_Common_Isr
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_529
***********************************************************************************************************************/
#if (ETH_COMA_ERR_ISR == STD_ON)
#if defined (Os_ETH_COMAERRISR_CAT2) || (ETH_ISR_CATEGORY_2 == STD_ON)
ISR(ETH_COMAERRISR_CAT2)                                                                                                /* PRQA S 3408, 1503 # JV-01, JV-01 */
#else
_INTERRUPT_ FUNC(void, ETH_CODE_FAST) ETH_COMAERRISR(void)                                                              /* PRQA S 1503 # JV-01 */
#endif
{
  Eth_Coma_ERR_Common_Isr();
}
#endif /* (ETH_COMA_ERR_ISR == STD_ON) */

/***********************************************************************************************************************
** Function Name         : ETH_ETHA0ERRISR
**
** Service ID            : NA
**
** Description           : Error Interrupt Service Handler (ETHA0)
**
** Sync/Async            : NA
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variable(s)    : None
**
** Function(s) invoked   : Eth_Etha_ERR_Common_Isr
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_530
***********************************************************************************************************************/
#if (ETH_ETHA0_ERR_ISR == STD_ON)
#if defined (Os_ETH_ETHA0ERRISR_CAT2) || (ETH_ISR_CATEGORY_2 == STD_ON)
ISR(ETH_ETHA0ERRISR_CAT2)                                                                                               /* PRQA S 3408, 1503 # JV-01, JV-01 */
#else
_INTERRUPT_ FUNC(void, ETH_CODE_FAST) ETH_ETHA0ERRISR(void)                                                             /* PRQA S 1503 # JV-01 */
#endif
{
  Eth_Etha_ERR_Common_Isr(ETH_RACE_ID_ETHA0);
}
#endif /* (ETH_ETHA0_ERR_ISR == STD_ON) */

/***********************************************************************************************************************
** Function Name         : ETH_ETHA1ERRISR
**
** Service ID            : NA
**
** Description           : Error Interrupt Service Handler (ETHA1)
**
** Sync/Async            : NA
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variable(s)    : None
**
** Function(s) invoked   : Eth_Etha_ERR_Common_Isr
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_531
***********************************************************************************************************************/
#if (ETH_ETHA1_ERR_ISR == STD_ON)
#if defined (Os_ETH_ETHA1ERRISR_CAT2) || (ETH_ISR_CATEGORY_2 == STD_ON)
ISR(ETH_ETHA1ERRISR_CAT2)                                                                                               /* PRQA S 1503, 3408 # JV-01, JV-01 */
#else
_INTERRUPT_ FUNC(void, ETH_CODE_FAST) ETH_ETHA1ERRISR(void)                                                             /* PRQA S 1503 # JV-01 */
#endif
{
  Eth_Etha_ERR_Common_Isr(ETH_RACE_ID_ETHA1);
}
#endif /* (ETH_ETHA1_ERR_ISR == STD_ON) */

#if (ETH_SGMII_ISR == STD_ON)
#if defined (ETH_PORT0)
/***********************************************************************************************************************
** Function Name         : ETH_ETHA0SGMIIISR
**
** Service ID            : NA
**
** Description           : Interrupt Service Handler for SGMII (ETHA01)
**
** Sync/Async            : NA
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variable(s)    : None
**
** Function(s) invoked   : Eth_Etha_SGMII_Common_Isr
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_532
***********************************************************************************************************************/
#if defined (Os_ETH_ETHA0SGMIIISR_CAT2) || (ETH_ISR_CATEGORY_2 == STD_ON)
ISR(ETH_ETHA0SGMIIISR_CAT2)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
#else
_INTERRUPT_ FUNC(void, ETH_CODE_FAST) ETH_ETHA0SGMIIISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  Eth_Etha_SGMII_Common_Isr(ETH_PORT0);
}
#endif /* #if defined (ETH_PORT0) */

#if defined (ETH_PORT1)
/***********************************************************************************************************************
** Function Name         : ETH_ETHA1SGMIIISR
**
** Service ID            : NA
**
** Description           : Interrupt Service Handler for SGMII (ETHA01)
**
** Sync/Async            : NA
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variable(s)    : None
**
** Function(s) invoked   : Eth_Etha_SGMII_Common_Isr
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_533
***********************************************************************************************************************/
#if defined (Os_ETH_ETHA1SGMIIISR_CAT2) || (ETH_ISR_CATEGORY_2 == STD_ON)
ISR(ETH_ETHA1SGMIIISR_CAT2)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
#else
_INTERRUPT_ FUNC(void, ETH_CODE_FAST) ETH_ETHA1SGMIIISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif
{
  Eth_Etha_SGMII_Common_Isr(ETH_PORT1);
}
#endif /* #if defined (ETH_PORT1) */
#endif /* (ETH_SGMII_ISR == STD_ON) */

#define ETH_STOP_SEC_CODE_FAST
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
**                                                End of File                                                         **
***********************************************************************************************************************/
