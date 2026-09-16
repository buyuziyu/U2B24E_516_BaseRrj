/*============================================================================*/
/* Project      = RH850 X2x MCAL Ver22.01.00.D                                */
/* Module       = App_GPT_Common_Multicore_PostBuildVariant_Sample_1.c        */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2024, 2025 Renesas Electronics Corporation. All rights reserved.       */
/*============================================================================*/
/* Purpose:                                                                   */
/* This file contains sample application multi core of Core 1 for GPT Driver  */
/* Component                                                                  */
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
/*
 *  2.4.0  30/06/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.01.00 (D) release
 *  2.3.2  25/04/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03
 *  2.3.1  31/03/2025  : Update SW-VERSION for RH850/U2BxE MCAL
 *                       Ver22.00.02/Ver22.00.02.D Release
 *  2.3.0  28/02/2025  : Update SW-VERSION for
 *                       RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 *  2.2.0  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D
 *                       Final Release
 *  2.1.2  31/10/2024  : As part of GTM HWIP support, following changes are made
 *                       1.Add macro to support GTM
 *  2.1.1  22/08/2024  : Add macro to support U2Ax
 *         29/05/2024  : Add marco to support U2BxE
 *  2.0.3  10/04/2024  : Initial Version
 */
/******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "App_GPT_Common_Sample_1.h"
#include "App_Gpt_Multi_Sample.h"
#include "App_GPT_Device_Sample.h"
#include "Gpt.h"
#include "Gpt_PBTypes.h"
/*******************************************************************************
**                            Macros                                          **
*******************************************************************************/

/*******************************************************************************
**                        Global variables                                    **
*******************************************************************************/

/* Global variable to hold the values of GPT */
volatile uint8 GaaNotificationEntered_Core1[10];
extern uint16 LulCount;

#if (GPT_TIME_ELAPSED_API == STD_ON)
Gpt_ValueType Test_Value_Elapsed0_Core1;
Gpt_ValueType Test_Value_Elapsed1_Core1;
Gpt_ValueType Test_Value_Elapsed2_Core1;
Gpt_ValueType Test_Value_Elapsed3_Core1;
Gpt_ValueType Test_Value_Elapsed4_Core1;
Gpt_ValueType Test_Value_Elapsed5_Core1;
Gpt_ValueType Test_Value_Elapsed6_Core1;
Gpt_ValueType Test_Value_Elapsed7_Core1;
Gpt_ValueType Test_Value_Elapsed8_Core1;
Gpt_ValueType Test_Value_Elapsed9_Core1;
#endif
#if (GPT_TIME_REMAINING_API == STD_ON)
Gpt_ValueType Test_Value_Remain0_Core1;
Gpt_ValueType Test_Value_Remain1_Core1;
Gpt_ValueType Test_Value_Remain2_Core1;
Gpt_ValueType Test_Value_Remain3_Core1;
Gpt_ValueType Test_Value_Remain4_Core1;
Gpt_ValueType Test_Value_Remain5_Core1;
Gpt_ValueType Test_Value_Remain6_Core1;
Gpt_ValueType Test_Value_Remain7_Core1;
Gpt_ValueType Test_Value_Remain8_Core1;
Gpt_ValueType Test_Value_Remain9_Core1;
#endif

/*******************************************************************************
**                        User function prototypes                            **
*******************************************************************************/
/* Function prototype variant support */
void Gpt_sequence_variant1(uint32 Gpt_NotifyCountType, uint32 Gpt_TargetTime);

/*******************************************************************************
*                      Function Definitions                                   **
*******************************************************************************/
/*******************************************************************************
** Function Name         : main_PE1
**
** Description           : Sample application of GPT instance 1.
**
** Note                  : Following API need exclusive control between multi
**                         core for avoid resource access conflicting.
**                         - Gpt_Init()
**                         - Gpt_DeInit()
**                         - Gpt_StartTimer()
**                         - Gpt_StopTimer()
**                         When the application call above APIs, please
**                         take care resource access conflicting between
**                         multi core.
*******************************************************************************/
int main_PE1(void)
{
  /* Call sequence on core 1 variant 1 */
  Gpt_sequence_variant1(GPT_NOTI_COUNT_CONTINOUS, GPT_TARGET_VALUE_MAX16BIT);

  /* Call sequence on core 1 variant 2 */
  Gpt_sequence_variant1(GPT_NOTI_COUNT_ONESHOT, GPT_TARGET_VALUE_RANDOM);

  /* End trap */
  while(1)
  {
    /* This Sample application was completed */
  };
} /* End of main() function */

void Gpt_sequence_variant1(uint32 Gpt_NotifyCountType, uint32 Gpt_TargetTime)
{
  /* Enable Interrupt */
  ENABLE_INTERRUPT();

  /* Wait until Master core is done Initialization */
  while(0U == GblSyncFlag);

  #if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)
  /* Enabling the Notification */
  Gpt_EnableNotification(Gpt_GptChannelConfiguration3);
  Gpt_EnableNotification(Gpt_GptChannelConfiguration4);
  Gpt_EnableNotification(Gpt_GptChannelConfiguration5);
  #if (STD_ON == GPT_TIMER_IP_ATU || STD_ON == GPT_TIMER_IP_GTM)
  Gpt_EnableNotification(Gpt_GptChannelConfiguration7);
  #endif
  #if (GPT_TIMER_IP_TAUJ == STD_ON && STD_ON == GPT_TIMER_IP_ATU)
  Gpt_EnableNotification(Gpt_GptChannelConfiguration8);
  Gpt_EnableNotification(Gpt_GptChannelConfiguration9);
  #endif
  #endif

  /* Starting the Timer */
  Gpt_StartTimer(Gpt_GptChannelConfiguration3, Gpt_TargetTime);
  Gpt_StartTimer(Gpt_GptChannelConfiguration4, Gpt_TargetTime);
  Gpt_StartTimer(Gpt_GptChannelConfiguration5, Gpt_TargetTime);
  #if (STD_ON == GPT_TIMER_IP_ATU || STD_ON == GPT_TIMER_IP_GTM)
  Gpt_StartTimer(Gpt_GptChannelConfiguration7, Gpt_TargetTime);
  #endif
   #if (GPT_TIMER_IP_TAUJ == STD_ON && STD_ON == GPT_TIMER_IP_ATU)
  Gpt_StartTimer(Gpt_GptChannelConfiguration8, Gpt_TargetTime);
  Gpt_StartTimer(Gpt_GptChannelConfiguration9, Gpt_TargetTime);
  #endif

  #if (GPT_TIME_REMAINING_API == STD_ON)
  /* Reading the time elapsed */
  Test_Value_Elapsed3_Core1 = Gpt_GetTimeElapsed(Gpt_GptChannelConfiguration3);
  Test_Value_Elapsed4_Core1 = Gpt_GetTimeElapsed(Gpt_GptChannelConfiguration4);
  Test_Value_Elapsed5_Core1 = Gpt_GetTimeElapsed(Gpt_GptChannelConfiguration5);
  #if (STD_ON == GPT_TIMER_IP_ATU || STD_ON == GPT_TIMER_IP_GTM)
  Test_Value_Elapsed7_Core1 = Gpt_GetTimeElapsed(Gpt_GptChannelConfiguration7);
  #endif
  #if (GPT_TIMER_IP_TAUJ == STD_ON && STD_ON == GPT_TIMER_IP_ATU)
  Test_Value_Elapsed8_Core1 = Gpt_GetTimeElapsed(Gpt_GptChannelConfiguration8);
  Test_Value_Elapsed9_Core1 = Gpt_GetTimeElapsed(Gpt_GptChannelConfiguration9);
  #endif
  #endif


  #if (GPT_TIME_ELAPSED_API == STD_ON)
  /* Reading the time remaining */
  Test_Value_Remain3_Core1 = Gpt_GetTimeRemaining(Gpt_GptChannelConfiguration3);
  Test_Value_Remain4_Core1 = Gpt_GetTimeRemaining(Gpt_GptChannelConfiguration4);
  Test_Value_Remain5_Core1 = Gpt_GetTimeRemaining(Gpt_GptChannelConfiguration5);
  #if (STD_ON == GPT_TIMER_IP_ATU || STD_ON == GPT_TIMER_IP_GTM)
  Test_Value_Remain7_Core1 = Gpt_GetTimeRemaining(Gpt_GptChannelConfiguration7);
  #endif
  #if (GPT_TIMER_IP_TAUJ == STD_ON && STD_ON == GPT_TIMER_IP_ATU)
  Test_Value_Remain8_Core1 = Gpt_GetTimeRemaining(Gpt_GptChannelConfiguration8);
  Test_Value_Remain9_Core1 = Gpt_GetTimeRemaining(Gpt_GptChannelConfiguration9);
  #endif
  #endif

  /* Waiting Notification */
  while (GaaNotificationEntered_global[3] < Gpt_NotifyCountType);
  while (GaaNotificationEntered_Core1[4] < Gpt_NotifyCountType);
  while (GaaNotificationEntered_global[5] < Gpt_NotifyCountType);
  #if (STD_ON == GPT_TIMER_IP_ATU || STD_ON == GPT_TIMER_IP_GTM)
  while (GaaNotificationEntered_global[7] < Gpt_NotifyCountType);
  #endif
  #if (GPT_TIMER_IP_TAUJ == STD_ON && STD_ON == GPT_TIMER_IP_ATU)
  while (GaaNotificationEntered_global[8] < Gpt_NotifyCountType);
  while (GaaNotificationEntered_Core1[9] < Gpt_NotifyCountType);
  #endif

  #if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)
  /* Disabling the Notification */
  Gpt_DisableNotification(Gpt_GptChannelConfiguration3);
  Gpt_DisableNotification(Gpt_GptChannelConfiguration4);
  Gpt_DisableNotification(Gpt_GptChannelConfiguration5);
  #if (STD_ON == GPT_TIMER_IP_ATU || STD_ON == GPT_TIMER_IP_GTM)
  Gpt_DisableNotification(Gpt_GptChannelConfiguration7);
  #endif
  #if (GPT_TIMER_IP_TAUJ == STD_ON && STD_ON == GPT_TIMER_IP_ATU)
  Gpt_DisableNotification(Gpt_GptChannelConfiguration8);
  Gpt_DisableNotification(Gpt_GptChannelConfiguration9);
  #endif
  #endif /* (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON) */

  /* Stopping the Timer */
  Gpt_StopTimer(Gpt_GptChannelConfiguration3);
  Gpt_StopTimer(Gpt_GptChannelConfiguration4);
  #if (GPT_TIMER_IP_TAUJ == STD_ON && STD_ON == GPT_TIMER_IP_ATU)
  Gpt_StopTimer(Gpt_GptChannelConfiguration8);
  Gpt_StopTimer(Gpt_GptChannelConfiguration9);
  #endif

  /* Reset the notification in all channels */
  for (LulCount = GPT_ZERO; LulCount < GPT_TOTAL_CHANNELS_CONFIG; LulCount++)
  {
    GaaNotificationEntered_Core1[LulCount] = 0;

    GaaNotificationEntered_global[LulCount] = 0;
  }

  /* Notify the other core that core 1 has been finished */
  GblSyncFlag = 0;

}/* End of main() function */


/*******************************************************************************
** Function Name         : Gpt_Notification_2
**
** Description           : Notification function Channel Configuration of 2.
*******************************************************************************/
void Gpt_Notification_4_Variant_1(void)
{
  /* Notification for channel */
  GaaNotificationEntered_Core1[4]++;
}

void Gpt_Notification_4_Variant_2(void)
{
  /* Notification for channel */
  GaaNotificationEntered_Core1[4]++;
}

#if (GPT_TIMER_IP_TAUJ == STD_ON && STD_ON == GPT_TIMER_IP_ATU)
void Gpt_Notification_9_Variant_1(void)
{
  /* Notification for channel */
  GaaNotificationEntered_Core1[9]++;
}

void Gpt_Notification_9_Variant_2(void)
{
  /* Notification for channel */
  GaaNotificationEntered_Core1[9]++;
}
#endif
/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
