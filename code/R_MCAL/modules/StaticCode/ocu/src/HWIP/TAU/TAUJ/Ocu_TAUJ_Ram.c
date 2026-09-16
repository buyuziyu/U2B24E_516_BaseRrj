/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2X MCAL Components                                                                 */
/* Module       = Ocu_TAUJ_Ram.c                                                                                      */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2023-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Global variable declarations                                                                                       */
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
 *  1.0.1  17/10/2023  : Delete QAC message 1531
 *  1.0.0  29/03/2023  : Initial Version
 */
/***********************************************************************************************************************
**                                             Margin for Control History                                             **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (4:5087)    : Use of #include directive after code fragment.                                               */
/* Rule                : MISRA C:2012 Rule-20.1                                                                       */
/* JV-01 Justification : This is done as per Memory Requirement, (MEMMAP003 - Specification of Memory Mapping).       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for RAM variable declarations */
#include "Ocu_TAUJ_Ram.h"
/* Included for function table of low-level functions */
#include "Ocu_TAUJ_LLDriver.h"
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR Release version information */
#define OCU_TAUJ_RAM_C_AR_RELEASE_MAJOR_VERSION    OCU_AR_RELEASE_MAJOR_VERSION_VALUE
#define OCU_TAUJ_RAM_C_AR_RELEASE_MINOR_VERSION    OCU_AR_RELEASE_MINOR_VERSION_VALUE
#define OCU_TAUJ_RAM_C_AR_RELEASE_REVISION_VERSION OCU_AR_RELEASE_REVISION_VERSION_VALUE
/* File version information */
#define OCU_TAUJ_RAM_C_SW_MAJOR_VERSION            OCU_SW_MAJOR_VERSION_VALUE
#define OCU_TAUJ_RAM_C_SW_MINOR_VERSION            OCU_SW_MINOR_VERSION_VALUE
/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (OCU_TAUJ_RAM_AR_RELEASE_MAJOR_VERSION != OCU_TAUJ_RAM_C_AR_RELEASE_MAJOR_VERSION)
  #error "Ocu_TAUJ_Ram.c : Mismatch in Release Major Version"
#endif
#if (OCU_TAUJ_RAM_AR_RELEASE_MINOR_VERSION != OCU_TAUJ_RAM_C_AR_RELEASE_MINOR_VERSION)
  #error "Ocu_TAUJ_Ram.c : Mismatch in Release Minor Version"
#endif
#if (OCU_TAUJ_RAM_AR_RELEASE_REVISION_VERSION != OCU_TAUJ_RAM_C_AR_RELEASE_REVISION_VERSION)
  #error "Ocu_TAUJ_Ram.c : Mismatch in Release Revision Version"
#endif
#if (OCU_TAUJ_RAM_SW_MAJOR_VERSION != OCU_TAUJ_RAM_C_SW_MAJOR_VERSION)
  #error "Ocu_TAUJ_Ram.c : Mismatch in Software Major Version"
#endif
#if (OCU_TAUJ_RAM_SW_MINOR_VERSION != OCU_TAUJ_RAM_C_SW_MINOR_VERSION)
  #error "Ocu_TAUJ_Ram.c : Mismatch in Software Minor Version"
#endif

/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/
#if (OCU_TIMER_IP_TAUJ == STD_ON)
#define OCU_START_SEC_CONST_PTR
#include "Ocu_MemMap.h"
CONST(Ocu_HwFuncTableType, OCU_CONST) Ocu_TaujFunc =
{
  &Ocu_HW_Tauj_UnitInit,
  &Ocu_HW_Tauj_ChannelInit,
  #if (OCU_DE_INIT_API == STD_ON)
  &Ocu_HW_Tauj_ChannelDeInit,
  NULL_PTR,
  #endif
  &Ocu_HW_Tauj_StartRestartChannel,
  &Ocu_HW_Tauj_StopChannel,
  #if (OCU_SET_PIN_STATE_API == STD_ON)
  &Ocu_HW_Tauj_SetPinState,
  #endif
  #if (OCU_SET_PIN_ACTION_API == STD_ON)
  &Ocu_HW_Tauj_SetPinAction,
  #endif
  #if (((OCU_SET_ABSOLUTE_THRESHOLD_API == STD_ON) || (OCU_SET_RELATIVE_THRESHOLD_API == STD_ON)) \
                                                                                  || (OCU_GET_COUNTER_API == STD_ON))
  &Ocu_HW_Tauj_GetCounter,
  #endif
  #if (OCU_SET_ABSOLUTE_THRESHOLD_API == STD_ON) || (OCU_SET_RELATIVE_THRESHOLD_API == STD_ON)
  &Ocu_HW_Tauj_SetThreshold,
  #endif
  &Ocu_HW_Tauj_EnableInterrupt,
  &Ocu_HW_Tauj_DisableInterrupt
};
#define OCU_STOP_SEC_CONST_PTR
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* OCU_TIMER_IP_TAUJ == STD_ON */
/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
