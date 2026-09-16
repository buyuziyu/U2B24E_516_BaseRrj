/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Can.h                                                                                               */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2019-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Provision of external declaration of APIs and Service IDs.                                                         */
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
 *                      Update CAN_SW_PATCH_VERSION to 1U
 * 2.4.0: 30/05/2025  : Update SW-VERSION for RH850/Ver22.01.00 (D) U2Ax Release
 * 2.3.1: 31/03/2025  : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 *                    : Add message 1336 to support QA-C version 11.6.0
 * 2.3.0: 28/02/2025  : Update SW-VERSION for RH850/Ver22.01.00/Ver22.01.00.D Final Release
 *                      Change value of macro CAN_SW_MINOR_VERSION to 3
 * 2.2.0: 31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 *                      Change value of macro CAN_SW_PATCH_VERSION to 0
 *                      Change value of macro CAN_SW_MINOR_VERSION to 2
 * 2.1.2: 31/10/2024  : Change value of macro CAN_SW_PATCH_VERSION to 2
 *                      As part of CANXL driver support, following changes are made:
 *                      1. Fixing QAC message. Remove messages: 1336
 *                      2. Update condition for pHWUnitInfo in struct Can_ConfigType
 * 2.1.1: 30/08/2024  : As part of U2Cx driver support, following changes are made:
 *                      1. Change CAN_APPL_CODE to CAN_CALLOUT_CODE
 *                      As part of U2Bx-E driver support, following changes are made:
 *                      1. Update Can_ConfigType to support U2Bx-E
 *                      2. Change value of macro CAN_SW_MINOR_VERSION to 1U and CAN_SW_PATCH_VERSION to 1U
 *        01/06/2024  : As part of U2Cx driver support, following changes are made:
 *                      1. Remove pCoreID2Index and add macro in Can_ConfigType struct
 *                      2. Update struct Can_ConfigType to support Post Build Variant
 *                      3. Remove message 1534, 1536
 *                      As part of CANXL driver support, following changes are made:
 *                      1. Add global data types for CAN XL: usCanXLNoOfHohs, pCanXLHWUnitInfo, pCanXLHohConfig
 * 2.1.0: 23/02/2024  : Update SW Version to 2.1.0
 * 2.0.3: 09/04/2024  : Change value of macro CAN_SW_PATCH_VERSION to 3U
 * 2.0.2: 19/12/2023  : Update CAN_SW_PATCH_VERSION to 2U
 * 2.0.1: 19/10/2023  : Add message 1534, 1536, 1336
 *        14/10/2023  : Change DBTOC_DATA_UNSPECIFIED to CONFIG_DATA_POSTBUILD_UNSPECIFIED
 *                      Change macro CAN_AR_R21_11_VERSION to CAN_AR_R22_11_VERSION
 *                      Change value of macro CAN_SW_PATCH_VERSION to 1U
 * 2.0.0: 16/08/2023  : Add #include "SchM_Can.h"
 *        02/08/2023  : Remove multi instance and support multi core
 *                      Remove redundant QAC messages
 *                      Add CWE Rule
 *        28/06/2023  : Remove redundant QAC messages
 *        19/06/2023  : Add Can_GusHthCOMFIFO2Id to Can_ConfigType
 *        01/06/2023  : Update memclass of Can_GusHrhIndex2Id(CAN_RSCAN_CONFIG_DATA to CAN_CONFIG_DATA)
 *        22/05/2023  : Add Can_GusHrhIdex2Id to Can_ConfigType, pLpduCalloutReceiveFunction
 *                      Remove redundant QAC message
 *        06/05/2023  : Add CAN_START_SEC_PRIVATE_CODE, CAN_STOP_SEC_PRIVATE_CODE section
 *        28/04/2023  : Update to increase sw version:
 *                      - Change value of macro CAN_SW_MAJOR_VERSION to 2U
 *                      - Change value of macro CAN_SW_MINOR_VERSION to 0U
 * 1.5.0: 27/03/2023  : Add AUTOSAR release version information AUTOSAR R21-11.
 *                      Add Can_GetControllerTxErrorCounter and Can_GetControllerRxErrorCounter declaration
 *        02/03/2023  : Update to increase sw version
 * 1.4.5: 06/12/2022  : Update to increase sw version:
 *                      - Change value of macro CAN_SW_PATCH_VERSION to 5U
 * 1.4.4: 14/06/2022  : Update to increase sw version:
 *                      - Change value of macro CAN_SW_PATCH_VERSION to 4U
 * 1.4.3: 11/05/2022  : Change Common_ControllerStateType to Can_CommonControllerStateType;
 *                      COMMON_OK to CAN_COMMON_OK, COMMON_NOT_OK to CAN_COMMON_NOT_OK;
 *                      COMMON_STATE_STARTED to CAN_COMMON_STATE_STARTED; 
 *                      COMMON_STATE_STOPPED to CAN_COMMON_STATE_STOPPED;
 *                      COMMON_STATE_SLEEP to CAN_COMMON_STATE_SLEEP;
 *                      COMMON_STATE_WAKEUP to CAN_COMMON_STATE_WAKEUP;
 *                      MAX_VALID_STATE_TRANSITION to CAN_MAX_VALID_STATE_TRANSITION;
 *                      COMMON_IF_STATE_STARTED to CAN_COMMON_IF_STATE_STARTED;
 *                      COMMON_IF_STATE_STOPPED to CAN_COMMON_IF_STATE_STOPPED;
 *                      COMMON_IF_STATE_SLEEP to CAN_COMMON_IF_STATE_SLEEP;
 *                      COMMON_STATE_UNINIT to CAN_COMMON_STATE_UNINIT; Common_ReturnType to Can_CommonReturnType
 *        12/04/2022  : Remove macro CAN_SET_ICOM_CONFIGURATION_SID
 *        08/04/2022  : Update to increase sw version:
 *                      - Change value of macro CAN_SW_PATCH_VERSION to 3U
 * 1.4.2: 11/03/2022  : Update to increase sw version:
 *                      - Change value of macro CAN_SW_PATCH_VERSION to 2U
 * 1.4.1: 30/12/2021  : Update to increase sw version:
 *                      - Change value of macro CAN_SW_MINOR_VERSION to 4U
 *                      - Change value of macro CAN_SW_PATCH_VERSION to 1U
 * 1.4.0: 08/10/2021  : Update to increase sw version:
 *                      - Change value of macro CAN_SW_MINOR_VERSION to 4U
 *                      - Change value of macro CAN_SW_PATCH_VERSION to 0U
 * 1.3.2: 30/08/2021  : Update to support multi-instance:
 *                      - Add precondition check CAN_INSTANCE_INDEX
 *                      - Change include to Can_Mapping.h
 *                      - Change include to CAN_CFG_HEADER
 *                      - Add include to Can_MultiInstance.h
 * 1.3.1: 02/07/2021  : Add QAC message 9.5.0
 *                      Format source code to 120 characters
 *                      Improve Violation tag (remove START/END)
 *        06/05/2021  : Move all declarations of CAN MainFunctions from Can.h
 *                      to SchM_Can.h
 *        05/05/2021  : Update the memory section, memclass, ptrclass to change
 *                      the CAN_RSCAN prefix to CAN
 * 1.3.0: 20/01/2021  : Update input parameter from CONST to VAR of
 *                      Can_ChangeBaudrate, Can_SetBaudrate, Can_CheckBaudrate.
 * 1.2.0: 09/07/2020  : Release.
 *        28/07/2020  : Add QAC 9.3.1 comment.
 * 1.1.0: 19/06/2020  : Release.
 * 1.0.2: 15/05/2020  : As per #269867, Updated precondition for
 *                      Can_CheckBaudrate and Can_ChangeBaudrate.
 * 1.0.1: 05/02/2020  : Add Can_DeInit declaration for AR 4.3.1
 *        03/02/2020  : Add Can_GetControllerMode and
 *                      Can_GetControllerErrorState declaration for AR 4.3.1
 *        20/01/2020  : Update Controller State Machine function complying
 *                      with AR 4.3.1
 *        16/01/2020  : Update function declaration of reception callout
 *                      function comply with AR 4.3.1
 *        13/01/2020  : Disbale Can_ChangeBaudrate and Can_CheckBaudrate
 *                      comply with AR 4.3.1
 *        10/01/2020  : Update error code name and value comply with AR 4.3.1
 *        09/01/2020  : Support AUTOSAR version 4.3.1
 *                      - Use Common_ReturnType as representative of
 *                        Can_ReturnType and Std_ReturnType depending on
 *                        AUTOSAR Version
 * 1.0.0: 09/12/2019  : Initial version.
 */
/**********************************************************************************************************************/

#ifndef CAN_HEADER
#define CAN_HEADER

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/

/* Include standard Autosar Type */
#include "Std_Types.h"
/* CAN Pre-compile configuration Header File */
#include "Can_Cfg.h"
/* CAN Driver GeneralTypes Header File */
#include "Can_GeneralTypes.h"
/* Register structure Header file */
#include "Can_CommonRegStruct.h"

/* Included for declaration of MainFunction in scheduler */
#include "SchM_Can.h"

#include "ComStack_Types.h"
#if (CAN_MULTI_CORE_SUPPORT == STD_ON)
#include "Os.h"
#endif
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/

#define CAN_VENDOR_ID      CAN_VENDOR_ID_VALUE
#define CAN_MODULE_ID      CAN_MODULE_ID_VALUE
#define CAN_INSTANCE_ID    CAN_INSTANCE_ID_VALUE

/* AUTOSAR release version information */

#define CAN_AR_422_VERSION 422
#define CAN_AR_431_VERSION 431
#define CAN_AR_R22_11_VERSION 2211

#if (CAN_AR_VERSION == CAN_AR_422_VERSION)

#define CAN_AR_RELEASE_MAJOR_VERSION    4U
#define CAN_AR_RELEASE_MINOR_VERSION    2U
#define CAN_AR_RELEASE_REVISION_VERSION 2U

#elif (CAN_AR_VERSION == CAN_AR_431_VERSION)

#define CAN_AR_RELEASE_MAJOR_VERSION    4U
#define CAN_AR_RELEASE_MINOR_VERSION    3U
#define CAN_AR_RELEASE_REVISION_VERSION 1U

#elif (CAN_AR_VERSION == CAN_AR_R22_11_VERSION)

#define CAN_AR_RELEASE_MAJOR_VERSION    4U
#define CAN_AR_RELEASE_MINOR_VERSION    8U
#define CAN_AR_RELEASE_REVISION_VERSION 0U

#endif /* (CAN_AR_VERSION == CAN_AR_422_VERSION) */

/* Module Software version information */
#define CAN_SW_MAJOR_VERSION 2U
#define CAN_SW_MINOR_VERSION 4U
#define CAN_SW_PATCH_VERSION 1U

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:3684)    : Array declared with unknown size.                                                            */
/* Rule                : CERTCCM ARR02, MISRA C:2012 Rule-8.11                                                        */
/* JV-01 Justification : Arrays used are verified in the file which are only declarations and size is configuration   */
/*                       dependent.                                                                                   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE Rule CWE-398, CWE-569                                            */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is accepted. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:1336)    : Parameter identifiers missing in declaration of a function type.                             */
/* Rule                : MISRA C:2012 Rule-8.2, CWE Rule CWE-398, CWE-569                                             */
/* JV-01 Justification : Parameter identifiers are  missing however not impact the MCAL operation.                    */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/
#if (CAN_AR_VERSION == CAN_AR_422_VERSION)

#define Can_CommonReturnType          Can_ReturnType
#define CAN_COMMON_OK                  CAN_OK
#define CAN_COMMON_NOT_OK              CAN_NOT_OK

#define Can_CommonControllerStateType Can_StateTransitionType
#define CAN_COMMON_STATE_UNINIT
#define CAN_COMMON_STATE_STARTED       CAN_T_START
#define CAN_COMMON_STATE_STOPPED       CAN_T_STOP
#define CAN_COMMON_STATE_SLEEP         CAN_T_SLEEP
#define CAN_COMMON_STATE_WAKEUP        CAN_T_WAKEUP
#define CAN_MAX_VALID_STATE_TRANSITION CAN_T_WAKEUP
#define CAN_COMMON_IF_STATE_STARTED    CANIF_CS_STARTED
#define CAN_COMMON_IF_STATE_STOPPED    CANIF_CS_STOPPED
#define CAN_COMMON_IF_STATE_SLEEP      CANIF_CS_SLEEP

#elif ((CAN_AR_VERSION == CAN_AR_431_VERSION) || (CAN_AR_VERSION == CAN_AR_R22_11_VERSION))

#define Can_CommonReturnType          Std_ReturnType
#define CAN_COMMON_OK                  E_OK
#define CAN_COMMON_NOT_OK              E_NOT_OK

#define Can_CommonControllerStateType Can_ControllerStateType
#define CAN_COMMON_STATE_UNINIT        CAN_CS_UNINIT
#define CAN_COMMON_STATE_STARTED       CAN_CS_STARTED
#define CAN_COMMON_STATE_STOPPED       CAN_CS_STOPPED
#define CAN_COMMON_STATE_SLEEP         CAN_CS_SLEEP
#define CAN_COMMON_STATE_WAKEUP
#define CAN_MAX_VALID_STATE_TRANSITION CAN_CS_SLEEP
#define CAN_COMMON_IF_STATE_STARTED    CAN_CS_STARTED
#define CAN_COMMON_IF_STATE_STOPPED    CAN_CS_STOPPED
#define CAN_COMMON_IF_STATE_SLEEP      CAN_CS_SLEEP

#endif /* (CAN_AR_VERSION == CAN_AR_422_VERSION) */
/***********************************************************************************************************************
**                                                    Service IDs                                                     **
***********************************************************************************************************************/
/* Service ID for Can_Init */
#define CAN_INIT_SID                   (uint8)0x00U
/* Service ID for Can_MainFunction_Write */
#define CAN_MAIN_WRITE_SID             (uint8)0x01U
/* Service ID for Can_SetControllerMode */
#define CAN_SET_MODECNTRL_SID          (uint8)0x03U
/* Service ID for Can_DisableControllerInterupts */
#define CAN_DISABLE_CNTRL_INT_SID      (uint8)0x04U
/* Service ID for Can_EnableControllerInterupts */
#define CAN_ENABLE_CNTRL_INT_SID       (uint8)0x05U
/* Service ID for Can_Write */
#define CAN_WRITE_SID                  (uint8)0x06U
/* Service ID for Can_GetVersionInfo */
#define CAN_GET_VERSIONINFO_SID        (uint8)0x07U
/* Service ID for Can_MainFunction_Read */
#define CAN_MAIN_READ_SID              (uint8)0x08U
/* Service ID for Can_MainFunction_BusOff */
#define CAN_MAIN_BUSOFF_SID            (uint8)0x09U
/* Service ID for Can_MainFunction_Wakeup */
#define CAN_MAIN_WAKEUP_SID            (uint8)0x0AU
/* Service ID for Can_CheckWakeup */
#define CAN_CHECK_WAKEUP_SID           (uint8)0x0BU
/* Service ID for Can_MainFunction_Mode */
#define CAN_MAIN_MODE_SID              (uint8)0x0CU
/* Service ID for Can_ChangeBaudrate */
#define CAN_CHANGE_BAUDRATE_SID        (uint8)0x0DU
/* Service ID for Can_CheckBaudrate */
#define CAN_CHECK_BAUDRATE_SID         (uint8)0x0EU
/* Service ID for Can_SetBaudrate */
#define CAN_SET_BAUDRATE_SID           (uint8)0x0FU
/* Service ID for Can_DeInit */
#define CAN_DEINIT_SID                 (uint8)0x10U
/* Service ID for Can_GetControllerErrorState */
#define CAN_GET_ERRSTATECNTRL_SID      (uint8)0x11U
/* Service ID for Can_GetControllerMode */
#define CAN_GET_MODECNTRL_SID          (uint8)0x12U
/* Service ID for Can_RxProcessing */
#define CAN_RXPROCESSING_SID           (uint8)0x13U

/* DET ERRORS */
/* API service called with null Pointer */
#define CAN_E_PARAM_POINTER            (uint8)0x01U
/* API service called with wrong Handle */
#define CAN_E_PARAM_HANDLE             (uint8)0x02U
/* API service called with wrong Controller Id */
#define CAN_E_PARAM_CONTROLLER         (uint8)0x04U
/* API service called with de-initialization */
#define CAN_E_UNINIT                   (uint8)0x05U
/* API service called with wrong Transition */
#define CAN_E_TRANSITION               (uint8)0x06U

#if (CAN_AR_VERSION == CAN_AR_422_VERSION)

/* API service called with wrong DLC */
#define CAN_E_PARAM_DLC           (uint8)0x03U
/* Received CAN Message is lost */
#define CAN_E_DATALOST            (uint8)0x07U
/* API service called with invalid baudrate value */
#define CAN_E_PARAM_BAUDRATE      (uint8)0x08U
/* API service called with invalid ICOM configuration Id */
#define CAN_E_ICOM_CONFIG_INVALID (uint8)0x09U
/* API service called with invalid configuration set selection */
#define CAN_E_INIT_FAILED         (uint8)0x0AU

#elif (CAN_AR_VERSION == CAN_AR_431_VERSION)

/* API service called with wrong Data length */
#define CAN_E_PARAM_DATA_LENGTH   (uint8)0x03U
/* Received CAN Message is lost */
#define CAN_E_DATALOST            (uint8)0x01U
/* API service called with invalid baudrate value */
#define CAN_E_PARAM_BAUDRATE      (uint8)0x07U
/* API service called with invalid ICOM configuration Id */
#define CAN_E_ICOM_CONFIG_INVALID (uint8)0x09U
/* API service called with invalid configuration set selection */
#define CAN_E_INIT_FAILED         (uint8)0x09U

#elif (CAN_AR_VERSION == CAN_AR_R22_11_VERSION)
/* API service called with wrong Data length */
#define CAN_E_PARAM_DATA_LENGTH   (uint8)0x03U
/* Received CAN Message is lost */
#define CAN_E_DATALOST            (uint8)0x01U
/* API service called with invalid baudrate value */
#define CAN_E_PARAM_BAUDRATE      (uint8)0x07U
/* API service called with invalid configuration set selection */
#define CAN_E_INIT_FAILED         (uint8)0x09U
/* Service ID for Can_GetControllerRxErrorCounter */
#define CAN_GET_CONTROLLER_RXERROR_COUNTER_SID  (uint8)0x30U
/* Service ID for Can_GetControllerTxErrorCounter */
#define CAN_GET_CONTROLLER_TXERROR_COUNTER_SID  (uint8)0x31U

#endif
/* API service called with wrong database address */
#define CAN_E_INVALID_DATABASE (uint8)0xEFU

#if (CAN_MULTI_CORE_SUPPORT == STD_ON)
#define CAN_E_INVALID_CORE          (uint8)0xF1U
#endif

/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/
/* CAN Driver Initialization configuration */
typedef struct STag_Can_ConfigType
{
  /* StartOfDbToc */
  VAR(uint32, CAN_CONFIG_DATA) ulStartOfDbToc;
  /* Element number of HWUnitInfo */
  VAR(uint8, CAN_CONFIG_DATA) ucNoOfUnits;
  /* Element number of pControllerPCConfig and pControllerPBConfig */
  VAR(uint8, CAN_CONFIG_DATA) ucNoOfControllers;
  /* Element number of pHohConfig */
  VAR(uint16, CAN_CONFIG_DATA) usNoOfHohs;
  /* Pointer to HWUnit configuration structures */
  #if (CAN_RSCANFD_CONFIGURED == STD_ON)
  P2CONST(void, TYPEDEF, CAN_CONFIG_DATA) pHWUnitInfo;
  #endif
  /* Pointer to Controller Pre-compile Configuration structures */
  P2CONST(void, TYPEDEF, CAN_CONFIG_DATA) pControllerPCConfig;
  /* Pointer to Controller Post-build Configuration structures */
  P2CONST(void, TYPEDEF, CAN_CONFIG_DATA) pControllerPBConfig;
  /* Pointer to HTH/HRH configuration structures */
  P2CONST(void, TYPEDEF, CAN_CONFIG_DATA) pHohConfig;
  #if(CAN_CANXL_SUPPORTED == STD_ON)
  /* Element number of pHohConfig */
  VAR(uint16, TYPEDEF) usCanXLNoOfHohs;
  /* Pointer to CanXLHWUnit configuration structures */
  P2CONST(void, TYPEDEF, CAN_CONFIG_DATA) pCanXLHWUnitInfo;
  /* Pointer to HTH/HRH configuration structures */
  P2CONST(void, TYPEDEF, CAN_CONFIG_DATA) pCanXLHohConfig;
  /* Lookup table to get index of Controller from physical number of Channel */
  P2CONST(uint8, TYPEDEF, CAN_CONFIG_DATA) pCanXLPhysicalControllerToIndex;
  /* Lookup table to get index of Controller from physical number of Channel */
  P2CONST(uint8, TYPEDEF, CAN_CONFIG_DATA) pCanXLSecondPhysicalControllerToIndex;
  #endif 
  /* Lookup table to get index of Controller from physical number of Channel */
  P2CONST(uint8, TYPEDEF, CAN_CONFIG_DATA) pPhysicalControllerToIndex;
  #if(CAN_RX_OBJECT == STD_ON)
  /* MISRA Violation: START Msg(2:3432)-3 */
  P2CONST(uint16, TYPEDEF, CAN_CONFIG_DATA) Can_GusHrhIndex2Id;
  /* END Msg(2:3432)-3 */
  #endif
  #if (CAN_TX_COMFIFO == STD_ON)
  P2CONST(uint16, TYPEDEF, CAN_CONFIG_DATA) Can_GusHthCOMFIFO2Id;
  #endif
  #if (CAN_AR_VERSION == CAN_AR_R22_11_VERSION)
  P2FUNC(boolean, TYPEDEF, pLpduCalloutReceiveFunction)(uint16, Can_IdType, uint8, const uint8*);                       /* PRQA S 3432, 1336 # JV-01, JV-01 */
  #endif
  #if (((CAN_DEV_ERROR_DETECT == STD_ON) || (CAN_RX_FIFO == STD_ON)) && (CAN_MULTI_CORE_SUPPORT == STD_ON))
  VAR(uint8, CAN_CONFIG_DATA) ucKernelCoreID;
  #endif
  #if ((CAN_RX_COMFIFO == STD_ON) || (CAN_RX_FIFO == STD_ON))
  /* Element total number of HRH RxFIFO */
  VAR(uint16, CAN_CONFIG_DATA) ucTotalHrhRxFIFO;
  #endif
  #if ((CAN_RX_COMFIFO == STD_ON) || (CAN_RX_BUFFER == STD_ON))
  #if (CAN_NO_OF_UNITS == 3U)
  /* Element total number of HRH RXFIFO and COMFIFO of 1 unit */
  VAR(uint16, CAN_CONFIG_DATA) ucTotalHrhComFIFO0;
  /* Element total number of HRH RXFIFO and COMFIFO of 2 unit */
  VAR(uint16, CAN_CONFIG_DATA) ucTotalHrhComFIFO1;
  #endif /* #if (CAN_NO_OF_UNITS == 3U) */
  #if (CAN_NO_OF_UNITS == 2U)
  /* Element total number of HRH RXFIFO and COMFIFO of 1 unit */
  VAR(uint16, CAN_CONFIG_DATA) ucTotalHrhComFIFO0;
  #endif /* #if (CAN_NO_OF_UNITS == 2U) */
  /* Element total number of HRH RXFIFO and COMFIFO of all unit*/
  VAR(uint16, CAN_CONFIG_DATA) ucTotalHrhComFIFO;
  #endif /* #if (CAN_RX_COMFIFO == STD_ON) */
  #if (CAN_RX_BUFFER == STD_ON)
  #if (CAN_NO_OF_UNITS == 3U)
  /* Element total number of HRH 1 unit */
  VAR(uint16, CAN_CONFIG_DATA) ucTotalHrhBuffer0;
  /* Element total number of HRH 2 unit */
  VAR(uint16, CAN_CONFIG_DATA) ucTotalHrhBuffer1;
  #endif /* #if (CAN_NO_OF_UNITS == 3U) */
  #if (CAN_NO_OF_UNITS == 2U)
  /* Element total number of HRH 1 unit */
  VAR(uint16, CAN_CONFIG_DATA) ucTotalHrhBuffer0;
  #endif /* #if (CAN_NO_OF_UNITS == 2U) */
  /* Element total number of HRH */
  VAR(uint16, CAN_CONFIG_DATA) ucTotalHrhBuffer;
  #endif /* #if (CAN_RX_BUFFER == STD_ON) */
  #if (CAN_TX_COMFIFO == STD_ON)
  /* Element total number of HTH COMFIFO */
  VAR(uint16, CAN_CONFIG_DATA) ucTotalHthComFIFO;
  #endif
} Can_ConfigType;

/***********************************************************************************************************************
**                                        Extern declarations for Global Data                                         **
***********************************************************************************************************************/
#define CAN_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Can_MemMap.h"
/* Global array for Config structure */
extern CONST(Can_ConfigType, CAN_CONST) Can_GaaConfig[];                                                                /* PRQA S 3684 # JV-01 */

#define CAN_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Can_MemMap.h"
/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/
#define CAN_START_SEC_PUBLIC_CODE
#include "Can_MemMap.h"

/* API for global initialization */
extern FUNC(void, CAN_PUBLIC_CODE) Can_Init(P2CONST(Can_ConfigType, CAN_PUBLIC_CONST, CAN_APPL_DATA) Config);

#if (CAN_AR_VERSION == CAN_AR_422_VERSION)
#if (CAN_CHANGE_BAUDRATE_API == STD_ON)
/* API for changing baudrate of the Controller */
extern FUNC(Std_ReturnType, CAN_PUBLIC_CODE)
    Can_ChangeBaudrate(VAR(uint8, CAN_APPL_DATA) Controller, VAR(uint16, CAN_APPL_DATA) Baudrate);

/* API for checking baudrates configured for the Controller */
extern FUNC(Std_ReturnType, CAN_PUBLIC_CODE)
    Can_CheckBaudrate(VAR(uint8, CAN_APPL_DATA) Controller, VAR(uint16, CAN_APPL_DATA) Baudrate);
#endif
#endif

#if (CAN_SET_BAUDRATE_API == STD_ON)
/* API for changing baudrate of the Controller by ID value */
extern FUNC(Std_ReturnType, CAN_PUBLIC_CODE)
    Can_SetBaudrate(VAR(uint8, CAN_APPL_DATA) Controller, VAR(uint16, CAN_APPL_DATA) BaudRateConfigID);
#endif

/* API for set Controller mode */
extern FUNC(Can_CommonReturnType, CAN_PUBLIC_CODE) Can_SetControllerMode(
  VAR(uint8, CAN_APPL_DATA) Controller, VAR(Can_CommonControllerStateType, CAN_APPL_DATA) Transition);

#if ((CAN_AR_VERSION == CAN_AR_431_VERSION) || (CAN_AR_VERSION == CAN_AR_R22_11_VERSION))

/* API for global de-initialization */
extern FUNC(void, CAN_PUBLIC_CODE) Can_DeInit(void);

/* API for obtaining Controller error state */
extern FUNC(Std_ReturnType, CAN_PUBLIC_CODE) Can_GetControllerErrorState(
  VAR(uint8, CAN_APPL_DATA) ControllerId, P2VAR(Can_ErrorStateType, AUTOMATIC, CAN_APPL_DATA) ErrorStatePtr);           /* PRQA S 3432 # JV-01 */

/* API for obtaining Controller mode */
extern FUNC(Std_ReturnType, CAN_PUBLIC_CODE) Can_GetControllerMode(
  VAR(uint8, CAN_APPL_DATA) Controller, P2VAR(Can_ControllerStateType, AUTOMATIC, CAN_APPL_DATA) ControllerModePtr);    /* PRQA S 3432 # JV-01 */
#endif

/* API for disabling Controller interrupt */
extern FUNC(void, CAN_PUBLIC_CODE) Can_DisableControllerInterrupts(VAR(uint8, CAN_APPL_DATA) Controller);

/* API for enabling Controller interrupt */
extern FUNC(void, CAN_PUBLIC_CODE) Can_EnableControllerInterrupts(VAR(uint8, CAN_APPL_DATA) Controller);

/* API for Can Write */
extern FUNC(Can_CommonReturnType, CAN_PUBLIC_CODE)
    Can_Write(VAR(Can_HwHandleType, CAN_APPL_DATA) Hth, P2CONST(Can_PduType, AUTOMATIC, CAN_APPL_DATA) PduInfo);

#if (CAN_VERSION_INFO_API == STD_ON)
/* API for getting version information */
extern FUNC(void, CAN_PUBLIC_CODE) Can_GetVersionInfo(
                                                    P2VAR(Std_VersionInfoType, AUTOMATIC, CAN_APPL_DATA) versioninfo);  /* PRQA S 3432 # JV-01 */
#endif

#if (CAN_CHECK_WAKEUP_API == STD_ON)
/* API for getting wakeup status of a controller */
extern FUNC(Can_CommonReturnType, CAN_PUBLIC_CODE) Can_CheckWakeup(VAR(uint8, CAN_APPL_DATA) Controller);
#endif

#if (CAN_AR_VERSION == CAN_AR_R22_11_VERSION)
extern FUNC(Std_ReturnType, CAN_PUBLIC_CODE) Can_GetControllerTxErrorCounter(
  VAR(uint8, AUTOMATIC) ControllerId,
  P2VAR(uint8, AUTOMATIC, CAN_APPL_DATA) TxErrorCounterPtr);                                                            /* PRQA S 3432 # JV-01 */
extern FUNC(Std_ReturnType, CAN_PUBLIC_CODE) Can_GetControllerRxErrorCounter(
  VAR(uint8, AUTOMATIC) ControllerId,
  P2VAR(uint8, AUTOMATIC, CAN_APPL_DATA) RxErrorCounterPtr);                                                            /* PRQA S 3432 # JV-01 */
#endif

#define CAN_STOP_SEC_PUBLIC_CODE
#include "Can_MemMap.h"

#if ((CAN_AR_VERSION == CAN_AR_422_VERSION) || (CAN_AR_VERSION == CAN_AR_431_VERSION))
#define CAN_START_SEC_APPL_CODE
#include "Can_MemMap.h"

#if defined(CAN_LPDU_RECEIVE_CALLOUT_FUNCTION)
extern FUNC(boolean, CAN_CALLOUT_CODE)
    CAN_LPDU_RECEIVE_CALLOUT_FUNCTION(VAR(uint16, CAN_APPL_DATA) Hrh, VAR(Can_IdType, CAN_APPL_DATA) CanId,
                                      #if (CAN_AR_VERSION == CAN_AR_422_VERSION)
                                      VAR(uint8, CAN_APPL_DATA) CanDlc,
                                      #elif (CAN_AR_VERSION == CAN_AR_431_VERSION)
                                      VAR(uint8, CAN_APPL_DATA) CanDataLength,
                                      #endif
                                      P2CONST(uint8, AUTOMATIC, CAN_APPL_DATA) CanSduPtr);
#endif

#define CAN_STOP_SEC_APPL_CODE
#include "Can_MemMap.h"
#endif

#define CAN_START_SEC_PRIVATE_CODE
#include "Can_MemMap.h"

#if (CAN_DEV_ERROR_DETECT == STD_ON)
/* API for common DET validation */
extern FUNC(Can_CommonReturnType, CAN_PRIVATE_CODE)
    Can_CommonDetCheck(CONST(uint8, AUTOMATIC) LucSID, CONST(uint8, AUTOMATIC) LucController);
#endif

#define CAN_STOP_SEC_PRIVATE_CODE
#include "Can_MemMap.h"


#endif /* CAN_HEADER */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
