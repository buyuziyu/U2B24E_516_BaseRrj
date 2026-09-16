/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Spi_Cfg.h                                                                                           */
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
/* TOOL VERSION:  SpiU2Bx-E.dll version: 2.5.1, MCALConfGen.exe version: 2.3.0                                        */
/*                                                                                                                    */


/***********************************************************************************************************************
**                      Input File                                                                                    **
***********************************************************************************************************************/
/*
 * INPUT FILE:    C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\MCAL_RH850U2B24E_516_CodeGen\U2B24-E.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\modules\spi\generator\U2B24-E\R2211_spi_U2B24-E_BSWMDT.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\Dem\xml\Dem_spi.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\Os\xml\Os_spi.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\EcuC\xml\EcuC_spi.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\MCAL_RH850U2B24E_516_CodeGen\Translation.trxml
 * GENERATED ON:  10 Jul 2026 - 18:50:04
 */


#ifndef SPI_CFG_H
#define SPI_CFG_H


/***********************************************************************************************************************
**                      Include Section                                                                               **
***********************************************************************************************************************/
#include "Spi_Externals.h"


/***********************************************************************************************************************
**                      Coding Rule Violations                                                                        **
***********************************************************************************************************************/



/***********************************************************************************************************************
**                      Version Information                                                                           **
***********************************************************************************************************************/
/* AUTOSAR specification version information */
#define SPI_AR_VERSION                                                          SPI_AR_R22_11_VERSION
#define SPI_CFG_AR_RELEASE_MAJOR_VERSION                                        4U
#define SPI_CFG_AR_RELEASE_MINOR_VERSION                                        8U
#define SPI_CFG_AR_RELEASE_REVISION_VERSION                                     0U
/* File version information */
#define SPI_CFG_SW_MAJOR_VERSION                                                2U
#define SPI_CFG_SW_MINOR_VERSION                                                5U
#define SPI_AR_RELEASE_MAJOR_VERSION_VALUE                                      4U
#define SPI_AR_RELEASE_MINOR_VERSION_VALUE                                      8U
#define SPI_AR_RELEASE_REVISION_VERSION_VALUE                                   0U
#define SPI_SW_MAJOR_VERSION_VALUE                                              2U
#define SPI_SW_MINOR_VERSION_VALUE                                              5U
#define SPI_SW_PATCH_VERSION_VALUE                                              1U
#define SPI_VENDOR_ID_VALUE                                                     59U
#define SPI_MODULE_ID_VALUE                                                     83U
#define SPI_CFG_C_AR_RELEASE_MAJOR_VERSION                                      4U
#define SPI_CFG_C_AR_RELEASE_MINOR_VERSION                                      8U
#define SPI_CFG_C_AR_RELEASE_REVISION_VERSION                                   0U
#define SPI_CFG_C_SW_MAJOR_VERSION                                              2U
#define SPI_CFG_C_SW_MINOR_VERSION                                              5U

/***********************************************************************************************************************
**                      Global Symbols                                                                                **
***********************************************************************************************************************/



/* Instance ID of the SPI SpiDriver */
#define SPI_INSTANCE_ID_VALUE                                                   0U

/* Enables/Disables GetVersionInfo API */
#define SPI_VERSION_INFO_API                                                    STD_ON

/* Enables/Disables GetHWUnitStatus API */
#define SPI_HW_STATUS_API                                                       STD_ON

/* Enables/Disables Cancel API */
#define SPI_CANCEL_API                                                          STD_ON

/* Enables/Disables Cancel API */
#define SPI_FORCE_CANCEL_API                                                    STD_ON

/* Enables/Disables Development error detection */
#define SPI_DEV_ERROR_DETECT                                                    STD_ON

/* Pre-compile option for enable or disable inter-module dependencies */
#define SPI_VERSION_CHECK_EXT_MODULES                                           STD_ON

/* Switches the Interruptible SpiSequence handling functionality ON or OFF */
#define SPI_INTERRUPTIBLE_SEQ_ALLOWED                                           STD_ON

/* Enables/Disables configuration of Direct Access Memory mode selection */
#define SPI_DIRECT_ACCESS_MODE                                                  STD_ON

/* Enables/Disables configuration of Fixed Buffer Memory mode selection */
#define SPI_FIXED_BUFFER_MODE                                                   STD_OFF

/* Enables/Disables configuration of Fixed FIFO Memory mode selection */
#define SPI_FIXED_FIFO_MODE                                                     STD_OFF

/* Enables/Disables configuration of critical section functionality */
#define SPI_CRITICAL_SECTION_PROTECTION                                         STD_ON

/* Specifies whether concurrent Spi_SyncTransmit() calls for different sequences shall be configurable */
#define SPI_SUPPORT_CONCURRENT_SYNC_TRANSMIT                                    STD_ON

/* Specifies whether concurrent async transmission is enabled or not. */
#define SPI_SUPPORT_CONCURRENT_ASYNC_TRANSMIT                                   STD_ON

/* Enables/Disables the SPI_E_ALREADY_INITIALIZED Det error check in Spi_Init API */
#define SPI_ALREADY_INIT_DET_CHECK                                              STD_ON

/* Enables/Disables the names configured in SpiSeqStartNotification */
#define SPI_SEQ_STARTNOTIFICATION_ENABLED                                       STD_ON

/* Enables/Disables the check for the names configured for synchronous transmissions in SpiSeqEndNotification */
#define SPI_SYNC_SEQ_ENDNOTIFICATION_ENABLED                                    STD_ON

/* Enables/Disables the check when HW configuration is static or dynamic HW */
#define SPI_PERSISTENT_HW_CONFIGURATION_ENABLED                                 STD_ON


/* This parameter enables/disables the interrupt consistency check in the ISRs. */
#define SPI_INTERRUPT_CONSISTENCY_CHECK                                         STD_OFF

/* Enables/Disables the SpiDma mode */
#define SPI_DMA_CONFIGURED                                                      STD_OFF

/* Enable Multi Core Distributed type IV for SPI Driver */
#define SPI_MULTI_CORE_SUPPORT                                                  STD_ON

/* Configuration of CSIH hardware unit */
#define SPI_CSIH_CONFIGURED                                                     STD_OFF

/* Configuration of HSPI hardware unit */
#define SPI_HSPI_CONFIGURED                                                     STD_OFF

/* Configuration of MSPI hardware unit */
#define SPI_MSPI_CONFIGURED                                                     STD_ON

/* Enables/Disables the CS via GPIO */
#define SPI_CS_VIA_GPIO_CONFIGURED                                              STD_OFF

/* Specifies whether MSPI HW unit supports Rx buffer full */
#define SPI_MSPI_NOT_SUPPORT_RX_BUFFER_FULL                                     STD_OFF

/* The maximum number of HW unit types in all configuration sets */
#define SPI_MAX_MACRO                                                           1UL

/* Handles for configured HW unit type as MSPI */
#define SPI_MACRO_MSPI                                                          0U

/* Maximum number of transfer channels */
#define SPI_MSPI_MAX_CHANNEL                                                    12U

/* Select the SPI Handler/SpiDriver level of scalable functionality */
#define SPI_LEVEL_DELIVERED                                                     2U

/* Select the SPI Handler/SpiDriver Channel Buffers usage allowed */
#define SPI_CHANNEL_BUFFERS_ALLOWED                                             2U

/* Number of Tx/Rx IB buffers of channels associated to Direct Access mode, FIFO mode */
#define SPI_MAX_CHANNEL_BUFFER_SIZE                                             8U

/* The maximum number of HSPI HW units channel buffer size in all configuration sets */
#define SPI_MAX_HSPI_CHANNEL_BUFFER_SIZE                                        0U

/* Number of Channels configured SpiChannelType as EB */
#define SPI_EBDATA_SIZE                                                         1U

/* The maximum value of SpiMaxChannel in all configuration sets */
#define SPI_MAX_CHANNEL                                                         (Spi_ChannelType)2U

/* The maximum value of SpiMaxJob in all configuration sets */
#define SPI_MAX_JOB                                                             (Spi_JobType)2U

/* The maximum value of SpiMaxSequence in all configuration sets */
#define SPI_MAX_SEQUENCE                                                        (Spi_SequenceType)2U

/* Gives the maximum queue used */
#define SPI_MAX_QUEUE                                                           3U

/* The maximum number of HW channels in all configuration sets */
#define SPI_MAX_HWUNIT                                                          2U

/* Polling times on waiting asynchronous APIs to be executed by the kernel. */
#define SPI_ASYNCHONOUS_POLLING_TIMES                                           0x0000FFFFUL

/* Macro of ored interrupt function feature */
#define SPI_ORED_INTERRUPT_FUNCTION                                             STD_OFF

/* This parameter enables/disables module wise ISR category. */
#define SPI_ISR_CATEGORY_2                                                      STD_OFF

/* The reference to DEM event parameter for hardware error */
#define SPI_E_HARDWARE_ERROR                                                    \
                                                                         DemConf_DemEventParameter_DemEventParameter_001
/* The reference to DEM event parameter for data timeout failure */
#define SPI_E_DATA_TX_TIMEOUT_FAILURE                                           \
                                                                             DemConf_DemEventParameter_DemEventParameter

/* Handles for configured SpiChannel */
#define SpiConf_SpiChannel_SpiChannel                                           (Spi_ChannelType)0U
#define SpiConf_SpiChannel_SpiChannel_001                                       (Spi_ChannelType)1U

/* Handles for configured SpiJob */
#define SpiConf_SpiJob_SpiJob                                                   (Spi_JobType)0U
#define SpiConf_SpiJob_SpiJob_001                                               (Spi_JobType)1U

/* Handles for configured SpiSequence */
#define SpiConf_SpiSequence_SpiSequence                                         (Spi_SequenceType)0U
#define SpiConf_SpiSequence_SpiSequence_001                                     (Spi_SequenceType)1U

/* Handles for configured HW unit */
#define SPI_MSPI0                                                               (Spi_HWUnitType)0U
#define SPI_MSPI1                                                               (Spi_HWUnitType)1U

/* Handles for configured SpiDriver */
#define Spi_Config                                                              (&Spi_GaaConfiguration[0])
/* Macros for enabling/disabling Hardware units ISRS */
#define SPI_MSPI0_TX_ISR_API                                                    STD_ON
#define SPI_MSPI0_RX_ISR_API                                                    STD_ON
#define SPI_MSPI0_FE_ISR_API                                                    STD_OFF
#define SPI_MSPI1_TX_ISR_API                                                    STD_ON
#define SPI_MSPI1_RX_ISR_API                                                    STD_ON
#define SPI_MSPI1_FE_ISR_API                                                    STD_OFF
#define SPI_MSPI2_TX_ISR_API                                                    STD_OFF
#define SPI_MSPI2_RX_ISR_API                                                    STD_OFF
#define SPI_MSPI2_FE_ISR_API                                                    STD_OFF
#define SPI_MSPI3_TX_ISR_API                                                    STD_OFF
#define SPI_MSPI3_RX_ISR_API                                                    STD_OFF
#define SPI_MSPI3_FE_ISR_API                                                    STD_OFF
#define SPI_MSPI4_TX_ISR_API                                                    STD_OFF
#define SPI_MSPI4_RX_ISR_API                                                    STD_OFF
#define SPI_MSPI4_FE_ISR_API                                                    STD_OFF
#define SPI_MSPI5_TX_ISR_API                                                    STD_OFF
#define SPI_MSPI5_RX_ISR_API                                                    STD_OFF
#define SPI_MSPI5_FE_ISR_API                                                    STD_OFF
#define SPI_MSPI6_TX_ISR_API                                                    STD_OFF
#define SPI_MSPI6_RX_ISR_API                                                    STD_OFF
#define SPI_MSPI6_FE_ISR_API                                                    STD_OFF
#define SPI_MSPI7_TX_ISR_API                                                    STD_OFF
#define SPI_MSPI7_RX_ISR_API                                                    STD_OFF
#define SPI_MSPI7_FE_ISR_API                                                    STD_OFF
#define SPI_MSPI8_TX_ISR_API                                                    STD_OFF
#define SPI_MSPI8_RX_ISR_API                                                    STD_OFF
#define SPI_MSPI8_FE_ISR_API                                                    STD_OFF
#define SPI_MSPI9_TX_ISR_API                                                    STD_OFF
#define SPI_MSPI9_RX_ISR_API                                                    STD_OFF
#define SPI_MSPI9_FE_ISR_API                                                    STD_OFF
#define SPI_MSPI_ORED0_TX_ISR_API                                               STD_OFF
#define SPI_MSPI_ORED0_RX_ISR_API                                               STD_OFF
#define SPI_MSPI_ORED0_FE_ISR_API                                               STD_OFF
#define SPI_MSPI_ORED1_TX_ISR_API                                               STD_OFF
#define SPI_MSPI_ORED1_RX_ISR_API                                               STD_OFF
#define SPI_MSPI_ORED1_FE_ISR_API                                               STD_OFF
#define SPI_MSPI_ORED2_TX_ISR_API                                               STD_OFF
#define SPI_MSPI_ORED2_RX_ISR_API                                               STD_OFF
#define SPI_MSPI_ORED2_FE_ISR_API                                               STD_OFF
#define SPI_MSPI_ORED3_TX_ISR_API                                               STD_OFF
#define SPI_MSPI_ORED3_RX_ISR_API                                               STD_OFF
#define SPI_MSPI_ORED3_FE_ISR_API                                               STD_OFF
#define SPI_DMA0_00_ISR_API                                                     STD_OFF
#define SPI_DMA0_01_ISR_API                                                     STD_OFF
#define SPI_DMA0_02_ISR_API                                                     STD_OFF
#define SPI_DMA0_03_ISR_API                                                     STD_OFF
#define SPI_DMA0_04_ISR_API                                                     STD_OFF
#define SPI_DMA0_05_ISR_API                                                     STD_OFF
#define SPI_DMA0_06_ISR_API                                                     STD_OFF
#define SPI_DMA0_07_ISR_API                                                     STD_OFF
#define SPI_DMA0_08_ISR_API                                                     STD_OFF
#define SPI_DMA0_09_ISR_API                                                     STD_OFF
#define SPI_DMA0_10_ISR_API                                                     STD_OFF
#define SPI_DMA0_11_ISR_API                                                     STD_OFF
#define SPI_DMA0_12_ISR_API                                                     STD_OFF
#define SPI_DMA0_13_ISR_API                                                     STD_OFF
#define SPI_DMA0_14_ISR_API                                                     STD_OFF
#define SPI_DMA0_15_ISR_API                                                     STD_OFF
#define SPI_DMA1_00_ISR_API                                                     STD_OFF
#define SPI_DMA1_01_ISR_API                                                     STD_OFF
#define SPI_DMA1_02_ISR_API                                                     STD_OFF
#define SPI_DMA1_03_ISR_API                                                     STD_OFF
#define SPI_DMA1_04_ISR_API                                                     STD_OFF
#define SPI_DMA1_05_ISR_API                                                     STD_OFF
#define SPI_DMA1_06_ISR_API                                                     STD_OFF
#define SPI_DMA1_07_ISR_API                                                     STD_OFF
#define SPI_DMA1_08_ISR_API                                                     STD_OFF
#define SPI_DMA1_09_ISR_API                                                     STD_OFF
#define SPI_DMA1_10_ISR_API                                                     STD_OFF
#define SPI_DMA1_11_ISR_API                                                     STD_OFF
#define SPI_DMA1_12_ISR_API                                                     STD_OFF
#define SPI_DMA1_13_ISR_API                                                     STD_OFF
#define SPI_DMA1_14_ISR_API                                                     STD_OFF
#define SPI_DMA1_15_ISR_API                                                     STD_OFF

/* Enables/Disables the reference to DEM event parameter for interrupt inconsistency error. */
#define SPI_E_INT_INCONSISTENT_CONFIGURED                                       STD_OFF
/* Enables/Disables the reference to DEM event parameter for hardware error. */
#define SPI_E_HARDWARE_ERROR_CONFIGURED                                         STD_OFF
/* Enables/Disables the reference to DEM event parameter for data timeout failure. */
#define SPI_E_DATA_TX_TIMEOUT_FAILURE_CONFIGURED                                STD_OFF

/***********************************************************************************************************************
**                      Global Data Types                                                                             **
***********************************************************************************************************************/



/***********************************************************************************************************************
**                      Global Data                                                                                   **
***********************************************************************************************************************/



/***********************************************************************************************************************
**                      Function Prototypes                                                                           **
***********************************************************************************************************************/



#endif /* SPI_CFG_H */


/***********************************************************************************************************************
**                      End of File                                                                                   **
***********************************************************************************************************************/

