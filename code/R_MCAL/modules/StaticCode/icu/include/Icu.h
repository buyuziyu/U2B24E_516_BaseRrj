/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Icu.h                                                                                               */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains macros, ICU type definitions, structure data types and API function prototypes of ICU Driver    */
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
 * 2.4.1:  30/06/2025  : Remove SW-VERSION in file header and update value of ICU_SW_PATCH_VERSION to 1
 * 2.4.0:  30/05/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.01 Release
 * 2.3.1:  31/03/2025  : Update SW-VERSION for RH850/U2BxE MCAL Ver22.00.02 Release
 * 2.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release 
 *                       Change ICU_SW_MINOR_VERSION to 2 
 *                       Change ICU_SW_PATCH_VERSION to 0
 * 2.1.2:  31/10/2024  : Update SW-VERSION for Ver22.01.02 Beta2 Release 
 *                       As part of support QAC 9.5.0, following changes are made:
 *                       1. Remove QAC messages 1534, 1535, 1536.
 * 2.1.0:  09/03/2024  : Increase SW Version
 * 2.0.2:  10/01/2024  : Update ICU_SW_PATCH_VERSION to 2U
 * 2.0.1:  19/10/2023  : Add QAC messages 1534, 1535, 1536
 *         15/10/2023  : Change value of ICU_SW_PATCH_VERSION
 *         14/10/2023  : Change ICU_AR_R21_11_VERSION to ICU_AR_R22_11_VERSION
 *                       Change ICU_AR_RELEASE_MINOR_VERSION 7U to #define ICU_AR_RELEASE_MINOR_VERSION 8U
 *                       Change ICU_AR_R21_11_VERSION 470 to ICU_AR_R22_11_VERSION 480
 *                       Change memory section ICU_START/STOP_SEC_CONFIG_DATA_UNSPECIFIED to
 *                       ICU_START/STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
 * 2.0.0:  03/08/2023  : #include "Icu_Mapping.h" update to #include "Icu_MemMap.h"
 *                       Remove all multi-instance including methods
 *                       Remove all supported multi-instance header file
 *                       Add new det ID ICU_E_INVALID_CORE, ICU_E_REQUEST_FALSE
 *         20/04/2023  : Update value of ICU_SW_MAJOR_VERSION to 2, ICU_SW_MINOR_VERSION to 0
 *                       Update enum ETag_Icu_ActivationType
 * 1.5.0:  07/03/2023  : Update value of ICU_SW_MINOR_VERSION and ICU_SW_PATCH_VERSION
 * 1.4.5:  02/12/2022  : Add macro ICU_AR_2111_VERSION for support AR21-11
 *                     : Update value ICU_SW_PATCH_VERSION from 4 to 5
 * 1.4.4:  10/06/2022  : Update value ICU_SW_PATCH_VERSION from 3 to 4
 * 1.4.3:  17/04/2022  : Merge QAC message from U2Ax, E2x and U2Bx
 *         07/04/2022  : Update value ICU_GET_INPUT_LEVEL_SID from 0x18 to 0xA0
 *                       Update value ICU_SW_PATCH_VERSION from 2 to 3
 * 1.4.2:  01/03/2022  : Update value ICU_SW_PATCH_VERSION from 1 to 2
 * 1.4.1:  06/12/2021  : Update value of ICU_SW_MINOR_VERSION and ICU_SW_PATCH_VERSION
 *         18/10/2021  : Add QAC message 9.5.0
 *         15/09/2021  : Add STag_Icu_PINChannelUserRegConfigType, STag_Icu_PINChannelConfigType
 * 1.3.2:  30/08/2021  : Change from #include "Icu_MemMap.h" to #include "Icu_Mapping.h".
 *                       Update header file macro.
 * 1.3.2:  12/08/2021  : Update value of ICU_SW_PATCH_VERSION
 * 1.3.1:  02/07/2021  : Add QAC message 9.5.0
 *                       Format source code to 120 characters
 *                       Improve Violation tag (remove START/END)
 * 1.2.0:  17/07/2020  : Release
 * 1.1.0:  19/06/2020  : Release
 * 1.0.0:  25/03/2020  : Initial Version
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
/* Message (2:3630)    : The implementation of this struct/union type should be hidden.                               */
/* Rule                : MISRA C:2012 Dir-4.8                                                                         */
/* JV-01 Justification : This is accepted. Redundant of struct or union type has no affect to driver operation.       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3684)    : Array declared with unknown size.                                                            */
/* Rule                : MISRA C:2012 Rule-8.11, CERTCCM ARR02                                                        */
/* JV-01 Justification : Arrays used are verified in the file which are only declarations and size is configuration   */
/*                       dependent.                                                                                   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/**********************************************************************************************************************/
#ifndef ICU_H
#define ICU_H

#define ICU_AR_422_VERSION      422
#define ICU_AR_431_VERSION      431
#define ICU_AR_R22_11_VERSION   480
/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/

/* Included for Icu_Cfg.h inclusion and To publish the type Icu_ConfigType */
#include "Icu_Types.h"
#if (ICU_REPORT_WAKEUP_SOURCE == STD_ON)
/* Included for the declaration of EcuM_SetWakeupEvent() */
#include "EcuM_Cbk.h"
#endif

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* Vendor and Module IDs */
#define ICU_VENDOR_ID   ICU_VENDOR_ID_VALUE
#define ICU_MODULE_ID   ICU_MODULE_ID_VALUE
#define ICU_INSTANCE_ID ICU_INSTANCE_ID_VALUE

#if (ICU_AR_VERSION == ICU_AR_422_VERSION)
/* AUTOSAR release version information */
#define ICU_AR_RELEASE_MAJOR_VERSION     4U
#define ICU_AR_RELEASE_MINOR_VERSION     2U
#define ICU_AR_RELEASE_REVISION_VERSION  2U

#elif (ICU_AR_VERSION == ICU_AR_431_VERSION) /* #elif (ICU_AR_VERSION == ICU_AR_431_VERSION) */
#define ICU_AR_RELEASE_MAJOR_VERSION     4U
#define ICU_AR_RELEASE_MINOR_VERSION     3U
#define ICU_AR_RELEASE_REVISION_VERSION  1U

#elif (ICU_AR_VERSION == ICU_AR_R22_11_VERSION) /* #elif (ICU_AR_VERSION == ICU_AR_R22_11_VERSION) */
#define ICU_AR_RELEASE_MAJOR_VERSION     4U
#define ICU_AR_RELEASE_MINOR_VERSION     8U
#define ICU_AR_RELEASE_REVISION_VERSION  0U
#endif

/* Module Software version information */
#define ICU_SW_MAJOR_VERSION             2U
#define ICU_SW_MINOR_VERSION             4U
#define ICU_SW_PATCH_VERSION             1U

/***********************************************************************************************************************
**                                               API Service Id Macros                                                **
***********************************************************************************************************************/
/* Service ID of Icu_Init */
#define ICU_INIT_SID                             (uint8)0x00
/* Service ID of Icu_DeInit */
#define ICU_DEINIT_SID                           (uint8)0x01
/* Service ID of Icu_SetMode */
#define ICU_SET_MODE_SID                         (uint8)0x02
/* Service ID of Icu_DisableWakeup */
#define ICU_DISABLE_WAKEUP_SID                   (uint8)0x03
/* Service ID of Icu_EnableWakeup */
#define ICU_ENABLE_WAKEUP_SID                    (uint8)0x04
/* Service ID of Icu_SetActivationCondition */
#define ICU_SET_ACTIVATION_CONDITION_SID         (uint8)0x05
/* Service ID of Icu_DisableNotification */
#define ICU_DISABLE_NOTIFICATION_SID             (uint8)0x06
/* Service ID of Icu_EnableNotification */
#define ICU_ENABLE_NOTIFICATION_SID              (uint8)0x07
/* Service ID of Icu_GetInputState */
#define ICU_GET_INPUT_STATE_SID                  (uint8)0x08
/* Service ID of Icu_StartTimestamp */
#define ICU_START_TIMESTAMP_SID                  (uint8)0x09
/* Service ID of Icu_StopTimestamp */
#define ICU_STOP_TIMESTAMP_SID                   (uint8)0x0A
/* Service ID of Icu_GetTimestampIndex */
#define ICU_GET_TIMESTAMP_INDEX_SID              (uint8)0x0B
/* Service ID of Icu_ResetEdgeCount */
#define ICU_RESET_EDGE_COUNT_SID                 (uint8)0x0C
/* Service ID of Icu_EnableEdgeCount */
#define ICU_ENABLE_EDGE_COUNT_SID                (uint8)0x0D
/* Service ID of Icu_DisableEdgeCount */
#define ICU_DISABLE_EDGE_COUNT_SID               (uint8)0x0E
/* Service ID of Icu_GetEdgeNumbers */
#define ICU_GET_EDGE_NUMBERS_SID                 (uint8)0x0F
/* Service ID of Icu_GetTimeElapsed */
#define ICU_GET_TIME_ELAPSED_SID                 (uint8)0x10
/* Service ID of Icu_GetDutyCycleValues */
#define ICU_GET_DUTY_CYCLE_VALUES_SID            (uint8)0x11
/* Service ID of Icu_GetVersionInfo */
#define ICU_GET_VERSION_INFO_SID                 (uint8)0x12
/* Service ID of Icu_StartSignalMeasurement */
#define ICU_START_SIGNAL_MEASUREMENT_SID         (uint8)0x13
/* Service ID of Icu_StopSignalMeasurement */
#define ICU_STOP_SIGNAL_MEASUREMENT_SID          (uint8)0x14
/* Service ID of Icu_CheckWakeup */
#define ICU_CHECK_WAKEUP_SID                     (uint8)0x15
/* Service ID of Icu_EnableEdgeDetection */
#define ICU_ENABLE_EDGE_DETECTION_SID            (uint8)0x16
/* Service ID of Icu_DisableEdgeDetection */
#define ICU_DISABLE_EDGE_DETECTION_SID           (uint8)0x17
/* Service ID of Icu_GetInputLevel */
#define ICU_GET_INPUT_LEVEL_SID                  (uint8)0xA0
/* Service ID of Icu_GetTAUCountValue */
#define ICU_GET_COUNT_VALUE_SID                  (uint8)0x19

/***********************************************************************************************************************
**                                                  DET Error Codes                                                   **
***********************************************************************************************************************/

/* DET code to report that API is called with an invalid pointer */

#define ICU_E_PARAM_POINTER              (uint8)0x0AU
/*
 * DET code to report that API service used with an invalid Channel Identifier
 * or Channel is not configured for the functionality of the calling API.
 */
#define ICU_E_PARAM_CHANNEL              (uint8)0x0BU

/* DET code to report that API service used with an invalid or not feasible activation. */
#define ICU_E_PARAM_ACTIVATION           (uint8)0x0CU

/* DET code to report that API service used with Init function failed. */

#define ICU_E_INIT_FAILED                (uint8)0x0DU

/* DET code to report that API service used with invalid buffer size. */
#define ICU_E_PARAM_BUFFER_SIZE          (uint8)0x0EU

/* DET code to report that API service Icu_SetMode is used with an invalid operation mode. */
#define ICU_E_PARAM_MODE                 (uint8)0x0FU

/* DET code to report that API service used without module initialization. */
#define ICU_E_UNINIT                     (uint8)0x14U

/* DET code to report that the API Icu_StopTimestamp was used on a channel that was not started or already stopped. */
#define ICU_E_NOT_STARTED                (uint8)0x15U

/* DET code to report that the API Icu_SetMode is used during a running operation. */
#define ICU_E_BUSY_OPERATION             (uint8)0x16U

/* DET code to report that ICU is already initialized when Icu_Init() is called. */
#define ICU_E_ALREADY_INITIALIZED        (uint8)0x17U

/* DET code to report that the API Icu_StartTimeStamp invoked with NotifyInterval < 1. */
#define ICU_E_PARAM_NOTIFY_INTERVAL      (uint8)0x18U

/* DET code to report that the API Icu_GetVersionInfo invoked with a null pointer. */
#define ICU_E_PARAM_VINFO                (uint8)0x19U

/* API service Icu_Init called without a database is reported using the following error code.*/
#define ICU_E_INVALID_DATABASE           (uint8)0xEFU

/*
 * DET code to report that Icu API service Icu_DisableNotification
 * is invoked for the channel for which the notification is already disabled.
 */
#define ICU_E_ALREADY_DISABLED           (uint8)0xF1U

/*
 * DET code to report that Icu API service Icu_EnableNotification
 * is invoked for the channel for which the notification is already enabled.
*/
#define ICU_E_ALREADY_ENABLED            (uint8)0xF2U

/* DET code to report invalid core mapping service */
#define ICU_E_INVALID_CORE               (uint8)0xEDU
/* DET code to report service is being requested by other cores */
#define ICU_E_REQUEST_FALSE              (uint8)0xEEU

/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/
/* Numeric identifier of an ICU Channel */
typedef uint8 Icu_ChannelType;

/* Input state of an ICU channel */
typedef enum ETag_Icu_InputStateType                                                                                    
{
  ICU_ACTIVE,
  ICU_IDLE
} Icu_InputStateType;

/* Input level of an ICU channel */
typedef enum ETag_Icu_LevelType                                                                                         
{
  ICU_LOW,
  ICU_HIGH
} Icu_LevelType;
/* Definition of the type of activation of an ICU Channel */
typedef enum ETag_Icu_ActivationType                                                                                    
{
  ICU_RISING_EDGE,
  ICU_FALLING_EDGE,
  ICU_BOTH_EDGES
} Icu_ActivationType;

/* Width of the buffer for storing time in terms of timer ticks  */
typedef uint32 Icu_ValueType;

/* Type which contains the values needed for calculating duty cycles */
typedef struct STag_Icu_DutyCycleType                                                                                   /* PRQA S 3630 # JV-01 */
{
  Icu_ValueType ActiveTime;
  Icu_ValueType PeriodTime;
} Icu_DutyCycleType;

/* Type to abstract the return value of the service Icu_GetTimestampIndex() */
typedef uint16 Icu_IndexType;

/* Type to abstract the return value of the service Icu_GetEdgeNumbers() */
typedef uint32 Icu_EdgeNumberType;

/* Type to abstract the return value of the service Icu_GetTAUCountValue() */
typedef uint32 Icu_CounterValueType;

/* Definition of the measurement mode type */
typedef enum ETag_Icu_MeasurementModeType                                                                               
{
  ICU_MODE_SIGNAL_EDGE_DETECT,
  ICU_MODE_SIGNAL_MEASUREMENT,
  ICU_MODE_TIMESTAMP,
  ICU_MODE_EDGE_COUNTER
} Icu_MeasurementModeType;

/* Definition of the signal measurement property type */
typedef enum ETag_Icu_SignalMeasurementPropertyType                                                                     
{
  ICU_LOW_TIME,
  ICU_HIGH_TIME,
  ICU_PERIOD_TIME,
  ICU_DUTY_CYCLE
} Icu_SignalMeasurementPropertyType;

/* Definition of the timestamp measurement property type */
typedef enum ETag_Icu_TimestampBufferType                                                                               
{
  ICU_LINEAR_BUFFER,
  ICU_CIRCULAR_BUFFER
} Icu_TimestampBufferType;
/* Channel User Mode Regs*/
#if (ICU_IRQ_EDGE_DETECT == STD_ON)
typedef uint16 Icu_UserModeSettingType;
#else
typedef uint8 Icu_UserModeSettingType;
#endif

/***********************************************************************************************************************
**                                       Structure for PIN Timer Channel information                                  **
***********************************************************************************************************************/
typedef struct STag_Icu_PINChannelUserRegConfigType
{
  Icu_UserModeSettingType ddChannelModeUserRegSettings;
} Icu_PINChannelUserRegConfigType;

/***********************************************************************************************************************
**                                         Structure for ICU Channel information                                      **
***********************************************************************************************************************/
typedef struct STag_Icu_PINChannelConfigType
{
  /* void pointer to the base address of channel user control register structure */
  P2VAR(void, TYPEDEF, REGSPACE) pEXINSTCRegsAddress;
} Icu_PINChannelConfigType;

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/
#define ICU_START_SEC_PUBLIC_CODE_LOCAL
#include "Icu_MemMap.h"

extern FUNC(void, ICU_PUBLIC_CODE) Icu_Init(P2CONST(Icu_ConfigType, AUTOMATIC, ICU_APPL_CONST) ConfigPtr);

#if (ICU_DE_INIT_API == STD_ON)
extern FUNC(void, ICU_PUBLIC_CODE) Icu_DeInit(void);
#endif

#if (ICU_SET_MODE_API == STD_ON)
extern FUNC(void, ICU_PUBLIC_CODE) Icu_SetMode(Icu_ModeType Mode);
#endif

#if ((ICU_WAKEUP_FUNCTIONALITY_API == STD_ON) && (ICU_REPORT_WAKEUP_SOURCE == STD_ON))
extern FUNC(void, ICU_PUBLIC_CODE) Icu_CheckWakeup(EcuM_WakeupSourceType WakeupSource);
#endif

#define ICU_STOP_SEC_PUBLIC_CODE_LOCAL
#include "Icu_MemMap.h"

#define ICU_START_SEC_PUBLIC_CODE_GLOBAL
#include "Icu_MemMap.h"

#if (ICU_DISABLE_WAKEUP_API == STD_ON)
extern FUNC(void, ICU_PUBLIC_CODE) Icu_DisableWakeup(Icu_ChannelType Channel);
#endif

#if (ICU_ENABLE_WAKEUP_API == STD_ON)
extern FUNC(void, ICU_PUBLIC_CODE) Icu_EnableWakeup(Icu_ChannelType Channel);
#endif

extern FUNC(void, ICU_PUBLIC_CODE) Icu_SetActivationCondition(Icu_ChannelType Channel, Icu_ActivationType Activation);

extern FUNC(void, ICU_PUBLIC_CODE) Icu_DisableNotification(Icu_ChannelType Channel);

extern FUNC(void, ICU_PUBLIC_CODE) Icu_EnableNotification(Icu_ChannelType Channel);

#if (ICU_GET_INPUT_STATE_API == STD_ON)
extern FUNC(Icu_InputStateType, ICU_PUBLIC_CODE) Icu_GetInputState(Icu_ChannelType Channel);
#endif

#if (ICU_GET_INPUT_LEVEL_API == STD_ON)
extern FUNC(Icu_LevelType, ICU_PUBLIC_CODE) Icu_GetInputLevel(Icu_ChannelType LddChannel);
#endif

#if (ICU_TIMESTAMP_API == STD_ON)
extern FUNC(void, ICU_PUBLIC_CODE)
    Icu_StartTimestamp(Icu_ChannelType Channel, P2VAR(Icu_ValueType, AUTOMATIC, ICU_APPL_DATA) BufferPtr,               /* PRQA S 3432 # JV-01 */
                                                                            uint16 BufferSize, uint16 NotifyInterval);

extern FUNC(void, ICU_PUBLIC_CODE) Icu_StopTimestamp(Icu_ChannelType Channel);

extern FUNC(Icu_IndexType, ICU_PUBLIC_CODE) Icu_GetTimestampIndex(Icu_ChannelType Channel);
#endif

#if (ICU_EDGE_COUNT_API == STD_ON)
extern FUNC(void, ICU_PUBLIC_CODE) Icu_ResetEdgeCount(Icu_ChannelType Channel);

extern FUNC(void, ICU_PUBLIC_CODE) Icu_EnableEdgeCount(Icu_ChannelType Channel);

extern FUNC(void, ICU_PUBLIC_CODE) Icu_DisableEdgeCount(Icu_ChannelType Channel);

extern FUNC(Icu_EdgeNumberType, ICU_PUBLIC_CODE) Icu_GetEdgeNumbers(Icu_ChannelType Channel);
#endif

#if (ICU_EDGE_DETECT_API == STD_ON)
extern FUNC(void, ICU_PUBLIC_CODE) Icu_EnableEdgeDetection(Icu_ChannelType Channel);

extern FUNC(void, ICU_PUBLIC_CODE) Icu_DisableEdgeDetection(Icu_ChannelType Channel);
#endif

#if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)
extern FUNC(void, ICU_PUBLIC_CODE) Icu_StartSignalMeasurement(Icu_ChannelType Channel);

extern FUNC(void, ICU_PUBLIC_CODE) Icu_StopSignalMeasurement(Icu_ChannelType Channel);
#endif

#if (ICU_GET_TIME_ELAPSED_API == STD_ON)
extern FUNC(Icu_ValueType, ICU_PUBLIC_CODE) Icu_GetTimeElapsed(Icu_ChannelType Channel);
#endif

#if (ICU_GET_DUTY_CYCLE_VALUES_API == STD_ON)
extern FUNC(void, ICU_PUBLIC_CODE)Icu_GetDutyCycleValues(Icu_ChannelType Channel,
                                                   P2VAR(Icu_DutyCycleType, AUTOMATIC, ICU_APPL_DATA) DutyCycleValues); /* PRQA S 3432 # JV-01 */
#endif

#if (ICU_GET_TAU_COUNT_VALUE_API == STD_ON)
extern FUNC(Icu_CounterValueType, ICU_PUBLIC_CODE) Icu_GetTAUInCountValue(Icu_ChannelType LddChannel);
#endif

#if (ICU_GET_VERSION_INFO_API == STD_ON)
extern FUNC(void, ICU_PUBLIC_CODE) Icu_GetVersionInfo(
                                                     P2VAR(Std_VersionInfoType, AUTOMATIC, ICU_APPL_DATA) versioninfo); /* PRQA S 3432 # JV-01 */
#endif /* End of (ICU_GET_VERSION_INFO_API == STD_ON) */

#define ICU_STOP_SEC_PUBLIC_CODE_GLOBAL
#include "Icu_MemMap.h"

/**********************************************************************************************************************/
#define ICU_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Icu_MemMap.h"
/* Declaration for ICU Database */
extern CONST(Icu_ConfigType, ICU_CONFIG_DATA) Icu_GaaConfiguration[];                                                   /* PRQA S 3684 # JV-01 */
#define ICU_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Icu_MemMap.h"

#endif /* ICU_H  */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
