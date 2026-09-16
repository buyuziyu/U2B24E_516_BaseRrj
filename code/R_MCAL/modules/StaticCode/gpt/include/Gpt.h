/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Gpt.h                                                                                               */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
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
/*              Devices:        X2x                                                                                   */
/*====================================================================================================================*/

/***********************************************************************************************************************
**                                              Revision Control History                                              **
***********************************************************************************************************************/
/*
 *  2.4.1  30/06/2025 : As part of RH850/U2Bx MCAL Ver22.02.00.001 release, following changes are made
 *                      1.Update GPT_SW_PATCH_VERSION to 0 (2.4.0 to 2.4.1)
 *  2.4.0  30/06/2025 : As part of RH850/U2Ax MCAL Ver22.01.00 (D) release, following changes are made
 *                      1.Update GPT_SW_MINOR_VERSION to 4 (2.3.2 to 2.4.0)
 *                      2.Update GPT_SW_PATCH_VERSION to 0 (2.3.2 to 2.4.0)
 *  2.3.2  25/04/2025 : Update GPT_SW_PATCH_VERSION from 1 to 2
 *  2.3.1  31/03/2025 : Update SW-VERSION for RH850/U2BxE MCAL Ver22.00.02/Ver22.00.02.D Release
 *                      Update GPT_SW_PATCH_VERSION from 0 to 1
 * 2.3.0  28/02/2025  : As part of RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release, following changes are made
 *                      1.Update GPT_SW_MINOR_VERSION to 2 (2.2.0 to 2.3.0)
 * 2.2.0  31/12/2024  : As part of Ver22.02.00/Ver22.02.00.D Final Release, following changes are made
 *                      1.Update GPT_SW_MINOR_VERSION to 2 (2.1.2 to 2.2.0)
 *                      2.Update GPT_SW_PATCH_VERSION to 0 (2.1.2 to 2.2.0)
 * 2.1.2  31/10/2024  : Update GPT_SW_PATCH_VERSION to 2 (2.1.1 to 2.1.2)
 * 2.1.1  30/08/2024  : As part of QAC 9.5.0 support, following changes are made
 *                      1.Remove QAC message 1534
 * 2.1.0  04/03/2024  : Update GPT_SW_PATCH_VERSION to 0, GPT_SW_MINOR_VERSION to 1 (2.0.2 to 2.1.0)
 * 2.0.1  17/10/2023  : Update preprocessor GPT_AR_R21_11_VERSION to GPT_AR_R22_11_VERSION
 *                      Update GPT_SW_PATCH_VERSION from 0 to 1
 *                      Update memory section from CONFIG_DATA to CONFIG_DATA_POSTBUILD
 *                      Add QAC message 1534
 * 2.0.0  26/07/2023  : Change Gpt_Mapping.h to Gpt_MemMap.h, remove qac message 0841, 0791, update qac message
 *                      3432 header, remove GPT_INSTANCE_INDEX, Gpt_MultiInstance.h; add GPT_E_INVALID_CORE;
 *                      Change GPT_START_SEC_DBTOC_DATA_UNSPECIFIED, GPT_STOP_SEC_DBTOC_DATA_UNSPECIFIED to
 *                      GPT_START_SEC_CONFIG_DATA_UNSPECIFIED, GPT_STOP_SEC_CONFIG_DATA_UNSPECIFIED
 *                      Add CWE QAC header
 *        12/06/2023  : Update macro GPT_AR_2111_VERSION to GPT_AR_R21_11_VERSION and
 *                    : pre-processor GPT_AR_VERSION == GPT_AR_R21_11_VERSION
 *        12/05/2023  : Update GPT_SW_MINOR_VERSION from 5 to 0, GPT_SW_MAJOR_VERSION from 1 to 2
 * 1.5.0  01/03/2023  : Update GPT_SW_MINOR_VERSION from 4 to 5, GPT_SW_PATCH_VERSION from 5 to 0
 * 1.4.5  02/12/2022  : Add GPT_AR_2111_VERSION macro and pre-processor GPT_AR_VERSION == GPT_AR_2111_VERSION
 *                      for support AR21-11; Update macro GPT_SW_PATCH_VERSION to 5
 *        08/06/2022  : Update macro GPT_SW_PATCH_VERSION to 4
 * 1.4.3  08/04/2022  : Update macro GPT_SW_PATCH_VERSION to 3
 * 1.4.2  24/02/2022  : Update macro GPT_SW_PATCH_VERSION to 2
 * 1.4.0  06/10/2021  : Following Changes were made:
 *                      1. Updated macro GPT_SW_MINOR_VERSION to 4 and GPT_SW_PATCH_VERSION to 0.
 * 1.3.2  22/08/2021  : Following Changes were made:
 *                      1. Updated macro GPT_SW_PATCH_VERSION to 2.
 *                      2. Updated header file macro to call file multiple times.
 *                      3. Using #include GPT_CFG_HEADER instead of
 *                         include each config file base on define GPT_INSTANCE_INDEX value.
 *                      4. Change from #include "Gpt_MemMap.h" to #include "Gpy_Mapping.h".
 *                      5. Added QAC message 9.5.0.
 * 1.3.1  02/07/2021  : Added QAC message 9.5.0.
 *                       Format source code to 120 characters.
 *                       Improve Violation tag (remove START/END).
 *        31/05/2021  : Updated GPT_SW_PATCH_VERSION to 1.
 * 1.3.0  21/01/2021  : Change argument name in Gpt_GetPredefTimerValue(): from TimerValuePtr to TimeValuePtr.
 *        20/01/2021  : Change Compiler abstraction symbols of argument in 2 APIs follow AUTOSAR requirement:
 *                       1. VersionInfoPtr in Gpt_GetVersionInfo(): from CONSTP2VAR to P2VAR.
 *                       2. ConfigPtr in Gpt_Init(): from CONSTP2CONST to P2CONST.
 * 1.2.0  17/07/2020  : Release.
 * 1.1.0  19/06/2020  : Release.
 * 1.0.0  01/01/2020  : Initial Version.
 */
/**********************************************************************************************************************/
/***********************************************************************************************************************
**                                             Margin for Control History                                             **
***********************************************************************************************************************/

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

#ifndef GPT_HEADER
#define GPT_HEADER

#define GPT_AR_422_VERSION 422
#define GPT_AR_431_VERSION 431
#define GPT_AR_R22_11_VERSION 480
/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Include difinition of multi instance */

/* Included for using Std Type(e.g. STD_ON), Compiler Macros(e.g. P2FUNC), Platform Types(e.g. uint8) */
#include "Std_Types.h"
/* Included for GPT module-specific definitions */
#include "Gpt_Cfg.h"
/* Included for Type definitions */
#include "Gpt_Types.h"
#if (GPT_REPORT_WAKEUP_SOURCE == STD_ON)
/* Included for the declaration of EcuM_SetWakeupEvent() */
#include "EcuM_Cbk.h"
#endif
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* Version identification */
#define GPT_VENDOR_ID   GPT_VENDOR_ID_VALUE
#define GPT_MODULE_ID   GPT_MODULE_ID_VALUE
#define GPT_INSTANCE_ID GPT_INSTANCE_ID_VALUE

#if (GPT_AR_VERSION == GPT_AR_422_VERSION)
/* AUTOSAR release version information */
#define GPT_AR_RELEASE_MAJOR_VERSION    4U
#define GPT_AR_RELEASE_MINOR_VERSION    2U
#define GPT_AR_RELEASE_REVISION_VERSION 2U
#elif (GPT_AR_VERSION == GPT_AR_431_VERSION)
#define GPT_AR_RELEASE_MAJOR_VERSION    4U
#define GPT_AR_RELEASE_MINOR_VERSION    3U
#define GPT_AR_RELEASE_REVISION_VERSION 1U
#elif (GPT_AR_VERSION == GPT_AR_R22_11_VERSION)
#define GPT_AR_RELEASE_MAJOR_VERSION    4U
#define GPT_AR_RELEASE_MINOR_VERSION    8U
#define GPT_AR_RELEASE_REVISION_VERSION 0U
#endif

/* File version information */
#define GPT_SW_MAJOR_VERSION        2U
#define GPT_SW_MINOR_VERSION        4U
#define GPT_SW_PATCH_VERSION        1U

/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                    Service IDs                                                     **
***********************************************************************************************************************/

/* Service Id of Gpt_GetVersionInfo */
#define GPT_GET_VERSION_INFO_SID    (uint8)0x00
/* Service Id of Gpt_Init */
#define GPT_INIT_SID                (uint8)0x01
/* Service Id of Gpt_DeInit */
#define GPT_DEINIT_SID              (uint8)0x02
/* Service Id of Gpt_GetTimeElapsed */
#define GPT_GET_TIME_ELAPSED_SID    (uint8)0x03
/* Service Id of Gpt_GetTimeRemaining */
#define GPT_GET_TIME_REMAINING_SID  (uint8)0x04
/* Service Id of Gpt_StartTimer */
#define GPT_START_TIMER_SID         (uint8)0x05
/* Service Id of Gpt_StopTimer */
#define GPT_STOP_TIMER_SID          (uint8)0x06
/* Service Id of Gpt_EnableNotification */
#define GPT_ENABLE_NOTIFY_SID       (uint8)0x07
/* Service Id of Gpt_DisableNotification */
#define GPT_DISABLE_NOTIFY_SID      (uint8)0x08
/* Service Id of Gpt_SetMode */
#define GPT_SET_MODE_SID            (uint8)0x09
/* Service Id of Gpt_DisableWakeup */
#define GPT_DISABLE_WAKEUP_SID      (uint8)0x0A
/* Service Id of Gpt_EnableWakeup */
#define GPT_ENABLE_WAKEUP_SID       (uint8)0x0B
/* Service Id of  Gpt_CheckWakeup */
#define GPT_CHECK_WAKEUP_SID        (uint8)0x0C
/* Service Id of  Gpt_GetPredefTimerValue */
#define GPT_GET_PREDEFTIMRVALUE_SID (uint8)0x0D
/***********************************************************************************************************************
**                                                  DET Error Codes                                                   **
***********************************************************************************************************************/

/* DET code to report uninitialized state */
#define GPT_E_UNINIT                (uint8)0x0A
/* DET code to report Timer is already running */
#define GPT_E_BUSY                  (uint8)0x0B
/* DET code to report that driver is in wrong mode  */
#define GPT_E_MODE                  (uint8)0x0C
/* DET code to report Timer already Initialized */
#define GPT_E_ALREADY_INITIALIZED   (uint8)0x0D
/* DET code to report invalid Channel Identifier */
#define GPT_E_PARAM_CHANNEL         (uint8)0x14
/* DET code to report invalid timer value */
#define GPT_E_PARAM_VALUE           (uint8)0x15
/* DET code to report Gpt_Init called with NULL as parameter */
#define GPT_E_PARAM_POINTER         (uint8)0x16
/* DET code to report the parameter PredefTimer is invalid */
#define GPT_E_PARAM_PREDEF_TIMER    (uint8)0x17
/* DET code to report invalid mode parameter */
#define GPT_E_PARAM_MODE            (uint8)0x1F
/* DET code to report invalid database */
#define GPT_E_INVALID_DATABASE      (uint8)0xEF
/* DET code to report that the notification is already disabled */
#define GPT_E_ALREADY_DISABLED      (uint8)0xF1
/* DET code to report that the notification is already enabled */
#define GPT_E_ALREADY_ENABLED       (uint8)0xF2
/* DET code to report that Gpt_Init function failed  */
#define GPT_E_INIT_FAILED           (uint8)0x0E
/* Invalid core */
#define GPT_E_INVALID_CORE          (uint8)0x0F
/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/
#define GPT_START_SEC_PUBLIC_CODE
#include "Gpt_MemMap.h"
#if (GPT_VERSION_INFO_API == STD_ON)
extern FUNC(void, GPT_PUBLIC_CODE)
                               Gpt_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, GPT_APPL_DATA) VersionInfoPtr); /* PRQA S 3432 # JV-01 */
#endif /*(GPT_VERSION_INFO_API == STD_ON)*/
extern FUNC(void, GPT_PUBLIC_CODE) Gpt_Init(P2CONST(Gpt_ConfigType, AUTOMATIC, GPT_APPL_CONST) ConfigPtr);
#if (GPT_DE_INIT_API == STD_ON)
extern FUNC(void, GPT_PUBLIC_CODE) Gpt_DeInit(void);
#endif
#if (GPT_TIME_ELAPSED_API == STD_ON)
extern FUNC(Gpt_ValueType, GPT_PUBLIC_CODE) Gpt_GetTimeElapsed(Gpt_ChannelType Channel);
#endif
#if (GPT_TIME_REMAINING_API == STD_ON)
extern FUNC(Gpt_ValueType, GPT_PUBLIC_CODE) Gpt_GetTimeRemaining(Gpt_ChannelType Channel);
#endif
extern FUNC(void, GPT_PUBLIC_CODE) Gpt_StartTimer(Gpt_ChannelType Channel, Gpt_ValueType Value);
extern FUNC(void, GPT_PUBLIC_CODE) Gpt_StopTimer(Gpt_ChannelType Channel);
#if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)
extern FUNC(void, GPT_PUBLIC_CODE) Gpt_EnableNotification(Gpt_ChannelType Channel);
extern FUNC(void, GPT_PUBLIC_CODE) Gpt_DisableNotification(Gpt_ChannelType Channel);
#endif
#if ((GPT_REPORT_WAKEUP_SOURCE == STD_ON) && (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON))
extern FUNC(void, GPT_PUBLIC_CODE) Gpt_SetMode(Gpt_ModeType Mode);
extern FUNC(void, GPT_PUBLIC_CODE) Gpt_DisableWakeup(Gpt_ChannelType Channel);
extern FUNC(void, GPT_PUBLIC_CODE) Gpt_EnableWakeup(Gpt_ChannelType Channel);
extern FUNC(void, GPT_PUBLIC_CODE) Gpt_CheckWakeup(EcuM_WakeupSourceType WakeupSource);
#endif
#if (GPT_GET_PREDEF_TIMER_VALUE_API == STD_ON)
extern FUNC(Std_ReturnType, GPT_PUBLIC_CODE)
                                         Gpt_GetPredefTimerValue(Gpt_PredefTimerType PredefTimer, uint32 *TimeValuePtr);
#endif
#define GPT_STOP_SEC_PUBLIC_CODE
#include "Gpt_MemMap.h"

#define GPT_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Gpt_MemMap.h"
extern CONST(Gpt_ConfigType, GPT_CONST) Gpt_GaaConfiguration[];                                                         /* PRQA S 3684 # JV-01 */
#define GPT_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Gpt_MemMap.h"

#endif /* GPT_HEADER */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
