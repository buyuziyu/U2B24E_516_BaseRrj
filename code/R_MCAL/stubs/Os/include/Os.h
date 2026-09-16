/*============================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                         */
/* Module       = Os.h                                                        */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2023-2025 Renesas Electronics Corporation. All rights reserved.        */
/*============================================================================*/
/* Purpose:                                                                   */
/* This file is a stub for OS component                                       */
/*============================================================================*/
/*                                                                            */
/* Unless otherwise agreed upon in writing between your company and           */
/* Renesas Electronics Corporation the following shall apply!                 */
/*                                                                            */
/* Warranty Disclaimer                                                        */
/*                                                                            */
/* There is no warranty of any kind whatsoever granted by Renesas. Any        */
/* warranty is expressly disclaimed and excluded by Renesas, either expressed */
/* or implied, including but not limited to those for non-infringement of     */
/* intellectual property, merchantability and/or fitness for the particular   */
/* purpose.                                                                   */
/*                                                                            */
/* Renesas shall not have any obligation to maintain, service or provide bug  */
/* fixes for the supplied Product(s) and/or the Application.                  */
/*                                                                            */
/* Each User is solely responsible for determining the appropriateness of     */
/* using the Product(s) and assumes all risks associated with its exercise    */
/* of rights under this Agreement, including, but not limited to the risks    */
/* and costs of program errors, compliance with applicable laws, damage to    */
/* or loss of data, programs or equipment, and unavailability or              */
/* interruption of operations.                                                */
/*                                                                            */
/* Limitation of Liability                                                    */
/*                                                                            */
/* In no event shall Renesas be liable to the User for any incidental,        */
/* consequential, indirect, or punitive damage (including but not limited     */
/* to lost profits) regardless of whether such liability is based on breach   */
/* of contract, tort, strict liability, breach of warranties, failure of      */
/* essential purpose or otherwise and even if advised of the possibility of   */
/* such damages. Renesas shall not be liable for any services or products     */
/* provided by third party vendors, developers or consultants identified or   */
/* referred to the User by Renesas in connection with the Product(s) and/or   */
/* the Application.                                                           */
/*                                                                            */
/*============================================================================*/
/* Environment:                                                               */
/*              Devices:        X2x                                           */
/*============================================================================*/

/*******************************************************************************
**                      Revision Control History                              **
*******************************************************************************/
/* 2.4.1:  30/06/2025  : Remove the SW-VERSION from header of file
 * 2.3.0:  28/02/2025  : Update SW-VERSION for
 *                       Ver22.01.00/Ver22.01.00.D U2Cx Release
 * 2.2.1:  31/12/2024  : Update SW-VERSION for Ver22.00.01 U2Ax Release
 * 2.2.0:  31/12/2024  : Update SW-VERSION
 *                       for Ver22.02.00/Ver22.02.00.D Final Release
 * 2.1.1:  27/06/2024  : Update SW-VERSION to 2.1.1
 * 2.1.0:  23/02/2024  : Update SW-VERSION to 2.1.0
 * 2.0.3:  15/04/2024  : Update SW-VERSION to 2.0.3
 * 2.0.1:  28/09/2023  : Initial Version
 */
/*******************************************************************************
**                         Input File                                         **
*******************************************************************************/
#ifndef OS_H
#define OS_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Std_Types.h"
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR release version information */
#define OS_AR_RELEASE_MAJOR_VERSION 4U
#define OS_AR_RELEASE_MINOR_VERSION 8U
#define OS_AR_RELEASE_REVISION_VERSION 0U

/* Module Software version information */
#define OS_SW_MAJOR_VERSION 2U
#define OS_SW_MINOR_VERSION 3U
#define OS_SW_PATCH_VERSION 0U
/*******************************************************************************
**                      Macro                                                 **
*******************************************************************************/
#define ISR(X) void OS_ISR_##X(void)
/* For Multi-Core support */
#ifdef USE_MULTI_CORE
#define SpinlockNothing             0U
#define SpinlockAllISRs             1U
#endif
/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/
#define OsCounter  (uint8)0u
#define OsCounter1 (uint8)1u
/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* OS ID Type */
typedef uint32 CounterType;
/* OS Tick reference type */
typedef uint32 TickType;
typedef P2VAR(TickType, AUTOMATIC, OS_APPL_DATA) TickRefType;
/* For Multi-Core support */
typedef unsigned short CoreIdType; /* Core identifier */
/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
extern StatusType GetCounterValue(CounterType CounterID, TickRefType Value);
/* For Multi-Core support */
extern CoreIdType GetCoreID(void);
#ifdef USE_MULTI_CORE
extern StatusType GetSpinlock(uint8 SpinlockType);
extern StatusType ReleaseSpinlock(uint8 SpinlockType);
#endif

#endif /* OS_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
