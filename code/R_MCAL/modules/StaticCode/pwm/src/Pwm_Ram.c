/*====================================================================================================================*/
/* Project      = RH850/X2x AR4 MCAL Development                                                                      */
/* Module       = Pwm_Ram.c                                                                                           */
/*                                                                                                                    */
/*====================================================================================================================*/
/*                                                       COPYRIGHT                                                    */
/*====================================================================================================================*/
/* (c) 2020,2021,2023-2025 Renesas Electronics Corporation. All rights reserved.                                      */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Global variable declarations                                                                                       */
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
 ** 2.3.2: 29/04/2025 : Update SW-VERSION for U2Ax Ver22.00.04 Beta Release                                           **
 ** 2.3.1: 31/03/2025 : Update SW-VERSION for U2BxE Ver22.00.02 Beta Release                                          **
 ** 2.3.0: 28/02/2025 : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release                       **
 ** 2.2.0: 31/12/2024 : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release                                 **
 ** 2.1.2: 31/10/2024 : Update SW-VERSION for Ver22.01.02 U2Bx, Ver22.00.05 U2Cx Beta2 Release                        **
 ** 2.1.1: 30/08/2024 : As part of ARDAACL-40198 support, following changes are made                                  **
 **                     1. Add QAC message 1533 for line 161                                                          **
 **                     2. Add Global variable Pwm_GucKernelCoreId for supporting multi core multi postbuid variant   **
 **                     3. Remove redundant QAC message                                                               **
 **                     4. Update version in header comment                                                           **
 ** 2.0.1: 21/10/2023 : Follow rule QAC 10.3.0, remove QAC message 1531                                               **
 ** 2.0.0: 28/08/2023 : Remove condition PWM_DEV_ERROR_DETECT == STD_ON for Pwm_GblDriverStatus                       **
 **        05/07/2023 : Update from "Pwm_Mapping.h to "Pwm_MemMap.h. Update QAC message                               **
 **                     Remove Pwm_GblOutputState                                                                     **
 ** 1.3.2: 04/08/2021 : Device specific implementation move to device specific file.                                  **
 **                     Format source code unified within module.                                                     **
 ** 1.3.1: 02/07/2021 : Format source code to 120 characters                                                          **
 **        15/05/2021 : Fixed Coding Rule and tailor space                                                            **
 ** 1.2.0: 28/07/2020 : Release                                                                                       **
 ** 1.1.0: 19/06/2020 : Release                                                                                       **
 ** 1.0.1: 20/05/2020 : Moved Pwm_GpATUUnitConfig                                                                     **
 **                               to "(PWM_TIMER_IP_ATU == STD_ON)                                                    **
 ** 1.0.0: 24/03/2020 : Initial Version.                                                                              **
 **                                                                                                                   */
/**********************************************************************************************************************/
/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for module version information and other types declarations */
#include "Pwm.h"
/* Included for RAM variable declarations */
#include "Pwm_Ram.h"

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define PWM_RAM_C_AR_RELEASE_MAJOR_VERSION    PWM_AR_RELEASE_MAJOR_VERSION_VALUE
#define PWM_RAM_C_AR_RELEASE_MINOR_VERSION    PWM_AR_RELEASE_MINOR_VERSION_VALUE
#define PWM_RAM_C_AR_RELEASE_REVISION_VERSION PWM_AR_RELEASE_REVISION_VERSION_VALUE
/* Module software version information */
#define PWM_RAM_C_SW_MAJOR_VERSION            PWM_SW_MAJOR_VERSION_VALUE
#define PWM_RAM_C_SW_MINOR_VERSION            PWM_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (PWM_RAM_AR_RELEASE_MAJOR_VERSION != PWM_RAM_C_AR_RELEASE_MAJOR_VERSION)
  #error "Pwm_Ram.c : Mismatch in Release Major Version"
#endif
#if (PWM_RAM_AR_RELEASE_MINOR_VERSION != PWM_RAM_C_AR_RELEASE_MINOR_VERSION)
  #error "Pwm_Ram.c : Mismatch in Release Minor Version"
#endif
#if (PWM_RAM_AR_RELEASE_REVISION_VERSION != PWM_RAM_C_AR_RELEASE_REVISION_VERSION)
  #error "Pwm_Ram.c : Mismatch in Release Revision Version"
#endif
#if (PWM_RAM_SW_MAJOR_VERSION != PWM_RAM_C_SW_MAJOR_VERSION)
  #error "Pwm_Ram.c : Mismatch in Software Major Version"
#endif
#if (PWM_RAM_SW_MINOR_VERSION != PWM_RAM_C_SW_MINOR_VERSION)
  #error "Pwm_Ram.c : Mismatch in Software Minor Version"
#endif

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (1:1533)    : The object '%1s' is only referenced by function '%2s'.                                       */
/* Rule                : MISRA C:2012 Rule-8.9, CWE Rule CWE-398, CWE-569                                             */
/* JV-01 Justification : This is accepted, due to the object is defined in separated source C file to followed        */
/*                       coding rule                                                                                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
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

/* Global pointer variable for channel configuration */
P2CONST(Pwm_ChannelConfigType, PWM_VAR_NO_INIT, PWM_CONFIG_DATA) volatile Pwm_GpChannelConfig;

#define PWM_STOP_SEC_VAR_NO_INIT_PTR
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


#define PWM_START_SEC_VAR_NO_INIT_8
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
/* Array for Notification status of timers configured */
volatile VAR(uint8, PWM_VAR_NO_INIT) Pwm_GaaNotifStatus[PWM_TOTAL_CHANNELS_CONFIG];
#endif

#if ((PWM_TAUD_UNIT_USED == STD_ON) || (PWM_TAUJ_UNIT_USED == STD_ON))
#if (PWM_SET_CHANNEL_OUTPUT_API == STD_ON)
/* Global array to store Idle state status of configured channels */
volatile VAR(uint8, PWM_VAR_NO_INIT) Pwm_GaaChannelConstantStatus[PWM_TOTAL_CHANNELS_CONFIG];
#endif
/* Array for Idle state status for all configured channels */
volatile VAR(uint8, PWM_VAR_NO_INIT) Pwm_GaaChannelIdleStatus[PWM_TOTAL_CHANNELS_CONFIG];
#endif

#define PWM_STOP_SEC_VAR_NO_INIT_8
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


#define PWM_START_SEC_VAR_INIT_BOOLEAN
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Status of PWM Driver initialization */
volatile VAR(boolean, PWM_VAR_INIT) Pwm_GblDriverStatus = PWM_UNINITIALIZED;                                            /* PRQA S 1533 # JV-01 */

#if ((PWM_SYNC_START_SUPPORT == STD_ON) && (PWM_DEV_ERROR_DETECT == STD_ON))
/* Status of PWM synchronous initialization */
volatile VAR(boolean, PWM_VAR_INIT) Pwm_GblSyncInitStatus = PWM_UNINITIALIZED;
/* Status of PWM synchronous operation */
volatile VAR(boolean, PWM_VAR_INIT) Pwm_GblSyncOperationStatus = PWM_SYNC_STOPPED;
#endif

#define PWM_STOP_SEC_VAR_INIT_BOOLEAN
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#if (PWM_MULTI_CORE_SUPPORT == STD_ON)
#define PWM_START_SEC_VAR_INIT_8
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/* Holds the kernal core ID in multicore */
uint8 Pwm_GucKernelCoreId = PWM_ZERO;
#define PWM_STOP_SEC_VAR_INIT_8
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif
/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
