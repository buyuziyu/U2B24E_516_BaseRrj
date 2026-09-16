/*====================================================================================================================*/
/* Project      = RH850/X2x MCAL PF Development                                                                       */
/* Module       = Can_RegStruct.h                                                                                     */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2024, 2025 Renesas Electronics Corporation. All rights reserved.                                               */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Provision of Controller register structure.                                                                        */
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
**                                                  Revision History                                                  **
***********************************************************************************************************************/
/*
 * 2.4.1: 30/06/2025  : Remove the SW-VERSION from header of file
 * 2.3.1: 31/03/2025  : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 * 2.2.0: 31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 * 2.1.2: 31/10/2024  : As part of CANXL driver support, following changes are made:
 *                      1. Add macro CAN_RSCAN_CHMDC_KEEP
 * 2.1.1: 15/07/2024  : As part of CANXL driver support, following changes are made:
 *                      1. Add macro CAN_INTMUXSEL_INTERRUPT_FUNCTION, CANINTMUXSELn_BASE, CANINTMUXSEL0_VALUE
 *                      CANINTMUXSEL1_VALUE, CANINTMUXSEL2_VALUE, CANINTMUXSELn_DEFAULT
 *                      2. Add struct Can_IntMuxSelRegType
 *        10/05/2024  : Initial version.
 */
/**********************************************************************************************************************/
#ifndef CAN_REGSTRUCT_H
#define CAN_REGSTRUCT_H

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/

/* AUTOSAR release version information */
#define CAN_REGSTRUCT_AR_RELEASE_MAJOR_VERSION    CAN_AR_RELEASE_MAJOR_VERSION
#define CAN_REGSTRUCT_AR_RELEASE_MINOR_VERSION    CAN_AR_RELEASE_MINOR_VERSION
#define CAN_REGSTRUCT_AR_RELEASE_REVISION_VERSION CAN_AR_RELEASE_REVISION_VERSION

/* File version information */
#define CAN_REGSTRUCT_SW_MAJOR_VERSION            CAN_SW_MAJOR_VERSION
#define CAN_REGSTRUCT_SW_MINOR_VERSION            CAN_SW_MINOR_VERSION

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:3630)    : The implementation of this struct/union type should be hidden.                               */
/* Rule                : MISRA C:2012 Dir-4.8                                                                         */
/* JV-01 Justification : This is accepted. Redundant of struct or union type has no affect to driver operation.       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0750)    : A union type specifier has been defined.                                                     */
/* Rule                : MISRA C:2012 Rule-19.2, CWE Rule CWE-843                                                     */
/* JV-01 Justification : This union type is used for register accessing and there is no issue with this usage.        */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3472)    : All toplevel uses of this function-like macro look like they could be replaced by            */
/*                       equivalent function calls.                                                                   */
/* Rule                : MISRA C:2012 Dir-4.9                                                                         */
/* JV-01 Justification : This message indicates that a candidate macro may be suitable for replacement by a           */
/*                       function, based on an actual call-site and the arguments passed to it there                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/

/* Filter controller register support */
#define CAN_FILTER_CONTROL_SUPPORT

/* Support common FIFO enhancement register */
#define CAN_COMFIFO_ENHANCEMENT_SUPPORT

/* Location of interface mode selection bit */
#define CAN_INTERFACE_MODE_SELECTION_LOCATION CAN_FDCFG_REG

/* Location of label data field */
#define CAN_LABEL_DATA_LOCATION               CAN_CTR_REG

/* Create a word data from four byte data */
#define CAN_RSCAN_CREATEWORD(byte0, byte1, byte2, byte3)                                                                /* PRQA S 3472 # JV-01 */\
  ((uint32)(byte0) | ((uint32)(byte1) << 8UL) | ((uint32)(byte2) << 16UL) | ((uint32)(byte3) << 24UL))

/* Number of Tx History List entries per controller */
#define CAN_RSCAN_THL_ENTRIES_PER_CH 32UL

/* Number of tx buffers per controller */
#define CAN_RSCAN_TXBUFFER_PER_CH    64UL

/* Number of RxFIFO per unit */
#define CAN_RSCAN_RXFIFO_PER_UNIT    8UL

/* Number of TxRxFIFO per controller */
#define CAN_RSCAN_TXRXFIFO_PER_CH    3UL

/* Number of TxQUEUE per controller */
#define CAN_RSCAN_TXQUEUE_PER_CH     4UL

/* Number queue depth reserved*/
#define CAN_RSCAN_TXQUEUE_RESERVED     32UL

/* Max depth of TxQUEUE */
#define CAN_RSCAN_TXQUEUE_MAX_DEPTH  16UL

/* Number of CFDRMNDt per unit */
#define CAN_RSCAN_MAX_RMND_PER_UNIT  4UL            

/* Macro of ored interrupt function feature  */
#define CAN_ORED_INTERRUPT_FUNCTION    STD_OFF

/* Macro of CAN Interrupt Select Register feature  */
#define CAN_INTMUXSEL_INTERRUPT_FUNCTION    STD_ON

/* Max controller per unit*/
#define CAN_MAX_CHANNEL_PER_UNIT  8U

/* Get number of FIFO Buffer Depth (number of messages) */

#define CAN_RSCAN_FIFO_BUFFER_DEPTH_GET(x) \
  (uint8)(((uint8)(x) == 1U) ? 4U   : \
         (((uint8)(x) == 2U) ? 8U   : \
         (((uint8)(x) == 3U) ? 16U  : \
         (((uint8)(x) == 4U) ? 32U  : \
         (((uint8)(x) == 5U) ? 48U  : \
         (((uint8)(x) == 6U) ? 64U  : \
         (((uint8)(x) == 7U) ? 128U : 0U )))))))


/* Get number of TX Queue Depth (number of messages) */
#define CAN_RSCAN_TX_QUEUE_DEPTH_GET(x) (((uint32)(x) > 1UL) ? ((uint32)(x) + 1UL) : ((uint32)(x)))                     /* PRQA S 3472 # JV-01 */

/* INTSEL */
#define CANINTMUXSELn_BASE              0xFF09081C
// CAN10(Mux0), CAN11(Mux1), CAN12(Mux2), CAN13(Mux3)
#define CANINTMUXSEL0_VALUE             0x038D030BUL
// CAN14(Mux4), CAN15(Mux5), CAN16(Mux6), CAN17(Mux7)
#define CANINTMUXSEL1_VALUE             0x0491040FUL
// CAN18(Mux8), CAN19(Mux9)
#define CANINTMUXSEL2_VALUE             0x00000513UL
#define CANINTMUXSELn_DEFAULT           0UL

/* GCFG */
#define CAN_RSCAN_GCFG_DEFAULT          0x00000000UL
#define CAN_RSCAN_ITRCP(x)              ((uint32)(x) << 16UL)
#define CAN_RSCAN_CMPOC                 0x00000020UL
#define CAN_RSCAN_DCS                   0x00000010UL
#define CAN_RSCAN_MME                   0x00000008UL
#define CAN_RSCAN_DCE                   0x00000002UL
#define CAN_RSCAN_TPRI                  0x00000001UL

/* GFDCFG */
#define CAN_RSCAN_GFDCFG_DEFAULT        0x00000000UL

/* GCTR */
#define CAN_RSCAN_GSLPR                 0x00000004UL
#define CAN_RSCAN_GMDC_MASK             0x00000003UL
#define CAN_RSCAN_GMDC_OP               0x00000000UL
#define CAN_RSCAN_GMDC_RESET            0x00000001UL

/* GSTS */
#define CAN_RSCAN_GRAMINIT              0x00000008UL
#define CAN_RSCAN_GSTSMASK              0x00000007UL
#define CAN_RSCAN_GSLPSTS               0x00000004UL
#define CAN_RSCAN_GRSTSTS               0x00000001UL
#define CAN_RSCAN_GOPSTS                0x00000000UL

/* GAFLCFGw */
#define CAN_RSCAN_GAFLCFG_DEFAULT       0x00000000UL

/* GAFLECTR */
#define CAN_RSCAN_RULES_PER_PAGE        16UL        
#define CAN_RSCAN_AFLDAE                0x00000100UL
#define CAN_RSCAN_AFLPN(x)              ((uint32)(x))                                                                   /* PRQA S 3472 # JV-01 */
#define CAN_RSCAN_AFLDAE_OFF            0x00000000UL

/* GAFLIDj */
#define CAN_RSCAN_GAFLID_DEFAULT        0x00000000UL

/* GAFLMj */
#define CAN_RSCAN_GAFLM_DEFAULT         0x00000000UL

/* GAFLP0_j */
#define CAN_RSCAN_GAFLP0_DEFAULT        0x00000000UL
#define CAN_RSCAN_GAFLP_PAGE0           0U          
#define CAN_RSCAN_GAFLP_PAGE1           1U          
#define CAN_RSCAN_GAFLDLC_0             0x00000000UL
#define CAN_RSCAN_GAFLDLC_1             0x00000001UL
#define CAN_RSCAN_GAFLDLC_2             0x00000002UL
#define CAN_RSCAN_GAFLDLC_3             0x00000003UL
#define CAN_RSCAN_GAFLDLC_4             0x00000004UL
#define CAN_RSCAN_GAFLDLC_5             0x00000005UL
#define CAN_RSCAN_GAFLDLC_6             0x00000006UL
#define CAN_RSCAN_GAFLDLC_7             0x00000007UL
#define CAN_RSCAN_GAFLDLC_8             0x00000008UL
#define CAN_RSCAN_GAFLDLC_12            0x00000009UL
#define CAN_RSCAN_GAFLDLC_16            0x0000000AUL
#define CAN_RSCAN_GAFLDLC_20            0x0000000BUL
#define CAN_RSCAN_GAFLDLC_24            0x0000000CUL
#define CAN_RSCAN_GAFLDLC_32            0x0000000DUL
#define CAN_RSCAN_GAFLDLC_48            0x0000000EUL
#define CAN_RSCAN_GAFLDLC_64            0x0000000FUL
#define CAN_RSCAN_GAFLSRD_0             0x00000010UL
#define CAN_RSCAN_GAFLSRD_1             0x00000020UL
#define CAN_RSCAN_GAFLSRD_2             0x00000040UL
#define CAN_RSCAN_GAFLRMV               0x00008000UL
#define CAN_RSCAN_GAFLRMDP(x)           (uint32)((uint32)(x) << 8U)

/* GAFLP1_j */
#define CAN_RSCAN_GAFLP1_DEFAULT        0x00000000UL
#define CAN_RSCAN_GAFLFDP_TXRXFIFO(x)   (0x100UL << (uint32)(x))
#define CAN_RSCAN_GAFLFDP_RXFIFO(x)     (1UL << (uint32)(x))
#define CAN_RSCAN_GAFLFDP_TXQUEUE(x)    (0x100UL << (uint32)(((((uint32)(x)) / 4UL) * 3UL) + (((uint32)(x)) % 4UL)))

/* RFCCx */
#define CAN_RSCAN_RFCC_DEFAULT          0x00000000UL
#define CAN_RSCAN_RFPLS_GET(x)          (((uint32)(x) >> 4UL) & 0x7UL)                                                  /* PRQA S 3472 # JV-01 */
#define CAN_RSCAN_RFIE_GET(x)           (((uint32)(x) >> 1UL) & 1UL)                                                    /* PRQA S 3472 # JV-01 */
#define CAN_RSCAN_RFDC_GET(x)           (((uint32)(x) >> 8UL) & 0x7UL)                                                  /* PRQA S 3472 # JV-01 */
#define CAN_RSCAN_RFFIE                 0x00010000UL
#define CAN_RSCAN_RFIGCV_1_8            0x00000000UL
#define CAN_RSCAN_RFIGCV_2_8            0x00002000UL
#define CAN_RSCAN_RFIGCV_3_8            0x00004000UL
#define CAN_RSCAN_RFIGCV_4_8            0x00006000UL
#define CAN_RSCAN_RFIGCV_5_8            0x00008000UL
#define CAN_RSCAN_RFIGCV_6_8            0x0000A000UL
#define CAN_RSCAN_RFIGCV_7_8            0x0000C000UL
#define CAN_RSCAN_RFIGCV_8_8            0x0000E000UL
#define CAN_RSCAN_RFIM                  0x00001000UL
#define CAN_RSCAN_RFDC_0                0x00000000UL
#define CAN_RSCAN_RFDC_4                0x00000100UL
#define CAN_RSCAN_RFDC_8                0x00000200UL
#define CAN_RSCAN_RFDC_16               0x00000300UL
#define CAN_RSCAN_RFDC_32               0x00000400UL
#define CAN_RSCAN_RFDC_48               0x00000500UL
#define CAN_RSCAN_RFDC_64               0x00000600UL
#define CAN_RSCAN_RFDC_128              0x00000700UL
#define CAN_RSCAN_RFPLS_8               0x00000000UL
#define CAN_RSCAN_RFPLS_12              0x00000010UL
#define CAN_RSCAN_RFPLS_16              0x00000020UL
#define CAN_RSCAN_RFPLS_20              0x00000030UL
#define CAN_RSCAN_RFPLS_24              0x00000040UL
#define CAN_RSCAN_RFPLS_32              0x00000050UL
#define CAN_RSCAN_RFPLS_48              0x00000060UL
#define CAN_RSCAN_RFPLS_64              0x00000070UL
#define CAN_RSCAN_RFIE                  0x00000002UL
#define CAN_RSCAN_RFE                   0x00000001UL

/* RFSTSx */
#define CAN_RSCAN_RFIF_GET(x)           (((uint32)(x) >> 3UL) & 1UL)                                                    /* PRQA S 3472 # JV-01 */
#define CAN_RSCAN_RFEMP                 0x00000001UL
#define CAN_RSCAN_CLEAR_RFIF            0x0001FF07UL
#define CAN_RSCAN_CLEAR_RFMLT           0x0001FF0BUL

/* CmCFG */
#define CAN_RSCAN_CFG_DEFAULT           0x00000000UL

/* CFDCmDCFG */
#define CAN_RSCAN_DCFG_DEFAULT          0x00000000UL
#define CAN_RSCAN_SJW(x)                (((uint32)(x)-1UL) << 24UL)
#define CAN_RSCAN_TSEG2(x)              (((uint32)(x)-1UL) << 16UL)
#define CAN_RSCAN_TSEG1(x)              (((uint32)(x)-1UL) << 8UL)
#define CAN_RSCAN_BRP(x)                ((uint32)(x))

/* CFDCmNCFG */
#define CAN_RSCAN_NTSEG2(x)             (((uint32)(x)-1UL) << 25UL)
#define CAN_RSCAN_NTSEG1(x)             (((uint32)(x)-1UL) << 17UL)
#define CAN_RSCAN_NSJW(x)               (((uint32)(x)-1UL) << 10UL)
#define CAN_RSCAN_NBRP(x)               ((uint32)(x))

/* CmCTR */
#define CAN_RSCAN_CTR_DEFAULT           0x00000005UL
#define CAN_RSCAN_GET_EIEBITS(x)        (((uint32)(x) >> 8UL) & 0xFFUL)                                                 /* PRQA S 3472 # JV-01 */
#define CAN_RSCAN_BOM_HALT_BUSOFF_ENTRY 0x00200000UL
#define CAN_RSCAN_BORIE                 0x00001000UL
#define CAN_RSCAN_BOEIE                 0x00000800UL
#define CAN_RSCAN_CHMDC_MASK            0x00000007UL
#define CAN_RSCAN_CSLPR                 0x00000004UL
#define CAN_RSCAN_CHMDC_COM             0x00000000UL
#define CAN_RSCAN_CHMDC_RESET           0x00000001UL
#define CAN_RSCAN_CHMDC_HALT            0x00000002UL
#define CAN_RSCAN_BUS_ERROR_ENABLE      0x0080E500UL
#define CAN_RSCAN_CHMDC_KEEP            0x00000003UL

/* CmSTS */
#define CAN_RSCAN_BOSTS                 0x00000010UL
#define CAN_RSCAN_EPSTS                 0x00000008UL
#define CAN_RSCAN_CSTSMASK              0x00000007UL
#define CAN_RSCAN_CSLPSTS               0x00000004UL
#define CAN_RSCAN_CHLTSTS               0x00000002UL
#define CAN_RSCAN_CRSTSTS               0x00000001UL
#define CAN_RSCAN_COPSTS                0x00000000UL
#define CAN_RSCAN_TEC_MASK              0xFF000000UL
#define CAN_RSCAN_TEC_OFFSET            24U
#define CAN_RSCAN_REC_MASK              0x00FF0000UL
#define CAN_RSCAN_REC_OFFSET            16U

/* CmERFL */
#define CAN_RSCAN_GET_EFBITS(x)         ((uint32)(x)&0xFFUL)                                                            /* PRQA S 3472 # JV-01 */
#define CAN_RSCAN_BEF                   0x00000001UL
#define CAN_RSCAN_EWF                   0x00000002UL
#define CAN_RSCAN_EPF                   0x00000004UL
#define CAN_RSCAN_BOEF                  0x00000008UL
#define CAN_RSCAN_BORF                  0x00000010UL
#define CAN_RSCAN_ERFL_CLEAR            0x00000000UL
#define CAN_RSCAN_BIT_ERROR_POS(x)      (uint8)((uint8)(x) + 5UL)
#define CAN_RSCAN_CHECK_BIT_SET         0x00000001UL
#define CAN_RSCAN_NUM_OF_BUS_ERROR      10U         

/* CmFDCFG */
#define CAN_RSCAN_FDCFG_DEFAULT         0x00000000UL
#define CAN_RSCAN_CLOE                  0x40000000UL
#define CAN_RSCAN_FDOE                  0x10000000UL
#define CAN_RSCAN_GWBRS                 0x04000000UL
#define CAN_RSCAN_GWFDF                 0x02000000UL
#define CAN_RSCAN_GWEN                  0x01000000UL
#define CAN_RSCAN_TDCO(x)               ((uint32)(x) << 16UL)
#define CAN_RSCAN_TDCE                  0x00000200UL

/* THLCCm */
#define CAN_RSCAN_THLCC_DEFAULT         0x00000000UL
#define CAN_RSCAN_THLDTE                0x00000400UL
#define CAN_RSCAN_THLIM                 0x00000200UL
#define CAN_RSCAN_THLIE                 0x00000100UL
#define CAN_RSCAN_THLE                  0x00000001UL

/* THLSTSm */
#define CAN_RSCAN_THLEMP                0x00000001UL
#define CAN_RSCAN_CLEAR_THLIF           0x00003F07UL
#define CAN_RSCAN_CLEAR_THLELT          0x00003F0BUL
#define CAN_RSCAN_THLEFT                0x00000004UL

/* THLACC0m */
#define CAN_RSCAN_BN_GET(x)             (uint32)(((uint32)(x) >> 3UL) & 0x7FUL)
#define CAN_RSCAN_BT_GET(x)             (uint32)((uint32)(x)&0x07UL)
#define CAN_RSCAN_BT_TXRXFIFO           0x00000002UL
#define CAN_RSCAN_BT_TXQUEUE            0x00000004UL

/* THLACC1m */
#define CAN_RSCAN_TID_GET(x)            (uint32)((uint32)(x)&0xFFFFUL)

/* THLPCTRm */
#define CAN_RSCAN_THLPC_NEXT            0x000000FFUL

/* TMPTRp, CFPTRk */
#define CAN_RSCAN_XXDLC(x)              (uint32)((uint32)(x) << 28UL)
#define CAN_RSCAN_XXDLC_GET(x)          (uint32)((uint32)(x) >> 28UL)
#define CAN_RSCAN_XXPTR(x)              (uint32)((uint32)(x) << 16UL)

/* TMFDCTR, CFFDCSTS, RFFDSTS, RMFDSTS */
#define CAN_RSCAN_XXFDF                 0x00000004UL
#define CAN_RSCAN_XXBRS                 0x00000002UL

/* TMCp */
#define CAN_RSCAN_TMTR                  (uint8)0x01U

/* TMSTSp */
#define CAN_RSCAN_TMTRM                 (uint8)0x08U
#define CAN_RSCAN_TMTRF_NO              (uint8)0x00U

/* TMIECy */
#define CAN_RSCAN_TMIEC_DEFAULT         0x00000000UL

/* TMIDp, CFIDk */
#define CAN_RSCAN_THLEN                 0x20000000UL

/* CFPCTRk */
#define CAN_RSCAN_CFPC_NEXT             0x000000FFUL

/* CFCCk */
#define CAN_RSCAN_CFCC_DEFAULT          0x00000000UL
#define CAN_RSCAN_CFITT(x)              (uint32)((uint32)(x) << 24U)
#define CAN_RSCAN_CFTML(x)              (uint32)(((uint32)(x)&0x1FUL) << 16UL)
#define CAN_RSCAN_CFTML_GET(x)          ((((uint32)(x) >> 16UL) & 0x1FUL) | 0x20UL)                                     /* PRQA S 3472 # JV-01 */
#define CAN_RSCAN_CFPLS_GET(x)          (((uint32)(x) >> 4UL) & 0x7UL)                                                  /* PRQA S 3472 # JV-01 */
#define CAN_RSCAN_CFRXIE_GET(x)         (((uint32)(x) >> 1UL) & 1UL)                                                    /* PRQA S 3472 # JV-01 */
#define CAN_RSCAN_CFDC_GET(x)           (((uint32)(x) >> 21UL) & 0x7UL)                                                 /* PRQA S 3472 # JV-01 */
#define CAN_RSCAN_CFDC_0                0x00000000UL
#define CAN_RSCAN_CFDC_4                0x00200000UL
#define CAN_RSCAN_CFDC_8                0x00400000UL
#define CAN_RSCAN_CFDC_16               0x00600000UL
#define CAN_RSCAN_CFDC_32               0x00800000UL
#define CAN_RSCAN_CFDC_48               0x00A00000UL
#define CAN_RSCAN_CFDC_64               0x00C00000UL
#define CAN_RSCAN_CFDC_128              0x00E00000UL
#define CAN_RSCAN_CFIGCV_1_8            0x00000000UL
#define CAN_RSCAN_CFIGCV_2_8            0x00002000UL
#define CAN_RSCAN_CFIGCV_3_8            0x00004000UL
#define CAN_RSCAN_CFIGCV_4_8            0x00006000UL
#define CAN_RSCAN_CFIGCV_5_8            0x00008000UL
#define CAN_RSCAN_CFIGCV_6_8            0x0000A000UL
#define CAN_RSCAN_CFIGCV_7_8            0x0000C000UL
#define CAN_RSCAN_CFIGCV_8_8            0x0000E000UL
#define CAN_RSCAN_CFIM                  0x00001000UL
#define CAN_RSCAN_CFM_RX                0x00000000UL
#define CAN_RSCAN_CFM_TX                0x00000100UL
#define CAN_RSCAN_CFM_GW                0x00000200UL
#define CAN_RSCAN_CFPLS_8               0x00000000UL
#define CAN_RSCAN_CFPLS_12              0x00000010UL
#define CAN_RSCAN_CFPLS_16              0x00000020UL
#define CAN_RSCAN_CFPLS_20              0x00000030UL
#define CAN_RSCAN_CFPLS_24              0x00000040UL
#define CAN_RSCAN_CFPLS_32              0x00000050UL
#define CAN_RSCAN_CFPLS_48              0x00000060UL
#define CAN_RSCAN_CFPLS_64              0x00000070UL
#define CAN_RSCAN_CFTXIE                0x00000004UL
#define CAN_RSCAN_CFRXIE                0x00000002UL
#define CAN_RSCAN_CFE                   0x00000001UL

/* CFCCEk */
#define CAN_RSCAN_CFCCE_DEFAULT         0x00000000UL
#define CAN_RSCAN_CFMOWM                0x00000100UL

/* CFSTSk */
#define CAN_RSCAN_CFRXIF_GET(x)         (((uint32)(x) >> 3UL) & 1UL)                                                    /* PRQA S 3472 # JV-01 */
#define CAN_RSCAN_CFMLT                 0x00000004UL
#define CAN_RSCAN_CFFLL                 0x00000002UL
#define CAN_RSCAN_CFEMP                 0x00000001UL
#define CAN_RSCAN_CLEAR_CFTXIF          0x0107FF0FUL
#define CAN_RSCAN_CLEAR_CFRXIF          0x0107FF17UL
#define CAN_RSCAN_CLEAR_CFMLT           0x0107FF1BUL

/* TXQPCTRm */
#define CAN_RSCAN_TXQPC_NEXT            0x000000FFUL

/* TXQCC0m, TXQCC1m, TXQCC2m, TXQCC3m */
#define CAN_RSCAN_TXQCC_DEFAULT         0x00000000UL
#define CAN_RSCAN_TXQDC(x)              (uint32)((uint32)(x) << 8UL)
#define CAN_RSCAN_TXQDC_GET(x)          (((uint32)(x)&0x1F00UL) >> 8UL)                                                 /* PRQA S 3472 # JV-01 */
#define CAN_RSCAN_TXQIM                 0x00000080UL
#define CAN_RSCAN_TXQTXIE               0x00000020UL
#define CAN_RSCAN_TXQOWE                0x00000004UL
#define CAN_RSCAN_TXQGWE                0x00000002UL
#define CAN_RSCAN_TXQE                  0x00000001UL

/* TXQSTS0m, TXQSTS1m, TXQSTS2m, TXQSTS3m */
#define CAN_RSCAN_TXQFIF_GET(x)         (((uint32)(x) >> 16UL) & 1UL)
#define CAN_RSCAN_TXQMOW                0x00100000UL
#define CAN_RSCAN_TXQMLT                0x00080000UL
#define CAN_RSCAN_TXQOFTXIF             0x00040000UL
#define CAN_RSCAN_TXQOFRXIF             0x00020000UL
#define CAN_RSCAN_TXQFIF                0x00010000UL
#define CAN_RSCAN_TXQIF                 0x00000004UL
#define CAN_RSCAN_TXQFLL                0x00000002UL

/* RMIDq, RFIDx, CFIDk, TMIDp, CFIDk */
#define CAN_RSCAN_IDE                   0x80000000UL

/* RMNB */
#define CAN_RSCAN_RMNB_DEFAULT          0x00000000UL
#define CAN_RSCAN_RMPLS_GET(x)          (((uint32)(x) >> 8U) & 0x7UL)                                                   /* PRQA S 3472 # JV-01 */

/* RMNDy */
#define CAN_RSCAN_RMND_GET_INDEX(x)     (uint32)((uint32)(x) >> 5UL)
#define CAN_RSCAN_RMND_GET_BITMASK(x)   (uint32)(1UL << ((uint32)(x)&0x1FUL))

/* FESTS */
#define CAN_RSCAN_FESTS_RXFFIFO_GET_BITMASK(x)     (uint32)(1UL << (uint32)(x))
#define CAN_RSCAN_FESTS_TXRXFFIFO_GET_BITMASK(x)   (uint32)(1UL << (uint32)((x) + 8UL))

/* Calc TxBuffer index to access TxQueue */
#define CAN_RSCAN_TXQUEUE0_WINDOW(x)    (uint32)(((x)*CAN_RSCAN_TXBUFFER_PER_CH) + 0UL)
#define CAN_RSCAN_TXQUEUE1_WINDOW(x)    (uint32)(((x)*CAN_RSCAN_TXBUFFER_PER_CH) + 31UL)
#define CAN_RSCAN_TXQUEUE2_WINDOW(x)    (uint32)(((x)*CAN_RSCAN_TXBUFFER_PER_CH) + 32UL)
#define CAN_RSCAN_TXQUEUE3_WINDOW(x)    (uint32)(((x)*CAN_RSCAN_TXBUFFER_PER_CH) + 63UL)

/* Wake-up Edge detection */
#define CAN_RSCAN_FCLA_FALLING_EDGE     (uint8)0x02U
/* Clear the filter control register */
#define CAN_RSCAN_FCLA_DISABLE          (uint8)0x00U

#if (CAN_WAKE_UP_FACTOR_CLEAR_ISR == STD_ON)
/* ulWUFMask */
#define CAN_RSCAN_WUF_CHANNEL_0  0x00000002UL
#define CAN_RSCAN_WUF_CHANNEL_1  0x00000004UL
#define CAN_RSCAN_WUF_CHANNEL_2  0x00000008UL
#define CAN_RSCAN_WUF_CHANNEL_3  0x00000010UL
#define CAN_RSCAN_WUF_CHANNEL_4  0x00000020UL
#define CAN_RSCAN_WUF_CHANNEL_5  0x00000040UL
#define CAN_RSCAN_WUF_CHANNEL_6  0x00000080UL
#define CAN_RSCAN_WUF_CHANNEL_7  0x00000100UL
#define CAN_RSCAN_WUF_CHANNEL_8  0x00000400UL
#define CAN_RSCAN_WUF_CHANNEL_9  0x00000800UL
#define CAN_RSCAN_WUF_CHANNEL_10 0x00001000UL
#define CAN_RSCAN_WUF_CHANNEL_11 0x00002000UL
#define CAN_RSCAN_WUF_CHANNEL_12 0x00004000UL
#define CAN_RSCAN_WUF_CHANNEL_13 0x00008000UL
#define CAN_RSCAN_WUF_CHANNEL_14 0x00010000UL
#define CAN_RSCAN_WUF_CHANNEL_15 0x00020000UL
#define CAN_RSCAN_WUF_CHANNEL_16 0x00080000UL
#define CAN_RSCAN_WUF_CHANNEL_17 0x00100000UL
#define CAN_RSCAN_WUF_CHANNEL_18 0x00200000UL
#define CAN_RSCAN_WUF_CHANNEL_19 0x00400000UL

/* ulRxFIFOWUFMask */
#define CAN_RSCAN_WUF_GLOBAL_0   0x00000001UL
#define CAN_RSCAN_WUF_GLOBAL_1   0x00000200UL
#define CAN_RSCAN_WUF_GLOBAL_2   0x00040000UL

#endif

/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/
typedef struct STag_Can_ChRegType
{
  uint32 ulCFG;                                  /* +0000H+(m*10H) Cm(N)CFG  */
  uint32 ulCTR;                                  /* +0004H+(m*10H) CmCTR     */
  uint32 ulSTS;                                  /* +0008H+(m*10H) CmSTS     */
  uint32 ulERFL;                                 /* +000CH+(m*10H) CmERFL    */
} Can_ChRegType;

typedef struct STag_Can_FDChRegType
{
  uint32 ulDCFG;                                 /* +1400H+(m*20H) CmDCFG    */
  uint32 ulFDCFG;                                /* +1404H+(m*20H) CmFDCFG   */
  uint32 ulFDCTR;                                /* +1408H+(m*20H) CmFDCTR   */
  uint32 ulFDSTS;                                /* +140CH+(m*20H) CmFDSTS   */
  uint32 ulFDCRC;                                /* +1410H+(m*20H) CmFDCRC   */
  uint32 aaReserved[3];                          /* +1414H+(m*20H) Reserved  */
} Can_FDChRegType;

typedef struct STag_Can_RRuleRegType
{
  uint32 ulGAFLID;                               /* +1800H+(j*10H) GAFLIDj   */
  uint32 ulGAFLM;                                /* +1804H+(j*10H) GAFLMj    */
  uint32 aaGAFLP[2];                             /* +1808H+(j*10H) GAFLPbj   */
} Can_RRuleRegType;

typedef struct STag_Can_FDHrhRegType
{
  uint32 ulFDRMID;                               /* +2000H+(80H*q) FDRMIDq   */
  uint32 ulFDRMPTR;                              /* +2004H+(80H*q) FDRMPTRq  */
  uint32 ulFDRMFDSTS;                            /* +2008H+(80H*q) FDRMSTSq  */
  uint32 aaFDRMDF[29];                           /* +200CH+(80H*q) FDRMDFbq  */
} Can_FDHrhRegType;

typedef struct STag_Can_FDHRTFIFORegType
{
  uint32 ulFDRFID;                               /* +6000H+(80H*x) FDRFIDx   */
  uint32 ulFDRFPTR;                              /* +6004H+(80H*x) FDRFPTRx  */
  uint32 ulFDRFFDSTS;                            /* +6008H+(80H*x) FDRFFDSTSx*/
  uint32 aaFDRFDF[29];                           /* +600CH+(80H*x) FDRFDFdx  */
} Can_FDHRTFIFORegType;

typedef struct STag_Can_FDCFIFORegType
{
  uint32 ulFDCFID;                               /* +6400H+(80H*k) FDCFIDk   */
  uint32 ulFDCFPTR;                              /* +6404H+(80H*k) FDCFPTRk  */
  uint32 ulFDCSTS;                               /* +6408H+(80H*k) FDCFFDCST */
  uint32 aaFDCFDF[29];                           /* +640CH+(80H*k) FDCFDFdk  */
} Can_FDCFIFORegType;

typedef struct STag_Can_FDHthRegType
{
  uint32 ulFDTMID;                               /* +10000H+(80H*p) FDTMIDp   */
  uint32 ulFDTMPTR;                              /* +10004H+(80H*p) FDTMPTRp  */
  uint32 ulFDTMFDCTR;                            /* +10008H+(80H*p) FDTMFDCTRp*/
  uint32 aaFDTMDF[29];                           /* +1000CH+(80H*p) FDTMDFbp  */
} Can_FDHthRegType;

typedef struct STag_Can_THistRegType
{
  uint32 ulTHLACC0;                              /* +8000H+(8H*m) THLACC0m  */
  uint32 ulTHLACC1;                              /* +8004H+(8H*m) THLACC1m  */
} Can_THistRegType;

typedef struct STag_Can_TQueueRegType
{
  uint32 aaTXQCC[8];                     /* +1000H+(60H*4)+(4H*m) TXQCCxm   */
  uint32 aaTXQSTS[8];                    /* +1020H+(60H*4)+(4H*m) TXQTSTxm  */
  uint32 aaTXQPCTR[8];                   /* +1040H+(60H*4)+(4H*m) TXQPCTRxm */
} Can_TQueueRegType;

typedef struct STag_Can_CommonRegType                                                                                   /* PRQA S 3630 # JV-01 */
{
  Can_ChRegType aaChReg[8];                      /* +0000H+(10H*m) ChRegs    */
  uint32 ulReserved0;                            /* +0080H Reserved          */
  uint32 ulGCFG;                                 /* +0084H GCFG              */
  uint32 ulGCTR;                                 /* +0088H GCTR              */
  uint32 ulGSTS;                                 /* +008CH GSTS              */
  uint32 ulGERFL;                                /* +0090H GERFL             */
  uint32 ulGTSC;                                 /* +0094H GTSC              */
  uint32 ulGAFLECTR;                             /* +0098H GAFLECTR          */
  uint32 aaGAFLCFG[4];                           /* +009CH GAFLCFGn          */
  uint32 ulRMNB;                                 /* +00ACH RMNB              */
  uint32 aaRMND[4];                              /* +00B0H RMNDy             */
  uint32 aaRFCC[8];                              /* +00C0H+(04H*x) RFCCx     */
  uint32 aaRFSTS[8];                             /* +00E0H+(04H*x) RFSTSx    */
  uint32 aaRFPCTR[8];                            /* +0100H+(04H*x) RFPCTRx   */
  uint32 aaCFCC[24];                             /* +0120H+(04H*x) CFCCk     */
  uint32 aaCFCCE[24];                            /* +0180H+(04H*x) CFCCk     */
  uint32 aaCFSTS[24];                            /* +01E0H+(04H*x) CFSTSk    */
  uint32 aaCFPCTR[24];                           /* +0240H+(04H*x) CFPCTRk   */
  uint32 ulFESTS;                                /* +02A0H FESTS             */
  uint32 ulFFSTS;                                /* +02A4H FFSTS             */
  uint32 ulFMSTS;                                /* +02A8H FMSTS             */
  uint32 ulRFISTS;                               /* +02ACH RFISTS            */
  uint32 ulCFRISTS;                              /* +02B0H CFRISTS           */
  uint32 ulCFTISTS;                              /* +02B4H CRTISTS           */
  uint32 ulCFOFRISTS;                            /* +02B8H CFOFRISTS         */
  uint32 ulCFOFTISTS;                            /* +02BCH CFOFTISTS         */
  uint32 ulCFMOWSTS;                             /* +02C0H CFMOWSTS          */
  uint32 ulFFFSTS;                               /* +02C4H FFFSTS            */
  uint32 aaReserved1[2];                         /* +02C8H Reserved          */
  uint8 aaTMC[1280];                             /* +02D0H+(01H*p) TMCp      */
  uint8 aaTMSTS[1280];                           /* +07D0H+(01H*p) TMSTSp    */
  uint32 aaTMTRSTS[40];                          /* +0CD0H+(04H*y) TMTRSTSy  */
  uint32 aaTMTARSTS[40];                         /* +0D70H+(04H*y) TMTARSTSy */
  uint32 aaTMTCSTS[40];                          /* +0E10H+(04H*y) TMTCSTSy  */
  uint32 aaTMTASTS[40];                          /* +0EB0H+(04H*y) TMTASTSy  */
  uint32 aaTMIEC[40];                            /* +0F50H+(04H*y) TMIECy    */
  uint32 aaReserved2[4];                         /* +0FF0H Reserved          */
  Can_TQueueRegType aaTQueueReg[4];              /* +1000H+(60H*4) TQueueRegs */
  uint32 ulTXQESTS;                              /* +1180H TXQESTS           */
  uint32 ulTXQFISTS;                             /* +1184H TXQFISTS          */
  uint32 ulTXQMSTS;                              /* +1188H TXQMSTS           */
  uint32 ulTXQOWSTS;                             /* +118CH TXQOWSTS          */
  uint32 ulTXQISTS;                              /* +1190H TXQISTS           */
  uint32 ulTXQOFTISTS;                           /* +1194H TXQOFTISTS        */
  uint32 ulTXQOFRISTS;                           /* +1198H TXQOFRISTS        */
  uint32 ulTXQFSTS;                              /* +119CH TXQFSTS           */
  uint32 aaReserved3[24];                        /* +11A0H Reserved          */
  uint32 aaTHLCC[8];                             /* +1200H+(04H*y) THLCCm    */
  uint32 aaTHLSTS[8];                            /* +1220H+(04H*y) THLSTSm   */
  uint32 aaTHLPCTR[8];                           /* +1240H+(04H*y) THLPCTRm  */
  uint32 aaReserved4[40];                        /* +1260H Reserved          */
  union                                          /* +1300H+(04H*x) GTINTSTSx */
  {                                                                                                                     /* PRQA S 0750 # JV-01 */
    uint32 aaGTINTSTS[2];                        /* for 32bit access         */
    uint8  aaGTINTSTSb[8];                       /* for 8bit access          */
  } unGTINTSTS;
  uint32 ulGTSTCFG;                              /* +1308H GTSTCFG           */
  uint32 ulGTSTCTR;                              /* +130CH GTSTCTR           */
  uint32 ulReserved5;                            /* +1310H Reserved          */
  uint32 ulGFDCFG;                               /* +1314H GFDCFG            */
  uint32 ulReserved6;                            /* +1318H Reserved          */
  uint32 ulGLOCKK;                               /* +131CH GLOCKK            */
  uint32 aaReserved7[4];                         /* +1320H Reserved          */
  uint32 ulCDTCT;                                /* +1330H CDTCT             */
  uint32 ulCDTSTS;                               /* +1334H CDTSTS            */
  uint32 aaReserved8[2];                         /* +1338H Reserved          */
  uint32 ulCDTTCT;                               /* +1340H CDTTCT            */
  uint32 ulCDTTSTS;                              /* +1344H CDTTSTS           */
  uint32 aaReserved9[46];                        /* +1348H Reserved          */
  Can_FDChRegType aaFDChReg[8];                  /* +1400H+(20H*m)           */

  uint32 aaReserved10[192];                      /* +1500H Reserved          */

  Can_RRuleRegType aaRRReg[16];                  /* +1800H+(10H*j)           */

  uint32 aaReserved11[448];                      /* +1900H Reserved          */

  Can_FDHrhRegType aaHrhReg[128];                /* +2000H+(80H*q)           */
  Can_FDHRTFIFORegType aaRFReg[8];               /* +6000H+(80H*x)           */
  Can_FDCFIFORegType aaCFReg[24];                /* +6400H+(80H*k)           */

  uint32 aaReserved12[1024];                     /* +7000H Reserved          */

  Can_THistRegType aaTHistReg[8];                /* +8000H+(08H*m)           */

  uint32 aaReserved13[240];                      /* +8040H Reserved          */
  uint32 aaRPGACC[64];                           /* +8400H+(04H*r)           */
} Can_CommonRegType;

typedef struct STag_Can_FDRegType                                                                                       /* PRQA S 3630 # JV-01 */
{
  Can_FDChRegType aaFDChReg[8];                  /* +1400H+(20H*m)           */
  uint32 aaReserved0[192];                       /* +1500H Reserved          */
  Can_RRuleRegType aaRRReg[16];                  /* +1800H+(10H*j)           */
  uint32 aaReserved1[448];                       /* +1900H Reserved          */
  Can_FDHrhRegType aaHrhReg[128];                /* +2000H+(80H*q)           */
  Can_FDHRTFIFORegType aaRFReg[8];               /* +6000H+(80H*x)           */
  Can_FDCFIFORegType aaCFReg[24];                /* +6400H+(80H*k)           */
  uint32 aaReserved2[1024];                      /* +7000H Reserved          */
  Can_THistRegType aaTHistReg[8];                /* +8000H+(08H*m)           */
  uint32 aaReserved3[240];                       /* +8040H Reserved          */
  uint32 aaRPGACC[64];                           /* +8400H+(04H*r)           */
  uint32 aaReserved4[7872];                      /* +8500H Reserved          */
  Can_FDHthRegType aaHthReg[128];                /* +10000H+(80H*p)          */
} Can_FDRegType;

typedef struct STag_Can_IntMuxSelRegType
{
  uint32 ulCANINTSEL0;                           /* +0000H+(04H*n)           */
  uint32 ulCANINTSEL1;
  uint32 ulCANINTSEL2;
  uint32 ulCANINTSEL3;
} Can_IntMuxSelRegType;


/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/

#endif /* CAN_REGSTRUCT_H */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
