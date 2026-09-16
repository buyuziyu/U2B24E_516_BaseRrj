/*============================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                         */
/* Module       = Det.h                                                       */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2023-2025 Renesas Electronics Corporation. All rights reserved.        */
/*============================================================================*/
/* Purpose:                                                                   */
/* This file is a stub for DET component                                      */
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
/* 2.4.1:     30/06/2025     Remove the SW-VERSION from header of file
 * 2.3.0:     28/02/2025     Update SW-VERSION for
 *                           Ver22.01.00/Ver22.01.00.D U2Cx Release
 * 2.2.1      31/12/2024     Update SW-VERSION for Ver22.00.01 U2Ax Release
 * 2.2.0      31/12/2024     Update SW-VERSION
 *                           for Ver22.02.00/Ver22.02.00.D Final Release
 * 2.1.1      27/06/2024     Update SW-VERSION to 2.1.1
 * 2.1.0      23/02/2024     Update SW-VERSION to 2.1.0
 * 2.0.3      15/04/2024     Update SW-VERSION to 2.0.3
 * 2.0.1      22/09/2023     Initial Version
 */
/******************************************************************************/

/*******************************************************************************
**                         Input File                                         **
*******************************************************************************/
#ifndef DET_H
#define DET_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Std_Types.h"

/*******************************************************************************
**                      Version Information                                  **
*******************************************************************************/
/* AUTOSAR release version information */
#define DET_AR_RELEASE_MAJOR_VERSION    4U
#define DET_AR_RELEASE_MINOR_VERSION    8U
#define DET_AR_RELEASE_REVISION_VERSION 0U

/* Module Software version information */
#define DET_SW_MAJOR_VERSION    2U
#define DET_SW_MINOR_VERSION    3U
#define DET_SW_PATCH_VERSION    0U

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/


/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/* Defining the structure to store the parameters of Det Report Error
   function */
typedef struct STag_Det_Error
{ /* It will store the ModuleId of the reporting module */
  uint16 ModuleId;

  /* It will store the index based InstanceId of the reporting module */
  uint8 InstanceId;

  /* It will store the ApiId of the reporting function */
  uint8 ApiId;

  /* It will store the ErrorId of the reporting error */
  uint8 ErrorId;

}Det_Error;

/* Defining the structure to store the parameters of Det Report Error
   function */
typedef struct STag_Det_Fault
{ /* It will store the ModuleId of the reporting module */
  uint16 ModuleId;

  /* It will store the index based InstanceId of the reporting module */
  uint8 InstanceId;

  /* It will store the ApiId of the reporting function */
  uint8 ApiId;

  /* It will store the FaultId of the reporting error */
  uint8 FaultId;

}Det_Fault;

/*******************************************************************************
**                         Global Data  Declarations                          **
*******************************************************************************/
extern Det_Error GstDetErrBuffer[];
extern Det_Fault GstDetFaultBuffer[];
extern uint8 GstDetBuffIndex;

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
extern Std_ReturnType Det_ReportError(uint16 ModuleId, uint8 InstanceId,
                                                    uint8 ApiId, uint8 ErrorId);

extern Std_ReturnType Det_ReportRuntimeError(uint16 ModuleId, uint8 InstanceId,
                                                    uint8 ApiId, uint8 ErrorId);
                                                    
extern Std_ReturnType Det_ReportTransientFault(uint16 ModuleId, uint8 InstanceId,
                                                    uint8 ApiId, uint8 FaultId);
#endif /* DET_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
