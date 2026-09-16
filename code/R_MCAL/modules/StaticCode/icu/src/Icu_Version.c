/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Icu_Version.c                                                                                       */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.                                               */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains version check of modules included by ICU Driver                                                 */
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
 * 2.0.1:  19/10/2023  : Remove QAC message 0857
 * 2.0.0:  03/08/2023  : #include "Icu_Mapping.h" update to #include "Icu_MemMap.h" 
 *                       Remove all multi-instance including methods
 *                       Remove all supported multi-instance header file
 * 1.4.1:  18/10/2021  : Add QAC message 9.5.0
 * 1.3.2:  02/07/2021  : Format source code to 120 characters
 *         04/05/2021  : Added SW version check
 * 1.2.0:  17/07/2020  : Release
 * 1.1.0:  19/06/2020  : Release
 * 1.0.0:  25/03/2020  : Initial Version
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/*
 * Included for Icu module version information and other modules version
 * information
 */

/* Included for module version information and other types declarations */
#include "Icu_Version.h"

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define ICU_VERSION_C_AR_RELEASE_MAJOR_VERSION    ICU_AR_RELEASE_MAJOR_VERSION_VALUE
#define ICU_VERSION_C_AR_RELEASE_MINOR_VERSION    ICU_AR_RELEASE_MINOR_VERSION_VALUE
#define ICU_VERSION_C_AR_RELEASE_REVISION_VERSION ICU_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define ICU_VERSION_C_SW_MAJOR_VERSION            ICU_SW_MAJOR_VERSION_VALUE
#define ICU_VERSION_C_SW_MINOR_VERSION            ICU_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (ICU_VERSION_AR_RELEASE_MAJOR_VERSION != ICU_VERSION_C_AR_RELEASE_MAJOR_VERSION)
  #error "Icu_Version.c : Mismatch in Release Major Version"
#endif /* #if (ICU_VERSION_AR_RELEASE_MAJOR_VERSION != ICU_VERSION_C_AR_RELEASE_MAJOR_VERSION) */

#if (ICU_VERSION_AR_RELEASE_MINOR_VERSION != ICU_VERSION_C_AR_RELEASE_MINOR_VERSION)
  #error "Icu_Version.c : Mismatch in Release Minor Version"
#endif /* #if (ICU_VERSION_AR_RELEASE_MINOR_VERSION != ICU_VERSION_C_AR_RELEASE_MINOR_VERSION) */

#if (ICU_VERSION_AR_RELEASE_REVISION_VERSION != ICU_VERSION_C_AR_RELEASE_REVISION_VERSION)
  #error "Icu_Version.c : Mismatch in Release Revision Version"
#endif /* #if (ICU_VERSION_AR_RELEASE_REVISION_VERSION != ICU_VERSION_C_AR_RELEASE_REVISION_VERSION) */

#if (ICU_VERSION_SW_MAJOR_VERSION != ICU_VERSION_C_SW_MAJOR_VERSION)
  #error "Icu_Version.c : Mismatch in Software Major Version"
#endif /* #if (ICU_VERSION_SW_MAJOR_VERSION != ICU_VERSION_C_SW_MAJOR_VERSION) */

#if (ICU_VERSION_SW_MINOR_VERSION != ICU_VERSION_C_SW_MINOR_VERSION)
  #error "Icu_Version.c : Mismatch in Software Minor Version"
#endif /* #if (ICU_VERSION_SW_MINOR_VERSION != ICU_VERSION_C_SW_MINOR_VERSION) */

#if (ICU_VERSION_CHECK_EXT_MODULES == STD_ON)
#if (ICU_REPORT_WAKEUP_SOURCE == STD_ON)

/* EcuM Module Version Check */
#if ((ECUM_AR_RELEASE_MAJOR_VERSION != ICU_AR_RELEASE_MAJOR_VERSION) || \
                                                        (ECUM_AR_RELEASE_MINOR_VERSION != ICU_AR_RELEASE_MINOR_VERSION))
  #error "The AR version of EcuM.h does not match the expected version"
#endif /* #if ((ECUM_AR_RELEASE_MAJOR_VERSION != ICU_AR_RELEASE_MAJOR_VERSION) \
                                                  || (ECUM_AR_RELEASE_MINOR_VERSION != ICU_AR_RELEASE_MINOR_VERSION)) */
#endif /* #if (ICU_REPORT_WAKEUP_SOURCE == STD_ON) */

/* Det Module Version Check */
#if (ICU_DEV_ERROR_DETECT == STD_ON)
#if ((DET_AR_RELEASE_MAJOR_VERSION != ICU_AR_RELEASE_MAJOR_VERSION) || \
                                                         (DET_AR_RELEASE_MINOR_VERSION != ICU_AR_RELEASE_MINOR_VERSION))
  #error "The AR version of Det.h does not match the expected version"
#endif /* #if ((DET_AR_RELEASE_MAJOR_VERSION != ICU_AR_RELEASE_MAJOR_VERSION)    \
                                                   || (DET_AR_RELEASE_MINOR_VERSION != ICU_AR_RELEASE_MINOR_VERSION)) */
#endif /* #if (ICU_DEV_ERROR_DETECT == STD_ON) */

/* Os Module Version Check */
#if ((OS_AR_RELEASE_MAJOR_VERSION != ICU_AR_RELEASE_MAJOR_VERSION) || \
                                                          (OS_AR_RELEASE_MINOR_VERSION != ICU_AR_RELEASE_MINOR_VERSION))
  #error "The AR version of Os.h does not match the expected version"
#endif /* #if ((OS_AR_RELEASE_MAJOR_VERSION != ICU_AR_RELEASE_MAJOR_VERSION)     \
                                                    || (OS_AR_RELEASE_MINOR_VERSION != ICU_AR_RELEASE_MINOR_VERSION)) */

/* Rte Module Version Check */
#if (ICU_CRITICAL_SECTION_PROTECTION == STD_ON)
#if ((RTE_AR_RELEASE_MAJOR_VERSION != ICU_AR_RELEASE_MAJOR_VERSION) || \
                                                         (RTE_AR_RELEASE_MINOR_VERSION != ICU_AR_RELEASE_MINOR_VERSION))
  #error "The AR version of Rte.h does not match the expected version"
#endif /* #if ((RTE_AR_RELEASE_MAJOR_VERSION != ICU_AR_RELEASE_MAJOR_VERSION)    \
                                                   || (RTE_AR_RELEASE_MINOR_VERSION != ICU_AR_RELEASE_MINOR_VERSION)) */
#endif /* #if (ICU_CRITICAL_SECTION_PROTECTION == STD_ON) */

/* Dem Module Version Check */
#if ((DEM_AR_RELEASE_MAJOR_VERSION != ICU_AR_RELEASE_MAJOR_VERSION) || \
                                                         (DEM_AR_RELEASE_MINOR_VERSION != ICU_AR_RELEASE_MINOR_VERSION))
  #error "The AR version of Dem.h does not match the expected version"
#endif

#endif /* (ICU_VERSION_CHECK_EXT_MODULES == STD_ON) */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
