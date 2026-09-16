/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2X MCAL Components                                                                 */
/* Module       = Ocu_TAU_PBTypes.h                                                                                   */
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
 *  1.1.1  30/08/2024  : As part of Multi Variant support, following changes are made:
                         1. Remove definition of struct name Ocu_GaaTAUUnitConfig, Ocu_GaaTAUChannelData
 *  1.0.1  23/10/2023  : Change from OCU_AR_RELEASE_MAJOR_VERSION_VALUE to OCU_AR_RELEASE_MAJOR_VERSION
                         Change from OCU_AR_RELEASE_MINOR_VERSION_VALUE to OCU_AR_RELEASE_MINOR_VERSION
                         Change from OCU_AR_RELEASE_REVISION_VERSION_VALUE to OCU_AR_RELEASE_REVISION_VERSION
           17/10/2023  : Add new QAC message 1534 and 1536
           25/09/2023  : Update OCU_START_SEC_CONFIG_DATA_UNSPECIFIED to 
                         OCU_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
                         Reason: AR21-11 to AR22-11 memory mapping update
 *  1.0.0  04/04/2023  : Initial Version
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

#ifndef OCU_TAU_PBTYPES_H
#define OCU_TAU_PBTYPES_H

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
#define OCU_TAU_PBTYPES_AR_RELEASE_MAJOR_VERSION    OCU_AR_RELEASE_MAJOR_VERSION
#define OCU_TAU_PBTYPES_AR_RELEASE_MINOR_VERSION    OCU_AR_RELEASE_MINOR_VERSION
#define OCU_TAU_PBTYPES_AR_RELEASE_REVISION_VERSION OCU_AR_RELEASE_REVISION_VERSION
/* File version information */
#define OCU_TAU_PBTYPES_SW_MAJOR_VERSION            OCU_SW_MAJOR_VERSION
#define OCU_TAU_PBTYPES_SW_MINOR_VERSION            OCU_SW_MINOR_VERSION
#define OCU_TAU_PBTYPES_SW_PATCH_VERSION            OCU_SW_PATCH_VERSION

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                     Structure for TAU Unit configuration type                                      **
***********************************************************************************************************************/
typedef struct STag_Ocu_TAUUnitConfigType                                                                               /* PRQA S 3630 # JV-01 */
{
  /* Pointer to base address of TAU Channel Mode User register */
  P2VAR(void, TYPEDEF, REGSPACE) pTAUUnitUserCntlRegs;
  /* Pointer to base address of TAU Channel Mode OS register */
  P2VAR(void, TYPEDEF, REGSPACE) pTAUUnitOsCntlRegs;
  /* Type of OCU timer (TAUD/TAUJ) */
  uint8 ucTimerType;
  /* TAU Unit pre scaler for clock sources CK0, CK1, CK2 and CK3 and the baudrate value */
  #if ((OCU_TAUD_CONFIG_PRESCALER_SUPPORTED == STD_ON) || (OCU_TAUJ_CONFIG_PRESCALER_SUPPORTED == STD_ON))
  uint16 usPrescaler;
  /* TAU Unit baud rate value */
  uint8 ucBaudRate;
  #endif
} Ocu_TAUUnitConfigType;

/***********************************************************************************************************************
**                                         Structure for channel information                                          **
***********************************************************************************************************************/
typedef struct STag_Ocu_TAUChannelConfigType
{
  /* Pointer to base address of channel user control TAU#nCDRm register */
  P2VAR(void, TYPEDEF, REGSPACE) pCDRReg;
  /* Pointer to base address of channel user control TAU#nCDR(m-1) register */
  P2VAR(void, TYPEDEF, REGSPACE) pMasterCDRReg;
  /* Pointer to base address of channel TAU#nCMORm register */
  P2VAR(void, TYPEDEF, REGSPACE) pCMORReg;
  /* Pointer to base address of channel TAU#nCMOR(m-1) register */
  P2VAR(void, TYPEDEF, REGSPACE) pMasterCMORReg;
  /* Individual channel bit assigned value - slave only */
  uint16 usChannelBitValue;
  /* Value of clock selection bit 15 to 12 for both master and slave channel */
  uint16 usClockSelection;
  /* TAUD3 interrupt number selection */
  #if (OCU_TAUD3_UNIT_USED == STD_ON)
  /* Pointer to base address of TAUD3INTNOSELx register */
  P2VAR(volatile uint32, TYPEDEF, REGSPACE) pTAUD3INTNOSELxReg;
  /* Mask value for channels in TAUD3 configured to support selection interrupt number */
  uint32 ulTAUD3SelectInterruptMask;
  #endif
} Ocu_TAUChannelConfigType;

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/

#endif /* OCU_TAU_PBTYPES_H */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
