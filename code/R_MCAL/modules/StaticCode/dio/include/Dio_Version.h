/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Dio_Version.h                                                                                       */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2019-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains macros required for checking versions of modules included by DIO Driver.                        */
/*                                                                                                                    */
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
 * 2.4.1:  19/06/2025  : Remove SW-VERSION in header file
 * 2.4.0:  30/06/2025  : Update SW-VERSION for RH850/Ver22.01.00(D) U2Ax Release
 * 2.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D U2Bx Final Release
 * 2.1.2:  31/10/2024  : Update SW-VERSION to for Ver22.01.02 U2Bx Beta2
 * 2.1.1:  11/06/2024  : As part of  ARDAACL-42260, following changes are made
 *                       Add #include "Os.h"
 * 2.1.0:  29/02/2024  : Update SW-VERSION to 2.1.0
 * 2.0.2:  25/12/2023  : Update SW-Verison 2.0.2     
 * 2.0.1:  12/10/2023  : Update SW-VERSION 2.0.1
 * 2.0.0:  15/05/2023  : Updated SW-VERSION 
 * 1.4.1:  08/10/2021  : Updated SW-VERSION 
 * 1.3.1:  02/07/2021  : Format source code to 120 characters
 * 1.2.0:  26/08/2020  : Release
 * 1.1.1:  26/08/2020  : Update revision history
 * 1.1.0:  19/06/2020  : Release
 * 1.0.0:  21/11/2019  : Initial Version
 */
/**********************************************************************************************************************/
#ifndef DIO_VERSION_H
#define DIO_VERSION_H

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for module version information */
#include "Dio.h"

/* Following is required only when external modules version check is enabled */
#if (DIO_VERSION_CHECK_EXT_MODULES == STD_ON)

#if (DIO_DEV_ERROR_DETECT == STD_ON)
/* DET module version information is required only when DET is enabled */
#include "Det.h"
#endif

#if (DIO_CRITICAL_SECTION_PROTECTION == STD_ON)
/*
 * RTE module version information is required only when critical section
 * protection is enabled
 */
#include "Rte.h"
#endif

#if (DIO_MULTI_CORE_SUPPORT == STD_ON)
/*
 * OS module version information is required only when Multicore support is enabled
 */
#include "Os.h"
#endif

#endif

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define DIO_VERSION_AR_RELEASE_MAJOR_VERSION    DIO_AR_RELEASE_MAJOR_VERSION
#define DIO_VERSION_AR_RELEASE_MINOR_VERSION    DIO_AR_RELEASE_MINOR_VERSION
#define DIO_VERSION_AR_RELEASE_REVISION_VERSION DIO_AR_RELEASE_REVISION_VERSION

/* Module Software version information */
#define DIO_VERSION_SW_MAJOR_VERSION            DIO_SW_MAJOR_VERSION
#define DIO_VERSION_SW_MINOR_VERSION            DIO_SW_MINOR_VERSION

#endif /* DIO_VERSION_H */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
