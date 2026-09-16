/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Eth_ETNF_LLDriver.h                                                                                 */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2023 - 2025 Renesas Electronics Corporation. All rights reserved.                                              */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains ETNF specific definitions of Eth Driver Component.                                              */
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
 * 2.4.0: 30/05/2025    : Update SW-VERSION for RH850/Ver22.01.02 U2Cx release
 * 2.3.1: 31/03/2025    : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 * 2.3.0: 28/02/2025    : - As per ticket ARDAACL-53039:
 *                         Change Eth_HwReadMiiBit and Eth_HwWriteMiiBit from void to return function 
 *                         and add ETH_ETNF_ECSR_ICD_MASK.
 *                      : Update SW-VERSION for Ver22.01.00/Ver22.01.00.D U2Cx Release
 * 2.2.0: 31/12/2024    : Update SW-VERSION for Ver22.02.00(D) U2Bx Final Release
 * 2.1.2: 31/10/2024    : Increase SW-VERSION to 2.1.2
 * 2.1.1: 22/07/2024    : Update QAC message
 *        19/06/2024    : Add #include "Os.h"
 * 2.0.3: 25/03/2024    : Add ETH_ETND_TSEL_TIMESTAMP_T1S
 * 2.0.2: 08/01/2024    : Remove QA-C Warning 1534, 1535, 1536
 *        30/11/2023    : Add define macro ETH_DESC_MAC_FIFO and ulMsr in Eth_TxCtrlTagType struct
 * 1.0.0: 30/11/2023    : Initial Version
 */
/**********************************************************************************************************************/
#ifndef ETH_ETNF_LLDRIVER_H
#define ETH_ETNF_LLDRIVER_H

#include "Eth_Types.h"
#include "Eth_Util.h"
#include "Os.h"
#include <rh850_Types.h>
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
#if (ETH_MACRO_ETNF == STD_ON)
/* AUTOSAR release version information */
#define ETH_ETNF_AR_RELEASE_MAJOR_VERSION    ETH_AR_RELEASE_MAJOR_VERSION
#define ETH_ETNF_AR_RELEASE_MINOR_VERSION    ETH_AR_RELEASE_MINOR_VERSION
#define ETH_ETNF_AR_RELEASE_REVISION_VERSION ETH_AR_RELEASE_REVISION_VERSION

/* Module Software version information */
#define ETH_ETNF_SW_MAJOR_VERSION            ETH_SW_MAJOR_VERSION
#define ETH_ETNF_SW_MINOR_VERSION            ETH_SW_MINOR_VERSION

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
/* Message (2:0750)    : A union type specifier has been defined.                                                     */
/* Rule                : MISRA C:2012 Rule-19.2                                                                       */
/* JV-01 Justification : This union type is used for register accessing and there is no issue with this usage         */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3630)    : The implementation of this struct/union type should be hidden.                               */
/* Rule                : MISRA C:2012 Dir-4.8                                                                         */
/* JV-01 Justification : The pointers point to this struct are dereferenced in other .c files, so this implementation */
/*                       should not be hidden.                                                                        */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0635)    : [E] Bit-fields in this struct/union have been declared with types other than int signed      */
/*                       int or unsigned int.                                                                         */
/* Rule                : CERTCCM INT12, MSC14, MISRA C:2012 Dir-1.1,  Rule-1.2, Rule-6.1                              */
/* JV-01 Justification : To get value bit field with type enum.                                                       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:1039)    : [E] Treating array of length one as potentially flexible member.                             */
/* Rule                : CERTCCM DCL38, MISRA C:2012 Dir-1.1, Rule-1.2                                                */
/* JV-01 Justification : Use array of length as the final member has no problem by manual reviewing.                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE Rule CWE-398, CWE-569                                            */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is accepted. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0828)    : More than 8 levels of nested conditional inclusion - program does not conform strictly to    */
/*                       ISO:C90.                                                                                     */
/* Rule                : CERTCCM DCL23, MISRA C:2012 Rule-5.4                                                         */
/* JV-01 Justification : This is accepted, , due to the implementation is following hardware specification.           */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0639)    : [E] Treating array of length one as potentially flexible member.                             */
/* Rule                : MISRA-C:2012 Dir 1.1                                                                         */
/* JV-01 Justification : This warning does not indicate a mistake in the code, it is a message to call attention to   */
/*                       the processing power of the compiler. Because the compiler in use has been confirmed to have */
/*                       the ability to handle this, no problem.                                                      */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                            HW specific parameters referred from the upper-level driver                             **
***********************************************************************************************************************/
#define ETH_CPUCLK_MHZ                       400UL
#define ETH_NS2HZ_AVB(nano_sec)              ((ETH_CPUCLK_MHZ * (nano_sec)) / 1000UL)                                   /* PRQA S 3472 # JV-01 */
#define ETH_HZ2NS(clock_hz)                  (1000000000UL / (clock_hz))                                                

/* Insert paddings to the top of buffers to align payload location as 4 byte */
/* Paddings before header */
#define ETH_TXRX_BUFFER_PRE_PADDING          2UL
/* Paddings between header and payload */
#define ETH_TXRX_BUFFER_IN_PADDING           0UL

/* Minimum payload length allowed by the HW */
#define ETH_MIN_PAYLOAD_SIZE_AVB             1UL

/* Rx descriptor chain offset in descriptor base address table */
#define ETH_RXBEQ_OFFSET                     (uint8)4

/* Descriptor Types */
#define ETH_DESC_FSINGLE_AVB                 7U

#define ETH_DESC_LINK_AVB                    8U
#define ETH_DESC_LINKFIX                     9U

#define ETH_DESC_FEMPTY_AVB                  12U
#define ETH_DESC_RETAIN_TS                   1U
#define ETH_DESC_MAC_FIFO                    1U

/* Range of Increment value for gPTP timer */
#define ETH_GPTP_INC_MINVALUE                0x00100000UL
#define ETH_GPTP_INC_MAXVALUE                0x0FF00000UL

#define ETH_GPTP_OFFSET_NANOSEC_MAXVALUE     0x3B9AC9FFUL

/***********************************************************************************************************************
**                                              size of Tx/Rx descriptor                                              **
***********************************************************************************************************************/
#define ETH_NORMAL_DESC_SIZE                 8U  /* normal descriptor size(in byte)*/
#define ETH_SPECIAL_DESC_SIZE                20U /*special descriptor size(in byte)*/

/* Rx interrupt status */
#define ETH_RX_FIFO_CRIT_LVL                 (uint32)0x1800U /* Rx FIFO Critical Level */

#define ETH_ETNF_EIC_ERROR                   0x00000004UL
#define ETH_ETNF_ESR_ERROR_MASK              0x00000F00UL
#define ETH_ETNF_ESR_ERROR_TX_BUFFER         0x00000300UL

/***********************************************************************************************************************
**                                         General Ethernet MAC Address Size                                          **
***********************************************************************************************************************/
#define ETH_RX_BUF_LENGTH                    (ETH_HEADER_SIZE + 1500UL + ETH_VLAN_SIZE)
#define ETH_RX_DPTR_OFFSET                   2UL
#define ETH_MAX_TX_PAYLOAD_LENGTH            (1500UL + ETH_VLAN_SIZE)

/* Copy the stream filter address */
#define ETH_COPY_STREAM_ADDRESS(src, dst)                                                                               /* PRQA S 3472 # JV-01 */\
  do                                      \
  {                                       \
    (dst)[0] = (src)[0];                  \
    (dst)[1] = (src)[1];                  \
    (dst)[2] = (src)[2];                  \
    (dst)[3] = (src)[3];                  \
    (dst)[4] = (src)[4];                  \
    (dst)[5] = (src)[5];                  \
    (dst)[6] = (src)[6];                  \
    (dst)[7] = (src)[7];                  \
  } while (0)

#define ETH_FIFOSIZE_TWO                       2U
/* want to change from ETH_BIT1_SET_32 to ETH_ETNF_GET_RIS0_QUEUE */
#define ETH_BIT1_SET_32                        0x00000001UL
#define ETH_ETNF_GET_RIS0_QUEUE

#define ETH_DESCR_TAG_MASK                     0x000003FFUL

/* CBS Limits */
#define ETH_MAX_CIV                            0x0000FFFFU /* 65535 */
#define ETH_MIN_CDV                            0xFFFF0000U /* -65536 */

/* SFL Load Command */
#define ETH_SFL_MASK                           0x0000001FUL
#define ETH_NO_LOAD_REQ                        0x1FUL

/***********************************************************************************************************************
**                                                 Rx Channel number                                                  **
***********************************************************************************************************************/
#define ETH_BECHANNEL                          (uint8)0U /* best effort channel */
#define ETH_NCCHANNEL                          (uint8)1U /* network control channel */

/***********************************************************************************************************************
**                                             Number of TX/RX descriptor                                             **
***********************************************************************************************************************/
#define ETH_CYCLIC_DESC_NUM                    1U   /* Number of descriptors for the Cyclic */

/***********************************************************************************************************************
** Number of Tx/Rx queues
***********************************************************************************************************************/
#define ETH_TXQ_NUM                            4UL  /* tx queue number */
#define ETH_RXQ_NUM                            18UL /* rx queue number */

/* Rx queue index available for filtering from queue 2 to 17 */
#define ETH_RX_QUEUE_INDEX_AVAILABLE_FILTER    2U

/***********************************************************************************************************************
** Mask for the Status Register
***********************************************************************************************************************/

/* AVB DMAC */
#define ETH_RX_INT_MASK                        0x3FFFFUL
#define ETH_TIC_TFUE                           0x00000100UL
#define ETH_TIS_TFUF_MASK                      0x00000100UL
#define ETH_TFA2_TSV_MASK                      0x0000FFFFUL

/* MAC */
#define ETH_ETNF_ECMR_PRM                      0x00000001UL

/* Register */
#define ETH_EIS_QEF_MASK                       0x00000004UL
#define ETH_SGINTS_MASK                        0x00000003UL

/* This is the minimum GTI value possible 22.4.7.2 Free-Running Operation */
#define ETH_GPTP_MAXVALUE                      0xFFFFFFFFUL

/* MASK */
#define ETH_GPTP_CAPTURE_MASK                  0x00000003UL
#define ETH_CSR_TDUO_RPO_TPOX_MASK             0x003F0000UL
#define ETH_TCCR_TSRQX_MASK                    0x0000000FUL
#define ETH_TSR_TFFL_MASK                      0x00000700UL

/* register value */
/* ETNFnCCC */
#define ETH_ETNF_CCC_LBME                      0x01000000UL
#define ETH_ETNF_CCC_DTSR                      0x00000100UL
#define ETH_ETNF_CCC_OPC_OPERATION             0x00000002UL
#define ETH_ETNF_CCC_OPC_MASK                  0x00000003UL
#define ETH_ETNF_CCC_CSEL_ETH_TX_CLK           0x00020000UL
#define ETH_ETNF_CCC_CSEL_PTP_CLK_SRC          0x00030000UL
#define ETH_ETNF_CCC_CSEL_MASK                 0x00030000UL

#define ETH_ETNF_CSR_DTS                       0x00000100UL
#define ETH_ETNF_CSR_TDUO_RPO                  0x00300000UL
#define ETH_ETNF_CSR_OPS                       0x0000000FUL

#define ETH_ETNF_RCR_ENCF_SHIFT                1UL
#define ETH_ETNF_RCR_ESF_SHIFT                 2UL
#define ETH_ETNF_RCR_ETS0_SHIFT                4UL
#define ETH_ETNF_RCR_ETS2_SHIFT                5UL
#define ETH_ETNF_RCR_RFCL_SHIFT                16UL

#define ETH_ETNF_ECSR_ICD_MASK                 0x00000001UL

/* Masking for summary of error information in info0 */
#define ETH_ETND_TSEL_TIMESTAMP_T1S           0x00000001UL

#define ETH_ETNF_GET_RQCi(LulQIndex)           ((LulQIndex) / 4UL)                                                      /* PRQA S 3472 # JV-01 */

#define ETH_ETNF_SET_RQCi_RSMr(val, LulQIndex) ((uint32)(val) << (((LulQIndex) % 4UL) * 8UL))                           /* PRQA S 3472 # JV-01 */

#define ETH_ETNF_SET_RQCi_UFCCr(val, LulQIndex) ((uint32)(val) << ((((LulQIndex) % 4UL) * 8UL) + 4UL))                  /* PRQA S 3472 # JV-01 */

#define ETH_ETNF_SET_RQCi_PIAr(val, LulQIndex) ((uint32)(val) << ((((LulQIndex) % 4UL) * 8UL) + 6UL))                   /* PRQA S 3472 # JV-01 */

#define ETH_ETNF_GET_UFCVi(LulQIndex)          ((LulQIndex) / 4UL)                                                      /* PRQA S 3472 # JV-01 */

#define ETH_ETNF_GET_UFCVi_CVr(val, LulQIndex) (uint32)(((val) >> (((LulQIndex) % 4UL) * 8UL)) & 0x3FUL)

#define ETH_ETNF_GET_UFCDi(LucQidx)            ((LucQidx) / 4U)                                                         /* PRQA S 3472 # JV-01 */

#define ETH_ETNF_SET_UFCDi_DVr(val, LucQidx)   ((val) << (((uint32)(LucQidx) % 4UL) * 8UL))                             /* PRQA S 3472 # JV-01 */

#define ETH_ETNF_SET_GTI_TIV(val)              ((uint32)(val) << 20UL)                                                  /* PRQA S 3472 # JV-01 */

#define ETH_ETNF_GET_TFFL(val)                 (((val) & ETH_TSR_TFFL_MASK) >> 8UL)                                     /* PRQA S 3472 # JV-01 */

#define ETH_ETNF_GET_TST(val)                  ((uint32)(val) >> 16UL)                                                  /* PRQA S 3472 # JV-01 */

#define ETH_ETNF_SFO_FBP_VALUE                 0x16U
#define ETH_ETNF_GET_LOW_SFPi(LucSFPidx)       ((LucSFPidx) * 2U)                                                       /* PRQA S 3472 # JV-01 */

#define ETH_ETNF_GET_HIGH_SFPi(LucSFPidx)      (((LucSFPidx) * 2U) + 1U)                                                /* PRQA S 3472 # JV-01 */

#define ETH_ETNF_SFM0_TALKERFILTER             0xFFFFFFFFUL
#define ETH_ETNF_SFM1_TALKERFILTER             0x0000FFFFUL

#define ETH_ETNF_SFM0_LISNERFILTER             0xFFFFFFFFUL
#define ETH_ETNF_SFM1_LISNERFILTER             0xFFFFFFFFUL

#define ETH_ETNF_TGC_TSM1_SHIFT                1U
#define ETH_ETNF_TGC_TSM2_SHIFT                2U
#define ETH_ETNF_TGC_TSM3_SHIFT                3U
#define ETH_ETNF_TGC_TQP0_SHIFT                4U
#define ETH_ETNF_TGC_TQP1_SHIFT                5U

#define ETH_ETNF_TGC_TBDn_VALUE                0x00222200UL

#define ETH_ETNF_TCCR_TFR                      0x00000200UL
#define ETH_ETNF_TCCR_TFEN                     0x00000100UL
#define ETH_ETNF_GCCR_TCSS_ADJUSTED_GPTP       0x00000100UL
#define ETH_ETNF_GCCR_TCR_CAP_START            0x00000003UL
#define ETH_ETNF_GCCR_LTI                      0x00000008UL
#define ETH_ETNF_GCCR_LTO                      0x00000004UL
#define ETH_ETNF_GCCR_TCR_MASK                 0x00000003UL
#define ETH_ETNF_GCCR_TCSS_MASK                0x00000300UL
#define ETH_ETNF_GCCR_PGM                      0x00010000UL
#define ETH_ETNF_ECMR_RE_TE                    0x00000060UL
#define ETH_ETNF_ECMR_DM_FULL_DUPLEX           0x00000002UL
#define ETH_ETNF_ECMR_DM_T1S                   0x00000000UL
#define ETH_ETNF_ECMR_ZPF_CRS_NOT_CHECKED      0x00080000UL

/* ETNFnPIR */
#define ETH_ETNF_GET_MDI(regval)               (((uint32)(regval) >> 3UL) & 1UL)                                        /* PRQA S 3472 # JV-01 */

#define ETH_ETNF_PIR_MDC                       0x00000001UL
#define ETH_ETNF_PIR_MMD                       0x00000002UL
#define ETH_ETNF_PIR_MDO                       0x00000004UL

/***********************************************************************************************************************
**                                             MDIO related definitions                                               **
***********************************************************************************************************************/
#define ETH_ETNF_WORST_SLEW_RATE               90UL

/***********************************************************************************************************************
**                                              Register address offset                                               **
***********************************************************************************************************************/
#define ETH_CCC                                0x0000UL
#define ETH_DBAT                               0x0004UL
#define ETH_DLR                                0x0008UL
#define ETH_CSR                                0x000CUL
#define ETH_ESR                                0x0088UL
#define ETH_RIMR                               0x008CUL
#define ETH_RCR                                0x0090UL
#define ETH_RQC0                               0x0094UL
#define ETH_RQC1                               0x0098UL
#define ETH_RQC2                               0x009CUL
#define ETH_RQC3                               0x00A0UL
#define ETH_RQC4                               0x00A4UL
#define ETH_RPC                                0x00B0UL
#define ETH_UFCV0                              0x00C4UL
#define ETH_UFCV1                              0x00C8UL
#define ETH_UFCV2                              0x00CCUL
#define ETH_UFCV3                              0x00D0UL
#define ETH_UFCV4                              0x00D4UL
#define ETH_UFCD0                              0x00E0UL
#define ETH_UFCD1                              0x00E4UL
#define ETH_UFCD2                              0x00E8UL
#define ETH_UFCD3                              0x00ECUL
#define ETH_UFCD4                              0x00F0UL
#define ETH_SFO                                0x00FCUL
#define ETH_SFP00                              0x0100UL
#define ETH_SFP01                              0x0104UL
#define ETH_SFP02                              0x0108UL
#define ETH_SFP03                              0x010CUL
#define ETH_SFP04                              0x0110UL
#define ETH_SFP05                              0x0114UL
#define ETH_SFP06                              0x0118UL
#define ETH_SFP07                              0x011CUL
#define ETH_SFP08                              0x0120UL
#define ETH_SFP09                              0x0124UL
#define ETH_SFP10                              0x0128UL
#define ETH_SFP11                              0x012CUL
#define ETH_SFP12                              0x0130UL
#define ETH_SFP13                              0x0134UL
#define ETH_SFP14                              0x0138UL
#define ETH_SFP15                              0x013CUL
#define ETH_SFP16                              0x0140UL
#define ETH_SFP17                              0x0144UL
#define ETH_SFP18                              0x0148UL
#define ETH_SFP19                              0x014CUL
#define ETH_SFP20                              0x0150UL
#define ETH_SFP21                              0x0154UL
#define ETH_SFP22                              0x0158UL
#define ETH_SFP23                              0x015CUL
#define ETH_SFP24                              0x0160UL
#define ETH_SFP25                              0x0164UL
#define ETH_SFP26                              0x0168UL
#define ETH_SFP27                              0x016CUL
#define ETH_SFP28                              0x0170UL
#define ETH_SFP29                              0x0174UL
#define ETH_SFP30                              0x0178UL
#define ETH_SFP31                              0x017CUL
#define ETH_SFM0                               0x01C0UL
#define ETH_SFM1                               0x01C4UL

#define ETH_TGC                                0x0300UL
#define ETH_TCCR                               0x0304UL
#define ETH_TFA0                               0x0310UL
#define ETH_TFA1                               0x0314UL
#define ETH_TFA2                               0x0318UL
#define ETH_CIVR0                              0x0320UL
#define ETH_CIVR1                              0x0324UL
#define ETH_CDVR0                              0x0328UL
#define ETH_CDVR1                              0x032CUL
#define ETH_CUL0                               0x0330UL
#define ETH_CUL1                               0x0334UL
#define ETH_CLL0                               0x0338UL
#define ETH_CLL1                               0x033CUL

#define ETH_DIC                                0x0350UL
#define ETH_DIS                                0x0354UL
#define ETH_EIC                                0x0358UL
#define ETH_EIS                                0x035CUL
#define ETH_RIC0                               0x0360UL
#define ETH_RIS0                               0x0364UL
#define ETH_RIC2                               0x0370UL
#define ETH_TIC                                0x0378UL
#define ETH_GCCR                               0x0390UL
#define ETH_GTI                                0x039CUL
#define ETH_GTO0                               0x03A0UL
#define ETH_GTO1                               0x03A4UL
#define ETH_GTO2                               0x03A8UL
#define ETH_GIC                                0x03ACUL
#define ETH_RIC3                               0x0388UL

#define ETH_ECMR                               0x0500UL /* MAC mode reg                 */
#define ETH_RFLR                               0x0508UL /* receive frame length reg     */
#define ETH_ECSIPR                             0x0518UL /* MAC interrupt permission reg */
#define ETH_MAHR                               0x05C0UL /* MAC address high reg         */
#define ETH_MALR                               0x05C8UL /* MAC address low reg          */

#define ETH_DCDC                               0x0708UL /* Delay collisions counter           */
#define ETH_CEFCR                              0x0740UL /* CRC error frame receive counter    */
#define ETH_FRECR                              0x0748UL /* frame receive error counter reg    */
#define ETH_TSFRCR                             0x0750UL /* too short frame receive counter    */
#define ETH_TLFRCR                             0x0758UL /* too long frame receive counter     */
#define ETH_RFCR                               0x0760UL /* residual-bit frame receive counter */
#define ETH_MAFCR                              0x0778UL /* multicast address frame counter    */

/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/

typedef struct STag_Eth_MemManagerType                                                                                  /* PRQA S 3630 # JV-01 */
{
  struct STag_Eth_MemManagerType *pNext; /* Next node */
  struct STag_Eth_MemManagerType *pPrev; /* Prev node */
  uint32 ulHeapSize;                     /* Memory block size */
  boolean blHeapLock;                    /* Memory lock flag  */
  uint8 ucDummy[3];                      /* Dummy */
} Eth_MemManagerType;

/***********************************************************************************************************************
**  Type: Eth_TxSyncModeType                                                                                          **
**                                                                                                                    **
**  Transmission synchronization mode                                                                                 **
**                                                                                                                    **
**  Members:                                                                                                          **
**    ETH_TXNORMAL  - normal mode, full descriptor write back                                                         **
**    ETH_TXNOWB    - no write back, no descriptor write back                                                         **
***********************************************************************************************************************/
typedef enum ETag_Eth_TxSyncModeType
{
  ETH_TXNORMAL = 0,
  ETH_TXNOWB
} Eth_TxSyncModeType;

/***********************************************************************************************************************
**  Type: Eth_PIAConfigType                                                                                           **
**                                                                                                                    **
**  packed incremental data area configuration                                                                        **
**                                                                                                                    **
**  Members:                                                                                                          **
**    ETH_GAP32 - frame data starts always 32 bit aligned                                                             **
**    ETH_NOGAP - no gaps between frame data in incremental data area                                                 **
***********************************************************************************************************************/
typedef enum ETag_Eth_PIAConfigType
{
  ETH_GAP32 = 0,
  ETH_NOGAP
} Eth_PIAConfigType;

/***********************************************************************************************************************
**  Type: Eth_UFCConfigType                                                                                           **
**                                                                                                                    **
**  unread frame counter configuration                                                                                **
**                                                                                                                    **
**  Members:                                                                                                          **
**    ETH_UFCC0 - unread frame counter configuration 0                                                                **
**    ETH_UFCC1 - unread frame counter configuration 1                                                                **
**    ETH_UFCC2 - unread frame counter configuration 2                                                                **
**    ETH_UFCC3 - unread frame counter configuration 3                                                                **
***********************************************************************************************************************/
typedef enum ETag_Eth_UFCConfigType
{
  ETH_UFCC0 = 0,
  ETH_UFCC1,
  ETH_UFCC2,
  ETH_UFCC3
} Eth_UFCConfigType;

/***********************************************************************************************************************
**  Type: Eth_RxSyncModeType                                                                                          **
**                                                                                                                    **
**  receive synchronization mode                                                                                      **
**                                                                                                                    **
**  Members:                                                                                                          **
**    ETH_NORMAL  - normal mode (full descriptor write back)                                                          **
**    ETH_KEEPDT  - keep DT mode (no update of DT field at descriptor write back)                                     **
**    ETH_NOWB    - no write back (no descriptor write back)                                                          **
***********************************************************************************************************************/
typedef enum Etag_Eth_RxSyncModeType
{
  ETH_RXNORMAL = 0,
  ETH_RXKEEPDT,
  ETH_RXNOWB
} Eth_RxSyncModeType;

/***********************************************************************************************************************
**  Type: ETag_QueuePolicyType                                                                                        **
**                                                                                                                    **
**  Setting option                                                                                                    **
**                                                                                                                    **
**  Members:                                                                                                          **
**    ETH_NONE    - None                                                                                              **
**    ETH_CBS     - CBS                                                                                               **
***********************************************************************************************************************/
/* Type of Shaper for a specific Queue */
typedef enum ETag_QueuePolicyType
{
  ETH_NONE,
  ETH_CBS
} Eth_TxQueuePolicyType;

/***********************************************************************************************************************
**  Type: Eth_TxQPrioType                                                                                             **
**                                                                                                                    **
**  Transmission queue priority                                                                                       **
**                                                                                                                    **
**  Members:                                                                                                          **
**    ETH_NONAVB  - non-AVB mode (Q3 > Q2 > Q1 > Q0)                                                                  **
**    ETH_AVBDEF  - default AVB priority (Q3 > Q2 > Q1 > Q0)                                                          **
**    ETH_AVBALT  - alternate AVB priority (Q1 > Q3 > Q2 > Q0)                                                        **
***********************************************************************************************************************/
typedef enum ETag_Eth_TxQPrioType
{
  ETH_AVBDEF = 0,
  ETH_AVBALT
} Eth_TxQPrioType;

/***********************************************************************************************************************
**  Enum: Eth_OpStatusType                                                                                            **
**                                                                                                                    **
**  AVB operation status                                                                                              **
**                                                                                                                    **
**  Members:                                                                                                          **
**    ETH_RESET      - reset                                                                                          **
**    ETH_CONFIG     - config                                                                                         **
**    ETH_OPERATION  - operation                                                                                      **
**    ETH_STANDBY    - standby                                                                                        **
***********************************************************************************************************************/
typedef enum Etag_Eth_OpStatusType
{
  ETH_RESET = 0,
  ETH_CONFIG = 1,
  ETH_OPERATION = 2,
  ETH_STANDBY = 3,
  ETH_UNINIT = 4
} Eth_OpStatusType;

/***********************************************************************************************************************
**  Enum: Eth_GPtpClkType                                                                                             **
**                                                                                                                    **
**  gPTP clock source                                                                                                 **
**                                                                                                                    **
**  Members:                                                                                                          **
**    ETH_GPTP_DISABLE   - gPTP support disabled                                                                      **
**    ETH_GPTP_PBUS      - gPTP based on peripheral bus clock                                                         **
**    ETH_GPTP_ETHTX     - gPTP based on ethernet Tx clock                                                            **
***********************************************************************************************************************/
typedef enum ETag_Eth_GPtpClkType
{
  ETH_GPTP_DISABLE = 0,
  ETH_GPTP_PBUS,
  ETH_GPTP_ETHTX
} Eth_GPtpClkType;

/***********************************************************************************************************************
**  Type: Eth_SFOptionType                                                                                            **
**                                                                                                                    **
**  Stream filtering option                                                                                           **
**                                                                                                                    **
**  Members:                                                                                                          **
**    ETH_DISABLE   - receive queues r>=2 are disabled                                                                **
**    ETH_SEPFILTER - separation filtering only                                                                       **
**    ETH_AVBNMDISC - avb stream with separation filtering, no matching frames discarded                              **
**    ETH_AVBNMQUE0 - avb stream with separation filtering, no matching frames into queue0                            **
***********************************************************************************************************************/
typedef enum Etag_Eth_SFOptionType
{
  ETH_SFDISABLE = 0,
  ETH_SEPFILTER = 0,
  ETH_AVBNMDISC = 2,
  ETH_AVBNMQUE0 = 3
} Eth_SFOptionType;

/***********************************************************************************************************************
**  Enum: Eth_TxChannel                                                                                               **
**                                                                                                                    **
**  Value are based on on Fig 22.13                                                                                   **
**                                                                                                                    **
**  Members:                                                                                                          **
**    ETH_TX_BE  - Queue 0                                                                                            **
**    ETH_TX_NC  - Queue 1                                                                                            **
**    ETH_TX_SB  - Queue 2                                                                                            **
**    ETH_TX_SA  - Queue 3                                                                                            **
***********************************************************************************************************************/
typedef enum ETag_Eth_TxChannelType
{
  ETH_TX_BE = 0,
  ETH_TX_NC,
  ETH_TX_SB,
  ETH_TX_SA
} Eth_TxChannelType;

/***********************************************************************************************************************
**  Enum: Eth_RxChType                                                                                                **
**                                                                                                                    **
**  AVB Rx Channel                                                                                                    **
**                                                                                                                    **
**  Members:                                                                                                          **
**    ETH_RX_BE    - best effort                                                                                      **
**    ETH_RX_NC    - network control                                                                                  **
**    ETH_RX_S     - stream                                                                                           **
***********************************************************************************************************************/
typedef enum ETag_Eth_RxChType
{
  ETH_RX_BE,
  ETH_RX_NC,
  ETH_RX_S
} Eth_RxChType;

/***********************************************************************************************************************
  Section: Structures
***********************************************************************************************************************/

/***********************************************************************************************************************
**  Type: Eth_TxConfigType                                                                                            **
**                                                                                                                    **
**  Transmission configuration enum                                                                                   **
**                                                                                                                    **
**  Members:                                                                                                          **
**    enTsm0   - transmit synchronization mode0 (BE class)                                                            **
**    enTsm1   - transmit synchronization mode1 (NC class)                                                            **
**    enTsm2   - transmit synchronization mode2 (stream class B)                                                      **
**    enTsm3   - transmit synchronization mode3 (stream class A)                                                      **
**    enEcbs   - enable credit based shaping                                                                          **
**    enTqp    - transmission queues priority                                                                         **
***********************************************************************************************************************/
typedef struct STag_Eth_TxConfigType
{
  Eth_TxSyncModeType enTsm0;
  Eth_TxSyncModeType enTsm1;
  Eth_TxSyncModeType enTsm2;
  Eth_TxSyncModeType enTsm3;
  Eth_OptionType enEcbs;
  Eth_TxQPrioType enTqp;
} Eth_TxConfigType;

/***********************************************************************************************************************
**  Type: Eth_DescTimeStampType                                                                                       **
**                                                                                                                    **
**  Timestamp structure                                                                                               **
**                                                                                                                    **
**  Members:                                                                                                          **
**    ulTimestamp0  - timestamp[31:0]                                                                                 **
**    ulTimestamp1  - timestamp[63:32]                                                                                **
**    usTimestamp2  - timestamp[79:64]                                                                                **
***********************************************************************************************************************/

typedef struct STag_Eth_DescTimeStampType
{
  uint32 ulTimestamp0;
  uint32 ulTimestamp1;
  uint16 usTimestamp2;
  /* Add dummy variable */
  uint16 usDummy;
} Eth_DescTimeStampType;

/***********************************************************************************************************************
**  Type: Eth_QConfigType                                                                                             **
**                                                                                                                    **
**  Queue configuration                                                                                               **
**                                                                                                                    **
**  Members:                                                                                                          **
**    enPia   - packed incremental data area                                                                          **
**    enUfcc  - unread frame counter configuration                                                                    **
**    enRsm   - receive synchronization mode                                                                          **
***********************************************************************************************************************/
typedef struct STag_Eth_QConfigType
{
  Eth_PIAConfigType enPia;
  Eth_UFCConfigType enUfcc;
  Eth_RxSyncModeType enRsm;
} Eth_QConfigType;

/***********************************************************************************************************************
**  Type: Eth_RxConfigTypeEtnf                                                                                        **
**                                                                                                                    **
**  reception configuration structure                                                                                 **
**                                                                                                                    **
**  Members:                                                                                                          **
**    enEncf                  - enable network control filtering                                                      **
**    enEsf                   - enable stream filtering                                                               **
**    enEts0                  - enable timestamp storage (best effort)                                                **
**    enEts2                  - enable timestamp storage (stream)                                                     **
**    ulRfcl                  - reception FIFO critical level                                                         **
**    enSRPTalkerFiltering    - enable stream filtering for talker only                                               **
***********************************************************************************************************************/
typedef struct STag_Eth_RxConfigTypeEtnf
{
  Eth_OptionType enEncf;
  Eth_SFOptionType enEsf;
  Eth_OptionType enEts0;
  Eth_OptionType enEts2;
  uint32 ulRfcl;
  #if (ETH_STREAM_FILTERING == STD_ON)
  Eth_OptionType enSRPTalkerFiltering;
  #endif
} Eth_RxConfigTypeEtnf;

/***********************************************************************************************************************
**  Type: Eth_AvbConfigType                                                                                           **
**                                                                                                                    **
**  AVB part configuration structure                                                                                  **
**                                                                                                                    **
**  Members:                                                                                                          **
**    stRxConfig    - see <Eth_ComConfigType>                                                                         **
**    stTxConfig    - see <Eth_TxConfigType>                                                                          **
***********************************************************************************************************************/
typedef struct STag_Eth_AvbConfigType
{
  Eth_RxConfigTypeEtnf stRxConfig;
  Eth_TxConfigType stTxConfig;
} Eth_AvbConfigType;

/***********************************************************************************************************************
**  Type: Eth_RxChConfigType                                                                                          **
**                                                                                                                    **
**  Rx channel configuration structure                                                                                **
**                                                                                                                    **
**  Members:                                                                                                          **
**    enChType          - channel type, see <Eth_RxChType>                                                            **
**    ucChNum           - channel number                                                                              **
**    aaPatternStream   - Pattern Stream to be written into SFPi                                                      **
***********************************************************************************************************************/
typedef struct STag_Eth_RxChConfigType
{
  Eth_RxChType enChType;
  uint8 ucChNum;
  uint8 usDummy[3];
  uint8 aaPatternStream[8];
} Eth_RxChConfigType;

/***********************************************************************************************************************
**  Type: Eth_TxCtrlTagType                                                                                           **
**                                                                                                                    **
**  Tx specific control field structure                                                                               **
**                                                                                                                    **
**  Members:                                                                                                          **
**    ulTag  - frame tag                                                                                              **
**    ulTsr  - timestamp storage request                                                                              **
**    ulMsr  - MAC Status storage Request                                                                             **
***********************************************************************************************************************/
typedef struct STag_Eth_TxCtrlTagType
{
  uint32 ulTag : 10;                                                                                                    /* PRQA S 0635 # JV-01 */
  uint32 ulTsr : 1;                                                                                                     /* PRQA S 0635 # JV-01 */
  uint32 ulMsr : 1;                                                                                                     /* PRQA S 0635 # JV-01 */
} Eth_TxCtrlTagType;

/***********************************************************************************************************************
**  Union: Eth_TxRxCtrl                                                                                               **
**                                                                                                                    **
**  Simplifies Bit and Byte access                                                                                    **
**                                                                                                                    **
**  Members:                                                                                                          **
**    stTxCtrl  - Tx control field                                                                                    **
**    ulWord    - Allow access of the whole word.                                                                     **
***********************************************************************************************************************/
typedef union UTag_Eth_TxRxCtrl
{                                                                                                                       /* PRQA S 0750 # JV-01 */
  Eth_TxCtrlTagType stTxCtrl;
  uint32 ulWord;
} Eth_TxRxCtrl;

/***********************************************************************************************************************
**  Type: Eth_DataDescLTypeEtnf                                                                                       **
**                                                                                                                    **
**  Data descriptor structure low word                                                                                **
**                                                                                                                    **
**  Members:                                                                                                          **
**    ulDs   - Size of descriptor data                                                                                **
**    ulCtrl - content control code for Tx/Rx                                                                         **
**    ulDie  - descriptor interrupt enable                                                                            **
**    ulDt   - descriptor type                                                                                        **
***********************************************************************************************************************/
typedef struct STag_Eth_DataDescLTypeEtnf
{
  uint32 ulDs : 12;                                                                                                     /* PRQA S 0635 # JV-01 */
  uint32 ulCtrl : 12;                                                                                                   /* PRQA S 0635 # JV-01 */
  uint32 ulDie : 4;                                                                                                     /* PRQA S 0635 # JV-01 */
  uint32 ulDt : 4;                                                                                                      /* PRQA S 0635 # JV-01 */
} Eth_DataDescLTypeEtnf;

/***********************************************************************************************************************
**  Type: Eth_LinkDescLType                                                                                           **
**                                                                                                                    **
**  Link descriptor structure low word                                                                                **
**                                                                                                                    **
**  Members:                                                                                                          **
**    ulRes  - Reserved                                                                                               **
**    ulDie  - descriptor interrupt enable                                                                            **
**    ulDt   - descriptor type                                                                                        **
***********************************************************************************************************************/
typedef struct STag_Eth_LinkDescLType
{
  uint32 ulRes : 24;                                                                                                    /* PRQA S 0635 # JV-01 */
  uint32 ulDie : 4;                                                                                                     /* PRQA S 0635 # JV-01 */
  uint32 ulDt : 4;                                                                                                      /* PRQA S 0635 # JV-01 */
} Eth_LinkDescLType;

/***********************************************************************************************************************
**  Type: Eth_DataDescType                                                                                            **
**                                                                                                                    **
**  Data descriptor structure                                                                                         **
**                                                                                                                    **
**  Members:                                                                                                          **
**    stHeader - low word of the data descriptor                                                                      **
**    ulDptr   - point to the descriptor data                                                                         **
***********************************************************************************************************************/
typedef struct STag_Eth_DataDescType
{
  Eth_DataDescLTypeEtnf stHeader;
  uint32 ulDptr;
} Eth_DataDescType;

/***********************************************************************************************************************
**  Type: Eth_ExtDataDescType                                                                                         **
**                                                                                                                    **
**  Extended data descriptor structure                                                                                **
**                                                                                                                    **
**  Members:                                                                                                          **
**    stHeader    - low word of the data descriptor                                                                   **
**    ulDptr      - point to the descriptor data                                                                      **
**    stTimestamp - timestamp for received frame                                                                      **
***********************************************************************************************************************/
typedef struct STag_Eth_ExtDataDescType
{
  Eth_DataDescLTypeEtnf stHeader;
  uint32 ulDptr;
  Eth_DescTimeStampType stTimestamp;
} Eth_ExtDataDescType;

/***********************************************************************************************************************
**  Type: Eth_LinkDescType                                                                                            **
**                                                                                                                    **
**  Link descriptor structure                                                                                         **
**                                                                                                                    **
**  Members:                                                                                                          **
**    stHeader    - low word of the link descriptor                                                                   **
**    ulDptr      - point to the next descriptor                                                                      **
***********************************************************************************************************************/
typedef struct STag_Eth_LinkDescType
{
  Eth_LinkDescLType stHeader;
  uint32 ulDptr;
} Eth_LinkDescType;

/***********************************************************************************************************************
**  Type: Etag_Eth_DirectionType                                                                                      **
**                                                                                                                    **
**  Direction type                                                                                                    **
**                                                                                                                    **
**  Members:                                                                                                          **
**    ETH_TX    - Transmit                                                                                            **
**    ETH_RX    - Receive                                                                                             **
***********************************************************************************************************************/
typedef enum Etag_Eth_DirectionType
{
  ETH_TX,
  ETH_RX
} Eth_DirectionType;

/***********************************************************************************************************************
**  Type: Eth_GeneralHandlerType                                                                                      **
**                                                                                                                    **
**  Generic handler                                                                                                   **
**                                                                                                                    **
**  Members:                                                                                                          **
**    stNode      - the Node for linked list management                                                               **
**    pHandler    - the Generic handler pointer                                                                       **
***********************************************************************************************************************/
typedef struct STag_Eth_GeneralHandlerType
{
  Eth_DListNodeType stNode;
  void *pHandler;
} Eth_GeneralHandlerType;


/***********************************************************************************************************************
**  Type: Eth_HwStatusTypeEtnf                                                                                        **
**                                                                                                                    **
**  Device instance specific data.                                                                                    **
**                                                                                                                    **
**  All instance specific data is kept within that structure.                                                         **
**                                                                                                                    **
**  Members:                                                                                                          **
**    ulBaseAddr            - Avb part base address                                                                   **
**    ulDescTableAddr       - Descriptor table address                                                                **
**    aaBufTxCnt            - Buffer Tx counter                                                                       **
**    aaHeadTxDesc          - Head tx descriptor address                                                              **
**    aaLastTxDesc          - Last tx descriptor address                                                              **
**    aaNextRxDesc          - Next free rx descriptor address                                                         **
**    enRxBeTimestamp       - Rx timestamp function status of best effort channel                                     **
**    enRxSTimestamp        - Rx timestamp function status of stream channel                                          **
**    aaRxBeQueueBuf        - Rx BE buffer addresses                                                                  **
**    aaRxNcQueueBuf        - Rx NC buffer addresses                                                                  **
**    aaRxSQueueBuf         - Rx stream buffer address                                                                **
**    enDevStatus           - Device status                                                                           **
**    stStats               - Statistics (e.g. RxPacketNo, BroadcastNo)                                               **
***********************************************************************************************************************/
typedef struct STag_Eth_HwStatusTypeEtnf
{
  uint32 ulDescTableAddr;
  uint32 aaBufTxCnt[ETH_TXQ_NUM];
  uint32 aaHeadTxDesc[ETH_TXQ_NUM];
  uint32 aaLastTxDesc[ETH_TXQ_NUM];
  uint32 aaNextRxDesc[ETH_RXQ_NUM];
  Eth_OptionType enRxBeTimestamp;
  Eth_OptionType enRxSTimestamp;
  uint32 aaRxBeQueueBuf[ETH_RX_BUF_TOTAL];
  uint32 aaRxNcQueueBuf[ETH_RX_BUF_TOTAL];
  uint32 aaRxSQueueBuf[ETH_RXQ_NUM][ETH_RX_BUF_TOTAL];
  Eth_OpStatusType enDevStatus;
  #if (ETH_REGISTER_CHECK_RUNTIME == STD_ON)
  /* Backup of the value of ECMR register, used for the verification */
  uint32 ulECMRCopy;
  /* Whether register error is detected by the ISR or the MainFunction */
  boolean blErrDetected;
  /* Whether the DEM error of register corruption is already reported */
  boolean blErrReported;
  #endif
} Eth_HwStatusTypeEtnf;

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/
#if (ETH_QOS_SUPPORT == STD_ON)
/* Tx Queue Shaper */
typedef struct STag_Eth_QueueShaperType
{
  Eth_TxQueuePolicyType enTxQPolicy;
  uint32 ulCiv; /* Credit Increment value should be [1..65535] */
  sint32 slCdv; /* Credit Decrement value should be [-65536 ..-1] */
} Eth_QueueShaperType;
#endif

/* Tx Queue Struct */
typedef struct STag_Eth_TxQueueTypeEtnf                                                                                 /* PRQA S 3630 # JV-01 */
{
  #if (ETH_QOS_SUPPORT == STD_ON)
  Eth_QueueShaperType stTxQueueShaper;
  #endif
  uint16 usEthTxQueueBufs;
  uint8 ucEthTxQueueId;
} Eth_TxQueueTypeEtnf;

/* Rx Queue struct */
typedef struct STag_Eth_RxQueueTypeEtnf                                                                                 /* PRQA S 3630 # JV-01 */
{
  uint16 usEthRxQueueBufs;
  uint8 ucEthRxQueueId;
  #if (ETH_STREAM_FILTERING == STD_ON)
  uint8 aaEthPatternStream[8];
  #endif
} Eth_RxQueueTypeEtnf;

typedef struct STag_Eth_QueueConfigTypeEtnf
{
  P2CONST(Eth_TxQueueTypeEtnf, TYPEDEF, ETH_APPL_CONST) pTxQueueConfig;
  P2CONST(Eth_RxQueueTypeEtnf, TYPEDEF, ETH_APPL_CONST) pRxQueueConfig;
  uint8 ucNumberOfTxQueue;
  uint8 ucNumberOfRxQueue;
} Eth_QueueConfigTypeEtnf;

#if (ETH_QOS_SUPPORT == STD_ON)
/*******Traffic Priorities Table****************/
typedef struct STag_Eth_PriorityMappingType                                                                             /* PRQA S 3630 # JV-01 */
{
  uint8 ucEthCtrlPriorityValue;
  uint8 ucEthCtrlTxQueueId;
} Eth_PriorityMappingType;

typedef struct STag_Eth_CtrlPriorityType
{
  /* Array to collect all configured Prorities */
  P2CONST(Eth_PriorityMappingType, TYPEDEF, ETH_APPL_CONST) pPriorityTable;
  /* Store the number of Traffic Priorities configured */
  uint8 ucNumberOfPriorities;
  /* Default Tx Queue for unmapped traffic */
  uint8 ucDflTxQueue;
} Eth_CtrlPriorityType;
#endif

/* ETNF LLDriver specific hardware configuration */
typedef struct STag_Eth_ETNFConfigType
{
  Eth_QueueConfigTypeEtnf stQueueConfig;
  Eth_RxConfigTypeEtnf stRxConfig;
  Eth_TxQPrioType enTxConfig;
  Eth_OptionType enEcbs;
  #if (ETH_QOS_SUPPORT == STD_ON)
  Eth_CtrlPriorityType stCtrlPriority;
  #endif
} Eth_ETNFConfigType;

/* Contains data to be used for register read/write check */
typedef struct STag_Eth_ETNFCheckRWRegType
{
  uint32 ulOffset;
  uint32 ulMaskValue;
  uint32 ulWritePattern0;
  uint32 ulWritePattern1;
} Eth_ETNFCheckRWRegType;

/* Contains data to be used for register read check */
typedef struct STag_Eth_ETNFCheckRORegType
{
  uint32 ulOffset;
  uint32 ulMaskValue;
  uint32 ulExpectedValue;
} Eth_ETNFCheckRORegType;

/***********************************************************************************************************************
**  Type: Eth_EtherFrameTypeEtnf                                                                                      **
**                                                                                                                    **
**  Ethernet Frame structure                                                                                          **
**                                                                                                                    **
**  Members:                                                                                                          **
**    ucDstAddr    - Destination address                                                                              **
**    ucSrcAddr    - Source address                                                                                   **
**    ucFrameType  - EtherType                                                                                        **
**    ucPayload    - Payload                                                                                          **
***********************************************************************************************************************/
typedef struct STag_Eth_EtherFrameTypeEtnf
{
  uint8 ucDstAddr[6];
  uint8 ucSrcAddr[6];
  uint8 ucFrameType[2];
  Eth_DataType ucPayload[1];                                                                                            /* PRQA S 1039 # JV-01 */
} Eth_EtherFrameTypeEtnf;

/* ETNF register definitions */
typedef struct STag_Eth_ETNFRegType                                                                                     /* PRQA S 3630 # JV-01 */
{
  uint32 ulCCC;             /* +0000 CCC       */
  uint32 ulDBAT;            /* +0004 DBAT      */
  uint32 ulDLR;             /* +0008 DLR       */
  uint32 ulCSR;             /* +000C CSR       */
  uint32 ulCDAR[22];        /* +0010 CDAR      */
  uint32 aaReserved0[8];    /* Reserved        */
  uint32 ulESR;             /* +0088 ESR       */
  uint32 ulRIMR;            /* +008C RIMR      */
  uint32 ulRCR;             /* +0090 RCR       */
  uint32 ulRQC[5];          /* +0094 RQC       */
  uint32 aaReserved1[2];    /* Reserved        */
  uint32 ulRPC;             /* +00B0 RPC       */
  uint32 aaReserved2[2];    /* Reserved        */
  uint32 ulUFCW;            /* +00BC UFCW      */
  uint32 ulUFCS;            /* +00C0 UFCS      */
  uint32 ulUFCV[5];         /* +00C4 UFCV      */
  uint32 aaReserved3[2];    /* Reserved        */
  uint32 ulUFCD[5];         /* +00E0 UFCD      */
  uint32 aaReserved4[2];    /* Reserved        */
  uint32 ulSFO;             /* +00FC SFO       */
  uint32 ulSFP[32];         /* +0100 SFP       */
  uint32 aaReserved5[14];   /* Reserved        */
  uint32 ulSFV[2];          /* +01B8 SFV       */
  uint32 ulSFM[2];          /* +01C0 SFM       */
  uint32 ulSFL;             /* +01C8 SFL       */
  uint32 ulPCRC;            /* +01CC PCRC      */
  uint32 aaReserved6[76];   /* Reserved        */
  uint32 ulTGC;             /* +0300 TGC       */
  uint32 ulTCCR;            /* +0304 TCCR      */
  uint32 ulTSR;             /* +0308 TSR       */
  uint32 ulReserved7;       /* Reserved        */
  uint32 ulTFA0;            /* +0310 TFA0      */
  uint32 ulTFA1;            /* +0314 TFA1      */
  uint32 ulTFA2;            /* +0318 TFA2      */
  uint32 ulVRR;             /* +031C VRR       */
  uint32 ulCIVR[2];         /* +0320 CIVR      */
  uint32 ulCDVR[2];         /* +0328 CDVR      */
  uint32 ulCUL[2];          /* +0330 CUL       */
  uint32 ulCLL[2];          /* +0338 CLL       */
  uint32 aaReserved8[4];    /* Reserved        */
  uint32 ulDIC;             /* +0350 DIC       */
  uint32 ulDIS;             /* +0354 DIS       */
  uint32 ulEIC;             /* +0358 EIC       */
  uint32 ulEIS;             /* +035C EIS       */
  uint32 ulRIC0;            /* +0360 RIC0      */
  uint32 ulRIS0;            /* +0364 RIS0      */
  uint32 ulRIC1;            /* +0368 RIC0      */
  uint32 ulRIS1;            /* +036C RIS0      */
  uint32 ulRIC2;            /* +0370 RIC0      */
  uint32 ulRIS2;            /* +0374 RIS0      */
  uint32 ulTIC;             /* +0378 TIC       */
  uint32 ulTIS;             /* +037C TIS       */
  uint32 ulISS;             /* +0380 ISS       */
  uint32 ulCIE;             /* +0384 CIE       */
  uint32 ulRIC3;            /* +0388 RIC3      */
  uint32 ulRIS3;            /* +038C RIS3      */
  uint32 ulGCCR;            /* +0390 GCCR      */
  uint32 ulGMTT;            /* +0394 GMTT      */
  uint32 ulGPTC;            /* +0398 GPTC      */
  uint32 ulGTI;             /* +039C GTI       */
  uint32 ulGTO[3];          /* +03A0 GTO       */
  uint32 ulGIC;             /* +03AC GIC       */
  uint32 ulGIS;             /* +03B0 GIS       */
  uint32 ulReserved9;       /* Reserved        */
  uint32 ulGCT[3];          /* +03B8 GCT       */
  uint32 ulGSR;             /* +03C4 GSR       */
  uint32 aaReserved10[6];   /* Reserved        */
  uint32 ulGPTF[4];         /* +03E0 GPTF      */
  uint32 aaReserved11[28];  /* Reserved        */
  uint32 ulRIE0;            /* +0460 RIE0      */
  uint32 ulRID0;            /* +0464 RID0      */
  uint32 ulRIE1;            /* +0468 RIE1      */
  uint32 ulRID1;            /* +046C RID1      */
  uint32 ulRIE2;            /* +0470 RIE2      */
  uint32 ulRID2;            /* +0474 RID2      */
  uint32 ulTIE;             /* +0478 TIE       */
  uint32 ulTID;             /* +047C TID       */
  uint32 aaReserved12[2];   /* Reserved        */
  uint32 ulRIE3;            /* +0488 RIE3      */
  uint32 ulRID3;            /* +048C RID3      */
  uint32 aaReserved13[28];  /* Reserved        */
  uint32 ulECMR;            /* +0500 ECMR      */
  uint32 ulReserved14;      /* Reserved        */
  uint32 ulRFLR;            /* +0508 RFLR      */
  uint32 ulReserved15;      /* Reserved        */
  uint32 ulECSR;            /* +0510 TIS       */
  uint32 ulReserved16;      /* Reserved        */
  uint32 ulECSIPR;          /* +0518 ECSIPR    */
  uint32 ulReserved17;      /* Reserved        */
  uint32 ulPIR;             /* +0520 PIR       */
  uint32 aaReserved18[12];   /* Reserved       */
  uint32 ulAPFTP;           /* +0554 APFTP     */
  uint32 ulMPR;             /* +0558 MPR       */
  uint32 ulPFTCR;           /* +055C PFTCR     */
  uint32 ulPFRCR;           /* +0560 PFRCR     */
  uint32 ulTPAUSER;         /* +0564 TPAUSER   */
  uint32 ulPFTTCR;          /* +0568 PFTTCR    */
  uint32 aaReserved19[21];  /* Reserved        */
  uint32 ulMAHR;            /* +05C0 MAHR      */
  uint32 ulReserved20;      /* Reserved        */
  uint32 ulMALR;            /* +05C8 MALR      */
  uint32 aaReserved21[77];  /* Reserved        */
  uint32 ulTROC;            /* +0700 TROC      */
  uint32 aaReserved22;      /* Reserved        */  
  uint32 ulDCDC;            /* +0708 DCDC      */ 
  uint32 aaReserved23;      /* Reserved        */
  uint32 ulLCC;             /* +0710 LCC       */
  uint32 aaReserved24[11];  /* Reserved        */        
  uint32 ulCEFCR;           /* +0740 CEFCR     */
  uint32 ulReserved25;      /* Reserved        */
  uint32 ulFRECR;           /* +0748 FRECR     */
  uint32 ulReserved26;      /* Reserved        */
  uint32 ulTSFRCR;          /* +0750 TSFRCR    */
  uint32 ulReserved27;      /* Reserved        */
  uint32 ulTLFRCR;          /* +0758 TLFRCR    */
  uint32 ulReserved28;      /* Reserved        */
  uint32 ulRFCR;            /* +0760 RFCR      */
  uint32 aaReserved29[5];   /* Reserved        */
  uint32 ulMAFCR;           /* +0778 MAFCR     */
  uint32 aaReserved30[545]; /* Reserved        */
} Eth_ETNFRegType;

typedef struct STag_Eth_ETNFEICRegType                                                                                  /* PRQA S 3630 # JV-01 */
{
  uint16 usDATA; /* +0000 DATA      */
  uint16 usERR;  /* +0002 ERR       */
  uint16 usMNG;  /* +0004 MNG       */
  uint16 usMAC;  /* +0006 MAC       */
} Eth_ETNFEICRegType;

typedef struct STag_Eth_ETNFT1SRegType                                                                                  /* PRQA S 3630 # JV-01 */
{
  uint32 ulETNFT1SCTL0;   /* +0000 T1SCTL0  */
} Eth_ETNFT1SRegType;

/* Mask patterns to be used for the register corruption checking */
#define ETH_ETNF_ECMR_CHECK_MASK 0x04BF02C3UL

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/


/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/
#define ETH_START_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"

extern FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_ETNF_HwInit(CONST(uint32, AUTOMATIC) LulCtrlIdx);
extern FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_ETNF_HwDisableController(CONST(uint32, AUTOMATIC) LulCtrlIdx);
extern FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_ETNF_HwEnableController(CONST(uint32, AUTOMATIC) LulCtrlIdx);

extern FUNC(Std_ReturnType, ETH_PRIVATE_CODE)
    Eth_ETNF_HwTransmit(CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulBufIdx,
                   CONST(uint32, AUTOMATIC) LulLenByte, CONST(boolean, AUTOMATIC) LblConfirmation);

#if (ETH_GET_COUNTER_VALUES_API == STD_ON)
extern FUNC(void, ETH_PRIVATE_CODE)
    Eth_ETNF_HwGetCounterValues(CONST(uint32, AUTOMATIC) LulCtrlIdx,
                           CONSTP2VAR(Eth_CounterType, AUTOMATIC, ETH_APPL_DATA) LpCounterPtr);                         /* PRQA S 3432 # JV-01 */
#endif

#if (ETH_GET_RX_STATS_API == STD_ON)
extern FUNC(void, ETH_PRIVATE_CODE) Eth_ETNF_HwGetRxStats(CONST(uint32, AUTOMATIC) LulCtrlIdx,
                     CONSTP2VAR(Eth_RxStatsType, AUTOMATIC, ETH_APPL_DATA) LpRxStats);                                  /* PRQA S 3432 # JV-01 */
#endif

#if (ETH_GET_TX_STATS_API == STD_ON)
extern FUNC(void, ETH_PRIVATE_CODE) Eth_ETNF_HwGetTxStats(CONST(uint32, AUTOMATIC) LulCtrlIdx,
                     CONSTP2VAR(Eth_TxStatsType, AUTOMATIC, ETH_APPL_DATA) LpTxStats);                                  /* PRQA S 3432 # JV-01 */
#endif

#if (ETH_GET_TX_ERROR_COUNTER_VALUES_API == STD_ON)
extern FUNC(void, ETH_PRIVATE_CODE) Eth_ETNF_HwGetTxErrorCounterValues(
    CONST(uint32, AUTOMATIC) LulCtrlIdx,
    CONSTP2VAR(Eth_TxErrorCounterValuesType, AUTOMATIC, ETH_APPL_DATA) LpTxErrorCounterValues);                         /* PRQA S 3432 # JV-01 */
#endif
extern FUNC(void, ETH_PRIVATE_CODE) Eth_ETNF_HwMainFunction(CONST(uint32, AUTOMATIC) LulCtrlIdx);
extern FUNC(void, ETH_PRIVATE_CODE) Eth_ETNF_HwTxConfirmation(CONST(uint32, AUTOMATIC) LulCtrlIdx);

#if (ETH_CTRL_ENABLE_RX_POLLING == STD_ON)
#if (ETH_AR_VERSION >= ETH_AR_431_VERSION)                                                                              
extern FUNC(Std_ReturnType, ETH_PRIVATE_CODE)
    Eth_ETNF_HwCheckFifoIndex(CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulQueueIdx);
#endif
#endif

#if (ETH_CTRL_ENABLE_RX_POLLING == STD_ON)
extern FUNC(Eth_RxStatusType, ETH_PRIVATE_CODE)
    Eth_ETNF_HwReceive(CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulQueueIdx);
#endif

#if (ETH_STREAM_FILTERING == STD_ON)
#if (ETH_DEV_ERROR_DETECT == STD_ON)                                                                                    
extern FUNC(Std_ReturnType, ETH_PRIVATE_CODE)
    Eth_HwCheckRxStreamQueueIndex(CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulQueIdx);
#endif
extern FUNC(void, ETH_PRIVATE_CODE)
    Eth_HwUpdateStreamFilter(CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulQueIdx,
                             CONSTP2CONST(uint8, AUTOMATIC, ETH_APPL_DATA) StreamIdPtr);
#endif

#if (ETH_GLOBAL_TIME_SUPPORT == STD_ON)
extern FUNC(Std_ReturnType, ETH_PRIVATE_CODE)
    Eth_ETNF_HwSetIncrementTimeForGptp(CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulIncVal);

extern FUNC(Std_ReturnType, ETH_PRIVATE_CODE)
    Eth_ETNF_HwSetOffsetTimeForGptp(CONST(uint32, AUTOMATIC) LulCtrlIdx,
                               CONSTP2CONST(Eth_TimeStampType, AUTOMATIC, ETH_APPL_DATA) LpTimeOffsetPtr);

FUNC(Std_ReturnType, ETH_PRIVATE_CODE)
    Eth_ETNF_HwGetCurrentTime(CONST(uint32, AUTOMATIC) LulCtrlIdx,
                         CONSTP2VAR(Eth_TimeStampQualType, AUTOMATIC, ETH_APPL_DATA) LpTimeQualPtr,                     /* PRQA S 3432 # JV-01 */
                         CONSTP2VAR(Eth_TimeStampType, AUTOMATIC, ETH_APPL_DATA) LpTimeStampPtr);                       /* PRQA S 3432 # JV-01 */

FUNC(Std_ReturnType, ETH_PRIVATE_CODE)
    Eth_ETNF_HwGetEgressTimeStamp(CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(Eth_BufIdxType, AUTOMATIC) LulBufIdx,
                             CONSTP2VAR(Eth_TimeStampQualType, AUTOMATIC, ETH_APPL_DATA) LpTimeQualPtr,                 /* PRQA S 3432 # JV-01 */
                             CONSTP2VAR(Eth_TimeStampType, AUTOMATIC, ETH_APPL_DATA) LpTimeStampPtr);                   /* PRQA S 3432 # JV-01 */

FUNC(Std_ReturnType, ETH_PRIVATE_CODE)
    Eth_ETNF_HwGetIngressTimeStamp(CONST(uint32, AUTOMATIC) LulCtrlIdx,
                              CONSTP2CONST(Eth_DataType, AUTOMATIC, ETH_APPL_DATA) LpDataPtr,
                              CONSTP2VAR(Eth_TimeStampQualType, AUTOMATIC, ETH_APPL_DATA) LpTimeQualPtr,                /* PRQA S 3432 # JV-01 */
                              CONSTP2VAR(Eth_TimeStampType, AUTOMATIC, ETH_APPL_DATA) LpTimeStampPtr);                  /* PRQA S 3432 # JV-01 */
#endif
#if (ETH_CTRL_ENABLE_MII == STD_ON)
extern FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_HwWriteMiiBit(
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulBit);
extern FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_HwReadMiiBit(
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONSTP2VAR(uint16, AUTOMATIC, ETH_APPL_DATA) LpRegValPtr);                       /* PRQA S 3432 # JV-01 */
#endif
#define ETH_STOP_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"

#endif /* !ETH_ETNC_LLDRIVER_H_ */
#endif /* ETH_MACRO_ETNF == STD_ON */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
