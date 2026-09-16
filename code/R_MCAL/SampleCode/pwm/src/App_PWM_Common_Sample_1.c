/*============================================================================*/
/* Project      = RH850/X2x AR4 MCAL Development                              */
/* Module       = App_PWM_Common_Sample_1.c                                   */
/*                                                                            */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.        */
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
 *        15/04/2025 : Update to not call Pwm_SetChannelOutput for U2Ax GTM   **
 * 2.3.1: 31/03/2025 : Update SW-VERSION for U2BxE Ver22.00.02 Beta Release   **
 * 2.3.0:  28/02/2025 : As part of GTM support, following changes are made    **
 *                     1. Update sample app for GTM channel in U2Cx           **
 *                     2. Remove PWM_DEVICE_U2B12E_U2B6E macro for U2BxE      **
 * 2.2.0:  31/12/2024 : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final **
 *                      Release                                               **
 *                      As part of U2BxE support, following changes are made: **
 *                      1. Update Pwm_SelectChannelClk for device U2B12E,     **
 *                         U2B6E                                              **
 * 2.1.2:  31/10/2024 : As part of GTM support, following changes are made    **
 *                      1. Update function Pwm_SelectChannelClk for GTM       **
 * 2.1.1:  18/06/2024 : As part of U2C support, following changes are made    **
 *                      1. Update sample app for  channel Diag                **
 *                      As part of U2BxE support, following changes are made  **
 *                      1. Update sample app for device U2B12E, U2B6E         **
 * 2.0.1:  25/10/2023 : Update version in header comment                      **
 * 2.0.0:  05/07/2023 : Re-write test app to support PWM Multi-core           **
 * 1.4.5:  19/01/2023 : Add EIBD for U2B24                                    **
 * 1.4.4:  26/07/2022 : Added bound interrupts for TAUJ1.                     **
 * 1.3.1:  15/05/2021 : Fixed Coding Rule                                     **
 * 1.2.0:  17/07/2020 : Release                                               **
 * 1.1.0:  19/06/2020 : Release                                               **
 * 1.0.1:  01/06/2020 : Removed "#include Pwm_Ram.h"                          **
 * 1.0.0:  24/03/2020 : Initial Version.                                      **
 *                                                                            */
/******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "App_Pwm_Common_Sample_1.h"
#include "App_Pwm_Multi_Sample.h"

/*******************************************************************************
**                            Macros                                          **
*******************************************************************************/

/*******************************************************************************
**                        Global variables                                    **
*******************************************************************************/
/* Variables used to store the Notification counts a channel */
uint32 GulEdgeIntCount_PE1[PWM_TOTAL_CHANNELS_CONFIG];


/* Variable used to store the version information */
Std_VersionInfoType versionInfo_PE1;
extern volatile uint32 Gul1msecCount;
/* Variable used to store the result of version information check*/
uint8 GucVerCheckStatus_PE1;
/* Variable used to store the output state of a channel */
uint8 GucOutputState_PE1;
/*******************************************************************************
**                        User function prototypes                            **
*******************************************************************************/
#ifdef USE_FREERUN_TIMER
/* Variable used to store the timer count */
#if (DEVICE == U2Cx) || (DEVICE == U2Ax)
uint32 GulTimerChannel1CountA;
uint32 GulTimerChannel1CountB;
#endif
uint32 GulTimerChannel4CountA;
uint32 GulTimerChannel4CountB;

uint32 GulTimerChannel5CountA;
uint32 GulTimerChannel5CountB;
#endif
/*******************************************************************************
*                      Function Definitions                                   **
*******************************************************************************/
/* The app default starts on Core 1 after startup */
void main_PE1(void)
{
  /* Wait until Master core is done Initialization */
  while(0U == GblSyncFlag);

  /* Loop until the SW timer reaches 100ms */
  while(Gul1msecCount < 100)
  {
    /* Invoke task 3 at 20ms */
    if (Gul1msecCount == 20U)
    {
      volatile uint32 LulCounter;

      #if (PWM_VERSION_INFO_API == STD_ON)
      /* To get the version of the PWM Driver module */
      Pwm_GetVersionInfo(&versionInfo_PE1);
      /* Check for the correctness of version information */
      if ((PWM_VENDOR_ID == versionInfo_PE1.vendorID) &&
          (PWM_MODULE_ID == versionInfo_PE1.moduleID) &&
          (PWM_SW_MAJOR_VERSION == versionInfo_PE1.sw_major_version) &&
          (PWM_SW_MINOR_VERSION == versionInfo_PE1.sw_minor_version) &&
          (PWM_SW_PATCH_VERSION == versionInfo_PE1.sw_patch_version))
      {
        GucVerCheckStatus_PE1 = TRUE;
      }
      else
      {
        GucVerCheckStatus_PE1 = FALSE;
      }
      #endif

      #if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
      #if (STD_ON == PWM_DIAG_UNIT_USED)
      /* Enabling the Notification */
      Pwm_EnableNotification(Pwm_PwmChannel2_Diag, PWM_BOTH_EDGES);

      for (LulCounter = 0; LulCounter < 8000000; LulCounter++);
      for (LulCounter = 0; LulCounter < 8000000; LulCounter++);
      #endif
      /* Enabling the Notification */
      Pwm_EnableNotification(Pwm_PwmChannel5, PWM_FALLING_EDGE);

      for (LulCounter = 0; LulCounter < 8000000; LulCounter++);
      for (LulCounter = 0; LulCounter < 8000000; LulCounter++);

      #if (DEVICE == U2Cx) || (DEVICE == U2Ax)
      /* Enabling the Notification */
      Pwm_EnableNotification(Pwm_PwmChannel1, PWM_FALLING_EDGE);

      for (LulCounter = 0; LulCounter < 8000000; LulCounter++);
      for (LulCounter = 0; LulCounter < 8000000; LulCounter++);
      #endif

      /* Disabling the Notification */
      Pwm_DisableNotification(Pwm_PwmChannel5);

      for (LulCounter = 0; LulCounter < 8000000; LulCounter++);
      
      #if (DEVICE == U2Cx) || (DEVICE == U2Ax)
      /* Disabling the Notification */
      Pwm_DisableNotification(Pwm_PwmChannel1);

      for (LulCounter = 0; LulCounter < 8000000; LulCounter++);
      #endif
      #endif

      #if (PWM_SET_DUTY_CYCLE_API == STD_ON)
      /* Set the Duty cycle for channel 5 */
      Pwm_SetDutyCycle(Pwm_PwmChannel5, 0x2000);
      /* Wait until master core process the request */
      while (CheckSlaveRequest(Pwm_PwmChannel5, PWM_SET_DUTYCYCLE_SID));

      #if (DEVICE == U2Cx) || (DEVICE == U2Ax)
      /* Set the Duty cycle for channel 1 */
      Pwm_SetDutyCycle(Pwm_PwmChannel1, 0x2000);
      /* Wait until master core process the request */
      while (CheckSlaveRequest(Pwm_PwmChannel1, PWM_SET_DUTYCYCLE_SID));
      #endif
      #endif

      #if (STD_ON == PWM_DIAG_UNIT_USED)
      #if (PWM_SET_DUTY_CYCLE_API == STD_ON)
      /* Set the Duty cycle for channel 1 PwmDiag */
      Pwm_SetDutyCycle(Pwm_PwmChannel2_Diag, 0x4000);
      /* Wait until master core process the request */
      while (CheckSlaveRequest(Pwm_PwmChannel2_Diag, PWM_SET_DUTYCYCLE_SID));
      #endif

      for (LulCounter = 0; LulCounter < 8000000; LulCounter++);
      #endif

      #if (PWM_SET_PERIOD_AND_DUTY_API == STD_ON)
      /* Set the Period and Duty cycle for channel 5 */
      Pwm_SetPeriodAndDuty(Pwm_PwmChannel5, 0x6000, 0x6000);
      /* Wait until master core process the request */
      while (CheckSlaveRequest(Pwm_PwmChannel5, PWM_SET_PERIODANDDUTY_SID));

      #if (DEVICE == U2Cx) || (DEVICE == U2Ax)
      /* Set the Period and Duty cycle for channel 1 */
      Pwm_SetPeriodAndDuty(Pwm_PwmChannel1, 0x6000, 0x6000);
      /* Wait until master core process the request */
      while (CheckSlaveRequest(Pwm_PwmChannel1, PWM_SET_PERIODANDDUTY_SID));
      #endif
      #endif
  
      #if (PWM_SET_OUTPUT_TO_IDLE_API == STD_ON)
      /* Set PWM channel 5 to its idle state */
      Pwm_SetOutputToIdle(Pwm_PwmChannel5);
      /* Wait until master core process the request */
      while (CheckSlaveRequest(Pwm_PwmChannel5, PWM_SET_OUTPUTTOIDLE_SID));

      #if (DEVICE == U2Cx) || (DEVICE == U2Ax)
      /* Set PWM channel 1 to its idle state */
      Pwm_SetOutputToIdle(Pwm_PwmChannel1);
      /* Wait until master core process the request */
      while (CheckSlaveRequest(Pwm_PwmChannel1, PWM_SET_OUTPUTTOIDLE_SID));
      #endif
      #endif

      #if (PWM_GET_OUTPUT_STATE_API == STD_ON)
      GucOutputState_PE1 = (uint8)Pwm_GetOutputState(Pwm_PwmChannel5);

      #if (DEVICE == U2Cx) || (DEVICE == U2Ax)
      GucOutputState_PE1 = (uint8)Pwm_GetOutputState(Pwm_PwmChannel1);
      #endif
      #endif

      for (LulCounter = 0; LulCounter < 8000000; LulCounter++);

      #if (STD_ON == PWM_DIAG_UNIT_USED)
      #if (PWM_SET_OUTPUT_TO_IDLE_API == STD_ON)
      /* Set PWM channel 2 PwmDiag to its idle state */
      Pwm_SetOutputToIdle(Pwm_PwmChannel2_Diag);
      /* Wait until master core process the request */
      while (CheckSlaveRequest(Pwm_PwmChannel2_Diag, PWM_SET_OUTPUTTOIDLE_SID));
      #endif
      #endif

      #if (PWM_SET_DUTY_CYCLE_API == STD_ON)
      /* Set the Duty cycle for channel 5 */
      Pwm_SetDutyCycle(Pwm_PwmChannel5, 0x4000);
      /* Wait until master core process the request */
      while (CheckSlaveRequest(Pwm_PwmChannel5, PWM_SET_DUTYCYCLE_SID));

      for (LulCounter = 0; LulCounter < 800000; LulCounter++);

      #if (DEVICE == U2Cx) || (DEVICE == U2Ax)
      /* Set the Duty cycle for channel 1 */
      Pwm_SetDutyCycle(Pwm_PwmChannel1, 0x4000);
      /* Wait until master core process the request */
      while (CheckSlaveRequest(Pwm_PwmChannel1, PWM_SET_DUTYCYCLE_SID));

      for (LulCounter = 0; LulCounter < 800000; LulCounter++);
      #endif
      #endif

      #if (STD_ON == PWM_DIAG_UNIT_USED)
      #if (PWM_SET_DUTY_CYCLE_API == STD_ON)
      /* Set the Duty cycle for channel 2 PwmDiag */
      Pwm_SetDutyCycle(Pwm_PwmChannel2_Diag, 0x2000);
      /* Wait until master core process the request */
      while (CheckSlaveRequest(Pwm_PwmChannel2_Diag, PWM_SET_DUTYCYCLE_SID));

      for (LulCounter = 0; LulCounter < 800000; LulCounter++);
      #endif
      #endif

      #if (PWM_SET_CHANNEL_OUTPUT_API == STD_ON)
      /* Set Constant state Low for PWM channel 5 */
      Pwm_SetChannelOutput(Pwm_PwmChannel5, PWM_LOW);
      /* Wait until master core process the request */
      while (CheckSlaveRequest(Pwm_PwmChannel5, PWM_SET_CHANNEL_OUTPUT_SID));
      #endif

      #if (PWM_GET_OUTPUT_STATE_API == STD_ON)
      GucOutputState_PE1 = (uint8)Pwm_GetOutputState(Pwm_PwmChannel5);
      #endif

      #if (DEVICE == U2Cx)
      #if (PWM_SET_CHANNEL_OUTPUT_API == STD_ON)
      /* Set Constant state Low for PWM channel 1 */
      Pwm_SetChannelOutput(Pwm_PwmChannel1, PWM_LOW);
      /* Wait until master core process the request */
      while (CheckSlaveRequest(Pwm_PwmChannel1, PWM_SET_CHANNEL_OUTPUT_SID));
      #endif

      #if (PWM_GET_OUTPUT_STATE_API == STD_ON)
      GucOutputState_PE1 = (uint8)Pwm_GetOutputState(Pwm_PwmChannel1);
      #endif
      #endif

      for (LulCounter = 0; LulCounter < 8000000; LulCounter++);

      #if (PWM_SELECT_CHANNEL_CLK_API == STD_ON)
      /* Select channel clock source of PWM channel4 to PWMCLK1 */
      Pwm_SelectChannelClk(Pwm_PwmChannel4, PWM_SELECT_CHANNEL_CLOCK1);
      /* Wait until master core process the request */
      while (CheckSlaveRequest(Pwm_PwmChannel4, PWM_SELECT_CHANNEL_CLK_SID));
      
      #if (DEVICE == U2Cx) || (DEVICE == U2Ax)
      /* Select channel clock source of PWM channel1 to PWMCLK1 */
      Pwm_SelectChannelClk(Pwm_PwmChannel1, PWM_CCM_CLK_RES_1);
      /* Wait until master core process the request */
      while (CheckSlaveRequest(Pwm_PwmChannel1, PWM_SELECT_CHANNEL_CLK_SID));
      #endif
      #endif
    }
  }
  /* Notify core 0 as a task done from core 1 */
  GblSyncFlag = 0;

  /* End trap */
  sample_end();
  //return 0;
} /* End of main() function */

#define PWM_START_SEC_APPL_CODE
#include "Pwm_MemMap.h"
/*******************************************************************************
**                         Notification function                              **
*******************************************************************************/
#if (DEVICE == U2Cx) || (DEVICE == U2Ax)
/* Notification for channel1 */
void Pwm_Notification_PwmChannel_001(void)
{
#ifdef USE_FREERUN_TIMER
  GulTimerChannel1CountA = GulTimerChannel1CountB;
  GulTimerChannel1CountB = PWM_OSTM0CNT;
#endif
  GulEdgeIntCount_PE1[1]++;
}
#endif
/* Notification for channel4 */
void Pwm_Notification_PwmChannel_004(void)
{
#ifdef USE_FREERUN_TIMER
  GulTimerChannel4CountA = GulTimerChannel4CountB;
  GulTimerChannel4CountB = PWM_OSTM0CNT;
#endif
  GulEdgeIntCount_PE1[4]++;
}

/* Notification for channel5 */
void Pwm_Notification_PwmChannel_005(void)
{
#ifdef USE_FREERUN_TIMER
  GulTimerChannel5CountA = GulTimerChannel4CountB;
  GulTimerChannel5CountB = PWM_OSTM0CNT;
#endif
  GulEdgeIntCount_PE1[5]++;
}

#if(PWM_DIAG_UNIT_USED == STD_ON)
void Pwm_DiagNotification_01 (uint32 LulIntFactor)
{
  GulEdgeIntCount_PE1[9]++;
}
#endif

#define PWM_STOP_SEC_APPL_CODE
#include "Pwm_MemMap.h"

/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
