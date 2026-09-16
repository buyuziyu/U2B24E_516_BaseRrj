/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas R22.11 X2x MCAL Components                                                          */
/* Module       = Fee_Ram.h                                                                                           */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2024-2025 Renesas Electronics Corporation. All rights reserved.                                                */
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
 * 1.1.1:  30/06/2025:  Remove SW-VERSION in file header
 * 1.1.0:  30/06/2025:  Update SW-VERSION for U2Ax Ver22.01.00(D) Final Release
 * 1.0.3:  25/04/2025:  Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03
 * 1.0.2:  31/03/2025:  Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02 Release
 * 1.0.1:  28/02/2025:  Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 1.0.0:  31/12/2024:  Update SW-VERSION 1.0.0.
 * 0.0.2:  31/10/2024:  Fixed typo of macro FEE_MAX_DEFINED_ADDRESS_AREA_NUMBER.
 *                      Remove definition of global variable Fee_GulTimeOutCounter, Fee_GblTimeOutMonitor.
 * 0.0.1:  30/08/2024:  Initial Version.
 */
/**********************************************************************************************************************/

#ifndef FEE_RAM_H
#define FEE_RAM_H

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/

/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Standard AUTOSAR types */
#include "Std_Types.h"
/* Included for Fee types and macro definitions */
#include "Fee_Types.h"

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define FEE_RAM_AR_RELEASE_MAJOR_VERSION                                        FEE_AR_RELEASE_MAJOR_VERSION
#define FEE_RAM_AR_RELEASE_MINOR_VERSION                                        FEE_AR_RELEASE_MINOR_VERSION
#define FEE_RAM_AR_RELEASE_REVISION_VERSION                                     FEE_AR_RELEASE_REVISION_VERSION

/* Module Software version information */
#define FEE_RAM_SW_MAJOR_VERSION                                                FEE_SW_MAJOR_VERSION
#define FEE_RAM_SW_MINOR_VERSION                                                FEE_SW_MINOR_VERSION

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/

#define FEE_START_SEC_VAR_NO_INIT_BOOLEAN
#include "Fee_MemMap.h"
extern VAR(boolean, FEE_VAR) Fee_GblWaitMemAccResult;
#define FEE_STOP_SEC_VAR_NO_INIT_BOOLEAN
#include "Fee_MemMap.h"

#define FEE_START_SEC_VAR_NO_INIT_16
#include "Fee_MemMap.h"
extern VAR(uint16, FEE_VAR) Fee_GusCurrAddrAreaId;
extern VAR(uint16, FEE_VAR) Fee_GusCurrSubAddrAreaId;
extern VAR(uint16, FEE_VAR) Fee_GusBlockIndex;
#define FEE_STOP_SEC_VAR_NO_INIT_16
#include "Fee_MemMap.h"

#define FEE_START_SEC_VAR_NO_INIT_32
#include "Fee_MemMap.h"
extern VAR(MemAcc_AddressType, FEE_VAR) Fee_GulJobRefAreaAddr;
extern VAR(MemAcc_AddressType, FEE_VAR) Fee_GulJobDataAddr;
extern VAR(uint32, FEE_VAR) Fee_GaaDataBuffer[FEE_DATA_BUFFER];
#define FEE_STOP_SEC_VAR_NO_INIT_32
#include "Fee_MemMap.h"

#define FEE_START_SEC_VAR_INIT_UNSPECIFIED
#include "Fee_MemMap.h"
extern VAR(MemIf_StatusType, FEE_VAR) Fee_GenModuleState;
#define FEE_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Fee_MemMap.h"

#define FEE_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Fee_MemMap.h"
extern VAR(Fee_CommandType, FEE_VAR) Fee_GenRequestedCmd;
extern VAR(Fee_CommandType, FEE_VAR) Fee_enPreviousRequestCmd;
extern P2CONST(Fee_ConfigType, TYPEDEF, FEE_APPL_CONST) Fee_GpBlockConfig;
extern VAR(MemIf_JobResultType, FEE_VAR) Fee_GenJobResult;
extern VAR(Fee_InforJobRequest, FEE_VAR) Fee_GstVar;
extern VAR(Fee_BlockInfoType, FEE_VAR) Fee_GaaBlockInfo[FEE_MAX_CONFIGURED_BLOCK_NUMBER];
extern VAR(Fee_AddrAreaInfoType, FEE_VAR) Fee_GaaAddrAreaInfo[FEE_MAX_DEFINED_ADDRESS_AREA_NUMBER];
#define FEE_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Fee_MemMap.h"

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/

#endif /* FEE_RAM_H */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
