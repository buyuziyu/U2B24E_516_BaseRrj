/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Adc_Cfg.h                                                                                           */
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
/* TOOL VERSION:  AdcU2Bx-E.dll version: 2.5.1, MCALConfGen.exe version: 2.3.0                                        */
/*                                                                                                                    */


/***********************************************************************************************************************
**                      Input File                                                                                    **
***********************************************************************************************************************/
/*
 * INPUT FILE:    C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\MCAL_RH850U2B24E_516_CodeGen\U2B24-E.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\modules\adc\generator\U2B24-E\R2211_adc_U2B24-E_BSWMDT.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\Dem\xml\Dem_adc.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\Os\xml\Os_adc.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\EcuC\xml\EcuC_adc.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\MCAL_RH850U2B24E_516_CodeGen\Translation.trxml
 * GENERATED ON:  10 Jul 2026 - 18:49:17
 */


#ifndef ADC_CFG_H
#define ADC_CFG_H


/***********************************************************************************************************************
**                      Include Section                                                                               **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                      Coding Rule Violations                                                                        **
***********************************************************************************************************************/
/**********************************************************************************************************************/
/* Message (7:0791)    : [U] Macro identifier does not differ from other macro identifier(s) (e.g. '%s') within       */
/*                       the specified number of significant characters.                                              */
/* Rule                : CERTCCM DCL23, MISRA C:2012 Rule-5.4                                                         */
/* JV-01 Justification : This macro identifier is following AUTOSAR standard rule (Symbolic Name or Published         */
/*                       Macro's name), so this is accepted.                                                          */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1534)    : The macro '%1s' is declared but not used within this project.                                */
/* Rule                : MISRA C:2012 Rule-2.5                                                                        */
/* JV-01 Justification : This is accepted. This macro is used by other file.                                          */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/


/***********************************************************************************************************************
**                      Version Information                                                                           **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define ADC_CFG_AR_RELEASE_MAJOR_VERSION                                        4U                                      /* PRQA S 1534 # JV-01 */
#define ADC_CFG_AR_RELEASE_MINOR_VERSION                                        8U                                      /* PRQA S 1534 # JV-01 */
#define ADC_CFG_AR_RELEASE_REVISION_VERSION                                     0U                                      /* PRQA S 1534 # JV-01 */

/* File version information */
#define ADC_CFG_SW_MAJOR_VERSION                                                2U                                      /* PRQA S 1534 # JV-01 */
#define ADC_CFG_SW_MINOR_VERSION                                                5U                                      /* PRQA S 1534 # JV-01 */

/***********************************************************************************************************************
**                      Common Published Information                                                                  **
***********************************************************************************************************************/
#define ADC_AR_RELEASE_MAJOR_VERSION_VALUE                                      4U                                      /* PRQA S 1534 # JV-01 */
#define ADC_AR_RELEASE_MINOR_VERSION_VALUE                                      8U                                      /* PRQA S 1534 # JV-01 */
#define ADC_AR_RELEASE_REVISION_VERSION_VALUE                                   0U                                      /* PRQA S 1534 # JV-01 */

#define ADC_SW_MAJOR_VERSION_VALUE                                              2U                                      /* PRQA S 1534 # JV-01 */
#define ADC_SW_MINOR_VERSION_VALUE                                              5U                                      /* PRQA S 1534 # JV-01 */
#define ADC_SW_PATCH_VERSION_VALUE                                              1U                                      /* PRQA S 1534 # JV-01 */

#define ADC_VENDOR_ID_VALUE                                                     59U                                     /* PRQA S 1534 # JV-01 */
#define ADC_MODULE_ID_VALUE                                                     123U                                    /* PRQA S 1534 # JV-01 */

/***********************************************************************************************************************
**                      Global Symbols                                                                                **
***********************************************************************************************************************/


/* Instance ID of the ADC Driver */
#define ADC_INSTANCE_ID_VALUE                                                   0U
/* Pre-compile option for Version information */
#define ADC_AR_VERSION                                                          ADC_AR_R22_11_VERSION
/* Device IP of the ADC Driver U2Cx */
#define ADC_IP_C_ADCK                                                           STD_OFF
/* Device IP of the ADC Driver */
#define ADC_IP_ADCK                                                             STD_ON
/* Device IP of the ADC Driver */
#define ADC_IP_ADCJ                                                             STD_OFF
/* Device IP of the ADC Driver */
#define ADC_IP_ADCH                                                             STD_OFF
/* Define the macro definitions and structure declarations */
#define ADC_HWIP_PBTYPES_H_FILE                                                 "Adc_ADCK_PBTypes.h"
/* Define the declaration of internal function prototypes */
#define ADC_HWIP_LLDRIVER_H_FILE                                                "Adc_ADCK_LLDriver.h"
/* Enable/Disable Track and Hold Physical IO Select */
#define ADC_TRACK_AND_HOLD_CHANNEL_IO_SELECT                                    STD_ON
/* Number of hardware units configured */
#define ADC_MAX_HW_UNITS                                                        2U
/* Number of max SW trigger */
#define ADC_MAX_SW_TRIGGER                                                      0x07U                                   /* PRQA S 1534 # JV-01 */
/* Number of max HW trigger */
#define ADC_MAX_HW_TRIGGER                                                      0x01U                                   /* PRQA S 1534 # JV-01 */
/* Enables/Disables GetVersionInfo API */
#define ADC_VERSION_INFO_API                                                    STD_ON                                  /* PRQA S 1534 # JV-01 */
/* Enables/Disables the inclusion of Adc_DeInit API */
#define ADC_DEINIT_API                                                          STD_ON                                  /* PRQA S 1534 # JV-01 */
/* Enables/Disables Adc_StartGroupConversion and Adc_StopGroupConversion */
#define ADC_ENABLE_START_STOP_GROUP_API                                         STD_ON                                  /* PRQA S 1534 # JV-01 */
/* Enables/Disables Adc_EnableHardwareTrigger and Adc_DisableHardwareTrigger functions */
#define ADC_HW_TRIGGER_API                                                      STD_ON                                  /* PRQA S 1534 # JV-01 */
/* Enables/Disables Adc_ReadGroup function */
#define ADC_READ_GROUP_API                                                      STD_ON                                  /* PRQA S 1534 # JV-01 */
/* Enables/Disables Adc_EnableChannel and Adc_DisableChannel functions */
#define ADC_ENABLE_DISABLE_CHANNEL                                              STD_ON                                  /* PRQA S 1534 # JV-01 */
/* Enables/Disables Development error detection */
#define ADC_DEV_ERROR_DETECT                                                    STD_OFF                                 /* PRQA S 1534 # JV-01 */
/* Enables/Disables the inclusion of first come first serve mechanism */
#define ADC_ENABLE_QUEUING                                                      STD_OFF                                 /* PRQA S 1534 # JV-01 */
/* Enables/Disables Notification functions */
#define ADC_GRP_NOTIF_CAPABILITY                                                STD_ON                                  /* PRQA S 1534 # JV-01 */
/* Enables/Disables limit checking functionality */
#define ADC_ENABLE_LIMIT_CHECK                                                  STD_OFF                                 /* PRQA S 1534 # JV-01 */
/* Enables/Disables the Overwrite Error feature */
#define ADC_ENABLE_OVERWRITE_ERR                                                STD_OFF                                 /* PRQA S 1534 # JV-01 */
/* Enables/Disables the Trigger Overlap Error feature */
#define ADC_ENABLE_TRIGGER_OVERLAP_ERR                                          STD_ON                                  /* PRQA S 1534 # JV-01 */
/* Enables/Disables DMA ISR for DMA channel */
#define ADC_ENABLE_DMA_MODE                                                     STD_ON                                  /* PRQA S 1534 # JV-01 */
/* Enables/Disables the enter/exit critical section functionality */
#define ADC_CRITICAL_SECTION_PROTECTION                                         STD_ON                                  /* PRQA S 1534 # JV-01 */
/* Enables/Disables version check of Adc with dependent module */
#define ADC_VERSION_CHECK_EXT_MODULES                                           STD_ON                                  /* PRQA S 1534 # JV-01 */
/* Enables/Disables the ADC_E_ALREADY_INITIALIZED Det check in Adc_Init API */
#define ADC_ALREADY_INIT_DET_CHECK                                              STD_ON                                  /* PRQA S 1534 # JV-01 */
/* Enables/Disables the streaming functionality */
#define ADC_ENABLE_STREAMING                                                    STD_ON                                  /* PRQA S 1534 # JV-01 */
/* Enables/Disables the self diagnostics */
#define ADC_ENABLE_SELF_DIAG                                                    STD_ON                                  /* PRQA S 1534 # JV-01 */
/* Enables/Disables the AD timer trigger feature to logical groups */
#define ADC_ENABLE_ADTIMER                                                      STD_ON                                  /* PRQA S 1534 # JV-01 */
/* Enable/Disable Track and Hold feature */
#define ADC_TRACK_AND_HOLD                                                      STD_OFF                                 /* PRQA S 1534 # JV-01 */
/* Enable/Disable PWM-Diag feature */
#define ADC_ENABLE_PWM_DIAG                                                     STD_OFF                                 /* PRQA S 1534 # JV-01 */
/* Enables/Disables Multi Core feature */
#define ADC_MULTI_CORE_SUPPORT                                                  STD_ON                                  /* PRQA S 1534 # JV-01 */
/* Enables/Disables ISR for SG0 unit of HW 0 */
#define ADC0_SG0_ISR_API                                                        STD_OFF
/* Enables/Disables ISR for SG1 unit of HW 0 */
#define ADC0_SG1_ISR_API                                                        STD_ON
/* Enables/Disables ISR for SG2 unit of HW 0 */
#define ADC0_SG2_ISR_API                                                        STD_OFF
/* Enables/Disables ISR for SG3 unit of HW 0 */
#define ADC0_SG3_ISR_API                                                        STD_OFF
/* Enables/Disables ISR for SG4 unit of HW 0 */
#define ADC0_SG4_ISR_API                                                        STD_OFF
/* Enables/Disables ISR for SG0 unit of HW 1 */
#define ADC1_SG0_ISR_API                                                        STD_OFF
/* Enables/Disables ISR for SG1 unit of HW 1 */
#define ADC1_SG1_ISR_API                                                        STD_ON
/* Enables/Disables ISR for SG2 unit of HW 1 */
#define ADC1_SG2_ISR_API                                                        STD_OFF
/* Enables/Disables ISR for SG3 unit of HW 1 */
#define ADC1_SG3_ISR_API                                                        STD_OFF
/* Enables/Disables ISR for SG4 unit of HW 1 */
#define ADC1_SG4_ISR_API                                                        STD_OFF
/* Enables/Disables ISR for SG0 unit of HW 2 */
#define ADC2_SG0_ISR_API                                                        STD_OFF
/* Enables/Disables ISR for SG1 unit of HW 2 */
#define ADC2_SG1_ISR_API                                                        STD_OFF
/* Enables/Disables ISR for SG2 unit of HW 2 */
#define ADC2_SG2_ISR_API                                                        STD_OFF
/* Enables/Disables ISR for SG3 unit of HW 2 */
#define ADC2_SG3_ISR_API                                                        STD_OFF
/* Enables/Disables ISR for SG4 unit of HW 2 */
#define ADC2_SG4_ISR_API                                                        STD_OFF
/* Enables/Disables ISR for SG0 unit of HW 3 */
#define ADC3_SG0_ISR_API                                                        STD_OFF
/* Enables/Disables ISR for SG1 unit of HW 3 */
#define ADC3_SG1_ISR_API                                                        STD_OFF
/* Enables/Disables ISR for SG2 unit of HW 3 */
#define ADC3_SG2_ISR_API                                                        STD_OFF
/* Enables/Disables ISR for SG3 unit of HW 3 */
#define ADC3_SG3_ISR_API                                                        STD_OFF
/* Enables/Disables ISR for SG4 unit of HW 3 */
#define ADC3_SG4_ISR_API                                                        STD_OFF
/* Enables/Disables ISR for SG0 unit of HW A */
#define ADCA_SG0_ISR_API                                                        STD_OFF
/* Enables/Disables ISR for SG1 unit of HW A */
#define ADCA_SG1_ISR_API                                                        STD_OFF
/* Enables/Disables ISR for SG2 unit of HW A */
#define ADCA_SG2_ISR_API                                                        STD_OFF
/* Enables/Disables ISR for SG3 unit of HW A */
#define ADCA_SG3_ISR_API                                                        STD_OFF
/* Enables/Disables ISR for SG4 unit of HW A */
#define ADCA_SG4_ISR_API                                                        STD_OFF
/* Enables/Disables DMA ISR for channel 00 of HW 0 */
#define ADC_DMA0_ISR_CH00_API                                                   STD_ON
/* Enables/Disables DMA ISR for channel 01 of HW 0 */
#define ADC_DMA0_ISR_CH01_API                                                   STD_OFF
/* Enables/Disables DMA ISR for channel 02 of HW 0 */
#define ADC_DMA0_ISR_CH02_API                                                   STD_OFF
/* Enables/Disables DMA ISR for channel 03 of HW 0 */
#define ADC_DMA0_ISR_CH03_API                                                   STD_OFF
/* Enables/Disables DMA ISR for channel 04 of HW 0 */
#define ADC_DMA0_ISR_CH04_API                                                   STD_OFF
/* Enables/Disables DMA ISR for channel 05 of HW 0 */
#define ADC_DMA0_ISR_CH05_API                                                   STD_ON
/* Enables/Disables DMA ISR for channel 06 of HW 0 */
#define ADC_DMA0_ISR_CH06_API                                                   STD_OFF
/* Enables/Disables DMA ISR for channel 07 of HW 0 */
#define ADC_DMA0_ISR_CH07_API                                                   STD_OFF
/* Enables/Disables DMA ISR for channel 08 of HW 0 */
#define ADC_DMA0_ISR_CH08_API                                                   STD_OFF
/* Enables/Disables DMA ISR for channel 09 of HW 0 */
#define ADC_DMA0_ISR_CH09_API                                                   STD_OFF
/* Enables/Disables DMA ISR for channel 10 of HW 0 */
#define ADC_DMA0_ISR_CH10_API                                                   STD_OFF
/* Enables/Disables DMA ISR for channel 11 of HW 0 */
#define ADC_DMA0_ISR_CH11_API                                                   STD_OFF
/* Enables/Disables DMA ISR for channel 12 of HW 0 */
#define ADC_DMA0_ISR_CH12_API                                                   STD_OFF
/* Enables/Disables DMA ISR for channel 13 of HW 0 */
#define ADC_DMA0_ISR_CH13_API                                                   STD_OFF
/* Enables/Disables DMA ISR for channel 14 of HW 0 */
#define ADC_DMA0_ISR_CH14_API                                                   STD_OFF
/* Enables/Disables DMA ISR for channel 15 of HW 0 */
#define ADC_DMA0_ISR_CH15_API                                                   STD_OFF
/* Enables/Disables DMA ISR for channel 00 of HW 1 */
#define ADC_DMA1_ISR_CH00_API                                                   STD_OFF
/* Enables/Disables DMA ISR for channel 01 of HW 1 */
#define ADC_DMA1_ISR_CH01_API                                                   STD_OFF
/* Enables/Disables DMA ISR for channel 02 of HW 1 */
#define ADC_DMA1_ISR_CH02_API                                                   STD_OFF
/* Enables/Disables DMA ISR for channel 03 of HW 1 */
#define ADC_DMA1_ISR_CH03_API                                                   STD_OFF
/* Enables/Disables DMA ISR for channel 04 of HW 1 */
#define ADC_DMA1_ISR_CH04_API                                                   STD_OFF
/* Enables/Disables DMA ISR for channel 05 of HW 1 */
#define ADC_DMA1_ISR_CH05_API                                                   STD_OFF
/* Enables/Disables DMA ISR for channel 06 of HW 1 */
#define ADC_DMA1_ISR_CH06_API                                                   STD_OFF
/* Enables/Disables DMA ISR for channel 07 of HW 1 */
#define ADC_DMA1_ISR_CH07_API                                                   STD_OFF
/* Enables/Disables DMA ISR for channel 08 of HW 1 */
#define ADC_DMA1_ISR_CH08_API                                                   STD_OFF
/* Enables/Disables DMA ISR for channel 09 of HW 1 */
#define ADC_DMA1_ISR_CH09_API                                                   STD_OFF
/* Enables/Disables DMA ISR for channel 10 of HW 1 */
#define ADC_DMA1_ISR_CH10_API                                                   STD_OFF
/* Enables/Disables DMA ISR for channel 11 of HW 1 */
#define ADC_DMA1_ISR_CH11_API                                                   STD_OFF
/* Enables/Disables DMA ISR for channel 12 of HW 1 */
#define ADC_DMA1_ISR_CH12_API                                                   STD_OFF
/* Enables/Disables DMA ISR for channel 13 of HW 1 */
#define ADC_DMA1_ISR_CH13_API                                                   STD_OFF
/* Enables/Disables DMA ISR for channel 14 of HW 1 */
#define ADC_DMA1_ISR_CH14_API                                                   STD_OFF
/* Enables/Disables DMA ISR for channel 15 of HW 1 */
#define ADC_DMA1_ISR_CH15_API                                                   STD_OFF
/* Enables/Disables the Error feature */
#define ADC_ENABLE_ERR                                                          STD_ON
/* Enables/Disables the Error interrupt */
#define ADC_ENABLE_ERR_INT                                                      STD_ON
/* Enables/Disables parity error interrupt */
#define ADC_ENABLE_PARITY_ERR_INT                                               STD_OFF
/* Enables/Disables the Pin Level self diagnostics */
#define ADC_ENABLE_SELF_DIAG_PIN_LVL                                            STD_OFF
/* Enables/Disables the Wire break self diagnostics */
#define ADC_ENABLE_SELF_DIAG_WIRE_BRK                                           STD_OFF
/* Enables/Disables the Wiring break detection result check */
#define ADC_ENABLE_WIRE_BRK                                                     STD_OFF
/* Select the support interrupt category */
#define ADC_ISR_CATEGORY_2                                                      STD_OFF
/* Enable/Disable PIC Trigger selection */
#define ADC_ENABLE_PIC_TSEL                                                     STD_ON
/* Enable/Disable PIC Common Trigger selection */
#define ADC_ENABLE_PIC_COMMON                                                   STD_OFF
/* Enable/Disable ADC Trigger selection */
#define ADC_ENABLE_ADC_TSEL                                                     STD_OFF
/* Number of PIC Trigger Output Selection Control Register */
#define ADC_NUM_OF_PIC_SELECT                                                   5U
/* Number of PIC Trigger Output Control Register */
#define ADC_NUM_OF_PIC_CONTROL                                                  1U
/* Enables/Disables priority mechanism functions */
#define ADC_PRIORITY_IMPLEMENTATION                                             ADC_PRIORITY_NONE
/* Functionality mode type */
#define ADC_FUNCTIONALITY_MODE                                                  ADC_POLLING_INTERRUPT
/* ADC result alignment */
#define ADC_RESULT_ALIGNMENT                                                    ADC_ALIGN_RIGHT
/* ADC result data type */
#define ADC_RESULT_DATA_TYPE                                                    ADC_RESULT_DATA_16_BITS
/* Mask of the AIR_DSELR0 register */
#define ADC_DMATRANSFER_REQUEST                                                 ((uint32)0xFFFB7EDFUL)
/* Mask of the AIR_ISELR0 register */
#define ADC_INTERRUPT_REQUEST                                                   ((uint32)0xFAFF7FDFUL)
/* Error Interrupt check mask */
#define ADC_ERR_INT_MASK                                                        (uint8)0x40
/* Align right mask */
#define ADC_ALIGN_RIGHT_MASK                                                    (uint8)0x10
/* Address of the ADC_AIR_ISELR0 register */
#define ADC_AIR_ISELR0                                                          (*((volatile uint32 *)0xFFCB2500UL))
/* Address of the ADC_AIR_DSELR0 register */
#define ADC_AIR_DSELR0                                                          (*((volatile uint32 *)0xFFCB2508UL))
/* Enables/Disables the ECM Interrupt consistency check */
#define ADC_ECM_INTERRUPT_CONSISTENCY_CHECK                                     STD_OFF
/* Enables/Disables the Interrupt consistency check */
#define ADC_INTERRUPT_CONSISTENCY_CHECK                                         STD_OFF
/* Enables/Disables the Id Error feature */
#define ADC_ENABLE_ID_ERR                                                       STD_OFF
/* Enables/Disables the Parity Error feature */
#define ADC_ENABLE_PARITY_ERR                                                   STD_OFF
/* Adc timeout caused by hardware error */
#define ADC_E_TIMEOUT                                                           \
                                                                         DemConf_DemEventParameter_DemEventParameter_004
/* Configuration Set Handles */
#define Adc_Config                                                              (&Adc_GaaConfiguration[0])              /* PRQA S 1534 # JV-01 */
/* Group Handles */
#define AdcConf_AdcGroup_AdcGroup_000                                           (Adc_GroupType)0x00                     /* PRQA S 1534 # JV-01 */
#define AdcConf_AdcGroup_AdcGroup_001                                           (Adc_GroupType)0x01                     /* PRQA S 1534 # JV-01 */
#define AdcConf_AdcGroup_AdcGroup_002                                           (Adc_GroupType)0x02                     /* PRQA S 1534 # JV-01 */
#define AdcConf_AdcGroup_AdcGroup_003                                           (Adc_GroupType)0x07                     /* PRQA S 1534 # JV-01 */
#define AdcConf_AdcGroup_AdcGroup_100                                           (Adc_GroupType)0x03                     /* PRQA S 1534 # JV-01 */
#define AdcConf_AdcGroup_AdcGroup_101                                           (Adc_GroupType)0x04                     /* PRQA S 1534 # JV-01 */
#define AdcConf_AdcGroup_AdcGroup_102                                           (Adc_GroupType)0x05                     /* PRQA S 1534 # JV-01 */
#define AdcConf_AdcGroup_AdcGroup_103                                           (Adc_GroupType)0x06                     /* PRQA S 1534 # JV-01 */
/* ADC Channel Handles */
#define AdcConf_AdcChannel_AdcChannel_000                                       (Adc_ChannelType)0x04                   /* PRQA S 1534 # JV-01 */
#define AdcConf_AdcChannel_AdcChannel_001                                       (Adc_ChannelType)0x05                   /* PRQA S 1534 # JV-01 */
#define AdcConf_AdcChannel_AdcChannel_002                                       (Adc_ChannelType)0x07                   /* PRQA S 1534 # JV-01 */
#define AdcConf_AdcChannel_AdcChannel_003                                       (Adc_ChannelType)0x0D                   /* PRQA S 1534 # JV-01 */
#define AdcConf_AdcChannel_AdcChannel_004                                       (Adc_ChannelType)0x06                   /* PRQA S 1534 # JV-01 */
#define AdcConf_AdcChannel_AdcChannel_005                                       (Adc_ChannelType)0x07                   /* PRQA S 1534 # JV-01 */
#define AdcConf_AdcChannel_AdcChannel_006                                       (Adc_ChannelType)0x0C                   /* PRQA S 1534 # JV-01 */
#define AdcConf_AdcChannel_AdcChannel_007                                       (Adc_ChannelType)0x0F                   /* PRQA S 1534 # JV-01 */

/***********************************************************************************************************************
**                      Global Data Types                                                                             **
***********************************************************************************************************************/



/***********************************************************************************************************************
**                      Global Data                                                                                   **
***********************************************************************************************************************/



/***********************************************************************************************************************
**                      Function Prototypes                                                                           **
***********************************************************************************************************************/



#endif /* ADC_CFG_H */


/***********************************************************************************************************************
**                      End of File                                                                                   **
***********************************************************************************************************************/

