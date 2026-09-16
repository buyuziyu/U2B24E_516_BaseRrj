/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Can_MainServ.c                                                                                      */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2019-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Provision of Main Service Routines Functionality.                                                                  */
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
 * 2.4.0: 30/05/2025  : Update Can_CanXLTxConfirmation, Can_MainFunction_BusOff, Can_MainFunction_Mode, 
 *                      Can_RxIndicationCommonPart
 *                      Fixing QAC message
 * 2.3.1: 31/03/2025  : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 *                    : Update CanXL_RxProcessing, CanXL_RxIndication, Can_MainFunction_BusOff
 *                    : Add message 1502, 0489, 3006 to support QA-C version 11.6.0
 * 2.3.0: 28/02/2025  : As part of ARDAACL-41983:  Move clear flag step to the end of 
 *                      Can_RxIndicationTxRxFIFO, Can_RxIndicationRxFIFO 
 *                      As part of ARDAACL-52560: Update CanXL_RxProcessing, Can_MainFunction_BusOff,
 *                      Can_CanXLTxConfirmation, CanXL_RxIndication
 * 2.2.0: 31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 *                      As part of CANXL driver support, following changes are made:
 *                      1. Update Can_MainFunction_BusOff, Can_MainFunction_Read_Common, Can_CanXLTxConfirmation,
 *                      CanXL_RxProcessing, CanXL_RxIndication.
 * 2.1.2: 31/10/2024  : As part of U2Ax support, following changes are made:
 *                      1. Add Can_MainFunction_Write_20, Can_MainFunction_Write_21, Can_MainFunction_Read_20, 
 *                      Can_MainFunction_Read_21
 *                      2. Fixing QAC message. Remove messages: 2880, 2961, 0404, 0489
 *                      As part of CANXL driver support, following changes are made:
 *                      1. Update Can_MainFunction_BusOff, Can_MainFunction_Mode, Can_MainFunction_Read_Common 
 *                      2. Can_CanXLTxConfirmation to fix findings
 * 2.1.1: 30/08/2024  : As part of CANXL driver support, following changes are made:
 *                      1. Update CanXL_RxProcessing
 *                      2. Update Can_RxProcessingRxFIFO, Can_RxProcessingTxRxFIFO to fix 
 *                      CanHardwareObjectUsesPolling issue
 *                      3. Update CanXL_RxProcessing
 *                      4. Update Can_MainFunction_Write_Common, Can_CanXLTxConfirmation, CanXL_RxIndication
 *                      5. Update API Can_MainFunction_Write_Common, Can_MainFunction_Read_Common, CanXL_RxProcessing
 *                      Can_CanXLTxConfirmation, CanXL_RxIndication, Can_MainFunction_BusOff
 *                      6. Update API Can_CanXLTxConfirmation, CanXL_RxIndication
 *                      Add precondition to include CanXL.h, CanXLTrcv.h
 *                      Add precondition for API Can_RxIndicationCommonPart, Can_MainFunction_Write_Common
 *                      Can_RxIndicationCommonPart, Can_GaaPayloadFromPLSTable
 *                      7. Update API Can_CanXLTxConfirmation, CanXL_RxIndication to fix issue related to RX_FQ_INT_STS,
 *                      TX_FQ_INT_STS register 
 *                      8. Update API Can_CanXLTxConfirmation to fix issue FIFO_QUEUE
 *                      9. Add QAC message 3408
 *                      10. Update function Can_MainFunction_Write, Can_MainFunction_Read, Can_RxProcessingBuffer,  
 *                      Can_RxProcessingTxRxFIFO to support U2Bx-E
 *                      11. Add #include "CanXLTrcv.h" 
 *                      12. Update type CanXL_RxIndication
 *                      13. Update Can_MainFunction_BusOff, Can_CanXLTxConfirmation, CanXL_RxProcessing, 
 *                      CanXL_RxIndication
 *                      14. Add message header 2991
 *                      15. Change Can_GpConfig->pCoreID2Index[] to Can_GpPBController[].ucCoreId
 *                      16. Remove macro U2Cx_VLAB_CAN_USED
 *                      17. Change Can_GpPCController[].ucCoreId to Can_GpConfig->pCoreID2Index[]
 *                      CAN_KERNEL_COREID to Can_GpConfig->ucKernelCoreID
 *                      CAN_TOTAL_NUMBER_HTH_COMFIFO to Can_GpConfig->ucTotalHthComFIFO
 *                      CAN_TOTAL_NUMBER_HRH_RXFIFO to Can_GpConfig->ucTotalHrhRxFIFO
 *                      CAN_TOTAL_NUMBER_HRH_COMFIFO to Can_GpConfig->ucTotalHrhComFIFO
 *                      CAN_TOTAL_NUMBER_HRH_COMFIFO_UNIT_0 to Can_GpConfig->ucTotalHrhComFIFOUnit0
 *                      CAN_TOTAL_NUMBER_HRH_BUFFER to Can_GpConfig->ucTotalHrhBuffer
 *                      CAN_TOTAL_NUMBER_HRH_BUFFER_UNIT_0 to Can_GpConfig->ucTotalHrhBufferUnit0
 *                      18. Update reference ID to support CANXL
 *                      19. Add macro U2Cx_VLAB_CAN_USED in Can_MainFunction_Write_Common, Can_MainFunction_Read_Common
 *                      20. Add reference ID for Can_CanXLTxConfirmation, Can_RxProcessingBuffer, 
 *                      Can_RxIndicationRxBuffer, Can_RxIndicationCommonPart, CanXL_RxProcessing, CanXL_RxIndication
 *                      21. Add message header 0306, 0488, 0489, 2985, 2995, 3673
 *                      22. Correct AUTOSAR version name
 *                      23. Add message 3464
 *                      24. Support CANXL: CanXL_RxProcessing, CanXL_RxIndication, Can_CanXLTxConfirmation 
 * 2.0.1: 06/11/2023  : Remove redundant message 0857, remove header message 2963
 *        19/10/2023  : Remove message 1532, 0857, 2844, 2814, 2824, 3677
 *                      Add message 3415, 3006
 *        14/10/2023  : Change macro CAN_AR_R21_11_VERSION to CAN_AR_R22_11_VERSION
 *                      Add Dem report for CAN_E_TX_HISTORY_OVERFLOW 
 * 2.0.0: 16/08/2023  : Update function Can_MainFunction_BusOff, Can_MainFunction_Wakeup, Can_MainFunction_Mode,
 *                      Can_MainFunction_Write_Common, Can_MainFunction_Read_Common to support multi core
 *        02/08/2023  : Update function Can_MainFunction_BusOff, Can_MainFunction_Wakeup, Can_MainFunction_Mode, 
 *                      Can_MainFunction_Write_Common, Can_MainFunction_Read_Common, Can_CommonDetCheck to support 
 *                      multi core
 *                      Change from Can_Mapping.h to Can_MemMap.
 *                      Add QAC message
 *                      Remove redundant QAC messages
 *                      Update description of function
 *                      Add CWE Rule
 *        20/07/2023  : Split Can_RxProcessingTxRxFIFO and Can_RxProcessingRxFIFO from Can_RxProcessing
 *                      Change Can_BufferValidateRead to Can_RxProcessingBuffer
 *        30/06/2023  : Fix/Remove redundant QAC messages, update Can_RxProcessing
 *        27/06/2023  : Split Can_BufferValidateRead from Can_RxProcessing
 *        19/06/2023  : Update Can_TxConfirmationProcessing: Add Can_GusHthCOMFIFO2Id to check TxRxFIFO's index
 *        01/06/2023  : Update Can_RxIndicationCommonPart: Add function pointer pLpduCalloutReceiveFunction
 *                       Can_MainFunction_BusOff: Sequence of clearing error flags 
 *        31/05/2023  : Remove redundant QAC messages and #include Can_Externals.h
 *        06/05/2023  : Add #include Can_Externals.h
 * 1.5.0: 27/03/2023  : Add AUTOSAR release version information AUTOSAR R21-11
 * 1.4.5: 02/03/2022  : Function Can_TxConfirmationProcessing(): Change macro of formula LulTxQReserved from 
 *                      CAN_RSCAN_TXQUEUE_MAX_DEPTH to CAN_RSCAN_TXQUEUE_RESERVED
 *        10/02/2023  : Update Can_TxConfirmationProcessing function to clear interupt history 
 *                      of Can_GaaRegs[LucUnit].pCmn->aaTHLSTS[LucCh]
 *                      Remove the following decision statements in Can_TxConfirmationProcessing():
 *                       - if (0UL == (LulTXRXFIFOCleared & (1UL << LusTXRXFIFOIndex)))
 *                       - if (0UL == (LulTXQCleared & (1UL << LulTxQIndex)))
 *                      Remove variable LulTXRXFIFOCleared, LulTXQCleared which related to the interrupt status flag
 *                      Remove the following two conditional statements in Can_RxProcessing
 *                      CAN_COMMON_STATE_STARTED == Can_GaaCtrlState[LpHoh->ucController].enMode
 *                      CAN_TRUE != Can_GaaCtrlState[LpHoh->ucController].blBusOff
 * 1.4.4: 15/06/2022  : Add DummyRead and SYNCP
 * 1.4.3: 11/05/2022  : Change COMMON_OK to CAN_COMMON_OK; COMMON_NOT_OK to CAN_COMMON_NOT_OK;
                        Common_ReturnType to Can_CommonReturnType; COMMON_STATE_STARTED to CAN_COMMON_STATE_STARTED;
                        COMMON_STATE_STOPPED to CAN_COMMON_STATE_STOPPED;
                        COMMON_STATE_SLEEP to CAN_COMMON_STATE_SLEEP
          10/05/2022  : Remove "else" statement don't use when no action required. 
 *        12/04/2022  : Change LpPCController->ulWakeupSourceId to LpPCController->ucWakeupSourceId
                        Change (uint32)LpHoh->ucController to LpHoh->ucController. Update comment message 0857
 * 1.4.1: 08/03/2022  : Update comment and header message 2877 
          24/02/2022  : Update to add null pointer check for pICWakeup in function Can_MainFunction_Wakeup
 * 1.4.0: 08/10/2021  : Function Can_TxConfirmationProcessing, update precodition
 *                      check when define and assign value into local variable LulBufferIndex
 * 1.3.2: 30/08/2021  : Update to support multi-instance:
 *                      - Change include to Can_Mapping.h
 *                      - Change include to SCHM_CAN_HEADER
 * 1.3.1: 02/07/2021  : Add QAC message 9.5.0
 *                      Format source code to 120 characters
 *                      Improve Violation tag (remove START/END)
 *        05/05/2021  : Update the memory section, memclass, ptrclass to change
 *                      the CAN_RSCAN prefix to CAN
 *                      Update to include SchM_Can.h
 *        04/05/2021  : Update to use new macro to clear Interrupt Flag in
 *                      function Can_TxConfirmationProcessing,
 *                      Can_RxIndicationRxFIFO, Can_RxIndicationTxRxFIFO
 * 1.3.0: 12/03/2021  : Update to correct passed argument of EcuM_CheckWakeup
 *                      functions at Can_MainFunction_Wakeup.
 * 1.2.0: 09/07/2020  : Release.
 *        28/07/2020  : Add QAC 9.3.1 comment.
 * 1.1.1: 01/07/2020  : Function Can_RxProcessing update condition check
 *                      to improve RxProcessing is MIXED.
 * 1.1.0: 19/06/2020  : Release.
 * 1.0.3: 08/06/2020  : Update Can_TxConfirmationProcessing:
 *                      + Add condition break loop after found TxRx FIFO Index.
 *                      + Add condition break loop after found Tx Queue Index.
 *        02/06/2020  : As per #272230, Update Can_TxConfirmationProcessing
 *                      to get correct TX Queue Depth value.
 *        11/05/2020  : As per #268768, Can_TxConfirmationProcessing,
 *                      Can_RxIndicationRxFIFO, Can_RxIndicationTxRxFIFO,
 *                      Update to one more break condition instead of only
 *                      waiting for register change.
 * 1.0.2: 16/04/2020  : As per #266253, Add CAN_CONTROLLER_OFFSET to
 *                      ControllerID when invoke to CanIf
 * 1.0.1: 26/03/2020  : As per redmine #263175, Change pre-condition check from
 *                      ((CAN_RX_FIFO STD_ON) || (CAN_RX_COMFIFO STD_ON)) to
 *                      (CAN_RX_OBJECT == STD_ON) when declaring
 *                      Can_GaaPayloadFromPLSTable
 *        19/03/2020  : Updated Global Variables Used in function description.
 *        18/03/2020  : Add pre-condition check (CAN_WAKEUP_POLLING == STD_ON)
 *                      and (CAN_BUSOFF_POLLING == STD_ON) in
 *                      Can_MainFunction_BusOff and Can_MainFunction_Wakeup.
 *        12/03/2020  : Correct macro CAN_RSCAN_RMND_PER_UNIT in
 *                      Can_RxProcessing.
 *        11/03/2020  : Fetch values of RSCFDnCFDRMNDt to local variable.
 *                      Add check Controller Mode in Can_RxProcessing
 *                      Update argument for calling Can_RxProcessing in
 *                      function Can_MainFunction_Read_Common
 *        04/03/2020  : Remove functionality of full and one frame interrupt.
 *                      Add null check for pFCLAReg.
 *        20/01/2020  : Use common controller state macro for commonization of
 *                      AUTOSAR version 4.2.2 and 4.3.1 for the change of
 *                      controller state machine function.
 *        16/01/2020  : Update MainFunction APIs to not report to DET when CAN
 *                      module was not initialized complying with AUTOSAR
 *                      version 4.3.1
 *        10/01/2020  : Implement Det_ReportRuntimeError to report for AUTOSAR
 *                     version 4.3.1
 *        09/01/2020  : Support AUTOSAR version 4.3.1
 *                      - Use Can_CommonReturnType as representative of
 *                        Can_ReturnType and Std_ReturnType depending on
 *                        AUTOSAR Version
 * 1.0.0: 09/12/2019  : Initial version.
 */
/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/

/* CAN module header file */
#include "Can.h"

#if (CAN_CANXL_SUPPORTED == STD_ON)
/* CANXL module header file */
#include "CanXL.h"
#endif

/* Included for RAM variable declarations */
#include "Can_Ram.h"

#include "Can_Irq.h"
#if ((CAN_DEV_ERROR_DETECT == STD_ON) || (CAN_AR_VERSION == CAN_AR_431_VERSION) || \
     (CAN_AR_VERSION == CAN_AR_R22_11_VERSION))
/* Included for the declaration of Det_ReportError() */
/* and Det_ReportRuntimeError */
#include "Det.h"
#endif

/* including DEM header file */
#include "Dem.h"

/* CAN Interface call-back Header File */
#if (CAN_AR_VERSION == CAN_AR_R22_11_VERSION)
#if (CAN_CANXL_SUPPORTED == STD_ON)
#include "CanXLTrcv.h"
#endif
#include "CanIf_Can.h"
#else
#include "CanIf_Cbk.h"
#endif

/* Needed for RH850_Sv\MODE_ICR_AND */
#include "rh850_Types.h"

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define CAN_MAINSERV_C_AR_RELEASE_MAJOR_VERSION    CAN_AR_RELEASE_MAJOR_VERSION_VALUE
#define CAN_MAINSERV_C_AR_RELEASE_MINOR_VERSION    CAN_AR_RELEASE_MINOR_VERSION_VALUE
#define CAN_MAINSERV_C_AR_RELEASE_REVISION_VERSION CAN_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define CAN_MAINSERV_C_SW_MAJOR_VERSION            CAN_SW_MAJOR_VERSION_VALUE
#define CAN_MAINSERV_C_SW_MINOR_VERSION            CAN_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (CAN_MAINSERV_C_AR_RELEASE_MAJOR_VERSION != CAN_MAINSERV_AR_RELEASE_MAJOR_VERSION)
  #error "Can_MainServ.c : Mismatch in Release Major Version"
#endif
#if (CAN_MAINSERV_C_AR_RELEASE_MINOR_VERSION != CAN_MAINSERV_AR_RELEASE_MINOR_VERSION)
  #error "Can_MainServ.c : Mismatch in Release Minor Version"
#endif
#if (CAN_MAINSERV_C_AR_RELEASE_REVISION_VERSION != CAN_MAINSERV_AR_RELEASE_REVISION_VERSION)
  #error "Can_MainServ.c : Mismatch in Release Revision Version"
#endif

#if (CAN_MAINSERV_C_SW_MAJOR_VERSION != CAN_MAINSERV_SW_MAJOR_VERSION)
  #error "Can_MainServ.c : Mismatch in Software Major Version"
#endif

#if (CAN_MAINSERV_C_SW_MINOR_VERSION != CAN_MAINSERV_SW_MINOR_VERSION)
  #error "Can_MainServ.c : Mismatch in Software Minor Version"
#endif

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (3:2004)    : No concluding 'else' exists in this 'if'-'else'-'if' statement.                              */
/* Rule                : CERTCCM EXP02, MISRA C:2012 Rule-15.7, CWE Rule CWE-398, CWE-569                             */
/* JV-01 Justification : The "else"statement with empty content is removed to improve readability.                    */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3408)    : '%s' has external linkage and is being defined without any previous declaration.             */
/* Rule                : MISRA C:2012 Rule 8.4, CERTCCM DCL07                                                         */
/* JV-01 Justification : This is accepted, due to following coding rule, internal function can be defined in other C  */
/*                       source files                                                                                 */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:1006)    : [E] This in-line assembler construct is a language extension. The code has been ignored.     */
/* Rule                : MISRA-C:2012 Dir-1.1, Rule-1.2, Dir-4.2, CERTC 1.2.4 MSC14                                   */
/* JV-01 Justification : Inline assembler support for syncp instruction.                                              */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1533)    : The object '%1s' is only referenced by function '%2s'.                                       */
/* Rule                : MISRA C:2012 Rule-8.9, CWE Rule CWE-398, CWE-569                                             */
/* JV-01 Justification : This is accepted, due to the object is defined in separated source C file to followed        */
/*                       coding rule                                                                                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1504)    : The object '%1s' is only referenced in the translation unit where it is defined.             */
/* Rule                : CERTCCM DCL15, DCL19, MISRA C:2012 Rule-8.7, CWE Rule CWE-398, CWE-569                       */
/* JV-01 Justification : This is accepted, due to following coding rule, internal function can be defined in other C  */
/*                       source files                                                                                 */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:5087)    : Use of #include directive after code fragment.                                               */
/* Rule                : MISRA C:2012 Rule-20.1                                                                       */
/* JV-01 Justification : This is done as per Memory Requirement, (MEMMAP003 - Specification of Memory Mapping).       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1503)    : The function '%1s' is defined but is not used within this project.                           */
/* Rule                : CERTCCM MSC07, MISRA C:2012 Rule-2.1, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : This is accepted, due to the module's API is exported for user's usage.                      */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3416)    : Logical operation performed on expression with persistent side effects.                      */
/* Rule                : CERTCCM EXP45, CWE Rule CWE-398, CWE-569, CWE-737                                            */
/* JV-01 Justification : Logical operation accesses volatile object which is a register access. All register          */
/*                       addresses are generated with volatile qualifier. There is no impact on the functionality     */
/*                       due to this conditional check for mode change.                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:3383)    : Cannot identify wraparound guard for unsigned arithmetic expression.                         */
/* Rule                : CERTCCM INT30                                                                                */
/* JV-01 Justification : It can still result in values that are out of range for the intended use, as intuitive       */
/*                       "invariants" may not hold                                                                    */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3206)    : The parameter '%s' is not used in this function.                                             */
/* Rule                : CERTCCM MSC07, MSC13, MISRA C:2012 Rule-2.7, CWE Rule CWE-398, CWE-563, CWE-569              */
/* JV-01 Justification : This is done as per implementation requirement                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1505)    : The function '%1s' is only referenced in the translation unit where it is defined.           */
/* Rule                : CERTCCM DCL19, MISRA C:2012 Rule-8.7, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : This is accepted, due to following coding rule, internal function can be defined in other C  */
/*                       source files                                                                                 */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3678)    : The object referenced by '%1s' is not modified through it, so '%1s' could be declared with   */
/*                       type '%2s'.                                                                                  */
/* Rule                : MISRA C:2012 Rule-8.13                                                                       */
/* JV-01 Justification : This is accepted. It just an advise for  improve safety by reducing the possibility that     */
/*                       the referenced data is unintentionally modified through an unexpected alias and improves     */
/*                       clarity by indicating that the referenced data is not intended to be modified through this   */
/*                       alias or those depending on it                                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3469)    : This usage of a function-like macro looks like it could be replaced by an equivalent         */
/*                       function call.                                                                               */
/* Rule                : MISRA C:2012 Dir-4.9                                                                         */
/* JV-01 Justification : This message indicates that a candidate macro may be suitable for replacement by a           */
/*                       function, based on an actual call-site and the arguments passed to it there. (Other uses of  */
/*                       the macro may not necessarily be suitable for replacement.)                                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:3384)    : Cannot identify wraparound guard for dependent unsigned arithmetic expression.               */
/* Rule                : CERTCCM INT30                                                                                */
/* JV-01 Justification : In order to effectively guard against overflow and wraparound at all stages, the expression  */
/*                       should be split up into individual dynamic operations, with their own guards where applicable*/
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0316)    : Cast from a pointer to void to a pointer to object type.                                     */
/* Rule                : MISRA C:2012 Rule-11.5, CWE Rule CWE-188, CWE-398, CWE-569                                   */
/* JV-01 Justification : A cast should not be performed between a pointer to object type and a different pointer to   */
/*                       object type.                                                                                 */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0751)    : Casting to char pointer type.                                                                */
/* Rule                : CERTCCM EXP11, EXP39, CWE Rule CWE-188, CWE-398, CWE-468, CWE-588, CWE-465, CWE-569, CWE-737 */
/* JV-01 Justification : Using void due to specific requirement of input parameter. So, this can be skipped           */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE Rule CWE-398, CWE-569                                            */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is accepted. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (5:2976)    : Definite: Passing address of partially initialized object '%s' to a function parameter       */
/*                       declared as a pointer to const.                                                              */
/* Rule                : CERTCCM EXP33, CWE Rule CWE-456, CWE-908, CWE-452, CWE-737                                   */
/* JV-01 Justification : The message propose that address should be initialized before passed to function             */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (6:2877)    : This loop will never be executed more than once.                                             */
/* Rule                : CERTCCM MSC07, MISRA C:2012 Dir-4.1, CWE Rule CWE-670                                        */
/* JV-01 Justification : This loop will only be executed at least once, depends on user configuration.                */
/*       Verification  : This is Hardware Specification, X2x only provides 1 Unit. So it is not having any impact.    */
/**********************************************************************************************************************/
/* Message (3:3415)    : Right hand operand of '&&' or '||' is an expression with persistent side effects.            */
/* Rule                : MISRA C:2012 Rule-13.5, CERTCCM EXP02, CWE Rule CWE-398, CWE-768, CWE-569                    */
/* JV-01 Justification : Although it is a volatile object, it does not have direct access to the HW register, and     */
/*                       there is no side effect.                                                                     */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3464)    : Argument to macro '%s' contains a side effect that will be evaluated more than once.         */
/* Rule                : CERTCCM PRE31                                                                                */
/* JV-01 Justification : This message is only emitted for expressions expanded from argument tokens written out at    */
/*                       the top level, that did not themselves originate from a macro expansion.                     */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0306)    : Cast between a pointer to object and an integral type.                                       */
/* Rule                : CERTCCM INT36, MISRA C:2012 Rule-11.4                                                        */
/* JV-01 Justification : Typecasting is done as per the register size, to access hardware registers.                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0488)    : Performing pointer arithmetic.                                                               */
/* Rule                : CERTCCM EXP08, MISRA C:2012 Rule-18.4                                                        */
/* JV-01 Justification : This is to get the ID in the data structure in the code.                                     */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:2985)    : This operation is redundant. The value of the result is always that of the left-hand operand.*/
/* Rule                : CERTCCM MSC07, MSC13, MISRA C:2012 Rule-2.2                                                  */
/* JV-01 Justification : For readability, setting to registers will used redundant macros and is based on hardware    */
/*                       user's manual                                                                                */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (6:2995)    : The result of this logical operation is always 'true'.                                       */
/* Rule                : MISRA C:2012 Rule-2.2, CWE-561, CWE-633                                                      */
/* JV-01 Justification : Depending on device configuration, there is case where the 'if' will return 'false'.         */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (6:2991)    : The value of this 'if' controlling expression is always 'true'.                              */
/* Rule                : MISRA C:2012 Rule-14.3                                                                       */
/* JV-01 Justification : Depending on device configuration, there is case where the 'if' will return 'false'.         */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1502)    : The object 'name' is defined but is not used within this project.                            */
/* Rule                : MISRA C:2012 Rule-2.8, CWE Rule CWE-398, CWE-569, CERTC Rule MSC13                           */
/* JV-01 Justification : Array is used in another part of driver code. There is no problem in use                     */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3006)    : This function contains a mixture of in-line assembler statements and C statements.           */
/* Rule                : MISRA C:2012 Dir-4.3                                                                         */
/* JV-01 Justification : This is accepted, due to the implementation is following hardware specification.             */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0489)    : The integer value 1 is being added or subtracted from a pointer.                             */
/* Rule                : MISRA C:2012 Rule-18.4, CWE-188, CWE-468, CWE-398, CWE-465, CWE-569                          */
/* JV-01 Justification : This is to get the ID in the data structure in the code.                                     */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/
#if (CAN_RSCANFD_CONFIGURED == STD_ON) || (CAN_CANXL_SUPPORTED == STD_ON)
#define CAN_START_SEC_CONST_8
#include "Can_MemMap.h"
/* The LUT to acquire DLC register value from payload size */
CONST(uint8, CAN_CONST)
Can_GaaDLCFromPayloadTable[] =                                                                                          /* PRQA S 1502, 1533 # JV-01, JV-01 */
{
  0x00U, /*     0 byte  -> 0x00 */
  0x01U, /*     1 byte  -> 0x01 */
  0x02U, /*     2 bytes -> 0x02 */
  0x03U, /*     3 bytes -> 0x03 */
  0x04U, /*     4 bytes -> 0x04 */
  0x05U, /*     5 bytes -> 0x05 */
  0x06U, /*     6 bytes -> 0x06 */
  0x07U, /*     7 bytes -> 0x07 */
  0x08U, /*     8 bytes -> 0x08 */
  0x09U, /*  9~12 bytes -> 0x09 */
  0x09U, /*  9~12 bytes -> 0x09 */
  0x09U, /*  9~12 bytes -> 0x09 */
  0x09U, /*  9~12 bytes -> 0x09 */
  0x0AU, /* 13~16 bytes -> 0x0A */
  0x0AU, /* 13~16 bytes -> 0x0A */
  0x0AU, /* 13~16 bytes -> 0x0A */
  0x0AU, /* 13~16 bytes -> 0x0A */
  0x0BU, /* 17~20 bytes -> 0x0B */
  0x0BU, /* 17~20 bytes -> 0x0B */
  0x0BU, /* 17~20 bytes -> 0x0B */
  0x0BU, /* 17~20 bytes -> 0x0B */
  0x0CU, /* 21~24 bytes -> 0x0C */
  0x0CU, /* 21~24 bytes -> 0x0C */
  0x0CU, /* 21~24 bytes -> 0x0C */
  0x0CU, /* 21~24 bytes -> 0x0C */
  0x0DU, /* 25~32 bytes -> 0x0D */
  0x0DU, /* 25~32 bytes -> 0x0D */
  0x0DU, /* 25~32 bytes -> 0x0D */
  0x0DU, /* 25~32 bytes -> 0x0D */
  0x0DU, /* 25~32 bytes -> 0x0D */
  0x0DU, /* 25~32 bytes -> 0x0D */
  0x0DU, /* 25~32 bytes -> 0x0D */
  0x0DU, /* 25~32 bytes -> 0x0D */
  0x0EU, /* 33~48 bytes -> 0x0E */
  0x0EU, /* 33~48 bytes -> 0x0E */
  0x0EU, /* 33~48 bytes -> 0x0E */
  0x0EU, /* 33~48 bytes -> 0x0E */
  0x0EU, /* 33~48 bytes -> 0x0E */
  0x0EU, /* 33~48 bytes -> 0x0E */
  0x0EU, /* 33~48 bytes -> 0x0E */
  0x0EU, /* 33~48 bytes -> 0x0E */
  0x0EU, /* 33~48 bytes -> 0x0E */
  0x0EU, /* 33~48 bytes -> 0x0E */
  0x0EU, /* 33~48 bytes -> 0x0E */
  0x0EU, /* 33~48 bytes -> 0x0E */
  0x0EU, /* 33~48 bytes -> 0x0E */
  0x0EU, /* 33~48 bytes -> 0x0E */
  0x0EU, /* 33~48 bytes -> 0x0E */
  0x0EU, /* 33~48 bytes -> 0x0E */
  0x0FU, /* 49~64 bytes -> 0x0F */
  0x0FU, /* 49~64 bytes -> 0x0F */
  0x0FU, /* 49~64 bytes -> 0x0F */
  0x0FU, /* 49~64 bytes -> 0x0F */
  0x0FU, /* 49~64 bytes -> 0x0F */
  0x0FU, /* 49~64 bytes -> 0x0F */
  0x0FU, /* 49~64 bytes -> 0x0F */
  0x0FU, /* 49~64 bytes -> 0x0F */
  0x0FU, /* 49~64 bytes -> 0x0F */
  0x0FU, /* 49~64 bytes -> 0x0F */
  0x0FU, /* 49~64 bytes -> 0x0F */
  0x0FU, /* 49~64 bytes -> 0x0F */
  0x0FU, /* 49~64 bytes -> 0x0F */
  0x0FU, /* 49~64 bytes -> 0x0F */
  0x0FU, /* 49~64 bytes -> 0x0F */
  0x0FU  /* 49~64 bytes -> 0x0F */
};

/* The LUT to acquire payload size from DLC value */
CONST(uint8, CAN_CONST)
Can_GaaPayloadFromDLCTable[] =                                                                                          /* PRQA S 1533, 1504 # JV-01, JV-01 */
{
  0U,  /* 0x00 ->  0 byte  */
  1U,  /* 0x01 ->  1 byte  */
  2U,  /* 0x02 ->  2 bytes */
  3U,  /* 0x03 ->  3 bytes */
  4U,  /* 0x04 ->  4 bytes */
  5U,  /* 0x05 ->  5 bytes */
  6U,  /* 0x06 ->  6 bytes */
  7U,  /* 0x07 ->  7 bytes */
  8U,  /* 0x08 ->  8 bytes */
  12U, /* 0x09 -> 12 bytes */
  16U, /* 0x0A -> 16 bytes */
  20U, /* 0x0B -> 20 bytes */
  24U, /* 0x0C -> 24 bytes */
  32U, /* 0x0D -> 32 bytes */
  48U, /* 0x0E -> 48 bytes */
  64U  /* 0x0F -> 64 bytes */
};

#if ((CAN_RX_OBJECT == STD_ON) && ((CAN_RX_BUFFER == STD_ON) || (CAN_RX_FIFO == STD_ON) || (CAN_RX_COMFIFO == STD_ON)))
/* The LUT to acuire payload size from RFPLS/CFPLS field */
STATIC CONST(uint8, CAN_CONST) Can_GaaPayloadFromPLSTable[] =
{
  8U,  /* 0x0 ->  8 bytes */
  12U, /* 0x1 -> 12 bytes */
  16U, /* 0x2 -> 16 bytes */
  20U, /* 0x3 -> 20 bytes */
  24U, /* 0x4 -> 24 bytes */
  32U, /* 0x5 -> 32 bytes */
  48U, /* 0x6 -> 48 bytes */
  64U  /* 0x7 -> 64 bytes */
};
#endif /* End of (CAN_RX_OBJECT == STD_ON) */
#define CAN_STOP_SEC_CONST_8
#include "Can_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* (CAN_RSCANFD_CONFIGURED == STD_ON) */

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/
#define CAN_START_SEC_PRIVATE_CODE
#include "Can_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#if (CAN_RX_FIFO == STD_ON)
STATIC FUNC(void, CAN_PRIVATE_CODE)
    Can_RxIndicationRxFIFO(CONSTP2CONST(Can_HohConfigType, AUTOMATIC, CAN_PRIVATE_CONST) LpHoh,
                           CONST(uint8, AUTOMATIC) LucUnit);
#endif
#if (CAN_RX_COMFIFO == STD_ON)
STATIC FUNC(void, CAN_PRIVATE_CODE)
    Can_RxIndicationTxRxFIFO(CONSTP2CONST(Can_HohConfigType, AUTOMATIC, CAN_PRIVATE_CONST) LpHoh,
                             CONST(uint8, AUTOMATIC) LucUnit);
#endif
#if (CAN_RX_BUFFER == STD_ON)
STATIC FUNC(void, CAN_PRIVATE_CODE)
    Can_RxIndicationRxBuffer(CONSTP2CONST(Can_HohConfigType, AUTOMATIC, CAN_PRIVATE_CONST) LpHoh,
                             CONST(uint8, AUTOMATIC) LucUnit);
#endif
#if ((CAN_RX_OBJECT == STD_ON) && ((CAN_RX_BUFFER == STD_ON) || (CAN_RX_FIFO == STD_ON) || (CAN_RX_COMFIFO == STD_ON)))
STATIC FUNC(void, CAN_PRIVATE_CODE)
    Can_RxIndicationCommonPart(CONSTP2CONST(Can_HohConfigType, AUTOMATIC, CAN_PRIVATE_CONST) LpHoh,
                               VAR(uint32, AUTOMATIC) LaaCanSdu[], CONST(uint32, AUTOMATIC) LulDlc,
                               CONST(uint32, AUTOMATIC) LulIDRegValue, CONST(uint32, AUTOMATIC) LulFDSts);
#endif
STATIC FUNC(void, CAN_PRIVATE_CODE) Can_MainFunction_Write_Common(CONST(uint32, AUTOMATIC) LulIndex);
STATIC FUNC(void, CAN_PRIVATE_CODE) Can_MainFunction_Read_Common(CONST(uint32, AUTOMATIC) LulIndex);

#if (CAN_CANXL_SUPPORTED == STD_ON)
STATIC FUNC(void, CAN_PRIVATE_CODE) CanXL_RxIndication(
                            P2CONST(Can_HohConfigType, AUTOMATIC, CAN_PRIVATE_CONST) LpHoh,
                            P2VAR(Can_RxDescriptorsType, AUTOMATIC, CAN_CONFIG_DATA) Descriptor);                       /* PRQA S 3432 # JV-01 */
#endif
#define CAN_STOP_SEC_PRIVATE_CODE
#include "Can_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define CAN_START_SEC_PUBLIC_CODE
#include "Can_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Can_MainFunction_Write(_n)
**
** Service ID            : 0x01
**
** Description           : This function performs the polling of transmit
**                         confirmation that is configured statically as
**                         'to be polled'.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : The CAN Driver must be initialized.
**                         CAN_TX_PROCESSING is set to POLLING.
**
** Global Variables Used : None
**
** Functions Invoked     : Can_TxConfirmationProcessing
**
** Registers Used        : None
**
** Reference ID          : CAN_DUD_ACT_002
***********************************************************************************************************************/
FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_Write(void)                                                                /* PRQA S 1503 # JV-01 */
{
  Can_MainFunction_Write_Common(CAN_MAINFUNCTION_INSTANCE_0);
}
#if (CAN_NUMBER_OF_MAINFUNCTIONS > 0U)
FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_Write_0(void)                                                              /* PRQA S 1503 # JV-01 */
{
  Can_MainFunction_Write_Common(CAN_MAINFUNCTION_INSTANCE_0);
}
#endif
#if (CAN_NUMBER_OF_MAINFUNCTIONS > 1U)
FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_Write_1(void)                                                              /* PRQA S 1503 # JV-01 */
{
  Can_MainFunction_Write_Common(CAN_MAINFUNCTION_INSTANCE_1);
}
#endif
#if (CAN_NUMBER_OF_MAINFUNCTIONS > 2U)
FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_Write_2(void)                                                              /* PRQA S 1503 # JV-01 */
{
  Can_MainFunction_Write_Common(CAN_MAINFUNCTION_INSTANCE_2);
}
#endif
#if (CAN_NUMBER_OF_MAINFUNCTIONS > 3U)
FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_Write_3(void)                                                              /* PRQA S 1503 # JV-01 */
{
  Can_MainFunction_Write_Common(CAN_MAINFUNCTION_INSTANCE_3);
}
#endif
#if (CAN_NUMBER_OF_MAINFUNCTIONS > 4U)
FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_Write_4(void)                                                              /* PRQA S 1503 # JV-01 */
{
  Can_MainFunction_Write_Common(CAN_MAINFUNCTION_INSTANCE_4);
}
#endif
#if (CAN_NUMBER_OF_MAINFUNCTIONS > 5U)
FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_Write_5(void)                                                              /* PRQA S 1503 # JV-01 */
{
  Can_MainFunction_Write_Common(CAN_MAINFUNCTION_INSTANCE_5);
}
#endif
#if (CAN_NUMBER_OF_MAINFUNCTIONS > 6U)
FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_Write_6(void)                                                              /* PRQA S 1503 # JV-01 */
{
  Can_MainFunction_Write_Common(CAN_MAINFUNCTION_INSTANCE_6);
}
#endif
#if (CAN_NUMBER_OF_MAINFUNCTIONS > 7U)
FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_Write_7(void)                                                              /* PRQA S 1503 # JV-01 */
{
  Can_MainFunction_Write_Common(CAN_MAINFUNCTION_INSTANCE_7);
}
#endif
#if (CAN_NUMBER_OF_MAINFUNCTIONS > 8U)
FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_Write_8(void)                                                              /* PRQA S 1503 # JV-01 */
{
  Can_MainFunction_Write_Common(CAN_MAINFUNCTION_INSTANCE_8);
}
#endif
#if (CAN_NUMBER_OF_MAINFUNCTIONS > 9U)
FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_Write_9(void)                                                              /* PRQA S 1503 # JV-01 */
{
  Can_MainFunction_Write_Common(CAN_MAINFUNCTION_INSTANCE_9);
}
#endif
#if (CAN_NUMBER_OF_MAINFUNCTIONS > 10U)
FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_Write_10(void)                                                             /* PRQA S 1503 # JV-01 */
{
  Can_MainFunction_Write_Common(CAN_MAINFUNCTION_INSTANCE_10);
}
#endif
#if (CAN_NUMBER_OF_MAINFUNCTIONS > 11U)
FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_Write_11(void)                                                             /* PRQA S 1503 # JV-01 */
{
  Can_MainFunction_Write_Common(CAN_MAINFUNCTION_INSTANCE_11);
}
#endif
#if (CAN_NUMBER_OF_MAINFUNCTIONS > 12U)
FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_Write_12(void)                                                             /* PRQA S 1503 # JV-01 */
{
  Can_MainFunction_Write_Common(CAN_MAINFUNCTION_INSTANCE_12);
}
#endif
#if (CAN_NUMBER_OF_MAINFUNCTIONS > 13U)
FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_Write_13(void)                                                             /* PRQA S 1503 # JV-01 */
{
  Can_MainFunction_Write_Common(CAN_MAINFUNCTION_INSTANCE_13);
}
#endif
#if (CAN_NUMBER_OF_MAINFUNCTIONS > 14U)
FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_Write_14(void)                                                             /* PRQA S 1503 # JV-01 */
{
  Can_MainFunction_Write_Common(CAN_MAINFUNCTION_INSTANCE_14);
}
#endif
#if (CAN_NUMBER_OF_MAINFUNCTIONS > 15U)
FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_Write_15(void)                                                             /* PRQA S 1503 # JV-01 */
{
  Can_MainFunction_Write_Common(CAN_MAINFUNCTION_INSTANCE_15);
}
#endif
#if (CAN_NUMBER_OF_MAINFUNCTIONS > 16U)
FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_Write_16(void)                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
{
  Can_MainFunction_Write_Common(CAN_MAINFUNCTION_INSTANCE_16);
}
#endif
#if (CAN_NUMBER_OF_MAINFUNCTIONS > 17U)
FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_Write_17(void)                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
{
  Can_MainFunction_Write_Common(CAN_MAINFUNCTION_INSTANCE_17);
}
#endif
#if (CAN_NUMBER_OF_MAINFUNCTIONS > 18U)
FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_Write_18(void)                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
{
  Can_MainFunction_Write_Common(CAN_MAINFUNCTION_INSTANCE_18);
}
#endif
#if (CAN_NUMBER_OF_MAINFUNCTIONS > 19U)
FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_Write_19(void)                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
{
  Can_MainFunction_Write_Common(CAN_MAINFUNCTION_INSTANCE_19);
}
#endif
#if (CAN_NUMBER_OF_MAINFUNCTIONS > 20U)
FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_Write_20(void)                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
{
  Can_MainFunction_Write_Common(CAN_MAINFUNCTION_INSTANCE_20);
}
#endif
#if (CAN_NUMBER_OF_MAINFUNCTIONS > 21U)
FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_Write_21(void)                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
{
  Can_MainFunction_Write_Common(CAN_MAINFUNCTION_INSTANCE_21);
}
#endif
/***********************************************************************************************************************
** Function Name         : Can_MainFunction_Read(_n)
**
** Service ID            : 0x08
**
** Description           : This function performs the polling of receive
**                         indications that are configured statically as 'to be
**                         polled'.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : None
**
** Input Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : The CAN Driver must be initialized.
**                         Read operation must be set as polling mode.
**
** Global Variables Used : None
**
** Functions Invoked     : Can_MainFunction_Read_Common
**
** Registers Used        : None
**
** Reference ID          : CAN_DUD_ACT_008
***********************************************************************************************************************/
FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_Read(void)                                                                 /* PRQA S 1503 # JV-01 */
{
  Can_MainFunction_Read_Common(CAN_MAINFUNCTION_INSTANCE_0);
}
#if (CAN_NUMBER_OF_MAINFUNCTIONS > 0U)
FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_Read_0(void)                                                               /* PRQA S 1503 # JV-01 */
{
  Can_MainFunction_Read_Common(CAN_MAINFUNCTION_INSTANCE_0);
}
#endif
#if (CAN_NUMBER_OF_MAINFUNCTIONS > 1U)
FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_Read_1(void)                                                               /* PRQA S 1503 # JV-01 */
{
  Can_MainFunction_Read_Common(CAN_MAINFUNCTION_INSTANCE_1);
}
#endif
#if (CAN_NUMBER_OF_MAINFUNCTIONS > 2U)
FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_Read_2(void)                                                               /* PRQA S 1503 # JV-01 */
{
  Can_MainFunction_Read_Common(CAN_MAINFUNCTION_INSTANCE_2);
}
#endif
#if (CAN_NUMBER_OF_MAINFUNCTIONS > 3U)
FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_Read_3(void)                                                               /* PRQA S 1503 # JV-01 */
{
  Can_MainFunction_Read_Common(CAN_MAINFUNCTION_INSTANCE_3);
}
#endif
#if (CAN_NUMBER_OF_MAINFUNCTIONS > 4U)
FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_Read_4(void)                                                               /* PRQA S 1503 # JV-01 */
{
  Can_MainFunction_Read_Common(CAN_MAINFUNCTION_INSTANCE_4);
}
#endif
#if (CAN_NUMBER_OF_MAINFUNCTIONS > 5U)
FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_Read_5(void)                                                               /* PRQA S 1503 # JV-01 */
{
  Can_MainFunction_Read_Common(CAN_MAINFUNCTION_INSTANCE_5);
}
#endif
#if (CAN_NUMBER_OF_MAINFUNCTIONS > 6U)
FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_Read_6(void)                                                               /* PRQA S 1503 # JV-01 */
{
  Can_MainFunction_Read_Common(CAN_MAINFUNCTION_INSTANCE_6);
}
#endif
#if (CAN_NUMBER_OF_MAINFUNCTIONS > 7U)
FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_Read_7(void)                                                               /* PRQA S 1503 # JV-01 */
{
  Can_MainFunction_Read_Common(CAN_MAINFUNCTION_INSTANCE_7);
}
#endif
#if (CAN_NUMBER_OF_MAINFUNCTIONS > 8U)
FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_Read_8(void)                                                               /* PRQA S 1503 # JV-01 */
{
  Can_MainFunction_Read_Common(CAN_MAINFUNCTION_INSTANCE_8);
}
#endif
#if (CAN_NUMBER_OF_MAINFUNCTIONS > 9U)
FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_Read_9(void)                                                               /* PRQA S 1503 # JV-01 */
{
  Can_MainFunction_Read_Common(CAN_MAINFUNCTION_INSTANCE_9);
}
#endif
#if (CAN_NUMBER_OF_MAINFUNCTIONS > 10U)
FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_Read_10(void)                                                              /* PRQA S 1503 # JV-01 */
{
  Can_MainFunction_Read_Common(CAN_MAINFUNCTION_INSTANCE_10);
}
#endif
#if (CAN_NUMBER_OF_MAINFUNCTIONS > 11U)
FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_Read_11(void)                                                              /* PRQA S 1503 # JV-01 */
{
  Can_MainFunction_Read_Common(CAN_MAINFUNCTION_INSTANCE_11);
}
#endif
#if (CAN_NUMBER_OF_MAINFUNCTIONS > 12U)
FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_Read_12(void)                                                              /* PRQA S 1503 # JV-01 */
{
  Can_MainFunction_Read_Common(CAN_MAINFUNCTION_INSTANCE_12);
}
#endif
#if (CAN_NUMBER_OF_MAINFUNCTIONS > 13U)
FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_Read_13(void)                                                              /* PRQA S 1503 # JV-01 */
{
  Can_MainFunction_Read_Common(CAN_MAINFUNCTION_INSTANCE_13);
}
#endif
#if (CAN_NUMBER_OF_MAINFUNCTIONS > 14U)
FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_Read_14(void)                                                              /* PRQA S 1503 # JV-01 */
{
  Can_MainFunction_Read_Common(CAN_MAINFUNCTION_INSTANCE_14);
}
#endif
#if (CAN_NUMBER_OF_MAINFUNCTIONS > 15U)
FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_Read_15(void)                                                              /* PRQA S 1503 # JV-01 */
{
  Can_MainFunction_Read_Common(CAN_MAINFUNCTION_INSTANCE_15);
}
#endif
#if (CAN_NUMBER_OF_MAINFUNCTIONS > 16U)
FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_Read_16(void)                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
{
  Can_MainFunction_Read_Common(CAN_MAINFUNCTION_INSTANCE_16);
}
#endif
#if (CAN_NUMBER_OF_MAINFUNCTIONS > 17U)
FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_Read_17(void)                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
{
  Can_MainFunction_Read_Common(CAN_MAINFUNCTION_INSTANCE_17);
}
#endif
#if (CAN_NUMBER_OF_MAINFUNCTIONS > 18U)
FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_Read_18(void)                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
{
  Can_MainFunction_Read_Common(CAN_MAINFUNCTION_INSTANCE_18);
}
#endif
#if (CAN_NUMBER_OF_MAINFUNCTIONS > 19U)
FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_Read_19(void)                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
{
  Can_MainFunction_Read_Common(CAN_MAINFUNCTION_INSTANCE_19);
}
#endif
#if (CAN_NUMBER_OF_MAINFUNCTIONS > 20U)
FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_Read_20(void)                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
{
  Can_MainFunction_Read_Common(CAN_MAINFUNCTION_INSTANCE_20);
}
#endif
#if (CAN_NUMBER_OF_MAINFUNCTIONS > 21U)
FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_Read_21(void)                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
{
  Can_MainFunction_Read_Common(CAN_MAINFUNCTION_INSTANCE_21);
}
#endif
/***********************************************************************************************************************
** Function Name         : Can_MainFunction_BusOff
**
** Service ID            : 0x09
**
** Description           : This function performs the polling of BusOff events
**                         that are configured statically as 'to be polled'.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : The CAN Driver must be initialized.
**                         Busoff operation must be set as polling mode.
**                         If the state transition START to STOP has been
**                         started by Can_SetControllerMode, just clear error
**                         flags and do not do further operations.
**
** Global Variables Used : Can_GblInitialized, Can_GpConfig,
**                         Can_GpPCController, Can_GaaCtrlState,
**                         Can_GaaRegs, CanXL_GaaCtrlStat
**
** Functions Invoked     : Det_ReportError, CanIf_ControllerBusOff
**
** Registers Used        : (CFD)ERFL
**
** Reference ID          : CAN_DUD_ACT_009
** Reference ID          : CAN_DUD_ACT_009_CRT001, CAN_DUD_ACT_009_CRT002,
** Reference ID          : CAN_DUD_ACT_009_ERR001, CAN_DUD_ACT_009_GBL001,
** Reference ID          : CAN_DUD_ACT_009_GBL002, CAN_DUD_ACT_009_GBL003
** Reference ID          : CAN_DUD_ACT_009_GBL004, CAN_DUD_ACT_009_REG001
***********************************************************************************************************************/
FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_BusOff(void)                                                               /* PRQA S 1503 # JV-01 */
{
  #if (CAN_BUSOFF_POLLING == STD_ON)
  P2CONST(Can_ControllerPCConfigType, AUTOMATIC, CAN_CONFIG_DATA)
  LpPCController;
  VAR(uint8, AUTOMATIC) LucCtrlIndex;
  VAR(boolean, AUTOMATIC) LblNotificationRequired;
  VAR(boolean, AUTOMATIC) LblBusOff;

  #if (CAN_CANXL_SUPPORTED == STD_ON)
  VAR(uint8, AUTOMATIC) LucCtrlInfoIndex;
  VAR(uint8, AUTOMATIC) LucTransceiverID;
  P2CONST(Can_CanXLHWUnitInfoType, AUTOMATIC, CAN_CONFIG_DATA) LpCanXLHWInfo;
  uint32 LulCounter;
  P2CONST(CanXL_BufHandlerType, AUTOMATIC, CAN_APPL_DATA) LpBufHandlerPtr;
  #endif /* (CAN_CANXL_SUPPORTED == STD_ON) */

  #if (CAN_MULTI_CORE_SUPPORT == STD_ON)
  uint8 LucCoreId;
  /* Get core id for code branching */
  LucCoreId = (uint8)GetCoreID();
  #endif /* #if (CAN_MULTI_CORE_SUPPORT) */
  #endif /* (CAN_BUSOFF_POLLING == STD_ON) */

  /* If CAN Driver is not initialized yet, return without any operation */
  if (CAN_FALSE == Can_GblInitialized)                                                                                  /* PRQA S 3416 # JV-01 */
  {
    #if ((CAN_DEV_ERROR_DETECT == STD_ON) && (CAN_AR_VERSION == CAN_AR_422_VERSION))
    (void)Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_MAIN_BUSOFF_SID, CAN_E_UNINIT);
    #endif
  }
  else
  {
    #if (CAN_BUSOFF_POLLING == STD_ON)
    /* Loop for the number of Controllers configured  */
    for (LucCtrlIndex = 0U; LucCtrlIndex < Can_GpConfig->ucNoOfControllers; LucCtrlIndex++)                             /* PRQA S 3416 # JV-01 */
    {
      LpPCController = &Can_GpPCController[LucCtrlIndex];
      LblBusOff = CAN_FALSE;
      /* Check whether polling method is configured or not */
      if ((
          #if (CAN_CANXL_SUPPORTED == STD_ON)
          (CAN_XL == LpPCController->enControllerType) ||
          #endif
          (0UL == ((uint32)LpPCController->ucIntEnable & (uint32)CAN_CHECK_INT_BUSOFF)))
           && (CAN_TRUE != Can_GaaCtrlState[LucCtrlIndex].blBusOff)
          #if (CAN_MULTI_CORE_SUPPORT == STD_ON)
          /* Check current core ID and assigned core */
          && (LucCoreId == Can_GpPBController[LucCtrlIndex].ucCoreId)                                                   /* PRQA S 3415, 3416 # JV-01, JV-01 */
          #endif
          )
      {
        /* Check whether BusOff flag is enabled */
        if(
        #if (CAN_CANXL_SUPPORTED == STD_ON)
        (CAN_FD == LpPCController->enControllerType) 
        #endif
        #if (CAN_CANXL_SUPPORTED == STD_ON) && (CAN_RSCANFD_CONFIGURED == STD_ON)
        &&
        #endif
        #if (CAN_RSCANFD_CONFIGURED == STD_ON)
        (0UL != (Can_GaaRegs[LpPCController->ucUnit].pCmn->aaChReg[LpPCController->ucCh].ulERFL & CAN_RSCAN_BOEF))
        #endif
        )
        {
          #if (CAN_RSCANFD_CONFIGURED == STD_ON)
          LblBusOff = CAN_TRUE;
          #if (CAN_CHECK_SECURITY_EVENT_REPORTING == STD_ON)
          /* Clear Bus Off flag */
          RH850_SV_MODE_REG_AND(32, &Can_GaaRegs[LpPCController->ucUnit].pCmn->aaChReg[LpPCController->ucCh].ulERFL,    /* PRQA S 3464 # JV-01 */\
                                                                                                   ~CAN_RSCAN_BOEF);  
          #else
          /* Clear all error flags */
          Can_GaaRegs[LpPCController->ucUnit].pCmn->aaChReg[LpPCController->ucCh].ulERFL = CAN_RSCAN_ERFL_CLEAR;
          #endif
          #endif
        }
        #if (CAN_CANXL_SUPPORTED == STD_ON)
        else if (CAN_XL == LpPCController->enControllerType)                                                            /* PRQA S 2004 # JV-01 */
        {
          LucCtrlInfoIndex = Can_GpConfig->pCanXLSecondPhysicalControllerToIndex[LpPCController->ucCh];
          if ((CAN_TRUE == CanXL_GaaCtrlStat[LucCtrlInfoIndex].blErrorSignaling) && 
              (0UL == ((uint32)LpPCController->ucIntEnable & (uint32)CAN_CHECK_INT_BUSOFF)) &&
              (0UL != (CanXL_GaaRegs[LucCtrlInfoIndex].pPRT->ulSTAT & CAN_CANXL_BOEF)))
          {
            LblBusOff = CAN_TRUE;
          }
          else if ((CAN_FALSE == CanXL_GaaCtrlStat[LucCtrlInfoIndex].blErrorSignaling) &&                               /* PRQA S 2004 # JV-01 */
            (CanXL_GaaCtrlStat[LucCtrlInfoIndex].ulTEC >= 255UL))
          {
            LblBusOff = CAN_TRUE;
            CanXL_GaaCtrlStat[LucCtrlInfoIndex].ulTEC = 0U;
            CanXL_GaaCtrlStat[LucCtrlInfoIndex].ulREC = 0U;
          } /* else no action required*/
        }
        #endif
        if(CAN_TRUE == LblBusOff)
        {
          /*
           * The transition START -> STOP is done by the following triggers:
           *  - Can_SetControllerMode(CAN_COMMON_STATE_STOPPED)
           *  - Bus-off
           * To avoid the state transition is done twice by both of triggers,
           * the exclusive control is required.
           */
          CAN_ENTER_CRITICAL_SECTION(CAN_RAM_DATA_PROTECTION);
          if ((CAN_COMMON_STATE_STARTED == Can_GaaCtrlState[LucCtrlIndex].enMode) &&
              (CAN_NO_PENDING_TRANSITION == Can_GaaCtrlState[LucCtrlIndex].enSubState))
          {
            /* Set bus-off flag */
            Can_GaaCtrlState[LucCtrlIndex].blBusOff = CAN_TRUE;
            
            /* When busoff has been occured, HW is CHANNEL_HALT mode already.
               So no additional operation is required, just set the mode. */
            /* XCAN IP use SW to stop controller completely */
            #if (CAN_CANXL_SUPPORTED == STD_ON)
            if(CAN_XL == LpPCController->enControllerType)
            {
              if (CAN_TRUE == CanXL_GaaCtrlStat[LucCtrlInfoIndex].blErrorSignaling)
              {
                Can_GaaCtrlState[LucCtrlIndex].enSubState = CANXL_STOP_WAIT_TXRXQUEUE_STOP;
              }
              else
              {
                Can_GaaCtrlState[LucCtrlIndex].enSubState = CAN_TENTATIVE_TRANSITION;
              }
            }
            else
            #endif
            {
              Can_GaaCtrlState[LucCtrlIndex].enMode = CAN_COMMON_STATE_STOPPED;
              Can_GaaCtrlState[LucCtrlIndex].enSubState = CAN_NO_PENDING_TRANSITION;
            }
            /* Notification for CanIf is required */
            LblNotificationRequired = CAN_TRUE;
          }
          else
          {
            /* State transition by Can_SetControllerMode has been started
               already, ignore this BusOff interruption. */
            LblNotificationRequired = CAN_FALSE;
          }
          CAN_EXIT_CRITICAL_SECTION(CAN_RAM_DATA_PROTECTION);
          if (CAN_TRUE == LblNotificationRequired)
          {
            CanIf_ControllerBusOff((uint8)(LucCtrlIndex + CAN_CONTROLLER_OFFSET));                                      /* PRQA S 3383, 2985 # JV-01, JV-01 */
            #if (CAN_CANXL_SUPPORTED == STD_ON)
            if (CAN_XL == LpPCController->enControllerType)
            {
              LpCanXLHWInfo = 
                  (P2CONST(Can_CanXLHWUnitInfoType, AUTOMATIC, CAN_CONFIG_DATA))Can_GpConfig->pCanXLHWUnitInfo;         /* PRQA S 0316 # JV-01 */
              LucCtrlInfoIndex = Can_GpConfig->pCanXLSecondPhysicalControllerToIndex[LpPCController->ucCh];
              if (CAN_TRUE == LpCanXLHWInfo[LucCtrlInfoIndex].blEthStackConfigured)
              {
                for(LulCounter = 0UL; LulCounter < CanXL_GaaTxBufferTotal[LucCtrlInfoIndex]; LulCounter++)
                {
                  LpBufHandlerPtr = CanXL_GaaTxBufferMgrTable[LucCtrlInfoIndex][LulCounter].pBufferHdr;
                  /* Check Buffer handler is not NULL */
                  if (NULL_PTR != LpBufHandlerPtr)
                  {
                    /* Release all Tx buffer */
                    CanXL_ReleaseTxBuffer(LucCtrlInfoIndex, LulCounter);
                  } /* else no action required*/
                }
                if (ETH_MODE_ACTIVE == CanXL_GaaCtrlStat[LucCtrlInfoIndex].enMode)
                {
                  CanXL_GaaCtrlStat[LucCtrlInfoIndex].enMode = ETH_MODE_DOWN;
                  EthIf_TxConfirmation((uint8)(LucCtrlIndex + CAN_CONTROLLER_OFFSET),CANXL_BUSOFF_BUFFER_ID,E_NOT_OK);  /* PRQA S 3383 # JV-01 */
                }
                LucTransceiverID = LpCanXLHWInfo[LucCtrlInfoIndex].ucTransceiverID;
                (void)(CanXLTrcv_ReportErrorState(LucTransceiverID, CAN_ERRORSTATE_BUSOFF));
              }
              (void)CanXL_StopMode(LucCtrlIndex);
            }
            #endif
          } /* else No action required */
        } /* else No action required */
      } /* else No action required */
    }
    #endif /* (CAN_BUSOFF_POLLING == STD_ON) */
  }
}

/***********************************************************************************************************************
** Function Name         : Can_MainFunction_Wakeup
**
** Service ID            : 0x0A
**
** Description           : This function performs the polling of wake-up events
**                         that are configured statically as 'to be polled'.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : The CAN Driver must be initialized.
**                         Wakeup operation must be set as poling mode.
**
** Global Variables Used : Can_GblInitialized, Can_GpConfig,
**                         Can_GpPCController, Can_GaaCtrlState
**
** Functions Invoked     : Det_ReportError, Can_WakeupMode
**
** Registers Used        : EICn
**
** Reference ID          : CAN_DUD_ACT_010
** Reference ID          : CAN_DUD_ACT_010_CRT001, CAN_DUD_ACT_010_CRT002,
** Reference ID          : CAN_DUD_ACT_010_ERR001, CAN_DUD_ACT_010_GBL001,
** Reference ID          : CAN_DUD_ACT_010_GBL002, CAN_DUD_ACT_010_GBL003,
** Reference ID          : CAN_DUD_ACT_010_REG001, CAN_DUD_ACT_010_REG002
***********************************************************************************************************************/
FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_Wakeup(void)                                                               /* PRQA S 1503, 3006 # JV-01, JV-01 */
{
  #if ((CAN_WAKEUP_SUPPORT == STD_ON) && (CAN_WAKEUP_POLLING == STD_ON))
  P2CONST(Can_ControllerPCConfigType, AUTOMATIC, CAN_CONFIG_DATA) LpPCController;
  VAR(uint32, AUTOMATIC) LucCtrlIndex;
  VAR(boolean, AUTOMATIC) LblCheckWakeupRequired;
  #if (CAN_MULTI_CORE_SUPPORT == STD_ON)
  uint8 LucCoreId;
  /* Get core id for code branching */
  LucCoreId = (uint8)GetCoreID();
  #endif
  #endif /* ((CAN_WAKEUP_SUPPORT == STD_ON) && (CAN_WAKEUP_POLLING == STD_ON)) */

  /* If CAN Driver is not initialized yet, return without any operation */
  if (CAN_FALSE == Can_GblInitialized)                                                                                  /* PRQA S 3416 # JV-01 */
  {
    #if ((CAN_DEV_ERROR_DETECT == STD_ON) && (CAN_AR_VERSION == CAN_AR_422_VERSION))
    /* Report to DET, if module is not initialized */
    (void)Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_MAIN_WAKEUP_SID, CAN_E_UNINIT);
    #endif
  }
  else
  {
    #if ((CAN_WAKEUP_SUPPORT == STD_ON) && (CAN_WAKEUP_POLLING == STD_ON))
    /* Loop for the number of Controllers configured */
    for (LucCtrlIndex = 0U; LucCtrlIndex < Can_GpConfig->ucNoOfControllers; LucCtrlIndex++)                             /* PRQA S 3416 # JV-01 */
    {
      LpPCController = &Can_GpPCController[LucCtrlIndex];
      if (
          #if (CAN_MULTI_CORE_SUPPORT == STD_ON)
          (LucCoreId == Can_GpPBController[LucCtrlIndex].ucCoreId) &&                                                   /* PRQA S 3416 # JV-01 */
          #endif /* #if (CAN_MULTI_CORE_SUPPORT) */
          (0UL == ((uint32)LpPCController->ucIntEnable &  (uint32)CAN_CHECK_INT_WAKEUP))
         )
      {
      /* Check whether wakeup interrupt request occurred */
        if (NULL_PTR != LpPCController->pICWakeup)
        {
          if (0U != (*LpPCController->pICWakeup & CAN_EIC_EIRF_MASK))
          {
            CAN_ENTER_CRITICAL_SECTION(CAN_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
            /* Clear EIRF */
            RH850_SV_MODE_ICR_AND(16, LpPCController->pICWakeup, (uint16)(~CAN_EIC_EIRF_MASK));
            /* DummyRead & SYNCP */
            RH850_SV_MODE_REG_READ_ONLY(16, LpPCController->pICWakeup);
            EXECUTE_SYNCP();                                                                                            /* PRQA S 1006 # JV-01 */
            #ifdef CAN_FILTER_CONTROL_SUPPORT
            if (NULL_PTR != LpPCController->pFCLAReg)
            {
              /* Clear the filter control register to reset value */
              *LpPCController->pFCLAReg = CAN_RSCAN_FCLA_DISABLE;
            } /* else No action required */
            #endif
            /* Confirm that state transition is not
            on-going by Can_SetControllerMode */
            if ((CAN_COMMON_STATE_SLEEP == Can_GaaCtrlState[LucCtrlIndex].enMode) &&
                (CAN_NO_PENDING_TRANSITION == Can_GaaCtrlState[LucCtrlIndex].enSubState))
            {
              /* The state transition takes a long time,
              the subsequent operation will be done in Can_MainFunction_Mode */
              Can_GaaCtrlState[LucCtrlIndex].enSubState =  CAN_PENDING_WAKEUP_REQUESTED;
              /* Store the wakeup event */
              Can_GaaCtrlState[LucCtrlIndex].blWakeupEventOccurred = CAN_TRUE;
              Can_GaaCtrlState[LucCtrlIndex].blWakeupByHW = CAN_TRUE;
              LblCheckWakeupRequired = CAN_TRUE;
            }
            else
            {
              /* If the state transition is already on-going, nothing to do */
              LblCheckWakeupRequired = CAN_FALSE;
            }
            CAN_EXIT_CRITICAL_SECTION(CAN_INTERRUPT_CONTROL_PROTECTION_GLOBAL);

            if (CAN_TRUE == LblCheckWakeupRequired)
            {
              Can_WakeupMode((uint8)LucCtrlIndex);
              /* Invoke EcuM_CheckWakeup call-back function */
              EcuM_CheckWakeup((EcuM_WakeupSourceType)(CAN_ONE << LpPCController->ucWakeupSourceId));
            } /* else No action required */
          } /* else No action required */
        } /* else No action required */
      } /* else No action required */
    }
    #endif /* ((CAN_WAKEUP_SUPPORT == STD_ON) && (CAN_WAKEUP_POLLING == STD_ON)) */
  }
}

/***********************************************************************************************************************
** Function Name         : Can_MainFunction_Mode
**
** Service ID            : 0x0C
**
** Description           : This function performs the polling of CAN controller
**                         mode transitions.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : The CAN Driver must be initialized.
**                         Mode operation must be set as polling mode.
**
** Remarks               : None
**
** Global Variables Used : Can_GblInitialized, Can_GpConfig,
**                         Can_GaaCtrlState
**
** Functions Invoked     : Det_ReportError, Can_StatMode, Can_StopMode,
**                         Can_SleepMode, Can_WakeupMode
**
** Registers Used        : None
**
** Reference ID          : CAN_DUD_ACT_012
** Reference ID          : CAN_DUD_ACT_012_ERR001
***********************************************************************************************************************/
FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_Mode(void)                                                                 /* PRQA S 1503 # JV-01 */
{
  VAR(uint8, AUTOMATIC) LucCtrlIndex;
  #if (CAN_MULTI_CORE_SUPPORT == STD_ON)
  uint8 LucCoreId;
  /* Get core id for code branching */
  LucCoreId = (uint8)GetCoreID();
  #endif /* #if (CAN_MULTI_CORE_SUPPORT) */

  /* If CAN Driver is not initialized yet, return without any operation */
  if (CAN_FALSE == Can_GblInitialized)                                                                                  /* PRQA S 3416 # JV-01 */
  {
    #if ((CAN_DEV_ERROR_DETECT == STD_ON) && (CAN_AR_VERSION == CAN_AR_422_VERSION))
    /* Report to DET, if module is not initialized */
    (void)Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_MAIN_MODE_SID, CAN_E_UNINIT);
    #endif
  }
  else
  {
    /* Loop for the number of Controllers configured */
    for (LucCtrlIndex = (uint8)0UL; LucCtrlIndex < Can_GpConfig->ucNoOfControllers; LucCtrlIndex++)                     /* PRQA S 3416 # JV-01 */
    {
      #if (CAN_MULTI_CORE_SUPPORT == STD_ON)
      if(LucCoreId == Can_GpPBController[LucCtrlIndex].ucCoreId)                                                        /* PRQA S 3416 # JV-01 */
      #endif /* #if (CAN_MULTI_CORE_SUPPORT) */
      {
        {
          switch (Can_GaaCtrlState[LucCtrlIndex].enSubState)
          {
            case CAN_PENDING_START_WAIT_RESET:
              Can_StartMode(LucCtrlIndex);
              break;
            case CAN_PENDING_START_WAIT_COM:
              Can_StartMode(LucCtrlIndex);
              break;
            case CAN_PENDING_STOP_WAIT_HALT:
              Can_StopMode(LucCtrlIndex);
              break;
            case CAN_PENDING_STOP_WAIT_RESET:
              Can_StopMode(LucCtrlIndex);
              break;
            #if (CAN_WAKEUP_SUPPORT == STD_ON)
            case CAN_PENDING_SLEEP_WAIT_STOP:
              Can_SleepMode(LucCtrlIndex);
              break;
            case CAN_PENDING_SLEEP_WAIT_GLOBALRESET:
              Can_SleepMode(LucCtrlIndex);
              break;
            case CAN_PENDING_SLEEP_WAIT_GLOBALSTOP:
              Can_SleepMode(LucCtrlIndex);
              break;
            case CAN_PENDING_WAKEUP_REQUESTED:
              Can_WakeupMode(LucCtrlIndex);
              break;
            case CAN_PENDING_WAKEUP_WAIT_GLOBALCHANGE:
              Can_WakeupMode(LucCtrlIndex);
              break;
            case CAN_PENDING_WAKEUP_WAIT_GLOBALRESET:
              Can_WakeupMode(LucCtrlIndex);
              break;
            case CAN_PENDING_WAKEUP_WAIT_GLOBALOP:
              Can_WakeupMode(LucCtrlIndex);
              break;
            case CAN_PENDING_WAKEUP_WAIT_RESET:
              Can_WakeupMode(LucCtrlIndex);
              break;
            #endif
            #if (CAN_CANXL_SUPPORTED == STD_ON)
            case CANXL_START_WAIT_RXQUEUE_START:
              CanXL_StartMode(LucCtrlIndex);
              break;
            case CANXL_START_WAIT_PRT_START:
              CanXL_StartMode(LucCtrlIndex);
              break;
            case CANXL_START_WAIT_BUSOFF_RECOVERY:
              CanXL_StartMode(LucCtrlIndex);
              break;
            case CANXL_STOP_WAIT_PRT_STOP:
              CanXL_StopMode(LucCtrlIndex);
              break;
            case CANXL_STOP_WAIT_TXRXQUEUE_STOP:
              CanXL_StopMode(LucCtrlIndex);
              break;
            case CANXL_STOP_WAIT_MH_STOP:
              CanXL_StopMode(LucCtrlIndex);
              break;
            #endif
            default: /* CAN_NO_PENDING_TRANSITION, CAN_TENTATIVE_TRANSITION */
              /* Nothing to do */
              break;
          } /* switch(*(LpPCController->pModeTransitionSts)) */
        }
      }
    }
  }
}
#define CAN_STOP_SEC_PUBLIC_CODE
#include "Can_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define CAN_START_SEC_PRIVATE_CODE
#include "Can_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Can_CommonDetCheck
**
** Service ID            : Not Applicable
**
** Description           : Perform DET checking for Controller ID
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LulSID        : Service ID
**                         LucController : Controller ID
**
** Output Parameters     : None
**
** Return parameter      : Can_CommonReturnType
**
** Preconditions         : None
**
** Global Variables Used : Can_GblInitialized, Can_GpConfig
**                         Can_GpPCController
**
** Functions Invoked     : Det_ReportError
**
** Registers Used        : None
**
** Reference ID          : CAN_DUD_ACT_046
** Reference ID          : CAN_DUD_ACT_046_ERR001, CAN_DUD_ACT_046_ERR002
** Reference ID          : CAN_DUD_ACT_046_ERR003
***********************************************************************************************************************/
#if (CAN_DEV_ERROR_DETECT == STD_ON)
FUNC(Can_CommonReturnType, CAN_PRIVATE_CODE)
Can_CommonDetCheck(CONST(uint8, AUTOMATIC) LucSID, CONST(uint8, AUTOMATIC) LucController)
{
  VAR(Can_CommonReturnType, AUTOMATIC) LenReturnValue;

  #if ((CAN_MULTI_CORE_SUPPORT == STD_ON) && (CAN_AR_R22_11_VERSION == CAN_AR_VERSION))
  VAR(uint8, AUTOMATIC) LucCoreId;
  /* Get Core id for code branching */
  LucCoreId = (uint8)GetCoreID();
  #endif /* #if (CAN_MULTI_CORE_SUPPORT == STD_ON) */

  /* Report to DET, if module is not initialized */
  if (CAN_FALSE == Can_GblInitialized)                                                                                  /* PRQA S 3416 # JV-01 */
  {
    (void)Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, LucSID, CAN_E_UNINIT);
    LenReturnValue = CAN_COMMON_NOT_OK;
  }
  /* Report to DET, if the Controller Id is out of range */
  else if ((Can_GpConfig->ucNoOfControllers <= LucController) ||                                                        /* PRQA S 3416 # JV-01 */
           (CAN_FALSE == Can_GpPCController[LucController].blActivation))                                               /* PRQA S 3415, 3416 # JV-01, JV-01 */
  {
    (void)Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, LucSID, CAN_E_PARAM_CONTROLLER);
    LenReturnValue = CAN_COMMON_NOT_OK;
  }
  #if ((CAN_MULTI_CORE_SUPPORT == STD_ON) && (CAN_AR_R22_11_VERSION == CAN_AR_VERSION))
    /* Check invalid core*/
  else if(LucCoreId != Can_GpPBController[LucController].ucCoreId)                                                      /* PRQA S 3416 # JV-01 */
  {
    /* Report to DET */
    (void)Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, LucSID, CAN_E_INVALID_CORE);
    LenReturnValue = CAN_COMMON_NOT_OK;
  }
  #endif
  else
  {
    LenReturnValue = CAN_COMMON_OK;
  }

  return LenReturnValue;
}
#endif /* (CAN_DEV_ERROR_DETECT == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Can_MainFunction_Write_Common
**
** Service ID            : Not Applicable
**
** Description           : This function notifies the upper layer about transmit
**                         confirmation.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LulIndex : Index of MainFunction configuration
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : The CAN Driver must be initialized.
**                         CAN_TX_PROCESSING is set to POLLING.
**
** Global Variables Used : Can_GblInitialized, Can_GpConfig,
**                         Can_GpPBController, Can_GpPCController
**
** Functions Invoked     : Can_TxConfirmationProcessing, Det_ReportError, Can_CanXLTxConfirmation
**
** Registers Used        : None
**
** Reference ID          : CAN_DUD_ACT_055
** Reference ID          : CAN_DUD_ACT_055_ERR001
***********************************************************************************************************************/
STATIC FUNC(void, CAN_PRIVATE_CODE) Can_MainFunction_Write_Common(CONST(uint32, AUTOMATIC) LulIndex)                    /* PRQA S 3206 # JV-01 */
{
  #if (((CAN_TX_POLLING == STD_ON) && \
    (((CAN_TX_BUFFER == STD_ON) || (CAN_TX_COMFIFO == STD_ON) || (CAN_TX_QUEUE == STD_ON)))) || \
    (CAN_CANXL_SUPPORTED == STD_ON))
  VAR(uint8, AUTOMATIC) LucCtrlIndex;
  #if (CAN_MULTI_CORE_SUPPORT == STD_ON)
  uint8 LucCoreId;
  /* Get core id for code branching */
  LucCoreId = (uint8)GetCoreID();
  #endif /* #if (CAN_MULTI_CORE_SUPPORT) */
  #endif

  /* If CAN Driver is not initialized yet, return without any operation */
  if (CAN_FALSE == Can_GblInitialized)                                                                                  /* PRQA S 3416 # JV-01 */
  {
    #if ((CAN_DEV_ERROR_DETECT == STD_ON) && (CAN_AR_VERSION == CAN_AR_422_VERSION))
    /* Report to DET, if module is not initialized */
    (void)Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_MAIN_WRITE_SID, CAN_E_UNINIT);
    #endif
  }
  else
  {
    #if (((CAN_TX_POLLING == STD_ON) && \
    (((CAN_TX_BUFFER == STD_ON) || (CAN_TX_COMFIFO == STD_ON) || (CAN_TX_QUEUE == STD_ON)))) || \
    (CAN_CANXL_SUPPORTED == STD_ON))
    /* Invoke Can_TxConfirmationProcessing for each Controller which
       cofigured as polling mode */
    for (LucCtrlIndex = 0U; LucCtrlIndex < Can_GpConfig->ucNoOfControllers; LucCtrlIndex++)                             /* PRQA S 3416 # JV-01 */
    {
      if (
          #if (CAN_NUMBER_OF_MAINFUNCTIONS > 0U)
          ((uint32)Can_GpPBController[LucCtrlIndex].ucMainFunctionWIndex == LulIndex) &&                                /* PRQA S 3416 # JV-01 */
          #endif
          (0U == (Can_GpPCController[LucCtrlIndex].ucIntEnable & CAN_CHECK_INT_TX))                                     /* PRQA S 3415, 3416 # JV-01, JV-01 */
          #if (CAN_MULTI_CORE_SUPPORT == STD_ON)
          /* Check current core ID and assigned core */
          && (LucCoreId == Can_GpPBController[LucCtrlIndex].ucCoreId)                                                   /* PRQA S 3415, 3416 # JV-01, JV-01 */
          #endif
          )
      {
        #if (CAN_CANXL_SUPPORTED == STD_ON)
        if (CAN_XL == Can_GpPCController[LucCtrlIndex].enControllerType)                                                /* PRQA S 3416 # JV-01 */
        {
          Can_CanXLTxConfirmation(LucCtrlIndex);
        }
        else
        #endif
        {
          #if ((CAN_TX_POLLING == STD_ON) && \
              ((CAN_TX_BUFFER == STD_ON) || (CAN_TX_COMFIFO == STD_ON) || (CAN_TX_QUEUE == STD_ON)))
          Can_TxConfirmationProcessing(LucCtrlIndex);
          #endif
        }
      } /* else No action required */
    }
    #endif /* (CAN_TX_POLLING == STD_ON) &&                        \
    (((CAN_TX_BUFFER == STD_ON) || (CAN_TX_COMFIFO == STD_ON) || \
    (CAN_TX_QUEUE == STD_ON))) */
  }
}

/***********************************************************************************************************************
** Function Name         : Can_MainFunction_Read_Common
**
** Service ID            : Not Applicable
**
** Description           : This function notifies the upper layer about receive
**                         messages.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LulIndex : Index of MainFunction Configuration
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : The CAN Driver must be initialized.
**                         Read operation must be set as polling mode.
**
** Global Variables Used : Can_GblInitialized
**
** Functions Invoked     : Can_RxProcessingRxFIFO, Can_RxProcessingTxRxFIFO, Can_RxProcessingBuffer, Det_ReportError,
**                         CanXL_RxProcessing
**
** Registers Used        : None
**
** Reference ID          : CAN_DUD_ACT_056
** Reference ID          : CAN_DUD_ACT_056_ERR001
***********************************************************************************************************************/
STATIC FUNC(void, CAN_PRIVATE_CODE) Can_MainFunction_Read_Common(
    CONST(uint32, AUTOMATIC) LulIndex)                                                                                  /* PRQA S 3206 # JV-01 */
{
  #if (CAN_RX_COMFIFO == STD_ON) 
  uint32 LulFilterCtrl;
  #endif
  #if (((CAN_RX_COMFIFO == STD_ON) && (CAN_MULTI_CORE_SUPPORT == STD_ON)) || (CAN_RX_BUFFER == STD_ON) || \
  (CAN_CANXL_SUPPORTED == STD_ON))
  uint8 LucCtrlIndex;
  #endif
  #if ((CAN_RX_FIFO == STD_ON) && (CAN_MULTI_CORE_SUPPORT == STD_ON))
  uint8 LucKernelCoreID;
  #endif

  #if (((CAN_RX_COMFIFO == STD_ON) || (CAN_RX_BUFFER == STD_ON) || (CAN_RX_FIFO == STD_ON) || \
       (CAN_CANXL_SUPPORTED == STD_ON)) && (CAN_MULTI_CORE_SUPPORT == STD_ON))
  uint8 LucCoreId;
  /* Get core id for code branching */
  LucCoreId = (uint8)GetCoreID();
  #endif 
  #if ((CAN_MULTI_CORE_SUPPORT == STD_OFF) && ((CAN_RX_BUFFER == STD_ON) || (CAN_CANXL_SUPPORTED == STD_ON)))
  /* Initial value when multi core not support*/
  LucCtrlIndex = 0;
  #endif
  
  if (CAN_FALSE == Can_GblInitialized)                                                                                  /* PRQA S 3416 # JV-01 */
  {
    #if ((CAN_DEV_ERROR_DETECT == STD_ON) && (CAN_AR_VERSION == CAN_AR_422_VERSION))
    /* Report to DET, if module is not initialized */
    (void)Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_MAIN_READ_SID, CAN_E_UNINIT);
    #endif
  }
  else
  {
    #if (CAN_RX_FIFO == STD_ON)
    #if (CAN_MULTI_CORE_SUPPORT == STD_ON)
    LucKernelCoreID = Can_GpConfig->ucKernelCoreID;
    if (LucKernelCoreID != LucCoreId)
    {
        /* Do nothing*/
    }
    else
    #endif
    {
      Can_RxProcessingRxFIFO(CAN_RXPROC_RXFIFO_ALL, CAN_INT_DISABLED, LulIndex);
    }
    #endif
    #if (((CAN_RX_COMFIFO == STD_ON) || (CAN_RX_BUFFER == STD_ON) || (CAN_CANXL_SUPPORTED == STD_ON)) && \
    (CAN_MULTI_CORE_SUPPORT == STD_ON))
      /* Loop all configured controller  */
    for (LucCtrlIndex = 0U; LucCtrlIndex < Can_GpConfig->ucNoOfControllers; LucCtrlIndex++)                             /* PRQA S 3416 # JV-01 */
    {
    /* Check coreID if multicore is true */
      if (LucCoreId == Can_GpPBController[LucCtrlIndex].ucCoreId)                                                       /* PRQA S 3416 # JV-01 */
    #endif
      {
        #if ((CAN_CANXL_SUPPORTED == STD_ON) && (CAN_MULTI_CORE_SUPPORT == STD_ON))
        if(CAN_XL == Can_GpPCController[LucCtrlIndex].enControllerType)                                                 /* PRQA S 3416 # JV-01 */
        #endif
        {
          #if (CAN_CANXL_SUPPORTED == STD_ON)
          CanXL_RxProcessing(LucCtrlIndex, CAN_INT_DISABLED, LulIndex);
          #endif
        }
        #if ((CAN_CANXL_SUPPORTED == STD_ON) && (CAN_MULTI_CORE_SUPPORT == STD_ON))
        else
        #endif
        {
          #if (CAN_RX_COMFIFO == STD_ON) 
          #if (CAN_MULTI_CORE_SUPPORT == STD_ON)
          /* Filter controller when CanMemoryMode is TxRxFiFo and multicore is true */
          LulFilterCtrl = CAN_RXPROC_TXRXFIFO(LucCtrlIndex);                                                            /* PRQA S 3469 # JV-01 */
          #else
          /* Set value to check all controller for Rx*/
          LulFilterCtrl = (uint32)CAN_RXPROC_TXRXFIFO_ALL;
          #endif
          Can_RxProcessingTxRxFIFO(LulFilterCtrl, CAN_INT_DISABLED, LulIndex);
          #endif
          #if (CAN_RX_BUFFER == STD_ON)
          Can_RxProcessingBuffer(LulIndex, LucCtrlIndex);
          #endif
        }
      }
    #if (((CAN_RX_COMFIFO == STD_ON) || (CAN_RX_BUFFER == STD_ON) || (CAN_CANXL_SUPPORTED == STD_ON)) && \
    (CAN_MULTI_CORE_SUPPORT == STD_ON))
    }
    #endif
  }
}

/***********************************************************************************************************************
** Function Name         : Can_TxConfirmationProcessing
**
** Service ID            : Not Applicable
**
** Description           : This function notifies the upper layer about transmit
**                         confirmation.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LucCtrlIndex : Index of Controller config table
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : The availability of the index must be guaranteed by
**                         the upper layer.
**
** Global Variables Used : Can_GpPCController, Can_GaaRegs,
**                         Can_GpConfig, Can_GpHohConfig
**
** Functions Invoked     : CanIf_TxConfirmation
**
** Registers Used        : (CFD)THLACC, (CFD)THLSTS, (CFD)THLPCTR,
**                         (CFD)CFSTSk, (CFD)TXQSTSm, (CFD)TMSTSp
**
** Reference ID          : CAN_DUD_ACT_032, CAN_DUD_ACT_032_ERR001
** Reference ID          : CAN_DUD_ACT_032_REG001, CAN_DUD_ACT_032_REG002,
** Reference ID          : CAN_DUD_ACT_032_REG003, CAN_DUD_ACT_032_REG004
** Reference ID          : CAN_DUD_ACT_032_REG005, CAN_DUD_ACT_032_REG006
***********************************************************************************************************************/
#if ((CAN_TX_BUFFER == STD_ON) || (CAN_TX_COMFIFO == STD_ON) || (CAN_TX_QUEUE == STD_ON))
FUNC(void, CAN_PRIVATE_CODE) Can_TxConfirmationProcessing(CONST(uint8, AUTOMATIC) LucCtrlIndex)                         /* PRQA S 1505 # JV-01 */
{
  P2VAR(volatile Can_THistRegType, AUTOMATIC, REGSPACE) LpTHistReg;                                                     /* PRQA S 3678 # JV-01 */
  VAR(uint8, AUTOMATIC) LucUnit;
  VAR(uint8, AUTOMATIC) LucCh;
  VAR(uint32, AUTOMATIC) LulHistoryData0;
  VAR(uint32, AUTOMATIC) LulHistoryData1;
  VAR(uint8, AUTOMATIC) LucCount;
  #if ((CAN_TX_COMFIFO == STD_ON) || (CAN_TX_BUFFER == STD_ON) || \
        ((CAN_TX_QUEUE == STD_ON) && (CAN_RSCAN_TXQUEUE_PER_CH > 1UL)))
  VAR(uint32, AUTOMATIC) LulBufferIndex;
  #endif
  #if ((CAN_TX_COMFIFO == STD_ON) || (CAN_TX_QUEUE == STD_ON))
  VAR(uint32, AUTOMATIC) LulBufferType;
  #endif
  #if (CAN_TX_COMFIFO == STD_ON)
  VAR(uint16, AUTOMATIC) LusHohIndex;
  VAR(uint16, AUTOMATIC) LusTXRXFIFOIndex;
  P2CONST(Can_HohConfigType, AUTOMATIC, CAN_CONFIG_DATA) LpHoh;
  VAR(boolean, AUTOMATIC) LblTXRXFIFOIndexFound;
  VAR(uint16, AUTOMATIC) LusHohId;
  #endif
  #if (CAN_TX_QUEUE == STD_ON)
  VAR(uint32, AUTOMATIC) LulTxQIndex;
  #if (CAN_RSCAN_TXQUEUE_PER_CH > 1UL)
  VAR(uint32, AUTOMATIC) LulTxQReserved;
  VAR(uint32, AUTOMATIC) LulTxQDepth;
  VAR(uint32, AUTOMATIC) LulTXQDValue;
  VAR(boolean, AUTOMATIC) LblTxQIndexFound;
  #endif
  #endif

  LucUnit = Can_GpPCController[LucCtrlIndex].ucUnit;
  LucCh = Can_GpPCController[LucCtrlIndex].ucCh;

  /* Get the address of transmit history access register
     because the address is different bw RSCAN and RSCANFD */
  #if ((CAN_RSCAN_CONFIGURED == STD_ON) && (CAN_RSCANFD_CONFIGURED == STD_ON))
  if (CAN_MACRO_RSCANFD == Can_GaaRegs[LucUnit].enMacroType)
  #endif
  {
    #if (CAN_RSCANFD_CONFIGURED == STD_ON)
    LpTHistReg = &(Can_GaaRegs[LucUnit].pFD->aaTHistReg[LucCh]);
    #endif
  }
  #if ((CAN_RSCAN_CONFIGURED == STD_ON) && (CAN_RSCANFD_CONFIGURED == STD_ON))
  else
  #endif
  {
    #if (CAN_RSCAN_CONFIGURED == STD_ON)
    LpTHistReg = &(Can_GaaRegs[LucUnit].pCmn->aaTHistReg[LucCh]);
    #endif
  }
  
  #if defined(CAN_E_TX_HISTORY_OVERFLOW)
  if(0UL != (Can_GaaRegs[LucUnit].pCmn->aaTHLSTS[LucCh] & CAN_RSCAN_THLEFT))
  {
    CAN_DEM_REPORT_ERROR(CAN_E_TX_HISTORY_OVERFLOW, DEM_EVENT_STATUS_FAILED);
  }
  #endif
  /* Clear transmit history overflow bit */
  Can_GaaRegs[LucUnit].pCmn->aaTHLSTS[LucCh] = CAN_RSCAN_CLEAR_THLELT;
  LucCount = 0U;
  /* Read all transmit history and inform CanIf */
  while ((((uint8)CAN_RSCAN_THL_ENTRIES_PER_CH) > LucCount)  &&
         (0UL == (Can_GaaRegs[LucUnit].pCmn->aaTHLSTS[LucCh] & CAN_RSCAN_THLEMP)))
  {
    /* Clear THL interrupt for every storing entry */
    Can_GaaRegs[LucUnit].pCmn->aaTHLSTS[LucCh] = CAN_RSCAN_CLEAR_THLIF;
    /* Read stored data from THL */
    LulHistoryData0 = LpTHistReg->ulTHLACC0;
    LulHistoryData1 = LpTHistReg->ulTHLACC1;
    /* Inform CanIf_TxConfirmation of */
    CanIf_TxConfirmation((PduIdType)CAN_RSCAN_TID_GET(LulHistoryData1));
    /* Increment buffer pointer */
    Can_GaaRegs[LucUnit].pCmn->aaTHLPCTR[LucCh] = CAN_RSCAN_THLPC_NEXT;

    /* Clear interrupt request flag according to the buffer type */
    #if ((CAN_TX_COMFIFO == STD_ON) || (CAN_TX_BUFFER == STD_ON) || \
          ((CAN_TX_QUEUE == STD_ON) && (CAN_RSCAN_TXQUEUE_PER_CH > 1UL)))
    LulBufferIndex = CAN_RSCAN_BN_GET(LulHistoryData0);
    #endif
    #if ((CAN_TX_COMFIFO == STD_ON) || (CAN_TX_QUEUE == STD_ON))
    LulBufferType = CAN_RSCAN_BT_GET(LulHistoryData0);
    #endif
    #if (CAN_TX_COMFIFO == STD_ON)
    if (CAN_RSCAN_BT_TXRXFIFO == LulBufferType)
    {
      /* Seek TxRxFIFO index of this buffer from the HOH config table */
      LusTXRXFIFOIndex = 0U;
      LusHohIndex = 0U;
      LblTXRXFIFOIndexFound = CAN_FALSE;
      while ((LusHohIndex < Can_GpConfig->ucTotalHthComFIFO) && (CAN_FALSE == LblTXRXFIFOIndexFound))                   /* PRQA S 3416 # JV-01 */
      {
        LusHohId = Can_GpConfig->Can_GusHthCOMFIFO2Id[LusHohIndex];
        LpHoh = &Can_GpHohConfig[LusHohId];
        if ((LpHoh->ucController == LucCtrlIndex) &&
            (CAN_RSCAN_CFTML_GET(LpHoh->ulXXCCRegValue) == LulBufferIndex))                                             /* PRQA S 3469 # JV-01 */
        {
          LusTXRXFIFOIndex = LpHoh->usBufferIndex;
          LblTXRXFIFOIndexFound = CAN_TRUE;
        } /* else No action required */
        LusHohIndex++;
      }
      /* Clear TxRxFIFO Tx interrupt flag */
      Can_GaaRegs[LucUnit].pCmn->aaCFSTS[LusTXRXFIFOIndex] = (CAN_RSCAN_CLEAR_CFTXIF);
    }
    else
    #endif /* (CAN_TX_COMFIFO == STD_ON) */
    #if (CAN_TX_QUEUE == STD_ON)
    if (CAN_RSCAN_BT_TXQUEUE == LulBufferType)
    {
      LulTxQIndex = 0UL;
      #if (CAN_RSCAN_TXQUEUE_PER_CH > 1UL)
      LblTxQIndexFound = CAN_FALSE;
      /* Seek Tx Queue index in a channel from configured Queue depth */
      while ((CAN_RSCAN_TXQUEUE_PER_CH > LulTxQIndex) && (CAN_FALSE == LblTxQIndexFound))
      {
        LulTxQReserved = (uint32)CAN_RSCAN_TXQUEUE_RESERVED * (LulTxQIndex / CAN_TWO);                                  /* PRQA S 3384 # JV-01 */
        /* Get TXQD value */
        LulTXQDValue = CAN_RSCAN_TXQDC_GET(Can_GaaRegs[LucUnit].pCmn->aaTQueueReg[LulTxQIndex].aaTXQCC[LucCh]);         /* PRQA S 3469 # JV-01 */
        /* Get Tx Queue Depth value */
        LulTxQDepth = CAN_RSCAN_TX_QUEUE_DEPTH_GET(LulTXQDValue);                                                       /* PRQA S 3469, 3383 # JV-01, JV-01 */
        /* Check the Tx Queue Index whether it contains the buffer */
        if (((0UL == (LulTxQIndex % CAN_TWO)) && ((LulTxQReserved + LulTxQDepth) > LulBufferIndex)) ||                  /* PRQA S 3383 # JV-01 */
            ((1UL == (LulTxQIndex % CAN_TWO)) &&
             ((LulBufferIndex - LulTxQReserved) >= (CAN_RSCAN_TXQUEUE_MAX_DEPTH - LulTxQDepth)) &&                      /* PRQA S 3383 # JV-01 */
             (CAN_RSCAN_TXQUEUE_MAX_DEPTH > (LulBufferIndex - LulTxQReserved))))                                        /* PRQA S 3383 # JV-01 */
        {
      #endif /* (CAN_RSCAN_TXQUEUE_PER_CH > 1UL) */
          /* Clear Tx Queue interrupt flag */
          Can_GaaRegs[LucUnit].pCmn->aaTQueueReg[LulTxQIndex].aaTXQSTS[LucCh] &= ~(CAN_RSCAN_TXQIF);
      #if (CAN_RSCAN_TXQUEUE_PER_CH > 1UL)
          LblTxQIndexFound = CAN_TRUE;
        } /* else No action required */
        LulTxQIndex++;
      }
      #endif /* (CAN_RSCAN_TXQUEUE_PER_CH > 1UL) */
    }
    else
    #endif /* (CAN_TX_QUEUE == STD_ON) */
    {
      #if (CAN_TX_BUFFER == STD_ON)
      /* Clear TMTRF flags (Tx completion) */
      Can_GaaRegs[LucUnit].pCmn->aaTMSTS[(LucCh * CAN_RSCAN_TXBUFFER_PER_CH) + LulBufferIndex] = CAN_RSCAN_TMTRF_NO;    /* PRQA S 3383 # JV-01 */
      #endif
    }
    LucCount++;
  }
}
#endif /* ((CAN_TX_BUFFER == STD_ON) || (CAN_TX_COMFIFO == STD_ON) || \
  (CAN_TX_QUEUE == STD_ON)) */

#if (CAN_CANXL_SUPPORTED == STD_ON)
/***********************************************************************************************************************
** Function Name         : Can_CanXLTxConfirmation
**
** Service ID            : Not Applicable
**
** Description           : This function notifies the upper layer about transmit
**                         confirmation.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LucCtrlIndex : Index of Controller config table
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : The availability of the index must be guaranteed by
**                         the upper layer.
**
** Global Variables Used : Can_GpPCController, CanXL_GaaRegs,
**                         Can_GpConfig, CanXL_GpHohConfig, CanXL_GaaCtrlStat
**
** Functions Invoked     : CanIf_TxConfirmation, CanXL_TECEmulator
**
** Registers Used        : (CFD)THLACC, (CFD)THLSTS, (CFD)THLPCTR,
**                         (CFD)CFSTSk, (CFD)TXQSTSm, (CFD)TMSTSp
**
** Reference ID          : CAN_DUD_ACT_074
** Reference ID          : CAN_DUD_ACT_074_REG001, CAN_DUD_ACT_074_REG002
** Reference ID          : CAN_DUD_ACT_074_REG003, CAN_DUD_ACT_074_REG004
** Reference ID          : CAN_DUD_ACT_074_REG005, CAN_DUD_ACT_074_REG006
** Reference ID          : CAN_DUD_ACT_074_REG007, CAN_DUD_ACT_074_REG008
** Reference ID          : CAN_DUD_ACT_074_GBL001, CAN_DUD_ACT_074_GBL002
** Reference ID          : CAN_DUD_ACT_074_GBL003, CAN_DUD_ACT_074_GBL004
** Reference ID          : CAN_DUD_ACT_074_GBL005, CAN_DUD_ACT_074_GBL006
***********************************************************************************************************************/
FUNC(void, CAN_PRIVATE_CODE) Can_CanXLTxConfirmation(CONST(uint8, AUTOMATIC) LucCtrlIndex)                              /* PRQA S 1505, 3006 # JV-01, JV-01 */
{
  #if (CANFD_ON_XL_BUS_SUPPORT == STD_ON)
  VAR(uint16, AUTOMATIC) LusHohIndex;
  VAR(uint16, AUTOMATIC) LusMaxHohIndex;
  #endif
  VAR(PduIdType, AUTOMATIC) LucPduID;
  VAR(uint8, AUTOMATIC) LucCtrlInfoIndex;
  VAR(uint16, AUTOMATIC) LusXLHohIndex;
  VAR(uint16, AUTOMATIC) LusMaxXLHohIndex;
  VAR(uint32, AUTOMATIC) LulDescIndex;
  VAR(uint32, AUTOMATIC) LusQueue;
  VAR(uint32, AUTOMATIC) LucController;
  VAR(Can_BufferType, AUTOMATIC) LusQueueType;
  P2VAR(Can_TxDescriptorsType, AUTOMATIC, CAN_CONFIG_DATA) LpTargetDesc;                                                /* PRQA S 3432 # JV-01 */
  P2VAR(Can_TxDescriptorsType, AUTOMATIC, CAN_CONFIG_DATA) LpCurrentDec;                                                /* PRQA S 3432 # JV-01 */
  P2VAR(PduIdType, AUTOMATIC, CAN_CONFIG_DATA) LpSwPduHandle;                                                           /* PRQA S 3432, 3678 # JV-01, JV-01 */
  P2CONST(Can_CanXLHWUnitInfoType, AUTOMATIC, CAN_CONFIG_DATA) LpCanXLHWInfo;
  P2CONST(Can_HohConfigType, AUTOMATIC, CAN_CONFIG_DATA) LpHoh;

  LusXLHohIndex = 0U;
  LusMaxXLHohIndex = Can_GpConfig->usCanXLNoOfHohs;
  #if (CANFD_ON_XL_BUS_SUPPORT == STD_ON)
  LusHohIndex = 0U;
  LusMaxHohIndex = Can_GpConfig->usNoOfHohs;
  #endif
  LpCanXLHWInfo = (P2CONST(Can_CanXLHWUnitInfoType, AUTOMATIC, CAN_CONFIG_DATA))Can_GpConfig->pCanXLHWUnitInfo;         /* PRQA S 0316 # JV-01 */
  LucController = Can_GpPCController[LucCtrlIndex].ucCh;
  LucCtrlInfoIndex = Can_GpConfig->pCanXLSecondPhysicalControllerToIndex[LucController];
  while ((LusXLHohIndex < LusMaxXLHohIndex)
        #if (CANFD_ON_XL_BUS_SUPPORT == STD_ON)
        || (LusHohIndex < LusMaxHohIndex)
        #endif
        )
  {
    
    if(LusXLHohIndex < LusMaxXLHohIndex)                                                                                /* PRQA S 2995, 2991 # JV-01, JV-01 */
    {
      LpHoh = &CanXL_GpHohConfig[LusXLHohIndex];
      LusXLHohIndex++;
    }
    #if (CANFD_ON_XL_BUS_SUPPORT == STD_ON)
    else
    {
      LpHoh = &Can_GpHohConfig[LusHohIndex];
      LusHohIndex++;
    }
    #endif
    
    if ((CAN_HOH_HTH == LpHoh->enHoh) && (LpHoh->ucController == LucCtrlIndex))
    {
      LusQueue = LpHoh->usBufferIndex;
      LusQueueType = LpHoh->enBufferType;
      if (CANXL_QUEUETYPE_TXPRIORITY == LusQueueType)
      {
        LpTargetDesc = (Can_TxDescriptorsType *)(CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulTXPQSTADD) + LusQueue;          /* PRQA S 0306, 0488 # JV-01, JV-01 */
        if ((1UL == ((LpTargetDesc->ulElement0) & 0x0FUL)) &&
        (0UL != (CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulTXPQINSTS0 & (uint32)(1UL << LusQueue)))
         && (((CANXL_BIT_SDT(5U) | CANXL_BIT_XLF) != (LpTargetDesc->ulElement4T0 & 0x400000FFUL))))                     /* PRQA S 3469 # JV-01 */
        {
          CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulTXPQINSTS0 &= (uint32)(1UL << LusQueue);
          /* Get PDU Id and inform to CanIf */
          LulDescIndex = LpCanXLHWInfo[LucCtrlInfoIndex].pTxPriorityQueueConfig->aaDescIndex[LusQueue];
          LpSwPduHandle = &LpCanXLHWInfo[LucCtrlInfoIndex].pTxPriorityQueueConfig->pSwPduHandle[LulDescIndex];
          LucPduID = *(LpSwPduHandle);
          CanIf_TxConfirmation(LucPduID);
        }
        if(CAN_FALSE == CanXL_GaaCtrlStat[LucCtrlInfoIndex].blErrorSignaling)
          {
          CanXL_TECEmulator(LucCtrlInfoIndex, LpTargetDesc);
        }
      }
      else
      {
        if(0U != (CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulTXFQINSTS & (uint32)(1UL << LusQueue)))
        {
          LpCurrentDec = (Can_TxDescriptorsType *)(CanXL_GaaRegs[LucCtrlInfoIndex].pMH->aaTXFQReg[LusQueue].ulTXADDPT); /* PRQA S 0306 # JV-01 */
          LpTargetDesc = CanXL_GaaCtrlStat[LucCtrlInfoIndex].stHwStatNonSDT5.aaHeadTxDesc[LusQueue];
          do
          {
            if(((CANXL_BIT_SDT(5U) | CANXL_BIT_XLF) != (LpTargetDesc->ulElement4T0 & 0x400000FFUL)) &&                  /* PRQA S 3469 # JV-01 */
              (0UL != ((LpTargetDesc->ulElement0) & 0x0FUL)))
            {
              if (1UL == ((LpTargetDesc->ulElement0) & 0x0FUL))
              {
                /* Get PDU Id and inform to CanIf */
                LulDescIndex = (uint32)
                            (LpTargetDesc - CanXL_GaaCtrlStat[LucCtrlInfoIndex].stHwStatFixed.aaFirstTxDesc[LusQueue]); /* PRQA S 0488 # JV-01 */
                LpSwPduHandle = &LpCanXLHWInfo[LucCtrlInfoIndex].pTxFIFOQueueConfig[LusQueue].pSwPduHandle[0];
                LucPduID = *(LpSwPduHandle + LulDescIndex);                                                             /* PRQA S 0488 # JV-01 */
                CanIf_TxConfirmation(LucPduID);
              }
              if(CAN_FALSE == CanXL_GaaCtrlStat[LucCtrlInfoIndex].blErrorSignaling)
              {
                CanXL_TECEmulator(LucCtrlInfoIndex, LpTargetDesc);
              }
              LpTargetDesc->ulElement0 &= CAN_DMA1_RESET_VALUE;
              LpTargetDesc->ulElement1 &= CAN_DMA2_RESET_VALUE;
              LpTargetDesc->ulElement4T0 = CAN_MH_INITIAL_VALUE;
            }
            if(LpTargetDesc != CanXL_GaaCtrlStat[LucCtrlInfoIndex].stHwStatFixed.aaLastTxDesc[LusQueue])
            {
              LpTargetDesc += 1UL;                                                                                      /* PRQA S 0489 # JV-01 */
            }
            else
            {
              LpTargetDesc = CanXL_GaaCtrlStat[LucCtrlInfoIndex].stHwStatFixed.aaFirstTxDesc[LusQueue];
            }
          }
          while (LpTargetDesc != LpCurrentDec);
          
          CanXL_GaaCtrlStat[LucCtrlInfoIndex].stHwStatNonSDT5.aaHeadTxDesc[LusQueue] = LpCurrentDec;
          /* Clear interrupt */
          CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulTXFQINSTS &= (uint32)(1UL << LusQueue);
        }
      }
      if((0UL != (CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulTXFQSTS0 & (uint32)(1UL << (LusQueue + 16UL)))) &&             /* PRQA S 3383 # JV-01 */
        (0UL != (CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulTXFQSTS1 & (uint32)(1UL << LusQueue))))
      {
        LpCurrentDec =(Can_TxDescriptorsType *)(CanXL_GaaRegs[LucCtrlInfoIndex].pMH->aaTXFQReg[LusQueue].ulTXADDPT);    /* PRQA S 0306 # JV-01 */
        if (0UL != ((uint32)(LpCurrentDec->ulElement0) & (CANXL_BIT_VALID(1U))))                                        /* PRQA S 3469 # JV-01 */
        {
          RH850_SET_IOREG_SYNCP(32, &CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulTXFQCTRL0, (1UL << LusQueue));              /* PRQA S 3464, 1006 # JV-01, JV-01 */
        }
      }
    } /* else No action required */
  }
  CanXL_GaaRegs[LucCtrlInfoIndex].pPRT->ulEVNT &= (CANXL_PRT_EVENT_ACK);
}
#endif /* #if (CAN_CANXL_SUPPORTED == STD_ON)*/
/***********************************************************************************************************************
** Function Name         : Can_RxProcessingRxFIFO
**
** Service ID            : Not Applicable
**
** Description           : This function notifies the upper layer about receive
**                         indication.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LulBufferBits : Target buffer to be read
**                         LulMode       : Interrupt or polling or both
**                         LulIndex      : Index of MainFunction configuration
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : The availability of pointers must be guaranteed by
**                         the upper layer.
**
** Global Variables Used : Can_GaaRegs, Can_GpConfig,
**                         Can_GpHohConfig, Can_GpPCController,
**                         Can_GaaCtrlState
**
** Functions Invoked     : Can_RxIndicationRxFIFO
**
** Registers Used        : (CFD)FESTS
**
** Reference ID          : CAN_DUD_ACT_033
***********************************************************************************************************************/
#if (CAN_RX_FIFO == STD_ON)
FUNC(void, CAN_PRIVATE_CODE) Can_RxProcessingRxFIFO( const uint32 LulBufferBits, const uint32 LulMode,                  /* PRQA S 1505 # JV-01 */
                                                                                              const uint32 LulIndex)    /* PRQA S 3206 # JV-01 */
{
  P2CONST(Can_HohConfigType, AUTOMATIC, CAN_CONFIG_DATA) LpHoh;
  P2CONST(Can_ControllerPCConfigType, AUTOMATIC, CAN_CONFIG_DATA) LpPCController;
  VAR(uint16, AUTOMATIC) LusHohId;
  VAR(uint16, AUTOMATIC) LusRxFIFOIndex;
  VAR(uint32, AUTOMATIC) LulCFDFESTS[CAN_NO_OF_UNITS];
  VAR(uint8, AUTOMATIC) LucUnit;

  for (LucUnit = 0U; CAN_NO_OF_UNITS > LucUnit; LucUnit++)                                                              /* PRQA S 2877 # JV-01 */
  {
    /* Fetch register RSCFDnCFDFESTS - ulFESTS */
    LulCFDFESTS[LucUnit] = Can_GaaRegs[LucUnit].pCmn->ulFESTS;
  }
  
  LusRxFIFOIndex = 0U;
  while (LusRxFIFOIndex < Can_GpConfig->ucTotalHrhRxFIFO)                                                               /* PRQA S 3416 # JV-01 */
  {
    /* Convert from HRH index to HRH ID */
    LusHohId = Can_GpConfig->Can_GusHrhIndex2Id[LusRxFIFOIndex];
    /* Get configuration respectively */
    LpHoh = &Can_GpHohConfig[LusHohId];
    LpPCController = &Can_GpPCController[LpHoh->ucController];
    LucUnit = LpPCController->ucUnit;
    if (0UL != (LulBufferBits & CAN_RXPROC_RXFIFO(LucUnit)))                                                            /* PRQA S 3469 # JV-01 */
    {
      /* Checking if FIFO is not empty */
      if ((0UL == (LulCFDFESTS[LucUnit] & CAN_RSCAN_FESTS_RXFFIFO_GET_BITMASK(LpHoh->usBufferIndex))) &&
        #if ((CAN_RX_POLLING == STD_ON) && (CAN_NUMBER_OF_MAINFUNCTIONS > 1U))
        (LulIndex == (uint32)LpHoh->ucMainFunctionRIndex) &&
        #endif
         /*
          * Check Can_RxProcessing is called by MainFunction and
          * CanHardwareObjectUsesPolling is true
          * Or Can_RxProcessing is called by ISR and
          * CanHardwareObjectUsesPolling is false
          */
          ((((uint32)CAN_INT_DISABLED == LulMode) && (CAN_TRUE == LpHoh->blObjectUsesPolling)) ||
          (((uint32)CAN_CHECK_INT_RX == LulMode) && (CAN_FALSE == LpHoh->blObjectUsesPolling)))
        )
        {
          Can_RxIndicationRxFIFO(LpHoh, LucUnit);
        }
    } /* else No action required */
    LusRxFIFOIndex++;
  } 
}
#endif/* (CAN_RX_FIFO == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Can_RxProcessingTxRxFIFO
**
** Service ID            : Not Applicable
**
** Description           : This function notifies the upper layer about receive
**                         indication.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LulBufferBits : Target buffer to be read
**                         LulMode       : Interrupt or polling or both
**                         LulIndex      : Index of MainFunction configuration
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : The availability of pointers must be guaranteed by
**                         the upper layer.
**
** Global Variables Used : Can_GaaRegs, Can_GpConfig,
**                         Can_GpHohConfig, Can_GpPCController,
**                         Can_GaaCtrlState
**
** Functions Invoked     : Can_RxIndicationTxRxFIFO
**
** Registers Used        : (CFD)FESTS
**
** Reference ID          : CAN_DUD_ACT_065
***********************************************************************************************************************/
#if (CAN_RX_COMFIFO == STD_ON)
FUNC(void, CAN_PRIVATE_CODE) Can_RxProcessingTxRxFIFO( const uint32 LulBufferBits, const uint32 LulMode, 
                                                                                              const uint32 LulIndex)    /* PRQA S 3206 # JV-01 */
{
  P2CONST(Can_HohConfigType, AUTOMATIC, CAN_CONFIG_DATA) LpHoh;
  VAR(uint16, AUTOMATIC) LusHohId;
  VAR(uint16, AUTOMATIC) LusTxRxFIFOIndex;
  VAR(uint32, AUTOMATIC) LulCFDFESTS[CAN_NO_OF_UNITS];
  VAR(uint8, AUTOMATIC) LucUnit;
  VAR(uint16, AUTOMATIC) LusBufferMaxIndex[] = {                                                                        /* PRQA S 3678 # JV-01 */
  #if (3U == CAN_NO_OF_UNITS)
  Can_GpConfig->ucTotalHrhComFIFO0,
  Can_GpConfig->ucTotalHrhComFIFO1,
  #endif
  #if (2U == CAN_NO_OF_UNITS)
  Can_GpConfig->ucTotalHrhComFIFO0,
  #endif
  Can_GpConfig->ucTotalHrhComFIFO};
  
  for (LucUnit = 0U; CAN_NO_OF_UNITS > LucUnit; LucUnit++)                                                              /* PRQA S 2877 # JV-01 */
  {
    /* Fetch register RSCFDnCFDFESTS - ulFESTS */
    LulCFDFESTS[LucUnit] = Can_GaaRegs[LucUnit].pCmn->ulFESTS;
  }
  
  LusTxRxFIFOIndex = Can_GpConfig->ucTotalHrhRxFIFO;
  for (LucUnit = 0U; CAN_NO_OF_UNITS > LucUnit; LucUnit++)                                                              /* PRQA S 2877 # JV-01 */
  {
    while (LusTxRxFIFOIndex < LusBufferMaxIndex[LucUnit])
    {
      /* Convert from HRH index to HRH ID */
      LusHohId = Can_GpConfig->Can_GusHrhIndex2Id[LusTxRxFIFOIndex];
      /* Get configuration respectively */
      LpHoh = &Can_GpHohConfig[LusHohId];
      if (0UL != (LulBufferBits & CAN_RXPROC_TXRXFIFO(LpHoh->ucController)))                                            /* PRQA S 3469 # JV-01 */
      {
        /* Checking if FIFO is not empty */
        if ((0UL == (LulCFDFESTS[LucUnit] & CAN_RSCAN_FESTS_TXRXFFIFO_GET_BITMASK(LpHoh->usBufferIndex))) &&            /* PRQA S 3383 # JV-01 */
          #if ((CAN_RX_POLLING == STD_ON) && (CAN_NUMBER_OF_MAINFUNCTIONS > 1U))
          (LulIndex == (uint32)LpHoh->ucMainFunctionRIndex) &&
          #endif
           /*
            * Check Can_RxProcessing is called by MainFunction and
            * CanHardwareObjectUsesPolling is true
            * Or Can_RxProcessing is called by ISR and
            * CanHardwareObjectUsesPolling is false
            */
            ((((uint32)CAN_INT_DISABLED == LulMode) && (CAN_TRUE == LpHoh->blObjectUsesPolling)) ||
            (((uint32)CAN_CHECK_INT_RX == LulMode) && (CAN_FALSE == LpHoh->blObjectUsesPolling)))
          )
          { 
            Can_RxIndicationTxRxFIFO(LpHoh, LucUnit);
          }
      } /* else No action required */
      LusTxRxFIFOIndex++;
    }
  }
}
#endif/* (CAN_RX_COMFIFO == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Can_RxProcessingBuffer
**
** Service ID            : Not Applicable
**
** Description           : This function notifies the upper layer about receive
**                         indication.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LulIndex: Index of MainFunction configuration
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : The availability of pointers must be guaranteed by
**                         the upper layer.
**
** Global Variables Used : Can_GaaRegs, Can_GpConfig,
**                         Can_GpHohConfig, Can_GpPCController,
**                         Can_GaaCtrlState
**
** Functions Invoked     : Can_RxIndicationRxBuffer
**
** Registers Used        : (CFD)RMNDy
**
** Reference ID          : CAN_DUD_ACT_064
** Reference ID          : CAN_DUD_ACT_064_REG001
***********************************************************************************************************************/
#if (CAN_RX_BUFFER == STD_ON)
FUNC(void, CAN_PRIVATE_CODE) Can_RxProcessingBuffer(                                                                    /* PRQA S 1505 # JV-01 */
              CONST(uint32, AUTOMATIC) LulIndex, VAR(uint8, AUTOMATIC) LucCtrlIndex)                                    /* PRQA S 3206 # JV-01 */
{
  P2CONST(Can_HohConfigType, AUTOMATIC, CAN_CONFIG_DATA) LpHoh;
  VAR(uint8, AUTOMATIC) LucUnit;
  VAR(uint16, AUTOMATIC) LucIndex;
  VAR(uint16, AUTOMATIC) LusHohId;
  VAR(uint32, AUTOMATIC) LulCFDRMNDt[CAN_NO_OF_UNITS][CAN_RSCAN_MAX_RMND_PER_UNIT];
  VAR(uint16, AUTOMATIC) LusBufferIndex;
  VAR(uint16, AUTOMATIC) LusBufferMaxIndex[] = {                                                                        /* PRQA S 3678 # JV-01 */
  #if (3U == CAN_NO_OF_UNITS)
  Can_GpConfig->ucTotalHrhBuffer0,
  Can_GpConfig->ucTotalHrhBuffer1,
  #endif
  #if (2U == CAN_NO_OF_UNITS)
  Can_GpConfig->ucTotalHrhBuffer0,
  #endif
  Can_GpConfig->ucTotalHrhBuffer};
  #if (CAN_MULTI_CORE_SUPPORT == STD_OFF)
  /* This command is added to fix QAC message 3206 */
  (void)LucCtrlIndex; 
  #endif 
  for (LucUnit = 0U; CAN_NO_OF_UNITS > LucUnit; LucUnit++)                                                              /* PRQA S 2877 # JV-01 */
  {
    /* Fetch all value of  RSCFDnCFDRMNDt registers to local variable */  
    for (LucIndex = 0U; CAN_RSCAN_MAX_RMND_PER_UNIT > LucIndex; LucIndex++)
    {
      LulCFDRMNDt[LucUnit][LucIndex] = Can_GaaRegs[LucUnit].pCmn->aaRMND[LucIndex];
    }
  }
  LusBufferIndex = Can_GpConfig->ucTotalHrhComFIFO;
  for (LucUnit = 0U; CAN_NO_OF_UNITS > LucUnit; LucUnit++)                                                              /* PRQA S 2877 # JV-01 */
  {
    while (LusBufferIndex < LusBufferMaxIndex[LucUnit])
    {
      /* Convert from HRH index to HRH ID */
      LusHohId = Can_GpConfig->Can_GusHrhIndex2Id[LusBufferIndex];
      /* Get configuration respectively */
      LpHoh = &Can_GpHohConfig[LusHohId];
      /* Checking if BUFFER has new data */
      if ((0UL != (LulCFDRMNDt[LucUnit][CAN_RSCAN_RMND_GET_INDEX(LpHoh->usBufferIndex)]
                                  & CAN_RSCAN_RMND_GET_BITMASK(LpHoh->usBufferIndex)))
          #if (CAN_MULTI_CORE_SUPPORT == STD_ON)
           && (LucCtrlIndex == LpHoh->ucController)
          #endif
          #if ((CAN_RX_POLLING == STD_ON) && (CAN_NUMBER_OF_MAINFUNCTIONS > 1U))
          && (LulIndex == (uint32)LpHoh->ucMainFunctionRIndex)
          #endif 
         )
      {
        Can_RxIndicationRxBuffer(LpHoh, LucUnit);
      }
      LusBufferIndex++;
    }
  } 
}
#endif /* (CAN_RX_BUFFER == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Can_RxIndicationRxFIFO
**
** Service ID            : Not Applicable
**
** Description           : This function reads a RxFIFO and
**                         notifies the upper layer about receive indication.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LpHoh   : Pointer to HRH
**                         LucUnit : Module number of RSCANn
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : The availability of the index must be guaranteed by
**                         the upper layer.
**
** Global Variables Used : Can_GaaRegs, Can_GaaPayloadFromDLCTable,
**                         Can_GaaPayloadFromPLSTable
**
** Functions Invoked     : Can_RxIndicationCommonPart, Det_ReportError, Det_ReportRuntimeError
**
** Registers Used        : CFDRFFDSTS, (CFD)RFID, (CFD)RFPTR, (CFD)RFDF,
**                         (CFD)RFPCTR, (CFD)RFSTS
**
** Reference ID          : CAN_DUD_ACT_047
** Reference ID          : CAN_DUD_ACT_047_ERR001, CAN_DUD_ACT_047_REG001,
** Reference ID          : CAN_DUD_ACT_047_REG002, CAN_DUD_ACT_047_REG003
***********************************************************************************************************************/
#if (CAN_RX_FIFO == STD_ON)
STATIC FUNC(void, CAN_PRIVATE_CODE)
    Can_RxIndicationRxFIFO(CONSTP2CONST(Can_HohConfigType, AUTOMATIC, CAN_PRIVATE_CONST) LpHoh,
                           CONST(uint8, AUTOMATIC) LucUnit)
{
  P2VAR(volatile uint32, AUTOMATIC, REGSPACE) LpDataReg;                                                                /* PRQA S 3678 # JV-01 */
  /* To optimize data copy operation, declare data array with uint32 */
  VAR(uint32, CAN_VAR_NO_INIT) LaaCanSdu[CAN_LOCALBUFFER_SIZE_32];
  VAR(uint32, AUTOMATIC) LulMessageDlc;
  VAR(uint32, AUTOMATIC) LulAvailableDlc;
  VAR(uint32, AUTOMATIC) LulFDSts;
  VAR(uint32, AUTOMATIC) LulIDRegValue;
  VAR(uint32, AUTOMATIC) LulWordIndex;
  VAR(uint32, AUTOMATIC) LulDlcWords;
  VAR(uint8, AUTOMATIC) LucRFDCValue;
  VAR(uint8, AUTOMATIC) LucFifoBufferDepth;
  VAR(uint8, AUTOMATIC) LucCount;

  /* Get Receive FIFO Buffer Depth Configuration value */
  LucRFDCValue = (uint8)CAN_RSCAN_RFDC_GET(LpHoh->ulXXCCRegValue);                                                      /* PRQA S 3469 # JV-01 */
  /* Get FIFO Buffer Depth value */
  LucFifoBufferDepth = (uint8)CAN_RSCAN_FIFO_BUFFER_DEPTH_GET(LucRFDCValue);
  LucCount = 0U;
  /* Read RxFIFO until the FIFO becomes empty */
  while ((0UL == (Can_GaaRegs[LucUnit].pCmn->aaRFSTS[LpHoh->usBufferIndex] & CAN_RSCAN_RFEMP)) &&
                  (LucCount < LucFifoBufferDepth))
  {
    #if ((CAN_DEV_ERROR_DETECT == STD_ON) || (CAN_AR_VERSION == CAN_AR_431_VERSION) || \
         (CAN_AR_VERSION == CAN_AR_R22_11_VERSION))
    /* Check lost message*/
    if (CAN_FIFO_MSG_LOST_MASK == ((Can_GaaRegs[LucUnit].pCmn->aaRFSTS[LpHoh->usBufferIndex])
                                   & CAN_FIFO_MSG_LOST_MASK))
    {
      /* Clear receive FIFO message lost flag */
      Can_GaaRegs[LucUnit].pCmn->aaRFSTS[LpHoh->usBufferIndex] = (CAN_RSCAN_CLEAR_RFMLT);
      #if (CAN_AR_VERSION == CAN_AR_422_VERSION)
      /* Report to DET default error */
      (void)Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_RXPROCESSING_SID, CAN_E_DATALOST);
      #elif ((CAN_AR_VERSION == CAN_AR_431_VERSION) || (CAN_AR_VERSION == CAN_AR_R22_11_VERSION))
      /* Report to DET runtime error */
      (void)Det_ReportRuntimeError(CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_RXPROCESSING_SID, CAN_E_DATALOST);
      #endif
    } /* else No action required */
    #endif /* ((CAN_DEV_ERROR_DETECT == STD_ON) || */
       /*  (CAN_AR_VERSION == CAN_AR_431_VERSION)) */

    #if ((CAN_RSCAN_CONFIGURED == STD_ON) && (CAN_RSCANFD_CONFIGURED == STD_ON))
    if (CAN_MACRO_RSCANFD == Can_GaaRegs[LucUnit].enMacroType)
    #endif
    {
      #if (CAN_RSCANFD_CONFIGURED == STD_ON)
      /* Get status and data register address accroding to each buffer mode */
      LulFDSts = Can_GaaRegs[LucUnit].pFD->aaRFReg[LpHoh->usBufferIndex].ulFDRFFDSTS;
      LulIDRegValue = Can_GaaRegs[LucUnit].pFD->aaRFReg[LpHoh->usBufferIndex].ulFDRFID;
      LulMessageDlc = Can_GaaRegs[LucUnit].pFD->aaRFReg[LpHoh->usBufferIndex].ulFDRFPTR;
      LpDataReg = &Can_GaaRegs[LucUnit].pFD->aaRFReg[LpHoh->usBufferIndex].aaFDRFDF[0];

      /* Convert DLC value to actual byte length */
      LulMessageDlc = (uint32)Can_GaaPayloadFromDLCTable[CAN_RSCAN_XXDLC_GET(LulMessageDlc)];
      /* Read registers as the smaller one of message DLC or buffer DLC */
      LulAvailableDlc = Can_GaaPayloadFromPLSTable[CAN_RSCAN_RFPLS_GET(LpHoh->ulXXCCRegValue)];                         /* PRQA S 3469 # JV-01 */
      if (LulAvailableDlc > LulMessageDlc)
      {
        LulAvailableDlc = LulMessageDlc;
      } /* else No action required */
      #endif /* (CAN_RSCANFD_CONFIGURED == STD_ON) */
    }
    #if ((CAN_RSCAN_CONFIGURED == STD_ON) && (CAN_RSCANFD_CONFIGURED == STD_ON))
    else
    #endif
    {
      #if (CAN_RSCAN_CONFIGURED == STD_ON)
      LulFDSts = 0UL;
      LulIDRegValue = Can_GaaRegs[LucUnit].pCmn->aaRFReg[LpHoh->usBufferIndex].ulRFID;
      LulMessageDlc = Can_GaaRegs[LucUnit].pCmn->aaRFReg[LpHoh->usBufferIndex].ulRFPTR;
      LpDataReg = &Can_GaaRegs[LucUnit].pCmn->aaRFReg[LpHoh->usBufferIndex].aaRFDF[0];
      LulMessageDlc = CAN_RSCAN_XXDLC_GET(LulMessageDlc);
      /* Truncate 1xxxb to 1000b */
      if ((uint32)CAN_STD_MAX_PAYLOAD < LulMessageDlc)
      {
        LulMessageDlc = CAN_STD_MAX_PAYLOAD;
      } /* else No action required */
      LulAvailableDlc = LulMessageDlc;
      #endif /* (CAN_RSCAN_CONFIGURED == STD_ON) */
    }

    /* Copy Data to memory from registers by 4 bytes */
    LulDlcWords = CAN_ALIGN_4(LulAvailableDlc) / (uint32)sizeof(uint32);                                                /* PRQA S 3469, 3383 # JV-01, JV-01 */
    for (LulWordIndex = 0U; LulWordIndex < LulDlcWords; LulWordIndex++)
    {
      LaaCanSdu[LulWordIndex] = LpDataReg[LulWordIndex];
    }

    /* Increment FIFO pointer */
    Can_GaaRegs[LucUnit].pCmn->aaRFPCTR[LpHoh->usBufferIndex] = CAN_RSCAN_CFPC_NEXT;

    /* Indicate to the upper layer */
    Can_RxIndicationCommonPart(LpHoh, LaaCanSdu, LulMessageDlc, LulIDRegValue, LulFDSts);
    LucCount++;
  } /* while (FIFO is not empty) */

  /* Clear interrupt request flag */
  if (1UL == (Can_GaaRegs[LucUnit].pCmn->aaRFSTS[LpHoh->usBufferIndex] & CAN_RSCAN_RFEMP))
  {
    Can_GaaRegs[LucUnit].pCmn->aaRFSTS[LpHoh->usBufferIndex] = (CAN_RSCAN_CLEAR_RFIF);
  } /* else No action required */
}
#endif /* (CAN_RX_FIFO == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Can_RxIndicationTxRxFIFO
**
** Service ID            : Not Applicable
**
** Description           : This function reads a TxRxFIFO and
**                         notifies the upper layer about receive indication.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LpHoh   : Pointer to HRH
**                         LucUnit : Module number of RSCANn
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : The availability of pointers must be guaranteed by
**                         the upper layer.
**
** Global Variables Used : Can_GaaRegs, Can_GaaPayloadFromDLCTable,
**                         Can_GaaPayloadFromPLSTable
**
** Functions Invoked     : Can_RxIndicationCommonPart, Det_ReportError, Det_ReportRuntimeError
**
** Registers Used        : (CFD)CFFDCSTS, (CFD)CFID, (CFD)CFPTR,
**                         (CFD)CFDF, (CFD)CFPCTR, (CFD)CFSTS
**
** Reference ID          : CAN_DUD_ACT_048
** Reference ID          : CAN_DUD_ACT_048_ERR001, CAN_DUD_ACT_048_REG001,
** Reference ID          : CAN_DUD_ACT_048_REG002, CAN_DUD_ACT_048_REG003
***********************************************************************************************************************/
#if (CAN_RX_COMFIFO == STD_ON)
STATIC FUNC(void, CAN_PRIVATE_CODE)
    Can_RxIndicationTxRxFIFO(CONSTP2CONST(Can_HohConfigType, AUTOMATIC, CAN_PRIVATE_CONST) LpHoh,
                             CONST(uint8, AUTOMATIC) LucUnit)
{
  P2VAR(volatile uint32, AUTOMATIC, REGSPACE) LpDataReg;                                                                /* PRQA S 3678 # JV-01 */
  VAR(uint32, AUTOMATIC) LulMessageDlc;
  VAR(uint32, AUTOMATIC) LulAvailableDlc;
  /* To optimize data copy operation, declare data array with uint32 */
  VAR(uint32, CAN_VAR_NO_INIT) LaaCanSdu[CAN_LOCALBUFFER_SIZE_32];
  VAR(uint32, AUTOMATIC) LulFDSts;
  VAR(uint32, AUTOMATIC) LulIDRegValue;
  VAR(uint32, AUTOMATIC) LulWordIndex;
  VAR(uint32, AUTOMATIC) LulDlcWords;
  VAR(uint8, AUTOMATIC) LucCFDCValue;
  VAR(uint8, AUTOMATIC) LucFifoBufferDepth;
  VAR(uint8, AUTOMATIC) LucCount;

  /* Get Receive FIFO Buffer Depth Configuration value */
  LucCFDCValue = (uint8)CAN_RSCAN_CFDC_GET(LpHoh->ulXXCCRegValue);                                                      /* PRQA S 3469 # JV-01 */

  /* Get FIFO Buffer Depth value */
  LucFifoBufferDepth = (uint8)CAN_RSCAN_FIFO_BUFFER_DEPTH_GET(LucCFDCValue);
  LucCount = 0U;
  /* Read TxRxFIFO until the FIFO becomes empty */
  while ((0UL == (Can_GaaRegs[LucUnit].pCmn->aaCFSTS[LpHoh->usBufferIndex] & CAN_RSCAN_CFEMP)) &&
         (LucCount < LucFifoBufferDepth))
  {
    #if ((CAN_DEV_ERROR_DETECT == STD_ON) || (CAN_AR_VERSION == CAN_AR_431_VERSION) || \
         (CAN_AR_VERSION == CAN_AR_R22_11_VERSION))
    /* Check lost message */
    if (CAN_FIFO_MSG_LOST_MASK == ((Can_GaaRegs[LucUnit].pCmn->aaCFSTS[LpHoh->usBufferIndex])
                                   & CAN_FIFO_MSG_LOST_MASK))
    {
      /* Clear transmit/receive FIFO message lost flag */
      Can_GaaRegs[LucUnit].pCmn->aaCFSTS[LpHoh->usBufferIndex] = (CAN_RSCAN_CLEAR_CFMLT);
      #if (CAN_AR_VERSION == CAN_AR_422_VERSION)
      /* Report to DET default error*/
      (void)Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_RXPROCESSING_SID, CAN_E_DATALOST);
      #elif ((CAN_AR_VERSION == CAN_AR_431_VERSION) || (CAN_AR_VERSION == CAN_AR_R22_11_VERSION))
      /* Report to DET runtime error*/
      (void)Det_ReportRuntimeError(CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_RXPROCESSING_SID, CAN_E_DATALOST);
      #endif
    } /* else No action required */
    #endif /* ((CAN_DEV_ERROR_DETECT == STD_ON) || (CAN_AR_VERSION == CAN_AR_431_VERSION)) */

    #if ((CAN_RSCAN_CONFIGURED == STD_ON) && (CAN_RSCANFD_CONFIGURED == STD_ON))
    if (CAN_MACRO_RSCANFD == Can_GaaRegs[LucUnit].enMacroType)
    #endif
    {
    #if (CAN_RSCANFD_CONFIGURED == STD_ON)
      /* Get status and data register address accroding to each buffer mode */
      LulFDSts = Can_GaaRegs[LucUnit].pFD->aaCFReg[LpHoh->usBufferIndex].ulFDCSTS;
      LulIDRegValue = Can_GaaRegs[LucUnit].pFD->aaCFReg[LpHoh->usBufferIndex].ulFDCFID;
      LulMessageDlc = Can_GaaRegs[LucUnit].pFD->aaCFReg[LpHoh->usBufferIndex].ulFDCFPTR;
      LpDataReg = &Can_GaaRegs[LucUnit].pFD->aaCFReg[LpHoh->usBufferIndex].aaFDCFDF[0];

      /* Convert DLC value to actual byte length */
      LulMessageDlc = (uint32)Can_GaaPayloadFromDLCTable[CAN_RSCAN_XXDLC_GET(LulMessageDlc)];
      /* Read registers as the smaller one of message DLC or buffer DLC */
      LulAvailableDlc = Can_GaaPayloadFromPLSTable[CAN_RSCAN_CFPLS_GET(LpHoh->ulXXCCRegValue)];                         /* PRQA S 3469 # JV-01 */
      if (LulAvailableDlc > LulMessageDlc)
      {
        LulAvailableDlc = LulMessageDlc;
      } /* else No action required */
    #endif /* (CAN_RSCANFD_CONFIGURED == STD_ON) */
    }
    #if ((CAN_RSCAN_CONFIGURED == STD_ON) && (CAN_RSCANFD_CONFIGURED == STD_ON))
    else
    #endif
    {
      #if (CAN_RSCAN_CONFIGURED == STD_ON)
      LulFDSts = 0UL;
      LulIDRegValue = Can_GaaRegs[LucUnit].pCmn->aaCFReg[LpHoh->usBufferIndex].ulCFID;
      LulMessageDlc = Can_GaaRegs[LucUnit].pCmn->aaCFReg[LpHoh->usBufferIndex].ulCFPTR;
      LpDataReg = &Can_GaaRegs[LucUnit].pCmn->aaCFReg[LpHoh->usBufferIndex].aaCFDF[0];
      LulMessageDlc = CAN_RSCAN_XXDLC_GET(LulMessageDlc);
      /* Truncate 1xxxb to 1000b */
      if ((uint32)CAN_STD_MAX_PAYLOAD < LulMessageDlc)
      {
        LulMessageDlc = CAN_STD_MAX_PAYLOAD;
      } /* else No action required */
      LulAvailableDlc = LulMessageDlc;
      #endif /* (CAN_RSCAN_CONFIGURED == STD_ON) */
    }

    /* Copy Data to memory from registers by 4 bytes */
    LulDlcWords = CAN_ALIGN_4(LulAvailableDlc) / (uint32)sizeof(uint32);                                                /* PRQA S 3383, 3469 # JV-01, JV-01 */
    for (LulWordIndex = 0U; LulWordIndex < LulDlcWords; LulWordIndex++)
    {
      LaaCanSdu[LulWordIndex] = LpDataReg[LulWordIndex];
    }

    /* Increment FIFO pointer */
    Can_GaaRegs[LucUnit].pCmn->aaCFPCTR[LpHoh->usBufferIndex] = CAN_RSCAN_CFPC_NEXT;

    /* Indicate to the uppder layer */
    Can_RxIndicationCommonPart(LpHoh, LaaCanSdu, LulMessageDlc, LulIDRegValue, LulFDSts);
    LucCount++;
  } /* while (FIFO is not empty) */

  /* Clear interrupt request flag */
  if (1UL == (Can_GaaRegs[LucUnit].pCmn->aaCFSTS[LpHoh->usBufferIndex] & CAN_RSCAN_CFEMP))
  {
    Can_GaaRegs[LucUnit].pCmn->aaCFSTS[LpHoh->usBufferIndex] = (CAN_RSCAN_CLEAR_CFRXIF);
  } /* else No action required */
}
#endif /* (CAN_RX_COMFIFO == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Can_RxIndicationRxBuffer
**
** Service ID            : Not Applicable
**
** Description           : This function reads a RxBuffer and
**                         notifies the upper layer about receive indication.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LpHoh   : Pointer to HRH
**                         LucUnit : Module number of RSCANn
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : The availability of the index must be guaranteed by
**                         the upper layer.
**
** Global Variables Used : Can_GaaRegs, Can_GpConfig,
**                         Can_GaaPayloadFromDLCTable,
**                         Can_GaaPayloadFromPLSTable
**
** Functions Invoked     : Can_RxIndicationCommonPart()
**
** Registers Used        : (CFD)RMIDq, (CFD)RMPTRq, (CFD)RMDFq,
**                         (CFD)RMFDSTSq
**
** Reference ID          : CAN_DUD_ACT_049
** Reference ID          : CAN_DUD_ACT_049_REG001
***********************************************************************************************************************/
#if (CAN_RX_BUFFER == STD_ON)
STATIC FUNC(void, CAN_PRIVATE_CODE)
    Can_RxIndicationRxBuffer(CONSTP2CONST(Can_HohConfigType, AUTOMATIC, CAN_PRIVATE_CONST) LpHoh,
                             CONST(uint8, AUTOMATIC) LucUnit)
{
  P2VAR(volatile uint32, AUTOMATIC, REGSPACE) LpDataReg;                                                                /* PRQA S 3678 # JV-01 */
  P2CONST(Can_HWUnitInfoType, AUTOMATIC, CAN_CONFIG_DATA) LpHWInfo;
  /* To optimize data copy operation, declare data array with uint32 */
  VAR(uint32, CAN_VAR_NO_INIT) LaaCanSdu[CAN_LOCALBUFFER_SIZE_32];
  VAR(uint32, AUTOMATIC) LulMessageDlc;
  VAR(uint32, AUTOMATIC) LulAvailableDlc;
  VAR(uint32, AUTOMATIC) LulFDSts;
  VAR(uint32, AUTOMATIC) LulIDRegValue;
  VAR(uint32, AUTOMATIC) LulWordIndex;
  VAR(uint32, AUTOMATIC) LulDlcWords;
  VAR(uint32, AUTOMATIC) LulRMNDIndex;
  VAR(uint32, AUTOMATIC) LulRMNDMask;
  VAR(uint32, AUTOMATIC) LulRetryCount;
  VAR(boolean, AUTOMATIC) LblReceiveOK;

  /* The retry operation is required for RxBuffer
     because it can be overwriten when new message arives while reading */
  LblReceiveOK = CAN_FALSE;
  for (LulRetryCount = 0U; ((CAN_RECBUFFER_RETRY_COUNT >= LulRetryCount) && (CAN_FALSE == LblReceiveOK));
                                                                                                      LulRetryCount++)
  {
    /* Clear RMNSq bit */
    LulRMNDIndex = CAN_RSCAN_RMND_GET_INDEX(LpHoh->usBufferIndex);
    LulRMNDMask = CAN_RSCAN_RMND_GET_BITMASK(LpHoh->usBufferIndex);
    Can_GaaRegs[LucUnit].pCmn->aaRMND[LulRMNDIndex] = ~LulRMNDMask;

    #if ((CAN_RSCAN_CONFIGURED == STD_ON) && (CAN_RSCANFD_CONFIGURED == STD_ON))
    if (CAN_MACRO_RSCANFD == Can_GaaRegs[LucUnit].enMacroType)
    #endif
    {
      #if (CAN_RSCANFD_CONFIGURED == STD_ON)
      /* Get status and data register address accroding to each buffer mode */
      LulFDSts = Can_GaaRegs[LucUnit].pFD->aaHrhReg[LpHoh->usBufferIndex].ulFDRMFDSTS;
      LulIDRegValue = Can_GaaRegs[LucUnit].pFD->aaHrhReg[LpHoh->usBufferIndex].ulFDRMID;
      LulMessageDlc = Can_GaaRegs[LucUnit].pFD->aaHrhReg[LpHoh->usBufferIndex].ulFDRMPTR;
      LpDataReg = &Can_GaaRegs[LucUnit].pFD->aaHrhReg[LpHoh->usBufferIndex].aaFDRMDF[0];
      LpHWInfo = (P2CONST(Can_HWUnitInfoType, AUTOMATIC, CAN_CONFIG_DATA))Can_GpConfig->pHWUnitInfo;                    /* PRQA S 0316 # JV-01 */
      LpHWInfo = &LpHWInfo[LucUnit];

      /* Convert DLC value to actual byte length */
      LulMessageDlc = (uint32)Can_GaaPayloadFromDLCTable[CAN_RSCAN_XXDLC_GET(LulMessageDlc)];
      /* Read registers as the smaller one of message DLC or buffer DLC */
      LulAvailableDlc = Can_GaaPayloadFromPLSTable[CAN_RSCAN_RMPLS_GET(LpHWInfo->ulRMNB)];                              /* PRQA S 3469 # JV-01 */
      if (LulAvailableDlc > LulMessageDlc)
      {
        LulAvailableDlc = LulMessageDlc;
      } /* else No action required */
      #endif /* (CAN_RSCANFD_CONFIGURED == STD_ON) */
    }
    #if ((CAN_RSCAN_CONFIGURED == STD_ON) && (CAN_RSCANFD_CONFIGURED == STD_ON))
    else
    #endif
    {
      #if (CAN_RSCAN_CONFIGURED == STD_ON)
      LulFDSts = 0UL;
      LulIDRegValue = Can_GaaRegs[LucUnit].pCmn->aaHrhReg[LpHoh->usBufferIndex].ulRMID;
      LulMessageDlc = Can_GaaRegs[LucUnit].pCmn->aaHrhReg[LpHoh->usBufferIndex].ulRMPTR;
      LpDataReg = &Can_GaaRegs[LucUnit].pCmn->aaHrhReg[LpHoh->usBufferIndex].aaRMDF[0];
      /* Read registers as the smaller one of message DLC or buffer DLC */
      LulMessageDlc = CAN_RSCAN_XXDLC_GET(LulMessageDlc);
      LulAvailableDlc = CAN_STD_MAX_PAYLOAD;
      if (LulAvailableDlc > LulMessageDlc)
      {
        LulAvailableDlc = LulMessageDlc;
      } /* else No action required */
      #endif /* (CAN_RSCAN_CONFIGURED == STD_ON) */
    }

    /* Copy Data to memory from registers by 4 bytes */
    LulDlcWords = CAN_ALIGN_4(LulAvailableDlc) / (uint32)sizeof(uint32);                                                /* PRQA S 3383, 3469 # JV-01, JV-01 */
    for (LulWordIndex = 0U; LulWordIndex < LulDlcWords; LulWordIndex++)
    {
      LaaCanSdu[LulWordIndex] = LpDataReg[LulWordIndex];
    }

    /* If RMNSq bit is set, it means new message arrived while reading buffer */
    if (0UL != (Can_GaaRegs[LucUnit].pCmn->aaRMND[LulRMNDIndex] & LulRMNDMask))
    {
      /* The buffer has been updated, retry */
    }
    else
    {
      /* Indicate the upper layer */
      Can_RxIndicationCommonPart(LpHoh, LaaCanSdu, LulMessageDlc, LulIDRegValue, LulFDSts);
      /* Finish loop */
      LblReceiveOK = CAN_TRUE;
    }
  }
}
#endif /* (CAN_RX_BUFFER == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Can_RxIndicationCommonPart
**
** Service ID            : Not Applicable
**
** Description           : This function notifies the upper layer of
**                         the received message.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LpHoh         : Pointer to HRH
**                         LaaCanSdu     : SDU buffer
**                         LulDlc        : Data Length
**                         LulIdRegValue : Receive Message ID
**                         LulFDSts      : Value of xFDSTS register
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : The availability of pointers must be guaranteed by
**                         the upper layer.
**
** Global Variables Used : None
**
** Functions Invoked     : CanIf_RxIndication
**
** Registers Used        : None
**
** Reference ID          : CAN_DUD_ACT_050
***********************************************************************************************************************/
#if ((CAN_RX_OBJECT == STD_ON) && ((CAN_RX_BUFFER == STD_ON) || (CAN_RX_FIFO == STD_ON) || (CAN_RX_COMFIFO == STD_ON)))
STATIC FUNC(void, CAN_PRIVATE_CODE)
    Can_RxIndicationCommonPart(CONSTP2CONST(Can_HohConfigType, AUTOMATIC, CAN_PRIVATE_CONST) LpHoh,
                               VAR(uint32, AUTOMATIC) LaaCanSdu[], CONST(uint32, AUTOMATIC) LulDlc,
                               CONST(uint32, AUTOMATIC) LulIDRegValue, CONST(uint32, AUTOMATIC) LulFDSts)
{
  Can_HwType LstMailbox;
  PduInfoType LstPduInfo;
  #if defined(CAN_LPDU_RECEIVE_CALLOUT_FUNCTION) || (CAN_AR_VERSION == CAN_AR_R22_11_VERSION)
  boolean LblCalloutOK;
  LblCalloutOK = CAN_TRUE;
  #endif

  /* If this is CANFD message, set FD flag */
  #if (CAN_RSCANFD_CONFIGURED == STD_ON)
  if (0UL != (LulFDSts & CAN_RSCAN_XXFDF))
  {
    LstMailbox.CanId = CAN_FD_FRAME_FORMAT;
  }
  else
  #endif
  {
    LstMailbox.CanId = 0U;
  }

  /* Extracting extended can id and storing it */
  if (0UL != (LulIDRegValue & CAN_RSCAN_IDE))
  {
    LstMailbox.CanId =
        LstMailbox.CanId | (Can_IdType)((LulIDRegValue & (uint32)CAN_ID_TYPE_IDMASK) | (uint32)CAN_EXTENDED_FORMAT);
  }
  else
  {
    LstMailbox.CanId = LstMailbox.CanId | (Can_IdType)(LulIDRegValue & (uint32)CAN_ID_TYPE_IDMASK);
  }

  /* This is the second redundant path function provided for legacy
   * safety relevant ECUs */
  /* CanObjectId is uint16 but 1st param of call-out func is uint8. */
  #if (CAN_AR_VERSION == CAN_AR_R22_11_VERSION)
  if(NULL_PTR != Can_GpConfig->pLpduCalloutReceiveFunction)                                                             /* PRQA S 3416 # JV-01 */
  {
    LblCalloutOK = Can_GpConfig->pLpduCalloutReceiveFunction(LpHoh->usHohId,
      LstMailbox.CanId, (uint8)LulDlc, (P2CONST(uint8, AUTOMATIC, CAN_CONFIG_DATA))LaaCanSdu);                          /* PRQA S 0751 # JV-01 */
  }/* Else no action required */
  #else
  #if defined(CAN_LPDU_RECEIVE_CALLOUT_FUNCTION) 
  LblCalloutOK = CAN_LPDU_RECEIVE_CALLOUT_FUNCTION(LpHoh->usHohId,
      LstMailbox.CanId, (uint8)LulDlc, (P2CONST(uint8, AUTOMATIC, CAN_CONFIG_DATA))LaaCanSdu);
  #endif
  #endif
  #if defined(CAN_LPDU_RECEIVE_CALLOUT_FUNCTION) || (CAN_AR_VERSION == CAN_AR_R22_11_VERSION)
  if (CAN_FALSE == LblCalloutOK)
  {
    /* If callout function returns false, nothing to do */
  }
  else
  #endif
  {
    LstMailbox.Hoh = (Can_HwHandleType)LpHoh->usHohId;
    LstMailbox.ControllerId = (uint8)(LpHoh->ucController + CAN_CONTROLLER_OFFSET);                                     /* PRQA S 3383, 2985 # JV-01, JV-01 */
    LstPduInfo.SduDataPtr = (P2VAR(uint8, AUTOMATIC, CAN_CONFIG_DATA))LaaCanSdu;                                        /* PRQA S 0751, 3432 # JV-01, JV-01 */
    LstPduInfo.SduLength = (PduLengthType)LulDlc;

    /* Invoke CanIf_RxIndication call-back function to give
    receive indication */
    CanIf_RxIndication(&LstMailbox, &LstPduInfo);                                                                       /* PRQA S 2976 # JV-01 */
  } /* (CAN_FALSE == LbCalloutOK) */
}
#endif /* (CAN_RX_OBJECT == STD_ON) */

#if (CAN_CANXL_SUPPORTED == STD_ON)
/***********************************************************************************************************************
** Function Name         : CanXL_RxProcessing
**
** Service ID            : Not Applicable
**
** Description           : This function notifies the upper layer about receive
**                         indication.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LulBufferBits : Target buffer to be read
**                         LulMode       : Interrupt or polling or both
**                         LulIndex      : Index of MainFunction configuration
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : The availability of pointers must be guaranteed by
**                         the upper layer.
**
** Global Variables Used : CanXL_GaaRegs, Can_GpConfig,
**                         CanXL_GpHohConfig, Can_GpPCController, CanXL_GaaCtrlStat
**
** Functions Invoked     : CanXL_RxIndication
**
** Registers Used        : (CFD)FESTS
**
** Reference ID          : CAN_DUD_ACT_075
** Reference ID          : CAN_DUD_ACT_075_GBL001, CAN_DUD_ACT_075_GBL002
** Reference ID          : CAN_DUD_ACT_075_GBL003, CAN_DUD_ACT_075_GBL004
** Reference ID          : CAN_DUD_ACT_075_GBL005, CAN_DUD_ACT_075_REG001
** Reference ID          : CAN_DUD_ACT_075_REG002, CAN_DUD_ACT_075_REG003
** Reference ID          : CAN_DUD_ACT_075_REG004
***********************************************************************************************************************/
FUNC(void, CAN_PRIVATE_CODE) CanXL_RxProcessing(const uint8 LucController, const uint32 LulMode, const uint32 LulIndex) /* PRQA S 1505, 3006 # JV-01, JV-01 */
{    
  P2VAR(Can_RxDescriptorsType, AUTOMATIC, CAN_CONFIG_DATA) LpCurrentDec;                                                /* PRQA S 3432 # JV-01 */
  P2VAR(Can_RxDescriptorsType, AUTOMATIC, CAN_CONFIG_DATA) LpCheckDec;                                                  /* PRQA S 3432 # JV-01 */
  P2CONST(Can_ControllerPCConfigType, AUTOMATIC, CAN_CONFIG_DATA) LpPCController;
  P2CONST(Can_HohConfigType, AUTOMATIC, CAN_CONFIG_DATA) LpHoh;
  VAR(uint32, AUTOMATIC) LucControllerId;
  VAR(uint32, AUTOMATIC) LucCtrlInfoIndex;
  VAR(uint32, AUTOMATIC) LulQueueIndex;
  #if (CANFD_ON_XL_BUS_SUPPORT == STD_ON)
  VAR(uint16, AUTOMATIC) LusHohIndex;
  VAR(uint16, AUTOMATIC) LusMaxHohIndex;
  #endif
  VAR(uint16, AUTOMATIC) LusXLHohIndex;
  VAR(uint16, AUTOMATIC) LusMaxXLHohIndex;
  
  #if (CANFD_ON_XL_BUS_SUPPORT == STD_ON)
  LusHohIndex = 0U;
  LusMaxHohIndex = Can_GpConfig->usNoOfHohs;
  #endif
  LusXLHohIndex = 0U;
  LusMaxXLHohIndex = Can_GpConfig->usCanXLNoOfHohs;
  #if !((CAN_RX_POLLING == STD_ON) && (CAN_NUMBER_OF_MAINFUNCTIONS > 1U))
  /* Unused Parameters */
  (void)LulIndex;
  #endif

  while ((LusXLHohIndex < LusMaxXLHohIndex)
        #if (CANFD_ON_XL_BUS_SUPPORT == STD_ON)
        || (LusHohIndex < LusMaxHohIndex)
        #endif
        )
  {
    if(LusXLHohIndex < LusMaxXLHohIndex)                                                                                /* PRQA S 2991, 2995 # JV-01, JV-01 */
    {
      LpHoh = &CanXL_GpHohConfig[LusXLHohIndex];
      LusXLHohIndex++;
    }
    #if (CANFD_ON_XL_BUS_SUPPORT == STD_ON)
    else
    {
      LpHoh = &Can_GpHohConfig[LusHohIndex];
      LusHohIndex++;
    }
    #endif
    /* Get the CanXL Hoh config and polling/interrupt information */
    LpPCController = &Can_GpPCController[(LpHoh->ucController)];
    if ((CAN_HOH_HRH == LpHoh->enHoh) && (CANXL_QUEUETYPE_RXFIFO == LpHoh->enBufferType) &&
    #if ((CAN_RX_POLLING == STD_ON) && (CAN_NUMBER_OF_MAINFUNCTIONS > 1U))
        (LulIndex == (uint32)LpHoh->ucMainFunctionRIndex) &&
    #endif
          /* Checking if controller RxProcessing */
          (((LulMode & (uint32)CAN_CHECK_INT_RX) == ((uint32)LpPCController->ucIntEnable & (uint32)CAN_CHECK_INT_RX))
         /*
          * Check CanXL_RxProcessing is called by MainFunction and
          * CanHardwareObjectUsesPolling is true
          * Or CanXL_RxProcessing is called by ISR and
          * CanHardwareObjectUsesPolling is false
          */
          #if ((CAN_AR_VERSION == CAN_AR_431_VERSION) || (CAN_AR_VERSION == CAN_AR_R22_11_VERSION))
          || ((((uint32)CAN_INT_DISABLED == LulMode) && (CAN_TRUE == LpHoh->blObjectUsesPolling)) ||
            (((uint32)CAN_CHECK_INT_RX == LulMode) && (CAN_FALSE == LpHoh->blObjectUsesPolling)))
          #endif
          ) && (((CAN_CHECK_INT_RX == LulMode) && (LucController == LpHoh->ucController))
               || ((CAN_INT_DISABLED == LulMode)
              #if (CAN_MULTI_CORE_SUPPORT == STD_ON)
              && (LpHoh->ucController == LucController)
              #endif
        )))
     {
      /* Get the RX FIFO queue configuration and current status */
      LulQueueIndex = LpHoh->usBufferIndex;
      LucControllerId = LpPCController->ucCh;
      LucCtrlInfoIndex = Can_GpConfig->pCanXLSecondPhysicalControllerToIndex[LucControllerId];
      if (0UL != (CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulRXFQINSTS & (1UL << LulQueueIndex)))
      {
        /* Clear interrupt */
        CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulRXFQINSTS &= (1UL << (LulQueueIndex));
        /* Get start point of descriptor list for this polling time which has been saved from the previous polling */
        LpCheckDec = CanXL_GaaCtrlStat[LucCtrlInfoIndex].stHwStatNonSDT5.aaHeadRxDesc[LulQueueIndex];
        
        if(CAN_COMMON_STATE_STARTED == Can_GaaCtrlState[LpHoh->ucController].enMode)
        {
          LpCurrentDec = 
                    (Can_RxDescriptorsType *)(CanXL_GaaRegs[LucCtrlInfoIndex].pMH->aaRXFQReg[LulQueueIndex].ulRXADDPT); /* PRQA S 0306 # JV-01 */
        }
        else
        {
          LpCurrentDec = LpCheckDec;
        }
        /* Loop all descriptor from starting point descriptor to the current descriptor of this RX FIFO queue */
        do
        {
          /* Check if the head descriptor is valid */
          if(0UL != ((LpCheckDec->ulElement0) & CANXL_RX_BIT_VALID(0x01U)))                                             /* PRQA S 3469 # JV-01 */
          {
            /* Call internal function to handle data and inform to CanIf */
            CanXL_RxIndication(LpHoh, LpCheckDec);
          }
          /* Check if checked descriptor is the last one of this RX FIFO queue */
          if(LpCheckDec != CanXL_GaaCtrlStat[LucCtrlInfoIndex].stHwStatFixed.aaLastRxDesc[LulQueueIndex])
          {
            /* Move to the next descriptor if it does not reach the last one yet */
            LpCheckDec++;
          }
          else
          {
            /* Wrap back to the first descriptor of this RX FIFO queue if it reaches the last one already */
            LpCheckDec = CanXL_GaaCtrlStat[LucCtrlInfoIndex].stHwStatFixed.aaFirstRxDesc[LulQueueIndex];
          }
        } while(LpCheckDec != LpCurrentDec);
        CanXL_GaaCtrlStat[LucCtrlInfoIndex].stHwStatNonSDT5.aaHeadRxDesc[LulQueueIndex] = LpCurrentDec;
      }
      /* Check if Rx FIFO Queue is on-hold or not */
      if (0UL != (CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulRXFQSTS1 & (1UL << LulQueueIndex)))
      {
        /* Report to DET runtime error*/
        (void)Det_ReportRuntimeError(CANXL_MODULE_ID, CANXL_INSTANCE_ID, CANXL_RXPROCESSING_SID, CAN_E_DATALOST);
        RH850_SET_IOREG_SYNCP(32, &CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulRXFQCTRL0, (1UL << LulQueueIndex));           /* PRQA S 3464, 1006 # JV-01, JV-01 */
      } /* else no action required */
    }
  }
}
#endif /* #if (CAN_CANXL_SUPPORTED == STD_ON)*/

#if (CAN_CANXL_SUPPORTED == STD_ON)
/***********************************************************************************************************************
** Function Name         : CanXL_RxIndication
**
** Service ID            : Not Applicable
**
** Description           : This function notifies the upper layer about receive
**                         indication.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LulBufferBits : Target buffer to be read
**                         LulMode       : Interrupt or polling or both
**                         LulIndex      : Index of MainFunction configuration
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : The availability of pointers must be guaranteed by
**                         the upper layer.
**
** Global Variables Used : CanXL_GaaRegs, Can_GpConfig,
**                         Can_GpPCController
**
** Functions Invoked     : Can_RxIndicationRxFIFO, CanXL_ConsistentCheck
**
** Registers Used        : (CFD)FESTS
**
** Reference ID          : CAN_DUD_ACT_076
** Reference ID          : CAN_DUD_ACT_076_GBL001, CAN_DUD_ACT_076_GBL002,
** Reference ID          : CAN_DUD_ACT_076_GBL003, CAN_DUD_ACT_076_ERR001,
** Reference ID          : CAN_DUD_ACT_076_REG001, CAN_DUD_ACT_076_REG002
***********************************************************************************************************************/
STATIC FUNC(void, CAN_PRIVATE_CODE) CanXL_RxIndication(
                                                  P2CONST(Can_HohConfigType, AUTOMATIC, CAN_PRIVATE_CONST) LpHoh,
                                                  P2VAR(Can_RxDescriptorsType, AUTOMATIC, CAN_CONFIG_DATA) Descriptor)  /* PRQA S 3432 # JV-01 */
{
  CanXL_HwType XlMailbox;
  #if (CANFD_ON_XL_BUS_SUPPORT == STD_ON)
  boolean LblCalloutOK;
  Can_HwType Mailbox;
  #endif
  PduInfoType PduInfoPtr;
  CanXL_Params XLParamsInfo;
  P2VAR(uint32, AUTOMATIC, CAN_CONFIG_DATA) LpDCAddress;                                                                /* PRQA S 3432, 3678 # JV-01, JV-01 */
  VAR(Std_ReturnType, AUTOMATIC) LenResult;
  VAR(uint32, AUTOMATIC) LulQueueIndex;
  VAR(uint32, AUTOMATIC) LucControllerId;
  VAR(uint32, AUTOMATIC) LucCtrlInfoIndex;
  VAR(uint32, CAN_VAR_NO_INIT) LaaCanSdu[CANXL_MAX_PAYLOAD / sizeof(uint32)];
  VAR(uint32, AUTOMATIC) LulR0;
  VAR(uint32, AUTOMATIC) LulR1;
  VAR(uint32, AUTOMATIC) LulR2;
  VAR(uint32, AUTOMATIC) LulDLC;
  VAR(uint8, AUTOMATIC)  LucSDT;

  /* Get the RX FIFO queue configuration */
  LenResult = E_NOT_OK;
  LucControllerId = Can_GpPCController[LpHoh->ucController].ucCh;
  LulQueueIndex = LpHoh->usBufferIndex;
  LucCtrlInfoIndex = Can_GpConfig->pCanXLSecondPhysicalControllerToIndex[LucControllerId];

  /* Get the data container address and fetch Rx element of this message */
  LpDCAddress = (uint32 *)(Descriptor->ulElement1);                                                                     /* PRQA S 0306 # JV-01 */
  LulR0 = *(LpDCAddress);
  LulR1 = *(LpDCAddress + 1UL);                                                                                         /* PRQA S 0489 # JV-01 */
  LucSDT = (uint8)(CANXL_RX_BIT_SDT(LulR0) & 0xFFUL);                                                                   /* PRQA S 3469, 2985 # JV-01, JV-01 */
  /* Check SduType and format of Rx frame */
  if((LucSDT != 5U) && ((LulR0 & CANXL_BIT_XLF) != 0UL))
  {
    LenResult = CanXL_ConsistentCheck
          ((uint8)LucCtrlInfoIndex, (P2CONST(volatile uint32, AUTOMATIC, CAN_APPL_DATA))(LpDCAddress), LucSDT);
    if(E_NOT_OK == LenResult)
    {
      #if (CAN_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportRuntimeError(CANXL_MODULE_ID, CANXL_INSTANCE_ID, CANXL_RXPROCESSING_SID, CANXL_E_INV_DATA);
      #endif   
    }
    else
    {
      LulDLC = (CANXL_RX_BIT_DLCXL(LulR1) & 0x7FFUL) + 1UL;                                                             /* PRQA S 3469, 3383 # JV-01, JV-01 */
      LulR2 = *(LpDCAddress + 2UL);                                                                                     /* PRQA S 0488 # JV-01 */
      /* Update Mailbox */
      XlMailbox.Hoh = (Can_HwHandleType)LpHoh->usHohId;
      XlMailbox.ControllerId = (uint8)LpHoh->ucController;
      XlMailbox.XLParams = &XLParamsInfo;
      /* Update XLParamsInfo */
      XLParamsInfo.PriorityId = (uint16)(CANXL_RX_BIT_PRIO(LulR0) & 0x7FFUL);                                           /* PRQA S 3469 # JV-01 */
      XLParamsInfo.Vcid = (uint16)(CANXL_RX_BIT_VCID(LulR0) & 0xFUL);                                                   /* PRQA S 3469 # JV-01 */
      XLParamsInfo.SduType = LucSDT;
      XLParamsInfo.AcceptanceField = (uint32)LulR2;
      XLParamsInfo.Sec = (uint8)(CANXL_RX_BIT_SEC(LulR0) & 0x1UL);                                                      /* PRQA S 3469 # JV-01 */  
    }
  }
  #if (CANFD_ON_XL_BUS_SUPPORT == STD_ON)
  else if ((LulR0 & CANXL_BIT_XLF) == 0UL)
  {
    LenResult = E_OK;
    if (0UL != (uint32)(LulR0 & CANFD_BIT_XTD(1UL)))                                                                    /* PRQA S 3469 # JV-01 */
    {
      Mailbox.CanId = (Can_IdType)((LulR0 & (uint32)CAN_ID_TYPE_IDMASK) | (uint32)CAN_EXTENDED_FORMAT);
    }
    else
    {
      Mailbox.CanId = (Can_IdType)(LulR0 & (uint32)CAN_ID_TYPE_IDMASK) >> CAN_FD_BASEID_OFFSET;
    }
    if (0UL != (uint32)(LulR0 & CANFD_BIT_FDF(1UL)))                                                                    /* PRQA S 3469 # JV-01 */
    {
      Mailbox.CanId |= (uint32)(CAN_FD_FRAME_FORMAT);
    }
    Mailbox.Hoh = (Can_HwHandleType)LpHoh->usHohId;
    Mailbox.ControllerId = (uint8)(LpHoh->ucController + CAN_CONTROLLER_OFFSET);                                        /* PRQA S 2985 # JV-01 */
    LulDLC = Can_GaaPayloadFromDLCTable[CANXL_RX_BIT_DLCXL(LulR1) & 0x0FUL];                                            /* PRQA S 3469 # JV-01 */
  }
  #endif
  else
  {
    /* Nothing else required */
  }

  if(E_OK == LenResult)
  {
    CanXL_WriteRxData((uint8)LucCtrlInfoIndex, LulQueueIndex, Descriptor, &LaaCanSdu[0]);
    /* Update the PduInfoPtr */
    PduInfoPtr.SduDataPtr = (P2VAR(uint8, AUTOMATIC, CAN_CONFIG_DATA))(LaaCanSdu);                                      /* PRQA S 0751, 3432 # JV-01, JV-01 */
    PduInfoPtr.SduLength = (uint16)(LulDLC);
    if((LulR0 & CANXL_BIT_XLF) != 0UL)                                                                                  /* PRQA S 2995, 2991 # JV-01, JV-01 */
    {
       /* Inform to CanIf_XLRxIndication */
      CanIf_XLRxIndication(&XlMailbox, &PduInfoPtr);                                                                    /* PRQA S 2976 # JV-01 */
    }
    else
    {
      #if (CANFD_ON_XL_BUS_SUPPORT == STD_ON)
      LblCalloutOK = CAN_TRUE;
      if(NULL_PTR != Can_GpConfig->pLpduCalloutReceiveFunction)                                                         /* PRQA S 3416 # JV-01 */
      {
        LblCalloutOK = Can_GpConfig->pLpduCalloutReceiveFunction(LpHoh->usHohId,
          Mailbox.CanId, (uint8)LulDLC, (P2CONST(uint8, AUTOMATIC, CAN_CONFIG_DATA))(PduInfoPtr.SduDataPtr));
      }/* Else no action required */
      if (CAN_FALSE == LblCalloutOK)
      {
        /* If callout function returns false, nothing to do */
      }
      else
      {
        /* Inform to CanIf_RxIndication */
        CanIf_RxIndication(&Mailbox, &PduInfoPtr);
      }
      #endif
    }
  }
  else
  {
    /* Nothing else required */
  }
  /* Reset this descriptor for next reception times */
  Descriptor->ulElement0 &= ~(0xF000000FUL);
}
#endif /* #if (CAN_CANXL_SUPPORTED == STD_ON)*/

#define CAN_STOP_SEC_PRIVATE_CODE
#include "Can_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
