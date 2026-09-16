/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = CanXL.h                                                                                             */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2024, 2025 Renesas Electronics Corporation. All rights reserved.                                               */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Provision of external declaration of APIs and Service IDs.                                                         */
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
/*              Devices:        X2x                                                                                   */
/*====================================================================================================================*/

/***********************************************************************************************************************
**                                                  Revision History                                                  **
***********************************************************************************************************************/
/*
 * 2.4.1: 30/06/2025  : Remove the SW-VERSION from header of file
 * 2.4.0:  30/05/2025 : Add macro CANXL_PACK_TX_DATA
 * 2.3.1:  31/03/2025 : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 *                      Update CANXL_RXPROCESSING_SID's value
 * 2.3.0:  28/02/2025 : As part of ARDAACL-52560: 
 *                      Update value of CANXL_MODULE_ID, CANXL_INSTANCE_ID
 *                      Add macro CANXL_RXPROCESSING_SID
 * 2.2.0: 31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 *                      As part of CANXL driver support, following changes are made:
 *                      1. Update value CAN_DMA1_RESET_VALUE
 * 2.1.2: 31/10/2024  : As part of CANXL driver support, following changes are made:
 *                      1. Add macro CANXL_BUSOFF_BUFFER_ID
 * 2.1.1: 29/07/2024  : As part of CANXL driver support, following changes are made:
 *                      1. Update extern for function declaration
 *        20/06/2024  : As part of CANXL driver support, following changes are made:
 *                      1. Update default macros for CanXL registers supporting CanXL_DeInitController 
 *        10/06/2024  : As part of CANXL driver support, following changes are made:
 *                      1. Update macro CANXL_BIT_PLSRC, CANXL_DMA2_FIXED_FQ, CANXL_DMA2_FIXED_PQ, CANXL_IRC_FUNC_RX_IRQ
 *                      2. Add new macro CAN_DMA1_RESET_VALUE, CAN_DMA2_RESET_VALUE, CANXL_IRC_FUNC_TFX_IRQ, 
 *                      CANXL_IRC_FUNC_TPX_IRQ
 *        19/05/2024  : As part of CANXL driver support, following changes are made:
 *                      1. Add CANXL_E_INVALID_CORE to support multicore for CANXL
 * 2.0.3: 13/04/2024  : Add CANFD_BIT_FDF, CANFD_BIT_XLF, CANFD_BIT_XTD, CANFD_BIT_BASEID, CANFD_BIT_EXTID,
 *                      CANFD_BIT_RESERVED0, CANFD_BIT_FIR, CANFD_BIT_RESERVED1, CANFD_BIT_RESERVED2, CANFD_BIT_BRS, 
 *                      CANFD_BIT_RESERVED3, CANFD_BIT_ESI, CANFD_BIT_DLC, CANFD_BIT_RESERVED4, CANFD_T1_FIXED,
 *                      CANXL_IRC_FUNC_RX_IRQ, CANXL_XLFF_FORMAT, CANFD_T0_FIXED
 * 2.0.2: 15/01/2024  : Remove message 1534 
 *        02/01/2024  : Initial version.
 */
#ifndef CANXL_H
#define CANXL_H

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Inclusion  #include "Std_Types.h" */
#include "Can_GeneralTypes.h"

/* Include Can header file */
#include "Can.h"
#include "Can_LTTypes.h"
#include "Can_ModeCntrl.h"
/* Include Eth interface header file */
#if (CAN_CANXL_SUPPORTED == STD_ON)
#include "Eth_GeneralTypes.h"
#include "EthIf.h"
#include "EthIf_Cbk.h"
#endif
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:3472)    : All toplevel uses of this function-like macro look like they could be replaced by            */
/*                       equivalent function calls.                                                                   */
/* Rule                : MISRA C:2012 Dir-4.9                                                                         */
/* JV-01 Justification : This message indicates that a candidate macro may be suitable for replacement by a           */
/*                       function, based on an actual call-site and the arguments passed to it there                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

#if (CAN_CANXL_SUPPORTED == STD_ON)
/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/
/**
 * CAN XL Representive
*/
#define CANXL_MODULE_ID                              85U

#define CANXL_ONE                                    1U         
#define CANXL_ZERO                                   0U         
#define CANXL_MAX_PAYLOAD                            2048U      
#define CANXL_TOTAL_TXRX_FIFOQUEUE                   32U        
#define CANXL_RXFIFO_OFFSET                          8U         
/**
 * SDU Type for CAN XL frame - refer CiA611-1 standard
*/
/* Content Based Addressing */
#define CANXL_SDU_TYPE_CANXL_CONTEN_BASE_ADDR_FRAME  (uint8)0x01U
/* Node Addressing */
#define CANXL_SDU_TYPE_CANXL_NODE_ADDR_FRAME         (uint8)0x02U
/* Classical & FD Frame Tunneling */
#define CANXL_SDU_TYPE_CANFD_FRAME                   (uint8)0x03U
/* IEEE 802.3 (Eth) Tunneling */
#define CANXL_SDU_TYPE_ETH_TUNELLING                 (uint8)0x04U
/* IEEE 802.3 (Eth) mapped Tunneling */
#define CANXL_SDU_TYPE_ETH_MAPPED_TUNELLING          (uint8)0x05U
/**
 * Error handling - Development error
*/
/* API Service called with wrong parameter */
#define CANXL_E_PARAM_POINTER                        (uint8)0x01
/* API Service called with wrong parameter */ 
#define CANXL_E_PARAM_HANDLE                         (uint8)0x02
/* API Service called with wrong parameter */ 
#define CANXL_E_PARAM_DATA_LENGTH                    (uint8)0x03
/* API Service called with wrong parameter */ 
#define CANXL_E_PARAM_CONTROLLER                     (uint8)0x04
/* API Service used without initialization */ 
#define CANXL_E_UNINIT                               (uint8)0x05
/* Invalid parameter */
#define CANXL_E_INV_PARAM                            (uint8)0x10
/* Invalid mode */
#define CANXL_E_INV_MODE                             (uint8)0x11
/**
 * Error handling - Runtime errors
*/
/* Invalid data */
#define CANXL_E_INV_DATA                             (uint8)0x12

/* Invalid core */
#if (CAN_MULTI_CORE_SUPPORT == STD_ON)
#define CANXL_E_INVALID_CORE                         (uint8)0xF1U
#endif
/**
 * Service ID for CAN XL specific
*/
#define CANXL_INSTANCE_ID                            CAN_INSTANCE_ID_VALUE 
/* Service ID for CanXL_Write */
#define CANXL_WRITE_SID                              (uint8)0x10

#define CANXL_GET_CONTROLLER_MODE_SID                0x04U      

#define CANXL_SET_CONTROLLER_MODE_SID                0x03U      

#define CANXL_PROVIDETXBUFFER_SID                    0x09U      

#define CANXL_TRANSMIT_SID                           0xAU       

#define CANXL_RECEIVE_SID                            0xBU       

#define CANXL_GETCURRENTTIME_SID                     0x16U      

#define CANXL_ENABLEEGRESSTS_SID                     0x17U      

#define CANXL_GETEGRESSTS_SID                        0x18U      

#define CANXL_GETINGRESSTS_SID                       0x19U      

#define CANXL_GETPHYSADDR_SID                        0x08U      

#define CANXL_SETPHYSADDR_SID                        0x13U      

#define CANXL_UPDATEPHYSADDRFILTER_SID               0x12U      

#define CANXL_TXCONFIRMATION_SID                     0xCU       

#define CANXL_RXPROCESSING_SID                       0x25U

#define CANXL_TX_DESC                                (uint8)(0U)
#define CANXL_RX_DESC                                (uint8)(1U)
/* DMA Info Ctrl 1 for Tx Queue */
#define CANXL_BIT_VALID(x)                           ((uint32)(x) << 31UL)                                              /* PRQA S 3472 # JV-01 */
#define CANXL_BIT_HD                                 (0x01UL << 30UL)
#define CANXL_BIT_WRAP                               (0x00UL << 29UL)
#define CANXL_BIT_NEXT                               (0x00UL << 28UL)
#define CANXL_BIT_IRQ(x)                             ((uint32)(x) << 27UL)                                              /* PRQA S 3472 # JV-01 */
#define CANXL_BIT_PQ                                 (0x01UL << 26UL)
#define CANXL_BIT_FQ                                 (0x00UL << 26UL)
#define CANXL_BIT_RESERVED1                          (0x00UL << 25UL)
#define CANXL_BIT_CRC(x)                             ((uint32)(x) << 16UL)                                              /* PRQA S 3472 # JV-01 */
#define CANXL_BIT_PQSN(x)                            ((uint32)(x) << 11UL)                                              /* PRQA S 3472 # JV-01 */
#define CANXL_BIT_FQN(x)                             ((uint32)(x) << 12UL)                                              /* PRQA S 3472 # JV-01 */
#define CANXL_BIT_RESERVED2                          (0x00UL << 11UL)
#define CANXL_BIT_RESERVED3                          (0x00UL << 9UL) 
#define CANXL_BIT_RC(x)                              (((uint32)(x) & 0x1FUL) << 4UL)                                    /* PRQA S 3472 # JV-01 */
#define CANXL_BIT_STS                                (0x00UL)   

/* DMA Info Ctrl 2 for Tx Queue */
#define CANXL_BIT_RESERVED4                          (0X00UL << 27UL)
#define CANXL_BIT_PLSRC(x)                           ((uint32)(x) << 26UL)                                              /* PRQA S 3472 # JV-01 */
#define CANXL_BIT_SIZE(x)                            ((uint32)(x) << 16UL)                                              /* PRQA S 3472 # JV-01 */
#define CANXL_BIT_IN(x)                              ((uint32)(x) << 13UL)                                              /* PRQA S 3472 # JV-01 */
#define CANXL_BIT_RESERVED5                          (0x00UL << 12UL)
#define CANXL_BIT_TDO                                (0x00UL << 2UL) 
#define CANXL_BIT_NHDO                               (0x3FFUL << 2UL)
#define CANXL_BIT_RESERVED6                          (0x00UL)   

#define CANXL_DMA1_FIXED_PQ                                     \
    (uint32)(CANXL_BIT_HD | CANXL_BIT_WRAP | CANXL_BIT_NEXT | \
            CANXL_BIT_PQ | CANXL_BIT_RESERVED1 | \
            CANXL_BIT_RESERVED3 | CANXL_BIT_STS)

#define CANXL_DMA2_FIXED_PQ                                     \
    (uint32)(CANXL_BIT_RESERVED4 | \
            CANXL_BIT_RESERVED5 | CANXL_BIT_TDO | CANXL_BIT_RESERVED6)

#define CANXL_DMA1_FIXED_FQ                                     \
    (uint32)(CANXL_BIT_HD | CANXL_BIT_WRAP | CANXL_BIT_NEXT | \
            CANXL_BIT_FQ | CANXL_BIT_RESERVED1 | \
            CANXL_BIT_RESERVED2| CANXL_BIT_RESERVED3 | CANXL_BIT_STS)

#define CANXL_DMA2_FIXED_FQ                                     \
    (uint32)(CANXL_BIT_RESERVED4 | \
            CANXL_BIT_RESERVED5 | CANXL_BIT_NHDO | CANXL_BIT_RESERVED6)

#define CAN_DMA1_RESET_VALUE                         ~((uint32)(0x0FUL | CANXL_BIT_CRC(0x1FFUL)))

#define CAN_DMA2_RESET_VALUE                         ~((uint32)(CANXL_BIT_PLSRC(0x1UL) | CANXL_BIT_SIZE(0x3FUL)))

/* T0 for Tx Queue */
#define CANXL_BIT_FDF                                (0x01UL << 31UL)
#define CANXL_BIT_XLF                                (0x01UL << 30UL)
#define CANXL_BIT_XTD                                (0x00UL << 29UL)
#define CANXL_BIT_PRID(x)                            ((uint32)(x) << 18UL)                                              /* PRQA S 3472 # JV-01 */
#define CANXL_BIT_RRS                                (0x00UL << 17UL)
#define CANXL_BIT_SEC(x)                             ((uint32)(x) << 16UL)                                              /* PRQA S 3472 # JV-01 */
#define CANXL_BIT_VCID(x)                            ((uint32)(x) << 8UL)                                               /* PRQA S 3472 # JV-01 */
#define CANXL_BIT_SDT(x)                             (x)                                                                /* PRQA S 3472 # JV-01 */

#define CANXL_T0_FIXED                                          \
    (uint32)(CANXL_BIT_FDF | CANXL_BIT_XLF | CANXL_BIT_XTD | \
            CANXL_BIT_RRS | CANXL_BIT_VCID(0))

#define CANFD_BIT_FDF(x)                             ((uint32)(x) << 31UL)                                              /* PRQA S 3472 # JV-01 */
#define CANFD_BIT_XLF                                (0x00UL << 30UL)
#define CANFD_BIT_XTD(x)                             ((uint32)(x) << 29UL)                                              /* PRQA S 3472 # JV-01 */
#define CANFD_BIT_BASEID(x)                          ((uint32)(x) << 18UL)                                              /* PRQA S 3472 # JV-01 */
#define CANFD_BIT_EXTID(x)                           (x)                                                                /* PRQA S 3472 # JV-01 */       

#define CANFD_T0_FIXED                               (uint32)(CANFD_BIT_XLF)

/* T1 for Tx Queue */
#define CANXL_BIT_RESERVED7                          (0x00UL << 31UL)
#define CANXL_BIT_FIR                                (0x00UL << 30UL)
#define CANXL_BIT_RESERVED8                          (0x00UL << 27UL)
#define CANXL_BIT_DLCXL(x)                           (uint32)((uint32)(x) << 16UL)
#define CANXL_BIT_RESERVED9                          (0x00UL)   

#define CANXL_T1_FIXED                                          \
    (uint32)(CANXL_BIT_RESERVED7 | CANXL_BIT_FIR | \
            CANXL_BIT_RESERVED8 | CANXL_BIT_RESERVED9)

#define CANFD_BIT_RESERVED0                          (0x00UL << 31UL)
#define CANFD_BIT_FIR                                (0x00UL << 30UL)
#define CANFD_BIT_RESERVED1                          (0x00UL << 27UL)
#define CANFD_BIT_RESERVED2                          (0x00UL << 26UL)
#define CANFD_BIT_BRS(x)                             ((uint32)(x) << 25UL)                                              /* PRQA S 3472 # JV-01 */
#define CANFD_BIT_RESERVED3                          (0x00UL << 21UL)
#define CANFD_BIT_ESI(x)                             ((uint32)(x) << 20UL)
#define CANFD_BIT_DLC(x)                             (uint32)((uint32)(x) << 16UL)
#define CANFD_BIT_RESERVED4                          (0x00UL)

#define CANFD_T1_FIXED    \
    (uint32)(CANFD_BIT_RESERVED0 | CANFD_BIT_FIR | CANFD_BIT_RESERVED1 | \
            CANFD_BIT_RESERVED2 | CANFD_BIT_RESERVED3 | CANFD_BIT_RESERVED4)

/* DMA Info Ctrl 1 for Rx Queue */
#define CANXL_RX_BIT_VALID(x)                        ((uint32)(x) << 31UL)                                              /* PRQA S 3472 # JV-01 */
#define CANXL_RX_BIT_HD                              (0x00UL << 30UL)
#define CANXL_RX_BIT_RESERVED1                       (0x00UL << 29UL)
#define CANXL_RX_BIT_NEXT                            (0x00UL << 28UL)
#define CANXL_RX_BIT_IRQ(x)                          ((uint32)(x) << 27UL)                                              /* PRQA S 3472 # JV-01 */
#define CANXL_RX_BIT_RESERVED2                       (0x00UL << 25UL)
#define CANXL_RX_BIT_CRC(x)                          ((uint32)(x) << 16UL)                                              /* PRQA S 3472 # JV-01 */
#define CANXL_RX_BIT_FQN(x)                          ((uint32)(x) << 12UL)                                              /* PRQA S 3472 # JV-01 */
#define CANXL_RX_BIT_IN(x)                           ((uint32)(x) << 9UL)                                               /* PRQA S 3472 # JV-01 */
#define CANXL_RX_BIT_RC(x)                           (((uint32)(x) & 0x1FUL) << 4UL)                                    /* PRQA S 3472 # JV-01 */
#define CANXL_RX_BIT_STS                             (0x00UL << 0UL) 

#define CANXL_RX_DMA1_FIXED                                     \
    (uint32)(CANXL_RX_BIT_HD | CANXL_RX_BIT_RESERVED1 | \
            CANXL_RX_BIT_NEXT | CANXL_RX_BIT_RESERVED2 | CANXL_RX_BIT_STS)
                                                            
#define CANXL_RXQ_NUM                               40U         
/* R0 for Tx Queue */
#define CANXL_RX_BIT_PRIO(x)                        ((uint32)(x) >> 18UL)                                               /* PRQA S 3472 # JV-01 */
#define CANXL_RX_BIT_SEC(x)                         ((uint32)(x) >> 16UL)                                               /* PRQA S 3472 # JV-01 */
#define CANXL_RX_BIT_VCID(x)                        ((uint32)(x) >> 8UL)                                                /* PRQA S 3472 # JV-01 */
#define CANXL_RX_BIT_SDT(x)                         ((uint32)(x) >> 0UL)                                                /* PRQA S 3472 # JV-01 */

#define CANXL_BYTE_BITS                              8UL        
/* R1 for Tx Queue */
#define CANXL_RX_BIT_DLCXL(x)                       ((uint32)(x) >> 16UL)                                               /* PRQA S 3472 # JV-01 */
/* Tx FIFO Queue interrupt bits in FUNC_INT */
#define CANXL_IRC_FUNC_TFX_IRQ(x)                                            (uint32)(1UL << (x))
/* Tx Priority Queue interrupt bits in FUNC_INT */
#define CANXL_IRC_FUNC_TPX_IRQ                                               (uint32)(1UL << 16UL)
/* Rx FIFO Queue interrupt bits in FUNC_INT */
#define CANXL_IRC_FUNC_RX_IRQ(x)                                             (uint32)(1UL << (x + 8UL))
/* Macros to convert between byte array and the structure */
#define CANXL_PACK_ADDRESS_FROM_8(src, dst) do {                                                                        /* PRQA S 3472 # JV-01 */\
  (dst).ulH32 = ((uint32)(src)[0U] << 24UL) | ((uint32)(src)[1U] << 16UL) | \
  ((uint32)(src)[2U] << 8UL) | (uint32)(src)[3U]; \
  (dst).ulL16 = ((uint32)(src)[4U] << 8UL) | (uint32)(src)[5U]; } while (0)

#define CANXL_UNPACK_ADDRESS_TO_8(src, dst) do {                                                                        /* PRQA S 3472 # JV-01 */\
  (dst)[0] = (uint8)((src).ulH32 >> 24UL); \
  (dst)[1] = (uint8)((src).ulH32 >> 16UL); \
  (dst)[2] = (uint8)((src).ulH32 >> 8UL); \
  (dst)[3] = (uint8)(src).ulH32; \
  (dst)[4] = (uint8)((src).ulL16 >> 8UL); \
  (dst)[5] = (uint8)(src).ulL16; } while (0)   

#define CAN_DWORD_SIZE         4UL                              
#define CAN_ALIGN_TO_32BIT(n)  ((((n) + CAN_DWORD_SIZE) - 1UL) & 0xFFFFFFFCUL)                                          /* PRQA S 3472 # JV-01 */

/* Copy the MAC address */
#define CANXL_COPY_MAC_ADDRESS(src, dst) do {                                                                           /* PRQA S 3472 # JV-01 */\
  (dst)[0] = (src)[0]; \
  (dst)[1] = (src)[1]; \
  (dst)[2] = (src)[2]; \
  (dst)[3] = (src)[3]; \
  (dst)[4] = (src)[4]; \
  (dst)[5] = (src)[5]; } while (0)  
      
#define CANXL_PACK_ADDRESS_FROM_4(src, dst) do {                \
  dst = ((uint32)(src)[0U] << 24UL) | ((uint32)(src)[3U] << 16UL) | \
  ((uint32)(src)[4U] << 8UL) | (uint32)(src)[5U];} while (0)
      
/* Compare two MAC addresses, return 0 when both are equal */
#define CANXL_COMPARE_MAC(a, b) (((a).ulH32 ^ (b).ulH32) | ((a).ulL16 ^ ((b).ulL16)))                                   /* PRQA S 3472 # JV-01 */
  
/* Check whether a address has the multicast bit */
#define CANXL_CHECK_MULTICAST(addr) ((addr).ulH32 & 0x01000000UL)                                                       /* PRQA S 3472 # JV-01 */

#define CANXL_FILTER_COUNT_MAX 0x00000001UL                     

#define CANXL_MAX_FILTERS                   32UL                

#define CANXL_MAX_PRIORITYQUEUE_SLOT        32UL                

#define CANXL_CVLAN_TAG                     0x8100U             

#define CANXL_SVLAN_TAG                     0x88A8U             

#define CANXL_PACK_TX_DATA(src, dst) do {                \
  dst = ((uint32)(src)[0U]) | ((uint32)(src)[1U] << 8UL) | \
  ((uint32)(src)[2U] << 16UL) | ((uint32)(src)[3U] << 24UL);} while (0)

#define CANXL_RXFIFO_SIZE(x, y)             (uint32)((uint32)(x) | ((uint32)(y) << 16UL))
/* The size offset of header format */
#define CANXL_HEADER_SIZE                   14UL                
/* The size offset of Src and dst */
#define CANXL_SRC_DST_ADDRESS_SIZE          12UL                
/* The size offset of EtherType */
#define CANXL_ETHERTYPE_SIZE                2UL                 
/* The mask of SDT in Rx */
#define CANXL_RX_SDT_MASK                   0x400000FFUL        
/* The mask of RX FIFO Queue in FUNC */
#define CANXL_FUNC_RX_FIFO_MASK             0x0000FF00UL        
/* The size offset of R3 field into Rx */
#define CANXL_R3_SIZE                       12UL                
/* The mask of DLC Rx */
#define CANXL_DLC_MASK                      0x000007FFUL        
/* The mask of VCID Rx */
#define CANXL_RX_VCID_MASK                  0x0000FF00UL
/* The mask of XLFF format */
#define CANXL_XLFF_FORMAT                   0x00000003UL
/* The Buffer ID of Bus-Off handling */
#define CANXL_BUSOFF_BUFFER_ID              0x00000000UL
/* The default value */
#define CANXL_IRC_ENABLE_DEFAULT            0x00000000UL
#define CANXL_IRC_CAPTURE_DEFAULT           0x00000000UL
#define CANXL_PRT_MODE_DEFAULT              0x00000000UL
#define CANXL_PRT_BITRATE_DEFAULT           0x00000000UL
#define CANXL_PRT_PWM_DEFAULT               0x00000000UL
#define CANXL_MH_CFG_DEFAULT                0x00000000UL
#define CANXL_MH_SFTYCFG_DEFAULT            0x00000000UL
#define CANXL_MH_SFTYCTRL_DEFAULT           0x00000000UL
#define CANXL_MH_AXIADD_DEFAULT             0x00000000UL
#define CANXL_MH_AXIPAR_DEFAULT             0x00000000UL
#define CANXL_MH_TXFTCTRL0_DEFAULT          0x00000000UL
#define CANXL_MH_TXFTCTRL1_DEFAULT          0x00000000UL
#define CANXL_MH_TXFTREF_DEFAULT            0x00000000UL
#define CANXL_MH_TXDADD_DEFAULT             0x00000000UL
#define CANXL_MH_TXSTADD_DEFAULT            0x00000000UL
#define CANXL_MH_TXSIZE_DEFAULT             0x00000000UL
#define CANXL_MH_RXSTADD_DEFAULT            0x00000000UL
#define CANXL_MH_RXSIZE_DEFAULT             0x00000000UL
#define CANXL_MH_RXDCSTADD_DEFAULT          0x00000000UL
#define CANXL_MH_RXRDADDPT_DEFAULT          0x00000000UL
#define CANXL_MH_RXFADD_DEFAULT             0x00000000UL
#define CANXL_RXFILTER_DEFAULT              0x00000000UL
#define CANXL_DESCRIPTOR_DEFAULT            0x00000000UL
/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/
#define CAN_START_SEC_PUBLIC_CODE
#include "Can_MemMap.h"
/*
* CanXL_Write
*/
extern FUNC(Can_CommonReturnType, CAN_PUBLIC_CODE) CanXL_Write(VAR(Can_HwHandleType, AUTOMATIC) Hth,
                                      P2CONST(CanXL_PduType, AUTOMATIC, CAN_APPL_DATA) PduInfo);
/**
 * CanXL_GetControllerMode
*/
extern FUNC(Std_ReturnType, CAN_PUBLIC_CODE) CanXL_GetControllerMode (uint8 CtrlIdx, Eth_ModeType* CtrlModePtr);
/**
 * CanXL_GetCounterValues
*/
extern FUNC(Std_ReturnType, CAN_PUBLIC_CODE) CanXL_GetCounterValues (uint8 CtrlIdx, Eth_CounterType* CounterPtr);

#if(CAN_CANXL_GLOBAL_TIME_SUPPORT == STD_ON)
/**
 * CanXL_EnableEgressTimeStamp
*/
extern FUNC(void, CAN_PUBLIC_CODE) CanXL_EnableEgressTimeStamp (uint8 CtrlIdx, Eth_BufIdxType BufIdx);
/**
 * CanXL_GetCurrentTime
*/
extern FUNC(Std_ReturnType, CAN_PUBLIC_CODE) CanXL_GetCurrentTime (uint8 CtrlIdx, 
                                                   Eth_TimeStampQualType* timeQualPtr, Eth_TimeStampType* timeStampPtr);
/**
 * CanXL_GetEgressTimeStamp
*/
extern FUNC(Std_ReturnType, CAN_PUBLIC_CODE) CanXL_GetEgressTimeStamp (uint8 CtrlIdx, Eth_BufIdxType BufIdx, 
                                                   Eth_TimeStampQualType* timeQualPtr, Eth_TimeStampType* timeStampPtr);
/**
 * CanXL_GetIngressTimeStamp
*/
extern FUNC(Std_ReturnType, CAN_PUBLIC_CODE) CanXL_GetIngressTimeStamp (uint8 CtrlIdx, const Eth_DataType* DataPtr, 
                                                   Eth_TimeStampQualType* timeQualPtr, Eth_TimeStampType* timeStampPtr);
#endif /* CAN_CANXL_GLOBAL_TIME_SUPPORT */
/**
 * CanXL_GetPhysAddr
*/
extern FUNC(void, CAN_PUBLIC_CODE) CanXL_GetPhysAddr (uint8 CtrlIdx, uint8* PhysAddrPtr);
/**
 * CanXL_GetRxStats
*/
extern FUNC(Std_ReturnType, CAN_PUBLIC_CODE) CanXL_GetRxStats (uint8 CtrlIdx, Eth_RxStatsType* RxStats);
/**
 * CanXL_GetTxErrorCounterValues
*/
extern FUNC(Std_ReturnType, CAN_PUBLIC_CODE) CanXL_GetTxErrorCounterValues (uint8 CtrlIdx, 
                                                                    Eth_TxErrorCounterValuesType* TxErrorCounterValues);
/**
 * CanXL_GetTxStats
*/
extern FUNC(Std_ReturnType, CAN_PUBLIC_CODE) CanXL_GetTxStats (uint8 CtrlIdx, Eth_TxStatsType* TxStats);
/**
 * CanXL_ProvideTxBuffer
*/
extern FUNC(BufReq_ReturnType, CAN_PUBLIC_CODE) CanXL_ProvideTxBuffer (uint8 CtrlIdx, uint8 Priority, 
                                                         Eth_BufIdxType* BufIdxPtr, uint8** BufPtr, uint16* LenBytePtr);
/**
 * CanXL_Receive
*/
extern FUNC(void, CAN_PUBLIC_CODE) CanXL_Receive(uint8 CtrlIdx, uint8 QueueIdx, Eth_RxStatusType* RxStatusPtr);
/**
 * CanXL_SetControllerMode
*/
extern FUNC(Std_ReturnType, CAN_PUBLIC_CODE) CanXL_SetControllerMode (uint8 CtrlIdx, Eth_ModeType CtrlMode);
/**
 * CanXL_SetPhysAddr
*/
extern FUNC(void, CAN_PUBLIC_CODE) CanXL_SetPhysAddr ( uint8 CtrlIdx, const uint8* PhysAddrPtr);
/**
 * CanXL_Transmit
*/
extern FUNC(Std_ReturnType, CAN_PUBLIC_CODE) CanXL_Transmit (uint8 CtrlIdx, Eth_BufIdxType BufIdx, 
                         Eth_FrameType FrameType , boolean TxConfirmation, uint16 LenByte, const uint8* PhysAddrPtr);
/**
 * CanXL_TxConfirmation
*/
extern FUNC(void, CAN_PUBLIC_CODE) CanXL_TxConfirmation (uint8 CtrlIdx);
/**
 * CanXL_UpdatePhysAddrFilter
*/
extern FUNC(Std_ReturnType, CAN_PUBLIC_CODE) CanXL_UpdatePhysAddrFilter (uint8 CtrlIdx, const uint8* PhysAddrPtr, 
                                                                                           Eth_FilterActionType Action);
                             
#define CAN_STOP_SEC_PUBLIC_CODE
#include "Can_MemMap.h"

#endif /* #if (CAN_CANXL_SUPPORTED == STD_ON) */

#endif /* CANXL_H */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
