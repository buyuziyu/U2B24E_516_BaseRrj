/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Can_MainServ.h                                                                                      */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2019-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* C header file for Can_MainServ.c                                                                                   */
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
 * 2.4.0: 30/05/2025  : Update SW-VERSION for RH850/Ver22.01.00 (D) U2Ax Release
 * 2.3.1: 31/03/2025  : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 *                      Update value of CAN_RXPROC_TXRXFIFO_ALL, CAN_RXPROC_RXFIFO,
 *                      CAN_RXPROC_RXFIFO_ALL
 * 2.3.0: 28/02/2025  : Update SW-VERSION for RH850/Ver22.01.00/Ver22.01.00.D Final Release
 * 2.2.0: 31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 *                      As part of CANXL driver support, following changes are made:
 *                      1. Add new define CAN_ID_STANDARDTYPE_IDMASK, CANXL_PRIORITY_IDMASK
 * 2.1.2: 31/10/2024  : As part of U2Ax driver support, following changes are made:
 *                      1. Update condition for payload size and DLC register value
 *                      2. Add macro CAN_MAINFUNCTION_INSTANCE_20, CAN_MAINFUNCTION_INSTANCE_21
 * 2.1.1: 30/08/2024  : As part of CANXL driver support, following changes are made:
 *                      1. Add macro CAN_MAINFUNCTION_INSTANCE_15 to CAN_MAINFUNCTION_INSTANCE_19
 *                      2. Remove message 1534
 *                      3. Add Function Prototype for Can_CanXLTxConfirmation, CanXL_RxProcessing
 * 2.0.1: 06/11/2023  : Remove redundant QAC message
 *        19/10/2023  : Add message 1534
 * 2.0.0: 16/08/2023  : Update condition in function Can_TxConfirmationProcessing()
 *        02/08/2023  : Remove multi instance and change from Can_Mapping.h to Can_MemMap.h
 *                      Remove redundant QAC message
 *                      Add CWE Rule
 *        28/06/2023  : Remove redundant QAC messages
 *        27/06/2023  : Add Can_BufferValidateRead function
 * 1.3.2: 30/08/2021  : Update to support multi-instance:
 *                      - Add precondition check CAN_INSTANCE_INDEX
 *                      - Change include to Can_Mapping.h
 * 1.3.1: 02/07/2021  : Add QAC message 9.5.0
 *                      Format source code to 120 characters
 *                      Improve Violation tag (remove START/END)
 *        05/05/2021  : Update the memory section, memclass, ptrclass to change
 *                      the CAN_RSCAN prefix to CAN
 * 1.2.0: 09/07/2020  : Release.
 *        28/07/2020  : Add QAC 9.3.1 comment.
 * 1.1.0: 19/06/2020  : Release.
 * 1.0.1: 19/03/2020  : Add macro CAN_ONE, CAN_TWO, CAN_THREE.
 *                      Fix QAC findings
 *        11/03/2020  : Update value of marco CAN_RXPROC_BUFFER,
 *                      CAN_RXPROC_TXRXFIFO_ALL, CAN_RXPROC_RXFIFO(unit)
 *                      CAN_RXPROC_RXFIFO_ALL.
 * 1.0.0: 09/12/2019  : Initial version.
 */
/**********************************************************************************************************************/

#ifndef CAN_MAINSERV_HEADER
#define CAN_MAINSERV_HEADER

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/

/* AUTOSAR Release version information */
#define CAN_MAINSERV_AR_RELEASE_MAJOR_VERSION    CAN_AR_RELEASE_MAJOR_VERSION
#define CAN_MAINSERV_AR_RELEASE_MINOR_VERSION    CAN_AR_RELEASE_MINOR_VERSION
#define CAN_MAINSERV_AR_RELEASE_REVISION_VERSION CAN_AR_RELEASE_REVISION_VERSION

/* File version information */
#define CAN_MAINSERV_SW_MAJOR_VERSION            CAN_SW_MAJOR_VERSION
#define CAN_MAINSERV_SW_MINOR_VERSION            CAN_SW_MINOR_VERSION

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

/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/
/* 4byte align */
#define CAN_ALIGN_4(value)                       (((uint32)(value) + 3UL) & (uint32)(~3UL))                             /* PRQA S 3472 # JV-01 */

/* Instance indexes of MainFunctions */
#define CAN_MAINFUNCTION_INSTANCE_0              0U
#define CAN_MAINFUNCTION_INSTANCE_1              1U
#define CAN_MAINFUNCTION_INSTANCE_2              2U
#define CAN_MAINFUNCTION_INSTANCE_3              3U
#define CAN_MAINFUNCTION_INSTANCE_4              4U
#define CAN_MAINFUNCTION_INSTANCE_5              5U
#define CAN_MAINFUNCTION_INSTANCE_6              6U
#define CAN_MAINFUNCTION_INSTANCE_7              7U
#define CAN_MAINFUNCTION_INSTANCE_8              8U
#define CAN_MAINFUNCTION_INSTANCE_9              9U
#define CAN_MAINFUNCTION_INSTANCE_10             10U
#define CAN_MAINFUNCTION_INSTANCE_11             11U
#define CAN_MAINFUNCTION_INSTANCE_12             12U
#define CAN_MAINFUNCTION_INSTANCE_13             13U
#define CAN_MAINFUNCTION_INSTANCE_14             14U
#define CAN_MAINFUNCTION_INSTANCE_15             15U
#define CAN_MAINFUNCTION_INSTANCE_16             16U
#define CAN_MAINFUNCTION_INSTANCE_17             17U
#define CAN_MAINFUNCTION_INSTANCE_18             18U
#define CAN_MAINFUNCTION_INSTANCE_19             19U
#define CAN_MAINFUNCTION_INSTANCE_20             20U
#define CAN_MAINFUNCTION_INSTANCE_21             21U
/* size of the local buffer */
#if ((CAN_RSCANFD_CONFIGURED == STD_ON)  || (CANFD_ON_XL_BUS_SUPPORT == STD_ON))
#define CAN_LOCALBUFFER_SIZE_32 (CAN_CANFD_MAX_PAYLOAD / sizeof(uint32))
#else
#define CAN_LOCALBUFFER_SIZE_32 (CAN_STD_MAX_PAYLOAD / sizeof(uint32))
#endif

#if (CAN_CANXL_SUPPORTED == STD_ON)
/* Maximum payload length for CAN-XL */
#define CAN_CANXL_MAX_PAYLOAD     2048U
#define CANXL_LOCALBUFFER_SIZE_32 (CAN_CANXL_MAX_PAYLOAD / sizeof(uint32))
#endif

/* Inform Can_RxProcessing of target buffers */
#define CAN_RXPROC_BUFFER         0x00000001UL
#define CAN_RXPROC_TXRXFIFO(cntl) (0x00000010UL << (cntl))                                                              /* PRQA S 3472 # JV-01 */
#define CAN_RXPROC_TXRXFIFO_ALL   0x00FFFFF0UL
#define CAN_RXPROC_RXFIFO(unit)   (0x01000000UL << (unit))                                                              /* PRQA S 3472 # JV-01 */
#define CAN_RXPROC_RXFIFO_ALL     0x0F000000UL

/* Format flags in Can_IdType to inform CanIf */
#ifdef CAN_CANTYPE_DECLARATION_UINT16
#define CAN_EXTENDED_FORMAT (Can_IdType)0x8000U
#define CAN_FD_FRAME_FORMAT (Can_IdType)0x4000U
#define CAN_ID_TYPE_IDMASK  (Can_IdType)0x07FFU
#else
#define CAN_EXTENDED_FORMAT (Can_IdType)0x80000000UL
#define CAN_FD_FRAME_FORMAT (Can_IdType)0x40000000UL
#define CAN_ID_TYPE_IDMASK  (Can_IdType)0x1FFFFFFFUL
#define CAN_ID_STANDARDTYPE_IDMASK  (Can_IdType)0x7FFUL
#define CANXL_PRIORITY_IDMASK       (Can_IdType)0x7FFUL
#endif

/* Maximum payload length for standard(non-FD) CAN */
#define CAN_FD_FRAME_OFFSET       30U   

/* Maximum payload length for standard(non-FD) CAN */
#define CAN_FD_BASEID_OFFSET      18U   

/* Maximum payload length for standard(non-FD) CAN */
#define CAN_STD_MAX_PAYLOAD       8U          

/* Maximum payload length for CAN-FD */
#define CAN_CANFD_MAX_PAYLOAD     64U

/* Maximum retry count for reading receive buffer
   This is just for guarantee to avoid infinite loop.
   Actually, since reading speed is enough fast than message arival interval,
   reading loop will finish within two times. */
#define CAN_RECBUFFER_RETRY_COUNT 10UL        

/* TX/RX message lost flag */
#define CAN_FIFO_MSG_LOST_MASK    (uint32)0x00000004UL

#define CAN_ONE                   1UL         
#define CAN_TWO                   2UL         
#define CAN_THREE                 3UL         

#define CAN_RX_FIFO_TYPE                   0UL
#define CAN_RX_COMFIFO_TYPE                1UL
/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/
#define CAN_START_SEC_CONST_8
#include "Can_MemMap.h"

#if (CAN_RSCANFD_CONFIGURED == STD_ON) || (CAN_CANXL_SUPPORTED == STD_ON)
/* The LUT to acquire DLC register value from payload size */
extern CONST(uint8, CAN_CONST) Can_GaaDLCFromPayloadTable[65];
/* The LUT to acquire payload size from DLC register value */
extern CONST(uint8, CAN_CONST) Can_GaaPayloadFromDLCTable[16];
#endif

#define CAN_STOP_SEC_CONST_8
#include "Can_MemMap.h"

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/
#define CAN_START_SEC_PRIVATE_CODE
#include "Can_MemMap.h"
#if ((CAN_TX_BUFFER == STD_ON) || (CAN_TX_COMFIFO == STD_ON) || (CAN_TX_QUEUE == STD_ON))
extern FUNC(void, CAN_PRIVATE_CODE) Can_TxConfirmationProcessing(CONST(uint8, AUTOMATIC) LucCtrlIndex);
#endif
#if (CAN_RX_FIFO == STD_ON)
extern FUNC(void, CAN_PRIVATE_CODE)
    Can_RxProcessingRxFIFO(CONST(uint32, AUTOMATIC) LulBufferBits, CONST(uint32, AUTOMATIC) LulMode,
                           CONST(uint32, AUTOMATIC) LulIndex);
#endif
#if (CAN_RX_COMFIFO == STD_ON)
extern FUNC(void, CAN_PRIVATE_CODE)
    Can_RxProcessingTxRxFIFO(CONST(uint32, AUTOMATIC) LulBufferBits, CONST(uint32, AUTOMATIC) LulMode,
                             CONST(uint32, AUTOMATIC) LulIndex);
#endif
#if (CAN_RX_BUFFER == STD_ON) 
extern FUNC(void, CAN_PRIVATE_CODE) Can_RxProcessingBuffer(
                                               CONST(uint32, AUTOMATIC) LulIndex, VAR(uint8, AUTOMATIC) LucCtrlIndex);
#endif

#if (CAN_CANXL_SUPPORTED == STD_ON)
extern FUNC(void, CAN_PRIVATE_CODE) Can_CanXLTxConfirmation(CONST(uint8, AUTOMATIC) LucCtrlIndex);
extern FUNC(void, CAN_PRIVATE_CODE) CanXL_RxProcessing(const uint8 LucController, const uint32 LulMode, 
                                                                                const uint32 LulIndex);
#endif

#define CAN_STOP_SEC_PRIVATE_CODE
#include "Can_MemMap.h"
#endif /* CAN_MAINSERV_H */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
