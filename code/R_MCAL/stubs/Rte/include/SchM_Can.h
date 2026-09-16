 /*===========================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                         */
/* Module       = SchM_Can.h                                                  */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2022-2025 Renesas Electronics Corporation. All rights reserved.        */
/*============================================================================*/
/* Purpose:                                                                   */
/* Header file information for application.                                   */
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
/*              Devices:        X2x                                           */
/*============================================================================*/

/*******************************************************************************
**                      Revision Control History                              **
*******************************************************************************/
/*
 * 2.4.1:  30/06/2025  : Remove the SW-VERSION from header of file
 * 2.3.1:  31/03/2025  : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 * 2.3.0:  28/02/2025  : Update SW-VERSION for RH850/Ver22.01.00/Ver22.01.00.D 
 *                       Final Release
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D
 *                       Final Release
 * 2.1.1:  27/06/2024  : Update SW-VERSION to 2.1.1
 * 2.1.0:  23/02/2024  : Update SW-VERSION to 2.1.0
 * 2.0.0:  16/08/2023  : Add new function to support multi core
 * 1.4.5:  28/09/2022  : Initial Version
 */
/******************************************************************************/
#ifndef SCHM_CAN_H
#define SCHM_CAN_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/
#define NUM_CPU                                                    (uint8)0x06U
/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

extern void SchM_Enter_Can_CAN_RAM_DATA_PROTECTION(void);
extern void SchM_Exit_Can_CAN_RAM_DATA_PROTECTION(void);

extern void SchM_Enter_Can_CAN_INTERRUPT_CONTROL_PROTECTION(void);
extern void SchM_Exit_Can_CAN_INTERRUPT_CONTROL_PROTECTION(void);

extern void SchM_Enter_Can_CAN_INTERRUPT_CONTROL_PROTECTION_GLOBAL(void);
extern void SchM_Exit_Can_CAN_INTERRUPT_CONTROL_PROTECTION_GLOBAL(void);

extern void SchM_Enter_Can_CAN_RAM_DATA_PROTECTION_GLOBAL(void);
extern void SchM_Exit_Can_CAN_RAM_DATA_PROTECTION_GLOBAL(void);

/* API for schedule processing of write */
extern void Can_MainFunction_Write(void);
extern void Can_MainFunction_Write_0(void);
extern void Can_MainFunction_Write_1(void);
extern void Can_MainFunction_Write_2(void);
extern void Can_MainFunction_Write_3(void);
extern void Can_MainFunction_Write_4(void);
extern void Can_MainFunction_Write_5(void);
extern void Can_MainFunction_Write_6(void);
extern void Can_MainFunction_Write_7(void);
extern void Can_MainFunction_Write_8(void);
extern void Can_MainFunction_Write_9(void);
extern void Can_MainFunction_Write_10(void);
extern void Can_MainFunction_Write_11(void);
extern void Can_MainFunction_Write_12(void);
extern void Can_MainFunction_Write_13(void);
extern void Can_MainFunction_Write_14(void);
extern void Can_MainFunction_Write_15(void);

/* API for schedule processing of read */
extern void Can_MainFunction_Read(void);
extern void Can_MainFunction_Read_0(void);
extern void Can_MainFunction_Read_1(void);
extern void Can_MainFunction_Read_2(void);
extern void Can_MainFunction_Read_3(void);
extern void Can_MainFunction_Read_4(void);
extern void Can_MainFunction_Read_5(void);
extern void Can_MainFunction_Read_6(void);
extern void Can_MainFunction_Read_7(void);
extern void Can_MainFunction_Read_8(void);
extern void Can_MainFunction_Read_9(void);
extern void Can_MainFunction_Read_10(void);
extern void Can_MainFunction_Read_11(void);
extern void Can_MainFunction_Read_12(void);
extern void Can_MainFunction_Read_13(void);
extern void Can_MainFunction_Read_14(void);
extern void Can_MainFunction_Read_15(void);

/* API for schedule processing of BusOff */
extern void Can_MainFunction_BusOff(void);

/* API for schedule processing of Wakeup */
extern void Can_MainFunction_Wakeup(void);

/* API for schedule processing of Mode */
extern void Can_MainFunction_Mode(void);

#endif /* SCHM_CAN_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
