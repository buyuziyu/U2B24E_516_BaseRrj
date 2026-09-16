/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2X MCAL Components                                                                 */
/* Module       = App_OCU_PostBuildVariant_Sample.c                                                                   */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2024,2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains sample application for OCU Driver Component                                                     */
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
 *  1.4.0  30/05/2025  : Improve test app for GTM channel
 *                     : Update 
 *  1.3.1  31/03/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 and RH850/U2Bx-E MCAL Ver22.00.02 Release
 *                       As part of support U2Bx-E SampleApp on G4KH, following changes are made:
 *                       1. Add function Guard_Enable_PE, Big_Delay
 *  1.3.0  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 *  1.2.0  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 *  1.1.1  31/10/2024  : As part of U2Bx-E support, following changes are made:
 *                       1. Add macro RUN_OTHER_PE,RUN_PEx(x from 1 to 6)
 *  1.0.3  26/03/2024  : Initial Version
 *         18/05/2024  : Change sequence sample app to test channels in GaaListChannel
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                 Include Section                                                    **
***********************************************************************************************************************/
#include "App_Ocu_Common_Sample.h"
#include "Std_Types.h"
#include "Ocu.h"
#include "App_OCU_Device_Sample.h"
#include "Ocu_PBTypes.h"
#include "Ocu_Ram.h"

/***********************************************************************************************************************
**                                                     Macros                                                         **
***********************************************************************************************************************/
/***********************************************************************************************************************
**                                                 Global variables                                                   **
***********************************************************************************************************************/
volatile uint16 GaaNotificationEntered[7] = {0, 0, 0, 0, 0, 0, 0};
uint32 GaaCounterValue[2] = {0, 0};
Ocu_ReturnType GenSetThresholdStatus[2] = {OCU_CM_OUT_REF_INTERVAL,OCU_CM_OUT_REF_INTERVAL};
Std_ReturnType GblSampleAppStatus = E_NOT_OK;
/* Variable used to store the version information */
Std_VersionInfoType versionInfo;
extern void Big_Delay(void);
/* Setting testing value*/
uint32 countVal;
uint32 refThreshold;
uint32 AbsThreshold;
uint32 relThreshold;
uint32 currentCountVal;
/* Global variable to store the test result */
volatile uint8 GulCheckpoint = 0;
volatile boolean GblFlagFinalResult = TRUE;
volatile uint32 GulFalseCheckPoint = 0;
/***********************************************************************************************************************
**                                              User function prototypes                                              **
***********************************************************************************************************************/
int main_sequence(const Ocu_ConfigType * Ocu_Config, Ocu_ChannelType ChannelNumber);
/***********************************************************************************************************************
**                                                 Function Definitions                                               **
***********************************************************************************************************************/
/*
 * Main Function
 */
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
  /* Wait amout of time */
  Big_Delay();
  /* Init the MCAL by stub init PORT,MCU... */
  Mcal_Ocu_Init();
  /* To get the version of the OCU Driver module */
  Ocu_GetVersionInfo(&versionInfo);
  /* Check for the correctness of version information */
  if ((OCU_VENDOR_ID == versionInfo.vendorID) &&
      (OCU_MODULE_ID == versionInfo.moduleID) &&
      (OCU_SW_MAJOR_VERSION == versionInfo.sw_major_version) &&
      (OCU_SW_MINOR_VERSION == versionInfo.sw_minor_version) &&
      (OCU_SW_PATCH_VERSION == versionInfo.sw_patch_version))
  {
    GblFlagFinalResult = TRUE;
  }
  else
  {
    GblFlagFinalResult = FALSE;
  }

  /* Loop for all testing channels */
  for (uint8 LucCount = OCU_ZERO; LucCount < sizeof(GaaListChannel)/sizeof(GaaListChannel[0]); LucCount++)
  {
    /* Call sample app sequence with Ocu_Config_Variant_1 */ 
    GblFlagFinalResult &= main_sequence(Ocu_Config_Variant_1, GaaListChannel[LucCount]);
    /* Call sample app sequence with Ocu_Config_Variant_2 */ 
    GblFlagFinalResult &= main_sequence(Ocu_Config_Variant_2, GaaListChannel[LucCount]);
  }

  return GblFlagFinalResult;
}/* End of main() function */

int main_sequence(const Ocu_ConfigType * Ocu_Config, Ocu_ChannelType channelNumber)
{
  /* Initialization of the OCU Driver */
  Ocu_Init(Ocu_Config);

  /* Enabling the Notification */
  Ocu_EnableNotification(channelNumber);

  /* Set pin action to OCU_TOGGLE */
  Ocu_SetPinAction(channelNumber, OCU_TOGGLE);

  if (( channelNumber == (int)0 ) || ( channelNumber == (int)2 ))
  {
    /* Wait for the counter count */
    while (Ocu_GetCounter(channelNumber) != countVal);
  }

  /* Set pin State to low level */
  Ocu_SetPinState(channelNumber,OCU_LOW);

  /* Set pin State to high level */
  Ocu_SetPinState(channelNumber,OCU_HIGH);

  /* Start channel */
  GblSampleAppStatus = Ocu_StartChannel(channelNumber);
  if (E_OK == GblSampleAppStatus)
  {
    GulFalseCheckPoint |= 1 << GulCheckpoint;
    GulCheckpoint++;
  }
  else
  {
    GulCheckpoint++;
  }

  /* Wait for 5 times of compare match, equal to 5 notifications was invoked */
  while (GaaNotificationEntered[channelNumber]<5U);

  /* Set the new threshold using Ocu_SetAbsoluteThreshold */
  refThreshold = (uint32)(0.3*(Ocu_GpChannelConfig[channelNumber].ulMaxCounterValue));
  AbsThreshold = (uint32)(0.5*(Ocu_GpChannelConfig[channelNumber].ulMaxCounterValue));
  GenSetThresholdStatus[0] = Ocu_SetAbsoluteThreshold(channelNumber,refThreshold,AbsThreshold);
  if (OCU_CM_OUT_REF_INTERVAL == GenSetThresholdStatus[0])
  {
    GulFalseCheckPoint |= 1 << GulCheckpoint;
    GulCheckpoint++;
  }
  else
  {
    GulCheckpoint++;
  }

  /* Wait for 5 times of compare match, equal to 5 notifications was invoked */
  while (GaaNotificationEntered[channelNumber]<10U);

  /* Set the new threshold using Ocu_SetRelativeThreshold */
  relThreshold = (uint32)(0.1*(Ocu_GpChannelConfig[channelNumber].ulMaxCounterValue));
  GenSetThresholdStatus[1] = Ocu_SetRelativeThreshold(channelNumber,relThreshold);
  if (OCU_CM_IN_REF_INTERVAL == GenSetThresholdStatus[1])
  {
    GulFalseCheckPoint |= 1 << GulCheckpoint;
    GulCheckpoint++;
  }
  else
  {
    GulCheckpoint++;
  }

  /* Wait for 5 times of compare match, equal to 5 notifications was invoked */
  while (GaaNotificationEntered[channelNumber]<15U);

  /* Check the current value of the counter */
  GaaCounterValue[0] = Ocu_GetCounter(channelNumber);
  currentCountVal = (uint32)(0.6*(Ocu_GpChannelConfig[channelNumber].ulMaxCounterValue));
  if (currentCountVal <= GaaCounterValue[0])
  {
    GulFalseCheckPoint |= 1 << GulCheckpoint;
    GulCheckpoint++;
  }
  else
  {
    GulCheckpoint++;
  }

  /* Set pin action to OCU_SET_HIGH, output level will be high level at next compare match */
  Ocu_SetPinAction(channelNumber, OCU_SET_HIGH);

  /* Wait for 5 times of compare match, equal to 5 notifications was invoked */
  while (GaaNotificationEntered[channelNumber]<20U);

  /* Set pin action to OCU_SET_LOW  output level will be low level at next compare match */
  Ocu_SetPinAction(channelNumber, OCU_SET_LOW);

  /* Wait for 5 times of compare match, equal to 5 notifications was invoked */
  while (GaaNotificationEntered[channelNumber]<25U);

  /* Disable the notification */
  Ocu_DisableNotification(channelNumber);

  /* Stop the channel */
  Ocu_StopChannel(channelNumber);

  /* Reset notification for channel */
  GaaNotificationEntered[channelNumber] = 0U;

  /* Deinit the Ocu module */
  Ocu_DeInit();

  uint8 count = 0;
  /* Loop through all checkpoint and set value to result flag */
  for (count = 0; count < GulCheckpoint ; count++)
  {
    if ((GulFalseCheckPoint & (1 << count)) == 0)
    {
      GblFlagFinalResult = FALSE;
      break;
    }
  }
  /* Reset */
  GulCheckpoint = 0;

  return GblFlagFinalResult;

} /* End of main_sequenceTAU() function */

void Ocu_Notification_0_Variant_1(void)
{
  /* Notification for channel */
  GaaNotificationEntered[0]++;
}

void Ocu_Notification_0_Variant_2(void)
{
  /* Notification for channel */
  GaaNotificationEntered[0]++;
}

void Ocu_Notification_1(void)
{
  /* Notification for channel */
  GaaNotificationEntered[1]++;
}

void Ocu_Notification_1_Variant_1(void)
{
  /* Notification for channel */
  GaaNotificationEntered[1]++;
}

void Ocu_Notification_1_Variant_2(void)
{
  /* Notification for channel */
  GaaNotificationEntered[1]++;
}

void Ocu_Notification_2(void)
{
  /* Notification for channel */
  GaaNotificationEntered[2]++;
}

void Ocu_Notification_2_Variant_1(void)
{
  /* Notification for channel */
  GaaNotificationEntered[2]++;
}

void Ocu_Notification_2_Variant_2(void)
{
  /* Notification for channel */
  GaaNotificationEntered[2]++;
}

void Ocu_Notification_3_Variant_1(void)
{
  /* Notification for channel */
  GaaNotificationEntered[3]++;
}

void Ocu_Notification_3_Variant_2(void)
{
  /* Notification for channel */
  GaaNotificationEntered[3]++;
}

void Ocu_Notification_4_Variant_1(void)
{
  /* Notification for channel */
  GaaNotificationEntered[4]++;
}

void Ocu_Notification_4_Variant_2(void)
{
  /* Notification for channel */
  GaaNotificationEntered[4]++;
}

void Ocu_Notification_5_Variant_1(void)
{
  /* Notification for channel */
  GaaNotificationEntered[5]++;
}

void Ocu_Notification_5_Variant_2(void)
{
  /* Notification for channel */
  GaaNotificationEntered[5]++;
}

void Ocu_Notification_6_Variant_1(void)
{
  /* Notification for channel */
  GaaNotificationEntered[6]++;
}

void Ocu_Notification_6_Variant_2(void)
{
  /* Notification for channel */
  GaaNotificationEntered[6]++;
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


/***********************************************************************************************************************
**                                                       End of File                                                  **
***********************************************************************************************************************/
