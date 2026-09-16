/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Eth_ETNE_Irq.h                                                                                      */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2024, 2025 Renesas Electronics Corporation. All rights reserved.                                               */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Provision of prototypes for Interrupt service routine for ethernet driver.                                         */
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
 * 2.4.1: 30/06/2025    : Remove the SW-VERSION from header of file
 * 2.4.0: 30/06/2025    : Update SW-VERSION for RH850/Ver22.01.00 (D) U2Ax release
 * 2.3.1: 31/03/2025    : Change precompile Eth_Gwca_TSDIS_Common_Isr by ETH_GWCA0_TSDATA_ISR
 *                      : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 * 2.3.0: 28/02/2025    : - As per ticket ARDAACJ-680:
 *                        Add new function ETH_ETHA0SGMIIISR, ETH_ETHA1SGMIIISR to support interrupt for SGMII mode
 * 2.2.0: 31/12/2024    : Update SW-VERSION for Ver22.02.00(D) U2Bx Final Release
 * 2.1.2: 31/10/2024    : Increase SW-VERSION to 2.1.2
 * 2.1.1: 31/05/2024    : Initial Version
 */
/**********************************************************************************************************************/
#ifndef ETH_ETNE_IRQ_H
#define ETH_ETNE_IRQ_H
/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
#include "Eth_Types.h"
/* Included for version information macros */
#include "Os.h"

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define ETH_ETNE_IRQ_AR_RELEASE_MAJOR_VERSION    ETH_AR_RELEASE_MAJOR_VERSION
#define ETH_ETNE_IRQ_AR_RELEASE_MINOR_VERSION    ETH_AR_RELEASE_MINOR_VERSION
#define ETH_ETNE_IRQ_AR_RELEASE_REVISION_VERSION ETH_AR_RELEASE_REVISION_VERSION

/* Module Software version information */
#define ETH_ETNE_IRQ_SW_MAJOR_VERSION            ETH_SW_MAJOR_VERSION
#define ETH_ETNE_IRQ_SW_MINOR_VERSION            ETH_SW_MINOR_VERSION

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:1055)    : [C99] The keyword 'inline' has been used.                                                    */
/* Rule                : MISRA C:2012 Dir-1.1, Rule-1.2                                                               */
/* JV-01 Justification : In this case, inline functions are considered more optimized for ECODE than function-like    */
/*                       macros. Usage of inline functions is accepted.                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#define ETH_START_SEC_CODE_FAST
#include "Eth_MemMap.h"

#if (ETH_GWCA0_DATA_ISR == STD_ON)
#if defined (Os_ETH_GWCA0DISISR_CAT2) || (ETH_ISR_CATEGORY_2 == STD_ON)
#else
extern _INTERRUPT_ FUNC(void, ETH_CODE_FAST) ETH_GWCA0DISISR(void);
#endif
#endif

#if (ETH_GWCA0_TSDATA_ISR == STD_ON)
#if defined (Os_ETH_GWCA0TSDISISR_CAT2) || (ETH_ISR_CATEGORY_2 == STD_ON)
#else
extern _INTERRUPT_ FUNC(void, ETH_CODE_FAST) ETH_GWCA0TSDISISR(void);
#endif
#endif

#if (ETH_GWCA0_ERR_ISR == STD_ON)
#if defined (Os_ETH_GWCA0ERRISR_CAT2) || (ETH_ISR_CATEGORY_2 == STD_ON)
#else
extern _INTERRUPT_ FUNC(void, ETH_CODE_FAST) ETH_GWCA0ERRISR(void);
#endif
#endif

#if (ETH_COMA_ERR_ISR == STD_ON)
#if defined (Os_ETH_COMAERRISR_CAT2) || (ETH_ISR_CATEGORY_2 == STD_ON)
#else
extern _INTERRUPT_ FUNC(void, ETH_CODE_FAST) ETH_COMAERRISR(void);
#endif
#endif

#if (ETH_ETHA0_ERR_ISR == STD_ON)
#if defined (Os_ETH_ETHA0ERRISR_CAT2) || (ETH_ISR_CATEGORY_2 == STD_ON)
#else
extern _INTERRUPT_ FUNC(void, ETH_CODE_FAST) ETH_ETHA0ERRISR(void);
#endif
#endif

#if (ETH_ETHA1_ERR_ISR == STD_ON)
#if defined (Os_ETH_ETHA1ERRISR_CAT2) || (ETH_ISR_CATEGORY_2 == STD_ON)
#else
extern _INTERRUPT_ FUNC(void, ETH_CODE_FAST) ETH_ETHA1ERRISR(void);
#endif
#endif

#if (ETH_SGMII_ISR == STD_ON)
#if defined (ETH_PORT0)
#if defined (Os_ETH_ETHA0SGMIIISR_CAT2) || (ETH_ISR_CATEGORY_2 == STD_ON)
#else
extern _INTERRUPT_ FUNC(void, ETH_CODE_FAST) ETH_ETHA0SGMIIISR(void);
#endif
#endif /* #if defined (ETH_PORT0) */

#if defined (ETH_PORT1)
#if defined (Os_ETH_ETHA1SGMIIISR_CAT2) || (ETH_ISR_CATEGORY_2 == STD_ON)
#else
extern _INTERRUPT_ FUNC(void, ETH_CODE_FAST) ETH_ETHA1SGMIIISR(void);
#endif
#endif /* #if defined (ETH_PORT1) */
#endif /* (ETH_SGMII_ISR == STD_ON) */

#define ETH_STOP_SEC_CODE_FAST
#include "Eth_MemMap.h"


#endif  /* ETH_RSW2_IRQ_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
