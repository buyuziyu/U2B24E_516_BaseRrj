/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Adc_Types.h                                                                                         */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Provision of Database declaration.                                                                                 */
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
 * 2.4.0: 31/05/2025 : Update SW-VERSION for RH850/Ver21.01.01 U2Cx release
 * 2.3.1: 31/03/2025 : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 *                     Support QAC 11.6.0: add Msg(2:4641)
 * 2.3.1: 28/02/2025 : Update SW-VERSION for Ver22.00.02 U2Ax Beta 1 Release
 * 2.3.0: 28/02/2025 : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0: 31/12/2024 : As part of ARDAACJ-572 support, following changes are made:
 *                     1.Add preprocessor directive ADC_RESULT_DATA_TYPE to support DMA transfer 4-byte data
 *                     2.Defined ADC_RESULT_DATA_16_BITS and ADC_RESULT_DATA_32_BITS macros
 * 2.1.3: 31/10/2024 : Update SW-VERSION 2.1.3
 * 2.1.2: 30/09/2024 : Update SW-VERSION 2.1.2
 * 2.1.1: 30/08/2024 : As part of U2Bx-E support, following changes are made:
 *                     1.Add pTnHChannelSelectValue Adc_ConfigType struct.
 *                   : As part of Multi-core support, following changes are made:
 *                     1.Add item ucCoreIndex to Adc_ConfigType struct.
 * 2.0.1: 18/10/2023 : Fix QAC support Amendment 2 
 * 2.0.0: 28/08/2023 : Removed Multi-Instance define.
 * 1.4.4: 15/07/2022 : Changed the initialization of Adc_SelfDiagModeType enumerators to explicit.
 *        29/06/2022 : Remvoed the type Adc_Pic2ADTenType in U2Ax and U2Bx.
 *        20/06/2022 : Added pHwTriggConfig and removed pGroupHWTrigg and pGroupSGTrigg of Adc_ConfigType in U2Ax.
 *        15/06/2022 : Defined ADC_SELF_DIAG_WIRE_BRK as exactly the same value as ADC_SELF_DIAG_WIRE_BRK_MODE1
 *                     in order to use ADC_SELF_DIAG_WIRE_BRK_MODE1 in Adc_SelfDiagModeType in common.
 * 1.4.3: 18/05/2022 : Changed the compile switch macro for HW Trigger.
 *                     Fixed the typos in comments.
 *        15/04/2022 : Changed the pointers to the structure of HW trigger configuration for U2Bx.
 * 1.4.1: 24/11/2021 : Changed the conditions of compile switches to support ADCK.
 *                     Added instance 4 to the suppression of duplicate inclusion.
 * 1.3.2: 06/09/2021 : Update header file macro to call file multiple times.
 * 1.3.1: 07/07/2021 : Changed comment format to 120 columns
 *        01/06/2021 : Changed to the appropriate memory classes and pointer classes.
 *        07/04/2021 : Changed to comply with coding rules.
 * 1.2.0: 14/07/2020 : Release
 * 1.1.0: 19/06/2020 : Release
 * 1.0.1: 13/04/2020 : Remove ADC_TYPES_SW_MAJOR_VERSION,
 *                     ADC_TYPES_SW_MINOR_VERSION.
 * 1.0.0: 09/01/2020 : Initial Version
 */
/**********************************************************************************************************************/
#ifndef ADC_TYPES_H
#define ADC_TYPES_H


/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                             To support different AUTOSAR releases in a single package                              **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR Release version information */
#define ADC_TYPES_AR_RELEASE_MAJOR_VERSION    ADC_AR_RELEASE_MAJOR_VERSION_VALUE                                        /* PRQA S 1534 # JV-01 */
#define ADC_TYPES_AR_RELEASE_MINOR_VERSION    ADC_AR_RELEASE_MINOR_VERSION_VALUE                                        /* PRQA S 1534 # JV-01 */
#define ADC_TYPES_AR_RELEASE_REVISION_VERSION ADC_AR_RELEASE_REVISION_VERSION_VALUE                                     /* PRQA S 1534 # JV-01 */

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (1:1534)    : The macro '%1s' is declared but not used within this project.                                */
/* Rule                : MISRA C:2012 Rule-2.5                                                                        */
/* JV-01 Justification : This is accepted. This macro is used by other file.                                          */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1535)    : The typedef '%1s' is declared but not used within this project.                              */
/* Rule                : MISRA C:2012 Rule-2.3                                                                        */
/* JV-01 Justification : This is accepted. This type is used by other file.                                           */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1536)    : The tag '%1s' is declared but not used within this project.                                  */
/* Rule                : MISRA C:2012 Rule-2.4                                                                        */
/* JV-01 Justification : This is accepted. This tag is used by other file.                                            */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:4641)    : The identifier '%1s' could conflict in the future with the name of a macro in '<%2s>'.       */
/* Rule                : CWE Rule CWE-398, CWE-569                                                                    */
/* JV-01 Justification : This message is just a notice to avoid using this identifier as a macro                      */
/*                       in standard library in the future                                                            */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/
/* Priority Implementation values */
#define ADC_PRIORITY_NONE  0U
#define ADC_PRIORITY_HW    1U                                                                                           /* PRQA S 1534 # JV-01 */                                                                                     
#define ADC_PRIORITY_HW_SW 2U

/* Alignment */
#define ADC_ALIGN_RIGHT    0U
#define ADC_ALIGN_LEFT     1U                                                                                           /* PRQA S 1534 # JV-01 */

/* Result Data Type */
#define ADC_RESULT_DATA_16_BITS    0U
#define ADC_RESULT_DATA_32_BITS    1U

/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/
#if (ADC_ENABLE_DISABLE_CHANNEL == STD_ON)
/* Numeric ID of an ADC channel. */
typedef uint8 Adc_ChannelType;
#endif

/* Type of channel resolution in number of bits. */
typedef uint8 Adc_ResolutionType;                                                                                       /* PRQA S 1535 # JV-01 */

/* Numeric ID of an ADC channel group */
typedef uint8 Adc_GroupType;

/*
 * Type for reading the converted values of a channel group (raw, without
 * further scaling, right or left aligned depending on configuration).
 */
#if (ADC_RESULT_DATA_TYPE == ADC_RESULT_DATA_16_BITS)
typedef uint16 Adc_ValueGroupType;
#else
typedef uint32 Adc_ValueGroupType;
#endif /* (ADC_RESULT_DATA_TYPE == ADC_RESULT_DATA_16_BITS) */

/* Type for configuring the number of group conversions in stream access mode. */
typedef uint8 Adc_StreamNumSampleType;

/* Define type for AD Converter Trigger Out Control Register */
#if (ADC_IP_ADCH == STD_ON)
typedef uint32 Adc_Pic2ADTenType;
#endif /* (ADC_IP_ADCH == STD_ON) */

/* Current status of the conversion of the requested ADC Channel group */
typedef enum ETag_Adc_StatusType                                                                                        /* PRQA S 1536, 4641 # JV-01, JV-01 */
{
  ADC_IDLE,
  ADC_BUSY,
  ADC_COMPLETED,
  ADC_STREAM_COMPLETED
} Adc_StatusType;

/* Type for configuring the trigger source for an ADC Channel group */
typedef enum ETag_Adc_TriggerSourceType                                                                                 /* PRQA S 1536, 4641 # JV-01, JV-01 */
{
  ADC_TRIGG_SRC_SW,
  ADC_TRIGG_SRC_HW
} Adc_TriggerSourceType;                                                                                                /* PRQA S 1535 # JV-01 */

/* Type for configuring the conversion mode of an ADC Channel group */
typedef enum ETag_Adc_GroupConvModeType                                                                                 /* PRQA S 1536, 4641 # JV-01, JV-01 */
{
  ADC_CONV_MODE_ONESHOT,
  ADC_CONV_MODE_CONTINUOUS
} Adc_GroupConvModeType;

/* Type for configuring the streaming access mode buffer type. */
typedef enum ETag_Adc_StreamBufferModeType                                                                              /* PRQA S 1536, 4641 # JV-01, JV-01 */
{
  ADC_STREAM_BUFFER_LINEAR,
  ADC_STREAM_BUFFER_CIRCULAR
} Adc_StreamBufferModeType;                                                                                             /* PRQA S 1535 # JV-01 */

/* Type for configuring the access mode to group conversion results */
typedef enum ETag_Adc_GroupAccessModeType                                                                               /* PRQA S 1536, 4641 # JV-01, JV-01 */
{
  ADC_ACCESS_MODE_SINGLE,
  ADC_ACCESS_MODE_STREAMING
} Adc_GroupAccessModeType;                                                                                              /* PRQA S 1535 # JV-01 */

/* Type for replacement mechanism, which is used on ADC group level */
typedef enum ETag_Adc_GroupReplacementType                                                                              /* PRQA S 1536, 4641 # JV-01, JV-01 */
{
  ADC_GROUP_REPL_ABORT_RESTART,
  ADC_GROUP_REPL_SUSPEND_RESUME
} Adc_GroupReplacementType;                                                                                             /* PRQA S 1535 # JV-01 */

/*
 * Type for configuring on which edge of the hardware trigger signal the
 * driver should reach, i.e. start the conversion
 */
typedef enum ETag_Adc_HwTriggerSignalType                                                                               /* PRQA S 1536, 4641 # JV-01, JV-01 */
{
  ADC_HW_TRIG_RISING_EDGE,
  ADC_HW_TRIG_FALLING_EDGE,
  ADC_HW_TRIG_BOTH_EDGES
} Adc_HwTriggerSignalType;                                                                                              /* PRQA S 1535 # JV-01 */

/* Type of processing mode of the HW unit */
typedef enum ETag_Adc_FunctionalityModeType                                                                             /* PRQA S 1536, 4641 # JV-01, JV-01 */
{
  ADC_INTERRUPT_MODE,
  ADC_POLLING_MODE,
  ADC_POLLING_INTERRUPT_MODE
} Adc_FunctionalityModeType;

/* Type for configuring the Self Diag */
typedef enum ETag_Adc_SelfDiagModeType                                                                                  /* PRQA S 1536, 4641 # JV-01, JV-01 */
{
  ADC_SELF_DIAG_OFF            = 0,
  ADC_SELF_DIAG_PIN_LVL        = 1,
  ADC_SELF_DIAG_CONV_CKT       = 2,
  ADC_SELF_DIAG_WIRE_BRK_MODE1 = 3,
  ADC_SELF_DIAG_WIRE_BRK_MODE2 = 4,
  ADC_SELF_DIAG_WIRE_BRK       = ADC_SELF_DIAG_WIRE_BRK_MODE1
} Adc_SelfDiagModeType;

/* Priority level of the channel. Lowest priority is 0 */
typedef uint8 Adc_GroupPriorityType;                                                                                    /* PRQA S 1535 # JV-01 */

/* Data Structure required for initializing the ADC unit */
typedef struct STag_Adc_ConfigType                                                                                      /* PRQA S 1536 # JV-01 */
{
  /* Database start value - ADC_DBTOC_VALUE */
  uint32 ulStartOfDbToc;

  /* Pointer to the ADC HW unit configuration. */
  P2CONST(void, TYPEDEF, ADC_CONFIG_DATA) pHWUnitConfig;

  /* Pointer to the ADC SG unit configuration. */
  P2CONST(void, TYPEDEF, ADC_CONFIG_DATA) pSgUnitConfig;

  /* Pointer to the ADC channel group configuration. */
  P2CONST(void, TYPEDEF, ADC_CONFIG_DATA) pGroupConfig;

  #if (ADC_ENABLE_PIC_TSEL == STD_ON)
  #if ((ADC_IP_ADCJ == STD_ON) || (ADC_IP_ADCK == STD_ON))
  /* Pointer to the ADC HW triggers configuration */
  P2CONST(void, TYPEDEF, ADC_CONFIG_DATA) pHwTriggConfig;
  #endif /* ((ADC_IP_ADCJ == STD_ON) || (ADC_IP_ADCK == STD_ON)) */

  #if (ADC_IP_ADCH == STD_ON)
  /* Pointer to the ADC HW triggers of the HW channel groups configured. */
  P2CONST(void, TYPEDEF, ADC_CONFIG_DATA) pGroupHWTrigg;
  /* Pointer to the ADC HW trigger output control values for scan group. */
  P2CONST(void, TYPEDEF, ADC_CONFIG_DATA) pGroupSGTrigg;
  /* Pointer to the ADC trigger output configuration values. */
  P2CONST(void, TYPEDEF, ADC_CONFIG_DATA) pTriggOutConfigValue;
  /* Pointer to the ADC trigger output configuration registers */
  P2CONST(void, TYPEDEF, ADC_CONFIG_DATA) pTriggOutConfigRegister;
  #endif /* (ADC_IP_ADCH == STD_ON) */
  #endif /* (ADC_ENABLE_PIC_TSEL == STD_ON) */

  #if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
  /* Pointer to limit check range values. */
  P2CONST(void, TYPEDEF, ADC_CONFIG_DATA) pLimitCheckRange;
  #endif

  #if (ADC_ENABLE_DMA_MODE == STD_ON)
  /* Pointer to the ADC DMA channel configuration */
  P2CONST(void, TYPEDEF, ADC_CONFIG_DATA) pDmaUnitConfig;
  /* Pointer to the ADC group of internal RAM data. */
  P2CONST(void, TYPEDEF, ADC_CONFIG_DATA) pDmaHWUnitMapping;
  /* Pointer to the ADC HW unit of internal RAM data. */
  P2CONST(void, TYPEDEF, ADC_CONFIG_DATA) pDmaSGUnitMapping;
  #endif /* (ADC_ENABLE_DMA_MODE == STD_ON) */

  /* Pointer to the ADC runtime internal RAM data. */
  P2CONST(void, TYPEDEF, ADC_CONFIG_DATA) pChannelToGroup;

  /* Pointer to the ADC HW unit */
  P2CONST(void, TYPEDEF, ADC_CONFIG_DATA) pHwUnitIndex;
  /* Pointer to the ADC SG unit. */
  P2CONST(void, TYPEDEF, ADC_CONFIG_DATA) pSgUnitIndex;

  /* Pointer to the ADC channel group Ram data unit. */
  volatile P2VAR(void, TYPEDEF, ADC_VAR_NO_INIT) pGroupRamData;
  /* Pointer to the ADC SG unit ram data. */
  volatile P2VAR(void, TYPEDEF, ADC_VAR_NO_INIT) pSgUnitRamData;

  #if (ADC_ENABLE_DISABLE_CHANNEL == STD_ON)
  /* Pointer to the ADC channel configured in group. */
  volatile P2VAR(void, TYPEDEF, ADC_VAR_NO_INIT) pChannelToDisableEnable;
  #endif

  /* Pointer to the wait time configuration. */
  P2CONST(void, TYPEDEF, ADC_CONFIG_DATA) pWaittimeConfig;

  #if (ADC_TRACK_AND_HOLD_CHANNEL_IO_SELECT == STD_ON)
  /* Pointer to the ADC Track and Hold channel select registers. */
  P2CONST(void, TYPEDEF, ADC_VAR_NO_INIT) pTnHChannelSelectValue;
  #endif /* (ADC_TRACK_AND_HOLD_CHANNEL_IO_SELECT == STD_ON) */

  /* Indicates the number of SW triggered groups in the corresponding AdcConfigSet. */
  uint8 ucMaxSwTriggGroups;

  /* Total number of groups configured in the config set. */
  uint8 ucNoOfGroups;

  #if (ADC_ENABLE_DMA_MODE == STD_ON)
  /* Parameter indicates the number of DMA channel IDs configured in the corresponding configuration set. */
  uint8 ucMaxDmaChannels;
  #endif

  #if (ADC_ENABLE_DISABLE_CHANNEL == STD_ON)
  /* Parameter indicates the number of channel configured in the groups. */
  uint8 ucNoOfChannels;
  #endif

  #if (ADC_MULTI_CORE_SUPPORT == STD_ON)
  /* Parameter indicates kernel core ID if multi-core support */
  uint8 ucCoreIndex;
  #endif
} Adc_ConfigType;


#endif /* ADC_TYPES_H */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
