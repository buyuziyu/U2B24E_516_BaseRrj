/*============================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                         */
/* File name    = Eth_GeneralTypes.h                                          */
/* ===========================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2023-2025 Renesas Electronics Corporation. All rights reserved.        */
/*============================================================================*/
/* Purpose:                                                                   */
/* Provision for Communication Stack dependent types                          */
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
 * 2.4.1      30/06/2025     Remove the SW-VERSION from header of file
 * 2.4.0      30/06/2025     Update SW-VERSION for RH850/Ver22.01.00 (D) U2Ax Release
 * 2.3.1      31/03/2025     Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02 Release
 * 2.2.0      31/12/2024     Add ETH_MODE_ACTIVE_WITH_WAKEUP_REQUEST in Eth_ModeType
 *                           Update SW-VERSION for Ver22.02.00(D) U2Bx Final Release
 * 2.1.2      31/10/2024     Update SW-VERSION to 2.1.2
 * 2.1.1      24/07/2024     Update SW-VERSION to 2.1.1
 * 2.1.0      23/02/2024     Update SW-VERSION to 2.1.0
 * 2.0.2      15/04/2024     Remove Eth_SpiStatusType
 * 2.0.1      22/09/2023     Initial Version
 */
/******************************************************************************/
#ifndef ETH_GENERALTYPES_H
#define ETH_GENERALTYPES_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "ComStack_Types.h"                  /* Com Stack AUTOSAR types */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/*
 * AUTOSAR specification version information
 */

#define ETH_GENERALTYPES_AR_RELEASE_MAJOR_VERSION    4
#define ETH_GENERALTYPES_AR_RELEASE_MINOR_VERSION    8
#define ETH_GENERALTYPES_AR_RELEASE_REVISION_VERSION 0

/*
 * File version information
 */
#define ETH_GENERALTYPES_SW_MAJOR_VERSION 2
#define ETH_GENERALTYPES_SW_MINOR_VERSION 2
#define ETH_GENERALTYPES_SW_PATCH_VERSION 0

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/
/*******************************************************************************
**                      Global Data Types (ECU dependent)                     **
*******************************************************************************/
/* Type definition for DataType */
typedef uint8 Eth_DataType;
/*******************************************************************************
**                      Global Data Types (ECU independent)                   **
*******************************************************************************/
/* Ethernet buffer identifier type. */
typedef uint32 Eth_BufIdxType;

/* Type definition for FrameType */
typedef uint16 Eth_FrameType;

/***********************************************************
Enum: Eth_ModeType

Enumeration for Ethernet Mode

Members:
ETH_MODE_DOWN                          - Controller Disabled Mode
ETH_MODE_ACTIVE                        - Controller Enabled Mode
ETH_MODE_ACTIVE_WITH_WAKEUP_REQUEST    - Controller Enabled Mode and wake-up request
ETH_MODE_ACTIVE_TX_OFFLINE             - Controller Silent Communication Mode
ETH_MODE_STANDBY                       - Controller Standby Mode
*/
typedef enum ETag_Eth_ModeType
{
  ETH_MODE_DOWN = 0,
  ETH_MODE_ACTIVE,
  ETH_MODE_ACTIVE_WITH_WAKEUP_REQUEST,
  ETH_MODE_ACTIVE_TX_OFFLINE,
  ETH_MODE_STANDBY
} Eth_ModeType;


/***********************************************************
Enum: Eth_StateType

Enumeration for Ethernet driverState

Members:
ETH_STATE_UNINIT  - UnInitialized State
ETH_STATE_INIT    - Initialized State
*/
typedef enum ETag_Eth_StateType
{
  ETH_STATE_UNINIT = 0,
  ETH_STATE_INIT
} Eth_StateType;

/***********************************************************
Enum: Eth_RxStatusType

Enumeration for Rx status

Members:
ETH_RECEIVED                     - Ethernet frame has been received,
                                   no further frames available
ETH_NOT_RECEIVED                 - Ethernet frame has not been received,
                                   no further frames available
ETH_RECEIVED_MORE_DATA_AVAILABLE - Ethernet frame has been received,
                                   more frames are available
*/
typedef enum ETag_Eth_RxStatusType
{
  ETH_RECEIVED = 0,
  ETH_NOT_RECEIVED,
  ETH_RECEIVED_MORE_DATA_AVAILABLE
} Eth_RxStatusType;

/***********************************************************
Enum: Eth_FilterActionType

Enumeration for ETH Filter Action

Members:
ETH_ADD_TO_FILTER       - add the MAC address to the filter,
ETH_REMOVE_FROM_FILTER  - remove the MAC address from the filter,
*/
typedef enum ETag_Eth_FilterActionType
{
  ETH_ADD_TO_FILTER = 0,
  ETH_REMOVE_FROM_FILTER
} Eth_FilterActionType;

/***********************************************************
Enum: Eth_TimeStampQualType

Enumeration for quality information regarding the evaluated time stamp.
Meaning of each value is depending on the HW. 

Members:
ETH_VALID
ETH_INVALID
ETH_UNCERTAIN
*/
typedef enum
{
  ETH_VALID = 0,
  ETH_INVALID,
  ETH_UNCERTAIN
} Eth_TimeStampQualType;

/***********************************************************
Struct: Eth_TimeStampType

Struct containing a time stamp value

Members:
nanoseconds - Nanoseconds part of the time
seconds     - 32 bit LSB of the 48 bits Seconds part of the time
secondsHi   - 16 bit MSB of the 48 bits Seconds part of the time
*/
typedef struct
{
  uint32 nanoseconds;
  uint32 seconds;
  uint16 secondsHi;
} Eth_TimeStampType;

/***********************************************************
Struct: Eth_TimeIntDiffType

Struct cantaining an express time difference

Members:
diff     - Time difference
sign     - Positive (true) / negative (false) time
*/
typedef struct
{
  Eth_TimeStampType diff;
  boolean sign;
} Eth_TimeIntDiffType;

/***********************************************************
Struct: Eth_RateRatioType

Struct containing an express frequency ratio.

Members:
IngressTimeStampDelta - IngressTimeStampSync2 - IngressTimeStampSync1
OriginTimeStampDelta  - OriginTimeStampSync2 - OriginTimeStampSync1
*/
typedef struct
{
  Eth_TimeIntDiffType IngressTimeStampDelta;
  Eth_TimeIntDiffType OriginTimeStampDelta;
} Eth_RateRatioType;

/***********************************************************
Struct: Eth_MacVlanType

The interpretation of this value is not specified, 
i.e. whether it is number of used bytes or number of used memory cells, etc.

Members:
MacAddr    - Specifies the MAC address [0..255,0..255,0..255,0..255,0..255,0..255]
VlanId     - Specifies the VLAN address 0..65535
SwitchPort - Specifies the ports of the switch as bit mask (0x00000001->Port0,
             0x80000001->Port31+Port0)
*/
typedef struct
{
  uint8  MacAddr[6];
  uint16 VlanId;
  uint32 SwitchPort;
} Eth_MacVlanType;

/***********************************************************
Struct: Eth_CounterType

Statistic counter for diagnostics.

Members:
DropPktBufOverrun    - dropped packets due to buffer overrun
DropPktCrc           - dropped packets due to CRC errors
UndersizePkt         - number of undersize packets which were less than 64 octets long 
                       (excluding framing bits, but including FCS octets) and were otherwise 
                       well formed. (see IETF RFC 1757)
OversizePkt          - number of oversize packets which are longer than 1518 octets 
                       (excluding framing bits, but including FCS octets) and were otherwise 
                       well formed. (see IETF RFC 1757)
AlgnmtErr            - number of alignment errors, i.e. packets which are received and are 
                       not an integral number of octets in length and do not pass the CRC.
SqeTestErr           - SQE test error according to IETF RFC1643 dot3StatsSQETestErrors
DiscInbdPkt          - The number of inbound packets which were chosen to be discarded 
                       even though no errors had been detected to prevent their being deliverable 
                       to a higher-layer protocol. One possible reason for discarding such a packet 
                       could be to free up buffer space. (see IETF RFC 2233 ifInDiscards)
ErrInbdPkt           - total number of erroneous inbound packets
DiscOtbdPkt          - The number of outbound packets which were chosen to be discarded even though 
                       no errors had been detected to prevent their being transmitted. One possible 
                       reason for discarding such a packet could be to free up buffer space. 
                       (see IETF RFC 2233 ifOutDiscards)
ErrOtbdPkt           - total number of erroneous outbound packets
SnglCollPkt          - Single collision frames: A count of successfully transmitted frames on a 
                       particular interface for which transmission is inhibited by exactly one 
                       collision. (see IETF RFC1643 dot3StatsSingleCollisionFrames)
MultCollPkt          - Multiple collision frames: A count of successfully transmitted frames on 
                       a particular interface for which transmission is inhibited by more than 
                       one collision. (see IETF RFC1643 dot3StatsMultipleCollisionFrames)
DfrdPkt              - Number of deferred transmission: A count of frames for which the first 
                       transmission attempt on a particular interface is delayed because the 
                       medium is busy. (see IETF RFC1643 dot3StatsDeferredTransmissions)
LatCollPkt           - Number of late collisions: The number of times that a collision is detected 
                       on a particular interface later than 512 bit-times into the transmission of 
                       a packet. (see IETF RFC1643 dot3StatsLateCollisions)
HwDepCtr0            - hardware dependent counter value
HwDepCtr1            - hardware dependent counter value
HwDepCtr2            - hardware dependent counter value
HwDepCtr3            - hardware dependent counter value
*/
typedef struct
{
  uint32 DropPktBufOverrun;
  uint32 DropPktCrc;
  uint32 UndersizePkt;
  uint32 OversizePkt;
  uint32 AlgnmtErr;
  uint32 SqeTestErr; 
  uint32 DiscInbdPkt;
  uint32 ErrInbdPkt;
  uint32 DiscOtbdPkt;
  uint32 ErrOtbdPkt;
  uint32 SnglCollPkt;
  uint32 MultCollPkt;
  uint32 DfrdPkt;
  uint32 LatCollPkt;
  uint32 HwDepCtr0;
  uint32 HwDepCtr1;
  uint32 HwDepCtr2;
  uint32 HwDepCtr3;
} Eth_CounterType;

/***********************************************************
Struct: Eth_RxStatsType

Statistic counter for diagnostics.

Members:
RxStatsDropEvents           - The total number of events in which packets were dropped by the probe 
                              due to lack of resources. Also described in IETF RFC 2819 MIB 
                              etherStatsDropEvents.
RxStatsOctets               - The total number of octets of data (including those in bad packets) 
                              received on the network (excluding framing bits but including FCS octets). 
                              Also described in IETF RFC 2819 MIB etherStatsOctets.
RxStatsPkts                 - The total number of packets (including bad packets, broadcast packets, 
                              and multicast packets) received. Also described in IETF RFC 2819 MIB 
                              etherStatsPkts
RxStatsBroadcastPkts        - The total number of good packets received that were directed to the 
                              broadcast address. Also described in IETF RFC 2819 MIB etherStatsBroadcastPkts
RxStatsMulticastPkts        - The total number of good packets received that were directed to a multicast address. 
                              Also described in IETF RFC 2819 MIB etherStatsMulticastPkts.
RxStatsCrcAlignErrors       - The total number of packets received that had a length of bertween 64 and 1518 octets 
                              that had either a bad Frame Check Sequence (FCS) with an integral number of octets 
                              (FCS Error) or a bad FCS with a non-integral number of octets (Alignment Error). 
                              Also described in IETF RFC 2819 MIB etherStatsCRCAlignErrors
RxStatsUndersizePkts        - The total number of packets received that were less than 64 octets long (excluding 
                              framing bits, but including FCS octets) and were otherwise well formed. 
                              Also described in IETF RFC 2819 MIB etherStatsUndersizePkts.
RxStatsOversizePkts         - The total number of packets received that were longer than 1518 octets (excluding 
                              framing bits, but including FCS octets) and were otherwise well formed. 
                              Also described in IETF RFC 2819 MIB etherStatsOversizePkts
RxStatsFragments            - The total number of packets received that were less than 64 octets in length (excluding 
                              framing bits but including FCS octets) and had either a bad Frame Check Sequence (FCS) 
                              with an integral number of octets (FCS Error) or a bad FCS with a non-integral number of 
                              octets (Alignment Error). Also described in IETF RFC 2819 MIB etherStatsFragments. 
RxStatsJabbers              - The total number of packets received that were longer than 1518 octets, and had either 
                              a bad Frame Check Sequence (FCS) with an integral number of octets (FCS Error) or a bad 
                              FCS with a non-integral number of octets (Alignment Error). Also described in IETF RFC 
                              2819 MIB etherStatsJabbers.
RxStatsCollisions           - The best estimate of the total number of collisions on this Ethernet segment. 
                              Also described in IETF RFC 2819 MIB etherStatsCollisions
RxStatsPkts64Octets         - The total number of packets (including bad packets) received that were 64 octets in 
                              length. Also described in IETF RFC 2819 MIB etherStatsPkts64Octets
RxStatsPkts65to127Octets    - The total number of packets (including bad packets) received that were between 65 and 127 
                              octets in length. Also described in IETF RFC 2819 MIB etherStatsPkts65to127Octets
RxStatsPkts128to255Octets   - The total number of packets (including bad packets) received that were between 128 and 
                              255 octets in length. Also described in IETF RFC 2819 MIB etherStatsPkts128to255Octets
RxStatsPkts256to511Octets   - The total number of packets (including bad packets) received that were between 256 and 
                              511 octets in length. Also described in IETF RFC 2819 MIB etherStatsPkts256to511Octets
RxStatsPkts512to1023Octets  - The total number of packets (including bad packets) received that were between 512 and 
                              1023 octets in length. Also described in IETF RFC 2819 MIB etherStatsPkts512to1023Octets
RxStatsPkts1024to1518Octets - The total number of packets (including bad packets) received that were between 1024 and 
                              1518 octets in length. Also described in IETF RFC 2819 MIB etherStatsPkts1024to1518Octets
RxUnicastFrames             - The number of subnetwork-unicast packets delivered to a higher-layer protocol. 
                              Also described in IETF RFC1213 MIB ifInUcastPkts
*/
typedef struct
{
  uint32 RxStatsDropEvents;
  uint32 RxStatsOctets;
  uint32 RxStatsPkts;
  uint32 RxStatsBroadcastPkts;
  uint32 RxStatsMulticastPkts;
  uint32 RxStatsCrcAlignErrors; 
  uint32 RxStatsUndersizePkts;
  uint32 RxStatsOversizePkts;
  uint32 RxStatsFragments;
  uint32 RxStatsJabbers;
  uint32 RxStatsCollisions;
  uint32 RxStatsPkts64Octets;
  uint32 RxStatsPkts65to127Octets;
  uint32 RxStatsPkts128to255Octets;
  uint32 RxStatsPkts256to511Octets;
  uint32 RxStatsPkts512to1023Octets;
  uint32 RxStatsPkts1024to1518Octets;
  uint32 RxUnicastFrames;
} Eth_RxStatsType;

/***********************************************************
Struct: Eth_TxStatsType

Statistic counter for diagnostics.

Members:
TxNumberOfOctets - The total number of octets transmitted out of the interface, including framing characters. 
                   Also described in IETF RFC1213 MIB ifOutOctets.
TxNUcastPkts     - The total number of packets that higher-level protocols requested be transmitted to a non-unicast 
                   (i.e., a subnetwork-broadcast or subnetwork-multicast) address, including those that were discarded 
                   or not sent. Also described in IETF RFC1213 MIB ifOutNUcastPkts
TxUniCastPkts    - The total number of packets that higher-level protocols requested be transmitted to a 
                   subnetwork-unicast address, including those that were discarded or not sent. Also described in 
                   IETF RFC1213 MIB ifOutUcastPkts.
*/
typedef struct
{
  uint32 TxNumberOfOctets;
  uint32 TxNUcastPkts;
  uint32 TxUniCastPkts;
} Eth_TxStatsType;

/***********************************************************
Struct: Eth_TxErrorCounterValuesType

Statistic counter for diagnostics.

Members:
TxDroppedNoErrorPkts - The number of outbound packets which were chosen to be discarded even though no errors had been 
                       detected to prevent their being transmitted. One possible reason for discarding such a packet 
                       could be to free up buffer space. Also described in IETF RFC1213 MIB ifOutDiscards
TxDroppedErrorPkts   - transmitted because of errors. Also described in IETF RFC1213 MIB ifOutErrors
TxDeferredTrans      - A count of frames for which the first transmission attempt on a particular interface is delayed 
                       because the medium is busy. The count represented by an instance of this object does not include 
                       frames involved in collisions. Also described in IETF RFC1643 MIB dot3StatsDeferredTransmissions
TxSingleCollision    - A count of successfully transmitted frames on a particular interface for which transmission is 
                       inhibited by exactly one collision. A frame that is counted by an instance of this object is 
                       also counted by the corresponding instance of either the TxUniCastPkts and TxNUcastPkts and is 
                       not counted by the corresponding instance of the TxMultipleCollision object. 
                       Also described in IETF RFC1643 MIB dot3StatsSingleCollisionFrames
TxMultipleCollision  - A count of successfully transmitted frames on a particular interface for which transmission is 
                       inhibited by more than one collision. A frame that is counted by an instance of this object is 
                       also counted by the corresponding instance of either the TxUniCastPkts and TxNUcastPkts and is 
                       not counted by the corresponding instance of the TxSingleCollision object. 
                       Also described in IETF RFC1643 MIB dot3StatsMultipleCollisionFrames.
TxLateCollision      - The number of times that a collision is detected on a particular interface later than 512 
                       bit-times into the transmission of a packet. Five hundred and twelve bit-times corresponds to 
                       51.2 microseconds on a 10 Mbit/s system. A (late) collision included in a count represented by 
                       an instance of this object is also considered as a (generic) collision for purposes of other 
                       collision-related statistics. Also described in IETF RFC1643 MIB dot3StatsLateCollisions
TxExcessiveCollison  - A count of frames for which transmission on a particular interface fails due to excessive 
                       collisions. Also described in IETF RFC1643 MIB dot3StatsExcessiveCollisions
*/
typedef struct
{
  uint32 TxDroppedNoErrorPkts;
  uint32 TxDroppedErrorPkts;
  uint32 TxDeferredTrans;
  uint32 TxSingleCollision;
  uint32 TxMultipleCollision;
  uint32 TxLateCollision; 
  uint32 TxExcessiveCollison;
} Eth_TxErrorCounterValuesType;

#endif /* ETH_GENERALTYPES_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

