/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Eth_Cfg.h                                                                                           */
/*====================================================================================================================*/
/*                                  COPYRIGHT                                                                         */
/*====================================================================================================================*/
/* (c) 2023, 2024 Renesas Electronics Corporation. All rights reserved.                                               */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains pre-compile time parameters.                                                                    */
/* AUTOMATICALLY GENERATED FILE - DO NOT EDIT                                                                         */
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
/* Renesas shall not have any obligation to maintain, service or provide bug fixes for the supplied Product(s)        */
/* and/or the Application.                                                                                            */
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
/*              Devices:        R7F7025BxFABC                                                                         */
/*====================================================================================================================*/


/***********************************************************************************************************************
**                      Revision Control History                                                                      **
***********************************************************************************************************************/



/***********************************************************************************************************************
**                      Generation Tool Version                                                                       **
***********************************************************************************************************************/
/*                                                                                                                    */
/* TOOL VERSION:  EthU2Bx-E.dll version: 2.4.1, MCALConfGen.exe version: 2.3.0                                        */
/*                                                                                                                    */


/***********************************************************************************************************************
**                      Input File                                                                                    **
***********************************************************************************************************************/
/*
 * INPUT FILE:    C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\MCAL_RH850U2B24E_516_CodeGen\U2B24-E.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\modules\eth\generator\U2B24-E\R2211_eth_U2B24-E_BSWMDT.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\Dem\xml\Dem_eth.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\Os\xml\Os_eth.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\EcuC\xml\EcuC_eth.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\MCAL_RH850U2B24E_516_CodeGen\Translation.trxml
 * GENERATED ON:  10 Jul 2026 - 18:49:26
 */


#ifndef ETH_CFG_H
#define ETH_CFG_H


/***********************************************************************************************************************
**                      Include Section                                                                               **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                      Coding Rule Violations                                                                        **
***********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7                                                                       */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is accepted. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3684)    : Array declared with unknown size.                                                            */
/* Rule                : CERTCCM ARR02, MISRA C:2012 Rule-8.11                                                        */
/* JV-01 Justification : Arrays used are verified in the file which are only declarations and size is configuration   */
/*                       dependent.                                                                                   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (7:0791)    : Macro identifier does not differ from other macro identifier(s) (e.g. '%s') within the       */
/*                       specified number of significant characters.                                                  */
/* Rule                : CERTCCM DCL23, MISRA C:2012 Rule-5.4                                                         */
/* JV-01 Justification : This macro identifier is following AUTOSAR standard rule (Symbolic Name or Published         */
/*                       Macro's name), so this is accepted.                                                          */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/


/***********************************************************************************************************************
**                      Version Information                                                                           **
***********************************************************************************************************************/
#define ETH_AR_VERSION                                                          ETH_AR_R22_11_VERSION
/* AUTOSAR release version information */
#define ETH_CFG_AR_RELEASE_MAJOR_VERSION                                        4U
#define ETH_CFG_AR_RELEASE_MINOR_VERSION                                        8U
#define ETH_CFG_AR_RELEASE_REVISION_VERSION                                     0U
/* File version information */
#define ETH_CFG_SW_MAJOR_VERSION                                                2U
#define ETH_CFG_SW_MINOR_VERSION                                                4U
#define ETH_CFG_C_AR_RELEASE_MAJOR_VERSION                                      4U
#define ETH_CFG_C_AR_RELEASE_MINOR_VERSION                                      8U
#define ETH_CFG_C_AR_RELEASE_REVISION_VERSION                                   0U
#define ETH_CFG_C_SW_MAJOR_VERSION                                              2U
#define ETH_CFG_C_SW_MINOR_VERSION                                              4U

/***********************************************************************************************************************
**                      Common Published Information                                                                  **
***********************************************************************************************************************/
#define ETH_AR_RELEASE_MAJOR_VERSION_VALUE                                      4U
#define ETH_AR_RELEASE_MINOR_VERSION_VALUE                                      8U
#define ETH_AR_RELEASE_REVISION_VERSION_VALUE                                   0U
#define ETH_SW_MAJOR_VERSION_VALUE                                              2U
#define ETH_SW_MINOR_VERSION_VALUE                                              4U
#define ETH_SW_PATCH_VERSION_VALUE                                              1U
#define ETH_VENDOR_ID_VALUE                                                     59U
#define ETH_MODULE_ID_VALUE                                                     88U

/***********************************************************************************************************************
**                      Global Symbols                                                                                **
***********************************************************************************************************************/


/* Pre-compile option for Version Info API */
#define ETH_VERSION_INFO_API                                                    STD_ON

#define ETH_GWCA0_DATA_ISR                                                      STD_OFF
#define ETH_GWCA0_TSDATA_ISR                                                    STD_OFF
#define ETH_GWCA0_ERR_ISR                                                       STD_OFF
#define ETH_COMA_ERR_ISR                                                        STD_OFF
#define ETH_ETHA0_ERR_ISR                                                       STD_OFF
#define ETH_ETHA1_ERR_ISR                                                       STD_OFF
#define ETH_SGMII_ISR                                                           STD_ON
/* Pre-compile option for Control Enable for Address Filtering */
#define ETH_UPDATE_PHYS_ADDR_FILTER                                             STD_ON
#define ETH_GET_COUNTER_VALUES_API                                              STD_ON
#define ETH_GET_TX_ERROR_COUNTER_VALUES_API                                     STD_ON
/* Pre-compile option for EthGetDropCountApi API */
#define ETH_GET_DROP_COUNT_API                                                  STD_OFF
/* Pre-compile option for EthGetEtherStatsApi API */
#define ETH_GET_ETHER_STATS_API                                                 STD_OFF
#define ETH_GET_RX_STATS_API                                                    STD_ON
#define ETH_GET_TX_STATS_API                                                    STD_ON
/* Pre-compile option for EthCtrlEnableSpiInterface API */
#define ETH_CTRL_ENABLE_SPI_INTERFACE_API                                       STD_OFF
/* Pre-compile for Separation Filtering */
#define ETH_STREAM_FILTERING                                                    STD_OFF
/* Pre-compile option for EthDeInitApi API */
#define ETH_DEINIT_API                                                          STD_ON

/* Pre-compile option for Development Error Detect */
#define ETH_DEV_ERROR_DETECT                                                    STD_ON
/* Pre-compile option for enable or disable the critical section protection */
#define ETH_CRITICAL_SECTION_PROTECTION                                         STD_ON
/* Pre-compile option for enable or disable version check of inter-module dependencies */
#define ETH_VERSION_CHECK_EXT_MODULES                                           STD_ON
/* Enable/Disable Interrupt Consistency */
#define ETH_INTERRUPT_CONSISTENCY_CHECK                                         STD_OFF
/* Whether Eth uses Category 1 or Category 2 */
#define ETH_ISR_CATEGORY_2                                                      STD_OFF
/* Pre-compile option for MII Control Enable */
#define ETH_CTRL_ENABLE_MII                                                     STD_ON
/* Pre-compile option for Control Enable for receive Interrupt */
#define ETH_CTRL_ENABLE_RX_INTERRUPT                                            STD_OFF
/* Pre-compile option for Control Enable for transmit Interrupt */
#define ETH_CTRL_ENABLE_TX_INTERRUPT                                            STD_OFF
#define ETH_CTRL_ENABLE_RX_POLLING                                              STD_ON
#define ETH_CTRL_ENABLE_TX_POLLING                                              STD_ON

/* Pre-compile option for GlobalTime APIs */
#define ETH_GLOBAL_TIME_SUPPORT                                                 STD_OFF
#define ETH_ETHSWITCH_MANAGEMENT_SUPPORT                                        STD_OFF
/* PreCompile Option to enable / disable the Priority in Transmission */
#define ETH_QOS_SUPPORT                                                         STD_OFF
/* Enable / disable the checking whether registers are not corrupted in Eth_MainFunction */
#define ETH_REGISTER_CHECK_RUNTIME                                              STD_OFF
/* Enable / disable the checking whether registers are not stuck in Eth_Init */
#define ETH_REGISTER_CHECK_INITTIME                                             STD_OFF
/* Enable / disable bypass mode */
#define ETH_BYPASS_MODE                                                         STD_OFF
/* Enable/Disable multicore support */
#define ETH_MULTI_CORE_SUPPORT                                                  STD_ON
#define ETH_UPDATE_PHYS_ADDR_FILTER_LEGACY                                      STD_ON
#define ETH_UNINTENDED_INTERRUPT_CHECK                                          STD_OFF
/* Enable/Disable Interrupt Consistency */
#define ETH_INTERRUPT_CONSISTENCY_CHECK                                         STD_OFF
#define ETH_MACRO_ETNF                                                          STD_OFF
#define ETH_MACRO_ETNE                                                          STD_ON
#define ETH_MACRO_ETND                                                          STD_OFF
#define ETH_MACRO_ETNB                                                          STD_OFF
#define ETH_MACRO_ETNC                                                          STD_OFF
/* Pre-compile option for Switching Mode */
#define ETH_SWITCHING_MODE                                                      ETH_SWMODE_ENDSTATION
/* Instance ID of the ETH Driver */
#define ETH_INSTANCE_ID_VALUE                                                   0U
/* Maximum Ethernet Controllers Supported */
#define ETH_MAX_CTRLS_SUPPORTED                                                 0x04U
/* Total number of Ethernet controller config available */
#define ETH_TOTAL_CTRL_CONFIG                                                   0x02U
/* Total number of Ethernet core config */
#define ETH_TOTAL_CORE_CONFIG                                                   0x02U
/* Maximum Ethernet controller configed per core */
#define ETH_MAX_CTRL_CONFIG_PER_CODE                                            0x01U
/* Maximum Ethernet core supported */
#define ETH_SUPPORTED_CORE_MAX_NUM                                              0x03U
/* Maximum Ethernet Timeout Count */
#define ETH_TIMEOUT_COUNT                                                       63158UL
/* Ethernet EthRxBufTotal */
#define ETH_RX_BUF_TOTAL                                                        (uint16)0x0000U
#define ETH_ETNE_CTRLS_SUPPORTED                                                0x02U
/* The used Controller Index in Configset */
#define ETH_CTRLIDX_CONFIGSET_0                                                 0x00U
#define ETH_CTRLIDX_CONFIGSET_1                                                 0x01U

/* Peripheral clock value for the ETH Macro in Hz */
#define ETH_PERI_CLOCK_HZ                                                       100000000UL
#define ETH_TX_BUF_TOTAL_0                                                      64U
#define ETH_TX_BUF_TOTAL_1                                                      64U
#define ETH_RAM_SIZE_0                                                          0x0000EB40UL
#define ETH_RAM_SIZE_1                                                          0x0000EB40UL
#define ETHRSW0                                                                 ETH_CTRLIDX_CONFIGSET_0
#define ETHRSW1                                                                 ETH_CTRLIDX_CONFIGSET_1
#define ETH_PORT0                                                               ETH_CTRLIDX_CONFIGSET_0
#define ETH_PORT1                                                               ETH_CTRLIDX_CONFIGSET_1
#define ETH_OS_COUNTER_ID                                                       OsCounter
#define ETH_OS_COUNTER_MAX_VALUE                                                0U

/* MFWD Registers Base Address */
#define ETH_ETNE_MFWD_ADDRESS                                                   0xff900000UL
/* TSNA Registers Base Address */
#define ETH_ETNE_TSNA0_ADDRESS                                                  0xff90a000UL
#define ETH_ETNE_TSNA1_ADDRESS                                                  0xff90c000UL
/* RMAC Registers Base Address */
#define ETH_ETNE_RMAC0_ADDRESS                                                  0xff90b000UL
#define ETH_ETNE_RMAC1_ADDRESS                                                  0xff90d000UL
/* Controller - RACE Mapping */
#define ETH_CTRL0_ETHA_ADDRESS                                                  ETH_ETNE_TSNA0_ADDRESS
#define ETH_CTRL0_RMAC_ADDRESS                                                  ETH_ETNE_RMAC0_ADDRESS
#define ETH_CTRL1_ETHA_ADDRESS                                                  ETH_ETNE_TSNA1_ADDRESS
#define ETH_CTRL1_RMAC_ADDRESS                                                  ETH_ETNE_RMAC1_ADDRESS

#define ETH_HW_COMMON_INIT
#define ETH_HW_COMMON_DEINIT

#define ETH_HW_COMMON_POST_INIT

#define ETH_RSW2_GWCA_ID                                                        0UL

#define ETH_RSW2_BOTH_CORE_PORT_ID                                              0x00000004UL

/* GWCA Registers Base Address */
#define ETH_ETNE_GWCA0_ADDRESS                                                  0xff90e000UL

/* TOP Registers Base Address */
#define ETH_ETNE_TOP_ADDRESS                                                    0xff908000UL

/* COMA Registers Base Address */
#define ETH_ETNE_COMA_ADDRESS                                                   0xff909000UL

/* GPTP Registers Base Address */
#define ETH_ETNE_GPTP_ADDRESS                                                   0xff920000UL

/* Ethernet Configuration Set Handles */
#define Eth_Config                                                              (&Eth_GaaConfiguration[0])
#define EthConf_EthCtrlConfig_EthCtrlConfig                                     (uint8)0U
#define EthConf_EthCtrlConfig_EthCtrlConfig_001                                 (uint8)1U

/* Do not move the location of this include file */
#include "Eth_Common_LLDriver.h"

#include "Eth_ETNE_LLDriver.h"

#define ETH_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Eth_MemMap.h"

#define ETH_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Eth_MemMap.h"

#define ETH_START_SEC_VAR_INIT_PTR
#include "Eth_MemMap.h"

extern P2VAR(uint8, AUTOMATIC, ETH_VAR_INIT_PTR) Eth_GaaMemPoolBufferTable[];                                           /* PRQA S 3432, 3684 # JV-01, JV-01 */
extern P2VAR(Eth_TxBufferType, AUTOMATIC, ETH_VAR_INIT_PTR) Eth_GaaTxBufferMgrTable[];                                  /* PRQA S 3432, 3684 # JV-01, JV-01 */
#define ETH_STOP_SEC_VAR_INIT_PTR
#include "Eth_MemMap.h"

#define ETH_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Eth_MemMap.h"

extern CONST(uint32, ETH_CONFIG_DATA) Eth_GaaTxBufferTotal[];                                                           /* PRQA S 3684 # JV-01 */
extern CONST(volatile Eth_ETNE_RegType, ETH_CONFIG_DATA) Eth_GstETNE_Regs;
extern CONST(volatile Eth_RSW2_IntRegType, ETH_CONFIG_DATA) Eth_RSW2_IntReg;
extern CONST(uint32, ETH_CONFIG_DATA) Eth_GaaRamSize[];                                                                 /* PRQA S 3684 # JV-01 */
#define ETH_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Eth_MemMap.h"

#define ETH_START_SEC_CONST_32
#include "Eth_MemMap.h"

extern CONSTP2VAR(volatile Eth_ETNE_EICRegType, ETH_CONST, REGSPACE) Eth_GpETNE_EICRegs;
#define ETH_STOP_SEC_CONST_32
#include "Eth_MemMap.h"

#define ETH_START_SEC_VAR_INIT_16
#include "Eth_MemMap.h"

extern VAR(uint16, ETH_VAR_INIT) Eth_GaaDemEventAccess[];                                                               /* PRQA S 3684 # JV-01 */
extern VAR(uint16, ETH_VAR_INIT) Eth_GaaDemEventRxFramesLost[];                                                         /* PRQA S 3684 # JV-01 */
extern VAR(uint16, ETH_VAR_INIT) Eth_GaaDemEventCRC[];                                                                  /* PRQA S 3684 # JV-01 */
extern VAR(uint16, ETH_VAR_INIT) Eth_GaaDemEventUnderSizeFrame[];                                                       /* PRQA S 3684 # JV-01 */
extern VAR(uint16, ETH_VAR_INIT) Eth_GaaDemEventOverSizeFrame[];                                                        /* PRQA S 3684 # JV-01 */
extern VAR(uint16, ETH_VAR_INIT) Eth_GaaDemEventAlignment[];                                                            /* PRQA S 3684 # JV-01 */
extern VAR(uint16, ETH_VAR_INIT) Eth_GaaDemEventSinglecollision[];                                                      /* PRQA S 3684 # JV-01 */
extern VAR(uint16, ETH_VAR_INIT) Eth_GaaDemEventMultiplecollision[];                                                    /* PRQA S 3684 # JV-01 */
extern VAR(uint16, ETH_VAR_INIT) Eth_GaaDemEventLatecollision[];                                                        /* PRQA S 3684 # JV-01 */
#if (ETH_INTERRUPT_CONSISTENCY_CHECK == STD_ON)

extern VAR(uint16, ETH_VAR_INIT) Eth_GaaDemEventIntInconsistent[];                                                      /* PRQA S 3684 # JV-01 */
#endif

extern VAR(uint16, ETH_VAR_INIT) Eth_GaaDemEventDmaError[];                                                             /* PRQA S 3684 # JV-01 */
extern VAR(uint16, ETH_VAR_INIT) Eth_GaaDemEventEccError[];                                                             /* PRQA S 3684 # JV-01 */
#if ((ETH_REGISTER_CHECK_INITTIME == STD_ON) || (ETH_REGISTER_CHECK_RUNTIME == STD_ON))

extern VAR(uint16, ETH_VAR_INIT) Eth_GaaDemEventRegisterCorruption[];                                                   /* PRQA S 3684 # JV-01 */
#endif

extern VAR(uint16, ETH_VAR_INIT) Eth_GaaDemEventUnintendedIntChk[];                                                     /* PRQA S 3684 # JV-01 */
#define ETH_STOP_SEC_VAR_INIT_16
#include "Eth_MemMap.h"

#define ETH_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Eth_MemMap.h"

extern CONST(uint32, ETH_CONFIG_DATA) Eth_GaaTotalCtrlConfig[ETH_TOTAL_CORE_CONFIG];
#define ETH_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Eth_MemMap.h"

#define ETH_START_SEC_CONST_8
#include "Eth_MemMap.h"

extern CONST(uint8, ETH_VAR_INIT) Eth_GaaGetCoreId2Index[ETH_SUPPORTED_CORE_MAX_NUM];
#define ETH_STOP_SEC_CONST_8
#include "Eth_MemMap.h"

#define ETH_START_SEC_VAR_INIT_UNSPECIFIED
#include "Eth_MemMap.h"

extern VAR(Eth_StateType, ETH_VAR_INIT) Eth_GenDriverState[ETH_TOTAL_CORE_CONFIG];
#define ETH_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Eth_MemMap.h"


/***********************************************************************************************************************
**                      Global Data Types                                                                             **
***********************************************************************************************************************/



/***********************************************************************************************************************
**                      Global Data                                                                                   **
***********************************************************************************************************************/



/***********************************************************************************************************************
**                      Function Prototypes                                                                           **
***********************************************************************************************************************/



#endif /* ETH_CFG_H */


/***********************************************************************************************************************
**                      End of File                                                                                   **
***********************************************************************************************************************/

