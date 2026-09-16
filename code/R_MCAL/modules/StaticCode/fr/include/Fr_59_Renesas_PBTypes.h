/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Fr_59_Renesas_PBTypes.h                                                                             */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2019-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains the type definitions of Post Build time Parameters.                                             */
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
 * 2.3.0:  28/02/2025    : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.1:  31/12/2024    : Update SW-VERSION for Ver22.00.01 U2Ax Release
 * 2.2.0:  31/12/2024    : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 * 2.1.3:  31/10/2024    : Update SW-VERSION to 2.1.3
 * 2.1.2:  16/08/2024    : Remove preprocessor FR_59_RENESAS_AR_431_VERSION
 * 2.1.1:  01/06/2024    : As part of multicore support, following changes are made:
 *                         Add new struct type Fr_59_Renesas_GlobalAccessPointType to support multicore
 *                       : As part of multiple postbuild variant support, following changes are made:
 *                         1. Change condition #ifdef FR_59_RENESAS_FRAME_HEADER_CONFIG_COUNT01 to 
 *                         #ifdef Fr_59_RenesasConf_FrAbsoluteTimer_FrAbsoluteTimer_001
 *                         2. Add new struct Fr_59_Renesas_PeriodTimeType, and add it as
 *                         new element in Fr_59_Renesas_ConfigType, delete redundant defined of posbuild variable
 *                       : As part of QAC 10.3.0 support, following changes are made:
 *                         1. Add new QAC for message 3630
 *                         2. Remove redundant QAC message: 1536
 *                         3. Remove redundant QAC message: 0791, 3472
 * 2.1.0:  24/02/2024    : Change SW-VERSION to 2.1.0
 * 2.0.1:  27/09/2023   : Change FR_59_RENESAS_AR_R21_11_VERSION with FR_59_RENESAS_AR_R22_11_VERSION to support AR22-11
 *                         Add QAC message: 1536
 * 2.0.0:   30/07/2023   : Add CWE rule into QAC header (3432 message)
 *                       : Change FR_59_RENESAS_AR_2111_VERSION to FR_59_RENESAS_AR_R21_11_VERSION
 *          21/04/2023   : Add function name of DEM report error in AR2111
 *                         Change SW-VERSION to 2.0.0
 * 1.4.3:   09/05/2022   : Change SW-VERSION to 1.4.3
 * 1.3.3:   02/03/2022   : Change SW-VERSION to 1.4.2
 * 1.3.2:   13/08/2021   : Change SW-VERSION to 1.3.2
 * 1.3.1:   02/07/2021   : Add QAC message 9.5.0.
 *                         Format source code to 120 characters.
 *                         Improve Violation tag (remove START/END).
 *          04/05/2021   : In function FR_59_RENESAS_DEM_REPORT_ERROR add space to follow
 *                         coding guideline Style_Format_010.
 * 1.3.0:   02/12/2020   : Add ucAbsTimerCount to struct Fr_59_Renesas_CtrlTableType.
 *                         Add struct Fr_59_Renesas_AbsTimerConfigType.
 *                         Add pAbsTimerConfig to struct Fr_59_Renesas_ControllerConfigType.
 *                         Add definition for array: Fr_59_Renesas_GaaCtrl_00_AbsTimerConfig[],
 *                         Fr_59_Renesas_GaaCtrl_01_AbsTimerConfig[].
 *                         Remove ulFrTimer0Config and ulFrTimer2Config in struct
 *                         Fr_59_Renesas_LowLevelConfSetType.
 *                         Update comment for QAC message 0342.
 * 1.2.0:   26/08/2020   : Release.
 * 1.1.0:   19/06/2020   : Release.
 *          28/07/2020   : Add QAC 9.3.1 comment.
 * 1.0.2:   12/06/2020   : Add blAllowColdStart to struct Fr_59_Renesas_CtrlTableType.
 *          28/05/2020   : Remove QAC message Msg(4:3448),Msg(4:3447),Msg(2:3210)
 *          24/05/2020   : Add MISRA C Rule Violation (2:3453)
 *          17/04/2020   : Remove the header files including.
 *          13/04/2020   : Remove QAC message 0777.
 * 1.0.1:   26/03/2020   : Rename as in #262866.
 *          20/03/2020   : Add QAC for message 3684 and message 0777.
 *          18/12/2019   : Update section FR_59_RENESAS_START_SEC_VAR_NOINIT_16
 *                         to FR_59_RENESAS_START_SEC_VAR_NO_INIT_16,
 *                         FR_59_RENESAS_STOP_SEC_VAR_NOINIT_16
 *                         to FR_59_RENESAS_STOP_SEC_VAR_NO_INIT_16.
 * 1.0.0:   11/12/2019  : Initial Version.
 */
/**********************************************************************************************************************/

#ifndef FR_59_RENESAS_PBTYPES_H
#define FR_59_RENESAS_PBTYPES_H
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/

/* AUTOSAR release version information */
#define FR_59_RENESAS_PBTYPES_AR_RELEASE_MAJOR_VERSION       FR_59_RENESAS_AR_RELEASE_MAJOR_VERSION
#define FR_59_RENESAS_PBTYPES_AR_RELEASE_MINOR_VERSION       FR_59_RENESAS_AR_RELEASE_MINOR_VERSION
#define FR_59_RENESAS_PBTYPES_AR_RELEASE_REVISION_VERSION    FR_59_RENESAS_AR_RELEASE_REVISION_VERSION

/* Module Software version information */
#define FR_59_RENESAS_PBTYPES_SW_MAJOR_VERSION               FR_59_RENESAS_SW_MAJOR_VERSION
#define FR_59_RENESAS_PBTYPES_SW_MINOR_VERSION               FR_59_RENESAS_SW_MINOR_VERSION

/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:0342)    : Using the glue operator '##'.                                                                */
/* Rule                : CERTCCM PRE05, MISRA C:2012 Rule-20.10                                                       */
/* JV-01 Justification : This can be accepted, due to the implementation is following AUTOSAR standard rule for SchM  */
/*                       module's name.                                                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE Rule CWE-398, CWE-569                                            */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is accepted. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3684)    : Array declared with unknown size.                                                            */
/* Rule                : CERTCCM ARR02, MISRA C:2012 Rule-8.11                                                        */
/* JV-01 Justification : Arrays used are verified in the file which are only declarations and size is configuration   */
/*                       dependent.                                                                                   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3630)    : The implementation of this struct/union type should be hidden.                               */
/* Rule                : MISRA C:2012 Dir-4.8                                                                         */
/* JV-01 Justification : This is accepted. Redundant of struct or union type has no affect to driver operation.       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                      SchM Critical Section Protection Macros                                       **
***********************************************************************************************************************/

/* SchM Critical Section Protection */
#define FR_59_RENESAS_ENTER_CRITICAL_SECTION(Exclusive_Area) SchM_Enter_Fr_59_Renesas_##Exclusive_Area()                /* PRQA S 0342 # JV-01 */
#define FR_59_RENESAS_EXIT_CRITICAL_SECTION(Exclusive_Area)  SchM_Exit_Fr_59_Renesas_##Exclusive_Area()                 /* PRQA S 0342 # JV-01 */

/*
 * Macro to define DEM error report function for AR422, R2211
 */
#if (FR_59_RENESAS_AR_VERSION == FR_59_RENESAS_AR_422_VERSION)
/* Function name of DEM report error in AR422 */
#define FR_59_RENESAS_DEM_REPORT_ERROR(EventId, EventStatus) Dem_ReportErrorStatus(EventId, EventStatus)
#elif (FR_59_RENESAS_AR_VERSION == FR_59_RENESAS_AR_R22_11_VERSION)
/* Function name of DEM report error in AR2211 */
#define FR_59_RENESAS_DEM_REPORT_ERROR(EventId, EventStatus) (void)Dem_SetEventStatus(EventId, EventStatus)
#endif

/* Structure for controller specific parameters */
typedef struct STag_Fr_59_Renesas_CtrlTableType                                                                         /* PRQA S 3630 # JV-01 */
{
  /* Channels configured for the CC */
  Fr_ChannelType ddChannels;
  /* Max Macroticks per cycle */
  uint16 usMaxMacroPerCycle;
  /* Maximum Number of Initial frames configured */
  uint16 usInitialMaxFrames;
  /* Maximum number of frames configured */
  uint16 usMaxFrames;
  /* Maximum payload length dynamic frame  */
  uint8 ucFrPPayloadLengthDynMax;
  /* Key slot ID */
  uint16 usFrPKeySlotId;
  /*
   * Maximum wait time for PBSY flag, IBSY flag, OBSY flag and interrupt flags to clear
   */
  uint16 usFlagClearMaxWait;
  /* Allow ColdStart */
  boolean blAllowColdStart;
  /* ucAbsTimerCount */
  uint8 ucAbsTimerCount;
} Fr_59_Renesas_CtrlTableType;

/* Structure of register values for Low level configuration */
typedef struct STag_Fr_59_Renesas_LowLevelConfSetType                                                                   /* PRQA S 3630 # JV-01 */
{
  /* Error Interrupts line selection configuration */
  uint32 ulFrErrorIntpLineSelect;
  /* Status Interrupts line selection */
  uint32 ulFrStatusIntpLineSelect;
  /* Enable / Disable Errors Interrupts */
  uint32 ulFrErrorIntpEnable;
  /* Enable / Disable Status Interrupts */
  uint32 ulFrStatusIntpEnable;
  /* Enable / Disable Interrupt Lines */
  uint32 ulFrIntpLineEnable;
  /* Stop Watch Configuration */
  uint32 ulFrStopWatchConfig;
  /* System Universal Control Register 1 Configuration */
  uint32 ulFrSUCC1Config;
  /* System Universal Control Register 2 Configuration */
  uint32 ulFrSUCC2Config;
  /* System Universal Control Register 3 Configuration */
  uint32 ulFrSUCC3Config;
  /* Network Management Vector Configuration */
  uint32 ulFrNEMConfig;
  /* Protocol Controller Register 1 Configuration */
  uint32 ulFrPRTC1Config;
  /* Protocol Controller Register 2 Configuration */
  uint32 ulFrPRTC2Config;
  /* Message Handler Configuration */
  uint32 ulFrMHDCConfig;
  /* Global Time Unit Register 1 Configuration */
  uint32 ulFrGTUC1Config;
  /* Global Time Unit Register 2 Configuration */
  uint32 ulFrGTUC2Config;
  /* Global Time Unit Register 3 Configuration */
  uint32 ulFrGTUC3Config;
  /* Global Time Unit Register 4 Configuration */
  uint32 ulFrGTUC4Config;
  /* Global Time Unit Register 5 Configuration */
  uint32 ulFrGTUC5Config;
  /* Global Time Unit Register 6 Configuration */
  uint32 ulFrGTUC6Config;
  /* Global Time Unit Register 7 Configuration */
  uint32 ulFrGTUC7Config;
  /* Global Time Unit Register 8 Configuration */
  uint32 ulFrGTUC8Config;
  /* Global Time Unit Register 9 Configuration */
  uint32 ulFrGTUC9Config;
  /* Global Time Unit Register 10 Configuration */
  uint32 ulFrGTUC10Config;
  /* Global Time Unit Register 11 Configuration */
  uint32 ulFrGTUC11Config;
  /* Message RAM Configuration */
  uint32 ulFrMRCConfig;
  /* FIFO Rejection Filter Configuration */
  uint32 ulFrFRFConfig;
  /* FIFO Rejection Filter Mask Configuration */
  uint32 ulFrFRFMConfig;
  /* FIFO Critical Level Configuration */
  uint32 ulFrFCLConfig;
#if (FR_59_RENESAS_ENABLE_INPUT_TX_HANDLER == STD_ON)
  /* Input Transfer Configuration */
  uint32 ulFrInputTxConfReg;
  /* Input Pointer Table Base Address */
  uint32 ulFrInpPtrTblBaseAddReg;
#endif
#if (FR_59_RENESAS_ENABLE_OUTPUT_RX_HANDLER == STD_ON)
  /* Output Pointer Table Base Address */
  uint32 ulFrOptPtrTblBaseAddReg;
#endif
#if (FR_59_RENESAS_ENABLE_OUTPUT_RX_FIFO_HANDLER == STD_ON)
  /*FlexRay Output Transfer Configuration*/
  uint32 ulFrOutputTxConfReg;
  /* FIFO Pointer Table Base Address */
  uint32 ulFrFIFOPtrTblBaseAddReg;
#endif
} Fr_59_Renesas_LowLevelConfSetType;

/* Structure of register values for Controller Register Set Structure */
typedef struct STag_Fr_59_Renesas_RegisterSetType
{
  /* Pointer to FlexRay Operation register set */
  P2VAR(volatile Fr_59_Renesas_OperationRegType, TYPEDEF, REGSPACE) pFROReg;
  /* FlexRay Lock Register */
  P2VAR(volatile uint32, TYPEDEF, REGSPACE) pFLXAnFRLCK; /* Base + 001CH */
  /* Pointer to interrupt register set */
  P2VAR(volatile Fr_59_Renesas_InterruptRegType, TYPEDEF, REGSPACE) pIntReg;
  /* Pointer to FlexRay Timer register set */
  P2VAR(volatile Fr_59_Renesas_TimerRegType, TYPEDEF, REGSPACE) pTimerReg;
  /* Pointer to CC Control register set */
  P2VAR(volatile Fr_59_Renesas_CCControlRegType, TYPEDEF, REGSPACE) pCCCtrlReg;
  /* Pointer to CC Status register set */
  P2VAR(volatile Fr_59_Renesas_CCStatusRegType, TYPEDEF, REGSPACE) pCCStatusReg;
  /* Pointer to Message Buffer Control register set */
  P2VAR(volatile Fr_59_Renesas_MessageBufferControlRegType, TYPEDEF, REGSPACE) pMBCtrlReg;
  /* Pointer to Message Buffer Status register set */
  P2VAR(volatile Fr_59_Renesas_MessageBufferStatusRegType, TYPEDEF, REGSPACE) pMBStatusReg;
  /* Pointer to Input Buffer register set */
  P2VAR(volatile Fr_59_Renesas_InputBufferRegType, TYPEDEF, REGSPACE) pInputBuffReg;
  /* Pointer to Output Buffer register set */
  P2VAR(volatile Fr_59_Renesas_OutputBufferRegType, TYPEDEF, REGSPACE) pOutputBuffReg;
  /* Pointer to Data Transfer Control register set */
  P2VAR(volatile Fr_59_Renesas_DataTransferControlRegType, TYPEDEF, REGSPACE) pDataTransferCtrlReg;
  /* Pointer to Data Transfer Status register set */
  P2VAR(volatile Fr_59_Renesas_DataTransferStatusRegType, TYPEDEF, REGSPACE) pDataTransferStatusReg;
  /* FlexRay Timer 2 Configuration Register */
  P2VAR(volatile uint32, TYPEDEF, REGSPACE) plFLXAnFRT2C; /* Base + 0844H */
} Fr_59_Renesas_RegisterSetType;

/* Structure for frame configuration */
typedef struct STag_Fr_59_Renesas_FrameHeaderType                                                                       /* PRQA S 3630 # JV-01 */
{
  /* Frame ID of the message header */
  uint16 usFrameId;
  /* Message Ram data pointer (Frame ID) */
  uint16 usDataPointer;
  /* Header CRC */
  uint16 usHeaderCrc;
  /* DEM event Id that is reported when CC detects slot errors */
  uint16 usFrIfDemFTSlotStatus;
  /* Message Buffer associated with the Frame */
  uint8 ucMsgBuffer;
  /* Payload Preamble Indication Transmit */
  uint8 ucPpit;
  /* Cycle Code value for the frame */
  uint8 ucCycleCode;
  /* Channel Filter control for the frame */
  uint8 ucChannelFilter;
  /* Transmit or Receive frame configuration */
  uint8 ucFrameConfig;
  /* Frame Transmission Mode - Single shot or Continuous */
  uint8 ucTransmissionMode;
  /* Message Buffer Interrupt Enable/Disable */
  uint8 ucMsgBufferInterrupt;
  /* Payload Length Configured */
  uint8 ucPayloadLength;
  /* Reconfigurable message buffer */
  boolean blBufferReConfig;
  /* Allow Dynamic LSdu Length */
  boolean blAllowDynLength;
  /* FIFO Configuration */
  boolean blIsFIFOConfig;
  /* FrIf DEM Check */
  boolean blIsFrIfDemFTSlotStatusConfig;
  /* FrIfReconfigurable */
  boolean blFrIfReconfigurable;
} Fr_59_Renesas_FrameHeaderType;

/* DEM event ID structure */
typedef struct STag_Fr_59_Renesas_DemEventIdType                                                                        /* PRQA S 3630 # JV-01 */
{
  /*
   * Reference to DEM event Id reported for FlexRay controller hardware test failure
   */
  uint16 usHardwareTestFailure;
  /*
   * Reference to DEM event Id reported if FlexRay hardware register has timed out while reading
   */
  uint16 usReadTimeoutFailure;
} Fr_59_Renesas_DemEventIdType;

/* Structure for Timer configuration */
typedef struct STag_Fr_59_Renesas_AbsTimerConfigType
{
  /* To specifies the timer is selected */
  Fr_59_Renesas_TimerSelectionType enTimerSelection;
  /* To configures the mode of timer */
  Fr_59_Renesas_TimerModeSelectType enTimerModeSelect;
} Fr_59_Renesas_AbsTimerConfigType;

/* FlexRay Driver Initialization Data Structure */
typedef struct Stag_Fr_59_Renesas_ControllerConfigType                                                                  /* PRQA S 3630 # JV-01 */
{
  /* Pointer to FlexRay CC Configuration */
  P2CONST(Fr_59_Renesas_CtrlTableType, TYPEDEF, FR_APPL_CONST) pCtrlTable;

  /* Pointer to FlexRay Low level Configuration */
  P2CONST(Fr_59_Renesas_LowLevelConfSetType, TYPEDEF, FR_APPL_CONST) pLowLevelConfig;

  /* Pointer to FlexRay Frame Configuration */
  P2CONST(Fr_59_Renesas_FrameHeaderType, TYPEDEF, FR_APPL_CONST) pFrameConfig;

#if (FR_59_RENESAS_RECONFIG_LPDU == STD_ON) || (FR_59_RENESAS_PREPARE_LPDU == STD_ON) || \
    (FR_59_RENESAS_DISABLE_LPDU == STD_ON)
  /* Pointer to Flexray Buffer reconfig status */
  P2VAR(uint16, TYPEDEF, FR_VAR_NO_INIT) pBufferReConfigStatus;                                                         /* PRQA S 3432 # JV-01 */

#endif /* FR_59_RENESAS_RECONFIG_LPDU */

  /* Pointer to list of register addresses for FlexRay controller */
  P2CONST(Fr_59_Renesas_RegisterSetType, TYPEDEF, FR_APPL_CONST) pCtrlReg;

  /* Pointer to reference path to Dem Event ID for FlexRay controller */
  P2CONST(Fr_59_Renesas_DemEventIdType, TYPEDEF, FR_APPL_CONST) pDemEventId;

  /* Pointer to reference path to Dem Event ID for FlexRay controller */
  P2CONST(Fr_59_Renesas_AbsTimerConfigType, TYPEDEF, FR_APPL_CONST) pAbsTimerConfig;
} Fr_59_Renesas_ControllerConfigType;


/* Period/Timeout Count Information Struct*/
typedef struct STag_Fr_59_Renesas_PeriodTimeType                                                                        /* PRQA S 3630 # JV-01 */
{
  /* ulGdNit */
  uint32 ulGdNit;
  /* ucGdbit */
  uint8 ucGdBit;
  /* ulGdcycle */
  uint32 ulGdCycle;
  /* ulGdSymbolWindow */
  uint32 ulGdSymbolWindow;
  /* ulMacroTick */
  uint32 ulMacroTick;
} Fr_59_Renesas_PeriodTimeType;


/* Structure for reference the implementation-specific post build */
typedef struct STag_Fr_59_Renesas_ConfigType
{
  /* Database start value - 0x55AA55AA */
  uint32 ulStartOfDbToc;
  /* pPeriodTimeConfig */
  P2CONST(Fr_59_Renesas_PeriodTimeType, TYPEDEF, FR_APPL_CONST) pPeriodTimeConfig;
  /* Pointer to FlexRay CC Configuration */
  P2CONST(Fr_59_Renesas_ControllerConfigType, TYPEDEF, FR_APPL_CONST) pControllerConfig;
} Fr_59_Renesas_ConfigType;

/* Global data for using across core */
typedef struct STag_Fr_59_Renesas_GlobalAccessPointType
{
  /* Global variable to store the Fr driver initialization state */
  volatile boolean *pInitDone;
  /* Global variable to store the Fr transfer handler initialization state */
  volatile boolean *pTransferHandlerInitDone;
} Fr_59_Renesas_GlobalAccessPointType;
/***********************************************************************************************************************
**                                           Global configuration constants                                           **
***********************************************************************************************************************/


#define FR_59_RENESAS_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Fr_59_Renesas_MemMap.h"

extern CONST(Fr_59_Renesas_RegisterSetType, FR_CONFIG_DATA) Fr_59_Renesas_GaaCtrlRegSet[];                              /* PRQA S 3684 # JV-01 */

extern CONST(Fr_59_Renesas_AbsTimerConfigType, FR_CONFIG_DATA) Fr_59_Renesas_GaaCtrl_00_AbsTimerConfig[];               /* PRQA S 3684 # JV-01 */
#ifdef Fr_59_RenesasConf_FrAbsoluteTimer_FrAbsoluteTimer_001
extern CONST(Fr_59_Renesas_AbsTimerConfigType, FR_CONFIG_DATA) Fr_59_Renesas_GaaCtrl_01_AbsTimerConfig[];               /* PRQA S 3684 # JV-01 */
#endif


#define FR_59_RENESAS_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Fr_59_Renesas_MemMap.h"

#endif /* FR_59_RENESAS_PBTYPES_H */
/***********************************************************************************************************************
**                                                    END OF FILE                                                     **
***********************************************************************************************************************/
