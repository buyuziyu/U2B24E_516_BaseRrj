/*====================================================================================================================*/
/* Project      = RH850/X2x AR4 MCAL Development                                                                      */
/* Module       = Pwm_TAUJ_PBTypes.h                                                                                  */
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
 * 2.0.0: 05/07/2023 : Remove #ifdef PWM_INSTANCE_INDEX. Remove message 0841                                          **
 * 1.4.3: 18/04/2022 : Removed un-used PWM_SYNCH_TAUJ_MASK macro definition                                           **
 * 1.3.2: 04/08/2021 : Format source code unified within module.                                                      **
 * 1.3.1: 02/07/2021 : Add QAC message 9.5.0                                                                          **
 *                     Format source code to 120 characters                                                           **
 *                     Improve Violation tag (remove START/END)                                                       **
 * 1.2.0: 28/07/2020 : Release                                                                                        **
 * 1.1.0: 19/06/2020 : Release                                                                                        **
 * 1.0.0: 24/03/2020 : Initial Version.                                                                               **
 *                                                                                                                    */
/**********************************************************************************************************************/

#ifndef PWM_TAUJ_PBTYPES_H
#define PWM_TAUJ_PBTYPES_H
/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for data type unsigned integer declaration */
#include "rh850_Types.h"

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:3630)    : The implementation of this struct/union type should be hidden.                               */
/* Rule                : MISRA C:2012 Dir-4.8                                                                         */
/* JV-01 Justification : This is accepted. Redundant of struct or union type has no affect to driver operation.       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3684)    : Array declared with unknown size.                                                            */
/* Rule                : MISRA C:2012 Rule-8.11, CERTCCM ARR02                                                        */
/* JV-01 Justification : Arrays used are verified in the file which are only declarations and size is configuration   */
/*                       dependent.                                                                                   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define PWM_TAUJ_PBTYPES_AR_RELEASE_MAJOR_VERSION    PWM_AR_RELEASE_MAJOR_VERSION
#define PWM_TAUJ_PBTYPES_AR_RELEASE_MINOR_VERSION    PWM_AR_RELEASE_MINOR_VERSION
#define PWM_TAUJ_PBTYPES_AR_RELEASE_REVISION_VERSION PWM_AR_RELEASE_REVISION_VERSION
/* Software module version information */
#define PWM_TAUJ_PBTYPES_SW_MAJOR_VERSION            PWM_SW_MAJOR_VERSION
#define PWM_TAUJ_PBTYPES_SW_MINOR_VERSION            PWM_SW_MINOR_VERSION
#define PWM_TAUJ_PBTYPES_SW_PATCH_VERSION            PWM_SW_PATCH_VERSION
/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/
#define PWM_TAUJ_MIN_PERIOD_VAL                      (uint32)0x00000000UL
/* Reset values */
#define PWM_RESET_TAUJCDR_REG                        (uint32)0x00000000UL
#define PWM_TAUJ_MASK_8BIT_INIT                      (uint8)0x00U
#define PWM_TAUJ_RESET_8BIT_REG                      (uint8)0x00U
#define PWM_TAUJ_RESET_CMOR_REG                      (uint16)0x0000U
/* set values */
#define PWM_STOP_TAUJ_ALL_CH                         (uint8)0x0FU
#define PWM_TAUJ_CMOR_MASK                           (uint16)0x3FFFU

/***********************************************************************************************************************
**                                     Structure for TAUJ User control registers                                      **
***********************************************************************************************************************/
typedef struct STag_Pwm_TAUJUnitUserRegs                                                                                /* PRQA S 3630 # JV-01 */
{
  uint8 volatile ucTAUJnTE;
  uint8 volatile aaReserved1[3];
  uint8 volatile ucTAUJnTS;
  uint8 volatile aaReserved2[3];
  uint8 volatile ucTAUJnTT;
  uint8 volatile aaReserved3[3];
  uint8 volatile ucTAUJnTO;
  uint8 volatile aaReserved4[3];
  uint8 volatile ucTAUJnTOE;
  uint8 volatile aaReserved5[3];
  uint8 volatile ucTAUJnTOL;
  uint8 volatile aaReserved6[3];
  uint8 volatile ucTAUJnRDT;
  uint8 volatile aaReserved7[3];
  uint8 volatile ucTAUJnRSF;
} Pwm_TAUJUnitUserRegs;

/***********************************************************************************************************************
**                                      Structure for TAUJ OS control registers                                       **
***********************************************************************************************************************/
typedef struct STag_Pwm_TAUJUnitOsRegs                                                                                  /* PRQA S 3630 # JV-01 */
{
  uint16 volatile usTAUJnTPS;
  uint16 volatile usReserved1;
  uint8 volatile ucTAUJnBRS;
  uint8 volatile aaReserved2[3];
  uint8 volatile ucTAUJnTOM;
  uint8 volatile aaReserved3[3];
  uint8 volatile ucTAUJnTOC;
  uint8 volatile aaReserved4[3];
  uint8 volatile ucTAUJnRDE;
  uint8 volatile aaReserved5[3];
  uint8 volatile ucTAUJnRDM;
} Pwm_TAUJUnitOsRegs;

/***********************************************************************************************************************
**                                 Structure for TAUJ channel User control registers                                  **
***********************************************************************************************************************/
typedef struct STag_Pwm_TAUJUserRegs                                                                                    /* PRQA S 3630 # JV-01 */
{
  uint32 volatile ulTAUJnCDRm;
  uint32 volatile aaReserved1[3];
  uint32 volatile ulTAUJnCNTm;
  uint32 volatile aaReserved2[3];
  uint8 volatile ucTAUJnCMURm;
} Pwm_TAUJChannelUserRegs;

/***********************************************************************************************************************
**                                  Overall module TAUJ configuration data structure                                  **
***********************************************************************************************************************/
typedef struct STag_Pwm_TAUJConfigType
{
  /* Pointer to PWM Driver TAUJ Unit configuration */
  P2CONST(void, TYPEDEF, PWM_CONFIG_DATA) pTAUJUnitConfig;
} Pwm_TAUJConfigType;

/***********************************************************************************************************************
**                                  Data Structure for TAUJ Unit configuration type                                   **
***********************************************************************************************************************/
typedef struct STag_Pwm_TAUJUnitConfigType
{
  /* pointer to base address of TAUJ Unit user control registers */
  P2VAR(volatile Pwm_TAUJUnitUserRegs, TYPEDEF, REGSPACE) pUserCntlRegs;
  /* pointer to base address of TAUJ Unit os control registers */
  P2VAR(volatile Pwm_TAUJUnitOsRegs, TYPEDEF, REGSPACE) pOsCntlRegs;
  /* TAU Unit prescaler for clock sources CK0, CK1, CK3 and CK4 */
  #if (PWM_TAUJ_PRESCALER == STD_ON)
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
  /* Mask value for all channels in a TAUJ*/
  uint8 ucTAUChannelMask;
  /* Mask value for the TOM register based on configuration of channels */
  uint8 ucTOMMask;
  /* Mask value for the TOL register based on configuration of channels */
  uint8 ucTOLMask;
  /* Mask value for the TO register based on configuration of channels */
  uint8 ucTOMask;
  /* Mask value for the TOE register based on configuration of channels */
  uint8 ucTOEMask;
  #if (PWM_SYNC_START_SUPPORT == STD_ON)
  /* Mask value for all channels in TAUJ configured to support synchronous start/stop of timers */
  uint8 ucSyncInitMask;
  #endif
} Pwm_TAUJUnitConfigType;

/***********************************************************************************************************************
**                                 Data Structure for TAUJ Channel configuration type                                 **
***********************************************************************************************************************/
typedef struct STag_Pwm_TAUJChannelProp
{
  /* Default Period of channel in timer ticks (0 - 2^32) */
  Pwm_PeriodType ddDefaultPeriodOrDuty;
  /* Individual channel mask value */
  uint8 ucChannelMask;
  /* void pointer to user base address of Timer control register */
  P2VAR(volatile Pwm_TAUJChannelUserRegs, TYPEDEF, REGSPACE) pCntlRegs;
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
   * Bit  7- 6:    00: Not Used, so set to 00
   * Bit  4- 0: 00001: Interval Timer mode *a
   *            01001: One Count mode *b
   *(Bit 0: *a: Outputs INTn (timer interrupt) at the start of count operation.
   *        *b: Enables start trigger detected during count operation)
   */
  uint16 usCMORRegSettingsMask;
} Pwm_TAUJChannelPropType;

/***********************************************************************************************************************
**                                           Global configuration constants                                           **
***********************************************************************************************************************/

#define PWM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Pwm_MemMap.h"

/* Array of structures for TAUJ Unit Channel Configuration */
extern CONST(Pwm_TAUJUnitConfigType, PWM_CONST) Pwm_GaaTAUJUnitConfig[];                                                /* PRQA S 3684 # JV-01 */

#define PWM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Pwm_MemMap.h"

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/

#endif /* PWM_TAUJ_PBTYPES_H */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
