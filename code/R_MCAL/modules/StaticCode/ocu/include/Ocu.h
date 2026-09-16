/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2X MCAL Components                                                                 */
/* Module       = Ocu.h                                                                                               */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2023-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Provision of API information.                                                                                      */
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
 *  1.4.1  30/06/2025  : Update SW-VERSION for RH850/U2Bx MCAL Ver22.02.00.001 and RH850/U2Bx-E MCAL Ver22.00.03
 *  1.4.0  30/05/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.01
 *  1.3.1  31/03/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 and RH850/U2Bx-E MCAL Ver22.00.02 Release
 *  1.3.0  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 *                       Change OCU_SW_MINOR_VERSION from 1 to 3   
 *  1.2.0  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 *                       Change OCU_SW_MINOR_VERSION from 1 to 2 
 *                       Change OCU_SW_PATCH_VERSION from 1 to 0 
 *  1.1.1  10/06/2024  : Change OCU_SW_MINOR_VERSION from 0 to 1
 *                       Change OCU_SW_PATCH_VERSION from 3 to 1
 *                       Up value of OCU_SW_PATCH_VERSION from 2U to 3U
 *  1.1.0  21/02/2024  : Update SW version to 1.1.0
 *  1.0.2  10/01/2024  : Update SW version to 1.0.2
 *  1.0.1  17/10/2023  : Add new QAC message 1534
           25/09/2023  : Update sec OCU_START_SEC_CONFIG_DATA_UNSPECIFIED to 
                         OCU_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
                         Remove OCU_AR_R21_11_VERSION, add OCU_AR_R22_11_VERSION, update release, file version
                         Reason: Support AR22-11 from AR22-11 for OCU
 *  1.0.0  29/03/2023  : Initial Version
 */
/**********************************************************************************************************************/
/***********************************************************************************************************************
**                                             Margin for Control History                                             **
***********************************************************************************************************************/
#ifndef OCU_H
#define OCU_H
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

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for using Std Type(e.g. STD_ON), Compiler Macros(e.g. P2FUNC), Platform Types(e.g. uint8) */
#include "Std_Types.h"
/* Included for OCU module-specific definitions */
#include "Ocu_Cfg.h"
/* Included for Type definitions */
#include "Ocu_Types.h"
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR version information */
#define OCU_AR_R22_11_VERSION 480

/* Version identification */
#define OCU_VENDOR_ID   OCU_VENDOR_ID_VALUE
#define OCU_MODULE_ID   OCU_MODULE_ID_VALUE
#define OCU_INSTANCE_ID OCU_INSTANCE_ID_VALUE


/* AUTOSAR release version information */
#if (OCU_AR_VERSION == OCU_AR_R22_11_VERSION)
#define OCU_AR_RELEASE_MAJOR_VERSION    4U
#define OCU_AR_RELEASE_MINOR_VERSION    8U
#define OCU_AR_RELEASE_REVISION_VERSION 0U
#endif

/* File version information */
#define OCU_SW_MAJOR_VERSION            1U
#define OCU_SW_MINOR_VERSION            4U
#define OCU_SW_PATCH_VERSION            1U

/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                    Service IDs                                                     **
***********************************************************************************************************************/


/* Service Id of Ocu_Init */
#define OCU_INIT_SID                          (uint8)0x00U
/* Service Id of Ocu_DeInit */
#define OCU_DEINIT_SID                        (uint8)0x01U
/* Service Id of Ocu_StartChannel */
#define OCU_START_CHANNEL_SID                 (uint8)0x02U
/* Service Id of Ocu_StopChannel */
#define OCU_STOP_CHANNEL_SID                  (uint8)0x03U
/* Service Id of Ocu_SetPinState */
#define OCU_SET_PIN_STATE_SID                 (uint8)0x04U
/* Service Id of Ocu_SetPinAction */
#define OCU_SET_PIN_ACTION_SID                (uint8)0x05U
/* Service Id of Ocu_GetCounter */
#define OCU_SET_GET_COUNTER_SID               (uint8)0x06U
/* Service Id of Ocu_SetAbsoluteThreshold */
#define OCU_SET_ABSOLUTE_THRESHOLD_SID        (uint8)0x07U
/* Service Id of Ocu_SetRelativeThreshold  */
#define OCU_SET_RELATIVE_THRESHOLD_SID        (uint8)0x08U
/* Service Id of Ocu_GetVersionInfo */
#define OCU_GET_VERSION_INFO_SID              (uint8)0x09U
/* Service Id of Ocu_DisableNotification */
#define OCU_DISABLE_NOTIFICATION_SID          (uint8)0x0AU
/* Service Id of Ocu_EnableNotification */
#define OCU_ENABLE_NOTIFICATION_SID           (uint8)0x0BU

/***********************************************************************************************************************
**                                                  DET Error Codes                                                   **
***********************************************************************************************************************/

/* API services other than Ocu_GetVersionInfo() and Ocu_init() used without module initialization */
#define OCU_E_UNINIT                        (uint8)0x02U
/* API services used with an invalid channel Identifier.  */
#define OCU_E_PARAM_INVALID_CHANNEL         (uint8)0x03U
/* API Ocu_SetPinState() called with an invalid pin state or when the channel is in the RUNNING state */
#define OCU_E_PARAM_INVALID_STATE           (uint8)0x04U
/* API Ocu_SetPinAction() called with an invalid pin action */
#define OCU_E_PARAM_INVALID_ACTION          (uint8)0x05U
/* Usage of Ocu_DisableNotification() or Ocu_EnableNotification() on a channel where a NULL pointer is configured as
the notification function */
#define OCU_E_NO_VALID_NOTIF                (uint8)0x06U
/* API Ocu_Init() called while the OCU driver has already been initialized */
#define OCU_E_ALREADY_INITIALIZED           (uint8)0x07U
/* API Ocu_GetVersionInfo() is called with a NULL parameter */
#define OCU_E_PARAM_POINTER                 (uint8)0x08U
/* API Ocu_StartChannel() called on a channel that is in state RUNNING */
#define OCU_E_BUSY                          (uint8)0x09U
/* Ocu_SetPinState() or Ocu_SetPinAction() called for a channel that doesn't have an associated output pin */
#define OCU_E_PARAM_NO_PIN                  (uint8)0x0AU
/* OCU initialization has failed, e.g. selected configuration set doesn't exist */
#define OCU_E_INIT_FAILED                   (uint8)0x0BU
/* API Ocu_SetAbsoluteThreshold() and Ocu_SetRelativeThreshold called with a threshold large than the max value
that the counter is able to count */
#define OCU_E_PARAM_INVALID_THRESHOLD       (uint8)0x0CU
/* DET code to report invalid database */
#define OCU_E_INVALID_DATABASE              (uint8)0xEFU
/* DET code to report the service has not been executed after polling */
#define OCU_E_REQUEST_ONGOING               (uint8)0xECU
/* DET code to report invalid core mapping service */
#define OCU_E_INVALID_CORE                  (uint8)0xEDU
/* DET code to report service is being requested by other cores */
#define OCU_E_REQUEST_FALSE                 (uint8)0xEEU
/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/
#define OCU_START_SEC_PUBLIC_CODE_LOCAL
#include "Ocu_MemMap.h"

extern FUNC(void, OCU_PUBLIC_CODE) Ocu_Init(P2CONST(Ocu_ConfigType, AUTOMATIC, OCU_APPL_CONST) ConfigPtr);
#if (OCU_DE_INIT_API == STD_ON)

extern FUNC(void, OCU_PUBLIC_CODE) Ocu_DeInit(void);
#endif

#define OCU_STOP_SEC_PUBLIC_CODE_LOCAL
#include "Ocu_MemMap.h"


#define OCU_START_SEC_PUBLIC_CODE_GLOBAL
#include "Ocu_MemMap.h"

extern FUNC(Std_ReturnType, OCU_PUBLIC_CODE) Ocu_StartChannel(Ocu_ChannelType ChannelNumber);
extern FUNC(void, OCU_PUBLIC_CODE) Ocu_StopChannel(Ocu_ChannelType ChannelNumber);

#if (OCU_SET_PIN_STATE_API == STD_ON)
extern FUNC(void, OCU_PUBLIC_CODE) Ocu_SetPinState(Ocu_ChannelType ChannelNumber, Ocu_PinStateType PinState);
#endif

#if (OCU_SET_PIN_ACTION_API == STD_ON)
extern FUNC(void, OCU_PUBLIC_CODE) Ocu_SetPinAction(Ocu_ChannelType ChannelNumber, Ocu_PinActionType PinAction);
#endif

#if (OCU_GET_COUNTER_API == STD_ON)
extern FUNC(Ocu_ValueType, OCU_PUBLIC_CODE) Ocu_GetCounter(Ocu_ChannelType ChannelNumber);
#endif

#if (OCU_SET_ABSOLUTE_THRESHOLD_API == STD_ON)
extern FUNC(Ocu_ReturnType, OCU_PUBLIC_CODE) Ocu_SetAbsoluteThreshold(Ocu_ChannelType ChannelNumber,
                                                            Ocu_ValueType ReferenceValue, Ocu_ValueType AbsoluteValue);
#endif

#if (OCU_SET_RELATIVE_THRESHOLD_API == STD_ON)
extern FUNC(Ocu_ReturnType, OCU_PUBLIC_CODE) Ocu_SetRelativeThreshold(Ocu_ChannelType ChannelNumber,
                                                                                         Ocu_ValueType RelativeValue);
#endif

#if (OCU_NOTIFICATION_SUPPORTED == STD_ON)
extern FUNC(void, OCU_PUBLIC_CODE) Ocu_EnableNotification(Ocu_ChannelType ChannelNumber);
extern FUNC(void, OCU_PUBLIC_CODE) Ocu_DisableNotification(Ocu_ChannelType ChannelNumber);
#endif

#if (OCU_VERSION_INFO_API == STD_ON)
extern FUNC(void, OCU_PUBLIC_CODE)
                               Ocu_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, OCU_APPL_DATA) versioninfo);    /* PRQA S 3432 # JV-01 */
#endif

#define OCU_STOP_SEC_PUBLIC_CODE_GLOBAL
#include "Ocu_MemMap.h"


#define OCU_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Ocu_MemMap.h"
extern CONST(Ocu_ConfigType, OCU_CONST) Ocu_GaaConfiguration[];                                                         /* PRQA S 3684 # JV-01 */
#define OCU_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Ocu_MemMap.h"

#endif /* OCU_H */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
