/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Mem_59_Renesas_Types.h                                                                              */
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
/*              Devices:        X2x                                                                                   */
/*====================================================================================================================*/

/***********************************************************************************************************************
**                                              Revision Control History                                              **
***********************************************************************************************************************/
/*
 * 1.1.0:  30/06/2025   : Update SW-VERSION for RH850/Ver22.01.00(D) U2Ax release
 * 1.0.3:  25/04/2025   : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 Release
 * 1.0.2:  31/03/2025   : Update Mem_59_Renesas_CFECCRegType and Mem_59_Renesas_DFECCRegType
 * 1.0.1:  28/02/2025   : Remove Mem_59_Renesas_OptionByteID type
 * 1.0.0:  31/12/2024   : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 * 0.0.2:  31/10/2024   : As part of ARDAACJ-621, support downgrade from version AR23-11 to AR22-11.
 *                        Support commonize source code.
 * 0.0.1:  30/08/2024   : Initial Version
 */
/**********************************************************************************************************************/
#ifndef MEM_59_RENESAS_TYPES_H
#define MEM_59_RENESAS_TYPES_H

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for Type definitions */
#include "Std_Types.h"
/* Included for pre-compile options */
#include "Mem_59_Renesas_PCTypes.h"
/* Included for pre-compile options */
#include "r_rfd_config.h"
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define MEM_59_RENESAS_TYPES_AR_RELEASE_MAJOR_VERSION       MEM_59_RENESAS_AR_RELEASE_MAJOR_VERSION
#define MEM_59_RENESAS_TYPES_AR_RELEASE_MINOR_VERSION       MEM_59_RENESAS_AR_RELEASE_MINOR_VERSION
#define MEM_59_RENESAS_TYPES_AR_RELEASE_REVISION_VERSION    MEM_59_RENESAS_AR_RELEASE_REVISION_VERSION
/* Module Software version information */
#define MEM_59_RENESAS_TYPES_SW_MAJOR_VERSION               MEM_59_RENESAS_SW_MAJOR_VERSION
#define MEM_59_RENESAS_TYPES_SW_MINOR_VERSION               MEM_59_RENESAS_SW_MINOR_VERSION

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
/* Address offset from the configured flash base address to access a certain flash memory area */
typedef uint8 Mem_59_Renesas_DataType;

typedef uint32 Mem_59_Renesas_InstanceIdType;

typedef uint32 Mem_59_Renesas_LengthType;

typedef uint32 Mem_59_Renesas_HwServiceIdType;

/* Enumeration for job result type */
typedef enum ETag_Mem_59_Renesas_JobResultType
{
  MEM_59_RENESAS_JOB_OK = 0,
  MEM_59_RENESAS_JOB_PENDING,
  MEM_59_RENESAS_JOB_FAILED,
  MEM_59_RENESAS_INCONSISTENT,
  MEM_59_RENESAS_ECC_UNCORRECTED,
  MEM_59_RENESAS_ECC_CORRECTED
} Mem_59_Renesas_JobResultType;

/* Enumeration for flash driver status type */
typedef enum ETag_Mem_59_Renesas_StatusType
{
  MEM_59_RENESAS_IDLE = 0,
  MEM_59_RENESAS_BUSY
} Mem_59_Renesas_StatusType;

/* Enumeration for flash memoty type */
typedef enum ETag_Mem_59_Renesas_FlashType
{
  MEM_59_RENESAS_CODE_FLASH = 0,
  MEM_59_RENESAS_DATA_FLASH,
  MEM_59_RENESAS_NONE_FLASH
} Mem_59_Renesas_FlashType;

/* Enumeration for driver commands */
typedef enum ETag_Mem_59_Renesas_CommandType
{
  MEM_59_RENESAS_COMMAND_NONE = 0,
  MEM_59_RENESAS_COMMAND_ERASE,
  MEM_59_RENESAS_COMMAND_WRITE,
  MEM_59_RENESAS_COMMAND_READ,
  MEM_59_RENESAS_COMMAND_READIMMEDIATE,
  MEM_59_RENESAS_COMMAND_BLANKCHECK,
  MEM_59_RENESAS_COMMAND_HWSPECIFIC_SERVICE
} Mem_59_Renesas_CommandType;

/* Enumeration for returning FCU status values */
typedef enum ETag_Mem_59_Renesas_FcuStatusType
{
  MEM_59_RENESAS_FCU_OK = 0,
  MEM_59_RENESAS_FCU_BUSY,
  MEM_59_RENESAS_FCU_ERR_CONFIGURATION,
  MEM_59_RENESAS_FCU_DF_ERR_ECC_SED,
  MEM_59_RENESAS_FCU_DF_ERR_ECC_DED,
  MEM_59_RENESAS_FCU_CF_ERR_ECC_SED,
  MEM_59_RENESAS_FCU_CF_ERR_ECC_DED,
  MEM_59_RENESAS_FCU_ERR_BLANKCHECK,
  MEM_59_RENESAS_FCU_ERR_INTERNAL,
  MEM_59_RENESAS_FCU_CANCELED,
  MEM_59_RENESAS_FCU_BC_INCONSISTENT,
  MEM_59_RENESAS_FCU_ERR_HW_FAILED
} Mem_59_Renesas_FcuStatusType;

/* Global Structure for Sector Batch type */
typedef struct STag_Mem_59_Renesas_SectorBatchType                                                                      /* PRQA S 3630 # JV-01 */
{
  Mem_59_Renesas_FlashType enFlashType;
  uint32 ulSectorStartAddr;
  uint32 ulSectorEndAddr;
  uint32 ulReadPageSize;
  uint32 ulWritePageSize;
  uint32 ulEraseSectorSize;
  uint32 ulReadBurstSize;
  uint32 ulWriteBurstSize;
  uint32 ulEraseBurstSize;
} Mem_59_Renesas_SectorBatchType;

typedef struct STag_Mem_59_Renesas_HWFuncTableType                                                                      /* PRQA S 3630 # JV-01 */
{
  /* Pointer to hardware resource init function */
  Std_ReturnType (*pHWResourceInit)(Mem_59_Renesas_InstanceIdType LulInstanceId);
  /* Pointer to function processing Mem Job */
  void (*pProcessJob)(Mem_59_Renesas_InstanceIdType LulInstanceId);
  /* Pointer to function processing suspend */
  void (*pProcessSuspend)(Mem_59_Renesas_InstanceIdType LulInstanceId);
  /* Pointer to function processing resume */
  void (*pProcessResume)(Mem_59_Renesas_InstanceIdType LulInstanceId);
  /* Pointer to function processing cancel */
  void (*pHWProcessCancel)(Mem_59_Renesas_InstanceIdType LulInstanceId);
  /* Pointer to function processing HW specific service */
  Std_ReturnType (*pHWSpecificService)(Mem_59_Renesas_InstanceIdType LulInstanceId,
    Mem_59_Renesas_HwServiceIdType LulHwServiceId,
    P2VAR(Mem_59_Renesas_DataType, AUTOMATIC, MEM_APPL_DATA) pDataPtr,                                                  /* PRQA S 3432 # JV-01 */
    P2VAR(Mem_59_Renesas_LengthType, AUTOMATIC, MEM_APPL_DATA) pLengthPtr);                                             /* PRQA S 3432 # JV-01 */
} Mem_59_Renesas_HWFuncTableType;

/* Global Structure for Instance type */
typedef struct STag_Mem_59_Renesas_InstanceType                                                                         /* PRQA S 3630 # JV-01 */
{
  uint32 ulTotalSectorBatch;
  const Mem_59_Renesas_SectorBatchType* pSectorBatch;
  const Mem_59_Renesas_HWFuncTableType *pHWIPFunc;
} Mem_59_Renesas_InstanceType;

/* Global Structure to handle the CFECC Registers */
typedef struct STag_Mem_59_Renesas_CFECCRegType                                                                         /* PRQA S 3630 # JV-01 */
{
/* Error notification control register */
uint32 volatile ulCFERRINT;
uint8 volatile ucReserved00[MEM_59_RENESAS_CFERRINT2CFSSTCLR];
/* 1-bit error status clear register */
uint32 volatile ulCFSSTCLR;
/* Fatal error status clear register */ 
uint32 volatile ulCFDSTCLR;
/* 1-bit error overflow status clear register */
uint32 volatile ulCFOVFCLR;
uint8 volatile ucReserved03[MEM_59_RENESAS_CFOVFCLR2CFSERSTR];
/* 1-bit error status register */
uint32 volatile ulCFSERSTR;
/* Fatal error status register */
uint32 volatile ulCFDERSTR;
/* 1-bit error overflow status register */
uint32 volatile ulCFOVFSTR;
uint8 volatile ucReserved06[MEM_59_RENESAS_CFOVFSTR2CFSERINF];
/* 1-bit error location information register */
uint32 volatile ulCFSERINF;
} Mem_59_Renesas_CFECCRegType;

#if (R_RFD_NUMBER_OF_FACI == MEM_59_RENESAS_FACI_ONE)
/* Global Structure to handle the DFECC Registers */
typedef struct STag_Mem_59_Renesas_DFECCRegType                                                                         /* PRQA S 3630 # JV-01 */
{
  /* ECC control Register */
  uint32 volatile ulDFECCCTL;
  /* Data Flash 1-bit Error Status Register - ECC */
  uint32 volatile ulDFSERSTR;
  /* Data Flash 2-bit Error Status Register - ECC */
  uint32 volatile ulDFDERSTR;
  /* Data Flash 1-bit Error Clear Register - ECC */
  uint32 volatile ulDFSERSTC;
  /* Data Flash 2-bit Error Clear Register - ECC */
  uint32 volatile ulDFDERSTC;
  uint8 volatile ucReserved02[MEM_59_RENESAS_DFERSTC2DFERRINT];
  /* Data Flash Error Interrupt Register - ECC */
  uint32 volatile ulDFERRINT;
  uint8 volatile ucReserved03[MEM_59_RENESAS_DFERRINT2DFTSTCTL];
  /* Test Control Register */
  uint32 volatile ulDFTSTCTL;
  /* Data Flash ECC Control Register */
  uint32 volatile ulDFKCPROT;
} Mem_59_Renesas_DFECCRegType;
#else
typedef struct STag_Mem_59_Renesas_DFECCRegType                                                                         /* PRQA S 3630 # JV-01 */
{
  /* ECC control Register */
  uint32 volatile ulDFECCCTL;
  /* Data Flash Error Status Register - ECC */
  uint32 volatile ulDFERSTR;
  /* Data Flash Error Clear Register - ECC */
  uint32 volatile ulDFERSTC;
  /* Data Flash error overflow status register*/
  uint32 volatile ulDFOVFSTR;
  /* Data Flash error overflow status clear register */
  uint32 volatile ulDFOVFSTC;
  /* Data Flash Error Interrupt Register - ECC */
  uint32 volatile ulDFERRINT;
  /* Data Flash 1st error address register*/
  uint32 volatile ulDFEADR;
  /* Test Control Register */
  uint32 volatile ulDFTSTCTL;
  /* Data Flash ECC Control Register */
  uint32 volatile ulDFKCPROT;
} Mem_59_Renesas_DFECCRegType;
#endif

typedef struct STag_Mem_59_Renesas_ConfigType
{
  /* Pointer to ECC SED callback notification */
  P2FUNC(void, MEM_APPL_CODE, pEccSEDNotificationPointer)(uint32);                                                      /* PRQA S 3432, 1336 # JV-01, JV-01 */
  /* Pointer to ECC DED callback notification */
  P2FUNC(void, MEM_APPL_CODE, pEccDEDNotificationPointer)(uint32);                                                      /* PRQA S 3432, 1336 # JV-01, JV-01 */
  /*  Base Address for ECC CF Registers */
  P2VAR(volatile Mem_59_Renesas_CFECCRegType, TYPEDEF, REGSPACE) pCFECCRegPtr;
  /* Addres of CF_CECCCTL */
  P2VAR(volatile uint32, TYPEDEF, REGSPACE) pCFCECCCTLRegPtr;
  /* Addres of ECCKCPROT */
  P2VAR(volatile uint32, TYPEDEF, REGSPACE) pECCKCPROTRegPtr;
  /* Base Address for ECC DF Registers */
  P2VAR(volatile Mem_59_Renesas_DFECCRegType, TYPEDEF, REGSPACE) pDFECCRegPtr;
  /* Instance config */
  const Mem_59_Renesas_InstanceType* pInstanceConfig;
} Mem_59_Renesas_ConfigType;

typedef struct STag_Mem_59_Renesas_GstVarProperties
{
  /* Variable to store the source address */
  const volatile uint8 * pBufferAddress;
  /* Variable to store the target address */
  volatile uint32 ulSrcDestAddress;
  /* Variable to store the read address */
  volatile uint32 ulReadAddress;
  /* Variable to hold the erase/write start address */
  volatile uint32 ulJobStartAddress;
  /* Variable to hold the erase/write end address */
  volatile uint32 ulJobEndAddress;
  /* Variable to store the requested number of bytes to be processed */
  volatile uint32 ulRequestedLength;
  /* Variable to store the requested commands */
  volatile Mem_59_Renesas_CommandType enGenCommand;
  /* Variable to store sector batch index */
  volatile uint32 ulSectorBatchIdx;
  /* Variable to store the RFD request state */
  volatile boolean blHwRequestedFlg;
  /* Variable to store the type of Flash */
  volatile Mem_59_Renesas_FlashType enFlashType;
} Mem_59_Renesas_GstVarProperties;
#endif /* MEM_59_RENESAS_TYPES_H */

/***********************************************************************************************************************
**                                                    End Of File                                                     **
***********************************************************************************************************************/
