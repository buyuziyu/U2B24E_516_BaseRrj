/*============================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                         */
/* Module       = WdgIf.h                                                     */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2022-2025 Renesas Electronics Corporation. All rights reserved.        */
/*============================================================================*/
/* Purpose:                                                                   */
/* Provision for compiler macros and external declarations.                   */
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
/* Environment:                       X2x                                     */
/*============================================================================*/

/*******************************************************************************
**                      Revision Control History                              **
*******************************************************************************/
/*
 * 2.4.1:  30/06/2025  : Remove SW-VERSION in file header                       
 * 2.4.0:  30/06/2025  : Update SW-VERSION for RH850/Ver22.01.00(D)U2Ax release
 * 2.3.2:  29/04/2025  : Update SW-VERSION for RH850/Ver22.00.03 U2Bx-E 
 * 2.3.1:  31/03/2025  : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 * 2.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL                
 *                       Ver22.01.00/Ver22.01.00.D Release                    
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D
 *                       Final Release
 * 2.1.2:  31/10/2024  : Update SW-VERSION to 2.1.2
 * 2.1.1:  27/06/2024  : Update SW-VERSION to 2.1.1
 * 2.1.0:  23/02/2024  : Update SW-VERSION to 2.1.0
 * 2.0.0:  20/04/2023  : Update sw version to 2.0.0
 * 1.4.4:  28/09/2022  : Initial Version
 */
/*******************************************************************************
**                         Input File                                         **
*******************************************************************************/
#ifndef WDGIF_TYPES_H
#define WDGIF_TYPES_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Std_Types.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/* Autosar Specification Version */
#define WDGIF_TYPES_AR_MAJOR_VERSION  WDGIF_AR_MAJOR_VERSION_VALUE
#define WDGIF_TYPES_AR_MINOR_VERSION  WDGIF_AR_MINOR_VERSION_VALUE
#define WDGIF_TYPES_AR_PATCH_VERSION  WDGIF_AR_PATCH_VERSION_VALUE
/* File Version Information */
#define WDGIF_TYPES_SW_MAJOR_VERSION    2
#define WDGIF_TYPES_SW_MINOR_VERSION    3
#define WDGIF_TYPES_SW_PATCH_VERSION    2
/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/
/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
typedef enum
{
  WDGIF_UNINIT = 0,
  WDGIF_IDLE,
  WDGIF_BUSY
}WdgIf_StatusType;

typedef enum
{
  WDGIF_OFF_MODE = 0,
  WDGIF_SLOW_MODE,
  WDGIF_FAST_MODE
}WdgIf_ModeType;

#endif /* WDGIF_TYPES_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
