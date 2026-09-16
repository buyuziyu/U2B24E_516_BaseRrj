/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Eth_Common_LLDriver.h                                                                               */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains common definitions among all low level drivers of Eth                                           */
/* Driver Component.                                                                                                  */
/*====================================================================================================================*/
/*                                                                                                                    */
/* Unless otherwise agreed upon in writing between your company and Renesas Electronics Corporation the following     */
/* shall apply!                                                                                                       */
/*                                                                                                                    */
/* Warranty Disclaimer                                                                                                */
/*                                                                                                                    */
/* There is no warranty of any kind whatsoever granted by Renesas. Any warranty is expressly disclaimed and excluded  */
/* by Renesas, either expressed or implied, including but not limited to those for non-infringement of intellectual   */
/* property, merchantability and/or fitness for the particular purpose.                                               */
/*                                                                                                                    */
/* Renesas shall not have any obligation to maintain, service or provide bug fixes for the supplied Product(s) and/or */
/* the Application.                                                                                                   */
/*                                                                                                                    */
/* Each User is solely responsible for determining the appropriateness of using the Product(s) and assumes all risks  */
/* associated with its exercise of rights under this Agreement, including, but not limited to the risks and costs of  */
/* program errors, compliance with applicable laws, damage to or loss of data, programs or equipment, and             */
/* unavailability or interruption of operations.                                                                      */
/*                                                                                                                    */
/* Limitation of Liability                                                                                            */
/*                                                                                                                    */
/* In no event shall Renesas be liable to the User for any incidental, consequential, indirect, or punitive damage    */
/* (including but not limited to lost profits) regardless of whether such liability is based on breach of contract,   */
/* tort, strict liability, breach of warranties, failure of essential purpose or otherwise and even if advised of the */
/* possibility of such damages. Renesas shall not be liable for any services or products provided by third party      */
/* vendors, developers or consultants identified or referred to the User by Renesas in connection with the Product(s) */
/* and/or the Application.                                                                                            */
/*                                                                                                                    */
/*====================================================================================================================*/
/* Environment:                                                                                                       */
/*              Devices:        X2x                                                                                   */
/*====================================================================================================================*/

/***********************************************************************************************************************
**                                              Revision Control History                                              **
***********************************************************************************************************************/
/*
 * 2.4.1: 30/06/2025    : Remove the SW-VERSION from header of file
 * 2.4.0: 30/06/2025    : Update SW-VERSION for RH850/Ver22.01.00 (D) U2Ax release
 * 2.3.1: 31/03/2025    : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 * 2.3.0: 28/02/2025    : Update SW-VERSION for Ver22.01.00/Ver22.01.00.D U2Cx Release
 * 2.2.0: 31/12/2024    : Update SW-VERSION for Ver22.02.00(D) U2Bx Final Release
 *        26/11/2024    : Updated QA-C 9.5.0 comments
 * 2.1.2: 31/10/2024    : Arrange define argument in Eth_BufHandlerType
 *                      : Increase SW-VERSION to 2.1.2
 * 2.1.1: 30/08/2024    : Add stHwStatEtnb and macro cover in Eth_BufHandlerType, Eth_RxFrameType for ETNB
 *        19/06/2024    : Change stTimestamp to stTimestampRsw2 in Eth_RxFrameType
 *        31/05/2024    : Add definition of stCounter, stRxStat, stTxStat stTxError in Eth_ControllerStatusType struct.
 *                      : Add definition of stTimestamp in Eth_RxFrameType.
 *        08/01/2024    : Remove QA-C Warning 1534, 1535, 1536
 *        26/12/2023    : Remove QA-C Warning 3432 according to QA-C 10.3.0
 *        12/12/2023    : Removed QA-C warning 1536,  according to QA-C 10.3.0
 *                      : Added QA-C warning 3630 according to QA-C 10.3.0
 *        01/12/2023    : Removed Eth_HwGetIngressTimeStamp, Eth_HwGetEgressTimeStamp, Eth_HwGetCurrentTime
 *        22/11/2023    : Added Eth_RxFrameType struct
 *                      : Added Eth_TxBufferType and Eth_BufHandlerType
 *                      : Remove extern function Eth_HwInit, Eth_HwDeInit, Eth_HwDisableController, 
 *                        Eth_HwEnableController, Eth_HwTransmit, Eth_HwGetCounterValues, Eth_HwGetRxStats, 
 *                        Eth_HwGetTxStats, Eth_HwGetTxErrorCounterValues, Eth_HwMainFunction, Eth_HwTxConfirmation,
 *                        Eth_HwCheckFifoIndex, Eth_HwReceive
 * 2.0.1: 17/10/2023    : Added QA-C Warning 1534, 1535, 1536 according to QA-C 10.3.0
 *                        Added QA-C 10.3.0 comments
 *        14/10/2023    : Remove Eth_HwCommonInit, Eth_HwCommonDeInit
 *                        Add Eth_HwPreCommonInit, Eth_HwPostCommonInit, Eth_HwPreCommonDeInit, Eth_HwPostCommonDeInit
 *        13/10/2023    : Change FifoIdx to QueueIdx in Eth_HwCheckFifoIndex and Eth_HwReceive.
 * 2.0.0: 24/07/2023    : Improve QAC comment.
 *        29/05/2023    : Added QA-C Warning 3432
 *        25/05/2023    : Add Std_ReturnType for Eth_HwGetEgressTimeStamp and Eth_HwGetIngressTimeStamp for R21-11. 
 *        23/05/2022    : Change Type of Eth_HwReadMii to Std_ReturnType and add LpRegValPtr to argument.
 * 1.5.3: 05/04/2022    : Add control index to parameter of Eth_HwCheckFifoIndex.
 *                        Add function prototype for Eth_HwDeInit.
 * 1.5.2: 03/03/2022    : Add control index to parameter of Eth_HwGetTxErrorCounterValues.
 *        28/01/2022    : Move the ETH_HEADER_SIZE, ETH_MACADDR_SIZE, ETH_SRC_DST_ADDRESS_SIZE,
 *                        ETH_ETHERTYPE_SIZE, ETH_VLAN_SIZE to Eth_Types.h
 *        25/01/2022    : Changed the management variable of the ring buffer of Tx buffer from uint8 to uint32.
 * 1.5.1: 14/12/2021    : Changed ON / OFF of function definition of Eth_HwReceive for support U2Bx devices.
 *        13/12/2021    : Add ulTsDescTail member variable to Eth_ControllerStatusType.
 *        28/10/2021    : Update include file for support U2Bx devices.
 *        12/01/2021    : Update QA-C 9.5.0 comments
 * 1.4.2: 24/08/2021    : Modify the format to 120 characters
 *        20/08/2021    : Update include file for support U2Bx devices.
 * 1.4.1: 07/05/2021    : Changes to support U2Bx devices.
 *                        Remove vendor ID from the file name, API names
 *                        and parameters according to BSW00347 requirement
 *        09/06/2021    : Remove QA-C Warning 3432 according to QA-C 9.5.0
 *        06/07/2021    : Updated QA-C 9.5.0 comments.
 * 1.2.0: 13/07/2020    : Release
 *        29/07/2020    : Add QAC 9.3.1 comment.
 * 1.1.0: 19/06/2020    : Release
 * 1.0.1: 04/06/2020    : To support Transmit/Receive interrupts for each controller.
 *                        Added ETH_59_COPY_MAC_ADDRESS macro.
 *                        Moved ETNB specific function.
 *                        Update for improvement by the QA-C.
 * 1.0.0: 25/03/2020    : Initial Version
 */
/**********************************************************************************************************************/
#ifndef ETH_COMMON_LLDRIVER_H
#define ETH_COMMON_LLDRIVER_H

/***********************************************************************************************************************
**                                               Macro type definitions                                               **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
#include "Eth_Types.h"
#include "Eth_Filter.h"
/* Include the LLDriver header file */
#if (ETH_MACRO_ETNC == STD_ON)
#include "Eth_ETNC_LLDriver.h"
#elif (ETH_MACRO_ETNB == STD_ON)
#include "Eth_ETNB_LLDriver.h"
#elif (ETH_MACRO_ETND == STD_ON)
#include "Eth_ETND_LLDriver.h"
#elif (ETH_MACRO_ETNE == STD_ON)
#include "Eth_ETNE_LLDriver.h"
#endif
#if (ETH_MACRO_ETNF == STD_ON)
#include "Eth_ETNF_LLDriver.h"
#endif

/***********************************************************************************************************************
**                                                General definitions                                                 **
***********************************************************************************************************************/
/* Bit length of byte */
#define ETH_BYTE_BITS            8UL

/* Maximum value of uint32 */
#define ETH_UINT32_MAXVALUE      0xFFFFFFFFUL

/* EIMK bit mask of EICn register */
#define ETH_EIC_EIMK_MASK        (uint16)0x0080U
/* EIRF bit mask of EICn register */
#define ETH_EIC_EIRF_MASK        (uint16)0x1000U
/* EIRF and EIMK bit mask of EICn register */
#define ETH_EIC_CONSISTENCY_MASK (uint16)(ETH_EIC_EIRF_MASK | ETH_EIC_EIMK_MASK)

/* Copy the MAC address */
#define ETH_COPY_MAC_ADDRESS(src, dst)                                                                                  /* PRQA S 3472 # JV-01 */\
  do                                   \
  {                                    \
    (dst)[0] = (src)[0];               \
    (dst)[1] = (src)[1];               \
    (dst)[2] = (src)[2];               \
    (dst)[3] = (src)[3];               \
    (dst)[4] = (src)[4];               \
    (dst)[5] = (src)[5];               \
  } while (0)

/***********************************************************************************************************************
**                                      PHY management data reletive definitions                                      **
***********************************************************************************************************************/
#define ETH_PHY_MAX_PHYAD_IDX    31U
#define ETH_PHY_MAX_REGAD_IDX    31U
#define ETH_PHY_PREAMBLE_SIZE    32UL
#define ETH_PHY_HEADER_SIZE      14UL
#define ETH_PHY_DATA_SIZE        16UL
/* Create a header for read operation */
#define ETH_PHY_RHEADER(phyad, regad)                                                                                   /* PRQA S 3472 # JV-01 */\
  (0x1800UL | ((uint32)(phyad) << 5UL) | ((uint32)(regad)))
/* Create a header for write operation */
#define ETH_PHY_WHEADER(phyad, regad)                                                                                   /* PRQA S 3472 # JV-01 */\
  (0x1400UL | ((uint32)(phyad) << 5UL) | ((uint32)(regad)))

/***********************************************************************************************************************
**                                             MDIO reletive definitions                                              **
***********************************************************************************************************************/
#define ETH_MDIO_SETUP_TIME      10UL

/***********************************************************************************************************************
**                                      Offset addressed from the top of buffer                                       **
**                                  These are depending on each MACRO specification                                   **
***********************************************************************************************************************/
/* Destination MAC address */
#define ETH_DST_MACADDR_OFFSET ETH_TXRX_BUFFER_PRE_PADDING
/* Src MAC address */
#define ETH_SRC_MACADDR_OFFSET   (ETH_TXRX_BUFFER_PRE_PADDING + ETH_MACADDR_SIZE)
/* Frame type */
#define ETH_FRAMETYPE_OFFSET     (ETH_SRC_MACADDR_OFFSET + ETH_MACADDR_SIZE)
/* Payload */
#define ETH_PAYLOAD_OFFSET       (ETH_TXRX_BUFFER_PRE_PADDING + ETH_HEADER_SIZE + ETH_TXRX_BUFFER_IN_PADDING)

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:3472)    : All toplevel uses of this function-like macro look like they could be replaced by            */
/*                       equivalent function calls.                                                                   */
/* Rule                : MISRA C:2012 Dir-4.9                                                                         */
/* JV-01 Justification : To prevent overhead and speed up the processing, there is no need to use function call for   */
/*                       such a small operation.                                                                      */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3630)    : The implementation of this struct/union type should be hidden.                               */
/* Rule                : MISRA C:2012 Dir-4.8                                                                         */
/* JV-01 Justification : This is accepted. Redudant of struct or union type has no affect to driver operation         */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3416)    : Logical operation performed on expression with possible side effects.                        */
/* Rule                : CERTCCM EXP45, CWE Rule CWE-398, CWE-569, CWE-737                                            */
/* JV-01 Justification : This is necessary for suppressing optimization by dummy loop.                                */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:5087)    : Use of #include directive after code fragment.                                               */
/* Rule                : MISRA C:2012 Rule-20.1                                                                       */
/* JV-01 Justification : This is accepted, due to implementation for include memmap is following AUTOSAR rule.        */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/
/* Order of the drop count information for Eth_GetDropCount */
typedef enum ETag_Eth_EtherDropType
{
  ETH_DROP_BUFF_OVER_RUN = 0,
  ETH_DROP_CRC_ERR,
  ETH_DROP_UNDERSIZE,
  ETH_DROP_OVERSIZE,
  ETH_DROP_ALIGNMENT_ERR,
  ETH_DROP_SQE_TEST_ERR,
  ETH_DROP_RECEIVE_DISCARD,
  ETH_DROP_ERRONEOUS_INBOUND,
  ETH_DROP_TRANSMIT_DISCARD,
  ETH_DROP_ERRONESOUS_OUTBOUND,
  ETH_DROP_SINGLE_COLLISION,
  ETH_DROP_MULTIPLE_COLLISTION,
  ETH_DROP_DEFERRED_TRANSMIT,
  ETH_DROP_LATE_COLLISION
} Eth_EtherDropType;

/* Order of the error statuses for Eth_GetEtherStats */
typedef enum ETag_Eth_EtherStatsType
{
  ETH_STATS_DROP_EVENTS = 0,
  ETH_STATS_OCTETS,
  ETH_STATS_PKTS,
  ETH_STATS_BROADCAST_PKTS,
  ETH_STATS_MULTICAST_PKTS,
  ETH_STATS_CRC_ALIGN_ERRORS,
  ETH_STATS_UNDERSIZE_PKTS,
  ETH_STATS_OVERSIZE_PKTS,
  ETH_STATS_FRAGMENTS,
  ETH_STATS_JABBERS,
  ETH_STATS_COLLISIONS,
  ETH_STATS_PKTS_64_OCTETS,
  ETH_STATS_PKTS_65_TO_127_OCTETS,
  ETH_STATS_PKTS_128_TO_255_OCTETS,
  ETH_STATS_PKTS_256_TO_511_OCTETS,
  ETH_STATS_PKTS_512_TO_1023_OCTETS,
  ETH_STATS_PKTS_1024_TO_1518_OCTETS,
  ETH_STATS_MAX_VALUE /* stopper */
} Eth_EtherStatsType;

#if (ETH_GET_ETHER_STATS_API == STD_ON || ETH_GET_COUNTER_VALUES_API == STD_ON || \
     ETH_GET_TX_STATS_API == STD_ON || ETH_GET_RX_STATS_API == STD_ON)
typedef struct Stag_Eth_TxRxStatsType
{
  /* The total number of good packets received that were directed to the broadcast address.*/
  uint32 ulStatsBroadcastPkts;
  /* The total number of packets (including bad packets, broadcast packets, and multicast packets) received. */
  uint32 ulRxStatsPkts;
  /* The total number of octets of data (including those in bad packets) received on the network
     (excluding framing bits but including FCS octets). */
  uint32 ulRxStatsOctets;
  /* The total number of packets received that had a length of bertween 64 and 1518 octets 
     that had either a bad Frame Check Sequence (FCS) with an integral number of octets 
     (FCS Error) or a bad FCS with a non-integral number of octets (Alignment Error). */
  uint32 ulRxStatsCrcAlignErrors;
  /* The total number of packets received that were less than 64 octets long (excluding 
     framing bits, but including FCS octets) and were otherwise well formed. 
     Also described in IETF RFC 2819 MIB etherStatsUndersizePkts. */
  uint32 ulRxStatsUndersizePkts;
  /* The total number of packets received that were longer than 1518 octets (excluding 
     framing bits, but including FCS octets) and were otherwise well formed. 
     Also described in IETF RFC 2819 MIB etherStatsOversizePkts */
  uint32 ulRxStatsOversizePkts;
  /* The total number of packets (including bad packets) received that were 64 octets in length.  */
  uint32 ulRxStatsPkts64Octets;
  /* The total number of packets (including bad packets) received that were between 65 and 127 octets in length. */
  uint32 ulRxStatsPkts65to127Octets;
  /* The total number of packets (including bad packets) received that were between 128 and 255 octets in length. */
  uint32 ulRxStatsPkts128to255Octets;
  /* The total number of packets (including bad packets) received that were between 256 and 511 octets in length. */
  uint32 ulRxStatsPkts256to511Octets;
  /* The total number of packets (including bad packets) received that were between 512 and 1023 octets in length. */
  uint32 ulRxStatsPkts512to1023Octets;
  /* The total number of packets (including bad packets) received that were between 1024 and 1518 octets in length. */
  uint32 ulRxStatsPkts1024to1518Octets;
  /* The number of subnetwork-unicast packets delivered to a higher-layer protocol. */
  uint32 ulRxUnicastFrames;
  /* The total number of octets transmitted out of the interface, including framing characters. */
  uint32 ulTxNumberOfOctets;
  /* The total number of packets that higher-level protocols requested be transmitted to a
     non-unicast address, including those that were discarded or not sent. */
  uint32 ulTxNUcastPkts;
  /* The total number of packets that higher-level protocols requested be transmitted to a subnetwork-unicast address,
     including those that were discarded or not sent. */
  uint32 ulTxUniCastPkts;
  /* dropped packets due to CRC errors */
  uint32 ulDropPktCrc;
  /* number of undersize packets which were less than 64 octets long
    (excluding framing bits, but including FCS octets) and were otherwise well formed. (see IETF RFC 1757) */
  uint32 ulUndersizePkt;
  /* number of oversize packets which are longer than 1518 octets
    (excluding framing bits, but including FCS octets) and were otherwise well formed. (see IETF RFC 1757) */
  uint32 ulOversizePkt;
  /* number of alignment errors, i.e.packets which are received and
     are not an integral number of octets in length and do not pass the CRC. */
  uint32 ulAlgnmtErr;
} Eth_TxRxStatsType;

#endif

/* Status of each controller */
typedef struct Stag_Eth_ControllerStatusType
{
  /* MAC address of this controller */
  Eth_MacAddressType stMacAddr;
  /* Current mode, DOWN or ACTIVE */
  Eth_ModeType enMode;
#if (ETH_UPDATE_PHYS_ADDR_FILTER == STD_ON)
  /* Whether a controller is in promiscuous mode.
  This is the logical state, not necessarily equal to the HW state. */
  boolean blPromiscuous;
  /* Whether the filter operation is activated */
  uint32 ulActiveFilterBits;
#endif
  /* Pointer to the head of tx buffer ring */
  uint32 ulTxBufHead;
  /* Pointer to the tail of tx buffer ring */
  uint32 ulTxBufTail;
#if (ETH_GLOBAL_TIME_SUPPORT == STD_ON)
  /* Pointer to the tail of ts descriptor ring */
  uint32 ulTsDescTail;
#endif
#if (ETH_GET_ETHER_STATS_API == STD_ON || ETH_GET_COUNTER_VALUES_API == STD_ON || \
     ETH_GET_TX_STATS_API == STD_ON || ETH_GET_RX_STATS_API == STD_ON)
  Eth_TxRxStatsType stTxRxStat;
#endif
  /* LLDriver specific status */
#if (ETH_MACRO_ETNF == STD_ON)
  Eth_HwStatusTypeEtnf stHwStatEtnf;
#endif
#if (ETH_MACRO_ETNB == STD_ON)
  Eth_HwStatusTypeEtnb stHwStatEtnb;
#endif
#if ((ETH_MACRO_ETND == STD_ON) || (ETH_MACRO_ETNE == STD_ON))
  Eth_HwStatusType stHwStat;
#endif
#if (ETH_MACRO_ETNE == STD_ON)
  #if (ETH_GET_COUNTER_VALUES_API == STD_ON)
  Eth_CounterType stCounter;
  #endif
  #if (ETH_GET_RX_STATS_API == STD_ON)
  Eth_RxStatsType stRxStat;
  #endif
  #if (ETH_GET_TX_STATS_API == STD_ON)
  Eth_TxStatsType stTxStat;
  #endif
  #if (ETH_GET_TX_ERROR_COUNTER_VALUES_API == STD_ON)
  Eth_TxErrorCounterValuesType stTxError;
  #endif
#endif /* (ETH_MACRO_ETNE == STD_ON) */
} Eth_ControllerStatusType;

/***********************************************************************************************************************
**  Type: Eth_BufHandlerType                                                                                          **
**                                                                                                                    **
**  Setting option                                                                                                    **
**                                                                                                                    **
**  Members:                                                                                                          **
**    stNode      - the Node for linked list management                                                               **
**    ulbufIdx    - the Index of buffer                                                                               **
**    ulbufAddr   - Pointer to the Frame in URAM to be transmitted                                                    **
**    ulTxLength  - Transmit request size                                                                             **
**    enChannel   - Tx Queue used to transmit the associated buffer                                                   **
**    blEnableTS  - Flag to store if TimeStamp shall be stored                                                        **
**    blTxConfirm - the Tx Confirmation flag                                                                          **
**    stTimeStamp   - Timestamp information                                                                           **
**    enTimeQual    - Timestamp quality                                                                               **
***********************************************************************************************************************/
typedef struct STag_Eth_BufHandlerType                                                                                  /* PRQA S 3630 # JV-01 */
{
  #if ((ETH_MACRO_ETNF == STD_ON) || (ETH_MACRO_ETNB == STD_ON))
  Eth_DListNodeType stNode;
  #endif
  uint32 ulbufIdx;
  uint32 ulbufAddr;
  uint32 ulTxLength;
  uint32 ulEthTypeAddr;
  #if ((ETH_MACRO_ETNF == STD_ON) || (ETH_MACRO_ETNB == STD_ON))
  Eth_TxChannelType enChannel;
  #endif
  boolean blbenableTS;
  boolean blTxConfirm;
  uint8 usDummy[2];
  uint8   ucDummy;
  #if ((ETH_MACRO_ETND == STD_ON) || (ETH_MACRO_ETNE == STD_ON))
  uint8 ucPriority;
  uint8 ucDummy0;
  #if ((ETH_GLOBAL_TIME_SUPPORT == STD_ON))
  Eth_TimeStampType stTimeStamp;
  Eth_TimeStampQualType enTimeQual;
  uint8 ucDummy1[3];
  #endif
  #endif
} Eth_BufHandlerType;

typedef struct STag_Eth_TxBufferType                                                                                    /* PRQA S 3630 # JV-01 */
{
  Eth_BufHandlerType *pBufferHdr;
  boolean blTxOngoing;
  uint8 ucDummy[3];
  #if (ETH_GLOBAL_TIME_SUPPORT == STD_ON)
  Eth_TimeStampType stTimeStamp;
  Eth_TimeStampQualType enTimeQual;
  #endif
  boolean blLocked;
} Eth_TxBufferType;

/***********************************************************************************************************************
**  Type: Eth_RxFrameType                                                                                       **
**                                                                                                                    **
**  Rx frame information structure (single frame single buffer)                                                       **
**                                                                                                                    **
**  Members:                                                                                                          **
**    ulFrameAddr    - frame address                                                                                  **
**    ulFrameLength  - frame length                                                                                   **
**    ulEthTypeAddr  - Ether type data pointer address                                                                **
**    stTimestamp    - timestamp if enabled                                                                           **
**    enTimeQual     - timestamp quality                                                                              **
**    ulTsns         - Timestamps nanosecond                                                                          **
**    ulTss          - Timestamp second                                                                               **
**  Below this is used only when ETH_GLOBAL_TIME_SUPPORT is STD_ON and ETH_MACRO_ETNE.                                **
**    stTimestampRsw2 - Timestamp information                                                                         **
***********************************************************************************************************************/
typedef struct STag_Eth_RxFrameType
{
  uint32 ulFrameAddr;
  uint32 ulFrameLength;
  uint32 ulEthTypeAddr;
  #if ((ETH_MACRO_ETNF == STD_ON) || (ETH_MACRO_ETNB == STD_ON))
  Eth_DescTimeStampType stTimestamp;
  Eth_TimeStampQualType enTimeQual;
  #endif
  #if (ETH_MACRO_ETND == STD_ON)
  uint32 ulTsns;
  uint32 ulTss;
  #endif
  #if (ETH_MACRO_ETNE == STD_ON)
  #if (ETH_GLOBAL_TIME_SUPPORT == STD_ON)
  Eth_TimeStampDescType  stTimestampRsw2;
  #endif
  #endif
} Eth_RxFrameType;

/* A dummy value for unsupported items by HW */
#define ETH_NOT_AVAILABLE 0xFFFFFFFFUL

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/
#define ETH_START_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"

#if ((ETH_MACRO_ETND == STD_ON) || (ETH_MACRO_ETNE == STD_ON))
extern FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_HwPreCommonInit(void);
extern FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_HwPostCommonInit(void);
#endif

#if (ETH_MACRO_ETNE == STD_ON)
extern FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_HwPreCommonDeInit(void);
extern FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_HwPostCommonDeInit(void);
#endif

#if (ETH_GET_DROP_COUNT_API == STD_ON)
extern FUNC(void, ETH_PRIVATE_CODE)
    Eth_HwGetDropCount(CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulCountValues,
                       CONSTP2VAR(uint32, AUTOMATIC, ETH_APPL_DATA) LpDropCount);
#endif

#if (ETH_GET_ETHER_STATS_API == STD_ON)
extern FUNC(void, ETH_PRIVATE_CODE)
    Eth_HwGetEtherStats(CONST(uint32, AUTOMATIC) LulCtrlIdx,
                        CONSTP2VAR(uint32, AUTOMATIC, ETH_APPL_DATA) LpEtherStats);
#endif

#if (ETH_GLOBAL_TIME_SUPPORT == STD_ON)

FUNC(void, ETH_PRIVATE_CODE) Eth_HwEnableEgressTimeStamp(CONST(uint32, AUTOMATIC) LulCtrlIdx, uint8 BufIdx);

#if (ETH_AR_VERSION == ETH_AR_422_VERSION)
FUNC(Std_ReturnType, ETH_PRIVATE_CODE)
    Eth_HwSetCorrectionTime(CONST(uint32, AUTOMATIC) LucCtrlIdx,
                            P2CONST(Eth_TimeIntDiffType, AUTOMATIC, ETH_APPL_DATA) LpTimeOffsetPtr);

FUNC(Std_ReturnType, ETH_PRIVATE_CODE)
    Eth_HwSetGlobalTime(CONST(uint32, AUTOMATIC) LulCtrlIdx,
                        P2CONST(Eth_TimeStampType, AUTOMATIC, ETH_APPL_DATA) timeStampPtr);
#endif
#endif

#define ETH_STOP_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"

#endif /* !ETH_COMMON_LLDIVER_H */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
