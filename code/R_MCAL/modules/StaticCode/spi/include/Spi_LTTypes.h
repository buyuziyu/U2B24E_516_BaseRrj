/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Spi_LTTypes.h                                                                                       */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* Copyright(c) 2020-2025 Renesas Electronics Corporation.                                                            */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains the type definitions for link time parameters                                                   */
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
 * 2.3.1:  31/03/2025  : Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02 Release
 * 2.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00(D) U2Bx Final Release
 * 2.1.3:  31/10/2024  : Update SW-VERSION up to 2.1.3
 * 2.1.2:  30/09/2024  : Update SW-VERSION up to 2.1.2
 * 2.1.1:  28/08/2024  : Support AR2211: update macro file definition,
 *                     : Remove QAC messages (2:0841) to fix redundant QAC messages
 *                     : Increase SW-VERSION up to 2.0.3
 *                     : Remove QAC message 1534, 1536
 * 2.1.0:  27/02/2024  : Update SW-VERSION to 2.1.0
 * 2.0.2:  14/12/2023  : Update SW-VERSION to 2.0.2
 * 2.0.1:  22/10/2023  : Update QAC message 1534, 1536 support Amendment 2
 *                       Update SW-VERSION to 2.0.1
 * 2.0.0:  28/08/2023  : Remove SPI_INSTANCE_INDEX
 * 1.4.2:  02/03/2022  : Merge QAC
 * 1.3.2:  06/09/2021  : Update QAC contents
 *         30/08/2021  : Update header file macro to call file multiple times
 * 1.3.1:  02/07/2021  : Format source code to 120 characters
 *                       Improve Violation tag (remove START/END)
 * 1.2.0:  30/07/2020  : Release
 *         28/07/2020  : Add QAC 9.3.1 comment.
 * 1.1.0:  19/06/2020  : Release
 * 1.0.1:  14/04/2020  : Add usTxChannelOffset in Spi_HWStatusType
 * 1.0.0:  24/03/2020  : Initial Version
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE Rule CWE-398, CWE-569                                            */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is accepted. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

#ifndef SPI_LTTYPES_H
#define SPI_LTTYPES_H

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR Release version information */
#define SPI_LTTYPES_AR_RELEASE_MAJOR_VERSION    SPI_AR_RELEASE_MAJOR_VERSION
#define SPI_LTTYPES_AR_RELEASE_MINOR_VERSION    SPI_AR_RELEASE_MINOR_VERSION
#define SPI_LTTYPES_AR_RELEASE_REVISION_VERSION SPI_AR_RELEASE_REVISION_VERSION

/* File version information */
#define SPI_LTTYPES_SW_MAJOR_VERSION            SPI_SW_MAJOR_VERSION
#define SPI_LTTYPES_SW_MINOR_VERSION            SPI_SW_MINOR_VERSION

/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/
#define SPI_DBTOC_VALUE                                                                  \
  (uint32)(((uint32)SPI_VENDOR_ID_VALUE << 22U) | ((uint32)SPI_MODULE_ID_VALUE << 14U) | \
           ((uint32)SPI_SW_MAJOR_VERSION_VALUE << 8U) | ((uint32)SPI_SW_MINOR_VERSION_VALUE << 3U))

#define SPI_TRUE            (boolean)1
#define SPI_FALSE           (boolean)0
#define SPI_MAX_PRIORITY    (uint8)0x03
#define SPI_INVALID_DMAUNIT (uint8)0xFF

/* Structure for storing external buffer attributes */
typedef struct STag_Spi_EBDataType
{
  /* Pointer to external buffer source data */
  P2CONST(Spi_DataBufferType, TYPEDEF, SPI_APPL_DATA) pSrcPtr;
  /* Pointer to external buffer destination data */
  P2VAR(Spi_DataBufferType, TYPEDEF, SPI_APPL_DATA) pDestPtr;                                                           /* PRQA S 3432 # JV-01 */
  /* Length of external buffer */
  Spi_NumberOfDataType usEBLength;
} Spi_EBDataType;

/* Structure for the status for each HW unit */
typedef struct STag_Spi_HWStatusType
{
  #if (SPI_HW_STATUS_API == STD_ON)
  /* Whether this HWUnit is active */
  boolean blActive;
  #endif
  /* Index of Sequence which is going on this HWUnit */
  Spi_SequenceType ucOngoingSeqIndex;
  /* Index of Job which is going on this HWUnit */
  Spi_JobType usOngoingJobIndex;
  /* Index of Channel which should be accessed at the next transmission */
  Spi_ChannelType ucTxChannelCount;
  /* Index of Channel which should be accessed at the next reception */
  Spi_ChannelType ucRxChannelCount;
  /* Number of remained tx data elements of the current Channel */
  Spi_NumberOfDataType usRemainedTxCount;
  /* Number of remained rx data elements of the current Channel */
  Spi_NumberOfDataType usRemainedRxCount;
  #if ((STD_ON == SPI_MSPI_CONFIGURED) && (STD_ON == SPI_FIXED_BUFFER_MODE))
  /* Offset of Channel in MSPI RAM to start transmission */
  Spi_NumberOfDataType usTxChannelOffset;
  #endif
  /* Pointer to tx buffer */
  volatile P2CONST(Spi_DataBufferType, TYPEDEF, SPI_APPL_DATA) pTxPtr;
  /* Pointer to rx buffer */
  volatile P2VAR(Spi_DataBufferType, TYPEDEF, SPI_APPL_DATA) pRxPtr;                                                    /* PRQA S 3432 # JV-01 */
} Spi_HWStatusType;

/***********************************************************************************************************************
**                                        Extern declarations for Global Data                                         **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                             Global Function Prototypes                                             **
***********************************************************************************************************************/

#endif /* SPI_LTTYPES_H */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
