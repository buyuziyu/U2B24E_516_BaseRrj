/*******************************************************************************
|    Header File Inclusion
|******************************************************************************/
#include "user_ethif.h"

#include "Eth.h"

/*******************************************************************************
|    Macro Definition
|******************************************************************************/
#if defined ETH_CTRLIDX_CONFIGSET_1 
#define ETH_CTRL_NUM                       2 
#else 
#define ETH_CTRL_NUM                       1 
#endif 
 
#define ETH_TX_SAMPLE_TOTAL                5U 
 
/* Eth controller index */ 
#define ETH_CTRLIDX_0                      0 
#define ETH_CTRLIDX_1                      1 

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

/*******************************************************************************
|    Typedef Definition
|******************************************************************************/

/*******************************************************************************
|    variables Declaration  
|******************************************************************************/
volatile uint8 GaaRxEthFrame[ETH_CTRL_NUM][ETH_VLFRAME_SIZE]; 
volatile uint8 GaaRxSrcAddr[ETH_CTRL_NUM][SRC_MACADDR_LEN]; 
volatile uint8 GucTxConfirmed[ETH_CTRL_NUM]; 
volatile uint16 GusMsgLength[ETH_CTRL_NUM]; 
volatile uint16 GusRxFrameCnt[ETH_CTRL_NUM]; 
volatile uint16 GusRxLenByte[ETH_CTRL_NUM]; 
volatile Eth_FrameType GusRxFrameType[ETH_CTRL_NUM]; 
volatile boolean EthRcvBroadcastMsg; 
volatile uint8 EthPassedCount[70]; 
volatile uint8 EthCheckCount; 
volatile uint8 EthModeActiveCnt; 
volatile uint8 EthModeDownCnt; 

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

volatile uint8 GaaRxEthFrame_1[ETH_TOTAL_CTRL_CONFIG][ETH_VLFRAME_SIZE];
volatile uint8 GaaRxSrcAddr_1[ETH_TOTAL_CTRL_CONFIG][SRC_MACADDR_LEN];
volatile uint8 GucTxConfirmed_1[ETH_TOTAL_CTRL_CONFIG];
volatile uint16 GusMsgLength_1[ETH_TOTAL_CTRL_CONFIG];
volatile uint16 GusRxFrameCnt_1[ETH_TOTAL_CTRL_CONFIG];
volatile uint16 GusRxLenByte_1[ETH_TOTAL_CTRL_CONFIG];
volatile Eth_FrameType GusRxFrameType_1[ETH_TOTAL_CTRL_CONFIG];
volatile boolean EthRcvBroadcastMsg_1;
volatile uint8 EthPassedCount_1[70];
volatile uint8 EthCheckCount_1;
volatile uint8 EthModeActiveCnt_1;
volatile uint8 EthModeDownCnt_1;

#if (ETH_GLOBAL_TIME_SUPPORT == STD_ON) 
Eth_TimeStampQualType TxTimeQual; 
Eth_TimeStampType TxTimeStamp[2]; 
#endif 

/*******************************************************************************
|    code Declaration  
|******************************************************************************/

void EthIf_Init(void)
{   
    /* Invoke Eth_Init to initialize the Ethernet Driver */
    Eth_Init(Eth_Config);

}



static const uint32 GaaPcrRegAddr[] = {
  /* ETNB0 */
  REG_PCR(10, 0),           /* P10_0  (ETNB0RXER)    */
  REG_PCR(10, 1),           /* P10_1  (ETNB0TXCLK)   */
  REG_PCR(10, 2),           /* P10_2  (ETNB0RXCLK)   */
  REG_PCR(10, 3),           /* P10_3  (ETNB0RXD0)    */
  REG_PCR(10, 4),           /* P10_4  (ETNB0RXD1)    */
  REG_PCR(10, 5),           /* P10_5  (ETNB0RXD2)    */
  REG_PCR(10, 6),           /* P10_6  (ETNB0RXD3)    */
  REG_PCR(10, 7),           /* P10_7  (ETNB0RXDV)    */
  REG_PCR(10, 8),           /* P10_8  (ETNB0WOL)     */
  REG_PCR(20, 0),           /* P20_0  (ETNB0RESET)   */
  REG_PCR(20, 1),           /* P20_1  (ETNB0LINKSTA) */
  REG_PCR(20, 3),           /* P20_3  (ETNB0MD)      */
  REG_PCR(20, 6),           /* P20_6  (ETNB0MDC)     */
  REG_PCR(20, 8),           /* P20_8  (ETNB0TXER)    */
  REG_PCR(20, 9),           /* P20_9  (ETNB0TXD0)    */
  REG_PCR(20, 10),          /* P20_10 (ETNB0TXD1)    */
  REG_PCR(20, 12),          /* P20_12 (ETNB0TXD2)    */
  REG_PCR(20, 13),          /* P20_13 (ETNB0TXD3)    */
  REG_PCR(20, 14),          /* P20_14 (ETNB0TXEN)    */

  /* ETNB1 */
  REG_PCR(3, 6),            /* P3_6   (ETNB1MDC)     */
  REG_PCR(3, 7),            /* P3_7   (ETNB1MD)      */
/* No need to change PCR since ETNB1REFCLK is special function */
/*REG_PCR(3, 8),*/          /* P3_8   (ETNB1REFCLK)  */
  REG_PCR(6, 0),            /* P6_0   (ETNB1PHYINT)  */
  REG_PCR(6, 12),           /* P6_12  (ETNB1WOL)     */
/* ETNB1RESET is pulled-up to 2.5V (RESET de-asserted) in the PiggyBack board. Note that do not set port level to Hi (3.3 or 5V) because PHY 88E1112 needs 2.5V */
  REG_PCR(9, 0),            /* P9_0   (ETNB1RESET)   */
  REG_PCR(23, 0),           /* P23_0  (ETNB1RXER)    */
  REG_PCR(23, 1),           /* P23_1  (ETNB1RXDV)    */
  REG_PCR(23, 2),           /* P23_2  (ETNB1RXCLK)   */
  REG_PCR(23, 3),           /* P23_3  (ETNB1RXD0)    */
  REG_PCR(23, 4),           /* P23_4  (ETNB1RXD1)    */
  REG_PCR(23, 5),           /* P23_5  (ETNB1RXD2)    */
  REG_PCR(23, 6),           /* P23_6  (ETNB1RXD3)    */
  REG_PCR(23, 7),           /* P23_7  (ETNB1TXER)    */
  REG_PCR(23, 8),           /* P23_8  (ETNB1TXEN)    */
  REG_PCR(23, 9),           /* P23_9  (ETNB1TXCLK)   */
  REG_PCR(23, 10),          /* P23_10 (ETNB1TXD0)    */
  REG_PCR(23, 11),          /* P23_11 (ETNB1TXD1)    */
  REG_PCR(23, 12),          /* P23_12 (ETNB1TXD2)    */
  REG_PCR(23, 13),          /* P23_13 (ETNB1TXD3)    */

  (uint32)NULL_PTR
};

static const uint32 GaaPcrRegValue[] = {
  /* ETNB0 */
  PCR_AF2_IN_SOFTIOCNT,     /* P10_0  (ETNB0RXER)    */
  PCR_AF2_IN_SOFTIOCNT,     /* P10_1  (ETNB0TXCLK)   */
  PCR_AF2_IN_SOFTIOCNT,     /* P10_2  (ETNB0RXCLK)   */
  PCR_AF2_IN_SOFTIOCNT,     /* P10_3  (ETNB0RXD0)    */
  PCR_AF2_IN_SOFTIOCNT,     /* P10_4  (ETNB0RXD1)    */
  PCR_AF2_IN_SOFTIOCNT,     /* P10_5  (ETNB0RXD2)    */
  PCR_AF2_IN_SOFTIOCNT,     /* P10_6  (ETNB0RXD3)    */
  PCR_AF2_IN_SOFTIOCNT,     /* P10_7  (ETNB0RXDV)    */
  PCR_AF2_OUT_SOFTIOCNT,    /* P10_8  (ETNB0WOL)     */
  PCR_NML_OUT_SOFTIOCNT,    /* P20_0  (ETNB0RESET)   */
  PCR_AF2_IN_SOFTIOCNT,     /* P20_1  (ETNB0LINKSTA) */
  PCR_AF2_PIPC_SOFTIOCNT,   /* P20_3  (ETNB0MD)      */
  PCR_AF2_OUT_SOFTIOCNT,    /* P20_6  (ETNB0MDC)     */
  PCR_AF2_OUT_SOFTIOCNT,    /* P20_8  (ETNB0TXER)    */
  PCR_AF2_OUT_SOFTIOCNT,    /* P20_9  (ETNB0TXD0)    */
  PCR_AF2_OUT_SOFTIOCNT,    /* P20_10 (ETNB0TXD1)    */
  PCR_AF2_OUT_SOFTIOCNT,    /* P20_12 (ETNB0TXD2)    */
  PCR_AF2_OUT_SOFTIOCNT,    /* P20_13 (ETNB0TXD3)    */
  PCR_AF2_OUT_SOFTIOCNT,    /* P20_14 (ETNB0TXEN)    */

  /* ETNB1 */
  PCR_AF3_OUT_SOFTIOCNT,    /* P3_6   (ETNB1MDC)     */
  PCR_AF3_PIPC_SOFTIOCNT,   /* P3_7   (ETNB1MD)      */
/* No need to change PCR since ETNB1REFCLK is special function */
/*PCR_AFx_IN_SOFTIOCNT,*/   /* P3_8   (ETNB1REFCLK)  */
  PCR_AF4_IN_SOFTIOCNT,     /* P6_0   (ETNB1PHYINT)  */
  PCR_AF2_OUT_SOFTIOCNT,    /* P6_12  (ETNB1WOL)     */
/* ETNB1RESET is pulled-up to 2.5V (RESET de-asserted) in the PiggyBack board. Note that do not set port level to Hi (3.3 or 5V) because PHY 88E1112 needs 2.5V */
  PCR_NML_OUT_SOFTIOCNT,    /* P9_0   (ETNB1RESET)   */
  PCR_AF5_IN_SOFTIOCNT,     /* P23_0  (ETNB1RXER)    */
  PCR_AF5_IN_SOFTIOCNT,     /* P23_1  (ETNB1RXDV)    */
  PCR_AF5_IN_SOFTIOCNT,     /* P23_2  (ETNB1RXCLK)   */
  PCR_AF5_IN_SOFTIOCNT,     /* P23_3  (ETNB1RXD0)    */
  PCR_AF5_IN_SOFTIOCNT,     /* P23_4  (ETNB1RXD1)    */
  PCR_AF5_IN_SOFTIOCNT,     /* P23_5  (ETNB1RXD2)    */
  PCR_AF5_IN_SOFTIOCNT,     /* P23_6  (ETNB1RXD3)    */
  PCR_AF5_OUT_SOFTIOCNT,    /* P23_7  (ETNB1TXER)    */
  PCR_AF5_OUT_SOFTIOCNT,    /* P23_8  (ETNB1TXEN)    */
  PCR_AF5_IN_SOFTIOCNT,     /* P23_9  (ETNB1TXCLK)   */
  PCR_AF5_OUT_SOFTIOCNT,    /* P23_10 (ETNB1TXD0)    */
  PCR_AF5_OUT_SOFTIOCNT,    /* P23_11 (ETNB1TXD1)    */
  PCR_AF5_OUT_SOFTIOCNT,    /* P23_12 (ETNB1TXD2)    */
  PCR_AF5_OUT_SOFTIOCNT,    /* P23_13 (ETNB1TXD3)    */

  (uint32)NULL_PTR
}; 

void ETH_Port_Init(void)
{
//   volatile uint32 LulCount;
//   volatile uint32 *LpPcrReg;
//   volatile uint16 val  = 0;

//   LulCount = 0UL;

//   /* Register Protection Disable */
//   REG_PKCPROT = KCPROT_SET;

//   /* Set Port Write Enable Register(P10, P20) */
//   REG_PWE = 0x001FFFFEUL;

//   do
//   {
//     LpPcrReg = (volatile uint32*)(GaaPcrRegAddr[LulCount]);
//     *LpPcrReg = ((uint32)*LpPcrReg & (uint32)(~PCR_MASK)) | GaaPcrRegValue[LulCount];
//     LulCount++;
//   } while (GaaPcrRegAddr[LulCount] != (uint32)NULL_PTR);

//   // Set direction of pin AP0_8 to output.
//   REG_APCR0_8 = 0;
//   REG_APM0 &= ~0x0100U;
//     /*======================================================*/
//   /* RESET of Ether PHY asserted and de-asserted to reset */
//   /*======================================================*/
//   /* RESET de-asserted (Normal mode) via ETH1RESET */
//   REG_AP0 &= ~0x0100U;
//   REG_AP0 |= 0x0100U;

//   /* Wait for TRESET(Minimum reset pulse width during normal operation: 10ms) */
//   ETH_WAIT_NS(10 * 1000 * 1000);

//   /* Register Protection Enable */
//   REG_PKCPROT = KCPROT_CLR;
//   REG_PWE = 0x00000000UL;
}


void ErhIf_Sample_test(void)
{
    // uint16 LusRegValue;

    // Eth_ReadMii(ETH_CTRLIDX_0, PHY_TRCV_IDX, PHY_TRCV_STATUS_REG, &LusRegValue);

}

/******************************************************************************/
/* Initialize SGMII registers for ETNB1                                       */
/******************************************************************************/
void Eth_InitSgmii(void)
{
#if (ETH_CTRL_ENABLE_MII == STD_ON)
//   uint16 LusPhySts;

//   /* Release power down mode of PHY */
//   Eth_WriteMii( ETH_CTRLIDX_1, 1, 22, 0);
//   Eth_WriteMii( ETH_CTRLIDX_1, 1,  0, 0x1140);

//   /* Activate Enhanced SGMII (flow control) with default 100 Mbit/s speed in PHY, enable SGMII CLK */
//   Eth_WriteMii( ETH_CTRLIDX_1, 1, 22, 2);
//   Eth_WriteMii( ETH_CTRLIDX_1, 1, 16, 0x090c);
//   Eth_WriteMii( ETH_CTRLIDX_1, 1, 26, 0x2014);
//   Eth_WriteMii( ETH_CTRLIDX_1, 1,  0, 0x9040);

//   /* No Loopback, Soft Reset PHY to start, so that also auto negotiation starts */
//   Eth_WriteMii( ETH_CTRLIDX_1, 1, 22, 0);
//   Eth_WriteMii( ETH_CTRLIDX_1, 1,  0, 0x9340);

  /* wait until link is up */
//   do{
//     Eth_ReadMii( ETH_CTRLIDX_1, 1, 1, &LusPhySts);
//   }while((LusPhySts & 0x0004) != 0x0004); /* Link is up */
#endif
}
