/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2X MCAL Components                                                                 */
/* Module       = Ocu_TAUD_PBTypes.h                                                                                  */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2023-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains macros and structure data types for post build parameters of OCU Driver                         */
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
 *  1.0.1  23/10/2023  : Change from OCU_AR_RELEASE_MAJOR_VERSION_VALUE to OCU_AR_RELEASE_MAJOR_VERSION
                         Change from OCU_AR_RELEASE_MINOR_VERSION_VALUE to OCU_AR_RELEASE_MINOR_VERSION
                         Change from OCU_AR_RELEASE_REVISION_VERSION_VALUE to OCU_AR_RELEASE_REVISION_VERSION
           17/10/2023  : Add new QAC message 1534 and 1536
           25/09/2023  : Remove OCU_TAUD_MASTER_CMOR_SETTING and OCU_TAUD_SLAVE_CMOR_SETTING
                         Old: master channel running interval timer mode and slave channel running one count mode
                              both master channel and slave channel running in Synchronous Channel Operation
                         New: master channel running interval timer mode and slave channel running interval timer mode
                              both master channel and slave channel running in Independent Channel Operation
                         Reason: The old channel hardware mode is only confirm by testing and not conform the HWM
 *  1.0.0  04/04/2023  : Initial Version
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/

#ifndef OCU_TAUD_PBTYPES_H
#define OCU_TAUD_PBTYPES_H

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for using Std Type(e.g. STD_ON), Compiler Macros(e.g. P2FUNC), Platform Types(e.g. uint8) */
#include "Std_Types.h"
/* Included for OCU module specific definitions */
#include "Ocu_Cfg.h"
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR Release version information */
#define OCU_TAUD_PBTYPES_AR_RELEASE_MAJOR_VERSION    OCU_AR_RELEASE_MAJOR_VERSION
#define OCU_TAUD_PBTYPES_AR_RELEASE_MINOR_VERSION    OCU_AR_RELEASE_MINOR_VERSION
#define OCU_TAUD_PBTYPES_AR_RELEASE_REVISION_VERSION OCU_AR_RELEASE_REVISION_VERSION
/* File version information */
#define OCU_TAUD_PBTYPES_SW_MAJOR_VERSION            OCU_SW_MAJOR_VERSION
#define OCU_TAUD_PBTYPES_SW_MINOR_VERSION            OCU_SW_MINOR_VERSION
#define OCU_TAUD_PBTYPES_SW_PATCH_VERSION            OCU_SW_PATCH_VERSION

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/
#if (OCU_TIMER_IP_TAUD == STD_ON)

/***********************************************************************************************************************
**                                Structure for TAUD unit user register configuration                                 **
***********************************************************************************************************************/
typedef volatile struct STag_Ocu_TAUDUnitUserRegs
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
  uint16 aaReserved6;
  uint16 usTAUDnTOE;
  uint16 aaReserved7[177];
  uint16 usTAUDnTE;
  uint16 usReserved8;
  uint16 usTAUDnTS;
  uint16 usReserved9;
  uint16 usTAUDnTT;
} Ocu_TAUDUnitUserRegs;
/***********************************************************************************************************************
**                                 Structure for TAUD unit OS register configuration                                  **
***********************************************************************************************************************/
typedef volatile struct STag_Ocu_TAUDUnitOsRegs
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
} Ocu_TAUDUnitOsRegs;
/***********************************************************************************************************************
**                                  Structure for TAUD channel user control register                                  **
***********************************************************************************************************************/
typedef volatile struct STag_Ocu_TAUDUserRegs
{
  uint16 usTAUDnCDRm;
  uint16 aaReserved1[63];
  uint16 usTAUDnCNTm;
  uint16 aaReserved2[31];
  uint8 ucTAUDnCMURm;
} Ocu_TAUDChannelUserRegs;
/***********************************************************************************************************************
**                                           Global configuration constants                                           **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/
#endif /* OCU_TIMER_IP_TAUD == STD_ON */
#endif /* OCU_TAUD_PBTYPES_H */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
