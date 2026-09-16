/*============================================================================*/
/* Project      = RH850 X2x MCAL Ver22.01.00.D                                */
/* Module       = App_GPT_Common_Multicore_PostBuildVariant_Sample_0.c        */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2024, 2025 Renesas Electronics Corporation. All rights reserved.       */
/*============================================================================*/
/* Purpose:                                                                   */
/* This file contains sample application multi core of Core 0 for GPT Driver  */
/* Component                                                                  */
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
/*
 *  2.4.0  30/06/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.01.00 (D) release
 *  2.3.2  25/04/2025  : As part of GTM HWIP support for U2Ax, following changes
 *                       are made:
 *                       1. Update Check PredefTimer for common devices
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
**                      Instance Index                                        **
*******************************************************************************/
//#define GPT_INSTANCE_INDEX    0
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "App_GPT_Common_Sample_0.h"
#include "App_Gpt_Multi_Sample.h"
#include "App_GPT_Device_Sample.h"
#include "Gpt.h"
#include "Gpt_PBTypes.h"
#include "Gpt_Ram.h"
/*******************************************************************************
**                            Macros                                          **
*******************************************************************************/

/*******************************************************************************
**                        Global variables                                    **
*******************************************************************************/
/* Global variable to hold the values of GPT */
volatile uint8  GaaNotificationEntered_Core0[10];
uint8  GaaTestResult[100];
uint16 LulCount;
uint16 GulCheckpoint = GPT_ZERO;
uint32 Gpt_PredefTimerValue;
Std_ReturnType CheckReturnValue;

#if (GPT_TIME_ELAPSED_API == STD_ON)
Gpt_ValueType Test_Value_Elapsed0_Core0;
Gpt_ValueType Test_Value_Elapsed1_Core0;
Gpt_ValueType Test_Value_Elapsed2_Core0;
Gpt_ValueType Test_Value_Elapsed3_Core0;
Gpt_ValueType Test_Value_Elapsed4_Core0;
Gpt_ValueType Test_Value_Elapsed5_Core0;
Gpt_ValueType Test_Value_Elapsed6_Core0;
Gpt_ValueType Test_Value_Elapsed7_Core0;
Gpt_ValueType Test_Value_Elapsed8_Core0;
#endif
#if (GPT_TIME_REMAINING_API == STD_ON)
Gpt_ValueType Test_Value_Remain0_Core0;
Gpt_ValueType Test_Value_Remain1_Core0;
Gpt_ValueType Test_Value_Remain2_Core0;
Gpt_ValueType Test_Value_Remain3_Core0;
Gpt_ValueType Test_Value_Remain4_Core0;
Gpt_ValueType Test_Value_Remain5_Core0;
Gpt_ValueType Test_Value_Remain6_Core0;
Gpt_ValueType Test_Value_Remain7_Core0;
Gpt_ValueType Test_Value_Remain8_Core0;
#endif

#if ((GPT_REPORT_WAKEUP_SOURCE == STD_ON) && (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON))
/* Index to access data of core */
uint8 LucAccPointIdx;
/* Pointer to the channel configuration */
P2CONST(Gpt_ChannelConfigType, AUTOMATIC, GPT_CONFIG_DATA) LpChannel;
#endif

/*******************************************************************************
**                        User function prototypes                            **
*******************************************************************************/
/* Function prototype variant support */
void Gpt_sequence(const Gpt_ConfigType * Gpt_Config, uint32 Gpt_NotifyCountType, uint32 Gpt_TargetTime);
/*******************************************************************************
*                      Function Definitions                                   **
*******************************************************************************/

/*******************************************************************************
** Function Name         : main
**
** Description           : Sample application of GPT instance 0.
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
int main(void)
{
  /* Local Variable for GPT sample application */
  Std_VersionInfoType Lddversioninfo;
  Std_ReturnType LddInitCheckValue;

  #if (GPT_VERSION_INFO_API == STD_ON)
  /* Getting the version Info of the GPT Driver */
  Gpt_GetVersionInfo(&Lddversioninfo);
  #endif /* (GPT_VERSION_INFO_API == STD_ON) */

  /* Checking version information */
  if((GPT_VENDOR_ID == Lddversioninfo.vendorID) &&
    (GPT_MODULE_ID == Lddversioninfo.moduleID) &&
    (GPT_SW_MAJOR_VERSION == Lddversioninfo.sw_major_version) &&
    (GPT_SW_MINOR_VERSION == Lddversioninfo.sw_minor_version) &&
    (GPT_SW_PATCH_VERSION == Lddversioninfo.sw_patch_version))
  {
    /* Enable Interrupt */
    ENABLE_INTERRUPT();

    /* Initialize function of both core */
    LddInitCheckValue = Init_MCAL();
    
    if (E_OK == LddInitCheckValue)
    {
    /* Call sample app sequence with configuration from variant 1 */
      Gpt_sequence(Gpt_Config_Variant_1, GPT_NOTI_COUNT_CONTINOUS, GPT_TARGET_VALUE_MAX16BIT);

      /* Call sample app sequence with configuration from variant 2 */
      Gpt_sequence(Gpt_Config_Variant_2, GPT_NOTI_COUNT_ONESHOT, GPT_TARGET_VALUE_RANDOM);

      /* Return OK */
      while (1);
    }
    else
    {
      /* Initialize function of both core is failure */
      while (1);
    }
  }
  else
  {
    /* Version check is failure */
    while (1);
  }
} /* End of main() function */

void Gpt_sequence(const Gpt_ConfigType * Gpt_Config, uint32 Gpt_NotifyCountType, uint32 Gpt_TargetTime)
{   
  Gpt_Init(Gpt_Config);

  #if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)
  /* Enabling the Notification */
  Gpt_EnableNotification(Gpt_GptChannelConfiguration0);
  Gpt_EnableNotification(Gpt_GptChannelConfiguration1);
  Gpt_EnableNotification(Gpt_GptChannelConfiguration2);
  Gpt_EnableNotification(Gpt_GptChannelConfiguration3);
  Gpt_EnableNotification(Gpt_GptChannelConfiguration5);
  #if (STD_ON == GPT_TIMER_IP_ATU || STD_ON == GPT_TIMER_IP_GTM)
  Gpt_EnableNotification(Gpt_GptChannelConfiguration6);
  Gpt_EnableNotification(Gpt_GptChannelConfiguration7);
  #endif
  #if (GPT_TIMER_IP_TAUJ == STD_ON && STD_ON == GPT_TIMER_IP_ATU)
  Gpt_EnableNotification(Gpt_GptChannelConfiguration8);
  #endif
  #endif /* (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON) */

  /* Starting the Timer */
  Gpt_StartTimer(Gpt_GptChannelConfiguration0, Gpt_TargetTime);
  Gpt_StartTimer(Gpt_GptChannelConfiguration1, Gpt_TargetTime);
  Gpt_StartTimer(Gpt_GptChannelConfiguration2, Gpt_TargetTime);
  Gpt_StartTimer(Gpt_GptChannelConfiguration3, Gpt_TargetTime);
  Gpt_StartTimer(Gpt_GptChannelConfiguration5, Gpt_TargetTime);
  #if (STD_ON == GPT_TIMER_IP_ATU || STD_ON == GPT_TIMER_IP_GTM)
  Gpt_StartTimer(Gpt_GptChannelConfiguration6, Gpt_TargetTime);
  Gpt_StartTimer(Gpt_GptChannelConfiguration7, Gpt_TargetTime);
  #endif
  #if (GPT_TIMER_IP_TAUJ == STD_ON && STD_ON == GPT_TIMER_IP_ATU)
  Gpt_StartTimer(Gpt_GptChannelConfiguration8, Gpt_TargetTime);
  #endif

  #if (GPT_TIME_REMAINING_API == STD_ON)
  /* Reading the time remaining */
  Test_Value_Remain0_Core0 = Gpt_GetTimeRemaining(Gpt_GptChannelConfiguration0);
  Test_Value_Remain1_Core0 = Gpt_GetTimeRemaining(Gpt_GptChannelConfiguration1);
  Test_Value_Remain2_Core0 = Gpt_GetTimeRemaining(Gpt_GptChannelConfiguration2);
  Test_Value_Remain3_Core0 = Gpt_GetTimeRemaining(Gpt_GptChannelConfiguration3);
  Test_Value_Remain5_Core0 = Gpt_GetTimeRemaining(Gpt_GptChannelConfiguration5);
  #if (STD_ON == GPT_TIMER_IP_ATU || STD_ON == GPT_TIMER_IP_GTM)
  Test_Value_Remain6_Core0 = Gpt_GetTimeRemaining(Gpt_GptChannelConfiguration6);
  Test_Value_Remain7_Core0 = Gpt_GetTimeRemaining(Gpt_GptChannelConfiguration7);
  #endif
  #if (GPT_TIMER_IP_TAUJ == STD_ON && STD_ON == GPT_TIMER_IP_ATU)
  Test_Value_Remain8_Core0 = Gpt_GetTimeRemaining(Gpt_GptChannelConfiguration8);
  #endif
  #endif /* (GPT_TIME_REMAINING_API == STD_ON) */

  #if (GPT_TIME_ELAPSED_API == STD_ON)
  /* Reading the time elapsed */
  Test_Value_Elapsed0_Core0 = Gpt_GetTimeElapsed(Gpt_GptChannelConfiguration0);
  Test_Value_Elapsed1_Core0 = Gpt_GetTimeElapsed(Gpt_GptChannelConfiguration1);
  Test_Value_Elapsed2_Core0 = Gpt_GetTimeElapsed(Gpt_GptChannelConfiguration2);
  Test_Value_Elapsed3_Core0 = Gpt_GetTimeElapsed(Gpt_GptChannelConfiguration3);
  Test_Value_Elapsed5_Core0 = Gpt_GetTimeElapsed(Gpt_GptChannelConfiguration5);
  #if (STD_ON == GPT_TIMER_IP_ATU || STD_ON == GPT_TIMER_IP_GTM)
  Test_Value_Elapsed6_Core0 = Gpt_GetTimeElapsed(Gpt_GptChannelConfiguration6);
  Test_Value_Elapsed7_Core0 = Gpt_GetTimeElapsed(Gpt_GptChannelConfiguration7);
  #endif
  #if (GPT_TIMER_IP_TAUJ == STD_ON && STD_ON == GPT_TIMER_IP_ATU)
  Test_Value_Elapsed8_Core0 = Gpt_GetTimeElapsed(Gpt_GptChannelConfiguration8);
  #endif
  #endif /* (GPT_TIME_ELAPSED_API == STD_ON) */

  /* Waiting Notification */
  while(GaaNotificationEntered_Core0[0] < Gpt_NotifyCountType);
  while(GaaNotificationEntered_Core0[1] < Gpt_NotifyCountType);
  while(GaaNotificationEntered_Core0[2] < Gpt_NotifyCountType);
  while(GaaNotificationEntered_global[3] < Gpt_NotifyCountType);
  while(GaaNotificationEntered_global[5] < Gpt_NotifyCountType);
  #if (STD_ON == GPT_TIMER_IP_ATU || STD_ON == GPT_TIMER_IP_GTM)
  while(GaaNotificationEntered_Core0[6] < Gpt_NotifyCountType);
  while(GaaNotificationEntered_global[7] < Gpt_NotifyCountType);
  #endif
  #if (GPT_TIMER_IP_TAUJ == STD_ON && STD_ON == GPT_TIMER_IP_ATU)
  while(GaaNotificationEntered_global[8] < Gpt_NotifyCountType);
  #endif

  #if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)
  /* Disabling the Notification */
  Gpt_DisableNotification(Gpt_GptChannelConfiguration0);
  Gpt_DisableNotification(Gpt_GptChannelConfiguration1);
  Gpt_DisableNotification(Gpt_GptChannelConfiguration2);
  Gpt_DisableNotification(Gpt_GptChannelConfiguration3);
  Gpt_DisableNotification(Gpt_GptChannelConfiguration5);
  #if (STD_ON == GPT_TIMER_IP_ATU || STD_ON == GPT_TIMER_IP_GTM)
  Gpt_DisableNotification(Gpt_GptChannelConfiguration6);
  Gpt_DisableNotification(Gpt_GptChannelConfiguration7);
  #endif
  #if (GPT_TIMER_IP_TAUJ == STD_ON && STD_ON == GPT_TIMER_IP_ATU)
  Gpt_DisableNotification(Gpt_GptChannelConfiguration8);
  #endif
  #endif /* (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON) */


  #if ((GPT_REPORT_WAKEUP_SOURCE == STD_ON) && (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON))
  LucAccPointIdx = (Gpt_GaaCoreId2Index[Gpt_GucKernelCoreId] & GPT_CORE_MASK);	
  #if (STD_OFF == GPT_TIMER_IP_ATU)
  /* Update pointer to wakeup channel */
  LpChannel = &(*(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pChannelConfig))[Gpt_GptChannelConfiguration4];
  #else
  LpChannel = &(*(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pChannelConfig))[Gpt_GptChannelConfiguration8];
  #endif
  /* Set mode to Sleep */
  Gpt_SetMode(GPT_MODE_SLEEP);

  #if (STD_OFF == GPT_TIMER_IP_ATU)
  /* Disabling the Wakeup Notification */
  Gpt_DisableWakeup(Gpt_GptChannelConfiguration4);
  #else
  /* Disabling the Wakeup Notification */
  Gpt_DisableWakeup(Gpt_GptChannelConfiguration8);
  #endif

  /* Set mode to Normal */
  Gpt_SetMode(GPT_MODE_NORMAL);

  #if (STD_OFF == GPT_TIMER_IP_ATU)
  /* Enabling the Wakeup Notification */
  Gpt_EnableWakeup(Gpt_GptChannelConfiguration4);
  /* Starting the Timer */
  Gpt_StartTimer(Gpt_GptChannelConfiguration4, Gpt_TargetTime);
  #else
  /* Enabling the Wakeup Notification */
  Gpt_EnableWakeup(Gpt_GptChannelConfiguration8);
  /* Starting the Timer */
  Gpt_StartTimer(Gpt_GptChannelConfiguration8, Gpt_TargetTime);
  #endif

  /* Set mode to Sleep */
  Gpt_SetMode(GPT_MODE_SLEEP);

  /* Delay to wait cbk notification */
  volatile  uint32 count;
  while (count < 8000) {
      count ++;
  };

  /* Checking the wake up notification */
  while(Gpt_GaaChannelRamData[(LpChannel->ucRamDataIndex)].blWakeupOccurrence == GPT_FALSE);
  Gpt_CheckWakeup(GPT_WKP_SRC_4);

  /* Set mode to Normal */
  Gpt_SetMode(GPT_MODE_NORMAL);
  #endif

  /* Stopping the Timer */
  Gpt_StopTimer(Gpt_GptChannelConfiguration0);
  Gpt_StopTimer(Gpt_GptChannelConfiguration1);
  Gpt_StopTimer(Gpt_GptChannelConfiguration2);
  Gpt_StopTimer(Gpt_GptChannelConfiguration3);
  Gpt_StopTimer(Gpt_GptChannelConfiguration5);
  #if (STD_ON == GPT_TIMER_IP_ATU || STD_ON == GPT_TIMER_IP_GTM)
  Gpt_StopTimer(Gpt_GptChannelConfiguration6);
  Gpt_StopTimer(Gpt_GptChannelConfiguration7);
  #endif

  #if(GPT_GET_PREDEF_TIMER_VALUE_API == STD_ON)
  /* U2Bx with ATU */
  #if ((STD_ON == GPT_TIMER_IP_ATU)\
  ||(((STD_ON == GPT_TIMER_IP_TAUJ)) && (STD_ON == GPT_TOM_UNIT_USED) && (STD_ON == GPT_ATOM_UNIT_USED))) /* U2BxE */
  /* Check PredefTimer */
  CheckReturnValue = Gpt_GetPredefTimerValue(GPT_PREDEF_TIMER_1US_32BIT, &Gpt_PredefTimerValue);
  if(CheckReturnValue == E_OK)
  {
    GaaTestResult[GulCheckpoint] = TRUE;
  }
  else
  {
    GaaTestResult[GulCheckpoint] = FALSE;
  }
  #elif ((STD_ON == GPT_TIMER_IP_TAUJ) && (STD_ON == GPT_TIMER_IP_GTM)) /* U2Cx and U2Ax */
  CheckReturnValue = Gpt_GetPredefTimerValue(GPT_PREDEF_TIMER_100US_32BIT, &Gpt_PredefTimerValue);
  if(CheckReturnValue == E_OK)
  {
    GaaTestResult[GulCheckpoint] = TRUE;
  }
  else
  {
    GaaTestResult[GulCheckpoint] = FALSE;
  }
  #else
  CheckReturnValue = Gpt_GetPredefTimerValue(GPT_PREDEF_TIMER_1US_16BIT, &Gpt_PredefTimerValue);
  if(CheckReturnValue == E_OK)
  {
    GaaTestResult[GulCheckpoint] = TRUE;
  }
  else
  {
    GaaTestResult[GulCheckpoint] = FALSE;
  }
  #endif
  GulCheckpoint++;
  #endif /* (GPT_GET_PREDEF_TIMER_VALUE_API == STD_ON) */

  /* Reset the notification in all channels */
  for (LulCount = GPT_ZERO; LulCount < GPT_TOTAL_CHANNELS_CONFIG; LulCount++)
  {
    GaaNotificationEntered_Core0[LulCount] = 0;

    GaaNotificationEntered_global[LulCount] = 0;
  }

  /* Notify the other core that startup and module initialization has been finished */
  GblSyncFlag = 1;

  /* Wait until core 1 main task is done with variant 1*/
  while(1U == GblSyncFlag);

  #if (GPT_DE_INIT_API == STD_ON)
  /* DeInitialization for GPT module */
  Gpt_DeInit();
  #endif /* (GPT_DE_INIT_API == STD_ON) */

} /* End of Gpt_sequence */

/*******************************************************************************
** Function Name         : Gpt_Notification_0
**
** Description           : Notification function Channel Configuration of 0.
*******************************************************************************/
void Gpt_Notification_0_Variant_1(void)
{
  /* Notification for channel 0 */
  GaaNotificationEntered_Core0[0]++;
}

void Gpt_Notification_0_Variant_2(void)
{
  /* Notification for channel 0 */
  GaaNotificationEntered_Core0[0]++;
}

void Gpt_Notification_1_Variant_1(void)
{
  /* Notification for channel 1 */
  GaaNotificationEntered_Core0[1]++;
}

void Gpt_Notification_1_Variant_2(void)
{
  /* Notification for channel 1 */
  GaaNotificationEntered_Core0[1]++;
}

void Gpt_Notification_2_Variant_1(void)
{
  /* Notification for channel 2 */
  GaaNotificationEntered_Core0[2]++;
}

void Gpt_Notification_2_Variant_2(void)
{
  /* Notification for channel 2 */
  GaaNotificationEntered_Core0[2]++;
}

void Gpt_Notification_3(void)
{
  /* Notification for channel 3 */
  GaaNotificationEntered_global[3]++;
}

void Gpt_Notification_5_Variant_1(void)
{
  /* Notification for channel */
  GaaNotificationEntered_global[5]++;
}

void Gpt_Notification_5_Variant_2(void)
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

void Gpt_Notification_6(void)
{
  /* Notification for channel 1 */
  GaaNotificationEntered_Core0[6]++;
}
#endif

#if (GPT_TIMER_IP_TAUJ == STD_ON && STD_ON == GPT_TIMER_IP_ATU)
void Gpt_Notification_8(void)
{
  /* Notification for channel 1 */
  GaaNotificationEntered_global[8]++;
}
#endif

/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
