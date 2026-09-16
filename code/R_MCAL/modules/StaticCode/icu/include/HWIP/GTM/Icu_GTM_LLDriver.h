/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Icu_GTM_LLDriver.h                                                                                  */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2024-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains Low level driver function prototypes of the ICU Driver                                          */
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
 * 2.1.2:  31/10/2024  : Initial version
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
#ifndef ICU_GTM_LLDRIVER_H
#define ICU_GTM_LLDRIVER_H

/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for Icu.h inclusion and macro definitions */
#include "Icu_PBTypes.h"
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
#if (ICU_GTM_TIMER_UNIT_USED == STD_ON)
/* AUTOSAR release version information */
#define ICU_GTM_LLDRIVER_AR_RELEASE_MAJOR_VERSION    ICU_AR_RELEASE_MAJOR_VERSION
#define ICU_GTM_LLDRIVER_AR_RELEASE_MINOR_VERSION    ICU_AR_RELEASE_MINOR_VERSION
#define ICU_GTM_LLDRIVER_AR_RELEASE_REVISION_VERSION ICU_AR_RELEASE_REVISION_VERSION

/* Module Software version information */
#define ICU_GTM_LLDRIVER_SW_MAJOR_VERSION            ICU_SW_MAJOR_VERSION
#define ICU_GTM_LLDRIVER_SW_MINOR_VERSION            ICU_SW_MINOR_VERSION

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/
#define ICU_START_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"

/* The GTM Lowlayer Init function */
extern FUNC(void, ICU_PRIVATE_CODE) Icu_HW_Gtm_UnitInit(P2CONST(Icu_ConfigType, AUTOMATIC, ICU_APPL_CONST) ConfigPtr);
extern FUNC(void, ICU_PRIVATE_CODE) Icu_HW_Gtm_ChannelInit(Icu_ChannelType LddChannel);

/* The GTM Lowlayer SetActivation function */
extern FUNC(void, ICU_PRIVATE_CODE)
                          Icu_HW_Gtm_SetActivation(Icu_ChannelType LddChannel, Icu_ActivationType ActiveEdge);

#if (ICU_DE_INIT_API == STD_ON)
/* The GTM Lowlayer DeInit function */
extern FUNC(void, ICU_PRIVATE_CODE) Icu_HW_Gtm_UnitDeInit(void);
extern FUNC(void, ICU_PRIVATE_CODE) Icu_HW_Gtm_ChannelDeInit(Icu_ChannelType LddChannel);
#endif

#if (ICU_SIGNAL_MEASUREMENT_API == STD_ON) || (ICU_EDGE_DETECT_API == STD_ON)
/* The GTM Lowlayer GetInputState, GetTimeElapse and GetDutyCycleValues function */
FUNC(void, ICU_PRIVATE_CODE) Icu_HW_Gtm_GetPulseData(Icu_ChannelType LddChannel);
#endif

#if (ICU_EDGE_COUNT_API == STD_ON)
/* The GTM Lowlayer ResetEdgeCount function */
extern FUNC(void, ICU_PRIVATE_CODE) Icu_HW_Gtm_ResetEdgeCount(Icu_ChannelType LddChannel);
/* The GTM Lowlayer GetEdgeNumbers function */
extern FUNC(void, ICU_PRIVATE_CODE) Icu_HW_Gtm_GetEdgeNumbers(Icu_ChannelType LddChannel);
#endif

/* The GTM Lowlayer start and stop time function */
extern FUNC(void, ICU_PRIVATE_CODE) Icu_HW_Gtm_StartCountMeasurement(Icu_ChannelType LddChannel);
extern FUNC(void, ICU_PRIVATE_CODE) Icu_HW_Gtm_StopCountMeasurement(Icu_ChannelType LddChannel);

#define ICU_STOP_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"

#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"

#if (ICU_TIMESTAMP_API == STD_ON)
/* The GTM Lowlayer record timestamp data in interrupt function */
FUNC(void, ICU_CODE_FAST) Icu_Gtm_ServiceTimestamp(Icu_ChannelType LddChannel, uint32 LulCapturedTimestampVal);
#endif

/* The GTM Lowlayer interrupt function */
extern FUNC(void, ICU_CODE_FAST) Icu_Gtm_TimerIsr(Icu_ChannelType LddChannel);

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"
#endif /* #if (ICU_GTM_TIMER_UNIT_USED == STD_ON) */
#endif /* ICU_GTM_LLDRIVER_H */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
