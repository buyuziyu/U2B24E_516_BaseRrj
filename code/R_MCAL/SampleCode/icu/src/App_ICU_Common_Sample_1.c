/*============================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                         */
/* Module       = App_ICU_Common_Sample_1.c                                   */
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
 * 2.4.1:  30/06/2025  : Remove SW-VERSION in file header
 * 2.4.0:  30/05/2025  : Remove prinft, improve volatile variable
 * 2.3.1:  31/03/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 
 *                       and RH850/U2Bx-E MCAL Ver22.00.02 Release
 * 2.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL
 *                       Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D 
 *                       Final Release
 * 2.1.2:  31/10/2024  : As part of support GTM HWIP into common sample app, 
 *                       following changes are made:
 *                       1.Update sample app for support GTM HWIP
 * 2.0.1:  28/10/2023  : Correct typo OCU to ICU
 *         25/10/2023  : Update SW-VERSION to 2.0.1
 * 2.0.0:  03/07/2022  : Re-write test app to support ICU Multi-core
 * 1.4.4:  28/06/2022  : Update EIBD setting for U2B6
 *         13/09/2022  : Update EIBD setting for U2Cx
 * 1.4.3:  18/04/2022  : Remove Caxi fuction, add api Icu_GetInputState, 
 *                       Icu_GetInputLevel Icu_GetTAUInCountValue
 * 1.3.1:  06/05/2021  : Implement Icu_SetMode, Icu_CheckWakeup, 
 *                       Icu_EnableWakup, Icu_DisableWakup sequences
 * 1.2.0:  17/07/2020  : Release
 * 1.1.0:  19/06/2020  : Release
 * 1.0.0:  25/03/2020  : Initial Version
 */
/******************************************************************************/

/*******************************************************************************
**                     Include Section                                        **
*******************************************************************************/
#include "App_ICU_Common_Sample_1.h"
#include "App_ICU_Multi_Sample.h"
/*******************************************************************************
**                            Macros                                          **
*******************************************************************************/

/*******************************************************************************
**                        Global variables                                    **
*******************************************************************************/
volatile uint16 GusEdgeNumbers;
Icu_EdgeNumberType GblEdgeNumberCh[1];
/* Global variable to store the test result */
uint8 GaaTestResult_PE1[50];
uint16 GulCheckpoint_PE1 = 0;
volatile boolean GblFlagFinalResult_PE1 = TRUE;
boolean GblBreakLoop_PE1 = ICU_FALSE;
/*******************************************************************************
**                        User function prototypes                            **
*******************************************************************************/
void task3(void);
int Icu_Edge_Count_Test(uint8 testType);
int Icu_Edge_Detect_Test(boolean detectEnable);
extern void Big_Delay(void);
/*******************************************************************************
*                      Function Definitions                                   **
*******************************************************************************/

/*******************************************************************************
** Function Name         : main_PE1
**
** Description           : Sample application of ICU Core 1.
** A continuous signal of 1 milli-second with 50% duty cycle and Vref
** should be given at input for all testing channel.
*******************************************************************************/
/* The app default starts on Core 1 after startup */
int main_PE1(void)
{
  /* Wait until Master core is done Initialization */
  while(0U == GblSyncFlag);

  /* Task 3 with channel Icu_IcuChannelConfiguration1 */
  task3();
  /* Notify core 0 as a task done from core 1 */
  GblSyncFlag = 0;

  /* Loop through all checkpoints and set value to result flag */
  for (uint8 count = 0; count < GulCheckpoint_PE1 ; count++)
  {
    if (FALSE == GaaTestResult_PE1[count])
    {
      GblFlagFinalResult_PE1 = FALSE;
      break;
    }
  }

  /* End trap */
  while(1)
  {
    /* This Sample application was completed */
  };
} /* End of main() function */

/*******************************************************************************
**                         Example task functions                             **
*******************************************************************************/

/* Task3, service API on core 1 */
void task3(void)
{
  volatile Icu_InputStateType LddInputStatus_Core1[3];
  /* Local Variable for measurement */
  Std_VersionInfoType versionInfo_PE1;
  int ret = 0;
  /* To get the version of the ICU Driver module */
  Icu_GetVersionInfo(&versionInfo_PE1);
  if ((ICU_VENDOR_ID == versionInfo_PE1.vendorID) &&
     (ICU_MODULE_ID == versionInfo_PE1.moduleID) &&
     (ICU_SW_MAJOR_VERSION == versionInfo_PE1.sw_major_version) &&
     (ICU_SW_MINOR_VERSION == versionInfo_PE1.sw_minor_version) &&
     (ICU_SW_PATCH_VERSION == versionInfo_PE1.sw_patch_version))
  {
    GaaTestResult_PE1[GulCheckpoint_PE1] = TRUE;
    GulCheckpoint_PE1++;
  }
  else
  {
    GaaTestResult_PE1[GulCheckpoint_PE1] = FALSE;
    GulCheckpoint_PE1++;
  }
/*******************************************************************************
**                         EDGE DETECT SECTION                                **
*******************************************************************************/
  #if (ICU_EDGE_DETECT_API == STD_ON)
  /* Loop for all configured channel to find the target channel */
  for(uint8 channel = 0; channel < ICU_MAX_CHANNEL; channel++)
  {
    if(Icu_GpChannelConfig[channel].ucIcuMeasurementMode == ICU_MODE_SIGNAL_EDGE_DETECT)
    {
      GusEdgeNumbers = 0;
      /* Enable EdgeDetection for channel */
      Icu_EnableEdgeDetection(channel);
      /* Wait until master core process the request */
      while (CheckSlaveRequest(channel, ICU_ENABLE_EDGE_DETECTION_SID));
      /* Enable notification for channel */
      Icu_EnableNotification(channel);
      /* Provide pulses */
      do
      {
        ret = Icu_Edge_Detect_Test(ICU_TRUE);
        if (0 ==ret)
        {
          /* Icu_Edge_Detect_Test Success */
          GblBreakLoop_PE1 = ICU_TRUE;
        }
      }while (!GblBreakLoop_PE1);
      GblBreakLoop_PE1 = ICU_FALSE;
      /* Disable EdgeDetection for channel */
      Icu_DisableEdgeDetection(channel);
      /* Wait until master core process the request */
      while (CheckSlaveRequest(channel, ICU_DISABLE_EDGE_DETECTION_SID));
      /* Disable notification for channel */
      Icu_DisableNotification(channel);
      /* Provide pulses */
      do
      {
        ret = Icu_Edge_Detect_Test(ICU_FALSE);
        if (0 == ret)
        {
          /* Icu_Edge_Detect_Test Success */
          GblBreakLoop_PE1 = ICU_TRUE;
        }
      }while (!GblBreakLoop_PE1);
      GblBreakLoop_PE1 = ICU_FALSE;

      /* To check the input state of a channel configured for edge detection mode */
      Big_Delay();
      #if (ICU_GET_INPUT_STATE_API == STD_ON)
      /* Read Input status for channel */
      LddInputStatus_Core1[0] = Icu_GetInputState(channel);
      LddInputStatus_Core1[1] = Icu_GetInputState(channel);
      /* Verify the output */
      if((LddInputStatus_Core1[0] == ICU_ACTIVE) & (LddInputStatus_Core1[1] == ICU_IDLE))
      {
        GaaTestResult_PE1[GulCheckpoint_PE1] = TRUE;
        GulCheckpoint_PE1++;
      }
      else
      {
        GaaTestResult_PE1[GulCheckpoint_PE1] = FALSE;
        GulCheckpoint_PE1++;
      }
      LddInputStatus_Core1[0] = ICU_IDLE;
      LddInputStatus_Core1[1] = ICU_IDLE;
      #endif
    }
  }
  #endif
/*******************************************************************************
**                          EDGE COUNT SECTION                                **
*******************************************************************************/
  #if (ICU_EDGE_COUNT_API == STD_ON)
  /* Loop for all configured channel to find the target channel */
  for(uint8 channel = 0; channel < ICU_MAX_CHANNEL; channel++)
  {
    if(Icu_GpChannelConfig[channel].ucIcuMeasurementMode == ICU_MODE_EDGE_COUNTER)
    {
      /* Set Rising Edge Activation condition for channel */
      Icu_SetActivationCondition(channel, ICU_RISING_EDGE);
      /* Wait until master core process the request */
      while (CheckSlaveRequest(channel, ICU_SET_ACTIVATION_CONDITION_SID));
      /* Enable Edge Counting for channel */
      Icu_EnableEdgeCount(channel);
      /* Wait until master core process the request */
      while (CheckSlaveRequest(channel, ICU_ENABLE_EDGE_COUNT_SID));
      /* Read Edge count for channel */
      do
      {
        /* Get the number of edges counted channel */
        GblEdgeNumberCh[0] = Icu_GetEdgeNumbers(channel);
        ret = Icu_Edge_Count_Test(ICU_EDGE_COUNT_TEST);
        if (0 == ret)
        {
          /* Icu_Edge_Count_Test Success */
          GblBreakLoop_PE1 = ICU_TRUE;
        }
      }while (!GblBreakLoop_PE1);
      GblBreakLoop_PE1 = ICU_FALSE;
      /* Reset Edge count for channel */
      Icu_ResetEdgeCount(channel);
      /* Wait until master core process the request */
      while (CheckSlaveRequest(channel, ICU_RESET_EDGE_COUNT_SID));
      do
      {
        /* Get the number of edges counted */
        GblEdgeNumberCh[0] = Icu_GetEdgeNumbers(channel);
        ret = Icu_Edge_Count_Test(ICU_EDGE_RESET_TEST);
        if (0 == ret)
        {
          /* Icu_Edge_Count_Test Success */
          GblBreakLoop_PE1 = ICU_TRUE;
        }
      }while (!GblBreakLoop_PE1);
      GblBreakLoop_PE1 = ICU_FALSE;
      /* Disable Edge Counting for channel */
      Icu_DisableEdgeCount(channel);
      /* Wait until master core process the request */
      while (CheckSlaveRequest(channel, ICU_DISABLE_EDGE_COUNT_SID));
      do
      {
        /* Get the number of edges counted */
        GblEdgeNumberCh[0] = Icu_GetEdgeNumbers(channel);
        ret = Icu_Edge_Count_Test(ICU_EDGE_STOP_TEST);
        if (0 == ret)
        {
          /* Icu_Edge_Count_Test Success */
          GblBreakLoop_PE1 = ICU_TRUE;
        }
      }while (!GblBreakLoop_PE1);
      GblBreakLoop_PE1 = ICU_FALSE;
    }
  }
  #endif /* End of (ICU_EDGE_COUNT_API == STD_ON) */
}
/* End of main() function */

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
void Icu_EdgeDetect_Notification(void)
{
  /* Detect activation edge, changing status flags */
  GusEdgeNumbers++;
}

void Icu_EdgeCount_Overflow_Notification(void)
{
  /* No action required */
}

/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
