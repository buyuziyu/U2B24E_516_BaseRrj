/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Mem_59_Renesas_FPSYS_LLDriver.h                                                                     */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2024-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains API Declarations of low level handling                                                          */
/* functions                                                                                                          */
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
 * 0.0.2:  31/10/2024  : Support commonize
 * 0.0.1:  30/08/2024  : Initial Version
 */
/**********************************************************************************************************************/

#ifndef MEM_59_RENESAS_LLDRIVER_H
#define MEM_59_RENESAS_LLDRIVER_H
/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
#include "Mem_59_Renesas.h"
#include "SchM_Mem_59_Renesas.h"
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR Release version information */
#define MEM_59_RENESAS_LLDRIVER_AR_RELEASE_MAJOR_VERSION    MEM_59_RENESAS_AR_RELEASE_MAJOR_VERSION
#define MEM_59_RENESAS_LLDRIVER_AR_RELEASE_MINOR_VERSION    MEM_59_RENESAS_AR_RELEASE_MINOR_VERSION
#define MEM_59_RENESAS_LLDRIVER_AR_RELEASE_REVISION_VERSION MEM_59_RENESAS_AR_RELEASE_REVISION_VERSION
/* Module Software version information */
#define MEM_59_RENESAS_LLDRIVER_SW_MAJOR_VERSION            MEM_59_RENESAS_SW_MAJOR_VERSION
#define MEM_59_RENESAS_LLDRIVER_SW_MINOR_VERSION            MEM_59_RENESAS_SW_MINOR_VERSION

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
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                            Extern Function Declarations                                            **
***********************************************************************************************************************/
#define MEM_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"
/* Declaration of Internal Function "Mem_59_Renesas_FPSYS_FcuPreCheck". */
extern FUNC(Mem_59_Renesas_FcuStatusType, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_FcuPreCheck(void);

/* Declaration of Internal Function "Mem_59_Renesas_FPSYS_FcuSwitchMode". */
extern FUNC(Mem_59_Renesas_FcuStatusType, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_FcuSwitchMode(
                                                                          CONST(T_en_FACIMode, MEM_APPL_CONST) LenMode);

/* Declaration of Internal Function "Mem_59_Renesas_FPSYS_FcuCheckJobStatus". */
extern FUNC(Mem_59_Renesas_FcuStatusType, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_FcuCheckJobStatus(void);

/* Declaration of Internal Function "Mem_59_Renesas_FPSYS_FcuCheckBCJobStatus". */
extern FUNC(Mem_59_Renesas_FcuStatusType, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_FcuCheckBCJobStatus(void);

/* Declaration of Internal Function "Mem_59_Renesas_FPSYS_FcuResetErrorBits". */
extern FUNC(Mem_59_Renesas_FcuStatusType, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_FcuResetErrorBits(
                                                                           Mem_59_Renesas_InstanceIdType LulInstanceId);

/* Declaration of Internal Function "Mem_59_Renesas_FPSYS_FcuCheckSequencerStatus". */
extern FUNC(Mem_59_Renesas_FcuStatusType, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_FcuCheckSequencerStatus(void);

/* Declaration of Internal Function "Mem_59_Renesas_FPSYS_FcuReset". */
extern FUNC(Mem_59_Renesas_FcuStatusType, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_FcuReset(void);

/* Declaration of Internal Function "Mem_59_Renesas_FPSYS_GetFACINumber". */
extern FUNC(void, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_GetFACINumber(const uint32 LulStartAddr, 
                                                                     const Mem_59_Renesas_InstanceIdType LulInstanceId);

/* Declaration of Internal Function "Mem_59_Renesas_FPSYS_PreFcuInitCheck". */
extern FUNC(Mem_59_Renesas_FcuStatusType, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_PreFcuInitCheck(void);

/* Declaration of Internal Function "Mem_59_Renesas_FPSYS_InitFcu". */
extern FUNC(Mem_59_Renesas_FcuStatusType, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_InitFcu(void);

/* Declaration of Internal Function "Mem_59_Renesas_FPSYS_ProcessEraseJob" */
extern FUNC(Std_ReturnType, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_ProcessEraseJob(
                                                                           Mem_59_Renesas_InstanceIdType LulInstanceId);

#if (MEM_59_RENESAS_DATA_FLASH_CONFIGURED == STD_ON)
/* Declaration of Internal Function "Mem_59_Renesas_FPSYS_ProcessBlankCheckDFJob" */
extern FUNC(Std_ReturnType, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_ProcessBlankCheckDFJob(
                                                                           Mem_59_Renesas_InstanceIdType LulInstanceId);
#endif

#if (MEM_59_RENESAS_CODE_FLASH_CONFIGURED == STD_ON)
/* Declaration of Internal Function "Mem_59_Renesas_FPSYS_BlankCheckCFRequest" */
extern FUNC(Mem_59_Renesas_FcuStatusType, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_BlankCheckCFRequest(
                                                                           Mem_59_Renesas_InstanceIdType LulInstanceId);
#endif

#if (MEM_59_RENESAS_DATA_FLASH_CONFIGURED == STD_ON)
/* Declaration of Internal Function "Mem_59_Renesas_FPSYS_PerformReadDFCheckECC" */
extern FUNC(Mem_59_Renesas_FcuStatusType, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_PerformReadDFCheckECC(
  Mem_59_Renesas_InstanceIdType LulInstanceId, const uint32 LulSrcAddr, const uint32 LulDestAddr);
#endif

#if (MEM_59_RENESAS_CODE_FLASH_CONFIGURED == STD_ON)
/* Declaration of Internal Function "Mem_59_Renesas_FPSYS_PerformReadCFCheckECC" */
extern FUNC(Mem_59_Renesas_FcuStatusType, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_PerformReadCFCheckECC(
  Mem_59_Renesas_InstanceIdType LulInstanceId, const uint32 LulSrcAddr, const uint32 LulDestAddr);
#endif

#if (MEM_59_RENESAS_FHVE_REGS == MEM_59_RENESAS_SUPPORTED)
/* Declaration of Internal Function "Mem_59_Renesas_FPSYS_SetFHVE" */
extern FUNC(void, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_SetFHVE(const uint32 Lulvalue);
#endif /* END of #if (MEM_59_RENESAS_FHVE_REGS == MEM_59_RENESAS_SUPPORTED) */

#if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
/* Declaration of Internal Function "Mem_59_Renesas_FPSYS_SuspendPreCheck". */
extern FUNC(Std_ReturnType, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_SuspendPreCheck(
  Mem_59_Renesas_InstanceIdType LulInstanceId, const uint32 LulJobStartAddress,
  const uint32 LulJobEndAddress, const Mem_59_Renesas_CommandType LenGenCommand);
#endif

#if (MEM_59_RENESAS_DATA_FLASH_CONFIGURED == STD_ON)
/* Declaration of Internal Function "Mem_59_Renesas_FPSYS_SetDFEccErrInt" */
extern FUNC(void, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_SetDFEccErrInt(const uint8 LucSetValue);
#endif

#if (MEM_59_RENESAS_CODE_FLASH_CONFIGURED == STD_ON)
/* Declaration of Internal Function "Mem_59_Renesas_FPSYS_SetCFEccErrInt" */
extern FUNC(void, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_SetCFEccErrInt(const uint8 LucSetValue);
#endif

/* Declaration of Internal Function "Mem_59_Renesas_FPSYS_SuspendHwOperation". */
extern FUNC(Std_ReturnType, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_SuspendHwOperation(
                                                                           Mem_59_Renesas_InstanceIdType LulInstanceId);

/* Declaration of Internal Function "Mem_59_Renesas_FPSYS_FcuSuspendRequest". */
extern FUNC(Mem_59_Renesas_FcuStatusType, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_FcuSuspendRequest(void);

/* Declaration of Internal Function "Mem_59_Renesas_FPSYS_ResumeHwOperation". */
extern FUNC(Std_ReturnType, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_ResumeHwOperation(
                                                                           Mem_59_Renesas_InstanceIdType LulInstanceId);

/* Declaration of Internal Function "Mem_59_Renesas_FPSYS_FcuResumeRequest". */
extern FUNC(Mem_59_Renesas_FcuStatusType, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_FcuResumeRequest(void);

/* Declaration of Internal Function "Mem_59_Renesas_FPSYS_ReadOptionByteService" */
extern FUNC(void, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_ReadOptionByteService(
        Mem_59_Renesas_InstanceIdType LulInstanceId, P2VAR(Mem_59_Renesas_DataType, AUTOMATIC, MEM_APPL_DATA) dataPtr); /* PRQA S 3432 # JV-01 */

/* Declaration of Internal Function "Mem_59_Renesas_FPSYS_PerformBlankCheckForReadOp" */
extern Mem_59_Renesas_FcuStatusType Mem_59_Renesas_FPSYS_PerformBlankCheckForReadOp(
  Mem_59_Renesas_InstanceIdType LulInstanceId, const uint32 LulStartAddr);

/* Declaration of Internal Function "Mem_59_Renesas_InitiateWriteJob" */
extern Std_ReturnType Mem_59_Renesas_FPSYS_ProcessWriteJob(Mem_59_Renesas_InstanceIdType LulInstanceId);
#define MEM_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"
/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/

#endif /* MEM_59_RENESAS_LLDRIVER_H */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
