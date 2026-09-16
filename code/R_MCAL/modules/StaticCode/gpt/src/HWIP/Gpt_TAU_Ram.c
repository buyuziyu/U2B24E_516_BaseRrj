/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Gpt_TAU_Ram.c                                                                                       */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2020,2021,2023-2025 Renesas Electronics Corporation. All rights reserved.                                      */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Global variable declarations                                                                                       */
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
 *  2.4.1  30/06/2025  : As part of QAC 11.6.0 support, following changes are made:
 *                       Add QAC message 1502
 *  2.4.0  30/06/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.01.00 (D) release
 *  2.3.2  25/04/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03
 *  2.3.1  31/03/2025  : Update SW-VERSION for RH850/U2BxE MCAL Ver22.00.02/Ver22.00.02.D Release
 *  2.3.0  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 *  2.2.0  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 *  2.1.2  31/10/2024  : As part of QAC 9.5.0 support, following changes are made
 *                       1.Remove QAC message 1531
 *  2.0.0  26/07/2023  : Change Gpt_Mapping.h to Gpt_MemMap.h, Add CWE QAC header
 *         12/05/2023  : Update SW version 2.0.0
 *                       Add version checking
 *  1.3.2  22/08/2021  : Changed Gpt_MemMap.h to Gpt_Mapping.h.
 *  1.3.1  02/07/2021  : Format source code to 120 characters
 *         06/05/2021  : Updated the Memclass to GPT_VAR_NO_INIT for
 *                       Gpt_GpTAUUnitConfig
 *  1.2.0  17/07/2020  : Release
 *  1.1.0  19/06/2020  : Release
 *         12/03/2020  : Change #include "Gpt_Ram.h" to "Gpt_TAU_Ram.h"
 *  1.0.0  01/01/2020  : Initial Version
 */
/**********************************************************************************************************************/
/***********************************************************************************************************************
**                                             Margin for Control History                                             **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (1:1502)    : The object '%1s' is defined but is not used within this project.                             */
/* Rule                : MISRA C:2012 Dir-1.1-C90                                                                     */
/* JV-01 Justification : This is accepted since there is no problem with the software behavior. This variable is      */
/*                       intended for user use, so it will not be used within the module scope                        */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:5087)    : Use of #include directive after code fragment.                                               */
/* Rule                : MISRA C:2012 Rule-20.1                                                                       */
/* JV-01 Justification : This is done as per Memory Requirement, (MEMMAP003 - Specification of Memory Mapping).       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for module version information and other types declarations */
#include "Gpt.h"
/* Included for macro definitions */
#include "Gpt_TAU_PBTypes.h"
/* Included for RAM variable declarations */
#include "Gpt_TAU_Ram.h"

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR Release version information */
#define GPT_TAU_RAM_C_AR_RELEASE_MAJOR_VERSION    GPT_AR_RELEASE_MAJOR_VERSION_VALUE
#define GPT_TAU_RAM_C_AR_RELEASE_MINOR_VERSION    GPT_AR_RELEASE_MINOR_VERSION_VALUE
#define GPT_TAU_RAM_C_AR_RELEASE_REVISION_VERSION GPT_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define GPT_TAU_RAM_C_SW_MAJOR_VERSION            GPT_SW_MAJOR_VERSION_VALUE
#define GPT_TAU_RAM_C_SW_MINOR_VERSION            GPT_SW_MINOR_VERSION_VALUE
/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (GPT_TAU_RAM_AR_RELEASE_MAJOR_VERSION != GPT_TAU_RAM_C_AR_RELEASE_MAJOR_VERSION)
  #error "Gpt_TAU_Ram.c : Mismatch in Release Major Version"
#endif
#if (GPT_TAU_RAM_AR_RELEASE_MINOR_VERSION != GPT_TAU_RAM_C_AR_RELEASE_MINOR_VERSION)
  #error "Gpt_TAU_Ram.c : Mismatch in Release Minor Version"
#endif
#if (GPT_TAU_RAM_AR_RELEASE_REVISION_VERSION != GPT_TAU_RAM_C_AR_RELEASE_REVISION_VERSION)
  #error "Gpt_TAU_Ram.c : Mismatch in Release Revision Version"

#endif
#if (GPT_TAU_RAM_SW_MAJOR_VERSION != GPT_TAU_RAM_C_SW_MAJOR_VERSION)
  #error "Gpt_TAU_Ram.c : Mismatch in Software Major Version"
#endif
#if (GPT_TAU_RAM_SW_MINOR_VERSION != GPT_TAU_RAM_C_SW_MINOR_VERSION)
  #error "Gpt_TAU_Ram.c : Mismatch in Software Minor Version"
#endif

/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/
#define GPT_START_SEC_VAR_NO_INIT_PTR
#include "Gpt_MemMap.h"
/* Global pointer variable for TAU Unit configuration */
P2CONST(Gpt_TAUUnitConfigType, GPT_VAR_NO_INIT, GPT_CONFIG_DATA) Gpt_GpTAUUnitConfig;                                   /* PRQA S 1502 # JV-01 */
#define GPT_STOP_SEC_VAR_NO_INIT_PTR
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
