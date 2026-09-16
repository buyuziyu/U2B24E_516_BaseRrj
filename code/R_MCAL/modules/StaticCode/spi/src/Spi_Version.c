/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Spi_Version.c                                                                                       */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* Copyright(c) 2020-2025 Renesas Electronics Corporation.                                                            */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains code for version check for modules included by SPI Driver                                       */
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
 *                     : Remove QAC messages (2:0857) to fix redundant QAC messages
 *                     : Increase SW-VERSION up to 2.0.3
 * 2.1.0:  27/02/2024  : Update SW-VERSION to 2.1.0
 * 2.0.2:  14/12/2023  : Update SW-VERSION to 2.0.2
 * 2.0.1:  23/10/2023  : Update SW-VERSION to 2.0.1
 * 1.3.1:  02/07/2021  : Format source code to 120 characters 
 * 1.2.0:  17/07/2020  : Release
 * 1.1.0:  19/06/2020  : Release
 * 1.0.0:  24/03/2020  : Initial Version
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/*
 * Included for SPI module version information and other modules version information
 */
/* SPI module version information is required for inter module version check */
#include "Spi_Version.h"
#include "Spi.h"

/* Following is required only when external modules version check is enabled */
#if (SPI_VERSION_CHECK_EXT_MODULES == STD_ON)

/* DEM module version information is required */
#include "Dem.h"

/* DET module version information is required only when DET is enabled */
#include "Det.h"

/* OS module version information is required */
#include "Os.h"

#if (SPI_CRITICAL_SECTION_PROTECTION == STD_ON)
/*
 * RTE module version information is required only when critical section protection is enabled
 */
#include "Rte.h"
#endif

#endif /* (SPI_VERSION_CHECK_EXT_MODULES == STD_ON) */

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define SPI_VERSION_C_AR_RELEASE_MAJOR_VERSION    SPI_AR_RELEASE_MAJOR_VERSION_VALUE
#define SPI_VERSION_C_AR_RELEASE_MINOR_VERSION    SPI_AR_RELEASE_MINOR_VERSION_VALUE
#define SPI_VERSION_C_AR_RELEASE_REVISION_VERSION SPI_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define SPI_VERSION_C_SW_MAJOR_VERSION            SPI_SW_MAJOR_VERSION_VALUE
#define SPI_VERSION_C_SW_MINOR_VERSION            SPI_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (SPI_VERSION_AR_RELEASE_MAJOR_VERSION != SPI_VERSION_C_AR_RELEASE_MAJOR_VERSION)
#error "Spi_Version.c : Mismatch in Release Major Version"
#endif
#if (SPI_VERSION_AR_RELEASE_MINOR_VERSION != SPI_VERSION_C_AR_RELEASE_MINOR_VERSION)
#error "Spi_Version.c : Mismatch in Release Minor Version"
#endif
#if (SPI_VERSION_AR_RELEASE_REVISION_VERSION != SPI_VERSION_C_AR_RELEASE_REVISION_VERSION)
#error "Spi_Version.c : Mismatch in Release Revision Version"
#endif

#if (SPI_VERSION_SW_MAJOR_VERSION != SPI_VERSION_C_SW_MAJOR_VERSION)
#error "Spi_Version.c : Mismatch in Software Major Version"
#endif
#if (SPI_VERSION_SW_MINOR_VERSION != SPI_VERSION_C_SW_MINOR_VERSION)
#error "Spi_Version.c : Mismatch in Software Minor Version"
#endif

#if (SPI_VERSION_CHECK_EXT_MODULES == STD_ON)
#if (SPI_CRITICAL_SECTION_PROTECTION == STD_ON)
#if ((RTE_AR_RELEASE_MAJOR_VERSION != SPI_AR_RELEASE_MAJOR_VERSION) || \
     (RTE_AR_RELEASE_MINOR_VERSION != SPI_AR_RELEASE_MINOR_VERSION))
#error "The AR version of Rte.h does not match the expected version"
#endif
#endif /* (SPI_VERSION_CHECK_EXT_MODULES == STD_ON) */

#if (SPI_DEV_ERROR_DETECT == STD_ON)
#if ((DET_AR_RELEASE_MAJOR_VERSION != SPI_AR_RELEASE_MAJOR_VERSION) || \
     (DET_AR_RELEASE_MINOR_VERSION != SPI_AR_RELEASE_MINOR_VERSION))
#error "The AR version of Det.h does not match the expected version"
#endif
#endif /*(SPI_DEV_ERROR_DETECT == STD_ON) */

#if ((OS_AR_RELEASE_MAJOR_VERSION != SPI_AR_RELEASE_MAJOR_VERSION) || \
     (OS_AR_RELEASE_MINOR_VERSION != SPI_AR_RELEASE_MINOR_VERSION))
#error "The AR version of Os.h does not match the expected version"
#endif

#if ((DEM_AR_RELEASE_MAJOR_VERSION != SPI_AR_RELEASE_MAJOR_VERSION) || \
     (DEM_AR_RELEASE_MINOR_VERSION != SPI_AR_RELEASE_MINOR_VERSION))
#error "The AR version of Dem.h does not match the expected version"
#endif
#endif /* End of SPI_VERSION_CHECK_EXT_MODULES */

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/

/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
