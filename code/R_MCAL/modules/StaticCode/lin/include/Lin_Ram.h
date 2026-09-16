/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Lin_Ram.h                                                                                           */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2019-2025 Renesas Electronics Corporation. All rights reserved.                                                */
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
 *
 * 2.4.0:  30/06/2025  : Remove the SW-VERSION from header of file
 * 2.3.2:  25/04/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 Release
 * 2.3.1:  31/03/2025  : Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02 Release
 * 2.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00(D) U2Bx Final Release
 * 2.1.2:  31/10/2024  : Update SW-VERSION to 2.1.2
 * 2.0.0:  26/07/2023  : Add information about CWE violation ID
 *         18/07/2023  : Update to suppport for multicore
 *                       Remove parameter "Lin_GblDriverState" Lin_GblDriverState, Lin_GpChannelConfig, 
 *                       Lin_GpRLIN3Properties, Lin_GpChannelRamData in Global Data Type Section
 *                       Add new Lin_GaaGetCoreId2Index[], Lin_GaaChannelId2CoreIndex[] and Lin_GaaGlobalAccPoint[] 
 *                       to support for multicore in Global Data Type Section
 * 1.4.3:  14/04/2022  : Update SW-VERSION to 1.4.3
 * 1.3.2:  04/03/2022  : Update SW-VERSION
 * 1.3.1:  02/07/2021  : Add QAC message 9.5.0.
 *                       Format source code to 120 characters.
 *                       Improve Violation tag (remove START/END).
 * 1.2.0:  26/08/2020  : Release.
 * 1.1.0:  19/06/2020  : Release.
 * 1.0.1:  16/04/2020  : Modified #include heading files.
 * 1.0.0:  12/03/2019  : Initial Version.
 *
 */
/**********************************************************************************************************************/

#ifndef LIN_RAM_H
#define LIN_RAM_H

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE Rule CWE-398, CWE-569                                            */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is accepted. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Post build time parameters header file */
#include "Lin_PBTypes.h"
/* Macros header file */
#include "Lin_RLIN3_PBTypes.h"
/* Lin Transmit receive header for the target */
#include "Lin_RLIN3_LLDriver.h"

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define LIN_RAM_AR_RELEASE_MAJOR_VERSION    LIN_AR_RELEASE_MAJOR_VERSION
#define LIN_RAM_AR_RELEASE_MINOR_VERSION    LIN_AR_RELEASE_MINOR_VERSION
#define LIN_RAM_AR_RELEASE_REVISION_VERSION LIN_AR_RELEASE_REVISION_VERSION

/* Module Software version information */
#define LIN_RAM_SW_MAJOR_VERSION            LIN_SW_MAJOR_VERSION
#define LIN_RAM_SW_MINOR_VERSION            LIN_SW_MINOR_VERSION

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/
#if (LIN_MULTI_CORE_SUPPORT == STD_ON)
#define LIN_START_SEC_CONST_8
#include "Lin_MemMap.h"

/* Assumption - support 4 core, and core 4 is not valid */
extern const uint8 Lin_GaaGetCoreId2Index[LIN_SUPPORTED_CORE_MAX_NUM];

/* Covert channel id to core id */
extern const uint8 Lin_GaaChannelId2CoreIndex[LIN_NO_OF_CHANNELS];

#define LIN_STOP_SEC_CONST_8
#include "Lin_MemMap.h"
#endif 

#define LIN_START_SEC_CONST_32
#include "Lin_MemMap.h"

extern const Lin_GlobalAccessPointType Lin_GaaGlobalAccPoint[LIN_CONFIGURED_CORE_NUM];

#define LIN_STOP_SEC_CONST_32
#include "Lin_MemMap.h"

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/

#endif /* LIN_RAM_H */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
