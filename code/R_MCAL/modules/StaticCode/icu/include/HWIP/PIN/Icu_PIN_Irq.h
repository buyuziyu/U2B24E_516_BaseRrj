/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Icu_PIN_Irq.h                                                                                       */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains ISRs prototypes for all Timers of ICU Driver                                                    */
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
 * 2.3.1:  31/03/2025  : Update SW-VERSION for RH850/U2BxE MCAL Ver22.00.02 Release
 * 2.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release 
 * 2.1.2:  31/10/2024  : Update SW-VERSION for Ver22.01.02 Beta2 Release 
 *                       As part of support U2Bx-E, following changes are made:
 *                       1.Add INTP44 and INTP45
 * 2.0.1:  25/10/2023  : Update SW-VERSION to 2.0.1
 * 2.0.0:  03/08/2023  : #include "Icu_Mapping.h" update to #include "Icu_MemMap.h" 
 *                       Remove all multi-instance including methods
 *                       Remove all supported multi-instance header file
 * 1.4.1:  15/09/2021  : Saperate IRQ and INTP section
 * 1.3.2:  30/08/2021  : Change from #include "Icu_MemMap.h" to #include "Icu_Mapping.h".
 *                       Update header file macro.
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

/**********************************************************************************************************************/
#ifndef ICU_PIN_IRQ_H
#define ICU_PIN_IRQ_H
/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for interrupt category definitions */
#include "Os.h"

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define ICU_PIN_IRQ_AR_RELEASE_MAJOR_VERSION    ICU_AR_RELEASE_MAJOR_VERSION
#define ICU_PIN_IRQ_AR_RELEASE_MINOR_VERSION    ICU_AR_RELEASE_MINOR_VERSION
#define ICU_PIN_IRQ_AR_RELEASE_REVISION_VERSION ICU_AR_RELEASE_REVISION_VERSION

/* File version information */
#define ICU_PIN_IRQ_SW_MAJOR_VERSION            ICU_SW_MAJOR_VERSION
#define ICU_PIN_IRQ_SW_MINOR_VERSION            ICU_SW_MINOR_VERSION

/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/

#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"

/* For IRQ */
#if (STD_ON == ICU_IRQ_EDGE_DETECT)

/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_IRQ_CH00_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_IRQ_CH00_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_IRQ_CH01_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_IRQ_CH01_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_IRQ_CH02_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_IRQ_CH02_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_IRQ_CH03_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_IRQ_CH03_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_IRQ_CH04_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_IRQ_CH04_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_IRQ_CH05_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_IRQ_CH05_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_IRQ_CH06_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_IRQ_CH06_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_IRQ_CH07_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_IRQ_CH07_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_IRQ_CH08_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_IRQ_CH08_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_IRQ_CH09_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_IRQ_CH09_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_IRQ_CH10_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_IRQ_CH10_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_IRQ_CH11_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_IRQ_CH11_ISR(void);
#endif
#endif /* End of STD_ON == ICU_IRQ_EDGE_DETECT */

/* For INTP */
#if (STD_ON == ICU_INTP_EDGE_DETECT)

#if (ICU_EXT_INTP_CH00_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH00_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH00_ISR(void);                                                   
#endif
#endif /* End of ICU_EXT_INTP_CH00_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH01_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH01_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH01_ISR(void);                                                   
#endif
#endif /* End of ICU_EXT_INTP_CH01_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH02_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH02_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH02_ISR(void);                                                   
#endif
#endif /* End of ICU_EXT_INTP_CH02_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH03_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH03_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH03_ISR(void);                                                   
#endif
#endif /* End of ICU_EXT_INTP_CH03_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH04_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH04_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH04_ISR(void);                                                   
#endif
#endif /* End of ICU_EXT_INTP_CH04_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH05_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH05_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH05_ISR(void);                                                   
#endif
#endif /* End of ICU_EXT_INTP_CH05_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH06_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH06_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH06_ISR(void);                                                   
#endif
#endif /* End of ICU_EXT_INTP_CH06_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH07_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH07_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH07_ISR(void);                                                   
#endif
#endif /* End of ICU_EXT_INTP_CH07_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH08_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH08_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH08_ISR(void);                                                   
#endif
#endif /* End of ICU_EXT_INTP_CH08_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH09_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH09_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH09_ISR(void);                                                   
#endif
#endif /* End of ICU_EXT_INTP_CH09_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH10_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH10_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH10_ISR(void);                                                   
#endif
#endif /* End of ICU_EXT_INTP_CH10_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH11_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH11_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH11_ISR(void);                                                   
#endif
#endif /* End of ICU_EXT_INTP_CH11_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH12_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH12_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH12_ISR(void);                                                   
#endif
#endif /* End of ICU_EXT_INTP_CH12_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH13_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH13_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH13_ISR(void);                                                   
#endif
#endif /* End of ICU_EXT_INTP_CH13_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH14_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH14_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH14_ISR(void);                                                   
#endif
#endif /* End of ICU_EXT_INTP_CH14_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH15_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH15_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH15_ISR(void);                                                   
#endif
#endif /* End of ICU_EXT_INTP_CH15_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH16_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH16_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH16_ISR(void);                                                   
#endif
#endif /* End of ICU_EXT_INTP_CH16_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH17_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH17_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH17_ISR(void);                                                   
#endif
#endif /* End of ICU_EXT_INTP_CH17_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH18_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH18_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH18_ISR(void);                                                   
#endif
#endif /* End of ICU_EXT_INTP_CH18_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH19_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH19_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH19_ISR(void);                                                   
#endif
#endif /* End of ICU_EXT_INTP_CH19_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH20_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH20_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH20_ISR(void);                                                   
#endif
#endif /* End of ICU_EXT_INTP_CH20_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH21_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH21_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH21_ISR(void);                                                   
#endif
#endif /* End of ICU_EXT_INTP_CH21_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH22_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH22_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH22_ISR(void);                                                   
#endif
#endif /* End of ICU_EXT_INTP_CH22_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH23_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH23_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH23_ISR(void);                                                   
#endif
#endif /* End of ICU_EXT_INTP_CH23_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH24_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH24_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH24_ISR(void);                                                   
#endif
#endif /* End of ICU_EXT_INTP_CH24_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH25_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH25_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH25_ISR(void);                                                   
#endif
#endif /* End of ICU_EXT_INTP_CH25_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH26_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH26_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH26_ISR(void);                                                   
#endif
#endif /* End of ICU_EXT_INTP_CH26_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH27_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH27_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH27_ISR(void);                                                   
#endif
#endif /* End of ICU_EXT_INTP_CH27_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH28_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH28_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH28_ISR(void);                                                   
#endif
#endif /* End of ICU_EXT_INTP_CH28_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH29_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH29_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH29_ISR(void);                                                   
#endif
#endif /* End of ICU_EXT_INTP_CH29_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH30_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH30_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH30_ISR(void);                                                   
#endif
#endif /* End of ICU_EXT_INTP_CH30_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH31_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH31_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH31_ISR(void);                                                   
#endif
#endif /* End of ICU_EXT_INTP_CH31_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH32_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH32_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH32_ISR(void);                                                   
#endif
#endif /* End of ICU_EXT_INTP_CH32_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH33_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH33_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH33_ISR(void);                                                   
#endif
#endif /* End of ICU_EXT_INTP_CH33_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH34_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH34_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH34_ISR(void);                                                   
#endif
#endif /* End of ICU_EXT_INTP_CH34_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH35_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH35_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH35_ISR(void);                                                   
#endif
#endif /* End of ICU_EXT_INTP_CH35_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH36_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH36_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH36_ISR(void);                                                   
#endif
#endif /* End of ICU_EXT_INTP_CH36_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH37_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH37_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH37_ISR(void);                                                   
#endif
#endif /* End of ICU_EXT_INTP_CH37_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH38_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH38_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH38_ISR(void);                                                   
#endif
#endif /* End of ICU_EXT_INTP_CH38_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH39_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH39_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH39_ISR(void);                                                   
#endif
#endif /* End of ICU_EXT_INTP_CH39_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH40_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH40_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH40_ISR(void);                                                   
#endif
#endif /* End of ICU_EXT_INTP_CH40_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH41_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH41_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH41_ISR(void);                                                   
#endif
#endif /* End of ICU_EXT_INTP_CH41_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH42_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH42_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH42_ISR(void);                                                   
#endif
#endif /* End of ICU_EXT_INTP_CH42_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH43_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH43_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH43_ISR(void);                                                   
#endif
#endif /* End of ICU_EXT_INTP_CH43_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH44_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH44_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH44_ISR(void);                                                   
#endif
#endif /* End of ICU_EXT_INTP_CH44_ISR_API == STD_ON */

#if (ICU_EXT_INTP_CH45_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_EXT_INTP_CH45_CAT2_ISR) || (ICU_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
extern _INTERRUPT_ FUNC(void, ICU_CODE_FAST) EXT_INTP_CH45_ISR(void);                                                   
#endif
#endif /* End of ICU_EXT_INTP_CH45_ISR_API == STD_ON */

#endif /* End of STD_ON == ICU_INTP_EDGE_DETECT */

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"
#endif /* ICU_PIN_IRQ_H */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
