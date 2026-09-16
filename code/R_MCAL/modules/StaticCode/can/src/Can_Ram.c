/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Can_Ram.c                                                                                           */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2019-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Provision of initialized and uninitialized global variables and constants.                                         */
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
 *                    : Add message 1502 to support QA-C version 11.6.0
 * 2.3.0: 28/02/2025  : As part of ARDAACL-52460: Remove redundant variable CanXL_GaaFIFOQueuePosition
 * 2.2.0: 31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 *                      As part of CANXL driver support, following changes are made:
 *                      1. Remove CanXL_GaaErrorSignaling, CanXL_GaaEmulationTEC, CanXL_GaaEmulationREC
 * 2.1.2: 31/10/2024  : As part of CANXL driver support, following changes are made:
 *                      1. Add precompile condition for CanXL_GaaHwAccessFlag
 *                      2. Update condition to check CAN_NO_OF_UNITS
 * 2.1.1: 30/08/2024  : As part of CANXL driver support, following changes are made:
 *                      1. Remove redundant QAC message
 *                      2. Add condition check macro of Global interrupt
 *                      3. Update type CanXL_GpHohConfig  
 *                      4. Add CanXL_GaaErrorSignaling, CanXL_GaaEmulationTEC, CanXL_GaaEmulationREC
 *                      5. Update range CanXL_GaaTxBufferMgr_0, CanXL_GaaTxBufferMgr_1  
 *                      6. Update memory section DATA_CONTAINER_S_MEM_UNIT0 to DATA_CONTAINER_S_MEM_UNIT0_8, 
 *                      DATA_CONTAINER_S_MEM_UNIT1 to DATA_CONTAINER_S_MEM_UNIT1_8 
 *                      7. Add global variables: CanXL_GaaTxBufferTotal, CanXL_GaaRamSize, CanXL_GaaTxAllocCnt, 
 *                      CanXL_GaaRxBufferIndex, CanXL_GaaRxFrame, CanXL_GaaTxBufferMgrTable, CanXL_GaaMemPoolBufferTable
 *                      CanXL_GpRamManager, CanXL_GaaMacFilterMng, CanXL_GaaCtrlStat.
 * 2.0.1: 19/10/2023  : Remove message 0857, 1531
 * 2.0.0: 02/08/2023  : Change from Can_MemMap.h to Can_MemMap.h
 *                      Add QAC message
 *                      Add CWE Rule
 *        28/06/2023  : Remove redundant QAC messages
 *        31/05/2023  : Remove redundant QAC message
 * 1.4.3: 15/05/2022  : Add comment message 0857
 * 1.4.1: 08/03/2022  : Add comment message 0857
 * 1.4.0: 10/10/2021  : Update to add comment for QAC Msg(2:0857)
 * 1.3.2: 30/08/2021  : Update to support multi-instance:
 *                      - Change include to Can_MemMap.h
 * 1.3.1: 02/07/2021  : Format source code to 120 characters
 *                      Improve Violation tag (remove START/END)
 *        05/05/2021  : Update the memory section, memclass, ptrclass to change
 *                      the CAN_RSCAN prefix to CAN
 * 1.2.0: 09/07/2020  : Release.
 *        28/07/2020  : Add QAC 9.3.1 comment.
 * 1.1.0: 19/06/2020  : Release.
 * 1.0.2: 16/04/2020  : As per #266255, Add Can_GaaHwAccessFlag to implement
 *                      Mutex in Can_Write.
 * 1.0.1: 06/02/2020  : Add new memory section for VAR_NO_INIT_PTR complying
 *                      with AUTOSAR version 4.3.1
 *        20/01/2020  : Change Can_ControllerStateType to
 *                      Can_ControllerStateWrapperType complying with AUTOSAR
 *                      version 4.3.1
 * 1.0.0: 09/12/2019  : Initial version.
 */
/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
#include "Can.h"
#include "Can_Ram.h"
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define CAN_RAM_C_AR_RELEASE_MAJOR_VERSION    CAN_AR_RELEASE_MAJOR_VERSION_VALUE
#define CAN_RAM_C_AR_RELEASE_MINOR_VERSION    CAN_AR_RELEASE_MINOR_VERSION_VALUE
#define CAN_RAM_C_AR_RELEASE_REVISION_VERSION CAN_AR_RELEASE_REVISION_VERSION_VALUE
/* File version information */
#define CAN_RAM_C_SW_MAJOR_VERSION            CAN_SW_MAJOR_VERSION_VALUE
#define CAN_RAM_C_SW_MINOR_VERSION            CAN_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (CAN_RAM_AR_RELEASE_MAJOR_VERSION != CAN_RAM_C_AR_RELEASE_MAJOR_VERSION)
  #error "Can_Ram.c : Mismatch in Release Major Version"
#endif
#if (CAN_RAM_AR_RELEASE_MINOR_VERSION != CAN_RAM_C_AR_RELEASE_MINOR_VERSION)
  #error "Can_Ram.c : Mismatch in Release Minor Version"
#endif
#if (CAN_RAM_AR_RELEASE_REVISION_VERSION != CAN_RAM_C_AR_RELEASE_REVISION_VERSION)
  #error "Can_Ram.c : Mismatch in Release Revision Version"
#endif

#if (CAN_RAM_SW_MAJOR_VERSION != CAN_RAM_C_SW_MAJOR_VERSION)
  #error "Can_Ram.c : Mismatch in Software Major Version"
#endif
#if (CAN_RAM_SW_MINOR_VERSION != CAN_RAM_C_SW_MINOR_VERSION)
  #error "Can_Ram.c : Mismatch in Software Minor Version"
#endif

/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (4:5087)    : Use of #include directive after code fragment.                                               */
/* Rule                : MISRA C:2012 Rule-20.1                                                                       */
/* JV-01 Justification : This is done as per Memory Requirement, (MEMMAP003 - Specification of Memory Mapping).       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7                                                                       */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is accepted. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1533)    : The object '%1s' is only referenced by function '%2s'.                                       */
/* Rule                : MISRA C:2012 Rule-8.9                                                                        */
/* JV-01 Justification : This is accepted, due to the object is defined in separated source C file to followed        */
/*                       coding rule                                                                                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1502)    : The object 'name' is defined but is not used within this project.                            */
/* Rule                : MISRA C:2012 Rule-2.8, CWE Rule CWE-398, CWE-569, CERTC Rule MSC13                           */
/* JV-01 Justification : Array is used in another part of driver code. There is no problem in use                     */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/
#define CAN_START_SEC_VAR_INIT_BOOLEAN
#include "Can_MemMap.h"

/* Global variable to store initialization status of CAN Driver */
volatile VAR(boolean, CAN_VAR_INIT) Can_GblInitialized = CAN_FALSE;

#define CAN_STOP_SEC_VAR_INIT_BOOLEAN
#include "Can_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define CAN_START_SEC_VAR_NO_INIT_BOOLEAN
#include "Can_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#if (CAN_WAKEUP_SUPPORT == STD_ON) && (CAN_RSCANFD_CONFIGURED == STD_ON)
/* Global state transition is on-going when sleep or wakeup */
volatile VAR(boolean, CAN_VAR_NO_INIT) Can_GaaGlobalStateTransition[CAN_NO_OF_UNITS];
#endif

#if ((CAN_TX_BUFFER == STD_ON) || (CAN_TX_COMFIFO == STD_ON) || (CAN_TX_QUEUE == STD_ON) || \
      (CANFD_ON_XL_BUS_SUPPORT == STD_ON))
/* Flags which indicates HOH is being accessed by a Can_Write */
volatile VAR(boolean, CAN_VAR_NO_INIT) Can_GaaHwAccessFlag[CAN_NO_OF_HOHS];
#endif

#define CAN_STOP_SEC_VAR_NO_INIT_BOOLEAN
#include "Can_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define CAN_START_SEC_VAR_NO_INIT_32
#include "Can_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#if (CAN_WAKEUP_SUPPORT == STD_ON) && (CAN_RSCANFD_CONFIGURED == STD_ON)
/* Flags which indicates active (not slept) Controllers */
volatile VAR(uint32, CAN_VAR_NO_INIT) Can_GaaActiveControllers[CAN_NO_OF_UNITS];
#endif

#if (CAN_RSCAN0_RXFIFO_INTERRUPT == STD_ON) || (CAN_RSCAN1_RXFIFO_INTERRUPT == STD_ON) || \
    (CAN_RSCAN2_RXFIFO_INTERRUPT == STD_ON)
/* Interrupt disable count for Global interruption */
volatile VAR(uint32, CAN_VAR_NO_INIT) Can_GaaGlobalIntCount[CAN_NO_OF_UNITS];
#endif

#define CAN_STOP_SEC_VAR_NO_INIT_32
#include "Can_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define CAN_START_SEC_VAR_NO_INIT_PTR
#include "Can_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Global variable to store pointer to Config structure */
P2CONST(Can_ConfigType, CAN_VAR_NO_INIT, CAN_CONFIG_DATA) volatile Can_GpConfig;
P2CONST(Can_ControllerPCConfigType, CAN_VAR_NO_INIT, CAN_CONFIG_DATA) volatile Can_GpPCController;
P2CONST(Can_ControllerPBConfigType, CAN_VAR_NO_INIT, CAN_CONFIG_DATA) volatile Can_GpPBController;
P2CONST(Can_HohConfigType, CAN_VAR_NO_INIT, CAN_CONFIG_DATA) volatile Can_GpHohConfig;                                  /* PRQA S 1502 # JV-01 */

#define CAN_STOP_SEC_VAR_NO_INIT_PTR
#include "Can_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define CAN_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Can_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Global variable to controller status */
volatile VAR(Can_ControllerStateWrapperType, CAN_VAR_NO_INIT) Can_GaaCtrlState[CAN_MAX_NUMBER_OF_CONTROLLER];

#define CAN_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Can_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/*---------------------------------------------------------------------------------------------------------------------
 * CAN XL Specific
 ---------------------------------------------------------------------------------------------------------------------*/
#if (CAN_CANXL_SUPPORTED == STD_ON)
#define CAN_START_SEC_VAR_NO_INIT_PTR
#include "Can_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
P2CONST(Can_HohConfigType, CAN_VAR_NO_INIT, CAN_CONFIG_DATA) volatile CanXL_GpHohConfig;
#define CAN_STOP_SEC_VAR_NO_INIT_PTR
#include "Can_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define CAN_START_SEC_VAR_NO_INIT_BOOLEAN
#include "Can_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#if (CAN_CANXL_NO_OF_HOHS > CANXL_ZERO)
/* Flags which indicates HOH is being accessed by a CanXL_Write */
volatile VAR(boolean, CAN_VAR_NO_INIT) CanXL_GaaHwAccessFlag[CAN_CANXL_NO_OF_HOHS];
#endif
#define CAN_STOP_SEC_VAR_NO_INIT_BOOLEAN
#include "Can_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define CAN_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Can_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
VAR(CanXL_MacFilterMng, CAN_VAR_NO_INIT) CanXL_GaaMacFilterMng[CAN_CANXL_NO_OF_CONTROLLER];
volatile VAR(CanXL_ControllerStatusType, CAN_VAR_NO_INIT) CanXL_GaaCtrlStat[CAN_CANXL_NO_OF_CONTROLLER];

#if defined(CANXL_TX_BUF_TOTAL_0)
STATIC VAR(CanXL_TxBufferType, CAN_VAR_NO_INIT) CanXL_GaaTxBufferMgr_0[CANXL_TX_BUF_TOTAL_0];
#endif /* CANXL_TX_BUF_TOTAL_0 */
#if defined(CANXL_TX_BUF_TOTAL_1)
STATIC VAR(CanXL_TxBufferType, CAN_VAR_NO_INIT) CanXL_GaaTxBufferMgr_1[CANXL_TX_BUF_TOTAL_1];
#endif /* CANXL_TX_BUF_TOTAL_1 */

#define CAN_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Can_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define CAN_START_SEC_VAR_DATA_CONTAINER_S_MEM_UNIT0_8
#include "Can_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */                                                                                            
STATIC VAR(uint8, CAN_VAR_NO_INIT)CanXL_GaaMemPoolBuffer_0[CANXL_RAM_SIZE_0];
#define CAN_STOP_SEC_VAR_DATA_CONTAINER_S_MEM_UNIT0_8
#include "Can_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */                                                                                               

#if defined(CANXL_RAM_SIZE_1)
#define CAN_START_SEC_VAR_DATA_CONTAINER_S_MEM_UNIT1_8
#include "Can_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */                                                                                         
STATIC VAR(uint8, CAN_VAR_NO_INIT)CanXL_GaaMemPoolBuffer_1[CANXL_RAM_SIZE_1];                                      
#define CAN_STOP_SEC_VAR_DATA_CONTAINER_S_MEM_UNIT1_8
#include "Can_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */ 
#endif /* CANXL_RAM_SIZE_1 */

#define CAN_START_SEC_VAR_NO_INIT_32
#include "Can_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
VAR(uint32, CAN_VAR_NO_INIT) CanXL_GaaTxBufferTotal[CANXL_MAX_CONTROLLER] =
{
  CANXL_TX_BUF_TOTAL_0,
#if defined(CANXL_TX_BUF_TOTAL_1)
  CANXL_TX_BUF_TOTAL_1
#else
  0
#endif
};

VAR(uint32, CAN_VAR_INIT) CanXL_GaaRamSize[CANXL_MAX_CONTROLLER] =                                                      /* PRQA S 1533 # JV-01 */
{
  CANXL_RAM_SIZE_0,
#if defined(CANXL_RAM_SIZE_1)
  CANXL_RAM_SIZE_1
#else
  0
#endif
};

VAR(uint32, CAN_VAR_NO_INIT) CanXL_GaaTxAllocCnt[CAN_CANXL_NO_OF_CONTROLLER][CANXL_MAX_TXQUEUE];

VAR(CanXL_RxFrameType, CAN_VAR_NO_INIT) CanXL_GaaRxFrame[CAN_CANXL_NO_OF_CONTROLLER];

#define CAN_STOP_SEC_VAR_NO_INIT_32
#include "Can_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define CAN_START_SEC_VAR_NO_INIT_PTR
#include "Can_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
P2VAR(CanXL_TxBufferType, AUTOMATIC, CAN_VAR_INIT) CanXL_GaaTxBufferMgrTable[CANXL_MAX_CONTROLLER] =                    /* PRQA S 3432 # JV-01 */
{
  CanXL_GaaTxBufferMgr_0, 
#if defined(CANXL_TX_BUF_TOTAL_1)
  CanXL_GaaTxBufferMgr_1
#else
  NULL_PTR
#endif
};

P2VAR(uint8, AUTOMATIC, CAN_VAR_INIT) CanXL_GaaMemPoolBufferTable[CANXL_MAX_CONTROLLER] =                               /* PRQA S 3432, 1533 # JV-01, JV-01 */
{
  CanXL_GaaMemPoolBuffer_0, /* Tx FIFO Queue + Priority Queue for Controller 0 */
#if defined(CANXL_RAM_SIZE_1)
  CanXL_GaaMemPoolBuffer_1  /* Tx FIFO Queue + Priority Queue for Controller 1 */
#else
  NULL_PTR
#endif
};

P2VAR(CanXL_MemManagerType, CAN_VAR_NO_INIT, CAN_VAR_NO_INIT) CanXL_GpRamManager[CAN_CANXL_NO_OF_CONTROLLER];           /* PRQA S 3432 # JV-01 */

#define CAN_STOP_SEC_VAR_NO_INIT_PTR
#include "Can_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* #if (CAN_CANXL_SUPPORTED == STD_ON) */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
