/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Eth_Version.c                                                                                       */
/*====================================================================================================================*/
/*                                          COPYRIGHT                                                                 */
/*====================================================================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains code for version checking for modules included by Eth Driver                                    */
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
/* Renesas shall not have any obligation to maintain, service or provide bug fixes for the supplied Product(s)        */
/* and/or the Application.                                                                                            */
/*                                                                                                                    */
/* Each User is solely responsible for determining the appropriateness of using the Product(s) and assumes all risks  */
/* associated with its exercise of rights under this Agreement, including, but not limited to the risks and costs     */
/* of program errors, compliance with applicable laws, damage to or loss of data, programs or equipment,              */
/* and unavailability or interruption of operations.                                                                  */
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
/*                                        Devices:        X2x                                                         */
/*====================================================================================================================*/

/***********************************************************************************************************************
**                                        Revision Control History                                                    **
***********************************************************************************************************************/
/*
 * 2.4.1: 30/06/2025    : Remove the SW-VERSION from header of file
 * 2.4.0: 30/06/2025    : Update SW-VERSION for RH850/Ver22.01.00 (D) U2Ax release
 * 2.3.1: 31/03/2025    : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 * 2.3.0: 28/02/2025    : Update SW-VERSION for Ver22.01.00/Ver22.01.00.D U2Cx Release
 * 2.2.0: 31/12/2024    : Update SW-VERSION for Ver22.02.00(D) U2Bx Final Release 
 * 2.1.2: 31/10/2024    : Increase SW-VERSION to 2.1.2
 * 2.1.1: 30/08/2024    : Add Check AR version for Os.h, Eth_GeneralTypes.h
 * 1.4.2: 24/08/2021    : Modify the format to 120 characters
 * 1.4.1: 07/05/2021    : Remove vendor ID from the file name, API names
 *                        and parameters according to BSW00347 requirement
 *        06/07/2021    : Updated QA-C 9.5.0 comments.
 * 1.2.0: 13/07/2020    : Release
 * 1.1.0: 19/06/2020    : Release
 * 1.0.0: 25/03/2020    : Initial Version
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                       Include Section                                                              **
***********************************************************************************************************************/
/* Included for Eth module version information and other types declarations */
#include "Eth.h"

#if (ETH_DEV_ERROR_DETECT == STD_ON)
/* DET module version information is required only when DET is enabled */
#include "Det.h"
#endif

#if (ETH_CRITICAL_SECTION_PROTECTION == STD_ON)
/*
 * RTE module version information is required only when critical section
 * protection is enabled
 */
#include "Rte.h"
#endif
/* DEM module version information */
#include "Dem.h"

/***********************************************************************************************************************
**                                       Version Information                                                          **
***********************************************************************************************************************/
/* AUTOSAR Release version information */
#define ETH_VERSION_C_AR_RELEASE_MAJOR_VERSION ETH_AR_RELEASE_MAJOR_VERSION_VALUE
#define ETH_VERSION_C_AR_RELEASE_MINOR_VERSION ETH_AR_RELEASE_MINOR_VERSION_VALUE
#define ETH_VERSION_C_AR_RELEASE_REVISION_VERSION ETH_AR_RELEASE_REVISION_VERSION_VALUE

/***********************************************************************************************************************
**                                        Version Check                                                               **
***********************************************************************************************************************/
#if (ETH_VERSION_C_AR_RELEASE_MAJOR_VERSION != ETH_AR_RELEASE_MAJOR_VERSION)
#error "Eth_Version.c : Mismatch in Release Major Version"
#endif

#if (ETH_VERSION_C_AR_RELEASE_MINOR_VERSION != ETH_AR_RELEASE_MINOR_VERSION)
#error "Eth_Version.c : Mismatch in Release Minor Version"
#endif

#if (ETH_VERSION_C_AR_RELEASE_REVISION_VERSION != ETH_AR_RELEASE_REVISION_VERSION)
#error "Eth_Version.c : Mismatch in Release Revision Version"
#endif

#if (ETH_VERSION_CHECK_EXT_MODULES == STD_ON)

#if (ETH_CRITICAL_SECTION_PROTECTION == STD_ON)
#if ((RTE_AR_RELEASE_MAJOR_VERSION != ETH_AR_RELEASE_MAJOR_VERSION) \
|| (RTE_AR_RELEASE_MINOR_VERSION != ETH_AR_RELEASE_MINOR_VERSION))
  #error "The AR version of Rte.h does not match the expected version"
#endif
#endif /* End of ETH_CRITICAL_SECTION_PROTECTION */

#if ((DEM_AR_RELEASE_MAJOR_VERSION != ETH_AR_RELEASE_MAJOR_VERSION) \
|| (DEM_AR_RELEASE_MINOR_VERSION != ETH_AR_RELEASE_MINOR_VERSION))
  #error "The AR version of Dem.h does not match the expected version"
#endif

#if (ETH_DEV_ERROR_DETECT == STD_ON)
#if ((DET_AR_RELEASE_MAJOR_VERSION != ETH_AR_RELEASE_MAJOR_VERSION) \
|| (DET_AR_RELEASE_MINOR_VERSION != ETH_AR_RELEASE_MINOR_VERSION))
  #error "The AR version of Det.h does not match the expected version"
#endif
#endif /* End of ETH_DEV_ERROR_DETECT */

#if ((OS_AR_RELEASE_MAJOR_VERSION != ETH_AR_RELEASE_MAJOR_VERSION) || \
     (OS_AR_RELEASE_MINOR_VERSION != ETH_AR_RELEASE_MINOR_VERSION))
  #error "The AR version of Os.h does not match the expected version"
#endif

#if ((ETH_GENERALTYPES_AR_RELEASE_MAJOR_VERSION != ETH_AR_RELEASE_MAJOR_VERSION) || \
     (ETH_GENERALTYPES_AR_RELEASE_MINOR_VERSION != ETH_AR_RELEASE_MINOR_VERSION))
  #error "The AR version of Eth_GeneralTypes.h does not match the expected version"
#endif

#endif /* End of ETH_VERSION_CHECK_EXT_MODULES */

/***********************************************************************************************************************
**                                      Global Data                                                                  **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                      Function Definitions                                                          **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                      End of File                                                                   **
***********************************************************************************************************************/
