/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Icu_TAUD_PBTypes.h                                                                                  */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains macros and structure data types for post build                                                  */
/* parameters of ICU Driver                                                                                           */
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
 * 2.4.1:  30/06/2025  : Remove SW-VERSION in file header
 * 2.4.0:  30/05/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.01 Release
 * 2.3.1:  31/03/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 and RH850/U2Bx-E MCAL Ver22.00.02 Release
 * 2.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release 
 * 2.1.2:  31/10/2024  : Update SW-VERSION for Ver22.01.02 Beta2 Release 
 *                       As part of support GTM HWIP into common code, following changes are made:
 *                       1.Update pre-compile condition
 *                       As part of support QAC 9.5.0, following changes are made:
 *                       1.Remove QAC messages 1534, 1536.
 * 2.0.1:  19/10/2023  : Add QAC messages 1534, 1536
 * 2.0.0:  03/08/2023  : #include "Icu_Mapping.h" update to #include "Icu_MemMap.h" 
 *                       Remove all multi-instance including methods
 *                       Remove all supported multi-instance header file
 * 1.3.2:  30/08/2021  : Update header file macro.
 * 1.3.1:  02/07/2021  : Format source code to 120 characters
 * 1.2.0:  17/07/2020  : Release
 * 1.1.0:  19/06/2020  : Release
 * 1.0.0:  25/03/2020  : Initial Version
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/

/**********************************************************************************************************************/
#ifndef ICU_TAUD_PBTYPES_H
#define ICU_TAUD_PBTYPES_H
/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/

/* To avoid QAC error */
#include "Icu_PBTypes.h"

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define ICU_TAUD_PBTYPES_AR_RELEASE_MAJOR_VERSION    ICU_AR_RELEASE_MAJOR_VERSION
#define ICU_TAUD_PBTYPES_AR_RELEASE_MINOR_VERSION    ICU_AR_RELEASE_MINOR_VERSION
#define ICU_TAUD_PBTYPES_AR_RELEASE_REVISION_VERSION ICU_AR_RELEASE_REVISION_VERSION

/* Module Software version information */
#define ICU_TAUD_PBTYPES_SW_MAJOR_VERSION            ICU_SW_MAJOR_VERSION
#define ICU_TAUD_PBTYPES_SW_MINOR_VERSION            ICU_SW_MINOR_VERSION

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/
#define ICU_TAUD_TIMER_RESET_VAL                     (uint16)0xFFFF
#define ICU_TAUD_START_DWNCNT_VAL                    (uint16)0xFFFF
#define ICU_TAUD_CNT_MASK_VAL                        (uint32)0x0000FFFFUL
#define ICU_TAUD_TPS_RESET_VAL                       (uint16)0xFFFF
#define ICU_TAUD_BRS_RESET_VAL                       (uint8)0x00
#define ICU_TAUD_CSC_RESET_VAL                       (uint8)0x01
#define ICU_TAUD_CMUR_RESET_VAL                      (uint8)0x00
#define ICU_TAUD_CDR_RESET_VAL                       (uint16)0x0000
#define ICU_TAUD_CMOR_RESET_VAL                      (uint16)0x0000

/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                           Data structure for Timer Array Units D user control registers                            **
***********************************************************************************************************************/
#if (ICU_TAUD_UNIT_USED == STD_ON)
typedef struct STag_Icu_TAUDUnitUserRegs
{
  uint16 volatile usTAUDnTOL;
  uint16 volatile usReserved1;
  uint16 volatile usTAUDnRDT;
  uint16 volatile usReserved2;
  uint16 volatile usTAUDnRSF;
  uint16 volatile usReserved3;
  uint16 volatile usTAUDnTRO;
  uint16 volatile usReserved4;
  uint16 volatile usTAUDnTME;
  uint16 volatile usReserved5;
  uint16 volatile usTAUDnTDL;
  uint16 volatile usReserved6;
  uint16 volatile usTAUDnTO;
  uint16 volatile usReserved7;
  uint16 volatile usTAUDnTOE;
  uint16 volatile aaReserved8[ICU_ONEHUNDRED_SEVENTY_SEVEN];
  uint16 volatile usTAUDnTE;
  uint16 volatile usReserved9;
  uint16 volatile usTAUDnTS;
  uint16 volatile usReserved10;
  uint16 volatile usTAUDnTT;
} Icu_TAUDUnitUserRegs;

/***********************************************************************************************************************
**                            Data structure for Timer Array Units D os control registers                             **
***********************************************************************************************************************/
typedef struct STag_Icu_TAUDUnitOsRegs
{
  uint16 volatile usTAUDnTPS;
  uint16 volatile usReserved1;
  uint8 volatile ucTAUDnBRS;
  uint8 volatile aaReserved2[ICU_THREE];
  uint16 volatile usTAUDnTOM;
  uint16 volatile usReserved3;
  uint16 volatile usTAUDnTOC;
  uint16 volatile usReserved4;
  uint16 volatile usTAUDnTDE;
  uint16 volatile usReserved5;
  uint16 volatile usTAUDnTDM;
  uint16 volatile usReserved6;
  uint16 volatile usTAUDnTRE;
  uint16 volatile usReserved7;
  uint16 volatile usTAUDnTRC;
  uint16 volatile usReserved8;
  uint16 volatile usTAUDnRDE;
  uint16 volatile usReserved9;
  uint16 volatile usTAUDnRDM;
  uint16 volatile usReserved10;
  uint16 volatile usTAUDnRDS;
  uint16 volatile usReserved11;
  uint16 volatile usTAUDnRDC;
} Icu_TAUDUnitOsRegs;

/***********************************************************************************************************************
**                       Data structure for Timer Array Units D channel user control registers                        **
***********************************************************************************************************************/
typedef struct STag_Icu_TAUDChannelUserRegs
{
  uint16 volatile usTAUDnCDRm;
  uint16 volatile aaReserved1[ICU_SIXTY_THREE];
  uint16 volatile usTAUDnCNTm;
  uint16 volatile aaReserved2[ICU_THIRTY_ONE];
  uint8 volatile ucTAUDnCMURm;
  uint8 volatile ucReserved3;
  uint16 volatile aaReserved4[ICU_SIXTY_THREE];
  uint8 volatile ucTAUDnCSRm;
  uint8 volatile ucReserved5;
  uint16 volatile aaReserved6[ICU_THIRTY_ONE];
  uint8 volatile ucTAUDnCSCm;
} Icu_TAUDChannelUserRegs;
#endif /* End of (ICU_TAUD_UNIT_USED == STD_ON) */

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/

#endif /* ICU_TAUD_PBTYPES_H  */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
