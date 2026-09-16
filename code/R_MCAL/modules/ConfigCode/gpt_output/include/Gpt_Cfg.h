/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Gpt_Cfg.h                                                                                           */
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
/* TOOL VERSION:  GptU2Bx-E.dll version: 2.4.1, MCALConfGen.exe version: 2.3.0                                        */
/*                                                                                                                    */


/***********************************************************************************************************************
**                      Input File                                                                                    **
***********************************************************************************************************************/
/*
 * INPUT FILE:    C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\MCAL_RH850U2B24E_516_CodeGen\U2B24-E.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\modules\gpt\generator\U2B24-E\R2211_gpt_U2B24-E_BSWMDT.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\Dem\xml\Dem_gpt.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\EcuM\xml\EcuM_gpt.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\Os\xml\Os_gpt.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\EcuC\xml\EcuC_gpt.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\MCAL_RH850U2B24E_516_CodeGen\Translation.trxml
 * GENERATED ON:  13 Jul 2026 - 15:38:56
 */


#ifndef GPT_CFG_H
#define GPT_CFG_H


/***********************************************************************************************************************
**                      Include Section                                                                               **
***********************************************************************************************************************/
#include "Gpt_Cbk.h"


/***********************************************************************************************************************
**                      Coding Rule Violations                                                                        **
***********************************************************************************************************************/



/***********************************************************************************************************************
**                      Version Information                                                                           **
***********************************************************************************************************************/
#define GPT_CFG_AR_RELEASE_MAJOR_VERSION                                        4U
#define GPT_CFG_AR_RELEASE_MINOR_VERSION                                        8U
#define GPT_CFG_AR_RELEASE_REVISION_VERSION                                     0U
#define GPT_CFG_SW_MAJOR_VERSION                                                2U
#define GPT_CFG_SW_MINOR_VERSION                                                4U
#define GPT_AR_RELEASE_MAJOR_VERSION_VALUE                                      4U
#define GPT_AR_RELEASE_MINOR_VERSION_VALUE                                      8U
#define GPT_AR_RELEASE_REVISION_VERSION_VALUE                                   0U
#define GPT_SW_MAJOR_VERSION_VALUE                                              2U
#define GPT_SW_MINOR_VERSION_VALUE                                              4U
#define GPT_SW_PATCH_VERSION_VALUE                                              1U
#define GPT_VENDOR_ID_VALUE                                                     59U
#define GPT_MODULE_ID_VALUE                                                     100U
#define GPT_CFG_C_AR_RELEASE_MAJOR_VERSION                                      4U
#define GPT_CFG_C_AR_RELEASE_MINOR_VERSION                                      8U
#define GPT_CFG_C_AR_RELEASE_REVISION_VERSION                                   0U
#define GPT_CFG_C_SW_MAJOR_VERSION                                              2U
#define GPT_CFG_C_SW_MINOR_VERSION                                              4U
#define GPT_AR_VERSION                                                          GPT_AR_R22_11_VERSION

/***********************************************************************************************************************
**                      Global Symbols                                                                                **
***********************************************************************************************************************/
/* Supported version for GTM HWIP */
#define GPT_GTM_VERSION                                                         GPT_GTM_410_VERSION

/* Instance ID of the Gpt Component */
#define GPT_INSTANCE_ID_VALUE                                                   0U

/* Enable/Disable the timer ATU IP */
#define GPT_TIMER_IP_ATU                                                        STD_OFF

/* Enable/Disable the OSTM unit */
#define GPT_TIMER_IP_OSTM                                                       STD_ON

/* Enable/Disable the TAUD unit */
#define GPT_TIMER_IP_TAUD                                                       STD_OFF

/* Enable/Disable the TAUJ unit */
#define GPT_TIMER_IP_TAUJ                                                       STD_ON

/* The number of HWIP configured STD_ON */
#define GPT_TOTAL_HW_IP_CONFIG                                                  2

/* Total number of GPT Channels configured */
#define GPT_TOTAL_CHANNELS_CONFIG                                               1U

/* Maximum GPT Channel ID configured */
#define GPT_MAX_CHANNEL_ID_CONFIGURED                                           0U

/* Enables/Disables inclusion of Gpt_SetMode, Gpt_EnableWakeup and Gpt_DisableWakeup */
#define GPT_WAKEUP_FUNCTIONALITY_API                                            STD_ON

/* Enable/Disable GptIsrCategory */
#define GPT_ISR_CATEGORY_2                                                      STD_OFF


/* Total number of GPT Channels PreDef Configured */
#define GPT_TOTAL_PREDEF_CHANNELS_CONFIG                                        1U

/* The number of total configured cores */
#define GPT_NUM_CONFIGURED_CORE                                                 1U

/* Total number of GPT TAUD and TAUJ units configured */
#define GPT_TOTAL_TAU_UNITS_CONFIGURED                                          1U

/* Enable/disable the setting of Prescaler and blConfigurePrescaler by the */
#define GPT_TAUD_CONFIG_PRESCALER_SUPPORTED                                     STD_OFF

/* Enable/disable the setting of Prescaler and blConfigurePrescaler by the */
#define GPT_TAUJ_CONFIG_PRESCALER_SUPPORTED                                     STD_ON

/* Enable/Disable TAUD3 interrupt number selection. */
#define GPT_TAUD3_UNIT_USED                                                     STD_OFF

/* Enable/Disable the GTM-IP depending on the TOM/ATOM channels configured */
#define GPT_TIMER_IP_GTM                                                        STD_OFF

/* Enable/Disable the ATOM unit depending on the ATOM channels configured */
#define GPT_ATOM_UNIT_USED                                                      STD_OFF

/* Enable/Disable the TOM unit depending on the TOM channels configured */
#define GPT_TOM_UNIT_USED                                                       STD_OFF

/* Number of Cluster that used for channel configuration */
#define GPT_TOTAL_GTM_UNITS_CONFIG                                              0

/* Enables/Disables the inclusion of Gpt_DeInit API */
#define GPT_DE_INIT_API                                                         STD_ON

/* Enables/Disables inclusion of Gpt_GetTimeElapsed API */
#define GPT_TIME_ELAPSED_API                                                    STD_ON

/* Enables/Disables inclusion of GptTimeRemaining Api */
#define GPT_TIME_REMAINING_API                                                  STD_ON

/* Enables/Disables inclusion of GptVersionInfoApi */
#define GPT_VERSION_INFO_API                                                    STD_ON

/* Enables/Disables inclusion of GptEnableDisableNotificationApi */
#define GPT_ENABLE_DISABLE_NOTIFICATION_API                                     STD_ON

/* Enables/Disables Predef Timer function */
#define GPT_GET_PREDEF_TIMER_VALUE_API                                          STD_ON

/* Enables/Disables Development error detection */
#define GPT_DEV_ERROR_DETECT                                                    STD_OFF

/* Enable/Disable Report Wakeup Source */
#define GPT_REPORT_WAKEUP_SOURCE                                                STD_ON

/* Enable/Disable critical section */
#define GPT_CRITICAL_SECTION_PROTECTION                                         STD_ON

/* Enable/Disable clear pending interrupt */
#define GPT_CLEAR_PENDING_INTERRUPT                                             STD_ON

/* Enable/Disable already init DET check */
#define GPT_ALREADY_INIT_DET_CHECK                                              STD_ON

/* Enable/Disable version check external modules */
#define GPT_VERSION_CHECK_EXT_MODULES                                           STD_ON

/* Enable/Disable Interrupt consistency */
#define GPT_INTERRUPT_CONSISTENCY_CHECK                                         STD_OFF

/* Enable/Disable multi-core usage */
#define GPT_MULTI_CORE_SUPPORT                                                  STD_OFF

/* Macros for enabling/disabling ISRS */
#define GPT_OSTM00_CH0_ISR_API                                                  STD_ON
#define GPT_OSTM01_CH0_ISR_API                                                  STD_OFF
#define GPT_OSTM02_CH0_ISR_API                                                  STD_OFF
#define GPT_OSTM03_CH0_ISR_API                                                  STD_OFF
#define GPT_OSTM04_CH0_ISR_API                                                  STD_OFF
#define GPT_OSTM05_CH0_ISR_API                                                  STD_OFF
#define GPT_OSTM06_CH0_ISR_API                                                  STD_OFF
#define GPT_OSTM07_CH0_ISR_API                                                  STD_OFF
#define GPT_OSTM08_CH0_ISR_API                                                  STD_OFF
#define GPT_OSTM09_CH0_ISR_API                                                  STD_OFF
#define GPT_TAUD0_CH00_ISR_API                                                  STD_OFF
#define GPT_TAUD0_CH01_ISR_API                                                  STD_OFF
#define GPT_TAUD0_CH02_ISR_API                                                  STD_OFF
#define GPT_TAUD0_CH03_ISR_API                                                  STD_OFF
#define GPT_TAUD0_CH04_ISR_API                                                  STD_OFF
#define GPT_TAUD0_CH05_ISR_API                                                  STD_OFF
#define GPT_TAUD0_CH06_ISR_API                                                  STD_OFF
#define GPT_TAUD0_CH07_ISR_API                                                  STD_OFF
#define GPT_TAUD0_CH08_ISR_API                                                  STD_OFF
#define GPT_TAUD0_CH09_ISR_API                                                  STD_OFF
#define GPT_TAUD0_CH10_ISR_API                                                  STD_OFF
#define GPT_TAUD0_CH11_ISR_API                                                  STD_OFF
#define GPT_TAUD0_CH12_ISR_API                                                  STD_OFF
#define GPT_TAUD0_CH13_ISR_API                                                  STD_OFF
#define GPT_TAUD0_CH14_ISR_API                                                  STD_OFF
#define GPT_TAUD0_CH15_ISR_API                                                  STD_OFF
#define GPT_TAUD1_CH00_ISR_API                                                  STD_OFF
#define GPT_TAUD1_CH01_ISR_API                                                  STD_OFF
#define GPT_TAUD1_CH02_ISR_API                                                  STD_OFF
#define GPT_TAUD1_CH03_ISR_API                                                  STD_OFF
#define GPT_TAUD1_CH04_ISR_API                                                  STD_OFF
#define GPT_TAUD1_CH05_ISR_API                                                  STD_OFF
#define GPT_TAUD1_CH06_ISR_API                                                  STD_OFF
#define GPT_TAUD1_CH07_ISR_API                                                  STD_OFF
#define GPT_TAUD1_CH08_ISR_API                                                  STD_OFF
#define GPT_TAUD1_CH09_ISR_API                                                  STD_OFF
#define GPT_TAUD1_CH10_ISR_API                                                  STD_OFF
#define GPT_TAUD1_CH11_ISR_API                                                  STD_OFF
#define GPT_TAUD1_CH12_ISR_API                                                  STD_OFF
#define GPT_TAUD1_CH13_ISR_API                                                  STD_OFF
#define GPT_TAUD1_CH14_ISR_API                                                  STD_OFF
#define GPT_TAUD1_CH15_ISR_API                                                  STD_OFF
#define GPT_TAUD2_CH00_ISR_API                                                  STD_OFF
#define GPT_TAUD2_CH01_ISR_API                                                  STD_OFF
#define GPT_TAUD2_CH02_ISR_API                                                  STD_OFF
#define GPT_TAUD2_CH03_ISR_API                                                  STD_OFF
#define GPT_TAUD2_CH04_ISR_API                                                  STD_OFF
#define GPT_TAUD2_CH05_ISR_API                                                  STD_OFF
#define GPT_TAUD2_CH06_ISR_API                                                  STD_OFF
#define GPT_TAUD2_CH07_ISR_API                                                  STD_OFF
#define GPT_TAUD2_CH08_ISR_API                                                  STD_OFF
#define GPT_TAUD2_CH09_ISR_API                                                  STD_OFF
#define GPT_TAUD2_CH10_ISR_API                                                  STD_OFF
#define GPT_TAUD2_CH11_ISR_API                                                  STD_OFF
#define GPT_TAUD2_CH12_ISR_API                                                  STD_OFF
#define GPT_TAUD2_CH13_ISR_API                                                  STD_OFF
#define GPT_TAUD2_CH14_ISR_API                                                  STD_OFF
#define GPT_TAUD2_CH15_ISR_API                                                  STD_OFF
#define GPT_TAUD3_CH00_ISR_API                                                  STD_OFF
#define GPT_TAUD3_CH01_ISR_API                                                  STD_OFF
#define GPT_TAUD3_CH02_ISR_API                                                  STD_OFF
#define GPT_TAUD3_CH03_ISR_API                                                  STD_OFF
#define GPT_TAUD3_CH04_ISR_API                                                  STD_OFF
#define GPT_TAUD3_CH05_ISR_API                                                  STD_OFF
#define GPT_TAUD3_CH06_ISR_API                                                  STD_OFF
#define GPT_TAUD3_CH07_ISR_API                                                  STD_OFF
#define GPT_TAUD3_CH08_ISR_API                                                  STD_OFF
#define GPT_TAUD3_CH09_ISR_API                                                  STD_OFF
#define GPT_TAUD3_CH10_ISR_API                                                  STD_OFF
#define GPT_TAUD3_CH11_ISR_API                                                  STD_OFF
#define GPT_TAUD3_CH12_ISR_API                                                  STD_OFF
#define GPT_TAUD3_CH13_ISR_API                                                  STD_OFF
#define GPT_TAUD3_CH14_ISR_API                                                  STD_OFF
#define GPT_TAUD3_CH15_ISR_API                                                  STD_OFF
#define GPT_TAUJ0_CH00_ISR_API                                                  STD_OFF
#define GPT_TAUJ0_CH01_ISR_API                                                  STD_OFF
#define GPT_TAUJ0_CH02_ISR_API                                                  STD_OFF
#define GPT_TAUJ0_CH03_ISR_API                                                  STD_OFF
#define GPT_TAUJ1_CH00_ISR_API                                                  STD_OFF
#define GPT_TAUJ1_CH01_ISR_API                                                  STD_OFF
#define GPT_TAUJ1_CH02_ISR_API                                                  STD_OFF
#define GPT_TAUJ1_CH03_ISR_API                                                  STD_OFF
#define GPT_TAUJ2_CH00_ISR_API                                                  STD_OFF
#define GPT_TAUJ2_CH01_ISR_API                                                  STD_OFF
#define GPT_TAUJ2_CH02_ISR_API                                                  STD_OFF
#define GPT_TAUJ2_CH03_ISR_API                                                  STD_OFF
#define GPT_TAUJ3_CH00_ISR_API                                                  STD_OFF
#define GPT_TAUJ3_CH01_ISR_API                                                  STD_OFF
#define GPT_TAUJ3_CH02_ISR_API                                                  STD_OFF
#define GPT_TAUJ3_CH03_ISR_API                                                  STD_OFF
#define GPT_TOM0_CH00_ISR_API                                                   STD_OFF
#define GPT_TOM0_CH01_ISR_API                                                   STD_OFF
#define GPT_TOM0_CH02_ISR_API                                                   STD_OFF
#define GPT_TOM0_CH03_ISR_API                                                   STD_OFF
#define GPT_TOM0_CH04_ISR_API                                                   STD_OFF
#define GPT_TOM0_CH05_ISR_API                                                   STD_OFF
#define GPT_TOM0_CH06_ISR_API                                                   STD_OFF
#define GPT_TOM0_CH07_ISR_API                                                   STD_OFF
#define GPT_TOM0_CH08_ISR_API                                                   STD_OFF
#define GPT_TOM0_CH09_ISR_API                                                   STD_OFF
#define GPT_TOM0_CH10_ISR_API                                                   STD_OFF
#define GPT_TOM0_CH11_ISR_API                                                   STD_OFF
#define GPT_TOM0_CH12_ISR_API                                                   STD_OFF
#define GPT_TOM0_CH13_ISR_API                                                   STD_OFF
#define GPT_TOM0_CH14_ISR_API                                                   STD_OFF
#define GPT_TOM0_CH15_ISR_API                                                   STD_OFF
#define GPT_TOM1_CH00_ISR_API                                                   STD_OFF
#define GPT_TOM1_CH01_ISR_API                                                   STD_OFF
#define GPT_TOM1_CH02_ISR_API                                                   STD_OFF
#define GPT_TOM1_CH03_ISR_API                                                   STD_OFF
#define GPT_TOM1_CH04_ISR_API                                                   STD_OFF
#define GPT_TOM1_CH05_ISR_API                                                   STD_OFF
#define GPT_TOM1_CH06_ISR_API                                                   STD_OFF
#define GPT_TOM1_CH07_ISR_API                                                   STD_OFF
#define GPT_TOM1_CH08_ISR_API                                                   STD_OFF
#define GPT_TOM1_CH09_ISR_API                                                   STD_OFF
#define GPT_TOM1_CH10_ISR_API                                                   STD_OFF
#define GPT_TOM1_CH11_ISR_API                                                   STD_OFF
#define GPT_TOM1_CH12_ISR_API                                                   STD_OFF
#define GPT_TOM1_CH13_ISR_API                                                   STD_OFF
#define GPT_TOM1_CH14_ISR_API                                                   STD_OFF
#define GPT_TOM1_CH15_ISR_API                                                   STD_OFF
#define GPT_TOM2_CH00_ISR_API                                                   STD_OFF
#define GPT_TOM2_CH01_ISR_API                                                   STD_OFF
#define GPT_TOM2_CH02_ISR_API                                                   STD_OFF
#define GPT_TOM2_CH03_ISR_API                                                   STD_OFF
#define GPT_TOM2_CH04_ISR_API                                                   STD_OFF
#define GPT_TOM2_CH05_ISR_API                                                   STD_OFF
#define GPT_TOM2_CH06_ISR_API                                                   STD_OFF
#define GPT_TOM2_CH07_ISR_API                                                   STD_OFF
#define GPT_TOM2_CH08_ISR_API                                                   STD_OFF
#define GPT_TOM2_CH09_ISR_API                                                   STD_OFF
#define GPT_TOM2_CH10_ISR_API                                                   STD_OFF
#define GPT_TOM2_CH11_ISR_API                                                   STD_OFF
#define GPT_TOM2_CH12_ISR_API                                                   STD_OFF
#define GPT_TOM2_CH13_ISR_API                                                   STD_OFF
#define GPT_TOM2_CH14_ISR_API                                                   STD_OFF
#define GPT_TOM2_CH15_ISR_API                                                   STD_OFF
#define GPT_TOM3_CH00_ISR_API                                                   STD_OFF
#define GPT_TOM3_CH01_ISR_API                                                   STD_OFF
#define GPT_TOM3_CH02_ISR_API                                                   STD_OFF
#define GPT_TOM3_CH03_ISR_API                                                   STD_OFF
#define GPT_TOM3_CH04_ISR_API                                                   STD_OFF
#define GPT_TOM3_CH05_ISR_API                                                   STD_OFF
#define GPT_TOM3_CH06_ISR_API                                                   STD_OFF
#define GPT_TOM3_CH07_ISR_API                                                   STD_OFF
#define GPT_TOM3_CH08_ISR_API                                                   STD_OFF
#define GPT_TOM3_CH09_ISR_API                                                   STD_OFF
#define GPT_TOM3_CH10_ISR_API                                                   STD_OFF
#define GPT_TOM3_CH11_ISR_API                                                   STD_OFF
#define GPT_TOM3_CH12_ISR_API                                                   STD_OFF
#define GPT_TOM3_CH13_ISR_API                                                   STD_OFF
#define GPT_TOM3_CH14_ISR_API                                                   STD_OFF
#define GPT_TOM3_CH15_ISR_API                                                   STD_OFF
#define GPT_TOM4_CH00_ISR_API                                                   STD_OFF
#define GPT_TOM4_CH01_ISR_API                                                   STD_OFF
#define GPT_TOM4_CH02_ISR_API                                                   STD_OFF
#define GPT_TOM4_CH03_ISR_API                                                   STD_OFF
#define GPT_TOM4_CH04_ISR_API                                                   STD_OFF
#define GPT_TOM4_CH05_ISR_API                                                   STD_OFF
#define GPT_TOM4_CH06_ISR_API                                                   STD_OFF
#define GPT_TOM4_CH07_ISR_API                                                   STD_OFF
#define GPT_TOM4_CH08_ISR_API                                                   STD_OFF
#define GPT_TOM4_CH09_ISR_API                                                   STD_OFF
#define GPT_TOM4_CH10_ISR_API                                                   STD_OFF
#define GPT_TOM4_CH11_ISR_API                                                   STD_OFF
#define GPT_TOM4_CH12_ISR_API                                                   STD_OFF
#define GPT_TOM4_CH13_ISR_API                                                   STD_OFF
#define GPT_TOM4_CH14_ISR_API                                                   STD_OFF
#define GPT_TOM4_CH15_ISR_API                                                   STD_OFF
#define GPT_ATOM0_CH00_ISR_API                                                  STD_OFF
#define GPT_ATOM0_CH01_ISR_API                                                  STD_OFF
#define GPT_ATOM0_CH02_ISR_API                                                  STD_OFF
#define GPT_ATOM0_CH03_ISR_API                                                  STD_OFF
#define GPT_ATOM0_CH04_ISR_API                                                  STD_OFF
#define GPT_ATOM0_CH05_ISR_API                                                  STD_OFF
#define GPT_ATOM0_CH06_ISR_API                                                  STD_OFF
#define GPT_ATOM0_CH07_ISR_API                                                  STD_OFF
#define GPT_ATOM1_CH00_ISR_API                                                  STD_OFF
#define GPT_ATOM1_CH01_ISR_API                                                  STD_OFF
#define GPT_ATOM1_CH02_ISR_API                                                  STD_OFF
#define GPT_ATOM1_CH03_ISR_API                                                  STD_OFF
#define GPT_ATOM1_CH04_ISR_API                                                  STD_OFF
#define GPT_ATOM1_CH05_ISR_API                                                  STD_OFF
#define GPT_ATOM1_CH06_ISR_API                                                  STD_OFF
#define GPT_ATOM1_CH07_ISR_API                                                  STD_OFF
#define GPT_ATOM2_CH00_ISR_API                                                  STD_OFF
#define GPT_ATOM2_CH01_ISR_API                                                  STD_OFF
#define GPT_ATOM2_CH02_ISR_API                                                  STD_OFF
#define GPT_ATOM2_CH03_ISR_API                                                  STD_OFF
#define GPT_ATOM2_CH04_ISR_API                                                  STD_OFF
#define GPT_ATOM2_CH05_ISR_API                                                  STD_OFF
#define GPT_ATOM2_CH06_ISR_API                                                  STD_OFF
#define GPT_ATOM2_CH07_ISR_API                                                  STD_OFF
#define GPT_ATOM3_CH00_ISR_API                                                  STD_OFF
#define GPT_ATOM3_CH01_ISR_API                                                  STD_OFF
#define GPT_ATOM3_CH02_ISR_API                                                  STD_OFF
#define GPT_ATOM3_CH03_ISR_API                                                  STD_OFF
#define GPT_ATOM3_CH04_ISR_API                                                  STD_OFF
#define GPT_ATOM3_CH05_ISR_API                                                  STD_OFF
#define GPT_ATOM3_CH06_ISR_API                                                  STD_OFF
#define GPT_ATOM3_CH07_ISR_API                                                  STD_OFF
#define GPT_ATOM4_CH00_ISR_API                                                  STD_OFF
#define GPT_ATOM4_CH01_ISR_API                                                  STD_OFF
#define GPT_ATOM4_CH02_ISR_API                                                  STD_OFF
#define GPT_ATOM4_CH03_ISR_API                                                  STD_OFF
#define GPT_ATOM4_CH04_ISR_API                                                  STD_OFF
#define GPT_ATOM4_CH05_ISR_API                                                  STD_OFF
#define GPT_ATOM4_CH06_ISR_API                                                  STD_OFF
#define GPT_ATOM4_CH07_ISR_API                                                  STD_OFF
#define GPT_ATOM5_CH00_ISR_API                                                  STD_OFF
#define GPT_ATOM5_CH01_ISR_API                                                  STD_OFF
#define GPT_ATOM5_CH02_ISR_API                                                  STD_OFF
#define GPT_ATOM5_CH03_ISR_API                                                  STD_OFF
#define GPT_ATOM5_CH04_ISR_API                                                  STD_OFF
#define GPT_ATOM5_CH05_ISR_API                                                  STD_OFF
#define GPT_ATOM5_CH06_ISR_API                                                  STD_OFF
#define GPT_ATOM5_CH07_ISR_API                                                  STD_OFF
#define GPT_ATOM6_CH00_ISR_API                                                  STD_OFF
#define GPT_ATOM6_CH01_ISR_API                                                  STD_OFF
#define GPT_ATOM6_CH02_ISR_API                                                  STD_OFF
#define GPT_ATOM6_CH03_ISR_API                                                  STD_OFF
#define GPT_ATOM6_CH04_ISR_API                                                  STD_OFF
#define GPT_ATOM6_CH05_ISR_API                                                  STD_OFF
#define GPT_ATOM6_CH06_ISR_API                                                  STD_OFF
#define GPT_ATOM6_CH07_ISR_API                                                  STD_OFF
#define GPT_ATOM7_CH00_ISR_API                                                  STD_OFF
#define GPT_ATOM7_CH01_ISR_API                                                  STD_OFF
#define GPT_ATOM7_CH02_ISR_API                                                  STD_OFF
#define GPT_ATOM7_CH03_ISR_API                                                  STD_OFF
#define GPT_ATOM7_CH04_ISR_API                                                  STD_OFF
#define GPT_ATOM7_CH05_ISR_API                                                  STD_OFF
#define GPT_ATOM7_CH06_ISR_API                                                  STD_OFF
#define GPT_ATOM7_CH07_ISR_API                                                  STD_OFF
#define GPT_ATOM8_CH00_ISR_API                                                  STD_OFF
#define GPT_ATOM8_CH01_ISR_API                                                  STD_OFF
#define GPT_ATOM8_CH02_ISR_API                                                  STD_OFF
#define GPT_ATOM8_CH03_ISR_API                                                  STD_OFF
#define GPT_ATOM8_CH04_ISR_API                                                  STD_OFF
#define GPT_ATOM8_CH05_ISR_API                                                  STD_OFF
#define GPT_ATOM8_CH06_ISR_API                                                  STD_OFF
#define GPT_ATOM8_CH07_ISR_API                                                  STD_OFF
#define GPT_ATOM9_CH00_ISR_API                                                  STD_OFF
#define GPT_ATOM9_CH01_ISR_API                                                  STD_OFF
#define GPT_ATOM9_CH02_ISR_API                                                  STD_OFF
#define GPT_ATOM9_CH03_ISR_API                                                  STD_OFF
#define GPT_ATOM9_CH04_ISR_API                                                  STD_OFF
#define GPT_ATOM9_CH05_ISR_API                                                  STD_OFF
#define GPT_ATOM9_CH06_ISR_API                                                  STD_OFF
#define GPT_ATOM9_CH07_ISR_API                                                  STD_OFF
/* GPT Channel Handles */
#define GptConf_GptChannelConfiguration_GPT_OSTM0                               (Gpt_ChannelType) 0x00
/* GPT ConfigSet Handles */
#define Gpt_Config                                                              (&Gpt_GaaConfiguration[0])
/* Channel Mapping for Timer Unit Channels */
#define GPT_OSTM00_CH0                                                          0x00



/***********************************************************************************************************************
**                      Global Data Types                                                                             **
***********************************************************************************************************************/



/***********************************************************************************************************************
**                      Global Data                                                                                   **
***********************************************************************************************************************/



/***********************************************************************************************************************
**                      Function Prototypes                                                                           **
***********************************************************************************************************************/



#endif /* GPT_CFG_H */


/***********************************************************************************************************************
**                      End of File                                                                                   **
***********************************************************************************************************************/

