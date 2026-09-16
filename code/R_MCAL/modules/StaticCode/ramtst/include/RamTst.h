/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = RamTst.h                                                                                            */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2023-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains macros, RamTst type definitions, structure data types                                           */
/* and API function prototypes of RamTst Driver                                                                       */
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
 *  1.4.1:  30/06/2025  : Update SW-VERSION for RH850/U2Bx MCAL Ver22.02.00.001
 *  1.3.1:  31/03/2025  : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E 
 *  1.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 *  1.2.0:  31/12/2024  : Update SW-Version for Ver22.02.00/Ver22.02.00.D U2Bx Final release
 *  1.1.2:  31/10/2024  : Update SW-VERSION to 1.1.2
 *                        As part of QAC 9.5.0 support, following changes are made:
 *                        1. Remove QAC message 1534
 *  1.1.0:  20/02/2024  : Update SW-VERSION to 1.1.0
 *  1.0.2:  28/12/2023  : Update RAMTST_SW_PATCH_VERSION to 2
 *  1.0.1:  17/10/2023  : Update RAMTST_SW_PATCH_VERSION to 1
 *                        Remove Crictical section macro define due to redundant
 *                        Add new precompiler switch #if (RAMTST_DEV_ERROR_DETECT == STD_ON) for DET report
 *                        Remove macro RAMTST_MAINFUNCTION_SVCID due to redundant
 *                        Add QAC message 1534 header, remove unused QAC message header
 *  1.0.0:  23/07/2023  : Update critical section.  
 *                        Remove macro RAMTST_ALG_INVALID,  RAMTST_RWW_DESCEND, RAMTST_LRECCTSTCTL_RESET_VALUE, 
 *                        RAMTST_LRECCCTL_RESET_VALUE, RAMTST_LR0_ERRINT_RESET_VALUE, RAMTST_LR1_ERRINT_RESET_VALUE, 
 *                        RAMTST_CRCECCTSTCTL_RESET_VALUE, RAMTST_CRAECCCTL_RESET_VALUE, RAMTST_CR_ERRINT_RESET_VALUE.
 *                        Remove RamTst_NumBlock, RamTst_Block, RamTst_NumTestedCell, RamTst_GpCellAddress, 
 *                        RamTst_AlgParamsId, RamTst_OverallTestResult, RamTst_ExecutionStatus, 
 *                        RamTst_TestResultBuffer, RamTst_Algorithm
 *                        Change RamTst_59_93_Config to RamTst_Config RamTst_GaaAlgId2CoreIndex 
 *                        RamTst_GaaDefaultAlgParams
 *                        Add RamTst_GaaGlobalAccessPointType RamTst_GaaGetCoreId2Index
 *          16/06/2023  : Remove redundant macro RAMTST_DET_REPORTERROR
 *          19/05/2023  : Initial Version
 */
/**********************************************************************************************************************/
#ifndef RAMTST_H
#define RAMTST_H
/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/**********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE Rule CWE-398, CWE-569                                            */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is accepted. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for Pre-compile options */
#include "RamTst_Cfg.h"
/* Included AUTOSAR standard types */
#include "Std_Types.h"
/* Included for Type declarations */
#include "RamTst_Types.h"
/* Included for Notification declarations */
#include "RamTst_Cbk.h"
#if (RAMTST_DEV_ERROR_DETECT == STD_ON)
/* Included for the declaration of Det_ReportError() */
#include "Det.h"
#endif
/***********************************************************************************************************************
**                                         Critical Section Protection Macros                                         **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
#define RAMTST_VENDOR_ID                              RAMTST_VENDOR_ID_VALUE
#define RAMTST_MODULE_ID                              RAMTST_MODULE_ID_VALUE
#if (RAMTST_DEV_ERROR_DETECT == STD_ON)
#define RAMTST_INSTANCE_ID                            RAMTST_INSTANCE_ID_VALUE
#endif
/* AUTOSAR release version information */
#define RAMTST_AR_R22_11_VERSION                      480
#define RAMTST_AR_RELEASE_MAJOR_VERSION               4U
#define RAMTST_AR_RELEASE_MINOR_VERSION               8U
#define RAMTST_AR_RELEASE_REVISION_VERSION            0U
/* Module Software version information */
#define RAMTST_SW_MAJOR_VERSION                       1U
#define RAMTST_SW_MINOR_VERSION                       4U
#define RAMTST_SW_PATCH_VERSION                       1U
/***********************************************************************************************************************
**                                               API Service Id Macros                                                **
***********************************************************************************************************************/
#if (RAMTST_DEV_ERROR_DETECT == STD_ON)
/* RamTst_Init service ID */
#define RAMTST_INIT_SVCID                             (uint8)(0x00)
/* RamTst_Stop service ID */
#define RAMTST_STOP_SVCID                             (uint8)(0x02)
/* RamTst_Allow service ID */
#define RAMTST_ALLOW_SVCID                            (uint8)(0x03)
/* RamTst_GetExecutionStatus service ID */
#define RAMTST_GET_EXECUTION_STATUS_SVCID             (uint8)(0x04)
/* RamTst_GetTestResult service ID */
#define RAMTST_GET_TEST_RESULT_SVCID                  (uint8)(0x05)
/* RamTst_GetTestResultPerBlock service ID */
#define RAMTST_GET_TEST_RESULT_PER_BLOCK_SVCID        (uint8)(0x06)  
/* RamTst_GetTestAlgorithm service ID */
#define RAMTST_GET_TEST_ALGORITHM_SVCID               (uint8)(0x07)
/* RamTst_ChangeNumberOfTestedCells service ID */
#define RAMTST_CHANGE_NUMBER_OF_TESTED_CELLS_SVCID    (uint8)(0x08)
/* RamTst_GetNumberOfTestedCells service ID */
#define RAMTST_GET_NUMBER_OF_TESTED_CELLS_SVCID       (uint8)(0x09)
/* RamTst_GetVersionInfo service ID */
#define RAMTST_GET_VERSIONINFO_SVCID                  (uint8)(0x0A)
/* RamTst_SelectAlgParams service ID */
#define RAMTST_SELECT_ALGORITHM_PARAMS_SVCID          (uint8)(0x0B)
/* RamTst_DeInit service ID */
#define RAMTST_DEINIT_SVCID                           (uint8)(0x0C)
/* RamTst_Suspend service ID */
#define RAMTST_SUSPEND_SVCID                          (uint8)(0x0D)
/* RamTst_Resume service ID */
#define RAMTST_RESUME_SVCID                           (uint8)(0x0E)
/* RamTst_RunFullTest service ID */
#define RAMTST_RUN_FULL_TEST_SVCID                    (uint8)(0x10)
/* RamTst_RunPartialTest service ID */
#define RAMTST_RUN_PARTIAL_TEST_SVCID                 (uint8)(0x11)
/* RamTst_GetAlgParams service ID */
#define RAMTST_GET_ALGORITHM_PARAMS_SVCID             (uint8)(0x12)

/***********************************************************************************************************************
**                                                  DET Error Codes                                                   **
***********************************************************************************************************************/
/* API called with irrelevant execution status */
#define RAMTST_E_STATUS_FAILURE                       (uint8)0x01
/* API called with parameter out of specified range */
#define RAMTST_E_OUT_OF_RANGE                         (uint8)0x02
/* API called without module initialization */
#define RAMTST_E_UNINIT                               (uint8)0x03
/* API called with null pointer */
#define RAMTST_E_PARAM_POINTER                        (uint8)0x04
/* DET Error - Call in invalid core */
#define RAMTST_E_INVALID_CORE                         (uint8)0xF1

#endif /* #if (RAMTST_DEV_ERROR_DETECT == STD_ON) */
/***********************************************************************************************************************
**                                                  Internal Defines                                                  **
***********************************************************************************************************************/
/* Macro for finding the Mask */
#define RAMTST_MASK_BITX(X)                           ((0x0001UL) << (X)) 
/* Macro for inverting a particular bit */
#define RAMTST_INVERT_BITX(Y, X, TYPE)                ((Y) = (Y) ^ (TYPE)RAMTST_MASK_BITX(X))
/*  Number of test runs */
#define RAMTST_ABRAHAM_TESTRUN                        (uint8)0x09
/*  First test run in Abraham test */
#define RAMTST_RW1_ASCEND                             (uint8)0x00
/* Second test run in Abraham test */
#define RAMTST_RW0_ASCEND                             (uint8)0x01
/* Third test run in Abraham test */
#define RAMTST_RW1_DESCEND                            (uint8)0x02
/* Fourth test run in Abraham test */
#define RAMTST_RW0_DESCEND                            (uint8)0x03
/* Fifth test run in Abraham test */
#define RAMTST_RWW_ASCEND                             (uint8)0x04
/* Sixth test run in Abraham test */
#define RAMTST_WRW_DESCEND                            (uint8)0x05
/* Seventh test run in Abraham test */
#define RAMTST_W_ASCEND                               (uint8)0x06
/* Eighth test run in Abraham test */
#define RAMTST_WRW_ASCEND                             (uint8)0x07
/* Invalid core */
#define RAMTST_INVALID_CORE                           (uint8)0xFF

/***********************************************************************************************************************
**                                                 Global Variables                                                   **
***********************************************************************************************************************/

#define RAMTST_START_SEC_CONST_32
#include "RamTst_MemMap.h"

extern const RamTst_GlobalAccessPointType RamTst_GaaGlobalAccPoint[RAMTST_CONFIGURED_CORE_NUM];

#define RAMTST_STOP_SEC_CONST_32
#include "RamTst_MemMap.h"

#define RAMTST_START_SEC_CONST_8
#include "RamTst_MemMap.h"

#if (RAMTST_MULTI_CORE_SUPPORT == STD_ON)

extern const uint8 RamTst_GaaGetCoreId2Index[RAMTST_SUPPORTED_CORE_MAX_NUM];  

extern const uint8 RamTst_GaaAlgId2CoreIndex[RAMTST_NO_OF_ALGORITHM];

#endif

extern const uint8 RamTst_GaaDefaultAlgParams[RAMTST_CONFIGURED_CORE_NUM];

#define RAMTST_STOP_SEC_CONST_8
#include "RamTst_MemMap.h"
/***********************************************************************************************************************
**                                              API FUNCTION PROTOTYPES                                               **
***********************************************************************************************************************/
/* Start of RamTst Section Code   */
#define RAMTST_START_SEC_PUBLIC_CODE
#include "RamTst_MemMap.h"
extern FUNC(void, RAMTST_PUBLIC_CODE) RamTst_Init(P2CONST(RamTst_ConfigType, AUTOMATIC, RAMTST_CONFIG_CONST) ConfigPtr);
extern FUNC(void, RAMTST_PUBLIC_CODE) RamTst_DeInit(void);
#if (RAMTST_STOP_API == STD_ON)
extern FUNC(void, RAMTST_PUBLIC_CODE) RamTst_Stop(void);
#endif
#if (RAMTST_ALLOW_API == STD_ON)
extern FUNC(void, RAMTST_PUBLIC_CODE) RamTst_Allow(void);
#endif
#if (RAMTST_SUSPEND_API == STD_ON)
extern FUNC(void, RAMTST_PUBLIC_CODE) RamTst_Suspend(void);
#endif
#if (RAMTST_RESUME_API == STD_ON)
extern FUNC(void, RAMTST_PUBLIC_CODE) RamTst_Resume(void);
#endif
#if (RAMTST_GET_EXECUTION_STATUS_API == STD_ON)
extern FUNC(RamTst_ExecutionStatusType, RAMTST_PUBLIC_CODE) RamTst_GetExecutionStatus(void);
#endif
#if (RAMTST_GET_TEST_RESULT_API == STD_ON)
extern FUNC(RamTst_TestResultType, RAMTST_PUBLIC_CODE) RamTst_GetTestResult(void);
#endif
#if (RAMTST_GET_TEST_RESULT_PER_BLOCK_API == STD_ON)
extern FUNC(RamTst_TestResultType, RAMTST_PUBLIC_CODE)
    RamTst_GetTestResultPerBlock(VAR(RamTst_NumberOfBlocksType, AUTOMATIC) BlockID);
#endif
#if (RAMTST_GET_ALG_PARAMS_API == STD_ON)
extern FUNC(RamTst_AlgParamsIdType, RAMTST_PUBLIC_CODE) RamTst_GetAlgParams(void);
#endif
#if (RAMTST_GET_TEST_ALGORITHM_API == STD_ON)
extern FUNC(RamTst_AlgorithmType, RAMTST_PUBLIC_CODE) RamTst_GetTestAlgorithm(void);
#endif
#if (RAMTST_GET_NUMBER_OF_TESTED_CELLS_API == STD_ON)
extern FUNC(RamTst_NumberOfTestedCellsType, RAMTST_PUBLIC_CODE) RamTst_GetNumberOfTestedCells(void);
#endif
#if (RAMTST_SELECT_ALG_PARAMS_API == STD_ON)
extern FUNC(void, RAMTST_PUBLIC_CODE) RamTst_SelectAlgParams(VAR(RamTst_AlgParamsIdType, AUTOMATIC) NewAlgParamsId);
#endif
#if (RAMTST_CHANGE_NUMBER_OF_TESTED_CELLS_API == STD_ON)
extern FUNC(void, RAMTST_PUBLIC_CODE)
    RamTst_ChangeNumberOfTestedCells(VAR(RamTst_NumberOfTestedCellsType, AUTOMATIC) NewNumberOfTestedCells);
#endif
#if (RAMTST_RUN_FULL_TEST_API == STD_ON)
extern FUNC(void, RAMTST_PUBLIC_CODE) RamTst_RunFullTest(void);
#endif
#if (RAMTST_RUN_PARTIAL_TEST_API == STD_ON)
extern FUNC(void, RAMTST_PUBLIC_CODE) RamTst_RunPartialTest(VAR(RamTst_NumberOfBlocksType, AUTOMATIC) BlockId);
#endif
#if (RAMTST_GET_VERSION_INFO_API == STD_ON)
extern FUNC(void, RAMTST_PUBLIC_CODE)
    RamTst_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, RAMTST_APPL_DATA) VersionInfo);                         /* PRQA S 3432 # JV-01 */
#endif
/** End of RamTst Section Code  */
#define RAMTST_STOP_SEC_PUBLIC_CODE
#include "RamTst_MemMap.h"
/***********************************************************************************************************************
**                                                External variables                                                  **
***********************************************************************************************************************/
#define RAMTST_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "RamTst_MemMap.h"
/* RamTst Configuration array */
extern CONST(RamTst_ConfigType, RAMTST_CONST) RamTst_Config[RAMTST_ONE];
#define RAMTST_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "RamTst_MemMap.h"
#endif 
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
