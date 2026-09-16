/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Icu_GTM_Ram.c                                                                                       */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2024-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains Global variable definitions of ICU Driver                                                       */
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
 * 2.3.1:  31/03/2025  : As part of support QAC 11.6.0, following changes are made:
                         1. Remove 1531
 * 2.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release 
 * 2.1.2:  31/10/2024  : Initial Version
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/

/* Included for RAM variable declarations */
#include "Icu_LLDriver.h"
/* Included for internal functions */
#include "Icu_GTM_LLDriver.h"

#if (ICU_GTM_TIMER_UNIT_USED == STD_ON)
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define ICU_GTM_RAM_C_AR_RELEASE_MAJOR_VERSION    ICU_AR_RELEASE_MAJOR_VERSION_VALUE
#define ICU_GTM_RAM_C_AR_RELEASE_MINOR_VERSION    ICU_AR_RELEASE_MINOR_VERSION_VALUE
#define ICU_GTM_RAM_C_AR_RELEASE_REVISION_VERSION ICU_AR_RELEASE_REVISION_VERSION_VALUE
/* File version information */
#define ICU_GTM_RAM_C_SW_MAJOR_VERSION            ICU_SW_MAJOR_VERSION_VALUE
#define ICU_GTM_RAM_C_SW_MINOR_VERSION            ICU_SW_MINOR_VERSION_VALUE
/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (4:5087)    : Use of #include directive after code fragment.                                               */
/* Rule                : MISRA C:2012 Rule-20.1                                                                       */
/* JV-01 Justification : This is done as per Memory Requirement, (MEMMAP003 - Specification of Memory Mapping).       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (ICU_GTM_RAM_AR_RELEASE_MAJOR_VERSION != ICU_GTM_RAM_C_AR_RELEASE_MAJOR_VERSION)
#error "Icu_GTM_Ram.c : Mismatch in Release Major Version"
#endif /* End of #if (ICU_RAM_AR_RELEASE_MAJOR_VERSION != \
                                          ICU_RAM_C_AR_RELEASE_MAJOR_VERSION) */

#if (ICU_GTM_RAM_AR_RELEASE_MINOR_VERSION != ICU_GTM_RAM_C_AR_RELEASE_MINOR_VERSION)
#error "Icu_GTM_Ram.c : Mismatch in Release Minor Version"
#endif /* End of #if (ICU_RAM_AR_RELEASE_MINOR_VERSION != \
                                          ICU_RAM_C_AR_RELEASE_MINOR_VERSION) */

#if (ICU_GTM_RAM_AR_RELEASE_REVISION_VERSION != ICU_GTM_RAM_C_AR_RELEASE_REVISION_VERSION)
#error "Icu_GTM_Ram.c : Mismatch in Release Revision Version"
#endif /* End of #if (ICU_RAM_AR_RELEASE_REVISION_VERSION != \
                                       ICU_RAM_C_AR_RELEASE_REVISION_VERSION) */

#if (ICU_GTM_RAM_SW_MAJOR_VERSION != ICU_GTM_RAM_C_SW_MAJOR_VERSION)
#error "Icu_GTM_Ram.c : Mismatch in Software Major Version"
#endif /* End of #if (ICU_RAM_SW_MAJOR_VERSION != ICU_RAM_C_SW_MAJOR_VERSION) */

#if (ICU_GTM_RAM_SW_MINOR_VERSION != ICU_GTM_RAM_C_SW_MINOR_VERSION)
#error "Icu_GTM_Ram.c : Mismatch in Software Minor Version"
#endif /* End of #if (ICU_RAM_SW_MINOR_VERSION != ICU_RAM_C_SW_MINOR_VERSION) */

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/
#define ICU_START_SEC_VAR_NO_INIT_PTR
#include "Icu_MemMap.h"

#if (ICU_GTM_TBU_UNIT_USED == STD_ON)
/* Global pointer to the address of CMU Unit Config data */
P2CONST(Icu_GtmTbuUnitConfigType, ICU_VAR, ICU_CONFIG_CONST) Icu_GpGtmTbuConfig;
#endif

#define ICU_STOP_SEC_VAR_NO_INIT_PTR
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define ICU_START_SEC_CONST_PTR
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Extern global call back function pointer */
CONST(Icu_HwFuncTableType, ICU_CONST) Icu_GtmFunc =
{
  #if (ICU_GTM_TBU_UNIT_USED == STD_ON)
  &Icu_HW_Gtm_UnitInit,
  #else
  NULL_PTR,
  #endif
  &Icu_HW_Gtm_ChannelInit,
  #if (ICU_DE_INIT_API == STD_ON)
  #if (ICU_GTM_TBU_UNIT_USED == STD_ON)
  &Icu_HW_Gtm_UnitDeInit,
  #else
  NULL_PTR,
  #endif
  &Icu_HW_Gtm_ChannelDeInit,
  #else
  NULL_PTR,
  NULL_PTR,
  #endif
  #if (ICU_EDGE_COUNT_API == STD_ON)
  &Icu_HW_Gtm_GetEdgeNumbers,
  #else
  NULL_PTR,
  #endif
  NULL_PTR,
  #if (ICU_SET_MODE_API == STD_ON)
  &Icu_HW_SetMode,
  #else
  NULL_PTR,
  #endif
  &Icu_HW_Gtm_SetActivation,
  &Icu_HW_Gtm_StartCountMeasurement,
  &Icu_HW_Gtm_StopCountMeasurement,
  #if (ICU_EDGE_COUNT_API == STD_ON)
  &Icu_HW_Gtm_ResetEdgeCount,
  #else
  NULL_PTR,
  #endif
  #if (ICU_GET_INPUT_LEVEL_API == STD_ON)
  &Icu_HW_GetInputLevel,
  #else
  NULL_PTR,
  #endif
  #if (ICU_SIGNAL_MEASUREMENT_API == STD_ON) || (ICU_EDGE_DETECT_API == STD_ON)
  &Icu_HW_Gtm_GetPulseData
  #else
  NULL_PTR
  #endif
};

#define ICU_STOP_SEC_CONST_PTR
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
