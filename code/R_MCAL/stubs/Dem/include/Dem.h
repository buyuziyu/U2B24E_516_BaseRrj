/*============================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                         */
/* Module       = Dem.h                                                       */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2023-2025 Renesas Electronics Corporation. All rights reserved.        */
/*============================================================================*/
/* Purpose:                                                                   */
/* This file is a stub for DEM component                                      */
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
external/X2x/common/generic/stubs/22_11/Dem/include/Dem_Cfg.h
 * 2.3.0      28/02/2025     Update SW-VERSION for
 *                           Ver22.01.00/Ver22.01.00.D U2Cx Release
 * 2.2.1      31/12/2024     Update SW-VERSION for Ver22.00.01 U2Ax Release
 * 2.2.0      31/12/2024     Update SW-VERSION 
 *                           for Ver22.02.00/Ver22.02.00.D Final Release
 * 2.1.1      27/06/2024     Update SW-VERSION to 2.1.1
 * 2.1.0      23/02/2024     Update SW-VERSION to 2.1.0
 * 2.0.3      15/04/2024     Update SW-VERSION to 2.0.3
 * 2.0.1      22/09/2023     Initial Version
 */
/*******************************************************************************
**                         Input File                                         **
*******************************************************************************/
#ifndef DEM_H
#define DEM_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Std_Types.h"
#include "Dem_Cfg.h"

/*******************************************************************************
**                      Version Information                                  **
*******************************************************************************/
/* AUTOSAR release version information */
#define DEM_AR_RELEASE_MAJOR_VERSION    4U
#define DEM_AR_RELEASE_MINOR_VERSION    8U
#define DEM_AR_RELEASE_REVISION_VERSION 0U

/* Module Software version information */
#define DEM_SW_MAJOR_VERSION    2U
#define DEM_SW_MINOR_VERSION    3U
#define DEM_SW_PATCH_VERSION    0U
/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/


/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

typedef uint16 Dem_EventIdType;                              /**<  DEM event ID type */
typedef uint8  Dem_EventStatusType;                          /**<  DEM event status type */

#define DEM_EVENT_STATUS_PASSED                (uint8)0x00
#define DEM_EVENT_STATUS_FAILED                (uint8)0x01
#define DEM_EVENT_STATUS_PREPASSED             (uint8)0x02
#define DEM_EVENT_STATUS_PREFAILED             (uint8)0x03
#define DEM_EVENT_STATUS_FDC_THRESHOLD_REACHED (uint8)0x04

/*******************************************************************************
**                         Global Data  Declarations                          **
*******************************************************************************/
extern VAR(uint16, DEM_VAR) Dem_EventId;                     /**<  DEM event ID*/
extern VAR(uint8 , DEM_VAR) Dem_EventStatus;                 /**<  DEM event status*/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/


extern Std_ReturnType Dem_SetEventStatus
                    (Dem_EventIdType EventId, Dem_EventStatusType EventStatus);

#endif /* DEM_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
