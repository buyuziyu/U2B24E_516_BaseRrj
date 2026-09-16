/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Gpt_TAUD_LLDriver.h                                                                                 */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2020,2021,2023-2025 Renesas Electronics Corporation. All rights reserved.                                      */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Provision of prototypes for internal functions.                                                                    */
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
 *  2.1.2  31/10/2024  : As part of QAC 9.5.0 support, following changes are made
 *                       1.Remove QAC message 1534
 *  2.0.1  17/10/2023  : Add QAC message 1534
 *  2.0.0  26/07/2023  : Remove qac message 0841 header, GPT_INSTANCE_INDEX, Gpt_MultiInstance.h,
 *                       Change Gpt_Mapping.h to Gpt_MemMap.h
 *         12/05/2023  : Update SW version 2.0.0
 *  1.3.2  22/08/2021  : Following Changes were made:
 *                       1. Updated header file macro to call file multiple times.
 *                       2. Using #include GPT_CFG_HEADER instead of
 *                          #include "Gpt_cfg.h".
 *                       3. Added QAC message 9.5.0.
 *  1.3.1  02/07/2021  : Added QAC message 9.5.0.
 *                       Format source code to 120 characters.
 *                       Improve Violation tag (remove START/END).
 *         24/05/2021  : Fixed QAC Msg 3432.
 *  1.2.0  17/07/2020  : Release.
 *  1.1.0  19/06/2020  : Release.
 *  1.0.0  01/01/2020  : Initial Version.
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/

#ifndef GPT_TAUD_LLDRIVER_HEADER
#define GPT_TAUD_LLDRIVER_HEADER

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for using Std Type(e.g. STD_ON), Compiler Macros(e.g. P2FUNC), Platform Types(e.g. uint8) */
#include "Std_Types.h"
/* Include difinition of multi instance */

/* Included for GPT module specific definitions */
#include "Gpt_Cfg.h"
/* Included for Type of Gpt_ChannelType and Gpt_ValueType */
#include "Gpt_Types.h"
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR Release version information */
#define GPT_TAUD_LLDRIVER_AR_RELEASE_MAJOR_VERSION    GPT_AR_RELEASE_MAJOR_VERSION_VALUE
#define GPT_TAUD_LLDRIVER_AR_RELEASE_MINOR_VERSION    GPT_AR_RELEASE_MINOR_VERSION_VALUE
#define GPT_TAUD_LLDRIVER_AR_RELEASE_REVISION_VERSION GPT_AR_RELEASE_REVISION_VERSION_VALUE
/*  File version information */
#define GPT_TAUD_LLDRIVER_SW_MAJOR_VERSION            GPT_SW_MAJOR_VERSION
#define GPT_TAUD_LLDRIVER_SW_MINOR_VERSION            GPT_SW_MINOR_VERSION
#define GPT_TAUD_LLDRIVER_SW_PATCH_VERSION            GPT_SW_PATCH_VERSION
/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/
#if (GPT_TIMER_IP_TAUD == STD_ON)
#define GPT_START_SEC_CODE_FAST
#include "Gpt_MemMap.h"
extern FUNC(void, GPT_CODE_FAST) Gpt_HW_Taud_CbkNotification(uint8 LucChannelIdx);
#define GPT_STOP_SEC_CODE_FAST
#include "Gpt_MemMap.h"

#define GPT_START_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"
extern FUNC(void, GPT_PRIVATE_CODE)
                                   Gpt_HW_Taud_UnitInit(P2CONST(Gpt_ConfigType, AUTOMATIC, GPT_APPL_CONST) LpConfigPtr);
extern FUNC(void, GPT_PRIVATE_CODE) Gpt_HW_Taud_ChannelInit(Gpt_ChannelType LddChannel);
#if (GPT_DE_INIT_API == STD_ON)
extern FUNC(void, GPT_PRIVATE_CODE) Gpt_HW_Taud_DeInit(void);
extern FUNC(void, GPT_PRIVATE_CODE) Gpt_HW_Taud_UnitDeInit(void);
extern FUNC(void, GPT_PRIVATE_CODE) Gpt_HW_Taud_ChannelDeInit(Gpt_ChannelType LddChannel);
#endif
extern FUNC(void, GPT_PRIVATE_CODE) Gpt_HW_Taud_StopTimer(Gpt_ChannelType LddChannel);
extern FUNC(void, GPT_PRIVATE_CODE) Gpt_HW_Taud_StartTimer(Gpt_ChannelType LddChannel, Gpt_ValueType LddValue);
#if (GPT_TIME_ELAPSED_API == STD_ON)
extern FUNC(Gpt_ValueType, GPT_PRIVATE_CODE) Gpt_HW_Taud_GetTimeElapsed(Gpt_ChannelType LddChannel);
#endif
#if (GPT_TIME_REMAINING_API == STD_ON)
extern FUNC(Gpt_ValueType, GPT_PRIVATE_CODE) Gpt_HW_Taud_GetTimeRemaining(Gpt_ChannelType LddChannel);
#endif
extern FUNC(void, GPT_PRIVATE_CODE) Gpt_HW_Taud_EnableInterrupt(Gpt_ChannelType LddChannel);
extern FUNC(void, GPT_PRIVATE_CODE) Gpt_HW_Taud_DisableInterrupt(Gpt_ChannelType LddChannel);
#define GPT_STOP_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"

#endif /* GPT_TIMER_IP_TAUD == STD_ON */
#endif /* GPT_TAUD_LLDRIVER_HEADER */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
