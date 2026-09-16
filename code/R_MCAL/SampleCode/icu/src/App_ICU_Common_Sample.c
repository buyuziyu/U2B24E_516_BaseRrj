/**********************************************************************************************************************/
/* Project      = RH850/X2x MCAL PF Development                                                                       */
/* Module       = ICU Driver                                                                                          */
/**********************************************************************************************************************/
/*                                                     COPYRIGHT                                                      */
/**********************************************************************************************************************/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/**********************************************************************************************************************/
/* Purpose:                                                                                                           */
/* This file contains sample application for ICU Driver Component                                                     */
/*                                                                                                                    */
/**********************************************************************************************************************/
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
/**********************************************************************************************************************/
/* Environment:                                                                                                       */
/*              Devices:        X2x                                                                                   */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                             Revision Control History                                               **
***********************************************************************************************************************/
/*
 * 2.4.1:  30/06/2025  : Remove SW-VERSION in file header
 * 2.4.0:  30/05/2025  : Remove prinft, improve volatile variable
 * 2.3.1:  31/03/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 
 *                       and RH850/U2Bx-E MCAL Ver22.00.02 Releases
 *                       As part of support U2Bx-E SampleApp on G4KH, following changes are made:
 *                       1. Add function Guard_Enable_PE, Big_Delay
 * 2.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 * 2.1.2:  31/10/2024  : As part of support GTM HWIP into common sample app,  following changes are made:
 *                       1.Update sample app for support GTM HWIP
 * 2.0.1:  25/10/2023  : Update SW-VERSION to 2.0.1
 * 1.4.3:  13/09/2022  : Remove redundant enable ISR for IRQ/INTP
 * 1.4.3:  15/04/2022  : Update prefix from TAUInCountValue to GulTauInCountValue
 * 1.4.1:  18/10/2021  : Update channel 006, 007 and set Reference Table Method for U2Bx
 * 1.2.0:  17/07/2020  : Release
 * 1.1.0:  19/06/2020  : Release
 * 1.0.0:  25/03/2020  : Initial Version
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                 Include Section                                                    **
***********************************************************************************************************************/
#include "Icu.h"
#include "Icu_Ram.h"
#include "Icu_PBTypes.h"
#include "Icu_LLDriver.h"
#include "App_Icu_Common_Sample.h"
#include "App_ICU_Device_Sample.h"
#include "Std_Types.h"
/*******************************************************************************
**                            Macros                                          **
*******************************************************************************/


/*******************************************************************************
**                        Global variables                                    **
*******************************************************************************/

/* Array used to store the timestamps */
Icu_ValueType GusTimestamp[ICU_TIMESTAMP_MAX];
/* Variable used to store the Module Version Info */
Std_VersionInfoType GddVersionInfo;
/* Global variable to hold the timestamp capture status */
volatile boolean GblTimestampsCaptured;
boolean GblBreakLoop;
Icu_InputStateType GblInputStatus[2];
Icu_LevelType GblInputPinLevel[1];
Icu_ValueType GddTimeElapsed[7];
Icu_DutyCycleType GddDutyCycleValues[7];
uint16 GblTimestampIndex[1];
volatile uint16 GusEdgeNumbers;
volatile uint32 GulTauInCountValue[3];
Icu_EdgeNumberType GblEdgeNumberCh[1];
/* Global variable to store the test result */
uint8 GaaTestResult[50];
uint16 GulCheckpoint = 0;
volatile boolean GblFlagFinalResult = TRUE;
/*******************************************************************************
**                        User function prototypes                            **
*******************************************************************************/
void Wdg_Init(void);
void Mcu_Init(void);
void Port_Init(void);
void Big_Delay(void);
void Reg_Init(void);
int Icu_Edge_Count_Test(uint8 testType);
int Icu_Edge_Detect_Test(boolean detectEnable);

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
/*******************************************************************************
** Function Name         : main
**
** Description           : Sample application of ICU Core 0.
** A continuous signal of 1 milli-second with 50% duty cycle and Vref
** should be given at input for all testing channel.
*******************************************************************************/

int main(void)
#if defined (RUN_OTHER_PE)
{
  Guard_Enable_PE();
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
  int ret = 0;

  /* Wait amout of time */
  Big_Delay();

  /* Initialize MCU */
  Mcu_Init();

  /* Initialize PORT */
  Port_Init();

  /* Initialize WDG */
  Wdg_Init();

  /* Initialization of the table reference bit in ICR register */
  Reg_Init();

  #if (ICU_GET_VERSION_INFO_API == STD_ON)
  /* Read the ICU Driver version information */
  Icu_GetVersionInfo(&GddVersionInfo);
  if ((ICU_VENDOR_ID == GddVersionInfo.vendorID) &&
    (ICU_MODULE_ID == GddVersionInfo.moduleID) &&
    (ICU_SW_MAJOR_VERSION == GddVersionInfo.sw_major_version) &&
    (ICU_SW_MINOR_VERSION == GddVersionInfo.sw_minor_version) &&
    (ICU_SW_PATCH_VERSION == GddVersionInfo.sw_patch_version))
  {
    GaaTestResult[GulCheckpoint] = TRUE;
    GulCheckpoint++;
  }
  else
  {
    GaaTestResult[GulCheckpoint] = FALSE;
    GulCheckpoint++;
  }
  #endif
  /* Call Big Delay */
  Big_Delay();
  /*
  * Initialize ICU Driver. A valid database address needs to
  * be provided for the proper initialization of the driver.
  */
  Icu_Init(Icu_Config);
  GblBreakLoop = ICU_FALSE;

  /* Enable Global Interrupt */
  ENABLE_INTERRUPT();

  /*****************************************************************************
  ********************** TIME STAMPING FUNCTIONALITY ***************************
  *****************************************************************************/
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
      /* Enable notification for channel */
      Icu_EnableNotification(channel);
      /* Enable Timestamping for channel */
      Icu_StartTimestamp(channel, &GusTimestamp[0], ICU_TIMESTAMP_MAX, 5);
      do
      {
        /* Get the index of the buffer at which next timestamp value is to be written */
        GblTimestampIndex[0] = Icu_GetTimestampIndex(channel);
        /* Wait untill buffer reach index 8 */
        if (8 == GblTimestampIndex[0])
        {
          /* Icu_Time_Stamp_Test Success */
          GblBreakLoop = ICU_TRUE;
        }
        #if (ICU_GET_TAU_COUNT_VALUE_API == STD_ON)
        if((Icu_GpChannelConfig[channel].ucIcuChannelType == ICU_HW_TAUD) ||
           (Icu_GpChannelConfig[channel].ucIcuChannelType == ICU_HW_TAUJ))
        {
          GulTauInCountValue[0] = Icu_GetTAUInCountValue(channel);
        }
        #endif
      }while(!GblBreakLoop);
      GblBreakLoop = ICU_FALSE;

      /* Stop Timestamping for for channel */
      Icu_StopTimestamp(channel);

      /* Get the index of the buffer at which next timestamp value is to be written */
      GblTimestampIndex[0] = Icu_GetTimestampIndex(channel);

      /* Verify the output */
      if((GusTimestamp[0]!=0) && (GusTimestamp[1]!=0) && (GusTimestamp[2]!=0) && (GusTimestamp[3]!=0) &&
        (GusTimestamp[4]!=0) && (GusTimestamp[5]!=0) && (GusTimestamp[6]!=0) && (GusTimestamp[7]!=0) &&
        (GblTimestampsCaptured == ICU_TRUE) && (GblTimestampIndex[0] != 0))
      {
        GaaTestResult[GulCheckpoint] = TRUE;
        GulCheckpoint++;
      }
      else
      {
        GaaTestResult[GulCheckpoint] = FALSE;
        GulCheckpoint++;
      }
      #if (ICU_GET_TAU_COUNT_VALUE_API == STD_ON)
      if((Icu_GpChannelConfig[channel].ucIcuChannelType == ICU_HW_TAUD) ||
         (Icu_GpChannelConfig[channel].ucIcuChannelType == ICU_HW_TAUJ))
      {
        /* Verify the output */
        if(GulTauInCountValue[0] != 0)
        {
          GaaTestResult[GulCheckpoint] = TRUE;
          GulCheckpoint++;
        }
        else
        {
          GaaTestResult[GulCheckpoint] = FALSE;
          GulCheckpoint++;
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
      do
      {
        /* Get the index of the buffer at which next timestamp value is to be written */
        GblTimestampIndex[0] = Icu_GetTimestampIndex(channel);
        if (8 == GblTimestampIndex[0])
        {
          /* Icu_Time_Stamp_Test Success */
          GblBreakLoop = ICU_TRUE;
        }
      }while(!GblBreakLoop);
      GblBreakLoop = ICU_FALSE;

      /* Stop Timestamping for channel */
      Icu_StopTimestamp(channel);
      /* Get the index of the buffer at which next timestamp value is to be written */
      GblTimestampIndex[0] = Icu_GetTimestampIndex(channel);

      /* Verify the output */
      if((GusTimestamp[0]!=0) && (GusTimestamp[1]!=0) && (GusTimestamp[2]!=0) && (GusTimestamp[3]!=0) &&
        (GusTimestamp[4]!=0) && (GusTimestamp[5]!=0) && (GusTimestamp[6]!=0) && (GusTimestamp[7]!=0) &&
        (GblTimestampsCaptured == ICU_FALSE) && (GblTimestampIndex[0] != 0))
      {
        GaaTestResult[GulCheckpoint] = TRUE;
        GulCheckpoint++;
      }
      else
      {
        GaaTestResult[GulCheckpoint] = FALSE;
        GulCheckpoint++;
      }
    }
  }
  #endif /* End of (ICU_TIMESTAMP_API == STD_ON) */

  /*****************************************************************************
  ********************** EDGE COUNTING FUNCTIONALITY ***************************
  *****************************************************************************/
  #if (ICU_EDGE_COUNT_API == STD_ON)
  /* Loop for all configured channel to find the target channel */
  for(uint8 channel = 0; channel < ICU_MAX_CHANNEL; channel++)
  {
    if(Icu_GpChannelConfig[channel].ucIcuMeasurementMode == ICU_MODE_EDGE_COUNTER)
    {
      /* Set Rising Edge Activation condition for channel */
      Icu_SetActivationCondition(channel, ICU_RISING_EDGE);
      /* Enable Edge Counting for channel */
      Icu_EnableEdgeCount(channel);
      /* Read Edge count for channel */
      do
      {
        /* Get the number of edges counted channel */
        GblEdgeNumberCh[0] = Icu_GetEdgeNumbers(channel);
        ret = Icu_Edge_Count_Test(ICU_EDGE_COUNT_TEST);
        if (0 == ret)
        {
          /* Icu_Edge_Count_Test Success */
          GblBreakLoop = ICU_TRUE;
        }
      }while (!GblBreakLoop);
      GblBreakLoop = ICU_FALSE;
      /* Reset Edge count for channel */
      Icu_ResetEdgeCount(channel);
      do
      {
        /* Get the number of edges counted */
        GblEdgeNumberCh[0] = Icu_GetEdgeNumbers(channel);
        ret = Icu_Edge_Count_Test(ICU_EDGE_RESET_TEST);
        if (0 == ret)
        {
          /* Icu_Edge_Count_Test Success */
          GblBreakLoop = ICU_TRUE;
        }
      }while (!GblBreakLoop);
      GblBreakLoop = ICU_FALSE;
      /* Disable Edge Counting for channel */
      Icu_DisableEdgeCount(channel);
      do
      {
        /* Get the number of edges counted */
        GblEdgeNumberCh[0] = Icu_GetEdgeNumbers(channel);
        ret = Icu_Edge_Count_Test(ICU_EDGE_STOP_TEST);
        if (0 == ret)
        {
          /* Icu_Edge_Count_Test Success */
          GblBreakLoop = ICU_TRUE;
        }
      }while (!GblBreakLoop);
      GblBreakLoop = ICU_FALSE;
    }
  }
  #endif /* End of (ICU_EDGE_COUNT_API == STD_ON) */
  /*****************************************************************************
  ********************* SIGNAL MEASUREMENT FUNCTIONALITY ***********************
  *****************************************************************************/
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
      /* Call Big Delay */
      Big_Delay();
      /* Read Elapsed Time for channel */
      GddTimeElapsed[6] = Icu_GetTimeElapsed(channel);

      /* Verify the output */
      if((GddTimeElapsed[0]==0)&&(GddTimeElapsed[1]!=0)&&(GddTimeElapsed[2]==0)&&
        (GddTimeElapsed[3]!=0)&&(GddTimeElapsed[4]!=0)&&(GddTimeElapsed[5]!=0)&&(GddTimeElapsed[6]==0))
      {
        GaaTestResult[GulCheckpoint] = TRUE;
        GulCheckpoint++;
      }
      else
      {
        GaaTestResult[GulCheckpoint] = FALSE;
        GulCheckpoint++;
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
        (GddDutyCycleValues[5].ActiveTime!=0) && (GddDutyCycleValues[5].PeriodTime!=0) &&
        (GddDutyCycleValues[6].ActiveTime==0) && (GddDutyCycleValues[6].PeriodTime==0))
      {
        GaaTestResult[GulCheckpoint] = TRUE;
        GulCheckpoint++;
      }
      else
      {
        GaaTestResult[GulCheckpoint] = FALSE;
        GulCheckpoint++;
      }

      /* To check the input state of a channel configured for signal measurement mode */
      /* Start Signal measurement for channel */
      Icu_StartSignalMeasurement(channel);

      Big_Delay();
      /* Get the input stae of the channel */
      GblInputStatus[0] = Icu_GetInputState(channel);
      GblInputStatus[1] = Icu_GetInputState(channel);
      /* GblInputStatus[0] should be ICU_ACTIVE and GblInputStatus[1] should be ICU_IDLE */
      /* Verify the output */
      if((GblInputStatus[0] == ICU_ACTIVE) & (GblInputStatus[1] == ICU_IDLE))
      {
        GaaTestResult[GulCheckpoint] = TRUE;
        GulCheckpoint++;
      }
      else
      {
        GaaTestResult[GulCheckpoint] = FALSE;
        GulCheckpoint++;
      }
      /* Stop Signal Measurement for for channel */
      Icu_StopSignalMeasurement(channel);

      GblInputStatus[0] = ICU_IDLE;
      GblInputStatus[1] = ICU_IDLE;
    }
  }
  #endif /* End of (ICU_SIGNAL_MEASUREMENT_API == STD_ON) */

  /*****************************************************************************
  ************************* EDGE DETECTION FUNCTIONALITY ***********************
  *****************************************************************************/
  #if (ICU_EDGE_DETECT_API == STD_ON)
  /* Loop for all configured channel to find the target channel */
  for(uint8 channel = 0; channel < ICU_MAX_CHANNEL; channel++)
  {
    if(Icu_GpChannelConfig[channel].ucIcuMeasurementMode == ICU_MODE_SIGNAL_EDGE_DETECT)
    {
      GusEdgeNumbers = 0;
      /* Enable EdgeDetection for channel */
      Icu_EnableEdgeDetection(channel);
      /* Enable notification for channel */
      Icu_EnableNotification(channel);
      /* Provide pulses */
      do
      {
        ret = Icu_Edge_Detect_Test(ICU_TRUE);
        if (0 ==ret)
        {
          /* Icu_Edge_Detect_Test Success */
          GblBreakLoop = ICU_TRUE;
        }
      }while (!GblBreakLoop);
      GblBreakLoop = ICU_FALSE;
      /* Disable EdgeDetection for channel */
      Icu_DisableEdgeDetection(channel);
      /* Disable notification for channel */
      Icu_DisableNotification(channel);
      /* Provide pulses */
      do
      {
        ret = Icu_Edge_Detect_Test(ICU_FALSE);
        if (0 == ret)
        {
          /* Icu_Edge_Detect_Test Success */
          GblBreakLoop = ICU_TRUE;
        }
      }while (!GblBreakLoop);
      GblBreakLoop = ICU_FALSE;

      /* To check the input state of a channel configured for edge detection mode */
      Big_Delay();
      #if (ICU_GET_INPUT_STATE_API == STD_ON)
      /* Read Input status for channel */
      GblInputStatus[0] = Icu_GetInputState(channel);
      GblInputStatus[1] = Icu_GetInputState(channel);
      /* Verify the output */
      if((GblInputStatus[0] == ICU_ACTIVE) & (GblInputStatus[1] == ICU_IDLE))
      {
        GaaTestResult[GulCheckpoint] = TRUE;
        GulCheckpoint++;
      }
      else
      {
        GaaTestResult[GulCheckpoint] = FALSE;
        GulCheckpoint++;
      }
      GblInputStatus[0] = ICU_IDLE;
      GblInputStatus[1] = ICU_IDLE;
      #endif
    }
  }
  #endif

  /*****************************************************************************
  **************************** WAKEUP FUNCTIONALITY ****************************
  *****************************************************************************/
  #if (ICU_WAKEUP_FUNCTIONALITY_API == STD_ON)
  /* Loop for all configured channel to find the target channel */
  for(uint8 channel = 0; channel < ICU_MAX_CHANNEL; channel++)
  {
    if((Icu_GpChannelConfig[channel].ucIcuWakeupCapability == ICU_TRUE) &&
      (Icu_GpChannelConfig[channel].ucIcuMeasurementMode == ICU_MODE_SIGNAL_EDGE_DETECT))
    {
      /* Set Rising Edge Activation condition for channel */
      Icu_SetActivationCondition(channel, ICU_RISING_EDGE);
      /* Enable EdgeDetection for channel */
      Icu_EnableEdgeDetection(channel);
      /* Enable notification for channel */
      Icu_EnableNotification(channel);
      #if (ICU_ENABLE_WAKEUP_API == STD_ON)
      /* Disable wakeup for channel */
      Icu_EnableWakeup(channel);
      #endif
      #if (ICU_SET_MODE_API == STD_ON)
      /* Set Icu to sleep mode */
      Icu_SetMode(ICU_MODE_SLEEP);
      /* Reset edge detect counter */
      GusEdgeNumbers = 0;
      Big_Delay();
      /* Set Icu to normal mode */
      Icu_SetMode(ICU_MODE_NORMAL);
      #endif
      #if (ICU_DISABLE_WAKEUP_API == STD_ON)
      /* Disable wakeup for channel */
      Icu_DisableWakeup(channel);
      #endif
      /* Disable EdgeDetection for channel */
      Icu_DisableEdgeDetection(channel);
      /* Disable notification for channel */
      Icu_DisableNotification(channel);
      #if (ICU_WAKEUP_FUNCTIONALITY_API == STD_ON)
      /* To verify and notify the wakeup source to the EcuM */
      Icu_CheckWakeup(Icu_GpChannelConfig[channel].ucEcuMChannelWakeupInfo);
      #endif
      /* Verify the output */
      if(GusEdgeNumbers != ICU_ZERO)
      {
        GaaTestResult[GulCheckpoint] = TRUE;
        GulCheckpoint++;
      }
      else
      {
        GaaTestResult[GulCheckpoint] = FALSE;
        GulCheckpoint++;
      }
      break;
    }
  }
  #endif
  /*****************************************************************************
  **************************** Read input level ********************************
  *****************************************************************************/
  #if (ICU_GET_INPUT_LEVEL_API == STD_ON)
  GblInputPinLevel[0] = Icu_GetInputLevel(0);
  /* Portpin output is low or high depend on the input level */
  if((GblInputPinLevel[0] == ICU_LOW) || (GblInputPinLevel[0] == ICU_HIGH))
  {
    GaaTestResult[GulCheckpoint] = TRUE;
    GulCheckpoint++;
  }
  else
  {
    GaaTestResult[GulCheckpoint] = FALSE;
    GulCheckpoint++;
  }
  #endif

  /* End of main() function */
  Icu_DeInit();

  /* Loop through all checkpoint and set value to result flag */
  for (uint8 count = 0; count < GulCheckpoint ; count++)
  {
    if (FALSE == GaaTestResult[count])
    {
      GblFlagFinalResult = FALSE;
      break;
    }
  }

  while(1)
  {
    /* This Sample application was completed */
  };
}

void Big_Delay(void)
{
  volatile uint16 LuiCnt1 = 0;
  volatile uint16 LuiCnt2 = 0;

  while (LuiCnt1 < 100)
  {
    LuiCnt1++;
    while (LuiCnt2 < 10000)
    {
      LuiCnt2++;
    }
    LuiCnt2 = 0;
  }
}

int Icu_Edge_Count_Test(uint8 testType)
{
  static Icu_EdgeNumberType edgeCount = 0;
  int ret = 0;

  switch (testType)
  {
  case ICU_EDGE_COUNT_TEST:
    Big_Delay();
    Big_Delay();
    edgeCount = GblEdgeNumberCh[0];
    if (0 == edgeCount)
    {
      ret = -1;
    }
    break;
  case ICU_EDGE_RESET_TEST:
    Big_Delay();
    if (edgeCount <= GblEdgeNumberCh[0])
    {
      ret = -1;
    }
    break;
  case ICU_EDGE_STOP_TEST:
    Big_Delay();
    edgeCount = GblEdgeNumberCh[0];
    Big_Delay();
    if (edgeCount != GblEdgeNumberCh[0])
    {
      ret = -1;
    }
    break;
  default:
    break;
  }
  return ret;
}

int Icu_Edge_Detect_Test(boolean detectEnable)
{
  static uint16 edgeDetect = 0U;
  int ret = 0;

  if (ICU_TRUE == detectEnable)
  {
    Big_Delay();
    edgeDetect = GusEdgeNumbers;
    if (0 == edgeDetect)
    {
      ret = -1;
    }
  }
  else
  {
    Big_Delay();
    edgeDetect = GusEdgeNumbers;
    Big_Delay();
    if (edgeDetect != GusEdgeNumbers)
    {
      ret = -1;
    }
  }
  return ret;
}

/*******************************************************************************
**                         Notification function                              **
*******************************************************************************/

/* Notification function for edge detect channel */
void Icu_EdgeDetect_Notification(void)
{
  /* Increment the counter to indicate that notification is invoked */
  GusEdgeNumbers++;
}

/* Notification function for timestamp channel */
void Icu_TimeStamps_Notification(void)
{
  /* Set flag to true to inform that the 5 timestamps have been captured */
  GblTimestampsCaptured = TRUE;
}

/* Notification function for edge count channel */
void Icu_EdgeCount_Overflow_Notification(void)
{
  /* Edge count overflow */
}

/* Notification function for signal measurement channel */
void Icu_Signal_Overflow_Notification(void)
{
  /* Signal measurement counter overflow */
}

/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
