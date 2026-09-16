/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Mcu_Cfg.h                                                                                           */
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
/* TOOL VERSION:  McuU2Bx-E.dll version: 2.4.1, MCALConfGen.exe version: 2.3.0                                        */
/*                                                                                                                    */


/***********************************************************************************************************************
**                      Input File                                                                                    **
***********************************************************************************************************************/
/*
 * INPUT FILE:    C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\MCAL_RH850U2B24E_516_CodeGen\U2B24-E.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\modules\mcu\generator\U2B24-E\R2211_mcu_U2B24-E_BSWMDT.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\Dem\xml\Dem_mcu.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\EcuC\xml\EcuC_mcu.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\MCAL_RH850U2B24E_516_CodeGen\Translation.trxml
 * GENERATED ON:  13 Jul 2026 - 15:38:52
 */


#ifndef MCU_CFG_H
#define MCU_CFG_H


/***********************************************************************************************************************
**                      Include Section                                                                               **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                      Coding Rule Violations                                                                        **
***********************************************************************************************************************/

/**********************************************************************************************************************/
/* Message (1:1534)    : The macro '%1s' is declared but not used within this project.                                */
/* Rule                : MISRA C:2012 Rule-2.5                                                                        */
/* JV-01 Justification : These macros are used for version checking in precompile or in user application.             */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/


/***********************************************************************************************************************
**                      Version Information                                                                           **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define MCU_CFG_AR_RELEASE_MAJOR_VERSION                                        4U                                      /* PRQA S 1534 # JV-01 */
#define MCU_CFG_AR_RELEASE_MINOR_VERSION                                        8U                                      /* PRQA S 1534 # JV-01 */
#define MCU_CFG_AR_RELEASE_REVISION_VERSION                                     0U                                      /* PRQA S 1534 # JV-01 */

/* File version information */
#define MCU_CFG_SW_MAJOR_VERSION                                                2U                                      /* PRQA S 1534 # JV-01 */
#define MCU_CFG_SW_MINOR_VERSION                                                5U                                      /* PRQA S 1534 # JV-01 */
#define MCU_AR_VERSION                                                          MCU_AR_R22_11_VERSION

/***********************************************************************************************************************
**                      Common Published Information                                                                  **
***********************************************************************************************************************/
#define MCU_AR_RELEASE_MAJOR_VERSION_VALUE                                      4U                                      /* PRQA S 1534 # JV-01 */
#define MCU_AR_RELEASE_MINOR_VERSION_VALUE                                      8U                                      /* PRQA S 1534 # JV-01 */
#define MCU_AR_RELEASE_REVISION_VERSION_VALUE                                   0U                                      /* PRQA S 1534 # JV-01 */

#define MCU_SW_MAJOR_VERSION_VALUE                                              2U                                      /* PRQA S 1534 # JV-01 */
#define MCU_SW_MINOR_VERSION_VALUE                                              5U                                      /* PRQA S 1534 # JV-01 */
#define MCU_SW_PATCH_VERSION_VALUE                                              1U                                      /* PRQA S 1534 # JV-01 */

#define MCU_VENDOR_ID_VALUE                                                     59U                                     /* PRQA S 1534 # JV-01 */
#define MCU_MODULE_ID_VALUE                                                     101U                                    /* PRQA S 1534 # JV-01 */

/***********************************************************************************************************************
**                      Global Symbols                                                                                **
***********************************************************************************************************************/


#define MCU_DEVICE_NAME                                                         MCU_U2BXE                               /* PRQA S 1534 # JV-01 */

/* Instance ID of the MCU Driver */
#define MCU_INSTANCE_ID_VALUE                                                   0U                                      /* PRQA S 1534 # JV-01 */

/* Pre-compile option for Mcu_GetVersion API */
#define MCU_VERSION_INFO_API                                                    STD_ON                                  /* PRQA S 1534 # JV-01 */

/* Pre-compile option for Mcu_PerformReset API */
#define MCU_PERFORM_RESET_API                                                   STD_ON                                  /* PRQA S 1534 # JV-01 */

/* Pre-compile option for Mcu_GetRamState API */
#define MCU_GET_RAM_STATE_API                                                   STD_ON                                  /* PRQA S 1534 # JV-01 */

/* Pre-compile option for Mcu_InitClock API */
#define MCU_INIT_CLOCK                                                          STD_ON                                  /* PRQA S 1534 # JV-01 */

/* Pre-compile option for availability of PLL */
#define MCU_NO_PLL                                                              STD_OFF                                 /* PRQA S 1534 # JV-01 */

/* Pre-compile option for MCU_RESET_CALLOUT API */
#define MCU_SW_RESET_CALL_API                                                   STD_ON                                  /* PRQA S 1534 # JV-01 */

/* Pre-compile option for the development error detection and Reporting */
#define MCU_DEV_ERROR_DETECT                                                    STD_OFF                                 /* PRQA S 1534 # JV-01 */

/* Pre-compile option for enable or disable inter-module dependencies */
#define MCU_VERSION_CHECK_EXT_MODULES                                           STD_ON                                  /* PRQA S 1534 # JV-01 */

/* Pre-compile option for the critical section functionality */
#define MCU_CRITICAL_SECTION_PROTECTION                                         STD_ON                                  /* PRQA S 1534 # JV-01 */

/* Pre-compile option for availability of CLMA group */
#define MCU_CLMA_OPERATION                                                      STD_OFF                                 /* PRQA S 1534 # JV-01 */

/* Pre-compile option for provide ram state ISR */
#define MCU_PROVIDE_RAM_STATE_ISR                                               STD_ON                                  /* PRQA S 1534 # JV-01 */

/* Pre-compile option for MCU_FEINT_ISR API */
#define MCU_FEINT_ISR_API                                                       STD_OFF                                 /* PRQA S 1534 # JV-01 */

/* Pre-compile option for MCU_EIINT_EIC8_ISR_API API */
#define MCU_EIINT_EIC8_ISR_API                                                  STD_OFF                                 /* PRQA S 1534 # JV-01 */

/* Pre-compile option for MCU_EIINT_EIC9_ISR_API API */
#define MCU_EIINT_EIC9_ISR_API                                                  STD_OFF                                 /* PRQA S 1534 # JV-01 */

/* Pre-compile option for availability of ECM */
#define MCU_ECM_OPERATION                                                       STD_ON                                  /* PRQA S 1534 # JV-01 */

/* Pre-compile option for availability of GTM */
#define MCU_GTM_SETTING                                                         STD_ON                                  /* PRQA S 1534 # JV-01 */

/* Pre-compile option for availability of software reset trigger */
#define MCU_SWRESET_APPLICATION_RESET                                           STD_ON                                  /* PRQA S 1534 # JV-01 */

/* Pre-compile option for availability of ECM reset trigger */
#define MCU_ECMRESET_APPLICATION_RESET                                          STD_ON                                  /* PRQA S 1534 # JV-01 */

/* Pre-compile option for MCU_VMON_DIAG_OPERATION */
#define MCU_VMON_DIAG_OPERATION                                                 STD_OFF                                 /* PRQA S 1534 # JV-01 */

/* Pre-compile option for MCU_DMON_DIAG_OPERATION */
#define MCU_DMON_DIAG_OPERATION                                                 STD_OFF                                 /* PRQA S 1534 # JV-01 */

/* Pre-compile option for MCU_DMON_DIAG_FILTER_OPERATION */
#define MCU_DMON_DIAG_FILTER_OPERATION                                          STD_OFF                                 /* PRQA S 1534 # JV-01 */

/* Pre-compile option for MCU_ECM_ERROROUTC_CLEAR_VERIFY */
#define MCU_ECM_ERROROUTC_CLEAR_VERIFY                                          STD_ON                                  /* PRQA S 1534 # JV-01 */

/* Pre-compile option for MCU_ECM_INTERRUPT_CONSISTENCY_CHECK */
#define MCU_ECM_INTERRUPT_CONSISTENCY_CHECK                                     STD_OFF                                 /* PRQA S 1534 # JV-01 */

/* Pre-compile option for MCU_ISR_CATEGORY_2 */
#define MCU_ISR_CATEGORY_2                                                      STD_OFF                                 /* PRQA S 1534 # JV-01 */

/* Pre-compile option for MCU_RAM_ECCECM_SETTING_INITRAMSECTION */
#define MCU_RAM_ECCECM_SETTING_INITRAMSECTION                                   STD_ON                                  /* PRQA S 1534 # JV-01 */

/* Pre-compile option for MCU_RETENTION_RAM_SETTING */
#define MCU_RETENTION_RAM_SETTING                                               STD_OFF                                 /* PRQA S 1534 # JV-01 */

/* Pre-compile option for MCU_SOSC_SUPPORT */
#define MCU_SOSC_SUPPORT                                                        STD_OFF                                 /* PRQA S 1534 # JV-01 */

/* Pre-compile option for MCU_SSCG_ENABLE */
#define MCU_SSCG_ENABLE                                                         STD_ON                                  /* PRQA S 1534 # JV-01 */

/* Pre-compile option for MCU_SSCG1_ENABLE */
#define MCU_SSCG1_ENABLE                                                        STD_ON                                  /* PRQA S 1534 # JV-01 */

/* Pre-compile option for MCU_CLOCK_TRIMMING_SUPPORT */
#define MCU_CLOCK_TRIMMING_SUPPORT                                              STD_ON                                  /* PRQA S 1534 # JV-01 */

/* Pre-compile option for MCU_STANDBY_RST_ENABLE */
#define MCU_STANDBY_RST_ENABLE                                                  STD_ON                                  /* PRQA S 1534 # JV-01 */

/* Pre-compile option for MCU_TOTAL_PE_NUM */
#define MCU_TOTAL_PE_NUM                                                        7                                       /* PRQA S 1534 # JV-01 */

/* Pre-compile option for MCU_CLEARANDSETWAKEUPFACTOR_API */
#define MCU_CLEARANDSETWAKEUPFACTOR_API                                         STD_ON                                  /* PRQA S 1534 # JV-01 */

/* Pre-compile option for MCU_GETWAKEUPFACTOR_API */
#define MCU_GETWAKEUPFACTOR_API                                                 STD_ON                                  /* PRQA S 1534 # JV-01 */

/* Pre-compile option for MCU_RELEASEIOBUFFERHOLD_API */
#define MCU_RELEASEIOBUFFERHOLD_API                                             STD_ON                                  /* PRQA S 1534 # JV-01 */

/* Pre-compile option for MCU_MODE_TRANSITION_SUPPORT */
#define MCU_MODE_TRANSITION_SUPPORT                                             STD_ON                                  /* PRQA S 1534 # JV-01 */

/* Pre-compile option to generate number of wakeup factor */
#define MCU_NUMBER_WAKEUP_FACTOR                                                (uint8)0x0BU                            /* PRQA S 1534 # JV-01 */

/* Pre-compile option for MCU_CLMA_BACKUP_CLOCK_ENABLE_SUPPORT */
#define MCU_CLMA_BACKUP_CLOCK_ENABLE_SUPPORT                                    STD_ON                                  /* PRQA S 1534 # JV-01 */

/* Pre-compile option for MCU_POWER_SUPPLY_MODE_SELECTION */
#define MCU_POWER_SUPPLY_MODE_SELECTION                                         STD_OFF                                 /* PRQA S 1534 # JV-01 */

/* Pre-compile option for MCU_SHUT_DOWN_SELECTION */
#define MCU_SHUT_DOWN_SELECTION                                                 STD_OFF                                 /* PRQA S 1534 # JV-01 */

/* Pre-compile option for MCU_CLK_SRC_NUM */
#define MCU_CLK_SRC_NUM                                                         (uint8)0x03U                            /* PRQA S 1534 # JV-01 */

/* Pre-compile option for MCU_POWER_GOOD_COUNTER_VALUE */
#define MCU_POWER_GOOD_COUNTER_VALUE                                            (uint32)0x0000027AUL

/***********************************************************************************************************************
**                      Global Data Types                                                                             **
***********************************************************************************************************************/


#define McuRamSectorSettingConf_McuRamSectorSettingConf                         (Mcu_RamSectionType)0                   /* PRQA S 1534 # JV-01 */

/* The RAM Sector Setting Configuration Handles */
#define McuRamSectorSettingConf_McuRamSectorSettingConf_001                     (Mcu_RamSectionType)1                   /* PRQA S 1534 # JV-01 */

/* The RAM Sector Setting Configuration Handles */
#define McuRamSectorSettingConf_McuRamSectorSettingConf_002                     (Mcu_RamSectionType)2                   /* PRQA S 1534 # JV-01 */

/* The RAM Sector Setting Configuration Handles */
#define McuRamSectorSettingConf_McuRamSectorSettingConf_003                     (Mcu_RamSectionType)3                   /* PRQA S 1534 # JV-01 */

/* The RAM Sector Setting Configuration Handles */
#define McuRamSectorSettingConf_McuRamSectorSettingConf_004                     (Mcu_RamSectionType)4                   /* PRQA S 1534 # JV-01 */

/* The RAM Sector Setting Configuration Handles */
#define McuRamSectorSettingConf_McuRamSectorSettingConf_005                     (Mcu_RamSectionType)5                   /* PRQA S 1534 # JV-01 */

/* The RAM Sector Setting Configuration Handles */
#define McuRamSectorSettingConf_McuRamSectorSettingConf_006                     (Mcu_RamSectionType)6                   /* PRQA S 1534 # JV-01 */

/* The RAM Sector Setting Configuration Handles */
#define McuRamSectorSettingConf_McuRamSectorSettingConf_007                     (Mcu_RamSectionType)7                   /* PRQA S 1534 # JV-01 */

/* The RAM Sector Setting Configuration Handles */
#define McuRamSectorSettingConf_McuRamSectorSettingConf_008                     (Mcu_RamSectionType)8                   /* PRQA S 1534 # JV-01 */

/* The Configuration Set Handles */
#define Mcu_Config                                                              (&Mcu_GaaConfiguration[0])              /* PRQA S 1534 # JV-01 */

/* The Clock Setting Configuration Handles */
#define McuConf_McuClockSettingConfig_McuClockSettingConfig                     (Mcu_ClockType)0                        /* PRQA S 1534 # JV-01 */

/* The Mode Setting Configuration Handles */
#define McuConf_McuModeSettingConf_McuModeSettingConf                           (Mcu_ModeType)0                         /* PRQA S 1534 # JV-01 */

/* The Mode Setting Configuration Handles */
#define McuConf_McuModeSettingConf_McuModeSettingConf_001                       (Mcu_ModeType)1                         /* PRQA S 1534 # JV-01 */

/* The Mode Setting Configuration Handles */
#define McuConf_McuModeSettingConf_McuModeSettingConf_002                       (Mcu_ModeType)2                         /* PRQA S 1534 # JV-01 */

/* The Power On reset Reset Reason Handles */
#define McuConf_McuRstRsnConfPowerOnReset_McuRstRsnConfPowerOnReset             (Mcu_ResetType)0x00U                    /* PRQA S 1534 # JV-01 */

/* The Stand by Reset Reset Reason Handles */
#define McuConf_McuRstRsnConfStandbyRst_McuRstRsnConfStandbyRst                 (Mcu_ResetType)0x01U                    /* PRQA S 1534 # JV-01 */

/* The External System reset 1 Reset Reason Handles */
#define McuConf_McuRstRsnConfExtRst_McuRstRsnConfExtRst                         (Mcu_ResetType)0x02U                    /* PRQA S 1534 # JV-01 */

/* The VMON System reset 1 Reset Reason Handles */
#define McuConf_McuRstRsnConfVmonRst_McuRstRsnConfVmonRst                       (Mcu_ResetType)0x03U                    /* PRQA S 1534 # JV-01 */

/* The Software System reset 2 Reset Reason Handles */
#define McuConf_McuRstRsnConfSwSysRst_McuRstRsnConfSwSysRst                     (Mcu_ResetType)0x04U                    /* PRQA S 1534 # JV-01 */

/* The ECM System reset 2 Reset Reason Handles */
#define McuConf_McuRstRsnConfEcmSysRst_McuRstRsnConfEcmSysRst                   (Mcu_ResetType)0x05U                    /* PRQA S 1534 # JV-01 */

/* The WDTBA System reset 2 Reset Reason Handles */
#define McuConf_McuRstRsnConfWdtbaSysRst_McuRstRsnConfWdtbaSysRst               (Mcu_ResetType)0x06U                    /* PRQA S 1534 # JV-01 */

/* The Software Application reset Reset Reason Handles */
#define McuConf_McuRstRsnConfSwAppRst_McuRstRsnConfSwAppRst                     (Mcu_ResetType)0x07U                    /* PRQA S 1534 # JV-01 */

/* The ECM Application reset Reset Reason Handles */
#define McuConf_McuRstRsnConfEcmAppRst_McuRstRsnConfEcmAppRst                   (Mcu_ResetType)0x08U                    /* PRQA S 1534 # JV-01 */

/* The DeepSTOP reset Reset Reason Handles */
#define McuConf_McuRstRsnConfDeepstopRst_McuRstRsnConfDeepstopRst               (Mcu_ResetType)0x09U                    /* PRQA S 1534 # JV-01 */

/* The ICUM System reset 2 Reset Reason Handles */
#define McuConf_McuRstRsnConfIcumSwSysRst_McuRstRsnConfIcumSwSysRst             (Mcu_ResetType)0x0AU                    /* PRQA S 1534 # JV-01 */

/* The ICUM Application reset Reset Reason Handles */
#define McuConf_McuRstRsnConfIcumSwAppRst_McuRstRsnConfIcumSwAppRst             (Mcu_ResetType)0x0BU                    /* PRQA S 1534 # JV-01 */

/* The ECM Delay Timer Overflow reset Reset Reason Handles */
#define McuConf_McuRstRsnConfEcmDlyTimerOflowRst_McuRstRsnConfEcmDlyTimerOflowRst                                       /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0x0CU

/* The ECM Compare Error reset Reset Reason Handles */
#define McuConf_McuRstRsnConfEcmCompErrRst_McuRstRsnConfEcmCompErrRst           (Mcu_ResetType)0x0DU                    /* PRQA S 1534 # JV-01 */

/* The ECM Mode Error 0 reset Reset Reason Handles */
#define McuConf_McuRstRsnConfModeErr0Rst_McuRstRsnConfModeErr0Rst               (Mcu_ResetType)0x0EU                    /* PRQA S 1534 # JV-01 */

/* The ECM Mode Error 1 reset Reset Reason Handles */
#define McuConf_McuRstRsnConfModeErr1Rst_McuRstRsnConfModeErr1Rst               (Mcu_ResetType)0x0FU                    /* PRQA S 1534 # JV-01 */

/* The ECM Mode Error 2 reset Reset Reason Handles */
#define McuConf_McuRstRsnConfModeErr2Rst_McuRstRsnConfModeErr2Rst               (Mcu_ResetType)0x10U                    /* PRQA S 1534 # JV-01 */

/* The ECM Mode Error 3 reset Reset Reason Handles */
#define McuConf_McuRstRsnConfModeErr3Rst_McuRstRsnConfModeErr3Rst               (Mcu_ResetType)0x11U                    /* PRQA S 1534 # JV-01 */

/* The ECM Mode Error 4 reset Reset Reason Handles */
#define McuConf_McuRstRsnConfModeErr4Rst_McuRstRsnConfModeErr4Rst               (Mcu_ResetType)0x12U                    /* PRQA S 1534 # JV-01 */

/* The ECM Mode Error 5 reset Reset Reason Handles */
#define McuConf_McuRstRsnConfModeErr5Rst_McuRstRsnConfModeErr5Rst               (Mcu_ResetType)0x13U                    /* PRQA S 1534 # JV-01 */

/* The ECM Mode Error 6 reset Reset Reason Handles */
#define McuConf_McuRstRsnConfModeErr6Rst_McuRstRsnConfModeErr6Rst               (Mcu_ResetType)0x14U                    /* PRQA S 1534 # JV-01 */

/* The ECM Flash Access Error reset Reset Reason Handles */
#define McuConf_McuRstRsnConfFlashAccessErrRst_McuRstRsnConfFlashAccessErrRst   (Mcu_ResetType)0x15U                    /* PRQA S 1534 # JV-01 */

/* The ECM DTS compare error reset Reset Reason Handles */
#define McuConf_McuRstRsnConfDtsCompErrRst_McuRstRsnConfDtsCompErrRst           (Mcu_ResetType)0x16U                    /* PRQA S 1534 # JV-01 */

#define McuConf_McuRstRsnConfRDC0CompErrRst_McuRstRsnConfRDC0CompErrRst         (Mcu_ResetType)0x17U                    /* PRQA S 1534 # JV-01 */

#define McuConf_McuRstRsnConfRDC1CompErrRst_McuRstRsnConfRDC1CompErrRst         (Mcu_ResetType)0x18U                    /* PRQA S 1534 # JV-01 */

#define McuConf_McuRstRsnConfsDmac0Cn0CompErrRst_McuRstRsnConfsDmac0Cn0CompErrRst                                       /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0x19U

#define McuConf_McuRstRsnConfsDmac0Cn1CompErrRst_McuRstRsnConfsDmac0Cn1CompErrRst                                       /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0x1AU

#define McuConf_McuRstRsnConfsDmac0Cn2CompErrRst_McuRstRsnConfsDmac0Cn2CompErrRst                                       /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0x1BU

#define McuConf_McuRstRsnConfsDmac0Cn3CompErrRst_McuRstRsnConfsDmac0Cn3CompErrRst                                       /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0x1CU

#define McuConf_McuRstRsnConfsDmac0Cn4CompErrRst_McuRstRsnConfsDmac0Cn4CompErrRst                                       /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0x1DU

#define McuConf_McuRstRsnConfsDmac0Cn5CompErrRst_McuRstRsnConfsDmac0Cn5CompErrRst                                       /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0x1EU

#define McuConf_McuRstRsnConfsDmac0Cn6CompErrRst_McuRstRsnConfsDmac0Cn6CompErrRst                                       /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0x1FU

#define McuConf_McuRstRsnConfsDmac0Cn7CompErrRst_McuRstRsnConfsDmac0Cn7CompErrRst                                       /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0x20U

#define McuConf_McuRstRsnConfsDmac1Cn0CompErrRst_McuRstRsnConfsDmac1Cn0CompErrRst                                       /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0x21U

#define McuConf_McuRstRsnConfsDmac1Cn1CompErrRst_McuRstRsnConfsDmac1Cn1CompErrRst                                       /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0x22U

#define McuConf_McuRstRsnConfsDmac1Cn2CompErrRst_McuRstRsnConfsDmac1Cn2CompErrRst                                       /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0x23U

#define McuConf_McuRstRsnConfsDmac1Cn3CompErrRst_McuRstRsnConfsDmac1Cn3CompErrRst                                       /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0x24U

#define McuConf_McuRstRsnConfsDmac1Cn4CompErrRst_McuRstRsnConfsDmac1Cn4CompErrRst                                       /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0x25U

#define McuConf_McuRstRsnConfsDmac1Cn5CompErrRst_McuRstRsnConfsDmac1Cn5CompErrRst                                       /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0x26U

#define McuConf_McuRstRsnConfsDmac1Cn6CompErrRst_McuRstRsnConfsDmac1Cn6CompErrRst                                       /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0x27U

#define McuConf_McuRstRsnConfsDmac1Cn7CompErrRst_McuRstRsnConfsDmac1Cn7CompErrRst                                       /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0x28U

#define McuConf_McuRstRsnConfBusBridgeCompErrsDmc0Rst_McuRstRsnConfBusBridgeCompErrsDmc0Rst                             /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0x29U

#define McuConf_McuRstRsnConfBusBridgeCompErrsDmc1Rst_McuRstRsnConfBusBridgeCompErrsDmc1Rst                             /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0x2AU

/* The ECM BUS Bridge compare error reset Reset Reason Handles */
#define McuConf_McuRstRsnConfBusBridgecompErrorRst_McuRstRsnConfBusBridgecompErrorRst                                   /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0x2BU

#define McuConf_McuRstRsnConfGtmCompErrRst_McuRstRsnConfGtmCompErrRst           (Mcu_ResetType)0x2CU                    /* PRQA S 1534 # JV-01 */

#define McuConf_McuRstRsnConfGtmErrIsrRst_McuRstRsnConfGtmErrIsrRst             (Mcu_ResetType)0x2DU                    /* PRQA S 1534 # JV-01 */

/* The ECM Inter-processor element Bus reset Reset Reason Handles */
#define McuConf_McuRstRsnConfInterProcElementBusRst_McuRstRsnConfInterProcElementBusRst                                 /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0x2EU

/* The ECM Inter-cluster Bus (I-Bus) reset Reset Reason Handles */
#define McuConf_McuRstRsnConfInterClusterBusRst_McuRstRsnConfInterClusterBusRst (Mcu_ResetType)0x2FU                    /* PRQA S 1534 # JV-01 */

/* The ECM Peripheral Bus (P-Bus) reset Reset Reason Handles */
#define McuConf_McuRstRsnConfPheripheralBusRst_McuRstRsnConfPheripheralBusRst   (Mcu_ResetType)0x30U                    /* PRQA S 1534 # JV-01 */

/* The ECM CRAM Bus reset Reset Reason Handles */
#define McuConf_McuRstRsnConfCramBusRst_McuRstRsnConfCramBusRst                 (Mcu_ResetType)0x31U                    /* PRQA S 1534 # JV-01 */

/* The ECM System Bus reset Reset Reason Handles */
#define McuConf_McuRstRsnConfSystemBusRst_McuRstRsnConfSystemBusRst             (Mcu_ResetType)0x32U                    /* PRQA S 1534 # JV-01 */

/* The ECM Global Flash Bus reset Reset Reason Handles */
#define McuConf_McuRstRsnConfGlobalFlashBusRst_McuRstRsnConfGlobalFlashBusRst   (Mcu_ResetType)0x33U                    /* PRQA S 1534 # JV-01 */

/* The ECM Local Flash Bus reset Reset Reason Handles */
#define McuConf_McuRstRsnConfLocalFlashBusRst_McuRstRsnConfLocalFlashBusRst     (Mcu_ResetType)0x34U                    /* PRQA S 1534 # JV-01 */

/* The ECM Clock monitor error reset for MOSC (CLMA0) Reset Reason Handles */
#define McuConf_McuRstRsnConfClmaMoscErrRst_McuRstRsnConfClmaMoscErrRst         (Mcu_ResetType)0x35U                    /* PRQA S 1534 # JV-01 */

/* The ECM Clock monitor error reset for HSintOSC (CLMA1) Reset Reason Handles */
#define McuConf_McuRstRsnConfClmaHoscErrRst_McuRstRsnConfClmaHoscErrRst         (Mcu_ResetType)0x36U                    /* PRQA S 1534 # JV-01 */

/* The ECM Clock monitor error reset for LSintOSC (CLMA2) Reset Reason Handles */
#define McuConf_McuRstRsnConfClmaLoscErrRst_McuRstRsnConfClmaLoscErrRst         (Mcu_ResetType)0x37U                    /* PRQA S 1534 # JV-01 */

/* The ECM Clock monitor error reset for CLK_LSB (CLMA3and4) Reset Reason Handles */
#define McuConf_McuRstRsnConfClmaLsbErrRst_McuRstRsnConfClmaLsbErrRst           (Mcu_ResetType)0x38U                    /* PRQA S 1534 # JV-01 */

/* The ECM Clock monitor error reset for CLK_UHSB (CLMA5) Reset Reason Handles */
#define McuConf_McuRstRsnConfClmaUhsbErrRst_McuRstRsnConfClmaUhsbErrRst         (Mcu_ResetType)0x39U                    /* PRQA S 1534 # JV-01 */

#define McuConf_McuRstRsnConfClmaClkcLsbErrRst_McuRstRsnConfClmaClkcLsbErrRst   (Mcu_ResetType)0x3AU                    /* PRQA S 1534 # JV-01 */

#define McuConf_McuRstRsnConfClmaSbusErrRst_McuRstRsnConfClmaSbusErrRst         (Mcu_ResetType)0x3BU                    /* PRQA S 1534 # JV-01 */

/* The ECM OSTM1 interrupt reset Reset Reason Handles */
#define McuConf_McuRstRsnConfOstm1IntRst_McuRstRsnConfOstm1IntRst               (Mcu_ResetType)0x3CU                    /* PRQA S 1534 # JV-01 */

/* The ECM OSTM2 interrupt reset Reset Reason Handles */
#define McuConf_McuRstRsnConfOstm2IntRst_McuRstRsnConfOstm2IntRst               (Mcu_ResetType)0x3DU                    /* PRQA S 1534 # JV-01 */

/* The ECM OSTM3 interrupt reset Reset Reason Handles */
#define McuConf_McuRstRsnConfOstm3IntRst_McuRstRsnConfOstm3IntRst               (Mcu_ResetType)0x3EU                    /* PRQA S 1534 # JV-01 */

/* The ECM OSTM4 interrupt reset Reset Reason Handles */
#define McuConf_McuRstRsnConfOstm4IntRst_McuRstRsnConfOstm4IntRst               (Mcu_ResetType)0x3FU                    /* PRQA S 1534 # JV-01 */

/* The ECM OSTM5 interrupt reset Reset Reason Handles */
#define McuConf_McuRstRsnConfOstm5IntRst_McuRstRsnConfOstm5IntRst               (Mcu_ResetType)0x40U                    /* PRQA S 1534 # JV-01 */

/* The ECM OSTM6 interrupt reset Reset Reason Handles */
#define McuConf_McuRstRsnConfOstm6IntRst_McuRstRsnConfOstm6IntRst               (Mcu_ResetType)0x41U                    /* PRQA S 1534 # JV-01 */

#define McuConf_McuRstRsnConfOspiErrIsrRst_McuRstRsnConfOspiErrIsrRst           (Mcu_ResetType)0x42U                    /* PRQA S 1534 # JV-01 */

#define McuConf_McuRstRsnConfCanXL0IntRst_McuRstRsnConfCanXL0IntRst             (Mcu_ResetType)0x43U                    /* PRQA S 1534 # JV-01 */

#define McuConf_McuRstRsnConfCanXL1IntRst_McuRstRsnConfCanXL1IntRst             (Mcu_ResetType)0x44U                    /* PRQA S 1534 # JV-01 */

#define McuConf_McuRstRsnConfDsmif0CompErrRst_McuRstRsnConfDsmif0CompErrRst     (Mcu_ResetType)0x45U                    /* PRQA S 1534 # JV-01 */

#define McuConf_McuRstRsnConfDsmif1CompErrRst_McuRstRsnConfDsmif1CompErrRst     (Mcu_ResetType)0x46U                    /* PRQA S 1534 # JV-01 */

#define McuConf_McuRstRsnConfTsg30ErrIsrRst_McuRstRsnConfTsg30ErrIsrRst         (Mcu_ResetType)0x47U                    /* PRQA S 1534 # JV-01 */

#define McuConf_McuRstRsnConfTsg31ErrIsrRst_McuRstRsnConfTsg31ErrIsrRst         (Mcu_ResetType)0x48U                    /* PRQA S 1534 # JV-01 */

#define McuConf_McuRstRsnConfTsg32ErrIsrRst_McuRstRsnConfTsg32ErrIsrRst         (Mcu_ResetType)0x49U                    /* PRQA S 1534 # JV-01 */

#define McuConf_McuRstRsnConfSecPowerSuppErrRst_McuRstRsnConfSecPowerSuppErrRst (Mcu_ResetType)0x4AU                    /* PRQA S 1534 # JV-01 */

/* The ECM AD parity error reset Reset Reason Handles */
#define McuConf_McuRstRsnConfAdParityErrRst_McuRstRsnConfAdParityErrRst         (Mcu_ResetType)0x4BU                    /* PRQA S 1534 # JV-01 */

#define McuConf_McuRstRsnConfFastCompErrRst_McuRstRsnConfFastCompErrRst         (Mcu_ResetType)0x4CU                    /* PRQA S 1534 # JV-01 */

#define McuConf_McuRstRsnConfResolveConvErrRst_McuRstRsnConfResolveConvErrRst   (Mcu_ResetType)0x4DU                    /* PRQA S 1534 # JV-01 */

/* The ECM Temperature sensor error reset Reset Reason Handles */
#define McuConf_McuRstRsnConfTempSensorerrRst_McuRstRsnConfTempSensorerrRst     (Mcu_ResetType)0x4EU                    /* PRQA S 1534 # JV-01 */

/* The ECM Code Flash Address parity error reset Reset Reason Handles */
#define McuConf_McuRstRsnConfCflhErrAdrPrtyErrRst_McuRstRsnConfCflhErrAdrPrtyErrRst                                     /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0x4FU

/* The ECM Code Flash ECC 2bit error reset Reset Reason Handles */
#define McuConf_McuRstRsnConfCflhEcc2bitErrRst_McuRstRsnConfCflhEcc2bitErrRst   (Mcu_ResetType)0x50U                    /* PRQA S 1534 # JV-01 */

/* The ECM Code Flash ECC 1bit error reset Reset Reason Handles */
#define McuConf_McuRstRsnConfCflhEcc1bitErrRst_McuRstRsnConfCflhEcc1bitErrRst   (Mcu_ResetType)0x51U                    /* PRQA S 1534 # JV-01 */

/* The ECM Code Flash ECC Error address overflow reset Reset Reason Handles */
#define McuConf_McuRstRsnConfCflhErrAdrOflowRst_McuRstRsnConfCflhErrAdrOflowRst (Mcu_ResetType)0x52U                    /* PRQA S 1534 # JV-01 */

/* The ECM Data Flash ECC 2 bit error reset Reset Reason Handles */
#define McuConf_McuRstRsnConfDflhEcc2bitErrRst_McuRstRsnConfDflhEcc2bitErrRst   (Mcu_ResetType)0x53U                    /* PRQA S 1534 # JV-01 */

/* The ECM Data Flash ECC 1bit error reset Reset Reason Handles */
#define McuConf_McuRstRsnConfDflhEcc1bitErrRst_McuRstRsnConfDflhEcc1bitErrRst   (Mcu_ResetType)0x54U                    /* PRQA S 1534 # JV-01 */

/* The ECM Data Flash ECC Error address overflow reset Reset Reason Handles */
#define McuConf_McuRstRsnConfDflhErrAdrOflowRst_McuRstRsnConfDflhErrAdrOflowRst (Mcu_ResetType)0x55U                    /* PRQA S 1534 # JV-01 */

/* The ECM LRAM (error by other core access) ECC 2bit error reset Reset Reason Handles */
#define McuConf_McuRstRsnConfLramEcc2bitErrRst_McuRstRsnConfLramEcc2bitErrRst   (Mcu_ResetType)0x56U                    /* PRQA S 1534 # JV-01 */

/* The ECM LRAM (error by other core access) ECC 1bit error reset Reset Reason Handles */
#define McuConf_McuRstRsnConfLramEcc1bitErrRst_McuRstRsnConfLramEcc1bitErrRst   (Mcu_ResetType)0x57U                    /* PRQA S 1534 # JV-01 */

/* The ECM LRAM (error by other core access) Error address overflow reset Reset Reason Handles */
#define McuConf_McuRstRsnConfLramErrAdrOflowRst_McuRstRsnConfLramErrAdrOflowRst (Mcu_ResetType)0x58U                    /* PRQA S 1534 # JV-01 */

/* The ECM Cluster RAM Address feedback compare error or ECC 2bit error reset Reset Reason Handles */
#define McuConf_McuRstRsnConfCramAdrOrEcc2ErrRst_McuRstRsnConfCramAdrOrEcc2ErrRst                                       /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0x59U

/* The ECM Cluster RAM ECC 1bit error reset Reset Reason Handles */
#define McuConf_McuRstRsnConfCramEcc1bitErrRst_McuRstRsnConfCramEcc1bitErrRst   (Mcu_ResetType)0x5AU                    /* PRQA S 1534 # JV-01 */

/* The ECM Cluster RAM ECC Error address overflow reset Reset Reason Handles */
#define McuConf_McuRstRsnConfCramErrAdrOflowRst_McuRstRsnConfCramErrAdrOflowRst (Mcu_ResetType)0x5BU                    /* PRQA S 1534 # JV-01 */

/* The ECM DTS RAM Address feedback compare error or ECC 2bit error reset Reset Reason Handles */
#define McuConf_McuRstRsnConfDtsramEcc2bitErrRst_McuRstRsnConfDtsramEcc2bitErrRst                                       /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0x5CU

/* The ECM DTS RAM ECC 1bit error reset Reset Reason Handles */
#define McuConf_McuRstRsnConfDtsramEcc1bitErrRst_McuRstRsnConfDtsramEcc1bitErrRst                                       /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0x5DU

/* The ECM DTS RAM ECC Error address overflow reset Reset Reason Handles */
#define McuConf_McuRstRsnConfDtsramErrAdrOflowRst_McuRstRsnConfDtsramErrAdrOflowRst                                     /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0x5EU

/* The ECM sDMA0 RAM ECC 2bit error reset Reset Reason Handles */
#define McuConf_McuRstRsnConfSdmac0RamEcc2bitErrRst_McuRstRsnConfSdmac0RamEcc2bitErrRst                                 /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0x5FU

/* The ECM sDMA0 RAM ECC 1bit error reset Reset Reason Handles */
#define McuConf_McuRstRsnConfSdmac0RamEcc1bitErrRst_McuRstRsnConfSdmac0RamEcc1bitErrRst                                 /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0x60U

/* The ECM sDMA1 RAM ECC 2bit error reset Reset Reason Handles */
#define McuConf_McuRstRsnConfSdmac1RamEcc2bitErrRst_McuRstRsnConfSdmac1RamEcc2bitErrRst                                 /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0x61U

/* The ECM sDMA1 RAM ECC 1bit error reset Reset Reason Handles */
#define McuConf_McuRstRsnConfSdmac1RamEcc1bitErrRst_McuRstRsnConfSdmac1RamEcc1bitErrRst                                 /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0x62U

#define McuConf_McuRstRsnConfExCRamEcc2bitErrRst_McuRstRsnConfExCRamEcc2bitErrRst                                       /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0x63U

#define McuConf_McuRstRsnConfExCRamEcc1bitErrRst_McuRstRsnConfExCRamEcc1bitErrRst                                       /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0x64U

#define McuConf_McuRstRsnConfExCRamErrAdrOflowRst_McuRstRsnConfExCRamErrAdrOflowRst                                     /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0x65U

/* The ECM Peripheral(FlexRay) RAM ECC 2bit error reset Reset Reason Handles */
#define McuConf_McuRstRsnConfFrramEcc2bitErrRst_McuRstRsnConfFrramEcc2bitErrRst (Mcu_ResetType)0x66U                    /* PRQA S 1534 # JV-01 */

/* The ECM Peripheral(FlexRay) RAM ECC 1bit error reset Reset Reason Handles */
#define McuConf_McuRstRsnConfFrramEcc1bitErrRst_McuRstRsnConfFrramEcc1bitErrRst (Mcu_ResetType)0x67U                    /* PRQA S 1534 # JV-01 */

/* The ECM Peripheral(CAN) RAM ECC 2bit error reset Reset Reason Handles */
#define McuConf_McuRstRsnConfCanramEcc2bitErrRst_McuRstRsnConfCanramEcc2bitErrRst                                       /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0x68U

/* The ECM Peripheral(CAN) RAM ECC 1bit error reset Reset Reason Handles */
#define McuConf_McuRstRsnConfCanramEcc1bitErrRst_McuRstRsnConfCanramEcc1bitErrRst                                       /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0x69U

/* The ECM Peripheral(MSPI) RAM ECC 2bit error reset Reset Reason Handles */
#define McuConf_McuRstRsnConfMspiramEcc2bitErrRst_McuRstRsnConfMspiramEcc2bitErrRst                                     /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0x6AU

/* The ECM Peripheral(MSPI) RAM ECC 1bit error reset Reset Reason Handles */
#define McuConf_McuRstRsnConfMspiramEcc1bitErrRst_McuRstRsnConfMspiramEcc1bitErrRst                                     /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0x6BU

/* The ECM Peripheral(GTM) RAM ECC 2bit error reset Reset Reason Handles */
#define McuConf_McuRstRsnConfGtmramEcc2bitErrRst_McuRstRsnConfGtmramEcc2bitErrRst                                       /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0x6CU

/* The ECM Peripheral(GTM) RAM ECC 1bit error reset Reset Reason Handles */
#define McuConf_McuRstRsnConfGtmramEcc1bitErrRst_McuRstRsnConfGtmramEcc1bitErrRst                                       /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0x6DU

/* The ECM Peripheral(MMC) RAM ECC 2bit error reset Reset Reason Handles */
#define McuConf_McuRstRsnConfMmcaRamEcc2bitErrRst_McuRstRsnConfMmcaRamEcc2bitErrRst                                     /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0x6EU

/* The ECM Peripheral(MMC) RAM ECC 1bit error reset Reset Reason Handles */
#define McuConf_McuRstRsnConfMmcaRamEcc1bitErrRst_McuRstRsnConfMmcaRamEcc1bitErrRst                                     /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0x6FU

#define McuConf_McuRstRsnConfDfe0RamErr2bitRst_McuRstRsnConfDfe0RamErr2bitRst   (Mcu_ResetType)0x70U                    /* PRQA S 1534 # JV-01 */

#define McuConf_McuRstRsnConfDfe0RamErr1bitRst_McuRstRsnConfDfe0RamErr1bitRst   (Mcu_ResetType)0x71U                    /* PRQA S 1534 # JV-01 */

#define McuConf_McuRstRsnConfRswitchRamEcc2bitErrRst_McuRstRsnConfRswitchRamEcc2bitErrRst                               /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0x72U

#define McuConf_McuRstRsnConfRswitchRamEcc1bitErrRst_McuRstRsnConfRswitchRamEcc1bitErrRst                               /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0x73U

#define McuConf_McuRstRsnConfCanxlramEcc2bitErrRst_McuRstRsnConfCanxlramEcc2bitErrRst                                   /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0x74U

#define McuConf_McuRstRsnConfCanxlramEcc1bitErrRst_McuRstRsnConfCanxlramEcc1bitErrRst                                   /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0x75U

#define McuConf_McuRstRsnConfETNFFIFOEcc2bitErrRst_McuRstRsnConfETNFFIFOEcc2bitErrRst                                   /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0x76U

#define McuConf_McuRstRsnConfETNFFIFOEcc1bitErrRst_McuRstRsnConfETNFFIFOEcc1bitErrRst                                   /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0x77U

#define McuConf_McuRstRsnConfOSPIEcc2bitErrRst_McuRstRsnConfOSPIEcc2bitErrRst   (Mcu_ResetType)0x78U                    /* PRQA S 1534 # JV-01 */

#define McuConf_McuRstRsnConfOSPIEcc1bitErrRst_McuRstRsnConfOSPIEcc1bitErrRst   (Mcu_ResetType)0x79U                    /* PRQA S 1534 # JV-01 */

/* The ECM Peripheral RAM ECC and sDMA RAM ECC Error address overflow reset Reset Reason Handles */
#define McuConf_McuRstRsnConfPeriRamEccOflowErrRst_McuRstRsnConfPeriRamEccOflowErrRst                                   /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0x7AU

/* The ECM Address Bus ECC EDC 2bit error or EDC 1bit error reset Reset Reason Handles */
#define McuConf_McuRstRsnConfAdrbusEdcEccErrRst_McuRstRsnConfAdrbusEdcEccErrRst (Mcu_ResetType)0x7BU                    /* PRQA S 1534 # JV-01 */

/* The ECM Data Bus ECC 2bit error reset Reset Reason Handles */
#define McuConf_McuRstRsnConfDatabusEcc2bitErrRst_McuRstRsnConfDatabusEcc2bitErrRst                                     /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0x7CU

/* The ECM Data Bus ECC 1bit error reset Reset Reason Handles */
#define McuConf_McuRstRsnConfDatabusEcc1bitErrRst_McuRstRsnConfDatabusEcc1bitErrRst                                     /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0x7DU

#define McuConf_McuRstRsnConfExCramGuardErrRst_McuRstRsnConfExCramGuardErrRst   (Mcu_ResetType)0x7EU                    /* PRQA S 1534 # JV-01 */

/* The ECM CRAM Guard error reset Reset Reason Handles */
#define McuConf_McuRstRsnConfCramGuardErrRst_McuRstRsnConfCramGuardErrRst       (Mcu_ResetType)0x7FU                    /* PRQA S 1534 # JV-01 */

/* The ECM I-Bus Guard error (IPIR, Barrier sync and TPTM) reset Reset Reason Handles */
#define McuConf_McuRstRsnConfIbusGuardErrRst_McuRstRsnConfIbusGuardErrRst       (Mcu_ResetType)0x80U                    /* PRQA S 1534 # JV-01 */

/* The ECM P-Bus Guard error reset Reset Reason Handles */
#define McuConf_McuRstRsnConfPbusGuardErrRst_McuRstRsnConfPbusGuardErrRst       (Mcu_ResetType)0x81U                    /* PRQA S 1534 # JV-01 */

/* The ECM H-Bus Guard error reset Reset Reason Handles */
#define McuConf_McuRstRsnConfHbusGuardErrRst_McuRstRsnConfHbusGuardErrRst       (Mcu_ResetType)0x82U                    /* PRQA S 1534 # JV-01 */

#define McuConf_McuRstRsnConfIcumDmacRamEcc2bitErrRst_McuRstRsnConfIcumDmacRamEcc2bitErrRst                             /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0x83U

#define McuConf_McuRstRsnConfIcumDmacRamEcc1bitErrRst_McuRstRsnConfIcumDmacRamEcc1bitErrRst                             /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0x84U

/* The ECM DMA Address Error or DTS Transfer Error reset Reset Reason Handles */
#define McuConf_McuRstRsnConfDataTransDmaOrDtsErrRst_McuRstRsnConfDataTransDmaOrDtsErrRst                               /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0x85U

/* The ECM H-Bus master Transfer Error reset Reset Reason Handles */
#define McuConf_McuRstRsnConfDataTransHbusErrRst_McuRstRsnConfDataTransHbusErrRst                                       /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0x86U

/* The ECM ERRORIN0 reset Reset Reason Handles */
#define McuConf_McuRstRsnConfExtErrin0Rst_McuRstRsnConfExtErrin0Rst             (Mcu_ResetType)0x87U                    /* PRQA S 1534 # JV-01 */

/* The ECM ERRORIN1 reset Reset Reason Handles */
#define McuConf_McuRstRsnConfExtErrin1Rst_McuRstRsnConfExtErrin1Rst             (Mcu_ResetType)0x88U                    /* PRQA S 1534 # JV-01 */

/* The ECM ERRORIN2 reset Reset Reason Handles */
#define McuConf_McuRstRsnConfExtErrin2Rst_McuRstRsnConfExtErrin2Rst             (Mcu_ResetType)0x89U                    /* PRQA S 1534 # JV-01 */

/* The ECM ERRORIN3 reset Reset Reason Handles */
#define McuConf_McuRstRsnConfExtErrin3Rst_McuRstRsnConfExtErrin3Rst             (Mcu_ResetType)0x8AU                    /* PRQA S 1534 # JV-01 */

#define McuConf_McuRstRsnConfExtErrin4Rst_McuRstRsnConfExtErrin4Rst             (Mcu_ResetType)0x8BU                    /* PRQA S 1534 # JV-01 */

#define McuConf_McuRstRsnConfExtErrin5Rst_McuRstRsnConfExtErrin5Rst             (Mcu_ResetType)0x8CU                    /* PRQA S 1534 # JV-01 */

#define McuConf_McuRstRsnConfExtErrin6Rst_McuRstRsnConfExtErrin6Rst             (Mcu_ResetType)0x8DU                    /* PRQA S 1534 # JV-01 */

#define McuConf_McuRstRsnConfExtErrin7Rst_McuRstRsnConfExtErrin7Rst             (Mcu_ResetType)0x8EU                    /* PRQA S 1534 # JV-01 */

/* The ECM SW alarm 0 reset Reset Reason Handles */
#define McuConf_McuRstRsnConfSwAlarm0Rst_McuRstRsnConfSwAlarm0Rst               (Mcu_ResetType)0x8FU                    /* PRQA S 1534 # JV-01 */

/* The ECM SW alarm 1 reset Reset Reason Handles */
#define McuConf_McuRstRsnConfSwAlarm1Rst_McuRstRsnConfSwAlarm1Rst               (Mcu_ResetType)0x90U                    /* PRQA S 1534 # JV-01 */

/* The ECM SW alarm 2 reset Reset Reason Handles */
#define McuConf_McuRstRsnConfSwAlarm2Rst_McuRstRsnConfSwAlarm2Rst               (Mcu_ResetType)0x91U                    /* PRQA S 1534 # JV-01 */

/* The ECM SW alarm 3 reset Reset Reason Handles */
#define McuConf_McuRstRsnConfSwAlarm3Rst_McuRstRsnConfSwAlarm3Rst               (Mcu_ResetType)0x92U                    /* PRQA S 1534 # JV-01 */

#define McuConf_McuRstRsnConfSwAlarm4Rst_McuRstRsnConfSwAlarm4Rst               (Mcu_ResetType)0x93U                    /* PRQA S 1534 # JV-01 */

#define McuConf_McuRstRsnConfSwAlarm5Rst_McuRstRsnConfSwAlarm5Rst               (Mcu_ResetType)0x94U                    /* PRQA S 1534 # JV-01 */

#define McuConf_McuRstRsnConfSwAlarm6Rst_McuRstRsnConfSwAlarm6Rst               (Mcu_ResetType)0x95U                    /* PRQA S 1534 # JV-01 */

#define McuConf_McuRstRsnConfIcumHBCompErrRst_McuRstRsnConfIcumHBCompErrRst     (Mcu_ResetType)0x96U                    /* PRQA S 1534 # JV-01 */

#define McuConf_McuRstRsnConfAce0CompErrRst_McuRstRsnConfAce0CompErrRst         (Mcu_ResetType)0x97U                    /* PRQA S 1534 # JV-01 */

#define McuConf_McuRstRsnConfAce1CompErrRst_McuRstRsnConfAce1CompErrRst         (Mcu_ResetType)0x98U                    /* PRQA S 1534 # JV-01 */

#define McuConf_McuRstRsnConfIcumHbBusRoutingRst_McuRstRsnConfIcumHbBusRoutingRst                                       /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0x99U

#define McuConf_McuRstRsnConfBusSecurityEcc2bitErrRst_McuRstRsnConfBusSecurityEcc2bitErrRst                             /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0x9AU

#define McuConf_McuRstRsnConfBusSecurityEcc1bitErrRst_McuRstRsnConfBusSecurityEcc1bitErrRst                             /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0x9BU

#define McuConf_McuRstRsnConfSecurityGuardErrRst_McuRstRsnConfSecurityGuardErrRst                                       /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0x9CU

#define McuConf_McuRstRsnConfSecurityDrTransErrRst_McuRstRsnConfSecurityDrTransErrRst                                   /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0x9DU

#define McuConf_McuRstRsnConfAce2CompErrRst_McuRstRsnConfAce2CompErrRst         (Mcu_ResetType)0x9EU                    /* PRQA S 1534 # JV-01 */

#define McuConf_McuRstRsnConfAce3CompErrRst_McuRstRsnConfAce3CompErrRst         (Mcu_ResetType)0x9FU                    /* PRQA S 1534 # JV-01 */

#define McuConf_McuRstRsnConfDfaCompErrRst_McuRstRsnConfDfaCompErrRst           (Mcu_ResetType)0xA0U                    /* PRQA S 1534 # JV-01 */

#define McuConf_McuRstRsnConfDfaHwCheckErrRst_McuRstRsnConfDfaHwCheckErrRst     (Mcu_ResetType)0xA1U                    /* PRQA S 1534 # JV-01 */

#define McuConf_McuRstRsnConfClmaDfaErrRst_McuRstRsnConfClmaDfaErrRst           (Mcu_ResetType)0xA2U                    /* PRQA S 1534 # JV-01 */

#define McuConf_McuRstRsnConfLramEcc2bitErrDfaErrRst_McuRstRsnConfLramEcc2bitErrDfaErrRst                               /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0xA3U

#define McuConf_McuRstRsnConfLramEcc1bitErrDfaErrRst_McuRstRsnConfLramEcc1bitErrDfaErrRst                               /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0xA4U

#define McuConf_McuRstRsnConfDfaErrOflowRst_McuRstRsnConfDfaErrOflowRst         (Mcu_ResetType)0xA5U                    /* PRQA S 1534 # JV-01 */

#define McuConf_McuRstRsnConfDfaBusParityErrRst_McuRstRsnConfDfaBusParityErrRst (Mcu_ResetType)0xA6U                    /* PRQA S 1534 # JV-01 */

#define McuConf_McuRstRsnConfDfaGuardErrRst_McuRstRsnConfDfaGuardErrRst         (Mcu_ResetType)0xA7U                    /* PRQA S 1534 # JV-01 */

/* The ECM DCLS compare error reset (PE0) Reset Reason Handles */
#define McuConf_McuRstRsnConfDclsCompErrPe0Rst_McuRstRsnConfDclsCompErrPe0Rst   (Mcu_ResetType)0xA8U                    /* PRQA S 1534 # JV-01 */

#define McuConf_McuRstRsnConfDclsModeErrPe0Rst_McuRstRsnConfDclsModeErrPe0Rst   (Mcu_ResetType)0xA9U                    /* PRQA S 1534 # JV-01 */

/* The ECM Unintended Debug Enable detection reset (PE0) Reset Reason Handles */
#define McuConf_McuRstRsnConfModeUnintDebugEnablePe0Rst_McuRstRsnConfModeUnintDebugEnablePe0Rst                         /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0xAAU

/* The ECM Watchdog timer error reset (PE0) Reset Reason Handles */
#define McuConf_McuRstRsnConfWdtErrPe0Rst_McuRstRsnConfWdtErrPe0Rst             (Mcu_ResetType)0xABU                    /* PRQA S 1534 # JV-01 */

/* The ECM Clock monitor error reset for CLK_CPU (PE0) (CLMA6) Reset Reason Handles */
#define McuConf_McuRstRsnConfClmaErrPe0Rst_McuRstRsnConfClmaErrPe0Rst           (Mcu_ResetType)0xACU                    /* PRQA S 1534 # JV-01 */

/* The ECM Local RAM Address feedback compare error or ECC 2bit error (PE0) Reset Reason Handles */
#define McuConf_McuRstRsnConfLramAdrOrEcc2ErrPe0Rst_McuRstRsnConfLramAdrOrEcc2ErrPe0Rst                                 /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0xADU

/* The ECM Local RAM ECC 1bit error reset (PE0) Reset Reason Handles */
#define McuConf_McuRstRsnConfLramEcc1ErrPe0Rst_McuRstRsnConfLramEcc1ErrPe0Rst   (Mcu_ResetType)0xAEU                    /* PRQA S 1534 # JV-01 */

/* The ECM Local RAM ECC Error address overflow reset (PE0) Reset Reason Handles */
#define McuConf_McuRstRsnConfLramErradrOflowPe0Rst_McuRstRsnConfLramErradrOflowPe0Rst                                   /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0xAFU

/* The ECM Instruction Cache RAM Address feedback compare error, EDC 2bit error or EDC 1bit error reset (PE0) Reset   */
/*   Reason Handles                                                                                                   */
#define McuConf_McuRstRsnConfIcacheAdrOrEdcErrPe0Rst_McuRstRsnConfIcacheAdrOrEdcErrPe0Rst                               /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0xB0U

/* The ECM PEG error reset (PE0) Reset Reason Handles */
#define McuConf_McuRstRsnConfPeguardErrPe0Rst_McuRstRsnConfPeguardErrPe0Rst     (Mcu_ResetType)0xB1U                    /* PRQA S 1534 # JV-01 */

/* The ECM PEG error (Detected in a read request from PE to the other LRAM) reset (PE0) Reset Reason Handles */
#define McuConf_McuRstRsnConfPegOtherLramreqPe0Rst_McuRstRsnConfPegOtherLramreqPe0Rst                                   /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0xB2U

/* The ECM Data Access Error reset (PE0) Reset Reason Handles */
#define McuConf_McuRstRsnConfDataAccessErrPe0Rst_McuRstRsnConfDataAccessErrPe0Rst                                       /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0xB3U

/* The ECM DCLS compare error reset (PE1) Reset Reason Handles */
#define McuConf_McuRstRsnConfDclsCompErrPe1Rst_McuRstRsnConfDclsCompErrPe1Rst   (Mcu_ResetType)0xB4U                    /* PRQA S 1534 # JV-01 */

#define McuConf_McuRstRsnConfDclsModeErrPe1Rst_McuRstRsnConfDclsModeErrPe1Rst   (Mcu_ResetType)0xB5U                    /* PRQA S 1534 # JV-01 */

#define McuConf_McuRstRsnConfUnintDisableEnableDetectionPe1Rst_McuRstRsnConfUnintDisableEnableDetectionPe1Rst           /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0xB6U

/* The ECM Unintended Debug Enable detection reset (PE1) Reset Reason Handles */
#define McuConf_McuRstRsnConfModeUnintDebugEnablePe1Rst_McuRstRsnConfModeUnintDebugEnablePe1Rst                         /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0xB7U

/* The ECM Watchdog timer error reset (PE1) Reset Reason Handles */
#define McuConf_McuRstRsnConfWdtErrPe1Rst_McuRstRsnConfWdtErrPe1Rst             (Mcu_ResetType)0xB8U                    /* PRQA S 1534 # JV-01 */

/* The ECM Clock monitor error reset for CLK_CPU (PE1) (CLMA7) Reset Reason Handles */
#define McuConf_McuRstRsnConfClmaErrPe1Rst_McuRstRsnConfClmaErrPe1Rst           (Mcu_ResetType)0xB9U                    /* PRQA S 1534 # JV-01 */

/* The ECM Local RAM Address feedback compare error or ECC 2bit error (PE1) Reset Reason Handles */
#define McuConf_McuRstRsnConfLramAdrOrEcc2ErrPe1Rst_McuRstRsnConfLramAdrOrEcc2ErrPe1Rst                                 /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0xBAU

/* The ECM Local RAM ECC 1bit error reset (PE1) Reset Reason Handles */
#define McuConf_McuRstRsnConfLramEcc1ErrPe1Rst_McuRstRsnConfLramEcc1ErrPe1Rst   (Mcu_ResetType)0xBBU                    /* PRQA S 1534 # JV-01 */

/* The ECM Local RAM ECC Error address overflow reset (PE1) Reset Reason Handles */
#define McuConf_McuRstRsnConfLramErradrOflowPe1Rst_McuRstRsnConfLramErradrOflowPe1Rst                                   /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0xBCU

/* The ECM Instruction Cache RAM Address feedback compare error, EDC 2bit error or EDC 1bit error reset (PE1) Reset   */
/*   Reason Handles                                                                                                   */
#define McuConf_McuRstRsnConfIcacheAdrOrEdcErrPe1Rst_McuRstRsnConfIcacheAdrOrEdcErrPe1Rst                               /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0xBDU

/* The ECM PEG error reset (PE1) Reset Reason Handles */
#define McuConf_McuRstRsnConfPeguardErrPe1Rst_McuRstRsnConfPeguardErrPe1Rst     (Mcu_ResetType)0xBEU                    /* PRQA S 1534 # JV-01 */

/* The ECM PEG error (Detected in a read request from PE to the other LRAM) reset (PE1) Reset Reason Handles */
#define McuConf_McuRstRsnConfPegOtherLramreqPe1Rst_McuRstRsnConfPegOtherLramreqPe1Rst                                   /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0xBFU

/* The ECM Data Access Error reset (PE1) Reset Reason Handles */
#define McuConf_McuRstRsnConfDataAccessErrPe1Rst_McuRstRsnConfDataAccessErrPe1Rst                                       /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0xC0U

/* The ECM DCLS compare error reset (PE2) Reset Reason Handles */
#define McuConf_McuRstRsnConfDclsCompErrPe2Rst_McuRstRsnConfDclsCompErrPe2Rst   (Mcu_ResetType)0xC1U                    /* PRQA S 1534 # JV-01 */

#define McuConf_McuRstRsnConfDclsModeErrPe2Rst_McuRstRsnConfDclsModeErrPe2Rst   (Mcu_ResetType)0xC2U                    /* PRQA S 1534 # JV-01 */

#define McuConf_McuRstRsnConfUnintDisableEnableDetectionPe2Rst_McuRstRsnConfUnintDisableEnableDetectionPe2Rst           /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0xC3U

/* The ECM Unintended Debug Enable detection reset (PE2) Reset Reason Handles */
#define McuConf_McuRstRsnConfModeUnintDebugEnablePe2Rst_McuRstRsnConfModeUnintDebugEnablePe2Rst                         /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0xC4U

/* The ECM Watchdog timer error reset (PE2) Reset Reason Handles */
#define McuConf_McuRstRsnConfWdtErrPe2Rst_McuRstRsnConfWdtErrPe2Rst             (Mcu_ResetType)0xC5U                    /* PRQA S 1534 # JV-01 */

/* The ECM Clock monitor error reset for CLK_CPU (PE2) (CLMA8) Reset Reason Handles */
#define McuConf_McuRstRsnConfClmaErrPe2Rst_McuRstRsnConfClmaErrPe2Rst           (Mcu_ResetType)0xC6U                    /* PRQA S 1534 # JV-01 */

/* The ECM Local RAM Address feedback compare error or ECC 2bit error (PE2) Reset Reason Handles */
#define McuConf_McuRstRsnConfLramAdrOrEcc2ErrPe2Rst_McuRstRsnConfLramAdrOrEcc2ErrPe2Rst                                 /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0xC7U

/* The ECM Local RAM ECC 1bit error reset (PE2) Reset Reason Handles */
#define McuConf_McuRstRsnConfLramEcc1ErrPe2Rst_McuRstRsnConfLramEcc1ErrPe2Rst   (Mcu_ResetType)0xC8U                    /* PRQA S 1534 # JV-01 */

/* The ECM Local RAM ECC Error address overflow reset (PE2) Reset Reason Handles */
#define McuConf_McuRstRsnConfLramErradrOflowPe2Rst_McuRstRsnConfLramErradrOflowPe2Rst                                   /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0xC9U

/* The ECM Instruction Cache RAM Address feedback compare error, EDC 2bit error or EDC 1bit error reset (PE2) Reset   */
/*   Reason Handles                                                                                                   */
#define McuConf_McuRstRsnConfIcacheAdrOrEdcErrPe2Rst_McuRstRsnConfIcacheAdrOrEdcErrPe2Rst                               /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0xCAU

/* The ECM PEG error reset (PE2) Reset Reason Handles */
#define McuConf_McuRstRsnConfPeguardErrPe2Rst_McuRstRsnConfPeguardErrPe2Rst     (Mcu_ResetType)0xCBU                    /* PRQA S 1534 # JV-01 */

/* The ECM PEG error (Detected in a read request from PE to the other LRAM) reset (PE2) Reset Reason Handles */
#define McuConf_McuRstRsnConfPegOtherLramreqPe2Rst_McuRstRsnConfPegOtherLramreqPe2Rst                                   /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0xCCU

/* The ECM Data Access Error reset (PE2) Reset Reason Handles */
#define McuConf_McuRstRsnConfDataAccessErrPe2Rst_McuRstRsnConfDataAccessErrPe2Rst                                       /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0xCDU

/* The ECM DCLS compare error reset (PE3) Reset Reason Handles */
#define McuConf_McuRstRsnConfDclsCompErrPe3Rst_McuRstRsnConfDclsCompErrPe3Rst   (Mcu_ResetType)0xCEU                    /* PRQA S 1534 # JV-01 */

#define McuConf_McuRstRsnConfDclsModeErrPe3Rst_McuRstRsnConfDclsModeErrPe3Rst   (Mcu_ResetType)0xCFU                    /* PRQA S 1534 # JV-01 */

#define McuConf_McuRstRsnConfUnintDisableEnableDetectionPe3Rst_McuRstRsnConfUnintDisableEnableDetectionPe3Rst           /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0xD0U

/* The ECM Unintended Debug Enable detection reset (PE3) Reset Reason Handles */
#define McuConf_McuRstRsnConfModeUnintDebugEnablePe3Rst_McuRstRsnConfModeUnintDebugEnablePe3Rst                         /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0xD1U

/* The ECM Watchdog timer error reset (PE3) Reset Reason Handles */
#define McuConf_McuRstRsnConfWdtErrPe3Rst_McuRstRsnConfWdtErrPe3Rst             (Mcu_ResetType)0xD2U                    /* PRQA S 1534 # JV-01 */

/* The ECM Clock monitor error reset for CLK_CPU (PE3) (CLMA9) Reset Reason Handles */
#define McuConf_McuRstRsnConfClmaErrPe3Rst_McuRstRsnConfClmaErrPe3Rst           (Mcu_ResetType)0xD3U                    /* PRQA S 1534 # JV-01 */

/* The ECM Local RAM Address feedback compare error or ECC 2bit error (PE3) Reset Reason Handles */
#define McuConf_McuRstRsnConfLramAdrOrEcc2ErrPe3Rst_McuRstRsnConfLramAdrOrEcc2ErrPe3Rst                                 /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0xD4U

/* The ECM Local RAM ECC 1bit error reset (PE3) Reset Reason Handles */
#define McuConf_McuRstRsnConfLramEcc1ErrPe3Rst_McuRstRsnConfLramEcc1ErrPe3Rst   (Mcu_ResetType)0xD5U                    /* PRQA S 1534 # JV-01 */

/* The ECM Local RAM ECC Error address overflow reset (PE3) Reset Reason Handles */
#define McuConf_McuRstRsnConfLramErradrOflowPe3Rst_McuRstRsnConfLramErradrOflowPe3Rst                                   /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0xD6U

/* The ECM Instruction Cache RAM Address feedback compare error, EDC 2bit error or EDC 1bit error reset (PE3) Reset   */
/*   Reason Handles                                                                                                   */
#define McuConf_McuRstRsnConfIcacheAdrOrEdcErrPe3Rst_McuRstRsnConfIcacheAdrOrEdcErrPe3Rst                               /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0xD7U

/* The ECM PEG error reset (PE3) Reset Reason Handles */
#define McuConf_McuRstRsnConfPeguardErrPe3Rst_McuRstRsnConfPeguardErrPe3Rst     (Mcu_ResetType)0xD8U                    /* PRQA S 1534 # JV-01 */

/* The ECM PEG error (Detected in a read request from PE to the other LRAM) reset (PE3) Reset Reason Handles */
#define McuConf_McuRstRsnConfPegOtherLramreqPe3Rst_McuRstRsnConfPegOtherLramreqPe3Rst                                   /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0xD9U

/* The ECM Data Access Error reset (PE3) Reset Reason Handles */
#define McuConf_McuRstRsnConfDataAccessErrPe3Rst_McuRstRsnConfDataAccessErrPe3Rst                                       /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0xDAU

/* The DCLS compare error (PE4) Reset Reason Handles */
#define McuConf_McuRstRsnConfDclsCompErrPe4Rst_McuRstRsnConfDclsCompErrPe4Rst   (Mcu_ResetType)0xDBU                    /* PRQA S 1534 # JV-01 */

#define McuConf_McuRstRsnConfDclsModeErrPe4Rst_McuRstRsnConfDclsModeErrPe4Rst   (Mcu_ResetType)0xDCU                    /* PRQA S 1534 # JV-01 */

#define McuConf_McuRstRsnConfUnintDisableEnableDetectionPe4Rst_McuRstRsnConfUnintDisableEnableDetectionPe4Rst           /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0xDDU

#define McuConf_McuRstRsnConfModeUnintDebugEnablePe4Rst_McuRstRsnConfModeUnintDebugEnablePe4Rst                         /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0xDEU

#define McuConf_McuRstRsnConfWdtErrPe4Rst_McuRstRsnConfWdtErrPe4Rst             (Mcu_ResetType)0xDFU                    /* PRQA S 1534 # JV-01 */

#define McuConf_McuRstRsnConfClmaErrPe4Rst_McuRstRsnConfClmaErrPe4Rst           (Mcu_ResetType)0xE0U                    /* PRQA S 1534 # JV-01 */

#define McuConf_McuRstRsnConfLramAdrOrEcc2ErrPe4Rst_McuRstRsnConfLramAdrOrEcc2ErrPe4Rst                                 /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0xE1U

#define McuConf_McuRstRsnConfLramEcc1ErrPe4Rst_McuRstRsnConfLramEcc1ErrPe4Rst   (Mcu_ResetType)0xE2U                    /* PRQA S 1534 # JV-01 */

/* The Local RAM Error address overflow (PE4) Reset Reason Handles */
#define McuConf_McuRstRsnConfLramErradrOflowPe4Rst_McuRstRsnConfLramErradrOflowPe4Rst                                   /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0xE3U

#define McuConf_McuRstRsnConfIcacheAdrOrEdcErrPe4Rst_McuRstRsnConfIcacheAdrOrEdcErrPe4Rst                               /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0xE4U

/* The PEG error (PE4) Reset Reason Handles */
#define McuConf_McuRstRsnConfPeguardErrPe4Rst_McuRstRsnConfPeguardErrPe4Rst     (Mcu_ResetType)0xE5U                    /* PRQA S 1534 # JV-01 */

/* The PEG error (PE4) Detected in a read request from PE4 to the others LRAM Reset Reason Handles */
#define McuConf_McuRstRsnConfPegOtherLramreqPe4Rst_McuRstRsnConfPegOtherLramreqPe4Rst                                   /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0xE6U

#define McuConf_McuRstRsnConfDataAccessErrPe4Rst_McuRstRsnConfDataAccessErrPe4Rst                                       /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0xE7U

#define McuConf_McuRstRsnConfUnintDisableEnableDetectionPe5Rst_McuRstRsnConfUnintDisableEnableDetectionPe5Rst           /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0xE8U

#define McuConf_McuRstRsnConfModeUnintDebugEnablePe5Rst_McuRstRsnConfModeUnintDebugEnablePe5Rst                         /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0xE9U

#define McuConf_McuRstRsnConfWdtErrPe5Rst_McuRstRsnConfWdtErrPe5Rst             (Mcu_ResetType)0xEAU                    /* PRQA S 1534 # JV-01 */

#define McuConf_McuRstRsnConfLramAdrOrEcc2ErrPe5Rst_McuRstRsnConfLramAdrOrEcc2ErrPe5Rst                                 /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0xEBU

#define McuConf_McuRstRsnConfLramEcc1ErrPe5Rst_McuRstRsnConfLramEcc1ErrPe5Rst   (Mcu_ResetType)0xECU                    /* PRQA S 1534 # JV-01 */

/* The Local RAM Error address overflow (PE5) Reset Reason Handles */
#define McuConf_McuRstRsnConfLramErradrOflowPe5Rst_McuRstRsnConfLramErradrOflowPe5Rst                                   /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0xEDU

#define McuConf_McuRstRsnConfIcacheAdrOrEdcErrPe5Rst_McuRstRsnConfIcacheAdrOrEdcErrPe5Rst                               /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0xEEU

/* The PEG error (PE5) Reset Reason Handles */
#define McuConf_McuRstRsnConfPeguardErrPe5Rst_McuRstRsnConfPeguardErrPe5Rst     (Mcu_ResetType)0xEFU                    /* PRQA S 1534 # JV-01 */

/* The PEG error (PE5) Detected in a read request from PE5 to the others LRAM Reset Reason Handles */
#define McuConf_McuRstRsnConfPegOtherLramreqPe5Rst_McuRstRsnConfPegOtherLramreqPe5Rst                                   /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0xF0U

#define McuConf_McuRstRsnConfDataAccessErrPe5Rst_McuRstRsnConfDataAccessErrPe5Rst                                       /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0xF1U

#define McuConf_McuRstRsnConfDclsCompErrPe6Rst_McuRstRsnConfDclsCompErrPe6Rst   (Mcu_ResetType)0xF2U                    /* PRQA S 1534 # JV-01 */

#define McuConf_McuRstRsnConfDclsModeErrPe6Rst_McuRstRsnConfDclsModeErrPe6Rst   (Mcu_ResetType)0xF3U                    /* PRQA S 1534 # JV-01 */

#define McuConf_McuRstRsnConfUnintDisableEnableDetectionPe6Rst_McuRstRsnConfUnintDisableEnableDetectionPe6Rst           /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0xF4U

#define McuConf_McuRstRsnConfModeUnintDebugEnablePe6Rst_McuRstRsnConfModeUnintDebugEnablePe6Rst                         /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0xF5U

#define McuConf_McuRstRsnConfWdtErrPe6Rst_McuRstRsnConfWdtErrPe6Rst             (Mcu_ResetType)0xF6U                    /* PRQA S 1534 # JV-01 */

#define McuConf_McuRstRsnConfClmaErrPe6Rst_McuRstRsnConfClmaErrPe6Rst           (Mcu_ResetType)0xF7U                    /* PRQA S 1534 # JV-01 */

#define McuConf_McuRstRsnConfLramAdrOrEcc2ErrPe6Rst_McuRstRsnConfLramAdrOrEcc2ErrPe6Rst                                 /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0xF8U

#define McuConf_McuRstRsnConfLramEcc1ErrPe6Rst_McuRstRsnConfLramEcc1ErrPe6Rst   (Mcu_ResetType)0xF9U                    /* PRQA S 1534 # JV-01 */

#define McuConf_McuRstRsnConfLramErradrOflowPe6Rst_McuRstRsnConfLramErradrOflowPe6Rst                                   /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0xFAU

#define McuConf_McuRstRsnConfIcacheAdrOrEdcErrPe6Rst_McuRstRsnConfIcacheAdrOrEdcErrPe6Rst                               /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0xFBU

#define McuConf_McuRstRsnConfPeguardErrPe6Rst_McuRstRsnConfPeguardErrPe6Rst     (Mcu_ResetType)0xFCU                    /* PRQA S 1534 # JV-01 */

#define McuConf_McuRstRsnConfDataAccessErrPe6Rst_McuRstRsnConfDataAccessErrPe6Rst                                       /* PRQA S 1534 # JV-01 */ \
                                                                                (Mcu_ResetType)0xFDU

/* The Multi reset Reset Reason Handles */
#define McuConf_McuRstRsnConfMultiRst_McuRstRsnConfMultiRst                     (Mcu_ResetType)0xFEU                    /* PRQA S 1534 # JV-01 */

/* The Reset undefined Reset Reason Handles */
#define McuConf_McuRstRsnConfResetUndefined_McuRstRsnConfResetUndefined         (Mcu_ResetType)0xFFU                    /* PRQA S 1534 # JV-01 */

/* The Reset is not occurred Reset Reason Handles */
#define McuConf_McuRstRsnConfNonRst_McuRstRsnConfNonRst                         (Mcu_ResetType)0x100U                   /* PRQA S 1534 # JV-01 */

/* The Reset Reason Handles */
#define McuConf_McuResetReasonConf_McuResetReasonConf                           (Mcu_ResetType)0x00U                    /* PRQA S 1534 # JV-01 */

/* Maximum number of RAM Settings */
#define MCU_MAX_RAMSETTING                                                      (Mcu_RamSectionType)9                   /* PRQA S 1534 # JV-01 */

/* Mcu Vmon and Divider setting response time count */
#define MCU_VMON_WAIT_CNT_NUM                                                   0x0FA0                                  /* PRQA S 1534 # JV-01 */

/* Mcu Dmon and Divider setting response time count */
#define MCU_DMON_WAIT_CNT_NUM                                                   (uint32)0x00000640UL                    /* PRQA S 1534 # JV-01 */

/* Maximum number of Mode Settings */
#define MCU_CONFIGURED_MODE_SETTING_NUM                                         (uint8)3                                /* PRQA S 1534 # JV-01 */

/* Pre-compile option for MCU_CLOCK_REFLECT_WAIT_CNT_NUM */
#define MCU_CLOCK_REFLECT_WAIT_CNT_NUM                                          0x43                                    /* PRQA S 1534 # JV-01 */

/* Pre-compile option for MCU_VMON_FILTER_WAIT_CNT_NUM */
#define MCU_VMON_FILTER_WAIT_CNT_NUM                                            0xABE0U                                 /* PRQA S 1534 # JV-01 */

#define MCU_CKSC_PLLO                                                           (uint32)0x00000000UL                    /* PRQA S 1534 # JV-01 */

#define MCU_CKSC_MASK                                                           (uint32)0x00000001UL                    /* PRQA S 1534 # JV-01 */

#define MCU_CKDC_MASK                                                           (uint32)0x0000000FUL                    /* PRQA S 1534 # JV-01 */

#define MCU_CKDC_DIV1                                                           (uint32)0x00000000UL                    /* PRQA S 1534 # JV-01 */

#define MCU_PLLS_CLK_STABLE                                                     (uint32)0x00000003UL                    /* PRQA S 1534 # JV-01 */

#define MCU_PLLS_READ_COUNT                                                     (uint32)0x00000000UL                    /* PRQA S 1534 # JV-01 */

#define MCU_MOSCS_CLK_STABLE                                                    (uint32)0x00000003UL                    /* PRQA S 1534 # JV-01 */

#define MCU_MOSCS_CONFIRMATION                                                  (uint32)0x00000000UL                    /* PRQA S 1534 # JV-01 */

#define MCU_HSOSC_MAX_FREQUENCY_VALUE                                           (uint32)0x000000CAUL                    /* PRQA S 1534 # JV-01 */

#define MCU_HSOSC_MIN_FREQUENCY_VALUE                                           (uint32)0x000000C6UL                    /* PRQA S 1534 # JV-01 */

#define MCU_NUMBER_CLOCK_GEAR_UP_REPETITION                                     (uint8)0x07U                            /* PRQA S 1534 # JV-01 */

#define MCU_NUMBER_CLOCK_GEAR_DOWN_REPETITION                                   (uint8)0x06U                            /* PRQA S 1534 # JV-01 */

#define MCU_TOTAL_CMU_CONFIG                                                    (uint8)0x12U                            /* PRQA S 1534 # JV-01 */

#define MCU_CMUCLKEN_ENABLE_REG_TRIGGER                                         (uint32)0x00AAAAAAUL                    /* PRQA S 1534 # JV-01 */

#define MCU_CMUCLKEN_DISABLE_REG_TRIGGER                                        (uint32)0x00555555UL                    /* PRQA S 1534 # JV-01 */

#define MCU_CMUCLKEN_ENABLE_VALUE                                               (uint32)0x00FFFFFFUL                    /* PRQA S 1534 # JV-01 */

#define MCU_CMUCLKEN_MASK                                                       (uint32)0x00FFFFFFUL                    /* PRQA S 1534 # JV-01 */

#define MCU_VMON_VMONF_BIT_MASK                                                 (uint8)0xFFU                            /* PRQA S 1534 # JV-01 */

#define MCU_VMON_VMONF_DIAG_DEFAULT_VALUE                                       (uint8)0x00U                            /* PRQA S 1534 # JV-01 */

#define MCU_VMON_VMONFC_ALL_CLEAR_VALUE                                         (uint8)0xFFU                            /* PRQA S 1534 # JV-01 */

#define MCU_VMON_VMONDMASK_ALL_MASK_VALUE                                       (uint8)0xFFU                            /* PRQA S 1534 # JV-01 */

#define MCU_VMON_VMONDIAG_ALL_DETECTION_ENABLE_VALUE                            (uint8)0xFFU                            /* PRQA S 1534 # JV-01 */

#define MCU_VMON_ISOVDDDE_LOWVOLTAGE_DETECTION_ENABLE                           (uint8)0x01U                            /* PRQA S 1534 # JV-01 */

#define MCU_ISOVDDCIRREN_LOW_DETECTION_ID111                                    (uint8)0xE0U                            /* PRQA S 1534 # JV-01 */

#define MCU_ISOVDDCIRREN_LOW_DETECTION_ID110                                    (uint8)0xC0U                            /* PRQA S 1534 # JV-01 */

#define MCU_ISOVDDCIRREN_BIT_MASK                                               (uint8)0xE0U                            /* PRQA S 1534 # JV-01 */

#define MCU_OPBT4_NUMBER_BIT_CHECK                                              (uint8)0x08U                            /* PRQA S 1534 # JV-01 */

#define MCU_POWER_ON_RESET_BIT                                                  (uint32)0x00000001UL                    /* PRQA S 1534 # JV-01 */

#define MCU_STANDBY_RESET_BIT                                                   (uint32)0x00000002UL                    /* PRQA S 1534 # JV-01 */

#define MCU_EXTERNAL_RESET_BIT                                                  (uint32)0x00000004UL                    /* PRQA S 1534 # JV-01 */

#define MCU_RESC_SET_VALUE                                                      (uint32)0x00000001UL                    /* PRQA S 1534 # JV-01 */

#define MCU_ECM_CORE_NUM                                                        (uint8)0x07U                            /* PRQA S 1534 # JV-01 */

#define MCU_ECM_SETTING_NUM                                                     (uint8)0x03U                            /* PRQA S 1534 # JV-01 */

#define MCU_ECM_COMMON_REG_NUM                                                  (uint8)0x0EU                            /* PRQA S 1534 # JV-01 */

#define MCU_ECM_ERROR_TRIGGER_NUM                                               (uint8)0x07U                            /* PRQA S 1534 # JV-01 */

#define MCU_ECM_DTM_DELAYTIMER_STARTED                                          (uint32)0x01000000UL                    /* PRQA S 1534 # JV-01 */

#define MCU_ECM_DTM_DELAYTIMER_STATUS_MASK                                      (uint32)0x01000000UL                    /* PRQA S 1534 # JV-01 */

#define MCU_ECM_EOCCFG_COUNTER_UPDATING                                         (uint32)0x01000000UL                    /* PRQA S 1534 # JV-01 */

#define MCU_ECM_EOCCFG_COUNTER_CMPW_MASK                                        (uint32)0x01000000UL                    /* PRQA S 1534 # JV-01 */

#define MCU_ECM_ECMEMK0_MASK                                                    (uint32)0xFFF00800UL                    /* PRQA S 1534 # JV-01 */

#define MCU_ECM_ERROROUT_CLEAR_NUM                                              (uint8)0x07U                            /* PRQA S 1534 # JV-01 */

#define MCU_ECM_ESSTR_ERROUT_MASK                                               (uint32)0x00000001UL                    /* PRQA S 1534 # JV-01 */

#define MCU_ECM_COMMON_REG_NUM_EIC9                                             (uint8)0x0EU                            /* PRQA S 1534 # JV-01 */

#define MCU_ECM_EIC9_REG_NUM                                                    (uint8)0x20U                            /* PRQA S 1534 # JV-01 */

#define MCU_ECM_EIC9_UNIT_NUM                                                   (uint8)0x01U                            /* PRQA S 1534 # JV-01 */

#define MCU_ECM_COMMON_REG_LOOP_NUM                                             (uint8)0x11U                            /* PRQA S 1534 # JV-01 */

#define MCU_ECM_STATUS_REG_SIZE                                                 (uint8)0x20U                            /* PRQA S 1534 # JV-01 */

#define MCU_ECM_STATUS_REG_DIV                                                  (uint8)0x01U                            /* PRQA S 1534 # JV-01 */

#define MCU_ECM_ESSTR_DCLS_MASK                                                 (uint32)0x00000000UL                    /* PRQA S 1534 # JV-01 */

#define MCU_ECM_ESSTR_MASK                                                      (uint32)0xFFFFFFFFUL                    /* PRQA S 1534 # JV-01 */

#define MCU_ECM_DCLS_ERROR_FACTOR_MASK                                          (uint32)0x00000001UL                    /* PRQA S 1534 # JV-01 */

#define MCU_ECM_EIC8_ESSTR_OFFSET                                               (uint32)0x00000000UL                    /* PRQA S 1534 # JV-01 */

#define MCU_ECM_EIC8_ESSTR_START_NUM                                            (uint8)0x00U                            /* PRQA S 1534 # JV-01 */

#define MCU_RESF_CLEAR                                                          (uint32)0x0000F5DFUL                    /* PRQA S 1534 # JV-01 */

#define MCU_CLMxTESEN_BIT                                                       (uint32)0x001FBFF8UL                    /* PRQA S 1534 # JV-01 */

#define MCU_FOUTDIVS_STOPPED                                                    (uint32)0x00000001UL                    /* PRQA S 1534 # JV-01 */

#define MCU_CLKD_SYNCMASK                                                       (uint32)0x00000001UL                    /* PRQA S 1534 # JV-01 */


/***********************************************************************************************************************
**                      Global Data                                                                                   **
***********************************************************************************************************************/



/***********************************************************************************************************************
**                      Function Prototypes                                                                           **
***********************************************************************************************************************/



#endif /* MCU_CFG_H */


/***********************************************************************************************************************
**                      End of File                                                                                   **
***********************************************************************************************************************/

