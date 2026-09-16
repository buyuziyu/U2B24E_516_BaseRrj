/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = FlsTst.h                                                                                            */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2023-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Provision of external declaration of APIs and Service IDs.                                                         */
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
 * 1.4.1:  30/06/2025  : Update SW-VERSION
 * 1.3.1:  31/03/2025  : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E 
 * 1.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 1.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Relase      
 * 1.1.2:  31/10/2024  : As part of QAC 9.5.0 support, following changes are made:
 *                       1. Remove QAC message 1534
 * 1.1.0:  22/02/2024  : Update SW-VERSION to 1.1.0
 * 1.0.1:  18/10/2023  : Add QAC message 1534
 *         05/10/2023  : Update FLSTST_AR_R22_11_VERSION. Remove FLSTST_START_SEC_DBTOC_DATA_UNSPECIFIED, 
 *                       FLSTST_STOP_SEC_DBTOC_DATA_UNSPECIFIED.
 * 1.0.0:  17/03/2023  : Initial Version.
 *
 */
/**********************************************************************************************************************/

#ifndef FLSTST_H
#define FLSTST_H

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Standard type include */
#include "Std_Types.h"
/* Included to get pre-compile macros */
#include "FlsTst_Cfg.h"
/* Included to get types definition */
#include "FlsTst_Types.h"
/* Include callback header for test complete notification */
#include "FlsTst_Cbk.h"

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* Supported AUTOSAR release versions information */
#define FLSTST_AR_R22_11_VERSION 480U
#define FLSTST_AR_R21_11_VERSION 470U
#define FLSTST_AR_431_VERSION 431U                                                                                      

/* Vendor and module identification */
#define FLSTST_VENDOR_ID         FLSTST_VENDOR_ID_VALUE
#define FLSTST_MODULE_ID         FLSTST_MODULE_ID_VALUE
#define FLSTST_INSTANCE_ID       FLSTST_INSTANCE_ID_VALUE

#if (FLSTST_AR_VERSION == FLSTST_AR_R22_11_VERSION)
/* AUTOSAR release version information */
#define FLSTST_AR_RELEASE_MAJOR_VERSION    4U
#define FLSTST_AR_RELEASE_MINOR_VERSION    8U
#define FLSTST_AR_RELEASE_REVISION_VERSION 0U

#elif (FLSTST_AR_VERSION == FLSTST_AR_R21_11_VERSION)
/* AUTOSAR release version information */
#define FLSTST_AR_RELEASE_MAJOR_VERSION    4U
#define FLSTST_AR_RELEASE_MINOR_VERSION    7U
#define FLSTST_AR_RELEASE_REVISION_VERSION 0U
#elif (FLSTST_AR_VERSION == FLSTST_AR_431_VERSION)
/* AUTOSAR release version information */
#define FLSTST_AR_RELEASE_MAJOR_VERSION    4U
#define FLSTST_AR_RELEASE_MINOR_VERSION    3U
#define FLSTST_AR_RELEASE_REVISION_VERSION 1U
#endif

/* Module Software version information */
#define FLSTST_SW_MAJOR_VERSION    1U
#define FLSTST_SW_MINOR_VERSION    4U
#define FLSTST_SW_PATCH_VERSION    1U

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:3684)    : Array declared with unknown size.                                                            */
/* Rule                : CERTCCM ARR02, MISRA C:2012 Rule-8.11                                                        */
/* JV-01 Justification : Arrays used are verified in the file which are only declarations and size is configuration   */
/*                       dependent.                                                                                   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE Rule CWE-398, CWE-569                                            */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is accepted. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/
/* API service Ids */
#define FLSTST_INIT_SID                         (uint8)0x00
#define FLSTST_DEINIT_SID                       (uint8)0x01
#define FLSTST_START_FGND_SID                   (uint8)0x02
#define FLSTST_ABORT_SID                        (uint8)0x03
#define FLSTST_SUSPEND_SID                      (uint8)0x04
#define FLSTST_RESUME_SID                       (uint8)0x05
#define FLSTST_GET_CURRENT_STATE_SID            (uint8)0x06                                                             
#define FLSTST_GET_TEST_RESULT_BGND_SID         (uint8)0x07
#define FLSTST_GET_VERSION_INFO_SID             (uint8)0x08
#define FLSTST_GET_TEST_SIGNATURE_BGND_SID      (uint8)0x09
#define FLSTST_GET_TEST_SIGNATURE_FGND_SID      (uint8)0x0A
#define FLSTST_GET_ERROR_DETAILS_SID            (uint8)0x0B
#define FLSTST_TEST_ECC_SID                     (uint8)0x0C                                                             
#define FLSTST_MAIN_FUNCTION_SID                (uint8)0x0D                                                             
#define FLSTST_TEST_COMPLETED_NOTIFICATION_SID  (uint8)0x0E                                                             
#define FLSTST_GET_TEST_RESULT_FGND_SID         (uint8)0x0F

/* DET error codes */
#define FLSTST_E_STATE_FAILURE          (uint8)0x01
#define FLSTST_E_PARAM_INVALID          (uint8)0x02
#define FLSTST_E_UNINIT                 (uint8)0x03
#define FLSTST_E_ALREADY_INITIALIZED    (uint8)0x04
#define FLSTST_E_INIT_FAILED            (uint8)0x05
#define FLSTST_E_PARAM_POINTER          (uint8)0x06
#define FLSTST_E_INVALID_DATABASE       (uint8)0xEF

/***********************************************************************************************************************
**                                             Global Function Prototypes                                             **
***********************************************************************************************************************/
#define FLSTST_START_SEC_PUBLIC_CODE
#include "FlsTst_MemMap.h"

/* This API performs the initialization of the FLSTST */
extern FUNC(void, FLSTST_PUBLIC_CODE) FlsTst_Init(
    P2CONST(FlsTst_ConfigType, AUTOMATIC, FLSTST_APPL_CONST) ConfigPtr);

/* This service is for Flash Test De-Initialization */
extern FUNC(void, FLSTST_PUBLIC_CODE) FlsTst_DeInit(void);

#if (FLSTST_START_FGND_API == STD_ON)
/* This service is for executing Foreground Flash Test */
extern FUNC(Std_ReturnType, FLSTST_PUBLIC_CODE)
    FlsTst_StartFgnd(FlsTst_BlockIdFgndType FgndBlockId);
#endif

/* This service is for aborting the Flash Test */
extern FUNC(void, FLSTST_PUBLIC_CODE) FlsTst_Abort(void);

#if (FLSTST_SUSPEND_RESUME_API == STD_ON)
/* This service is for suspending current operation of the Flash Test */
extern FUNC(void, FLSTST_PUBLIC_CODE) FlsTst_Suspend(void);

/* This service is for continuing the Flash Test at the point it was suspended */
extern FUNC(void, FLSTST_PUBLIC_CODE) FlsTst_Resume(void);
#endif

#if (FLSTST_GET_CURRENT_STATE_API == STD_ON)
/* This service is for returning the current Flash Test execution state */
extern FUNC(FlsTst_StateType, FLSTST_PUBLIC_CODE) FlsTst_GetCurrentState(void);
#endif

#if (FLSTST_GET_TEST_RESULT_BGND_API == STD_ON)
/* This service is for returning the Background Flash Test result */
extern FUNC(FlsTst_TestResultBgndType, FLSTST_PUBLIC_CODE)
    FlsTst_GetTestResultBgnd(void);
#endif

#if (FLSTST_GET_TEST_RESULT_FGND_API == STD_ON)
/* This service is for returning the Foreground Flash Test result */
extern FUNC(FlsTst_TestResultFgndType, FLSTST_PUBLIC_CODE)
    FlsTst_GetTestResultFgnd(void);
#endif

#if (FLSTST_VERSION_INFO_API == STD_ON)
/* This service is for returning the version information of this module */
extern FUNC(void, FLSTST_PUBLIC_CODE) FlsTst_GetVersionInfo
    (P2VAR(Std_VersionInfoType, AUTOMATIC, FLSTST_APPL_CONST) versioninfo);                                             /* PRQA S 3432 # JV-01 */
#endif

#if (FLSTST_GET_TEST_SIGNATURE_BGND_API == STD_ON)
/* This service is for returning the Flash Test result in background mode */
extern FUNC(FlsTst_TestSignatureBgndType, FLSTST_PUBLIC_CODE)
    FlsTst_GetTestSignatureBgnd(void);
#endif

#if (FLSTST_GET_TEST_SIGNATURE_FGND_API == STD_ON)
/* This service is for returning the Flash Test result in foreground mode */
extern FUNC(FlsTst_TestSignatureFgndType, FLSTST_PUBLIC_CODE)
    FlsTst_GetTestSignatureFgnd(void);
#endif

#if (FLSTST_GET_ERROR_DETAILS_API == STD_ON)
/* This service is for returning error details monitored from the Flash Test module */
extern FUNC(FlsTst_ErrorDetailsType, FLSTST_PUBLIC_CODE)
    FlsTst_GetErrorDetails(void);
#endif

#if (FLSTST_TEST_ECC_API  == STD_ON)
/* This service is for executing a test of ECC hardware */
extern FUNC(Std_ReturnType, FLSTST_PUBLIC_CODE) FlsTst_TestEcc(void);
#endif

#define FLSTST_STOP_SEC_PUBLIC_CODE
#include "FlsTst_MemMap.h"

/***********************************************************************************************************************
**                                        Extern declarations for Global Data                                         **
***********************************************************************************************************************/
#define FLSTST_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "FlsTst_MemMap.h"

extern CONST(FlsTst_ConfigType, FLSTST_CONST) FlsTst_GstConfiguration[];                                                /* PRQA S 3684 # JV-01 */

#define FLSTST_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "FlsTst_MemMap.h"
#endif /* FLSTST_H */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
