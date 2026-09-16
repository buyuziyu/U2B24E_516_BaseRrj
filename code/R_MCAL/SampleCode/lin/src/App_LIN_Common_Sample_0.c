/*============================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                         */
/* Module       = App_LIN_Common_Sample.c                                     */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2023-2025 Renesas Electronics Corporation. All rights reserved.        */
/*============================================================================*/
/* Purpose:                                                                   */
/* This file contains sample application for LIN Driver Component             */
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
 * 2.4.0:  30/06/2025  : Remove the SW-VERSION from header of file
 * 2.3.2:  25/04/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03
 *                       Release
 *                       Add ASM_NOP() to support CCRH compiler
 * 2.3.1:  31/03/2025  : Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02
 *                       Release
 * 2.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL
 *                       Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00(D) U2Bx Final Release
 * 2.1.2:  31/10/2024  : Update SW-VERSION
 * 2.1.1:  30/08/2024  : As part of U2BxE support, following changes are made:
 *                       1. Add precondition for U2BxE
 *                       As part of multi-core and post build variant support,
 *                       following changes are made:
 *                       1. Replace marco TEST_LIN_WAIT_500MS with LIN_WAIT_MS(t)
 * 2.0.1:  29/10/2023  : Update register to support for U2Cx device
 * 2.0.0:  22/08/2023  : Fix typo mistake
 *         18/07/2023  : Initialize version for SA support multi-core
 */
/******************************************************************************/

/*******************************************************************************
**                     Include Section                                        **
*******************************************************************************/
#include "App_LIN_Multi_Sample.h"
#include "App_LIN_Device_Sample.h"
#include "App_LIN_Common_Sample_0.h"

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/
/* Global variable for Lin Pdu structure used in Lin_SendHeader and
 * Lin_SendResponse APIs */
Lin_PduType GddPduInfo_0;
/* Global variable to use in Lin_GetStatus API for function return type */
Lin_StatusType GenStatusType_0;
/* Global pointer used in Lin_GetStatus API as output parameter */
const uint8 ** GpRxDataPtr_0;
/* Global pointer used by GpRxDataPtr */
const uint8 *GpLinSduPtr_0;

/* Global data used as input parameter in Lin_SendResponse API */
uint8 Lin_GaaDataArray0_0[LIN_DATA_SIZE] = 
                      {(uint8)0x00U, (uint8)0x02U, (uint8)0x03U, (uint8)0x04U, 
                       (uint8)0x05U, (uint8)0x06U, (uint8)0x07U, (uint8)0x08U};
/* Global data used by GpLinSduPtr_0 for a default value */
uint8 Lin_GaaDataArray1_0[LIN_DATA_SIZE] = 
                      {(uint8)0xFFU, (uint8)0xFFU, (uint8)0xFFU, (uint8)0xFFU, 
                       (uint8)0xFFU, (uint8)0xFFU, (uint8)0xFFU, (uint8)0xFFU};
/* Global data used by check data receive*/
uint8 Lin_GaaDataReceiveArray1_0[LIN_DATA_SIZE] = 
                      {(uint8)0x03U, (uint8)0x03U, (uint8)0x03U, (uint8)0x03U, 
                       (uint8)0x03U, (uint8)0x03U, (uint8)0x03U, (uint8)0x03U};

/* Local variable to store the test result */
uint8 GaaTestResult0[13];

/* Local flag to hold final result*/
uint8 LucFlagFinalResult0 = TRUE;

const char *GucFinalResult0;

/******************************************************************************
* F U N C T I O N    D E F I N I T I O N S
******************************************************************************/
int main(void)
{
  uint32 LulTimeOut = 0;
  uint8 LucStatus;
  
  Init_MCAL();

  ENABLE_INTERRUPT();

  /* Set flag to indicate core 1 stub modules have been initialized */
  GucStubInitFlag = 1;

  /* Waiting for another core to complete init */
  while (1 == GucStubInitFlag)
  {
    //Do nothing
  }
  

  LucStatus = Lin_WakeupInternal(LIN_CHANNEL_0);
  if (E_OK == LucStatus)
  {
    GaaTestResult0[1] = 1;
  }
  else
  {
    GaaTestResult0[1] = 0;
  }

  LucStatus = Lin_GoToSleepInternal(LIN_CHANNEL_0);
  if (E_OK == LucStatus)
  {
    GaaTestResult0[2] = 1;
  }
  else
  {
    GaaTestResult0[2] = 0;
  }

  LucStatus = Lin_WakeupInternal(LIN_CHANNEL_0);
  if (E_OK == LucStatus)
  {
    GaaTestResult0[3] = 1;
  }
  else
  {
    GaaTestResult0[3] = 0;
  }

  LucStatus = Lin_GoToSleep(LIN_CHANNEL_0);
  if (E_OK == LucStatus)
  {
    GaaTestResult0[4] = 1;
  }
  else
  {
    GaaTestResult0[4] = 0;
  }
  LIN_WAIT_MS(500 * 1000); /* 500ms */

  if ((GenStatusType_0 = Lin_GetStatus(LIN_CHANNEL_0, GpRxDataPtr_0))
                                               == LIN_CH_SLEEP)
  {
    GaaTestResult0[5] = 1;
  }
  else
  {
    GaaTestResult0[5] = 0;
  }

  LucStatus = Lin_Wakeup(LIN_CHANNEL_0);
  if (E_OK == LucStatus)
  {
    GaaTestResult0[6] = 1;
  }
  else
  {
    GaaTestResult0[6] = 0;
  }
  LIN_WAIT_MS(500 * 1000); /* 500ms */

  if ((GenStatusType_0 = Lin_GetStatus(LIN_CHANNEL_0, GpRxDataPtr_0))
                                               == LIN_OPERATIONAL)
  {
    GaaTestResult0[7] = 1;
  }
  else
  {
    GaaTestResult0[7] = 0;
  }

  LucStatus = Lin_CheckWakeup(LIN_CHANNEL_0);
  if (E_OK == LucStatus)
  {
    GaaTestResult0[8] = 1;
  }
  else
  {
    GaaTestResult0[8] = 0;
  }

  LucStatus = Lin_GoToSleepInternal(LIN_CHANNEL_0);
  if (E_OK == LucStatus)
  {
    GaaTestResult0[9] = 1;
  }
  else
  {
    GaaTestResult0[9] = 0;
  }

  /* Set the LIN PDU parameters for transmitting the LIN Frame */
  GddPduInfo_0.Pid = (uint8)LIN_SEND_PID;
  GddPduInfo_0.Cs = LIN_CLASSIC_CS;
  GddPduInfo_0.Drc = LIN_FRAMERESPONSE_TX;
  GddPduInfo_0.Dl = LIN_DATA_SIZE;

  GddPduInfo_0.SduPtr = Lin_GaaDataArray0_0;

  /* Following API is invoked to transmit the header and response part of a LIN
   * as Frame on the addressed LIN Channel
   */
  Lin_WakeupInternal(LIN_CHANNEL_0);

  LucStatus = Lin_SendFrame(LIN_CHANNEL_0, &GddPduInfo_0);

  /* Wait transmission complete */
  LulTimeOut = TEST_LIN_TRANSFER_DELAY_9600;

  while((GenStatusType_0 = Lin_GetStatus(LIN_CHANNEL_0, GpRxDataPtr_0))
                                               != LIN_TX_OK && (LulTimeOut > 0))
  {
    LulTimeOut--;
  }
  
  /* Check Channel send frame succesfully */
  if (0 < LulTimeOut)
  {
    GaaTestResult0[10] = 1;
  }
  else
  {
    GaaTestResult0[10] = 0;
  }

  /* Set the LIN PDU parameters for receive the the LIN response */
  GddPduInfo_0.Pid = (uint8)LIN_RESP_PID;
  GddPduInfo_0.Cs = LIN_CLASSIC_CS;
  GddPduInfo_0.Drc = LIN_FRAMERESPONSE_RX;
  GddPduInfo_0.Dl = LIN_DATA_SIZE ;
  GddPduInfo_0.SduPtr = Lin_GaaDataArray1_0;

  /* Following API is invoked to transmit the header and receive the response
   * as part of a LIN Frame on the addressed LIN Channel
   */
  LucStatus = Lin_SendFrame(LIN_CHANNEL_0, &GddPduInfo_0);

  /* Wait transmission complete */
  LulTimeOut = TEST_LIN_TRANSFER_DELAY_9600;

  while((GenStatusType_0 = Lin_GetStatus(LIN_CHANNEL_0, GpRxDataPtr_0))
                                               != LIN_RX_OK && (LulTimeOut > 0))
  {
    LulTimeOut--;
  }

  /* Check channel receive message from CANoe successfully */
  if (0 < LulTimeOut)
  {
    GaaTestResult0[11] = 1;
  }
  else
  {
    GaaTestResult0[11] = 0;
  }

  /* Check data received from CANoe */
  if ((GpRxDataPtr_0[0][0] == Lin_GaaDataReceiveArray1_0[0]) &&
  (GpRxDataPtr_0[0][1] == Lin_GaaDataReceiveArray1_0[1]) &&
  (GpRxDataPtr_0[0][2] == Lin_GaaDataReceiveArray1_0[2]) &&
  (GpRxDataPtr_0[0][3] == Lin_GaaDataReceiveArray1_0[3]) &&
  (GpRxDataPtr_0[0][4] == Lin_GaaDataReceiveArray1_0[4]) &&
  (GpRxDataPtr_0[0][5] == Lin_GaaDataReceiveArray1_0[5]) &&
  (GpRxDataPtr_0[0][6] == Lin_GaaDataReceiveArray1_0[6]) &&
  (GpRxDataPtr_0[0][7] == Lin_GaaDataReceiveArray1_0[7]))
  {
    GaaTestResult0[12] = 1;
  }
  else
  {
    GaaTestResult0[12] = 0;
  }

  /*Loop through all checkpoint and set value to result flag*/
  for(uint8 count = 0; count < 13; count++)
  {
    if (FALSE == GaaTestResult0[count])
    {
        LucFlagFinalResult0 = FALSE;
    }
    else
    {
        //Do not thing
    }
  }

  /* Final Result*/
  if (TRUE == LucFlagFinalResult0)
  {
    GucFinalResult0 = "EXECUTED OK";
  }
  else
  {
    GucFinalResult0 = "EXECUTED NOT OK";
  }

  /* End trap */
  sample_end();
}

/*****************************************************************************
                        LIN Module Initialization
*****************************************************************************/
void Appl_Lin_Init(void)
{
  /* Initialise GpLinSduPtr_0 to application buffer */
  GpLinSduPtr_0 = &Lin_GaaDataArray1_0[0];
  /* Initialise GpRxDataPtr_0 to GpLinSduPtr_0 */
  GpRxDataPtr_0 = &GpLinSduPtr_0;

  #if (NON_RLININTCNTLREG == STD_ON)
  /* Enable the RLIN Tx/Rx/Status interrupt by using IC register */
  #if (DEVICE == U2Bx || DEVICE == U2BxE)
  /* RLIN30 */
  EIC621 = LIN_ENABLE_INTERRUPT;
  EIC622 = LIN_ENABLE_INTERRUPT;
  EIC623 = LIN_ENABLE_INTERRUPT;
  /* RLIN31 */
  EIC626 = LIN_ENABLE_INTERRUPT;
  EIC627 = LIN_ENABLE_INTERRUPT;
  EIC628 = LIN_ENABLE_INTERRUPT;
  /* RLIN32 */
  EIC631 = LIN_ENABLE_INTERRUPT;
  EIC632 = LIN_ENABLE_INTERRUPT;
  EIC633 = LIN_ENABLE_INTERRUPT;
  /* RLIN35 */
  EIC645 = LIN_ENABLE_INTERRUPT;
  EIC646 = LIN_ENABLE_INTERRUPT;
  EIC647 = LIN_ENABLE_INTERRUPT;
  #elif (DEVICE == U2Cx)
  /* RLIN30 */
  EIC174 = LIN_ENABLE_INTERRUPT;
  EIC175 = LIN_ENABLE_INTERRUPT;
  EIC176 = LIN_ENABLE_INTERRUPT;
  /* RLIN31 */
  EIC179 = LIN_ENABLE_INTERRUPT;
  EIC180 = LIN_ENABLE_INTERRUPT;
  EIC181 = LIN_ENABLE_INTERRUPT;
  /* RLIN32 */
  EIC184 = LIN_ENABLE_INTERRUPT;
  EIC185 = LIN_ENABLE_INTERRUPT;
  EIC186 = LIN_ENABLE_INTERRUPT;
  /* RLIN35 */
  EIC189 = LIN_ENABLE_INTERRUPT;
  EIC190 = LIN_ENABLE_INTERRUPT;
  EIC191 = LIN_ENABLE_INTERRUPT;
  #endif /* #if (DEVICE == U2Bx || DEVICE == U2BxE) */
  #else
  /* Enable the RLIN interrupt by using IC register */
  RLININTCNTLREG = LIN_ENABLE_INTERRUPT;
  #endif /* #if (NON_RLININTCNTLREG == STD_ON) */
  /* Global Initialisation */
  Lin_Init(Lin_Config);

  #if(LIN_VERSION_INFO_API == STD_ON)
  Std_VersionInfoType versionInfo;

  /* Invoke the API Lin_GetVersionInfo() to get the version information of LIN
     Driver */
  Lin_GetVersionInfo(&versionInfo);

  if((LIN_VENDOR_ID == versionInfo.vendorID) &&
     (LIN_MODULE_ID == versionInfo.moduleID) &&
     (LIN_SW_MAJOR_VERSION == versionInfo.sw_major_version) &&
     (LIN_SW_MINOR_VERSION == versionInfo.sw_minor_version) &&
     (LIN_SW_PATCH_VERSION == versionInfo.sw_patch_version))
  {
    GaaTestResult0[0] = 1;
  }
  else
  {
    GaaTestResult0[0] = 0;
  }
  #endif /* (LIN_VERSION_INFO_API == STD_ON) */
}

/*******************************************************************************
                              Timer Interrupt routine
*******************************************************************************/
/* 1 msec timer interrupt */
_INTERRUPT_ void Timer0_Interrupt(void)
{

}
/****************************************************************************
                          End of the file
****************************************************************************/
