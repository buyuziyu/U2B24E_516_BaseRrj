/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Adc_ADCK_LLDriver.h                                                                                 */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2021-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Private functions declarations.                                                                                    */
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
 * 2.5.1: 30/06/2025 : Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.03 release
 *                     Remove SW-VERSION in file header
 * 2.4.0: 31/05/2025 : Update SW-VERSION for RH850/Ver22.01.02 U2Cx release
 * 2.3.1: 31/03/2025 : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 * 2.3.0: 28/02/2025 : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0: 31/12/2024 : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 * 2.1.3: 31/10/2024 : Update SW-VERSION 2.1.3
 * 2.1.2: 30/09/2024 : Update SW-VERSION 2.1.2
 * 2.1.1: 30/08/2024 : As part of U2Bx-E support, following changes are made:
 *                     1.Add macro ADC_TRACKHOLD_CHANNEL_SELECT_OFF
 *                     As part of U2Cx support, following changes are made:
 *                     1.Add declaration internal functions for PWM-Diag feature
 * 2.0.0: 28/08/2023 : Removed Multi-Instance define. Change Adc_Mapping.h to Adc_Memmap.h
 * 1.4.3: 11/05/2022 : Removed prototype declarations for functions changed to STATIC.
 * 1.4.1: 24/11/2021 : Initial Version
 */
/**********************************************************************************************************************/
#ifndef ADC_ADCK_LLDRIVER_H
#define ADC_ADCK_LLDRIVER_H

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define ADC_ADCK_LLDRIVER_AR_RELEASE_MAJOR_VERSION    ADC_AR_RELEASE_MAJOR_VERSION
#define ADC_ADCK_LLDRIVER_AR_RELEASE_MINOR_VERSION    ADC_AR_RELEASE_MINOR_VERSION
#define ADC_ADCK_LLDRIVER_AR_RELEASE_REVISION_VERSION ADC_AR_RELEASE_REVISION_VERSION

/* Module Software version information */
#define ADC_ADCK_LLDRIVER_SW_MAJOR_VERSION            ADC_SW_MAJOR_VERSION
#define ADC_ADCK_LLDRIVER_SW_MINOR_VERSION            ADC_SW_MINOR_VERSION

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/
/* Each flag disable functionality in T&H Channel Select function */
#define ADC_TRACKHOLD_CHANNEL_SELECT_OFF           (uint8)0xFFU
/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/
#define ADC_START_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"

extern FUNC(void, ADC_PRIVATE_CODE) Adc_AdcInit(const uint8 LucHwUnitIndex);
#if (ADC_DEINIT_API == STD_ON)
extern FUNC(void, ADC_PRIVATE_CODE) Adc_AdcDeInit(const uint8 LucHwUnitIndex);
#endif /* (ADC_DEINIT_API == STD_ON) */

#if (ADC_TRACK_AND_HOLD == STD_ON)
extern FUNC(void, ADC_PRIVATE_CODE) Adc_TrackHoldEnable(const Adc_GroupType LddGroup);
extern FUNC(void, ADC_PRIVATE_CODE) Adc_TrackHoldDisable(const Adc_GroupType LddGroup);
#endif /* (ADC_TRACK_AND_HOLD == STD_ON) */

#if (ADC_ENABLE_PARITY_ERR_INT == STD_ON)
extern FUNC(void, ADC_PRIVATE_CODE) Adc_EcmErrorInterrupt(const boolean LblEnableInterrupt);
#endif /* (ADC_ENABLE_PARITY_ERR_INT == STD_ON) */

#if (ADC_ENABLE_PWM_DIAG == STD_ON)
extern FUNC(void, ADC_PRIVATE_CODE) Adc_PwmDiagEnable(const Adc_GroupType LddGroup);
extern FUNC(boolean, ADC_PRIVATE_CODE) Adc_PwmDiagDisable(const Adc_GroupType LddGroup);
extern FUNC(uint32, ADC_PRIVATE_CODE) Adc_PwmDiagReadData(const Adc_GroupType LddGroup);
#endif /* (ADC_ENABLE_PWM_DIAG == STD_ON) */

#define ADC_STOP_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"

#endif /* ADC_ADCK_LLDRIVER_H */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
