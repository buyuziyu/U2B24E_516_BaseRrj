/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2X MCAL Components                                                                 */
/* Module       = App_OCU_Multicore_PostBuildVariant_Sample.c                                                         */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2024,2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Sample all Multicore common source file.                                                                           */
/*                                                                                                                    */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Provision of API and database declaration, Service Id and DET error Macros                                         */
/* and Module version information Macros.                                                                             */
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
 *  1.4.1  30/06/2025  : Add PE synchronous register, function
 *  1.4.0  30/05/2025  : Improve test app for GTM channel
 *  1.3.1  31/03/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 and RH850/U2Bx-E MCAL Ver22.00.02 Release
 *  1.3.0  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 *  1.2.0  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 *  1.0.3  26/03/2024  : Initial Version
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
#include "Std_Types.h"
#include "App_OCU_Multi_Sample.h"
/***********************************************************************************************************************
**                                                     Macros                                                         **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Global variables                                                     **
***********************************************************************************************************************/
//Global flag for sync information between cores
volatile boolean GblSyncFlag = 0;
volatile uint16 GaaNotificationEntered[8] = {0, 0, 0, 0, 0, 0, 0, 0};
volatile boolean GblCore0SyncInit=0;
volatile boolean GblCore1SyncInit=0;
/***********************************************************************************************************************
**                                               Global Function Prototypes                                           **
***********************************************************************************************************************/
/* Check the request has been executed or not */
boolean CheckSlaveRequest(uint8 channel_index, uint8 api_id)
{
  boolean LblReturnResult = 1;
  switch(api_id)
  {
    case OCU_START_CHANNEL_SID:
      LblReturnResult = Ocu_GaaStartChannelBuffer[channel_index].blSetRequest;
      break;
    case OCU_STOP_CHANNEL_SID:
      LblReturnResult = Ocu_GaaStopChannelBuffer[channel_index].blSetRequest;
      break;
    case OCU_SET_PIN_STATE_SID:
      LblReturnResult = Ocu_GaaSetPinStateBuffer[channel_index].blSetRequest;
      break;
    case OCU_SET_PIN_ACTION_SID:
      LblReturnResult = Ocu_GaaSetPinActionBuffer[channel_index].blSetRequest;
      break;
    case OCU_SET_ABSOLUTE_THRESHOLD_SID:
      LblReturnResult = Ocu_GaaSetAbsoluteThresholdBuffer[channel_index].blSetRequest;
      break;
    case OCU_SET_RELATIVE_THRESHOLD_SID:
      LblReturnResult = Ocu_GaaSetRelativeThresholdBuffer[channel_index].blSetRequest;
      break;
    default:
      break;
  }
  return LblReturnResult;
}

/* Initialization for select cores */
void OCU_SYNC_CORE(void)
{
  OCU_SYNC_PARTICIPATING_PE_EN = (OCU_SYNC_START_PE0 | OCU_SYNC_START_PE1);
  OCU_SYNC_INIT = OCU_SYNC_CLEAR;
  GblCore0SyncInit = 1;
  GblCore1SyncInit = 1;
}

/* Waiting Initialization by PE0 */
void PE0_SYNC_INIT_CHECK(void)
{
  while(GblCore0SyncInit == 0)
  {
    /* No action required */
  };
}

/* Waiting Initialization by PE0 */
void PE1_SYNC_INIT_CHECK(void)
{
  while(GblCore1SyncInit == 0)
  {
    /* No action required */
  };
}

/* Waiting Initialization by PE0 */
void PE0_SYNC(void)
{
  OCU_SYNC_CHECK_0_PE0 = OCU_SYNC_ENABLE;
  while (OCU_SYNC_COMPLETION_PE0 != OCU_SYNC_COMPLETION)
  {
  /* No action required */
  };
  OCU_SYNC_COMPLETION_PE0 = 0;
}

/* Waiting Initialization by PE1 */
void PE1_SYNC(void)
{
  OCU_SYNC_CHECK_0_PE1 = OCU_SYNC_ENABLE;
  while (OCU_SYNC_COMPLETION_PE1 != OCU_SYNC_COMPLETION)
  {
  /* No action required */
  };
  OCU_SYNC_COMPLETION_PE1 = 0;
}

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

void Ocu_Notification_7_Variant_1(void)
{
  /* Notification for channel */
  GaaNotificationEntered[7]++;
}
void Ocu_Notification_7_Variant_2(void)
{
  /* Notification for channel */
  GaaNotificationEntered[7]++;
}
/* Trap CPU at the end of the application */
void sample_end(void)
{
  while(1);
}
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/

