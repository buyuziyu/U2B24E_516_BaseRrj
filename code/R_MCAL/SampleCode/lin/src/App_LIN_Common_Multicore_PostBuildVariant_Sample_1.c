/*============================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                         */
/* Module       = App_LIN_Common_Sample.c                                     */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2024-2025 Renesas Electronics Corporation. All rights reserved.        */
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
 *                       Add ASM_NOP() to support IAR compiler
 * 2.3.2:  25/04/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03
 *                       Release
 *                       Add ASM_NOP() to support CCRH compiler
 * 2.3.1:  31/03/2025  : Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02
 *                       Release
 * 2.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL
 *                       Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00(D) U2Bx Final Release
 * 2.1.2:  31/10/2024  : Update SW-VERSION
 * 2.1.1:  25/06/2024  : Update to support U2BxE
 * 2.0.3:  13/04/2024  : Initialize version for SA support multi-core and
 *                       post build variant
 */
/******************************************************************************/

/*******************************************************************************
**                     Include Section                                        **
*******************************************************************************/
#include "App_LIN_Multi_Sample.h"
#include "App_LIN_Device_Sample.h"
#include "App_LIN_Common_Sample_1.h"

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
void BoundIntToPE1(void);
/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/
#if (DEVICE == U2Bx || DEVICE == U2BxE)
CONST(uint32, LIN_APPL_CONST) Lin_GaaEIBDRegsInfoPE1[] =
{
  626,
  627,
  628
};
#elif (DEVICE == U2Cx)
CONST(uint32, LIN_APPL_CONST) Lin_GaaEIBDRegsInfoPE1[] =
{
  179,
  180,
  181
};
#elif (DEVICE == U2Ax)
CONST(uint32, LIN_APPL_CONST) Lin_GaaEIBDRegsInfoPE1[] =
{
  421,
  422,
  423
};
#endif /* #if (DEVICE == U2Bx || DEVICE == U2BxE) */

/* Global variable for Lin Pdu structure used in Lin_SendHeader and
 * Lin_SendResponse APIs */
Lin_PduType GddPduInfo_1;
/* Global variable to use in Lin_GetStatus API for function return type */
Lin_StatusType GenStatusType_1;
/* Global pointer used in Lin_GetStatus API as output parameter */
const uint8 ** GpRxDataPtr_1;
/* Global pointer used by GpRxDataPtr */
const uint8 *GpLinSduPtr_1;

/* Global data used as input parameter in Lin_SendResponse API */
uint8 Lin_GaaDataArray0_1[LIN_DATA_SIZE] = 
                      {(uint8)0x01U, (uint8)0x02U, (uint8)0x03U, (uint8)0x04U, 
                       (uint8)0x05U, (uint8)0x06U, (uint8)0x07U, (uint8)0x08U};
/* Global data used by GpLinSduPtr_0 for a default value */
uint8 Lin_GaaDataArray1_1[LIN_DATA_SIZE] = 
                      {(uint8)0xFFU, (uint8)0xFFU, (uint8)0xFFU, (uint8)0xFFU, 
                       (uint8)0xFFU, (uint8)0xFFU, (uint8)0xFFU, (uint8)0xFFU};
/* Global data used by check data receive*/
uint8 Lin_GaaDataReceiveArray1_1[LIN_DATA_SIZE] = 
                      {(uint8)0x03U, (uint8)0x03U, (uint8)0x03U, (uint8)0x03U, 
                       (uint8)0x03U, (uint8)0x03U, (uint8)0x03U, (uint8)0x03U};

/* Local variable to store the test result */
uint8 GaaTestResult1[12];

/* Local flag to hold final result*/
uint8 LucFlagFinalResult1= TRUE;

const char *GucFinalResult1;

/******************************************************************************
* F U N C T I O N    D E F I N I T I O N S
******************************************************************************/
int main_PE1(void)
{
  uint32 LulTimeOut = 0;
  uint8 LucStatus;
  
  /* Waiting for core 0 to complete init */
  while (GucStubInitFlag == 0);

  /* Bound interrupt to PE1 */
  ENABLE_INTERRUPT();
  
  BoundIntToPE1();

  /* Initialise GpLinSduPtr_1 to application buffer */
  GpLinSduPtr_1 = &Lin_GaaDataArray1_1[0];
  /* Initialise GpRxDataPtr_0 to GpLinSduPtr_0 */
  GpRxDataPtr_1 = &GpLinSduPtr_1;
  /* Intialize LIN channels of core 1 */
  /* Support MCU reset for post build variant */
  if (GET_BIT(APP_RESF, APP_MCU_RESF_BIT_POS) == APP_MCU_RST_FLAG_VALUE)
  {
    LIN_WAIT_MS(1000 * 1000); /* 1s */
    Lin_Init(Lin_Config_Variant_2);
  }
  else
  {
    Lin_Init(Lin_Config_Variant_1);
  }

  /* Set flag to indicate core 2 have been initialized */
  GucStubInitFlag = 0;

  LucStatus = Lin_WakeupInternal(LIN_CHANNEL_1);
  if (E_OK == LucStatus)
  {
    GaaTestResult1[0] = 1;
  }
  else
  {
    GaaTestResult1[0] = 0;
  }

  LucStatus = Lin_GoToSleepInternal(LIN_CHANNEL_1);
  if (E_OK == LucStatus)
  {
    GaaTestResult1[1] = 1;
  }
  else
  {
    GaaTestResult1[1] = 0;
  }

  LucStatus = Lin_WakeupInternal(LIN_CHANNEL_1);
  if (E_OK == LucStatus)
  {
    GaaTestResult1[2] = 1;
  }
  else
  {
    GaaTestResult1[2] = 0;
  }

  LucStatus = Lin_GoToSleep(LIN_CHANNEL_1);
  if (E_OK == LucStatus)
  {
    GaaTestResult1[3] = 1;
  }
  else
  {
    GaaTestResult1[3] = 0;
  }
  LulTimeOut = 0;
  LIN_WAIT_MS(500 * 1000); /* 500ms */

  if ((GenStatusType_1 = Lin_GetStatus(LIN_CHANNEL_1, GpRxDataPtr_1))
                                               == LIN_CH_SLEEP)
  {
    GaaTestResult1[4] = 1;
  }
  else
  {
    GaaTestResult1[4] = 0;
  }

  LucStatus = Lin_Wakeup(LIN_CHANNEL_1);
  if (E_OK == LucStatus)
  {
    GaaTestResult1[5] = 1;
  }
  else
  {
    GaaTestResult1[5] = 0;
  }
  LulTimeOut = 0;
  LIN_WAIT_MS(500 * 1000); /* 500ms */

  if ((GenStatusType_1 = Lin_GetStatus(LIN_CHANNEL_1, GpRxDataPtr_1))
                                               == LIN_OPERATIONAL)
  {
    GaaTestResult1[6] = 1;
  }
  else
  {
    GaaTestResult1[6] = 0;
  }

  LucStatus = Lin_CheckWakeup(LIN_CHANNEL_1);
  if (E_OK == LucStatus)
  {
    GaaTestResult1[7] = 1;
  }
  else
  {
    GaaTestResult1[7] = 0;
  }

  LucStatus = Lin_GoToSleepInternal(LIN_CHANNEL_1);
  if (E_OK == LucStatus)
  {
    GaaTestResult1[8] = 1;
  }
  else
  {
    GaaTestResult1[8] = 0;
  }

  /* Set the LIN PDU parameters for transmitting the LIN Frame */
  GddPduInfo_1.Pid = (uint8)LIN_SEND_PID;
  GddPduInfo_1.Cs = LIN_CLASSIC_CS;
  GddPduInfo_1.Drc = LIN_FRAMERESPONSE_TX;
  GddPduInfo_1.Dl = LIN_DATA_SIZE;

  GddPduInfo_1.SduPtr = Lin_GaaDataArray0_1;

  /* Following API is invoked to transmit the header and response part of a LIN
   * as Frame on the addressed LIN Channel
   */
  Lin_WakeupInternal(LIN_CHANNEL_1);

  LucStatus = Lin_SendFrame(LIN_CHANNEL_1, &GddPduInfo_1);

  /* Wait transmission complete */
  LulTimeOut = TEST_LIN_TRANSFER_DELAY_9600;

  while((GenStatusType_1 = Lin_GetStatus(LIN_CHANNEL_1, GpRxDataPtr_1))
                                               != LIN_TX_OK && (LulTimeOut > 0))
  {
    LulTimeOut--;
  }

  if (0 < LulTimeOut)
  {
    GaaTestResult1[9] = 1;
  }
  else
  {
    GaaTestResult1[9] = 0;
  }

  /* Set the LIN PDU parameters for receive the the LIN response */
  GddPduInfo_1.Pid = (uint8)LIN_RESP_PID;
  GddPduInfo_1.Cs = LIN_CLASSIC_CS;
  GddPduInfo_1.Drc = LIN_FRAMERESPONSE_RX;
  GddPduInfo_1.Dl = LIN_DATA_SIZE ;
  GddPduInfo_1.SduPtr = Lin_GaaDataArray1_1;

  /* Following API is invoked to transmit the header and receive the response
   * as part of a LIN Frame on the addressed LIN Channel
   */
  LucStatus = Lin_SendFrame(LIN_CHANNEL_1, &GddPduInfo_1);

  /* Wait transmission complete */
  LulTimeOut = TEST_LIN_TRANSFER_DELAY_9600;

  while((GenStatusType_1 = Lin_GetStatus(LIN_CHANNEL_1, GpRxDataPtr_1))
                                               != LIN_RX_OK && (LulTimeOut > 0))
  {
    LulTimeOut--;
  }

  /* Check channel received frame successfully */
  if (0 < LulTimeOut)
  {
    GaaTestResult1[10] = 1;
  }
  else
  {
    GaaTestResult1[10] = 0;
  }

  /* Check data receive from CANoe */
  if ((GpRxDataPtr_1[0][0] == Lin_GaaDataReceiveArray1_1[0]) &&
  (GpRxDataPtr_1[0][1] == Lin_GaaDataReceiveArray1_1[1]) &&
  (GpRxDataPtr_1[0][2] == Lin_GaaDataReceiveArray1_1[2]) &&
  (GpRxDataPtr_1[0][3] == Lin_GaaDataReceiveArray1_1[3]) &&
  (GpRxDataPtr_1[0][4] == Lin_GaaDataReceiveArray1_1[4]) &&
  (GpRxDataPtr_1[0][5] == Lin_GaaDataReceiveArray1_1[5]) &&
  (GpRxDataPtr_1[0][6] == Lin_GaaDataReceiveArray1_1[6]) &&
  (GpRxDataPtr_1[0][7] == Lin_GaaDataReceiveArray1_1[7]))
  {
    GaaTestResult1[11] = 1;
  }
  else
  {
    GaaTestResult1[11] = 0;
  }

  /*Loop through all checkpoint and set value to result flag*/
  for(uint8 count = 0; count < 12; count++)
  {
    if (FALSE == GaaTestResult1[count])
    {
        LucFlagFinalResult1 = FALSE;
    }
    else
    {
        //Do not thing
    }
  }

  /* Final Result*/
  if (TRUE == LucFlagFinalResult1)
  {
    GucFinalResult1 = "EXECUTED OK";
    /* Set flag to indicate core 1 stub modules have been completed variant */
    GucStubVariantFlag1 = 1;
  }
  else
  {
    GucFinalResult1 = "EXECUTED NOT OK";
  }

  /* Waiting for another core to complete variant */
  while (0 == GucStubVariantFlag0 || 0 == GucStubVariantFlag1)
  {
    ASM_NOP();//Do nothing
  }

  /* End trap */
  sample_end();
  return 0;
}

/*****************************************************************************
                        LIN Module Initialization
*****************************************************************************/
void BoundIntToPE1(void)
{
  uint32 LulIndex;
  int peid;
  peid = STSR(0, 2);
  if (peid == PEID_PE1_VALUE)
  {
    for (LulIndex = 0U;
      LulIndex < (sizeof(Lin_GaaEIBDRegsInfoPE1) / sizeof(uint32)); LulIndex++)
    {
      LIN_EIBD2[Lin_GaaEIBDRegsInfoPE1[LulIndex]] |= PEID_PE1_VALUE;
    }
  }
  else
  {
    // Do nothing since PE0 is default
  }
}

/*******************************************************************************
                              Timer Interrupt routine
*******************************************************************************/

/****************************************************************************
                          End of the file
****************************************************************************/
