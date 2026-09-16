/*============================================================================*/
/* Project      = RH850/X2x AR4 MCAL Development                              */
/* Module       = App_PWM_Common_Multicore_PostBuildVariant_Sample_0.c        */
/*                                                                            */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2024-2025 Renesas Electronics Corporation. All rights reserved.        */
/*============================================================================*/
/* Purpose:                                                                   */
/* This file contains sample application for PWM Driver Component             */
/*                                                                            */
/*============================================================================*/
/*                                                                            */
/* Unless otherwise agreed upon in writing between your company and           */
/* Renesas Electronics Corporation the following shall apply!                 */
/*                                                                            */
/* Warranty Disclaimer                                                        */
/*                                                                            */
/* There is no warranty of any kind whatsoever granted by Renesas. Any        */
/* warranty is expressly disclaimed and excluded by Renesas, either expressed */
/* or implied, including but not limited to those for non-infringement of     */
/* intellectual property, merchantability and/or fitness for the particular   */
/* purpose.                                                                   */
/*                                                                            */
/* Renesas shall not have any obligation to maintain, service or provide bug  */
/* fixes for the supplied Product(s) and/or the Application.                  */
/*                                                                            */
/* Each User is solely responsible for determining the appropriateness of     */
/* using the Product(s) and assumes all risks associated with its exercise    */
/* of rights under this Agreement, including, but not limited to the risks    */
/* and costs of program errors, compliance with applicable laws, damage to    */
/* or loss of data, programs or equipment, and unavailability or              */
/* interruption of operations.                                                */
/*                                                                            */
/* Limitation of Liability                                                    */
/*                                                                            */
/* In no event shall Renesas be liable to the User for any incidental,        */
/* consequential, indirect, or punitive damage (including but not limited     */
/* to lost profits) regardless of whether such liability is based on breach   */
/* of contract, tort, strict liability, breach of warranties, failure of      */
/* essential purpose or otherwise and even if advised of the possibility of   */
/* such damages. Renesas shall not be liable for any services or products     */
/* provided by third party vendors, developers or consultants identified or   */
/* referred to the User by Renesas in connection with the Product(s) and/or   */
/* the Application.                                                           */
/*                                                                            */
/*============================================================================*/
/* Environment:                                                               */
/*              Devices:        X2x                                           */
/*============================================================================*/
/*******************************************************************************
**                      Revision Control History                              **
*******************************************************************************/
/*                                                                            **
 * 2.5.1: 30/06/2025 : Remove SW-VERSION in header comment                    **
 * 2.5.0: 30/06/2025 : Update SW-VERSION for U2Ax Ver22.01.00(D) Final Release**
 * 2.4.0: 31/05/2025 : Update SW-VERSION for U2Cx Ver21.01.01 Final Release   **
 * 2.3.2: 29/04/2025 : As part of GTM support, following changes are made     **
 *                     1. Add condition "(DEVICE == U2Ax)" for U2Ax           **
 *                     As part of CCRH support                                **
 *                     1. Add pragma for Timer0_Interrupt                     **
 *                     2. Remove task1 to before main_sequence                **
 * 2.3.1: 31/03/2025 : Update SW-VERSION for U2BxE Ver22.00.02 Beta Release   **
 * 2.3.0: 28/02/2025 : As part of GTM support, following changes are made     **
 *                     1. Update sample app for GTM channel in U2Cx           **
 *                     2. Remove PWM_DEVICE_U2B12E_U2B6E macro for U2BxE      **
 * 2.2.0: 31/12/2024 : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final  **
 *                     Release                                                **
 *                     As part of U2BxE support, following changes are made:  **
 *                     1. Update Pwm_SelectChannelClk for device U2B12E, U2B6E**
 * 2.1.2: 31/10/2024 : As part of GTM support, following changes are made     **
 *                     1. Update function Pwm_SelectChannelClk for GTM        **
 *                     2. Add macro for DeInit                                **
 * 2.1.1: 18/06/2024 : As part of U2C support, following changes are made:    **
 *                     1. Update sample app for channel Diag                  **
 *        15/06/2024 : As part of U2BxE support, following changes are made:  **
 *                     1. Update sample app for device U2B12E, U2B6E          **
 * 1.0.0: 25/03/2024 : Initial Version.                                       **
 *                                                                            */
/******************************************************************************/
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "App_Pwm_Common_Sample_0.h"
#include "App_Pwm_Multi_Sample.h"

/*******************************************************************************
**                            Macros                                          **
*******************************************************************************/

/*******************************************************************************
**                        Global variables                                    **
*******************************************************************************/

/* Variable used to store the version information */
Std_VersionInfoType versionInfo_PE0;
/* Variable used to store the result of version information check*/
uint8 GucVerCheckStatus_PE0;
/* Variable used to store the output state of a channel */
uint8 GucOutputState_PE0;
/* Variables used to store the Notification counts a channel */
uint32 GulEdgeIntCount_PE0[PWM_TOTAL_CHANNELS_CONFIG];

/* Global variable for 1msec timer counter */
volatile uint32 Gul1msecCount;
/*******************************************************************************
**                        User function prototypes                            **
*******************************************************************************/
#ifdef USE_FREERUN_TIMER
/* Variable used to store the timer count */
uint32 GulTimerChannel0CountA;
uint32 GulTimerChannel0CountB;
#if (DEVICE != U2Cx) && (DEVICE != U2Ax)
uint32 GulTimerChannel1CountA;
uint32 GulTimerChannel1CountB;
#endif
uint32 GulTimerChannel2CountA;
uint32 GulTimerChannel2CountB;
uint32 GulTimerChannel3CountA;
uint32 GulTimerChannel3CountB;

uint32 GulTimerChannel6CountA;
uint32 GulTimerChannel6CountB;
uint32 GulTimerChannel7CountA;
uint32 GulTimerChannel7CountB;
#if (DEVICE == U2Cx) || (DEVICE == U2Ax)
uint32 GulTimerChannel8CountA;
uint32 GulTimerChannel8CountB;
uint32 GulTimerChannel9CountA;
uint32 GulTimerChannel9CountB;
#endif
#endif

extern void Mcal_Pwm_Init(void);
void task1(void);
void main_sequence(const Pwm_ConfigType * Pwm_Config);
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/


int main(void)
{
    /* Init the MCAL by stub init PORT, MCU, etc */
  Mcal_Pwm_Init();

  /* Call sample app sequence with Pwm_Config_Variant_1 */ 
  main_sequence(Pwm_Config_Variant_1);
  /* Call sample app sequence with Pwm_Config_Variant_2 */
  main_sequence(Pwm_Config_Variant_2);
  
  /* End trap */
  sample_end();
  
}

/*******************************************************************************
**                          Example task functions                            **
*******************************************************************************/
/* Task1, kernel API */
void task1(void)
{
  /* Kernel API handle Pwm_SetDutyCycle request */
  Pwm_Kernel_SetDutyCycle();

  /* Kernel API handle Pwm_SetPeriodAndDuty request */
  Pwm_Kernel_SetPeriodAndDuty();

  /* Kernel API handle Pwm_SetOutputToIdle request */
  Pwm_Kernel_SetOutputToIdle();

  /* Kernel API handle Pwm_SelectChannelClk request */
  Pwm_Kernel_SelectChannelClk();

  /* Kernel API handle Pwm_SetChannelOutput request */
  Pwm_Kernel_SetChannelOutput();
}

void main_sequence(const Pwm_ConfigType * Pwm_Config)
{

  uint8 LucCountTmp;
  /* Reset Gul1msecCount to 0 before start new sequence*/
  Gul1msecCount = 0;

  /* Reset GulEdgeIntCount GucOutputState and to 0 before start new sequence*/
  for (LucCountTmp = 0; LucCountTmp < PWM_TOTAL_CHANNELS_CONFIG; LucCountTmp++)
  {
    GulEdgeIntCount_PE0[LucCountTmp] = 0;
    GucOutputState_PE0 = 0;
  }
  /* Initialize the PWM Driver */
  Pwm_Init(Pwm_Config);
  
  #if (PWM_SYNC_START_SUPPORT == STD_ON)
  /* Initialize PWM channels configured to support synchronous start/stop of timers */
  Pwm_SynchronousInit();

  Pwm_SynchronousStart();
  #endif

  /* Notify the other instance that startup and module initialization has been finished */
  GblSyncFlag = 1;

  /* Invoke OSTM timer, the OSTM counter duration is 1ms */
  App_Pwm_Start_Timer0();

  
  /* Loop until the SW timer reaches 100ms */
  while(Gul1msecCount < 100)
  {
    /* Invoke task 2 at 20ms */
    if (20 == Gul1msecCount)
    {
      volatile uint32 LulCounter;

      #if (PWM_VERSION_INFO_API == STD_ON)
      /* To get the version of the OCU Driver module */
      Pwm_GetVersionInfo(&versionInfo_PE0);

      /* Check for the correctness of version information */
      if ((PWM_VENDOR_ID == versionInfo_PE0.vendorID) &&
          (PWM_MODULE_ID == versionInfo_PE0.moduleID) &&
          (PWM_SW_MAJOR_VERSION == versionInfo_PE0.sw_major_version) &&
          (PWM_SW_MINOR_VERSION == versionInfo_PE0.sw_minor_version) &&
          (PWM_SW_PATCH_VERSION == versionInfo_PE0.sw_patch_version))
      {
        GucVerCheckStatus_PE0 = TRUE;
      }
      else
      {
        GucVerCheckStatus_PE0 = FALSE;
      }
      #endif

      #if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
      #if (DEVICE != U2Cx) && (DEVICE != U2Ax)
      /* Enabling the Notification for PWM channel 1 */
      Pwm_EnableNotification(Pwm_PwmChannel1, PWM_RISING_EDGE);

      for (LulCounter = 0; LulCounter < 8000000; LulCounter++);
      #endif
      
      #if (DEVICE == U2Cx) || (DEVICE == U2Ax)
      /* Enabling the Notification for PWM channel 0 */
      Pwm_EnableNotification(Pwm_PwmChannel0, PWM_RISING_EDGE);

      for (LulCounter = 0; LulCounter < 8000000; LulCounter++);
      
      /* Enabling the Notification for PWM channel 3 */
      Pwm_EnableNotification(Pwm_PwmChannel3, PWM_RISING_EDGE);

      for (LulCounter = 0; LulCounter < 8000000; LulCounter++);
      #endif

      /* Enabling the Notification for PWM channel 7 */
      Pwm_EnableNotification(Pwm_PwmChannel7, PWM_FALLING_EDGE);

      for (LulCounter = 0; LulCounter < 800000; LulCounter++);

      #if (STD_ON == PWM_DIAG_UNIT_USED)
      /* Enable the notification for channel 1 PwmDiag */
      Pwm_EnableNotification(Pwm_PwmChannel1_Diag, PWM_BOTH_EDGES);

      for (LulCounter = 0; LulCounter < 800000; LulCounter++);
      #endif
  
      #if (DEVICE != U2Cx) && (DEVICE != U2Ax)
      /* Disable the notifications for PWM channel 1 */
      Pwm_DisableNotification(Pwm_PwmChannel1);

      for (LulCounter = 0; LulCounter < 8000000; LulCounter++);
      #endif
      
      #if (DEVICE == U2Cx) || (DEVICE == U2Ax)
      /* Disable the notifications for PWM channel 0 */
      Pwm_DisableNotification(Pwm_PwmChannel0);

      for (LulCounter = 0; LulCounter < 8000000; LulCounter++);

      /* Disable the notifications for PWM channel 3 */
      Pwm_DisableNotification(Pwm_PwmChannel3);

      for (LulCounter = 0; LulCounter < 8000000; LulCounter++);
      #endif

      /* Disabling the Notification for PWM channel 7 */
      Pwm_DisableNotification(Pwm_PwmChannel7);

      for (LulCounter = 0; LulCounter < 8000000; LulCounter++);
      #endif

      #if (STD_ON == PWM_DIAG_UNIT_USED)
      /* Enable the notification for channel 1 PwmDiag */
      Pwm_DisableNotification(Pwm_PwmChannel1_Diag);

      for (LulCounter = 0; LulCounter < 800000; LulCounter++);
      #endif

      #if (PWM_SET_DUTY_CYCLE_API == STD_ON)
      #if (DEVICE == U2Cx) || (DEVICE == U2Ax)
      /* Set the Duty cycle for channel 0 */
      Pwm_SetDutyCycle(Pwm_PwmChannel0, 0x6000);
      /* Wait until master core process the request */
      while (CheckSlaveRequest(Pwm_PwmChannel0, PWM_SET_DUTYCYCLE_SID));
      #endif

      /* Set the Duty cycle for channel 7 */
      Pwm_SetDutyCycle(Pwm_PwmChannel7, 0x6000);
      /* Wait until master core process the request */
      while (CheckSlaveRequest(Pwm_PwmChannel7, PWM_SET_DUTYCYCLE_SID));
      #endif

      #if (STD_ON == PWM_DIAG_UNIT_USED)
      #if (PWM_SET_DUTY_CYCLE_API == STD_ON)
      /* Set the Duty cycle for channel 1 PwmDiag */
      Pwm_SetDutyCycle(Pwm_PwmChannel1_Diag, 0x4000);
      /* Wait until master core process the request */
      while (CheckSlaveRequest(Pwm_PwmChannel1_Diag, PWM_SET_DUTYCYCLE_SID));
      #endif

      for (LulCounter = 0; LulCounter < 8000000; LulCounter++);
      #endif

      #if (PWM_SET_PERIOD_AND_DUTY_API == STD_ON)
      /* Set the Period and Duty cycle for channel 6 */
      Pwm_SetPeriodAndDuty(Pwm_PwmChannel6, 0x6000, 0x4000);
      /* Wait until master core process the request */
      while (CheckSlaveRequest(Pwm_PwmChannel6, PWM_SET_PERIODANDDUTY_SID));

      /* Set the Period and Duty cycle for channel 4 */
      Pwm_SetPeriodAndDuty(Pwm_PwmChannel4, 0x6000, 0x4000);
      /* Wait until master core process the request */
      while (CheckSlaveRequest(Pwm_PwmChannel4, PWM_SET_PERIODANDDUTY_SID));

      #if (DEVICE == U2Cx) || (DEVICE == U2Ax)
      /* Set the Period and Duty cycle for channel 0 */
      Pwm_SetPeriodAndDuty(Pwm_PwmChannel0, 0x6000, 0x4000);
      /* Wait until master core process the request */
      while (CheckSlaveRequest(Pwm_PwmChannel0, PWM_SET_PERIODANDDUTY_SID));
      #endif
      #endif

      #if (PWM_SET_OUTPUT_TO_IDLE_API == STD_ON)
      /* Set PWM channel 7 to its idle state */
      Pwm_SetOutputToIdle(Pwm_PwmChannel7);
      /* Wait until master core process the request */
      while (CheckSlaveRequest(Pwm_PwmChannel7, PWM_SET_OUTPUTTOIDLE_SID));
      
      #if (DEVICE == U2Cx) || (DEVICE == U2Ax)
      /* Set PWM channel 0 to its idle state */
      Pwm_SetOutputToIdle(Pwm_PwmChannel0);
      /* Wait until master core process the request */
      while (CheckSlaveRequest(Pwm_PwmChannel0, PWM_SET_OUTPUTTOIDLE_SID));
      #endif
      #endif

      for (LulCounter = 0; LulCounter < 800000; LulCounter++);
      #if (PWM_GET_OUTPUT_STATE_API == STD_ON)
      GucOutputState_PE0 = (uint8)Pwm_GetOutputState(Pwm_PwmChannel7);
  
      #if (DEVICE == U2Cx) || (DEVICE == U2Ax)
      GucOutputState_PE0 = (uint8)Pwm_GetOutputState(Pwm_PwmChannel0);
      #endif
      #endif

      #if (STD_ON == PWM_DIAG_UNIT_USED)
      #if (PWM_SET_OUTPUT_TO_IDLE_API == STD_ON)
      /* Set PWM channel 1 PwmDiag to its idle state */
      Pwm_SetOutputToIdle(Pwm_PwmChannel1_Diag);
      /* Wait until master core process the request */
      while (CheckSlaveRequest(Pwm_PwmChannel1_Diag, PWM_SET_OUTPUTTOIDLE_SID));
      #endif
      #endif

      #if (PWM_SET_DUTY_CYCLE_API == STD_ON)
      /* Set the Duty cycle for channel 7 */
      Pwm_SetDutyCycle(Pwm_PwmChannel7, 0x5000);
      /* Wait until master core process the request */
      while (CheckSlaveRequest(Pwm_PwmChannel7, PWM_SET_DUTYCYCLE_SID));

      #if (DEVICE == U2Cx) || (DEVICE == U2Ax)
      /* Set the Duty cycle for channel 0 */
      Pwm_SetDutyCycle(Pwm_PwmChannel0, 0x5000);
      /* Wait until master core process the request */
      while (CheckSlaveRequest(Pwm_PwmChannel0, PWM_SET_DUTYCYCLE_SID));
      #endif
      #endif

      for (LulCounter = 0; LulCounter < 8000000; LulCounter++);

      #if (STD_ON == PWM_DIAG_UNIT_USED)
      #if (PWM_SET_DUTY_CYCLE_API == STD_ON)
      /* Set the Duty cycle for channel 1 */
      Pwm_SetDutyCycle(Pwm_PwmChannel1_Diag, 0x2000);
      /* Wait until master core process the request */
      while (CheckSlaveRequest(Pwm_PwmChannel1_Diag, PWM_SET_DUTYCYCLE_SID));
      #endif

      for (LulCounter = 0; LulCounter < 8000000; LulCounter++);
      #endif

      #if (PWM_SET_CHANNEL_OUTPUT_API == STD_ON)
      /* Set Constant state High for PWM channel 7 */
      Pwm_SetChannelOutput(Pwm_PwmChannel7, PWM_HIGH);
      /* Wait until master core process the request */
      while (CheckSlaveRequest(Pwm_PwmChannel7, PWM_SET_CHANNEL_OUTPUT_SID));
      #endif
  
      #if (PWM_GET_OUTPUT_STATE_API == STD_ON)
      GucOutputState_PE0 = (uint8)Pwm_GetOutputState(Pwm_PwmChannel7);
      #endif

      for (LulCounter = 0; LulCounter < 8000000; LulCounter++);

      #if (DEVICE == U2Cx)
      #if (PWM_SET_CHANNEL_OUTPUT_API == STD_ON)
      /* Set Constant state High for PWM channel 0 */
      Pwm_SetChannelOutput(Pwm_PwmChannel0, PWM_HIGH);
      /* Wait until master core process the request */
      while (CheckSlaveRequest(Pwm_PwmChannel0, PWM_SET_CHANNEL_OUTPUT_SID));
      #endif

      #if (PWM_GET_OUTPUT_STATE_API == STD_ON)
      GucOutputState_PE0 = (uint8)Pwm_GetOutputState(Pwm_PwmChannel0);
      #endif

      for (LulCounter = 0; LulCounter < 8000000; LulCounter++);
      #endif

      #if (PWM_SELECT_CHANNEL_CLK_API == STD_ON)
      /* Select channel clock source of PWM channel6 to PWMCLK0 */
      Pwm_SelectChannelClk(Pwm_PwmChannel6, PWM_SELECT_CHANNEL_CLOCK0);
      /* Wait until master core process the request */
      while (CheckSlaveRequest(Pwm_PwmChannel6, PWM_SELECT_CHANNEL_CLK_SID));

      #if (DEVICE == U2Cx) || (DEVICE == U2Ax)
      /* Select channel clock source of PWM channel0 to PWMCLK0 */
      Pwm_SelectChannelClk(Pwm_PwmChannel0, PWM_CCM_CLK_RES_0);
      /* Wait until master core process the request */
      while (CheckSlaveRequest(Pwm_PwmChannel0, PWM_SELECT_CHANNEL_CLK_SID));
      #endif
      #endif
    }
  } /* End of main() function */

  /* Wait until core 1 is done with task3 */
  while(1U == GblSyncFlag);

  #if (PWM_SYNC_START_SUPPORT == STD_ON)
  Pwm_SynchronousStop();
  #endif

  #if (PWM_DE_INIT_API == STD_ON)
  /* Deinit the Pwm module */
  Pwm_DeInit();
  #endif

}

/*******************************************************************************
**                         Timer Interrupt routine                            **
*******************************************************************************/
/* 1 msec timer interrupt */
#ifdef CCRH
#pragma interrupt Timer0_Interrupt(enable=false, fpu=true, fxu=false, callt=false)
#endif
_INTERRUPT_ void Timer0_Interrupt(void)
{
  /* Increase the SW counter */
  Gul1msecCount++;
  /* Invoke task 1 every 1 ms */
  task1();
}

#define PWM_START_SEC_APPL_CODE
#include "Pwm_MemMap.h"
/*******************************************************************************
**                         Notification function                              **
*******************************************************************************/
/* Notification for channel */
/* Notification for channel0 */
void Pwm_Notification_PwmChannel_Variant_1(void)
{
#ifdef USE_FREERUN_TIMER
  GulTimerChannel0CountA = GulTimerChannel0CountB;
  GulTimerChannel0CountB = PWM_OSTM0CNT;
#endif
  GulEdgeIntCount_PE0[0]++;
}

#if (DEVICE != U2Cx) && (DEVICE != U2Ax)
/* Notification for channel1 */
void Pwm_Notification_PwmChannel_001_Variant_1(void)
{
#ifdef USE_FREERUN_TIMER
  GulTimerChannel1CountA = GulTimerChannel0CountB;
  GulTimerChannel1CountB = PWM_OSTM0CNT;
#endif
  GulEdgeIntCount_PE0[1]++;
}
#endif

/* Notification for channel2 */
void Pwm_Notification_PwmChannel_002_Variant_1(void)
{
#ifdef USE_FREERUN_TIMER
  GulTimerChannel2CountA = GulTimerChannel0CountB;
  GulTimerChannel2CountB = PWM_OSTM0CNT;
#endif
  GulEdgeIntCount_PE0[2]++;
}

/* Notification for channel3 */
void Pwm_Notification_PwmChannel_003_Variant_1(void)
{
#ifdef USE_FREERUN_TIMER
  GulTimerChannel3CountA = GulTimerChannel0CountB;
  GulTimerChannel3CountB = PWM_OSTM0CNT;
#endif
  GulEdgeIntCount_PE0[3]++;
}

/* Notification for channel6 */
void Pwm_Notification_PwmChannel_006_Variant_1(void)
{
#ifdef USE_FREERUN_TIMER
  GulTimerChannel6CountA = GulTimerChannel6CountB;
  GulTimerChannel6CountB = PWM_OSTM0CNT;
#endif
  GulEdgeIntCount_PE0[6]++;
}
/* Notification for channel7 */
void Pwm_Notification_PwmChannel_007_Variant_1(void)
{
#ifdef USE_FREERUN_TIMER
  GulTimerChannel7CountA = GulTimerChannel6CountB;
  GulTimerChannel7CountB = PWM_OSTM0CNT;
#endif
  GulEdgeIntCount_PE0[7]++;
}

/* Notification for channel0 */
void Pwm_Notification_PwmChannel_Variant_2(void)
{
#ifdef USE_FREERUN_TIMER
  GulTimerChannel0CountA = GulTimerChannel0CountB;
  GulTimerChannel0CountB = PWM_OSTM0CNT;
#endif
  GulEdgeIntCount_PE0[0]++;
}

#if (DEVICE != U2Cx) && (DEVICE != U2Ax)
/* Notification for channel1 */
void Pwm_Notification_PwmChannel_001_Variant_2(void)
{
#ifdef USE_FREERUN_TIMER
  GulTimerChannel1CountA = GulTimerChannel0CountB;
  GulTimerChannel1CountB = PWM_OSTM0CNT;
#endif
  GulEdgeIntCount_PE0[1]++;
}
#endif

/* Notification for channel2 */
void Pwm_Notification_PwmChannel_002_Variant_2(void)
{
#ifdef USE_FREERUN_TIMER
  GulTimerChannel2CountA = GulTimerChannel0CountB;
  GulTimerChannel2CountB = PWM_OSTM0CNT;
#endif
  GulEdgeIntCount_PE0[2]++;
}

/* Notification for channel3 */
void Pwm_Notification_PwmChannel_003_Variant_2(void)
{
#ifdef USE_FREERUN_TIMER
  GulTimerChannel3CountA = GulTimerChannel0CountB;
  GulTimerChannel3CountB = PWM_OSTM0CNT;
#endif
  GulEdgeIntCount_PE0[3]++;
}

/* Notification for channel6 */
void Pwm_Notification_PwmChannel_006_Variant_2(void)
{
#ifdef USE_FREERUN_TIMER
  GulTimerChannel6CountA = GulTimerChannel6CountB;
  GulTimerChannel6CountB = PWM_OSTM0CNT;
#endif
  GulEdgeIntCount_PE0[6]++;
}
/* Notification for channel7 */
void Pwm_Notification_PwmChannel_007_Variant_2(void)
{
#ifdef USE_FREERUN_TIMER
  GulTimerChannel7CountA = GulTimerChannel6CountB;
  GulTimerChannel7CountB = PWM_OSTM0CNT;
#endif
  GulEdgeIntCount_PE0[7]++;
}

#if (DEVICE != U2Cx) && (DEVICE != U2Ax)
#if(PWM_DIAG_UNIT_USED == STD_ON)
void Pwm_DiagNotification_00_Variant_1 (uint32 LulIntFactor)
{
  GulEdgeIntCount_PE0[8]++;
}
#endif

#if(PWM_DIAG_UNIT_USED == STD_ON)
void Pwm_DiagNotification_00_Variant_2 (uint32 LulIntFactor)
{
  GulEdgeIntCount_PE0[8]++;
}
#endif
#endif

#if (DEVICE == U2Cx) || (DEVICE == U2Ax)
/* Notification for channel8 */
void Pwm_Notification_PwmChannel_008_Variant_1(void)
{
#ifdef USE_FREERUN_TIMER
  GulTimerChannel8CountA = GulTimerChannel8CountB;
  GulTimerChannel8CountB = PWM_OSTM0CNT;
#endif
  GulEdgeIntCount_PE0[8]++;
}

/* Notification for channel8 */
void Pwm_Notification_PwmChannel_008_Variant_2(void)
{
#ifdef USE_FREERUN_TIMER
  GulTimerChannel8CountA = GulTimerChannel8CountB;
  GulTimerChannel8CountB = PWM_OSTM0CNT;
#endif
  GulEdgeIntCount_PE0[8]++;
}

/* Notification for channel9 */
void Pwm_Notification_PwmChannel_009_Variant_1(void)
{
#ifdef USE_FREERUN_TIMER
  GulTimerChannel9CountA = GulTimerChannel9CountB;
  GulTimerChannel9CountB = PWM_OSTM0CNT;
#endif
  GulEdgeIntCount_PE0[9]++;
}

/* Notification for channel9 */
void Pwm_Notification_PwmChannel_009_Variant_2(void)
{
#ifdef USE_FREERUN_TIMER
  GulTimerChannel9CountA = GulTimerChannel9CountB;
  GulTimerChannel9CountB = PWM_OSTM0CNT;
#endif
  GulEdgeIntCount_PE0[9]++;
}

#if(PWM_DIAG_UNIT_USED == STD_ON)
void Pwm_DiagNotification_00_Variant_1 (uint32 LulIntFactor)
{
  GulEdgeIntCount_PE0[10]++;
}

void Pwm_DiagNotification_00_Variant_2 (uint32 LulIntFactor)
{
  GulEdgeIntCount_PE0[10]++;
}
#endif
#endif

#define PWM_STOP_SEC_APPL_CODE
#include "Pwm_MemMap.h"


/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
