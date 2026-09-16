/*============================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                         */
/* Module       = App_CAN_Common_Sample_0.c                                   */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2021-2025 Renesas Electronics Corporation. All rights reserved.        */
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
 * 2.1.3: 31/10/2024  : Update to support CANXL frame
 * 2.1.2: 30/09/2024  : Update to support CANXL frame
 * 2.1.1: 30/08/2024  : Update Id, checkpoint conditions for CAN XL controller
 *                    : Change CAN_APPL_CODE to CAN_CALLOUT_CODE
 *                    : Support multicore for CANXL
 *                    : Update condition of GucReturnCount_0 variable
 *                    : Remove macro U2Cx_VLAB_CAN_USED
 *                    : Support multicore for CANXL
 * 2.0.0: 09/08/2023  : Update to support Multicore
 *        14/07/2023  : Add AUTOSAR version R21-11
 * 1.0.2: 15/05/2022  : Add function Can_CheckBaudrate,  
 *                      AUTOSAR version 4.2.2
 *        10/05/2022  : Add function Can_GetControllerErrorState
 *                      AUTOSAR version 4.3.1
 * 1.0.1: 13/04/2022  : Update lulDlc to LucDlc
 * 1.0.0: 30/08/2021  : Initial Version
 */
/******************************************************************************/
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "App_CAN_Common_Sample_0.h"
#include "App_CAN_Multi_Sample.h"
#include "App_CAN_Device_Sample.h"
#include "CanIf.h"
#include "Can_Ram.h"

/*******************************************************************************
**                     Global Variables                                       **
*******************************************************************************/
/* Variable used to store the result of version information check*/

uint8 GucVerCheckStatus;
Can_ErrorStateType ErrorStatePtr_0;
uint8 TxErrorCounterPtr_0;
uint8 RxErrorCounterPtr_0;
#if (CAN_CANXL_SUPPORTED == STD_ON)
#if (CAN_CANXL_GLOBAL_TIME_SUPPORT == STD_ON)
Eth_TimeStampQualType RxTimeQual_0;
Eth_TimeStampType RxTimeStamp_0[2];
Eth_TimeStampQualType TxTimeQual_0;
Eth_TimeStampType TxTimeStamp_0[2];
#endif
#endif
volatile uint8 GucReturnCount_0 = 0;
Std_ReturnType GenCanReturn_0;
volatile Std_ReturnType GbOverallStatus_0 = CAN_COMMON_NOT_OK;
/*******************************************************************************
*                       Global Symbols                                        **
*******************************************************************************/

/******************************************************************************
*                       Function Definitions                                  **
******************************************************************************/
int main(void)
{
  Can_PduType LddCanPduType;
  Std_VersionInfoType versionInfo;
  Can_ControllerStateType LenCanCntlState;
  #if (CAN_CANXL_SUPPORTED == STD_ON)
  CanXL_PduType LddCanXLPduType;
  CanXL_Params XLParamsInfo;
  Eth_TxStatsType* TxStats = NULL_PTR;
  Eth_RxStatsType* RxStats = NULL_PTR;
  Eth_TxErrorCounterValuesType* TxErrorCounterValues = NULL_PTR;
  Eth_CounterType* CounterPtr = NULL_PTR;
  #endif
  uint8 LucHthId;
  volatile uint32 LulCount;
  uint8 LucTransmitCountOld_0 = 0;
  uint8 LucReceiveCountOld_0 = 0;
  /* CAN global as well as controller initialization and put the Controller
  into START mode */
  Appl_Can_Init();

  GenCanReturn_0 = Can_SetBaudrate(CanConf_CanController_CanController0, 0);
  if (E_OK == GenCanReturn_0)
  {
    GucReturnCount_0++;
  }
  /* Set Controller Mode to START Mode for Controller 0 and 1*/
  GenCanReturn_0 = Can_SetControllerMode(
                       CanConf_CanController_CanController0, CAN_CS_STARTED);
  if (E_OK == GenCanReturn_0)
  {
    GucReturnCount_0++;
  }

  /* To get error state of CAN Driver */
  Can_GetControllerErrorState(
    CanConf_CanController_CanController0, &ErrorStatePtr_0);
  /* Check Active Error State of controller */
  if (CAN_ERRORSTATE_ACTIVE == ErrorStatePtr_0)
  {
    GucReturnCount_0++;
  }

  /* To get Tx error counter of CAN Driver */
  GenCanReturn_0 = Can_GetControllerTxErrorCounter(
    CanConf_CanController_CanController0, &TxErrorCounterPtr_0);
  /* Check return final value of controller */
  if (E_OK == GenCanReturn_0)
  {
    GucReturnCount_0++;
  }

  /* To get Rx error counter of CAN Driver */
  GenCanReturn_0 = Can_GetControllerRxErrorCounter(
    CanConf_CanController_CanController0, &RxErrorCounterPtr_0);
  /* Check return final value of controller */
  if (E_OK == GenCanReturn_0)
  {
    GucReturnCount_0++;
  }

  /* To get the CAN Driver version information */
  Can_GetVersionInfo(&versionInfo);
  /* Check for the correctness of version information */
  if ((CAN_VENDOR_ID == versionInfo.vendorID) &&
    (CAN_MODULE_ID == versionInfo.moduleID) &&
    (CAN_SW_MAJOR_VERSION == versionInfo.sw_major_version) &&
    (CAN_SW_MINOR_VERSION == versionInfo.sw_minor_version) &&
    (CAN_SW_PATCH_VERSION == versionInfo.sw_patch_version))
  {
    GucVerCheckStatus = TRUE;
  }
  else
  {
    GucVerCheckStatus = FALSE;
  }

  ENABLE_INTERRUPT();

  /* Timer 0 Initialization  */
  Gpt_Init();

  #if (CAN_CANXL_SUPPORTED == STD_ON)

  Can_SetBaudrate(
    CanConf_CanController_CanController2, 0);

  GenCanReturn_0 = Can_SetControllerMode(
    CanConf_CanController_CanController2, CAN_CS_STARTED);

  /********************************/
  /*           CAN FRAME          */
  /********************************/
  /***************************************/
  /* Transmit an L-PDU for Controller 0  in CANXL  */
  /* TX FF Queue 0 */
  /***************************************/
  LucTransmitCountOld_0 = GucTransmitCount_0;
  LucReceiveCountOld_0 = GucReceiveCount_0;
  LucHthId = 0;
  LddCanXLPduType.length = 0x40;
  LddCanXLPduType.swPduHandle = 0x00;
  LddCanXLPduType.sdu = (uint8 *)&GaaByteArray64[0];
  LddCanXLPduType.XLParams = &XLParamsInfo;

  XLParamsInfo.PriorityId = 0x40;
  XLParamsInfo.Vcid = 0x000;
  XLParamsInfo.SduType = 0x03;
  XLParamsInfo.AcceptanceField = 0x80000099;
  XLParamsInfo.Sec = 0x00;
  GenCanReturn_0 = CanXL_Write(LucHthId, &LddCanXLPduType);

  if (E_OK == GenCanReturn_0)
  {
    GucReturnCount_0++;
  }
  
  LulCount = 100000;
  while (LulCount--);
  /***************************************/
  /* Transmit an L-PDU for Controller 0 in CANXL  */
  /* TX FF Queue 2 */
  /***************************************/
  LucHthId = 1;
  LddCanXLPduType.length = 0x40;
  LddCanXLPduType.swPduHandle = 0x01;
  LddCanXLPduType.sdu = (uint8 *)&GaaByteArray64[0];
  LddCanXLPduType.XLParams = &XLParamsInfo;

  XLParamsInfo.PriorityId = 0x041;
  XLParamsInfo.Vcid = 0x000;
  XLParamsInfo.SduType = 0x01;
  XLParamsInfo.AcceptanceField = 0x098;
  XLParamsInfo.Sec = 0x00;
  GenCanReturn_0 = CanXL_Write(LucHthId, &LddCanXLPduType);
  
  if (E_OK == GenCanReturn_0)
  {
    GucReturnCount_0++;
  }
  /***************************************/
  /* Receive FD00 obj:0 ID: 0x101        */
  /* Polling Transmit FD00               */
  /* Polling Receive FD00                */
  /***************************************/
  LulCount = 2000000;
  while (LulCount--);
  
  if (((GucReceiveCount_0 - LucReceiveCountOld_0) == 2) && 
      ((GucTransmitCount_0 - LucTransmitCountOld_0) == 2))
  {
    GucReturnCount_0++;
  }
  /********************************/
  /*           ETH FRAME          */
  /********************************/
  Std_ReturnType LucReturnValue = E_NOT_OK;
  boolean GucCheckStatus = TRUE;
  uint8 LucInc;
  
  /**************************************************************/
  /****************** Test sendata for ETH Frame ****************/
  /**************************************************************/
  GenCanReturn_0 = CanXL_SetControllerMode(
    CanConf_CanController_CanController2, ETH_MODE_ACTIVE);
  if (E_OK == GenCanReturn_0)
  {
    GucReturnCount_0++;
  }
  
  CanXL_SetPhysAddr(CanConf_CanController_CanController2, mac_board_addr[0]);
  /* Invoke CanXL_GetPhysAddr to get physical address */
  CanXL_GetPhysAddr(CanConf_CanController_CanController2, (uint8*)RetrieveMacAddr[0]);
  for (LucInc = 0; LucInc < 6U; LucInc++)
  {
    if (RetrieveMacAddr[0][LucInc] != mac_board_addr[0][LucInc])
    {
      /* If the MAC address is incorrect */
      GucCheckStatus = FALSE;
    }
  }
  /* Check */
  if(TRUE == GucCheckStatus)
  {
    GucReturnCount_0++;
  }
      
  LucReturnValue = CanXL_UpdatePhysAddrFilter(CanConf_CanController_CanController2, mac_tgt_addr[0], ETH_ADD_TO_FILTER);
  if (E_OK == LucReturnValue)
  {
    GucReturnCount_0++;
  }
  uint16 LusDataLen = 63U;
  Eth_FrameType LulEtherType = 0x6666;
  SendEthFrame(CanConf_CanController_CanController2, &TxEthFrame[0][0], LusDataLen, LulEtherType, 0, mac_tgt_addr[0]);
  
  #if (CAN_CANXL_GLOBAL_TIME_SUPPORT == STD_ON)
  if ((0UL != TxTimeStamp_0[0].seconds) || (0UL != TxTimeStamp_0[0].nanoseconds))
  {
    GucReturnCount_0++;
  }
  #endif
  /**************************************************************/
  /****************** Test receive for ETH Frame ****************/
  /**************************************************************/
  LenEthRxStatus[0] = ETH_NOT_RECEIVED;
  GusRxFrameCnt[0] = 0U;
  LulCounter = 0;
  while ((ETH_RECEIVED != LenEthRxStatus[0]) && (2U != GusRxFrameCnt[0]) && (LulCounter < 100000))
  {
    /* Check for received message with polling mode */
    CanXL_Receive(CanConf_CanController_CanController2, 0, &LenEthRxStatus[0]);
    LulCounter++;
  }
  if ((ETH_RECEIVED == LenEthRxStatus[0]) && (2U == GusRxFrameCnt[0]) && \
      (GusRxFrameType[0] == LulEtherType))
  {
    GucReturnCount_0++;
  }
  
  /* Check Eth data frame for controller 2 */
  for(LulCounter = 0UL; LulCounter < (uint32)LusDataLen; LulCounter++)
  {
    /* Compare Rx data with Tx Data */
    if (GaaRxEthFrame[0][LulCounter] != TxEthFrame[0][LulCounter])
    {
      /* Failed */
      break;
    }
  }
  if(LulCounter == (uint32)LusDataLen)
  {
    GucReturnCount_0++;
  }
  
  #if (CAN_CANXL_GLOBAL_TIME_SUPPORT == STD_ON)
  if ((RxTimeStamp_0[0].seconds > TxTimeStamp_0[0].seconds) ||
      ((RxTimeStamp_0[0].seconds == TxTimeStamp_0[0].seconds) && (RxTimeStamp_0[0].nanoseconds > TxTimeStamp_0[0].nanoseconds)))
  {
    GucReturnCount_0++;
  }
  #endif

  LucReturnValue = CanXL_GetTxErrorCounterValues(CanConf_CanController_CanController2, TxErrorCounterValues);
  if (LucReturnValue == E_NOT_OK)
  {
    GucReturnCount_0++;
  }

  LucReturnValue = CanXL_GetTxStats(CanConf_CanController_CanController2, TxStats);
  if (LucReturnValue == E_NOT_OK)
  {
    GucReturnCount_0++;
  }

  LucReturnValue = CanXL_GetRxStats(CanConf_CanController_CanController2, RxStats);
  if (LucReturnValue == E_NOT_OK)
  {
    GucReturnCount_0++;
  }

  LucReturnValue = CanXL_GetCounterValues(CanConf_CanController_CanController2, CounterPtr);
  if (LucReturnValue == E_NOT_OK)
  {
    GucReturnCount_0++;
  }
  /* Transmit an L-PDU for Controller 0 */
  LucTransmitCountOld_0 = GucTransmitCount_0;
  LucReceiveCountOld_0 = GucReceiveCount_0;
  LucHthId = 5;
  LddCanPduType.length = 0x08;
  LddCanPduType.swPduHandle = 0x02;
  LddCanPduType.id = 0x11;
  LddCanPduType.sdu = &GaaByteArray1[0];
  GenCanReturn_0 = Can_Write(LucHthId, &LddCanPduType);

  if (E_OK == GenCanReturn_0)
  {
    GucReturnCount_0++;
  }

  LulCount = 1000000;
  while (LulCount--);
  
  if (((GucReceiveCount_0 - LucReceiveCountOld_0) == 1) && 
      ((GucTransmitCount_0 - LucTransmitCountOld_0) == 1)) 
  {
    GucReturnCount_0++;
  }
  
  
  /* To get error state of CAN Driver */
  Can_GetControllerErrorState(
    CanConf_CanController_CanController2, &ErrorStatePtr_0);
  /* Check Active Error State of controller */
  if (CAN_ERRORSTATE_ACTIVE == ErrorStatePtr_0)
  {
    GucReturnCount_0++;
  }
  
  /* To get Tx error counter of CAN Driver */
  GenCanReturn_0 = Can_GetControllerTxErrorCounter(
    CanConf_CanController_CanController2, &TxErrorCounterPtr_0);
  /* Check return final value of controller */
  if (E_OK == GenCanReturn_0)
  {
    GucReturnCount_0++;
  }

  /* To get Rx error counter of CAN Driver */
  GenCanReturn_0 = Can_GetControllerRxErrorCounter(
    CanConf_CanController_CanController2, &RxErrorCounterPtr_0);
  /* Check return final value of controller */
  if (E_OK == GenCanReturn_0)
  {
    GucReturnCount_0++;
  }

  LulCount = 100000;
  while (LulCount--);
  #endif /* CAN_CANXL_SUPPORTED == STD_ON */
  /* Transmit an L-PDU for Controller 0 */
  LucTransmitCountOld_0 = GucTransmitCount_0;
  LucReceiveCountOld_0 = GucReceiveCount_0;
  LucHthId = 2;
  LddCanPduType.length = 0x08;
  LddCanPduType.swPduHandle = 0x02;
  LddCanPduType.id = 0x100;
  LddCanPduType.sdu = &GaaByteArray1[0];
  GenCanReturn_0 = Can_Write(LucHthId, &LddCanPduType);
  if (E_OK == GenCanReturn_0)
  {
    GucReturnCount_0++;
  }

  LulCount = 1000000;
  while (LulCount--);
  if (((GucReceiveCount_0 - LucReceiveCountOld_0) == 1) && 
      ((GucTransmitCount_0 - LucTransmitCountOld_0) == 1))
  {
    GucReturnCount_0++;
  }
  /* Following API can be invoked while entering a critical area where
  controller interrupts need to be disabled  */
  /* Following API disables RX, TX, Wakeup and BusOff Interrupts for
  CAN Controller 0  */
  Can_DisableControllerInterrupts(0);

  /* Following API can be invoked while exiting a critical area which enables
  all disabled interrupts */
  /* Following API enables RX, TX, Wakeup and BusOff Interrupts for
  CAN Controller 0  */
  Can_EnableControllerInterrupts(0);
  /* Put the Controller 0 into STOP Mode.
  CAN Controller will stop transmitting and receiving L-PDUs after this */
  GenCanReturn_0 = Can_SetControllerMode(
    CanConf_CanController_CanController0, CAN_CS_STOPPED);
  if (E_OK == GenCanReturn_0)
  {
    GucReturnCount_0++;
  }

  /* Wait for mode transition */
  LulCount = 100000;
  while (LulCount--)
  {
      GenCanReturn_0 = Can_GetControllerMode(
        CanConf_CanController_CanController0, &LenCanCntlState);
      if (E_OK == GenCanReturn_0 && CAN_CS_STOPPED == LenCanCntlState)
      {
        GucReturnCount_0++;
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
  GenCanReturn_0 = Can_SetControllerMode(
    CanConf_CanController_CanController0, CAN_CS_SLEEP);
  if (E_OK == GenCanReturn_0)
  {
    GucReturnCount_0++;
  }
  else
  {
    /* No action Required */
  }
  /* Wait for mode transition */
  LulCount = 100000;
  while (LulCount--)
  {
      GenCanReturn_0 = Can_GetControllerMode(
        CanConf_CanController_CanController0, &LenCanCntlState);
      if (E_OK == GenCanReturn_0 && CAN_CS_SLEEP == LenCanCntlState)
      {
        GucReturnCount_0++;
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
  GenCanReturn_0 = Can_SetControllerMode(
    CanConf_CanController_CanController0, CAN_CS_STOPPED);
  if (E_OK == GenCanReturn_0)

  {
    GucReturnCount_0++;
  }

  /* Wait for mode transition */
  LulCount = 100000;
  while (LulCount--)
  {
      GenCanReturn_0 = Can_GetControllerMode(
        CanConf_CanController_CanController0, &LenCanCntlState);
      if (E_OK == GenCanReturn_0 && CAN_CS_STOPPED == LenCanCntlState)
      {
        GucReturnCount_0++;
        break;
      }
  }
  /* Following API detects the wakeup event for controller 0 */
  GenCanReturn_0 = Can_CheckWakeup(0);

  if (E_NOT_OK == GenCanReturn_0)
  {
    GucReturnCount_0++;
  }
  else
  {
    /* No action Required */
  }
  /* Put the Controller 0 to START mode from STOP mode
  Note: Following API can be invoked to put the Controller into START mode
  from STOP mode. CAN Controller can receive/transmit an L-PDU after this */

  GenCanReturn_0 = Can_SetControllerMode(
    CanConf_CanController_CanController0, CAN_CS_STARTED);
  if (E_OK == GenCanReturn_0)

  {
    GucReturnCount_0++;
  }
  else
  {
    /* No action Required */
  }
 
  Can_SetControllerMode(CanConf_CanController_CanController0, CAN_CS_STOPPED);

  /* Wait for mode transition */
  LulCount = 100000;
  while (LulCount--)
  {
    GenCanReturn_0 = Can_GetControllerMode(
      CanConf_CanController_CanController0, &LenCanCntlState);
    if (E_OK == GenCanReturn_0 && CAN_CS_STOPPED == LenCanCntlState)
    {
        GucReturnCount_0++;
        break;
    }

  }
  
  #if (CAN_CANXL_SUPPORTED == STD_ON)
  GenCanReturn_0 = Can_SetControllerMode(
    CanConf_CanController_CanController2, CAN_CS_STOPPED);
  if (E_OK == GenCanReturn_0)

  {
    GucReturnCount_0++;
  }

 LulCount = 100000;
  while (LulCount--)
  {
      GenCanReturn_0 = Can_GetControllerMode(
        CanConf_CanController_CanController2, &LenCanCntlState);
      if (E_OK == GenCanReturn_0 && CAN_CS_STOPPED == LenCanCntlState)
      {
        GucReturnCount_0++;
        break;
      }
  }
  #endif
  /* Wait core 1 done */
  while (GblCheckInit == 1);
  Can_DeInit();

  /* Reinitialize CAN driver */
  Appl_Can_Init();

    /* Set Controller Mode to START Mode for Controller 0 and 1*/
  GenCanReturn_0 = Can_SetControllerMode(
                       CanConf_CanController_CanController0, CAN_CS_STARTED);
  if (E_OK == GenCanReturn_0)
  {
    GucReturnCount_0++;
  }

  /* Transmit an L-PDU for Controller 0 */
  LucTransmitCountOld_0 = GucTransmitCount_0;
  LucReceiveCountOld_0 = GucReceiveCount_0;
  LucHthId = 2;
  LddCanPduType.length = 0x08;
  LddCanPduType.swPduHandle = 0x02;
  LddCanPduType.id = 0x100;
  LddCanPduType.sdu = &GaaByteArray1[0];
  GenCanReturn_0 = Can_Write(LucHthId, &LddCanPduType);
  if (E_OK == GenCanReturn_0)
  {
    GucReturnCount_0++;
  }
  else
  {
    /* No action Required */
  }
  LulCount = 1000000;
  while (LulCount--);
  if (((GucReceiveCount_0 - LucReceiveCountOld_0) == 1) && 
      ((GucTransmitCount_0 - LucTransmitCountOld_0) == 1)) 
  {
    GucReturnCount_0++;
  }
  
  if (GucReturnCount_0 == TOTAL_CHECKPOINT_MULTICORE_SINGLEVARIANT_CORE0)
  {
    GbOverallStatus_0 = CAN_COMMON_OK;
  }
  Can_SetControllerMode(CanConf_CanController_CanController0, CAN_CS_STOPPED);
  /* End trap */
  Can_SampleApp_End();
}

/*******************************************************************************
                          Scheduler Task
*******************************************************************************/
/* This is an example Scheduler Task. Invocation of following APIs might vary
   depending upon the mode and functionality */
_INTERRUPT_ FUNC(void, CAN_CALLOUT_CODE) Timer_Task(void)
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
