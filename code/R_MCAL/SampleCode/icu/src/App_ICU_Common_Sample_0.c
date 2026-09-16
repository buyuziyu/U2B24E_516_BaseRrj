/*============================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                         */
/* Module       = App_ICU_Common_Sample_0.c                                   */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.        */
/*============================================================================*/
/* Purpose:                                                                   */
/* This file contains sample application for ICU Driver Component             */
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
 * 2.4.1:  30/06/2025  : Remove SW-VERSION in file headers
 * 2.4.0:  30/05/2025  : Remove prinft, improve volatile variable
 * 2.3.1:  31/03/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 
 *                       and RH850/U2Bx-E MCAL Ver22.00.02 Release
 * 2.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL
 *                       Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D 
 *                       Final Release
 * 2.1.2:  31/10/2024  : As part of support GTM HWIP into common sample app, 
 *                       following changes are made:
 *                       1. Update sample app for support GTM HWIP
 * 2.0.1:  28/10/2023  : Correct typo OCU to ICU
 *         25/10/2023  : Update SW-VERSION to 2.0.1
 * 2.0.0:  03/07/2022  : Re-write test app to support ICU Multi-core
 * 1.4.3:  18/04/2022  : Remove Caxi fuction, add api Icu_GetInputState 
 *                       Icu_GetInputLevel Icu_GetTAUInCountValue
 *         15/04/2022  : Update prefix from LucCount to LulCount
 * 1.3.1:  06/05/2021  : Update Sync flag after invoke Icu_GetDutyCycleValues
 * 1.2.0:  17/07/2020  : Release
 * 1.1.0:  19/06/2020  : Release
 * 1.0.0:  25/03/2020  : Initial Version
 */
/******************************************************************************/

/*******************************************************************************
**                     Include Section                                        **
*******************************************************************************/
#include "App_ICU_Common_Sample_0.h"
#include "App_ICU_Multi_Sample.h"
/*******************************************************************************
**                            Macros                                          **
*******************************************************************************/
#define TS_NOTIFY_INTERVAL    5   /* Time Stamps Notify Interval value */
#define TS_BUFFER_SIZE        10  /* Time Stamps buffer size */
/*******************************************************************************
**                        Global variables                                    **
*******************************************************************************/
/* Global variable to store the test result */
uint8 GaaTestResult_PE0[50];
uint16 GulCheckpoint_PE0 = 0;
volatile boolean GblFlagFinalResult_PE0 = TRUE;
/* Global variable to hold the timestamp capture status */
volatile boolean GblTimestampsCaptured;
uint16 GblTimestampIndex[1];
boolean GblBreakLoop_PE0 = ICU_FALSE;
/*******************************************************************************
**                        User function prototypes                            **
*******************************************************************************/
void task1(void);
void task2(void);
extern void Big_Delay(void);
/*******************************************************************************
*                      Function Definitions                                   **
*******************************************************************************/

/*******************************************************************************
** Function Name         : main
**
** Description           : Sample application of ICU Core 0.
** A continuous signal of 1 milli-second with 50% duty cycle and Vref
** should be given at input for all testing channel.
*******************************************************************************/

int main(void)
{
  /* Open register access permission for all CPU */
  Guard_Enable_PE();
  /* Initialize MCU */
  Mcu_Init();
  /* Initialize the Port pins */
  Port_Init();
  /* Initialize the Watchdog timer */
  Wdg_Init();
  /* Initialization of the table reference bit in ICR register */
  Reg_Init();
  /* Enable interrupt for PE0 */
  ENABLE_INTERRUPT();
  /* Initialization of the ICU Driver */
  Icu_Init(Icu_Config);

  /* Notify the other instance that startup and module initialization have been finished */
  GblSyncFlag = 1;

  /* Invoke OSTM timer, the OSTM counter duration is 1ms */
  App_Icu_Start_Timer0();

  /* Invoke task 2 */
  task2();

  /* Wait until core 1 is done execution with task3 */
  while(1U == GblSyncFlag);

  /* Deinit the Icu module */
  Icu_DeInit();

  /* Loop through all checkpoints and set value to result flag */
  for (uint8 count = 0; count < GulCheckpoint_PE0 ; count++)
  {
    if (FALSE == GaaTestResult_PE0[count])
    {
      GblFlagFinalResult_PE0 = FALSE;
      break;
    }
  }

  while(1)
  {
    /* This Sample application was completed */
  };

}
/* End of main() function */

/*******************************************************************************
**                         Example task functions                             **
*******************************************************************************/
/* Task1, kernel API */
void task1(void)
{
  /* For example invoke all ICU kernel services at 1 task */
  Icu_Kernel_StartTimestamp();
  Icu_Kernel_StopTimestamp();
  Icu_Kernel_ResetEdgeCount();
  Icu_Kernel_EnableEdgeCount();
  Icu_Kernel_DisableEdgeCount();
  Icu_Kernel_EnableEdgeDetection();
  Icu_Kernel_DisableEdgeDetection();
  Icu_Kernel_StartSignalMeasurement();
  Icu_Kernel_StopSignalMeasurement();
  Icu_Kernel_SetActivationCondition();
}

/* Task2, service API on core 0 */
void task2(void) 
{
  /* Local Variable for measurement */
  Std_VersionInfoType versionInfo_PE0;
  Icu_DutyCycleType GddDutyCycleValues[7];
  Icu_ValueType GddTimeElapsed[7];
  /* Array used to store the timestamps */
  Icu_ValueType GusTimestamp[ICU_TIMESTAMP_MAX];
  volatile uint32 GulTauInCountValue[3];
  Icu_InputStateType GblInputStatus[2];

  /* To get the version of the ICU Driver module */
  Icu_GetVersionInfo(&versionInfo_PE0);
  if ((ICU_VENDOR_ID == versionInfo_PE0.vendorID) &&
     (ICU_MODULE_ID == versionInfo_PE0.moduleID) &&
     (ICU_SW_MAJOR_VERSION == versionInfo_PE0.sw_major_version) &&
     (ICU_SW_MINOR_VERSION == versionInfo_PE0.sw_minor_version) &&
     (ICU_SW_PATCH_VERSION == versionInfo_PE0.sw_patch_version))
  {
    GaaTestResult_PE0[GulCheckpoint_PE0] = TRUE;
    GulCheckpoint_PE0++;
  }
  else
  {
    GaaTestResult_PE0[GulCheckpoint_PE0] = FALSE;
    GulCheckpoint_PE0++;
  }
/*******************************************************************************
**                         SIGNAL MEASUREMENT SECTION                         **
*******************************************************************************/
  #if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)
  /* Signal measurement: != Duty cycle */
  /* Loop for all configured channel to find the target channel */
  for(uint8 channel = 0; channel < ICU_MAX_CHANNEL; channel++)
  {
    if((Icu_GpChannelConfig[channel].ucIcuMeasurementMode == ICU_MODE_SIGNAL_MEASUREMENT) &&
      (ICU_DUTY_PERIOD_ENABLED_MASK !=
      (Icu_GpChannelUserRegConfig[channel].ucChannelProperties & ICU_DUTY_PERIOD_ENABLED_MASK)))
    {
      /* Start Signal Measurement for channel */
      Icu_StartSignalMeasurement(channel);
      while (CheckSlaveRequest(channel, ICU_START_SIGNAL_MEASUREMENT_SID));
      /* Read Elapsed Time for channel */
      GddTimeElapsed[0] = Icu_GetTimeElapsed(channel);
      /* Call Big Delay */
      Big_Delay();
      /* Read Elapsed Time for channel */
      GddTimeElapsed[1] = Icu_GetTimeElapsed(channel);
      /* Read Elapsed Time for channel */
      GddTimeElapsed[2] = Icu_GetTimeElapsed(channel);
      /* Call Big Delay */
      Big_Delay();
      /* Read Elapsed Time for channel */
      GddTimeElapsed[3] = Icu_GetTimeElapsed(channel);
      /* Call Big Delay */
      Big_Delay();
      /* Read Elapsed Time for channel */
      GddTimeElapsed[4] = Icu_GetTimeElapsed(channel);
      /* Call Big Delay */
      Big_Delay();
      /* Read Elapsed Time for channel */
      GddTimeElapsed[5] = Icu_GetTimeElapsed(channel);
      /* Stop Signal Measurement for channel */
      Icu_StopSignalMeasurement(channel);
      while (CheckSlaveRequest(channel, ICU_STOP_SIGNAL_MEASUREMENT_SID));
      /* Read Elapsed Time for channel */
      GddTimeElapsed[6] = Icu_GetTimeElapsed(channel);
      /* Verify the output */
      if((GddTimeElapsed[0]==0)&&(GddTimeElapsed[1]!=0)&&(GddTimeElapsed[2]==0)&&
         (GddTimeElapsed[3]!=0)&&(GddTimeElapsed[4]!=0)&&(GddTimeElapsed[5]!=0))
      {
        GaaTestResult_PE0[GulCheckpoint_PE0] = TRUE;
        GulCheckpoint_PE0++;
      }
      else
      {
        GaaTestResult_PE0[GulCheckpoint_PE0] = FALSE;
        GulCheckpoint_PE0++;
      }
    }
  }

  /* Signal measurement: Duty cycle */
  /* Loop for all configured channel to find the target duty cycle channel */
  for(uint8 channel = 0; channel < ICU_MAX_CHANNEL; channel++)
  {
    /* Check if the channel is configured as duty cycle */
    if((Icu_GpChannelConfig[channel].ucIcuMeasurementMode == ICU_MODE_SIGNAL_MEASUREMENT) &&
      (Icu_GpChannelUserRegConfig[channel].ucChannelProperties == 6))
    {
      /* Start Signal Measurement for channel */
      Icu_StartSignalMeasurement(channel);
      /* Wait until master core process the request */
      while (CheckSlaveRequest(channel, ICU_START_SIGNAL_MEASUREMENT_SID));
      /* Read DutyCycle for channel */
      Icu_GetDutyCycleValues(channel, &GddDutyCycleValues[0]);
      /* Call Big Delay */
      Big_Delay();
      /* Signal DutyCycle has been captured */
      Icu_GetDutyCycleValues(channel, &GddDutyCycleValues[1]);
      Icu_GetDutyCycleValues(channel, &GddDutyCycleValues[2]);
      /* Call Big Delay */
      Big_Delay();
      /* Signal DutyCycle has been captured */
      Icu_GetDutyCycleValues(channel, &GddDutyCycleValues[3]);
      /* Call Big Delay */
      Big_Delay();
      /* Signal DutyCycle has been captured */
      Icu_GetDutyCycleValues(channel, &GddDutyCycleValues[4]);
      /* Call Big Delay */
      Big_Delay();
      /* Signal DutyCycle has been captured */
      Icu_GetDutyCycleValues(channel, &GddDutyCycleValues[5]);
      /* Stop Signal Measurement for channel */
      Icu_StopSignalMeasurement(channel);
      /* Wait until master core process the request */
      while (CheckSlaveRequest(channel, ICU_STOP_SIGNAL_MEASUREMENT_SID));
      /* Call Big Delay */
      Big_Delay();
      /* Signal DutyCycle has been captured */
      Icu_GetDutyCycleValues(channel, &GddDutyCycleValues[6]);

      /* Verify the output */
      if((GddDutyCycleValues[0].ActiveTime==0) && (GddDutyCycleValues[0].PeriodTime==0) &&
         (GddDutyCycleValues[1].ActiveTime!=0) && (GddDutyCycleValues[1].PeriodTime!=0) &&
         (GddDutyCycleValues[2].ActiveTime==0) && (GddDutyCycleValues[2].PeriodTime==0) &&
         (GddDutyCycleValues[3].ActiveTime!=0) && (GddDutyCycleValues[3].PeriodTime!=0) &&
         (GddDutyCycleValues[4].ActiveTime!=0) && (GddDutyCycleValues[4].PeriodTime!=0) &&
         (GddDutyCycleValues[5].ActiveTime!=0) && (GddDutyCycleValues[5].PeriodTime!=0))
      {
        GaaTestResult_PE0[GulCheckpoint_PE0] = TRUE;
        GulCheckpoint_PE0++;
      }
      else
      {
        GaaTestResult_PE0[GulCheckpoint_PE0] = FALSE;
        GulCheckpoint_PE0++;
      }

      /* To check the input state of a channel configured for signal measurement mode */
      /* Start Signal measurement for channel */
      Icu_StartSignalMeasurement(channel);
      /* Wait until master core process the request */
      while(CheckSlaveRequest(channel, ICU_START_SIGNAL_MEASUREMENT_SID));
      Big_Delay();
      /* Get the input stae of the channel */
      GblInputStatus[0] = Icu_GetInputState(channel);
      GblInputStatus[1] = Icu_GetInputState(channel);
      /* GblInputStatus[0] should be ICU_ACTIVE and GblInputStatus[1] should be ICU_IDLE */
      /* Verify the output */
      if((GblInputStatus[0] == ICU_ACTIVE) & (GblInputStatus[1] == ICU_IDLE))
      {
        GaaTestResult_PE0[GulCheckpoint_PE0] = TRUE;
        GulCheckpoint_PE0++;
      }
      else
      {
        GaaTestResult_PE0[GulCheckpoint_PE0] = FALSE;
        GulCheckpoint_PE0++;
      }
      /* Stop Signal Measurement for for channel */
      Icu_StopSignalMeasurement(channel);
      /* Wait until master core process the request */
      while(CheckSlaveRequest(channel, ICU_STOP_SIGNAL_MEASUREMENT_SID));
      GblInputStatus[0] = ICU_IDLE;
      GblInputStatus[1] = ICU_IDLE;
    }
  }
  #endif /* End of (ICU_SIGNAL_MEASUREMENT_API == STD_ON) */

/*******************************************************************************
**                            TIMESTAMP SECTION                               **
*******************************************************************************/
  #if (ICU_TIMESTAMP_API == STD_ON)
  /* Loop for all configured channel to find the target timestamp channel */
  for(uint8 channel = 0; channel < ICU_MAX_CHANNEL; channel++)
  {
    if(Icu_GpChannelConfig[channel].ucIcuMeasurementMode == ICU_MODE_TIMESTAMP)
    {
      /* Clear buffer data */
      memset(GusTimestamp, 0, ICU_TIMESTAMP_MAX);
      /* Reset the time stamp notification */
      GblTimestampsCaptured = ICU_FALSE;
      /* Set Activation condition for channel */
      Icu_SetActivationCondition(channel, ICU_RISING_EDGE);
      /* Wait until master core process the request */
      while (CheckSlaveRequest(channel, ICU_SET_ACTIVATION_CONDITION_SID));
      /* Enable notification for channel */
      Icu_EnableNotification(channel);
      /* Enable Timestamping for channel */
      Icu_StartTimestamp(channel, &GusTimestamp[0], ICU_TIMESTAMP_MAX, 5);
      /* Wait until master core process the request */
      while (CheckSlaveRequest(channel, ICU_START_TIMESTAMP_SID));
      do
      {
        /* Get the index of the buffer at which next timestamp value is to be written */
        GblTimestampIndex[0] = Icu_GetTimestampIndex(channel);
        /* Wait untill buffer reach index 8 */
        if (8 == GblTimestampIndex[0])
        {
          /* Icu_Time_Stamp_Test Success */
          GblBreakLoop_PE0 = ICU_TRUE;
        }
        #if (ICU_GET_TAU_COUNT_VALUE_API == STD_ON)
        if((Icu_GpChannelConfig[channel].ucIcuChannelType == ICU_HW_TAUD) ||
           (Icu_GpChannelConfig[channel].ucIcuChannelType == ICU_HW_TAUJ))
        {
          GulTauInCountValue[0] = Icu_GetTAUInCountValue(channel);
        }
        #endif
      }while(!GblBreakLoop_PE0);
      GblBreakLoop_PE0 = ICU_FALSE;

      /* Stop Timestamping for for channel */
      Icu_StopTimestamp(channel);
      /* Wait until master core process the request */
      while (CheckSlaveRequest(channel, ICU_STOP_TIMESTAMP_SID));
      /* Get the index of the buffer at which next timestamp value is to be written */
      GblTimestampIndex[0] = Icu_GetTimestampIndex(channel);

      /* Verify the output */
      if((GusTimestamp[0]!=0) && (GusTimestamp[1]!=0) && (GusTimestamp[2]!=0) && (GusTimestamp[3]!=0) &&
         (GusTimestamp[4]!=0) && (GusTimestamp[5]!=0) && (GusTimestamp[6]!=0) && (GusTimestamp[7]!=0) &&
         (GblTimestampsCaptured == ICU_TRUE))
      {
        GaaTestResult_PE0[GulCheckpoint_PE0] = TRUE;
        GulCheckpoint_PE0++;
      }
      else
      {
        GaaTestResult_PE0[GulCheckpoint_PE0] = FALSE;
        GulCheckpoint_PE0++;
      }
      #if (ICU_GET_TAU_COUNT_VALUE_API == STD_ON)
      if((Icu_GpChannelConfig[channel].ucIcuChannelType == ICU_HW_TAUD) ||
         (Icu_GpChannelConfig[channel].ucIcuChannelType == ICU_HW_TAUJ))
      {
        /* Verify the output */
        if(GulTauInCountValue[0] != 0)
        {
          GaaTestResult_PE0[GulCheckpoint_PE0] = TRUE;
          GulCheckpoint_PE0++;
        }
        else
        {
          GaaTestResult_PE0[GulCheckpoint_PE0] = FALSE;
          GulCheckpoint_PE0++;
        }
      }
      #endif
      /* Disable notification for channel */
      Icu_DisableNotification(channel);
      GblTimestampsCaptured = ICU_FALSE;
      /* Clear buffer data */
      memset(GusTimestamp, 0, ICU_TIMESTAMP_MAX);
      /* Enable Timestamping for channel */
      Icu_StartTimestamp(channel, &GusTimestamp[0], ICU_TIMESTAMP_MAX, 5);
      /* Wait until master core process the request */
      while (CheckSlaveRequest(channel, ICU_START_TIMESTAMP_SID));
      do
      {
        /* Get the index of the buffer at which next timestamp value is to be written */
        GblTimestampIndex[0] = Icu_GetTimestampIndex(channel);
        if (8 == GblTimestampIndex[0])
        {
          /* Icu_Time_Stamp_Test Success */
          GblBreakLoop_PE0 = ICU_TRUE;
        }
      }while(!GblBreakLoop_PE0);
      GblBreakLoop_PE0 = ICU_FALSE;

      /* Stop Timestamping for channel */
      Icu_StopTimestamp(channel);
      /* Wait until master core process the request */
      while (CheckSlaveRequest(channel, ICU_STOP_TIMESTAMP_SID));
      /* Get the index of the buffer at which next timestamp value is to be written */
      GblTimestampIndex[0] = Icu_GetTimestampIndex(channel);

      /* Verify the output */
      if((GusTimestamp[0]!=0) && (GusTimestamp[1]!=0) && (GusTimestamp[2]!=0) && (GusTimestamp[3]!=0) &&
         (GusTimestamp[4]!=0) && (GusTimestamp[5]!=0) && (GusTimestamp[6]!=0) && (GusTimestamp[7]!=0) &&
         (GblTimestampsCaptured == ICU_FALSE))
      {
        GaaTestResult_PE0[GulCheckpoint_PE0] = TRUE;
        GulCheckpoint_PE0++;
      }
      else
      {
        GaaTestResult_PE0[GulCheckpoint_PE0] = FALSE;
        GulCheckpoint_PE0++;
      }
    }
  }
  #endif /* End of (ICU_TIMESTAMP_API == STD_ON) */

/*******************************************************************************
**                            WAKEUP/SETMODE Section                          **
*******************************************************************************/
  #if (ICU_WAKEUP_FUNCTIONALITY_API == STD_ON)
  /* Wait until core 1 is done execution with task3 */
  while(1U == GblSyncFlag);
   /* Loop for all configured channel to find the target channel */
  for(uint8 channel = 0; channel < ICU_MAX_CHANNEL; channel++)
  {
    if((Icu_GpChannelConfig[channel].ucIcuWakeupCapability == ICU_TRUE) &&
       (Icu_GpChannelConfig[channel].ucIcuMeasurementMode == ICU_MODE_SIGNAL_EDGE_DETECT))
    {
      #if (ICU_ENABLE_WAKEUP_API == STD_ON)
      /* Enable wakeup */
      Icu_EnableWakeup(channel);
      #endif

      /* Enter Icu Sleep mode */
      #if (ICU_SET_MODE_API == STD_ON)
      /* Set Icu to sleep mode */
      Icu_SetMode(ICU_MODE_SLEEP);
      #endif

      /* Exit Icu Sleep mode */
      #if (ICU_SET_MODE_API == STD_ON)
      /* Set Icu to normal mode */
      Icu_SetMode(ICU_MODE_NORMAL);
      #endif

      #if (ICU_WAKEUP_FUNCTIONALITY_API == STD_ON)
      /* To verify and notify the wakeup source to the EcuM */
      Icu_CheckWakeup(Icu_GpChannelConfig[channel].ucEcuMChannelWakeupInfo);
      #endif

      #if (ICU_DISABLE_WAKEUP_API == STD_ON)
      /* Disable wakeup for channel */
      Icu_DisableWakeup(channel);
      #endif
      break;
    }
  }
  #endif
}
/******************************************************************************
**                       Timer Interrupt routine                             **
******************************************************************************/
_INTERRUPT_ void Timer0_Interrupt(void)
{
  /* Invoke task 1 every 1 ms */
  task1();
}

void Icu_TimeStamps_Notification(void)
{
  /* Set flag to true to inform that the 5 timestamps have been captured */
  GblTimestampsCaptured = TRUE;
}

/* Notification function for signal measurement channel */
void Icu_Signal_Overflow_Notification(void)
{
  /* Signal measurement counter overflow */
}
/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
