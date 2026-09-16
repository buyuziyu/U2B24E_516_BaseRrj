/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2X MCAL Components                                                                 */
/* Module       = Ocu_PBTypes.h                                                                                       */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2023-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains macros and structure data types for post build parameters of OCU Driver                         */
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
 *  1.4.0  30/05/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.01
 *  1.3.1  31/03/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 and RH850/U2Bx-E MCAL Ver22.00.02 Release
 *  1.3.0  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 *  1.2.0  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 *  1.1.1  30/08/2024  : As part of Multi Variant support, following changes are made:
                         1. Add definition of OCU_UPCOUNTING, OCU_DOWNCOUNTING
                         2. Remove definition of struct name Ocu_GaaChannelConfig, Ocu_GaaChannelRamData
 *  1.0.1  23/10/2023  : Change from OCU_AR_RELEASE_MAJOR_VERSION_VALUE to OCU_AR_RELEASE_MAJOR_VERSION
                         Change from OCU_AR_RELEASE_MINOR_VERSION_VALUE to OCU_AR_RELEASE_MINOR_VERSION
                         Change from OCU_AR_RELEASE_REVISION_VERSION_VALUE to OCU_AR_RELEASE_REVISION_VERSION
           17/10/2023  : Add new QAC message 1534 and 1536
           25/09/2023  : Update sec OCU_START_SEC_CONFIG_DATA_UNSPECIFIED to 
                         OCU_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
                         Reason: Support AR22-11 from AR22-11 for OCU
                         Remove pEICMasterReg struct item
                         New: no need to check the master channel overflow status since 2 channel now runing
                         independently
 *  1.0.0  29/03/2023  : Initial Version
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

#ifndef OCU_PBTYPES_H
#define OCU_PBTYPES_H

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for the declaration of the critical section protection functions */
#if (OCU_CRITICAL_SECTION_PROTECTION == STD_ON)
#include "SchM_Ocu.h"
#endif
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR Release version information */
#define OCU_PBTYPES_AR_RELEASE_MAJOR_VERSION    OCU_AR_RELEASE_MAJOR_VERSION
#define OCU_PBTYPES_AR_RELEASE_MINOR_VERSION    OCU_AR_RELEASE_MINOR_VERSION
#define OCU_PBTYPES_AR_RELEASE_REVISION_VERSION OCU_AR_RELEASE_REVISION_VERSION

/* File version information */
#define OCU_PBTYPES_SW_MAJOR_VERSION            OCU_SW_MAJOR_VERSION
#define OCU_PBTYPES_SW_MINOR_VERSION            OCU_SW_MINOR_VERSION
#define OCU_PBTYPES_SW_PATCH_VERSION            OCU_SW_PATCH_VERSION

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/

/* Macros for Hardware Timer type */
#define OCU_HWIP_TAUD                           (uint8)0x00U
#define OCU_HWIP_TAUJ                           (uint8)0x01U
#define OCU_HWIP_GTM                            (uint8)0x02U

/* Macros for Hardware Timer type */
#define OCU_HW_TAUD                             (uint8)0x01U
#define OCU_HW_TAUJ                             (uint8)0x02U
/* Macros used as flag */
#define OCU_TRUE                                (boolean)0x01U
#define OCU_FALSE                               (boolean)0x00U

/* Macros for OCU driver status */
#define OCU_UNINITIALIZED                       (boolean)0x00U
#define OCU_INITIALIZED                         (boolean)0x01U

/* Macros for index */
#define OCU_ZERO                                (uint8)0x00U
#define OCU_ONE                                 (uint8)0x01U
#define OCU_TWO                                 (uint8)0x02U

/* Reset values */
#define OCU_SET_16BIT                           (uint16)0xFFFFU

/* Reset values */
#define OCU_SET_32BIT                           (uint32)0xFFFFFFFFUL

/* Macros to avoid Magic numbers */
#define OCU_DBTOC_VALUE     (((uint32)OCU_VENDOR_ID_VALUE << 22) | ((uint32)OCU_MODULE_ID_VALUE << 14) | \
                                ((uint32)OCU_SW_MAJOR_VERSION_VALUE << 8) | ((uint32)OCU_SW_MINOR_VERSION_VALUE << 3))

/* Macros to hold timer status */
#define OCU_CH_STOPPED                             (boolean)0x00U
#define OCU_CH_RUNNING                             (boolean)0x01U

#define OCU_UPCOUNTING                             (boolean)0x00U
#define OCU_DOWNCOUNTING                           (boolean)0x01U

/* Macro for clearing pending interrupts */
#define OCU_CLEAR_PENDING_INTR_MASK                (uint16)0xEFFFU

/* Macros for masking EIMKn bit */
#define OCU_EIMK_ENABLE_MASK                       (uint8)0x7FU
#define OCU_EIMK_DISABLE_MASK                      (uint8) ~(OCU_EIMK_ENABLE_MASK)

/* Critical section protect */
#if (OCU_CRITICAL_SECTION_PROTECTION == STD_ON)
#define OCU_ENTER_CRITICAL_SECTION(Exclusive_Area) SchM_Enter_Ocu_##Exclusive_Area()                                    /* PRQA S 0342 # JV-01 */
#define OCU_EXIT_CRITICAL_SECTION(Exclusive_Area)  SchM_Exit_Ocu_##Exclusive_Area()                                     /* PRQA S 0342 # JV-01 */
#else
#define OCU_ENTER_CRITICAL_SECTION(Exclusive_Area)
#define OCU_EXIT_CRITICAL_SECTION(Exclusive_Area)
#endif /* OCU_CRITICAL_SECTION_PROTECTION */

/***********************************************************************************************************************
**                                          Interrupt Consistency Check Mask                                          **
***********************************************************************************************************************/
/* Interrupt Consistency check mask value */
#define OCU_EIC_EIMK_MASK (uint8)0x80U

/***********************************************************************************************************************
**                                         Structure for channel information                                          **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                           Global configuration constants                                           **
***********************************************************************************************************************/
/* Data Structure for OCU required for Initializing the OCU timer Channel */
typedef struct STag_Ocu_ChannelConfigType                                                                               /* PRQA S 3630 # JV-01 */
{
  /* Timer Unit Index in the array of Timer Unit */
  uint8 ucTimerUnitIndex;
  /* Type of OCU Timer Unit */
  uint8 ucTimerUnitType;
  /* Pointer to EIC (Interrupt control register) of slave channel */
  P2VAR(volatile uint16, TYPEDEF, REGSPACE) pEICReg;
  /* Type of default channel tick duration for the current channel */
  uint16 usChannelTickDuration;
  /* Type of default threshold for the current channel */
  uint32 ulDefaultThreshold;
  /* Type of max tick value of free running counter */
  uint32 ulMaxCounterValue;
  /* Type of output pin used */
  boolean blOutputPinUsed;
  /* Type of output pin default state */
  Ocu_PinStateType enOutputPinDefaultState;
  #if (OCU_NOTIFICATION_SUPPORTED == STD_ON)
  /* Notification function pointer */
  P2FUNC(void, OCU_APPL_CODE, pOcuNotificationPointer)(void);                                                           /* PRQA S 3432 # JV-01 */
  #endif
  /* Pointer to address of HWIP channel config */
  P2CONST(void, TYPEDEF, OCU_CONFIG_DATA) pHWIPChannelConfig;
  #if ((OCU_DEV_ERROR_DETECT == STD_ON) && (OCU_MULTI_CORE_SUPPORT == STD_ON))
  /* Declare the variable to store the list of configured core IDs for the channel */
  uint8 ucCoreIndex;
  #endif
} Ocu_ChannelConfigType;

#define OCU_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Ocu_MemMap.h"
/* Array of structures for HW-IP Configuration */
extern CONST(Ocu_HWIPType, OCU_CONST) Ocu_GaaHWIP[];                                                                    /* PRQA S 3684 # JV-01 */
#define OCU_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Ocu_MemMap.h"

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/

#endif /* OCU_PBTYPES_H */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
