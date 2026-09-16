/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Adc_LLDriver.h                                                                                      */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.                                                */
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
 * 2.5.0: 30/06/2025 : Update SW-VERSION for RH850/Ver22.01.00 (D) U2Ax release
 * 2.4.0: 31/05/2025 : Update SW-VERSION for RH850/Ver21.01.01 U2Cx release
 * 2.3.1: 31/03/2025 : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 * 2.3.1: 28/02/2025 : Update SW-VERSION for Ver22.00.02 U2Ax Beta 1 Release
 * 2.3.0: 28/02/2025 : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0: 31/12/2024 : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 * 2.1.3: 31/10/2024 : Update SW-VERSION 2.1.3
 * 2.1.2: 30/09/2024 : Update SW-VERSION 2.1.2
 * 2.0.0: 28/08/2023 : Removed Multi-Instance define. Change Adc_Mapping.h to Adc_Memmap.h
 * 1.4.4: 15/07/2022 : Removed the prototype of Adc_SetStatus.
 *        12/07/2022 : Changed the return type of Adc_HwStopGroupConversion to void.
 * 1.4.1: 24/11/2021 : Added instance 4 to the suppression of duplicate inclusion.
 * 1.3.2: 06/09/2021 : Update header file macro to call file multiple times.
 *        03/09/2021 : Added a compile switch to the prototype declaration of Adc_PollingReadGroup.
 * 1.3.1: 08/07/2021 : Removed argument LucChannelCount of function Adc_PollingReadGroup.
 *        07/07/2021 : Changed comment format to 120 columns
 *        24/05/2021 : Added "extern" to external functions.
 *                     Moved the function declaration of the internal function from the header to the source code.
 *                     Change the position of an external function declaration.
 *        07/04/2021 : Changed to comply with coding rules.
 * 1.3.0: 23/12/2020 : Change return type of Adc_HwStopGroupConversion,
 *                     Adc_ChannelCompleteMode, Adc_GroupCompleteMode,
 *                     Adc_DisableHWGroup, Adc_HwStopScanGroup function to
 *                     boolean
 * 1.2.0: 14/07/2020 : Release
 *        27/07/2020 : Add QAC 9.3.1 comment.
 * 1.1.1: 02/07/2020 : - Add define for function Adc_GetLastSgConvGroup
 *                     - Remove parameter LucHwUnitIndex in function
 *                     Adc_PopFromQueue
 * 1.1.0: 19/06/2020 : Release
 * 1.0.2: 25/04/2020 : As per new requirement, remove Adc_ClearInternalBuffer().
 * 1.0.1: 09/04/2020 : Add const qualifier for arguments of internal functions
 *                     that are never changed.
 * 1.0.0: 09/01/2020 : Initial Version
 */
/**********************************************************************************************************************/
#ifndef ADC_LLDRIVER_H
#define ADC_LLDRIVER_H

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define ADC_LLDRIVER_AR_RELEASE_MAJOR_VERSION    ADC_AR_RELEASE_MAJOR_VERSION
#define ADC_LLDRIVER_AR_RELEASE_MINOR_VERSION    ADC_AR_RELEASE_MINOR_VERSION
#define ADC_LLDRIVER_AR_RELEASE_REVISION_VERSION ADC_AR_RELEASE_REVISION_VERSION

/* Module Software version information */
#define ADC_LLDRIVER_SW_MAJOR_VERSION            ADC_SW_MAJOR_VERSION
#define ADC_LLDRIVER_SW_MINOR_VERSION            ADC_SW_MINOR_VERSION

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/
#define ADC_START_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"

extern FUNC(void, ADC_PRIVATE_CODE) Adc_HwInit(void);

#if (ADC_DEINIT_API == STD_ON)
extern FUNC(void, ADC_PRIVATE_CODE) Adc_HwDeInit(void);
#endif /* (ADC_DEINIT_API == STD_ON) */

extern FUNC(void, ADC_PRIVATE_CODE) Adc_StateTransition(const Adc_GroupType LddGroup);

#if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
extern FUNC(void, ADC_PRIVATE_CODE) Adc_HwStartGroupConversion(const Adc_GroupType LddGroup);
extern FUNC(void, ADC_PRIVATE_CODE) Adc_HwStopGroupConversion(const Adc_GroupType LddGroup);
#endif /* (ADC_ENABLE_START_STOP_GROUP_API == STD_ON) */

#if (ADC_HW_TRIGGER_API == STD_ON)
extern FUNC(void, ADC_PRIVATE_CODE) Adc_HwEnableHardwareTrigger(const Adc_GroupType LddGroup);
extern FUNC(void, ADC_PRIVATE_CODE) Adc_HwDisableHardwareTrigger(const Adc_GroupType LddGroup);
#endif /* (ADC_HW_TRIGGER_API == STD_ON) */

#if (ADC_ENABLE_DISABLE_CHANNEL == STD_ON)
extern FUNC(void, ADC_PRIVATE_CODE) Adc_IntDisableEnableChannel(const Adc_GroupType LddGroup,
  const Adc_ChannelType LddChannelId, const boolean LblApiType);
#endif /* (ADC_ENABLE_DISABLE_CHANNEL == STD_ON) */

#if ((ADC_FUNCTIONALITY_MODE != ADC_INTERRUPT) && (ADC_READ_GROUP_API == STD_ON))
extern FUNC(void, ADC_PRIVATE_CODE) Adc_PollingReadGroup(const Adc_GroupType LddGroup);
#endif /* ((ADC_FUNCTIONALITY_MODE != ADC_INTERRUPT) && (ADC_READ_GROUP_API == STD_ON)) */

#define ADC_STOP_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE_FAST
#include "Adc_MemMap.h"

#if (ADC_FUNCTIONALITY_MODE != ADC_POLLING)
extern FUNC(void, ADC_CODE_FAST) Adc_Isr(const uint8 LucHwUnitIndex, const uint8 LucSgUnitIndex);
#endif /* (ADC_FUNCTIONALITY_MODE != ADC_POLLING) */

#if (ADC_ENABLE_ERR == STD_ON)
extern FUNC(void, ADC_CODE_FAST) Adc_ErrIsr(const uint8 LucHwUnitIndex);
#endif /* (ADC_ENABLE_ERR == STD_ON) */

#if (ADC_ENABLE_PARITY_ERR == STD_ON)
extern FUNC(void, ADC_CODE_FAST) Adc_ParityErrIsr(void);
#endif /* (ADC_ENABLE_PARITY_ERR == STD_ON) */

#if (ADC_ENABLE_DMA_MODE == STD_ON)
extern FUNC(void, ADC_CODE_FAST) Adc_DmaIsr(const uint8 LucHwUnitIndex, const uint8 LucSgUnitIndex);
#endif /* (ADC_ENABLE_DMA_MODE == STD_ON) */

#define ADC_STOP_SEC_CODE_FAST
#include "Adc_MemMap.h"

#endif /* ADC_LLDRIVER_HEADER */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
