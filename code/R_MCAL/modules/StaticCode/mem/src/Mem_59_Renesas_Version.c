/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Mem_59_Renesas_Version.c                                                                            */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2024-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains code for version checking for modules included by MEM                                           */
/* Driver                                                                                                             */
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
 * 1.1.0:  30/06/2025  : Update SW-VERSION for RH850/Ver22.01.00(D) U2Ax release
 * 1.0.3:  25/04/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 Release
 * 1.0.2:  31/03/2025  : Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02 Release
 *                       Update check version for MemAcc_GeneralTypes
 * 1.0.1:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 1.0.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 * 0.0.2:  31/10/2024  : Support commonize
 * 0.0.1:  30/08/2024  : Initial Version
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/*
 * Included for Mem module version information and other modules version
 * information
 */
#include "Mem_59_Renesas_Version.h"

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define MEM_59_RENESAS_VERSION_C_AR_RELEASE_MAJOR_VERSION    MEM_59_RENESAS_AR_RELEASE_MAJOR_VERSION_VALUE
#define MEM_59_RENESAS_VERSION_C_AR_RELEASE_MINOR_VERSION    MEM_59_RENESAS_AR_RELEASE_MINOR_VERSION_VALUE
#define MEM_59_RENESAS_VERSION_C_AR_RELEASE_REVISION_VERSION MEM_59_RENESAS_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define MEM_59_RENESAS_VERSION_C_SW_MAJOR_VERSION            MEM_59_RENESAS_SW_MAJOR_VERSION_VALUE
#define MEM_59_RENESAS_VERSION_C_SW_MINOR_VERSION            MEM_59_RENESAS_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (MEM_59_RENESAS_VERSION_AR_RELEASE_MAJOR_VERSION != MEM_59_RENESAS_VERSION_C_AR_RELEASE_MAJOR_VERSION)
     #error "Mem_59_Renesas_Version.c : Mismatch in Release Major Version"
#endif
#if (MEM_59_RENESAS_VERSION_AR_RELEASE_MINOR_VERSION != MEM_59_RENESAS_VERSION_C_AR_RELEASE_MINOR_VERSION)
     #error "Mem_59_Renesas_Version.c : Mismatch in Release Minor Version"
#endif
#if (MEM_59_RENESAS_VERSION_AR_RELEASE_REVISION_VERSION != MEM_59_RENESAS_VERSION_C_AR_RELEASE_REVISION_VERSION)
     #error "Mem_59_Renesas_Version.c : Mismatch in Release Revision Version"
#endif

#if (MEM_59_RENESAS_VERSION_SW_MAJOR_VERSION != MEM_59_RENESAS_VERSION_C_SW_MAJOR_VERSION)
     #error "Mem_59_Renesas_Version.c : Mismatch in Software Major Version"
#endif
#if (MEM_59_RENESAS_VERSION_SW_MINOR_VERSION != MEM_59_RENESAS_VERSION_C_SW_MINOR_VERSION)
     #error "Mem_59_Renesas_Version.c : Mismatch in Software Minor Version"
#endif

#if (MEM_59_RENESAS_VERSION_CHECK_EXT_MODULES == STD_ON)
/* Rte Module Version Check */
#if (MEM_59_RENESAS_CRITICAL_SECTION_PROTECTION == STD_ON)
#if ((RTE_AR_RELEASE_MAJOR_VERSION != MEM_59_RENESAS_AR_RELEASE_MAJOR_VERSION) || \
                                              (RTE_AR_RELEASE_MINOR_VERSION != MEM_59_RENESAS_AR_RELEASE_MINOR_VERSION))
     #error "The AR version of Rte.h does not match the expected version"
#endif
#endif /* (MEM_59_RENESAS_CRITICAL_SECTION_PROTECTION == STD_ON) */
/* Det Module Version Check */
#if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
#if ((DET_AR_RELEASE_MAJOR_VERSION != MEM_59_RENESAS_AR_RELEASE_MAJOR_VERSION) || \
                                              (DET_AR_RELEASE_MINOR_VERSION != MEM_59_RENESAS_AR_RELEASE_MINOR_VERSION))
     #error "The AR version of Det.h does not match the expected version"
#endif
#endif /* End of MEM_59_RENESAS_DEV_ERROR_DETECT */
/* MemAccGeneral Module Version Check */
#if ((MEMACC_GENERALTYPES_AR_RELEASE_MAJOR_VERSION != MEM_59_RENESAS_AR_RELEASE_MAJOR_VERSION) || \
                              (MEMACC_GENERALTYPES_AR_RELEASE_MINOR_VERSION != MEM_59_RENESAS_AR_RELEASE_MINOR_VERSION))
#error "The AR version of MemAcc_GeneralTypes.h does not match the expected version"
#endif
#endif /* End of (MEM_59_RENESAS_VERSION_CHECK_EXT_MODULES == STD_ON) */

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
