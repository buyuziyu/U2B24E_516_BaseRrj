/*====================================================================================================================*/
/* Project      = RH850/X2x AR4 MCAL Development                                                                      */
/* Module       = Pwm_Kernel.h                                                                                        */
/*                                                                                                                    */
/*====================================================================================================================*/
/*                                                       COPYRIGHT                                                    */
/*====================================================================================================================*/
/* (c) 2023-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Provision of Kernel-API information for Multicore                                                                  */
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
 * 2.1.2: 31/10/2024 : Update SW-VERSION for Ver22.01.02 U2Bx, Ver22.00.05 U2Cx Beta2 Release                         **
 * 2.1.1: 30/08/2024 : Update SW-VERSION for Ver22.01.01 U2Bx Beta Release                                            **
 *                     As part of U2C support, following changes are made                                             **
 *                     1. Remove QAC message 1534, 1536                                                               **
 * 2.0.1: 21/10/2023 : Add QAC message 1534, 1536                                                                     **
 * 2.0.0: 26/06/2023 : Initial Version.                                                                               **
 *                                                                                                                    */
/**********************************************************************************************************************/

#ifndef PWM_KERNEL_H
#define PWM_KERNEL_H
/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for using Std Type(e.g. STD_ON), Compiler Macros(e.g. P2FUNC), Platform Types(e.g. uint8) */
#include "Std_Types.h"
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define PWM_KERNEL_AR_RELEASE_MAJOR_VERSION    PWM_AR_RELEASE_MAJOR_VERSION
#define PWM_KERNEL_AR_RELEASE_MINOR_VERSION    PWM_AR_RELEASE_MINOR_VERSION
#define PWM_KERNEL_AR_RELEASE_REVISION_VERSION PWM_AR_RELEASE_REVISION_VERSION
/* Software module version information */
#define PWM_KERNEL_SW_MAJOR_VERSION            PWM_SW_MAJOR_VERSION
#define PWM_KERNEL_SW_MINOR_VERSION            PWM_SW_MINOR_VERSION
/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/
#if (PWM_MULTI_CORE_SUPPORT == STD_ON)
/* Satellite service */
#define Pwm_LockedStatus(x)                    (x == PWM_TRUE)
#define Pwm_UnLockedStatus(x)                  (x == PWM_FALSE)

/* Master serivce */
#define Pwm_CheckingRequest(x)                 (x == PWM_TRUE)
#define Pwm_LockProcess(x)                     (x = PWM_TRUE)
#define Pwm_UnLockProcess(x)                   (x = PWM_FALSE)

#if (PWM_SET_DUTY_CYCLE_API == STD_ON)
/* Type definition for Request from Pwm_SetDutyCycle */
typedef struct Stag_Pwm_SetDutyCycle_RequestType
{
    /* storing value of request from Pwm_SetDutyCycle (DutyCycle) */
    uint16 lusDutyCycle;
    /* Satellite request */
    boolean blSetReq;
    /* Status of locking the buffer */
    boolean blBufferLock;
} Pwm_SetDutyCycle_RequestType;
#endif

#if (PWM_SET_PERIOD_AND_DUTY_API == STD_ON)
/* Type definition for Request from Pwm_SetPeriodAndDuty */
typedef struct Stag_Pwm_SetPeriodAndDuty_RequestType
{
    /* storing value of request from Pwm_SetPeriodAndDuty (DutyCycle) */
    uint16 lusDutyCycle;
    /* storing value of request from Pwm_SetPeriodAndDuty (Period) */
    Pwm_PeriodType lddPeriod;
    /* Satellite request */
    boolean blSetReq;
    /* Status of locking the buffer */
    boolean blBufferLock;
} Pwm_SetPeriodAndDuty_RequestType;
#endif

#if (PWM_SET_OUTPUT_TO_IDLE_API == STD_ON)
/* Type definition for Request from API only have input is ChannelNumber */
typedef struct Stag_Pwm_Channel_RequestType
{
    /* Satellite request */
    boolean blSetReq;
    /* Status of locking the buffer */
    boolean blBufferLock;
} Pwm_Channel_RequestType;
#endif

#if (PWM_SELECT_CHANNEL_CLK_API == STD_ON)
/* Type definition for Request from Pwm_SelectChannelClk */
typedef struct Stag_Pwm_SelectChannelClk_RequestType
{
    /* storing value of request from Pwm_SelectChannelClk (ClockSource) */
    Pwm_ClockSourceType lddClockSource;
    /* Satellite request */
    boolean blSetReq;
    /* Status of locking the buffer */
    boolean blBufferLock;
} Pwm_SelectChannelClk_RequestType;
#endif

#if (PWM_SET_CHANNEL_OUTPUT_API == STD_ON)
/* Type definition for Request from Pwm_SetChannelOutput */
typedef struct Stag_Pwm_SetChannelOutput_RequestType
{
    /* storing value of request from Pwm_SetChannelOutput (State) */
    Pwm_OutputStateType lddState;
    /* Satellite request */
    boolean blSetReq;
    /* Status of locking the buffer */
    boolean blBufferLock;
} Pwm_SetChannelOutput_RequestType;
#endif

#if (PWM_SET_TRIGGER_DELAY_API == STD_ON)
/* Type definition for Request from Pwm_SetTriggerDelay */
typedef struct Stag_Pwm_SetTriggerDelay_RequestType
{
    /* storing value of request from Pwm_SetTriggerDelay (LusTriggerDelay) */
    uint16 lusTriggerDelay;
    /* Satellite request */
    boolean blSetReq;
    /* Status of locking the buffer */
    boolean blBufferLock;
} Pwm_SetTriggerDelay_RequestType;
#endif

/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/
/* Globale scope - share among cores */
#define PWM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Pwm_MemMap.h"

#if (PWM_SET_DUTY_CYCLE_API == STD_ON)
/* Pwm_SetDutyCycle request */
extern volatile VAR(Pwm_SetDutyCycle_RequestType, PWM_VAR_NO_INIT) Pwm_GaaSetDutyCycleBuffer[PWM_TOTAL_CHANNELS_CONFIG];
#endif

#if (PWM_SET_PERIOD_AND_DUTY_API == STD_ON)
/* Pwm_SetPeriodAndDuty request */
extern volatile VAR(Pwm_SetPeriodAndDuty_RequestType, PWM_VAR_NO_INIT) 
                                                            Pwm_GaaSetPeriodAndDutyBuffer[PWM_TOTAL_CHANNELS_CONFIG];
#endif

#if (PWM_SET_OUTPUT_TO_IDLE_API == STD_ON)
/* Pwm_SetOutputToIdle request*/
extern volatile VAR(Pwm_Channel_RequestType, PWM_VAR_NO_INIT) Pwm_GaaSetOutputToIdleBuffer[PWM_TOTAL_CHANNELS_CONFIG];
#endif

#if (PWM_SELECT_CHANNEL_CLK_API == STD_ON)
/* Pwm_SelectChannelClk request*/
extern volatile VAR(Pwm_SelectChannelClk_RequestType, PWM_VAR_NO_INIT) 
                                                            Pwm_GaaSelectChannelClkBuffer[PWM_TOTAL_CHANNELS_CONFIG];
#endif

#if (PWM_SET_CHANNEL_OUTPUT_API == STD_ON)
/* Pwm_SetChannelOutput request*/
extern volatile VAR(Pwm_SetChannelOutput_RequestType, PWM_VAR_NO_INIT) 
                                                            Pwm_GaaSetChannelOutputBuffer[PWM_TOTAL_CHANNELS_CONFIG];
#endif

#if (PWM_SET_TRIGGER_DELAY_API == STD_ON)
/* Pwm_SetTriggerDelay request*/
extern volatile VAR(Pwm_SetTriggerDelay_RequestType, PWM_VAR_NO_INIT) 
                                                            Pwm_GaaSetTriggerDelayBuffer[PWM_TOTAL_CHANNELS_CONFIG];
#endif

#define PWM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Pwm_MemMap.h"

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/
#define PWM_START_SEC_PUBLIC_CODE_LOCAL
#include "Pwm_MemMap.h"

#if (PWM_SET_DUTY_CYCLE_API == STD_ON)
/* Kernel API handle request by Pwm_SetDutyCycle */
extern FUNC(void, PWM_PUBLIC_CODE) Pwm_Kernel_SetDutyCycle(void);
#endif

#if (PWM_SET_PERIOD_AND_DUTY_API == STD_ON)
/* Kernel API handle request by Pwm_SetPeriodAndDuty */
extern FUNC(void, PWM_PUBLIC_CODE) Pwm_Kernel_SetPeriodAndDuty(void);
#endif

#if (PWM_SET_OUTPUT_TO_IDLE_API == STD_ON)
/* Kernel API handle request by Pwm_SetOutputToIdle */
extern FUNC(void, PWM_PUBLIC_CODE) Pwm_Kernel_SetOutputToIdle(void);
#endif

#if (PWM_SELECT_CHANNEL_CLK_API == STD_ON)
/* Kernel API handle request by Pwm_SelectChannelClk*/
extern FUNC(void, PWM_PUBLIC_CODE) Pwm_Kernel_SelectChannelClk(void);
#endif

#if (PWM_SET_CHANNEL_OUTPUT_API == STD_ON)
/* Kernel API handle request by Pwm_SetChannelOutput*/
extern FUNC(void, PWM_PUBLIC_CODE) Pwm_Kernel_SetChannelOutput(void);
#endif

#if (PWM_SET_TRIGGER_DELAY_API == STD_ON)
/* Kernel API handle request by Pwm_SetTriggerDelay*/
extern FUNC(void, PWM_PUBLIC_CODE) Pwm_Kernel_SetTriggerDelay(void);
#endif

#define PWM_STOP_SEC_PUBLIC_CODE_LOCAL
#include "Pwm_MemMap.h"

#endif /* PWM_MULTI_CORE_SUPPORT == STD_ON */

#endif /* #ifndef PWM_KERNEL_H */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
