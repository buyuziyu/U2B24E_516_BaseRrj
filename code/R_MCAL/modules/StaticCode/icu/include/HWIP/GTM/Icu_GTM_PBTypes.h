/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Icu_GTM_PBTypes.h                                                                                   */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2024-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains macros and structure datatypes for post build parameters of ICU Driver                          */
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
 * 2.1.2:  31/10/2024  : Initial version
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
#ifndef ICU_GTM_PBTYPES_H
#define ICU_GTM_PBTYPES_H

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for Macro definitions */
#include "Icu.h"
/* Included for data type declaration */
#include "rh850_Types.h"
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
#if (ICU_GTM_TIMER_UNIT_USED == STD_ON)
/* AUTOSAR release version information */
#define ICU_GTM_PBTYPES_AR_RELEASE_MAJOR_VERSION    ICU_AR_RELEASE_MAJOR_VERSION
#define ICU_GTM_PBTYPES_AR_RELEASE_MINOR_VERSION    ICU_AR_RELEASE_MINOR_VERSION
#define ICU_GTM_PBTYPES_AR_RELEASE_REVISION_VERSION ICU_AR_RELEASE_REVISION_VERSION

/* Module Software version information */
#define ICU_GTM_PBTYPES_SW_MAJOR_VERSION            ICU_SW_MAJOR_VERSION
#define ICU_GTM_PBTYPES_SW_MINOR_VERSION            ICU_SW_MINOR_VERSION

/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                     Data structure for GTM Timer TIM registers                                     **
***********************************************************************************************************************/
typedef volatile struct STag_Icu_GtmTimerTimRegs
{
  uint32 ulGPR0Regs;
  uint32 ulGPR1Regs;
  uint32 ulCNTRegs;
  uint32 ulECNTRegs;
  uint32 ulCNTSRegs;
  uint32 ulTDUCRegs;
  uint32 ulTDUVRegs;
  uint32 ulFLTRERegs;
  uint32 ulFLTFERegs;
  uint32 ulTIMCTRLRegs;
  uint32 ulTIMECTRLRegs;
  uint32 ulIRQNOTIFYRegs;
  uint32 ulIRQENRegs;
  uint32 ulIRQFORCINTRegs;
  uint32 ulIRQMODERegs;
} Icu_GtmTimerTimRegs;

/***********************************************************************************************************************
**                                    Structure for GTM ICU Timer Channel information                                 **
***********************************************************************************************************************/
typedef struct STag_Icu_GTMChannelConfigType
{
  /* Config of TIM Ctrl register */
  uint32 ulCtrlRegsChannelSettings;
  /* Pointer to base address of channel GTM Interrupt select register */
  P2VAR(volatile uint32, TYPEDEF, REGSPACE) pGTM_IRQ_SELij;
  /* IRQ SEL Enable value */
  uint32 ulGTM_IRQ_SELijEnableValue;
  #if (ICU_GTM_TIM_FILTER_USED == STD_ON)
  /* Config of TIM ECtrl register */
  uint32 ulECtrlRegsChannelSettings;
  /* Config of TIM TIM[i]_CH[x]_FLT_RE register */
  uint32 ulFilterRisingEdgeMask;
  /* Config of TIM TIM[i]_CH[x]_FLT_FE register */
  uint32 ulFilterFallingEdgeMask;
  #endif
} Icu_GtmChannelConfigType;

/***********************************************************************************************************************
**                                   Structure for TBUn unit register configuration                                   **
***********************************************************************************************************************/
typedef struct STag_Icu_GtmTbuUnitConfigType                                                                            /* PRQA S 3630 # JV-01 */
{
  /* Register address of GTM0TBUCHENR */
  P2VAR(volatile uint32, TYPEDEF, REGSPACE) pTBUCHENRegs;
  /* Register value of GTM0TBUCHENR */
  uint32 ulTBUCHENValue;
  #if (ICU_GTM_TBU0_UNIT_CONFIGURED == STD_ON)
  /* Register address of GTM0TBU0CTRL */
  P2VAR(volatile uint32, TYPEDEF, REGSPACE) pTBU0CTRLRegs;
  /* Register value of GTM0TBU0CTRL */
  uint32 ulTBU0CTRLValue;
  #endif
  #if (ICU_GTM_TBU1_UNIT_CONFIGURED == STD_ON)
  /* Register address of GTM0TBU1CTRL */
  P2VAR(volatile uint32, TYPEDEF, REGSPACE) pTBU1CTRLRegs;
  /* Register value of GTM0TBU1CTRL */
  uint32 ulTBU1CTRLValue;
  #endif
  #if (ICU_GTM_TBU2_UNIT_CONFIGURED == STD_ON)
  /* Register address of GTM0TBU2CTRL */
  P2VAR(volatile uint32, TYPEDEF, REGSPACE) pTBU2CTRLRegs;
  /* Register value of GTM0TBU2CTRL */
  uint32 ulTBU2CTRLValue;
  #endif
} Icu_GtmTbuUnitConfigType;
/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/
#endif /* End of (ICU_GTM_TIMER_UNIT_USED == STD_ON) */
#endif /* ICU_GTM_PBTYPES_H  */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
