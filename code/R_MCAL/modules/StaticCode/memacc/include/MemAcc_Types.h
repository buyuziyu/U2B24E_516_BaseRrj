/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas R22-11 X2x MCAL Components                                                          */
/* Module       = MemAcc_Types.h                                                                                      */
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
 * 1.1.1:  30/06/2025:  Remove SW-VERSION in file header
 * 1.1.0:  30/06/2025:  Update SW-VERSION for RH850/Ver22.01.00 (D) U2Ax release
 * 1.0.3:  25/04/2025:  Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03
 * 1.0.2:  31/03/2025:  Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02
                        Remove MemAcc_MemConfigType, MemAcc_MemInitFuncType, MemAcc_MemDeInitFuncType, 
                        MemAcc_MemGetJobResultFuncType, MemAcc_MemSuspendFuncType, MemAcc_MemResumeFuncType,
                        MemAcc_MemPropagateErrorFuncType, MemAcc_MemReadFuncType, MemAcc_MemWriteFuncType,
                        MemAcc_MemEraseFuncType, MemAcc_MemHwSpecificServiceFuncType, MemAcc_MemMainFuncType, 
                        MemAcc_MemBlankCheckFuncType, MemAcc_MemBinaryHeaderType to correct the place of these types.       
                        Add message 1336 to support QA-C version 11.6.0 
 * 1.0.1:  28/02/2025:  Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 1.0.0:  31/12/2024:  Update SW-VERSION for Ver22.02.00 U2Bx Final Release. 
 * 0.0.2:  31/10/2024:  Remove blUseEraseBurst, blUseWriteBurst that not use in MemAcc_SubAreaConfigType struct
 *                      Update Mem to Mem_59_Renesas
 * 0.0.1:  30/08/2024:  Initial Version.
 */
/**********************************************************************************************************************/
#ifndef MEMACC_TYPES_H
#define MEMACC_TYPES_H

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for Type definitions */
#include "Std_Types.h"
#include "MemAcc_GeneralTypes.h"
#include "MemAcc_MemApi.h"
#include "Mem_59_Renesas.h"
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define MEMACC_TYPES_AR_RELEASE_MAJOR_VERSION    MEMACC_AR_RELEASE_MAJOR_VERSION
#define MEMACC_TYPES_AR_RELEASE_MINOR_VERSION    MEMACC_AR_RELEASE_MINOR_VERSION
#define MEMACC_TYPES_AR_RELEASE_REVISION_VERSION MEMACC_AR_RELEASE_REVISION_VERSION
/* Module Software version information */
#define MEMACC_TYPES_SW_MAJOR_VERSION            MEMACC_SW_MAJOR_VERSION
#define MEMACC_TYPES_SW_MINOR_VERSION            MEMACC_SW_MINOR_VERSION

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
/***********************************************************************************************************************
**                                                 GLOBAL DATA TYPES                                                  **
***********************************************************************************************************************/

typedef enum ETag_MemAcc_StatusType                                                                                     
{
  MEMACC_UNINIT = 0,
  MEMACC_INIT
} MemAcc_StatusType;

typedef enum ETag_MemAcc_InstanceStatusType                                                                             
{
  MEMACC_INSTANCE_BUSY = 0,
  MEMACC_INSTANCE_IDLE,
  MEMACC_INSTANCE_UNINIT
} MemAcc_InstanceStatusType;

typedef struct STag_MemAcc_SubAreaConfigType                                                                            /* PRQA S 3630 # JV-01 */
{
  MemAcc_AddressType ddLogicStartAddr;
  MemAcc_AddressType ddPhysicalStartAddr;
  MemAcc_LengthType ddSubAreaLength;
  MemAcc_HwIdType enHwType;
  uint32 ulMemReadPageSize;
  uint32 ulMemReadBurstSize;
  uint32 ulMemWritePageSize;
  uint32 ulMemWriteBurstSize;
  uint32 ulMemEraseSectorSize;
  uint32 ulMemEraseBurstSize;
  Mem_59_Renesas_InstanceIdType ulInstanceId;
  uint8 ucNumberOfEraseRetries;
  uint8 ucNumberOfWriteRetries;
} MemAcc_SubAreaConfigType;

typedef struct STag_MemAcc_AddrAreaConfigType                                                                           /* PRQA S 3630 # JV-01 */
{
  /* Pointer to job end callback notification */
  P2FUNC(void, MEMACC_APPL_CODE, pJobEndNotificationPointer)(MemAcc_AddressAreaIdType, MemAcc_JobResultType);           /* PRQA S 3432, 1336 # JV-01, JV-01 */
  /* Pointer to sub address area config */
  const MemAcc_SubAreaConfigType *pSubAreaConfig;
  /* Number of sub address area */
  uint16 usNumOfSubArea;
  /* Buffer alignment value */
  uint8 ucBufferAlignValue;
} MemAcc_AddrAreaConfigType;

typedef struct STag_MemAcc_AddrAreaGlobalDataType
{
  boolean blWaitingMemResult;
  boolean blCancelRequest;
  uint8 ucRetryTimes;
  uint16 usCurrentSubAreaIdx;
  MemAcc_JobType enCommand;
  MemAcc_LengthType ddProcessedLength;
  MemAcc_LengthType ddMemRequestedLength;
  MemAcc_JobResultType enJobResult;
  Mem_59_Renesas_JobResultType enMemJobResult;
  MemAcc_JobStatusType enJobStatus;
  MemAcc_MemHwServiceIdType ulHwServiceId;
  MemAcc_AddressType ddCurrentAddress;
  MemAcc_LengthType ddRemainingLength;
  MemAcc_DataType* pBufferAddress;
  const MemAcc_DataType* pReadOnlyBufferAddr;
  MemAcc_LengthType* pLengthPtr;
} MemAcc_AddrAreaGlobalDataType;

typedef struct STag_MemAcc_LockRequestData
{
  /* Number of instance need to be locked */
  Mem_59_Renesas_InstanceIdType ulNumOfLockInstance;
  P2FUNC(void, MEMACC_APPL_CODE, pLockNotificationFctPtr)(void);                                                        /* PRQA S 3432 # JV-01 */
} MemAcc_LockRequestData;

/* Structure for MemAcc Init Configuration */
/* Overall Module Configuration Data Structure */
typedef struct STag_MemAcc_ConfigType
{
  /* Database start value - 0x0EDF0400 */
  uint32 ulStartOfDbToc;
  const uint16 *pPriority2AddrAreaId;
  /* Address of address area config */
  const MemAcc_AddrAreaConfigType* pAddrAreaConfig;
  /* Pointer to invocation type of instance */
  const uint8* pInstInvocation;
} MemAcc_ConfigType;
                                                               

typedef struct STag_MemAcc_GstVarProperties
{
  /* Flag to indicate there is a lock request on this instance */
  boolean blLockRequest;
  /* Flag to indicate Mem driver related to this instance is locked */
  boolean blLockState;
  /* Flag to indicate that this instance is suspended once,
     can't process another suspend request */
  boolean blSuspendedFlag;
  /* Addread area id is being processed */
  uint16 usProcessingAreaId;
  /* Addread area id is being processed */
  uint16 usSuspendedAreaId;
  /* Status of instance */
  MemAcc_InstanceStatusType enInstanceStatus;
  /* Pointer to Mem binary header */
  MemAcc_MemBinaryHeaderType *pMemBinary;
} MemAcc_GstVarProperties;

typedef struct STag_MemAcc_UniqueIdType                                                                                 
{
  /* ABI version - fixed 0001 */
  uint16 usABIversion;
  /* Vendor Id */
  uint16 usVendorId;
  /* Driver Id */
  uint32 ulDriverId;
} MemAcc_UniqueIdType;

#endif /* MEMACC_TYPES_H */

/***********************************************************************************************************************
**                                                    End Of File                                                     **
***********************************************************************************************************************/
