/*============================================================================*/
/* Project      = AUTOSAR Renesas X2x, R-Car S4 MCAL Components               */
/* File name    = Std_Types.h                                                 */
/* SW-VERSION   = 2.3.0                                                       */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c)  2023-2025 Renesas Electronics Corporation. All rights reserved.       */
/*============================================================================*/
/* Purpose:                                                                   */
/* Provision for Standard types                                               */
/*                                                                            */
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
/*              Devices:        X2x/R-Car                                     */
/*============================================================================*/

/*******************************************************************************
**                      Revision Control History                              **
*******************************************************************************/
/*
 * 2.3.0      28/02/2025     Update SW-VERSION for
 *                           RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0      31/12/2024     Update SW-VERSION
 *                           for Ver22.02.00/Ver22.02.00.D Final Release
 * 2.1.1      27/06/2024     Update SW-VERSION to 2.1.1
 * 2.1.0      23/02/2024     Update SW-VERSION to 2.1.0
 * 2.0.3      15/04/2024     Update SW-VERSION to 2.0.3
 * 2.0.1      22/09/2023     Initial Version
 */
/******************************************************************************/
#ifndef STD_TYPES_H
#define STD_TYPES_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Compiler.h"                  /* mapping compiler specific keywords */
#include "Platform_Types.h"            /* platform specific type definitions */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/*
 * AUTOSAR specification version information
 */
#define STD_TYPES_AR_RELEASE_MAJOR_VERSION     4
#define STD_TYPES_AR_RELEASE_MINOR_VERSION     8
#define STD_TYPES_AR_RELEASE_REVISION_VERSION  0

/*
 * File version information
 */
#define STD_TYPES_SW_MAJOR_VERSION  2
#define STD_TYPES_SW_MINOR_VERSION  3
#define STD_TYPES_SW_PATCH_VERSION  0

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                    **
*******************************************************************************/

/* for OSEK compliance this typedef has been added (SWS_Std_00006) */
#ifndef STATUSTYPEDEFINED
  #define STATUSTYPEDEFINED
  #define E_OK      0x00u
  typedef unsigned char StatusType;
#endif

#define E_NOT_OK    0x01u

/* SWS_Std_00005 */
/* Std_ReturnType shall normally be used with value E_OK or E_NOT_OK. */
typedef uint8 Std_ReturnType;

typedef struct
{
  uint16  vendorID;
  uint16  moduleID;
  uint8  sw_major_version;
  uint8  sw_minor_version;
  uint8  sw_patch_version;
} Std_VersionInfoType;      /* SWS_Std_00015                         */

/* SWS_Std_00007 */
#define STD_HIGH    0x01u   /* Physical state 5V or 3.3V             */
#define STD_LOW     0x00u   /* Physical state 0V                     */

/* SWS_Std_00013 */
#define STD_ACTIVE  0x01u   /* Logical state active                  */
#define STD_IDLE    0x00u   /* Logical state idle                    */

/* SWS_Std_00010 */
#define STD_ON      0x01u
#define STD_OFF     0x00u

/* SWS_Std_00031 */
#define NULL_PTR  ((void *)0)

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#endif  /* STD_TYPES_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

