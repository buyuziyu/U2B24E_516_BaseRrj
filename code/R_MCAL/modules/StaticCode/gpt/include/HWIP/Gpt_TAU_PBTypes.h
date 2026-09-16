/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Gpt_TAU_PBTypes.h                                                                                   */
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
 *  2.3.2  25/04/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03
 *  2.3.1  31/03/2025  : Update SW-VERSION for RH850/U2BxE MCAL Ver22.00.02/Ver22.00.02.D Release
 *  2.3.0  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 *  2.2.0  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 *  2.1.2  31/10/2024  : As part of QAC 9.5.0 support, following changes are made
 *                       1.Add QAC message 3630. Remove header for QAC message 3684
 *                       2.Remove QAC message 1534, 1536
 *                       3.Add QAC message 3484
 *                       As part of Post Build multiple varriant support, following changes are made
 *                       1.Remove extern of structure Gpt_GaaPredefTimerConfig
 *  2.0.1  17/10/2023  : Add QAC message 1534, 1536
 *                     : Update memory section from CONFIG_DATA to CONFIG_DATA_POSTBUILD
 *  2.0.0  26/07/2023  : Remove qac message 0841 header, GPT_INSTANCE_INDEX, Gpt_MultiInstance.h,
 *                       Change Gpt_Mapping.h to Gpt_MemMap.h
 *         12/05/2023  : Update SW version 2.0.0
 *  1.4.2  17/05/2022  : Change name GPT_TAUD3_INTERRUPT_SELECTION_USED -> GPT_TAUD3_UNIT_USED
 *  1.4.1  11/11/2021  : Add pTAUD3INTNOSELxReg and ulTAUD3SelectInterruptMask to struct Gpt_TAUChannelConfigType
 *  1.3.2  22/08/2021  : Following Changes were made:
 *                       1. Updated header file macro to call file multiple times.
 *                       2. Using #include GPT_CFG_HEADER instead of
 *                          #include "Gpt_cfg.h".
 *                       3. Added QAC message 9.5.0.
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
/* Message (2:3630)    : The implementation of this struct/union type should be hidden.                               */
/* Rule                : MISRA C:2012 Dir-4.8                                                                         */
/* JV-01 Justification : This is accepted. Redundant of struct or union type has no affect to driver operation.       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

#ifndef GPT_TAU_PBTYPES_HEADER
#define GPT_TAU_PBTYPES_HEADER

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
#define GPT_TAU_PBTYPES_AR_RELEASE_MAJOR_VERSION    GPT_AR_RELEASE_MAJOR_VERSION_VALUE
#define GPT_TAU_PBTYPES_AR_RELEASE_MINOR_VERSION    GPT_AR_RELEASE_MINOR_VERSION_VALUE
#define GPT_TAU_PBTYPES_AR_RELEASE_REVISION_VERSION GPT_AR_RELEASE_REVISION_VERSION_VALUE
/* File version information */
#define GPT_TAU_PBTYPES_SW_MAJOR_VERSION            GPT_SW_MAJOR_VERSION
#define GPT_TAU_PBTYPES_SW_MINOR_VERSION            GPT_SW_MINOR_VERSION
#define GPT_TAU_PBTYPES_SW_PATCH_VERSION            GPT_SW_PATCH_VERSION

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                     Structure for TAU Unit configuration type                                      **
***********************************************************************************************************************/
typedef struct STag_Gpt_TAUUnitConfigType                                                                               /* PRQA S 3630 # JV-01 */
{
  /* Pointer to base address of TAU Channel Mode User register */
  P2VAR(void, TYPEDEF, REGSPACE) pTAUUnitUserCntlRegs;
  /* Pointer to base address of TAU Channel Mode OS register */
  P2VAR(void, TYPEDEF, REGSPACE) pTAUUnitOsCntlRegs;
  /* Type of GPT timer (TAUD/TAUJ/OSTM) */
  uint8 ucTimerType;
  /* TAU Configured Channels value */
  uint16 usTAUConfiguredChannelsValue;
  /* TAU Unit pre scaler for clock sources CK0, CK1, CK3 and CK4 */
  #if ((GPT_TAUD_CONFIG_PRESCALER_SUPPORTED == STD_ON) || (GPT_TAUJ_CONFIG_PRESCALER_SUPPORTED == STD_ON))
  uint16 usPrescaler;
  /* TAU Unit baud rate value */
  uint8 ucBaudRate;
  /* Pre scaler shared between ICU/GPT module */
  boolean blConfigurePrescaler;
  #endif
} Gpt_TAUUnitConfigType;

/***********************************************************************************************************************
**                                         Structure for channel information                                          **
***********************************************************************************************************************/
typedef struct STag_Gpt_TAUChannelConfigType
{
  /* Pointer to base address of channel user control TAU#nCDRm register */
  P2VAR(void, TYPEDEF, REGSPACE) pCDRReg;
  /* Pointer to base address of channel TAU#nCMORm register */
  P2VAR(void, TYPEDEF, REGSPACE) pCMORReg;
  /* Individual channel bit assigned value */
  uint16 usChannelBitValue;
  /* For channels belonging to TAUD/TAUJ Bit 3-.0:0001: if GPT_CH_MODE_CONTINUOUS/GPT_CH_MODE_ONESHOT */
  uint16 usModeSettingValue;
  /* TAUD3 interrupt number selection */
  #if (GPT_TAUD3_UNIT_USED == STD_ON)
  /* Pointer to base address of TAUD3INTNOSELx register */
  P2VAR(volatile uint32, TYPEDEF, REGSPACE) pTAUD3INTNOSELxReg;
  /* Mask value for channels in TAUD3 configured to support selection interrupt number */
  uint32 ulTAUD3SelectInterruptMask;
  #endif
} Gpt_TAUChannelConfigType;

/***********************************************************************************************************************
**                                           Global configuration constants                                           **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/

#endif /* GPT_TAU_PBTYPES_HEADER */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
