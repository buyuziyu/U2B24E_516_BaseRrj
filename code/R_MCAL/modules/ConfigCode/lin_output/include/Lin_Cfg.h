/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Lin_Cfg.h                                                                                           */
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
/* TOOL VERSION:  LinU2Bx-E.dll version: 2.4.1, MCALConfGen.exe version: 2.3.0                                        */
/*                                                                                                                    */


/***********************************************************************************************************************
**                      Input File                                                                                    **
***********************************************************************************************************************/
/*
 * INPUT FILE:    C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\MCAL_RH850U2B24E_516_CodeGen\U2B24-E.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\modules\lin\generator\U2B24-E\R2211_lin_U2B24-E_BSWMDT.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\Dem\xml\Dem_lin.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\EcuM\xml\EcuM_lin.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\Os\xml\Os_lin.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\EcuC\xml\EcuC_lin.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\MCAL_RH850U2B24E_516_CodeGen\Translation.trxml
 * GENERATED ON:  10 Jul 2026 - 18:49:41
 */


#ifndef LIN_CFG_H
#define LIN_CFG_H


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
#define LIN_CFG_AR_RELEASE_MAJOR_VERSION                                        4U
#define LIN_CFG_AR_RELEASE_MINOR_VERSION                                        8U
#define LIN_CFG_AR_RELEASE_REVISION_VERSION                                     0U

/* File version information */
#define LIN_CFG_SW_MAJOR_VERSION                                                2U
#define LIN_CFG_SW_MINOR_VERSION                                                4U

/***********************************************************************************************************************
**                      Common Published Information                                                                  **
***********************************************************************************************************************/
#define LIN_AR_RELEASE_MAJOR_VERSION_VALUE                                      4U
#define LIN_AR_RELEASE_MINOR_VERSION_VALUE                                      8U
#define LIN_AR_RELEASE_REVISION_VERSION_VALUE                                   0U

#define LIN_SW_MAJOR_VERSION_VALUE                                              2U
#define LIN_SW_MINOR_VERSION_VALUE                                              4U
#define LIN_SW_PATCH_VERSION_VALUE                                              1U

#define LIN_VENDOR_ID_VALUE                                                     59U
#define LIN_MODULE_ID_VALUE                                                     82U

/***********************************************************************************************************************
**                      Global Symbols                                                                                **
***********************************************************************************************************************/


/* Pre-compile option for Version information */
#define LIN_AR_VERSION                                                          LIN_AR_R22_11_VERSION

/* Instance ID of the LIN Driver */
#define LIN_INSTANCE_ID_VALUE                                                   0U

/* Maximum LIN Channel Id */
#define LIN_MAX_CHANNEL_ID                                                      (uint8)0x05

/* Number of configured LIN Channels */
#define LIN_NO_OF_CHANNELS                                                      (uint8)0x06

/* User define value for Endless Loop */
#define LIN_TIMEOUT_DURATION                                                    (uint16)0x0032


/* Maximum Core Support in Multi Core */
#define LIN_SUPPORTED_CORE_MAX_NUM                                              (uint8)0x07

/* The Number of Core Configuration */
#define LIN_CONFIGURED_CORE_NUM                                                 (uint8)0x02

/* Enables/Disables Support Multi Core */
#define LIN_MULTI_CORE_SUPPORT                                                  STD_ON

/* Enables/Disables GetVersionInfo API */
#define LIN_VERSION_INFO_API                                                    STD_ON

/* Enables/Disables version check of LIN with dependent module */
#define LIN_VERSION_CHECK_EXT_MODULES                                           STD_ON

/* Enables/Disables critical section protection */
#define LIN_CRITICAL_SECTION_PROTECTION                                         STD_ON

/* Enables/Disables Development error detection */
#define LIN_DEV_ERROR_DETECT                                                    STD_OFF

/* Enables/Disables LIN_INTERRUPT_CONSISTENCY_CHECK */
#define LIN_INTERRUPT_CONSISTENCY_CHECK                                         STD_OFF


/* Enables/Disables the wake up functionality */
#define LIN_WAKEUP_SUPPORT                                                      STD_ON

/* Enables/Disables the master mode */
#define LIN_MASTER_MODE_SUPPORT                                                 STD_ON

/* Enables/Disables the slave mode */
#define LIN_SLAVE_MODE_SUPPORT                                                  STD_ON

/* Enables/Disables LIN_ISR_CATEGORY_2 */
#define LIN_ISR_CATEGORY_2                                                      STD_OFF

/* Enables/Disables Mux interrupt */
#define LIN_INTERRUPT_MUX_SUPPORT                                               STD_OFF

/* Configured and Unused Channels */
#define LIN_CHANNEL0_CONFIGURED                                                 STD_ON
#define LIN_CHANNEL1_CONFIGURED                                                 STD_ON
#define LIN_CHANNEL2_CONFIGURED                                                 STD_ON
#define LIN_CHANNEL3_CONFIGURED                                                 STD_ON
#define LIN_CHANNEL4_CONFIGURED                                                 STD_ON
#define LIN_CHANNEL5_CONFIGURED                                                 STD_ON
#define LIN_CHANNEL6_CONFIGURED                                                 STD_OFF
#define LIN_CHANNEL7_CONFIGURED                                                 STD_OFF
#define LIN_CHANNEL8_CONFIGURED                                                 STD_OFF
#define LIN_CHANNEL9_CONFIGURED                                                 STD_OFF
#define LIN_CHANNEL10_CONFIGURED                                                STD_OFF
#define LIN_CHANNEL11_CONFIGURED                                                STD_OFF
#define LIN_CHANNEL12_CONFIGURED                                                STD_OFF
#define LIN_CHANNEL13_CONFIGURED                                                STD_OFF
#define LIN_CHANNEL14_CONFIGURED                                                STD_OFF
#define LIN_CHANNEL15_CONFIGURED                                                STD_OFF
#define LIN_CHANNEL16_CONFIGURED                                                STD_OFF
#define LIN_CHANNEL17_CONFIGURED                                                STD_OFF
#define LIN_CHANNEL18_CONFIGURED                                                STD_OFF
#define LIN_CHANNEL19_CONFIGURED                                                STD_OFF
#define LIN_CHANNEL20_CONFIGURED                                                STD_OFF
#define LIN_CHANNEL21_CONFIGURED                                                STD_OFF
#define LIN_CHANNEL22_CONFIGURED                                                STD_OFF
#define LIN_CHANNEL23_CONFIGURED                                                STD_OFF

/* Pre-compile option for Hardware to Channel Mapping for Interrupt */
#define LIN_CHANNEL0                                                            (uint8)0x00
#define LIN_CHANNEL1                                                            (uint8)0x01
#define LIN_CHANNEL2                                                            (uint8)0x02
#define LIN_CHANNEL3                                                            (uint8)0x03
#define LIN_CHANNEL4                                                            (uint8)0x04
#define LIN_CHANNEL5                                                            (uint8)0x05

/* Channel Handles */
#define LinConf_LinChannel_LinChannel                                           (uint8)0x00
#define LinConf_LinChannel_LinChannel_001                                       (uint8)0x01
#define LinConf_LinChannel_LinChannel_002                                       (uint8)0x02
#define LinConf_LinChannel_LinChannel_003                                       (uint8)0x03
#define LinConf_LinChannel_LinChannel_004                                       (uint8)0x04
#define LinConf_LinChannel_LinChannel_005                                       (uint8)0x05

/* Configuration Set Handles */
#define Lin_Config                                                              (&Lin_GaaConfiguration[0])


/***********************************************************************************************************************
**                      Global Data Types                                                                             **
***********************************************************************************************************************/



/***********************************************************************************************************************
**                      Global Data                                                                                   **
***********************************************************************************************************************/



/***********************************************************************************************************************
**                      Function Prototypes                                                                           **
***********************************************************************************************************************/



#endif /* LIN_CFG_H */


/***********************************************************************************************************************
**                      End of File                                                                                   **
***********************************************************************************************************************/

