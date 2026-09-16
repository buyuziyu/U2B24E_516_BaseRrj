/*============================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                         */
/* Module       = App_CAN_Multi_PostBuildVariant_Sample_1.c                   */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2024, 2025 Renesas Electronics Corporation. All rights reserved.       */
/*============================================================================*/
/* Purpose:                                                                   */
/* This application file contains execution sequences to demonstrate the usage*/
/* of CAN Driver APIs.                                                        */
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
 * 2.4.1: 30/06/2025  : Remove the SW-VERSION from header of file
 * 2.4.0: 30/05/2025  : Add Can_SetControllerMode in the end of the sequence
 * 2.3.1: 29/04/2025  : Update checkpoint conditions
 *        31/03/2025  : Update condition checkpoint
 *                      Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 * 2.3.0: 28/02/2025  : Update SW-VERSION for RH850/Ver22.01.00/Ver22.01.00.D 
 *                      Final Release
 * 2.2.0: 31/12/2024  : As part of CANXL support: Add macro CANXL
 *                      Update interrupt EIBD for U2Ax
 *                      Update sequence call Gpt 
 * 2.1.3: 31/10/2024  : Update to support CANXL frame, map interrupt ID
 * 2.1.2: 30/09/2024  : Update to support CANXL frame
 * 2.1.1: 12/08/2024  : Update Id, data length and data source for CAN XL 
 *                      controller transmission
 *        21/05/2024  : Change CAN_APPL_CODE to CAN_CALLOUT_CODE
 * 2.0.3: 09/04/2024  : Update to support postbuild variant
 * 2.0.2: 22/03/2024  : Initial Version
 */
/******************************************************************************/
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "App_CAN_Common_Sample_1.h"
#include "App_CAN_Multi_Sample.h"
#include "CanIf.h"
#include "Can_Ram.h"
/*******************************************************************************
**                     Global Variables                                       **
*******************************************************************************/
Can_ErrorStateType ErrorStatePtr_1;
uint8 TxErrorCounterPtr_1;
uint8 RxErrorCounterPtr_1;
uint8 LucReceiveValue_1;
#if (CAN_CANXL_SUPPORTED == STD_ON)
#if (CAN_CANXL_GLOBAL_TIME_SUPPORT == STD_ON)
Eth_TimeStampQualType RxTimeQual_1;
Eth_TimeStampType RxTimeStamp_1[2];
Eth_TimeStampQualType TxTimeQual_1;
Eth_TimeStampType TxTimeStamp_1[2];
#endif
#endif
volatile uint8 GucReturnCount_1 = 0;
Std_ReturnType GenCanReturn_1;
volatile Std_ReturnType GbOverallStatus_1 = CAN_COMMON_NOT_OK;
CONST(uint32, CAN_APPL_CONST) Can_GaaEIBDRegsInfoPE1[] =
{
  #ifndef CAN_U2Ax_USED
  #if defined(CAN_U2B12E_USED)
  655,1005,1006,1007,773,1020,1021,1022,36,344
  #elif defined(CAN_U2B24E_516_USED)
  657,612,613,614,781,1020,1021,1022,36,344
  #elif defined(CAN_U2B6E_USED)
  664,665,666,766,344,653
  #elif defined(CAN_U2Bx_USED)
  664,665,666,766,344,653
  #else
  119,
  120,
  114,
  105,
  344,
  664,
  665,
  666,
  490,
  491,
  492
  #endif
  #else
  400,
  323,
  324,
  325,
  326,
  #endif

};
/*******************************************************************************
*                       Global Symbols                                        **
*******************************************************************************/
void BoundIntToPE1(void);
/*******************************************************************************
*                       Function Definitions                                  **
*******************************************************************************/
int main_PE1(void)
{
  Can_PduType LddCanPduType;
  Can_ControllerStateType LenCanCntlState;
  #if !defined (CAN_U2B6E_USED)
  #if (CAN_CANXL_SUPPORTED == STD_ON)
  uint8 LucInc;
  boolean GucCheckStatus = TRUE;
  Std_ReturnType LucReturnValue = E_NOT_OK;
  CanXL_PduType LddCanXLPduType;
  CanXL_Params XLParamsInfo;
  #endif
  #endif
  uint8 LucHthId;
  volatile uint32 LulCount;
  volatile uint8 LucTransmitCountOld_1 = 0;
  volatile uint8 LucReceiveCountOld_1 = 0;
  BoundIntToPE1();
  ENABLE_INTERRUPT();
  while (GblCheckInit_1 == 0);
  /* Init after enable timer clock */
  Gpt_Init_1();

  GenCanReturn_1 = Can_SetBaudrate(
    CanConf_CanController_CanController1, 0);
  if (E_OK == GenCanReturn_1)
  {
    GucReturnCount_1++;
  }
  GenCanReturn_1 = Can_SetControllerMode(
    CanConf_CanController_CanController1, CAN_CS_STARTED);

  if (E_OK == GenCanReturn_1)
  {
    GucReturnCount_1++;
  }

  /* To get error state of CAN Driver */
  Can_GetControllerErrorState(
    CanConf_CanController_CanController1, &ErrorStatePtr_1);
  /* Check Active Error State of controller */
  if (CAN_ERRORSTATE_ACTIVE == ErrorStatePtr_1)
  {
    GucReturnCount_1++;
  }

  /* To get Tx error counter of CAN Driver */
  GenCanReturn_1 = Can_GetControllerTxErrorCounter(
    CanConf_CanController_CanController1, &TxErrorCounterPtr_1);
  /* Check return final value of controller */
  if (E_OK == GenCanReturn_1)
  {
    GucReturnCount_1++;
  }

  /* To get Rx error counter of CAN Driver */
  GenCanReturn_1 = Can_GetControllerRxErrorCounter(
    CanConf_CanController_CanController1, &RxErrorCounterPtr_1);
  /* Check return final value of controller */
  if (E_OK == GenCanReturn_1)
  {
    GucReturnCount_1++;
  }

  LucTransmitCountOld_1 = GucTransmitCount_1;
  LucReceiveCountOld_1 = GucReceiveCount_1;
  /* Transmit an L-PDU for Controller 1 */
  LucHthId = 3;
  LddCanPduType.length = 0x08;
  LddCanPduType.swPduHandle = 0x02;
  LddCanPduType.id = 0x058;
  LddCanPduType.sdu = &GaaByteArray0[0];
  GenCanReturn_1 = Can_Write(LucHthId, &LddCanPduType);
  if (E_OK == GenCanReturn_1)

  {
    GucReturnCount_1++;
  }
/* Following API can be invoked while entering a critical area where
  controller interrupts need to be disabled  */
  /* Following API disables RX, TX, Wakeup and BusOff Interrupts for
  CAN Controller 0  */
  Can_DisableControllerInterrupts(1);

  /* Following API can be invoked while exiting a critical area which enables
  all disabled interrupts */
  /* Following API enables RX, TX, Wakeup and BusOff Interrupts for
  CAN Controller 0  */
  Can_EnableControllerInterrupts(1);
  /* Put the Controller 0 into STOP Mode.
  CAN Controller will stop transmitting and receiving L-PDUs after this */
  
  /* waiting for receive*/
  LulCount = 1000000;
  while (LulCount--);
  if (((GucReceiveCount_1 - LucReceiveCountOld_1) == 1) && 
      ((GucTransmitCount_1 - LucTransmitCountOld_1) == 1))  
  {
    GucReturnCount_1++;
  }

  /* Change state to STOP mode */
  Can_SetControllerMode(CanConf_CanController_CanController1, CAN_CS_STOPPED);
  
  /* Wait for mode transition */
  LulCount = 100000;
  while (LulCount--)
  {
      GenCanReturn_1 = Can_GetControllerMode(
        CanConf_CanController_CanController1, &LenCanCntlState);
      if (E_OK == GenCanReturn_1 && CAN_CS_STOPPED == LenCanCntlState)
      {
        GucReturnCount_1++;
        break;
      }
      else
      {
        /* No action required */
      }
  }

  /* Put the Controller 0 into SLEEP mode
  Note: It is mandatory to put the Controller into STOP mode before
  requesting SLEEP mode.
  CAN Controller will be in SLEEP mode */
  GenCanReturn_1 = Can_SetControllerMode(
    CanConf_CanController_CanController1, CAN_CS_SLEEP);
  if (E_OK == GenCanReturn_1)
  {
    GucReturnCount_1++;
  }
  else
  {
    /* No action Required */
  }
  /* Wait for mode transition */
  LulCount = 100000;
  while (LulCount--)
  {
      GenCanReturn_1 = Can_GetControllerMode(
        CanConf_CanController_CanController1, &LenCanCntlState);
      if (E_OK == GenCanReturn_1 && CAN_CS_SLEEP == LenCanCntlState)
      {
        GucReturnCount_1++;
        break;
      }
      else
      {
        /* No action required */
      }
  }
  /* Put the Controller 0 to STOP Mode from SLEEP mode
  Note: Following API can be invoked to put the Controller into STOP mode
  from SLEEP mode */
  GenCanReturn_1 = Can_SetControllerMode(
    CanConf_CanController_CanController1, CAN_CS_STOPPED);
  if (E_OK == GenCanReturn_1)

  {
    GucReturnCount_1++;
  }

LulCount = 100000;
  while (LulCount--)
  {
      GenCanReturn_1 = Can_GetControllerMode(
        CanConf_CanController_CanController1, &LenCanCntlState);
      if (E_OK == GenCanReturn_1 && CAN_CS_STOPPED == LenCanCntlState)
      {
        GucReturnCount_1++;
        break;
      }
  }
/******************************************/ 
/* CANXL support post build variant 1     */
/******************************************/ 
#if !defined (CAN_U2B6E_USED)
#if (CAN_CANXL_SUPPORTED == STD_ON)
  Can_SetBaudrate(
    CanConf_CanController_CanController3, 0);
  GenCanReturn_1 = Can_SetControllerMode(
    CanConf_CanController_CanController3, CAN_CS_STARTED);
  /********************************/
  /*           CAN FRAME          */
  /********************************/
  /***************************************/
  /* Transmit an L-PDU for Controller 1  in CANXL  */
  /* TX FF Queue 4 */
  /***************************************/
  LucTransmitCountOld_1 = GucTransmitCount_1;
  LucReceiveCountOld_1 = GucReceiveCount_1;
  LucHthId = 2;
  LddCanXLPduType.length = 0x08;
  LddCanXLPduType.swPduHandle = 0x02;
  LddCanXLPduType.sdu = (uint8 *)&GaaByteArray0[0];
  LddCanXLPduType.XLParams = &XLParamsInfo;

  XLParamsInfo.PriorityId = 0x042;
  XLParamsInfo.Vcid = 0x000;
  XLParamsInfo.SduType = 0x01;
  XLParamsInfo.AcceptanceField = 0x80000097;
  XLParamsInfo.Sec = 0x00;
  GenCanReturn_1 = CanXL_Write(LucHthId, &LddCanXLPduType);

  if (E_OK == GenCanReturn_1)
  {
    GucReturnCount_1++;
  }
  LulCount = 1000000;
  while (LulCount--);

  /***************************************/
  /* Transmit an L-PDU for Controller 1  in CANXL  */
  /* TX FF Queue 6 */
  /***************************************/
  LucHthId = 3;
  LddCanXLPduType.length = 0x0800;
  LddCanXLPduType.swPduHandle = 0x03;
  LddCanXLPduType.sdu = (uint8 *)&GaaByteArray0[0];
  LddCanXLPduType.XLParams = &XLParamsInfo;

  XLParamsInfo.PriorityId = 0x043;
  XLParamsInfo.Vcid = 0x000;
  XLParamsInfo.SduType = 0x01;
  XLParamsInfo.AcceptanceField = 0x096;
  XLParamsInfo.Sec = 0x00;
  GenCanReturn_1 = CanXL_Write(LucHthId, &LddCanXLPduType);

  if (E_OK == GenCanReturn_1)
  {
    GucReturnCount_1++;
  }
  LulCount = 10000000;
  while (LulCount--);

  if (((GucReceiveCount_1 - LucReceiveCountOld_1) == 2) && 
      ((GucTransmitCount_1 - LucTransmitCountOld_1) == 2))
  {
    GucReturnCount_1++;
  }
  
  /********************************/
  /*           ETH FRAME          */
  /********************************/
  GenCanReturn_1 = CanXL_SetControllerMode(
    CanConf_CanController_CanController3, ETH_MODE_ACTIVE);
  if (E_OK == GenCanReturn_1)
  {
    GucReturnCount_1++;
  }
  CanXL_SetPhysAddr(CanConf_CanController_CanController3, mac_board_addr[1]);
  /* Invoke CanXL_GetPhysAddr to get physical address */
  CanXL_GetPhysAddr(CanConf_CanController_CanController3, (uint8*)RetrieveMacAddr[1]);
          
  for (LucInc = 0; LucInc < 6U; LucInc++)
  {
    if (RetrieveMacAddr[1][LucInc] != mac_board_addr[1][LucInc])
    {
      /* If the MAC address is incorrect */
      GucCheckStatus = FALSE;
    }
  }
  /* Check */
  if(TRUE == GucCheckStatus)
  {
    GucReturnCount_1++;
  }
  
  LucReturnValue = CanXL_UpdatePhysAddrFilter(CanConf_CanController_CanController3, mac_tgt_addr[1], ETH_ADD_TO_FILTER);
  if (E_OK == LucReturnValue)
  {
    GucReturnCount_1++;
  }
  uint16 LusDataLen = 63U;
  GusRxFrameCnt[1] = 0UL;
  Eth_FrameType LulEtherType = 0x8100; /* CVLAN */
  SendEthFrame(CanConf_CanController_CanController3, &TxEthFrame[2][0], LusDataLen, LulEtherType, 0, mac_tgt_addr[1]);

  #if (CAN_CANXL_GLOBAL_TIME_SUPPORT == STD_ON)
  if ((0UL != TxTimeStamp_1[1].seconds) || (0UL != TxTimeStamp_1[1].nanoseconds))
  {
    GucReturnCount_1++;
  }
  #endif
  /**************************************************************/
  /****************** Test receive for ETH Frame ****************/
  /**************************************************************/
  LenEthRxStatus[1] = ETH_NOT_RECEIVED;
  LulCounter = 0;
  do
  {
    LulCounter++;
  } while ((2UL != GusRxFrameCnt[1]) && (LulCounter < 100000));
  /* Check for received message with interrupt mode */
  if ((2UL == GusRxFrameCnt[1]) && (GusRxFrameType[1] == LulEtherType))
  {
    GucReturnCount_1++;
  }

  /* Check Eth data frame for controller 3 */
  for(LulCounter = 0UL; LulCounter < (uint32)LusDataLen; LulCounter++)
  {
    /* Compare Rx data with Tx Data */
    if (GaaRxEthFrame[1][LulCounter] != TxEthFrame[2][LulCounter])
    {
      /* Fail */
      break;
    }
  }
  if(LulCounter == (uint32)LusDataLen)
  {
    GucReturnCount_1++;
  }

  #if (CAN_CANXL_GLOBAL_TIME_SUPPORT == STD_ON)
  if ((RxTimeStamp_1[1].seconds > TxTimeStamp_1[1].seconds) ||
      ((RxTimeStamp_1[1].seconds == TxTimeStamp_1[1].seconds) && (RxTimeStamp_1[1].nanoseconds > TxTimeStamp_1[1].nanoseconds)))
  {
    GucReturnCount_1++;
  }
  #endif
  /* Wait for Core 0 Init Variant 1 for CANXL */
  GenCanReturn_1 = Can_SetControllerMode(
    CanConf_CanController_CanController3, CAN_CS_STARTED);

   /* Following API can be invoked while entering a critical area where controller interrupts need to be disabled  */
  Can_DisableControllerInterrupts(3);

  /* Following API can be invoked while entering a critical area where controller interrupts need to be enabled  */
  Can_EnableControllerInterrupts(3);
  
  LucTransmitCountOld_1 = GucTransmitCount_1;
  LucReceiveCountOld_1 = GucReceiveCount_1;
  LucHthId = 7;
  LddCanPduType.length = 0x08;
  LddCanPduType.swPduHandle = 0x02;
  LddCanPduType.id = 0x022;
  LddCanPduType.sdu = &GaaByteArray0[0];
  GenCanReturn_1 = Can_Write(LucHthId, &LddCanPduType);
  
  if (E_OK == GenCanReturn_1)
  {
    GucReturnCount_1++;
  }
  
  LulCount = 1000000;
  while (LulCount--);
  if (((GucReceiveCount_1 - LucReceiveCountOld_1) == 1) && 
      ((GucTransmitCount_1 - LucTransmitCountOld_1) == 1))
  {
    GucReturnCount_1++;
  }
  
  GenCanReturn_1 = Can_SetControllerMode(
    CanConf_CanController_CanController3, CAN_CS_STOPPED);
#endif /* (CAN_CANXL_SUPPORTED == STD_ON) */
#endif
  /* Core 1 done process remark */  
  GblDone_Core1 = 1;
  GblCheckInit_2 = 0;
  /* Wait for Core 0 De init */
  while (GblCheck_DeInit_Core0 == 0);
  GblCheck_DeInit_Core0 = 0;
/*******************************************************************************
*                                 VARIANT2                                    **
*******************************************************************************/
  /* Reinitialize CAN driver */
  Clock_Init();

  /* Initialize MCU */
  Mcu_Init();

  /* CAN Port Pin Configuration */
  Port_Init();
  /* Initialize Watchdog */
  Wdg_Init();
  Can_Init(Can_Config_Variant_2);

  /* Remark done init core 1 */
  GblCheckInit_1 = 0;

  GenCanReturn_1 = Can_SetBaudrate(
    CanConf_CanController_CanController1, 0);
  if (E_OK == GenCanReturn_1)
  {
    GucReturnCount_1++;
  }
  GenCanReturn_1 = Can_SetControllerMode(
    CanConf_CanController_CanController1, CAN_CS_STARTED);

  if (E_OK == GenCanReturn_1)
  {
    GucReturnCount_1++;
  }

  /* Transmit an L-PDU for Controller 1 */
  LucTransmitCountOld_1 = GucTransmitCount_1;
  LucReceiveCountOld_1 = GucReceiveCount_1;
  LucHthId = 3;
  LddCanPduType.length = 0x18;
  LddCanPduType.swPduHandle = 0x02;
  LddCanPduType.id = 0x075 | 0x40000000UL;
  LddCanPduType.sdu = &GaaByteArray0[0];
  GenCanReturn_1 = Can_Write(LucHthId, &LddCanPduType);
  if (E_OK == GenCanReturn_1)
  {
    GucReturnCount_1++;
  }
  else
  {
    /* No action Required */
  }
  LulCount = 1000000;
  while (LulCount--);
  if (((GucReceiveCount_1 - LucReceiveCountOld_1) == 1) && 
      ((GucTransmitCount_1 - LucTransmitCountOld_1) == 1))
  {
    GucReturnCount_1++;
  }
#if !defined (CAN_U2B6E_USED)
#if (CAN_CANXL_SUPPORTED == STD_ON)
  GenCanReturn_1 = Can_SetControllerMode(
    CanConf_CanController_CanController3, CAN_CS_STARTED);

  /* Following API can be invoked while entering a critical area where controller interrupts need to be disabled  */
  Can_DisableControllerInterrupts(3);
  
  /* Following API can be invoked while entering a critical area where controller interrupts need to be enabled  */
  Can_EnableControllerInterrupts(3);
  LucTransmitCountOld_1 = GucTransmitCount_1;
  LucReceiveCountOld_1 = GucReceiveCount_1;
  LucHthId = 7;
  LddCanPduType.length = 0x18;
  LddCanPduType.swPduHandle = 0x02;
  LddCanPduType.id = 0x075 | 0x40000000UL;
  LddCanPduType.sdu = &GaaByteArray0[0];
  GenCanReturn_1 = Can_Write(LucHthId, &LddCanPduType);
  
  if (E_OK == GenCanReturn_1)
  {
    GucReturnCount_1++;
  }
  
  LulCount = 1000000;
  while (LulCount--);
  if (((GucReceiveCount_1 - LucReceiveCountOld_1) == 1) && 
      ((GucTransmitCount_1 - LucTransmitCountOld_1) == 1))
  {
    GucReturnCount_1++;
  }
  
  GenCanReturn_1 = Can_SetControllerMode(
    CanConf_CanController_CanController3, CAN_CS_STOPPED);
#endif /* (CAN_CANXL_SUPPORTED == STD_ON) */
#endif
  if (GucReturnCount_1 == TOTAL_CHECKPOINT_MULTICORE_POSTBUILD_CORE1)
  {
    GbOverallStatus_1 = CAN_COMMON_OK;
  }
  Can_SetControllerMode(CanConf_CanController_CanController1, CAN_CS_STOPPED);
  Can_SampleApp_End();
  return TRUE;
}



/*******************************************************************************
*                          User Function                                      **
*******************************************************************************/

void BoundIntToPE1(void)
{
  uint32 LulIndex;
  int peid;
  peid = STSR(0, 2);
  if (peid == PEID_PE1_VALUE)
  {
    for (LulIndex = 0U;
      LulIndex < (sizeof(Can_GaaEIBDRegsInfoPE1) / sizeof(uint32)); LulIndex++)
    {
      CAN_EIBD2[Can_GaaEIBDRegsInfoPE1[LulIndex]] |= PEID_PE1_VALUE;
    }
  }
  else
  {
    // Do nothing since PE0 is default
  }
}

/*******************************************************************************
                          Scheduler Task
*******************************************************************************/
/* This is an example Scheduler Task. Invocation of following APIs might vary
   depending upon the mode and functionality */
_INTERRUPT_ FUNC(void, CAN_CALLOUT_CODE) Timer_Task_1(void)
{
  Can_MainFunction_Read();
  Can_MainFunction_Write();
  Can_MainFunction_BusOff();
  Can_MainFunction_Wakeup();
  Can_MainFunction_Mode();
}

/*******************************************************************************
                          End of the file
*******************************************************************************/
