/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = RamTst_Version.c                                                                                    */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2023-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains code for version checking for modules included by RAM                                           */
/* Test Driver.                                                                                                       */
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
 * 1.4.1:  30/06/2025  : Update SW-VERSION
 * 1.3.1:  31/03/2025  : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E 
 * 1.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 1.2.0:  31/12/2024  : Update SW-Version for Ver22.02.00/Ver22.02.00.D U2Bx Final release
 * 1.1.2:  31/10/2024  : Update SW-VERSION to 1.1.2
 * 1.0.1:  16/10/2023  : Add version check for OS module
 * 1.0.0:  19/05/2023  : Initial Version
 */
/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/*
 * Included for RAM Test module version information and other modules version
 * information
 */
#include "RamTst_Version.h"

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/

/* AUTOSAR release version information */
#define RAMTST_VERSION_C_AR_RELEASE_MAJOR_VERSION    RAMTST_AR_RELEASE_MAJOR_VERSION_VALUE
#define RAMTST_VERSION_C_AR_RELEASE_MINOR_VERSION    RAMTST_AR_RELEASE_MINOR_VERSION_VALUE
#define RAMTST_VERSION_C_AR_RELEASE_REVISION_VERSION RAMTST_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define RAMTST_VERSION_C_SW_MAJOR_VERSION            RAMTST_SW_MAJOR_VERSION_VALUE
#define RAMTST_VERSION_C_SW_MINOR_VERSION            RAMTST_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/

#if (RAMTST_VERSION_AR_RELEASE_MAJOR_VERSION != RAMTST_VERSION_C_AR_RELEASE_MAJOR_VERSION)
  #error "RamTst_Version.c : Mismatch in Release Major Version"
#endif
#if (RAMTST_VERSION_AR_RELEASE_MINOR_VERSION != RAMTST_VERSION_C_AR_RELEASE_MINOR_VERSION)
  #error "RamTst_Version.c : Mismatch in Release Minor Version"
#endif
#if (RAMTST_VERSION_AR_RELEASE_REVISION_VERSION != RAMTST_VERSION_C_AR_RELEASE_REVISION_VERSION)
  #error "RamTst_Version.c : Mismatch in Release Revision Version"
#endif

#if (RAMTST_VERSION_SW_MAJOR_VERSION != RAMTST_VERSION_C_SW_MAJOR_VERSION)
  #error "RamTst_Version.c : Mismatch in Software Major Version"
#endif
#if (RAMTST_VERSION_SW_MINOR_VERSION != RAMTST_VERSION_C_SW_MINOR_VERSION)
  #error "RamTst_Version.c : Mismatch in Software Minor Version"
#endif

#if (RAMTST_VERSION_CHECK_EXT_MODULES == STD_ON)
/* Rte Module Version Check */
#if (RAMTST_CRITICAL_SECTION_PROTECTION == STD_ON)
#if ((RTE_AR_RELEASE_MAJOR_VERSION != RAMTST_AR_RELEASE_MAJOR_VERSION) || \
     (RTE_AR_RELEASE_MINOR_VERSION != RAMTST_AR_RELEASE_MINOR_VERSION))
  #error "The AR version of Rte.h does not match the expected version"
#endif
#endif /* End of RAMTST_CRITICAL_SECTION_PROTECTION */

/* Dem Module Version Check */
#if ((DEM_AR_RELEASE_MAJOR_VERSION != RAMTST_AR_RELEASE_MAJOR_VERSION) || \
     (DEM_AR_RELEASE_MINOR_VERSION != RAMTST_AR_RELEASE_MINOR_VERSION))
  #error "The AR version of Dem.h does not match the expected version"
#endif

/* Det Module Version Check */
#if (RAMTST_DEV_ERROR_DETECT == STD_ON)
#if ((DET_AR_RELEASE_MAJOR_VERSION != RAMTST_AR_RELEASE_MAJOR_VERSION) || \
     (DET_AR_RELEASE_MINOR_VERSION != RAMTST_AR_RELEASE_MINOR_VERSION))
  #error "The AR version of Det.h does not match the expected version"
#endif
#endif /* #if (RAMTST_DEV_ERROR_DETECT == STD_ON) */

/* Os Module Version Check */
#if (RAMTST_MULTI_CORE_SUPPORT == STD_ON)
#if ((OS_AR_RELEASE_MAJOR_VERSION != RAMTST_AR_RELEASE_MAJOR_VERSION) || \
     (OS_AR_RELEASE_MINOR_VERSION != RAMTST_AR_RELEASE_MINOR_VERSION))
  #error "The AR version of Os.h does not match the expected version"
#endif
#endif /* #if (RAMTST_MULTI_CORE_SUPPORT == STD_ON) */
#endif /* #if (RAMTST_VERSION_CHECK_EXT_MODULES == STD_ON) */

/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
