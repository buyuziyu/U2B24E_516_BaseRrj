/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Pwm_Cfg.h                                                                                           */
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
/* TOOL VERSION:  PwmU2Bx-E.dll version: 2.5.1, MCALConfGen.exe version: 2.3.0                                        */
/*                                                                                                                    */


/***********************************************************************************************************************
**                      Input File                                                                                    **
***********************************************************************************************************************/
/*
 * INPUT FILE:    C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\MCAL_RH850U2B24E_516_CodeGen\U2B24-E.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\modules\pwm\generator\U2B24-E\R2211_pwm_U2B24-E_BSWMDT.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\Dem\xml\Dem_pwm.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\Os\xml\Os_pwm.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\EcuC\xml\EcuC_pwm.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\MCAL_RH850U2B24E_516_CodeGen\Translation.trxml
 * GENERATED ON:  10 Jul 2026 - 18:50:00
 */


#ifndef PWM_CFG_H
#define PWM_CFG_H


/***********************************************************************************************************************
**                      Include Section                                                                               **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                      Coding Rule Violations                                                                        **
***********************************************************************************************************************/



/***********************************************************************************************************************
**                      Version Information                                                                           **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define PWM_CFG_AR_RELEASE_MAJOR_VERSION                                        4U
#define PWM_CFG_AR_RELEASE_MINOR_VERSION                                        8U
#define PWM_CFG_AR_RELEASE_REVISION_VERSION                                     0U

/* File version information */
#define PWM_CFG_SW_MAJOR_VERSION                                                2U
#define PWM_CFG_SW_MINOR_VERSION                                                5U

/* Macro for AR version */
#define PWM_AR_VERSION                                                          PWM_AR_R22_11_VERSION

/* Macro for GTM version */
#define PWM_GTM_VERSION                                                         PWM_GTM_4_1_VERSION

/***********************************************************************************************************************
**                      Common Published Information                                                                  **
***********************************************************************************************************************/
#define PWM_AR_RELEASE_MAJOR_VERSION_VALUE                                      4U
#define PWM_AR_RELEASE_MINOR_VERSION_VALUE                                      8U
#define PWM_AR_RELEASE_REVISION_VERSION_VALUE                                   0U

#define PWM_SW_MAJOR_VERSION_VALUE                                              2U
#define PWM_SW_MINOR_VERSION_VALUE                                              5U
#define PWM_SW_PATCH_VERSION_VALUE                                              1U

#define PWM_VENDOR_ID_VALUE                                                     59U
#define PWM_MODULE_ID_VALUE                                                     121U

/***********************************************************************************************************************
**                      Global Symbols                                                                                **
***********************************************************************************************************************/
/* Instance ID of the PWM Driver */
#define PWM_INSTANCE_ID_VALUE                                                   0U

/* Total number of PWM TAUD units configured */
#define PWM_TOTAL_TAUD_UNITS_CONFIG                                             0U

/* Total number of PWM TAUJ units configured */
#define PWM_TOTAL_TAUJ_UNITS_CONFIG                                             0U

/* Total number of PWM GTM units configured */
#define PWM_TOTAL_GTM_UNITS_CONFIG                                              1U

/* Total number of PWM Channels configured */
#define PWM_TOTAL_CHANNELS_CONFIG                                               1U

/* Maximum channel ID configured */
#define PWM_MAX_CHANNEL_ID_CONFIGURED                                           0U

/* Enable/Disable the TAUD unit depending on the TAUD channels configured */
#define PWM_TAUD_UNIT_USED                                                      STD_OFF

/* Enable/Disable the TAUD3's unit depending on the TAUD3's channels configured */
#define PWM_TAUD3_UNIT_USED                                                     STD_OFF

/* Enable/Disable the TAUJ unit depending on the TAUJ channels configured */
#define PWM_TAUJ_UNIT_USED                                                      STD_OFF

/* Enable/disable the setting of Prescaler, baudrate and blConfigurePrescaler by the PWM Driver for TAUD */
#define PWM_TAUD_PRESCALER                                                      STD_OFF

/* Enable/disable the setting of Prescaler, baudrate and blConfigurePrescaler by the PWM Driver for TAUJ */
#define PWM_TAUJ_PRESCALER                                                      STD_OFF

/* Enable/Disable the ATUE unit depending on the ATU channels configured */
#define PWM_ATU_UNIT_USED                                                       STD_OFF

/* Enable/Disable the GTM unit depending on the GTM channels configured */
#define PWM_GTM_UNIT_USED                                                       STD_ON

/* Enable/Disable the TOM feature depending on the GTM channels configured */
#define PWM_GTM_TOM_USED                                                        STD_OFF

/* Enable/Disable the ATOM feature depending on the GTM channels configured */
#define PWM_GTM_ATOM_USED                                                       STD_ON

/* Previous simultaneous rewrite failed */
#define PWM_E_REWRITE_FAILED                                                    \
                                                                         DemConf_DemEventParameter_DemEventParameter_001

/* Total number of HW IP configured */
#define PWM_TOTAL_HW_IP_CONFIG                                                  1U

/* Enables/Disables PWM_CLOCK_SETTING */
#define PWM_CLOCK_SETTING                                                       STD_OFF

/* Enable/Disable the DIAG unit depending on the DIAG_CH channels configured */
#define PWM_DIAG_UNIT_USED                                                      STD_OFF

/* Enables/Disables PWM_E_REWRITE_FAILED */
#define PWM_E_REWRITE_FAILED_CONFIGURED                                         STD_OFF

/* Enables/Disables the Pwm_DeInit API */
#define PWM_DE_INIT_API                                                         STD_ON

/* Enables/Disables GetVersionInfo API */
#define PWM_VERSION_INFO_API                                                    STD_ON

/* Enables/Disables the Pwm_GetOutputState API */
#define PWM_GET_OUTPUT_STATE_API                                                STD_ON

/* Enables/Disables the Pwm_SetDutyCycle API */
#define PWM_SET_DUTY_CYCLE_API                                                  STD_ON

/* Enables/Disables the Pwm_SetOutputToIdle API */
#define PWM_SET_OUTPUT_TO_IDLE_API                                              STD_ON

/* Enables/Disables the Pwm_SetPeriodAndDuty API */
#define PWM_SET_PERIOD_AND_DUTY_API                                             STD_ON

/* Enables/Disables the Pwm_SetChannelClk API */
#define PWM_SELECT_CHANNEL_CLK_API                                              STD_ON

/* Enables/Disables the Pwm_SetChannelOutput API */
#define PWM_SET_CHANNEL_OUTPUT_API                                              STD_ON

/* Enables/Disables PwmSetTriggerDelayApi API */
#define PWM_SET_TRIGGER_DELAY_API                                               STD_OFF

/* Enables/Disables PwmDiagReadAdConvResultApi API */
#define PWM_READ_CONV_RESLUT_API                                                STD_OFF

/* Enables/Disables PwmDiagEnableDisableAdTriggerApi API */
#define PWM_ENABLE_DISABLE_AD_TRG_API                                           STD_OFF

/* Enables/Disables Multi Core Distributed type IV for PWM Driver */
#define PWM_MULTI_CORE_SUPPORT                                                  STD_OFF

/* Enables/Disables Development error detection */
#define PWM_DEV_ERROR_DETECT                                                    STD_OFF

/* Enables/Disables the PWM_E_ALREADY_INITIALIZED Det check in Pwm_Init API */
#define PWM_ALREADY_INIT_DET_CHECK                                              STD_ON

/* Pre-compile option for enable or disable version check of inter-module dependencies */
#define PWM_VERSION_CHECK_EXT_MODULES                                           STD_ON

/* Enables/Disables the Critical section protection */
#define PWM_CRITICAL_SECTION_PROTECTION                                         STD_ON

/* Enables/Disables Clearing Pending Interrupts */
#define PWM_CLEAR_PENDING_INTERRUPT                                             STD_ON

/* Enables/Disables Pwm Notification */
#define PWM_NOTIFICATION_SUPPORTED                                              STD_ON

/* Enables/Disables Synchronous start/stop of timer functionality */
#define PWM_SYNC_START_SUPPORT                                                  STD_ON

/* Enables/Disables the interrupt consistency check */
#define PWM_INTERRUPT_CONSISTENCY_CHECK                                         STD_OFF

/* Adds/Removes all power state management related APIs */
#define PWM_LOW_POWER_STATE_SUPPORT                                             STD_OFF

/* Interrupt category */
#define PWM_ISR_CATEGORY_2                                                      STD_OFF

/* ATU IP is using or not */
#define PWM_TIMER_IP_ATU                                                        STD_OFF

/* TAU IP is using or not */
#define PWM_TIMER_IP_TAUDJ                                                      STD_ON

/* Macros for enabling/disabling ISRS */

/* Macros for enabling/disabling TAUD/TAUJ ISRs */
#define PWM_TAUD0_CH00_ISR_API                                                  STD_OFF
#define PWM_TAUD0_CH01_ISR_API                                                  STD_OFF
#define PWM_TAUD0_CH02_ISR_API                                                  STD_OFF
#define PWM_TAUD0_CH03_ISR_API                                                  STD_OFF
#define PWM_TAUD0_CH04_ISR_API                                                  STD_OFF
#define PWM_TAUD0_CH05_ISR_API                                                  STD_OFF
#define PWM_TAUD0_CH06_ISR_API                                                  STD_OFF
#define PWM_TAUD0_CH07_ISR_API                                                  STD_OFF
#define PWM_TAUD0_CH08_ISR_API                                                  STD_OFF
#define PWM_TAUD0_CH09_ISR_API                                                  STD_OFF
#define PWM_TAUD0_CH10_ISR_API                                                  STD_OFF
#define PWM_TAUD0_CH11_ISR_API                                                  STD_OFF
#define PWM_TAUD0_CH12_ISR_API                                                  STD_OFF
#define PWM_TAUD0_CH13_ISR_API                                                  STD_OFF
#define PWM_TAUD0_CH14_ISR_API                                                  STD_OFF
#define PWM_TAUD0_CH15_ISR_API                                                  STD_OFF
#define PWM_TAUD1_CH00_ISR_API                                                  STD_OFF
#define PWM_TAUD1_CH01_ISR_API                                                  STD_OFF
#define PWM_TAUD1_CH02_ISR_API                                                  STD_OFF
#define PWM_TAUD1_CH03_ISR_API                                                  STD_OFF
#define PWM_TAUD1_CH04_ISR_API                                                  STD_OFF
#define PWM_TAUD1_CH05_ISR_API                                                  STD_OFF
#define PWM_TAUD1_CH06_ISR_API                                                  STD_OFF
#define PWM_TAUD1_CH07_ISR_API                                                  STD_OFF
#define PWM_TAUD1_CH08_ISR_API                                                  STD_OFF
#define PWM_TAUD1_CH09_ISR_API                                                  STD_OFF
#define PWM_TAUD1_CH10_ISR_API                                                  STD_OFF
#define PWM_TAUD1_CH11_ISR_API                                                  STD_OFF
#define PWM_TAUD1_CH12_ISR_API                                                  STD_OFF
#define PWM_TAUD1_CH13_ISR_API                                                  STD_OFF
#define PWM_TAUD1_CH14_ISR_API                                                  STD_OFF
#define PWM_TAUD1_CH15_ISR_API                                                  STD_OFF
#define PWM_TAUD2_CH00_ISR_API                                                  STD_OFF
#define PWM_TAUD2_CH01_ISR_API                                                  STD_OFF
#define PWM_TAUD2_CH02_ISR_API                                                  STD_OFF
#define PWM_TAUD2_CH03_ISR_API                                                  STD_OFF
#define PWM_TAUD2_CH04_ISR_API                                                  STD_OFF
#define PWM_TAUD2_CH05_ISR_API                                                  STD_OFF
#define PWM_TAUD2_CH06_ISR_API                                                  STD_OFF
#define PWM_TAUD2_CH07_ISR_API                                                  STD_OFF
#define PWM_TAUD2_CH08_ISR_API                                                  STD_OFF
#define PWM_TAUD2_CH09_ISR_API                                                  STD_OFF
#define PWM_TAUD2_CH10_ISR_API                                                  STD_OFF
#define PWM_TAUD2_CH11_ISR_API                                                  STD_OFF
#define PWM_TAUD2_CH12_ISR_API                                                  STD_OFF
#define PWM_TAUD2_CH13_ISR_API                                                  STD_OFF
#define PWM_TAUD2_CH14_ISR_API                                                  STD_OFF
#define PWM_TAUD2_CH15_ISR_API                                                  STD_OFF
#define PWM_TAUD3_CH00_ISR_API                                                  STD_OFF
#define PWM_TAUD3_CH01_ISR_API                                                  STD_OFF
#define PWM_TAUD3_CH02_ISR_API                                                  STD_OFF
#define PWM_TAUD3_CH03_ISR_API                                                  STD_OFF
#define PWM_TAUD3_CH04_ISR_API                                                  STD_OFF
#define PWM_TAUD3_CH05_ISR_API                                                  STD_OFF
#define PWM_TAUD3_CH06_ISR_API                                                  STD_OFF
#define PWM_TAUD3_CH07_ISR_API                                                  STD_OFF
#define PWM_TAUD3_CH08_ISR_API                                                  STD_OFF
#define PWM_TAUD3_CH09_ISR_API                                                  STD_OFF
#define PWM_TAUD3_CH10_ISR_API                                                  STD_OFF
#define PWM_TAUD3_CH11_ISR_API                                                  STD_OFF
#define PWM_TAUD3_CH12_ISR_API                                                  STD_OFF
#define PWM_TAUD3_CH13_ISR_API                                                  STD_OFF
#define PWM_TAUD3_CH14_ISR_API                                                  STD_OFF
#define PWM_TAUD3_CH15_ISR_API                                                  STD_OFF
#define PWM_TAUJ0_CH00_ISR_API                                                  STD_OFF
#define PWM_TAUJ0_CH01_ISR_API                                                  STD_OFF
#define PWM_TAUJ0_CH02_ISR_API                                                  STD_OFF
#define PWM_TAUJ0_CH03_ISR_API                                                  STD_OFF
#define PWM_TAUJ1_CH00_ISR_API                                                  STD_OFF
#define PWM_TAUJ1_CH01_ISR_API                                                  STD_OFF
#define PWM_TAUJ1_CH02_ISR_API                                                  STD_OFF
#define PWM_TAUJ1_CH03_ISR_API                                                  STD_OFF
#define PWM_TAUJ2_CH00_ISR_API                                                  STD_OFF
#define PWM_TAUJ2_CH01_ISR_API                                                  STD_OFF
#define PWM_TAUJ2_CH02_ISR_API                                                  STD_OFF
#define PWM_TAUJ2_CH03_ISR_API                                                  STD_OFF
#define PWM_TAUJ3_CH00_ISR_API                                                  STD_OFF
#define PWM_TAUJ3_CH01_ISR_API                                                  STD_OFF
#define PWM_TAUJ3_CH02_ISR_API                                                  STD_OFF
#define PWM_TAUJ3_CH03_ISR_API                                                  STD_OFF

/* Macros for enabling/disabling TOM/ATOM ISRs */
#define PWM_TOM0_CH00_ISR_API                                                   STD_OFF
#define PWM_TOM0_CH01_ISR_API                                                   STD_OFF
#define PWM_TOM0_CH02_ISR_API                                                   STD_OFF
#define PWM_TOM0_CH03_ISR_API                                                   STD_OFF
#define PWM_TOM0_CH04_ISR_API                                                   STD_OFF
#define PWM_TOM0_CH05_ISR_API                                                   STD_OFF
#define PWM_TOM0_CH06_ISR_API                                                   STD_OFF
#define PWM_TOM0_CH07_ISR_API                                                   STD_OFF
#define PWM_TOM0_CH08_ISR_API                                                   STD_OFF
#define PWM_TOM0_CH09_ISR_API                                                   STD_OFF
#define PWM_TOM0_CH10_ISR_API                                                   STD_OFF
#define PWM_TOM0_CH11_ISR_API                                                   STD_OFF
#define PWM_TOM0_CH12_ISR_API                                                   STD_OFF
#define PWM_TOM0_CH13_ISR_API                                                   STD_OFF
#define PWM_TOM0_CH14_ISR_API                                                   STD_OFF
#define PWM_TOM0_CH15_ISR_API                                                   STD_OFF
#define PWM_TOM1_CH00_ISR_API                                                   STD_OFF
#define PWM_TOM1_CH01_ISR_API                                                   STD_OFF
#define PWM_TOM1_CH02_ISR_API                                                   STD_OFF
#define PWM_TOM1_CH03_ISR_API                                                   STD_OFF
#define PWM_TOM1_CH04_ISR_API                                                   STD_OFF
#define PWM_TOM1_CH05_ISR_API                                                   STD_OFF
#define PWM_TOM1_CH06_ISR_API                                                   STD_OFF
#define PWM_TOM1_CH07_ISR_API                                                   STD_OFF
#define PWM_TOM1_CH08_ISR_API                                                   STD_OFF
#define PWM_TOM1_CH09_ISR_API                                                   STD_OFF
#define PWM_TOM1_CH10_ISR_API                                                   STD_OFF
#define PWM_TOM1_CH11_ISR_API                                                   STD_OFF
#define PWM_TOM1_CH12_ISR_API                                                   STD_OFF
#define PWM_TOM1_CH13_ISR_API                                                   STD_OFF
#define PWM_TOM1_CH14_ISR_API                                                   STD_OFF
#define PWM_TOM1_CH15_ISR_API                                                   STD_OFF
#define PWM_TOM2_CH00_ISR_API                                                   STD_OFF
#define PWM_TOM2_CH01_ISR_API                                                   STD_OFF
#define PWM_TOM2_CH02_ISR_API                                                   STD_OFF
#define PWM_TOM2_CH03_ISR_API                                                   STD_OFF
#define PWM_TOM2_CH04_ISR_API                                                   STD_OFF
#define PWM_TOM2_CH05_ISR_API                                                   STD_OFF
#define PWM_TOM2_CH06_ISR_API                                                   STD_OFF
#define PWM_TOM2_CH07_ISR_API                                                   STD_OFF
#define PWM_TOM2_CH08_ISR_API                                                   STD_OFF
#define PWM_TOM2_CH09_ISR_API                                                   STD_OFF
#define PWM_TOM2_CH10_ISR_API                                                   STD_OFF
#define PWM_TOM2_CH11_ISR_API                                                   STD_OFF
#define PWM_TOM2_CH12_ISR_API                                                   STD_OFF
#define PWM_TOM2_CH13_ISR_API                                                   STD_OFF
#define PWM_TOM2_CH14_ISR_API                                                   STD_OFF
#define PWM_TOM2_CH15_ISR_API                                                   STD_OFF
#define PWM_TOM3_CH00_ISR_API                                                   STD_OFF
#define PWM_TOM3_CH01_ISR_API                                                   STD_OFF
#define PWM_TOM3_CH02_ISR_API                                                   STD_OFF
#define PWM_TOM3_CH03_ISR_API                                                   STD_OFF
#define PWM_TOM3_CH04_ISR_API                                                   STD_OFF
#define PWM_TOM3_CH05_ISR_API                                                   STD_OFF
#define PWM_TOM3_CH06_ISR_API                                                   STD_OFF
#define PWM_TOM3_CH07_ISR_API                                                   STD_OFF
#define PWM_TOM3_CH08_ISR_API                                                   STD_OFF
#define PWM_TOM3_CH09_ISR_API                                                   STD_OFF
#define PWM_TOM3_CH10_ISR_API                                                   STD_OFF
#define PWM_TOM3_CH11_ISR_API                                                   STD_OFF
#define PWM_TOM3_CH12_ISR_API                                                   STD_OFF
#define PWM_TOM3_CH13_ISR_API                                                   STD_OFF
#define PWM_TOM3_CH14_ISR_API                                                   STD_OFF
#define PWM_TOM3_CH15_ISR_API                                                   STD_OFF
#define PWM_TOM4_CH00_ISR_API                                                   STD_OFF
#define PWM_TOM4_CH01_ISR_API                                                   STD_OFF
#define PWM_TOM4_CH02_ISR_API                                                   STD_OFF
#define PWM_TOM4_CH03_ISR_API                                                   STD_OFF
#define PWM_TOM4_CH04_ISR_API                                                   STD_OFF
#define PWM_TOM4_CH05_ISR_API                                                   STD_OFF
#define PWM_TOM4_CH06_ISR_API                                                   STD_OFF
#define PWM_TOM4_CH07_ISR_API                                                   STD_OFF
#define PWM_TOM4_CH08_ISR_API                                                   STD_OFF
#define PWM_TOM4_CH09_ISR_API                                                   STD_OFF
#define PWM_TOM4_CH10_ISR_API                                                   STD_OFF
#define PWM_TOM4_CH11_ISR_API                                                   STD_OFF
#define PWM_TOM4_CH12_ISR_API                                                   STD_OFF
#define PWM_TOM4_CH13_ISR_API                                                   STD_OFF
#define PWM_TOM4_CH14_ISR_API                                                   STD_OFF
#define PWM_TOM4_CH15_ISR_API                                                   STD_OFF
#define PWM_ATOM0_CH00_ISR_API                                                  STD_OFF
#define PWM_ATOM0_CH01_ISR_API                                                  STD_OFF
#define PWM_ATOM0_CH02_ISR_API                                                  STD_OFF
#define PWM_ATOM0_CH03_ISR_API                                                  STD_OFF
#define PWM_ATOM0_CH04_ISR_API                                                  STD_OFF
#define PWM_ATOM0_CH05_ISR_API                                                  STD_OFF
#define PWM_ATOM0_CH06_ISR_API                                                  STD_OFF
#define PWM_ATOM0_CH07_ISR_API                                                  STD_OFF
#define PWM_ATOM1_CH00_ISR_API                                                  STD_OFF
#define PWM_ATOM1_CH01_ISR_API                                                  STD_OFF
#define PWM_ATOM1_CH02_ISR_API                                                  STD_OFF
#define PWM_ATOM1_CH03_ISR_API                                                  STD_OFF
#define PWM_ATOM1_CH04_ISR_API                                                  STD_OFF
#define PWM_ATOM1_CH05_ISR_API                                                  STD_OFF
#define PWM_ATOM1_CH06_ISR_API                                                  STD_OFF
#define PWM_ATOM1_CH07_ISR_API                                                  STD_OFF
#define PWM_ATOM2_CH00_ISR_API                                                  STD_OFF
#define PWM_ATOM2_CH01_ISR_API                                                  STD_OFF
#define PWM_ATOM2_CH02_ISR_API                                                  STD_OFF
#define PWM_ATOM2_CH03_ISR_API                                                  STD_OFF
#define PWM_ATOM2_CH04_ISR_API                                                  STD_OFF
#define PWM_ATOM2_CH05_ISR_API                                                  STD_OFF
#define PWM_ATOM2_CH06_ISR_API                                                  STD_OFF
#define PWM_ATOM2_CH07_ISR_API                                                  STD_OFF
#define PWM_ATOM3_CH00_ISR_API                                                  STD_OFF
#define PWM_ATOM3_CH01_ISR_API                                                  STD_OFF
#define PWM_ATOM3_CH02_ISR_API                                                  STD_OFF
#define PWM_ATOM3_CH03_ISR_API                                                  STD_OFF
#define PWM_ATOM3_CH04_ISR_API                                                  STD_OFF
#define PWM_ATOM3_CH05_ISR_API                                                  STD_OFF
#define PWM_ATOM3_CH06_ISR_API                                                  STD_OFF
#define PWM_ATOM3_CH07_ISR_API                                                  STD_OFF
#define PWM_ATOM4_CH00_ISR_API                                                  STD_OFF
#define PWM_ATOM4_CH01_ISR_API                                                  STD_OFF
#define PWM_ATOM4_CH02_ISR_API                                                  STD_OFF
#define PWM_ATOM4_CH03_ISR_API                                                  STD_OFF
#define PWM_ATOM4_CH04_ISR_API                                                  STD_OFF
#define PWM_ATOM4_CH05_ISR_API                                                  STD_OFF
#define PWM_ATOM4_CH06_ISR_API                                                  STD_OFF
#define PWM_ATOM4_CH07_ISR_API                                                  STD_OFF
#define PWM_ATOM5_CH00_ISR_API                                                  STD_OFF
#define PWM_ATOM5_CH01_ISR_API                                                  STD_OFF
#define PWM_ATOM5_CH02_ISR_API                                                  STD_OFF
#define PWM_ATOM5_CH03_ISR_API                                                  STD_OFF
#define PWM_ATOM5_CH04_ISR_API                                                  STD_OFF
#define PWM_ATOM5_CH05_ISR_API                                                  STD_OFF
#define PWM_ATOM5_CH06_ISR_API                                                  STD_OFF
#define PWM_ATOM5_CH07_ISR_API                                                  STD_OFF
#define PWM_ATOM6_CH00_ISR_API                                                  STD_OFF
#define PWM_ATOM6_CH01_ISR_API                                                  STD_OFF
#define PWM_ATOM6_CH02_ISR_API                                                  STD_OFF
#define PWM_ATOM6_CH03_ISR_API                                                  STD_OFF
#define PWM_ATOM6_CH04_ISR_API                                                  STD_OFF
#define PWM_ATOM6_CH05_ISR_API                                                  STD_OFF
#define PWM_ATOM6_CH06_ISR_API                                                  STD_OFF
#define PWM_ATOM6_CH07_ISR_API                                                  STD_OFF
#define PWM_ATOM7_CH00_ISR_API                                                  STD_OFF
#define PWM_ATOM7_CH01_ISR_API                                                  STD_OFF
#define PWM_ATOM7_CH02_ISR_API                                                  STD_OFF
#define PWM_ATOM7_CH03_ISR_API                                                  STD_OFF
#define PWM_ATOM7_CH04_ISR_API                                                  STD_OFF
#define PWM_ATOM7_CH05_ISR_API                                                  STD_OFF
#define PWM_ATOM7_CH06_ISR_API                                                  STD_OFF
#define PWM_ATOM7_CH07_ISR_API                                                  STD_OFF
#define PWM_ATOM8_CH00_ISR_API                                                  STD_OFF
#define PWM_ATOM8_CH01_ISR_API                                                  STD_OFF
#define PWM_ATOM8_CH02_ISR_API                                                  STD_OFF
#define PWM_ATOM8_CH03_ISR_API                                                  STD_OFF
#define PWM_ATOM8_CH04_ISR_API                                                  STD_OFF
#define PWM_ATOM8_CH05_ISR_API                                                  STD_OFF
#define PWM_ATOM8_CH06_ISR_API                                                  STD_OFF
#define PWM_ATOM8_CH07_ISR_API                                                  STD_OFF
#define PWM_ATOM9_CH00_ISR_API                                                  STD_OFF
#define PWM_ATOM9_CH01_ISR_API                                                  STD_OFF
#define PWM_ATOM9_CH02_ISR_API                                                  STD_OFF
#define PWM_ATOM9_CH03_ISR_API                                                  STD_OFF
#define PWM_ATOM9_CH04_ISR_API                                                  STD_OFF
#define PWM_ATOM9_CH05_ISR_API                                                  STD_OFF
#define PWM_ATOM9_CH06_ISR_API                                                  STD_OFF
#define PWM_ATOM9_CH07_ISR_API                                                  STD_OFF



/* Channel Mapping for Timer Unit Channels */

/* Channel Mapping for Timer Unit Channels */

/* Channel Mapping for Timer Unit Channels */
#define PWM_ATOM0_CH00                                                          (uint8)0x00

/* PWM Channel Handles */
#define PwmConf_PwmChannel_PwmChannel_ATOM00                                    (Pwm_ChannelType)0x00

/* Configuration Set Handles */
#define Pwm_Config                                                              (&Pwm_GaaConfiguration[0])

/* Include header files support for timer */


/***********************************************************************************************************************
**                      Global Data Types                                                                             **
***********************************************************************************************************************/



/***********************************************************************************************************************
**                      Global Data                                                                                   **
***********************************************************************************************************************/



/***********************************************************************************************************************
**                      Function Prototypes                                                                           **
***********************************************************************************************************************/



#endif /* PWM_CFG_H */


/***********************************************************************************************************************
**                      End of File                                                                                   **
***********************************************************************************************************************/

