/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas R22-11 X2x MCAL Components                                                          */
/* Module       = MemAcc_MemApi.h                                                                                     */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2024-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Provision of Flash Wrapper Component specific types used within the module.                                        */
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
 * 1.1.1:  30/06/2025:  Remove SW-VERSION in file header and update MEMACC_MEMAPI_SW_PATCH_VERSION to 1
 * 1.1.0:  30/06/2025:  Update SW-VERSION for RH850/Ver22.01.00 (D) U2Ax release
 * 1.0.3:  25/04/2025: Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 
 * 1.0.2:  31/03/2025: Initial Version.
 */
/**********************************************************************************************************************/
#ifndef MEMACC_MEMAPI_H
#define MEMACC_MEMAPI_H

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for Type definitions */
#include "MemAcc_GeneralTypes.h"
/***********************************************************************************************************************
 **                                                Version Information                                                 **
 ***********************************************************************************************************************/
/* AUTOSAR release version information */
#define MEMACC_MEMAPI_AR_RELEASE_MAJOR_VERSION                              4
#define MEMACC_MEMAPI_AR_RELEASE_MINOR_VERSION                              8
#define MEMACC_MEMAPI_AR_RELEASE_REVISION_VERSION                           0
/* Module Software version information */                         
#define MEMACC_MEMAPI_SW_MAJOR_VERSION                                      1
#define MEMACC_MEMAPI_SW_MINOR_VERSION                                      1
#define MEMACC_MEMAPI_SW_PATCH_VERSION                                      1
/***********************************************************************************************************************
 **                                               Coding Rule Violations                                               **
 ***********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE Rule CWE-398, CWE-569                                            */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is accepted. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3630)    : The implementation of this struct/union type should be hidden.                               */
/* Rule                : MISRA C:2012 Dir-4.8                                                                         */
/* JV-01 Justification : This is accepted. Redundant of struct or union type has no affect to driver operation.       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:1336)    : Parameter identifiers missing in declaration of a function type.                             */
/* Rule                : MISRA C:2012 Rule-8.2, CWE Rule CWE-398, CWE-569                                             */
/* JV-01 Justification : Parameter identifiers are  missing however not impact the MCAL operation.                    */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:4641)    : The identifier '%1s' could conflict in the future with the name of a macro in '<%2s>'.       */
/* Rule                : CERTC 3.6.0 Rule DCL37, CWE 3.6.0 Rule CWE-398, CWE-569                                      */
/* JV-01 Justification : This message is just a notice to avoid using this identifier as a macro in standard library  */
/*                       in the future.                                                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/***********************************************************************************************************************
 **                                                 GLOBAL DATA TYPES                                                  **
 ***********************************************************************************************************************/

/* Physical memory device address type */
typedef MemAcc_AddressType MemAcc_MemAddressType;

typedef Mem_59_Renesas_ConfigType MemAcc_MemConfigType; 

/* General data type */
typedef uint8 MemAcc_MemDataType;

/* Memory driver instance ID type */
typedef uint32 MemAcc_MemInstanceIdType;

/* Physical memory device length type */
typedef uint32 MemAcc_MemLengthType;

/* Index type for Mem driver hardware specific service table */
typedef uint32 MemAcc_MemHwServiceIdType;

/* Function pointer for the Mem_59_Renesas_Init service for the invocation of the Mem driver API via function
pointer interface. */
typedef P2FUNC(void, MEMACC_APPL_CODE, MemAcc_MemInitFuncType) (                                                        /* PRQA S 3432 # JV-01 */
  MemAcc_MemConfigType* configPtr
);

/* Function pointer for the Mem_DeInit service for the invocation of the Mem driver API via
function pointer interface */
typedef P2FUNC(void, MEMACC_APPL_CODE, MemAcc_MemDeInitFuncType) (                                                      /* PRQA S 3432 # JV-01 */
  void
);

/* Function pointer for the Mem_JobResultType service for the invocation of the Mem driver API
via function pointer interface */
typedef P2FUNC(Mem_59_Renesas_JobResultType, MEMACC_APPL_CODE, MemAcc_MemGetJobResultFuncType) (                        /* PRQA S 3432 # JV-01 */
  MemAcc_MemInstanceIdType instanceId
);

/* Function pointer for the Mem_Suspend service for the invocation of the Mem driver API via
function pointer interface */
typedef P2FUNC(void, MEMACC_APPL_CODE, MemAcc_MemSuspendFuncType) (                                                     /* PRQA S 3432 # JV-01 */
  MemAcc_MemInstanceIdType instanceId
);

/* Function pointer for the Mem_Resume service for the invocation of the Mem driver API via
function pointer interface */
typedef P2FUNC(void, MEMACC_APPL_CODE, MemAcc_MemResumeFuncType) (                                                      /* PRQA S 3432 # JV-01 */
  MemAcc_MemInstanceIdType instanceId
);


/* Function pointer for the Mem_PropagateError service for the invocation of the Mem driver API
via function pointer interface */
typedef P2FUNC(void, MEMACC_APPL_CODE, MemAcc_MemPropagateErrorFuncType) (                                              /* PRQA S 3432 # JV-01 */
  MemAcc_MemInstanceIdType instanceId
);

/* Function pointer for the Mem_Read service for the invocation of the Mem driver API via
function pointer interface */
typedef P2FUNC(Std_ReturnType, MEMACC_APPL_CODE, MemAcc_MemReadFuncType) (                                              /* PRQA S 3432 # JV-01 */
  MemAcc_MemInstanceIdType instanceId,
  MemAcc_MemAddressType sourceAddress,
  MemAcc_MemDataType* destinationDataPtr,
  MemAcc_MemLengthType length
);

/* Function pointer for the Mem_Write service for the invocation of the Mem driver API via function
pointer interface */
typedef P2FUNC(Std_ReturnType, MEMACC_APPL_CODE, MemAcc_MemWriteFuncType) (                                             /* PRQA S 3432 # JV-01 */
  MemAcc_MemInstanceIdType instanceId,
  MemAcc_MemAddressType targetAddress,
  const MemAcc_MemDataType* sourceDataPtr,
  MemAcc_MemLengthType length
);


/* Function pointer for the Mem_Erase service for the invocation of the Mem driver API via
function pointer interface */
typedef P2FUNC(Std_ReturnType, MEMACC_APPL_CODE, MemAcc_MemEraseFuncType) (                                             /* PRQA S 3432 # JV-01 */
  MemAcc_MemInstanceIdType instanceId,
  MemAcc_MemAddressType targetAddress,
  MemAcc_MemLengthType length
);

/* Function pointer for the Mem_BlankCheck function for the invocation of the Mem driver
API via function pointer interface */
typedef P2FUNC(Std_ReturnType, MEMACC_APPL_CODE, MemAcc_MemBlankCheckFuncType) (                                        /* PRQA S 3432 # JV-01 */
  MemAcc_MemInstanceIdType instanceId,
  MemAcc_MemAddressType targetAddress,
  MemAcc_MemLengthType length
);

/* Function pointer for the Mem_HwSpecificService function for the invocation of the Mem driver
API via function pointer interface */
typedef P2FUNC(Std_ReturnType, MEMACC_APPL_CODE, MemAcc_MemHwSpecificServiceFuncType) (                                 /* PRQA S 3432 # JV-01 */
  MemAcc_MemInstanceIdType instanceId,
  MemAcc_MemHwServiceIdType hwServiceId,
  MemAcc_MemDataType* dataPtr,
  MemAcc_MemLengthType* lengthPtr
);

/* Function pointer for the Mem_59_Renesas_MainFunction service for the invocation of the Mem driver API via
function pointer interface */
typedef P2FUNC(void, MEMACC_APPL_CODE, MemAcc_MemMainFuncType) (                                                        /* PRQA S 3432 # JV-01 */
  void
);

/* This structure contains elements for accessing the Mem driver service functions and consistency
information */
typedef volatile struct STag_MemAcc_MemBinaryHeaderType                                                                 /* PRQA S 3630 # JV-01 */
{
  /* Unique ID */
  uint64 UniqueId;
  /* Header flags */
  uint64 Flags;
  /* Address of Mem driver header structure */
  uint64 Header;
  /* Address of Mem driver delimiter field */
  uint64 Delimiter;
  /* Mem_59_Renesas_Init function pointer */
  MemAcc_MemInitFuncType *InitFunc;
  /* Mem_DeInit function pointer */
  MemAcc_MemDeInitFuncType *DeInitFunc;
  /* Mem_Main function pointer */
  MemAcc_MemMainFuncType *MainFunc;
  /* Mem_GetJobResult function pointer */
  MemAcc_MemGetJobResultFuncType *GetJobResultFunc;
  /* Mem_Read function pointer */
  MemAcc_MemReadFuncType *ReadFunc;
  /* Mem_Write function pointer */
  MemAcc_MemWriteFuncType *WriteFunc;
  /* Mem_Erase function pointer */
  MemAcc_MemEraseFuncType *EraseFunc;
  /* Mem_PropagateError function pointer */
  MemAcc_MemPropagateErrorFuncType *PropagateErrorFunc;
  /* Mem_BlankCheck function pointer */
  MemAcc_MemBlankCheckFuncType *BlankCheckFunc;
  /* Mem_Suspend function pointer */
  MemAcc_MemSuspendFuncType *SuspendFunc;
  /* Mem_Resume function pointer */
  MemAcc_MemResumeFuncType *ResumeFunc;
  /* Hardware specific service function pointer */
  MemAcc_MemHwSpecificServiceFuncType *HwSpecificServiceFunc;
} MemAcc_MemBinaryHeaderType;

/* Asynchronous job result type */
typedef enum ETag_MemAcc_MemJobResultType                                                                               /* PRQA S 4641 # JV-01 */
{
  MEM_JOB_OK = 0,          /* The last job has been finished successfully */
  MEM_JOB_PENDING,         /* A job is currently being processed */
  MEM_JOB_FAILED,          /* Job failed for some unspecific reason */
  MEM_INCONSISTENT,        /* The checked page is not blank */
  MEM_ECC_UNCORRECTED,     /* Uncorrectable ECC errors occurred during  memory access */
  MEM_ECC_CORRECTED        /* Correctable ECC errors occurred during memory access */
} MemAcc_MemJobResultType;


#endif /* MEMACC_MEMAPI_H */

/***********************************************************************************************************************
**                                                    End Of File                                                     **
***********************************************************************************************************************/
