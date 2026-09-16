/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas R22-11 X2x MCAL Components                                                          */
/* Module       = MemAcc.h                                                                                            */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2024-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains macros, MEMACC type definitions, structure data types and API function prototypes               */
/* of MEMACC Driver                                                                                                   */
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
 * 1.1.1:  30/06/2025:  Remove SW-VERSION in file header and Update MEMACC_SW_PATCH_VERSION to 1
 * 1.1.0:  30/06/2025:  Update SW-VERSION for RH850/Ver22.01.00 (D) U2Ax release
 * 1.0.3:  25/04/2025:  Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03
 * 1.0.2:  31/03/2025:  Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02
 * 1.0.1:  28/02/2025:  Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 1.0.0:  31/12/2024:  Update to support macro MEMACC_COMPARE_API for declaration of API MemAcc_Comapre
 * 0.0.2:  31/10/2024:  Updated Version.
 * 0.0.1:  30/08/2024:  Initial Version.
 */
/**********************************************************************************************************************/
#ifndef MEMACC_H
#define MEMACC_H
/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* To publish the standard types */
#include "Std_Types.h"
/* Included for pre-compile time parameters */
#include "MemAcc_Cfg.h"
/* To publish the type MemAcc_ConfigType */
#include "MemAcc_Types.h"
#include "MemAcc_GeneralTypes.h"
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* Version autosar */
#define MEMACC_AR_R22_11_VERSION            480
/* Version identification */
#define MEMACC_VENDOR_ID                    59U
#define MEMACC_MODULE_ID                    41U
#define MEMACC_INSTANCE_ID                  MEMACC_INSTANCE_ID_VALUE

#if (MEMACC_AR_VERSION == MEMACC_AR_R22_11_VERSION)
/* AUTOSAR release version information */
#define MEMACC_AR_RELEASE_MAJOR_VERSION     4U
#define MEMACC_AR_RELEASE_MINOR_VERSION     8U
#define MEMACC_AR_RELEASE_REVISION_VERSION  0U
#endif
/* Module Software version information */
#define MEMACC_SW_MAJOR_VERSION             1U
#define MEMACC_SW_MINOR_VERSION             1U
#define MEMACC_SW_PATCH_VERSION             1U

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE Rule CWE-398, CWE-569                                            */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is accepted. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3684)    : Array declared with unknown size.                                                            */
/* Rule                : MISRA C:2012 Rule-8.11, CERTCCM ARR02                                                        */
/* JV-01 Justification : Arrays used are verified in the file which are only declarations and size is configuration   */
/*                       dependent.                                                                                   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:4643)    : The identifier '%1s' could conflict in the future with the name of a function in '<%2s>'.    */
/* Rule                : CERTCCM DCL37, CWE-398, CWE-569                                                              */
/* JV-01 Justification : Arrays used are verified in the file which are only declarations and size is configuration   */
/*                       dependent.                                                                                   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                               API Service Id Macros                                                **
***********************************************************************************************************************/
/* Service Id of MemAcc_Init */
#define MEMACC_INIT_SID                  ((uint8)0x01U)

/* Service Id of MemAcc_GetVersionInfo */
#define MEMACC_GET_VERSION_INFO_SID      ((uint8)0x02U)

/* Service Id of MemAcc_MainFunction */
#define MEMACC_MAINFUNCTION_SID          ((uint8)0x03U)

/* Service Id of MemAcc_Cancel */
#define MEMACC_CANCEL_SID                ((uint8)0x04U)

/* Service Id of MemAcc_GetJobResult */
#define MEMACC_GET_JOB_RESULT_SID        ((uint8)0x05U)

/* Service Id of MemAcc_GetMemoryInfo */
#define MEMACC_GET_MEMORY_INFO_SID       ((uint8)0x06U)

/* Service Id of MemAcc_GetProcessedLength */
#define MEMACC_GET_PROCESSED_LENGHT_SID  ((uint8)0x07U)

/* Service Id of MemAcc_GetJobInfo */
#define MEMACC_GET_JOB_INFO_SID          ((uint8)0x08U)

/* Service Id of MemAcc_Read */
#define MEMACC_READ_SID                  ((uint8)0x09U)

/* Service Id of MemAcc_Write */
#define MEMACC_WRITE_SID                 ((uint8)0x0AU)

/* Service Id of MemAcc_Erase */
#define MEMACC_ERASE_SID                 ((uint8)0x0BU)

/* Service Id of MemAcc_Compare */
#define MEMACC_COMPARE_SID               ((uint8)0x0CU)

/* Service Id of MemAcc_BlankCheck */
#define MEMACC_BLANK_CHECK_SID           ((uint8)0x0DU)

/* Service Id of MemAcc_HwSpecificService */
#define MEMACC_HW_SPECIFIC_SERVICE_SID   ((uint8)0x0EU)

/* Service Id of MemAcc_GetJobStatus */
#define MEMACC_GET_JOB_STATUS_SID        ((uint8)0x10U)

/* Service Id of MemAcc_RequestLock */
#define MEMACC_REQUEST_LOCK_SID          ((uint8)0x11U)

/* Service Id of MemAcc_ReleaseLock */
#define MEMACC_RELEASE_LOCK_SID          ((uint8)0x11U)

/* Service Id of MemAcc_DeInit */
#define MEMACC_DEINIT_SID                ((uint8)0x13U)

/* Service Id of MemAcc_ActivateMem */
#define MEMACC_ACTIVATE_MEM_SID          ((uint8)0x14U)

/* Service Id of MemAcc_DeactivateMem */
#define MEMACC_DEACTIVATE_MEM_SID        ((uint8)0x15U)

/***********************************************************************************************************************
**                                                  DET Error Codes                                                   **
***********************************************************************************************************************/

/* API service called without module initialization. */
#define MEMACC_E_UNINIT                   ((uint8)0x01U)

/* API service called with NULL pointer argument. */
#define MEMACC_E_PARAM_POINTER            ((uint8)0x02U)

/* API service called with wrong address area ID. */
#define MEMACC_E_PARAM_ADDRESS_AREA_ID    ((uint8)0x03U)

/* API service called with address and length not belonging to the passed address area ID. */
#define MEMACC_E_PARAM_ADDRESS_LENGTH     ((uint8)0x04U)

/* API service called with a hardware ID not belonging to the passed address area ID. */
#define MEMACC_E_PARAM_HW_ID              ((uint8)0x05U)

/* API service called for an address area ID with a pending job request. */
#define MEMACC_E_BUSY                     ((uint8)0x06U)

/* Dynamic MEM driver activation failed due to inconsistent MEM driver binary. */
#define MEMACC_E_MEM_INIT_FAILED          ((uint8)0x07U)

/* API service used when the module has already been initialized */
#define MEMACC_E_ALREADY_INITIALIZED      ((uint8)0x0BU)

/* API service called with wrong database address */
#define MEMACC_E_INVALID_DATABASE         ((uint8)0xEFU)

#define MEMACC_RENESAS_DRIVER_ID          (0UL)
/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/
#define MEMACC_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "MemAcc_MemMap.h"
extern CONST(MemAcc_ConfigType, MEMACC_CONFIG_DATA) MemAcc_GstConfiguration[];                                          /* PRQA S 3684 # JV-01 */
#define MEMACC_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "MemAcc_MemMap.h"
/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/
#define MEMACC_START_SEC_PUBLIC_CODE
#include "MemAcc_MemMap.h"

/* Declaration of API MemAcc_Init */
extern FUNC(void, MEMACC_PUBLIC_CODE) MemAcc_Init(P2CONST(MemAcc_ConfigType, AUTOMATIC, MEMACC_APPL_CONST) configPtr);

/* Declaration of API MemAcc_DeInit */
extern FUNC(void, MEMACC_PUBLIC_CODE) MemAcc_DeInit(void);

/* Declaration of API MemAcc_GetVersionInfo */
extern FUNC(void, MEMACC_PUBLIC_CODE) MemAcc_GetVersionInfo(P2VAR(Std_VersionInfoType,                                  /* PRQA S 3432 # JV-01 */
AUTOMATIC, MEMACC_APPL_DATA) versionInfoPtr); 

/* Declaration of API MemAcc_GetProcessedLength */
extern FUNC(MemAcc_LengthType, MEMACC_PUBLIC_CODE) MemAcc_GetProcessedLength(MemAcc_AddressType addressAreaId);

/* Declaration of API MemAcc_GetJobResult */
extern FUNC(MemAcc_JobResultType, MEMACC_PUBLIC_CODE) MemAcc_GetJobResult(MemAcc_AddressAreaIdType addressAreaId);

/* Declaration of API MemAcc_GetJobStatus */
extern FUNC(MemAcc_JobStatusType, MEMACC_PUBLIC_CODE) MemAcc_GetJobStatus(MemAcc_AddressAreaIdType addressAreaId);

/* Declaration of API MemAcc_MainFunction */
extern FUNC(void, MEMACC_PUBLIC_CODE) MemAcc_MainFunction(void);

/* Declaration of API MemAcc_Read */
extern FUNC(Std_ReturnType, MEMACC_PUBLIC_CODE) MemAcc_Read(
  MemAcc_AddressAreaIdType addressAreaId,
  MemAcc_AddressType sourceAddress,
  P2VAR(MemAcc_DataType, AUTOMATIC, MEMACC_APPL_DATA) destinationDataPtr,                                               /* PRQA S 3432 # JV-01 */
  MemAcc_LengthType length);

/* Declaration of API MemAcc_GetMemoryInfo */
extern FUNC(Std_ReturnType, MEMACC_PUBLIC_CODE) MemAcc_GetMemoryInfo (
  MemAcc_AddressAreaIdType addressAreaId,
  MemAcc_AddressType address,
  P2VAR(MemAcc_MemoryInfoType, AUTOMATIC, MEMACC_APPL_DATA) memoryInfoPtr);                                             /* PRQA S 3432, 4643 # JV-01, JV-01 */

/* Declaration of API MemAcc_GetJobInfo */
extern FUNC(void, MEMACC_PUBLIC_CODE) MemAcc_GetJobInfo (
  MemAcc_AddressAreaIdType addressAreaId,
  P2VAR(MemAcc_JobInfoType, AUTOMATIC, MEMACC_APPL_DATA) jobInfoPtr);                                                   /* PRQA S 3432 # JV-01 */

/* Declaration of API MemAcc_Erase */
extern FUNC(Std_ReturnType, MEMACC_PUBLIC_CODE) MemAcc_Erase (
  MemAcc_AddressAreaIdType addressAreaId,
  MemAcc_AddressType targetAddress,
  MemAcc_LengthType length);

/* Declaration of API MemAcc_Write */
extern FUNC(Std_ReturnType, MEMACC_PUBLIC_CODE) MemAcc_Write (
  MemAcc_AddressAreaIdType addressAreaId,
  MemAcc_AddressType targetAddress,
  P2CONST(MemAcc_DataType, AUTOMATIC, MEMACC_APPL_CONST) sourceDataPtr,
  MemAcc_LengthType length);

/* Declaration of API MemAcc_Comapre */
#if (MEMACC_COMPARE_API == STD_ON)
extern FUNC(Std_ReturnType, MEMACC_PUBLIC_CODE) MemAcc_Compare (
  MemAcc_AddressAreaIdType addressAreaId,
  MemAcc_AddressType sourceAddress,
  P2CONST(MemAcc_DataType, AUTOMATIC, MEMACC_APPL_CONST) dataPtr,
  MemAcc_LengthType length);
#endif

/* Declaration of API MemAcc_Blank-Check */
extern FUNC(Std_ReturnType, MEMACC_PUBLIC_CODE) MemAcc_BlankCheck (
  MemAcc_AddressAreaIdType addressAreaId,
  MemAcc_AddressType targetAddress,
  MemAcc_LengthType length);

/* Declaration of API MemAcc_Cancel */
extern void MemAcc_Cancel(MemAcc_AddressAreaIdType addressAreaId);

/* Declaration of API MemAcc_RequestLock */
extern FUNC(Std_ReturnType, MEMACC_PUBLIC_CODE) MemAcc_RequestLock (
  MemAcc_AddressAreaIdType addressAreaId,
  MemAcc_AddressType address,
  MemAcc_AddressType length,
  void* lockNotificationFctPtr);

/* Declaration of API MemAcc_ReleaseLock */
extern FUNC(Std_ReturnType, MEMACC_PUBLIC_CODE) MemAcc_ReleaseLock (
  MemAcc_AddressAreaIdType addressAreaId,
  MemAcc_AddressType address,
  MemAcc_AddressType length);

/* Declaration of API MemAcc_DeactivateMem */
extern FUNC(Std_ReturnType, MEMACC_PUBLIC_CODE) MemAcc_DeactivateMem (
  MemAcc_HwIdType hwId,
  MemAcc_AddressType headerAddress);

/* Declaration of API MemAcc_ActivateMem */
extern FUNC(Std_ReturnType, MEMACC_PUBLIC_CODE) MemAcc_ActivateMem (
  MemAcc_AddressType headerAddress,
  MemAcc_HwIdType hwId);

/* Declaration of API MemAcc_HwSpecificService */
extern FUNC(Std_ReturnType, MEMACC_PUBLIC_CODE) MemAcc_HwSpecificService(
  MemAcc_AddressAreaIdType addressAreaId,
  MemAcc_HwIdType hwId,
  MemAcc_MemHwServiceIdType hwServiceId,
  MemAcc_DataType* dataPtr,
  MemAcc_LengthType* lengthPtr);

#define MEMACC_STOP_SEC_PUBLIC_CODE
#include "MemAcc_MemMap.h"

#endif /* MEMACC_H */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
