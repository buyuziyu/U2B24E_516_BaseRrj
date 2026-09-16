/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Spi_PBTypes.h                                                                                       */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* Copyright(c) 2020-2025 Renesas Electronics Corporation.                                                            */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains the type definitions for post-build time parameters                                             */
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
 * 2.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00(D) U2Bx Final Release
 * 2.1.3:  31/10/2024  : Update SW-VERSION up to 2.1.3
 * 2.1.2:  30/09/2024  : Update SW-VERSION up to 2.1.2
 * 2.1.1:  28/08/2024  : Support AR2211: update macro file definition, remove condition macro SPI_AR_431_VERSION
 *                     : Remove QAC messages (2:0841) to fix redundant QAC messages
 *                     : Increase SW-VERSION up to 2.0.3
 *                     : Remove QAC message 1534, 1536
 * 2.1.0:  27/02/2024  : Update SW-VERSION to 2.1.0
 * 2.0.2:  14/12/2023  : Update SW-VERSION to 2.0.2
 * 2.0.1:  23/10/2023  : Remove SPI_AR_R21_11_VERSION
 *         22/10/2023  : Update QAC message 1534, 1536 support Amendment 2
 *         11/10/2023  : Update SPI_AR_R22_11_VERSION
 *                       Update SW-VERSION to 2.0.1
 *                       Update pre-condition SPI_AR_VERSION == SPI_AR_R22_11_VERSION for 
 *                       SPI_LEVEL_DELIVERED == SPI_LEVEL_1 to pHwMainFunction_Handling
 * 2.0.0:  12/08/2023  : Change #include SCHM_SPI_HEADER to #include "SchM_Spi.h"
 *                       Support Multicore: 
 *                       Add macro ((SPI_DEV_ERROR_DETECT == STD_ON) && (SPI_MULTI_CORE_SUPPORT == STD_ON)
 *                       Add uint8 ucCoreMask;
 *                       Add pre-compile condition check for SPI_ENTER/EXIT_CRITICAL_SECTION. 
 *                       Remove #ifdef SPI_INSTANCE_INDEX 
 *         17/07/2023  : Update pre-condition SPI_AR_VERSION == SPI_AR_R21_11_VERSION for 
 *                       SPI_LEVEL_DELIVERED == SPI_LEVEL_1 to pHwMainFunction_Handling
 *         19/06/2023  : Added marco SPI_SYNC_HW_BITS
 *         26/05/2023  : Change SPI_AR_2111_VERSION to SPI_AR_R21_11_VERSION
 *         06/05/2023  : Update SPI_AR_R21_11_VERSION
 * 1.4.4:  20/06/2022  : Added enCSType, pPSRReg, ulPortPinMask, ulClk2CsCount, blCsPolarity into Spi_JobConfigType
 *                       Added macro SPI_CS_HIGH, SPI_CS_LOW
 * 1.4.2:  02/03/2022  : Merge QAC
 * 1.4.1:  09/09/2021  : Change ucCSInfo to usCSInfo and SW-VERSION to 1.4.1
 * 1.3.2:  06/09/2021  : Update QAC contents
 *         30/08/2021  : Update header file macro to call file multiple times
 *                       Update to include SCHM_SPI_HEADER instead of "SchM_Spi.h"
 * 1.3.1:  02/07/2021  : Add QAC message 9.5.0
 *                       Format source code to 120 characters
 *                       Improve Violation tag (remove START/END) 
 * 1.2.0:  30/07/2020  : Release
 *         28/07/2020  : Add QAC 9.3.1 comment.
 * 1.1.0:  19/06/2020  : Release
 * 1.0.1:  19/05/2020  : Move pHwDMACompleteISR outside of pre-compile check for Level 1 and Level 2 to support DMA at
 *                       Level 0.
 * 1.0.0:  24/03/2020  : Initial Version
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:3471)    : Some uses of this function-like macro look like they could be replaced by equivalent         */
/*                       function calls.                                                                              */
/* Rule                : MISRA C:2012 Dir-4.9                                                                         */
/* JV-01 Justification : This message indicates that a candidate macro may be suitable for replacement by a           */
/*                       function, based on an actual call-site and the arguments passed to it there.                 */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3472)    : All toplevel uses of this function-like macro look like they could be replaced by            */
/*                       equivalent function calls.                                                                   */
/* Rule                : MISRA C:2012 Dir-4.9                                                                         */
/* JV-01 Justification : This message indicates that a candidate macro may be suitable for replacement by a           */
/*                       function, based on an actual call-site and the arguments passed to it there                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0342)    : Using the glue operator '##'.                                                                */
/* Rule                : CERTCCM PRE05, MISRA C:2012 Rule-20.10                                                       */
/* JV-01 Justification : This can be accepted, due to the implementation is following AUTOSAR standard rule for SchM  */
/*                       module's name.                                                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3630)    : The implementation of this struct/union type should be hidden.                               */
/* Rule                : MISRA C:2012 Dir-4.8                                                                         */
/* JV-01 Justification : This is accepted. Redundant of struct or union type has no affect to driver operation.       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE Rule CWE-398, CWE-569                                            */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is accepted. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:1039)    : Treating array of length one as potentially flexible member.                                 */
/* Rule                : CERTCCM DCL38, MISRA C:2012 Dir-1.1, Rule-1.2                                                */
/* JV-01 Justification : Use array of length as the final member has no problem by manual reviewing.                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:4641)    : The identifier '%1s' could conflict in the future with the name of a macro in '<%2s>'.       */
/* Rule                : CERTC 3.6.0 Rule DCL37, CWE 3.6.0 Rule CWE-398, CWE-569                                      */
/* JV-01 Justification : This message is just a notice to avoid using this identifier as a macro in standard library  */
/*                       in the future.                                                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

#ifndef SPI_PBTYPES_H
#define SPI_PBTYPES_H

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
#if (SPI_CRITICAL_SECTION_PROTECTION == STD_ON)
#include "SchM_Spi.h"
#endif

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR Release version information */
#define SPI_PBTYPES_AR_RELEASE_MAJOR_VERSION    SPI_AR_RELEASE_MAJOR_VERSION
#define SPI_PBTYPES_AR_RELEASE_MINOR_VERSION    SPI_AR_RELEASE_MINOR_VERSION
#define SPI_PBTYPES_AR_RELEASE_REVISION_VERSION SPI_AR_RELEASE_REVISION_VERSION

/* File version information */
#define SPI_PBTYPES_SW_MAJOR_VERSION            SPI_SW_MAJOR_VERSION
#define SPI_PBTYPES_SW_MINOR_VERSION            SPI_SW_MINOR_VERSION

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/
/* Calculate word size to hold bits */
#define SPI_BITS_TO_WORDS(bits)                 (((uint32)(bits) + 31UL) / 32UL)                                        /* PRQA S 3471 # JV-01 */

/* Extend address to the next 32bit align. Add 3 and clear the lowest 2bits. */
#define SPI_ALIGN_4(address)                    (((uint32)(address) + 3UL) & (uint32)(~3UL))                            /* PRQA S 3472 # JV-01 */

/* Start bit to store active HW in async transmission */
#define SPI_ACTIVE_HW_BITS                      16U

/* Start bit to store active HW in sync transmission */
#define SPI_SYNC_HW_BITS                        0x0000FFFFUL

/* 32-Bit length */
#define SPI_UINT32_BITS                         32U

/* CS polarity */
#define SPI_CS_HIGH             SPI_TRUE
#define SPI_CS_LOW              SPI_FALSE

/***********************************************************************************************************************
**                                      SchM Critical Section Protection Macros                                       **
***********************************************************************************************************************/

#if (SPI_CRITICAL_SECTION_PROTECTION == STD_ON)
#define SPI_ENTER_CRITICAL_SECTION(Exclusive_Area) SchM_Enter_Spi_##Exclusive_Area()                                    /* PRQA S 0342 # JV-01 */
#define SPI_EXIT_CRITICAL_SECTION(Exclusive_Area)  SchM_Exit_Spi_##Exclusive_Area()                                     /* PRQA S 0342 # JV-01 */
#else
#define SPI_ENTER_CRITICAL_SECTION(Exclusive_Area)
#define SPI_EXIT_CRITICAL_SECTION(Exclusive_Area)
#endif /* (SPI_CRITICAL_SECTION_PROTECTION == STD_ON) */

/***********************************************************************************************************************
**                                              DET Report Error Macros                                               **
***********************************************************************************************************************/
#if (SPI_AR_VERSION == SPI_AR_422_VERSION)
#if (SPI_DEV_ERROR_DETECT == STD_ON)
#define SPI_DET_REPORT_RUNTIME_ERROR(ModuleId, InstanceId, ApiId, ErrorId) \
  (void)Det_ReportError(ModuleId, InstanceId, ApiId, ErrorId)
#endif
#elif (SPI_AR_VERSION == SPI_AR_R22_11_VERSION)
#define SPI_DET_REPORT_RUNTIME_ERROR(ModuleId, InstanceId, ApiId, ErrorId) \
  (void)Det_ReportRuntimeError(ModuleId, InstanceId, ApiId, ErrorId)
#endif

/***********************************************************************************************************************
**                                              DEM Report Error Macros                                               **
***********************************************************************************************************************/
#if (SPI_AR_VERSION == SPI_AR_422_VERSION)
#define SPI_DEM_REPORT_ERROR(EventId, EventStatus) Dem_ReportErrorStatus(EventId, EventStatus)
#elif (SPI_AR_VERSION == SPI_AR_R22_11_VERSION)
#define SPI_DEM_REPORT_ERROR(EventId, EventStatus) (void)Dem_SetEventStatus(EventId, EventStatus)
#endif

/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/

/* Definition of First transfer bit */
typedef enum ETag_Spi_TransferStartType                                                                                 /* PRQA S 4641 # JV-01 */
{
  /* Data is transmitted with MSB first */
  SPI_TRANSFER_START_MSB,
  /* Data is transmitted with LSB first */
  SPI_TRANSFER_START_LSB
} Spi_TransferStartType;

/* Definition of Channel buffer types */
typedef enum ETag_Spi_ChannelBufferType                                                                                 /* PRQA S 4641 # JV-01 */
{
  /* Software internal buffer */
  SPI_BUFFER_TYPE_IB = 0,
  /* External buffer */
  SPI_BUFFER_TYPE_EB
} Spi_ChannelBufferType;

/* Structure for channel configuration */
typedef struct STag_Spi_ChannelConfigType                                                                               /* PRQA S 3630 # JV-01 */
{
  #if ((SPI_DEV_ERROR_DETECT == STD_ON) && (SPI_MULTI_CORE_SUPPORT == STD_ON))
  /* Declare the variable to store the list of configured core IDs for the channel */
  uint8 ucCoreMask;
  #endif
  /* Bit width of each data element (2 to 64) */
  uint8 ucDataWidth;
  /* Byte size of each data element in memory (1, 2, 4) */
  uint8 ucByteSize;
  /* First starting bit */
  Spi_TransferStartType enTransferStart;
  /* Default value of the channel */
  uint32 ulDefaultData;
  /* Channel buffer type (IB, EB, HWIB) */
  Spi_ChannelBufferType enChannelBufferType;
  /* Number of IB or maximum size of EB */
  uint16 usNoOfBuffers;
  #if ((SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IB) || (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IBEB))
  /* Pointer to the tx data buffer */
  volatile P2VAR(Spi_DataBufferType, TYPEDEF, SPI_VAR_NO_INIT) pTxBuffer;                                               /* PRQA S 3432 # JV-01 */
  /* Pointer to the rx data buffer */
  volatile P2VAR(Spi_DataBufferType, TYPEDEF, SPI_VAR_NO_INIT) pRxBuffer;                                               /* PRQA S 3432 # JV-01 */
  #endif
  #if ((SPI_CHANNEL_BUFFERS_ALLOWED == SPI_EB) || (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IBEB))
  /* Pointer to the EB information structure */
  volatile P2VAR(Spi_EBDataType, TYPEDEF, SPI_VAR_NO_INIT) pEBData;                                                     /* PRQA S 3432 # JV-01 */
  #endif
} Spi_ChannelConfigType;

/* Structure for job configuration */
typedef struct STag_Spi_JobConfigType                                                                                   /* PRQA S 3630 # JV-01 */
{
  #if ((SPI_DEV_ERROR_DETECT == STD_ON) && (SPI_MULTI_CORE_SUPPORT == STD_ON))
  /* Declare the variable to store the list of configured core IDs for the channel */
  uint8 ucCoreMask;
  #endif
  /* Number of channels in the list */
  uint8 ucNoOfChannels;
  /* Chip select information */
  uint16 usCSInfo;
  /* Pointer to list of channels */
  P2CONST(Spi_ChannelType, AUTOMATIC, SPI_CONFIG_DATA) pChannelList;
  #if ((SPI_LEVEL_DELIVERED == SPI_LEVEL_1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2))
  /* Pointer to callback notification */
  P2FUNC(void, SPI_APPL_CODE, pJobEndNotification)(void);                                                               /* PRQA S 3432 # JV-01 */
  /* Job priority */
  uint8 ucJobPriority;
  #endif
  /* Index of HWUnit which this Job associated to */
  Spi_HWUnitType ucHWUnitIndex;
  /* Chip select type with which this job is associated to */
  Spi_CSType enCSType;
  #if (SPI_CS_VIA_GPIO_CONFIGURED == STD_ON)
  /* Address of PSR register of GPIO CS port */
  P2VAR(volatile uint32, TYPEDEF, REGSPACE) pPSRReg;
  /* Port pin mask of GPIO chip select port pin associated with this job */
  uint32 ulPortPinMask;
  /* Timing between clock start and chip select activated */
  uint32 ulClk2CsCount;
  /* Chip select polarity */
  boolean blCsPolarity;
  #endif
  /* All Channels properties are same*/
  boolean blChannelPropertySame;
  #if (SPI_DMA_CONFIGURED == STD_ON)
  /* Index of DMA for Tx side */
  uint8 ucTxDmaIndex;
  /* Index of DMA for Rx side */
  uint8 ucRxDmaIndex;
  #endif /* (SPI_DMA_CONFIGURED == STD_ON) */
  /* Pointer to HW-dependent device configuration */
  CONSTP2CONST(void, TYPEDEF, SPI_CONFIG_DATA) pHWDevConfig;
} Spi_JobConfigType;

/* Structure contains Job list for each Queue */
typedef struct STag_Spi_SubSeqConfigType
{
  #if ((SPI_LEVEL_DELIVERED == SPI_LEVEL_1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2))
  /* Bit array indicating priorities used byte this Sequence */
  uint8 ucUsingPriorities;
  #endif
  /* Number of Jobs in the list */
  uint16 usNoOfJobs;
  /* Pointer to the array of Jobs */
  P2CONST(Spi_JobType, AUTOMATIC, SPI_CONFIG_DATA) pJobList;
} Spi_SubSeqConfigType;

/* Structure for sequence configuration */
typedef struct STag_Spi_SeqConfigType                                                                                   /* PRQA S 3630 # JV-01 */
{
  #if ((SPI_DEV_ERROR_DETECT == STD_ON) && (SPI_MULTI_CORE_SUPPORT == STD_ON))
  /* Declare the variable to store the list of configured core IDs for the sequence */
  uint8 ucCoreMask;
  #endif
  /* Bit array indicating HWUnits used by this Sequence */
  uint32 ulUsingHWUnits;
  #if ((SPI_LEVEL_DELIVERED == SPI_LEVEL_1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2) || \
     (SPI_SYNC_SEQ_ENDNOTIFICATION_ENABLED == STD_ON))
  /* Pointer to start sequence callback notification */
  P2FUNC(void, SPI_APPL_CODE, pSeqEndNotification)(void);                                                               /* PRQA S 3432 # JV-01 */
  #endif
  #if (SPI_SEQ_STARTNOTIFICATION_ENABLED == STD_ON)
  /* Pointer to start sequence callback notification */
  P2FUNC(void, SPI_APPL_CODE, pSeqStartNotification)(void);                                                             /* PRQA S 3432 # JV-01 */
  #endif
  #if ((SPI_AR_VERSION == SPI_AR_422_VERSION) && (SPI_LEVEL_DELIVERED == SPI_LEVEL_2))
  /* Sequence is synchronous or asynchronous */
  boolean blSynchronous;
  #endif
  #if ((SPI_LEVEL_DELIVERED == SPI_LEVEL_1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2))
  #if (SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON)
  /* Sequence to be interrupted or not */
  boolean blInterruptible;
  #endif
  /* Bit array indicating other Sequences that share Jobs with this Sequence */
  uint32 aaJobSharedSequences[SPI_BITS_TO_WORDS(SPI_MAX_SEQUENCE)];
  #endif
  /* Job list for each Queue */
  Spi_SubSeqConfigType aaSubSeqs[SPI_MAX_QUEUE];                                                                        /* PRQA S 1039 # JV-01 */
} Spi_SeqConfigType;

/* Structure for hardware unit information */
typedef struct STag_Spi_HWUnitInfoType                                                                                  /* PRQA S 3630 # JV-01 */
{
  #if ((SPI_DEV_ERROR_DETECT == STD_ON) && (SPI_MULTI_CORE_SUPPORT == STD_ON))
  /* Declare the variable to store the list of configured core IDs for the sequence */
  uint8 ucCoreMask;
  #endif
  /* Macro type of this HWUnit */
  uint8 ucMacroIndex;
  /* The physical index of HWUnit */
  uint8 ucPhyUnitIndex;
  #if ((SPI_AR_VERSION == SPI_AR_422_VERSION) && (SPI_LEVEL_DELIVERED == SPI_LEVEL_2))
  /* Whether the HW Unit is synchronous or asynchronous */
  boolean blSynchronous;
  #endif
} Spi_HWUnitInfoType;

/* Structure for HW-dependent function pointer table */
typedef struct STag_Spi_HwFuncTableType                                                                                 /* PRQA S 3630 # JV-01 */
{
  P2FUNC(void, TYPEDEF, pHwInit)(void);                                                                                 /* PRQA S 3432 # JV-01 */
  P2FUNC(void, TYPEDEF, pHwDisableAllInterrupts)(void);                                                                 /* PRQA S 3432 # JV-01 */
  P2FUNC(void, TYPEDEF, pHwProcessJob)                                                                                  /* PRQA S 3432 # JV-01 */
  (const boolean LblFirst, CONSTP2CONST(Spi_JobConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpJobConfig);
  #if ((SPI_LEVEL_DELIVERED == SPI_LEVEL_0) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2))
  P2FUNC(Std_ReturnType, TYPEDEF, pHwTransmitSyncJob)                                                                   /* PRQA S 3432 # JV-01 */
  (CONSTP2CONST(Spi_JobConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpJobConfig);
  #endif
  P2FUNC(void, TYPEDEF, pHwMaskInterrupts)                                                                              /* PRQA S 3432 # JV-01 */
  (CONSTP2CONST(Spi_JobConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpJobConfig, const boolean LblMask);
  #if ((SPI_LEVEL_DELIVERED == SPI_LEVEL_1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2))
  #if (SPI_FORCE_CANCEL_API == STD_ON)
  P2FUNC(void, TYPEDEF, pHwForceStop)(const uint32 LulHWUnitIndex);                                                     /* PRQA S 3432 # JV-01 */
  #endif
  #endif
  #if (SPI_DMA_CONFIGURED == STD_ON)
  P2FUNC(void, TYPEDEF, pHwDMACompleteISR)(const uint32 LulDMAUnitIndex);                                               /* PRQA S 3432 # JV-01 */
  #endif
  #if (SPI_LEVEL_DELIVERED == SPI_LEVEL_2) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_1)
  P2FUNC(void, TYPEDEF, pHwMainFunction_Handling)(void);                                                                /* PRQA S 3432 # JV-01 */
  #endif
  P2FUNC(void, TYPEDEF, pHwTurnOff)(const uint32 LulHWPhyIndex);                                                        /* PRQA S 3432 # JV-01 */
  P2FUNC(void, TYPEDEF, pHwDeInit)(void);                                                                               /* PRQA S 3432 # JV-01 */
} Spi_HwFuncTableType;

/* Structure for HW-dependent configuration */
typedef struct STag_Spi_HwConfigType                                                                                    /* PRQA S 3630 # JV-01 */
{
  CONSTP2CONST(Spi_HwFuncTableType, TYPEDEF, SPI_CONFIG_DATA) pHwDepFunc;
  CONSTP2CONST(uint8, TYPEDEF, SPI_CONFIG_DATA) pPhyToHWUnit;
} Spi_HwConfigType;

/***********************************************************************************************************************
**                                                Global Declarations                                                 **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                             Global Function Prototypes                                             **
***********************************************************************************************************************/

#endif /* SPI_PBTYPES_H */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
