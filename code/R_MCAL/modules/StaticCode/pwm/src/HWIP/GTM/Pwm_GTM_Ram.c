/*====================================================================================================================*/
/* Project      = RH850/X2x AR4 MCAL Development                                                                      */
/* Module       = Pwm_GTM_Ram.c                                                                                       */
/*                                                                                                                    */
/*====================================================================================================================*/
/*                                                       COPYRIGHT                                                    */
/*====================================================================================================================*/
/* (c) 2024,2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* API function implementations of PWM Driver                                                                         */
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
 ** 2.5.1: 30/06/2025 : Remove SW-VERSION in header comment                                                           **
 ** 2.5.0: 30/06/2025 : Update SW-VERSION for U2Ax Ver22.01.00(D) Final Release                                       **
 ** 2.4.0: 31/05/2025 : Update SW-VERSION for U2Cx Ver21.01.01 Final Release                                          **
 ** 2.3.2: 29/04/2025 : As part of GTM support, following changes are made                                            **
 **                     1. Update function Pwm_HW_GTM_SetChannelOutput to support GTM version 3.5                     **
 ** 2.3.1: 31/03/2025 : Update SW-VERSION for U2BxE Ver22.00.02 Beta Release                                          **
 ** 2.3.0: 28/02/2025 : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release                       **
 ** 2.2.0: 31/12/2024 : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release                                 **
 ** 2.1.2: 31/10/2024 : Initial Version.                                                                              **
 **                                                                                                                   */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for module version information and other types declarations */
#include "Pwm.h"
#include "Pwm_Ram.h"

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
#if (PWM_GTM_UNIT_USED == STD_ON)
/* AUTOSAR release version information */
#define PWM_GTM_RAM_C_AR_RELEASE_MAJOR_VERSION    PWM_AR_RELEASE_MAJOR_VERSION_VALUE
#define PWM_GTM_RAM_C_AR_RELEASE_MINOR_VERSION    PWM_AR_RELEASE_MINOR_VERSION_VALUE
#define PWM_GTM_RAM_C_AR_RELEASE_REVISION_VERSION PWM_AR_RELEASE_REVISION_VERSION_VALUE

/* Module software version information */
#define PWM_GTM_RAM_C_SW_MAJOR_VERSION            PWM_SW_MAJOR_VERSION_VALUE
#define PWM_GTM_RAM_C_SW_MINOR_VERSION            PWM_SW_MINOR_VERSION_VALUE
#define PWM_GTM_RAM_C_SW_PATCH_VERSION            PWM_SW_PATCH_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/

#if (PWM_GTM_RAM_AR_RELEASE_MAJOR_VERSION != PWM_GTM_RAM_C_AR_RELEASE_MAJOR_VERSION)
  #error "Pwm_GTM_Ram.c : Mismatch in Release Major Version"
#endif

#if (PWM_GTM_RAM_AR_RELEASE_MINOR_VERSION != PWM_GTM_RAM_C_AR_RELEASE_MINOR_VERSION)
  #error "Pwm_GTM_Ram.c : Mismatch in Release Minor Version"
#endif

#if (PWM_GTM_RAM_AR_RELEASE_REVISION_VERSION != PWM_GTM_RAM_C_AR_RELEASE_REVISION_VERSION)
  #error "Pwm_GTM_Ram.c : Mismatch in Release Revision Version"
#endif

#if (PWM_GTM_RAM_SW_MAJOR_VERSION != PWM_GTM_RAM_C_SW_MAJOR_VERSION)
  #error "Pwm_GTM_Ram.c : Mismatch in Software Major Version"
#endif

#if (PWM_GTM_RAM_SW_MINOR_VERSION != PWM_GTM_RAM_C_SW_MINOR_VERSION)
  #error "Pwm_GTM_Ram.c : Mismatch in Software Minor Version"
#endif

#if (PWM_GTM_RAM_SW_PATCH_VERSION != PWM_GTM_RAM_C_SW_PATCH_VERSION)
  #error "Pwm_GTM_Ram.c : Mismatch in Software Patch Version"
#endif
/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (4:5087)    : Use of #include directive after code fragment.                                               */
/* Rule                : MISRA C:2012 Rule-20.1                                                                       */
/* JV-01 Justification : This is done as per Memory Requirement, (MEMMAP003 - Specification of Memory Mapping).       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/
#define PWM_START_SEC_VAR_NO_INIT_PTR
#include "Pwm_MemMap.h"

P2CONST(Pwm_GTMUnitConfigType, PWM_VAR_NO_INIT, PWM_CONFIG_DATA) volatile Pwm_GpGTMUnitConfig;

#define PWM_STOP_SEC_VAR_NO_INIT_PTR
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


#define PWM_START_SEC_CONST_PTR
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/* The Function table for GTM */
CONST(Pwm_HwFuncTableType, PWM_CONST) Pwm_GtmFunc =
{
     &Pwm_HW_GTM_InitUnit,
     &Pwm_HW_GTM_InitChannel,
     #if (PWM_DE_INIT_API == STD_ON)
     &Pwm_HW_GTM_DeInitUnit,
     &Pwm_HW_GTM_DeInitChannel,
     #endif
     #if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
     &Pwm_HW_GTM_DisableNotification,
     &Pwm_HW_GTM_EnableNotification,
     #endif
     #if (PWM_GET_OUTPUT_STATE_API == STD_ON)
     &Pwm_HW_GTM_GetOutputState,
     #endif
     #if (PWM_SELECT_CHANNEL_CLK_API == STD_ON)
     &Pwm_HW_GTM_SelectChannelClk,
     #endif
     #if (PWM_SET_CHANNEL_OUTPUT_API == STD_ON)
     #if (PWM_GTM_VERSION == PWM_GTM_4_1_VERSION)
     &Pwm_HW_GTM_SetChannelOutput,
     #else
     NULL_PTR,
     #endif
     #endif
     #if (PWM_SET_DUTY_CYCLE_API == STD_ON)
     &Pwm_HW_GTM_SetDutyCycle,
     #endif
     #if (PWM_SET_PERIOD_AND_DUTY_API == STD_ON)
     &Pwm_HW_GTM_SetPeriodAndDuty,
     #endif
     #if (PWM_SET_OUTPUT_TO_IDLE_API == STD_ON)
     &Pwm_HW_GTM_SetOutputToIdle,
     #endif
     #if (PWM_SYNC_START_SUPPORT == STD_ON)
     &Pwm_HW_GTM_SynchronousInit,
     &Pwm_HW_GTM_SynchronousStart,
     &Pwm_HW_GTM_SynchronousStop,
     #endif
     &Pwm_HW_GTM_StartOutput
};
#define PWM_STOP_SEC_CONST_PTR
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /*#if (PWM_GTM_UNIT_USED == STD_ON)*/
/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
