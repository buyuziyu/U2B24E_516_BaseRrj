/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Lin_Version.c                                                                                       */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2019-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains code for version checking for modules included by LIN Driver.                                   */
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
 * 2.1.1:  30/08/2024  : As part of ARDAACL-45721, following changes are made:
                         1. Add Version Check for LinIf.h and Lin_GeneralTypes.h
 * 1.4.3:  14/04/2022  : Update "Mismatch in Release Patch Version" to "Mismatch in Release Revision Version"
 *                       Update SW-VERSION to 1.4.3
 * 1.3.2:  04/03/2022  : Update SW-VERSION to 1.4.2
 * 1.3.1:  02/07/2021  : Format source code to 120 characters.
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
/*
 * Included for Lin module version information and other modules version
 * information
 */
#include "Lin_Version.h"

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define LIN_VERSION_C_AR_RELEASE_MAJOR_VERSION    LIN_AR_RELEASE_MAJOR_VERSION_VALUE
#define LIN_VERSION_C_AR_RELEASE_MINOR_VERSION    LIN_AR_RELEASE_MINOR_VERSION_VALUE
#define LIN_VERSION_C_AR_RELEASE_REVISION_VERSION LIN_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define LIN_VERSION_C_SW_MAJOR_VERSION            LIN_SW_MAJOR_VERSION_VALUE
#define LIN_VERSION_C_SW_MINOR_VERSION            LIN_SW_MINOR_VERSION_VALUE
/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (LIN_VERSION_AR_RELEASE_MAJOR_VERSION != LIN_VERSION_C_AR_RELEASE_MAJOR_VERSION)
  #error "Lin_Version.c : Mismatch in Release Major Version"
#endif

#if (LIN_VERSION_AR_RELEASE_MINOR_VERSION != LIN_VERSION_C_AR_RELEASE_MINOR_VERSION)
  #error "Lin_Version.c : Mismatch in Release Minor Version"
#endif

#if (LIN_VERSION_AR_RELEASE_REVISION_VERSION != LIN_VERSION_C_AR_RELEASE_REVISION_VERSION)
  #error "Lin_Version.c : Mismatch in Release Revision Version"
#endif

#if (LIN_VERSION_SW_MAJOR_VERSION != LIN_VERSION_C_SW_MAJOR_VERSION)
  #error "Lin_Version.c : Mismatch in Major Version"
#endif

#if (LIN_VERSION_SW_MINOR_VERSION != LIN_VERSION_C_SW_MINOR_VERSION)
  #error "Lin_Version.c : Mismatch in Minor Version"
#endif

#if (LIN_VERSION_CHECK_EXT_MODULES == STD_ON)
#if ((LINIF_AR_RELEASE_MAJOR_VERSION != LIN_AR_RELEASE_MAJOR_VERSION) || \
     (LINIF_AR_RELEASE_MINOR_VERSION != LIN_AR_RELEASE_MINOR_VERSION))
  #error "The AR version of LinIf.h does not match the expected version"
#endif

#if ((LIN_GENERALTYPES_AR_RELEASE_MAJOR_VERSION != LIN_AR_RELEASE_MAJOR_VERSION) || \
     (LIN_GENERALTYPES_AR_RELEASE_MINOR_VERSION != LIN_AR_RELEASE_MINOR_VERSION))
  #error "The AR version of Lin_GeneralTypes.h does not match the expected version"
#endif

#if ((DEM_AR_RELEASE_MAJOR_VERSION != LIN_AR_RELEASE_MAJOR_VERSION) || \
     (DEM_AR_RELEASE_MINOR_VERSION != LIN_AR_RELEASE_MINOR_VERSION))
  #error "The AR version of Dem.h does not match the expected version"
#endif /* End of DEM */

#if (LIN_DEV_ERROR_DETECT == STD_ON)
#if ((DET_AR_RELEASE_MAJOR_VERSION != LIN_AR_RELEASE_MAJOR_VERSION) || \
     (DET_AR_RELEASE_MINOR_VERSION != LIN_AR_RELEASE_MINOR_VERSION))
  #error "The AR version of Det.h does not match the expected version"
#endif /* End of DET */
#endif /* End of LIN_DEV_ERROR_DETECT */

#if (LIN_WAKEUP_SUPPORT == STD_ON)
#if ((ECUM_AR_RELEASE_MAJOR_VERSION != LIN_AR_RELEASE_MAJOR_VERSION) || \
     (ECUM_AR_RELEASE_MINOR_VERSION != LIN_AR_RELEASE_MINOR_VERSION))
  #error "The AR version of EcuM.h does not match the expected version"
#endif /* End of EcuM */
#endif /* End of LIN_WAKEUP_SUPPORT */

#if ((OS_AR_RELEASE_MAJOR_VERSION != LIN_AR_RELEASE_MAJOR_VERSION) || \
     (OS_AR_RELEASE_MINOR_VERSION != LIN_AR_RELEASE_MINOR_VERSION))
  #error "The AR version of Os.h does not match the expected version"
#endif /* End of OS */

#if (LIN_CRITICAL_SECTION_PROTECTION == STD_ON)
#if ((RTE_AR_RELEASE_MAJOR_VERSION != LIN_AR_RELEASE_MAJOR_VERSION) || \
     (RTE_AR_RELEASE_MINOR_VERSION != LIN_AR_RELEASE_MINOR_VERSION))
  #error "The AR version of Rte.h does not match the expected version"
#endif /* End of RTE */
#endif /* End of LIN_CRITICAL_SECTION_PROTECTION */

#endif /* End of LIN_VERSION_CHECK_EXT_MODULES */

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
