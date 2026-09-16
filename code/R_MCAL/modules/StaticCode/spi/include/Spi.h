/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Spi.h                                                                                               */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* Copyright(c) 2020-2025 Renesas Electronics Corporation.                                                            */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains macros, SPI type definitions, structure data types and API function prototypes of SPI Driver    */
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
 * 2.5.1:  30/06/2025  : Remove SW-VERSION in file header, Update SW-VERSION to 2.5.1
 * 2.5.0:  30/06/2025  : Update SW-VERSION for RH850/Ver21.01.00(D) U2Ax release
 * 2.4.0:  31/05/2025  : Update SW-VERSION for RH850/Ver21.01.01 U2Cx release(D) Release
 * 2.3.2:  30/04/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 Release
 * 2.3.1:  31/03/2025  : Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02 Release
 * 2.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00(D) U2Bx Final Release
 * 2.1.3:  31/10/2024  : Update SW-VERSION up to 2.1.3 and SPI_SW_PATCH_VERSION to 3
 * 2.1.2:  30/09/2024  : Support AR2211: update macro file definition, remove macro condition SPI_AR_R22_11_VERSION for 
 *                       Spi_SetAsyncMode
 * 2.1.1:  13/08/2024  : Remove redundant macro SPI_E_INVALID_CORE
 *                     : Add new "SPI_E_SEQUENCE_TIMEOUT" to report DET RUNTIME ERROR for Spi_SyncTransmit
 *                     : Update SPI_SW_MAJOR_VERSION to 2
 *                     : Update SPI_SW_MINOR_VERSION to 1
 *                     : Update SPI_SW_PATCH_VERSION to 1 
 *                     : Remove QAC messages (2:0841) to fix redundant QAC messages
 *                     : Update Spi_GaaConfiguration to support for post build variant
 *                     : Add new QAC message (2:3684)
 *                     : Increase SW-VERSION up to 2.0.3
 *                     : Remove QAC message 1534
 * 2.1.0:  27/02/2024  : Update SW-VERSION to 2.1.0
 *                       Update SPI_SW_MINOR_VERSION to 1
 *                       Update SPI_SW_PATCH_VERSION to 0
 * 2.0.2:  14/12/2023  : Update SW-VERSION to 2.0.2
 *                     : Update SPI_SW_PATCH_VERSION to 2
 * 2.0.1:  23/10/2023  : Remove SPI_AR_R21_11_VERSION
 *         22/10/2023  : Update QAC message 1534 support Amendment 2
 *         11/10/2023  : Add new Autosar version 22_11
 *                       Update SW-VERSION to 2.0.1
 *                       Update re-processor SPI_AR_VERSION == SPI_AR_R22_11_VERSION for support R22-11
 *                       Update pre-condition SPI_AR_VERSION == SPI_AR_R22_11_VERSION for 
 *                       SPI_LEVEL_DELIVERED == SPI_LEVEL_1 to Spi_SetAsyncMode
 *                       Change macro SPI_START/STOP_SEC_DBTOC_DATA_UNSPECIFIED to
 *                       SPI_START/STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED support
 *                       new requirement MemoryMapping 7.2.1.3                                             
 * 2.0.0:  28/08/2023  : Remove SPI_INSTANCE_INDEX 
 *         25/07/2023  : Support Multicore: Remove #include "Spi_MultiInstance.h"
 *                       Update from "Spi_Mapping.h to "Spi_MemMap.h".
 *                       Change #include SPI_CFG_HEADER to #include "Spi_Cfg.h"
 *                       Add #define SPI_E_REQUEST_ONGOING, #define SPI_E_INVALID_CORE, #define SPI_E_REQUEST_FALSE
 *         17/07/2023  : Update pre-condition SPI_AR_VERSION == SPI_AR_R21_11_VERSION for 
 *                       SPI_LEVEL_DELIVERED == SPI_LEVEL_1 to Spi_SetAsyncMode
 *         26/05/2023  : Change SPI_AR_2111_VERSION to SPI_AR_R21_11_VERSION
 *         05/05/2023  : Add new Autosar version 21_11
 *         25/04/2023  : Update SPI_SW_MAJOR_VERSION to 2
 *                       Update SPI_SW_MINOR_VERSION to 0
 *                       Update SPI_SW_PATCH_VERSION to 0
 * 1.5.1:  07/03/2023  : Update SPI_SW_MINOR_VERSION to 5
 *                       Update SPI_SW_PATCH_VERSION to 0
 * 1.5.0:  05/12/2022  : Update SPI_SW_PATCH_VERSION to 5
 * 1.4.4:  20/06/2022  : Added macro SPI_PORT_PIN_MASK
 *         17/06/2022  : Update SPI_SW_PATCH_VERSION to 4
 * 1.4.3:  09/05/2022  : Add new DET error code SPI_E_PARAM_VALUE
 *         20/05/2022  : Remove redundant macro
 * 1.4.2:  02/03/2022  : Merge QAC
 * 1.4.1:  06/12/2021  : Update SPI_SW_PATCH_VERSION to 1U for SW-VERSION up
 * 1.4.0:  15/10/2021  : Update SPI_SW_MINOR_VERSION to 4U and SPI_SW_PATCH_VERSION to 0U for SW-VERSION up
 * 1.3.2:  06/09/2021  : Update QAC contents
 *         30/08/2021  : Update header file macro to call file multiple times
 *                       Update to include Spi_Mapping.h instead of Spi_MemMap.h
 *         13/08/2021  : Changed SPI_SW_PATCH_VERSION to 2U for SW-VERSION up
 * 1.3.1:  02/07/2021  : Add QAC message 9.5.0
 *                       Format source code to 120 characters
 *                       Improve Violation tag (remove START/END)
 *         07/05/2021  : Remove the declaration of Spi_MainFunction_Handling
 * 1.3.0:  02/12/2020  : Changed SPI_SW_MINOR_VERSION to 3U and SPI_SW_PATCH_VERSION to 1U for SW-VERSION up
 * 1.2.1:  14/10/2020  : Changed SPI_SW_PATCH_VERSION to 1U for SW-VERSION up
 * 1.2.0:  30/07/2020  : Release
 *         28/07/2020  : Add QAC 9.3.1 comment.
 * 1.1.0:  19/06/2020  : Release
 * 1.0.0:  24/03/2020  : Initial Version
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (7:0791)    : Macro identifier does not differ from other macro identifier(s) (e.g. '%s') within the       */
/*                       specified number of significant characters.                                                  */
/* Rule                : CERTCCM DCL23, MISRA C:2012 Rule-5.4                                                         */
/* JV-01 Justification : This macro identifier is following AUTOSAR standard rule (Symbolic Name or Published         */
/*                       Macro's name), so this is accepted.                                                          */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE Rule CWE-398, CWE-569                                            */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is accepted. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3684)    : Array declared with unknown size.                                                            */
/* Rule                : CERTCCM ARR02, MISRA C:2012 Rule-8.11                                                        */
/* JV-01 Justification : Arrays used are verified in the file which are only declarations and size is configuration   */
/*                       dependent.                                                                                   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

#ifndef SPI_H
#define SPI_H
/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Include standard Autosar Type */
#include "Std_Types.h"
/* Include Spi pre-compile options */
#include "Spi_Cfg.h"
/* Include for Spi Type declaration */
#include "Spi_Types.h"

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
#define SPI_INSTANCE_ID    SPI_INSTANCE_ID_VALUE

/* Vendor and module identification */
#define SPI_VENDOR_ID      SPI_VENDOR_ID_VALUE
#define SPI_MODULE_ID      SPI_MODULE_ID_VALUE

/* Different supported AUTOSAR release versions information */
#define SPI_AR_422_VERSION 422U
#define SPI_AR_R22_11_VERSION 480U

/* AUTOSAR specification version information */
#if (SPI_AR_VERSION == SPI_AR_422_VERSION)
#define SPI_AR_RELEASE_MAJOR_VERSION    4U
#define SPI_AR_RELEASE_MINOR_VERSION    2U
#define SPI_AR_RELEASE_REVISION_VERSION 2U
#elif (SPI_AR_VERSION == SPI_AR_R22_11_VERSION)
#define SPI_AR_RELEASE_MAJOR_VERSION    4U
#define SPI_AR_RELEASE_MINOR_VERSION    8U
#define SPI_AR_RELEASE_REVISION_VERSION 0U
#endif

/* File version information */
#define SPI_SW_MAJOR_VERSION          2U
#define SPI_SW_MINOR_VERSION          5U
#define SPI_SW_PATCH_VERSION          1U

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/
/* Port pin mask */
#define SPI_PORT_PIN_MASK                (uint32)0xFFFF0000UL
/***********************************************************************************************************************
**                                                    Service IDs                                                     **
***********************************************************************************************************************/
/* Service ID for Spi_Init() */
#define SPI_INIT_SID                  (uint8)0x00
/* Service ID for Spi_DeInit() */
#define SPI_DEINIT_SID                (uint8)0x01
/* Service ID for Spi_WriteIB() */
#define SPI_WRITEIB_SID               (uint8)0x02
/* Service ID for Spi_AsyncTransmit() */
#define SPI_ASYNCTRANSMIT_SID         (uint8)0x03
/* Service ID for Spi_ReadIB() */
#define SPI_READIB_SID                (uint8)0x04
/* Service ID for Spi_SetupEB() */
#define SPI_SETUPEB_SID               (uint8)0x05
/* Service ID for Spi_GetStatus() */
#define SPI_GETSTATUS_SID             (uint8)0x06
/* Service ID for Spi_GetJobResult() */
#define SPI_GETJOBRESULT_SID          (uint8)0x07
/* Service ID for Spi_GetSequenceResult() */
#define SPI_GETSEQUENCERESULT_SID     (uint8)0x08
/* Service ID for Spi_GetVersionInfo() */
#define SPI_GETVERSIONINFO_SID        (uint8)0x09
/* Service ID for Spi_SyncTransmit() */
#define SPI_SYNCTRANSMIT_SID          (uint8)0x0A
/* Service ID for Spi_GetHWUnitStatus() */
#define SPI_GETHWUNITSTATUS_SID       (uint8)0x0B
/* Service ID for Spi_Cancel() */
#define SPI_CANCEL_SID                (uint8)0x0C
/* Service ID for Spi_SetAsyncMode() */
#define SPI_SETASYNCMODE_SID          (uint8)0x0D
/* Service ID for Spi_ForceCancel() */
#define SPI_FORCECANCEL_SID           (uint8)0xA0

/***********************************************************************************************************************
**                                                  DET Error Codes                                                   **
***********************************************************************************************************************/
/* API services invoked with invalid channel ID */
#define SPI_E_PARAM_CHANNEL           (uint8)0x0A
/* API services invoked with invalid job ID */
#define SPI_E_PARAM_JOB               (uint8)0x0B
/* API services invoked with invalid sequence ID */
#define SPI_E_PARAM_SEQ               (uint8)0x0C
/* Spi_SetupEB API invoked with length greater than configured length */
#define SPI_E_PARAM_LENGTH            (uint8)0x0D
/* Spi_GetHWUnitStatus API invoked with invalid hardware unit ID */
#define SPI_E_PARAM_UNIT              (uint8)0x0E
/* Spi_SetAsyncMode API invoked with invalid asynchronous mode */
#define SPI_E_PARAM_VALUE             (uint8)0x0F
/* API services invoked before the initialization of SPI Driver */
#define SPI_E_UNINIT                  (uint8)0x1A
/* API services invoked in a wrong sequence */
#define SPI_E_SEQ_PENDING             (uint8)0x2A
/* Spi_SyncTransmit API invoked at wrong time */
#define SPI_E_SEQ_IN_PROCESS          (uint8)0x3A
/* Spi_init API service called while the Spi driver has already been initialized */
#define SPI_E_ALREADY_INITIALIZED     (uint8)0x4A
/* Spi_Init API invoked with pointer to invalid database */
#define SPI_E_INVALID_DATABASE        (uint8)0xEF
/* Spi_GetVersionInfo API invoked with invalid pointer */
#define SPI_E_PARAM_POINTER           (uint8)0x10
/* DET code to report invalid core mapping service */
#define SPI_E_INVALID_CORE            (uint8)0xEDU
/* DET code to report the service has not been executed after polling */
#define SPI_E_REQUEST_ONGOING         (uint8)0xECU
/* DET code to report service is being requested by other cores */
#define SPI_E_REQUEST_FALSE           (uint8)0xEEU
/* DET code to report that the sequence is running but time out occurs in multicore for sync transmission */
#define SPI_E_SEQUENCE_TIMEOUT        (uint8)0xEBU

/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/
#define SPI_START_SEC_PUBLIC_CODE_LOCAL
#include "Spi_MemMap.h"

/* External declaration for Spi performs initialization SPI Driver API */
extern FUNC(void, SPI_PUBLIC_CODE) Spi_Init(P2CONST(Spi_ConfigType, AUTOMATIC, SPI_APPL_CONST) ConfigPtr);
/* External declaration for Spi performs de-initialization SPI Driver API */
extern FUNC(Std_ReturnType, SPI_PUBLIC_CODE) Spi_DeInit(void);

#if (SPI_LEVEL_DELIVERED == SPI_LEVEL_2) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_1)
/* External declaration for Spi setting the asynchronous mode API */
extern FUNC(Std_ReturnType, SPI_PUBLIC_CODE) Spi_SetAsyncMode(Spi_AsyncModeType Mode);
#endif

#define SPI_STOP_SEC_PUBLIC_CODE_LOCAL
#include "Spi_MemMap.h"

#define SPI_START_SEC_PUBLIC_CODE_GLOBAL
#include "Spi_MemMap.h"

#if (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IB) || (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IBEB)
/* External declaration for Spi performs write IB API */
extern FUNC(Std_ReturnType, SPI_PUBLIC_CODE)
    Spi_WriteIB(Spi_ChannelType Channel, P2CONST(Spi_DataBufferType, AUTOMATIC, SPI_APPL_CONST) DataBufferPtr);
/* External declaration for Spi performs read IB API */
extern FUNC(Std_ReturnType, SPI_PUBLIC_CODE)
    Spi_ReadIB(Spi_ChannelType Channel, P2VAR(Spi_DataBufferType, AUTOMATIC, SPI_APPL_DATA) DataBufferPointer);         /* PRQA S 3432 # JV-01 */
#endif

#if (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_EB) || (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IBEB)
/* External declaration for Spi performs setup EB API */
extern FUNC(Std_ReturnType, SPI_PUBLIC_CODE)
    Spi_SetupEB(Spi_ChannelType Channel, P2CONST(Spi_DataBufferType, AUTOMATIC, SPI_APPL_DATA) SrcDataBufferPtr,
                P2VAR(Spi_DataBufferType, AUTOMATIC, SPI_APPL_DATA) DesDataBufferPtr, Spi_NumberOfDataType Length);     /* PRQA S 3432 # JV-01 */
#endif

#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL_1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2))
/* External declaration for Spi transmitting data asynchronously API */
extern FUNC(Std_ReturnType, SPI_PUBLIC_CODE) Spi_AsyncTransmit(Spi_SequenceType Sequence);
#endif

#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL_0) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2))
/* External declaration for Spi transmitting data synchronously API */
extern FUNC(Std_ReturnType, SPI_PUBLIC_CODE) Spi_SyncTransmit(Spi_SequenceType Sequence);
#endif

/* External declaration for Spi get status API */
extern FUNC(Spi_StatusType, SPI_PUBLIC_CODE) Spi_GetStatus(void);

/* External declaration for Spi get job result API */
extern FUNC(Spi_JobResultType, SPI_PUBLIC_CODE) Spi_GetJobResult(Spi_JobType Job);

/* External declaration for Spi get sequence result API */
extern FUNC(Spi_SeqResultType, SPI_PUBLIC_CODE) Spi_GetSequenceResult(Spi_SequenceType Sequence);

/* API to get the version information */
#if (SPI_VERSION_INFO_API == STD_ON)
/* External declaration for Spi get version info  API */
extern FUNC(void, SPI_PUBLIC_CODE) Spi_GetVersionInfo(
                                                    P2VAR(Std_VersionInfoType, AUTOMATIC, SPI_APPL_DATA) versioninfo);  /* PRQA S 3432 # JV-01 */
#endif /* END of SPI_VERSION_INFO_API */

#if (SPI_HW_STATUS_API == STD_ON)
/* External declaration for Spi get HW status  API */
extern FUNC(Spi_StatusType, SPI_PUBLIC_CODE) Spi_GetHWUnitStatus(Spi_HWUnitType HWUnit);
#endif

#if (SPI_CANCEL_API == STD_ON)
/* External declaration for Spi cancel API */
extern FUNC(void, SPI_PUBLIC_CODE) Spi_Cancel(Spi_SequenceType Sequence);
#endif

#if (SPI_FORCE_CANCEL_API == STD_ON)
/* External declaration for Spi force cancel API */
extern FUNC(void, SPI_PUBLIC_CODE) Spi_ForceCancel(const Spi_SequenceType LucSequence);
#endif

#define SPI_STOP_SEC_PUBLIC_CODE_GLOBAL
#include "Spi_MemMap.h"

/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/
#define SPI_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Spi_MemMap.h"

/* Structure for SPI Init configuration */
extern CONST(Spi_ConfigType, SPI_CONFIG_DATA) Spi_GaaConfiguration[];                                                   /* PRQA S 3684 # JV-01 */

#define SPI_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Spi_MemMap.h"
#endif /* SPI_H */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
