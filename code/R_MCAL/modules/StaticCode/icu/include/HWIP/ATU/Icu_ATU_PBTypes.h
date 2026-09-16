/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Icu_ATU_PBTypes.h                                                                                   */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.                                                */
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
 * 2.4.1:  30/06/2025  : As part of support QAC 11.6.0, following changes are made:
 *                       1. Update QAC message and QAC header
 * 2.4.0:  30/05/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.01 Release
 * 2.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release 
 * 2.1.2:  31/10/2024  : As part of support GTM HWIP into common code, following changes are made:
 *                       1.Add precompile ICU_ATU_TIMER_UNIT_USED
 *                       2.Update pre-compile condition
 *                       As part of support Postbuild variant feature, following changes are made:
 *                       1.Remove extern generator stuct
 *                       As part of support QAC 9.5.0, following changes are made:
 *                       1. Remove redundant QAC message 3684, 1534, 1536, add QAC message 3640
 * 2.0.1:  23/10/2023  : Add QAC messages 1534, 1536. Remove QAC message 0828
 *         14/10/2023  : Change memory section ICU_START/STOP_SEC_CONFIG_DATA_UNSPECIFIED to
 *                       ICU_START/STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
 * 2.0.0:  03/08/2023  : #include "Icu_Mapping.h" update to #include "Icu_MemMap.h"
 *                       Remove all multi-instance including methods
 *                       Remove all supported multi-instance header file
 * 1.4.3:  17/04/2022  : Merge QAC message from U2Ax, E2x and U2Bx
 * 1.4.1:  18/10/2021  : Add QAC message 9.5.0
 *         05/10/2021  : Remove ICU_ATU_TIMER_IP_USED, Icu_ATUChannelRamDataType,
 *                       Icu_ATUSignalMeasurementModeRamDataType, Icu_UserModeSettingType, Icu_GaaATUChannelRamData,
 *                       Icu_GaaATUSignalMeasureRamData
 *                       Rename Icu_ATUTimerChannelConfigType to Icu_ATUChannelUserRegConfigType
 *                       Rename GaaATUTimerChannelConfig to Icu_GaaATUChannelUserRegConfig, changed its datatype as well
 *                       Re-designed Icu_ATUTimerChannelConfigType
 *                       Rename ATU5 -> ATU
 * 1.3.2:  30/08/2021  : Change from #include "Icu_MemMap.h" to #include "Icu_Mapping.h".
 *                       Update header file macro.
 * 1.3.1:  02/07/2021  : Add QAC message 9.5.0
 *                       Format source code to 120 characters
 *                       Improve Violation tag (remove START/END)
 * 1.2.0:  17/07/2020  : Release
 * 1.1.0:  19/06/2020  : Release
 * 1.0.0:  25/03/2020  : Initial Version
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

/**********************************************************************************************************************/
#ifndef ICU_ATU_PBTYPES_H
#define ICU_ATU_PBTYPES_H
/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for Macro definitions */
#include "Icu.h"

/* Included for data type declaration */
#include "rh850_Types.h"

/* Following for QAC */
/* Included for Macro definitions */

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define ICU_ATU_PBTYPES_AR_RELEASE_MAJOR_VERSION    ICU_AR_RELEASE_MAJOR_VERSION
#define ICU_ATU_PBTYPES_AR_RELEASE_MINOR_VERSION    ICU_AR_RELEASE_MINOR_VERSION
#define ICU_ATU_PBTYPES_AR_RELEASE_REVISION_VERSION ICU_AR_RELEASE_REVISION_VERSION

/* Module Software version information */
#define ICU_ATU_PBTYPES_SW_MAJOR_VERSION            ICU_SW_MAJOR_VERSION
#define ICU_ATU_PBTYPES_SW_MINOR_VERSION            ICU_SW_MINOR_VERSION

/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/
#if (ICU_ATU_TIMER_UNIT_USED == STD_ON)
/* IcuCommon prescaler status */
#define ICU_COMMON_PRESCALER_NOT_USED               0U
#define ICU_TIMER_CLK_BUS_NOT_USED                  0U
#if (ICU_ATU_TIMER_UNIT_USED == STD_ON)
#if (ICU_ATUC_NOISE_CANCELLATION_ENABLE == STD_ON)
#define ICU_NC_NCMC_MASK (uint8)0x02
#else
#define ICU_NC_NCMC_MASK (uint8)0x00
#endif
#if (ICU_ATUA_NOISE_CANCELLATION_ENABLE == STD_ON)
#define ICU_NC_NCMA_MASK (uint8)0x01
#else
#define ICU_NC_NCMA_MASK (uint8)0x00
#endif
#define ICU_NC_NCMR_MASK (ICU_NC_NCMSEL_MASK | ICU_NC_NCMC_MASK | ICU_NC_NCMA_MASK)
#endif

/***********************************************************************************************************************
**                                        Structure for ATU configuration type                                        **
***********************************************************************************************************************/
typedef struct STag_Icu_ATUConfigType
{
  #if (ICU_COMMON_PRESCALER_NOT_USED != ICU_ATU_COMMON_PRESCALER_CONFIGURED)
  /* Pointer to ICU driver Timer Common Prescaler Config */
  P2CONST(void, TYPEDEF, ICU_CONFIG_DATA) pCommonPrescalerConfig;
  #endif

  #if (ICU_TIMER_CLK_BUS_NOT_USED != ICU_TIMER_CLK_BUS_SELECTION_CONFIGURED)
  /* Pointer to ICU pTimerClock bus configuration */
  P2CONST(void, TYPEDEF, ICU_CONFIG_DATA) pTimerClkBusConfig;
  #endif

  #if ((ICU_ATUC_NOISE_CANCELLATION_ENABLE == STD_ON) || (ICU_ATUA_NOISE_CANCELLATION_ENABLE == STD_ON))
  /* Pointer to the address of Icu Noise Cancellation Configuration */
  P2CONST(void, TYPEDEF, ICU_CONFIG_DATA) pNoiseCancellationConfig;
  #endif
} Icu_ATUConfigType;
/***********************************************************************************************************************
**                                Structure for ATU Channel User Register information                                 **
***********************************************************************************************************************/
typedef struct STag_Icu_ATUChannelUserRegConfigType
{

  /* Pointer to base address of ATU Timer Control registers */
  P2VAR(void, TYPEDEF, REGSPACE) pTimerCntlRegs;

  /* For TimerA
   * Bits 13-12 : Edge selection of external input TIA6
   *              00: Input capturing is not performed.
   *              01: Captured on the rising edge.
   *              10: Captured on the falling edge.
   *              11: Captured on both edges.
   *
   * Bits 11-10 : Edge selection of external input TIA5
   *              00: Input capturing is not performed.
   *              01: Captured on the rising edge.
   *              10: Captured on the falling edge.
   *              11: Captured on both edges.
   *
   * Bits 9-8 : Edge selection of external input TIA4
   *             00: Input capturing is not performed.
   *             01: Captured on the rising edge.
   *             10: Captured on the falling edge.
   *             11: Captured on both edges.
   *
   * Bits 7-6 : Edge selection of external input TIA3
   *             00: Input capturing is not performed.
   *             01: Captured on the rising edge.
   *             10: Captured on the falling edge.
   *             11: Captured on both edges.
   *
   * Bits 5-4 : Edge selection of external input TIA2
   *             00: Input capturing is not performed.
   *             01: Captured on the rising edge.
   *             10: Captured on the falling edge.
   *             11: Captured on both edges.
   *
   * Bits 3-2 : Edge selection of external input TIA1
   *             00: Input capturing is not performed.
   *             01: Captured on the rising edge.
   *             10: Captured on the falling edge.
   *             11: Captured on both edges.
   *
   * Bits 1-0 : Edge selection of external input TIA0
   *             00: Input capturing is not performed.
   *             01: Captured on the rising edge.
   *             10: Captured on the falling edge.
   *             11: Captured on both edges.
   */
  /* For TimerC (m = 0 to 7)
   * Bits 15-12 : Edge selection of external input TICm3
   *            0100  : Input capture disabled.
   *            0101  : Capturing at the rising edge of TIOCxy.
   *            0110  : Capturing at the falling edge of TIOCxy.
   *            0111  : Capturing at the rising edge and falling edge of TIOCxy
   *
   * Bits 11-8 : Edge selection of external input TICm2
   *            0100  : Input capture disabled.
   *            0101  : Capturing at the rising edge of TIOCxy.
   *            0110  : Capturing at the falling edge of TIOCxy.
   *            0111  : Capturing at the rising edge and falling edge of TIOCxy
   *
   * Bits 7-4 : Edge selection of external input TICm1
   *            0100  : Input capture disabled.
   *            0101  : Capturing at the rising edge of TIOCxy.
   *            0110  : Capturing at the falling edge of TIOCxy.
   *            0111  : Capturing at the rising edge and falling edge of TIOCxy
   *
   * Bits 3-0 : Edge selection of external input TICm0
   *            0100  : Input capture disabled.
   *            0101  : Capturing at the rising edge of TIOCxy.
   *            0110  : Capturing at the falling edge of TIOCxy.
   *            0111  : Capturing at the rising edge and falling edge of TIOCxy
   */

  #if (ICU_ATU_TIMERC_UNIT_USED == STD_ON)
  uint16 usTSTRCValue;
  #endif
  /* Individual channel mask value for channel mode user register */
  uint16 usChannelModeUserRegSettings;
} Icu_ATUChannelUserRegConfigType;

/***********************************************************************************************************************
**                                       Structure for ICU Channel information                                        **
***********************************************************************************************************************/
typedef struct STag_Icu_ATUChannelConfigType
{
  /* void pointer to base address of channel user control register structure */
  P2VAR(void, TYPEDEF, REGSPACE) pTimerSubBlkUserRegs;
  /* void pointer to base address of channel user control register structure */
  P2VAR(void, TYPEDEF, REGSPACE) pTimerChannelUserRegs;
  /* void pointer to base address of common control register structure */
  P2VAR(void, TYPEDEF, REGSPACE) pAtuCommonCntlRegs;

  #if ((ICU_ATUA_NOISE_CANCELLATION_ENABLE == STD_ON) || (ICU_ATUC_NOISE_CANCELLATION_ENABLE == STD_ON))
  /* Enables/Disables the use of TIMERC unit Noise cancellation. */
  uint8 ucIcuEnableNoiseCancellation;
  /* Individual channel Period value */
  uint16 usIcuNoiseCancellationPeriod;
  /* Individual channel NCR register address */
  P2VAR(volatile uint16, TYPEDEF, REGSPACE) pNCRPeriodRegAdress;
  #endif /* End of ((ICU_ATUA_NOISE_CANCELLATION_ENABLE == STD_ON) || \
                              (ICU_ATUC_NOISE_CANCELLATION_ENABLE == STD_ON))*/
} Icu_ATUChannelConfigType;

/***********************************************************************************************************************
**                               Data structure for ATU Timer Common Control Registers                                **
***********************************************************************************************************************/

typedef struct STag_Icu_ATUCommonCntlRegs
{
  uint8 volatile ucAtuTimerATUENR;
  uint8 volatile ucReserved1;
  uint8 volatile ucAtuTimerCBCNT;
  uint8 volatile ucAtuTimerNCMR;

} Icu_ATUCommonCntlRegs;

/***********************************************************************************************************************
**                               Data structure for ATU Timer A channel user registers                                **
***********************************************************************************************************************/
#if (ICU_ATU_TIMERA_UNIT_USED == STD_ON)
typedef struct STag_Icu_ATUTimerACommonUserRegs
{
  uint8 volatile ucAtuTimerATCR1A;
  uint8 volatile ucReserved1;
  uint16 volatile usAtuTimerATCR2A;
  uint16 volatile usAtuTimerATCR3A;

  uint16 volatile usAtuTimerATCR4A;
  uint16 volatile usAtuTimerATSRA;
  uint16 volatile usAtuTimerATSCRA;
  uint8 volatile ucAtuTimerANCMCR1A;
  uint8 volatile ucReserved2;
  uint8 volatile ucAtuTimerANCMCR2A;
  uint8 volatile ucReserved3;
  uint16 volatile usAtuTimerATIOR1A;
  uint16 volatile usReserved4;
  uint32 volatile ulAtuTimerATIOR2A;
  uint8 volatile ucAtuTimerATILRA;
  uint8 volatile ucReserved5;
  uint16 volatile usReserved6;
  /* TCR5A */
  uint8 volatile ucAtuTimerATCR5A;
  uint8 volatile ucReserved7;
  uint16 volatile usReserved8;
  /* TCNTA 32bit */
  uint32 volatile ulAtuTimerATCNTA;
  /* TCR2AS1 */
  uint8 volatile ucAtuTimerATCR2AS1;
  uint8 volatile ucReserved9;
  /* TCR2AS2 */
  uint8 volatile ucAtuTimerATCR2AS2;
  uint8 volatile ucReserved10;
  uint32 volatile ulReserved11;
  /* TIERA */
  uint16 volatile usAtuTimerATIERA;

} Icu_ATUTimerACommonUserRegs;

typedef struct STag_Icu_ATUTimerAChannelUserRegs
{
  uint16 volatile usAtuTimerANCNTAm;
  uint16 volatile usAtuTimerANCRAm;
  uint32 volatile ulAtuTimerAICRAm;
  uint32 volatile ulAtuTimerAICRA2m;

} Icu_ATUTimerAChannelUserRegs;

#endif /* End of (ICU_ATU_TIMERA_UNIT_USED == STD_ON) */

/***********************************************************************************************************************
**                               Data structure for ATU Timer C channel user registers                                **
***********************************************************************************************************************/
#if (ICU_ATU_TIMERC_UNIT_USED == STD_ON)
typedef struct STag_Icu_ATUTimerCCommonUserRegs
{
  uint16 volatile usAtuTimerCTSTRC;
  uint16 volatile usReserved1;
  uint16 volatile usAtuTimerCNCMCR1C;
  uint16 volatile usAtuTimerCNCMCR2C;

} Icu_ATUTimerCCommonUserRegs;

typedef struct STag_Icu_ATUTimerCSubBlkUserRegs
{
  uint16 volatile usReserved1;
  uint16 volatile usAtuTimerCTSCRCm;
  uint16 volatile usAtuTimerCTCRCm;
  uint16 volatile usAtuTimerCTSRCm;
  uint16 volatile usAtuTimerCTIORCm;
  uint16 volatile aaReserved2[5];
  uint16 volatile usAtuTimerCTIERCm;
  uint16 volatile usReserved3;
  uint32 volatile ulAtuTimerCTCNTCm;
  uint32 volatile ulAtuTimerCCUCRCm;

} Icu_ATUTimerCSubBlkUserRegs;

typedef struct STag_Icu_ATUTimerCChannelUserRegs
{
  uint32 volatile ulAtuTimerCGRCmn;
  uint32 volatile aaReserved1[3]; /* GRCm1 - GRCm3 registers */
  uint32 volatile ulAtuTimerCOCRCmn;
  uint32 volatile aaReserved2[3]; /* OCRCm1 - OCRCm3 registers */
} Icu_ATUTimerCChannelUserRegs;

#endif /* End of (ICU_ATU_TIMERC_UNIT_USED == STD_ON) */

/***********************************************************************************************************************
**                                     Structure for store NCCRC register values                                      **
***********************************************************************************************************************/
#if (ICU_ATUC_NOISE_CANCELLATION_ENABLE == STD_ON)
typedef struct STag_Icu_NCCRCCntrlRegConfigType
{
  /* variable to index of SubBlock for NCCRC register */
  uint8 ucAtuNCCRCSubBlockIndex;
  /* variable to store value of NCCRC register*/
  uint8 ucAtuNCCRCCntrlRegValue;

} Icu_NCCRCCntrlRegConfigType;
#endif /* (ICU_ATUC_NOISE_CANCELLATION_ENABLE == STD_ON)*/

/***********************************************************************************************************************
**                                Structure for ATU Timer Unit Noise Cancellation type                                **
***********************************************************************************************************************/
#if ((ICU_ATUC_NOISE_CANCELLATION_ENABLE == STD_ON) || (ICU_ATUA_NOISE_CANCELLATION_ENABLE == STD_ON))
typedef struct STag_Icu_NoiseCancellationConfigType                                                                     /* PRQA S 3630 # JV-01 */
{
  /* pointer to store address of NCMR register */
  P2VAR(volatile uint8, TYPEDEF, REGSPACE) pAtuNCMRCntrlReg;
  /* variable to store value of NCMR register*/
  uint8 ucAtuNCMRCntrlRegValue;

  #if (ICU_ATUA_NOISE_CANCELLATION_ENABLE == STD_ON)
  /* pointer to store address of NCMCR1A register */
  P2VAR(volatile uint8, TYPEDEF, REGSPACE) pAtuNCMCR1ACntrlReg;
  /* variable to store value of NCMCR1A register*/
  uint8 ucAtuNCMCR1ACntrlRegValue;
  /* pointer to store address of NCMCR2A register */
  P2VAR(volatile uint8, TYPEDEF, REGSPACE) pAtuNCMCR2ACntrlReg;
  /* variable to store value of NCMCR2A register*/
  uint8 ucAtuNCMCR2ACntrlRegValue;
  /* pointer to store address of TIOR2A register */
  P2VAR(volatile uint32, TYPEDEF, REGSPACE) pAtuTIOR2ACntrlReg;
  /* variable to store value of TIOR2A register*/
  uint32 ulAtuTIOR2ACntrlRegValue;
  #endif
  #if (ICU_ATUC_NOISE_CANCELLATION_ENABLE == STD_ON)
  /* pointer to store address of NCMCR1C register */
  P2VAR(volatile uint16, TYPEDEF, REGSPACE) pAtuNCMCR1CCntrlReg;
  /* variable to store value of NCMCR1C register*/
  uint16 usAtuNCMCR1CCntrlRegValue;
  /* pointer to store address of NCMCR2C register */
  P2VAR(volatile uint16, TYPEDEF, REGSPACE) pAtuNCMCR2CCntrlReg;
  /* variable to store value of NCMCR2C register*/
  uint16 usAtuNCMCR2CCntrlRegValue;
  /* pointer to store address of NCCRC register*/
  P2VAR(volatile uint8, TYPEDEF, REGSPACE) pAtuNCCRCCntrlRegAdrs;
  /* variable to store Total TimerC Configured */
  uint8 ucTotalTimerCConfigured;
  /* Pointer to the NCCRC register Configuration */
  P2CONST(void, TYPEDEF, REGSPACE) pNCCRCCntrlRegConfig;
  #endif
} Icu_NoiseCancellationConfigType;

#endif /* ((ICU_ATUC_NOISE_CANCELLATION_ENABLE == STD_ON) || \
                              (ICU_ATUA_NOISE_CANCELLATION_ENABLE == STD_ON))*/

/***********************************************************************************************************************
**                               Structure for ICU common prescaler config information                                **
***********************************************************************************************************************/

typedef struct STag_Icu_ATU_CommonPrescalerConfigType
{
  /* Pointer to base address of common prescaler control register structure */
  P2VAR(void, TYPEDEF, REGSPACE) pATUCommonPrescalerCntlReg;

  /* ATUx Prescaler register PSCx Value */
  uint16 usAtuCommonPrescalerDivRatio;

} Icu_ATU_CommonPrescalerConfigType;

/***********************************************************************************************************************
**                                   Structure for ICU clockbus config information                                    **
***********************************************************************************************************************/

typedef struct STag_Icu_ATU_ClockBusConfigType                                                                          /* PRQA S 3630 # JV-01 */
{
  /* Pointer to base address of ATU clock bus control registers. */
  P2VAR(void, TYPEDEF, REGSPACE) pAtuClkBusCntrlRegs;

  /* Select ATU Timer Type(TIMER A or TIMER C)*/
  uint8 ucIcuUnitType;

  /* Select Prescaler clock bus line*/
  uint8 ucClkBusSelect;

} Icu_ATU_ClockBusConfigType;
#endif
/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/
#endif /* ICU_ATU_PBTYPES_H  */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
