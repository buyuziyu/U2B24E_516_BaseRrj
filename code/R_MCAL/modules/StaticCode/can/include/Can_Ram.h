/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Can_Ram.h                                                                                           */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2019-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* C header file for Can_Ram.c                                                                                        */
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
**                                              Revision Control History                                              **
***********************************************************************************************************************/
/*
 * 2.4.1: 30/06/2025  : Remove the SW-VERSION from header of file
 * 2.4.0: 30/05/2025  : Update SW-VERSION for RH850/Ver22.01.00 (D) U2Ax Release
 * 2.3.1: 31/03/2025  : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 * 2.3.0: 28/02/2025  : As part of ARDAACL-52460: Remove redundant variable CanXL_GaaFIFOQueuePosition
 * 2.2.0: 31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 *                      As part of CANXL driver support, following changes are made:
 *                      1. Update CanXL_ConsistentCheck.
 *                      2. Remove CanXL_GaaErrorSignaling, CanXL_GaaEmulationTEC, CanXL_GaaEmulationREC.
 *                      3. Add CanXL_TECEmulator, CanXL_WriteRxData.
 *                      update type of CanXL_RxQueueProcess
 * 2.1.2: 31/10/2024  : As part of CANXL driver support, following changes are made:
 *                      1. Add precompile condition for CanXL_GaaHwAccessFlag
 *                      2. Update condition to check CAN_NO_OF_UNITS
 *                      3. Add prototype of CanXL_ReleaseTxBuffer
 * 2.1.1: 30/08/2024  : As part of CANXL driver support, following changes are made:
 *                      1. Add prototype of CanXL_DeInitController
 *                      2. Add precondition to include CanXL.h
 *                      3. Add condition check macro of Global interrupt
 *                      4. Update type CanXL_GpHohConfig
 *                      5. Add CanXL_GaaErrorSignaling, CanXL_GaaEmulationTEC, CanXL_GaaEmulationREC,
 *                      CanXL_ConsistentCheck, CanXL_CheckBusyQueue
 *                      6. Add extern CanXL_TxConfirmationQueueProcess, CanXL_ComputeCRC Can_CanXLInit
 *                      7. Remove header message 0841
 *                      8. Add message header 3432
 *                      9. Change from Can_Mapping.h to Can_MemMap.h
 *                      10. Add global variables: CanXL_GaaTxBufferTotal, CanXL_GaaRamSize, CanXL_GaaTxAllocCnt, 
 *                      CanXL_GaaRxBufferIndex, CanXL_GaaRxFrame, CanXL_GaaTxBufferMgrTable, CanXL_GaaMemPoolBufferTable
 *                      CanXL_GpRamManager, CanXL_GaaMacFilterMng, CanXL_GaaCtrlStat.
 *                      11. Add new function CanXL_RxQueueProcess.
 *                      12. Add Global data types to sopport CANXL: CanXL_GpHohConfig, CanXL_GaaHwAccessFlag, 
 *                      CanXL_GaaSwPduHandle0, CanXL_GaaSwPduHandle1, CanXL_GaaSwPduHandle
 * 2.0.0: 02/08/2023  : Remove multi instance and change from Can_Mapping.h to Can_MemMap.h
 *                      Remove redundant QAC message
 *                      Add CWE Rule
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
 * 1.0.1: 06/02/2020  : Add new memory section for VAR_NO_INIT_PTR complying
 *                      with AUTOSAR version 4.3.1
 *        20/01/2020  : Change Can_ControllerStateType to
 *                      Can_ControllerStateWrapperType complying with AUTOSAR
 *                      version 4.3.1
 * 1.0.0: 09/12/2019  : Initial version.
 */
/**********************************************************************************************************************/

#ifndef CAN_RAM_HEADER
#define CAN_RAM_HEADER

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
#include "Can_LTTypes.h"
#include "Can_MainServ.h"
#include "Can_ModeCntrl.h"
#include "Can_PBTypes.h"

#if (CAN_CANXL_SUPPORTED == STD_ON)
#include "CanXL.h"
#endif

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define CAN_RAM_AR_RELEASE_MAJOR_VERSION    CAN_AR_RELEASE_MAJOR_VERSION
#define CAN_RAM_AR_RELEASE_MINOR_VERSION    CAN_AR_RELEASE_MINOR_VERSION
#define CAN_RAM_AR_RELEASE_REVISION_VERSION CAN_AR_RELEASE_REVISION_VERSION

/* Module Software version information */
#define CAN_RAM_SW_MAJOR_VERSION            CAN_SW_MAJOR_VERSION
#define CAN_RAM_SW_MINOR_VERSION            CAN_SW_MINOR_VERSION

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7                                                                       */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is accepted. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/
#define CAN_START_SEC_VAR_INIT_BOOLEAN
#include "Can_MemMap.h"

/* Global variable to store initialization status of CAN Driver */
extern volatile VAR(boolean, CAN_VAR_INIT) Can_GblInitialized;

#define CAN_STOP_SEC_VAR_INIT_BOOLEAN
#include "Can_MemMap.h"

#define CAN_START_SEC_VAR_NO_INIT_BOOLEAN
#include "Can_MemMap.h"

#if (CAN_WAKEUP_SUPPORT == STD_ON) && (CAN_RSCANFD_CONFIGURED == STD_ON)
/* Global state transition is on-going when sleep or wakeup */
extern volatile VAR(boolean, CAN_VAR_NO_INIT) Can_GaaGlobalStateTransition[CAN_NO_OF_UNITS];
#endif

#if ((CAN_TX_BUFFER == STD_ON) || (CAN_TX_COMFIFO == STD_ON) || (CAN_TX_QUEUE == STD_ON) || \
    (CANFD_ON_XL_BUS_SUPPORT == STD_ON))
/* Flags which indicates HOH is being accessed by a Can_Write */
extern volatile VAR(boolean, CAN_VAR_NO_INIT) Can_GaaHwAccessFlag[CAN_NO_OF_HOHS];
#endif

#define CAN_STOP_SEC_VAR_NO_INIT_BOOLEAN
#include "Can_MemMap.h"

#define CAN_START_SEC_VAR_NO_INIT_32
#include "Can_MemMap.h"

#if (CAN_WAKEUP_SUPPORT == STD_ON) && (CAN_RSCANFD_CONFIGURED == STD_ON)
/* Flags which indicates active (not slept) Controllers */
extern volatile VAR(uint32, CAN_VAR_NO_INIT) Can_GaaActiveControllers[CAN_NO_OF_UNITS];
#endif

#if ((CAN_RSCAN0_RXFIFO_INTERRUPT == STD_ON) || (CAN_RSCAN1_RXFIFO_INTERRUPT == STD_ON) || \
     (CAN_RSCAN2_RXFIFO_INTERRUPT == STD_ON))
/* Interrupt disable count for Global interruption */
extern volatile VAR(uint32, CAN_VAR_NO_INIT) Can_GaaGlobalIntCount[CAN_NO_OF_UNITS];
#endif

#define CAN_STOP_SEC_VAR_NO_INIT_32
#include "Can_MemMap.h"

#define CAN_START_SEC_VAR_NO_INIT_PTR
#include "Can_MemMap.h"

/* Global variable to store pointer to Config structure */
extern P2CONST(Can_ConfigType, CAN_VAR_NO_INIT, CAN_CONFIG_DATA) volatile Can_GpConfig;
extern P2CONST(Can_ControllerPCConfigType, CAN_VAR_NO_INIT, CAN_CONFIG_DATA) volatile Can_GpPCController;
extern P2CONST(Can_ControllerPBConfigType, CAN_VAR_NO_INIT, CAN_CONFIG_DATA) volatile Can_GpPBController;
extern P2CONST(Can_HohConfigType, CAN_VAR_NO_INIT, CAN_CONFIG_DATA) volatile Can_GpHohConfig;

#define CAN_STOP_SEC_VAR_NO_INIT_PTR
#include "Can_MemMap.h"

#define CAN_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Can_MemMap.h"

/* Global variable to controller status */
extern volatile VAR(Can_ControllerStateWrapperType, CAN_VAR_NO_INIT) Can_GaaCtrlState[CAN_MAX_NUMBER_OF_CONTROLLER];

#define CAN_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Can_MemMap.h"

/*---------------------------------------------------------------------------------------------------------------------
 * CAN XL Specific
 ---------------------------------------------------------------------------------------------------------------------*/
#if (CAN_CANXL_SUPPORTED == STD_ON)
#define CAN_START_SEC_VAR_NO_INIT_PTR
#include "Can_MemMap.h"
extern P2CONST(Can_HohConfigType, CAN_VAR_NO_INIT, CAN_CONFIG_DATA) volatile CanXL_GpHohConfig;
#define CAN_STOP_SEC_VAR_NO_INIT_PTR
#include "Can_MemMap.h"

#define CAN_START_SEC_VAR_NO_INIT_BOOLEAN
#include "Can_MemMap.h"
#if (CAN_CANXL_NO_OF_HOHS > CANXL_ZERO)
/* Flags which indicates HOH is being accessed by a CanXL_Write */
extern volatile VAR(boolean, CAN_VAR_NO_INIT) CanXL_GaaHwAccessFlag[CAN_CANXL_NO_OF_HOHS];
#endif
#define CAN_STOP_SEC_VAR_NO_INIT_BOOLEAN
#include "Can_MemMap.h"

#define CAN_START_SEC_VAR_NO_INIT_32
#include "Can_MemMap.h"
extern VAR(uint32, CAN_VAR_NO_INIT) CanXL_GaaTxBufferTotal[CANXL_MAX_CONTROLLER];
extern VAR(uint32, CAN_VAR_INIT) CanXL_GaaRamSize[CANXL_MAX_CONTROLLER];
extern VAR(uint32, CAN_VAR_NO_INIT) CanXL_GaaTxAllocCnt[CAN_CANXL_NO_OF_CONTROLLER][CANXL_MAX_TXQUEUE];
extern VAR(CanXL_RxFrameType, CAN_VAR_NO_INIT) CanXL_GaaRxFrame[CAN_CANXL_NO_OF_CONTROLLER];
#define CAN_STOP_SEC_VAR_NO_INIT_32
#include "Can_MemMap.h"

#define CAN_START_SEC_VAR_NO_INIT_PTR
#include "Can_MemMap.h"
extern P2VAR(CanXL_TxBufferType, AUTOMATIC, CAN_VAR_INIT) CanXL_GaaTxBufferMgrTable[CANXL_MAX_CONTROLLER];              /* PRQA S 3432 # JV-01 */
extern P2VAR(uint8, AUTOMATIC, CAN_VAR_INIT) CanXL_GaaMemPoolBufferTable[CANXL_MAX_CONTROLLER];                         /* PRQA S 3432 # JV-01 */
extern P2VAR(CanXL_MemManagerType, CAN_VAR_NO_INIT, CAN_VAR_NO_INIT) CanXL_GpRamManager[CAN_CANXL_NO_OF_CONTROLLER];    /* PRQA S 3432 # JV-01 */
#define CAN_STOP_SEC_VAR_NO_INIT_PTR
#include "Can_MemMap.h"

#define CAN_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Can_MemMap.h"
extern VAR(CanXL_MacFilterMng, CAN_VAR_NO_INIT) CanXL_GaaMacFilterMng[CAN_CANXL_NO_OF_CONTROLLER];
extern volatile VAR(CanXL_ControllerStatusType, CAN_VAR_NO_INIT) CanXL_GaaCtrlStat[CAN_CANXL_NO_OF_CONTROLLER];
#define CAN_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Can_MemMap.h"

#endif /* #if (CAN_CANXL_SUPPORTED == STD_ON) */

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/
#if (CAN_CANXL_SUPPORTED == STD_ON)
#define CAN_START_SEC_PRIVATE_CODE
#include "Can_MemMap.h"
extern FUNC(CanXL_ExtRxStatusType, CAN_PRIVATE_CODE) CanXL_RxQueueProcess(
       CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulQueueIdx);
extern FUNC(void, CAN_PRIVATE_CODE) CanXL_HwTxConfirmation(CONST(uint32, AUTOMATIC) LulCtrlIdx);

extern FUNC(uint16, CAN_PRIVATE_CODE) CanXL_ComputeCRC(P2CONST(uint32, AUTOMATIC, RECAN_APPL_DATAGSPACE)
                                                Descriptor, uint8 DescType);

extern FUNC(boolean, CAN_PRIVATE_CODE) Can_CanXLInit (CONST(uint8, AUTOMATIC) LucControllerID);

extern FUNC(boolean, CAN_PRIVATE_CODE) CanXL_DeInitController (uint8 LucController);

extern FUNC(Std_ReturnType, CAN_PRIVATE_CODE) CanXL_ConsistentCheck(CONST(uint8, AUTOMATIC) LucCtrlIndex, 
           P2CONST(volatile uint32, AUTOMATIC, CAN_APPL_DATA) LpTargetData, CONST(uint8, AUTOMATIC) LucSdtType);

extern FUNC(void, CAN_PRIVATE_CODE) CanXL_TECEmulator(CONST(uint8, AUTOMATIC) LulCtrlIdx, 
                            P2VAR(Can_TxDescriptorsType, AUTOMATIC, CAN_CONFIG_DATA) Descriptor);                       /* PRQA S 3432 # JV-01 */

extern FUNC(Can_CommonReturnType, CAN_PRIVATE_CODE) CanXL_CheckBusyQueue(
       P2VAR(Can_TxDescriptorsType *, AUTOMATIC, ETH_APPL_DATA) LpTargetDesc,                                           /* PRQA S 3432 # JV-01 */
       P2CONST(Can_HohConfigType, AUTOMATIC, CAN_CONFIG_DATA) LpHoh);
extern FUNC(void, CAN_PRIVATE_CODE) CanXL_ReleaseTxBuffer(
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulBufIdx);

extern FUNC(void, CAN_PRIVATE_CODE) CanXL_WriteRxData(CONST(uint8, AUTOMATIC) LucCtrlInfoIndex, 
  VAR(uint32, AUTOMATIC) LulQueueIndex, P2VAR(Can_RxDescriptorsType, AUTOMATIC, CAN_CONFIG_DATA) Descriptor,            /* PRQA S 3432 # JV-01 */
  P2VAR(uint32, AUTOMATIC, CAN_VAR_NO_INIT) LpCanSdu);                                                                  /* PRQA S 3432 # JV-01 */

#define CAN_STOP_SEC_PRIVATE_CODE
#include "Can_MemMap.h"
#endif /* #if (CAN_CANXL_SUPPORTED == STD_ON) */

#endif /* CAN_RAM_HEADER */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
