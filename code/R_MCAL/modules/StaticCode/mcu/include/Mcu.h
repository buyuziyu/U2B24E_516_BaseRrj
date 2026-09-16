/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2X MCAL Components                                                                 */
/* Module       = Mcu.h                                                                                               */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Provision of API information.                                                                                      */
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
/*              Devices:        X2X                                                                                   */
/*====================================================================================================================*/

/***********************************************************************************************************************
**                                              Revision Control History                                              **
***********************************************************************************************************************/
/*
 * 2.5.1:  30/06/2025   : Update SW-VERSION for U2Bx Ver22.02.00.001 Release
 * 2.5.0:  30/06/2025   : Update SW-VERSION for U2Ax Ver22.01.00(D) Release
 * 2.4.0:  31/05/2025   : Update SW-VERSION for U2Cx Ver21.01.01 Release
 * 2.3.2:  29/04/2025   : Update SW-VERSION for U2Ax Ver22.00.03 Release
 * 2.3.1:  31/03/2025   : Update SW-VERSION for U2BxE Ver22.00.02 Release
 * 2.3.0:  28/02/2025   : Update SW-VERSION for Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024   : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Release
 * 2.1.2:  31/10/2024   : Update SW-VERSION to 2.1.2
 * 2.1.1:  30/08/2024   : Update SW-VERSION to 2.1.1
 *                        As part of QAC 9.5.0 support, following changes are made:
 *                        - Remove redundant QAC message 1534
 * 2.1.0:  26/02/2024   : Update SW-VERSION to 2.1.0
 * 2.0.1:  10/10/2023   : Change "MCU_START/STOP_SEC_DBTOC_DATA_UNSPECIFIED"
 *                        to "MCU_START/STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED"
 *         05/10/2023   : Change MCU_AR_R21_11_VERSION to MCU_AR_R22_11_VERSION support for R22-11
 *                        Update SW-VERSION to 2.0.1
 * 2.0.0:  04/08/2023   : Remove redundant QAC message 0791
 *         20/04/2023   : Change MCU_AR_431_VERSION to MCU_AR_R21_11_VERSION support for R21-11
 *                        Update SW-VERSION to 2.0.0
 * 1.5.0:  07/03/2023   : Update value of MCU_SW_PATCH_VERSION from 5 to 0
 *                        Update value of MCU_SW_MINOR_VERSION from 4 to 5 
 * 1.4.5:  01/02/2023   : Update value of MCU_SW_PATCH_VERSION from 4 to 5
 * 1.4.4:  13/07/2022   : Update value of MCU_SW_PATCH_VERSION from 3 to 4
 * 1.4.3:  13/04/2022   : Update SW-VERSION to 1.4.3
 *         07/04/2022   : Update description for MCU_CLEARANDSETWAKEUPFACTOR_SID from Mcu_ClearWakeUpFactor to
 *                        Mcu_ClearAndSetWakeUpFactor
 *                        Update value of MCU_SW_PATCH_VERSION from 2 to 3
 * 1.4.2:  09/03/2022   : Update value of MCU_SW_PATCH_VERSION from 1 to 2
 * 1.4.0:  11/10/2021   : Update value of MCU_SW_PATCH_VERSION from 2 to 0
 *                        Update value of MCU_SW_MINOR_VERSION from 3 to 4
 * 1.3.2:  02/07/2021   : Update value of MCU_SW_PATCH_VERSION from 1 to 2
 * 1.3.1:  02/07/2021   : Add QAC message 9.5.0
 *                        Format source code to 120 characters
 *                        Improve Violation tag (remove START/END)
 *         19/05/2021   : Removed macro MCU_E_INITRAMSECTION_FAILED, MCU_E_INITCLOCK_FAILED.
 *                        Update module software version information to 1.3.1
 * 1.3.0:  24/11/2020   : Update module software version information to 1.3.0
 * 1.2.0:  17/07/2020   : Release
 * 1.1.0:  19/06/2020   : Release
 * 1.0.1:  15/04/2020   : Fix to define hardcode for module software version
 * 1.0.0:  10/01/2020   : Initial Version
 */
/**********************************************************************************************************************/
#ifndef MCU_H
#define MCU_H
/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE Rule CWE-398, CWE-569                                            */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is accepted. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3684)    : Array declared with unknown size.                                                            */
/* Rule                : MISRA C:2012 Rule-8.11, CERTCCM ARR02                                                        */
/* JV-01 Justification : Arrays used are verified in the file which are only declarations and size is configuration   */
/*                       dependent.                                                                                   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for Type definitions */
#include "Std_Types.h"
/* Included for pre-compile options */
#include "Mcu_Cfg.h"
/* To publish the type Mcu_ConfigType */
#include "Mcu_Types.h"


/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
#define MCU_VENDOR_ID      MCU_VENDOR_ID_VALUE
#define MCU_MODULE_ID      MCU_MODULE_ID_VALUE
#define MCU_INSTANCE_ID    MCU_INSTANCE_ID_VALUE
#define MCU_AR_422_VERSION 422
#define MCU_AR_R22_11_VERSION 2211

/* AUTOSAR release version information */
#if (MCU_AR_VERSION == MCU_AR_422_VERSION)
#define MCU_AR_RELEASE_MAJOR_VERSION    4U
#define MCU_AR_RELEASE_MINOR_VERSION    2U
#define MCU_AR_RELEASE_REVISION_VERSION 2U
#elif (MCU_AR_VERSION == MCU_AR_R22_11_VERSION)
#define MCU_AR_RELEASE_MAJOR_VERSION    4U
#define MCU_AR_RELEASE_MINOR_VERSION    8U
#define MCU_AR_RELEASE_REVISION_VERSION 0U
#endif

/* Module Software version information */
#define MCU_SW_MAJOR_VERSION            2U
#define MCU_SW_MINOR_VERSION            5U
#define MCU_SW_PATCH_VERSION            1U

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/
/* Service IDs */
/* Service Id of Mcu_Init API */
#define MCU_INIT_SID                    (uint8)0x00

/* Service Id of Mcu_InitRamSection API */
#define MCU_INITRAMSECTION_SID          (uint8)0x01

/* Service Id of Mcu_InitClock API */
#define MCU_INITCLOCK_SID               (uint8)0x02

/* Service Id of Mcu_DistributePllClock API */
#define MCU_DISTRIBUTEPLLCLOCK_SID      (uint8)0x03

/* Service Id of Mcu_GetPllStatus API */
#define MCU_GETPLLSTATUS_SID            (uint8)0x04

/* Service Id of Mcu_GetResetReason API */
#define MCU_GETRESETREASON_SID          (uint8)0x05

/* Service Id of Mcu_GetResetRawValue API */
#define MCU_GETRESETRAWVAULE_SID        (uint8)0x06

/* Service Id of Mcu_PerformReset API */
#define MCU_PERFORMRESET_SID            (uint8)0x07

/* Service Id of Mcu_SetMode API */
#define MCU_SETMODE_SID                 (uint8)0x08

/* Service Id of Mcu_GetVersionInfo API */
#define MCU_GETVERSIONINFO_SID          (uint8)0x09

/* Service Id of Mcu_GetRamState API */
#define MCU_GETRAMSTATE_SID             (uint8)0x0A

/* Service Id of Mcu_ClearAndSetWakeUpFactor API */
#define MCU_CLEARANDSETWAKEUPFACTOR_SID (uint8)0x0B

/* Service Id of Mcu_GetWakeUpFactor API */
#define MCU_GETWAKEUPFACTOR_SID         (uint8)0x0C

/* Service Id of Mcu_ReleaseIoBufferHold API */
#define MCU_RELEASEIOBUFFERHOLD_SID     (uint8)0x0D

/***********************************************************************************************************************
**                                                  DET Error Codes                                                   **
***********************************************************************************************************************/

/* DET Code to report NULL pointer passed to Mcu_Init API */
#define MCU_E_PARAM_CONFIG              (uint8)0x0A

/* DET Code for invalid Clock Setting */
#define MCU_E_PARAM_CLOCK               (uint8)0x0B

/* DET Code for invalid Operation Mode */
#define MCU_E_PARAM_MODE                (uint8)0x0C

/* DET Code for invalid RAM Section handle */
#define MCU_E_PARAM_RAMSECTION          (uint8)0x0D

/* DET Code to report that PLL Clock is not locked */
#define MCU_E_PLL_NOT_LOCKED            (uint8)0x0E

/* DET code to report uninitialized state */
#define MCU_E_UNINIT                    (uint8)0x0F

/* DET code to report NULL pointer violation */
#define MCU_E_PARAM_POINTER             (uint8)0x10

/* DET code to report Invalid configuration set selection */
#define MCU_E_INIT_FAILED               (uint8)0x11

/* DET code to report invalid database */
#define MCU_E_INVALID_DATABASE          (uint8)0xEF

/* DET code to report invalid set mode sequence */
#define MCU_E_INVALID_MODE_SEQUENCE     (uint8)0x14

/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/
#define MCU_START_SEC_PUBLIC_CODE
#include "Mcu_MemMap.h"

extern FUNC(void, MCU_PUBLIC_CODE) Mcu_Init(P2CONST(Mcu_ConfigType, AUTOMATIC, MCU_APPL_CONST) ConfigPtr);

extern FUNC(Std_ReturnType, MCU_PUBLIC_CODE) Mcu_InitRamSection (Mcu_RamSectionType RamSection);

#if (MCU_INIT_CLOCK == STD_ON)
extern FUNC(Std_ReturnType, MCU_PUBLIC_CODE) Mcu_InitClock (Mcu_ClockType ClockSetting);
#endif

#if (MCU_NO_PLL == STD_OFF)
extern FUNC(Std_ReturnType, MCU_PUBLIC_CODE) Mcu_DistributePllClock(void);
#endif

extern FUNC(Mcu_PllStatusType, MCU_PUBLIC_CODE) Mcu_GetPllStatus(void);

extern FUNC(Mcu_ResetType, MCU_PUBLIC_CODE) Mcu_GetResetReason(void);

extern FUNC(Mcu_RawResetType, MCU_PUBLIC_CODE) Mcu_GetResetRawValue(void);

#if (MCU_PERFORM_RESET_API == STD_ON)
extern FUNC(void, MCU_PUBLIC_CODE) Mcu_PerformReset(void);
#endif

#if (MCU_SW_RESET_CALL_API == STD_ON)
extern FUNC(void, MCU_PUBLIC_CODE) MCU_RESET_CALLOUT(void);
#endif

#if (MCU_GET_RAM_STATE_API == STD_ON)
extern FUNC(Mcu_RamStateType, MCU_PUBLIC_CODE) Mcu_GetRamState(void);
#endif

#if (MCU_VERSION_INFO_API == STD_ON)
extern FUNC(void, MCU_PUBLIC_CODE) Mcu_GetVersionInfo
    (P2VAR(Std_VersionInfoType, AUTOMATIC, MCU_APPL_DATA) versioninfo);                                                 /* PRQA S 3432 # JV-01 */
#endif

extern FUNC(void, MCU_PUBLIC_CODE) Mcu_SetMode(Mcu_ModeType LddMcuMode);

#if (MCU_CLEARANDSETWAKEUPFACTOR_API == STD_ON)
extern FUNC(Std_ReturnType, MCU_PUBLIC_CODE) Mcu_ClearAndSetWakeUpFactor(Mcu_ModeType LddMcuMode);
#endif

#if (MCU_GETWAKEUPFACTOR_API == STD_ON)
extern FUNC(Std_ReturnType, MCU_PUBLIC_CODE)
    Mcu_GetWakeUpFactor(P2VAR(Mcu_WakeUpFactorInfoType, AUTOMATIC, MCU_APPL_DATA) LpMcuWakeupfactorinfoPtr);            /* PRQA S 3432 # JV-01 */
#endif

#if (MCU_RELEASEIOBUFFERHOLD_API == STD_ON)
extern FUNC(Std_ReturnType, MCU_PUBLIC_CODE) Mcu_ReleaseIoBufferHold(void);
#endif

#define MCU_STOP_SEC_PUBLIC_CODE
#include "Mcu_MemMap.h"

/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/
#define MCU_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Mcu_MemMap.h"
/* Structure for MCU Init configuration */
extern CONST(Mcu_ConfigType, MCU_CONFIG_DATA) Mcu_GaaConfiguration[];                                                   /* PRQA S 3684 # JV-01 */
#define MCU_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Mcu_MemMap.h"
#endif /* MCU_H */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
