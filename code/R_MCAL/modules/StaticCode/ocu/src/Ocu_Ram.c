/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2X MCAL Components                                                                 */
/* Module       = Ocu_Ram.c                                                                                           */
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
 *  1.1.1  30/08/2024  : As part of Multi Variant support, following changes are made:
 *                       1. Add definition of global variable: Ocu_GulPollingTimes, Ocu_GucKernelCoreId, 
 *                          Ocu_GblCountingDirection.
 *  1.0.1  17/10/2023  : Delete QAC message 1531
 *  1.0.0  04/04/2023  : Initial Version
 */
/**********************************************************************************************************************/
/***********************************************************************************************************************
**                                             Margin for Control History                                             **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE Rule CWE-398, CWE-569                                            */
/* JV-01 Justification : Compiler keyword (macro) is defined and used following AUTOSAR standard rule. It is accepted.*/
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:5087)    : Use of #include directive after code fragment.                                               */
/* Rule                : MISRA C:2012 Rule-20.1                                                                       */
/* JV-01 Justification : This is done as per Memory Requirement, (MEMMAP003 - Specification of Memory Mapping).       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for Ocu.h inclusion and macro definitions */
#include "Ocu.h"
/* Included for RAM variable declarations */
#include "Ocu_Ram.h"
/* Included for definitions of OCU_UNINITIALIZED */
#include "Ocu_PBTypes.h"
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR Release version information */
#define OCU_RAM_C_AR_RELEASE_MAJOR_VERSION OCU_AR_RELEASE_MAJOR_VERSION_VALUE
#define OCU_RAM_C_AR_RELEASE_MINOR_VERSION OCU_AR_RELEASE_MINOR_VERSION_VALUE
#define OCU_RAM_C_AR_RELEASE_PATCH_VERSION OCU_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define OCU_RAM_C_SW_MAJOR_VERSION         OCU_SW_MAJOR_VERSION_VALUE
#define OCU_RAM_C_SW_MINOR_VERSION         OCU_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (OCU_RAM_AR_RELEASE_MAJOR_VERSION != OCU_RAM_C_AR_RELEASE_MAJOR_VERSION)
  #error "Ocu_Ram.c : Mismatch in Release Major Version"
#endif
#if (OCU_RAM_AR_RELEASE_MINOR_VERSION != OCU_RAM_C_AR_RELEASE_MINOR_VERSION)
  #error "Ocu_Ram.c : Mismatch in Release Minor Version"
#endif
#if (OCU_RAM_AR_RELEASE_REVISION_VERSION != OCU_RAM_C_AR_RELEASE_PATCH_VERSION)
  #error "Ocu_Ram.c : Mismatch in Release Revision Version"
#endif
#if (OCU_RAM_SW_MAJOR_VERSION != OCU_RAM_C_SW_MAJOR_VERSION)
  #error "Ocu_Ram.c : Mismatch in Software Major Version"
#endif
#if (OCU_RAM_SW_MINOR_VERSION != OCU_RAM_C_SW_MINOR_VERSION)
  #error "Ocu_Ram.c : Mismatch in Software Minor Version"
#endif

/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/
#define OCU_START_SEC_VAR_NO_INIT_PTR
#include "Ocu_MemMap.h"
/* Global pointer variable for channel configuration */
P2CONST(Ocu_ChannelConfigType, OCU_VAR_NO_INIT, OCU_CONFIG_CONST) volatile Ocu_GpChannelConfig;
/* Global pointer variable for channel data */
P2VAR(Ocu_ChannelRamDataType, OCU_VAR_NO_INIT, OCU_VAR_NO_INIT) volatile Ocu_GpChannelRamData;                          /* PRQA S 3432 # JV-01 */

#define OCU_STOP_SEC_VAR_NO_INIT_PTR
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define OCU_START_SEC_VAR_INIT_BOOLEAN
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/* Holds the status of Initialization */
volatile VAR(boolean, OCU_VAR_INIT) Ocu_GblDriverStatus = OCU_UNINITIALIZED;
#define OCU_STOP_SEC_VAR_INIT_BOOLEAN
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define OCU_START_SEC_VAR_NO_INIT_BOOLEAN
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/* Holds configured counting direction */
volatile boolean Ocu_GblCountingDirection;
#define OCU_STOP_SEC_VAR_NO_INIT_BOOLEAN
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#if (OCU_MULTI_CORE_SUPPORT == STD_ON)
#define OCU_START_SEC_VAR_INIT_8
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/* Holds the kernel core ID in multicore */
uint8 Ocu_GucKernelCoreId = OCU_ZERO;
#define OCU_STOP_SEC_VAR_INIT_8
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif

#if (OCU_MULTI_CORE_SUPPORT == STD_ON)
#define OCU_START_SEC_VAR_NO_INIT_32
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/* Hold the polling times for Ocu_StartChannel and Ocu_SetAbsolute/RelativeThreshold */
uint32 Ocu_GulPollingTimes;
#define OCU_STOP_SEC_VAR_NO_INIT_32
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif
/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
