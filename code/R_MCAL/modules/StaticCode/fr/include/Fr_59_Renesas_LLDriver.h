/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Fr_59_Renesas_LLDriver.h                                                                            */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2019-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Provision of FlexRay Driver Module internal functions.                                                             */
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
 * 2.4.1:  30/06/2025    : Remove SW-VERSION in file header
 * 2.4.0:  30/06/2025    : Update SW-VERSION for RH850/U2Ax MCAL Ver22.01.00(D) Final Release
 * 2.3.2:  29/04/2025    : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 Release
 * 2.3.1:  31/03/2025    : Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02 Release
 *                         As part of QAC 11.6.0 support, following changes are made: 
 *                         1. Remove QAC comment of message 0778
 * 2.3.0:  28/02/2025    : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.1:  31/12/2024    : Update SW-VERSION for Ver22.00.01 U2Ax Release
 * 2.2.0:  31/12/2024    : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 * 2.1.3:  31/10/2024    : Update SW-VERSION to 2.1.3
 * 2.1.1:  30/08/2024    : As part of multicore support, following changes are made:
 *                         Add agrument uint8 LucCoreIndex to function Fr_59_Renesas_InitDone
 *                       : As part of QAC 10.3.0 support, following changes are made:
 *                         Remove redundant QAC message: 0791
 * 2.1.0:  24/02/2024    : Change SW-VERSION to 2.1.0
 * 2.0.0:  30/07/2023    : Add CWE rule into QAC header (0779, 0778 messages)
 *                       : Due to support AR2111, add extern for function: Fr_59_Renesas_GetSlotAssignment
 * 1.4.3:  09/05/2022    : Change SW-VERSION to 1.4.3
 * 1.3.3:  02/03/2022    : Change SW-VERSION to 1.4.2
 * 1.3.2:  13/08/2021    : Change SW-VERSION to 1.3.2
 * 1.3.1:  02/07/2021    : Add QAC message 9.5.0.
 *                         Format source code to 120 characters.
 *                         Improve Violation tag (remove START/END).
 *         28/04/2021    : + Added QAC message 0779.
 *                         + Update QAC comments to accept message 3432.
 *                         + Remove the following redundant function declaration.
 *                         Fr_59_Renesas_HaltAbsTimer
 *                         Fr_59_Renesas_GetWakeupStsFlag
 *                         Fr_59_Renesas_InputTransferEnabled
 *                         Fr_59_Renesas_SetWakeupReady
 *                         Fr_59_Renesas_CheckGetIndexAndPutIndex
 *                         Fr_59_Renesas_InputQueueRunRequest
 *                         Fr_59_Renesas_InputQueueHaltRequest
 *                         Fr_59_Renesas_OutputBufferCommandMask
 *                         Fr_59_Renesas_ReadFirstMessageBuffer
 *                         Fr_59_Renesas_InputQueueTableMax
 *                         Fr_59_Renesas_UserRequestPending
 *                         Fr_59_Renesas_ClearDAFlag
 *                         Fr_59_Renesas_InputTransferHalted
 *                         Fr_59_Renesas_InputTransferStatus
 *                         Fr_59_Renesas_InputQueueFull
 *                         Fr_59_Renesas_ResetAccessErrorReg
 *                         Fr_59_Renesas_IBFShadowTransferCompleted
 *                         Fr_59_Renesas_OutputTransferStatus
 *                         Fr_59_Renesas_ClearDataAvailableReg
 *                         Fr_59_Renesas_OutputBufferBusyShadow
 *                         Fr_59_Renesas_GetGTUConfiguration
 *                         Fr_59_Renesas_InterruptPending
 *                         Fr_59_Renesas_ResetStatusIntReg
 *                         Fr_59_Renesas_ResetAggregatedStatus
 *                         Fr_59_Renesas_WriteInputBufferCommand
 *                         Fr_59_Renesas_ClearTransmissionRequest
 *                         Fr_59_Renesas_OutputTransferEnabled
 * 1.3.0:  05/12/2020    : Remove QAC message 3210.
 * 1.2.0:  26/08/2020    : Release.
 * 1.1.0:  19/06/2020    : Release.
 *         28/07/2020    : Add QAC 9.3.1 comment.
 * 1.0.2:  29/05/2020    : Remove MISRA C Rule message (4:3447).
 *         21/05/2020    : Change return type of Fr_59_Renesas_UpdateDataTransferMode from
 *                         'void' to 'Std_ReturnType'.
 *         25/04/2020    : Remove argument definition using Compiler.h's macros.
 *         17/04/2020    : Update the header file including.
 * 1.0.1:  20/03/2020    : Update the declaration of Fr_59_Renesas_UpdateLPduTxSts and
 *                         Fr_59_Renesas_WriteOutputBufferCommand.
 * 1.0.0:  11/12/2019    : Initial Version.
 */
/**********************************************************************************************************************/

#ifndef FR_59_RENESAS_LLDRIVER_H
#define FR_59_RENESAS_LLDRIVER_H

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/

/* AUTOSAR Release version information */
#define FR_59_RENESAS_LLDRIVER_AR_RELEASE_MAJOR_VERSION    FR_59_RENESAS_AR_RELEASE_MAJOR_VERSION
#define FR_59_RENESAS_LLDRIVER_AR_RELEASE_MINOR_VERSION    FR_59_RENESAS_AR_RELEASE_MINOR_VERSION
#define FR_59_RENESAS_LLDRIVER_AR_RELEASE_REVISION_VERSION FR_59_RENESAS_AR_RELEASE_REVISION_VERSION

/*
 * File version information
 */
#define FR_59_RENESAS_LLDRIVER_SW_MAJOR_VERSION            FR_59_RENESAS_SW_MAJOR_VERSION
#define FR_59_RENESAS_LLDRIVER_SW_MINOR_VERSION            FR_59_RENESAS_SW_MINOR_VERSION

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (7:0779)    : Identifier does not differ from other identifier(s) (e.g. '%s') within the specified number  */
/*                       of significant characters.                                                                   */
/* Rule                : CERTCCM DCL23, DCL40, MSC15, MISRA C:2012 Rule-5.2, CWE Rule CWE-682, CWE-758, CWE-736       */
/* JV-01 Justification : Compiler will distinguish numerous characters, so this is accepted.                          */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0778)    : Identifier matches other identifier(s) (e.g. '%s') in first 31 characters - program does     */
/*                       not conform strictly to ISO:C90.                                                             */
/* Rule                : CERTCCM DCL23, DCL40, MISRA C:2012 Dir-1.1, CWE Rule CWE-736                                 */
/* JV-01 Justification : Compiler will distinguish numerous characters, so this is accepted.                          */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"

extern FUNC(Std_ReturnType, FR_PRIVATE_CODE) Fr_59_Renesas_CheckIfCCBusy(const uint8 Fr_CtrlIdx);
extern FUNC(Std_ReturnType, FR_PRIVATE_CODE)
    Fr_59_Renesas_LoadCfgLowLevelParameters(const uint8 Fr_CtrlIdx,
                                            const Fr_59_Renesas_LowLevelConfSetType *const pLowLevelCfgPtr);
extern FUNC(Std_ReturnType, FR_PRIVATE_CODE) Fr_59_Renesas_CfgBuffer(const uint8 Fr_CtrlIdx);
extern FUNC(Std_ReturnType, FR_PRIVATE_CODE)
    Fr_59_Renesas_CfgBufferHeader(const uint8 Fr_CtrlIdx, const uint16 usFrameHandle, const uint8 ucPayLoadLength);
extern FUNC(Std_ReturnType, FR_PRIVATE_CODE)
    Fr_59_Renesas_CheckCCConfig(const uint8 Fr_CtrlIdx,
                                const Fr_59_Renesas_LowLevelConfSetType *const pLowLevelCfgPtr);
extern FUNC(uint16, FR_PRIVATE_CODE)
    Fr_59_Renesas_CalHeaderCRC(const uint8 Fr_CtrlIdx, const uint16 usFrameHandle,
                               const uint8 ucPayLoadLength, const uint16 ucFrameId);
extern FUNC(Std_ReturnType, FR_PRIVATE_CODE) Fr_59_Renesas_OperationEnable(const uint8 Fr_CtrlIdx);
extern FUNC(uint32, FR_PRIVATE_CODE) Fr_59_Renesas_GetPOCStsFlag(const uint8 Fr_CtrlIdx);
extern FUNC(Std_ReturnType, FR_PRIVATE_CODE)
    Fr_59_Renesas_WriteCHICmd(const uint8 Fr_CtrlIdx, const uint32 CHICmd);
extern FUNC(Std_ReturnType, FR_PRIVATE_CODE) Fr_59_Renesas_SwitchCCToConfig(const uint8 Fr_CtrlIdx);
extern FUNC(Std_ReturnType, FR_PRIVATE_CODE) Fr_59_Renesas_UpdatePOCSts(const uint8 Fr_CtrlIdx,
                                                                        Fr_POCStatusType *const Fr_POCStatusPtr);
extern FUNC(Std_ReturnType, FR_PRIVATE_CODE)
    Fr_59_Renesas_GetCorrectionValue(const uint8 Fr_CtrlIdx,
                                     sint16 *const Fr_RateCorrectionPtr, sint32 *const Fr_OffsetCorrectionPtr);
#if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
extern FUNC(void, FR_PRIVATE_CODE) Fr_59_Renesas_InitDone(uint8 LucCoreIndex);
#endif
extern FUNC(Std_ReturnType, FR_PRIVATE_CODE) Fr_59_Renesas_CheckErrorInterrupt(const uint8 Fr_CtrlIdx);
extern FUNC(Std_ReturnType, FR_PRIVATE_CODE) Fr_59_Renesas_GetBufferCommand(const uint8 Fr_CtrlIdx);
extern FUNC(void, FR_PRIVATE_CODE) Fr_59_Renesas_WriteHeaderSection(const uint8 Fr_CtrlIdx,
                                                                    const uint32 RegMacro, const uint32 RegValue);
#if (FR_59_RENESAS_SET_CYCLE_COUNTER_FILTERING_API == STD_ON)
extern FUNC(Std_ReturnType, FR_PRIVATE_CODE)
    Fr_59_Renesas_SetCycleOffset(const uint8 Fr_CtrlIdx,
                                 const uint8 Fr_AbsTimerIdx, uint8 Fr_CycleCode, const uint16 Fr_Offset);
#endif

#if (FR_59_RENESAS_ENABLE_OUTPUT_RX_HANDLER == STD_ON)
extern FUNC(Std_ReturnType, FR_PRIVATE_CODE)
    Fr_59_Renesas_OutputTransferRequest(const uint8 Fr_CtrlIdx,
                                        volatile Fr_59_Renesas_OutputPointerTableType *const Fr_OutputTableContentPtr);
#endif

#if (FR_59_RENESAS_ENABLE_INPUT_TX_HANDLER == STD_ON)
extern FUNC(Std_ReturnType, FR_PRIVATE_CODE)
    Fr_59_Renesas_InputTransferRequest(const uint8 Fr_CtrlIdx,
                                       volatile Fr_59_Renesas_InputPointerTableType *const Fr_InputTableContentPtr);
#endif
#if (FR_59_RENESAS_ENABLE_INPUT_TX_HANDLER == STD_ON)
extern FUNC(Std_ReturnType, FR_PRIVATE_CODE)
    Fr_59_Renesas_UpdateInputPtrTable(const uint8 Fr_CtrlIdx,
                                      volatile Fr_59_Renesas_InputPointerTableType *const Fr_InputTableContentPtr);
#endif
extern FUNC(Std_ReturnType, FR_PRIVATE_CODE) Fr_59_Renesas_ResetOutputTransfer(const uint8 Fr_CtrlIdx);
extern FUNC(Std_ReturnType, FR_PRIVATE_CODE) Fr_59_Renesas_ResetInputTransfer(const uint8 Fr_CtrlIdx);
extern FUNC(Std_ReturnType, FR_PRIVATE_CODE) Fr_59_Renesas_ResumeInputQueueTransfer(const uint8 Fr_CtrlIdx);
#if ((FR_59_RENESAS_ENABLE_OUTPUT_RX_HANDLER == STD_ON) || (FR_59_RENESAS_ENABLE_OUTPUT_RX_FIFO_HANDLER == STD_ON))
extern FUNC(Std_ReturnType, FR_PRIVATE_CODE)
    Fr_59_Renesas_DataAvailable(const uint8 Fr_CtrlIdx,
                                CONSTP2VAR(volatile Fr_59_Renesas_OutputPointerTableType, AUTOMATIC, FR_APPL_DATA)
                                    Fr_OutputTableContentPtr,
                                CONSTP2VAR(volatile Fr_59_Renesas_OutputPointerTableType, AUTOMATIC, FR_APPL_DATA)
                                    Fr_FIFOTableContentPtr);
#endif
extern FUNC(Std_ReturnType, FR_PRIVATE_CODE)
    Fr_59_Renesas_UpdateCCConfig(const uint8 Fr_CtrlIdx,
                                 const uint8 Fr_ConfigParamIdx, uint32 *const Fr_ConfigParamValuePtr);
extern FUNC(void, FR_PRIVATE_CODE) Fr_59_Renesas_DisableTimer(const uint8 Fr_CtrlIdx,const uint8 Fr_AbsTimerIdx);

extern FUNC(Std_ReturnType, FR_PRIVATE_CODE) Fr_59_Renesas_ClearTimerInterrupt(const uint8 Fr_CtrlIdx,
                                                                               const uint8 Fr_AbsTimerIdx);
extern FUNC(void, FR_PRIVATE_CODE) Fr_59_Renesas_EnableTimerInterrupt(const uint8 Fr_CtrlIdx,
                                                                      const uint8 Fr_AbsTimerIdx);
extern FUNC(void, FR_PRIVATE_CODE) Fr_59_Renesas_CancelTimerInterrupt(const uint8 Fr_CtrlIdx,
                                                                      const uint8 Fr_AbsTimerIdx);
extern FUNC(Std_ReturnType, FR_PRIVATE_CODE)
    Fr_59_Renesas_StartTimer(const uint8 Fr_CtrlIdx,
                             const uint8 Fr_AbsTimerIdx, uint8 Fr_Cycle, const uint16 Fr_Offset);
extern FUNC(void, FR_PRIVATE_CODE) Fr_59_Renesas_TimerRunning(const uint8 Fr_CtrlIdx,
                                                              const uint32 Data, const uint8 Fr_AbsTimerIdx);
extern FUNC(Std_ReturnType, FR_PRIVATE_CODE) Fr_59_Renesas_UpdateWakeupRxSts(const uint8 Fr_CtrlIdx,
                                                                             uint8 *const Fr_WakeupRxStatusPtr);

extern FUNC(void, FR_PRIVATE_CODE) Fr_59_Renesas_UpdateWriteDataSection(const uint8 Fr_CtrlIdx,
                                                                        const uint32 RegMacro, const uint32 Data);
extern FUNC(void, FR_PRIVATE_CODE)
    Fr_59_Renesas_UpdateChannelEvenList(const uint8 Fr_CtrlIdx, const uint32 RegMacro,
                                        uint16 *const Fr_ChannelAEvenListPtr, uint16 *const Fr_ChannelBEvenListPtr);
extern FUNC(void, FR_PRIVATE_CODE)
    Fr_59_Renesas_UpdateChannelOddList(const uint8 Fr_CtrlIdx, const uint32 RegAdd,
                                       uint16 *const Fr_ChannelAOddListPtr, uint16 *const Fr_ChannelBOddListPtr);
extern FUNC(Std_ReturnType, FR_PRIVATE_CODE)
    Fr_59_Renesas_ReadAggregatedStatus(const uint8 Fr_CtrlIdx,
                                       uint16 *const Fr_ChannelAStatusPtr, uint16 *const Fr_ChannelBStatusPtr);
extern FUNC(Std_ReturnType, FR_PRIVATE_CODE) Fr_59_Renesas_NetworkManagement(const uint8 Fr_CtrlIdx,
                                                                             uint8 *Fr_NmVectorPtr);
extern FUNC(Std_ReturnType, FR_PRIVATE_CODE)
    Fr_59_Renesas_GetCycleCounter(const uint8 Fr_CtrlIdx, uint8 *const Fr_CyclePtr, uint16 *const Fr_MacroTickPtr);
#if (FR_59_RENESAS_DISABLE_LPDU == STD_ON)
extern FUNC(Std_ReturnType, FR_PRIVATE_CODE) Fr_59_Renesas_ResetWriteHeader(const uint8 Fr_CtrlIdx,
                                                                            const uint16 Fr_LPduIdx);
#endif /* FR_59_RENESAS_DISABLE_LPDU == STD_ON */
extern FUNC(Std_ReturnType, FR_PRIVATE_CODE)
    Fr_59_Renesas_UpdateDataTransferMode(const uint8 Fr_CtrlIdx, const uint8 LucMessageBuffer);
extern FUNC(Std_ReturnType, FR_PRIVATE_CODE)
    Fr_59_Renesas_UpdateLPduTxSts(const uint8 Fr_CtrlIdx,
                                  const uint16 Fr_LPduIdx, const uint8 LucMessageBuffer,
                                  Fr_TxLPduStatusType *const Fr_TxLPduStatusPtr);
extern FUNC(Std_ReturnType, FR_PRIVATE_CODE) Fr_59_Renesas_ClearTxReq(const uint8 Fr_CtrlIdx,
                                                                      const uint8 LucMessageBuffer);
extern FUNC(Std_ReturnType, FR_PRIVATE_CODE)
    Fr_59_Renesas_MessageBufferStatus(const uint8 Fr_CtrlIdx,const uint16 Fr_LPduIdx);                                  
extern FUNC(void, FR_PRIVATE_CODE)
    Fr_59_Renesas_UpdateStsLength(const uint8 Fr_CtrlIdx,
                                  Fr_RxLPduStatusType *const Fr_LPduStatusPtr, uint8 *const Fr_LSduLengthPtr);
extern FUNC(Std_ReturnType, FR_PRIVATE_CODE)
    Fr_59_Renesas_NewData(const uint8 Fr_CtrlIdx, const uint8 LucMessageBuffer,
                          Fr_RxLPduStatusType *const Fr_LPduStatusPtr, uint8 *const Fr_LSduLengthPtr);
extern FUNC(Std_ReturnType, FR_PRIVATE_CODE)
    Fr_59_Renesas_WriteOutputBufferCommand(const uint8 Fr_CtrlIdx, const uint16 Fr_LPduIdx);
extern FUNC(Std_ReturnType, FR_PRIVATE_CODE)
    Fr_59_Renesas_ReadReceiveData(const uint8 Fr_CtrlIdx,
                                  const uint16 Fr_LPduIdx, uint8 *Fr_LSduPtr,
                                  Fr_RxLPduStatusType *const Fr_LPduStatusPtr, uint8 *const Fr_LSduLengthPtr);
extern FUNC(uint32, FR_PRIVATE_CODE)
    Fr_59_Renesas_ReadDataSection(const uint8 Fr_CtrlIdx, const uint32 RegMacro);
#if ((FR_59_RENESAS_ENABLE_OUTPUT_RX_HANDLER == STD_ON) || (FR_59_RENESAS_ENABLE_OUTPUT_RX_FIFO_HANDLER == STD_ON))
extern FUNC(Std_ReturnType, FR_PRIVATE_CODE) Fr_59_Renesas_UpdateOutputPtrTable(
    const uint8 Fr_CtrlIdx,
    const volatile Fr_59_Renesas_OutputPointerTableType *const Fr_OutputTableContentPtr);
#endif
extern FUNC(void, FR_PRIVATE_CODE) Fr_59_Renesas_UnlockSequence(const uint8 Fr_CtrlIdx);
extern FUNC(Std_ReturnType, FR_PRIVATE_CODE)
    Fr_59_Renesas_SetWakeupChannelProcess(const uint8 Fr_CtrlIdx,
                                          CONST(Fr_ChannelType, AUTOMATIC) Fr_ChnlIdx);
extern FUNC(void, FR_PRIVATE_CODE) Fr_59_Renesas_UpdateInputBuffer(const uint8 Fr_CtrlIdx,
                                                                   const uint8 Fr_LSduLength, const uint8 *Fr_LSduPtr);
extern FUNC(Std_ReturnType, FR_PRIVATE_CODE)
    Fr_59_Renesas_UpdateWRHReg(const uint8 Fr_CtrlIdx,
                               uint32 RegValue, const uint16 Fr_HeaderCRC, const uint8 Fr_PayloadLength,
                               const uint16 Fr_LPduIdx);
extern FUNC(Std_ReturnType, FR_PRIVATE_CODE)
    Fr_59_Renesas_UpdateNumOfStartupFrame(const uint8 Fr_CtrlIdx, uint8 *const Fr_NumOfStartupFramesPtr);
extern FUNC(void, FR_PRIVATE_CODE)
    Fr_59_Renesas_UpdateSyncFrameList(const uint8 Fr_CtrlIdx,
                                      const uint8 Fr_ListSize, uint16 *Fr_ChannelAEvenListPtr,
                                      uint16 *Fr_ChannelBEvenListPtr, uint16 *Fr_ChannelAOddListPtr,
                                      uint16 *Fr_ChannelBOddListPtr);
extern FUNC(void, FR_PRIVATE_CODE) Fr_59_Renesas_GetIrqSts(const uint8 Fr_CtrlIdx,
                                                           const uint8 Fr_AbsTimerIdx, boolean *const Fr_IRQStatusPtr);
#if (FR_59_RENESAS_ENABLE_INPUT_TX_HANDLER == STD_ON)
extern FUNC(Std_ReturnType, FR_PRIVATE_CODE) Fr_59_Renesas_HaltInputQueueProcess(
    const uint8 Fr_CtrlIdx,
    const volatile Fr_59_Renesas_InputPointerTableType *const Fr_InputTableContentPtr);
#endif

#if (FR_59_RENESAS_EXTENDED_LPDU_REPORTING == STD_ON)
extern FUNC(Std_ReturnType, FR_PRIVATE_CODE)
    Fr_59_Renesas_GetSlotAssignment(const uint8 Fr_CtrlIdx, const uint16 Fr_LPduIdx, 
    Fr_SlotAssignmentType *const Fr_SlotAssignmentPtr);
#endif

#define FR_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"

#endif /* FR_59_RENESAS_LLDRIVER_H */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
