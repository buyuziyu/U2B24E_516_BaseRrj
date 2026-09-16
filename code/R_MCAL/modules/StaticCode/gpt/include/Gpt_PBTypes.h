/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Gpt_PBTypes.h                                                                                       */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains macros and structure data types for post build parameters of GPT Driver                         */
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
 *  2.4.0  30/06/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.01.00 (D) release
 *  2.3.2  25/04/2025  : As part of GTM HWIP support for U2Ax, following changes are made:
 *                       1. GPT_GTM_350_VERSION and GPT_GTM_410_VERSION
 *  2.3.1  31/03/2025  : Update SW-VERSION for RH850/U2BxE MCAL Ver22.00.02/Ver22.00.02.D Release
 *  2.3.0  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 *  2.2.0  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 *  2.1.2  31/10/2024  : As part of GTM HWIP support, following changes are made
 *                       1.Add macros GPT_HWIP_GTM, GPT_HW_TOM, GPT_HW_ATOM
 *                       As part of Post Build multiple varriant support, following changes are made
 *                       1.Remove extern of structure Gpt_GaaPredefTimerConfig
 *                       As part of QAC 9.5.0 support, following changes are made
 *                       1.Remove QAC message 1534, 1546
 *  2.0.1  17/10/2023  : Add QAC message 1534, 1536, add macro GPT_ENTER_CRITICAL_SECTION_FROM_TYPE,
 *                       GPT_EXIT_CRITICAL_SECTION_FROM_TYPE
 *                       Update preprocessor GPT_AR_R21_11_VERSION to GPT_AR_R22_11_VERSION
 *                       Update memory section from CONFIG_DATA to CONFIG_DATA_POSTBUILD
 *         21/09/2023  : Add preprocessor #if (GPT_TYPE_II_SUPPORT == STD_ON) for Gpt_GlobalAccessPointType
 *  2.0.0  25/08/2023  : Add preprocessor for pOSTMUnitRegs, remove qac message 3630
 *         26/07/2023  : Remove qac message 0841, 3630 header, update information of qac message 3432 header,
 *                       Remove GPT_INSTANCE_INDEX, Gpt_GaaChannelRamData, Gpt_GaaChannelConfig
 *                       Change Gpt_Mapping.h to Gpt_MemMap.h
 *                       In STag_Gpt_ChannelConfigType, add pOSTMUnitRegs, ucCoreIndex, ucRamDataIndex,
 *                       remove ucTimerUnitType
 *                       Add macro GPT_INVALID_CORE, GPT_CORE_MASK, STag_Gpt_GlobalAccessPointType
 *                       Change Gpt_Mapping.h to Gpt_MemMap.h, Add CWE QAC header
 *         12/06/2023  : Update pre-processor GPT_AR_VERSION == GPT_AR_R21_11_VERSION
 *         12/05/2023  : Update SW version 2.0.0
 *  1.4.4  14/10/2022  : Add pre-processor GPT_AR_VERSION == GPT_AR_2111_VERSION for support AR21-11;
 *                       Update SW-VERSION to 1.4.5
 *  1.4.1  11/11/2021  : Replace ATU5 with ATU in macro: GPT_HW_ATU5C, GPT_HW_ATU5D, GPT_HW_ATU5G.
 *  1.4.0  05/10/2021  : Following Changes were made:
 *                       1. Removed unused macro GPT_HW_ATU5A, GPT_TWO, GPT_THREE, GPT_FOUR, GPT_FIVE,
 *                          GPT_SEVEN, GPT_EIGHT, GPT_THIRTYONE, GPT_SIXTYTHREE, GPT_ONEHUNDREDSEVENTYNINE,
 *                          GPT_16BIT_MASK, GPT_24BIT_MASK, GPT_NOTIFICATION_ENABLED, GPT_NOTIFICATION_DISABLED,
 *                          GPT_WAKEUP_NOTIFICATION_ENABLED, GPT_WAKEUP_NOTIFICATION_DISABLED.
 *  1.3.2  22/08/2021  : Following Changes were made:
 *                        1. Updated header file macro to call file multiple times.
 *                        2. Using #include SCHM_WDG_HEADER instead of
 *                           #include "SchM_Gpt_Renesas.h".
 *                        3. Added QAC message 9.5.0.
 *  1.3.1  02/07/2021  : Add QAC message 9.5.0.
 *                       Format source code to 120 characters.
 *                       Improve Violation tag (remove START/END).
 *  1.2.0  17/07/2020  : Release.
 *  1.1.0  19/06/2020  : Release.
 *         27/05/2020  : Add DET/DEM Report Error Macros.
 *  1.0.0  01/01/2020  : Initial Version.
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

#ifndef GPT_PBTYPES_H
#define GPT_PBTYPES_H

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for the declaration of the critical section protection functions */
#if (GPT_CRITICAL_SECTION_PROTECTION == STD_ON)
#include "SchM_Gpt.h"
#endif
#if (GPT_TIMER_IP_OSTM == STD_ON)
#include "Gpt_OSTM_Ram.h"
#endif
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR Release version information */
#define GPT_PBTYPES_AR_RELEASE_MAJOR_VERSION    GPT_AR_RELEASE_MAJOR_VERSION_VALUE
#define GPT_PBTYPES_AR_RELEASE_MINOR_VERSION    GPT_AR_RELEASE_MINOR_VERSION_VALUE
#define GPT_PBTYPES_AR_RELEASE_REVISION_VERSION GPT_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define GPT_PBTYPES_SW_MAJOR_VERSION            GPT_SW_MAJOR_VERSION
#define GPT_PBTYPES_SW_MINOR_VERSION            GPT_SW_MINOR_VERSION
#define GPT_PBTYPES_SW_PATCH_VERSION            GPT_SW_PATCH_VERSION

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/
/* Macros for Hardware Timer type */
#define GPT_HWIP_OSTM                           (uint8)0x00
#define GPT_HWIP_TAUD                           (uint8)0x01
#define GPT_HWIP_TAUJ                           (uint8)0x02
#define GPT_HWIP_ATU                            (uint8)0x03
#define GPT_HWIP_GTM                            (uint8)0x04

/* Macros for Hardware Timer type */
#define GPT_HW_OSTM                             (uint8)0x00
#define GPT_HW_TAUD                             (uint8)0x01
#define GPT_HW_TAUJ                             (uint8)0x02
#define GPT_HW_ATUC                             (uint8)0x03
#define GPT_HW_ATUD                             (uint8)0x04
#define GPT_HW_ATUG                             (uint8)0x05
#define GPT_HW_TOM                              (uint8)0x06
#define GPT_HW_ATOM                             (uint8)0x07

/* Macros for channel modes */
#define GPT_CH_MODE_ONESHOT                     (uint8)0x00
#define GPT_CH_MODE_CONTINUOUS                  (uint8)0x01

/* Macros for HWUM version of GTM */
#define GPT_GTM_350_VERSION                     0U
#define GPT_GTM_410_VERSION                     1U

/* Macros used as flag */
#define GPT_TRUE                                (boolean)0x01
#define GPT_FALSE                               (boolean)0x00

/* Macros for GPT driver status */
#define GPT_INITIALIZED                         (boolean)0x01
#define GPT_UNINITIALIZED                       (boolean)0x00

/* Macros for index */
#define GPT_ZERO                                (uint8)0x00
#define GPT_ONE                                 (uint8)0x01
#define GPT_INVALID_CORE                        (uint8)0xFF

/* Reset values */
#define GPT_RESET_WORD                          (uint16)0x0000

/* Macros to avoid Magic numbers */
#define GPT_DBTOC_VALUE     (((uint32)GPT_VENDOR_ID_VALUE << 22) | ((uint32)GPT_MODULE_ID_VALUE << 14) | \
                                  ((uint32)GPT_SW_MAJOR_VERSION_VALUE << 8) | ((uint32)GPT_SW_MINOR_VERSION_VALUE << 3))

/* Macros to hold timer status */
#define GPT_CH_NOTSTARTED                          (uint8)0x00
#define GPT_CH_RUNNING                             (uint8)0x01
#define GPT_CH_STOPPED                             (uint8)0x02
#define GPT_CH_EXPIRED                             (uint8)0x03

/* Macro for clearing pending interrupts */
#define GPT_CLEAR_PENDING_INTR_MASK                (uint16)0xEFFFU

/* Macros for masking EIMKn bit */
#define GPT_EIMK_ENABLE_MASK                       (uint8)0x7FU
#define GPT_EIMK_DISABLE_MASK                      (uint8) ~(GPT_EIMK_ENABLE_MASK)

/* Macro for which wakeup not configured */
#define GPT_NOWAKEUP                               (uint8)0xFF

/* Macro to check interrupt request flag */
#define GPT_CHECK_INTR_REQUEST_MASK                (uint16)0x1000U

/* Macro to mask core */
#define GPT_CORE_MASK                              (uint8)0x0F

/* PredefTimer UpperBitClearMask */
#define GPT_UPPER_24BIT_CLEAR_MASK                 (uint32)0x00FFFFFFUL
#define GPT_UPPER_16BIT_CLEAR_MASK                 (uint32)0x0000FFFFUL


#if (GPT_CRITICAL_SECTION_PROTECTION == STD_ON)
/* Critical section protect for multicore */
#if (GPT_MULTI_CORE_SUPPORT == STD_ON)
#define GPT_ENTER_CRITICAL_SECTION_FROM_TYPE(type) (GPT_HWIP_OSTM == type) ? \
  GPT_ENTER_CRITICAL_SECTION(GPT_INTERRUPT_CONTROL_PROTECTION) : \
    GPT_ENTER_CRITICAL_SECTION(GPT_INTERRUPT_CONTROL_PROTECTION_GLOBAL)
#define GPT_EXIT_CRITICAL_SECTION_FROM_TYPE(type) (GPT_HWIP_OSTM == type)  ? \
  GPT_EXIT_CRITICAL_SECTION(GPT_INTERRUPT_CONTROL_PROTECTION) : \
    GPT_EXIT_CRITICAL_SECTION(GPT_INTERRUPT_CONTROL_PROTECTION_GLOBAL)
#endif
/* Critical section protect */
#define GPT_ENTER_CRITICAL_SECTION(Exclusive_Area) SchM_Enter_Gpt_##Exclusive_Area()                                    /* PRQA S 0342 # JV-01 */
#define GPT_EXIT_CRITICAL_SECTION(Exclusive_Area)  SchM_Exit_Gpt_##Exclusive_Area()                                     /* PRQA S 0342 # JV-01 */
#endif /* GPT_CRITICAL_SECTION_PROTECTION */

/***********************************************************************************************************************
**                                              DEM Report Error Macros                                               **
***********************************************************************************************************************/
#if (GPT_AR_VERSION == GPT_AR_422_VERSION)
#define GPT_DEM_REPORT_ERROR(EventId, EventStatus) (void)Dem_ReportErrorStatus(EventId, EventStatus)
#elif ((GPT_AR_VERSION == GPT_AR_431_VERSION)|| (GPT_AR_VERSION == GPT_AR_R22_11_VERSION))
#define GPT_DEM_REPORT_ERROR(EventId, EventStatus) (void)Dem_SetEventStatus(EventId, EventStatus)
#endif

/***********************************************************************************************************************
**                                              DET Report Error Macros                                               **
***********************************************************************************************************************/
#if (GPT_AR_VERSION == GPT_AR_422_VERSION)
#if (GPT_DEV_ERROR_DETECT == STD_ON)
#define GPT_DET_REPORT_ERROR(ModuleId, InstanceId, ApiId, ErrorId) \
                                                             (void)Det_ReportError(ModuleId, InstanceId, ApiId, ErrorId)
#else
#define GPT_DET_REPORT_ERROR(ModuleId, InstanceId, ApiId, ErrorId)
#endif
#elif ((GPT_AR_VERSION == GPT_AR_431_VERSION)|| (GPT_AR_VERSION == GPT_AR_R22_11_VERSION))
#define GPT_DET_REPORT_ERROR(ModuleId, InstanceId, ApiId, ErrorId) \
                                                      (void)Det_ReportRuntimeError(ModuleId, InstanceId, ApiId, ErrorId)
#endif

/***********************************************************************************************************************
**                                          Interrupt Consistency Check Mask                                          **
***********************************************************************************************************************/
/* Interrupt Consistency check mask value */
#define GPT_EIC_EIMK_MASK (uint8)0x80U

/* Macros used as DEM error flag */
#define GPT_DEM_NOT_ERROR (uint8)0x00
#define GPT_DEM_ERROR     (uint8)0x01
/***********************************************************************************************************************
**                                         Structure for channel information                                          **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                           Global configuration constants                                           **
***********************************************************************************************************************/
/* Data Structure for GPT required for Initializing the GPT timer Channel */
typedef struct STag_Gpt_ChannelConfigType                                                                               /* PRQA S 3630 # JV-01 */
{
  /* Timer Unit Index in the array of Timer Unit */
  uint8 ucTimerUnitIndex;
  /* Type of GPT Timer Channel */
  uint8 ucTimerType;
  /* Channel Mode */
  uint8 ucGptChannelMode;
  /* Pointer to Timer Interrupt control register */
  P2VAR(volatile uint16, TYPEDEF, REGSPACE) pEICReg;
  #if (GPT_DEV_ERROR_DETECT == STD_ON)
  /* The Max tick value of start timer API */
  uint32 ulMaxTickValue;
  #endif
  #if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)
  /* Notification function pointer */
  P2FUNC(void, GPT_APPL_CODE, pGptNotificationPointer)(void);                                                           /* PRQA S 3432 # JV-01 */
  #endif
  #if ((GPT_REPORT_WAKEUP_SOURCE == STD_ON) && (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON))
  /* this channel support wakeup or not */
  boolean blGptWakeupSupport;
  /* Channel Wakeup Source */
  uint8 ucWakeupSourceId;
  #endif
  /* Pointer to address of HWIP channel config */
  P2CONST(void, TYPEDEF, GPT_CONFIG_DATA) pHWIPChannelConfig;

  /* Pointer to base address of OSTM Unit registers */
  #if (GPT_TIMER_IP_OSTM == STD_ON)
  P2VAR(Gpt_OSTMnUnitRegs, AUTOMATIC, REGSPACE) pOSTMUnitRegs;                                                          /* PRQA S 3432 # JV-01 */
  #else
  P2VAR(void, AUTOMATIC, REGSPACE) pOSTMUnitRegs;
  #endif

  /* Indicate which core(s) is (are) mapped to */
  #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
  uint8 ucCoreIndex;
  #endif

  /* Indicate the order of channel in mapped core */
  uint8 ucRamDataIndex;
} Gpt_ChannelConfigType;


/* Global data for using across core */
typedef struct STag_Gpt_GlobalAccessPointType
{
  /* Driver Status for each core */
  P2VAR(volatile boolean, TYPEDEF, GPT_CONFIG_DATA) pDriverState;
  /* Pointer to GPT driver channel configuration */
  P2CONST(Gpt_ChannelConfigType *, TYPEDEF, GPT_CONFIG_CONST) pChannelConfig;
  #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
  #if (GPT_TYPE_II_SUPPORT == STD_ON)
  /* Global pointer to hold first channel RAM structure */
  P2VAR(volatile Gpt_ChannelRamDataType, TYPEDEF, GPT_CONFIG_DATA) pChannelRamData;
  #endif
  #endif
} Gpt_GlobalAccessPointType;

#define GPT_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Gpt_MemMap.h"

/* Array of structures for HW-IP Configuration */
extern CONST(Gpt_HWIPType, GPT_CONST) Gpt_GaaHWIP[];                                                                    /* PRQA S 3684 # JV-01 */

#define GPT_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Gpt_MemMap.h"

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/

#endif /* GPT_PBTYPES_HEADER */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
