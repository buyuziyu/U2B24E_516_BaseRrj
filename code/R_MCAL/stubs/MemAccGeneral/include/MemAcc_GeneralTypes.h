/*============================================================================*/
/* Project      = AUTOSAR Renesas R22-11 X2x MCAL Components                  */
/* File name    = MemAcc_GeneralTypes.h                                       */
/* ===========================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2024-2025 Renesas Electronics Corporation. All rights reserved.        */
/*============================================================================*/
/* Purpose:                                                                   */
/* Contains definition of datatypes used by MemAcc driver                     */
/*                                                                            */
/*============================================================================*/
/*                                                                            */
/* Unless otherwise agreed upon in writing between your company and           */
/* Renesas Electronics Corporation the following shall apply!                 */
/*                                                                            */
/* Warranty Disclaimer                                                        */
/*                                                                            */
/* There is no warranty of any kind whatsoever granted by Renesas. Any        */
/* warranty is expressly disclaimed and excluded by Renesas, either expressed */
/* or implied, including but not limited to those for non-infringement of     */
/* intellectual property, merchantability and/or fitness for the particular   */
/* purpose.                                                                   */
/*                                                                            */
/* Renesas shall not have any obligation to maintain, service or provide bug  */
/* fixes for the supplied Product(s) and/or the Application.                  */
/*                                                                            */
/* Each User is solely responsible for determining the appropriateness of     */
/* using the Product(s) and assumes all risks associated with its exercise    */
/* of rights under this Agreement, including, but not limited to the risks    */
/* and costs of program errors, compliance with applicable laws, damage to    */
/* or loss of data, programs or equipment, and unavailability or              */
/* interruption of operations.                                                */
/*                                                                            */
/* Limitation of Liability                                                    */
/*                                                                            */
/* In no event shall Renesas be liable to the User for any incidental,        */
/* consequential, indirect, or punitive damage (including but not limited     */
/* to lost profits) regardless of whether such liability is based on breach   */
/* of contract, tort, strict liability, breach of warranties, failure of      */
/* essential purpose or otherwise and even if advised of the possibility of   */
/* such damages. Renesas shall not be liable for any services or products     */
/* provided by third party vendors, developers or consultants identified or   */
/* referred to the User by Renesas in connection with the Product(s) and/or   */
/* the Application.                                                           */
/*                                                                            */
/*============================================================================*/
/* Environment:                                                               */
/*              Devices:        RH850/X2x                                     */
/*============================================================================*/

/*******************************************************************************
**                      Revision Control History                              **
*******************************************************************************/
/*
 * 1.1.1:  30/06/2025:  Remove SW-VERSION in file header and update MEMACC_GENERALTYPES_SW_PATCH_VERSION to 1
 * 1.1.0:  30/06/2025:  Update SW-VERSION for RH850/Ver22.01.00 (D) U2Ax release
 * 1.0.3:  25/04/2025:  Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03    
 * 1.0.2:  31/03/2025:  Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02
                        Remove MemAcc_MemDataType, MemAcc_MemAddressType, MemAcc_MemInstanceIdType,
                        MemAcc_MemLengthType, MemAcc_MemHwServiceIdType 
                        Add message 4641 to support QA-C version 11.6.0
 * 1.0.1:  28/02/2025:  Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 1.0.0:  31/12/2024:  Update SW-VERSION for Ver22.02.00 U2Bx Final Release. 
 * 0.0.2:  31/10/2024:  Updated Version.
 * 0.0.1:  30/08/2024:  Initial Version. 
 */
/******************************************************************************/
#ifndef MEMACC_GENERALTYPES_H
#define MEMACC_GENERALTYPES_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* Included for Type definitions */
#include "Std_Types.h"
#include "Mem_59_Renesas_Types.h"
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/*
 * AUTOSAR specification version information
 */

#define MEMACC_GENERALTYPES_AR_RELEASE_MAJOR_VERSION                          4
#define MEMACC_GENERALTYPES_AR_RELEASE_MINOR_VERSION                          8
#define MEMACC_GENERALTYPES_AR_RELEASE_REVISION_VERSION                       0

/*
 * File version information
 */
#define MEMACC_GENERALTYPES_SW_MAJOR_VERSION                                  1
#define MEMACC_GENERALTYPES_SW_MINOR_VERSION                                  1
#define MEMACC_GENERALTYPES_SW_PATCH_VERSION                                  0

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:3630)    : The implementation of this struct/union type should be hidden.                               */
/* Rule                : MISRA C:2012 Dir-4.8                                                                         */
/* JV-01 Justification : This is accepted. Redundant of struct or union type has no affect to driver operation.       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:4641)    : The identifier '%1s' could conflict in the future with the name of a macro in '<%2s>'.       */
/* Rule                : CERTC 3.6.0 Rule DCL37, CWE 3.6.0 Rule CWE-398, CWE-569                                      */
/* JV-01 Justification : This message is just a notice to avoid using this identifier as a macro in standard library  */
/*                       in the future.                                                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/
/*******************************************************************************
**                      Global Data Types (ECU dependent)                     **
*******************************************************************************/
/* Unique address area ID type */
typedef uint16 MemAcc_AddressAreaIdType;

/* Logical memory address type */
typedef uint32 MemAcc_AddressType;

/* Job length type */
typedef uint32 MemAcc_LengthType;

/* General data type */
typedef uint8 MemAcc_DataType;

/***********************************************************
Enum: MemAcc_JobResultType

Enumeration for Asynchronous job result type

Members:
MEMACC_MEM_OK                - The last MemAcc job was finished successfully
MEMACC_MEM_FAILED            - The last MemAcc job resulted in an unspecific
                               failure and the job was not completed
MEMACC_MEM_INCONSISTENT      - The results of the last MemAcc job didn't
                               meet the expected result, e.g. a blank check
                               operation was applied on a non-blank memory area
MEMACC_MEM_CANCELED          - The last MemAcc job was canceled
MEMACC_MEM_ECC_UNCORRECTED   - The last memory operation returned an uncorrectable ECC error
MEMACC_MEM_ECC_CORRECTED     - The last memory operation returned a correctable ECC error
*/
typedef enum ETag_MemAcc_JobResultType                                                                                  /* PRQA S 4641 # JV-01 */
{
  MEMACC_MEM_OK = 0,
  MEMACC_MEM_FAILED,
  MEMACC_MEM_INCONSISTENT,
  MEMACC_MEM_CANCELED,
  MEMACC_MEM_ECC_UNCORRECTED,
  MEMACC_MEM_ECC_CORRECTED
} MemAcc_JobResultType;
/***********************************************************
Enum: MemAcc_JobStatusType

Enumeration for Asynchronous job status type

Members:
MEMACC_JOB_IDLE              - Job processing was completed or no job pending
MEMACC_JOB_PENDING           - A job is currently being processed
*/
typedef enum ETag_MemAcc_JobStatusType                                                                                  /* PRQA S 4641 # JV-01 */
{
  MEMACC_JOB_IDLE = 0,
  MEMACC_JOB_PENDING
} MemAcc_JobStatusType;
/***********************************************************
Enum: MemAcc_JobType

Enumeration for asynchronous jobs type

Members:
MEMACC_NO_JOB              - No job currently pending
MEMACC_WRITE_JOB           - Write job pending
MEMACC_READ_JOB           - Read job pending
MEMACC_COMPARE_JOB - Compare job pending
MEMACC_ERASE_JOB - Erase job pending
MEMACC_MEMHWSPECIFIC_JOB - Hardware specific job pending
MEMACC_BLANKCHECK_JOB - Blank check job pending
MEMACC_REQUESTLOCK_JOB - Request lock job pending
*/
typedef enum ETag_MemAcc_JobType                                                                                        /* PRQA S 4641 # JV-01 */
{
  MEMACC_NO_JOB = 0,
  MEMACC_WRITE_JOB,
  MEMACC_READ_JOB,
  MEMACC_COMPARE_JOB,
  MEMACC_ERASE_JOB,
  MEMACC_MEMHWSPECIFIC_JOB,
  MEMACC_BLANKCHECK_JOB,
  MEMACC_REQUESTLOCK_JOB
} MemAcc_JobType;

/* Type for the unique numeric identifiers of all Mem hardware instances used for hardware specific
requests */
typedef uint32 MemAcc_HwIdType;

/***********************************************************
Struct: MemAcc_MemoryInfoType

Structure contains information of Mem device characteristics. It can be accessed via the
MemAcc_GetMemoryInfo() service.

Members:
LogicalStartAddress - Logical start address of sub address area
PhysicalStartAddress - Physical start address of sub address area
MaxOffset - Size of sub address area in bytes -1
EraseSectorSize - Size of a sector in bytes
EraseSectorBurstSize- Size of a sector burst in bytes. Equals SectorSize in case burst is disabled
ReadPageSize - Read size of a page in bytes
WritePageSize - Write size of a page in bytes
ReadPageBurstSize - Size of a read page burst in bytes. Equals ReadPageSize in case burst
is disabled
WritePageBurstSize - Size of a page burst in bytes. Equals WritePageSize in case burst is
disabled
HwId - Referenced memory driver hardware identifier
*/
typedef struct                                                                                                          /* PRQA S 3630 # JV-01 */
{
  MemAcc_AddressType LogicalStartAddress;
  MemAcc_AddressType PhysicalStartAddress;
  MemAcc_LengthType MaxOffset;
  uint32 EraseSectorSize;
  uint32 EraseSectorBurstSize;
  uint32 ReadPageSize;
  uint32 WritePageSize;
  uint32 ReadPageBurstSize;
  uint32 WritePageBurstSize;
  uint32 HwId;
} MemAcc_MemoryInfoType;

/***********************************************************
Struct: MemAcc_JobInfoType

Structure contains information the current processing state of the MemAcc module.

Members:
LogicalAddress - Address of currently active address area request
Length - Length of the currently active address area request
HwId - Referenced memory driver hardware identifier
MemInstanceId - Instance ID of the current memory request
MemAddress- Physical address of the current memory driver request
MemLength - Length of memory driver request
CurrentJob - Currently active MemAcc job
MemResult - Current or last Mem driver result
*/
typedef struct                                                                                                          /* PRQA S 3630 # JV-01 */
{
  MemAcc_AddressType LogicalAddress;
  MemAcc_LengthType Length;
  MemAcc_HwIdType HwId;
  uint32 MemInstanceId;
  uint32 MemAddress;
  uint32 MemLength;
  MemAcc_JobType CurrentJob;
  Mem_59_Renesas_JobResultType MemResult;
} MemAcc_JobInfoType;

#endif /* MEMACC_GENERALTYPES_H */

/***********************************************************************************************************************
**                                                    End Of File                                                     **
***********************************************************************************************************************/
