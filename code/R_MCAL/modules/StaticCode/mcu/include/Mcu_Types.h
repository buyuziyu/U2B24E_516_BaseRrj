/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2X MCAL Components                                                                 */
/* Module       = Mcu_Types.h                                                                                         */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Provision of API information.                                                                                      */
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
/*              Devices:        X2X                                                                                   */
/*====================================================================================================================*/

/***********************************************************************************************************************
**                                              Revision Control History                                              **
***********************************************************************************************************************/
/*
 * 2.5.1:  30/06/2025   : Update SW-VERSION for U2Bx Ver22.02.00.001 Release
 * 2.5.0:  30/06/2025   : Update SW-VERSION for U2Ax Ver22.01.00(D) Release
 * 2.4.0:  31/05/2025   : Update SW-VERSION for U2Cx Ver21.01.01 Release
 * 2.3.2:  29/04/2025   : Update SW-VERSION for U2Ax Ver22.00.03 Release
 * 2.3.1:  31/03/2025   : Update SW-VERSION for U2BxE Ver22.00.02 Release
 * 2.3.0:  28/02/2025   : Update SW-VERSION for Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024   : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Release
 * 2.1.2:  31/10/2024   : Update SW-VERSION to 2.1.2
 * 2.1.1:  30/08/2024   : Update SW-VERSION to 2.1.1
 *         12/06/2024   : As part of ARDAACL-46027 (ARDAACL-45132), following changes are made:
 *                        - Remove MCU_ECM_APP_RST in Mcu_ResetType for U2Cx device
 *                        As part of U2Bx-E device support, following changes are made:
 *                        - Add Mcu_ResetType enum for U2Bx-E device
 *                        As part of U2Cx device support, following changes are made:
 *                        - Add Mcu_ResetType enum for U2Cx device
 *                        As part of QAC 9.5.0 support, following changes are made:
 *                        - Remove redundant QAC message 1534 and 1536
 * 2.0.0:  04/07/2023   : In Mcu_ResetType defined for U2Bx, add 'MCU_DSMIF0_COMP_ERR_RST', 'MCU_DSMIF1_COMP_ERR_RST'
 *         11/05/2023   : In Mcu_ResetType defined for U2Bx, remove 'MCU_POWEROF_STANDBY_RST', 
 *                        add 'MCU_OSTM5_INT_RST', change 'MCU_CLMA_HBUS_ERR_RST' to 'MCU_CLMA_SBUS_ERR_RST'
 * 1.4.5:  06/01/2023   : As new Mcu structure:
 *                        - Update definitions of Mcu_ConfigType, Mcu_ClockModuleType, Mcu_ClkShiftType, Mcu_ClkModeType
 * 1.4.3:  23/06/2022   : Update QAC Message (2:3432), (2:0647), (2:3630) description
 *         21/06/2022   : Remove MCU_DEVICE_E2X, MCU_DEVICE_U2AX, MCU_DEVICE_U2BX macro
 *         21/03/2022   : In Mcu_ResetType defined, remove MCU_PSEQ_RAM_ECC_2BIT_ERR_RST, MCU_PSEQ_RAM_ECC_1BIT_ERR_RST
 *         13/04/2022   : Update SW-VERSION to 1.4.3
 * 1.3.2:  27/09/2021   : Add Mcu_ResetType enum for U2Bx device
 *                        Update Mcu_ModeSettingType support for U2Bx device
 *                        Update Mcu_WakeUpFactorInfoType support for U2Bx device
 * 1.3.1:  02/07/2021   : Add QAC message 9.5.0
 *                        Format source code to 120 characters
 *                        Improve Violation tag (remove START/END)
 * 1.2.0:  17/07/2020   : Release
 * 1.1.0:  19/06/2020   : Release
 * 1.0.1:  21/05/2020   : As per ticket #271167
 *                        Update list of reset reason for E2x devices
 *                        Removed MCU_LRAM_ADR_PARITY_ERR_RST,
 *                        MCU_BARRIERSYNC_COMP_ERR_RST,
 *                        MCU_FACI_RST_TRANS_ERR_RST,
 *                        MCU_IPIR_COMP_ERR_RST
 * 1.0.0:  10/01/2020   : Initial Version
 */
/**********************************************************************************************************************/
#ifndef MCU_TYPES_H
#define MCU_TYPES_H

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:1336)    : Parameter identifiers missing in declaration of a function type.                             */
/* Rule                : MISRA C:2012 Rule-8.2, CWE Rule CWE-398, CWE-569                                             */
/* JV-01 Justification : Parameter identifiers are  missing however not impact the MCAL operation.                    */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE Rule CWE-398, CWE-569                                            */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is accepted. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3630)    : The implementation of this struct/union type should be hidden.                               */
/* Rule                : MISRA C:2012 Dir-4.8                                                                         */
/* JV-01 Justification : This is accepted. Redundant of struct or union type has no affect to driver operation.       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Standard AUTOSAR types */
#include "Std_Types.h"

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */

#define MCU_TYPES_AR_RELEASE_MAJOR_VERSION    MCU_AR_RELEASE_MAJOR_VERSION
#define MCU_TYPES_AR_RELEASE_MINOR_VERSION    MCU_AR_RELEASE_MINOR_VERSION
#define MCU_TYPES_AR_RELEASE_REVISION_VERSION MCU_AR_RELEASE_REVISION_VERSION

/* File version information */
#define MCU_TYPES_SW_MAJOR_VERSION            MCU_SW_MAJOR_VERSION
#define MCU_TYPES_SW_MINOR_VERSION            MCU_SW_MINOR_VERSION

/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/
#define MCU_E2X                       0U
#define MCU_U2AX                      1U
#define MCU_U2BX                      2U
#define MCU_U2CX                      3U
#define MCU_U2BXE                     4U
/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/

/* Type definition for Mcu_ClockType used by the API Mcu_InitClock */
typedef uint8 Mcu_ClockType;

/* Type definition for Mcu_RawResetType used by the API Mcu_GetResetRawValue */
typedef uint32 Mcu_RawResetType;

/* Type definition for Mcu_ModeType used by the API Mcu_SetMode */
typedef uint8 Mcu_ModeType;

/* Type definition for Mcu_RamSectionType used by the API Mcu_InitRamSection */
typedef uint8 Mcu_RamSectionType;

/* Structure for MCU Init Configuration */
typedef struct STag_Mcu_ConfigType
{
  /* Database start value */
  uint32 ulStartOfDbToc;

  /* The number of clock settings configured  */
  uint8 ucNofClockSettings;

  /* Pointer to MCU Clock Setting configuration */
  P2CONST(void, AUTOMATIC, MCU_CONFIG_CONST) pClockSetting;

  /* Pointer to MCU RAM Setting configuration */
  P2CONST(void, AUTOMATIC, MCU_CONFIG_CONST) pRamSetting;

  #if (MCU_ECM_OPERATION == STD_ON)
  /* Pointer to MCU ECM Setting configuration */
  P2CONST(void, AUTOMATIC, MCU_CONFIG_CONST) pEcmSetting;

  /* Pointer to callback FE interrupt notification function */
  P2FUNC(void, AUTOMATIC, pFeintNotificationPtr)(uint16);                                                               /* PRQA S 1336, 3432 # JV-01, JV-01 */

  /* Pointer to callback EI DCLS interrupt notification function */
  P2FUNC(void, AUTOMATIC, pEiintDCLSNotificationPtr)(uint16);                                                           /* PRQA S 1336, 3432 # JV-01, JV-01 */

  /* Pointer to callback EI interrupt notification function */
  P2FUNC(void, AUTOMATIC, pEiintNotificationPtr)(uint16);                                                               /* PRQA S 1336, 3432 # JV-01, JV-01 */
  #endif

  #if (MCU_VMON_DIAG_OPERATION == STD_ON)
  /* Pointer to MCU Voltage Moniter Setting configuration */
  P2CONST(void, AUTOMATIC, MCU_CONFIG_CONST) pVmonSetting;
  #endif

  /* Pointer to MCU Mode setting configuration */
  P2CONST(void, AUTOMATIC, MCU_CONFIG_CONST) pModeSetting;

  #if (MCU_DMON_DIAG_OPERATION == STD_ON)
  /* Pointer to MCU Delay Moniter Setting configuration */
  P2CONST(void, TYPEDEF, MCU_CONFIG_DATA) pDmonSetting;
  #endif

  /* Pointer to HW Information of clock controller */
  P2CONST(void, TYPEDEF, MCU_CONFIG_DATA) pClockHwInfo;

  /* Pointer to HW Information of reset controller */
  P2CONST(void, TYPEDEF, MCU_CONFIG_DATA) pRstHwInfo;

  #if (MCU_MODE_TRANSITION_SUPPORT == STD_ON)
  /* Pointer to HW Information of Standby  */
  P2CONST(void, TYPEDEF, MCU_CONFIG_DATA) pStbHwInfo;
  #endif

  #if (MCU_CLMA_OPERATION == STD_ON)
  /* Pointer to HW Information of Clock Monitor  */
  P2CONST(void, TYPEDEF, MCU_CONFIG_DATA) pClmHwInfo;
  #endif

  #if (MCU_GETWAKEUPFACTOR_API == STD_ON)
  /* Pointer to HW Information of Wake up Factor Monitor  */
  P2CONST(void, TYPEDEF, MCU_CONFIG_DATA) pWUFMONHwInfo;
  #endif
  
  #if ((MCU_GETWAKEUPFACTOR_API == STD_ON) || (MCU_CLEARANDSETWAKEUPFACTOR_API == STD_ON))
  /* Pointer to HW Information of Wake up Factor   */
  P2CONST(void, TYPEDEF, MCU_CONFIG_DATA) pWUFHwInfo;
  #endif

  #if (MCU_RELEASEIOBUFFERHOLD_API == STD_ON)
  /* Pointer to HW Information of IO Buffer Hold  */
  P2CONST(void, TYPEDEF, MCU_CONFIG_DATA) pIOBufferHoldHwInfo;
  #endif

  #if (MCU_VMON_DIAG_OPERATION == STD_ON)
  /* Pointer to HW Information of Vmon */
  P2CONST(void, TYPEDEF, MCU_CONFIG_DATA) pVmonHwInfo;
  #endif

  #if (MCU_DMON_DIAG_OPERATION == STD_ON)
  /* Pointer to HW Information of Dmon */
  P2CONST(void, TYPEDEF, MCU_CONFIG_DATA) pDmonHwInfo;
  #endif

  /* Pointer to HW Information of Ecc */
  P2CONST(void, TYPEDEF, MCU_CONFIG_DATA) pEccHwInfo;

  #if (MCU_ECM_OPERATION == STD_ON)
  /* Pointer to HW Information of Ecm */
  P2CONST(void, TYPEDEF, MCU_CONFIG_DATA) pEcmHwInfo;
  #endif
} Mcu_ConfigType;

/* Status value returned by the API Mcu_GetPllStatus */
typedef enum ETag_Mcu_PllStatusType
{
  MCU_PLL_LOCKED = 0,
  MCU_PLL_UNLOCKED,
  MCU_PLL_STATUS_UNDEFINED
} Mcu_PllStatusType;

/* Type of reset supported by the hardware */
#if (MCU_DEVICE_NAME == MCU_E2X)
typedef enum ETag_Mcu_ResetType
{
  MCU_POWER_ON_RESET = 0,
  MCU_STANDBY_RST,
  MCU_EXT_RST,
  MCU_VMON_RST,
  MCU_SW_SYS_RST,
  MCU_SWDT_SYS_RST,
  MCU_ECM_SYS_RST,
  MCU_SW_APP_RST,
  MCU_SWDT_APP_RST,
  MCU_ECM_APP_RST,
  MCU_ICUM_SW_SYS_RST,
  MCU_ICUM_SW_APP_RST,
  MCU_DCLS_COMP_ERR_PE0_RST,
  MCU_DCLS_COMP_ERR_PE1_RST,
  MCU_WDT_CH0_ERR_RST,
  MCU_WDT_CH1_ERR_RST,
  MCU_LRAM_ADR_ERR_PE0_RST,
  MCU_LRAM_ADR_ERR_PE1_RST,
  MCU_LRAM_ECC2BIT_ERR_PE0_RST,
  MCU_LRAM_ECC2BIT_ERR_PE1_RST,
  MCU_LRAM_ECC1BIT_ERR_PE0_RST,
  MCU_LRAM_ECC1BIT_ERR_PE1_RST,
  MCU_LRAM_ERRADR_OFLOW_PE0_RST,
  MCU_LRAM_ERRADR_OFLOW_PE1_RST,
  MCU_ICACHE_ADR_ERR_PE0_RST,
  MCU_ICACHE_ADR_ERR_PE1_RST,
  MCU_ICACHE_EDC_ERR_PE0_RST,
  MCU_ICACHE_EDC_ERR_PE1_RST,
  MCU_PEGUARD_ERR_PE0_RST,
  MCU_PEGUARD_ERR_PE1_RST,
  MCU_CLMA5_ERR_RST,
  MCU_CLMA6_ERR_RST,
  MCU_OSTM1_INT_RST,
  MCU_OSTM2_INT_RST,
  MCU_UNINTEND_DBG_EN_PE0_RST,
  MCU_UNINTEND_DBG_EN_PE1_RST,
  MCU_PEG_OTHER_LRAMREQ_PE0_RST,
  MCU_PEG_OTHER_LRAMREQ_PE1_RST,
  MCU_CRAM_ADDRESS_ERR_RST,
  MCU_CRAM_ECC2BIT_ERR_RST,
  MCU_CRAM_ECC1BIT_ERR_RST,
  MCU_CRAM_ERR_ADR_OFLOW_RST,
  MCU_LRAM_ECC2BIT_ERR_RST,
  MCU_LRAM_ECC1BIT_ERR_RST,
  MCU_LRAM_ERR_ADR_OFLOW_RST,
  MCU_SDMAC0_RAM_ECC2BIT_ERR_RST,
  MCU_SDMAC0_RAM_ECC1BIT_ERR_RST,
  MCU_SDMAC1_RAM_ECC2BIT_ERR_RST,
  MCU_SDMAC1_RAM_ECC1BIT_ERR_RST,
  MCU_DTSRAM_ECC2BIT_ERR_RST,
  MCU_DTSRAM_ECC1BIT_ERR_RST,
  MCU_DTSRAM_ERR_ADR_OFLOW_RST,
  MCU_PERIRAM_ERR_ADR_OFLOW_RST,
  MCU_FRRAM_ECC2BIT_ERR_RST,
  MCU_FRRAM_ECC1BIT_ERR_RST,
  MCU_CANRAM_ECC2BIT_ERR_RST,
  MCU_CANRAM_ECC1BIT_ERR_RST,
  MCU_DFERAM_ECC2BIT_ERR_RST,
  MCU_DFERAM_ECC1BIT_ERR_RST,
  MCU_GTMRAM_ECC2BIT_ERR_RST,
  MCU_GTMRAM_ECC1BIT_ERR_RST,
  MCU_ETHRAM_ECC2BIT_ERR_RST,
  MCU_ETHRAM_ECC1BIT_ERR_RST,
  MCU_CFLH_ERR_ADR_PRTY_ERR_RST,
  MCU_CFLH_ECC2BIT_ERR_RST,
  MCU_CFLH_ECC1BIT_ERR_RST,
  MCU_CFLH_ERR_ADR_OFLOW_RST,
  MCU_DFLH_ECC2BIT_ERR_RST,
  MCU_DFLH_ECC1BIT_ERR_RST,
  MCU_DFLH_ERR_ADR_OFLOW_RST,
  MCU_DATABUS_ECC2BIT_ERR_RST,
  MCU_DATABUS_ECC1BIT_ERR_RST,
  MCU_ADRBUS_EDC_ECC_ERR_RST,
  MCU_CRAM_GUARD_ERR_RST,
  MCU_PBUS_GUARD_ERR_RST,
  MCU_HBUS_GUARD_ERR_RST,
  MCU_IBUS_GUARD_ERR_RST,
  MCU_CLMA0_ERR_RST,
  MCU_CLMA1_ERR_RST,
  MCU_CLMA2_ERR_RST,
  MCU_CLMA3_ERR_RST,
  MCU_CLMA4_ERR_RST,
  MCU_AD_PARITY_ERR_RST,
  MCU_MISG_COMP_ERR_RST,
  MCU_DTS_COMP_ERR_RST,
  MCU_EXT_ERRIN_RST,
  MCU_FLASH_ACCESS_ERR_RST,
  MCU_DMA_COMP_ERR_RST,
  MCU_BUS_BRIDGECOMP_ERROR_RST,
  MCU_INTER_PROC_ELEMENT_BUS_RST,
  MCU_INTER_CLUSTER_BUS_RST,
  MCU_PHERIPHERAL_BUS_RST,
  MCU_CRAM_BUS_RST,
  MCU_SYSTEM_BUS_RST,
  MCU_GLOBAL_FLASH_BUS_RST,
  MCU_LOCAL_FLASH_BUS_RST,
  MCU_EVCC_SECONDARY_HDET_RST,
  MCU_EVCC_SECONDARY_LDET_RST,
  MCU_VCC_SECONDARY_HDET_RST,
  MCU_VCC_SECONDARY_LDET_RST,
  MCU_VDD_SECONDARY_HDET_RST,
  MCU_VDD_SECONDARY_LDET_RST,
  MCU_MODE_ERR_0_RST,
  MCU_MODE_ERR_1_RST,
  MCU_MODE_ERR_2_RST,
  MCU_MODE_ERR_3_RST,
  MCU_MODE_ERR_4_RST,
  MCU_MODE_ERR_5_RST,
  MCU_MODE_ERR_6_RST,
  MCU_ECM_COMP_ERR_RST,
  MCU_ECM_DLY_TIMER_OFLOW_RST,
  MCU_CLMA7_ERR_RST,
  MCU_CLMA8_ERR_RST,
  MCU_CLMA9_ERR_RST,
  MCU_CLMA10_ERR_RST,
  MCU_DCLS_COMP_ERR_PE4_RST,
  MCU_DCLS_COMP_ERR_PE5_RST,
  MCU_ICACHE_ADR_ERR_PE2_RST,
  MCU_ICACHE_ADR_ERR_PE3_RST,
  MCU_ICACHE_ADR_ERR_PE4_RST,
  MCU_ICACHE_ADR_ERR_PE5_RST,
  MCU_ICACHE_EDC_ERR_PE2_RST,
  MCU_ICACHE_EDC_ERR_PE3_RST,
  MCU_ICACHE_EDC_ERR_PE4_RST,
  MCU_ICACHE_EDC_ERR_PE5_RST,
  MCU_LRAM_ADR_ERR_PE2_RST,
  MCU_LRAM_ADR_ERR_PE3_RST,
  MCU_LRAM_ADR_ERR_PE4_RST,
  MCU_LRAM_ADR_ERR_PE5_RST,
  MCU_LRAM_ECC1BIT_ERR_PE2_RST,
  MCU_LRAM_ECC1BIT_ERR_PE3_RST,
  MCU_LRAM_ECC1BIT_ERR_PE4_RST,
  MCU_LRAM_ECC1BIT_ERR_PE5_RST,
  MCU_LRAM_ECC2BIT_ERR_PE2_RST,
  MCU_LRAM_ECC2BIT_ERR_PE3_RST,
  MCU_LRAM_ECC2BIT_ERR_PE4_RST,
  MCU_LRAM_ECC2BIT_ERR_PE5_RST,
  MCU_LRAM_ERRADR_OFLOW_PE2_RST,
  MCU_LRAM_ERRADR_OFLOW_PE3_RST,
  MCU_LRAM_ERRADR_OFLOW_PE4_RST,
  MCU_LRAM_ERRADR_OFLOW_PE5_RST,
  MCU_OSTM3_INT_RST,
  MCU_OSTM4_INT_RST,
  MCU_OSTM5_INT_RST,
  MCU_OSTM6_INT_RST,
  MCU_PEG_OTHER_LRAMREQ_PE2_RST,
  MCU_PEG_OTHER_LRAMREQ_PE3_RST,
  MCU_PEG_OTHER_LRAMREQ_PE4_RST,
  MCU_PEG_OTHER_LRAMREQ_PE5_RST,
  MCU_PEGUARD_ERR_PE2_RST,
  MCU_PEGUARD_ERR_PE3_RST,
  MCU_PEGUARD_ERR_PE4_RST,
  MCU_PEGUARD_ERR_PE5_RST,
  MCU_UNINTEND_DBG_EN_PE2_RST,
  MCU_UNINTEND_DBG_EN_PE3_RST,
  MCU_UNINTEND_DBG_EN_PE4_RST,
  MCU_UNINTEND_DBG_EN_PE5_RST,
  MCU_WDT_CH1_ERR_PE2_RST,
  MCU_WDT_CH1_ERR_PE3_RST,
  MCU_WDT_CH1_ERR_PE4_RST,
  MCU_WDT_CH1_ERR_PE5_RST,
  MCU_MULTI_RST,
  MCU_RESET_UNDEFINED,
  MCU_NON_RST,
  MCU_RESERVED_RST
} Mcu_ResetType;
#elif (MCU_DEVICE_NAME == MCU_U2AX)
typedef enum ETag_Mcu_ResetType
{
  MCU_POWER_ON_RESET = 0,
  MCU_EXT_RST,
  MCU_VMON_RST,
  MCU_SW_SYS_RST,
  MCU_ECM_SYS_RST,
  MCU_WDTBA_SYS_RST,
  MCU_SW_APP_RST,
  MCU_ECM_APP_RST,
  MCU_DEEPSTOP_RST,
  MCU_ICUM_SW_SYS_RST,
  MCU_ICUM_SW_APP_RST,
  MCU_ECM_DLY_TIMER_OFLOW_RST,
  MCU_ECM_COMP_ERR_RST,
  MCU_MODE_ERR_0_RST,
  MCU_MODE_ERR_1_RST,
  MCU_MODE_ERR_2_RST,
  MCU_MODE_ERR_3_RST,
  MCU_MODE_ERR_4_RST,
  MCU_MODE_ERR_5_RST,
  MCU_MODE_ERR_6_RST,
  MCU_FLASH_ACCESS_ERR_RST,
  MCU_DTS_COMP_ERR_RST,
  MCU_DMA_COMP_ERR_RST,
  MCU_BUS_BRIDGECOMP_ERROR_RST,
  MCU_INTER_PROC_ELEMENT_BUS_RST,
  MCU_INTER_CLUSTER_BUS_RST,
  MCU_PHERIPHERAL_BUS_RST,
  MCU_CRAM_BUS_RST,
  MCU_SYSTEM_BUS_RST,
  MCU_GLOBAL_FLASH_BUS_RST,
  MCU_LOCAL_FLASH_BUS_RST,
  MCU_CLMA_MOSC_ERR_RST,
  MCU_CLMA_HOSC_ERR_RST,
  MCU_CLMA_LOSC_ERR_RST,
  MCU_CLMA_LSB_ERR_RST,
  MCU_CLMA_UHSB_ERR_RST,
  MCU_CLMA_HBUS_ERR_RST,
  MCU_OSTM1_INT_RST,
  MCU_OSTM2_INT_RST,
  MCU_OSTM3_INT_RST,
  MCU_OSTM4_INT_RST,
  MCU_OSTM5_INT_RST,
  MCU_OSTM6_INT_RST,
  MCU_OSTM7_INT_RST,
  MCU_OSTM8_INT_RST,
  MCU_OSTM9_INT_RST,
  MCU_AD_PARITY_ERR_RST,
  MCU_TEMP_SENSORERR_RST,
  MCU_CFLH_ERR_ADR_PRTY_ERR_RST,
  MCU_CFLH_ECC2BIT_ERR_RST,
  MCU_CFLH_ECC1BIT_ERR_RST,
  MCU_CFLH_ERR_ADR_OFLOW_RST,
  MCU_DFLH_ECC2BIT_ERR_RST,
  MCU_DFLH_ECC1BIT_ERR_RST,
  MCU_DFLH_ERR_ADR_OFLOW_RST,
  MCU_LRAM_ECC2BIT_ERR_RST,
  MCU_LRAM_ECC1BIT_ERR_RST,
  MCU_LRAM_ERR_ADR_OFLOW_RST,
  MCU_CRAM_ADR_OR_ECC2_ERR_RST,
  MCU_CRAM_ECC1BIT_ERR_RST,
  MCU_CRAM_ERR_ADR_OFLOW_RST,
  MCU_DTSRAM_ECC2BIT_ERR_RST,
  MCU_DTSRAM_ECC1BIT_ERR_RST,
  MCU_DTSRAM_ERR_ADR_OFLOW_RST,
  MCU_SDMAC0_RAM_ECC2BIT_ERR_RST,
  MCU_SDMAC0_RAM_ECC1BIT_ERR_RST,
  MCU_SDMAC1_RAM_ECC2BIT_ERR_RST,
  MCU_SDMAC1_RAM_ECC1BIT_ERR_RST,
  MCU_FRRAM_ECC2BIT_ERR_RST,
  MCU_FRRAM_ECC1BIT_ERR_RST,
  MCU_CANRAM_ECC2BIT_ERR_RST,
  MCU_CANRAM_ECC1BIT_ERR_RST,
  MCU_MSPIRAM_ECC2BIT_ERR_RST,
  MCU_MSPIRAM_ECC1BIT_ERR_RST,
  MCU_GTMRAM_ECC2BIT_ERR_RST,
  MCU_GTMRAM_ECC1BIT_ERR_RST,
  MCU_METHRAM_ECC2BIT_ERR_RST,
  MCU_METHRAM_ECC1BIT_ERR_RST,
  MCU_GETHRAM_ECC2BIT_ERR_RST,
  MCU_GETHRAM_ECC1BIT_ERR_RST,
  MCU_MMCARAM_ECC2BIT_ERR_RST,
  MCU_MMCARAM_ECC1BIT_ERR_RST,
  MCU_PERIRAM_ECC_OFLOW_ERR_RST,
  MCU_ADRBUS_EDC_ECC_ERR_RST,
  MCU_DATABUS_ECC2BIT_ERR_RST,
  MCU_DATABUS_ECC1BIT_ERR_RST,
  MCU_CRAM_GUARD_ERR_RST,
  MCU_IBUS_GUARD_ERR_RST,
  MCU_PBUS_GUARD_ERR_RST,
  MCU_HBUS_GUARD_ERR_RST,
  MCU_DATA_TRANS_DMA_OR_DTS_ERR_RST,
  MCU_DATA_TRANS_HBUS_ERR_RST,
  MCU_EXT_ERRIN0_RST,
  MCU_EXT_ERRIN1_RST,
  MCU_EXT_ERRIN2_RST,
  MCU_EXT_ERRIN3_RST,
  MCU_SW_ALARM0_RST,
  MCU_SW_ALARM1_RST,
  MCU_SW_ALARM2_RST,
  MCU_SW_ALARM3_RST,
  MCU_DCLS_COMP_ERR_PE0_RST,
  MCU_MODE_UNINT_DEBUG_ENABLE_PE0_RST,
  MCU_WDT_ERR_PE0_RST,
  MCU_CLMA_ERR_PE0_RST,
  MCU_LRAM_ADR_OR_ECC2_ERR_PE0_RST,
  MCU_LRAM_ECC1_ERR_PE0_RST,
  MCU_LRAM_ERRADR_OFLOW_PE0_RST,
  MCU_ICACHE_ADR_OR_EDC_ERR_PE0_RST,
  MCU_PEGUARD_ERR_PE0_RST,
  MCU_PEG_OTHER_LRAMREQ_PE0_RST,
  MCU_DATA_ACCESS_ERR_PE0_RST,
  MCU_DCLS_COMP_ERR_PE1_RST,
  MCU_MODE_UNINT_DEBUG_ENABLE_PE1_RST,
  MCU_WDT_ERR_PE1_RST,
  MCU_CLMA_ERR_PE1_RST,
  MCU_LRAM_ADR_OR_ECC2_ERR_PE1_RST,
  MCU_LRAM_ECC1_ERR_PE1_RST,
  MCU_LRAM_ERRADR_OFLOW_PE1_RST,
  MCU_ICACHE_ADR_OR_EDC_ERR_PE1_RST,
  MCU_PEGUARD_ERR_PE1_RST,
  MCU_PEG_OTHER_LRAMREQ_PE1_RST,
  MCU_DATA_ACCESS_ERR_PE1_RST,
  MCU_DCLS_COMP_ERR_PE2_RST,
  MCU_MODE_UNINT_DEBUG_ENABLE_PE2_RST,
  MCU_WDT_ERR_PE2_RST,
  MCU_CLMA_ERR_PE2_RST,
  MCU_LRAM_ADR_OR_ECC2_ERR_PE2_RST,
  MCU_LRAM_ECC1_ERR_PE2_RST,
  MCU_LRAM_ERRADR_OFLOW_PE2_RST,
  MCU_ICACHE_ADR_OR_EDC_ERR_PE2_RST,
  MCU_PEGUARD_ERR_PE2_RST,
  MCU_PEG_OTHER_LRAMREQ_PE2_RST,
  MCU_DATA_ACCESS_ERR_PE2_RST,
  MCU_DCLS_COMP_ERR_PE3_RST,
  MCU_MODE_UNINT_DEBUG_ENABLE_PE3_RST,
  MCU_WDT_ERR_PE3_RST,
  MCU_CLMA_ERR_PE3_RST,
  MCU_LRAM_ADR_OR_ECC2_ERR_PE3_RST,
  MCU_LRAM_ECC1_ERR_PE3_RST,
  MCU_LRAM_ERRADR_OFLOW_PE3_RST,
  MCU_ICACHE_ADR_OR_EDC_ERR_PE3_RST,
  MCU_PEGUARD_ERR_PE3_RST,
  MCU_PEG_OTHER_LRAMREQ_PE3_RST,
  MCU_DATA_ACCESS_ERR_PE3_RST,
  MCU_MULTI_RST,
  MCU_RESET_UNDEFINED,
  MCU_NON_RST,
  MCU_RESERVED_RST
} Mcu_ResetType;
#elif (MCU_DEVICE_NAME == MCU_U2BX)
typedef enum ETag_Mcu_ResetType
{
  MCU_POWER_ON_RESET = 0,
  MCU_STANDBY_RST,
  MCU_EXT_RST,
  MCU_VMON_RST,
  MCU_SW_SYS_RST,
  MCU_ECM_SYS_RST,
  MCU_WDTBA_SYS_RST,
  MCU_SW_APP_RST,
  MCU_ECM_APP_RST,
  MCU_DEEPSTOP_RST,
  MCU_ICUM_SW_SYS_RST,
  MCU_ICUM_SW_APP_RST,
  MCU_ECM_DLY_TIMER_OFLOW_RST,
  MCU_ECM_COMP_ERR_RST,
  MCU_MODE_ERR_0_RST,
  MCU_MODE_ERR_1_RST,
  MCU_MODE_ERR_2_RST,
  MCU_MODE_ERR_3_RST,
  MCU_MODE_ERR_4_RST,
  MCU_MODE_ERR_5_RST,
  MCU_MODE_ERR_6_RST,
  MCU_FLASH_ACCESS_ERR_RST,
  MCU_DTS_COMP_ERR_RST,
  MCU_EMU3S0_RST,
  MCU_EMU3S1_RST,
  MCU_RDC0_ERR_RST,
  MCU_RDC1_ERR_RST,
  MCU_SDMAC0_CHANNEL0_ERR_RST,
  MCU_SDMAC0_CHANNEL1_ERR_RST,
  MCU_SDMAC0_CHANNEL2_ERR_RST,
  MCU_SDMAC0_CHANNEL3_ERR_RST,
  MCU_SDMAC0_CHANNEL4_ERR_RST,
  MCU_SDMAC0_CHANNEL5_ERR_RST,
  MCU_SDMAC0_CHANNEL6_ERR_RST,
  MCU_SDMAC0_CHANNEL7_ERR_RST,
  MCU_SDMAC1_CHANNEL0_ERR_RST,
  MCU_SDMAC1_CHANNEL1_ERR_RST,
  MCU_SDMAC1_CHANNEL2_ERR_RST,
  MCU_SDMAC1_CHANNEL3_ERR_RST,
  MCU_SDMAC1_CHANNEL4_ERR_RST,
  MCU_SDMAC1_CHANNEL5_ERR_RST,
  MCU_SDMAC1_CHANNEL6_ERR_RST,
  MCU_SDMAC1_CHANNEL7_ERR_RST,
  MCU_BUS_BRIDGE_SDMC0_ERR_RST,
  MCU_BUS_BRIDGE_SDMC1_ERR_RST,
  MCU_BUS_BRIDGECOMP_ERROR_RST,
  MCU_GTM_COMPARE_ERR_RST,
  MCU_GTM_ERR_ISR_RST,
  MCU_INTER_PROC_ELEMENT_BUS_RST,
  MCU_INTER_CLUSTER_BUS_RST,
  MCU_PHERIPHERAL_BUS_RST,
  MCU_CRAM_BUS_RST,
  MCU_SYSTEM_BUS_RST,
  MCU_GLOBAL_FLASH_BUS_RST,
  MCU_LOCAL_FLASH_BUS_RST,
  MCU_CLMA_MOSC_ERR_RST,
  MCU_CLMA_HOSC_ERR_RST,
  MCU_CLMA_LOSC_ERR_RST,
  MCU_CLMA_LSB_ERR_RST,
  MCU_CLMA_UHSB_ERR_RST,
  MCU_CLMA_HBUS_EMU_3S0_ERR_RST,
  MCU_CLMA_CLKC_LSB_ERR_RST,
  MCU_CLMA_HBUS_EMU_3S1_ERR_RST,
  MCU_CLMA_SBUS_ERR_RST,
  MCU_OSTM1_INT_RST,
  MCU_OSTM2_INT_RST,
  MCU_OSTM3_INT_RST,
  MCU_OSTM4_INT_RST,
  MCU_OSTM5_INT_RST,
  MCU_DSMIF0_COMP_ERR_RST,
  MCU_DSMIF1_COMP_ERR_RST,
  MCU_TSG30_ERR_ISR_RST,
  MCU_TSG31_ERR_ISR_RST,
  MCU_TSG32_ERR_ISR_RST,
  MCU_SEC_POWER_SUPP_ERR_RST,
  MCU_AD_PARITY_ERR_RST,
  MCU_FAST_COMP_ERR_RST,
  MCU_RESOLVE_CONV_ERR_RST,
  MCU_TEMP_SENSORERR_RST,
  MCU_CFLH_ERR_ADR_PRTY_ERR_RST,
  MCU_CFLH_ECC2BIT_ERR_RST,
  MCU_CFLH_ECC1BIT_ERR_RST,
  MCU_CFLH_ERR_ADR_OFLOW_RST,
  MCU_DFLH_ECC2BIT_ERR_RST,
  MCU_DFLH_ECC1BIT_ERR_RST,
  MCU_DFLH_ERR_ADR_OFLOW_RST,
  MCU_LRAM_ECC2BIT_ERR_RST,
  MCU_LRAM_ECC1BIT_ERR_RST,
  MCU_LRAM_ERR_ADR_OFLOW_RST,
  MCU_CRAM_ADR_OR_ECC2_ERR_RST,
  MCU_CRAM_ECC1BIT_ERR_RST,
  MCU_CRAM_ERR_ADR_OFLOW_RST,
  MCU_DTSRAM_ECC2BIT_ERR_RST,
  MCU_DTSRAM_ECC1BIT_ERR_RST,
  MCU_DTSRAM_ERR_ADR_OFLOW_RST,
  MCU_SDMAC0_RAM_ECC2BIT_ERR_RST,
  MCU_SDMAC0_RAM_ECC1BIT_ERR_RST,
  MCU_SDMAC1_RAM_ECC2BIT_ERR_RST,
  MCU_SDMAC1_RAM_ECC1BIT_ERR_RST,
  MCU_FRRAM_ECC2BIT_ERR_RST,
  MCU_FRRAM_ECC1BIT_ERR_RST,
  MCU_CANRAM_ECC2BIT_ERR_RST,
  MCU_CANRAM_ECC1BIT_ERR_RST,
  MCU_MSPIRAM_ECC2BIT_ERR_RST,
  MCU_MSPIRAM_ECC1BIT_ERR_RST,
  MCU_GTMRAM_ECC2BIT_ERR_RST,
  MCU_GTMRAM_ECC1BIT_ERR_RST,
  MCU_TSN0_ECC_2BIT_ERR_RST,
  MCU_TSN0_ECC_1BIT_ERR_RST,
  MCU_TSN1_ECC_2BIT_ERR_RST,
  MCU_TSN1_ECC_1BIT_ERR_RST,
  MCU_MMCARAM_ECC2BIT_ERR_RST,
  MCU_MMCARAM_ECC1BIT_ERR_RST,
  MCU_DFE0_RAM_ERR_2BIT_RST,
  MCU_DFE0_RAM_ERR_1BIT_RST,
  MCU_RSWITCH_ECC_2BIT_ERR_RST,
  MCU_RSWITCH_ECC_1BIT_ERR_RST,
  MCU_PERIRAM_ECC_OFLOW_ERR_RST,
  MCU_ADRBUS_EDC_ECC_ERR_RST,
  MCU_DATABUS_ECC2BIT_ERR_RST,
  MCU_DATABUS_ECC1BIT_ERR_RST,
  MCU_CRAM_GUARD_ERR_RST,
  MCU_IBUS_GUARD_ERR_RST,
  MCU_PBUS_GUARD_ERR_RST,
  MCU_HBUS_GUARD_ERR_RST,
  MCU_DATA_TRANS_DMA_OR_DTS_ERR_RST,
  MCU_DATA_TRANS_HBUS_ERR_RST,
  MCU_EXT_ERRIN0_RST,
  MCU_EXT_ERRIN1_RST,
  MCU_EXT_ERRIN2_RST,
  MCU_EXT_ERRIN3_RST,
  MCU_EXT_ERRIN4_RST,
  MCU_EXT_ERRIN5_RST,
  MCU_EXT_ERRIN6_RST,
  MCU_EXT_ERRIN7_RST,
  MCU_SW_ALARM0_RST,
  MCU_SW_ALARM1_RST,
  MCU_SW_ALARM2_RST,
  MCU_SW_ALARM3_RST,
  MCU_SW_ALARM4_RST,
  MCU_SW_ALARM5_RST,
  MCU_AES_COMPARE_ERR_RST,
  MCU_ACE0_COMPARE_ERR_RST,
  MCU_ICUMHB_BUS_ROUTING_ERR_RST,
  MCU_BUS_SECURITY_ECC_2BIT_ERR_RST,
  MCU_BUS_SECURITY_ECC_1BIT_ERR_RST,
  MCU_BUS_SECURITY_GUARD_ERR_RST,
  MCU_BUS_SECURITY_DR_TRANS_ERR_RST,
  MCU_DFP_COMPARE_ERR_RST,
  MCU_DFP_HW_CHECKER_ERR_RST,
  MCU_DFP_WDT_TIMER_ERR_RST,
  MCU_DFP_CLMA_ERR_RST,
  MCU_DFP_LRAM_ECC_2BIT_ERR_RST,
  MCU_DFP_LRAM_ECC_1BIT_ERR_RST,
  MCU_DFP_ICACHE_ECC_2BIT_ERR_RST,
  MCU_DFP_ICACHE_ECC_1BIT_ERR_RST,
  MCU_DFP_ERR_OVERFLOW_RST,
  MCU_DFP_BUS_PARITY_ERR_RST,
  MCU_DFP_GUARD_ERR_RST,
  MCU_DFP_MPU_ERR_RST,
  MCU_DFP_ALL_ERR_RST,
  MCU_DCLS_COMP_ERR_PE0_RST,
  MCU_DCLS_MODE_PE0_ERR_RST,
  MCU_MODE_UNINT_DEBUG_ENABLE_PE0_RST,
  MCU_WDT_ERR_PE0_RST,
  MCU_CLMA_ERR_PE0_RST,
  MCU_LRAM_ADR_OR_ECC2_ERR_PE0_RST,
  MCU_LRAM_ECC1_ERR_PE0_RST,
  MCU_LRAM_ERRADR_OFLOW_PE0_RST,
  MCU_ICACHE_ADR_OR_EDC_ERR_PE0_RST,
  MCU_PEGUARD_ERR_PE0_RST,
  MCU_PEG_OTHER_LRAMREQ_PE0_RST,
  MCU_DATA_ACCESS_ERR_PE0_RST,
  MCU_DCLS_COMP_ERR_PE1_RST,
  MCU_DCLS_MODE_PE1_ERR_RST,
  MCU_UNINT_DETECTION_PE1_RST,
  MCU_MODE_UNINT_DEBUG_ENABLE_PE1_RST,
  MCU_WDT_ERR_PE1_RST,
  MCU_CLMA_ERR_PE1_RST,
  MCU_LRAM_ADR_OR_ECC2_ERR_PE1_RST,
  MCU_LRAM_ECC1_ERR_PE1_RST,
  MCU_LRAM_ERRADR_OFLOW_PE1_RST,
  MCU_ICACHE_ADR_OR_EDC_ERR_PE1_RST,
  MCU_PEGUARD_ERR_PE1_RST,
  MCU_PEG_OTHER_LRAMREQ_PE1_RST,
  MCU_DATA_ACCESS_ERR_PE1_RST,
  MCU_DCLS_COMP_ERR_PE2_RST,
  MCU_DCLS_MODE_PE2_ERR_RST,
  MCU_UNINT_DETECTION_PE2_RST,
  MCU_MODE_UNINT_DEBUG_ENABLE_PE2_RST,
  MCU_WDT_ERR_PE2_RST,
  MCU_CLMA_ERR_PE2_RST,
  MCU_LRAM_ADR_OR_ECC2_ERR_PE2_RST,
  MCU_LRAM_ECC1_ERR_PE2_RST,
  MCU_LRAM_ERRADR_OFLOW_PE2_RST,
  MCU_ICACHE_ADR_OR_EDC_ERR_PE2_RST,
  MCU_PEGUARD_ERR_PE2_RST,
  MCU_PEG_OTHER_LRAMREQ_PE2_RST,
  MCU_DATA_ACCESS_ERR_PE2_RST,
  MCU_DCLS_COMP_ERR_PE3_RST,
  MCU_DCLS_MODE_PE3_ERR_RST,
  MCU_UNINT_DETECTION_PE3_RST,
  MCU_MODE_UNINT_DEBUG_ENABLE_PE3_RST,
  MCU_WDT_ERR_PE3_RST,
  MCU_CLMA_ERR_PE3_RST,
  MCU_LRAM_ADR_OR_ECC2_ERR_PE3_RST,
  MCU_LRAM_ECC1_ERR_PE3_RST,
  MCU_LRAM_ERRADR_OFLOW_PE3_RST,
  MCU_ICACHE_ADR_OR_EDC_ERR_PE3_RST,
  MCU_PEGUARD_ERR_PE3_RST,
  MCU_PEG_OTHER_LRAMREQ_PE3_RST,
  MCU_DATA_ACCESS_ERR_PE3_RST,
  MCU_DCLS_COMP_ERR_PE4_RST,
  MCU_DCLS_MODE_PE4_ERR_RST,
  MCU_UNINT_DETECTION_PE4_RST,
  MCU_MODE_UNINT_DEBUG_ENABLE_PE4_RST,
  MCU_WDT_ERR_PE4_RST,
  MCU_CLMA_ERR_PE4_RST,
  MCU_LRAM_ADR_OR_ECC2_ERR_PE4_RST,
  MCU_LRAM_ECC1_ERR_PE4_RST,
  MCU_LRAM_ERRADR_OFLOW_PE4_RST,
  MCU_ICACHE_ADR_OR_EDC_ERR_PE4_RST,
  MCU_PEGUARD_ERR_PE4_RST,
  MCU_PEG_OTHER_LRAMREQ_PE4_RST,
  MCU_DATA_ACCESS_ERR_PE4_RST,
  MCU_UNINT_DETECTION_PE5_RST,
  MCU_MODE_UNINT_DEBUG_ENABLE_PE5_RST,
  MCU_WDT_ERR_PE5_RST,
  MCU_LRAM_ADR_OR_ECC2_ERR_PE5_RST,
  MCU_LRAM_ECC1_ERR_PE5_RST,
  MCU_LRAM_ERRADR_OFLOW_PE5_RST,
  MCU_ICACHE_ADR_OR_EDC_ERR_PE5_RST,
  MCU_PEGUARD_ERR_PE5_RST,
  MCU_PEG_OTHER_LRAMREQ_PE5_RST,
  MCU_DATA_ACCESS_ERR_PE5_RST,
  MCU_MULTI_RST,
  MCU_RESET_UNDEFINED,
  MCU_NON_RST,
  MCU_RESERVED_RST
} Mcu_ResetType;
#elif (MCU_DEVICE_NAME == MCU_U2CX)
typedef enum ETag_Mcu_ResetType
{
  MCU_POWER_ON_RESET = 0,
  MCU_EXT_RST,
  MCU_VMON_RST,
  MCU_SW_SYS_RST,
  MCU_ECM_SYS_RST,
  MCU_WDTBA_SYS_RST,
  MCU_SW_APP_RST,
  MCU_DEEPSTOP_RST,
  MCU_ICUM_SW_SYS_RST,
  MCU_ICUM_SW_APP_RST,
  MCU_ECM_DLY_TIMER_OFLOW_RST,
  MCU_ECM_COMP_ERR_RST,
  MCU_MODE_ERR_0_RST,
  MCU_MODE_ERR_1_RST,
  MCU_MODE_ERR_2_RST,
  MCU_MODE_ERR_3_RST,
  MCU_MODE_ERR_4_RST,
  MCU_MODE_ERR_5_RST,
  MCU_MODE_ERR_6_RST,
  MCU_FLASH_ACCESS_ERR_RST,
  MCU_DTS_COMP_ERR_RST,
  MCU_SDMAC0_CHANNEL0_ERR_RST,
  MCU_SDMAC0_CHANNEL1_ERR_RST,
  MCU_SDMAC0_CHANNEL2_ERR_RST,
  MCU_SDMAC0_CHANNEL3_ERR_RST,
  MCU_SDMAC0_CHANNEL4_ERR_RST,
  MCU_SDMAC0_CHANNEL5_ERR_RST,
  MCU_SDMAC0_CHANNEL6_ERR_RST,
  MCU_SDMAC0_CHANNEL7_ERR_RST,
  MCU_SDMAC1_CHANNEL0_ERR_RST,
  MCU_SDMAC1_CHANNEL1_ERR_RST,
  MCU_SDMAC1_CHANNEL2_ERR_RST,
  MCU_SDMAC1_CHANNEL3_ERR_RST,
  MCU_SDMAC1_CHANNEL4_ERR_RST,
  MCU_SDMAC1_CHANNEL5_ERR_RST,
  MCU_SDMAC1_CHANNEL6_ERR_RST,
  MCU_SDMAC1_CHANNEL7_ERR_RST,
  MCU_BUS_BRIDGE_SDMC0_ERR_RST,
  MCU_BUS_BRIDGE_SDMC1_ERR_RST,
  MCU_BUS_BRIDGECOMP_ERROR_RST,
  MCU_GTM_COMPARE_ERR_RST,
  MCU_GTM_ERR_ISR_RST,
  MCU_INTER_PROC_ELEMENT_BUS_RST,
  MCU_PHERIPHERAL_BUS_RST,
  MCU_SYSTEM_BUS_RST,
  MCU_GLOBAL_FLASH_BUS_RST,
  MCU_LOCAL_FLASH_BUS_RST,
  MCU_CLMA_MOSC_ERR_RST,
  MCU_CLMA_HOSC_ERR_RST,
  MCU_CLMA_LOSC_ERR_RST,
  MCU_CLMA_LSB_ERR_RST,
  MCU_CLMA_UHSB_ERR_RST,
  MCU_CLMA_CLKC_LSB_ERR_RST,
  MCU_CLMA_SBUS_ERR_RST,
  MCU_OSTM1_INT_RST,
  MCU_CANXL0_INT_RST,
  MCU_CANXL1_INT_RST,
  MCU_TSG30_ERR_ISR_RST,
  MCU_TSG31_ERR_ISR_RST,
  MCU_SEC_POWER_SUPP_ERR_RST,
  MCU_AD_PARITY_ERR_RST,
  MCU_TEMP_SENSORERR_RST,
  MCU_CFLH_ERR_ADR_PRTY_ERR_RST,
  MCU_CFLH_ECC2BIT_ERR_RST,
  MCU_CFLH_ECC1BIT_ERR_RST,
  MCU_CFLH_ERR_ADR_OFLOW_RST,
  MCU_DFLH_ECC2BIT_ERR_RST,
  MCU_DFLH_ECC1BIT_ERR_RST,
  MCU_DFLH_ERR_ADR_OFLOW_RST,
  MCU_CRAM_ADR_OR_ECC2_ERR_RST,
  MCU_CRAM_ECC1BIT_ERR_RST,
  MCU_CRAM_ERR_ADR_OFLOW_RST,
  MCU_DTSRAM_ECC2BIT_ERR_RST,
  MCU_DTSRAM_ECC1BIT_ERR_RST,
  MCU_DTSRAM_ERR_ADR_OFLOW_RST,
  MCU_SDMAC0_RAM_ECC2BIT_ERR_RST,
  MCU_SDMAC0_RAM_ECC1BIT_ERR_RST,
  MCU_SDMAC1_RAM_ECC2BIT_ERR_RST,
  MCU_SDMAC1_RAM_ECC1BIT_ERR_RST,
  MCU_FRRAM_ECC2BIT_ERR_RST,
  MCU_FRRAM_ECC1BIT_ERR_RST,
  MCU_CANRAM_ECC2BIT_ERR_RST,
  MCU_CANRAM_ECC1BIT_ERR_RST,
  MCU_MSPIRAM_ECC2BIT_ERR_RST,
  MCU_MSPIRAM_ECC1BIT_ERR_RST,
  MCU_GTMRAM_ECC2BIT_ERR_RST,
  MCU_GTMRAM_ECC1BIT_ERR_RST,
  MCU_TSN0_ECC_2BIT_ERR_RST,
  MCU_TSN0_ECC_1BIT_ERR_RST,
  MCU_TSN1_ECC_2BIT_ERR_RST,
  MCU_TSN1_ECC_1BIT_ERR_RST,
  MCU_MMCARAM_ECC2BIT_ERR_RST,
  MCU_MMCARAM_ECC1BIT_ERR_RST,
  MCU_CANXLRAM_ECC2BIT_ERR_RST,
  MCU_CANXLRAM_ECC1BIT_ERR_RST,
  MCU_RETENRAM_ECC2BIT_ERR_RST,
  MCU_RETENRAM_ECC1BIT_ERR_RST,
  MCU_RETEN_ERR_ADR_OFLOW_ERR_RST,
  MCU_ETNF_ECC2BIT_ERR_RST,
  MCU_ETNF_ECC1BIT_ERR_RST,
  MCU_PERIRAM_ECC_OFLOW_ERR_RST,
  MCU_ADRBUS_EDC_ECC_ERR_RST,
  MCU_DATABUS_ECC2BIT_ERR_RST,
  MCU_DATABUS_ECC1BIT_ERR_RST,
  MCU_CRAM_GUARD_ERR_RST,
  MCU_IBUS_GUARD_ERR_RST,
  MCU_PBUS_GUARD_ERR_RST,
  MCU_HBUS_GUARD_ERR_RST,
  MCU_DATA_TRANS_DMA_OR_DTS_ERR_RST,
  MCU_DATA_TRANS_HBUS_ERR_RST,
  MCU_EXT_ERRIN0_RST,
  MCU_EXT_ERRIN1_RST,
  MCU_EXT_ERRIN2_RST,
  MCU_EXT_ERRIN3_RST,
  MCU_SW_ALARM0_RST,
  MCU_SW_ALARM1_RST,
  MCU_SW_ALARM2_RST,
  MCU_SW_ALARM3_RST,
  MCU_AES_COMPARE_ERR_RST,
  MCU_ACE0_COMPARE_ERR_RST,
  MCU_ICUMHB_BUS_ROUTING_ERR_RST,
  MCU_BUS_SECURITY_ECC_2BIT_ERR_RST,
  MCU_BUS_SECURITY_ECC_1BIT_ERR_RST,
  MCU_BUS_SECURITY_GUARD_ERR_RST,
  MCU_BUS_SECURITY_DR_TRANS_ERR_RST,
  MCU_ICUM_DMAC_RAM_ECC_2BIT_ERR_RST,
  MCU_ICUM_DMAC_RAM_ECC_1BIT_ERR_RST,
  MCU_DCLS_COMP_ERR_PE0_RST,
  MCU_DCLS_MODE_PE0_ERR_RST,
  MCU_MODE_UNINT_DEBUG_ENABLE_PE0_RST,
  MCU_WDT_ERR_PE0_RST,
  MCU_CLMA_ERR_PE0_RST,
  MCU_LRAM_ADR_OR_ECC2_ERR_PE0_RST,
  MCU_LRAM_ECC1_ERR_PE0_RST,
  MCU_LRAM_ERRADR_OFLOW_PE0_RST,
  MCU_ICACHE_ADR_OR_EDC_ERR_PE0_RST,
  MCU_PEGUARD_ERR_PE0_RST,
  MCU_DATA_ACCESS_ERR_PE0_RST,
  MCU_DCLS_COMP_ERR_PE1_RST,
  MCU_DCLS_MODE_PE1_ERR_RST,
  MCU_UNINT_DETECTION_PE1_RST,
  MCU_MODE_UNINT_DEBUG_ENABLE_PE1_RST,
  MCU_WDT_ERR_PE1_RST,
  MCU_CLMA_ERR_PE1_RST,
  MCU_LRAM_ADR_OR_ECC2_ERR_PE1_RST,
  MCU_LRAM_ECC1_ERR_PE1_RST,
  MCU_LRAM_ERRADR_OFLOW_PE1_RST,
  MCU_ICACHE_ADR_OR_EDC_ERR_PE1_RST,
  MCU_PEGUARD_ERR_PE1_RST,
  MCU_DATA_ACCESS_ERR_PE1_RST,
  MCU_MULTI_RST,
  MCU_RESET_UNDEFINED,
  MCU_NON_RST,
  MCU_RESERVED_RST
} Mcu_ResetType;
#elif (MCU_DEVICE_NAME == MCU_U2BXE)
typedef enum ETag_Mcu_ResetType
{
  MCU_POWER_ON_RESET = 0,
  MCU_STANDBY_RST,
  MCU_EXT_RST,
  MCU_VMON_RST,
  MCU_SW_SYS_RST,
  MCU_ECM_SYS_RST,
  MCU_WDTBA_SYS_RST,
  MCU_SW_APP_RST,
  MCU_ECM_APP_RST,
  MCU_DEEPSTOP_RST,
  MCU_ICUM_SW_SYS_RST,
  MCU_ICUM_SW_APP_RST,
  MCU_ECM_DLY_TIMER_OFLOW_RST,
  MCU_ECM_COMP_ERR_RST,
  MCU_MODE_ERR_0_RST,
  MCU_MODE_ERR_1_RST,
  MCU_MODE_ERR_2_RST,
  MCU_MODE_ERR_3_RST,
  MCU_MODE_ERR_4_RST,
  MCU_MODE_ERR_5_RST,
  MCU_MODE_ERR_6_RST,
  MCU_FLASH_ACCESS_ERR_RST,
  MCU_DTS_COMP_ERR_RST,
  MCU_RDC0_ERR_RST,
  MCU_RDC1_ERR_RST,
  MCU_SDMAC0_CHANNEL0_ERR_RST,
  MCU_SDMAC0_CHANNEL1_ERR_RST,
  MCU_SDMAC0_CHANNEL2_ERR_RST,
  MCU_SDMAC0_CHANNEL3_ERR_RST,
  MCU_SDMAC0_CHANNEL4_ERR_RST,
  MCU_SDMAC0_CHANNEL5_ERR_RST,
  MCU_SDMAC0_CHANNEL6_ERR_RST,
  MCU_SDMAC0_CHANNEL7_ERR_RST,
  MCU_SDMAC1_CHANNEL0_ERR_RST,
  MCU_SDMAC1_CHANNEL1_ERR_RST,
  MCU_SDMAC1_CHANNEL2_ERR_RST,
  MCU_SDMAC1_CHANNEL3_ERR_RST,
  MCU_SDMAC1_CHANNEL4_ERR_RST,
  MCU_SDMAC1_CHANNEL5_ERR_RST,
  MCU_SDMAC1_CHANNEL6_ERR_RST,
  MCU_SDMAC1_CHANNEL7_ERR_RST,
  MCU_BUS_BRIDGE_SDMC0_ERR_RST,
  MCU_BUS_BRIDGE_SDMC1_ERR_RST,
  MCU_BUS_BRIDGECOMP_ERROR_RST,
  MCU_GTM_COMPARE_ERR_RST,
  MCU_GTM_ERR_ISR_RST,
  MCU_INTER_PROC_ELEMENT_BUS_RST,
  MCU_INTER_CLUSTER_BUS_RST,
  MCU_PHERIPHERAL_BUS_RST,
  MCU_CRAM_BUS_RST,
  MCU_SYSTEM_BUS_RST,
  MCU_GLOBAL_FLASH_BUS_RST,
  MCU_LOCAL_FLASH_BUS_RST,
  MCU_CLMA_MOSC_ERR_RST,
  MCU_CLMA_HOSC_ERR_RST,
  MCU_CLMA_LOSC_ERR_RST,
  MCU_CLMA_LSB_ERR_RST,
  MCU_CLMA_UHSB_ERR_RST,
  MCU_CLMA_CLKC_LSB_ERR_RST,
  MCU_CLMA_SBUS_ERR_RST,
  MCU_OSTM1_INT_RST,
  MCU_OSTM2_INT_RST,
  MCU_OSTM3_INT_RST,
  MCU_OSTM4_INT_RST,
  MCU_OSTM5_INT_RST,
  MCU_OSTM6_INT_RST,
  MCU_OSPI_ERR_ISR_RST,
  MCU_CANXL0_INT_RST,
  MCU_CANXL1_INT_RST,
  MCU_DSMIF0_COMP_ERR_RST,
  MCU_DSMIF1_COMP_ERR_RST,
  MCU_TSG30_ERR_ISR_RST,
  MCU_TSG31_ERR_ISR_RST,
  MCU_TSG32_ERR_ISR_RST,
  MCU_SEC_POWER_SUPP_ERR_RST,
  MCU_AD_PARITY_ERR_RST,
  MCU_FAST_COMP_ERR_RST,
  MCU_RESOLVE_CONV_ERR_RST,
  MCU_TEMP_SENSORERR_RST,
  MCU_CFLH_ERR_ADR_PRTY_ERR_RST,
  MCU_CFLH_ECC2BIT_ERR_RST,
  MCU_CFLH_ECC1BIT_ERR_RST,
  MCU_CFLH_ERR_ADR_OFLOW_RST,
  MCU_DFLH_ECC2BIT_ERR_RST,
  MCU_DFLH_ECC1BIT_ERR_RST,
  MCU_DFLH_ERR_ADR_OFLOW_RST,
  MCU_LRAM_ECC2BIT_ERR_RST,
  MCU_LRAM_ECC1BIT_ERR_RST,
  MCU_LRAM_ERR_ADR_OFLOW_RST,
  MCU_CRAM_ADR_OR_ECC2_ERR_RST,
  MCU_CRAM_ECC1BIT_ERR_RST,
  MCU_CRAM_ERR_ADR_OFLOW_RST,
  MCU_DTSRAM_ECC2BIT_ERR_RST,
  MCU_DTSRAM_ECC1BIT_ERR_RST,
  MCU_DTSRAM_ERR_ADR_OFLOW_RST,
  MCU_SDMAC0_RAM_ECC2BIT_ERR_RST,
  MCU_SDMAC0_RAM_ECC1BIT_ERR_RST,
  MCU_SDMAC1_RAM_ECC2BIT_ERR_RST,
  MCU_SDMAC1_RAM_ECC1BIT_ERR_RST,
  MCU_EX_CRAM_ECC2BIT_ERR_RST,
  MCU_EX_CRAM_ECC1BIT_ERR_RST,
  MCU_EXCRAM_ERR_ADR_OFLOW_RST,
  MCU_FRRAM_ECC2BIT_ERR_RST,
  MCU_FRRAM_ECC1BIT_ERR_RST,
  MCU_CANRAM_ECC2BIT_ERR_RST,
  MCU_CANRAM_ECC1BIT_ERR_RST,
  MCU_MSPIRAM_ECC2BIT_ERR_RST,
  MCU_MSPIRAM_ECC1BIT_ERR_RST,
  MCU_GTMRAM_ECC2BIT_ERR_RST,
  MCU_GTMRAM_ECC1BIT_ERR_RST,
  MCU_MMCARAM_ECC2BIT_ERR_RST,
  MCU_MMCARAM_ECC1BIT_ERR_RST,
  MCU_DFE0_RAM_ERR_2BIT_RST,
  MCU_DFE0_RAM_ERR_1BIT_RST,
  MCU_RSWITCH_ECC_2BIT_ERR_RST,
  MCU_RSWITCH_ECC_1BIT_ERR_RST,
  MCU_CANXL_RAM_ECC2BIT_ERR_RST,
  MCU_CANXL_RAM_ECC1BIT_ERR_RST,
  MCU_ETNF_FIFO_ECC2BIT_ERR_RST,
  MCU_ETNF_FIFO_ECC1BIT_ERR_RST,
  MCU_OSPI_ECC2BIT_ERR_RST,
  MCU_OSPI_ECC1BIT_ERR_RST,
  MCU_PERIRAM_ECC_OFLOW_ERR_RST,
  MCU_ADRBUS_EDC_ECC_ERR_RST,
  MCU_DATABUS_ECC2BIT_ERR_RST,
  MCU_DATABUS_ECC1BIT_ERR_RST,
  MCU_EXCRAM_GUARD_ERR_RST,
  MCU_CRAM_GUARD_ERR_RST,
  MCU_IBUS_GUARD_ERR_RST,
  MCU_PBUS_GUARD_ERR_RST,
  MCU_HBUS_GUARD_ERR_RST,
  MCU_ICUM_DMAC_RAM_ECC2BIT_ERR_RST,
  MCU_ICUM_DMAC_RAM_ECC1BIT_ERR_RST,
  MCU_DATA_TRANS_DMA_OR_DTS_ERR_RST,
  MCU_DATA_TRANS_HBUS_ERR_RST,
  MCU_EXT_ERRIN0_RST,
  MCU_EXT_ERRIN1_RST,
  MCU_EXT_ERRIN2_RST,
  MCU_EXT_ERRIN3_RST,
  MCU_EXT_ERRIN4_RST,
  MCU_EXT_ERRIN5_RST,
  MCU_EXT_ERRIN6_RST,
  MCU_EXT_ERRIN7_RST,
  MCU_SW_ALARM0_RST,
  MCU_SW_ALARM1_RST,
  MCU_SW_ALARM2_RST,
  MCU_SW_ALARM3_RST,
  MCU_SW_ALARM4_RST,
  MCU_SW_ALARM5_RST,
  MCU_SW_ALARM6_RST,
  MCU_ICUMHB_COMP_ERR_RST,
  MCU_ACE0_COMPARE_ERR_RST,
  MCU_ACE1_COMPARE_ERR_RST,
  MCU_ICUMHB_BUS_ROUTING_ERR_RST,
  MCU_BUS_SECURITY_ECC_2BIT_ERR_RST,
  MCU_BUS_SECURITY_ECC_1BIT_ERR_RST,
  MCU_BUS_SECURITY_GUARD_ERR_RST,
  MCU_BUS_SECURITY_DR_TRANS_ERR_RST,
  MCU_ACE2_COMPARE_ERR_RST,
  MCU_ACE3_COMPARE_ERR_RST,
  MCU_DFA_CRITICAL_ERR_RST,
  MCU_DFA_NON_CRITICAL_ERR_RST,
  MCU_CLMA_DFA_ERR_RST,
  MCU_LRAM_DFA_ECC2_ERR_PE0_RST,
  MCU_LRAM_DFA_ECC1_ERR_PE0_RST,
  MCU_DFA_ECC_ERR_OFLOW_ERR_RST,
  MCU_DFA_PARITY_ERR_RST,
  MCU_DFA_GUARD_ERR_RST,
  MCU_DCLS_COMP_ERR_PE0_RST,
  MCU_DCLS_MODE_PE0_ERR_RST,
  MCU_MODE_UNINT_DEBUG_ENABLE_PE0_RST,
  MCU_WDT_ERR_PE0_RST,
  MCU_CLMA_ERR_PE0_RST,
  MCU_LRAM_ADR_OR_ECC2_ERR_PE0_RST,
  MCU_LRAM_ECC1_ERR_PE0_RST,
  MCU_LRAM_ERRADR_OFLOW_PE0_RST,
  MCU_ICACHE_ADR_OR_EDC_ERR_PE0_RST,
  MCU_PEGUARD_ERR_PE0_RST,
  MCU_PEG_OTHER_LRAMREQ_PE0_RST,
  MCU_DATA_ACCESS_ERR_PE0_RST,
  MCU_DCLS_COMP_ERR_PE1_RST,
  MCU_DCLS_MODE_PE1_ERR_RST,
  MCU_UNINT_DETECTION_PE1_RST,
  MCU_MODE_UNINT_DEBUG_ENABLE_PE1_RST,
  MCU_WDT_ERR_PE1_RST,
  MCU_CLMA_ERR_PE1_RST,
  MCU_LRAM_ADR_OR_ECC2_ERR_PE1_RST,
  MCU_LRAM_ECC1_ERR_PE1_RST,
  MCU_LRAM_ERRADR_OFLOW_PE1_RST,
  MCU_ICACHE_ADR_OR_EDC_ERR_PE1_RST,
  MCU_PEGUARD_ERR_PE1_RST,
  MCU_PEG_OTHER_LRAMREQ_PE1_RST,
  MCU_DATA_ACCESS_ERR_PE1_RST,
  MCU_DCLS_COMP_ERR_PE2_RST,
  MCU_DCLS_MODE_PE2_ERR_RST,
  MCU_UNINT_DETECTION_PE2_RST,
  MCU_MODE_UNINT_DEBUG_ENABLE_PE2_RST,
  MCU_WDT_ERR_PE2_RST,
  MCU_CLMA_ERR_PE2_RST,
  MCU_LRAM_ADR_OR_ECC2_ERR_PE2_RST,
  MCU_LRAM_ECC1_ERR_PE2_RST,
  MCU_LRAM_ERRADR_OFLOW_PE2_RST,
  MCU_ICACHE_ADR_OR_EDC_ERR_PE2_RST,
  MCU_PEGUARD_ERR_PE2_RST,
  MCU_PEG_OTHER_LRAMREQ_PE2_RST,
  MCU_DATA_ACCESS_ERR_PE2_RST,
  MCU_DCLS_COMP_ERR_PE3_RST,
  MCU_DCLS_MODE_PE3_ERR_RST,
  MCU_UNINT_DETECTION_PE3_RST,
  MCU_MODE_UNINT_DEBUG_ENABLE_PE3_RST,
  MCU_WDT_ERR_PE3_RST,
  MCU_CLMA_ERR_PE3_RST,
  MCU_LRAM_ADR_OR_ECC2_ERR_PE3_RST,
  MCU_LRAM_ECC1_ERR_PE3_RST,
  MCU_LRAM_ERRADR_OFLOW_PE3_RST,
  MCU_ICACHE_ADR_OR_EDC_ERR_PE3_RST,
  MCU_PEGUARD_ERR_PE3_RST,
  MCU_PEG_OTHER_LRAMREQ_PE3_RST,
  MCU_DATA_ACCESS_ERR_PE3_RST,
  MCU_DCLS_COMP_ERR_PE4_RST,
  MCU_DCLS_MODE_PE4_ERR_RST,
  MCU_UNINT_DETECTION_PE4_RST,
  MCU_MODE_UNINT_DEBUG_ENABLE_PE4_RST,
  MCU_WDT_ERR_PE4_RST,
  MCU_CLMA_ERR_PE4_RST,
  MCU_LRAM_ADR_OR_ECC2_ERR_PE4_RST,
  MCU_LRAM_ECC1_ERR_PE4_RST,
  MCU_LRAM_ERRADR_OFLOW_PE4_RST,
  MCU_ICACHE_ADR_OR_EDC_ERR_PE4_RST,
  MCU_PEGUARD_ERR_PE4_RST,
  MCU_PEG_OTHER_LRAMREQ_PE4_RST,
  MCU_DATA_ACCESS_ERR_PE4_RST,
  MCU_UNINT_DETECTION_PE5_RST,
  MCU_MODE_UNINT_DEBUG_ENABLE_PE5_RST,
  MCU_WDT_ERR_PE5_RST,
  MCU_LRAM_ADR_OR_ECC2_ERR_PE5_RST,
  MCU_LRAM_ECC1_ERR_PE5_RST,
  MCU_LRAM_ERRADR_OFLOW_PE5_RST,
  MCU_ICACHE_ADR_OR_EDC_ERR_PE5_RST,
  MCU_PEGUARD_ERR_PE5_RST,
  MCU_PEG_OTHER_LRAMREQ_PE5_RST,
  MCU_DATA_ACCESS_ERR_PE5_RST,
  MCU_DCLS_COMP_ERR_PE6_RST,
  MCU_DCLS_MODE_PE6_ERR_RST,
  MCU_UNINT_DETECTION_PE6_RST,
  MCU_MODE_UNINT_DEBUG_ENABLE_PE6_RST,
  MCU_WDT_ERR_PE6_RST,
  MCU_CLMA_ERR_PE6_RST,
  MCU_LRAM_ADR_OR_ECC2_ERR_PE6_RST,
  MCU_LRAM_ECC1_ERR_PE6_RST,
  MCU_LRAM_ERRADR_OFLOW_PE6_RST,
  MCU_ICACHE_ADR_OR_EDC_ERR_PE6_RST,
  MCU_PEGUARD_ERR_PE6_RST,
  MCU_DATA_ACCESS_ERR_PE6_RST,
  MCU_MULTI_RST,
  MCU_RESET_UNDEFINED,
  MCU_NON_RST,
  MCU_RESERVED_RST
} Mcu_ResetType;
#endif

#if (MCU_GET_RAM_STATE_API == STD_ON)
/* Status value returned by the API Mcu_GetRamState */
typedef enum ETag_Mcu_RamStateType
{
  MCU_RAMSTATE_INVALID = 0,
  MCU_RAMSTATE_VALID
} Mcu_RamStateType;
#endif

typedef enum ETag_Mcu_ClkModeType
{
  MCU_CLOCK_MODE = 0,
  MCU_STANDBY_MODE
} Mcu_ClkModeType;

typedef enum ETag_Mcu_ClkShiftType
{
  MCU_CLK_GEAR_UP = 0,
  MCU_CLK_GEAR_DOWN
} Mcu_ClkShiftType;

typedef enum ETag_Mcu_ClockModuleType
{
  MCU_CLK_SEL = 0,
  MCU_CLKA_ADC,
  MCU_CLK_EXTCLKO
} Mcu_ClockModuleType;

/* Type of MCU mode that supported by hardware */
typedef enum ETag_Mcu_StandbyModeType
{
  MCU_RUN_MODE = 0,
  MCU_HALT_MODE,
  MCU_STOP_MODE,
  MCU_CYCLICSTOP_MODE,
  MCU_CYCLICRUN_MODE,
  MCU_DEEPSTOP_MODE,
  MCU_POWEROF_STANDBY_MODE
} Mcu_StandbyModeType;

/***********************************************************************************************************************
**                                              WakeUp Factor Structure                                               **
***********************************************************************************************************************/
#if (MCU_GETWAKEUPFACTOR_API == STD_ON)
typedef struct STag_Mcu_WakeUpFactorInfoType                                                                            /* PRQA S 3630 # JV-01 */
{
  uint32 ulWufMonValue;
  uint32 aaWufDetail[MCU_NUMBER_WAKEUP_FACTOR];
} Mcu_WakeUpFactorInfoType;
#endif

#endif /* MCU_TYPES_H */
/***********************************************************************************************************************
**                                                    End Of File                                                     **
***********************************************************************************************************************/
