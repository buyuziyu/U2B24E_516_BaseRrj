/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Spi_Ram.h                                                                                           */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* Copyright(c) 2020-2025 Renesas Electronics Corporation.                                                            */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains the extern declarations of global RAM variables of SPI Driver                                   */
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
 *                     : Add Global variable Spi_GucKernalCoreId for supporting multi core multi postbuid variant
 * 2.1.0:  27/02/2024  : Update SW-VERSION to 2.1.0
 * 2.0.2:  14/12/2023  : Update SW-VERSION to 2.0.2
 * 2.0.1:  11/10/2023  : Remove SPI_AR_R21_11_VERSION
 *                       Update SW-VERSION to 2.0.1
 *                       Update pre-condition SPI_AR_VERSION == SPI_AR_R22_11_VERSION for 
 *                       SPI_LEVEL_DELIVERED == SPI_LEVEL_1 to Spi_GulCancelingHWUnits
 * 2.0.0:  28/08/2023  : Remove SPI_INSTANCE_INDEX
 *         25/07/2023  : Update from "Spi_Mapping.h to "Spi_MemMap.h".
 *         17/07/2023  : Update pre-condition SPI_AR_VERSION == SPI_AR_R21_11_VERSION for 
 *                       SPI_LEVEL_DELIVERED == SPI_LEVEL_1 to Spi_GulCancelingHWUnits
 * 1.4.2:  02/03/2022  : Merge QAC
 * 1.3.2:  06/09/2021  : Update QAC contents
 *         30/08/2021  : Update header file macro to call file multiple times
 *                       Update to include Spi_Mapping.h instead of Spi_MemMap.h
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

/**********************************************************************************************************************/

/**********************************************************************************************************************/

#ifndef SPI_RAM_H
#define SPI_RAM_H

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
#include "Spi_LTTypes.h"
#include "Spi_sDMAC_LLDriver.h"
#include "Spi_PBTypes.h"
#include "Spi_Scheduler.h"

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define SPI_RAM_AR_RELEASE_MAJOR_VERSION    SPI_AR_RELEASE_MAJOR_VERSION
#define SPI_RAM_AR_RELEASE_MINOR_VERSION    SPI_AR_RELEASE_MINOR_VERSION
#define SPI_RAM_AR_RELEASE_REVISION_VERSION SPI_AR_RELEASE_REVISION_VERSION

/* File version information */
#define SPI_RAM_SW_MAJOR_VERSION            SPI_SW_MAJOR_VERSION
#define SPI_RAM_SW_MINOR_VERSION            SPI_SW_MINOR_VERSION

/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/
#define SPI_START_SEC_VAR_INIT_BOOLEAN
#include "Spi_MemMap.h"

/* Global variable to store the initialization status of SPI Driver */
extern volatile VAR(boolean, SPI_VAR_INIT) Spi_GblInitialized;

#define SPI_STOP_SEC_VAR_INIT_BOOLEAN
#include "Spi_MemMap.h"

#define SPI_START_SEC_VAR_NO_INIT_PTR
#include "Spi_MemMap.h"

/* Global variable to store config pointer */
extern P2CONST(Spi_ConfigType, SPI_VAR_NO_INIT, SPI_CONFIG_DATA) volatile Spi_GpConfigPtr;

/* Global variable to store first channel structure */
extern P2CONST(Spi_ChannelConfigType, SPI_VAR_NO_INIT, SPI_CONFIG_DATA) volatile Spi_GpFirstChannel;

/* Global variable to store first job structure */
extern P2CONST(Spi_JobConfigType, SPI_VAR_NO_INIT, SPI_CONFIG_DATA) volatile Spi_GpFirstJob;

/* Global variable to store first sequence structure */
extern P2CONST(Spi_SeqConfigType, SPI_VAR_NO_INIT, SPI_CONFIG_DATA) volatile Spi_GpFirstSeq;

/* Global variable to store HWUnit information table */
extern P2CONST(Spi_HWUnitInfoType, SPI_VAR_NO_INIT, SPI_CONFIG_DATA) volatile Spi_GpFirstHWUnit;

#if (SPI_DMA_CONFIGURED == STD_ON)
/* Global pointer variable for HW group configuration */
extern P2CONST(Spi_DmaConfigType, SPI_VAR_NO_INIT, SPI_CONFIG_DATA) volatile Spi_GpFirstDMAUnit;
#endif

/* Global pointer variable for HW-dependent function pointer table */
extern P2CONST(Spi_HwConfigType, SPI_VAR_NO_INIT, SPI_CONST) volatile Spi_GpHwConfig;

#define SPI_STOP_SEC_VAR_NO_INIT_PTR
#include "Spi_MemMap.h"

#define SPI_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Spi_MemMap.h"

#if (SPI_LEVEL_DELIVERED == SPI_LEVEL_2) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_1)
/* Global variable to store the asynchronous transmission mechanism */
extern volatile VAR(Spi_AsyncModeType, SPI_VAR_NO_INIT) Spi_GenAsyncMode;
#endif

/* Hardware statuses */
extern volatile VAR(Spi_HWStatusType, SPI_VAR_NO_INIT) Spi_GaaHWStatus[SPI_MAX_HWUNIT];

#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL_1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2))
/* Queue structures */
extern volatile VAR(Spi_QueueType, SPI_VAR_NO_INIT) Spi_GaaQueue[SPI_MAX_QUEUE];
#endif

/* Sequence statuses and results */
extern volatile VAR(Spi_SeqStatusType, SPI_VAR_NO_INIT) Spi_GaaSeqStatus[SPI_MAX_SEQUENCE];

/* Job statuses and results */
extern volatile VAR(Spi_JobStatusType, SPI_VAR_NO_INIT) Spi_GaaJobStatus[SPI_MAX_JOB];

#if (SPI_EBDATA_SIZE > 0)
extern volatile VAR(Spi_EBDataType, SPI_VAR_NO_INIT) Spi_GaaEBData[SPI_EBDATA_SIZE];
#endif

#define SPI_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Spi_MemMap.h"

#define SPI_START_SEC_VAR_NO_INIT_32
#include "Spi_MemMap.h"

/* Bit array indicates active HW unit index
- The lower 16-bits are for synchronous transmission
- The upper 16-bits are for asynchronous transmission */
extern volatile VAR(uint32, SPI_VAR_NO_INIT) Spi_GulActiveHWUnits;

#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL_1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2))
/* Bit array indicates active Queues */
extern volatile VAR(uint32, SPI_VAR_NO_INIT) Spi_GulAllQueueSts;
/* Bit array indicates active Sequences */
extern volatile VAR(uint32, SPI_VAR_NO_INIT) Spi_GaaActiveSequence[SPI_BITS_TO_WORDS(SPI_MAX_SEQUENCE)];
#endif

#if (SPI_MAX_CHANNEL_BUFFER_SIZE > 0U)
/* Channel buffer, includes all tx and rx buffers for all channels
   This buffer should be aligned to 4 byte for 32 bit access */
extern volatile VAR(uint32, SPI_VAR_NO_INIT) Spi_GaaChannelBuffer[SPI_MAX_CHANNEL_BUFFER_SIZE / sizeof(uint32)];
#endif

#if (SPI_DMA_CONFIGURED == STD_ON)
/* Dummy destination if read data is not necessary */
extern volatile VAR(uint32, SPI_VAR_NO_INIT) Spi_GulDmaRxData;
#endif

#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL_2) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_1)) && (SPI_FORCE_CANCEL_API == STD_ON)
/* Bit array indicates HWUnits is being canceled by Spi_ForceCancel */
extern volatile VAR(uint32, SPI_VAR_NO_INIT) Spi_GulCancelingHWUnits;
#endif

#define SPI_STOP_SEC_VAR_NO_INIT_32
#include "Spi_MemMap.h"

#if (SPI_MULTI_CORE_SUPPORT == STD_ON)
#define SPI_START_SEC_VAR_INIT_8
#include "Spi_MemMap.h"
/* Holds the kernal core ID in multicore */
extern VAR(uint8, SPI_VAR_INIT) Spi_GucKernalCoreId;
#define SPI_STOP_SEC_VAR_INIT_8
#include "Spi_MemMap.h"
#endif

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/

#endif /* SPI_RAM_H */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
