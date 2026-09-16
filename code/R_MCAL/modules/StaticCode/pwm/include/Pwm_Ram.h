/*====================================================================================================================*/
/* Project      = RH850/X2x AR4 MCAL Development                                                                      */
/* Module       = Pwm_Ram.h                                                                                           */
/*                                                                                                                    */
/*====================================================================================================================*/
/*                                                       COPYRIGHT                                                    */
/*====================================================================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Global RAM variable definitions for PWM Driver are declared.                                                       */
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
 * 2.3.2: 29/04/2025 : Update SW-VERSION for U2Ax Ver22.00.04 Beta Release                                            **
 * 2.3.1: 31/03/2025 : Update SW-VERSION for U2BxE Ver22.00.02 Beta Release                                           **
 * 2.3.0: 28/02/2025 : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release                        **
 * 2.2.0: 31/12/2024 : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release                                  **
 * 2.1.2: 31/10/2024 : As part of GTM support, following changes are made                                             **
 *                     1. Add the includes for GTM unit and fix typo mistake                                          **
 * 2.1.1: 30/08/2024 : Update SW-VERSION for Ver22.01.01 U2Bx Beta Release                                            **
 *                     As part of ARDAACL-40198 support, following changes are made ARDAACL-40198                     **
 *                     1. Add Global variable Pwm_GucKernelCoreId for supporting multi core multi postbuid variant    **
 * 2.0.1: 14/10/2023 : Change PWM_START/STOP_SEC_CONFIG_DATA_UNSPECIFIED to                                           **
 *                     PWM_START/STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED                                           **
 * 2.0.0: 28/08/2023 : Remove condition PWM_DEV_ERROR_DETECT == STD_ON for Pwm_GblDriverStatus                        **
 *        05/07/2023 : Update from "Pwm_Mapping.h to "Pwm_MemMap.h". Remove #ifdef PWM_INSTANCE_INDEX                 **
 *                     Update START/STOP_SEC_VAR_INIT_UNSPECIFIED to START/STOP_SEC_VAR_INIT_PTR for Pwm_GaaHwFunc    **
 *                     Remove message 0841                                                                            **
 * 1.4.1: 21/11/2021 : Change PWM_TIMER_IP_ATU to PWM_ATU_UNIT_USED to support U2Bx                                   **
 * 1.3.2: 23/08/2021 : Added PWM-Diag HW module.                                                                      **
 *        04/08/2021 : Device specific implementation move to device specific file.                                   **
 *                     Format source code unified within module.                                                      **
 * 1.3.1: 02/07/2021 : Add QAC message 9.5.0                                                                          **
 *                     Format source code to 120 characters                                                           **
 *                     Improve Violation tag (remove START/END)                                                       **
 *        15/05/2021 : Fixed Coding Rule and tailor space                                                             **
 *        11/05/2021 : Moved Pwm_GaaHwFunc to                                                                         **
 *                     section PWM_START_SEC_VAR_INIT_UNSPECIFIED                                                     **
 * 1.2.0: 28/07/2020 : Release                                                                                        **
 * 1.1.0: 19/06/2020 : Release                                                                                        **
 * 1.0.2: 20/05/2020 : Moved "Pwm_GpATUUnitConfig" from "PWM_CLOCK_SETTING" to                                        **
 *                     "PWM_TIMER_IP_ATU"                                                                             **
 * 1.0.1: 18/05/2020 : Added size for Pwm_GaaHWIP_Used[PWM_TOTAL_HW_IP_CONFIG]                                        **
 *                     and Pwm_GaaHwFunc[PWM_TOTAL_HWFUNC]                                                            **
 * 1.0.0: 24/03/2020 : Initial Version.                                                                               **
 *                                                                                                                    */
/**********************************************************************************************************************/

#ifndef PWM_RAM_H
#define PWM_RAM_H

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for macro definitions and structure declarations */
#include "Pwm_PBTypes.h"
/* Included for Header file inclusion */
#if (PWM_TAUD_UNIT_USED == STD_ON)
#include "Pwm_TAUD_LLDriver.h"
#include "Pwm_TAUD_PBTypes.h"
#include "Pwm_TAUD_Ram.h"
#endif
#if (PWM_TAUJ_UNIT_USED == STD_ON)
#include "Pwm_TAUJ_LLDriver.h"
#include "Pwm_TAUJ_PBTypes.h"
#include "Pwm_TAUJ_Ram.h"
#endif
#if (PWM_ATU_UNIT_USED == STD_ON)
#include "Pwm_ATU_LLDriver.h"
#include "Pwm_ATU_PBTypes.h"
#include "Pwm_ATU_Ram.h"
#endif

#if (PWM_GTM_UNIT_USED == STD_ON)
#include "Pwm_GTM_LLDriver.h"
#include "Pwm_GTM_PBTypes.h"
#include "Pwm_GTM_Ram.h"
#endif

#if (PWM_TIMER_IP_TAUDJ == STD_ON)
#include "Pwm_TAU_PBTypes.h"
#endif

#if(PWM_DIAG_UNIT_USED == STD_ON)
#include "Pwm_DIAG_Ram.h"
#endif
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define PWM_RAM_AR_RELEASE_MAJOR_VERSION    PWM_AR_RELEASE_MAJOR_VERSION
#define PWM_RAM_AR_RELEASE_MINOR_VERSION    PWM_AR_RELEASE_MINOR_VERSION
#define PWM_RAM_AR_RELEASE_REVISION_VERSION PWM_AR_RELEASE_REVISION_VERSION
/* Software module version information */
#define PWM_RAM_SW_MAJOR_VERSION            PWM_SW_MAJOR_VERSION
#define PWM_RAM_SW_MINOR_VERSION            PWM_SW_MINOR_VERSION

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:3684)    : Array declared with unknown size.                                                            */
/* Rule                : MISRA C:2012 Rule-8.11, CERTCCM ARR02                                                        */
/* JV-01 Justification : Arrays used are verified in the file which are only declarations and size is configuration   */
/*                       dependent.                                                                                   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Global Variables                                                  **
***********************************************************************************************************************/

#define PWM_START_SEC_VAR_INIT_PTR
#include "Pwm_MemMap.h"
/* Function pointer variable for all timer IP configuration */
extern P2CONST(Pwm_HwFuncTableType, PWM_VAR_INIT, PWM_CONFIG_DATA) Pwm_GaaHwFunc[PWM_TOTAL_HWFUNC];

#define PWM_STOP_SEC_VAR_INIT_PTR
#include "Pwm_MemMap.h"


#define PWM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Pwm_MemMap.h"

#if ((PWM_TAUD_UNIT_USED == STD_ON) || (PWM_TAUJ_UNIT_USED == STD_ON))
/* Structure for TAU channel configuration */
extern CONST(Pwm_TAUChannelConfigType, PWM_CONFIG_DATA) Pwm_GaaTAUChannelConfig[];                                      /* PRQA S 3684 # JV-01 */
#endif

#define PWM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Pwm_MemMap.h"


#define PWM_START_SEC_VAR_NO_INIT_PTR
#include "Pwm_MemMap.h"

/* Global pointer variable for channel configuration */
extern P2CONST(Pwm_ChannelConfigType, PWM_VAR_NO_INIT, PWM_CONFIG_DATA) volatile Pwm_GpChannelConfig;

#define PWM_STOP_SEC_VAR_NO_INIT_PTR
#include "Pwm_MemMap.h"


#define PWM_START_SEC_VAR_NO_INIT_8
#include "Pwm_MemMap.h"

#if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
/* Array for Notification status of timers configured */
extern volatile VAR(uint8, PWM_VAR_NO_INIT) Pwm_GaaNotifStatus[PWM_TOTAL_CHANNELS_CONFIG];
#endif

#if ((PWM_TAUD_UNIT_USED == STD_ON) || (PWM_TAUJ_UNIT_USED == STD_ON) )
#if (PWM_SET_CHANNEL_OUTPUT_API == STD_ON)
/* Global array to store Idle state status of configured channels */
extern volatile VAR(uint8, PWM_VAR_NO_INIT) Pwm_GaaChannelConstantStatus[PWM_TOTAL_CHANNELS_CONFIG];
#endif
/* Array for Idle state status for all configured channels */
extern volatile VAR(uint8, PWM_VAR_NO_INIT) Pwm_GaaChannelIdleStatus[PWM_TOTAL_CHANNELS_CONFIG];
#endif

#define PWM_STOP_SEC_VAR_NO_INIT_8
#include "Pwm_MemMap.h"


#define PWM_START_SEC_VAR_INIT_BOOLEAN
#include "Pwm_MemMap.h"

/* Status of PWM Driver initialization */
extern volatile VAR(boolean, PWM_VAR_INIT) Pwm_GblDriverStatus;

#if ((PWM_SYNC_START_SUPPORT == STD_ON) && (PWM_DEV_ERROR_DETECT == STD_ON))
/* Status of PWM synchronous initialization */
extern volatile VAR(boolean, PWM_VAR_INIT) Pwm_GblSyncInitStatus;
/* Status of PWM synchronous operation */
extern volatile VAR(boolean, PWM_VAR_INIT) Pwm_GblSyncOperationStatus;
#endif
#if (PWM_GET_OUTPUT_STATE_API == STD_ON)
/*Output state*/
extern volatile Pwm_OutputStateType Pwm_GblOutputState;
#endif

#define PWM_STOP_SEC_VAR_INIT_BOOLEAN
#include "Pwm_MemMap.h"


#define PWM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Pwm_MemMap.h"

extern CONST(Pwm_HWIP_ConfigType, PWM_CONFIG_DATA) Pwm_GaaHWIP_Used[PWM_TOTAL_HW_IP_CONFIG];

#define PWM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Pwm_MemMap.h"

#define PWM_START_SEC_VAR_INIT_8
#include "Pwm_MemMap.h"

#if (PWM_MULTI_CORE_SUPPORT == STD_ON)
/* Holds the kernel core ID in multicore */
extern uint8 Pwm_GucKernelCoreId;
#endif

#define PWM_STOP_SEC_VAR_INIT_8
#include "Pwm_MemMap.h"

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/

#endif /* PWM_RAM_H */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
