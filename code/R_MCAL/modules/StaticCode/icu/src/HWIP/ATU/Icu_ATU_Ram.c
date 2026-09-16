/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Icu_ATU_Ram.c                                                                                       */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.                                                */
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
 * 2.4.1:  30/06/2025  : As part of support QAC 11.6.0, following changes are made:
 *                       1. Update QAC message and QAC header
 * 2.4.0:  30/05/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.01 Release
 * 2.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release 
 * 2.1.2:  31/10/2024  : As part of support QAC 9.5.0, following changes are made:
 *                       1. Update QAC message and QAC header 
 *                       As part of support GTM HWIP into common code, following changes are made:
 *                       1. Update constant Icu_AtuFunc
 *                       2. Add preprocesser ICU_ATU_TIMER_UNIT_USED
 * 2.0.1:  18/10/2023  : Remove QAC messages 0857, 1531
 * 2.0.0:  03/08/2023  : #include "Icu_Mapping.h" update to #include "Icu_MemMap.h" 
 *                       Remove all multi-instance including methods
 *                       Remove all supported multi-instance header file
 *                       Update Icu_AtuFunc from sec Var to CONST
 *                       New function "Icu_HW_Atu_SetMode"
 * 1.4.3:  17/04/2022  : Merge QAC message from U2Ax, E2x and U2Bx
 * 1.4.1:  18/10/2021  : Add QAC message 9.5.0
 *         05/10/2021  : Rename ATU5 -> ATU
 * 1.3.2:  30/08/2021  : Change from #include "Icu_MemMap.h" to #include "Icu_Mapping.h".
 * 1.3.1:  02/07/2021  : Format source code to 120 characters
 *         04/05/2021  : Updated memory section and memory class for Icu_AtuFunc
 *         15/09/2021  : Remove Icu_GpChannelRamData, Icu_GpSignalMeasurementData
 * 1.2.0:  17/07/2020  : Release
 * 1.1.0:  19/06/2020  : Release
 * 1.0.0:  25/03/2020  : Initial Version
 */
/**********************************************************************************************************************/

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
#include "Icu_LLDriver.h"
/* Included for internal functions */
#include "Icu_ATU_LLDriver.h"

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define ICU_ATU_RAM_C_AR_RELEASE_MAJOR_VERSION    ICU_AR_RELEASE_MAJOR_VERSION_VALUE
#define ICU_ATU_RAM_C_AR_RELEASE_MINOR_VERSION    ICU_AR_RELEASE_MINOR_VERSION_VALUE
#define ICU_ATU_RAM_C_AR_RELEASE_REVISION_VERSION ICU_AR_RELEASE_REVISION_VERSION_VALUE
/* File version information */
#define ICU_ATU_RAM_C_SW_MAJOR_VERSION            ICU_SW_MAJOR_VERSION_VALUE
#define ICU_ATU_RAM_C_SW_MINOR_VERSION            ICU_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (ICU_RAM_AR_RELEASE_MAJOR_VERSION != ICU_ATU_RAM_C_AR_RELEASE_MAJOR_VERSION)
  #error "Icu_ATU_Ram.c : Mismatch in Release Major Version"
#endif /* End of #if (ICU_RAM_AR_RELEASE_MAJOR_VERSION != ICU_RAM_C_AR_RELEASE_MAJOR_VERSION) */

#if (ICU_RAM_AR_RELEASE_MINOR_VERSION != ICU_ATU_RAM_C_AR_RELEASE_MINOR_VERSION)
  #error "Icu_ATU_Ram.c : Mismatch in Release Minor Version"
#endif /* End of #if (ICU_RAM_AR_RELEASE_MINOR_VERSION != ICU_RAM_C_AR_RELEASE_MINOR_VERSION) */

#if (ICU_RAM_AR_RELEASE_REVISION_VERSION != ICU_ATU_RAM_C_AR_RELEASE_REVISION_VERSION)
  #error "Icu_ATU_Ram.c : Mismatch in Release Revision Version"
#endif /* End of #if (ICU_RAM_AR_RELEASE_REVISION_VERSION != ICU_RAM_C_AR_RELEASE_REVISION_VERSION) */

#if (ICU_RAM_SW_MAJOR_VERSION != ICU_ATU_RAM_C_SW_MAJOR_VERSION)
  #error "Icu_ATU_Ram.c : Mismatch in Software Major Version"
#endif /* End of #if (ICU_RAM_SW_MAJOR_VERSION != ICU_RAM_C_SW_MAJOR_VERSION) */

#if (ICU_RAM_SW_MINOR_VERSION != ICU_ATU_RAM_C_SW_MINOR_VERSION)
  #error "Icu_ATU_Ram.c : Mismatch in Software Minor Version"
#endif /* End of #if (ICU_RAM_SW_MINOR_VERSION != ICU_RAM_C_SW_MINOR_VERSION) */

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/
#if (ICU_ATU_TIMER_UNIT_USED == STD_ON)

#define ICU_START_SEC_VAR_NO_INIT_PTR
#include "Icu_MemMap.h"

#if (ICU_TIMER_CLK_BUS_NOT_USED != ICU_TIMER_CLK_BUS_SELECTION_CONFIGURED)
/* Global pointer variable for ICU hardware unit configuration */
P2CONST(Icu_ATU_ClockBusConfigType, ICU_VAR_NO_INIT, ICU_CONFIG_DATA) Icu_GpTimerClkBusConfig;
#endif

#if ((ICU_ATUC_NOISE_CANCELLATION_ENABLE == STD_ON) || (ICU_ATUA_NOISE_CANCELLATION_ENABLE == STD_ON))
/* Global pointer variable for Timer Noise Cancellation configuration */
P2CONST(Icu_NoiseCancellationConfigType, ICU_VAR_NO_INIT, ICU_CONFIG_DATA) Icu_GpNoiseCancellationConfig;

#endif /* End of #if ((ICU_ATUC_NOISE_CANCELLATION_ENABLE == STD_ON) || \
                                                                      (ICU_ATUA_NOISE_CANCELLATION_ENABLE == STD_ON))*/

#define ICU_STOP_SEC_VAR_NO_INIT_PTR
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


#define ICU_START_SEC_CONST_PTR
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

CONST(Icu_HwFuncTableType, ICU_CONST) Icu_AtuFunc =
{
  &Icu_HW_Atu_UnitInit,
  &Icu_HW_Atu_ChannelInit,
  #if (ICU_DE_INIT_API == STD_ON)
  &Icu_HW_Atu_UnitDeInit,
  &Icu_HW_Atu_ChannelDeInit,
  #else
  NULL_PTR,
  NULL_PTR,
  #endif
  NULL_PTR,
  NULL_PTR,
  #if (ICU_SET_MODE_API == STD_ON)
  &Icu_HW_SetMode,
  #else
  NULL_PTR,
  #endif
  &Icu_HW_Atu_SetActivation,
  &Icu_HW_Atu_StartCountMeasurement,
  &Icu_HW_Atu_StopCountMeasurement,
  #if (ICU_EDGE_COUNT_API == STD_ON)
  &Icu_HW_Atu_ResetEdgeCount,
  #else
  NULL_PTR,
  #endif
  #if (ICU_GET_INPUT_LEVEL_API == STD_ON)
  &Icu_HW_GetInputLevel,
  #else
  NULL_PTR,
  #endif
  NULL_PTR
};
#define ICU_STOP_SEC_CONST_PTR
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /*(STD_ON == ICU_ATU_TIMER_UNIT_USED)*/
/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
