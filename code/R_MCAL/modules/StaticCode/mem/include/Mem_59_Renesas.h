/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Mem_59_Renesas.h                                                                                    */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2024-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains macros, MEM type definitions, structure data types and API function prototypes of MEM Driver    */
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
 * 1.1.1:  30/06/2025   : Update MEM_59_RENESAS_SW_PATCH_VERSION
 * 1.1.0:  30/06/2025   : Update SW-VERSION for RH850/Ver22.01.00(D) U2Ax release
 *                        Support parameter on/off for Mem_59_Renesas_ReadImmediate API
 * 1.0.3:  25/04/2025   : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 Release
 *                        Add global array Mem_59_Renesas_GaaCodeFlash and Mem_59_Renesas_GaaDataFlash
 * 1.0.2:  31/03/2025   : Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02 Release
 *                        Add array Mem_59_Renesas_GaaDataFlash and Mem_59_Renesas_GaaCodeFlash
 * 1.0.1:  28/02/2025   : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 1.0.0:  31/12/2024   : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 *                        As part of ARDAACL-51152, add Error ID MEM_59_RENESAS_E_PARAM_INPUT.
 * 0.0.2:  31/10/2024   : As part of ARDAACJ-621, support downgrade from version AR23-11 to AR22-11.
 *                        Change name from Mem_AddressType to Mem_59_Renesas_AddressType.
 *                        Support commonize source code.
 * 0.0.1:  30/08/2024   : Initial Version
 */
/**********************************************************************************************************************/
#ifndef MEM_59_RENESAS_H
#define MEM_59_RENESAS_H
/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* To publish the standard types */
#include "Std_Types.h"
/* Included for pre-compile time parameters */
#include "Mem_59_Renesas_Cfg.h"
/* To publish the type Mem_59_Renesas_ConfigType */
#include "Mem_59_Renesas_Types.h"
#include "r_rfd.h"
#include "MemAcc_GeneralTypes.h"
#include "Mem_59_Renesas_Cbk.h"
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* Version autosar */
#define MEM_59_RENESAS_AR_R22_11_VERSION 480
/* Version identification */
#define MEM_59_RENESAS_VENDOR_ID      59U
#define MEM_59_RENESAS_MODULE_ID      91U
#define MEM_59_RENESAS_INSTANCE_ID    MEM_59_RENESAS_INSTANCE_ID_VALUE

#if (MEM_59_RENESAS_AR_VERSION == MEM_59_RENESAS_AR_R22_11_VERSION)
/* AUTOSAR release version information */
#define MEM_59_RENESAS_AR_RELEASE_MAJOR_VERSION    4U
#define MEM_59_RENESAS_AR_RELEASE_MINOR_VERSION    8U
#define MEM_59_RENESAS_AR_RELEASE_REVISION_VERSION 0U
#endif
/* Module Software version information */
#define MEM_59_RENESAS_SW_MAJOR_VERSION          1U
#define MEM_59_RENESAS_SW_MINOR_VERSION          1U
#define MEM_59_RENESAS_SW_PATCH_VERSION          1U

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

/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                               API Service Id Macros                                                **
***********************************************************************************************************************/
/* Service Id of Mem_59_Renesas_Init */
#define MEM_59_RENESAS_INIT_SID                  ((uint8)0x01U)
/* Service Id of Mem_59_Renesas_GetVersionInfo */
#define MEM_59_RENESAS_GET_VERSION_INFO_SID      ((uint8)0x02U)
/* Service Id of Mem_59_Renesas_MainFunction */
#define MEM_59_RENESAS_MAINFUNCTION_SID          ((uint8)0x03U)
/* Service Id of Mem_59_Renesas_GetJobResult */
#define MEM_59_RENESAS_GET_JOB_RESULT_SID        ((uint8)0x04U)
/* Service Id of Mem_59_Renesas_Read */
#define MEM_59_RENESAS_READ_SID                  ((uint8)0x05U)
/* Service Id of Mem_59_Renesas_Write */
#define MEM_59_RENESAS_WRITE_SID                 ((uint8)0x06U)
/* Service Id of Mem_59_Renesas_Erase */
#define MEM_59_RENESAS_ERASE_SID                 ((uint8)0x07U)
/* Service Id of Mem_59_Renesas_PropagateError */
#define MEM_59_RENESAS_PROPAGATE_ERROR_SID       ((uint8)0x08U)
/* Service Id of Mem_59_Renesas_BlankCheck */
#define MEM_59_RENESAS_BLANK_CHECK_SID           ((uint8)0x09U)
/* Service Id of Mem_59_Renesas_HwSpecificService */
#define MEM_59_RENESAS_HW_SPECIFIC_SERVICE_SID   ((uint8)0x0AU)
/* Service Id of Mem_59_Renesas_DeInit */
#define MEM_59_RENESAS_DEINIT_SID                ((uint8)0x0BU)
/* Service Id of Mem_59_Renesas_Suspend */
#define MEM_59_RENESAS_SUSPEND_SID               ((uint8)0x0CU)
/* Service Id of Mem_59_Renesas_Resume */
#define MEM_59_RENESAS_RESUME_SID                ((uint8)0x0DU)
/* Service Id of Mem_59_Renesas_ReadImmediate */
#define MEM_59_RENESAS_READIMMEDIATE_SID         ((uint8)0x0EU)
/***********************************************************************************************************************
**                                                  DET Error Codes                                                   **
***********************************************************************************************************************/

/* API service is used without driver initialization */
#define MEM_59_RENESAS_E_UNINIT                  ((uint8)0x01U)

/* A null pointer passed to the APIs */
#define MEM_59_RENESAS_E_PARAM_POINTER           ((uint8)0x02U)

/* A wrong address passed to the APIs */
#define MEM_59_RENESAS_E_PARAM_ADDRESS           ((uint8)0x03U)

/* A wrong length of the address passed to the APIs */
#define MEM_59_RENESAS_E_PARAM_LENGTH            ((uint8)0x04U)

/* A invalid driver instance ID passed to the APIs */
#define MEM_59_RENESAS_E_PARAM_INSTANCE_ID       ((uint8)0x05U)

/* API service used while a job request is still in progress */
#define MEM_59_RENESAS_E_JOB_PENDING             ((uint8)0x06U)

/* A wrong input passed to the APIs */
#define MEM_59_RENESAS_E_PARAM_INPUT             ((uint8)0x07U)

/* API service used when the module has already been initialized */
#define MEM_59_RENESAS_E_ALREADY_INITIALIZED     ((uint8)0x0BU)
/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/
typedef MemAcc_AddressType Mem_59_Renesas_AddressType;
/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/
#define MEM_59_RENESAS_START_SEC_PUBLIC_CODE
#include "Mem_59_Renesas_MemMap.h"
/* Declaration of API "Mem_59_Renesas_Init" */
extern FUNC(void, MEM_PUBLIC_CODE) Mem_59_Renesas_Init(
                                               P2CONST(Mem_59_Renesas_ConfigType, AUTOMATIC, MEM_APPL_CONST) configPtr);

/* Declaration of API "Mem_59_Renesas_DeInit" */
extern FUNC(void, MEM_PUBLIC_CODE) Mem_59_Renesas_DeInit(void);

/* Declaration of API "Mem_59_Renesas_59_Renesas_DeInit" */
extern FUNC(void, MEM_PUBLIC_CODE) Mem_59_Renesas_59_Renesas_DeInit(void);

/* Declaration of API "Mem_59_Renesas_GetVersionInfo" */
extern FUNC(void, MEM_PUBLIC_CODE) Mem_59_Renesas_GetVersionInfo(
                                                   P2VAR(Std_VersionInfoType, AUTOMATIC, MEM_APPL_DATA) versionInfoPtr);/* PRQA S 3432 # JV-01 */

/* Declaration of API "Mem_59_Renesas_GetJobResult" */
extern FUNC(Mem_59_Renesas_JobResultType, MEM_PUBLIC_CODE) Mem_59_Renesas_GetJobResult(
                                                                              Mem_59_Renesas_InstanceIdType instanceId);

/* Declaration of API "Mem_59_Renesas_Suspend" */
extern FUNC(void, MEM_PUBLIC_CODE) Mem_59_Renesas_Suspend(Mem_59_Renesas_InstanceIdType instanceId);

/* Declaration of API "Mem_59_Renesas_Resume" */
extern FUNC(void, MEM_PUBLIC_CODE) Mem_59_Renesas_Resume(Mem_59_Renesas_InstanceIdType instanceId);

/* Declaration of API "Mem_59_Renesas_PropagateError" */
extern FUNC(void, MEM_PUBLIC_CODE) Mem_59_Renesas_PropagateError(Mem_59_Renesas_InstanceIdType instanceId);

/* Declaration of API "Mem_59_Renesas_Read" */
extern FUNC(Std_ReturnType, MEM_PUBLIC_CODE) Mem_59_Renesas_Read(Mem_59_Renesas_InstanceIdType instanceId, 
Mem_59_Renesas_AddressType sourceAddress, P2VAR(Mem_59_Renesas_DataType, AUTOMATIC, MEM_APPL_DATA) destinationDataPtr,  /* PRQA S 3432 # JV-01 */
Mem_59_Renesas_LengthType length);

#if (MEM_59_RENESAS_READIMMEDIATE_API == STD_ON)
/* Declaration of API "Mem_59_Renesas_ReadImmediate" */
extern FUNC(Std_ReturnType, MEM_PUBLIC_CODE) Mem_59_Renesas_ReadImmediate(Mem_59_Renesas_InstanceIdType instanceId, 
Mem_59_Renesas_AddressType sourceAddress, P2VAR(Mem_59_Renesas_DataType, AUTOMATIC, MEM_APPL_DATA) destinationDataPtr,  /* PRQA S 3432 # JV-01 */
Mem_59_Renesas_LengthType length);
#endif

/* Declaration of API "Mem_59_Renesas_Write" */
extern FUNC(Std_ReturnType, MEM_PUBLIC_CODE) Mem_59_Renesas_Write(Mem_59_Renesas_InstanceIdType instanceId, 
  Mem_59_Renesas_AddressType targetAddress, P2CONST(Mem_59_Renesas_DataType, AUTOMATIC, MEM_APPL_CONST) sourceDataPtr, 
  Mem_59_Renesas_LengthType length);

/* Declaration of API "Mem_59_Renesas_Erase" */
extern FUNC(Std_ReturnType, MEM_PUBLIC_CODE) Mem_59_Renesas_Erase(Mem_59_Renesas_InstanceIdType instanceId, 
                                           Mem_59_Renesas_AddressType targetAddress, Mem_59_Renesas_LengthType length);

/* Declaration of API "Mem_59_Renesas_BlankCheck" */
extern FUNC(Std_ReturnType, MEM_PUBLIC_CODE) Mem_59_Renesas_BlankCheck(Mem_59_Renesas_InstanceIdType instanceId, 
                                           Mem_59_Renesas_AddressType targetAddress, Mem_59_Renesas_LengthType length);

/* Declaration of API "Mem_59_Renesas_HwSpecificService" */
extern FUNC(Std_ReturnType, MEM_PUBLIC_CODE) Mem_59_Renesas_HwSpecificService(Mem_59_Renesas_InstanceIdType instanceId,
Mem_59_Renesas_HwServiceIdType hwServiceId, P2VAR(Mem_59_Renesas_DataType, AUTOMATIC, MEM_APPL_DATA) dataPtr,           /* PRQA S 3432 # JV-01 */
P2VAR(Mem_59_Renesas_LengthType, AUTOMATIC, MEM_APPL_DATA) lengthPtr);                                                  /* PRQA S 3432 # JV-01 */

/*Declaration of API "Mem_59_Renesas_MainFunction" */
extern FUNC(void, MEM_PUBLIC_CODE) Mem_59_Renesas_MainFunction(void);
#define MEM_59_RENESAS_STOP_SEC_PUBLIC_CODE
#include "Mem_59_Renesas_MemMap.h"

#define MEM_59_RENESAS_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "Mem_59_Renesas_MemMap.h"
/* Declaration for MEM Database */
extern CONST(Mem_59_Renesas_ConfigType, MEM_59_RENESAS_CONFIG_DATA) Mem_59_Renesas_GstConfiguration[];                  /* PRQA S 3684 # JV-01 */

#define MEM_59_RENESAS_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "Mem_59_Renesas_MemMap.h"


#define MEM_59_RENESAS_START_SEC_CONST_32
#include "Mem_59_Renesas_MemMap.h"
#if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
/* Declaration for start/end of code flash */
extern CONST(uint32, MEM_59_RENESAS_CONFIG_DATA) \
                                             Mem_59_Renesas_GaaCodeFlash[MEM_59_RENESAS_TOTAL_BANK][MEM_59_RENESAS_TWO];
/* Declaration for start/end of data flash */
extern CONST(uint32, MEM_59_RENESAS_CONFIG_DATA) \
                                             Mem_59_Renesas_GaaDataFlash[MEM_59_RENESAS_TOTAL_AREA][MEM_59_RENESAS_TWO];
#endif
#define MEM_59_RENESAS_STOP_SEC_CONST_32
#include "Mem_59_Renesas_MemMap.h"

#endif /* MEM_59_RENESAS_H */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
