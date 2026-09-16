/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = App_ADC_Common_Sample_1.h                                                                           */
/*====================================================================================================================*/
/*                                  COPYRIGHT                                                                         */
/*====================================================================================================================*/
/* (c) 2019-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains sample application for ADC Driver Component                                                     */
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
**                                                 Revision Control History                                           **
***********************************************************************************************************************/
/*
 * 2.5.1:  30/06/2025    : Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.03 release
 *                         Remove SW-VERSION in file header
 * 2.5.0:  30/06/2025    : Update SW-VERSION for RH850/Ver22.01.00 (D) U2Ax release
 * 2.3.1:  04/04/2025    : As part of ARDAACL-54066, following changes are made:
 *                         1. Define ADC_WORD_ZERO
 *         28/02/2025    : Update SW-VERSION for Ver22.00.02 U2Ax Beta 1 Release
 * 2.3.0:  28/02/2025    : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024    : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 * 2.1.3:  31/10/2024    : Update SW-VERSION 2.1.3
 * 2.1.2:  30/09/2024    : Update SW-VERSION 2.1.2
 * 1.4.3:  27/05/2022    : Modify the format to 120 characters.
 * 1.2.0:  14/07/2020    : Release
 * 1.1.0:  19/06/2020    : Release
 * 1.0.0:  27/02/2019    : Initial Version
 */
/**********************************************************************************************************************/
#ifndef APP_ADC_COMMON_SAMPLE_1_H
#define APP_ADC_COMMON_SAMPLE_1_H

#define TEST_ADC_NUMB_CHNL_G0_1        4
#define TEST_ADC_NUMB_CHNL_G1_1        4
#define TEST_ADC_NUMB_CHNL_G2_1        4
#define TEST_ADC_NUMB_CHNL_G3_1        4
#define TEST_ADC_NUMB_SAMPLE_G0_1      1
#define TEST_ADC_NUMB_SAMPLE_G1_1      4
#define TEST_ADC_NUMB_SAMPLE_G2_1      1
#define TEST_ADC_NUMB_SAMPLE_G3_1      1
#define ADC_WORD_ZERO                  (uint16)0x0000U

/***********************************************************************************************************************
**                      Global Symbols                                                                                **
***********************************************************************************************************************/
#define Adc_AdcGroup_100        AdcConf_AdcGroup_AdcGroup_100
#define Adc_AdcGroup_101        AdcConf_AdcGroup_AdcGroup_101
#define Adc_AdcGroup_102        AdcConf_AdcGroup_AdcGroup_102
#define Adc_AdcGroup_103        AdcConf_AdcGroup_AdcGroup_103

/***********************************************************************************************************************
**                      Global Function Prototypes                                                                    **
***********************************************************************************************************************/
extern void Adc_Init_PE1(void);
extern void Adc_DeInit_PE1(void);

#endif /* APP_ADC_COMMON_SAMPLE_1_H */

/***********************************************************************************************************************
**                      End of File                                                                                   **
***********************************************************************************************************************/
