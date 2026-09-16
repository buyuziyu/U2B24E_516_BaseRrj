/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Port.h                                                                                              */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Private functions declarations.                                                                                    */
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
/*              Devices:        X2x                                                                                   */
/*====================================================================================================================*/

/***********************************************************************************************************************
**                                              Revision Control History                                              **
***********************************************************************************************************************/
/*
 * 2.4.0: 30/06/2025 : Update SW-VERSION for RH850/Ver22.01.00(D) U2Ax Release
 * 2.3.2: 25/04/2025 : Update SW-VERSION for RH850/Ver22.00.03 U2Ax Release
 * 2.3.1: 31/03/2025 : Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02 Release
 *                   : Remove Msg 4641 
 * 2.3.0: 28/02/2025 : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release 
 *                   : Add Msg 4641
 * 2.2.0: 31/12/2024 : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D U2Bx Final Release
 * 2.1.2: 31/10/2024 : Update SW-VERSION to 2.1.2 for Ver22.01.02 U2Bx Beta2
 *                   : Update value of PORT_SW_MINOR_VERSION and PORT_SW_PATCH_VERSION
 * 2.1.1: 30/08/2024 : Update value of PORT_SW_MINOR_VERSION and PORT_SW_PATCH_VERSION
 * 2.1.0: 28/02/2024 : Update SW-VERSION to 2.1.0
 *                   : Add definition for PORT_INVALID_INPUTPORT
 *                   : Remove Msg 1534, 1536
 *                   : Update value of PORT_SW_PATCH_VERSION
 * 2.0.1: 19/10/2023 : Add Msg 1536
 *        12/10/2023 : Change PORT_START/STOP_SEC_CONFIG_DATA_UNSPECIFIED to 
 *                     PORT_START/STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED .
 *        30/09/2023 : Change macro PORT_AR_R21_11_VERSION to PORT_AR_R22_11_VERSION and update value 
 *                     '470U' to '480U'.
 * 2.0.0: 06/08/2023 : Update CWE Rule CWE-398, CWE-569 for messsage 3432
 *        01/08/2023 : Add macro PORT_E_INVALID_CORE for support multi-core
 *        27/06/2023 : Remove redundant QAC message
 *        28/05/2023 : Remove redundant macro: PORT_E_INVALID_PARAM
 *        25/05/2023 : Update PORT_AR_2111_VERSION to PORT_AR_R21_11_VERSION
 *        22/05/2023 : Remove redundant QAC message
 *        27/04/2023 : Update SW-VERSION to 2.0.0
 * 1.5.0: 08/04/2023 : Change structure of Port_PinDirectionType to support R21_11
 *                     Add PORT_AR_RELEASE_MAJOR_VERSION, PORT_AR_RELEASE_MINOR_VERSION,
 *                     PORT_AR_RELEASE_REVISION_VERSION to support R21_11 
 *        19/03/2023 : Update PORT_SW_MINOR_VERSION to 5, Update PORT_SW_PATCH_VERSION to 0
 * 1.4.5: 15/12/2022 : Add macro PORT_REG_PSFTSAE to define for register PSFTSAE
 *        02/12/2022 : Add macro PORT_AR_470_VERSION for support AR21-11, Update value for PORT_SW_PATCH_VERSION
 * 1.4.4: 15/07/2022 : Update value for PORT_SW_PATCH_VERSION
 * 1.4.3: 19/05/2022 : Remove define of macro PORT_E_INVALID_PORT_ID
 *        14/05/2022 : Add Pre-Condition for Port_EcmMaskERRORIN and Port_EcmClearERRORIN API.  
 *        09/05/2022 : Update PORT_MODE_REG_NUM value. 
 *        15/04/2022 : Add macro PORT_REG_PULVSEL5 and PORT_REG_PEIODC for PULVSEL5 and PEIODC register.
 *                     - Remove macros: PORT_REG_PNOT, PORT_REG_PPR, PORT_ALT_OUTPUT, PORT_DIO_INPUT, PORT_ALT_INPUT,
 *                     PORT_ECM_MASK_ERRORIN_SID, PORT_ECM_CLEAR_ERRORIN_SID.
 *                     - Rename macros wrong name rule:
 *                     MODE_MASK to PORT_MODE_MASK, MODE_DIO_OUT to PORT_MODE_DIO_OUT, MODE_DIO_IN to PORT_MODE_DIO_IN,
 *                     MODE_ALT_OUT to PORT_MODE_ALT_OUT, MODE_ALT_IN to PORT_MODE_ALT_IN, MODE_ALT_DIRECT to 
 *                     PORT_MODE_ALT_DIRECT, APP_ALT1_OUT to PORT_APP_ALT1_OUT, APP_ALT2_OUT to PORT_APP_ALT2_OUT,
 *                     APP_ALT3_OUT to PORT_APP_ALT3_OUT, APP_ALT4_OUT to PORT_APP_ALT4_OUT, APP_ALT5_OUT to 
 *                     PORT_APP_ALT5_OUT, APP_ALT6_OUT to PORT_APP_ALT6_OUT, APP_ALT7_OUT to PORT_APP_ALT7_OUT,
 *                     APP_ALT8_OUT to PORT_APP_ALT8_OUT, APP_ALT9_OUT to PORT_APP_ALT9_OUT, APP_ALT10_OUT to 
 *                     PORT_APP_ALT10_OUT, APP_ALT11_OUT to PORT_APP_ALT11_OUT, APP_ALT12_OUT to PORT_APP_ALT12_OUT,
 *                     APP_ALT13_OUT to PORT_APP_ALT13_OUT, APP_ALT14_OUT to PORT_APP_ALT14_OUT, APP_ALT15_OUT to
 *                     PORT_APP_ALT15_OUT, APP_ALT16_OUT to PORT_APP_ALT16_OUT, APP_ALT1_IN to PORT_APP_ALT1_IN,
 *                     APP_ALT2_IN to PORT_APP_ALT2_IN, APP_ALT3_IN to PORT_APP_ALT3_IN, APP_ALT4_IN to
 *                     PORT_APP_ALT4_IN, APP_ALT5_IN to PORT_APP_ALT5_IN, APP_ALT6_IN to PORT_APP_ALT6_IN,
 *                     APP_ALT7_IN to PORT_APP_ALT7_IN, APP_ALT8_IN to PORT_APP_ALT8_IN, APP_ALT9_IN to
 *                     PORT_APP_ALT9_IN, APP_ALT10_IN to PORT_APP_ALT10_IN, APP_ALT11_IN to PORT_APP_ALT11_IN,
 *                     APP_ALT12_IN to PORT_APP_ALT12_IN, APP_ALT13_IN to PORT_APP_ALT13_IN, APP_ALT14_IN to
 *                     PORT_APP_ALT14_IN, APP_ALT15_IN to PORT_APP_ALT15_IN, APP_ALT16_IN to PORT_APP_ALT16_IN,
 *                     APP_ALT1_DIRECT to PORT_APP_ALT1_DIRECT, APP_ALT2_DIRECT to PORT_APP_ALT2_DIRECT,
 *                     APP_ALT3_DIRECT to PORT_APP_ALT3_DIRECT, APP_ALT4_DIRECT to PORT_APP_ALT4_DIRECT,
 *                     APP_ALT5_DIRECT to PORT_APP_ALT5_DIRECT, APP_ALT6_DIRECT to PORT_APP_ALT6_DIRECT,
 *                     APP_ALT7_DIRECT to PORT_APP_ALT7_DIRECT, APP_ALT8_DIRECT to PORT_APP_ALT8_DIRECT,
 *                     APP_ALT9_DIRECT to PORT_APP_ALT9_DIRECT, APP_ALT10_DIRECT to PORT_APP_ALT10_DIRECT,
 *                     APP_ALT11_DIRECT to PORT_APP_ALT11_DIRECT, APP_ALT12_DIRECT to PORT_APP_ALT12_DIRECT,
 *                     APP_ALT13_DIRECT to PORT_APP_ALT13_DIRECT, APP_ALT14_DIRECT to PORT_APP_ALT14_DIRECT,
 *                     APP_ALT15_DIRECT to PORT_APP_ALT15_DIRECT, APP_ALT16_DIRECT to PORT_APP_ALT16_DIRECT.
 *        07/04/2022   Removed redundant define PORT_SET_PIN_DEFAULT_MODE_SID
 *                     Update SW-VERSION to 1.4.3
 * 1.4.2: 18/02/2022 : Update SW-VERSION to 1.4.2
 * 1.4.1: 07/10/2021 : Update SW-VERSION to 1.4.1
 * 1.3.1: 11/08/2021 : Updated version of PORT_SW_PATCH_VERSION to 2
 * 1.3.1: 02/07/2021 : Add QAC message 9.5.0
 *                     Format source code to 120 characters
 *                     Improve Violation tag (remove START/END)
 *        06/05/2021 : As per ticket #ARDAACL-275, add memory section
 *                     _PUBLIC_CODE for API's declaration.
 * 1.3.0: 20/01/2021 : Correct prototype of Port_SetPinDirection, Port_SetPinMode
 *                     in order to comply AUTOSAR specification.
 *        24/11/2020 : Update SW-VERSION to 1.3.0
 * 1.2.0: 28/07/2020 : Release.
 * 1.1.0: 19/06/2020 : Release.
 * 1.0.0: 09/01/2020 : Initial Version
 */
/**********************************************************************************************************************/
#ifndef PORT_H
#define PORT_H

/***********************************************************************************************************************
**                             To support different AUTOSAR releases in a single package                              **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* To publish the standard types */
#include "Std_Types.h"
/* To publish the type Port_ConfigType */
#include "Port_Cfg.h"
#include "Port_Types.h"

#if (PORT_DEV_ERROR_DETECT == STD_ON)
/* Only in case of DET enabled, Debug variables will be available externally */
#endif
#define PORT_AR_422_VERSION 422U
#define PORT_AR_431_VERSION 431U
#define PORT_AR_R22_11_VERSION 480U

/*START of DIO_AR_VERSION */

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* Version identification */
#define PORT_VENDOR_ID      PORT_VENDOR_ID_VALUE
#define PORT_MODULE_ID      PORT_MODULE_ID_VALUE
#define PORT_INSTANCE_ID    PORT_INSTANCE_ID_VALUE   

/* AUTOSAR release version information */
#if (PORT_AR_VERSION == PORT_AR_422_VERSION)
#define PORT_AR_RELEASE_MAJOR_VERSION    4U
#define PORT_AR_RELEASE_MINOR_VERSION    2U
#define PORT_AR_RELEASE_REVISION_VERSION 2U 
#elif (PORT_AR_VERSION == PORT_AR_431_VERSION)
#define PORT_AR_RELEASE_MAJOR_VERSION    4U
#define PORT_AR_RELEASE_MINOR_VERSION    3U
#define PORT_AR_RELEASE_REVISION_VERSION 1U 
#elif (PORT_AR_VERSION == PORT_AR_R22_11_VERSION)
#define PORT_AR_RELEASE_MAJOR_VERSION    4U
#define PORT_AR_RELEASE_MINOR_VERSION    8U
#define PORT_AR_RELEASE_REVISION_VERSION 0U
#endif
/*END of PORT_AR_VERSION */

/* Module Software version information */
#define PORT_SW_MAJOR_VERSION         2U
#define PORT_SW_MINOR_VERSION         4U
#define PORT_SW_PATCH_VERSION         1U

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE Rule CWE-398, CWE-569                                            */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is accepted. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3684)    : Array declared with unknown size.                                                            */
/* Rule                : CERTCCM ARR02, MISRA C:2012 Rule-8.11                                                        */
/* JV-01 Justification : Arrays used are verified in the file which are only declarations and size is configuration   */
/*                       dependent.                                                                                   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                               API service ID Macros                                                **
***********************************************************************************************************************/
/* Service ID for PORT Initialization */
#define PORT_INIT_SID                 (uint8)0x00
/* Service ID for setting the Direction of PORT Pin */
#define PORT_SET_PIN_DIR_SID          (uint8)0x01
/* Service ID for refreshing the Direction of PORT Pin */
#define PORT_REFRESH_PORT_DIR_SID     (uint8)0x02
/* Service ID for PORT getting Version Information */
#define PORT_GET_VERSION_INFO_SID     (uint8)0x03
/* Service ID for setting the Mode of PORT Pin */
#define PORT_SET_PIN_MODE_SID         (uint8)0x04
/* Service ID for setting the Mode of PORT Pin */
#define PORT_SET_TO_DIO_MODE_SID      (uint8)0x05
/* Service ID for setting the Mode of PORT Pin */
#define PORT_SET_TO_ALT_MODE_SID      (uint8)0x06
/* Service ID for setting the Default Direction of PORT Pin */
#define PORT_SET_PIN_DEFAULT_DIR_SID  (uint8)0x08

/***********************************************************************************************************************
**                                                  DET Error Codes                                                   **
***********************************************************************************************************************/
#define PORT_E_PARAM_PIN              (uint8)0x0A

/* Port Pin Direction not configured as changeable */
#define PORT_E_DIRECTION_UNCHANGEABLE (uint8)0x0B

/* API Port_Init service called with wrong parameter. */
#define PORT_E_INIT_FAILED            (uint8)0x0C

/* When valid Mode is not available */
#define PORT_E_PARAM_INVALID_MODE     (uint8)0x0D

/* When valid Mode is not configured as changeable  */
#define PORT_E_MODE_UNCHANGEABLE      (uint8)0x0E

/* When PORT APIs are invoked before PORT Module Initialization */
#define PORT_E_UNINIT                 (uint8)0x0F

/* When PORT APIs are invoked with wrong pointer parameter. */
#define PORT_E_PARAM_POINTER          (uint8)0x10

/* When valid Database is not available */
#define PORT_E_INVALID_DATABASE       (uint8)0xEF

/* DET code to report service is being requested by other cores */
#define PORT_E_INVALID_CORE           (uint8)0xF1

/***********************************************************************************************************************
**                                                  Define Procedure                                                  **
***********************************************************************************************************************/
/* Port Type */
#define PORT_TYPE_JPORT               (uint16)0x0000U
#define PORT_TYPE_PORT                (uint16)0x0001U
#define PORT_TYPE_APORT               (uint16)0x0002U
#define PORT_INVALID_INPUTPORT        (uint32)0x00000000UL

/* Register Type */
#define PORT_REG_PMC                  0U
#define PORT_REG_PM                   1U
#define PORT_REG_PIPC                 2U
#define PORT_REG_PIBC                 3U
#define PORT_REG_PFC                  4U
#define PORT_REG_PFCE                 5U
#define PORT_REG_PFCAE                6U
#define PORT_REG_PFCEAE               7U
#define PORT_REG_PULVSEL5             15U         
#define PORT_REG_PU                   16U
#define PORT_REG_PD                   17U
#define PORT_REG_PIS                  18U
#define PORT_REG_PISA                 19U
#define PORT_REG_PEIODC               20U
#define PORT_REG_PODC                 24U
#define PORT_REG_PODCE                25U
#define PORT_REG_PDSC                 26U
#define PORT_REG_PUCC                 27U
#define PORT_REG_PINV                 28U
#define PORT_REG_PBDC                 29U
#define PORT_REG_P                    30U
#define PORT_REG_PSFTSAE              31U         
#define PORT_REG_PSFSOE               32U
#define PORT_REG_PSFSD                33U
#define PORT_REG_PSFSC                34U
#define PORT_REG_PKCPROT              35U
#define PORT_REG_PWE                  36U
#define PORT_REG_PSR                  37U
#define PORT_REG_PMSR                 38U
#define PORT_REG_PMCSR                39U
#define PORT_REG_NOTHING              (uint16)0xFFFFU

/* Register Bit */
#define PORT_BIT_PMC                  0x00000001UL
#define PORT_BIT_PM                   0x00000002UL
#define PORT_BIT_PIPC                 0x00000004UL
#define PORT_BIT_PIBC                 0x00000008UL
#define PORT_BIT_PFC                  0x00000010UL
#define PORT_BIT_PFCE                 0x00000020UL
#define PORT_BIT_PFCAE                0x00000040UL
#define PORT_BIT_PFCEAE               0x00000080UL
#define PORT_BIT_PU                   0x00010000UL
#define PORT_BIT_PD                   0x00020000UL
#define PORT_BIT_PIS                  0x00040000UL
#define PORT_BIT_PISA                 0x00080000UL
#define PORT_BIT_PODC                 0x01000000UL
#define PORT_BIT_PODCE                0x02000000UL
#define PORT_BIT_PDSC                 0x04000000UL
#define PORT_BIT_PUCC                 0x08000000UL
#define PORT_BIT_PINV                 0x10000000UL
#define PORT_BIT_PBDC                 0x20000000UL
#define PORT_BIT_P                    0x40000000UL

/* Number of Input Option Register */
#define PORT_IN_REG_NUM               4U
/* Number of Output Option Register */
#define PORT_OUT_REG_NUM              5U
/* Number of Alternate Register */
#define PORT_ALT_REG_NUM              4U
/* Number of Mode Register */
#define PORT_MODE_REG_NUM             7U
/* Number of Register to Reset */
#define PORT_RESET_REG_NUM            (PORT_ALT_REG_NUM + PORT_MODE_REG_NUM)
/* Number of Register to Set */
#define PORT_SET_REG_NUM              (PORT_IN_REG_NUM + PORT_OUT_REG_NUM + PORT_ALT_REG_NUM + PORT_MODE_REG_NUM)
/* Number of Register to Switch */
#define PORT_SWITCH_REG_NUM           4U

/* Number of Setting Mode */
#define PORT_SET_MODE_NUM             5U
/* Mode */
#define PORT_DIO_OUTPUT               1U
#define PORT_ALT_DIRECT               4U

/* Set Value */
#define PORT_MODE_DIO                 (uint16)0x0000U
#define PORT_MODE_ALT                 (uint16)0x0001U
#define PORT_PIPC_SW                  (uint16)0x0000U
#define PORT_PIPC_DIRECT              (uint16)0x0001U

/* Default Value */
#define PORT_DEFAULT                  (uint32)0xFFFFFFFFUL

/* Mask / Unmask */
#define PORT_MASK                     (boolean)0x01
#define PORT_UNMASK                   (boolean)0x00

/* Enable / Disable */
#define PORT_ENABLE                   (boolean)0x01
#define PORT_DISABLE                  (boolean)0x00

/* Initial / Reset */
#define PORT_INIT                     (boolean)0x01
#define PORT_RESET                    (boolean)0x00

/* Port_SetPinMode() Value to set for Mode */
#define PORT_MODE_MASK                     0x0000000FUL
#define PORT_MODE_DIO_OUT                  0x0000U
#define PORT_MODE_DIO_IN                   0x000AU
#define PORT_MODE_ALT_OUT                  0x0001U /* for check */
#define PORT_MODE_ALT_IN                   0x0003U /* for check */
#define PORT_MODE_ALT_DIRECT               0x0007U /* for check */
#define PORT_APP_ALT1_OUT                  (PORT_MODE_ALT_OUT + 0x0000U)
#define PORT_APP_ALT2_OUT                  (PORT_MODE_ALT_OUT + 0x0010U)
#define PORT_APP_ALT3_OUT                  (PORT_MODE_ALT_OUT + 0x0020U)
#define PORT_APP_ALT4_OUT                  (PORT_MODE_ALT_OUT + 0x0030U)
#define PORT_APP_ALT5_OUT                  (PORT_MODE_ALT_OUT + 0x0040U)
#define PORT_APP_ALT6_OUT                  (PORT_MODE_ALT_OUT + 0x0050U)
#define PORT_APP_ALT7_OUT                  (PORT_MODE_ALT_OUT + 0x0060U)
#define PORT_APP_ALT8_OUT                  (PORT_MODE_ALT_OUT + 0x0070U)
#define PORT_APP_ALT9_OUT                  (PORT_MODE_ALT_OUT + 0x0080U)
#define PORT_APP_ALT10_OUT                 (PORT_MODE_ALT_OUT + 0x0090U)
#define PORT_APP_ALT11_OUT                 (PORT_MODE_ALT_OUT + 0x00A0U)
#define PORT_APP_ALT12_OUT                 (PORT_MODE_ALT_OUT + 0x00B0U)
#define PORT_APP_ALT13_OUT                 (PORT_MODE_ALT_OUT + 0x00C0U)
#define PORT_APP_ALT14_OUT                 (PORT_MODE_ALT_OUT + 0x00D0U)
#define PORT_APP_ALT15_OUT                 (PORT_MODE_ALT_OUT + 0x00E0U)
#define PORT_APP_ALT16_OUT                 (PORT_MODE_ALT_OUT + 0x00F0U)
#define PORT_APP_ALT1_IN                   (PORT_MODE_ALT_IN + 0x0000U) 
#define PORT_APP_ALT2_IN                   (PORT_MODE_ALT_IN + 0x0010U) 
#define PORT_APP_ALT3_IN                   (PORT_MODE_ALT_IN + 0x0020U) 
#define PORT_APP_ALT4_IN                   (PORT_MODE_ALT_IN + 0x0030U) 
#define PORT_APP_ALT5_IN                   (PORT_MODE_ALT_IN + 0x0040U) 
#define PORT_APP_ALT6_IN                   (PORT_MODE_ALT_IN + 0x0050U) 
#define PORT_APP_ALT7_IN                   (PORT_MODE_ALT_IN + 0x0060U) 
#define PORT_APP_ALT8_IN                   (PORT_MODE_ALT_IN + 0x0070U) 
#define PORT_APP_ALT9_IN                   (PORT_MODE_ALT_IN + 0x0080U) 
#define PORT_APP_ALT10_IN                  (PORT_MODE_ALT_IN + 0x0090U) 
#define PORT_APP_ALT11_IN                  (PORT_MODE_ALT_IN + 0x00A0U) 
#define PORT_APP_ALT12_IN                  (PORT_MODE_ALT_IN + 0x00B0U) 
#define PORT_APP_ALT13_IN                  (PORT_MODE_ALT_IN + 0x00C0U) 
#define PORT_APP_ALT14_IN                  (PORT_MODE_ALT_IN + 0x00D0U) 
#define PORT_APP_ALT15_IN                  (PORT_MODE_ALT_IN + 0x00E0U) 
#define PORT_APP_ALT16_IN                  (PORT_MODE_ALT_IN + 0x00F0U) 
#define PORT_APP_ALT1_DIRECT               (PORT_MODE_ALT_DIRECT + 0x0000U)
#define PORT_APP_ALT2_DIRECT               (PORT_MODE_ALT_DIRECT + 0x0010U)
#define PORT_APP_ALT3_DIRECT               (PORT_MODE_ALT_DIRECT + 0x0020U)
#define PORT_APP_ALT4_DIRECT               (PORT_MODE_ALT_DIRECT + 0x0030U)
#define PORT_APP_ALT5_DIRECT               (PORT_MODE_ALT_DIRECT + 0x0040U)
#define PORT_APP_ALT6_DIRECT               (PORT_MODE_ALT_DIRECT + 0x0050U)
#define PORT_APP_ALT7_DIRECT               (PORT_MODE_ALT_DIRECT + 0x0060U)
#define PORT_APP_ALT8_DIRECT               (PORT_MODE_ALT_DIRECT + 0x0070U)
#define PORT_APP_ALT9_DIRECT               (PORT_MODE_ALT_DIRECT + 0x0080U)
#define PORT_APP_ALT10_DIRECT              (PORT_MODE_ALT_DIRECT + 0x0090U)
#define PORT_APP_ALT11_DIRECT              (PORT_MODE_ALT_DIRECT + 0x00A0U)
#define PORT_APP_ALT12_DIRECT              (PORT_MODE_ALT_DIRECT + 0x00B0U)
#define PORT_APP_ALT13_DIRECT              (PORT_MODE_ALT_DIRECT + 0x00C0U)
#define PORT_APP_ALT14_DIRECT              (PORT_MODE_ALT_DIRECT + 0x00D0U)
#define PORT_APP_ALT15_DIRECT              (PORT_MODE_ALT_DIRECT + 0x00E0U)
#define PORT_APP_ALT16_DIRECT              (PORT_MODE_ALT_DIRECT + 0x00F0U)

/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/
/* Type definition for Port_PinType used by the API Port_SetPinDirection() */
typedef uint16 Port_PinType;

/* Type definition for Port_PinDirectionType used by the API
 * Port_SetPinDirection()
 */
typedef enum ETag_Port_PinDirectionType
{
  PORT_PIN_IN = 0x00,
  PORT_PIN_OUT = 0x01,
  PORT_PIN_DEFAULT
} Port_PinDirectionType;

/* Type definition for Port_PinModeType used by the API
 * Port_SetPinMode()
 */
typedef uint32 Port_PinModeType;

/***********************************************************************************************************************
**                                                 Constant Data Type                                                 **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                        Extern declarations for Global Data                                         **
***********************************************************************************************************************/
#define PORT_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Port_MemMap.h"

extern CONST(Port_ConfigType, PORT_CONST) Port_GaaConfiguration[];                                                      /* PRQA S 3684 # JV-01 */

#define PORT_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Port_MemMap.h"

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/
#define PORT_START_SEC_PUBLIC_CODE
#include "Port_MemMap.h"

/* External Declaration for Port Initialization API. */
extern FUNC(void, PORT_PUBLIC_CODE) Port_Init(P2CONST(Port_ConfigType, AUTOMATIC, PORT_APPL_CONST) ConfigPtr);

#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
/* External Declaration for Port Set pin direction API. */
extern FUNC(void, PORT_PUBLIC_CODE) Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction);
#endif

/* External Declaration for Port refresh port direction API. */
extern FUNC(void, PORT_PUBLIC_CODE) Port_RefreshPortDirection(void);

#if (PORT_VERSION_INFO_API == STD_ON)
extern FUNC(void, PORT_PUBLIC_CODE)
                                Port_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, PORT_APPL_DATA) versioninfo); /* PRQA S 3432 # JV-01 */

#endif /*(PORT_VERSION_INFO_API == STD_ON)*/

#if (PORT_SET_PIN_MODE_API == STD_ON)
/* External Declaration for Port set pin mode API. */
extern FUNC(void, PORT_PUBLIC_CODE) Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode);
#endif

#if (PORT_SET_TO_DIO_ALT_MODE_API == STD_ON)
extern FUNC(void, PORT_PUBLIC_CODE) Port_SetToDioMode(const Port_PinType LddPinNumber);

extern FUNC(void, PORT_PUBLIC_CODE) Port_SetToAlternateMode(const Port_PinType LddPinNumber);
#endif

#if ((PORT_SET_PIN_DEFAULT_DIRECTION_API == STD_ON) && (PORT_SET_PIN_DIRECTION_API == STD_ON))
/* External Declaration for Port Set pin direction API. */
extern FUNC(void, PORT_PUBLIC_CODE) Port_SetPinDefaultDirection(const Port_PinType LddPinNumber);
#endif

#if (PORT_ECM_ERRORIN_API == STD_ON)
extern FUNC(boolean, PORT_PUBLIC_CODE) Port_EcmMaskERRORIN(const boolean LblMask);

extern FUNC(void, PORT_PUBLIC_CODE) Port_EcmClearERRORIN(void);
#endif

#define PORT_STOP_SEC_PUBLIC_CODE
#include "Port_MemMap.h"

#endif /* PORT_H */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
