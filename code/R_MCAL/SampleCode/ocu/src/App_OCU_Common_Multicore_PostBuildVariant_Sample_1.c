/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2X MCAL Components                                                                 */
/* Module       = App_OCU_Common_Multicore_PostBuildVariant_Sample_1.c                                                */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2024,2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains sample application multi core of Core 1 for OCU Driver Component                                */
/*                                                                                                                    */
/*====================================================================================================================*/
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
/*====================================================================================================================*/
/* Environment:                                                                                                       */
/*              Devices:        X2x                                                                                   */
/*====================================================================================================================*/

/***********************************************************************************************************************
**                                              Revision Control History                                              **
***********************************************************************************************************************/
/*
 *  1.4.1  30/06/2025  : Improve test app for U2B10 clock up
 *  1.4.0  30/05/2025  : Improve test app for GTM channel
 *  1.3.1  31/03/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 and RH850/U2Bx-E MCAL Ver22.00.02 Release
 *  1.3.0  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 *  1.2.0  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 *  1.0.3  26/03/2024  : Initial Version
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                 Include Section                                                    **
***********************************************************************************************************************/
#include "App_OCU_Common_Sample_1.h"
#include "App_OCU_Multi_Sample.h"
#include "Ocu_Ram.h"

/***********************************************************************************************************************
**                                                     Macros                                                         **
***********************************************************************************************************************/
/***********************************************************************************************************************
**                                                 Global variables                                                   **
***********************************************************************************************************************/
uint32 GaaCounterValue_PE1[2] = {0, 0};
Ocu_ReturnType GenSetThresholdStatus_PE1[2] = {OCU_CM_OUT_REF_INTERVAL,OCU_CM_OUT_REF_INTERVAL};
Std_ReturnType GblSampleAppStatus_PE1 = E_NOT_OK;
/* Variable used to store the version information */
Std_VersionInfoType versionInfo_PE1;
extern volatile uint32 Gul1msecCount;
/* Setting testing value*/
extern uint32 currentCountVal;
extern uint32 refThreshold;
extern uint32 AbsThreshold;
extern uint32 relThreshold;
/* Global variable to store the test result */
volatile uint8 GulCheckpointPE1 = 0;
volatile boolean GblFlagFinalResultPE1 = TRUE;
volatile uint32 GulFalseCheckPointPE1 = 0;
/***********************************************************************************************************************
**                                              User function prototypes                                              **
***********************************************************************************************************************/
int task3(uint8 channel_index);
/***********************************************************************************************************************
**                                                 Function Definitions                                               **
***********************************************************************************************************************/

/* The app default starts on Core 1 after startup */
int main_PE1(void)
{
  /* Check synchronous init in core 0 */
  PE1_SYNC_INIT_CHECK();

  /* Waiting Initialization by PE0 */
  PE1_SYNC();
  /* Task 3 with channel Ocu_OcuChannelConfiguration1 for Variant1 */
  GblFlagFinalResultPE1 &= task3(Ocu_OcuChannelConfiguration1);
  /* Task 3 with channel Ocu_OcuChannelConfiguration1 for Variant2 */
  GblFlagFinalResultPE1 &= task3(Ocu_OcuChannelConfiguration1);
  /* Waiting Initialization by PE0 */
  PE1_SYNC();

  #if (STD_ON == OCU_GTM_ATOM_USED)
  /* Waiting Initialization by PE0 */
  PE1_SYNC();
  /* Task 3 with channel Ocu_OcuChannelConfiguration1 for Variant1 */
  GblFlagFinalResultPE1 &= task3(Ocu_OcuChannelConfiguration3);
  /* Task 3 with channel Ocu_OcuChannelConfiguration1 for Variant2 */
  GblFlagFinalResultPE1 &= task3(Ocu_OcuChannelConfiguration3);
  /* Waiting Initialization by PE0 */
  PE1_SYNC();
  #endif

  #if (STD_ON == OCU_GTM_TOM_USED)
  /* Waiting Initialization by PE0 */
  PE1_SYNC();
  /* Task 3 with channel Ocu_OcuChannelConfiguration1 for Variant1 */
  GblFlagFinalResultPE1 &= task3(Ocu_OcuChannelConfiguration5);
  /* Task 3 with channel Ocu_OcuChannelConfiguration1 for Variant2 */
  GblFlagFinalResultPE1 &= task3(Ocu_OcuChannelConfiguration5);
  /* Waiting Initialization by PE0 */
  PE1_SYNC();
  #endif

  /* End trap */
  while(1)
  {
    /* This Sample application was completed */
  };
} /* End of main() function */


/* Task3, service API on core 1 */
int task3(uint8 channel_index)
{
  /* To get the version of the OCU Driver module */
  Ocu_GetVersionInfo(&versionInfo_PE1);

  /* Wait until Master core is done Initialization */
  while(0U == GblSyncFlag);

  /* Enabling the Notification */
  Ocu_EnableNotification(channel_index);

  /* Set pin action to OCU_TOGGLE */
  Ocu_SetPinAction(channel_index, OCU_TOGGLE);
  /* Wait until master core process the request */
  while (CheckSlaveRequest(channel_index, OCU_SET_PIN_ACTION_SID));

  if (((int)2 == channel_index) || ((int)1 == channel_index))
  {
  /* Wait for the counter count to 20 */
  while (Ocu_GetCounter(channel_index) != 20U);
  }

  /* Set pin State to low level */
  Ocu_SetPinState(channel_index,OCU_LOW);
  /* Wait until master core process the request */
  while (CheckSlaveRequest(channel_index, OCU_SET_PIN_STATE_SID));
  /* Set pin State to high level */
  Ocu_SetPinState(channel_index,OCU_HIGH);
  /* Wait until master core process the request */
  while (CheckSlaveRequest(channel_index, OCU_SET_PIN_STATE_SID));

  /* Start the channel */
  GblSampleAppStatus_PE1 = Ocu_StartChannel(channel_index);
  if (E_OK == GblSampleAppStatus_PE1)
  {
    GulFalseCheckPointPE1 |= 1 << GulCheckpointPE1;
    GulCheckpointPE1++;
  }
  else
  {
    GulCheckpointPE1++;
  }
  /* Wait until master core process the request */
  while (CheckSlaveRequest(channel_index, OCU_START_CHANNEL_SID));

  /* Wait the notification */
  while (GaaNotificationEntered[channel_index]<5U);

  /* Set the new threshold using Ocu_SetAbsoluteThreshold */
  GenSetThresholdStatus_PE1[0] = Ocu_SetAbsoluteThreshold(channel_index, OCU_ZERO, OCU_ZERO);
  if (OCU_CM_OUT_REF_INTERVAL == GenSetThresholdStatus_PE1[0])
  {
    GulFalseCheckPointPE1 |= 1 << GulCheckpointPE1;
    GulCheckpointPE1++;
  }
  else
  {
    GulCheckpointPE1++;
  }
  /* Wait until master core process the request */
  while (CheckSlaveRequest(channel_index, OCU_SET_ABSOLUTE_THRESHOLD_SID));

  /* Wait the notification */
  while (GaaNotificationEntered[channel_index]<10U);
  /* Get the current value of the counter */
  GaaCounterValue_PE1[0] = Ocu_GetCounter(channel_index);
  if ((GaaCounterValue_PE1[0] > OCU_ZERO) || (GaaCounterValue_PE1[0] == OCU_ZERO))
  {
    GulFalseCheckPointPE1 |= 1 << GulCheckpointPE1;
    GulCheckpointPE1++;
  }
  else
  {
    GulCheckpointPE1++;
  }

  /* Set the new threshold using Ocu_SetRelativeThreshold */
  relThreshold = (uint32)(0.1*(Ocu_GpChannelConfig[channel_index].ulMaxCounterValue));
  GenSetThresholdStatus_PE1[1] = Ocu_SetRelativeThreshold(channel_index,relThreshold);
  if (OCU_CM_IN_REF_INTERVAL == GenSetThresholdStatus_PE1[1])
  {
    GulFalseCheckPointPE1 |= 1 << GulCheckpointPE1;
    GulCheckpointPE1++;
  }
  else
  {
    GulCheckpointPE1++;
  }
  /* Wait until master core process the request */
  while (CheckSlaveRequest(channel_index, OCU_SET_RELATIVE_THRESHOLD_SID));

  /* Wait the notification */
  while (GaaNotificationEntered[channel_index]<15U);

  /* Set pin action to OCU_SET_HIGH, output level will be high level at next compare match */
  Ocu_SetPinAction(channel_index, OCU_SET_HIGH);
  /* Wait until master core process the request */
  while (CheckSlaveRequest(channel_index, OCU_SET_PIN_ACTION_SID));

  /* Wait the notification */
  while (GaaNotificationEntered[channel_index]<20U);

  /* Set pin action to OCU_SET_LOW  output level will be low level at next compare match */
  Ocu_SetPinAction(channel_index, OCU_SET_LOW);
  /* Wait until master core process the request */
  while (CheckSlaveRequest(channel_index, OCU_SET_PIN_ACTION_SID));

  /* Wait the notification */
  while (GaaNotificationEntered[channel_index]<25U);

  /* Disable the notification */
  Ocu_DisableNotification(channel_index);
  
  /* Stop the channel */
  Ocu_StopChannel(channel_index);

  /* Wait until master core process the request */
  while (CheckSlaveRequest(channel_index, OCU_STOP_CHANNEL_SID));
  
  /* Reset the notification */
  GaaNotificationEntered[channel_index] = 0U;

  /* Notify core 0 as a task done from core 1 */
  GblSyncFlag = 0;
  
  uint8 count = 0;
  /* Loop through all checkpoint and set value to result flag */
  for (count = 0; count < GulCheckpointPE1 ; count++)
  {
    if ((GulFalseCheckPointPE1 & (1 << count)) == 0)
    {
      GblFlagFinalResultPE1 = FALSE;
      break;
    }
  }
  return GblFlagFinalResultPE1;
}
/***********************************************************************************************************************
**                                                       End of File                                                  **
***********************************************************************************************************************/
