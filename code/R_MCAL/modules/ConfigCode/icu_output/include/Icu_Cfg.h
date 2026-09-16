/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Icu_Cfg.h                                                                                           */
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
/* TOOL VERSION:  IcuU2Bx-E.dll version: 2.4.1, MCALConfGen.exe version: 2.3.0                                        */
/*                                                                                                                    */


/***********************************************************************************************************************
**                      Input File                                                                                    **
***********************************************************************************************************************/
/*
 * INPUT FILE:    C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\MCAL_RH850U2B24E_516_CodeGen\U2B24-E.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\modules\icu\generator\U2B24-E\R2211_icu_U2B24-E_BSWMDT.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\Dem\xml\Dem_icu.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\EcuM\xml\EcuM_icu.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\Os\xml\Os_icu.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\EcuC\xml\EcuC_icu.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\MCAL_RH850U2B24E_516_CodeGen\Translation.trxml
 * GENERATED ON:  10 Jul 2026 - 18:49:38
 */


#ifndef ICU_CFG_H
#define ICU_CFG_H


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
#define ICU_CFG_AR_RELEASE_MAJOR_VERSION                                        4U
#define ICU_CFG_AR_RELEASE_MINOR_VERSION                                        8U
#define ICU_CFG_AR_RELEASE_REVISION_VERSION                                     0U

/* File version information */
#define ICU_CFG_SW_MAJOR_VERSION                                                2U
#define ICU_CFG_SW_MINOR_VERSION                                                4U
/* Macro to distinguish Autosar version */
#define ICU_AR_VERSION                                                          ICU_AR_R22_11_VERSION

/***********************************************************************************************************************
**                      Common Published Information                                                                  **
***********************************************************************************************************************/
#define ICU_AR_RELEASE_MAJOR_VERSION_VALUE                                      4U
#define ICU_AR_RELEASE_MINOR_VERSION_VALUE                                      8U
#define ICU_AR_RELEASE_REVISION_VERSION_VALUE                                   0U

#define ICU_SW_MAJOR_VERSION_VALUE                                              2U
#define ICU_SW_MINOR_VERSION_VALUE                                              4U
#define ICU_SW_PATCH_VERSION_VALUE                                              1U

#define ICU_VENDOR_ID_VALUE                                                     59U
#define ICU_MODULE_ID_VALUE                                                     122U

/***********************************************************************************************************************
**                      Global Symbols                                                                                **
***********************************************************************************************************************/
/* Instance ID of the ICU Driver */
#define ICU_INSTANCE_ID_VALUE                                                   0U

/* Indicates whether the ATU timer channels configured or not */
#define ICU_ATU_TIMER_UNIT_USED                                                 STD_OFF

/* Indicates whether the TAU channels configured or not */
#define ICU_TAU_UNIT_USED                                                       STD_OFF

/* Maximum number of channels configured */
#define ICU_MAX_CHANNEL                                                         (Icu_ChannelType)1U

/* Maximum ICU Channel ID configured */
#define ICU_MAX_CHANNEL_ID_CONFIGURED                                           0U

/* Total number of ICU TAU units configured */
#define ICU_TOTAL_TAU_UNITS_CONFIGURED                                          0U

/* Enables/Disables the use of TAUD unit */
#define ICU_TAUD_UNIT_USED                                                      STD_OFF

/* Enables/Disables the use of TAUJ unit */
#define ICU_TAUJ_UNIT_USED                                                      STD_OFF

/* Enable/disable the setting of Prescaler, baud-rate and blConfigurePrescaler by the ICU Driver */
#define ICU_PRESCALER_CONFIGURED                                                STD_OFF

/* Enable/disable the setting of baud-rate by the ICU Driver for TAUD */
#define ICU_TAUD_UNIT_CONFIG                                                    STD_OFF

/* Enable/disable the setting of baud-rate by the ICU Driver for TAUJ */
#define ICU_TAUJ_UNIT_CONFIG                                                    STD_OFF

/* Pre-compile option for EDGE DETECT for External interrupts IRQ */
#define ICU_IRQ_EDGE_DETECT                                                     STD_OFF

/* Pre-compile option for EDGE DETECT for External interrupts INTP */
#define ICU_INTP_EDGE_DETECT                                                    STD_OFF

/* Total number of ICU HW-IP configured */
#define ICU_TOTAL_HW_IP_CONFIG                                                  1U

/* Enables/Disables the use of TAUD3 unit depending on the TAUD3 channels configured */
#define ICU_TAUD3_UNIT_USED                                                     STD_OFF

/* Enables/Disables the inclusion of Icu_DisableWakeup API */
#define ICU_DISABLE_WAKEUP_API                                                  STD_OFF

/* Enables/Disables the inclusion of Icu_EnableWakeup API */
#define ICU_ENABLE_WAKEUP_API                                                   STD_OFF

/* Enables/Disables the inclusion of Icu_CheckWakeup API */
#define ICU_WAKEUP_FUNCTIONALITY_API                                            STD_OFF

/* Enables/Disables wakeup source reporting */
#define ICU_REPORT_WAKEUP_SOURCE                                                STD_OFF

/* Enables/Disables the notification and wakeup */
#define ICU_NOTIFY_WAKEUP_INTERRUPT                                             STD_OFF

/* Enables/Disables the inclusion of Icu_SetMode API */
#define ICU_SET_MODE_API                                                        STD_OFF

/* Pre-compile option for USE_PREVIOUS_INPUT feature of TAUD01 */
#define ICU_TAUDN_USE_PREVIOUS_INPUT                                            STD_OFF

/* Pre-compile option for USE_PREVIOUS_INPUT feature of TAUD2 */
#define ICU_TAUD2_USE_PREVIOUS_INPUT                                            STD_OFF

/* Indicates whether the GTM TIM timer channels configured or not */
#define ICU_GTM_TIMER_UNIT_USED                                                 STD_ON

/* Indicates whether the GTM TBU timer is used or not */
#define ICU_GTM_TBU_UNIT_USED                                                   STD_ON

/* Indicates whether the GTM TBU0 timer is used or not */
#define ICU_GTM_TBU0_UNIT_CONFIGURED                                            STD_ON

/* Indicates whether the GTM TBU1 timer is used or not */
#define ICU_GTM_TBU1_UNIT_CONFIGURED                                            STD_OFF

/* Indicates whether the GTM TBU2 timer is used or not */
#define ICU_GTM_TBU2_UNIT_CONFIGURED                                            STD_OFF

/* Indicates whether the GTM TIM filter function is used or not */
#define ICU_GTM_TIM_FILTER_USED                                                 STD_OFF

/* Enable Multi Core Distributed type IV for ICU Driver */
#define ICU_MULTI_CORE_SUPPORT                                                  STD_OFF

/* Enables/Disables Default error detection */
#define ICU_DEV_ERROR_DETECT                                                    STD_OFF

/* Enables/Disables the inclusion of Icu_DeInit API */
#define ICU_DE_INIT_API                                                         STD_ON

/* Enables/Disables the inclusion of modules version information */
#define ICU_GET_VERSION_INFO_API                                                STD_ON

/* Enables/Disables the inclusion of Icu_GetInputState API */
#define ICU_GET_INPUT_STATE_API                                                 STD_ON

/* Enables/Disables the inclusion of Icu_StartTimestamp, Icu_StopTimestamp and Icu_GetTimestampIndex APIs */
#define ICU_TIMESTAMP_API                                                       STD_OFF

/* Enables/Disables the inclusion of Icu_ResetEdgeCount, Icu_EnableEdgeCount, Icu_DisableEdgeCount and                */
/*   Icu_GetEdgeNumbers APIs                                                                                          */
#define ICU_EDGE_COUNT_API                                                      STD_OFF

/* Enables/Disables the inclusion of Icu_GetTimeElapsed API */
#define ICU_GET_TIME_ELAPSED_API                                                STD_ON

/* Enables/Disables the inclusion of Icu_GetDutyCycleValues API */
#define ICU_GET_DUTY_CYCLE_VALUES_API                                           STD_ON

/* Enables/Disables Icu_StartSignalMeasurement and Icu_StopSignalMeasurement APIs */
#define ICU_SIGNAL_MEASUREMENT_API                                              STD_OFF

/* Enables/Disables the inclusion of Icu_EnableEdgeDetection and Icu_DisableEdgeDetection APIs */
#define ICU_EDGE_DETECT_API                                                     STD_ON

/* Enables/Disables the critical section protection */
#define ICU_CRITICAL_SECTION_PROTECTION                                         STD_ON

/* Pre-compile option for enable or disable version check of inter-module dependencies */
#define ICU_VERSION_CHECK_EXT_MODULES                                           STD_ON

/* Enable/Disable Clearing Pending Interrupts */
#define ICU_CLEAR_PENDING_INTERRUPT                                             STD_ON

/* Pre-compile option for enable or disable-already DET init check */
#define ICU_ALREADY_INIT_DET_CHECK                                              STD_ON

/* Pre-compile option for enable or disable busy operation DET check */
#define ICU_BUSY_OPERATION_DET_CHECK                                            STD_ON

/* Pre-compile option for enable or disable interrupt inconsitency check */
#define ICU_INTERRUPT_CONSISTENCY_CHECK                                         STD_OFF

/* Enables/Disables the inclusion of Icu_GetInputLevel API */
#define ICU_GET_INPUT_LEVEL_API                                                 STD_ON

/* Enables/Disables the counter value of TAU timer */
#define ICU_GET_TAU_COUNT_VALUE_API                                             STD_ON

/* Enables/Disables the already initialize Det check */
#define ICU_ALREADY_ENABLEDISABLE_DET_CHECK                                     STD_ON

/* Indicates the inclusion of notification function */
#define ICU_NOTIFICATION_CONFIG                                                 STD_OFF

/* Enables/Disables the Isr category */
#define ICU_ISR_CATEGORY_2                                                      STD_OFF

/* Macros for enabling/disabling ISRS */
#define ICU_TAUD0_CH00_ISR_API                                                  STD_OFF
#define ICU_TAUD0_CH01_ISR_API                                                  STD_OFF
#define ICU_TAUD0_CH02_ISR_API                                                  STD_OFF
#define ICU_TAUD0_CH03_ISR_API                                                  STD_OFF
#define ICU_TAUD0_CH04_ISR_API                                                  STD_OFF
#define ICU_TAUD0_CH05_ISR_API                                                  STD_OFF
#define ICU_TAUD0_CH06_ISR_API                                                  STD_OFF
#define ICU_TAUD0_CH07_ISR_API                                                  STD_OFF
#define ICU_TAUD0_CH08_ISR_API                                                  STD_OFF
#define ICU_TAUD0_CH09_ISR_API                                                  STD_OFF
#define ICU_TAUD0_CH10_ISR_API                                                  STD_OFF
#define ICU_TAUD0_CH11_ISR_API                                                  STD_OFF
#define ICU_TAUD0_CH12_ISR_API                                                  STD_OFF
#define ICU_TAUD0_CH13_ISR_API                                                  STD_OFF
#define ICU_TAUD0_CH14_ISR_API                                                  STD_OFF
#define ICU_TAUD0_CH15_ISR_API                                                  STD_OFF
#define ICU_TAUD1_CH00_ISR_API                                                  STD_OFF
#define ICU_TAUD1_CH01_ISR_API                                                  STD_OFF
#define ICU_TAUD1_CH02_ISR_API                                                  STD_OFF
#define ICU_TAUD1_CH03_ISR_API                                                  STD_OFF
#define ICU_TAUD1_CH04_ISR_API                                                  STD_OFF
#define ICU_TAUD1_CH05_ISR_API                                                  STD_OFF
#define ICU_TAUD1_CH06_ISR_API                                                  STD_OFF
#define ICU_TAUD1_CH07_ISR_API                                                  STD_OFF
#define ICU_TAUD1_CH08_ISR_API                                                  STD_OFF
#define ICU_TAUD1_CH09_ISR_API                                                  STD_OFF
#define ICU_TAUD1_CH10_ISR_API                                                  STD_OFF
#define ICU_TAUD1_CH11_ISR_API                                                  STD_OFF
#define ICU_TAUD1_CH12_ISR_API                                                  STD_OFF
#define ICU_TAUD1_CH13_ISR_API                                                  STD_OFF
#define ICU_TAUD1_CH14_ISR_API                                                  STD_OFF
#define ICU_TAUD1_CH15_ISR_API                                                  STD_OFF
#define ICU_TAUD2_CH00_ISR_API                                                  STD_OFF
#define ICU_TAUD2_CH01_ISR_API                                                  STD_OFF
#define ICU_TAUD2_CH02_ISR_API                                                  STD_OFF
#define ICU_TAUD2_CH03_ISR_API                                                  STD_OFF
#define ICU_TAUD2_CH04_ISR_API                                                  STD_OFF
#define ICU_TAUD2_CH05_ISR_API                                                  STD_OFF
#define ICU_TAUD2_CH06_ISR_API                                                  STD_OFF
#define ICU_TAUD2_CH07_ISR_API                                                  STD_OFF
#define ICU_TAUD2_CH08_ISR_API                                                  STD_OFF
#define ICU_TAUD2_CH09_ISR_API                                                  STD_OFF
#define ICU_TAUD2_CH10_ISR_API                                                  STD_OFF
#define ICU_TAUD2_CH11_ISR_API                                                  STD_OFF
#define ICU_TAUD2_CH12_ISR_API                                                  STD_OFF
#define ICU_TAUD2_CH13_ISR_API                                                  STD_OFF
#define ICU_TAUD2_CH14_ISR_API                                                  STD_OFF
#define ICU_TAUD2_CH15_ISR_API                                                  STD_OFF
#define ICU_TAUD3_CH00_ISR_API                                                  STD_OFF
#define ICU_TAUD3_CH01_ISR_API                                                  STD_OFF
#define ICU_TAUD3_CH02_ISR_API                                                  STD_OFF
#define ICU_TAUD3_CH03_ISR_API                                                  STD_OFF
#define ICU_TAUD3_CH04_ISR_API                                                  STD_OFF
#define ICU_TAUD3_CH05_ISR_API                                                  STD_OFF
#define ICU_TAUD3_CH06_ISR_API                                                  STD_OFF
#define ICU_TAUD3_CH07_ISR_API                                                  STD_OFF
#define ICU_TAUD3_CH08_ISR_API                                                  STD_OFF
#define ICU_TAUD3_CH09_ISR_API                                                  STD_OFF
#define ICU_TAUD3_CH10_ISR_API                                                  STD_OFF
#define ICU_TAUD3_CH11_ISR_API                                                  STD_OFF
#define ICU_TAUD3_CH12_ISR_API                                                  STD_OFF
#define ICU_TAUD3_CH13_ISR_API                                                  STD_OFF
#define ICU_TAUD3_CH14_ISR_API                                                  STD_OFF
#define ICU_TAUD3_CH15_ISR_API                                                  STD_OFF
#define ICU_TAUJ0_CH00_ISR_API                                                  STD_OFF
#define ICU_TAUJ0_CH01_ISR_API                                                  STD_OFF
#define ICU_TAUJ0_CH02_ISR_API                                                  STD_OFF
#define ICU_TAUJ0_CH03_ISR_API                                                  STD_OFF
#define ICU_TAUJ1_CH00_ISR_API                                                  STD_OFF
#define ICU_TAUJ1_CH01_ISR_API                                                  STD_OFF
#define ICU_TAUJ1_CH02_ISR_API                                                  STD_OFF
#define ICU_TAUJ1_CH03_ISR_API                                                  STD_OFF
#define ICU_TAUJ2_CH00_ISR_API                                                  STD_OFF
#define ICU_TAUJ2_CH01_ISR_API                                                  STD_OFF
#define ICU_TAUJ2_CH02_ISR_API                                                  STD_OFF
#define ICU_TAUJ2_CH03_ISR_API                                                  STD_OFF
#define ICU_TAUJ3_CH00_ISR_API                                                  STD_OFF
#define ICU_TAUJ3_CH01_ISR_API                                                  STD_OFF
#define ICU_TAUJ3_CH02_ISR_API                                                  STD_OFF
#define ICU_TAUJ3_CH03_ISR_API                                                  STD_OFF
#define ICU_GTM_TIM0_CH0_ISR_API                                                STD_OFF
#define ICU_GTM_TIM0_CH1_ISR_API                                                STD_OFF
#define ICU_GTM_TIM0_CH2_ISR_API                                                STD_OFF
#define ICU_GTM_TIM0_CH3_ISR_API                                                STD_OFF
#define ICU_GTM_TIM0_CH4_ISR_API                                                STD_OFF
#define ICU_GTM_TIM0_CH5_ISR_API                                                STD_OFF
#define ICU_GTM_TIM0_CH6_ISR_API                                                STD_OFF
#define ICU_GTM_TIM0_CH7_ISR_API                                                STD_OFF
#define ICU_GTM_TIM1_CH0_ISR_API                                                STD_OFF
#define ICU_GTM_TIM1_CH1_ISR_API                                                STD_OFF
#define ICU_GTM_TIM1_CH2_ISR_API                                                STD_OFF
#define ICU_GTM_TIM1_CH3_ISR_API                                                STD_OFF
#define ICU_GTM_TIM1_CH4_ISR_API                                                STD_OFF
#define ICU_GTM_TIM1_CH5_ISR_API                                                STD_OFF
#define ICU_GTM_TIM1_CH6_ISR_API                                                STD_OFF
#define ICU_GTM_TIM1_CH7_ISR_API                                                STD_OFF
#define ICU_GTM_TIM2_CH0_ISR_API                                                STD_OFF
#define ICU_GTM_TIM2_CH1_ISR_API                                                STD_OFF
#define ICU_GTM_TIM2_CH2_ISR_API                                                STD_OFF
#define ICU_GTM_TIM2_CH3_ISR_API                                                STD_OFF
#define ICU_GTM_TIM2_CH4_ISR_API                                                STD_OFF
#define ICU_GTM_TIM2_CH5_ISR_API                                                STD_OFF
#define ICU_GTM_TIM2_CH6_ISR_API                                                STD_OFF
#define ICU_GTM_TIM2_CH7_ISR_API                                                STD_OFF
#define ICU_GTM_TIM3_CH0_ISR_API                                                STD_OFF
#define ICU_GTM_TIM3_CH1_ISR_API                                                STD_OFF
#define ICU_GTM_TIM3_CH2_ISR_API                                                STD_OFF
#define ICU_GTM_TIM3_CH3_ISR_API                                                STD_OFF
#define ICU_GTM_TIM3_CH4_ISR_API                                                STD_OFF
#define ICU_GTM_TIM3_CH5_ISR_API                                                STD_OFF
#define ICU_GTM_TIM3_CH6_ISR_API                                                STD_OFF
#define ICU_GTM_TIM3_CH7_ISR_API                                                STD_OFF
#define ICU_GTM_TIM4_CH0_ISR_API                                                STD_OFF
#define ICU_GTM_TIM4_CH1_ISR_API                                                STD_OFF
#define ICU_GTM_TIM4_CH2_ISR_API                                                STD_OFF
#define ICU_GTM_TIM4_CH3_ISR_API                                                STD_OFF
#define ICU_GTM_TIM4_CH4_ISR_API                                                STD_OFF
#define ICU_GTM_TIM4_CH5_ISR_API                                                STD_OFF
#define ICU_GTM_TIM4_CH6_ISR_API                                                STD_OFF
#define ICU_GTM_TIM4_CH7_ISR_API                                                STD_OFF
#define ICU_GTM_TIM5_CH0_ISR_API                                                STD_OFF
#define ICU_GTM_TIM5_CH1_ISR_API                                                STD_OFF
#define ICU_GTM_TIM5_CH2_ISR_API                                                STD_OFF
#define ICU_GTM_TIM5_CH3_ISR_API                                                STD_OFF
#define ICU_GTM_TIM5_CH4_ISR_API                                                STD_OFF
#define ICU_GTM_TIM5_CH5_ISR_API                                                STD_OFF
#define ICU_GTM_TIM5_CH6_ISR_API                                                STD_OFF
#define ICU_GTM_TIM5_CH7_ISR_API                                                STD_OFF
#define ICU_GTM_TIM6_CH0_ISR_API                                                STD_OFF
#define ICU_GTM_TIM6_CH1_ISR_API                                                STD_OFF
#define ICU_GTM_TIM6_CH2_ISR_API                                                STD_OFF
#define ICU_GTM_TIM6_CH3_ISR_API                                                STD_OFF
#define ICU_GTM_TIM6_CH4_ISR_API                                                STD_OFF
#define ICU_GTM_TIM6_CH5_ISR_API                                                STD_OFF
#define ICU_GTM_TIM6_CH6_ISR_API                                                STD_OFF
#define ICU_GTM_TIM6_CH7_ISR_API                                                STD_OFF
#define ICU_EXT_INTP_CH00_ISR_API                                               STD_OFF
#define ICU_EXT_INTP_CH01_ISR_API                                               STD_OFF
#define ICU_EXT_INTP_CH02_ISR_API                                               STD_OFF
#define ICU_EXT_INTP_CH03_ISR_API                                               STD_OFF
#define ICU_EXT_INTP_CH04_ISR_API                                               STD_OFF
#define ICU_EXT_INTP_CH05_ISR_API                                               STD_OFF
#define ICU_EXT_INTP_CH06_ISR_API                                               STD_OFF
#define ICU_EXT_INTP_CH07_ISR_API                                               STD_OFF
#define ICU_EXT_INTP_CH08_ISR_API                                               STD_OFF
#define ICU_EXT_INTP_CH09_ISR_API                                               STD_OFF
#define ICU_EXT_INTP_CH10_ISR_API                                               STD_OFF
#define ICU_EXT_INTP_CH11_ISR_API                                               STD_OFF
#define ICU_EXT_INTP_CH12_ISR_API                                               STD_OFF
#define ICU_EXT_INTP_CH13_ISR_API                                               STD_OFF
#define ICU_EXT_INTP_CH14_ISR_API                                               STD_OFF
#define ICU_EXT_INTP_CH15_ISR_API                                               STD_OFF
#define ICU_EXT_INTP_CH16_ISR_API                                               STD_OFF
#define ICU_EXT_INTP_CH17_ISR_API                                               STD_OFF
#define ICU_EXT_INTP_CH18_ISR_API                                               STD_OFF
#define ICU_EXT_INTP_CH19_ISR_API                                               STD_OFF
#define ICU_EXT_INTP_CH20_ISR_API                                               STD_OFF
#define ICU_EXT_INTP_CH21_ISR_API                                               STD_OFF
#define ICU_EXT_INTP_CH22_ISR_API                                               STD_OFF
#define ICU_EXT_INTP_CH23_ISR_API                                               STD_OFF
#define ICU_EXT_INTP_CH24_ISR_API                                               STD_OFF
#define ICU_EXT_INTP_CH25_ISR_API                                               STD_OFF
#define ICU_EXT_INTP_CH26_ISR_API                                               STD_OFF
#define ICU_EXT_INTP_CH27_ISR_API                                               STD_OFF
#define ICU_EXT_INTP_CH28_ISR_API                                               STD_OFF
#define ICU_EXT_INTP_CH29_ISR_API                                               STD_OFF
#define ICU_EXT_INTP_CH30_ISR_API                                               STD_OFF
#define ICU_EXT_INTP_CH31_ISR_API                                               STD_OFF
#define ICU_EXT_INTP_CH32_ISR_API                                               STD_OFF
#define ICU_EXT_INTP_CH33_ISR_API                                               STD_OFF
#define ICU_EXT_INTP_CH34_ISR_API                                               STD_OFF
#define ICU_EXT_INTP_CH35_ISR_API                                               STD_OFF
#define ICU_EXT_INTP_CH36_ISR_API                                               STD_OFF
#define ICU_EXT_INTP_CH37_ISR_API                                               STD_OFF
#define ICU_EXT_INTP_CH38_ISR_API                                               STD_OFF
#define ICU_EXT_INTP_CH39_ISR_API                                               STD_OFF
#define ICU_EXT_INTP_CH40_ISR_API                                               STD_OFF
#define ICU_EXT_INTP_CH41_ISR_API                                               STD_OFF
#define ICU_EXT_INTP_CH42_ISR_API                                               STD_OFF
#define ICU_EXT_INTP_CH43_ISR_API                                               STD_OFF
#define ICU_EXT_INTP_CH44_ISR_API                                               STD_OFF
#define ICU_EXT_INTP_CH45_ISR_API                                               STD_OFF




/***********************************************************************************************************************
**                      Global Data Types                                                                             **
***********************************************************************************************************************/
/* ICU Channel Handles */
#define IcuConf_IcuChannel_IcuChannel_TIM00                                     (Icu_ChannelType)0x00U


/***********************************************************************************************************************
**                      Global Data                                                                                   **
***********************************************************************************************************************/
/* Channel Mapping for Timer and External Unit Channels */
#define ICU_GTM_TIM0_CH0                                                        0x00U

/* Configuration Set Handles */
#define Icu_Config                                                              (&Icu_GaaConfiguration[0])



/***********************************************************************************************************************
**                      Function Prototypes                                                                           **
***********************************************************************************************************************/



#endif /* ICU_CFG_H */


/***********************************************************************************************************************
**                      End of File                                                                                   **
***********************************************************************************************************************/

