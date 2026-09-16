/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Dio_Cfg.h                                                                                           */
/*====================================================================================================================*/
/*                                  COPYRIGHT                                                                         */
/*====================================================================================================================*/
/* (c) 2023, 2024 Renesas Electronics Corporation. All rights reserved.                                               */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains pre-compile time parameters                                                                     */
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
/* TOOL VERSION:  DioU2Bx-E.dll version: 2.4.1, MCALConfGen.exe version: 2.3.0                                        */
/*                                                                                                                    */


/***********************************************************************************************************************
**                      Input File                                                                                    **
***********************************************************************************************************************/
/*
 * INPUT FILE:    C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\MCAL_RH850U2B24E_516_CodeGen\U2B24-E.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\modules\dio\generator\U2B24-E\R2211_dio_U2B24-E_BSWMDT.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\Os\xml\Os_dio.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\EcuC\xml\EcuC_dio.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\MCAL_RH850U2B24E_516_CodeGen\Translation.trxml
 * GENERATED ON:  10 Jul 2026 - 18:49:23
 */


#ifndef DIO_CFG_H
#define DIO_CFG_H


/***********************************************************************************************************************
**                      Include Section                                                                               **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                      Coding Rule Violations                                                                        **
***********************************************************************************************************************/



/***********************************************************************************************************************
**                      Version Information                                                                           **
***********************************************************************************************************************/
#define DIO_AR_VERSION                                                          DIO_AR_R22_11_VERSION
/* AUTOSAR release version information */
#define DIO_CFG_AR_RELEASE_MAJOR_VERSION                                        4U
#define DIO_CFG_AR_RELEASE_MINOR_VERSION                                        8U
#define DIO_CFG_AR_RELEASE_REVISION_VERSION                                     0U
/* File version information */
#define DIO_CFG_SW_MAJOR_VERSION                                                2U
#define DIO_CFG_SW_MINOR_VERSION                                                4U
#define DIO_CFG_C_AR_RELEASE_MAJOR_VERSION                                      4U
#define DIO_CFG_C_AR_RELEASE_MINOR_VERSION                                      8U
#define DIO_CFG_C_AR_RELEASE_REVISION_VERSION                                   0U
#define DIO_CFG_C_SW_MAJOR_VERSION                                              2U
#define DIO_CFG_C_SW_MINOR_VERSION                                              4U

/***********************************************************************************************************************
**                      Common Published Information                                                                  **
***********************************************************************************************************************/
#define DIO_AR_RELEASE_MAJOR_VERSION_VALUE                                      4U
#define DIO_AR_RELEASE_MINOR_VERSION_VALUE                                      8U
#define DIO_AR_RELEASE_REVISION_VERSION_VALUE                                   0U
#define DIO_SW_MAJOR_VERSION_VALUE                                              2U
#define DIO_SW_MINOR_VERSION_VALUE                                              4U
#define DIO_SW_PATCH_VERSION_VALUE                                              1U
#define DIO_VENDOR_ID_VALUE                                                     59U
#define DIO_MODULE_ID_VALUE                                                     120U

/***********************************************************************************************************************
**                      Global Symbols                                                                                **
***********************************************************************************************************************/


/* Instance ID of the DIO Driver */
#define DIO_INSTANCE_ID_VALUE                                                   0U
/* Pre-compile option for Version Info API */
#define DIO_VERSION_INFO_API                                                    STD_ON
/* Pre-compile option for presence of Dio_MaskedWritePort API */
#define DIO_MASKED_WRITE_PORT_API                                               STD_ON
/* Pre-compile option for presence of Dio_FlipChannel API */
#define DIO_FLIP_CHANNEL_API                                                    STD_ON
/* Pre-compile option for presence of Dio_ReadChannelOutputValue API */
#define DIO_READ_CHANNEL_OUTPUT_VALUE_API                                       STD_ON
/* Pre-compile option for presence of Dio_ReadChannelGroupOutputValue API */
#define DIO_READ_CHANNELGROUP_OUTPUT_VALUE_API                                  STD_ON
/* Pre-compile option for presence of DioMultiCoreSupport */
#define DIO_MULTI_CORE_SUPPORT                                                  STD_ON
/* Pre-compile option for presence of Channel */
#define DIO_CHANNEL_CONFIGURED                                                  STD_ON
/* Pre-compile option for presence of Channel Group */
#define DIO_CHANNELGROUP_CONFIGURED                                             STD_OFF
/* Pre-compile option for Development Error Detect */
#define DIO_DEV_ERROR_DETECT                                                    STD_OFF
/* Pre-compile option for enable or disable version check of inter-module dependencies */
#define DIO_VERSION_CHECK_EXT_MODULES                                           STD_ON
/* Pre-compile option for critical section protection */
#define DIO_CRITICAL_SECTION_PROTECTION                                         STD_ON
/* Offset for getting PPR register address from PSR register address for Numeric and Alphabetic ports. */
#define DIO_PPR_OFFSET_NONJTAG                                                  (uint8)0x02
/* Offset for getting PNOT register address from PSR register address for Numeric and Alphabetic ports. */
#define DIO_PNOT_OFFSET_NONJTAG                                                 (uint8)0x01
/* Offset for getting PMSR register address from PSR register address for NONJTAG ports. */
#define DIO_PMSR_OFFSET_NONJTAG                                                 (uint8)0x07
/* Offset for getting JPPR register address from JPSR register address for JTAG ports */
#define DIO_PPR_OFFSET_JTAG                                                     (uint8)0x02
/* Offset for getting JPNOT register address from JPSR register address for JTAG ports. */
#define DIO_PNOT_OFFSET_JTAG                                                    (uint8)0x01
/* Offset for getting JPMSR register address from JPSR register address for JTAG ports */
#define DIO_PMSR_OFFSET_JTAG                                                    (uint8)0x07
/* Port Keycode Protection Register */
#define DIO_PKCPROT                                                             (uint32)0xFFD92F40UL
/* Port Write Enable Register */
#define DIO_PWE                                                                 (uint32)0xFFD92F44UL
/* Disable write access to PWE register */
#define DIO_WRITE_PWE_DISABLE_VAL                                               (uint32)0xA5A5A500UL
/* Enable write access to PWE register */
#define DIO_WRITE_PWE_ENABLE_VAL                                                (uint32)0xA5A5A501UL

/***********************************************************************************************************************
**                      Global Data Types                                                                             **
***********************************************************************************************************************/


/* Total number of configured ports */
#define DIO_MAXNOOFPORT                                                         (Dio_PortType)1
/* Total number of configured channels */
#define DIO_MAXNOOFCHANNEL                                                      (Dio_ChannelType)3

/***********************************************************************************************************************
**                      Global Data                                                                                   **
***********************************************************************************************************************/


/* DIO Port Configuration Handles */
#define DioConf_DioPort_DioPort_P14                                             (Dio_PortType)0
/* DIO Channel Configuration Handles */
#define DioConf_DioChannel_DioChannel_P14_11_LED9                               (Dio_ChannelType)0
#define DioConf_DioChannel_DioChannel_P14_12_LED10                              (Dio_ChannelType)1
#define DioConf_DioChannel_DioChannel_P14_13_LED11                              (Dio_ChannelType)2
/* DIO Channel Group Configuration Handles */
/* Channel Mapping for DioChannelBitPosition */
#define DioConfig_DioChannel_P14_11_LED9_bit                                    (uint8)0x09
#define DioConfig_DioChannel_P14_12_LED10_bit                                   (uint8)0x0C
#define DioConfig_DioChannel_P14_13_LED11_bit                                   (uint8)0x0D

/***********************************************************************************************************************
**                      Function Prototypes                                                                           **
***********************************************************************************************************************/



#endif /* DIO_CFG_H */


/***********************************************************************************************************************
**                      End of File                                                                                   **
***********************************************************************************************************************/

