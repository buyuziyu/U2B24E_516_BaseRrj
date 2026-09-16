/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Spi_SDMAC_Irq.h                                                                                     */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* Copyright(c) 2020-2025 Renesas Electronics Corporation.                                                            */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Provision for prototypes of Interrupt Service Routines.                                                            */
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
 * 2.5.1:  30/06/2025  : Remove SW-VERSION in file header
 * 2.5.0:  30/06/2025  : Update SW-VERSION for RH850/Ver21.01.00(D) U2Ax release
 * 2.4.0:  31/05/2025  : Update SW-VERSION for RH850/Ver21.01.01 U2Cx release
 * 2.3.2:  30/04/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 Release
 * 2.3.1:  31/03/2025  : Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02 Release
 * 2.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00(D) U2Bx Final Release
 * 2.1.3:  31/10/2024  : Update SW-VERSION up to 2.1.3
 * 2.1.2:  30/09/2024  : Update SW-VERSION up to 2.1.2
 * 2.1.1:  28/08/2024  : Support AR2211: update macro file definition.
 *                     : Remove QAC messages (2:0841) to fix redundant QAC messages
 *                     : Increase SW-VERSION up to 2.0.3
 *                     : Remove QAC message 1534
 * 2.1.0:  27/02/2024  : Update SW-VERSION to 2.1.0
 * 2.0.2:  14/12/2023  : Update SW-VERSION to 2.0.2
 * 2.0.1:  22/10/2023  : Update QAC message 1534 support Amendment 2
 *                       Update SW-VERSION to 2.0.1
 * 2.0.0:  28/08/2023  : Remove SPI_INSTANCE_INDEX
 *         25/07/2023  : Update from "Spi_Mapping.h to "Spi_MemMap.h".
 * 1.4.2:  02/03/2022  : Merge QAC
 * 1.3.2:  06/09/2021  : Update QAC contents
 *         04/09/2021  : Add pre-compile condition for defining multiple files base on instance index
 *                       Replace the inclusion of Spi_MemMap.h with Spi_Mapping.h
 * 1.3.1:  02/07/2021  : Add QAC message 9.5.0
 *                       Format source code to 120 characters
 *                       Improve Violation tag (remove START/END) 
 * 1.2.0:  30/07/2020  : Release
 *         28/07/2020  : Add QAC 9.3.1 comment.
 * 1.1.0:  19/06/2020  : Release
 * 1.0.0:  24/03/2020  : Initial Version
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/

/**********************************************************************************************************************/


/**********************************************************************************************************************/

#ifndef SPI_SDMAC_IRQ_H
#define SPI_SDMAC_IRQ_H

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for interrupt category definitions */
#include "Os.h"

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR Release version information */
#define SPI_SDMAC_IRQ_AR_RELEASE_MAJOR_VERSION    SPI_AR_RELEASE_MAJOR_VERSION
#define SPI_SDMAC_IRQ_AR_RELEASE_MINOR_VERSION    SPI_AR_RELEASE_MINOR_VERSION
#define SPI_SDMAC_IRQ_AR_RELEASE_REVISION_VERSION SPI_AR_RELEASE_REVISION_VERSION

/* File version information */
#define SPI_SDMAC_IRQ_SW_MAJOR_VERSION            SPI_SW_MAJOR_VERSION
#define SPI_SDMAC_IRQ_SW_MINOR_VERSION            SPI_SW_MINOR_VERSION

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/

/* Physical unit number */
#define SPI_PHYIDX_DMA0_00                        0U
#define SPI_PHYIDX_DMA0_01                        1U
#define SPI_PHYIDX_DMA0_02                        2U
#define SPI_PHYIDX_DMA0_03                        3U
#define SPI_PHYIDX_DMA0_04                        4U
#define SPI_PHYIDX_DMA0_05                        5U
#define SPI_PHYIDX_DMA0_06                        6U
#define SPI_PHYIDX_DMA0_07                        7U
#define SPI_PHYIDX_DMA0_08                        8U
#define SPI_PHYIDX_DMA0_09                        9U
#define SPI_PHYIDX_DMA0_10                        10U
#define SPI_PHYIDX_DMA0_11                        11U
#define SPI_PHYIDX_DMA0_12                        12U
#define SPI_PHYIDX_DMA0_13                        13U
#define SPI_PHYIDX_DMA0_14                        14U
#define SPI_PHYIDX_DMA0_15                        15U
#define SPI_PHYIDX_DMA1_00                        16U
#define SPI_PHYIDX_DMA1_01                        17U
#define SPI_PHYIDX_DMA1_02                        18U
#define SPI_PHYIDX_DMA1_03                        19U
#define SPI_PHYIDX_DMA1_04                        20U
#define SPI_PHYIDX_DMA1_05                        21U
#define SPI_PHYIDX_DMA1_06                        22U
#define SPI_PHYIDX_DMA1_07                        23U
#define SPI_PHYIDX_DMA1_08                        24U
#define SPI_PHYIDX_DMA1_09                        25U
#define SPI_PHYIDX_DMA1_10                        26U
#define SPI_PHYIDX_DMA1_11                        27U
#define SPI_PHYIDX_DMA1_12                        28U
#define SPI_PHYIDX_DMA1_13                        29U
#define SPI_PHYIDX_DMA1_14                        30U
#define SPI_PHYIDX_DMA1_15                        31U

/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/
#define SPI_START_SEC_CODE_FAST
#include "Spi_MemMap.h"

#if (SPI_DMA0_00_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_SPI_DMA0_00_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_DMA0_00_ISR(void);
#endif
#endif /* End of (SPI_DMA0_00_ISR_API == STD_ON) */

#if (SPI_DMA0_01_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_SPI_DMA0_01_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_DMA0_01_ISR(void);
#endif
#endif /* End of (SPI_DMA0_01_ISR_API == STD_ON) */

#if (SPI_DMA0_02_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_SPI_DMA0_02_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_DMA0_02_ISR(void);
#endif
#endif /* End of (SPI_DMA0_02_ISR_API == STD_ON) */

#if (SPI_DMA0_03_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_SPI_DMA0_03_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_DMA0_03_ISR(void);
#endif
#endif /* End of (SPI_DMA0_03_ISR_API == STD_ON) */

#if (SPI_DMA0_04_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_SPI_DMA0_04_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_DMA0_04_ISR(void);
#endif
#endif /* End of (SPI_DMA0_04_ISR_API == STD_ON) */

#if (SPI_DMA0_05_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_SPI_DMA0_05_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_DMA0_05_ISR(void);
#endif
#endif /* End of (SPI_DMA0_05_ISR_API == STD_ON) */

#if (SPI_DMA0_06_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_SPI_DMA0_06_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_DMA0_06_ISR(void);
#endif
#endif /* End of (SPI_DMA0_06_ISR_API == STD_ON) */

#if (SPI_DMA0_07_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_SPI_DMA0_07_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_DMA0_07_ISR(void);
#endif
#endif /* End of (SPI_DMA0_07_ISR_API == STD_ON) */

#if (SPI_DMA0_08_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_SPI_DMA0_08_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_DMA0_08_ISR(void);
#endif
#endif /* End of (SPI_DMA0_08_ISR_API == STD_ON) */

#if (SPI_DMA0_09_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_SPI_DMA0_09_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_DMA0_09_ISR(void);
#endif
#endif /* End of (SPI_DMA0_09_ISR_API == STD_ON) */

#if (SPI_DMA0_10_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_SPI_DMA0_10_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_DMA0_10_ISR(void);
#endif
#endif /* End of (SPI_DMA0_10_ISR_API == STD_ON) */

#if (SPI_DMA0_11_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_SPI_DMA0_11_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_DMA0_11_ISR(void);
#endif
#endif /* End of (SPI_DMA0_11_ISR_API == STD_ON) */

#if (SPI_DMA0_12_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_SPI_DMA0_12_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_DMA0_12_ISR(void);
#endif
#endif /* End of (SPI_DMA0_12_ISR_API == STD_ON) */

#if (SPI_DMA0_13_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_SPI_DMA0_13_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_DMA0_13_ISR(void);
#endif
#endif /* End of (SPI_DMA0_13_ISR_API == STD_ON) */

#if (SPI_DMA0_14_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_SPI_DMA0_14_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_DMA0_14_ISR(void);
#endif
#endif /* End of (SPI_DMA0_14_ISR_API == STD_ON) */

#if (SPI_DMA0_15_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_SPI_DMA0_15_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_DMA0_15_ISR(void);
#endif
#endif /* End of (SPI_DMA0_15_ISR_API == STD_ON) */

#if (SPI_DMA1_00_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_SPI_DMA1_00_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_DMA1_00_ISR(void);
#endif
#endif /* End of (SPI_DMA1_00_ISR_API == STD_ON) */

#if (SPI_DMA1_01_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_SPI_DMA1_01_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_DMA1_01_ISR(void);
#endif
#endif /* End of (SPI_DMA1_01_ISR_API == STD_ON) */

#if (SPI_DMA1_02_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_SPI_DMA1_02_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_DMA1_02_ISR(void);
#endif
#endif /* End of (SPI_DMA1_02_ISR_API == STD_ON) */

#if (SPI_DMA1_03_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_SPI_DMA1_03_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_DMA1_03_ISR(void);
#endif
#endif /* End of (SPI_DMA1_03_ISR_API == STD_ON) */

#if (SPI_DMA1_04_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_SPI_DMA1_04_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_DMA1_04_ISR(void);
#endif
#endif /* End of (SPI_DMA1_04_ISR_API == STD_ON) */

#if (SPI_DMA1_05_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_SPI_DMA1_05_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_DMA1_05_ISR(void);
#endif
#endif /* End of (SPI_DMA1_05_ISR_API == STD_ON) */

#if (SPI_DMA1_06_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_SPI_DMA1_06_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_DMA1_06_ISR(void);
#endif
#endif /* End of (SPI_DMA1_06_ISR_API == STD_ON) */

#if (SPI_DMA1_07_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_SPI_DMA1_07_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_DMA1_07_ISR(void);
#endif
#endif /* End of (SPI_DMA1_07_ISR_API == STD_ON) */

#if (SPI_DMA1_08_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_SPI_DMA1_08_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_DMA1_08_ISR(void);
#endif
#endif /* End of (SPI_DMA1_08_ISR_API == STD_ON) */

#if (SPI_DMA1_09_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_SPI_DMA1_09_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_DMA1_09_ISR(void);
#endif
#endif /* End of (SPI_DMA1_09_ISR_API == STD_ON) */

#if (SPI_DMA1_10_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_SPI_DMA1_10_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_DMA1_10_ISR(void);
#endif
#endif /* End of (SPI_DMA1_10_ISR_API == STD_ON) */

#if (SPI_DMA1_11_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_SPI_DMA1_11_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_DMA1_11_ISR(void);
#endif
#endif /* End of (SPI_DMA1_11_ISR_API == STD_ON) */

#if (SPI_DMA1_12_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_SPI_DMA1_12_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_DMA1_12_ISR(void);
#endif
#endif /* End of (SPI_DMA1_12_ISR_API == STD_ON) */

#if (SPI_DMA1_13_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_SPI_DMA1_13_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_DMA1_13_ISR(void);
#endif
#endif /* End of (SPI_DMA1_13_ISR_API == STD_ON) */

#if (SPI_DMA1_14_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_SPI_DMA1_14_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_DMA1_14_ISR(void);
#endif
#endif /* End of (SPI_DMA1_14_ISR_API == STD_ON) */

#if (SPI_DMA1_15_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_SPI_DMA1_15_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_DMA1_15_ISR(void);
#endif
#endif /* End of (SPI_DMA1_15_ISR_API == STD_ON) */

#define SPI_STOP_SEC_CODE_FAST
#include "Spi_MemMap.h"

#endif /* SPI_SDMAC_IRQ_H */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
