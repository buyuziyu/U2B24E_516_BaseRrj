/*============================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                         */
/* Module       = App_ETH_U2B12-E_Sample.c                                    */
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
 * 2.3.1: 31/03/2025    : Added condition to initialize for ETHA port only in Sgmii_Init 
 *                      : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 * 2.3.0: 28/02/2025    : Update function Mcu_Init()
 * 2.2.0: 31/12/2024    : Update SW-VERSION for Ver22.02.00(D) U2Bx Final Release
 * 2.1.2: 31/10/2024    : Increase SW-VERSION to 2.1.2
 * 2.1.1: 31/05/2024    : Initial Version.
 */
/******************************************************************************/

/*******************************************************************************
**                     Include Section                                        **
*******************************************************************************/
#include "App_ETH_Device_Sample.h"
#include <stdio.h>
#include <string.h>
/*******************************************************************************
**                            Macros                                          **
*******************************************************************************/
#define DISABLE_WRITE_KEY_CODE  (0xA5A5A500UL)
#define ENABLE_WRITE_KEY_CODE   (0xA5A5A501UL)

/*******************************************************************************
**                      Phy Initialization                                    **
*******************************************************************************/
#define ETH_CPUCLK_MHZ 400UL
#define ETH_WAIT_NS(t)  { volatile uint32 cnt; \
  for ( cnt = 0;cnt < ((((uint32)ETH_CPUCLK_MHZ * ((uint32)t)) / (uint32)1000) + (uint32)1);cnt++ ); }

/*------------------------------------------------------------------------------------------------------------------------------*/
#define ETH_REG0_BASIC_CONTROL_REG        (0U)
#define ETH_REG1_BASIC_STATUS_REG         (1U)
#define ETH_REG2_PHY_IDENTIFIER1_REG      (2U)
#define ETH_REG3_PHY_IDENTIFIER2_REG      (3U)
#define ETH_REG17_MODE_CONTROL_REG        (17U)
#define ETH_REG27_CONTROL_INDICATION_REG  (27U)
#define ETH_REG30_INTERRUPT_MASK_REG      (30U)
#define ETH_REG31_PHY_SPECIAL_CONTROL_REG (31U)

/* Soft reset request.                                          */
#define ETH_REG0_SW_RESET                (0x8000U)
#define ETH_REG0_NEAR_LOOPBACK_ON        (0x4000U)
#define ETH_REG0_NEAR_LOOPBACK_OFF       (0x0000U)
#define ETH_REG0_SPEED_100MBPS           (0x2000U)
#define ETH_REG0_SPEED_10MBPS            (0x0000U)
#define ETH_REG0_AUTONEG_PROC_ON         (0x1000U)
#define ETH_REG0_AUTONEG_PROC_OFF        (0x0000U)
#define ETH_REG0_POWERDOWN_MODE_ON       (0x0800U)
#define ETH_REG0_POWERDOWN_MODE_OFF      (0x0000U)
#define ETH_REG0_ELEC_ISOLATE_ON         (0x0400U)
#define ETH_REG0_ELEC_ISOLATE_OFF        (0x0000U)
#define ETH_REG0_RESTART_AUTONEG         (0x0200U)
#define ETH_REG0_DUPLEX_FULL             (0x0100U)
#define ETH_REG0_DUPLEX_HALF             (0x0000U)
#define ETH_REG0_COLTEST_ON              (0x0008U)
#define ETH_REG0_COLTEST_OFF             (0x0000U)

#define ETH_REG17_ENE_POWERDOWN_MODE_OFF (0x0000U)
#define ETH_REG17_ENE_POWERDOWN_MODE_ON  (0x2000U)
#define ETH_REG17_LOWSQEN_HIGHER         (0x0000U)
#define ETH_REG17_LOWSQEN_LOWER          (0x0800U)
#define ETH_REG17_SMI_WITH_PREAMBLE      (0x0000U)
#define ETH_REG17_SMI_WITHOUT_PREAMBLE   (0x0400U)
/* Only RMII mode.                                              */
#define ETH_REG17_FAR_LOOPBACK_ON        (0x0200U)
#define ETH_REG17_FAR_LOOPBACK_OFF       (0x0000U)
#define ETH_REG17_ALT_INTERRUPT_ENABLE   (0x0040U)
#define ETH_REG17_ALT_INTERRUPT_DISABLE  (0x0000U)
#define ETH_REG17_IGNORE_PHY_ADDR_OFF    (0x0000U)
#define ETH_REG17_IGNORE_PHY_ADDR_ON     (0x0008U)
#define ETH_REG17_FORCE_100TX_LINK_OFF   (0x0000U)
/* Only in test.                                                */
#define ETH_REG17_FORCE_100TX_LINK_ON    (0x0004U)

#define ETH_REG27_AUTOMDIX_ENABLE        (0x0000U)
#define ETH_REG27_AUTOMDIX_DISABLE       (0x8000U)
#define ETH_REG27_MANCHSEL_MDI           (0x0000U)
#define ETH_REG27_MANCHSEL_MDIX          (0x2000U)
#define ETH_REG27_SQE_TEST_ENABLE        (0x0000U)
#define ETH_REG27_SQE_TEST_DISABLE       (0x0800U)
#define ETH_REG27_10BASET_POL_NORMAL     (0x0000U)
#define ETH_REG27_10BASET_POL_REVERSE    (0x0010U)

#define ETH_REG30_INT1_ENABLE            (0x0002U)
#define ETH_REG30_INT1_DISABLE           (0x0000U)
#define ETH_REG30_INT2_ENABLE            (0x0004U)
#define ETH_REG30_INT2_DISABLE           (0x0000U)
#define ETH_REG30_INT3_ENABLE            (0x0008U)
#define ETH_REG30_INT3_DISABLE           (0x0000U)
#define ETH_REG30_INT4_ENABLE            (0x0010U)
#define ETH_REG30_INT4_DISABLE           (0x0000U)
#define ETH_REG30_INT5_ENABLE            (0x0020U)
#define ETH_REG30_INT5_DISABLE           (0x0000U)
#define ETH_REG30_INT6_ENABLE            (0x0040U)
#define ETH_REG30_INT6_DISABLE           (0x0000U)
#define ETH_REG30_INT7_ENABLE            (0x0080U)
#define ETH_REG30_INT7_DISABLE           (0x0000U)

#define ETH_REG31_4B5B_ENCDEC_ENABLE     (0x0040U)
#define ETH_REG31_4B5B_ENCDEC_DISABLE    (0x0000U)
#define ETH_REG31_DATA_SCRMBL_ENABLE     (0x0000U)
#define ETH_REG31_DATA_SCRMBL_DISABLE    (0x0001U)

#define ETH_REG2_DEF_VALUE               (0x0007U)
#define ETH_REG3_DEF_VALUE               (0xC0C4U)
#define ETH_REG16_DEF_VALUE              (0x0040U)

#define ETH_CHECKPOINT_TOTAL          40U
#define ETH_FAILED                    0
#define ETH_PASSED                    1
#define ETH_NC_TYPE                   0x88F7U /* Precision Time Protocol (PTP) over Ethernet (IEEE 1588)  */
#define PHY_TRCV_CTRL_REG             0U
#define PHY_TRCV_STATUS_REG           1U
#define PHY_TRCV_ID1_REG              2U  /* PHY Identifier 1 (0x0141 is set for 88E1112) */
#define FRAME_LEN                     62U       /* Without header and FCS.    */
#define FRAME_LEN_MTU                 1500U     /* Maximum payload size */
#define APP_ETH_MACADDR_LEN           6U
#define STREAMID_LEN                  8U
#define ETHTYPE_LEN                   2U
#define PHY_LINKUP_BIT                0x002CU

#define RX_QUEUE_0                    0U
#define RX_QUEUE_1                    1U
#define RX_QUEUE_2                    2U
#define RX_QUEUE_3                    3U
/* Time-out */
#define ETH_TIMEOUT                   (uint32)0x200000

#define BUFFER_OVERRUN_ERROR          1U
#define CRC_ERROR                     2U
#define UNDERSIZE_PACKET_ERROR        3U
#define OVERSIZE_PACKET_ERROR         4U
#define ALIGNMENT_ERROR               5U

#define ALL_PACKETS                   3U
#define BROADCAST_PACKETS             4U
#define MULTICAST_PACKETS             5U
#define CRC_ALIGN_ERRORS              6U
#define UNDERSIZE_ERRORS              7U
#define OVERSIZE_ERRORS               8U

/* Marvell PHY Chip Macro*/
// Auto-Negotiation Flags - reg 7.0x0203
#define MRVL_88Q2112_AN_FE_ABILITY      0x0020
#define MRVL_88Q2112_AN_GE_ABILITY      0x0080
#define MRVL_88Q2112_PRODUCT_ID         0x0018
#define MRVL_88Q2112_AN_PREFER_MASTER   0x0010

// Auto-Negotiation Controls - reg 7.0x0200
#define MRVL_88Q2112_AN_ENABLE          0x1000
#define MRVL_88Q2112_AN_RESTART         0x0200

// Auto-Negotiation Status - reg 7.0x0201
#define MRVL_88Q2112_AN_COMPLETE        0x0020

// PHY Revisions
#define MRVL_88Q2112_A2     0x0003
#define MRVL_88Q2112_A1     0x0002
#define MRVL_88Q2112_A0     0x0001

#if (ETH_MACRO_ETNE == STD_ON)
/* ETHA External Register Verify */
static uint32 GulPortId;
#endif /* ETH_MACRO_ETNE == STD_ON */
#define TX_TOTAL_EHAx      7UL
#define TX_TOTAL_GWCA      0UL
#define TX_TOTAL_ETNF      4UL
volatile uint16 EthTxTotal[ETH_TOTAL_CTRL_CONFIG] = 
{
  #ifdef ETHRSW0
  TX_TOTAL_EHAx, 
  #endif
  #ifdef ETHRSW1
  TX_TOTAL_EHAx,
  #endif
  #ifdef ETHGWCA0 
  TX_TOTAL_GWCA,
  #endif
  #ifdef ETHAVB0
  TX_TOTAL_ETNF
  #endif
};
/*------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------*/
/* User configuration                                                                                                           */
/*------------------------------------------------------------------------------------------------------------------------------*/
#define ETH_PHY_ADDR                     (0x1FU)
#define ETH_REG0_NEAR_LOOPBACK_CFG       ETH_REG0_NEAR_LOOPBACK_OFF           /* Near loopback mode. [ON/OFF]                 */
#define ETH_REG0_SPEED_CFG               ETH_REG0_SPEED_100MBPS               /* Ethernet network speed. [10MBPS/100MBPS]     */
#define ETH_REG0_AUTONEG_PROC_CFG        ETH_REG0_AUTONEG_PROC_ON             /* Auto negotiation. [ON/OFF]                   */
#define ETH_REG0_POWERDOWN_MODE_CFG      ETH_REG0_POWERDOWN_MODE_OFF          /* General Powerdown mode. [ON/OFF]             */
#define ETH_REG0_ELEC_ISOLATE_CFG        ETH_REG0_ELEC_ISOLATE_OFF            /* PHY Electrical Isolcation. [ON/OFF]          */
#define ETH_REG0_DUPLEX_CFG              ETH_REG0_DUPLEX_FULL                 /* Duplex mode. [HALF/FULL]                     */
#define ETH_REG0_COLTEST_CFG             ETH_REG0_COLTEST_OFF                 /* Colision Test. [ON/OFF]                      */

#define ETH_REG17_ENE_POWERDOWN_MODE_CFG ETH_REG17_ENE_POWERDOWN_MODE_OFF     /* Energy Detect Powerdown mode. [ON/OFF]       */
#define ETH_REG17_LOWSQEN_CFG            ETH_REG17_LOWSQEN_LOWER              /* Threshold of power down mode. [LOWER/HIGHER] */
#define ETH_REG17_SMI_PREAMBLE_CFG       ETH_REG17_SMI_WITH_PREAMBLE          /* SMI preamble detection. [WITH/WITHOUT]       */
#define ETH_REG17_FAR_LOOPBACK_CFG       ETH_REG17_FAR_LOOPBACK_OFF           /* Far loopback mode. [ON/OFF] (RMII only)      */
#define ETH_REG17_ALT_INTERRUPT_CFG      ETH_REG17_ALT_INTERRUPT_DISABLE      /* Alternative Interrupt. [ENABLE/DISABLE]      */
#define ETH_REG17_IGNORE_PHY_ADDR_CFG    ETH_REG17_IGNORE_PHY_ADDR_OFF        /* Ignore PHY address in SMI. [ON/OFF]          */
#define ETH_REG17_FORCE_100TX_LINK_CFG   ETH_REG17_FORCE_100TX_LINK_OFF       /* Force 100TX-LINK. [ON/OFF] (test only)       */

#define ETH_REG27_AUTOMDIX_CFG           ETH_REG27_AUTOMDIX_DISABLE           /* Auto-MDIX. [ENABLE/DISABLE]                  */
#define ETH_REG27_MANCHSEL_CFG           ETH_REG27_MANCHSEL_MDI               /* Manual Channel Select. [MDI/MDIX]            */
#define ETH_REG27_SQE_TEST_CFG           ETH_REG27_SQE_TEST_DISABLE           /* SQE Test. [ENABLE/DISABLE]                   */
#define ETH_REG27_10BASET_POL_CFG        ETH_REG27_10BASET_POL_NORMAL         /* Polarity of 10Base-T. [NORMAL/REVERSE]       */

#define ETH_REG30_INT1_CFG               ETH_REG30_INT1_DISABLE   /* Rx Auto Negotiation Page interrupt. [ENABLE/DISABLE]     */
#define ETH_REG30_INT2_CFG               ETH_REG30_INT2_DISABLE   /* Parallel Detection Failure interrupt. [ENABLE/DISABLE]   */
#define ETH_REG30_INT3_CFG               ETH_REG30_INT3_DISABLE   /* Auto Negotiation LP Ack interrupt. [ENABLE/DISABLE]      */
#define ETH_REG30_INT4_CFG               ETH_REG30_INT4_DISABLE   /* Link Down interrupt. [ENABLE/DISABLE]                    */
#define ETH_REG30_INT5_CFG               ETH_REG30_INT5_DISABLE   /* Remote Fault detection interrupt. [ENABLE/DISABLE]       */
#define ETH_REG30_INT6_CFG               ETH_REG30_INT6_DISABLE   /* Auto Negotiation completion interrupt. [ENABLE/DISABLE]  */
#define ETH_REG30_INT7_CFG               ETH_REG30_INT7_DISABLE   /* Energy Detect Powerdown interrupt. [ENABLE/DISABLE]      */

#define ETH_REG31_4B5B_ENCDEC_CFG        ETH_REG31_4B5B_ENCDEC_ENABLE         /* 4B5B Enc/Decoding. [ENABLE/DISABLE]          */
#define ETH_REG31_DATA_SCRMBL_CFG        ETH_REG31_DATA_SCRMBL_ENABLE         /* Data Scrambling. [ENABLE/DISABLE]            */

/*******************************************************************************
**                         Global Data                                        **
*******************************************************************************/

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/

/*******************************************************************************
**                        Global variables                                    **
*******************************************************************************/

/*******************************************************************************
**                      ISR Defines                                           **
*******************************************************************************/

/*******************************************************************************
**                      Mcu Initialization                                    **
*******************************************************************************/
void Mcu_Init(void)
{
  /**********************************************************/
  /* Interrupt Controller                                      */
  /* Set Reference Table Method for RSW */
  EIC708 |= (uint16)(1 << 6);
  EIC709 |= (uint16)(1 << 6);
  EIC710 |= (uint16)(1 << 6);
  EIC711 |= (uint16)(1 << 6);
  EIC712 |= (uint16)(1 << 6);
  EIC713 |= (uint16)(1 << 6);
  EIC714 |= (uint16)(1 << 6);
  EIC715 |= (uint16)(1 << 6);

  /* Following settings are for AVBT1S. */
  EIC964 |= (uint16)(1 << 6);
  EIC965 |= (uint16)(1 << 6);
  EIC966 |= (uint16)(1 << 6);
  EIC967 |= (uint16)(1 << 6);
  

  /**********************************************************/

  /* Standby Controller                                      */

  /* Release the write protection of Standby controller register.*/
  MSRKCPROT = ENABLE_WRITE_KEY_CODE;

  /* Enable clocks supplied for ES0, ES1 */
  MSR_ETNF = 0x0UL;
  while (MSR_ETNF != 0);

  /* Enable clocks supplied for ES0 */
  MSR_ETN &= ~0x00000017UL;
  while (MSR_ETN != 0);

  /*Set the write protection of Standby controller registers.*/
  MSRKCPROT = DISABLE_WRITE_KEY_CODE;

  /* Enable interrupts */
  __asm("ei");
}

#if defined(RUN_OTHER_PE)
/* Enable register write to all HWIP for other than PE0 */
void Guard_Enable_PE()
{
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
    (uint32) 0xFFF6D480UL, //PBGERRSLV8M0_base
    (uint32) 0xFF97A200UL, //PBGERRSLV8L0_base
    (uint32) 0xFFF6E080UL, //PBGERRSLV8UL0_base
    (uint32) 0xFF0A1400UL, //PBGERRSLV90_base
    (uint32) 0xFF0A1600UL, //PBGERRSLV91_base
    (uint32) 0xFF87A000UL, //PBGERRSLV100_base
    (uint32) 0xFF8B2000UL, //PBGERRSLV11H0_base
    (uint32) 0xFF8F8100UL, //PBGERRSLV11L0_base
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
    (uint32) 0xFFF6D400UL, //PBG8M0_base
    (uint32) 0xFF97A000UL, //PBG8L0_base
    (uint32) 0xFF97A100UL, //PBG8L1_base
    (uint32) 0xFFF6E000UL, //PBG8UL0_base
    (uint32) 0xFF0A1300UL, //PBG90_base
    (uint32) 0xFF0A1500UL, //PBG91_base
    (uint32) 0xFF0A1700UL, //PBG92_base
    (uint32) 0xFF879400UL, //PBG100_base
    (uint32) 0xFF879500UL, //PBG101_base
    (uint32) 0xFF8B1400UL, //PBG11H0_base
    (uint32) 0xFF8B1600UL, //PBG11H1_base
    (uint32) 0xFF8B1800UL, //PBG11H2_base
    (uint32) 0xFF8F8000UL, //PBG11L0_base
  };

  //Enable write
  for (int i =0; i<sizeof(RSLVXX_base)/sizeof(RSLVXX_base[0]);i++)
  {
    volatile uint32 *ptr;
    ptr = (volatile uint32 *)(RSLVXX_base[i] + (uint32)0x18UL);
    *ptr = (uint32)0xA5A5A501UL;
  }

  //Write PBG0
  for (int i =0; i<sizeof(PBGXX_base)/sizeof(PBGXX_base[0]);i++)
  {
    for (int ii =0; ii<16;ii++)
    {
      volatile uint32 *ptr;
      ptr = (volatile uint32 *)(PBGXX_base[i] + ((uint32)ii * 0x8UL));
      *ptr |= 0x00000143UL;
    }
  }

  //Write PBG1
  for (int i =0; i<sizeof(PBGXX_base)/sizeof(PBGXX_base[0]);i++)
  {
    for (int ii =0; ii<16;ii++)
    {
      volatile uint32 *ptr;
      ptr = (volatile uint32 *)(PBGXX_base[i] + 0x4UL + ((uint32)ii * 0x8UL));
      *ptr |= 0xFFFFUL;
    }
  }

  //Disable write
  for (int i =0; i<sizeof(RSLVXX_base)/sizeof(RSLVXX_base[0]);i++)
  {
    volatile uint32 *ptr;
    ptr = (volatile uint32 *)(RSLVXX_base[i]+0x18UL);
    *ptr = 0xA5A5A500UL;
  }
}
#elif (ETH_MULTI_CORE_SUPPORT == STD_ON)
void Guard_Enable_PE(void)
{
  PEGKCPROT0 = 0xA5A5A501UL;
  PBGKCPROT90 = 0xA5A5A501UL;
  PBGKCPROT8L0 = 0xA5A5A501UL;
  
  PEGPROT0(0) |= 0x00000143UL;
  PEGPROT0(1) |= 0x00000143UL;
  PEGPROT0(2) |= 0x00000143UL;
  PEGPROT0(3) |= 0x00000143UL;
  PEGPROT0(4) |= 0x00000143UL;
  PEGPROT0(5) |= 0x00000143UL;
  PEGPROT0(6) |= 0x00000143UL;
  PEGPROT0(7) |= 0x00000143UL;

  PEGPROT1(0) |= 0x00000143UL;
  PEGPROT1(1) |= 0x00000143UL;
  PEGPROT1(2) |= 0x00000143UL;
  PEGPROT1(3) |= 0x00000143UL;
  PEGPROT1(4) |= 0x00000143UL;
  PEGPROT1(5) |= 0x00000143UL;
  PEGPROT1(6) |= 0x00000143UL;
  PEGPROT1(7) |= 0x00000143UL;

  PBG90PROT0(12) |= 0x00000143UL;
  PBG8L0PROT0(2) |= 0x00000143UL;
  PBG8L0PROT0(4) |= 0x00000143UL;
  PBG8L0PROT0(7) |= 0x00000143UL;
  PBG8L0PROT0(8) |= 0x00000143UL;
  PBG8L0PROT0(12) |= 0x00000143UL;
}
#endif

void Clock_Init(void)
{

  /* Wait to HSIntOSC clock is stable(HSOSCS.HSOSCSTAB = 1). */
  while ( (HSOSCS & 0x00000002ul) != 0x00000002ul )
  {
  }

  /* HSIntOSC stops operation in stand-by mode(HSOSCSTPM.MOSCSTPMSK = 0). */
  CLKKCPROT1  = ENABLE_WRITE_KEY_CODE;
  HSOSCSTPM   = 0x00000000UL;
  CLKKCPROT1  = DISABLE_WRITE_KEY_CODE;

  /***********/
  /* MainOSC */
  /***********/

  /* Start the MainOSC (MOSCE.MOSCENTRG = 1). */
  CLKKCPROT1  = ENABLE_WRITE_KEY_CODE;
  MOSCE       = 0x00000001ul;
  CLKKCPROT1  = DISABLE_WRITE_KEY_CODE;

  /* Confirm that the MainOSC has been started (MOSCS.MOSCSTAB = 1). */
  while ( (MOSCS & 0x00000002ul) != 0x00000002ul )
  {
  }

  /* MainOSC stops operation in stand-by mode(MOSCSTPM.MOSCSTPMSK = 0). */
  CLKKCPROT1  = ENABLE_WRITE_KEY_CODE;
  MOSCSTPM    = 0x00000000UL;
  CLKKCPROT1  = DISABLE_WRITE_KEY_CODE;



  /* Start the PLL (PLLE.PLLENTRG = 1). */
  CLKKCPROT1  = ENABLE_WRITE_KEY_CODE;
  PLLE        = 0x00000001ul;
  CLKKCPROT1  = DISABLE_WRITE_KEY_CODE;

  /* 4.Confirm that the PLL has been started (PLLS.PLLCLKSTAB = 1). */
  while ((PLLS & 0x00000003UL) != 0x00000003UL)
  {
  }

  /* PLL stops operation in stand-by mode(PLLSTPM.PLLSTPMSK = 0) */
  CLKKCPROT1  = ENABLE_WRITE_KEY_CODE;
  PLLSTPM     = 0x00000000ul;
  CLKKCPROT1  = DISABLE_WRITE_KEY_CODE;

  /* Select a source clock(CKS_CLEANC.CPUCLKSCSID = 0). */
  CLKKCPROT1  = ENABLE_WRITE_KEY_CODE;
  /* Selected Clock source ID=0:CLK_PLLO */
  /* (This setting dependencies Option Bytes. CKDIVMD = 11B) */
  CKSC_CPUC   = 0x00000000ul;
  CLKKCPROT1  = DISABLE_WRITE_KEY_CODE;

  /* Confirm completion of selection(CKSC_CPUS.CPUCLKSACT = 0). */
  while ( (CKSC_CPUS & 0x00000001ul) != 0x00000000ul )
  {
  }

CLKKCPROT1  = ENABLE_WRITE_KEY_CODE;
  /* Division ratio of clock source PLL is changed from 1 to 3/8 */
  CKD_PLLC = 0x6U;   /* Write 0110B in CKD_PLLC.PLLCLKDCSID */
  (void)CKD_PLLC;
  CKD_SSCGC = 0x6U;  /* Write 0110B in CKD_SSCGC.SSCGCLKDCSID */
  (void)CKD_SSCGC;
  EXECUTE_SYNCP();
  /* -- Divider clock synchronized for PLL -- */
  while ( (CKD_PLLS & (uint32)0x2) != (uint32)0x2U ); /* Read CKD_PLLS and verify that the value of PLLCLKDSYNC is 1B */
  /* Read CKS_CLEANS and verify that the value of SYSCLKSACT is 0B */
  while ( (CKS_CLEANS & (uint32)0x1U) != (uint32)0x0U );
  ETH_WAIT_NS(100 * 1000); /* 100us */

  /* Start of repetitions: 5 repetitions (800MHz) */
  /* Division ratio of clock source PLL is changed from 3/8 to 4/8 */
  CKD_PLLC = 0x8U;
  (void)CKD_PLLC;
  EXECUTE_SYNCP();
  while ( (CKD_PLLS & (uint32)0x2) != (uint32)0x2U );
  ETH_WAIT_NS(100 * 1000); /* 100us */
  /* Division ratio of clock source PLL is changed from 4/8 to 5/8 */
  CKD_PLLC = 0xAU;
  (void)CKD_PLLC;
  EXECUTE_SYNCP();
  while ( (CKD_PLLS & (uint32)0x2) != (uint32)0x2U );
  ETH_WAIT_NS(100 * 1000); /* 100us */
  /* Division ratio of clock source PLL is changed from 5/8 to 6/8 */
  CKD_PLLC = 0xCU;
  (void)CKD_PLLC;
  EXECUTE_SYNCP();
  while ( (CKD_PLLS & (uint32)0x2) != (uint32)0x2U );
  ETH_WAIT_NS(100 * 1000); /* 100us */
  /* Division ratio of clock source PLL is changed from 6/8 to 7/8 */
  CKD_PLLC = 0xEU;
  (void)CKD_PLLC;
  EXECUTE_SYNCP();
  while ( (CKD_PLLS & (uint32)0x2) != (uint32)0x2U );
  ETH_WAIT_NS(100 * 1000); /* 100us */
  /* Division ratio of clock source PLL is changed from 7/8 to 1 */
  CKD_PLLC = 0x0U;
  (void)CKD_PLLC;
  EXECUTE_SYNCP();
  while ( (CKD_PLLS & (uint32)0x2) != (uint32)0x2U );
  ETH_WAIT_NS(100 * 1000); /* 100us */
  /* End of repetitions for PLL */

CLKKCPROT1  = DISABLE_WRITE_KEY_CODE;
}

/*******************************************************************************
**                      Wdg Initialization                                    **
*******************************************************************************/
void Wdg_Init(void)
{
  /* Do nothing */
}

/*******************************************************************************
**                      Port Initialization                                   **
*******************************************************************************/
typedef enum ETag_EthTest_PortAltMode
{
  PORT_ALT_1 = 0,
  PORT_ALT_2,
  PORT_ALT_3,
  PORT_ALT_4,
  PORT_ALT_5,
  PORT_ALT_6,
  PORT_ALT_7,
  PORT_ALT_8,
  PORT_ALT_9,
  PORT_ALT_10,
  PORT_ALT_11,
  PORT_ALT_12,
  PORT_ALT_13,
  PORT_ALT_14,
  PORT_ALT_15,
  PORT_RESET=0xFFU
} EthTest_PortAltMode;
typedef enum ETag_EthTest_PortMode
{
  PORT_OUT = 0,
  PORT_IN,
  PORT_INOUT
} EthTest_PortMode;
typedef enum ETag_EthTest_PortSetPIPC
{
  CLEAR_PIPC = 0,
  SET_PIPC = 1,
  PortSetPIPC_UNSET=0xFFU
} EthTest_PortSetPIPC;
typedef enum ETag_EthTest_PortBufferType
{
  /*
   HWUM: PISn/JPIS0 — Port input buffer selection register
   HWUM: PISAn/JPISA0 – Port Input buffer Selection Advanced registe
   
    PISA | PIS  |
    0    | 0    | SHMT1
    0    | 1    | SHMT4
    1    | 0    | TTL
    1    | 1    | SHMTMSC
   */
  PORT_SHMT1 = 0,
  PORT_SHMT4,
  PORT_TTL,
  PORT_TTL_SHMTMSC,
  PortBufferType_UNSET=0xFFU
} EthTest_PortBufferType;


typedef enum ETag_EthTest_PortDriveStrength
{
  /*
   HWUM: PDSCn/JPDSC0 — Port Drive Strength Control Register
   HWUM: PUCCn/JPUCC0 — Port Universal Characteristic Control Register
   
    PUCC | PDSC |
    0    | 0    | Drive strength = 5 (very low)
    0    | 1    | Drive strength = 4 (low)
    1    | 0    | Drive strength = 3 (medium)
    1    | 1    | Drive strength = 2 (high) / Drive strength = 1 (very high)

   */
  PORT_STRENGTH_5 = 0,
  PORT_STRENGTH_4 = 1,
  PORT_STRENGTH_3 = 2,
  PORT_STRENGTH_2_1 = 3,
  PortDriveStrength_UNSET=0xFFU
} EthTest_PortDriveStrength;

typedef struct STag_EthTest_PortValue
{
  EthTest_PortMode PortMode;
  EthTest_PortAltMode PortAltMode;
  EthTest_PortSetPIPC PortSetPIPC;
  EthTest_PortBufferType PortBufferType;
  EthTest_PortDriveStrength PortStrength;
} EthTest_PortValue;

typedef struct STag_EthTest_PortSetting
{
  uint8 PortNumber;
  uint8 PinNumber;
  EthTest_PortValue PortValue;
} EthTest_PortSetting;

#define PORT_INVALID   255
static const EthTest_PortSetting U2BxE_Port_Setting[]  = {
#if (ETH_MACRO_ETNE == STD_ON)
  /* ETNE0 MII/SGMII */
  {12, 0,  {PORT_OUT,   PORT_ALT_8,  PortSetPIPC_UNSET, PortBufferType_UNSET, PortDriveStrength_UNSET} },     // P12_0  - ALT_OUT8    - ETH0_MDC
  {12, 1,  {PORT_INOUT, PORT_ALT_1,  SET_PIPC, PORT_TTL, PortDriveStrength_UNSET} },                          // P12_1  - ALT_INOUT1  - ETH0_MDIO
  {11, 0,  {PORT_OUT,   PORT_ALT_1,  PortSetPIPC_UNSET, PortBufferType_UNSET, PORT_STRENGTH_2_1} },           // P11_0  - ALT_OUT1    - ETH0_MII_TXD3
  {11, 1,  {PORT_OUT,   PORT_ALT_1,  PortSetPIPC_UNSET, PortBufferType_UNSET, PORT_STRENGTH_2_1} },           // P11_1  - ALT_OUT1    - ETH0_MII_TXD2
  {11, 2,  {PORT_OUT,   PORT_ALT_1,  PortSetPIPC_UNSET, PortBufferType_UNSET, PORT_STRENGTH_2_1} },           // P11_2  - ALT_OUT1    - ETH0_MII_TXD1
  {11, 3,  {PORT_OUT,   PORT_ALT_1,  PortSetPIPC_UNSET, PortBufferType_UNSET, PORT_STRENGTH_2_1} },           // P11_3  - ALT_OUT1    - ETH0_MII_TXD0
  {11, 4,  {PORT_OUT,   PORT_ALT_1,  PortSetPIPC_UNSET, PortBufferType_UNSET, PORT_STRENGTH_2_1} },           // P11_4  - ALT_OUT1    - ETH0_MII_TX_ER
  {11, 5,  {PORT_IN,    PORT_ALT_4,  PortSetPIPC_UNSET, PORT_TTL, PortDriveStrength_UNSET} },                 // P11_5  - ALT_IN4     - ETH0_MII_TX_CLK
  {11, 6,  {PORT_OUT,   PORT_ALT_1,  PortSetPIPC_UNSET, PortBufferType_UNSET, PORT_STRENGTH_2_1} },           // P11_6  - ALT_OUT1    - ETH0_MII_TX_EN
  {11, 7,  {PORT_IN,    PORT_ALT_5,  PortSetPIPC_UNSET, PORT_TTL, PortDriveStrength_UNSET} },                 // P11_7  - ALT_IN5     - ETH0_MII_RXD3
  {11, 8,  {PORT_IN,    PORT_ALT_5,  PortSetPIPC_UNSET, PORT_TTL, PortDriveStrength_UNSET} },                 // P11_8  - ALT_IN5     - ETH0_MII_RXD2
  {11, 9,  {PORT_IN,    PORT_ALT_5,  PortSetPIPC_UNSET, PORT_TTL, PortDriveStrength_UNSET} },                 // P11_9  - ALT_IN5     - ETH0_MII_RXD1
  {11, 10, {PORT_IN,    PORT_ALT_10, PortSetPIPC_UNSET, PORT_TTL, PortDriveStrength_UNSET} },                 // P11_10 - ALT_IN10    - ETH0_MII_RXD0
  {11, 11, {PORT_IN,    PORT_ALT_5,  PortSetPIPC_UNSET, PORT_SHMT1, PortDriveStrength_UNSET} },               // P11_11 - ALT_IN5     - ETH0_MII_CRSDV
  {11, 12, {PORT_IN,    PORT_ALT_6,  PortSetPIPC_UNSET, PORT_SHMT1, PortDriveStrength_UNSET} },               // P11_12 - ALT_IN6     - ETH0_MII_RX_CLK
  {11, 13, {PORT_IN,    PORT_ALT_6,  PortSetPIPC_UNSET, PORT_TTL, PortDriveStrength_UNSET} },                 // P11_13 - ALT_IN6     - ETH0_MII_RX_ER
  {11, 14, {PORT_IN,    PORT_ALT_6,  PortSetPIPC_UNSET, PORT_TTL, PortDriveStrength_UNSET} },                 // P11_14 - ALT_IN6     - ETH0_MII_RX_DV
  {11, 15, {PORT_IN,    PORT_ALT_5,  PortSetPIPC_UNSET, PORT_SHMT1, PortDriveStrength_UNSET} },               // P11_15 - ALT_IN5     - ETH0_MII_COL
  {14, 2,  {PORT_IN,    PORT_ALT_5,  PortSetPIPC_UNSET, PORT_TTL, PortDriveStrength_UNSET} },                 // P14_2  - ALT_IN5     - ETH0_LINKSTA
  {20, 0,  {PORT_OUT,   PORT_RESET,  PortSetPIPC_UNSET, PortBufferType_UNSET, PortDriveStrength_UNSET} },     // P20_0  - ALT_RESET   - ETH0_RESET

  /* ETNE1 SGMII */
  {14, 11, {PORT_OUT,   PORT_ALT_11,  PortSetPIPC_UNSET, PortBufferType_UNSET, PortDriveStrength_UNSET} },    // P14_11 - ALT_OUT11   - ETH0_MDC
  {14, 12, {PORT_INOUT, PORT_ALT_11,  SET_PIPC, PORT_TTL, PortDriveStrength_UNSET} },                         // P14_12 - ALT_INOUT11 - ETH0_MDIO
  {34, 1,  {PORT_OUT,    PORT_RESET,  PortSetPIPC_UNSET, PortBufferType_UNSET, PortDriveStrength_UNSET} },    // P34_1  - ALT_RESET   - ETH1_RESET
#endif

#if (ETH_MACRO_ETNF == STD_ON)
  /* ETNF0 T1S */
  {11, 5,  {PORT_OUT,   PORT_ALT_14,  PortSetPIPC_UNSET, PortBufferType_UNSET, PORT_STRENGTH_2_1} },          // P11_5  - ALT_OUT14   - ETS0_TX
  {11, 14, {PORT_INOUT,   PORT_ALT_14,  SET_PIPC, PORT_TTL, PORT_STRENGTH_2_1} },                             // P11_14 - ALT_INOUT14 - ETS0_RX_MDC
  {11, 13, {PORT_INOUT,   PORT_ALT_14,  SET_PIPC, PORT_TTL, PORT_STRENGTH_2_1} },                             // P11_13 - ALT_INOUT14 - ETS0_RX_MDIO
#endif
  {PORT_INVALID}
};

#define SET_BIT_REGISTER(RegAddress, BitNumber)           (*(volatile uint32*)(RegAddress)) |=  (1 << BitNumber)
#define CLEAR_BIT_REGISTER(RegAddress, BitNumber)         (*(volatile uint32*)(RegAddress)) &= ~(1 << BitNumber)
#define WRITE_REGISTER(RegAddress, RegValue, WriteMask)   (*(volatile uint32*)(RegAddress)) = ((*(volatile uint32*)(RegAddress)) & ~(WriteMask)) | (RegValue & WriteMask)
#define PORT_BASE_ADDRESS        (0xFFD90000UL)        
#define PORT_PSFC(n)             (PORT_BASE_ADDRESS + 0x6000 + (0x40 * (uint32)(n)))

static void sub_port_init(const EthTest_PortSetting* Port_Setting)
{
  volatile uint32 LulCount;
  volatile uint8 PortNumber;
  volatile uint8 PinNumber;
  volatile uint32 LulRegAddress;
  volatile uint32 PCRReg_PIS_Val = 0;
  volatile uint32 PCRReg_PISA_Val = 0;
  LulCount = 0UL;
  EthTest_PortMode PortMode;
  EthTest_PortDriveStrength PortStrength;
  EthTest_PortSetPIPC PortSetPIPC;
  EthTest_PortBufferType PortBufferType;
  EthTest_PortAltMode PortAltMode;
  while(Port_Setting[LulCount].PortNumber != PORT_INVALID)
  {
    PortMode = Port_Setting[LulCount].PortValue.PortMode;
    PortStrength = Port_Setting[LulCount].PortValue.PortStrength;
    PortSetPIPC = Port_Setting[LulCount].PortValue.PortSetPIPC;
    PortBufferType = Port_Setting[LulCount].PortValue.PortBufferType;
    PortAltMode = Port_Setting[LulCount].PortValue.PortAltMode;
    PortNumber = Port_Setting[LulCount].PortNumber;
    PinNumber = Port_Setting[LulCount].PinNumber;
    LulRegAddress = PORT_PSFC(PortNumber);
    CLEAR_BIT_REGISTER(LulRegAddress, PinNumber);

    LulRegAddress = REG_PCR(PortNumber, PinNumber);
    if(PORT_RESET == PortAltMode)
    {
      WRITE_REGISTER(LulRegAddress, (PortMode & 1) << PCR_PM_BIT_POSITION, 0xFFFFFFFF);
      LulCount++;
      continue;
    }
    
    /* PFCEAE_PFCAE_PFCE_PFC */
    WRITE_REGISTER(LulRegAddress, PortAltMode , 0xFFFFFFFF);
    
    /* PM */
    if(PortMode == PORT_IN)
    {
      SET_BIT_REGISTER(LulRegAddress, PCR_PM_BIT_POSITION);
    }
    else
    {
      CLEAR_BIT_REGISTER(LulRegAddress, PCR_PM_BIT_POSITION);
    }

    if(PortSetPIPC == SET_PIPC)
    {
      /* PIPC */
      SET_BIT_REGISTER(LulRegAddress, PCR_PIPC_BIT_POSITION);
    }
    else
    {
      /* PIPC */
      CLEAR_BIT_REGISTER(LulRegAddress, PCR_PIPC_BIT_POSITION);
    }

    /* PMC */
    SET_BIT_REGISTER(LulRegAddress, PCR_PMC_BIT_POSITION);
    
    if(PortBufferType != PortBufferType_UNSET)
    {
      /* PIS */
      PCRReg_PIS_Val  = (PortBufferType & 0x01U); 
      WRITE_REGISTER(LulRegAddress, (PCRReg_PIS_Val) << PCR_PIS_BIT_POSITION, 1 << PCR_PIS_BIT_POSITION);
      
      /* PISA */
      PCRReg_PISA_Val = (PortBufferType >> 0x01U); 
      WRITE_REGISTER(LulRegAddress, (PCRReg_PISA_Val) << PCR_PISA_BIT_POSITION, 1 << PCR_PISA_BIT_POSITION);
    }
    
    if(PortStrength != PortDriveStrength_UNSET)
    {
      /* PUCC, PDSC */
      WRITE_REGISTER(LulRegAddress, PortStrength << PCR_PDSC_BIT_POSITION, (1 << PCR_PUCC_BIT_POSITION | 1 << PCR_PDSC_BIT_POSITION));
    }
    //printf("0x%08x P%d_%d: 0x%08x\r\n", LulRegAddress, PortNumber, PinNumber,(*(volatile uint32*)(LulRegAddress)));
    LulCount++;
  }
}
/* Port for Ethernet follows the table below: */
/*----------------------------------------------------------------------------+
| Devices | P3_0 -> P3_1 | P42_0 -> P42_15 | P46_6 -> P46_15 | P47_0 -> P47_7 |
|---------+--------------+-----------------+-----------------+----------------|
| D1M1    |   SUPPORT    |    SUPPORT      |   NOT_SUPPORT   |   NOT_SUPPORT  |
| D1M1H   |   SUPPORT    |    SUPPORT      |   NOT_SUPPORT   |   NOT_SUPPORT  |
| D1M2    |   SUPPORT    |    NOT_SUPPORT  |   SUPPORT       |   SUPPORT      |
| D1M2H   |   SUPPORT    |    SUPPORT      |   SUPPORT       |   SUPPORT      |
| D1M1A   |   SUPPORT    |    SUPPORT      |   NOT_SUPPORT   |   NOT_SUPPORT  |
| D1M1-V2 |   SUPPORT    |    SUPPORT      |   NOT_SUPPORT   |   NOT_SUPPORT  |
+-----------------------------------------------------------------------------*/

/* 1. For the devices with the adapter board schematic:
    + D1M2H used both ETHERNET0 connector and ETHERNET1 connector.
      But the priority is ETHERNET0.
    + D1M1A and D1M1-V2 used only ETHERNET0 connector.
   2. For the devices without the adapter board schematic:
      Assume that others apdapter devices are followed below information:
    + D1M1 and D1M1H used only ETHERNET0 connector.
    + D1M2 used only ETHERNET1 connector.
    IMPORTANT NOTE: This implement will update when receiving their adapter
    board schematic.*/

void Port_Init(void)
{
  volatile uint32 LulCount;
  volatile uint16 *addr = 0;
  volatile uint16 val  = 0;

  LulCount = 0UL;

  /* Register Protection Disable */
  REG_PKCPROT = KCPROT_SET;

  /* Set Port Write Enable Register(P11, P12, P14, P20) */
  REG_PWE = 0x0FFFFFFFUL;

  sub_port_init(U2BxE_Port_Setting);

  /*======================================================*/
  /* RESET of Ether PHY asserted and de-asserted to reset */
  /*======================================================*/
  /* RESET de-asserted (Normal mode) via ETH0RESET(P20_0=LO) */
  addr = (volatile uint16 *)REG_P(20);
  val  = *addr;
  val &= ~0x0001U;
  *addr = val;

  /* Wait for TRESET(Minimum reset pulse width during normal operation: 10ms) */
  ETH_WAIT_NS(10 * 1000 * 1000);

  /* ETH0RESET(P21_10=HIGH) */
  addr = (volatile uint16 *)REG_P(20);
  val  = *addr;
  val |= 0x0001U;
  *addr = val;

  ETH_WAIT_NS( 100 * 1000); /* 100us */

    /* RESET de-asserted (Normal mode) via ETH1RESET(P34_1=LO) */
  addr = (volatile uint16 *)REG_P(34);
  val  = *addr;
  val &= ~0x0002U;
  *addr = val;

  /* Wait for TRESET(Minimum reset pulse width during normal operation: 10ms) */
  ETH_WAIT_NS(10 * 1000 * 1000);

  /* ETH0RESET(P34_1=HIGH) */
  addr = (volatile uint16 *)REG_P(34);
  val  = *addr;
  val |= 0x0002U;
  *addr = val;

   ETH_WAIT_NS( 100 * 1000); /* 100us */

  /* Register Protection Enable */
  REG_PWE = 0x00000000UL;
  REG_PKCPROT = KCPROT_CLR;
}

void Phy_Init(void)
{
  /* Initialize PHY(8700) for Ethernet */
  #if (ETH_CTRL_ENABLE_MII == STD_ON)
  /* Software reset. */
  Eth_WriteMii(ETH_CTRLIDX_CONFIGSET_0, ETH_PHY_ADDR, ETH_REG0_BASIC_CONTROL_REG, ETH_REG0_SW_RESET);

  ETH_WAIT_NS(256 * 1000); /* 256us */

  /* Setting PHY to auto-negotiate 100Mbps*/
  Eth_WriteMii(ETH_CTRLIDX_CONFIGSET_0, ETH_PHY_ADDR, ETH_REG0_BASIC_CONTROL_REG,
    ETH_REG0_NEAR_LOOPBACK_CFG         |
    ETH_REG0_SPEED_CFG                 |
    ETH_REG0_AUTONEG_PROC_CFG          |
    ETH_REG0_POWERDOWN_MODE_CFG        |
    ETH_REG0_ELEC_ISOLATE_CFG          |
    ETH_REG0_DUPLEX_CFG                |
    ETH_REG0_COLTEST_CFG);
  #endif
}

void R_ETNF_ConfigPLCA (uint8 LucCtrlIdx)
{
  uint16 vs;

  /* Software reset. */
  Eth_WriteMii(LucCtrlIdx, ETH_PHY_ADDR, ETH_REG0_BASIC_CONTROL_REG, ETH_REG0_SW_RESET);

  Eth_WriteMii (LucCtrlIdx, ETH_PHY_ADDR, 0 , 0x8000);     // CONTROL  , set LCTL
  do
  {
    vs = Eth_ReadMii (LucCtrlIdx, ETH_PHY_ADDR, 0, &vs); // T1STXCST, check TXCST status NORMAL
    
  } while( vs  != 0x00 );
  
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // check content of some T1S-PHY register                   (content)
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  Eth_ReadMii (LucCtrlIdx, ETH_PHY_ADDR, 0, &vs); // CONTROL     -> 0x0000
  Eth_ReadMii (LucCtrlIdx, ETH_PHY_ADDR, 1, &vs); // STATUS      -> 0x0809
  Eth_ReadMii (LucCtrlIdx, ETH_PHY_ADDR, 2, &vs); // PHYID0      -> 0xB824
  Eth_ReadMii (LucCtrlIdx, ETH_PHY_ADDR, 3, &vs); // PHYID1      -> 0x2B01
  vs = regRead (LucCtrlIdx, 0x3F8000); // CTIPVER     -> 0x20C2

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // setup T1S-PHY
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  regWrite (LucCtrlIdx, 0x3F8001, 0x0003);      // T1STWEAKS, set PKTLOOP
  vs = regRead (LucCtrlIdx, 0x3F8001);         // T1STWEAKS, -> 0x8003/0x0003
  
  Eth_WriteMii (LucCtrlIdx, ETH_PHY_ADDR, 0 , 0x1000);     // CONTROL  , set LCTL
  Eth_ReadMii  (LucCtrlIdx, ETH_PHY_ADDR, 0 , &vs);        // CONTROL  , -> 0x1000
 
  regWrite (LucCtrlIdx, 0x3FCA02, 0x0800);      // PLCACTRL1, set NCNT=8, ID=0
  vs = regRead  (LucCtrlIdx, 0x3FCA02);         // PLCACTRL1, -> 0x0800

  vs = regRead (LucCtrlIdx, 0x3FCA03);          // PLCAST, check PST -> 0x0000
  
}

void Eth_InitT1s(uint8 LucCtrlIdx)
{
  /* Configure PLCA */
  R_ETNF_ConfigPLCA(LucCtrlIdx);
  uint16 vs;
  do
  {
    /* Checking status of the attached transceiver */ 
    vs = regRead(LucCtrlIdx, 0x3F8006); // T1STXCST, check TXCST status NORMAL
    
  } while( ( vs & 0x07 ) != 0x00 );
  
  regWrite(LucCtrlIdx, 0x3F8005, 0x0002 ); // T1STXCCTL: PHY CONFIG Request

  /* Setup PHY on Address 1 */
  
  Eth_ReadMii (LucCtrlIdx, 1, 2 , &vs); // PHYID0 
  Eth_ReadMii (LucCtrlIdx, 1, 3 , &vs); // PHYID1 

  Eth_ReadMii (LucCtrlIdx, 1, 0x18, &vs); // XCVR_ANALOG_SET_2 
  vs |= 0x6000;                           // Set 14:13 -> 11B
  Eth_WriteMii(LucCtrlIdx, 1, 0x18, vs ); 
  
  Eth_ReadMii (LucCtrlIdx, 1, 0x1F, &vs); // XCVR_ANALOG_SET_9 
  vs |= 0x0018;                          // Set 4:3 -> 11B
  Eth_WriteMii(LucCtrlIdx, 1, 0x1F, vs ); 

  Eth_ReadMii (LucCtrlIdx, 1, 0x18, &vs); // XCVR_ANALOG_SET_2 
  Eth_ReadMii (LucCtrlIdx, 1, 0x1F, &vs); // XCVR_ANALOG_SET_9 

  /* Set Normal Mode */

  regWrite(LucCtrlIdx, 0x3F8005, 0x0000); // T1STXCCTL: PHY RESET/NORMAL Request

  do
  {
   vs = regRead(LucCtrlIdx, 0x3F8006); // T1STXCST, check TXCST status NORMAL
    
  } while( ( vs & 0x07 ) != 0x00 );

  regWrite (LucCtrlIdx, 0x3FCA01, 0x8000 ); // PLCACTRL0, set PLCA EN
  do
  {
   vs = regRead (LucCtrlIdx, 0x3FCA01); // PLCACTRL0, -> 0x8000
  } while( ( vs & 0x8000 ) != 0x8000 );
  Eth_ReadMii (LucCtrlIdx, ETH_PHY_ADDR, 0x01, &vs);
}

/******************************************************************************/
/* Write PHY's register follow clause 45.                                     */
/******************************************************************************/
void regWrite(uint8 LucCtrlIdx, uint32 regAddr45, uint16 reg_val)
{
  uint16 mmd      = ((uint16)(regAddr45 >> 16) & 0x001F);
  uint16 reg_addr = ((uint16)(regAddr45 >>  0) & 0xFFFF);
  
  Eth_WriteMii (LucCtrlIdx, ETH_PHY_ADDR, 13, 0x0000 | mmd); // MMD
  Eth_WriteMii (LucCtrlIdx, ETH_PHY_ADDR, 14, reg_addr    );
  Eth_WriteMii (LucCtrlIdx, ETH_PHY_ADDR, 13, 0x4000 | mmd); // MMD + SEL_DATA
  Eth_WriteMii (LucCtrlIdx, ETH_PHY_ADDR, 14, reg_val     );
}

/******************************************************************************/
/* Read PHY's register follow clause 45.                                      */
/******************************************************************************/
uint16 regRead(uint8 LucCtrlIdx, uint32 regAddr45)
{
  uint16 mmd      = ((uint16)(regAddr45 >> 16) & 0x001F);
  uint16 reg_addr = ((uint16)(regAddr45 >>  0) & 0xFFFF);
  uint16 reg_val;

  Eth_WriteMii (LucCtrlIdx, ETH_PHY_ADDR, 13, 0x0000 | mmd); // MMD
  Eth_WriteMii (LucCtrlIdx, ETH_PHY_ADDR, 14, reg_addr);
  Eth_WriteMii (LucCtrlIdx, ETH_PHY_ADDR, 13, 0x4000 | mmd); // MMD + SEL_DATA
  Eth_ReadMii  (LucCtrlIdx, ETH_PHY_ADDR, 14, &reg_val);
  return reg_val;
}

/******************************************************************************/
/* Initialize SGMII registers for ETND                                        */
/******************************************************************************/
#if (ETH_CTRL_ENABLE_MII == STD_ON)
/******************************************************************************/
/* Write PHY's register follow clause 22 in register 13, 14.                  */
/******************************************************************************/
void regWrite_SGMII(uint8 ctrlIdx, uint16 phyAddr, uint16 devAddr, uint16 regAddr, uint16 data)
{
  Eth_WriteMii(ctrlIdx, phyAddr, 13, devAddr);
  Eth_WriteMii(ctrlIdx, phyAddr, 14, regAddr);
  Eth_WriteMii(ctrlIdx, phyAddr, 13, devAddr | 0x4000);
  Eth_WriteMii(ctrlIdx, phyAddr, 14, data);
}

/******************************************************************************/
/* Read PHY's register follow clause 22 in register 13, 14.                   */
/******************************************************************************/
uint16 regRead_SGMII(uint8 ctrlIdx, uint16 phyAddr, uint16 devAddr, uint16 regAddr)
{
  uint16 LusPhySts;
  Eth_WriteMii(ctrlIdx, phyAddr, 13, devAddr);
  Eth_WriteMii(ctrlIdx, phyAddr, 14, regAddr);
  Eth_WriteMii(ctrlIdx, phyAddr, 13, devAddr | 0x4000);
  Eth_ReadMii(ctrlIdx, phyAddr, 14, &LusPhySts);
  return LusPhySts;
}

/******************************************************************************/
/* Get speed of Marvell 88Q2112.                                              */
/******************************************************************************/
uint16 getSpeed(uint8 ctrlIdx, uint16 phyAddr)
{
  uint16 regData;
  uint16 speed = 0;

  regData = regRead_SGMII(ctrlIdx, phyAddr, 7, 0x0200);
  // check if AN enabled
  if ((regData & 0x1000) == 0x1000)
  {
    regData = regRead_SGMII(ctrlIdx, phyAddr, 7, 0x801a);
    if ((regData & 0x4000) == 0x4000)
    {
      speed = 1;
    }
  }
  else
  {
    regData = regRead_SGMII(ctrlIdx, phyAddr, 1, 0x0834);
    if ((regData & 0x0001) == 0x0001)
    {
      speed = 1;
    }
  }
  return speed;
}

/******************************************************************************/
/* Get revision number of Marvell 88Q2112.                                    */
/* E.g. Q2112 A0's revision number is 0x1.                                    */
/*            A1's revision number is 0x2.                                    */
/*            A2's revision number is 0x3.                                    */
/******************************************************************************/
uint16 getRevNum(uint8 ctrlIdx, uint16 phyAddr)
{
    uint16 revData;
    // Read device 1, register 0x0003
    revData = regRead_SGMII(ctrlIdx, phyAddr, 1, 0x0003);
    // Get Revision Number
    revData = (revData & 0x000F);

    return revData;
}

/******************************************************************************/
/* Obtain 88Q211x model number from a register                                */
/* Useful to verify SMI connection                                            */
/* Return constant value MRVL_88Q2112_PRODUCT_ID read from a register         */
/******************************************************************************/
uint16 getModelNum(uint8 ctrlIdx, uint16 phyAddr)
{
  uint16 revData;
  // Read device 1, register 0x0003
  revData = regRead_SGMII(ctrlIdx, phyAddr, 1, 0x0003);
  // Get Revision Number
  revData = ( (revData & 0x03F0) >> 4 );

  return revData;
}

/******************************************************************************/
/* Check SGMII link                                                           */
/******************************************************************************/
uint8 checkSGMIILink(uint8 ctrlIdx, uint16 phyAddr)
{
  uint16 regData;
  uint16 isLinkup = 0;
  regData = regRead_SGMII(ctrlIdx, phyAddr, 4, 0x8011);
  regData = regRead_SGMII(ctrlIdx, phyAddr, 4, 0x8011);
  if ((regData & 0x0420) == 0x0420)
  {
    /* SGMII Link/Sync OK */
    isLinkup = 1;
  }

  return isLinkup;
}

/******************************************************************************/
/* check PCS link                                                             */
/******************************************************************************/
uint8 checkPCSLink(uint8 ctrlIdx, uint16 phyAddr)
{
  uint16 regData1, regData2 = 0;
  uint16 isLinkup = 0;
  uint16 speed = getSpeed(ctrlIdx, phyAddr);

  if (speed == 1)
  {
    // ge
    // Need to call twice to be able to read register 3.0901
    regData1 = regRead_SGMII(ctrlIdx, phyAddr, 3, 0x0901);
    regData1 = regRead_SGMII(ctrlIdx, phyAddr, 3, 0x0901);
    regData2 = regRead_SGMII(ctrlIdx, phyAddr, 7, 0x8001);
    ETH_WAIT_NS(1000 * 1000);
    if (((regData1 & 0x0004) == 0x0004) && ((regData2 & 0x3000) == 0x3000))
    {
      isLinkup = 1;
    }
  }
  else
  {
    // fe
    regData1 = regRead_SGMII(ctrlIdx, phyAddr, 3, 0x8108);
    regData2 = regRead_SGMII(ctrlIdx, phyAddr, 3, 0x8109);
    ETH_WAIT_NS(1000 * 1000);
    if (((regData1 & 0x3000) == 0x3000) && ((regData2 & 0x0004) == 0x0004))
    {
      isLinkup = 1;
    }
  }

  return isLinkup;
}

/******************************************************************************/
/* Initialize SGMII registers for ETNE with Auto-Negotiation enabled         */
/******************************************************************************/
void Eth_InitSgmii(uint8 LucCtrlIdx)
{
  uint16 regData;
  uint16 masterselect = 1;
  uint16 anAbility = 0;
  uint16 revData = 0;
  uint8 isPCSLink = 0;
  uint8 isSGMIILink = 0;
#if (ETH_MACRO_ETNE == STD_ON)
  GulPortId = ((Eth_ETNEConfigType*)Eth_GpCtrlConfigPtr[LucCtrlIdx].pHwUnitConfig)->ulEthPortId;
  if (ETH_RSW2_PORT_TYPE_ETHA == Eth_GaaRsw2PortType[GulPortId])
#endif
  {
  if (0x0 != masterselect)
  {
    /* Auto-Negotiation: Prefer Master */
    anAbility = MRVL_88Q2112_AN_PREFER_MASTER;
  }

  /* Ensure functional communication to PHY SMI */
  do
  {
    /* Obtain 88Q211x model number */
    regData = getModelNum(LucCtrlIdx, 0);
  } while (regData != MRVL_88Q2112_PRODUCT_ID);

  /* Initilize GBit Ethernet 1000BASE-T1 acc. MARVELL API script */
  // Global PMA Transmit Disable to 1(Disable transmitters).
  regWrite_SGMII(LucCtrlIdx, 0, 1, 0x0900, 0x4000);
  regWrite_SGMII(LucCtrlIdx, 0, 7, 0x0200, 0x0000);

  // Auto-Negotiation Enable
  regWrite_SGMII(LucCtrlIdx, 0, 7, 0x0200, MRVL_88Q2112_AN_ENABLE | MRVL_88Q2112_AN_RESTART);

  /* Obtain 88Q211x revision number */
  revData = getRevNum(LucCtrlIdx, 0);

  switch (revData)
  {
  case MRVL_88Q2112_A2:
  case MRVL_88Q2112_A1:
  case MRVL_88Q2112_A0:
    /*======================================================*/
    /* Initialize internal PHY registers for 1000 BASE-T1   */
    /*======================================================*/
    anAbility |= MRVL_88Q2112_AN_GE_ABILITY;
    // BASE-T1 Control Register
    // 0x4000 = 100 0000 0000 0000b
    // Global PMA Transmit Disable to 1(Disable transmitters)
    regWrite_SGMII(LucCtrlIdx, 0, 1, 0x0900, 0x4000);

    // Read BASE-T1 PMA/PMD Control Register
    regData = regRead_SGMII(LucCtrlIdx, 0, 1, 0x0834);

    // Set Type Selection to 1000BASE-T1
    regData = (regData & 0xFFF0) | 0x0001;
    regWrite_SGMII(LucCtrlIdx, 0, 1, 0x0834, regData);

    // Unknown this is secret register by the Marvell.
    regWrite_SGMII(LucCtrlIdx, 0, 3, 0xFFE4, 0x07B5);
    regWrite_SGMII(LucCtrlIdx, 0, 3, 0xFFE4, 0x06B6);

    // 5ms
    ETH_WAIT_NS(5000 * 1000);

    // Unknown this is secret register by the Marvell.
    regWrite_SGMII(LucCtrlIdx, 0, 3, 0xFFDE, 0x402F);
    regWrite_SGMII(LucCtrlIdx, 0, 3, 0xFE2A, 0x3C3D);

    regWrite_SGMII(LucCtrlIdx, 0, 7, 0x8032, 0x0064);
    regWrite_SGMII(LucCtrlIdx, 0, 7, 0x8031, 0x0A01);
    regWrite_SGMII(LucCtrlIdx, 0, 7, 0x8031, 0x0C01);
    regWrite_SGMII(LucCtrlIdx, 0, 3, 0xFE0F, 0x0000);
    regWrite_SGMII(LucCtrlIdx, 0, 3, 0x800C, 0x0000);

    // LPSD Register 2
    // 0x0800 = 1000 0000 0000b
    // Disable LPSD Remote Wake Up to 1
    // The device will not wake up if energy is received at the MDIP/N pins.
    regWrite_SGMII(LucCtrlIdx, 0, 3, 0x801D, 0x0800);

    // Unknown this is secret register by the Marvell.
    regWrite_SGMII(LucCtrlIdx, 0, 3, 0xFC00, 0x01C0);
    regWrite_SGMII(LucCtrlIdx, 0, 3, 0xFC17, 0x0425);
    regWrite_SGMII(LucCtrlIdx, 0, 3, 0xFC94, 0x5470);
    regWrite_SGMII(LucCtrlIdx, 0, 3, 0xFC95, 0x0055);
    regWrite_SGMII(LucCtrlIdx, 0, 3, 0xFC19, 0x08D8);
    regWrite_SGMII(LucCtrlIdx, 0, 3, 0xFC1a, 0x0110);
    regWrite_SGMII(LucCtrlIdx, 0, 3, 0xFC1b, 0x0A10);
    regWrite_SGMII(LucCtrlIdx, 0, 3, 0xFC3A, 0x2725);
    regWrite_SGMII(LucCtrlIdx, 0, 3, 0xFC61, 0x2627);
    regWrite_SGMII(LucCtrlIdx, 0, 3, 0xFC3B, 0x1612);
    regWrite_SGMII(LucCtrlIdx, 0, 3, 0xFC62, 0x1C12);
    regWrite_SGMII(LucCtrlIdx, 0, 3, 0xFC9D, 0x6367);
    regWrite_SGMII(LucCtrlIdx, 0, 3, 0xFC9E, 0x8060);
    regWrite_SGMII(LucCtrlIdx, 0, 3, 0xFC00, 0x01C8);

    // Reset and Control Register
    // TX Disable Feature Enable to 0
    // Disable TX Disable Feature. TX_ENABLE has no effect on Tx packets.
    regWrite_SGMII(LucCtrlIdx, 0, 3, 0x8000, 0x0000);

    // Function Control Register
    // 0x0011 = 1 0001b
    // 1    = On - Link, Blink - Activity, Off - No Link
    // 0001 = On - Link, Blink - Activity, Off - No Link
    regWrite_SGMII(LucCtrlIdx, 0, 3, 0x8016, 0x0011);

    // Unknown this is secret register by the Marvell.
    regWrite_SGMII(LucCtrlIdx, 0, 3, 0xFE02, 0x00C0);
    regWrite_SGMII(LucCtrlIdx, 0, 3, 0xFFDB, 0x0010);
    regWrite_SGMII(LucCtrlIdx, 0, 3, 0xFFF3, 0x0020);
    regWrite_SGMII(LucCtrlIdx, 0, 3, 0xFE40, 0x00A6);
    regWrite_SGMII(LucCtrlIdx, 0, 3, 0xFE60, 0x0000);
    regWrite_SGMII(LucCtrlIdx, 0, 3, 0xFE04, 0x0008);
    regWrite_SGMII(LucCtrlIdx, 0, 3, 0xFE2A, 0x3C3D);
    regWrite_SGMII(LucCtrlIdx, 0, 3, 0xFE4B, 0x9334);
    regWrite_SGMII(LucCtrlIdx, 0, 3, 0xFC10, 0xF600);
    regWrite_SGMII(LucCtrlIdx, 0, 3, 0xFC11, 0x073D);
    regWrite_SGMII(LucCtrlIdx, 0, 3, 0xFC12, 0x000D);
    regWrite_SGMII(LucCtrlIdx, 0, 3, 0xFC13, 0x0010);

    /*======================================================*/
    /* Initialize internal PHY registers for 100 BASE-T1    */
    /*======================================================*/
    anAbility |= MRVL_88Q2112_AN_FE_ABILITY;
    regWrite_SGMII(LucCtrlIdx, 0, 3, 0xFA07, 0x0202);

    regData = regRead_SGMII(LucCtrlIdx, 0, 1, 0x0834);
    regData = regData & 0xFFF0;
    regWrite_SGMII(LucCtrlIdx, 0, 1, 0x0834, regData);
    // 5ms
    ETH_WAIT_NS(5000 * 1000);

    regWrite_SGMII(LucCtrlIdx, 0, 3, 0x8000, 0x0000);
    regWrite_SGMII(LucCtrlIdx, 0, 3, 0x8100, 0x0200);
    regWrite_SGMII(LucCtrlIdx, 0, 3, 0xFA1E, 0x0002);
    regWrite_SGMII(LucCtrlIdx, 0, 3, 0xFE5C, 0x2402);
    regWrite_SGMII(LucCtrlIdx, 0, 3, 0xFA12, 0x001F);
    regWrite_SGMII(LucCtrlIdx, 0, 3, 0xFA0C, 0x9E05);
    regWrite_SGMII(LucCtrlIdx, 0, 3, 0xFBDD, 0x6862);
    regWrite_SGMII(LucCtrlIdx, 0, 3, 0xFBDE, 0x736E);
    regWrite_SGMII(LucCtrlIdx, 0, 3, 0xFBDF, 0x7F79);
    regWrite_SGMII(LucCtrlIdx, 0, 3, 0xFBE0, 0x8A85);
    regWrite_SGMII(LucCtrlIdx, 0, 3, 0xFBE1, 0x9790);
    regWrite_SGMII(LucCtrlIdx, 0, 3, 0xFBE3, 0xA39D);
    regWrite_SGMII(LucCtrlIdx, 0, 3, 0xFBE4, 0xB0AA);
    regWrite_SGMII(LucCtrlIdx, 0, 3, 0xFBE5, 0x00B8);
    regWrite_SGMII(LucCtrlIdx, 0, 3, 0xFBFD, 0x0D0A);
    regWrite_SGMII(LucCtrlIdx, 0, 3, 0xFBFE, 0x0906);
    regWrite_SGMII(LucCtrlIdx, 0, 3, 0x801D, 0x8000);
    regWrite_SGMII(LucCtrlIdx, 0, 3, 0x8016, 0x0011);

    /*======================================================*/
    /* Initialize Auto-Negotiation related logic            */
    /*======================================================*/
    regData = 0;
    regData = regRead_SGMII(LucCtrlIdx, 0, 7, 0x8032);
    regWrite_SGMII(LucCtrlIdx, 0, 7, 0x8032, regData | 0x0001);
    regWrite_SGMII(LucCtrlIdx, 0, 7, 0x8031, 0x0013);
    regWrite_SGMII(LucCtrlIdx, 0, 7, 0x8031, 0x0a13);

    regData = regRead_SGMII(LucCtrlIdx, 0, 7, 0x8032);
    regData = (0xFC00 & regData) | 0x0012;
    regWrite_SGMII(LucCtrlIdx, 0, 7, 0x8032, regData);
    regWrite_SGMII(LucCtrlIdx, 0, 7, 0x8031, 0x0016);
    regWrite_SGMII(LucCtrlIdx, 0, 7, 0x8031, 0x0a16);

    regData = regRead_SGMII(LucCtrlIdx, 0, 7, 0x8032);
    regData = (0xFC00 & regData) | 0x64;
    regWrite_SGMII(LucCtrlIdx, 0, 7, 0x8032, regData);
    regWrite_SGMII(LucCtrlIdx, 0, 7, 0x8031, 0x0017);
    regWrite_SGMII(LucCtrlIdx, 0, 7, 0x8031, 0x0a17);

    regWrite_SGMII(LucCtrlIdx, 0, 3, 0x800C, 0x0008);
    regWrite_SGMII(LucCtrlIdx, 0, 3, 0xFE04, 0x0016);
    break;

  default:                          // Z1

    // Does not support Z1.

    break;
  }

  /*======================================================*/
  /* Apply current operating mode to PHY                  */
  /*======================================================*/
  switch (revData)
  {
  case MRVL_88Q2112_A2:

    // Unknown this is secret register by the Marvell.
    // Set back to default compliant mode setting
    regWrite_SGMII(LucCtrlIdx, 0, 3, 0xFDB8, 0x0000);
    regWrite_SGMII(LucCtrlIdx, 0, 3, 0xFD3D, 0x0000);
    regWrite_SGMII(LucCtrlIdx, 0, 1, 0x0902, 0x0002);

    break;

  case MRVL_88Q2112_A1:

    // Unknown this is secret register by the Marvell.
    // Set A1 to legacy mode
    regWrite_SGMII(LucCtrlIdx, 0, 3, 0xFDB8, 0x0001);

    // 1000BASE-T1 Training Register
    // 0x06B0 | 0x0002 = 110 1011 0010b
    // Legacy mode & Advertise mode
    regWrite_SGMII(LucCtrlIdx, 0, 1, 0x0902, 0x06B0 | 0x0002);

    break;

  case MRVL_88Q2112_A0:

    // 1000BASE-T1 Training Register
    // 0x06B0 | 0x0002 = 110 1011 0010b
    // Legacy mode & Advertise mode
    regWrite_SGMII(LucCtrlIdx, 0, 1, 0x0902, 0x06B0 | 0x0002);

    break;

  default:

    // Does not support Z1.

    break;
  }
  /*======================================================*/
  /* Set Ability registers                                */
  /*======================================================*/
  regWrite_SGMII(LucCtrlIdx, 0, 7, 0x0203, anAbility);

  /*======================================================*/
  /* Software Reset procedure                             */
  /*======================================================*/
  /* Reset sequence for 1000 BASE-T1 */
  // When Auto-Negotiation only
  regWrite_SGMII(LucCtrlIdx, 0, 3, 0xFFF3, 0x0024);

  /* Enable low-power mode */
  // PMA/PMD Control Register 1
  // Low Power to 1(Low Power mode)
  regData = regRead_SGMII(LucCtrlIdx, 0, 1, 0x0000);
  regWrite_SGMII(LucCtrlIdx, 0, 1, 0x0000, regData | 0x0800);

  // Unknown this is secret register by the Marvell.
  regWrite_SGMII(LucCtrlIdx, 0, 3, 0xFFF3, 0x0020);
  regWrite_SGMII(LucCtrlIdx, 0, 3, 0xFFE4, 0x000C);

  // 1ms
  ETH_WAIT_NS(1000 * 1000);

  // Unknown this is secret register by the Marvell.
  regWrite_SGMII(LucCtrlIdx, 0, 3, 0xFFE4, 0x06B6);

  /* Disable low-power mode */
  // PMA/PMD Control Register 1
  // Low Power to 0(Normal operation)
  regWrite_SGMII(LucCtrlIdx, 0, 1, 0x0000, regData & 0xF7FF);

  // 1ms
  ETH_WAIT_NS(1000 * 1000);

  // Unknown this is secret register by the Marvell.
  regWrite_SGMII(LucCtrlIdx, 0, 3, 0xFC47, 0x0030);
  regWrite_SGMII(LucCtrlIdx, 0, 3, 0xFC47, 0x0031);
  regWrite_SGMII(LucCtrlIdx, 0, 3, 0xFC47, 0x0030);
  regWrite_SGMII(LucCtrlIdx, 0, 3, 0xFC47, 0x0000);
  regWrite_SGMII(LucCtrlIdx, 0, 3, 0xFC47, 0x0001);
  regWrite_SGMII(LucCtrlIdx, 0, 3, 0xFC47, 0x0000);

  // BASE-T1 Control Register
  // Reset to 1(PMA/PMD reset)
  regWrite_SGMII(LucCtrlIdx, 0, 3, 0x0900, 0x8000);

  // BASE-T1 Control Register
  // Reset to 0(Normal operation)
  regWrite_SGMII(LucCtrlIdx, 0, 1, 0x0900, 0x0000);

  // Unknown this is secret register by the Marvell.
  regWrite_SGMII(LucCtrlIdx, 0, 3, 0xFFE4, 0x000C);

  /* Reset sequence for 100 BASE-T1 */
  regWrite_SGMII(LucCtrlIdx, 0, 3, 0x0900, 0x8000);
  regWrite_SGMII(LucCtrlIdx, 0, 3, 0xFA07, 0x0200);

  do
  {
    /* Wait PCS link */
    isPCSLink = checkPCSLink(LucCtrlIdx, 0);
  } while (0 == isPCSLink);

  do
  {
    /* Reset SGMII */
    regWrite_SGMII(LucCtrlIdx, 0, 4, 0x801A, 0x0002);
    regWrite_SGMII(LucCtrlIdx, 0, 4, 0x8000, 0x9340);

    /* DELAYTIME, STAISR */
    ETH_WAIT_NS(50000 * 1000);

    isSGMIILink = checkSGMIILink(LucCtrlIdx, 0);
  } while (0 == isSGMIILink);
  }
}
#endif

/******************************************************************************
**                          End of File                                      **
*******************************************************************************/
