/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Adc_Version.c                                                                                       */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains code for version checking for modules included by ADC                                           */
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
 * 2.5.1: 30/06/2025 : Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.03 release
 *                     Remove SW-VERSION in file header
 * 2.5.0: 30/06/2025 : Update SW-VERSION for RH850/Ver22.01.00 (D) U2Ax release
 * 2.4.0: 31/05/2025 : Update SW-VERSION for RH850/Ver21.01.01 U2Cx release
 * 2.3.1: 31/03/2025 : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 * 2.3.1: 28/02/2025 : Update SW-VERSION for Ver22.00.02 U2Ax Beta 1 Release
 * 2.3.0: 28/02/2025 : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0: 31/12/2024 : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 * 2.1.3: 30/09/2024 : Update SW-VERSION 2.1.3
 * 2.1.2: 30/09/2024 : Update SW-VERSION 2.1.2
 * 1.3.1: 07/07/2021 : Changed comment format to 120 columns
 *        07/04/2021 : Changed to comply with coding rules.
 * 1.2.0: 14/07/2020 : Release
 * 1.1.0: 19/06/2020 : Release
 * 1.0.0: 09/01/2020 : Initial Version
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for macro definitions and type definitions */
#include "Adc.h"
/*
 * Included for Adc module version information and other modules version
 * information
 */
#include "Adc_Version.h"

#if (ADC_VERSION_CHECK_EXT_MODULES == STD_ON)

#if (ADC_DEV_ERROR_DETECT == STD_ON)
/* DET module version information is required only when DET is enabled */
#include "Det.h"
#endif
/* DEM module version information is required */
#if (ADC_CRITICAL_SECTION_PROTECTION == STD_ON)
/* RTE module version information is required only when critical section protection is enabled */
#include "Rte.h"
#endif
/* OS module version information is required */
#include "Os.h"
/* Included for declaration of the function Dem_ReportErrorStatus() */
#include "Dem.h"
#endif /* (ADC_VERSION_CHECK_EXT_MODULES == STD_ON) */

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define ADC_VERSION_C_AR_RELEASE_MAJOR_VERSION    ADC_AR_RELEASE_MAJOR_VERSION_VALUE
#define ADC_VERSION_C_AR_RELEASE_MINOR_VERSION    ADC_AR_RELEASE_MINOR_VERSION_VALUE
#define ADC_VERSION_C_AR_RELEASE_REVISION_VERSION ADC_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define ADC_VERSION_C_SW_MAJOR_VERSION            ADC_SW_MAJOR_VERSION_VALUE
#define ADC_VERSION_C_SW_MINOR_VERSION            ADC_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (ADC_VERSION_AR_RELEASE_MAJOR_VERSION != ADC_VERSION_C_AR_RELEASE_MAJOR_VERSION)
  #error "Adc_Version.c : Mismatch in Release Major Version"
#endif

#if (ADC_VERSION_AR_RELEASE_MINOR_VERSION != ADC_VERSION_C_AR_RELEASE_MINOR_VERSION)
  #error "Adc_Version.c : Mismatch in Release Minor Version"
#endif

#if (ADC_VERSION_AR_RELEASE_REVISION_VERSION != ADC_VERSION_C_AR_RELEASE_REVISION_VERSION)
  #error "Adc_Version.c : Mismatch in Release Revision Version"
#endif

#if (ADC_VERSION_SW_MAJOR_VERSION != ADC_VERSION_C_SW_MAJOR_VERSION)
  #error "Adc_Version.c : Mismatch in Software Major Version"
#endif

#if (ADC_VERSION_SW_MINOR_VERSION != ADC_VERSION_C_SW_MINOR_VERSION)
  #error "Adc_Version.c : Mismatch in Software Minor Version"
#endif

#if (ADC_VERSION_CHECK_EXT_MODULES == STD_ON)

#if (ADC_CRITICAL_SECTION_PROTECTION == STD_ON)
#if ((RTE_AR_RELEASE_MAJOR_VERSION != ADC_AR_RELEASE_MAJOR_VERSION) || \
     (RTE_AR_RELEASE_MINOR_VERSION != ADC_AR_RELEASE_MINOR_VERSION))
  #error "The AR version of Rte.h does not match the expected version"
#endif
#endif /* (ADC_CRITICAL_SECTION_PROTECTION == STD_ON) */

#if (ADC_DEV_ERROR_DETECT == STD_ON)
#if ((DET_AR_RELEASE_MAJOR_VERSION != ADC_AR_RELEASE_MAJOR_VERSION) || \
     (DET_AR_RELEASE_MINOR_VERSION != ADC_AR_RELEASE_MINOR_VERSION))
  #error "The AR version of Det.h does not match the expected version"
#endif
#endif /* (ADC_DEV_ERROR_DETECT == STD_ON) */

#if ((OS_AR_RELEASE_MAJOR_VERSION != ADC_AR_RELEASE_MAJOR_VERSION) || \
     (OS_AR_RELEASE_MINOR_VERSION != ADC_AR_RELEASE_MINOR_VERSION))
  #error "The AR version of Os.h does not match the expected version"
#endif

#if ((DEM_AR_RELEASE_MAJOR_VERSION != ADC_AR_RELEASE_MAJOR_VERSION) || \
     (DEM_AR_RELEASE_MINOR_VERSION != ADC_AR_RELEASE_MINOR_VERSION))
  #error "The AR version of Dem.h does not match the expected version"
#endif

#endif /* (ADC_VERSION_CHECK_EXT_MODULES == STD_ON) */

/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
