/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Eth_ETNE_LLDriver.h                                                                                 */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2024, 2025 Renesas Electronics Corporation. All rights reserved.                                               */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains ETNE specific definitions of Eth Driver Component.                                              */
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
 * 2.3.1: 31/03/2025    : Change precompile Eth_Gwca_TSDIS_Common_Isr by ETH_GWCA0_TSDATA_ISR
 *                      : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 * 2.3.0: 28/02/2025    : - As per ticket ARDAACJ-676:
 *                        + ETH_RACE_PORT_GWCA0 from 0x00000008UL to 0x00000004UL
 *                        - As per ticket ARDAACJ-665:
 *                        + Change ETH_RACE_AXI_CHAIN_N from 128UL to 64UL
 *                        + Change ETH_GWCA_AXI_RINC_N from 8UL to 4UL
 *                        + Change ETH_GWCA_AXI_TLIM_N from 32UL to 8UL
 *                        + ETH_RACE_AXI_CHAIN_RLMIN_N from 96UL to 56UL
 *                        + Change ETH_RSW2_RMAC_MPIC_FHDM from 0x00000080UL to 0x00000001UL
 *                        + Remove the macro ETH_RSW2_RMAC_MPIC_PIS_XGMII
 *                        + Add the new macro ETH_ETNE_MLBC_CONFIG
 *                        + Update the struct to correctly support the U2BxE device: Eth_ETNEConfigType, 
 *                        Eth_RSW2_TOPRegType, Eth_RSW2_COMARegType, Eth_RSW2_MFWDRegType, Eth_RSW2_GWCARegType, 
 *                        Eth_RSW2_ETHARegType, Eth_RSW2_RMACRegType, Eth_ETNE_PWRCTLRegType
 *                        - As per ticket ARDAACJ-696:
 *                        + Add the new element ulMaxFrameSize to Eth_RxConfigType and remove it from Eth_RxQueueType
 *                        - As per ticket ARDAACJ-680:
 *                        + Add new struct Eth_ETNE_EICRegType, Eth_ETNE_INTSMRegType, Eth_RSW2_IntRegType, 
 *                        Eth_InterruptHandlingType
 *                        + Add new macro ETH_SGOPMS_DATA_LINKUP, ETH_SGOPMS_STATE_MASK, ETH_SGOPMS_DATA_COM, 
 *                        ETH_SGOPMS_XMIT_MASK, ETH_SGOPMS_SPEED_MASK, ETH_INTSM_COMA_ERR_MASK, 
 *                        ETH_INTSM_GWCA0_ERR_MASK, ETH_INTSM_ETHA01_ERR_MASK, ETH_INTSM_ETHA0_ERR_MASK, 
 *                        ETH_INTSM_ETHA1_ERR_MASK, ETH_INTSM_GWDIS0_MASK, ETH_INTSM_GWDIS1_MASK, 
 *                        ETH_INTSM_GWDIS01_MASK, ETH_INTSM_TSS_MASK, ETH_INTSM_SGMII01_MASK, ETH_INTSM_SGMII0_MASK, 
 *                        ETH_INTSM_SGMII1_MASK
 *                        - Update to correct memory section to ETH_CODE_FAST for functions: 
 *                        + Eth_Gwca_DIS_Common_Isr, Eth_Gwca_TSDIS_Common_Isr, Eth_Gwca_ERR_Common_Isr,
 *                        Eth_Coma_ERR_Common_Isr, Eth_Etha_ERR_Common_Isr, Eth_Etha_SGMII_Common_Isr
 * 2.2.0: 31/12/2024    : Update SW-VERSION for Ver22.02.00(D) U2Bx Final Release
 * 2.1.2: 31/10/2024    : Increase SW-VERSION to 2.1.2
 * 2.1.1: 22/07/2024    : Update QAC message
 *        15/07/2024    : Add ETH_RSW2_RMAC_MPIC_FHDM = 0x00000080UL and Add ETH_RSW2_RMAC_MPIC_10MB = 0x00000000UL
 *        19/06/2024    : Add define Eth_ETNE_HwGetEgressTimeStamp and Eth_ETNE_HwGetIngressTimeStamp
 *        31/05/2024    : Initial Version
 */
/**********************************************************************************************************************/
#ifndef ETH_ETNE_LLDRIVER_H
#define ETH_ETNE_LLDRIVER_H

#include "Std_Types.h"
#include "Eth_Types.h"
#include "Eth_Util.h"
#include "Os.h"
#include <rh850_Types.h>

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define ETH_ETNE_AR_RELEASE_MAJOR_VERSION    ETH_AR_RELEASE_MAJOR_VERSION
#define ETH_ETNE_AR_RELEASE_MINOR_VERSION    ETH_AR_RELEASE_MINOR_VERSION
#define ETH_ETNE_AR_RELEASE_REVISION_VERSION ETH_AR_RELEASE_REVISION_VERSION

/* Module Software version information */
#define ETH_ETNE_SW_MAJOR_VERSION            ETH_SW_MAJOR_VERSION
#define ETH_ETNE_SW_MINOR_VERSION            ETH_SW_MINOR_VERSION

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:1055)    : [C99] The keyword 'inline' has been used.                                                    */
/* Rule                : MISRA C:2012 Dir-1.1, Rule-1.2                                                               */
/* JV-01 Justification : In this case, inline functions are considered more optimized for ECODE than function-like    */
/*                       macros. Usage of inline functions is accepted.                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3630)    : The implementation of this struct/union type should be hidden.                               */
/* Rule                : MISRA C:2012 Dir-4.8                                                                         */
/* JV-01 Justification : The pointers point to this type are dereferenced in other .c files, so this                  */
/*                       implementation should not be hidden.                                                         */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0635)    : Bit-field %s in %s has been declared with a type not explicitly supported.                   */
/* Rule                : CERTCCM INT12, MSC14, MISRA C:2012 Dir-1.1,  Rule-1.2, Rule-6.1                              */
/* JV-01 Justification : To access bit wise from register.                                                            */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0750)    : A union type specifier has been defined.                                                     */
/* Rule                : MISRA C:2012 Rule-19.2, CWE Rule CWE-843                                                     */
/* JV-01 Justification : This union type is used for descriptor accessing and there is no issue with this usage       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE Rule CWE-398, CWE-569                                            */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is accepted. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0639)    : [E] Treating array of length one as potentially flexible member.                             */
/* Rule                : MISRA-C:2012 Dir 1.1                                                                         */
/* JV-01 Justification : This warning does not indicate a mistake in the code, it is a message to call attention to   */
/*                       the processing power of the compiler. Because the compiler in use has been confirmed to have */
/*                       the ability to handle this, no problem.                                                      */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:3383)    : Cannot identify wraparound guard for unsigned arithmetic expression.                         */
/* Rule                : CERTCCM INT30                                                                                */
/* JV-01 Justification : Wraparound can't be occur in this unsigned integer arithmetic so there is no need to add a   */
/*                       wraparound guard here.                                                                       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:3384)    : Cannot identify wraparound guard for dependent unsigned arithmetic expression.               */
/* Rule                : CERTCCM INT30                                                                                */
/* JV-01 Justification : Wraparound can't be occur in this unsigned integer arithmetic so there is no need to add a   */
/*                       wraparound guard here.                                                                       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:4395)    : A composite expression of 'essentially floating' type (double) is being cast to a different  */
/*                       type category, 'unsigned'.                                                                   */
/* Rule                : MISRA C:2012 Rule-10.8                                                                       */
/* JV-01 Justification : This calculation is handled with care to preserve the accuracy of the result. It is confirmed*/
/*                       that there is no problem with this calculation.                                              */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
//* Message (3:4394)    : A composite expression of 'essentially unsigned' type (unsigned long) is being cast to a     */
/*                       different type category, 'floating'.                                                         */
/* Rule                : MISRA C:2012 Rule-10.8, CWE Rule CWE-136                                                     */
/* JV-01 Justification : This calculation is handled with care to preserve the accuracy of the result. It is confirmed*/
/*                       that there is no problem with this calculation.                                              */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (7:0275)    : [U] Floating value is out of range for conversion to destination type.                       */
/* Rule                : CERTCCM MSC15, MISRA C:2012 Rule-1.3, CWE Rule CWE-682, CWE-758                              */
/* JV-01 Justification : This calculation is handled with care to preserve the accuracy of the result. It is confirmed*/
/*                       that there is no problem with this calculation.                                              */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (8:0644)    : [C] Width of bit-field must be no bigger than the width of an 'int'.                         */
/* Rule                : MISRA C:2012 Rule-1.1, CWE Rule CWE-747                                                      */
/* JV-01 Justification : This is specific for memory accessing and there is no issue with this usage.                 */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:1039)    : [E] Treating array of length one as potentially flexible member.                             */
/* Rule                : CERTCCM DCL38, MISRA C:2012 Dir-1.1, Rule-1.2                                                */
/* JV-01 Justification : Use array of length as the final member has no problem by manual reviewing.                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3472)    : All toplevel uses of this function-like macro look like they could be replaced by            */
/*                       equivalent function calls.                                                                   */
/* Rule                : MISRA C:2012 Dir-4.9                                                                         */
/* JV-01 Justification : This message indicates that a candidate macro may be suitable for replacement by a           */
/*                       function, based on an actual call-site and the arguments passed to it there. It not affect   */
/*                       to driver operation and can be accepted                                                      */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                             Switching Mode type                                                                    **
***********************************************************************************************************************/
#define ETH_SWMODE_ENDSTATION                           0
#define ETH_SWMODE_SWITCH                               1

/***********************************************************************************************************************
**                            HW specific parameters referred from the upper-level driver                             **
***********************************************************************************************************************/
/* Cache Line size */
#define ETH_CACHE_LINE_SIZE     (uint32)(32)
/* TxRx buffer length cache align */
#define ETH_BUF_LEN_CACHE_ALIGN(x) \
  (((uint32)x) + \
  (ETH_CACHE_LINE_SIZE - ((uint32)x % ETH_CACHE_LINE_SIZE)))

#define ETH_CPUCLK_MHZ_ETNE          1066UL
#define ETH_NS2HZ(nano_sec)     ((ETH_CPUCLK_MHZ_ETNE * (nano_sec)) / 1000UL)                                           /* PRQA S 3472 # JV-01 */
#define ETH_HZ2NS(clock_hz)     (1000000000UL / (clock_hz))                                                             /* PRQA S 3472 # JV-01 */

/* Caculate gPTP timer increment value */
#define ETH_GPTP_SET_PTPTIVC_50MHZ        0xA0000000UL
#define ETH_GPTP_SET_PTPTIVC_100MHZ       0x50000000UL
#define ETH_GPTP_SET_PTPTIVC_200MHZ       0x28000000UL
#define ETH_GPTP_SET_PTPTIVC_320MHZ       0x19000000UL
#define ETH_GPTP_SET_PTPTIVC_400MHZ       0x14000000UL

/* Minimum payload length allowed by the HW */
#define ETH_MIN_PAYLOAD_SIZE            2UL

/* Maximum payload size without GWCA's frame splitting */
#define ETH_GWCA_MAX_PAYLOAD_SIZE       2048UL

/* gPTP timer MAX Ctroler */
#define ETH_GPTP_MAX_CTRLS_SUPPORTED           2UL

/* Use gPTP timer domain 1 */
#define ETH_GPTP_TIMER_DOMAIN           0U

/* Use AVTP timer domain 1 */
#define ETH_AVTP_TIMER_DOMAIN           0U

/* Enable gPTP timer domain 1 */
#define ETH_GPTP_TIMER_DOMAIN_ENABLE   1UL
#define ETH_GPTP_TIMER_DOMAIN_MASK     (1UL << ETH_GPTP_TIMER_DOMAIN)

#define ETH_GPTP_OFFSET_NANOSEC_MAXVALUE 0x3B9AC9FFUL

/*******************************************************************************
** Descriptor Types                                                           **
*******************************************************************************/
#define ETH_DESC_LINKFIX_RSW2     0U
#define ETH_DESC_FEMPTY_ND        3U
#define ETH_DESC_FEMPTY           4U
#define ETH_DESC_FSINGLE          8U
#define ETH_DESC_LINK             14U

/*******************************************************************************
** Descriptor Attribute Types                                                 **
*******************************************************************************/
#define ETH_TX_DESCR_TSUN_OFFSET  64UL   /* offset = 256 / maximum port */
#define ETH_TX_DESCR_TSUN_MASK    0x000000FFUL

/*******************************************************************************
**  Size of descriptor                                                        **
*******************************************************************************/
#define ETH_BASIC_DESC_SIZE        8UL    /* Basic descriptor size(in byte) */
#define ETH_TS_DESC_SIZE          16UL    /* Timestamp descriptor size(in byte) */
#define ETH_EXT_TX_DIR_DESC_SIZE       16UL    /* Extended TX Direct descriptor size(in byte) */
#if (ETH_GLOBAL_TIME_SUPPORT == STD_ON)
#define ETH_EXT_RX_ETH_TS_DESC_SIZE    24UL    /* Extended RX Ethernet TimeStamp descriptor size(in byte) */
#define ETH_EXT_RX_ETH_DESC_SIZE       ETH_EXT_RX_ETH_TS_DESC_SIZE
#else
#define ETH_EXT_RX_ETH_DESC_SIZE       16UL    /* Extended RX Ethernet descriptor size(in byte) */
#endif

/*******************************************************************************
**   General Ethernet MAC Address Size                                        **
*******************************************************************************/
#define ETH_MACADDR_SIZE                  6UL
/* Padding to align the PAYLOAD part of the frame with 4Byte alignment */
#define ETH_RX_PAYLOAD_PADDING            (((sizeof(Eth_BufIdxType) + ETH_HEADER_SIZE + 4U) / 4U * 4U) - \
                                           (sizeof(Eth_BufIdxType) + ETH_HEADER_SIZE))
/* Padding to align the PAYLOAD part of the frame with 4Byte alignment */
#define ETH_TX_PAYLOAD_PADDING            (((sizeof(Eth_BufHandlerType) + ETH_HEADER_SIZE + 4U) / 4U * 4U) - \
                                           (sizeof(Eth_BufHandlerType) + ETH_HEADER_SIZE)) 


/*******************************************************************************
** Descriptor related                                                         **
*******************************************************************************/
#define ETH_CYCLIC_DESC_NUM               1U

/* The TS descriptor must be set to twice the number of transmit buffers */
#if defined ETH_TX_BUF_TOTAL_3
#define ETH_MAX_TS_DESCRIPTOR ((ETH_TX_BUF_TOTAL_0 + ETH_TX_BUF_TOTAL_1 + ETH_TX_BUF_TOTAL_2 + \
                                ETH_TX_BUF_TOTAL_3) * 2UL)
#elif defined ETH_TX_BUF_TOTAL_2
#define ETH_MAX_TS_DESCRIPTOR ((ETH_TX_BUF_TOTAL_0 + ETH_TX_BUF_TOTAL_1 + ETH_TX_BUF_TOTAL_2) * 2UL)
#elif defined ETH_TX_BUF_TOTAL_1
#define ETH_MAX_TS_DESCRIPTOR ((ETH_TX_BUF_TOTAL_0 + ETH_TX_BUF_TOTAL_1) * 2UL)
#else
#define ETH_MAX_TS_DESCRIPTOR ((ETH_TX_BUF_TOTAL_0) * 2UL)
#endif

/*******************************************************************************
** Number of Tx/Rx queues
*******************************************************************************/
#define ETH_TXQ_NUM_RSW2               8UL     /* Number of tx queue per port */
#define ETH_RXQ_NUM_RSW2               32UL     /* Number of rx queue per port */

/*******************************************************************************
** Number of Tx/Rx queues
*******************************************************************************/
#define ETH_TAS_ENTRY_NUM     8UL       /* Maximum TAS entry number */

/*******************************************************************************
** Mask for the Status Register
*******************************************************************************/

/* GWCA Mode values in GWMC register */
#define ETH_RSW2_GWCA_RESET_MODE       0x00000000UL
#define ETH_RSW2_GWCA_DISABLE_MODE     0x00000001UL
#define ETH_RSW2_GWCA_CONFIG_MODE      0x00000002UL
#define ETH_RSW2_GWCA_OPERATION_MODE   0x00000003UL

/* ETHA Mode values in EAMC register */
#define ETH_RSW2_ETHA_RESET_MODE       0x00000000UL
#define ETH_RSW2_ETHA_DISABLE_MODE     0x00000001UL
#define ETH_RSW2_ETHA_CONFIG_MODE      0x00000002UL
#define ETH_RSW2_ETHA_OPERATION_MODE   0x00000003UL

/* MAC reception frame size configuration for e-frames */

/* MAC reception frame size configuration for p-frames */

/* MAC Timestamp reception configuration */

/* MAC reception address filter configuration */

/* AXI Transmit Status */

/* AXI Receive Status */

/* Rx descriptor full Status */

/*******************************************************************************
** RSW2                                                                       **
*******************************************************************************/
/* R-ACE parameters for ETNE and depended parameter */
#define ETH_RACE_AXI_CHAIN_N            64UL
#define ETH_RACE_PORT_TSNA_N            2UL
#define ETH_RACE_PORT_GWCA_N            1UL
#define ETH_RACE_LTH_REMAP_N            32UL
#define ETH_RACE_PTP_TN                 2UL
#define ETH_RACE_PFL_TWBF_N             48UL
#define ETH_RACE_PFL_FOBF_N             48UL
#define ETH_RACE_PFL_RAGF_N             16UL
#define ETH_RACE_PFL_CADF_N             64UL
#define ETH_RACE_PFL_CFMF_N             7UL
#define ETH_RACE_PSFP_GATE_N            8UL
#define ETH_RACE_PAS_LVL_N              2UL
#define ETH_RACE_PORT_N                 (ETH_RACE_PORT_TSNA_N+ETH_RACE_PORT_GWCA_N)
#define ETH_RACE_PSFP_MTR_N             32UL
#define ETH_GWCA_AXI_RINC_N             4UL
#define ETH_GWCA_AXI_TLIM_N             8UL
#define ETH_GWCA_FRM_PRIO_N             8UL
#define ETH_ETHA_FRM_PRIO_N             8UL
#define ETH_MEDIA_CAPT_N                2UL
#define ETH_MEDIA_RECV_N                2UL
#define ETH_CYC_COMP_N                  8UL
#define ETH_RACE_AXI_CHAIN_RLMIN_N      56UL

#define ETH_RACE_PORT_TSNA0             0x00000001UL
#define ETH_RACE_PORT_TSNA1             0x00000002UL
#define ETH_RACE_PORT_ETHA0             ETH_RACE_PORT_TSNA0
#define ETH_RACE_PORT_ETHA1             ETH_RACE_PORT_TSNA1
#define ETH_RACE_PORT_GWCA0             0x00000004UL
#define ETH_RACE_PORT_ACPA0             0x00000020UL
#define ETH_RACE_PORT_ALL               ( \
                                          ETH_RACE_PORT_TSNA0 | \
                                          ETH_RACE_PORT_TSNA1 | \
                                          ETH_RACE_PORT_GWCA0 | \
                                          ETH_RACE_PORT_ACPA0 )
#define ETH_RACE_PORT_GWCA              ETH_RACE_PORT_GWCA0
#define ETH_RACE_PORT_NULL              0x00000000UL

#define ETH_RACE_ID_GWCA0               0UL
#define ETH_RACE_ID_GWCA1               1UL
#define ETH_RACE_ID_ETHA0               0UL
#define ETH_RACE_ID_ETHA1               1UL
#define ETH_RACE_ID_ETHA2               2UL
#define ETH_RACE_ID_RMAC0               0UL
#define ETH_RACE_ID_RMAC1               1UL
#define ETH_RACE_ID_RMAC2               2UL

#define ETH_CONV_ETHAID_TO_PORTID(id)   (id)                                                                            /* PRQA S 3472 # JV-01 */
#define ETH_CONV_RMACID_TO_PORTID(id)   (id)                                                                            /* PRQA S 3472 # JV-01 */
#define ETH_CONV_GWCAID_TO_PORTID(id)   (ETH_RACE_PORT_TSNA_N + id)
#define ETH_CONV_PORTID_TO_ETHAID(id)   (id)                                                                            /* PRQA S 3472 # JV-01 */
#define ETH_CONV_PORTID_TO_RMACID(id)   (id)                                                                            /* PRQA S 3472 # JV-01 */
#define ETH_CONV_PORTID_TO_GWCAID(id)   (id - ETH_RACE_PORT_TSNA_N)

/* Port type */
#define ETH_RSW2_PORT_TYPE_GWCA         0UL
#define ETH_RSW2_PORT_TYPE_ETHA         1UL

#define ETH_MAX_GWCA_SUPPORTED          ETH_RACE_PORT_GWCA_N
#define ETH_MAX_TSNA_SUPPORTED          ETH_RACE_PORT_TSNA_N
#define ETH_MAX_RMAC_SUPPORTED          ETH_RACE_PORT_TSNA_N

#define ETH_RSW2_SETCYCLE_START         (uint64)1500000000U
#define ETH_RSW2_64_TO_32_SHIFT         (uint64)32U

/*********
** TOP  **
*********/

/*********
** COMA **
*********/
#define ETH_RSW2_COMA_RCEC_RCE          0x00010000UL
#define ETH_RSW2_COMA_CABPIRM_BPIOG     0x00000001UL
#define ETH_RSW2_COMA_CABPIRM_BPR       0x00000002UL
#define ETH_RSW2_SOFTWARE_RESET_ENABLE  0x00000001UL

#if (ETH_COMA_ERR_ISR == STD_ON)
#define ETH_RSW2_COMA_CAEIE0_BPECCES    0x00000004UL
#define ETH_RSW2_COMA_CAEIE0_DSECCES    0x00000002UL
#define ETH_RSW2_COMA_CAEIE0_PECCES     0x00000001UL
#define ETH_RSW2_COMA_ECC_ERROR_MASK    ( ETH_RSW2_COMA_CAEIE0_BPECCES | \
                                          ETH_RSW2_COMA_CAEIE0_DSECCES | \
                                          ETH_RSW2_COMA_CAEIE0_PECCES )
#endif /* (ETH_COMA_ERR_ISR == STD_ON) */

/*********
** MFWD **
*********/
#define ETH_RSW2_MFWD_FWPC1_DDE             0x00000001UL
#define ETH_RSW2_MFWD_FWPC1_DDSL            0x00000002UL
#define ETH_RSW2_MFWD_FWPC1_DDE_DDSL_MASK   (ETH_RSW2_MFWD_FWPC1_DDE | ETH_RSW2_MFWD_FWPC1_DDSL)
#define ETH_RSW2_MFWD_FWVLANTIM_VLANTIOG    0x00000001UL
#define ETH_RSW2_MFWD_FWVLANTIM_VLANTR      0x00000002UL
#define ETH_RSW2_MFWD_FWLTHTIM_LTHTIOG      0x00000001UL
#define ETH_RSW2_MFWD_FWLTHTIM_LTHTR        0x00000002UL
#define ETH_RSW2_MFWD_FWMACTIM_MACTIOG      0x00000001UL
#define ETH_RSW2_MFWD_FWMACTIM_MACTR        0x00000002UL
#define ETH_RSW2_MFWD_FWL23UTIM_L23UTIOG    0x00000001UL
#define ETH_RSW2_MFWD_FWL23UTIM_L23UTR      0x00000002UL
#define ETH_RSW2_MFWD_FWPGFRIM_GFRIOG       0x00000001UL
#define ETH_RSW2_MFWD_FWPGFRIM_GFRR         0x00000002UL

/*********
** GWCA **
*********/
#define ETH_RSW2_GWCA0                  0UL
#define ETH_RSW2_GWCA1                  1UL

#define ETH_RSW2_GWCA_GWDCC_RX          0x00000000UL
#define ETH_RSW2_GWCA_GWDCC_TX          0x00000800UL
#define ETH_RSW2_GWCA_GWDCC_ETS         0x00000200UL
#define ETH_RSW2_GWCA_GWDCC_EDE         0x00000100UL
#define ETH_RSW2_GWCA_GWDCC_BALR        0x01000000UL
#define ETH_RSW2_GWCA_GWDCC_DCP_MASK    0x00070000UL

#define ETH_RSW2_GWCA_GWDCC_DCP_SET(priority) ((priority << 16UL) & ETH_RSW2_GWCA_GWDCC_DCP_MASK)

#define ETH_RSW2_GWCA_GWMTIRM_MTIOG     0x00000001UL
#define ETH_RSW2_GWCA_GWMTIRM_MTR       0x00000002UL
#define ETH_RSW2_GWCA_GWARIRM_ARIOG     0x00000001UL
#define ETH_RSW2_GWCA_GWARIRM_ARR       0x00000002UL
#define ETH_RSW2_GWCA_GWMS_OPS_MASK     0x00000003UL

#define ETH_RSW2_GWCA_NUM_OF_CHAIN_PER_REG                      32UL

#if (ETH_GWCA0_ERR_ISR == STD_ON)
#define ETH_GWCA_ERR_ISR                STD_ON
#define ETH_RSW2_GWCA_GWEIE0_L23UECCES  0x00000100UL
#define ETH_RSW2_GWCA_GWEIE0_TSECCES    0x00000080UL
#define ETH_RSW2_GWCA_GWEIE0_AECCES     0x00000040UL
#define ETH_RSW2_GWCA_GWEIE0_MECCES     0x00000020UL
#define ETH_RSW2_GWCA_GWEIE0_DSECCES    0x00000010UL
#define ETH_RSW2_GWCA_GWEIE0_PECCES     0x00000008UL
#define ETH_RSW2_GWCA_GWEIE0_TECCES     0x00000004UL
#define ETH_RSW2_GWCA_GWEIE0_DECCES     0x00000002UL
#define ETH_RSW2_GWCA_GWEIE0_AES        0x00000001UL
#define ETH_RSW2_GWCA_DMA_ERROR_MASK    ( ETH_RSW2_GWCA_GWEIE0_AES )
#define ETH_RSW2_GWCA_ECC_ERROR_MASK    ( ETH_RSW2_GWCA_GWEIE0_L23UECCES | \
                                          ETH_RSW2_GWCA_GWEIE0_TSECCES | \
                                          ETH_RSW2_GWCA_GWEIE0_AECCES | \
                                          ETH_RSW2_GWCA_GWEIE0_MECCES | \
                                          ETH_RSW2_GWCA_GWEIE0_DSECCES | \
                                          ETH_RSW2_GWCA_GWEIE0_PECCES | \
                                          ETH_RSW2_GWCA_GWEIE0_TECCES | \
                                          ETH_RSW2_GWCA_GWEIE0_DECCES )
#else /* (ETH_GWCA0_ERR_ISR == STD_ON) */
#define ETH_GWCA_ERR_ISR                STD_OFF
#endif /* (ETH_GWCA0_ERR_ISR == STD_ON) */

/*********
** ETHA **
*********/
#define ETH_RSW2_ETHA_TASRIRM_TASRIOG   0x00000001UL
#define ETH_RSW2_ETHA_TASRIRM_TASRR     0x00000002UL
#define ETH_RSW2_ETHA_EAMS_OPS_MASK     0x00000003UL

#if ((ETH_ETHA0_ERR_ISR == STD_ON) || (ETH_ETHA1_ERR_ISR == STD_ON))
#define ETH_ETHA_ERR_ISR                STD_ON
#define ETH_RSW2_ETHA_EAEIE0_TASGEES    0x00FF0000UL
#define ETH_RSW2_ETHA_EAEIE0_L23UECCES  0x00000010UL
#define ETH_RSW2_ETHA_EAEIE0_DSECCES    0x00000008UL
#define ETH_RSW2_ETHA_EAEIE0_PECCES     0x00000004UL
#define ETH_RSW2_ETHA_EAEIE0_TECCES     0x00000002UL
#define ETH_RSW2_ETHA_EAEIE0_DECCES     0x00000001UL
#define ETH_RSW2_ETHA_ECC_ERROR_MASK    ( ETH_RSW2_ETHA_EAEIE0_TASGEES | \
                                          ETH_RSW2_ETHA_EAEIE0_L23UECCES | \
                                          ETH_RSW2_ETHA_EAEIE0_DSECCES | \
                                          ETH_RSW2_ETHA_EAEIE0_PECCES | \
                                          ETH_RSW2_ETHA_EAEIE0_TECCES | \
                                          ETH_RSW2_ETHA_EAEIE0_DECCES )
#else /* ((ETH_ETHA0_ERR_ISR == STD_ON) || (ETH_ETHA1_ERR_ISR == STD_ON)) */
#define ETH_ETHA_ERR_ISR                STD_OFF
#endif /* ((ETH_ETHA0_ERR_ISR == STD_ON) || (ETH_ETHA1_ERR_ISR == STD_ON)) */

#define ETH_RSW2_ETHA_EATASC_TASCI 0x00000004UL
#define ETH_RSW2_ETHA_EATASC_TASCA 0x00FF0000UL
#define ETH_RSW2_ETHA_EATASGLR_GL  0x80000000UL
#define ETH_RSW2_ETHA_EATASC_TASE  0x00000001UL
#define ETH_RSW2_ETHA_EATASC_TASCC 0x00000002UL

/*********
** RMAC **
*********/
#define ETH_RSW2_RMAC_MPSM_MFF_MDIO     0x00000000UL
#define ETH_RSW2_RMAC_MPSM_MFF_EMDIO    0x00000004UL
#define ETH_RSW2_RMAC_MPSM_POP_READ     0x00004000UL
#define ETH_RSW2_RMAC_MPSM_POP_WRITE    0x00002000UL
#define ETH_RSW2_RMAC_MPSM_PSME         0x00000001UL
#define ETH_RSW2_RMAC_MPIC_PSMCS_BIT    0x007F0000UL
#define ETH_RSW2_RMAC_MPIC_100MB        0x00000008UL
#define ETH_RSW2_RMAC_MPIC_10MB         0x00000000UL
#define ETH_RSW2_RMAC_MPIC_1GB          0x00000010UL
#define ETH_RSW2_RMAC_MPIC_2_5GB        0x00000018UL
#define ETH_RSW2_RMAC_MPIC_MII          0x00000000UL
#define ETH_RSW2_RMAC_MPIC_GMII         0x00000002UL
#define ETH_RSW2_RMAC_MPIC_XGMII        0x00000004UL
#define ETH_RSW2_RMAC_MPIC_PSMC_320MHZ  0x003F0000UL
#define ETH_RSW2_RMAC_MPIC_LSC_BIT      0x00000038UL
#define ETH_RSW2_RMAC_MPIC_PIS_BIT      0x00000007UL
#define ETH_RSW2_RMAC_MPIC_MASK         (ETH_RSW2_RMAC_MPIC_LSC_BIT | \
                                         ETH_RSW2_RMAC_MPIC_PIS_BIT)
#define ETH_RSW2_RMAC_MPIC_PSMCS_MASK   ETH_RSW2_RMAC_MPIC_PSMCS_BIT
#define ETH_RSW2_RMAC_MPIC_FHDM         0x00000001UL
#define ETH_RSW2_RMAC_MPIC_PIS_XGMII    0x00000004UL
#define ETH_RSW2_RMAC_MLVC_PLV          0x00010000UL
#define ETH_RSW2_RMAC_MLVC_LVT          (uint32)(0x09U)
#define ETH_RSW2_RMAC_MLVC_PASE         (0x1UL << 8UL)
#define ETH_RSW2_RMAC_MTRC_TRHFME_ENABLE      0x00000001UL

#define ETH_RSW2_RMAC_MTFFC_PAUSE       0x00000000UL
#define ETH_RSW2_RMAC_MTFFC_PFC         0x00000001UL

#define ETH_RSW2_MPSM_SET(regidx, trcvidx, mode, val) ((uint32) \
  (((uint32)val << 16U) | ((uint32)regidx << 8U) | ((uint32)trcvidx << 3U) | (mode) | \
   (ETH_RSW2_RMAC_MPSM_MFF_MDIO) | (ETH_RSW2_RMAC_MPSM_PSME)))

#define ETH_RSW2_SET_MPSM_PRD_READ(LulRegVal) ((uint16)((LulRegVal) >> 16UL))                                           /* PRQA S 3472 # JV-01 */

/*********
** gPTP **
*********/
#define ETH_RSW2_64_TO_32_LOW  (uint64)0x00000000FFFFFFFFU
#define ETH_RSW2_64_TO_32_HIGH (uint64)0xFFFFFFFF00000000U

/* MAC Loopback configuration */
#define ETH_ETNE_MLBC_CONFIG                  0x00000001UL

/***********************************************************************************************************************
**                                             SGMII related definitions                                              **
***********************************************************************************************************************/
#define ETH_ETNE_WAIT_FOR_SGMII                4000UL /* nanosecond */

#define ETH_ETNE_PIR_MDC                       0x00000001UL
#define ETH_ETNE_PIR_MMD                       0x00000002UL
#define ETH_ETNE_PIR_MDO                       0x00000004UL
#define ETH_ETNE_GECMR_SPEED                   0x00000001UL
#define ETH_ETNE_SGSRST_SRST                   0x00000001UL
#define ETH_ETNE_SGINTM_URDYIM                 0x0002U
#define ETH_ETNE_SGINTM_RDYIM                  0x0001U
#define ETH_ETNE_SGINTS_URDY                   0x0002U
#define ETH_ETNE_SGINTS_RDY                    0x0001U
#define ETH_ETNE_SGINTS_RDY_UNRDY              (ETH_ETNE_SGINTS_RDY | ETH_ETNE_SGINTS_URDY)
#define ETH_ETNE_SGSDS_SUC                     0x04U
#define ETH_ETNE_SGSDS_PWS_ON                  0x03U
#define ETH_ETNE_SGCLKSEL_SEL                  0x01U
#define ETH_ETNE_SGRCIE_RCIE                   0x01U

#define ETH_SGOPMS_DATA_LINKUP                 0x00020012UL
#define ETH_SGOPMS_STATE_MASK                  0x00030012UL
#define ETH_SGOPMS_DATA_COM                    0x00020000UL
#define ETH_SGOPMS_XMIT_MASK                   0x00030000UL
#define ETH_SGOPMS_SPEED_MASK                  0x00000038UL

#define ETH_ETNE_SGOPMC_10M                    0x00000003UL
#define ETH_ETNE_SGOPMC_100M                   0x00000007UL
#define ETH_ETNE_SGOPMC_1G                     0x0000000BUL

#define ETH_INTSM_COMA_ERR_MASK                0x00040000UL
#define ETH_INTSM_GWCA0_ERR_MASK               0x00010000UL
#define ETH_INTSM_ETHA01_ERR_MASK              0x0000C000UL
#define ETH_INTSM_ETHA0_ERR_MASK               0x00008000UL
#define ETH_INTSM_ETHA1_ERR_MASK               0x00004000UL
#define ETH_INTSM_GWDIS0_MASK                  0x00000000UL
#define ETH_INTSM_GWDIS1_MASK                  0x00000001UL
#define ETH_INTSM_GWDIS01_MASK                 0x00000003UL
#define ETH_INTSM_TSS_MASK                     0x00000300UL
#define ETH_INTSM_SGMII01_MASK                 0x00300000UL
#define ETH_INTSM_SGMII0_MASK                  0x00200000UL
#define ETH_INTSM_SGMII1_MASK                  0x00100000UL

/*******************************************************************************
**                      MDIO reletive definitions                             **
*******************************************************************************/

/*******************************************************************************
**                      GTO reletive definitions                              **
*******************************************************************************/

/*******************************************************************************
**                      Macro for the Configuratin                            **
*******************************************************************************/
/* ulFwdVectorId */
#define ETH_FWD_VECTOR_GWCA0 0x00000010UL
#define ETH_FWD_VECTOR_GWCA1 0x00000020UL
#define ETH_FWD_VECTOR_ETHA0 0x00000001UL
#define ETH_FWD_VECTOR_ETHA1 0x00000002UL
#define ETH_FWD_VECTOR_ETHA2 0x00000004UL

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/* TSN frame type */
typedef enum ETag_Eth_TSN_FrameType
{
  ETH_EXPRESS_FRAME,
  ETH_PREEMPTION_FRAME
} Eth_TSN_FrameType;

typedef enum ETag_Eth_TxFragmentType
{
  ETH_FRAGMENT_64_BYTE,
  ETH_FRAGMENT_128_BYTE,
  ETH_FRAGMENT_192_BYTE,
  ETH_FRAGMENT_256_BYTE
} Eth_TxFragmentType;

typedef enum ETag_Eth_TASGateStateType
{
  ETH_TAS_CLOSE,
  ETH_TAS_OPEN
} Eth_TASGateStateType;

typedef enum ETag_Eth_RxExtStatusType
{
  ETH_EXT_RECEIVED = 0,
  ETH_EXT_NOT_RECEIVED,
  ETH_EXT_RECEIVED_MORE_DATA_AVAILABLE,
  ETH_EXT_NOT_RECEIVED_MORE_DATA_AVAILABLE
} Eth_ExtRxStatusType;

/* Credit Based Shaper */
typedef struct STag_Eth_CBSConfigType
{
  uint32 ulCE;
  uint32 ulCIV;    /* Credit Increment Value */
  uint32 ulCUL;    /* Credit Upper Limit */
} Eth_CBSConfigType;

typedef struct STag_Eth_TASEntryType                                                                                    /* PRQA S 3630 # JV-01 */
{
  Eth_TASGateStateType enGateState;
  uint32 ulTimeInterval;
} Eth_TASEntryType;

/***********************************************************
  Type: EthPerQueueRLConfigType

  Structure for Per-queue rate-limiter setting in GWCA register

  Members:
    ulGWRLCiValue - GWCA Rate Limiter Configuration i.
    ulGWRLULCiValue - GWCA Rate limiter upper limit configuration i.
*/
typedef struct STagEth_PerQueRLCfgType
{
  uint32 ulGWRLCiValue;
  uint32 ulGWRLULCiValue;
}Eth_PerQueRLCfgType;

/* Time Aware Shaper */
typedef struct STag_Eth_TASConfigType
{
  Eth_OptionType enTasEnable;
  uint32 ulTxMiniLatency;
  uint32 ulTxJitter;
  P2CONST(Eth_TASEntryType, TYPEDEF, ETH_APPL_CONST) pTasTable;
  uint32 ulNumberOfTasTable;
  uint8 aaEntryNumber[ETH_ETHA_FRM_PRIO_N];
} Eth_TASConfigType;

/* Tx Queue Struct */
typedef struct STag_Eth_TxQueueType                                                                                     /* PRQA S 3630 # JV-01 */
{
  uint32 ulQueueBufs;
  uint32 ulQueueId;
  uint32 ulChainId;
  Eth_TSN_FrameType enFrameType;
  uint32 ulMaxFrameSize;
  Eth_TASGateStateType enInitGateState;
  uint32 ulCycleTime;
  Eth_CBSConfigType stCBSConfig;
  Eth_PerQueRLCfgType stPerQueRLConfig;
} Eth_TxQueueType;

/* Rx Queue struct */
typedef struct STag_Eth_RxQueueType                                                                                     /* PRQA S 3630 # JV-01 */
{
  uint32 ulQueueBufs;
  uint32 ulQueueId;
  uint32 ulChainId;
} Eth_RxQueueType;

typedef struct STag_Eth_QueueConfigType
{
  P2CONST(Eth_TxQueueType, TYPEDEF, ETH_APPL_CONST) pTxQueueConfig;
  P2CONST(Eth_RxQueueType, TYPEDEF, ETH_APPL_CONST) pRxQueueConfig;
  uint8 ucNumberOfTxQueue;
  uint8 ucNumberOfRxQueue;
} Eth_QueueConfigType;

typedef struct STag_Eth_PauseLevelType
{
  uint32 ulPauseAssertionLevel;
  uint32 ulPauseDeAssertionLevel;
} Eth_PauseLevelType;

typedef struct STag_Eth_FlowControlType
{
  Eth_OptionType enPauseFrame;
  uint32 ulRetransmissionTime;
  uint32 ulPauseTime;
  Eth_OptionType enPauseTimeZero;
  Eth_PauseLevelType stPauseLevelConfig;
} Eth_FlowControlType;

typedef struct STag_Eth_PFCPauseLevelConfig
{
  uint32 ulPausePriority;
  uint32 ulPauseAssertionLevel;
  uint32 ulPauseDeAssertionLevel;
} Eth_PFCPauseLevelConfig;

typedef struct STag_Eth_PFCType
{
  Eth_OptionType enPFCFrame;
  uint32 ulRetransmissionTime;
  uint32 ulPauseTime;
  Eth_OptionType enPauseTimeZero;
  Eth_PFCPauseLevelConfig stPFCPauseLevelConfig[ETH_RACE_PAS_LVL_N];
} Eth_PFCType;

/*******************************************************************************
**  Type: Eth_CaptureTimeAdjustment                                           **
**                                                                            **
**  Capture Time option                                                       **
**                                                                            **
**  Members:                                                                  **
**    MDIO_CAPTURE_TIME_0_CLK_CYCLE  -  No adjusted capture time              **
**    MDIO_CAPTURE_TIME_1_CLK_CYCLE  -  Capture before 1 clk                  **
**    MDIO_CAPTURE_TIME_2_CLK_CYCLE  -  Capture before 2 clk                  **
**    MDIO_CAPTURE_TIME_3_CLK_CYCLE  -  Capture before 3 clk                  **
**    MDIO_CAPTURE_TIME_4_CLK_CYCLE  -  Capture before 4 clk                  **
**    MDIO_CAPTURE_TIME_5_CLK_CYCLE  -  Capture before 5 clk                  **
**    MDIO_CAPTURE_TIME_6_CLK_CYCLE  -  Capture before 6 clk                  **
**    MDIO_CAPTURE_TIME_7_CLK_CYCLE  -  Capture before 7 clk                  **
*******************************************************************************/
typedef enum STag_Eth_CaptureTimeAdjustmentType
{
  MDIO_CAPTURE_TIME_0_CLK_CYCLE = 0,
  MDIO_CAPTURE_TIME_1_CLK_CYCLE,
  MDIO_CAPTURE_TIME_2_CLK_CYCLE,
  MDIO_CAPTURE_TIME_3_CLK_CYCLE,
  MDIO_CAPTURE_TIME_4_CLK_CYCLE,
  MDIO_CAPTURE_TIME_5_CLK_CYCLE,
  MDIO_CAPTURE_TIME_6_CLK_CYCLE,
  MDIO_CAPTURE_TIME_7_CLK_CYCLE
} Eth_CaptureTimeAdjustmentType;

/*******************************************************************************
**  Type: Eth_HoldTimeAdjustment                                              **
**                                                                            **
**  Hold Time option                                                          **
**                                                                            **
**  Members:                                                                  **
**    MDIO_HOLD_TIME_0_CLK_CYCLE  -  No adjusted hold time                    **
**    MDIO_HOLD_TIME_1_CLK_CYCLE  -  Hold extra 1 clk                         **
**    MDIO_HOLD_TIME_2_CLK_CYCLE  -  Hold extra 2 clk                         **
**    MDIO_HOLD_TIME_3_CLK_CYCLE  -  Hold extra 3 clk                         **
**    MDIO_HOLD_TIME_4_CLK_CYCLE  -  Hold extra 4 clk                         **
**    MDIO_HOLD_TIME_5_CLK_CYCLE  -  Hold extra 5 clk                         **
**    MDIO_HOLD_TIME_6_CLK_CYCLE  -  Hold extra 6 clk                         **
**    MDIO_HOLD_TIME_7_CLK_CYCLE  -  Hold extra 7 clk                         **
*******************************************************************************/
typedef enum STag_Eth_HoldTimeAdjustmentType
{
  MDIO_HOLD_TIME_0_CLK_CYCLE = 0,
  MDIO_HOLD_TIME_1_CLK_CYCLE,
  MDIO_HOLD_TIME_2_CLK_CYCLE,
  MDIO_HOLD_TIME_3_CLK_CYCLE,
  MDIO_HOLD_TIME_4_CLK_CYCLE,
  MDIO_HOLD_TIME_5_CLK_CYCLE,
  MDIO_HOLD_TIME_6_CLK_CYCLE,
  MDIO_HOLD_TIME_7_CLK_CYCLE
} Eth_HoldTimeAdjustmentType;

/*******************************************************************************
**  Type: Etag_Eth_DirectionTypeRsw2                                          **
**                                                                            **
**  Direction type                                                            **
**                                                                            **
**  Members:                                                                  **
**    ETH_TX_RSW2    - Transmit                                               **
**    ETH_RX_RSW2    - Receive                                                **
*******************************************************************************/
typedef enum Etag_Eth_DirectionTypeRsw2
{
  ETH_TX_RSW2,
  ETH_RX_RSW2
} Eth_DirectionTypeRsw2;

/*******************************************************************************
**  Type: Eth_RxConfigType                                                    **
**                                                                            **
**  reception configuration structure                                         **
**                                                                            **
**  Members:                                                                  **
**  enEncf                  - enable network control filtering                **
**  enEsf                   - enable stream filtering                         **
**  enEts0                  - enable timestamp storage (best effort)          **
**  enEts2                  - enable timestamp storage (stream)               **
**  ulRfcl                  - reception FIFO critical level                   **
**  enSRPTalkerFiltering    - enable stream filtering for talker only         **
*******************************************************************************/
typedef struct STag_Eth_RxConfigType
{
  uint32            ulBcastThreshold;
  uint32            ulMcastThreshold;
  Eth_OptionType    enBcastStormFilter;
  Eth_OptionType    enMcastStormFilter;
  uint32 ulMaxFrameSize;
} Eth_RxConfigType;

/*******************************************************************************
**  Type: Eth_TimeAdjustment                                                  **
**                                                                            **
**  Time adjustment structure                                                 **
**                                                                            **
**  Members:                                                                  **
**    enPSMCaptureTime        - PHY Station Management Capture time           **
**    enPSMHoldTime           - PHY Station Management Hold time              **
**    ulPSMClockSelection     - PHY Station Management Clock Selection        **
*******************************************************************************/
typedef struct STag_Eth_PHYConfigType
{
  Eth_CaptureTimeAdjustmentType enPSMCaptureTime;
  Eth_HoldTimeAdjustmentType    enPSMHoldTime;
  uint32 ulPSMClockSelection;
} Eth_PHYConfigType;

/* RSW2 LLDriver specific hardware configuration */
typedef struct STag_Eth_ETNEConfigType
{
  uint32 ulEthPortId;
  uint32 ulFwdVectorId;
  uint32 aaFwdCsd[ETH_MAX_GWCA_SUPPORTED];
  uint32 ulGateLatency;
  uint32 ulGateJitter;
  Eth_FlowControlType stFlowControlConfig;
  Eth_PFCType stPFCConfig;
  Eth_QueueConfigType stQueueConfig;
  Eth_RxConfigType stRxConfig;
  Eth_TxFragmentType enTxFragment;
  Eth_TASConfigType stTASConfig;
  Eth_PHYConfigType stPHYConfig;
  Eth_OptionType enBypassMode;
} Eth_ETNEConfigType;

/*******************************************************************************
**  Type: Eth_BasicDescType                                                   **
**                                                                            **
**  Basic descriptor structure                                                **
**                                                                            **
**  Members:                                                                  **
**    ulDs     - Descriptor size                                              **
**    ulInfo0  - Information 0                                                **
**    ulErr    - Error                                                        **
**    ulDse    - Data Size Error                                              **
**    ulAxie   - AXI Bus Error                                                **
**    ulDie    - Descriptor Interrupt Enable                                  **
**    ulDt     - Descriptor Type                                              **
**    ulDptrH  - Data Pinter Hith                                             **
**    ulDptr   - Data Pinter                                                  **
*******************************************************************************/
typedef struct STag_Eth_BasicDescType
{
  uint32 ulDs      : 12;                                                                                                /* PRQA S 0635 # JV-01 */
  uint32 ulInfo0   : 4;                                                                                                 /* PRQA S 0635 # JV-01 */
  uint32 ulErr     : 1;                                                                                                 /* PRQA S 0635 # JV-01 */
  uint32 ulDse     : 1;                                                                                                 /* PRQA S 0635 # JV-01 */
  uint32 ulAxie    : 1;                                                                                                 /* PRQA S 0635 # JV-01 */
  uint32 ulDie     : 1;                                                                                                 /* PRQA S 0635 # JV-01 */
  uint32 ulDt      : 4;                                                                                                 /* PRQA S 0635 # JV-01 */
  uint32 ulDptrH   : 8;                                                                                                 /* PRQA S 0635 # JV-01 */
  uint32 ulDptr;
} Eth_BasicDescType;

#if (ETH_GLOBAL_TIME_SUPPORT == STD_ON)
/*******************************************************************************
**  Type: Eth_TimeStampDescType                                               **
**                                                                            **
**  Timestamp structure                                                       **
**                                                                            **
**  Members:                                                                  **
**    ulTSNS - Timestamp nanosecond                                           **
**    ulTSV  - Timestamp valid                                                **
**    ulTSD  - Timestamp default                                              **
**    ulTSS  - Timestamp second                                               **
*******************************************************************************/
typedef struct STag_Eth_TimeStampDescType
{
  uint32 ulTSNS: 30;                                                                                                    /* PRQA S 0635 # JV-01 */
  uint32 ulTSV : 1;                                                                                                     /* PRQA S 0635 # JV-01 */
  uint32 ulTSD : 1;                                                                                                     /* PRQA S 0635 # JV-01 */
  uint32 ulTSS;
} Eth_TimeStampDescType;

/*******************************************************************************
**  Type: Eth_TSDescType                                                      **
**                                                                            **
**  Timestamp descriptor structure                                            **
**                                                                            **
**  Members:                                                                  **
**    ulDs        - Descriptor size                                           **
**    ulInfo0     - Information 0                                             **
**    ulErr       -  Error                                                    **
**    ulDse       -  Data Size Error                                          **
**    ulAxie      -  AXI Bus Error                                            **
**    ulDie       -  Descriptor Interrupt Enable                              **
**    ulDt        -  Descriptor Type                                          **
**    ulRSV1      -  Reserved                                                 **
**    ulTsun      -  Timestamp unique number                                  **
**    ulSpn       -  Port number from which the timestamp corresponding frame **
**                   entered the switch                                       **
**    ulRSV2      -  Reserved                                                 **
**    ulDpn       -  Port number by which the timestamp has been taken        **
**    ulRSV3      -  Reserved                                                 **
**    ulTn        -  Timer Number                                             **
**    ulRSV4      -  Reserved                                                 **
**    stTimestamp - Timestamp information                                     **
*******************************************************************************/
typedef struct STag_Eth_TSDescType
{
  uint64 ulDs      : 12;                                                                                                /* PRQA S 0635 # JV-01 */
  uint64 ulInfo0   : 4;                                                                                                 /* PRQA S 0635 # JV-01 */
  uint64 ulErr     : 1;                                                                                                 /* PRQA S 0635 # JV-01 */
  uint64 ulDse     : 1;                                                                                                 /* PRQA S 0635 # JV-01 */
  uint64 ulAxie    : 1;                                                                                                 /* PRQA S 0635 # JV-01 */
  uint64 ulDie     : 1;                                                                                                 /* PRQA S 0635 # JV-01 */
  uint64 ulDt      : 4;                                                                                                 /* PRQA S 0635 # JV-01 */
  uint64 ulRSV1    : 8;                                                                                                 /* PRQA S 0635 # JV-01 */
  uint64 ulTsun    : 8;                                                                                                 /* PRQA S 0635 # JV-01 */
  uint64 ulSpn     : 3;                                                                                                 /* PRQA S 0635 # JV-01 */
  uint64 ulRSV2    : 5;                                                                                                 /* PRQA S 0635 # JV-01 */
  uint64 ulDpn     : 2;                                                                                                 /* PRQA S 0635 # JV-01 */
  uint64 ulRSV3    : 6;                                                                                                 /* PRQA S 0635 # JV-01 */
  uint64 ulTn      : 1;                                                                                                 /* PRQA S 0635 # JV-01 */
  uint64 ulRSV4    : 7;                                                                                                 /* PRQA S 0635 # JV-01 */
  Eth_TimeStampDescType stTimestamp;
} Eth_TSDescType;
#endif /* ETH_GLOBAL_TIME_SUPPORT */

/*******************************************************************************
**  Type: Eth_LinkDescTypeRsw2                                                **
**                                                                            **
**  LINKFIX table descriptor structure                                        **
**                                                                            **
**  Members:                                                                  **
**    ulDs     - Descriptor size                                              **
**    ulInfo0  - Information 0                                                **
**    ulErr    - Error                                                        **
**    ulDse    - Data Size Error                                              **
**    ulAxie   - AXI Bus Error                                                **
**    ulDie    - Descriptor Interrupt Enable                                  **
**    ulDt     - Descriptor Type                                              **
**    ulDptrH  - Data Pinter Hith                                             **
**    ulDptr   - Data Pinter                                                  **
*******************************************************************************/
typedef struct STag_Eth_LinkDescTypeRsw2
{
  uint32 ulDs      : 12;                                                                                                /* PRQA S 0635 # JV-01 */
  uint32 ulInfo0   : 4;                                                                                                 /* PRQA S 0635 # JV-01 */
  uint32 ulErr     : 1;                                                                                                 /* PRQA S 0635 # JV-01 */
  uint32 ulDse     : 1;                                                                                                 /* PRQA S 0635 # JV-01 */
  uint32 ulAxie    : 1;                                                                                                 /* PRQA S 0635 # JV-01 */
  uint32 ulDie     : 1;                                                                                                 /* PRQA S 0635 # JV-01 */
  uint32 ulDt      : 4;                                                                                                 /* PRQA S 0635 # JV-01 */
  uint32 ulDptrH   : 8;                                                                                                 /* PRQA S 0635 # JV-01 */
  uint32 ulDptr;
} Eth_LinkDescTypeRsw2;

/*******************************************************************************
**  Type: Eth_ExtTxEthDescType                                                **
**                                                                            **
**  (Extended descriptor) Transmission ethernet descriptor structure          **
**                                                                            **
**  Members:                                                                  **
**    stHeader  - Basic Descriptor                                            **
**    ulFi      - FCS in                                                      **
**    ulRSV1    - Reserved                                                    **
**    ulFmt     - Descriptor format                                           **
**    ulTxc     - TX Timestamp capture                                        **
**    ulIet     - Timestamp insertion request                                 **
**    ulCrt     - Residence time calculation request                          **
**    ulTn      - Timer utilized for capture/insertion                        **
**    ulRSV2    - Reserved                                                    **
**    ulTsun    - Timestamp unique number                                     **
**    ulRSV3    - Reserved                                                    **
*******************************************************************************/
typedef struct STag_Eth_ExtTxEthDescType
{
  Eth_BasicDescType stHeader;
  uint32 ulFi      : 1;                                                                                                 /* PRQA S 0635 # JV-01 */
  uint32 ulRSV1    : 1;                                                                                                 /* PRQA S 0635 # JV-01 */
  uint32 ulFmt     : 1;                                                                                                 /* PRQA S 0635 # JV-01 */
  uint32 ulTxc     : 1;                                                                                                 /* PRQA S 0635 # JV-01 */
  uint32 ulIet     : 1;                                                                                                 /* PRQA S 0635 # JV-01 */
  uint32 ulCrt     : 1;                                                                                                 /* PRQA S 0635 # JV-01 */
  uint32 ulTn      : 1;                                                                                                 /* PRQA S 0635 # JV-01 */
  uint32 ulRSV2    : 1;                                                                                                 /* PRQA S 0635 # JV-01 */
  uint32 ulTsun    : 8;                                                                                                 /* PRQA S 0635 # JV-01 */
  uint32 ulRSV3_H  : 16;                                                                                                /* PRQA S 0635 # JV-01 */
  uint32 ulRSV3_L;
} Eth_ExtTxEthDescType;

/*******************************************************************************
**  Type: Eth_ExtTxDirDescType                                                **
**                                                                            **
**  (Extended descriptor) Transmission direct descriptor structure            **
**                                                                            **
**  Members:                                                                  **
**    stHeader  - Basic Descriptor                                            **
**    ulFi      - FCS in                                                      **
**    ulSec     - Secure descriptor                                           **
**    ulFmt     - Descriptor format                                           **
**    ulTxc     - TX Timestamp capture                                        **
**    ulIet     - Timestamp insertion request                                 **
**    ulCrt     - Residence time calculation request                          **
**    ulTn      - Timer utilized for capture/insertion                        **
**    ulRSV1    - Reserved                                                    **
**    ulTsun    - Timestamp unique number                                     **
**    ulRn      - Routing valid                                               **
**    ulRSV2    - Reserved                                                    **
**    ulRv      - Routing valid                                               **
**    ulIpv     - Internal priority value                                     **
**    ulFw      - The FCS contained in the frame is wrong                     **
**    ulCsd0    - CPU sub destination for GWCA0                               **
**    ulRSV3    - Reserved                                                    **
**    ulCsd1    - CPU sub destination for GWCA1                               **
**    ulRSV4    - Reserved                                                    **
**    ulDv      - Destination vector                                          **
**    ulRSV5    - Reserved                                                    **
*******************************************************************************/
typedef struct STag_Eth_ExtTxDirDescType                                                                                /* PRQA S 3630 # JV-01 */
{
  Eth_BasicDescType stHeader;
  uint64 ulFi      : 1;                                                                                                 /* PRQA S 0635 # JV-01 */
  uint64 ulSec     : 1;                                                                                                 /* PRQA S 0635 # JV-01 */
  uint64 ulFmt     : 1;                                                                                                 /* PRQA S 0635 # JV-01 */
  uint64 ulTxc     : 1;                                                                                                 /* PRQA S 0635 # JV-01 */
  uint64 ulIet     : 1;                                                                                                 /* PRQA S 0635 # JV-01 */
  uint64 ulCrt     : 1;                                                                                                 /* PRQA S 0635 # JV-01 */
  uint64 ulTn      : 1;                                                                                                 /* PRQA S 0635 # JV-01 */
  uint64 ulRSV1    : 1;                                                                                                 /* PRQA S 0635 # JV-01 */
  uint64 ulTsun    : 8;                                                                                                 /* PRQA S 0635 # JV-01 */
  uint64 ulRn      : 8;                                                                                                 /* PRQA S 0635 # JV-01 */
  uint64 ulRSV2    : 3;                                                                                                 /* PRQA S 0635 # JV-01 */
  uint64 ulRv      : 1;                                                                                                 /* PRQA S 0635 # JV-01 */
  uint64 ulIpv     : 3;                                                                                                 /* PRQA S 0635 # JV-01 */
  uint64 ulFw      : 1;                                                                                                 /* PRQA S 0635 # JV-01 */
  uint64 ulCsd0    : 7;                                                                                                 /* PRQA S 0635 # JV-01 */
  uint64 ulRSV3    : 1;                                                                                                 /* PRQA S 0635 # JV-01 */
  uint64 ulCsd1    : 7;                                                                                                 /* PRQA S 0635 # JV-01 */
  uint64 ulRSV4    : 1;                                                                                                 /* PRQA S 0635 # JV-01 */
  uint64 ulDv      : 7;                                                                                                 /* PRQA S 0635 # JV-01 */
  uint64 ulRSV5    : 9;                                                                                                 /* PRQA S 0635 # JV-01 */
} Eth_ExtTxDirDescType;

/*******************************************************************************
**  Type: Eth_ExtRxEthDescType                                                **
**                                                                            **
**  (Extended descriptor) Reception ethernet descriptor structure             **
**  (Extended timestamp descriptor) Reception ethernet descriptor structure   **
**                                                                            **
**  Members:                                                                  **
**    stHeader    - Basic Descriptor                                          **
**    ulFi        - FCS in                                                    **
**    ulSec       - Secure descriptor                                         **
**    ulFmt       - Descriptor format                                         **
**    ulTxc       - TX Timestamp capture                                      **
**    ulIet       - Timestamp insertion request                               **
**    ulCrt       - Residence time calculation request                        **
**    ulTn        - Timer utilized for capture/insertion                      **
**    ulRSV1      - Reserved                                                  **
**    ulTsun      - Timestamp unique number                                   **
**    ulSaef      - Source agent error flags                                  **
**    ulRn        - Routing valid                                             **
**    ulRSV2      - Reserved                                                  **
**    ulRv        - Routing valid                                             **
**    ulSpn       - Source port number                                        **
**    ulRSV3      - Reserved                                                  **
**    ulFesf      - Forwarding engine status flags                            **
**                                                                            **
**  Below this is used only when ETH_GLOBAL_TIME_SUPPORT is STD_ON.           **
**    stTimestamp - Timestamp information                                     **
*******************************************************************************/
typedef struct STag_Eth_ExtRxEthDescType                                                                                /* PRQA S 3630 # JV-01 */
{
  Eth_BasicDescType stHeader;
  uint64 ulFi      : 1;                                                                                                 /* PRQA S 0635 # JV-01 */
  uint64 ulSec     : 1;                                                                                                 /* PRQA S 0635 # JV-01 */
  uint64 ulFmt     : 1;                                                                                                 /* PRQA S 0635 # JV-01 */
  uint64 ulTxc     : 1;                                                                                                 /* PRQA S 0635 # JV-01 */
  uint64 ulIet     : 1;                                                                                                 /* PRQA S 0635 # JV-01 */
  uint64 ulCrt     : 1;                                                                                                 /* PRQA S 0635 # JV-01 */
  uint64 ulTn      : 1;                                                                                                 /* PRQA S 0635 # JV-01 */
  uint64 ulRSV1    : 1;                                                                                                 /* PRQA S 0635 # JV-01 */
  uint64 ulTsun    : 8;                                                                                                 /* PRQA S 0635 # JV-01 */
  uint64 ulSaef    : 8;                                                                                                 /* PRQA S 0635 # JV-01 */
  uint64 ulRn      : 8;                                                                                                 /* PRQA S 0635 # JV-01 */
  uint64 ulRSV2    : 3;                                                                                                 /* PRQA S 0635 # JV-01 */
  uint64 ulRv      : 1;                                                                                                 /* PRQA S 0635 # JV-01 */
  uint64 ulSpn     : 3;                                                                                                 /* PRQA S 0635 # JV-01 */
  uint64 ulRSV3    : 1;                                                                                                 /* PRQA S 0635 # JV-01 */
  uint64 ulFesf    : 24;                                                                                                /* PRQA S 0635 # JV-01 */
#if (ETH_GLOBAL_TIME_SUPPORT == STD_ON)
  Eth_TimeStampDescType  stTimestamp;
#endif
} Eth_ExtRxEthDescType;

/*******************************************************************************
**  Type: Eth_RSW2StatusType                                                  **
**                                                                            **
**  Device instance specific data.                                            **
**                                                                            **
**  All instance specific data is kept within that structure.                 **
**                                                                            **
**  Members:                                                                  **
**    ulBaseAddr            - Avb part base address                           **
**    ulDescTableAddr       - Descriptor table address                        **
**    aaBufTxCnt            - Buffer Tx counter                               **
**    aaHeadTxDesc          - Head tx descriptor address                      **
**    aaLastTxDesc          - Last tx descriptor address                      **
**    aaNextRxDesc          - Next free rx descriptor address                 **
**    enRxBeTimestamp       - Rx timestamp function status of best effort     **
**                            channel                                         **
**    enRxSTimestamp        - Rx timestamp function status of stream channel  **
**    aaRxBeQueueBuf        - Rx BE buffer addresses                          **
**    aaRxNcQueueBuf        - Rx NC buffer addresses                          **
**    aaRxSQueueBuf         - Rx stream buffer address                        **
**    enDevStatus           - Device status                                   **
**    stStats               - Statistics (e.g. RxPacketNo, BroadcastNo)       **
*******************************************************************************/
typedef struct STag_Eth_HwStatusType
{
  uint32                                                 aaBufTxCnt[ETH_TXQ_NUM_RSW2];                                  
  P2VAR(Eth_ExtTxDirDescType, AUTOMATIC, ETH_APPL_DATA)  aaHeadTxDesc[ETH_TXQ_NUM_RSW2];                                /* PRQA S 3432 # JV-01 */
  P2VAR(Eth_ExtTxDirDescType, AUTOMATIC, ETH_APPL_DATA)  aaNextTxDesc[ETH_TXQ_NUM_RSW2];                                /* PRQA S 3432 # JV-01 */
  P2VAR(Eth_ExtRxEthDescType, AUTOMATIC, ETH_APPL_DATA)  aaHeadRxDesc[ETH_RXQ_NUM_RSW2];                                /* PRQA S 3432 # JV-01 */
  P2VAR(Eth_ExtRxEthDescType, AUTOMATIC, ETH_APPL_DATA)  aaNextRxDesc[ETH_RXQ_NUM_RSW2];                                /* PRQA S 3432 # JV-01 */
} Eth_HwStatusType;

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/

/*******************************************************************************
**  Type: Eth_EtherFrameType                                                  **
**                                                                            **
**  Ethernet Frame structure                                                  **
**                                                                            **
**  Members:                                                                  **
**    ucDstAddr    - Destination address                                      **
**    ucSrcAddr    - Source address                                           **
**    ucFrameType  - EtherType                                                **
**    ucPayload    - Payload                                                  **
*******************************************************************************/
typedef struct STag_Eth_EtherFrameType
{
  uint8 ucDstAddr[6];
  uint8 ucSrcAddr[6];
  uint8 ucFrameType[2];
  Eth_DataType ucPayload;
} Eth_EtherFrameType;

/*******************************************************************************
**  Type: Eth_DescChainInfo                                                   **
**                                                                            **
**  Descriptor Chain configuration information structure                      **
**                                                                            **
**  Members:                                                                  **
**  enDir                   - Tx / Rx direction                               **
**  ulCtrlIdx               - Index of the controller                         **
**  ulFifoIdx               - Index of related fifo                           **
**  enInterrupt             - enable interrupt                                **
*******************************************************************************/
typedef struct STag_Eth_DescChainInfo
{
  Eth_DirectionTypeRsw2 enDir;
  uint32 ulCtrlIdx;
  uint32 ulFifoIdx;
  Eth_OptionType enInterrupt;
} Eth_DescChainInfo;

/*******************************************************************************
**  Type: Eth_DescChainMap                                                    **
**                                                                            **
**  Descriptor Chain configuration information map structure                  **
**                                                                            **
**  Members:                                                                  **
**  aaChainInfo             - Descriptor Chain information array              **
**  ulValidChainNum         - Number of Descriptor Chain used                 **
**  ucValidChainId          - Valid Chain ID array                            **
*******************************************************************************/
typedef struct STag_Eth_DescQueueMap
{
  Eth_DescChainInfo aaChainInfo[ETH_RACE_AXI_CHAIN_N];
  uint32 ulValidChainNum;
  uint8 ucValidChainId[ETH_RACE_AXI_CHAIN_N];
} Eth_DescChainMap;

/********************************
**  RSW2 TOP module Registers  **
********************************/
typedef struct STag_Eth_RSW2_TOPRegType                                                                                 /* PRQA S 3630 # JV-01 */
{
  uint32 ulTPEMIMC0;                                 /* 0000H TPEMIMC0 */
  uint32 ulTPEMIMC1;                                 /* 0004H TPEMIMC1 */
  uint16 usTPEMIMC2;                                 /* 0008H TPEMIMC2 */
  uint8  usReserved0[2];                             /*       Reserved0 */
  uint32 ulTPEMIMC3;                                 /* 000CH TPEMIMC3 */
  uint32 ulTPEMIMC4;                                 /* 0010H TPEMIMC4 */
  uint32 ulReserved1[27];                            /*       Reserved1 */
  uint32 ulTPEMIMC6t[ETH_RACE_PTP_TN];               /* 0080H TPEMIMC6 */
  uint32 ulReserved2[30];                            /*       Reserved2 */
  uint32 ulTPEMIMC7t[ETH_RACE_AXI_CHAIN_N];          /* 0100H TPEMIMC7t */
  uint32 ulReserved3[320];                           /*       Reserved3 */
  uint32 ulTSIM;                                     /* 0700H TSIM */
  uint32 ulTFIM;                                     /* 0704H TFIM */
  uint32 ulTCIM;                                     /* 0708H TCIM */
  uint32 ulReserved4;                                /*       Reserved4 */
  uint32 ulTGIM0;                                    /* 0710H TGIM0 */
  uint32 ulTGIM1;                                    /* 0714H TGIM1 */
  uint32 ulReserved5[2];                             /*       Reserved5 */
  uint32 ulTEIM0;                                    /* 0720H TEIM0 */
  uint32 ulTEIM1;                                    /* 0724H TEIM1 */
  uint32 ulTEIM2;                                    /* 0728H TEIM2 */
} Eth_RSW2_TOPRegType;

/*********************************
**  RSW2 COMA module Registers  **
*********************************/
typedef struct STag_Eth_RSW2_COMARegType                                                                                /* PRQA S 3630 # JV-01 */
{
  uint32 ulRIPV;                                             /* 0000H RIPV */
  uint32 ulRRC;                                              /* 0004H RRC */
  uint32 ulRCEC;                                             /* 0008H RCEC */
  uint32 ulRCDC;                                             /* 000CH RCDC */
  uint32 ulReserved0[4];                                     /*       Reserved0 */
  uint32 ulCABPIBWMCi[8];                                    /* 0020H CABPIBWMCi */
  uint32 ulCABPWMLC;                                         /* 0040H CABPWMLC */
  uint32 ulReserved1[3];                                     /*       Reserved1 */
  uint32 ulCABPPFLCi[ETH_RACE_PAS_LVL_N];                    /* 0050H CABPPFLCi */
  uint32 ulReserved2[2];                                     /*       Reserved2 */
  uint32 ulCABPPWMLCi[ETH_RACE_PORT_N];                      /* 0060H CABPPWMLCi */
  uint32 ulReserved3[13];                                    /*       Reserved3 */
  uint32 ulCABPPPFLCij[ETH_RACE_PORT_N][ETH_RACE_PAS_LVL_N]; /* 00A0H CABPPPFLCij */
  uint32 ulReserved4[18];                                    /*       Reserved4 */
  uint32 ulCABPULCi[ETH_RACE_PORT_N];                        /* 0100H CABPULCi */
  uint32 ulReserved5[13];                                    /*       Reserved5 */
  uint32 ulCABPIRM;                                          /* 0140H CABPIRM */
  uint32 ulCABPPCM;                                          /* 0144H CABPPCM */
  uint32 ulCABPLCM;                                          /* 0148H CABPLCM */
  uint32 ulCABPLCM_E;                                        /* 014CH CABPLCM(E) */
  uint32 ulReserved6[12];                                    /*       Reserved6 */
  uint32 ulCABPCPMi[ETH_RACE_PORT_N];                        /* 0180H CABPCPMi */
  uint32 ulReserved7[29];                                    /*       Reserved7 */
  uint32 ulCABPMCPMi[ETH_RACE_PORT_N];                       /* 0200H CABPMCPMi */
  uint32 ulReserved8[29];                                    /*       Reserved8 */
  uint32 ulCABPMCPMi_E[ETH_RACE_PORT_N];                     /* 0280H CABPMCPMi(E) */
  uint32 ulReserved9[29];                                    /*       Reserved9 */
  uint32 ulCARDNM;                                           /* 0300H CARDNM */
  uint32 ulCARDMNM;                                          /* 0304H CARDMNM */
  uint32 ulCARDMNM_E;                                        /* 0308H CARDMNM(E) */
  uint32 ulReserved10;                                       /*       Reserved10 */
  uint32 ulCARDCN;                                           /* 0310H CARDCN */
  uint32 ulCARDCN_E;                                         /* 0314H CARDCN(E) */
  uint32 ulReserved11[58];                                   /*       Reserved11 */
  uint32 ulCAEIS0;                                           /* 0400H CAEIS0 */
  uint32 ulCAEIE0;                                           /* 0404H CAEIE0 */
  uint32 ulCAEID0;                                           /* 0408H CAEID0 */
  uint32 ulReserved12;                                       /*       Reserved12 */
  uint32 ulCAEIS1;                                           /* 0410H CAEIS1 */
  uint32 ulCAEIE1;                                           /* 0414H CAEIE1 */
  uint32 ulCAEID1;                                           /* 0418H CAEID1 */
  uint32 ulReserved13[9];                                    /*       Reserved13 */
  uint32 ulCAMIS0;                                           /* 0440H CAMIS0 */
  uint32 ulCAMIE0;                                           /* 0444H CAMIE0 */
  uint32 ulCAMID0;                                           /* 0448H CAMID0 */
  uint32 ulReserved14;                                       /*       Reserved14 */
  uint32 ulCAMIS1;                                           /* 0450H CAMIS1 */
  uint32 ulCAMIE1;                                           /* 0454H CAMIE1 */
  uint32 ulCAMID1;                                           /* 0458H CAMID1 */
} Eth_RSW2_COMARegType;

/*********************************
**  RSW2 MFWD module Registers  **
*********************************/
typedef struct STag_Eth_RSW2_MFWDRegType                                                                                /* PRQA S 3630 # JV-01 */
{
  uint32 ulFWGC;                                      /* FWGC             */
  uint32 ulReserved0[3];                              /* Reserved0        */
  uint32 ulFWTTC0;                                    /* FWTTC0           */
  uint32 ulFWTTC1;                                    /* FWTTC1           */
  uint32 ulReserved1[2];                              /* Reserved1        */
  uint32 ulFWCEPTC;                                   /* FWCEPTC          */
  uint32 ulFWCEPRC0;                                  /* FWCEPRC0         */
  uint32 ulFWCEPRC1;                                  /* FWCEPRC1         */
  uint32 ulFWCEPRC2;                                  /* FWCEPRC2         */
  uint32 ulFWCLPTC;                                   /* FWCLPTC          */
  uint32 ulFWCLPRC;                                   /* FWCLPRC          */
  uint32 ulReserved2[2];                              /* Reserved2        */
  uint32 ulFWCMPTC;                                   /* FWCMPTC          */
  uint32 ulFWEMPTC;                                   /* FWEMPTC          */
  uint32 ulReserved3[2];                              /* Reserved3        */
  uint32 ulFWSDMPTC;                                  /* FWSDMPTC         */
  uint32 ulFWSDMPVC;                                  /* FWSDMPVC         */
  uint32 ulReserved4[10];                             /* Reserved4        */
  uint32 ulFWLBWMC0;                                   /* FWLBWMC0         */
  uint32 ulFWLBWMC1;                                   /* FWLBWMC1         */
  uint32 ulFWLBWMC2;                                   /* FWLBWMC2         */
  uint32 ulFWLBWMC3;                                   /* FWLBWMC3         */
  uint32 ulReserved5[28];                              /* Reserved5        */
  struct STag_FWPC{
    uint32 ulFWPC0i;                             /* 0100H FWPC0i */
    uint32 ulFWPC1i;                             /* 0104H FWPC1i */
    uint32 ulFWPC2i;                             /* 0108H FWPC2i */
    uint32 ulReserved6;                          /*       Reserved6 */
  } FWPC[ETH_RACE_PORT_N];
  uint32 ulReserved7[4076];                      /*       Reserved7 */
  uint32 ulFWLTHTIM;                             /* 40E0H FWLTHTIM */
  uint32 ulReserved8[351];                       /*       Reserved8 */
  uint32 ulFWMACTIM;                             /* 4660H FWMACTIM */
  uint32 ulReserved9[183];                       /*       Reserved9 */
  uint32 ulFWVLANTIM;                            /* 4940H FWVLANTIM */
  uint32 ulReserved10[47];                        /*       Reserved10 */
  struct STag_FWPBF{
    uint32 ulFWPBFCi;                            /* 4A00H FWPBFCi */
    uint32 ulFWPBFCSDCji[ETH_RACE_PORT_GWCA_N];  /* 4A04H FWPBFCSDCji */
    uint32 ulReserved11[2];                                                                         /* PRQA S 1039 # JV-01 */
  } FWPBF[ETH_RACE_PORT_N];
  uint32 ulReserved12[252];                       /*       Reserved12 */
  uint32 ulFWL23UTIM;                             /* 4E20H FWL23UTIM */
  uint32 ulReserved13[2937];                      /*       Reserved13 */
} Eth_RSW2_MFWDRegType;

/*********************************
**  RSW2 GWCA module Registers  **
*********************************/
typedef struct STag_Eth_RSW2_GWCARegType                                                                                /* PRQA S 3630 # JV-01 */
{
  uint32 ulGWMC;                                 /* 0000H GWMC */
  uint32 ulGWMS;                                 /* 0004H GWMS */
  uint32 ulReserved0[2];                         /*       Reserved0 */
  uint32 ulGWIRC;                                /* 0010H GWIRC */
  uint32 ulGWRDQSC;                              /* 0014H GWRDQSC */
  uint32 ulGWRDQC;                               /* 0018H GWRDQC */
  uint32 ulGWRDQAC;                              /* 001CH GWRDQAC */
  uint32 ulGWRGC;                                /* 0020H GWRGC */
  uint32 ulReserved1[7];                         /*       Reserved1 */
  uint32 ulGWRMFSCq[ETH_GWCA_FRM_PRIO_N];        /* 0040H GWRMFSCq */
  uint32 ulGWRDQDCq[ETH_GWCA_FRM_PRIO_N];        /* 0060H GWRDQDCq */
  uint32 ulGWRDQMq[ETH_GWCA_FRM_PRIO_N];         /* 0080H GWRDQDCq */
  uint32 ulGWRDQMLMq[ETH_GWCA_FRM_PRIO_N];       /* 00A0H GWRDQDCq */
  uint32 ulGWRDQMLMq_E[ETH_GWCA_FRM_PRIO_N];     /* 00A0H GWRDQDCq */
  uint32 ulReserved2[8];                         /*       Reserved2 */
  uint32 ulGWMTIRM;                              /* 0100H GWMTIRM */
  uint32 ulGWMSTLS;                              /* 0104H GWMSTLS */
  uint32 ulGWMSTLR;                              /* 0108H GWMSTLR */
  uint32 ulGWMSTSS;                              /* 010CH GWMSTSS */
  uint32 ulGWMSTSR;                              /* 0110H GWMSTSR */
  uint32 ulReserved3[3];                         /*       Reserved3 */
  uint32 ulGWMAC0;                               /* 0120H GWMAC0 */
  uint32 ulGWMAC1;                               /* 0124H GWMAC1 */
  uint32 ulReserved4[2];                         /*       Reserved4 */
  uint32 ulGWVCC;                                /* 0130H GWVCC */
  uint32 ulGWVTC;                                /* 0134H GWVTC */
  uint32 ulGWTTFC;                               /* 0138H GWTTFC */
  uint32 ulReserved5;                            /*       Reserved5 */
  struct STag_GWTDCAC{
    uint32 ulGWTDCAC0s;                          /* 0140H GWTDCAC0s */
    uint32 ulGWTDCAC1s;                          /* 0144H GWTDCAC1s */
  } GWTDCAC[ETH_RACE_PTP_TN];
  uint32 ulReserved6[4];                         /*       Reserved6 */
  uint32 ulGWTSDCCs[ETH_RACE_PTP_TN];            /* 0160H GWTSDCCs */
  uint32 ulReserved7[6];                         /*       Reserved7 */
  uint32 ulGWTSNM;                               /* 0180H GWTSNM */
  uint32 ulGWTSMNM;                              /* 0184H GWTSMNM */
  uint32 ulGWTSMNM_E;                            /* 0188H GWTSMNM(E) */
  uint32 ulReserved8;                            /*       Reserved8 */
  uint32 ulGWAC;                                 /* 0190H GWAC */
  uint32 ulGWDCBAC0;                             /* 0194H GWDCBAC0 */
  uint32 ulGWDCBAC1;                             /* 0198H GWDCBAC1 */
  uint32 ulReserved9;                            /*       Reserved9 */
  uint32 ulGWMDNC;                               /* 01A0H GWMDNC */
  uint32 ulReserved10[23];                       /*       Reserved10 */
  uint32 ulGWTRCi[ETH_RACE_AXI_CHAIN_N/32UL];      /* 0200H GWTRCi */
  uint32 ulReserved11[62];                       /*       Reserved11 */
  uint32 ulGWTPCp[ETH_RACE_PAS_LVL_N];           /* 0300H GWTPCp */
  uint32 ulReserved12[30];                       /*       Reserved12 */
  uint32 ulGWARIRM;                              /* 0380H GWARIRM */
  uint32 ulReserved13[31];                       /*       Reserved13 */
  uint32 ulGWDCCi[ETH_RACE_AXI_CHAIN_N];         /* 0400H GWDCCi */
  uint32 ulReserved14[192];                      /*       Reserved14 */
  uint32 ulGWAARSS;                              /* 0800H GWAARSS */
  uint32 ulGWAARSR0;                             /* 0804H GWAARSR0 */
  uint32 ulGWAARSR1;                             /* 0808H GWAARSR1 */
  uint32 ulReserved15[13];                       /*       Reserved15 */
  uint32 ulGWIDAUASi[ETH_GWCA_AXI_RINC_N];       /* 0840H GWIDAUASi */
  uint32 ulReserved16[12];                        /*       Reserved16 */
  uint32 ulGWIDASMi[ETH_GWCA_AXI_RINC_N];        /* 0880H GWIDASMi */
  uint32 ulReserved17[28];                       /*       Reserved17 */
  struct STag_GWIDASAM{
    uint32 ulGWIDASAM0i;                         /* 0900H GWIDASAM0i */
    uint32 ulGWIDASAM1i;                         /* 0904H GWIDASAM1i */
  } GWIDASAM[ETH_GWCA_AXI_RINC_N];
  uint32 ulReserved18[24];                       /*       Reserved18 */
  struct STag_GWIDACAM{
    uint32 ulGWIDACAM0i;                         /* 0980H GWIDACAM0i */
    uint32 ulGWIDACAM1i;                         /* 0984H GWIDACAM1i */
  } GWIDACAM[ETH_GWCA_AXI_RINC_N];
  uint32 ulReserved19[24];                       /*       Reserved19 */
  uint32 ulGWGRLC;                               /* 0A00H GWGRLC */
  uint32 ulGWGRLULC;                             /* 0A04H GWGRLULC */
  uint32 ulReserved20[30];                       /*       Reserved20 */
  struct STag_GWRL{
    uint32 ulGWRLCi;                             /* 0A80H GWRLCi */
    uint32 ulGWRLULCi;                           /* 0A84H GWRLULCi */
  } GWRL[ETH_GWCA_AXI_TLIM_N];
  uint32 ulReserved21[48];                      /*       Reserved21 */
  uint32 ulGWIDPC;                               /* 0B80H GWIDPC */
  uint32 ulReserved22[31];                       /*       Reserved22 */
  uint32 ulGWIDCi[ETH_RACE_AXI_CHAIN_N];         /* 0C00H GWIDCi */
  uint32 ulReserved23[192];                      /*       Reserved23 */
  uint32 ulGWRDCN;                               /* 1000H GWRDCN */
  uint32 ulGWTDCN;                               /* 1004H GWTDCN */
  uint32 ulGWTSCN;                               /* 1008H GWTSCN */
  uint32 ulGWTSOVFECN;                           /* 100CH GWTSOVFECN */
  uint32 ulGWUSMFSECN;                           /* 1010H GWUSMFSECN */
  uint32 ulGWTFECN;                              /* 1014H GWTFECN */
  uint32 ulGWSEQECN;                             /* 1018H GWSEQECN */
  uint32 ulReserved24;                           /*       Reserved24 */
  uint32 ulGWTXDNECN;                            /* 1020H GWTXDNECN */
  uint32 ulGWFSECN;                              /* 1024H GWFSECN */
  uint32 ulGWTDFECN;                             /* 1028H GWTDFECN */
  uint32 ulGWTSDNECN;                            /* 102CH GWTSDNECN */
  uint32 ulGWDQOECN;                             /* 1030H GWDQOECN */
  uint32 ulGWDQSECN;                             /* 1034H GWDQSECN */
  uint32 ulGWDFECN;                              /* 1038H GWDFECN */
  uint32 ulGWDSECN;                              /* 103CH GWDSECN */
  uint32 ulGWDSZECN;                             /* 1040H GWDSZECN */
  uint32 ulGWDCTECN;                             /* 1044H GWDCTECN */
  uint32 ulGWRXDNECN;                            /* 1048H GWRXDNECN */
  uint32 ulReserved25[13];                       /*       Reserved25 */
  uint32 ulGWRDCN_E;                             /* 1080H GWRDCN(E) */
  uint32 ulGWTDCN_E;                             /* 1084H GWTDCN(E) */
  uint32 ulGWTSCN_E;                             /* 1088H GWTSCN(E) */
  uint32 ulGWTSOVFECN_E;                         /* 108CH GWTSOVFECN(E) */
  uint32 ulGWUSMFSECN_E;                         /* 1090H GWUSMFSECN(E) */
  uint32 ulGWTFECN_E;                            /* 1094H GWTFECN(E) */
  uint32 ulGWSEQECN_E;                           /* 1098H GWSEQECN(E) */
  uint32 ulReserved26;                           /*       Reserved26 */
  uint32 ulGWTXDNECN_E;                          /* 10A0H GWTXDNECN(E) */
  uint32 ulGWFSECN_E;                            /* 10A4H GWFSECN(E) */
  uint32 ulGWTDFECN_E;                           /* 10A8H GWTDFECN(E) */
  uint32 ulGWTSDNECN_E;                          /* 10ACH GWTSDNECN(E) */
  uint32 ulGWDQOECN_E;                           /* 10B0H GWDQOECN(E) */
  uint32 ulGWDQSECN_E;                           /* 10B4H GWDQSECN(E) */
  uint32 ulGWDFECN_E;                            /* 10B8H GWDFECN(E) */
  uint32 ulGWDSECN_E;                            /* 10BCH GWDSECN(E) */
  uint32 ulGWDSZECN_E;                           /* 10C0H GWDSZECN(E) */
  uint32 ulGWDCTECN_E;                           /* 10C4H GWDCTECN(E) */
  uint32 ulGWRXDNECN_E;                          /* 10C8H GWRXDNECN(E) */
  uint32 ulReserved27[13];                       /*       Reserved27 */
  struct STag_GWDI{
    uint32 ulGWDISi;                             /* 1100H GWDISi */
    uint32 ulGWDIEi;                             /* 1104H GWDIEi */
    uint32 ulGWDIDi;                             /* 1108H GWDIDi */
    uint32 ulGWDIDSi;                            /* 110CH GWDIDSi */
  } GWDI[ETH_RACE_AXI_CHAIN_N/32UL];
  uint32 ulReserved28[24];                       /*       Reserved28 */
  uint32 ulGWTSDIS;                              /* 1180H GWTSDIS */
  uint32 ulGWTSDIE;                              /* 1184H GWTSDIE */
  uint32 ulGWTSDID;                              /* 1188H GWTSDID */
  uint32 ulReserved29;                           /*       Reserved29 */
  uint32 ulGWEIS0;                               /* 1190H GWEIS0 */
  uint32 ulGWEIE0;                               /* 1194H GWEIE0 */
  uint32 ulGWEID0;                               /* 1198H GWEID0 */
  uint32 ulReserved30;                           /*       Reserved30 */
  uint32 ulGWEIS1;                               /* 11A0H GWEIS1 */
  uint32 ulGWEIE1;                               /* 11A4H GWEIE1 */
  uint32 ulGWEID1;                               /* 11A8H GWEID1 */
  uint32 ulReserved31[21];                       /*       Reserved31 */
  struct STag_GWEI{
    uint32 ulGWEIS2i;                            /* 1200H GWEIS2i */
    uint32 ulGWEIE2i;                            /* 1204H GWEIE2i */
    uint32 ulGWEID2i;                            /* 1208H GWEID2i */
    uint32 ulReserved32;                         /*       Reserved32 */
  } GWEI[ETH_RACE_AXI_CHAIN_N/32UL];
  uint32 ulReserved33[24];                       /*       Reserved33 */
  uint32 ulGWEIS3;                               /* 1280H GWEIS3 */
  uint32 ulGWEIE3;                               /* 1284H GWEIE3 */
  uint32 ulGWEID3;                               /* 1288H GWEIS3 */
  uint32 ulReserved34;                           /*       Reserved34 */
  uint32 ulGWEIS4;                               /* 1290H GWEIS4 */
  uint32 ulGWEIE4;                               /* 1294H GWEIE4 */
  uint32 ulGWEID4;                               /* 1298H GWEIS4 */
  uint32 ulReserved35;                           /*       Reserved35 */
  uint32 ulGWEIS5;                               /* 12A0H GWEIS5 */
  uint32 ulGWEIE5;                               /* 12A4H GWEIE5 */
  uint32 ulGWEID5;                               /* 12A8H GWEIS5 */
} Eth_RSW2_GWCARegType;                                                                                                 

/*********************************
**  RSW2 ETHA module Registers  **
*********************************/
typedef struct STag_Eth_RSW2_ETHARegType                                                                                /* PRQA S 3630 # JV-01 */
{
  uint32 ulEAMC;                                 /* 0000H EAMC */
  uint32 ulEAMS;                                 /* 0004H EAMS */
  uint32 ulReserved0[2];                         /*       Reserved0 */
  uint32 ulEAIRC;                                /* 0010H EAIRC */
  uint32 ulEATDQSC;                              /* 0014H EATDQSC */
  uint32 ulEATDQC;                               /* 0018H EATDQC */
  uint32 ulEATDQAC;                              /* 001CH EATDQAC */
  uint32 ulEATPEC;                               /* 0020H EATPEC */
  uint32 ulReserved1[7];                         /*       Reserved1 */
  uint32 ulEATMFSCq[ETH_ETHA_FRM_PRIO_N];        /* 0040H EATMFSCq */
  uint32 ulEATDQDCq[ETH_ETHA_FRM_PRIO_N];        /* 0060H EATDQDCq */
  uint32 ulEATDQMq[ETH_ETHA_FRM_PRIO_N];         /* 0080H EATDQMq */
  uint32 ulEATDQMLMq[ETH_ETHA_FRM_PRIO_N];       /* 00A0H EATDQMLMq */
  uint32 ulEATDQMLMq_E[ETH_ETHA_FRM_PRIO_N];     /* 00C0H EATDQMLMq(E) */
  uint32 ulReserved2[8];                         /*       Reserved2 */
  uint32 ulEACTQC;                               /* EACTQC           */
  uint32 ulEACTDQDC;                             /* EACTDQDC         */
  uint32 ulEACTDQM;                              /* EACTDQM          */
  uint32 ulEACTDQMLM;                            /* EACTDQMLM        */
  uint32 ulEACTDQMLME;                           /* EACTDQMLME       */
  uint32 ulReserved3[7];                         /*       Reserved3 */
  uint32 ulEAVCC;                                /* 0130H EAVCC */
  uint32 ulEAVTC;                                /* 0134H EAVTC */
  uint32 ulEARTFC;                               /* 0138H EARTFC */
  uint32 ulReserved4[49];                        /*       Reserved4 */
  uint32 ulEACAEC;                               /* 0200H EACAEC */
  uint32 ulEACC;                                 /* 0204H EACC */
  uint32 ulReserved5[6];                         /*       Reserved5 */
  uint32 ulEACAIVCq[ETH_ETHA_FRM_PRIO_N];        /* 0220H EACAIVCq */
  uint32 ulEACAULCq[ETH_ETHA_FRM_PRIO_N];        /* 0240H EACAULCq */
  uint32 ulEACOEM;                               /* 0260H EACOEM */
  uint32 ulReserved6[7];                         /*       Reserved6 */
  uint32 ulEACOIVMq[ETH_ETHA_FRM_PRIO_N];        /* 0280H EACOIVMq */
  uint32 ulEACOULMq[ETH_ETHA_FRM_PRIO_N];        /* 02A0H EACOULMq */
  uint32 ulEACGSM;                               /* 02C0H EACGSM */
  uint32 ulReserved7[15];                        /*       Reserved7 */
  uint32 ulEATASC;                               /* 0300H EATASC */
  uint32 ulEATASIGSC;                            /* 0304H EATASIGSC */
  uint32 ulReserved8[6];                         /*       Reserved8 */
  uint32 ulEATASENCi[ETH_ETHA_FRM_PRIO_N];       /* 0320H EATASENCi */
  uint32 ulEATASCTENC;                           /* EATASCTENC       */
  uint32 ulReserved9[7];                         /*       Reserved9 */
  uint32 ulEATASENMi[ETH_ETHA_FRM_PRIO_N];       /* 0360H EATASENMi */
  uint32 ulEATASCTENM;                           /* EATASCTENM       */
  uint32 ulReserved10[7];                         /*       Reserved10 */
  uint32 ulEATASCSTC0;                           /* 03A0H EATASCSTC0 */
  uint32 ulEATASCSTC1;                           /* 03A4H EATASCSTC1 */
  uint32 ulEATASCSTM0;                           /* 03A8H EATASCSTM0 */
  uint32 ulEATASCSTM1;                           /* 03ACH EATASCSTM1 */
  uint32 ulEATASCTC;                             /* 03B0H EATASCTC */
  uint32 ulEATASCTM;                             /* 03B4H EATASCTM */
  uint32 ulReserved11[2];                        /*       Reserved11 */
  uint32 ulEATASGL0;                             /* 03C0H EATASGL0 */
  uint32 ulEATASGL1;                             /* 03C4H EATASGL1 */
  uint32 ulEATASGLR;                             /* 03C8H EATASGLR */
  uint32 ulReserved12;                           /*       Reserved12 */
  uint32 ulEATASGR;                              /* 03D0H EATASGR */
  uint32 ulEATASGRR;                             /* 03D4H EATASGRR */
  uint32 ulReserved13[2];                        /*       Reserved13 */
  uint32 ulEATASHCC;                             /* 03E0H EATASHCC */
  uint32 ulEATASRIRM;                            /* 03E4H EATASRIRM */
  uint32 ulEATASSM;                              /* 03E8H EATASSM */
  uint32 ulReserved14[5];                        /*       Reserved14 */
  uint32 ulEAUSMFSECN;                           /* 0400H EAUSMFSECN */
  uint32 ulEATFECN;                              /* 0404H EATFECN */
  uint32 ulEAFSECN;                              /* 0408H EAFSECN */
  uint32 ulEADQOECN;                             /* 040CH EADQOECN */
  uint32 ulEADQSECN;                             /* 0410H EADQSECN */
  uint32 ulReserved15;                           /*       Reserved15 */
  uint32 ulEAEXCECN;                             /* 0418H EAEXCECN */
  uint32 ulReserved16;                           /*       Reserved16 */
  uint32 ulEALATCECN;                            /* 0420H EALATCECN */
  uint32 ulEACLSECN;                             /* 0424H EACLSECN */
  uint32 ulReserved17[22];                       /*       Reserved17 */
  uint32 ulEAUSMFSECN_E;                         /* 0480H EAUSMFSECN(E) */
  uint32 ulEATFECN_E;                            /* 0484H EATFECN(E) */
  uint32 ulEAFSECN_E;                            /* 0488H EAFSECN(E) */
  uint32 ulEADQOECN_E;                           /* 048CH EADQOECN(E) */
  uint32 ulEADQSECN_E;                           /* 0490H EADQSECN(E) */
  uint32 ulReserved18;                           /*       Reserved18 */
  uint32 ulEACLSECN_E;                           /* 0424H EACLSECN */
  uint32 ulReserved19;                           /*       Reserved19 */
  uint32 ulEALATCECN_E;                          /* 04A0H EALATCECN */
  uint32 ulEAEXCECN_E;                           /* 04A4H EAEXCECN(E) */
  uint32 ulReserved20[22];                       /*       Reserved20 */
  uint32 ulEAEIS0;                               /* 0500H EAEIS0 */
  uint32 ulEAEIE0;                               /* 0504H EAEIE0 */
  uint32 ulEAEID0;                               /* 0508H EAEID0 */
  uint32 ulReserved21;                           /*       Reserved21 */
  uint32 ulEAEIS1;                               /* 0510H EAEIS1 */
  uint32 ulEAEIE1;                               /* 0514H EAEIE1 */
  uint32 ulEAEID1;                               /* 0518H EAEID1 */
  uint32 ulReserved22;                           /*       Reserved22 */
  uint32 ulEAEIS2;                               /* 0520H EAEIS2 */
  uint32 ulEAEIE2;                               /* 0524H EAEIE2 */
  uint32 ulEAEID2;                               /* 0528H EAEID2 */
  uint32 ulReserved23;                           /*       Reserved23 */
  uint32 ulEAEIS3;                               /* 0520H EAEIS2 */
  uint32 ulEAEIE3;                               /* 0524H EAEIE2 */
  uint32 ulEAEID3;                               /* 0528H EAEID2 */
  uint32 ulReserved24[689];                      /*       Reserved24 */
  uint32 ulRMRO;                                 /* 1000H RMRO */
} Eth_RSW2_ETHARegType;

/*********************************
**  RSW2 RMAC module Registers  **
*********************************/
typedef struct STag_Eth_RSW2_RMACRegType                                                                                /* PRQA S 3630 # JV-01 */
{
  uint32 ulMPSM;                                 /* 0000H MPSM */
  uint32 ulMPIC;                                 /* 0004H MPIC */
  uint32 ulMPIM;                                 /* 0008H MPIM */
  uint32 ulReserved0;                            /*       Reserved0 */
  uint32 ulMIOC;                                 /* MIOC             */
  uint32 ulReserved1[3];                         /*       Reserved1 */
  uint32 ulMTFFC;                                /* 0020H MTFFC */
  uint32 ulMTPFC;                                /* 0024H MTPFC */
  uint32 ulMTPFC2;                               /* 0028H MTPFC2 */
  uint32 ulReserved2;                            /*       Reserved2 */
  uint32 ulMTPFC3t[ETH_RACE_PAS_LVL_N];          /* 0030H MTPFC3t */
  uint32 ulReserved3[6];                         /*       Reserved3 */
  uint32 ulMTATCt[ETH_RACE_PTP_TN];              /* 0050H MTATCt */
  uint32 ulReserved4[2];                         /*       Reserved4 */
  uint32 ulMTIM;                                 /* 0060H MTIM */
  uint32 ulReserved5[3];                         /*       Reserved5 */
  uint32 ulMTFCJC;                               /* MTFCJC           */
  uint32 ulReserved6[3];                         /*       Reserved6 */
  uint32 ulMRGC;                                 /* 0080H MRGC */
  uint32 ulMRMAC0;                               /* 0084H MRMAC0 */
  uint32 ulMRMAC1;                               /* 0088H MRMAC1 */
  uint32 ulMRAFC;                                /* 008CH MRAFC */
  uint32 ulMRSCE;                                /* 0090H MRSCE */
  uint32 ulMRSCP;                                /* 0094H MRSCP */
  uint32 ulMRSCC;                                /* 0098H MRSCC */
  uint32 ulMRFSCE;                               /* 009CH MRFSCE */
  uint32 ulMRFSCP;                               /* 00A0H MRFSCP */
  uint32 ulMTRC;                                 /* 00A4H MTRC */
  uint32 ulMRIM;                                 /* 00A8H MRIM */
  uint32 ulMRPFM;                                /* 00ACH MRPFM */
  uint32 ulReserved7[20];                        /*       Reserved7 */
  uint32 ulMPFCt[ETH_RACE_PTP_TN*8UL];           /* 0100H MPFCt */
  uint32 ulReserved8[16];                        /*       Reserved8 */
  uint32 ulMLVC;                                 /* 0180H MLVC */
  uint32 ulMEEEC;                                /* 0184H MEEEC */
  uint32 ulMLBC;                                 /* 0188H MLBC */
  uint32 ulReserved9;                            /*       Reserved9 */
  uint32 ulMXGMIIC;                              /* 0190H MXGMIIC */
  uint32 ulMPCH;                                 /* 0194H MPCH */
  uint32 ulMANC;                                 /* 0198H MANC */
  uint32 ulMANM;                                 /* 019CH MANM */
  uint32 ulReserved10[24];                        /*       Reserved10 */
  uint32 ulMEIS;                                 /* 0200H MEIS */
  uint32 ulMEIE;                                 /* 0204H MEIE */
  uint32 ulMEID;                                 /* 0208H MEID */
  uint32 ulReserved11;                            /*       Reserved11 */
  uint32 ulMMIS0;                                /* 0210H MMIS0 */
  uint32 ulMMIE0;                                /* 0214H MMIE0 */
  uint32 ulMMID0;                                /* 0218H MMID0 */
  uint32 ulReserved12;                           /*       Reserved12 */
  uint32 ulMMIS1;                                /* 0220H MMIS1 */
  uint32 ulMMIE1;                                /* 0224H MMIE1 */
  uint32 ulMMID1;                                /* 0228H MMID1 */
  uint32 ulReserved13;                           /*       Reserved13 */
  uint32 ulMMIS2;                                /* 0230H MMIS2 */
  uint32 ulMMIE2;                                /* 0234H MMIE2 */
  uint32 ulMMID2;                                /* 0238H MMID2 */
  uint32 ulReserved14[49];                       /*       Reserved14 */
  uint32 ulMMPFTCT;                              /* 0300H MMPFTCT */
  uint32 ulMAPFTCT;                              /* 0304H MAPFTCT */
  uint32 ulMPFRCT;                               /* 0308H MPFRCT */
  uint32 ulMFCICT;                               /* 030CH MFCICT */
  uint32 ulMEEECT;                               /* 0310H MEEECT */
  uint32 ulReserved15[3];                        /*       Reserved15 */
  uint32 ulMMPCFTCTt[ETH_RACE_PAS_LVL_N];        /* 0320H MMPCFTCTt */
  uint32 ulReserved16[2];                        /*       Reserved16 */
  uint32 ulMAPCFTCTt[ETH_RACE_PAS_LVL_N];        /* 0330H MAPCFTCTt */
  uint32 ulReserved17[2];                        /*       Reserved17 */
  uint32 ulMPCFRCTt[ETH_ETHA_FRM_PRIO_N];        /* 0340H MMPCFTCTt */
  uint32 ulMROVFC;                               /* 0360H MROVFC */
  uint32 ulMRHCRCEC;                             /* 0364H MRHCRCEC */
  uint32 ulReserved18[40];                       /*       Reserved18 */
  uint32 ulMRGFCE;                               /* 0408H MRGFCE */
  uint32 ulMRGFCP;                               /* 040CH MRGFCP */
  uint32 ulMRBFC;                                /* 0410H MRBFC */
  uint32 ulMRMFC;                                /* 0414H MRMFC */
  uint32 ulMRUFC;                                /* 0418H MRUFC */
  uint32 ulMRPEFC;                               /* 041CH MRPEFC */
  uint32 ulMRNEFC;                               /* 0420H MRNEFC */
  uint32 ulMRFMEFC;                              /* 0424H MRFMEFC */
  uint32 ulMRFFMEFC;                             /* 0428H MRFFMEFC */
  uint32 ulMRCFCEFC;                             /* 042CH MRCFCEFC */
  uint32 ulMRFCEFC;                              /* 0430H MRFCEFC */
  uint32 ulMRRCFEFC;                             /* 0434H MRRCFEFC */
  uint32 ulMRFC;                                 /* 0438H MRFC */
  uint32 ulMRGUEFC;                              /* 043CH MRGUEFC */
  uint32 ulMRBUEFC;                              /* 0440H MRBUEFC */
  uint32 ulMRGOEFC;                              /* 0444H MRGOEFC */
  uint32 ulMRBOEFC;                              /* 0448H MRBOEFC */
  uint32 ulMRXBCEU;                              /* 044CH MRXBCEU */
  uint32 ulMRXBCEL;                              /* 0450H MRXBCEL */
  uint32 ulMRXBCPU;                              /* 0454H MRXBCPU */
  uint32 ulMRXBCPL;                              /* 0458H MRXBCPL */
  uint32 ulReserved19[43];                       /*       Reserved19 */
  uint32 ulMTGFCE;                               /* 0508H MTGFCE */
  uint32 ulMTGFCP;                               /* 050CH MTGFCP */
  uint32 ulMTBFC;                                /* 0510H MTBFC */
  uint32 ulMTMFC;                                /* 0514H MTMFC */
  uint32 ulMTUFC;                                /* 0518H MTUFC */
  uint32 ulMTEFC;                                /* 051CH MTEFC */
  uint32 ulMTXBCEU;                              /* 0520H MTXBCEU */
  uint32 ulMTXBCEL;                              /* 0524H MTXBCEL */
  uint32 ulMTXBCPU;                              /* 0528H MTXBCPU */
  uint32 ulMTXBCPL;                              /* 052CH MTXBCPL */
  uint32 ulMTHDGFC;                              /* MTHDGFC          */
  uint32 ulReserved20[51];                       /*       Reserved20 */
  uint32 ulMMPFTCTM;                             /* 0600H MMPFTCTM */
  uint32 ulMAPFTCTM;                             /* 0604H MAPFTCTM */
  uint32 ulMPFRCTM;                              /* 0608H MPFRCTM */
  uint32 ulMFCICTM;                              /* 060CH MFCICTM */
  uint32 ulMEEECTM;                              /* 0610H MEEECTM */
  uint32 ulReserved21[3];                        /*       Reserved21 */
  uint32 ulMMPCFTCTtM[ETH_RACE_PAS_LVL_N];       /* 0620H MMPCFTCTtM */
  uint32 ulReserved22[2];                        /*       Reserved22 */
  uint32 ulMAPCFTCTtM[ETH_RACE_PAS_LVL_N];       /* 0630H MAPCFTCTtM */
  uint32 ulReserved23[2];                        /*       Reserved23 */
  uint32 ulMPCFRCTtM[ETH_ETHA_FRM_PRIO_N];       /* 0640H MMPCFTCTtM */
  uint32 ulReserved24[42];                       /*       Reserved24 */
  uint32 ulMRGFCEM;                              /* 0708H MRGFCEM */
  uint32 ulMRGFCPM;                              /* 070CH MRGFCPM */
  uint32 ulMRBFCM;                               /* 0710H MRBFCM */
  uint32 ulMRMFCM;                               /* 0714H MRMFCM */
  uint32 ulMRUFCM;                               /* 0718H MRUFCM */
  uint32 ulMRPEFCM;                              /* 071CH MRPEFCM */
  uint32 ulMRNEFCM;                              /* 0720H MRNEFCM */
  uint32 ulMRFMEFCM;                             /* 0724H MRFMEFCM */
  uint32 ulMRFFMEFCM;                            /* 0728H MRFFMEFCM */
  uint32 ulMRCFCEFCM;                            /* 072CH MRCFCEFCM */
  uint32 ulMRFCEFCM;                             /* 0730H MRFCEFCM */
  uint32 ulMRRCFEFCM;                            /* 0734H MRRCFEFCM */
  uint32 ulMRFCM;                                /* 0738H MRFCM */
  uint32 ulMRGUEFCM;                             /* 073CH MRGUEFCM */
  uint32 ulMRBUEFCM;                             /* 0740H MRBUEFCM */
  uint32 ulMRGOEFCM;                             /* 0744H MRGOEFCM */
  uint32 ulMRBOEFCM;                             /* 0748H MRBOEFCM */
  uint32 ulMRXBCEUM;                             /* 074CH MRXBCEUM */
  uint32 ulMRXBCELM;                             /* 0750H MRXBCELM */
  uint32 ulMRXBCPUM;                             /* 0754H MRXBCPUM */
  uint32 ulMRXBCPLM;                             /* 0758H MRXBCPLM */
  uint32 ulReserved25[43];                       /*       Reserved25 */
  uint32 ulMTGFCEM;                              /* 0808H MTGFCEM */
  uint32 ulMTGFCPM;                              /* 080CH MTGFCPM */
  uint32 ulMTBFCM;                               /* 0810H MTBFCM */
  uint32 ulMTMFCM;                               /* 0814H MTMFCM */
  uint32 ulMTUFCM;                               /* 0818H MTUFCM */
  uint32 ulMTEFCM;                               /* 081CH MTEFCM */
  uint32 ulMTXBCEUM;                             /* 0820H MTXBCEUM */
  uint32 ulMTXBCELM;                             /* 0824H MTXBCELM */
  uint32 ulMTXBCPUM;                             /* 0828H MTXBCPUM */
  uint32 ulMTXBCPLM;                             /* 082CH MTXBCPLM */
} Eth_RSW2_RMACRegType;                                                                                                 

/*********************************
**  RSW2 gPTP module Registers  **
*********************************/
typedef struct STag_Eth_RSW2_gPTPRegType                                                                                /* PRQA S 3630 # JV-01 */
{
  uint32 ulPTPIPV;                                 /* 0000H PTPIPV */
  uint32 ulReserved0[3];                           /*       Reserved0 */
  uint32 ulPTPTMEC;                                /* 0010H PTPTMEC */
  uint32 ulPTPTMDC;                                /* 0014H PTPTMDC */
  uint32 ulReserved1[2];                           /*       Reserved1 */
  struct STag_PTP{
    uint32 ulPTPTIVCt;                             /* 0020H GWDISi */
    uint32 ulReserved2[3];                         /*       Reserved2 */
    uint32 ulPTPTOVC0t;                            /* 0030H GWDIEi */
    uint32 ulPTPTOVC1t;                            /* 0034H GWDIDi */
    uint32 ulPTPTOVC2t;                            /* 0038H GWDIDSi */
    uint32 ulReserved3;                            /*       Reserved3 */
    uint32 ulPTPAVTPTM0t;                          /* 0040H GWDIDSi */
    uint32 ulPTPAVTPTM1t;                          /* 0044H GWDIDSi */
    uint32 ulReserved4[2];                         /*       Reserved4 */
    uint32 ulPTPGPTPTM0t;                          /* 0050H GWDIDSi */
    uint32 ulPTPGPTPTM1t;                          /* 0054H GWDIDSi */
    uint32 ulPTPGPTPTM2t;                          /* 0058H GWDIDSi */
    uint32 ulReserved5;                            /*       Reserved5 */
  } PTP[ETH_RACE_PTP_TN];
  uint32 ulReserved6[88];                          /*       Reserved6 */
  struct STag_PTPMCC{
    uint32 ulPTPMCCCm;                             /* 0200H PTPMCCCm */
    uint32 ulPTPMCCM0m;                            /* 0204H PTPMCCM0m */
    uint32 ulPTPMCCM1m;                            /* 0208H PTPMCCM1m */
    uint32 ulPTPMCCM2m;                            /* 020CH PTPMCCM2m */
  } PTPMCC[ETH_MEDIA_CAPT_N];
  uint32 ulReserved7[56];                          /*       Reserved7 */
  struct STag_PTPMCR{
    uint32 ulPTPMCRCm;                             /* 0300H PTPMCCCm */
    uint32 ulPTPMCRTC0m;                           /* 0304H PTPMCCM0m */
    uint32 ulPTPMCRTC1m;                           /* 0308H PTPMCCM1m */
    uint32 ulPTPMCRTC2m;                           /* 030CH PTPMCCM2m */
  } PTPMCR[ETH_MEDIA_RECV_N];
  uint32 ulReserved8[56];                          /*       Reserved8 */
  uint32 ulPTPMCPCm[ETH_MEDIA_RECV_N];             /* 0400H ulPTPMCPCm */
  uint32 ulReserved9[62];                          /*       Reserved9 */
  struct STag_PTPCCC{
    uint32 ulPTPCCC0c;                             /* 0500H PTPCCC0c */
    uint32 ulPTPCCC1c;                             /* 0504H PTPCCC1c */
  } PTPCCC[ETH_CYC_COMP_N];
  uint32 ulReserved10[112];                        /*       Reserved10 */
  uint32 ulPTPIS0;                                 /* 0700H PTPIS0 */
  uint32 ulPTPIE0;                                 /* 0704H PTPIE0 */
  uint32 ulPTPID0;                                 /* 0708H PTPID0 */
  uint32 ulReserved11;                             /*       Reserved11 */
  uint32 ulPTPIS1;                                 /* 0710H PTPIS1 */
  uint32 ulPTPIE1;                                 /* 0714H PTPIE1 */
  uint32 ulPTPID1;                                 /* 0718H PTPID1 */
  uint32 ulReserved12[25];                         /*       Reserved12 */
  uint32 ulPTPSCR0;                                /* 0780H PTPSCR0 */
  uint32 ulPTPSCR1;                                /* 0784H PTPSCR1 */
  uint32 ulPTPSCR2;                                /* 0788H PTPSCR2 */
} Eth_RSW2_gPTPRegType;

/* Limit the statistics counter value, because where the maximal possible value shall denote an invalid value */
#define ETH_STATISTICS_MAXVALUE   (ETH_UINT32_MAXVALUE - 1UL)
#define ETH_STATISTICS_LIMIT(val) ((ETH_UINT32_MAXVALUE == (val)) ? ((uint32)((val) - 1UL)) : ((uint32)(val)))          /* PRQA S 3472 # JV-01 */

/* Statistics counter register values */
typedef struct Stag_Eth_StatsRegValueType
{
  uint32 ulMROVFC;  /* Receive overflow Counter */
  uint32 ulMRFMEFC; /* RMAC Received FCS/mCRC error frame count */
  uint32 ulMRGUEFC; /* RMAC Received good undersize error frame count */
  uint32 ulMRBUEFC; /* RMAC Received bad undersize error frame count */
  uint32 ulMRGOEFC; /* RMAC Received good oversize error frame count */
  uint32 ulMRBOEFC; /* RMAC Received bad oversize error frame count */
  uint32 ulMRNEFC;  /* RMAC Received nibble error frame count */
  uint32 ulMRFCEFC; /* RMAC Received fragment count error frame count */
  uint32 ulMRXBCEU; /* RMAC Received byte counter E-frames upper side */
  uint32 ulMRXBCEL; /* RMAC Received byte counter E-frames lower side */
  uint32 ulMRXBCPU; /* RMAC Received byte counter P-frames upper side */
  uint32 ulMRXBCPL; /* RMAC Received byte counter P-frames lower side */
  uint32 ulMRFC;    /* RMAC Received fragment count error frame count */
  uint32 ulMRBFC;   /* RMAC Received good broadcast frame counter */
  uint32 ulMRUFC;   /* RMAC Received good unicast frame counter */
  uint32 ulMRMFC;   /* RMAC Received good multicast frame counter */
  uint32 ulMTXBCEU; /* RMAC Transmitted byte counter E-frames upper side */
  uint32 ulMTXBCEL; /* RMAC Transmitted byte counter E-frames lower side */
  uint32 ulMTXBCPU; /* RMAC Transmitted byte counter P-frames upper side */
  uint32 ulMTXBCPL; /* RMAC Transmitted byte counter P-frames lower side */
  uint32 ulMTBFC;   /* RMAC Transmitted broadcast frame counter */
  uint32 ulMTMFC;   /* RMAC Transmitted multicast frame counter */
  uint32 ulMTUFC;   /* RMAC Transmitted unicast frame counter */
  uint32 ulMTEFC;   /* RMAC Transmitted error frame counter */
  uint32 ulMRPEFC;  /* RMAC Received PHY error frame count */
} Eth_StatsRegValueType;


typedef struct STag_Eth_ETNE_PWRCTLRegType
{
  uint8  ucETNEzSGSDS;                 /* <PWRCTLz_base> + 0000H            */
  uint8 Reserved0[3];                  /* Reserved                          */
  uint8 ucETNEzSGCLKSEL;               /* <PWRCTLz_base> + 0004H            */
  uint8 Reserved1[3];                  /* Reserved                          */
  uint8 ucETNEzSGRCIE;                 /* <PWRCTLz_base> + 0008H            */
  uint8 Reserved2[3];                  /* Reserved                          */
} Eth_ETNE_PWRCTLRegType;

typedef struct STag_Eth_ETNE_SGMIIRegType                                                                               /* PRQA S 3630 # JV-01 */
{
  uint32 ulETNEzSGOPMC;                /* <SGMIIz_base> + 0000H             */
  uint32 ulETNEzSGOPMS;                /* <SGMIIz_base> + 0004H             */
  uint32 ulETNEzSGSRST;                /* <SGMIIz_base> + 0008H             */
  uint32 ulETNEzSGINTS;                /* <SGMIIz_base> + 000CH             */
  uint32 ulETNEzSGINTM;                /* <SGMIIz_base> + 0010H             */
  uint32 ulETNEzSGLTVC;                /* <SGMIIz_base> + 0014H             */
  uint32 ulETNEzSGCECT;                /* <SGMIIz_base> + 0018H             */
  uint32 ulETNEzSGRECT;                /* <SGMIIz_base> + 001CH             */
  uint32 Reserved0[120];                /* Reserved                          */
  Eth_ETNE_PWRCTLRegType stPWRCTL;     /* PWRCTL regs                       */
} Eth_ETNE_SGMIIRegType;

typedef struct STag_Eth_ETNE_RegType                                                                                    
{
  Eth_ETNE_SGMIIRegType *pSGMII[ETH_TOTAL_CTRL_CONFIG];                                                                 /* PRQA S 1039 # JV-01 */
} Eth_ETNE_RegType;                                                                                                     

/* EIC of RSW 2 */
typedef struct STag_Eth_ETNE_EICRegType                                                                                 /* PRQA S 3630 # JV-01 */
{
  uint16 usINTETNE00;
  uint16 usINTETNE01;
  uint16 usINTETNE02;
  uint16 usINTETNE03;
  uint16 usINTETNE04;
  uint16 usINTETNE05;
  uint16 usINTETNE06;
  uint16 usINTETNE07;
  uint16 usINTETNE08;
} Eth_ETNE_EICRegType;

/* Interrupt source selection Register */
typedef struct STag_Eth_ETNE_INTSMRegType                                                                               /* PRQA S 3630 # JV-01 */
{
  uint32 ulINTETNESEL0;
  uint32 ulINTETNESEL1;
  uint32 ulINTETNESEL2;
  uint32 ulINTETNESEL3;
  uint32 ulINTETNESEL4;
  uint32 ulINTETNESEL5;
  uint32 ulINTETNESEL6;
  uint32 ulINTETNESEL7;
  uint32 ulINTETNESEL8;
} Eth_ETNE_INTSMRegType;

typedef struct STag_Eth_RSW2_IntRegType
{
  Eth_ETNE_EICRegType *pEICReg;
  Eth_ETNE_INTSMRegType *pINTSMReg;
} Eth_RSW2_IntRegType;

/* Type of ETH interrupt handling */
typedef enum ETag_Eth_InterruptHandlingType
{
  ETH_ENABLE_INTERRUPT = 0x00,
  ETH_DISABLE_INTERRUPT = 0x01
} Eth_InterruptHandlingType;

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/
#define ETH_START_SEC_CONST_UNSPECIFIED
#include "Eth_MemMap.h"

/* RSW2 TOP module register */
extern CONSTP2VAR(volatile Eth_RSW2_TOPRegType, ETH_CONST, REGSPACE)
  Eth_GpRSW2_TOPRegs;

/* RSW2 COMA module register */
extern CONSTP2VAR(volatile Eth_RSW2_COMARegType, ETH_CONST, REGSPACE)
  Eth_GpRSW2_COMARegs;

/* RSW2 MFWD module register */
extern CONSTP2VAR(volatile Eth_RSW2_MFWDRegType, ETH_CONST, REGSPACE)
  Eth_GpRSW2_MFWDRegs;

/* RSW2 GWCA module register */
extern CONSTP2VAR(volatile Eth_RSW2_GWCARegType, ETH_CONST, REGSPACE)
  Eth_GaaRSW2_GWCARegs[ETH_MAX_GWCA_SUPPORTED];

/* RSW2 ETHA module register */
extern CONSTP2VAR(volatile Eth_RSW2_ETHARegType, ETH_CONST, REGSPACE)
  Eth_GaaRSW2_ETHARegs[ETH_MAX_TSNA_SUPPORTED];

/* RSW2 RMAC module register */
extern CONSTP2VAR(volatile Eth_RSW2_RMACRegType, ETH_CONST, REGSPACE)
  Eth_GaaRSW2_RMACRegs[ETH_MAX_RMAC_SUPPORTED];

/* RSW2 gPTP module register */
extern CONSTP2VAR(volatile Eth_RSW2_gPTPRegType, ETH_CONST, REGSPACE)
  Eth_GpRSW2_GPTPRegs;

/* RSW2 ETHA module register for controller */
extern CONSTP2VAR(volatile Eth_RSW2_ETHARegType, ETH_CONST, REGSPACE)
  Eth_GaaCtrl_ETHARegs[ETH_RACE_PORT_TSNA_N];

/* RSW2 RMAC module register for controller */
extern CONSTP2VAR(volatile Eth_RSW2_RMACRegType, ETH_CONST, REGSPACE)
  Eth_GaaCtrl_RMACRegs[ETH_RACE_PORT_TSNA_N];

extern CONST(uint32, ETH_CONST) Eth_GaaRsw2PortType[ETH_RACE_PORT_N];
extern CONST(uint32, ETH_CONST) Eth_GaaRsw2PortMap[ETH_RACE_PORT_N];

#define ETH_STOP_SEC_CONST_UNSPECIFIED
#include "Eth_MemMap.h"

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define ETH_START_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"

extern FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_ETNE_HwInit(
  CONST(uint32, AUTOMATIC) LulCtrlIdx);
extern FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_ETNE_HwDisableController(
  CONST(uint32, AUTOMATIC) LulCtrlIdx);
extern FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_ETNE_HwEnableController(
  CONST(uint32, AUTOMATIC) LulCtrlIdx);

extern FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_ETNE_HwTransmit(
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulBufIdx,
  CONST(uint32, AUTOMATIC) LulLenByte, CONST(boolean, AUTOMATIC) LblConfirmation);

#if (ETH_GET_COUNTER_VALUES_API == STD_ON)
extern FUNC(void, ETH_PRIVATE_CODE) Eth_ETNE_HwGetCounterValues(
  CONST(uint32, AUTOMATIC) LulCtrlIdx,
  CONSTP2VAR(Eth_CounterType, AUTOMATIC, ETH_APPL_DATA) LpCounterPtr);                                                  /* PRQA S 3432 # JV-01 */
#endif

#if (ETH_GET_RX_STATS_API == STD_ON)
extern FUNC(void, ETH_PRIVATE_CODE) Eth_ETNE_HwGetRxStats(
  CONST(uint32, AUTOMATIC) LulCtrlIdx,
  CONSTP2VAR(Eth_RxStatsType, AUTOMATIC, ETH_APPL_DATA) LpRxStats);                                                     /* PRQA S 3432 # JV-01 */
#endif

#if (ETH_GET_TX_STATS_API == STD_ON)
extern FUNC(void, ETH_PRIVATE_CODE) Eth_ETNE_HwGetTxStats(
  CONST(uint32, AUTOMATIC) LulCtrlIdx,
  CONSTP2VAR(Eth_TxStatsType, AUTOMATIC, ETH_APPL_DATA) LpTxStats);                                                     /* PRQA S 3432 # JV-01 */
#endif

#if (ETH_GET_TX_ERROR_COUNTER_VALUES_API == STD_ON)
extern FUNC(void, ETH_PRIVATE_CODE) Eth_ETNE_HwGetTxErrorCounterValues(
  CONST(uint32, AUTOMATIC) LulCtrlIdx,
  CONSTP2VAR(Eth_TxErrorCounterValuesType, AUTOMATIC, ETH_APPL_DATA) LpTxErrorCounterValues);                           /* PRQA S 3432 # JV-01 */
#endif

#if (ETH_CTRL_ENABLE_MII == STD_ON)
extern FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_ETNE_HwReadMii(
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint8, AUTOMATIC) LucTrcvIdx, CONST(uint8, AUTOMATIC) LucRegIdx,
  CONSTP2VAR(uint16, AUTOMATIC, ETH_APPL_DATA) LpRegValPtr);                                                            /* PRQA S 3432 # JV-01 */
extern FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_ETNE_HwWriteMii(
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint8, AUTOMATIC) LucTrcvIdx,
  CONST(uint8, AUTOMATIC) LucRegIdx  , CONST(uint16, AUTOMATIC) LusRegVal);
#endif

extern FUNC(void, ETH_PRIVATE_CODE) Eth_ETNE_HwMainFunction(CONST(uint32, AUTOMATIC) LulCtrlIdx);

#if (ETH_CTRL_ENABLE_TX_POLLING == STD_ON)
extern FUNC(void, ETH_PRIVATE_CODE) Eth_ETNE_HwTxConfirmation(
  CONST(uint32, AUTOMATIC) LulCtrlIdx);
#endif

#if (ETH_CTRL_ENABLE_RX_POLLING == STD_ON)
#if (ETH_AR_VERSION >= ETH_AR_431_VERSION)
extern FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_ETNE_HwCheckFifoIndex(
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulQueueIdx);
extern FUNC(Eth_RxStatusType, ETH_PRIVATE_CODE) Eth_ETNE_HwReceive(
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulQueueIdx);
#endif
#endif

#if (ETH_GLOBAL_TIME_SUPPORT == STD_ON)
FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_ETNE_HwGetCurrentTime(
  CONST(uint32, AUTOMATIC) LulCtrlIdx,
  CONSTP2VAR(Eth_TimeStampQualType, AUTOMATIC, ETH_APPL_DATA) LpTimeQualPtr,                                            /* PRQA S 3432 # JV-01 */
  CONSTP2VAR(Eth_TimeStampType, AUTOMATIC, ETH_APPL_DATA) LpTimeStampPtr);                                              /* PRQA S 3432 # JV-01 */

extern FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_ETNE_HwSetIncrementTimeForGptp(
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulIncVal);

extern FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_ETNE_HwSetOffsetTimeForGptp(
  CONST(uint32, AUTOMATIC) LulCtrlIdx,
  CONSTP2CONST(Eth_TimeStampType, AUTOMATIC, ETH_APPL_DATA) LpTimeOffsetPtr);

FUNC(Std_ReturnType, ETH_PRIVATE_CODE)
    Eth_ETNE_HwGetEgressTimeStamp(CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(Eth_BufIdxType, AUTOMATIC) LulBufIdx,
                             CONSTP2VAR(Eth_TimeStampQualType, AUTOMATIC, ETH_APPL_DATA) LpTimeQualPtr,                 /* PRQA S 3432 # JV-01 */
                             CONSTP2VAR(Eth_TimeStampType, AUTOMATIC, ETH_APPL_DATA) LpTimeStampPtr);                   /* PRQA S 3432 # JV-01 */

FUNC(Std_ReturnType, ETH_PRIVATE_CODE)
    Eth_ETNE_HwGetIngressTimeStamp(CONST(uint32, AUTOMATIC) LulCtrlIdx,
                              CONSTP2CONST(Eth_DataType, AUTOMATIC, ETH_APPL_DATA) LpDataPtr,
                              CONSTP2VAR(Eth_TimeStampQualType, AUTOMATIC, ETH_APPL_DATA) LpTimeQualPtr,                /* PRQA S 3432 # JV-01 */
                              CONSTP2VAR(Eth_TimeStampType, AUTOMATIC, ETH_APPL_DATA) LpTimeStampPtr);                  /* PRQA S 3432 # JV-01 */
#endif

extern FUNC(Eth_ExtRxStatusType, ETH_PRIVATE_CODE) Eth_RxQueueProcess(
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint8, AUTOMATIC) LulQueueIdx);

#define ETH_STOP_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"

#define ETH_START_SEC_CODE_FAST
#include "Eth_MemMap.h"

#if ((ETH_CTRL_ENABLE_TX_INTERRUPT == STD_ON) || (ETH_CTRL_ENABLE_RX_INTERRUPT == STD_ON))
extern FUNC(void, ETH_CODE_FAST) Eth_Gwca_DIS_Common_Isr(CONST(uint32, AUTOMATIC) LulGWCAIdx);
#endif /* #if ((ETH_CTRL_ENABLE_TX_INTERRUPT == STD_ON) || (ETH_CTRL_ENABLE_RX_INTERRUPT == STD_ON)) */

#if (ETH_GWCA0_TSDATA_ISR == STD_ON)
extern FUNC(void, ETH_CODE_FAST) Eth_Gwca_TSDIS_Common_Isr(CONST(uint32, AUTOMATIC) LulGWCAIdx);
#endif /* #if (ETH_GWCA0_TSDATA_ISR == STD_ON) */

#if (ETH_GWCA0_ERR_ISR == STD_ON)
extern FUNC(void, ETH_CODE_FAST) Eth_Gwca_ERR_Common_Isr(CONST(uint32, AUTOMATIC) LulGWCAIdx);
#endif /* #if (ETH_GWCA0_ERR_ISR == STD_ON) */

#if (ETH_COMA_ERR_ISR == STD_ON)
extern FUNC(void, ETH_CODE_FAST) Eth_Coma_ERR_Common_Isr(void);
#endif /* #if (ETH_COMA_ERR_ISR == STD_ON) */

#if ((ETH_ETHA0_ERR_ISR == STD_ON) || (ETH_ETHA1_ERR_ISR == STD_ON))
extern FUNC(void, ETH_CODE_FAST) Eth_Etha_ERR_Common_Isr(CONST(uint32, AUTOMATIC) LulETHAIdx);
#endif /* #if ((ETH_ETHA0_ERR_ISR == STD_ON) || (ETH_ETHA1_ERR_ISR == STD_ON)) */

#if (ETH_SGMII_ISR == STD_ON)
extern FUNC(void, ETH_CODE_FAST) Eth_Etha_SGMII_Common_Isr(CONST(uint32, AUTOMATIC) LulCtrlIdx);
#endif /* #if (ETH_SGMII_ISR == STD_ON) */

#define ETH_STOP_SEC_CODE_FAST
#include "Eth_MemMap.h"                                                                                                 

#endif /* !ETH_ETNE_LLDRIVER_H_ */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
