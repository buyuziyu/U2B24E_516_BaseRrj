/*============================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                         */
/* Module       = App_CAN_Multi_Sample.c                                      */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2021-2025 Renesas Electronics Corporation. All rights reserved.        */
/*============================================================================*/
/* Purpose:                                                                   */
/* This file contains sample application for CAN Driver Component             */
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
 * 2.4.0: 30/05/2025  : Change GucReturnCount to LucReturnCount
 * 2.3.1: 29/04/2025  : Update precompile conditions
 *        31/03/2025  : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 * 2.3.0: 28/02/2025  : Update SW-VERSION for RH850/Ver22.01.00/Ver22.01.00.D 
 *                      Final Release
 * 2.2.0: 31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final 
 *                      Release
 * 2.1.3: 31/10/2024  : Remove unuse setting for U2Ax
 * 2.1.2: 31/08/2024  : Update to support CANXL frame
 * 2.1.1: 30/08/2024  : Update checkpoint conditions for CAN XL controller
 *                    : Change CAN_APPL_CODE to CAN_CALLOUT_CODE
 *                    : Remove macro U2Cx_VLAB_CAN_USED
 *                    : Support multicore for CANXL
 * 2.0.0: 09/08/2023  : Update to support Multicore
 * 1.0.0: 30/08/2021  : Initial Version
 */
/******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "App_CAN_Multi_Sample.h"
#include "App_CAN_Common_Sample_0.h"
#include "App_CAN_Common_Sample_1.h"

/*******************************************************************************
**                      Defines                                               **
*******************************************************************************/


/*******************************************************************************
**                         Global Data                                        **
*******************************************************************************/
#if (CAN_MULTI_CORE_SUPPORT == STD_ON)
void Guard_Enable_PE(void);
#endif
uint8 GaaByteArray0[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
uint8 GaaByteArray1[] = { 0x02, 0x04, 0x06, 0x08, 0x01, 0x03, 0x05, 0x07};
volatile uint8 GblCheckInit = 0;

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
#if (CAN_CANXL_GLOBAL_TIME_SUPPORT == STD_ON)
Eth_TimeStampQualType TxTimeQual;
Eth_TimeStampType TxTimeStamp[2];
Eth_TimeStampType RxTimeStamp[2];
#endif /* CAN_CANXL_GLOBAL_TIME_SUPPORT */
/* Target MAC address */
uint8 mac_tgt_addr[2U][6U] =
{
  {0x75U, 0x90U, 0x50U, 0xFFU, 0xFFU, 0x00U}
  ,{0x75U, 0x90U, 0x50U, 0xFFU, 0xFFU, 0x01U}
};

uint8 mac_board_addr[2U][6U] =
{
  {0x75U, 0x90U, 0x50U, 0x11U, 0x22U, 0x33U}
  ,{0x75U, 0x90U, 0x50U, 0x44U, 0x55U, 0x66U}
};

uint8 RetrieveMacAddr[2][6] =
{
  {0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U}
  ,{0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U}
};
/*---------------------------------------------------*/
/* Receive and Transmit Buffers */
/*---------------------------------------------------*/
uint8 TxEthFrame[6][63] =
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

/*******************************************************************************
**                        User function prototypes                            **
*******************************************************************************/
/*******************************************************************************
*                      Function Definitions                                  **
*******************************************************************************/
/*******************************************************************************
** Function Name         : Can_SampleApp_End
**
** Description           : While true when Sample application complete
*******************************************************************************/
void Can_SampleApp_End(void)
{
  while (1)
  {
    /* No action required*/
  }
}


/*******************************************************************************
                          UserCalloutFunction
*******************************************************************************/

#if defined(CAN_LPDU_RECEIVE_CALLOUT_FUNCTION)
/* Callout function */
FUNC(boolean, CAN_CALLOUT_CODE) UserCalloutFunction(
  uint16 Hrh, Can_IdType CanId,
  uint8 CanDataLength,
  P2CONST(uint8, CAN_APPL_DATA, AUTOMATIC) CanSduPtr)
{
  uint8 LucCoreId;
  /* Get Core id for code branching */
  LucCoreId = (uint8)GetCoreID();
  /* Covert Core Id to Core Index */
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
    if (LucCoreId == 0 )
    {
      GucReturnCount_0 ++;
    }
    else
    {
      GucReturnCount_1 ++;
    }
    // GucReturnCount++;
  }
  /* return TRUE unconditionally */
  return TRUE;
}
#endif

/*******************************************************************************
** Function Name         : Init_MCAL
**
** Description           : Init Mcu, Port, Wdg, Can
*******************************************************************************/

void Appl_Can_Init(void)
{
  /* System Initialization
  (Clock Initialization, Programmable Peripheral I/O register,
  Selecting the clock for the CAN Module ETC..) */
  Clock_Init();

  /* Initialize MCU */
  Mcu_Init();

  /* CAN Port Pin Configuration */
  Port_Init();
  /* Initialize Watchdog */
  Wdg_Init();

  /* Set "Table Reference Interrupt" for all of CAN/TAUD interrupts. */
  
  #if (CAN_MULTI_CORE_SUPPORT == STD_ON)
  #ifndef CAN_U2Ax_USED
  Guard_Enable_PE();
  #endif
  #endif
  
  /* Global Initialization */
  Can_Init(Can_Config);
  
  GblCheckInit = 1;
}


#if (CAN_MULTI_CORE_SUPPORT == STD_ON)
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
  (uint32) 0xFFC72D00UL, //PBG32_base
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
  #if defined(CAN_U2B24E_516_USED) || defined(CAN_U2B12E_USED)
  (uint32) 0xFFF6D400UL, //PBG8M0_base
  #endif
  (uint32) 0xFF97A000UL, //PBG8L0_base
  #if defined(CAN_U2B24E_516_USED) || defined(CAN_U2B12E_USED)
  (uint32) 0xFF97A100UL, //PBG8L1_base
  (uint32) 0xFFF6E000UL, //PBG8UL0_base
  #endif
  (uint32) 0xFF0A1300UL, //PBG90_base
  (uint32) 0xFF0A1500UL, //PBG91_base
  (uint32) 0xFF0A1700UL, //PBG92_base
  (uint32) 0xFF879400UL, //PBG100_base
  (uint32) 0xFF879500UL, //PBG101_base
  (uint32) 0xFF8B1400UL, //PBG11H0_base
  (uint32) 0xFF8B1600UL, //PBG11H1_base
  (uint32) 0xFF8B1800UL, //PBG11H2_base
  (uint32) 0xFF8F8000UL, //PBG11L0_base    
  (uint32) 0xFF860000UL, //PBG_CANFD0_base
  (uint32) 0xFF860800UL, //PBG_CANFD1_base
  #if defined(CAN_U2B24E_516_USED)
  (uint32) 0xFF861000UL, //PBG_CANFD2_base
  #endif
  #if !defined(CAN_U2B24E_516_USED) && !defined(CAN_U2B12E_USED)
  (uint32) 0xFF88FA00UL, //PBG_ATU_base
  #endif
  (uint32) 0xFFF60000UL  //PBG_GTM_base
  };
  #if (CAN_CANXL_SUPPORTED == STD_ON)
  const uint32 HBGXX_base[]=
  {
    #if defined(CAN_U2B24E_516_USED) || defined(CAN_U2B12E_USED)
    (uint32) 0xFF0D0A00UL, //HBG913_base
    (uint32) 0xFF0D0B00UL, //HBG914_base
    #else
    (uint32) 0xFF0D0A00UL, //HBG92_base
    (uint32) 0xFF0D0C00UL, //HBG93_base
    #endif
  };
  #endif
  //Enable write
  for (int i =0; i<LucNumofRSLVXX;i++)
  {
  volatile uint32 *ptr;
  ptr = (volatile uint32 *)(RSLVXX_base[i] + (uint32)0x18UL);
  *ptr = (uint32)0xA5A5A501UL;
  }
  
  #if (CAN_CANXL_SUPPORTED == STD_ON)
  // Write HBGxx
  for (int i =0; i<2;i++)
  {
    volatile uint32 *ptr;
    ptr = (volatile uint32 *)(HBGXX_base[i]);
    *ptr |= 0x00000143UL;
  }
  #endif
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
#endif /* #if (CAN_MULTI_CORE_SUPPORT == STD_ON) */

/******************************************************************************/
/*                             Send ETH message                               */
/******************************************************************************/
#if (CAN_CANXL_SUPPORTED == STD_ON)
void SendEthFrame( uint8 CtrlIdx, uint8 *Buf, uint16 LenByte, Eth_FrameType FrameType,
                   uint8 Priority, const uint8* PhysAddrPtr)
{
  uint8 LucReturnCount;
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
  uint8 LucCoreId;

  /* Get Core id for code branching */
  LucCoreId = (uint8)GetCoreID();
  LucChannelId = Can_GaaControllerPCConfig0[CtrlIdx].ucCh;
  LusLength = LenByte;
  /* initialize value for GucTxConfirmed */
  GucTxConfirmed[LucChannelId] = 0;
  LucReturnCount = 0;

  /* ---------------------------------first Frame-------------------------------------- */
  /* Invoke CanXL_ProvideTxBuffer to get available buffer */
  LenRequestBuffer = CanXL_ProvideTxBuffer(CtrlIdx, Priority, &BufIdx, &BufPtr, &LusLength);

  if ((LenRequestBuffer == BUFREQ_OK) && (Buf != NULL_PTR))
  {
    LucReturnCount++;
  }

  for (LulCount = 0; LulCount < LusLength; LulCount++)
  {
    *(BufPtr + LulCount) = *(Buf + LulCount);
  }

  LucReturnValue = CanXL_Transmit(CtrlIdx, BufIdx, FrameType, CAN_TRUE, LusLength, PhysAddrPtr);
  if (E_OK == LucReturnValue)
  {
    LucReturnCount++;
  }

  LulCount = 100000;
  while (LulCount--);

  /* ---------------------------------seconds Frame-------------------------------------- */
  /* Invoke CanXL_ProvideTxBuffer to get available buffer */
  LenRequestBuffer = CanXL_ProvideTxBuffer(CtrlIdx, Priority, &BufIdx_1, &BufPtr_1, &LusLength);

  if ((LenRequestBuffer == BUFREQ_OK) && (Buf != NULL_PTR))
  {
    LucReturnCount++;
  }

  /* Copy Transmit data to the buffer to transmit */
  for (LulCount = 0; LulCount < LusLength; LulCount++)
  {
    *(BufPtr_1 + LulCount) = *(Buf + LulCount);
  }

  LucReturnValue = CanXL_Transmit(CtrlIdx, BufIdx_1, FrameType, CAN_TRUE, LusLength, PhysAddrPtr);
  if (E_OK == LucReturnValue)
  {
    LucReturnCount++;
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
    LucReturnCount++;
  }
  
  if (LucCoreId == 0 )
  {
      GucReturnCount_0 += LucReturnCount;
  }
  else
  {
      GucReturnCount_1 += LucReturnCount;
  }
}

void Appl_CanXL_TestMode(uint32 LucController)
{
  uint8 LucCtrlInfoIndex;

  LucCtrlInfoIndex = Can_GpConfig->pCanXLSecondPhysicalControllerToIndex[LucController];
  CanXL_GaaRegs[LucCtrlInfoIndex].pPRT->ulLOCK = (0x6789U) << 16U;
  CanXL_GaaRegs[LucCtrlInfoIndex].pPRT->ulLOCK = (0x9876U) << 16U;
  CanXL_GaaRegs[LucCtrlInfoIndex].pPRT->ulCTRL |= 0x01 << 12U;
  CanXL_GaaRegs[LucCtrlInfoIndex].pPRT->ulTEST |= 0x11;
}
#endif /* CAN_CANXL_SUPPORTED == STD_ON */

 /*******************************************************************************
 **                          End of File                                       **
 *******************************************************************************/
