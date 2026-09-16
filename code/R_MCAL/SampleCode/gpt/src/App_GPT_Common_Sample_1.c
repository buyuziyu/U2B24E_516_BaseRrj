/*============================================================================*/
/* Project      = RH850 X2x MCAL Ver22.01.00.D                                */
/* Module       = App_GPT_Common_Sample_1.c                                   */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2020,2022-2025 Renesas Electronics Corporation. All rights reserved.   */
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
 *  2.1.1  30/08/2024  : As part of U2Ax support, following changes are made
 *                       1.Add macro to support U2Ax
 *                     : As part of U2Bx-E support, following changes are made
 *                       1.Update sequence for U2BxE
 *                     : As part of Post Build multiple varriant support,
 *                       following changes are made
 *                       1.Replace GPT_SYNC_ process to GblSyncFlag
 *                     : As part of U2Cx support, following changes are made
 *                       1.Correct the channel using for GPT_DEVICE_U2CX
 *  2.0.1  18/01/2024  : Update purpose section of copyright
 *  2.0.0  26/07/2023  : Remove multi-instance, update with new configuration
 *         12/05/2023  : Update SW version 2.0.0
 *  1.4.5  12/02/2023  : Add EIBD section for U2Bx
 *  1.2.1  27/01/2022  : Place barrier synchronization after Gpt_Deinit
 *  1.2.0  17/07/2020  : Release
 *  1.1.0  19/06/2020  : Release
 *  1.0.0  01/01/2020  : Initial Version
 */
/******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "App_GPT_Common_Sample_1.h"
#include "App_Gpt_Multi_Sample.h"
#include "App_GPT_Device_Sample.h"
#include "Gpt.h"
/*******************************************************************************
**                            Macros                                          **
*******************************************************************************/

/*******************************************************************************
**                        Global variables                                    **
*******************************************************************************/

/* Global variable to hold the values of GPT */
volatile uint8 GaaNotificationEntered_Core1[10];

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
  uint32 Notify_Count_Continuous = 0x0F;
  uint32 Notify_Count_One_Shot = 0x01;

  #if (STD_ON == GPT_TIMER_IP_OSTM)
  EIBD841_U2Bx |= BOUND_PE1;    /* OSTM2 */
  #endif

   /* Enable Interrupt */
  ENABLE_INTERRUPT();

  /* Wait until Master core is done Initialization */
  while(0U == GblSyncFlag);

  Gpt_Init(Gpt_Config);

  #if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)
  /* Enabling the Notification */
  Gpt_EnableNotification(Gpt_GptChannelConfiguration2);
  Gpt_EnableNotification(Gpt_GptChannelConfiguration3);
  Gpt_EnableNotification(Gpt_GptChannelConfiguration4);
  Gpt_EnableNotification(Gpt_GptChannelConfiguration5);
  #if (STD_ON == GPT_TIMER_IP_ATU || STD_ON == GPT_TIMER_IP_GTM)
  Gpt_EnableNotification(Gpt_GptChannelConfiguration7);
  #endif
  #if (GPT_TIMER_IP_TAUJ == STD_ON && STD_ON == GPT_TIMER_IP_ATU)
  Gpt_EnableNotification(Gpt_GptChannelConfiguration9);
  #endif
  #endif

  /* Starting the Timer */
  Gpt_StartTimer(Gpt_GptChannelConfiguration2, GPT_TARGET_VALUE_2);
  Gpt_StartTimer(Gpt_GptChannelConfiguration4, GPT_TARGET_VALUE_4);
  Gpt_StartTimer(Gpt_GptChannelConfiguration5, GPT_TARGET_VALUE_5);
  #if (STD_ON == GPT_TIMER_IP_ATU || STD_ON == GPT_TIMER_IP_GTM)
  Gpt_StartTimer(Gpt_GptChannelConfiguration7, GPT_TARGET_VALUE_7);
  #endif
  #if (GPT_TIMER_IP_TAUJ == STD_ON && STD_ON == GPT_TIMER_IP_ATU)
  Gpt_StartTimer(Gpt_GptChannelConfiguration9, GPT_TARGET_VALUE_9);
  #endif

  #if (GPT_TIME_ELAPSED_API == STD_ON)
  /* Reading the time elapsed */
  Test_Value_Elapsed2_Core1 = Gpt_GetTimeElapsed(Gpt_GptChannelConfiguration2);
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

  #if (GPT_TIME_REMAINING_API == STD_ON)
  /* Reading the time remaining */
  Test_Value_Remain2_Core1 = Gpt_GetTimeRemaining(Gpt_GptChannelConfiguration2);
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
  while (GaaNotificationEntered_Core1[2] < Notify_Count_Continuous);
  while (GaaNotificationEntered_global[3] < Notify_Count_Continuous);
  while (GaaNotificationEntered_Core1[4] < Notify_Count_One_Shot);
  while (GaaNotificationEntered_global[5] < Notify_Count_Continuous);
  #if (STD_ON == GPT_TIMER_IP_ATU || STD_ON == GPT_TIMER_IP_GTM)
  while (GaaNotificationEntered_global[7] < Notify_Count_One_Shot);
  #endif
  #if (GPT_TIMER_IP_TAUJ == STD_ON && STD_ON == GPT_TIMER_IP_ATU)
  while (GaaNotificationEntered_global[8] < Notify_Count_Continuous);
  while (GaaNotificationEntered_Core1[9] < Notify_Count_Continuous);
  #endif

  /* Notify core 0 as a task done with checking the notification*/
  GblSyncFlag = 0;

  #if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)
  /* Disabling the Notification */
  Gpt_DisableNotification(Gpt_GptChannelConfiguration2);
  Gpt_DisableNotification(Gpt_GptChannelConfiguration3);
  Gpt_DisableNotification(Gpt_GptChannelConfiguration4);
  #if (STD_ON == GPT_TIMER_IP_ATU || STD_ON == GPT_TIMER_IP_GTM)
  Gpt_DisableNotification(Gpt_GptChannelConfiguration7);
  #endif
  #if (GPT_TIMER_IP_TAUJ == STD_ON && STD_ON == GPT_TIMER_IP_ATU)
  Gpt_DisableNotification(Gpt_GptChannelConfiguration8);
  Gpt_DisableNotification(Gpt_GptChannelConfiguration9);
  #endif
  #endif /* (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON) */

  /* Stopping the Timer */
  Gpt_StopTimer(Gpt_GptChannelConfiguration2);
  Gpt_StopTimer(Gpt_GptChannelConfiguration4);
  Gpt_StopTimer(Gpt_GptChannelConfiguration5);
  #if (GPT_TIMER_IP_TAUJ == STD_ON && STD_ON == GPT_TIMER_IP_ATU)
  Gpt_StopTimer(Gpt_GptChannelConfiguration8);
  Gpt_StopTimer(Gpt_GptChannelConfiguration9);
  #endif

  #if (GPT_DE_INIT_API == STD_ON)
  /* DeInitialization for GPT module */
  Gpt_DeInit();
  #endif /* (GPT_DE_INIT_API == STD_ON) */

  /* Notify core 0 as a task done from core 1 */
  GblSyncFlag = 1;

  /* Return OK */
  while (1);

}/* End of main() function */


/*******************************************************************************
** Function Name         : Gpt_Notification_2
**
** Description           : Notification function Channel Configuration of 2.
*******************************************************************************/
void Gpt_Notification_2(void)
{
  /* Notification for channel 1 */
  GaaNotificationEntered_Core1[2]++;
}
void Gpt_Notification_4(void)
{
  /* Notification for channel */
  GaaNotificationEntered_Core1[4]++;
}

void Gpt_Notification_5(void)
{
  /* Notification for channel */
  GaaNotificationEntered_global[5]++;
}

#if (STD_ON == GPT_TIMER_IP_ATU || STD_ON == GPT_TIMER_IP_GTM)
void Gpt_Notification_7(void)
{
  /* Notification for channel */
  GaaNotificationEntered_global[7]++;
}
#endif

#if (GPT_TIMER_IP_TAUJ == STD_ON && STD_ON == GPT_TIMER_IP_ATU)
void Gpt_Notification_9(void)
{
  /* Notification for channel */
  GaaNotificationEntered_Core1[9]++;
}
#endif
/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
