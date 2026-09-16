/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2X MCAL Components                                                                 */
/* Module       = Ocu_Version.c                                                                                       */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2023-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains code for version checking for modules included by OCU                                           */
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
 *  1.4.0  30/05/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.01
 *  1.3.1  31/03/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 and RH850/U2Bx-E MCAL Ver22.00.02 Release
 *  1.3.0  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 *  1.2.0  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 *  1.0.1  09/11/2023  : Move OS and DEM version check into preprocessor of OCU_VERSION_CHECK_EXT_MODULES
 *  1.0.0  04/04/2023  : Initial Version
 */
/**********************************************************************************************************************/
/***********************************************************************************************************************
**                                             Margin for Control History                                             **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
#include "Ocu_Version.h"
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR Release version information */
#define OCU_VERSION_C_AR_RELEASE_MAJOR_VERSION    OCU_AR_RELEASE_MAJOR_VERSION_VALUE
#define OCU_VERSION_C_AR_RELEASE_MINOR_VERSION    OCU_AR_RELEASE_MINOR_VERSION_VALUE
#define OCU_VERSION_C_AR_RELEASE_REVISION_VERSION OCU_AR_RELEASE_REVISION_VERSION_VALUE
/* File version information */
#define OCU_VERSION_C_SW_MAJOR_VERSION            OCU_SW_MAJOR_VERSION_VALUE
#define OCU_VERSION_C_SW_MINOR_VERSION            OCU_SW_MINOR_VERSION_VALUE
/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (OCU_VERSION_AR_RELEASE_MAJOR_VERSION != OCU_VERSION_C_AR_RELEASE_MAJOR_VERSION)
  #error "Ocu_Version.c : Mismatch in Release Major Version"
#endif
#if (OCU_VERSION_AR_RELEASE_MINOR_VERSION != OCU_VERSION_C_AR_RELEASE_MINOR_VERSION)
  #error "Ocu_Version.c : Mismatch in Release Minor Version"
#endif
#if (OCU_VERSION_AR_RELEASE_REVISION_VERSION != OCU_VERSION_C_AR_RELEASE_REVISION_VERSION)
  #error "Ocu_Version.c : Mismatch in Release Revision Version"
#endif
#if (OCU_VERSION_SW_MAJOR_VERSION != OCU_VERSION_C_SW_MAJOR_VERSION)
  #error "Ocu_Version.c : Mismatch in Software Major Version"
#endif
#if (OCU_VERSION_SW_MINOR_VERSION != OCU_VERSION_C_SW_MINOR_VERSION)
  #error "Ocu_Version.c : Mismatch in Software Minor Version"
#endif

#if (OCU_VERSION_CHECK_EXT_MODULES == STD_ON)

/* Rte Module Version Check */
#if (OCU_CRITICAL_SECTION_PROTECTION == STD_ON)
#if ((RTE_AR_RELEASE_MAJOR_VERSION != OCU_AR_RELEASE_MAJOR_VERSION) || \
                                                        (RTE_AR_RELEASE_MINOR_VERSION != OCU_AR_RELEASE_MINOR_VERSION))
  #error "The AR version of Rte.h does not match the expected version"
#endif
#endif

/* Det Module Version Check */
#if ((DET_AR_RELEASE_MAJOR_VERSION != OCU_AR_RELEASE_MAJOR_VERSION) || \
                                                        (DET_AR_RELEASE_MINOR_VERSION != OCU_AR_RELEASE_MINOR_VERSION))
  #error "The AR version of Det.h does not match the expected version"
#endif

/* OS Version Check */
#if ((OS_AR_RELEASE_MAJOR_VERSION != OCU_AR_RELEASE_MAJOR_VERSION) || \
                                                         (OS_AR_RELEASE_MINOR_VERSION != OCU_AR_RELEASE_MINOR_VERSION))
  #error "The AR version of Os.h does not match the expected version"
#endif

/* Dem Module Version Check */
#if ((DEM_AR_RELEASE_MAJOR_VERSION != OCU_AR_RELEASE_MAJOR_VERSION) || \
                                                        (DEM_AR_RELEASE_MINOR_VERSION != OCU_AR_RELEASE_MINOR_VERSION))
  #error "The AR version of Dem.h does not match the expected version"
#endif

#endif /* End of OCU_VERSION_CHECK_EXT_MODULES == STD_ON */
/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
