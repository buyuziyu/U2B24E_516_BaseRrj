/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Icu_TAU_PBTypes.h                                                                                   */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains macros and structure data types for post build parameters of TAU Timer IP                       */
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
 * 2.3.0:  28/02/2025  : As part of ARDAACL-52090, following changes are made:
 *                       1. Update struct type Icu_TAUUnitConfigType
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 * 2.1.2:  31/10/2024  : Update SW-VERSION for Ver22.01.02 Beta2 Release 
 *                       As part of support GTM HWIP into common code, following changes are made:
 *                       1.Update pre-compile condition
 *                       As part of support QAC 9.5.0, following changes are made:
 *                       1.Remove redundant QAC message 3684 add 3630
 *                       2.Remove QAC messages 1534, 1535, 1536.
 * 2.0.1:  19/10/2023  : Add QAC messages 1534, 1535, 1536
 *         14/10/2023  : Change memory section ICU_START/STOP_SEC_CONFIG_DATA_UNSPECIFIED to
 *                       ICU_START/STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
 * 2.0.0:  03/08/2023  : #include "Icu_Mapping.h" update to #include "Icu_MemMap.h"
 *                       Remove all multi-instance including methods
 *                       Remove all supported multi-instance header file
 * 1.4.3:  14/05/2022  : Change type of pTAUD3INTNOSELxReg from uint16 to uint32
 *                       Change ICU_TAUD3_INTERRUPT_SELECTION_USED to ICU_TAUD3_UNIT_USED
 *         17/04/2022  : Merge QAC message from U2Ax, E2x and U2Bx
 *         13/04/2022  : Update struct Icu_TAUChannelConfigType, add pTAUJCNTAddress and update pCNTAddress pointer
 *                       type from uint32 to uint16
 * 1.4.1:  15/09/2021  : Rename Icu_TAUTimerChannelConfigType to Icu_TAUChannelUserRegConfigType
 *                       Rename Icu_GaaTAUTimerChannelConfig to Icu_GaaTAUChannelUserRegConfig
 *                       Remove Icu_GaaTAUChannelRamData, Icu_GaaTAUSignalMeasureRamData, Icu_UserModeSettingType,
 *                          STag_Icu_TAUChannelRamDataType, STag_Icu_TAUSignalMeasurementModeRamDataType
 * 1.3.2:  30/08/2021  : Change from #include "Icu_MemMap.h" to #include "Icu_Mapping.h".
 *                       Update header file macro.
 * 1.3.1:  02/07/2021  : Add QAC message 9.5.0
 *                       Format source code to 120 characters
 *                       Improve Violation tag (remove START/END)
 * 1.2.0:  17/07/2020  : Release
 * 1.1.0:  19/06/2020  : Release
 * 1.0.0:  25/03/2020  : Initial Version
 */
/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:3630)    : The implementation of this struct/union type should be hidden.                               */
/* Rule                : MISRA C:2012 Dir-4.8                                                                         */
/* JV-01 Justification : This is accepted. Redundant of struct or union type has no affect to driver operation.       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/**********************************************************************************************************************/
#ifndef ICU_TAU_PBTYPES_H
#define ICU_TAU_PBTYPES_H

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for Macro definitions */
#include "Icu.h"
/* Included for data type declaration */
#include "rh850_Types.h"
/* To avoid QAC error */

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/

#define ICU_TAU_FALLING_EDGE_MASK             (uint8)0x00
#define ICU_TAU_RISING_EDGE_MASK              (uint8)0x01
#define ICU_TAU_BOTH_EDGES_MASK               (uint8)0x02

/***********************************************************************************************************************
**                                     Structure for TAU Unit configuration type                                      **
***********************************************************************************************************************/
typedef struct STag_Icu_TAUUnitConfigType                                                                               /* PRQA S 3630 # JV-01 */
{
  /* void pointer to base address of Timer Array Unit user control register */
  P2VAR(volatile uint8, TYPEDEF, REGSPACE) pTAUnitUserCntlRegs;
  /* void pointer to base address of Timer Array Unit os control register */
  P2VAR(volatile uint8, TYPEDEF, REGSPACE) pTAUnitOsCntlRegs;

  #if (ICU_PRESCALER_CONFIGURED == STD_ON)
  /* TAU Unit prescaler for clock sources CK0, CK1, CK2, CK3 */
  uint16 usPrescaler;
  #endif
  /* TAUnit type
   * ICU_HW_TAUD - 1
   * ICU_HW_TAUJ - 2
   */
  uint8 ucIcuUnitType;
  /* Mask value for all channels in a TAU */
  uint16 usTAUChannelMaskValue;

  /* TAU Unit baudrate value for CK3 */
  #if (ICU_PRESCALER_CONFIGURED == STD_ON)
  uint8 ucBaudRate;

  /* Prescaler shared between PWM/GPT/ICU/ICU modules
   * 1: Prescaler for CK0 - CK3 has to be set by ICU
   * 0: Prescaler for CK0 - CK3 need not be set by ICU
   */
  uint8 ucConfigurePrescaler;
  #endif

  #if (ICU_TAUDN_USE_PREVIOUS_INPUT == STD_ON)
  /* PIC1TAUDnSEL register address */
  P2VAR(volatile uint32, TYPEDEF, REGSPACE) pPic1TaudnSelRegs;
  /* PIC1TAUDnSEL register value */
  uint32 ulPic1TaudnSelVal;
  #endif
  #if (ICU_TAUD2_USE_PREVIOUS_INPUT == STD_ON)
  /* PIC1TAUDnSEL register address */
  P2VAR(volatile uint16, TYPEDEF, REGSPACE) pPic1Taud2SelRegs;
  /* PIC1TAUDnSEL register value */
  uint16 usPic1Taud2SelVal;
  #endif
} Icu_TAUUnitConfigType;

/***********************************************************************************************************************
**                                Structure for ICU Channel User Register information                                 **
***********************************************************************************************************************/
typedef struct STag_Icu_TAUChannelUserRegConfigType
{
  /* pointer to base address of CMOR register */
  P2VAR(volatile uint16, TYPEDEF, REGSPACE) pCMORReg;
  /*
   * Bits 15-14: 00: Selects the operation clock CK0
   *             01: Selects the operation clock CK1
   *             10: Selects the operation clock CK2
   *             11: Selects the operation clock CK3
   *
   * Bits 13-12: 00: Selects the prescaler output signal (ICU_MODE_SIGNAL_MEASUREMENT) / (ICU_MODE_TIMESTAMP)
   *             01: Selects TINn input valid edge detection signal (ICU_MODE_EDGE_COUNTER)
   *
   * Bit 11    :  0: Independent Channel operation functions
   *
   * Bits 10-8 : 000: Selects software start trigger (ICU_MODE_EDGE_COUNTER)
   *             001: Selects the TINn input valid edge detection signal (ICU_MODE_SIGNAL_MEASUREMENT)(ICU_PERIOD_TIME)
   *                  / (ICU_MODE_TIMESTAMP)
   *
   *             010: Selects the TINn input valid edge detection signal as the start signal and the reverse edge 
   *                  detection signal as the stop signal. (ICU_MODE_SIGNAL_MEASUREMENT)(ICU_HIGH_TIME, ICU_LOW_TIME)
   *
   * Bits 7-6  :  00: Not used  (ICU_MODE_EDGE_COUNTER)
   *
   *              01: Sets OVF when the counter reaches FFFFH, clears OVF when CSCn:CLOV = 1
   *                  Captures the counter value upon detection of a TINn input valid edge.
   *                  (ICU_MODE_SIGNAL_MEASUREMENT) (ICU_PERIOD_TIME)
   *                  (ICU_HIGH_TIME, ICU_LOW_TIME), (ICU_MODE_TIMESTAMP)
   *
   * Bits 4-1  :0010: Sets the Capture mode.
   *                   (ICU_MODE_SIGNAL_MEASUREMENT) (ICU_PERIOD_TIME)
   *
   *            0011: Event Count Mode (ICU_MODE_EDGE_COUNTER)
   *
   *            0110: Sets the Capture & One Count mode (ICU_MODE_SIGNAL_MEASUREMENT)(ICU_HIGH_TIME, ICU_LOW_TIME)
   *
   *            1011: Sets the Count Capture mode (ICU_MODE_TIMESTAMP)
   *
   * Bit 0     :  0: Neither output INTn nor toggles TOUTn at operation startup
   *              1: Outputs INTn at operation startup
   */
  uint16 usChannelModeOSRegSettings;
  /* Individual channel mask value for channel mode user register */
  uint8 ucChannelModeUserRegSettings;
  /* Index of Timer Unit in the Array Icu_GaaTAUUnitConfig */
  uint8 ucTimerUnitIndex;
  /* TAUD3 interrupt selection */
  #if (ICU_TAUD3_UNIT_USED == STD_ON)
  /* Pointer to base address of TAUD3INTNOSELx register */
  P2VAR(volatile uint32, TYPEDEF, REGSPACE) pTAUD3INTNOSELxReg;
  /* Mask value for channel in TAUD3 configured to support selection interrupt number */
  uint32 ulTAUD3SelectInterruptMask;
  #endif
} Icu_TAUChannelUserRegConfigType;

/***********************************************************************************************************************
**                                       Structure for TAU Channel information                                        **
***********************************************************************************************************************/
typedef struct STag_Icu_TAUChannelConfigType
{
  #if (ICU_GET_TAU_COUNT_VALUE_API == STD_ON)
  /* Pointer to base address of channel Counter register "TAUJnCNTm" */
  P2VAR(volatile uint32, TYPEDEF, REGSPACE) pTAUJCNTAddress;
  /* Pointer to base address of channel Counter register "TAUDnCNTm" */
  P2VAR(volatile uint16, TYPEDEF, REGSPACE) pCNTAddress;
  #else
  uint8 ucDummy;
  #endif
} Icu_TAUChannelConfigType;

/***********************************************************************************************************************
**                                           Global configuration constants                                           **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/

#endif /* ICU_TAU_PBTYPES_H  */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
