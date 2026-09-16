/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2X MCAL Components                                                                 */
/* Module       = Ocu_TAUJ_PBTypes.h                                                                                  */
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
 *  1.3.1   31/03/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 and RH850/U2Bx-E MCAL Ver22.00.02 Release
 *  1.3.0   28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 *  1.2.0   31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 *  1.0.1   23/10/2023  : Change from OCU_AR_RELEASE_MAJOR_VERSION_VALUE to OCU_AR_RELEASE_MAJOR_VERSION
                         Change from OCU_AR_RELEASE_MINOR_VERSION_VALUE to OCU_AR_RELEASE_MINOR_VERSION
                         Change from OCU_AR_RELEASE_REVISION_VERSION_VALUE to OCU_AR_RELEASE_REVISION_VERSION
            17/10/2023  : Add new QAC message 1534 and 1536
            25/09/2023  : Remove OCU_TAUJ_MASTER_CMOR_SETTING and OCU_TAUJ_SLAVE_CMOR_SETTING
                         Old: master channel running interval timer mode and slave channel running one count mode
                              both master channel and slave channel running in Synchronous Channel Operation
                         New: master channel running interval timer mode and slave channel running interval timer mode
                              both master channel and slave channel running in Independent Channel Operation
                         Reason: The old channel hardware mode is only confirm by testing and not conform the HWM
 *  1.0.0   04/04/2023  : Initial Version
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/

#ifndef OCU_TAUJ_PBTYPES_H
#define OCU_TAUJ_PBTYPES_H

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
#define OCU_TAUJ_PBTYPES_AR_RELEASE_MAJOR_VERSION    OCU_AR_RELEASE_MAJOR_VERSION
#define OCU_TAUJ_PBTYPES_AR_RELEASE_MINOR_VERSION    OCU_AR_RELEASE_MINOR_VERSION
#define OCU_TAUJ_PBTYPES_AR_RELEASE_REVISION_VERSION OCU_AR_RELEASE_REVISION_VERSION
/* File version information */
#define OCU_TAUJ_PBTYPES_SW_MAJOR_VERSION            OCU_SW_MAJOR_VERSION
#define OCU_TAUJ_PBTYPES_SW_MINOR_VERSION            OCU_SW_MINOR_VERSION
#define OCU_TAUJ_PBTYPES_SW_PATCH_VERSION            OCU_SW_PATCH_VERSION

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/
#if (OCU_TIMER_IP_TAUJ == STD_ON)

/***********************************************************************************************************************
**                                Structure for TAUJ unit user register configuration                                 **
***********************************************************************************************************************/
typedef volatile struct STag_Ocu_TAUJUnitUserRegs
{
  uint8 ucTAUJnTE;
  uint8 aaReserved1[3];
  uint8 ucTAUJnTS;
  uint8 aaReserved2[3];
  uint8 ucTAUJnTT;
  uint8 aaReserved3[3];
  uint8 ucTAUJnTO;
  uint8 aaReserved4[3];
  uint8 ucTAUJnTOE;
  uint8 aaReserved5[3];
  uint8 ucTAUJnTOL;
  uint8 aaReserved6[3];
  uint8 ucTAUJnRDT;
  uint8 aaReserved7[3];
  uint8 ucTAUJnRSF;
} Ocu_TAUJUnitUserRegs;
/***********************************************************************************************************************
**                                      Structure for TAUJ unit os configuration                                      **
***********************************************************************************************************************/
typedef volatile struct STag_Ocu_TAUJUnitOsRegs
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
} Ocu_TAUJUnitOsRegs;
/***********************************************************************************************************************
**                                  Structure for TAUJ channel user control register                                  **
***********************************************************************************************************************/
typedef volatile struct STag_Ocu_TAUJUserRegs
{
  uint32 ulTAUJnCDRm;
  uint32 aaReserved1[3];
  uint32 ulTAUJnCNTm;
  uint32 aaReserved2[3];
  uint8 ucTAUJnCMURm;
} Ocu_TAUJChannelUserRegs;
/***********************************************************************************************************************
**                                           Global configuration constants                                           **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/
#endif /* OCU_TIMER_IP_TAUJ == STD_ON */
#endif /* OCU_TAUJ_PBTYPES_H */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
