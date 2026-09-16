/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Adc.h                                                                                               */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains macros, ADC type definitions, enumerations,                                                     */
/* data types and API function prototypes of ADC Driver.                                                              */
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
 * 2.5.1: 30/06/2025 : Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.03 release
 *                     Remove SW-VERSION in file header
 * 2.5.0: 30/06/2025 : Update SW-VERSION for RH850/Ver22.01.00 (D) U2Ax release
 * 2.4.0: 31/05/2025 : Update SW-VERSION for RH850/Ver21.01.01 U2Cx release
 * 2.3.1: 31/03/2025 : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 * 2.3.1: 28/02/2025 : Updated software version definition for for Ver22.00.02 U2Ax Beta 1 Release
 * 2.3.0: 28/02/2025 : Updated software version definition for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0: 31/12/2024 : Updated software version definition for Ver22.02.00/Ver22.02.00.D Final Release
 * 2.1.3: 31/10/2024 : Updated software version definition.
 * 2.1.2: 30/09/2024 : Updated software version definition.
 * 2.1.1: 30/08/2024 : Updated software version definition.
 * 2.1.0: 19/02/2024 : Update SW-VERSION to 2.1.0
 * 2.0.1: 14/10/2023 : Support Autosar R22-11, support QAC Amendment 2
 *                     1. Remove #define ADC_AR_R21_11_VERSION 470U, add #define ADC_AR_R22_11_VERSION 480U
 *                     2. Change macro ADC_AR_R21_11_VERSION to ADC_AR_R22_11_VERSION support Autosar version.
 *                     3. Increase ADC_SW_PATCH_VERSION to 1U
 *                     4. Add message 1534
 *        11/10/2023 : Change ADC_START_SEC_DBTOC_DATA_UNSPECIFIED to ADC_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
 *                     and ADC_STOP_SEC_DBTOC_DATA_UNSPECIFIED to ADC_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED.
 * 2.0.0: 28/08/2023 : Removed Multi-Instance define. Change Adc_Mapping.h to Adc_Memmap.h
                       Adc macro ADC_E_INVALID_CORE, ADC_E_REQUEST_FALSE support multicore.
 *        20/04/2023 : Updated software version definition.
 * 1.5.0: 06/03/2023 : Updated software version definition.
 * 1.4.5: 13/09/2022 : Updated software version definition.
 * 1.4.4: 14/07/2022 : Updated software version definition.
 * 1.4.2: 25/02/2022 : Updated software version definition.
 * 1.4.1: 24/11/2021 : Updated software version definition.
 *                     Added instance 4 to the suppression of duplicate inclusion.
 * 1.4.0: 13/10/2021 : Updated software version definition.
 * 1.3.2: 06/09/2021 : Update header file macro to call file multiple times.
 *        01/09/2021 : Updated SW-VERSION definition.
 * 1.3.1: 08/07/2021 : Changed the compile switch macro that selects the AUTOSAR version information definition.
 *        07/07/2021 : Added QAC message 9.5.0
 *                     Changed comment format to 120 columns
 *                     Changed violation tag from START/END
 *        01/06/2021 : Changed to the appropriate memory classes and pointer classes.
 *        07/04/2021 : Changed to comply with coding rules.
 * 1.3.0: 20/01/2021 : Function Adc_SetupResultBuffer, update data type of
 *                     parameter DataBufferPtr from P2CONST to P2VAR.
 *                     Update parameter LddGroup to Group.
 *        03/12/2020 : Update software version definition
 * 1.2.1: 20/10/2020 : Update software version definition
 * 1.2.0: 14/07/2020 : Release
 *        27/07/2020 : Add QAC 9.3.1 comment.
 * 1.1.0: 19/06/2020 : Release
 * 1.0.1: 22/05/2020 : Update software version definition.
 * 1.0.0: 09/01/2020 : Initial Version
 */
/**********************************************************************************************************************/
#ifndef ADC_H
#define ADC_H

/* Define macro of AUTOSAR version */
#define ADC_AR_422_VERSION      422U
#define ADC_AR_431_VERSION      431U
#define ADC_AR_R22_11_VERSION      480U

/***********************************************************************************************************************
**                             To support different AUTOSAR releases in a single package                              **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
#include "Std_Types.h"
/* Included for ADC module specific definitions */
#include "Adc_Cfg.h"
/* Included for Adc type declarations */
#include "Adc_Types.h"

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
#define ADC_VENDOR_ID                   ADC_VENDOR_ID_VALUE
#define ADC_MODULE_ID                   ADC_MODULE_ID_VALUE
#define ADC_INSTANCE_ID                 ADC_INSTANCE_ID_VALUE

#if (ADC_AR_VERSION == ADC_AR_422_VERSION)
/* AUTOSAR release version information */
#define ADC_AR_RELEASE_MAJOR_VERSION    4U
#define ADC_AR_RELEASE_MINOR_VERSION    2U
#define ADC_AR_RELEASE_REVISION_VERSION 2U
#elif (ADC_AR_VERSION == ADC_AR_431_VERSION)
/* AUTOSAR release version information */
#define ADC_AR_RELEASE_MAJOR_VERSION    4U
#define ADC_AR_RELEASE_MINOR_VERSION    3U
#define ADC_AR_RELEASE_REVISION_VERSION 1U
#elif (ADC_AR_VERSION == ADC_AR_R22_11_VERSION)
/* AUTOSAR release version information */
#define ADC_AR_RELEASE_MAJOR_VERSION    4U
#define ADC_AR_RELEASE_MINOR_VERSION    8U
#define ADC_AR_RELEASE_REVISION_VERSION 0U
#endif /* (ADC_AR_VERSION == ADC_AR_422_VERSION) */

/* Module Software version information */
#define ADC_SW_MAJOR_VERSION            2U
#define ADC_SW_MINOR_VERSION            5U
#define ADC_SW_PATCH_VERSION            1U

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE Rule CWE-398, CWE-569                                            */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is accepted. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3684)    : Array declared with unknown size.                                                            */
/* Rule                : MISRA C:2012 Rule-8.11, CERTCCM ARR02                                                        */
/* JV-01 Justification : Arrays used are verified in the file which are only declarations and size is configuration   */
/*                       dependent.                                                                                   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1534)    : The macro '%1s' is declared but not used within this project.                                */
/* Rule                : MISRA C:2012 Rule-2.5                                                                        */
/* JV-01 Justification : This is accepted. This macro is used by other file.                                          */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                               API Service Id Macros                                                **
***********************************************************************************************************************/
/* Service Id of Adc_Init */
#define ADC_INIT_SID                       (uint8)0x00U                                                                 /* PRQA S 1534 # JV-01 */
/* Service Id of Adc_DeInit */
#define ADC_DEINIT_SID                     (uint8)0x01U
/* Service Id of Adc_StartGroupConversion */
#define ADC_START_GROUP_CONVERSION_SID     (uint8)0x02U
/* Service Id of Adc_StopGroupConversion */
#define ADC_STOP_GROUP_CONVERSION_SID      (uint8)0x03U
/* Service Id of Adc_ReadGroup */
#define ADC_READ_GROUP_SID                 (uint8)0x04U
/* Service Id of Adc_EnableHardwareTrigger */
#define ADC_ENABLE_HARDWARE_TRIGGER_SID    (uint8)0x05U
/* Service Id of Adc_DisableHardwareTrigger */
#define ADC_DISABLE_HARDWARE_TRIGGER_SID   (uint8)0x06U
/* Service Id of Adc_EnableGroupNotification */
#define ADC_ENABLE_GROUP_NOTIFICATION_SID  (uint8)0x07U                                                                 /* PRQA S 1534 # JV-01 */
/* Service Id of Adc_DisableGroupNotification */
#define ADC_DISABLE_GROUP_NOTIFICATION_SID (uint8)0x08U                                                                 /* PRQA S 1534 # JV-01 */
/* Service Id of Adc_GetGroupStatus */
#define ADC_GET_GROUP_STATUS_SID           (uint8)0x09U                                                                 /* PRQA S 1534 # JV-01 */
/* Service Id of Adc_GetVersionInfo */
#define ADC_GET_VERSION_INFO_SID           (uint8)0x0AU                                                                 /* PRQA S 1534 # JV-01 */
/* Service Id of Adc_GetStreamLastPointer */
#define ADC_GET_STREAM_LAST_POINTER_SID    (uint8)0x0BU
/* Service Id of Adc_SetupResultBuffer */
#define ADC_SETUP_RESULT_BUFFER_SID        (uint8)0x0CU
/* Service Id of Adc_DisableChannel */
#define ADC_DISABLE_CHANNEL_SID            (uint8)0xA0U                                                                 /* PRQA S 1534 # JV-01 */
/* Service Id of Adc_EnableChannel */
#define ADC_ENABLE_CHANNEL_SID             (uint8)0xA1U                                                                 /* PRQA S 1534 # JV-01 */


/***********************************************************************************************************************
**                                                  DET Error Codes                                                   **
***********************************************************************************************************************/
/* API service called without module initialization is reported using following error code */
#define ADC_E_UNINIT                       (uint8)0x0AU                                                                 /* PRQA S 1534 # JV-01 */

/*
 * API services Adc_StartGroupConversion, Adc_EnableHardwareTrigger, Adc_SetupResultBuffer and Adc_DeInit called
 * when the timer is already running is reported using following error code
 */
#define ADC_E_BUSY                         (uint8)0x0BU

/* API service Adc_StopGroupConversion called while no conversion was running is reported using following error code */
#define ADC_E_IDLE                         (uint8)0x0CU

/* API service Adc_Init called while ADC is already initialized is reported using following error code */
#define ADC_E_ALREADY_INITIALIZED          (uint8)0x0DU                                                                 /* PRQA S 1534 # JV-01 */

/* API service Adc_Init called with incorrect configuration is reported using following error code */
#define ADC_E_PARAM_CONFIG                 (uint8)0x0EU                                                                 /* PRQA S 1534 # JV-01 */

/* API service Adc_SetupResultBuffer or Adc_GetVersionInfo called with invalid data buffer pointer, NULL_PTR passed */
#define ADC_E_PARAM_POINTER                (uint8)0x14U                                                                 /* PRQA S 1534 # JV-01 */

/* API service called with invalid Group ID is reported using following error code */
#define ADC_E_PARAM_GROUP                  (uint8)0x15U                                                                 /* PRQA S 1534 # JV-01 */

/*
 * API services Adc_EnableHardwareTrigger or Adc_DisableHardwareTrigger called on a group
 * with conversion mode configured as continuous
 */
#define ADC_E_WRONG_CONV_MODE              (uint8)0x16U                                                                 /* PRQA S 1534 # JV-01 */

/*
 * API services Adc_EnableHardwareTrigger or Adc_DisableHardwareTrigger called on a group
 * with trigger source configured as software is reported using following error code
 */
#define ADC_E_WRONG_TRIGG_SRC              (uint8)0x17U                                                                 /* PRQA S 1534 # JV-01 */

/*
 * API services Adc_EnableGroupNotification or Adc_DisableGroupNotification called on a group
 * whose configuration set has no notification available is reported using following error code
 */
#define ADC_E_NOTIF_CAPABILITY             (uint8)0x18U                                                                 /* PRQA S 1534 # JV-01 */

/*
 * API services Adc_StartGroupConversion or Adc_EnableHardwareTrigger called on a group
 * whose result buffer pointer not initialized is reported using following error code
 */
#define ADC_E_BUFFER_UNINIT                (uint8)0x19U                                                                 /* PRQA S 1534 # JV-01 */

/* API service Adc_Init called without/with a wrong database is reported using following error code */
#define ADC_E_INVALID_DATABASE             (uint8)0xEFU                                                                 /* PRQA S 1534 # JV-01 */

/*
 * API service Adc_DisableChannel and Adc_EnableChannel called with invalid
 * channel is reported using following error code.
 * API service Adc_DisableChannel called so that total available channels is
 * zero afterwards is reported using following error code.
 */
#define ADC_E_PARAM_CHANNEL                (uint8)0xEEU                                                                 /* PRQA S 1534 # JV-01 */

/* API service called with an wrong core */
#define ADC_E_INVALID_CORE                 (uint8)0xF0U                                                                 /* PRQA S 1534 # JV-01 */
/* API service called when the request is already busy */
#define ADC_E_REQUEST_FALSE                (uint8)0xF1U                                                                 /* PRQA S 1534 # JV-01 */

/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/
#define ADC_START_SEC_PUBLIC_CODE_LOCAL
#include "Adc_MemMap.h"

extern FUNC(void, ADC_PUBLIC_CODE) Adc_Init(P2CONST(Adc_ConfigType, AUTOMATIC, ADC_CONFIG_DATA) ConfigPtr);

#if (ADC_DEINIT_API == STD_ON)
extern FUNC(void, ADC_PUBLIC_CODE) Adc_DeInit(void);
#endif

#define ADC_STOP_SEC_PUBLIC_CODE_LOCAL
#include "Adc_MemMap.h"

#define ADC_START_SEC_PUBLIC_CODE_GLOBAL
#include "Adc_MemMap.h"

#if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
extern FUNC(void, ADC_PUBLIC_CODE) Adc_StartGroupConversion(Adc_GroupType Group);
extern FUNC(void, ADC_PUBLIC_CODE) Adc_StopGroupConversion(Adc_GroupType Group);
#endif

#if (ADC_READ_GROUP_API == STD_ON)
extern FUNC(Std_ReturnType, ADC_PUBLIC_CODE) Adc_ReadGroup(Adc_GroupType Group,
  P2VAR(Adc_ValueGroupType, AUTOMATIC, ADC_APPL_DATA) DataBufferPtr);                                                   /* PRQA S 3432 # JV-01 */
#endif

#if (ADC_HW_TRIGGER_API == STD_ON)
extern FUNC(void, ADC_PUBLIC_CODE) Adc_EnableHardwareTrigger(Adc_GroupType Group);
extern FUNC(void, ADC_PUBLIC_CODE) Adc_DisableHardwareTrigger(Adc_GroupType Group);
#endif

#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
extern FUNC(void, ADC_PUBLIC_CODE) Adc_EnableGroupNotification(Adc_GroupType Group);
extern FUNC(void, ADC_PUBLIC_CODE) Adc_DisableGroupNotification(Adc_GroupType Group);
#endif

extern FUNC(Adc_StatusType, ADC_PUBLIC_CODE) Adc_GetGroupStatus(Adc_GroupType Group);
extern FUNC(Adc_StreamNumSampleType, ADC_PUBLIC_CODE) Adc_GetStreamLastPointer(Adc_GroupType Group,
  P2VAR(P2VAR(Adc_ValueGroupType, ADC_APPL_DATA, ADC_APPL_DATA), AUTOMATIC, ADC_APPL_DATA) PtrToSamplePtr);             /* PRQA S 3432 # JV-01 */

#if (ADC_ENABLE_DISABLE_CHANNEL == STD_ON)
extern FUNC(void, ADC_PUBLIC_CODE) Adc_DisableChannel(Adc_GroupType Group, Adc_ChannelType ChannelId);
extern FUNC(void, ADC_PUBLIC_CODE) Adc_EnableChannel(Adc_GroupType Group, Adc_ChannelType ChannelId);
#endif

#if (ADC_VERSION_INFO_API == STD_ON)
extern FUNC(void, ADC_PUBLIC_CODE) Adc_GetVersionInfo(
  P2VAR(Std_VersionInfoType, AUTOMATIC, ADC_APPL_DATA) versioninfo);                                                    /* PRQA S 3432 # JV-01 */
#endif

extern FUNC(Std_ReturnType, ADC_PUBLIC_CODE) Adc_SetupResultBuffer(Adc_GroupType Group,
  P2VAR(Adc_ValueGroupType, AUTOMATIC, ADC_APPL_DATA) DataBufferPtr);                                                   /* PRQA S 3432 # JV-01 */

#define ADC_STOP_SEC_PUBLIC_CODE_GLOBAL
#include "Adc_MemMap.h"

#define ADC_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Adc_MemMap.h"

/* Declaration for ADC Database */
extern CONST(Adc_ConfigType, ADC_CONFIG_DATA) Adc_GaaConfiguration[];                                                   /* PRQA S 3684 # JV-01 */

#define ADC_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Adc_MemMap.h"

#endif /* ADC_H */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
