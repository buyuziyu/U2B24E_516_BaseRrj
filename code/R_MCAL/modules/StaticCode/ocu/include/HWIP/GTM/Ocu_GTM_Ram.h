/*====================================================================================================================*/
/* Project      = RH850/X2x AR4 MCAL Development                                                                      */
/* Module       = Ocu_GTM_Ram.h                                                                                       */
/*====================================================================================================================*/
/*                                                       COPYRIGHT                                                    */
/*====================================================================================================================*/
/* (c) 2025 Renesas Electronics Corporation. All rights reserved.                                                     */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* API function implementations of OCU Driver                                                                         */
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
/*                                              Devices:        X2x                                                   */
/*====================================================================================================================*/
/***********************************************************************************************************************
**                                              Revision Control History                                              **
***********************************************************************************************************************/
/*
 * 1.4.0: 30/05/2025 : Initial Version.
 */
/**********************************************************************************************************************/
#ifndef OCU_GTM_RAM_H
#define OCU_GTM_RAM_H
/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for using Std Type(e.g. STD_ON), Compiler Macros(e.g. P2FUNC), Platform Types(e.g. uint8) */
#include "Std_Types.h"
/* Included for OCU module-specific definitions */
#include "Ocu_Cfg.h"
/* Included for Type of Ocu_HwFuncTableType */
#include "Ocu_Types.h"
/* Included for Ocu_GtmTbuUnitConfigType */
#include "Ocu_GTM_PBTypes.h"
/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define OCU_GTM_RAM_AR_RELEASE_MAJOR_VERSION    OCU_AR_RELEASE_MAJOR_VERSION
#define OCU_GTM_RAM_AR_RELEASE_MINOR_VERSION    OCU_AR_RELEASE_MINOR_VERSION
#define OCU_GTM_RAM_AR_RELEASE_REVISION_VERSION OCU_AR_RELEASE_REVISION_VERSION

/* Software module version information */
#define OCU_GTM_RAM_SW_MAJOR_VERSION            OCU_SW_MAJOR_VERSION
#define OCU_GTM_RAM_SW_MINOR_VERSION            OCU_SW_MINOR_VERSION
#define OCU_GTM_RAM_SW_PATCH_VERSION            OCU_SW_PATCH_VERSION
/***********************************************************************************************************************
**                                                  Global Variables                                                  **
***********************************************************************************************************************/
#if(OCU_TIMER_IP_GTM == STD_ON)

#define OCU_START_SEC_CONST_PTR
#include "Ocu_MemMap.h"
extern CONST(Ocu_HwFuncTableType, OCU_CONST) Ocu_GtmFunc;
#define OCU_STOP_SEC_CONST_PTR
#include "Ocu_MemMap.h"


#if (OCU_GTM_TBU_ATOM_SOMB_USED == STD_ON)
#define OCU_START_SEC_VAR_NO_INIT_PTR
#include "Ocu_MemMap.h"
/* Global pointer to the address of CMU Unit Config data */
extern P2CONST(Ocu_GtmTbuUnitConfigType, OCU_VAR, OCU_CONFIG_CONST) Ocu_GpGtmTbuUnitConfig;
#define OCU_STOP_SEC_VAR_NO_INIT_PTR
#include "Ocu_MemMap.h"

#define OCU_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Ocu_MemMap.h"
/* RAM Allocation of TBU Channel data */
extern VAR(Ocu_GaaCyclicRamDataType, OCU_VAR_NO_INIT) Ocu_GaaCyclicRamData[OCU_TOTAL_ATOM_OUTPUT_USED];
#define OCU_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Ocu_MemMap.h"
#endif

#endif /*#if (OCU_GTM_UNIT_USED == STD_ON)*/
#endif /* OCU_GTM_RAM_H */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
