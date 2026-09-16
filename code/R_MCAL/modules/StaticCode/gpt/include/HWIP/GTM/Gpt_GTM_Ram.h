/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Gpt_GTM_Ram.h                                                                                       */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2024, 2025 Renesas Electronics Corporation. All rights reserved.                                               */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Global variable declarations.                                                                                      */
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
 *  2.1.2  31/10/2024  : Initial Version.
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/

#ifndef GPT_GTM_RAM_H
#define GPT_GTM_RAM_H

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for using Std Type(e.g. STD_ON), Compiler Macros(e.g. P2FUNC), Platform Types(e.g. uint8) */
#include "Std_Types.h"
/* Included for GPT module specific definitions */
#include "Gpt_Cfg.h"
/* Included for type of Gpt_HwFuncTableType */
#include "Gpt_Types.h"
/* Include for type of Gpt_ATUUnitConfigType and Gpt_ATUCommonPrescalerConfigType */
#include "Gpt_GTM_PBTypes.h"
/* Included for macro definitions (e.g. Service IDs)*/
#include "Gpt.h"
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR Release version information */
#define GPT_GTM_RAM_AR_RELEASE_MAJOR_VERSION     GPT_AR_RELEASE_MAJOR_VERSION
#define GPT_GTM_RAM_AR_RELEASE_MINOR_VERSION     GPT_AR_RELEASE_MINOR_VERSION
#define GPT_GTM_RAM_AR_RELEASE_REVISION_VERSION  GPT_AR_RELEASE_REVISION_VERSION

/* File version information */
#define GPT_GTM_RAM_SW_MAJOR_VERSION    GPT_SW_MAJOR_VERSION
#define GPT_GTM_RAM_SW_MINOR_VERSION    GPT_SW_MINOR_VERSION

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/
#if (GPT_TIMER_IP_GTM == STD_ON)
#define GPT_START_SEC_VAR_INIT_UNSPECIFIED
#include "Gpt_MemMap.h"
extern Gpt_HwFuncTableType Gpt_GtmFunc;
#define GPT_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Gpt_MemMap.h"

#define GPT_START_SEC_VAR_NO_INIT_PTR
#include "Gpt_MemMap.h"

/* Global pointer variable for GTM Unit configuration */
extern const Gpt_GTMUnitConfigType* volatile Gpt_GpGTMUnitConfig;

#define GPT_STOP_SEC_VAR_NO_INIT_PTR
#include "Gpt_MemMap.h"
#endif
/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/

#endif /* GPT_GTM_RAM_H */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
