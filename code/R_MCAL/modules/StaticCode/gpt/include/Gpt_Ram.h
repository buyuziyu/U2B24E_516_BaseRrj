/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Gpt_Ram.h                                                                                           */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2020,2021,2023-2025 Renesas Electronics Corporation. All rights reserved.                                      */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Global variable declarations.                                                                                      */
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
 *  2.3.2  25/04/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03
 *  2.3.1  31/03/2025  : Update SW-VERSION for RH850/U2BxE MCAL Ver22.00.02/Ver22.00.02.D Release
 *  2.3.0  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 *  2.2.0  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 *  2.1.2  31/10/2024  : Update SW-VERSION for Ver22.01.02 Beta2 release
 *  2.1.1  30/08/2024  : As part of ARDAACL-46149 support, following changes are made
 *                       1.Add array define for Gpt_GaaChannelRamData when macros GPT_MULTI_CORE_SUPPORT = STD_ON
 *                       and GPT_TYPE_III_SUPPORT = STD_OFF
 *                       As part of Post Build multiple varriant support, following changes are made
 *                       1.Add extern for global variable Gpt_GucKernelCoreId
 *                       As part of QAC 9.5.0 support, following changes are made
 *                       1.Remove QAC message 1534
 *  2.0.1  17/10/2023  : Add QAC message 1534
 *         21/09/2023  : Seperate Gpt_GaaChannelRamData[GPT_TOTAL_CHANNELS_CONFIG] to 2 cases,
 *                       Gpt_GaaChannelRamData[GPT_TOTAL_CHANNELS_CONFIG] and
 *                       Gpt_GaaChannelRamData[GPT_TOTAL_TYPE_III_CHANNELS_CONFIG]
 *  2.0.0  26/08/2023  : Update memory section of Gpt_GaaHwFunc
 *         26/07/2023  : Remove Gpt_GpChannelRamData, Gpt_GpChannelConfig, Gpt_GblDriverStatus because they are
 *                       supported in generator output; Chane type of Gpt_GucDriverMode from uint8 to Gpt_ModeType
 *                       and memory section from VAR_NO_INIT_8 to VAR_INIT_UNSPECIFIED;
 *                       Change Gpt_Mapping.h to Gpt_MemMap.h; Add Gpt_GaaChannelRamData, Gpt_GaaGlobalAccPoint,
 *                       Gpt_GaaCoreId2Index, Gpt_GaaChannel2IpType
 *         12/05/2023  : Update SW version 2.0.0
 *  1.3.2  22/08/2021  : Following Changes were made:
 *                       1. Updated header file macro to call file multiple times.
 *                       2. Added QAC message 9.5.0.
 *  1.3.1  02/07/2021  : Added QAC message 9.5.0.
 *                       Format source code to 120 characters.
 *                       Improve Violation tag (remove START/END).
 *         06/05/2021  : Updated the Memclass to GPT_VAR_NO_INIT for
 *                       Gpt_GpChannelConfig and Gpt_GpPredefTimerConfig.
 *  1.2.0  17/07/2020  : Release.
 *  1.1.0  19/06/2020  : Release.
 *         26/05/2020  : Remove hard code in Gpt_GaaHwFunc[GPT_TOTAL_HW_IP_CONFIG].
 *         14/05/2020  : Move Function pointer variable Gpt_GaaHwFunc[] from Gpt.c.
 *  1.0.0  01/01/2020  : Initial Version.
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:3684)    : Array declared with unknown size.                                                            */
/* Rule                : MISRA C:2012 Rule-8.11, CERTCCM ARR02                                                        */
/* JV-01 Justification : Arrays used are verified in the file which are only declarations and size is configuration   */
/*                       dependent.                                                                                   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
#ifndef GPT_RAM_HEADER
#define GPT_RAM_HEADER

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for Type definitions */
#include "Gpt_PBTypes.h"
#include "Gpt_Types.h"

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR Release version information */
#define GPT_RAM_AR_RELEASE_MAJOR_VERSION    GPT_AR_RELEASE_MAJOR_VERSION_VALUE
#define GPT_RAM_AR_RELEASE_MINOR_VERSION    GPT_AR_RELEASE_MINOR_VERSION_VALUE
#define GPT_RAM_AR_RELEASE_REVISION_VERSION GPT_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define GPT_RAM_SW_MAJOR_VERSION            GPT_SW_MAJOR_VERSION
#define GPT_RAM_SW_MINOR_VERSION            GPT_SW_MINOR_VERSION
#define GPT_RAM_SW_PATCH_VERSION            GPT_SW_PATCH_VERSION

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/
#if (GPT_GET_PREDEF_TIMER_VALUE_API == STD_ON)
#define GPT_START_SEC_VAR_NO_INIT_PTR
#include "Gpt_MemMap.h"
/* Global pointer variable for Gpt Predef Timer configuration */
extern P2CONST(Gpt_PredefTimerConfigType, GPT_VAR_NO_INIT, GPT_CONFIG_CONST) Gpt_GpPredefTimerConfig;
#define GPT_STOP_SEC_VAR_NO_INIT_PTR
#include "Gpt_MemMap.h"
#endif
#define GPT_START_SEC_VAR_INIT_UNSPECIFIED
#include "Gpt_MemMap.h"
/* Holds the status of GPT Driver Component */
extern VAR(volatile Gpt_ModeType, GPT_VAR_INIT) Gpt_GucDriverMode;
#define GPT_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Gpt_MemMap.h"

#define GPT_START_SEC_VAR_INIT_PTR
#include "Gpt_MemMap.h"
/* Function pointer variable for ATU/OSTM/TAU# configuration */
extern P2CONST(Gpt_HwFuncTableType, GPT_VAR_INIT, GPT_CONFIG_DATA) Gpt_GaaHwFunc[];                                     /* PRQA S 3684 # JV-01 */
#define GPT_STOP_SEC_VAR_INIT_PTR
#include "Gpt_MemMap.h"


#if (GPT_MULTI_CORE_SUPPORT == STD_OFF)
#define GPT_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Gpt_MemMap.h"
/* RAM allocation for all active Channels */
extern VAR(volatile Gpt_ChannelRamDataType, GPT_VAR_NO_INIT) Gpt_GaaChannelRamData[GPT_TOTAL_CHANNELS_CONFIG];
#define GPT_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Gpt_MemMap.h"
#else /* GPT_MULTI_CORE_SUPPORT == STD_ON*/
#define GPT_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Gpt_MemMap.h"
#if (GPT_TYPE_III_SUPPORT == STD_ON)
/* RAM allocation for all active Channels */
extern VAR(volatile Gpt_ChannelRamDataType, GPT_VAR_NO_INIT) Gpt_GaaChannelRamData[GPT_TOTAL_TYPE_III_CHANNELS_CONFIG];
#else
/* RAM allocation for all active Channels */
extern VAR(volatile Gpt_ChannelRamDataType, GPT_VAR_NO_INIT) Gpt_GaaChannelRamData[];                                   /* PRQA S 3684 # JV-01 */
#endif
#define GPT_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Gpt_MemMap.h"

#define GPT_START_SEC_VAR_INIT_8
#include "Gpt_MemMap.h"
/* Holds the kernel core ID in multicore */
extern uint8 Gpt_GucKernelCoreId;
#define GPT_STOP_SEC_VAR_INIT_8
#include "Gpt_MemMap.h"
#endif /* End of GPT_MULTI_CORE_SUPPORT == STD_OFF*/


#define GPT_START_SEC_CONST_32
#include "Gpt_MemMap.h"
/* Global access point to global status, config data and RAM data */
extern CONST(Gpt_GlobalAccessPointType, GPT_CONST) Gpt_GaaGlobalAccPoint[GPT_NUM_CONFIGURED_CORE] ;
#define GPT_STOP_SEC_CONST_32
#include "Gpt_MemMap.h"

#define GPT_START_SEC_CONST_8
#include "Gpt_MemMap.h"
#if (GPT_MULTI_CORE_SUPPORT == STD_ON)
/* Convert core id to global access index (4 low bit) and indicate if there is any OSTM channel on core (4 high bit) */
extern CONST(uint8, GPT_CONFIG_DATA) Gpt_GaaCoreId2Index[GPT_SUPPORTED_CORE_MAX_NUM];
#endif
/* Convert Channel ID to HWIP */
extern CONST(uint8, GPT_CONFIG_DATA) Gpt_GaaChannel2IpType[GPT_TOTAL_CHANNELS_CONFIG];
#define GPT_STOP_SEC_CONST_8
#include "Gpt_MemMap.h"

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/

#endif /* GPT_RAM_HEADER */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
