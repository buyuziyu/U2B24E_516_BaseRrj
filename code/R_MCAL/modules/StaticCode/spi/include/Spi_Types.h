/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Spi_Types.h                                                                                         */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* Copyright(c) 2020-2025 Renesas Electronics Corporation.                                                            */
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
 * 2.5.1:  30/06/2025  : Remove SW-VERSION in file header
 * 2.5.0:  30/06/2025  : Update SW-VERSION for RH850/Ver21.01.00(D) U2Ax release
 * 2.4.0:  31/05/2025  : Update SW-VERSION for RH850/Ver21.01.01 U2Cx release
 * 2.3.2:  30/04/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 Release
 * 2.3.1:  31/03/2025  : Add new QAC msg: 4641 to support QAC 11.6.0
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00(D) U2Bx Final Release
 * 2.1.3:  31/10/2024  : Update SW-VERSION up to 2.1.3
 * 2.1.2:  30/09/2024  : Update SW-VERSION up to 2.1.2
 * 2.1.1:  28/08/2024  : Support AR2211: update macro file definition,
 *                     : Remove QAC messages (2:0841) to fix redundant QAC messages
 *                     : Increase SW-VERSION up to 2.0.3
 *                     : Add item "ucKernelCoreId", "ucNoOfQueues" in struct Spi_ConfigType 
 *                     : Remove QAC message 1534, 1536
 * 2.1.0:  27/02/2024  : Update SW-VERSION to 2.1.0
 * 2.0.2:  14/12/2023  : Update SW-VERSION to 2.0.2
 * 2.0.1:  22/10/2023  : Update QAC message 1534, 1536 support Amendment 2
 *                       Update SW-VERSION to 2.0.1
 * 2.0.0:  28/08/2023  : Remove SPI_INSTANCE_INDEX
 *         25/07/2023  : Support Multicore: Add #define SPI_ONE
 *         10/05/2023  : Add range enum of ETag_Spi_JobResultType, ETag_Spi_SeqResultType and condition to cover 
 *                       ETag_Spi_AsyncModeType.
 * 1.4.4:  20/06/2022  : Add Definition of chip select type
 * 1.4.2:  02/03/2022  : Merge QAC
 * 1.3.2:  06/09/2021  : Update QAC contents
 *         30/08/2021  : Update header file macro to call file multiple times
 * 1.3.1:  02/07/2021  : Add QAC message 9.5.0
 *                       Format source code to 120 characters 
 * 1.2.0:  17/07/2020  : Release
 * 1.1.0:  19/06/2020  : Release
 * 1.0.0:  24/03/2020  : Initial Version
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:4641)    : The identifier '%1s' could conflict in the future with the name of a macro in '<%2s>'.       */
/* Rule                : CERTC 3.6.0 Rule DCL37, CWE 3.6.0 Rule CWE-398, CWE-569                                      */
/* JV-01 Justification : This message is just a notice to avoid using this identifier as a macro in standard library  */
/*                       in the future.                                                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
#ifndef SPI_TYPES_H
#define SPI_TYPES_H

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/

/* AUTOSAR Release version information */
#define SPI_TYPES_AR_RELEASE_MAJOR_VERSION    SPI_AR_RELEASE_MAJOR_VERSION
#define SPI_TYPES_AR_RELEASE_MINOR_VERSION    SPI_AR_RELEASE_MINOR_VERSION
#define SPI_TYPES_AR_RELEASE_REVISION_VERSION SPI_AR_RELEASE_REVISION_VERSION

/* File version information */
#define SPI_TYPES_SW_MAJOR_VERSION            SPI_SW_MAJOR_VERSION
#define SPI_TYPES_SW_MINOR_VERSION            SPI_SW_MINOR_VERSION

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/
#define SPI_LEVEL_0                           0U
#define SPI_LEVEL_1                           1U
#define SPI_LEVEL_2                           2U
#define SPI_IB                                0U
#define SPI_EB                                1U
#define SPI_IBEB                              2U
#define SPI_ZERO                              0x00U
#define SPI_ONE                               0x01U

/***********************************************************************************************************************
**                                                  DEM TYPE CASTING                                                  **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/
/***********************************************************************************************************************
**                                                SPI TYPE DEFINITION                                                 **
***********************************************************************************************************************/

/* Definition of status type */
typedef enum ETag_Spi_StatusType                                                                                        /* PRQA S 4641 # JV-01 */
{
  /* The SPI Handler/Driver is not initialized or not usable */
  SPI_UNINIT = 0,
  /* The SPI Handler/Driver is not currently transmitting any Job */
  SPI_IDLE,
  /* The SPI Handler/Driver is performing a SPI Job */
  SPI_BUSY
} Spi_StatusType;

typedef enum ETag_Spi_JobResultType                                                                                     /* PRQA S 4641 # JV-01 */
{
  /* The last transmission of the Job has been finished successfully */
  SPI_JOB_OK = 0x00U,
  /* The Job is ongoing */
  SPI_JOB_PENDING = 0x01U,
  /* The last transmission of the Job has failed */
  SPI_JOB_FAILED = 0x02U,
  /* The transmission request has been accepted but not started yet */
  SPI_JOB_QUEUED = 0x03U
} Spi_JobResultType;

typedef enum ETag_Spi_SeqResultType                                                                                     /* PRQA S 4641 # JV-01 */
{
  /* The last transmission of the Sequence has been finished successfully */
  SPI_SEQ_OK = 0x00U,
  /* The Sequence is ongoing or queued but not finished yet */
  SPI_SEQ_PENDING = 0x01U,
  /* The last transmission of the Sequence has failed */
  SPI_SEQ_FAILED = 0x02U,
  /* The last transmission of the Sequence has been canceled */
  SPI_SEQ_CANCELED = 0x03U
} Spi_SeqResultType;

#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL_2)||(SPI_LEVEL_DELIVERED == SPI_LEVEL_1))
/* Definition of type for asynchronous mode */
typedef enum ETag_Spi_AsyncModeType                                                                                     /* PRQA S 4641 # JV-01 */
{
  /* Polling mode  for async transmission */
  SPI_POLLING_MODE = 0x00U,
  /* Interrupt mode for async transmission */
  SPI_INTERRUPT_MODE = 0x01U
} Spi_AsyncModeType;
#endif

/* Definition of chip select type */
typedef enum ETagSpi_CSType                                                                                             /* PRQA S 4641 # JV-01 */
{
  /* Master chip select handling is disabled */
  SPI_DISABLE_CS = 0,
  /* Chip select is handled by general purpose IO */
  SPI_GPIO_CS,
  /* Chip select is handled by peripheral HW engine */
  SPI_PERIPHERAL_ENGINE_CS
} Spi_CSType;

/* Definition of type for application data buffer elements */
typedef uint8 Spi_DataBufferType;

/* Definition of type for number of data elements */
typedef uint16 Spi_NumberOfDataType;

/* Definition of type for channel ID */
typedef uint8 Spi_ChannelType;

/* Definition of type for job ID */
typedef uint16 Spi_JobType;

/* Definition of type for sequence ID */
typedef uint8 Spi_SequenceType;

/* Definition of type for hardware unit ID */
typedef uint8 Spi_HWUnitType;

/***********************************************************************************************************************
**                                               Structure declarations                                               **
***********************************************************************************************************************/

/* Data Structure for SPI Handler/Driver initialization */
typedef struct STag_Spi_ConfigType
{
  /* Database start value */
  uint32 ulStartOfDbToc;
  /* Element number of pHWUnitInfo */
  uint8 ucNoOfHWUnits;
  /* Element number of queue */
  uint8 ucNoOfQueues;
  /* Element number of pChannelConfig */
  uint8 ucNoOfChannels;
  /* Element number of pJobConfig */
  uint16 usNoOfJobs;
  /* Element number of pSequenceConfig */
  uint8 ucNoOfSequences;
  #if (SPI_DMA_CONFIGURED == STD_ON)
  /* Element number of pDMAUnitInfo */
  uint8 ucNoOfDMAChannels;
  #endif

  #if (SPI_MULTI_CORE_SUPPORT == STD_ON)
  /* Hold the configured kernel core ID */
  uint8 ucKernelCoreId;
  #endif /* End of (SPI_MULTI_CORE_SUPPORT == STD_ON) */

  /* Pointer to HW Info configuration */
  P2CONST(void, TYPEDEF, SPI_CONFIG_DATA) pHWUnitInfo;
  /* Pointer to Channel configuration */
  P2CONST(void, TYPEDEF, SPI_CONFIG_DATA) pChannelConfig;
  /* Pointer to Job configuration */
  P2CONST(void, TYPEDEF, SPI_CONFIG_DATA) pJobConfig;
  /* Pointer to Sequence configuration */
  P2CONST(void, TYPEDEF, SPI_CONFIG_DATA) pSequenceConfig;
  #if (SPI_DMA_CONFIGURED == STD_ON)
  /* Pointer to DMA configuration */
  P2CONST(void, TYPEDEF, SPI_CONFIG_DATA) pDMAUnitInfo;
  #endif
  /* Timeout loop count */
  uint32 ulTimeoutCount;
  #if (SPI_DMA_CONFIGURED == STD_ON)
  /* Lookup table to get HWUnitIndex from physical index of DMA*/
  P2CONST(uint8, TYPEDEF, SPI_CONFIG_DATA) pDMAToHWUnit;
  #endif
  /* Pointer to HW-dependent configuration */
  P2CONST(void, TYPEDEF, SPI_CONST) pHwConfig;
} Spi_ConfigType;

#endif /* SPI_TYPES_H */

/***********************************************************************************************************************
**                                                    End Of File                                                     **
***********************************************************************************************************************/
