/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas R22.11 X2x MCAL Components                                                          */
/* Module       = Fee_InternalFct.h                                                                                   */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2024-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Header file for Fee_InternalFct.c.                                                                                 */
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
 * 0.0.2:  31/10/2024:  Update SW-VERSION 0.0.2.
 * 0.0.1:  30/08/2024:  Initial Version. 
 */
/**********************************************************************************************************************/

#ifndef  FEE_INTERNALFCT_H
#define  FEE_INTERNALFCT_H

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for Autosar Type definitions */
#include "Std_Types.h"
/* Included for MemIf types */
#include "MemIf.h"

#include "Fee.h"
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR Release version information */
#define FEE_INTERNALFCT_AR_RELEASE_MAJOR_VERSION                                FEE_AR_RELEASE_MAJOR_VERSION
#define FEE_INTERNALFCT_AR_RELEASE_MINOR_VERSION                                FEE_AR_RELEASE_MINOR_VERSION
#define FEE_INTERNALFCT_AR_RELEASE_REVISION_VERSION                             FEE_AR_RELEASE_REVISION_VERSION

/* Module Software version information */
#define FEE_INTERNALFCT_SW_MAJOR_VERSION                                        FEE_SW_MAJOR_VERSION
#define FEE_INTERNALFCT_SW_MINOR_VERSION                                        FEE_SW_MINOR_VERSION

/***********************************************************************************************************************
**                                             Global Function Prototypes                                             **
***********************************************************************************************************************/

#define FEE_START_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"

extern FUNC(uint16, FEE_PRIVATE_CODE) Fee_GetBlockIndex(uint16 LusBlockNumber);

extern FUNC(MemIf_JobResultType, FEE_PRIVATE_CODE) Fee_JobReadMain(void);

extern FUNC(MemIf_JobResultType, FEE_PRIVATE_CODE) Fee_JobReadDone(void);

extern FUNC(MemIf_JobResultType, FEE_PRIVATE_CODE) Fee_JobWriteMain(void);

extern FUNC(MemIf_JobResultType, FEE_PRIVATE_CODE) Fee_JobWriteBlockData(void);

extern FUNC(MemIf_JobResultType, FEE_PRIVATE_CODE) Fee_WriteUnalignedBlockData(void);

extern FUNC(MemIf_JobResultType, FEE_PRIVATE_CODE) Fee_JobWriteValidateBlock(void);

extern FUNC(MemIf_JobResultType, FEE_PRIVATE_CODE) Fee_JobWriteDone(void);

extern FUNC(MemIf_JobResultType, FEE_PRIVATE_CODE) Fee_JobInvalidateBlock(void);

extern FUNC(MemIf_JobResultType, FEE_PRIVATE_CODE) Fee_JobInvalidateBlockDone(void);

extern FUNC(MemIf_JobResultType, FEE_PRIVATE_CODE) Fee_JobEraseImmediate(void);

extern FUNC(void, FEE_PRIVATE_CODE) Fee_CheckMemIfJobResult(MemIf_JobResultType LenJobResult);

extern FUNC(MemIf_JobResultType, FEE_PRIVATE_CODE) Fee_HandleInternalManagementCommands(void);

#define FEE_STOP_SEC_PRIVATE_CODE
#include "Fee_MemMap.h"

#endif /* #define FEE_INTERNALFCT_H */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
