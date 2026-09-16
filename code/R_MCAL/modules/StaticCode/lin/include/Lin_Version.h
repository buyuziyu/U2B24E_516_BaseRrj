/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Lin_Version.h                                                                                       */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2019-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains macros required for checking versions of modules included by LIN Driver.                        */
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
 * 2.1.1:  30/08/2024  : Add include LinIf.h and Lin_GeneralTypes.h
 * 1.4.3:  14/04/2022  : Update SW-VERSION to 1.4.3
 * 1.3.2:  04/03/2022  : Update SW-VERSION
 * 1.3.1:  02/07/2021  : Format source code to 120 characters.
 * 1.2.0:  26/08/2020  : Release.
 * 1.1.0:  19/06/2020  : Release.
 * 1.0.1:  16/04/2020  : Modified #include heading files.
 * 1.0.0:  12/03/2019  : Initial Version.
 *
 */
/**********************************************************************************************************************/

#ifndef LIN_VERSION_H
#define LIN_VERSION_H

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Lin module version information is required for inter module version check */
#include "Lin.h"

/* Following is required only when external modules version check is enabled */
#if (LIN_VERSION_CHECK_EXT_MODULES == STD_ON)

/* Included for declaration of the function Dem_SetEventStatus() */
#include "Dem.h"
#if (LIN_DEV_ERROR_DETECT == STD_ON)
/* DET module version information is required only when DET is enabled */
#include "Det.h"
#endif

/* ECUM module version information is required */
#if (LIN_WAKEUP_SUPPORT == STD_ON)
#include "EcuM.h"
#endif

/* OS module version information is required */
#include "Os.h"

/* RTE module version information is required only when critical section protection is enabled */
#if (LIN_CRITICAL_SECTION_PROTECTION == STD_ON)
#include "Rte.h"
#endif

/* LinIf module version information is required */
#include "LinIf.h"

/* LinGeneral module version information is required */
#include "Lin_GeneralTypes.h"

#endif
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define LIN_VERSION_AR_RELEASE_MAJOR_VERSION    LIN_AR_RELEASE_MAJOR_VERSION
#define LIN_VERSION_AR_RELEASE_MINOR_VERSION    LIN_AR_RELEASE_MINOR_VERSION
#define LIN_VERSION_AR_RELEASE_REVISION_VERSION LIN_AR_RELEASE_REVISION_VERSION

/* Module Software version information */
#define LIN_VERSION_SW_MAJOR_VERSION            LIN_SW_MAJOR_VERSION
#define LIN_VERSION_SW_MINOR_VERSION            LIN_SW_MINOR_VERSION
/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/

#endif /* LIN_VERSION_H */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
