/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Icu_PBTypes.h                                                                                       */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains macros and structure datatypes for post build parameters of ICU Driver                          */
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
 * 2.4.1:  30/06/2025  : Remove SW-VERSION in file header
 * 2.4.0:  30/05/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.01 Release
 * 2.3.1:  31/03/2025  : Update SW-VERSION for RH850/U2BxE MCAL Ver22.00.02 Release
 * 2.3.0:  28/02/2025  : As part of ARDAACL-52090, following changes are made:
 *                       1. Add macro ICU_16BIT_ZERO
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 * 2.1.2:  31/10/2024  : As part of support GTM HWIP into common code, following changes are made:
 *                       1. Add new GTM macro definition
 *                       2. Remove pEnableEdgeDetection and pDisableEdgeDetection
 *                       As part of support Postbuild variant, following changes are made:
 *                       1. Remove redundant extern configuration struct/array data from ecode.
 *                       As part of support QAC 9.5.0, following changes are made:
 *                       1. Remove QAC messages 1534, 1535, 1536.
 *                       Update SW-VERSION for Ver22.01.02 Beta2 Release 
 * 2.0.1:  20/10/2023  : Add QAC messages 1534, 1535, 1536, 1336
 *         14/10/2023  : Change macro name from ICU_AR_R21_11_VERSION to ICU_AR_R22_11_VERSION
 *                       Change memory section ICU_START/STOP_SEC_CONFIG_DATA_UNSPECIFIED to
 *                       ICU_START/STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
 * 2.0.0:  03/08/2023  : #include "Icu_Mapping.h" update to #include "Icu_MemMap.h"
 *                       Remove all multi-instance including methods
 *                       Remove all supported multi-instance header file
 *                       Add ucCoreIndex to typedef struct STag_Icu_ChannelConfigType
 * 1.4.5:  02/12/2022  : Add condition DEM Report for support AR21-11
 * 1.4.4:  09/06/2022  : Add macro ICU_FIVE and update cast type of pCntlRegs to void
 * 1.4.3:  17/04/2022  : Merge QAC message from U2Ax, E2x and U2Bx
 *         15/04/2022  : Removed un-used macros
 *                       ICU_TIMESTAMP_STARTED, ICU_TIMESTAMP_STOPPED, ICU_RESULT_NOT_AVAILABLE,
 *                       ICU_RESULT_AVAILABLE, ICU_UINTEGER_TRUE, ICU_UINTEGER_FALSE,
 *                       ICU_UINTEGER_IDLE, ICU_UINTEGER_ACTIVE, ICU_EIGHT, ICU_SIXTEEN,
 *                       ICU_WORD_ZERO, ICU_ATU_TIMERA_START_DWNCNT_VAL, 
 *                       ICU_ATU_TIMERC_START_DWNCNT_VAL, ICU_ATU_TIMERA_EDGE_CNT_VAL,
 *                       ICU_ATU_TIMERC_OVF_STS_CLR, ICU_HIGH_LOW_PERIOD_TIME_MASK, 
 *                       ICU_BOTH_EDGE_ENABLED_MASK, ICU_BUFFERSIZE_MIN_VAL, ICU_ZERO_BIT_SHIFT,
 *                       ICU_1BIT_LENGTH, ICU_1BIT_POS, ICU_TIMERA_DISABLE, ICU_TIMERA_ENABLE,
 *                       ICU_ENABLE_INTR_MASK, ICU_DEM_NOT_ERROR, ICU_DEM_ERROR
 * 1.4.1:  30/11/2021  : Add preprocessor ICU_EDGE_COUNT_API == STD_ON to Declaration preprocessor for ucChannelRunning
 *                       in struct Icu_TAUChannelRamDataType.
 *         15/09/2021  : Change Include Section
 *                       Rename Icu_TimerChannelConfigType to Icu_ChannelUserRegConfigType
 *                       Rename pHWTimerChannelConfig to pHWChannelUserRegConfig
 *                       Re-design Icu_ChannelRamDataType
 *                       Correct pre-processor directives, function names
 *                       Rename ATU5 -> ATU
 * 1.3.2:  30/08/2021  : Change from #include "Icu_MemMap.h" to #include "Icu_Mapping.h".
 *                       Update header file macro.
 * 1.3.1:  02/07/2021  : Add QAC message 9.5.0
 *                       Format source code to 120 characters
 *                       Improve Violation tag (remove START/END)
 *         13/05/2021  : Remove ICU_ATU_TIMER_GLOBL_MASK
 * 1.2.0:  17/07/2020  : Release
 * 1.1.0:  19/06/2020  : Release
 * 1.0.0:  25/03/2020  : Initial Version
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:0342)    : Using the glue operator '##'.                                                                */
/* Rule                : MISRA C:2012 Rule-20.10, CERTCCM PRE05                                                       */
/* JV-01 Justification : This can be accepted, due to the implementation is following AUTOSAR standard rule for SchM  */
/*                       module's name.                                                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:1336)    : Parameter identifiers missing in declaration of a function type.                             */
/* Rule                : MISRA C:2012 Rule-8.2, CWE Rule CWE-398, CWE-569                                             */
/* JV-01 Justification : Parameter identifiers are  missing however not impact the MCAL operation.                    */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE Rule CWE-398, CWE-569                                            */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is accepted. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3630)    : The implementation of this struct/union type should be hidden.                               */
/* Rule                : MISRA C:2012 Dir-4.8                                                                         */
/* JV-01 Justification : This is accepted. Redundant of struct or union type has no affect to driver operation.       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3684)    : Array declared with unknown size.                                                            */
/* Rule                : MISRA C:2012 Rule-8.11, CERTCCM ARR02                                                        */
/* JV-01 Justification : Arrays used are verified in the file which are only declarations and size is configuration   */
/*                       dependent.                                                                                   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/**********************************************************************************************************************/
#ifndef ICU_PBTYPES_H
#define ICU_PBTYPES_H

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for Macro definitions */
#include "Icu_Types.h"
#if (ICU_TAU_UNIT_USED == STD_ON)
#include "Icu_TAU_PBTypes.h"
#endif
#ifdef ICU_ATU_COMMON_PRESCALER_CONFIGURED
#if ((ICU_ATU_TIMER_UNIT_USED == STD_ON) || (ICU_ATU_COMMON_PRESCALER_CONFIGURED > 0))
#include "Icu_ATU_PBTypes.h"
#endif
#endif
#if ((ICU_IRQ_EDGE_DETECT == STD_ON) || (ICU_INTP_EDGE_DETECT == STD_ON))
#include "Icu_PIN_PBTypes.h"
#endif
#if (ICU_CRITICAL_SECTION_PROTECTION == STD_ON)
/* Included for the declaration of the critical section protection functions */
#include "SchM_Icu.h"
#endif
#if (ICU_GTM_TIMER_UNIT_USED == STD_ON)
#include "Icu_GTM_PBTypes.h"
#endif
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define ICU_PBTYPES_AR_RELEASE_MAJOR_VERSION    ICU_AR_RELEASE_MAJOR_VERSION
#define ICU_PBTYPES_AR_RELEASE_MINOR_VERSION    ICU_AR_RELEASE_MINOR_VERSION
#define ICU_PBTYPES_AR_RELEASE_REVISION_VERSION ICU_AR_RELEASE_REVISION_VERSION

/* Module Software version information */
#define ICU_PBTYPES_SW_MAJOR_VERSION            ICU_SW_MAJOR_VERSION
#define ICU_PBTYPES_SW_MINOR_VERSION            ICU_SW_MINOR_VERSION

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/
#define ICU_TRUE                          (boolean)0x01
#define ICU_FALSE                         (boolean)0x00
#define ICU_INITIALIZED                   (boolean)0x01
#define ICU_UNINITIALIZED                 (boolean)0x00

/* Macro to avoid Magic numbers */
#define ICU_DBTOC_VALUE (((uint32)ICU_VENDOR_ID_VALUE << 22UL) | ((uint32)ICU_MODULE_ID_VALUE << 14UL) | \
                              ((uint32)ICU_SW_MAJOR_VERSION_VALUE << 8UL) | ((uint32)ICU_SW_MINOR_VERSION_VALUE << 3UL))

#define ICU_HW_EXT_INTP                   (uint8)0x00
#define ICU_HW_EXT_IRQ                    (uint8)0x01
#define ICU_HW_TAUD                       (uint8)0x02
#define ICU_HW_TAUJ                       (uint8)0x03
#define ICU_HW_ATU_TIMERA                 (uint8)0x04
#define ICU_HW_ATU_TIMERC                 (uint8)0x05
#define ICU_HW_GTM_TIM                    (uint8)0x06

#define ICU_NORMAL_PORT                   (uint8)0x00
#define ICU_JTAG_PORT                     (uint8)0x01

#define ICU_ZERO                          (uint8)0x00
#define ICU_ONE                           (uint8)0x01
#define ICU_TWO                           (uint8)0x02
#define ICU_THREE                         (uint8)0x03
#define ICU_FOUR                          (uint8)0x04
#define ICU_FIVE                          (uint8)0x05
#define ICU_SIX                           (uint8)0x06
#define ICU_SEVEN                         (uint8)0x07
#define ICU_THIRTY_ONE                    (uint8)31U
#define ICU_SIXTY_THREE                   (uint8)63U
#define ICU_ONEHUNDRED_SEVENTY_SEVEN      (uint8)177U

#define ICU_DOUBLE_ZERO                   (uint32)0x00000000uL
#define ICU_16BIT_ZERO                    (uint16)0x0000U
#define ICU_DOUBLE_ONE                    (uint32)0x00000001uL
#define ICU_EDGECOUNT_RESET_VAL           (uint32)0xFFFFFFFFuL
#define ICU_TIMER_RESET_VAL               (uint16)0xFFFF
#define ICU_ATU_TIMER_INITIAL_CNT_VAL     (uint32)0x00000000uL
#define ICU_ATU_TIMER_STS_CLR             (uint8)0x01
#define ICU_CLK_BUS_SELECT_MASK           (uint8)0xF8
#define ICU_ATU_TIMERA_TIERA_INIT_VAL     (uint16)0x00FF
#define ICU_ATU_TIMERC_TIERC_INIT_VAL     (uint16)0x000F
#define ICU_RESET_ATU_TIMERC_TIERC_VAL    (uint16)0x0000
#define ICU_RESET_ATU_TIMERA_TIERA_VAL    (uint16)0x0000
#define ICU_BYPASS_MASK                   (uint8)0xF8
#define ICU_BOTH_EDGES_MASK               (uint8)0x03
#define ICU_FALLING_EDGE_MASK             (uint8)0x02
#define ICU_RISING_EDGE_MASK              (uint8)0x01
#define ICU_TIMESTAMP_RESET_CNT_VAL       (uint8)0x00
#define ICU_PERIOD_TIME_RESET_VAL         (uint8)0x00
#define ICU_ACTIVE_TIME_RESET_VAL         (uint8)0x00
#define ICU_TAU_CNT_INIT_VAL              (uint32)0x00000000UL
#define ICU_ATU_FALLING_EDGE_MASK         (uint8)0x02
#define ICU_ATU_RISING_EDGE_MASK          (uint8)0x01
#define ICU_ATU_BOTH_EDGE_MASK            (uint8)0x03
#define ICU_IRQ_FALLING_EDGE_MASK         (uint8)0x02
#define ICU_IRQ_RISING_EDGE_MASK          (uint8)0x03
#define ICU_LOW_TIME_MASK                 (uint8)0x00
#define ICU_HIGH_TIME_MASK                (uint8)0x01
#define ICU_PERIOD_TIME_MASK              (uint8)0x02
#define ICU_PERIOD_CHANNEL_ENABLED_MASK   (uint8)0x02
#define ICU_NC_PLL_ENABLE                 (uint8)0x80
#define ICU_NC_NCMSEL_MASK                (uint8)0x10

/* Macro used as mask and for initilizing */
#define ICU_WAKEUP_INFO_INIT_VAL          (uint32)0x00000000uL
#define ICU_NOTIFY_INTERVAL_MIN_VAL       (uint8)0x01
#define ICU_BUFFER_IDX_INIT_VAL           (uint8)0x00
#define ICU_SIGNAL_TIME_INIT_VAL          (uint8)0x00
#define ICU_ACTIVE_TIME_INIT_VAL          (uint8)0x00
#define ICU_PERIOD_TIME_INIT_VAL          (uint8)0x00
#define ICU_SIGNAL_PERIOD_TIME_INIT_VAL   (uint8)0x00
#define ICU_RESET_ATU_TIMERA_ATIOR1A_VAL  (uint16)0x0000
#define ICU_RESET_ATU_TIMERA_ATSCRA_VAL   (uint16)0x80FF
#define ICU_RESET_ATU_TIMERC_GRCmn_VAL    (uint32)0x00000000uL
#define ICU_RESET_ATU_TIMERC_TIORCm_VAL   (uint16)0x0000
#define ICU_RESET_ATU_TIMERC_TSCRCm_VAL   (uint16)0x0F1F
#define ICU_RESET_EXINTCTL_VAL            (uint8)0x00
#define ICU_RESET_ATU_NOISE_CANCELER_VAL  (uint8)0x00
#define ICU_RESET_ATU_NCMCR1A_VAL         (uint8)0x00
#define ICU_RESET_ATU_NCMCR2A_VAL         (uint8)0x00
#define ICU_RESET_ATU_TIOR2A_VAL          (uint32)0x00000000uL
#define ICU_RESET_ATU_NCMCR1C_VAL         (uint8)0x00
#define ICU_RESET_ATU_NCMCR2C_VAL         (uint8)0x00
#define ICU_SET_INPUT_CAPTURE_MODE        (uint8)0x04
#define ICU_ATUENR_TAE_ENABLE             (uint8)0x02
#define ICU_ATUENR_TCE_ENABLE             (uint8)0x08
#define ICU_PSCE_MASK_VALUE               (uint8)0x01
#define ICU_TSRC_OVERFLOW_VALUE           (uint16)0x0010
#define ICU_TSRA_OVERFLOW_VALUE           (uint16)0x8000

/* Macro used in DutyCycle function */
#define ICU_TS_CIRCULAR_BUFFER_MASK       (uint8)0x08
#define ICU_DUTY_PERIOD_ENABLED_MASK      (uint8)0x04
#define ICU_HIGH_LOW_TIME_MASK            (uint8)0x03
#define ICU_EXTRA_CHANNEL_DISABLED_MASK   (uint8)0x01

/* Macro for clearing pending interrupts */
#define ICU_CLEAR_PENDING_INTR_MASK       (uint16)0xEFFF
/* Macro for Enabling interrupts */
#define ICU_ENABLE_EIMK_MASK              (uint8)0x7F
/* Macro for Disable interrupts */
#define ICU_DISABLE_EIMK_MASK             (uint8)0x80
/* Macro for which wakeup not configured */
#define ICU_NOWAKEUP                      (uint8)0xFF

/***********************************************************************************************************************
**                                                      TIM Macros                                                    **
***********************************************************************************************************************/
/* Macro Mask to check if filter is configured for a particular channel */
#define ICU_FLT_CONFIG                    (uint32)0x00010000UL
/* Macro for masking CNTX registers for TIM Channel */
#define ICU_DOUBLE_CNTX                   (uint32)0x00FFFFFFUL
/* Macro for TIM NEWVALUE IRQ interrupt enable mask value */
#define ICU_NEWVAL_IRQ_EN                 (uint32)0x00000001UL
/* Macro for TIM IRQ enable mask value */
#define ICU_CNTOFL_IRQ_EN                 (uint32)0x00000004UL
/* Macro for TIM IRQ clear value */
#define TIM_IRQ_CLEAR                     (uint32)0x00000000UL
/* Macro for TIM IRQ Notification clear value */
#define TIM_IRQ_NOTIF_CLEAR               (uint32)0x0000001FUL
/* Macro for setting ISL bit for enabling detection of Both edges */
#define TIM_ISL_BOTH_EDGES                (uint32)0x00004000UL
/* Macro for setting ISL and DSL bit for enabling detection of Falling edges */
#define TIM_ISL_DSL_FALLING_EDGE          (uint32)0xFFFF9FFFUL
/* Macro for setting ISL bit for enabling detection of Rising edges */
#define TIM_ISL_RISING_EDGE               (uint32)0xFFFFBFFFUL
/* Macro for setting DSL bit for enabling detection of Rising edges */
#define TIM_DSL_RISING_EDGE               (uint32)0x00002000UL
/***********************************************************************************************************************
**                                          Interrupt Consistency Check Mask                                          **
***********************************************************************************************************************/
/* Interrupt Consistency check mask value */
#define ICU_EIC_EIMK_MASK                 (uint8)0x80

/***********************************************************************************************************************
**                                              DEM Report Error Macros                                               **
***********************************************************************************************************************/
#if (ICU_AR_VERSION == ICU_AR_422_VERSION)
#define ICU_DEM_REPORT_ERROR(EventId, EventStatus) (void)Dem_ReportErrorStatus(EventId, EventStatus)
#elif (ICU_AR_VERSION == ICU_AR_431_VERSION) || (ICU_AR_VERSION == ICU_AR_R22_11_VERSION)
#define ICU_DEM_REPORT_ERROR(EventId, EventStatus) (void)Dem_SetEventStatus(EventId, EventStatus)
#endif

/***********************************************************************************************************************
**                                      SchM Critical Section Protection Macros                                       **
***********************************************************************************************************************/
#if (ICU_CRITICAL_SECTION_PROTECTION == STD_ON)
#define ICU_ENTER_CRITICAL_SECTION(Exclusive_Area) SchM_Enter_Icu_##Exclusive_Area()                                    /* PRQA S 0342 # JV-01 */
#define ICU_EXIT_CRITICAL_SECTION(Exclusive_Area)  SchM_Exit_Icu_##Exclusive_Area()                                     /* PRQA S 0342 # JV-01 */
#else
#define ICU_ENTER_CRITICAL_SECTION(Exclusive_Area)
#define ICU_EXIT_CRITICAL_SECTION(Exclusive_Area)
#endif

/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                             Structure to store Signal Measurement channel data into RAM                            **
***********************************************************************************************************************/
typedef struct STag_Icu_SignalMeasurementModeRamDataType                                                                /* PRQA S 3630 # JV-01 */
{
  uint32 ulSignalActiveTime;
  uint32 ulSignalPeriodTime;
  uint32 ulPrevSignalActiveTime;
  uint8 ucPeriodMeasurementStatus;
} Icu_SignalMeasurementModeRamDataType;

/***********************************************************************************************************************
**                               Structure to store Edge Counting channel data into RAM                               **
***********************************************************************************************************************/
typedef struct STag_Icu_EdgeCountModeRamDatatype                                                                        /* PRQA S 3630 # JV-01 */
{
  uint32 ulIcuEdgeCount;
} Icu_EdgeCountModeRamDatatype;

/***********************************************************************************************************************
**                                 Structure to store Timestamp channel data into RAM                                 **
***********************************************************************************************************************/
typedef struct STag_Icu_TimeStampChannelRamDataType                                                                     /* PRQA S 3630 # JV-01 */
{
  P2VAR(uint32, TYPEDEF, ICU_CONFIG_DATA) pBufferPointer;                                                               /* PRQA S 3432 # JV-01 */
  uint16 usBufferSize;
  uint16 usTimestampIndex;
  uint16 usTimestampsCounter;
  uint16 usNotifyInterval;
  boolean blTimestampingStarted;
} Icu_TimeStampChannelRamDataType;

/* Period measurment state of an ICU channel */
typedef enum ETag_Icu_PeriodMeasurementStateType                                                                        
{
  ICU_PERIOD_IDLE,
  ICU_PERIOD_ONGOING
} Icu_PeriodMeasuremantStateType;

/***********************************************************************************************************************
**                                    Structure for ICU Timer Channel information                                     **
***********************************************************************************************************************/
typedef struct STag_Icu_ChannelUserRegConfigType                                                                        /* PRQA S 3630 # JV-01 */
{
  /* RAM variable index */
  uint8 ucRamDataIndex;
  /*
   *********************************************************************************************************************
   *******************                      Time Stamp Measurement channels                          *******************
   *********************************************************************************************************************
   * Bit 3    :   1: If ICU_CIRCULAR_BUFFER is selected for time stamp measurement mode.
   *              0: If ICU_LINEAR_BUFFER is selected for time stamp measurement mode.
   *********************************************************************************************************************
   *******************                       Signal Measurement channels                             *******************
   *********************************************************************************************************************
   * Bit 2    :   1: If the timer channel is configured for Duty cycle measurement.
   *              0: If the timer channel is not configured for Duty cycle measurement.
   *
   * Bits 1-0 :  10: ICU_PERIOD_TIME /ICU_DUTY_CYCLE
   *             01: ICU_HIGH_TIME
   *             00: ICU_LOW_TIME
   *********************************************************************************************************************
   *******************                         Edge Counter Measurement                              *******************
   *********************************************************************************************************************
   * Bits 3-0 :    0000
   *********************************************************************************************************************
   * For all the Above Measurements Bits 7-4 should be generated as 0000
   */
  uint8 ucChannelProperties;
  /* Pointer to ICU driver channel configuration */
  P2CONST(void, TYPEDEF, ICU_CONFIG_DATA) pHWChannelUserRegConfig;

} Icu_ChannelUserRegConfigType;

/***********************************************************************************************************************
**                                         Structure to channel data into RAM                                         **
***********************************************************************************************************************/
typedef struct STag_Icu_ChannelRamDataType                                                                              /* PRQA S 3630 # JV-01 */
{
  uint8 ucChannelStatus;
  uint8 ucNotificationEnable;
  boolean blResultComplete;
  #if ((ICU_DISABLE_WAKEUP_API == STD_ON) || (ICU_ENABLE_WAKEUP_API == STD_ON) || \
  (ICU_WAKEUP_FUNCTIONALITY_API == STD_ON) || (ICU_NOTIFY_WAKEUP_INTERRUPT == STD_ON))
  uint8 ucWakeupEnable;
  boolean blWakeupOccurrence;
  #endif
  #if (STD_ON == ICU_SET_MODE_API)
  uint8 ucChannelRunning;
  #endif
  #if (ICU_ATU_TIMER_UNIT_USED == STD_ON)
  uint32 ulStartEdgeCaptureValue;
  uint32 ulEndEdgeCaptureValue;
  #endif
} Icu_ChannelRamDataType;

/***********************************************************************************************************************
**                                       Structure for ICU Channel information                                        **
***********************************************************************************************************************/
typedef struct STag_Icu_ChannelConfigType                                                                               /* PRQA S 3630 # JV-01 */
{
  #if (ICU_NOTIFICATION_CONFIG == STD_ON)
  /* Pointer to callback notification function */
  P2FUNC(void, ICU_APPL_CODE, pIcuNotificationPointer)(void);                                                           /* PRQA S 3432 # JV-01 */
  #endif /* End of (ICU_NOTIFICATION_CONFIG == STD_ON) */
  /* Void pointer to base address of channel user control register structure */
  P2VAR(void, TYPEDEF, REGSPACE) pCntlRegs;
  #if (ICU_GET_INPUT_LEVEL_API == STD_ON)
  /* Pointer to base address of channel PPR register */
  P2VAR(volatile uint16, TYPEDEF, REGSPACE) pPPRAddress;
  #endif
  /* Pointer to base address of channel Interrupt control register */
  P2VAR(volatile uint16, TYPEDEF, REGSPACE) pIntrCntlAddress;
  /* The wakeup ID of wakeup source to be transmitted to EcuM */
  #if (ICU_REPORT_WAKEUP_SOURCE == STD_ON)
  uint8 ucEcuMChannelWakeupInfo;
  #endif
  uint16 usChannelMaskValue;
  #if (ICU_GET_INPUT_LEVEL_API == STD_ON)
  /* PPR mask value */
  uint16 usPortMaskValue;
  /* Port type used for ICU channel*/
  /* ICU_NORMAL_PORT - 0
   * ICU_JTAG_PORT - 1
   */
  uint8 ucIcuPortType;
  #endif
  uint8 ucIcuMeasurementMode;
  /* Default Edge detection of the ICU channel */
  /* ICU_RISING_EDGE - 0
   * ICU_FALLING_EDGE - 1
   * ICU_BOTH_EDGES - 2
   */
  uint8 ucIcuDefaultStartEdge;
  /* Input capture channel type */
  /* ICU_HW_EXT_INTP - 0
   * ICU_HW_EXT_IRQ - 1
   * ICU_HW_TAUD - 2
   * ICU_HW_TAUJ - 3
   * ICU_HW_ATU_TIMERA - 4
   * ICU_HW_ATU_TIMERC - 5
   * ICU_HW_GTM_TIM - 6
   */
  uint8 ucIcuChannelType;
  /* Wakeup capability of the channel */
  uint8 ucIcuWakeupCapability;
  /* Enable or disable EcuM notification of the channel */
  uint8 ucIcuDisableEcumWakeupNotification;
  /* Pointer to ICU driver channel configuration */
  P2CONST(void, TYPEDEF, ICU_CONFIG_DATA) pHWIPChannelConfig;
  #if ((ICU_DEV_ERROR_DETECT == STD_ON) && (ICU_MULTI_CORE_SUPPORT == STD_ON))
  /* Declare the variable to store the list of configured core IDs for the channel */
  uint8 ucCoreIndex;
  #endif
} Icu_ChannelConfigType;

#define ICU_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Icu_MemMap.h"

/* Array of structures for HW-IP Configuration */
extern CONST(Icu_HWIPType, ICU_CONFIG_DATA) Icu_GaaHWIPConfig[];                                                        /* PRQA S 3684 # JV-01 */

#define ICU_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Icu_MemMap.h"
/***********************************************************************************************************************
**                                                  extern RAM data                                                   **
***********************************************************************************************************************/
#define ICU_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Icu_MemMap.h"

/* The function table for commonize */
typedef struct STag_Icu_HwFuncTableType
{
  P2FUNC(void, ICU_PRIVATE_CODE, pUnitInit)(const Icu_ConfigType *);                                                    /* PRQA S 1336, 3432 # JV-01, JV-01 */
  P2FUNC(void, ICU_PRIVATE_CODE, pChannelInit)(Icu_ChannelType);                                                        /* PRQA S 1336, 3432 # JV-01, JV-01 */
  P2FUNC(void, ICU_PRIVATE_CODE, pUnitDeInit)(void);                                                                    /* PRQA S 3432 # JV-01 */
  P2FUNC(void, ICU_PRIVATE_CODE, pChannelDeInit)(Icu_ChannelType);                                                      /* PRQA S 1336, 3432 # JV-01, JV-01 */
  P2FUNC(void, ICU_PRIVATE_CODE, pGetEdgeNumbers)(Icu_ChannelType);                                                     /* PRQA S 1336, 3432 # JV-01, JV-01 */
  P2FUNC(Icu_CounterValueType, ICU_PRIVATE_CODE, pGetTAUInCountValue)(Icu_ChannelType);                                 /* PRQA S 1336, 3432 # JV-01, JV-01 */
  P2FUNC(void, ICU_PRIVATE_CODE, pSetMode)(Icu_ChannelType, Icu_ModeType);                                              /* PRQA S 1336, 3432 # JV-01, JV-01 */
  P2FUNC(void, ICU_PRIVATE_CODE, pSetActivation)(Icu_ChannelType, Icu_ActivationType);                                  /* PRQA S 1336, 3432 # JV-01, JV-01 */
  P2FUNC(void, ICU_PRIVATE_CODE, pStartCountMeasurement)(Icu_ChannelType);                                              /* PRQA S 1336, 3432 # JV-01, JV-01 */
  P2FUNC(void, ICU_PRIVATE_CODE, pStopCountMeasurement)(Icu_ChannelType);                                               /* PRQA S 1336, 3432 # JV-01, JV-01 */
  P2FUNC(void, ICU_PRIVATE_CODE, pResetEdgeCount)(Icu_ChannelType);                                                     /* PRQA S 1336, 3432 # JV-01, JV-01 */
  P2FUNC(Icu_LevelType, ICU_PRIVATE_CODE, pGetInputLevel)(Icu_ChannelType);                                             /* PRQA S 1336, 3432 # JV-01, JV-01 */
  P2FUNC(void, ICU_PRIVATE_CODE, pGetPulseData)(Icu_ChannelType);                                                       /* PRQA S 1336, 3432 # JV-01, JV-01 */
} Icu_HwFuncTableType;
#define ICU_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Icu_MemMap.h"

/***********************************************************************************************************************
**                                                  extern RAM data                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/

#endif /* ICU_PBTYPES_HEADER  */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
