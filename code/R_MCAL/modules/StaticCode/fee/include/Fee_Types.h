/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas R22.11 X2x MCAL Components                                                          */
/* Module       = Fee_Types.h                                                                                         */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2024-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Provision of Database declaration.                                                                                 */
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
 * 1.1.1:  30/06/2025:  Remove SW-VERSION in file header
 * 1.1.0:  30/06/2025:  Update SW-VERSION for U2Ax Ver22.01.00(D) Final Release
 * 1.0.3:  25/04/2025:  Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03
 * 1.0.2:  31/03/2025:  Include Section add MemAcc_GeneralTypes.h
 *                      Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02 Release
 *                      As part of <QAC 11.6.0> support, following changes are made
 *                      Removed message 0778
 * 1.0.1:  28/02/2025:  Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 1.0.0:  31/12/2024:  Update SW-VERSION 1.0.0.
 * 0.0.2:  31/10/2024:  Add SchM Critical Section Protection Macros.
 *                      Add FEE_FOUR_UNIT_SIZE.
 * 0.0.1:  30/08/2024:  Initial Version.
 */
/**********************************************************************************************************************/

#ifndef FEE_TYPES_H
#define FEE_TYPES_H

/***********************************************************************************************************************
**                                                Include Section                                                     **
***********************************************************************************************************************/
/* Include standard Autosar Type */
#include "Std_Types.h"

#include "MemAcc.h"

#include "MemAcc_GeneralTypes.h"

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:3630)    : The implementation of this struct/union type should be hidden.                               */
/* Rule                : MISRA C:2012 Dir-4.8                                                                         */
/* JV-01 Justification : This is accepted. Redundant of struct or union type has no affect to driver operation.       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE rule CWE-398, CWE-569                                            */
/*                       REFERENCE - ISO:C90-6.3.1 Primary Expressions                                                */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is           */
/*                       accepted.                                                                                    */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0342)    : Using the glue operator '##'.                                                                */
/* Rule                : MISRA C:2012 Rule-20.10, CERTCCM PRE05                                                       */
/* JV-01 Justification : This can be accepted, due to the implementation is following AUTOSAR standard rule for SchM  */
/*                       module's name.                                                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR Release version information */
#define FEE_TYPES_AR_RELEASE_MAJOR_VERSION                                      FEE_AR_RELEASE_MAJOR_VERSION
#define FEE_TYPES_AR_RELEASE_MINOR_VERSION                                      FEE_AR_RELEASE_MINOR_VERSION
#define FEE_TYPES_AR_RELEASE_REVISION_VERSION                                   FEE_AR_RELEASE_REVISION_VERSION

/* Module Software version information */
#define FEE_TYPES_SW_MAJOR_VERSION                                              FEE_SW_MAJOR_VERSION
#define FEE_TYPES_SW_MINOR_VERSION                                              FEE_SW_MINOR_VERSION

/***********************************************************************************************************************
**                                                Global Symbols                                                      **
***********************************************************************************************************************/
#define FEE_TRUE                                                                (boolean)1
#define FEE_FALSE                                                               (boolean)0

#define FEE_ZERO                                                                (uint8)0U
#define FEE_ONE                                                                 (uint8)1U

/* Fee module initialization status */
#define FEE_UNINITIALIZED                                                       (boolean)0
#define FEE_INITIALIZED                                                         (boolean)1

#define FEE_UINT32_MASK                                                         (uint32)0xFFFFFFFFUL

#define FEE_INVALID_BLOCK_IDX                                                   (uint16)0xFFFFU

#define FEE_INVALID_ADDRESS_AREA_IDX                                            (uint16)0xFFFFU

/* Erased value in flash memory */
#define FEE_ERASED_VALUE                                                        (uint32)0xFFFFFFFFUL

#define FEE_VALIDATED_VALUE                                                     (uint32)0x55555555UL

#define FEE_INVALIDATED_FLAG_VALUE                                              (uint32)0x55555555UL

#define FEE_HEADE_VALID_INFOR_ADDRESS                                           (uint32)0x10UL

/* Block ID + Block Size - Block Data Address - Block W/E cycle count - CRC - Acitve Flag - Inactive Flag */
#define FEE_HEADER_INFOR_BLOCK_OFFSET_ADDR                                      (uint32)0x08UL

#define FEE_HEADER_BLOCK_OFFSET_ADDR                                            (uint32)0x20UL

#define FEE_VALID_BLOCK_OFFSET_ADDR                                             (uint32)0x10UL

#define FEE_INVALID_BLOCK_OFFSET_ADDR                                           (uint32)0x0CUL

#define FEE_INVALID_ADDRESS_AREA_OFFSET_ADDR                                    (uint32)0x0CUL

#define FEE_VALID_ADDRESS_AREA_OFFSET_ADDR                                      (uint32)0x10UL

/* Define mininum bytes of FLASH PAGE can be writen */
#define FEE_ONE_UNIT_SIZE                                                       4U

#define FEE_FOUR_UNIT_SIZE                                                      16U

#if (FEE_WRITE_DATA_IN_REVERT_DIRECTION == STD_ON)
#define FEE_DATA_DIRECTION                                                      (uint32)0x00000001UL
#else
#define FEE_DATA_DIRECTION                                                      (uint32)0x00000000UL
#endif /* #if (FEE_WRITE_DATA_IN_REVERT_DIRECTION == STD_ON) */

/***********************************************************************************************************************
**                                                Global Data Types                                                   **
***********************************************************************************************************************/

/* Status Type of Address Area */
typedef enum ETag_Fee_AddrAreaStatusType
{
   FEE_ADDRESS_AREA_VALID = 0,                                                  /* Fee Page is valid */
   FEE_ADDRESS_AREA_INVALID,                                                    /* Fee Page is invalid */
   FEE_ADDRESS_AREA_INCONSISTENT,                                               /* Fee Page is inconsistent */
   FEE_ADDRESS_AREA_HEADER_INVALID                                              /* Fee Page header is garbled */
} Fee_AddrAreaStatusType;

/* Status Type of Block Data */
typedef enum ETag_Fee_BlockStatusType
{
   FEE_BLOCK_VALID = 0,                                                         /* Fee block is valid */
   FEE_BLOCK_INVALID,                                                           /* Fee block is invalid */
   FEE_BLOCK_INCONSISTENT,                                                      /* Fee block is inconsistent */
   FEE_BLOCK_HEADER_INVALID,                                                    /* Fee block header is garbled */
   FEE_BLOCK_HEADER_BLANK                                                       /* Fee block header is blank */
} Fee_BlockStatusType;

/* List of all command option for internal usage */
typedef enum ETag_Fee_CommandType
{
   /* Nothing is requested or Job is accepted by underlying module */
   FEE_CMD_NO_PENDING = 0,

   /* Fee_Init: Init is requested */
   FEE_CMD_INITIALIZE,
   FEE_CMD_INIT_ADDRESS_AREA_HEADER_PARSE,
   FEE_CMD_INIT_WRITE_HEADER_FORMAT,
   FEE_CMD_INIT_WRITE_HEADER_FORMAT_DONE,
   FEE_CMD_INIT_SCAN_BLOCK_HEADER_PARSE,

   /* Fee support swap block */
   FEE_CMD_SWAP_ADDRESS_AREA,
   FEE_CMD_SWAP_HEADER_BLOCK,
   FEE_CMD_SWAP_VALIDATED_ADDRESS_AREA,
   FEE_CMD_SWAP_READ_BLOCK_DATA,
   FEE_CMD_SWAP_BLOCK_DATA_WRITE,
   FEE_CMD_SWAP_DATA_VALIDATE_BLOCK,
   FEE_CMD_SWAP_WRITE_HEADER_DATA,
   FEE_CMD_SWAP_DONE,

   /* Fee_Read: Read data is requested */
   FEE_CMD_READ,
   FEE_CMD_READ_DONE,

   /* Fee_Write: Write data is requested */
   FEE_CMD_WRITE,
   FEE_CMD_WRITE_BLOCK_DATA,
   FEE_CMD_WRITE_UNALIGNED_BLOCK,
   FEE_CMD_WRITE_VALIDATE_BLOCK,
   FEE_CMD_WRITE_DONE,

   /* Fee_InvalidateBlock: Invalidate is requested */
   FEE_CMD_INVALIDATE,
   FEE_CMD_INVALIDATE_DONE,

   /* Fee_EraseImmediateBlock: ERASE is requested */
   FEE_CMD_ERASE_IMMEDIATE,
   FEE_CMD_SWAP_ERASE_IMMEDIATE_BLOCK_DATA
} Fee_CommandType;

typedef struct STag_Fee_SubAddrAreaConfigType                                                                           /* PRQA S 3630 # JV-01 */
{
   /* Start address of address area */
   VAR(MemAcc_AddressType, FEE_VAR) ulStartAreaAddr;

   /* Size of the configured address area */
   VAR(MemAcc_AddressType, FEE_VAR) ulAddrAreaSize;
} Fee_SubAddrAreaConfigType;

typedef struct STag_Fee_AddrAreaConfigType
{
   VAR(MemAcc_AddressAreaIdType, FEE_VAR) usAddrAreaID;

   VAR(uint16, FEE_VAR) usNumOfSubAddrArea;

   const Fee_SubAddrAreaConfigType * pSubAddrArea;
} Fee_AddrAreaConfigType;

typedef struct STag_Fee_AddrAreaInfoType
{
   /* ID of active address area */
   VAR(uint32, FEE_VAR) usAddrAreaID;

   /* Index of active address area */
   VAR(uint16, FEE_VAR) usSubAddrAreaIndex;

   /* Address of current address area */
   VAR(MemAcc_AddressType, FEE_VAR) ulCurrHeaderAreaAddr;

   #if (FEE_WRITE_DATA_IN_REVERT_DIRECTION == STD_ON)
   /* Address of current data address */
   VAR(MemAcc_AddressType, FEE_VAR) ulCurrDataAreaAddr;
   #endif /* #if (FEE_WRITE_DATA_IN_REVERT_DIRECTION == STD_ON) */
} Fee_AddrAreaInfoType;

typedef struct STag_Fee_AddrAreaHeaderType
{
   VAR(MemAcc_AddressAreaIdType, FEE_VAR) usAddrAreaID;

   /* Start address of address area */
   VAR(MemAcc_AddressType, FEE_VAR) ulStartAreaAddr;

   /* Size of the configured address area */
   VAR(MemAcc_AddressType, FEE_VAR) ulAddrAreaSize;

   /* Direction of writing in memory */
   /* 0x00000000: Forward direction */
   /* 0x00000001: Reverse direction */
   VAR(uint32, FEE_VAR) ulConfigDirection;
} Fee_AddrAreaHeaderType;

/* Information for each block */
typedef struct STag_Fee_BlockHeaderType
{
   /* FeeBlockNumber: Block Id */
   VAR(uint16, FEE_VAR) usFeeBlockNumber;

   /* FeeBlockSize : Size of a logical block in bytes.*/
   VAR(uint16, FEE_VAR) usBlockSize;

   /* Marker for high priority data */
   VAR(boolean, FEE_VAR) blImmediateData;

   /* Data address of block */
   VAR(MemAcc_AddressType, FEE_VAR) ulBlockDataAddr;

   /* Number of write cycles required for this block */
   VAR(uint32, FEE_VAR) ulWECycles;

   /* Checksum of header block */
   VAR(uint32, FEE_VAR) ulBlockCRC;
} Fee_BlockHeaderType;

typedef struct STag_Fee_BlockInfoType
{
   /* Current status of Fee block */
   Fee_BlockStatusType enBlockStatus;

   /* Address of Fee block header in flash */
   VAR(MemAcc_AddressType, FEE_VAR) ulBlockRefAddr;

   /* Address of Fee block data in flash */
   VAR(MemAcc_AddressType, FEE_VAR) ulBlockDataAddr;

   /* Number of W/E cycle of configured block */
   VAR(uint32, FEE_VAR) ulBlockWECycle;
} Fee_BlockInfoType;

typedef struct STag_Fee_InforJobRequest
{
   /* Currently executed job (including internal one) */
   VAR(Fee_CommandType, FEE_NOINIT_DATA) enCmdJobRequest;

   /* Fee block index. Used by all Fee jobs */
   VAR(uint16, FEE_VAR) usBlockIndex;

   /* Fee block offset. Used by the read Fee job */
   VAR(MemAcc_LengthType, FEE_VAR) usBlockOffset;

   /* Number of bytes to read. Used by the read Fee job */
   VAR(MemAcc_LengthType, FEE_VAR) usBlockLength;

   /* Pointer to user data buffer. Used by the read Fee jobs */
   P2VAR(uint8, FEE_VAR, FEE_APPL_DATA) pJobReadDatatPtr;                                                               /* PRQA S 3432 # JV-01 */

   /* Pointer to user data buffer. Used by the write Fee jobs */
   P2CONST(uint8, FEE_VAR, FEE_APPL_CONST) pJobWriteDatatPtr;
} Fee_InforJobRequest;

/* Configuration data structure of the Fee module. */
typedef struct STag_Fee_ConfigType
{
   /* FeeBlockNumber: Block Id */
   VAR(uint16, FEE_VAR) usFeeBlockNumber;

   /* FeeBlockSize : Size of a logical block in bytes.*/
   VAR(uint16, FEE_VAR) usBlockSize;

   /* FeeImmediateData: Immediate Data Option */
   VAR(boolean, FEE_VAR) blImmeData;

   /* Number of write cycles required for this block */
   VAR(uint32, FEE_VAR) ulWECycles;

   /* Index of Addr Area */
   VAR(uint16, FEE_VAR) usIndexAddrArea;

   /* The alignment of the start address that Fee buffers need to have */
   VAR(uint8, FEE_VAR) ucBufferAlignmentValue;

} Fee_ConfigType;

typedef struct Stag_Fee_MemAccSubAddressAreaType
{
   /* MemAccLogicalStartAddress */
   MemAcc_AddressType ulLogicalStartAdress;

   /* Number of sector */
   Mem_59_Renesas_InstanceIdType ulNumberofSector;

   /* Sector offset */
   uint32 ulMemAccSectorOffset;
}Fee_MemAccSubAddressAreaType;

typedef struct Stag_Fee_MemAccAddressAreaType
{
   /* This value specifies a unique identifier which is used to reference to an AddressArea */
   uint32 MemAccAddressAreaConfiguration;

   /* MemAccBufferAlignmentValue */
   uint32 usAligedBuffer;

   uint32 *MemAccSubAddressAreaConfiguration;
}Fee_MemAccAddressAreaType;


/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                      SchM Critical Section Protection Macros                                       **
***********************************************************************************************************************/
#define FEE_ENTER_CRITICAL_SECTION(Exclusive_Area) SchM_Enter_Fee_##Exclusive_Area()                                    /* PRQA S 0342 # JV-01 */
#define FEE_EXIT_CRITICAL_SECTION(Exclusive_Area)  SchM_Exit_Fee_##Exclusive_Area()                                     /* PRQA S 0342 # JV-01 */
/***********************************************************************************************************************
**                                                Global Data                                                         **
***********************************************************************************************************************/
#define FEE_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "Fee_MemMap.h"

extern CONST(Fee_ConfigType, FEE_CONFIG_DATA) Fee_GaaBlockConfig[FEE_MAX_CONFIGURED_BLOCK_NUMBER];
extern CONST(Fee_AddrAreaConfigType, FEE_CONFIG_DATA) Fee_GaaAddrAreaConfig[FEE_MAX_DEFINED_ADDRESS_AREA_NUMBER];

#define FEE_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "Fee_MemMap.h"  

#endif /* #ifndef FEE_TYPES_H */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
