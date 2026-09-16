/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Lin_RLIN3_Irq.h                                                                                     */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2019-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Provision of Interrupt routines.                                                                                   */
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
 * 2.1.2:  31/10/2024  : Update SW-VERSION to 2.1.2
 * 1.4.3:  14/04/2022  : Update SW-VERSION to 1.4.3
 * 1.3.2:  04/03/2022  : Update SW-VERSION
 * 1.3.1:  02/07/2021  : Add QAC message 9.5.0.
 *                       Format source code to 120 characters.
 *                       Improve Violation tag (remove START/END).
 * 1.2.0:  26/08/2020  : Release.
 * 1.1.0:  19/06/2020  : Release.
 * 1.0.1:  16/04/2020  : Modified #include heading files.
 * 1.0.0:  12/03/2019  : Initial Version.
 *
 */
/**********************************************************************************************************************/

#ifndef LIN_RLIN3_IRQ_H
#define LIN_RLIN3_IRQ_H

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/

/* Included for interrupt category definitions */
#include "Os.h"

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define LIN_RLIN3_IRQ_AR_RELEASE_MAJOR_VERSION    LIN_AR_RELEASE_MAJOR_VERSION
#define LIN_RLIN3_IRQ_AR_RELEASE_MINOR_VERSION    LIN_AR_RELEASE_MINOR_VERSION
#define LIN_RLIN3_IRQ_AR_RELEASE_REVISION_VERSION LIN_AR_RELEASE_REVISION_VERSION
/* File version information */
#define LIN_RLIN3_IRQ_SW_MAJOR_VERSION            LIN_SW_MAJOR_VERSION
#define LIN_RLIN3_IRQ_SW_MINOR_VERSION            LIN_SW_MINOR_VERSION

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/
#define LIN_START_SEC_CODE_FAST
#include "Lin_MemMap.h"

#if (LIN_CHANNEL0_CONFIGURED == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL0_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL0_TX_ISR(void);
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL0_RX_ISR(void);
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL0_ERR_ISR(void);
#endif
#endif

#if (LIN_CHANNEL1_CONFIGURED == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL1_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL1_TX_ISR(void);
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL1_RX_ISR(void);
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL1_ERR_ISR(void);
#endif
#endif

#if (LIN_CHANNEL2_CONFIGURED == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL2_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL2_TX_ISR(void);
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL2_RX_ISR(void);
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL2_ERR_ISR(void);
#endif
#endif

#if (LIN_CHANNEL3_CONFIGURED == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL3_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL3_TX_ISR(void);
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL3_RX_ISR(void);
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL3_ERR_ISR(void);
#endif
#endif

#if (LIN_CHANNEL4_CONFIGURED == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL4_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL4_TX_ISR(void);
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL4_RX_ISR(void);
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL4_ERR_ISR(void);
#endif
#endif

#if (LIN_CHANNEL5_CONFIGURED == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL5_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL5_TX_ISR(void);
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL5_RX_ISR(void);
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL5_ERR_ISR(void);
#endif
#endif

#if (LIN_CHANNEL6_CONFIGURED == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL6_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL6_TX_ISR(void);
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL6_RX_ISR(void);
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL6_ERR_ISR(void);
#endif
#endif

#if (LIN_CHANNEL7_CONFIGURED == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL7_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL7_TX_ISR(void);
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL7_RX_ISR(void);
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL7_ERR_ISR(void);
#endif
#endif

#if (LIN_CHANNEL8_CONFIGURED == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL8_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL8_TX_ISR(void);
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL8_RX_ISR(void);
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL8_ERR_ISR(void);
#endif
#endif

#if (LIN_CHANNEL9_CONFIGURED == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL9_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL9_TX_ISR(void);
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL9_RX_ISR(void);
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL9_ERR_ISR(void);
#endif
#endif

#if (LIN_CHANNEL10_CONFIGURED == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL10_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL10_TX_ISR(void);
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL10_RX_ISR(void);
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL10_ERR_ISR(void);
#endif
#endif

#if (LIN_CHANNEL11_CONFIGURED == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL11_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL11_TX_ISR(void);
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL11_RX_ISR(void);
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL11_ERR_ISR(void);
#endif
#endif

#if (LIN_CHANNEL12_CONFIGURED == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL12_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL12_TX_ISR(void);
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL12_RX_ISR(void);
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL12_ERR_ISR(void);
#endif
#endif

#if (LIN_CHANNEL13_CONFIGURED == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL13_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL13_TX_ISR(void);
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL13_RX_ISR(void);
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL13_ERR_ISR(void);
#endif
#endif

#if (LIN_CHANNEL14_CONFIGURED == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL14_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL14_TX_ISR(void);
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL14_RX_ISR(void);
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL14_ERR_ISR(void);
#endif
#endif

#if (LIN_CHANNEL15_CONFIGURED == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL15_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL15_TX_ISR(void);
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL15_RX_ISR(void);
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL15_ERR_ISR(void);
#endif
#endif

#if (LIN_CHANNEL16_CONFIGURED == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL16_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL16_TX_ISR(void);
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL16_RX_ISR(void);
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL16_ERR_ISR(void);
#endif
#endif

#if (LIN_CHANNEL17_CONFIGURED == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL17_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL17_TX_ISR(void);
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL17_RX_ISR(void);
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL17_ERR_ISR(void);
#endif
#endif

#if (LIN_CHANNEL18_CONFIGURED == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL18_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL18_TX_ISR(void);
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL18_RX_ISR(void);
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL18_ERR_ISR(void);
#endif
#endif

#if (LIN_CHANNEL19_CONFIGURED == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL19_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL19_TX_ISR(void);
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL19_RX_ISR(void);
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL19_ERR_ISR(void);
#endif
#endif

#if (LIN_CHANNEL20_CONFIGURED == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL20_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL20_TX_ISR(void);
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL20_RX_ISR(void);
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL20_ERR_ISR(void);
#endif
#endif

#if (LIN_CHANNEL21_CONFIGURED == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL21_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL21_TX_ISR(void);
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL21_RX_ISR(void);
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL21_ERR_ISR(void);
#endif
#endif

#if (LIN_CHANNEL22_CONFIGURED == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL22_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL22_TX_ISR(void);
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL22_RX_ISR(void);
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL22_ERR_ISR(void);
#endif
#endif

#if (LIN_CHANNEL23_CONFIGURED == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_LIN_CHANNEL23_CAT2_ISR) || (LIN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL23_TX_ISR(void);
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL23_RX_ISR(void);
extern _INTERRUPT_ FUNC(void, LIN_CODE_FAST) LIN_CHANNEL23_ERR_ISR(void);
#endif
#endif

#define LIN_STOP_SEC_CODE_FAST
#include "Lin_MemMap.h"

#endif /* LIN_RLIN3_IRQ_H */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
