/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Adc_Ram.h                                                                                           */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Global variable declarations.                                                                                      */
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
 * 2.1.1: 30/08/2024 : As part of U2Bx-E support, following changes are made:
 *                     1.Add Adc_GpTnHChannelSelectValue
 *                     As part of Multi-core support, following changes are made:
 *                     1.Add global variable Adc_GucCoreIndex.
 * 2.0.0: 28/08/2023 : Removed Multi-Instance define. Change Adc_Mapping.h to Adc_Memmap.h
 * 1.4.4: 20/06/2022 : Added Adc_GpHwTriggConfig and removed Adc_GpHWGroupTrigg, Adc_GpSGGroupTrigg in U2Ax.
 * 1.4.3: 25/05/2022 : Removed unnecessary coding rule messages in header comment.
 *        15/04/2022 : Changed the pointers to the structure of HW trigger configuration for U2Bx.
 *                     Moved the volatile qualifier of pointer into argument of P2VAR macro.
 * 1.4.1: 24/11/2021 : Changed the conditions of compile switches to support ADCK.
 *                     Added instance 4 to the suppression of duplicate inclusion.
 * 1.3.2: 06/09/2021 : Update header file macro to call file multiple times.
 * 1.3.1: 12/07/2021 : Added the global variable Adc_GaaHwUnitData.
 *                     Changed the name of the global variable Adc_GpWaitTimeConfig to conform to Camel.
 *                     Removed the global variables Adc_GblDataAvailable, Adc_GblErrIntStatus.
 *                     Removed the volatile from global variables that are not changed except at initialization.
 *        07/07/2021 : Added QAC message 9.5.0
 *                     Changed comment format to 120 columns
 *                     Changed violation tag from START/END
 *        01/06/2021 : Changed to the appropriate memory classes and pointer classes.
 *        24/05/2021 : Change the position of an external function declaration.
 *        07/04/2021 : Changed to comply with coding rules.
 * 1.3.0: 06/12/2020 : Add new global variable Adc_GpTriggOutConfigRegister
 * 1.2.0: 14/07/2020 : Release
 *        27/07/2020 : Add QAC 9.3.1 comment.
 * 1.1.2: 06/07/2020 : Remove array Adc_GaaCurrentConvGroup
 * 1.1.1: 02/07/2020 : Update Adc_GddCurrentConvGroup to Adc_GaaCurrentConvGroup
 * 1.1.0: 19/06/2020 : Release
 * 1.0.0: 09/01/2020 : Initial Version
 */
/**********************************************************************************************************************/
#ifndef ADC_RAM_H
#define ADC_RAM_H

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
#include ADC_HWIP_PBTYPES_H_FILE
#include "Adc_PIC_LLDriver.h"
#include "Adc_sDMAC_LLDriver.h"
/* Included for macro definitions and structure declarations */
#include "Adc_PBTypes.h"

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define ADC_RAM_AR_RELEASE_MAJOR_VERSION    ADC_AR_RELEASE_MAJOR_VERSION
#define ADC_RAM_AR_RELEASE_MINOR_VERSION    ADC_AR_RELEASE_MINOR_VERSION
#define ADC_RAM_AR_RELEASE_REVISION_VERSION ADC_AR_RELEASE_REVISION_VERSION

/* Module Software version information */
#define ADC_RAM_SW_MAJOR_VERSION            ADC_SW_MAJOR_VERSION
#define ADC_RAM_SW_MINOR_VERSION            ADC_SW_MINOR_VERSION

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/
#define ADC_START_SEC_VAR_NO_INIT_PTR
#include "Adc_MemMap.h"

/* Global pointer variable for hardware unit configuration */
extern P2CONST(Adc_HwUnitConfigType, ADC_VAR_NO_INIT, ADC_CONFIG_DATA) Adc_GpHwUnitConfig;
/* Global pointer variable for Scan group unit configuration */
extern P2CONST(Adc_HwSgUnitType, ADC_VAR_NO_INIT, ADC_CONFIG_DATA) Adc_GpSgUnitConfig;
/* Global pointer variable for group configuration */
extern P2CONST(Adc_GroupConfigType, ADC_VAR_NO_INIT, ADC_CONFIG_DATA) Adc_GpGroupConfig;
/* Declaration for Hardware Index Mapping array */
extern P2CONST(uint8, ADC_VAR_NO_INIT, ADC_CONFIG_DATA) Adc_GpHwUnitIndex;
/* Declaration for SG unit Index Mapping array */
extern P2CONST(uint8, ADC_VAR_NO_INIT, ADC_CONFIG_DATA) Adc_GpSgUnitIndex;
/* Global pointer variable for channel to group data */
extern P2CONST(uint32, ADC_VAR_NO_INIT, ADC_CONFIG_DATA) Adc_GpChannelToGroup;
/* Global pointer variable for group RAM data */
extern P2VAR(volatile Adc_ChannelGroupRamData, ADC_VAR_NO_INIT, ADC_VAR_NO_INIT) Adc_GpGroupRamData;
/* Global pointer variable for hardware unit RAM data */
extern P2VAR(volatile Adc_SgUnitRamData, ADC_VAR_NO_INIT, ADC_VAR_NO_INIT) Adc_GpSgUnitRamData;
/* Global pointer variable for wait time config */
extern P2CONST(Adc_WaitTimeConfigType, ADC_VAR_NO_INIT, ADC_CONFIG_DATA) Adc_GpWaitTimeConfig;

#if (ADC_HW_TRIGGER_API == STD_ON)
#if ((ADC_IP_ADCJ == STD_ON) || (ADC_IP_ADCK == STD_ON))
/* Global pointer variable for HW trigger configuration */
extern P2CONST(Adc_HwTriggConfigType, ADC_VAR_NO_INIT, ADC_CONFIG_DATA) Adc_GpHwTriggConfig;
#endif /* ((ADC_IP_ADCJ == STD_ON) || (ADC_IP_ADCK == STD_ON)) */
#if (ADC_IP_ADCH == STD_ON)
/* Global pointer variable for HW group configuration */
extern P2CONST(uint32, ADC_VAR_NO_INIT, ADC_CONFIG_DATA) Adc_GpHWGroupTrigg;
/* Global pointer variable for SG group configuration */
extern P2CONST(Adc_PicConfigType, ADC_VAR_NO_INIT, ADC_CONFIG_DATA) Adc_GpSGGroupTrigg;
extern P2CONST(uint32, ADC_VAR_NO_INIT, ADC_CONFIG_DATA) Adc_GpTriggOutConfigRegister;
extern P2CONST(uint32, ADC_VAR_NO_INIT, ADC_CONFIG_DATA) Adc_GpTriggOutConfigValue;
#endif /* (ADC_IP_ADCH == STD_ON) */
#endif /* (ADC_HW_TRIGGER_API == STD_ON) */

#if (ADC_ENABLE_DMA_MODE == STD_ON)
/* Global pointer variable for HW group configuration */
extern P2CONST(Adc_DmaConfigType, ADC_VAR_NO_INIT, ADC_CONFIG_DATA) Adc_GpDmaUnitConfig;
/* Global pointer to DMA HW unit array mapping */
extern P2CONST(uint8, ADC_VAR_NO_INIT, ADC_CONFIG_DATA) Adc_GpDmaHWUnitMapping;
/* Global pointer to DMA SG unit array mapping */
extern P2CONST(uint8, ADC_VAR_NO_INIT, ADC_CONFIG_DATA) Adc_GpDmaSGUnitMapping;
#endif /* (ADC_ENABLE_DMA_MODE == STD_ON) */

#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
/* Global pointer variable for limit check enabled configuration */
extern P2CONST(Adc_LimitCheckConfigType, ADC_VAR_NO_INIT, ADC_CONFIG_DATA) Adc_GpLimitCheckRange;
#endif

#if (ADC_ENABLE_DISABLE_CHANNEL == STD_ON)
/* Global pointer variable for channel to Disable Enable data */
extern P2VAR(volatile boolean, ADC_VAR_NO_INIT, ADC_VAR_NO_INIT) Adc_GpChannelToDisableEnable;
#endif

#if (ADC_TRACK_AND_HOLD_CHANNEL_IO_SELECT == STD_ON)
/* Global pointer variable for T&H Channel Select data */
extern P2CONST(Adc_TrackHoldChannelValueType, ADC_VAR_NO_INIT, ADC_CONFIG_DATA) Adc_GpTnHChannelSelectValue;
#endif

#define ADC_STOP_SEC_VAR_NO_INIT_PTR
#include "Adc_MemMap.h"

#define ADC_START_SEC_VAR_NO_INIT_8
#include "Adc_MemMap.h"

/* Indicates max no of SW triggered groups configured */
extern VAR(uint8, ADC_VAR_NO_INIT) Adc_GucMaxSwTriggGroups;
/* Indicates total no of groups configured in the configset */
extern VAR(uint8, ADC_VAR_NO_INIT) Adc_GucNoOfGroups;
#if (ADC_MULTI_CORE_SUPPORT == STD_ON)
/* Indicates kernel core index configured in the configset */
extern VAR(uint8, ADC_VAR_NO_INIT) Adc_GucCoreIndex;
#endif /* ADC_MULTI_CORE_SUPPORT == STD_ON */

#if (ADC_ENABLE_DMA_MODE == STD_ON)
/* Indicates no of DMA channel Ids configured */
extern VAR(uint8, ADC_VAR_NO_INIT) Adc_GucMaxDmaChannels;
#endif

#define ADC_STOP_SEC_VAR_NO_INIT_8
#include "Adc_MemMap.h"

#define ADC_START_SEC_VAR_INIT_BOOLEAN
#include "Adc_MemMap.h"

/* Holds the status of Initialization */
extern volatile VAR(boolean, ADC_VAR_INIT) Adc_GblDriverStatus;

#define ADC_STOP_SEC_VAR_INIT_BOOLEAN
#include "Adc_MemMap.h"

#define ADC_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Adc_MemMap.h"

/* HW unit data */
extern volatile VAR(Adc_HwUnitDataType, ADC_VAR_NO_INIT) Adc_GaaHwUnitData[ADC_MAX_HW_UNITS];

#define ADC_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Adc_MemMap.h"

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/

#endif /* ADC_RAM_H */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
