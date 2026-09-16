/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Adc_PBTypes.h                                                                                       */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains the type definitions of Post-build Time Parameters                                              */
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
 * 2.5.1: 30/06/2025 : Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.03 release
 *                     Remove SW-VERSION in file header
 * 2.5.0: 30/06/2025 : Update SW-VERSION for RH850/Ver22.01.00 (D) U2Ax release
 *        31/05/2025 : As part of U2Ax support, following changes are made:
 *                     1. Move Adc_GaaWaitTimeConfig into ADC_START_SEC_CONFIG_DATA_POSTBUILD_16
 * 2.4.0: 31/05/2025 : Update SW-VERSION for RH850/Ver21.01.01 U2Cx release
 * 2.3.1: 31/03/2025 : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 *        28/03/2025 : Remove element usTrackHoldChannelSelect in struct Adc_HwUnitConfigType
 * 2.3.1: 28/02/2025 : Update SW-VERSION for Ver22.00.02 U2Ax Beta 1 Release
 * 2.3.0: 28/02/2025 : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0: 31/12/2024 : As part of ARDAACJ-572 support, following changes are made:
 *                     1.Add preprocessor directive ADC_RESULT_DATA_TYPE to support DMA transfer 4-byte data
 *                     2.Change type of element pBuffer of STag_AdcChannelGroupRamData struct from uint16 
 *                       to Adc_ValueGroup Type
 * 2.1.3: 31/10/2024 : Update SW-VERSION 2.1.3
 * 2.1.2: 30/09/2024 : Update SW-VERSION 2.1.2
 * 2.1.1: 30/08/2024 : As part of ARDAACL-45752 support, following changes are made:
 *                     1.Change ADC_START_SEC_CONFIG_DATA_8 to ADC_START_SEC_CONFIG_DATA_POSTBUILD_8
 *                       and ADC_STOP_SEC_CONFIG_DATA_8 to ADC_STOP_SEC_CONFIG_DATA_POSTBUILD_8
 *                     2.Change ADC_START_SEC_CONFIG_DATA_32 to ADC_START_SEC_CONFIG_DATA_POSTBUILD_32
 *                       and ADC_STOP_SEC_CONFIG_DATA_32 to ADC_STOP_SEC_CONFIG_DATA_POSTBUILD_32
 *                   : As part of U2Bx-E support, following changes are made:
 *                     1.Add ucTnHChannelIndex in struct Adc_GroupConfigType
 *                     2.Add pTnHChSelectReg, usTrackHoldChannelSelect in struct Adc_HwUnitConfigType
 *                   : As part of U2Cx support, following changes are made:
 *                     3.Add the macros to support PWM-Diag
 * 2.0.1: 14/10/2023 : Support Autosar R22-11, fix acceptance findings, support QAC Amendment 2
 *                     1. Change macro ADC_AR_R21_11_VERSION to ADC_AR_R22_11_VERSION support Autosar version.
 *                     2. Cast ADC_ONE to uint8
 *                     3. Add message 1534, 1536
 *        11/10/2023 : Change ADC_START_SEC_CONFIG_DATA_UNSPECIFIED to ADC_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
 *                     and ADC_STOP_SEC_CONFIG_DATA_UNSPECIFIED to ADC_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED.
 * 2.0.0: 28/08/2023 : Removed Multi-Instance define. Change Adc_Mapping.h to Adc_Memmap.h
 *        11/06/2023 : Change macro ADC_AR_2111_VERSION to ADC_AR_R21_11_VERSION support Autosar version.
 * 1.5.0: 19/04/2023 : Added the ADC_AR_2111_VERSION compile switch area.
 * 1.4.5: 12/09/2022 : Moved member ulDmaSourceAddress from struct Adc_GroupConfigType to struct Adc_HwSgUnitType.
 *                     Removed the members ulLimitCheckChannelMask1, ulLimitCheckChannelMask2 and ucLimitCheckIndex
 *                     of struct Adc_GroupConfigType.
 *                     Separated each bit of ucGroupSettings into independent variables.
 *                     Removed macro definitions for handling ucGroupSettings.
 *                     Removed macro definitions for ADC operation mode mask.
 * 1.4.4: 12/07/2022 : Removed the macros ADC_THACR_SGS and ADC_GTM_HW_TRIGGER_NOT_USED.
 *                     Added new macros ADC_TH_SAMPLING, ADC_ADCX_SGCR_TRGMD and ADC_SCAN_MODE_CONTINUOUS.
 *        29/06/2022 : Removed member ulErrImrMask of Adc_HwUnitConfigType.
 *                     Removed member ucSgUnitIndex of Adc_HwUnitDataType in U2Ax.
 *        20/06/2022 : Added members aaPicTriggReg, pPicTriggControlRegs, ucSgUnitOffset, pSgTriggReg,
 *                     and removed members pPicTenRegisters, ucVCRegIndex of Adc_HwUnitConfigType in U2Ax.
 *                     Added member ulSgTriggValue, and removed member pSgUnitPicBaseAddress, pSgUnitTSELBaseAddress
 *                     of Adc_HwSgUnitType in U2Ax.
 *                     Added members ucTriggConfigIndex, ucPicTriggControlIndex, ucPicTriggSelectIndex,
 *                     and removed members ucPicSetOffset, usTriggerEdgeValue of Adc_GroupConfigType in U2Ax.
 *                     Removed Adc_GaaSgTriggType, Adc_GaaHWGroupTrigg, and Adc_GaaPicTenRegisters in U2Ax.
 *        15/06/2022 : Added ucTrackHoldEnable and ucTrackHoldWait of Adc_HwUnitConfigType in U2Ax.
 *                     Removed ucTrackHoldMask of Adc_HwSgUnitType in U2Ax.
 *                     Added ucTrackHoldControl of Adc_GroupConfigType in U2Ax.
 *                     Renamed macro ADC_STOP_HW_CONVERSION to ADC_ADCX_ADHALTR_HALT.
 *                     Renamed macro ADC_STOP_SG_CONVERSION to ADC_ADCX_SGSTPCR_SGSTP.
 *                     Renamed macro ADC_START_CONVERSION to ADC_ADCX_SGSTCR_SGST.
 *                     Renamed macro ADC_START_ADTIMER to ADC_ADCX_ADTSTCR_ADTST.
 *                     Renamed macro ADC_STOP_ADTIMER to ADC_ADCX_ADTENDCR_ADTEND.
 * 1.4.3: 18/05/2022 : Renamed ucSgUnitIndex to ucSgUnitOffset in Adc_HwUnitConfigType.
 *                     Renamed ucTrackHoldMask to ucTrackHoldEnable in Adc_HwUnitConfigType.
 *                     Moved the structures Adc_TriggConfigType and Adc_HwTriggConfigType to PIC header.
 *                     Fixed the typos in comments.
 *        15/04/2022 : Removed the declaration of global variables for trigger configuration in U2Bx.
 *                     Removed the trigger selection values for U2Bx in group configuration.
 *                     Added indexes to PIC trigger configuration for U2Bx to group configuration.
 *                     Removed the trigger edge value for U2Bx in group configuration.
 *                     Removed the flag for having an SG start trigger for U2Bx in HW unit configuration.
 *                     Added the variable of first SG unit index for U2Bx to HW unit configuration.
 *                     Changed the PIC trigger configuration for U2Bx in HW unit configuration to new structure.
 *                     Added the variable of default value for U2Bx from SG unit configuration.
 *                     Moved the pointer to trigger configuration for U2Bx from SG unit to HW unit configuration.
 *                     Added the new structures of HW trigger configuration for U2Bx.
 *                     Moved the volatile qualifier of pointer into argument of P2VAR macro.
 *                     Changed the type of value of ADC_HWUNIT_0 and ADC_SCANGROUP_0 to uint32.
 * 1.4.1: 24/11/2021 : Changed the conditions of compile switches to support ADCK.
 *                     Added track & hold related members to the HW unit configuration.
 *                     Added instance 4 to the suppression of duplicate inclusion.
 *                     Added DMA request group information for ADCK.
 * 1.3.2: 10/09/2021 : Moved macros of ECM keycode from ADCH header.
 *                     Changed the type of DMA descriptor to Adc_DmaDescSetType.
 *        08/09/2021 : Changed the names of macro for handling EIC registers.
 *        06/09/2021 : Update header file macro to call file multiple times.
 *        03/09/2021 : Added new macro ADC_ADCX_DIR_SFT to get information on high-order bits.
 *        26/08/2021 : Added a new member variable blPwmDiag to the structure Adc_GroupConfigType.
 * 1.3.1: 12/07/2021 : Added the structure Adc_HwUnitDataType.
 *                     Removed ucStreamingSamples in struct Adc_ChannelGroupRamData.
 *                     Changed the type of ucBufferStatus in Adc_ChannelGroupRamData to boolean.
 *                     Removed the redundant conditions of compile switches.
 *                     Integrated the ADC_DET_REPORT_ERROR_NOFLAG and ADC_DET_REPORT_ERROR into ADC_DET_RUNTIME_ERROR.
 *                     Removed unused macros.
 *        07/07/2021 : Added QAC message 9.5.0
 *                     Changed comment format to 120 columns
 *                     Changed violation tag from START/END
 *        24/06/2021 : Removed the macro that not using.
 *        16/06/2021 : Move scan group definition to "Adc_ADCH_PBTypes.h", "Adc_ADCJ_PBTypes.h".
 *        01/06/2021 : Changed to the appropriate memory classes and pointer classes.
 *        24/05/2021 : Change the position of an external function declaration.
 *        07/04/2021 : Changed to comply with coding rules.
 * 1.3.0: 19/12/2020 : Change macro ADC_TIMEOUT_COUNT to macro ADC_DMA_TIMEOUT_COUNT.
 *        11/12/2020 : Add new macro ADC_AD_TIMER_TIMEOUT_COUNT
 *        09/12/2020 : Add new macro ADC_GTM_HW_TRIGGER_NOT_USED
 *        06/12/2020 : Remove ucTriggOutConfigOffset in struct
 *                     Adc_GroupConfigType
 * 1.2.0: 14/07/2020 : Release
 *        27/07/2020 : Add QAC 9.3.1 comment.
 * 1.1.1: 08/07/2020 : Remove pDmaImrRegaddress, ulDmaImrMask in struct
 *                     Adc_DmaConfigType
 * 1.1.0: 19/06/2020 : Release
 * 1.0.3: 18/06/2020 : Change blWaitTimeEnabled to ucWaitTimeIndex.
 *                     Add macro ADC_WAITTIME_DISABLED
 *                     Move macro ADC_INVALID_CHANNELID from Adc_ADCJ_PBTypes.h,
 *                     Adc_ADCH_PBTypes.h to Adc_PBTypes.h and change the value
 *                     to 0xFF
 * 1.0.2: 12/05/2020 : Update macro DET_REPORT_ERROR to ADC_DET_REPORT_ERROR,
 *                     DET_REPORT_ERROR_NOFLAG to ADC_DET_REPORT_ERROR_NOFLAG
 * 1.0.1: 13/04/2020 : Update software version definition.
 * 1.0.0: 09/01/2020 : Initial Version
 */
/**********************************************************************************************************************/
#ifndef ADC_PBTYPES_H
#define ADC_PBTYPES_H

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR Release version information */
#define ADC_ADCX_PBTYPES_AR_RELEASE_MAJOR_VERSION    ADC_AR_RELEASE_MAJOR_VERSION
#define ADC_ADCX_PBTYPES_AR_RELEASE_MINOR_VERSION    ADC_AR_RELEASE_MINOR_VERSION
#define ADC_ADCX_PBTYPES_AR_RELEASE_REVISION_VERSION ADC_AR_RELEASE_REVISION_VERSION

/* Module Software version information */
#define ADC_ADCX_PBTYPES_SW_MAJOR_VERSION            ADC_SW_MAJOR_VERSION
#define ADC_ADCX_PBTYPES_SW_MINOR_VERSION            ADC_SW_MINOR_VERSION

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:0342)    : Using the glue operator '##'.                                                                */
/* Rule                : MISRA C:2012 Rule-20.10, CERTCCM PRE05                                                       */
/* JV-01 Justification : This can be accepted, due to the implementation is following AUTOSAR standard rule for SchM  */
/*                       module's name.                                                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE Rule CWE-398, CWE-569                                            */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is accepted. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3684)    : Array declared with unknown size.                                                            */
/* Rule                : MISRA C:2012 Rule-8.11, CERTCCM ARR02                                                        */
/* JV-01 Justification : Arrays used are verified in the file which are only declarations and size is configuration   */
/*                       dependent.                                                                                   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1534)    : The macro '%1s' is declared but not used within this project.                                */
/* Rule                : MISRA C:2012 Rule-2.5                                                                        */
/* JV-01 Justification : This is accepted. This macro is used by other file.                                          */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1536)    : The tag '%1s' is declared but not used within this project.                                  */
/* Rule                : MISRA C:2012 Rule-2.4                                                                        */
/* JV-01 Justification : This is accepted. This tag is used by other file.                                            */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/
/* Module Software version information */
#define ADC_DBTOC_VALUE                  (((uint32)ADC_VENDOR_ID_VALUE << 22U) |                                        /* PRQA S 1534 # JV-01 */\
                                          ((uint32)ADC_MODULE_ID_VALUE << 14U) | \
                                          ((uint32)ADC_SW_MAJOR_VERSION_VALUE << 8U) | \
                                          ((uint32)ADC_SW_MINOR_VERSION_VALUE << 3U))

/* Adc driver initialization status */
#define ADC_UNINITIALIZED                (boolean)0
#define ADC_INITIALIZED                  (boolean)1

/* Adc condition flag value */
#define ADC_FALSE                        (boolean)0
#define ADC_TRUE                         (boolean)1
#define ADC_ONE                          (uint8)0x01U                                                                   /* PRQA S 1534 # JV-01 */

/* Adc hardware unit ID */
#define ADC_HWUNIT_0                     0UL
#define ADC_HWUNIT_1                     1UL
#define ADC_HWUNIT_2                     2UL
#define ADC_HWUNIT_3                     3UL                                                                            /* PRQA S 1534 # JV-01 */
#define ADC_HWUNIT_A                     4UL
#define ADC_SINGLE_HWUNIT                1UL

/* Adc scan group ID */
#define ADC_SCANGROUP_0                  0UL
#define ADC_SCANGROUP_1                  1UL
#define ADC_SCANGROUP_2                  2UL
#define ADC_SCANGROUP_3                  3UL
#define ADC_SCANGROUP_4                  4UL

/* Adc register initialize value */
#define ADC_REG_BYTE_INIT                (uint8)0x00U
#define ADC_REG_WORD_INIT                (uint16)0x0000U
#define ADC_REG_DWORD_INIT               (uint32)0x00000000UL

/* Adc local variable initialize value */
#define ADC_VAL_BYTE_INIT                (uint8)0x00U
#define ADC_VAL_DWORD_INIT               (uint32)0x00000000UL                                                           /* PRQA S 1534 # JV-01 */

/* Adc count variable initialize value */
#define ADC_COUNT_BYTE_INIT              (uint8)0x00U
#define ADC_COUNT_BYTE_ONE               (uint8)0x01U
#define ADC_COUNT_DWORD_INIT             (uint32)0x00000000UL

/* Adc various number value */
#define ADC_NUM_CHANNEL_ZERO             (uint8)0x00U
#define ADC_NUM_SCANMODE                 (uint8)0x02U                                                                   /* PRQA S 1534 # JV-01 */

/* Adc calculation value */
#define ADC_BYTE_ZERO                    (uint8)0x00U
#define ADC_WORD_ZERO                    (uint16)0x0000U
#define ADC_DWORD_ZERO                   (uint32)0x00000000UL
#define ADC_BYTE_ONE                     (uint8)0x01U
#define ADC_SHIFT_BYTE                   8U

/* Adc scan group setting values */
/* Adc conversion start/stop value */
#define ADC_ADCX_SGSTCR_SGST             (uint8)0x01U
#define ADC_ADCX_ADHALTR_HALT            (uint8)0x01U
#define ADC_ADCX_SGSTPCR_SGSTP           (uint8)0x01U

/* Adc conversion trigger mode value */
#define ADC_ADCX_SGCR_TRGMD_HW           (uint8)(1U << 0U)
#define ADC_ADCX_SGCR_TRGMD_ADTIMER      (uint8)(1U << 1U)
#define ADC_ADCX_SGCR_TRGMD              (uint8)(ADC_ADCX_SGCR_TRGMD_HW | ADC_ADCX_SGCR_TRGMD_ADTIMER)

/* Adc scan group status mask */
#define ADC_SGACT_STATUS                 (uint8)0x02U
#define ADC_ADTACT_STATUS                (uint8)0x04U

/* Adc scan group conversion end interrupt enable value */
#define ADC_ADCX_SGCR_ADIE               (uint8)0x10U

/* Adc conversion suspend method */
#define ADC_ASYNCHRONOUS_SUSPEND         (uint8)0x02U

/* Adc AIR of DMA register reset value */
#define ADC_AIR_DSEL_INIT                (uint32)0x0F000000UL                                                           /* PRQA S 1534 # JV-01 */

/* Adc AD timer feature value */
#define ADC_ADTIMER_SG                   (uint8)3U                                                                      /* PRQA S 1534 # JV-01 */
#define ADC_ADCX_ADTSTCR_ADTST           (uint8)0x01U
#define ADC_ADCX_ADTENDCR_ADTEND         (uint8)0x01U
#define ADC_ADCX_ADTPRR_INIT_VALUE       (uint32)0x001FFFFFUL

/* Macros for Virtual Channel Register */
#define ADC_ADCX_VCR_GCTRL               (uint32)0x0000003FUL
#define ADC_ADCX_VCR_ADIE                (uint32)0x00000080UL                                                           /* PRQA S 1534 # JV-01 */

/* Macros for Upper/Lower Limit Check Register */
#define ADC_ADCX_VCLMSCR1_ALL_MASK       (uint32)0xFFFFFFFFUL                                                           /* PRQA S 1534 # JV-01 */
#define ADC_ADCX_VCULLMTBR_OFF           (uint32)0xFFFFFFFFUL                                                           /* PRQA S 1534 # JV-01 */
#define ADC_ADCX_VCLMSR_HIGH_SHIFT       5U                                                                             /* PRQA S 1534 # JV-01 */
#define ADC_ADCX_VCLMSR_HIGH_MASK        (uint32)0x00000001UL                                                           /* PRQA S 1534 # JV-01 */
#define ADC_ADCX_VCLMSR_LOW_MASK         (uint32)0x0000001FUL                                                           /* PRQA S 1534 # JV-01 */
#define ADC_VCLM_1                       0U                                                                             /* PRQA S 1534 # JV-01 */
#define ADC_VCLM_2                       1U                                                                             /* PRQA S 1534 # JV-01 */

/* Macros for Parity Error Register */
#define ADC_ADCX_PER_PE                  (uint8)(1U << 7U)

/* Macros for Overwrite Error Register */
#define ADC_ADCX_OWER_OWECAP             (uint8)0x3FU
#define ADC_ADCX_OWER_OWE                (uint8)(1U << 7U)

/* Macros for Error Clear Register */
#define ADC_ADCX_ECR_PEC                 (Adc_ErrClearRegType)(1UL << 1U)
#define ADC_ADCX_ECR_OWEC                (Adc_ErrClearRegType)(1UL << 2U)

/* Adc channel mask for disable/enable channel function */
#define ADC_CHANNEL_ID_MASK              (uint32)0x0000003FUL                                                           /* PRQA S 1534 # JV-01 */

/* Macros for Data Supplementary Information Register */
#define ADC_ADCX_DIR_IDEF                (uint32)(1UL << 26U)
#define ADC_ADCX_DIR_IDEF_ERR            (uint32)0UL
#define ADC_ADCX_DIR_DR                  (uint32)0x0000FFFFUL
#define ADC_ADCX_DIR_SFT                 16U                                                                            /* PRQA S 1534 # JV-01 */

/* EIC register mask value */
#define ADC_EIC_EIMK                     (uint8)(1U << 7U)
#define ADC_EIC_EIRF                     (uint16)(1UL << 12U)

/* Keycode value for protection register access */
#define ADC_ECM_KEYCODE_DISABLE          (uint32)0xA5A5A500UL
#define ADC_ECM_KEYCODE_ENABLE           (uint32)0xA5A5A501UL

/* Macro for ADCXnTDCR.TDLV mask */
#define ADC_TDCR_TDLV_BIT                (uint8)0x83U                                                                   /* PRQA S 1534 # JV-01 */

/* Each function disable flag in conversion group */
#define ADC_DMA_CHANNEL_OFF              (uint8)0xFFU
#define ADC_INTERRUPT_OFF                (uint32)0xFFFFFFFFUL                                                           /* PRQA S 1534 # JV-01 */

/* Flag/status clear value */
#if (ADC_RESULT_DATA_TYPE == ADC_RESULT_DATA_16_BITS)
#define ADC_RESULT_BUF_INIT              (uint16)0x0000U
#else
#define ADC_RESULT_BUF_INIT              (uint32)0x00000000U
#endif /* (ADC_RESULT_DATA_TYPE == ADC_RESULT_DATA_16_BITS) */

/* Queue status value */
#define ADC_QUEUE_EMPTY                  (uint8)0x00U                                                                   /* PRQA S 1534 # JV-01 */
#define ADC_QUEUE_FILLED                 (uint8)0x01U                                                                   /* PRQA S 1534 # JV-01 */
#define ADC_QUEUE_FULL                   (uint8)0x02U                                                                   /* PRQA S 1534 # JV-01 */

/* Check value of WFLG bit */
#define ADC_RESULT_AVAILABLE             (uint32)0x02000000UL

/* ADC functionality mode value */
#define ADC_INTERRUPT                    0U
#define ADC_POLLING                      1U
#define ADC_POLLING_INTERRUPT            2U

/* Macro for invalid Group index */
#define ADC_INVALID_GROUP                (Adc_GroupType)0xFFU

#if (ADC_ENABLE_PWM_DIAG == STD_ON)
/* Macros for handling PWM-Diag */
#define ADC_ADCX_PWDCR_DISABLE           (uint8)0U
#define ADC_ADCX_PWDCR_PWE               (uint8)1U
#define ADC_ADCX_PWDSGCR_DISABLE         (uint8)0U
#define ADC_ADCX_PWDSGCR_TRGMD           (uint8)1U
#define ADC_ADCX_PWVCLMINTER_DISABLE     (uint8)0U
/* Macros to indicate PWM-Diag channel */
#define ADC_ADCX_PER_PECAP_PWD           (uint8)0x70U
#define ADC_ADCX_IDER_IDECAP_PWD         (uint8)0x70U
/* Macro for accessing PWM-Diag Data and Information */
#define ADC_PWM_DIAG_NUM_DATA            2UL
#endif /* (ADC_ENABLE_PWM_DIAG == STD_ON) */

/* Time out wait for status of register */
/*
 * Define time out wait for status of register DMAjCHSTA as 20us which is half of 40us (maximum duration of ISR)
 * If LS IntOSC is used, this should be excluded as the 2 cycles of CLK_HBUS alone exceed 40us.
 * As per actual measure when HS IntOSC is used, timeout measurement is:
 * CLK_HBUS is 25MHz, timeout is around 20us
 * CLK_HBUS = 100Mhz, timeout is around 5us
 * therefore ADC_DMA_TIMEOUT_COUNT is defined as 0x46
 */
#define ADC_DMA_TIMEOUT_COUNT            (uint32)0x00000046UL

/* Time out wait for status of AD Timer register */
/*
 * As per information from HW Team, AD Timer stops immediately. So define ADC_AD_TIMER_TIMEOUT_COUNT = 3
 * ADTACT = 0 can normally be received on the first register read.
 * However, define it as 3 times in total, because 1 more time for when ADTACT = 0 cannot be received
 * on the first register read and 1 more time as a margin.
 */
#define ADC_AD_TIMER_TIMEOUT_COUNT       (uint32)0x00000003UL

/* Adc read and clear enable value for result register */
#define ADC_READ_AND_CLEAR_ENABLE        (uint8)0x10U

/* Macro for wait time disable */
#define ADC_WAITTIME_DISABLED            (uint8)0xFFU

/* Macro for invalid channel ID */
#define ADC_INVALID_CHANNELID            (uint8)0xFFU

/* Macro for T&H sampling */
#define ADC_TH_SAMPLING                  (uint8)(1U << 5U)

/***********************************************************************************************************************
**                                              Critical Section Macros                                               **
***********************************************************************************************************************/
#if (ADC_CRITICAL_SECTION_PROTECTION == STD_ON)
#define ADC_ENTER_CRITICAL_SECTION(Exclusive_Area) SchM_Enter_Adc_##Exclusive_Area()                                    /* PRQA S 0342 # JV-01 */
#define ADC_EXIT_CRITICAL_SECTION(Exclusive_Area)  SchM_Exit_Adc_##Exclusive_Area()                                     /* PRQA S 0342 # JV-01 */
#else /* (ADC_CRITICAL_SECTION_PROTECTION == STD_ON) */
#define ADC_ENTER_CRITICAL_SECTION(Exclusive_Area)
#define ADC_EXIT_CRITICAL_SECTION(Exclusive_Area)
#endif /* (ADC_CRITICAL_SECTION_PROTECTION == STD_ON) */

/***********************************************************************************************************************
**                                              DET Report Error Macros                                               **
***********************************************************************************************************************/
#if (ADC_AR_VERSION == ADC_AR_422_VERSION)
#if (ADC_DEV_ERROR_DETECT == STD_ON)
#define ADC_DET_RUNTIME_ERROR(ModuleId, InstanceId, ApiId, ErrorId) \
  (void)Det_ReportError(ModuleId, InstanceId, ApiId, ErrorId)
#else /* ADC_DEV_ERROR_DETECT == STD_OFF */
#define ADC_DET_RUNTIME_ERROR(ModuleId, InstanceId, ApiId, ErrorId)
#endif /* (ADC_DEV_ERROR_DETECT == STD_ON) */
#elif (ADC_AR_VERSION == ADC_AR_431_VERSION)
#define ADC_DET_RUNTIME_ERROR(ModuleId, InstanceId, ApiId, ErrorId) \
  (void)Det_ReportRuntimeError(ModuleId, InstanceId, ApiId, ErrorId)
#elif (ADC_AR_VERSION == ADC_AR_R22_11_VERSION)
#define ADC_DET_RUNTIME_ERROR(ModuleId, InstanceId, ApiId, ErrorId) \
  (void)Det_ReportRuntimeError(ModuleId, InstanceId, ApiId, ErrorId)
#endif /* (ADC_AR_VERSION == ADC_AR_422_VERSION) */

/***********************************************************************************************************************
**                                              DEM Report Error Macros                                               **
***********************************************************************************************************************/
#if (ADC_AR_VERSION == ADC_AR_422_VERSION)
#define ADC_DEM_REPORT_ERROR(EventId, EventStatus) (void)Dem_ReportErrorStatus(EventId, EventStatus)
#elif (ADC_AR_VERSION == ADC_AR_431_VERSION)
#define ADC_DEM_REPORT_ERROR(EventId, EventStatus) (void)Dem_SetEventStatus(EventId, EventStatus)
#elif (ADC_AR_VERSION == ADC_AR_R22_11_VERSION)
#define ADC_DEM_REPORT_ERROR(EventId, EventStatus) (void)Dem_SetEventStatus(EventId, EventStatus)
#endif

/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/

/***********************************************************************************************************************
** Structure for DMA channel configuration for SGx unit                                                               **
***********************************************************************************************************************/
#if (ADC_ENABLE_DMA_MODE == STD_ON)
typedef struct STag_Adc_DmaConfigType                                                                                   /* PRQA S 1536 # JV-01 */
{
  /* Address for DMA control registers */
  P2VAR(volatile Adc_DmaRegisters, TYPEDEF, REGSPACE) pDmaRegBaseaddress;

  /* Address for Interrupt control registers */
  P2VAR(volatile uint16, TYPEDEF, REGSPACE) pDmaEicRegaddress;

  /* Descriptor RAM address */
  P2VAR(volatile Adc_DmaDescSetType, TYPEDEF, REGSPACE) pDmaDescriptoraddress;

  /* Resource register value */
  uint32 ulDmaResourceValue;

  /* Descriptor address pointer */
  uint16 usDmaDescriptorPointer;

  #if (ADC_IP_ADCK == STD_ON)
  /* Address for DMA Transfer Request Group Selection Register */
  P2VAR(volatile uint32, TYPEDEF, REGSPACE) pDMACSEL;

  /* Index of DMA unit */
  uint8 ucDmaUnit;

  /* DMA Request Group */
  uint8 ucDmaRequestGroup;
  #endif /* (ADC_IP_ADCK == STD_ON) */
} Adc_DmaConfigType;
#endif /* (ADC_ENABLE_DMA_MODE == STD_ON) */

/***********************************************************************************************************************
** Structure for Channel Group RAM data                                                                               **
***********************************************************************************************************************/
typedef struct STag_Adc_ChannelGroupRamData                                                                             /* PRQA S 1536 # JV-01 */
{
  /* Result Buffer pointer */
  P2VAR(Adc_ValueGroupType, TYPEDEF, ADC_APPL_DATA) pChannelBuffer;                                                     /* PRQA S 3432 # JV-01 */

  /* Result Buffer current pointer */
  P2VAR(Adc_ValueGroupType, TYPEDEF, ADC_APPL_DATA) pBuffer;                                                            /* PRQA S 3432 # JV-01 */

  /* Stores the conversion status of the requested group */
  Adc_StatusType enGroupStatus;

  #if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
  /* Stores the Group Notification Status */
  boolean blNotifyStatus;
  #endif

  #if (ADC_DEV_ERROR_DETECT == STD_ON)
  /* Stores the buffer pointer initialization Status */
  boolean blBufferStatus;
  #endif

  #if (ADC_HW_TRIGGER_API == STD_ON)
  /* Stores the enable hardware trigger status */
  boolean blHwTriggStatus;
  #endif

  #if ((ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) || (ADC_ENABLE_QUEUING == STD_ON))
  /* Stored the status if the group is present in queue */
  boolean blGrpPresent;
  #endif /* ((ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) || (ADC_ENABLE_QUEUING == STD_ON)) */

  #if (ADC_ENABLE_DISABLE_CHANNEL == STD_ON)
  /* Stored the number of disabled channels */
  uint8 ucNoOfDisabledChannels;
  #endif

  /* Indicates if the transition to ADC_COMPLETED should be prevented after the group reaches ADC_STREAM_COMPLETED */
  boolean blResultRead;

  /* Stores the number of channels in the group, excluding disabled channels */
  uint8 ucChannelCount;

  /* Stores the count of conversion completed channels */
  uint8 ucChannelsCompleted;
  /* Stores the count of conversion completed samples */
  uint8 ucSamplesCompleted;
  /* Stores the number of channels to skip before resuming */
  uint8 ucIsrSkipCount;

  #if (((((ADC_ENABLE_ID_ERR == STD_ON) && (ADC_IP_ADCH == STD_OFF)) || (ADC_ENABLE_LIMIT_CHECK == STD_ON)) && \
        (ADC_ENABLE_ERR_INT == STD_ON)) || (ADC_ENABLE_PARITY_ERR_INT == STD_ON))
  /* Stores the status if the conversion fails */
  boolean blConvError;
  #endif
  #if (ADC_ENABLE_ID_ERR == STD_ON)
  /* Stores the channel where the Id error occurred */
  uint8 ucChannelIdError;
  #endif
  #if (ADC_ENABLE_OVERWRITE_ERR == STD_ON)
  /* Stores the channel where the overwrite occurred */
  uint8 ucChannelOverwritten;
  #endif
  #if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
  /* Stores the channel where the limit error occurred */
  uint8 ucChannelLimitError;
  #endif
  #if (ADC_ENABLE_TRIGGER_OVERLAP_ERR == STD_ON)
  /* Stores the status when triggers overlap */
  boolean blTriggerOverlapped;
  #endif
  #if (ADC_ENABLE_PARITY_ERR == STD_ON)
  /* Stores the channel where the parity error occurred */
  uint8 ucChannelParityError;
  #endif
} Adc_ChannelGroupRamData;

/***********************************************************************************************************************
** Structure for Scan Group unit RAM data                                                                             **
***********************************************************************************************************************/
typedef struct STag_Adc_SgUnitRamData                                                                                   /* PRQA S 1536 # JV-01 */
{
  /* Stores the current conversion group */
  Adc_GroupType ddCurrentConvGroup;

  #if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)
  /* Stores the current conversion group priority */
  Adc_GroupPriorityType ddCurrentPriority;
  #endif /* (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) */

  #if ((ADC_ENABLE_START_STOP_GROUP_API == STD_ON) && \
       ((ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) || (ADC_ENABLE_QUEUING == STD_ON)))
  /* Stores the queue status */
  uint8 ucQueueStatus;
  /* Stores the queue counter */
  uint8 ucQueueCounter;
  #endif

  /* Stores the status of SG unit */
  boolean blSgUnitStatus;
} Adc_SgUnitRamData;

/***********************************************************************************************************************
** Structure for Scan Group unit configuration                                                                        **
***********************************************************************************************************************/
typedef struct STag_Adc_HwSgUnitType                                                                                    /* PRQA S 1536 # JV-01 */
{
  #if (ADC_ENABLE_PIC_TSEL == STD_ON)
  #if (ADC_IP_ADCH == STD_ON)
  /* Pointer to user base address of PIC Control registers */
  P2VAR(volatile Adc_PicRegisters, TYPEDEF, REGSPACE) pSgUnitPicBaseAddress;
  #endif /* (ADC_IP_ADCH == STD_ON) */
  #endif /* (ADC_ENABLE_PIC_TSEL == STD_ON) */

  #if ((ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) || (ADC_ENABLE_QUEUING == STD_ON))
  /* Pointer to the Priority Queue */
  P2VAR(volatile Adc_GroupType, TYPEDEF, ADC_VAR_NO_INIT) pQueue;
  #endif /* ((ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) || (ADC_ENABLE_QUEUING == STD_ON)) */

  /* Indicates if the SGx unit is configured in interrupt or polling mode */
  Adc_FunctionalityModeType enFunctionalityModeType;

  #if ((ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) || (ADC_ENABLE_QUEUING == STD_ON))
  /* Maximum Queue Size when software priority or first come first serve mechanism is enabled. */
  uint8 ucAdcSgQueueSize;
  #endif /* ((ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) || (ADC_ENABLE_QUEUING == STD_ON)) */

  /* SGx unit to which Scan group is configured */
  uint8 ucSgUnitId;

  #if (ADC_ENABLE_DMA_MODE == STD_ON)
  /* Index of the DMA channel Id configured for this SGx in the array Adc_GaaDmaUnitConfig[]. */
  uint8 ucDmaChannelIndex;
  #endif

  /* Wait time to stop the scan group */
  uint32 ulVcrProcessWait;

  #if (ADC_ENABLE_ADC_TSEL == STD_ON)
  /* Trigger selection for ADCXnSGTSELx */
  uint32 ulSgTriggValue;
  #endif /* (ADC_ENABLE_ADC_TSEL == STD_ON) */

  #if (ADC_ENABLE_DMA_MODE == STD_ON)
  /* Source address for the DMA channel mapped to the SG unit */
  uint32 ulDmaSourceAddress;
  #endif
} Adc_HwSgUnitType;

/***********************************************************************************************************************
** Structure for HW unit configuration                                                                                **
***********************************************************************************************************************/
typedef struct STag_Adc_HwUnitConfigType                                                                                /* PRQA S 1536 # JV-01 */
{
  #if ((ADC_ENABLE_ERR == STD_ON) || (ADC_ENABLE_PARITY_ERR == STD_ON))
  /* Pointer to Error callback notification */
  P2FUNC(void, ADC_APPL_CODE, pErrorNotificationPointer)(uint8 LucChannel);                                             /* PRQA S 3432 # JV-01 */
  #endif

  #if (ADC_ENABLE_TRIGGER_OVERLAP_ERR == STD_ON)
  /* Pointer to Error callback notification (SG) */
  P2FUNC(void, ADC_APPL_CODE, pErrorNotificationPointerSG)(uint8 LucScanGroup);                                         /* PRQA S 3432 # JV-01 */
  #endif

  /* Pointer to user base address of ADC Control registers */
  P2VAR(volatile Adc_ConfigRegisters, TYPEDEF, REGSPACE) pHwUnitBaseAddress;

  /* Pointer to ADC HW unit SG0 interrupt control register */
  P2VAR(volatile uint16, TYPEDEF, REGSPACE) pEicRegAddress;

  #if (ADC_ENABLE_ERR_INT == STD_ON)
  /* Pointer to base address of error interrupt register */
  P2VAR(volatile uint32, TYPEDEF, REGSPACE) pErrEicRegAddress;
  #endif

  #if (ADC_ENABLE_PIC_TSEL == STD_ON)
  #if ((ADC_IP_ADCJ == STD_ON) || (ADC_IP_ADCK == STD_ON))
  /* Pointer array for A/D Converter Selection Control Registers */
  P2VAR(volatile Adc_PicTriggRegType, TYPEDEF, REGSPACE) aaPicTriggReg[ADC_NUM_OF_TRIGG_SELECT];

  /* Pointer to A/D Converter Trigger Output Control Register */
  P2CONST(Adc_PicTriggControlRegsType, TYPEDEF, ADC_CONFIG_DATA) pPicTriggControlRegs;
  #endif /* ((ADC_IP_ADCJ == STD_ON) || (ADC_IP_ADCK == STD_ON)) */

  #if (ADC_IP_ADCH == STD_ON)
  /* Pointer to A/D Converter Trigger Output Control Register */
  P2CONST(void, TYPEDEF, ADC_CONFIG_DATA) pPicTenRegisters;
  #endif /* (ADC_IP_ADCH == STD_ON) */
  #endif /* (ADC_ENABLE_PIC_TSEL == STD_ON) */

  #if (ADC_ENABLE_ADC_TSEL == STD_ON)
  /* Pointer for A/D Converter Selection Control Registers */
  P2VAR(volatile Adc_SgTriggRegType, TYPEDEF, REGSPACE) pSgTriggReg;
  #endif /* (ADC_ENABLE_ADC_TSEL == STD_ON) */

  #if (ADC_TRACK_AND_HOLD_CHANNEL_IO_SELECT == STD_ON)
  /* Pointer for T&H Physical IO Select Registers */
  P2VAR(volatile Adc_TrackHoldSelectType, TYPEDEF, REGSPACE) pTnHChSelectReg;
  #endif /* (ADC_TRACK_AND_HOLD_CHANNEL_IO_SELECT == STD_ON) */

  #if ((ADC_IP_ADCJ == STD_ON) || (ADC_IP_ADCK == STD_ON))
  /* Stores the offset to the SG unit index configured for this HW unit */
  uint8 ucSgUnitOffset;
  #endif /* ((ADC_IP_ADCJ == STD_ON) || (ADC_IP_ADCK == STD_ON)) */

  /* Stores the count of number of SG units configured for this HW unit */
  uint8 ucSgUnitCount;

  #if ((ADC_ENABLE_ERR_INT == STD_ON) || (ADC_ENABLE_PARITY_ERR_INT == STD_ON))
  /* Indicates whether the error is handled by an interrupt */
  boolean blInterruptErr;
  #endif

  /* Index of Wait time table */
  uint8 ucWaitTimeIndex;

  #if (ADC_DEINIT_API == STD_ON)
  /* Number of virtual channels in the HW unit */
  uint8 ucMaxVirtualChannel;
  #endif

  #if ((ADC_ENABLE_ERR_INT == STD_ON) && (ADC_ENABLE_LIMIT_CHECK == STD_ON))
  /* Interrupt enable mask of limit check channels */
  uint32 ulLimitCheckInterruptMask1;
  uint32 ulLimitCheckInterruptMask2;
  #endif

  #if (ADC_TRACK_AND_HOLD == STD_ON)
  #if (ADC_IP_ADCK == STD_ON)
  /* Track and Hold group select for THGSR */
  uint16 usTrackHoldGroupSelect;
  #endif /* (ADC_IP_ADCK == STD_ON) */

  /* Track and Hold enabled channel flags for THER */
  uint8 ucTrackHoldEnable;

  /* Track and Hold wait time to start SW triggered group */
  uint8 ucTrackHoldWait;
  #endif /* (ADC_TRACK_AND_HOLD == STD_ON) */
} Adc_HwUnitConfigType;

/***********************************************************************************************************************
** Structure for HW unit runtime data                                                                                 **
***********************************************************************************************************************/
typedef struct STag_Adc_HwUnitDataType                                                                                  /* PRQA S 1536 # JV-01 */
{
  #if (ADC_IP_ADCH == STD_ON)
  /* Offset of SG index for Hw unit */
  uint8 ucSgUnitIndex;
  #endif /* (ADC_IP_ADCH == STD_ON) */

  /* SG unit status (BIT0..4 = SG0..4) */
  uint8 ucSgUnitStatus;

  #if (ADC_TRACK_AND_HOLD == STD_ON)
  /*
   * T&H status
   * BIT1..4 = 0: T&H has not started or has explicitly stopped in SG1..4.
   *           1: T&H has started or has implicitly stopped in SG1..4.
   * BIT5    = 0: T&H sampling has not started or has stopped.
   *           1: T&H sampling has started.
   */
  uint8 ucTrackHoldStatus;
  #endif /* (ADC_TRACK_AND_HOLD == STD_ON) */
} Adc_HwUnitDataType;

/***********************************************************************************************************************
** Structure for Group configuration                                                                                  **
***********************************************************************************************************************/
typedef struct STag_Adc_GroupConfigType                                                                                 /* PRQA S 1536 # JV-01 */
{
  #if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
  /* Pointer to callback notification */
  P2FUNC(void, ADC_APPL_CODE, pGroupNotificationPointer)(void);                                                         /* PRQA S 3432 # JV-01 */
  #endif

  #if (ADC_ENABLE_SELF_DIAG == STD_ON)
  Adc_SelfDiagModeType enAdcSelfDiagMode;
  #endif /* (ADC_ENABLE_SELF_DIAG == STD_ON) */

  #if (ADC_ENABLE_ADTIMER == STD_ON)
  /* Count that sets the initial phase of A/D timer */
  uint32 ulAdcTimerPeriod;
  /* Count that sets the cycle of A/D timer */
  uint32 ulAdcTimerPhaseDelay;
  #endif /* (ADC_ENABLE_ADTIMER == STD_ON) */

  /* Start virtual channel pointer */
  uint8 ucStartVirChPtr;

  #if (ADC_HW_TRIGGER_API == STD_ON)
  #if (ADC_IP_ADCH == STD_ON)
  uint16 usTriggerEdgeValue;
  #endif
  #endif

  #if (ADC_ENABLE_SELF_DIAG_PIN_LVL == STD_ON)
  uint8 ucAdcSelfdiagpinlevelMask;
  #endif

  #if ((ADC_ENABLE_SELF_DIAG_WIRE_BRK == STD_ON) || (ADC_ENABLE_WIRE_BRK == STD_ON))
  uint8 ucAdcSelfDiagWireBreakPulseWidth;
  #endif

  /* Number of Samples in Streaming Access Mode */
  Adc_StreamNumSampleType ddNumberofSamples;

  #if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)
  /* Software Priority configured for the group */
  Adc_GroupPriorityType ddGroupPriority;
  #endif /* (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) */

  /* Index of the hardware unit to which the group belongs */
  uint8 ucHwUnitIndex;
  /* Index of the SGx unit to which group is configured in the array Adc_GaaSgUnitConfig[] */
  uint8 ucSgUnitIndex;

  /* Index to the start of the channels configured for this group in the array Adc_GaaChannelToGroup[] */
  uint8 ucChannelToGroupIndex;

  /* The value to store in the SCANMD bit of the ADCXnSGCRx register */
  uint8 ucScanMode;

  #if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)
  /* The replacement mechanism used when group conversion is interrupted by a higher priority group */
  Adc_GroupReplacementType enGroupReplacement;
  #endif /* (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) */

  #if (ADC_ENABLE_DMA_MODE == STD_ON)
  /* Flag to indicate if the group uses DMA transfers, ADC_TRUE if it does */
  boolean blEnableDmaTransfer;
  #endif /* (ADC_ENABLE_DMA_MODE == STD_ON) */

  #if (ADC_ENABLE_STREAMING == STD_ON)
  /* The type of access mode indicating single or streaming */
  Adc_GroupAccessModeType enGroupAccessMode;
  /* The type of streaming buffer mode indicating linear or ring buffer */
  Adc_StreamBufferModeType enStreamBufferMode;
  #endif /* (ADC_ENABLE_STREAMING == STD_ON) */

  /* The type of conversion mode indicating one-shot or continuous */
  Adc_GroupConvModeType enGroupConvMode;

  /* Flag to indicate if the group is configured as implicitly stopped, ADC_TRUE if it is implicitly stopped */
  boolean blImplicitlyStopped;

  /* Number of channels configured in the group */
  uint8 ucChannelCount;

  #if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
  /* Flag to indicate if group contains Limit check enabled channel */
  boolean blLimitCheckEnabled;
  #endif

  #if (ADC_ENABLE_ADTIMER == STD_ON)
  /* AD Timer Trigger feature control for the logical group */
  boolean blAdcEnableAdTimerTriggMode;
  #endif

  #if (ADC_ENABLE_WIRE_BRK == STD_ON)
  /* Wiring break detection feature control for the logical group */
  boolean blAdcEnableWiringBreakDetection;
  #endif

  #if (ADC_ENABLE_PIC_TSEL == STD_ON)
  #if ((ADC_IP_ADCJ == STD_ON) || (ADC_IP_ADCK == STD_ON))
  /* Index of Trigger Configuration */
  uint8 ucTriggConfigIndex;
  /* Index of PIC Trigger Output Control */
  uint8 ucPicTriggControlIndex;
  /* Index of PIC Trigger Selection */
  uint8 ucPicTriggSelectIndex;
  #endif /* ((ADC_IP_ADCJ == STD_ON) || (ADC_IP_ADCK == STD_ON)) */

  #if (ADC_IP_ADCH == STD_ON)
  /*
   * In case there are any HW triggered groups configured in this SGx unit then ucPicSetOffset should provide
   * the index of the this SGx unit settings in the array Adc_GaaSgTriggType[], in case there are no HW triggered group
   * then this should point to 0xFF value
   */
  uint8 ucPicSetOffset;
  #endif /* (ADC_IP_ADCK == STD_ON) */
  #endif /* (ADC_ENABLE_PIC_TSEL == STD_ON) */

  #if (ADC_TRACK_AND_HOLD == STD_ON)
  #if (ADC_TRACK_AND_HOLD_CHANNEL_IO_SELECT == STD_ON)
  /* Index of T&H Channel Selection */
  uint8 ucTnHChannelIndex;
  #endif /* (ADC_TRACK_AND_HOLD_CHANNEL_IO_SELECT == STD_ON) */
  /* Track and Hold Operation Group name */
  uint8 ucTrackAndHoldGroup;

  /* Track and Hold control value */
  uint8 ucTrackHoldControl;
  #endif /* (ADC_TRACK_AND_HOLD == STD_ON) */

  #if (ADC_ENABLE_PWM_DIAG == STD_ON)
  /* Enable or disable PWM-Diag feature for this group */
  boolean blPwmDiag;
  #endif /* (ADC_ENABLE_PWM_DIAG == STD_ON) */
  
  #if ((ADC_MULTI_CORE_SUPPORT == STD_ON) & (ADC_DEV_ERROR_DETECT == STD_ON))
  /* Declare the variable to store list of configured core ID for the group */
  uint8 ucGroupCoreIndex;
  #endif
} Adc_GroupConfigType;

/***********************************************************************************************************************
** Structure for Limit Check Config                                                                                   **
***********************************************************************************************************************/
#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
typedef struct STag_Adc_LimitCheckConfigType                                                                            /* PRQA S 1536 # JV-01 */
{
  /* PIC register for AD converter trigger selection control */
  uint32 ulVCULLMTBR[ADC_NUM_OF_LIMIT_TABLE];
} Adc_LimitCheckConfigType;
#endif

/***********************************************************************************************************************
**                                Extern declarations for Global Arrays Of Structures                                 **
***********************************************************************************************************************/
#define ADC_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Adc_MemMap.h"

/* Declaration for Hardware unit Configuration */
extern CONST(Adc_HwUnitConfigType, ADC_CONFIG_DATA) Adc_GaaHWUnitConfig[];                                              /* PRQA S 3684 # JV-01 */
/* Declaration for Group Configuration */
extern CONST(Adc_GroupConfigType, ADC_CONFIG_DATA) Adc_GaaGroupConfig[];                                                /* PRQA S 3684 # JV-01 */
/* Declaration for SG Unit Configuration */
extern CONST(Adc_HwSgUnitType, ADC_CONFIG_DATA) Adc_GaaSgUnitConfig[];                                                  /* PRQA S 3684 # JV-01 */

#if ((ADC_HW_TRIGGER_API == STD_ON) && (ADC_IP_ADCH == STD_ON))
/* Declaration for HW Group Configuration */
extern CONST(Adc_PicConfigType, ADC_CONFIG_DATA) Adc_GaaSgTriggType[];
#endif /* ((ADC_HW_TRIGGER_API == STD_ON) && (ADC_IP_ADCH == STD_ON)) */

#if (ADC_ENABLE_DMA_MODE == STD_ON)
/* Declaration for DMA Channel Configuration */
extern CONST(Adc_DmaConfigType, ADC_CONFIG_DATA) Adc_GaaDmaUnitConfig[];                                                /* PRQA S 3684 # JV-01 */
#endif

#define ADC_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Adc_MemMap.h"

#define ADC_START_SEC_CONFIG_DATA_POSTBUILD_16
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

extern CONST(Adc_WaitTimeConfigType, ADC_CONFIG_DATA) Adc_GaaWaitTimeConfig[];                                          /* PRQA S 3684 # JV-01 */

#define ADC_STOP_SEC_CONFIG_DATA_POSTBUILD_16
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define ADC_START_SEC_CONFIG_DATA_POSTBUILD_32
#include "Adc_MemMap.h"

/* Declaration for Channel to Group Configuration */
extern CONST(uint32, ADC_CONFIG_DATA) Adc_GaaChannelToGroup[];                                                          /* PRQA S 3684 # JV-01 */

#if ((ADC_HW_TRIGGER_API == STD_ON) && (ADC_IP_ADCH == STD_ON))
/* Declaration for HW Group Configuration */
extern CONST(uint32, ADC_CONFIG_DATA) Adc_GaaHWGroupTrigg[];
#endif /* ((ADC_HW_TRIGGER_API == STD_ON) && (ADC_IP_ADCH == STD_ON)) */

#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
/* Declaration for limit check enabled channel Configuration */
extern CONST(Adc_LimitCheckConfigType, ADC_CONFIG_DATA) Adc_GaaLimitCheckRange[];                                       /* PRQA S 3684 # JV-01 */
#endif

#if ((ADC_HW_TRIGGER_API == STD_ON) && (ADC_IP_ADCH == STD_ON))
/* Declaration for PIC2ADTEN registers */
extern CONST(Adc_PicTenRegisters, ADC_CONFIG_DATA) Adc_GaaPicTenRegisters[];
#endif /* ((ADC_HW_TRIGGER_API == STD_ON) && (ADC_IP_ADCH == STD_ON)) */

#define ADC_STOP_SEC_CONFIG_DATA_POSTBUILD_32
#include "Adc_MemMap.h"

#define ADC_START_SEC_CONFIG_DATA_POSTBUILD_8
#include "Adc_MemMap.h"

/* Declaration for Hardware Index Mapping array */
extern CONST(uint8, ADC_CONFIG_DATA) Adc_GaaHwUnitIndex[];                                                              /* PRQA S 3684 # JV-01 */
/* Declaration for Scan Group Index Mapping array */
extern CONST(uint8, ADC_CONFIG_DATA) Adc_GaaSgUnitIndex[];                                                              /* PRQA S 3684 # JV-01 */

#if (ADC_ENABLE_DMA_MODE == STD_ON)
/* Declaration for DMA Channel to HW unit mapping Configuration */
extern CONST(uint8, ADC_CONFIG_DATA) Adc_GaaHwUnit[];                                                                   /* PRQA S 3684 # JV-01 */
/* Declaration for DMA Channel to SGx unit mapping Configuration */
extern CONST(uint8, ADC_CONFIG_DATA) Adc_GaaSGUnit[];                                                                   /* PRQA S 3684 # JV-01 */
#endif

#define ADC_STOP_SEC_CONFIG_DATA_POSTBUILD_8
#include "Adc_MemMap.h"

#define ADC_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Adc_MemMap.h"

/* RAM Allocation of Group data */
extern volatile VAR(Adc_ChannelGroupRamData, ADC_VAR_NO_INIT) Adc_GaaGroupRamData[];                                    /* PRQA S 3684 # JV-01 */
/* RAM Allocation of hardware unit data */
extern volatile VAR(Adc_SgUnitRamData, ADC_VAR_NO_INIT) Adc_GaaSgUnitRamData[];                                         /* PRQA S 3684 # JV-01 */

#define ADC_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Adc_MemMap.h"

#define ADC_START_SEC_VAR_NO_INIT_8
#include "Adc_MemMap.h"

#if ((ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) || (ADC_ENABLE_QUEUING == STD_ON))
/* Hardware Unit Queue Size */
extern volatile VAR(Adc_GroupType, ADC_VAR_NO_INIT) Adc_GaaSgUnitPriorityQueue[];                                       /* PRQA S 3684 # JV-01 */
#endif /* ((ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) || (ADC_ENABLE_QUEUING == STD_ON)) */

#define ADC_STOP_SEC_VAR_NO_INIT_8
#include "Adc_MemMap.h"

#define ADC_START_SEC_VAR_NO_INIT_BOOLEAN
#include "Adc_MemMap.h"

#if (ADC_ENABLE_DISABLE_CHANNEL == STD_ON)
/* Declaration for Disable Channel Configuration */
extern volatile VAR(boolean, ADC_VAR_NO_INIT) Adc_GaaChannelToDisableEnable[];                                          /* PRQA S 3684 # JV-01 */
#endif

#define ADC_STOP_SEC_VAR_NO_INIT_BOOLEAN
#include "Adc_MemMap.h"

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/

#endif /* ADC_PBTYPES_HEADER */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
