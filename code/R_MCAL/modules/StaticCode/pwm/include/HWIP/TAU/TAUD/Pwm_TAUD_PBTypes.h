/*====================================================================================================================*/
/* Project      = RH850/X2x AR4 MCAL Development                                                                      */
/* Module       = Pwm_TAUD_PBTypes.h                                                                                  */
/*                                                                                                                    */
/*====================================================================================================================*/
/*                                                       COPYRIGHT                                                    */
/*====================================================================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains the type definitions of Post Build time Parameters                                              */
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
/*                                              Devices:        X2x                                                   */
/*====================================================================================================================*/
/***********************************************************************************************************************
**                                              Revision Control History                                              **
***********************************************************************************************************************/
/*                                                                                                                    **
 * 2.5.1: 30/06/2025 : Remove SW-VERSION in header comment                                                            **
 * 2.5.0: 30/06/2025 : Update SW-VERSION for U2Ax Ver22.01.00(D) Final Release                                        **
 * 2.4.0: 31/05/2025 : Update SW-VERSION for U2Cx Ver21.01.01 Final Release                                           **
 * 2.3.2: 29/04/2025 : Update SW-VERSION for U2Ax Ver22.00.04 Beta Release                                            **
 * 2.3.1: 31/03/2025 : Update SW-VERSION for U2BxE Ver22.00.02 Beta Release                                           **
 * 2.3.0: 28/02/2025 : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release                        **
 * 2.2.0: 31/12/2024 : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release                                  **
 * 2.1.2: 31/10/2024 : Update SW-VERSION for Ver22.01.02 U2Bx, Ver22.00.05 U2Cx Beta2 Release                         **
 * 2.1.1: 30/08/2024 : Update SW-VERSION for Ver22.01.01 U2Bx Beta Release                                            **
 *                     As part of U2C support, following changes are made                                             **
 *                     1. Remove QAC message 1534, 1535, 1536                                                         **
 * 2.0.1: 24/10/2023 : Add QAC message 1534, 1535, 1536                                                               **
 *        14/10/2023 : Change PWM_START/STOP_SEC_CONFIG_DATA_UNSPECIFIED to                                           **
 *                     PWM_START/STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED                                           **
 * 2.0.0: 05/07/2023 : Remove #ifdef PWM_INSTANCE_INDEX                                                               **
 *                     Remove message 0841                                                                            **
 * 1.4.3: 18/05/2022 : Added new macro PWM_RESET_TAUD3INTNOSEL_REG, added 2 new elements: pTAUD3INTNOSELxReg,         **
 *                     ulTAUD3InterruptSelectionMask into Pwm_TAUDChannelPropType structure                           **
 * 1.4.1: 08/10/2021 : Updated SW VERSION to 1.4.1                                                                    **
 * 1.3.2: 04/08/2021 : Format source code unified within module.                                                      **
 * 1.3.1: 02/07/2021 : Add QAC message 9.5.0                                                                          **
 *                     Format source code to 120 characters                                                           **
 *                     Improve Violation tag (remove START/END)                                                       **
 *        15/05/2021 : Fixed Coding Rule and tailor space                                                             **
 * 1.2.0: 28/07/2020 : Release                                                                                        **
 * 1.1.0: 19/06/2020 : Release                                                                                        **
 * 1.0.0: 24/03/2020 : Initial Version.                                                                               **
 *                                                                                                                    */
/**********************************************************************************************************************/


#ifndef PWM_TAUD_PBTYPES_H
#define PWM_TAUD_PBTYPES_H

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for data type unsigned integer declaration */
#include "rh850_Types.h"

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/

/* AUTOSAR release version information */
#define PWM_TAUD_PBTYPES_AR_RELEASE_MAJOR_VERSION    PWM_AR_RELEASE_MAJOR_VERSION
#define PWM_TAUD_PBTYPES_AR_RELEASE_MINOR_VERSION    PWM_AR_RELEASE_MINOR_VERSION
#define PWM_TAUD_PBTYPES_AR_RELEASE_REVISION_VERSION PWM_AR_RELEASE_REVISION_VERSION

/* Software module version information */
#define PWM_TAUD_PBTYPES_SW_MAJOR_VERSION            PWM_SW_MAJOR_VERSION
#define PWM_TAUD_PBTYPES_SW_MINOR_VERSION            PWM_SW_MINOR_VERSION
#define PWM_TAUD_PBTYPES_SW_PATCH_VERSION            PWM_SW_PATCH_VERSION

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/
#define PWM_TAUD_MIN_PERIOD_VAL                      (uint16)0x0000U
#define PWM_TAUD_MAX_PERIOD_VAL                      (uint16)0xFFFFU
/* Reset values */
#define PWM_RESET_TAUDCDR_REG                        (uint16)0x0000U
#define PWM_TAUD_MASK_16BIT_INIT                     (uint16)0x0000U
#define PWM_TAUD_RESET_16BIT_REG                     (uint16)0x0000U
#define PWM_TAUD_RESET_CMOR_REG                      (uint16)0x0000U
#define PWM_RESET_TAUD3INTNOSEL_REG                  (uint32)0x00000000U
/* set values */
#define PWM_STOP_TAUD_ALL_CH                         (uint16)0xFFFFU
#define PWM_TAUD_CMOR_MASK                           (uint16)0x3FFFU

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:3630)    : The implementation of this struct/union type should be hidden.                               */
/* Rule                : MISRA C:2012 Dir-4.8                                                                         */
/* JV-01 Justification : This is accepted. Redundant of struct or union type has no affect to driver operation.       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                     Structure for TAUD User control registers                                      **
***********************************************************************************************************************/
typedef struct STag_Pwm_TAUDUnitUserRegs                                                                                /* PRQA S 3630 # JV-01 */
{
  uint16 volatile usTAUDnTOL;
  uint16 volatile usReserved1;
  uint16 volatile usTAUDnRDT;
  uint16 volatile aaReserved2;
  uint16 volatile usTAUDnRSF;
  uint16 volatile usReserved3;
  uint16 volatile usTAUDnTRO;
  uint16 volatile usReserved4;
  uint16 volatile usTAUDnTME;
  uint16 volatile aaReserved5;
  uint16 volatile usTAUDnTDL;
  uint16 volatile aaReserved6;
  uint16 volatile usTAUDnTO;
  uint16 volatile usReserved7;
  uint16 volatile usTAUDnTOE;
  uint16 volatile aaReserved8[177];
  uint16 volatile usTAUDnTE;
  uint16 volatile usReserved9;
  uint16 volatile usTAUDnTS;
  uint16 volatile usReserved10;
  uint16 volatile usTAUDnTT;
} Pwm_TAUDUnitUserRegs;

/***********************************************************************************************************************
**                                      Structure for TAUD OS control registers                                       **
***********************************************************************************************************************/
typedef struct STag_Pwm_TAUDUnitOsRegs                                                                                  /* PRQA S 3630 # JV-01 */
{
  uint16 volatile usTAUDnTPS;
  uint16 volatile usReserved1;
  uint8 volatile ucTAUDnBRS;
  uint8 volatile aaReserved2[3];
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
} Pwm_TAUDUnitOsRegs;

/***********************************************************************************************************************
**                                 Structure for TAUD channel User control registers                                  **
***********************************************************************************************************************/
typedef struct STag_Pwm_TAUDUserRegs                                                                                    /* PRQA S 3630 # JV-01 */
{
  uint16 volatile usTAUDnCDRm;
  uint16 volatile aaReserved1[63];
  uint16 volatile usTAUDnCNTm;
  uint16 volatile aaReserved2[31];
  uint8 volatile ucTAUDnCMURm;
} Pwm_TAUDChannelUserRegs;

/***********************************************************************************************************************
**                                  Overall module TAUD configuration data structure                                  **
***********************************************************************************************************************/
typedef struct STag_Pwm_TAUDConfigType
{
  /* Pointer to PWM Driver TAUD/TAUB Unit configuration */
  P2CONST(void, TYPEDEF, PWM_CONFIG_DATA) pTAUDUnitConfig;
} Pwm_TAUDConfigType;

/***********************************************************************************************************************
**                                  Data Structure for TAUD Unit configuration type                                   **
***********************************************************************************************************************/
typedef struct STag_Pwm_TAUDUnitConfigType
{
  /* pointer to base address of TAUD Unit user control registers */
  P2VAR(volatile Pwm_TAUDUnitUserRegs, TYPEDEF, REGSPACE) pUserCntlRegs;
  /* pointer to base address of TAUD Unit OS control registers */
  P2VAR(volatile Pwm_TAUDUnitOsRegs, TYPEDEF, REGSPACE) pOsCntlRegs;
  /* Mask value for all channels in a TAUD */
  uint16 usTAUChannelMask;
  /* Mask value for the TOM register based on configuration of channels */
  uint16 usTOMMask;
  /* Mask value for the TOC register based on configuration of channels */
  uint16 usTOCMask;
  /* Mask value for the TOL register based on configuration of channels */
  uint16 usTOLMask;
  /* Mask value for the TO register based on configuration of channels */
  uint16 usTOMask;
  /* Mask value for the TOE register based on configuration of channels */
  uint16 usTOEMask;
  /* TAU Unit prescaler for clock sources CK0, CK1, CK3 and CK4 */
  #if (PWM_TAUD_PRESCALER == STD_ON)
  uint16 usPrescaler;
  /* TAU Unit baudrate value */
  uint8 ucBaudRate;
  /*
   * Prescaler shared between ICU/GPT module
   * blConfigurePrescaler = TRUE Prescaler for CK0-CK3 has to be set by PWM
   * blConfigurePrescaler = FALSE Prescaler for CK0-CK3 need not be set by PWM
   */
  boolean blConfigurePrescaler;
  #endif
  #if (PWM_SYNC_START_SUPPORT == STD_ON)
  /* Mask value for all channels in TAUD configured to support synchronous start/stop of timers */
  uint16 usSyncInitMask;
  #endif
} Pwm_TAUDUnitConfigType;

/***********************************************************************************************************************
**                                 Data Structure for TAUD Channel configuration type                                 **
***********************************************************************************************************************/
typedef struct STag_Pwm_TAUDChannelProp
{
  /* Default Period of channel in timer ticks (0 - 2^16) */
  Pwm_PeriodType ddDefaultPeriodOrDuty;
  /* Individual channel mask value */
  uint16 usChannelMask;
  /* void pointer to user base address of Timer control register */
  P2VAR(volatile Pwm_TAUDChannelUserRegs, TYPEDEF, REGSPACE) pCntlRegs;
  /* pointer to base address of CMOR register */
  P2VAR(volatile uint16, TYPEDEF, REGSPACE) pCMORReg;
  #if ((PWM_NOTIFICATION_SUPPORTED == STD_ON) || (PWM_SET_CHANNEL_OUTPUT_API == STD_ON))
  /* Pointer to base address of Timer Interrupt control register */
  P2VAR(volatile uint16, TYPEDEF, REGSPACE) pEICReg;
  #endif
  /*
   * Bit 15-14:    00: This bits are already set during initialization for
   *                   clock source
   * Bit 13-12:    00: Selects the Operation Clock
   * Bit    11:     0: The channel operates as the slave channel in the
   *                   synchronous channel operation function.
   *                1: The channel operates as the master channel in the
   *                   synchronous channel operation function.
   * Bit 10- 8:   000: Valid only in software trigger start.
   *              100: Selects the INTn output signal of the master channel
   *              101: Selects the INTn output signal of the upper channel,
   *                   regardless of the setting of the master
   * Bit  7- 6:    00: Not Used, so set to 00
   * Bit  4- 0: 00001: Interval Timer mode *a
   *            01001: One Count mode *b
   *            10101: Pulse One Count mode *b
   *(Bit 0: *a: Outputs INTn (timer interrupt) at the start of count operation.
   *        *b: Enables start trigger detected during count operation)
   */
  uint16 usCMORRegSettingsMask;
  /* Specific for TAUD3 channels only*/
  #if (STD_ON == PWM_TAUD3_UNIT_USED)
  /* Pointer to base address of TAUD3 Interrupt Number Select Register0/1 */
  P2VAR(volatile uint32, TYPEDEF, REGSPACE) pTAUD3INTNOSELxReg;
  /* Setting bit value for TAUD3 Interrupt Number Select Register0/1 */
  uint32 ulTAUD3InterruptSelectionMask;
  #endif
} Pwm_TAUDChannelPropType;

/***********************************************************************************************************************
**                                           Global configuration constants                                           **
***********************************************************************************************************************/
#define PWM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Pwm_MemMap.h"

/* Array of structures for TAUD Unit Channel Configuration */
extern CONST(Pwm_TAUDUnitConfigType, PWM_CONST) Pwm_GaaTAUDUnitConfig[PWM_TOTAL_TAUD_UNITS_CONFIG];

#define PWM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Pwm_MemMap.h"

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/

#endif /* PWM_TAUD_PBTYPES_H */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
