/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Mem_59_Renesas_FPSYS_Control.h                                                                      */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2024-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Provision of prototypes for internal functions of Mem Component.                                                   */
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
/*              Devices:        U2Bx, U2Cx, U2Bx-E                                                                    */
/*====================================================================================================================*/

/***********************************************************************************************************************
**                                              Revision Control History                                              **
***********************************************************************************************************************/
/*
 * 1.1.0:  30/06/2025  : Support parameter on/off for Mem_59_Renesas_ReadImmediate API
 * 1.0.3:  25/04/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 Release
 * 1.0.2:  31/03/2025  : Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02 Release
 * 1.0.1:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 1.0.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 * 0.0.2:  31/10/2024  : As part of ARDAACJ-621, support downgrade from version AR23-11 to AR22-11.
 *                       Support commonize
 * 0.0.1:  30/08/2024  : Initial Version
 */
/**********************************************************************************************************************/
#ifndef MEM_59_RENESAS_FPSYS_CONTROL_H
#define MEM_59_RENESAS_FPSYS_CONTROL_H

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for version information macros */
#include "Mem_59_Renesas.h"
#include "Mem_59_Renesas_Types.h"
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define MEM_59_RENESAS_CONTROL_AR_RELEASE_MAJOR_VERSION    MEM_59_RENESAS_AR_RELEASE_MAJOR_VERSION
#define MEM_59_RENESAS_CONTROL_AR_RELEASE_MINOR_VERSION    MEM_59_RENESAS_AR_RELEASE_MINOR_VERSION
#define MEM_59_RENESAS_CONTROL_AR_RELEASE_REVISION_VERSION MEM_59_RENESAS_AR_RELEASE_REVISION_VERSION

/* Module Software version information */
#define MEM_59_RENESAS_CONTROL_SW_MAJOR_VERSION            MEM_59_RENESAS_SW_MAJOR_VERSION
#define MEM_59_RENESAS_CONTROL_SW_MINOR_VERSION            MEM_59_RENESAS_SW_MINOR_VERSION

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (7:0777)    : External identifier does not differ from other identifier(s) within the specified            */
/*                       number of significant characters.                                                            */
/* Rule                : CERTCCM DCL23, MSC15, MISRA C:2012 Rule-5.1, CWE Rule CWE-682,CWE-758                        */
/* JV-01 Justification : Compiler will distinguish numerous characters, so this is accepted.                          */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE Rule CWE-398, CWE-569                                            */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is accepted. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/
#define MEM_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"
/* Declaration of Internal Function "Mem_59_Renesas_RestoreJobData" */
extern FUNC(void, MEM_PRIVATE_CODE) Mem_59_Renesas_RestoreJobData(Mem_59_Renesas_InstanceIdType LulInstanceId);

/* Declaration of Internal Function "Mem_59_Renesas_ClearBackUpData" */
extern FUNC(void, MEM_PRIVATE_CODE) Mem_59_Renesas_ClearBackUpData(Mem_59_Renesas_InstanceIdType LulInstanceId);

/* Declaration of Internal Function "Mem_59_Renesas_BackupJobData" */
extern FUNC(void, MEM_PRIVATE_CODE) Mem_59_Renesas_BackupJobData(Mem_59_Renesas_InstanceIdType LulInstanceId);

/* Declaration of Internal Function "Mem_59_Renesas_FPSYS_InitFlashControl" */
extern FUNC(Mem_59_Renesas_FcuStatusType, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_InitFlashControl(void);

/* Declaration of Internal Function "Mem_59_Renesas_FPSYS_MainErase". */
extern FUNC(void, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_MainErase(Mem_59_Renesas_InstanceIdType LulInstanceId);

/* Declaration of Internal Function "Mem_59_Renesas_FPSYS_MainWrite" */
extern FUNC(void, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_MainWrite(Mem_59_Renesas_InstanceIdType LulInstanceId);

/* Declaration of Internal Function "Mem_59_Renesas_FPSYS_MainRead" */
extern FUNC(void, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_MainRead(Mem_59_Renesas_InstanceIdType LulInstanceId);

/* Declaration of Internal Function "Mem_59_Renesas_FPSYS_MainBlankCheck" */
extern FUNC(void, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_MainBlankCheck(Mem_59_Renesas_InstanceIdType LulInstanceId);

/* Declaration of Internal Function "Mem_59_Renesas_FPSYS_ProcessCancel" */
extern FUNC(void, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_ProcessCancel(Mem_59_Renesas_InstanceIdType LulInstanceId);

/* Declaration of Internal Function "Mem_59_Renesas_FPSYS_ProcessSuspend" */
extern FUNC(void, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_ProcessSuspend(Mem_59_Renesas_InstanceIdType LulInstanceId);

/* Declaration of Internal Function "Mem_59_Renesas_FPSYS_ProcessResume" */
extern FUNC(void, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_ProcessResume(Mem_59_Renesas_InstanceIdType LulInstanceId);

/* Declaration of Internal Function "Mem_59_Renesas_FPSYS_ProcessJobResult" */
extern FUNC(void, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_ProcessJobResult(
                              Mem_59_Renesas_InstanceIdType LulInstanceId,const Mem_59_Renesas_JobResultType LenResult);

/* Declaration of Internal Function "Mem_59_Renesas_FPSYS_ProcessRead" */
extern Mem_59_Renesas_JobResultType Mem_59_Renesas_FPSYS_ProcessRead(Mem_59_Renesas_InstanceIdType LulInstanceId);

#if (MEM_59_RENESAS_READIMMEDIATE_API == STD_ON)
/* Declaration of Internal Function "Mem_59_Renesas_FPSYS_MainReadImmediate" */
extern FUNC(void, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_MainReadImmediate(Mem_59_Renesas_InstanceIdType LulInstanceId);

/* Declaration of Internal Function "Mem_59_Renesas_FPSYS_ProcessReadImmediate" */
extern Mem_59_Renesas_JobResultType Mem_59_Renesas_FPSYS_ProcessReadImmediate(
                                                                         Mem_59_Renesas_InstanceIdType LulInstanceId);
#endif
/* Declaration of Internal Function "Mem_59_Renesas_FPSYS_HWResourceInit" */
extern FUNC(Std_ReturnType, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_HWResourceInit(
                                                                           Mem_59_Renesas_InstanceIdType LulInstanceId);

/* Declaration of Internal Function "Mem_59_Renesas_FPSYS_ProcessJob" */
extern FUNC(void, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_ProcessJob(Mem_59_Renesas_InstanceIdType LulInstanceId);

/* Declaration of Internal Function "Mem_59_Renesas_FPSYS_HwSpecificService" */
extern FUNC(Std_ReturnType, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_HwSpecificService(
  Mem_59_Renesas_InstanceIdType LulInstanceId, Mem_59_Renesas_HwServiceIdType LulHwServiceId,
  P2VAR(Mem_59_Renesas_DataType, AUTOMATIC, MEM_APPL_DATA) pDataPtr,                                                    /* PRQA S 3432 # JV-01 */
  P2VAR(Mem_59_Renesas_LengthType, AUTOMATIC, MEM_APPL_DATA) pLengthPtr);                                               /* PRQA S 3432 # JV-01 */
#define MEM_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"
#endif /* MEM_59_RENESAS_CONTROL_H */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
