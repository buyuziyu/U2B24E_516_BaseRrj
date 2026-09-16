/*====================================================================================================================*/
/* Project      = RH850/X2x AR4 MCAL Development                                                                      */
/* Module       = Pwm.h                                                                                               */
/*                                                                                                                    */
/*====================================================================================================================*/
/*                                                       COPYRIGHT                                                    */
/*====================================================================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.                                                */
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
/*                                              Devices:        X2x                                                   */
/*====================================================================================================================*/
/***********************************************************************************************************************
**                                              Revision Control History                                              **
***********************************************************************************************************************/
/*                                                                                                                    **
 * 2.5.1: 30/06/2025 : Remove SW-VERSION in header comment                                                            **
 * 2.5.0: 30/06/2025 : Update SW-VERSION for U2Ax Ver22.01.00(D) Final Release                                        **
 * 2.4.0: 31/05/2025 : Update SW-VERSION for U2Cx Ver21.01.01 Final Release                                           **
 * 2.3.2: 29/04/2025 : Update value of PWM_SW_PATCH_VERSION to 2U for U2Ax Ver22.00.04 Beta Release                   **
 * 2.3.1: 31/03/2025 : Update SW-VERSION for U2BxE Ver22.00.02 Beta Release                                           **
 * 2.3.0: 28/02/2025 : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release                        **
 *                     1. Change value of PWM_SW_MINOR_VERSION to 2U and PWM_SW_PATCH_VERSION to 3U                   **
 * 2.2.0: 31/12/2024 : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release:                                 **
 *                     1. Change value of PWM_SW_MINOR_VERSION to 2U and PWM_SW_PATCH_VERSION to 0U (2.1.2 to 2.2.0)  **
 * 2.1.2: 31/10/2024 : Update SW-VERSION for Ver22.01.02 U2Bx, Ver22.00.05 U2Cx Beta2 Release                         **
 *                     1. Change value of PWM_SW_PATCH_VERSION to 2U                                                  **
 * 2.1.1: 30/08/2024 : Update SW-VERSION for Ver22.01.01 U2Bx Beta Release                                            **
 *                     1. Change value of PWM_SW_MINOR_VERSION to 1U and PWM_SW_PATCH_VERSION to 1U (2.1.0 to 2.1.1)  **
 *                     As part of U2C support, following changes are made:                                            **
 *                     1. Remove QAC message 1534                                                                     **
 *                     2. Remove redundant QAC message                                                                **
 * 2.1.0: 21/02/2024 : Updated PWM_SW_MINOR_VERSION to "1U" (2.0.2 to 2.1.0)                                          **
 * 2.0.2: 10/12/2023 : Change value of PWM_SW_PATCH_VERSION to 2U                                                     **
 * 2.0.1: 21/10/2023 : Follow rule QAC 10.3.0, add new QAC message 1534                                               **
 *        18/10/2023 : Change value of PWM_SW_PATCH_VERSION to 1U                                                     **
 *        14/10/2023 : Change PWM_START/STOP_SEC_DBTOC_DATA_UNSPECIFIED to                                            **
 *                     PWM_START/STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED                                           **
 *                     Change "#define PWM_AR_RELEASE_MINOR_VERSION 7U" to "#define PWM_AR_RELEASE_MINOR_VERSION 8U"  **
 *                     Change "#define PWM_AR_R21_11_VERSION 470" to "#define PWM_AR_R22_11_VERSION 480"              **
 *                     Change condition compare PWM_AR_R21_11_VERSION to PWM_AR_R22_11_VERSION                        **
 * 2.0.0: 05/07/2023 : - Update from "Pwm_Mapping.h to "Pwm_MemMap.h". Remove #ifdef PWM_INSTANCE_INDEX               **
 *                     - Add new define PWM_E_INVALID_CORE, PWM_E_REQUEST_FALSE for DET check                         **
 *                     - Update from PWM_START_SEC_PUBLIC_CODE to PWM_START_SEC_PUBLIC_CODE_GLOBAL and                **
 *                     PWM_START_SEC_PUBLIC_CODE_LOCAL                                                                **
 *                      - Update QAC message                                                                          **
 *        06/06/2023 : Change macro PWM_AR_2111_VERSION to PWM_AR_R21_11_VERSION                                      **
 *        20/04/2023 : Updated PWM_SW_MAJOR_VERSION to "2U", PWM_SW_MINOR_VERSION to "0U",                            **
 *                     PWM_SW_PATCH_VERSION to "0U"                                                                   **
 * 1.4.5: 02/12/2022 : Updated PWM_SW_PATCH_VERSION to "5U"                                                           **
 *                     Add macro PWM_AR_2111_VERSION and AUTOSAR release version information for AR21-11              **
 * 1.4.4: 08/06/2022 : Updated PWM_SW_PATCH_VERSION to "4U"                                                           **
 * 1.4.3: 18/04/2022 : Removed un-used define PWM_E_REGISTER_WRITE_FAILED                                             **
 *        07/04/2022 : Removed redundant define PWM_MAIN_POWERTRANSITION_MANAGER                                      **
 *                     Updated PWM_SW_PATCH_VERSION to "3U"                                                           **
 * 1.4.2: 24/02/2022 : Updated PWM_SW_PATCH_VERSION to "2U"                                                           **
 * 1.4.1: 07/10/2021 : Updated PWM_SW_PATCH_VERSION to "1U"                                                           **
 * 1.4.0: 07/10/2021 : Updated PWM_SW_MINOR_VERSION to "4U", PWM_SW_PATCH_VERSION to "0U"                             **
 * 1.3.2: 23/08/2021 : Added PWM-Diag HW module.                                                                      **
 *        10/08/2021 : updated PWM_SW_PATCH_VERSION to "2"                                                            **
 *        04/08/2021 : Device specific implementation move to device specific file.                                   **
 *                     Error ID unified within device.                                                                **
 *                     Format source code unified within module.                                                      **
 * 1.3.1: 02/07/2021 : Add QAC message 9.5.0                                                                          **
 *                     Format source code to 120 characters                                                           **
 *                     Improve Violation tag (remove START/END)                                                       **
 *        15/05/2021 : Fixed Coding Rule and PWM_SW_PATCH_VERSION                                                     **
 * 1.3.0: 28/07/2020 : Updated SW-VERSION                                                                             **
 * 1.2.0: 28/07/2020 : Release                                                                                        **
 * 1.1.0: 19/06/2020 : Release                                                                                        **
 * 1.0.1: 22/05/2020 : Updated version information                                                                    **
 * 1.0.0: 24/03/2020 : Initial Version.                                                                               **
 *                                                                                                                    */
/**********************************************************************************************************************/

#ifndef PWM_H
#define PWM_H


/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for Type definitions */
#include "Std_Types.h"
/* Included for PWM module specific definitions */
#include "Pwm_Cfg.h"
/* Included for Pwm_Cfg.h inclusion and To publish the type Pwm_ConfigType */
#include "Pwm_Types.h"

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* Version identification */
#define PWM_VENDOR_ID   PWM_VENDOR_ID_VALUE
#define PWM_MODULE_ID   PWM_MODULE_ID_VALUE
#define PWM_INSTANCE_ID PWM_INSTANCE_ID_VALUE

/***********************************************************************************************************************
**                             To support different AUTOSAR releases in a single package                              **
***********************************************************************************************************************/
#define PWM_AR_422_VERSION 422
#define PWM_AR_431_VERSION 431
#define PWM_AR_R22_11_VERSION 480

/* AUTOSAR release version information */
#if (PWM_AR_VERSION == PWM_AR_422_VERSION)
#define PWM_AR_RELEASE_MAJOR_VERSION    4U
#define PWM_AR_RELEASE_MINOR_VERSION    2U
#define PWM_AR_RELEASE_REVISION_VERSION 2U
#elif (PWM_AR_VERSION == PWM_AR_431_VERSION)
#define PWM_AR_RELEASE_MAJOR_VERSION    4U
#define PWM_AR_RELEASE_MINOR_VERSION    3U
#define PWM_AR_RELEASE_REVISION_VERSION 1U
#elif (PWM_AR_VERSION == PWM_AR_R22_11_VERSION)
#define PWM_AR_RELEASE_MAJOR_VERSION    4U
#define PWM_AR_RELEASE_MINOR_VERSION    8U
#define PWM_AR_RELEASE_REVISION_VERSION 0U
#endif

/* Software module version information */
#define PWM_SW_MAJOR_VERSION             2U
#define PWM_SW_MINOR_VERSION             5U
#define PWM_SW_PATCH_VERSION             1U

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
**                                                    Service Ids                                                     **
***********************************************************************************************************************/

/* Service Id of Pwm_Init */
#define PWM_INIT_SID                     (uint8)0x00
/* Service Id of Pwm_DeInit */
#define PWM_DEINIT_SID                   (uint8)0x01
/* Service Id of Pwm_SetDutyCycle */
#define PWM_SET_DUTYCYCLE_SID            (uint8)0x02
/* Service Id of Pwm_SetPeriodAndDuty */
#define PWM_SET_PERIODANDDUTY_SID        (uint8)0x03
/* Service Id of Pwm_SetOutputToIdle */
#define PWM_SET_OUTPUTTOIDLE_SID         (uint8)0x04
/* Service Id of Pwm_GetOutputState */
#define PWM_GET_OUTPUTSTATE_SID          (uint8)0x05
/* Service Id of Pwm_DisableNotification */
#define PWM_DISABLENOTIFICATION_SID      (uint8)0x06
/* Service Id of Pwm_EnableNotification */
#define PWM_ENABLENOTIFICATION_SID       (uint8)0x07
/* Service Id of Pwm_GetVersionInfo */
#define PWM_GET_VERSION_INFO_SID         (uint8)0x08
/* Service Id of Pwm_SelectChannelClk */
#define PWM_SELECT_CHANNEL_CLK_SID       (uint8)0xA0
/* Service Id of Pwm_SynchronousInit */
#define PWM_SYNCHRONOUS_INIT_SID         (uint8)0xA1
/* Service Id of Pwm_SynchronousStart */
#define PWM_SYNCHRONOUS_START_SID        (uint8)0xA2
/* Service Id of Pwm_SynchronousStop */
#define PWM_SYNCHRONOUS_STOP_SID         (uint8)0xA3
/* Service Id of Pwm_SetChannelOutput */
#define PWM_SET_CHANNEL_OUTPUT_SID       (uint8)0xA4
/* Service Id of Pwm_SetTriggerDelay */
#define PWM_SET_TRIGGER_DELAY_SID        (uint8)0xA5
/* Service Id of Pwm_DiagReadAdConvResult */
#define PWM_READ_ADCONV_RESULT_SID       (uint8)0xA6
/* Service Id of Pwm_DiagDisableAdTrigger */
#define PWM_DISABLE_AD_TRIGGER_SID       (uint8)0xA7
/* Service Id of Pwm_DiagEnableAdTrigger */
#define PWM_ENABLE_AD_TRIGGER_SID        (uint8)0xA8

/***********************************************************************************************************************
**                                                  DET Error Codes                                                   **
***********************************************************************************************************************/

/* Pwm_Init API called with wrong parameter */
#define PWM_E_INIT_FAILED                (uint8)0x10
/* When PWM APIs are invoked before PWM Module Initialization */
#define PWM_E_UNINIT                     (uint8)0x11
/* When PWM APIs are invoked with invalid channel identifier */
#define PWM_E_PARAM_CHANNEL              (uint8)0x12
/* Invoking the PWM APIs on PWM channel configured as Fixed period */
#define PWM_E_PERIOD_UNCHANGEABLE        (uint8)0x13
/* Pwm_Init API called when PWM module is already initialized */
#define PWM_E_ALREADY_INITIALIZED        (uint8)0x14
/* Pwm_GetVersionInfo API is called with a NULL parameter. */
#define PWM_E_PARAM_POINTER              (uint8)0x15
/* Pwm_SetPowerState is called while the PWM module is still in use */
#define PWM_E_NOT_DISENGAGED             (uint8)0x16
/* Requested power state is not supported by the PWM module */
#define PWM_E_POWER_STATE_NOT_SUPPORTED  (uint8)0x17
/* Requested power state is not reachable from the current one */
#define PWM_E_TRANSITION_NOT_POSSIBLE    (uint8)0x18
/* Pwm_SetPowerState has been called without having called the API Pwm_PreparePowerState before */
#define PWM_E_PERIPHERAL_NOT_PREPARED    (uint8)0x19
/* Invoking Pwm_DisableNotification API for the configured channel whose notification is already disabled */
#define PWM_E_ALREADY_DISABLED           (uint8)0xF1
/* Invoking Pwm_EnableNotification API for the configured channel whose notification is already enabled */
#define PWM_E_ALREADY_ENABLED            (uint8)0xF2
/* When valid Database is not available */
#define PWM_E_INVALID_DATABASE           (uint8)0xEF
/* When PWM APIs Pwm_SetDutyCycle and Pwm_SetPeriodAndDuty are invoked with invalid parameter values */
#define PWM_E_PARAM_VALUE                (uint8)0xF3
/* When Notification is not configured for channel invoked by Pwm_DisableNotification and Pwm_EnableNotification APIs */
#define PWM_E_NOTIFY_NOTCONFIG           (uint8)0xF4
/* Pwm_SynchronousStart API called when PWM Synchronous mode is already started */
#define PWM_E_ALREADY_STARTED            (uint8)0xF6
/* DET code to report invalid core mapping service */
#define PWM_E_INVALID_CORE               (uint8)0xF7
/* DET code to report service is being requested by other cores */
#define PWM_E_REQUEST_FALSE              (uint8)0xF8

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/
#define PWM_START_SEC_PUBLIC_CODE_LOCAL
#include "Pwm_MemMap.h"

extern FUNC(void, PWM_PUBLIC_CODE) Pwm_Init(P2CONST(Pwm_ConfigType, PWM_VAR_NO_INIT, PWM_APPL_CONST) ConfigPtr);

#if (PWM_DE_INIT_API == STD_ON)
extern FUNC(void, PWM_PUBLIC_CODE) Pwm_DeInit(void);
#endif

#if (PWM_SYNC_START_SUPPORT == STD_ON)
extern FUNC(void, PWM_PUBLIC_CODE) Pwm_SynchronousInit(void);
extern FUNC(void, PWM_PUBLIC_CODE) Pwm_SynchronousStart(void);
extern FUNC(void, PWM_PUBLIC_CODE) Pwm_SynchronousStop(void);
#endif

#define PWM_STOP_SEC_PUBLIC_CODE_LOCAL
#include "Pwm_MemMap.h"


#define PWM_START_SEC_PUBLIC_CODE_GLOBAL
#include "Pwm_MemMap.h"

#if (PWM_SET_DUTY_CYCLE_API == STD_ON)
extern FUNC(void, PWM_PUBLIC_CODE) Pwm_SetDutyCycle(Pwm_ChannelType ChannelNumber, uint16 DutyCycle);
#endif

#if (PWM_SET_PERIOD_AND_DUTY_API == STD_ON)
extern FUNC(void, PWM_PUBLIC_CODE)
  Pwm_SetPeriodAndDuty(Pwm_ChannelType ChannelNumber, Pwm_PeriodType Period, uint16 DutyCycle);
#endif

#if (PWM_SET_OUTPUT_TO_IDLE_API == STD_ON)
extern FUNC(void, PWM_PUBLIC_CODE) Pwm_SetOutputToIdle(Pwm_ChannelType ChannelNumber);
#endif

#if (PWM_GET_OUTPUT_STATE_API == STD_ON)
extern FUNC(Pwm_OutputStateType, PWM_PUBLIC_CODE) Pwm_GetOutputState(Pwm_ChannelType ChannelNumber);
#endif

#if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
extern FUNC(void, PWM_PUBLIC_CODE)
  Pwm_EnableNotification(Pwm_ChannelType ChannelNumber, Pwm_EdgeNotificationType Notification);
extern FUNC(void, PWM_PUBLIC_CODE) Pwm_DisableNotification(Pwm_ChannelType ChannelNumber);
#endif

#if (PWM_SELECT_CHANNEL_CLK_API == STD_ON)
extern FUNC(void, PWM_PUBLIC_CODE)
  Pwm_SelectChannelClk(Pwm_ChannelType ChannelNumber, Pwm_ClockSourceType ClockSource);
#endif

#if (PWM_SET_CHANNEL_OUTPUT_API == STD_ON)
extern FUNC(void, PWM_PUBLIC_CODE) Pwm_SetChannelOutput(Pwm_ChannelType ChannelNumber, Pwm_OutputStateType State);
#endif

#if (PWM_VERSION_INFO_API == STD_ON)
extern FUNC(void, PWM_PUBLIC_CODE)
  Pwm_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, PWM_APPL_DATA) versioninfo);                                 /* PRQA S 3432 # JV-01 */
#endif

#if (PWM_SET_TRIGGER_DELAY_API == STD_ON)
extern FUNC(void, PWM_PUBLIC_CODE) Pwm_SetTriggerDelay(Pwm_ChannelType LddChannelNumber, uint16 LusTriggerDelay);
#endif

#if (PWM_READ_CONV_RESLUT_API == STD_ON)
extern FUNC(uint32, PWM_PUBLIC_CODE) Pwm_DiagReadAdConvResult(Pwm_ChannelType LddChannelNumber);
#endif

#if (PWM_ENABLE_DISABLE_AD_TRG_API == STD_ON)
extern FUNC(void, PWM_PUBLIC_CODE) Pwm_DiagDisableAdTrigger(Pwm_ChannelType LddChannelNumber);
extern FUNC(void, PWM_PUBLIC_CODE) Pwm_DiagEnableAdTrigger(Pwm_ChannelType LddChannelNumber);
#endif

#define PWM_STOP_SEC_PUBLIC_CODE_GLOBAL
#include "Pwm_MemMap.h"


#define PWM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Pwm_MemMap.h"

extern CONST(Pwm_ConfigType, PWM_CONST) Pwm_GaaConfiguration[];                                                         /* PRQA S 3684 # JV-01 */

#define PWM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Pwm_MemMap.h"

#endif /* PWM_H */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
