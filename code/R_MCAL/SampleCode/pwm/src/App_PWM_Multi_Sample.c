/*============================================================================*/
/* Project      = RH850/X2x AR4 MCAL Development                              */
/* Module       = App_PWM_Multi_Sample.c                                      */
/*                                                                            */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.        */
/*============================================================================*/
/* Purpose:                                                                   */
/* This file contains sample application for PWM Driver Component             */
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
/*                                                                            **
 * 2.5.1: 30/06/2025 : Remove SW-VERSION in header comment                    **
 * 2.5.0: 30/06/2025 : Update SW-VERSION for U2Ax Ver22.01.00(D) Final Release** 
 * 2.4.0: 31/05/2025 : Update SW-VERSION for U2Cx Ver21.01.01 Final Release   **
 * 2.3.2: 29/04/2025 : Update SW-VERSION for U2Ax Ver22.00.04 Beta Release    **
 * 2.3.1: 31/03/2025 : Update SW-VERSION for U2BxE Ver22.00.02 Beta Release   **
 * 2.3.0:  28/02/2025 : Update SW-VERSION for RH850/U2Cx MCAL                 **
 *                      Ver22.01.00/Ver22.01.00.D Release                     **
 * 2.2.0:  31/12/2024 : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final **
 *                      Release                                               **
 * 2.1.2:  31/10/2024 : Update SW-VERSION for Ver22.01.02 U2Bx Beta2 Release  **
 * 2.1.1:  15/06/2024 : As part of U2BxE support, following changes are made  **
 *                      1. Update sample app for device U2B12E, U2B6E         **
 * 2.0.1:  25/10/2023 : Update version in header comment                      **
 * 2.0.0:  05/07/2023 : Update to support Multi-corre                         **
 * 1.3.1:  15/05/2021 : Fixed Coding Rule                                     **
 * 1.2.0:  17/07/2020 : Release                                               **
 * 1.1.0:  19/06/2020 : Release                                               **
 * 1.0.0:  24/03/2020 : Initial Version.                                      **
 *                                                                            */
/******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "Std_Types.h"
#include "App_PWM_Device_Sample.h"
#include "App_PWM_Multi_Sample.h"
#include "App_PWM_Common_Sample_0.h"
#include "App_PWM_Common_Sample_1.h"

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
extern void Guard_Init(void);
extern void Port_Init(void);
extern void Mcu_Init(void);
extern void Wdg_Init(void);
extern void Reg_Init(void);
#if (DEVICE == E2x)
extern Std_ReturnType Pwm_CheckOpbtTimerIpSelect(void);
#endif
/*******************************************************************************
*                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
**                       Global Function Prototypes                           **
*******************************************************************************/
/* Check the request has been executed or not */
boolean CheckSlaveRequest(uint8 channel_index, uint8 api_id)
{
  boolean LblReturnResult = 1;
  switch(api_id)
  {
    case PWM_SET_DUTYCYCLE_SID:
      LblReturnResult = Pwm_GaaSetDutyCycleBuffer[channel_index].blSetReq;
      break;
    case PWM_SET_PERIODANDDUTY_SID:
      LblReturnResult = Pwm_GaaSetPeriodAndDutyBuffer[channel_index].blSetReq;
      break;
    case PWM_SET_OUTPUTTOIDLE_SID:
      LblReturnResult = Pwm_GaaSetOutputToIdleBuffer[channel_index].blSetReq;
      break;
    case PWM_SELECT_CHANNEL_CLK_SID:
      LblReturnResult = Pwm_GaaSelectChannelClkBuffer[channel_index].blSetReq;
      break;
    case PWM_SET_CHANNEL_OUTPUT_SID:
      LblReturnResult = Pwm_GaaSetChannelOutputBuffer[channel_index].blSetReq; 
      break;
    default:
      break;
  }
  return LblReturnResult;
}

/* Trap CPU at the end of the application */
void sample_end(void)
{
  while(1);
}
/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
