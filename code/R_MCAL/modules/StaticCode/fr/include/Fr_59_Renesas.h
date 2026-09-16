/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Fr_59_Renesas.h                                                                                     */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2019-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains macros for version information, DET error code, service ID,                                     */
/* API function prototypes of FR Driver.                                                                              */
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
 * 2.1.3:  31/10/2024    : As part of R22-11 support, following changes are made:
 *                         Remove preprocessor FR_59_RENESAS_AR_431_VERSION
 * 2.1.1:  30/08/2024    : As part of multicore support, following changes are made:
 *                         1. Add FR_59_RENESAS_E_INVALID_CORE to support multicore
 *                         2. Delete size in Fr_59_Renesas_GaaConfiguration
 *                       : As part of multiple postbuild variant support, following changes are made:
 *                         1. Add Message (2:3684) for Fr_59_Renesas_GaaConfiguration
 *                         2. Delete QAC message: 1534
 *                         3. Remove redundant QAC message: 0791
 * 2.1.0:  24/02/2024    : Change SW-VERSION to 2.1.0
 * 2.0.1:  27/09/2023   : Change FR_59_RENESAS_AR_R21_11_VERSION with FR_59_RENESAS_AR_R22_11_VERSION to support AR22-11
 *                         Add QAC message: 1534
 * 2.0.0:  26/05/2023    : Change FR_59_RENESAS_AR_2111_VERSION to FR_59_RENESAS_AR_R21_11_VERSION
 *         21/04/2023    : Due to support AR2111, update syntax for APIs: 
 *                         Fr_59_Renesas_TransmitTxLPdu
 *                         Fr_59_Renesas_ReceiveRxLPdu
 *                         Fr_59_Renesas_CheckTxLPduStatus
 *         06/03/2023    : Update FR_59_RENESAS_SW_MAJOR_VERSION from 1 to 2
 *                         Update FR_59_RENESAS_SW_MINOR_VERSION from 4 to 0
 *                         Update FR_59_RENESAS_SW_PATCH_VERSION from 5 to 0
 * 1.4.5:  05/12/2022    : Update FR_59_RENESAS_SW_PATCH_VERSION from 4 to 5
 * 1.4.4:  13/06/2022    : Update FR_59_RENESAS_SW_PATCH_VERSION from 3 to 4
 * 1.4.3:  09/05/2022    : Update FR_59_RENESAS_SW_PATCH_VERSION from 2 to 3
 * 1.4.2:  02/03/2022    : Update FR_59_RENESAS_SW_PATCH_VERSION from 1 to 2
 * 1.4.1:  06/12/2021    : Update FR_59_RENESAS_SW_PATCH_VERSION from 0 to 1
 * 1.4.0:  11/10/2021    : Update FR_59_RENESAS_SW_MINOR_VERSION from 3 to 4
 *                         Update FR_59_RENESAS_SW_PATCH_VERSION from 2 to 0
 *                         Update SW-VERSION to 1.4.0
 * 1.3.2:  13/08/2021    : Update FR_59_RENESAS_SW_PATCH_VERSION from 1 to 2, change SW-VERSION to 1.3.2
 * 1.3.1:  02/07/2021    : Add QAC message 9.5.0.
 *                         Format source code to 120 characters.
 *                         Improve Violation tag (remove START/END).
 *         04/05/2021    : In API Fr_59_Renesas_GetVersionInfo, add space to follow coding guideline Style_Format_010.
 * 1.3.0:  20/01/2021    : Update function prototype for following Renesas APIs
 *                         Fr_59_Renesas_TransferHandlerInit
 *                         Fr_59_Renesas_TransferQueueTable
 *                         Fr_59_Renesas_ReceiveQueueTable
 *                         Fr_59_Renesas_InputTransferDisable
 *                         Fr_59_Renesas_OutputTransferDisable
 *                         Fr_59_Renesas_UserInputTransferRequest
 *                         Fr_59_Renesas_UserOutputTransferRequest
 *                         Fr_59_Renesas_HaltInputQueue
 *                         Fr_59_Renesas_SetCycleCounterFiltering.
 *         30/11/2020    : Change SW-VERSION to 1.3.0.
 *                         Remove QAC message 3210.
 * 1.2.0:  26/08/2020    : Release.
 * 1.1.1:  26/08/2020    : Change SW-VERSION to 1.2.0.
 * 1.1.0:  19/06/2020    : Release.
 *         28/07/2020    : Add QAC 9.3.1 comment.
 * 1.0.4:  29/05/2020    : Remove MISRA C Rule (4:3447)
 *                         Add FR_59_RENESAS_E_INV_CHI_COMMAND.
 *         04/05/2020    : Add definition of FR_59_RENESAS_E_INV_FRAMEID DET error.
 * 1.0.3:  25/04/2020    : Remove argument definition using Compiler.h's macros.
 *         19/04/2020    : Defined FR_59_RENESAS_SW_MAJOR_VERSION, FR_59_RENESAS_SW_MINOR_VERSION,
 *                         FR_59_RENESAS_SW_PATCH_VERSION as fixed number.
 *         17/04/2020    : Update the header file including.
 * 1.0.2:  06/04/2020    : Add FR_59_RENESAS_ENABLE_INPUT_TX_HANDLER pre-compile condition to extern
 *                         Fr_59_Renesas_InputTransferDisable.
 * 1.0.1:  26/03/2020    : Move FR_59_RENESAS_DEM_REPORT_ERROR macro to Fr_59_Renesas_PBTypes.h.
 *         20/03/2020    : Add QAC header for message 3453.
 *         12/02/2020    : Improve FR_59_RENESAS_DEM_REPORT_ERROR macro format.
 *         14/01/2020    : Add FR_59_RENESAS_DEM_REPORT_ERROR macro to define function name that report Dem status 
 *                         base on AUTOSAR version.
 * 1.0.0:  11/12/2019    : Initial Version.
 */
/**********************************************************************************************************************/

#ifndef FR_59_RENESAS_H
#define FR_59_RENESAS_H

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Include configuration file */
#include "Fr_59_Renesas_Cfg.h"
/* Include type and variable definition */
#include "Fr_59_Renesas_Ram.h"

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* Vendor ID */
#define FR_59_RENESAS_VENDOR_ID   FR_59_RENESAS_VENDOR_ID_VALUE
/* Instance ID */
#define FR_59_RENESAS_INSTANCE_ID FR_59_RENESAS_INSTANCE_ID_VALUE
/* Module ID */
#define FR_59_RENESAS_MODULE_ID   FR_59_RENESAS_MODULE_ID_VALUE

#if (FR_59_RENESAS_AR_VERSION == FR_59_RENESAS_AR_422_VERSION)
/* AUTOSAR release version information */
#define FR_59_RENESAS_AR_RELEASE_MAJOR_VERSION    4U
#define FR_59_RENESAS_AR_RELEASE_MINOR_VERSION    2U
#define FR_59_RENESAS_AR_RELEASE_REVISION_VERSION 2U
#elif (FR_59_RENESAS_AR_VERSION == FR_59_RENESAS_AR_R22_11_VERSION)
/* AUTOSAR release version information */
#define FR_59_RENESAS_AR_RELEASE_MAJOR_VERSION    4U
#define FR_59_RENESAS_AR_RELEASE_MINOR_VERSION    8U
#define FR_59_RENESAS_AR_RELEASE_REVISION_VERSION 0U
#endif

/* Module Software version information */
#define FR_59_RENESAS_SW_MAJOR_VERSION              2U
#define FR_59_RENESAS_SW_MINOR_VERSION              4U
#define FR_59_RENESAS_SW_PATCH_VERSION              1U

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:3684)    : Array declared with unknown size.                                                            */
/* Rule                : MISRA C:2012 Rule-8.11, CERTCCM ARR02                                                        */
/* JV-01 Justification : Arrays used are verified in the file which are only declarations and size is configuration   */
/*                       dependent.                                                                                   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  DET ERROR CODES                                                   **
***********************************************************************************************************************/
/*
 * Following error will be reported when API service is called if Parameter
 * timer index exceeds number of available timers
 */
#define FR_59_RENESAS_E_INV_TIMER_IDX               (uint8)0x01

/*
 * Following error will be reported when API service is called with invalid
 * pointer in parameter list
 */
#define FR_59_RENESAS_E_PARAM_POINTER               (uint8)0x02

/*
 * Following error will be reported when API service is called with Parameter
 * offset exceeds bounds
 */
#define FR_59_RENESAS_E_INV_OFFSET                  (uint8)0x03

/*
 * Following error will be reported when API service is called with invalid
 * controller index
 */
#define FR_59_RENESAS_E_INV_CTRL_IDX                (uint8)0x04

/*
 * Following error will be reported when API service is called with Invalid
 * channel index
 */
#define FR_59_RENESAS_E_INV_CHNL_IDX                (uint8)0x05

/*
 * Following error will be reported when API service is called if Parameter
 * cycle exceeds 63
 */
#define FR_59_RENESAS_E_INV_CYCLE                   (uint8)0x06

/*
 * Following error will be reported when API service is called if Fr module was
 * not initialized
 */
#define FR_59_RENESAS_E_INIT_FAILED                 (uint8)0x08

/*
 * Following error will be reported when API service is called if Fr CC is not
 * in the expected POC state
 */
#define FR_59_RENESAS_E_INV_POCSTATE                (uint8)0x09

/*
 * Following error will be reported when API service is called with invalid
 * Payload length parameter value
 */
#define FR_59_RENESAS_E_INV_LENGTH                  (uint8)0x0A

/*
 * Following error will be reported when API service is called with invalid
 * LPdu index
 */
#define FR_59_RENESAS_E_INV_LPDU_IDX                (uint8)0x0B

/*
 * Following error will be reported when API service is called with invalid
 * FlexRay header CRC
 */
#define FR_59_RENESAS_E_INV_HEADERCRC               (uint8)0x0C

/*
 * Following error will be reported when API service is called with invalid
 * value passed as parameter Fr_ConfigParamIdx
 */
#define FR_59_RENESAS_E_INV_CONFIG_IDX              (uint8)0x0D

/*
 * Following error will be reported when API service is called with
 * invalid framelist size value
 */
#define FR_59_RENESAS_E_INV_FRAMELIST_SIZE          (uint8)0x0E

/*
 * Following error will be reported when API service is called with
 * invalid frameid value
 */
#define FR_59_RENESAS_E_INV_FRAMEID                 (uint8)0x0F

/*
 * Following error will be reported when API service is called with
 * wrong database address
 */
#define FR_59_RENESAS_E_INVALID_DATABASE            (uint8)0xEF

/*
 * Following error will be reported when API service is called if Parameter
 * cycle code exceeds 127
 */
#define FR_59_RENESAS_E_INV_CYCLE_CODE              (uint8)0xF0

/*
 * Following error will be reported if Fr_59_Renesas_AllowColdStart is called
 * for FlexRay controller which is not configured to coldstart
 */
#define FR_59_RENESAS_E_INV_CHI_COMMAND             (uint8)0xF1
/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/
/* Service ID of Fr Driver Initialization API */
#define FR_59_RENESAS_INIT_SID                      (uint8)0x1C

/* Service ID of Fr Driver Controller Initialization API */
#define FR_59_RENESAS_CONTROLLER_INIT_SID           (uint8)0x00

/*
 * Service ID of Start Communication API which changes the CC POC state from
 * POC: ready to POC: startup and then to POC: normal active or
 * POC: normal passive
 */
#define FR_59_RENESAS_STARTCOMMUNICATION_SID        (uint8)0x03

/*
 * Service ID of Allow cold start API which shall invokes the CC CHI command
 * ALLOW_COLDSTART
 */
#define FR_59_RENESAS_ALLOWCOLDSTART_SID            (uint8)0x23

/*
 * Service ID of all slots API which shall invokes the CC CHI command
 * ALL_SLOTS
 */
#define FR_59_RENESAS_ALLSLOTS_SID                  (uint8)0x24

/*
 * Service ID of halt communication API which shall invokes the CC CHI command
 * DEFERRED_HALT
 */
#define FR_59_RENESAS_HALTCOMMUNICATION_SID         (uint8)0x04

/*
 * Service ID of abort communication API which shall invokes the CC CHI command
 * FREEZE
 */
#define FR_59_RENESAS_ABORTCOMMUNICATION_SID        (uint8)0x05

/*
 * Service ID of send wakeup API which shall invokes the CC CHI command
 * WAKEUP
 */
#define FR_59_RENESAS_SENDWUP_SID                   (uint8)0x06

/* Service ID of set wakeup channel API which sets a wakeup channel */
#define FR_59_RENESAS_SETWAKEUPCHANNEL_SID          (uint8)0x07

/* Service ID of get poc status API which gets the POC status */
#define FR_59_RENESAS_GETPOCSTATUS_SID              (uint8)0x0A

/*
 * Service ID of transmit LPdu API which transmits data on the FlexRay
 * Network
 */
#define FR_59_RENESAS_TRANSMITTXLPDU_SID            (uint8)0x0B

/*
 * Service ID of cancel LPdu API which cancels the already pending
 * transmission
 */
#define FR_59_RENESAS_CANCELTXLPDU_SID              (uint8)0x2D

/*
 * Service ID of receive LPdu API which receive data on the FlexRay
 * Network
 */
#define FR_59_RENESAS_RECEIVERXLPDU_SID             (uint8)0x0C

/*
 * Service ID of check LPdu status API which receive data on the FlexRay
 * Network
 */
#define FR_59_RENESAS_CHECKTXLPDU_STATUS_SID        (uint8)0x0D

/* Service ID of prepare LPdu API which prepares the LPdu */
#define FR_59_RENESAS_PREPARELPDU_SID               (uint8)0x1F

/*
 * Service ID of reconfigure LPdu API which Reconfigures a given LPdu according
 * to the parameters (FrameId, Channel, CycleRepetition, CycleOffset,
 * PayloadLength, HeaderCRC) at runtime
 */
#define FR_59_RENESAS_RECONFIGLPDU_SID              (uint8)0x25

/*
 * Service ID of disable LPdu API which disables the hardware resource of a
 * LPdu for transmission/reception
 */
#define FR_59_RENESAS_DISABLELPDU_SID               (uint8)0x26

/*
 * Service ID of get global time API which gets the current global FlexRay
 * time
 */
#define FR_59_RENESAS_GETGLOBALTIME_SID             (uint8)0x10

/*
 * Service ID of get nm vector API which gets the current global FlexRay
 * time
 */
#define FR_59_RENESAS_GETNMVECTOR_SID               (uint8)0x22

/*
 * Service ID of get number of start up frames API which gets the current
 * number of startup frames seen on the cluster
 */
#define FR_59_RENESAS_GETNUMOFSTARTUPFRAMES_SID     (uint8)0x27

/*
 * Service ID of get channel status API which gets the channel status
 * information
 */
#define FR_59_RENESAS_GETCHANNELSTATUS_SID          (uint8)0x28

/*
 * Service ID of get clock correction API which gets the current clock
 * correction values
 */
#define FR_59_RENESAS_GETCLOCKCORRECTION_SID        (uint8)0x29

/*
 * Service ID of get syncframe list API which gets a list of syncframes
 * received or transmitted on channel A and channel B via the even and odd
 * communication cycle
 */
#define FR_59_RENESAS_GETSYNCFRAMELIST_SID          (uint8)0x2A

/*
 * Service ID of get wakeup tx status API which Gets the wakeup received
 * information from the FlexRay controller
 */
#define FR_59_RENESAS_GETWAKEUPRXSTATUS_SID         (uint8)0x2B

/* Service ID of set absolute timer API which Sets the absolute FlexRay timer */
#define FR_59_RENESAS_SETABSOLUTETIMER_SID          (uint8)0x11

/*
 * Service ID of cancel absolute timer API which stops the absolute FlexRay
 * timer
 */
#define FR_59_RENESAS_CANCELABSOLUTETIMER_SID       (uint8)0x13

/*
 * Service ID of enable absolute timer API which Enables the interrupt line of
 * an absolute FlexRay timer
 */
#define FR_59_RENESAS_ENABLEABSOLUTETIMER_IRQ_SID   (uint8)0x15

/*
 * Service ID of ack absolute timer interrupt API which resets the interrupt
 * condition of an absolute timer
 */
#define FR_59_RENESAS_ACKABSOLUTETIMERIRQ_SID       (uint8)0x17

/*
 * Service ID of disable absolute timer interrupt API which disables the
 * interrupt condition of an absolute timer
 */
#define FR_59_RENESAS_DISABLEABSOLUTETIMERIRQ_SID   (uint8)0x19

/*
 * Service ID of get absolute timer interrupt status API which gets IRQ status
 * of an absolute timer
 */
#define FR_59_RENESAS_GETABSOLUTETIMERIRQSTATUS_SID (uint8)0x20

/*
 * Service ID of get version information API which returns the version
 * information of this module
 */
#define FR_59_RENESAS_GETVERSIONINFO_SID            (uint8)0x1B

/*
 * Service ID of get version information API which reads a FlexRay protocol
 * configuration parameter for a particular FlexRay controller out of the
 *  module's configuration
 */
#define FR_59_RENESAS_READCCCONFIG_SID              (uint8)0x2E


/* DET Error - Call in invalid core */
#if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
#define FR_59_RENESAS_E_INVALID_CORE                (uint8)0xF2
#endif
/*
 * Service ID of transfer handler initialization API which activates the
 * input/output transfer feature
 */
#define FR_59_RENESAS_TRANSFERHANDLERINIT_SID       (uint8)0xA0
#define FR_59_RENESAS_TRANSFERQUEUETABLE_SID        (uint8)0xA1
#define FR_59_RENESAS_RECEIVEQUEUETABLE_SID         (uint8)0xA2
#define FR_59_RENESAS_INPUTTRANSFERDISABLE_SID      (uint8)0xA3
#define FR_59_RENESAS_OUTPUTTRANSFERDISABLE_SID     (uint8)0xA4
#define FR_59_RENESAS_USERINPUTTRANSFERREQUEST_SID  (uint8)0xA5
#define FR_59_RENESAS_USEROUTPUTTRANSFERREQUEST_SID (uint8)0xA6
#define FR_59_RENESAS_HALTINPUTQUEUE_SID            (uint8)0xA7
#define FR_59_RENESAS_SETCYCLECOUNTERFILTERING_SID  (uint8)0xA8

/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/
/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/
#define FR_59_RENESAS_START_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"

/* External Declaration for Fr Initialization API */
extern FUNC(void, FR_PUBLIC_CODE) Fr_59_Renesas_Init(const Fr_59_Renesas_ConfigType *Fr_ConfigPtr);

/* External Declaration for Fr Controller API */
extern FUNC(Std_ReturnType, FR_PUBLIC_CODE) Fr_59_Renesas_ControllerInit(uint8 Fr_CtrlIdx);
extern FUNC(Std_ReturnType, FR_PUBLIC_CODE)
    Fr_59_Renesas_CheckTxLPduStatus(uint8 Fr_CtrlIdx, uint16 Fr_LPduIdx, Fr_TxLPduStatusType *Fr_TxLPduStatusPtr,
                                    Fr_SlotAssignmentType *Fr_SlotAssignmentPtr);
#if (FR_59_RENESAS_RECONFIG_LPDU == STD_ON)
/* External Declaration for reconfiguration LPdu API */
extern FUNC(Std_ReturnType, FR_PUBLIC_CODE)
    Fr_59_Renesas_ReconfigLPdu(uint8 Fr_CtrlIdx,
                               uint16 Fr_LPduIdx, uint16 Fr_FrameId, Fr_ChannelType Fr_ChnlIdx,
                               uint8 Fr_CycleRepetition, uint8 Fr_CycleOffset, uint8 Fr_PayloadLength,
                               uint16 Fr_HeaderCRC);
#endif /* (FR_59_RENESAS_RECONFIG_LPDU == STD_ON) */
#if (FR_59_RENESAS_DISABLE_LPDU == STD_ON)
/* External Declaration for disable LPdu API */
extern FUNC(Std_ReturnType, FR_PUBLIC_CODE)Fr_59_Renesas_DisableLPdu(uint8 Fr_CtrlIdx, uint16 Fr_LPduIdx);
#endif /* FR_59_RENESAS_DISABLE_LPDU == STD_ON */
/* External Declaration for All slots API*/
extern FUNC(Std_ReturnType, FR_PUBLIC_CODE) Fr_59_Renesas_AllSlots(uint8 Fr_CtrlIdx);

/* External Declaration for get sync frame list API */
extern FUNC(Std_ReturnType, FR_PUBLIC_CODE)
    Fr_59_Renesas_GetSyncFrameList(uint8 Fr_CtrlIdx,
                                   uint8 Fr_ListSize, uint16 *Fr_ChannelAEvenListPtr, uint16 *Fr_ChannelBEvenListPtr,
                                   uint16 *Fr_ChannelAOddListPtr, uint16 *Fr_ChannelBOddListPtr);

/* External Declaration for get number of startup frames API */
extern FUNC(Std_ReturnType, FR_PUBLIC_CODE) Fr_59_Renesas_GetNumOfStartupFrames(uint8 Fr_CtrlIdx,
                                                                                uint8 *Fr_NumOfStartupFramesPtr);

/* External Declaration for cancel Tx LPdu API */
extern FUNC(Std_ReturnType, FR_PUBLIC_CODE) Fr_59_Renesas_CancelTxLPdu(uint8 Fr_CtrlIdx, uint16 Fr_LPduIdx);

/* External Declaration for Start Communication API */
extern FUNC(Std_ReturnType, FR_PUBLIC_CODE) Fr_59_Renesas_StartCommunication(uint8 Fr_CtrlIdx);

/* External Declaration for Allow cold start API */
extern FUNC(Std_ReturnType, FR_PUBLIC_CODE) Fr_59_Renesas_AllowColdstart(uint8 Fr_CtrlIdx);

/* External Declaration for Halt Communication API */
extern FUNC(Std_ReturnType, FR_PUBLIC_CODE) Fr_59_Renesas_HaltCommunication(uint8 Fr_CtrlIdx);

/* External Declaration for Abort Communication API */
extern FUNC(Std_ReturnType, FR_PUBLIC_CODE) Fr_59_Renesas_AbortCommunication(uint8 Fr_CtrlIdx);

/* External Declaration for Send WakeUp API */
extern FUNC(Std_ReturnType, FR_PUBLIC_CODE) Fr_59_Renesas_SendWUP(uint8 Fr_CtrlIdx);

/* External Declaration for set wakeup channel API */
extern FUNC(Std_ReturnType, FR_PUBLIC_CODE) Fr_59_Renesas_SetWakeupChannel(uint8 Fr_CtrlIdx, 
                                                                           Fr_ChannelType Fr_ChnlIdx);

/* External Declaration for get POC status API */
extern FUNC(Std_ReturnType, FR_PUBLIC_CODE) Fr_59_Renesas_GetPOCStatus(uint8 Fr_CtrlIdx,
                                                                       Fr_POCStatusType *Fr_POCStatusPtr);

/* External Declaration for transmit Tx LPdu API */
extern FUNC(Std_ReturnType, FR_PUBLIC_CODE)
    Fr_59_Renesas_TransmitTxLPdu(uint8 Fr_CtrlIdx,
                                 uint16 Fr_LPduIdx, const uint8 *Fr_LSduPtr, uint8 Fr_LSduLength,
                                 Fr_SlotAssignmentType *Fr_SlotAssignmentPtr);

/* External Declaration for receive Rx LPdu API */
extern FUNC(Std_ReturnType, FR_PUBLIC_CODE)
    Fr_59_Renesas_ReceiveRxLPdu(uint8 Fr_CtrlIdx,
                                uint16 Fr_LPduIdx, uint8 *Fr_LSduPtr, Fr_RxLPduStatusType *Fr_LPduStatusPtr,
                                uint8 *Fr_LSduLengthPtr, Fr_SlotAssignmentType *Fr_SlotAssignmentPtr);

/* External Declaration for get global time API */
extern FUNC(Std_ReturnType, FR_PUBLIC_CODE) Fr_59_Renesas_GetGlobalTime(uint8 Fr_CtrlIdx,
                                                                        uint8 *Fr_CyclePtr, uint16 *Fr_MacroTickPtr);

/* External Declaration for get nm vector API */
extern FUNC(Std_ReturnType, FR_PUBLIC_CODE) Fr_59_Renesas_GetNmVector(uint8 Fr_CtrlIdx, uint8 *Fr_NmVectorPtr);

/* External Declaration for get channel status API */
extern FUNC(Std_ReturnType, FR_PUBLIC_CODE)
    Fr_59_Renesas_GetChannelStatus(uint8 Fr_CtrlIdx, uint16 *Fr_ChannelAStatusPtr, uint16 *Fr_ChannelBStatusPtr);

/* External Declaration for get clock correction API */
extern FUNC(Std_ReturnType, FR_PUBLIC_CODE)
    Fr_59_Renesas_GetClockCorrection(uint8 Fr_CtrlIdx, sint16 *Fr_RateCorrectionPtr, sint32 *Fr_OffsetCorrectionPtr);

/* External Declaration for get wakeup rx status API */
extern FUNC(Std_ReturnType, FR_PUBLIC_CODE) Fr_59_Renesas_GetWakeupRxStatus(uint8 Fr_CtrlIdx,
                                                                            uint8 *Fr_WakeupRxStatusPtr);

/* External Declaration for set Absolute timer API */
extern FUNC(Std_ReturnType, FR_PUBLIC_CODE)
    Fr_59_Renesas_SetAbsoluteTimer(uint8 Fr_CtrlIdx, uint8 Fr_AbsTimerIdx, uint8 Fr_Cycle, uint16 Fr_Offset);

/* External Declaration for cancel absolute timer API */
extern FUNC(Std_ReturnType, FR_PUBLIC_CODE) Fr_59_Renesas_CancelAbsoluteTimer(uint8 Fr_CtrlIdx, uint8 Fr_AbsTimerIdx);

/* External Declaration for enable absolute timer interrupt API */
extern FUNC(Std_ReturnType, FR_PUBLIC_CODE) Fr_59_Renesas_EnableAbsoluteTimerIRQ(uint8 Fr_CtrlIdx,
                                                                                 uint8 Fr_AbsTimerIdx);

/* External Declaration for acknowledge Absolute Timer Interrupt API */
extern FUNC(Std_ReturnType, FR_PUBLIC_CODE) Fr_59_Renesas_AckAbsoluteTimerIRQ(uint8 Fr_CtrlIdx, uint8 Fr_AbsTimerIdx);

/* External Declaration for disable absolute timer interrupt API */
extern FUNC(Std_ReturnType, FR_PUBLIC_CODE)
    Fr_59_Renesas_DisableAbsoluteTimerIRQ(uint8 Fr_CtrlIdx, uint8 Fr_AbsTimerIdx);

/* External Declaration for get absolute timer interrupt status API */
extern FUNC(Std_ReturnType, FR_PUBLIC_CODE)
    Fr_59_Renesas_GetAbsoluteTimerIRQStatus(uint8 Fr_CtrlIdx, uint8 Fr_AbsTimerIdx, boolean *Fr_IRQStatusPtr);

/* External Declaration for read CC Configuration API */
extern FUNC(Std_ReturnType, FR_PUBLIC_CODE)
    Fr_59_Renesas_ReadCCConfig(uint8 Fr_CtrlIdx, uint8 Fr_ConfigParamIdx, uint32 *Fr_ConfigParamValuePtr);

#if (FR_59_RENESAS_PREPARE_LPDU == STD_ON)
/* External Declaration for prepare LPdu API */
extern FUNC(Std_ReturnType, FR_PUBLIC_CODE) Fr_59_Renesas_PrepareLPdu(uint8 Fr_CtrlIdx, uint16 Fr_LPduIdx);
#endif /* FR_59_RENESAS_PREPARE_LPDU == STD_ON */

#if (FR_59_RENESAS_VERSION_INFO_API == STD_ON)
extern FUNC(void, FR_PUBLIC_CODE) Fr_59_Renesas_GetVersionInfo(Std_VersionInfoType *VersioninfoPtr);
#endif

#if ((FR_59_RENESAS_ENABLE_INPUT_TX_HANDLER == STD_ON) || (FR_59_RENESAS_ENABLE_OUTPUT_RX_HANDLER == STD_ON) || \
     (FR_59_RENESAS_ENABLE_OUTPUT_RX_FIFO_HANDLER == STD_ON))
extern FUNC(Std_ReturnType, FR_PUBLIC_CODE)
    Fr_59_Renesas_TransferHandlerInit(uint8 Fr_CtrlIdx,
                                      volatile Fr_59_Renesas_OutputPointerTableType *Fr_OutputTableContentPtr,
                                      volatile Fr_59_Renesas_OutputPointerTableType *Fr_FIFOTableContentPtr);
#endif

#if (FR_59_RENESAS_ENABLE_INPUT_TX_HANDLER == STD_ON)
extern FUNC(Std_ReturnType, FR_PUBLIC_CODE)
    Fr_59_Renesas_TransferQueueTable(uint8 Fr_CtrlIdx,
                                     volatile Fr_59_Renesas_InputPointerTableType *Fr_InputTableContentPtr);

extern FUNC(Std_ReturnType, FR_PUBLIC_CODE) Fr_59_Renesas_InputTransferDisable(uint8 Fr_CtrlIdx);
#endif

#if ((FR_59_RENESAS_ENABLE_OUTPUT_RX_HANDLER == STD_ON) || (FR_59_RENESAS_ENABLE_OUTPUT_RX_FIFO_HANDLER == STD_ON))
extern FUNC(Std_ReturnType, FR_PUBLIC_CODE)
    Fr_59_Renesas_ReceiveQueueTable(uint8 Fr_CtrlIdx,
                                    volatile Fr_59_Renesas_OutputPointerTableType *Fr_OutputTableContentPtr);
#endif

#if ((FR_59_RENESAS_ENABLE_OUTPUT_RX_HANDLER == STD_ON) || (FR_59_RENESAS_ENABLE_OUTPUT_RX_FIFO_HANDLER == STD_ON))
extern FUNC(Std_ReturnType, FR_PUBLIC_CODE) Fr_59_Renesas_OutputTransferDisable(uint8 Fr_CtrlIdx);
#endif

#if ((FR_59_RENESAS_ENABLE_INPUT_TX_HANDLER == STD_ON) && (FR_59_RENESAS_ENABLE_USER_REQUEST_INPUT_TRANSFER == STD_ON))
extern FUNC(Std_ReturnType, FR_PUBLIC_CODE)
    Fr_59_Renesas_UserInputTransferRequest(uint8 Fr_CtrlIdx,
                                           volatile Fr_59_Renesas_InputPointerTableType *Fr_InputTableContentPtr);
#endif

#if ((FR_59_RENESAS_ENABLE_OUTPUT_RX_HANDLER == STD_ON) && \
     (FR_59_RENESAS_ENABLE_USER_REQUEST_OUTPUT_TRANSFER == STD_ON))
extern FUNC(Std_ReturnType, FR_PUBLIC_CODE)
    Fr_59_Renesas_UserOutputTransferRequest(uint8 Fr_CtrlIdx,
                                            volatile Fr_59_Renesas_OutputPointerTableType *Fr_OutputTableContentPtr);
#endif

#if (FR_59_RENESAS_ENABLE_INPUT_TX_HANDLER == STD_ON)
extern FUNC(Std_ReturnType, FR_PUBLIC_CODE)
    Fr_59_Renesas_HaltInputQueue(uint8 Fr_CtrlIdx,
                                 volatile Fr_59_Renesas_InputPointerTableType *Fr_InputTableContentPtr);
#endif

#if (FR_59_RENESAS_SET_CYCLE_COUNTER_FILTERING_API == STD_ON)
extern FUNC(Std_ReturnType, FR_PUBLIC_CODE)
    Fr_59_Renesas_SetCycleCounterFiltering(uint8 Fr_CtrlIdx,
                                           uint8 Fr_AbsTimerIdx, uint8 Fr_CycleCode, uint16 Fr_Offset);
#endif
#define FR_59_RENESAS_STOP_SEC_PUBLIC_CODE
#include "Fr_59_Renesas_MemMap.h"

#define FR_59_RENESAS_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Fr_59_Renesas_MemMap.h"
/* Declaration for Fr Database */
extern CONST(Fr_59_Renesas_ConfigType, FR_CONFIG_DATA) Fr_59_Renesas_GaaConfiguration[];                                /* PRQA S 3684 # JV-01 */
#define FR_59_RENESAS_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Fr_59_Renesas_MemMap.h"

#endif /* FR_59_RENESAS_H */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
