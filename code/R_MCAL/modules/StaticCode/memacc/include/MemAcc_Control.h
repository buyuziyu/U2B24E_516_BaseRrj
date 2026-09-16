/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas R22-11 X2x MCAL Components                                                          */
/* Module       = MemAcc_Control.h                                                                                    */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2024-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains Global variable declarations of MemAcc                                                          */
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
/*              Devices:        RH850/X2x                                                                             */
/*====================================================================================================================*/

/***********************************************************************************************************************
**                                              Revision Control History                                              **
***********************************************************************************************************************/
/*
 * 1.1.1:  30/06/2025:  Remove SW-VERSION in file header
 * 1.1.0:  30/06/2025:  Update SW-VERSION for RH850/Ver22.01.00 (D) U2Ax release
 * 1.0.3:  25/04/2025:  Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03
 * 1.0.2:  31/03/2025:  Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02
 * 1.0.1:  28/02/2025:  Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 1.0.0:  31/12/2024:  Update SW-VERSION for Ver22.02.00 U2Bx Final Release. 
 * 0.0.2:  31/10/2024: Update to support macro MEMACC_COMPARE_API
 * 0.0.1:  30/08/2024: Initial Version.
 */
/**********************************************************************************************************************/
#ifndef MEMACC_CONTROL_H
#define MEMACC_CONTROL_H
/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
#include "MemAcc_GeneralTypes.h"

#include "MemAcc_Types.h"

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR Release version information */
#define MEMACC_CONTROL_AR_RELEASE_MAJOR_VERSION    MEMACC_AR_RELEASE_MAJOR_VERSION
#define MEMACC_CONTROL_AR_RELEASE_MINOR_VERSION    MEMACC_AR_RELEASE_MINOR_VERSION
#define MEMACC_CONTROL_AR_RELEASE_REVISION_VERSION MEMACC_AR_RELEASE_REVISION_VERSION

/* Module Software version information */
#define MEMACC_CONTROL_SW_MAJOR_VERSION            MEMACC_SW_MAJOR_VERSION
#define MEMACC_CONTROL_SW_MINOR_VERSION            MEMACC_SW_MINOR_VERSION

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/
#define MEMACC_START_SEC_PRIVATE_CODE
#include "MemAcc_MemMap.h"

extern FUNC(void, MEMACC_PRIVATE_CODE) MemAcc_ProcessJobResult(Mem_59_Renesas_InstanceIdType LulInstanceId);
extern FUNC(void, MEMACC_PRIVATE_CODE) MemAcc_ProcessReadJob(Mem_59_Renesas_InstanceIdType LulInstanceId);
extern FUNC(void, MEMACC_PRIVATE_CODE) MemAcc_ProcessEraseJob(Mem_59_Renesas_InstanceIdType LulInstanceId);
extern FUNC(void, MEMACC_PRIVATE_CODE) MemAcc_ProcessBlankCheckJob(Mem_59_Renesas_InstanceIdType LulInstanceId);
extern FUNC(void, MEMACC_PRIVATE_CODE) MemAcc_ProcessHwSpecificJob(Mem_59_Renesas_InstanceIdType LulInstanceId);
#if (MEMACC_COMPARE_API == STD_ON)
extern FUNC(Std_ReturnType, MEMACC_PRIVATE_CODE) MemAcc_ProcessCompareData(uint16 LusAreaId);
#endif /* #if (MEMACC_COMPARE_API == STD_ON) */
extern FUNC(void, MEMACC_PRIVATE_CODE) MemAcc_ProcessJobOk(uint16 LusAreaId);
extern FUNC(void, MEMACC_PRIVATE_CODE) MemAcc_ProcessWriteJob(Mem_59_Renesas_InstanceIdType LulInstanceId);
extern FUNC(void, MEMACC_PRIVATE_CODE) MemAcc_CheckCancelRequest(void);
extern FUNC(void, MEMACC_PRIVATE_CODE) MemAcc_SelectAreaToProcess(Mem_59_Renesas_InstanceIdType LulInstanceIdx);

#define MEMACC_STOP_SEC_PRIVATE_CODE
#include "MemAcc_MemMap.h"
#endif /* MEMACC_CONTROL_H */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
