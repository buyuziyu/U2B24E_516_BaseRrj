/*====================================================================================================================*/
/* Project      = RH850/X2x AR4 MCAL Development                                                                      */
/* Module       = Pwm_PBTypes.h                                                                                       */
/*                                                                                                                    */
/*====================================================================================================================*/
/*                                  COPYRIGHT                                                                         */
/*====================================================================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains the type definitions of Post Build time Parameters                                              */
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
/*                                                                                                                    **
 * 2.5.1: 30/06/2025 : Remove SW-VERSION in header comment                                                            **
 * 2.5.0: 30/06/2025 : Update SW-VERSION for U2Ax Ver22.01.00(D) Final Release                                        **
 * 2.4.0: 31/05/2025 : Update SW-VERSION for U2Cx Ver21.01.01 Final Release                                           **
 * 2.3.2: 29/04/2025 : Update SW-VERSION for U2Ax Ver22.00.04 Beta Release                                            **
 * 2.3.1: 31/03/2025 : Update SW-VERSION for Update SW-VERSION for U2BxE Ver22.00.02 Beta Release                     **
 * 2.3.0: 28/02/2025 : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release                        **
 * 2.2.0: 31/12/2024 : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release                                  **
 * 2.1.2: 31/10/2024 : Update SW-VERSION for Ver22.01.02 U2Bx, Ver22.00.05 U2Cx Beta2 Release                         **
 * 2.1.1: 30/08/2024 : Update SW-VERSION for Ver22.01.01 U2Bx Beta Release                                            **
 *                     As part of GTM support, following changes are made                                             **
 *                     1. Add macro PWM_HWIP_GTM and update value of macro PWM_TOTAL_HWFUNC from 4 to 5               **
 *                     As part of U2C support, following changes are made                                             **
 *                     1. Remove QAC message 1534, 1536                                                               **
 *                     2. Remove redundant QAC message                                                                **
 * 2.0.1: 21/10/2023 : Follow rule QAC 10.3.0, add new QAC message 1534, 1536, 1336 and re-define type of             **
 *                     PWM_INITIALIZED, PWM_UNINITIALIZED, PWM_SYNC_STARTED and PWM_SYNC_STOPPED                      **
 *        14/10/2023 : Change PWM_START/STOP_SEC_CONFIG_DATA_UNSPECIFIED to                                           **
 *                     PWM_START/STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED                                           **
 *                     Change condition compare PWM_AR_R21_11_VERSION to PWM_AR_R22_11_VERSION                        **
 * 2.0.0: 05/07/2023 : Update from "Pwm_Mapping.h to "Pwm_MemMap.h". Remove #ifdef PWM_INSTANCE_INDEX                 **
 *                     Add variable ucCoreIndex                                                                       **
 *                     Add pre-compile condition check for PWM_ENTER/EXIT_CRITICAL_SECTION                            **
 *                     Update QAC message                                                                             **
 *        06/06/2023 : Change macro PWM_AR_2111_VERSION to PWM_AR_R21_11_VERSION                                      **
 *        20/04/2023 : Modify value of PWM_POLARITY_LOW to (uint8)0x01U and PWM_POLARITY_HIGH to (uint8)0x00U         **
 * 1.4.5: 02/12/2022 : Add condition for DEM Report Error Macro to support AR21-11                                    **
 * 1.4.4: 08/06/2022 : Changed value of macro PWM_DISABLE_INTR_MASK from (uint16)(0x0001U << 7) to (uint8)(0x01U << 7)**
 * 1.4.3: 18/04/2022 : Changed MAX_DUTY_CYCLE to PWM_MAX_DUTY_CYCLE_VALUE and                                         **
 *                             MIN_DUTY_CYCLE to PWM_MIN_DUTY_CYCLE_VALUE                                             **
 *                     Removed un-used define PWM_DUTY_MAX_LIMIT                                                      **
 * 1.4.2: 26/02/2022 : Updated SW VERSION to 1.4.2                                                                    **
 * 1.3.2: 23/08/2021 : Added PWM-Diag HW module.                                                                      **
 *        04/08/2021 : Device specific implementation move to device specific file.                                   **
 *                     Removed redundant macros.                                                                      **
 *                     Format source code unified within module.                                                      **
 * 1.3.1: 02/07/2021 : Add QAC message 9.5.0                                                                          **
 *                     Format source code to 120 characters                                                           **
 *                     Improve Violation tag (remove START/END)                                                       **
 *        19/05/2021 : Added new ucTimerUnitType to Pwm_ChannelConfigType                                             **
 *        15/05/2021 : Fixed Coding Rule and tailor space                                                             **
 *        12/05/2021 : Changed PWM_HW_ATU to PWM_ATU_UNIT_INDEX, PWM_HW_TAUD                                          **
 *                     to PWM_TAUD_UNIT_INDEX, and PWM_HW_TAUD to                                                     **
 *                     PWM_TAUJ_UNIT_INDEX                                                                            **
 * 1.2.0: 28/07/2020 : Release                                                                                        **
 * 1.1.0: 19/06/2020 : Release                                                                                        **
 * 1.0.3: 20/05/2020 : Changed "(uint16)0x7FU" to "(uint8)0x7FU"                                                      **
 * 1.0.2: 19/05/2020 : Changed "uinteger uiPolarity;" to "uint8 ucPolarity;"                                          **
 *                     Changed "uiIdleLevel" to "ucIdleLevel"                                                         **
 *                     Changed "uiTimerMode" to "ucTimerMode"                                                         **
 * 1.0.1: 18/05/2020 : Added PWM_TOTAL_HWFUNC macro                                                                   **
 * 1.0.0: 24/03/2020 : Initial Version.                                                                               **
 *                                                                                                                    */
/**********************************************************************************************************************/

#ifndef PWM_PBTYPES_H
#define PWM_PBTYPES_H

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for data type unsigned integer declaration */
#include "rh850_Types.h"

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define PWM_PBTYPES_AR_RELEASE_MAJOR_VERSION    PWM_AR_RELEASE_MAJOR_VERSION
#define PWM_PBTYPES_AR_RELEASE_MINOR_VERSION    PWM_AR_RELEASE_MINOR_VERSION
#define PWM_PBTYPES_AR_RELEASE_REVISION_VERSION PWM_AR_RELEASE_REVISION_VERSION
/* Software module version information */
#define PWM_PBTYPES_SW_MAJOR_VERSION            PWM_SW_MAJOR_VERSION
#define PWM_PBTYPES_SW_MINOR_VERSION            PWM_SW_MINOR_VERSION

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
/* Message (2:3472)    : All toplevel uses of this function-like macro look like they could be replaced by            */
/*                       equivalent function calls.                                                                   */
/* Rule                : MISRA C:2012 Dir-4.9                                                                         */
/* JV-01 Justification : This message indicates that a candidate macro may be suitable for replacement by a           */
/*                       function, based on an actual call-site and the arguments passed to it there                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:1336)    : Parameter identifiers missing in declaration of a function type.                             */
/* Rule                : MISRA C:2012 Rule-8.2, CWE-398, CWE-569                                                      */
/* JV-01 Justification : Parameter identifiers are  missing however not impact the MCAL operation.                    */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3684)    : Array declared with unknown size.                                                            */
/* Rule                : MISRA C:2012 Rule-8.11, CERTCCM ARR02                                                        */
/* JV-01 Justification : Arrays used are verified in the file which are only declarations and size is configuration   */
/*                       dependent.                                                                                   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/
#define PWM_TRUE                                (boolean)1
#define PWM_FALSE                               (boolean)0
#define PWM_ZERO                                (uint8)0x00U
#define PWM_ONE                                 (uint8)0x01U
#define PWM_TWO                                 (uint8)0x02U
#define PWM_THREE                               (uint8)0x03U
#define PWM_POLARITY_LOW                        (uint8)0x01U
#define PWM_POLARITY_HIGH                       (uint8)0x00U
#define PWM_INITIALIZED                         (boolean)1
#define PWM_UNINITIALIZED                       (boolean)0
#define PWM_SYNC_STARTED                        (boolean)1
#define PWM_SYNC_STOPPED                        (boolean)0
/* Macros to avoid Magic numbers */
#define PWM_DBTOC_VALUE\
  (((uint32)PWM_VENDOR_ID_VALUE << (uint8)22) | \
   ((uint32)PWM_MODULE_ID_VALUE << (uint8)14) | \
   ((uint32)PWM_SW_MAJOR_VERSION << (uint8)8) | \
   ((uint32)PWM_SW_MINOR_VERSION << (uint8)3))
/* Total HW Timer */
#define PWM_TOTAL_HWFUNC                        (uint8)0x05U
/* Macros for Hardware Timer type */
#define PWM_ATU_UNIT_INDEX                      (uint8)0x00U
#define PWM_TAUD_UNIT_INDEX                     (uint8)0x01U
#define PWM_TAUJ_UNIT_INDEX                     (uint8)0x02U
#define PWM_DIAG_UNIT_INDEX                     (uint8)0x03U
#define PWM_HWIP_ATU                            (uint8)0x00U
#define PWM_HWIP_TAUD                           (uint8)0x01U
#define PWM_HWIP_TAUJ                           (uint8)0x02U
#define PWM_HWIP_DIAG                           (uint8)0x03U
#define PWM_HWIP_GTM                            (uint8)0x04U
/* Macros for Timer Mode type */
#define PWM_MASTER_CHANNEL                      (uint8)0x00U
#define PWM_SLAVE_CHANNEL                       (uint8)0x01U
/* Macro for setting the PWM mode in Control registers */
#define PWM_DUTY_CALC_DIV                       (uint8)0x0FU
#define PWM_MIN_DUTY_CYCLE_VALUE                (uint16)0x0000U
#define PWM_MAX_DUTY_CYCLE_VALUE                (uint16)0x8000U
#define PWM_CALC_DUTY_MAX_LIMIT                 (uint32)0x00FFFFFFUL
#define PWM_PERIOD_MAX_LIMIT                    (uint32)0x00FFFFFFUL
#define PWM_CORRECTION_MASK                     (uint32)0x00007FFF
/* set values */
#define PWM_PERIOD_LIMIT                        (uint16)0xFFFFU
/* Macro for clearing pending interrupts */
#define PWM_CLEAR_PENDING_INTR_MASK             (uint16)~(0x0001U << 12)
/* Macro for interrupt consistency checking */
#define PWM_EIC_EIMK_MASK                       (uint16)(0x0001U << 7)
/* Macro for enable interrupts */
#define PWM_ENABLE_INTR_MASK                    (uint8)~(0x01U << 7)
/* Macro for disable interrupts */
#define PWM_DISABLE_INTR_MASK                   (uint8)(0x01U << 7)

/***********************************************************************************************************************
**                                              DEM Report Error Macros                                               **
***********************************************************************************************************************/
#if (PWM_AR_VERSION == PWM_AR_422_VERSION)
#define PWM_DEM_REPORT_ERROR(EventId, EventStatus) Dem_ReportErrorStatus(EventId, EventStatus)
#elif ((PWM_AR_VERSION == PWM_AR_431_VERSION)||(PWM_AR_VERSION == PWM_AR_R22_11_VERSION))
#define PWM_DEM_REPORT_ERROR(EventId, EventStatus) (void)Dem_SetEventStatus(EventId, EventStatus)
#endif

/***********************************************************************************************************************
**                                      SchM Critical Section Protection Macros                                       **
***********************************************************************************************************************/
#if (PWM_CRITICAL_SECTION_PROTECTION == STD_ON)
#define PWM_ENTER_CRITICAL_SECTION(Exclusive_Area) SchM_Enter_Pwm_##Exclusive_Area()                                    /* PRQA S 0342 # JV-01 */
#define PWM_EXIT_CRITICAL_SECTION(Exclusive_Area) SchM_Exit_Pwm_##Exclusive_Area()                                      /* PRQA S 0342 # JV-01 */
#else
#define PWM_ENTER_CRITICAL_SECTION(Exclusive_Area)
#define PWM_EXIT_CRITICAL_SECTION(Exclusive_Area)
#endif /* (PWM_CRITICAL_SECTION_PROTECTION == STD_ON) */

/***********************************************************************************************************************
**                                Data structure for PWM channel configuration (TAUx)                                 **
***********************************************************************************************************************/
typedef struct STag_Pwm_ChannelConfigType
{
  /* Pointer to the PWM Channel properties */
  P2CONST(void, TYPEDEF, PWM_CONFIG_CONST) pChannelProp;
  #if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
  /* Pointer to callback notification */
  P2FUNC(void, PWM_APPL_CODE, pPwmEdgeNotifPtr)(void);                                                                  /* PRQA S 3432 # JV-01 */
  #endif
  /* Polarity of the channel (HIGH/LOW) */
  uint8 ucPolarity;
  /* Class type of the PWM channel (Fixed Period /Fixed Period Shifted /Variable period)  */
  Pwm_ChannelClassType enClassType;
  /* Idle state of the channel (HIGH/LOW) */
  uint8 ucIdleLevel;
  #if (PWM_SYNC_START_SUPPORT == STD_ON)
  /* blSyncStartReq = true means channel will be initialized by API Pwm_SynchronousInit */
  /* blSyncStartReq = false means channel will be initialized by API Pwm_Init */
  boolean blSyncStartReq;
  #endif
  /* Pointer to address of HWIP channel config */
  P2CONST(void, TYPEDEF, PWM_CONFIG_DATA) pHWIPChannelConfig;
  /* Timer Unit Configured*/
  uint8 ucTimerUnitType;
  #if ((PWM_MULTI_CORE_SUPPORT == STD_ON) && (PWM_DEV_ERROR_DETECT == STD_ON))
  /* Declare the variable to store list of configured core ID for the channel */
  uint8 ucCoreIndex;
  #endif
} Pwm_ChannelConfigType;

/***********************************************************************************************************************
**                                           Structure for HW function type                                           **
***********************************************************************************************************************/
typedef struct STag_Pwm_HwFuncTable
{
  P2FUNC(void, PWM_PRIVATE_CODE, pHWInitUnit)(P2CONST (Pwm_ConfigType, AUTOMATIC, PWM_CONFIG_DATA));                    /* PRQA S 3432, 1336 # JV-01, JV-01 */
  P2FUNC(void, PWM_PRIVATE_CODE, pHWInitChannel)(void);                                                                 /* PRQA S 3432 # JV-01 */
  #if (PWM_DE_INIT_API == STD_ON)
  P2FUNC(void, PWM_PRIVATE_CODE, pHWDeInitUnit)(void);                                                                  /* PRQA S 3432 # JV-01 */
  P2FUNC(void, PWM_PRIVATE_CODE, pHWDeInitChannel)(void);                                                               /* PRQA S 3432 # JV-01 */
  #endif
  #if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
  P2FUNC(void, PWM_PRIVATE_CODE, pHWDisableNotification)(Pwm_ChannelType);                                              /* PRQA S 3432, 1336 # JV-01, JV-01 */
  P2FUNC(void, PWM_PRIVATE_CODE, pHWEnableNotification)(Pwm_ChannelType, Pwm_EdgeNotificationType);                     /* PRQA S 3432, 1336 # JV-01, JV-01 */
  #endif
  #if (PWM_GET_OUTPUT_STATE_API == STD_ON)
  P2FUNC(Pwm_OutputStateType, PWM_PRIVATE_CODE, pHWGetOutputState)(Pwm_ChannelType);                                    /* PRQA S 3432, 1336 # JV-01, JV-01 */
  #endif
  #if (PWM_SELECT_CHANNEL_CLK_API == STD_ON)
  P2FUNC(void, PWM_PRIVATE_CODE, pHWSelectChannelClk)(Pwm_ChannelType, Pwm_ClockSourceType);                            /* PRQA S 3432, 1336 # JV-01, JV-01 */
  #endif
  #if (PWM_SET_CHANNEL_OUTPUT_API == STD_ON)
  P2FUNC(void, PWM_PRIVATE_CODE, pHWSetChannelOutput)(Pwm_ChannelType, Pwm_OutputStateType);                            /* PRQA S 3432, 1336 # JV-01, JV-01 */
  #endif
  #if (PWM_SET_DUTY_CYCLE_API == STD_ON)
  P2FUNC(void, PWM_PRIVATE_CODE, pHWSetDutyCycle)(Pwm_ChannelType, uint16);                                             /* PRQA S 3432, 1336 # JV-01, JV-01 */
  #endif
  #if (PWM_SET_PERIOD_AND_DUTY_API == STD_ON)
  P2FUNC(void, PWM_PRIVATE_CODE, pHWSetPeriodAndDuty)(Pwm_ChannelType, Pwm_PeriodType, uint16);                         /* PRQA S 3432, 1336 # JV-01, JV-01 */
  #endif
  #if (PWM_SET_OUTPUT_TO_IDLE_API == STD_ON)

  P2FUNC(void, PWM_PRIVATE_CODE, pHWSetOutputToIdle)(Pwm_ChannelType);                                                  /* PRQA S 3432, 1336 # JV-01, JV-01 */
  #endif
  #if (PWM_SYNC_START_SUPPORT == STD_ON)
  P2FUNC(void, PWM_PRIVATE_CODE, pHWSynchronousInit)(void);                                                             /* PRQA S 3432 # JV-01 */
  P2FUNC(void, PWM_PRIVATE_CODE, pHWSynchronousStart)(void);                                                            /* PRQA S 3432 # JV-01 */
  P2FUNC(void, PWM_PRIVATE_CODE, pHWSynchronousStop)(void);                                                             /* PRQA S 3432 # JV-01 */
  #endif
  P2FUNC(void, PWM_PRIVATE_CODE, pHWStartOutput)(void);                                                                 /* PRQA S 3432 # JV-01 */
  #if (PWM_SET_TRIGGER_DELAY_API == STD_ON)
  P2FUNC(void, PWM_PRIVATE_CODE, pHWSetTriggerDelay)(Pwm_ChannelType, uint16);                                          /* PRQA S 3432, 1336 # JV-01, JV-01 */
  #endif
  #if (PWM_READ_CONV_RESLUT_API == STD_ON)
  P2FUNC(uint32, PWM_PRIVATE_CODE, pHWReadAdConvResult)(Pwm_ChannelType);                                               /* PRQA S 3432, 1336 # JV-01, JV-01 */
  #endif
  #if (PWM_ENABLE_DISABLE_AD_TRG_API == STD_ON)
  P2FUNC(void, PWM_PRIVATE_CODE, pHWDisableAdTrigger)(Pwm_ChannelType);                                                 /* PRQA S 3432, 1336 # JV-01, JV-01 */
  P2FUNC(void, PWM_PRIVATE_CODE, pHWEnableAdTrigger)(Pwm_ChannelType);                                                  /* PRQA S 3432, 1336 # JV-01, JV-01 */
  #endif
} Pwm_HwFuncTableType;

/***********************************************************************************************************************
**                                           Global configuration constants                                           **
***********************************************************************************************************************/

#define PWM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Pwm_MemMap.h"

/* Array of structures for Channel Configuration */
extern CONST(Pwm_ChannelConfigType, PWM_CONST) Pwm_GaaChannelConfig[];                                                  /* PRQA S 3684 # JV-01 */

#define PWM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Pwm_MemMap.h"

#endif /* PWM_PBTYPES_H */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
