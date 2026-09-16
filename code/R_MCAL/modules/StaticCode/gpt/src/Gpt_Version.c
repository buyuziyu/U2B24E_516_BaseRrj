/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Gpt_Version.c                                                                                       */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains code for version checking for modules included by GPT                                           */
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
 *  2.4.0  30/06/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.01.00 (D) release
 *  2.3.2  25/04/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03
 *  2.3.1  31/03/2025  : Update SW-VERSION for RH850/U2BxE MCAL Ver22.00.02/Ver22.00.02.D Release
 *  2.3.0  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 *  2.2.0  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 *  2.1.2  31/10/2024  : Update SW-VERSION for U2Bx Beta2 release
 *  2.0.1  17/10/2023  : Update preprocessor GPT_AR_R21_11_VERSION to GPT_AR_R22_11_VERSION
 *  2.0.0  12/06/2023  : Update pre-processor GPT_AR_VERSION == GPT_AR_R21_11_VERSION
 *         12/05/2023  : Update SW version 2.0.0
 *  1.4.5  02/12/2022  : Add pre-processor GPT_AR_VERSION == GPT_AR_2111_VERSION for support AR21-11;
 *                       Update SW-VERSION to 1.4.5
 *  1.4.3  12/04/2022  : Corrected error content from "Mismatch in Specification Major/Minor Version" to
 *                       "Mismatch in Release Major/Minor Version", from "Mismatch in Specification Patch Version" to
 *                       "Mismatch in Release Revision Version", from "Mismatch in Major/Minor Version" to
 *                       "Mismatch in Software Major/Minor Version".
 *  1.3.1  02/07/2021  : Format source code to 120 characters
 *  1.2.0  17/07/2020  : Release
 *  1.1.0  19/06/2020  : Release
 *  1.0.0  01/01/2020  : Initial Version
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
#include "Gpt_Version.h"
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR Release version information */
#define GPT_VERSION_C_AR_RELEASE_MAJOR_VERSION    GPT_AR_RELEASE_MAJOR_VERSION_VALUE
#define GPT_VERSION_C_AR_RELEASE_MINOR_VERSION    GPT_AR_RELEASE_MINOR_VERSION_VALUE
#define GPT_VERSION_C_AR_RELEASE_REVISION_VERSION GPT_AR_RELEASE_REVISION_VERSION_VALUE
/* File version information */
#define GPT_VERSION_C_SW_MAJOR_VERSION            GPT_SW_MAJOR_VERSION_VALUE
#define GPT_VERSION_C_SW_MINOR_VERSION            GPT_SW_MINOR_VERSION_VALUE
/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (GPT_VERSION_AR_RELEASE_MAJOR_VERSION != GPT_VERSION_C_AR_RELEASE_MAJOR_VERSION)
  #error "Gpt_Version.c : Mismatch in Release Major Version"
#endif
#if (GPT_VERSION_AR_RELEASE_MINOR_VERSION != GPT_VERSION_C_AR_RELEASE_MINOR_VERSION)
  #error "Gpt_Version.c : Mismatch in Release Minor Version"
#endif
#if (GPT_VERSION_AR_RELEASE_REVISION_VERSION != GPT_VERSION_C_AR_RELEASE_REVISION_VERSION)
  #error "Gpt_Version.c : Mismatch in Release Revision Version"
#endif
#if (GPT_VERSION_SW_MAJOR_VERSION != GPT_VERSION_C_SW_MAJOR_VERSION)
  #error "Gpt_Version.c : Mismatch in Software Major Version"
#endif
#if (GPT_VERSION_SW_MINOR_VERSION != GPT_VERSION_C_SW_MINOR_VERSION)
  #error "Gpt_Version.c : Mismatch in Software Minor Version"
#endif

#if (GPT_VERSION_CHECK_EXT_MODULES == STD_ON)
/* Rte Module Version Check */
#if (GPT_CRITICAL_SECTION_PROTECTION == STD_ON)
#if ((RTE_AR_RELEASE_MAJOR_VERSION != GPT_AR_RELEASE_MAJOR_VERSION) ||  \
                                                         (RTE_AR_RELEASE_MINOR_VERSION != GPT_AR_RELEASE_MINOR_VERSION))
  #error "The AR version of Rte.h does not match the expected version"
#endif
#endif
/* Det Module Version Check */
#if ((GPT_DEV_ERROR_DETECT == STD_ON) || (GPT_AR_VERSION == GPT_AR_431_VERSION) || \
  (GPT_AR_VERSION == GPT_AR_R22_11_VERSION))
#if ((DET_AR_RELEASE_MAJOR_VERSION != GPT_AR_RELEASE_MAJOR_VERSION) || \
                                                         (DET_AR_RELEASE_MINOR_VERSION != GPT_AR_RELEASE_MINOR_VERSION))
  #error "The AR version of Det.h does not match the expected version"
#endif
#endif
/* EcuM Module Version Check */
#if (GPT_REPORT_WAKEUP_SOURCE == STD_ON)
#if ((ECUM_AR_RELEASE_MAJOR_VERSION != GPT_AR_RELEASE_MAJOR_VERSION) || \
                                                        (ECUM_AR_RELEASE_MINOR_VERSION != GPT_AR_RELEASE_MINOR_VERSION))
  #error "The AR version of EcuM.h does not match the expected version"
#endif
#endif
/* OS Version Check */
#if ((OS_AR_RELEASE_MAJOR_VERSION != GPT_AR_RELEASE_MAJOR_VERSION) ||   \
                                                          (OS_AR_RELEASE_MINOR_VERSION != GPT_AR_RELEASE_MINOR_VERSION))
  #error "The AR version of Os.h does not match the expected version"
#endif
/* Dem Module Version Check */
#if ((DEM_AR_RELEASE_MAJOR_VERSION != GPT_AR_RELEASE_MAJOR_VERSION) ||  \
                                                         (DEM_AR_RELEASE_MINOR_VERSION != GPT_AR_RELEASE_MINOR_VERSION))
  #error "The AR version of Dem.h does not match the expected version"
#endif
#endif /* GPT_VERSION_CHECK_EXT_MODULES == STD_ON */

/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
