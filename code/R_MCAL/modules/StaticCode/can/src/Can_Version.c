/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Can_Version.c                                                                                       */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2019-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains code for version checking for modules included by CAN Driver                                    */
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
/*              Devices:       X2x                                                                                    */
/*====================================================================================================================*/

/***********************************************************************************************************************
**                                                  Revision History                                                  **
***********************************************************************************************************************/
/*
 * 2.4.1: 30/06/2025  : Remove the SW-VERSION from header of file
 * 2.4.0: 30/05/2025  : Update SW-VERSION for RH850/Ver22.01.00 (D) U2Ax Release
 * 2.3.1: 31/03/2025  : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 * 2.3.0: 28/02/2025  : Update SW-VERSION for RH850/Ver22.01.00/Ver22.01.00.D Final Release
 * 2.2.0: 31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 * 2.1.2: 31/10/2024  : Update SW-VERSION for Ver22.01.02 to 2.1.2
 * 2.1.1: 30/08/2024  : As part of CANXL driver support, following changes are made:
 *                      1. Add Can_GeneralTypes.h to check version information
 *                      2. Add precondition to include CanXLTrcv.h and check CanXLTrv version
 *                      3. Support for CanXLTrcv
 * 2.0.0: 02/08/2023  : Remove redundant QAC message
 *      : 31/05/2023  : Remove redundant QAC message
 * 1.4.3: 15/05/2022  : Add comment message 0857
 * 1.3.4: 13/04/2022  : Add comment message 0857
 * 1.3.3: 08/03/2022  : Add comment message 0857
 * 1.3.2: 30/08/2021  : Add comment for QAC Msg(2:0857)
 * 1.3.1: 02/07/2021  : Format source code to 120 characters
 *                      Improve Violation tag (remove START/END)
 * 1.2.0: 09/07/2020  : Release.
 *        28/07/2020  : Add QAC 9.3.1 comment.
 * 1.1.0: 19/06/2020  : Release.
 * 1.0.0: 09/12/2019  : Initial version.
 */
/**********************************************************************************************************************/
/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* CAN module version information is required for inter module version check */
#include "Can.h"
/*
 * Included for CAN module version information and other modules version
 * information
 */
#include "Can_Version.h"

/* Following is required only when external modules version check is enabled */
#if (CAN_VERSION_CHECK_EXT_MODULES == STD_ON)

/* CanIf module version information is required */
#include "CanIf.h"

/* DEM module version information is required */
#include "Dem.h"

#if (CAN_CANXL_SUPPORTED == STD_ON)
/* CanXLTrcv module version information is required */
#include "CanXLTrcv.h"
#endif

/* CanGeneral module version information is required */
#include "Can_GeneralTypes.h"

#if (CAN_DEV_ERROR_DETECT == STD_ON)
/* DET module version information is required only when DET is enabled */
#include "Det.h"
#endif

#if (CAN_WAKEUP_SUPPORT == STD_ON)
/*
 * EcuM module version information is required only when wakeup source is
 * enabled
 */
#include "EcuM.h"
#endif

/* OS module version information is required */
#include "Os.h"

#if (CAN_CRITICAL_SECTION_PROTECTION == STD_ON)
/*
 * RTE module version information is required only when critical section
 * protection is enabled
 */
#include "Rte.h"
#endif

#endif

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define CAN_VERSION_C_AR_RELEASE_MAJOR_VERSION    CAN_AR_RELEASE_MAJOR_VERSION_VALUE
#define CAN_VERSION_C_AR_RELEASE_MINOR_VERSION    CAN_AR_RELEASE_MINOR_VERSION_VALUE
#define CAN_VERSION_C_AR_RELEASE_REVISION_VERSION CAN_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define CAN_VERSION_C_SW_MAJOR_VERSION            CAN_SW_MAJOR_VERSION_VALUE
#define CAN_VERSION_C_SW_MINOR_VERSION            CAN_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
/* Functionality related to R4.0 */
#if (CAN_VERSION_C_AR_RELEASE_MAJOR_VERSION != CAN_VERSION_AR_RELEASE_MAJOR_VERSION)
  #error "Can_Version.c : Mismatch in Release Major Version"
#endif

#if (CAN_VERSION_C_AR_RELEASE_MINOR_VERSION != CAN_VERSION_AR_RELEASE_MINOR_VERSION)
  #error "Can_Version.c : Mismatch in Release Minor Version"
#endif

#if (CAN_VERSION_C_AR_RELEASE_REVISION_VERSION != CAN_VERSION_AR_RELEASE_REVISION_VERSION)
  #error "Can_Version.c : Mismatch in Release Revision Version"
#endif

#if (CAN_VERSION_C_SW_MAJOR_VERSION != CAN_VERSION_SW_MAJOR_VERSION)
  #error "Can_Version.c : Mismatch in Software Major Version"
#endif
#if (CAN_VERSION_C_SW_MINOR_VERSION != CAN_VERSION_SW_MINOR_VERSION)
  #error "Can_Version.c : Mismatch in Software Minor Version"
#endif

#if (CAN_VERSION_CHECK_EXT_MODULES == STD_ON)
#if ((CANIF_AR_RELEASE_MAJOR_VERSION != CAN_AR_RELEASE_MAJOR_VERSION) || \
     (CANIF_AR_RELEASE_MINOR_VERSION != CAN_AR_RELEASE_MINOR_VERSION))
  #error "The AR version of CanIf.h does not match the expected version"
#endif

#if (CAN_DEV_ERROR_DETECT == STD_ON)
#if ((DET_AR_RELEASE_MAJOR_VERSION != CAN_AR_RELEASE_MAJOR_VERSION) || \
     (DET_AR_RELEASE_MINOR_VERSION != CAN_AR_RELEASE_MINOR_VERSION))
  #error "The AR version of Det.h does not match the expected version"
#endif
#endif

#if ((DEM_AR_RELEASE_MAJOR_VERSION != CAN_AR_RELEASE_MAJOR_VERSION) || \
     (DEM_AR_RELEASE_MINOR_VERSION != CAN_AR_RELEASE_MINOR_VERSION))
  #error "The AR version of Dem.h does not match the expected version"
#endif

#if (CAN_CRITICAL_SECTION_PROTECTION == STD_ON)
#if ((RTE_AR_RELEASE_MAJOR_VERSION != CAN_AR_RELEASE_MAJOR_VERSION) || \
     (RTE_AR_RELEASE_MINOR_VERSION != CAN_AR_RELEASE_MINOR_VERSION))
  #error "The AR version of Rte.h does not match the expected version"
#endif
#endif /* End of CAN_CRITICAL_SECTION_PROTECTION */

#if (CAN_WAKEUP_SUPPORT == STD_ON)
#if ((ECUM_AR_RELEASE_MAJOR_VERSION != CAN_AR_RELEASE_MAJOR_VERSION) || \
     (ECUM_AR_RELEASE_MINOR_VERSION != CAN_AR_RELEASE_MINOR_VERSION))
  #error "The AR version of EcuM.h does not match the expected version"
#endif
#endif

#if ((OS_AR_RELEASE_MAJOR_VERSION != CAN_AR_RELEASE_MAJOR_VERSION) || \
     (OS_AR_RELEASE_MINOR_VERSION != CAN_AR_RELEASE_MINOR_VERSION))
  #error "The AR version of Os.h does not match the expected version"
#endif

#if (CAN_CANXL_SUPPORTED == STD_ON)
#if ((CANXLTRCV_AR_RELEASE_MAJOR_VERSION != CAN_AR_RELEASE_MAJOR_VERSION) || \
     (CANXLTRCV_AR_RELEASE_MINOR_VERSION != CAN_AR_RELEASE_MINOR_VERSION))
  #error "The AR version of CanXLTrcv.h does not match the expected version"
#endif
#endif

#if ((CAN_GENERALTYPES_AR_RELEASE_MAJOR_VERSION != CAN_AR_RELEASE_MAJOR_VERSION) || \
     (CAN_GENERALTYPES_AR_RELEASE_MINOR_VERSION != CAN_AR_RELEASE_MINOR_VERSION))
  #error "The AR version of Can_GeneralTypes.h does not match the expected version"
#endif

#endif /* (CAN_VERSION_CHECK_EXT_MODULES == STD_ON) */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
