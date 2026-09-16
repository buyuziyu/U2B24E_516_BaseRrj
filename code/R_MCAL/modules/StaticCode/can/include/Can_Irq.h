/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Can_Irq.h                                                                                           */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2019-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Provision of declaration of ISR.                                                                                   */
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
 * 2.3.0: 28/02/2025  : Update SW-VERSION for RH850/Ver22.01.00/Ver22.01.00.D Final Release
 * 2.2.0: 31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 * 2.1.2: 31/10/2024  : Update SW-VERSION for Ver22.01.02 to 2.1.2
 * 2.1.1: 30/08/2024  : As part of CANXL driver support, following changes are made:
 *                      1. Add prototype of CANXL_CONTROLLER0_ERR_ISR, CANXL_CONTROLLER1_ERR_ISR
 *                      CANXL_CONTROLLER0_WAKEUP_ISR, CANXL_CONTROLLER1_WAKEUP_ISR
 *                      2. Add macro CAN_PHYIDX_CONTROLLER16 to CAN_PHYIDX_CONTROLLER19
 *                      3. Define function to support controller 16 to controller 19 for U2Bx-E 
 *                      4. Update macro name of Ored Interrupt function to support U2Cx version 0.50
 *                      5. Remove message 1534
 *                      6. Add new function CanXL_RxIsr, CANXL_CONTROLLER0_RX_ISR, CANXL_CONTROLLER1_RX_ISR
 *                      7. Add macro CAN_PHYIDX_INTERRUPT_SELECTION0, CAN_PHYIDX_INTERRUPT_SELECTION1,
 *                      CAN_PHYIDX_INTERRUPT_SELECTION2, CAN_PHYIDX_INTERRUPT_SELECTION3 and update function prototypes
 *                      to suppport Ored interrupt function for U2Cx version 0.40
 *                      8. Add macro in Global Symbol and Function Prototypes to support ISR for U2Cx 
 * 2.0.1: 06/11/2023  : Remove redundant QAC message
 *        19/10/2023  : Add message 1534
 * 2.0.0: 02/08/2023  : Remove multi instance and change from Can_Mapping.h to Can_MemMap.h
 *                      Remove redundant QAC message
 *                      Add CWE Rule 
 *        28/04/2023  : Update name of CAN_CONTROLLERm_BUSOFF_ISR to CAN_CONTROLLERm_ERROR_ISR
 * 1.3.2: 30/08/2021  : Update to support multi-instance:
 *                      - Add precondition check CAN_INSTANCE_INDEX
 *                      - Change include to Can_Mapping.h
 * 1.3.1: 08/07/2021  : Removed CAN_PHYIDX_UNIT0, CAN_PHYIDX_UNIT1
 *        02/07/2021  : Add QAC message 9.5.0
 *                      Format source code to 120 characters
 *                      Improve Violation tag (remove START/END)
 *        05/05/2021  : Update the memory section, memclass, ptrclass to change
 *                      the CAN_RSCAN prefix to CAN
 * 1.2.0: 09/07/2020  : Release.
 *        28/07/2020  : Add QAC 9.3.1 comment.
 * 1.1.0: 19/06/2020  : Release.
 * 1.0.1: 27/03/2020  : Update macro CAN_EIC_EIMK_MASK from uint16 to uint8.
 * 1.0.0: 09/12/2019  : Initial version
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/

/**********************************************************************************************************************/

#ifndef CAN_IRQ_HEADER
#define CAN_IRQ_HEADER


/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for interrupt category definitions */
#include "Os.h"

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define CAN_IRQ_AR_RELEASE_MAJOR_VERSION    CAN_AR_RELEASE_MAJOR_VERSION
#define CAN_IRQ_AR_RELEASE_MINOR_VERSION    CAN_AR_RELEASE_MINOR_VERSION
#define CAN_IRQ_AR_RELEASE_REVISION_VERSION CAN_AR_RELEASE_REVISION_VERSION

/* File version information */
#define CAN_IRQ_SW_MAJOR_VERSION            CAN_SW_MAJOR_VERSION
#define CAN_IRQ_SW_MINOR_VERSION            CAN_SW_MINOR_VERSION

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/
/* EICn */
#define CAN_EIC_EIRF_MASK                   (uint16)0x1000U
#define CAN_EIC_EIMK_MASK                   (uint8)0x80U

/* Controller physical index */
#define CAN_PHYIDX_CONTROLLER0              0U
#define CAN_PHYIDX_CONTROLLER1              1U
#define CAN_PHYIDX_CONTROLLER2              2U
#define CAN_PHYIDX_CONTROLLER3              3U
#define CAN_PHYIDX_CONTROLLER4              4U
#define CAN_PHYIDX_CONTROLLER5              5U
#define CAN_PHYIDX_CONTROLLER6              6U
#define CAN_PHYIDX_CONTROLLER7              7U
#define CAN_PHYIDX_CONTROLLER8              8U
#define CAN_PHYIDX_CONTROLLER9              9U
#define CAN_PHYIDX_CONTROLLER10             10U
#define CAN_PHYIDX_CONTROLLER11             11U
#define CAN_PHYIDX_CONTROLLER12             12U
#define CAN_PHYIDX_CONTROLLER13             13U
#define CAN_PHYIDX_CONTROLLER14             14U
#define CAN_PHYIDX_CONTROLLER15             15U
#define CAN_PHYIDX_CONTROLLER16             16U
#define CAN_PHYIDX_CONTROLLER17             17U
#define CAN_PHYIDX_CONTROLLER18             18U
#define CAN_PHYIDX_CONTROLLER19             19U
#define CAN_PHYIDX_INTERRUPT_SELECTION0     0U
#define CAN_PHYIDX_INTERRUPT_SELECTION1     1U
#define CAN_PHYIDX_INTERRUPT_SELECTION2     2U
#define CAN_PHYIDX_INTERRUPT_SELECTION3     3U

#define CANXL_PHYIDX_CONTROLLER0            0U
#define CANXL_PHYIDX_CONTROLLER1            1U

#define CANXL_PRT_TXEVT_BIT                 (uint32)(1UL << 26UL)
#define CANXL_PRT_RXEVT_BIT                 (uint32)(1UL << 27UL)
#define CANXL_FQ_ISR_BIT                    (uint32)0xFFUL

#if (CAN_CANXL_SUPPORTED == STD_ON)
#if ((CAN_CANXL_CONTROLLER0_RX_INTERRUPT == STD_ON) || (CAN_CANXL_CONTROLLER1_RX_INTERRUPT == STD_ON))
#define CANXL_CONTROLLER_RX_INTERRUPT_ON
#endif

#if ((CAN_CANXL_CONTROLLER0_TX_INTERRUPT == STD_ON) || (CAN_CANXL_CONTROLLER1_TX_INTERRUPT == STD_ON))
#define CANXL_CONTROLLER_TX_INTERRUPT_ON
#endif
#endif

/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/

/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/
#define CAN_START_SEC_CODE_FAST
#include "Can_MemMap.h"

#if (CAN_CANXL_SUPPORTED == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CANXL_CONTROLLER0_FUNC_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for Transmit Receive FIFO handler of controller 14 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CANXL_CONTROLLER0_FUNC_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CANXL_CONTROLLER1_FUNC_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for Transmit Receive FIFO handler of controller 15 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CANXL_CONTROLLER1_FUNC_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CANXL_CONTROLLER0_ERR_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for Transmit Receive FIFO handler of controller 14 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CANXL_CONTROLLER0_ERR_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CANXL_CONTROLLER1_ERR_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for Transmit Receive FIFO handler of controller 15 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CANXL_CONTROLLER1_ERR_ISR(void);
#endif

#endif

#if defined(Os_CAN_RSCAN0_RXFIFO_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for global Receive FIFO handler of HW Unit 0*/
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_RSCAN0_RXFIFO_ISR(void);
#endif

#if defined(Os_CAN_RSCAN1_RXFIFO_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for global Receive FIFO handler of HW Unit 1*/
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_RSCAN1_RXFIFO_ISR(void);
#endif

#if defined(Os_CAN_RSCAN2_RXFIFO_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for global Receive FIFO handler of HW Unit 2*/
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_RSCAN2_RXFIFO_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER0_RX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for Transmit Receive FIFO handler of controller 0 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER0_RX_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER1_RX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for Transmit Receive FIFO handler of controller 1 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER1_RX_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER2_RX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for Transmit Receive FIFO handler of controller 2 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER2_RX_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER3_RX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for Transmit Receive FIFO handler of controller 3 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER3_RX_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER4_RX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for Transmit Receive FIFO handler of controller 4 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER4_RX_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER5_RX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for Transmit Receive FIFO handler of controller 5 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER5_RX_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER6_RX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for Transmit Receive FIFO handler of controller 6 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER6_RX_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER7_RX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for Transmit Receive FIFO handler of controller 7 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER7_RX_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER8_RX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for Transmit Receive FIFO handler of controller 8 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER8_RX_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER9_RX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for Transmit Receive FIFO handler of controller 9 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER9_RX_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER10_RX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for Transmit Receive FIFO handler of controller 10 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER10_RX_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER11_RX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for Transmit Receive FIFO handler of controller 11 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER11_RX_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER12_RX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for Transmit Receive FIFO handler of controller 12 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER12_RX_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER13_RX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for Transmit Receive FIFO handler of controller 13 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER13_RX_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER14_RX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for Transmit Receive FIFO handler of controller 14 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER14_RX_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER15_RX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for Transmit Receive FIFO handler of controller 15 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER15_RX_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER16_RX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for Transmit Receive FIFO handler of controller 16 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER16_RX_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER17_RX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for Transmit Receive FIFO handler of controller 17 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER17_RX_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER18_RX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for Transmit Receive FIFO handler of controller 18 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER18_RX_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER19_RX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for Transmit Receive FIFO handler of controller 19 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER19_RX_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER0_TX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for Transmit handler of controller 0 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER0_TX_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER1_TX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for Transmit handler of controller 1 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER1_TX_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER2_TX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for Transmit handler of controller 2 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER2_TX_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER3_TX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for Transmit handler of controller 3 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER3_TX_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER4_TX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for Transmit handler of controller 4 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER4_TX_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER5_TX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for Transmit handler of controller 5 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER5_TX_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER6_TX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for Transmit handler of controller 6 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER6_TX_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER7_TX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for Transmit handler of controller 7 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER7_TX_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER8_TX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for Transmit handler of controller 8 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER8_TX_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER9_TX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for Transmit handler of controller 9 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER9_TX_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER10_TX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for Transmit handler of controller 10 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER10_TX_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER11_TX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for Transmit handler of controller 11 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER11_TX_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER12_TX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for Transmit handler of controller 12 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER12_TX_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER13_TX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for Transmit handler of controller 13 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER13_TX_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER14_TX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for Transmit handler of controller 14 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER14_TX_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER15_TX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for Transmit handler of controller 15 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER15_TX_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER16_TX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for Transmit handler of controller 16 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER16_TX_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER17_TX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for Transmit handler of controller 17 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER17_TX_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER18_TX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for Transmit handler of controller 18 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER18_TX_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER19_TX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for Transmit handler of controller 19 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER19_TX_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER0_ERROR_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for BusOff handler of controller 0 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER0_ERROR_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER1_ERROR_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for BusOff handler of controller 1 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER1_ERROR_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER2_ERROR_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for BusOff handler of controller 2 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER2_ERROR_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER3_ERROR_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for BusOff handler of controller 3 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER3_ERROR_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER4_ERROR_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for BusOff handler of controller 4 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER4_ERROR_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER5_ERROR_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for BusOff handler of controller 5 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER5_ERROR_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER6_ERROR_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for BusOff handler of controller 6 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER6_ERROR_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER7_ERROR_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for BusOff handler of controller 7 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER7_ERROR_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER8_ERROR_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for BusOff handler of controller 8 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER8_ERROR_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER9_ERROR_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for BusOff handler of controller 9 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER9_ERROR_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER10_ERROR_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for BusOff handler of controller 10 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER10_ERROR_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER11_ERROR_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for BusOff handler of controller 11 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER11_ERROR_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER12_ERROR_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for BusOff handler of controller 12 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER12_ERROR_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER13_ERROR_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for BusOff handler of controller 13 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER13_ERROR_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER14_ERROR_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for BusOff handler of controller 14 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER14_ERROR_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER15_ERROR_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for BusOff handler of controller 15 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER15_ERROR_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER16_ERROR_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for BusOff handler of controller 16 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER16_ERROR_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER17_ERROR_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for BusOff handler of controller 17 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER17_ERROR_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER18_ERROR_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for BusOff handler of controller 18 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER18_ERROR_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER19_ERROR_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for BusOff handler of controller 19 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER19_ERROR_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER0_WAKEUP_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for Wakeup handler of controller 0 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER0_WAKEUP_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER1_WAKEUP_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for Wakeup handler of controller 1 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER1_WAKEUP_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER2_WAKEUP_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for Wakeup handler of controller 2 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER2_WAKEUP_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER3_WAKEUP_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for Wakeup handler of controller 3 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER3_WAKEUP_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER4_WAKEUP_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for Wakeup handler of controller 4 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER4_WAKEUP_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER5_WAKEUP_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for Wakeup handler of controller 5 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER5_WAKEUP_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER6_WAKEUP_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for Wakeup handler of controller 6 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER6_WAKEUP_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER7_WAKEUP_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for Wakeup handler of controller 7 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER7_WAKEUP_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER8_WAKEUP_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for Wakeup handler of controller 8 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER8_WAKEUP_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER9_WAKEUP_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for Wakeup handler of controller 9 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER9_WAKEUP_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER10_WAKEUP_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for Wakeup handler of controller 10 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER10_WAKEUP_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER11_WAKEUP_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for Wakeup handler of controller 11 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER11_WAKEUP_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER12_WAKEUP_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for Wakeup handler of controller 12 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER12_WAKEUP_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER13_WAKEUP_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for Wakeup handler of controller 13 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER13_WAKEUP_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER14_WAKEUP_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for Wakeup handler of controller 14 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER14_WAKEUP_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER15_WAKEUP_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for Wakeup handler of controller 15 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER15_WAKEUP_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER16_WAKEUP_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for Wakeup handler of controller 16 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER16_WAKEUP_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER17_WAKEUP_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for Wakeup handler of controller 17 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER17_WAKEUP_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER18_WAKEUP_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for Wakeup handler of controller 18 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER18_WAKEUP_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER19_WAKEUP_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for Wakeup handler of controller 19 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER19_WAKEUP_ISR(void);
#endif

#if (CAN_CANXL_SUPPORTED == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CANXL_CONTROLLER0_WAKEUP_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for Wakeup handler of controller 0 for CANXL */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CANXL_CONTROLLER0_WAKEUP_ISR(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CANXL_CONTROLLER1_WAKEUP_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* ISR for Wakeup handler of controller 1 for CANXL */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CANXL_CONTROLLER1_WAKEUP_ISR(void);
#endif
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER013_RX_CAT2_ISR0) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* Transmit Receive FIFO handler for ISR0 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER013_RX_ISR_0(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER013_RX_CAT2_ISR1) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* Transmit Receive FIFO handler for ISR1 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER013_RX_ISR_1(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER013_RX0_CAT2_ISR2) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* Transmit Receive FIFO handler for ISR2 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER013_RX_ISR_2(void);
#endif


/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER013_RX_CAT2_ISR3) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* Transmit Receive FIFO handler for ISR3 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER013_RX_ISR_3(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER013_TX_CAT2_ISR0) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* Transmit handler for ISR0 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER013_TX_ISR_0(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER013_TX_CAT2_ISR1) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* Transmit handler for ISR1 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER013_TX_ISR_1(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER013_TX_CAT2_ISR2) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* Transmit handler for ISR2 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER013_TX_ISR_2(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER013_TX_CAT2_ISR3) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* Transmit handler for ISR3 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER013_TX_ISR_3(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER013_ERROR_CAT2_ISR0) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* BusOff handler for ISR0 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER013_ERROR_ISR_0(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER013_ERROR_CAT2_ISR1) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* BusOff handler for ISR1 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER013_ERROR_ISR_1(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER013_ERROR_CAT2_ISR2) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* BusOff handler for ISR2 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER013_ERROR_ISR_2(void);
#endif

/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER013_ERROR_CAT2_ISR3) || (CAN_ISR_CATEGORY_2 == STD_ON)
/* Use ISR() macro from Os.h */
/* Defines the CAT1 interrupt mapping */
#else
/* BusOff handler for ISR3 */
extern _INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER013_ERROR_ISR_3(void);
#endif

#define CAN_STOP_SEC_CODE_FAST
#include "Can_MemMap.h"

#endif /* CAN_IRQ_HEADER */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
