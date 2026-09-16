/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas R22.11 X2x MCAL Components                                                          */
/* Module       = Fee_Version.h                                                                                       */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2024-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains macros required for checking versions of modules included by FEE Module.                        */
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
 * 1.1.1:  30/06/2025:  Remove SW-VERSION in file header
 * 1.1.0:  30/06/2025:  Update SW-VERSION for U2Ax Ver22.01.00(D) Final Release
 * 1.0.3:  25/04/2025:  Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03
 * 1.0.2:  31/03/2025:  Include Section add MemAcc_GeneralTypes.h
 *                      Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02 Release
 * 1.0.1:  28/02/2025:  Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 1.0.0:  31/12/2024:  Update SW-VERSION 1.0.0.
 * 0.0.2:  31/10/2024:  Update SW-VERSION 0.0.2.
 * 0.0.1:  30/08/2024:  Initial Version.
 */
/**********************************************************************************************************************/

#ifndef FEE_VERSION_H
#define FEE_VERSION_H

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Fee module version information is required for inter module version check */
#include "Fee.h"

/* Following is required only when external modules version check is enabled */
#if (FEE_VERSION_CHECK_EXT_MODULES == STD_ON)

#if (FEE_DEV_ERROR_DETECT == STD_ON)
/* DET module version information is required only when DET is enabled */
#include "Det.h"
#endif

#if (FEE_CRITICAL_SECTION_PROTECTION == STD_ON)
/* RTE module version information is required only when critical section protection is enabled */
#include "Rte.h"
#endif

#include "MemIf.h"

#include "MemAcc.h"

#include "MemAcc_GeneralTypes.h"

#endif /* #if (FEE_VERSION_CHECK_EXT_MODULES == STD_ON) */
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define FEE_VERSION_AR_RELEASE_MAJOR_VERSION                                    FEE_AR_RELEASE_MAJOR_VERSION
#define FEE_VERSION_AR_RELEASE_MINOR_VERSION                                    FEE_AR_RELEASE_MINOR_VERSION
#define FEE_VERSION_AR_RELEASE_REVISION_VERSION                                 FEE_AR_RELEASE_REVISION_VERSION

/* Module Software version information */
#define FEE_VERSION_SW_MAJOR_VERSION                                            FEE_SW_MAJOR_VERSION
#define FEE_VERSION_SW_MINOR_VERSION                                            FEE_SW_MINOR_VERSION
/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/

#endif /* FEE_VERSION_H */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
