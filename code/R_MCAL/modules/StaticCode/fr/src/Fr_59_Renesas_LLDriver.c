/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Fr_59_Renesas_LLDriver.c                                                                            */
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
 * 2.4.1:  30/06/2025   : Remove SW-VERSION in file header
 * 2.4.0:  30/06/2025   : Update SW-VERSION for RH850/U2Ax MCAL Ver22.01.00(D) Final Release
 * 2.3.2:  29/04/2025   : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 Release
 * 2.3.1:  31/03/2025   : Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02 Release
 *                        As part of QAC 11.6.0 support, following changes are made: 
 *                        1. Update comment for QAC message 3415, 3416, 2856, 4394, 3384. Not impact on behavior of code.
 *                        2. Remove QAC comments of message 1532, 2814, 2824, 2844, 2974, 3415, 3416, 3678
 *                        3. Add QAC message 3673
 * 2.3.0:  28/02/2025   : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.1:  31/12/2024   : Update SW-VERSION for Ver22.00.01 U2Ax Release
 * 2.2.0:  31/12/2024   : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 * 2.1.3:  31/10/2024   : Update SW-VERSION to 2.1.3
 * 2.1.2:  20/08/2024   : As part of QAC 9.5.0 support, following changes are made: 
 *                        1. Update for messages: 1532, 2814, 2824, 2844, 3415, 3416, 3673
 *                        2. Sort QAC message header in ascending order
 *                        As part of R22-11 support, following changes are made:
 *                        Remove preprocessor FR_59_RENESAS_AR_431_VERSION
 * 2.1.1:  15/07/2024   : As part of QAC 9.5.0 support, following changes are made: 
 *                        Update comment for QAC message. Not impact on behavior of code.
 *                      : As part of multicore support, following changes are made:
 *                        Add agrument uint8 LucCoreIndex to Fr_59_Renesas_InitDone
 *                      : As part of multiple postbuild variant support, following changes are made:
 *                        Update function Fr_59_Renesas_UpdateCCConfig, use global variable
 *                        Fr_59_Renesas_GpPeriodTimeConfigPtr
 *                      : As part of QAC 10.3.0 support, following changes are made:
 *                        Remove redundant QAC message: 1532 , 2814, 2824, 2844, 3421, 1031
 * 2.1.0:  24/02/2024   : Change SW-VERSION to 2.1.0
 * 2.0.1:  27/09/2023   : Change FR_59_RENESAS_AR_R21_11_VERSION with FR_59_RENESAS_AR_R22_11_VERSION to support AR22-11
 *                        Add QAC message: 0857, 0791
 *                        Remove QAC message: 0312
 *
 *                        In function Fr_59_Renesas_LoadCfgLowLevelParameters: 
 *                        Removed 'FLXAnFRT0C' out of 'Register used' due to redundant
 * 2.0.0:  30/07/2023      : Add CWE rule into QAC header (2004, 1532, 2844, 2814, 2824, 3415, 3416, 2982, 4394, 4342,
 *                           2856, 1505, 0303, 2934, 3432, 0310, 0312, 0488, 2962, 2983 messages)
 *                         : Change FR_59_RENESAS_AR_2111_VERSION to FR_59_RENESAS_AR_R21_11_VERSION
 *                           Improve Cyclomatic Complexity (STCYC<=20) for APIs Fr_59_Renesas_UpdateCCConfig, 
 *                           Fr_59_Renesas_UpdatePOCSts.
 *         21/04/2023      : For support AR2111:
 *                           - Add new funtion: Fr_59_Renesas_GetSlotAssignment
 *                           - Add condition to check AUTOSAR VERSION with FR_59_RENESAS_AR_R21_11_VERSION
 *                           Add QAC message for new function: Fr_59_Renesas_GetSlotAssignment
 *         19/04/2023      : Implement improvement actions from Technical Assessment
 *                          + Remove FLXAnFRT2C in Registers Used of API Fr_59_Renesas_LoadCfgLowLevelParameters
 *                          + Add Fr_59_Renesas_GpControllerConfigPtr to Global Variables description of APIs:
 *                             Fr_59_Renesas_GetCorrectionValue, Fr_59_Renesas_SetCycleOffset,
 *                             Fr_59_Renesas_OutputTransferRequest, Fr_59_Renesas_GetIrqSts,
 *                             Fr_59_Renesas_DisableTimer, Fr_59_Renesas_EnableTimerInterrupt,
 *                             Fr_59_Renesas_CancelTimerInterrupt, Fr_59_Renesas_TimerRunning,
 *                             Fr_59_Renesas_UpdateWakeupRxSts, Fr_59_Renesas_NetworkManagement,
 *                             Fr_59_Renesas_UpdateDataTransferMode, Fr_59_Renesas_ClearTxReq.
 *                          + Add Fr_OutputTableContentPtr to Global Variables description of API:
 *                             Fr_59_Renesas_DataAvailable
 *                          + Add FR_59_RENESAS_DEM_REPORT_ERROR in Functions Invoked of API: Fr_59_Renesas_ClearTxReq
 *                          + Add FR_59_RENESAS_ENTER_CRITICAL_SECTION, FR_59_RENESAS_EXIT_CRITICAL_SECTION
 *                            in Functions Invoked of API: Fr_59_Renesas_UpdateDataTransferMode.
 *                          + Remove Dem_ReportErrorStatus(AR422) and Dem_SetEventStatus(AR431)
 *                            and add FR_59_RENESAS_DEM_REPORT_ERROR in Functions Invoked of API:
 *                             Fr_59_Renesas_CfgBuffer, Fr_59_Renesas_CfgBufferHeader,
 *                             Fr_59_Renesas_CheckIfCCBusy, Fr_59_Renesas_CheckCCConfig, Fr_59_Renesas_OperationEnable,
 *                             Fr_59_Renesas_UpdatePOCSts, Fr_59_Renesas_GetCorrectionValue,
 *                             Fr_59_Renesas_ResetInputTransfer, Fr_59_Renesas_SetWakeupChannelProcess,
 *                             Fr_59_Renesas_CheckErrorInterrupt, Fr_59_Renesas_GetBufferCommand,
 *                             Fr_59_Renesas_UpdateWRHReg, Fr_59_Renesas_OutputTransferRequest,
 *                             Fr_59_Renesas_InputTransferRequest, Fr_59_Renesas_ResetOutputTransfer,
 *                             Fr_59_Renesas_UpdateInputPtrTable, Fr_59_Renesas_UpdateOutputPtrTable,
 *                             Fr_59_Renesas_ResumeInputQueueTransfer, Fr_59_Renesas_DataAvailable,
 *                             Fr_59_Renesas_ClearTimerInterrupt, Fr_59_Renesas_StartTimer,
 *                             Fr_59_Renesas_UpdateWakeupRxSts, Fr_59_Renesas_ReadAggregatedStatus,
 *                             Fr_59_Renesas_NetworkManagement, Fr_59_Renesas_UpdateNumOfStartupFrame,
 *                             Fr_59_Renesas_GetCycleCounter, Fr_59_Renesas_ResetWriteHeader,
 *                             Fr_59_Renesas_MessageBufferStatus, Fr_59_Renesas_WriteOutputBufferCommand,
 *                             Fr_59_Renesas_HaltInputQueueProcess.
 *                          + Change the Return parameter from None to Std_ReturnType E_OK or E_NOT_OK for API:
 *                             Fr_59_Renesas_UpdateLPduTxSts
  *        06/04/2023      : Reduce STCYC <=20 for APIs: Fr_59_Renesas_UpdateWriteDataSection
 *                                                       Fr_59_Renesas_ReadDataSection
 *                                                       Fr_59_Renesas_CheckCCConfig
 *                           Add QAC message 9.5.0 (2:0310), (4:0312), (2:0488), (2:3421), (2:1031), (6:2962) 
 *                           Add jugdement JV-02 for QAC message 9.5.0 (1:3383)
 * 1.4.3:  09/05/2022      : Change SW-VERSION to 1.4.3, Remove "else" statement don't use when no action required.
 *         05/05/2022      : Fix Un-balanced pre-processor
 *                            - Function: Fr_59_Renesas_DataAvailable
 *                              + LpMBCtrlReg, LpFrameConfigPtr, LpLowLevelCfgPtr, LpOutputPointerTablePtr,
 *                                LucMessageBuffer, LucFirstFifoBuff, LucOutputTableCount.
 *                            - Function: Fr_59_Renesas_UpdateOutputPtrTable
 *                              + LucMsgBufferMask, LucFRDAindex.
 *                           Change macros name FR_59_RENESAS_FLX0ESID_FLX0EID_MASK from FLX0ESID_FLX0EID_MASK,
 *                           Change macros name FR_59_RENESAS_FLX0OSID_FLX0OID_MASK from FLX0OSID_FLX0OID_MASK,
 *                           Change macros name FR_59_RENESAS_FLX0ESID_FLX0RXEA_FLX0RXEB_MASK from
 *                           FLX0ESID_FLX0RXEA_FLX0RXEB_MASK
 *                         : Add QAC message 9.5.0 2004
 *         13/04/2022      : Change uint8 LusLoopCount to uint8 LucLoopCount
 * 1.3.3:  02/03/2022      : Change SW-VERSION to 1.4.2
 * 1.3.2:  13/08/2021      : Change SW-VERSION to 1.3.2
 * 1.3.1:  09/07/2021      : Modify function: Fr_59_Renesas_SetWakeupChannelProcess() to fix implementation for checking
 *                           checking the POC state.
 *         02/07/2021      : Add QAC message 9.5.0.
 *                           Format source code to 120 characters.
 *                           Improve Violation tag (remove START/END).
 *         04/05/2021      : + In internal function Fr_59_Renesas_CfgBuffer, Fr_59_Renesas_OperationEnable,
 *                           Fr_59_Renesas_OutputTransferRequest, Fr_59_Renesas_WriteOutputBufferCommand add space
 *                           to follow coding guideline Style_Format_009.
 *                           + In internal function Fr_59_Renesas_CfgBufferHeader, Fr_59_Renesas_UpdateDataTransferMode,
 *                           Fr_59_Renesas_ClearTxReq, add space in FR_59_RENESAS_DEM_REPORT_ERROR to follow
 *                           coding guideline Style_Format_010.
 *                           + In internal function Fr_59_Renesas_SetCycleOffset, Fr_59_Renesas_GetIrqSts,
 *                           Fr_59_Renesas_DisableTimer, Fr_59_Renesas_ClearTimerInterrupt,
 *                           Fr_59_Renesas_EnableTimerInterrupt, Fr_59_Renesas_CancelTimerInterrupt,
 *                           Fr_59_Renesas_StartTimer, Fr_59_Renesas_TimerRunning correct name of enumeration's element
 *                           FR_59_RENESAS_TIMER0 (from TIMER0) to follow SWS Autosar Requirement SWS_BSW_00124.
 *                           + In internal function Fr_59_Renesas_SetCycleOffset, Fr_59_Renesas_StartTimer,
 *                           update macro name FR_59_RENESAS_FLX0TXC_CYC_SHIFT(from FR_59_RENESAS_FLX0TxC_CYC_SHIFT)
 *                           and FR_59_RENESAS_FLX0TXC_OFFSET_SHIFT (from FR_59_RENESAS_FLX0TxC_OFFSET_SHIFT)
 *                           to follow coding guideline Name_Macro_001
 *                           + Update name for the following self defined structure type to follow naming convention
 *                           in coding guideline Name_Type_002
 *                           Fr_59_Renesas_OperationRegType (from FR_OperationReg)
 *                           Fr_59_Renesas_InterruptRegType (from FR_InterruptReg)
 *                           Fr_59_Renesas_TimerRegType (from FR_TimerReg)
 *                           Fr_59_Renesas_CCControlRegType (from FR_CCControlReg)
 *                           Fr_59_Renesas_CCStatusRegType (from FR_CCStatusReg)
 *                           Fr_59_Renesas_MessageBufferControlRegType (from FR_MessageBufferControlReg)
 *                           Fr_59_Renesas_MessageBufferStatusRegType (from FR_MessageBufferStatusReg)
 *                           Fr_59_Renesas_InputBufferRegType (from FR_InputBufferReg)
 *                           Fr_59_Renesas_OutputBufferRegType (from FR_OutputBufferReg)
 *                           Fr_59_Renesas_DataTransferControlRegType (from FR_DataTransferControlReg)
 *                           Fr_59_Renesas_DataTransferStatusRegType (from FR_DataTransferStatusReg)
 *                           Fr_59_Renesas_OutputConstdataType (from Fr_59_Renesas_OutputConstdata)
 *                           Fr_59_Renesas_InputConstdataType (from Fr_59_Renesas_InputConstdata)
 *         29/04/2021      : In internal function Fr_59_Renesas_StartTimer, corrected wrong implementation when
 *                           halt the absolute timer 0 and timer 2 before apply new timer configuration, updated
 *                           to stop timers correctly by writing to hardware register (FLXAnFRT0C for Timer 0 and
 *                           FLXAnFRT2C for Timer 2) instead of writing to local variables.
 *         28/04/2021      : + Add missing condition check in internal function Fr_59_Renesas_CfgBuffer
 *                           (API Fr_ControllerInit) to exclude all LPdus which are dynamically reconfigurable
 *                           from buffer initialization.
 * 1.3.0:  02/12/2020      : + Update the condition to check timer selection in functions:
 *                           Fr_59_Renesas_SetCycleOffset, Fr_59_Renesas_GetIrqSts, Fr_59_Renesas_DisableTimer,
 *                           Fr_59_Renesas_ClearTimerInterrupt, Fr_59_Renesas_EnableTimerInterrupt,
 *                           Fr_59_Renesas_CancelTimerInterrupt, Fr_59_Renesas_StartTimer, Fr_59_Renesas_TimerRunning.
 *                           + Remove Timer 0 and Timer 2 mode configuration in function
 *                           Fr_59_Renesas_LoadCfgLowLevelParameters.
 *                           + Add Timer 0/2 mode configuration in function Fr_59_Renesas_StartTimer.
 *                           + Update to add comment for QAC msg 1532.
 *                           + Update Fr_59_Renesas_SetCycleOffset to fix QAC msg 0604.
 * 1.2.0:  26/08/2020      : Release.
 * 1.1.0:  19/06/2020      : Release.
 *         28/07/2020      : Add QAC 9.3.1 comment.
 * 1.0.3:  09/06/2020      : Remove Critical Section in Fr_59_Renesas_GetIrqSts, Fr_59_Renesas_UpdateWakeupRxSts
 *                           Add Critical Section in Fr_59_Renesas_UpdateDataTransferMode,
 *                           Fr_59_Renesas_WriteOutputBufferCommand
 *                           Re-implement Critical Section of Fr_59_Renesas_GetBufferCommand.
 *         28/05/2020      : Remove QAC message Msg(2:3227),Msg(3:3415),Msg(2:3416).
 *         22/05/2020      : Remove QAC message Msg(5:3673).
 *         21/05/2020      : Add FLXAnFRIBCR.IBSYH checking and report DEM error in Fr_59_Renesas_ClearTxReq and
 *                           Fr_59_Renesas_UpdateDataTransferMode.
 *                           Change Fr_59_Renesas_UpdateDataTransferMode return type from 'void' to 'Std_ReturnType'.
 *         09/05/2020      : Correct Fr_59_Renesas_CfgBuffer and Fr_59_Renesas_CfgBufferHeader sequence to transfer
 *                           Header section from Input Buffer to Message RAM.
 * 1.0.2:  25/04/2020      : Remove argument definition using Compiler.h's macros.
 *         17/04/2020      : Update the header file including.
 *         15/04/2020      : + In Fr_59_Renesas_UpdateLPduTxSts and Fr_59_Renesas_MessageBufferStatus: Change from use
 *                            enum value FR_CHANNEL_A, FR_CHANNEL_B and FR_CHANNEL_AB to macro FR_59_RENESAS_CHANNEL_A,
 *                            FR_59_RENESAS_CHANNEL_B and FR_59_RENESAS_CHANNEL_AB.
 * 1.0.1:  23/03/2020      : + Update Fr_59_Renesas_UpdateLPduTxSts, Fr_59_Renesas_UpdateDataTransferMode.
 *                           + Fix the condition to set status to FR_RECEIVED in Fr_59_Renesas_NewData.
 *                           + Remove FLXAnFRMBSCm (m = 1..4) implementation in Fr_59_Renesas_UpdateLPduTxSts.
 *                           + For #262380, use Frame Channel reference instead of Controller Channel reference in
 *                           Fr_59_Renesas_MessageBufferStatus.
 *         20/03/2020      : In Fr_59_Renesas_CfgBuffer, for FIFO buffer, value LucPayloadLength is retrieved from
 *                           LpBufferHeader->ucPayloadLength instead of ulFLXAnFRMHDC.
 *                           Remove LpCCCtrlReg Refer to ARDAACH-10 and #257241.
 *                         : Change traceability ID format from "FR_DDD_" to "FR_DUD_".
 *                         : + Redmine #262107 rework Fr_59_Renesas_UpdateLPduTxSts to report FR_TRANSMITTED_CONFLICT
 *                           for AR431 specification.
 *                           + Update algorithm of Fr_59_Renesas_ClearTxReq, Fr_59_Renesas_NewData,
 *                           Fr_59_Renesas_WriteOutputBufferCommand.
 *         15/03/2020      : Add condition check bit FLXAnFRITC.IQHR == 0 before clear bit FLXAnFRITC.ITE in
 *                           Fr_59_Renesas_ResetInputTransfer according to issue in ARDAACH-7.
 *         13/03/2020      : Replace uint16_least, uint8_lest to uint16 and uint16 and uint8.
 *         14/01/2020      : Change from use Dem_ReportStatus() to FR_59_RENESAS_DEM_REPORT_ERROR.
 * 1.0.0:  11/12/2019       : Initial Version.
 *****************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for declaration of the internal functions */
#include "Fr_59_Renesas.h"
/* Include internal function definition */
#include "Fr_59_Renesas_LLDriver.h"
/* Include Dem definition */
#include "Dem.h"
#if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
/* Included for the declaration of Det_ReportError() */
#include "Det.h"
#endif /* (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
#if (FR_59_RENESAS_CRITICAL_SECTION_PROTECTION == STD_ON)
/* Included for the declaration of the critical section protection functions */
#include "SchM_Fr_59_Renesas.h"
#endif
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define FR_59_RENESAS_LLDRIVER_C_AR_RELEASE_MAJOR_VERSION    FR_59_RENESAS_AR_RELEASE_MAJOR_VERSION_VALUE
#define FR_59_RENESAS_LLDRIVER_C_AR_RELEASE_MINOR_VERSION    FR_59_RENESAS_AR_RELEASE_MINOR_VERSION_VALUE
#define FR_59_RENESAS_LLDRIVER_C_AR_RELEASE_REVISION_VERSION FR_59_RENESAS_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define FR_59_RENESAS_LLDRIVER_C_SW_MAJOR_VERSION            FR_59_RENESAS_SW_MAJOR_VERSION_VALUE
#define FR_59_RENESAS_LLDRIVER_C_SW_MINOR_VERSION            FR_59_RENESAS_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (FR_59_RENESAS_LLDRIVER_AR_RELEASE_MAJOR_VERSION != FR_59_RENESAS_LLDRIVER_C_AR_RELEASE_MAJOR_VERSION)
  #error "Fr_59_Renesas_LLDriver.c : Mismatch in Release Major Version"
#endif

#if (FR_59_RENESAS_LLDRIVER_AR_RELEASE_MINOR_VERSION != FR_59_RENESAS_LLDRIVER_C_AR_RELEASE_MINOR_VERSION)
  #error "Fr_59_Renesas_LLDriver.c : Mismatch in Release Minor Version"
#endif

#if (FR_59_RENESAS_LLDRIVER_AR_RELEASE_REVISION_VERSION != FR_59_RENESAS_LLDRIVER_C_AR_RELEASE_REVISION_VERSION)
  #error "Fr_59_Renesas_LLDriver.c : Mismatch in Release Revision Version"
#endif

#if (FR_59_RENESAS_LLDRIVER_SW_MAJOR_VERSION != FR_59_RENESAS_LLDRIVER_C_SW_MAJOR_VERSION)
  #error "Fr_59_Renesas_LLDriver.c : Mismatch in Software Major Version"
#endif

#if (FR_59_RENESAS_LLDRIVER_SW_MINOR_VERSION != FR_59_RENESAS_LLDRIVER_C_SW_MINOR_VERSION)
  #error "Fr_59_Renesas_LLDriver.c : Mismatch in Software Minor Version"
#endif

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:0303)    : Cast between a pointer to volatile object and an integral type.                              */
/* Rule                : CERTCCM INT36, MISRA C:2012 Rule-11.4, CWE Rule CWE-398, CWE-569                             */
/* JV-01 Justification : Typecasting is done as per the register size, to access hardware registers.                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0310)    : Casting to different object pointer type.                                                    */
/* Rule                : CERTCCM EXP11, EXP39, MISRA C:2012 Rule-11.3, CWE Rule CWE-188, CWE-398, CWE-468, CWE-588    */
/*                       CWE-465, CWE-569, CWE-737                                                                    */
/* JV-01 Justification : There is no problem because it is as designed.                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0488)    : Performing pointer arithmetic.                                                               */
/* Rule                : CERTCCM EXP08, MISRA C:2012 Rule-18.4, CWE Rule CWE-188, CWE-398, CWE-569                    */
/* JV-01 Justification : This implementation is required for heap memory allocation algorithm                         */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (7:0791)    : Macro identifier does not differ from other macro identifier(s) (e.g. '%s') within the       */
/*                       specified number of significant characters.                                                  */
/* Rule                : CERTCCM DCL23, MISRA C:2012 Rule-5.4                                                         */
/* JV-01 Justification : This macro identifier is following AUTOSAR standard rule (Symbolic Name or Published         */
/*                       Macro's name), so this is accepted.                                                          */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0857)    : Number of macro definitions exceeds 1024 - program does not conform strictly to ISO:C90.     */
/* Rule                : MISRA C:2012 Dir-1.1                                                                         */
/* JV-01 Justification : The number of macro depend on module code size. There is no issue when number of macro is    */
/*                       over 1024.                                                                                   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:1338)    : The parameter '%s' is being modified.                                                        */
/* Rule                : MISRA C:2012 Rule-17.8                                                                       */
/* JV-01 Justification : This in case, parameter is not const, it could be accepted for modification.                 */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1505)    : The function '%1s' is only referenced in the translation unit where it is defined.           */
/* Rule                : CERTCCM DCL19, MISRA C:2012 Rule-8.7, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : This is accepted, due to following coding rule, internal function can be defined in other C  */
/*                       source files.                                                                                */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1532)    : The function '%1s' is only referenced in one translation unit - but not the one in which it  */
/*                       is defined.                                                                                  */
/* Rule                : CERTCCM DCL19, MISRA C:2012 Rule-8.7                                                         */
/* JV-01 Justification : This macro identifier is following AUTOSAR standard rule  (Symbolic Name or Published        */
/*                       Macro's name), so this is accepted.                                                          */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:2004)    : No concluding 'else' exists in this 'if'-'else'-'if' statement.                              */
/* Rule                : MISRA C:2012 Rule-15.7, CERTCCM MSC01, CWE Rule CWE-398, CWE-569                             */
/* JV-01 Justification : The "else"statement with empty content is removed to improve readability.                    */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:2814)    : Possible: Dereference of NULL pointer.                                                       */
/* Rule                : CERTCCM EXP34                                                                                */
/* JV-01 Justification : This is accepted, due to the implementation is following hardware specification.             */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:2824)    : Possible: Arithmetic operation on NULL pointer.                                              */
/* Rule                : CERTCCM EXP34                                                                                */
/* JV-01 Justification : This is accepted, due to the implementation is following hardware specification.             */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:2844)    : Possible: Dereference of an invalid pointer value.                                           */
/* Rule                : CERTCCM ARR30                                                                                */
/* JV-01 Justification : It is specific for device register accessing and confirmed has no issue in software behavior.*/
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (6:2856)    : Definite: Casting to a signed integer type of insufficient size.                             */
/* Rule                : CERTCCM INT31, MISRA C:2012 Dir-1.1, CWE Rule CWE-681, CWE-704, CWE-192, CWE-738             */
/* JV-01 Justification : Value range is controlled to not exist type size.                                            */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:2934)    : Possible: Computing an invalid pointer value.                                                */
/* Rule                : CERTCCM ARR30, ARR37, ARR38, EXP08, CWE Rule CWE-120, CWE-121, CWE-122, CWE-124, CWE-125     */
/*                       CWE-126, CWE-127, CWE-129, CWE-131, CWE-469, CWE-823, CWE-465, CWE-633, CWE-740              */
/* JV-01 Justification : This message prevent existing of an out of range pointer.                                    */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (6:2962)    : Apparent: Using value of uninitialized automatic object '%s'.                                */
/* Rule                : CERTCCM EXP33, MISRA C:2012 Rule-9.1, CWE Rule CWE-457, CWE-824, CWE-908, CWE-452, CWE-465   */
/*                       CWE-737                                                                                      */
/* JV-01 Justification : It will be initialized based on scope of 'if' statements where at least an 'if' statement    */
/*                       will be executed that will initialize the variable.                                          */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:2982)    : This assignment is redundant. The value of this object is never used before being modified.  */
/* Rule                : CERTCCM MSC07, MSC13, MISRA C:2012 Rule-2.2, CWE Rule CWE-14, CWE-398, CWE-561, CWE-563      */
/*                       CWE-569, CWE-633                                                                             */
/* JV-01 Justification : The variable needs to be initialized before using it.                                        */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:2983)    : This assignment is redundant. The value of this object is never subsequently used.           */
/* Rule                : CERTCCM MSC07, MSC13, MISRA C:2012 Rule-2.2, CWE Rule CWE-14, CWE-398, CWE-561, CWE-563      */
/*                       CWE-569, CWE-633                                                                             */
/* JV-01 Justification : The value is to increment the pointer to the next item.                                      */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:3383)    : Cannot identify wraparound guard for unsigned arithmetic expression.                         */
/* Rule                : CERTCCM INT30                                                                                */
/* JV-01 Justification : It can still result in values that are out of range for the intended use, as intuitive       */
/*                       "invariants" may not hold.                                                                   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/* JV-02 Justification : The variable being incremented is initialized and checked for upper bounds, so it never      */
/*                       wraps around.                                                                                */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:3384)    : Cannot identify wraparound guard for dependent unsigned arithmetic expression.               */
/* Rule                : CERTCCM INT30                                                                                */
/* JV-01 Justification : In order to effectively guard against overflow and wraparound at all stages, the             */
/*                       expression should be split up into individual dynamic operations, with their own guards      */
/*                       where applicable.                                                                            */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/* JV-02 Justification : LucLoopCount has the upper constraint to prevent the result of expression to be overflow.    */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3387)    : A full expression containing an increment (++) or decrement (--) operator should have no     */
/*                       potential side effects other than that caused by the increment or decrement operator.        */
/* Rule                : MISRA C:2012 Rule-13.3                                                                       */
/* JV-01 Justification : An increment/decrement is created a side affect. In this case it's accessing a volatile      */
/*                       object. This can be accepted.                                                                */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3415)    : Right hand operand of '&&' or '||' is an expression with persistent side effects.            */
/* Rule                : CERTCCM EXP02, MISRA C:2012 Rule-13.5, CWE Rule CWE-398, CWE-768, CWE-569                    */
/* JV-01 Justification : Although it is a volatile object, it is not a direct access to the HW register, and there    */
/*                       is no side effect.                                                                           */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3416)    : Logical operation performed on expression with persistent side effects.                      */
/* Rule                : CERTCCM EXP45, CWE Rule CWE-398, CWE-569, CWE-737                                            */
/* JV-01 Justification : Logical operation accesses volatile object which is a register access. All register          */
/*                       addresses are generated with volatile qualifier. There is no impact on the functionality     */
/*                       due to this conditional check for mode change.                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE Rule CWE-398, CWE-569                                            */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is accepted. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3469)    : This usage of a function-like macro looks like it could be replaced by an equivalent         */
/*                       function call.                                                                               */
/* Rule                : MISRA C:2012 Dir-4.9                                                                         */
/* JV-01 Justification : This message indicates that a candidate macro may be suitable for replacement by a           */
/*                       function, based on an actual call-site and the arguments passed to it there. (Other uses of  */
/*                       the macro may not necessarily be suitable for replacement).                                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3673)    : The object addressed by the pointer parameter '%s' is not modified and so the pointer        */
/*                       could be of type 'pointer to const'.                                                         */
/* Rule                : CERTCCM DCL00, DCL13, MISRA C:2012 Rule-8.13                                                 */
/* JV-01 Justification : Pointer variable is used to modify the value at the address so the pointer cannot be         */
/*                       declared as 'pointer to const' type.                                                         */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3678)    : The object referenced by '%1s' is not modified through it, so '%1s' could be declared with   */
/*                       type '%2s'.                                                                                  */
/* Rule                : MISRA C:2012 Rule-8.13                                                                       */
/* JV-01 Justification : This is accepted. It just an advise for improve safety by reducing the possibility that      */
/*                       the referenced data is unintentionally modified through an unexpected alias and improves     */
/*                       clarity by indicating that the referenced data is not intended to be modified through this   */
/*                       alias or those depending on it.                                                              */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:4342)    : An expression of 'essentially unsigned' type (%1s) is being cast to enum type '%2s'.         */
/* Rule                : MISRA C:2012 Rule-10.5, CWE Rule CWE-704                                                     */
/* JV-01 Justification : It is assigned to a variable with no conflict in the data.                                   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:4394)    : A composite expression of 'essentially unsigned' type (%1s) is being cast to a different     */
/*                       type category, '%2s'.                                                                        */
/* Rule                : MISRA C:2012 Rule-10.8, CWE Rule CWE-136                                                     */
/* JV-01 Justification : This is done as per implementation requirement.                                              */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:5087)    : Use of #include directive after code fragment.                                               */
/* Rule                : MISRA C:2012 Rule-20.1                                                                       */
/* JV-01 Justification : This is done as per Memory Requirement, (MEMMAP003 - Specification of Memory Mapping).       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/

/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_CfgBuffer
**
** Service ID            : Not Applicable
**
** Description           : This service invokes the function to calculate the
**                         header value of the corresponding frames
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : None
**
** Global Variables Used : Fr_59_Renesas_GpControllerConfigPtr,
**                         Fr_59_Renesas_GpCtrlRegSet
**
** Functions Invoked     : Fr_59_Renesas_CfgBufferHeader,
**                         FR_59_RENESAS_DEM_REPORT_ERROR
**
** Registers Used        : FLXAnFRFCL, FLXAnFRWRHS1, FLXAnFRWRHS2,
**                         FLXAnFRWRHS3, FLXAnFRIBCM, FLXAnFRIBCR
**
** Reference ID          : FR_DUD_ACT_042, FR_DUD_ACT_042_ERR001,
** Reference ID          : FR_DUD_ACT_042_REG001, FR_DUD_ACT_042_REG002,
** Reference ID          : FR_DUD_ACT_042_REG003, FR_DUD_ACT_042_REG004,
** Reference ID          : FR_DUD_ACT_042_REG005
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"
FUNC(Std_ReturnType, FR_PRIVATE_CODE) Fr_59_Renesas_CfgBuffer(const uint8 Fr_CtrlIdx)                                 
{
  /* Declare pointer to register */
  P2CONST(volatile Fr_59_Renesas_RegisterSetType, AUTOMATIC, FR_CONFIG_DATA) LpCtrlRegSet;
  P2VAR(volatile Fr_59_Renesas_MessageBufferControlRegType, AUTOMATIC, REGSPACE) LpMBCtrlReg;                           /* PRQA S 3678 # JV-01 */
  P2VAR(volatile Fr_59_Renesas_InputBufferRegType, AUTOMATIC, REGSPACE) LpInputBuffReg;
  /* Declare local pointer to CC configuration */
  P2CONST(Fr_59_Renesas_CtrlTableType, TYPEDEF, FR_CONFIG_DATA) LpCtrlTable;
  P2CONST(Fr_59_Renesas_FrameHeaderType, AUTOMATIC, FR_CONFIG_DATA) LpBufferHeader;
  P2CONST(Fr_59_Renesas_FrameHeaderType, TYPEDEF, FR_CONFIG_DATA) LpFrameConfig;
  /* Declare local pointer to Dem Event Id */
  P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF, FR_CONFIG_DATA)
  LpDemEventId;
  uint32 LulData;
  uint16 LusFrameCount;
  uint16 LusNoOfFrames;
  uint16 LusDataPointer;
  uint16 LusDataPtrInc;
  uint16 LusFirstFIFOBuffer;
  uint8 LucFIFOdepth;
  uint8 LucPayloadLength;
  Std_ReturnType LucReturnValue;
  volatile uint16 LusLoopCount;
  /* Initialize the return value */
  LucReturnValue = E_OK;
  /* Initialize the payload value */
  LucPayloadLength = FR_59_RENESAS_ZERO;
  /* Copy global pointer to local pointer */
  LpCtrlRegSet = Fr_59_Renesas_GpCtrlRegSet[Fr_CtrlIdx];                                                                
  LpMBCtrlReg = LpCtrlRegSet->pMBCtrlReg;                                                                               
  LpInputBuffReg = (P2VAR(volatile Fr_59_Renesas_InputBufferRegType, AUTOMATIC, REGSPACE))LpCtrlRegSet->pInputBuffReg;
  LpCtrlTable = (P2CONST(Fr_59_Renesas_CtrlTableType, AUTOMATIC,
                                          FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pCtrlTable);
  /* Get the total number of frames configured */
  LusNoOfFrames = LpCtrlTable->usMaxFrames;                                                                             
  LpFrameConfig = Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pFrameConfig;
  /* Initialize the number of frames processed */
  LusFrameCount = FR_59_RENESAS_ZERO;
  /* Initialize the 1st FIFO Buffer */
  LusFirstFIFOBuffer = FR_59_RENESAS_ZERO;
  /* Loop through all the frames for loading the message buffer header */
  do
  {
    /* Get the pointer to frame configuration of the corresponding LusFrameCount */
    LpBufferHeader = &LpFrameConfig[LusFrameCount];                                                                   
    /*
     * Note: Frames allocated dedicated buffers shall be only be configured from Fr_59_Renesas_ControllerInit().
     * All other frames which are reconfigurable shall be performed only by Fr_PrepareLPdu()
     */
    if ((FR_59_RENESAS_FALSE == LpBufferHeader->blBufferReConfig) ||                                                   
                                                         (FR_59_RENESAS_FALSE == LpBufferHeader->blFrIfReconfigurable))
    {
      /* Invoke the internal function to calculate header value of the frames and load the values in the register */
      LucReturnValue = Fr_59_Renesas_CfgBufferHeader(Fr_CtrlIdx, LusFrameCount, LpBufferHeader->ucPayloadLength);
      /* Check if the return value */
      if (E_NOT_OK == LucReturnValue)
      {
        /* Update the frame count to the maximum number of frames configured */
        LusFrameCount = LusNoOfFrames;
      } /* else No Action required */
    } /* else No Action required */
    /* If FIFO is configured, get the message Buffer Id and data pointer */
    if ((FR_59_RENESAS_TRUE == LpBufferHeader->blIsFIFOConfig) && (FR_59_RENESAS_ZERO == LusFirstFIFOBuffer))
    {
      /* Data Pointer of the FIFO */
      LusDataPointer = LpBufferHeader->usDataPointer;
      /* Message Buffer Id for FIFO */
      LusFirstFIFOBuffer = LpBufferHeader->ucMsgBuffer;
      /* Get the static payload length */
      LucPayloadLength = LpBufferHeader->ucPayloadLength;
    } /* else No Action required */
    /* Increment the number of frames processed */
    LusFrameCount++;                                                                                                    /* PRQA S 3383 # JV-01 */
  } while (LusFrameCount < LusNoOfFrames);
  /*
   * The header section of each FIFO buffer is configured as below
   * 1. Wait until IBCR.IBSYH is reset
   * 2. All bits of WRHS1 shall be configured to "0"
   * 3. In WRHS2, the payload length configured of the FIFO buffer has to be
   *    configured (WRHS2.PLC[6:0]).
   * 4. The configuration of WRHS2.CRC[10:0] is not necessary.
   * 5. In WRHS3, the data pointer according to the FIFO buffer has to be
   *    configured.
   * 6. Write header section to WRHS1..3
   * 7. Write Command Mask: Write IBCM.LDSH
   * 8. Demand data transfer to target message buffer: Write IBCR.IBRH[6:0]
   */
  if (LusFirstFIFOBuffer > FR_59_RENESAS_ZERO)
  {
    /* Get the FIFO depth from register */
    LucFIFOdepth = (uint8)LpMBCtrlReg->ulFLXAnFRFCL;                                                                    
    LusFrameCount = FR_59_RENESAS_ZERO;
    LusDataPtrInc = ((uint16)LucPayloadLength / (uint16)FR_59_RENESAS_TWO);
    /* Check if Fr_PayloadLength is a even number */
    if (FR_59_RENESAS_ZERO == (LucPayloadLength % FR_59_RENESAS_TWO))
    {
      /* No action required */
    }
    else
    {
      /* In case of Odd number, round it of to higher value */
      LusDataPtrInc = LusDataPtrInc + FR_59_RENESAS_ONE;                                                                /* PRQA S 3383 # JV-01 */
    }
    do
    {
      /* Initialize the loop count to FR_59_RENESAS_ZERO */
      LusLoopCount = FR_59_RENESAS_ZERO;
      while ((FR_59_RENESAS_FLX0IBCR_FLX0IBSYH_MASK == (LpInputBuffReg->ulFLXAnFRIBCR                                   
               & FR_59_RENESAS_FLX0IBCR_FLX0IBSYH_MASK)) && (LusLoopCount < (uint16)(LpCtrlTable->usFlagClearMaxWait))) /* PRQA S 3415, 3416 # JV-01, JV-01 */
      {
        /* Increment the loop count */
        LusLoopCount++;                                                                                                 /* PRQA S 3387, 3383 # JV-01, JV-01 */
      }
      if (LusLoopCount == (uint16)(LpCtrlTable->usFlagClearMaxWait))                                                    /* PRQA S 3416 # JV-01 */
      {
        LpDemEventId = (P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF,
                                         FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pDemEventId);
        if (FR_59_RENESAS_DEM_NOT_CONFIGURED != LpDemEventId->usReadTimeoutFailure)                                     
        {
          FR_59_RENESAS_DEM_REPORT_ERROR(LpDemEventId->usReadTimeoutFailure, DEM_EVENT_STATUS_FAILED);
        } /* else No Action required */
        /* Set return value */
        LucReturnValue = E_NOT_OK;
        /* Exit the loop */
        LusFrameCount = LucFIFOdepth;
      }
      else
      {
        LulData = FR_59_RENESAS_ZERO;
        /* Write the value of the header into FlexRay Write Header Section Register 1 and mirror address */
        LpInputBuffReg->ulFLXAnFRWRHS1 = LulData;
        /* Get the value of the Payload length configured */
        LulData = ((uint32)((LucPayloadLength)&FR_59_RENESAS_PLC_MASK) << FR_59_RENESAS_PLC_SHIFT);
        /* Write the value of the header into FlexRay Write Header Section Register 2 and mirror address */
        LpInputBuffReg->ulFLXAnFRWRHS2 = LulData;
        /* Get the value of the Data pointer */
        LulData = (LusDataPointer & FR_59_RENESAS_DP_MASK);

        /* Write the value of the Data Pointer header in the FlexRay Write Header
        Section Register 3 */
        LpInputBuffReg->ulFLXAnFRWRHS3 = LulData;
        /* Get the value of the Data pointer */
        LulData = FR_59_RENESAS_FLX0IBCM_FLX0LHSH_MASK;
        /* Write the value of the header into FlexRay Input Buffer Command Mask Register and mirror address */
        LpInputBuffReg->ulFLXAnFRIBCM = LulData;
        /* Get the value of the message buffer configured and load the value in the FRIBCR register */
        LulData = (LusFirstFIFOBuffer & FR_59_RENESAS_FLX0IBCR_FLX0IBRH_MASK);

        /* Write the value of the header into FlexRay Input Buffer Command Request Register and mirror address */
        LpInputBuffReg->ulFLXAnFRIBCR = LulData;
        /* Next Data Pointer Value */
        LusDataPointer = LusDataPointer + LusDataPtrInc;

        /* Get the next Message Buffer */
        LusFirstFIFOBuffer = LusFirstFIFOBuffer + FR_59_RENESAS_ONE;                                                    /* PRQA S 3383 # JV-01 */
      }
      LusFrameCount++;                                                                                                  /* PRQA S 3383 # JV-01 */
    } while (LusFrameCount < LucFIFOdepth);
  } /* else No Action required */
  return (LucReturnValue); /* End of function Fr_59_Renesas_CfgBuffer */
}
#define FR_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_CfgBufferHeader
**
** Service ID            : Not Applicable
**
** Description           : This service calculates the header value for the
**                         frames and loads it in the corresponding header
**                         section register
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx, usFrameHandle, ucPayLoadLength
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : None
**
** Global Variables Used : Fr_59_Renesas_GpControllerConfigPtr,
**                         Fr_59_Renesas_GpCtrlRegSet
**
** Functions Invoked     : FR_59_RENESAS_DEM_REPORT_ERROR,
**                         Fr_59_Renesas_CalHeaderCRC
**
** Registers Used        : FLXAnFRWRHS1, FLXAnFRWRHS2, FLXAnFRWRHS3,
**                         FLXAnFRIBCM, FLXAnFRIBCR
**
** Reference ID          : FR_DUD_ACT_043, FR_DUD_ACT_043_ERR001,
** Reference ID          : FR_DUD_ACT_043_REG001, FR_DUD_ACT_043_REG002,
** Reference ID          : FR_DUD_ACT_043_REG003, FR_DUD_ACT_043_REG004,
** Reference ID          : FR_DUD_ACT_043_REG005
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PRIVATE_CODE)
         Fr_59_Renesas_CfgBufferHeader(const uint8 Fr_CtrlIdx, const uint16 usFrameHandle, const uint8 ucPayLoadLength)
{
  /* Declare pointer to register */
  P2CONST(volatile Fr_59_Renesas_RegisterSetType, AUTOMATIC, FR_CONFIG_DATA) LpCtrlRegSet;
  P2VAR(volatile Fr_59_Renesas_InputBufferRegType, AUTOMATIC, REGSPACE) LpInputBuffReg;
  /* Declare local pointer to CC configuration */
  P2CONST(Fr_59_Renesas_CtrlTableType, TYPEDEF, FR_CONFIG_DATA) LpCtrlTable;
  P2CONST(Fr_59_Renesas_FrameHeaderType, AUTOMATIC, FR_APPL_CONST) LpBufferHeader;
  P2CONST(Fr_59_Renesas_FrameHeaderType, TYPEDEF, FR_CONFIG_DATA) LpFrameConfig;
  /* Declare local pointer to Dem Event Id */
  P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF, FR_CONFIG_DATA) LpDemEventId;
  uint32 LulData;
  Std_ReturnType LucReturnValue;
  volatile uint16 LusLoopCount;
  /* Initialize the default return value */
  LucReturnValue = E_OK;
  /* Copy global pointer to local pointer */
  LpCtrlRegSet = Fr_59_Renesas_GpCtrlRegSet[Fr_CtrlIdx];                                                               
  LpInputBuffReg = (P2VAR(volatile Fr_59_Renesas_InputBufferRegType, AUTOMATIC, 
                                                                               REGSPACE))(LpCtrlRegSet->pInputBuffReg); 
  LpCtrlTable = (P2CONST(Fr_59_Renesas_CtrlTableType, AUTOMATIC,
                                          FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pCtrlTable);
  /* Read the frame pointer */
  LpFrameConfig = Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pFrameConfig;
  LpBufferHeader = &LpFrameConfig[usFrameHandle];                                                                    
  /*
   * Check whether the frame is belong to FIFO.
   */
  if (FR_59_RENESAS_FALSE == LpBufferHeader->blIsFIFOConfig)                                                            
  {
    /* Initialize the loop count to FR_59_RENESAS_ZERO */
    LusLoopCount = FR_59_RENESAS_ZERO;
    while ((FR_59_RENESAS_FLX0IBCR_FLX0IBSYH_MASK == (LpInputBuffReg->ulFLXAnFRIBCR                                     
                         & FR_59_RENESAS_FLX0IBCR_FLX0IBSYH_MASK)) && (LusLoopCount < LpCtrlTable->usFlagClearMaxWait)) /* PRQA S 3415, 3416 # JV-01, JV-01 */
    {
      /* Increment the loop count */
      LusLoopCount++;                                                                                                   /* PRQA S 3383, 3387 # JV-01, JV-01 */
    }
    if (LusLoopCount == (uint16)(LpCtrlTable->usFlagClearMaxWait))                                                      /* PRQA S 3416 # JV-01 */
    {
      LpDemEventId = (P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF,
                                         FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pDemEventId);
      if (FR_59_RENESAS_DEM_NOT_CONFIGURED != LpDemEventId->usReadTimeoutFailure)                                      
      {
        FR_59_RENESAS_DEM_REPORT_ERROR(LpDemEventId->usReadTimeoutFailure, DEM_EVENT_STATUS_FAILED);
      } /* else No Action required */
      LucReturnValue = E_NOT_OK;
    }
    else
    {
      /* Get the frame Id: FID[10:0] bits */
      LulData = ((LpBufferHeader->usFrameId) & FR_59_RENESAS_FID_MASK);
      /* Get the configured cycle code */
      LulData = 
               LulData | ((uint32)((LpBufferHeader->ucCycleCode) & FR_59_RENESAS_CYC_MASK) << FR_59_RENESAS_CYC_SHIFT);
      /* Get the channel configured: CH[1:0] bits */
      LulData =
         LulData | ((uint32)((LpBufferHeader->ucChannelFilter) & FR_59_RENESAS_CHNL_MASK) << FR_59_RENESAS_CHNL_SHIFT);
      /* Get the message buffer configuration bit: CFG bit */
      LulData =
             LulData | ((uint32)((LpBufferHeader->ucFrameConfig) & FR_59_RENESAS_CFG_MASK) << FR_59_RENESAS_CFG_SHIFT);
      /* Get the PPIT bit configured: PPIT bit */
      LulData = LulData | ((uint32)((LpBufferHeader->ucPpit) & FR_59_RENESAS_PPIT_MASK) << FR_59_RENESAS_PPIT_SHIFT);
      /* Get the Transmission mode configured: TXM bit */
      LulData = LulData |
                  ((uint32)((LpBufferHeader->ucTransmissionMode) & FR_59_RENESAS_TXM_MASK) << FR_59_RENESAS_TXM_SHIFT);
      /* Get the message buffer interrupt configured: MBI */
      LulData = LulData |
                ((uint32)((LpBufferHeader->ucMsgBufferInterrupt) & FR_59_RENESAS_MBI_MASK) << FR_59_RENESAS_MBI_SHIFT);
      /* Write the value of the header into FlexRay Write Header Section Register 1 and mirror address */
      Fr_59_Renesas_GpCtrlRegSet[Fr_CtrlIdx]->pInputBuffReg->ulFLXAnFRWRHS1 = LulData;                                  
      /* Calculate the value of header CRC and payload to write to FR_59_RENESAS_FLX0WRHS2 */
      if (ucPayLoadLength == LpBufferHeader->ucPayloadLength)
      {
        /* Get the value of the CRC calculated for the header data */
        LulData = ((LpBufferHeader->usHeaderCrc) & FR_59_RENESAS_CRC_MASK);
        /* Get the value of the Payload length configured */
        LulData =
           LulData | ((uint32)((LpBufferHeader->ucPayloadLength) & FR_59_RENESAS_PLC_MASK) << FR_59_RENESAS_PLC_SHIFT);
      }
      else
      {
        /* Recalculate CRC with input ucPayLoadLength */
        LulData = Fr_59_Renesas_CalHeaderCRC(Fr_CtrlIdx, usFrameHandle, ucPayLoadLength, LpBufferHeader->usFrameId);
        /* Get the value of input ucPayLoadLength */
        LulData = LulData | ((uint32)((ucPayLoadLength)&FR_59_RENESAS_PLC_MASK) << FR_59_RENESAS_PLC_SHIFT);
      }
      /* Write the value of the header into FlexRay Write Header Section Register 2 and mirror address */
      LpInputBuffReg->ulFLXAnFRWRHS2 = LulData;
      /* Get the value of the Data pointer(Frame ID) */
      LulData = ((LpBufferHeader->usDataPointer) & FR_59_RENESAS_DP_MASK);
      /* Write the value of the header into FlexRay Write Header Section Register 3 and mirror address */
      LpInputBuffReg->ulFLXAnFRWRHS3 = LulData;
      /* Load Header Section Host */
      LulData = FR_59_RENESAS_FLX0IBCM_FLX0LHSH_MASK;
      /* Write the value of the header into FlexRay Input Buffer Command Mask Register and mirror address */
      LpInputBuffReg->ulFLXAnFRIBCM = LulData;
      /* Get the value of the message buffer configured and load the value in the FRIBCR register */
      LulData = ((LpBufferHeader->ucMsgBuffer) & FR_59_RENESAS_FLX0IBCR_FLX0IBRH_MASK);

      /* Write the value of the header into FlexRay Input Buffer Command Request Register and mirror address */
      LpInputBuffReg->ulFLXAnFRIBCR = LulData;
    }
  } /* else No Action required */
  return (LucReturnValue); /* End of function Fr_59_Renesas_CfgBufferHeader */
}
#define FR_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_CheckIfCCBusy
**
** Service ID            : Not Applicable
**
** Description           : This functions checks the status of the POC state
**                         busy flag for the maximum wait loop time specified
**                         for the flag to get cleared
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : None
**
** Global Variables Used : Fr_59_Renesas_GpControllerConfigPtr,
**                         Fr_59_Renesas_GpCtrlRegSet
**
** Functions Invoked     : FR_59_RENESAS_DEM_REPORT_ERROR
**
** Registers Used        : FLXAnFRSUCC1
**
** Reference ID          : FR_DUD_ACT_044, FR_DUD_ACT_044_ERR001
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PRIVATE_CODE) Fr_59_Renesas_CheckIfCCBusy(const uint8 Fr_CtrlIdx)
{
  /* Declare pointer to register */
  P2CONST(volatile Fr_59_Renesas_RegisterSetType, AUTOMATIC, FR_CONFIG_DATA) LpCtrlRegSet;
  P2VAR(volatile Fr_59_Renesas_CCControlRegType, AUTOMATIC, REGSPACE) LpCCCtrlReg;                                      /* PRQA S 3678 # JV-01 */
  /* Declare local pointer to CC configuration */
  P2CONST(Fr_59_Renesas_CtrlTableType, TYPEDEF, FR_CONFIG_DATA) LpCtrlTable;
  /* Declare variable to contain return value */
  Std_ReturnType LucReturnValue;
  volatile uint16 LusLoopCount;
  /* Declare local pointer to Dem Event Id */
  P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF, FR_CONFIG_DATA) LpDemEventId;
  LpCtrlTable = (P2CONST(Fr_59_Renesas_CtrlTableType, AUTOMATIC,
                                          FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pCtrlTable);
  /* Initialize the default return value */
  LucReturnValue = E_OK;
  /* Initialize the loop count */
  LusLoopCount = FR_59_RENESAS_ZERO;
  /* Copy global pointer to local pointer */
  LpCtrlRegSet = Fr_59_Renesas_GpCtrlRegSet[Fr_CtrlIdx];                                                               
  LpCCCtrlReg = LpCtrlRegSet->pCCCtrlReg;                                                                               
  while (((LpCCCtrlReg->ulFLXAnFRSUCC1 & FR_59_RENESAS_FLX0SUCC1_FLX0PBSY_MASK) != (uint32)FR_59_RENESAS_ZERO) &&       
                                                           (LusLoopCount < (uint16)(LpCtrlTable->usFlagClearMaxWait)))  /* PRQA S 3415, 3416 # JV-01, JV-01 */
  {
    LusLoopCount++;                                                                                                     /* PRQA S 3387, 3383 # JV-01, JV-01 */
  }
  if (LusLoopCount == (uint16)(LpCtrlTable->usFlagClearMaxWait))                                                        /* PRQA S 3416 # JV-01 */
  {
    /* Cannot access the communication controller */
    LpDemEventId = (P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF,
                                         FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pDemEventId);
    if (FR_59_RENESAS_DEM_NOT_CONFIGURED != LpDemEventId->usReadTimeoutFailure)                                         
    {
      FR_59_RENESAS_DEM_REPORT_ERROR(LpDemEventId->usReadTimeoutFailure, DEM_EVENT_STATUS_FAILED);
    } /* else No Action required */
    LucReturnValue = E_NOT_OK;
  } /* else No Action required */
  return (LucReturnValue); /* End of function Fr_59_Renesas_CheckIfCCBusy */
}
#define FR_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_LoadCfgLowLevelParameters
**
** Service ID            : Not Applicable
**
** Description           : This function loads the reset/configuration values in
**                         the corresponding register
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx, pLowLevelCfgPtr
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : None
**
** Global Variables Used : Fr_59_Renesas_GpCtrlRegSet
**
** Functions Invoked     : None
**
** Registers Used        : FLXAnFREIES, FLXAnFREILS, FLXAnFRFBA, FLXAnFRFCL,
**                         FLXAnFRFRF, FLXAnFRFRFM, FLXAnFRGTUC1, FLXAnFRGTUC10,
**                         FLXAnFRGTUC11, FLXAnFRGTUC2, FLXAnFRGTUC3,
**                         FLXAnFRGTUC4, FLXAnFRGTUC5, FLXAnFRGTUC6,
**                         FLXAnFRGTUC7, FLXAnFRGTUC8, FLXAnFRGTUC9,
**                         FLXAnFRIBA, FLXAnFRILE, FLXAnFRITC,
**                         FLXAnFRMHDC, FLXAnFRMRC, FLXAnFRNEMC, FLXAnFROBA,
**                         FLXAnFROTC, FLXAnFRPRTC1, FLXAnFRPRTC2, FLXAnFRSIES,
**                         FLXAnFRSILS, FLXAnFRSTPW1, FLXAnFRSUCC1,
**                         FLXAnFRSUCC2, FLXAnFRSUCC3
**
** Reference ID          : FR_DUD_ACT_045, FR_DUD_ACT_045_REG001,
** Reference ID          : FR_DUD_ACT_045_REG002, FR_DUD_ACT_045_REG003,
** Reference ID          : FR_DUD_ACT_045_REG004, FR_DUD_ACT_045_REG005,
** Reference ID          : FR_DUD_ACT_045_REG009,
** Reference ID          : FR_DUD_ACT_045_REG010, FR_DUD_ACT_045_REG011,
** Reference ID          : FR_DUD_ACT_045_REG012, FR_DUD_ACT_045_REG013,
** Reference ID          : FR_DUD_ACT_045_REG014, FR_DUD_ACT_045_REG015,
** Reference ID          : FR_DUD_ACT_045_REG016, FR_DUD_ACT_045_REG017,
** Reference ID          : FR_DUD_ACT_045_REG018, FR_DUD_ACT_045_REG019,
** Reference ID          : FR_DUD_ACT_045_REG020, FR_DUD_ACT_045_REG021,
** Reference ID          : FR_DUD_ACT_045_REG022, FR_DUD_ACT_045_REG023,
** Reference ID          : FR_DUD_ACT_045_REG024, FR_DUD_ACT_045_REG025,
** Reference ID          : FR_DUD_ACT_045_REG026, FR_DUD_ACT_045_REG027,
** Reference ID          : FR_DUD_ACT_045_REG028, FR_DUD_ACT_045_REG029,
** Reference ID          : FR_DUD_ACT_045_REG030, FR_DUD_ACT_045_REG031,
** Reference ID          : FR_DUD_ACT_045_REG032, FR_DUD_ACT_045_REG033,
** Reference ID          : FR_DUD_ACT_045_REG034, FR_DUD_ACT_045_REG035,
** Reference ID          : FR_DUD_ACT_045_REG036
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PRIVATE_CODE) Fr_59_Renesas_LoadCfgLowLevelParameters(const uint8 Fr_CtrlIdx,                   
                                                        const Fr_59_Renesas_LowLevelConfSetType *const pLowLevelCfgPtr)
{
  /* Declare pointer to register */
  P2CONST(volatile Fr_59_Renesas_RegisterSetType, AUTOMATIC, FR_CONFIG_DATA) LpCtrlRegSet;
  P2VAR(volatile Fr_59_Renesas_InterruptRegType, AUTOMATIC, REGSPACE) LpIntReg;
  P2VAR(volatile Fr_59_Renesas_TimerRegType, AUTOMATIC, REGSPACE) LpTimerReg;
  P2VAR(volatile Fr_59_Renesas_CCControlRegType, AUTOMATIC, REGSPACE) LpCCCtrlReg;
  P2VAR(volatile Fr_59_Renesas_MessageBufferControlRegType, AUTOMATIC, REGSPACE) LpMBCtrlReg;
  #if ((FR_59_RENESAS_ENABLE_INPUT_TX_HANDLER == STD_ON) || (FR_59_RENESAS_ENABLE_OUTPUT_RX_HANDLER == STD_ON) || \
                                                               (FR_59_RENESAS_ENABLE_OUTPUT_RX_FIFO_HANDLER == STD_ON))
  P2VAR(volatile Fr_59_Renesas_DataTransferControlRegType, AUTOMATIC, REGSPACE) LpDataTransferCtrlReg;
  #endif
  /* Declare the variable to store the return value */
  Std_ReturnType LucReturnValue;

  /* Initialize the default return value */
  LucReturnValue = E_OK;
  /* NULL pointer checking for input parameter */
  if (NULL_PTR == pLowLevelCfgPtr)
  {
    LucReturnValue = E_NOT_OK;
  }
  else
  {
    /* Copy global pointer to local pointer */
    LpCtrlRegSet = Fr_59_Renesas_GpCtrlRegSet[Fr_CtrlIdx];                                                              
    LpIntReg = LpCtrlRegSet->pIntReg;                                                                                   
    LpTimerReg = LpCtrlRegSet->pTimerReg;
    LpCCCtrlReg = LpCtrlRegSet->pCCCtrlReg;
    LpMBCtrlReg = LpCtrlRegSet->pMBCtrlReg;
    #if ((FR_59_RENESAS_ENABLE_INPUT_TX_HANDLER == STD_ON) || (FR_59_RENESAS_ENABLE_OUTPUT_RX_HANDLER == STD_ON) || \
                                                               (FR_59_RENESAS_ENABLE_OUTPUT_RX_FIFO_HANDLER == STD_ON))
    LpDataTransferCtrlReg = LpCtrlRegSet->pDataTransferCtrlReg;
    #endif
    /* Writing into FlexRay Error Interrupt Line Select Register and mirror address */
    LpIntReg->ulFLXAnFREILS = pLowLevelCfgPtr->ulFrErrorIntpLineSelect;                                                 
    /* Writing into FlexRay Status Interrupt Line Select Register and mirror address */
    LpIntReg->ulFLXAnFRSILS = pLowLevelCfgPtr->ulFrStatusIntpLineSelect;
    /* Writing into FlexRay Error Interrupt Enable Set Register and mirror address */
    LpIntReg->ulFLXAnFREIES = pLowLevelCfgPtr->ulFrErrorIntpEnable;
    /* Writing into FlexRay Status Interrupt Enable Set Register and mirror address */
    LpIntReg->ulFLXAnFRSIES = pLowLevelCfgPtr->ulFrStatusIntpEnable;
    /* Writing into FlexRay Interrupt Line Enable Register and mirror address */
    LpIntReg->ulFLXAnFRILE = pLowLevelCfgPtr->ulFrIntpLineEnable;
    /* Writing into FlexRay Stop Watch Register 1 and mirror address */
    LpTimerReg->ulFLXAnFRSTPW1 = pLowLevelCfgPtr->ulFrStopWatchConfig;                                                  
    /* Writing into FlexRay SUC Configuration Register 1 and mirror address */
    LpCCCtrlReg->ulFLXAnFRSUCC1 = pLowLevelCfgPtr->ulFrSUCC1Config;                                                     

    /* Writing into FlexRay SUC Configuration Register 2 and mirror address */
    LpCCCtrlReg->ulFLXAnFRSUCC2 = pLowLevelCfgPtr->ulFrSUCC2Config;

    /* Writing into FlexRay SUC Configuration Register 3 and mirror address */
    LpCCCtrlReg->ulFLXAnFRSUCC3 = pLowLevelCfgPtr->ulFrSUCC3Config;

    /* Writing into FlexRay NEM Configuration Register and mirror address */
    LpCCCtrlReg->ulFLXAnFRNEMC = pLowLevelCfgPtr->ulFrNEMConfig;

    /* Writing into FlexRay PRT Configuration Register 1 and mirror address */
    LpCCCtrlReg->ulFLXAnFRPRTC1 = pLowLevelCfgPtr->ulFrPRTC1Config;

    /* Writing into FlexRay PRT Configuration Register 2 and mirror address */
    LpCCCtrlReg->ulFLXAnFRPRTC2 = pLowLevelCfgPtr->ulFrPRTC2Config;

    /* Writing into FlexRay MHD Configuration Register and mirror address */
    LpCCCtrlReg->ulFLXAnFRMHDC = pLowLevelCfgPtr->ulFrMHDCConfig;

    /* Writing into FlexRay GTU Configuration Register 1 and mirror address */
    LpCCCtrlReg->ulFLXAnFRGTUC1 = pLowLevelCfgPtr->ulFrGTUC1Config;

    /* Writing into FlexRay GTU Configuration Register 2 and mirror address */
    LpCCCtrlReg->ulFLXAnFRGTUC2 = pLowLevelCfgPtr->ulFrGTUC2Config;

    /* Writing into FlexRay GTU Configuration Register 3 and mirror address */
    LpCCCtrlReg->ulFLXAnFRGTUC3 = pLowLevelCfgPtr->ulFrGTUC3Config;

    /* Writing into FlexRay GTU Configuration Register 4 and mirror address */
    LpCCCtrlReg->ulFLXAnFRGTUC4 = pLowLevelCfgPtr->ulFrGTUC4Config;

    /* Writing into FlexRay GTU Configuration Register 5 and mirror address */
    LpCCCtrlReg->ulFLXAnFRGTUC5 = pLowLevelCfgPtr->ulFrGTUC5Config;

    /* Writing into FlexRay GTU Configuration Register 6 and mirror address */
    LpCCCtrlReg->ulFLXAnFRGTUC6 = pLowLevelCfgPtr->ulFrGTUC6Config;

    /* Writing into FlexRay GTU Configuration Register 7 and mirror address */
    LpCCCtrlReg->ulFLXAnFRGTUC7 = pLowLevelCfgPtr->ulFrGTUC7Config;

    /* Writing into FlexRay GTU Configuration Register 8 and mirror address */
    LpCCCtrlReg->ulFLXAnFRGTUC8 = pLowLevelCfgPtr->ulFrGTUC8Config;

    /* Writing into FlexRay GTU Configuration Register 9 and mirror address */
    LpCCCtrlReg->ulFLXAnFRGTUC9 = pLowLevelCfgPtr->ulFrGTUC9Config;

    /* Writing into FlexRay GTU Configuration Register 10 and mirror address */
    LpCCCtrlReg->ulFLXAnFRGTUC10 = pLowLevelCfgPtr->ulFrGTUC10Config;

    /* Writing into FlexRay GTU Configuration Register 11 and mirror address */
    LpCCCtrlReg->ulFLXAnFRGTUC11 = pLowLevelCfgPtr->ulFrGTUC11Config;

    /* Writing into FlexRay Message RAM Configuration Register and mirror address */
    LpMBCtrlReg->ulFLXAnFRMRC = pLowLevelCfgPtr->ulFrMRCConfig;                                                       

    /* Writing into FlexRay FIFO Rejection Filter Register and mirror address */
    LpMBCtrlReg->ulFLXAnFRFRF = pLowLevelCfgPtr->ulFrFRFConfig;

    /* Writing into FlexRay FIFO Rejection Filter Mask Register and mirror address */
    LpMBCtrlReg->ulFLXAnFRFRFM = pLowLevelCfgPtr->ulFrFRFMConfig;

    /* Writing into FlexRay FIFO Critical Level Register and mirror address */
    LpMBCtrlReg->ulFLXAnFRFCL = pLowLevelCfgPtr->ulFrFCLConfig;

    #if (FR_59_RENESAS_ENABLE_INPUT_TX_HANDLER == STD_ON)
    /* Writing into FlexRay Input Transfer Configuration Register and mirror address */
    LpDataTransferCtrlReg->ulFLXAnFRITC = pLowLevelCfgPtr->ulFrInputTxConfReg;                                        

    /* Writing into FlexRay Input pointer table Base Address Register and mirror address */
    LpDataTransferCtrlReg->ulFLXAnFRIBA = pLowLevelCfgPtr->ulFrInpPtrTblBaseAddReg;
    #endif

    #if (FR_59_RENESAS_ENABLE_OUTPUT_RX_HANDLER == STD_ON)
    /* Writing into FlexRay Output pointer table Base Address Register and mirror address */
    LpDataTransferCtrlReg->ulFLXAnFROBA = pLowLevelCfgPtr->ulFrOptPtrTblBaseAddReg;
    #endif
    #if (FR_59_RENESAS_ENABLE_OUTPUT_RX_FIFO_HANDLER == STD_ON)
    /* Writing into FlexRay Output Transfer Configuration Register and mirror address */
    LpDataTransferCtrlReg->ulFLXAnFROTC = pLowLevelCfgPtr->ulFrOutputTxConfReg;

    /* Writing into FlexRay FIFO pointer table Base Address Register and mirror address */
    LpDataTransferCtrlReg->ulFLXAnFRFBA = pLowLevelCfgPtr->ulFrFIFOPtrTblBaseAddReg;
    #endif
  }
  return (LucReturnValue);
} /* End of function Fr_59_Renesas_LoadCfgLowLevelParameters */
#define FR_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_CheckCCConfig
**
** Service ID            : None
**
** Description           : This service shall verify (read back and compare to
**                         reference values held in the configuration) that the
**                         node and cluster FlexRay parameters were written
**                         properly into the FlexRay CC.
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx, pLowLevelCfgPtr
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : None
**
** Global Variables Used : Fr_59_Renesas_GpControllerConfigPtr,
**                         Fr_59_Renesas_GpCtrlRegSet
**
** Functions Invoked     : FR_59_RENESAS_DEM_REPORT_ERROR
**
** Registers Used        : FLXAnFRGTUC1, FLXAnFRGTUC10, FLXAnFRGTUC11,
**                         FLXAnFRGTUC2, FLXAnFRGTUC3, FLXAnFRGTUC4,
**                         FLXAnFRGTUC5, FLXAnFRGTUC6, FLXAnFRGTUC7,
**                         FLXAnFRGTUC8, FLXAnFRGTUC9, FLXAnFRMHDC, FLXAnFRNEMC,
**                         FLXAnFRPRTC1, FLXAnFRPRTC2, FLXAnFRSUCC1,
**                         FLXAnFRSUCC2, FLXAnFRSUCC3
**
** Reference ID          : FR_DUD_ACT_046, FR_DUD_ACT_046_ERR001,
** Reference ID          : FR_DUD_ACT_046_ERR002
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PRIVATE_CODE)
    Fr_59_Renesas_CheckCCConfig(const uint8 Fr_CtrlIdx, const Fr_59_Renesas_LowLevelConfSetType *const pLowLevelCfgPtr) 
{
  /* Declare pointer to register */
  P2CONST(volatile Fr_59_Renesas_RegisterSetType, AUTOMATIC, FR_CONFIG_DATA) LpCtrlRegSet;
  P2VAR(volatile Fr_59_Renesas_CCControlRegType, AUTOMATIC, REGSPACE) LpCCCtrlReg;                                      /* PRQA S 3678 # JV-01 */
  uint32 LulConfiguredData;
  uint32 LulOffSet;
  uint16 LusFrCtrlTestCount;
  uint8 LucRegCnt;
  /* Variable to index for count number */
  uint8 LucCount;
  /* Declare the variable to store the DET return value */
  Std_ReturnType LucReturnValue;
  /* Declare local pointer to Dem Event Id */
  P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF, FR_CONFIG_DATA) LpDemEventId;

  /* Declare Structure contain data from CC */
  VAR (Fr_59_Renesas_ReadDataFromCC, FR_CONFIG_DATA) Fr_ReadDataFromCC[FR_59_RENESAS_EIGHTTEEN]; 

  LpDemEventId = (P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF,
                                         FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pDemEventId);

    /* NULL pointer checking for input parameter */
  if (NULL_PTR == pLowLevelCfgPtr)
  {
    LucReturnValue = E_NOT_OK;
  }
  else
  {
    /* Copy global pointer to local pointer */
    LpCtrlRegSet = Fr_59_Renesas_GpCtrlRegSet[Fr_CtrlIdx];                                                              
    LpCCCtrlReg = LpCtrlRegSet->pCCCtrlReg;                                                                             

    Fr_ReadDataFromCC[FR_59_RENESAS_ZERO].LucRegCnt = FR_59_RENESAS_ZERO;
    Fr_ReadDataFromCC[FR_59_RENESAS_ZERO].LulOffSet = LpCCCtrlReg->ulFLXAnFRSUCC1;                                      
    Fr_ReadDataFromCC[FR_59_RENESAS_ZERO].LulConfiguredData = pLowLevelCfgPtr->ulFrSUCC1Config;

    Fr_ReadDataFromCC[FR_59_RENESAS_ONE].LucRegCnt = FR_59_RENESAS_ONE;
    Fr_ReadDataFromCC[FR_59_RENESAS_ONE].LulOffSet = LpCCCtrlReg->ulFLXAnFRSUCC2;
    Fr_ReadDataFromCC[FR_59_RENESAS_ONE].LulConfiguredData = pLowLevelCfgPtr->ulFrSUCC2Config;

    Fr_ReadDataFromCC[FR_59_RENESAS_TWO].LucRegCnt = FR_59_RENESAS_TWO;
    Fr_ReadDataFromCC[FR_59_RENESAS_TWO].LulOffSet = LpCCCtrlReg->ulFLXAnFRSUCC3;
    Fr_ReadDataFromCC[FR_59_RENESAS_TWO].LulConfiguredData = pLowLevelCfgPtr->ulFrSUCC3Config;

    Fr_ReadDataFromCC[FR_59_RENESAS_THREE].LucRegCnt = FR_59_RENESAS_THREE;
    Fr_ReadDataFromCC[FR_59_RENESAS_THREE].LulOffSet = LpCCCtrlReg->ulFLXAnFRNEMC;
    Fr_ReadDataFromCC[FR_59_RENESAS_THREE].LulConfiguredData = pLowLevelCfgPtr->ulFrNEMConfig;

    Fr_ReadDataFromCC[FR_59_RENESAS_FOUR].LucRegCnt = FR_59_RENESAS_FOUR;
    Fr_ReadDataFromCC[FR_59_RENESAS_FOUR].LulOffSet = LpCCCtrlReg->ulFLXAnFRPRTC1;
    Fr_ReadDataFromCC[FR_59_RENESAS_FOUR].LulConfiguredData = pLowLevelCfgPtr->ulFrPRTC1Config;

    Fr_ReadDataFromCC[FR_59_RENESAS_FIVE].LucRegCnt = FR_59_RENESAS_FIVE;
    Fr_ReadDataFromCC[FR_59_RENESAS_FIVE].LulOffSet = LpCCCtrlReg->ulFLXAnFRPRTC2;
    Fr_ReadDataFromCC[FR_59_RENESAS_FIVE].LulConfiguredData = pLowLevelCfgPtr->ulFrPRTC2Config;

    Fr_ReadDataFromCC[FR_59_RENESAS_SIX].LucRegCnt = FR_59_RENESAS_SIX;
    Fr_ReadDataFromCC[FR_59_RENESAS_SIX].LulOffSet = LpCCCtrlReg->ulFLXAnFRMHDC;
    Fr_ReadDataFromCC[FR_59_RENESAS_SIX].LulConfiguredData = pLowLevelCfgPtr->ulFrMHDCConfig;

    Fr_ReadDataFromCC[FR_59_RENESAS_SEVEN].LucRegCnt = FR_59_RENESAS_SEVEN;
    Fr_ReadDataFromCC[FR_59_RENESAS_SEVEN].LulOffSet = LpCCCtrlReg->ulFLXAnFRGTUC1;
    Fr_ReadDataFromCC[FR_59_RENESAS_SEVEN].LulConfiguredData = pLowLevelCfgPtr->ulFrGTUC1Config;

    Fr_ReadDataFromCC[FR_59_RENESAS_EIGHT].LucRegCnt = FR_59_RENESAS_EIGHT;
    Fr_ReadDataFromCC[FR_59_RENESAS_EIGHT].LulOffSet = LpCCCtrlReg->ulFLXAnFRGTUC2;
    Fr_ReadDataFromCC[FR_59_RENESAS_EIGHT].LulConfiguredData = pLowLevelCfgPtr->ulFrGTUC2Config;

    Fr_ReadDataFromCC[FR_59_RENESAS_NINE].LucRegCnt = FR_59_RENESAS_NINE;
    Fr_ReadDataFromCC[FR_59_RENESAS_NINE].LulOffSet = LpCCCtrlReg->ulFLXAnFRGTUC3;
    Fr_ReadDataFromCC[FR_59_RENESAS_NINE].LulConfiguredData = pLowLevelCfgPtr->ulFrGTUC3Config;

    Fr_ReadDataFromCC[FR_59_RENESAS_TEN].LucRegCnt = FR_59_RENESAS_TEN;
    Fr_ReadDataFromCC[FR_59_RENESAS_TEN].LulOffSet = LpCCCtrlReg->ulFLXAnFRGTUC4;
    Fr_ReadDataFromCC[FR_59_RENESAS_TEN].LulConfiguredData = pLowLevelCfgPtr->ulFrGTUC4Config;

    Fr_ReadDataFromCC[FR_59_RENESAS_ELEVEN].LucRegCnt = FR_59_RENESAS_ELEVEN;
    Fr_ReadDataFromCC[FR_59_RENESAS_ELEVEN].LulOffSet = LpCCCtrlReg->ulFLXAnFRGTUC5;
    Fr_ReadDataFromCC[FR_59_RENESAS_ELEVEN].LulConfiguredData = pLowLevelCfgPtr->ulFrGTUC5Config;

    Fr_ReadDataFromCC[FR_59_RENESAS_TWELVE].LucRegCnt = FR_59_RENESAS_TWELVE;
    Fr_ReadDataFromCC[FR_59_RENESAS_TWELVE].LulOffSet = LpCCCtrlReg->ulFLXAnFRGTUC6;
    Fr_ReadDataFromCC[FR_59_RENESAS_TWELVE].LulConfiguredData = pLowLevelCfgPtr->ulFrGTUC6Config;

    Fr_ReadDataFromCC[FR_59_RENESAS_THIRTEEN].LucRegCnt = FR_59_RENESAS_THIRTEEN;
    Fr_ReadDataFromCC[FR_59_RENESAS_THIRTEEN].LulOffSet = LpCCCtrlReg->ulFLXAnFRGTUC7;
    Fr_ReadDataFromCC[FR_59_RENESAS_THIRTEEN].LulConfiguredData = pLowLevelCfgPtr->ulFrGTUC7Config;

    Fr_ReadDataFromCC[FR_59_RENESAS_FOURTEEN].LucRegCnt = FR_59_RENESAS_FOURTEEN;
    Fr_ReadDataFromCC[FR_59_RENESAS_FOURTEEN].LulOffSet = LpCCCtrlReg->ulFLXAnFRGTUC8;
    Fr_ReadDataFromCC[FR_59_RENESAS_FOURTEEN].LulConfiguredData = pLowLevelCfgPtr->ulFrGTUC8Config;

    Fr_ReadDataFromCC[FR_59_RENESAS_FIFTEEN].LucRegCnt = FR_59_RENESAS_FIFTEEN;
    Fr_ReadDataFromCC[FR_59_RENESAS_FIFTEEN].LulOffSet = LpCCCtrlReg->ulFLXAnFRGTUC9;
    Fr_ReadDataFromCC[FR_59_RENESAS_FIFTEEN].LulConfiguredData = pLowLevelCfgPtr->ulFrGTUC9Config;

    Fr_ReadDataFromCC[FR_59_RENESAS_SIXTEEN].LucRegCnt = FR_59_RENESAS_SIXTEEN;
    Fr_ReadDataFromCC[FR_59_RENESAS_SIXTEEN].LulOffSet = LpCCCtrlReg->ulFLXAnFRGTUC10;
    Fr_ReadDataFromCC[FR_59_RENESAS_SIXTEEN].LulConfiguredData = pLowLevelCfgPtr->ulFrGTUC10Config;

    Fr_ReadDataFromCC[FR_59_RENESAS_SEVENTEEN].LucRegCnt = FR_59_RENESAS_SEVENTEEN;
    Fr_ReadDataFromCC[FR_59_RENESAS_SEVENTEEN].LulOffSet = LpCCCtrlReg->ulFLXAnFRGTUC11;
    Fr_ReadDataFromCC[FR_59_RENESAS_SEVENTEEN].LulConfiguredData = pLowLevelCfgPtr->ulFrGTUC11Config;

    LucRegCnt = FR_59_RENESAS_ZERO;

    do
    {
      LusFrCtrlTestCount = FR_59_RENESAS_ZERO;
      do
      {
        for (LucCount = (uint8)FR_59_RENESAS_ZERO; LucCount <= (uint8)FR_59_RENESAS_SEVENTEEN; LucCount++)
        { /* Check value of structure with input value */
          if (Fr_ReadDataFromCC[LucCount].LucRegCnt == LucRegCnt)
          {
            LulOffSet = Fr_ReadDataFromCC[LucCount].LulOffSet;
            LulConfiguredData = Fr_ReadDataFromCC[LucCount].LulConfiguredData;
          } /* else No Action required */
        }
        if (FR_59_RENESAS_ZERO == LucRegCnt)
        {
          /* Mask the CMD Command Bits and PBSY bits in FLXnSUCC1 */
          LulOffSet = LulOffSet & FR_59_RENESAS_FLX0SUCC1_FLX0_PBSY_CMD_MASK;                                           /* PRQA S 2962 # JV-01 */
        } /* else No Action required */
        if (FR_59_RENESAS_FOUR == LucRegCnt)
        {
          /* FLXnCASM06 is fixed to 1 */
          LulConfiguredData = LulConfiguredData | FR_59_RENESAS_FLX0PRTC1_FLX0CASM_MASK;                                /* PRQA S 2962 # JV-01 */
        } /* else No Action required */
        if (LulOffSet == LulConfiguredData)                                                                             /* PRQA S 2962 # JV-01 */
        {
          LucReturnValue = E_OK;
          /* Break the loop */
          LusFrCtrlTestCount = (uint16)FR_59_RENESAS_CTRL_TEST_COUNT + (uint16)FR_59_RENESAS_ONE;
        }
        else
        {
          LucReturnValue = E_NOT_OK;
          LusFrCtrlTestCount++;                                                                                         /* PRQA S 3383 # JV-01 */
        }
      } while ((uint16)FR_59_RENESAS_CTRL_TEST_COUNT >= LusFrCtrlTestCount);
      if (E_NOT_OK == LucReturnValue)
      {
        /* Break the while loop */
        LucRegCnt = FR_59_RENESAS_EIGHTTEEN;
      }
      else
      {
        LucRegCnt++;                                                                                                    /* PRQA S 3383 # JV-01 */
      }
    } while (FR_59_RENESAS_SEVENTEEN >= LucRegCnt);
  }
  if (E_OK == LucReturnValue)
  {
    /* Raise DEM Error PASSED */
    if (FR_59_RENESAS_DEM_NOT_CONFIGURED != LpDemEventId->usHardwareTestFailure)                                        
    {
      FR_59_RENESAS_DEM_REPORT_ERROR(LpDemEventId->usHardwareTestFailure, DEM_EVENT_STATUS_PASSED);
    } /* else No Action required */
  }
  else
  {
    /* Raise DEM Error FAILED */
    if (FR_59_RENESAS_DEM_NOT_CONFIGURED != LpDemEventId->usHardwareTestFailure)
    {
      FR_59_RENESAS_DEM_REPORT_ERROR(LpDemEventId->usHardwareTestFailure, DEM_EVENT_STATUS_FAILED);
    } /* else No Action required */
    LucReturnValue = E_NOT_OK;
  } /* else No Action required */
  return (LucReturnValue);
} /* End of function Fr_59_Renesas_CheckCCConfig */
#define FR_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_CalHeaderCRC
**
** Service ID            : None
**
** Description           : This service shall calculates header CRC value.
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx, usFrameHandle, ucPayLoadLength, ucFrameId
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : uint16
**
** Preconditions         : None
**
** Global Variables Used : Fr_59_Renesas_GpCtrlRegSet,
**                         Fr_59_Renesas_GpControllerConfigPtr
**
** Functions Invoked     : None
**
** Registers Used        : FLXAnFRMRC, FLXAnFRSUCC1
**
** Reference ID          : FR_DUD_ACT_047
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(uint16, FR_PRIVATE_CODE)
Fr_59_Renesas_CalHeaderCRC(const uint8 Fr_CtrlIdx, const uint16 usFrameHandle, const uint8 ucPayLoadLength,
                                                                                                const uint16 ucFrameId)
{
  /* Declare pointer to register */
  P2CONST(volatile Fr_59_Renesas_RegisterSetType, AUTOMATIC, FR_CONFIG_DATA) LpCtrlRegSet;
  P2VAR(volatile Fr_59_Renesas_MessageBufferControlRegType, AUTOMATIC, REGSPACE) LpMBCtrlReg;                           /* PRQA S 3678 # JV-01 */
  P2VAR(volatile Fr_59_Renesas_CCControlRegType, AUTOMATIC, REGSPACE) LpCCCtrlReg;                                      /* PRQA S 3678 # JV-01 */
  uint32 LulHeaderCRCVal;
  uint32 LulHeaderCRCRegVal;
  uint32 LulSyncbit;
  uint32 LulStartupbit;
  P2CONST(Fr_59_Renesas_FrameHeaderType, AUTOMATIC, FR_APPL_CONST) LpBufferHeader;
  P2CONST(Fr_59_Renesas_FrameHeaderType, TYPEDEF, FR_CONFIG_DATA) LpFrameConfig;
  uint8 LucHeaderLength;
  uint8 LucCrcNext;
  LulSyncbit = FR_59_RENESAS_ZERO;
  LulStartupbit = FR_59_RENESAS_ZERO;
  /* Copy global pointer to local pointer */
  LpCtrlRegSet = Fr_59_Renesas_GpCtrlRegSet[Fr_CtrlIdx];                                                                
  LpCCCtrlReg = LpCtrlRegSet->pCCCtrlReg;                                                                               
  LpMBCtrlReg = LpCtrlRegSet->pMBCtrlReg;
  /* Read the frame pointer */
  LpFrameConfig = Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pFrameConfig;
  LpBufferHeader = &LpFrameConfig[usFrameHandle];                                                                      
  LucHeaderLength = FR_59_RENESAS_HEADER_LENGTH;
  LulHeaderCRCRegVal = FR_59_RENESAS_HCRC_REG;
  /* Check whether the frame is startup and sync frame */
  if (((FR_59_RENESAS_ZERO == LpBufferHeader->ucMsgBuffer) || (FR_59_RENESAS_ONE == LpBufferHeader->ucMsgBuffer)) &&    
    (FR_59_RENESAS_SPLM_MASK == (((LpMBCtrlReg->ulFLXAnFRMRC) >> FR_59_RENESAS_SPLM_SHIFT) & FR_59_RENESAS_SPLM_MASK))) 

  {
    LulSyncbit = ((LpCCCtrlReg->ulFLXAnFRSUCC1) >> FR_59_RENESAS_TXSY_SHIFT) & FR_59_RENESAS_TXSY_MASK;                 
    LulStartupbit = ((LpCCCtrlReg->ulFLXAnFRSUCC1) >> FR_59_RENESAS_TXST_SHIFT) & FR_59_RENESAS_TXST_MASK;
  } /* else No Action required */
  /* Calculate the header value for the frame arg_FrameNum */
  LulHeaderCRCVal = (LulSyncbit << FR_59_RENESAS_SYNC_BIT_SHIFT);
  LulHeaderCRCVal = LulHeaderCRCVal | (LulStartupbit << FR_59_RENESAS_STARTUP_BIT_SHIFT);
  LulHeaderCRCVal = LulHeaderCRCVal | ((uint32)ucFrameId << FR_59_RENESAS_FRAME_ID_SHIFT);
  LulHeaderCRCVal = LulHeaderCRCVal | (uint32)ucPayLoadLength;
  LulHeaderCRCVal = LulHeaderCRCVal << FR_59_RENESAS_HEADER_SHIFT;
  /* Calculate the header CRC value for the frame */
  while (LucHeaderLength > FR_59_RENESAS_ZERO)
  {
    LulHeaderCRCVal = LulHeaderCRCVal << FR_59_RENESAS_HEADER_DATA_SHIFT;
    if ((uint32)FR_59_RENESAS_ZERO != ((LulHeaderCRCVal ^ LulHeaderCRCRegVal) & FR_59_RENESAS_HEADER_DATA_MASK))
    {
      LucCrcNext = FR_59_RENESAS_ONE;
    }
    else
    {
      LucCrcNext = FR_59_RENESAS_ZERO;
    }
    LulHeaderCRCRegVal = LulHeaderCRCRegVal << FR_59_RENESAS_CRC_REG_DATA_SHIFT;
    if (FR_59_RENESAS_ONE == LucCrcNext)
    {
      LulHeaderCRCRegVal = LulHeaderCRCRegVal ^ FR_59_RENESAS_CRC_POLYNOMIAL;
    } /* else No Action required */
    LucHeaderLength = LucHeaderLength - FR_59_RENESAS_ONE;
  } /* End of while */
  LulHeaderCRCRegVal = LulHeaderCRCRegVal >> FR_59_RENESAS_HCRC_REG_SHIFT;
  /* Return the value of header to be loaded in register FR_23_FLX0WRHS2 */
  return ((uint16)LulHeaderCRCRegVal);
  /* End of function Fr_59_Renesas_CalHeaderCRC */
}
#define FR_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_OperationEnable
**
** Service ID            : Not Applicable
**
** Description           : This function enables the operation of FlexRay
**                         by writing to Operation Control Register
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : None
**
** Global Variables Used : Fr_59_Renesas_GpControllerConfigPtr,
**                         Fr_59_Renesas_GpCtrlRegSet
**
** Functions Invoked     : FR_59_RENESAS_DEM_REPORT_ERROR
**
** Registers Used        : FLXAnFROS, FLXAnFROC
**
** Reference ID          : FR_DUD_ACT_048, FR_DUD_ACT_048_ERR001,
** Reference ID          : FR_DUD_ACT_048_REG001, FR_DUD_ACT_048_REG002,
** Reference ID          : FR_DUD_ACT_048_REG003
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PRIVATE_CODE) Fr_59_Renesas_OperationEnable(const uint8 Fr_CtrlIdx)                             
{
  /* Declare pointer to register */
  P2CONST(volatile Fr_59_Renesas_RegisterSetType, AUTOMATIC, FR_CONFIG_DATA) LpCtrlRegSet;
  P2VAR(volatile Fr_59_Renesas_OperationRegType, AUTOMATIC, REGSPACE) LpFROReg;
  /* Declare local pointer to CC configuration */
  P2CONST(Fr_59_Renesas_CtrlTableType, TYPEDEF, FR_CONFIG_DATA) LpCtrlTable;
  /* Declare variable to contain return value */
  Std_ReturnType LucReturnValue;
  uint32 LulData;
  volatile uint16 LusLoopCount;
  /* Declare local pointer to Dem Event Id */
  P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF, FR_CONFIG_DATA) LpDemEventId;
  LpCtrlTable = (P2CONST(Fr_59_Renesas_CtrlTableType, AUTOMATIC,
                                          FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pCtrlTable);
  /* Initialize the return value */
  LucReturnValue = E_OK;
  /* Copy global pointer to local pointer */
  LpCtrlRegSet = Fr_59_Renesas_GpCtrlRegSet[Fr_CtrlIdx];                                                                
  LpFROReg = LpCtrlRegSet->pFROReg;                                                                                     

  /* Check if CC Operation status is disable */
  LulData = LpFROReg->ulFLXAnFROS;                                                                                     
  if ((uint32)FR_59_RENESAS_ZERO == (LulData & FR_59_RENESAS_FLX0FROS_OS_MASK))
  {
    /* Reset OEP bit in FLX0FROC register to set OE bit is unprotected */
    LpFROReg->ulFLXAnFROC = FR_59_RENESAS_FLX0FROC_OEP_RESET;
    /* Set OE bit to set FlexRay module as Operation Enabled */
    LpFROReg->ulFLXAnFROC = FR_59_RENESAS_FLX0FROC_OE_SET;
    /* Initialize the loop count */
    LusLoopCount = FR_59_RENESAS_ZERO;
    do
    {
      LulData = LpFROReg->ulFLXAnFROS;
      if (LusLoopCount == (uint16)(LpCtrlTable->usFlagClearMaxWait))                                                   /* PRQA S 3416 # JV-01 */             
      {
        LpDemEventId = (P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF,
                                         FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pDemEventId);
        if (FR_59_RENESAS_DEM_NOT_CONFIGURED != LpDemEventId->usReadTimeoutFailure)                                     
        {
          FR_59_RENESAS_DEM_REPORT_ERROR(LpDemEventId->usReadTimeoutFailure, DEM_EVENT_STATUS_FAILED);
        } /* else No Action required */
        LucReturnValue = E_NOT_OK;
      } /* else No Action required */
      LusLoopCount++;                                                                                                   /* PRQA S 3383, 3387 # JV-01, JV-01 */
      /* Check for the operation status bit */
    } while (((uint32)FR_59_RENESAS_ONE != (LulData & FR_59_RENESAS_FLX0FROS_OS_MASK)) && (E_OK == LucReturnValue));
    /* Get the value of the register FR_59_RENESAS_FLX0FROC */
    LulData = LpFROReg->ulFLXAnFROC;
    LulData = LulData | FR_59_RENESAS_FLX0FROC_OEP_SET;
    /* Disable the operation protection bit */
    LpFROReg->ulFLXAnFROC = LulData;
  } /* else No Action required */
  return (LucReturnValue); /* End of function Fr_59_Renesas_OperationEnable */
}
#define FR_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_GetPOCStsFlag
**
** Service ID            : Not Applicable
**
** Description           : This function gets Protocol Operation Control
**                        Status Flags from FlexRay CC Status Vector Register
**
** Sync/Async            : Asynchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : uint32
**
** Preconditions         : None
**
** Global Variables Used : Fr_59_Renesas_GpCtrlRegSet
**
** Functions Invoked     : None.
**
** Registers Used        : FLXAnFRCCSV
**
** Reference ID          : FR_DUD_ACT_049
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(uint32, FR_PRIVATE_CODE) Fr_59_Renesas_GetPOCStsFlag(const uint8 Fr_CtrlIdx)
{
  /* Declare pointer to register */
  P2CONST(volatile Fr_59_Renesas_RegisterSetType, AUTOMATIC, FR_CONFIG_DATA) LpCtrlRegSet;
  P2VAR(volatile Fr_59_Renesas_CCStatusRegType, AUTOMATIC, REGSPACE) LpCCStatusReg;                                     /* PRQA S 3678 # JV-01 */

  /* Declare the variable to store the register value */
  uint32 LulData;
  /* Initialize value stored at register */
  LulData = FR_59_RENESAS_ZERO;                                                                                         /* PRQA S 2982 # JV-01 */
  /* Copy global pointer to local pointer */
  LpCtrlRegSet = Fr_59_Renesas_GpCtrlRegSet[Fr_CtrlIdx];                                                                
  LpCCStatusReg = LpCtrlRegSet->pCCStatusReg;                                                                           
  /* Read POC status from FlexRay CC Status Vector Register */
  LulData = (LpCCStatusReg->ulFLXAnFRCCSV) & FR_59_RENESAS_FLX0CCSV_FLX0POCS_MASK;                                      
  /* Return the value */
  return (LulData);
} /* End of function Fr_59_Renesas_GetPOCStsFlag */
#define FR_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_UpdatePOCSts
**
** Service ID            : Not Applicable
**
** Description           : This function updates Freeze, Halt request,
**                        Cold Start FlexRay CC Status Vector Register
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx
**
** InOut Parameters      : None
**
** Output Parameters     : Fr_POCStatusPtr
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : None
**
** Global Variables Used : Fr_59_Renesas_GpControllerConfigPtr,
**                         Fr_59_Renesas_GpCtrlRegSet
**
** Functions Invoked     : FR_59_RENESAS_DEM_REPORT_ERROR
**
** Registers Used        : FLXAnFRCCSV, FLXAnFRCCEV
**
** Reference ID          : FR_DUD_ACT_050, FR_DUD_ACT_050_ERR001,
** Reference ID          : FR_DUD_ACT_050_ERR002, FR_DUD_ACT_050_ERR003
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PRIVATE_CODE)
                            Fr_59_Renesas_UpdatePOCSts(const uint8 Fr_CtrlIdx, Fr_POCStatusType *const Fr_POCStatusPtr) 
{
  /* Declare pointer to register */
  P2CONST(volatile Fr_59_Renesas_RegisterSetType, AUTOMATIC, FR_CONFIG_DATA) LpCtrlRegSet;
  P2VAR(volatile Fr_59_Renesas_CCStatusRegType, AUTOMATIC, REGSPACE) LpCCStatusReg;                                     /* PRQA S 3678 # JV-01 */
  static VAR(Fr_Renesas_CheckPOCSts,FR_CONFIG_DATA) Fr_CheckPOCStates[FR_59_RENESAS_TWENTYONE];
  /* Declare the variable to store the return value */
  Std_ReturnType LucReturnValue;
  uint32 LulData;
  /* Declare local pointer to Dem Event Id */
  P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF, FR_CONFIG_DATA) LpDemEventId;
  /* Variable to index for count number */
  uint8 LucCount;

  /* Default config state*/
  Fr_CheckPOCStates[FR_59_RENESAS_ZERO].LulData = FR_59_RENESAS_DEFAULT_CONFIG_STATE;
  Fr_CheckPOCStates[FR_59_RENESAS_ZERO].LpState = FR_POCSTATE_DEFAULT_CONFIG;
  Fr_CheckPOCStates[FR_59_RENESAS_ZERO].LpStartupState = FR_STARTUP_UNDEFINED;
  /* Ready state*/
  Fr_CheckPOCStates[FR_59_RENESAS_ONE].LulData = FR_59_RENESAS_READY_STATE;
  Fr_CheckPOCStates[FR_59_RENESAS_ONE].LpState = FR_POCSTATE_READY;
  Fr_CheckPOCStates[FR_59_RENESAS_ONE].LpStartupState = FR_STARTUP_UNDEFINED;
  /* Normal active state*/
  Fr_CheckPOCStates[FR_59_RENESAS_TWO].LulData = FR_59_RENESAS_NORMAL_ACTIVE_STATE;
  Fr_CheckPOCStates[FR_59_RENESAS_TWO].LpState = FR_POCSTATE_NORMAL_ACTIVE;
  Fr_CheckPOCStates[FR_59_RENESAS_TWO].LpStartupState = FR_STARTUP_UNDEFINED;
  /* Normal passive state*/
  Fr_CheckPOCStates[FR_59_RENESAS_THREE].LulData = FR_59_RENESAS_NORMAL_PASSIVE_STATE;
  Fr_CheckPOCStates[FR_59_RENESAS_THREE].LpState = FR_POCSTATE_NORMAL_PASSIVE;
  Fr_CheckPOCStates[FR_59_RENESAS_THREE].LpStartupState = FR_STARTUP_UNDEFINED;
  /* Halt State */
  Fr_CheckPOCStates[FR_59_RENESAS_FOUR].LulData = FR_59_RENESAS_HALT_STATE;
  Fr_CheckPOCStates[FR_59_RENESAS_FOUR].LpState = FR_POCSTATE_HALT;
  Fr_CheckPOCStates[FR_59_RENESAS_FOUR].LpStartupState = FR_STARTUP_UNDEFINED;
  /* Config State */
  Fr_CheckPOCStates[FR_59_RENESAS_FIVE].LulData = FR_59_RENESAS_CONFIG_STATE;
  Fr_CheckPOCStates[FR_59_RENESAS_FIVE].LpState = FR_POCSTATE_CONFIG;
  Fr_CheckPOCStates[FR_59_RENESAS_FIVE].LpStartupState = FR_STARTUP_UNDEFINED;
  /* Wakeup Standby State */
  Fr_CheckPOCStates[FR_59_RENESAS_SIX].LulData = FR_59_RENESAS_WAKEUP_STANDBY_STATE;
  Fr_CheckPOCStates[FR_59_RENESAS_SIX].LpState = FR_POCSTATE_WAKEUP;
  Fr_CheckPOCStates[FR_59_RENESAS_SIX].LpStartupState = FR_STARTUP_UNDEFINED;
  /* Wakeup Listen State */
  Fr_CheckPOCStates[FR_59_RENESAS_SEVEN].LulData = FR_59_RENESAS_WAKEUP_LISTEN_STATE;
  Fr_CheckPOCStates[FR_59_RENESAS_SEVEN].LpState = FR_POCSTATE_WAKEUP;
  Fr_CheckPOCStates[FR_59_RENESAS_SEVEN].LpStartupState = FR_STARTUP_UNDEFINED;
  /* Wakeup Send State */
  Fr_CheckPOCStates[FR_59_RENESAS_EIGHT].LulData = FR_59_RENESAS_WAKEUP_SEND_STATE;
  Fr_CheckPOCStates[FR_59_RENESAS_EIGHT].LpState = FR_POCSTATE_WAKEUP;
  Fr_CheckPOCStates[FR_59_RENESAS_EIGHT].LpStartupState = FR_STARTUP_UNDEFINED;
  /* Wakeup Detect State */
  Fr_CheckPOCStates[FR_59_RENESAS_NINE].LulData = FR_59_RENESAS_WAKEUP_DETECT_STATE;
  Fr_CheckPOCStates[FR_59_RENESAS_NINE].LpState = FR_POCSTATE_WAKEUP;
  Fr_CheckPOCStates[FR_59_RENESAS_NINE].LpStartupState = FR_STARTUP_UNDEFINED;
  /* Startup Prepare State */
  Fr_CheckPOCStates[FR_59_RENESAS_TEN].LulData = FR_59_RENESAS_STARTUP_PREPARE_STATE;
  Fr_CheckPOCStates[FR_59_RENESAS_TEN].LpState = FR_POCSTATE_STARTUP;
  Fr_CheckPOCStates[FR_59_RENESAS_TEN].LpStartupState = FR_STARTUP_UNDEFINED;
  /* Coldstart Listen State */
  Fr_CheckPOCStates[FR_59_RENESAS_ELEVEN].LulData = FR_59_RENESAS_COLDSTART_LISTEN_STATE;
  Fr_CheckPOCStates[FR_59_RENESAS_ELEVEN].LpState = FR_POCSTATE_STARTUP;
  Fr_CheckPOCStates[FR_59_RENESAS_ELEVEN].LpStartupState = FR_STARTUP_COLDSTART_LISTEN;
  /* Coldstart Collision Resolution State */
  Fr_CheckPOCStates[FR_59_RENESAS_TWELVE].LulData = FR_59_RENESAS_COLDSTART_COLLISION_RESOLUTION_STATE;
  Fr_CheckPOCStates[FR_59_RENESAS_TWELVE].LpState = FR_POCSTATE_STARTUP;
  Fr_CheckPOCStates[FR_59_RENESAS_TWELVE].LpStartupState = FR_STARTUP_COLDSTART_COLLISION_RESOLUTION;
  /* Coldstart Consistency Check State */
  Fr_CheckPOCStates[FR_59_RENESAS_THIRTEEN].LulData = FR_59_RENESAS_COLDSTART_CONSISTENCY_CHECK_STATE;
  Fr_CheckPOCStates[FR_59_RENESAS_THIRTEEN].LpState = FR_POCSTATE_STARTUP;
  Fr_CheckPOCStates[FR_59_RENESAS_THIRTEEN].LpStartupState = FR_STARTUP_COLDSTART_CONSISTENCY_CHECK;
  /* Coldstart State */
  Fr_CheckPOCStates[FR_59_RENESAS_FOURTEEN].LulData = FR_59_RENESAS_COLDSTART_GAP_STATE;
  Fr_CheckPOCStates[FR_59_RENESAS_FOURTEEN].LpState = FR_POCSTATE_STARTUP;
  Fr_CheckPOCStates[FR_59_RENESAS_FOURTEEN].LpStartupState = FR_STARTUP_COLDSTART_GAP;
  /* Coldstart Join State */
  Fr_CheckPOCStates[FR_59_RENESAS_FIFTEEN].LulData = FR_59_RENESAS_COLDSTART_JOIN_STATE;
  Fr_CheckPOCStates[FR_59_RENESAS_FIFTEEN].LpState = FR_POCSTATE_STARTUP;
  Fr_CheckPOCStates[FR_59_RENESAS_FIFTEEN].LpStartupState = FR_STARTUP_COLDSTART_JOIN;
  /* Integration Coldstart Check State */
  Fr_CheckPOCStates[FR_59_RENESAS_SIXTEEN].LulData = FR_59_RENESAS_INTEGRATION_COLDSTART_CHECK_STATE;
  Fr_CheckPOCStates[FR_59_RENESAS_SIXTEEN].LpState = FR_POCSTATE_STARTUP;
  Fr_CheckPOCStates[FR_59_RENESAS_SIXTEEN].LpStartupState = FR_STARTUP_INTEGRATION_COLDSTART_CHECK;
  /* Integration Listen State */
  Fr_CheckPOCStates[FR_59_RENESAS_SEVENTEEN].LulData = FR_59_RENESAS_INTEGRATION_LISTEN_STATE;
  Fr_CheckPOCStates[FR_59_RENESAS_SEVENTEEN].LpState = FR_POCSTATE_STARTUP;
  Fr_CheckPOCStates[FR_59_RENESAS_SEVENTEEN].LpStartupState = FR_STARTUP_INTEGRATION_LISTEN;
  /* Integration Consistency Check State */
  Fr_CheckPOCStates[FR_59_RENESAS_EIGHTTEEN].LulData = FR_59_RENESAS_INTEGRATION_CONSISTENCY_CHECK_STATE;
  Fr_CheckPOCStates[FR_59_RENESAS_EIGHTTEEN].LpState = FR_POCSTATE_STARTUP;
  Fr_CheckPOCStates[FR_59_RENESAS_EIGHTTEEN].LpStartupState = FR_STARTUP_INTEGRATION_CONSISTENCY_CHECK;
  /* Initialize Schedule State */
  Fr_CheckPOCStates[FR_59_RENESAS_NINETEEN].LulData = FR_59_RENESAS_INITIALIZE_SCHEDULE_STATE;
  Fr_CheckPOCStates[FR_59_RENESAS_NINETEEN].LpState = FR_POCSTATE_STARTUP;
  Fr_CheckPOCStates[FR_59_RENESAS_NINETEEN].LpStartupState = FR_STARTUP_INITIALIZE_SCHEDULE;
  /* Abort Startup State */
  Fr_CheckPOCStates[FR_59_RENESAS_TWENTY].LulData = FR_59_RENESAS_ABORT_STARTUP_STATE;
  Fr_CheckPOCStates[FR_59_RENESAS_TWENTY].LpState = FR_POCSTATE_STARTUP;
  Fr_CheckPOCStates[FR_59_RENESAS_TWENTY].LpStartupState = FR_STARTUP_UNDEFINED;
  
  /* Initialize the return value */
  LucReturnValue = E_NOT_OK;

  LpDemEventId = (P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF,
                                         FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pDemEventId);
  LpCtrlRegSet = Fr_59_Renesas_GpCtrlRegSet[Fr_CtrlIdx];                                                                
  LpCCStatusReg = LpCtrlRegSet->pCCStatusReg;                                                                           
  /* Read the POC State by getting FLX0CCSV register value */
  LulData = LpCCStatusReg->ulFLXAnFRCCSV;                                                                               
  /* CHIReadyRequest is set to OFF (parameter not present in FlexRay Version 2.1 Revision A) */
  Fr_POCStatusPtr->CHIReadyRequest = FR_59_RENESAS_FALSE;                                                               
  /* Update WakeupStatus with curent value of WSV[2:0] */
  Fr_POCStatusPtr->WakeupStatus =
        (Fr_WakeupStatusType)((LulData & FR_59_RENESAS_FLX0CCSV_FLX0WSV_MASK) >> FR_59_RENESAS_FLX0CCSV_FLX0WSV_SHIFT); /* PRQA S 4394, 4342 # JV-01, JV-01 */

  for (LucCount = (uint8)FR_59_RENESAS_ZERO; LucCount < (uint8)FR_59_RENESAS_TWENTYONE; LucCount++)
  {
    if (Fr_CheckPOCStates[LucCount].LulData == (uint32)(LulData & FR_59_RENESAS_FLX0CCSV_FLX0POCS_MASK))
    {
      Fr_POCStatusPtr->State = Fr_CheckPOCStates[LucCount].LpState;
      Fr_POCStatusPtr->StartupState = Fr_CheckPOCStates[LucCount].LpStartupState; 
      LucReturnValue = E_OK;
    } /* else No Action required */
  }
  if ((FR_59_RENESAS_DEM_NOT_CONFIGURED != LpDemEventId->usHardwareTestFailure) && (E_NOT_OK == LucReturnValue))        
  {
    FR_59_RENESAS_DEM_REPORT_ERROR(LpDemEventId->usHardwareTestFailure, DEM_EVENT_STATUS_FAILED);
    LucReturnValue = E_NOT_OK;
  } /* else No Action required */
  /* Check if the return value is E_OK */
  if (E_OK == LucReturnValue)
  {
    /* Confirmation of Freeze Status Indicator */
    if (FR_59_RENESAS_FLX0CCSV_FLX0FSI_MASK == (LulData & FR_59_RENESAS_FLX0CCSV_FLX0FSI_MASK))
    {
      /* Update the parameter freeze of statusptr */
      Fr_POCStatusPtr->Freeze = FR_59_RENESAS_TRUE;
    }
    else
    {
      /* Update the parameter freeze of statusptr */
      Fr_POCStatusPtr->Freeze = FR_59_RENESAS_FALSE;
    }
    /* Confirmation of Halt Request */
    if (FR_59_RENESAS_FLX0CCSV_FLX0HRQ_MASK == (LulData & FR_59_RENESAS_FLX0CCSV_FLX0HRQ_MASK))
    {
      Fr_POCStatusPtr->CHIHaltRequest = FR_59_RENESAS_TRUE;
    }
    else
    {
      Fr_POCStatusPtr->CHIHaltRequest = FR_59_RENESAS_FALSE;
    }
    /* Confirmation of Coldstart Noise Indicator */
    if (FR_59_RENESAS_FLX0CCSV_FLX0CSNI_MASK == (LulData & FR_59_RENESAS_FLX0CCSV_FLX0CSNI_MASK))
    {
      Fr_POCStatusPtr->ColdstartNoise = FR_59_RENESAS_TRUE;
    }
    else
    {
      Fr_POCStatusPtr->ColdstartNoise = FR_59_RENESAS_FALSE;
    }
    /* Confirmation of Slot Mode */
    switch ((uint8)((LulData & FR_59_RENESAS_FLX0CCSV_FLX0SLM_MASK) >> FR_59_RENESAS_FLX0CCSV_FLX0SLM_SHIFT))
    {
    case FR_59_RENESAS_SLM_SINGLE:
      Fr_POCStatusPtr->SlotMode = FR_SLOTMODE_KEYSLOT;
      break;
    case FR_59_RENESAS_SLM_ALL_PENDING:
      Fr_POCStatusPtr->SlotMode = FR_SLOTMODE_ALL_PENDING;
      break;
    case FR_59_RENESAS_SLM_ALL:
      Fr_POCStatusPtr->SlotMode = FR_SLOTMODE_ALL;
      break;
    default:
      if (FR_59_RENESAS_DEM_NOT_CONFIGURED != LpDemEventId->usHardwareTestFailure)
      {
        FR_59_RENESAS_DEM_REPORT_ERROR(LpDemEventId->usHardwareTestFailure, DEM_EVENT_STATUS_FAILED);
      } /* else No Action required */
      LucReturnValue = E_NOT_OK;
      break;
    }
    /* Check if the return value is E_OK */
    if (E_OK == LucReturnValue)
    {
      /* Confirmation of Error Mode */
      LulData = LpCCStatusReg->ulFLXAnFRCCEV;
      /* Check for the error mode */
      switch ((uint8)((LulData & FR_59_RENESAS_FLX0CCEV_FLX0ERRM_MASK) >> FR_59_RENESAS_FLX0CCEV_FLX0ERRM_SHIFT))
      {
      case FR_59_RENESAS_ERRM_ACTIVE:
        Fr_POCStatusPtr->ErrorMode = FR_ERRORMODE_ACTIVE;
        break;
      case FR_59_RENESAS_ERRM_PASSIVE:
        Fr_POCStatusPtr->ErrorMode = FR_ERRORMODE_PASSIVE;
        break;
      case FR_59_RENESAS_ERRM_COMM_HALT:
        Fr_POCStatusPtr->ErrorMode = FR_ERRORMODE_COMM_HALT;
        break;
      default:
        if (FR_59_RENESAS_DEM_NOT_CONFIGURED != LpDemEventId->usHardwareTestFailure)
        {
          FR_59_RENESAS_DEM_REPORT_ERROR(LpDemEventId->usHardwareTestFailure, DEM_EVENT_STATUS_FAILED);
        } /* else No Action required */
        LucReturnValue = E_NOT_OK;
        break;
      }
    } /* else No Action required */
  } /* End of if (E_OK == LucReturnValue) */
/* else No Action required */
  return (LucReturnValue);
} /* End of function Fr_59_Renesas_UpdatePOCSts */
#define FR_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_GetCorrectionValue
**
** Service ID            : Not Applicable
**
** Description           : This function gets Rate Correction and Offset
**                        correction from FlexRay CC Status Vector Register
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx
**
** InOut Parameters      : None
**
** Output Parameters     : Fr_RateCorrectionPtr, Fr_OffsetCorrectionPtr
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : None
**
** Global Variables Used : Fr_59_Renesas_GpCtrlRegSet,
**                         Fr_59_Renesas_GpControllerConfigPtr
**
** Functions Invoked     : FR_59_RENESAS_DEM_REPORT_ERROR,
**                         Fr_59_Renesas_GetPOCStsFlag
**
** Registers Used        : FLXAnFRRCV, FLXAnFROCV
**
** Reference ID          : FR_DUD_ACT_051, FR_DUD_ACT_051_ERR001
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PRIVATE_CODE)
Fr_59_Renesas_GetCorrectionValue(const uint8 Fr_CtrlIdx, sint16 *const Fr_RateCorrectionPtr,                            
                                                                                  sint32 *const Fr_OffsetCorrectionPtr)
{
  /* Declare pointer to register */
  P2CONST(volatile Fr_59_Renesas_RegisterSetType, AUTOMATIC, FR_CONFIG_DATA) LpCtrlRegSet;
  P2VAR(volatile Fr_59_Renesas_CCStatusRegType, AUTOMATIC, REGSPACE) LpCCStatusReg;                                     /* PRQA S 3678 # JV-01 */
  /* Declare local pointer to Dem Event Id */
  P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF, FR_CONFIG_DATA) LpDemEventId;
  /* Declare variable to store the return value */
  Std_ReturnType LucReturnValue;
  uint32 LulData;

  /* Initialize the return value */
  LucReturnValue = E_OK;
  /* Copy global pointer to local pointer */
  LpCtrlRegSet = Fr_59_Renesas_GpCtrlRegSet[Fr_CtrlIdx];                                                                
  LpCCStatusReg = LpCtrlRegSet->pCCStatusReg;                                                                          
  /* Read the POC State by getting FLX0CCSV register value */
  LulData = Fr_59_Renesas_GetPOCStsFlag(Fr_CtrlIdx);
  /* Check if the CC is in normal active state */
  if ((FR_59_RENESAS_NORMAL_ACTIVE_STATE == LulData) || (FR_59_RENESAS_NORMAL_PASSIVE_STATE == LulData))
  {
    /* Read value of vRateCorrection (two's complement) */
    LulData = LpCCStatusReg->ulFLXAnFRRCV;                                                                             
    /* Check if vRateCorrection is positive or negative number */
    if ((uint32)FR_59_RENESAS_ONE == ((LulData & FR_59_RENESAS_FLX0FRRCV_MASK) >> FR_59_RENESAS_ELEVEN))
    {
      /* Value of vRateCorrection is negative number */
      /* Complement '0xF' to 4 highest bits of sint16 value */
      /* Load Rate correction value in Fr_RateCorrectionPtr */
      *Fr_RateCorrectionPtr = (sint16)(FR_59_RENESAS_FLX0FRRCV_COMPLEMENT | LulData);                                    /* PRQA S 2856, 4394 # JV-01, JV-01 */               
    }
    else
    {
      /* Value of vRateCorrection is positive number */
      /* Load Rate correction value in Fr_RateCorrectionPtr */
      *Fr_RateCorrectionPtr = (sint16)LpCCStatusReg->ulFLXAnFRRCV;
    }

    /* Read value of vOffsetCorrection (two's complement) */
    LulData = LpCCStatusReg->ulFLXAnFROCV;
    /* Check if vOffsetCorrection is positive or negative number */
    if ((uint32)FR_59_RENESAS_ONE == ((LulData & FR_59_RENESAS_FLX0FROCV_MASK) >> FR_59_RENESAS_EIGHTTEEN))
    {
      /* Value of vOffsetCorrection is negative number */
      /* Complement '0xFFF8' to 13 highest bits of sint32 value */
      /* Load Offset correction value in Fr_OffsetCorrectionPtr */
      *Fr_OffsetCorrectionPtr = (sint32)(FR_59_RENESAS_FLX0FROCV_COMPLEMENT | LulData);                                  /* PRQA S 2856, 4394 # JV-01, JV-01 */                         
    }
    else
    {
      /* Value of vOffsetCorrection is positive number */
      /* Load Offset correction value in Fr_OffsetCorrectionPtr */
      *Fr_OffsetCorrectionPtr = (sint32)LpCCStatusReg->ulFLXAnFROCV;
    }
  }
  else
  {
    /* Report Error to DEM */
    LpDemEventId = (P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF,
                                         FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pDemEventId);
    if (FR_59_RENESAS_DEM_NOT_CONFIGURED != LpDemEventId->usHardwareTestFailure)                                       
    {
      FR_59_RENESAS_DEM_REPORT_ERROR(LpDemEventId->usHardwareTestFailure, DEM_EVENT_STATUS_FAILED);
    } /* else No Action required */
    /* Set Return Value as E_NOT_OK */
    LucReturnValue = E_NOT_OK;
  }
  return (LucReturnValue);
} /* End of Fr_59_Renesas_GetCorrectionValue() */
#define FR_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_ResetInputTransfer
**
** Service ID            : Not Applicable
**
** Description           : This function resets the Input Transfer handler if
**                        Input Transfer is enabled
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : None
**
** Global Variables Used : Fr_59_Renesas_GpControllerConfigPtr,
**                         Fr_59_Renesas_GpCtrlRegSet
**
** Functions Invoked     : FR_59_RENESAS_DEM_REPORT_ERROR
**
** Registers Used        : FLXAnFRITS, FLXAnFRITC
**
** Reference ID          : FR_DUD_ACT_052, FR_DUD_ACT_052_ERR001,
** Reference ID          : FR_DUD_ACT_052_ERR002, FR_DUD_ACT_052_REG001
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PRIVATE_CODE) Fr_59_Renesas_ResetInputTransfer(const uint8 Fr_CtrlIdx)                    
{
  /* Declare pointer to register */
  P2CONST(volatile Fr_59_Renesas_RegisterSetType, AUTOMATIC, FR_CONFIG_DATA) LpCtrlRegSet;
  P2VAR(volatile Fr_59_Renesas_DataTransferControlRegType, AUTOMATIC, REGSPACE) LpDataTransferCtrlReg;
  P2VAR(volatile Fr_59_Renesas_DataTransferStatusRegType, AUTOMATIC, REGSPACE) LpDataTransferStatusReg;                 /* PRQA S 3678 # JV-01 */
  /* Declare local pointer to CC configuration */
  P2CONST(Fr_59_Renesas_CtrlTableType, TYPEDEF, FR_CONFIG_DATA) LpCtrlTable;
  Std_ReturnType LucReturnValue;
  uint32 LulData;
  volatile uint16 LusLoopCount;
  /* Declare local pointer to Dem Event Id */
  P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF, FR_CONFIG_DATA) LpDemEventId;
  /* Copy global pointer to local pointer */
  LpCtrlRegSet = Fr_59_Renesas_GpCtrlRegSet[Fr_CtrlIdx];                                                                
  LpDataTransferCtrlReg = LpCtrlRegSet->pDataTransferCtrlReg;                                                          
  LpDataTransferStatusReg = LpCtrlRegSet->pDataTransferStatusReg;
  LpDemEventId = (P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF,
                                         FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pDemEventId);
  /* Check for Input Transfer enable */
  LulData = LpDataTransferStatusReg->ulFLXAnFRITS;                                                                     
  if ((FR_59_RENESAS_FLX0FRITS_FLX0_ITS_MASK == (LulData & FR_59_RENESAS_FLX0FRITS_FLX0_ITS_MASK)) &&
                          (FR_59_RENESAS_FLX0FRITS_FLX0_IQH_MASK != (LulData & FR_59_RENESAS_FLX0FRITS_FLX0_IQH_MASK)))
  {
    LpCtrlTable = (P2CONST(Fr_59_Renesas_CtrlTableType, AUTOMATIC,
                                          FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pCtrlTable);
    /* Read current value of FLX0FRITC register */
    LulData = LpDataTransferCtrlReg->ulFLXAnFRITC;                                                                     
    /* Disable the input transfer handler */
    LulData = LulData & FR_59_RENESAS_FLX0FRITC_ITE_RESET;
    /* Writing in to FlexRay Input Transfer Configuration Register and mirror address */
    LpDataTransferCtrlReg->ulFLXAnFRITC = LulData;
    /* Initialize the loop count to FR_59_RENESAS_ZERO */
    LusLoopCount = FR_59_RENESAS_ZERO;
    /* Wait until input transfer is disabled */
    while ((FR_59_RENESAS_FLX0FRITS_FLX0_ITS_MASK ==                                                                   
            (LpDataTransferStatusReg->ulFLXAnFRITS & FR_59_RENESAS_FLX0FRITS_FLX0_ITS_MASK)) &&
                                                            (LusLoopCount < (uint16)(LpCtrlTable->usFlagClearMaxWait))) /* PRQA S 3415, 3416 # JV-01, JV-01 */
    {
      /* Increment the loop count */
      LusLoopCount++;                                                                                                   /* PRQA S 3383, 3387 # JV-01, JV-01 */
    }
    if (LusLoopCount == (uint16)(LpCtrlTable->usFlagClearMaxWait))                                                      /* PRQA S 3416 # JV-01 */
    {
      if (FR_59_RENESAS_DEM_NOT_CONFIGURED != LpDemEventId->usReadTimeoutFailure)                                       
      {
        FR_59_RENESAS_DEM_REPORT_ERROR(LpDemEventId->usReadTimeoutFailure, DEM_EVENT_STATUS_FAILED);
      } /* else No Action required */
      /* Set Return Value as E_NOT_OK */
      LucReturnValue = E_NOT_OK;
    }
    else
    {
      /* Set Return Value as E_OK */
      LucReturnValue = E_OK;
    }
  }
  else
  {
    /* Raise DEM Error FAILED */
    if (FR_59_RENESAS_DEM_NOT_CONFIGURED != LpDemEventId->usHardwareTestFailure)
    {
      FR_59_RENESAS_DEM_REPORT_ERROR(LpDemEventId->usHardwareTestFailure, DEM_EVENT_STATUS_FAILED);
    } /* else No Action required */
    /* Set Return Value as E_NOT_OK */
    LucReturnValue = E_NOT_OK;
  }
  return (LucReturnValue);
} /* End of function Fr_59_Renesas_ResetInputTransfer */
#define FR_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_WriteCHICmd
**
** Service ID            : Not Applicable
**
** Description           : This function writes CHI command to change POC state
**
** Sync/Async            : Asynchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx, CHICmd
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : None
**
** Global Variables Used : Fr_59_Renesas_GpCtrlRegSet
**
** Functions Invoked     : Fr_59_Renesas_CheckIfCCBusy
**
** Registers Used        : FLXAnFRSUCC1
**
** Reference ID          : FR_DUD_ACT_053, FR_DUD_ACT_053_REG001
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PRIVATE_CODE) Fr_59_Renesas_WriteCHICmd(const uint8 Fr_CtrlIdx, const uint32 CHICmd)
{
  /* Declare pointer to register */
  P2CONST(volatile Fr_59_Renesas_RegisterSetType, AUTOMATIC, FR_CONFIG_DATA) LpCtrlRegSet;
  P2VAR(volatile Fr_59_Renesas_CCControlRegType, AUTOMATIC, REGSPACE) LpCCCtrlReg;
  uint32 LulData;
  Std_ReturnType LucReturnValue;
  /* Copy global pointer to local pointer */
  LpCtrlRegSet = Fr_59_Renesas_GpCtrlRegSet[Fr_CtrlIdx];                                                                
  LpCCCtrlReg = LpCtrlRegSet->pCCCtrlReg;                                                                              
  /* Initialize internal variable */
  LulData = FR_59_RENESAS_ZERO;                                                                                         /* PRQA S 2982 # JV-01 */
  LucReturnValue = E_OK;                                                                                                /* PRQA S 2982 # JV-01 */
  /* Check whether POC is busy and FLXAnFRSUCC1.CMD locked or not */
  LucReturnValue = Fr_59_Renesas_CheckIfCCBusy(Fr_CtrlIdx);
  /* Check if the return value is E_OK */
  if (E_OK == LucReturnValue)
  {
    /* Check whether CHICmd is FR_59_RENESAS_CMD_NOT_ACCEPTED */
    if (FR_59_RENESAS_CMD_NOT_ACCEPTED != CHICmd)
    {
      /* Read the value of the FLX0SUCC1 register */
      LulData = LpCCCtrlReg->ulFLXAnFRSUCC1;                                                                           
      LulData = (LulData & FR_59_RENESAS_FLX0SUCC1_FLX0CMD_MASK) | CHICmd;
      /* Writing in to FlexRay SUC Configuration Register and mirror address */
      LpCCCtrlReg->ulFLXAnFRSUCC1 = LulData;
    } /* else No Action required */
    /*
     * All accepted commands with exception of CLEAR_RAMS and SEND_MTS will cause a change of the POC state in the
     * FlexRay domain after at most 8 cycles of the slower of the two clocks "bus clock" and "FlexRay sample clock"
     */
  } /* else No Action required */
  return (LucReturnValue); /* End of function Fr_59_Renesas_WriteCHICmd */
}
#define FR_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_SetWakeupChannelProcess
**
** Service ID            : Not Applicable
**
** Description           : This function set the wakeup channel to FlexRay SUC
**                         Configuration Register
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx, Fr_ChnlIdx
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : None
**
** Global Variables Used : Fr_59_Renesas_GpControllerConfigPtr,
**                         Fr_59_Renesas_GpCtrlRegSet
**
** Functions Invoked     : FR_59_RENESAS_DEM_REPORT_ERROR,
**                         Fr_59_Renesas_UnlockSequence,
**                         Fr_59_Renesas_GetPOCStsFlag,
**                         FR_59_RENESAS_ENTER_CRITICAL_SECTION,
**                         FR_59_RENESAS_EXIT_CRITICAL_SECTION
**
** Registers Used        : FLXAnFRSUCC1
**
** Reference ID          : FR_DUD_ACT_054, FR_DUD_ACT_054_CRT001,
** Reference ID          : FR_DUD_ACT_054_CRT002, FR_DUD_ACT_054_ERR001,
** Reference ID          : FR_DUD_ACT_054_ERR002, FR_DUD_ACT_054_REG001,
** Reference ID          : FR_DUD_ACT_054_REG002
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PRIVATE_CODE)
                         Fr_59_Renesas_SetWakeupChannelProcess(const uint8 Fr_CtrlIdx, const Fr_ChannelType Fr_ChnlIdx) 
{
  /* Declare pointer to register */
  P2CONST(volatile Fr_59_Renesas_RegisterSetType, AUTOMATIC, FR_CONFIG_DATA) LpCtrlRegSet;
  P2VAR(volatile Fr_59_Renesas_CCControlRegType, AUTOMATIC, REGSPACE) LpCCCtrlReg;
  /* Declare local pointer to CC configuration */
  P2CONST(Fr_59_Renesas_CtrlTableType, TYPEDEF, FR_CONFIG_DATA) LpCtrlTable;
  uint32 LulData;
  Std_ReturnType LucReturnValue;
  volatile uint16 LusLoopCount;
  /* Declare local pointer to Dem Event Id */
  P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF, FR_CONFIG_DATA) LpDemEventId;
  /* Copy global pointer to local pointer */
  LpCtrlTable = (P2CONST(Fr_59_Renesas_CtrlTableType, AUTOMATIC,
                                          FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pCtrlTable);
  LpDemEventId = (P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF,
                                         FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pDemEventId);
  LpCtrlRegSet = Fr_59_Renesas_GpCtrlRegSet[Fr_CtrlIdx];                                                                
  LpCCCtrlReg = LpCtrlRegSet->pCCCtrlReg;                                                                              
  /* Initialize internal variable */
  LulData = FR_59_RENESAS_ZERO;                                                                                         /* PRQA S 2982 # JV-01 */
  LucReturnValue = E_OK;
  /* Initialize the loop count */
  LusLoopCount = FR_59_RENESAS_ZERO;
  /* Read FRCCSV register value to get the POC state */
  LulData = Fr_59_Renesas_GetPOCStsFlag(Fr_CtrlIdx);
  /* Check whether POC is in CONFIG State */
  if (FR_59_RENESAS_CONFIG_STATE != LulData)
  {
    if (FR_59_RENESAS_DEM_NOT_CONFIGURED != LpDemEventId->usHardwareTestFailure)                                        
    {
      FR_59_RENESAS_DEM_REPORT_ERROR(LpDemEventId->usHardwareTestFailure, DEM_EVENT_STATUS_FAILED);
    } /* else No Action required */
    /* Update the return value to E_NOT_OK */
    LucReturnValue = E_NOT_OK;
  }
  else
  {
    /* Read the value of the register FLX0SUCC1 */
    LulData = LpCCCtrlReg->ulFLXAnFRSUCC1;                                                                             
    /* Check if the channel index is A */
    if (FR_CHANNEL_A == Fr_ChnlIdx)
    {
      /* Configure the wakeup channel as Channel A */
      LulData = (LulData & FR_59_RENESAS_FLX0SUCC1_FLX0WUCS_MASK);
    }
    else
    {
      /* Configure the wakeup channel as Channel B */
      LulData = (LulData | FR_59_RENESAS_FLX0SUCC1_FLX0WUCS_SET);
    }
    /* Writing in to FlexRay SUC Configuration Register and
     mirror address */
    LpCCCtrlReg->ulFLXAnFRSUCC1 = LulData;

    /* Read the value of the register FLX0SUCC1 */
    LulData = LpCCCtrlReg->ulFLXAnFRSUCC1;
    /* Update the READY command */
    LulData = ((LulData & FR_59_RENESAS_FLX0SUCC1_FLX0CMD_MASK) | FR_59_RENESAS_READY);

    /* Check if critical section protection is required */
    #if (FR_59_RENESAS_CRITICAL_SECTION_PROTECTION == STD_ON)
    /* Enter the Critical Section Area */
    FR_59_RENESAS_ENTER_CRITICAL_SECTION(FR_INTERRUPT_CONTROL_PROTECTION);
    #endif
    /* Execute the unlock sequence */
    Fr_59_Renesas_UnlockSequence(Fr_CtrlIdx);
    /* Command CC to enter READY State */
    /* Writing in to FlexRay SUC Configuration Register and
     mirror address */
    LpCCCtrlReg->ulFLXAnFRSUCC1 = LulData;
    /* Check if critical section protection is required */
    #if (FR_59_RENESAS_CRITICAL_SECTION_PROTECTION == STD_ON)
    /* Exit the Critical Section Area */
    FR_59_RENESAS_EXIT_CRITICAL_SECTION(FR_INTERRUPT_CONTROL_PROTECTION);
    #endif
    do
    {
      LulData = Fr_59_Renesas_GetPOCStsFlag(Fr_CtrlIdx);
      LusLoopCount++;                                                                                                   /* PRQA S 3387, 3383 # JV-01, JV-01 */
    } while ((FR_59_RENESAS_READY_STATE != LulData) && (LusLoopCount < (uint16)(LpCtrlTable->usFlagClearMaxWait)));     /* PRQA S 3415, 3416 # JV-01, JV-01 */
    if (FR_59_RENESAS_READY_STATE != LulData)
    {
      /* Cannot access the communication controller */
      if (FR_59_RENESAS_DEM_NOT_CONFIGURED != LpDemEventId->usReadTimeoutFailure)
      {
        FR_59_RENESAS_DEM_REPORT_ERROR(LpDemEventId->usReadTimeoutFailure, DEM_EVENT_STATUS_FAILED);
      } /* else No Action required */
      LucReturnValue = E_NOT_OK;
    } /* else No Action required */
  }
  return (LucReturnValue);
} /* End of function Fr_59_Renesas_SetWakeupChannelProcess */
#define FR_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_SwitchCCToConfig
**
** Service ID            : Not Applicable
**
** Description           : This function will check the current POC state and
**                         write CHI command to change POC state to CONFIG
**                         state accordingly. After that, reset WUP flag and
**                         MTS flag of Status Interrupt Register.
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Reentrant
**
** Input Parameters      : Fr_CtrlIdx
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : None
**
** Global Variables Used : Fr_59_Renesas_GpCtrlRegSet
**
** Functions Invoked     : Fr_59_Renesas_WriteCHICmd,
**                         Fr_59_Renesas_GetPOCStsFlag
**
** Registers Used        : FLXAnFRSIR
**
** Reference ID          : FR_DUD_ACT_055, FR_DUD_ACT_055_REG001
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PRIVATE_CODE) Fr_59_Renesas_SwitchCCToConfig(const uint8 Fr_CtrlIdx)                         
{
  /* Declare pointer to register */
  P2CONST(volatile Fr_59_Renesas_RegisterSetType, AUTOMATIC, FR_CONFIG_DATA) LpCtrlRegSet;
  P2VAR(volatile Fr_59_Renesas_InterruptRegType, AUTOMATIC, REGSPACE) LpIntReg;
  Std_ReturnType LucReturnValue;
  uint32 LulData;
  /* Initialize internal variable */
  LucReturnValue = E_OK;
  LulData = FR_59_RENESAS_ZERO;                                                                                         /* PRQA S 2982 # JV-01 */
  /* Copy global pointer to local pointer */
  LpCtrlRegSet = Fr_59_Renesas_GpCtrlRegSet[Fr_CtrlIdx];                                                                
  LpIntReg = LpCtrlRegSet->pIntReg;                                                                                    
  /* Get the current POC state */
  LulData = Fr_59_Renesas_GetPOCStsFlag(Fr_CtrlIdx);
  /* Check if the controller is in CONFIG state */
  if (FR_59_RENESAS_CONFIG_STATE != LulData)
  {
    /* Check whether POC is in NORMAL_ACTIVE, NORMAL_PASSIVE, WAKEUP or STARTUP States. */
    if ((FR_59_RENESAS_NORMAL_ACTIVE_STATE == LulData) || (FR_59_RENESAS_NORMAL_PASSIVE_STATE == LulData) ||
                                       (FR_59_RENESAS_WAKEUP_STATE == (LulData & FR_59_RENESAS_WAKEUP_STATE)) ||
                                              (FR_59_RENESAS_STARTUP_STATE == (LulData & FR_59_RENESAS_STARTUP_STATE)))
    {
      /* Command READY: NORMAL_ACTIVE, NORMAL_PASSIVE, WAKEUP, STARTUP to READY state */
      LucReturnValue = Fr_59_Renesas_WriteCHICmd(Fr_CtrlIdx, FR_59_RENESAS_READY);
    }
    /* Check if CC is in HALT state */
    else if (FR_59_RENESAS_HALT_STATE == LulData)                                                                       /* PRQA S 2004 # JV-01 */
    {
      /* Command CONFIG: HALT to DEFAULT_CONFIG State */
      LucReturnValue = Fr_59_Renesas_WriteCHICmd(Fr_CtrlIdx, FR_59_RENESAS_CONFIG);
    } /* else No Action required */
    /* Check if the return value is E_OK */
    if (E_OK == LucReturnValue)
    {
      /* Command CONFIG: DEFAULT_CONFIG to CONFIG State */
      LucReturnValue = Fr_59_Renesas_WriteCHICmd(Fr_CtrlIdx, FR_59_RENESAS_CONFIG);
    } /* else No Action required */
  } /* else No Action required */
  /* Absolute Timer 0, 2 are deactivated when leaving NORMAL_ACTIVE state or
   * NORMAL_PASSIVE state except for transitions between the two states
   */
  if (E_OK == LucReturnValue)
  {
    /* Reset of status flags SIR.WUPA, SIR.WUPB, SIR.MTSA, SIR.MTSB */
    LulData = FR_59_RENESAS_FLX0SIR_FLX0WUP_RESET | FR_59_RENESAS_FLX0SIR_FLX0MTS_MASK;
    /* Writing in to FlexRay Status Interrupt Register and mirror address */
    LpIntReg->ulFLXAnFRSIR = (uint32)LulData;                                                                          
  } /* else No Action required */
  return (LucReturnValue);
} /* End of function Fr_59_Renesas_ClearStatusForCCReset */
#define FR_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_InitDone
**
** Service ID            : Not Applicable
**
** Description           : This function to inform that FlexRay has been
**                         initialized successfully
**
** Sync/Async            : Asynchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : None
**
** Preconditions         : None
**
** Global Variables Used : Fr_59_Renesas_GaaGlobalAccPoint
**
** Functions Invoked     : None
**
** Registers Used        : None
**
** Reference ID          : FR_DUD_ACT_056, FR_DUD_ACT_056_GBL001
***********************************************************************************************************************/
#if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
#define FR_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(void, FR_PRIVATE_CODE) Fr_59_Renesas_InitDone(uint8 LucCoreIndex)                                              
{
  /* Set the global variable Fr_59_Renesas_GblInitDone to indicate that FlexRay
   driver has been initialized successfully */
  *(Fr_59_Renesas_GaaGlobalAccPoint[LucCoreIndex].pInitDone) = FR_59_RENESAS_TRUE;                                     
} /* End of function Fr_59_Renesas_InitDone */
#define FR_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
#endif
/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_CheckErrorInterrupt
**
** Service ID            : Not Applicable
**
** Description           : This function checks error interrupt
**                        from FLXAnFREIR register
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : None
**
** Global Variables Used : Fr_59_Renesas_GpControllerConfigPtr,
**                         Fr_59_Renesas_GpCtrlRegSet
**
** Functions Invoked     : FR_59_RENESAS_DEM_REPORT_ERROR
**
** Registers Used        : FLXAnFREIR
**
** Reference ID          : FR_DUD_ACT_057, FR_DUD_ACT_057_ERR001,
** Reference ID          : FR_DUD_ACT_057_REG001
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PRIVATE_CODE) Fr_59_Renesas_CheckErrorInterrupt(const uint8 Fr_CtrlIdx)                      
{
  /* Declare pointer to register */
  P2CONST(volatile Fr_59_Renesas_RegisterSetType, AUTOMATIC, FR_CONFIG_DATA) LpCtrlRegSet;
  P2VAR(volatile Fr_59_Renesas_InterruptRegType, AUTOMATIC, REGSPACE) LpIntReg;
  uint32 LulData;
  /* Declare the variable to store the return value */
  Std_ReturnType LucReturnValue;
  /* Declare local pointer to Dem Event Id */
  P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF, FR_CONFIG_DATA) LpDemEventId;
  /* Copy global pointer to local pointer */
  LpCtrlRegSet = Fr_59_Renesas_GpCtrlRegSet[Fr_CtrlIdx];                                                                
  LpIntReg = LpCtrlRegSet->pIntReg;                                                                                    

  /* Read the value of the register FLX0EIR */
  LulData = LpIntReg->ulFLXAnFREIR;                                                                                    
  LulData = LulData & FR_59_RENESAS_FLX0EIR_ED_LTV;
  if ((uint32)FR_59_RENESAS_ZERO != LulData)
  {
    /* To clear respective flag of FREIR.EDA/B, FREIR.LTVA/B */
    LpIntReg->ulFLXAnFREIR = LulData;
    /* Report to DEM */
    LpDemEventId = (P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF,
                                         FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pDemEventId);
    if (FR_59_RENESAS_DEM_NOT_CONFIGURED != LpDemEventId->usHardwareTestFailure)                                        
    {
      FR_59_RENESAS_DEM_REPORT_ERROR(LpDemEventId->usHardwareTestFailure, DEM_EVENT_STATUS_FAILED);
    } /* else No Action required */
    LucReturnValue = E_NOT_OK;
  }
  else
  {
    LucReturnValue = E_OK;
  }
  return (LucReturnValue);
} /* End of function Fr_59_Renesas_CheckErrorInterrupt */
#define FR_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_GetBufferCommand
**
** Service ID            : Not Applicable
**
** Description           : This function get the Input Buffer Request status
**                        from FlexRay Input Buffer Command Request Register
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : None
**
** Global Variables Used : Fr_59_Renesas_GpControllerConfigPtr,
**                         Fr_59_Renesas_GpCtrlRegSet
**
** Functions Invoked     : FR_59_RENESAS_ENTER_CRITICAL_SECTION,
**                         FR_59_RENESAS_EXIT_CRITICAL_SECTION,
**                         FR_59_RENESAS_DEM_REPORT_ERROR
**
** Registers Used        : FLXAnFRIBCR
**
** Reference ID          : FR_DUD_ACT_058, FR_DUD_ACT_058_CRT001,
** Reference ID          : FR_DUD_ACT_058_CRT002, FR_DUD_ACT_058_ERR001
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PRIVATE_CODE)
Fr_59_Renesas_GetBufferCommand(const uint8 Fr_CtrlIdx)                                                         
{
  /* Declare pointer to register */
  P2CONST(volatile Fr_59_Renesas_RegisterSetType, AUTOMATIC, FR_CONFIG_DATA) LpCtrlRegSet;
  P2VAR(volatile Fr_59_Renesas_InputBufferRegType, AUTOMATIC, REGSPACE) LpInputBuffReg;                                 /* PRQA S 3678 # JV-01 */
  /* Declare local pointer to CC configuration */
  P2CONST(Fr_59_Renesas_CtrlTableType, TYPEDEF, FR_CONFIG_DATA) LpCtrlTable;
  /* Declare the variable to store the return value */
  Std_ReturnType LucReturnValue;
  volatile uint16 LusLoopCount;
  /* Declare local pointer to Dem Event Id */
  P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF, FR_CONFIG_DATA) LpDemEventId;
  /* Initialize the return value */
  LucReturnValue = E_OK;
  /* Copy global pointer to local pointer */
  LpCtrlRegSet = Fr_59_Renesas_GpCtrlRegSet[Fr_CtrlIdx];                                                                
  LpInputBuffReg = LpCtrlRegSet->pInputBuffReg;                                                                        
  /* Wait if any Input Buffer is busy servicing the earlier request */
  LusLoopCount = FR_59_RENESAS_ZERO;

  LpCtrlTable = (P2CONST(Fr_59_Renesas_CtrlTableType, AUTOMATIC,
                                          FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pCtrlTable);
  /* Check if critical section protection is required */
  #if (FR_59_RENESAS_CRITICAL_SECTION_PROTECTION == STD_ON)
  /* Enter the Critical Section Area */
  FR_59_RENESAS_ENTER_CRITICAL_SECTION(FR_INTERRUPT_CONTROL_PROTECTION);
  #endif
  while (((uint32)FR_59_RENESAS_ZERO != ((LpInputBuffReg->ulFLXAnFRIBCR) &                                              
                 FR_59_RENESAS_FLX0IBCR_FLX0IBSYH_MASK)) && (LusLoopCount < (uint16)(LpCtrlTable->usFlagClearMaxWait))) /* PRQA S 3415, 3416 # JV-01, JV-01 */
  {
    /* Increment the loop count */
    LusLoopCount++;                                                                                                     /* PRQA S 3383, 3387 # JV-01, JV-01 */
  }
  /* Check if critical section protection is required */
  #if (FR_59_RENESAS_CRITICAL_SECTION_PROTECTION == STD_ON)
  /* Exit the Critical Section Area */
  FR_59_RENESAS_EXIT_CRITICAL_SECTION(FR_INTERRUPT_CONTROL_PROTECTION);
  #endif
  /* Check if the loop count is less the value of wait for the interrupt flag to get cleared */
  if (LusLoopCount == (uint16)(LpCtrlTable->usFlagClearMaxWait))                                                        /* PRQA S 3416 # JV-01 */
  {
    /* Report to DEM */
    LpDemEventId = (P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF,
                                         FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pDemEventId);
    if (FR_59_RENESAS_DEM_NOT_CONFIGURED != LpDemEventId->usReadTimeoutFailure)                                         
    {
      FR_59_RENESAS_DEM_REPORT_ERROR(LpDemEventId->usReadTimeoutFailure, DEM_EVENT_STATUS_FAILED);
    } /* else No Action required */
    /* Update the return value to E_NOT_OK */
    LucReturnValue = E_NOT_OK;
  } /* else No Action required */
  return (LucReturnValue);
} /* End of function Fr_59_Renesas_GetBufferCommand */
#define FR_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_WriteHeaderSection
**
** Service ID            : Not Applicable
**
** Description           : This function is to write data
**                        to FlexRay Write Header Section Register
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx, RegMacro, RegValue
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : None
**
** Preconditions         : None
**
** Global Variables Used : Fr_59_Renesas_GpCtrlRegSet
**
** Functions Invoked     : None.
**
** Registers Used        : FLXAnFRWRHS1, FLXAnFRWRHS2, FLXAnFRWRHS3
**
** Reference ID          : FR_DUD_ACT_059, FR_DUD_ACT_059_REG001,
** Reference ID          : FR_DUD_ACT_059_REG002, FR_DUD_ACT_059_REG003
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(void, FR_PRIVATE_CODE)
                 Fr_59_Renesas_WriteHeaderSection(const uint8 Fr_CtrlIdx, const uint32 RegMacro, const uint32 RegValue) /* PRQA S 1505 # JV-01 */
{
  /* Declare pointer to register */
  P2CONST(volatile Fr_59_Renesas_RegisterSetType, AUTOMATIC, FR_CONFIG_DATA) LpCtrlRegSet;
  P2VAR(volatile Fr_59_Renesas_InputBufferRegType, AUTOMATIC, REGSPACE) LpInputBuffReg;
  /* Copy global pointer to local pointer */
  LpCtrlRegSet = Fr_59_Renesas_GpCtrlRegSet[Fr_CtrlIdx];                                                                
  LpInputBuffReg = LpCtrlRegSet->pInputBuffReg;                                                                        
  /* Write the value of the header in FlexRay Write Header Section
   Register 1 and mirror address */
  switch (RegMacro)
  {
  case (FR_59_RENESAS_FLX0WRHS1):
    LpInputBuffReg->ulFLXAnFRWRHS1 = RegValue;                                                                         
    break;
  case (FR_59_RENESAS_FLX0WRHS2):
    LpInputBuffReg->ulFLXAnFRWRHS2 = RegValue;
    break;
  case (FR_59_RENESAS_FLX0WRHS3):
    LpInputBuffReg->ulFLXAnFRWRHS3 = RegValue;
    break;
  default:
    /* No action required */
    break;
  }
} /* End of function Fr_59_Renesas_WriteHeaderSection */
#define FR_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_UpdateWRHReg
**
** Service ID            : Not Applicable
**
** Description           : This function is to write data
**                         to FlexRay Input Buffer Command Mask Register
**                         and FlexRay Write Header Section Register
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx, RegValue, Fr_HeaderCRC, Fr_PayloadLength
**                         Fr_LPduIdx
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : None
**
** Global Variables Used : Fr_59_Renesas_GpControllerConfigPtr,
**                         Fr_59_Renesas_GpCtrlRegSet
**
** Functions Invoked     : FR_59_RENESAS_DEM_REPORT_ERROR,
**                         Fr_59_Renesas_WriteHeaderSection
**
** Registers Used        : FLXAnFRIBCM, FLXAnFRIBCR
**
** Reference ID          : FR_DUD_ACT_060, FR_DUD_ACT_060_ERR001,
** Reference ID          : FR_DUD_ACT_060_REG001, FR_DUD_ACT_060_REG002
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PRIVATE_CODE)
              Fr_59_Renesas_UpdateWRHReg(const uint8 Fr_CtrlIdx, uint32 RegValue, const uint16 Fr_HeaderCRC,         
                                                                 const uint8 Fr_PayloadLength, const uint16 Fr_LPduIdx)
{
  /* Declare pointer to register */
  P2CONST(volatile Fr_59_Renesas_RegisterSetType, AUTOMATIC, FR_CONFIG_DATA) LpCtrlRegSet;
  P2VAR(volatile Fr_59_Renesas_InputBufferRegType, AUTOMATIC, REGSPACE) LpInputBuffReg;
  /* Declare local pointer to CC configuration */
  P2CONST(Fr_59_Renesas_CtrlTableType, TYPEDEF, FR_CONFIG_DATA) LpCtrlTable;
  P2CONST(Fr_59_Renesas_FrameHeaderType, AUTOMATIC, FR_APPL_CONST) LpBufferHeader;
  P2CONST(Fr_59_Renesas_FrameHeaderType, TYPEDEF, FR_CONFIG_DATA) LpFrameConfig;
  /* Declare local pointer to Dem Event Id */
  P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF, FR_CONFIG_DATA) LpDemEventId;
  Std_ReturnType LucReturnValue;
  volatile uint16 LusLoopCount;
  /* Initialize the return value */
  LucReturnValue = E_OK;
  /* Copy global pointer to local pointer */
  LpCtrlRegSet = Fr_59_Renesas_GpCtrlRegSet[Fr_CtrlIdx];                                                                
  LpInputBuffReg = LpCtrlRegSet->pInputBuffReg;                                                                        
  /* Read the frame pointer */
  LpCtrlTable = (P2CONST(Fr_59_Renesas_CtrlTableType, AUTOMATIC,
                                          FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pCtrlTable);
  LpFrameConfig = Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pFrameConfig;
  LpBufferHeader = &LpFrameConfig[Fr_LPduIdx];                                                                        

  /* Write the value of the header in FlexRay Write Header Section Register 1 and mirror address */
  Fr_59_Renesas_WriteHeaderSection(Fr_CtrlIdx, FR_59_RENESAS_FLX0WRHS1, RegValue);
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_OFF)
  /* Since the Header CRC masking is considered when */
  /* 'FR_59_RENESAS_DEV_ERROR_DETECT'is ON */
  /* Get the value of the CRC calculated for the header data */
  RegValue = (Fr_HeaderCRC & FR_59_RENESAS_CRC_MASK);                                                                   /* PRQA S 1338 # JV-01 */
  #else
  RegValue = Fr_HeaderCRC;                                                                                              /* PRQA S 1338 # JV-01 */
  #endif
  #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  /* Since the 'Fr_PayloadLength' masking is considered when */
  /* FR_59_RENESAS_DEV_ERROR_DETECT is ON*/
  /* Get the value of the Payload length configured */
  RegValue = RegValue | ((uint32)Fr_PayloadLength << FR_59_RENESAS_PLC_SHIFT);                                          /* PRQA S 1338 # JV-01 */
  #else
  /* Get the value of the Payload length configured */
  RegValue = RegValue | ((uint32)((Fr_PayloadLength)&FR_59_RENESAS_PLC_MASK) << FR_59_RENESAS_PLC_SHIFT);               /* PRQA S 1338 # JV-01 */
  #endif
  /* Write the value of the header in the register FRWRHS2 */
  Fr_59_Renesas_WriteHeaderSection(Fr_CtrlIdx, FR_59_RENESAS_FLX0WRHS2, RegValue);

  /* Get the value of the Data pointer(Frame ID) */
  RegValue = ((LpBufferHeader->usDataPointer) & FR_59_RENESAS_DP_MASK);                                                 /* PRQA S 1338 # JV-01 */

  /* Write the value of the header in the register FRWRHS3 */
  Fr_59_Renesas_WriteHeaderSection(Fr_CtrlIdx, FR_59_RENESAS_FLX0WRHS3, RegValue);
  /* Initialize the loop count to FR_59_RENESAS_ZERO */
  LusLoopCount = FR_59_RENESAS_ZERO;
  while ((FR_59_RENESAS_FLX0IBCR_FLX0IBSYH_MASK == (LpInputBuffReg->ulFLXAnFRIBCR                                       
               & FR_59_RENESAS_FLX0IBCR_FLX0IBSYH_MASK)) && (LusLoopCount < (uint16)(LpCtrlTable->usFlagClearMaxWait))) /* PRQA S 3415, 3416 # JV-01, JV-01 */
  {
    /* Increment the loop count */
    LusLoopCount++;                                                                                                     /* PRQA S 3387, 3383 # JV-01, JV-01 */
  }
  if (LusLoopCount == (uint16)(LpCtrlTable->usFlagClearMaxWait))                                                        /* PRQA S 3416 # JV-01 */
  {
    LpDemEventId = (P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF,
                                         FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pDemEventId);
    if (FR_59_RENESAS_DEM_NOT_CONFIGURED != LpDemEventId->usReadTimeoutFailure)                                         
    {
      FR_59_RENESAS_DEM_REPORT_ERROR(LpDemEventId->usReadTimeoutFailure, DEM_EVENT_STATUS_FAILED);
    } /* else No Action required */
    LucReturnValue = E_NOT_OK;
  }
  else
  {

    /* Write the value of the header in the register FRIBCM */
    /* Writing in to FlexRay Input Buffer Command Mask Register and mirror address */
    LpInputBuffReg->ulFLXAnFRIBCM = FR_59_RENESAS_FLX0IBCM_FLX0LHSH_MASK;
    /* Get the value of the message buffer configured and load the value in the FRIBCR register */
    RegValue = ((LpBufferHeader->ucMsgBuffer) & FR_59_RENESAS_FLX0IBCR_FLX0IBRH_MASK);                                  /* PRQA S 1338 # JV-01 */
    /* Write the value of the header in the register FRIBCR */
    /* Writing in to FlexRay Input Buffer Command Request Register and mirror address */
    LpInputBuffReg->ulFLXAnFRIBCR = RegValue;
  }
  return (LucReturnValue);
} /* End of function Fr_59_Renesas_UpdateWRHReg */
#define FR_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_SetCycleOffset
**
** Service ID            : Not Applicable
**
** Description           : This function sets the absolute timers.
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx, Fr_AbsTimerIdx, Fr_CycleCode,
**                         Fr_Offset
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : None
**
** Global Variables Used : Fr_59_Renesas_GpCtrlRegSet,
**                         Fr_59_Renesas_GpControllerConfigPtr
**
** Functions Invoked     : None.
**
** Registers Used        : FLXAnFRT0C, FLXAnFRT2C
**
** Reference ID          : FR_DUD_ACT_061,
** Reference ID          : FR_DUD_ACT_061_REG001, FR_DUD_ACT_061_REG002,
** Reference ID          : FR_DUD_ACT_061_REG003, FR_DUD_ACT_061_REG004
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PRIVATE_CODE)
Fr_59_Renesas_SetCycleOffset(const uint8 Fr_CtrlIdx, const uint8 Fr_AbsTimerIdx, uint8 Fr_CycleCode,               
                                                                                                const uint16 Fr_Offset)
{
  /* Declare pointer to register */
  P2CONST(volatile Fr_59_Renesas_AbsTimerConfigType, TYPEDEF, FR_APPL_CONST) LpAbsTimerConfig;
  P2CONST(volatile Fr_59_Renesas_AbsTimerConfigType, AUTOMATIC, FR_APPL_CONST) LpAbsTimer;
  P2CONST(volatile Fr_59_Renesas_RegisterSetType, AUTOMATIC, FR_CONFIG_DATA) LpCtrlRegSet;
  P2VAR(volatile Fr_59_Renesas_TimerRegType, AUTOMATIC, REGSPACE) LpTimerReg;
  P2VAR(volatile uint32, AUTOMATIC, REGSPACE) LpFLXAnFRT2C;
  /* Declare the varible to store return value */
  Std_ReturnType LucReturnValue;
  uint32 LulTimerValue;
  /* Declare the variable to store the timer mode select */
  Fr_59_Renesas_TimerModeSelectType LenTimerModeSelect;
  /* Initialize the return value */
  LucReturnValue = E_OK;
  /* Copy global pointer to local pointer */
  LpAbsTimerConfig = Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pAbsTimerConfig;
  LpCtrlRegSet = Fr_59_Renesas_GpCtrlRegSet[Fr_CtrlIdx];                                                                
  LulTimerValue = FR_59_RENESAS_ZERO;                                                                                   /* PRQA S 2982 # JV-01 */
  /* Get the pointer to Absolute Timer configuration of the corresponding Fr_AbsTimerIdx */
  LpAbsTimer = &LpAbsTimerConfig[Fr_AbsTimerIdx];                                                                      
  /* Get the Timer mode */
  LenTimerModeSelect = LpAbsTimer->enTimerModeSelect;                                                                   
  /* Cycle Code Bit masking */
  Fr_CycleCode = Fr_CycleCode & (uint8)FR_59_RENESAS_CYCLE_CODE_MASK;                                                   /* PRQA S 1338 # JV-01 */
  /* Stop Absolute Timer by setting T0RC, T2RC bit */
  if (FR_59_RENESAS_TIMER0 == LpAbsTimer->enTimerSelection)
  {
    /* Read the value of the Timer 0 register */
    LpTimerReg = LpCtrlRegSet->pTimerReg;                                                                              
    LulTimerValue = LpTimerReg->ulFLXAnFRT0C;                                                                          
    /* Stop the Timer 0 */
    LpTimerReg->ulFLXAnFRT0C = LulTimerValue & FR_59_RENESAS_FLX0T0C_FLX0T0RC_HALT;
    /* Read the value of the timer register */
    LulTimerValue = LpTimerReg->ulFLXAnFRT0C;
    /* Clear the value of previous Timer mode, Cycle code and Macrotick value */
    LulTimerValue = LulTimerValue & FR_59_RENESAS_FLX0T0C_FLX0T0RC_CLR;
    /* Set Timer Mode Select, Macrotick Offset and Cycle Code */
    LulTimerValue = LulTimerValue | (((uint32)LenTimerModeSelect << FR_59_RENESAS_ONE) |
                                              ((uint32)Fr_Offset << FR_59_RENESAS_FLX0TXC_OFFSET_SHIFT) |
                                                            ((uint32)Fr_CycleCode << FR_59_RENESAS_FLX0TXC_CYC_SHIFT));
    /* Load the cycle and offset value in the timer register and start the timer */
    LpTimerReg->ulFLXAnFRT0C = LulTimerValue | FR_59_RENESAS_FLX0T0C_FLX0T0RC_SET;
  }
  else /* Timer 2 */
  {
    /* Read the value of the Timer 2 register */
    LpFLXAnFRT2C = LpCtrlRegSet->plFLXAnFRT2C;
    LulTimerValue = *LpFLXAnFRT2C;                                                                                     
    /* Stop the Timer 2 */
    *LpFLXAnFRT2C = LulTimerValue & FR_59_RENESAS_FLX0T2C_FLX0T2RC_HALT;
    /* Read the value of the timer register */
    LulTimerValue = *LpFLXAnFRT2C;
    /* Clear the value of previous cycle code and Macrotick value */
    LulTimerValue = LulTimerValue & FR_59_RENESAS_FLX0T2C_FLX0T2RC_CLR;
    /* Set Timer Mode Select, Macrotick Offset and Cycle Code */
    LulTimerValue = LulTimerValue | (((uint32)LenTimerModeSelect << FR_59_RENESAS_ONE) |
                                               ((uint32)Fr_Offset << FR_59_RENESAS_FLX0TXC_OFFSET_SHIFT) |
                                                            ((uint32)Fr_CycleCode << FR_59_RENESAS_FLX0TXC_CYC_SHIFT));
    /* Load the cycle and offset value in the timer register and start the timer */
    *LpFLXAnFRT2C = LulTimerValue | FR_59_RENESAS_FLX0T2C_FLX0T2RC_SET;
  }
  return (LucReturnValue);
} /* End of function Fr_59_Renesas_SetCycleOffset */
#define FR_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_OutputTransferRequest
**
** Service ID            : Not Applicable
**
** Description           : This function is to request to run Output Transfer
**                         by FlexRay User Output Transfer Request Register
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx, Fr_OutputTableContentPtr
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : None
**
** Global Variables Used : Fr_59_Renesas_GpCtrlRegSet,
**                         Fr_59_Renesas_GpControllerConfigPtr
**
** Functions Invoked     : FR_59_RENESAS_DEM_REPORT_ERROR
**
** Registers Used        : FLXAnFROTS, FLXAnFROBA, FLXAnFRUOR,
**                         FLXAnFRDAi(i = 0 to 3)
**
** Reference ID          : FR_DUD_ACT_062, FR_DUD_ACT_062_ERR001,
** Reference ID          : FR_DUD_ACT_062_ERR002, FR_DUD_ACT_062_ERR003,
** Reference ID          : FR_DUD_ACT_062_ERR004, FR_DUD_ACT_062_ERR005,
** Reference ID          : FR_DUD_ACT_062_REG001, FR_DUD_ACT_062_REG002,
** Reference ID          : FR_DUD_ACT_062_REG003, FR_DUD_ACT_062_REG004,
** Reference ID          : FR_DUD_ACT_062_REG005
***********************************************************************************************************************/
#if (FR_59_RENESAS_ENABLE_OUTPUT_RX_HANDLER == STD_ON)
#define FR_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PRIVATE_CODE) Fr_59_Renesas_OutputTransferRequest(const uint8 Fr_CtrlIdx,                   
                                         volatile Fr_59_Renesas_OutputPointerTableType *const Fr_OutputTableContentPtr) /* PRQA S 3673 # JV-01 */
{
  /* Declare pointer to register */
  P2CONST(volatile Fr_59_Renesas_RegisterSetType, AUTOMATIC, FR_CONFIG_DATA) LpCtrlRegSet;
  P2VAR(volatile Fr_59_Renesas_DataTransferControlRegType, AUTOMATIC, REGSPACE) LpDataTransferCtrlReg;
  P2VAR(volatile Fr_59_Renesas_DataTransferStatusRegType, AUTOMATIC, REGSPACE) LpDataTransferStatusReg;
  /* Declare local pointer to CC configuration */
  P2CONST(Fr_59_Renesas_CtrlTableType, TYPEDEF, FR_CONFIG_DATA) LpCtrlTable;
  P2VAR(volatile Fr_59_Renesas_OutputPointerTableType, AUTOMATIC, FR_APPL_DATA) LpOutputPointerTable;
  /* Declare local pointer to Dem Event Id */
  P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF, FR_CONFIG_DATA) LpDemEventId;
  uint32 LulData;
  uint8 LucMessageBuffer;
  Std_ReturnType LucReturnValue;
  uint8 LucMsgBufferMask;
  volatile uint16 LusLoopCount;
  uint8 LucFRDAindex;
  /* Initialize the loop count to FR_59_RENESAS_ZERO */
  LusLoopCount = FR_59_RENESAS_ZERO;
  LucReturnValue = E_OK;
  /* Copy global pointer to local pointer */
  LpCtrlRegSet = Fr_59_Renesas_GpCtrlRegSet[Fr_CtrlIdx];                                                                
  LpDemEventId = (P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF,
                                         FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pDemEventId);
  LpDataTransferCtrlReg = LpCtrlRegSet->pDataTransferCtrlReg;                                                          
  LpDataTransferStatusReg = LpCtrlRegSet->pDataTransferStatusReg;
  LucMessageBuffer = Fr_OutputTableContentPtr->ucMsgBuffer;                                                             
  LulData = LpDataTransferStatusReg->ulFLXAnFROTS;                                                                     
  /* Check for Output Transfer enabled, no pending user output transfer request pending */
  if ((FR_59_RENESAS_FLX0FROTS_FLX0_OTS_MASK == (LulData & FR_59_RENESAS_FLX0FROTS_FLX0_OTS_MASK)) &&
                        (FR_59_RENESAS_FLX0FROTS_FLX0_UORP_MASK != (LulData & FR_59_RENESAS_FLX0FROTS_FLX0_UORP_MASK)))
  {
    LpCtrlTable = (P2CONST(Fr_59_Renesas_CtrlTableType, AUTOMATIC,
                                          FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pCtrlTable);
    /* Get the output table base address */
    LulData = LpDataTransferCtrlReg->ulFLXAnFROBA;                                                                     
    /* Get the address of output pointer table */
    LpOutputPointerTable =
        (volatile Fr_59_Renesas_OutputPointerTableType *)(LulData +                                                     /* PRQA S 0303, 3383 # JV-01, JV-01 */
                                                              ((uint32)LucMessageBuffer * (uint32)FR_59_RENESAS_FOUR)); /* PRQA S 3384 # JV-01 */
    /* Write the output data structure address to output pointer table */
    LpOutputPointerTable->Fr_59_Renesas_pOutputDataPtr = Fr_OutputTableContentPtr->Fr_59_Renesas_pOutputDataPtr;        
    /* Update the Message buffer in User Output Transfer Request Register */
    /* Writing in to FlexRay User Output transfer Request Register and mirror address */
    LpDataTransferCtrlReg->ulFLXAnFRUOR = (LucMessageBuffer | FR_59_RENESAS_FLX0FRUOR_URDS_SET);
    /* Message buffer number is masked in range of 0-31 */
    LucMsgBufferMask = LucMessageBuffer & FR_59_RENESAS_FLXnFRDAi_MASK;
    /* Get the index of DA register for the given message buffer */
    LucFRDAindex = (LucMessageBuffer >> FR_59_RENESAS_FIVE) & FR_59_RENESAS_FLXnFRDA_INDEX_MASK;
    switch (LucFRDAindex)
    {
    case FR_59_RENESAS_FLX0FRDA_INDEX_ZERO:
      /* Get the position of DA flag to be cleared */
      LulData = ((uint32)FR_59_RENESAS_ONE << LucMsgBufferMask);
      LpDataTransferStatusReg->ulFLXAnFRDA0 = LulData;
      while (((LpDataTransferStatusReg->ulFLXAnFRDA0 & LulData) != LulData)                                           
                                                         && (LusLoopCount < (uint16)(LpCtrlTable->usFlagClearMaxWait))) /* PRQA S 3415, 3416 # JV-01, JV-01 */
      {
        /* Increment the loop count */
        LusLoopCount++;                                                                                                 /* PRQA S 3387, 3383 # JV-01, JV-01 */
      }
      if (LusLoopCount == (uint16)(LpCtrlTable->usFlagClearMaxWait))                                                    /* PRQA S 3416 # JV-01 */
      {
        if (FR_59_RENESAS_DEM_NOT_CONFIGURED != LpDemEventId->usReadTimeoutFailure)                                     
        {
          FR_59_RENESAS_DEM_REPORT_ERROR(LpDemEventId->usReadTimeoutFailure, DEM_EVENT_STATUS_FAILED);
        } /* else No Action required */
        /* Set Return Value as E_NOT_OK */
        LucReturnValue = E_NOT_OK;
      } /* else No Action required */
      break;
    case FR_59_RENESAS_FLX0FRDA_INDEX_ONE:
      /* Get the position of DA flag to be cleared */
      LulData = ((uint32)FR_59_RENESAS_ONE << LucMsgBufferMask);
      LpDataTransferStatusReg->ulFLXAnFRDA1 = LulData;
      while (((LpDataTransferStatusReg->ulFLXAnFRDA1) != LulData)                                                    
                                                         && (LusLoopCount < (uint16)(LpCtrlTable->usFlagClearMaxWait))) /* PRQA S 3415, 3416 # JV-01, JV-01 */
      {
        /* Increment the loop count */
        LusLoopCount++;                                                                                                 /* PRQA S 3387, 3383 # JV-01, JV-01 */
      }
      if (LusLoopCount == (uint16)(LpCtrlTable->usFlagClearMaxWait))                                                    /* PRQA S 3416 # JV-01 */
      {
        if (FR_59_RENESAS_DEM_NOT_CONFIGURED != LpDemEventId->usReadTimeoutFailure)
        {
          FR_59_RENESAS_DEM_REPORT_ERROR(LpDemEventId->usReadTimeoutFailure, DEM_EVENT_STATUS_FAILED);
        } /* else No Action required */
        /* Set Return Value as E_NOT_OK */
        LucReturnValue = E_NOT_OK;
      } /* else No Action required */
      break;
    case FR_59_RENESAS_FLX0FRDA_INDEX_TWO:
      /* Get the position of DA flag to be cleared */
      LulData = ((uint32)FR_59_RENESAS_ONE << LucMsgBufferMask);
      LpDataTransferStatusReg->ulFLXAnFRDA2 = LulData;
      while (((LpDataTransferStatusReg->ulFLXAnFRDA2) != LulData)                                                      
                                                         && (LusLoopCount < (uint16)(LpCtrlTable->usFlagClearMaxWait))) /* PRQA S 3415, 3416 # JV-01, JV-01 */
      {
        /* Increment the loop count */
        LusLoopCount++;                                                                                                 /* PRQA S 3387, 3383 # JV-01, JV-01 */
      }
      if (LusLoopCount == (uint16)(LpCtrlTable->usFlagClearMaxWait))                                                    /* PRQA S 3416 # JV-01 */
      {
        if (FR_59_RENESAS_DEM_NOT_CONFIGURED != LpDemEventId->usReadTimeoutFailure)
        {
          FR_59_RENESAS_DEM_REPORT_ERROR(LpDemEventId->usReadTimeoutFailure, DEM_EVENT_STATUS_FAILED);
        } /* else No Action required */
        /* Set Return Value as E_NOT_OK */
        LucReturnValue = E_NOT_OK;
      } /* else No Action required */
      break;
    default:
      /* Get the position of DA flag to be cleared */
      LulData = ((uint32)FR_59_RENESAS_ONE << LucMsgBufferMask);
      LpDataTransferStatusReg->ulFLXAnFRDA3 = LulData;
      while (((LpDataTransferStatusReg->ulFLXAnFRDA3) != LulData)                                                   
                                                         && (LusLoopCount < (uint16)(LpCtrlTable->usFlagClearMaxWait))) /* PRQA S 3415, 3416 # JV-01, JV-01 */
      {
        /* Increment the loop count */
        LusLoopCount++;                                                                                                 /* PRQA S 3387, 3383 # JV-01, JV-01 */
      }
      if (LusLoopCount == (uint16)(LpCtrlTable->usFlagClearMaxWait))                                                    /* PRQA S 3416 # JV-01 */
      {
        if (FR_59_RENESAS_DEM_NOT_CONFIGURED != LpDemEventId->usReadTimeoutFailure)
        {
          FR_59_RENESAS_DEM_REPORT_ERROR(LpDemEventId->usReadTimeoutFailure, DEM_EVENT_STATUS_FAILED);
        } /* else No Action required */
        /* Set Return Value as E_NOT_OK */
        LucReturnValue = E_NOT_OK;
      } /* else No Action required */
      break;
    }
  }
  else
  {
    /* Raise DEM Error FAILED */
    if (FR_59_RENESAS_DEM_NOT_CONFIGURED != LpDemEventId->usHardwareTestFailure)
    {
      FR_59_RENESAS_DEM_REPORT_ERROR(LpDemEventId->usHardwareTestFailure, DEM_EVENT_STATUS_FAILED);
    } /* else No Action required */
    /* Set Return Value as E_NOT_OK */
    LucReturnValue = E_NOT_OK;
  }
  return (LucReturnValue);
} /* End of function Fr_59_Renesas_OutputTransferRequest */
#define FR_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
#endif
/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_InputTransferRequest
**
** Service ID            : Not Applicable
**
** Description           : This function is to request Input Transfer by
**                         FlexRay User Input Transfer Request Register
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx, Fr_InputTableContentPtr
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : None
**
** Global Variables Used : Fr_59_Renesas_GpControllerConfigPtr,
**                         Fr_59_Renesas_GpCtrlRegSet
**
** Functions Invoked     : FR_59_RENESAS_DEM_REPORT_ERROR
**
** Registers Used        : FLXAnFRITS, FLXAnFRIBA, FLXAnFRITC, FLXAnFRUIR
**
** Reference ID          : FR_DUD_ACT_063, FR_DUD_ACT_063_ERR001,
** Reference ID          : FR_DUD_ACT_063_REG001
***********************************************************************************************************************/
#if (FR_59_RENESAS_ENABLE_INPUT_TX_HANDLER == STD_ON)
#define FR_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PRIVATE_CODE) Fr_59_Renesas_InputTransferRequest(const uint8 Fr_CtrlIdx,                   
                                           volatile Fr_59_Renesas_InputPointerTableType *const Fr_InputTableContentPtr) /* PRQA S 3673 # JV-01 */
{
  /* Declare pointer to register */
  P2CONST(volatile Fr_59_Renesas_RegisterSetType, AUTOMATIC, FR_CONFIG_DATA) LpCtrlRegSet;
  P2VAR(volatile Fr_59_Renesas_DataTransferControlRegType, AUTOMATIC, REGSPACE) LpDataTransferCtrlReg;
  P2VAR(volatile Fr_59_Renesas_DataTransferStatusRegType, AUTOMATIC, REGSPACE) LpDataTransferStatusReg;                 /* PRQA S 3678 # JV-01 */
  P2VAR(volatile Fr_59_Renesas_InputPointerTableType, AUTOMATIC, FR_APPL_DATA) LpInputPointerTablePtr;
  /* Declare local pointer to Dem Event Id */
  P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF, FR_CONFIG_DATA) LpDemEventId;
  /* Declare the variable to store the return value */
  Std_ReturnType LucReturnValue;
  uint32 LulData;
  uint32 LulData_Size;
  /* Copy global pointer to local pointer */
  LpCtrlRegSet = Fr_59_Renesas_GpCtrlRegSet[Fr_CtrlIdx];                                                                
  LpDataTransferCtrlReg = LpCtrlRegSet->pDataTransferCtrlReg;                                                          
  LpDataTransferStatusReg = LpCtrlRegSet->pDataTransferStatusReg;
  /* Check for Input Transfer enabled, input queue is not halted and no pending user input transfer requested */
  LulData = LpDataTransferStatusReg->ulFLXAnFRITS;                                                                     
  if ((FR_59_RENESAS_FLX0FRITS_FLX0_ITS_MASK == (LulData & FR_59_RENESAS_FLX0FRITS_FLX0_ITS_MASK)) &&
               (FR_59_RENESAS_FLX0FRITS_FLX0_IQH_MASK != (LulData & FR_59_RENESAS_FLX0FRITS_FLX0_IQH_MASK)) &&
                        (FR_59_RENESAS_FLX0FRITS_FLX0_UIRP_MASK != (LulData & FR_59_RENESAS_FLX0FRITS_FLX0_UIRP_MASK)))
  {
    /* Get the input pointer table base address */
    LulData = LpDataTransferCtrlReg->ulFLXAnFRIBA;                                                                     
    /* Get the size of the input pointer table */
    /* Read the first msg buffer of FIFO from FRMRC register */
    LulData_Size = LpDataTransferCtrlReg->ulFLXAnFRITC;
    LulData_Size = LulData_Size & FR_59_RENESAS_FLX0FRITS_FLX0_ITM_MASK;
    /* User input transfer address */
    /* Calculate user input transfer address */
    LpInputPointerTablePtr = (volatile Fr_59_Renesas_InputPointerTableType *)                                           /* PRQA S 0303 # JV-01 */
    (LulData + (((LulData_Size >> FR_59_RENESAS_SIXTEEN) + (uint32)FR_59_RENESAS_ONE) * (uint32)FR_59_RENESAS_EIGHT));  /* PRQA S 3383, 3384 # JV-01, JV-01 */
    /* Write the control register in user input pointer table */
    LpInputPointerTablePtr->ulFLX0FRWRHS4 = (Fr_InputTableContentPtr->ulFLX0FRWRHS4);                                   
    /* Write the Data pointer in user input pointer table */
    LpInputPointerTablePtr->Fr_59_Renesas_pInputDataPtr = (Fr_InputTableContentPtr->Fr_59_Renesas_pInputDataPtr);
    /* Get the size to calculate UIDX */
    LulData = LpDataTransferCtrlReg->ulFLXAnFRITC;
    LulData = LulData & FR_59_RENESAS_FLX0FRITS_FLX0_ITM_MASK;
    /* User requested pointer index */
    LulData = (LulData >> FR_59_RENESAS_SIXTEEN) + (uint32)FR_59_RENESAS_ONE;                                           /* PRQA S 3383 # JV-01 */
    /* Update the Input pointer table index requested for input transfer */
    /* Writing in to FlexRay User Input transfer Request Register and mirror address */
    LpDataTransferCtrlReg->ulFLXAnFRUIR = LulData;
    LucReturnValue = E_OK;
  }
  else
  {
    /* Raise DEM Error FAILED */
    LpDemEventId = (P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF,
                                         FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pDemEventId);
    if (FR_59_RENESAS_DEM_NOT_CONFIGURED != LpDemEventId->usHardwareTestFailure)                                        
    {
      FR_59_RENESAS_DEM_REPORT_ERROR(LpDemEventId->usHardwareTestFailure, DEM_EVENT_STATUS_FAILED);
    } /* else No Action required */
    /* Set Return Value as E_NOT_OK */
    LucReturnValue = E_NOT_OK;
  }
  return (LucReturnValue);
} /* End of function Fr_59_Renesas_InputTransferRequest */
#define FR_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
#endif
/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_ResetOutputTransfer
**
** Service ID            : Not Applicable
**
** Description           : This function is to disable the Output transfer.
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : None
**
** Global Variables Used : Fr_59_Renesas_GpControllerConfigPtr,
**                         Fr_59_Renesas_GpCtrlRegSet
**
** Functions Invoked     : FR_59_RENESAS_DEM_REPORT_ERROR
**
** Registers Used        : FLXAnFROTS, FLXAnFROTC
**
** Reference ID          : FR_DUD_ACT_064, FR_DUD_ACT_064_ERR001,
** Reference ID          : FR_DUD_ACT_064_ERR002, FR_DUD_ACT_064_REG001
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PRIVATE_CODE) Fr_59_Renesas_ResetOutputTransfer(const uint8 Fr_CtrlIdx)                      
{
  /* Declare pointer to register */
  P2CONST(volatile Fr_59_Renesas_RegisterSetType, AUTOMATIC, FR_CONFIG_DATA) LpCtrlRegSet;
  P2VAR(volatile Fr_59_Renesas_DataTransferStatusRegType, AUTOMATIC, REGSPACE) LpDataTransferStatusReg;                 /* PRQA S 3678 # JV-01 */
  P2VAR(volatile Fr_59_Renesas_DataTransferControlRegType, AUTOMATIC, REGSPACE) LpDataTransferCtrlReg;
  /* Declare local pointer to CC configuration */
  P2CONST(Fr_59_Renesas_CtrlTableType, TYPEDEF, FR_CONFIG_DATA) LpCtrlTable;
  uint32 LulData;
  volatile uint16 LusLoopCount;
  Std_ReturnType LucReturnValue;
  /* Declare local pointer to Dem Event Id */
  P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF, FR_CONFIG_DATA) LpDemEventId;
  /* Copy global pointer to local pointer */
  LpCtrlRegSet = Fr_59_Renesas_GpCtrlRegSet[Fr_CtrlIdx];                                                                
  LpDataTransferStatusReg = LpCtrlRegSet->pDataTransferStatusReg;                                                      
  LpDataTransferCtrlReg = LpCtrlRegSet->pDataTransferCtrlReg;
  LpDemEventId = (P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF,
                                         FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pDemEventId);
  /* Read current value of FLX0FROTS register */
  /* Check for Output Transfer enable */
  LulData = LpDataTransferStatusReg->ulFLXAnFROTS;                                                                     
  if (FR_59_RENESAS_FLX0FROTS_FLX0_OTS_MASK == (LulData & FR_59_RENESAS_FLX0FROTS_FLX0_OTS_MASK))
  {
    LpCtrlTable = (P2CONST(Fr_59_Renesas_CtrlTableType, AUTOMATIC,
                                          FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pCtrlTable);
    /* Read current value of FLX0FROTC register */
    LulData = LpDataTransferCtrlReg->ulFLXAnFROTC;                                                                     
    /*Disable the Output Transfer handler */
    LulData = LulData & FR_59_RENESAS_FLX0FROTC_OTE_RESET;
    /* Writing in to FlexRay Output Transfer Configuration Register and mirror address */
    LpDataTransferCtrlReg->ulFLXAnFROTC = LulData;
    /* Initialize the loop count to FR_59_RENESAS_ZERO */
    LusLoopCount = FR_59_RENESAS_ZERO;
    /* Wait until Output Transfer is disabled */
    while ((FR_59_RENESAS_FLX0FROTS_FLX0_OTS_MASK                                                                    
               == (LpDataTransferStatusReg->ulFLXAnFROTS & FR_59_RENESAS_FLX0FROTS_FLX0_OTS_MASK)) &&
                                                            (LusLoopCount < (uint16)(LpCtrlTable->usFlagClearMaxWait))) /* PRQA S 3415, 3416 # JV-01, JV-01 */
    {
      /* Increment the loop count */
      LusLoopCount++;                                                                                                   /* PRQA S 3387, 3383 # JV-01, JV-01 */
    }
    if (LusLoopCount == (uint16)(LpCtrlTable->usFlagClearMaxWait))                                                      /* PRQA S 3416 # JV-01 */
    {
      if (FR_59_RENESAS_DEM_NOT_CONFIGURED != LpDemEventId->usReadTimeoutFailure)                                       
      {
        FR_59_RENESAS_DEM_REPORT_ERROR(LpDemEventId->usReadTimeoutFailure, DEM_EVENT_STATUS_FAILED);
      } /* else No Action required */
      /* Set Return Value as E_NOT_OK */
      LucReturnValue = E_NOT_OK;
    }
    else
    {
      /* Set Return Value as E_OK */
      LucReturnValue = E_OK;
    }
  }
  else
  {
    /* Raise DEM Error FAILED */
    if (FR_59_RENESAS_DEM_NOT_CONFIGURED != LpDemEventId->usHardwareTestFailure)
    {
      FR_59_RENESAS_DEM_REPORT_ERROR(LpDemEventId->usHardwareTestFailure, DEM_EVENT_STATUS_FAILED);
    } /* else No Action required */
    /* Set Return Value as E_NOT_OK */
    LucReturnValue = E_NOT_OK;
  }
  return (LucReturnValue);
} /* End of function Fr_59_Renesas_ResetOutputTransfer */
#define FR_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_UpdateInputPtrTable
**
** Service ID            : Not Applicable
**
** Description           : This function is to update the Input pointer tabe
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx,
**                         Fr_InputTableContentPtr
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : None
**
** Global Variables Used : Fr_59_Renesas_GpCtrlRegSet,
**                         Fr_59_Renesas_GpControllerConfigPtr
**
** Functions Invoked     : FR_59_RENESAS_DEM_REPORT_ERROR
**
** Registers Used        : FLXAnFRITS, FLXAnFRIBA, FLXAnFRIQC, FLXAnFRAES
**
** Reference ID          : FR_DUD_ACT_066, FR_DUD_ACT_066_ERR001,
** Reference ID          : FR_DUD_ACT_066_ERR002, FR_DUD_ACT_066_ERR003,
** Reference ID          : FR_DUD_ACT_066_REG001, FR_DUD_ACT_066_REG002
***********************************************************************************************************************/
#if (FR_59_RENESAS_ENABLE_INPUT_TX_HANDLER == STD_ON)
#define FR_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PRIVATE_CODE) Fr_59_Renesas_UpdateInputPtrTable(const uint8 Fr_CtrlIdx,                  
                                           volatile Fr_59_Renesas_InputPointerTableType *const Fr_InputTableContentPtr) /* PRQA S 3673 # JV-01 */
{
  /* Declare pointer to register */
  P2CONST(volatile Fr_59_Renesas_RegisterSetType, AUTOMATIC, FR_CONFIG_DATA) LpCtrlRegSet;
  P2VAR(volatile Fr_59_Renesas_DataTransferControlRegType, AUTOMATIC, REGSPACE) LpDataTransferCtrlReg;
  P2VAR(volatile Fr_59_Renesas_DataTransferStatusRegType, AUTOMATIC, REGSPACE) LpDataTransferStatusReg;
  /* Declare the variable to store return value */
  Std_ReturnType LucReturnValue;
  /* Declare the variable to store the access error */
  uint32 LulAccessError;
  /* Declare the variable to store register value */
  uint32 LulData;
  /* Declare the variable to store the index */
  uint32 LulPut_index;
  /* Declare the pointer to which Input Table point */
  P2VAR(volatile Fr_59_Renesas_InputPointerTableType, AUTOMATIC, FR_APPL_DATA)
  LpInputPointerTablePtr;
  /* Declare local pointer to Dem Event Id */
  P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF, FR_CONFIG_DATA) LpDemEventId;
  /* Copy global pointer to local pointer */
  LpCtrlRegSet = Fr_59_Renesas_GpCtrlRegSet[Fr_CtrlIdx];                                                                
  LpDataTransferCtrlReg = LpCtrlRegSet->pDataTransferCtrlReg;                                                          
  LpDataTransferStatusReg = LpCtrlRegSet->pDataTransferStatusReg;
  LpDemEventId = (P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF,
                                         FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pDemEventId);
  LulData = LpDataTransferStatusReg->ulFLXAnFRITS;                                                                     
  /* Writing in to FlexRay Access Error Status Register and mirror address */
  LpDataTransferStatusReg->ulFLXAnFRAES = FR_59_RENESAS_FLX0FRAES_RESET;
  /* Check for Input Transfer enable and Input queue not halted */
  if ((FR_59_RENESAS_FLX0FRITS_FLX0_ITS_MASK == (LulData & FR_59_RENESAS_FLX0FRITS_FLX0_ITS_MASK)) &&
                          (FR_59_RENESAS_FLX0FRITS_FLX0_IQH_MASK != (LulData & FR_59_RENESAS_FLX0FRITS_FLX0_IQH_MASK)))
  {
    /* Get the putindex */
    LulData = LpDataTransferStatusReg->ulFLXAnFRITS;
    LulPut_index = ((LulData & FR_59_RENESAS_FLX0FRITS_FLX0_IPIDX_MASK) >> FR_59_RENESAS_SIXTEEN);
    /* Check for input queue is not full */
    if (FR_59_RENESAS_FLX0FRITS_FLX0_IQFP_MASK != (LulData & FR_59_RENESAS_FLX0FRITS_FLX0_IQFP_MASK))
    {
      LulData = LpDataTransferCtrlReg->ulFLXAnFRIBA;                                                                   
      /* Get the address to write the control reg and data pointer */
      LpInputPointerTablePtr = (volatile Fr_59_Renesas_InputPointerTableType *)                                         /* PRQA S 0303 # JV-01 */
                                                              (LulData + (LulPut_index * (uint32)FR_59_RENESAS_EIGHT)); /* PRQA S 3383 # JV-01 */
      /* Write the control reg in input pointer */
      LpInputPointerTablePtr->ulFLX0FRWRHS4 = (Fr_InputTableContentPtr->ulFLX0FRWRHS4);                                 

      /* Write the Data pointer in input pointer */
      LpInputPointerTablePtr->Fr_59_Renesas_pInputDataPtr = (Fr_InputTableContentPtr->Fr_59_Renesas_pInputDataPtr);
      /* Get the Message buffer from control register */
      LulData = ((Fr_InputTableContentPtr->ulFLX0FRWRHS4) & FR_59_RENESAS_FLX0FRWRHS4_FLX0_IMBNR);
      /* Update the Message buffer in Input Queue Control Register */
      /* Writing in to register and mirror address */
      LpDataTransferCtrlReg->ulFLXAnFRIQC = LulData;
      LulAccessError = LpDataTransferStatusReg->ulFLXAnFRAES;
      if ((uint32)FR_59_RENESAS_ZERO < (LulAccessError & FR_59_RENESAS_FLX0FRAES_ERR_MASK))
      {
        /* Raise DEM Error FAILED */
        if (FR_59_RENESAS_DEM_NOT_CONFIGURED != LpDemEventId->usHardwareTestFailure)                                    
        {
          FR_59_RENESAS_DEM_REPORT_ERROR(LpDemEventId->usHardwareTestFailure, DEM_EVENT_STATUS_FAILED);
        } /* else No Action required */
        LucReturnValue = E_NOT_OK;
      }
      else
      {
        LucReturnValue = E_OK;
      }
    }
    else
    {
      /* Raise DEM Error FAILED */
      if (FR_59_RENESAS_DEM_NOT_CONFIGURED != LpDemEventId->usHardwareTestFailure)
      {
        FR_59_RENESAS_DEM_REPORT_ERROR(LpDemEventId->usHardwareTestFailure, DEM_EVENT_STATUS_FAILED);
      } /* else No Action required */
      LucReturnValue = E_NOT_OK;
    }
  }
  else
  {
    /* Raise DEM Error FAILED */
    if (FR_59_RENESAS_DEM_NOT_CONFIGURED != LpDemEventId->usHardwareTestFailure)
    {
      FR_59_RENESAS_DEM_REPORT_ERROR(LpDemEventId->usHardwareTestFailure, DEM_EVENT_STATUS_FAILED);
    } /* else No Action required */
    /* Set Return Value as E_NOT_OK */
    LucReturnValue = E_NOT_OK;
  }
  return (LucReturnValue);
} /* End of Fr_59_Renesas_UpdateInputPtrTable */
#define FR_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
#endif
/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_UpdateOutputPtrTable
**
** Service ID            : Not Applicable
**
** Description           : This function is to clear the bit appropriated to
**                         the message buffer of received frames.
**                         and
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx,
**                         Fr_OutputTableContentPtr
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : None
**
** Global Variables Used : Fr_59_Renesas_GpControllerConfigPtr,
**                         Fr_59_Renesas_GpCtrlRegSet
**
** Functions Invoked     : FR_59_RENESAS_DEM_REPORT_ERROR
**
** Registers Used        : FLXAnFRMRC, FLXAnFRDAi(i = 0 to 3), FLXAnFROTS
**
** Reference ID          : FR_DUD_ACT_067, FR_DUD_ACT_067_ERR001,
** Reference ID          : FR_DUD_ACT_067_ERR002, FR_DUD_ACT_067_REG001,
** Reference ID          : FR_DUD_ACT_067_REG002, FR_DUD_ACT_067_REG003,
** Reference ID          : FR_DUD_ACT_067_REG004, FR_DUD_ACT_067_REG005
***********************************************************************************************************************/
#if ((FR_59_RENESAS_ENABLE_OUTPUT_RX_HANDLER == STD_ON) || (FR_59_RENESAS_ENABLE_OUTPUT_RX_FIFO_HANDLER == STD_ON))
#define FR_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PRIVATE_CODE) Fr_59_Renesas_UpdateOutputPtrTable(const uint8 Fr_CtrlIdx,                    
                                   const volatile Fr_59_Renesas_OutputPointerTableType *const Fr_OutputTableContentPtr)
{
  /* Declare pointer to register */
  P2CONST(volatile Fr_59_Renesas_RegisterSetType, AUTOMATIC, FR_CONFIG_DATA) LpCtrlRegSet;
  P2VAR(volatile Fr_59_Renesas_MessageBufferControlRegType, AUTOMATIC, REGSPACE) LpMBCtrlReg;                           /* PRQA S 3678 # JV-01 */
  P2VAR(volatile Fr_59_Renesas_DataTransferStatusRegType, AUTOMATIC, REGSPACE) LpDataTransferStatusReg;
  /* Declare local pointer to Dem Event Id */
  P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF, FR_CONFIG_DATA) LpDemEventId;
  /* Declare the variable to store the message buffer number */
  uint8 LucMessageBuffer;
  /* Declare the variable to store the mask of message buffer number */
  #if (FR_59_RENESAS_ENABLE_OUTPUT_RX_HANDLER == STD_ON)
  uint8 LucMsgBufferMask;
  /* Declare the variable to store the index of DA register */
  uint8 LucFRDAindex;
  #endif
  uint32 LulData;
  uint8 LucFirstFifoBuff;
  Std_ReturnType LucReturnValue;
  LucReturnValue = E_OK;
  LucMessageBuffer = Fr_OutputTableContentPtr->ucMsgBuffer;                                                             
  /* Copy global pointer to local pointer */
  LpCtrlRegSet = Fr_59_Renesas_GpCtrlRegSet[Fr_CtrlIdx];                                                                
  LpMBCtrlReg = LpCtrlRegSet->pMBCtrlReg;                                                                              
  LpDataTransferStatusReg = LpCtrlRegSet->pDataTransferStatusReg;
  LpDemEventId = (P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF,
                                         FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pDemEventId);
  /* Check Output transfer enabled */
  LulData = LpDataTransferStatusReg->ulFLXAnFROTS;                                                                     
  if (FR_59_RENESAS_FLX0FROTS_FLX0_OTS_MASK == (LulData & FR_59_RENESAS_FLX0FROTS_FLX0_OTS_MASK))
  {
    /* Read the first msg buffer of FIFO from FRMRC register */
    LulData = LpMBCtrlReg->ulFLXAnFRMRC;                                                                               
    LulData = LulData & FR_59_RENESAS_FLX0MRC_FFB_MASK;
    LucFirstFifoBuff = (uint8)(LulData >> FR_59_RENESAS_EIGHT);
    /* Check whether the requested msg buffer belongs to FIFO */
    if (LucMessageBuffer < LucFirstFifoBuff)
    {
      /* Check Output pointer transfer enabled */
      #if (FR_59_RENESAS_ENABLE_OUTPUT_RX_HANDLER == STD_ON)
      /* Mask buffer number in range of 0-31 */
      LucMsgBufferMask = LucMessageBuffer & FR_59_RENESAS_FLXnFRDAi_MASK;
      /* Get the index of DA register for the given message buffer */
      LucFRDAindex = (LucMessageBuffer >> FR_59_RENESAS_FIVE) & FR_59_RENESAS_FLXnFRDA_INDEX_MASK;
      /* Clear the corresponding DA flag */
      /* Get the position of DA flag to be cleared */
      LulData = ((uint32)FR_59_RENESAS_ONE << LucMsgBufferMask);
      switch (LucFRDAindex)
      {
      case FR_59_RENESAS_FLX0FRDA_INDEX_ZERO:
        /* Writing in to FlexRay message Data Available Register and mirror address */
        LpDataTransferStatusReg->ulFLXAnFRDA0 = LulData;
        break;
      case FR_59_RENESAS_FLX0FRDA_INDEX_ONE:
        /* Writing in to FlexRay message Data Available Register and mirror address */
        LpDataTransferStatusReg->ulFLXAnFRDA1 = LulData;
        break;
      case FR_59_RENESAS_FLX0FRDA_INDEX_TWO:
        /* Writing in to FlexRay message Data Available Register and mirror address */
        LpDataTransferStatusReg->ulFLXAnFRDA2 = LulData;
        break;
      default:
        /* Writing in to FlexRay message Data Available Register and mirror address */
        LpDataTransferStatusReg->ulFLXAnFRDA3 = LulData;
        break;
      }
    #endif
    }
    else
    {
      /* Check Output pointer FIFO transfer enabled */
      #if (FR_59_RENESAS_ENABLE_OUTPUT_RX_FIFO_HANDLER == STD_ON)
      LulData = LpDataTransferStatusReg->ulFLXAnFROTS;
      LulData = LulData & FR_59_RENESAS_FLX0FROTS_FFL_MASK;
      if ((uint32)FR_59_RENESAS_ZERO != LulData)
      {
        /* Writing in to FlexRay Output Transfer Status Register and
         mirror address */
        LpDataTransferStatusReg->ulFLXAnFROTS = FR_59_RENESAS_FLX0FROTS_FDA_RESET;
        /* Set Return Value as E_OK */
        LucReturnValue = E_OK;
      }
      else
      {
        /* Raise DEM Error FAILED */
        if (FR_59_RENESAS_DEM_NOT_CONFIGURED != LpDemEventId->usHardwareTestFailure)                                    
        {
          FR_59_RENESAS_DEM_REPORT_ERROR(LpDemEventId->usHardwareTestFailure, DEM_EVENT_STATUS_FAILED);
        } /* else No Action required */
        /* Set Return Value as E_NOT_OK */
        LucReturnValue = E_NOT_OK;
      }
      #endif
    }
  }
  else
  {
    /* Raise DEM Error FAILED */
    if (FR_59_RENESAS_DEM_NOT_CONFIGURED != LpDemEventId->usHardwareTestFailure)
    {
      FR_59_RENESAS_DEM_REPORT_ERROR(LpDemEventId->usHardwareTestFailure, DEM_EVENT_STATUS_FAILED);
    } /* else No Action required */
    /* Set Return Value as E_NOT_OK */
    LucReturnValue = E_NOT_OK;
  }
  return (LucReturnValue);
} /* End of Fr_59_Renesas_UpdateOutputPtrTable */
#define FR_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
#endif
/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_ResumeInputQueueTransfer
**
** Service ID            : Not Applicable
**
** Description           : This function resumes the input queue transfer.
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : None
**
** Global Variables Used : Fr_59_Renesas_GpControllerConfigPtr,
**                         Fr_59_Renesas_GpCtrlRegSet
**
** Functions Invoked     : FR_59_RENESAS_DEM_REPORT_ERROR
**
** Registers Used        : FLXAnFRITS, FLXAnFRIBCR, FLXAnFRITC
**
** Reference ID          : FR_DUD_ACT_068, FR_DUD_ACT_068_ERR001,
** Reference ID          : FR_DUD_ACT_068_ERR002, FR_DUD_ACT_068_REG001,
** Reference ID          : FR_DUD_ACT_068_REG002
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PRIVATE_CODE)
Fr_59_Renesas_ResumeInputQueueTransfer(const uint8 Fr_CtrlIdx)                                                  
{
  /* Declare pointer to register */
  P2CONST(volatile Fr_59_Renesas_RegisterSetType, AUTOMATIC, FR_CONFIG_DATA) LpCtrlRegSet;
  P2VAR(volatile Fr_59_Renesas_DataTransferControlRegType, AUTOMATIC, REGSPACE) LpDataTransferCtrlReg;
  P2VAR(volatile Fr_59_Renesas_DataTransferStatusRegType, AUTOMATIC, REGSPACE) LpDataTransferStatusReg;                 /* PRQA S 3678 # JV-01 */
  P2VAR(volatile Fr_59_Renesas_InputBufferRegType, AUTOMATIC, REGSPACE) LpInputBuffReg;                                 /* PRQA S 3678 # JV-01 */
  /* Declare local pointer to CC configuration */
  P2CONST(Fr_59_Renesas_CtrlTableType, TYPEDEF, FR_CONFIG_DATA) LpCtrlTable;
  /* Declare local pointer to Dem Event Id */
  P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF, FR_CONFIG_DATA)
  LpDemEventId;
  uint32 LulData;
  Std_ReturnType LucReturnValue;
  volatile uint16 LusLoopCount;
  LucReturnValue = E_NOT_OK;                                                                                            /* PRQA S 2982 # JV-01 */
  /* Copy global pointer to local pointer */
  LpCtrlRegSet = Fr_59_Renesas_GpCtrlRegSet[Fr_CtrlIdx];                                                                
  LpDataTransferCtrlReg = LpCtrlRegSet->pDataTransferCtrlReg;                                                          
  LpDataTransferStatusReg = LpCtrlRegSet->pDataTransferStatusReg;
  LpInputBuffReg = LpCtrlRegSet->pInputBuffReg;
  LpDemEventId = (P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF,
                                         FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pDemEventId);
  /* Read current value of FLX0FRITS register */
  LulData = LpDataTransferStatusReg->ulFLXAnFRITS;                                                                     
  /* Check for Input Transfer enable */
  if (FR_59_RENESAS_FLX0FRITS_FLX0_ITS_MASK != (LulData & FR_59_RENESAS_FLX0FRITS_FLX0_ITS_MASK))
  {
    LpCtrlTable = (P2CONST(Fr_59_Renesas_CtrlTableType, AUTOMATIC,
                                          FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pCtrlTable);
    /* Initialize the loop count to FR_59_RENESAS_ZERO */
    LusLoopCount = FR_59_RENESAS_ZERO;
    /* Wait until Transfer between IBF Shadow and Message RAM completed */
    while ((FR_59_RENESAS_FLX0IBCR_FLX0IBSYH_MASK == (LpInputBuffReg->ulFLXAnFRIBCR                                    
              & FR_59_RENESAS_FLX0IBCR_FLX0IBSYH_MASK)) &&  (LusLoopCount < (uint16)(LpCtrlTable->usFlagClearMaxWait))) /* PRQA S 3415, 3416 # JV-01, JV-01 */
    {
      /* Increment the loop count */
      LusLoopCount++;                                                                                                   /* PRQA S 3383, 3387 # JV-01, JV-01 */
    }
    if (LusLoopCount == (uint16)(LpCtrlTable->usFlagClearMaxWait))                                                      /* PRQA S 3416 # JV-01 */
    {
      if (FR_59_RENESAS_DEM_NOT_CONFIGURED != LpDemEventId->usReadTimeoutFailure)                                       
      {
        FR_59_RENESAS_DEM_REPORT_ERROR(LpDemEventId->usReadTimeoutFailure, DEM_EVENT_STATUS_FAILED);
      } /* else No Action required */
      /* Set Return Value as E_NOT_OK */
      LucReturnValue = E_NOT_OK;
    }
    else
    {
      /* Check for Input queue run request */
      if (FR_59_RENESAS_FLX0FRITS_FLX0_IQH_MASK == (LulData & FR_59_RENESAS_FLX0FRITS_FLX0_IQH_MASK))
      {
        LulData = LpDataTransferCtrlReg->ulFLXAnFRITC;                                                                 
        LulData = LulData & FR_59_RENESAS_FLX0FRITC_IQHR_RESET;
        /* The input queue resumes their operation */
        /* Writing in to FlexRay Input Transfer Configuration Register and mirror address */
        LpDataTransferCtrlReg->ulFLXAnFRITC = LulData;
      } /* else No Action required */
      /* Enable Input Transfer */
      /* This initialize the put and get index pointers to Zero */
      LulData = LpDataTransferCtrlReg->ulFLXAnFRITC;
      LulData = LulData | FR_59_RENESAS_FLX0FRITC_ITE_SET;
      /* Writing in to FlexRay Input Transfer Configuration Register and
       mirror address */
      LpDataTransferCtrlReg->ulFLXAnFRITC = LulData;
      LucReturnValue = E_OK;
    }
  }
  else
  {
    /* Raise DEM Error FAILED */
    if (FR_59_RENESAS_DEM_NOT_CONFIGURED != LpDemEventId->usHardwareTestFailure)
    {
      FR_59_RENESAS_DEM_REPORT_ERROR(LpDemEventId->usHardwareTestFailure, DEM_EVENT_STATUS_FAILED);
    } /* else No Action required */
    /* Set Return Value as E_NOT_OK */
    LucReturnValue = E_NOT_OK;
  }
  return (LucReturnValue);
} /* End of Fr_59_Renesas_ResumeInputQueueTransfer */
#define FR_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_DataAvailable
**
** Service ID            : Not Applicable
**
** Description           : This function is to initialize the output pointer
**                         table
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx, Fr_OutputTableContentPtr,
**                         Fr_FIFOTableContentPtr
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : Std_ReturnType E_NOT_OK or E_OK
**
** Preconditions         : None
**
** Global Variables Used : Fr_59_Renesas_GpControllerConfigPtr,
**                         Fr_59_Renesas_GpCtrlRegSet
**
** Functions Invoked     : FR_59_RENESAS_DEM_REPORT_ERROR
**
** Registers Used        : FLXAnFROTS, FLXAnFROBCR, FLXAnFRMRC, FLXAnFRFBA,
**                         FLXAnFRDAi(i = 0 to 3), FLXAnFROTC
**
** Reference ID          : FR_DUD_ACT_069, FR_DUD_ACT_069_ERR001,
** Reference ID          : FR_DUD_ACT_069_ERR002, FR_DUD_ACT_069_REG001,
** Reference ID          : FR_DUD_ACT_069_REG002, FR_DUD_ACT_069_REG003,
** Reference ID          : FR_DUD_ACT_069_REG004, FR_DUD_ACT_069_REG005
***********************************************************************************************************************/
#if ((FR_59_RENESAS_ENABLE_OUTPUT_RX_HANDLER == STD_ON) || (FR_59_RENESAS_ENABLE_OUTPUT_RX_FIFO_HANDLER == STD_ON))
#define FR_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PRIVATE_CODE) Fr_59_Renesas_DataAvailable(const uint8 Fr_CtrlIdx,                              
                                      volatile Fr_59_Renesas_OutputPointerTableType *const Fr_OutputTableContentPtr,    /* PRQA S 3673 # JV-01 */
                                           volatile Fr_59_Renesas_OutputPointerTableType *const Fr_FIFOTableContentPtr) /* PRQA S 3673 # JV-01 */
{
  /* Declare pointer to register */
  P2CONST(volatile Fr_59_Renesas_RegisterSetType, AUTOMATIC, FR_CONFIG_DATA) LpCtrlRegSet;
  #if (FR_59_RENESAS_ENABLE_OUTPUT_RX_HANDLER == STD_ON)
  P2VAR(volatile Fr_59_Renesas_MessageBufferControlRegType, AUTOMATIC, REGSPACE) LpMBCtrlReg;                           /* PRQA S 3678 # JV-01 */
  #endif
  P2VAR(volatile Fr_59_Renesas_DataTransferControlRegType, AUTOMATIC, REGSPACE) LpDataTransferCtrlReg;
  P2VAR(volatile Fr_59_Renesas_DataTransferStatusRegType, AUTOMATIC, REGSPACE) LpDataTransferStatusReg;
  P2VAR(volatile Fr_59_Renesas_OutputBufferRegType, AUTOMATIC, REGSPACE) LpOutputBuffReg;                               /* PRQA S 3678 # JV-01 */
  /* Declare local pointer to CC configuration */
  P2CONST(Fr_59_Renesas_CtrlTableType, TYPEDEF, FR_CONFIG_DATA) LpCtrlTable;
  #if (FR_59_RENESAS_ENABLE_OUTPUT_RX_HANDLER == STD_ON)
  P2CONST(Fr_59_Renesas_FrameHeaderType, AUTOMATIC, FR_APPL_CONST) LpFrameConfigPtr;
  P2CONST(Fr_59_Renesas_LowLevelConfSetType, AUTOMATIC, FR_CONST) LpLowLevelCfgPtr;
  P2VAR(volatile Fr_59_Renesas_OutputPointerTableType, AUTOMATIC, FR_APPL_DATA) LpOutputPointerTablePtr;
  #endif
  #if (FR_59_RENESAS_ENABLE_OUTPUT_RX_FIFO_HANDLER == STD_ON)
  P2VAR(volatile Fr_59_Renesas_OutputPointerTableType, AUTOMATIC, FR_APPL_DATA) LpFIFOPointerTablePtr;
  #endif
  /* Declare local pointer to Dem Event Id */
  P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF, FR_CONFIG_DATA)
  LpDemEventId;
  /* Declare the variable to store the return value */
  Std_ReturnType LucReturnValue;
  /* Declare the variable to store the message buffer number */
  #if (FR_59_RENESAS_ENABLE_OUTPUT_RX_HANDLER == STD_ON)
  uint8 LucMessageBuffer;
  /* Declare variable to store value of first FIFO */
  uint8 LucFirstFifoBuff;
  #endif
  volatile uint16 LusLoopCount;
  uint32 LulData;
  #if (FR_59_RENESAS_ENABLE_OUTPUT_RX_FIFO_HANDLER == STD_ON)
  uint8 LucFIFOMax;
  #endif
  uint16 LusFrameCount;
  #if (FR_59_RENESAS_ENABLE_OUTPUT_RX_HANDLER == STD_ON)
  uint8 LucOutputTableCount;
  #endif
  LucReturnValue = E_NOT_OK;                                                                                            /* PRQA S 2982 # JV-01 */
  /* Copy global pointer to local pointer */
  LpCtrlRegSet = Fr_59_Renesas_GpCtrlRegSet[Fr_CtrlIdx];                                                                
  LpDataTransferCtrlReg = LpCtrlRegSet->pDataTransferCtrlReg;                                                          
  LpDataTransferStatusReg = LpCtrlRegSet->pDataTransferStatusReg;
  LpOutputBuffReg = LpCtrlRegSet->pOutputBuffReg;
  #if (FR_59_RENESAS_ENABLE_OUTPUT_RX_HANDLER == STD_ON)
  LpMBCtrlReg = LpCtrlRegSet->pMBCtrlReg;
  LpLowLevelCfgPtr = Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pLowLevelConfig;
  LpFrameConfigPtr = Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pFrameConfig;
  #endif
  LpDemEventId = (P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF,
                                         FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pDemEventId);
  /* Check for output transfer disable*/
  LulData = LpDataTransferStatusReg->ulFLXAnFROTS;                                                                     
  if (FR_59_RENESAS_FLX0FROTS_FLX0_OTS_MASK != (LulData & FR_59_RENESAS_FLX0FROTS_FLX0_OTS_MASK))
  {
    LpCtrlTable = (P2CONST(Fr_59_Renesas_CtrlTableType, AUTOMATIC,
                                          FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pCtrlTable);
    /* Writing in to FlexRay message Data Available Register and mirror address */
    LpDataTransferStatusReg->ulFLXAnFRDA0 = FR_59_RENESAS_FLX0FRDA_FLAG_RESET;
    /* Writing in to FlexRay message Data Available Register and mirror address */
    LpDataTransferStatusReg->ulFLXAnFRDA1 = FR_59_RENESAS_FLX0FRDA_FLAG_RESET;
    /* Writing in to FlexRay message Data Available Register and mirror address */
    LpDataTransferStatusReg->ulFLXAnFRDA2 = FR_59_RENESAS_FLX0FRDA_FLAG_RESET;
    /* Writing in to FlexRay message Data Available Register and mirror address */
    LpDataTransferStatusReg->ulFLXAnFRDA3 = FR_59_RENESAS_FLX0FRDA_FLAG_RESET;
    /* Initialize the loop count to FR_59_RENESAS_ZERO */
    LusLoopCount = FR_59_RENESAS_ZERO;
    /* Wait until Transfer between OBF Shadow and Message RAM completed */
    while ((FR_59_RENESAS_FLX0FROBCR_FLX0_OBSYS_MASK ==  (LpOutputBuffReg->ulFLXAnFROBCR                            
            & FR_59_RENESAS_FLX0FROBCR_FLX0_OBSYS_MASK)) && (LusLoopCount < (uint16)(LpCtrlTable->usFlagClearMaxWait))) /* PRQA S 3415, 3416 # JV-01, JV-01 */
    {
      /* Increment the loop count */
      LusLoopCount++;                                                                                                   /* PRQA S 3383, 3387 # JV-01, JV-01 */
    }
    if (LusLoopCount == (uint16)(LpCtrlTable->usFlagClearMaxWait))                                                      /* PRQA S 3416 # JV-01 */
    {
      if (FR_59_RENESAS_DEM_NOT_CONFIGURED != LpDemEventId->usReadTimeoutFailure)                                       
      {
        FR_59_RENESAS_DEM_REPORT_ERROR(LpDemEventId->usReadTimeoutFailure, DEM_EVENT_STATUS_FAILED);
      } /* else No Action required */
      /* Set Return Value as E_NOT_OK */
      LucReturnValue = E_NOT_OK;
    }
    else
    {
      #if (FR_59_RENESAS_ENABLE_OUTPUT_RX_HANDLER == STD_ON)
      LucOutputTableCount = FR_59_RENESAS_ZERO;
      /* To update the address and data structure of output pointer table */
      for (LusFrameCount = FR_59_RENESAS_ZERO; LusFrameCount < LpCtrlTable->usMaxFrames; LusFrameCount++)
      {
        if ((LpFrameConfigPtr->ucFrameConfig == FR_59_RENESAS_ZERO) &&                                                  
                                                             (LpFrameConfigPtr->blIsFIFOConfig == FR_59_RENESAS_FALSE))
        {
          /* Read the first msg buffer of FIFO from FRMRC register */
          LulData = LpMBCtrlReg->ulFLXAnFRMRC & FR_59_RENESAS_FLX0MRC_FFB_MASK;                                        
          LucFirstFifoBuff = (uint8)(LulData >> FR_59_RENESAS_EIGHT);
          /* Get the message buffer of the frame */
          LucMessageBuffer = Fr_OutputTableContentPtr[LucOutputTableCount].ucMsgBuffer;                               
          if (LucMessageBuffer < LucFirstFifoBuff)
          {
            /* Get the address of output pointer table */
            LpOutputPointerTablePtr = (volatile Fr_59_Renesas_OutputPointerTableType *)                                 /* PRQA S 0303 # JV-01 */
                 (LpLowLevelCfgPtr->ulFrOptPtrTblBaseAddReg + ((uint32)LucMessageBuffer * (uint32)FR_59_RENESAS_FOUR)); /* PRQA S 3383, 3384 # JV-01, JV-01 */
            /* Write the output data structure to output pointer table*/
            LpOutputPointerTablePtr->Fr_59_Renesas_pOutputDataPtr =                                                     
                                            Fr_OutputTableContentPtr[LucOutputTableCount].Fr_59_Renesas_pOutputDataPtr;
            LucOutputTableCount++;                                                                                      /* PRQA S 3383 # JV-01 */
          } /* else No Action required */
        } /* else No Action required */
        /* Next output data structure */
        LpFrameConfigPtr++;                                                                                      
      }
      #endif
      #if (FR_59_RENESAS_ENABLE_OUTPUT_RX_FIFO_HANDLER == STD_ON)
      LpFIFOPointerTablePtr = (volatile Fr_59_Renesas_OutputPointerTableType *)  (LpDataTransferCtrlReg->ulFLXAnFRFBA); /* PRQA S 0303 # JV-01 */
      /* Read the value of Output Transfer Configuration register */
      LulData = LpDataTransferCtrlReg->ulFLXAnFROTC;
      LulData = LulData & FR_59_RENESAS_FLX0FROTC_FIFO_MAX;
      /* Get the FIFO table max value */
      LucFIFOMax = (uint8)(LulData >> FR_59_RENESAS_SIXTEEN);
      for (LusFrameCount = FR_59_RENESAS_ZERO; LusFrameCount < LucFIFOMax; LusFrameCount++)
      {
        /* Write the output data structure to output pointer table*/
        LpFIFOPointerTablePtr->Fr_59_Renesas_pOutputDataPtr =                                                          
                                                  (Fr_FIFOTableContentPtr[LusFrameCount].Fr_59_Renesas_pOutputDataPtr);
        /* Next output data structure */
        LpFIFOPointerTablePtr++;                                                                                      
      }
      #endif
      /* Enable Output Transfer */
      LulData = LpDataTransferCtrlReg->ulFLXAnFROTC;
      LulData = LulData | FR_59_RENESAS_FLX0FROTC_OTE_SET;
      /* Writing in to FlexRay Output Transfer Configuration Register and
       mirror address */
      LpDataTransferCtrlReg->ulFLXAnFROTC = LulData;
      LucReturnValue = E_OK;
    }
  }
  else
  {
    /* Raise DEM Error FAILED */
    if (FR_59_RENESAS_DEM_NOT_CONFIGURED != LpDemEventId->usHardwareTestFailure)
    {
      FR_59_RENESAS_DEM_REPORT_ERROR(LpDemEventId->usHardwareTestFailure, DEM_EVENT_STATUS_FAILED);
    } /* else No Action required */
    /* Set Return Value as E_NOT_OK */
    LucReturnValue = E_NOT_OK;
  }
  return (LucReturnValue);
} /* End of Fr_59_Renesas_DataAvailable */
#define FR_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
#endif
/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_UpdateCCConfig
**
** Service ID            : Not Applicable
**
** Description           : This function gets values of CC configuration
**                         registers to output pointer
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx, Fr_ConfigParamIdx,
**                         Fr_ConfigParamValuePtr
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : None
**
** Global Variables Used : Fr_59_Renesas_GpControllerConfigPtr,
**                         Fr_59_Renesas_GpCtrlRegSet,
**                         Fr_59_Renesas_GpPeriodTimeConfigPtr
**
** Functions Invoked     : None.
**
** Registers Used        : FLXAnFRGTUCi(i = 1 to 10), FLXAnFRMHDC, FLXAnFRNEMC,
**                         FLXAnFRPRTC1, FLXAnFRPRTC2, FLXAnFRSUCCi(i = 1 to 3)
**
** Reference ID          : FR_DUD_ACT_070
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PRIVATE_CODE)
                  Fr_59_Renesas_UpdateCCConfig(const uint8 Fr_CtrlIdx, const uint8 Fr_ConfigParamIdx,               
                                                                                  uint32 *const Fr_ConfigParamValuePtr)
{
  /* Declare pointer to register */
  P2CONST(volatile Fr_59_Renesas_RegisterSetType, AUTOMATIC, FR_CONFIG_DATA) LpCtrlRegSet;
  P2VAR(volatile Fr_59_Renesas_CCControlRegType, AUTOMATIC, REGSPACE) LpCCCtrlReg;
  /* Declare local pointer to CC configuration */
  P2CONST(Fr_59_Renesas_CtrlTableType, TYPEDEF, FR_CONFIG_DATA) LpCtrlTable;
  uint32 LulOffset;
  uint8 LucBitsTobeMovedRight;
  uint8 LucCount;
  Std_ReturnType LucReturnValue;

  /* Declare array contains CC Config */
  static VAR(Fr_Renesas_UpdateCCConfig, FR_CONFIG_DATA) Fr_UpdateCCConfig[FR_59_RENESAS_SIXTYTHREE];

  /* Copy global pointer to local pointer */
  LpCtrlRegSet = Fr_59_Renesas_GpCtrlRegSet[Fr_CtrlIdx];                                                                
  LpCCCtrlReg = LpCtrlRegSet->pCCCtrlReg;                                                                              
  /* Initialize the return value */
  LucReturnValue = E_OK;
  /* Initialize the bit to move */
  LucBitsTobeMovedRight = FR_59_RENESAS_ZERO;                                                                           /* PRQA S 2982 # JV-01 */
  LulOffset = (uint32)FR_59_RENESAS_ZERO;
  LpCtrlTable = (P2CONST(Fr_59_Renesas_CtrlTableType, AUTOMATIC,
                                          FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pCtrlTable);
  /* pMicroPerCycle FLX0GTUC01(19:0) */
  Fr_UpdateCCConfig[FR_59_RENESAS_ZERO].Fr_ConfigParamIdx = FR_CIDX_PMICROPERCYCLE;
  Fr_UpdateCCConfig[FR_59_RENESAS_ZERO].pOffset = &(LpCCCtrlReg->ulFLXAnFRGTUC1);                                      
  Fr_UpdateCCConfig[FR_59_RENESAS_ZERO].LulMask = FR_59_RENESAS_CIDX_PMICROPERCYCLE_MASK;
  Fr_UpdateCCConfig[FR_59_RENESAS_ZERO].LucBitsTobeMovedRight = FR_59_RENESAS_ZERO;
  Fr_UpdateCCConfig[FR_59_RENESAS_ZERO].Fr_ConfigParamValuePtr = FR_59_RENESAS_EMPTY;
  
  /* FrIfGMacroPerCycle FLX0GTUC02 FLX0MPC[13:0] */
  Fr_UpdateCCConfig[FR_59_RENESAS_ONE].Fr_ConfigParamIdx = FR_CIDX_GMACROPERCYCLE;
  Fr_UpdateCCConfig[FR_59_RENESAS_ONE].pOffset = &(LpCCCtrlReg->ulFLXAnFRGTUC2);
  Fr_UpdateCCConfig[FR_59_RENESAS_ONE].LulMask = FR_59_RENESAS_CIDX_GMACROPERCYCLE_MASK;
  Fr_UpdateCCConfig[FR_59_RENESAS_ONE].LucBitsTobeMovedRight = FR_59_RENESAS_ZERO;
  Fr_UpdateCCConfig[FR_59_RENESAS_ONE].Fr_ConfigParamValuePtr = FR_59_RENESAS_EMPTY;
  
  /* FrPMicroInitialOffsetA FLX0GTUC03 FLX0UIOA[7:0] */
  Fr_UpdateCCConfig[FR_59_RENESAS_TWO].Fr_ConfigParamIdx = FR_CIDX_PMICROINITIALOFFSETA;
  Fr_UpdateCCConfig[FR_59_RENESAS_TWO].pOffset = &(LpCCCtrlReg->ulFLXAnFRGTUC3);
  Fr_UpdateCCConfig[FR_59_RENESAS_TWO].LulMask = FR_59_RENESAS_CIDX_PMICROINITIALOFFSETA_MASK;
  Fr_UpdateCCConfig[FR_59_RENESAS_TWO].LucBitsTobeMovedRight = FR_59_RENESAS_ZERO;
  Fr_UpdateCCConfig[FR_59_RENESAS_TWO].Fr_ConfigParamValuePtr = FR_59_RENESAS_EMPTY;
  
  /* FrPDelayCompensationA FLX0GTUC05 FLX0DCA[7:0] */
  Fr_UpdateCCConfig[FR_59_RENESAS_THREE].Fr_ConfigParamIdx = FR_CIDX_PDELAYCOMPENSATIONA;
  Fr_UpdateCCConfig[FR_59_RENESAS_THREE].pOffset = &(LpCCCtrlReg->ulFLXAnFRGTUC5);
  Fr_UpdateCCConfig[FR_59_RENESAS_THREE].LulMask = FR_59_RENESAS_CIDX_PDELAYCOMPENSATIONA_MASK;
  Fr_UpdateCCConfig[FR_59_RENESAS_THREE].LucBitsTobeMovedRight = FR_59_RENESAS_ZERO;
  Fr_UpdateCCConfig[FR_59_RENESAS_THREE].Fr_ConfigParamValuePtr = FR_59_RENESAS_EMPTY;
  
  /* FrIfGdStaticSlot FLX0GTUC07 FLX0SSL[9:0] */
  Fr_UpdateCCConfig[FR_59_RENESAS_FOUR].Fr_ConfigParamIdx = FR_CIDX_GDSTATICSLOT;
  Fr_UpdateCCConfig[FR_59_RENESAS_FOUR].pOffset = &(LpCCCtrlReg->ulFLXAnFRGTUC7);
  Fr_UpdateCCConfig[FR_59_RENESAS_FOUR].LulMask = FR_59_RENESAS_CIDX_GDSTATICSLOT_MASK;
  Fr_UpdateCCConfig[FR_59_RENESAS_FOUR].LucBitsTobeMovedRight = FR_59_RENESAS_ZERO;
  Fr_UpdateCCConfig[FR_59_RENESAS_FOUR].Fr_ConfigParamValuePtr = FR_59_RENESAS_EMPTY;
  
  /* FrIfGdMinislot FLX0GTUC08 FLX0MSL[5:0] */
  Fr_UpdateCCConfig[FR_59_RENESAS_FIVE].Fr_ConfigParamIdx = FR_CIDX_GDMINISLOT;
  Fr_UpdateCCConfig[FR_59_RENESAS_FIVE].pOffset = &(LpCCCtrlReg->ulFLXAnFRGTUC8);
  Fr_UpdateCCConfig[FR_59_RENESAS_FIVE].LulMask = FR_59_RENESAS_CIDX_GDMINISLOT_MASK;
  Fr_UpdateCCConfig[FR_59_RENESAS_FIVE].LucBitsTobeMovedRight = FR_59_RENESAS_ZERO;
  Fr_UpdateCCConfig[FR_59_RENESAS_FIVE].Fr_ConfigParamValuePtr = FR_59_RENESAS_EMPTY;
  
  /* FrIfGdActionPointOffset FLX0GTUC09 FLX0APO[5:0] */
  Fr_UpdateCCConfig[FR_59_RENESAS_SIX].Fr_ConfigParamIdx = FR_CIDX_GDACTIONPOINTOFFSET;
  Fr_UpdateCCConfig[FR_59_RENESAS_SIX].pOffset = &(LpCCCtrlReg->ulFLXAnFRGTUC9);
  Fr_UpdateCCConfig[FR_59_RENESAS_SIX].LulMask = FR_59_RENESAS_CIDX_GDACTIONPOINTOFFSET_MASK;
  Fr_UpdateCCConfig[FR_59_RENESAS_SIX].LucBitsTobeMovedRight = FR_59_RENESAS_ZERO;
  Fr_UpdateCCConfig[FR_59_RENESAS_SIX].Fr_ConfigParamValuePtr = FR_59_RENESAS_EMPTY;
  
  /* FrIfGdSymbolWindowActionPointOffset FLX0GTUC09 FLX0APO[5:0] */
  Fr_UpdateCCConfig[FR_59_RENESAS_SEVEN].Fr_ConfigParamIdx = FR_CIDX_GDSYMBOLWINDOWACTIONPOINTOFFSET;
  Fr_UpdateCCConfig[FR_59_RENESAS_SEVEN].pOffset = &(LpCCCtrlReg->ulFLXAnFRGTUC9);
  Fr_UpdateCCConfig[FR_59_RENESAS_SEVEN].LulMask = FR_59_RENESAS_CIDX_GDACTIONPOINTOFFSET_MASK;
  Fr_UpdateCCConfig[FR_59_RENESAS_SEVEN].LucBitsTobeMovedRight = FR_59_RENESAS_ZERO;
  Fr_UpdateCCConfig[FR_59_RENESAS_SEVEN].Fr_ConfigParamValuePtr = FR_59_RENESAS_EMPTY;
  
  /* FrPOffsetCorrectionOut FLX0GTUC10 FLX0MOC[13:0] */
  Fr_UpdateCCConfig[FR_59_RENESAS_EIGHT].Fr_ConfigParamIdx = FR_CIDX_POFFSETCORRECTIONOUT;
  Fr_UpdateCCConfig[FR_59_RENESAS_EIGHT].pOffset = &(LpCCCtrlReg->ulFLXAnFRGTUC10);
  Fr_UpdateCCConfig[FR_59_RENESAS_EIGHT].LulMask = FR_59_RENESAS_CIDX_POFFSETCORRECTIONOUT_MASK;
  Fr_UpdateCCConfig[FR_59_RENESAS_EIGHT].LucBitsTobeMovedRight = FR_59_RENESAS_ZERO;
  Fr_UpdateCCConfig[FR_59_RENESAS_EIGHT].Fr_ConfigParamValuePtr = FR_59_RENESAS_EMPTY;
  
  /* FrIfGPayloadLengthStatic FLX0MHDC FLX0SFDL[6:0] */
  Fr_UpdateCCConfig[FR_59_RENESAS_NINE].Fr_ConfigParamIdx = FR_CIDX_GPAYLOADLENGTHSTATIC;
  Fr_UpdateCCConfig[FR_59_RENESAS_NINE].pOffset = &(LpCCCtrlReg->ulFLXAnFRMHDC);
  Fr_UpdateCCConfig[FR_59_RENESAS_NINE].LulMask = FR_59_RENESAS_CIDX_GPAYLOADLENGTHSTATIC_MASK;
  Fr_UpdateCCConfig[FR_59_RENESAS_NINE].LucBitsTobeMovedRight = FR_59_RENESAS_ZERO;
  Fr_UpdateCCConfig[FR_59_RENESAS_NINE].Fr_ConfigParamValuePtr = FR_59_RENESAS_EMPTY;
  
  /* FrIfGNetworkManagementVectorLength FLX0NEMC FLX0NML[3:0] */
  Fr_UpdateCCConfig[FR_59_RENESAS_TEN].Fr_ConfigParamIdx = FR_CIDX_GNETWORKMANAGEMENTVECTORLENGTH;
  Fr_UpdateCCConfig[FR_59_RENESAS_TEN].pOffset = &(LpCCCtrlReg->ulFLXAnFRNEMC);
  Fr_UpdateCCConfig[FR_59_RENESAS_TEN].LulMask = FR_59_RENESAS_CIDX_GNETWORKMANAGEMENTVECTORLENGTH_MASK;
  Fr_UpdateCCConfig[FR_59_RENESAS_TEN].LucBitsTobeMovedRight = FR_59_RENESAS_ZERO;
  Fr_UpdateCCConfig[FR_59_RENESAS_TEN].Fr_ConfigParamValuePtr = FR_59_RENESAS_EMPTY;
  
  /* FrIfGdTSSTransmitter FLX0PRTC1 FLX0TSST[3:0] */
  Fr_UpdateCCConfig[FR_59_RENESAS_ELEVEN].Fr_ConfigParamIdx = FR_CIDX_GDTSSTRANSMITTER;
  Fr_UpdateCCConfig[FR_59_RENESAS_ELEVEN].pOffset = &(LpCCCtrlReg->ulFLXAnFRPRTC1);
  Fr_UpdateCCConfig[FR_59_RENESAS_ELEVEN].LulMask = FR_59_RENESAS_CIDX_GDTSSTRANSMITTER_MASK;
  Fr_UpdateCCConfig[FR_59_RENESAS_ELEVEN].LucBitsTobeMovedRight = FR_59_RENESAS_ZERO;
  Fr_UpdateCCConfig[FR_59_RENESAS_ELEVEN].Fr_ConfigParamValuePtr = FR_59_RENESAS_EMPTY;
  
  /* FrIfGdWakeupRxIdle FLX0PRTC2 FLX0RXL[13:8] */
  Fr_UpdateCCConfig[FR_59_RENESAS_TWELVE].Fr_ConfigParamIdx = FR_CIDX_GDWAKEUPRXIDLE;
  Fr_UpdateCCConfig[FR_59_RENESAS_TWELVE].pOffset = &(LpCCCtrlReg->ulFLXAnFRPRTC2);
  Fr_UpdateCCConfig[FR_59_RENESAS_TWELVE].LulMask = FR_59_RENESAS_CIDX_GDWAKEUPRXIDLE_MASK;
  Fr_UpdateCCConfig[FR_59_RENESAS_TWELVE].LucBitsTobeMovedRight = FR_59_RENESAS_ZERO;
  Fr_UpdateCCConfig[FR_59_RENESAS_TWELVE].Fr_ConfigParamValuePtr = FR_59_RENESAS_EMPTY;
  
  /* FrPdListenTimeout FLX0SUCC2 FLX0LT[20:00] */
  Fr_UpdateCCConfig[FR_59_RENESAS_THIRTEEN].Fr_ConfigParamIdx = FR_CIDX_PDLISTENTIMEOUT;
  Fr_UpdateCCConfig[FR_59_RENESAS_THIRTEEN].pOffset = &(LpCCCtrlReg->ulFLXAnFRSUCC2);
  Fr_UpdateCCConfig[FR_59_RENESAS_THIRTEEN].LulMask = FR_59_RENESAS_CIDX_PDLISTENTIMEOUT_MASK;
  Fr_UpdateCCConfig[FR_59_RENESAS_THIRTEEN].LucBitsTobeMovedRight = FR_59_RENESAS_ZERO;
  Fr_UpdateCCConfig[FR_59_RENESAS_THIRTEEN].Fr_ConfigParamValuePtr = FR_59_RENESAS_EMPTY;
  
  /* FrIfGMaxWithoutClockCorrectPassive FLX0SUCC3 FLX0WCF[3:0] */
  Fr_UpdateCCConfig[FR_59_RENESAS_FOURTEEN].Fr_ConfigParamIdx = FR_CIDX_GMAXWITHOUTCLOCKCORRECTPASSIVE;
  Fr_UpdateCCConfig[FR_59_RENESAS_FOURTEEN].pOffset = &(LpCCCtrlReg->ulFLXAnFRSUCC3);
  Fr_UpdateCCConfig[FR_59_RENESAS_FOURTEEN].LulMask = FR_59_RENESAS_CIDX_GMAXWITHOUTCLOCKCORRECTPASSIVE_MASK;
  Fr_UpdateCCConfig[FR_59_RENESAS_FOURTEEN].LucBitsTobeMovedRight = FR_59_RENESAS_ZERO;
  Fr_UpdateCCConfig[FR_59_RENESAS_FOURTEEN].Fr_ConfigParamValuePtr = FR_59_RENESAS_EMPTY;
  
  /* FrIfGSyncFrameIDCountMax FLX0GTUC02 FLX0SNM[19:16] */
  Fr_UpdateCCConfig[FR_59_RENESAS_FIFTEEN].Fr_ConfigParamIdx = FR_CIDX_GSYNCFRAMEIDCOUNTMAX;
  Fr_UpdateCCConfig[FR_59_RENESAS_FIFTEEN].pOffset = &(LpCCCtrlReg->ulFLXAnFRGTUC2);
  Fr_UpdateCCConfig[FR_59_RENESAS_FIFTEEN].LulMask = FR_59_RENESAS_CIDX_GSYNCFRAMEIDCOUNTMAX_MASK;
  Fr_UpdateCCConfig[FR_59_RENESAS_FIFTEEN].LucBitsTobeMovedRight = FR_59_RENESAS_SIXTEEN;
  Fr_UpdateCCConfig[FR_59_RENESAS_FIFTEEN].Fr_ConfigParamValuePtr = FR_59_RENESAS_EMPTY;
  
  /* FrPMacroInitialOffsetA FLX0GTUC03 FLX0MIOA[22:16] */
  Fr_UpdateCCConfig[FR_59_RENESAS_SIXTEEN].Fr_ConfigParamIdx = FR_CIDX_PMACROINITIALOFFSETA;
  Fr_UpdateCCConfig[FR_59_RENESAS_SIXTEEN].pOffset = &(LpCCCtrlReg->ulFLXAnFRGTUC3);
  Fr_UpdateCCConfig[FR_59_RENESAS_SIXTEEN].LulMask = FR_59_RENESAS_CIDX_PMACROINITIALOFFSETA_MASK;
  Fr_UpdateCCConfig[FR_59_RENESAS_SIXTEEN].LucBitsTobeMovedRight = FR_59_RENESAS_SIXTEEN;
  Fr_UpdateCCConfig[FR_59_RENESAS_SIXTEEN].Fr_ConfigParamValuePtr = FR_59_RENESAS_EMPTY;
  
  /* FrPMacroInitialOffsetB FLX0GTUC03 FLX0MIOB[30:24] */
  Fr_UpdateCCConfig[FR_59_RENESAS_SEVENTEEN].Fr_ConfigParamIdx = FR_CIDX_PMACROINITIALOFFSETB;
  Fr_UpdateCCConfig[FR_59_RENESAS_SEVENTEEN].pOffset = &(LpCCCtrlReg->ulFLXAnFRGTUC3);
  Fr_UpdateCCConfig[FR_59_RENESAS_SEVENTEEN].LulMask = FR_59_RENESAS_CIDX_PMACROINITIALOFFSETB_MASK;
  Fr_UpdateCCConfig[FR_59_RENESAS_SEVENTEEN].LucBitsTobeMovedRight = FR_59_RENESAS_TWENTYFOUR;
  Fr_UpdateCCConfig[FR_59_RENESAS_SEVENTEEN].Fr_ConfigParamValuePtr = FR_59_RENESAS_EMPTY;
  
  /* FrPMicroInitialOffsetB FLX0GTUC03 FLX0UIOB[15:8] */
  Fr_UpdateCCConfig[FR_59_RENESAS_EIGHTTEEN].Fr_ConfigParamIdx = FR_CIDX_PMICROINITIALOFFSETB;
  Fr_UpdateCCConfig[FR_59_RENESAS_EIGHTTEEN].pOffset = &(LpCCCtrlReg->ulFLXAnFRGTUC3);
  Fr_UpdateCCConfig[FR_59_RENESAS_EIGHTTEEN].LulMask = FR_59_RENESAS_CIDX_PMICROINITIALOFFSETB_MASK;
  Fr_UpdateCCConfig[FR_59_RENESAS_EIGHTTEEN].LucBitsTobeMovedRight = FR_59_RENESAS_EIGHT;
  Fr_UpdateCCConfig[FR_59_RENESAS_EIGHTTEEN].Fr_ConfigParamValuePtr = FR_59_RENESAS_EMPTY;
  
  /* FrPOffsetCorrectionStart FLX0GTUC04 FLX0OCS[29:16] */
  Fr_UpdateCCConfig[FR_59_RENESAS_NINETEEN].Fr_ConfigParamIdx = FR_CIDX_POFFSETCORRECTIONSTART;
  Fr_UpdateCCConfig[FR_59_RENESAS_NINETEEN].pOffset = &(LpCCCtrlReg->ulFLXAnFRGTUC4);
  Fr_UpdateCCConfig[FR_59_RENESAS_NINETEEN].LulMask = FR_59_RENESAS_CIDX_POFFSETCORRECTIONSTART_MASK;
  Fr_UpdateCCConfig[FR_59_RENESAS_NINETEEN].LucBitsTobeMovedRight = FR_59_RENESAS_SIXTEEN;
  Fr_UpdateCCConfig[FR_59_RENESAS_NINETEEN].Fr_ConfigParamValuePtr = FR_59_RENESAS_EMPTY;
  
  /* FrPClusterDriftDamping FLX0GTUC05 FLX0CDD[20:16] */
  Fr_UpdateCCConfig[FR_59_RENESAS_TWENTY].Fr_ConfigParamIdx = FR_CIDX_PCLUSTERDRIFTDAMPING;
  Fr_UpdateCCConfig[FR_59_RENESAS_TWENTY].pOffset = &(LpCCCtrlReg->ulFLXAnFRGTUC5);
  Fr_UpdateCCConfig[FR_59_RENESAS_TWENTY].LulMask = FR_59_RENESAS_CIDX_PCLUSTERDRIFTDAMPING_MASK;
  Fr_UpdateCCConfig[FR_59_RENESAS_TWENTY].LucBitsTobeMovedRight = FR_59_RENESAS_SIXTEEN;
  Fr_UpdateCCConfig[FR_59_RENESAS_TWENTY].Fr_ConfigParamValuePtr = FR_59_RENESAS_EMPTY;
  
  /* FrPDecodingCorrection FLX0GTUC05 FLX0DEC[31:24] */
  Fr_UpdateCCConfig[FR_59_RENESAS_TWENTYONE].Fr_ConfigParamIdx = FR_CIDX_PDECODINGCORRECTION;
  Fr_UpdateCCConfig[FR_59_RENESAS_TWENTYONE].pOffset = &(LpCCCtrlReg->ulFLXAnFRGTUC5);
  Fr_UpdateCCConfig[FR_59_RENESAS_TWENTYONE].LulMask = FR_59_RENESAS_CIDX_PDECODINGCORRECTION_MASK;
  Fr_UpdateCCConfig[FR_59_RENESAS_TWENTYONE].LucBitsTobeMovedRight = FR_59_RENESAS_TWENTYFOUR;
  Fr_UpdateCCConfig[FR_59_RENESAS_TWENTYONE].Fr_ConfigParamValuePtr = FR_59_RENESAS_EMPTY;
  
  /* FrPDelayCompensationB FLX0GTUC05 FLX0DCB[15:8] */
  Fr_UpdateCCConfig[FR_59_RENESAS_TWENTYTWO].Fr_ConfigParamIdx = FR_CIDX_PDELAYCOMPENSATIONB;
  Fr_UpdateCCConfig[FR_59_RENESAS_TWENTYTWO].pOffset = &(LpCCCtrlReg->ulFLXAnFRGTUC5);
  Fr_UpdateCCConfig[FR_59_RENESAS_TWENTYTWO].LulMask = FR_59_RENESAS_CIDX_PDELAYCOMPENSATIONB_MASK;
  Fr_UpdateCCConfig[FR_59_RENESAS_TWENTYTWO].LucBitsTobeMovedRight = FR_59_RENESAS_EIGHT;
  Fr_UpdateCCConfig[FR_59_RENESAS_TWENTYTWO].Fr_ConfigParamValuePtr = FR_59_RENESAS_EMPTY;
  
  /* FrPdAcceptedStartupRange FLX0GTUC06 FLX0ASR[26:16] */
  Fr_UpdateCCConfig[FR_59_RENESAS_TWENTYTHREE].Fr_ConfigParamIdx = FR_CIDX_PDACCEPTEDSTARTUPRANGE;
  Fr_UpdateCCConfig[FR_59_RENESAS_TWENTYTHREE].pOffset = &(LpCCCtrlReg->ulFLXAnFRGTUC6);
  Fr_UpdateCCConfig[FR_59_RENESAS_TWENTYTHREE].LulMask = FR_59_RENESAS_CIDX_PDACCEPTEDSTARTUPRANGE_MASK;
  Fr_UpdateCCConfig[FR_59_RENESAS_TWENTYTHREE].LucBitsTobeMovedRight = FR_59_RENESAS_ZERO;
  Fr_UpdateCCConfig[FR_59_RENESAS_TWENTYTHREE].Fr_ConfigParamValuePtr = FR_59_RENESAS_EMPTY;
  
  /* FrIfGNumberOfStaticSlots FLX0GTUC07 FLX0NSS[25:16] */
  Fr_UpdateCCConfig[FR_59_RENESAS_TWENTYFOUR].Fr_ConfigParamIdx = FR_CIDX_GNUMBEROFSTATICSLOTS;
  Fr_UpdateCCConfig[FR_59_RENESAS_TWENTYFOUR].pOffset = &(LpCCCtrlReg->ulFLXAnFRGTUC7);
  Fr_UpdateCCConfig[FR_59_RENESAS_TWENTYFOUR].LulMask = FR_59_RENESAS_CIDX_GNUMBEROFSTATICSLOTS_MASK;
  Fr_UpdateCCConfig[FR_59_RENESAS_TWENTYFOUR].LucBitsTobeMovedRight = FR_59_RENESAS_SIXTEEN;
  Fr_UpdateCCConfig[FR_59_RENESAS_TWENTYFOUR].Fr_ConfigParamValuePtr = FR_59_RENESAS_EMPTY;
  
  /* FrIfGNumberOfMinislots FLX0GTUC08 FLX0NMS[28:16] */
  Fr_UpdateCCConfig[FR_59_RENESAS_TWENTYFIVE].Fr_ConfigParamIdx = FR_CIDX_GNUMBEROFMINISLOTS;
  Fr_UpdateCCConfig[FR_59_RENESAS_TWENTYFIVE].pOffset = &(LpCCCtrlReg->ulFLXAnFRGTUC8);
  Fr_UpdateCCConfig[FR_59_RENESAS_TWENTYFIVE].LulMask = FR_59_RENESAS_CIDX_GNUMBEROFMINISLOTS_MASK;
  Fr_UpdateCCConfig[FR_59_RENESAS_TWENTYFIVE].LucBitsTobeMovedRight = FR_59_RENESAS_SIXTEEN;
  Fr_UpdateCCConfig[FR_59_RENESAS_TWENTYFIVE].Fr_ConfigParamValuePtr = FR_59_RENESAS_EMPTY;
  
  /* FrIfGdDynamicSlotIdlePhase FLX0GTUC09 FLX0DSI[17:16] */
  Fr_UpdateCCConfig[FR_59_RENESAS_TWENTYSIX].Fr_ConfigParamIdx = FR_CIDX_GDDYNAMICSLOTIDLEPHASE;
  Fr_UpdateCCConfig[FR_59_RENESAS_TWENTYSIX].pOffset = &(LpCCCtrlReg->ulFLXAnFRGTUC9);
  Fr_UpdateCCConfig[FR_59_RENESAS_TWENTYSIX].LulMask = FR_59_RENESAS_CIDX_GDDYNAMICSLOTIDLEPHASE_MASK;
  Fr_UpdateCCConfig[FR_59_RENESAS_TWENTYSIX].LucBitsTobeMovedRight = FR_59_RENESAS_SIXTEEN;
  Fr_UpdateCCConfig[FR_59_RENESAS_TWENTYSIX].Fr_ConfigParamValuePtr = FR_59_RENESAS_EMPTY;
  
  /* FrIfGdMiniSlotActionPointOffset FLX0GTUC09 FLX0MAPO[12:8] */
  Fr_UpdateCCConfig[FR_59_RENESAS_TWENTYSEVEN].Fr_ConfigParamIdx = FR_CIDX_GDMINISLOTACTIONPOINTOFFSET;
  Fr_UpdateCCConfig[FR_59_RENESAS_TWENTYSEVEN].pOffset = &(LpCCCtrlReg->ulFLXAnFRGTUC9);
  Fr_UpdateCCConfig[FR_59_RENESAS_TWENTYSEVEN].LulMask = FR_59_RENESAS_CIDX_GDMINISLOTACTIONPOINTOFFSET_MASK;
  Fr_UpdateCCConfig[FR_59_RENESAS_TWENTYSEVEN].LucBitsTobeMovedRight = FR_59_RENESAS_EIGHT;
  Fr_UpdateCCConfig[FR_59_RENESAS_TWENTYSEVEN].Fr_ConfigParamValuePtr = FR_59_RENESAS_EMPTY;
  
  /* FrPRateCorrectionOut FLX0GTUC10 FLX0MRC[26:16] */
  Fr_UpdateCCConfig[FR_59_RENESAS_TWENTYEIGHT].Fr_ConfigParamIdx = FR_CIDX_PRATECORRECTIONOUT;
  Fr_UpdateCCConfig[FR_59_RENESAS_TWENTYEIGHT].pOffset = &(LpCCCtrlReg->ulFLXAnFRGTUC10);
  Fr_UpdateCCConfig[FR_59_RENESAS_TWENTYEIGHT].LulMask = FR_59_RENESAS_CIDX_PRATECORRECTIONOUT_MASK;
  Fr_UpdateCCConfig[FR_59_RENESAS_TWENTYEIGHT].LucBitsTobeMovedRight = FR_59_RENESAS_SIXTEEN;
  Fr_UpdateCCConfig[FR_59_RENESAS_TWENTYEIGHT].Fr_ConfigParamValuePtr = FR_59_RENESAS_EMPTY;
  
  /* FrPLatestTx FLX0MHDC FLX0SLT[28:16] */
  Fr_UpdateCCConfig[FR_59_RENESAS_TWENTYNINE].Fr_ConfigParamIdx = FR_CIDX_PLATESTTX;
  Fr_UpdateCCConfig[FR_59_RENESAS_TWENTYNINE].pOffset = &(LpCCCtrlReg->ulFLXAnFRMHDC);
  Fr_UpdateCCConfig[FR_59_RENESAS_TWENTYNINE].LulMask = FR_59_RENESAS_CIDX_PLATESTTX_MASK;
  Fr_UpdateCCConfig[FR_59_RENESAS_TWENTYNINE].LucBitsTobeMovedRight = FR_59_RENESAS_SIXTEEN;
  Fr_UpdateCCConfig[FR_59_RENESAS_TWENTYNINE].Fr_ConfigParamValuePtr = FR_59_RENESAS_EMPTY;
  
  /* FrPdMicrotick FLX0PRTC1 FLX0BRP[15:14] */
  Fr_UpdateCCConfig[FR_59_RENESAS_THIRTY].Fr_ConfigParamIdx = FR_CIDX_PDMICROTICK;
  Fr_UpdateCCConfig[FR_59_RENESAS_THIRTY].pOffset = &(LpCCCtrlReg->ulFLXAnFRPRTC1);
  Fr_UpdateCCConfig[FR_59_RENESAS_THIRTY].LulMask = FR_59_RENESAS_CIDX_PDMICROTICK_MASK;
  Fr_UpdateCCConfig[FR_59_RENESAS_THIRTY].LucBitsTobeMovedRight = FR_59_RENESAS_FOURTEEN;
  Fr_UpdateCCConfig[FR_59_RENESAS_THIRTY].Fr_ConfigParamValuePtr = FR_59_RENESAS_EMPTY;
  
  /* FrPSamplesPerMicrotick FLX0PRTC1 FLX0BRP[15:14] */
  Fr_UpdateCCConfig[FR_59_RENESAS_THIRTYONE].Fr_ConfigParamIdx = FR_CIDX_PSAMPLESPERMICROTICK;
  Fr_UpdateCCConfig[FR_59_RENESAS_THIRTYONE].pOffset = &(LpCCCtrlReg->ulFLXAnFRPRTC1);
  Fr_UpdateCCConfig[FR_59_RENESAS_THIRTYONE].LulMask = FR_59_RENESAS_CIDX_PSAMPLESPERMICROTICK_MASK;
  Fr_UpdateCCConfig[FR_59_RENESAS_THIRTYONE].LucBitsTobeMovedRight = FR_59_RENESAS_FOURTEEN;
  Fr_UpdateCCConfig[FR_59_RENESAS_THIRTYONE].Fr_ConfigParamValuePtr = FR_59_RENESAS_EMPTY;
  
  /* FrIfGdCasRxLowMax FLX0PRTC1 FLX0CASM[10:4] */
  Fr_UpdateCCConfig[FR_59_RENESAS_THIRTYTWO].Fr_ConfigParamIdx = FR_CIDX_GDCASRXLOWMAX;
  Fr_UpdateCCConfig[FR_59_RENESAS_THIRTYTWO].pOffset = &(LpCCCtrlReg->ulFLXAnFRPRTC1);
  Fr_UpdateCCConfig[FR_59_RENESAS_THIRTYTWO].LulMask = FR_59_RENESAS_CIDX_GDCASRXLOWMAX_MASK;
  Fr_UpdateCCConfig[FR_59_RENESAS_THIRTYTWO].LucBitsTobeMovedRight = FR_59_RENESAS_FOUR;
  Fr_UpdateCCConfig[FR_59_RENESAS_THIRTYTWO].Fr_ConfigParamValuePtr = FR_59_RENESAS_EMPTY;

  /* FrPWakeupPattern FLX0PRTC1 FLX0RWP[31:26] */
  Fr_UpdateCCConfig[FR_59_RENESAS_THIRTYTHREE].Fr_ConfigParamIdx = FR_CIDX_PWAKEUPPATTERN;
  Fr_UpdateCCConfig[FR_59_RENESAS_THIRTYTHREE].pOffset = &(LpCCCtrlReg->ulFLXAnFRPRTC1);
  Fr_UpdateCCConfig[FR_59_RENESAS_THIRTYTHREE].LulMask = FR_59_RENESAS_CIDX_PWAKEUPPATTERN_MASK;
  Fr_UpdateCCConfig[FR_59_RENESAS_THIRTYTHREE].LucBitsTobeMovedRight = FR_59_RENESAS_TWENTYSIX;
  Fr_UpdateCCConfig[FR_59_RENESAS_THIRTYTHREE].Fr_ConfigParamValuePtr = FR_59_RENESAS_EMPTY;
  
  /* FrIfGdSampleClockPeriod FLX0PRTC1 FLX0BRP[15:14] */
  Fr_UpdateCCConfig[FR_59_RENESAS_THIRTYFOUR].Fr_ConfigParamIdx = FR_CIDX_GDSAMPLECLOCKPERIOD;
  Fr_UpdateCCConfig[FR_59_RENESAS_THIRTYFOUR].pOffset = &(LpCCCtrlReg->ulFLXAnFRPRTC1);
  Fr_UpdateCCConfig[FR_59_RENESAS_THIRTYFOUR].LulMask = FR_59_RENESAS_CIDX_GDSAMPLECLOCKPERIOD_MASK;
  Fr_UpdateCCConfig[FR_59_RENESAS_THIRTYFOUR].LucBitsTobeMovedRight = FR_59_RENESAS_FOURTEEN;
  Fr_UpdateCCConfig[FR_59_RENESAS_THIRTYFOUR].Fr_ConfigParamValuePtr = FR_59_RENESAS_EMPTY;
  
  /* FrIfGdWakeupRxWindow FLX0PRTC1 FLX0RXW(24:16) */
  Fr_UpdateCCConfig[FR_59_RENESAS_THIRTYFIVE].Fr_ConfigParamIdx = FR_CIDX_GDWAKEUPRXWINDOW;
  Fr_UpdateCCConfig[FR_59_RENESAS_THIRTYFIVE].pOffset = &(LpCCCtrlReg->ulFLXAnFRPRTC1);
  Fr_UpdateCCConfig[FR_59_RENESAS_THIRTYFIVE].LulMask = FR_59_RENESAS_CIDX_GDWAKEUPRXWINDOW_MASK;
  Fr_UpdateCCConfig[FR_59_RENESAS_THIRTYFIVE].LucBitsTobeMovedRight = FR_59_RENESAS_SIXTEEN;
  Fr_UpdateCCConfig[FR_59_RENESAS_THIRTYFIVE].Fr_ConfigParamValuePtr = FR_59_RENESAS_EMPTY;
  
  /* FrIfGdWakeupRxLow FLX0PRTC2 FLX0RXI[5:0] */
  Fr_UpdateCCConfig[FR_59_RENESAS_THIRTYSIX].Fr_ConfigParamIdx = FR_CIDX_GDWAKEUPRXLOW;
  Fr_UpdateCCConfig[FR_59_RENESAS_THIRTYSIX].pOffset = &(LpCCCtrlReg->ulFLXAnFRPRTC2);
  Fr_UpdateCCConfig[FR_59_RENESAS_THIRTYSIX].LulMask = FR_59_RENESAS_CIDX_GDWAKEUPRXLOW_MASK;
  Fr_UpdateCCConfig[FR_59_RENESAS_THIRTYSIX].LucBitsTobeMovedRight = FR_59_RENESAS_EIGHT;
  Fr_UpdateCCConfig[FR_59_RENESAS_THIRTYSIX].Fr_ConfigParamValuePtr = FR_59_RENESAS_EMPTY;
  
  /* FrIfGdWakeupTxActive FLX0PRTC2 FLX0TXL[29:24] */
  Fr_UpdateCCConfig[FR_59_RENESAS_THIRTYSEVEN].Fr_ConfigParamIdx = FR_CIDX_GDWAKEUPTXACTIVE;
  Fr_UpdateCCConfig[FR_59_RENESAS_THIRTYSEVEN].pOffset = &(LpCCCtrlReg->ulFLXAnFRPRTC2);
  Fr_UpdateCCConfig[FR_59_RENESAS_THIRTYSEVEN].LulMask = FR_59_RENESAS_CIDX_GDWAKEUPTXACTIVE_MASK;
  Fr_UpdateCCConfig[FR_59_RENESAS_THIRTYSEVEN].LucBitsTobeMovedRight = FR_59_RENESAS_TWENTYFOUR;
  Fr_UpdateCCConfig[FR_59_RENESAS_THIRTYSEVEN].Fr_ConfigParamValuePtr = FR_59_RENESAS_EMPTY;
  
  /* FrIfGdWakeupTxIdle FLX0PRTC2 FLX0TXI[23:16] */
  Fr_UpdateCCConfig[FR_59_RENESAS_THIRTYEIGHT].Fr_ConfigParamIdx = FR_CIDX_GDWAKEUPTXIDLE;
  Fr_UpdateCCConfig[FR_59_RENESAS_THIRTYEIGHT].pOffset = &(LpCCCtrlReg->ulFLXAnFRPRTC2);
  Fr_UpdateCCConfig[FR_59_RENESAS_THIRTYEIGHT].LulMask = FR_59_RENESAS_CIDX_GDWAKEUPTXIDLE_MASK;
  Fr_UpdateCCConfig[FR_59_RENESAS_THIRTYEIGHT].LucBitsTobeMovedRight = FR_59_RENESAS_SIXTEEN;
  Fr_UpdateCCConfig[FR_59_RENESAS_THIRTYEIGHT].Fr_ConfigParamValuePtr = FR_59_RENESAS_EMPTY;
  
  /* FrIfGColdStartAttempts FLX0SUCC1 FLX0CSA[15:11] */
  Fr_UpdateCCConfig[FR_59_RENESAS_THIRTYNINE].Fr_ConfigParamIdx = FR_CIDX_GCOLDSTARTATTEMPTS;
  Fr_UpdateCCConfig[FR_59_RENESAS_THIRTYNINE].pOffset = &(LpCCCtrlReg->ulFLXAnFRSUCC1);
  Fr_UpdateCCConfig[FR_59_RENESAS_THIRTYNINE].LulMask = FR_59_RENESAS_CIDX_GCOLDSTARTATTEMPTS_MASK;
  Fr_UpdateCCConfig[FR_59_RENESAS_THIRTYNINE].LucBitsTobeMovedRight = FR_59_RENESAS_ELEVEN;
  Fr_UpdateCCConfig[FR_59_RENESAS_THIRTYNINE].Fr_ConfigParamValuePtr = FR_59_RENESAS_EMPTY;
  
  /* FrPChannels FLX0SUCC1 FLX0CCHA, FLX0CCHB */
  Fr_UpdateCCConfig[FR_59_RENESAS_FOURTY].Fr_ConfigParamIdx = FR_CIDX_PCHANNELS;
  Fr_UpdateCCConfig[FR_59_RENESAS_FOURTY].pOffset = &(LpCCCtrlReg->ulFLXAnFRSUCC1);
  Fr_UpdateCCConfig[FR_59_RENESAS_FOURTY].LulMask = FR_59_RENESAS_CIDX_PCHANNELS_MASK;
  Fr_UpdateCCConfig[FR_59_RENESAS_FOURTY].LucBitsTobeMovedRight = FR_59_RENESAS_TWENTYSIX;
  Fr_UpdateCCConfig[FR_59_RENESAS_FOURTY].Fr_ConfigParamValuePtr = FR_59_RENESAS_EMPTY;
  
  /* FrPKeySlotUsedForSync FLX0SUCC1 FLX0TXSY */
  Fr_UpdateCCConfig[FR_59_RENESAS_FOURTYONE].Fr_ConfigParamIdx = FR_CIDX_PKEYSLOTUSEDFORSYNC;
  Fr_UpdateCCConfig[FR_59_RENESAS_FOURTYONE].pOffset = &(LpCCCtrlReg->ulFLXAnFRSUCC1);
  Fr_UpdateCCConfig[FR_59_RENESAS_FOURTYONE].LulMask = FR_59_RENESAS_CIDX_PKEYSLOTUSEDFORSYNC_MASK;
  Fr_UpdateCCConfig[FR_59_RENESAS_FOURTYONE].LucBitsTobeMovedRight = FR_59_RENESAS_NINE;
  Fr_UpdateCCConfig[FR_59_RENESAS_FOURTYONE].Fr_ConfigParamValuePtr = FR_59_RENESAS_EMPTY;
  
  /* FrPKeySlotUsedForStartup FLX0SUCC1 FLX0TXST */
  Fr_UpdateCCConfig[FR_59_RENESAS_FOURTYTWO].Fr_ConfigParamIdx = FR_CIDX_PKEYSLOTUSEDFORSTARTUP;
  Fr_UpdateCCConfig[FR_59_RENESAS_FOURTYTWO].pOffset = &(LpCCCtrlReg->ulFLXAnFRSUCC1);
  Fr_UpdateCCConfig[FR_59_RENESAS_FOURTYTWO].LulMask = FR_59_RENESAS_CIDX_PKEYSLOTUSEDFORSTARTUP_MASK;
  Fr_UpdateCCConfig[FR_59_RENESAS_FOURTYTWO].LucBitsTobeMovedRight = FR_59_RENESAS_EIGHT;
  Fr_UpdateCCConfig[FR_59_RENESAS_FOURTYTWO].Fr_ConfigParamValuePtr = FR_59_RENESAS_EMPTY;
  
  /* FrPKeySlotOnlyEnabled FLX0SUCC1 FLX0TSM */
  Fr_UpdateCCConfig[FR_59_RENESAS_FOURTYTHREE].Fr_ConfigParamIdx = FR_CIDX_PKEYSLOTONLYENABLED;
  Fr_UpdateCCConfig[FR_59_RENESAS_FOURTYTHREE].pOffset = &(LpCCCtrlReg->ulFLXAnFRSUCC1);
  Fr_UpdateCCConfig[FR_59_RENESAS_FOURTYTHREE].LulMask = FR_59_RENESAS_CIDX_PKEYSLOTONLYENABLED_MASK;
  Fr_UpdateCCConfig[FR_59_RENESAS_FOURTYTHREE].LucBitsTobeMovedRight = FR_59_RENESAS_TWENTYTWO;
  Fr_UpdateCCConfig[FR_59_RENESAS_FOURTYTHREE].Fr_ConfigParamValuePtr = FR_59_RENESAS_EMPTY;
  
  /* FrPAllowHaltDueToClock FLX0SUCC1 FLX0HCSE */
  Fr_UpdateCCConfig[FR_59_RENESAS_FOURTYFOUR].Fr_ConfigParamIdx = FR_CIDX_PALLOWHALTDUETOCLOCK;
  Fr_UpdateCCConfig[FR_59_RENESAS_FOURTYFOUR].pOffset = &(LpCCCtrlReg->ulFLXAnFRSUCC1);
  Fr_UpdateCCConfig[FR_59_RENESAS_FOURTYFOUR].LulMask = FR_59_RENESAS_CIDX_PALLOWHALTDUETOCLOCK_MASK;
  Fr_UpdateCCConfig[FR_59_RENESAS_FOURTYFOUR].LucBitsTobeMovedRight = FR_59_RENESAS_TWENTYTHREE;
  Fr_UpdateCCConfig[FR_59_RENESAS_FOURTYFOUR].Fr_ConfigParamValuePtr = FR_59_RENESAS_EMPTY;
  
  /* FrPWakeupChannel FLX0SUCC1 FLX0WUCS */
  Fr_UpdateCCConfig[FR_59_RENESAS_FOURTYFIVE].Fr_ConfigParamIdx = FR_CIDX_PWAKEUPCHANNEL;
  Fr_UpdateCCConfig[FR_59_RENESAS_FOURTYFIVE].pOffset = &(LpCCCtrlReg->ulFLXAnFRSUCC1);
  Fr_UpdateCCConfig[FR_59_RENESAS_FOURTYFIVE].LulMask = FR_59_RENESAS_CIDX_PWAKEUPCHANNEL_MASK;
  Fr_UpdateCCConfig[FR_59_RENESAS_FOURTYFIVE].LucBitsTobeMovedRight = FR_59_RENESAS_TWENTYONE;
  Fr_UpdateCCConfig[FR_59_RENESAS_FOURTYFIVE].Fr_ConfigParamValuePtr = FR_59_RENESAS_EMPTY;
  
  /* FrPWakeupChannel FLX0SUCC1 FLX0WUCS */
  Fr_UpdateCCConfig[FR_59_RENESAS_FOURTYSIX].Fr_ConfigParamIdx = FR_CIDX_PALLOWPASSIVETOACTIVE;
  Fr_UpdateCCConfig[FR_59_RENESAS_FOURTYSIX].pOffset = &(LpCCCtrlReg->ulFLXAnFRSUCC1);
  Fr_UpdateCCConfig[FR_59_RENESAS_FOURTYSIX].LulMask = FR_59_RENESAS_CIDX_PALLOWPASSIVETOACTIVE_MASK;
  Fr_UpdateCCConfig[FR_59_RENESAS_FOURTYSIX].LucBitsTobeMovedRight = FR_59_RENESAS_SIXTEEN;
  Fr_UpdateCCConfig[FR_59_RENESAS_FOURTYSIX].Fr_ConfigParamValuePtr = FR_59_RENESAS_EMPTY;
  
  /* FrPAllowPassiveToActive FLX0SUCC1 FLX0PTA[20:16] */
  Fr_UpdateCCConfig[FR_59_RENESAS_FOURTYSEVEN].Fr_ConfigParamIdx = FR_CIDX_GLISTENNOISE;
  Fr_UpdateCCConfig[FR_59_RENESAS_FOURTYSEVEN].pOffset = &(LpCCCtrlReg->ulFLXAnFRSUCC2);
  Fr_UpdateCCConfig[FR_59_RENESAS_FOURTYSEVEN].LulMask = FR_59_RENESAS_CIDX_GLISTENNOISE_MASK;
  Fr_UpdateCCConfig[FR_59_RENESAS_FOURTYSEVEN].LucBitsTobeMovedRight = FR_59_RENESAS_TWENTYFOUR;
  Fr_UpdateCCConfig[FR_59_RENESAS_FOURTYSEVEN].Fr_ConfigParamValuePtr = FR_59_RENESAS_EMPTY;
  
  /* FrIfGMaxWithoutClockCorrectFatal FLX0SUCC3 FLX0WCP[7:4] */
  Fr_UpdateCCConfig[FR_59_RENESAS_FOURTYEIGHT].Fr_ConfigParamIdx = FR_CIDX_GMAXWITHOUTCLOCKCORRECTFATAL;
  Fr_UpdateCCConfig[FR_59_RENESAS_FOURTYEIGHT].pOffset = &(LpCCCtrlReg->ulFLXAnFRSUCC3);
  Fr_UpdateCCConfig[FR_59_RENESAS_FOURTYEIGHT].LulMask = FR_59_RENESAS_CIDX_GMAXWITHOUTCLOCKCORRECTFATAL_MASK;
  Fr_UpdateCCConfig[FR_59_RENESAS_FOURTYEIGHT].LucBitsTobeMovedRight = FR_59_RENESAS_FOUR;
  Fr_UpdateCCConfig[FR_59_RENESAS_FOURTYEIGHT].Fr_ConfigParamValuePtr = FR_59_RENESAS_EMPTY;
  
  /* Set to 63 for FlexRay Protocol 2.1 Rev. A compliance. */
  Fr_UpdateCCConfig[FR_59_RENESAS_FOURTYNINE].Fr_ConfigParamIdx = FR_CIDX_GCYCLECOUNTMAX;
  Fr_UpdateCCConfig[FR_59_RENESAS_FOURTYNINE].pOffset = NULL_PTR;
  Fr_UpdateCCConfig[FR_59_RENESAS_FOURTYNINE].LulMask = FR_59_RENESAS_ZERO;
  Fr_UpdateCCConfig[FR_59_RENESAS_FOURTYNINE].LucBitsTobeMovedRight = FR_59_RENESAS_ZERO;
  Fr_UpdateCCConfig[FR_59_RENESAS_FOURTYNINE].Fr_ConfigParamValuePtr = FR_59_RENESAS_MAX_CYCLE_COUNT;
  
  /* Set to 0 for FlexRay Protocol 2.1 Rev A compliance */
  Fr_UpdateCCConfig[FR_59_RENESAS_FIFTY].Fr_ConfigParamIdx = FR_CIDX_PSECONDKEYSLOTID;
  Fr_UpdateCCConfig[FR_59_RENESAS_FIFTY].pOffset = NULL_PTR;
  Fr_UpdateCCConfig[FR_59_RENESAS_FIFTY].LulMask = FR_59_RENESAS_ZERO;
  Fr_UpdateCCConfig[FR_59_RENESAS_FIFTY].LucBitsTobeMovedRight = FR_59_RENESAS_ZERO;
  Fr_UpdateCCConfig[FR_59_RENESAS_FIFTY].Fr_ConfigParamValuePtr = FR_59_RENESAS_ZERO;
  
  /* Set to 0 for FlexRay Protocol 2.1 Rev A compliance */
  Fr_UpdateCCConfig[FR_59_RENESAS_FIFTYONE].Fr_ConfigParamIdx = FR_CIDX_GDIGNOREAFTERTX;
  Fr_UpdateCCConfig[FR_59_RENESAS_FIFTYONE].pOffset = NULL_PTR;
  Fr_UpdateCCConfig[FR_59_RENESAS_FIFTYONE].LulMask = FR_59_RENESAS_ZERO;
  Fr_UpdateCCConfig[FR_59_RENESAS_FIFTYONE].LucBitsTobeMovedRight = FR_59_RENESAS_ZERO;
  Fr_UpdateCCConfig[FR_59_RENESAS_FIFTYONE].Fr_ConfigParamValuePtr = FR_59_RENESAS_ZERO;
  
  /*
     * FrPExternalSync :  Set to 'false' for FlexRay Protocol 2.1 Rev. A
     * compliance
     */
  Fr_UpdateCCConfig[FR_59_RENESAS_FIFTYTWO].Fr_ConfigParamIdx = FR_CIDX_PEXTERNALSYNC;
  Fr_UpdateCCConfig[FR_59_RENESAS_FIFTYTWO].pOffset = NULL_PTR;
  Fr_UpdateCCConfig[FR_59_RENESAS_FIFTYTWO].LulMask = FR_59_RENESAS_ZERO;
  Fr_UpdateCCConfig[FR_59_RENESAS_FIFTYTWO].LucBitsTobeMovedRight = FR_59_RENESAS_ZERO;
  Fr_UpdateCCConfig[FR_59_RENESAS_FIFTYTWO].Fr_ConfigParamValuePtr = FR_59_RENESAS_ZERO;
  
   /*
    * FrPFallBackInternal :  Set to 'false' for FlexRay Protocol 2.1 Rev. A
    * compliance
    */
  Fr_UpdateCCConfig[FR_59_RENESAS_FIFTYTHREE].Fr_ConfigParamIdx = FR_CIDX_PFALLBACKINTERNAL;
  Fr_UpdateCCConfig[FR_59_RENESAS_FIFTYTHREE].pOffset = NULL_PTR;
  Fr_UpdateCCConfig[FR_59_RENESAS_FIFTYTHREE].LulMask = FR_59_RENESAS_ZERO;
  Fr_UpdateCCConfig[FR_59_RENESAS_FIFTYTHREE].LucBitsTobeMovedRight = FR_59_RENESAS_ZERO;
  Fr_UpdateCCConfig[FR_59_RENESAS_FIFTYTHREE].Fr_ConfigParamValuePtr = FR_59_RENESAS_ZERO;
  
   /*
    * FrPNmVectorEarlyUpdate :  Set to 'false' for FlexRay Protocol 2.1
    * Rev. A compliance
    */
  Fr_UpdateCCConfig[FR_59_RENESAS_FIFTYFOUR].Fr_ConfigParamIdx = FR_CIDX_PNMVECTOREARLYUPDATE;
  Fr_UpdateCCConfig[FR_59_RENESAS_FIFTYFOUR].pOffset = NULL_PTR;
  Fr_UpdateCCConfig[FR_59_RENESAS_FIFTYFOUR].LulMask = FR_59_RENESAS_ZERO;
  Fr_UpdateCCConfig[FR_59_RENESAS_FIFTYFOUR].LucBitsTobeMovedRight = FR_59_RENESAS_ZERO;
  Fr_UpdateCCConfig[FR_59_RENESAS_FIFTYFOUR].Fr_ConfigParamValuePtr = FR_59_RENESAS_ZERO;
  
  /*
   * FrPTwoKeySlotMode :  Set to 'false' for FlexRay Protocol 2.1 Rev. A
   * compliance
     */
  Fr_UpdateCCConfig[FR_59_RENESAS_FIFTYFIVE].Fr_ConfigParamIdx = FR_CIDX_PTWOKEYSLOTMODE;
  Fr_UpdateCCConfig[FR_59_RENESAS_FIFTYFIVE].pOffset = NULL_PTR;
  Fr_UpdateCCConfig[FR_59_RENESAS_FIFTYFIVE].LulMask = FR_59_RENESAS_ZERO;
  Fr_UpdateCCConfig[FR_59_RENESAS_FIFTYFIVE].LucBitsTobeMovedRight = FR_59_RENESAS_ZERO;
  Fr_UpdateCCConfig[FR_59_RENESAS_FIFTYFIVE].Fr_ConfigParamValuePtr = FR_59_RENESAS_ZERO;
  
  /* Not present in registers FR_59_RENESAS_GDCYCLE */
  Fr_UpdateCCConfig[FR_59_RENESAS_FIFTYSIX].Fr_ConfigParamIdx = FR_CIDX_GDCYCLE;
  Fr_UpdateCCConfig[FR_59_RENESAS_FIFTYSIX].pOffset = NULL_PTR;
  Fr_UpdateCCConfig[FR_59_RENESAS_FIFTYSIX].LulMask = FR_59_RENESAS_ZERO;
  Fr_UpdateCCConfig[FR_59_RENESAS_FIFTYSIX].LucBitsTobeMovedRight = FR_59_RENESAS_ZERO;
  Fr_UpdateCCConfig[FR_59_RENESAS_FIFTYSIX].Fr_ConfigParamValuePtr = (Fr_59_Renesas_GpPeriodTimeConfigPtr->ulGdCycle);
  
  /* Not present in registers FR_59_RENESAS_GDMACRO_TICK */
  Fr_UpdateCCConfig[FR_59_RENESAS_FIFTYSEVEN].Fr_ConfigParamIdx = FR_CIDX_GDMACROTICK;
  Fr_UpdateCCConfig[FR_59_RENESAS_FIFTYSEVEN].pOffset = NULL_PTR;
  Fr_UpdateCCConfig[FR_59_RENESAS_FIFTYSEVEN].LulMask = FR_59_RENESAS_ZERO;
  Fr_UpdateCCConfig[FR_59_RENESAS_FIFTYSEVEN].LucBitsTobeMovedRight = FR_59_RENESAS_ZERO;
  Fr_UpdateCCConfig[FR_59_RENESAS_FIFTYSEVEN].Fr_ConfigParamValuePtr =
                                                                    (Fr_59_Renesas_GpPeriodTimeConfigPtr-> ulMacroTick);
  
  /* Not present in registers FR_PKEYSLOTID */
  Fr_UpdateCCConfig[FR_59_RENESAS_FIFTYEIGHT].Fr_ConfigParamIdx = FR_CIDX_PKEYSLOTID;
  Fr_UpdateCCConfig[FR_59_RENESAS_FIFTYEIGHT].pOffset = NULL_PTR;
  Fr_UpdateCCConfig[FR_59_RENESAS_FIFTYEIGHT].LulMask = FR_59_RENESAS_ZERO;
  Fr_UpdateCCConfig[FR_59_RENESAS_FIFTYEIGHT].LucBitsTobeMovedRight = FR_59_RENESAS_ZERO;
  Fr_UpdateCCConfig[FR_59_RENESAS_FIFTYEIGHT].Fr_ConfigParamValuePtr = LpCtrlTable->usFrPKeySlotId;                     
  
  /* Not present in registers FR_59_RENESAS_GDBIT */
  Fr_UpdateCCConfig[FR_59_RENESAS_FIFTYNINE].Fr_ConfigParamIdx = FR_CIDX_GDBIT;
  Fr_UpdateCCConfig[FR_59_RENESAS_FIFTYNINE].pOffset = NULL_PTR;
  Fr_UpdateCCConfig[FR_59_RENESAS_FIFTYNINE].LulMask = FR_59_RENESAS_ZERO;
  Fr_UpdateCCConfig[FR_59_RENESAS_FIFTYNINE].LucBitsTobeMovedRight = FR_59_RENESAS_ZERO;
  Fr_UpdateCCConfig[FR_59_RENESAS_FIFTYNINE].Fr_ConfigParamValuePtr = Fr_59_Renesas_GpPeriodTimeConfigPtr->ucGdBit;
  
  /* Not present in registers FR_59_RENESAS_GDSYMBOL_WINDOW */
  Fr_UpdateCCConfig[FR_59_RENESAS_SIXTY].Fr_ConfigParamIdx = FR_CIDX_GDSYMBOLWINDOW;
  Fr_UpdateCCConfig[FR_59_RENESAS_SIXTY].pOffset = NULL_PTR;
  Fr_UpdateCCConfig[FR_59_RENESAS_SIXTY].LulMask = FR_59_RENESAS_ZERO;
  Fr_UpdateCCConfig[FR_59_RENESAS_SIXTY].LucBitsTobeMovedRight = FR_59_RENESAS_ZERO;
  Fr_UpdateCCConfig[FR_59_RENESAS_SIXTY].Fr_ConfigParamValuePtr =
                                                                 Fr_59_Renesas_GpPeriodTimeConfigPtr-> ulGdSymbolWindow;
  /* Not present in registers FR_PPAYLOADLENGTHDYNMAX */
  Fr_UpdateCCConfig[FR_59_RENESAS_SIXTYONE].Fr_ConfigParamIdx = FR_CIDX_PPAYLOADLENGTHDYNMAX;
  Fr_UpdateCCConfig[FR_59_RENESAS_SIXTYONE].pOffset = NULL_PTR;
  Fr_UpdateCCConfig[FR_59_RENESAS_SIXTYONE].LulMask = FR_59_RENESAS_ZERO;
  Fr_UpdateCCConfig[FR_59_RENESAS_SIXTYONE].LucBitsTobeMovedRight = FR_59_RENESAS_ZERO;
  Fr_UpdateCCConfig[FR_59_RENESAS_SIXTYONE].Fr_ConfigParamValuePtr = LpCtrlTable->ucFrPPayloadLengthDynMax;
  
  /* Not present in registers FrIfGdNit */
  Fr_UpdateCCConfig[FR_59_RENESAS_SIXTYTWO].Fr_ConfigParamIdx = FR_CIDX_GDNIT;
  Fr_UpdateCCConfig[FR_59_RENESAS_SIXTYTWO].pOffset = NULL_PTR;
  Fr_UpdateCCConfig[FR_59_RENESAS_SIXTYTWO].LulMask = FR_59_RENESAS_ZERO;
  Fr_UpdateCCConfig[FR_59_RENESAS_SIXTYTWO].LucBitsTobeMovedRight = FR_59_RENESAS_ZERO;
  Fr_UpdateCCConfig[FR_59_RENESAS_SIXTYTWO].Fr_ConfigParamValuePtr = Fr_59_Renesas_GpPeriodTimeConfigPtr->ulGdNit;

 for (LucCount = (uint8)FR_59_RENESAS_ZERO; LucCount <= (uint8)FR_59_RENESAS_SIXTYTWO; LucCount++)
  {
    if (Fr_UpdateCCConfig[LucCount].Fr_ConfigParamIdx == Fr_ConfigParamIdx)
      {
        /* Update Offset */
            if (NULL_PTR != Fr_UpdateCCConfig[LucCount].pOffset)
            {
                LulOffset = (uint32)(*(Fr_UpdateCCConfig[LucCount].pOffset) & Fr_UpdateCCConfig[LucCount].LulMask);     
            } /* else No action required*/
        LucBitsTobeMovedRight = Fr_UpdateCCConfig[LucCount].LucBitsTobeMovedRight;

        if (FR_59_RENESAS_EMPTY != (Fr_UpdateCCConfig[LucCount].Fr_ConfigParamValuePtr))
        {
          *Fr_ConfigParamValuePtr = Fr_UpdateCCConfig[LucCount].Fr_ConfigParamValuePtr;                                 
        }
        else
        {
          *Fr_ConfigParamValuePtr = LulOffset >> LucBitsTobeMovedRight;
        }
      } /* else No action required*/
  }
  
  if (FR_CIDX_PSAMPLESPERMICROTICK == Fr_ConfigParamIdx)
  {
    /* pSamplepermicrotick */
    if ((uint32)FR_59_RENESAS_ZERO == *Fr_ConfigParamValuePtr)
    {
      /* T12_5NS */
      *Fr_ConfigParamValuePtr = FR_59_RENESAS_N2SAMPLES;
    }
    else
    {
      /* FR_59_RENESAS_T25NS/ T50NS*/
      *Fr_ConfigParamValuePtr = FR_59_RENESAS_N1SAMPLES;
    }
  }
  else if ((FR_CIDX_GDSAMPLECLOCKPERIOD == Fr_ConfigParamIdx) || (FR_CIDX_PDMICROTICK == Fr_ConfigParamIdx))
  {
    /* gdSampleClockPeriod */
    if ((uint32)FR_59_RENESAS_ZERO == *Fr_ConfigParamValuePtr)
    {
      if (FR_CIDX_PDMICROTICK == Fr_ConfigParamIdx)
      {
        /* FR_59_RENESAS_T25NS */
        *Fr_ConfigParamValuePtr = FR_59_RENESAS_T25NS;
      }
      else
      {
        /* T12_5NS */
        *Fr_ConfigParamValuePtr = FR_59_RENESAS_T12_5NS;
      }
    }
    else if ((uint32)FR_59_RENESAS_ONE == *Fr_ConfigParamValuePtr)
    {
      /* FR_59_RENESAS_T25NS */
      *Fr_ConfigParamValuePtr = FR_59_RENESAS_T25NS;
    }
    else 
    {
      /* T50NS */
      *Fr_ConfigParamValuePtr = FR_59_RENESAS_T50NS;
    }
  }
  else if (FR_CIDX_PCHANNELS == Fr_ConfigParamIdx)
  {
    if ((uint32)FR_59_RENESAS_ONE == *Fr_ConfigParamValuePtr)
    {
      *Fr_ConfigParamValuePtr = (uint32)FR_CHANNEL_A;
    }
    else if ((uint32)FR_59_RENESAS_TWO == *Fr_ConfigParamValuePtr)
    {
      *Fr_ConfigParamValuePtr = (uint32)FR_CHANNEL_B;
    }
    else if ((uint32)FR_59_RENESAS_THREE == *Fr_ConfigParamValuePtr)
    {
      *Fr_ConfigParamValuePtr = (uint32)FR_CHANNEL_AB;
    }
    else
    {
      /* Update the return value to E_NOT_OK */
      LucReturnValue = E_NOT_OK;
    }
  }
  else if (FR_CIDX_PWAKEUPCHANNEL == Fr_ConfigParamIdx)
  {
    if ((uint32)FR_59_RENESAS_ZERO == *Fr_ConfigParamValuePtr)
    {
      *Fr_ConfigParamValuePtr = (uint32)FR_CHANNEL_A;
    }
    else
    {
      *Fr_ConfigParamValuePtr = (uint32)FR_CHANNEL_B;
    }
  }
  else if ((FR_CIDX_POFFSETCORRECTIONSTART == Fr_ConfigParamIdx) || (FR_CIDX_GLISTENNOISE == Fr_ConfigParamIdx))        /* PRQA S 2004 # JV-01 */
  {
    *Fr_ConfigParamValuePtr = *Fr_ConfigParamValuePtr + (uint32)FR_59_RENESAS_ONE;                                      /* PRQA S 3383 # JV-01 */
  } /* else No Action required */
  return (LucReturnValue);
} /* End of function Fr_59_Renesas_UpdateCCConfig */
#define FR_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_GetIrqSts
**
** Service ID            : Not Applicable
**
** Description           : This function is to check if Timer Interrupt 0/2 is
**                         pending
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx, Fr_AbsTimerIdx
**
** InOut Parameters      : None
**
** Output Parameters     : Fr_IRQStatusPtr
**
** Return Parameter      : None
**
** Preconditions         : None
**
** Global Variables Used : Fr_59_Renesas_GpCtrlRegSet,
**                         Fr_59_Renesas_GpControllerConfigPtr
**
** Functions Invoked     : None
**
** Registers Used        : FLXAnFROS
**
** Reference ID          : FR_DUD_ACT_071
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(void, FR_PRIVATE_CODE)
            Fr_59_Renesas_GetIrqSts(const uint8 Fr_CtrlIdx, const uint8 Fr_AbsTimerIdx, boolean *const Fr_IRQStatusPtr)
{
  /* Declare pointer to register */
  P2CONST(volatile Fr_59_Renesas_AbsTimerConfigType, TYPEDEF, FR_APPL_CONST) LpAbsTimerConfig;
  P2CONST(volatile Fr_59_Renesas_AbsTimerConfigType, AUTOMATIC, FR_APPL_CONST) LpAbsTimer;
  P2CONST(volatile Fr_59_Renesas_RegisterSetType, AUTOMATIC, FR_CONFIG_DATA)
  LpCtrlRegSet;
  P2VAR(volatile Fr_59_Renesas_OperationRegType, AUTOMATIC, REGSPACE) LpFROReg;                                         /* PRQA S 3678 # JV-01 */
  uint32 LulData;
  Std_ReturnType LucReturnValue;
  /* Copy global pointer to local pointer */
  LpAbsTimerConfig = Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pAbsTimerConfig;
  LpCtrlRegSet = Fr_59_Renesas_GpCtrlRegSet[Fr_CtrlIdx];                                                                
  LpFROReg = LpCtrlRegSet->pFROReg;                                                                                    
  /* Get the pointer to Absolute Timer configuration of the corresponding Fr_AbsTimerIdx */
  LpAbsTimer = &LpAbsTimerConfig[Fr_AbsTimerIdx];                                                                       
  if (FR_59_RENESAS_TIMER0 == LpAbsTimer->enTimerSelection)                                                             
  {
    /* Read the value of FROS register */
    LulData = LpFROReg->ulFLXAnFROS;                                                                                   
    if (FR_59_RENESAS_FLX0FROS_T0IS_MASK == (LulData & FR_59_RENESAS_FLX0FROS_T0IS_MASK))
    {
      LucReturnValue = E_OK;
    }
    else
    {
      LucReturnValue = E_NOT_OK;
    }
  }
  else /* Timer 2 */
  {
    /* Read the value of FROS register */
    LulData = LpFROReg->ulFLXAnFROS;
    if (FR_59_RENESAS_FLX0FROS_T2IS_MASK == (LulData & FR_59_RENESAS_FLX0FROS_T2IS_MASK))
    {
      LucReturnValue = E_OK;
    }
    else
    {
      LucReturnValue = E_NOT_OK;
    }
  }
  /* Check if the interrupt is pending */
  if (E_OK == LucReturnValue)
  {
    /* Update the value of the output parameter to TRUE */
    *Fr_IRQStatusPtr = FR_59_RENESAS_TRUE;                                                                              
  }
  else
  {
    /* Update the value of the output parameter to FALSE */
    *Fr_IRQStatusPtr = FR_59_RENESAS_FALSE;
  }
} /* End of function Fr_59_Renesas_GetIrqSts */
#define FR_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_DisableTimer
**
** Service ID            : Not Applicable
**
** Description           : This function is to disable Timer 0/2 by
**                         FlexRay Operation Control Register
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx, Fr_AbsTimerIdx
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : None
**
** Preconditions         : None
**
** Global Variables Used : Fr_59_Renesas_GpCtrlRegSet,
**                         Fr_59_Renesas_GpControllerConfigPtr
**
** Functions Invoked     : FR_59_RENESAS_ENTER_CRITICAL_SECTION,
**                         FR_59_RENESAS_EXIT_CRITICAL_SECTION
**
** Registers Used        : FLXAnFROC
**
** Reference ID          : FR_DUD_ACT_072, FR_DUD_ACT_072_CRT001,
** Reference ID          : FR_DUD_ACT_072_CRT002, FR_DUD_ACT_072_CRT003,
** Reference ID          : FR_DUD_ACT_072_CRT004, FR_DUD_ACT_072_REG001,
** Reference ID          : FR_DUD_ACT_072_REG002
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(void, FR_PRIVATE_CODE) Fr_59_Renesas_DisableTimer(const uint8 Fr_CtrlIdx, const uint8 Fr_AbsTimerIdx)             
{
  /* Declare pointer to register */
  P2CONST(volatile Fr_59_Renesas_AbsTimerConfigType, TYPEDEF, FR_APPL_CONST) LpAbsTimerConfig;
  P2CONST(volatile Fr_59_Renesas_AbsTimerConfigType, AUTOMATIC, FR_APPL_CONST) LpAbsTimer;
  P2CONST(volatile Fr_59_Renesas_RegisterSetType, AUTOMATIC, FR_CONFIG_DATA) LpCtrlRegSet;
  P2VAR(volatile Fr_59_Renesas_OperationRegType, AUTOMATIC, REGSPACE) LpFROReg;
  /* Declare variable to store register value */
  uint32 LulData;
  /* Copy global pointer to local pointer */
  LpAbsTimerConfig = Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pAbsTimerConfig;
  LpCtrlRegSet = Fr_59_Renesas_GpCtrlRegSet[Fr_CtrlIdx];                                                                
  LpFROReg = LpCtrlRegSet->pFROReg;                                                                                    
  /* Get the pointer to Absolute Timer configuration of the corresponding Fr_AbsTimerIdx */
  LpAbsTimer = &LpAbsTimerConfig[Fr_AbsTimerIdx];                                                                      
  /* Timer 0 */
  if (FR_59_RENESAS_TIMER0 == LpAbsTimer->enTimerSelection)                                                             
  {
    /* Check if critical section protection is required */
    #if (FR_59_RENESAS_CRITICAL_SECTION_PROTECTION == STD_ON)
    /* Enter the Critical Section Area */
    FR_59_RENESAS_ENTER_CRITICAL_SECTION(FR_INTERRUPT_CONTROL_PROTECTION);
    #endif
    LulData = LpFROReg->ulFLXAnFROC;                                                                                   
    /* Disable the timer 2 interrupt */
    /* Writing in to FlexRay Operation Control Register and mirror address */
    LpFROReg->ulFLXAnFROC = LulData & FR_59_RENESAS_FLX0FROC_T0IE_RESET;
    /* Check if critical section protection is required */
    #if (FR_59_RENESAS_CRITICAL_SECTION_PROTECTION == STD_ON)
    /* Exit the Critical Section Area */
    FR_59_RENESAS_EXIT_CRITICAL_SECTION(FR_INTERRUPT_CONTROL_PROTECTION);
    #endif
  }
  else
  {
    /* Check if critical section protection is required */
    #if (FR_59_RENESAS_CRITICAL_SECTION_PROTECTION == STD_ON)
    /* Enter the Critical Section Area */
    FR_59_RENESAS_ENTER_CRITICAL_SECTION(FR_INTERRUPT_CONTROL_PROTECTION);
    #endif
    LulData = LpFROReg->ulFLXAnFROC;
    /* Disable the timer 2 interrupt */
    /* Writing in to FlexRay Operation Control Register and mirror address */
    LpFROReg->ulFLXAnFROC = LulData & FR_59_RENESAS_FLX0FROC_T2IE_RESET;
    /* Check if critical section protection is required */
    #if (FR_59_RENESAS_CRITICAL_SECTION_PROTECTION == STD_ON)
    /* Exit the Critical Section Area */
    FR_59_RENESAS_EXIT_CRITICAL_SECTION(FR_INTERRUPT_CONTROL_PROTECTION);
    #endif
  }
} /* End of function Fr_59_Renesas_DisableTimer */
#define FR_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_ClearTimerInterrupt
**
** Service ID            : Not Applicable
**
** Description           : This function is to clear Timer Interrupt by
**                         FlexRay Operation Status Register
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx, Fr_AbsTimerIdx
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : None
**
** Global Variables Used : Fr_59_Renesas_GpControllerConfigPtr,
**                         Fr_59_Renesas_GpCtrlRegSet
**
** Functions Invoked     : FR_59_RENESAS_DEM_REPORT_ERROR,
**                         FR_59_RENESAS_ENTER_CRITICAL_SECTION,
**                         FR_59_RENESAS_EXIT_CRITICAL_SECTION
**
** Registers Used        : FLXAnFROS
**
** Reference ID          : FR_DUD_ACT_073, FR_DUD_ACT_073_CRT001,
** Reference ID          : FR_DUD_ACT_073_CRT002, FR_DUD_ACT_073_CRT003,
** Reference ID          : FR_DUD_ACT_073_CRT004, FR_DUD_ACT_073_ERR001,
** Reference ID          : FR_DUD_ACT_073_REG001, FR_DUD_ACT_073_REG002
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PRIVATE_CODE)
                                  Fr_59_Renesas_ClearTimerInterrupt(const uint8 Fr_CtrlIdx, const uint8 Fr_AbsTimerIdx) 
{
  /* Declare pointer to register */
  P2CONST(volatile Fr_59_Renesas_AbsTimerConfigType, TYPEDEF, FR_APPL_CONST) LpAbsTimerConfig;
  P2CONST(volatile Fr_59_Renesas_AbsTimerConfigType, AUTOMATIC, FR_APPL_CONST) LpAbsTimer;
  P2CONST(volatile Fr_59_Renesas_RegisterSetType, AUTOMATIC, FR_CONFIG_DATA) LpCtrlRegSet;
  P2VAR(volatile Fr_59_Renesas_OperationRegType, AUTOMATIC, REGSPACE) LpFROReg;
  /* Declare local pointer to CC configuration */
  P2CONST(Fr_59_Renesas_CtrlTableType, TYPEDEF, FR_CONFIG_DATA) LpCtrlTable;
  /* Declare local pointer to Dem Event Id */
  P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF, FR_CONFIG_DATA)
  LpDemEventId;
  uint32 LulFrosValue;
  uint32 LulFrosMask;
  /* Declare the variable to store the return value */
  Std_ReturnType LucReturnValue;
  volatile uint16 LusLoopCount;
  /* Initialize return value */
  LucReturnValue = E_OK;
  /* Copy global pointer to local pointer */
  LpAbsTimerConfig = Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pAbsTimerConfig;
  LpCtrlRegSet = Fr_59_Renesas_GpCtrlRegSet[Fr_CtrlIdx];                                                                
  LpFROReg = LpCtrlRegSet->pFROReg;                                                                                    
  LusLoopCount = FR_59_RENESAS_ZERO;
  LpCtrlTable = (P2CONST(Fr_59_Renesas_CtrlTableType, AUTOMATIC,
                                          FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pCtrlTable);
  /* Get the pointer to Absolute Timer configuration of the corresponding Fr_AbsTimerIdx */
  LpAbsTimer = &LpAbsTimerConfig[Fr_AbsTimerIdx];                                                                      
  do
  {
    /* Timer 0 */
    if (FR_59_RENESAS_TIMER0 == LpAbsTimer->enTimerSelection)                                                           
    {
      /* Check if critical section protection is required */
      #if (FR_59_RENESAS_CRITICAL_SECTION_PROTECTION == STD_ON)
      /* Enter the Critical Section Area */
      FR_59_RENESAS_ENTER_CRITICAL_SECTION(FR_INTERRUPT_CONTROL_PROTECTION);
      #endif
      /* Reset the flag T0IS of the register FROS */
      /* Writing in to FlexRay Operation Status Register and mirror address */
      LpFROReg->ulFLXAnFROS = FR_59_RENESAS_FLX0FROS_T0IS_CLR;                                                         
      /* Read the status interrupt register */
      LulFrosValue = LpFROReg->ulFLXAnFROS;
      LulFrosMask = FR_59_RENESAS_FLX0FROS_T0IS_CLR;
      /* Check if critical section protection is required */
      #if (FR_59_RENESAS_CRITICAL_SECTION_PROTECTION == STD_ON)
      /* Exit the Critical Section Area */
      FR_59_RENESAS_EXIT_CRITICAL_SECTION(FR_INTERRUPT_CONTROL_PROTECTION);
      #endif
    }
    /* Timer 2 */
    else
    {
      /* Check if critical section protection is required */
      #if (FR_59_RENESAS_CRITICAL_SECTION_PROTECTION == STD_ON)
      /* Enter the Critical Section Area */
      FR_59_RENESAS_ENTER_CRITICAL_SECTION(FR_INTERRUPT_CONTROL_PROTECTION);
      #endif
      /* Reset the flag T2IS of the register FROS */
      /* Writing in to FlexRay Operation Status Register and mirror address */
      LpFROReg->ulFLXAnFROS = FR_59_RENESAS_FLX0FROS_T2IS_CLR;
      /* Read the status interrupt register */
      LulFrosValue = LpFROReg->ulFLXAnFROS;
      LulFrosMask = FR_59_RENESAS_FLX0FROS_T2IS_CLR;
      /* Check if critical section protection is required */
      #if (FR_59_RENESAS_CRITICAL_SECTION_PROTECTION == STD_ON)
      /* Exit the Critical Section Area */
      FR_59_RENESAS_EXIT_CRITICAL_SECTION(FR_INTERRUPT_CONTROL_PROTECTION);
      #endif
    }
    if (LusLoopCount == (uint16)(LpCtrlTable->usFlagClearMaxWait))                                                      /* PRQA S 3416 # JV-01 */
    {
      LpDemEventId = (P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF,
                                         FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pDemEventId);
      if (FR_59_RENESAS_DEM_NOT_CONFIGURED != LpDemEventId->usReadTimeoutFailure)                                       
      {
        FR_59_RENESAS_DEM_REPORT_ERROR(LpDemEventId->usReadTimeoutFailure, DEM_EVENT_STATUS_FAILED);
      } /* else No Action required */
      LucReturnValue = E_NOT_OK;
    } /* else No Action required */
    LusLoopCount++;                                                                                                     /* PRQA S 3387, 3383 # JV-01, JV-01 */
  } while ((LulFrosMask == (LulFrosValue & LulFrosMask)) && (E_OK == LucReturnValue));
  return (LucReturnValue);
} /* End of function Fr_59_Renesas_ClearTimerInterrupt */
#define FR_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_EnableTimerInterrupt
**
** Service ID            : Not Applicable
**
** Description           : This function is to enable Timer Interrupt by
**                         FlexRay Operation Control Register
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx, Fr_AbsTimerIdx
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : None
**
** Preconditions         : None
**
** Global Variables Used : Fr_59_Renesas_GpCtrlRegSet,
**                         Fr_59_Renesas_GpControllerConfigPtr
**
** Functions Invoked     : FR_59_RENESAS_ENTER_CRITICAL_SECTION,
**                         FR_59_RENESAS_EXIT_CRITICAL_SECTION.
**
** Registers Used        : FLXAnFROC
**
** Reference ID          : FR_DUD_ACT_074, FR_DUD_ACT_074_CRT001,
** Reference ID          : FR_DUD_ACT_074_CRT002, FR_DUD_ACT_074_CRT003,
** Reference ID          : FR_DUD_ACT_074_CRT004, FR_DUD_ACT_074_REG001,
** Reference ID          : FR_DUD_ACT_074_REG002
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(void, FR_PRIVATE_CODE)
Fr_59_Renesas_EnableTimerInterrupt(const uint8 Fr_CtrlIdx, const uint8 Fr_AbsTimerIdx)                               
{
  /* Declare pointer to register */
  P2CONST(volatile Fr_59_Renesas_AbsTimerConfigType, TYPEDEF, FR_APPL_CONST) LpAbsTimerConfig;
  P2CONST(volatile Fr_59_Renesas_AbsTimerConfigType, AUTOMATIC, FR_APPL_CONST) LpAbsTimer;
  P2CONST(volatile Fr_59_Renesas_RegisterSetType, AUTOMATIC, FR_CONFIG_DATA) LpCtrlRegSet;
  P2VAR(volatile Fr_59_Renesas_OperationRegType, AUTOMATIC, REGSPACE) LpFROReg;
  /* Declare variable to store return value */
  uint32 LulData;
  /* Copy global pointer to local pointer */
  LpAbsTimerConfig = Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pAbsTimerConfig;
  LpCtrlRegSet = Fr_59_Renesas_GpCtrlRegSet[Fr_CtrlIdx];                                                                
  LpFROReg = LpCtrlRegSet->pFROReg;                                                                                    
  /* Get the pointer to Absolute Timer configuration of the corresponding Fr_AbsTimerIdx */
  LpAbsTimer = &LpAbsTimerConfig[Fr_AbsTimerIdx];                                                                      
  /* Timer 0 */
  if (FR_59_RENESAS_TIMER0 == LpAbsTimer->enTimerSelection)                                                             
  {
    /* Check if critical section protection is required */
    #if (FR_59_RENESAS_CRITICAL_SECTION_PROTECTION == STD_ON)
    /* Enter the Critical Section Area */
    FR_59_RENESAS_ENTER_CRITICAL_SECTION(FR_INTERRUPT_CONTROL_PROTECTION);
    #endif
    /* Read the value of the operation control register */
    LulData = LpFROReg->ulFLXAnFROC;                                                                                   
    /* Enable the interrupt line of timer0 */
    /* Writing in to FlexRay Operation Control Register and
     mirror address */
    LpFROReg->ulFLXAnFROC = LulData | FR_59_RENESAS_FLX0FROC_T0IE_SET;
    /* Check if critical section protection is required */
    #if (FR_59_RENESAS_CRITICAL_SECTION_PROTECTION == STD_ON)
    /* Exit the Critical Section Area */
    FR_59_RENESAS_EXIT_CRITICAL_SECTION(FR_INTERRUPT_CONTROL_PROTECTION);
    #endif
  }
  /* Timer 2 */
  else
  {
    /* Check if critical section protection is required */
    #if (FR_59_RENESAS_CRITICAL_SECTION_PROTECTION == STD_ON)
    /* Enter the Critical Section Area */
    FR_59_RENESAS_ENTER_CRITICAL_SECTION(FR_INTERRUPT_CONTROL_PROTECTION);
    #endif
    /* Read the value of the operation control register */
    LulData = LpFROReg->ulFLXAnFROC;
    /* Enable the interrupt line of timer2 */
    /* Writing in to FlexRay Operation Control Register and mirror address */
    LpFROReg->ulFLXAnFROC = LulData | FR_59_RENESAS_FLX0FROC_T2IE_SET;
    /* Check if critical section protection is required */
    #if (FR_59_RENESAS_CRITICAL_SECTION_PROTECTION == STD_ON)
    /* Exit the Critical Section Area */
    FR_59_RENESAS_EXIT_CRITICAL_SECTION(FR_INTERRUPT_CONTROL_PROTECTION);
    #endif
  }
} /* End of function Fr_59_Renesas_EnableTimerInterrupt */
#define FR_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_CancelTimerInterrupt
**
** Service ID            : Not Applicable
**
** Description           : This function is to cancel Timer Interrupt by
**                         FlexRay Timer 0/2 Configuration Register
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx, Fr_AbsTimerIdx
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : None
**
** Preconditions         : None
**
** Global Variables Used : Fr_59_Renesas_GpCtrlRegSet,
**                         Fr_59_Renesas_GpControllerConfigPtr
**
** Functions Invoked     : None.
**
** Registers Used        : FLXAnFRT0C, FLXAnFRT2C
**
** Reference ID          : FR_DUD_ACT_075, FR_DUD_ACT_075_REG001,
** Reference ID          : FR_DUD_ACT_075_REG002
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(void, FR_PRIVATE_CODE) Fr_59_Renesas_CancelTimerInterrupt(const uint8 Fr_CtrlIdx, const uint8 Fr_AbsTimerIdx)     
{
  /* Declare pointer to register */
  P2CONST(volatile Fr_59_Renesas_AbsTimerConfigType, TYPEDEF, FR_APPL_CONST) LpAbsTimerConfig;
  P2CONST(volatile Fr_59_Renesas_AbsTimerConfigType, AUTOMATIC, FR_APPL_CONST) LpAbsTimer;
  P2CONST(volatile Fr_59_Renesas_RegisterSetType, AUTOMATIC, FR_CONFIG_DATA) LpCtrlRegSet;
  P2VAR(volatile Fr_59_Renesas_TimerRegType, AUTOMATIC, REGSPACE) LpTimerReg;
  P2VAR(volatile uint32, AUTOMATIC, REGSPACE) LpFLXAnFRT2C;
  /* Declare variable to store register value */
  uint32 LulTimerValue;
  /* Copy global pointer to local pointer */
  LpAbsTimerConfig = Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pAbsTimerConfig;
  LpCtrlRegSet = Fr_59_Renesas_GpCtrlRegSet[Fr_CtrlIdx];                                                                
  LpTimerReg = LpCtrlRegSet->pTimerReg;                                                                                
  LpFLXAnFRT2C = LpCtrlRegSet->plFLXAnFRT2C;
  /* Get the pointer to Absolute Timer configuration of the corresponding Fr_AbsTimerIdx */
  LpAbsTimer = &LpAbsTimerConfig[Fr_AbsTimerIdx];                                                                      
  /* Timer 0 */
  if (FR_59_RENESAS_TIMER0 == LpAbsTimer->enTimerSelection)                                                             
  {
    /* Read the value of the timer register */
    LulTimerValue = LpTimerReg->ulFLXAnFRT0C;                                                                          
    /* Stop the Timer */
    /* Writing in to FlexRay Timer Configuration Register and mirror address */
    LpTimerReg->ulFLXAnFRT0C = LulTimerValue & FR_59_RENESAS_FLX0T0C_FLX0T0RC_HALT;
  }
  else /* Timer 2 */
  {
    /* Read the value of the timer register */
    LulTimerValue = *LpFLXAnFRT2C;                                                                                     
    /* Stop the Timer */
    /* Writing in to FlexRay Timer Configuration Register and mirror address */
    *LpFLXAnFRT2C = LulTimerValue & FR_59_RENESAS_FLX0T2C_FLX0T2RC_HALT;
  } /* End of function Fr_59_Renesas_CancelTimerInterrupt */
}
#define FR_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_StartTimer
**
** Service ID            : Not Applicable
**
** Description           : This function is to start the timer for timer
**                         interrupt by FlexRay Timer Configuration Register
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx, Fr_AbsTimerIdx, Fr_Cycle, Fr_Offset
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : None
**
** Global Variables Used : Fr_59_Renesas_GpControllerConfigPtr,
**                         Fr_59_Renesas_GpCtrlRegSet
**
** Functions Invoked     : FR_59_RENESAS_DEM_REPORT_ERROR,
**                         Fr_59_Renesas_GetPOCStsFlag,
**                         Fr_59_Renesas_TimerRunning
**
** Registers Used        : FLXAnFRT0C, FLXAnFRT2C
**
** Reference ID          : FR_DUD_ACT_076, FR_DUD_ACT_076_ERR001,
** Reference ID          : FR_DUD_ACT_076_REG001, FR_DUD_ACT_076_REG002
** Reference ID          : FR_DUD_ACT_076_REG003, FR_DUD_ACT_076_REG004
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PRIVATE_CODE)
Fr_59_Renesas_StartTimer(const uint8 Fr_CtrlIdx, const uint8 Fr_AbsTimerIdx, uint8 Fr_Cycle, const uint16 Fr_Offset)    
{
  /* Declare pointer to register */
  P2CONST(volatile Fr_59_Renesas_AbsTimerConfigType, TYPEDEF, FR_APPL_CONST) LpAbsTimerConfig;
  P2CONST(volatile Fr_59_Renesas_AbsTimerConfigType, AUTOMATIC, FR_APPL_CONST) LpAbsTimer;
  P2CONST(volatile Fr_59_Renesas_RegisterSetType, AUTOMATIC, FR_CONFIG_DATA) LpCtrlRegSet;
  P2VAR(volatile Fr_59_Renesas_TimerRegType, AUTOMATIC, REGSPACE) LpTimerReg;
  P2VAR(volatile uint32, AUTOMATIC, REGSPACE) LpFLXAnFRT2C;
  /* Declare local pointer to Dem Event Id */
  P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF, FR_CONFIG_DATA)
  LpDemEventId;
  /* Declare the variable to store POC status */
  uint32 LulData;
  /* Declare variable to store register value */
  uint32 LulTimerValue;
  /* Declare the variable to store the return value */
  Std_ReturnType LucReturnValue;
  /* Declare the variable to store the timer mode select */
  Fr_59_Renesas_TimerModeSelectType LenTimerModeSelect;
  /* Initialize the return value */
  LucReturnValue = E_OK;
  /* Copy global pointer to local pointer */
  LpAbsTimerConfig = Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pAbsTimerConfig;
  LpCtrlRegSet = Fr_59_Renesas_GpCtrlRegSet[Fr_CtrlIdx];                                                                
  /* Read the POC State by getting FLX0CCSV register value */
  LulData = Fr_59_Renesas_GetPOCStsFlag(Fr_CtrlIdx);
  /* Get the pointer to Absolute Timer configuration of the corresponding Fr_AbsTimerIdx */
  LpAbsTimer = &LpAbsTimerConfig[Fr_AbsTimerIdx];                                                                       
  /* Get the Timer mode */
  LenTimerModeSelect = LpAbsTimer->enTimerModeSelect;                                                                   
  /* Check if the CC is in normal active state */
  if ((FR_59_RENESAS_NORMAL_ACTIVE_STATE == LulData) || (FR_59_RENESAS_NORMAL_PASSIVE_STATE == LulData))
  {
    /* Stop Absolute Timer by setting T0RC, T2RC bit */
    if (FR_59_RENESAS_TIMER0 == LpAbsTimer->enTimerSelection)
    {
      LpTimerReg = LpCtrlRegSet->pTimerReg;                                                                            
      LulTimerValue = LpTimerReg->ulFLXAnFRT0C;                                                                        
      /* Stop the Timer 0 */
      /* Writing in to FlexRay Timer Configuration Register and mirror address */
      LpTimerReg->ulFLXAnFRT0C = LulTimerValue & FR_59_RENESAS_FLX0T0C_FLX0T0RC_HALT;
      /* Read the value of the timer register */
      LulTimerValue = LpTimerReg->ulFLXAnFRT0C;
    }
    else /* Timer 2 */
    {
      LpFLXAnFRT2C = LpCtrlRegSet->plFLXAnFRT2C;
      LulTimerValue = *LpFLXAnFRT2C;                                                                                   
      /* Stop the Timer 2 */
      /* Writing in to FlexRay Timer Configuration Register and mirror address */
      *LpFLXAnFRT2C = LulTimerValue & FR_59_RENESAS_FLX0T2C_FLX0T2RC_HALT;
      /* Read the value of the timer register */
      LulTimerValue = *LpFLXAnFRT2C;
    }
    /* Clear the value of previous cycle code and Macrotick value */
    LulTimerValue = LulTimerValue & FR_59_RENESAS_FLX0T0C_FLX0T0RC_CLR;
    #if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_OFF)
    /* If the DET is enabled,the 'FR_59_RENESAS_DEV_ERROR_DETECT' switch is added to avoid QAC warning 5:2985 */
    Fr_Cycle = Fr_Cycle & FR_59_RENESAS_MAX_CYCLE_COUNT;                                                                /* PRQA S 1338 # JV-01 */
    #endif
    /* Force timer interrupt is generated every sixty-fourth Cycle */
    Fr_Cycle = Fr_Cycle | (uint8)FR_59_RENESAS_INT_EVERY_64_CYCLE;                                                      /* PRQA S 1338 # JV-01 */
    /* Set Timer Mode Select, Macrotick Offset and Cycle Code */
    LulTimerValue = LulTimerValue | (((uint32)LenTimerModeSelect << FR_59_RENESAS_ONE) |
                                              ((uint32)Fr_Offset << FR_59_RENESAS_FLX0TXC_OFFSET_SHIFT) |
                                                                ((uint32)Fr_Cycle << FR_59_RENESAS_FLX0TXC_CYC_SHIFT));
    /* Load the cycle and offset value in the timer register and start the timer */
    /* Writing in to FlexRay Timer Configuration Register and mirror address */
    Fr_59_Renesas_TimerRunning(Fr_CtrlIdx, LulTimerValue, Fr_AbsTimerIdx);
  }
  else
  {
    /* Report Error to DEM */
    LpDemEventId = (P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF,
                                         FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pDemEventId);
    if (FR_59_RENESAS_DEM_NOT_CONFIGURED != LpDemEventId->usHardwareTestFailure)                                        
    {
      FR_59_RENESAS_DEM_REPORT_ERROR(LpDemEventId->usHardwareTestFailure, DEM_EVENT_STATUS_FAILED);
    } /* else No Action required */
    /* Set Return Value as E_NOT_OK */
    LucReturnValue = E_NOT_OK;
  }
  return (LucReturnValue);
} /* End of Fr_59_Renesas_StartTimer */
#define FR_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_TimerRunning
**
** Service ID            : Not Applicable
**
** Description           : This function is to start the timer by
**                         FlexRay Timer Configuration Register
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx, Data, Fr_AbsTimerIdx
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : None
**
** Preconditions         : None
**
** Global Variables Used : Fr_59_Renesas_GpCtrlRegSet,
**                         Fr_59_Renesas_GpControllerConfigPtr
**
** Functions Invoked     : None.
**
** Registers Used        : FLXAnFRT0C, FLXAnFRT2C
**
** Reference ID          : FR_DUD_ACT_077, FR_DUD_ACT_077_REG001,
** Reference ID          : FR_DUD_ACT_077_REG002
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(void, FR_PRIVATE_CODE)
                      Fr_59_Renesas_TimerRunning(const uint8 Fr_CtrlIdx, const uint32 Data, const uint8 Fr_AbsTimerIdx) /* PRQA S 1505 # JV-01 */
{
  /* Declare pointer to register */
  P2CONST(volatile Fr_59_Renesas_AbsTimerConfigType, TYPEDEF, FR_APPL_CONST) LpAbsTimerConfig;
  P2CONST(volatile Fr_59_Renesas_AbsTimerConfigType, AUTOMATIC, FR_APPL_CONST) LpAbsTimer;
  P2CONST(volatile Fr_59_Renesas_RegisterSetType, AUTOMATIC, FR_CONFIG_DATA) LpCtrlRegSet;
  P2VAR(volatile Fr_59_Renesas_TimerRegType, AUTOMATIC, REGSPACE) LpTimerReg;
  P2VAR(volatile uint32, AUTOMATIC, REGSPACE) LpFLXAnFRT2C;
  /* Copy global pointer to local pointer */
  LpAbsTimerConfig = Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pAbsTimerConfig;
  LpCtrlRegSet = Fr_59_Renesas_GpCtrlRegSet[Fr_CtrlIdx];                                                                
  /* Get the pointer to Absolute Timer configuration of the corresponding Fr_AbsTimerIdx */
  LpAbsTimer = &LpAbsTimerConfig[Fr_AbsTimerIdx];                                                                 
  if (FR_59_RENESAS_TIMER0 == LpAbsTimer->enTimerSelection)                                                             
  {
    LpTimerReg = LpCtrlRegSet->pTimerReg;                                                                              
    /* Writing in to FlexRay Timer Configuration Register and mirror
     address */
    LpTimerReg->ulFLXAnFRT0C = Data | FR_59_RENESAS_FLX0T0C_FLX0T0RC_SET;                                              
  }
  else
  {
    LpFLXAnFRT2C = LpCtrlRegSet->plFLXAnFRT2C;
    /* Writing in to FlexRay Timer Configuration Register and mirror
     address */
    *LpFLXAnFRT2C = Data | FR_59_RENESAS_FLX0T2C_FLX0T2RC_SET;                                                         
  }
} /* End of function Fr_59_Renesas_TimerRunning */
#define FR_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_UpdateWakeupRxSts
**
** Service ID            : Not Applicable
**
** Description           : This function update the wakeup reception status
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx
**
** InOut Parameters      : None
**
** Output Parameters     : Fr_WakeupRxStatusPtr
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : None
**
** Global Variables Used : Fr_59_Renesas_GpCtrlRegSet,
**                         Fr_59_Renesas_GpControllerConfigPtr
**
** Functions Invoked     : FR_59_RENESAS_DEM_REPORT_ERROR,
**                         FR_59_RENESAS_ENTER_CRITICAL_SECTION,
**                         FR_59_RENESAS_EXIT_CRITICAL_SECTION
**
** Registers Used        : FLXAnFRSIR
**
** Reference ID          : FR_DUD_ACT_078, FR_DUD_ACT_078_CRT003,
** Reference ID          : FR_DUD_ACT_078_CRT004, FR_DUD_ACT_078_ERR001,
** Reference ID          : FR_DUD_ACT_078_REG001
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PRIVATE_CODE)
                             Fr_59_Renesas_UpdateWakeupRxSts(const uint8 Fr_CtrlIdx, uint8 *const Fr_WakeupRxStatusPtr) 
{
  /* Declare pointer to register */
  P2CONST(volatile Fr_59_Renesas_RegisterSetType, AUTOMATIC, FR_CONFIG_DATA) LpCtrlRegSet;
  P2VAR(volatile Fr_59_Renesas_InterruptRegType, AUTOMATIC, REGSPACE) LpIntReg;
  /* Declare local pointer to CC configuration */
  P2CONST(Fr_59_Renesas_CtrlTableType, TYPEDEF, FR_CONFIG_DATA) LpCtrlTable;
  /* Declare local pointer to Dem Event Id */
  P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF, FR_CONFIG_DATA) LpDemEventId;
  /* Declare the variable to store register value */
  uint32 LulFLX0SIR;
  /* Declare the variable to store return value */
  Std_ReturnType LucReturnValue;
  volatile uint16 LusLoopCount;
  /* Initialize the register value */
  LulFLX0SIR = FR_59_RENESAS_ZERO;                                                                                      /* PRQA S 2982 # JV-01 */
  /* Initialize the return value */
  LucReturnValue = E_OK;
  /* Copy global pointer to local pointer */
  LpCtrlRegSet = Fr_59_Renesas_GpCtrlRegSet[Fr_CtrlIdx];                                                                
  LpIntReg = LpCtrlRegSet->pIntReg;                                                                                    
  LpCtrlTable = (P2CONST(Fr_59_Renesas_CtrlTableType, AUTOMATIC,
                                          FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pCtrlTable);
  /* Read the status interrupt register */
  LulFLX0SIR = LpIntReg->ulFLXAnFRSIR;                                                                                 
  *Fr_WakeupRxStatusPtr = FR_59_RENESAS_ZERO;                                                                           
  /* Check if wakeup pattern was received on channel A */
  if (FR_59_RENESAS_FLX0SIR_FLX0WUPA_MASK == (LulFLX0SIR & FR_59_RENESAS_FLX0SIR_FLX0WUPA_MASK))
  {
    *Fr_WakeupRxStatusPtr = (uint8)FR_59_RENESAS_ONE;
  } /* else No Action required */
  /* Check if wakeup pattern was received on channel B */
  if (FR_59_RENESAS_FLX0SIR_FLX0WUPB_MASK == (LulFLX0SIR & FR_59_RENESAS_FLX0SIR_FLX0WUPB_MASK))
  {
    *Fr_WakeupRxStatusPtr = *Fr_WakeupRxStatusPtr | (uint8)FR_59_RENESAS_TWO;
  } /* else No Action required */
  LusLoopCount = FR_59_RENESAS_ZERO;
  do
  {
    /* Check if critical section protection is required */
    #if (FR_59_RENESAS_CRITICAL_SECTION_PROTECTION == STD_ON)
    /* Enter the Critical Section Area */
    FR_59_RENESAS_ENTER_CRITICAL_SECTION(FR_INTERRUPT_CONTROL_PROTECTION);
    #endif
    /* Reset the WUP by writing a one to the corresponding bit position */
    /* Writing in to FlexRay Status Interrupt Register and mirror address */
    LpIntReg->ulFLXAnFRSIR = FR_59_RENESAS_FLX0SIR_FLX0WUP_RESET;
    /* Read the status interrupt register */
    LulFLX0SIR = LpIntReg->ulFLXAnFRSIR;
    /* Check if critical section protection is required */
    #if (FR_59_RENESAS_CRITICAL_SECTION_PROTECTION == STD_ON)
    /* Exit the Critical Section Area */
    FR_59_RENESAS_EXIT_CRITICAL_SECTION(FR_INTERRUPT_CONTROL_PROTECTION);
    #endif
    if (LusLoopCount == (uint16)(LpCtrlTable->usFlagClearMaxWait))                                                      /* PRQA S 3416 # JV-01 */
    {
      LpDemEventId = (P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF,
                                         FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pDemEventId);
      if (FR_59_RENESAS_DEM_NOT_CONFIGURED != LpDemEventId->usReadTimeoutFailure)                                       
      {
        FR_59_RENESAS_DEM_REPORT_ERROR(LpDemEventId->usReadTimeoutFailure, DEM_EVENT_STATUS_FAILED);
      } /* else No Action required */
      LucReturnValue = E_NOT_OK;
    } /* else No Action required */
    LusLoopCount++;                                                                                                     /* PRQA S 3387, 3383 # JV-01, JV-01 */
  } while (((uint32)FR_59_RENESAS_ZERO != (LulFLX0SIR & FR_59_RENESAS_FLX0SIR_FLX0WUP_RESET)) &&
           (E_OK == LucReturnValue));
  return (LucReturnValue);
} /* End of function Fr_59_Renesas_UpdateWakeupRxSts */
#define FR_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_UpdateWriteDataSection
**
** Service ID            : Not Applicable
**
** Description           : This function loads the value into FlexRay write data
**                         section register
**
** Sync/Async            : Asynchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx, RegMacro, Data
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : None
**
** Preconditions         : None
**
** Global Variables Used : Fr_59_Renesas_GpCtrlRegSet
**
** Functions Invoked     : None.
**
** Registers Used        : FLXAnFRWRDSi (x = 1 to 64)
**
** Reference ID          : FR_DUD_ACT_079, FR_DUD_ACT_079_REG001,
** Reference ID          : FR_DUD_ACT_079_REG002, FR_DUD_ACT_079_REG003,
** Reference ID          : FR_DUD_ACT_079_REG004, FR_DUD_ACT_079_REG005,
** Reference ID          : FR_DUD_ACT_079_REG006, FR_DUD_ACT_079_REG007,
** Reference ID          : FR_DUD_ACT_079_REG008, FR_DUD_ACT_079_REG009,
** Reference ID          : FR_DUD_ACT_079_REG010, FR_DUD_ACT_079_REG011,
** Reference ID          : FR_DUD_ACT_079_REG012, FR_DUD_ACT_079_REG013,
** Reference ID          : FR_DUD_ACT_079_REG014, FR_DUD_ACT_079_REG015,
** Reference ID          : FR_DUD_ACT_079_REG016, FR_DUD_ACT_079_REG017,
** Reference ID          : FR_DUD_ACT_079_REG018, FR_DUD_ACT_079_REG019,
** Reference ID          : FR_DUD_ACT_079_REG020, FR_DUD_ACT_079_REG021,
** Reference ID          : FR_DUD_ACT_079_REG022, FR_DUD_ACT_079_REG023,
** Reference ID          : FR_DUD_ACT_079_REG024, FR_DUD_ACT_079_REG025,
** Reference ID          : FR_DUD_ACT_079_REG026, FR_DUD_ACT_079_REG027,
** Reference ID          : FR_DUD_ACT_079_REG028, FR_DUD_ACT_079_REG029,
** Reference ID          : FR_DUD_ACT_079_REG030, FR_DUD_ACT_079_REG031,
** Reference ID          : FR_DUD_ACT_079_REG032, FR_DUD_ACT_079_REG033,
** Reference ID          : FR_DUD_ACT_079_REG034, FR_DUD_ACT_079_REG035,
** Reference ID          : FR_DUD_ACT_079_REG036, FR_DUD_ACT_079_REG037,
** Reference ID          : FR_DUD_ACT_079_REG038, FR_DUD_ACT_079_REG039,
** Reference ID          : FR_DUD_ACT_079_REG040, FR_DUD_ACT_079_REG041,
** Reference ID          : FR_DUD_ACT_079_REG042, FR_DUD_ACT_079_REG043,
** Reference ID          : FR_DUD_ACT_079_REG044, FR_DUD_ACT_079_REG045,
** Reference ID          : FR_DUD_ACT_079_REG046, FR_DUD_ACT_079_REG047,
** Reference ID          : FR_DUD_ACT_079_REG048, FR_DUD_ACT_079_REG049,
** Reference ID          : FR_DUD_ACT_079_REG050, FR_DUD_ACT_079_REG051,
** Reference ID          : FR_DUD_ACT_079_REG052, FR_DUD_ACT_079_REG053,
** Reference ID          : FR_DUD_ACT_079_REG054, FR_DUD_ACT_079_REG055,
** Reference ID          : FR_DUD_ACT_079_REG056, FR_DUD_ACT_079_REG057,
** Reference ID          : FR_DUD_ACT_079_REG058, FR_DUD_ACT_079_REG059,
** Reference ID          : FR_DUD_ACT_079_REG060, FR_DUD_ACT_079_REG061,
** Reference ID          : FR_DUD_ACT_079_REG062, FR_DUD_ACT_079_REG063,
** Reference ID          : FR_DUD_ACT_079_REG064
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(void, FR_PRIVATE_CODE)
                 Fr_59_Renesas_UpdateWriteDataSection(const uint8 Fr_CtrlIdx, const uint32 RegMacro, const uint32 Data) /* PRQA S 1505 # JV-01 */
{
  /* Declare pointer to register */
  P2CONST(volatile Fr_59_Renesas_RegisterSetType, AUTOMATIC, FR_CONFIG_DATA) LpCtrlRegSet;
  P2VAR(volatile Fr_59_Renesas_InputBufferRegType, AUTOMATIC, REGSPACE) LpInputBuffReg;                                
  /* Copy global pointer to local pointer */
  LpCtrlRegSet = Fr_59_Renesas_GpCtrlRegSet[Fr_CtrlIdx];                                                                
  LpInputBuffReg = LpCtrlRegSet->pInputBuffReg;                                                                        
  /* Load value into FLXAnFRWRDSi register */
  *((volatile uint32 *)LpInputBuffReg + (uint32)((RegMacro - FR_59_RENESAS_FLX0WRDS1)/FR_59_RENESAS_FOUR)) = Data;      /* PRQA S 0310, 0488, 3383 # JV-01, JV-01, JV-02 */

} /* End of function Fr_59_Renesas_UpdateWriteDataSection */
#define FR_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_UpdateInputBuffer
**
** Service ID            : Not Applicable
**
** Description           : This function updates value to write data section
**                         registers and update LPdu status
**
** Sync/Async            : Asynchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx, Fr_LSduLength, Fr_LSduPtr
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : None
**
** Preconditions         : None
**
** Global Variables Used : None
**
** Functions Invoked     : Fr_59_Renesas_UpdateWriteDataSection,
**                         FR_59_RENESAS_ENTER_CRITICAL_SECTION,
**                         FR_59_RENESAS_EXIT_CRITICAL_SECTION
**
** Registers Used        : FLXAnFRWRDSi (x = 1 to 64)
**
** Reference ID          : FR_DUD_ACT_080, FR_DUD_ACT_080_CRT001,
** Reference ID          : FR_DUD_ACT_080_CRT002, FR_DUD_ACT_080_CRT003,
** Reference ID          : FR_DUD_ACT_080_CRT004
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(void, FR_PRIVATE_CODE)
            Fr_59_Renesas_UpdateInputBuffer(const uint8 Fr_CtrlIdx, const uint8 Fr_LSduLength, const uint8 *Fr_LSduPtr)
{
  uint32 LulDataAddress;
  uint8 LucShiftValue;
  volatile uint8 LucLoopCount;
  uint32 LulData;
  LucShiftValue = FR_59_RENESAS_ZERO;
  LulData = FR_59_RENESAS_ZERO;
  LucLoopCount = FR_59_RENESAS_ZERO;
  /* Load data from CPU RAM into Input Buffer */
  LulDataAddress = FR_59_RENESAS_FLX0WRDS1;
  /* Loop through the LSduLength and load the data in input buffer*/
  do
  {
    /* Load the data from LsduPtr to LulData */
    LulData = LulData | (((uint32)(*Fr_LSduPtr)) << ((uint32)LucShiftValue << FR_59_RENESAS_THREE));                    
    /* Get the next data */
    Fr_LSduPtr++;                                                                                                       /* PRQA S 1338 # JV-01 */
    /* Increment the variable for shifting the data value */
    LucShiftValue++;                                                                                                    /* PRQA S 3383 # JV-01 */
    /* Check whether 32-value is ready to load in the input buffer*/
    if (LucShiftValue > FR_59_RENESAS_THREE)
    {
      /* Check if critical section protection is required */
      #if (FR_59_RENESAS_CRITICAL_SECTION_PROTECTION == STD_ON)
      /* Enter the Critical Section Area */
      FR_59_RENESAS_ENTER_CRITICAL_SECTION(FR_INTERRUPT_CONTROL_PROTECTION);
      #endif
      Fr_59_Renesas_UpdateWriteDataSection(Fr_CtrlIdx, LulDataAddress, LulData);
      /* Check if critical section protection is required */
      #if (FR_59_RENESAS_CRITICAL_SECTION_PROTECTION == STD_ON)
      /* Exit the Critical Section Area */
      FR_59_RENESAS_EXIT_CRITICAL_SECTION(FR_INTERRUPT_CONTROL_PROTECTION);
      #endif
      /* Reset the shift and data values */
      LucShiftValue = FR_59_RENESAS_ZERO;
      LulData = FR_59_RENESAS_ZERO;
      /* Increment the input buffer register address */
      LulDataAddress = LulDataAddress + (uint32)FR_59_RENESAS_FOUR;                                                     /* PRQA S 3383 # JV-01 */
    } /* else No Action required */
    /* Increment the number of bytes processed */
    LucLoopCount++;                                                                                                     /* PRQA S 3387, 3383 # JV-01, JV-01 */
  } while (LucLoopCount < Fr_LSduLength);                                                                               /* PRQA S 3416 # JV-01 */
  /*
   * Check and load the input buffer when LSduLength is not multiple
   * of word length.
   */
  if (LucShiftValue > FR_59_RENESAS_ZERO)
  {
    /* Check if critical section protection is required */
    #if (FR_59_RENESAS_CRITICAL_SECTION_PROTECTION == STD_ON)
    /* Enter the Critical Section Area */
    FR_59_RENESAS_ENTER_CRITICAL_SECTION(FR_INTERRUPT_CONTROL_PROTECTION);
    #endif
    Fr_59_Renesas_UpdateWriteDataSection(Fr_CtrlIdx, LulDataAddress, LulData);
    /* Check if critical section protection is required */
    #if (FR_59_RENESAS_CRITICAL_SECTION_PROTECTION == STD_ON)
    /* Exit the Critical Section Area */
    FR_59_RENESAS_EXIT_CRITICAL_SECTION(FR_INTERRUPT_CONTROL_PROTECTION);
    #endif
  } /* else No Action required */
} /* End of function Fr_59_Renesas_UpdateInputBuffer */
#define FR_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_UpdateChannelEvenList
**
** Service ID            : Not Applicable
**
** Description           : This function reads value from FlexRay even sync id
**                         register
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx, RegMacro
**
** InOut Parameters      : None
**
** Output Parameters     : Fr_ChannelAEvenListPtr, Fr_ChannelBEvenListPtr
**
** Return Parameter      : None
**
** Preconditions         : None
**
** Global Variables Used : Fr_59_Renesas_GpCtrlRegSet
**
** Functions Invoked     : None.
**
** Registers Used        : FLXAnFRESIDi (i = 1 to 15)
**
** Reference ID          : FR_DUD_ACT_081
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(void, FR_PRIVATE_CODE)
Fr_59_Renesas_UpdateChannelEvenList(const uint8 Fr_CtrlIdx, const uint32 RegMacro,                                      /* PRQA S 1505 # JV-01 */
                                             uint16 *const Fr_ChannelAEvenListPtr,uint16 *const Fr_ChannelBEvenListPtr)
{
  /* Declare pointer to register */
  P2CONST(volatile Fr_59_Renesas_RegisterSetType, AUTOMATIC, FR_CONFIG_DATA) LpCtrlRegSet;
  P2VAR(volatile Fr_59_Renesas_CCStatusRegType, AUTOMATIC, REGSPACE) LpCCStatusReg;                                     /* PRQA S 3678 # JV-01 */
  /* Declare variable to store framelist */
  uint32 LulFrameList;
  /* Declare the variable to store Receive Sync Flag */
  uint8 LucRxSyncFlag;
  /* Initialize the frame list */
  LulFrameList = FR_59_RENESAS_ZERO;
  /* Copy global pointer to local pointer */
  LpCtrlRegSet = Fr_59_Renesas_GpCtrlRegSet[Fr_CtrlIdx];                                                                
  LpCCStatusReg = LpCtrlRegSet->pCCStatusReg;                                                                          
  switch (RegMacro)
  {
  case FR_59_RENESAS_FLX0ESID1:
    /* Read the Even Sync ID register */
    LulFrameList = LpCCStatusReg->ulFLXAnFRESID1;                                                                      
    break;
  case FR_59_RENESAS_FLX0ESID2:
    /* Read the Even Sync ID register */
    LulFrameList = LpCCStatusReg->ulFLXAnFRESID2;
    break;
  case FR_59_RENESAS_FLX0ESID3:
    /* Read the Even Sync ID register */
    LulFrameList = LpCCStatusReg->ulFLXAnFRESID3;
    break;
  case FR_59_RENESAS_FLX0ESID4:
    /* Read the Even Sync ID register */
    LulFrameList = LpCCStatusReg->ulFLXAnFRESID4;
    break;
  case FR_59_RENESAS_FLX0ESID5:
    /* Read the Even Sync ID register */
    LulFrameList = LpCCStatusReg->ulFLXAnFRESID5;
    break;
  case FR_59_RENESAS_FLX0ESID6:
    /* Read the Even Sync ID register */
    LulFrameList = LpCCStatusReg->ulFLXAnFRESID6;
    break;
  case FR_59_RENESAS_FLX0ESID7:
    /* Read the Even Sync ID register */
    LulFrameList = LpCCStatusReg->ulFLXAnFRESID7;
    break;
  case FR_59_RENESAS_FLX0ESID8:
    /* Read the Even Sync ID register */
    LulFrameList = LpCCStatusReg->ulFLXAnFRESID8;
    break;
  case FR_59_RENESAS_FLX0ESID9:
    /* Read the Even Sync ID register */
    LulFrameList = LpCCStatusReg->ulFLXAnFRESID9;
    break;
  case FR_59_RENESAS_FLX0ESID10:
    /* Read the Even Sync ID register */
    LulFrameList = LpCCStatusReg->ulFLXAnFRESID10;
    break;
  case FR_59_RENESAS_FLX0ESID11:
    /* Read the Even Sync ID register */
    LulFrameList = LpCCStatusReg->ulFLXAnFRESID11;
    break;
  case FR_59_RENESAS_FLX0ESID12:
    /* Read the Even Sync ID register */
    LulFrameList = LpCCStatusReg->ulFLXAnFRESID12;
    break;
  case FR_59_RENESAS_FLX0ESID13:
    /* Read the Even Sync ID register */
    LulFrameList = LpCCStatusReg->ulFLXAnFRESID13;
    break;
  case FR_59_RENESAS_FLX0ESID14:
    /* Read the Even Sync ID register */
    LulFrameList = LpCCStatusReg->ulFLXAnFRESID14;
    break;
  case FR_59_RENESAS_FLX0ESID15:
    /* Read the Even Sync ID register */
    LulFrameList = LpCCStatusReg->ulFLXAnFRESID15;
    break;
  default:
    /* No action required */
    break;
  }
  LucRxSyncFlag = (uint8)((LulFrameList & FR_59_RENESAS_FLX0ESID_FLX0RXEA_FLX0RXEB_MASK) >> FR_59_RENESAS_FOURTEEN);
  *Fr_ChannelAEvenListPtr = FR_59_RENESAS_ZERO;                                                                       
  *Fr_ChannelBEvenListPtr = FR_59_RENESAS_ZERO;                                                                    
  /* Received on both Channels AB */
  if (FR_59_RENESAS_THREE == LucRxSyncFlag)
  {
    *Fr_ChannelAEvenListPtr = (uint16)(LulFrameList & FR_59_RENESAS_FLX0ESID_FLX0EID_MASK);
    *Fr_ChannelBEvenListPtr = (uint16)(LulFrameList & FR_59_RENESAS_FLX0ESID_FLX0EID_MASK);
  }
  else if (FR_59_RENESAS_ONE == LucRxSyncFlag)
  {
    *Fr_ChannelAEvenListPtr = (uint16)(LulFrameList & FR_59_RENESAS_FLX0ESID_FLX0EID_MASK);
  }
  else if (FR_59_RENESAS_TWO == LucRxSyncFlag)                                                                          /* PRQA S 2004 # JV-01 */
  {
    *Fr_ChannelBEvenListPtr = (uint16)(LulFrameList & FR_59_RENESAS_FLX0ESID_FLX0EID_MASK);
  } /* else No Action required */
} /* End of function Fr_59_Renesas_UpdateChannelEvenList */
#define FR_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_UpdateChannelOddList
**
** Service ID            : Not Applicable
**
** Description           : This function reads the value from FlexRay odd sync
**                         ID register m
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx, RegAdd
**
** InOut Parameters      : None
**
** Output Parameters     : Fr_ChannelAOddListPtr, Fr_ChannelBOddListPtr
**
** Return Parameter      : None
**
** Preconditions         : None
**
** Global Variables Used : Fr_59_Renesas_GpCtrlRegSet
**
** Functions Invoked     : None.
**
** Registers Used        : FLXAnFROSIDi (i = 1 to 15)
**
** Reference ID          : FR_DUD_ACT_082
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(void, FR_PRIVATE_CODE)
Fr_59_Renesas_UpdateChannelOddList(const uint8 Fr_CtrlIdx, const uint32 RegAdd, uint16 *const Fr_ChannelAOddListPtr,    /* PRQA S 1505 # JV-01 */
                                                                                   uint16 *const Fr_ChannelBOddListPtr)
{
  /* Declare pointer to register */
  P2CONST(volatile Fr_59_Renesas_RegisterSetType, AUTOMATIC, FR_CONFIG_DATA) LpCtrlRegSet;
  P2VAR(volatile Fr_59_Renesas_CCStatusRegType, AUTOMATIC, REGSPACE) LpCCStatusReg;                                     /* PRQA S 3678 # JV-01 */
  /* Declare variable to store framelist */
  uint32 LulFrameList;
  uint8 LucRxSyncFlag;
  /* Initialize the frame list */
  LulFrameList = FR_59_RENESAS_ZERO;
  /* Copy global pointer to local pointer */
  LpCtrlRegSet = Fr_59_Renesas_GpCtrlRegSet[Fr_CtrlIdx];                                                           
  LpCCStatusReg = LpCtrlRegSet->pCCStatusReg;                                                                         
  switch (RegAdd)
  {
  case FR_59_RENESAS_FLX0OSID1:
    /* Read the Odd Sync ID register */
    LulFrameList = LpCCStatusReg->ulFLXAnFROSID1;                                                                       
    break;
  case FR_59_RENESAS_FLX0OSID2:
    /* Read the Odd Sync ID register */
    LulFrameList = LpCCStatusReg->ulFLXAnFROSID2;
    break;
  case FR_59_RENESAS_FLX0OSID3:
    /* Read the Odd Sync ID register */
    LulFrameList = LpCCStatusReg->ulFLXAnFROSID3;
    break;
  case FR_59_RENESAS_FLX0OSID4:
    /* Read the Odd Sync ID register */
    LulFrameList = LpCCStatusReg->ulFLXAnFROSID4;
    break;
  case FR_59_RENESAS_FLX0OSID5:
    /* Read the Odd Sync ID register */
    LulFrameList = LpCCStatusReg->ulFLXAnFROSID5;
    break;
  case FR_59_RENESAS_FLX0OSID6:
    /* Read the Odd Sync ID register */
    LulFrameList = LpCCStatusReg->ulFLXAnFROSID6;
    break;
  case FR_59_RENESAS_FLX0OSID7:
    /* Read the Odd Sync ID register */
    LulFrameList = LpCCStatusReg->ulFLXAnFROSID7;
    break;
  case FR_59_RENESAS_FLX0OSID8:
    /* Read the Odd Sync ID register */
    LulFrameList = LpCCStatusReg->ulFLXAnFROSID8;
    break;
  case FR_59_RENESAS_FLX0OSID9:
    /* Read the Odd Sync ID register */
    LulFrameList = LpCCStatusReg->ulFLXAnFROSID9;
    break;
  case FR_59_RENESAS_FLX0OSID10:
    /* Read the Odd Sync ID register */
    LulFrameList = LpCCStatusReg->ulFLXAnFROSID10;
    break;
  case FR_59_RENESAS_FLX0OSID11:
    /* Read the Odd Sync ID register */
    LulFrameList = LpCCStatusReg->ulFLXAnFROSID11;
    break;
  case FR_59_RENESAS_FLX0OSID12:
    /* Read the Odd Sync ID register */
    LulFrameList = LpCCStatusReg->ulFLXAnFROSID12;
    break;
  case FR_59_RENESAS_FLX0OSID13:
    /* Read the Odd Sync ID register */
    LulFrameList = LpCCStatusReg->ulFLXAnFROSID13;
    break;
  case FR_59_RENESAS_FLX0OSID14:
    /* Read the Odd Sync ID register */
    LulFrameList = LpCCStatusReg->ulFLXAnFROSID14;
    break;
  case FR_59_RENESAS_FLX0OSID15:
    /* Read the Odd Sync ID register */
    LulFrameList = LpCCStatusReg->ulFLXAnFROSID15;
    break;
  default:
    /* No action required */
    break;
  }
  LucRxSyncFlag = (uint8)((LulFrameList & FR_59_RENESAS_FLX0ESID_FLX0RXEA_FLX0RXEB_MASK) >> FR_59_RENESAS_FOURTEEN);

  *Fr_ChannelAOddListPtr = FR_59_RENESAS_ZERO;                                                                     
  *Fr_ChannelBOddListPtr = FR_59_RENESAS_ZERO;                                                                     
  /* Received on both Channels AB */
  if (FR_59_RENESAS_THREE == LucRxSyncFlag)
  {
    *Fr_ChannelAOddListPtr = (uint16)(LulFrameList & FR_59_RENESAS_FLX0OSID_FLX0OID_MASK);
    *Fr_ChannelBOddListPtr = (uint16)(LulFrameList & FR_59_RENESAS_FLX0OSID_FLX0OID_MASK);
  }
  else if (FR_59_RENESAS_ONE == LucRxSyncFlag)
  {
    *Fr_ChannelAOddListPtr = (uint16)(LulFrameList & FR_59_RENESAS_FLX0OSID_FLX0OID_MASK);
  }
  else if (FR_59_RENESAS_TWO == LucRxSyncFlag)                                                                          /* PRQA S 2004 # JV-01 */
  {
    *Fr_ChannelBOddListPtr = (uint16)(LulFrameList & FR_59_RENESAS_FLX0OSID_FLX0OID_MASK);
  } /* else No Action required */
} /* End of Fr_59_Renesas_UpdateChannelOddList */
#define FR_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_UpdateSyncFrameList
**
** Service ID            : Not Applicable
**
** Description           : This function reads value from FlexRay aggregated
**                         channel status register
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx
**
** InOut Parameters      : Fr_ChannelAEvenListPtr, Fr_ChannelBEvenListPtr,
**                         Fr_ChannelAOddListPtr, Fr_ChannelBOddListPtr
**
** Output Parameters     : None
**
** Return Parameter      : None
**
** Preconditions         : None
**
** Global Variables Used : None
**
** Functions Invoked     : Fr_59_Renesas_UpdateChannelEvenList,
**                         Fr_59_Renesas_UpdateChannelOddList
**
** Registers Used        : FLXAnFROSIDi (i = 1 to 15), FLXAnFRESIDi (i = 1 to 15)
**
** Reference ID          : FR_DUD_ACT_083
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(void, FR_PRIVATE_CODE)
Fr_59_Renesas_UpdateSyncFrameList(const uint8 Fr_CtrlIdx, const uint8 Fr_ListSize, uint16 *Fr_ChannelAEvenListPtr,    
                          uint16 *Fr_ChannelBEvenListPtr, uint16 *Fr_ChannelAOddListPtr, uint16 *Fr_ChannelBOddListPtr)
{
  uint8 LucListCnt;
  uint32 LulStrtRegAddr;
  LulStrtRegAddr = FR_59_RENESAS_FLX0ESID1;
  LucListCnt = FR_59_RENESAS_ZERO;
  do
  {
    /* Update the Channel Even List pointer */
    Fr_59_Renesas_UpdateChannelEvenList(Fr_CtrlIdx, LulStrtRegAddr, Fr_ChannelAEvenListPtr, Fr_ChannelBEvenListPtr);
    LucListCnt++;                                                                                                       /* PRQA S 3383 # JV-01 */
    Fr_ChannelAEvenListPtr++;                                                                                           /* PRQA S 1338 # JV-01 */
    Fr_ChannelBEvenListPtr++;                                                                                           /* PRQA S 1338 # JV-01 */
    LulStrtRegAddr += (uint32)FR_59_RENESAS_FOUR;                                                                       /* PRQA S 3383 # JV-01 */
  } while (LucListCnt < Fr_ListSize);
  LulStrtRegAddr = FR_59_RENESAS_FLX0OSID1;
  LucListCnt = FR_59_RENESAS_ZERO;
  do
  {
    /* Update Channel Odd list pointer */
    Fr_59_Renesas_UpdateChannelOddList(Fr_CtrlIdx, LulStrtRegAddr, Fr_ChannelAOddListPtr, Fr_ChannelBOddListPtr);
    LucListCnt++;                                                                                                       /* PRQA S 3383 # JV-01 */
    Fr_ChannelAOddListPtr++;                                                                                            /* PRQA S 1338 # JV-01 */
    Fr_ChannelBOddListPtr++;                                                                                            /* PRQA S 1338 # JV-01 */
    LulStrtRegAddr += (uint32)FR_59_RENESAS_FOUR;                                                                       /* PRQA S 3383 # JV-01 */
  } while (LucListCnt < Fr_ListSize);
} /* End of function Fr_59_Renesas_UpdateSyncFrameList */
#define FR_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_ReadAggregatedStatus
**
** Service ID            : Not Applicable
**
** Description           : This function reads value from FlexRay aggregated
**                         channel status register
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx,
**
** InOut Parameters      : Fr_ChannelAStatusPtr, Fr_ChannelBStatusPtr
**
** Output Parameters     : None
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : None
**
** Global Variables Used : Fr_59_Renesas_GpControllerConfigPtr,
**                         Fr_59_Renesas_GpCtrlRegSet
**
** Functions Invoked     : FR_59_RENESAS_DEM_REPORT_ERROR,
**                         Fr_59_Renesas_GetPOCStsFlag
**
** Registers Used        : FLXAnFRACS, FLXAnFRSWNIT
**
** Reference ID          : FR_DUD_ACT_084, FR_DUD_ACT_084_ERR001,
** Reference ID          : FR_DUD_ACT_084_REG001
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PRIVATE_CODE)
Fr_59_Renesas_ReadAggregatedStatus(const uint8 Fr_CtrlIdx, uint16 *const Fr_ChannelAStatusPtr,                       
                                                                                    uint16 *const Fr_ChannelBStatusPtr)
{
  /* Declare pointer to register */
  P2CONST(volatile Fr_59_Renesas_RegisterSetType, AUTOMATIC, FR_CONFIG_DATA) LpCtrlRegSet;
  P2VAR(volatile Fr_59_Renesas_CCStatusRegType, AUTOMATIC, REGSPACE) LpCCStatusReg;
  /* Declare local pointer to Dem Event Id */
  P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF, FR_CONFIG_DATA) LpDemEventId;
  /* Declare the variable to store the value of register */
  uint32 LulRegData;
  uint32 LulMTSVal;
  Std_ReturnType LucReturnValue;
  /* Initialize the value of register */
  LulRegData = FR_59_RENESAS_ZERO;                                                                                      /* PRQA S 2982 # JV-01 */
  /* Initialize the return value */
  LucReturnValue = E_OK;
  /* Copy global pointer to local pointer */
  LpCtrlRegSet = Fr_59_Renesas_GpCtrlRegSet[Fr_CtrlIdx];                                                               
  LpCCStatusReg = LpCtrlRegSet->pCCStatusReg;                                                                          
  /* Read the POC State by getting FLX0CCSV register value */
  LulRegData = Fr_59_Renesas_GetPOCStsFlag(Fr_CtrlIdx);
  /* Check if the CC is in normal active state */
  if ((FR_59_RENESAS_NORMAL_ACTIVE_STATE == LulRegData) || (FR_59_RENESAS_NORMAL_PASSIVE_STATE == LulRegData))
  {
    /* Read the Aggregated channel status register */
    LulRegData = LpCCStatusReg->ulFLXAnFRACS;                                                                       
    /* Copy 1st 4 bits of FLX0ACS to Output pointer VFRA, SEDA, CEDA, CIA, SBVA of Channel A */
    *Fr_ChannelAStatusPtr = (uint16)(LulRegData & FR_59_RENESAS_FLX0ACS_CHNL_A_MASK);                                 
    /* Copy 1st 4 bits of FLX0ACS to Output pointer VFRB, SEDB, CEDB, CIB, SBVB of Channel B */
    LulRegData = LulRegData >> FR_59_RENESAS_EIGHT;
    *Fr_ChannelBStatusPtr = (uint16)(LulRegData & FR_59_RENESAS_FLX0ACS_CHNL_B_MASK);                                
    /* Write '1' in all bit of the register to reset the aggregated channel status information */
    /* Writing in to FlexRay Aggregated Channel Status Register and mirror address */
    LpCCStatusReg->ulFLXAnFRACS = FR_59_RENESAS_FLX0ACS_MASK;
    /* Read the Symbol Window and NIT status register */
    LulRegData = LpCCStatusReg->ulFLXAnFRSWNIT;
    /* Extract MTS A from register FLX0SWNIT */
    LulMTSVal = LulRegData & FR_59_RENESAS_FLX0SWNIT_MTSA_MASK;
    /* Load MTS A in bit 8 of Fr_ChannelAStatusPtr */
    *Fr_ChannelAStatusPtr = *Fr_ChannelAStatusPtr | (uint16)(LulMTSVal << FR_59_RENESAS_TWO);

    /* Extract MTS B from register FLX0SWNIT */
    LulMTSVal = LulRegData & FR_59_RENESAS_FLX0SWNIT_MTSB_MASK;
    /* Load MTS B in bit 8 of Fr_ChannelBStatusPtr */
    *Fr_ChannelBStatusPtr = *Fr_ChannelBStatusPtr | (uint16)(LulMTSVal << FR_59_RENESAS_ONE);

    /* Extract SWNIT.SESA, SWNIT.SBSA, SWNIT.TCSA */
    LulMTSVal = LulRegData & FR_59_RENESAS_FLX0SWNIT_SW_A_MASK;
    /* From bit 0 (SESA) in SWNIT, left shift 9 bit to fill bit 9 in
     Fr_ChannelAStatusPtr */
    LulMTSVal = LulMTSVal << FR_59_RENESAS_NINE;
    /* Load SWNIT.SESA, SWNIT.SBSA, SWNIT.TCSA in bits 9, 10 and 11 of Fr_ChannelAStatusPtr */
    *Fr_ChannelAStatusPtr = *Fr_ChannelAStatusPtr | (uint16)LulMTSVal;
    /* Extract SWNIT.SESB, SWNIT.SBSB, SWNIT.TCSB */
    LulMTSVal = LulRegData & FR_59_RENESAS_FLX0SWNIT_SW_B_MASK;
    /* From bit 3 (SESA) in SWNIT, left shift 6 bit to fill from bit 9 in
     Fr_ChannelBStatusPtr */
    LulMTSVal = LulMTSVal << FR_59_RENESAS_SIX;
    /* Load SWNIT.SESB, SWNIT.SBSB, SWNIT.TCSB in bits 9, 10 and 11 of Fr_ChannelBStatusPtr */
    *Fr_ChannelBStatusPtr = *Fr_ChannelBStatusPtr | (uint16)LulMTSVal;
    /* Extract SWNIT.SENA, SWNIT.SBNA */
    LulMTSVal = LulRegData & FR_59_RENESAS_FLX0SWNIT_NIT_A_MASK;
    /* From bit 8 (SENA) in SWNIT, left shift 4 bit to fill from bit 12 in
     Fr_ChannelBStatusPtr */
    LulMTSVal = LulMTSVal << FR_59_RENESAS_FOUR;
    /* Load SWNIT.SENA, SWNIT.SBNA in bits 12, 13 of Fr_ChannelAStatusPtr */
    *Fr_ChannelAStatusPtr = *Fr_ChannelAStatusPtr | (uint16)LulMTSVal;
    /* Extract SWNIT.SENB, SWNIT.SBNB */
    LulMTSVal = LulRegData & FR_59_RENESAS_FLX0SWNIT_NIT_B_MASK;
    /* From bit 10 (SENB) in SWNIT, left shift 2 bit to fill from bit 12 in
     Fr_ChannelBStatusPtr */
    LulMTSVal = LulMTSVal << FR_59_RENESAS_TWO;
    /* Load SWNIT.SENB, SWNIT.SBNB in bits 12, 13 of Fr_ChannelBStatusPtr */
    *Fr_ChannelBStatusPtr = *Fr_ChannelBStatusPtr | (uint16)LulMTSVal;
  }
  else
  {
    /* Report Error to DEM */
    LpDemEventId = (P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF,
                                         FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pDemEventId);
    if (FR_59_RENESAS_DEM_NOT_CONFIGURED != LpDemEventId->usHardwareTestFailure)                                       
    {
      FR_59_RENESAS_DEM_REPORT_ERROR(LpDemEventId->usHardwareTestFailure, DEM_EVENT_STATUS_FAILED);
    } /* else No Action required */
    /* Set Return Value as E_NOT_OK */
    LucReturnValue = E_NOT_OK;
  }
  return (LucReturnValue);
} /* End of function Fr_59_Renesas_ReadAggregatedStatus */
#define FR_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_NetworkManagement
**
** Service ID            : Not Applicable
**
** Description           : This function reads value from FlexRay NEM
**                         Configuration Register
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx
**
**
** InOut Parameters      : None
**
** Output Parameters     : Fr_NmVectorPtr
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : None
**
** Global Variables Used : Fr_59_Renesas_GpCtrlRegSet,
**                         Fr_59_Renesas_GpControllerConfigPtr
**
** Functions Invoked     : FR_59_RENESAS_DEM_REPORT_ERROR
**
** Registers Used        : FLXAnFRNEMC, FLXAnFRNMV1, FLXAnFRNMV2, FLXAnFRNMV3
**
** Reference ID          : FR_DUD_ACT_085, FR_DUD_ACT_085_ERR001
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PRIVATE_CODE) Fr_59_Renesas_NetworkManagement(const uint8 Fr_CtrlIdx, uint8 *Fr_NmVectorPtr)
{
  /* Declare pointer to register */
  P2CONST(volatile Fr_59_Renesas_RegisterSetType, AUTOMATIC, FR_CONFIG_DATA) LpCtrlRegSet;
  P2VAR(volatile Fr_59_Renesas_CCStatusRegType, AUTOMATIC, REGSPACE) LpCCStatusReg;                                     /* PRQA S 3678 # JV-01 */
  P2VAR(volatile Fr_59_Renesas_CCControlRegType, AUTOMATIC, REGSPACE) LpCCCtrlReg;                                      /* PRQA S 3678 # JV-01 */
  /* Declare local pointer to Dem Event Id */
  P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF, FR_CONFIG_DATA) LpDemEventId;
  Std_ReturnType LucReturnValue;
  uint32 LulFrNEMCValue;
  uint32 LulFrNmvData1;
  uint32 LulFrNmvData2;
  uint32 LulFrNmvData3;
  /* Declare the variable */
  volatile uint8 LucLoopCount;
  /* Initialize the NEM value */
  LulFrNmvData1 = FR_59_RENESAS_ZERO;                                                                                   /* PRQA S 2982 # JV-01 */
  LulFrNmvData2 = FR_59_RENESAS_ZERO;
  LulFrNmvData3 = FR_59_RENESAS_ZERO;
  LucReturnValue = E_OK;
  /* Copy global pointer to local pointer */
  LpCtrlRegSet = Fr_59_Renesas_GpCtrlRegSet[Fr_CtrlIdx];                                                       
  LpCCCtrlReg = LpCtrlRegSet->pCCCtrlReg;                                                                            
  LpCCStatusReg = LpCtrlRegSet->pCCStatusReg;
  /* Read the value of the NEMC register */
  LulFrNEMCValue = LpCCCtrlReg->ulFLXAnFRNEMC;                                                                         
  /* Check if NEMC value is greater than configured NmVLength */
  if (LulFrNEMCValue > (uint32)FR_59_RENESAS_FLX0NEMC_MAX)
  {
    LpDemEventId = (P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF,
                                         FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pDemEventId);
    if (FR_59_RENESAS_DEM_NOT_CONFIGURED != LpDemEventId->usHardwareTestFailure)                                       
    {
      FR_59_RENESAS_DEM_REPORT_ERROR(LpDemEventId->usHardwareTestFailure, DEM_EVENT_STATUS_FAILED);
    } /* else No Action required */
    LucReturnValue = E_NOT_OK;
  }
  else if ((uint32)FR_59_RENESAS_ZERO == (uint32)LulFrNEMCValue)
  {
    *Fr_NmVectorPtr = FR_59_RENESAS_ZERO;                                                                            
  }
  else
  {
    /* Read Nm Data from FLX0NMV1 */
    LulFrNmvData1 = LpCCStatusReg->ulFLXAnFRNMV1;                                                                   
    if (LulFrNEMCValue > (uint32)FR_59_RENESAS_FOUR)
    {
      /* Read Nm Data from FLX0NMV2 */
      LulFrNmvData2 = LpCCStatusReg->ulFLXAnFRNMV2;
      if (LulFrNEMCValue > (uint32)FR_59_RENESAS_EIGHT)
      {
        /* Read Nm Data from FLX0NMV3 */
        LulFrNmvData3 = LpCCStatusReg->ulFLXAnFRNMV3;
      } /* else No Action required */
    } /* else No Action required */
    LucLoopCount = FR_59_RENESAS_ZERO;
    do
    {
      if (FR_59_RENESAS_THREE >= LucLoopCount)                                                                          /* PRQA S 3416 # JV-01 */
      {
        *(Fr_NmVectorPtr) = (uint8)(LulFrNmvData1 >> (LucLoopCount * FR_59_RENESAS_EIGHT));                             /* PRQA S 3384 # JV-01 */
      }
      else if (FR_59_RENESAS_SEVEN >= LucLoopCount)                                                                     /* PRQA S 3416 # JV-01 */
      {
        *(Fr_NmVectorPtr) = (uint8)(LulFrNmvData2 >> ((LucLoopCount - FR_59_RENESAS_FOUR) * FR_59_RENESAS_EIGHT));      /* PRQA S 3384 # JV-02 */
      }
      else /* LucLoopCount : 8 - 11 */
      {
        *(Fr_NmVectorPtr) = (uint8)(LulFrNmvData3 >> ((LucLoopCount - FR_59_RENESAS_EIGHT) * FR_59_RENESAS_EIGHT));     /* PRQA S 3384 # JV-02 */
      }
      /* Increment counter */
      LucLoopCount++;                                                                                                   /* PRQA S 3387, 3383 # JV-01, JV-01 */
      /* Increment pointer to access the next data */
      Fr_NmVectorPtr++;                                                                                                 /* PRQA S 1338 # JV-01 */
    } while ((FR_59_RENESAS_FLX0NEMC_MAX - FR_59_RENESAS_ONE) >= LucLoopCount);                                         /* PRQA S 3416 # JV-01 */
  }
  return (LucReturnValue);
} /* End of function Fr_59_Renesas_NetworkManagement */
#define FR_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_UpdateNumOfStartupFrame
**
** Service ID            : Not Applicable
**
** Description           : This function updated the number of startup frame.
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx
**
** InOut Parameters      : None
**
** Output Parameters     : Fr_NumOfStartupFramesPtr
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : None
**
** Global Variables Used : Fr_59_Renesas_GpControllerConfigPtr
**
** Functions Invoked     : FR_59_RENESAS_DEM_REPORT_ERROR,
**                         Fr_59_Renesas_GetPOCStsFlag
**
** Registers Used        : None
**
** Reference ID          : FR_DUD_ACT_086, FR_DUD_ACT_086_ERR001
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PRIVATE_CODE)
                   Fr_59_Renesas_UpdateNumOfStartupFrame(const uint8 Fr_CtrlIdx, uint8 *const Fr_NumOfStartupFramesPtr) 
{
  /* Declare local pointer to Dem Event Id */
  P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF, FR_CONFIG_DATA) LpDemEventId;
  /* Declare the variable to store return value */
  Std_ReturnType LucReturnValue;
  /* Declare the variable to store the FLX0ACS register value */
  uint32 LulRegData;
  /* Initialize the return value */
  LucReturnValue = E_OK;
  /* Read the POC State by getting FLX0CCSV register value */
  LulRegData = Fr_59_Renesas_GetPOCStsFlag(Fr_CtrlIdx);
  /* Check if the CC is in normal active state */
  if ((FR_59_RENESAS_NORMAL_ACTIVE_STATE == LulRegData) || (FR_59_RENESAS_NORMAL_PASSIVE_STATE == LulRegData))
  {
    *Fr_NumOfStartupFramesPtr = FR_59_RENESAS_TWO;                                                                     
  }
  else
  {
    /* Report Error to DEM */
    LpDemEventId = (P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF,
                                         FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pDemEventId);
    if (FR_59_RENESAS_DEM_NOT_CONFIGURED != LpDemEventId->usHardwareTestFailure)                                        
    {
      FR_59_RENESAS_DEM_REPORT_ERROR(LpDemEventId->usHardwareTestFailure, DEM_EVENT_STATUS_FAILED);
    } /* else No Action required */
    /* Set Return Value as E_NOT_OK */
    LucReturnValue = E_NOT_OK;
  }
  return (LucReturnValue);
} /* End of function Fr_59_Renesas_UpdateNumOfStartupFrame */
#define FR_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_GetCycleCounter
**
** Service ID            : Not Applicable
**
** Description           : This function gets Cycle Counter from
**                         FlexRay Macrotick and Cycle Counter Value Register
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx,
**
** InOut Parameters      : None
**
** Output Parameters     : Fr_CyclePtr, Fr_MacroTickPtr
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : None
**
** Global Variables Used : Fr_59_Renesas_GpControllerConfigPtr,
**                         Fr_59_Renesas_GpCtrlRegSet
**
** Functions Invoked     : FR_59_RENESAS_DEM_REPORT_ERROR,
**                         Fr_59_Renesas_GetPOCStsFlag
**
** Registers Used        : FLXAnFRMTCCV
**
** Reference ID          : FR_DUD_ACT_087, FR_DUD_ACT_087_ERR001
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PRIVATE_CODE)
Fr_59_Renesas_GetCycleCounter(const uint8 Fr_CtrlIdx, uint8 *const Fr_CyclePtr, uint16 *const Fr_MacroTickPtr)         
{
  /* Declare pointer to register */
  P2CONST(volatile Fr_59_Renesas_RegisterSetType, AUTOMATIC, FR_CONFIG_DATA) LpCtrlRegSet;
  P2VAR(volatile Fr_59_Renesas_CCStatusRegType, AUTOMATIC, REGSPACE) LpCCStatusReg;                                     /* PRQA S 3678 # JV-01 */
  /* Declare local pointer to Dem Event Id */
  P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF, FR_CONFIG_DATA) LpDemEventId;
  /* Declare the variable to store return value */
  Std_ReturnType LucReturnValue;
  uint32 LulRegData;
  /* Initialize the return value */
  LucReturnValue = E_OK;
  /* Copy global pointer to local pointer */
  LpCtrlRegSet = Fr_59_Renesas_GpCtrlRegSet[Fr_CtrlIdx];                                                                
  LpCCStatusReg = LpCtrlRegSet->pCCStatusReg;                                                                          
  /* Read the POC State by getting FLX0CCSV register value */
  LulRegData = Fr_59_Renesas_GetPOCStsFlag(Fr_CtrlIdx);
  /* Check if the CC is in normal active state */
  if ((FR_59_RENESAS_NORMAL_ACTIVE_STATE == LulRegData) || (FR_59_RENESAS_NORMAL_PASSIVE_STATE == LulRegData))
  {
    /* Read the value of the MTCCV register */
    LulRegData = LpCCStatusReg->ulFLXAnFRMTCCV;                                                                        
    /* Update the output parameter Fr_CyclePtr with the current cycle count of CC */
    *Fr_CyclePtr =                                                                                                     
        (uint8)((LulRegData & FR_59_RENESAS_FLX0MTCCV_FLX0CCV_MASK) >> FR_59_RENESAS_FLX0MTCCV_FLX0CCV_SHIFT);
    /* Update the Output parameter Fr_MacroTickPtr with the current macrotick value of CC */
    *Fr_MacroTickPtr = (uint16)(LulRegData & FR_59_RENESAS_FLX0MTCCV_FLX0MTV_MASK);                                     
  }
  else
  {
    /* Raise DEM Error FAILED */
    LpDemEventId = (P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF,
                                         FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pDemEventId);
    if (FR_59_RENESAS_DEM_NOT_CONFIGURED != LpDemEventId->usHardwareTestFailure)                                        
    {
      FR_59_RENESAS_DEM_REPORT_ERROR(LpDemEventId->usHardwareTestFailure, DEM_EVENT_STATUS_FAILED);
    } /* else No Action required */
    /* Set Return Value as E_NOT_OK */
    LucReturnValue = E_NOT_OK;
  }
  return (LucReturnValue);
} /* End of function Fr_59_Renesas_GetCycleCounter */
#define FR_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_ResetWriteHeader
**
** Service ID            : Not Applicable
**
** Description           : This function resets FlexRay Write Header Section
**                         Register
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx, Fr_LPduIdx
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : None
**
** Global Variables Used : Fr_59_Renesas_GpCtrlRegSet,
**                         Fr_59_Renesas_GpControllerConfigPtr,
**                         Fr_59_Renesas_GpBufReconfigStatusPtr
**
** Functions Invoked     : FR_59_RENESAS_DEM_REPORT_ERROR
**
** Registers Used        : FLXAnFRIBCM, FLXAnFRIBCR, FLXAnFRWRHS1
**
** Reference ID          : FR_DUD_ACT_088, FR_DUD_ACT_088_ERR001,
** Reference ID          : FR_DUD_ACT_088_GBL001, FR_DUD_ACT_088_REG001,
** Reference ID          : FR_DUD_ACT_088_REG002, FR_DUD_ACT_088_REG003
***********************************************************************************************************************/
#if (FR_59_RENESAS_DISABLE_LPDU == STD_ON)
#define FR_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PRIVATE_CODE)
Fr_59_Renesas_ResetWriteHeader(const uint8 Fr_CtrlIdx, const uint16 Fr_LPduIdx)                                       
{
  /* Declare pointer to register */
  P2CONST(volatile Fr_59_Renesas_RegisterSetType, AUTOMATIC, FR_CONFIG_DATA) LpCtrlRegSet;
  P2VAR(volatile Fr_59_Renesas_InputBufferRegType, AUTOMATIC, REGSPACE) LpInputBuffReg;
  /* Declare local pointer to CC configuration */
  P2CONST(Fr_59_Renesas_CtrlTableType, TYPEDEF, FR_CONFIG_DATA) LpCtrlTable;
  P2CONST(Fr_59_Renesas_FrameHeaderType, AUTOMATIC, FR_APPL_CONST) LpBufferHeader;
  P2CONST(Fr_59_Renesas_FrameHeaderType, TYPEDEF, FR_CONFIG_DATA) LpFrameConfig;
  P2VAR(uint16, AUTOMATIC, FR_APPL_DATA) LpBufReconfigStatusPtr;                                                        /* PRQA S 3432 # JV-01 */
  /* Declare local pointer to Dem Event Id */
  P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF, FR_CONFIG_DATA)
  LpDemEventId;
  /* Declare the variable to store register value */
  uint32 LulRegData;
  /* Declare the variable for timeout checking */
  volatile uint16 LusLoopCount;
  /* Declare the variable to store the return value */
  Std_ReturnType LucReturnValue;
  /* Initialize the return value */
  LucReturnValue = E_OK;
  /* Copy global pointer to local pointer */
  LpCtrlRegSet = Fr_59_Renesas_GpCtrlRegSet[Fr_CtrlIdx];                                                              
  LpInputBuffReg = LpCtrlRegSet->pInputBuffReg;                                                                        
  LpCtrlTable = (P2CONST(Fr_59_Renesas_CtrlTableType, AUTOMATIC,
                                          FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pCtrlTable);
  LpFrameConfig = Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pFrameConfig;
  LpBufferHeader = &LpFrameConfig[Fr_LPduIdx];                                                                        
  LpBufReconfigStatusPtr = Fr_59_Renesas_GpBufReconfigStatusPtr[Fr_CtrlIdx];                                            
  /* Write zero to register FRWRHS1 since rest of the fields are irrelevant. */
  LpInputBuffReg->ulFLXAnFRWRHS1 = FR_59_RENESAS_ZERO;                                                                 
  /* Initialize the loop count */
  LusLoopCount = FR_59_RENESAS_ZERO;
  while ((FR_59_RENESAS_FLX0IBCR_FLX0IBSYH_MASK ==                                                                     
          (LpInputBuffReg->ulFLXAnFRIBCR & FR_59_RENESAS_FLX0IBCR_FLX0IBSYH_MASK)) &&
                                                            (LusLoopCount < (uint16)(LpCtrlTable->usFlagClearMaxWait))) /* PRQA S 3415, 3416 # JV-01, JV-01 */
  {
    /* Increment the loop count */
    LusLoopCount++;                                                                                                     /* PRQA S 3383, 3387 # JV-01, JV-01 */
  }
  /* If the maximum wait time was expired */
  if (LusLoopCount == (uint16)(LpCtrlTable->usFlagClearMaxWait))                                                        /* PRQA S 3416 # JV-01 */
  {
    LpDemEventId = (P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF,
                                         FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pDemEventId);
    if (FR_59_RENESAS_DEM_NOT_CONFIGURED != LpDemEventId->usReadTimeoutFailure)                                         
    {
      FR_59_RENESAS_DEM_REPORT_ERROR(LpDemEventId->usReadTimeoutFailure, DEM_EVENT_STATUS_FAILED);
    } /* else No Action required */
    LucReturnValue = E_NOT_OK;
  }
  else
  {
    /* Write the value of the header in the register FRIBCM */
    /* Writing in to FlexRay Input Buffer Command Mask Register and mirror address */
    LpInputBuffReg->ulFLXAnFRIBCM = FR_59_RENESAS_FLX0IBCM_FLX0LHSH_MASK;
    /* Get the value of the message buffer configured and load the value in the FRIBCR register */
    LulRegData = ((LpBufferHeader->ucMsgBuffer) & FR_59_RENESAS_FLX0IBCR_FLX0IBRH_MASK);                               
    /* Write the value of the header in the register FRIBCR */
    /* Writing in to FlexRay Input Buffer Command Request Register and mirror address */
    LpInputBuffReg->ulFLXAnFRIBCR = LulRegData;
    /* Update the frame Id in the corresponding buffer reconfiguration status array to invalid LPdu index */
  LpBufReconfigStatusPtr[LpBufferHeader->ucMsgBuffer] = FR_59_RENESAS_INVALID_LPDUID;                                 
  }
  return (LucReturnValue);
} /* End of function Fr_59_Renesas_ResetWriteHeader */
#define FR_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
#endif
/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_UpdateDataTransferMode
**
** Service ID            : Not Applicable
**
** Description           : This function set transfer mode and data
**                         section by FlexRay Input Buffer Command Mask Register
**
** Sync/Async            : Asynchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx, LucMessageBuffer
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : Std_ReturnType
**
** Preconditions         : None
**
** Global Variables Used : Fr_59_Renesas_GpCtrlRegSet,
**                         Fr_59_Renesas_GpControllerConfigPtr
**
** Functions Invoked     : FR_59_RENESAS_ENTER_CRITICAL_SECTION,
**                         FR_59_RENESAS_EXIT_CRITICAL_SECTION
**
** Registers Used        : FLXAnFRIBCM, FLXAnFRIBCR
**
** Reference ID          : FR_DUD_ACT_089, FR_DUD_ACT_089_REG001,
** Reference ID          : FR_DUD_ACT_089_REG002, FR_DUD_ACT_089_ERR001
** Reference ID          : FR_DUD_ACT_089_CRT001,FR_DUD_ACT_089_CRT002
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PRIVATE_CODE)
                             Fr_59_Renesas_UpdateDataTransferMode(const uint8 Fr_CtrlIdx, const uint8 LucMessageBuffer) 
{
  /* Declare pointer to register */
  P2CONST(Fr_59_Renesas_CtrlTableType, AUTOMATIC, FR_CONFIG_DATA) LpCtrlTable;
  P2CONST(volatile Fr_59_Renesas_RegisterSetType, AUTOMATIC, FR_CONFIG_DATA) LpCtrlRegSet;
  P2VAR(volatile Fr_59_Renesas_InputBufferRegType, AUTOMATIC, REGSPACE) LpInputBuffReg;
  P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF, FR_CONFIG_DATA) LpDemEventId;
  /* Decalre the count variable */
  uint16 LusLoopCount;
  /* Declare return value */
  uint8 LucReturnValue;
  /* Copy global pointer to local pointer */
  LpCtrlRegSet = Fr_59_Renesas_GpCtrlRegSet[Fr_CtrlIdx];                                                    
  LpInputBuffReg = LpCtrlRegSet->pInputBuffReg;                                                                      
  LpCtrlTable = (P2CONST(Fr_59_Renesas_CtrlTableType, AUTOMATIC,
                                          FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pCtrlTable);
  /* Initialize the loop count to FR_59_RENESAS_ZERO */
  LusLoopCount = FR_59_RENESAS_ZERO;
  /* Initialize return value */
  LucReturnValue = E_OK;
  while ((FR_59_RENESAS_FLX0IBCR_FLX0IBSYH_MASK == (LpInputBuffReg->ulFLXAnFRIBCR                                      
               & FR_59_RENESAS_FLX0IBCR_FLX0IBSYH_MASK)) && (LusLoopCount < (uint16)(LpCtrlTable->usFlagClearMaxWait))) 
  {
    /* Increment the loop count */
    LusLoopCount++;
  }
  if (LusLoopCount == (uint16)(LpCtrlTable->usFlagClearMaxWait))
  {
    LpDemEventId = (P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF,
                                         FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pDemEventId);
    if (FR_59_RENESAS_DEM_NOT_CONFIGURED != LpDemEventId->usReadTimeoutFailure)                                         
    {
      /* Report DEM error */
      FR_59_RENESAS_DEM_REPORT_ERROR(LpDemEventId->usReadTimeoutFailure, DEM_EVENT_STATUS_FAILED);
      /* Set return value to E_OK */
      LucReturnValue = E_NOT_OK;
    } /* else No Action required */
  }
  else
  {
    /* Check if critical section protection is required */
    #if (FR_59_RENESAS_CRITICAL_SECTION_PROTECTION == STD_ON)
    /* Enter the Critical Section Area */
    FR_59_RENESAS_ENTER_CRITICAL_SECTION(FR_INTERRUPT_CONTROL_PROTECTION);
    #endif
    /* Select Load Data Mode */
    /* Writing in to FlexRay Input Buffer Command Mask Register and mirror address */
    LpInputBuffReg->ulFLXAnFRIBCM = (uint32)FR_59_RENESAS_FLX0IBCM_FLX0STXRH_FLX0LDSH;
    /* Select the Message Buffer for the data transfer */
    /* Writing in to FlexRay Input Buffer Command Request Register and mirror address */
    LpInputBuffReg->ulFLXAnFRIBCR = (uint32)LucMessageBuffer;
    #if (FR_59_RENESAS_CRITICAL_SECTION_PROTECTION == STD_ON)
    /* Exit the Critical Section Area */
    FR_59_RENESAS_EXIT_CRITICAL_SECTION(FR_INTERRUPT_CONTROL_PROTECTION);
    #endif
  }
  return LucReturnValue;
} /* End of function Fr_59_Renesas_UpdateDataTransferMode */
#define FR_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_UpdateLPduTxSts
**
** Service ID            : Not Applicable
**
** Description           : This function updates the status of transmission LPdu
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx, Fr_LPduIdx, LucMessageBuffer,
**
** InOut Parameters      : None
**
** Output Parameters     : Fr_TxLPduStatusPtr
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : None
**
** Global Variables Used : Fr_59_Renesas_GpCtrlRegSet,
**                         Fr_59_Renesas_GpControllerConfigPtr
**
** Functions Invoked     : Fr_59_Renesas_WriteOutputBufferCommand
**
** Registers Used        : FLXAnFRTXRQi(i = 1 to 4), FLXAnFRMBS
**
** Reference ID          : FR_DUD_ACT_090
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PRIVATE_CODE)
Fr_59_Renesas_UpdateLPduTxSts(const uint8 Fr_CtrlIdx, const uint16 Fr_LPduIdx, const uint8 LucMessageBuffer,           
                                                                         Fr_TxLPduStatusType *const Fr_TxLPduStatusPtr)
{
  /* Declare pointer to register */
  P2CONST(volatile Fr_59_Renesas_RegisterSetType, AUTOMATIC, FR_CONFIG_DATA) LpCtrlRegSet;
  P2VAR(volatile Fr_59_Renesas_MessageBufferStatusRegType, AUTOMATIC, REGSPACE) LpMBStatusReg;                          /* PRQA S 3678 # JV-01 */
  /* Declare the variable to store the address of Frame configuration */
  P2CONST(Fr_59_Renesas_FrameHeaderType, AUTOMATIC, FR_APPL_CONST) LpFrameConfigPtr;
  P2CONST(Fr_59_Renesas_FrameHeaderType, TYPEDEF, FR_CONFIG_DATA) LpFrameConfig;
  /* Declare the variable to store the value of FLXAnFRTXRQm register */
  uint32 LulTXRData;
  /* Declare return value */
  uint8 LucReturnValue;
  /* Message buffer register offset */
  uint8 LucMBRegNumber;
  uint32 LulMBBitMask;
  #if (FR_59_RENESAS_AR_VERSION == FR_59_RENESAS_AR_R22_11_VERSION)
  /* Pointer to Output buffer register */
  P2VAR(volatile Fr_59_Renesas_OutputBufferRegType, AUTOMATIC, REGSPACE) LpOutputBuffReg;                               /* PRQA S 3678 # JV-01 */
  /* Declare the variable to store the value of Channel */
  uint8 LucChannel;
  /* Declare the variable to store the value of Message buffer status */
  uint32 LulFLXAnFRMBSRegVal;
  #endif /* #if (FR_59_RENESAS_AR_VERSION == FR_59_RENESAS_AR_R22_11_VERSION) */

  /* Calculate the Message buffer register number and bit number */
  LucMBRegNumber = FR_59_RENESAS_REGNUMBER_OFFSET(LucMessageBuffer);
  LulMBBitMask = FR_59_RENESAS_BITNUMBER_MASK(LucMessageBuffer);                                                        /* PRQA S 3469 # JV-01 */
  /* Initial return value */
  LucReturnValue = E_OK;                                                                                                /* PRQA S 2982 # JV-01 */
  /* Copy global pointer to local pointer */
  LpCtrlRegSet = Fr_59_Renesas_GpCtrlRegSet[Fr_CtrlIdx];                                                               
  LpMBStatusReg = LpCtrlRegSet->pMBStatusReg;                                                                         
  /* Initialize the value of register */
  LulTXRData = (uint32)FR_59_RENESAS_ZERO;
  /* Initialize the value of pointer */
  LpFrameConfig = Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pFrameConfig;
  LpFrameConfigPtr = &LpFrameConfig[Fr_LPduIdx];                                                                     
  #if (FR_59_RENESAS_AR_VERSION == FR_59_RENESAS_AR_R22_11_VERSION)
  /* Copy global pointer to local pointer */
  LpOutputBuffReg = LpCtrlRegSet->pOutputBuffReg;
  /* Get channel value of target LPdu */
  LucChannel = LpFrameConfigPtr->ucChannelFilter;                                                                       
  /* Initial the value of Message buffer status */
  LulFLXAnFRMBSRegVal = (uint32)FR_59_RENESAS_ZERO;                                                                     /* PRQA S 2982 # JV-01 */
  #endif /* #if (FR_59_RENESAS_AR_VERSION == FR_59_RENESAS_AR_R22_11_VERSION) */
  switch (LucMBRegNumber)
  {
    /* Using FLXAnFRTXRQ1 */
  case FR_59_RENESAS_ZERO:
    LulTXRData = LpMBStatusReg->ulFLXAnFRTXRQ1;                                                                      
    break;
  /* Using FLXAnFRTXRQ2 */
  case FR_59_RENESAS_ONE:
    LulTXRData = LpMBStatusReg->ulFLXAnFRTXRQ2;
    break;
  /* Using FLXAnFRTXRQ2 */
  case FR_59_RENESAS_TWO:
    LulTXRData = LpMBStatusReg->ulFLXAnFRTXRQ3;
    break;
  /* Using FLXAnFRTXRQ3 */
  case FR_59_RENESAS_THREE:
    LulTXRData = LpMBStatusReg->ulFLXAnFRTXRQ4;
    break;
  default:
    /* No action required */
    break;
  }
  #if (FR_59_RENESAS_AR_VERSION == FR_59_RENESAS_AR_R22_11_VERSION)
  /* Read out the message header and status from Message RAM to Output buffer */
  LucReturnValue = Fr_59_Renesas_WriteOutputBufferCommand(Fr_CtrlIdx, Fr_LPduIdx);
  if (E_OK == LucReturnValue)
  {
    /* Read Message buffer status */
    LulFLXAnFRMBSRegVal = LpOutputBuffReg->ulFLXAnFRMBS;                                                              
  } /* else No Action required */
  /* Check the conflict transmission */
  if (E_OK == LucReturnValue)
  {
    if ((((LulFLXAnFRMBSRegVal & FR_59_RENESAS_FLX0FRMBS_TCIA_MASK) == FR_59_RENESAS_FLX0FRMBS_TCIA_MASK) &&
         (((uint8)FR_59_RENESAS_CHANNEL_A == LucChannel) || ((uint8)FR_59_RENESAS_CHANNEL_AB == LucChannel))) ||
               (((LulFLXAnFRMBSRegVal & FR_59_RENESAS_FLX0FRMBS_TCIB_MASK) == FR_59_RENESAS_FLX0FRMBS_TCIB_MASK) &&
                  (((uint8)FR_59_RENESAS_CHANNEL_B == LucChannel) || ((uint8)FR_59_RENESAS_CHANNEL_AB == LucChannel))))
    {
      /* Set the status to FR_TRANSMITTED_CONFLICT when conflict transmission exist */
      *Fr_TxLPduStatusPtr = FR_TRANSMITTED_CONFLICT;                                                                   
    }
    else if ((uint32)FR_59_RENESAS_ZERO == (LulTXRData & LulMBBitMask))
    #else
  /* Check TXR flag in register FLXAnFRMBSCi value */
  if ((uint32)FR_59_RENESAS_ZERO == (LulTXRData & LulMBBitMask))
  #endif /* #if (FR_59_RENESAS_AR_VERSION == FR_59_RENESAS_AR_R22_11_VERSION) */
    {
      /* Check whether the frame is configured for single shot */
      if (FR_59_RENESAS_TXM_SINGLESHOT == LpFrameConfigPtr->ucTransmissionMode)
      {
        *Fr_TxLPduStatusPtr = FR_TRANSMITTED;
      }
      else /* Continuous Mode */
      {
        *Fr_TxLPduStatusPtr = FR_NOT_TRANSMITTED;
      }
    }
    else /* Transmission request present */
    {
      /* Check whether the frame is configured for single shot */
      if (FR_59_RENESAS_TXM_SINGLESHOT == LpFrameConfigPtr->ucTransmissionMode)
      {
        *Fr_TxLPduStatusPtr = FR_NOT_TRANSMITTED;
      }
      else /* Continuous Mode */
      {
        *Fr_TxLPduStatusPtr = FR_TRANSMITTED;
      }
    }
  #if (FR_59_RENESAS_AR_VERSION == FR_59_RENESAS_AR_R22_11_VERSION)
  } /* else No Action required */
  #endif
  /* Return checking process is succeed or failed */
  return LucReturnValue;

} /* End of function Fr_59_Renesas_UpdateLPduTxSts */
#define FR_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_ClearTxReq
**
** Service ID            : Not Applicable
**
** Description           : This function clears transmission request.
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx, LucMessageBuffer
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : None
**
** Global Variables Used : Fr_59_Renesas_GpCtrlRegSet,
**                         Fr_59_Renesas_GpControllerConfigPtr
**
** Functions Invoked     : FR_59_RENESAS_DEM_REPORT_ERROR
**
** Registers Used        : FLXAnFRTXRQi(i = 1 to 4), FLXAnFRIBCM, FLXAnFRIBCR
**
** Reference ID          : FR_DUD_ACT_091, FR_DUD_ACT_091_REG001,
** Reference ID          : FR_DUD_ACT_091_REG002, FR_DUD_ACT_091_ERR001
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PRIVATE_CODE)
Fr_59_Renesas_ClearTxReq(const uint8 Fr_CtrlIdx, const uint8 LucMessageBuffer)                                        
{
  /* Declare pointer to controller config */
  P2CONST(Fr_59_Renesas_CtrlTableType, TYPEDEF, FR_CONFIG_DATA) LpCtrlTable;
  /* Declare pointer to register */
  P2VAR(volatile Fr_59_Renesas_InputBufferRegType, AUTOMATIC, REGSPACE) LpInputBuffReg;
  P2CONST(volatile Fr_59_Renesas_RegisterSetType, AUTOMATIC, FR_CONFIG_DATA) LpCtrlRegSet;
  P2VAR(volatile Fr_59_Renesas_MessageBufferStatusRegType, AUTOMATIC, REGSPACE) LpMBStatusReg;                          /* PRQA S 3678 # JV-01 */
  /* Declare local pointer to Dem Event Id */
  P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF, FR_CONFIG_DATA) LpDemEventId;
  /* Declare variable to store return value */
  Std_ReturnType LucReturnValue;
  /* Declare the variable to store the value of register */
  uint32 LulTXRData;
  /* Message buffer register offset */
  uint8 LucMBRegNumber;
  uint32 LulMBBitMask;
  /* Loop count variable */
  uint8 LucLoopCount;
  /* Initialize the return value */
  LucReturnValue = E_OK;
  /* Initialize the value of register */
  LulTXRData = FR_59_RENESAS_ZERO;
  /* Copy global pointer to local pointer */
  LpCtrlRegSet = Fr_59_Renesas_GpCtrlRegSet[Fr_CtrlIdx];                                                             
  LpMBStatusReg = LpCtrlRegSet->pMBStatusReg;                                                                          
  LpInputBuffReg = LpCtrlRegSet->pInputBuffReg;
  /* Get address of Transmission Requestregister corresponding with
   MessageBuffer */
  LucMBRegNumber = FR_59_RENESAS_REGNUMBER_OFFSET(LucMessageBuffer);
  LulMBBitMask = FR_59_RENESAS_BITNUMBER_MASK(LucMessageBuffer);                                                        /* PRQA S 3469 # JV-01 */
  switch (LucMBRegNumber)
  {
    /* Using FLXAnFRTXRQ1 */
  case FR_59_RENESAS_ZERO:
    LulTXRData = LpMBStatusReg->ulFLXAnFRTXRQ1;                                                                     
    break;
  /* Using FLXAnFRTXRQ2 */
  case FR_59_RENESAS_ONE:
    LulTXRData = LpMBStatusReg->ulFLXAnFRTXRQ2;
    break;
  /* Using FLXAnFRTXRQ2 */
  case FR_59_RENESAS_TWO:
    LulTXRData = LpMBStatusReg->ulFLXAnFRTXRQ3;
    break;
  /* Using FLXAnFRTXRQ3 */
  case FR_59_RENESAS_THREE:
    LulTXRData = LpMBStatusReg->ulFLXAnFRTXRQ4;
    break;
  default:
    /* No action required */
    break;
  }
  /* Check whether transmission request is present */
  if ((uint32)FR_59_RENESAS_ZERO == (LulTXRData & LulMBBitMask))
  {
    /* Transmission Completed, cancellation not possible */
    LucReturnValue = E_NOT_OK;
  }
  else /* Transmission request present */
  {
    LpCtrlTable = (P2CONST(Fr_59_Renesas_CtrlTableType, AUTOMATIC,
                                          FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pCtrlTable);
    /* Initialize the loop count to FR_59_RENESAS_ZERO */
    LucLoopCount = FR_59_RENESAS_ZERO;
    while ((FR_59_RENESAS_FLX0IBCR_FLX0IBSYH_MASK == (LpInputBuffReg->ulFLXAnFRIBCR                                    
                       & FR_59_RENESAS_FLX0IBCR_FLX0IBSYH_MASK)) && (LucLoopCount < (LpCtrlTable->usFlagClearMaxWait))) 
    {
      /* Increment the loop count */
      LucLoopCount++;
    }
    if (LucLoopCount == LpCtrlTable->usFlagClearMaxWait)
    {
      LpDemEventId = (P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF,
                                         FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pDemEventId);
      if (FR_59_RENESAS_DEM_NOT_CONFIGURED != LpDemEventId->usReadTimeoutFailure)                                      
      {
        /* Report DEM error */
        FR_59_RENESAS_DEM_REPORT_ERROR(LpDemEventId->usReadTimeoutFailure, DEM_EVENT_STATUS_FAILED);
        /* Set return value to E_NOT_OK */
        LucReturnValue = E_NOT_OK;
      } /* else No Action required */
    }
    else
    {
      /* Select Load Data Mode */
      /* Writing in to FlexRay Input Buffer Command Mask Register */
      LpInputBuffReg->ulFLXAnFRIBCM = (uint32)FR_59_RENESAS_FLX0IBCM_FLX0STXRH_CLEAR;
      /* Select the Message Buffer for the data transfer */
      /* Writing in to FlexRay Input Buffer Command Request Register */
      LpInputBuffReg->ulFLXAnFRIBCR = (uint32)LucMessageBuffer;
    }
  }
  return (LucReturnValue);

} /* End of function Fr_59_Renesas_ClearTxReq */
#define FR_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_MessageBufferStatus
**
** Service ID            : Not Applicable
**
** Description           : This function reads the status of Message buffer by
**                         FlexRay message buffer status register
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx, Fr_LPduIdx
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : None
**
** Global Variables Used : Fr_59_Renesas_GpCtrlRegSet,
**                         Fr_59_Renesas_GpControllerConfigPtr
**
** Functions Invoked     : FR_59_RENESAS_DEM_REPORT_ERROR
**
** Registers Used        : FLXAnFRMBS
**
** Reference ID          : FR_DUD_ACT_092, FR_DUD_ACT_092_ERR001,
** Reference ID          : FR_DUD_ACT_092_ERR002
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PRIVATE_CODE)
Fr_59_Renesas_MessageBufferStatus(const uint8 Fr_CtrlIdx, const uint16 Fr_LPduIdx)                                     
{
  /* Declare pointer to register */
  P2CONST(volatile Fr_59_Renesas_RegisterSetType, AUTOMATIC, FR_CONFIG_DATA) LpCtrlRegSet;
  P2VAR(volatile Fr_59_Renesas_OutputBufferRegType, AUTOMATIC, REGSPACE) LpOutputBuffReg;                               /* PRQA S 3678 # JV-01 */
  /* Declare local pointer to CC configuration */
  P2CONST(Fr_59_Renesas_FrameHeaderType, AUTOMATIC, FR_APPL_CONST) LpFrameConfigPtr;
  P2CONST(Fr_59_Renesas_FrameHeaderType, TYPEDEF, FR_CONFIG_DATA) LpFrameConfig;
  /* Declare the variable to store the return value */
  Std_ReturnType LucReturnValue;
  /* Declare the variable to store the slot status error flag */
  boolean LblSlotStatus;
  /* Declare the variable to store the Controller Channel */
  uint8 LucLPduChannel;
  /* Declare the variable to store the Slot Status Error value */
  uint32 LulSlotStatusError;
  LpFrameConfig = Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pFrameConfig;
  LpFrameConfigPtr = &LpFrameConfig[Fr_LPduIdx];                                                                      
  LblSlotStatus = FR_59_RENESAS_FALSE;
  LucReturnValue = E_OK;                                                                                                /* PRQA S 2982 # JV-01 */
  /* Read Controller Channel from Configuration */
  LucLPduChannel = LpFrameConfigPtr->ucChannelFilter;                                                                 
  /* Copy global pointer to local pointer */
  LpCtrlRegSet = Fr_59_Renesas_GpCtrlRegSet[Fr_CtrlIdx];                                                              
  LpOutputBuffReg = LpCtrlRegSet->pOutputBuffReg;                                                                     
  /* Read Slot Status Error Information from Register FLX0MBS */
  LulSlotStatusError = LpOutputBuffReg->ulFLXAnFRMBS;                                                                  
  /*
   * Check SEOA, SEOB, CEOA, CEOB, SVOA, SVOB bits in register FLXnMBS for
   * slots status error
   */
  if ((uint8)FR_59_RENESAS_CHANNEL_AB == LucLPduChannel)
  {
    LulSlotStatusError = LulSlotStatusError & FR_59_RENESAS_FLX0MBS_SLOT_ERROR_MASK;
    if ((uint32)FR_59_RENESAS_ZERO != LulSlotStatusError)
    {
      LblSlotStatus = FR_59_RENESAS_TRUE;
    } /* else No Action required */
  }
  /*
   * Check SEOA, CEOA, SVOA bits in register FLXnMBS for slots status error
   */
  else if ((uint8)FR_59_RENESAS_CHANNEL_A == LucLPduChannel)
  {
    LulSlotStatusError = LulSlotStatusError & FR_59_RENESAS_FLX0MBS_SEOA_CEOA_SVOA_MASK;
    if ((uint32)FR_59_RENESAS_ZERO != LulSlotStatusError)
    {
      LblSlotStatus = FR_59_RENESAS_TRUE;
    } /* else No Action required */
  }
  /*
   * Check SEOB, CEOB, SVOB bits in register FLXnMBS for slots status error
   */
  else /* FR_CHANNEL_B */
  {
    LulSlotStatusError = LulSlotStatusError & FR_59_RENESAS_FLX0MBS_SEOB_CEOB_SVOB_MASK;
    if ((uint32)FR_59_RENESAS_ZERO != LulSlotStatusError)
    {
      LblSlotStatus = FR_59_RENESAS_TRUE;
    } /* else No Action required */
  }
  /* No Slot Status Error */
  if (FR_59_RENESAS_FALSE == LblSlotStatus)
  {
    if (FR_59_RENESAS_TRUE == LpFrameConfigPtr->blIsFrIfDemFTSlotStatusConfig)
    {
      /* Report Error to DEM */
      FR_59_RENESAS_DEM_REPORT_ERROR(LpFrameConfigPtr->usFrIfDemFTSlotStatus, DEM_EVENT_STATUS_PASSED);
    } /* else No Action required */
    /* Set Return Value as E_OK */
    LucReturnValue = E_OK;
  }
  else
  {
    if (FR_59_RENESAS_TRUE == LpFrameConfigPtr->blIsFrIfDemFTSlotStatusConfig)
    {
      /* Report Error to DEM */
      FR_59_RENESAS_DEM_REPORT_ERROR(LpFrameConfigPtr->usFrIfDemFTSlotStatus, DEM_EVENT_STATUS_FAILED);
    } /* else No Action required */
    /* Set Return Value as E_NOT_OK */
    LucReturnValue = E_NOT_OK;
  }
  return (LucReturnValue);
} /* End of function Fr_59_Renesas_MessageBufferStatus */
#define FR_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_UpdateStsLength
**
** Service ID            : Not Applicable
**
** Description           : This function updates LPdu status and LSdu length
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx
**
** InOut Parameters      : None
**
** Output Parameters     : Fr_LPduStatusPtr, Fr_LSduLengthPtr
**
** Return Parameter      : None
**
** Preconditions         : None
**
** Global Variables Used : Fr_59_Renesas_GpCtrlRegSet
**
** Functions Invoked     : None.
**
** Registers Used        : FLXAnFRFSR
**
** Reference ID          : FR_DUD_ACT_093
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(void, FR_PRIVATE_CODE)
Fr_59_Renesas_UpdateStsLength(const uint8 Fr_CtrlIdx, Fr_RxLPduStatusType *const Fr_LPduStatusPtr,                     
                                                                                         uint8 *const Fr_LSduLengthPtr)
{
  /* Declare pointer to register */
  P2CONST(volatile Fr_59_Renesas_RegisterSetType, AUTOMATIC, FR_CONFIG_DATA) LpCtrlRegSet;
  P2VAR(volatile Fr_59_Renesas_MessageBufferStatusRegType, AUTOMATIC, REGSPACE) LpMBStatusReg;                          /* PRQA S 3678 # JV-01 */
  /* Declare variable to store register value */
  uint32 LulData;
  /* Initialize the register value */
  /* Copy global pointer to local pointer */
  LpCtrlRegSet = Fr_59_Renesas_GpCtrlRegSet[Fr_CtrlIdx];                                                               
  LpMBStatusReg = LpCtrlRegSet->pMBStatusReg;                                                                          
  LulData = LpMBStatusReg->ulFLXAnFRFSR;                                                                                
  LulData = LulData & FR_59_RENESAS_FLX0FSR_FLX0RFNE_MASK;
  if (FR_59_RENESAS_FLX0FSR_FLX0RFNE_MASK == LulData)
  {
    /* Update the status Ptr */
    *Fr_LPduStatusPtr = FR_RECEIVED;                                                                                   
  }
  else
  {
    /* Update the status Ptr and Sdu Length Ptr */
    *Fr_LPduStatusPtr = FR_NOT_RECEIVED;
    *Fr_LSduLengthPtr = FR_59_RENESAS_ZERO;                                                                            
  }
} /* End of Fr_59_Renesas_UpdateStsLength */
#define FR_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_NewData
**
** Service ID            : Not Applicable
**
** Description           : This function reads data from FlexRay New Data
**                         Register
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx, LucMessageBuffer
**
** InOut Parameters      : None
**
** Output Parameters     : Fr_LPduStatusPtr, Fr_LSduLengthPtr
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : None
**
** Global Variables Used : Fr_59_Renesas_GpCtrlRegSet
**
** Functions Invoked     : None
**
** Registers Used        : FLXAnFRNDATi(i = 1 to 4)
**
** Reference ID          : FR_DUD_ACT_094
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PRIVATE_CODE)
Fr_59_Renesas_NewData(const uint8 Fr_CtrlIdx, const uint8 LucMessageBuffer,                                             
                                             Fr_RxLPduStatusType *const Fr_LPduStatusPtr,uint8 *const Fr_LSduLengthPtr)
{
  /* Declare pointer to register */
  P2CONST(volatile Fr_59_Renesas_RegisterSetType, AUTOMATIC, FR_CONFIG_DATA) LpCtrlRegSet;
  P2VAR(volatile Fr_59_Renesas_MessageBufferStatusRegType, AUTOMATIC, REGSPACE) LpMBStatusReg;                          /* PRQA S 3678 # JV-01 */
  /* Declare variable to store return value */
  Std_ReturnType LucReturnValue;
  uint32 LulNDData;
  /* New Data register offset */
  uint8 LucNDRegNumber;
  uint32 LulNDBitMask;
  /* Initialize the return value */
  LucReturnValue = E_OK;
  /* Initialize the register value */
  LulNDData = FR_59_RENESAS_ZERO;
  /* Copy global pointer to local pointer */
  LpCtrlRegSet = Fr_59_Renesas_GpCtrlRegSet[Fr_CtrlIdx];                                                                
  LpMBStatusReg = LpCtrlRegSet->pMBStatusReg;                                                                          
  /* Get address of Transmission Requestregister corresponding with MessageBuffer */
  LucNDRegNumber = FR_59_RENESAS_REGNUMBER_OFFSET(LucMessageBuffer);
  LulNDBitMask = FR_59_RENESAS_BITNUMBER_MASK(LucMessageBuffer);                                                        /* PRQA S 3469 # JV-01 */
  switch (LucNDRegNumber)
  {
    /*Using FLXAnFRNDAT1 */
  case FR_59_RENESAS_ZERO:
    LulNDData = LpMBStatusReg->ulFLXAnFRNDAT1;                                                                          
    break;
    /*Using FLXAnFRNDAT2 */
  case FR_59_RENESAS_ONE:
    LulNDData = LpMBStatusReg->ulFLXAnFRNDAT2;
    break;
    /*Using FLXAnFRNDAT3 */
  case FR_59_RENESAS_TWO:
    LulNDData = LpMBStatusReg->ulFLXAnFRNDAT3;
    break;
    /*Using FLXAnFRNDAT4 */
  case FR_59_RENESAS_THREE:
    LulNDData = LpMBStatusReg->ulFLXAnFRNDAT4;
    break;
  default:
    /* No action required */
    break;
  }
  if (LulNDBitMask == (LulNDData & LulNDBitMask))
  {
    /* Update the status Ptr */
    *Fr_LPduStatusPtr = FR_RECEIVED;                                                                                    
  }
  else /* No new data received */
  {
    /* Update the return value to E_NOT_OK */
    LucReturnValue = E_NOT_OK;
    /* Update the status Ptr and Sdu Length Ptr */
    *Fr_LPduStatusPtr = FR_NOT_RECEIVED;
    *Fr_LSduLengthPtr = FR_59_RENESAS_ZERO;                                                                             
  }
  return (LucReturnValue);
} /* End of function Fr_59_Renesas_NewData */
#define FR_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_WriteOutputBufferCommand
**
** Service ID            : Not Applicable
**
** Description           : This function to request transfer header and data
**                         from Message RAM to Output buffer
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx, Fr_LPduIdx
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : None
**
** Global Variables Used : Fr_59_Renesas_GpCtrlRegSet,
**                         Fr_59_Renesas_GpControllerConfigPtr
**
** Functions Invoked     : FR_59_RENESAS_DEM_REPORT_ERROR,
**                         FR_59_RENESAS_ENTER_CRITICAL_SECTION, FR_59_RENESAS_EXIT_CRITICAL_SECTION
**
** Registers Used        : FLXAnFROBCR, FLXAnFROBCM
**
** Reference ID          : FR_DUD_ACT_095, FR_DUD_ACT_095_ERR001,
** Reference ID          : FR_DUD_ACT_095_REG001, FR_DUD_ACT_095_REG002,
** Reference ID          : FR_DUD_ACT_095_REG003, FR_DUD_ACT_095_REG004,
** Reference ID          : FR_DUD_ACT_095_REG005, FR_DUD_ACT_095_CRT001,
** Reference ID          : FR_DUD_ACT_095_CRT002
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PRIVATE_CODE)
Fr_59_Renesas_WriteOutputBufferCommand(const uint8 Fr_CtrlIdx, const uint16 Fr_LPduIdx)
{
  /* Declare pointer to register */
  P2CONST(volatile Fr_59_Renesas_RegisterSetType, AUTOMATIC, FR_CONFIG_DATA) LpCtrlRegSet;
  P2VAR(volatile Fr_59_Renesas_OutputBufferRegType, AUTOMATIC, REGSPACE) LpOutputBuffReg;
  /* Declare local pointer to CC configuration */
  P2CONST(Fr_59_Renesas_CtrlTableType, TYPEDEF, FR_CONFIG_DATA) LpCtrlTable;
  P2CONST(Fr_59_Renesas_FrameHeaderType, AUTOMATIC, FR_APPL_CONST) LpFrameConfigPtr;
  P2CONST(Fr_59_Renesas_FrameHeaderType, TYPEDEF, FR_CONFIG_DATA) LpFrameConfig;
  /* Declare local pointer to Dem Event Id */
  P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF, FR_CONFIG_DATA) LpDemEventId;
  uint32 LulData;
  volatile uint16 LusLoopCount;
  Std_ReturnType LucReturnValue;
  uint8 LucMessageBuffer;
  LulData = FR_59_RENESAS_ZERO;                                                                                         /* PRQA S 2982 # JV-01 */
  LucReturnValue = E_OK;
  /* Copy global pointer to local pointer */
  LpCtrlRegSet = Fr_59_Renesas_GpCtrlRegSet[Fr_CtrlIdx];                                                                
  LpOutputBuffReg = LpCtrlRegSet->pOutputBuffReg;                                                                       
  LpCtrlTable = (P2CONST(Fr_59_Renesas_CtrlTableType, AUTOMATIC,
                                          FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pCtrlTable);
  LpFrameConfig = Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pFrameConfig;
  LpDemEventId = (P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF,
                                         FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pDemEventId);
  LpFrameConfigPtr = &LpFrameConfig[Fr_LPduIdx];                                                                        

  /* Check if critical section protection is required */
  #if (FR_59_RENESAS_CRITICAL_SECTION_PROTECTION == STD_ON)
  /* Enter the Critical Section Area */
  FR_59_RENESAS_ENTER_CRITICAL_SECTION(FR_INTERRUPT_CONTROL_PROTECTION);
  #endif
  /* Selects Message Buffer to Shadow Buffer transfer */
  /* Writing in to FlexRay Output Buffer Command Mask Register and mirror address */
  LpOutputBuffReg->ulFLXAnFROBCM = FR_59_RENESAS_FLX0OBCM_READ_MASK;                                                    
  /* Wait if the Output Buffer is busy servicing the earlier request */
  LusLoopCount = FR_59_RENESAS_ZERO;
  while ((FR_59_RENESAS_FLX0FROBCR_FLX0_OBSYS_MASK ==                                                                  
                           (LpOutputBuffReg->ulFLXAnFROBCR & FR_59_RENESAS_FLX0FROBCR_FLX0_OBSYS_MASK)) &&
                                                            (LusLoopCount < (uint16)(LpCtrlTable->usFlagClearMaxWait))) /* PRQA S 3415, 3416 # JV-01, JV-01 */
  {
    /* Increment the loop count */
    LusLoopCount++;                                                                                                     /* PRQA S 3387, 3383 # JV-01, JV-01 */
    /* Check if the loop count value is equal to maximum wait time for the output buffer flag to get cleared */
    if (LusLoopCount == (uint16)(LpCtrlTable->usFlagClearMaxWait))                                                      /* PRQA S 3416 # JV-01 */
    {
      /* Update the return value to E_NOT_OK */
      LucReturnValue = E_NOT_OK;
    } /* else No Action required */
  }
  if (E_OK == LucReturnValue)
  {
    /* Read the Message Buffer configured to the frame */
    LucMessageBuffer = LpFrameConfigPtr->ucMsgBuffer;                                                                   
    /* Loads the value of message buffer to LulData */
    LulData = LucMessageBuffer | FR_59_RENESAS_FLX0OBCR_RAM_OBF;
    /*
     * if the number of the first message buffer of the receive FIFO is written to FLXnOBCR register the Message
     *Handler transfers the message buffer addressed by the GET Index Register (GIDX) to OBF Shadow.
     */
    /* Write the value to FlexRay Output Buffer Command Request Register
     and mirror address */
    LpOutputBuffReg->ulFLXAnFROBCR = LulData;
    /* Wait if the Output Buffer is busy servicing the earlier request*/
    LusLoopCount = FR_59_RENESAS_ZERO;
    while ((FR_59_RENESAS_FLX0FROBCR_FLX0_OBSYS_MASK ==                                                                 
                              (LpOutputBuffReg->ulFLXAnFROBCR & FR_59_RENESAS_FLX0FROBCR_FLX0_OBSYS_MASK)) &&
                                                            (LusLoopCount < (uint16)(LpCtrlTable->usFlagClearMaxWait))) /* PRQA S 3415, 3416 # JV-01, JV-01 */
    {
      /* Increment the loop count */
      LusLoopCount++;                                                                                                   /* PRQA S 3383, 3387 # JV-01, JV-01 */
      /* Check if the loop count value is equal to max wait time for the output buffer flag to get cleared */
      if (LusLoopCount == (uint16)(LpCtrlTable->usFlagClearMaxWait))                                                    /* PRQA S 3416 # JV-01 */
      {
        /* Update the return value to E_NOT_OK */
        LucReturnValue = E_NOT_OK;
      } /* else No Action required */
    }
    if (E_OK == LucReturnValue)
    {
      /* Toggle OBF Shadow and OBF Host by setting OBCR.VIEW = 1 */
      LulData = LpOutputBuffReg->ulFLXAnFROBCR;
      /* Reset REQ bit */
      LulData = LulData & FR_59_RENESAS_FLX0OBCR_RAM_OBF_RESET;
      /* Set VIEW bit to 1 */
      LulData = LulData | FR_59_RENESAS_FLX0OBCR_OBFS_OBFH;
      /* Writing in to FlexRay Input Buffer Command Request Register
       and mirror address */
      LpOutputBuffReg->ulFLXAnFROBCR = LulData;
      /* Completion of transfer from OBF Shadow and message RAM is noticed by setting OBSYS back to 0 */
      LusLoopCount = FR_59_RENESAS_ZERO;
      while ((FR_59_RENESAS_FLX0FROBCR_FLX0_OBSYS_MASK ==                                                               
                      (LpOutputBuffReg->ulFLXAnFROBCR & FR_59_RENESAS_FLX0FROBCR_FLX0_OBSYS_MASK)) &&
                                                            (LusLoopCount < (uint16)(LpCtrlTable->usFlagClearMaxWait))) /* PRQA S 3415, 3416 # JV-01, JV-01 */
      {
        /* Increment the loop count */
        LusLoopCount++;                                                                                                 /* PRQA S 3387, 3383 # JV-01, JV-01 */
        /* Check if the loop count value is equal to max wait time for the output buffer flag to get cleared */
        if (LusLoopCount == (uint16)(LpCtrlTable->usFlagClearMaxWait))                                                  /* PRQA S 3416 # JV-01 */
        {
          /* Update the return value to E_NOT_OK */
          LucReturnValue = E_NOT_OK;
        } /* else No Action required */
      }
    } /* else No Action required */
  } /* else No Action required */
  /* Check if critical section protection is required */
  #if (FR_59_RENESAS_CRITICAL_SECTION_PROTECTION == STD_ON)
  /* Enter the Critical Section Area */
  FR_59_RENESAS_EXIT_CRITICAL_SECTION(FR_INTERRUPT_CONTROL_PROTECTION);
  #endif
  /* Report to DEM */
  if ((FR_59_RENESAS_DEM_NOT_CONFIGURED != LpDemEventId->usReadTimeoutFailure) && (E_NOT_OK == LucReturnValue))         
  {
    FR_59_RENESAS_DEM_REPORT_ERROR(LpDemEventId->usReadTimeoutFailure, DEM_EVENT_STATUS_FAILED);
  } /* else No Action required */
  return (LucReturnValue);
} /* End of function Fr_59_Renesas_WriteOutputBufferCommand */
#define FR_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_ReadReceiveData
**
** Service ID            : Not Applicable
**
** Description           : This function reads the received data to Output
**                         pointer
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx, Fr_LPduIdx
**
** InOut Parameters      : None
**
** Output Parameters     : Fr_LSduPtr, Fr_LPduStatusPtr, Fr_LSduLengthPtr
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : None
**
** Global Variables Used : Fr_59_Renesas_GpCtrlRegSet,
**                         Fr_59_Renesas_GpControllerConfigPtr
**
** Functions Invoked     : Fr_59_Renesas_ReadDataSection,
**                         FR_59_RENESAS_DEM_REPORT_ERROR
**
** Registers Used        : FLXAnFRMBS, FLXAnFRRDHS2, FLXAnFRFSR
**
** Reference ID          : FR_DUD_ACT_096, FR_DUD_ACT_096_ERR001,
** Reference ID          : FR_DUD_ACT_096_ERR002
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PRIVATE_CODE)
          Fr_59_Renesas_ReadReceiveData(const uint8 Fr_CtrlIdx, const uint16 Fr_LPduIdx, uint8 *Fr_LSduPtr,          
                                            Fr_RxLPduStatusType *const Fr_LPduStatusPtr, uint8 *const Fr_LSduLengthPtr)
{
  /* Declare pointer to register */
  P2CONST(volatile Fr_59_Renesas_RegisterSetType, AUTOMATIC, FR_CONFIG_DATA) LpCtrlRegSet;
  P2VAR(volatile Fr_59_Renesas_OutputBufferRegType, AUTOMATIC, REGSPACE) LpOutputBuffReg;                               /* PRQA S 3678 # JV-01 */
  P2VAR(volatile Fr_59_Renesas_MessageBufferStatusRegType, AUTOMATIC, REGSPACE) LpMBStatusReg;                          /* PRQA S 3678 # JV-01 */
  P2CONST(Fr_59_Renesas_FrameHeaderType, AUTOMATIC, FR_APPL_CONST) LpFrameConfigPtr;
  P2CONST(Fr_59_Renesas_FrameHeaderType, TYPEDEF, FR_CONFIG_DATA) LpFrameConfig;
  uint32 LulData;
  volatile uint8 LucLoopCount;
  volatile uint8 LucIncrement;
  uint32 LulDataAddress;
  uint32 LulStatusFlags;
  uint32 LulValidFrameFlags;
  Std_ReturnType LucReturnValue;
  LucReturnValue = E_OK;
  /* Copy global pointer to local pointer */
  LpCtrlRegSet = Fr_59_Renesas_GpCtrlRegSet[Fr_CtrlIdx];                                                               
  LpOutputBuffReg = LpCtrlRegSet->pOutputBuffReg;                                                                      
  LpMBStatusReg = LpCtrlRegSet->pMBStatusReg;
  /* Read Slot Status Errors from register FLXnMBS */
  LulData = LpOutputBuffReg->ulFLXAnFRMBS;                                                                             
  LpFrameConfig = Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pFrameConfig;
  LpFrameConfigPtr = &LpFrameConfig[Fr_LPduIdx];                                                                        
  LulStatusFlags = FR_59_RENESAS_ZERO;                                                                                  /* PRQA S 2982 # JV-01 */
  if (FR_59_RENESAS_TRUE == LpFrameConfigPtr->blIsFrIfDemFTSlotStatusConfig)                                            
  {
    /* Check for slots status error */
    LulStatusFlags = (LulData & FR_59_RENESAS_FLX0MBS_SLOT_ERROR_MASK);
    LulStatusFlags = LulStatusFlags >> FR_59_RENESAS_TWO;
    if ((uint32)FR_59_RENESAS_ZERO < LulStatusFlags)
    {
      FR_59_RENESAS_DEM_REPORT_ERROR(LpFrameConfigPtr->usFrIfDemFTSlotStatus, DEM_EVENT_STATUS_FAILED);
    }
    else
    {
      FR_59_RENESAS_DEM_REPORT_ERROR(LpFrameConfigPtr->usFrIfDemFTSlotStatus, DEM_EVENT_STATUS_PASSED);
    }
  } /* else No Action required */
  /* Check for vSS!ValidFrame */
  LulValidFrameFlags = (LulData & FR_59_RENESAS_FLX0MBS_FLX0MBSVFR_MASK);
  #if (FR_59_RENESAS_RX_STRINGENT_CHECK == STD_ON)
  /* Check for slots status error */
  LulStatusFlags = (LulData & FR_59_RENESAS_FLX0MBS_SLOT_ERROR_MASK);
  #endif
  if (((uint32)FR_59_RENESAS_ZERO != LulStatusFlags) || ((uint32)FR_59_RENESAS_ZERO == LulValidFrameFlags))
  {
    *Fr_LPduStatusPtr = FR_NOT_RECEIVED;                                                                                
    *Fr_LSduLengthPtr = FR_59_RENESAS_ZERO;                                                                             
  } /* else No Action required */
  if (FR_RECEIVED == *Fr_LPduStatusPtr)
  {
    /* Copy the received data from OBF Host to Fr_LSduPtr */
    LulData = ((LpOutputBuffReg->ulFLXAnFRRDHS2) & FR_59_RENESAS_DATA_LENGTH_MASK) >> FR_59_RENESAS_DATA_LENGTH_SHIFT;
    /* Stringent length check */
    #if (FR_59_RENESAS_RX_STRINGENT_LENGTH_CHECK == STD_ON)
    if (LpFrameConfigPtr->ucPayloadLength != (uint8)LulData)
    {
      /* Update the return value to E_NOT_OK */
      LucReturnValue = E_NOT_OK;
      /* Update the status Ptr and Sdu Length Ptr */
      *Fr_LPduStatusPtr = FR_NOT_RECEIVED;
      *Fr_LSduLengthPtr = FR_59_RENESAS_ZERO;
    }
    else
    #endif
    {
      /* Copy the received data from OBF Host to Fr_LSduPtr */
      /* (*Fr_LSduLengthPtr) calculation is corrected by multiply with two */
      if (LulData <= LpFrameConfigPtr->ucPayloadLength)
      {
        *Fr_LSduLengthPtr = ((uint8)LulData * (uint8)FR_59_RENESAS_TWO);
      }
      else
      {
        *Fr_LSduLengthPtr = (LpFrameConfigPtr->ucPayloadLength * (uint8)FR_59_RENESAS_TWO);
      }
      /*  Host Buffer -> *FrLSduPtrPtr */
      /* FRRDDS1-64(0x0600-0x06FC) : Host Buffer*/
      /*                         -> Fr_LSduPtr  */
      /* (Mapping of FlexRayCC Register)        */
      /*      31     59     15     07    0      */
      /*      +------+------+------+-------+    */
      /*reg01:  Data4  Data3  Data2  Data1      */
      /*      +------+------+------+-------+    */
      /*reg02:  Data8  Data7  Data6  Data5      */
      /*      +------+------+------+-------+    */
      /* :                  :                   */
      /* :                  :                   */
      /*      +------+------+------+-------+    */
      /*reg63: Data252Data251Data250Data249     */
      /*      +------+------+------+-------+    */
      /*reg64:  -----  ----- Data254 Data253    */
      /*      +------+------+------+-------+    */
      /*                                        */
      /* (Mapping of LSduPtr)                   */
      /*        +0     +1     +2                */
      /*       +------+------+------+------     */
      /*LSduPtr:Data1  Data2  Data3       ---   */
      /*       +------+------+------+------     */
      /*                                        */
      /*       +251     +252     +253           */
      /*       ---------+--------+-------+      */
      /*   ---  Data252  Data253  Data254       */
      /*       ---------+--------+-------+      */
      /* Get the base address of the register FLX0RDDS1 */
      LulDataAddress = (uint32)FR_59_RENESAS_FLX0RDDS1;
      /* Update the value for loop count to FR_59_RENESAS_ONE */
      LucLoopCount = FR_59_RENESAS_ONE;
      /* Check if the loop count value is less than the value of Fr_LSduLengthPtr */
      while (LucLoopCount < (*Fr_LSduLengthPtr))                                                                        /* PRQA S 3416 # JV-01 */
      {
        /* Read the value of the data from the address LulDataAddress */
        LulData = Fr_59_Renesas_ReadDataSection(Fr_CtrlIdx, LulDataAddress);
        /* Update the data value in Fr_LSduPtr */
        *Fr_LSduPtr = (uint8)(LulData & FR_59_RENESAS_DATA_MASK);                                                       
        /* Increment the pointer address */
        Fr_LSduPtr++;                                                                                                   /* PRQA S 1338 # JV-01 */
        /* Shift the data value by 8, mask and update the data value in Fr_LSduPtr */
        *Fr_LSduPtr = (uint8)((LulData >> FR_59_RENESAS_DATA_BYTE2_SHIFT) & FR_59_RENESAS_DATA_MASK);                   
        Fr_LSduPtr++;                                                                                                   /* PRQA S 1338 # JV-01 */
        /* Increment the loop count by FR_59_RENESAS_TWO */
        LucIncrement = LucLoopCount + (uint8)FR_59_RENESAS_TWO;
        LucLoopCount = LucIncrement;
        /* Check the value of loop count */
        if (LucLoopCount < (*Fr_LSduLengthPtr))                                                                         /* PRQA S 3416 # JV-01 */
        {
          /* Shift the data value by 16, mask and update the data value in Fr_LSduPtr */
          *Fr_LSduPtr = (uint8)((LulData >> FR_59_RENESAS_DATA_BYTE3_SHIFT) & FR_59_RENESAS_DATA_MASK);                 
          /* Increment the pointer address */
          Fr_LSduPtr++;                                                                                                 /* PRQA S 1338 # JV-01 */
          /* Shift the data value by 24, mask and update the data value in Fr_LSduPtr */
          *Fr_LSduPtr = (uint8)(LulData >> FR_59_RENESAS_DATA_BYTE4_SHIFT);                                             
          /* Increment the pointer address */
          Fr_LSduPtr++;                                                                                                 /* PRQA S 1338 # JV-01 */
          /* Increment the loop count by FR_59_RENESAS_TWO */
          LucIncrement = LucLoopCount + (uint8)FR_59_RENESAS_TWO;
          LucLoopCount = LucIncrement;
        } /* else No Action required */
        /* Increment the loop count by FR_59_RENESAS_FOUR */
        LulDataAddress = LulDataAddress + (uint32)FR_59_RENESAS_FOUR;                                                   /* PRQA S 3383 # JV-01 */
      } /* End of while (LucLoopCount < (*Fr_LSduLengthPtr)) */
      /* Check if frame is configured to FIFO */
      if (FR_59_RENESAS_TRUE == LpFrameConfigPtr->blIsFIFOConfig)
      {
        LulData = LpMBStatusReg->ulFLXAnFRFSR;                                                                        
        /* Check if FIFO is empty or not */
        if (FR_59_RENESAS_FLX0FSR_FLX0RFNE_MASK == (LulData & FR_59_RENESAS_FLX0FSR_FLX0RFNE_MASK))
        {
          /* Update the status Ptr */
          *Fr_LPduStatusPtr = FR_RECEIVED_MORE_DATA_AVAILABLE;
        }
        else /* FIFO is empty, no new data is available */
        {
          /* Update the status Ptr and Sdu Length Ptr */
          *Fr_LPduStatusPtr = FR_RECEIVED;
        }
      } /* else No Action required */
    }
  } /* else No Action required */
  return (LucReturnValue);
} /* End of function Fr_59_Renesas_ReadReceiveData */
#define FR_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_ReadDataSection
**
** Service ID            : Not Applicable
**
** Description           : This function reads the data section from
**                         FlexRay Read Data Section Register.
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx, RegMacro
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : uint32
**
** Preconditions         : None
**
** Global Variables Used : Fr_59_Renesas_GpCtrlRegSet
**
** Functions Invoked     : None.
**
** Registers Used        : FLXAnFRRDDSi(i = 1 to 64)
**
** Reference ID          : FR_DUD_ACT_097
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(uint32, FR_PRIVATE_CODE) Fr_59_Renesas_ReadDataSection(const uint8 Fr_CtrlIdx, const uint32 RegMacro)              /* PRQA S 1505 # JV-01 */
{
  /* Declare pointer to register */
  P2CONST(volatile Fr_59_Renesas_RegisterSetType, AUTOMATIC, FR_CONFIG_DATA) LpCtrlRegSet;
  P2VAR(volatile Fr_59_Renesas_OutputBufferRegType, AUTOMATIC, REGSPACE) LpOutputBuffReg;                               /* PRQA S 3678 # JV-01 */
  /* Declare variable to store the register value */
  uint32 LulData;
  /* Initialize register value */
  LulData = FR_59_RENESAS_ZERO;                                                                                         /* PRQA S 2982 # JV-01 */
  /* Copy global pointer to local pointer */
  LpCtrlRegSet = Fr_59_Renesas_GpCtrlRegSet[Fr_CtrlIdx];                                                               
  LpOutputBuffReg = LpCtrlRegSet->pOutputBuffReg;                                                                       

  /* Read value of FLXAnFRRDDSi register */
  LulData = *((volatile uint32 *)LpOutputBuffReg + (uint32)((RegMacro-FR_59_RENESAS_FLX0RDDS1)/FR_59_RENESAS_FOUR));    /* PRQA S 0310, 0488, 3383 # JV-01, JV-01, JV-02 */
  
  return (LulData);
} /* End of function Fr_59_Renesas_ReadDataSection */
#define FR_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_UnlockSequence
**
** Service ID            : Not Applicable
**
** Description           : This function unlock driver to change to READY state.
**
** Sync/Async            : Asynchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : None
**
** Preconditions         : None
**
** Global Variables Used : Fr_59_Renesas_GpCtrlRegSet
**
** Functions Invoked     : None
**
** Registers Used        : FLXAnFRLCK
**
** Reference ID          : FR_DUD_ACT_098, FR_DUD_ACT_098_REG001,
** Reference ID          : FR_DUD_ACT_098_REG002
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(void, FR_PRIVATE_CODE) Fr_59_Renesas_UnlockSequence(const uint8 Fr_CtrlIdx)
{
  /* Declare pointer to register */
  P2CONST(volatile Fr_59_Renesas_RegisterSetType, AUTOMATIC, FR_CONFIG_DATA) LpCtrlRegSet;
  P2VAR(volatile uint32, AUTOMATIC, REGSPACE) LpFLXAnFRLCK;
  /* Copy global pointer to local pointer */
  LpCtrlRegSet = Fr_59_Renesas_GpCtrlRegSet[Fr_CtrlIdx];                                                               
  LpFLXAnFRLCK = LpCtrlRegSet->pFLXAnFRLCK;                                                                             
  /* The unlock sequence of the lock register FRLCK */
  *LpFLXAnFRLCK = FR_59_RENESAS_FLX0LCK_FIRST;                                                                          
  *LpFLXAnFRLCK = FR_59_RENESAS_FLX0LCK_SECOND;
} /* End of function Fr_59_Renesas_UnlockSequence */
#define FR_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_HaltInputQueueProcess
**
** Service ID            : Not Applicable
**
** Description           : This function to halt the input queue
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx,
**                         Fr_InputTableContentPtr
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : None
**
** Global Variables Used : Fr_59_Renesas_GpControllerConfigPtr,
**                         Fr_59_Renesas_GpCtrlRegSet
**
** Functions Invoked     : FR_59_RENESAS_DEM_REPORT_ERROR
**
** Registers Used        : FLXAnFRITS, FLXAnFRDAi(i = 0 to 3), FLXAnFRIBA,
**                         FLXAnFRITC
**
** Reference ID          : FR_DUD_ACT_099, FR_DUD_ACT_099_ERR001,
** Reference ID          : FR_DUD_ACT_099_ERR002, FR_DUD_ACT_099_ERR003,
** Reference ID          : FR_DUD_ACT_099_ERR004, FR_DUD_ACT_099_REG001,
** Reference ID          : FR_DUD_ACT_099_REG003
***********************************************************************************************************************/
#if (FR_59_RENESAS_ENABLE_INPUT_TX_HANDLER == STD_ON)
#define FR_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PRIVATE_CODE)
Fr_59_Renesas_HaltInputQueueProcess(const uint8 Fr_CtrlIdx,                                                             
                                     const volatile Fr_59_Renesas_InputPointerTableType *const Fr_InputTableContentPtr)
{
  /* Declare pointer to register */
  P2CONST(volatile Fr_59_Renesas_RegisterSetType, AUTOMATIC, FR_CONFIG_DATA) LpCtrlRegSet;
  P2VAR(volatile Fr_59_Renesas_DataTransferControlRegType, AUTOMATIC, REGSPACE) LpDataTransferCtrlReg;
  P2VAR(volatile Fr_59_Renesas_DataTransferStatusRegType, AUTOMATIC, REGSPACE) LpDataTransferStatusReg;                 /* PRQA S 3678 # JV-01 */
  /* Declare local pointer to CC configuration */
  P2CONST(Fr_59_Renesas_CtrlTableType, TYPEDEF, FR_CONFIG_DATA) LpCtrlTable;
  Std_ReturnType LucReturnValue;
  uint32 LulData;
  uint32 LulGetIndex;
  uint32 LulPutIndex;
  uint32 LulQueueMax;
  volatile uint16 LusLoopCount;
  uint8 LucMsgBuffer1;
  uint8 LucMsgBuffer2;
  uint8 LucMsgBufferMask;
  uint8 LucFRDAindex;
  boolean LblQueueHalted;
  P2VAR(volatile Fr_59_Renesas_InputPointerTableType, AUTOMATIC, FR_APPL_DATA) LpInputPointerTablePtr;
  /* Declare local pointer to Dem Event Id */
  P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF, FR_CONFIG_DATA)
  LpDemEventId;
  /* Copy global pointer to local pointer */
  LpCtrlRegSet = Fr_59_Renesas_GpCtrlRegSet[Fr_CtrlIdx];                                                               
  LpDataTransferCtrlReg = LpCtrlRegSet->pDataTransferCtrlReg;                                                          
  LpDataTransferStatusReg = LpCtrlRegSet->pDataTransferStatusReg;
  LpCtrlTable = (P2CONST(Fr_59_Renesas_CtrlTableType, AUTOMATIC,
                                          FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pCtrlTable);
  LpDemEventId = (P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF,
                                         FR_CONFIG_DATA))(Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pDemEventId);
  /* Initialize queue status as running */
  LblQueueHalted = FR_59_RENESAS_FALSE;
  /* Read current value of FLX0FRITS register */
  LulData = LpDataTransferStatusReg->ulFLXAnFRITS;                                                                      
  /* Check for Input Transfer enable */
  if (FR_59_RENESAS_FLX0FRITS_FLX0_ITS_MASK == (LulData & FR_59_RENESAS_FLX0FRITS_FLX0_ITS_MASK))
  {
    /* Read the input transfer control register */
    LulData = LpDataTransferCtrlReg->ulFLXAnFRITC;                                                                    
    /* Halt input transfer queue */
    LulData = LulData | FR_59_RENESAS_FLX0FRITC_FLX0_IQHR_MASK;
    /* Writing in to FlexRay Input Transfer Configuration Register and
     mirror address */
    LpDataTransferCtrlReg->ulFLXAnFRITC = LulData;
    /* Initialize the loop count to FR_59_RENESAS_ZERO */
    LusLoopCount = FR_59_RENESAS_ZERO;
    /* Wait input queue is halted */
    while ((FR_59_RENESAS_FLX0FRITS_FLX0_IQH_MASK !=                                                                  
                       (LpDataTransferStatusReg->ulFLXAnFRITS & FR_59_RENESAS_FLX0FRITS_FLX0_IQH_MASK)) &&
                                                            (LusLoopCount < (uint16)(LpCtrlTable->usFlagClearMaxWait))) /* PRQA S 3415, 3416 # JV-01, JV-01 */
    {
      /* Increment the loop count */
      LusLoopCount++;                                                                                                   /* PRQA S 3383, 3387 # JV-01, JV-01 */
    }
    if (LusLoopCount == (uint16)(LpCtrlTable->usFlagClearMaxWait))                                                      /* PRQA S 3416 # JV-01 */
    {
      if (FR_59_RENESAS_DEM_NOT_CONFIGURED != LpDemEventId->usReadTimeoutFailure)                                      
      {
        FR_59_RENESAS_DEM_REPORT_ERROR(LpDemEventId->usReadTimeoutFailure, DEM_EVENT_STATUS_FAILED);
      } /* else No Action required */
      /* Set Return Value as E_NOT_OK */
      LucReturnValue = E_NOT_OK;
    }
    else
    {
      /* Set queue status as halted */
      LblQueueHalted = FR_59_RENESAS_TRUE;
      /* Get the Message buffer from control register */
      LucMsgBuffer1 = (uint8)((Fr_InputTableContentPtr->ulFLX0FRWRHS4) & FR_59_RENESAS_FLX0FRWRHS4_FLX0_IMBNR);         
      /* Get the position of DA flag to be checked */
      LucMsgBufferMask = LucMsgBuffer1 & FR_59_RENESAS_FLXnFRDAi_MASK;
      /* Get the index of DA register for the given message buffer */
      LucFRDAindex = (LucMsgBuffer1 >> FR_59_RENESAS_FIVE) & FR_59_RENESAS_FLXnFRDA_INDEX_MASK;
      /* Check whether the frame is already transferred by polling
       the corresponding DA flag */
      if (FR_59_RENESAS_FLX0FRDA_INDEX_ZERO == LucFRDAindex)
      {
        LulData = LpDataTransferStatusReg->ulFLXAnFRDA0;
      }
      else if (FR_59_RENESAS_FLX0FRDA_INDEX_ONE == LucFRDAindex)
      {
        LulData = LpDataTransferStatusReg->ulFLXAnFRDA1;
      }
      else if (FR_59_RENESAS_FLX0FRDA_INDEX_TWO == LucFRDAindex)
      {
        LulData = LpDataTransferStatusReg->ulFLXAnFRDA2;
      }
      else
      {
        LulData = LpDataTransferStatusReg->ulFLXAnFRDA3;
      }
      /* Check if the corresponding DA flag is set */
      if ((uint32)FR_59_RENESAS_ONE == ((LulData >> LucMsgBufferMask) & (uint32)FR_59_RENESAS_ONE))
      {
        /* Set Return Value as E_OK */
        LucReturnValue = E_OK;
      }
      else
      {
        /* Raise DEM Error FAILED */
        if (FR_59_RENESAS_DEM_NOT_CONFIGURED != LpDemEventId->usHardwareTestFailure)
        {
          FR_59_RENESAS_DEM_REPORT_ERROR(LpDemEventId->usHardwareTestFailure, DEM_EVENT_STATUS_FAILED);
        } /* else No Action required */
        /* Set Return Value as E_NOT_OK */
        LucReturnValue = E_NOT_OK;
      }
    }
  }
  else
  {
    /* Raise DEM Error FAILED */
    if (FR_59_RENESAS_DEM_NOT_CONFIGURED != LpDemEventId->usHardwareTestFailure)
    {
      FR_59_RENESAS_DEM_REPORT_ERROR(LpDemEventId->usHardwareTestFailure, DEM_EVENT_STATUS_FAILED);
    } /* else No Action required */
    /* Set Return Value as E_NOT_OK */
    LucReturnValue = E_NOT_OK;
  }
  if (E_OK == LucReturnValue)
  {
    /* Set Return Value as E_NOT_OK */
    LucReturnValue = E_NOT_OK;
    /* Get the put index */
    LulData = LpDataTransferStatusReg->ulFLXAnFRITS & FR_59_RENESAS_FLX0FRITS_FLX0_IPIDX_MASK;
    LulPutIndex = LulData >> FR_59_RENESAS_SIXTEEN;
    /* Get the get index */
    LulData = LpDataTransferStatusReg->ulFLXAnFRITS & FR_59_RENESAS_FLX0FRITS_FLX0_IGIDX_MASK;
    LulGetIndex = LulData >> FR_59_RENESAS_TWENTYFOUR;
    /* Get the Input queue table max value */
    LulData = LpDataTransferCtrlReg->ulFLXAnFRITC & FR_59_RENESAS_FLX0FRITS_FLX0_ITM_MASK;
    LulQueueMax = LulData >> FR_59_RENESAS_SIXTEEN;
    do
    {
      /* Read current value of FLX0FRIBA register */
      LulData = LpDataTransferCtrlReg->ulFLXAnFRIBA;
      /* Get the address to write the control reg and data pointer */
      LpInputPointerTablePtr = (volatile Fr_59_Renesas_InputPointerTableType *)                                         /* PRQA S 0303 # JV-01 */
                                                               (LulData + (LulGetIndex * (uint32)FR_59_RENESAS_EIGHT)); /* PRQA S 3383 # JV-01 */
      /* Get the Message buffer at get index */
      LucMsgBuffer1 = (uint8)((LpInputPointerTablePtr->ulFLX0FRWRHS4) & FR_59_RENESAS_FLX0FRWRHS4_FLX0_IMBNR);          
      /* Get the Message buffer from control register */
      LucMsgBuffer2 = (uint8)((Fr_InputTableContentPtr->ulFLX0FRWRHS4) & FR_59_RENESAS_FLX0FRWRHS4_FLX0_IMBNR);
      /* Check whether the message buffer is same */
      if (LucMsgBuffer1 == LucMsgBuffer2)
      {
        if ((uint32)FR_59_RENESAS_ZERO <
                                  ((Fr_InputTableContentPtr->ulFLX0FRWRHS4) & FR_59_RENESAS_FLX0FRWRHS4_FLX0_INV_MASK))
        {
          /* Write the control reg in input pointer */
          LpInputPointerTablePtr->ulFLX0FRWRHS4 =
                                   ((LpInputPointerTablePtr->ulFLX0FRWRHS4) | FR_59_RENESAS_FLX0FRWRHS4_FLX0_INV_MASK);
          /* Set Return Value as E_OK */
          LucReturnValue = E_OK;
        }
        else
        {
          /* Raise DEM Error FAILED */
          if (FR_59_RENESAS_DEM_NOT_CONFIGURED != LpDemEventId->usHardwareTestFailure)
          {
            FR_59_RENESAS_DEM_REPORT_ERROR(LpDemEventId->usHardwareTestFailure, DEM_EVENT_STATUS_FAILED);
          } /* else No Action required */
          /* Set Return Value as E_NOT_OK */
          LucReturnValue = E_NOT_OK;
        }
      }
      else
      {
        LulGetIndex = ((LulGetIndex + (uint32)FR_59_RENESAS_ONE) % (LulQueueMax + (uint32)FR_59_RENESAS_ONE));          /* PRQA S 3383 # JV-01 */
      }
    } while ((LulPutIndex != LulGetIndex) && (E_OK != LucReturnValue));
  } /* else No Action required */
  /* Check whether queue was halted */
  if (FR_59_RENESAS_TRUE == LblQueueHalted)
  {
    /* Read the input transfer control register */
    LulData = LpDataTransferCtrlReg->ulFLXAnFRITC;
    /* Input queue run request */
    LulData = LulData & FR_59_RENESAS_FLX0FRITC_IQHR_RESET;
    /* Writing in to FlexRay Input Transfer Configuration Register and
     mirror address */
    LpDataTransferCtrlReg->ulFLXAnFRITC = LulData;
  } /* else No Action required */
  return (LucReturnValue);
} /* End of function Fr_59_Renesas_HaltInputQueueProcess */
#define FR_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
#endif
/***********************************************************************************************************************
** Function Name         : Fr_59_Renesas_GetSlotAssignment
**
** Service ID            : Not Applicable
**
** Description           : This function gets Channel ID, Cycle ID and Slot ID of the transmitted/received frame.
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : Fr_CtrlIdx,
**                         Fr_LPduIdx
**
** InOut Parameters      : None
**
** Output Parameters     : Fr_SlotAssignmentPtr
**
** Return Parameter      : Std_ReturnType E_OK or E_NOT_OK
**
** Preconditions         : None
**
** Global Variables Used : Fr_59_Renesas_GpControllerConfigPtr,
**                         Fr_59_Renesas_GpCtrlRegSet
**
** Functions Invoked     : FR_59_RENESAS_DEM_REPORT_ERROR
**
** Registers Used        : FLXAnFRRDHS1
**
** Reference ID          : FR_DUD_ACT_100
** Reference ID          : FR_DUD_ACT_100_ERR001
***********************************************************************************************************************/
#if (FR_59_RENESAS_EXTENDED_LPDU_REPORTING == STD_ON)
#define FR_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FR_PRIVATE_CODE)
Fr_59_Renesas_GetSlotAssignment(const uint8 Fr_CtrlIdx, const uint16 Fr_LPduIdx,                                        
                                Fr_SlotAssignmentType *const Fr_SlotAssignmentPtr)
{
  /* Declare local pointer to Dem Event Id */
  P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF, FR_CONFIG_DATA) LpDemEventId;
  /* Declare pointer to register */
  P2CONST(volatile Fr_59_Renesas_RegisterSetType, AUTOMATIC, FR_CONFIG_DATA) LpCtrlRegSet;
  P2VAR(volatile Fr_59_Renesas_OutputBufferRegType, AUTOMATIC, REGSPACE) LpOutputBuffReg;                               /* PRQA S 3678 # JV-01 */
  uint32 LulData;
  Std_ReturnType LucReturnValue;
  /* Declare pointer to frame configuration */
  P2CONST(Fr_59_Renesas_FrameHeaderType, AUTOMATIC, FR_APPL_CONST) LpFrameConfigPtr;
  P2CONST(Fr_59_Renesas_FrameHeaderType, TYPEDEF, FR_CONFIG_DATA) LpFrameConfig;
  LucReturnValue = E_NOT_OK;
  /* Copy global pointer to local pointer */
  LpCtrlRegSet = Fr_59_Renesas_GpCtrlRegSet[Fr_CtrlIdx];                                                               
  LpOutputBuffReg = LpCtrlRegSet->pOutputBuffReg;                                                                       
  LpFrameConfig = Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pFrameConfig;
  LpFrameConfigPtr = &LpFrameConfig[Fr_LPduIdx];                                                                        
  LpDemEventId = (P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF, FR_CONFIG_DATA))(
                                                           Fr_59_Renesas_GpControllerConfigPtr[Fr_CtrlIdx].pDemEventId);
  /* Read Channel ID from FLXAnFRWRHS1 register */
  if (LpFrameConfigPtr->ucFrameConfig == FR_59_RENESAS_CFG_TRANSMIT)                                                   
  {
    /* Get Channel ID */
    Fr_SlotAssignmentPtr->channelId = (Fr_ChannelType)LpFrameConfigPtr->ucChannelFilter;                                /* PRQA S 4342 # JV-01 */
    /* Get Cycle ID */
    Fr_SlotAssignmentPtr->Cycle = LpFrameConfigPtr->ucCycleCode;
    /* Get Slot ID */
    Fr_SlotAssignmentPtr->SlotId = LpFrameConfigPtr->usFrameId;
    /* Set Return Value as E_OK */
    LucReturnValue = E_OK;
  }
  else
  {
    LulData = ((LpOutputBuffReg->ulFLXAnFRRDHS1 & FR_59_RENESAS_CHANNEL_MASK) >> FR_59_RENESAS_CHNL_SHIFT);             
    switch (LulData)
    {
      case FR_59_RENESAS_CHANNEL_A:
        /* Channel A */
        Fr_SlotAssignmentPtr->channelId = FR_CHANNEL_A;
        /* Set Return Value as E_OK */
        LucReturnValue = E_OK;
        break;

      case FR_59_RENESAS_CHANNEL_B:
         /* Channel B */
        Fr_SlotAssignmentPtr->channelId = FR_CHANNEL_B;
        /* Set Return Value as E_OK */
        LucReturnValue = E_OK;
        break;

      case FR_59_RENESAS_CHANNEL_AB:
         /* Channel AB */
        Fr_SlotAssignmentPtr->channelId = FR_CHANNEL_AB;
        /* Set Return Value as E_OK */
        LucReturnValue = E_OK;
        break;

      default:
        /* No action required */
        break; 
    }
    if (LucReturnValue == E_OK)
    {
      /* Read Cycle ID from FLXAnFRWRHS1 register */
      LulData = ((LpOutputBuffReg->ulFLXAnFRRDHS1 & FR_59_RENESAS_CYCLE_MASK) >> FR_59_RENESAS_CYC_SHIFT);
      Fr_SlotAssignmentPtr->Cycle = (uint8)LulData;
      /* Read Frame ID from FLXAnFRWRHS1 register */
      LulData = LpOutputBuffReg->ulFLXAnFRRDHS1 & FR_59_RENESAS_FID_MASK;
      Fr_SlotAssignmentPtr->SlotId = (uint16)LulData;
    }
    else
    {
      if (FR_59_RENESAS_DEM_NOT_CONFIGURED != LpDemEventId->usHardwareTestFailure)                                   
        {
          FR_59_RENESAS_DEM_REPORT_ERROR(LpDemEventId->usHardwareTestFailure, DEM_EVENT_STATUS_FAILED);
        } /* else No action required */
        /* Set Return Value as E_NOT_OK */
        LucReturnValue = E_NOT_OK;
    }
  }
  return (LucReturnValue);
} /* End of function Fr_59_Renesas_GetSlotAssignment */
#define FR_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Fr_59_Renesas_MemMap.h"                                                                                       /* PRQA S 5087 # JV-01 */
#endif
/***********************************************************************************************************************
**                                                    END OF FILE                                                     **
***********************************************************************************************************************/
