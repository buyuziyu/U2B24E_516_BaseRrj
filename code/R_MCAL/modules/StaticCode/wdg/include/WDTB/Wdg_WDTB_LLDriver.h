/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Wdg_WDTB_LLDriver.h                                                                                 */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Provision of API and database declaration, Service Id and DET error Macros and Module version information Macros.  */
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
 * 2.4.1:  30/06/2025    : Remove SW-VERSION in file header 
 * 2.4.0:  30/06/2025    : Update SW-VERSION for RH850/Ver22.01.00 (D) U2Ax release
 * 2.3.2:  29/04/2025    : Update SW-VERSION for RH850/Ver22.00.03 U2Bx-E  
 * 2.3.1:  31/03/2025    : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 *                         Support QAC 11.6.0
 * 2.3.0:  28/02/2025    : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024    : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final release
 * 2.1.2:  30/10/2024    : Update SW-VERSION to 2.1.2
 * 2.1.1:  31/08/2024    : Update SW-VERSION to 2.1.1
 * 2.0.0:  18/07/2023    : Delete #ifdef WDG_INSTANCE_INDEX macros related,
 *                         Change #include "Wdg_Mapping.h" with #include "Wdg_MemMap.h",
 * 1.4.3:  10/05/2022    : Update SW-VERSION
 * 1.4.1:  06/12/2021    : Add INST6 to support U2Bx devices
 * 1.3.1:  07/07/2021    : Add QAC message 9.5.0
 *                         Format source code to 120 characters
 *                         Improve Violation tag (remove START/END)
 *         30/06/2021    : 1) Change file name from Wdg_59_WDTB_LLDriver.h to Wdg_WDTB_LLDriver.h.
 *                         2) Update header file macro to call file multiple times.
 *                         3) Change from #include "Wdg_59_MemMap.h" to #include "Wdg_MemMap.h".
 *                         4) Remove _VendorID ("_59") in all macros, APIs..
 * 1.2.0:  26/08/2020    : Release
 * 1.1.0:  19/06/2020    : Release
 * 1.0.0:  20/03/2020    : Initial Version
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/

#ifndef WDG_WDTB_LLDRIVER_HEADER
#define WDG_WDTB_LLDRIVER_HEADER

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define WDG_WDTB_LLDRIVER_AR_RELEASE_MAJOR_VERSION    WDG_AR_RELEASE_MAJOR_VERSION
#define WDG_WDTB_LLDRIVER_AR_RELEASE_MINOR_VERSION    WDG_AR_RELEASE_MINOR_VERSION
#define WDG_WDTB_LLDRIVER_AR_RELEASE_REVISION_VERSION WDG_AR_RELEASE_REVISION_VERSION

/* Module Software version information */
#define WDG_WDTB_LLDRIVER_SW_MAJOR_VERSION            WDG_SW_MAJOR_VERSION
#define WDG_WDTB_LLDRIVER_SW_MINOR_VERSION            WDG_SW_MINOR_VERSION

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/
#define WDG_START_SEC_PRIVATE_CODE
#include "Wdg_MemMap.h"
FUNC(void, WDG_PRIVATE_CODE) Wdg_WDTBn_Init(void);
#define WDG_STOP_SEC_PRIVATE_CODE
#include "Wdg_MemMap.h"

#define WDG_START_SEC_PRIVATE_CODE
#include "Wdg_MemMap.h"
FUNC(void, WDG_PRIVATE_CODE) Wdg_ECM_Init(void);
#define WDG_STOP_SEC_PRIVATE_CODE
#include "Wdg_MemMap.h"

#define WDG_START_SEC_PRIVATE_CODE
#include "Wdg_MemMap.h"
FUNC(void, WDG_PRIVATE_CODE) Wdg_WDTBn_SetMode(const WdgIf_ModeType LddMode);
#define WDG_STOP_SEC_PRIVATE_CODE
#include "Wdg_MemMap.h"

#if (WDG_DEV_ERROR_DETECT == STD_ON)
#define WDG_START_SEC_PRIVATE_CODE
#include "Wdg_MemMap.h"
FUNC(void, WDG_PRIVATE_CODE) Wdg_SetStatus(const Wdg_StatusType LenStatusType);
#define WDG_STOP_SEC_PRIVATE_CODE
#include "Wdg_MemMap.h"
#endif

#define WDG_START_SEC_CODE_FAST
#include "Wdg_MemMap.h"
extern FUNC(void, WDG_CODE_FAST) Wdg_WDTBn_TriggerFunc(void);
#define WDG_STOP_SEC_CODE_FAST
#include "Wdg_MemMap.h"
#endif /* WDG_WDTB_LLDRIVER_HEADER */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
