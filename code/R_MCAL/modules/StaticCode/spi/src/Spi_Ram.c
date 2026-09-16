/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Spi_Ram.c                                                                                           */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* Copyright(c) 2020-2025 Renesas Electronics Corporation.                                                            */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains global variable definitions of SPI Driver                                                       */
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
 * 2.1.1:  28/08/2024  : Support AR2211: update macro condition SPI_AR_R22_11_VERSION
 *                     : Remove QAC messages (2:0857) to fix redundant QAC messages
 *                     : Remove QAC message 1531 and add new QAC messages 1533
 *                     : Increase SW-VERSION up to 2.0.3
 *                       Add new "Spi_GucKernalCoreId" to support for multicore with multiple post build variant
 * 2.1.0:  27/02/2024  : Update SW-VERSION to 2.1.0
 * 2.0.2:  14/12/2023  : Update SW-VERSION to 2.0.2
 * 2.0.1:  23/10/2023  : Remove SPI_AR_R21_11_VERSION
 *         11/10/2023  : Update pre-condition SPI_AR_VERSION == SPI_AR_R22_11_VERSION for 
 *                       SPI_LEVEL_DELIVERED == SPI_LEVEL_1 in Spi_GulCancelingHWUnits
 *                       Update SW-VERSION to 2.0.1
 * 2.0.0:  17/07/2023  : Update pre-condition SPI_AR_VERSION == SPI_AR_R21_11_VERSION for 
 *                       SPI_LEVEL_DELIVERED == SPI_LEVEL_1 in Spi_GulCancelingHWUnits
 * 1.3.2:  04/09/2021  : Replace the inclusion of Spi_MemMap.h with Spi_Mapping.h 
 * 1.3.1:  02/07/2021  : Format source code to 120 characters
 *                       Improve Violation tag (remove START/END)
 * 1.2.0:  30/07/2020  : Release
 *         28/07/2020  : Add QAC 9.3.1 comment.
 * 1.1.0:  19/06/2020  : Release
 * 1.0.0:  24/03/2020  : Initial Version
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
#include "Spi.h"
#include "Spi_Ram.h"

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define SPI_RAM_C_AR_RELEASE_MAJOR_VERSION    SPI_AR_RELEASE_MAJOR_VERSION_VALUE
#define SPI_RAM_C_AR_RELEASE_MINOR_VERSION    SPI_AR_RELEASE_MINOR_VERSION_VALUE
#define SPI_RAM_C_AR_RELEASE_REVISION_VERSION SPI_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define SPI_RAM_C_SW_MAJOR_VERSION            SPI_SW_MAJOR_VERSION_VALUE
#define SPI_RAM_C_SW_MINOR_VERSION            SPI_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (SPI_RAM_AR_RELEASE_MAJOR_VERSION != SPI_RAM_C_AR_RELEASE_MAJOR_VERSION)
#error "Spi_Ram.c : Mismatch in Release Major Version"
#endif

#if (SPI_RAM_AR_RELEASE_MINOR_VERSION != SPI_RAM_C_AR_RELEASE_MINOR_VERSION)
#error "Spi_Ram.c : Mismatch in Release Minor Version"
#endif

#if (SPI_RAM_AR_RELEASE_REVISION_VERSION != SPI_RAM_C_AR_RELEASE_REVISION_VERSION)
#error "Spi_Ram.c : Mismatch in Release Revision Version"
#endif

#if (SPI_RAM_SW_MAJOR_VERSION != SPI_RAM_C_SW_MAJOR_VERSION)
#error "Spi_Ram.c : Mismatch in Software Major Version"
#endif

#if (SPI_RAM_SW_MINOR_VERSION != SPI_RAM_C_SW_MINOR_VERSION)
#error "Spi_Ram.c : Mismatch in Software Minor Version"
#endif

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (4:5087)    : Use of #include directive after code fragment.                                               */
/* Rule                : MISRA C:2012 Rule-20.1                                                                       */
/* JV-01 Justification : This is done as per Memory Requirement, (MEMMAP003 - Specification of Memory Mapping).       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1533)    : The object 'entity' is only referenced by function 'func'.                                   */
/* Rule                : MISRA C:2012 Rule-8.9, CWE Rule CWE-398, CWE-569                                             */
/* JV-01 Justification : This is accepted, due to the object is defined in seperated cource C file to followed        */
/*                       coding rule                                                                                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/
#define SPI_START_SEC_VAR_INIT_BOOLEAN
#include "Spi_MemMap.h"

/* Global variable to store the initialization status of SPI Driver */
volatile VAR(boolean, SPI_VAR_INIT) Spi_GblInitialized = SPI_FALSE;

#define SPI_STOP_SEC_VAR_INIT_BOOLEAN
#include "Spi_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define SPI_START_SEC_VAR_NO_INIT_PTR
#include "Spi_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Global variable to store config pointer */
P2CONST(Spi_ConfigType, SPI_VAR_NO_INIT, SPI_CONFIG_DATA)
volatile Spi_GpConfigPtr;

/* Global variable to store first channel structure */
P2CONST(Spi_ChannelConfigType, SPI_VAR_NO_INIT, SPI_CONFIG_DATA)
volatile Spi_GpFirstChannel;

/* Global variable to store first job structure */
P2CONST(Spi_JobConfigType, SPI_VAR_NO_INIT, SPI_CONFIG_DATA)
volatile Spi_GpFirstJob;

/* Global variable to store first sequence structure */
P2CONST(Spi_SeqConfigType, SPI_VAR_NO_INIT, SPI_CONFIG_DATA)
volatile Spi_GpFirstSeq;

/* Global variable to store HWUnit information table */
P2CONST(Spi_HWUnitInfoType, SPI_VAR_NO_INIT, SPI_CONFIG_DATA)
volatile Spi_GpFirstHWUnit;

#if (SPI_DMA_CONFIGURED == STD_ON)
/* Global pointer variable for HW group configuration */
P2CONST(Spi_DmaConfigType, SPI_VAR_NO_INIT, SPI_CONFIG_DATA)
volatile Spi_GpFirstDMAUnit;
#endif

/* Global pointer variable for HW-dependent function pointer table */
P2CONST(Spi_HwConfigType, SPI_VAR_NO_INIT, SPI_CONST)
volatile Spi_GpHwConfig;

#define SPI_STOP_SEC_VAR_NO_INIT_PTR
#include "Spi_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define SPI_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Spi_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#if (SPI_LEVEL_DELIVERED == SPI_LEVEL_2) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_1)
/* Global variable to store the asynchronous transmission mechanism */
volatile VAR(Spi_AsyncModeType, SPI_VAR_NO_INIT) Spi_GenAsyncMode;
#endif

/* Hardware statuses */
volatile VAR(Spi_HWStatusType, SPI_VAR_NO_INIT) Spi_GaaHWStatus[SPI_MAX_HWUNIT];

#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL_1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2))
/* Queue structures */
volatile VAR(Spi_QueueType, SPI_VAR_NO_INIT) Spi_GaaQueue[SPI_MAX_QUEUE];
#endif

/* Sequence statuses and results */
volatile VAR(Spi_SeqStatusType, SPI_VAR_NO_INIT) Spi_GaaSeqStatus[SPI_MAX_SEQUENCE];

/* Job statuses and results */
volatile VAR(Spi_JobStatusType, SPI_VAR_NO_INIT) Spi_GaaJobStatus[SPI_MAX_JOB];

#if (SPI_EBDATA_SIZE > 0)
volatile VAR(Spi_EBDataType, SPI_VAR_NO_INIT) Spi_GaaEBData[SPI_EBDATA_SIZE];
#endif

#define SPI_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Spi_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define SPI_START_SEC_VAR_NO_INIT_32
#include "Spi_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Bit array indicates active HW unit index
- The lower 16-bits are for synchronous transmission
- The upper 16-bits are for asynchronous transmission */
volatile VAR(uint32, SPI_VAR_NO_INIT) Spi_GulActiveHWUnits;

#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL_1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2))
/* Bit array indicates active Queues */
volatile VAR(uint32, SPI_VAR_NO_INIT) Spi_GulAllQueueSts;
/* Bit array indicates active Sequences */
volatile VAR(uint32, SPI_VAR_NO_INIT) Spi_GaaActiveSequence[SPI_BITS_TO_WORDS(SPI_MAX_SEQUENCE)];
#endif

#if (SPI_MAX_CHANNEL_BUFFER_SIZE > 0U)
/* Channel buffer, includes all tx and rx buffers for all channels
   This buffer should be aligned to 4 byte for 32 bit access */
volatile VAR(uint32, SPI_VAR_NO_INIT) Spi_GaaChannelBuffer[SPI_MAX_CHANNEL_BUFFER_SIZE / sizeof(uint32)];
#endif

#if (SPI_DMA_CONFIGURED == STD_ON)
/* Dummy destination if read data is not necessary */
volatile VAR(uint32, SPI_VAR_NO_INIT) Spi_GulDmaRxData;                                                                 /* PRQA S 1533 # JV-01 */
#endif

#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL_2) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_1)) && (SPI_FORCE_CANCEL_API == STD_ON)
/* Bit array indicates HWUnits is being canceled by Spi_ForceCancel */
volatile VAR(uint32, SPI_VAR_NO_INIT) Spi_GulCancelingHWUnits;
#endif

#define SPI_STOP_SEC_VAR_NO_INIT_32
#include "Spi_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#if (SPI_MULTI_CORE_SUPPORT == STD_ON)
#define SPI_START_SEC_VAR_INIT_8
#include "Spi_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/* Holds the kernal core ID in multicore */
VAR(uint8, SPI_VAR_INIT) Spi_GucKernalCoreId = SPI_ZERO;
#define SPI_STOP_SEC_VAR_INIT_8
#include "Spi_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
