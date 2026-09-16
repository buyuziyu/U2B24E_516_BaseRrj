/*====================================================================================================================*/
/* Project      = RH850/X2x AR4 MCAL Development                                                                      */
/* Module       = Pwm_TAU_PBTypes.h                                                                                   */
/*                                                                                                                    */
/*====================================================================================================================*/
/*                                                       COPYRIGHT                                                    */
/*====================================================================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains macros and structure data types for post build                                                  */
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
 *                     2. Remove redundant QAC message                                                                **
 * 2.0.1: 21/10/2023 : Follow rule QAC 10.3.0, add new QAC message 1534, 1536, 1535                                   **
 * 2.0.0: 05/07/2023 : Remove #ifdef PWM_INSTANCE_INDEX. Remove message 0841                                          **
 * 1.4.4: 13/07/2022 : Removed QAC message 0883                                                                       **
 * 1.4.1: 21/11/2021 : Update QAC message for U2Bx                                                                    **
 * 1.3.2: 04/08/2021 : Device specific implementation moved from Pwm common file.                                     **
 *                     Format source code unified within module.                                                      **
 * 1.3.1: 02/07/2021 : Format source code to 120 characters                                                           **
 *        19/05/2021 : Removed ucPwmTauType from Pwm_TAUChannelConfigType                                             **
 *        15/05/2021 : Fixed Coding Rule and tailor space                                                             **
 * 1.2.0: 28/07/2020 : Release                                                                                        **
 * 1.1.0: 19/06/2020 : Release                                                                                        **
 * 1.0.1: 19/05/2020 : Changed "uinteger uiPwmTAUType;"                                                               **
 *                                 to "uint8 ucPwmTAUType;"                                                           **
 * 1.0.0: 24/03/2020 : Initial Version.                                                                               **
 *                                                                                                                    */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/

#ifndef PWM_TAU_PBTYPES_H
#define PWM_TAU_PBTYPES_H
/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for data type uinteger declaration */
#include "rh850_Types.h"

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR Release version information */
#define PWM_TAU_PBTYPES_AR_RELEASE_MAJOR_VERSION    PWM_AR_RELEASE_MAJOR_VERSION
#define PWM_TAU_PBTYPES_AR_RELEASE_MINOR_VERSION    PWM_AR_RELEASE_MINOR_VERSION
#define PWM_TAU_PBTYPES_AR_RELEASE_REVISION_VERSION PWM_AR_RELEASE_REVISION_VERSION

/* File version information */
#define PWM_TAU_PBTYPES_SW_MAJOR_VERSION            PWM_SW_MAJOR_VERSION
#define PWM_TAU_PBTYPES_SW_MINOR_VERSION            PWM_SW_MINOR_VERSION

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/
/* Shift value */
#define PWM_CKS_BITS_POSITION                      (uint16)0x000EU
/* Flags which use SelectChannelClk function */
#define PWM_STOPPED_CH                             (uint8)0x01U
#define PWM_NOTSTARTED_CH                          (uint8)0x00U
/***********************************************************************************************************************
**                                     Structure for TAU Unit configuration type                                      **
***********************************************************************************************************************/
/***********************************************************************************************************************
**                                    Data structure for PWM channel configuration                                    **
***********************************************************************************************************************/
typedef struct STag_Pwm_TAUChannelConfigType
{
  /* Offset with respect to base Timer control register of the master channel of corresponding channel */
  uint8 ucMasterOffset;
  /* Timer Unit Index in the Array Pwm_GaaTAUDUnitConfig / Pwm_GaaTAUJUnitConfig based on the channel belongs to
   * TAUD or TAUJ */
  uint8 ucTimerUnitIndex;
  /*
   * ucTimerMode = true means channel acts as master channel
   * ucTimerMode = false means channel acts as slave channel
   */
  uint8 ucTimerMode;
  #if (PWM_SYNC_START_SUPPORT == STD_ON)
  /*
   * blComplexDriverInit = true means channel will be used by complex driver
   * blComplexDriverInit = false means channel will be used by PWM driver
   */
  boolean blComplexDriverInit;
  #endif
} Pwm_TAUChannelConfigType;

#endif /* PWM_TAU_PBTYPES_H */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
