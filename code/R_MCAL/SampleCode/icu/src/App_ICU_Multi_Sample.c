/*============================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                         */
/* Module       = App_ICU_Common_Sample.c                                     */
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
 * 2.4.0:  30/05/2025  : Update SW-VERSION for RH850/U2Cx MCAL 
 *                       Ver22.01.01 Release
 * 2.3.1:  31/03/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 
 *                       and RH850/U2Bx-E MCAL Ver22.00.02 Release
 * 2.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL
 *                       Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D 
 *                       Final Release
 * 2.1.2:  31/10/2024  : As part of support GTM HWIP into common sample app, 
 *                       following changes are made:
 *                       1.Update sample app for support GTM HWIP
 * 2.0.1:  25/10/2023  : Update SW-VERSION to 2.0.1
 * 1.2.0:  17/07/2020  : Release
 * 1.1.0:  19/06/2020  : Release
 * 1.0.0:  25/03/2020  : Initial Version
 */
/******************************************************************************/

/*******************************************************************************
**                     Include Section                                        **
*******************************************************************************/
#include "Std_Types.h"
#include "App_ICU_Multi_Sample.h"
/*******************************************************************************
**                            Macros                                          **
*******************************************************************************/

/*******************************************************************************
**                        Global variables                                    **
*******************************************************************************/
//Global flag for sync information between cores
volatile boolean GblSyncFlag = 0;
/*******************************************************************************
**                        User function prototypes                            **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
/* Check the request has been executed or not */
boolean CheckSlaveRequest(uint8 channel_index, uint8 api_id)
{
  /* Read the channel time stamp ram index */
  uint8 LucChannelRamIndex = Icu_GpChannelUserRegConfig[channel_index].ucRamDataIndex;
  /* Return result */
  boolean LblReturnResult = 1;
  switch(api_id)
  {
    case ICU_START_TIMESTAMP_SID:
      /* Check the buffer request Icu_GaaStartTimestampBuffer */
      LblReturnResult = Icu_GaaStartTimestampBuffer[LucChannelRamIndex].blSetRequest;
      break;
    case ICU_STOP_TIMESTAMP_SID:
      /* Check the buffer request Icu_GaaStopTimestampBuffer */
      LblReturnResult = Icu_GaaStopTimestampBuffer[LucChannelRamIndex].blSetRequest;
      break;
    case ICU_RESET_EDGE_COUNT_SID:
      /* Check the buffer request Icu_GaaResetEdgeCountBuffer */
      LblReturnResult = Icu_GaaResetEdgeCountBuffer[LucChannelRamIndex].blSetRequest;
      break;
    case ICU_ENABLE_EDGE_COUNT_SID:
      /* Check the buffer request Icu_GaaEnableEdgeCountBuffer */
      LblReturnResult = Icu_GaaEnableEdgeCountBuffer[LucChannelRamIndex].blSetRequest;
      break;
    case ICU_DISABLE_EDGE_COUNT_SID:
      /* Check the buffer request Icu_GaaDisableEdgeCountBuffer */
      LblReturnResult = Icu_GaaDisableEdgeCountBuffer[LucChannelRamIndex].blSetRequest;
      break;
    case ICU_ENABLE_EDGE_DETECTION_SID:
      /* Check the buffer request Icu_GaaEnableEdgeDetectionBuffer */
      LblReturnResult = Icu_GaaEnableEdgeDetectionBuffer[LucChannelRamIndex].blSetRequest;
      break;
    case ICU_DISABLE_EDGE_DETECTION_SID:
      /* Check the buffer request Icu_GaaDisableEdgeDetectionBuffer */
      LblReturnResult = Icu_GaaDisableEdgeDetectionBuffer[LucChannelRamIndex].blSetRequest;
      break;
    case ICU_START_SIGNAL_MEASUREMENT_SID:
      /* Check the buffer request Icu_GaaStartSignalMeasurementBuffer */
      LblReturnResult = Icu_GaaStartSignalMeasurementBuffer[LucChannelRamIndex].blSetRequest;
      break;
    case ICU_STOP_SIGNAL_MEASUREMENT_SID:
      /* Check the buffer request Icu_GaaStopSignalMeasurementBuffer */
      LblReturnResult = Icu_GaaStopSignalMeasurementBuffer[LucChannelRamIndex].blSetRequest;
      break;
    case ICU_SET_ACTIVATION_CONDITION_SID:
      /* Check the buffer request Icu_GaaSetActivationConditionBuffer */
      LblReturnResult = Icu_GaaSetActivationConditionBuffer[channel_index].blSetRequest;
      break;
    default:
      break;
  }
  return LblReturnResult;
}

/* Delay stub function */
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

/*******************************************************************************
**                         Notification function                              **
*******************************************************************************/

/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
