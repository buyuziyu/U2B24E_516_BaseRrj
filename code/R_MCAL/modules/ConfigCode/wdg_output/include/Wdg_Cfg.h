/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Wdg_Cfg.h                                                                                           */
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
/* TOOL VERSION:  WdgU2Bx-E.dll version: 2.4.1, MCALConfGen.exe version: 2.3.0                                        */
/*                                                                                                                    */


/***********************************************************************************************************************
**                      Input File                                                                                    **
***********************************************************************************************************************/
/*
 * INPUT FILE:    C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\MCAL_RH850U2B24E_516_CodeGen\U2B24-E.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\modules\wdg\generator\U2B24-E\R2211_wdg_U2B24-E_BSWMDT.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\Dem\xml\Dem_wdg.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\Os\xml\Os_wdg.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\EcuC\xml\EcuC_wdg.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\MCAL_RH850U2B24E_516_CodeGen\Translation.trxml
 * GENERATED ON:  10 Jul 2026 - 18:50:08
 */


#ifndef WDG_CFG_H
#define WDG_CFG_H


/***********************************************************************************************************************
**                      Include Section                                                                               **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                      Version Information                                                                           **
***********************************************************************************************************************/

/* AUTOSAR release version information. */
#define WDG_CFG_AR_RELEASE_MAJOR_VERSION                                        4U

#define WDG_CFG_AR_RELEASE_MINOR_VERSION                                        8U

#define WDG_CFG_AR_RELEASE_REVISION_VERSION                                     0U

/* File version information. */
#define WDG_CFG_SW_MAJOR_VERSION                                                2U

#define WDG_CFG_SW_MINOR_VERSION                                                4U

#define WDG_AR_VERSION                                                          WDG_AR_R22_11_VERSION

/***********************************************************************************************************************
**                      Common Published Information                                                                  **
***********************************************************************************************************************/

#define WDG_AR_RELEASE_MAJOR_VERSION_VALUE                                      4U

#define WDG_AR_RELEASE_MINOR_VERSION_VALUE                                      8U

#define WDG_AR_RELEASE_REVISION_VERSION_VALUE                                   0U

#define WDG_SW_MAJOR_VERSION_VALUE                                              2U

#define WDG_SW_MINOR_VERSION_VALUE                                              4U

#define WDG_SW_PATCH_VERSION_VALUE                                              1U

#define WDG_VENDOR_ID_VALUE                                                     59U

#define WDG_MODULE_ID_VALUE                                                     102U


/***********************************************************************************************************************
**                      Global Symbols                                                                                **
***********************************************************************************************************************/

/* Instance ID of the WDG Component. */
#define WDG_INSTANCE_ID_VALUE                                                   0U

/* Pre-compile option for critical section protection. */
#define WDG_CRITICAL_SECTION_PROTECTION                                         STD_ON

/* Pre-compile option for development error detect. */
#define WDG_DEV_ERROR_DETECT                                                    STD_OFF

/* Pre-compile option to allow or forbid disabling Watchdog Unit. */
#define WDG_DISABLE_ALLOWED                                                     STD_ON

/* Pre-compile option switch enable/disable ECM Interrupt consistency check functionality. */
#define WDG_ECM_INT_CONSISTENCY_CHECK                                           STD_ON

/* Pre-compile option select the method of reference to clock supply. */
#define WDG_ENABLE_WDTBA_CLOCK_IMMEDIATE_VALUE                                  STD_OFF

/* Pre-compile option select the method of reference to clock supply. */
#define WDG_ENABLE_WDTBN_CLOCK_IMMEDIATE_VALUE                                  STD_OFF

/* Pre-compiler parameter specifies whether Interrupt Consistency Check functionality is enable or disable */
#define WDG_INT_CONSISTENCY_CHECK                                               STD_ON

/* Enable Multicore WDG Driver */
#define WDG_MULTI_CORE_SUPPORT                                                  STD_ON

/* Variable_Activation_Code Function Support */
#define WDG_VAC_SUPPORT                                                         STD_ON

/* Pre-compile option for enable or disable inter-module dependencies. */
#define WDG_VER_CHECK_EXT                                                       STD_ON

/* Pre-compile option for version info API. */
#define WDG_VERSION_INFO_API                                                    STD_ON

/* Pre-compiler WdgIsrCategory select the support interrupt category CAT1 or CAT2. */
#define WDG_ISR_CATEGORY_2                                                      STD_OFF

/* Pre-compile option for enable/disable the watchdog driver at runtime */
#define WDG_FEINT_DISABLE_ALLOWED                                               STD_ON

/* Enable FE Level Interrupt mode */
#define WDG_ERR_FE_LEVEL_INTERRUPT_MODE                                         STD_ON

/* Enable WDTBA */
#define WDG_WDTBA_CONFIGURED                                                    STD_OFF

/* Enable WDTBN */
#define WDG_WDTBN_CONFIGURED                                                    STD_ON



/* Initial timeout in msec for the trigger condition to be initialized during Init or set mode function. */
#define WDG_INITIAL_TIMEOUT                                                     1000U

/* Maximum timeout in msec to which the watchdog trigger condition can be initialized. */
#define WDG_MAXIMUM_TIMEOUT                                                     8000U

/* Represents the watchdog driver execution area is either from ROM(Flash) or RAM as required with the particular     */
/*   micro-controller.                                                                                                */
#define WDG_RUN_AREA                                                            WDG_RAM

/* Represents the watchdog driver's ID. */
#define WDG_INDEX                                                               0U

/* Value of Clock supply for WDTBn */
#define WDG_WDTBN_CLOCK_REFERENCE_IMMEDIATE_VALUE                               250000U

/* Number of configured cores */
#define WDG_SUPPORTED_CORE_CONFIGURED_NUM                                       (uint8)0x02

/* Number of supported cores */
#define WDG_SUPPORTED_CORE_MAX_NUM                                              (uint8)0x06


/* Address of ECM Protection Command Register. */
#define WDG_ECMKCPROT                                                           (*((volatile uint32*)0xFFCCD4B4UL))

/* Watchdog trigger mode. */
#define WDG_TRIGGER_MODE                                                        WDG_WINDOW




/* Macro used to check the Interrupt Consistency */
#define WDG_EIC_EIMK_CHECK_VALUE                                                (uint16)0x0080U

#define WDG_ECMDTMCFG_E_DELAY_TIMER                                             (uint32)0x00000010UL

#define WDG_ECMEMK_MASK                                                         (uint32)0x00000010UL

#define WDG_ECMIS_CHECK_VALUE                                                   (uint32)0x00000010UL


/* FEINT Interrupt enable mask. */
#define WDG_FEINT_MASK                                                          (uint32)0xFFFFFFFBUL

#define WDG_ECMIE_CHECK_VALUE                                                   (uint32)0x00000010UL

#define WDG_ECMMSSE_CHECK_VALUE                                                 (uint32)0x00000010UL

#define WDG_ECMISCFG_E_INT                                                      (uint32)0x00000010UL


/* If error during mode switch failed, the following error is Reported to DEM. */
#define WDG_E_DISABLE_REJECTED                                                  \
                                                                             DemConf_DemEventParameter_DemEventParameter

/* If switching between the modes is failed, the following error is Reported to DEM. */
#define WDG_E_MODE_FAILED                                                       \
                                                                         DemConf_DemEventParameter_DemEventParameter_004

/* If the error Timeout value expired when WdgErrorModeSetting is WDG_FE_LEVEL_INTERRUPT_MODE has occurred, the       */
/*   following error is Reported to DEM.                                                                              */
#define WDG_E_TRIGGER_TIMEOUT                                                   \
                                                                         DemConf_DemEventParameter_DemEventParameter_005

/* If the error specific ECM interrupt is inconsistent when WdgErrorModeSetting is WDG_FE_LEVEL_INTERRUPT_MODE has    */
/*   occurred, the following error is Reported to DEM.                                                                */
#define WDG_E_ECM_INT_INCONSISTENT                                              \
                                                                         DemConf_DemEventParameter_DemEventParameter_001

/* If the error illegal update register access when WdgErrorModeSetting is WDG_FE_LEVEL_INTERRUPT_MODE has occurred,  */
/*   the following error is Reported to DEM.                                                                          */
#define WDG_E_ILLEGAL_UPDATE_REGISTER                                           \
                                                                         DemConf_DemEventParameter_DemEventParameter_002

/* If the trigger interrupt is inconsistent, the following error is reported to DEM. */
#define WDG_E_INT_INCONSISTENT                                                  \
                                                                         DemConf_DemEventParameter_DemEventParameter_001


/* Pre-compile option switch enable/disable disable rejected configured check. */
#define WDG_E_DISABLE_REJECTED_CONFIGURED                                       STD_OFF

/* Pre-compile option switch enable/disable mode failed configured check. */
#define WDG_E_MODE_FAILED_CONFIGURED                                            STD_OFF

/* Pre-compile option switch enable/disable trigger timeout consistency configured check. */
#define WDG_E_TRIGGER_TIMEOUT_CONFIGURED                                        STD_OFF

/* Pre-compile option switch enable/disable ECM Interrupt inconsistency configured check. */
#define WDG_E_ECM_INT_INCONSISTENT_CONFIGURED                                   STD_OFF

/* Pre-compile option switch enable/disable illegal update register configured check. */
#define WDG_E_ILLEGAL_UPDATE_REGISTER_CONFIGURED                                STD_OFF

/* Pre-compile option switch enable/disable Interrupt inconsistency configured check. */
#define WDG_E_INT_INCONSISTENT_CONFIGURED                                       STD_OFF



/* Configuration Set Handles. */
#define Wdg_Config                                                              (&Wdg_GstConfiguration[0])


/***********************************************************************************************************************
**                      Global Data Types                                                                             **
***********************************************************************************************************************/



/***********************************************************************************************************************
**                      Global Data                                                                                   **
***********************************************************************************************************************/



/***********************************************************************************************************************
**                      Function Prototypes                                                                           **
***********************************************************************************************************************/



#endif /* WDG_CFG_H */


/***********************************************************************************************************************
**                      End of File                                                                                   **
***********************************************************************************************************************/

