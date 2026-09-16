/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Gpt_TAUD_PBTypes.h                                                                                  */
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
 *                       1.Remove QAC message 1534, 1536
 *  2.0.1  17/10/2023  : Add QAC message 1534, 1536
 *  2.0.0  26/07/2023  : Remove qac message 0841 header, GPT_INSTANCE_INDEX, Gpt_MultiInstance.h,
 *                       Change Gpt_Mapping.h to Gpt_MemMap.h
 *         12/05/2023  : Update SW version 2.0.0
 *  1.3.2  22/08/2021  : Following Changes were made:
 *                       1. Updated header file macro to call file multiple times.
 *                       2. Using #include GPT_CFG_HEADER instead of
 *                          #include "Gpt_cfg.h".
 *                       3. Added QAC message 9.5.0.
 *  1.3.1  02/07/2021  : Format source code to 120 characters.
 *  1.2.0  17/07/2020  : Release.
 *  1.1.0  19/06/2020  : Release.
 *  1.0.0  01/01/2020  : Initial Version.
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/

#ifndef GPT_TAUD_PBTYPES_HEADER
#define GPT_TAUD_PBTYPES_HEADER

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
#define GPT_TAUD_PBTYPES_AR_RELEASE_MAJOR_VERSION    GPT_AR_RELEASE_MAJOR_VERSION_VALUE
#define GPT_TAUD_PBTYPES_AR_RELEASE_MINOR_VERSION    GPT_AR_RELEASE_MINOR_VERSION_VALUE
#define GPT_TAUD_PBTYPES_AR_RELEASE_REVISION_VERSION GPT_AR_RELEASE_REVISION_VERSION_VALUE
/* File version information */
#define GPT_TAUD_PBTYPES_SW_MAJOR_VERSION            GPT_SW_MAJOR_VERSION
#define GPT_TAUD_PBTYPES_SW_MINOR_VERSION            GPT_SW_MINOR_VERSION
#define GPT_TAUD_PBTYPES_SW_PATCH_VERSION            GPT_SW_PATCH_VERSION

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/
#if (GPT_TIMER_IP_TAUD == STD_ON)

/* Mask value for TAUD */
#define GPT_RESET_TAUD_DATA_REG         (uint16)0x0000
#define GPT_RESET_TAUD_CONTROL_MODE_REG (uint16)0x0000
#define GPT_STOP_TAUD_ALL_CH            (uint16)0xFFFF
/***********************************************************************************************************************
**                                Structure for TAUD unit user register configuration                                 **
***********************************************************************************************************************/
typedef volatile struct STag_Gpt_TAUDUnitUserRegs
{
  uint16 usTAUDnTOL;
  uint16 usReserved1;
  uint16 usTAUDnRDT;
  uint16 aaReserved2[3];
  uint16 usTAUDnTRO;
  uint16 usReserved3;
  uint16 usTAUDnTME;
  uint16 usReserved4;
  uint16 usTAUDnTDL;
  uint16 usReserved5;
  uint16 usTAUDnTO;
  uint16 aaReserved6[179];
  uint16 usTAUDnTE;
  uint16 usReserved7;
  uint16 usTAUDnTS;
  uint16 usReserved8;
  uint16 usTAUDnTT;
} Gpt_TAUDUnitUserRegs;
/***********************************************************************************************************************
**                                 Structure for TAUD unit OS register configuration                                  **
***********************************************************************************************************************/
typedef volatile struct STag_Gpt_TAUDUnitOsRegs
{
  uint16 usTAUDnTPS;
  uint16 usReserved1;
  uint8 ucTAUDnBRS;
  uint8 aaReserved2[3];
  uint16 usTAUDnTOM;
  uint16 usReserved3;
  uint16 usTAUDnTOC;
  uint16 usReserved4;
  uint16 usTAUDnTDE;
  uint16 usReserved5;
  uint16 usTAUDnTDM;
  uint16 usReserved6;
  uint16 usTAUDnTRE;
  uint16 usReserved7;
  uint16 usTAUDnTRC;
  uint16 usReserved8;
  uint16 usTAUDnRDE;
  uint16 usReserved9;
  uint16 usTAUDnRDM;
  uint16 usReserved10;
  uint16 usTAUDnRDS;
  uint16 usReserved11;
  uint16 usTAUDnRDC;
} Gpt_TAUDUnitOsRegs;
/***********************************************************************************************************************
**                                  Structure for TAUD channel user control register                                  **
***********************************************************************************************************************/
typedef volatile struct STag_Gpt_TAUDUserRegs
{
  uint16 usTAUDnCDRm;
  uint16 aaReserved1[63];
  uint16 usTAUDnCNTm;
  uint16 aaReserved2[31];
  uint8 ucTAUDnCMURm;
} Gpt_TAUDChannelUserRegs;
/***********************************************************************************************************************
**                                           Global configuration constants                                           **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/
#endif /* GPT_TIMER_IP_TAUD == STD_ON */
#endif /* GPT_TAUD_PBTYPES_HEADER */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
