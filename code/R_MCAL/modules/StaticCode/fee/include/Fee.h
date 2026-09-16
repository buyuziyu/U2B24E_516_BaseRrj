/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas R22.11 X2x MCAL Components                                                          */
/* Module       = Fee.h                                                                                               */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2024-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains macros, FEE type definitions, structure data types and API function prototypes of FEE Module    */
/*====================================================================================================================*/
/*                                                                                                                    */
/* Unless otherwise agreed upon in writing between your company and Renesas Electronics Corporation the following     */
/* shall apply!                                                                                                       */
/*                                                                                                                    */
/* Warranty Disclaimer                                                                                                */
/*                                                                                                                    */
/* There is no warranty of any kind whatsoever granted by Renesas. Any warranty is expressly disclaimed and excluded  */
/* by Renesas, either expressed or implied, including but not limited to those for non-infringement of intellectual   */
/* property, merchantability and/or fitness for the partFEElar purpose.                                               */
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
**                                                Revision Control History                                            **
***********************************************************************************************************************/
/*
 * 1.1.1:  30/06/2025:  Update FEE_SW_PATCH_VERSION to 1
 * 1.1.0:  30/06/2025:  Update SW-VERSION for U2Ax Ver22.01.00(D) Final Release
 * 1.0.3:  25/04/2025:  Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03
 * 1.0.2:  31/03/2025:  Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02 Release
 * 1.0.1:  28/02/2025:  Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 1.0.0:  31/12/2024:  Update SW-VERSION 1.0.0.
 * 0.0.2:  31/10/2024:  Update module version information.
 * 0.0.1:  30/08/2024:  Initial Version.
 */
/**********************************************************************************************************************/

#ifndef FEE_H
#define FEE_H

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/

/* Include standard Autosar Type */
#include "Std_Types.h"
/* Memory Abstraction Interface */
#include "MemIf.h"
/* Configuration precompile */
#include "Fee_Cfg.h"

#include "SchM_Fee.h"

#include "Fee_Types.h"

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE rule CWE-398, CWE-569                                            */
/*                       REFERENCE - ISO:C90-6.3.1 Primary Expressions                                                */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is           */
/*                       accepted.                                                                                    */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* Version autosar */
#define FEE_AR_R22_11_VERSION                                                   480

 /* Module Information */
#define FEE_VENDOR_ID                                                           59U
#define FEE_MODULE_ID                                                           21U
#define FEE_INSTANCE_ID                                                         FEE_INSTANCE_ID_VALUE

#if (FEE_AR_VERSION == FEE_AR_R22_11_VERSION)
/* AUTOSAR release version information */
#define FEE_AR_RELEASE_MAJOR_VERSION                                            4U
#define FEE_AR_RELEASE_MINOR_VERSION                                            8U
#define FEE_AR_RELEASE_REVISION_VERSION                                         0U
#endif

/* Software Version */
#define FEE_SW_MAJOR_VERSION                                                    1U
#define FEE_SW_MINOR_VERSION                                                    1U
#define FEE_SW_PATCH_VERSION                                                    1U

/***********************************************************************************************************************
**                                               API Service Id Macros                                                **
***********************************************************************************************************************/
/* Service Identifier */
#define FEE_INIT_SID                                                            0x00U
#define FEE_READ_SID                                                            0x02U
#define FEE_WRITE_SID                                                           0x03U
#define FEE_CANCEL_SID                                                          0x04U
#define FEE_GET_STATUS_SID                                                      0x05U
#define FEE_GET_JOB_RESULT_SID                                                  0x06U
#define FEE_INVALIDATE_BLOCK_SID                                                0x07U
#define FEE_GET_VERSIONINFO_SID                                                 0x08U
#define FEE_ERASE_IMMEDIATE_BLOCK_SID                                           0x09U

/***********************************************************************************************************************
**                                                  DET Error Codes                                                   **
***********************************************************************************************************************/
/* API service called when module was not initialized  */
#define FEE_E_UNINIT                                                            0x01U
/* API service called with invalid block number  */
#define FEE_E_INVALID_BLOCK_NO                                                  0x02U
/* API service called with invalid block offset  */
#define FEE_E_INVALID_BLOCK_OFS                                                 0x03U
/* API service called with invalid data pointer  */
#define FEE_E_PARAM_POINTER                                                     0x04U
/* API service called with invalid length information  */
#define FEE_E_INVALID_BLOCK_LEN                                                 0x05U
/* Fee_Init have ben initilaized. */
#define FEE_E_ALREADY_INITIALIZED                                               0x0A

/* Run Time Error */
#define FEE_E_BUSY                                                              0x06U
#define FEE_E_INVALID_CANCEL                                                    0x08U

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/
/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/
/***********************************************************************************************************************
**                                                    Type Definition                                                 **
***********************************************************************************************************************/
#define FEE_ADDRESS_OFFSET(Address, InputType)    (Address) = (Address) + sizeof(InputType)
/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/
#define FEE_START_SEC_PUBLIC_CODE
#include "Fee_MemMap.h"

extern FUNC(void, FEE_PUBLIC_CODE) Fee_Init(P2CONST(Fee_ConfigType, AUTOMATIC, FEE_APPL_CONST) ConfigPtr);


extern FUNC(Std_ReturnType, FEE_PUBLIC_CODE) Fee_Read(uint16 BlockNumber, uint16 BlockOffset, 
                                                P2VAR(uint8, AUTOMATIC, FEE_APPL_DATA) DataBufferPtr, uint16 Length);   /* PRQA S 3432 # JV-01 */

extern FUNC(Std_ReturnType, FEE_PUBLIC_CODE) Fee_Write(uint16 BlockNumber, 
                                                            P2CONST(uint8, AUTOMATIC, FEE_APPL_CONST) DataBufferPtr);

extern FUNC(void, FEE_PUBLIC_CODE) Fee_Cancel(void);

extern FUNC(MemIf_StatusType, FEE_PUBLIC_CODE) Fee_GetStatus(void);

extern FUNC(MemIf_JobResultType, FEE_PUBLIC_CODE) Fee_GetJobResult(void);

extern FUNC(Std_ReturnType, FEE_PUBLIC_CODE) Fee_InvalidateBlock(uint16 BlockNumber);

extern FUNC(void, FEE_PUBLIC_CODE) 
                            Fee_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, FEE_APPL_DATA) VersionInfoPtr);    /* PRQA S 3432 # JV-01 */

extern FUNC(Std_ReturnType, FEE_PUBLIC_CODE) Fee_EraseImmediateBlock(uint16 BlockNumber);

#if (FEE_POLLING_MODE == STD_OFF)
extern FUNC(void, FEE_PUBLIC_CODE) Fee_JobEndNotification(void);
#endif /* #if (FEE_POLLING_MODE == STD_OFF) */

#define FEE_STOP_SEC_PUBLIC_CODE
#include "Fee_MemMap.h"

#endif /* #ifndef FEE_H */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
