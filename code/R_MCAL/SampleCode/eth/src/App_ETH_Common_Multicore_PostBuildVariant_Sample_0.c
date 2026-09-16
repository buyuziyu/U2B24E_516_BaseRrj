/*============================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                         */
/* Module       = App_ETH_Common_Multicore_PostBuildVariant_Sample_0.c        */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2024, 2025 Renesas Electronics Corporation. All rights reserved.       */
/*============================================================================*/
/* Purpose:                                                                   */
/* This file contains sample application for ETH Driver Component             */
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
 * 2.4.1: 30/06/2025    : Remove the SW-VERSION from header of file
 * 2.4.0: 30/06/2025    : Update SW-VERSION for RH850/Ver22.01.00 (D) U2Ax release
 * 2.3.1: 31/03/2025    : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 * 2.3.0: 28/02/2025    : Update SW-VERSION for Ver22.01.00/Ver22.01.00.D U2Cx Release
 *                        Support multicore.
 * 2.2.0: 31/12/2024    : Update SW-VERSION for Ver22.02.00(D) U2Bx Final Release
 * 2.1.2: 30/09/2024    : Remove redundant define PHY_TRCV_IDX.
 *                        Change invoke Phy_Init() when Phy interface using MII.
 *                        Add logic code to check link-up after invoke Eth_InitT1s().
 * 2.0.2: 15/04/2024    : Initial Version.
 */
/******************************************************************************/

/*******************************************************************************
**                     Include Section                                        **
*******************************************************************************/
#include "App_ETH_Multi_Sample.h"
#include "App_Eth_Device_Sample.h"
#include "App_Eth_Common_Sample_0.h"
#include <stdio.h>
#include <string.h>
#include "Eth_Ram.h"
#if (ETH_MACRO_ETNF == STD_ON)
#include "Eth_ETNF_Ram.h"
#endif
/*******************************************************************************
**                            Macros                                          **
*******************************************************************************/
#define SAMPLE_TOTAL                  6U
#define ETH_FAILED                    0
#define ETH_PASSED                    1
#define ETH_AVBTP_TYPE                0x22F0
#define ETH_NC_TYPE                   0x88F7U
#define PHY_TRCV_IDX                  0x1FU
#define PHY_TRCV_CTRL_REG             0U
#define PHY_TRCV_STATUS_REG           1U
#define FRAME_LEN                     62U       /* Without header and FCS.    */
#define NORMAL_HEADER_LEN             14U
#define SRC_MACADDR_LEN               6U
#define DST_MACADDR_LEN               6U
#define STREAMID_LEN                  8U
#define ETHTYPE_LEN                   2U
#define ETH_VLFRAME_SIZE              1522U
#define PHY_LINKUP_BIT                0x002CU

#define RX_QUEUE_0                    0U
#define RX_QUEUE_1                    1U
#define RX_QUEUE_2                    2U
#define RX_QUEUE_3                    3U
/* Time-out */
#define ETH_TIMEOUT                   (uint32)0x200000

#define CRC_ERROR                     1U
#define UNDERSIZE_PACKET_ERROR        2U
#define OVERSIZE_PACKET_ERROR         3U
#define ALIGNMENT_ERROR               4U
#define LATE_COLLISION                13U

#define DROP_EVENTS                   0U
#define BROADCAST_PACKETS             3U
#define MULTICAST_PACKETS             4U
#define CRC_ALIGN_ERRORS              5U
#define UNDERSIZE_ERRORS              6U
#define OVERSIZE_ERRORS               7U
#define LATE_COLLISIONS               10U

#define RX_MULTICAST_FRAME_TOTAL      6U
#define RX_UNICAST_FRAME_TOTAL        1U
#define OCTET_TOTAL                   532U

#define CORE_0                        0U

extern void sample_end(void);
extern void sample_NG_end(void);
extern void Init_MCAL(void);
/*******************************************************************************
**                        Global variables                                    **
*******************************************************************************/
volatile uint8 GaaRxEthFrame_0[ETH_TOTAL_CTRL_CONFIG][ETH_VLFRAME_SIZE];
volatile uint8 GaaRxSrcAddr_0[ETH_TOTAL_CTRL_CONFIG][SRC_MACADDR_LEN];
volatile uint8 GucTxConfirmed_0[ETH_TOTAL_CTRL_CONFIG];
volatile uint16 GusMsgLength_0[ETH_TOTAL_CTRL_CONFIG];
volatile uint16 GusRxFrameCnt_0[ETH_TOTAL_CTRL_CONFIG];
volatile uint16 GusRxLenByte_0[ETH_TOTAL_CTRL_CONFIG];
volatile Eth_FrameType GusRxFrameType_0[ETH_TOTAL_CTRL_CONFIG];
volatile boolean EthRcvBroadcastMsg_0;
volatile uint8 EthPassedCount_0[70];
volatile uint8 EthCheckCount_0;
volatile uint8 EthModeActiveCnt_0;
volatile uint8 EthModeDownCnt_0;

#if (ETH_GLOBAL_TIME_SUPPORT == STD_ON)
Eth_TimeStampQualType TxTimeQual_0;
Eth_TimeStampType TxTimeStamp_0[ETH_TOTAL_CTRL_CONFIG];
#endif

/* Board MAC address */
static uint8 mac_board_addr_0[2][SRC_MACADDR_LEN] =
{
  {0x74U, 0x90U, 0x50U, 0x00U, 0x00U, 0x00U},
  {0x74U, 0x90U, 0x50U, 0x00U, 0x00U, 0x01U}
};

/* Target MAC address */
static uint8 mac_tgt_addr_0[DST_MACADDR_LEN] = {0x74U, 0x90U, 0x50U, 0xFFU, 0xFFU, 0xFFU};

/* IEEE 1722 frames MAC address*/
static uint8 mac_tgt_addr_00[DST_MACADDR_LEN] = {0x91U, 0xE0U, 0xF0U, 0x00U, 0x00U, 0x00U};
static uint8 mac_tgt_addr_01[DST_MACADDR_LEN] = {0x91U, 0xE0U, 0xF0U, 0x00U, 0xFEU, 0xFFU};

/* Network control MAC address */
static uint8 mac_nc_addr_0[DST_MACADDR_LEN] = {0x01U, 0x80U, 0xC2U, 0x00U, 0x00U, 0x0EU};

/* Valid multicast MAC address used for Eth_UpdatePhysAddrFilter */
static uint8 mac_multi_addr0_0[DST_MACADDR_LEN] =  {0x11U, 0x22U, 0x33U, 0x44U, 0x55U, 0x66U};
/* Invalid multicast MAC address used for Eth_UpdatePhysAddrFilter */
static uint8 mac_multi_addr1_0[DST_MACADDR_LEN] = {0x11U, 0x22U, 0x33U, 0x44U, 0x55U, 0x77U};

#if (ETH_STREAM_FILTERING == STD_ON)
static uint8 streamId0_0[STREAMID_LEN] = {0x11U, 0x22U, 0x33U, 0x44U, 0x55U, 0xFFU, 0x00U, 0x00U};
#endif

/*---------------------------------------------------*/
/* Receive and Transmit Buffers */
/*---------------------------------------------------*/
static uint8 TxEthFrame_0[SAMPLE_TOTAL][FRAME_LEN] =
{
  /* Index 0: Normal frame expected to get filter in Rx Queue 0 */
  {
    0xBBU, 0xBBU,
    0xBBU, 0xBBU, 0xBBU, 0xBBU, 0xBBU, 0xBBU, 0xBBU, 0xBBU, 0xBBU, 0xBBU,
    0xBBU, 0xBBU, 0xBBU, 0xBBU, 0xBBU, 0xBBU, 0xBBU, 0xBBU, 0xBBU, 0xBBU,
    0xBBU, 0xBBU, 0xBBU, 0xBBU, 0xBBU, 0xBBU, 0xBBU, 0xBBU, 0xBBU, 0xBBU,
    0xBBU, 0xBBU, 0xBBU, 0xBBU, 0xBBU, 0xBBU, 0xBBU, 0xBBU, 0xBBU, 0xBBU,
    0xBBU, 0xBBU, 0xBBU, 0xBBU, 0xBBU, 0xBBU, 0xBBU, 0xBBU, 0xBBU, 0xBBU,
    0xBBU, 0xBBU, 0xBBU, 0xBBU, 0xBBU, 0xBBU, 0xBBU, 0xBBU, 0xBBU, 0xBBU,
  },
  /* Index 1: Network control frame expected to get filter in Rx Queue 1 */
  {
    0xCCU, 0xCCU,
    0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU,
    0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU,
    0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU,
    0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU,
    0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU,
    0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU, 0xCCU,
  },
  /* Index 2: IEEE 1722 Frame expected to get filter in Rx Queue 2*/
  {
    /* Subtype */
    0x7EU, 0x00U,
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
    0xDDU, 0xDDU, 0xDDU, 0xDDU, 0xDDU, 0xDDU, 0xDDU, 0xDDU, 0xDDU, 0xDDU,
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

#if (ETH_VERSION_INFO_API == STD_ON)
/* Variable used to store the Module Version Info */
static Std_VersionInfoType GddVersionInfo;
uint8 GucVerCheckStatus;
#endif
uint8 GucTxFrameSentCnt_0;


static void SendData
(
  uint8 CtrlIdx,
  uint8 *Buf,
  uint16 LenByte,
  Eth_FrameType FrameType,
  uint8 Priority,
  const uint8* PhysAddrPtr
);
/******************************************************************************/
/* sample application for ETH Driver Component                                */
/******************************************************************************/
int main(void)
{
  Std_ReturnType LucReturnValue;
  uint8 LucCtrlCnt;
  uint8 LucCount;
  uint32 LulTotalCtrlConfig;
  uint32 LucCoreIndex;
  #if (ETH_CTRL_ENABLE_MII == STD_ON)
  uint32 LulDelayCounter;
  #endif
  Eth_ModeType LenEthCtrlMode[ETH_TOTAL_CTRL_CONFIG];
  #if (ETH_CTRL_ENABLE_RX_POLLING == STD_ON)
  Eth_RxStatusType LenEthRxStatus[ETH_TOTAL_CTRL_CONFIG];
  #if (ETH_AR_VERSION >= ETH_AR_431_VERSION)
  Eth_RxStatusType LenEthStatusRxQueue0[ETH_TOTAL_CTRL_CONFIG];
  #if ((ETH_MACRO_ETNB == STD_ON) || (ETH_MACRO_ETNF == STD_ON))
  Eth_RxStatusType LenEthStatusRxQueue1[ETH_TOTAL_CTRL_CONFIG];
  Eth_RxStatusType LenEthStatusRxQueue2[ETH_TOTAL_CTRL_CONFIG];
  Eth_RxStatusType LenEthStatusRxQueue3[ETH_TOTAL_CTRL_CONFIG];
  #endif
  #endif
  #endif
  #if (ETH_GLOBAL_TIME_SUPPORT == STD_ON)
  Eth_TimeStampQualType LenEthTimeQualPtr;
  Eth_TimeStampType LstCurrentTime;
  #endif
  #if (ETH_GET_DROP_COUNT_API == STD_ON)
  uint32 DropCount[15] = { 0 };
  uint8 CountValues;
  #endif
  #if (ETH_GET_COUNTER_VALUES_API == STD_ON)
  Eth_CounterType CounterPtr;
  CounterPtr.DropPktBufOverrun = 0;
  CounterPtr.DropPktCrc        = 0;
  CounterPtr.UndersizePkt      = 0;
  CounterPtr.OversizePkt       = 0;
  CounterPtr.AlgnmtErr         = 0;
  #endif
  #if (ETH_GET_TX_ERROR_COUNTER_VALUES_API == STD_ON)
  Eth_TxErrorCounterValuesType TxErrorCounterValues;
  #endif
  #if (ETH_GET_ETHER_STATS_API == STD_ON)
  uint32 etherStats[18] = { 0 };
  #endif

  #if (ETH_GET_RX_STATS_API == STD_ON)
  Eth_RxStatsType RxStats;
  RxStats.RxStatsPkts           = 0;
  RxStats.RxStatsBroadcastPkts  = 0;
  RxStats.RxStatsMulticastPkts  = 0;
  RxStats.RxStatsCrcAlignErrors = 0;
  RxStats.RxStatsUndersizePkts  = 0;
  RxStats.RxStatsOversizePkts   = 0;
  #endif
  #if (ETH_GET_TX_STATS_API == STD_ON)
  Eth_TxStatsType TxStats;
  #endif
  uint32 LulInc;
  #if (ETH_CTRL_ENABLE_MII == STD_ON)
  uint16 LusRegValue;
  #endif
  uint8 LucRetrieveMacAddr[ETH_TOTAL_CTRL_CONFIG][SRC_MACADDR_LEN];

  LucCoreIndex = Eth_Config_Variant_1->pCoreId2Index[CORE_0];
  LulTotalCtrlConfig = Eth_Config_Variant_1->pTotalCtrlConfig[LucCoreIndex];

  for (LucCount = 0; LucCount < LulTotalCtrlConfig; LucCount++)
  {
    LucCtrlCnt = Eth_Config_Variant_1->ulCtrlConfigIdx[CORE_0][LucCount];
    #if (ETH_CTRL_ENABLE_RX_POLLING == STD_ON)
    LenEthCtrlMode[LucCtrlCnt] = ETH_MODE_DOWN;
    LenEthRxStatus[LucCtrlCnt] = ETH_NOT_RECEIVED;
    #endif

    GusRxFrameCnt_0[LucCtrlCnt] = 0;
    GusMsgLength_0[LucCtrlCnt] = 0;
  }


  #if (ETH_GLOBAL_TIME_SUPPORT == STD_ON)
  LstCurrentTime.nanoseconds = 0;
  LstCurrentTime.seconds     = 0;
  LstCurrentTime.secondsHi   = 0;
  #endif
  GucTxFrameSentCnt_0 = 0;
  #if (ETH_CTRL_ENABLE_MII == STD_ON)
  LulDelayCounter = 0;
  #endif
  #if (ETH_GET_DROP_COUNT_API == STD_ON)
  CountValues = 15;
  #endif
  /*********************** Check version info ************************/

#if (ETH_VERSION_INFO_API == STD_ON)
  /* Invoke Eth_GetVersionInfo to get version info */
  Eth_GetVersionInfo(&GddVersionInfo);
  if ((ETH_VENDOR_ID == GddVersionInfo.vendorID) &&
      (ETH_MODULE_ID == GddVersionInfo.moduleID) &&
      (ETH_SW_MAJOR_VERSION == GddVersionInfo.sw_major_version) &&
      (ETH_SW_MINOR_VERSION == GddVersionInfo.sw_minor_version) &&
      (ETH_SW_PATCH_VERSION == GddVersionInfo.sw_patch_version)
  )
  {
    GucVerCheckStatus = ETH_TRUE;
    EthPassedCount_0[EthCheckCount_0] = ETH_PASSED;
  }
  else
  {
    /* If the version information is incorrect */
    GucVerCheckStatus = ETH_FALSE;
  }
  EthCheckCount_0++;
#endif /* (STD_ON == ETH_VERSION_INFO_API ) */

  /************************** Initilazation  *****************************/
  /* Initialize MCAL */
  Init_MCAL();

  /* Invoke Eth_Init to initialize the Ethernet Driver */
  Eth_Init(Eth_Config_Variant_1);
  GblInitStatus[0] = 1;
  
  /* Wait core 1 complete init */
  while (GblInitStatus[1] != 1);

  /************************* Set up transceiver ****************************/

  #if (ETH_CTRL_ENABLE_MII == STD_ON)
  for (LucCount = 0; LucCount < LulTotalCtrlConfig; LucCount++)
  {
    LucCtrlCnt = Eth_Config_Variant_1->ulCtrlConfigIdx[CORE_0][LucCount];
    switch (Eth_Config_Variant_1->pCtrlConfig->pEthConfig[LucCtrlCnt].enEthPHYInterface)
    {
    case ETH_MII:

      Phy_Init();
      do
      {
        /* Read the state register of the PHY(8700). */
        Eth_ReadMii(LucCtrlCnt, PHY_TRCV_IDX, PHY_TRCV_STATUS_REG, &LusRegValue);

        LulDelayCounter++;
      } while ((LusRegValue & PHY_LINKUP_BIT) != PHY_LINKUP_BIT && LulDelayCounter < ETH_TIMEOUT);

      if (LulDelayCounter < ETH_TIMEOUT)
      {
        EthPassedCount_0[EthCheckCount_0] = ETH_PASSED;
      }
      EthCheckCount_0++;

      break;

    #if (ETH_MACRO_ETNB == STD_ON || ETH_MACRO_ETND == STD_ON || ETH_MACRO_ETNE == STD_ON)
    case ETH_SGMII:

      Eth_InitSgmii(LucCtrlCnt);

      break;
    #endif

    #if (ETH_MACRO_ETNF == STD_ON || ETH_MACRO_ETNE == STD_ON)
    case ETH_T1S:

      Eth_InitT1s(LucCtrlCnt);
      do
      {
        /* Read the state register of the PHY(CT25205). */
        Eth_ReadMii(LucCtrlCnt, PHY_TRCV_IDX, PHY_TRCV_STATUS_REG, &LusRegValue);

        LulDelayCounter++;
      } while ((LusRegValue & PHY_LINKUP_BIT) != PHY_LINKUP_BIT && LulDelayCounter < ETH_TIMEOUT);

      if (LulDelayCounter < ETH_TIMEOUT)
      {
        EthPassedCount_0[EthCheckCount_0] = ETH_PASSED;
      }
      EthCheckCount_0++;

      break;
    #endif

    default:;
    }
    /* waiting for phy device stable */
    wait_msec(20);
  }
  #endif

  for (LucCount = 0; LucCount < LulTotalCtrlConfig; LucCount++)
  {
    LucCtrlCnt = Eth_Config_Variant_1->ulCtrlConfigIdx[CORE_0][LucCount];
    /*********************** Set controller MAC address **********************/

    /* Invoke Eth_SetPhysAddr to change physical address */
    Eth_SetPhysAddr(LucCtrlCnt, mac_board_addr_0[LucCtrlCnt]);

    /* Invoke Eth_GetPhysAddr to get physical address */
    Eth_GetPhysAddr(LucCtrlCnt, (uint8*)LucRetrieveMacAddr[LucCtrlCnt]);

    if (memcmp(&LucRetrieveMacAddr[LucCtrlCnt][0], &mac_board_addr_0[LucCtrlCnt][0], SRC_MACADDR_LEN) == 0)
    {
      /* If the MAC address is correct */
      EthPassedCount_0[EthCheckCount_0] = ETH_PASSED;
    }
    EthCheckCount_0++;

    /*********************** Configure frame filter *************************/
    #if (ETH_STREAM_FILTERING == STD_ON)
    /* Update Stream ID pattern to change SRP queue if needed */
    Eth_UpdateStreamFilter(LucCtrlCnt, RX_QUEUE_2, streamId0_0);
    #endif

    #if (ETH_UPDATE_PHYS_ADDR_FILTER == STD_ON)
    /* Add addition multicast address for this controller to listen to */
    Eth_UpdatePhysAddrFilter(LucCtrlCnt, mac_multi_addr0_0, ETH_ADD_TO_FILTER);

    /* Add addition multicast address for this controller to listen to */
    Eth_UpdatePhysAddrFilter(LucCtrlCnt, mac_tgt_addr_00, ETH_ADD_TO_FILTER);
    #endif

    /************************** Enable controller ****************************/

    /* Set the Controller mode to ACTIVE */
    do
    {
      LucReturnValue = Eth_SetControllerMode(LucCtrlCnt, ETH_MODE_ACTIVE);
    } while (E_NOT_OK == LucReturnValue);

    /* Get controller mode */
    Eth_GetControllerMode(LucCtrlCnt, &LenEthCtrlMode[LucCtrlCnt]);
    if (ETH_MODE_ACTIVE == LenEthCtrlMode[LucCtrlCnt])
    {
      EthPassedCount_0[EthCheckCount_0] = ETH_PASSED;
    }
    EthCheckCount_0++;
  }

  /*********************** Configure gPTP timer ****************************/

  /************************ Transmit and Receive a frame *******************/

  for (LucCount = 0; LucCount < LulTotalCtrlConfig; LucCount++)
  {
    LucCtrlCnt = Eth_Config_Variant_1->ulCtrlConfigIdx[CORE_0][LucCount];
    /* Send normal unicast frame */
    SendData(LucCtrlCnt, &TxEthFrame_0[0][0], FRAME_LEN, FRAME_LEN, 0, mac_tgt_addr_0);

    #if (ETH_GLOBAL_TIME_SUPPORT == STD_ON)
    /* Get the current time */
    Eth_GetCurrentTime(LucCtrlCnt, &LenEthTimeQualPtr, &LstCurrentTime);

    if ((ETH_VALID == LenEthTimeQualPtr) &&
        ((LstCurrentTime.secondsHi > TxTimeStamp_0[LucCtrlCnt].secondsHi) ||
        ((LstCurrentTime.secondsHi == TxTimeStamp_0[LucCtrlCnt].secondsHi) &&
         (LstCurrentTime.seconds > TxTimeStamp_0[LucCtrlCnt].seconds)) ||
        ((LstCurrentTime.secondsHi == TxTimeStamp_0[LucCtrlCnt].secondsHi) &&
         (LstCurrentTime.seconds == TxTimeStamp_0[LucCtrlCnt].seconds) &&
        (LstCurrentTime.nanoseconds > TxTimeStamp_0[LucCtrlCnt].nanoseconds))))
    {
      EthPassedCount_0[EthCheckCount_0] = ETH_PASSED;
    }
    EthCheckCount_0++;
    #endif

    #if (ETH_CTRL_ENABLE_RX_POLLING == STD_ON)
    /* Wait to receive message */
    do
    {
      /* Check for received message */
      Eth_Receive(LucCtrlCnt,
                  #if (ETH_AR_VERSION >= ETH_AR_431_VERSION)
                  0,
                  #endif
                  &LenEthRxStatus[LucCtrlCnt]);
    } while (ETH_RECEIVED != LenEthRxStatus[LucCtrlCnt]);
    #endif

    /* Check if Tx and Rx data is same. */
    if (memcmp((void *)&GaaRxEthFrame_0[LucCtrlCnt][0], &TxEthFrame_0[GusRxFrameCnt_0[LucCtrlCnt] - 1][0],
        GusMsgLength_0[LucCtrlCnt] - ETH_NORMALMAC_HSIZE_0) == 0)
    {
      EthPassedCount_0[EthCheckCount_0] = ETH_PASSED;
    }
    EthCheckCount_0++;

    /**************** Transmit and Receive multiple frames *******************/

    /* Send multicast frame which is valid for this station */
    SendData(LucCtrlCnt, &TxEthFrame_0[4][0], FRAME_LEN, FRAME_LEN, 0, mac_multi_addr0_0);

    /* Send multicast frame which is not valid for this station, it will be filtered out */
    SendData(LucCtrlCnt, &TxEthFrame_0[4][0], FRAME_LEN, FRAME_LEN, 0, mac_multi_addr1_0);

    /* Send Network control frame */
    SendData(LucCtrlCnt, &TxEthFrame_0[1][0], FRAME_LEN, ETH_NC_TYPE, 0, mac_nc_addr_0);

    /* Send 1722 frames with no reserved resource in this station */
    SendData(LucCtrlCnt, &TxEthFrame_0[5][0], FRAME_LEN, ETH_AVBTP_TYPE, 0, mac_tgt_addr_00);

    /* Send 1722 frames with reserved resource in this station */
    SendData(LucCtrlCnt, &TxEthFrame_0[2][0], FRAME_LEN, ETH_AVBTP_TYPE, 0, mac_tgt_addr_00);
    SendData(LucCtrlCnt, &TxEthFrame_0[3][0], FRAME_LEN, ETH_AVBTP_TYPE, 0, mac_tgt_addr_01);

    #if (ETH_CTRL_ENABLE_RX_POLLING == STD_ON)
    while (GusRxFrameCnt_0[LucCtrlCnt] != EthTxTotal[LucCtrlCnt])
    {
      Eth_MainFunction();

      /* Wait to receive message for controller ETNB0 */
      #if (ETH_AR_VERSION >= ETH_AR_431_VERSION)
      do
      {
        /* Check for received message */
        Eth_Receive(LucCtrlCnt, RX_QUEUE_0, &LenEthStatusRxQueue0[LucCtrlCnt]);
        #if ((ETH_MACRO_ETNB == STD_ON) || (ETH_MACRO_ETNF == STD_ON))
        Eth_Receive(LucCtrlCnt, RX_QUEUE_1, &LenEthStatusRxQueue1[LucCtrlCnt]);
        Eth_Receive(LucCtrlCnt, RX_QUEUE_2, &LenEthStatusRxQueue2[LucCtrlCnt]);
        Eth_Receive(LucCtrlCnt, RX_QUEUE_3, &LenEthStatusRxQueue3[LucCtrlCnt]);
        #endif
      } while ((ETH_NOT_RECEIVED == LenEthStatusRxQueue0[LucCtrlCnt])
              #if ((ETH_MACRO_ETNB == STD_ON) || (ETH_MACRO_ETNF == STD_ON))
            && (ETH_NOT_RECEIVED == LenEthStatusRxQueue1[LucCtrlCnt])
            && (ETH_NOT_RECEIVED == LenEthStatusRxQueue2[LucCtrlCnt])
            && (ETH_NOT_RECEIVED == LenEthStatusRxQueue3[LucCtrlCnt])
            #endif
            && (GusRxFrameCnt_0[LucCtrlCnt] != EthTxTotal[LucCtrlCnt]));
      #else
      do
      {
        /* Check for received message */
        Eth_Receive(LucCtrlCnt, &LenEthRxStatus[LucCtrlCnt]);
      } while (ETH_NOT_RECEIVED == LenEthRxStatus[LucCtrlCnt]);
      #endif
    }
    #endif

    /************************** Frame statistics ***************************/

    #if (ETH_GET_DROP_COUNT_API == STD_ON)
    /* Get drop packets statistic */
    do
    {
        Eth_GetDropCount(LucCtrlCnt, CountValues, DropCount);
      
        if ((0 == DropCount[CRC_ERROR]) && (0 == DropCount[UNDERSIZE_PACKET_ERROR])
          && (0 == DropCount[OVERSIZE_PACKET_ERROR]) && (0 == DropCount[ALIGNMENT_ERROR])
          && (0 == DropCount[LATE_COLLISION]))
        {
          EthPassedCount_0[EthCheckCount_0] = ETH_PASSED;
          break;
        }
    } while (1);
    EthCheckCount_0++;
    #endif

    #if (ETH_GET_COUNTER_VALUES_API == STD_ON)
    /* Get drop packets statistic */
    do
    {
        Eth_GetCounterValues(LucCtrlCnt, &CounterPtr);
      
        if ((0 == CounterPtr.DropPktBufOverrun) && (0 == CounterPtr.DropPktCrc) && (0 == CounterPtr.UndersizePkt) &&
            (0 == CounterPtr.OversizePkt) && (0 == CounterPtr.AlgnmtErr))
        {
          EthPassedCount_0[EthCheckCount_0] = ETH_PASSED;
          break;
        }
    } while (1);
    EthCheckCount_0++;
    #endif

    #if (ETH_GET_TX_ERROR_COUNTER_VALUES_API == STD_ON)
    /* This feature is not supported */
    Eth_GetTxErrorCounterValues(LucCtrlCnt, &TxErrorCounterValues);
    #endif

    #if (ETH_GET_ETHER_STATS_API == STD_ON)
    /* Get statistic */
    do
    {
      Eth_GetEtherStats(LucCtrlCnt, etherStats);
      
      /* Multicast packets dropped due to Eth_UpdatePhysAddrFilter is INCLUDED in statistic */
      if ((0 == etherStats[DROP_EVENTS]) && (0 == etherStats[BROADCAST_PACKETS]) &&
          (RX_MULTICAST_FRAME_TOTAL == etherStats[MULTICAST_PACKETS]) && (0 == etherStats[CRC_ALIGN_ERRORS]) &&
          (0 == etherStats[UNDERSIZE_ERRORS]) && (0 == etherStats[OVERSIZE_ERRORS]) &&
          (0 == etherStats[LATE_COLLISIONS]))
      {
        EthPassedCount_0[EthCheckCount_0] = ETH_PASSED;
        break;
      }
    } while (1);
    EthCheckCount_0++;
    #endif

    #if (ETH_GET_RX_STATS_API == STD_ON)
    /* Get statistic */
    do
    {
      Eth_GetRxStats(LucCtrlCnt, &RxStats);
      
      if ((EthTxTotal[LucCtrlCnt] == RxStats.RxStatsPkts) && (0 == RxStats.RxStatsBroadcastPkts) &&
          (RX_MULTICAST_FRAME_TOTAL == RxStats.RxStatsMulticastPkts) && (0 == RxStats.RxStatsCrcAlignErrors) &&
          (0 == RxStats.RxStatsUndersizePkts) && (0 == RxStats.RxStatsOversizePkts))
      {
        EthPassedCount_0[EthCheckCount_0] = ETH_PASSED;
        break;
      }
    } while (1);
    EthCheckCount_0++;
    #endif

    #if (ETH_GET_TX_STATS_API == STD_ON)
    /* Get statistic */
    do
    {
      Eth_GetTxStats(LucCtrlCnt, &TxStats);
      if ((OCTET_TOTAL == TxStats.TxNumberOfOctets) && (RX_MULTICAST_FRAME_TOTAL == TxStats.TxNUcastPkts)
          && (RX_UNICAST_FRAME_TOTAL == TxStats.TxUniCastPkts))
      {
        EthPassedCount_0[EthCheckCount_0] = ETH_PASSED;
        break;
      }
    } while (1);
    EthCheckCount_0++;
    #endif
  }

      /* Invoke Eth_DeInit to reset process needed for the initialization of the Ethernet Driver*/
  #if (ETH_DEINIT_API == STD_ON)
  Eth_DeInit(0);
  #endif

  /************************** Checkpoint validate *****************************/

  for (LulInc = 0; LulInc < EthCheckCount_0; LulInc++)
  {
    if (EthPassedCount_0[LulInc] != ETH_PASSED)
    {
      sample_NG_end();
    }
  }

  sample_end();
} /* End of main() function */

/******************************************************************************/
/* Send message                                                               */
/******************************************************************************/
static void SendData
(
  uint8 CtrlIdx,
  uint8 *Buf,
  uint16 LenByte,
  Eth_FrameType FrameType,
  uint8 Priority,
  const uint8* PhysAddrPtr
)
{
  Std_ReturnType LucReturnValue;
  Eth_DataType *BufPtr;
  Eth_BufIdxType BufIdx;
  BufReq_ReturnType LenRequestBuffer;
  uint16 LusLength;

  LusLength = LenByte;
  GucTxConfirmed_0[CtrlIdx] = 0;

  /* Invoke Eth_ProvideTxBuffer to get available buffer */
  LenRequestBuffer = Eth_ProvideTxBuffer(CtrlIdx,
    #if (ETH_AR_VERSION >= ETH_AR_431_VERSION)
    Priority,
    #endif
    &BufIdx, &BufPtr, &LusLength);

  if ((BUFREQ_OK == LenRequestBuffer) && (Buf != NULL_PTR))
  {
    EthPassedCount_0[EthCheckCount_0] = ETH_PASSED;
  }
  else
  {
    #if (ETH_CTRL_ENABLE_TX_POLLING == STD_ON)
    Eth_TxConfirmation(CtrlIdx);
    #endif
    return;
  }
  EthCheckCount_0++;

  #if (ETH_GLOBAL_TIME_SUPPORT == STD_ON)
  /* Invoke Eth_EnableEgressTimeStamp to activate egress time stamping */
  Eth_EnableEgressTimeStamp(CtrlIdx, BufIdx);
  #endif
  /* Copy Transmit data to the buffer to transmit */
  memcpy(BufPtr, Buf, LenByte);

  do
  {
    LucReturnValue = Eth_Transmit(CtrlIdx, BufIdx, FrameType, ETH_TRUE, LenByte, PhysAddrPtr);
  } while (E_NOT_OK == LucReturnValue);
  #if (ETH_CTRL_ENABLE_TX_POLLING == STD_ON)
  do
  {
    /* Polling for Tx confirmation */
    Eth_TxConfirmation(CtrlIdx);
  } while (0 == GucTxConfirmed_0[CtrlIdx]);
  #endif
}

/******************************************************************************
**                           Notification Functions                          **
******************************************************************************/


/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
