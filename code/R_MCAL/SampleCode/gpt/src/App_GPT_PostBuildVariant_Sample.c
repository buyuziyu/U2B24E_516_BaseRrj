/*============================================================================*/
/* Project      = RH850 X2x MCAL Ver22.01.00.D                                */
/* Module       = App_GPT_Common_Sample.c                                     */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2024, 2025 Renesas Electronics Corporation. All rights reserved.       */
/*============================================================================*/
/* Purpose:                                                                   */
/* This file contains sample application for GPT Driver Component             */
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
 *  2.3.1  31/03/2025  : Add GblSampleAppStatus variable and condition with PE6
 *                       Add calling Guard_Init() function when running on PE6
 *  2.3.0  28/02/2025  : Update SW-VERSION for
 *                       RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 *  2.2.0  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D
 *                       Final Release
 *  2.1.2  31/10/2024  : As part of GTM HWIP support, following changes are made
 *                       1.Add macro to support GTM
 *  2.1.1  22/08/2024  : As part of U2Ax support, following changes are made
 *                       1.Add macro to support U2Ax
 *  2.0.3  10/04/2024  : Initial Version
 */
/******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "App_GPT_Common_Sample.h"
#include "Std_Types.h"
#include "Gpt.h"
#include "App_GPT_Device_Sample.h"
#include "Gpt_PBTypes.h"
#include "Gpt_Ram.h"
/*******************************************************************************
**                            Macros                                          **
*******************************************************************************/

/*******************************************************************************
**                        Global variables                                    **
*******************************************************************************/

#if defined(RUN_OTHER_PE)
extern void Guard_Init(void);
Std_ReturnType GblSampleAppStatus = STD_OFF;
#endif

/* Variable used to store the Module Version Info */
Std_VersionInfoType versioninfo;

/* Global variables to hold version information */
uint16 VendorID;
uint16 ModuleID;
uint8  SW_Major_Version;
uint8  SW_Minor_Version;
uint8  SW_Patch_Version;
volatile uint16 GaaNotificationEntered[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
uint8  GaaTestResult[100];
uint16 GulCheckpoint = GPT_ZERO;
uint16 LulCount;

/* Global variable to hold the values of GPT */
#if (GPT_TIME_ELAPSED_API == STD_ON)
Gpt_ValueType Test_Value_Elapsed0;
Gpt_ValueType Test_Value_Elapsed1;
Gpt_ValueType Test_Value_Elapsed2;
Gpt_ValueType Test_Value_Elapsed3;
Gpt_ValueType Test_Value_Elapsed4;
Gpt_ValueType Test_Value_Elapsed5;
Gpt_ValueType Test_Value_Elapsed6;
Gpt_ValueType Test_Value_Elapsed7;
Gpt_ValueType Test_Value_Elapsed8;
Gpt_ValueType Test_Value_Elapsed9;
#endif
#if (GPT_TIME_REMAINING_API == STD_ON)
Gpt_ValueType Test_Value_Remain0;
Gpt_ValueType Test_Value_Remain1;
Gpt_ValueType Test_Value_Remain2;
Gpt_ValueType Test_Value_Remain3;
Gpt_ValueType Test_Value_Remain4;
Gpt_ValueType Test_Value_Remain5;
Gpt_ValueType Test_Value_Remain6;
Gpt_ValueType Test_Value_Remain7;
Gpt_ValueType Test_Value_Remain8;
Gpt_ValueType Test_Value_Remain9;
#endif

/* Global variable to hold the values of PreDef timer */
#if (GPT_GET_PREDEF_TIMER_VALUE_API == STD_ON)
Gpt_ValueType Gpt_PredefTimerValue;
Std_ReturnType CheckReturnValue;
#endif

/*******************************************************************************
**                        User function prototypes                            **
*******************************************************************************/
extern void Port_Init(void);
extern void Clock_Init(void);
extern void Mcu_Init(void);
extern void Wdg_Init(void);
extern void Reg_Init(void);

/* Function prototype variant support */
void Gpt_sequence(const Gpt_ConfigType * Gpt_Config, uint32 Gpt_NotifyCountType, uint32 Gpt_TargetTime);
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
void sample_end(void)
{
  while(1)
  {
    /* No action required */
  }
}

int main(void)
#if defined (RUN_OTHER_PE)
{
  Guard_Init();
  /* Report core 0 completing init */
  GblSampleAppStatus = STD_ON;
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
  #if defined(RUN_OTHER_PE)
  /* Waiting core 0 completing init */
  while(GblSampleAppStatus == STD_OFF);
  #endif

  /* Initialize Clock */
  Clock_Init();

  /* Initialize MCU */
  Mcu_Init();

  /* Initialize the Port pins */
  Port_Init();

  /* Initialization of the table reference bit in ICR register */
  Reg_Init();

  /* Initialize the Watchdog timer */
  Wdg_Init();

  ENABLE_INTERRUPT();

  #if (GPT_VERSION_INFO_API == STD_ON)
  /* Getting the version Info of the GPT Driver */
  Gpt_GetVersionInfo(&versioninfo);
  VendorID = versioninfo.vendorID;
  ModuleID = versioninfo.moduleID;
  #endif /* (GPT_VERSION_INFO_API == STD_ON) */

  SW_Major_Version = versioninfo.sw_major_version;
  SW_Minor_Version = versioninfo.sw_minor_version;
  SW_Patch_Version = versioninfo.sw_patch_version;

  /* Call sample app sequence with configuration from from variant 1*/
  Gpt_sequence(Gpt_Config_Variant_1, GPT_NOTI_COUNT_CONTINOUS, GPT_TARGET_VALUE_MAX16BIT);

  /* Call sample app sequence with configuration from from variant 2*/
  Gpt_sequence(Gpt_Config_Variant_2, GPT_NOTI_COUNT_ONESHOT, GPT_TARGET_VALUE_RANDOM);

  /* Return OK */
  return E_OK;
}

void Gpt_sequence(const Gpt_ConfigType * Gpt_Config, uint32 Gpt_NotifyCountType, uint32 Gpt_TargetTime)
{
  /* Initialization of the GPT Driver */
  Gpt_Init(Gpt_Config);

  /* Check if any notification is raised */
  for (LulCount = GPT_ZERO; LulCount < GPT_TOTAL_CHANNELS_CONFIG; LulCount++)
  {
    if(GPT_ZERO == GaaNotificationEntered[LulCount])
    {
      GaaTestResult[GulCheckpoint] = TRUE;
    }
    else
    {
      GaaTestResult[GulCheckpoint] = FALSE;
    }
    GulCheckpoint++;
  }

  #if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON )
  /* Enabling the Notification */
  Gpt_EnableNotification(Gpt_GptChannelConfiguration0);
  Gpt_EnableNotification(Gpt_GptChannelConfiguration1);
  Gpt_EnableNotification(Gpt_GptChannelConfiguration2);
  Gpt_EnableNotification(Gpt_GptChannelConfiguration3);
  Gpt_EnableNotification(Gpt_GptChannelConfiguration4);
  Gpt_EnableNotification(Gpt_GptChannelConfiguration5);
  #if (STD_ON == GPT_TIMER_IP_ATU || STD_ON == GPT_TIMER_IP_GTM)
  Gpt_EnableNotification(Gpt_GptChannelConfiguration6);
  Gpt_EnableNotification(Gpt_GptChannelConfiguration7);
  #endif
  #if (GPT_TIMER_IP_TAUJ == STD_ON && STD_ON == GPT_TIMER_IP_ATU)
  Gpt_EnableNotification(Gpt_GptChannelConfiguration8);
  Gpt_EnableNotification(Gpt_GptChannelConfiguration9);
  #endif
  #endif /* (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON) */

  /* Starting the Timer */
  Gpt_StartTimer(Gpt_GptChannelConfiguration0, Gpt_TargetTime);
  Gpt_StartTimer(Gpt_GptChannelConfiguration1, Gpt_TargetTime);
  Gpt_StartTimer(Gpt_GptChannelConfiguration2, Gpt_TargetTime);
  Gpt_StartTimer(Gpt_GptChannelConfiguration3, Gpt_TargetTime);
  Gpt_StartTimer(Gpt_GptChannelConfiguration4, Gpt_TargetTime);
  Gpt_StartTimer(Gpt_GptChannelConfiguration5, Gpt_TargetTime);
  #if (STD_ON == GPT_TIMER_IP_ATU || STD_ON == GPT_TIMER_IP_GTM)
  Gpt_StartTimer(Gpt_GptChannelConfiguration6, Gpt_TargetTime);
  Gpt_StartTimer(Gpt_GptChannelConfiguration7, Gpt_TargetTime);
  #endif
  #if (GPT_TIMER_IP_TAUJ == STD_ON && STD_ON == GPT_TIMER_IP_ATU)
  Gpt_StartTimer(Gpt_GptChannelConfiguration8, Gpt_TargetTime);
  Gpt_StartTimer(Gpt_GptChannelConfiguration9, Gpt_TargetTime);
  #endif

  #if (GPT_TIME_ELAPSED_API == STD_ON)
  /* Reading the time elapsed */
  Test_Value_Elapsed0 = Gpt_GetTimeElapsed(Gpt_GptChannelConfiguration0);
  Test_Value_Elapsed1 = Gpt_GetTimeElapsed(Gpt_GptChannelConfiguration1);
  Test_Value_Elapsed2 = Gpt_GetTimeElapsed(Gpt_GptChannelConfiguration2);
  Test_Value_Elapsed3 = Gpt_GetTimeElapsed(Gpt_GptChannelConfiguration3);
  Test_Value_Elapsed4 = Gpt_GetTimeElapsed(Gpt_GptChannelConfiguration4);
  Test_Value_Elapsed5 = Gpt_GetTimeElapsed(Gpt_GptChannelConfiguration5);
  #if (STD_ON == GPT_TIMER_IP_ATU || STD_ON == GPT_TIMER_IP_GTM)
  Test_Value_Elapsed6 = Gpt_GetTimeElapsed(Gpt_GptChannelConfiguration6);
  Test_Value_Elapsed7 = Gpt_GetTimeElapsed(Gpt_GptChannelConfiguration7);
  #endif
  #if (GPT_TIMER_IP_TAUJ == STD_ON && STD_ON == GPT_TIMER_IP_ATU)
  Test_Value_Elapsed8 = Gpt_GetTimeElapsed(Gpt_GptChannelConfiguration8);
  Test_Value_Elapsed9 = Gpt_GetTimeElapsed(Gpt_GptChannelConfiguration9);
  #endif
  #endif /* (GPT_TIME_ELAPSED_API == STD_ON) */

  #if (GPT_TIME_REMAINING_API == STD_ON)
  /* Reading the time remaining */
  Test_Value_Remain0 = Gpt_GetTimeRemaining(Gpt_GptChannelConfiguration0);
  Test_Value_Remain1 = Gpt_GetTimeRemaining(Gpt_GptChannelConfiguration1);
  Test_Value_Remain2 = Gpt_GetTimeRemaining(Gpt_GptChannelConfiguration2);
  Test_Value_Remain3 = Gpt_GetTimeRemaining(Gpt_GptChannelConfiguration3);
  Test_Value_Remain4 = Gpt_GetTimeRemaining(Gpt_GptChannelConfiguration4);
  Test_Value_Remain5 = Gpt_GetTimeRemaining(Gpt_GptChannelConfiguration5);
  #if (STD_ON == GPT_TIMER_IP_ATU || STD_ON == GPT_TIMER_IP_GTM)
  Test_Value_Remain6 = Gpt_GetTimeRemaining(Gpt_GptChannelConfiguration6);
  Test_Value_Remain7 = Gpt_GetTimeRemaining(Gpt_GptChannelConfiguration7);
  #endif
  #if (GPT_TIMER_IP_TAUJ == STD_ON && STD_ON == GPT_TIMER_IP_ATU)
  Test_Value_Remain8 = Gpt_GetTimeRemaining(Gpt_GptChannelConfiguration8);
  Test_Value_Remain9 = Gpt_GetTimeRemaining(Gpt_GptChannelConfiguration9);
  #endif
  #endif /* (GPT_TIME_REMAINING_API == STD_ON) */

  /* Delay to wait cbk notification */
  volatile  uint32 count;
  while (count < 8000) {
    count ++;
  };

  /* Wait until Notification occurs for the channel */

  while((GaaNotificationEntered[0] < Gpt_NotifyCountType) ||
        (GaaNotificationEntered[1] < Gpt_NotifyCountType) ||
        (GaaNotificationEntered[2] < Gpt_NotifyCountType) ||
        (GaaNotificationEntered[3] < Gpt_NotifyCountType));
  while(GaaNotificationEntered[4] < Gpt_NotifyCountType);
  while(GaaNotificationEntered[5] < Gpt_NotifyCountType);
  #if (STD_ON == GPT_TIMER_IP_ATU || STD_ON == GPT_TIMER_IP_GTM)
  while(GaaNotificationEntered[6] < Gpt_NotifyCountType);
  while(GaaNotificationEntered[7] < Gpt_NotifyCountType);
  #endif
  #if (GPT_TIMER_IP_TAUJ == STD_ON && STD_ON == GPT_TIMER_IP_ATU)
  while((GaaNotificationEntered[8] < Gpt_NotifyCountType));
  while((GaaNotificationEntered[9] < Gpt_NotifyCountType));
  #endif

  /* Check if notification is raised */
  for (LulCount = GPT_ZERO; LulCount < GPT_TOTAL_CHANNELS_CONFIG; LulCount++)
  {
    if(GPT_ZERO < GaaNotificationEntered[LulCount])
    {
      GaaTestResult[GulCheckpoint] = TRUE;
    }
    else
    {
      GaaTestResult[GulCheckpoint] = FALSE;
    }
    GulCheckpoint++;
  }

  #if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)
  /* Disabling the Notification */
  Gpt_DisableNotification(Gpt_GptChannelConfiguration0);
  Gpt_DisableNotification(Gpt_GptChannelConfiguration1);
  Gpt_DisableNotification(Gpt_GptChannelConfiguration2);
  Gpt_DisableNotification(Gpt_GptChannelConfiguration3);
  Gpt_DisableNotification(Gpt_GptChannelConfiguration4);
  Gpt_DisableNotification(Gpt_GptChannelConfiguration5);
  #if (STD_ON == GPT_TIMER_IP_ATU || STD_ON == GPT_TIMER_IP_GTM)
  Gpt_DisableNotification(Gpt_GptChannelConfiguration6);
  Gpt_DisableNotification(Gpt_GptChannelConfiguration7);
  #endif
  #if (GPT_TIMER_IP_TAUJ == STD_ON && STD_ON == GPT_TIMER_IP_ATU)
  Gpt_DisableNotification(Gpt_GptChannelConfiguration8);
  Gpt_DisableNotification(Gpt_GptChannelConfiguration9);
  #endif
  #endif /* (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON) */

  #if (GPT_REPORT_WAKEUP_SOURCE == STD_ON)
  #if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)

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
  while (count < 8000) {
      count ++;
  };

  /* Checking the wake up notification */
  Gpt_CheckWakeup(GPT_WKP_SRC_4);
  #if (STD_OFF == GPT_TIMER_IP_ATU)
  while(Gpt_GaaChannelRamData[Gpt_GptChannelConfiguration4].blWakeupOccurrence == GPT_FALSE);
  if(GPT_TRUE == Gpt_GaaChannelRamData[Gpt_GptChannelConfiguration4].blWakeupOccurrence)
  {
    GaaTestResult[GulCheckpoint] = TRUE;
  }
  else
  {
    GaaTestResult[GulCheckpoint] = FALSE;
  }
  #else
  while(Gpt_GaaChannelRamData[Gpt_GptChannelConfiguration8].blWakeupOccurrence == GPT_FALSE);
  if(GPT_TRUE == Gpt_GaaChannelRamData[Gpt_GptChannelConfiguration8].blWakeupOccurrence)
  {
    GaaTestResult[GulCheckpoint] = TRUE;
  }
  else
  {
    GaaTestResult[GulCheckpoint] = FALSE;
  }
  #endif
  GulCheckpoint++;

  /* Set mode to Normal */
  Gpt_SetMode(GPT_MODE_NORMAL);
  #endif
  #endif

  /* Stopping the Timer */
  Gpt_StopTimer(Gpt_GptChannelConfiguration0);
  Gpt_StopTimer(Gpt_GptChannelConfiguration1);
  Gpt_StopTimer(Gpt_GptChannelConfiguration2);
  Gpt_StopTimer(Gpt_GptChannelConfiguration3);
  Gpt_StopTimer(Gpt_GptChannelConfiguration4);
  Gpt_StopTimer(Gpt_GptChannelConfiguration5);
  #if (STD_ON == GPT_TIMER_IP_ATU || STD_ON == GPT_TIMER_IP_GTM)
  Gpt_StopTimer(Gpt_GptChannelConfiguration6);
  Gpt_StopTimer(Gpt_GptChannelConfiguration7);
  #endif
  #if (GPT_TIMER_IP_TAUJ == STD_ON && STD_ON == GPT_TIMER_IP_ATU)
  Gpt_StopTimer(Gpt_GptChannelConfiguration8);
  Gpt_StopTimer(Gpt_GptChannelConfiguration9);
  #endif

  #if (GPT_GET_PREDEF_TIMER_VALUE_API == STD_ON)
  /* U2Bx with ATU */
  #if ((STD_ON == GPT_TIMER_IP_ATU)\
     ||(((STD_ON == GPT_TIMER_IP_TAUJ)) && (STD_ON == GPT_TOM_UNIT_USED) && (STD_ON == GPT_ATOM_UNIT_USED))) /* U2BxE */
  /* Check PredefTimer */
  CheckReturnValue = Gpt_GetPredefTimerValue(GPT_PREDEF_TIMER_1US_32BIT, &Gpt_PredefTimerValue);
  if(E_OK == CheckReturnValue)
  {
    GaaTestResult[GulCheckpoint] = TRUE;
  }
  else
  {
    GaaTestResult[GulCheckpoint] = FALSE;
  }
  #elif ((STD_ON == GPT_TIMER_IP_TAUJ) && (STD_ON == GPT_TIMER_IP_GTM)) /* U2Cx and U2Ax */
  /* Check PredefTimer */
  CheckReturnValue = Gpt_GetPredefTimerValue(GPT_PREDEF_TIMER_100US_32BIT, &Gpt_PredefTimerValue);
  if(E_OK == CheckReturnValue)
  {
    GaaTestResult[GulCheckpoint] = TRUE;
  }
  else
  {
    GaaTestResult[GulCheckpoint] = FALSE;
  }
  #else /* U2Bx with GTM */
  CheckReturnValue = Gpt_GetPredefTimerValue(GPT_PREDEF_TIMER_1US_16BIT, &Gpt_PredefTimerValue);
  if(E_OK == CheckReturnValue)
  {
    GaaTestResult[GulCheckpoint] = TRUE;
  }
  else
  {
    GaaTestResult[GulCheckpoint] = FALSE;
  }
  #endif
  #endif /* (GPT_GET_PREDEF_TIMER_VALUE_API == STD_ON) */
  GulCheckpoint++;

  #if (GPT_DE_INIT_API == STD_ON)
  /* De-initialize GPT Driver */
  Gpt_DeInit();
  #endif /* (GPT_DE_INIT_API == STD_ON) */

  /* Reset the notification in all channels */
  for (LulCount = GPT_ZERO; LulCount < GPT_TOTAL_CHANNELS_CONFIG; LulCount++)
  {
    GaaNotificationEntered[LulCount] = 0;
  }

}/* End of Gpt_sequence function */

/*******************************************************************************
**                         Notification function                              **
*******************************************************************************/
void Gpt_Notification_0_Variant_1(void)
{
  /* Notification for channel */
  GaaNotificationEntered[0]++;
}

void Gpt_Notification_0_Variant_2(void)
{
  /* Notification for channel */
  GaaNotificationEntered[0]++;
}

void Gpt_Notification_1_Variant_1(void)
{
  /* Notification for channel */
  GaaNotificationEntered[1]++;
}

void Gpt_Notification_1_Variant_2(void)
{
  /* Notification for channel */
  GaaNotificationEntered[1]++;
}

void Gpt_Notification_2_Variant_1(void)
{
  /* Notification for channel */
  GaaNotificationEntered[2]++;
}

void Gpt_Notification_2_Variant_2(void)
{
  /* Notification for channel */
  GaaNotificationEntered[2]++;
}

void Gpt_Notification_3(void)
{
  /* Notification for channel */
  GaaNotificationEntered[3]++;
}

void Gpt_Notification_4(void)
{
  /* Notification for channel */
  GaaNotificationEntered[4]++;
}

void Gpt_Notification_5(void)
{
  /* Notification for channel */
  GaaNotificationEntered[5]++;
}

#if (STD_ON == GPT_TIMER_IP_ATU || STD_ON == GPT_TIMER_IP_GTM)
void Gpt_Notification_6(void)
{
  /* Notification for channel */
  GaaNotificationEntered[6]++;
}

void Gpt_Notification_7(void)
{
  /* Notification for channel */
  GaaNotificationEntered[7]++;
}
#endif

#if (GPT_TIMER_IP_TAUJ == STD_ON && STD_ON == GPT_TIMER_IP_ATU)
void Gpt_Notification_8(void)
{
  /* Notification for channel */
  GaaNotificationEntered[8]++;
}
void Gpt_Notification_9(void)
{
  /* Notification for channel */
  GaaNotificationEntered[9]++;
}
#endif

/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
