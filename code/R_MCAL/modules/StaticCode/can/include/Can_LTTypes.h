/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Can_LTTypes.h                                                                                       */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2019-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Provision of AUTOSAR CAN Link time parameters.                                                                     */
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
/*                                                                                                                    */
/*====================================================================================================================*/

/***********************************************************************************************************************
**                                                  Revision History                                                  **
***********************************************************************************************************************/
/*
 * 2.4.1: 30/06/2025  : Remove the SW-VERSION from header of file
 * 2.4.0: 30/05/2025  : Update SW-VERSION for RH850/Ver22.01.00 (D) U2Ax Release
 *                      Fixing QAC message
 * 2.3.1: 31/03/2025  : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 *                    : Add message 4641 to support QA-C version 11.6.0
 * 2.3.0: 28/02/2025  : Update SW-VERSION for RH850/Ver22.01.00/Ver22.01.00.D Final Release
 * 2.2.0: 31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 * 2.1.2: 31/10/2024  : As part of CANXL driver support, following changes are made:
 *                      1. Fixing QAC message
 *                      2. Update condition for Registers structure Can_GaaRegs
 * 2.1.1: 30/08/2024  : As part of CANXL driver support, following changes are made:
 *                      1. Remove condition check macro of Can_ControllerType
 *                      2. Change CONFIG_DATA_8 to CONFIG_DATA_PREBUILD_8
 *                      3. Add condition check macro of Global interrupt
 *                      4. Remove ucCoreId in Can_ControllerPCConfigType struct
 *                      5. Update struct Can_IntselRegisterSetType
 *                      6. Add message header 3432
 *                      7. Remove CAN_NO_ERROR
 *                      8. Remove message 1534, 1536
 *                      9. Change from Can_Mapping.h to Can_MemMap.h
 *                      10. Change CONFIG_DATA_UNSPECIFIED to CONFIG_DATA_PREBUILD_UNSPECIFIED
 *                      11. Add Can_ControllerType to support CANXL and CANFD
 *                      12. Add Can_ControllerType into Can_ControllerPCConfigType
 *                      13. Add Data types for CAN XL Specific CanXL_RegisterSetType
 *                      14. Add struct STag_Can_IntselRegisterSetType and update strcut STag_Can_ControllerPCConfigType
 *                      to suppport Ored interrupt function for U2Cx version 0.40
 * 2.0.1: 06/11/2023  : Add QAC message 1534, add macro CAN_NO_ERROR
 *        19/10/2023  : Add message 1534, 1536
 *        14/10/2023  : Change CONFIG_DATA_UNSPECIFIED to CONFIG_DATA_PREBUILD_UNSPECIFIED
 * 2.0.0: 02/08/2023  : Remove multi instance and change from Can_Mapping.h to Can_MemMap.h
 *                      Add ucCoreId to support multi core
 *                      Remove redundant QAC message
 *                      Add CWE Rule 
 *        28/04/2023  : Define new macro CAN_CHECK_INT_ERROR
 * 1.4.3: 11/05/2022  : Change Common_ControllerStateType to Can_CommonControllerStateType.
 *                    : Remove un-use macro CAN_BYTE_BITS
 *        12/04/2022  : Change EcuM_WakeupSourceType to uint8, ulWakeupSourceId to ucWakeupSourceId
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
 * 1.1.1: 01/07/2020  : Update to add macro CAN_CHECK_MIXED_RX
 * 1.1.0: 19/06/2020  : Release.
 * 1.0.1: 20/01/2020  : Change Can_ControllerStateType to
 *                      Can_ControllerStateWrapperType complying with AUTOSAR
 *                      version 4.3.1
 * 1.0.0: 09/12/2019  : Initial version.
 */
/**********************************************************************************************************************/

#ifndef CAN_LTTYPES_HEADER
#define CAN_LTTYPES_HEADER

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
#if (CAN_WAKEUP_SUPPORT == STD_ON)
#include "EcuM_Cbk.h"
#endif

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:3684)    : Array declared with unknown size.                                                            */
/* Rule                : CERTCCM ARR02, MISRA C:2012 Rule-8.11                                                        */
/* JV-01 Justification : Arrays used are verified in the file which are only declarations and size is configuration   */
/*                       dependent.                                                                                   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:4641)    : The identifier '%1s' could conflict in the future with the name of a macro in '<%2s>'.       */
/* Rule                : CWE 3.6.0 CWE-398, CWE-569, CERTC 3.6.0 DCL37                                                */
/* JV-01 Justification : This Etag naming rule is following internal requirement. It is accepted.                     */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/


/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define CAN_LTTYPES_AR_RELEASE_MAJOR_VERSION    CAN_AR_RELEASE_MAJOR_VERSION
#define CAN_LTTYPES_AR_RELEASE_MINOR_VERSION    CAN_AR_RELEASE_MINOR_VERSION
#define CAN_LTTYPES_AR_RELEASE_REVISION_VERSION CAN_AR_RELEASE_REVISION_VERSION

/* File version information */
#define CAN_LTTYPES_SW_MAJOR_VERSION            CAN_SW_MAJOR_VERSION
#define CAN_LTTYPES_SW_MINOR_VERSION            CAN_SW_MINOR_VERSION

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/
/* Flag not set */
#define CAN_FALSE                               (boolean)0
/* Flag set */
#define CAN_TRUE                                (boolean)1
/* The value indicates invalid index */
#define CAN_INVALID_INDEX                       (uint32)0xFFFFFFFFUL
/* Interupt mode or polling mode */
#define CAN_INT_DISABLED                        0x00U
#define CAN_CHECK_INT_TX                        0x01U
#define CAN_CHECK_INT_RX                        0x02U
#define CAN_CHECK_MIXED_RX                      0x10U
#define CAN_CHECK_INT_BUSOFF                    0x04U
#define CAN_CHECK_INT_WAKEUP                    0x08U
/* Can Bus Error Flag */
#define CAN_CHECK_INT_ERROR                     0x20U
/* Macro for controller with no wake up source enabled */
#define CAN_NOWAKEUP                            (uint8)0xFFU

/* Start address of database  */
#define CAN_DBTOC_VALUE\
  (((uint32)CAN_VENDOR_ID_VALUE << 22U) | ((uint32)CAN_MODULE_ID_VALUE << 14U) | \
   ((uint32)CAN_SW_MAJOR_VERSION_VALUE << 8U) | ((uint32)CAN_SW_MINOR_VERSION_VALUE << 3U))

/* The value after reset CAN channel status register */
#define CAN_T_UNINIT (uint32)0x00000005UL
/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/

/* Hardware Macro */
typedef enum ETag_Can_MacroType                                                                                         /* PRQA S 4641 # JV-01 */
{
  /* This hardware unit is RSCAN */
  CAN_MACRO_RSCAN,
  /* This hardware unit is RSCANFD */
  CAN_MACRO_RSCANFD
} Can_MacroType;

/* Can Controller Type*/
typedef enum ETag_Can_ControllerType                                                                                    /* PRQA S 4641 # JV-01 */
{
  /* This hardware unit is RSCANFD */
  CAN_FD,
  /* This hardware unit is CANXL */
  CAN_XL
} Can_ControllerType;

/* Sub-state during mode transition */
typedef enum ETag_Can_SubStatusType                                                                                     /* PRQA S 4641 # JV-01 */
{
  /* No Pending transitions in mode */
  CAN_NO_PENDING_TRANSITION,

  /* Tentative state for the exclusive control b/w HW trigger and SW trigger */
  CAN_TENTATIVE_TRANSITION,

  /* Pending start mode to wait CHANNEL_RESET after bus-off */
  CAN_PENDING_START_WAIT_RESET,
  /* Pending start mode to wait for CHANNEL_COMMUNICATION */
  CAN_PENDING_START_WAIT_COM,

  /* Pending stop mode to wait for CHANEL_HALT before enter CHANNEL_RESET */
  CAN_PENDING_STOP_WAIT_HALT,
  /* Pending reset mode to wait for CHANNEL_RESET */
  CAN_PENDING_STOP_WAIT_RESET,

  /* Pending sleep mode to wait for CAHNNEL_STOP */
  CAN_PENDING_SLEEP_WAIT_STOP,
  /* Pending sleep mode to wait for GLOBAL_RESET when this is last Channel */
  CAN_PENDING_SLEEP_WAIT_GLOBALRESET,
  /* Pending sleep mode to wait for GLOBAL_STOP when this is last Channel */
  CAN_PENDING_SLEEP_WAIT_GLOBALSTOP,

  /* Wake-up is requested by ISR but not started yet */
  CAN_PENDING_WAKEUP_REQUESTED,
  /* Pending wakeup to wait for previous Global state transition */
  CAN_PENDING_WAKEUP_WAIT_GLOBALCHANGE,
  /* Pending wakeup to wait for GLOBAL_RESET after wakeup from deep sleep */
  CAN_PENDING_WAKEUP_WAIT_GLOBALRESET,
  /* Pending wakeup to wait for GLOBAL_OPERATION after wakeup from deep sleep */
  CAN_PENDING_WAKEUP_WAIT_GLOBALOP,
  /* Pending wakeup to wait for CHANNEL_RESET */
  CAN_PENDING_WAKEUP_WAIT_RESET,
  
  CANXL_START_WAIT_RXQUEUE_START,
  
  CANXL_START_WAIT_PRT_START,
  
  CANXL_START_WAIT_BUSOFF_RECOVERY,
  
  CANXL_STOP_WAIT_PRT_STOP,
  
  CANXL_STOP_WAIT_TXRXQUEUE_STOP,
  
  CANXL_STOP_WAIT_MH_STOP
} Can_SubStatusType;

/* Register base address information for each unit */
typedef struct STag_Can_RegisterSetType
{
  /* RS-CAN or RS-CANFD */
  Can_MacroType enMacroType;
  /* Pointer to register map that is common between RS-CAN and RS-CANFD */
  P2VAR(volatile Can_CommonRegType, TYPEDEF, REGSPACE) pCmn;
  /* Pointer to Receive Rule registers */
  P2VAR(volatile Can_RRuleRegType, TYPEDEF, REGSPACE) pRR;
  #if (CAN_RSCANFD_CONFIGURED == STD_ON)
  /* Pointer to registers that is specified to RS-CANFD */
  P2VAR(volatile Can_FDRegType, TYPEDEF, REGSPACE) pFD;
  #endif
  #if ((CAN_RSCAN0_RXFIFO_INTERRUPT == STD_ON) || (CAN_RSCAN1_RXFIFO_INTERRUPT == STD_ON) || \
       (CAN_RSCAN2_RXFIFO_INTERRUPT == STD_ON))
  /* EIC register address for RxFIFO interruption */
  P2VAR(volatile uint16, TYPEDEF, REGSPACE) pICRxFIFO;
  #endif
  #if (CAN_WAKE_UP_FACTOR_CLEAR_ISR == STD_ON)
  /* Wake-up factor register address */
  P2VAR(volatile uint32, TYPEDEF, REGSPACE) pWUF0Reg;
  /* Wake-up factor clear register address */
  P2VAR(volatile uint32, TYPEDEF, REGSPACE) pWUFC0Reg;
  #endif
} Can_RegisterSetType;

/* CAN Controller Pre-compile Structure */
typedef struct STag_Can_ControllerPCConfigType
{
  #if (CAN_CANXL_SUPPORTED == STD_ON)
  /* Type of Can Controller */
  Can_ControllerType enControllerType;
  #endif
  /* Whether this Controller is used */
  VAR(boolean, CAN_CONFIG_DATA) blActivation;
  /* Index of Can_GaaRegs which this controller allocated to */
  VAR(uint8, CAN_CONFIG_DATA) ucUnit;
  /* Index of physical Channel which this controller allocated to */
  VAR(uint8, CAN_CONFIG_DATA) ucCh;
  /* Polling/Interrupt for each operation */
  VAR(uint8, CAN_CONFIG_DATA) ucIntEnable;
  /* Value of CmCTR, including error interrupt enable bits (bit 8-16) */
  VAR(uint32, CAN_CONFIG_DATA) ulCTR;
  /* Value of THLCCm except THLE bit */
  VAR(uint32, CAN_CONFIG_DATA) ulTHLCC;
  #if (CAN_WAKEUP_SUPPORT == STD_ON)
  /* wakeup source ID to indicate upper layer */
  VAR(uint8, CAN_CONFIG_DATA) ucWakeupSourceId;
  #endif
  #if (CAN_ORED_INTERRUPT_FUNCTION == STD_OFF)
  /* EIC reigster address for Rx interruption */
  P2VAR(volatile uint16, TYPEDEF, REGSPACE) pICRec;
  /* EIC register address for Tx interruption */
  P2VAR(volatile uint16, TYPEDEF, REGSPACE) pICTx;
  /* EIC register address for BusError interruption */
  P2VAR(volatile uint16, TYPEDEF, REGSPACE) pICErr;
  #else
  /* value of interrupt selection index*/
  VAR(uint8, CAN_CONFIG_DATA) ucInterruptSel;
  #endif
  #if (CAN_WAKEUP_SUPPORT == STD_ON)
  /* EIC register address for Wakeup interruption */
  P2VAR(volatile uint16, TYPEDEF, REGSPACE) pICWakeup;
  #ifdef CAN_FILTER_CONTROL_SUPPORT
  /* FCLA register address for setting edge detection */
  P2VAR(volatile uint8, TYPEDEF, REGSPACE) pFCLAReg;
  #endif
  #endif
  #if (CAN_WAKE_UP_FACTOR_CLEAR_ISR == STD_ON)
  /* Mask for Wakeup factor clear register */
  VAR(uint32, CAN_CONFIG_DATA) ulWUFMask;
  #endif
} Can_ControllerPCConfigType;

/* This structure includes statuses for each Controller */
typedef struct STag_Can_ControllerStateWrapperType
{
  /* Current Controller mode */
  VAR(Can_CommonControllerStateType, TYPEDEF) enMode;
  /* Sub-state during Controller is in mode transition */
  VAR(Can_SubStatusType, TYPEDEF) enSubState;
  /* Whether Controller is in bus-off state of not */
  VAR(boolean, TYPEDEF) blBusOff;
  #if (CAN_WAKEUP_SUPPORT == STD_ON)
  /* Whether wakeup event occurred */
  VAR(boolean, TYPEDEF) blWakeupEventOccurred;
  /* Whether wakeup is triggered by HW or SW */
  VAR(boolean, TYPEDEF) blWakeupByHW;
  #endif
  /* Index of current baudrate */
  VAR(uint32, TYPEDEF) ulBaudrateIndex;
  /* Recursive count of Can_DisableControllerInterrupts */
  VAR(uint32, TYPEDEF) ulIntCount;
} Can_ControllerStateWrapperType;

#if (CAN_ORED_INTERRUPT_FUNCTION == STD_ON)
/* INTSEL/EIC register base address information for each interrupt */
typedef struct STag_Can_IntselRegisterSetType
{

  /* EIC reigster address for Rx interruption */
  P2VAR(volatile uint16, TYPEDEF, REGSPACE) pICRec;
  /* EIC register address for Tx interruption */
  P2VAR(volatile uint16, TYPEDEF, REGSPACE) pICTx;
  /* EIC register address for BusError interruption */
  P2VAR(volatile uint16, TYPEDEF, REGSPACE) pICErr;
  /* INTSEL reigster address for Busoff interruption monitor */
  P2VAR(volatile uint32, TYPEDEF, REGSPACE) pERMON;
  /* INTSEL reigster address for Rx interruption monitor */
  P2VAR(volatile uint32, TYPEDEF, REGSPACE) pRCMON;
  /* INTSEL reigster address for Tx interruption monitor */
  P2VAR(volatile uint32, TYPEDEF, REGSPACE) pTRMON;
  /* INTSEL reigster address for Busoff interruption mask */
  P2VAR(volatile uint32, TYPEDEF, REGSPACE) pERMSK;
  /* INTSEL reigster address for Rx interruption mask */
  P2VAR(volatile uint32, TYPEDEF, REGSPACE) pRCMSK;
  /* INTSEL reigster address for Tx interruption mask */
  P2VAR(volatile uint32, TYPEDEF, REGSPACE) pTRMSK;
} Can_IntselRegisterSetType;
#endif

/*---------------------------------------------------------------------------------------------------------------------
 * CAN XL Specific
 ---------------------------------------------------------------------------------------------------------------------*/
#if (CAN_CANXL_SUPPORTED == STD_ON)
 /* Register base address information for each unit */
typedef struct STag_CanXL_RegisterSetType
{
  /* Pointer to register map that is used for Message Handler     */
  P2VAR(volatile CanXL_MHRegType, TYPEDEF, REGSPACE) pMH;
  /* Pointer to register map that is used for Protocol Controller */
  P2VAR(volatile CanXL_PRTRegType, TYPEDEF, REGSPACE) pPRT;
  /* Pointer to registers that is used for Interrupt Controller   */
  P2VAR(volatile CanXL_IRCRegType, TYPEDEF, REGSPACE) pIRC;
  /* Pointer to registers that is used for Global CANXL register   */
  P2VAR(volatile CanXL_GLBRegType, TYPEDEF, REGSPACE) pGLB;
} CanXL_RegisterSetType;

#endif /* #if (CAN_CANXL_SUPPORTED == STD_ON) */

/***********************************************************************************************************************
**                                        Extern declarations for Global Data                                         **
***********************************************************************************************************************/
#define CAN_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "Can_MemMap.h"

#if (CAN_RSCANFD_CONFIGURED == STD_ON)
/* Registers structure of RSCAN module */
extern CONST(Can_RegisterSetType, CAN_CONST) Can_GaaRegs[];                                                             /* PRQA S 3684 # JV-01 */
#endif

#if (CAN_ORED_INTERRUPT_FUNCTION == STD_ON)
extern CONST(Can_IntselRegisterSetType, CAN_CONST) Can_IntselGaaRegs[];                                                 /* PRQA S 3684 # JV-01 */
#endif

extern CONST(Can_ControllerPCConfigType, CAN_CONST) Can_GaaControllerPCConfig0[];                                       /* PRQA S 3684 # JV-01 */

#define CAN_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "Can_MemMap.h"

#define CAN_START_SEC_CONFIG_DATA_PREBUILD_8
#include "Can_MemMap.h"

extern CONST(uint8, CAN_CONFIG_DATA) Can_GaaPhysicalControllerToIndex0[];                                               /* PRQA S 3684 # JV-01 */
extern CONST(uint8, CAN_CONFIG_DATA) CanXL_GaaPhysicalControllerToIndex0[];                                             /* PRQA S 3684 # JV-01 */
extern CONST(uint8, CAN_CONFIG_DATA) CanXL_GaaSecondPhysicalControllerToIndex0[];                                       /* PRQA S 3684 # JV-01 */

#define CAN_STOP_SEC_CONFIG_DATA_PREBUILD_8
#include "Can_MemMap.h"

/*---------------------------------------------------------------------------------------------------------------------
 * CAN XL Specific
 ---------------------------------------------------------------------------------------------------------------------*/
#if (CAN_CANXL_SUPPORTED == STD_ON)
#define CAN_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "Can_MemMap.h"
/* Registers structure of XCAN module */
extern CONST(CanXL_RegisterSetType, CAN_CONST) CanXL_GaaRegs[CAN_CANXL_NO_OF_CONTROLLER];
#define CAN_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "Can_MemMap.h"
#endif 

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/
#endif /* CAN_LTTYPES_HEADER */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
