/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Lin.h                                                                                               */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2019-2025 Renesas Electronics Corporation. All rights reserved.                                                */
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
 *
 * 2.4.1:  30/06/2025  : Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.03 Release
 * 2.3.2:  25/04/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 Release
 * 2.3.1:  31/03/2025  : Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02 Release
 * 2.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 *                       Update LIN_SW_MINOR_VERSION to 3U
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00(D) U2Bx Final Release
 *                       Update LIN_SW_MINOR_VERSION to 2U
 *                       Update LIN_SW_PATCH_VERSION to 0U
 * 2.1.2:  31/10/2024  : Update Software version to 2.1.2
 * 2.1.1:  30/08/2024  : Update LIN_SW_PATCH_VERSION to 1U and LIN_SW_MINOR_VERSION to 1U
 *                       Update LIN_SW_PATCH_VERSION to 3U
 *         02/06/2024  : Remove redundant QAC message 1534 and 1536
 *         01/06/2024  : Remove redundant QAC message
 * 2.1.0:  23/02/2024  : Update SW Version to 2.1.0
 * 2.0.2:  15/01/2024  : Update LIN_SW_PATCH_VERSION to 2U
 * 2.0.1:  21/10/2023  : Add new QAC message 1534 and 1536
 *         11/10/2023  : Update AR version "LIN_AR_R21_11_VERSION" to "LIN_AR_R22_11_VERSION"
 *                       Update macro "LIN_AR_RELEASE_MINOR_VERSION" to 8U
 *                       Update "LIN_START/STOP_SEC_DBTOC_DATA_UNSPECIFIED" to
 *                       "LIN_START/STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED"
 * 2.0.0:  26/07/2023  : Add information about CWE violation ID
 *         18/07/2023  : Update to support for multicore:
 *                       Remove parameter "pFrameVariables" in struct "Lin_ConfigType"
 *                       Add new macro "LIN_E_INVALID_CORE"
 *         27/06/2023  : Remove redundant QAC message (7:0791)
 *         25/05/2023  : Change name of AR version LIN_AR_2111_VERSION to LIN_AR_R21_11_VERSION
 *         22/05/2023  : Remove redundant QAC message
 *         28/04/2023  : Update SW-VERSION to 2.0.0
 *                       Update LIN_SW_MAJOR_VERSION to 2U
 *                       Update LIN_SW_MINOR_VERSION to 0U
 *         20/04/2023  : Add pre-compile macro #if (LIN_MASTER_MODE_SUPPORT == STD_ON) for API:
 *                       Lin_SendFrame, Lin_GoToSleep, Lin_GetStatus
 * 1.5.0:  09/04/2023  : Add QAC message 9.5.0.
 *         06/04/2023  : Update to support AR21-11
 *                       Add macro LIN_AR_2111_VERSION, LIN_E_INVALID_NODE_TYPE
 *         06/03/2023  : Update SW-VERSION to 1.5.0
 *                       Update LIN_SW_MINOR_VERSION to 5U
 *                       Update LIN_SW_PATCH_VERSION to 0U
 * 1.4.5:  05/12/2022  : Update SW-VERSION to 1.4.5
 * 1.4.4:  13/05/2022  : Update SW-VERSION to 1.4.4
 *                       Update LIN_SW_PATCH_VERSION to 4U
 * 1.4.3:  14/04/2022  : Update SW-VERSION to 1.4.3
 *                       Update LIN_SW_PATCH_VERSION to 3U
 * 1.4.2:  04/03/2022  : Update SW-VERSION
 * 1.4.1:  30/12/2021  : Update LIN_SW_PATCH_VERSION to 1U
 * 1.4.0:  11/10/2021  : Update LIN_SW_MINOR_VERSION to 4U
 *                       Update LIN_SW_PATCH_VERSION to 0U
 * 1.3.2:  12/08/2021  : Update LIN_SW_PATCH_VERSION to 2U.
 * 1.3.1:  02/07/2021  : Add QAC message 9.5.0.
 *                       Format source code to 120 characters.
 *                       Improve Violation tag (remove START/END).
 *         21/05/2021  : Update LIN_SW_PATCH_VERSION to 1U.
 * 1.3.0:  15/12/2020  : Release.
 * 1.2.1:  15/12/2020  : Update Module Software version information.
 * 1.2.0:  26/08/2020  : Release.
 * 1.1.0:  19/06/2020  : Release.
 * 1.0.1:  16/04/2020  : Modified #include heading files.
 *         19/03/2019  : Fix QAC
 *                         1. Update "MISRA C Rule Violations" and "QAC warning"
 *                            message from MISRA-C:2004 to MISRA-C:2012.
 *                         2. Move static function prototypes from header file
 *                            to source file.
 * 1.0.0:  12/03/2019  : Initial Version.
 *
 */
/**********************************************************************************************************************/

#ifndef LIN_H
#define LIN_H

/***********************************************************************************************************************
**                             To support different AUTOSAR releases in a single package                              **
***********************************************************************************************************************/

#define LIN_AR_R22_11_VERSION        480
#define LIN_AR_431_VERSION           431
#define LIN_AR_422_VERSION           422

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE Rule CWE-398, CWE-569                                            */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is accepted. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3684)    : Array declared with unknown size.                                                            */
/* Rule                : CERTCCM ARR02, MISRA C:2012 Rule-8.11                                                        */
/* JV-01 Justification : Arrays used are verified in the file which are only declarations and size is configuration   */
/*                       dependent.                                                                                   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for global type declarations */
#include "ComStack_Types.h"
/* Included to get pre-compile macros */
#include "Lin_Cfg.h"
/* Included for Lin general type declarations */
#include "Lin_GeneralTypes.h"

#include "Lin_Types.h"


/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
#define LIN_VENDOR_ID         LIN_VENDOR_ID_VALUE
#define LIN_MODULE_ID         LIN_MODULE_ID_VALUE
#define LIN_INSTANCE_ID       LIN_INSTANCE_ID_VALUE

#if (LIN_AR_VERSION == LIN_AR_422_VERSION)
/* AUTOSAR release version information */
#define LIN_AR_RELEASE_MAJOR_VERSION    4U
#define LIN_AR_RELEASE_MINOR_VERSION    2U
#define LIN_AR_RELEASE_REVISION_VERSION 2U
#elif (LIN_AR_VERSION == LIN_AR_431_VERSION)
/* AUTOSAR release version information */
#define LIN_AR_RELEASE_MAJOR_VERSION    4U
#define LIN_AR_RELEASE_MINOR_VERSION    3U
#define LIN_AR_RELEASE_REVISION_VERSION 1U
#elif (LIN_AR_VERSION == LIN_AR_R22_11_VERSION)
/* AUTOSAR release version information */
#define LIN_AR_RELEASE_MAJOR_VERSION    4U
#define LIN_AR_RELEASE_MINOR_VERSION    8U
#define LIN_AR_RELEASE_REVISION_VERSION 0U
#endif /* #if (LIN_AR_VERSION == LIN_AR_422_VERSION) */

/* Module Software version information */
#define LIN_SW_MAJOR_VERSION    2U
#define LIN_SW_MINOR_VERSION    4U
#define LIN_SW_PATCH_VERSION    1U

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/
/* API service Ids */
#define LIN_WAKEUP_SID               (uint8)0x07
#if defined(LIN_E_TIMEOUT) || (LIN_DEV_ERROR_DETECT == STD_ON)
#define LIN_INIT_SID                 (uint8)0x00
#define LIN_WAKEUP_INTERNAL_SID      (uint8)0x0B
#endif /* #if defined(LIN_E_TIMEOUT) || (LIN_DEV_ERROR_DETECT == STD_ON) */
#if (LIN_MASTER_MODE_SUPPORT == STD_ON)
#define LIN_SEND_FRAME_SID           (uint8)0x04
#define LIN_GO_TO_SLEEP_SID          (uint8)0x06
#endif /* #if (LIN_MASTER_MODE_SUPPORT == STD_ON) */
#if (LIN_WAKEUP_SUPPORT == STD_ON) || (LIN_DEV_ERROR_DETECT == STD_ON)
#define LIN_GO_TO_SLEEP_INTERNAL_SID (uint8)0x09
#endif /* #if (LIN_WAKEUP_SUPPORT == STD_ON) || (LIN_DEV_ERROR_DETECT == STD_ON) */
#if (LIN_DEV_ERROR_DETECT == STD_ON)
#define LIN_GET_VERSIONINFO_SID      (uint8)0x01
#define LIN_GET_STATUS_SID           (uint8)0x08
#define LIN_CHECK_WAKEUP_SID         (uint8)0x0A

/* DET error codes */
#define LIN_E_UNINIT                 (uint8)0x00
#define LIN_E_INVALID_CHANNEL        (uint8)0x02
#define LIN_E_INVALID_POINTER        (uint8)0x03
#define LIN_E_STATE_TRANSITION       (uint8)0x04
#define LIN_E_PARAM_POINTER          (uint8)0x05
#if (LIN_SLAVE_MODE_SUPPORT == STD_ON)
#define LIN_E_INVALID_NODE_TYPE      (uint8)0x10
#endif /* #if (LIN_SLAVE_MODE_SUPPORT == STD_ON) */
#define LIN_E_INVALID_DATABASE       (uint8)0xEF
/* Support for ECUC_Lin_00189 in case DEM reference is not configured. */
#ifndef LIN_E_TIMEOUT
#define LIN_E_DET_TIMEOUT            (uint8)0xF0
#endif /* #ifndef LIN_E_TIMEOUT */

/* DET Error - Call in invalid core */
#if (LIN_MULTI_CORE_SUPPORT == STD_ON)
#define LIN_E_INVALID_CORE           (uint8)0xF1
#endif /* #if (LIN_MULTI_CORE_SUPPORT == STD_ON) */
#endif /* #if (LIN_DEV_ERROR_DETECT == STD_ON) */
/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/
/* LIN Driver Initialization configuration */
typedef struct STag_Lin_ConfigType
{
  /* StartOfDbToc */
  uint32 ulStartOfDbToc;
  
  /* Pointer to first Channel structure */
  P2CONST(void, TYPEDEF, LIN_APPL_CONST) pFirstChannel;

  /* Pointer to LIN3 channel properties */
  P2CONST(void, TYPEDEF, LIN_APPL_CONST) pRLIN3Properties;

} Lin_ConfigType;

/***********************************************************************************************************************
**                                             Global Function Prototypes                                             **
***********************************************************************************************************************/
#define LIN_START_SEC_PUBLIC_CODE
#include "Lin_MemMap.h"

/* API to get the version information */
#if (LIN_VERSION_INFO_API == STD_ON)
extern FUNC(void, LIN_PUBLIC_CODE) 
                                  Lin_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, LIN_APPL_DATA) versioninfo); /* PRQA S 3432 # JV-01 */
#endif /*(LIN_VERSION_INFO_API == STD_ON)*/

/* API to send the header and response part of a LIN Frame */
#if (LIN_MASTER_MODE_SUPPORT == STD_ON)
#if (LIN_AR_VERSION == LIN_AR_422_VERSION)
extern FUNC(Std_ReturnType, LIN_PUBLIC_CODE)
    Lin_SendFrame(uint8 Channel, P2VAR(Lin_PduType, AUTOMATIC, LIN_APPL_DATA) PduInfoPtr);
#elif ((LIN_AR_VERSION == LIN_AR_431_VERSION) || (LIN_AR_VERSION == LIN_AR_R22_11_VERSION))
extern FUNC(Std_ReturnType, LIN_PUBLIC_CODE)
    Lin_SendFrame(uint8 Channel, P2CONST(Lin_PduType, AUTOMATIC, LIN_APPL_DATA) PduInfoPtr);
#endif /* #if (LIN_AR_VERSION == LIN_AR_422_VERSION) */
#endif /* #if (LIN_MASTER_MODE_SUPPORT == STD_ON) */

/* API for wakeup functionality */
extern FUNC(Std_ReturnType, LIN_PUBLIC_CODE) Lin_Wakeup(uint8 Channel);

extern FUNC(Std_ReturnType, LIN_PUBLIC_CODE) Lin_CheckWakeup(uint8 Channel);

/* API for global initialization */
/* API for Lin_Init functionality */
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Init(P2CONST(Lin_ConfigType, AUTOMATIC, LIN_APPL_CONST) Config);

/* API for sleep functionality */
#if (LIN_MASTER_MODE_SUPPORT == STD_ON)
extern FUNC(Std_ReturnType, LIN_PUBLIC_CODE) Lin_GoToSleep(uint8 Channel);
#endif /* #if (LIN_MASTER_MODE_SUPPORT == STD_ON) */

/* API for GoToSleep Internal */
extern FUNC(Std_ReturnType, LIN_PUBLIC_CODE) Lin_GoToSleepInternal(uint8 Channel);

/* API for Wakeup Internal */
extern FUNC(Std_ReturnType, LIN_PUBLIC_CODE) Lin_WakeupInternal(uint8 Channel);

/* API to get the status */
#if (LIN_MASTER_MODE_SUPPORT == STD_ON)
#if (LIN_AR_VERSION == LIN_AR_R22_11_VERSION)
extern FUNC(Lin_StatusType, LIN_PUBLIC_CODE) Lin_GetStatus
    (uint8 Channel, P2CONST(P2VAR(uint8, AUTOMATIC, LIN_APPL_DATA), AUTOMATIC, LIN_APPL_CONST) Lin_SduPtr);             /* PRQA S 3432 # JV-01 */
#else
extern FUNC(Lin_StatusType, LIN_PUBLIC_CODE) Lin_GetStatus
    (uint8 Channel, P2VAR(P2VAR(uint8, AUTOMATIC, LIN_APPL_DATA), AUTOMATIC, LIN_APPL_DATA) Lin_SduPtr);
#endif /* #if (LIN_AR_VERSION == LIN_AR_R22_11_VERSION) */
#endif /* #if (LIN_MASTER_MODE_SUPPORT == STD_ON) */

#define LIN_STOP_SEC_PUBLIC_CODE
#include "Lin_MemMap.h"

/***********************************************************************************************************************
**                                        Extern declarations for Global Data                                         **
***********************************************************************************************************************/
#define LIN_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Lin_MemMap.h"

extern CONST(Lin_ConfigType, LIN_CONST) Lin_GaaConfiguration[];                                                         /* PRQA S 3684 # JV-01 */

#define LIN_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Lin_MemMap.h"

#endif /* LIN_H */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
