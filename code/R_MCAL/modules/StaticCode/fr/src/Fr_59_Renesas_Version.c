/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Fr_59_Renesas_Version.c                                                                             */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2019-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains code for version checking for modules included by Fr Driver.                                    */
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
 * 2.4.1:  30/06/2025    : Remove SW-VERSION in file header
 * 2.4.0:  30/06/2025    : Update SW-VERSION for RH850/U2Ax MCAL Ver22.01.00(D) Final Release
 * 2.3.2:  29/04/2025    : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 Release
 * 2.3.1:  31/03/2025    : Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02 Release
 * 2.3.0:  28/02/2025    : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.1:  31/12/2024    : Update SW-VERSION for Ver22.00.01 U2Ax Release
 * 2.2.0:  31/12/2024    : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 * 2.1.3:  31/10/2024    : Update SW-VERSION to 2.1.3
 * 2.1.2:  20/08/2024    : As part of R22-11 support, following changes are made:
 *                         Remove preprocessor FR_59_RENESAS_AR_431_VERSION
 * 2.1.1:  01/06/2024    : Update SW-VERSION for Ver22.00.01 Alpha Release
 *                       : As part of ARDAACL-45721, following changes are made:
 *                         Update Version check external module for module Fr_GeneralTypes, FrIf, Os
 *                       : As part of QAC 10.3.0 support, following changes are made:
 *                         Remove redundant QAC message: 0857, 0791
 * 2.1.0:  24/02/2024    : Change SW-VERSION to 2.1.0
 * 2.0.1:  27/09/2023    : Change FR_59_RENESAS_AR_R21_11_VERSION with
 *                         FR_59_RENESAS_AR_R22_11_VERSION to support AR22-11
 * 2.0.0:  26/05/2023    : Change FR_59_RENESAS_AR_2111_VERSION to FR_59_RENESAS_AR_R21_11_VERSION
 *         17/04/2023    : Updated for support AR2111
 * 1.4.3:  09/05/2022    : Change SW-VERSION to 1.4.3
 *                         Add message 9.5.0 0857
 * 1.3.3:  02/03/2022    : Change SW-VERSION to 1.4.2
 * 1.3.2:  13/08/2021    : Change SW-VERSION to 1.3.2
 * 1.3.1:  02/07/2021    : Format source code to 120 characters.
 *                         Improve Violation tag (remove START/END).
 * 1.2.0:  26/08/2020    : Release.
 * 1.1.0:  19/06/2020    : Release.
 *         28/07/2020    : Add QAC 9.3.1 comment.
 * 1.0.2:  17/04/2020    : Add the external header file including.
 * 1.0.1:  25/03/2020    : Change condition to check Det.h version.
 * 1.0.0:  11/12/2019    : Initial Version.
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for Fr module version information and other modules version information */
#include "Fr_59_Renesas.h"
/* Include version macro definition */
#include "Fr_59_Renesas_Version.h"

/* Following is required only when external modules version check is enabled */
#if (FR_59_RENESAS_VERSION_CHECK_EXT_MODULES == STD_ON)

/* DEM module version information is required */
#include "Dem.h"

#if ((FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) || (FR_59_RENESAS_AR_VERSION == FR_59_RENESAS_AR_R22_11_VERSION))
/* DET module version information is required only when DET is enabled */
#include "Det.h"
#endif

#if (FR_59_RENESAS_CRITICAL_SECTION_PROTECTION == STD_ON)
/*
 * RTE module version information is required only when critical section
 * protection is enabled
 */
#include "Rte.h"
#endif

/* Fr_GeneralTypes module version information is required */
#include "Fr_GeneralTypes.h"

/* FrIf module version information is required */
#include "FrIf.h"

#endif /* #if (FR_59_RENESAS_VERSION_CHECK_EXT_MODULES == STD_ON) */

#if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
/* OS module version information is required only when multi core support */
#include "Os.h"
#endif /* End of FR_59_RENESAS_MULTI_CORE_SUPPORT */

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/

/* AUTOSAR Release version information */
#define FR_59_RENESAS_VERSION_C_AR_RELEASE_MAJOR_VERSION    FR_59_RENESAS_AR_RELEASE_MAJOR_VERSION_VALUE
#define FR_59_RENESAS_VERSION_C_AR_RELEASE_MINOR_VERSION    FR_59_RENESAS_AR_RELEASE_MINOR_VERSION_VALUE
#define FR_59_RENESAS_VERSION_C_AR_RELEASE_REVISION_VERSION FR_59_RENESAS_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define FR_59_RENESAS_VERSION_C_SW_MAJOR_VERSION            FR_59_RENESAS_SW_MAJOR_VERSION_VALUE
#define FR_59_RENESAS_VERSION_C_SW_MINOR_VERSION            FR_59_RENESAS_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (FR_59_RENESAS_VERSION_AR_RELEASE_MAJOR_VERSION != FR_59_RENESAS_VERSION_C_AR_RELEASE_MAJOR_VERSION)
  #error "Fr_59_Renesas_Version.c : Mismatch in Release Major Version"
#endif

#if (FR_59_RENESAS_VERSION_AR_RELEASE_MINOR_VERSION != FR_59_RENESAS_VERSION_C_AR_RELEASE_MINOR_VERSION)
  #error "Fr_59_Renesas_Version.c : Mismatch in Release Minor Version"
#endif

#if (FR_59_RENESAS_VERSION_AR_RELEASE_REVISION_VERSION != FR_59_RENESAS_VERSION_C_AR_RELEASE_REVISION_VERSION)
  #error "Fr_59_Renesas_Version.c : Mismatch in Release Revision Version"
#endif

#if (FR_59_RENESAS_VERSION_SW_MAJOR_VERSION != FR_59_RENESAS_VERSION_C_SW_MAJOR_VERSION)
  #error "Fr_59_Renesas_Version.c : Mismatch in Software Major Version"
#endif

#if (FR_59_RENESAS_VERSION_SW_MINOR_VERSION != FR_59_RENESAS_VERSION_C_SW_MINOR_VERSION)
  #error "Fr_59_Renesas_Version.c : Mismatch in Software Minor Version"
#endif

#if (FR_59_RENESAS_VERSION_CHECK_EXT_MODULES == STD_ON)

#if ((DEM_AR_RELEASE_MAJOR_VERSION != FR_59_RENESAS_AR_RELEASE_MAJOR_VERSION) || \
     (DEM_AR_RELEASE_MINOR_VERSION != FR_59_RENESAS_AR_RELEASE_MINOR_VERSION) || \
     (DEM_AR_RELEASE_REVISION_VERSION != FR_59_RENESAS_AR_RELEASE_REVISION_VERSION))
  #error "The AR version of Dem.h does not match the expected version"
#endif /* End of DEM */

#if (((FR_59_RENESAS_AR_VERSION == FR_59_RENESAS_AR_422_VERSION) && (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)) || \
                                                     (FR_59_RENESAS_AR_VERSION == FR_59_RENESAS_AR_R22_11_VERSION))
#if ((DET_AR_RELEASE_MAJOR_VERSION != FR_59_RENESAS_AR_RELEASE_MAJOR_VERSION) || \
     (DET_AR_RELEASE_MINOR_VERSION != FR_59_RENESAS_AR_RELEASE_MINOR_VERSION) || \
     (DET_AR_RELEASE_REVISION_VERSION != FR_59_RENESAS_AR_RELEASE_REVISION_VERSION))
  #error "The AR version of Det.h does not match the expected version"
#endif /* End of DET */
#endif /* End of FR_59_RENESAS_DEV_ERROR_DETECT and AR version condition */

#if (FR_59_RENESAS_CRITICAL_SECTION_PROTECTION == STD_ON)
#if ((RTE_AR_RELEASE_MAJOR_VERSION != FR_59_RENESAS_AR_RELEASE_MAJOR_VERSION) || \
     (RTE_AR_RELEASE_MINOR_VERSION != FR_59_RENESAS_AR_RELEASE_MINOR_VERSION) || \
     (RTE_AR_RELEASE_REVISION_VERSION != FR_59_RENESAS_AR_RELEASE_REVISION_VERSION))
  #error "The AR version of Rte.h does not match the expected version"
#endif /* End of RTE */
#endif /* End of FR_59_RENESAS_CRITICAL_SECTION_PROTECTION */

#if ((FR_GENERAL_TYPES_AR_RELEASE_MAJOR_VERSION != FR_59_RENESAS_AR_RELEASE_MAJOR_VERSION) || \
     (FR_GENERAL_TYPES_AR_RELEASE_MINOR_VERSION != FR_59_RENESAS_AR_RELEASE_MINOR_VERSION) || \
     (FR_GENERAL_TYPES_AR_RELEASE_REVISION_VERSION != FR_59_RENESAS_AR_RELEASE_REVISION_VERSION))
  #error "The AR version of Fr_GeneralTypes.h does not match the expected version"
#endif /* End of Fr_GeneralTypes */

#if ((FRIF_AR_RELEASE_MAJOR_VERSION != FR_59_RENESAS_AR_RELEASE_MAJOR_VERSION) || \
     (FRIF_AR_RELEASE_MINOR_VERSION != FR_59_RENESAS_AR_RELEASE_MINOR_VERSION) || \
     (FRIF_AR_RELEASE_REVISION_VERSION != FR_59_RENESAS_AR_RELEASE_REVISION_VERSION))
  #error "The AR version of FrIf.h does not match the expected version"
#endif /* End of FrIf */

#endif /* End of FR_59_RENESAS_VERSION_CHECK_EXT_MODULES */

#if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
#if ((OS_AR_RELEASE_MAJOR_VERSION != FR_59_RENESAS_AR_RELEASE_MAJOR_VERSION) || \
     (OS_AR_RELEASE_MINOR_VERSION != FR_59_RENESAS_AR_RELEASE_MINOR_VERSION) || \
     (OS_AR_RELEASE_REVISION_VERSION != FR_59_RENESAS_AR_RELEASE_REVISION_VERSION))
  #error "The AR version of Os.h does not match the expected version"
#endif /* End of Os */
#endif /* End of FR_59_RENESAS_MULTI_CORE_SUPPORT */

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:0857)    : Number of macro definitions exceeds 1024 - program does not conform strictly to ISO:C90.     */
/* Rule                : MISRA C:2012 Dir-1.1                                                                         */
/* JV-01 Justification : The number of macro depend on module code size. There is no issue when number of macro is    */
/*                       over 1024.                                                                                   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (7:0791)    : Macro identifier does not differ from other macro identifier(s) (e.g. '%s') within the       */
/*                       specified number of significant characters.                                                  */
/* Rule                : CERTCCM DCL23, MISRA C:2012 Rule-5.4                                                         */
/* JV-01 Justification : This macro identifier is following AUTOSAR standard rule (Symbolic Name or Published         */
/*                       Macro's name), so this is accepted.                                                          */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/

/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
