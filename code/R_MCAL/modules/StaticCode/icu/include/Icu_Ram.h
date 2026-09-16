/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Icu_Ram.h                                                                                           */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains Global variable declarations of ICU Driver                                                      */
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
 * 2.1.2:  31/10/2024  : As part of support GTM HWIP into common code, following changes are made:
 *                       1. Add include GTM header
 *                       As part of support QAC 9.5.0, following changes are made:
 *                       1. Update QAC message and QAC header 
 *                       As part of support multi core multi postbuid variant, following changes are made:
 *                       1. Add Global variable Icu_GucKernalCoreId
 * 2.0.1:  25/10/2023  : Update SW-VERSION to 2.0.1
 * 2.0.0:  03/08/2023  : #include "Icu_Mapping.h" update to #include "Icu_MemMap.h" 
 *                       Remove all multi-instance including methods
 *                       Remove all supported multi-instance header file
 * 1.4.4:  25/06/2022  : Change memory mapping of Icu_GaaHwDepFunc[]
 * 1.4.3:  17/04/2022  : Merge QAC message from U2Ax, E2x and U2Bx
 * 1.4.1:  18/10/2021  : Add QAC message 9.5.0
 *         15/09/2021  : Update Include Section.
 *                       Rename GpTimerChannelConfig to GpChannelUserRegConfig
 *                       Define Icu_GpChannelRamData, Icu_GpSignalMeasurementData 
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

/**********************************************************************************************************************/
#ifndef ICU_RAM_H
#define ICU_RAM_H
/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Include type definition */
#include "Icu_PBTypes.h"
#if (ICU_TAU_UNIT_USED == STD_ON)
#include "Icu_TAU_Ram.h"
#endif
#if (ICU_ATU_TIMER_UNIT_USED == STD_ON)
#include "Icu_ATU_Ram.h"
#endif
#if ((ICU_IRQ_EDGE_DETECT == STD_ON) || (ICU_INTP_EDGE_DETECT == STD_ON))
#include "Icu_PIN_Ram.h"
#endif
#if (ICU_GTM_TIMER_UNIT_USED == STD_ON)
#include "Icu_GTM_Ram.h"
#endif
/* Include the Timer configuration file */
/* Included for declaration of the Low Level Driver function */
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define ICU_RAM_AR_RELEASE_MAJOR_VERSION    ICU_AR_RELEASE_MAJOR_VERSION
#define ICU_RAM_AR_RELEASE_MINOR_VERSION    ICU_AR_RELEASE_MINOR_VERSION
#define ICU_RAM_AR_RELEASE_REVISION_VERSION ICU_AR_RELEASE_REVISION_VERSION

/* Module Software version information */
#define ICU_RAM_SW_MAJOR_VERSION            ICU_SW_MAJOR_VERSION
#define ICU_RAM_SW_MINOR_VERSION            ICU_SW_MINOR_VERSION

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/

#define ICU_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Icu_MemMap.h"
/* Holds the status of ICU Driver Component */
extern VAR(Icu_ModeType, ICU_VAR_NO_INIT) Icu_GenModuleMode;
#define ICU_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Icu_MemMap.h"

#define ICU_START_SEC_VAR_NO_INIT_PTR
#include "Icu_MemMap.h"
/* Global pointer variable for channel configuration */
extern P2CONST(Icu_ChannelConfigType, ICU_VAR_NO_INIT, ICU_CONFIG_DATA) volatile Icu_GpChannelConfig;
/* Global pointer variable for channel user register configuration */
extern P2CONST(Icu_ChannelUserRegConfigType, ICU_VAR_NO_INIT, ICU_CONFIG_DATA) volatile Icu_GpChannelUserRegConfig;

/* Global pointer to the address of Channel RAM data */
extern P2VAR(volatile Icu_ChannelRamDataType, ICU_VAR_NO_INIT, ICU_CONFIG_DATA) volatile Icu_GpChannelRamData;

/* Global pointer to the address of Edge Count RAM data */
extern P2VAR(volatile Icu_EdgeCountModeRamDatatype, ICU_VAR_NO_INIT, ICU_CONFIG_DATA) volatile Icu_GpEdgeCountData;

/* Global pointer variable for Timestamp channel RAM data */
extern P2VAR(volatile Icu_TimeStampChannelRamDataType, ICU_VAR_NO_INIT, ICU_CONFIG_DATA) volatile Icu_GpTimeStampData;

/* Global pointer to the address of Signal Measure RAM data */
extern P2VAR(volatile Icu_SignalMeasurementModeRamDataType, ICU_VAR_NO_INIT, ICU_CONFIG_DATA)
                                                                                  volatile Icu_GpSignalMeasurementData;
#define ICU_STOP_SEC_VAR_NO_INIT_PTR
#include "Icu_MemMap.h"

#define ICU_START_SEC_VAR_INIT_PTR
#include "Icu_MemMap.h"
/* Declaration for HWIP Functions */
extern P2CONST(Icu_HwFuncTableType, ICU_VAR_INIT, ICU_CONFIG_DATA) Icu_GaaHwDepFunc[ICU_SEVEN];
#define ICU_STOP_SEC_VAR_INIT_PTR
#include "Icu_MemMap.h"

#if (ICU_REPORT_WAKEUP_SOURCE == STD_ON)
#define ICU_START_SEC_VAR_NO_INIT_32
#include "Icu_MemMap.h"
/* Holds the wake up source information */
extern VAR(uint32, ICU_VAR_NO_INIT) Icu_GulWakeupSource;
#define ICU_STOP_SEC_VAR_NO_INIT_32
#include "Icu_MemMap.h"
#endif

/* Functionality related to R4.0 */
#define ICU_START_SEC_VAR_INIT_BOOLEAN
#include "Icu_MemMap.h"
/* Holds the status of Initialization */
extern VAR(volatile boolean, ICU_VAR_INIT) Icu_GblDriverStatus;
/* Functionality related to R4.0 */
#define ICU_STOP_SEC_VAR_INIT_BOOLEAN
#include "Icu_MemMap.h"

#if (ICU_MULTI_CORE_SUPPORT == STD_ON)
#define ICU_START_SEC_VAR_INIT_8
#include "Icu_MemMap.h"
/* Holds the kernal core ID in multicore */
extern uint8 Icu_GucKernalCoreId;
#define ICU_STOP_SEC_VAR_INIT_8
#include "Icu_MemMap.h"
#endif

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/

#endif /* ICU_RAM_H */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
