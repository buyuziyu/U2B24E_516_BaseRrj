/*============================================================================*/
/* Project      = RH850/X2x AR4 MCAL Development                              */
/* Module       = App_PWM_PostBuildVariant_Sample.c                           */
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
 *        15/04/2025 : Update to not call Pwm_SetChannelOutput for U2Ax GTM   **
 * 2.3.1: 31/03/2025 : Update SW-VERSION for U2BxE Ver22.00.02 Beta Release   **
 *                     As part of U2BxE support, following changes are made:  **
 *                     1. Add function Guard_Enable_PE, GblSyncCoreFlag       **
 * 2.3.0: 28/02/2025 : As part of GTM support, following changes are made     **
 *                     1. Update sample app for GTM channel in U2Cx           **
 *                     2. Remove PWM_DEVICE_U2B12E_U2B6E macro for U2BxE      **
 * 2.2.0: 31/12/2024 : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final  **
 *                     Release                                                **
 *                     As part of U2BxE support, following changes are made:  **
 *                     1. Add macro RUN_OTHER_PE ,RUN_PEx(x from 1 to 6) for  **
 *                        run multiple PE                                     **
 *                     2. Update Pwm_SelectChannelClk for device U2B12E, U2B6E**
 * 2.1.2: 31/10/2024 : As part of GTM support, following changes are made     **
 *                     1. Update function Pwm_SelectChannelClk for GTM        **
 *                     2. Add macro for DeInit                                **
 * 2.1.1: 18/06/2024 : As part of U2C support, following changes are made:    **
 *                     1. Update sample app for channel Diag                  **
 *        15/06/2024 : As part of U2BxE support, following changes are made:  **
 *                     1. Update sample app for device U2B12E, U2B6E          **
 * 2.1.1: 20/05/2024 : Add U2BxE to section Global variables                  **
 * 1.0.0: 25/03/2024 : Initial Version.                                       **
 *                                                                            */
/******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "App_Pwm_Common_Sample.h"
#include "Pwm.h"
/*******************************************************************************
**                            Macros                                          **
*******************************************************************************/
#define LULCOUNTER_MAX    (800000UL)

/*******************************************************************************
**                        Global variables                                    **
*******************************************************************************/

/* Variable used to store the version information */
Std_VersionInfoType versionInfo;
/* Variable used to store the result of version information check*/
uint8 GucVerCheckStatus;

#if ((PWM_DEVICE_U2Ax==STD_ON)||(DEVICE == U2Bx)||(DEVICE == U2Cx)||(DEVICE == U2BxE))
/* Variable used to store the output state of a channel */
uint8 GucOutputState[PWM_TOTAL_CHANNELS_CONFIG];
/* Variables used to store the Notification counts a channel */
uint32 GulEdgeIntCount[PWM_TOTAL_CHANNELS_CONFIG];
uint32 GulTest;
#ifdef USE_FREERUN_TIMER
/* Variable used to store the timer count */
uint32 GulTimerChannel0CountA;
uint32 GulTimerChannel0CountB;
uint32 GulTimerChannel1CountA;
uint32 GulTimerChannel1CountB;
uint32 GulTimerChannel2CountA;
uint32 GulTimerChannel2CountB;
uint32 GulTimerChannel3CountA;
uint32 GulTimerChannel3CountB;

uint32 GulTimerChannel4CountA;
uint32 GulTimerChannel4CountB;
uint32 GulTimerChannel5CountA;
uint32 GulTimerChannel5CountB;
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
#elif (DEVICE == E2x)
/* Variable used to store the output state of a channel */
uint8 GucOutputState;
/* Variables used to store the Notification counts a channel */
uint32 GulEdgeIntCount[36];
#endif
#if defined (RUN_OTHER_PE)
volatile uint8 GblSyncCoreFlag = 0;
#endif
/*******************************************************************************
**                        User function prototypes                            **
*******************************************************************************/
#if ((PWM_TAUD_UNIT_USED == STD_ON) || (PWM_TAUJ_UNIT_USED == STD_ON))
extern void Clock_Init(void);
#endif
extern void Mcu_Init(void);
extern void Port_Init(void);
extern void Wdg_Init(void);
extern void Reg_Init(void);
void main_sequence(const Pwm_ConfigType * Pwm_Config);

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
void sample_end(void)
{
  while(1)
  {
    /* No action required*/
  };
}

int main(void)
#if defined (RUN_OTHER_PE)
{
  Guard_Enable_PE();
  GblSyncCoreFlag = 1;
  while(1);
}
#if defined(RUN_PE1)
int main_PE1(void)

#elif defined(RUN_PE2)
int main_PE2(void)

#elif defined(RUN_PE3)
int main_PE3(void)

#elif defined(RUN_PE4)
int main_PE4(void)

#elif defined(RUN_PE5)
int main_PE5(void)

#elif defined(RUN_PE6)
int main_PE6(void)
#endif
#endif
{

  /* Initialize MCU */
  Mcu_Init();

  /* Initialize the Port pins */
  Port_Init();

  /* Initialize the watchdog */
  Wdg_Init();

  /* Initialization of the table reference bit in ICR register */
  Reg_Init();
  
  /* Enable Global Interrupt */
  ENABLE_INTERRUPT();

  /* Call sample app sequence with Pwm_Config_Variant_1 */ 
  main_sequence(Pwm_Config_Variant_1);
  /* Call sample app sequence with Pwm_Config_Variant_2 */
  main_sequence(Pwm_Config_Variant_2);
  
  /* End trap */
  sample_end();
  #if defined (RUN_OTHER_PE)
  return 0;
  #endif


}

void main_sequence(const Pwm_ConfigType * Pwm_Config)
{
  volatile uint32 LulCounter;

  uint8 LucCountTmp;
  #if (DEVICE == E2x)
  /* Variable used to checking of Option Byte */
  Std_ReturnType LddReturnOpbtResult;
  /* Initialized variable */
  LddReturnOpbtResult = E_NOT_OK;

  /* Checking Option Byte */
  LddReturnOpbtResult =  Pwm_CheckOpbtTimerIpSelect();
  if (E_OK == LddReturnOpbtResult)
 #endif
  {

  for (LucCountTmp = 0; LucCountTmp < PWM_TOTAL_CHANNELS_CONFIG; LucCountTmp++)
  {
    GulEdgeIntCount[LucCountTmp] = 0;
    GucOutputState[LucCountTmp] = 0;
  }

  #if (PWM_VERSION_INFO_API == STD_ON)
  /* To get the version of the PWM Driver module */
  Pwm_GetVersionInfo(&versionInfo);

  /* Check for the correctness of version information */
  if ((PWM_VENDOR_ID == versionInfo.vendorID) &&
      (PWM_MODULE_ID == versionInfo.moduleID) &&
      (PWM_SW_MAJOR_VERSION == versionInfo.sw_major_version) &&
      (PWM_SW_MINOR_VERSION == versionInfo.sw_minor_version) &&
      (PWM_SW_PATCH_VERSION == versionInfo.sw_patch_version))
  {
    GucVerCheckStatus = TRUE;
  }
  else
  {
    GucVerCheckStatus = FALSE;
  }
  #endif

#if ((PWM_DEVICE_U2Ax==STD_ON)||(DEVICE == U2Cx))
#ifdef USE_FREERUN_TIMER
  /* Timer Initialization */
  App_Start_FreeRun_Timer();
#endif
#endif

  /* Initialize the PWM Driver */
  Pwm_Init(Pwm_Config);

  #if (PWM_SYNC_START_SUPPORT == STD_ON)
  /* Initialize PWM channels configured to support synchronous start/stop of
     timers */
  Pwm_SynchronousInit();

  /* Start PWM channels configured to support synchronous start/stop of
        timers */
  Pwm_SynchronousStart();

  #endif

  #if (PWM_SET_DUTY_CYCLE_API == STD_ON)
    /* Set the Duty cycle for channel 2 */
  Pwm_SetDutyCycle(Pwm_PwmChannel2, 0x6000);
  
  #if (DEVICE == U2Cx) || (DEVICE == U2Ax)
  /* Set the Duty cycle for channel 1 */
  Pwm_SetDutyCycle(Pwm_PwmChannel1, 0x6000);
  #endif
  #endif

  /* Add some delay to make sure the simultaneous rewrite has been completed
  * for Pwm_PwmChannel2. This value of delay isn't specific, it only much
  * longer than the current pwm cycle.
  */
  for (LulCounter = 0; LulCounter < LULCOUNTER_MAX; LulCounter++);
  for (LulCounter = 0; LulCounter < LULCOUNTER_MAX; LulCounter++);

  #if (PWM_SET_PERIOD_AND_DUTY_API == STD_ON)
  /* Set the Period and Duty cycle for channel 0 */
  Pwm_SetPeriodAndDuty(Pwm_PwmChannel0, 0xFFFF, 0x4000);

  #if (DEVICE == U2Cx) || (DEVICE == U2Ax)
  /* Set the Period and Duty cycle for channel 2 */
  Pwm_SetPeriodAndDuty(Pwm_PwmChannel2, 0xFFFF, 0x4000);
  #endif
  #endif

  /* Add some delay to make sure the simultaneous rewrite has been completed
  * for Pwm_PwmChannel1, Pwm_PwmChannel2 and Pwm_PwmChannel3. This value of
  * delay isn't specific, it only much longer than the current pwm cycle.
  */
  for (LulCounter = 0; LulCounter < LULCOUNTER_MAX; LulCounter++);
  for (LulCounter = 0; LulCounter < LULCOUNTER_MAX; LulCounter++);

  #if(PWM_DIAG_UNIT_USED == STD_ON)
  #if(PWM_SET_DUTY_CYCLE_API == STD_ON)
    /* Set the Duty cycle for channel 1 PwmDiag */
  Pwm_SetDutyCycle(Pwm_PwmChannel1_Diag, 0x6000);
    /* Set the Duty cycle for channel 2 PwmDiag */
  Pwm_SetDutyCycle(Pwm_PwmChannel2_Diag, 0x6000);
  #endif
  #endif

  /* Add some delay to make sure the simultaneous rewrite has been completed
  * for Pwm_PwmChannel2. This value of delay isn't specific, it only much
  * longer than the current pwm cycle.
  */
  for (LulCounter = 0; LulCounter < LULCOUNTER_MAX; LulCounter++);
  for (LulCounter = 0; LulCounter < LULCOUNTER_MAX; LulCounter++);
  #if (PWM_SET_OUTPUT_TO_IDLE_API == STD_ON)
  /* Set PWM channel 1 to its idle state */
  Pwm_SetOutputToIdle(Pwm_PwmChannel1);
  
  #if (DEVICE == U2Cx) || (DEVICE == U2Ax)
  /* Set PWM channel 3 to its idle state */
  Pwm_SetOutputToIdle(Pwm_PwmChannel3);
  #endif
  #endif

  #if (PWM_GET_OUTPUT_STATE_API == STD_ON)
  /* Get PWM channel 1 output state */
  GucOutputState[Pwm_PwmChannel1] = Pwm_GetOutputState(Pwm_PwmChannel1);
  
  #if (DEVICE == U2Cx) || (DEVICE == U2Ax)
  /* Get PWM channel 3 output state */
  GucOutputState[Pwm_PwmChannel3] = Pwm_GetOutputState(Pwm_PwmChannel3);
  #endif
  #endif

  #if (PWM_DIAG_UNIT_USED == STD_ON)
  #if (PWM_SET_OUTPUT_TO_IDLE_API == STD_ON)
  /* Set PWM channel 2 PwmDiag to its idle state */
  Pwm_SetOutputToIdle(Pwm_PwmChannel2_Diag);
  #endif
  #endif

  #if (PWM_SET_DUTY_CYCLE_API == STD_ON)
  /* Set the Duty cycle for channel 1 */
  Pwm_SetDutyCycle(Pwm_PwmChannel1, 0x2000);
  
  #if (DEVICE == U2Cx) || (DEVICE == U2Ax)
  /* Set the Duty cycle for channel 3 */
  Pwm_SetDutyCycle(Pwm_PwmChannel3, 0x2000);
  #endif
  #endif

  #if (PWM_DIAG_UNIT_USED == STD_ON)
  #if (PWM_SET_DUTY_CYCLE_API == STD_ON)
  /* Set PWM channel 2 PwmDiag to its idle state */
  Pwm_SetDutyCycle(Pwm_PwmChannel2_Diag, 0x2000);
  #endif
  #endif

  #if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
  /* Enable notification for PWM channel 1 */
  Pwm_EnableNotification(Pwm_PwmChannel1, PWM_BOTH_EDGES);
  /* Enable notification for PWM channel 5 */
  Pwm_EnableNotification(Pwm_PwmChannel5, PWM_BOTH_EDGES);
  #if (STD_ON == PWM_TAUD_UNIT_USED && STD_ON == PWM_TAUD3_UNIT_USED)
  /* Enable the notification for PWM TAUD3 channel*/
  Pwm_EnableNotification(Pwm_PwmChannel7, PWM_BOTH_EDGES);
  #elif ((STD_ON == PWM_TAUJ_UNIT_USED) && (STD_ON == PWM_TAUD_UNIT_USED))
  /* Enable the notification for PWM TAUJ3 channel*/
  Pwm_EnableNotification(Pwm_PwmChannel7, PWM_BOTH_EDGES);
  #endif
  #if (STD_ON == PWM_DIAG_UNIT_USED)
  /* Enable the notification for channel 1 PwmDiag */
  Pwm_EnableNotification(Pwm_PwmChannel1_Diag, PWM_BOTH_EDGES);
  /* Enable the notification for channel 2 PwmDiag */
  Pwm_EnableNotification(Pwm_PwmChannel2_Diag, PWM_BOTH_EDGES);
  #endif
  #endif /* end #if (PWM_NOTIFICATION_SUPPORTED == STD_ON) */

  /* Add some delay to verify that the notifications occurs
  * and the variables 'GulEdgeIntCount[1]' and 'GulEdgeIntCount[5]' gets
  * incremented every time the user defined notification function is invoked.
  */
  for (LulCounter = 0; LulCounter < LULCOUNTER_MAX; LulCounter++);
  for (LulCounter = 0; LulCounter < LULCOUNTER_MAX; LulCounter++);

  #if (DEVICE != U2Cx) && (DEVICE != U2Ax)
  #if (PWM_SET_CHANNEL_OUTPUT_API == STD_ON)
  /* Set Constant state Low for PWM channel 2 */
  Pwm_SetChannelOutput(Pwm_PwmChannel2, PWM_LOW);
  #endif

  #if (PWM_GET_OUTPUT_STATE_API == STD_ON)
  /* Check PWM channel 2 output state */
  GucOutputState[Pwm_PwmChannel2] = Pwm_GetOutputState(Pwm_PwmChannel2);
  #endif
  #endif
  
  #if (DEVICE == U2Cx)
  #if (PWM_SET_CHANNEL_OUTPUT_API == STD_ON)
  /* Set Constant state Low for PWM channel 0 */
  Pwm_SetChannelOutput(Pwm_PwmChannel0, PWM_LOW);
  #endif

  #if (PWM_GET_OUTPUT_STATE_API == STD_ON)
  /* Check PWM channel 0 output state */
  GucOutputState[Pwm_PwmChannel0] = Pwm_GetOutputState(Pwm_PwmChannel0);
  #endif
  #endif

  #if (DEVICE == U2Cx) || (DEVICE == U2Ax)
  #if (PWM_SET_CHANNEL_OUTPUT_API == STD_ON)
  /* Set Constant state Low for PWM channel 4 */
  Pwm_SetChannelOutput(Pwm_PwmChannel4, PWM_LOW);
  #endif

  #if (PWM_GET_OUTPUT_STATE_API == STD_ON)
  /* Check PWM channel 4 output state */
  GucOutputState[Pwm_PwmChannel4] = Pwm_GetOutputState(Pwm_PwmChannel4);
  #endif
  #endif

  /* Add some delay to verify that the Pwm channel is set to a constant state
   * and will resume to previous output once the current period is completed.
   */
  for (LulCounter = 0; LulCounter < LULCOUNTER_MAX; LulCounter++);
  for (LulCounter = 0; LulCounter < LULCOUNTER_MAX; LulCounter++);

  #if (PWM_SET_CHANNEL_OUTPUT_API == STD_ON)
  /* Set Constant state Low for PWM channel 7 */
  Pwm_SetChannelOutput(Pwm_PwmChannel7, PWM_HIGH);
  /* Add some delay to verify that the Pwm channel is set to a constant state
   * and will resume to previous output once the current period is completed.
   */
  #endif

  #if (PWM_GET_OUTPUT_STATE_API == STD_ON)
  /* Check PWM channel 7 output state */
  GucOutputState[Pwm_PwmChannel7] = Pwm_GetOutputState(Pwm_PwmChannel7);
  #endif

  for (LulCounter = 0; LulCounter < LULCOUNTER_MAX; LulCounter++);
  for (LulCounter = 0; LulCounter < LULCOUNTER_MAX; LulCounter++);

  #if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
  /* Disable the notifications for PWM master channel 1 */
  Pwm_DisableNotification(Pwm_PwmChannel1);
  /* Add some delay to verify that the notifications does not occur and the variable 'GulEdgeIntCount[1]' 
     does not get incremented */
  /* Reset GulEdgeIntCount to 0 */
  GulEdgeIntCount[1] = 0;

  /* Disable the notifications for PWM channel 4 and 5 */
  Pwm_DisableNotification(Pwm_PwmChannel4);
  Pwm_DisableNotification(Pwm_PwmChannel5);
  /* Reset GulEdgeIntCount to 0 */
  GulEdgeIntCount[4] = 0;
  GulEdgeIntCount[5] = 0;
  /* Add some delay to verify that the notifications does not occur and the variable 'GulEdgeIntCount[5]' 
     does not get incremented */
  #if (STD_ON == PWM_TAUD_UNIT_USED && STD_ON == PWM_TAUD3_UNIT_USED)
  /* Disable the notifications for PWM channel 6 and 7 */
  Pwm_DisableNotification(Pwm_PwmChannel6);
  Pwm_DisableNotification(Pwm_PwmChannel7);
  /* Reset GulEdgeIntCount to 0 */
  GulEdgeIntCount[6] = 0;
  GulEdgeIntCount[7] = 0;
  #elif ((STD_ON == PWM_TAUJ_UNIT_USED) && (STD_ON == PWM_TAUD_UNIT_USED))
  /* Enable the notification for PWM TAUJ3 channel 6 and 7*/
  Pwm_DisableNotification(Pwm_PwmChannel6);
  Pwm_DisableNotification(Pwm_PwmChannel7);
  /* Reset GulEdgeIntCount to 0 */
  GulEdgeIntCount[6] = 0;
  GulEdgeIntCount[7] = 0;
  #endif
  #if (STD_ON == PWM_DIAG_UNIT_USED)
  #if (DEVICE != U2Cx) && (DEVICE != U2Ax)
  /* Enable the notification for PWM channel 1 PwmDiag */
  Pwm_DisableNotification(Pwm_PwmChannel1_Diag);
  /* Reset GulEdgeIntCount to 0 */
  GulEdgeIntCount[8] = 0;
  /* Enable the notification for PWM channel 2 PwmDiag */
  Pwm_DisableNotification(Pwm_PwmChannel2_Diag);
  /* Reset GulEdgeIntCount to 0 */
  GulEdgeIntCount[9] = 0;
  #endif

  #if (DEVICE == U2Cx) || (DEVICE == U2Ax)
  /* Enable the notification for PWM channel 1 Pwm-Diag */
  Pwm_DisableNotification(Pwm_PwmChannel1_Diag);
  /* Reset GulEdgeIntCount to 0 */
  GulEdgeIntCount[10] = 0;
  /* Enable the notification for PWM channel 2 Pwm-Diag */
  Pwm_DisableNotification(Pwm_PwmChannel2_Diag);
  /* Reset GulEdgeIntCount to 0 */
  GulEdgeIntCount[11] = 0;
  #endif
  #endif
  #endif
  /* Add some delay to verify that the notifications does not occur and the variable 'GulEdgeIntCount[7]' 
     does not get incremented */

  for (LulCounter = 0; LulCounter < LULCOUNTER_MAX; LulCounter++);
  for (LulCounter = 0; LulCounter < LULCOUNTER_MAX; LulCounter++);

  #if (PWM_SELECT_CHANNEL_CLK_API == STD_ON)
  #if (PWM_ATU_UNIT_USED == STD_ON)
  /* Select channel clock source of PWM channel0 to PWMCLK1 */
  Pwm_SelectChannelClk(Pwm_PwmChannel0, PWM_CLKBUSLINE1);
  #endif

  #if (PWM_GTM_UNIT_USED == STD_ON)
  #if (DEVICE == U2Bx) || (DEVICE == U2BxE)
  /* Select channel clock source of PWM channel0 to PWMCLK1 */
  Pwm_SelectChannelClk(Pwm_PwmChannel0, PWM_CCM_FXCLK_RES1);
  #endif
  #endif

  #if (DEVICE == U2Cx) || (DEVICE == U2Ax)
  /* Select channel clock source of PWM channel0 to PWMCLK1 */
  Pwm_SelectChannelClk(Pwm_PwmChannel0, PWM_CCM_CLK_RES_1);

  /* Select channel clock source of PWM channel0 to PWMCLK1 */
  Pwm_SelectChannelClk(Pwm_PwmChannel6, PWM_CLKBUSLINE0);
  #endif

  /* Select channel clock source of PWM channel4 to PWMCLK0 */
  Pwm_SelectChannelClk(Pwm_PwmChannel4, PWM_CLKBUSLINE0);
  #endif
  
  #if (PWM_SYNC_START_SUPPORT == STD_ON)
  /* Stop PWM channels configured to support synchronous start/stop of timers */
  Pwm_SynchronousStop();
  #endif/* PWM_SYNC_START_SUPPORT == STD_ON */

  #if (PWM_DE_INIT_API == STD_ON)
  /* De-Initialize the PWM Driver */
  Pwm_DeInit();
  #endif
  }
}
/* End of main function */

/*******************************************************************************
**                         Notification function                              **
*******************************************************************************/
/* Notification for channel0 with varian 1*/
void Pwm_Notification_PwmChannel_Variant_1(void)
{
#ifdef USE_FREERUN_TIMER
  GulTimerChannel1CountA = GulTimerChannel0CountB;
  GulTimerChannel1CountB = PWM_OSTM0CNT;
#endif
  GulEdgeIntCount[0]++;
}

/* Notification for channel1 with varian 1*/
void Pwm_Notification_PwmChannel_001_Variant_1(void)
{
#ifdef USE_FREERUN_TIMER
  GulTimerChannel1CountA = GulTimerChannel0CountB;
  GulTimerChannel1CountB = PWM_OSTM0CNT;
#endif
  GulEdgeIntCount[1]++;
}

/* Notification for channel2 with varian 1*/
void Pwm_Notification_PwmChannel_002_Variant_1(void)
{
#ifdef USE_FREERUN_TIMER
  GulTimerChannel2CountA = GulTimerChannel0CountB;
  GulTimerChannel2CountB = PWM_OSTM0CNT;
#endif
  GulEdgeIntCount[2]++;
}

/* Notification for channel3 with varian 1*/
void Pwm_Notification_PwmChannel_003_Variant_1(void)
{
#ifdef USE_FREERUN_TIMER
  GulTimerChannel3CountA = GulTimerChannel0CountB;
  GulTimerChannel3CountB = PWM_OSTM0CNT;
#endif
  GulEdgeIntCount[3]++;
}

/* Notification for channel4 with varian 1*/
void Pwm_Notification_PwmChannel_004_Variant_1(void)
{
#ifdef USE_FREERUN_TIMER
  GulTimerChannel4CountA = GulTimerChannel4CountB;
  GulTimerChannel4CountB = PWM_OSTM0CNT;
#endif
  GulEdgeIntCount[4]++;
}

/* Notification for channel5 with varian 1*/
void Pwm_Notification_PwmChannel_005_Variant_1(void)
{
#ifdef USE_FREERUN_TIMER
  GulTimerChannel5CountA = GulTimerChannel4CountB;
  GulTimerChannel5CountB = PWM_OSTM0CNT;
#endif
  GulEdgeIntCount[5]++;
}

/* Notification for channel6 with varian 1*/
void Pwm_Notification_PwmChannel_006_Variant_1(void)
{
#ifdef USE_FREERUN_TIMER
  GulTimerChannel6CountA = GulTimerChannel4CountB;
  GulTimerChannel6CountB = PWM_OSTM0CNT;
#endif
  GulEdgeIntCount[6]++;
}

/* Notification for channel7 with varian 1*/
void Pwm_Notification_PwmChannel_007_Variant_1(void)
{
#ifdef USE_FREERUN_TIMER
  GulTimerChannel7CountA = GulTimerChannel4CountB;
  GulTimerChannel7CountB = PWM_OSTM0CNT;
#endif
  GulEdgeIntCount[7]++;
}

#if (DEVICE != U2Cx) && (DEVICE != U2Ax)
/* Notification for channel7 with varian 2*/
#if(PWM_DIAG_UNIT_USED == STD_ON)
void Pwm_DiagNotification_00_Variant_1 (uint32 LulIntFactor)
{
  GulEdgeIntCount[8]++;
}
void Pwm_DiagNotification_01_Variant_1 (uint32 LulIntFactor)
{
  GulEdgeIntCount[9]++;
}
#endif
#endif

#if (DEVICE == U2Cx) || (DEVICE == U2Ax)
/* Notification for channel8 with varian 1*/
void Pwm_Notification_PwmChannel_008_Variant_1(void)
{
#ifdef USE_FREERUN_TIMER
  GulTimerChannel8CountA = GulTimerChannel4CountB;
  GulTimerChannel8CountB = PWM_OSTM0CNT;
#endif
  GulEdgeIntCount[8]++;
}

/* Notification for channel9 with varian 1*/
void Pwm_Notification_PwmChannel_009_Variant_1(void)
{
#ifdef USE_FREERUN_TIMER
  GulTimerChannel9CountA = GulTimerChannel4CountB;
  GulTimerChannel9CountB = PWM_OSTM0CNT;
#endif
  GulEdgeIntCount[9]++;
}

#if(PWM_DIAG_UNIT_USED == STD_ON)
void Pwm_DiagNotification_00_Variant_1 (uint32 LulIntFactor)
{
  GulEdgeIntCount[10]++;
}
void Pwm_DiagNotification_01_Variant_1 (uint32 LulIntFactor)
{
  GulEdgeIntCount[11]++;
}
#endif
#endif

/* Notification for channel0 with varian 2*/
void Pwm_Notification_PwmChannel_Variant_2(void)
{
#ifdef USE_FREERUN_TIMER
  GulTimerChannel1CountA = GulTimerChannel0CountB;
  GulTimerChannel1CountB = PWM_OSTM0CNT;
#endif
  GulEdgeIntCount[0]++;
}

/* Notification for channel1 with varian 2*/
void Pwm_Notification_PwmChannel_001_Variant_2(void)
{
#ifdef USE_FREERUN_TIMER
  GulTimerChannel1CountA = GulTimerChannel0CountB;
  GulTimerChannel1CountB = PWM_OSTM0CNT;
#endif
  GulEdgeIntCount[1]++;
}

/* Notification for channel2 with varian 2*/
void Pwm_Notification_PwmChannel_002_Variant_2(void)
{
#ifdef USE_FREERUN_TIMER
  GulTimerChannel2CountA = GulTimerChannel0CountB;
  GulTimerChannel2CountB = PWM_OSTM0CNT;
#endif
  GulEdgeIntCount[2]++;
}

/* Notification for channel3 with varian 2*/
void Pwm_Notification_PwmChannel_003_Variant_2(void)
{
#ifdef USE_FREERUN_TIMER
  GulTimerChannel3CountA = GulTimerChannel0CountB;
  GulTimerChannel3CountB = PWM_OSTM0CNT;
#endif
  GulEdgeIntCount[3]++;
}

/* Notification for channel4 with varian 2*/
void Pwm_Notification_PwmChannel_004_Variant_2(void)
{
#ifdef USE_FREERUN_TIMER
  GulTimerChannel4CountA = GulTimerChannel4CountB;
  GulTimerChannel4CountB = PWM_OSTM0CNT;
#endif
  GulEdgeIntCount[4]++;
}

/* Notification for channel5 with varian 2*/
void Pwm_Notification_PwmChannel_005_Variant_2(void)
{
#ifdef USE_FREERUN_TIMER
  GulTimerChannel5CountA = GulTimerChannel4CountB;
  GulTimerChannel5CountB = PWM_OSTM0CNT;
#endif
  GulEdgeIntCount[5]++;
}

/* Notification for channel6 with varian 2*/
void Pwm_Notification_PwmChannel_006_Variant_2(void)
{
#ifdef USE_FREERUN_TIMER
  GulTimerChannel6CountA = GulTimerChannel4CountB;
  GulTimerChannel6CountB = PWM_OSTM0CNT;
#endif
  GulEdgeIntCount[6]++;
}

/* Notification for channel7 with varian 2*/
void Pwm_Notification_PwmChannel_007_Variant_2(void)
{
#ifdef USE_FREERUN_TIMER
  GulTimerChannel7CountA = GulTimerChannel4CountB;
  GulTimerChannel7CountB = PWM_OSTM0CNT;
#endif
  GulEdgeIntCount[7]++;
}

#if (DEVICE != U2Cx) && (DEVICE != U2Ax)
/* Notification for channel7 with varian 2*/
#if(PWM_DIAG_UNIT_USED == STD_ON)
void Pwm_DiagNotification_00_Variant_2 (uint32 LulIntFactor)
{
  GulEdgeIntCount[8]++;
}
void Pwm_DiagNotification_01_Variant_2 (uint32 LulIntFactor)
{
  GulEdgeIntCount[9]++;
}
#endif
#endif

#if (DEVICE == U2Cx) || (DEVICE == U2Ax)
/* Notification for channel8 with varian 2*/
void Pwm_Notification_PwmChannel_008_Variant_2(void)
{
#ifdef USE_FREERUN_TIMER
  GulTimerChannel8CountA = GulTimerChannel4CountB;
  GulTimerChannel8CountB = PWM_OSTM0CNT;
#endif
  GulEdgeIntCount[8]++;
}

/* Notification for channel9 with varian 2*/
void Pwm_Notification_PwmChannel_009_Variant_2(void)
{
#ifdef USE_FREERUN_TIMER
  GulTimerChannel9CountA = GulTimerChannel4CountB;
  GulTimerChannel9CountB = PWM_OSTM0CNT;
#endif
  GulEdgeIntCount[9]++;
}

#if(PWM_DIAG_UNIT_USED == STD_ON)
void Pwm_DiagNotification_00_Variant_2 (uint32 LulIntFactor)
{
  GulEdgeIntCount[10]++;
}
void Pwm_DiagNotification_01_Variant_2 (uint32 LulIntFactor)
{
  GulEdgeIntCount[11]++;
}
#endif
#endif
/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
