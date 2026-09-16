/*============================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                         */
/* Module       = MemIf.h                                                     */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2022-2025 Renesas Electronics Corporation. All rights reserved.        */
/*============================================================================*/
/* Purpose:                                                                   */
/* This file is a stub for MEMIF Module                                       */
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
/*
 * 2.3.1:  30/06/2025  : Update SW-VERSION for U2Ax Ver22.01.00(D) Final Release
 * 2.2.1:  31/03/2025  : Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D
 *                       Final Release
 * 2.1.1:  24/07/2024  : Update SW-VERSION to 2.1.1
 * 2.1.0:  23/02/2024  : Update SW-VERSION to 2.1.0
 * 2.0.3:  15/04/2024  : Update SW-VERSION to 2.0.3
 * 2.0.0:  27/04/2023  : Update MEMIF_SW_MAJOR_VERSION to 2
 *                       Update MEMIF_SW_MINOR_VERSION to 0
 * 1.4.5:  28/09/2022  : Initial Version
 */
/******************************************************************************/

#ifndef MEMIF_H
#define MEMIF_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR release version information */
#define MEMIF_AR_RELEASE_MAJOR_VERSION    4
#define MEMIF_AR_RELEASE_MINOR_VERSION    8
#define MEMIF_AR_RELEASE_REVISION_VERSION 0

/* Module software version information */
#define MEMIF_SW_MAJOR_VERSION    2
#define MEMIF_SW_MINOR_VERSION    3
#define MEMIF_SW_PATCH_VERSION    0

/* Type definition for MEMIF status types */
typedef enum
{
  MEMIF_UNINIT = 0,
  MEMIF_IDLE,
  MEMIF_BUSY,
  MEMIF_BUSY_INTERNAL
} MemIf_StatusType;

/* Type definition for MEMIF job result types */
typedef enum
{
  MEMIF_JOB_OK = 0,
  MEMIF_JOB_FAILED,
  MEMIF_JOB_PENDING,
  MEMIF_JOB_CANCELED,
  MEMIF_BLOCK_INCONSISTENT,
  MEMIF_BLOCK_INVALID
} MemIf_JobResultType;

/* Type definition for MEMIF mode types */
typedef enum
{
  MEMIF_MODE_SLOW = 0,
  MEMIF_MODE_FAST
} MemIf_ModeType;

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#endif /* MEMIF_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
