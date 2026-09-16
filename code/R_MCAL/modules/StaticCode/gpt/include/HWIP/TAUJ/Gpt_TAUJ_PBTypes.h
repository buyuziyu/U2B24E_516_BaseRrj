/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Gpt_TAUJ_PBTypes.h                                                                                  */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2020,2021,2023-2025 Renesas Electronics Corporation. All rights reserved.                                      */
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
 *  2.3.2  25/04/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03
 *  2.3.1  31/03/2025  : Update SW-VERSION for RH850/U2BxE MCAL Ver22.00.02/Ver22.00.02.D Release
 *  2.3.0  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 *  2.2.0  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 *  2.1.2  31/10/2024  : As part of QAC 9.5.0 support, following changes are made
 *                       1.Remove QAC message 1534, 1535, 1536
 *                       2.Add QAC message 3648
 *  2.0.1  07/10/2023  : Add QAC message 1534, 1536
 *                       Update memory section from CONFIG_DATA to CONFIG_DATA_POSTBUILD
 *  2.0.0  26/07/2023  : Remove qac message 0841 header, GPT_INSTANCE_INDEX, Gpt_MultiInstance.h,
 *                       Change Gpt_Mapping.h to Gpt_MemMap.h
 *         12/05/2023  : Update SW version 2.0.0
 *  1.3.2  22/08/2021  : Following Changes were made:
 *                       1. Updated header file macro to call file multiple times.
 *                       2. Using #include GPT_CFG_HEADER instead of
 *                          #include "Gpt_cfg.h".
 *                       3. Changed name STag_Gpt_Gpt_PredefTimerTAUJUnitConfigType to
 *                          STag_Gpt_PredefTimerTAUJUnitConfigType.
 *                       4. Added QAC message 9.5.0.
 *  1.3.1  02/07/2021  : Added QAC message 9.5.0.
 *                       Format source code to 120 characters.
 *                       Improve Violation tag (remove START/END).
 *  1.2.0  17/07/2020  : Release.
 *  1.1.0  19/06/2020  : Release.
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

#ifndef GPT_TAUJ_PBTYPES_HEADER
#define GPT_TAUJ_PBTYPES_HEADER

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for using Std Type(e.g. STD_ON), Compiler Macros(e.g. P2FUNC), Platform Types(e.g. uint8) */
#include "Std_Types.h"
/* Include difinition of multi instance */

/* Included for GPT module specific definitions */
#include "Gpt_Cfg.h"
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR Release version information */
#define GPT_TAUJ_PBTYPES_AR_RELEASE_MAJOR_VERSION    GPT_AR_RELEASE_MAJOR_VERSION_VALUE
#define GPT_TAUJ_PBTYPES_AR_RELEASE_MINOR_VERSION    GPT_AR_RELEASE_MINOR_VERSION_VALUE
#define GPT_TAUJ_PBTYPES_AR_RELEASE_REVISION_VERSION GPT_AR_RELEASE_REVISION_VERSION_VALUE
/* File version information */
#define GPT_TAUJ_PBTYPES_SW_MAJOR_VERSION            GPT_SW_MAJOR_VERSION
#define GPT_TAUJ_PBTYPES_SW_MINOR_VERSION            GPT_SW_MINOR_VERSION
#define GPT_TAUJ_PBTYPES_SW_PATCH_VERSION            GPT_SW_PATCH_VERSION

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/
#if (GPT_TIMER_IP_TAUJ == STD_ON)

/* Mask Value for TAUJ */
#define GPT_RESET_TAUJ_CONTROL_MODE_REG (uint16)0x0000
#define GPT_RESET_TAUJ_DATA_REG         (uint32)0x00000000UL
#define GPT_32BIT_MASK_VALUE            (uint32)0xFFFFFFFFUL
#define GPT_STOP_TAUJ_ALL_CH            (uint8)0x0F
/***********************************************************************************************************************
**                                Structure for TAUJ unit user register configuration                                 **
***********************************************************************************************************************/
typedef volatile struct STag_Gpt_TAUJUnitUserRegs
{
  uint8 ucTAUJnTE;
  uint8 aaReserved1[3];
  uint8 ucTAUJnTS;
  uint8 aaReserved2[3];
  uint8 ucTAUJnTT;
  uint8 aaReserved3[3];
  uint8 ucTAUJnTO;
  uint8 aaReserved4[7];
  uint8 ucTAUJnTOL;
  uint8 aaReserved5[3];
  uint8 ucTAUJnRDT;
  uint8 aaReserved6[3];
  uint8 ucTAUJnRSF;
} Gpt_TAUJUnitUserRegs;
/***********************************************************************************************************************
**                                      Structure for TAUJ unit os configuration                                      **
***********************************************************************************************************************/
typedef volatile struct STag_Gpt_TAUJUnitOsRegs
{
  uint16 usTAUJnTPS;
  uint16 usReserved1;
  uint8 ucTAUJnBRS;
  uint8 aaReserved2[3];
  uint8 ucTAUJnTOM;
  uint8 aaReserved3[3];
  uint8 ucTAUJnTOC;
  uint8 aaReserved4[3];
  uint8 ucTAUJnRDE;
  uint8 aaReserved5[3];
  uint8 ucTAUJnRDM;
} Gpt_TAUJUnitOsRegs;
/***********************************************************************************************************************
**                                  Structure for TAUJ channel user control register                                  **
***********************************************************************************************************************/
typedef volatile struct STag_Gpt_TAUJUserRegs
{
  uint32 ulTAUJnCDRm;
  uint32 aaReserved1[3];
  uint32 ulTAUJnCNTm;
  uint32 aaReserved2[3];
  uint8 ucTAUJnCMURm;
} Gpt_TAUJChannelUserRegs;
/***********************************************************************************************************************
**                                  Structure for TAUJ channel user control register                                  **
***********************************************************************************************************************/
typedef struct STag_Gpt_PredefTimerTAUJUnitConfigType
{
  /* Pointer to base address of TAU Channel Mode User register */
  P2VAR(void, TYPEDEF, REGSPACE) pPT_TAUJUnitUserCntlRegs;
} Gpt_PredefTimerTAUJUnitConfigType;
/***********************************************************************************************************************
**                                  Structure for TAUJ channel user control register                                  **
***********************************************************************************************************************/
typedef struct STag_Gpt_PredefTimerTAUJChannelConfigType
{
  /* Pointer to base address of channel user control TAU#nCDRm register */
  P2VAR(void, TYPEDEF, REGSPACE) pPT_CDRReg;
  /* Pointer to base address of channel TAU#nCMORm register */
  P2VAR(void, TYPEDEF, REGSPACE) pPT_CMORReg;
  /* Individual channel bit assigned value */
  uint8 ucPT_ChannelBitValue;
  /* For channels belonging to TAUD/TAUJ Bit 3-.0:0001: if GPT_CH_MODE_CONTINUOUS/GPT_CH_MODE_ONESHOT */
  uint16 usPT_ModeSettingValue;
} Gpt_PredefTimerTAUJChannelConfigType;
/***********************************************************************************************************************
**                                           Global configuration constants                                           **
***********************************************************************************************************************/
#define GPT_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Gpt_MemMap.h"

#if (GPT_GET_PREDEF_TIMER_VALUE_API == STD_ON)
extern CONST(Gpt_PredefTimerTAUJUnitConfigType, GPT_CONST) Gpt_GaaPT_TAUJUnitConfig[];                                  /* PRQA S 3684 # JV-01 */
extern CONST(Gpt_PredefTimerTAUJChannelConfigType, GPT_CONST) Gpt_GaaPT_TAUJChannelConfig[];                            /* PRQA S 3684 # JV-01 */
#endif

#define GPT_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Gpt_MemMap.h"
/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/
#endif /* GPT_TIMER_IP_TAUJ == STD_ON */
#endif /* GPT_TAUJ_PBTYPES_HEADER */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
