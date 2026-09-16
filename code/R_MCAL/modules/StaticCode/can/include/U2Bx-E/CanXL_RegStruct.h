/*====================================================================================================================*/
/* Project      = RH850/X2x MCAL PF Development                                                                       */
/* Module       = CanXL_RegStruct.h                                                                                   */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2024, 2025 Renesas Electronics Corporation. All rights reserved.                                               */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Provision of Controller register structure                                                                         */
/*                                                                                                                    */
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
/*              Devices:        U2Bx-E                                                                                */
/*====================================================================================================================*/

/***********************************************************************************************************************
**                                              Revision Control History                                              **
***********************************************************************************************************************/
/*
 * 2.4.1:  30/06/2025  : Remove the SW-VERSION from header of file
 * 2.3.1:  31/03/2025  : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 * 2.1.2:  31/10/2024  : Update SW-VERSION for Ver22.01.02 to 2.1.2
 * 2.1.1:  07/08/2024  : As part of CANXL driver support, following changes are made:
 *                      1. Update macro CAN_PRT_STOP
 *         29/07/2024  : As part of CANXL driver support, following changes are made:
 *                      1. Update macro CAN_CANXL_BOEF
 *         20/06/2024  : As part of CANXL driver support, following changes are made:
 *                      1. Add macro CANXL_NUM_OF_BUS_ERROR, CANXL_BUS_ERROR_MASK, CANXL_PRT_SRES_BIT
 *                      CANXL_IRC_BUSOFF_BIT
 *        10/05/2024  : Initial version.
 */
/**********************************************************************************************************************/

#ifndef CAN_XL_REG_STRUCUTURE_H
#define CAN_XL_REG_STRUCUTURE_H

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/

/* AUTOSAR release version information */
#define CAN_REGSTRUCT_AR_RELEASE_MAJOR_VERSION \
                                                 CAN_AR_RELEASE_MAJOR_VERSION
#define CAN_REGSTRUCT_AR_RELEASE_MINOR_VERSION \
                                                 CAN_AR_RELEASE_MINOR_VERSION
#define CAN_REGSTRUCT_AR_RELEASE_REVISION_VERSION \
                                              CAN_AR_RELEASE_REVISION_VERSION

/* File version information */
#define CAN_REGSTRUCT_SW_MAJOR_VERSION    CAN_SW_MAJOR_VERSION
#define CAN_REGSTRUCT_SW_MINOR_VERSION    CAN_SW_MINOR_VERSION

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:3630)    : The implementation of this struct/union type should be hidden.                               */
/* Rule                : MISRA C:2012 Dir-4.8                                                                         */
/* JV-01 Justification : This is accepted. Redundant of struct or union type has no affect to driver operation.       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                    Global Symbols                                                  **
***********************************************************************************************************************/
/* L_MEM Base Address (4MSB)*/
#define CAN_LRAM_BASE_ADDR_CH0                    0x18002000UL
#define CAN_LRAM_BASE_ADDR_CH1                    0x18042000UL

#define CANXL_CHECK_BIT_SET                       (uint32)0x01UL
/* CXLGSTS */
#define CAN_CXLGSTS_LRAMINIT_MASK                 (uint32)0x01UL
/* CXLCCLKC */
/* Clock Control for HOST clock domain - When this bit is set, HOST clock(HOST_CLK) will be switched on */
#define CAN_CXLCCLKC_HCLKC_MASK                   (uint32)0x01UL
/* Clock Control for CAN clock domain - When this bit is set, CAN clock(CAN_CLK) will be switched on.*/
#define CAN_CXLCCLKC_CCLKC_MASK                   (uint32)0x02UL
/* Clock Control for TIMEBASE clock domain - When this bit is set, TIMEBASE clock(TIMEBASE_CLK) will be switched on. */
#define CAN_CXLCCLKC_TCLKC_MASK                   (uint32)0x04UL
/* When C4h is written in these bits,
   the write of CXLCCLKC.HCLKC, CXLCCLKC.CCLKC and CXLCCLKC.TCLKC bits become available. */
#define CAN_CXLCCLKC_KEY_VALUE                    (uint32)(0xC4UL << 8U)

/* 1.4.4.2.1.4 MH_STS .. Message Handler Status register */
/* Status of MH core clock: 0 = clock off, 1 = clock on */
#define CAN_MH_STS_CLOCK_ACTIVE                   (uint32)(0x01UL << 8U)
/* Value of the ENABLE signal driven by the PRT. The PRT signalizes via
   ENABLE whether it is active (ENABLE = 1) and requires message handling or not (ENABLE = 0). */
#define CAN_MH_STS_CLOCK_ENABLE                   (uint32)(0x01UL << 4U)
/* This bit is the general busy flag, it is an ORED( RX/TX FIFO Queues and TX Priority Queue slots busy flags) */
#define CAN_MH_STS_CLOCK_BUSY                     (uint32)(0x01UL << 0U)
/* This bit is used to select Mode of Rx FIFO Queue  */
#define CAN_MH_RX_FIFO_NORAL_MODE_VALUE           (uint32)0x00UL
#define CAN_MH_RX_FIFO_CONTINUOUS_MODE_VALUE      (uint32)0x01UL
/* 1.5.4.2.1.3 STAT .. PRT Status Register */
#define CAN_STAT_CLKA                             (uint32)(0x01UL << 4U)
/* Start Protocol Controller */
#define CAN_PRT_START                             (uint32)0x10UL
/* Stop Protocol Controller */
#define CAN_PRT_STOP                              (uint32)0x03UL

/* MH_CFG */
/* Initial value */
#define CAN_MH_INITIAL_VALUE                      (uint32)0x00000000UL
/* Rx Continous Mode */
#define CAN_MH_CFG_RX_CONT_DC                     (uint32)0x01UL
/* TX message re-transmissions (0x07 - unlimited) */
#define CAN_MH_CFG_MAX_RETRANS                    (uint32)(0x7UL << 8U)
/* Instance Number - default 0x00 temparorily */
#define CAN_MH_CFG_NST_NUM                        (uint32)0x0UL
/* Start MH */
#define CAN_MH_START                              (uint32)0x00000001UL
/* Check bit ENABLE */
#define CAN_MH_ENABLE_MASK                        (uint32)0x10UL
/* Check bit Bus-Off */
#define CAN_CANXL_BOEF                            (uint32)(0x01UL << 7U)
/* Check bit STOP */
#define CAN_CANXL_STP                             (uint32)(0x01UL << 3U)
/* Check bit Error Passive */
#define CAN_CANXL_EPEF                            (uint32)(0x01UL << 6U)
/* Clear bit value */
#define CAN_CANXL_ERFL_CLEAR                      (uint32)0x00000000UL
/* Error Disable bit */
#define CANXL_PRT_EFDI_BIT                        (uint32)(0x01UL << 10U)
/* PWM Transceiver bit */
#define CANXL_PRT_XLTR_BIT                        (uint32)(0x01UL << 9U)
/* TDCO bit */
#define CANXL_PRT_TDCO_BIT                        (uint32)(0x01UL << 2U)
/* Receive error counter bit */
#define CANXL_REC_MASK    0x007F0000UL
#define CANXL_REC_OFFSET  16
/* Transmit error counter bit */
#define CANXL_TEC_MASK    0xFF000000UL
#define CANXL_TEC_OFFSET  24
/* PRT EVENT Acknowledge bit */
#define CANXL_PRT_EVENT_ACK                       (uint32)(0x01UL << 3U)
/* PRT EVENT number of bus error*/
#define CANXL_NUM_OF_BUS_ERROR                    6U
/* PRT EVENT number of bus error*/
#define CANXL_BUS_ERROR_MASK                      (uint32)0x0000003FUL
/* SRES bit for PRT.CTRL */
#define CANXL_PRT_SRES_BIT                        (uint32)(1UL << 8UL)
/* PRT_BUS_OFF bit for IRC.ERR_RAW */
#define CANXL_IRC_BUSOFF_BIT                      (uint32)(1UL << 23UL)
/* MH_SFTY_CFG */
/* Define maximum timeout value
DMA_TO_VAL[0:7]:   This value is used by the watchdog timer for the DMA_AXI interface
MEM_TO_VAL[8:15]:  This value is used by the watchdog timer for the MEM_AXI interface
PRT_TO_VAL[16:29]: This value is used by the watchdog timers for the internal RX_MSG and TX_MSG interfaces
PRESCALER[30:31]:  Prescaler used to generate the timer ticks for the watchdogs
*/
#define CANXL_TIMEOUT_CONFIG_VALUE                (uint32)0xFFFFFFFFUL

/* MH_SFTY_CTRL */
/* Enable all event except CRC checking */
#define CANXL_SFTY_CHECKING_ENABLE                (uint32)0x00FCUL

/* AXI_PARAMS */
/* Define the maximum read/write pending transactions on DMA_AXI interface */
#define CANXL_AXI_MAX_PEND_VALUE                  (uint32)0x33UL

/* RX_FQ_CTRL1 */
/* Define value to clear Abort bit */
#define CANXL_RX_FQ_CLEAR_ABORT                                            (uint32)0x00000000UL
/* Define value to set Abort bit */
#define CANXL_RX_FQ_SET_ABORT                                              (uint32)0x000000FFUL

/* RX_FQ_CTRL2 */
/* Disable RX FIFO Queue */
#define CANXL_RX_FIFO_QUEUE_DISABLE                                        (uint32)0x00000000UL

/* TX_FILTER_CTRL0 */
/* Tx Filter initial value (reject CAN-FD, Classic CAN messages) */
#define CAN_TX_FILTER_INITIAL_VALUE               (uint32)0x00060000UL

/* TX_FILTER_REFVALn */
/* Define value or value/mask pair to perform the comparison
Bit 7:0    Define the reference value 0.
Bit 15:8   Define the reference value 1.
Bit 23:16  Define the reference value 2.
Bit 31:24  Define the reference value 3
*/
#define CANXL_TX_REFVAL_0                                         (uint32)0x00000001UL
#define CANXL_TX_REFVAL_1                                         (uint32)0x00000003UL
#define CANXL_TX_REFVAL_2                                         (uint32)0x00000005UL /* STD 05 <==> Eth Frame */
#define CANXL_TX_REFVAL_3                                         (uint32)0x00000000UL

/* TX_PQ_STS0 */
/* Define the mask value to check the TX Priority Queue is not busy */
#define CANXL_TX_PQ_STS_MASK                                               (uint32)0xFFFFFFFFUL
/* Define value to confirm the TX Priority Queue is not busy */
#define CANXL_TX_PQ_NOT_BUSY                                               (uint32)0x00000000UL

/* TX_PQ_CTRL1 */
/* Define value to clear Abort bit */
#define CANXL_TX_PQ_CLEAR_ABORT                                            (uint32)0x00000000UL

/* TX_PQ_CTRL2 */
/* Define value to clear Enable bit */
#define CANXL_TX_PQ_CLEAR_ENABLE                                           (uint32)0x00000000UL

/* RX_FQ_STS0 */
/* Define the mask value to check the status of RX FIFO Queue*/
#define CANXL_RX_FQ_STS_MASK                                               (uint32)0x00FF00FFUL
/* Define the value to check the RX FIFO Queue is not busy */
#define CANXL_RX_FQ_NOT_BUSY                                               (uint32)0x00000000UL

/* RX_FQ_STS1 */
/* Define the value to check the RX FIFO Queue is not on hold */
#define CANXL_RX_FQ_NOT_ON_HOLD                                            (uint32)0x00000000UL

/* TX_FQ_CTRL1 */
/* Define value to clear Abort bit */
#define CANXL_TX_FQ_CLEAR_ABORT                                            (uint32)0x00000000UL
/* Define value to set Abort bit */
#define CANXL_TX_FQ_SET_ABORT                                              (uint32)0x000000FFUL

/* TX_FQ_CTRL2 */
/* Disable TX FIFO Queue */
#define CANXL_TX_FIFO_QUEUE_DISABLE                                        (uint32)0x00000000UL

/* TX_FQ_STS0 */
/* Define the mask value to check the status of TX FIFO Queue*/
#define CANXL_TX_FQ_STS_MASK                                               (uint32)0x00FF00FFUL
/* Define the value to check the TX FIFO Queue is not busy */
#define CANXL_TX_FQ_NOT_BUSY                                               (uint32)0x00000000UL

/* 1.7 IRC Interrupt Controller */
/* FUNC_ENA */
/* Enable all event to trigger the interrupt line FUNC_INT */
#define CANXL_IRC_FUNC_ENA_VALUE                                            (uint32)0x08000000UL

/* ERR_ENA */
/* Enable all event to trigger the interrupt line ERR_INT */
#define CANXL_IRC_ERR_ENA_VALUE                                             (uint32)0x10FF3FFFUL

/* SAFETY_ENA */
/* Enable all event to trigger the interrupt line SAFETY_INT */
#define CANXL_IRC_SAFETY_ENA_VALUE                                          (uint32)0x10FF3FFFUL

/* 1.5 PRT Protocol Controller */
/* MODE */
/* Setting Operation Mode for PRT */
/* MODE.FDOE = 1, MODE.XLOE = 1, MODE.XLTR = 0, MODE.EFDI = 0 */
#define CANXL_PRT_OPERATION_MODE                                            (uint32)0x03UL
/* Time stamp position */
/* MODE.SFS = 1: Timestamps captured at the start of a frame */
#define CANXL_PRT_TIME_STAMP                                                (uint32)0x0100UL

/* NBTP */
/* Setting bit rate Prescaler */
/* Range: 0x00 .. 0x1F */
#define CANXL_PRT_PRESCALER_VALUE                                           (uint32)(0x0UL << 25U)

/* Setting bit Nominal SJW */
/* Range: 0x00 .. 0x7F */
#define CANXL_PRT_NOMINAL_SJW_VALUE                                         (uint32)(0x01UL)

/* Setting bit Nominal Phase_Seg2 */
/* Range: 0x01 .. 0x7F */
#define CANXL_PRT_NOMINAL_NTSEG2_VALUE                                      (uint32)(0x27UL << 8U)

/* Setting bit Nominal Prop_Seg and Phase_Seg1 */
/* Valid values for NTSEG1 are 0x01-0x1FF */
/* This value defines the sum of Prop_Seg(N) and Phase_Seg1(N) */
#define CANXL_PRT_NOMINAL_NTSEG1_VALUE                                      (uint32)(0x76UL << 16U)

/* XBTP */
/* Setting XL data phase SJW */
/* Range: 0x00 .. 0x7F */
#define CANXL_PRT_XL_DATA_SJW_VALUE                                         (uint32)(0x01UL)

/* Setting XL data Phase_Seg2 */
/* Range: 0x01 .. 0x7F */
#define CANXL_PRT_XL_DATA_XTSEG2_VALUE                                      (uint32)(0x1UL << 8U)

/* Setting XL data phase Prop_Seg and Phase_Seg1 */
/* Valid values for XTSEG1 are 0x00 .. 0xFF */
/* This value defines the sum of Prop_Seg(X) and Phase_Seg1(X) */
#define CANXL_PRT_XL_DATA_XTSEG1_VALUE                                      (uint32)(0x6UL << 16U)

/* Transmitter Delay Compensation Offset for XL frames */
/* Valid values for the XL Transmitter Delay Compensation Offset XTDCO is 0x00-0xFF */
#define CANXL_PRT_XL_DATA_XTDCO_VALUE                                       (uint32)(0x64UL << 24U)

/***********************************************************************************************************************
**                                                    Baud-rate                                                       **
***********************************************************************************************************************/
/* NBTP - Arbitration Phase Nominal Bit Timing Register */
#define CAN_CANXL_NBTP_DEFAULT  0x00000000UL
#define CAN_CANXL_NSJW(x)       (((uint32)(x) - 1UL))
#define CAN_CANXL_NTSEG2(x)     (((uint32)(x) - 1UL) << 8UL)
#define CAN_CANXL_NTSEG1(x)     (((uint32)(x) - 1UL) << 16UL)
#define CAN_CANXL_NBRP(x)       (((uint32)(x)) << 25UL)

/* DBTP - CAN FD Data Phase Bit Timing Register */
#define CAN_CANXL_DBTP_DEFAULT  0x00000000UL
#define CAN_CANXL_FDSJW(x)      (((uint32)(x) - 1UL))
#define CAN_CANXL_FDTSEG2(x)    (((uint32)(x) - 1UL) << 8UL)
#define CAN_CANXL_FDTSEG1(x)    (((uint32)(x) - 1UL) << 16UL)
#define CAN_CANXL_FDDCO(x)      (((uint32)(x)) << 24UL)

/* XBTP - CAN XL Data Phase Bit Timing Register */
#define CAN_CANXL_XBTP_DEFAULT  0x00000000UL
#define CAN_CANXL_XLSJW(x)      (((uint32)(x) - 1UL))
#define CAN_CANXL_XLTSEG2(x)    (((uint32)(x) - 1UL) << 8UL)
#define CAN_CANXL_XLTSEG1(x)    (((uint32)(x) - 1UL) << 16UL)
#define CAN_CANXL_XLDCO(x)      (((uint32)(x)) << 24UL)

/* PCFG - CANXL PWME Configuration Registerr */
#define CAN_CANXL_PWMS(x)       ((uint32)(x))
#define CAN_CANXL_PWML(x)       ((uint32)(x) << 8UL)
#define CAN_CANXL_PWMO(x)       ((uint32)(x) << 16UL)



/***********************************************************************************************************************
**                                                    Type Definition                                                 **
***********************************************************************************************************************/
typedef struct STag_CanXL_TXFQRegType
{
  uint32 ulTXADDPT;                              /*  +0x000H + (0x010H x n) TX_FQ_ADD_PT[n]     */
  uint32 ulTXSTADD;                              /*  +0x004H + (0x010H x n) TX_FQ_START_ADD[n]  */
  uint32 ulTXSIZE;                               /*  +0x008H + (0x010H x n) TX_FQ_SIZE[n]       */
  uint32 aareserved;                             /*  +0x00CH + (0x010H x n) reserved            */
} CanXL_TXFQRegType;

typedef struct STag_CanXL_RXFQRegType
{
  uint32 ulRXADDPT;                              /*  +0x000H + (0x018H x n) RX_FQ_ADD_PT[n]       */
  uint32 ulRXSTADD;                              /*  +0x004H + (0x018H x n) RX_FQ_START_ADD[n]    */
  uint32 ulRXSIZE;                               /*  +0x008H + (0x018H x n) RX_FQ_SIZE[n]         */
  uint32 ulRXDCSTADD;                            /*  +0x00CH + (0x018H x n) RX_FQ_DC_START_ADD[n] */
  uint32 ulRXRDADDPT;                            /*  +0x010H + (0x018H x n) RX_FQ_RD_ADD_PT[n]    */
  uint32 aareserved;                             /*  +0x01CH + (0x018H x n) reserved              */
} CanXL_RXFQRegType;

typedef struct STag_CanXL_MHRegType                                                                                     /* PRQA S 3630 # JV-01 */
{
  /* MH global control and status registers */
  uint32 ulVERSION;                                  /*  +0x000H VERSION           */
  uint32 ulCTRL;                                     /*  +0x004H MH_CTRL           */
  uint32 ulCFG;                                      /*  +0x008H MH_CFG            */
  uint32 ulSTS;                                      /*  +0x00CH MH_STS            */
  uint32 ulSFTYCFG;                                  /*  +0x010H MH_SFTY_CFG       */
  uint32 ulSFTYCTRL;                                 /*  +0x014H MH_SFTY_CTRL      */
  uint32 ulRXFADD;                                   /*  +0x018H RX_FILTER_MEM_ADD */
  uint32 ulTXDADD;                                   /*  +0x01CH TX_DESC_MEM_ADD   */
  uint32 ulAXIADD;                                   /*  +0x020H AXI_ADD_EXT       */
  uint32 ulAXIPAR;                                   /*  +0x024H AXI_PARAMS        */
  uint32 ulLOCK;                                     /*  +0x028H AXI_PARAMS        */
  uint32 aaReserved0[53];                            /*  +0x02CH reserved          */

  /* TX FIFO Queues control and status registers */
  uint32 ulTXDPT;                                    /*  +0x100H TX_DESC_ADD_PT   */
  uint32 ulTXSTAT;                                   /*  +0x104H TX_STATISTICS    */
  uint32 ulTXFQSTS0;                                 /*  +0x108H TX_FQ_STS0       */
  uint32 ulTXFQSTS1;                                 /*  +0x10CH TX_FQ_STS1       */
  uint32 ulTXFQCTRL0;                                /*  +0x110H TX_FQ_CTRL0      */
  uint32 ulTXFQCTRL1;                                /*  +0x114H TX_FQ_CTRL1      */
  uint32 ulTXFQCTRL2;                                /*  +0x118H TX_FQ_CTRL2      */
  uint32 aaReserved1;                                /*  +0x11CH reserved         */
  CanXL_TXFQRegType aaTXFQReg[8];                    /*  +0x120H                  */
  uint32 aaReserved2[88];                            /*  +0x1A0H reserved         */

  /* TX Priority Queue control and status registers */
  uint32 ulTXPQSTS0;                                 /*  +0x300H TX_PQ_STS0       */
  uint32 ulTXPQSTS1;                                 /*  +0x304H TX_PQ_STS1       */
  uint32 aaReserved3;                                /*  +0x308H reserved         */
  uint32 ulTXPQCTRL0;                                /*  +0x30CH TX_PQ_CTRL0      */
  uint32 ulTXPQCTRL1;                                /*  +0x310H TX_PQ_CTRL1      */
  uint32 ulTXPQCTRL2;                                /*  +0x314H TX_PQ_CTRL2      */
  uint32 ulTXPQSTADD;                                /*  +0x318H TX_PQ_START_ADD  */
  uint32 aaReserved4[57];                            /*  +0x31CH reserved         */

  /* RX FIFO Queues control and status registers */
  uint32 ulRXDPT;                                    /*  +0x400H RX_DESC_ADD_PT   */
  uint32 ulRXSTAT;                                   /*  +0x404H RX_STATISTICS    */
  uint32 ulRXFQSTS0;                                 /*  +0x408H RX_FQ_STS0       */
  uint32 ulRXFQSTS1;                                 /*  +0x40CH RX_FQ_STS1       */
  uint32 ulRXFQSTS2;                                 /*  +0x410H RX_FQ_STS2       */
  uint32 ulRXFQCTRL0;                                /*  +0x414H RX_FQ_CTRL0      */
  uint32 ulRXFQCTRL1;                                /*  +0x418H RX_FQ_CTRL1      */
  uint32 ulRXFQCTRL2;                                /*  +0x41CH RX_FQ_CTRL2      */
  CanXL_RXFQRegType aaRXFQReg[8];                    /*  +0x420H                  */
  uint32 aaReserved5[72];                            /*  +0x4E0H reserved         */

  /* TX/RX filter control registers */
  uint32 ulTXFTCTRL0;                                /*  +0x600H TX_FILTER_CTRL0  */
  uint32 ulTXFTCTRL1;                                /*  +0x604H TX_FILTER_CTRL1  */
  uint32 ulTXFTREF0;                                 /*  +0x608H TX_FILTER_REFVAL0*/
  uint32 ulTXFTREF1;                                 /*  +0x60CH TX_FILTER_REFVAL1*/
  uint32 ulTXFTREF2;                                 /*  +0x610H TX_FILTER_REFVAL2*/
  uint32 ulTXFTREF3;                                 /*  +0x614H TX_FILTER_REFVAL3*/
  uint32 aaReserved6[26];                            /*  +0x618H reserved         */
  uint32 ulRXFTCTRL0;                                /*  +0x680H RX_FILTER_CTRL   */
  uint32 aaReserved7[31];                            /*  +0x684H reserved         */

  /* Interrupts control and status registers */
  uint32 ulTXFQINSTS;                                /*  +0x700H TX_FQ_INT_STS    */
  uint32 ulRXFQINSTS;                                /*  +0x704H RX_FQ_INT_STS    */
  uint32 ulTXPQINSTS0;                               /*  +0x708H TX_PQ_INT_STS0   */
  uint32 ulTXPQINSTS1;                               /*  +0x70CH TX_PQ_INT_STS1   */
  uint32 ulSTATINSTS;                                /*  +0x710H STATS_INT_STS    */
  uint32 ulERRINSTS;                                 /*  +0x714H ERR_INT_STS      */
  uint32 ulSFTYINSTS;                                /*  +0x718H SFTY_INT_STS     */
  uint32 ulAXIERR;                                   /*  +0x71CH AXI_ERR_INFO     */
  uint32 ulDESERR0;                                  /*  +0x720H DESC_ERR_INFO0   */
  uint32 ulDESERR1;                                  /*  +0x724H DESC_ERR_INFO1   */
  uint32 ulTXFTERR;                                  /*  +0x728H TX_FILTER_ERR_INFO */
  uint32 aaReserved8[53];                            /*  +0x72CH reserved         */

  /* Integration/Debug control and status registers */
  uint32 ulDEBUCTRL;                                 /*  +0x800H DEBUG_TEST_CTRL  */
  uint32 ulINTEST0;                                  /*  +0x804H INT_TEST0        */
  uint32 ulINTEST1;                                  /*  +0x808H INT_TEST1        */
  uint32 aaReserved9;                                /*  +0x80CH reserved         */
  uint32 ulTXSCANFC;                                 /*  +0x810H TX_SCAN_FC       */
  uint32 ulTXSCANBC;                                 /*  +0x814H TX_SCAN_BC       */
  uint32 ulTXFQDESVAl;                               /*  +0x818H TX_FQ_DESC_VALID */
  uint32 ulTXPQDESVAl;                               /*  +0x81CH TX_PQ_DESC_VALID */
  uint32 aaReserved10[24];                            /*  +0x820H reserved         */

  /* CRC control registers */
  uint32 ulCRCCTRL;                                  /*  +0x880H CRC_CTRL         */
  uint32 ulCRCREG;                                   /*  +0x884H CRC_REG          */
} CanXL_MHRegType;


typedef struct STag_CanXL_PRTRegType                                                                                    /* PRQA S 3630 # JV-01 */
{
  /* Status information of the PRT */
  uint32 ulENDN;                                     /*  +0x000H EDNN        */
  uint32 ulPREL;                                     /*  +0x004H PREL        */
  uint32 ulSTAT;                                     /*  +0x008H STAT        */
  uint32 aaReserved1[5];                             /*  +0x00CH reserved    */

  /* Event information of the PRT */
  uint32 ulEVNT;                                     /*  +0x020H EVNT        */
  uint32 aaReserved2[7];                             /*  +0x024H reserved    */

  /* Control of the PRT during runtime */
  uint32 ulLOCK;                                     /*  +0x040H LOCK        */
  uint32 ulCTRL;                                     /*  +0x044H CTRL        */
  uint32 ulFIMC;                                     /*  +0x048H FIMC        */
  uint32 ulTEST;                                     /*  +0x04CH TESt        */
  uint32 aaReserved3[4];                             /*  +0x050H reserved    */

 /* Configuration of the PRT before runtime */
  uint32 ulMODE;                                     /*  +0x060H MODE        */
  uint32 ulNBTP;                                     /*  +0x064H NBTP        */
  uint32 ulDBTP;                                     /*  +0x068H DBTP        */
  uint32 ulXBTP;                                     /*  +0x06CH XBTP        */
  uint32 ulPCFG;                                     /*  +0x070H PCFG        */
} CanXL_PRTRegType;


typedef struct STag_CanXL_IRCRegType                                                                                    /* PRQA S 3630 # JV-01 */
{
  /* MH and PRT capture event registers */
  uint32 ulFUNCRAW;                                   /*  +0x000H FUNC_RAW       */
  uint32 ulERRRAW;                                    /*  +0x004H ERR_RAW        */
  uint32 ulSFTYRAW;                                   /*  +0x008H SAFETY_RAW     */
  uint32 aaReserved1;                                 /*  +0x00CH reserved       */

  /* IRC control register */
  uint32 ulFUNCCLR;                                   /*  +0x010H FUNC_CLR       */
  uint32 ulERRCLR;                                    /*  +0x014H ERR_CLR        */
  uint32 ulSFTYCLR;                                   /*  +0x018H SAFETY_CLR     */
  uint32 aaReserved2;                                 /*  +0x01CH reserved       */
  uint32 ulFUNCENA;                                   /*  +0x020H FUNC_ENA       */
  uint32 ulERRENA;                                    /*  +0x024H ERR_ENA        */
  uint32 ulSFTYENA;                                   /*  +0x028H SAFETY_ENA     */
  uint32 aaReserved3;                                 /*  +0x02CH reserved       */

  /* Hardware configuration of the IRC */
  uint32 ulCAPMODE;                                   /*  +0x030H CAPTURING_MODE  */
  uint32 aaReserved4[3];                              /*  +0x034H reserved        */
  uint32 ulHDP;                                       /*  +0x040H CTRL            */
} CanXL_IRCRegType;

typedef struct STag_CanXL_GLBRegType                                                                                    /* PRQA S 3630 # JV-01 */
{
  uint32 ulCXLGIPV;                                   /*  +0x000H Global IP Version Register         */
  uint32 reserved1;                                   /*  +0x004H reserved                           */
  uint32 ulCXLGSTS;                                   /*  +0x008H Global Status Register             */
  uint32 reserved2;                                   /*  +0x00CH reserved                           */
  uint32 ulCXLGGPT;                                   /*  +0x010H Global General Port Register       */
  uint32 reserved3[27];                               /*  +0x014H reserved                           */
  uint32 ulCXLGRSTC;                                  /*  +0x080H Global Reset Control Register      */
  uint32 ulCXLGRESPC;                                 /*  +0x084H Global RESPConfiguration Register  */
  uint32 ulCXLGLRAPC;                                 /*  +0x088H Global LRAM Read Access Priority
                                                                  Configuration Register             */
  uint32 reserved4[29];                               /*  +0x08CH reserved                           */
  uint32 ulCXLCCLKC;                                  /*  +0x100H Clock Control Register             */
} CanXL_GLBRegType;

#endif /* #ifndef CAN_XL_REG_STRUCUTURE_H */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
