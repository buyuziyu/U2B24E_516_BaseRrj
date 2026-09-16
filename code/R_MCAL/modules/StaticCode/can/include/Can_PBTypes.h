/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Can_PBTypes.h                                                                                       */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2019-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Provision of AUTOSAR CAN Post Build time parameters.                                                               */
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
 * 2.4.0: 30/05/2025  : Update Can_CanXLHWUnitInfoType, CanXL_RXFilterRefPairType, remove CanXL_TXFilterElementType
 * 2.3.1: 31/03/2025  : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 *                    : Add message 4641 to support QA-C version 11.6.0
 * 2.3.0: 28/02/2025  : As part of ARDAACL-52560: 
 *                      1. Add element blEthStackConfigured to structure CanXLHWUnitInfoType
 *                      2. Add element blTDCO to structure Can_BaudrateConfigType
 *                      3. Remove element blRxNormalModeEnable from CanXLHWUnitInfoType
 * 2.2.0: 31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 *                      As part of CANXL driver support, following changes are made:
 *                      1. Update macro CANXL_TXFILTER_FIELD, CANXL_TXFILTER_VALID.
 *                      2. Update type CanXL_HwStatusType, CanXL_ControllerStatusType, Can_BaudrateConfigType,
 *                      CanXL_ExtRxStatusType.
 *                      3. Add new type CanXL_HwFixedStatusType.
 * 2.1.2: 31/10/2024  : As part of CANXL driver support, following changes are made:
 *                      1. Change ucTMDLC to usTMDLC
 *                      2. Update condition for ucPaddingValue
 *                      3. Remove ulCAPMODE, ulSFTYIRC, pICSafety from Can_CanXLHWUnitInfoType,
 *                      4. Update CanXL_RxEthQueueType 
 * 2.1.1: 30/08/2024  : As part of CANXL driver support, following changes are made:
 *                      1. Update CanXL_HwStatusType.aaLastRxDesc, CanXL_HwStatusType.aaNextRxDesc 
 *                      2. Update Can_BufferType CanXL_BufHandlerType, CanXL_TxEthQueueType, CanXL_TxQueueType,
 *                      CanXL_TXPriorityQueueType, Can_BaudrateConfigType, Can_ControllerPBConfigType
 *                      3. Remove CanXL_BufferType, Can_CanXLHohConfigType 
 *                      4. Add ucCoreId to Can_ControllerPBConfigType struct
 *                      5. Add message header 3432, Update Can_CanXLHWUnitInfoType for support EIC
 *                      6. Remove message 1534, 1536
 *                      7. Add include Eth_GeneralTypes.h.
 *                      8. Add structure CanXL_MacAddressType, Eth_ExtRxStatusType, CanXL_TxEthQueueType, 
 *                      CanXL_RxEthQueueType, CanXL_TxQueueType, CanXL_RxQueueType, CanXL_HwStatusType, 
 *                      CanXL_ControllerStatusType, CanXL_MacFilter, CanXL_MacFilterMng, CanXL_MemManagerType, 
 *                      CanXL_EtherFrameType, CanXL_TimeStampDescType, CanXL_RxFrameType, CanXL_BufHandlerType,
 *                      CanXL_RXFIFOQueueType, CanXL_BufferType, Can_TxDescriptorsType, CanXL_TXFilterElementType
 *                      CanXL_RXFilterRefPairType, CanXL_FilterType, Can_CanXLHWUnitInfoType
 * 2.0.1: 19/10/2023  : Add message 1536
 *        14/10/2023  : Change macro CAN_AR_R21_11_VERSION to CAN_AR_R22_11_VERSION
 * 2.0.0: 02/08/2023  : Remove multi instance and change from SCHM_CAN_HEADER to SchM_Can.h
 *                      Remove redundant QAC message
 *                      Add CWE Rule
 *        31/05/2023  : Remove redundant QAC message
 * 1.5.0: 27/03/2023  : Add AUTOSAR release version information AR2111.
 * 1.4.3: 11/05/2022  : Remove macro un-use define name CAN_DEM_TYPE
 * 1.3.2: 30/08/2021  : Update to support multi-instance:
 *                      - Add precondition check CAN_INSTANCE_INDEX
 *                      - Change include to SCHM_CAN_HEADER
 * 1.3.1: 02/07/2021  : Add QAC message 9.5.0
 *                      Format source code to 120 characters
 *                      Improve Violation tag (remove START/END)
 *        05/05/2021  : Update the memory section, memclass, ptrclass to change
 *                      the CAN_RSCAN prefix to CAN
 * 1.2.0: 09/07/2020  : Release.
 *        28/07/2020  : Add QAC 9.3.1 comment.
 * 1.1.1: 01/07/2020  : Update Can_HohConfigType to add element
 *                      blObjectUsesPolling.
 * 1.1.0: 19/06/2020  : Release.
 * 1.0.1: 05/02/2020  : Add common macros for Dem report error API.
 *        13/01/2020  : Disbale usBaudrateConfig for AR 4.3.1 because of
 *                      non-supported Can_ChangeBaudrate.
 * 1.0.0: 09/12/2019  : Initial version.
 */
/**********************************************************************************************************************/

#ifndef CAN_PBTYPES_HEADER
#define CAN_PBTYPES_HEADER

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
#if (CAN_CRITICAL_SECTION_PROTECTION == STD_ON)
#include "SchM_Can.h"
#endif
#if(CAN_CANXL_SUPPORTED == STD_ON)
#include "Eth_GeneralTypes.h"
#endif /* CAN_CANXL_SUPPORTED */
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define CAN_PBTYPES_AR_RELEASE_MAJOR_VERSION    CAN_AR_RELEASE_MAJOR_VERSION
#define CAN_PBTYPES_AR_RELEASE_MINOR_VERSION    CAN_AR_RELEASE_MINOR_VERSION
#define CAN_PBTYPES_AR_RELEASE_REVISION_VERSION CAN_AR_RELEASE_REVISION_VERSION

/* File version information */
#define CAN_PBTYPES_SW_MAJOR_VERSION            CAN_SW_MAJOR_VERSION
#define CAN_PBTYPES_SW_MINOR_VERSION            CAN_SW_MINOR_VERSION

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:3472)    : All toplevel uses of this function-like macro look like they could be replaced by            */
/*                       equivalent function calls.                                                                   */
/* Rule                : MISRA C:2012 Dir-4.9                                                                         */
/* JV-01 Justification : This message indicates that a candidate macro may be suitable for replacement by a           */
/*                       function, based on an actual call-site and the arguments passed to it there                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0342)    : Using the glue operator '##'.                                                                */
/* Rule                : CERTCCM PRE05, MISRA C:2012 Rule-20.10                                                       */
/* JV-01 Justification : This can be accepted, due to the implementation is following AUTOSAR standard rule for SchM  */
/*                       module's name.                                                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3630)    : The implementation of this struct/union type should be hidden.                               */
/* Rule                : MISRA C:2012 Dir-4.8                                                                         */
/* JV-01 Justification : This is accepted. Redundant of struct or union type has no affect to driver operation.       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7                                                                       */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is accepted. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:4641)    : The identifier '%1s' could conflict in the future with the name of a macro in '<%2s>'.       */
/* Rule                : CWE 3.6.0 CWE-398, CWE-569, CERTC 3.6.0 DCL37                                                */
/* JV-01 Justification : This Etag naming rule is following internal requirement. It is accepted.                     */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/
/* Index of the default baudrate index of Can_BaudrateConfigType array */
#define CAN_DEFAULT_BAUDRATE_INDEX              0U

/* Macro for CANXL */
#define CANXL_TXFILTER_REFVAL0(x)               (((uint32)(x) & 0xFFUL) << 0UL)
#define CANXL_TXFILTER_REFVAL1(x)               (((uint32)(x) & 0xFFUL) << 8UL)
#define CANXL_TXFILTER_REFVAL2(x)               (((uint32)(x) & 0xFFUL) << 16UL)
#define CANXL_TXFILTER_REFVAL3(x)               (((uint32)(x) & 0xFFUL) << 24UL)

#define CANXL_RX_MODE(x)                        ((uint32)(x) & 0x01UL)
#define CANXL_TX_RETRANS(x)                     (((uint32)(x) & 0x07UL) << 8UL)                                         /* PRQA S 3472 # JV-01 */
#define CANXL_INST_NUM(x)                       (((uint32)(x) & 0x07UL) << 16UL)

#define CANXL_DMAAXI_TIMEOUT(x)                 (((uint32)(x) & 0xFFUL) << 0UL)
#define CANXL_MEMAXI_TIMEOUT(x)                 (((uint32)(x) & 0xFFUL) << 8UL)
#define CANXL_PRT_TIMEOUT(x)                    (((uint32)(x) & 0x3FFFUL) << 16UL)
#define CANXL_PRESCALER(x)                      (((uint32)(x) & 0x3UL) << 30UL)
#define CANXL_AR_MAXPEND(x)                     (((uint32)(x) & 0x3UL) << 0UL)
#define CANXL_AW_MAXPEND(x)                     (((uint32)(x) & 0x3UL) << 4UL)

#define CANXL_FQ_BASEADDR(x)                    (((uint32)(x) & 0xFFFFUL) << 0UL)
#define CANXL_PQ_BASEADDR(x)                    (((uint32)(x) & 0xFFFFUL) << 16UL)

#define CANXL_TXFILTER_COMB(x)                  (((uint32)(x) & 0xFFUL) << 0UL)
#define CANXL_TXFILTER_MASK(x)                  (((uint32)(x) & 0xFFUL) << 8UL)
#define CANXL_TXFILTER_CFG(x)                   (((uint32)(x) & 0xFFUL) << 16UL)


#define CANXL_RXFILTER_NBFE(x)                  (((uint32)(x) & 0xFFUL) << 0UL)
#define CANXL_RXFILTER_THRESHOLD(x)             (((uint32)(x) & 0x1FUL) << 8UL)
#define CANXL_RXFILTER_ANMF_FQ(x)               (((uint32)(x) & 0x07UL) << 16UL)
#define CANXL_RXFILTER_ANMF                     (uint32)(1UL << 20UL)
#define CANXL_RXFILTER_ANFF                     (uint32)(1UL << 21UL)

#define CANXL_TXFILTER_FIELD(x)                 (((uint32)(x) & 0xFFFFUL) << 16UL)
#define CANXL_TXFILTER_VALID(x)                 ((uint32)(x) & 0xFFFFUL)

/* 8 TX FIFO + 32 slots Priority Queue */
#define CANXL_MAX_TXQUEUE                        40U

/* 8 TX FIFO Queue */
#define CANXL_MAX_TXFIFOQUEUE                    8U

/* 8 RX FIFO Queue */
#define CANXL_MAX_RXFIFOQUEUE                    8U

#if (CAN_CRITICAL_SECTION_PROTECTION == STD_ON)
#define CAN_ENTER_CRITICAL_SECTION(Exclusive_Area) SchM_Enter_Can_##Exclusive_Area()                                    /* PRQA S 0342 # JV-01 */
#define CAN_EXIT_CRITICAL_SECTION(Exclusive_Area)  SchM_Exit_Can_##Exclusive_Area()                                     /* PRQA S 0342 # JV-01 */
#else
#define CAN_ENTER_CRITICAL_SECTION(Exclusive_Area)
#define CAN_EXIT_CRITICAL_SECTION(Exclusive_Area)
#endif

/***********************************************************************************************************************
**                                              DEM Report Error Macros                                               **
***********************************************************************************************************************/
#if (CAN_AR_VERSION == CAN_AR_422_VERSION)
#define CAN_DEM_REPORT_ERROR(EventId, EventStatus) (void)Dem_ReportErrorStatus(EventId, EventStatus)
#elif ((CAN_AR_VERSION == CAN_AR_431_VERSION) || (CAN_AR_VERSION == CAN_AR_R22_11_VERSION))
#define CAN_DEM_REPORT_ERROR(EventId, EventStatus) (void)Dem_SetEventStatus(EventId, EventStatus)
#endif

/***********************************************************************************************************************
**                                                  DEM TYPE CASTING                                                  **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                    ACCEPTANCE FILTER RECEIVE RULE CONFIGURATION                                    **
***********************************************************************************************************************/
/* This structure includes values of filter setting registers */
typedef struct STag_Can_FilterType                                                                                      /* PRQA S 3630 # JV-01 */
{
  /* Value of GAFLIDj */
  VAR(uint32, CAN_CONFIG_DATA) ulGAFLID;
  /* Value of GAFLMj */
  VAR(uint32, CAN_CONFIG_DATA) ulGAFLM;
  /* Value of GAFLP0j and GAFLP1j */
  VAR(uint32, CAN_CONFIG_DATA) aaGAFLP[2];
} Can_FilterType;

/* This structure includes setting value of registers for each RSCAN(FD) unit */
typedef struct STag_Can_HWUnitInfoType
{
  /* Element number of pTMIEC */
  VAR(uint8, CAN_CONFIG_DATA) ucNoOfTMIEC;
  /* Element number of pGAFLCFG */
  VAR(uint8, CAN_CONFIG_DATA) ucNoOfGAFLCFG;
  /* Element number of pFilterConfig */
  VAR(uint16, CAN_CONFIG_DATA) usNoOfFilters;
  /* Value of RMNB including number and payload size of rx buffer */
  VAR(uint32, CAN_CONFIG_DATA) ulRMNB;
  /* Value of GCFG including mirror, DLC check, and priority features */
  VAR(uint32, CAN_CONFIG_DATA) ulGCFG;
  /* Pointer to configuration value of GAFLCFG */
  P2CONST(uint32, TYPEDEF, CAN_CONFIG_DATA) pGAFLCFG;
  /* Pointer to table including value of TMIECy */
  P2CONST(uint32, TYPEDEF, CAN_CONFIG_DATA) pTMIEC;
  /* Pointer to table including HW filter information */
  P2CONST(Can_FilterType, TYPEDEF, CAN_CONFIG_DATA) pFilterConfig;
  #if (CAN_WAKE_UP_FACTOR_CLEAR_ISR == STD_ON)
  /* Mask for Receive FIFO Wakeup factor clear register */
  VAR(uint32, CAN_CONFIG_DATA) ulRxFIFOWUFMask;
  #endif
} Can_HWUnitInfoType;

/***********************************************************************************************************************
**                                 HARDWARE TRANSMITRECEIVE HARDWARE OBJECT STRUCTURE                                 **
***********************************************************************************************************************/
/* HRH or HTH */
typedef enum ETag_Can_HohType                                                                                           /* PRQA S 4641 # JV-01 */
{
  /* This is HRH */
  CAN_HOH_HRH,
  /* This is HTH */
  CAN_HOH_HTH
} Can_HohType;

/* Buffer type */
typedef enum ETag_Can_BufferType                                                                                        /* PRQA S 4641 # JV-01 */
{
  /* Single buffer */
  CAN_BUFFERTYPE_BUFFER,
  /* Transmit/Receive FIFO */
  CAN_BUFFERTYPE_TXRXFIFO,
  /* Gateway mode */
  CAN_BUFFERTYPE_GATEWAY,
  /* Receive FIFO */
  CAN_BUFFERTYPE_RXFIFO,
  /* Transmit Queue */
  CAN_BUFFERTYPE_TXQUEUE,
  /* TX Priority Queue */
  CANXL_QUEUETYPE_TXPRIORITY,
  /* TX FIFO Queue */
  CANXL_QUEUETYPE_TXFIFO,
  /* RX FIFO Queue */
  CANXL_QUEUETYPE_RXFIFO
} Can_BufferType;

/* Hardware Transmit Handle Structure */
typedef struct STag_Can_HohConfigType                                                                                   /* PRQA S 3630 # JV-01 */
{
  /* HRH or HTH */
  VAR(Can_HohType, CAN_CONFIG_DATA) enHoh;
  /* Index of CanMainFunctionRWPeriod */
  VAR(uint8, CAN_CONFIG_DATA) ucMainFunctionRIndex;
  /* Index of controller which this HxH allocated to */
  VAR(uint8, CAN_CONFIG_DATA) ucController;
  /* TMDLC value indicating the maximum payload length */
  VAR(uint16, CAN_CONFIG_DATA) usTMDLC;
  /* ID of HRH or HTH */
  VAR(uint16, CAN_CONFIG_DATA) usHohId;
  /* Type of the buffer */
  VAR(Can_BufferType, CAN_CONFIG_DATA) enBufferType;
  /* Index for TxBuffer, RxBuffer, RxFIFO or TxRxFIFO */
  VAR(uint16, CAN_CONFIG_DATA) usBufferIndex;
  #if ((CAN_TRIGGER_TRANSMIT_FUNCTION == STD_ON) || (CAN_CANXL_TRIGGER_TRANSMIT_FUNCTION == STD_ON))
  /* Whether trigger transmit is enabled for this HTH */
  VAR(boolean, CAN_CONFIG_DATA) blTriggerTransmitEnable;
  #endif
  #if (CAN_RSCANFD_CONFIGURED == STD_ON) || (CAN_CANXL_SUPPORTED == STD_ON)
  /* Padding value for CANFD */
  VAR(uint8, CAN_CONFIG_DATA) ucPaddingValue;
  #endif
  #if ((CAN_TX_COMFIFO == STD_ON) || (CAN_TX_QUEUE == STD_ON) || (CAN_RX_FIFO == STD_ON) || \
  (CAN_RX_COMFIFO == STD_ON) || (CAN_GATEWAY_COMFIFO == STD_ON)) || (CAN_GATEWAY_QUEUE == STD_ON)
  /* Register value for CFCC, RFCC or TXQCC */
  VAR(uint32, CAN_CONFIG_DATA) ulXXCCRegValue;
  #endif
  #if (defined(CAN_COMFIFO_ENHANCEMENT_SUPPORT) && \
     ((CAN_TX_COMFIFO == STD_ON) || (CAN_RX_COMFIFO == STD_ON) || (CAN_GATEWAY_COMFIFO == STD_ON)))
  /* Register value for CFCCE */
  VAR(uint32, CAN_CONFIG_DATA) ulXXCCERegValue;
  #endif
  #if ((CAN_AR_VERSION == CAN_AR_431_VERSION) || (CAN_AR_VERSION == CAN_AR_R22_11_VERSION))
  /* Whether CanHardwareObjectUsesPolling is enabled for this HOH */
  VAR(boolean, CAN_CONFIG_DATA) blObjectUsesPolling;
  #endif
} Can_HohConfigType;
/*---------------------------------------------------------------------------------------------------------------------
 * CAN XL Specific
 ---------------------------------------------------------------------------------------------------------------------*/
#if (CAN_CANXL_SUPPORTED == STD_ON)
/* The structure contains MAC address. It consists of two word values
   to improve performance of MAC address comparing operation. */
typedef struct STag_CanXL_MacAddressType
{
  /* e.g. when a address is "12:34:56:78:9A:BC": */
  uint32 ulH32; /* has 0x12345678 */
  uint32 ulL16; /* has 0x00009ABC */
} CanXL_MacAddressType;

typedef enum ETag_CanXL_RxExtStatusType                                                                                 /* PRQA S 4641 # JV-01 */
{
  CANXL_EXT_RECEIVED = 0,
  CANXL_EXT_NOT_RECEIVED,
  CANXL_EXT_RECEIVED_MORE_DATA_AVAILABLE,
  CANXL_EXT_NOT_RECEIVED_MORE_DATA_AVAILABLE
} CanXL_ExtRxStatusType;

/*******************************************************************************
**  Type: CanXL_BufHandlerType                                                  **
**                                                                            **
**  Setting option                                                            **
**                                                                            **
**  Members:                                                                  **
**    ulbufIdx      - the Index of buffer                                     **
**    ulbufAddr     - Pointer to the Frame in URAM  to be transmitted         **
**    ulTxLength    - Transmit request size                                   **
**    ulEthTypeAddr - ether type address                                      **
**    ucPriority    - Buffer priority                                         **
**    ucQueue       - Buffer Queue                                            **
**    blEnableTS    - Flag to store if TimeStamp shall be stored              **
**    blTxConfirm   - the Tx Confirmation flag                                **
**    stTimeStamp   - Timestamp information                                   **
**    enTimeQual    - Timestamp quality                                       **
*******************************************************************************/
typedef struct STag_CanXL_BufHandlerType                                                                                /* PRQA S 3630 # JV-01 */
{
  uint32            ulbufIdx;
  uint32            ulbufAddr;
  uint32            ulTxLength;
  uint32            ulEthTypeAddr;
  uint32            ulPriority;
  uint8             ucQueue;
  Can_BufferType    ucQueueType;
  boolean           blbenableTS;
  boolean           blTxConfirm;
  #if (CAN_CANXL_GLOBAL_TIME_SUPPORT == STD_ON)
  Eth_TimeStampType stTimeStamp;
  Eth_TimeStampQualType enTimeQual;
  uint8 ucDummy1[3];
  #endif
} CanXL_BufHandlerType;

/*******************************************************************************
**  Type: CanXL_TxBufferType                                                  **
**                                                                            **
**  Transmission buffer structure                                             **
**                                                                            **
**  Members:                                                                  **
**    pBufferHdr   - Buffer Handler                                           **
**    blTxOngoing  - Transmission flag in Buffer                              **
*******************************************************************************/
typedef struct STag_CanXL_TxBufferType                                                                                  /* PRQA S 3630 # JV-01 */
{
  CanXL_BufHandlerType  *pBufferHdr;
  boolean               blTxOngoing;
  uint8                 ucDummy[3];
} CanXL_TxBufferType;

/*******************************************************************************
**  Type: CanXL_TxEthQueueType                                                **
**                                                                            **
**  Transmission buffer structure                                             **
**                                                                            **
**  Members:                                                                  **
**    ucEthEgressFifoIdx - Eth Egress Fifo Index                              **
**    usEthPriority      - Eth Priority                                       **
**    ucEthQueue         - Eth Queue                                          **
**    ucTxQueueType      - Default Tx Queue Type                              **
*******************************************************************************/
typedef struct STag_CanXL_TxEthQueueType                                                                                /* PRQA S 3630 # JV-01 */
{
  VAR(uint16, TYPEDEF)                                  usEthPriority;
  VAR(uint8, TYPEDEF)                                   ucEthEgressFifoIdx;
  VAR(uint8, TYPEDEF)                                   ucEthQueue;
  VAR(Can_BufferType, TYPEDEF)                          ucTxQueueType;
} CanXL_TxEthQueueType;

/*******************************************************************************
**  Type: CanXL_RxEthQueueType                                                **
**                                                                            **
**  Transmission buffer structure                                             **
**                                                                            **
**  Members:                                                                  **
**    ucEthIngressFifoIdx - Eth Ingress Fifo index                            **
**    ucEthFIFOQueue      - FIFO Queue                                        **
**    ucFifoVcid          - FIFO VCID                                         **
**    blVCIDConfigured    - VCID is configured                                **
*******************************************************************************/
typedef struct STag_CanXL_RxEthQueueType                                                                                /* PRQA S 3630 # JV-01 */
{
  VAR(uint8, TYPEDEF)                                     ucEthIngressFifoIdx;
  VAR(uint8, TYPEDEF)                                     ucEthFIFOQueue;
  VAR(uint8, TYPEDEF)                                     ucNoOfVCIDConfigured;
  P2CONST(uint8, TYPEDEF, CAN_CONFIG_DATA)                pVcidConfig;
} CanXL_RxEthQueueType;

/*******************************************************************************
**  Type: CanXL_TxQueueType                                                   **
**                                                                            **
**  Tx ETH Queue structure                                                    **
**                                                                            **
**  Members:                                                                  **
**    ucEthDefaultPriority - Default Priority Queue                           **
**    ucEthDefaultQueue    - Default FIFO Queue                               **
**    ucNoOfEthEgressFifo  - Numer of FIFO Queue                              **
**    ucTxDefaultQueueType - Default Tx Queue Type                            **
**    pTxEthEthEgressFifo  - pointer to Queue Configured specific             **
*******************************************************************************/
typedef struct STag_CanXL_TxQueueType                                                                                   /* PRQA S 3630 # JV-01 */
{
  VAR(uint16, TYPEDEF)                                    usEthDefaultPriority;
  VAR(uint8, TYPEDEF)                                     ucEthDefaultQueue;
  VAR(uint32, TYPEDEF)                                    ulNoOfEthEgressFifo;
  VAR(Can_BufferType, TYPEDEF)                            ucTxDefaultQueueType;
  P2CONST(CanXL_TxEthQueueType, TYPEDEF, CAN_CONFIG_DATA) pTxEthEthEgressFifo;
} CanXL_TxQueueType;

/*******************************************************************************
**  Type: CanXL_RxQueueType                                                   **
**                                                                            **
**  Rx ETH Queue structure                                                    **
**                                                                            **
**  Members:                                                                  **
**    ucNoOfEthIngressFifo - Numer of FIFO Queue                              **
**    pRxEthEthIngressFifo - pointer to Rx FIFO Queue                         **
*******************************************************************************/
typedef struct STag_CanXL_RxQueueType                                                                                   /* PRQA S 3630 # JV-01 */
{
  VAR(uint8, TYPEDEF)                                     ucNoOfEthIngressFifo;
  P2CONST(CanXL_RxEthQueueType, TYPEDEF, CAN_CONFIG_DATA) pRxEthIngressFifo;
} CanXL_RxQueueType;


/**
 * Tx Descriptor (Tx FIFO Queue is double size for currrent and next)
*/
typedef struct Can_TxDescriptorsType_Stag                                                                               /* PRQA S 3630 # JV-01 */
{
  uint32 ulElement0;         /* SW/MH: DMA Info Ctrl 1 - 0x0+20*m */
  uint32 ulElement1;         /* SW/MH: DMA Info Ctrl 2 - 0x4+0x20*m */
  uint32 ulElement2TS0;      /* MH: TimeStamp 0 - 0x8+0x20*m */
  uint32 ulElement3TS1;      /* MH: TimeStamp 1 - 0xC+0x20*m */
  uint32 ulElement4T0;       /* SW: TX Message Header Information - 0x10+0x20*m */
  uint32 ulElement5T1;       /* SW: TX Message Header Information - 0x14+0x20*m */
  uint32 ulElement6T2TD0;    /* SW: TX Message Header Information / First TX Data Payload - 0x18+0x20*m */
  uint32 ulElement7TX_APTD1; /* SW (optional): TX Payload Data Address Pointer / Second TX Data Payload - 0x1C+0x20*m */
  
} Can_TxDescriptorsType;

/**
 * Rx Descriptor (Both normal and continuous mode)
*/
typedef struct Can_RxDescriptorsType_Stag                                                                               /* PRQA S 3630 # JV-01 */
{
  uint32 ulElement0;         /* DMA info Ctrl 1 */
  uint32 ulElement1;         /* RX Address Pointer */
  uint32 ulElement2TS0;      /* TimeStamp 0 */
  uint32 ulElement3TS1;      /* TimeStamp 1 */
} Can_RxDescriptorsType;

/*******************************************************************************
**  Type: CanXL_StatusType                                                  **
**                                                                            **
**  Device instance specific data.                                            **
**                                                                            **
**  All instance specific data is kept within that structure.                 **
**                                                                            **
**  Members:                                                                  **
**    aaBufTxCnt            - Buffer Tx counter                               **
**    aaHeadTxDesc          - Head tx descriptor address                      **
**    aaLastTxDesc          - Last tx descriptor address                      **
**    aaHeadRxDesc          - Next free rx descriptor address                 **
**    aaLastRxDesc          - Last rx descriptor address                      **
*******************************************************************************/

typedef struct STag_CanXL_HwStatusType
{
  uint32                                                  aaBufTxCnt[CANXL_MAX_TXQUEUE];
  P2VAR(Can_TxDescriptorsType, AUTOMATIC, CAN_APPL_DATA)  aaHeadTxDesc[CANXL_MAX_TXFIFOQUEUE];                          /* PRQA S 3432 # JV-01 */
  P2VAR(Can_RxDescriptorsType, AUTOMATIC, CAN_APPL_DATA)  aaHeadRxDesc[CANXL_MAX_RXFIFOQUEUE];                          /* PRQA S 3432 # JV-01 */
} CanXL_HwStatusType;

typedef struct STag_CanXL_HwFixedStatusType
{
  P2VAR(Can_TxDescriptorsType, AUTOMATIC, CAN_APPL_DATA)  aaFirstTxDesc[CANXL_MAX_TXFIFOQUEUE];                         /* PRQA S 3432 # JV-01 */
  P2VAR(Can_TxDescriptorsType, AUTOMATIC, CAN_APPL_DATA)  aaLastTxDesc[CANXL_MAX_TXFIFOQUEUE];                          /* PRQA S 3432 # JV-01 */
  P2VAR(Can_RxDescriptorsType, AUTOMATIC, CAN_APPL_DATA)  aaFirstRxDesc[CANXL_MAX_TXFIFOQUEUE];                         /* PRQA S 3432 # JV-01 */
  P2VAR(Can_RxDescriptorsType, AUTOMATIC, CAN_APPL_DATA)  aaLastRxDesc[CANXL_MAX_TXFIFOQUEUE];                          /* PRQA S 3432 # JV-01 */
} CanXL_HwFixedStatusType;

/* Status of each controller CANXL for mapped tunneled 802.3 Ethernet frames) */
typedef struct Stag_CanXL_ControllerStatusType
{
  /* MAC address of this controller */
  CanXL_MacAddressType stMacAddr;
  /* Current mode, DOWN or ACTIVE */
  Eth_ModeType enMode;
  /* Pointer to the head of tx buffer ring */
  uint8 ucTxBufHead;
  /* Pointer to the tail of tx buffer ring */
  uint32 ulTxBufTail;
  /* TEC emulation of CAN XL controller */
  uint32 ulTEC;
  /* REC emulation of CAN XL controller */
  uint32 ulREC;
  /* Flags which indicates CANXL controller error signaling is enabled */
  boolean blErrorSignaling;
  /* LLDriver specific fixed status for queue */
  CanXL_HwFixedStatusType stHwStatFixed;
  /* LLDriver specific status for SDT 5 frame */
  CanXL_HwStatusType stHwStatSDT5;
  /* LLDriver specific status for non-SDT 5 frame */
  CanXL_HwStatusType stHwStatNonSDT5;
} CanXL_ControllerStatusType;

/* Multicast address table */
typedef struct STag_CanXL_MacFilter
{
  /* Filter counter */
  uint32 ulCount;
  /* Mac Address */
  CanXL_MacAddressType  stMacAddr;
} CanXL_MacFilter;

/* Filter Function Management */
typedef struct STag_CanXL_MacFilterMng
{
  /* Multicast address table */
  CanXL_MacFilter stFilter[32U];
  /* Promiscuous mode entering counter */
  uint32 ulPromiscuousCount;
} CanXL_MacFilterMng;

/* Structure of Memmory Manager */
typedef struct STag_CanXL_MemManagerType                                                                                /* PRQA S 3630 # JV-01 */
{
  struct STag_CanXL_MemManagerType *pNext;     /* Next node */
  struct STag_CanXL_MemManagerType *pPrev;     /* Prev node */
  uint32 ulHeapSize;                           /* Memory block size */
  boolean blHeapLock;                          /* Memory lock flag */
  uint8 ucDummy[3];                            /* Dummy */
} CanXL_MemManagerType;

/*******************************************************************************
**  Type: CanXL_EtherFrameType                                                  **
**                                                                            **
**  Ethernet Frame structure                                                  **
**                                                                            **
**  Members:                                                                  **
**    ucDstAddr    - Destination address                                      **
**    ucSrcAddr    - Source address                                           **
**    ucFrameType  - EtherType                                                **
**    ucPayload    - Payload                                                  **
*******************************************************************************/
typedef struct STag_CanXL_EtherFrameType
{
  uint8 ucDstAddr[6];
  uint8 ucSrcAddr[6];
  uint8 ucFrameType[2];
  Eth_DataType ucPayload;
} CanXL_EtherFrameType;
/*******************************************************************************
**  Type: CanXL_TimeStampDescType                                             **
**                                                                            **
**  Timestamp structure                                                       **
**                                                                            **
**  Members:                                                                  **
**    ulElement2TS0  - Timestamp 0: LSB of the 64bits timestamp               **
**    ulElement3TS1  - Timestamp 1: MSB of the 64bits timestamp               **
*******************************************************************************/
#if (CAN_CANXL_GLOBAL_TIME_SUPPORT == STD_ON)
typedef struct STag_Eth_TimeStampDescType
{
  uint32 ulElement2TS0;
  uint32 ulElement3TS1;
} CanXL_TimeStampDescType;
#endif

/*******************************************************************************
**  Type: CanXL_RxFrameType                                                   **
**                                                                            **
**  Rx frame information structure                                            **
**                                                                            **
**  Members:                                                                  **
**    ulFrameAddr    - frame address                                          **
**    ulEthTypeAddr  - Eth frame type                                         **
**    ulFrameLength  - frame length                                           **
**    stTimestamp    - Timestamps                                             **
*******************************************************************************/
typedef struct STag_CanXL_RxFrameType
{
  uint32            ulFrameAddr;
  uint32            ulEthTypeAddr;
  uint32            ulFrameLength;
#if (CAN_CANXL_GLOBAL_TIME_SUPPORT == STD_ON)
  CanXL_TimeStampDescType  stTimestamp;
#endif
} CanXL_RxFrameType;

/* Tx FIFO Queue Struct */
typedef struct STag_CanXL_TXFIFOQueueType                                                                               /* PRQA S 3630 # JV-01 */
{
  /* Value of Queue index */
  uint8 ucQueueId;
  /* Value number of descriptors per each Queue */
  uint16 usMaxNumDesc;
  /* Value of payload size of all buffers per each Queue */
  uint16 usPayloadSize; 
  /* Pointer to Tx FIFO queue Data Container */
  P2VAR(Can_TxDescriptorsType, TYPEDEF, CAN_CONFIG_DATA) pStartAddress;                                                 /* PRQA S 3432 # JV-01 */
  /* Pointer to Tx Data queue Data Container */
  P2VAR(uint8, TYPEDEF, CAN_CONFIG_DATA) pDataContainer;                                                                /* PRQA S 3432 # JV-01 */
  /* Pointer to Tx FIFO queues SwPduHandle array */
  P2VAR(PduIdType, TYPEDEF, CAN_CONFIG_DATA) pSwPduHandle;                                                              /* PRQA S 3432 # JV-01 */
} CanXL_TXFIFOQueueType;

/* Tx Priority Queue Struct */
typedef struct STag_CanXL_TXPriorityQueueType                                                                           /* PRQA S 3630 # JV-01 */
{
  /* Value of MAC address for each controller */
  VAR(uint8, TYPEDEF) aaDescIndex[32];
  /* Value of payload size of all buffers per each Queue slots */
  uint16 usPayloadSize;
  /* Pointer to Tx Priority queue Data Container */
  P2VAR(Can_TxDescriptorsType, TYPEDEF, CAN_CONFIG_DATA) pStartAddress;                                                 /* PRQA S 3432 # JV-01 */
  /* Pointer to Tx Data queue Data Container */
  P2VAR(uint8, TYPEDEF, CAN_CONFIG_DATA) pDataContainer;                                                                /* PRQA S 3432 # JV-01 */
  /* Pointer to Tx Priority queues SwPduHandle array */
  P2VAR(PduIdType, TYPEDEF, CAN_CONFIG_DATA) pSwPduHandle;                                                              /* PRQA S 3432 # JV-01 */
} CanXL_TXPriorityQueueType;

/* Rx FIFO Queue Struct */
typedef struct STag_CanXL_RXFIFOQueueType                                                                               /* PRQA S 3630 # JV-01 */
{
  /* Value of Queue index */
  uint8 ucQueueId;
  /* Value number of descriptors per each Queue */
  uint16 usMaxNumDesc;
  /* Value of payload size of all buffers per each Queue */
  uint16 usPayloadSize; 
  /* Pointer to Rx FIFO queue Data Container */
  P2VAR(Can_RxDescriptorsType, TYPEDEF, CAN_CONFIG_DATA) pStartAddress;                                                 /* PRQA S 3432 # JV-01 */
  /* Pointer to Rx Data queue Data Container */
  P2VAR(uint8, TYPEDEF, CAN_CONFIG_DATA) pDataContainer;                                                                /* PRQA S 3432 # JV-01 */
} CanXL_RXFIFOQueueType;


/**
 * Rx Filter Reference and Mask
*/
typedef struct Can_CanXL_RXFilterRefPairType_Stag                                                                       /* PRQA S 3630 # JV-01 */
{
  /* Index of Rx filter */
  VAR(uint16, TYPEDEF) usRxRefPairId;
  /* Value of Reference */
  VAR(uint32, TYPEDEF) ulRefVal;
  /* Value of Mask */
  VAR(uint32, TYPEDEF) ulMask;
} CanXL_RXFilterRefPairType;

typedef struct CanXL_FilterType_Stag                                                                                    /* PRQA S 3630 # JV-01 */
{
  /* Index of Rx filter */
  VAR(uint8, TYPEDEF) ucRxFilterId;
  /* Value of Rx filter */
  VAR(uint32, TYPEDEF) ulRxFilterVal;
} CanXL_FilterType;

/* This structure includes setting value of registers for each CANXL unit */
typedef struct STag_Can_CanXLHWUnitInfoType                                                                             /* PRQA S 3630 # JV-01 */
{
  /* Value of MAC address for each controller */
  VAR(uint8, TYPEDEF) aaEthMACAddr[6];
  /* Value of GCFG including mirror, DLC check, and priority features */
  VAR(uint32, TYPEDEF) ulGCFG;
  /* Value of Message Handler Safety Configuration register*/
  VAR(uint32, TYPEDEF) ulSTYCFG;
  /* Value of Message Handler Safety Control register*/
  VAR(uint32, TYPEDEF) ulSTYCTRL;
  /* Value of AXI parameter register */
  VAR(uint32, TYPEDEF) ulAXIPARAM;
  /* Value of TX Descriptor Base Address register */
  VAR(uint32, TYPEDEF) ulTXDESCLMEM;
  /* Value local memory of Rx filters*/
  VAR(uint32, TYPEDEF) ulRXFILTLMEM;
  /* Value of RX_FILTER_CTRL0 register */
  VAR(uint32, TYPEDEF) ulRXFILCTRL0;
  /* Value of mode register */
  VAR(uint32, TYPEDEF) ulPRTMODE;
  /* Value of Functional raw event enable register */
  VAR(uint32, TYPEDEF) ulFUNCIRC;
  /* Value of Error Interrupt Status register */
  VAR(uint32, TYPEDEF) ulERRCIRC;
  /* Value of Transceiver ID */
  VAR(uint8, TYPEDEF) ucTransceiverID;
  /* The number of Tx FIFO Queue */
  VAR(uint8, TYPEDEF) ucNoOfTxFIFOQueues;
  /* The number of Tx Priority Queue slots */
  VAR(uint8, TYPEDEF) ucNoOfTxPrioritySlots; 
  /* The number of Rx FIFO Queue */
  VAR(uint8, TYPEDEF) ucNoOfRxFIFOQueues;
  /* The number of Rx Filters Refence Pairs */
  VAR(uint16, TYPEDEF) usNoOfRxFilterRefPairs;
  /* The number of Filters */
  VAR(uint8, TYPEDEF) ucNoOfFilters;
  /* The Eth Stack configured or not */
  VAR(boolean, TYPEDEF) blEthStackConfigured;
  /* The Tx FIFO Queue enable */
  VAR(boolean, TYPEDEF) blTxFQEnable;
  /* The Tx Priority Queue enable */
  VAR(boolean, TYPEDEF) blTxPQEnable;
  /* The setting of RX FIFO Queue used */
  VAR(uint32, TYPEDEF) ulRXFQUsed;
  /* The setting of TX FIFO Queue used */
  VAR(uint32, TYPEDEF) ulTXFQUsed;
  /* The setting of TX Priority Queue used */
  VAR(uint32, TYPEDEF) ulTXPQUsed;
  /* The setting of TX FIFO Queue */
  P2CONST(CanXL_TXFIFOQueueType, TYPEDEF, CAN_CONFIG_DATA) pTxFIFOQueueConfig;
  /* The setting of TX Priority Queue */
  P2CONST(CanXL_TXPriorityQueueType, TYPEDEF, CAN_CONFIG_DATA) pTxPriorityQueueConfig;
  /* The setting of RX FIFO Queue */
  P2CONST(CanXL_RXFIFOQueueType, TYPEDEF, CAN_CONFIG_DATA) pRxFIFOQueueConfig;
  /* The setting of RX Filter Reference Pair */
  P2CONST(CanXL_RXFilterRefPairType, TYPEDEF, CAN_CONFIG_DATA) pRxFilterRefPairConfig;
  /* The setting of Filter Configuration */
  P2CONST(CanXL_FilterType, TYPEDEF, CAN_CONFIG_DATA) pFilterConfig;
  /* The setting of Tx Eth Queue Configuration*/
  P2CONST(CanXL_TxQueueType, TYPEDEF, CAN_CONFIG_DATA) pTxEthQueueConfig;
  /* The setting of Rx Eth Queue Configuration*/
  P2CONST(CanXL_RxQueueType, TYPEDEF, CAN_CONFIG_DATA) pRxEthQueueConfig;
  /* EIC register address for functional interruption */
  P2VAR(volatile uint16, TYPEDEF, REGSPACE) pICFunc;
  /* EIC register address for error interruption */
  P2VAR(volatile uint16, TYPEDEF, REGSPACE) pICErr;
} Can_CanXLHWUnitInfoType;
#endif /* CAN_CANXL_SUPPORTED == STD_ON */

/***********************************************************************************************************************
**                                        CAN Controller Post-build Structure                                         **
***********************************************************************************************************************/
/* Baud rate structure */
typedef struct STag_Can_BaudrateConfigType                                                                              /* PRQA S 3630 # JV-01 */
{
  /* Value of CanControllerBaudRateConfigID used by Can_SetBaudrate API */
  VAR(uint16, CAN_CONFIG_DATA) usBaudrateConfigID;
  #if (CAN_AR_VERSION == CAN_AR_422_VERSION)
  /* Value of CanControllerBaudRate used by Can_ChangeBaudrate API */
  VAR(uint16, CAN_CONFIG_DATA) usBaudrateConfig;
  #endif
  /* Value of CmCFG including baudrate and timing settings */
  VAR(uint32, CAN_CONFIG_DATA) ulCFG;
  /* Value of CmDCFG including baudrate and timing settings for FD */
  VAR(uint32, CAN_CONFIG_DATA) ulDCFG;
  #if (CAN_RSCANFD_CONFIGURED == STD_ON)
  /* Value of CmFDCFG */
  VAR(uint32, CAN_CONFIG_DATA) ulFDCFG;
  #endif
  #if ((CAN_RSCANFD_CONFIGURED == STD_ON) || (CANFD_ON_XL_BUS_SUPPORT == STD_ON))
  /* Whether baudrate switching is enabled or disabled */
  VAR(boolean, CAN_CONFIG_DATA) blBRS;
  /* Whether CanControllerFdBaudrateConfig is configured */
  VAR(boolean, CAN_CONFIG_DATA) blFdConfigured;
  #endif
  #if (CAN_CANXL_SUPPORTED == STD_ON)
  /* Value of XLCFG including baudrate and timing settings for XL */
  VAR(uint32, TYPEDEF) ulXLCFG;
  /* Value of PWMCFG including PWM settings for XL */
  VAR(uint32, TYPEDEF) ulPWMCFG;
  /* Whether Error Signaling is enabled */
  VAR(boolean, TYPEDEF) blErrorSignalingEnabled;
  /* Whether PWM Transceiver is connected */
  VAR(boolean, TYPEDEF) blTrcvPwmMode;
  /* Whether Transmit Delay Compensation is used */
  VAR(boolean, TYPEDEF) blTDCO;
  #endif
} Can_BaudrateConfigType;

/* This structure includes Post-Build configurations for each Controller */
typedef struct STag_Can_ControllerPBConfigType                                                                          /* PRQA S 3630 # JV-01 */
{
  /* Index of CanMainFunctionRWPeriod */
  VAR(uint8, CAN_CONFIG_DATA) ucMainFunctionWIndex;
  /* Element number of pBaudrateConfig */
  VAR(uint16, CAN_CONFIG_DATA) usNoOfBaudrate;
  #if (CAN_MULTI_CORE_SUPPORT == STD_ON)
  /* Core ID setting for controller */
  VAR(uint8, CAN_CONFIG_DATA) ucCoreId;
  #endif
  /* Pointer to baud-rate configuration structure */
  P2CONST(Can_BaudrateConfigType, TYPEDEF, CAN_CONFIG_DATA) pBaudrateConfig;
} Can_ControllerPBConfigType;

/***********************************************************************************************************************
**                                        Extern declarations for Global Data                                         **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/
#endif /* CAN_PBTYPES_HEADER */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
