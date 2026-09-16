/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Fr_59_Renesas_Ram.h                                                                                 */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2019-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Global RAM variable definitions for Fr Driver are declared.                                                        */
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
 * 2.4.0:  30/06/2025    : Update SW-VERSION for RH850/U2Ax MCAL Ver22.01.00(D) Final Release
 * 2.3.2:  29/04/2025    : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 Release
 * 2.3.1:  31/03/2025    : Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02 Release
 * 2.3.1:  31/03/2025    : Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02 Release
 * 2.3.0:   28/02/2025   : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.1:   31/12/2024   : Update SW-VERSION for Ver22.00.01 U2Ax Release
 * 2.2.0:   31/12/2024   : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 * 2.1.3:   31/10/2024   : Update SW-VERSION to 2.1.3
 * 2.1.1:   30/08/2024   : As part of multicore support, following changes are made:
 *                         1. Delete global variable Fr_59_Renesas_GblInitDone Fr_59_Renesas_GblTransferHandlerInitDone
 *                          and move it to postbuild
 *                         2. Add new array Fr_59_Renesas_GaaGetCoreId2Index Fr_59_Renesas_GaaGetController2CoreIndex
 *                       : As part of multiple postbuild variant support, following changes are made:
 *                         Add new variable Fr_59_Renesas_GpPeriodTimeConfigPtr
 *                       : As part of QAC 10.3.0 support, following changes are made:
 *                         Remove redundant QAC message: 0791
 * 2.1.0:   24/02/2024   : Change SW-VERSION to 2.1.0
 * 2.0.0:   30/07/2023   : Add CWE rule into QAC header (3432 message)
 *                       : Remove Types of AUTOSAR FlexRay modules (Fr, FrIf and FrTrcv)
 * 1.4.3:   09/05/2022   : Change SW-VERSION to 1.4.3
 * 1.3.3:   02/03/2022   : Change SW-VERSION to 1.4.2
 * 1.3.2:   13/08/2021   : Change SW-VERSION to 1.3.2
 * 1.3.1:   02/07/2021   : Add QAC message 9.5.0.
 *                         Format source code to 120 characters.
 *                         Improve Violation tag (remove START/END).
 * 1.3.0:   02/12/2020   : Remove QAC message 3210.
 * 1.2.0:   26/08/2020   : Release.
 * 1.1.0:   19/06/2020   : Release.
 *          28/07/2020   : Add QAC 9.3.1 comment.
 * 1.0.3:   29/05/2020   : Remove MISRA C Rule (4:3447).
 *          13/05/2020   : Move Fr_59_Renesas_GpBufReconfigStatusPtr memory section from
 *                         FR_59_RENESAS_START_SEC_VAR_NO_INIT_16 to FR_59_RENESAS_STOP_SEC_VAR_NO_INIT_PTR.
 *          06/05/2020   : Add declaration of Fr_59_Renesas_GblTransferHandlerInitDone.
 * 1.0.2:   17/04/2020   : Update the header files including.
 * 1.0.1:   04/02/2020   : Change FR_59_RENESAS_START_SEC_VAR_NOINIT_UNSPECIFIED
 *                         to FR_59_RENESAS_START_SEC_VAR_NO_INIT_PTR,
 *                         FR_59_RENESAS_STOP_SEC_VAR_NOINIT_UNSPECIFIED to
 *                         FR_59_RENESAS_STOP_SEC_VAR_NO_INIT_PTR to support
 *                         AUTOSAR R4.3.1.
 *          18/12/2019   : Update section FR_59_RENESAS_START_SEC_VAR_NOINIT_16
 *                         to FR_59_RENESAS_START_SEC_VAR_NO_INIT_16,
 *                         FR_59_RENESAS_STOP_SEC_VAR_NOINIT_16
 *                         to FR_59_RENESAS_STOP_SEC_VAR_NO_INIT_16,
 *                         FR_59_RENESAS_START_SEC_VAR_NOINIT_UNSPECIFIED
 *                         to FR_59_RENESAS_START_SEC_VAR_NO_INIT_UNSPECIFIED,
 *                         FR_59_RENESAS_STOP_SEC_VAR_NOINIT_UNSPECIFIED
 *                         to FR_59_RENESAS_STOP_SEC_VAR_NO_INIT_UNSPECIFIED.
 * 1.0.0:   11/12/2019   : Initial Version.
 */
/**********************************************************************************************************************/
#ifndef FR_59_RENESAS_RAM_H
#define FR_59_RENESAS_RAM_H

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/***********************************************************************************************************************
**                             To support different AUTOSAR releases in a single package                              **
***********************************************************************************************************************/
/* Common FR types definition */
#include "Fr_59_Renesas_Types.h"
/* Post-build Types definition */
#include "Fr_59_Renesas_PBTypes.h"
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define FR_59_RENESAS_RAM_AR_RELEASE_MAJOR_VERSION    FR_59_RENESAS_AR_RELEASE_MAJOR_VERSION
#define FR_59_RENESAS_RAM_AR_RELEASE_MINOR_VERSION    FR_59_RENESAS_AR_RELEASE_MINOR_VERSION
#define FR_59_RENESAS_RAM_AR_RELEASE_REVISION_VERSION FR_59_RENESAS_AR_RELEASE_REVISION_VERSION

/* Module Software version information */
#define FR_59_RENESAS_RAM_SW_MAJOR_VERSION            FR_59_RENESAS_SW_MAJOR_VERSION
#define FR_59_RENESAS_RAM_SW_MINOR_VERSION            FR_59_RENESAS_SW_MINOR_VERSION

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE Rule CWE-398, CWE-569                                            */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is accepted. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/
#if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
#define FR_59_RENESAS_START_SEC_CONST_8
#include "Fr_59_Renesas_MemMap.h"

/* Core Id to index table */
extern const uint8 Fr_59_Renesas_GaaGetCoreId2Index[FR_59_RENESAS_SUPPORTED_CORE_MAX_NUM];

/* Covert controller index to core index */
extern const uint8 Fr_59_Renesas_GaaGetController2CoreIndex[FR_59_RENESAS_NUM_CTRL_SUPPORTED];

#define FR_59_RENESAS_STOP_SEC_CONST_8
#include "Fr_59_Renesas_MemMap.h"
#endif

#define FR_59_RENESAS_START_SEC_CONST_32
#include "Fr_59_Renesas_MemMap.h"

extern const Fr_59_Renesas_GlobalAccessPointType Fr_59_Renesas_GaaGlobalAccPoint[FR_59_RENESAS_CONFIGURED_CORE_NUM];

#define FR_59_RENESAS_STOP_SEC_CONST_32
#include "Fr_59_Renesas_MemMap.h"

#define FR_59_RENESAS_START_SEC_VAR_NO_INIT_PTR
#include "Fr_59_Renesas_MemMap.h"

/* Global pointer for Hardware register */
extern P2CONST(Fr_59_Renesas_PeriodTimeType, FR_VAR_NO_INIT,
               FR_CONFIG_DATA) volatile Fr_59_Renesas_GpPeriodTimeConfigPtr;

/* Global pointer for Hardware register */
extern P2CONST(Fr_59_Renesas_RegisterSetType, FR_VAR_NO_INIT,
               FR_CONFIG_DATA) volatile Fr_59_Renesas_GpCtrlRegSet[FR_59_RENESAS_NUM_CTRL_SUPPORTED];

/* Global pointer variable for database */
extern P2CONST(Fr_59_Renesas_ControllerConfigType, FR_VAR_NO_INIT,
               FR_CONFIG_DATA) volatile Fr_59_Renesas_GpControllerConfigPtr;

#if (FR_59_RENESAS_RECONFIG_LPDU == STD_ON) || (FR_59_RENESAS_PREPARE_LPDU == STD_ON) || \
    (FR_59_RENESAS_DISABLE_LPDU == STD_ON)
/* Global pointer for Buffer Reconfig Status */
extern P2VAR(uint16, FR_VAR_NO_INIT,                                                                                    /* PRQA S 3432 # JV-01 */
             FR_APPL_DATA) volatile Fr_59_Renesas_GpBufReconfigStatusPtr[FR_59_RENESAS_NUM_CTRL_SUPPORTED];
#endif

#define FR_59_RENESAS_STOP_SEC_VAR_NO_INIT_PTR
#include "Fr_59_Renesas_MemMap.h"
/***********************************************************************************************************************
**                                             Global Function Prototypes                                             **
***********************************************************************************************************************/

#endif /* FR_59_RENESAS_RAM_H */

/***********************************************************************************************************************
**                                                    End Of File                                                     **
***********************************************************************************************************************/
