/*====================================================================================================================*/
/* Project      = RH850/X2x AR4 MCAL Development                                                                      */
/* Module       = Ocu_GTM_Ram.c                                                                                       */
/*                                                                                                                    */
/*====================================================================================================================*/
/*                                                       COPYRIGHT                                                    */
/*====================================================================================================================*/
/* (c) 2025 Renesas Electronics Corporation. All rights reserved.                                                     */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* API function implementations of OCU Driver                                                                         */
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
/*                                              Devices:        X2x                                                   */
/*====================================================================================================================*/
/***********************************************************************************************************************
**                                              Revision Control History                                              **
***********************************************************************************************************************/
/*
 * 1.4.0: 30/05/2025 : Initial Version.
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for RAM variable declarations */
#include "Ocu_GTM_Ram.h"
/* Included for function table of low-level functions */
#include "Ocu_GTM_LLDriver.h"
/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (4:5087)    : Use of #include directive after code fragment.                                               */
/* Rule                : MISRA C:2012 Rule-20.1                                                                       */
/* JV-01 Justification : This is done as per Memory Requirement, (MEMMAP003 - Specification of Memory Mapping).       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
#if (OCU_TIMER_IP_GTM == STD_ON)
/* AUTOSAR release version information */
#define OCU_GTM_RAM_C_AR_RELEASE_MAJOR_VERSION    OCU_AR_RELEASE_MAJOR_VERSION_VALUE
#define OCU_GTM_RAM_C_AR_RELEASE_MINOR_VERSION    OCU_AR_RELEASE_MINOR_VERSION_VALUE
#define OCU_GTM_RAM_C_AR_RELEASE_REVISION_VERSION OCU_AR_RELEASE_REVISION_VERSION_VALUE

/* Module software version information */
#define OCU_GTM_RAM_C_SW_MAJOR_VERSION            OCU_SW_MAJOR_VERSION_VALUE
#define OCU_GTM_RAM_C_SW_MINOR_VERSION            OCU_SW_MINOR_VERSION_VALUE
#define OCU_GTM_RAM_C_SW_PATCH_VERSION            OCU_SW_PATCH_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/

#if (OCU_GTM_RAM_AR_RELEASE_MAJOR_VERSION != OCU_GTM_RAM_C_AR_RELEASE_MAJOR_VERSION)
  #error "Ocu_GTM_Ram.c : Mismatch in Release Major Version"
#endif
#if (OCU_GTM_RAM_AR_RELEASE_MINOR_VERSION != OCU_GTM_RAM_C_AR_RELEASE_MINOR_VERSION)
  #error "Ocu_GTM_Ram.c : Mismatch in Release Minor Version"
#endif
#if (OCU_GTM_RAM_AR_RELEASE_REVISION_VERSION != OCU_GTM_RAM_C_AR_RELEASE_REVISION_VERSION)
  #error "Ocu_GTM_Ram.c : Mismatch in Release Revision Version"
#endif
#if (OCU_GTM_RAM_SW_MAJOR_VERSION != OCU_GTM_RAM_C_SW_MAJOR_VERSION)
  #error "Ocu_GTM_Ram.c : Mismatch in Software Major Version"
#endif
#if (OCU_GTM_RAM_SW_MINOR_VERSION != OCU_GTM_RAM_C_SW_MINOR_VERSION)
  #error "Ocu_GTM_Ram.c : Mismatch in Software Minor Version"
#endif
#if (OCU_GTM_RAM_SW_PATCH_VERSION != OCU_GTM_RAM_C_SW_PATCH_VERSION)
  #error "Ocu_GTM_Ram.c : Mismatch in Software Patch Version"
#endif
/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/
#define OCU_START_SEC_CONST_PTR
#include "Ocu_MemMap.h"
/* The Function table for GTM */
CONST(Ocu_HwFuncTableType, OCU_CONST) Ocu_GtmFunc =
{
  #if (OCU_GTM_TBU_ATOM_SOMB_USED == STD_ON)
  &Ocu_HW_Gtm_AtomTbuInit,
  #else
  NULL_PTR,
  #endif
  &Ocu_HW_Gtm_ChannelInit,
  #if (OCU_DE_INIT_API == STD_ON)
  &Ocu_HW_Gtm_ChannelDeInit,
  #if (OCU_GTM_TBU_ATOM_SOMB_USED == STD_ON)
  &Ocu_HW_Gtm_UnitDeInit,
  #else
  NULL_PTR,
  #endif
  #endif
  &Ocu_HW_Gtm_StartRestartChannel,
  &Ocu_HW_Gtm_StopChannel,
  #if (OCU_SET_PIN_STATE_API == STD_ON)
  #if (OCU_GTM_TBU_ATOM_SOMB_USED == STD_ON)
  &Ocu_HW_Gtm_SetPinState,
  #else
  NULL_PTR,
  #endif
  #endif
  #if (OCU_SET_PIN_ACTION_API == STD_ON)
  NULL_PTR,
  #endif
  #if (((OCU_SET_ABSOLUTE_THRESHOLD_API == STD_ON) || (OCU_SET_RELATIVE_THRESHOLD_API == STD_ON)) \
                                                                                  || (OCU_GET_COUNTER_API == STD_ON))
  &Ocu_HW_Gtm_GetCounter,
  #endif
  #if ((OCU_SET_ABSOLUTE_THRESHOLD_API == STD_ON) || (OCU_SET_RELATIVE_THRESHOLD_API == STD_ON))
  &Ocu_HW_Gtm_SetThreshold,
  #endif
  &Ocu_HW_Gtm_EnableInterrupt,
  &Ocu_HW_Gtm_DisableInterrupt
};
#define OCU_STOP_SEC_CONST_PTR
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#if (OCU_GTM_TBU_ATOM_SOMB_USED == STD_ON)
#define OCU_START_SEC_VAR_NO_INIT_PTR
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/* Global pointer to the address of TBU Unit Config data */
P2CONST(Ocu_GtmTbuUnitConfigType, OCU_VAR, OCU_CONFIG_CONST) Ocu_GpGtmTbuUnitConfig;
#define OCU_STOP_SEC_VAR_NO_INIT_PTR
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define OCU_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/* RAM Allocation of OCU TBU cyclic data */
VAR(Ocu_GaaCyclicRamDataType, OCU_VAR_NO_INIT) Ocu_GaaCyclicRamData[OCU_TOTAL_ATOM_OUTPUT_USED];
#define OCU_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif

#endif /*#if (OCU_GTM_UNIT_USED == STD_ON)*/
/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
