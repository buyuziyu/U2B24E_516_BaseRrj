/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Eth_Types.h                                                                                         */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Provision of Ethernet Component specific types used within the module.                                             */
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
 * 2.4.1: 30/06/2025    : Remove the SW-VERSION from header of file
 * 2.4.0: 30/06/2025    : Update SW-VERSION for RH850/Ver22.01.00 (D) U2Ax release
 * 2.3.1: 31/03/2025    : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 * 2.3.0: 28/02/2025    : - As per ticket ARDAACL-53039:
 *                         Change Eth_HwReadMiiBit and Eth_HwWriteMiiBit from void to return function 
 *                      : Updated QA-C 9.5.0 comments
 * 2.2.0: 31/12/2024    : Update SW-VERSION for Ver22.02.00(D) U2Bx Final Release
 *        26/11/2024    : Updated QA-C 9.5.0 comments
 * 2.1.2: 31/10/2024    : Increase SW-VERSION to 2.1.2
 * 2.1.1: 30/08/2024    : Add T1s interface into Eth_MediaInterfaceType
 *        16/07/2024    : Add pDemEventUnintendedIntChk
 *                      : Add definition of Eth_GwcaRegValue struct, Eth_GlobalPauseConfiguration struct, 
 *                        Eth_BothCoreConfiguration struct, Eth_TsnaRegValue struct, Eth_SWConfigType struct.
 *                      : Add definition of stGlobalPauseConfiguration pointer, stBothCoreConfiguration pointer.
 *                      : Update range of ulCtrlConfigIdx
 *                      : Update QAC message.
 *                      : Update Eth_ConfigType struct elements.
 * 2.1.0: 06/04/2024    : Added Eth_SpiStatusType 
 *                      : Update Eth_ConfigType struct elements.
 *                      : Remove QA-C Warning 1534, 1536
 *                      : Added QA-C warning 3432 according to QA-C 10.3.0
 *                      : For support Function pointer, Added pHwSetIncrementTimeForGptp, pHwSetOffsetTimeForGptp, 
 *                        pHwGetCurrentTime, pHwGetEgressTimeStamp, pHwGetIngressTimeStamp into Eth_HwFuncTableType
 *                      : For support Function pointer, Added Eth_HwFuncTableType to assign function address
 * 2.0.1: 18/10/2023    : Added QA-C Warning 1534, 1536 according to QA-C 10.3.0
 *                        Added QA-C 10.3.0 comments 
 *        11/10/2023    : Add define TH_AR_R22_11_VERSION for support R22-11
 * 2.0.0: 25/05/2023    : Change AR version name and Update condition to define ETH_DEM_REPORT_ERROR for R21_11
 *        20/04/2023    : Add define ETH_AR_2111_VERSION for support R21-11 
 * 1.5.2: 28/01/2022    : Add the ETH_HEADER_SIZE, ETH_MACADDR_SIZE, ETH_SRC_DST_ADDRESS_SIZE,
 *                        ETH_ETHERTYPE_SIZE, ETH_VLAN_SIZE and ETH_FCS_LENGTH macros.
 * 1.5.0: 07/10/2021    : For support U2Bx, changed the definition location of the include file.
 *                        For support U2Bx, removed the extern definition of the following global variables.
 *                        Eth_GaaDemEventAccess, Eth_GaaDemEventRxFramesLost, Eth_GaaDemEventCRC,
 *                        Eth_GaaDemEventUnderSizeFrame, Eth_GaaDemEventOverSizeFrame, Eth_GaaDemEventAlignment,
 *                        Eth_GaaDemEventSinglecollision, Eth_GaaDemEventMultiplecollision,
 *                        Eth_GaaDemEventLatecollision, Eth_GaaDemEventIntInconsistent,
 *                        Eth_GaaDemEventRegisterCorruption and Eth_GaaDemEventDmaError.
 * 1.4.2: 24/08/2021    : Modify the format to 120 characters
 * 1.4.1: 24/06/2021    : Add ETH_AR_R19_11_VERSION for R19-11 support.
 *        07/05/2021    : Changes to support U2Bx devices.
 *                        Remove vendor ID from the file name, API names
 *                        and parameters according to BSW00347 requirement
 *        06/07/2021    : Updated QA-C 9.5.0 comments.
 * 1.3.0: 09/12/2020    : Update value for ETH_DEM_NOT_CONFIGURED to 0x0000
 * 1.2.0: 13/07/2020    : Release
 *        29/07/2020    : Add QAC 9.3.1 comment.
 * 1.1.0: 19/06/2020    : Release
 * 1.0.1: 04/06/2020    : To support Transmit/Receive interrupts for each controller.
 *                        Removed unnecessary code.
 *                        Updated static analysis result.
 * 1.0.0: 25/03/2020    : Initial Version
 */
/**********************************************************************************************************************/
#ifndef ETH_TYPES_H
#define ETH_TYPES_H

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:0342)    : Using the glue operator '##'.                                                                */
/* Rule                : CERTCCM PRE05, MISRA C:2012 Rule-20.10                                                       */
/* JV-01 Justification : This can be accepted, due to the implementation is following AUTOSAR standard rule for       */
/*                       SchM module's name                                                                           */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3630)    : The implementation of this struct/union type should be hidden.                               */
/* Rule                : MISRA C:2012 Dir-4.8                                                                         */
/* JV-01 Justification : This is accepted. Redudant of struct or union type has no affect to driver operation         */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE Rule CWE-398, CWE-569                                            */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is accepted. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for Type definitions */
#include "Eth_GeneralTypes.h"


/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
#define ETH_AR_R19_11_VERSION                 450
#define ETH_AR_431_VERSION                    431
#define ETH_AR_422_VERSION                    422
#define ETH_AR_R21_11_VERSION                 470
#define ETH_AR_R22_11_VERSION                 480
/* AUTOSAR release version information */
#define ETH_TYPES_AR_RELEASE_MAJOR_VERSION    ETH_AR_RELEASE_MAJOR_VERSION
#define ETH_TYPES_AR_RELEASE_MINOR_VERSION    ETH_AR_RELEASE_MINOR_VERSION
#define ETH_TYPES_AR_RELEASE_REVISION_VERSION ETH_AR_RELEASE_REVISION_VERSION

/* Module Software version information */
#define ETH_TYPES_SW_MAJOR_VERSION            ETH_SW_MAJOR_VERSION
#define ETH_TYPES_SW_MINOR_VERSION            ETH_SW_MINOR_VERSION

/***********************************************************************************************************************
**                                                 GLOBAL DATA TYPES                                                  **
***********************************************************************************************************************/

/***********************************************************************************************************************
                        Section: MACROS
***********************************************************************************************************************/
/* Macros for boolean variables */
#define ETH_FALSE              (boolean)0
#define ETH_TRUE               (boolean)1

/* Byte length of Ethernet header */
#define ETH_HEADER_SIZE          14UL
/* Byte length of MAC address */
#define ETH_MACADDR_SIZE         6UL
#define ETH_SRC_DST_ADDRESS_SIZE 12UL
#define ETH_ETHERTYPE_SIZE       2UL
#define ETH_VLAN_SIZE            4UL
#define ETH_FCS_LENGTH           4UL

#define ETH_DEM_NOT_CONFIGURED 0x0000

#define ETH_HWIP_ETNC            0U
#define ETH_HWIP_ETNB            1U
#define ETH_HWIP_ETND            2U
#define ETH_HWIP_ETNE            3U
#define ETH_HWIP_ETNF            4U
/***********************************************************************************************************************
                        Section: Enumerators
***********************************************************************************************************************/

/***********************************************************************************************************************
**  Enum: Eth_MacLayerSpeedType                                                                                       **
**                                                                                                                    **
**  Mac speed                                                                                                         **
**                                                                                                                    **
**  Members:                                                                                                          **
**    ETH_MAC_LAYER_SPEED_10M    - 10MBps                                                                             **
**    ETH_MAC_LAYER_SPEED_100M   - 100MBps                                                                            **
**    ETH_MAC_LAYER_SPEED_1G     - 1GBps                                                                              **
**    ETH_MAC_LAYER_SPEED_2500M  - 2.5GBps                                                                            **
**    ETH_MAC_LAYER_SPEED_10G    - 10GBps                                                                             **
***********************************************************************************************************************/
typedef enum ETag_Eth_MacLayerSpeedType
{
  ETH_MAC_LAYER_SPEED_10M = 0,
  ETH_MAC_LAYER_SPEED_100M,
  ETH_MAC_LAYER_SPEED_1G,
  ETH_MAC_LAYER_SPEED_2500M,
  ETH_MAC_LAYER_SPEED_10G
} Eth_MacLayerSpeedType;

/***********************************************************************************************************************
**  Enum: Eth_DuplexModeType                                                                                          **
**                                                                                                                    **
**  Mac duplex mode                                                                                                   **
**                                                                                                                    **
**  Members:                                                                                                          **
**    ETH_HALF_DUPLEX  - half duplex                                                                                  **
**    ETH_FULL_DUPLEX  - full duplex                                                                                  **
**    ETH_T1S_MODE     - t1s mode                                                                                     **
***********************************************************************************************************************/
typedef enum ETag_Eth_DuplexModeType
{
  ETH_HALF_DUPLEX = 0,
  ETH_FULL_DUPLEX,
  ETH_T1S_MODE
} Eth_DuplexModeType;

/***********************************************************************************************************************
**  Type: Eth_MediaInterfaceType                                                                                      **
**                                                                                                                    **
**  Setting option                                                                                                    **
**                                                                                                                    **
**  Members:                                                                                                          **
**    ETH_MII   - select MII                                                                                          **
**    ETH_RMII  - select RMII                                                                                         **
**    ETH_SGMII - select SGMII                                                                                        **
**    ETH_T1S   - select T1S                                                                                          **
***********************************************************************************************************************/
typedef enum ETag_Eth_MediaInterfaceType
{
  ETH_MII = 0,
  ETH_RMII,
  ETH_SGMII,
  ETH_T1S
} Eth_MediaInterfaceType;

/***********************************************************************************************************************
**  Type: Eth_OptionType                                                                                              **
**                                                                                                                    **
**  Setting option                                                                                                    **
**                                                                                                                    **
**  Members:                                                                                                          **
**    ETH_DISABLE  - setting is disabled                                                                              **
**    ETH_ENABLE   - setting is enabled                                                                               **
***********************************************************************************************************************/
typedef enum ETag_Eth_OptionType
{
  ETH_DISABLE = 0,
  ETH_ENABLE
} Eth_OptionType;

/***********************************************************************************************************************
                        Section: Structures
***********************************************************************************************************************/

/***********************************************************************************************************************
  Type: Eth_EthConfigType

  Structure for Ethernet Configuration
  Overall Module Configuration Data Structure

  Members:
    enEthSpeed              - Ethernet Speed configured
    enEthDuplex             - Ethernet Duplex Mode configured
    enInternalLoopBackMode  - Enable InternalLoopBack Mode
    enEthPHYInterface       - PHY Interface (MII/RMII/SGMII)
    enTxInterruptMode       - Tx interrupt enable.
    enRxInterruptMode       - Rx interrupt enable.
*/

/* Data Structure for ETH required for Initializing the ETH controller */
typedef struct STag_Eth_HWIPType
{
  /* Pointer to ETH driver ETH Unit configuration */
  VAR(uint8, ETH_CONFIG_DATA) ucIndex;
} Eth_HWIPType;

/***********************************************************
Struct: Eth_SpiStatusType

Statistic counter for diagnostics.

Members:
SpiStatusRegister    - Bit mapped status defined by OA TC6 [26] to notify following information:
                       0x00: Transmit_Protocol_Error,
                       0x01: Transmit_Buffer_Overflow_Error,
                       0x02: Transmit_Buffer_Underflow_Error,
                       0x03: Receive_Buffer_Overflow_Error,
                       0x04: Loss_Framing_error,
                       0x05: Header_Error,
                       0x06: Reset_Complete,
                       0x07: PHY_Interrupt,
                       0x08: Transmit_Timestamp Capture_Available_A,
                       0x09: Transmit_Timestamp Capture_Available_B,
                       0x0A: Transmit_Timestamp Capture_Available_C,
                       0x0B: Transmit_Frame_Check_Sequence_Error,
                       0x0C: Control_Data_Protection_Error,
                       0x0D - 0xFF: Reserved.
Sync                 - Synchronization configuration as defined in the OA TC6 [26]. 
                       true: MACPHY has been reset and is not configured. 
                       false: MACPHY is configured.
BufferStatusTxCredit - Contains the number of consecutive transmited data chunks of
                       Ethernet frame the SPI host can write without overflowing the MAC.
BufferStatusRxCredit - Contains the number of additional received data chunks of Ethernet
                       frame currently available for the SPI host to read.
*/
typedef struct                                                                                                          /* PRQA S 3630 # JV-01 */
{
  uint32 SpiStatusRegister;
  boolean Sync;
  uint8 BufferStatusTxCredit;
  uint8 BufferStatusRxCredit;
} Eth_SpiStatusType;

/* Do not move the location of this include file */
#include "Eth_Cfg.h"

typedef struct STag_Eth_EthConfigType                                                                                   /* PRQA S 3630 # JV-01 */
{
  Eth_MacLayerSpeedType enEthSpeed;
  Eth_DuplexModeType enEthDuplex;
  Eth_OptionType enInternalLoopBackMode;
  Eth_MediaInterfaceType enEthPHYInterface;
  Eth_OptionType enTxInterruptMode;
  Eth_OptionType enRxInterruptMode;
} Eth_EthConfigType;

#if (ETH_MACRO_ETNE == STD_ON)
/***********************************************************
  Type: Eth_GwcaRegValue

  Structure for GWCA register setting.

  Members:
    ulGWVCCValue    - GWCA VLAN Control Configuration.
    ulGWVTCValue    - GWCA VLAN TAG Configuration.
    ulGWTTFCValue   - GWCA Transmission TAG Filtering Configuration.
    ulGWSCR0Value   - GWCA Security Configuration Register 0.
    ulGWGRLCValue   - GWCA Global Rate Limiter Configuration.
    ulGWGRLULCValue - GWCA Global Rate Limiter Upper Limit Configuration.
*/
typedef struct STagEth_GwcaRegValue
{
  uint32 ulGWVCCValue;
  uint32 ulGWVTCValue;
  uint32 ulGWTTFCValue;
  uint32 ulGWSCR0Value;
  uint32 ulGWGRLCValue;
  uint32 ulGWGRLULCValue;
} Eth_GwcaRegValue;

typedef struct STagEth_GlobalPauseConfiguration
{
  Eth_OptionType enGlobalPause;
  uint32 ulPauseAssertionLevel;
  uint32 ulPauseDeAssertionLevel;
} Eth_GlobalPauseConfiguration;

typedef struct STagEth_BothCorePauseLevelType
{
  uint32 ulBothCorePauseAssertionLevel;
  uint32 ulBothCorePauseDeAssertionLevel;
} Eth_BothCorePauseLevelType;

typedef struct STagEth_BothCoreConfiguration
{
  uint32 ulBothCorePortFwdVectorId;
  uint32 aaBothCorePortFwdCsd[2];
  Eth_BothCorePauseLevelType stBothCorePauseLevelConfig[2];
} Eth_BothCoreConfiguration;

#endif /* ETH_MACRO_ETNE == STD_ON */

#if (ETH_MACRO_ETNE == STD_ON)
typedef struct STagEth_TsnaRegValue
{
  uint32 ulEAVCCValue;
  uint32 ulEAVTCValue;
  uint32 ulEARTFCValue;
} Eth_TsnaRegValue;

typedef struct STag_Eth_SWConfigType
{
  Eth_TsnaRegValue stTsnaRegValue;
} Eth_SWConfigType;
#endif /* ETH_MACRO_ETNE == STD_ON */

typedef struct STag_Eth_CtrlConfigType                                                                                  /* PRQA S 3630 # JV-01 */
{
  uint8 aaEthMACAddr[6];
  P2CONST(Eth_EthConfigType, TYPEDEF, ETH_APPL_CONST) pEthConfig;
  P2CONST(void, TYPEDEF, ETH_APPL_CONST) pHwUnitConfig;
  #if (ETH_MACRO_ETNE == STD_ON)
  Eth_SWConfigType stSWConfig;
  #endif
} Eth_CtrlConfigType;

typedef struct STag_Eth_ConfigType
{
  /* Database start value - ETH_DBTOC_VALUE */
  uint32 ulStartOfDbToc;
  P2CONST(Eth_CtrlConfigType, TYPEDEF, ETH_APPL_CONST) pCtrlConfig;
  P2VAR(uint16, AUTOMATIC, ETH_VAR_INIT) pDemEventAccess;                                                               /* PRQA S 3432 # JV-01 */
  P2VAR(uint16, AUTOMATIC, ETH_VAR_INIT) pDemEventRxFramesLost;                                                         /* PRQA S 3432 # JV-01 */
  P2VAR(uint16, AUTOMATIC, ETH_VAR_INIT) pDemEventCRC;                                                                  /* PRQA S 3432 # JV-01 */
  P2VAR(uint16, AUTOMATIC, ETH_VAR_INIT) pDemEventUnderSizeFrame;                                                       /* PRQA S 3432 # JV-01 */
  P2VAR(uint16, AUTOMATIC, ETH_VAR_INIT) pDemEventOverSizeFrame;                                                        /* PRQA S 3432 # JV-01 */
  P2VAR(uint16, AUTOMATIC, ETH_VAR_INIT) pDemEventAlignment;                                                            /* PRQA S 3432 # JV-01 */
  P2VAR(uint16, AUTOMATIC, ETH_VAR_INIT) pDemEventSinglecollision;                                                      /* PRQA S 3432 # JV-01 */
  P2VAR(uint16, AUTOMATIC, ETH_VAR_INIT) pDemEventMultiplecollision;                                                    /* PRQA S 3432 # JV-01 */
  P2VAR(uint16, AUTOMATIC, ETH_VAR_INIT) pDemEventLatecollision;                                                        /* PRQA S 3432 # JV-01 */
  #if ( ETH_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  P2VAR(uint16, AUTOMATIC, ETH_VAR_INIT) pDemEventIntInconsistent;                                                      /* PRQA S 3432 # JV-01 */
  #endif
  P2VAR(uint16, AUTOMATIC, ETH_VAR_INIT) pDemEventDmaError;                                                             /* PRQA S 3432 # JV-01 */
  P2VAR(uint16, AUTOMATIC, ETH_VAR_INIT) pDemEventEccError;                                                             /* PRQA S 3432 # JV-01 */
  #if (ETH_MACRO_ETNB == STD_ON || ETH_MACRO_ETNF ==STD_ON)
  #if (ETH_GLOBAL_TIME_SUPPORT == STD_ON)
  P2VAR(uint16, AUTOMATIC, ETH_VAR_INIT) pDemEventTimerincFailed;                                                       /* PRQA S 3432 # JV-01 */
  P2VAR(uint16, AUTOMATIC, ETH_VAR_INIT) pDemEventTimeroffsetFailed;                                                    /* PRQA S 3432 # JV-01 */
  #endif
  #if ((ETH_REGISTER_CHECK_INITTIME == STD_ON) || (ETH_REGISTER_CHECK_RUNTIME == STD_ON))
  P2VAR(uint16, AUTOMATIC, ETH_VAR_INIT) pDemEventRegisterCorruption;                                                   /* PRQA S 3432 # JV-01 */
  #endif
  #endif
  #if (ETH_MACRO_ETNE == STD_ON)
  #if (ETH_UNINTENDED_INTERRUPT_CHECK == STD_ON)
  P2VAR(uint16, AUTOMATIC, ETH_VAR_INIT) pDemEventUnintendedIntChk;                                                     /* PRQA S 3432 # JV-01 */
  #endif
  #endif
  P2CONST(uint32, AUTOMATIC, ETH_CONFIG_DATA) pTotalCtrlConfig;
  uint32 ulCtrlConfigIdx[ETH_TOTAL_CORE_CONFIG][ETH_TOTAL_CTRL_CONFIG];
  P2VAR(Eth_StateType, AUTOMATIC, ETH_VAR_INIT) pDriverState;                                                           /* PRQA S 3432 # JV-01 */
  #if (ETH_MULTI_CORE_SUPPORT == STD_ON)
  P2CONST(uint8, AUTOMATIC, ETH_VAR_INIT) pCoreId2Index;
  #endif
  #if (ETH_MACRO_ETNE == STD_ON)
  Eth_GwcaRegValue stGwcaRegValue;
  Eth_GlobalPauseConfiguration stGlobalPauseConfiguration[2];
  Eth_BothCoreConfiguration stBothCoreConfiguration;
  #endif /* ETH_MACRO_ETNE == STD_ON */
} Eth_ConfigType;
/* Data Structure for ETH function Table */
typedef struct STag_Eth_HwFuncTableType                                                                                 /* PRQA S 3630 # JV-01 */
{
  P2FUNC(void, ETH_PRIVATE_CODE, pInitializeBuffer)(CONST(uint32, AUTOMATIC) LulCtrlIdx);                               /* PRQA S 3432 # JV-01 */
  P2FUNC(void, ETH_PRIVATE_CODE, pPreprocessBuffer)(CONST(uint32, AUTOMATIC) LulCtrlIdx);                               /* PRQA S 3432 # JV-01 */
  P2FUNC(BufReq_ReturnType, ETH_PRIVATE_CODE, pGetTxBuffer)                                                             /* PRQA S 3432 # JV-01 */
                   (CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint8, AUTOMATIC) LucPriority,
                    CONSTP2VAR(Eth_BufIdxType, AUTOMATIC, ETH_APPL_DATA) LpBufIdxPtr,                                   /* PRQA S 3432 # JV-01 */
                    CONSTP2VAR(uint8 *, AUTOMATIC, ETH_APPL_DATA) LpBufPtr,                                             /* PRQA S 3432 # JV-01 */
                    CONSTP2VAR(uint16, AUTOMATIC, ETH_APPL_DATA) LenBytePtr);                                           /* PRQA S 3432 # JV-01 */
  P2FUNC(void, ETH_PRIVATE_CODE, pReleaseTxBuffer)                                                                      /* PRQA S 3432 # JV-01 */
        (CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulBufIdx);
  P2FUNC(Std_ReturnType, ETH_PRIVATE_CODE, pCheckProvideBuffer)                                                         /* PRQA S 3432 # JV-01 */
        (CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulBufIdx);
  P2FUNC(void, ETH_PRIVATE_CODE, pPreprocessFrame)                                                                      /* PRQA S 3432 # JV-01 */
                       (CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulBufIdx,
                        CONST(uint32, AUTOMATIC) LulFrameType,
                        CONSTP2CONST(uint8, AUTOMATIC, ETH_APPL_DATA) LpPhysAddrPtr,
                        CONSTP2VAR(uint16, AUTOMATIC, ETH_APPL_DATA) LpPayloadLen);                                     /* PRQA S 3432 # JV-01 */
  P2FUNC(Eth_BufHandlerType *, ETH_PRIVATE_CODE, pFindTxBufferHandler)                                                  /* PRQA S 3432 # JV-01 */
        (CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulBufIdx);
  P2FUNC(Std_ReturnType, ETH_PRIVATE_CODE, pHwInit)(CONST(uint32, AUTOMATIC) LulCtrlIdx);                               /* PRQA S 3432 # JV-01 */
  #if (ETH_DEINIT_API == STD_ON)
  P2FUNC(Std_ReturnType, ETH_PRIVATE_CODE, pHwDeInit)                                                                   /* PRQA S 3432 # JV-01 */
        (CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(boolean, AUTOMATIC) ForceReset);
  #endif
  P2FUNC(Std_ReturnType, ETH_PRIVATE_CODE, pHwDisableController)(CONST(uint32, AUTOMATIC) LulCtrlIdx);                  /* PRQA S 3432 # JV-01 */
  P2FUNC(Std_ReturnType, ETH_PRIVATE_CODE, pHwEnableController)(CONST(uint32, AUTOMATIC) LulCtrlIdx);                   /* PRQA S 3432 # JV-01 */
  P2FUNC(Std_ReturnType, ETH_PRIVATE_CODE, pHwTransmit)                                                                 /* PRQA S 3432 # JV-01 */
        (CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulBufIdx,
         CONST(uint32, AUTOMATIC) LulLenByte, CONST(boolean, AUTOMATIC) LblConfirmation);
  #if (ETH_GET_COUNTER_VALUES_API == STD_ON)
  P2FUNC(void, ETH_PRIVATE_CODE, pHwGetCounterValues)(CONST(uint32, AUTOMATIC) LulCtrlIdx,                              /* PRQA S 3432 # JV-01 */
                           CONSTP2VAR(Eth_CounterType, AUTOMATIC, ETH_APPL_DATA) LpCounterPtr);                         /* PRQA S 3432 # JV-01 */
  #endif
  #if (ETH_GET_RX_STATS_API == STD_ON)
  P2FUNC(void, ETH_PRIVATE_CODE, pHwGetRxStats)(CONST(uint32, AUTOMATIC) LulCtrlIdx,                                    /* PRQA S 3432 # JV-01 */
                                                CONSTP2VAR(Eth_RxStatsType, AUTOMATIC, ETH_APPL_DATA) LpRxStats);       /* PRQA S 3432 # JV-01 */
  #endif
  #if (ETH_GET_TX_STATS_API == STD_ON)
  P2FUNC(void, ETH_PRIVATE_CODE, pHwGetTxStats)(CONST(uint32, AUTOMATIC) LulCtrlIdx,                                    /* PRQA S 3432 # JV-01 */
                                                CONSTP2VAR(Eth_TxStatsType, AUTOMATIC, ETH_APPL_DATA) LpTxStats);       /* PRQA S 3432 # JV-01 */
  #endif
  #if (ETH_GET_TX_ERROR_COUNTER_VALUES_API == STD_ON)
  P2FUNC(void, ETH_PRIVATE_CODE, pHwGetTxErrorCounterValues)                                                            /* PRQA S 3432 # JV-01 */
      (CONST(uint32, AUTOMATIC) LulCtrlIdx,
       CONSTP2VAR(Eth_TxErrorCounterValuesType, AUTOMATIC, ETH_APPL_DATA) LpTxErrorCounterValues);                      /* PRQA S 3432 # JV-01 */
  #endif
  P2FUNC(void, ETH_PRIVATE_CODE, pHwMainFunction)(CONST(uint32, AUTOMATIC) LulCtrlIdx);                                 /* PRQA S 3432 # JV-01 */
  P2FUNC(void, ETH_PRIVATE_CODE, pHwTxConfirmation)(CONST(uint32, AUTOMATIC) LulCtrlIdx);                               /* PRQA S 3432 # JV-01 */
  #if (ETH_CTRL_ENABLE_RX_POLLING == STD_ON)
  #if (ETH_AR_VERSION >= ETH_AR_431_VERSION)
  P2FUNC(Std_ReturnType, ETH_PRIVATE_CODE, pHwCheckFifoIndex)(CONST(uint32, AUTOMATIC) LulCtrlIdx,                      /* PRQA S 3432 # JV-01 */
                                                              CONST(uint32, AUTOMATIC) LulQueueIdx);
  #endif
  #endif
  #if (ETH_MACRO_ETNC == STD_ON || ETH_MACRO_ETNB == STD_ON)
  #if (ETH_CTRL_ENABLE_RX_POLLING == STD_ON)
  #if (ETH_AR_VERSION >= ETH_AR_431_VERSION)
  P2FUNC(Eth_RxStatusType, ETH_PRIVATE_CODE, pHwReceive)(CONST(uint32, AUTOMATIC) LulCtrlIdx,                           
                                                         CONST(uint32, AUTOMATIC) LulFifoIdx);
  #else
  P2FUNC(Eth_RxStatusType, ETH_PRIVATE_CODE, pHwReceive)(CONST(uint32, AUTOMATIC) LulCtrlIdx);
  #endif
  #endif
  #else
  P2FUNC(Eth_RxStatusType, ETH_PRIVATE_CODE, pHwReceive)(CONST(uint32, AUTOMATIC) LulCtrlIdx,                           /* PRQA S 3432 # JV-01 */
                                                         CONST(uint32, AUTOMATIC) LulQueueIdx);
  #endif
  #if (ETH_GLOBAL_TIME_SUPPORT == STD_ON)
  P2FUNC(Std_ReturnType, ETH_PRIVATE_CODE, pHwSetIncrementTimeForGptp)                                                  /* PRQA S 3432 # JV-01 */
      (CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulIncVal);

  P2FUNC(Std_ReturnType, ETH_PRIVATE_CODE, pHwSetOffsetTimeForGptp)                                                     /* PRQA S 3432 # JV-01 */
    (CONST(uint32, AUTOMATIC) LulCtrlIdx, CONSTP2CONST(Eth_TimeStampType, AUTOMATIC, ETH_APPL_DATA) LpTimeOffsetPtr);
  P2FUNC(Std_ReturnType, ETH_PRIVATE_CODE, pHwGetCurrentTime)                                                           /* PRQA S 3432 # JV-01 */
                        (CONST(uint32, AUTOMATIC) LulCtrlIdx,
                         CONSTP2VAR(Eth_TimeStampQualType, AUTOMATIC, ETH_APPL_DATA) LpTimeQualPtr,                     /* PRQA S 3432 # JV-01 */
                         CONSTP2VAR(Eth_TimeStampType, AUTOMATIC, ETH_APPL_DATA) LpTimeStampPtr);                       /* PRQA S 3432 # JV-01 */
  #if (ETH_AR_VERSION <= ETH_AR_431_VERSION)
  P2FUNC(void, ETH_PRIVATE_CODE, pHwGetEgressTimeStamp)
                              (CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(Eth_BufIdxType, AUTOMATIC) LulBufIdx,
                               CONSTP2VAR(Eth_TimeStampQualType, AUTOMATIC, ETH_APPL_DATA) LpTimeQualPtr,
                               CONSTP2VAR(Eth_TimeStampType, AUTOMATIC, ETH_APPL_DATA) LpTimeStampPtr);
  
  P2FUNC(void, ETH_PRIVATE_CODE, pHwGetIngressTimeStamp)
                               (CONST(uint32, AUTOMATIC) LulCtrlIdx,
                                CONSTP2CONST(Eth_DataType, AUTOMATIC, ETH_APPL_DATA) LpDataPtr,
                                CONSTP2VAR(Eth_TimeStampQualType, AUTOMATIC, ETH_APPL_DATA) LpTimeQualPtr,
                                CONSTP2VAR(Eth_TimeStampType, AUTOMATIC, ETH_APPL_DATA) LpTimeStampPtr);
  #else
  P2FUNC(Std_ReturnType, ETH_PRIVATE_CODE, pHwGetEgressTimeStamp)                                                       /* PRQA S 3432 # JV-01 */
                              (CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(Eth_BufIdxType, AUTOMATIC) LulBufIdx,
                               CONSTP2VAR(Eth_TimeStampQualType, AUTOMATIC, ETH_APPL_DATA) LpTimeQualPtr,               /* PRQA S 3432 # JV-01 */
                               CONSTP2VAR(Eth_TimeStampType, AUTOMATIC, ETH_APPL_DATA) LpTimeStampPtr);                 /* PRQA S 3432 # JV-01 */
  
  P2FUNC(Std_ReturnType, ETH_PRIVATE_CODE, pHwGetIngressTimeStamp)                                                      /* PRQA S 3432 # JV-01 */
                               (CONST(uint32, AUTOMATIC) LulCtrlIdx,
                                CONSTP2CONST(Eth_DataType, AUTOMATIC, ETH_APPL_DATA) LpDataPtr,
                                CONSTP2VAR(Eth_TimeStampQualType, AUTOMATIC, ETH_APPL_DATA) LpTimeQualPtr,              /* PRQA S 3432 # JV-01 */
                                CONSTP2VAR(Eth_TimeStampType, AUTOMATIC, ETH_APPL_DATA) LpTimeStampPtr);                /* PRQA S 3432 # JV-01 */
  #endif
  #endif
  #if (ETH_CTRL_ENABLE_MII == STD_ON)
  #if ((ETH_MACRO_ETND == STD_ON) || (ETH_MACRO_ETNE == STD_ON))
  P2FUNC(Std_ReturnType, ETH_PRIVATE_CODE, pHwReadMii)                                                                  /* PRQA S 3432 # JV-01 */
    (CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint8, AUTOMATIC) LucTrcvIdx, 
                   CONST(uint8, AUTOMATIC) LucRegIdx, CONSTP2VAR(uint16, AUTOMATIC, ETH_APPL_DATA) LpRegValPtr);        /* PRQA S 3432 # JV-01 */
  P2FUNC(Std_ReturnType, ETH_PRIVATE_CODE, pHwWriteMii)                                                                 /* PRQA S 3432 # JV-01 */
    (CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint8, AUTOMATIC) LucTrcvIdx,
                   CONST(uint8, AUTOMATIC) LucRegIdx, CONST(uint16, AUTOMATIC) LusRegVal);
  #endif
  #if ((ETH_MACRO_ETNB == STD_ON) || (ETH_MACRO_ETNC == STD_ON) || (ETH_MACRO_ETNF == STD_ON))
  P2FUNC(Std_ReturnType, ETH_PRIVATE_CODE, pHwWriteMiibit)                                                              /* PRQA S 3432 # JV-01 */
    (CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulBit);
  P2FUNC(Std_ReturnType, ETH_PRIVATE_CODE, pHwReadMiibit) (CONST(uint32, AUTOMATIC) LulCtrlIdx,                         /* PRQA S 3432 # JV-01 */
                              CONSTP2VAR(uint16, AUTOMATIC, ETH_APPL_DATA) LpRegValPtr);                                /* PRQA S 3432 # JV-01 */
  #endif
  #endif

} Eth_HwFuncTableType;

/***********************************************************************************************************************
**                                      SchM Critical Section Protection Macros                                       **
***********************************************************************************************************************/
#if (ETH_CRITICAL_SECTION_PROTECTION == STD_ON)
#define ETH_ENTER_CRITICAL_SECTION(Exclusive_Area) SchM_Enter_Eth_##Exclusive_Area()                                    /* PRQA S 0342 # JV-01 */
#define ETH_EXIT_CRITICAL_SECTION(Exclusive_Area)  SchM_Exit_Eth_##Exclusive_Area()                                     /* PRQA S 0342 # JV-01 */
#else
#define ETH_ENTER_CRITICAL_SECTION(Exclusive_Area)
#define ETH_EXIT_CRITICAL_SECTION(Exclusive_Area)
#endif

/***********************************************************************************************************************
**                                                Dem interface Macros                                                **
***********************************************************************************************************************/
#if (ETH_AR_VERSION == ETH_AR_422_VERSION)
#define ETH_DEM_REPORT_ERROR Dem_ReportErrorStatus
#elif (ETH_AR_VERSION >= ETH_AR_431_VERSION)
#define ETH_DEM_REPORT_ERROR (void)Dem_SetEventStatus
#endif

#endif /* ETH_TYPES_H */

/***********************************************************************************************************************
**                                                    End Of File                                                     **
***********************************************************************************************************************/
