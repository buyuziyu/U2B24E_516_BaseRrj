/*============================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                         */
/* Module       = App_CAN_Common_Sample.c                                     */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2019-2025 Renesas Electronics Corporation. All rights reserved.        */
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
 * 2.3.1: 31/03/2025  : Support core G4KH for U2Bx-E device
 *                    : Update condition checkpoint
 *                      Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 * 2.3.0: 28/02/2025  : Update SW-VERSION for RH850/Ver22.01.00/Ver22.01.00.D 
 *                      Final Release
 * 2.2.0: 31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final 
 *                      Release
 *                      Remove unuse setting for U2Ax
 * 2.1.3: 31/10/2024  : Update to support CANXL frame
 * 2.1.2: 30/09/2024  : Update to support CANXL frame
 * 2.1.1: 30/08/2024  : Update Id, checkpoint conditions for CAN XL controller
 *                    : Add EthPassedCount and EthCheckCount to be compatible 
 *                      with Eth stub files
 *                    : Update SampleApp to support DeInit and Wake-up feature
 *                      for CANXL
 *                    : Change CAN_APPL_CODE to CAN_CALLOUT_CODE
 *                    : Update to support U2Bx-E device
 *                    : Add macro CANXL_FRAME_SUPPORTED and CAN_U2C2_USED
 *                    : Remove U2Cx_VLAB_CAN_USED macro
 *                    : Update Sample Application to support CANXL
 *                      Remove macro U2Cx_VLAB_CAN_USED for support 
 *                      SetControllerMode to Start Mode and transmit/receive
 *                      by CANoe
 *                    : Support Sample App VLAB for U2C
 * 2.0.0: 29/03/2023  : Support AUTOSAR version 21.11
 * 1.3.4: 15/05/2022  : Add function Can_CheckBaudrate, Can_SetBaudrate 
 *                      AUTOSAR version 4.2.2
 *        10/05/2022  : Add function Can_GetControllerErrorState for 
 *                      AUTOSAR version 4.3.1
 * 1.3.3: 13/04/2022  : Update lulDlc to LucDlc
 * 1.3.2: 30/08/2021  : Update to add include Can.h to unify with
 *                      multi-instance sample app
 * 1.3.1: 05/05/2021  : Update the memory section, memclass, ptrclass to change
 *                      the CAN_RSCAN prefix to CAN
 *                      Update condition checks to place the macro
 *                      to the left side of equality comparisons
 * 1.2.0: 09/07/2020  : Release.
 * 1.1.0: 19/06/2020  : Release.
 * 1.0.1: 13/03/2020  : Correct parameter Can_ConfigSet_0 to Can_Config.
 *        10/02/2020  : Update Sample App to correct Baudate setting for each
 *                      Controller.
 *        06/02/2020  : Add Can_DeInit for sample application.
 *        03/02/2020  : Add the use of Can_GetControllerMode.
 *        20/01/2020  : Separate the calls of Can_SetControllerMode for
 *                      individual AR version 4.2.2 and 4.3.1
 *        16/01/2020  : Separate the parameter name of DLC in user callout
 *                      function for individual AR version 4.2.2 and 4.3.1
 *        13/01/2020  : Replace can Can_ChangeBaudrate with Can_SetBaudrate
 *                      comply with AR 4.3.1
 *        09/01/2020  : Support AUTOSAR version 4.3.1
 *                      - Use Common_ReturnType as representative of
 *                        Can_ReturnType and Std_ReturnType depending on
 *                        AUTOSAR Version
 * 1.0.0: 09/12/2019  : Initial Version
 */
/******************************************************************************/
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Can.h"
#include "App_Can_Common_Sample.h"
#include "CanIf.h"
#include "Can_Ram.h"
#include "App_CAN_Device_Sample.h"
/*******************************************************************************
**                     Global Variables                                       **
*******************************************************************************/

#define CAN_PASS '1'
#define CAN_FAIL '0'
#define CAN_EIBD2                         ((volatile uint32*)0xFFF82000UL)

/*******************************************************************************
*                       Global Symbols                                        **
*******************************************************************************/

/* Variable used to store the result of version information check*/
volatile Std_ReturnType GbOverallStatus = CAN_COMMON_NOT_OK;
uint8 GucVerCheckStatus;
void Appl_Can_Init(void);
void Appl_Scheduler_Task(void);
void Appl_CanXL_TestMode(uint32 LucControllerID);
uint8 GaaByteArray0[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
uint8 GaaByteArray1[] = { 0x02, 0x04, 0x06, 0x08, 0x01, 0x03, 0x05, 0x07};
uint8 GaaHohArray[CAN_NO_OF_HOHS];
Can_ErrorStateType ErrorStatePtr;
uint8 TxErrorCounterPtr;
uint8 RxErrorCounterPtr;
Std_ReturnType GenCanReturn;
uint8 GucTestResult[2];

#if (CAN_CANXL_SUPPORTED == STD_ON)
const uint8 GaaByteArrayXL0[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09};
const uint8 GaaByteArrayXL1[] = { 0x02, 0x04, 0x06, 0x08, 0x01, 0x03, 0x05, 0x07, 0x09};
const uint8 GaaByteArray64[] = {
    0x00U, 0x01U, 0x02U, 0x03U, 0x04U, 0x05U, 0x06U, 0x07U,
    0x08U, 0x09U, 0x0AU, 0x0BU, 0x0CU, 0x0DU, 0x0EU, 0x0FU,
    0x10U, 0x11U, 0x12U, 0x13U, 0x14U, 0x15U, 0x16U, 0x17U,
    0x18U, 0x19U, 0x1AU, 0x1BU, 0x1CU, 0x1DU, 0x1EU, 0x1FU,
    0x20U, 0x21U, 0x22U, 0x23U, 0x24U, 0x25U, 0x26U, 0x27U,
    0x28U, 0x29U, 0x2AU, 0x2BU, 0x2CU, 0x2DU, 0x2EU, 0x2FU,
    0x30U, 0x31U, 0x32U, 0x33U, 0x34U, 0x35U, 0x36U, 0x37U,
    0x38U, 0x39U, 0x3AU, 0x3BU, 0x3CU, 0x3DU, 0x3EU, 0x3FU
};
/* Eth variable */
Eth_ModeType EthControllerMode[2];
volatile uint8 GaaRxEthFrame[2][1522];
volatile uint8 GaaRxSrcAddr[2][6];
volatile Eth_FrameType GusRxFrameType[2];
volatile uint16 GusRxLenByte[2];
volatile uint16 GusRxFrameCnt[2];
volatile uint8 GucTxConfirmed[2];
volatile uint16 GusMsgLength[2];
/* Build only */
volatile uint8 EthPassedCount[70];
volatile uint8 EthCheckCount;
#if (CAN_CANXL_GLOBAL_TIME_SUPPORT == STD_ON)
Eth_TimeStampQualType RxTimeQual;
Eth_TimeStampType RxTimeStamp[2];
Eth_TimeStampQualType TxTimeQual;
Eth_TimeStampType TxTimeStamp[2];
#endif /* CAN_CANXL_GLOBAL_TIME_SUPPORT */
/* Target MAC address */
static uint8 mac_tgt_addr[2U][6U] =
{
  {0x75U, 0x90U, 0x50U, 0xFFU, 0xFFU, 0x00U}
  ,{0x75U, 0x90U, 0x50U, 0xFFU, 0xFFU, 0x01U}
};

static uint8 mac_board_addr[2U][6U] =
{
  {0x75U, 0x90U, 0x50U, 0x11U, 0x22U, 0x33U}
  ,{0x75U, 0x90U, 0x50U, 0x44U, 0x55U, 0x66U}
};

static uint8 RetrieveMacAddr[2][6] =
{
  {0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U}
  ,{0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U}
};
/*---------------------------------------------------*/
/* Receive and Transmit Buffers */
/*---------------------------------------------------*/
static uint8 TxEthFrame[6][63] =
{
  /* Index 0: Normal frame expected to get filter in Rx Queue 0 */
  {
    0x00U, 0x00U, 0x00U,
    0x01U, 0x02U, 0x03U, 0x04U, 0x05U, 0x06U, 0x07U, 0x08U, 0x09U, 0x0AU,
    0x0BU, 0x0CU, 0x0DU, 0x0EU, 0x0FU, 0x10U, 0x11U, 0x12U, 0x13U, 0x14U,
    0x15U, 0x16U, 0x17U, 0x18U, 0x19U, 0x1AU, 0x1BU, 0x1CU, 0x1DU, 0x1EU,
    0x1FU, 0x20U, 0x21U, 0x22U, 0x23U, 0x24U, 0x25U, 0x26U, 0x27U, 0x28U,
    0x29U, 0x2AU, 0x2BU, 0x2CU, 0x2DU, 0x2EU, 0x2FU, 0x30U, 0x31U, 0x32U,
    0x33U, 0x34U, 0x35U, 0x36U, 0x37U, 0x38U, 0x39U, 0x3AU, 0x3BU, 0x00U,
  },
  /* Index 1: Network control frame expected to get filter in Rx Queue 1 */
  {
    0xCCU, 0xCCU, 0xCCU,
    0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU,
    0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU,
    0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU,
    0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU,
    0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU,
    0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU,
  },
  /* Index 2: IEEE 1722 Frame expected to get filter in Rx Queue 2*/
  {
    /* Subtype and VICD = 0x42U*/
    0x7EU, 0x42U,
    /* MAAP version + MAAP data length */
    0x00U, 0x34U,
    /* Talker source address */
    0x11U, 0x22U, 0x33U, 0x44U, 0x55U, 0xFFU,
    /* Unique ID */
    0x00U, 0x00U,
    /* Control packet payload */
    0xDDU, 0xDDU, 0xDDU, 0xDDU, 0xDDU, 0xDDU, 0xDDU, 0xDDU, 0xDDU, 0xDDU,
    0xDDU, 0xDDU, 0xDDU, 0xDDU, 0xDDU, 0xDDU, 0xDDU, 0xDDU, 0xDDU, 0xDDU,
    0xDDU, 0xDDU, 0xDDU, 0xDDU, 0xDDU, 0xDDU, 0xDDU, 0xDDU, 0xDDU, 0xDDU,
    0xDDU, 0xDDU, 0xDDU, 0xDDU, 0xDDU, 0xDDU, 0xDDU, 0xDDU, 0xDDU, 0xDDU,
    0xDDU, 0xDDU, 0xDDU, 0xDDU, 0xDDU, 0xDDU, 0xDDU, 0xDDU, 0xDDU, 0xDDU, 0xDDU,
  },
  /* Index 3: IEEE 1722 Frame expected to get filter in Rx Queue 3*/
  {
    /* Subtype */
    0x7EU, 0x00U,
    /* MAAP version + MAAP data length */
    0x00U, 0x34U,
    /* Talker source address */
    0x11U, 0x22U, 0x33U, 0x44U, 0x55U, 0x00U,
    /* Unique ID */
    0x00U, 0x00U,
    /* Control packet payload */
    0xEEU, 0xEEU, 0xEEU, 0xEEU, 0xEEU, 0xEEU, 0xEEU, 0xEEU, 0xEEU, 0xEEU,
    0xEEU, 0xEEU, 0xEEU, 0xEEU, 0xEEU, 0xEEU, 0xEEU, 0xEEU, 0xEEU, 0xEEU,
    0xEEU, 0xEEU, 0xEEU, 0xEEU, 0xEEU, 0xEEU, 0xEEU, 0xEEU, 0xEEU, 0xEEU,
    0xEEU, 0xEEU, 0xEEU, 0xEEU, 0xEEU, 0xEEU, 0xEEU, 0xEEU, 0xEEU, 0xEEU,
    0xEEU, 0xEEU, 0xEEU, 0xEEU, 0xEEU, 0xEEU, 0xEEU, 0xEEU, 0xEEU, 0xEEU,
  },
  /* Index 4: Normal frame with known multicast address expected
     to get filter in Rx Queue 0 */
  {
    0xFFU, 0xFFU,
    0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU,
    0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU,
    0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU,
    0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU,
    0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU,
    0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU,
  },
  /* Index 5: IEEE 1722 Frame not match with Separation Filter
     and expected to get filter in Rx Queue 0 */
  {
    /* Subtype */
    0x7EU, 0x00U,
    /* MAAP version + MAAP data length */
    0x00U, 0x34U,
    /* Talker source address */
    0x11U, 0x22U, 0x33U, 0x44U, 0x55U, 0xAAU,
    /* Unique ID */
    0x00U, 0x00U,
    /* Control packet payload */
    0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
    0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
    0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
    0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
    0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
  }
};
Eth_RxStatusType LenEthRxStatus[2];
volatile uint32 LulCounter;
#endif /* CAN_CANXL_SUPPORTED */
#if defined (CAN_U2BxE_USED) && defined (RUN_OTHER_PE)
void Guard_Enable_PE(void);
boolean checkinit = false;
void BoundIntToPE6(void);
#endif

/******************************************************************************
*                       Function Definitions                                  **
******************************************************************************/
#if defined (CAN_U2BxE_USED) && defined (RUN_OTHER_PE)
void BoundIntToPE6(void)
{
  CONST(uint32, CAN_APPL_CONST) Can_GaaEIBDRegsInfoPE1[] =
  {
    #ifndef CAN_U2Ax_USED
    #if defined(CAN_U2B12E_USED)
    1005,1006,1007,773,1020,1021,1022,36,344,1005,1006,1007,653,655
    #elif defined(CAN_U2B24E_516_USED)
    612,613,614,781,1020,1021,1022,36,344,863,864,865,1005,1006,1007,653,655,657
    #else
    114,
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
    301,
    302,
    303
    #endif
  };
  uint32 LulIndex;
  int peid;
  peid = STSR(0, 2);
  if (peid == 0x06)
  {
    for (LulIndex = 0U;
      LulIndex < (sizeof(Can_GaaEIBDRegsInfoPE1) / sizeof(uint32)); LulIndex++)
    {
      CAN_EIBD2[Can_GaaEIBDRegsInfoPE1[LulIndex]] |= 0x06;
    }
  }
  else
  {
    // Do nothing since PE0 is default
  }
}
#endif

#if (CAN_CANXL_SUPPORTED == STD_ON)
void SendEthFrame( uint8 CtrlIdx, uint8 *Buf, uint16 LenByte, Eth_FrameType FrameType,
                   uint8 Priority, const uint8* PhysAddrPtr);
#endif /* CAN_CANXL_SUPPORTED */

void sample_end(void)
{
  while (1)
  {
    /* No action required*/
  }
}

int main(void)
#if defined (CAN_U2BxE_USED) && defined (RUN_OTHER_PE)
{
  Guard_Enable_PE();
  checkinit = true;
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
  Can_PduType LddCanPduType;
  Std_VersionInfoType versionInfo;
  #if (CAN_CANXL_SUPPORTED == STD_ON)
  CanXL_PduType LddCanXLPduType;
  CanXL_Params XLParamsInfo;
  Eth_TxStatsType* TxStats = NULL_PTR;
  Eth_RxStatsType* RxStats = NULL_PTR;
  Eth_TxErrorCounterValuesType* TxErrorCounterValues = NULL_PTR;
  Eth_CounterType* CounterPtr = NULL_PTR;
  #endif
  uint8 LucTransmitCountOld = 0;
  uint8 LucReceiveCountOld = 0;
  Can_ControllerStateType LenCanCntlState;
  uint8 LucHthId;
  volatile uint32 LulCount;

  /* System Initialization
  (Clock Initialization, Programmable Peripheral I/O register,
  Selecting the clock for the CAN Module ETC..) */
  #if defined (CAN_U2BxE_USED) && defined (RUN_OTHER_PE)
  while(checkinit == false);
  #endif
  Clock_Init();
  /* Initialize MCU */
  Mcu_Init();
  /* CAN Port Pin Configuration */
  Port_Init();
  /* Initialize Watchdog */
  Wdg_Init();

  /* CAN global as well as controller initialization and put the Controller
  into START mode */
  Appl_Can_Init();
  #if defined (CAN_U2BxE_USED) && defined (RUN_OTHER_PE)
  BoundIntToPE6();
  #endif

  LulCount = 100000;/*temp*/
  while (LulCount--);/*temp*/

  /* To get error state of CAN Driver */
  Can_GetControllerErrorState(
    CanConf_CanController_CanController0, &ErrorStatePtr);
  /* Check Active Error State of controller */
  if (CAN_ERRORSTATE_ACTIVE == ErrorStatePtr)
  {
    GucReturnCount++;
  }

  /* To get Tx error counter of CAN Driver */
  GenCanReturn = Can_GetControllerTxErrorCounter(
    CanConf_CanController_CanController0, &TxErrorCounterPtr);
  /* Check return final value of controller */
  if (E_OK == GenCanReturn)
  {
    GucReturnCount++;
  }

  /* To get Rx error counter of CAN Driver */
  GenCanReturn = Can_GetControllerRxErrorCounter(
    CanConf_CanController_CanController0, &RxErrorCounterPtr);
  /* Check return final value of controller */
  if (E_OK == GenCanReturn)
  {
    GucReturnCount++;
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
  
  #if defined (CAN_U2BxE_USED) && defined (RUN_OTHER_PE)
  CAN_EIC_EIBDOSTM = 0x06;
  #endif

  ENABLE_INTERRUPT();

  /* Timer 0 Initialization  */
  Gpt_Init();
  
  //Switch_To_ControllerId(0);
  LucTransmitCountOld = GucTransmitCount;
  LucReceiveCountOld = GucReceiveCount;
  /* Transmit an L-PDU for Controller 0 */
  LucHthId = 2;
  LddCanPduType.length = 0x08;
  LddCanPduType.swPduHandle = 0x02;
  LddCanPduType.id = 0x100;
  LddCanPduType.sdu = &GaaByteArray1[0];
  GenCanReturn = Can_Write(LucHthId, &LddCanPduType);

  if (E_OK == GenCanReturn)
  {
    GucReturnCount++;
  }

  LulCount = 1000000;
  while (LulCount--);
  
  if (((GucReceiveCount - LucReceiveCountOld) == 1) && 
      ((GucTransmitCount - LucTransmitCountOld) == 1))
  {
    GucReturnCount++;
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

  GenCanReturn = Can_SetControllerMode(
    CanConf_CanController_CanController0, CAN_CS_STOPPED);
  if (E_OK == GenCanReturn)
  {
    GucReturnCount++;
  }
  else
  {
    /* No action Required */
  }
  /* Wait for mode transition */
  LulCount = 100000;
  while (LulCount--)
  {
    GenCanReturn = Can_GetControllerMode(
    CanConf_CanController_CanController0, &LenCanCntlState);
    if (E_OK == GenCanReturn && CAN_CS_STOPPED == LenCanCntlState)
    {
      GucReturnCount++;
      break;
    }
    else
    {
      /* No action required */
    }
  }

#if (CAN_WAKEUP_SUPPORT == STD_ON)
  /* Put the Controller 0 into SLEEP mode
  Note: It is mandatory to put the Controller into STOP mode before
  requesting SLEEP mode.
  CAN Controller will be in SLEEP mode */

  GenCanReturn = Can_SetControllerMode(
    CanConf_CanController_CanController0, CAN_CS_SLEEP);
  if (E_OK == GenCanReturn)
  {
    GucReturnCount++;
  }
  else
  {
    /* No action Required */
  }
  /* Wait for mode transition */
  LulCount = 100000;
  while (LulCount--)
  {
    GenCanReturn = Can_GetControllerMode(
    CanConf_CanController_CanController0, &LenCanCntlState);
    if (E_OK == GenCanReturn && CAN_CS_SLEEP == LenCanCntlState)
    {
      GucReturnCount++;
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

  GenCanReturn = Can_SetControllerMode(
    CanConf_CanController_CanController0, CAN_CS_STOPPED);
  if (E_OK == GenCanReturn)
  {
    GucReturnCount++;
  }
  else
  {
    /* No action Required */
  }
  /* Wait for mode transition */
  LulCount = 100000;
  while (LulCount--)
  {
    GenCanReturn = Can_GetControllerMode(
    CanConf_CanController_CanController0, &LenCanCntlState);
    if (E_OK == GenCanReturn && CAN_CS_STOPPED == LenCanCntlState)
    {
      GucReturnCount++;
      break;
    }
    else
    {
       /* No action required */
    }
  }
  /* Following API detects the wakeup event for controller 0 */
  GenCanReturn = Can_CheckWakeup(0);
  if (E_NOT_OK == GenCanReturn)
  {
    GucReturnCount++;
  }
  else
  {
    /* No action Required */
  }
#endif /*#if (CAN_WAKEUP_SUPPORT == STD_ON)*/

  /* Put the Controller 0 to START mode from STOP mode
  Note: Following API can be invoked to put the Controller into START mode
  from STOP mode. CAN Controller can receive/transmit an L-PDU after this */

  GenCanReturn = Can_SetControllerMode(
    CanConf_CanController_CanController0, CAN_CS_STARTED);
  if (E_OK == GenCanReturn)
  {
    GucReturnCount++;
  }
  else
  {
    /* No action Required */
  }
  //Switch_To_ControllerId(1);
  LucTransmitCountOld = GucTransmitCount;
  LucReceiveCountOld = GucReceiveCount;
  /* Transmit an L-PDU for Controller 0 */
  LucHthId = 3;
  LddCanPduType.length = 0x08;
  LddCanPduType.swPduHandle = 0x02;
  LddCanPduType.id = 0x058;
  LddCanPduType.sdu = &GaaByteArray0[0];
  GenCanReturn = Can_Write(LucHthId, &LddCanPduType);

  if (E_OK == GenCanReturn)
  {
    GucReturnCount++;
  }
  else
  {
    /* No action Required */
  }
  LulCount = 1000000;
  while (LulCount--);

  if (((GucReceiveCount - LucReceiveCountOld) == 1) && 
      ((GucTransmitCount - LucTransmitCountOld) == 1))
  {
    GucReturnCount++;
  }

#ifdef CAN_U2B24E_516_USED
  Switch_To_ControllerId(4);
  LucTransmitCountOld = GucTransmitCount;
  LucReceiveCountOld = GucReceiveCount;
  /* Transmit an L-PDU for Controller 0 */
  LucHthId = 9;
  LddCanPduType.length = 0x08;
  LddCanPduType.swPduHandle = 0x02;
  LddCanPduType.id = 0x0022;
  LddCanPduType.sdu = &GaaByteArray0[0];
  GenCanReturn = Can_Write(LucHthId, &LddCanPduType);

  if (E_OK == GenCanReturn)
  {
    GucReturnCount++;
  }
  else
  {
    /* No action Required */
  }
  LulCount = 1000000;
  while (LulCount--);

  if (((GucReceiveCount - LucReceiveCountOld) == 1) && 
      ((GucTransmitCount - LucTransmitCountOld) == 1))
  {
    GucReturnCount++;
  }
#endif

  /* Sample app support for de-initialization feature */
  Can_SetControllerMode(CanConf_CanController_CanController0, CAN_CS_STOPPED);
  Can_SetControllerMode(CanConf_CanController_CanController1, CAN_CS_STOPPED);
  #ifdef CAN_U2B24E_516_USED
  Can_SetControllerMode(CanConf_CanController_CanController4, CAN_CS_STOPPED);
  #endif
  #if (CAN_CANXL_SUPPORTED == STD_ON)
  Can_SetControllerMode(CanConf_CanController_CanController2, CAN_CS_STOPPED);
  #if (!defined CAN_U2C2_USED) && (!defined CAN_U2B6E_USED)
  Can_SetControllerMode(CanConf_CanController_CanController3, CAN_CS_STOPPED);
  #endif
  #endif
  /* Wait for mode transition */
  LulCount = 100000;
  while (LulCount--)
  {
    GenCanReturn = Can_GetControllerMode(
      CanConf_CanController_CanController0, &LenCanCntlState);
    if (E_OK == GenCanReturn && CAN_CS_STOPPED == LenCanCntlState)
    {
      GenCanReturn = Can_GetControllerMode(
        CanConf_CanController_CanController1, &LenCanCntlState);
      if (E_OK == GenCanReturn && CAN_CS_STOPPED == LenCanCntlState)
      {
        #ifdef CAN_U2B24E_516_USED
        GenCanReturn = Can_GetControllerMode(
          CanConf_CanController_CanController4, &LenCanCntlState);
        if (E_OK == GenCanReturn && CAN_CS_STOPPED == LenCanCntlState)
        #endif
        {
          GucReturnCount++;
          break;
        }
        #ifdef CAN_U2B24E_516_USED
        else
        {
          /* No action required */
        }
        #endif
      }
      else
      {
        /* No action required */
      }
    }
    else
    {
      /* No action required */
    }

  }
  
  Can_DeInit();

  /* Reinitialize CAN driver */
  Appl_Can_Init();
  
  Switch_To_ControllerId(0);
  LucTransmitCountOld = GucTransmitCount;
  LucReceiveCountOld = GucReceiveCount;
  /* Transmit an L-PDU for Controller 0 */
  LucHthId = 2;
  LddCanPduType.length = 0x08;
  LddCanPduType.swPduHandle = 0x02;
  LddCanPduType.id = 0x100;
  LddCanPduType.sdu = &GaaByteArray1[0];
  GenCanReturn = Can_Write(LucHthId, &LddCanPduType);
  if (E_OK == GenCanReturn)
  {
    GucReturnCount++;
  }
  else
  {
    /* No action Required */
  }
  LulCount = 1000000;
  while (LulCount--);
  if (((GucReceiveCount - LucReceiveCountOld) == 1) && 
      ((GucTransmitCount - LucTransmitCountOld) == 1))
  {
    GucReturnCount++;
  }

  #if (CAN_CANXL_SUPPORTED == STD_ON)
  LucTransmitCountOld = GucTransmitCount;
  LucReceiveCountOld = GucReceiveCount;
  /***************************************/
  /* Transmit an L-PDU for Controller 0  in CANXL  */
  /* TX FF Queue 0 */
  /***************************************/
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
  GenCanReturn = CanXL_Write(LucHthId, &LddCanXLPduType);

  if (E_OK == GenCanReturn)
  {
    GucReturnCount++;
  }

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
  GenCanReturn = CanXL_Write(LucHthId, &LddCanXLPduType);
  
  if (E_OK == GenCanReturn)
  {
    GucReturnCount++;
  }
  /***************************************/
  /* Receive FD00 obj:0 ID: 0x101         */
  /* Polling Transmit FD00                */
  /* Polling Receive FD00                 */
  /***************************************/
  /* Confirm transmission */
  LulCount = 1000000;
  while (LulCount--);

  if (((GucReceiveCount - LucReceiveCountOld) == 2) && 
      ((GucTransmitCount - LucTransmitCountOld) == 2))
  {
    GucReturnCount++;
  }

#if (!defined CAN_U2C2_USED) && (!defined CAN_U2B6E_USED)
  LucTransmitCountOld = GucTransmitCount;
  LucReceiveCountOld = GucReceiveCount;
  /***************************************/
  /* Transmit an L-PDU for Controller 1  in CANXL  */
  /* TX FF Queue 4 */
  /***************************************/
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
  GenCanReturn = CanXL_Write(LucHthId, &LddCanXLPduType);

  if (E_OK == GenCanReturn)
  {
    GucReturnCount++;
  }

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
  GenCanReturn = CanXL_Write(LucHthId, &LddCanXLPduType);

  if (E_OK == GenCanReturn)
  {
    GucReturnCount++;
  }

  LulCount = 2000000;
  while (LulCount--);

  if (((GucReceiveCount - LucReceiveCountOld) == 2) && 
      ((GucTransmitCount - LucTransmitCountOld) == 2))
  {
    GucReturnCount++;
  }
  #endif

  Std_ReturnType LucReturnValue = E_NOT_OK;
  boolean GucCheckStatus = TRUE;
  uint8 LucInc;

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
    GucReturnCount++;
  }
      
  LucReturnValue = CanXL_UpdatePhysAddrFilter(CanConf_CanController_CanController2, mac_tgt_addr[0], ETH_ADD_TO_FILTER);
  if (E_OK == LucReturnValue)
  {
    GucReturnCount++;
  }
  
  /**************************************************************/
  /****************** Test sendata for ETH Frame ****************/
  /**************************************************************/
  uint16 LusDataLen = 63U;
  Eth_FrameType LulEtherType = 0x6666;
  SendEthFrame(CanConf_CanController_CanController2, &TxEthFrame[0][0], LusDataLen, LulEtherType, 0, mac_tgt_addr[0]);
  
  #if (CAN_CANXL_GLOBAL_TIME_SUPPORT == STD_ON)
  if ((0UL != TxTimeStamp[0].seconds) || (0UL != TxTimeStamp[0].nanoseconds))
  {
    GucReturnCount++;
  }
  #endif
  /**************************************************************/
  /****************** Test receive for ETH Frame ****************/
  /**************************************************************/
  LenEthRxStatus[0] = ETH_NOT_RECEIVED;
  GusRxFrameCnt[0] = 0U;
  LulCounter = 0;
  while ((ETH_RECEIVED != LenEthRxStatus[0]) && (2U != GusRxFrameCnt[0]) && (LulCounter < 1000))
  {
    /* Check for received message with polling mode */
    CanXL_Receive(CanConf_CanController_CanController2, 0, &LenEthRxStatus[0]);
    LulCounter++;
  }
  if ((ETH_RECEIVED == LenEthRxStatus[0]) && (2U == GusRxFrameCnt[0]) && \
      (GusRxFrameType[0] == LulEtherType))
  {
    GucReturnCount++;
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
    GucReturnCount++;
  }
  #if (CAN_CANXL_GLOBAL_TIME_SUPPORT == STD_ON)
  if ((RxTimeStamp[0].seconds > TxTimeStamp[0].seconds) ||
      ((RxTimeStamp[0].seconds == TxTimeStamp[0].seconds) && (RxTimeStamp[0].nanoseconds > TxTimeStamp[0].nanoseconds)))
  {
    GucReturnCount++;
  }
  #endif
  /**************************************************************/
  /****************** Test sendata for ETH Frame ****************/
  /**************************************************************/
  #if (!defined CAN_U2C2_USED) && (!defined CAN_U2B6E_USED)
  LucReturnValue = E_NOT_OK;
  GucCheckStatus = TRUE;
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
    GucReturnCount++;
  }
  
  LucReturnValue = CanXL_UpdatePhysAddrFilter(CanConf_CanController_CanController3, mac_tgt_addr[1], ETH_ADD_TO_FILTER);
  if (E_OK == LucReturnValue)
  {
    GucReturnCount++;
  }
  LusDataLen = 63U;
  GusRxFrameCnt[1] = 0UL;
  LulEtherType = 0x8100; /* CVLAN */
  SendEthFrame(CanConf_CanController_CanController3, &TxEthFrame[2][0], LusDataLen, LulEtherType, 0, mac_tgt_addr[1]);

  #if (CAN_CANXL_GLOBAL_TIME_SUPPORT == STD_ON)
  if ((0UL != TxTimeStamp[1].seconds) || (0UL != TxTimeStamp[1].nanoseconds))
  {
    GucReturnCount++;
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
  } while ((2UL != GusRxFrameCnt[1]) && (LulCounter < 1000));
  /* Check for received message with interrupt mode */
  if ((2UL == GusRxFrameCnt[1]) && (GusRxFrameType[1] == LulEtherType))
  {
    GucReturnCount++;
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
    GucReturnCount++;
  }
  
  #if (CAN_CANXL_GLOBAL_TIME_SUPPORT == STD_ON)
  if ((RxTimeStamp[1].seconds > TxTimeStamp[1].seconds) ||
      ((RxTimeStamp[1].seconds == TxTimeStamp[1].seconds) && (RxTimeStamp[1].nanoseconds > TxTimeStamp[1].nanoseconds)))
  {
    GucReturnCount++;
  }
  #endif
  #endif
  LucReturnValue = CanXL_GetTxErrorCounterValues(CanConf_CanController_CanController2, TxErrorCounterValues);
  if (LucReturnValue == E_NOT_OK)
  {
    GucReturnCount++;
  }

  LucReturnValue = CanXL_GetTxStats(CanConf_CanController_CanController2, TxStats);
  if (LucReturnValue == E_NOT_OK)
  {
    GucReturnCount++;
  }

  LucReturnValue = CanXL_GetRxStats(CanConf_CanController_CanController2, RxStats);
  if (LucReturnValue == E_NOT_OK)
  {
    GucReturnCount++;
  }

  LucReturnValue = CanXL_GetCounterValues(CanConf_CanController_CanController2, CounterPtr);
  if (LucReturnValue == E_NOT_OK)
  {
    GucReturnCount++;
  }

  LucTransmitCountOld = GucTransmitCount;
  LucReceiveCountOld = GucReceiveCount;
  /* Transmit an L-PDU for Controller 0 */
  LucHthId = 5;
  LddCanPduType.length = 0x08;
  LddCanPduType.swPduHandle = 0x02;
  LddCanPduType.id = 0x11;
  LddCanPduType.sdu = &GaaByteArray1[0];
  GenCanReturn = Can_Write(LucHthId, &LddCanPduType);
  
  if (E_OK == GenCanReturn)
  {
    GucReturnCount++;
  }
  
  LulCount = 100000;
  while (LulCount--);
  
  if (((GucReceiveCount - LucReceiveCountOld) == 1) && 
      ((GucTransmitCount - LucTransmitCountOld) == 1))
  {
    GucReturnCount++;
  }
  
  /* To get error state of CAN Driver */
  Can_GetControllerErrorState(
    CanConf_CanController_CanController2, &ErrorStatePtr);
  /* Check Active Error State of controller */
  if (CAN_ERRORSTATE_ACTIVE == ErrorStatePtr)
  {
    GucReturnCount++;
  }
  
  /* To get Tx error counter of CAN Driver */
  GenCanReturn = Can_GetControllerTxErrorCounter(
    CanConf_CanController_CanController2, &TxErrorCounterPtr);
  /* Check return final value of controller */
  if (E_OK == GenCanReturn)
  {
    GucReturnCount++;
  }

  /* To get Rx error counter of CAN Driver */
  GenCanReturn = Can_GetControllerRxErrorCounter(
    CanConf_CanController_CanController2, &RxErrorCounterPtr);
  /* Check return final value of controller */
  if (E_OK == GenCanReturn)
  {
    GucReturnCount++;
  }
  
#if (!defined CAN_U2C2_USED) && (!defined CAN_U2B6E_USED)
  LucTransmitCountOld = GucTransmitCount;
  LucReceiveCountOld = GucReceiveCount;
  Can_DisableControllerInterrupts(3);
  
  Can_EnableControllerInterrupts(3);
  
  LucHthId = 7;
  LddCanPduType.length = 0x08;
  LddCanPduType.swPduHandle = 0x02;
  LddCanPduType.id = 0x022;
  LddCanPduType.sdu = &GaaByteArray0[0];
  GenCanReturn = Can_Write(LucHthId, &LddCanPduType);
  
  if (E_OK == GenCanReturn)
  {
    GucReturnCount++;
  }
  
  LulCount = 100000;
  while (LulCount--);
  
  if (((GucReceiveCount - LucReceiveCountOld) == 1) && 
      ((GucTransmitCount - LucTransmitCountOld) == 1))
  {
    GucReturnCount++;
  }
#endif
  
  LulCount = 100000;
  while (LulCount--);
Can_SetControllerMode(CanConf_CanController_CanController2, CAN_CS_STOPPED);
#if (!defined CAN_U2C2_USED) && (!defined CAN_U2B6E_USED)
Can_SetControllerMode(CanConf_CanController_CanController3, CAN_CS_STOPPED);
#endif
#if (CAN_WAKEUP_SUPPORT == STD_ON)
  /* Put the Controller 0 into SLEEP mode
  Note: It is mandatory to put the Controller into STOP mode before
  requesting SLEEP mode.
  CAN Controller will be in SLEEP mode */

  GenCanReturn = Can_SetControllerMode(
    CanConf_CanController_CanController2, CAN_CS_SLEEP);
  if (E_OK == GenCanReturn)
  {
    GucReturnCount++;
  }
  else
  {
    /* No action Required */
  }
  /* Wait for mode transition */
  LulCount = 100000;
  while (LulCount--)
  {
    GenCanReturn = Can_GetControllerMode(
    CanConf_CanController_CanController2, &LenCanCntlState);
    if (E_OK == GenCanReturn && CAN_CS_SLEEP == LenCanCntlState)
    {
      GucReturnCount++;
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

  GenCanReturn = Can_SetControllerMode(
    CanConf_CanController_CanController2, CAN_CS_STOPPED);
  if (E_OK == GenCanReturn)
  {
    GucReturnCount++;
  }
  else
  {
    /* No action Required */
  }
  /* Wait for mode transition */
  LulCount = 100000;
  while (LulCount--)
  {
    GenCanReturn = Can_GetControllerMode(
    CanConf_CanController_CanController2, &LenCanCntlState);
    if (E_OK == GenCanReturn && CAN_CS_STOPPED == LenCanCntlState)
    {
      GucReturnCount++;
      break;
    }
    else
    {
       /* No action required */
    }
  }
#endif /*#if (CAN_WAKEUP_SUPPORT == STD_ON)*/
/* Sample app support for de-initialization feature */ 
  Can_SetControllerMode(CanConf_CanController_CanController0, CAN_CS_STOPPED); 
  Can_SetControllerMode(CanConf_CanController_CanController1, CAN_CS_STOPPED); 
  Can_DeInit();

  /* Reinitialize CAN driver */
  Appl_Can_Init();
  
  LucTransmitCountOld = GucTransmitCount;
  LucReceiveCountOld = GucReceiveCount;
  /* Transmit an L-PDU for Controller 0 */
  LucHthId = 5;
  LddCanPduType.length = 0x08;
  LddCanPduType.swPduHandle = 0x02;
  LddCanPduType.id = 0x11;
  LddCanPduType.sdu = &GaaByteArray1[0];
  GenCanReturn = Can_Write(LucHthId, &LddCanPduType);
  
  if (E_OK == GenCanReturn)
  {
    GucReturnCount++;
  }
  
  LulCount = 100000;
  while (LulCount--);
  
  if (((GucReceiveCount - LucReceiveCountOld) == 1) && 
      ((GucTransmitCount - LucTransmitCountOld) == 1))
  {
    GucReturnCount++;
  }
#endif /* CAN_CANXL_SUPPORTED == STD_ON */
  Can_SetControllerMode(CanConf_CanController_CanController0, CAN_CS_STOPPED);
  Can_SetControllerMode(CanConf_CanController_CanController1, CAN_CS_STOPPED);
  
  if (GucReturnCount == TOTAL_CHECKPOINT_SINGLECORE_SINGLEVARIANT)
  {
    GbOverallStatus = CAN_COMMON_OK;
  }

  /* End trap */
  sample_end();
#if defined (RUN_OTHER_PE)
  return 0;
#endif
}

/*******************************************************************************
                        CAN Module Initialization
*******************************************************************************/

void Appl_Can_Init(void)
{
  /* Global Initialization */
  Can_Init(Can_Config);
  /* Channel Initialization */
  Can_SetBaudrate(
    CanConf_CanController_CanController0, 0);
  Can_SetBaudrate(
    CanConf_CanController_CanController1, 0);
#ifdef CAN_U2B24E_516_USED
  Can_SetBaudrate(
    CanConf_CanController_CanController4, 0);
#endif
#if (CAN_CANXL_SUPPORTED == STD_ON)
  Can_SetBaudrate(
    CanConf_CanController_CanController2, 0);
#if (!defined CAN_U2C2_USED) && (!defined CAN_U2B6E_USED)
  Can_SetBaudrate(
    CanConf_CanController_CanController3, 0);
#endif
#endif
  /* Set Controller Mode to START Mode for Controller 0 and 1*/
  GenCanReturn = Can_SetControllerMode(
    CanConf_CanController_CanController0, CAN_CS_STARTED);
  GenCanReturn = Can_SetControllerMode(
    CanConf_CanController_CanController1, CAN_CS_STARTED);
#if (CAN_CANXL_SUPPORTED == STD_ON)
  GenCanReturn = Can_SetControllerMode(
    CanConf_CanController_CanController2, CAN_CS_STARTED);
  GenCanReturn = CanXL_SetControllerMode(
    CanConf_CanController_CanController2, ETH_MODE_ACTIVE);
#if (!defined CAN_U2C2_USED) && (!defined CAN_U2B6E_USED)
  GenCanReturn = Can_SetControllerMode(
    CanConf_CanController_CanController3, CAN_CS_STARTED);
  GenCanReturn = CanXL_SetControllerMode(
    CanConf_CanController_CanController3, ETH_MODE_ACTIVE);
#endif
#endif
#ifdef CAN_U2B24E_516_USED
  GenCanReturn = Can_SetControllerMode(
    CanConf_CanController_CanController4, CAN_CS_STARTED);
#endif
  if (E_OK == GenCanReturn)
  {
    GucReturnCount++;
  }
  else
  {
    /* No action Required */
  }
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

#if defined(CAN_LPDU_RECEIVE_CALLOUT_FUNCTION)
/* Callout function */
FUNC(boolean, CAN_CALLOUT_CODE) UserCalloutFunction(
  uint16 Hrh, Can_IdType CanId,
  uint8 CanDataLength,
  P2CONST(uint8, CAN_APPL_DATA, AUTOMATIC) CanSduPtr)
{
  uint8 LucDlc;
  uint8 LucCnt;
  uint8 *LpData;
  LucDlc = CanDataLength;
  if ((0x068 == CanId) || (0x02 == CanId))
  {
    LpData = &GaaByteArray0[0];
  }
  else
  {
    LpData = &GaaByteArray1[0];
  }

  for (LucCnt = 0; LucCnt < LucDlc; LucCnt++)
  {
    if (LpData[LucCnt] != CanSduPtr[LucCnt])
    {
      break;
    }
  }

  if (LucCnt == LucDlc)
  {
    GucReturnCount++;
    GaaHohArray[Hrh]++;
  }
  /* return TRUE unconditionally */
  return TRUE;
}
#endif
/******************************************************************************/
/*                             Send ETH message                               */
/******************************************************************************/
#if (CAN_CANXL_SUPPORTED == STD_ON)
void SendEthFrame( uint8 CtrlIdx, uint8 *Buf, uint16 LenByte, Eth_FrameType FrameType,
                   uint8 Priority, const uint8* PhysAddrPtr)
{
  Std_ReturnType LucReturnValue;
  Eth_DataType *BufPtr;
  Eth_DataType *BufPtr_1;
  Eth_BufIdxType BufIdx;
  Eth_BufIdxType BufIdx_1;
  BufReq_ReturnType LenRequestBuffer;
  uint16 LusLength;
  uint8 LucChannelId; 
  volatile uint32 LulSendCounter;
  volatile uint32 LulCount;
  
  LucChannelId = Can_GaaControllerPCConfig0[CtrlIdx].ucCh;
  LusLength = LenByte;
  /* initialize value for GucTxConfirmed */
  GucTxConfirmed[LucChannelId] = 0;

  /* ---------------------------------first Frame-------------------------------------- */
  /* Invoke CanXL_ProvideTxBuffer to get available buffer */
  LenRequestBuffer = CanXL_ProvideTxBuffer(CtrlIdx, Priority, &BufIdx, &BufPtr, &LusLength);

  if ((LenRequestBuffer == BUFREQ_OK) && (Buf != NULL_PTR))
  {
    GucReturnCount++;
  }

  /* Copy Transmit data to the buffer to transmit */
  for (LulCount = 0; LulCount < LusLength; LulCount++)
  {
    *(BufPtr + LulCount) = *(Buf + LulCount);
  }

  LucReturnValue = CanXL_Transmit(CtrlIdx, BufIdx, FrameType, CAN_TRUE, LusLength, PhysAddrPtr);
  if (E_OK == LucReturnValue)
  {
    GucReturnCount++;
  }

  LulCount = 100000;
  while (LulCount--);

  /* ---------------------------------seconds Frame-------------------------------------- */
  /* Invoke CanXL_ProvideTxBuffer to get available buffer */
  LenRequestBuffer = CanXL_ProvideTxBuffer(CtrlIdx, Priority, &BufIdx_1, &BufPtr_1, &LusLength);

  if ((LenRequestBuffer == BUFREQ_OK) && (Buf != NULL_PTR))
  {
    GucReturnCount++;
  }

  /* Copy Transmit data to the buffer to transmit */
  for (LulCount = 0; LulCount < LusLength; LulCount++)
  {
    *(BufPtr_1 + LulCount) = *(Buf + LulCount);
  }

  LucReturnValue = CanXL_Transmit(CtrlIdx, BufIdx_1, FrameType, CAN_TRUE, LusLength, PhysAddrPtr);
  if (E_OK == LucReturnValue)
  {
    GucReturnCount++;
  }

  LulCount = 100000;
  while (LulCount--);
  

  /* ---------------------------------Tx Confirmation-------------------------------------- */
  LulSendCounter = 0;
  while ((2U != GucTxConfirmed[LucChannelId]) && (1000 > LulSendCounter))
  {
    /* Polling for Tx confirmation */
    CanXL_TxConfirmation(CtrlIdx);
    LulSendCounter++;
  }
  
  if(GucTxConfirmed[LucChannelId] == 2U)
  {
    GucReturnCount++;
  }
}
#endif /* CAN_CANXL_SUPPORTED == STD_ON */

/* Guard_Enable_PE */
#if defined(RUN_OTHER_PE)
void Guard_Enable_PE(void)
{
  #if defined(CAN_U2B24E_516_USED) || defined(CAN_U2B12E_USED)
  uint8 LucNumofRSLVXX = 20;
  #else
  uint8 LucNumofRSLVXX = 18;
  #endif
  
  #if defined(CAN_U2B24E_516_USED)
  uint8 LucNumofPBGXX = 39;
  #elif defined(CAN_U2B12E_USED)
  uint8 LucNumofPBGXX = 38;
  #else
  uint8 LucNumofPBGXX = 36;
  #endif
  
  const uint32 RSLVXX_base[]=
  {
  (uint32) 0xFFC6B000UL, //PBGERRSLV00_base
  (uint32) 0xFFC63100UL, //PBGERRSLV10_base
  (uint32) 0xFFDE1000UL, //PBGERRSLV20_base
  (uint32) 0xFFC73200UL, //PBGERRSLV30_base
  (uint32) 0xFFC75400UL, //PBGERRSLV40_base
  (uint32) 0xFFC7B000UL, //PBGERRSLV50_base
  (uint32) 0xFFC83000UL, //PBGERRSLV60_base
  (uint32) 0xFFC83040UL, //PBGERRSLV62_base
  (uint32) 0xFFF4A000UL, //PBGERRSLV70_base
  (uint32) 0xFFF2A000UL, //PBGERRSLV8H0_base
  #if defined(CAN_U2B24E_516_USED) || defined(CAN_U2B12E_USED)
  (uint32) 0xFFF6D480UL, //PBGERRSLV8M0_base
  #endif
  (uint32) 0xFF97A200UL, //PBGERRSLV8L0_base
  #if defined(CAN_U2B24E_516_USED) || defined(CAN_U2B12E_USED)
  (uint32) 0xFFF6E080UL, //PBGERRSLV8M0_base
  #endif
  (uint32) 0xFF0A1400UL, //PBGERRSLV90_base
  (uint32) 0xFF0A1600UL, //PBGERRSLV91_base
  (uint32) 0xFF87A000UL, //PBGERRSLV100_base
  (uint32) 0xFF8B2000UL, //PBGERRSLV11H0_base
  (uint32) 0xFF8F8100UL, //PBGERRSLV11L0_base
  (uint32) 0xFF0D4440UL, //HBGERRSLV92_base
  (uint32) 0xFF0D4480UL, //HBGERRSLV93_base
  };

  const uint32 PBGXX_base[]=
  {
  (uint32) 0xFFC6B080UL, //PBG00_base
  (uint32) 0xFFC6B100UL, //PBG01_base
  (uint32) 0xFFC63000UL, //PBG10_base
  (uint32) 0xFFDE0B00UL, //PBG20_base
  (uint32) 0xFFDE0C00UL, //PBG21_base
  (uint32) 0xFFDE0D00UL, //PBG22_base
  (uint32) 0xFFDE0E00UL, //PBG23_base
  (uint32) 0xFFDE1200UL, //PBG24_base
  (uint32) 0xFFC72B00UL, //PBG30_base
  (uint32) 0xFFC72C00UL, //PBG31_base
  #if defined(CAN_U2B24E_516_USED) || defined(CAN_U2B12E_USED)
  (uint32) 0xFFC72D00UL, //PBG32_base
  #endif
  (uint32) 0xFFC75300UL, //PBG40_base
  (uint32) 0xFFC75380UL, //PBG41_base
  (uint32) 0xFFC7A300UL, //PBG50_base
  (uint32) 0xFFC7A400UL, //PBG51_base
  (uint32) 0xFFC7A500UL, //PBG52_base
  (uint32) 0xFFC81000UL, //PBG60_base
  (uint32) 0xFFC81200UL, //PBG61_base
  (uint32) 0xFFC82000UL, //PBG62_base
  (uint32) 0xFFF49400UL, //PBG70_base
  (uint32) 0xFFF49600UL, //PBG71_base
  (uint32) 0xFFF29300UL, //PBG8H0_base
  #if defined(CAN_U2B24E_516_USED) || defined(CAN_U2B12E_USED) || defined(CAN_U2B6E_USED)
  (uint32) 0xFFF6D400UL, //PBG8M0_base
  #endif
  (uint32) 0xFF97A000UL, //PBG8L0_base
  #if defined(CAN_U2B24E_516_USED) || defined(CAN_U2B12E_USED) || defined(CAN_U2B6E_USED)
  (uint32) 0xFF97A100UL, //PBG8L1_base
  #endif
  #if defined(CAN_U2B24E_516_USED) || defined(CAN_U2B12E_USED)
  (uint32) 0xFFF6E000UL, //PBG8UL0_base
  #endif
  (uint32) 0xFF0A1300UL, //PBG90_base
  (uint32) 0xFF0A1500UL, //PBG91_base
  (uint32) 0xFF0A1700UL, //PBG92_base
  (uint32) 0xFF879400UL, //PBG100_base
  #if defined(CAN_U2B24E_516_USED) || defined(CAN_U2B12E_USED)
  (uint32) 0xFF879500UL, //PBG101_base
  #endif
  (uint32) 0xFF8B1400UL, //PBG11H0_base
  (uint32) 0xFF8B1600UL, //PBG11H1_base
  #if defined(CAN_U2B24E_516_USED) || defined(CAN_U2B12E_USED)
  (uint32) 0xFF8B1800UL, //PBG11H2_base
  #endif
  (uint32) 0xFF8F8000UL, //PBG11L0_base    
  (uint32) 0xFF860000UL, //PBG_CANFD0_base
  #if defined(CAN_U2B24E_516_USED) || defined(CAN_U2B12E_USED)
  (uint32) 0xFF860800UL, //PBG_CANFD1_base
  #endif
  #if defined(CAN_U2B24E_516_USED)
  (uint32) 0xFF861000UL, //PBG_CANFD2_base
  #endif
  #if !defined(CAN_U2B24E_516_USED) && !defined(CAN_U2B12E_USED) && !defined(CAN_U2B6E_USED)
  (uint32) 0xFF88FA00UL, //PBG_ATU_base
  #endif
  (uint32) 0xFFF60000UL  //PBG_GTM_base
  };
  const uint32 HBGXX_base[]=
  {
    #if defined(CAN_U2B24E_516_USED) || defined(CAN_U2B12E_USED)
    (uint32) 0xFF0D0A00UL, //HBG913_base
    (uint32) 0xFF0D0B00UL, //HBG914_base
    #elif defined(CAN_U2B6E_USED)
    (uint32) 0xFF0D0A00UL, //HBG913_base
    #else
    (uint32) 0xFF0D0A00UL, //HBG92_base
    (uint32) 0xFF0D0C00UL, //HBG93_base
    #endif
  };
  //Enable write
  for (int i =0; i<LucNumofRSLVXX;i++)
  {
  volatile uint32 *ptr;
  ptr = (volatile uint32 *)(RSLVXX_base[i] + (uint32)0x18UL);
  *ptr = (uint32)0xA5A5A501UL;
  }
  // Write HBGxx
  for (int i =0; i<2;i++)
  {
    volatile uint32 *ptr;
    ptr = (volatile uint32 *)(HBGXX_base[i]);
    *ptr |= 0x00000143UL;
  }
  //Write PBG0
  for (int i =0; i<LucNumofPBGXX;i++)
  {
    for (int ii =0; ii<16;ii++)
    {
      volatile uint32 *ptr;
      ptr = (volatile uint32 *)(PBGXX_base[i] + ((uint32)ii * 0x8UL));
      *ptr |= 0x00000143UL;
    }
  }

  //Write PBG1
  for (int i =0; i<LucNumofPBGXX;i++)
  {
    for (int ii =0; ii<16;ii++)
    {
      volatile uint32 *ptr;
      ptr = (volatile uint32 *)(PBGXX_base[i] + 0x4UL + ((uint32)ii * 0x8UL));
      *ptr |= 0xFFFFUL;
    }
  }

  //Disable write
  for (int i =0; i<LucNumofRSLVXX;i++)
  {
  volatile uint32 *ptr;
  ptr = (volatile uint32 *)(RSLVXX_base[i]+0x18UL);
  *ptr = 0xA5A5A500UL;
  }
  
} 
#endif

/*******************************************************************************
                          End of the file
*******************************************************************************/

